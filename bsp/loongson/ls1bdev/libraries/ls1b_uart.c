 /*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-02   michael5hzg@gmail.com   adapt to ls1b
 */
// 串口相关源码

#include <stdio.h>
#include <stdarg.h>
#include "ls1b_public.h"
#include "ls1b_regs.h"
#include "ls1b_pin.h"
#include "ls1b_uart.h"
#include "ls1b_clock.h"
#include "ls1b.h"


// 串口线路状态寄存器的位域
#define LS1B_UART_LSR_TE                (1 << 6)
#define LS1B_UART_LSR_TFE               (1 << 5)


// 打印缓存的大小
#define LS1B_UART_PRINT_BUF_SIZE        (256)


// 调试串口信息
ls1b_uart_info_t debug_uart_info = {0};


/*
 * 获取指定串口模块的基地址
 * @UARTx 串口编号
 * @ret 基地址
 */
void *uart_get_base(ls1b_uart_t UARTx)
{
    void *base = NULL;

    switch (UARTx)
    {
        case LS1B_UART00:
            base = (void *)LS1B_UART00_BASE;
            break;
        case LS1B_UART01:
            base = (void *)LS1B_UART01_BASE;
            break;

        case LS1B_UART1:
            base = (void *)LS1B_UART1_BASE;
            break;
        
        case LS1B_UART2:
            base = (void *)LS1B_UART2_BASE;
            break;

        case LS1B_UART3:
            base = (void *)LS1B_UART3_BASE;
            break;
        
        case LS1B_UART4:
            base = (void *)LS1B_UART4_BASE;
            break;

        case LS1B_UART5:
            base = (void *)LS1B_UART5_BASE;
            break;

        case LS1B_UART6:
            base = (void *)LS1B_UART6_BASE;
            break;

        case LS1B_UART7:
            base = (void *)LS1B_UART7_BASE;
            break;

        case LS1B_UART8:
            base = (void *)LS1B_UART8_BASE;
            break;

        case LS1B_UART9:
            base = (void *)LS1B_UART9_BASE;
            break;

        case LS1B_UART10:
            base = (void *)LS1B_UART10_BASE;
            break;

        case LS1B_UART11:
            base = (void *)LS1B_UART11_BASE;
            break;

        default:
            break;
    }

    return base;
}


/*
 * 初始化指定的串口模块
 * @uart_info_p 串口模块信息
 */
void uart_init(ls1b_uart_info_t *uart_info_p)
{
    void *uart_base = uart_get_base(uart_info_p->UARTx);
    unsigned long baudrate_div = 0;

    // 禁止所有中断
    reg_write_8(0,      uart_base + LS1B_UART_IER_OFFSET);

    // 接收FIFO的中断申请Trigger为14字节，清空发送和接收FIFO，并复位
    reg_write_8(0xc3,   uart_base + LS1B_UART_FCR_OFFSET);

    // 设置波特率
    reg_write_8(0x80,   uart_base + LS1B_UART_LCR_OFFSET);
    baudrate_div = clk_get_apb_rate() / 16 / uart_info_p->baudrate;
    reg_write_8((baudrate_div >> 8) & 0xff, uart_base + LS1B_UART_MSB_OFFSET);
    reg_write_8(baudrate_div & 0xff,        uart_base + LS1B_UART_LSB_OFFSET);

    // 8个数据位，1个停止位，无校验
    reg_write_8(0x03,   uart_base + LS1B_UART_LCR_OFFSET);

    // 使能接收中断
    if (TRUE == uart_info_p->rx_enable)
    {
        reg_write_8(IER_IRxE|IER_ILE , uart_base + LS1B_UART_IER_OFFSET);
    }

    return ;
}


/*
 * 判断FIFO是否为空
 * @uartx 串口号
 * @ret TRUE or FALSE
 */
BOOL uart_is_transmit_empty(ls1b_uart_t uartx)
{
    void *uart_base = uart_get_base(uartx);
    unsigned char status = reg_read_8(uart_base + LS1B_UART_LSR_OFFSET);

    if (status & (LS1B_UART_LSR_TE | LS1B_UART_LSR_TFE))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


/*
 * 发送一个字节
 * @uartx 串口号
 * @ch 待发送的字符串
 */
void uart_putc(ls1b_uart_t uartx, unsigned char ch)
{
    void *uart_base = uart_get_base(uartx);
    
    // 等待
    while (FALSE == uart_is_transmit_empty(uartx))
        ;

    // 发送
    reg_write_8(ch, uart_base + LS1B_UART_DAT_OFFSET);

    return ;
}


/*
 * 打印一个字符串到指定串口
 * @uartx 串口号
 * @str 待打印的字符串
 */
void uart_print(ls1b_uart_t uartx, const char *str)
{
    while ('\0' != *str)                // 判断是否为字符串结束符
    {
        uart_putc(uartx, *str);   // 发送一个字符
        str++;
    }

    return ;
}


/*
 * 初始化串口2
 */
void uart2_init(void)
{
    unsigned int tx_gpio = 37;
    unsigned int rx_gpio = 36;

    // 设置复用
    pin_set_remap(tx_gpio, PIN_REMAP_SECOND);
    pin_set_remap(rx_gpio, PIN_REMAP_SECOND);
    
    // 初始化相关寄存器
    debug_uart_info.UARTx = LS1B_UART2;
    debug_uart_info.baudrate = 115200;
    debug_uart_info.rx_enable = FALSE;  // 调试串口只需要打印(发送)功能，不需要接收功能
    uart_init(&debug_uart_info);

    return ;
}


/*
 * 在串口2上打印字符串
 * @str 待打印的字符串
 */
void uart2_print(const char *str)
{
    uart_print(LS1B_UART2, str);
    return ;
}


/*
 * 在调试串口打印字符串
 * @str 待打印的字符串
 */
void uart_debug_print(const char *str)
{
    uart_print(debug_uart_info.UARTx, str);
    return ;
}


/*
 * 在调试串口打印一个字符
 * @ch 待打印的字符
 */
void uart_debug_putc(unsigned char ch)
{
    uart_putc(debug_uart_info.UARTx, ch);
    return ;
}


