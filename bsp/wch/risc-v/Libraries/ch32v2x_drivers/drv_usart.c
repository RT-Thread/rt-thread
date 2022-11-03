/*
 * File      : drv_usart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2010-03-29     Bernard      remove interrupt Tx and DMA Rx mode
 * 2013-05-13     aozima       update for kehong-lingtai.
 * 2015-01-31     armink       make sure the serial transmit complete in putc()
 * 2016-05-13     armink       add DMA Rx mode
 * 2017-01-19     aubr.cool    add interrupt Tx mode
 * 2017-04-13     aubr.cool    correct Rx parity err
 * 2017-10-20     ZYH          porting to HAL Libraries(with out DMA)
 * 2017-11-15     ZYH          update to 3.0.0
 */

#include "board.h"
#include <rtdevice.h>
#include <drv_usart.h>

/*  uart driver */
struct ch32_uart
{
    USART_InitTypeDef huart;
    USART_TypeDef *USARTx;
    IRQn_Type irq;
};

static rt_err_t ch32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct ch32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct ch32_uart *)serial->parent.user_data;
    uart->huart.USART_BaudRate             = cfg->baud_rate;
    uart->huart.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;
    uart->huart.USART_Mode                 = USART_Mode_Rx|USART_Mode_Tx;

    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        uart->huart.USART_WordLength = USART_WordLength_8b;
        break;
    case DATA_BITS_9:
        uart->huart.USART_WordLength = USART_WordLength_9b;
        break;
    default:
        uart->huart.USART_WordLength = USART_WordLength_8b;
        break;
    }
    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart->huart.USART_StopBits   = USART_StopBits_1;
        break;
    case STOP_BITS_2:
        uart->huart.USART_StopBits   = USART_StopBits_2;
        break;
    default:
        uart->huart.USART_StopBits   = USART_StopBits_1;
        break;
    }
    switch (cfg->parity)
    {
    case PARITY_NONE:
        uart->huart.USART_Parity    = USART_Parity_No;
        break;
    case PARITY_ODD:
        uart->huart.USART_Parity    = USART_Parity_Odd;
        break;
    case PARITY_EVEN:
        uart->huart.USART_Parity    = USART_Parity_Even;
        break;
    default:
        uart->huart.USART_Parity     = USART_Parity_No;
        break;
    }
//    if (HAL_UART_Init(&uart->huart) != HAL_OK)
//    {
//        return RT_ERROR;
//    }

    if(uart->USARTx == USART1)
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);

//        uart->irq=USART1_IRQn;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        USART_Init(uart->USARTx,&uart->huart);
        USART_Cmd(uart->USARTx, ENABLE);
    }

    return RT_EOK;
}

static rt_err_t ch32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct ch32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct ch32_uart *)serial->parent.user_data;
    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irq);
        /* disable interrupt */
        USART_ITConfig(uart->USARTx,USART_IT_RXNE,DISABLE);
        break;
    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irq);
        /* enable interrupt */
        USART_ITConfig(uart->USARTx, USART_IT_RXNE,ENABLE);
        break;
    }
    return RT_EOK;
}

static int ch32_putc(struct rt_serial_device *serial, char c)
{
    struct ch32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct ch32_uart *)serial->parent.user_data;
//    while (__HAL_UART_GET_FLAG(&uart->huart, UART_FLAG_TXE) == RESET);
    while (USART_GetFlagStatus(uart->USARTx, USART_FLAG_TC) == RESET);
    uart->USARTx->DATAR = c;
    return 1;
}

static int ch32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct ch32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct ch32_uart *)serial->parent.user_data;
    ch = -1;
    if (USART_GetFlagStatus(uart->USARTx, USART_FLAG_RXNE) != RESET)
    {
        ch = uart->USARTx->DATAR & 0xff;
    }
    return ch;
}


rt_size_t ch32dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    return RT_EOK;
}


/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct ch32_uart *uart = (struct ch32_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);
    if (USART_GetITStatus(uart->USARTx, USART_IT_RXNE) != RESET)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        USART_ClearITPendingBit(uart->USARTx, USART_IT_RXNE);
    }
}

static const struct rt_uart_ops ch32_uart_ops =
{
    ch32_configure,
    ch32_control,
    ch32_putc,
    ch32_getc,
    ch32dma_transmit
};

#if defined(RT_USING_UART1)
/* UART1 device driver structure */
struct ch32_uart uart1;
struct rt_serial_device serial1;



void USART1_IRQHandler(void) __attribute__((interrupt()));
void USART1_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();
//    printf("int_SP:%08x\n",__get_SP());
    uart_isr(&serial1);
    /* leave interrupt */
    rt_interrupt_leave();

    FREE_INT_SP();
}
#endif /* RT_USING_UART1 */




int rt_hw_usart_init(void)
{
    struct ch32_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

//    ch32_uart_ops.configure   = ch32_configure;
//    ch32_uart_ops.control     = ch32_control;
//    ch32_uart_ops.putc        = ch32_putc;
//    ch32_uart_ops.getc        = ch32_getc;
//    ch32_uart_ops.dma_transmit= ch32dma_transmit;

#if defined(RT_USING_UART1)
    uart=&uart1;
    uart->irq=USART1_IRQn;
    uart->USARTx=USART1;

    config.baud_rate = BAUD_RATE_115200;
    serial1.ops      =  &ch32_uart_ops;
    serial1.config   =  config;


    uart->huart.USART_BaudRate             = 115200;
    uart->huart.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;
    uart->huart.USART_Mode                 = USART_Mode_Rx|USART_Mode_Tx;
    uart->huart.USART_WordLength           = USART_WordLength_8b;
    uart->huart.USART_StopBits             = USART_StopBits_1;
    uart->huart.USART_Parity               = USART_Parity_No;

    if(uart->USARTx == USART1)
    {
            GPIO_InitTypeDef GPIO_InitStructure;
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);

    //        uart->irq=USART1_IRQn;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
            USART_Init(uart->USARTx,&uart->huart);
            USART_Cmd(uart->USARTx, ENABLE);
   }

    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* RT_USING_UART1 */

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);

