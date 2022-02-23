/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-02-16     Tuber             first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_uart.h"

#ifdef BSP_USING_UART

struct uart_device
{
    struct rt_serial_device serial;
    char *name;
};

#ifdef BSP_USING_UART0
static struct uart_device uart_device0 =
{
    .name = "uart0",
};
#endif
#ifdef BSP_USING_UART1
static struct uart_device uart_device1 =
{
    .name = "uart1",
};
#endif
#ifdef BSP_USING_UART2
static struct uart_device uart_device2 =
{
    .name = "uart2",
};
#endif
#ifdef BSP_USING_UART3
static struct uart_device uart_device3 =
{
    .name = "uart3",
};
#endif

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    UINT32 x;
    UINT8V R8_UARTx_FCR = 0, R8_UARTx_LCR = 0, R8_UARTx_IER = 0, R8_UARTx_DIV = 0;
    UINT16V R16_UARTx_DL = 0;
    struct uart_device *uart_device = serial->parent.user_data;

    //设置波特率
    x = 10 * GetSysClock() / 8 / cfg->baud_rate;
    x = (x + 5) / 10;
    R16_UARTx_DL = (UINT16)x;
    //设置数据长度
    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
        //R8_UARTx_LCR |= 0x00;
        break;
    case DATA_BITS_6:
        R8_UARTx_LCR |= 0x01;
        break;
    case DATA_BITS_7:
        R8_UARTx_LCR |= 0x02;
        break;
    case DATA_BITS_8:
    default:
        R8_UARTx_LCR |= 0x03;
        break;
    }
    //设置停止位
    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        R8_UARTx_LCR |= 0x04;
        break;
    case STOP_BITS_1:
    default:
        //R8_UARTx_LCR |= 0x00;
        break;
    }
    //设置校验位
    switch (cfg->parity)
    {
    case PARITY_ODD:
        R8_UART1_LCR |= R8_LCR_PAR_EN;
        //R8_UART1_LCR |= 0x00;
        break;
    case PARITY_EVEN:
        R8_UART1_LCR |= R8_LCR_PAR_EN;
        R8_UART1_LCR |= 0x10;
        break;
    case PARITY_NONE:
    default:
        //R8_UART1_LCR &= (~R8_UART1_LCR);
        break;
    }

#ifdef BSP_USING_UART0
    if (uart_device == &uart_device0)
    {
        GPIOB_SetBits(GPIO_Pin_7);
        GPIOB_ModeCfg(GPIO_Pin_4, GPIO_ModeIN_PU);          // RXD-配置上拉输入
        GPIOB_ModeCfg(GPIO_Pin_7, GPIO_ModeOut_PP_5mA);     // TXD-配置推挽输出，注意先让IO口输出高电平
        R16_UART0_DL = R16_UARTx_DL;
        R8_UART0_FCR = (2 << 6) | RB_FCR_TX_FIFO_CLR | RB_FCR_RX_FIFO_CLR | RB_FCR_FIFO_EN;     // FIFO打开，触发点4字节
        R8_UART0_LCR = R8_UARTx_LCR;
        R8_UART0_IER = RB_IER_TXD_EN;
        R8_UART0_DIV = 1;
    }
#endif
#ifdef BSP_USING_UART1
    if (uart_device == &uart_device1)
    {
        GPIOA_SetBits(GPIO_Pin_9);
        GPIOA_ModeCfg(GPIO_Pin_8, GPIO_ModeIN_PU);          // RXD-配置上拉输入
        GPIOA_ModeCfg(GPIO_Pin_9, GPIO_ModeOut_PP_5mA);     // TXD-配置推挽输出，注意先让IO口输出高电平
        R16_UART1_DL = R16_UARTx_DL;
        R8_UART1_FCR = (2 << 6) | RB_FCR_TX_FIFO_CLR | RB_FCR_RX_FIFO_CLR | RB_FCR_FIFO_EN;     // FIFO打开，触发点4字节
        R8_UART1_LCR = R8_UARTx_LCR;
        R8_UART1_IER = RB_IER_TXD_EN;
        R8_UART1_DIV = 1;
    }
