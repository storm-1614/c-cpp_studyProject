#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <util/atomic.h>

volatile uint32_t tick = 0;

// Timer1 Compare Match 中断
ISR(TIMER1_COMPA_vect)
{
    tick++;
}

// 初始化 timer1
void timer1_init(void)
{
    // CTC 模式
    TCCR1B |= (1 << WGM12);

    // 每 1 ms
    OCR1A = 249;

    // 开启 Compare 中断
    TIMSK1 |= (1 << OCIE1A);

    // 64 分频
    TCCR1B |= (1 << CS11) | (1 << CS10);
}

/* 初始化 UART
 * 配置波特率，打开发送器配置 8N1
 */
void uart_init(void)
{
    UBRR0 = 103; // 波特率 9600

    UCSR0B |= (1 << TXEN0); // 开启发送器

    // 8 data bits
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}


// 发送字符
void uart_putc(char c)
{
    while (!(UCSR0A & (1 << UDRE0))) // 等待发送数据
    {
    }

    UDR0 = c; // 要发送的数据
}

// 发送字符串
void uart_puts(const char *s)
{
    while (*s)
    {
        uart_putc(*s);
        s++;
    }
}

// 发送 u32
void uart_put_u32(uint32_t n)
{
    char buf[10];
    uint8_t i = 0;
    uint8_t j = 0;
    if (n == 0)
    {
        buf[0] = '0';
        i = 1;
    }

    while (n > 0)
    {
        buf[i++] = (n % 10) + '0';
        n /= 10;
    }

    while (i > 0)
    {
        uart_putc(buf[--i]);
    }
}

int main()
{
    uint32_t snaphost;
    uart_init();
    timer1_init();

    sei();

    while (1)
    {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            snaphost = tick;
        }

        uart_puts("tick =");
        uart_put_u32(snaphost);
        uart_puts("\r\n");

        _delay_ms(1000);
    }
}
