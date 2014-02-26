/*
 * File      : usart.c
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
 */

#include "stm32f10x.h"
#include "usart.h"
#include "board.h"

#include <rtdevice.h>

/* USART1 */
#define UART1_TX_PIN		GPIO_Pin_9
#define UART1_TX_GPIO		GPIOA
#define UART1_RX_PIN		GPIO_Pin_10
#define UART1_RX_GPIO		GPIOA

#define UART1_CTS_PIN		((uint16_t)0x0000)// cts is disable
#define UART1_CTS_GPIO		((GPIO_TypeDef *)0x00000000)
#define UART1_RTS_PIN		((uint16_t)0x0000)// rts is disable
#define UART1_RTS_GPIO		((GPIO_TypeDef *)0x00000000)

#define UART1_REMAP         (((uint32_t)0x00000000))// remap is disable

/* USART2 */
#define UART2_TX_PIN		GPIO_Pin_2
#define UART2_TX_GPIO		GPIOA
#define UART2_RX_PIN		GPIO_Pin_3
#define UART2_RX_GPIO		GPIOA

#define UART2_CTS_PIN		((uint16_t)0x0000)// cts is disable
#define UART2_CTS_GPIO		((GPIO_TypeDef *)0x00000000)
#define UART2_RTS_PIN		((uint16_t)0x0000)// rts is disable
#define UART2_RTS_GPIO		((GPIO_TypeDef *)0x00000000)

#define UART2_REMAP         (((uint32_t)0x00000000))// remap is disable

/* USART3_REMAP[1:0] = 11 */
#define UART3_TX_PIN		GPIO_Pin_8
#define UART3_TX_GPIO		GPIOD
#define UART3_RX_PIN		GPIO_Pin_9
#define UART3_RX_GPIO		GPIOD

#define UART3_CTS_PIN		((uint16_t)0x0000)// cts is disable
#define UART3_CTS_GPIO		((GPIO_TypeDef *)0x00000000)
#define UART3_RTS_PIN		((uint16_t)0x0000)// rts is disable
#define UART3_RTS_GPIO		((GPIO_TypeDef *)0x00000000)

#define UART3_REMAP         GPIO_FullRemap_USART3

/* USART4 */
#define UART4_TX_PIN		GPIO_Pin_10
#define UART4_TX_GPIO		GPIOC
#define UART4_RX_PIN		GPIO_Pin_11
#define UART4_RX_GPIO		GPIOC

#define UART4_CTS_PIN		((uint16_t)0x0000)// cts is disable
#define UART4_CTS_GPIO		((GPIO_TypeDef *)0x00000000)
#define UART4_RTS_PIN		((uint16_t)0x0000)// rts is disable
#define UART4_RTS_GPIO		((GPIO_TypeDef *)0x00000000)

#define UART4_REMAP         (((uint32_t)0x00000000))// remap is disable

/* USART5 */
#define UART5_TX_PIN		GPIO_Pin_12
#define UART5_TX_GPIO		GPIOC
#define UART5_RX_PIN		GPIO_Pin_2
#define UART5_RX_GPIO		GPIOD

#define UART5_CTS_PIN		((uint16_t)0x0000)// cts is disable
#define UART5_CTS_GPIO		((GPIO_TypeDef *)0x00000000)
#define UART5_RTS_PIN		((uint16_t)0x0000)// rts is disable
#define UART5_RTS_GPIO		((GPIO_TypeDef *)0x00000000)

#define UART4_REMAP         (((uint32_t)0x00000000))// remap is disable

/* STM32 uart driver */
struct stm32_uart
{
    USART_TypeDef* uart_device;
    IRQn_Type irq;
    
    uint16_t uart_tx_pin;    
    GPIO_TypeDef *uart_tx_gpio;

    uint16_t uart_rx_pin;
    GPIO_TypeDef *uart_rx_gpio;
    
    uint16_t uart_cts_pin;
    GPIO_TypeDef *uart_cts_gpio;
    
    uint16_t uart_rts_pin;
    GPIO_TypeDef *uart_rts_gpio;

    uint32_t uart_remap;

};

