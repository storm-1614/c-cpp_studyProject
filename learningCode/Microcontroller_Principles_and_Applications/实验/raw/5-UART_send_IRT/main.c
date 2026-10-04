#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

#define TX_BUFFER_SIZE 64

volatile char tx_buffer[TX_BUFFER_SIZE];
volatile uint8_t tx_head = 0;
volatile uint8_t tx_tail = 0;

void uart_init(void)
{
    // 9600 band
    UBRR0 = 103;

    // 开启发送
    UCSR0B |= (1 << TXEN0);

    // 8N1
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

// 发送字符
void uart_putc(char c)
{
    uint8_t next = (tx_head + 1) % TX_BUFFER_SIZE;
    // TX buffer 满了就阻塞等待
    while (next == tx_tail)
    {
    }

    tx_buffer[tx_head] = c;
    tx_head = next;

    // 置位 UDRIE0 启用 USART_UDRE 中断
    UCSR0B |= (1 << UDRIE0);
}

// 发送字符串
void uart_puts(const char *s)
{
    while (*s)
    {
        uart_putc(*s++);
    }
}

// 当 UDR0 空就触发中断把字符给 UART 的中断
ISR(USART_UDRE_vect)
{
    // 如果队列为空
    if (tx_head == tx_tail)
    {
        UCSR0B &= ~(1 << UDRIE0);
        return;
    }

    // 否则读取数据
    UDR0 = tx_buffer[tx_tail];

    tx_tail = (tx_tail + 1) % TX_BUFFER_SIZE;
}

int main(void)
{
    uart_init();

    sei();

    uart_puts("Hello interrput UART!\r\n");

    while (1)
    {
    }
}
