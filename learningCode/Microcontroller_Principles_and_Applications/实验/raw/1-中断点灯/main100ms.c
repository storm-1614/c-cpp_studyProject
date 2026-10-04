#include <avr/interrupt.h>
#include <avr/io.h>

int main()
{
    // 设置的 PB5 为输出
    DDRB |= (1 << PB5);

    // 设置 Timer1 TCC 模式
    TCCR1B |= (1 << WGM12);

    OCR1A = 6249; // 100 ms

    // 写 TCC12
    TCCR1B |= (1 << CS12);

    TIMSK1 |= (1 << OCIE1A);

    sei();

    while (1)
    {
    }
}

ISR(TIMER1_COMPA_vect)
{
    PORTB ^= (1 << PB5);
}