static rt_err_t stm32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct stm32_uart* uart;
    USART_InitTypeDef USART_InitStructure;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct stm32_uart *)serial->parent.user_data;
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = cfg->baud_rate;

    if (cfg->data_bits == DATA_BITS_8)
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;

    if (cfg->stop_bits == STOP_BITS_1)
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
    else if (cfg->stop_bits == STOP_BITS_2)
        USART_InitStructure.USART_StopBits = USART_StopBits_2;

    if (cfg->parity == PARITY_NONE)
        USART_InitStructure.USART_Parity = USART_Parity_No;
    else if (cfg->parity == PARITY_EVEN)
        USART_InitStructure.USART_Parity = USART_Parity_Even;
    else if (cfg->parity == PARITY_ODD)
        USART_InitStructure.USART_Parity = USART_Parity_Odd;
    
    if (cfg->hw_control == HW_CONTROL_NONE)
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    else if (cfg->hw_control == HW_CONTROL_RTS_CTS)
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;

    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(uart->uart_device, &USART_InitStructure);

    /* Enable USART */
    USART_Cmd(uart->uart_device, ENABLE);
    /* enable interrupt */
    USART_ITConfig(uart->uart_device, USART_IT_RXNE, ENABLE);

    return RT_EOK;
}

static rt_err_t stm32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct stm32_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct stm32_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        UART_DISABLE_IRQ(uart->irq);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        UART_ENABLE_IRQ(uart->irq);
        break;
    }

    return RT_EOK;
}

static int stm32_putc(struct rt_serial_device *serial, char c)
{
    struct stm32_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct stm32_uart *)serial->parent.user_data;

    while (!(uart->uart_device->SR & USART_FLAG_TXE));
    uart->uart_device->DR = c;

    return 1;
}

static int stm32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct stm32_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct stm32_uart *)serial->parent.user_data;

    ch = -1;
    if (uart->uart_device->SR & USART_FLAG_RXNE)
    {
        ch = uart->uart_device->DR & 0xff;
    }

    return ch;
}

static const struct rt_uart_ops stm32_uart_ops =
{
    stm32_configure,
    stm32_control,
    stm32_putc,
    stm32_getc,
};

__STATIC_INLINE void serial_device_isr(struct rt_serial_device *serial)
{
    volatile int ch = 0;
	struct stm32_uart *uart = serial->parent.user_data;

	/* process uart error */
	if(uart->uart_device->SR & (USART_FLAG_ORE | USART_FLAG_NE | USART_FLAG_FE | USART_FLAG_PE))
	{
		ch = uart->uart_device->DR; // invalid read
		while (uart->uart_device->SR & USART_FLAG_RXNE)
		{
            ch = uart->uart_device->DR; // invalid read
		}
	}
	/* process usart receive */
	if (uart->uart_device->SR & USART_FLAG_RXNE)
	{
        rt_hw_serial_isr(serial);//auto clear interrupt flag
	}
    /* process usart send */
    if (uart->uart_device->SR & USART_IT_TC)
    {
        /* clear interrupt */
        uart->uart_device->SR = ~((uint16_t)0x01 << (uint16_t)(USART_IT_TC >> 0x08));
    }
}

#if defined(RT_USING_UART1)
/* UART1 device driver structure */
struct serial_ringbuffer uart1_int_rx;
#define UART1_POOL_SIZE 64
rt_uint8_t uart1_pool[UART1_POOL_SIZE];
struct stm32_uart uart1 =
{
    USART1,
    USART1_IRQn,

    UART1_TX_PIN,
    UART1_TX_GPIO,
    UART1_RX_PIN,
    UART1_RX_GPIO,

    UART1_CTS_PIN,
    UART1_CTS_GPIO,
    UART1_RTS_PIN,
    UART1_RTS_GPIO,

    UART1_REMAP,
};
struct rt_serial_device serial1;

void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    serial_device_isr(&serial1);
    
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_USING_UART1 */

#if defined(RT_USING_UART2)
/* UART2 device driver structure */
struct serial_ringbuffer uart2_int_rx;
#define UART2_POOL_SIZE 64
rt_uint8_t uart2_pool[UART2_POOL_SIZE];
struct stm32_uart uart2 =
{
    USART2,
    USART2_IRQn,

    UART2_TX_PIN,
    UART2_TX_GPIO,
    UART2_RX_PIN,
    UART2_RX_GPIO,

    UART2_CTS_PIN,
    UART2_CTS_GPIO,
    UART2_RTS_PIN,
    UART2_RTS_GPIO,

    UART2_REMAP,

};
struct rt_serial_device serial2;

void USART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    serial_device_isr(&serial2);
    
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_USING_UART2 */

#if defined(RT_USING_UART3)
/* UART3 device driver structure */
struct serial_ringbuffer uart3_int_rx;
#define UART3_POOL_SIZE 64
rt_uint8_t uart3_pool[UART3_POOL_SIZE];
struct stm32_uart uart3 =
{
    USART3,
    USART3_IRQn,

    UART3_TX_PIN,
    UART3_TX_GPIO,
    UART3_RX_PIN,
    UART3_RX_GPIO,

    UART3_CTS_PIN,
    UART3_CTS_GPIO,
    UART3_RTS_PIN,
    UART3_RTS_GPIO,

