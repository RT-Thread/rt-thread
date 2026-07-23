/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-16     CYFS         first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_usart_v2.h"
#ifdef RT_USING_SERIAL_V2
#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && !defined(BSP_USING_UART7) && !defined(BSP_USING_UART8) && !defined(BSP_USING_LPUART1)
#error "Please define at least one BSP_USING_UARTx"
/* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

/******************************* declare ****************************************************************************************** */
enum
{
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
#ifdef BSP_USING_UART2
    UART2_INDEX,
#endif
#ifdef BSP_USING_UART3
    UART3_INDEX,
#endif
#ifdef BSP_USING_UART4
    UART4_INDEX,
#endif
#ifdef BSP_USING_UART5
    UART5_INDEX,
#endif
#ifdef BSP_USING_UART6
    UART6_INDEX,
#endif
#ifdef BSP_USING_UART7
    UART7_INDEX,
#endif
#ifdef BSP_USING_UART8
    UART8_INDEX,
#endif
};



struct DMA_HandleTypeDef
{
    DMA_Channel_TypeDef           *Instance; /* DMA registers base address */
    struct UART_HandleTypeDef *Parent;
    DMA_InitTypeDef               Init;     /* DMA initialization parameters */
    rt_uint32_t                dma_rcc;
    IRQn_Type                  dma_irq;
    void (*DMA_ITC_Callback)(struct UART_HandleTypeDef *huart) ;/* DMA transfer complete callback */
    void (*DMA_IE_Callback)(void);  /* DMA error complete callback */
};

struct UART_HandleTypeDef
{
    USART_TypeDef             *Instance; /*!< UART registers base address        */
    USART_InitTypeDef            Init;     /*!< UART communication parameters      */
    struct DMA_HandleTypeDef *HDMA_Tx;  /*!< UART Tx DMA handle parameters */
    struct DMA_HandleTypeDef *HDMA_Rx;  /*!< UART Rx DMA handle parameters */
};

struct ch32_uart_config
{
    const char   *name;
    USART_TypeDef *Instance;
    rt_uint32_t   rcc;
    IRQn_Type     irq_type;
    GPIO_TypeDef  *tx_port;
    uint16_t      tx_pin;
    GPIO_TypeDef  *rx_port;
    uint16_t      rx_pin;
};

struct ch32_uart
{
    struct UART_HandleTypeDef handle;
    struct ch32_uart_config   *config;
#ifdef RT_SERIAL_USING_DMA
    struct
    {
        struct DMA_HandleTypeDef handle;
        rt_size_t                remaining_cnt;
    } dma_rx;
    struct
    {
        struct DMA_HandleTypeDef handle;
    } dma_tx;
#endif
    rt_uint16_t             uart_dma_flag;
    struct rt_serial_device serial;
};
/********************************************************************************************************************************** */
/******************************* funtion ****************************************************************************************** */
static void     ch32_uart_get_config(void);
static rt_err_t ch32_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static void     NVIC_Set(IRQn_Type irq, FunctionalState state);
#ifdef RT_SERIAL_USING_DMA
static void dma_recv_isr(struct rt_serial_device *serial, rt_uint8_t isr_flag);
static void ch32_uart_dma_config(struct rt_serial_device *serial, rt_ubase_t flag);
void HAL_UART_TxCpltCallback(struct UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(struct UART_HandleTypeDef *huart);
static void HAL_DMA_IRQHandler(struct DMA_HandleTypeDef *hdma);
#endif
static void GPIOInit(GPIO_TypeDef* GPIOx, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, uint16_t Pin);
/********************************************************************************************************************************** */
/******************************** value ******************************************************************************************* */
static struct ch32_uart_config uart_config[] =
{
#ifdef BSP_USING_UART1
    {
        .name = "uart1",
        .Instance = USART1,
        .rcc = RCC_APB2Periph_USART1,
        .irq_type = USART1_IRQn,
        .tx_port  = GPIOA,
        .tx_pin   = GPIO_Pin_9,
        .rx_port  = GPIOA,
        .rx_pin   = GPIO_Pin_10
    },
#endif
#ifdef BSP_USING_UART2
    {
        .name = "uart2",
        .Instance = USART2,
        .rcc = RCC_APB1Periph_USART2,
        .irq_type = USART2_IRQn,
        .tx_port  = GPIOA,
        .tx_pin   = GPIO_Pin_2,
        .rx_port  = GPIOA,
        .rx_pin   = GPIO_Pin_3
    },
#endif
#ifdef BSP_USING_UART3
    {
        .name = "uart3",
        .Instance = USART3,
        .rcc = RCC_APB1Periph_USART3,
        .irq_type = USART3_IRQn,
        .tx_port  = GPIOB,
        .tx_pin   = GPIO_Pin_10,
        .rx_port  = GPIOB,
        .rx_pin   = GPIO_Pin_11,
    },
#endif
#ifdef BSP_USING_UART4
    {
        .name = "uart4",
        .Instance = UART4,
        .rcc = RCC_APB1Periph_UART4,
        .irq_type = UART4_IRQn,
        .tx_port  = GPIOC,
        .tx_pin   = GPIO_Pin_10,
        .rx_port  = GPIOC,
        .rx_pin   = GPIO_Pin_11,
    },
#endif
#ifdef BSP_USING_UART5
    {
        .name = "uart5",
        .Instance = UART5,
        .rcc = RCC_APB1Periph_UART5,
        .irq_type = UART5_IRQn,
        .tx_port  = GPIOC,
        .tx_pin   = GPIO_Pin_12,
        .rx_port  = GPIOD,
        .rx_pin   = GPIO_Pin_2,
    },
#endif
#ifdef BSP_USING_UART6
    {
        .name = "uart6",
        .Instance = UART6,
        .rcc = RCC_APB1Periph_UART6,
        .irq_type = UART6_IRQn,
        .tx_port  = GPIOC,
        .tx_pin   = GPIO_Pin_0,
        .rx_port  = GPIOC,
        .rx_pin   = GPIO_Pin_1,

    },
#endif
#ifdef BSP_USING_UART7
    {
        .name = "uart7",
        .Instance = UART7,
        .rcc = RCC_APB1Periph_UART7,
        .irq_type = UART7_IRQn,
        .tx_port  = GPIOC,
        .tx_pin   = GPIO_Pin_2,
        .rx_port  = GPIOC,
        .rx_pin   = GPIO_Pin_3,
    },
#endif
#ifdef BSP_USING_UART8
    {
        .name = "uart8",
        .Instance = UART8,
        .rcc = RCC_APB1Periph_UART8,
        .irq_type = UART8_IRQn,
        .tx_port  = GPIOC,
        .tx_pin   = GPIO_Pin_4,
        .rx_port  = GPIOC,
        .rx_pin   = GPIO_Pin_5,
    },
#endif
};
static struct ch32_uart uart_obj[sizeof(uart_config) / sizeof(struct ch32_uart_config)];
/********************************************************************************************************************************** */

static void GPIOInit(GPIO_TypeDef* GPIOx, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, uint16_t Pin)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Enable the GPIO Clock */
    if (GPIOx == GPIOA)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    }
    else if (GPIOx == GPIOE)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    }
    /* Configure the GPIO pin */
    GPIO_InitStructure.GPIO_Pin   = Pin;
    GPIO_InitStructure.GPIO_Mode  = mode;
    GPIO_InitStructure.GPIO_Speed = speed;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}