#endif
#ifdef BSP_USING_UART2
    if (uart_device == &uart_device2)
    {
        GPIOA_SetBits(GPIO_Pin_7);
        GPIOA_ModeCfg(GPIO_Pin_6, GPIO_ModeIN_PU);          // RXD-配置上拉输入
        GPIOA_ModeCfg(GPIO_Pin_7, GPIO_ModeOut_PP_5mA);     // TXD-配置推挽输出，注意先让IO口输出高电平
        R16_UART2_DL = R16_UARTx_DL;
        R8_UART2_FCR = (2 << 6) | RB_FCR_TX_FIFO_CLR | RB_FCR_RX_FIFO_CLR | RB_FCR_FIFO_EN;     // FIFO打开，触发点4字节
        R8_UART2_LCR = R8_UARTx_LCR;
        R8_UART2_IER = RB_IER_TXD_EN;
        R8_UART2_DIV = 1;
    }
#endif
#ifdef BSP_USING_UART3
    if (uart_device == &uart_device3)
    {
        GPIOA_SetBits(GPIO_Pin_5);
        GPIOA_ModeCfg(GPIO_Pin_4, GPIO_ModeIN_PU);          // RXD-配置上拉输入
        GPIOA_ModeCfg(GPIO_Pin_5, GPIO_ModeOut_PP_5mA);     // TXD-配置推挽输出，注意先让IO口输出高电平
        R16_UART3_DL = R16_UARTx_DL;
        R8_UART3_FCR = (2 << 6) | RB_FCR_TX_FIFO_CLR | RB_FCR_RX_FIFO_CLR | RB_FCR_FIFO_EN;     // FIFO打开，触发点4字节
        R8_UART3_LCR = R8_UARTx_LCR;
        R8_UART3_IER = RB_IER_TXD_EN;
        R8_UART3_DIV = 1;
    }
#endif

    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct uart_device *uart_device = serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
#ifdef BSP_USING_UART0
        if (uart_device == &uart_device0)
        {
            UART0_INTCfg(DISABLE, RB_IER_RECV_RDY);
            NVIC_EnableIRQ(UART0_IRQn);
        }
#endif
#ifdef BSP_USING_UART1
        if (uart_device == &uart_device1)
        {
            UART1_INTCfg(DISABLE, RB_IER_RECV_RDY);
            NVIC_EnableIRQ(UART1_IRQn);
        }
#endif
#ifdef BSP_USING_UART2
        if (uart_device == &uart_device2)
        {
            UART2_INTCfg(DISABLE, RB_IER_RECV_RDY);
            NVIC_EnableIRQ(UART2_IRQn);
        }
#endif
#ifdef BSP_USING_UART3
        if (uart_device == &uart_device3)
        {
            UART3_INTCfg(DISABLE, RB_IER_RECV_RDY);
            NVIC_EnableIRQ(UART3_IRQn);
        }
#endif
        break;
    case RT_DEVICE_CTRL_SET_INT:
#ifdef BSP_USING_UART0
        if (uart_device == &uart_device0)
        {
            UART0_ByteTrigCfg(UART_1BYTE_TRIG);
            UART0_INTCfg(ENABLE, RB_IER_RECV_RDY);
            NVIC_EnableIRQ(UART0_IRQn);
        }
#endif
#ifdef BSP_USING_UART1
        if (uart_device == &uart_device1)
        {
            UART1_ByteTrigCfg(UART_1BYTE_TRIG);
            UART1_INTCfg(ENABLE, RB_IER_RECV_RDY);
            NVIC_EnableIRQ(UART1_IRQn);
        }
#endif
#ifdef BSP_USING_UART2
        if (uart_device == &uart_device2)
        {
            UART2_ByteTrigCfg(UART_1BYTE_TRIG);
            UART2_INTCfg(ENABLE, RB_IER_RECV_RDY);
            NVIC_EnableIRQ(UART2_IRQn);
        }
#endif
#ifdef BSP_USING_UART3
        if (uart_device == &uart_device3)
        {
            UART3_ByteTrigCfg(UART_1BYTE_TRIG);
            UART3_INTCfg(ENABLE, RB_IER_RECV_RDY);
            NVIC_EnableIRQ(UART3_IRQn);
        }
#endif
        break;
    default:
        break;
    }

    return RT_EOK;
}

