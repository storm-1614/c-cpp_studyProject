# 第一个纯 C 的 Arduino

``` c
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
```

就是 CPU 空转一段时间，翻转一个 GPIO 然后 LED 闪烁。  

## 头文件
### avr/io.h
提供了 ATmega328P 的寄存器名和位符号。是 avr-libc 对 ATmega328P 硬件寄存器的 C 定义。  

### util/delay.h
提供
```
_delay_ms();
_delay_us();
```

但这里需要知道 CPU 的主频比如在编译时：  
``` bash
avr-gcc -DF_CPU=16000000UL ...
```

## 设置输出
``` c
DDRB |= (1 << PB5);
```

PB5 的宏实际就是 5，这里的右侧实际是 : `1 << 5` 把第 5 位置 1：  
``` c
DDRB |= 0b00100000;
```

所以含义是把 DDRB 的 bit5 设成 1。  
ATmega328P Datasheet 规定：  
DDRx = 1 为输入，DDRx = 0 为输出。  

真实意思为：把 Port B 的第 5 号针脚 PB5 设置成输出。  

### PB5
Arduino UNO 板载 LED 所连接的 D13 对应 ATmega328P 的 PB5。  

## 闪灯
``` c
PORTB |= (1 << PB5);
PORTB &= ~(1 << PB5);
```

第一行同样的把 PORTB 的第 5 位设置为 1。  
因为 PB5 已经是输出，该位置 1 就相当于 PB5 输出高电平于是板载 LED 亮。  

``` c
PORTB &= ~(1 << PB5);
```

这句对 bit5 取 &0 就是把 bit5 清零。变成低电平。  

整套循环就是近乎在 500ms 闪灯。  

### DDRB 和 PORTB
- DDRB 决定这个引脚是输入还是输出
- PORTB 决定这个引脚在输出模式下输出高电平还是低电平

| DDRB | PORTB | PB5 状态 |
|---|---|---|
| 0 | 0 | 输入，浮空 |
| 0 | 1 | 输入，内部上拉 |
| 1 | 0 | 输出 LOW |
| 1 | 1 | 输出 HIGH |

总结：**DDR 管方向，PORT 管输出，PIN 管读取**  