static void ch32_uart_init(struct ch32_uart_config *uart)
{
    if (uart->Instance==USART1)
    {
        RCC_APB2PeriphClockCmd(uart->rcc, ENABLE);
    }
    else
    {
        RCC_APB1PeriphClockCmd(uart->rcc, ENABLE);
    }
    NVIC_SetPriority(uart->irq_type, 0);
    GPIOInit(uart->rx_port, GPIO_Mode_IPU, GPIO_Speed_50MHz, uart->rx_pin);
    GPIOInit(uart->tx_port, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, uart->tx_pin);
}

static rt_err_t ch32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct ch32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = rt_container_of(serial, struct ch32_uart, serial);
    ch32_uart_init(uart->config);
    uart->handle.Init.USART_BaudRate = cfg->baud_rate;

    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        uart->handle.Init.USART_WordLength = USART_WordLength_8b;
        break;
    case DATA_BITS_9:
        uart->handle.Init.USART_WordLength = USART_WordLength_9b;
        break;

    default:
        uart->handle.Init.USART_WordLength = USART_WordLength_8b;
        ;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart->handle.Init.USART_StopBits = USART_StopBits_1;
        break;
    case STOP_BITS_2:
        uart->handle.Init.USART_StopBits = USART_StopBits_0_5;
        break;
    case STOP_BITS_3:
        uart->handle.Init.USART_StopBits = USART_StopBits_2;
        break;
    case STOP_BITS_4:
        uart->handle.Init.USART_StopBits = USART_StopBits_1_5;
        break;
    default:
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        uart->handle.Init.USART_Parity = USART_Parity_Odd;
        break;
    case PARITY_EVEN:
        uart->handle.Init.USART_Parity = USART_Parity_Even;
        break;
    case PARITY_NONE:
        uart->handle.Init.USART_Parity = USART_Parity_No;
        break;
    default:
        break;
    }

    switch (cfg->flowcontrol)
    {
    case RT_SERIAL_FLOWCONTROL_NONE:
        uart->handle.Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        break;
    case RT_SERIAL_FLOWCONTROL_CTSRTS:
        uart->handle.Init.USART_HardwareFlowControl = USART_HardwareFlowControl_CTS;
        break;
    default:
        uart->handle.Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        break;
    }
    uart->handle.Init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_DeInit(uart->handle.Instance);
    USART_Init(uart->handle.Instance, &uart->handle.Init);
    USART_Cmd(uart->handle.Instance, ENABLE);
#ifdef RT_SERIAL_USING_DMA
    uart->dma_rx.remaining_cnt = serial->config.dma_ping_bufsz;
#endif
    return RT_EOK;
}

/**
 * @brief  Configures the nested vectored interrupt controller.
 */
static void NVIC_Set(IRQn_Type irq, FunctionalState state)
{
    if (state == ENABLE)
    {
        NVIC_SetPriority(irq, 0);
        NVIC_EnableIRQ(irq);
    }
    else if (state == DISABLE)
    {
        NVIC_DisableIRQ(irq);
    }
}

static rt_err_t ch32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct ch32_uart *uart;
    rt_ubase_t       ctrl_arg = (rt_ubase_t)arg;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ch32_uart, serial);
    if (ctrl_arg & (RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_RX_NON_BLOCKING))
    {
        if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_RX)
            ctrl_arg = RT_DEVICE_FLAG_DMA_RX;
        else
            ctrl_arg = RT_DEVICE_FLAG_INT_RX;
    }
    else if (ctrl_arg & (RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING))
    {
        if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_TX)
            ctrl_arg = RT_DEVICE_FLAG_DMA_TX;
        else
            ctrl_arg = RT_DEVICE_FLAG_INT_TX;
    }

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        NVIC_Set(uart->config->irq_type, DISABLE);
        if (ctrl_arg & RT_DEVICE_FLAG_INT_RX)
        {
            USART_ITConfig(uart->handle.Instance, USART_IT_RXNE, DISABLE);
        }

        if (ctrl_arg & RT_DEVICE_FLAG_INT_TX)
        {
            USART_ITConfig(uart->handle.Instance, USART_IT_TC, DISABLE);

        }
#ifdef RT_SERIAL_USING_DMA
        if (ctrl_arg & RT_DEVICE_FLAG_DMA_RX)
        {
            NVIC_Set(uart->dma_rx.handle.dma_irq, DISABLE);
            USART_ITConfig(uart->handle.Instance, USART_IT_IDLE, DISABLE);
            DMA_DeInit(uart->dma_rx.handle.Instance);

        }
        else if (ctrl_arg & RT_DEVICE_FLAG_DMA_TX)
        {
            NVIC_Set(uart->dma_tx.handle.dma_irq, DISABLE);
            USART_ITConfig(uart->handle.Instance, USART_IT_TC, DISABLE);
            USART_ClearFlag(uart->handle.Instance, USART_FLAG_TC);
            DMA_DeInit(uart->dma_tx.handle.Instance);
        }
