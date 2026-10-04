# UART 接收

最开始的代码实际新增了对接收位使能，然后写接收字符函数。  

## 初始化 UART

把 RXEN0 也给置 1 了。  
``` c
UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
```

其余不变。  

## 接收字符
``` c
// 接收 1 字节
char uart_getc(void)
{
    while (!(UCSR0A & (1 << RXC0)))
    {
    }

    return UDR0;
}
```

同样的方式，阻塞等待接收然后返回 UDR0。    

这里的 UDR0 名字一样但是接收发送对应的实际寄存器不一样。  

简单就做一个发送接收的循环：  
``` c
int main(void)
{
    uart_init();

    while (1)
    {
        char c = uart_getc();
        uart_putc(c);
    }
}
```

---
但 uart_getc 的循环一进去就必须要接收 1 字节数据，不然就阻塞了 CPU ，只能说是最基础的了。 
