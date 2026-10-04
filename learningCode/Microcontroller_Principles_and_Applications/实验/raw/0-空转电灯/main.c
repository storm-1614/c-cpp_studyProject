#include <avr/io.h>
#include <util/delay.h>

int main()
{
    // PB 5 设置为输出
    DDRB |= (1 << PB5);

    while (1)
    {
        // PB5 输出高电平， LED 亮
        PORTB |= (1 << PB5);
        _delay_ms(500);

        // PB5 输出低电平，LED 灭
        PORTB &= ~(1 << PB5);
        _delay_ms(500);

    }
    return 0;
}