#endif
        break;

    case RT_DEVICE_CTRL_CONFIG:
#ifdef RT_SERIAL_USING_DMA
        if (ctrl_arg & (RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX))
        {
            ch32_uart_dma_config(serial, ctrl_arg);

        }
        else
            ch32_control(serial, RT_DEVICE_CTRL_SET_INT, (void *)ctrl_arg);
        break;
#endif
    case RT_DEVICE_CTRL_SET_INT:
        NVIC_Set(uart->config->irq_type, ENABLE);
        if (ctrl_arg & RT_DEVICE_FLAG_INT_RX)
        {

            USART_ITConfig(uart->handle.Instance, USART_IT_RXNE, ENABLE);
            USART_ClearITPendingBit(uart->config->Instance, USART_IT_RXNE);
            USART_ClearFlag(uart->handle.Instance, USART_FLAG_RXNE);
        }
        else if (ctrl_arg & RT_DEVICE_FLAG_INT_TX)
        {
            USART_ITConfig(uart->handle.Instance, USART_IT_TC, ENABLE);
            USART_ClearFlag(uart->handle.Instance, USART_FLAG_TC);
        }
        NVIC_Set(uart->config->irq_type, ENABLE);
        break;

    case RT_DEVICE_CHECK_OPTMODE:
        if (ctrl_arg & RT_DEVICE_FLAG_DMA_TX)
            return RT_SERIAL_TX_BLOCKING_NO_BUFFER;
        else
            return RT_SERIAL_TX_BLOCKING_BUFFER;
    case RT_DEVICE_CTRL_CLOSE:
#ifdef RT_SERIAL_USING_DMA
        DMA_Cmd(uart->dma_tx.handle.Instance, DISABLE);
        DMA_Cmd(uart->dma_rx.handle.Instance, DISABLE);
        NVIC_Set(uart->dma_rx.handle.dma_irq, DISABLE);
#endif
        USART_DeInit(uart->handle.Instance);
        NVIC_Set(uart->config->irq_type, DISABLE);
        USART_ITConfig(uart->handle.Instance, USART_IT_TC, DISABLE);
        USART_ITConfig(uart->handle.Instance, USART_IT_RXNE, DISABLE);
        USART_ITConfig(uart->handle.Instance, USART_IT_IDLE, DISABLE);
        USART_ITConfig(uart->handle.Instance, USART_IT_RXNE, DISABLE);
        break;
    }

    return RT_EOK;
}

static int ch32_putc(struct rt_serial_device *serial, char c)
{
    struct ch32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ch32_uart, serial);
     while (USART_GetFlagStatus(uart->config->Instance, USART_FLAG_TC) == RESET);
    uart->config->Instance->DATAR = c;
/* Transmit Data */

    return 1;
}

static int ch32_getc(struct rt_serial_device *serial)
{
    struct ch32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ch32_uart, serial);

    return (int)(uart->handle.Instance->DATAR & (uint16_t)0xFF);
}

static rt_ssize_t ch32_transmit(struct rt_serial_device *serial,
                              rt_uint8_t              *buf,
                              rt_size_t                size,
                              rt_uint32_t              tx_flag)
{
    struct ch32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    uart = rt_container_of(serial, struct ch32_uart, serial);

#ifdef RT_SERIAL_USING_DMA
    if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        DMA_Cmd(uart->dma_tx.handle.Instance, DISABLE);
        uart->dma_tx.handle.Instance->MADDR = (unsigned int)buf;
        uart->dma_tx.handle.Instance->CNTR = size & 0xFFFF;
        DMA_Cmd(uart->dma_tx.handle.Instance, ENABLE);

        return size & 0xFFFF;
    }
#endif

    return size;
}


/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct ch32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct ch32_uart, serial);
    /* If the Read data register is not empty and the RXNE interrupt is enabled  （RDR） */
    if (USART_GetITStatus(uart->handle.Instance, USART_IT_RXNE) != RESET && USART_GetFlagStatus(uart->handle.Instance, USART_FLAG_RXNE) != RESET)
    {
        char chr = uart->handle.Instance->DATAR;
        rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_PUTC, &chr);
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        USART_ClearITPendingBit(uart->config->Instance, USART_IT_RXNE);
    }
    /* If the Transmit data register is empty and the TXE interrupt enable is enabled  （TDR）*/
    else if (USART_GetITStatus(uart->handle.Instance, USART_IT_TXE) != RESET && USART_GetFlagStatus(uart->handle.Instance, USART_FLAG_TXE) != RESET)
    {
        rt_uint8_t put_char = 0;
        if (rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_GETC, &put_char) == RT_EOK)
        {
            USART_SendData(uart->handle.Instance, put_char);
        }
         USART_ClearITPendingBit(uart->config->Instance, USART_IT_TXE);
    }
    else if (USART_GetITStatus(uart->handle.Instance, USART_IT_TC) != RESET && USART_GetFlagStatus(uart->handle.Instance, USART_FLAG_TC))
    {
        /* Clear Transmission complete interrupt flag ( ISR Register ) */
        USART_ClearITPendingBit(uart->handle.Instance, USART_IT_TC);
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
    }

#ifdef RT_SERIAL_USING_DMA
    else if ((uart->uart_dma_flag) && (USART_GetFlagStatus(uart->handle.Instance, USART_FLAG_IDLE) != RESET)
             && (USART_GetITStatus(uart->handle.Instance, USART_IT_IDLE) != RESET))
    {
        /* clean IDLEF flag */
        dma_recv_isr(serial, UART_RX_DMA_IT_IDLE_FLAG);
        USART_ReceiveData(uart->handle.Instance);
    }
#endif

}



#if defined(BSP_USING_UART1)
#if defined (SOC_RISCV_SERIES_CH32V2)
void USART1_IRQHandler(void) __attribute__((interrupt()));
#else
void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void USART1_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART1_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_RX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA1_Channel5_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA1_Channel5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA1_Channel5_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART1_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}

