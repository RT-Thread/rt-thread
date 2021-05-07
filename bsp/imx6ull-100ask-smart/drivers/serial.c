/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-03-30     Bernard      the first verion
 */

#include <rthw.h>
#include <rtdevice.h>

#include "serial.h"
#include "board.h"
#include "mmu.h"

/*根据IMX6ULL芯片手册<<55.15 UART Memory Map/Register Definition>>的3608页，定义UART的结构体,*/
typedef struct {
  volatile unsigned int  URXD;               /**< UART Receiver Register, offset: 0x0              串口接收寄存器，偏移地址0x0     */
           unsigned char RESERVED_0[60];
  volatile unsigned int  UTXD;               /**< UART Transmitter Register, offset: 0x40          串口发送寄存器，偏移地址0x40*/
           unsigned char RESERVED_1[60];
  volatile unsigned int  UCR1;               /**< UART Control Register 1, offset: 0x80            串口控制寄存器1，偏移地址0x80*/
  volatile unsigned int  UCR2;               /**< UART Control Register 2, offset: 0x84            串口控制寄存器2，偏移地址0x84*/
  volatile unsigned int  UCR3;               /**< UART Control Register 3, offset: 0x88            串口控制寄存器3，偏移地址0x88*/
  volatile unsigned int  UCR4;               /**< UART Control Register 4, offset: 0x8C            串口控制寄存器4，偏移地址0x8C*/
  volatile unsigned int  UFCR;               /**< UART FIFO Control Register, offset: 0x90         串口FIFO控制寄存器，偏移地址0x90*/
  volatile unsigned int  USR1;               /**< UART Status Register 1, offset: 0x94             串口状态寄存器1，偏移地址0x94*/
volatile unsigned int  USR2;               /**< UART Status Register 2, offset: 0x98             串口状态寄存器2，偏移地址0x98*/
  volatile unsigned int  UESC;               /**< UART Escape Character Register, offset: 0x9C     串口转义字符寄存器，偏移地址0x9C*/
  volatile unsigned int  UTIM;               /**< UART Escape Timer Register, offset: 0xA0         串口转义定时器寄存器 偏移地址0xA0*/
  volatile unsigned int  UBIR;               /**< UART BRM Incremental Register, offset: 0xA4      串口二进制倍率增加寄存器 偏移地址0xA4*/
  volatile unsigned int  UBMR;               /**< UART BRM Modulator Register, offset: 0xA8        串口二进制倍率调节寄存器 偏移地址0xA8*/
  volatile unsigned int  UBRC;               /**< UART Baud Rate Count Register, offset: 0xAC      串口波特率计数寄存器 偏移地址0xAC*/
  volatile unsigned int  ONEMS;              /**< UART One Millisecond Register, offset: 0xB0      串口一毫秒寄存器 偏移地址0xB0*/
  volatile unsigned int  UTS;                /**< UART Test Register, offset: 0xB4                 串口测试寄存器 偏移地址0xB4*/
  volatile unsigned int  UMCR;               /**< UART RS-485 Mode Control Register, offset: 0xB8  串口485模式控制寄存器 偏移地址0xB8*/
} UART_Type;



struct hw_uart_device
{
    rt_uint32_t hw_base;
    rt_uint32_t irqno;
};

#define UART_DR(base)   __REG32(base + 0x00)
#define UART_FR(base)   __REG32(base + 0x18)
#define UART_CR(base)   __REG32(base + 0x30)
#define UART_IMSC(base) __REG32(base + 0x38)
#define UART_ICR(base)  __REG32(base + 0x44)

#define UARTFR_RXFE     0x10
#define UARTFR_TXFF     0x20
#define UARTIMSC_RXIM   0x10
#define UARTIMSC_TXIM   0x20
#define UARTICR_RXIC    0x10
#define UARTICR_TXIC    0x20

