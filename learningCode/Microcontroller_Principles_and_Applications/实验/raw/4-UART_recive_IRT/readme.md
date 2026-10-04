# UART 接收 中断版
之前的 getc 需要一个 while 循环阻塞。但如果用中断就能实现非阻塞接收了。  

## UCSR0B 添加 RXCIE0 位
RXCIE0 是 USART0 Receive Complete Interrupt Enable 也就是接收完成中断使能。这样就打开这个中断了。  

## USART_RX_vect

这里写接收完成中断向量的 handler:  
``` c
ISR(USART_RX_vect)
{
    rx_byte = UDR0;
    rx_ready = 1;
}
```

其实就是 rx_bytes 写入数据，然后 ready 设置为 true。  

## main
这时候 main 的 while 循环只需要不断判断 rx_ready 就好了，如果为 1 直接打印出 rx_bytes。  

``` c
int main(void)
{
    uart_init();
    sei();

    while(1)
    {
        if (rx_ready)
        {
            char c = rx_byte;
            rx_ready = 0;

            uart_putc(c);
        }
    }
}
```

---
但这里只是一个单字节，假如上位机迅速发送大量字节就不能保证全部接收。这就引入了环形缓冲区。  

## 环形缓冲区
引入一个数组保存接收的数据，这样接收到的数据不是马上发送而是先放到缓冲区，等 CPU 空闲再来处理。用取模就可以形成环绕，引入 `tail` 和 `head` 两个变量，这样就有：  

``` c
#define RX_BUFFER_SIZE 64

// 环形缓冲区
volatile char rx_buffer[RX_BUFFER_SIZE];

// head: 下一次写到哪里
// tail: 下一次读到哪里
volatile uint8_t rx_head = 0;
volatile uint8_t rx_tail = 0;
```

最开始 `rx_head` = `rx_tail` 此时可以说明环形缓冲区空。当我们写入的时候就将 head 自增，读取就从 tail 读并自增。这样就把硬件接收速度和程序处理速度解耦了。  

### 接收-生产
用 UART 接收完成中断做实际接收：  

``` c
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
```

根据如果 `next == rx_tail` 也就是写下一个位置如果与 tail 重叠就说明是满的，就是说 next 不能追上 tail，只有 tail 追上 next 才算是空的。  
本质就是读取 UDR0 然后拿到 next 的索引如果环形缓冲区未满就写入到环形缓冲区。  

这里用 `head == tail` 表示空，所以无法把 4 个格子都写满，否则无法区分满与空的语义。  

### 消费
当 CPU 有空闲的时候，就会检查是否 `head != tail`:  
``` c
uint8_t uart_available(void)
{
    return rx_head != rx_tail;
}
```

如果是，就会进入循环把缓冲区的东西都消费掉：  
```c
while (1)
{
    if (uart_available())
    {
        char c = uart_getc();
        uart_putc(c);
    }
}
```

这里的 `uart_getc()` 直接消费环形缓冲区：  
``` c
char uart_getc(void)
{
    while (rx_head == rx_tail)
    {
    }

    char c = rx_buffer[rx_tail];
    rx_tail = (rx_tail + 1) % RX_BUFFER_SIZE;

    return c;
}
```