#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_TX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA1_Channel4_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA1_Channel4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA1_Channel4_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART1_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_TX_USING_DMA) */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#if defined (SOC_RISCV_SERIES_CH32V2)
void USART2_IRQHandler(void) __attribute__((interrupt()));
#else
void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void USART2_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART2_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_RX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA1_Channel6_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA1_Channel6_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA1_Channel6_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART2_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_TX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA1_Channel7_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA1_Channel7_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA1_Channel7_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART2_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_TX_USING_DMA) */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
#if defined (SOC_RISCV_SERIES_CH32V2)
void USART3_IRQHandler(void) __attribute__((interrupt()));
#else
void USART3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void USART3_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART3_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART3_RX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA1_Channel3_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA1_Channel3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA1_Channel3_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART3_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* defined(BSP_UART_USING_DMA_RX) && defined(BSP_UART3_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART3_TX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA1_Channel2_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA1_Channel2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA1_Channel2_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART3_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* defined(BSP_UART_USING_DMA_TX) && defined(BSP_UART3_TX_USING_DMA) */
#endif /* BSP_USING_UART3*/

#if defined(BSP_USING_UART4)
#if defined (SOC_RISCV_SERIES_CH32V2)
void UART4_IRQHandler(void) __attribute__((interrupt()));
#else
void UART4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void UART4_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART4_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART4_RX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA2_Channel3_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA2_Channel3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA2_Channel3_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART4_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* defined(BSP_UART_USING_DMA_RX) && defined(BSP_UART4_RX_USING_DMA) */

#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART4_TX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA2_Channel5_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA2_Channel5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA2_Channel5_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART4_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* defined(BSP_UART_USING_DMA_TX) && defined(BSP_UART4_TX_USING_DMA) */
#endif /* BSP_USING_UART4*/

#if defined(BSP_USING_UART5)
#if defined (SOC_RISCV_SERIES_CH32V2)
void UART5_IRQHandler(void) __attribute__((interrupt()));
#else
void UART5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void UART5_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART5_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART5_RX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA2_Channel2_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA2_Channel2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA2_Channel2_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART5_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART5_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART5_TX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA2_Channel4_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA2_Channel4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA2_Channel4_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART5_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART5_TX_USING_DMA) */
#endif /* BSP_USING_UART5*/

#if defined(BSP_USING_UART6)
#if defined (SOC_RISCV_SERIES_CH32V2)
void UART6_IRQHandler(void) __attribute__((interrupt()));
#else
void UART6_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void UART6_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART6_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART6_RX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA2_Channel7_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA2_Channel7_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA2_Channel7_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART6_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART6_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART6_TX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA2_Channel6_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA2_Channel6_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA2_Channel6_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART6_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART6_TX_USING_DMA) */
#endif /* BSP_USING_UART6*/

#if defined(BSP_USING_UART7)
#if defined (SOC_RISCV_SERIES_CH32V2)
void UART7_IRQHandler(void) __attribute__((interrupt()));
#else
void UART7_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void UART7_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART7_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART7_RX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA2_Channel9_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA2_Channel9_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA2_Channel9_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART7_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART7_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART7_TX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA2_Channel8_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA2_Channel8_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA2_Channel8_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART7_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART7_TX_USING_DMA) */
#endif /* BSP_USING_UART7*/

