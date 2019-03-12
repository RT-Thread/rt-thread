/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-11-15     bright       the first version
 */

#include <HAL_device.h>
#include <rtdevice.h>
#include "drv_uart.h"

/* UART1 */
#define UART1_GPIO_TX			GPIO_Pin_9
#define UART1_GPIO_TX_SOURCE	GPIO_PinSource9
#define UART1_GPIO_RX			GPIO_Pin_10
#define UART1_GPIO_RX_SOURCE	GPIO_PinSource10
#define UART1_GPIO_AF			GPIO_AF_1
#define UART1_GPIO				GPIOA

/* UART2 */
#define UART2_GPIO_TX			GPIO_Pin_2
#define UART2_GPIO_TX_SOURCE	GPIO_PinSource2
#define UART2_GPIO_RX			GPIO_Pin_3
#define UART2_GPIO_RX_SOURCE	GPIO_PinSource3
#define UART2_GPIO_AF			GPIO_AF_1
#define UART2_GPIO				GPIOA

/* uart driver */
struct mm32_uart
{
    UART_TypeDef* uart_device;
    IRQn_Type irq;
};

static rt_err_t mm32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct mm32_uart* uart;
    UART_InitTypeDef UART_InitStructure;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct mm32_uart *)serial->parent.user_data;

    UART_InitStructure.UART_BaudRate = cfg->baud_rate;

    if (cfg->data_bits == DATA_BITS_8)
        UART_InitStructure.UART_WordLength = UART_WordLength_8b;

    if (cfg->stop_bits == STOP_BITS_1)
        UART_InitStructure.UART_StopBits = UART_StopBits_1;
    else if (cfg->stop_bits == STOP_BITS_2)
        UART_InitStructure.UART_StopBits = UART_StopBits_2;

    UART_InitStructure.UART_Parity = UART_Parity_No;
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
    UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;
    UART_Init(uart->uart_device, &UART_InitStructure);

    /* Enable UART */
    UART_Cmd(uart->uart_device, ENABLE);
    /* enable interrupt */
    UART_ITConfig(uart->uart_device, UART_IT_RXIEN, ENABLE);

    return RT_EOK;
}

static rt_err_t mm32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct mm32_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct mm32_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irq);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irq);
        break;
    }

    return RT_EOK;
}

static int mm32_putc(struct rt_serial_device *serial, char c)
{
    struct mm32_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct mm32_uart *)serial->parent.user_data;

    //UART_ClearFlag(uart->uart_device,UART_FLAG_TXEPT);
    while((uart->uart_device->CSR&UART_CSR_TXC)==0);
    uart->uart_device->TDR = c;
    //while (!(uart->uart_device->ISR & UART_FLAG_TXEPT));

    return 1;
}

static int mm32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct mm32_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct mm32_uart *)serial->parent.user_data;

    ch = -1;
    if (uart->uart_device->CSR & UART_FLAG_RXAVL)
    {
        ch = uart->uart_device->RDR & 0xff;
    }

    return ch;
}

static const struct rt_uart_ops mm32_uart_ops =
{
    mm32_configure,
    mm32_control,
    mm32_putc,
    mm32_getc,
};

#if defined(BSP_USING_UART1)
/* UART1 device driver structure */
struct mm32_uart uart1 =
{
    UART1,
    UART1_IRQn,
};
struct rt_serial_device serial1;

void UART1_IRQHandler(void)
{
    struct mm32_uart* uart;

    uart = &uart1;

    /* enter interrupt */
    rt_interrupt_enter();
    if(UART_GetITStatus(uart->uart_device, UART_IT_RXIEN) != RESET)
    {
        UART_ClearITPendingBit(uart->uart_device, UART_IT_RXIEN);
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    }
    if (UART_GetITStatus(uart->uart_device, UART_IT_TXIEN) != RESET)
    {
        /* clear interrupt */
        UART_ClearITPendingBit(uart->uart_device, UART_IT_TXIEN);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
/* UART2 device driver structure */
struct mm32_uart uart2 =
{
    UART2,
    UART2_IRQn,
};
struct rt_serial_device serial2;

void UART2_IRQHandler(void)
{
    struct mm32_uart* uart;

    uart = &uart2;

    /* enter interrupt */
    rt_interrupt_enter();
    if(UART_GetITStatus(uart->uart_device, UART_IT_RXIEN) != RESET)
    {
        UART_ClearITPendingBit(uart->uart_device, UART_IT_RXIEN);
        rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
    }
    if (UART_GetITStatus(uart->uart_device, UART_IT_TXIEN) != RESET)
    {
        /* clear interrupt */
        UART_ClearITPendingBit(uart->uart_device, UART_IT_TXIEN);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */


#ifdef BSP_USING_UART1
static void UART1PINconfigStepA(void){
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE);	//使能UART1
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);  //开启GPIOA时钟
    //UART 初始化设置
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);    
    
}

static void UART1PINconfigStepB(void){
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    
    //UART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
    
    //UART1_RX	  GPIOA.10初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  
    
}
#endif
#ifdef BSP_USING_UART2
static void UART2PINconfigStepA(void){
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, ENABLE);	//使能UART1
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);  //开启GPIOA时钟
    //UART 初始化设置
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_1);    
    
}

static void UART2PINconfigStepB(void){
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    
    //UART2_TX   GPIOA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.2
    
    //UART2_RX	  GPIOA.3初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.3
    
}
#endif
static void NVIC_Configuration(struct mm32_uart* uart)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable the UART Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = uart->irq;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

int rt_hw_uart_init(void)
{
    struct mm32_uart* uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART1
    UART1PINconfigStepA();
    uart = &uart1;
    config.baud_rate = BAUD_RATE_115200;

    serial1.ops    = &mm32_uart_ops;
    serial1.config = config;

    NVIC_Configuration(&uart1);

    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
    UART1PINconfigStepB();
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
    UART2PINconfigStepA();
    uart = &uart2;

    config.baud_rate = BAUD_RATE_115200;
    serial2.ops    = &mm32_uart_ops;
    serial2.config = config;

    NVIC_Configuration(&uart2);

    /* register UART1 device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
    UART2PINconfigStepB();                                
#endif /* BSP_USING_UART2 */

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);