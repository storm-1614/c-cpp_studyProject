# UART 发送数据 中断版

这里主要是用 `USART_UDRE_vect` ： UART 数据寄存器空中断。  

在调用 putc 的时候启用：  

``` c
// 置位 UDRIE0 启用 USART_UDRE 中断
UCSR0B |= (1 << UDRIE0);
```

中断向量的 handler 就是把发送环形缓冲区待发送的数据逐字节写入 UDR0 直到空的时候关闭中断：  

``` c
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
```

当调用 uart_putc 的时候仅写入环形缓冲区，然后开启中断，实际发送由中断实现。  