static int uart_putc(struct rt_serial_device *serial, char ch)
{
    struct uart_device *uart_device = serial->parent.user_data;

#ifdef BSP_USING_UART0
    if (uart_device == &uart_device0)
    {
        while (R8_UART0_TFC >= UART_FIFO_SIZE);
        R8_UART0_THR = ch;
    }
#endif
#ifdef BSP_USING_UART1
    if (uart_device == &uart_device1)
    {
        while (R8_UART1_TFC >= UART_FIFO_SIZE);
        R8_UART1_THR = ch;
    }
#endif
#ifdef BSP_USING_UART2
    if (uart_device == &uart_device2)
    {
        while (R8_UART2_TFC >= UART_FIFO_SIZE);
        R8_UART2_THR = ch;
    }
#endif
#ifdef BSP_USING_UART3
    if (uart_device == &uart_device3)
    {
        while (R8_UART3_TFC >= UART_FIFO_SIZE);
        R8_UART3_THR = ch;
    }
#endif

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    struct uart_device *uart_device = serial->parent.user_data;

#ifdef BSP_USING_UART0
    if (uart_device == &uart_device0)
    {
        if (R8_UART0_RFC > 0)
        {
            return R8_UART0_RBR;
        }
    }
#endif
#ifdef BSP_USING_UART1
    if (uart_device == &uart_device1)
    {
        if (R8_UART1_RFC > 0)
        {
            return R8_UART1_RBR;
        }
    }
#endif
#ifdef BSP_USING_UART2
    if (uart_device == &uart_device2)
    {
        if (R8_UART2_RFC > 0)
        {
            return R8_UART2_RBR;
        }
    }
#endif
#ifdef BSP_USING_UART3
    if (uart_device == &uart_device3)
    {
        if (R8_UART3_RFC > 0)
        {
            return R8_UART3_RBR;
        }
    }
#endif

    return -1;
}

static const struct rt_uart_ops uart_ops =
{
    .configure = uart_configure,
    .control = uart_control,
    .putc = uart_putc,
    .getc = uart_getc,
    .dma_transmit = RT_NULL,
};

void uart_isr(struct rt_serial_device *serial, UINT8 flag)
{
    switch (flag)
    {
    case UART_II_RECV_RDY:          // 数据达到设置触发点
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        break;
    case UART_II_RECV_TOUT:         // 接收超时，暂时一帧数据接收完成
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_TIMEOUT);
        break;
    case UART_II_THR_EMPTY:         // 发送缓存区空，可继续发送
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
        break;
    default:
        break;
    }
}

#ifdef BSP_USING_UART0
void UART0_IRQHandler(void)
{
    rt_interrupt_enter();

    uart_isr(&uart_device0.serial, UART0_GetITFlag());

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART1
void UART1_IRQHandler(void)
{
    rt_interrupt_enter();

    uart_isr(&uart_device1.serial, UART1_GetITFlag());

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART2
void UART2_IRQHandler(void)
{
    rt_interrupt_enter();

    uart_isr(&uart_device2.serial, UART2_GetITFlag());

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART3
void UART3_IRQHandler(void)
{
    rt_interrupt_enter();

    uart_isr(&uart_device3.serial, UART3_GetITFlag());

    rt_interrupt_leave();
}
#endif

int rt_hw_uart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART0
    uart_device0.serial.config = config;
    uart_device0.serial.ops = &uart_ops;
    rt_hw_serial_register(&uart_device0.serial, uart_device0.name,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX,
                          &uart_device0);
#endif
#ifdef BSP_USING_UART1
    uart_device1.serial.config = config;
    uart_device1.serial.ops = &uart_ops;
    rt_hw_serial_register(&uart_device1.serial, uart_device1.name,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX,
                          &uart_device1);
#endif
#ifdef BSP_USING_UART2
    uart_device2.serial.config = config;
    uart_device2.serial.ops = &uart_ops;
    rt_hw_serial_register(&uart_device2.serial, uart_device2.name,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX,
                          &uart_device2);
#endif
#ifdef BSP_USING_UART3
    uart_device3.serial.config = config;
    uart_device3.serial.ops = &uart_ops;
    rt_hw_serial_register(&uart_device3.serial, uart_device3.name,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX,
                          &uart_device3);
#endif

    return RT_EOK;
}
#endif /* BSP_USING_UART */
