/* uart_echo.c
 * 经典 12T MCS-51 / AT89C52 示例，Keil C51 + REG52.H
 * 前提：11.0592 MHz 晶振，9600 baud，8N1。
 * 与 1T 8051 / 使用独立波特率发生器的型号不保证直接兼容。
 */
#include <REG52.H>

void uart_init(void)
{
    ES = 0;                /* 本例查询收发，不使用串口中断 */
    ET1 = 0;               /* Timer1 专用于波特率，不开 T1 中断 */
    TR1 = 0;

    PCON &= 0x7F;          /* SMOD = 0，不改变 PCON 其余位 */
    TMOD = (TMOD & 0x0F) | 0x20; /* T1 模式2：8位自动重装；保留 T0 配置 */
    TH1 = 0xFD;           /* 11.0592 MHz、12T、SMOD=0 -> 9600 */
    TL1 = 0xFD;
    SCON = 0x50;          /* 串口模式1：8位数据、允许接收 */
    TI = 0;
    RI = 0;

    TR1 = 1;              /* 启动定时器1 */
}

void uart_send_byte(unsigned char value)
{
    SBUF = value;         /* 写 SBUF：启动发送 */
    while (TI == 0) { }   /* 等待发送标志置位 */
    TI = 0;               /* TI 由软件清零 */
}

/* 收到一个字节返回 1，未收到返回 0；不阻塞主循环 */
unsigned char uart_try_read(unsigned char *value)
{
    if (RI == 0) {
        return 0;
    }
    *value = SBUF;        /* 读 SBUF：取接收缓冲的数据 */
    RI = 0;               /* RI 由软件清零 */
    return 1;
}

void main(void)
{
    unsigned char ch;

    uart_init();
    while (1) {
        if (uart_try_read(&ch)) {
            uart_send_byte(ch); /* 串口助手发什么，就回传什么 */
        }
    }
}
