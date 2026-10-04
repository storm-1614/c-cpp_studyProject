#include <avr/io.h>

// 初始化 UART
void uart_init(void)
{
    // 波特率 9600
    UBRR0 = 103;

    // 开启发送和接收
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);

    // 8N1
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

// 发送字符
void uart_putc(char c)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }

    UDR0 = c;
}

// 接收 1 字节
char uart_getc(void)
{
    while (!(UCSR0A & (1 << RXC0)))
    {
    }

    return UDR0;
}

int main(void)
{
    uart_init();

    while (1)
    {
        char c = uart_getc();
        uart_putc(c);
    }
}