#if defined(BSP_USING_UART8)
#if defined (SOC_RISCV_SERIES_CH32V2)
void UART8_IRQHandler(void) __attribute__((interrupt()));
#else
void UART8_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void UART8_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART8_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART8_RX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA2_Channel11_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA2_Channel11_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA2_Channel11_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART8_INDEX].dma_rx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART8_RX_USING_DMA) */
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART8_TX_USING_DMA)
#if defined (SOC_RISCV_SERIES_CH32V2)
void DMA2_Channel10_IRQHandler(void) __attribute__((interrupt()));
#else
void DMA2_Channel10_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#endif
void DMA2_Channel10_IRQHandler(void)
{
    GET_INT_SP();
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&uart_obj[UART8_INDEX].dma_tx.handle);

    /* leave interrupt */
    rt_interrupt_leave();
    FREE_INT_SP();
}
#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART8_TX_USING_DMA) */
#endif /* BSP_USING_UART8*/
static void ch32_uart_get_config(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART1
    uart_obj[UART1_INDEX].serial.config          = config;
    uart_obj[UART1_INDEX].serial.config.rx_bufsz = BSP_UART1_RX_BUFSIZE;
    uart_obj[UART1_INDEX].serial.config.tx_bufsz = BSP_UART1_TX_BUFSIZE;
    uart_obj[UART1_INDEX].handle.Instance        = USART1;
    uart_obj[UART1_INDEX].uart_dma_flag          = 0;
#ifdef BSP_UART1_RX_USING_DMA
    uart_obj[UART1_INDEX].handle.HDMA_Rx          = &uart_obj[UART1_INDEX].dma_rx.handle;
    uart_obj[UART1_INDEX].serial.config.dma_ping_bufsz = BSP_UART1_DMA_PING_BUFSIZE;
    uart_obj[UART1_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_RX;
    uart_obj[UART1_INDEX].dma_rx.handle.Parent    = &uart_obj[UART1_INDEX].handle;
    uart_obj[UART1_INDEX].dma_rx.handle.Instance  = DMA1_Channel5;
    uart_obj[UART1_INDEX].dma_rx.handle.dma_rcc   = RCC_AHBPeriph_DMA1;
    uart_obj[UART1_INDEX].dma_rx.handle.dma_irq   = DMA1_Channel5_IRQn;
#endif
#ifdef BSP_UART1_TX_USING_DMA
    uart_obj[UART1_INDEX].handle.HDMA_Tx          = &uart_obj[UART1_INDEX].dma_tx.handle;
    uart_obj[UART1_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_TX;
    uart_obj[UART1_INDEX].dma_tx.handle.Parent    = &uart_obj[UART1_INDEX].handle;
    uart_obj[UART1_INDEX].dma_tx.handle.Instance  = DMA1_Channel4;
    uart_obj[UART1_INDEX].dma_tx.handle.dma_rcc   = RCC_AHBPeriph_DMA1;
    uart_obj[UART1_INDEX].dma_tx.handle.dma_irq   = DMA1_Channel4_IRQn;
#endif
#endif

#ifdef BSP_USING_UART2
    uart_obj[UART2_INDEX].serial.config          = config;
    uart_obj[UART2_INDEX].serial.config.rx_bufsz = BSP_UART2_RX_BUFSIZE;
    uart_obj[UART2_INDEX].serial.config.tx_bufsz = BSP_UART2_TX_BUFSIZE;
    uart_obj[UART2_INDEX].handle.Instance        = USART2;
    uart_obj[UART2_INDEX].uart_dma_flag          = 0;
#ifdef BSP_UART2_RX_USING_DMA
    uart_obj[UART2_INDEX].handle.HDMA_Rx          = &uart_obj[UART2_INDEX].dma_rx.handle;
    uart_obj[UART2_INDEX].serial.config.dma_ping_bufsz = BSP_UART2_DMA_PING_BUFSIZE;
    uart_obj[UART2_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_RX;
    uart_obj[UART2_INDEX].dma_rx.handle.Parent    = &uart_obj[UART2_INDEX].handle;
    uart_obj[UART2_INDEX].dma_rx.handle.DMA_ITC_Callback = HAL_UART_RxCpltCallback;
    uart_obj[UART2_INDEX].dma_rx.handle.Instance  = DMA1_Channel6;
    uart_obj[UART2_INDEX].dma_rx.handle.dma_rcc   = RCC_AHBPeriph_DMA1;
    uart_obj[UART2_INDEX].dma_rx.handle.dma_irq   = DMA1_Channel6_IRQn;
#endif
#ifdef BSP_UART2_TX_USING_DMA
    uart_obj[UART2_INDEX].handle.HDMA_Tx          = &uart_obj[UART2_INDEX].dma_tx.handle;
    uart_obj[UART2_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_TX;
    uart_obj[UART2_INDEX].dma_tx.handle.Parent    = &uart_obj[UART2_INDEX].handle;
    uart_obj[UART2_INDEX].dma_tx.handle.DMA_ITC_Callback = HAL_UART_TxCpltCallback;
    uart_obj[UART2_INDEX].dma_tx.handle.Instance  = DMA1_Channel7;
    uart_obj[UART2_INDEX].dma_tx.handle.dma_rcc   = RCC_AHBPeriph_DMA1;
    uart_obj[UART2_INDEX].dma_tx.handle.dma_irq   = DMA1_Channel7_IRQn;
#endif
#endif

#ifdef BSP_USING_UART3
    uart_obj[UART3_INDEX].serial.config          = config;
    uart_obj[UART3_INDEX].serial.config.rx_bufsz = BSP_UART3_RX_BUFSIZE;
    uart_obj[UART3_INDEX].serial.config.tx_bufsz = BSP_UART3_TX_BUFSIZE;
    uart_obj[UART3_INDEX].handle.Instance        = USART3;
    uart_obj[UART3_INDEX].uart_dma_flag          = 0;
#ifdef BSP_UART3_RX_USING_DMA
    uart_obj[UART3_INDEX].handle.HDMA_Rx          = &uart_obj[UART3_INDEX].dma_rx.handle;
    uart_obj[UART3_INDEX].serial.config.dma_ping_bufsz = BSP_UART3_DMA_PING_BUFSIZE;
    uart_obj[UART3_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_RX;
    uart_obj[UART3_INDEX].dma_rx.handle.Parent    = &uart_obj[UART3_INDEX].handle;
    uart_obj[UART3_INDEX].dma_rx.handle.DMA_ITC_Callback = HAL_UART_RxCpltCallback;
    uart_obj[UART3_INDEX].dma_rx.handle.Instance  = DMA1_Channel3;
    uart_obj[UART3_INDEX].dma_rx.handle.dma_rcc   = RCC_AHBPeriph_DMA1;
    uart_obj[UART3_INDEX].dma_rx.handle.dma_irq   = DMA1_Channel3_IRQn;
#endif
#ifdef BSP_UART3_TX_USING_DMA
    uart_obj[UART3_INDEX].handle.HDMA_Tx          = &uart_obj[UART3_INDEX].dma_tx.handle;
    uart_obj[UART3_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_TX;
    uart_obj[UART3_INDEX].dma_tx.handle.Parent    = &uart_obj[UART3_INDEX].handle;
    uart_obj[UART3_INDEX].dma_tx.handle.Instance  = DMA1_Channel2;
    uart_obj[UART3_INDEX].dma_tx.handle.DMA_ITC_Callback = HAL_UART_TxCpltCallback;
    uart_obj[UART3_INDEX].dma_tx.handle.dma_rcc   = RCC_AHBPeriph_DMA1;
    uart_obj[UART3_INDEX].dma_tx.handle.dma_irq   = DMA1_Channel2_IRQn;
#endif
#endif

#ifdef BSP_USING_UART4
    uart_obj[UART4_INDEX].serial.config          = config;
    uart_obj[UART4_INDEX].serial.config.rx_bufsz = BSP_UART4_RX_BUFSIZE;
    uart_obj[UART4_INDEX].serial.config.tx_bufsz = BSP_UART4_TX_BUFSIZE;
    uart_obj[UART4_INDEX].handle.Instance        = UART4;
    uart_obj[UART4_INDEX].uart_dma_flag          = 0;
#ifdef BSP_UART4_RX_USING_DMA
    uart_obj[UART4_INDEX].handle.HDMA_Rx          = &uart_obj[UART4_INDEX].dma_rx.handle;
    uart_obj[UART4_INDEX].serial.config.dma_ping_bufsz = BSP_UART4_DMA_PING_BUFSIZE;
    uart_obj[UART4_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_RX;
    uart_obj[UART4_INDEX].dma_rx.handle.Parent    = &uart_obj[UART4_INDEX].handle;
    uart_obj[UART4_INDEX].dma_rx.handle.DMA_ITC_Callback = HAL_UART_RxCpltCallback;
    uart_obj[UART4_INDEX].dma_rx.handle.Instance  = DMA2_Channel3;
    uart_obj[UART4_INDEX].dma_rx.handle.dma_rcc   = RCC_AHBPeriph_DMA2;
    uart_obj[UART4_INDEX].dma_rx.handle.dma_irq   = DMA2_Channel3_IRQn;
#endif
#ifdef BSP_UART4_TX_USING_DMA
    uart_obj[UART4_INDEX].handle.HDMA_Tx          = &uart_obj[UART4_INDEX].dma_tx.handle;
    uart_obj[UART4_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_TX;
    uart_obj[UART4_INDEX].dma_tx.handle.Parent    = &uart_obj[UART4_INDEX].handle;
    uart_obj[UART4_INDEX].dma_tx.handle.DMA_ITC_Callback = HAL_UART_TxCpltCallback;
    uart_obj[UART4_INDEX].dma_tx.handle.Instance  = DMA2_Channel5;
    uart_obj[UART4_INDEX].dma_tx.handle.dma_rcc   = RCC_AHBPeriph_DMA2;
    uart_obj[UART4_INDEX].dma_tx.handle.dma_irq   = DMA2_Channel5_IRQn;
#endif
#endif

#ifdef BSP_USING_UART5
    uart_obj[UART5_INDEX].serial.config          = config;
    uart_obj[UART5_INDEX].serial.config.rx_bufsz = BSP_UART5_RX_BUFSIZE;
    uart_obj[UART5_INDEX].serial.config.tx_bufsz = BSP_UART5_TX_BUFSIZE;
    uart_obj[UART5_INDEX].handle.Instance        = UART5;
    uart_obj[UART5_INDEX].uart_dma_flag          = 0;
#ifdef BSP_UART5_RX_USING_DMA
    uart_obj[UART5_INDEX].handle.HDMA_Rx          = &uart_obj[UART5_INDEX].dma_rx.handle;
    uart_obj[UART5_INDEX].serial.config.dma_ping_bufsz = BSP_UART5_DMA_PING_BUFSIZE;
    uart_obj[UART5_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_RX;
    uart_obj[UART5_INDEX].dma_rx.handle.Parent    = &uart_obj[UART5_INDEX].handle;
    uart_obj[UART5_INDEX].dma_rx.handle.DMA_ITC_Callback = HAL_UART_RxCpltCallback;
    uart_obj[UART5_INDEX].dma_rx.handle.Instance  = DMA2_Channel2;
    uart_obj[UART5_INDEX].dma_rx.handle.dma_rcc   = RCC_AHBPeriph_DMA2;
    uart_obj[UART5_INDEX].dma_rx.handle.dma_irq   = DMA2_Channel2_IRQn;
#endif
#ifdef BSP_UART5_TX_USING_DMA
    uart_obj[UART5_INDEX].handle.HDMA_Tx          = &uart_obj[UART5_INDEX].dma_tx.handle;
    uart_obj[UART5_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_TX;
    uart_obj[UART5_INDEX].dma_tx.handle.Parent    = &uart_obj[UART5_INDEX].handle;
    uart_obj[UART5_INDEX].dma_tx.handle.DMA_ITC_Callback = HAL_UART_TxCpltCallback;
    uart_obj[UART5_INDEX].dma_tx.handle.Instance  = DMA2_Channel4;
    uart_obj[UART5_INDEX].dma_tx.handle.dma_rcc   = RCC_AHBPeriph_DMA2;
    uart_obj[UART5_INDEX].dma_tx.handle.dma_irq   = DMA2_Channel4_IRQn;
#endif
#endif

#ifdef BSP_USING_UART6
    uart_obj[UART6_INDEX].serial.config          = config;
    uart_obj[UART6_INDEX].serial.config.rx_bufsz = BSP_UART6_RX_BUFSIZE;
    uart_obj[UART6_INDEX].serial.config.tx_bufsz = BSP_UART6_TX_BUFSIZE;
    uart_obj[UART6_INDEX].handle.Instance        = UART6;
    uart_obj[UART6_INDEX].uart_dma_flag          = 0;
#ifdef BSP_UART6_RX_USING_DMA
    uart_obj[UART6_INDEX].handle.HDMA_Rx          = &uart_obj[UART6_INDEX].dma_rx.handle;
    uart_obj[UART6_INDEX].serial.config.dma_ping_bufsz = BSP_UART6_DMA_PING_BUFSIZE;
    uart_obj[UART6_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_RX;
    uart_obj[UART6_INDEX].dma_rx.handle.Parent    = &uart_obj[UART6_INDEX].handle;
    uart_obj[UART6_INDEX].dma_rx.handle.DMA_ITC_Callback = HAL_UART_RxCpltCallback;
    uart_obj[UART6_INDEX].dma_rx.handle.Instance  = DMA2_Channel7;
    uart_obj[UART6_INDEX].dma_rx.handle.dma_rcc   = RCC_AHBPeriph_DMA2;
    uart_obj[UART6_INDEX].dma_rx.handle.dma_irq   = DMA2_Channel7_IRQn;
#endif
#ifdef BSP_UART6_TX_USING_DMA
    uart_obj[UART6_INDEX].handle.HDMA_Tx          = &uart_obj[UART6_INDEX].dma_tx.handle;
    uart_obj[UART6_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_TX;
    uart_obj[UART6_INDEX].dma_tx.handle.Parent    = &uart_obj[UART6_INDEX].handle;
    uart_obj[UART6_INDEX].dma_tx.handle.DMA_ITC_Callback = HAL_UART_TxCpltCallback;
    uart_obj[UART6_INDEX].dma_tx.handle.Instance  = DMA2_Channel6;
    uart_obj[UART6_INDEX].dma_tx.handle.dma_rcc   = RCC_AHBPeriph_DMA2;
    uart_obj[UART6_INDEX].dma_tx.handle.dma_irq   = DMA2_Channel6_IRQn;
#endif
#endif

#ifdef BSP_USING_UART7
    uart_obj[UART7_INDEX].serial.config          = config;
    uart_obj[UART7_INDEX].serial.config.rx_bufsz = BSP_UART7_RX_BUFSIZE;
    uart_obj[UART7_INDEX].serial.config.tx_bufsz = BSP_UART7_TX_BUFSIZE;
    uart_obj[UART7_INDEX].handle.Instance        = UART7;
    uart_obj[UART7_INDEX].uart_dma_flag          = 0;
#ifdef BSP_UART7_RX_USING_DMA
    uart_obj[UART7_INDEX].handle.HDMA_Rx          = &uart_obj[UART7_INDEX].dma_rx.handle;
    uart_obj[UART7_INDEX].serial.config.dma_ping_bufsz = BSP_UART7_DMA_PING_BUFSIZE;
    uart_obj[UART7_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_RX;
    uart_obj[UART7_INDEX].dma_rx.handle.Parent    = &uart_obj[UART7_INDEX].handle;
    uart_obj[UART7_INDEX].dma_rx.handle.DMA_ITC_Callback = HAL_UART_RxCpltCallback;
    uart_obj[UART7_INDEX].dma_rx.handle.Instance  = DMA2_Channel9;
    uart_obj[UART7_INDEX].dma_rx.handle.dma_rcc   = RCC_AHBPeriph_DMA2;
    uart_obj[UART7_INDEX].dma_rx.handle.dma_irq   = DMA2_Channel9_IRQn;
#endif
#ifdef BSP_UART7_TX_USING_DMA
    uart_obj[UART7_INDEX].handle.HDMA_Tx          = &uart_obj[UART7_INDEX].dma_tx.handle;
    uart_obj[UART7_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_TX;
    uart_obj[UART7_INDEX].dma_tx.handle.Parent    = &uart_obj[UART7_INDEX].handle;
    uart_obj[UART7_INDEX].dma_tx.handle.DMA_ITC_Callback = HAL_UART_TxCpltCallback;
    uart_obj[UART7_INDEX].dma_tx.handle.Instance  = DMA2_Channel8;
    uart_obj[UART7_INDEX].dma_tx.handle.dma_rcc   = RCC_AHBPeriph_DMA2;
    uart_obj[UART7_INDEX].dma_tx.handle.dma_irq   = DMA2_Channel8_IRQn;
#endif
#endif

#ifdef BSP_USING_UART8
    uart_obj[UART8_INDEX].serial.config            = config;
    uart_obj[UART8_INDEX].serial.config.rx_bufsz   = BSP_UART8_RX_BUFSIZE;
    uart_obj[UART8_INDEX].serial.config.tx_bufsz   = BSP_UART8_TX_BUFSIZE;
    uart_obj[UART8_INDEX].handle.Instance          = UART8;
    uart_obj[UART8_INDEX].uart_dma_flag            = 0;
#ifdef BSP_UART8_RX_USING_DMA
    uart_obj[UART8_INDEX].handle.HDMA_Rx          = &uart_obj[UART8_INDEX].dma_rx.handle;
    uart_obj[UART8_INDEX].serial.config.dma_ping_bufsz = BSP_UART8_DMA_PING_BUFSIZE;
    uart_obj[UART8_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_RX;
    uart_obj[UART8_INDEX].dma_rx.handle.Parent    = &uart_obj[UART8_INDEX].handle;
    uart_obj[UART8_INDEX].dma_rx.handle.DMA_ITC_Callback = HAL_UART_RxCpltCallback;
    uart_obj[UART8_INDEX].dma_rx.handle.Instance  = DMA2_Channel10;
    uart_obj[UART8_INDEX].dma_rx.handle.dma_rcc   = RCC_AHBPeriph_DMA2;
    uart_obj[UART8_INDEX].dma_rx.handle.dma_irq   = DMA2_Channel10_IRQn;
#endif
#ifdef BSP_UART8_TX_USING_DMA
    uart_obj[UART8_INDEX].handle.HDMA_Tx          = &uart_obj[UART8_INDEX].dma_tx.handle;
    uart_obj[UART8_INDEX].uart_dma_flag          |= RT_DEVICE_FLAG_DMA_TX;
    uart_obj[UART8_INDEX].dma_tx.handle.Parent    = &uart_obj[UART8_INDEX].handle;
    uart_obj[UART8_INDEX].dma_tx.handle.DMA_ITC_Callback = HAL_UART_TxCpltCallback;
    uart_obj[UART8_INDEX].dma_tx.handle.Instance  = DMA2_Channel11;
    uart_obj[UART8_INDEX].dma_tx.handle.dma_rcc   = RCC_AHBPeriph_DMA2;
    uart_obj[UART8_INDEX].dma_tx.handle.dma_irq   = DMA2_Channel11_IRQn;
#endif
#endif
}

#ifdef RT_SERIAL_USING_DMA
static void ch32_uart_dma_config(struct rt_serial_device *serial, rt_ubase_t flag)
{
    struct DMA_HandleTypeDef *DMA_Handle;
    struct ch32_uart          *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(flag == RT_DEVICE_FLAG_DMA_TX || flag == RT_DEVICE_FLAG_DMA_RX);
    uart = rt_container_of(serial, struct ch32_uart, serial);
    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        DMA_Handle = &uart->dma_rx.handle;
    }
    else /* RT_DEVICE_FLAG_DMA_TX == flag */
    {
        DMA_Handle = &uart->dma_tx.handle;
    }

    RCC_AHBPeriphClockCmd(DMA_Handle->dma_rcc, ENABLE);
    DMA_DeInit(DMA_Handle->Instance);
    DMA_Handle->Init.DMA_PeripheralBaseAddr     = (unsigned int)uart->config->Instance + 0x4;
    DMA_Handle->Init.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_Handle->Init.DMA_MemoryInc  = DMA_MemoryInc_Enable;
    DMA_Handle->Init.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_Handle->Init.DMA_MemoryDataSize    = DMA_MemoryDataSize_Byte;
    DMA_Handle->Init.DMA_M2M        = DMA_M2M_Disable;
    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        rt_uint8_t *ptr = NULL;
        rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_GET_DMA_PING_BUF, &ptr);
        DMA_Handle->Init.DMA_DIR    = DMA_DIR_PeripheralSRC;
        DMA_Handle->Init.DMA_MemoryBaseAddr      = (unsigned int)ptr;
        DMA_Handle->Init.DMA_BufferSize      = serial->config.dma_ping_bufsz;
        DMA_Handle->Init.DMA_Mode = DMA_Mode_Circular;
        DMA_Handle->Init.DMA_Priority     = DMA_Priority_VeryHigh;
    }
    else if (RT_DEVICE_FLAG_DMA_TX == flag)
    {
        DMA_Handle->Init.DMA_DIR    = DMA_DIR_PeripheralDST;
        DMA_Handle->Init.DMA_MemoryBaseAddr      = (unsigned int)1;
        DMA_Handle->Init.DMA_BufferSize      = 1;
        DMA_Handle->Init.DMA_Mode = DMA_Mode_Normal;
        DMA_Handle->Init.DMA_Priority     = DMA_Priority_High;
    }
    DMA_Init(DMA_Handle->Instance, &DMA_Handle->Init);
    NVIC_Set(DMA_Handle->dma_irq, ENABLE);
    /* Enable USART DMA Rx or TX request */
    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        DMA_Cmd(DMA_Handle->Instance, DISABLE);
        USART_DMACmd(uart->handle.Instance, USART_DMAReq_Rx, ENABLE);
        USART_ITConfig(uart->handle.Instance, USART_IT_IDLE, ENABLE);
        USART_ReceiveData(uart->handle.Instance);
        DMA_ITConfig(DMA_Handle->Instance, DMA_IT_TC, ENABLE);
        NVIC_Set(uart->config->irq_type, ENABLE);
        DMA_Cmd(DMA_Handle->Instance, ENABLE);
    }
    else if (RT_DEVICE_FLAG_DMA_TX == flag)
    {
        USART_DMACmd(uart->handle.Instance, USART_DMAReq_Tx, ENABLE);
        DMA_ITConfig(uart->dma_tx.handle.Instance, DMA_IT_TC, ENABLE);
    }
    USART_Cmd(uart->handle.Instance, ENABLE);
}
/**
  * @brief  Handle DMA interrupt request.
  * @param  hdma pointer to a DMA_HandleTypeDef structure that contains
  *               the configuration information for the specified DMA Channel.
  * @retval None
  */
static void HAL_DMA_IRQHandler(struct DMA_HandleTypeDef *hdma)
{
    DMA_TypeDef *dmax = RT_NULL;
    if ((unsigned int)hdma->Instance < DMA2_BASE)
    {
        dmax = DMA1;
    }
    else
    {
        dmax = DMA2;
    }
    unsigned int flag_it        = dmax->INTFR;
    unsigned int channel_offset = ((unsigned int)hdma->Instance - (unsigned int)dmax - 8) / 20;
    /* Transfer Complete Interrupt management ***********************************/
    if ((flag_it & 2u << (4 * channel_offset)))
    {
        /* Clear the transfer complete flag */
        dmax->INTFCR |= 2u << (4 * channel_offset);
        struct ch32_uart *uart = (struct ch32_uart *)hdma->Parent;
        /* Call the transfer complete callback */
        if (hdma->DMA_ITC_Callback != RT_NULL)
        {
            hdma->DMA_ITC_Callback(&uart->handle);
        }

    }

    if(flag_it & (8u << (4 * channel_offset)))
    {
        rt_kprintf("DMA error: %d\n", flag_it & (8u << (4 * channel_offset)));
        dmax->INTFCR |= 8u << (4 * channel_offset);
    }



}

static void dma_recv_isr(struct rt_serial_device *serial, rt_uint8_t isr_flag)
{
    struct ch32_uart *uart;
    rt_base_t        level;
    rt_size_t        recv_len, counter;

    RT_ASSERT(serial != RT_NULL);
    uart     = rt_container_of(serial, struct ch32_uart, serial);
    recv_len = 0;
    counter = uart->dma_rx.handle.Instance->CNTR;

    switch (isr_flag)
    {
    case UART_RX_DMA_IT_IDLE_FLAG:
        if (counter <= uart->dma_rx.remaining_cnt)
            recv_len = uart->dma_rx.remaining_cnt - counter;
        else
            recv_len = serial->config.dma_ping_bufsz + uart->dma_rx.remaining_cnt - counter;

        break;
    case UART_RX_DMA_IT_HT_FLAG:
        if (counter < uart->dma_rx.remaining_cnt)
            recv_len = uart->dma_rx.remaining_cnt - counter;
        else
            recv_len = 0;
        break;
    case UART_RX_DMA_IT_TC_FLAG:
        recv_len = uart->dma_rx.remaining_cnt;
        break;

    default:
        recv_len = 0;
        break;
    }

    if (recv_len)
    {
        uart->dma_rx.remaining_cnt = counter;

        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }


}

void HAL_UART_TxCpltCallback(struct UART_HandleTypeDef *huart)
{
    RT_ASSERT(huart != NULL);
    struct ch32_uart *uart = (struct ch32_uart *)huart;

    rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_TX_DMADONE);
}

void HAL_UART_RxCpltCallback(struct UART_HandleTypeDef *huart)
{
    struct ch32_uart *uart;
    RT_ASSERT(huart != NULL);
    uart = (struct ch32_uart *)huart;
    dma_recv_isr(&uart->serial, UART_RX_DMA_IT_TC_FLAG);
}
#endif /* RT_SERIAL_USING_DMA */

static const struct rt_uart_ops ch32_uart_ops =
{
    .configure = ch32_configure,
    .control   = ch32_control,
    .putc      = ch32_putc,
    .getc      = ch32_getc,
    .transmit  = ch32_transmit
};

int rt_hw_usart_init(void)
{
    rt_err_t  result  = 0;
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct ch32_uart);

    ch32_uart_get_config();
    for (int i = 0; i < obj_num; i++)
    {
        uart_obj[i].config = &uart_config[i];
        /* init UART object */
        uart_obj[i].serial.ops = &ch32_uart_ops;
        /* register UART device */
        rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_DMA_TX, NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL_V2 */