    UART3_REMAP,
};
struct rt_serial_device serial3;

void USART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    serial_device_isr(&serial3);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_USING_UART3 */

#if defined(RT_USING_UART4)
/* UART4 device driver structure */
struct serial_ringbuffer uart4_int_rx;
#define UART4_POOL_SIZE 64
rt_uint8_t uart4_pool[UART4_POOL_SIZE];
struct stm32_uart uart4 =
{
    UART4,
    UART4_IRQn,

    UART4_TX_PIN,
    UART4_TX_GPIO,
    UART4_RX_PIN,
    UART4_RX_GPIO,

    UART4_CTS_PIN,
    UART4_CTS_GPIO,
    UART4_RTS_PIN,
    UART4_RTS_GPIO,

    UART4_REMAP,
};
struct rt_serial_device serial4;

void UART4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    serial_device_isr(&serial4);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_USING_UART4 */

#if defined(RT_USING_UART5)
/* UART5 device driver structure */
struct serial_ringbuffer uart5_int_rx;
#define UART5_POOL_SIZE 64
rt_uint8_t uart5_pool[UART5_POOL_SIZE];
struct stm32_uart uart5 =
{
    UART5,
    UART5_IRQn,

    UART5_TX_PIN,
    UART5_TX_GPIO,
    UART5_RX_PIN,
    UART5_RX_GPIO,

    UART5_CTS_PIN,
    UART5_CTS_GPIO,
    UART5_RTS_PIN,
    UART5_RTS_GPIO,

    UART5_REMAP,
};
struct rt_serial_device serial5;

void UART5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    serial_device_isr(&serial5);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_USING_UART5 */

#define GPIO_RCC_ENABLE(x)                                          \
do{                                                                 \
    if (IS_GPIO_ALL_PERIPH(x))                                      \
    {                                                               \
        if ((x) == GPIOA)                                           \
        {                                                           \
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);    \
        }                                                           \
        if ((x) == GPIOB)                                           \
        {                                                           \
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);    \
        }                                                           \
        if ((x) == GPIOC)                                           \
        {                                                           \
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);    \
        }                                                           \
        if ((x) == GPIOD)                                           \
        {                                                           \
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);    \
        }                                                           \
        if ((x) == GPIOE)                                           \
        {                                                           \
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);    \
        }                                                           \
        if ((x) == GPIOF)                                           \
        {                                                           \
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);   \
        }                                                           \
        if ((x) == GPIOG)                                           \
        {                                                           \
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);   \
        }                                                           \
    }                                                               \
}while(0)

#define UART_RCC_ENABLE(x)                                          \
do{                                                                 \
    if (IS_USART_ALL_PERIPH(x))                                      \
    {                                                               \
        if ((x) == USART1)                                           \
        {                                                           \
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);    \
        }                                                           \
        if ((x) == USART2)                                           \
        {                                                           \
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);    \
        }                                                           \
        if ((x) == USART3)                                           \
        {                                                           \
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);    \
        }                                                           \
        if ((x) == UART4)                                           \
        {                                                           \
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);    \
        }                                                           \
        if ((x) == UART5)                                           \
        {                                                           \
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);    \
        }                                                           \
    }                                                               \
}while(0)

static void RCC_Configuration(struct stm32_uart* uart)
{
    /* Enable UART GPIO clocks */
    GPIO_RCC_ENABLE(uart->uart_tx_gpio);
    GPIO_RCC_ENABLE(uart->uart_rx_gpio);
    GPIO_RCC_ENABLE(uart->uart_cts_gpio);
    GPIO_RCC_ENABLE(uart->uart_rts_gpio);
    /* Enable UART GPIO AF clocks */
    if (IS_GPIO_REMAP(uart->uart_remap))
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        GPIO_PinRemapConfig(uart->uart_remap, ENABLE);
    }
    /* Enable UART clock */
    UART_RCC_ENABLE(uart->uart_device);
}

static void GPIO_Configuration(struct stm32_uart* uart)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    /* Configure USART Rx/tx PIN */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = uart->uart_rx_pin;
    GPIO_Init(uart->uart_rx_gpio, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = uart->uart_tx_pin;
    GPIO_Init(uart->uart_tx_gpio, &GPIO_InitStructure);
    /* Configure USART RTS/CTS PIN */
    if (IS_GPIO_ALL_PERIPH(uart->uart_cts_gpio) && 
        IS_GPIO_ALL_PERIPH(uart->uart_rts_gpio) && 
        IS_GPIO_PIN(uart->uart_cts_pin) && 
        IS_GPIO_PIN(uart->uart_rts_pin))
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Pin = uart->uart_cts_pin;
        GPIO_Init(uart->uart_cts_gpio, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Pin = uart->uart_rts_pin;
        GPIO_Init(uart->uart_rts_gpio, &GPIO_InitStructure);
    }
}

