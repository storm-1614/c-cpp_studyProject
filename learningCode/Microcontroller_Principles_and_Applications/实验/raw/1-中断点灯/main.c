#include <avr/interrupt.h>
#include <avr/io.h>

int main(void)
{
    // LED 引脚作为输出
    DDRB |= (1 << PB5);

    // Timer1:
    // Comprare Match 后自动清零
    TCCR1B |= (1 << WGM12);

    // 数到 31249
    OCR1A = 31249;

    // Timer 时钟 = 16 MHz / 256
    TCCR1B |= (1 << CS12);

    // Compare Match 可以产生中断
    TIMSK1 |= (1 << OCIE1A);


    // CPU 允许中断
    sei();

    while (1)
    {
    }
}

ISR(TIMER1_COMPA_vect)
{
    // 每 500 ms 执行一次
    PORTB ^= (1 << PB5);
}
