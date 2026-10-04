#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define RX_BUFFER_SIZE 64

// 环形缓冲区
volatile char rx_buffer[RX_BUFFER_SIZE];

// head: 下一次写到哪里
// tail: 下一次读到哪里
volatile uint8_t rx_head = 0;
volatile uint8_t rx_tail = 0;

void uart_init(void)
{
    // 9600 band
    UBRR0 = 103;

    // 开启发送、接收、接收完成中断
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);

    // 8N1
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

// 发送一字符
void uart_putc(char c)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }

    UDR0 = c;
}

// 发送字符串
void uart_puts(const char *s)
{
    while (*s)
    {
        uart_putc(*s++);
    }
}

uint8_t uart_available(void)
{
    return rx_head != rx_tail;
}

char uart_getc(void)
{
    while (rx_head == rx_tail)
    {
    }

    char c = rx_buffer[rx_tail];
    rx_tail = (rx_tail + 1) % RX_BUFFER_SIZE;

    return c;
}

// UART 接收 中断 handler
ISR(USART_RX_vect)
{
    char c = UDR0;

    uint8_t next = (rx_head + 1) % RX_BUFFER_SIZE;

    // 当 next == rx_tail 说明环形缓冲区满了
    if (next != rx_tail)
    {
        rx_buffer[rx_head] = c;
        rx_head = next;
    }
}

int main(void)
{
    uart_init();
    sei();

    uart_puts("UART ready\r\n");

    while (1)
    {
        if (uart_available())
        {
            char c = uart_getc();
            uart_putc(c);
        }
    }
}