static void rt_hw_uart_isr(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    /* 115200,8n1 */
    volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA ;
    volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA  ;
    volatile unsigned int *IOMUXC_UART1_RX_DATA_SELECT_INPUT ;
    volatile unsigned int *CCM_CSCDR1;
    volatile unsigned int *CCM_CCGR5;

    IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA     = (volatile unsigned int *)rt_ioremap((void *)0x20E0084, 4);
    IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA     = (volatile unsigned int *)rt_ioremap((void *)0x20E0088, 4);
    IOMUXC_UART1_RX_DATA_SELECT_INPUT       = (volatile unsigned int *)rt_ioremap((void *)0x20E0624, 4);
    CCM_CSCDR1 = (volatile unsigned int *)rt_ioremap((void *)0x020C4024, 4);
    CCM_CCGR5 = (volatile unsigned int *)rt_ioremap((void *)0x020C407C, 4);

    struct hw_uart_device * uart = (struct hw_uart_device *)serial->parent.user_data;

    UART_Type *uart_reg = (UART_Type *)uart->hw_base;

    /* 设置UART的总时钟
     * UART_CLK_ROOT = 80Mhz
     */
    *CCM_CSCDR1 &= ~((1<<6) | (0x3f));

    /* 给UART1模块提供时钟
     * uart1_clk_enable
     */
    *CCM_CCGR5 |= (3<<24);

    /* 配置引脚功能 */
    *IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA &= ~0xf;
    *IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA &= ~0xf;

    /* IMX6ULL特殊的地方 */
    *IOMUXC_UART1_RX_DATA_SELECT_INPUT |= 3;


    /* 设置波特率
     * 115200 = 80M/(16*(UBMR+1)/(UBIR+1))
     * UBIR = 15
     * 115200 = 80M/(UBMR+1)
     * UBMR = 80,000,000/115200 = 694 - 1 = 693
     * 真正的baudrate = 80,000,000/694 = 115274
     * 先设置UBIR, 后设置UBMR
     */
    uart_reg->UFCR |= (5<<7);
    uart_reg->UBIR = 15;
    uart_reg->UBMR = 693;

    /* 设置数据格式 */
    uart_reg->UCR2 |= (1<<14) | (0<<8) | (0<<6) | (1<<5) | (1<<2) | (1<<1);

    /* IMX6ULL芯片要求必须设置 */
    uart_reg->UCR3 |= (1<<2);

    /* 使能UART */
    uart_reg->UCR1 |= (1<<0);

    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hw_uart_device *uart;
    UART_Type *uart_reg;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;
    uart_reg = (UART_Type *)uart->hw_base;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        uart_reg->UCR4 &= ~(1<<0);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        uart_reg->UCR4 |= (1<<0);
        rt_hw_interrupt_umask(uart->irqno);
        break;
    }

    return RT_EOK;
}

static int uart_putc(struct rt_serial_device *serial, char c)
{
    struct hw_uart_device *uart;
    UART_Type *uart_reg;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;
    uart_reg = (UART_Type *)uart->hw_base;

    while ((uart_reg->USR2 & (1<<3)) == 0);
    uart_reg->UTXD = c;

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct hw_uart_device *uart;
    UART_Type *uart_reg;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;
    uart_reg = (UART_Type *)uart->hw_base;

    if ((uart_reg->USR2 & (1<<0)) == 0)
        ch = -1;
    else
        ch = uart_reg->URXD;

    return ch;
}

static const struct rt_uart_ops _uart_ops =
{
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
};

#ifdef RT_USING_UART0
/* UART device driver structure */
static struct hw_uart_device _uart0_device =
{
    0x02020000,  /* imx6ull uart1 phy addr */
    58,          /* rx irq */
};
static struct rt_serial_device _serial0;
#endif

#ifdef RT_USING_UART1
/* UART1 device driver structure */
static struct hw_uart_device _uart1_device =
{
    REALVIEW_UART1_BASE,
    IRQ_PBA8_UART1,
};
static struct rt_serial_device _serial1;
#endif

int rt_hw_uart_init(void)
{
    struct hw_uart_device *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART0
    _uart0_device.hw_base = (uint32_t)rt_ioremap((void*)_uart0_device.hw_base, 0x1000);
    uart = &_uart0_device;

    _serial0.ops    = &_uart_ops;
    _serial0.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&_serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
    rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, &_serial0, "uart0");
#endif

#ifdef RT_USING_UART1
    _uart1_device.hw_base = (uint32_t)rt_ioremap((void*)_uart1_device.hw_base, 0x1000);
    uart = &_uart1_device;
    _serial1.ops = &_uart_ops;
    _serial1.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&_serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart);
    /* enable Rx and Tx of UART */
    UART_CR(uart->hw_base) = (1 << 0) | (1 << 8) | (1 << 9);
    rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, &_serial1, "uart1");
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