static void NVIC_Configuration(struct stm32_uart* uart)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable the USART Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = uart->irq;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void rt_hw_usart_init(void)
{
    struct stm32_uart* uart;
    struct rt_serial_device *serial;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART1
    uart = &uart1;
    serial = &serial1;
    
    uart1_int_rx.pool = uart1_pool;
    uart1_int_rx.size = UART1_POOL_SIZE;
    
    config.baud_rate = BAUD_RATE_115200;

    serial->ops    = &stm32_uart_ops;
    serial->int_rx = &uart1_int_rx;
    serial->config = config;
    
    RCC_Configuration(uart);
    GPIO_Configuration(uart);
    NVIC_Configuration(uart);

    /* register UART1 device */
    rt_hw_serial_register(serial, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          uart);
#endif /* RT_USING_UART1 */

#ifdef RT_USING_UART2
    uart = &uart2;
    serial = &serial2;
    
    uart2_int_rx.pool = uart2_pool;
    uart2_int_rx.size = UART2_POOL_SIZE;

    config.baud_rate = BAUD_RATE_115200;

    serial->ops    = &stm32_uart_ops;
    serial->int_rx = &uart2_int_rx;
    serial->config = config;
    
    RCC_Configuration(uart);
    GPIO_Configuration(uart);
    NVIC_Configuration(uart);

    /* register UART2 device */
    rt_hw_serial_register(serial, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* RT_USING_UART2 */

#ifdef RT_USING_UART3
    uart = &uart3;
    serial = &serial3;
    
    uart3_int_rx.pool = uart3_pool;
    uart3_int_rx.size = UART3_POOL_SIZE;

    config.baud_rate = BAUD_RATE_115200;

    serial->ops    = &stm32_uart_ops;
    serial->int_rx = &uart3_int_rx;
    serial->config = config;
    
    RCC_Configuration(uart);
    GPIO_Configuration(uart);
    NVIC_Configuration(uart);

    /* register UART3 device */
    rt_hw_serial_register(serial, "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* RT_USING_UART3 */

#ifdef RT_USING_UART4
    uart = &uart4;
    serial = &serial4;
    
    uart4_int_rx.pool = uart4_pool;
    uart4_int_rx.size = UART4_POOL_SIZE;

    config.baud_rate = BAUD_RATE_115200;

    serial->ops    = &stm32_uart_ops;
    serial->int_rx = &uart4_int_rx;
    serial->config = config;
    
    RCC_Configuration(uart);
    GPIO_Configuration(uart);
    NVIC_Configuration(uart);

    /* register UART4 device */
    rt_hw_serial_register(serial, "uart4",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* RT_USING_UART4 */

#ifdef RT_USING_UART5
    uart = &uart5;
    serial = &serial5;
    
    uart5_int_rx.pool = uart5_pool;
    uart5_int_rx.size = UART5_POOL_SIZE;

    config.baud_rate = BAUD_RATE_115200;

    serial->ops    = &stm32_uart_ops;
    serial->int_rx = &uart5_int_rx;
    serial->config = config;
    
    RCC_Configuration(uart);
    GPIO_Configuration(uart);
    NVIC_Configuration(uart);

    /* register UART5 device */
    rt_hw_serial_register(serial, "uart5",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* RT_USING_UART5 */
}


/* uart device test */
#ifdef RT_USING_FINSH
#include <finsh.h>

#if (defined(RT_USING_UART1) || defined(RT_USING_UART2) || defined(RT_USING_UART3) || defined(RT_USING_UART4) || defined(RT_USING_UART5))
void uart_rw(const char *name, rt_int8_t cmd, const char *str)
{
    rt_device_t uart;
    uart = rt_device_find(name);
    if (uart != RT_NULL)
    {
        if (uart->open_flag == RT_DEVICE_OFLAG_CLOSE)
        {
            rt_device_open(uart, RT_DEVICE_OFLAG_RDWR);
        }
        if (cmd == 0)
        {
            rt_int8_t temp[20];
            memset(temp, '\0', 20);
            rt_device_read(uart,0,(void *)temp,20);
            rt_kprintf("%s", temp);
        }
        else
        {
            rt_kprintf("%s, %d", str, strlen(str));
            rt_device_write(uart,0,str,strlen(str));
        }
        //rt_device_close(uart);
    }
    else
    {
        rt_kprintf("device %s is not exist!\n", name);
    }
}
FINSH_FUNCTION_EXPORT(uart_rw, set uart[name 0 xxx] for read.)
#endif

#endif
