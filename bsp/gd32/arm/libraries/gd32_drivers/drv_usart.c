/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 * 2023-06-17     CX      	   support DMA TX and RX
 */

#include "drv_usart.h"
#define DBG_TAG             "drv.usart"
#define DBG_LVL             DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_SERIAL

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && \
    !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && \
    !defined(BSP_USING_UART6) && !defined(BSP_USING_UART7)
#error "Please define at least one UARTx"

#endif

#include <rtdevice.h>

static void GD32_UART_IRQHandler(struct rt_serial_device *serial);

enum
{
#ifdef BSP_USING_UART0
    UART0_INDEX,
#endif
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
};

#ifdef RT_SERIAL_USING_DMA
static void gd32_dma_config(struct rt_serial_device *serial, rt_ubase_t flag);
#endif

#ifdef RT_SERIAL_USING_DMA
static void gd32_dma_config(struct rt_serial_device *serial, rt_ubase_t flag)
{
	struct rt_serial_rx_fifo *rx_fifo;
    struct dma_config *dma_config;
	dma_single_data_parameter_struct dma_init_struct;
	
	RT_ASSERT(serial != RT_NULL);
	struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;
	RT_ASSERT(uart != RT_NULL);
	RT_ASSERT(flag == RT_DEVICE_FLAG_DMA_TX || flag == RT_DEVICE_FLAG_DMA_RX);
	
    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        dma_config = uart->dma_rx;
    }
    else /* RT_DEVICE_FLAG_DMA_TX == flag */
    {
        dma_config = uart->dma_tx;
    }
    LOG_D("%s dma config start", uart->device_name);

	/* enable DMA clock */
	if(dma_config->dma_periph == DMA0)
	{
		rcu_periph_clock_enable(RCU_DMA0);
	}
	else if(dma_config->dma_periph == DMA1)
	{
		rcu_periph_clock_enable(RCU_DMA1);
	}
	else
	{
		RT_ASSERT(0);
	}
	
	/* config DMA TX mode*/
	if(flag == RT_DEVICE_FLAG_DMA_TX)
	{
		dma_deinit(dma_config->dma_periph, dma_config->channel);
		dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
		dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
		dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
		dma_init_struct.periph_addr = (uint32_t)&USART_DATA(uart->uart_periph);
		dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
		dma_init_struct.priority = dma_config->priority;
		dma_single_data_mode_init(dma_config->dma_periph, dma_config->channel, &dma_init_struct);
		
		dma_circulation_disable(dma_config->dma_periph, dma_config->channel);
		dma_channel_subperipheral_select(dma_config->dma_periph, dma_config->channel, dma_config->peripheral);    

		usart_dma_transmit_config(uart->uart_periph, USART_TRANSMIT_DMA_ENABLE);

		/* clean TC flag */
        usart_flag_clear(uart->uart_periph, USART_FLAG_TC);
		/* enable interrupt */
        usart_interrupt_enable(uart->uart_periph, USART_INT_TC);
        /* enable DMA Tx irq */
        NVIC_EnableIRQ(uart->dma_tx->dma_irqn);
		dma_interrupt_enable(uart->dma_tx->dma_periph, uart->dma_tx->channel, DMA_CHXCTL_FTFIE);
	}
	else
	{
		rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
		dma_deinit(dma_config->dma_periph, dma_config->channel);
		dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
		dma_init_struct.memory0_addr = (uint32_t)rx_fifo->buffer;
		dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
		dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
		dma_init_struct.number = serial->config.bufsz;
		dma_init_struct.periph_addr = (uint32_t)&USART_DATA(uart->uart_periph);
		dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
		dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
		dma_single_data_mode_init(dma_config->dma_periph, dma_config->channel, &dma_init_struct);
		
		dma_circulation_enable(dma_config->dma_periph, dma_config->channel); 
		dma_channel_subperipheral_select(dma_config->dma_periph, dma_config->channel, dma_config->peripheral);
		dma_transfer_number_config(dma_config->dma_periph, dma_config->channel, serial->config.bufsz);
		dma_channel_enable(dma_config->dma_periph, dma_config->channel);
		
		usart_dma_receive_config(uart->uart_periph, USART_RECEIVE_DMA_ENABLE);
		
		usart_flag_clear(uart->uart_periph, USART_FLAG_IDLE);
		/* enable rx irq */
        NVIC_EnableIRQ(uart->irqn);
        /* enable interrupt */
        usart_interrupt_enable(uart->uart_periph, USART_INT_IDLE);
		
		dma_interrupt_flag_clear(uart->dma_rx->dma_periph, uart->dma_rx->channel, DMA_INT_FLAG_FTF|DMA_INT_FLAG_HTF);
		/* enable DMA rx irq */
		NVIC_EnableIRQ(uart->dma_rx->dma_irqn);
		/* enable DMA interrupt */
        dma_interrupt_enable(uart->dma_rx->dma_periph, uart->dma_rx->channel, DMA_CHXCTL_FTFIE|DMA_CHXCTL_HTFIE);
	}

    LOG_D("%s dma %s instance: %x", uart->device_name, flag == RT_DEVICE_FLAG_DMA_RX ? "RX" : "TX", dma_config->dma_periph);
    LOG_D("%s dma config done", uart->device_name);
}

static void dma_recv_isr(struct rt_serial_device *serial, rt_uint8_t isr_flag)
{
    rt_base_t level;
    rt_size_t recv_len, counter;
	
	RT_ASSERT(serial != RT_NULL);
	struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;
	RT_ASSERT(uart != RT_NULL);

    level = rt_hw_interrupt_disable();
    recv_len = 0;
    counter = dma_transfer_number_get(uart->dma_rx->dma_periph, uart->dma_rx->channel);

    switch (isr_flag)
    {
    case UART_RX_DMA_IT_IDLE_FLAG:
        if (counter <= uart->dma_rx->remaining_cnt)
		{
			recv_len = uart->dma_rx->remaining_cnt - counter;
		}      
        else
		{
			recv_len = serial->config.bufsz + uart->dma_rx->remaining_cnt - counter;
		}          
        break;

    case UART_RX_DMA_IT_HT_FLAG:
        if (counter < uart->dma_rx->remaining_cnt)
		{
			recv_len = uart->dma_rx->remaining_cnt - counter;
		}  
        break;

    case UART_RX_DMA_IT_TC_FLAG:
        if(counter >= uart->dma_rx->remaining_cnt)
		{
			recv_len = serial->config.bufsz + uart->dma_rx->remaining_cnt - counter;
		}
    default:
        break;
    }

    if (recv_len)
    {
        uart->dma_rx->remaining_cnt = counter;
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
    rt_hw_interrupt_enable(level);
}

static void _dma_tx_complete(struct rt_serial_device *serial)
{
    rt_size_t trans_total_index;
    rt_base_t level;

	RT_ASSERT(serial != RT_NULL);
	struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;
	RT_ASSERT(uart != RT_NULL);

    level = rt_hw_interrupt_disable();
    trans_total_index = dma_transfer_number_get(uart->dma_tx->dma_periph, uart->dma_tx->channel);
    rt_hw_interrupt_enable(level);

    if (trans_total_index == 0)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
    }
}

static struct dma_config tx_dma_confings[] =
{
#if defined(BSP_USING_UART0)
    {
        .dma_periph = DMA1,
        .channel = DMA_CH7,
        .peripheral = DMA_SUBPERI4,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA1_Channel7_IRQn,
    },
#endif
#if defined(BSP_USING_UART1)
    {
        .dma_periph = DMA0,
        .channel = DMA_CH6,
        .peripheral = DMA_SUBPERI4,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA0_Channel6_IRQn,
    },
#endif
#if defined(BSP_USING_UART2)
    {
        .dma_periph = DMA0,
        .channel = DMA_CH3,
        .peripheral = DMA_SUBPERI4,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA0_Channel3_IRQn,
    },
#endif
#if defined(BSP_USING_UART3)
    {
        .dma_periph = DMA0,
        .channel = DMA_CH4,
        .peripheral = DMA_SUBPERI4,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA0_Channel4_IRQn,
    },
#endif
#if defined(BSP_USING_UART4)
    {
        .dma_periph = DMA0,
        .channel = DMA_CH7,
        .peripheral = DMA_SUBPERI4,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA0_Channel7_IRQn,
    },
#endif
#if defined(BSP_USING_UART5)
    {
        .dma_periph = DMA1,
        .channel = DMA_CH7,
        .peripheral = DMA_SUBPERI5,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA1_Channel6_IRQn,
    },
#endif
#if defined(BSP_USING_UART6)
    {
        .dma_periph = DMA0,
        .channel = DMA_CH1,
        .peripheral = DMA_SUBPERI5,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA0_Channel1_IRQn,
    },
#endif
#if defined(BSP_USING_UART7)
    {
        .dma_periph = DMA0,
        .channel = DMA_CH0,
        .peripheral = DMA_SUBPERI5,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA0_Channel0_IRQn,
    }
#endif
};
 
static struct dma_config rx_dma_confings[] =
{
#if defined(BSP_USING_UART0)
    {
        .dma_periph = DMA1,
        .channel = DMA_CH5,
        .peripheral = DMA_SUBPERI4,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA1_Channel5_IRQn,
    },
#endif
#if defined(BSP_USING_UART1)
    {
        .dma_periph = DMA0,
        .channel = DMA_CH5,
        .peripheral = DMA_SUBPERI4,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA0_Channel5_IRQn,
    },
#endif
#if defined(BSP_USING_UART2)
    {
        .dma_periph = DMA0,
        .channel = DMA_CH1,
        .peripheral = DMA_SUBPERI4,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA0_Channel1_IRQn,
    },
#endif
#if defined(BSP_USING_UART3)
    {
        .dma_periph = DMA0,
        .channel = DMA_CH2,
        .peripheral = DMA_SUBPERI4,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA0_Channel2_IRQn,
    },
#endif
#if defined(BSP_USING_UART4)
    {
        .dma_periph = DMA0,
        .channel = DMA_CH0,
        .peripheral = DMA_SUBPERI4,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA0_Channel0_IRQn,
    },
#endif
#if defined(BSP_USING_UART5)
    {
        .dma_periph = DMA1,
        .channel = DMA_CH2,
        .peripheral = DMA_SUBPERI5,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA1_Channel2_IRQn,
    },
#endif
#if defined(BSP_USING_UART6)
    {
        .dma_periph = DMA0,
        .channel = DMA_CH3,
        .peripheral = DMA_SUBPERI5,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA0_Channel3_IRQn,
    },
#endif
#if defined(BSP_USING_UART7)
    {
        .dma_periph = DMA0,
        .channel = DMA_CH6,
        .peripheral = DMA_SUBPERI5,
        .priority = DMA_PRIORITY_ULTRA_HIGH,
		.dma_irqn = DMA0_Channel6_IRQn,
    }
#endif
};
#endif

#if defined(BSP_USING_UART0)
struct rt_serial_device serial0;
void USART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    GD32_UART_IRQHandler(&serial0);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART0_TX_USING_DMA)
void DMA1_Channel7_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial0);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART0_RX_USING_DMA)
void DMA1_Channel5_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial0);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
struct rt_serial_device serial1;
void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    GD32_UART_IRQHandler(&serial1);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_TX_USING_DMA)
void DMA0_Channel6_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial1);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_RX_USING_DMA)
void DMA0_Channel5_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial1);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
struct rt_serial_device serial2;
void USART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    GD32_UART_IRQHandler(&serial2);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_TX_USING_DMA)
void DMA0_Channel3_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial2);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART2_RX_USING_DMA)
void DMA0_Channel1_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial2);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
struct rt_serial_device serial3;
void UART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    GD32_UART_IRQHandler(&serial3);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART3_TX_USING_DMA)
void DMA0_Channel4_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial3);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART3_RX_USING_DMA)
void DMA0_Channel2_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial3);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
struct rt_serial_device serial4;
void UART4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
	
    GD32_UART_IRQHandler(&serial4);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART4_TX_USING_DMA)
void DMA0_Channel7_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial4);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART4_RX_USING_DMA)
void DMA0_Channel0_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial4);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
struct rt_serial_device serial5;
void USART5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    GD32_UART_IRQHandler(&serial5);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART5_TX_USING_DMA)
void DMA1_Channel6_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial5);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART5_RX_USING_DMA)
void DMA1_Channel2_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial5);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
struct rt_serial_device serial6;
void UART6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    GD32_UART_IRQHandler(&serial6);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART6_TX_USING_DMA)
void DMA0_Channel1_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial6);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART6_RX_USING_DMA)
void DMA0_Channel3_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial6);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
struct rt_serial_device serial7;
void UART7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    GD32_UART_IRQHandler(&serial7);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART7_TX_USING_DMA)
void DMA0_Channel0_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial7);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART7_RX_USING_DMA)
void DMA0_Channel6_IRQHandler(void)
{    
    /* enter interrupt */
    rt_interrupt_enter();
	
	GD32_UART_IRQHandler(&serial7);
	
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#endif /* BSP_USING_UART7 */

static const struct gd32_uart uart_obj[] = {
#ifdef BSP_USING_UART0
    {
		"uart0",
        USART0,                                 // uart peripheral index
        USART0_IRQn,                            // uart iqrn
        RCU_USART0, RCU_GPIOA, RCU_GPIOA,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOA, GPIO_AF_7, GPIO_PIN_9,           // tx port, tx alternate, tx pin
        GPIOA, GPIO_AF_7, GPIO_PIN_10,          // rx port, rx alternate, rx pin
#else
        GPIOA, GPIO_PIN_9,           // tx port, tx pin
        GPIOA, GPIO_PIN_10,          // rx port, rx pin
#endif
#ifdef RT_SERIAL_USING_DMA
		.dma_flag = RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX,
		.dma_rx =   &rx_dma_confings[UART0_INDEX],
		.dma_tx =   &tx_dma_confings[UART0_INDEX],
#endif
		&serial0
    },
#endif

#ifdef BSP_USING_UART1
    {
	    "uart1",
        USART1,                                 // uart peripheral index
        USART1_IRQn,                            // uart iqrn
        RCU_USART1, RCU_GPIOA, RCU_GPIOA,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOA, GPIO_AF_7, GPIO_PIN_2,           // tx port, tx alternate, tx pin
        GPIOA, GPIO_AF_7, GPIO_PIN_3,           // rx port, rx alternate, rx pin
#else
        GPIOA, GPIO_PIN_2,                      // tx port, tx pin
        GPIOA, GPIO_PIN_3,                      // rx port, rx pin
#endif
#ifdef RT_SERIAL_USING_DMA
		.dma_flag = RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX,
		.dma_rx =   &rx_dma_confings[UART1_INDEX],
		.dma_tx =   &tx_dma_confings[UART1_INDEX],
#endif
		&serial1
    },
#endif

#ifdef BSP_USING_UART2
    {
		"uart2",
        USART2,                                 // uart peripheral index
        USART2_IRQn,                            // uart iqrn
        RCU_USART2, RCU_GPIOB, RCU_GPIOB,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOB, GPIO_AF_7, GPIO_PIN_10,          // tx port, tx alternate, tx pin
        GPIOB, GPIO_AF_7, GPIO_PIN_11,          // rx port, rx alternate, rx pin
#else
        GPIOB, GPIO_PIN_10,          // tx port, tx pin
        GPIOB, GPIO_PIN_11,          // rx port, rx pin
#endif
#ifdef RT_SERIAL_USING_DMA
		.dma_flag = RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX,
		.dma_rx =   &rx_dma_confings[UART2_INDEX],
		.dma_tx =   &tx_dma_confings[UART2_INDEX],
#endif
		&serial2
    },
#endif

    #ifdef BSP_USING_UART3
    {
		"uart3",
        UART3,                                 // uart peripheral index
        UART3_IRQn,                            // uart iqrn
        RCU_UART3, RCU_GPIOA, RCU_GPIOA,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOA, GPIO_AF_8, GPIO_PIN_0,         // tx port, tx alternate, tx pin
        GPIOA, GPIO_AF_8, GPIO_PIN_1,         // rx port, rx alternate, rx pin
#else
        GPIOC, GPIO_PIN_10,         // tx port, tx pin
        GPIOC, GPIO_PIN_11,         // rx port, rx pin
#endif
#ifdef RT_SERIAL_USING_DMA
		.dma_flag = RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX,
		.dma_rx =   &rx_dma_confings[UART3_INDEX],
		.dma_tx =   &tx_dma_confings[UART3_INDEX],
#endif
		&serial3
    },
#endif

#ifdef BSP_USING_UART4
    {
		"uart4",
        UART4,                                 // uart peripheral index
        UART4_IRQn,                            // uart iqrn
        RCU_UART4, RCU_GPIOC, RCU_GPIOD,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOC, GPIO_AF_8, GPIO_PIN_12,         // tx port, tx alternate, tx pin
        GPIOD, GPIO_AF_8, GPIO_PIN_2,          // rx port, rx alternate, rx pin
#else
        GPIOC, GPIO_PIN_12,         // tx port, tx pin
        GPIOD, GPIO_PIN_2,          // rx port, rx pin
#endif
#ifdef RT_SERIAL_USING_DMA
		.dma_flag = RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX,
		.dma_rx =   &rx_dma_confings[UART4_INDEX],
		.dma_tx =   &tx_dma_confings[UART4_INDEX],
#endif
		&serial4
    },
#endif

#ifdef BSP_USING_UART5
    {
		"uart5",
        USART5,                                 // uart peripheral index
        USART5_IRQn,                            // uart iqrn
        RCU_USART5, RCU_GPIOC, RCU_GPIOC,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOC, GPIO_AF_8, GPIO_PIN_6,           // tx port, tx alternate, tx pin
        GPIOC, GPIO_AF_8, GPIO_PIN_7,           // rx port, rx alternate, rx pin
#else
        GPIOC, GPIO_PIN_6,           // tx port, tx pin
        GPIOC, GPIO_PIN_7,           // rx port, rx pin
#endif
	#ifdef RT_SERIAL_USING_DMA
		.dma_flag = RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX,
		.dma_rx =   &rx_dma_confings[UART5_INDEX],
		.dma_tx =   &tx_dma_confings[UART5_INDEX],
#endif
		&serial5
    },
#endif

#ifdef BSP_USING_UART6
    {
		"uart6",
        UART6,                                 // uart peripheral index
        UART6_IRQn,                            // uart iqrn
        RCU_UART6, RCU_GPIOE, RCU_GPIOE,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOE, GPIO_AF_8, GPIO_PIN_7,          // tx port, tx alternate, tx pin
        GPIOE, GPIO_AF_8, GPIO_PIN_8,          // rx port, rx alternate, rx pin
#else
        GPIOE, GPIO_PIN_7,          // tx port, tx pin
        GPIOE, GPIO_PIN_8,          // rx port, rx pin
#endif
#ifdef RT_SERIAL_USING_DMA
		.dma_flag = RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX,
		.dma_rx =   &rx_dma_confings[UART6_INDEX],
		.dma_tx =   &tx_dma_confings[UART6_INDEX],
#endif
		&serial6
    },
#endif

#ifdef BSP_USING_UART7
    {
		"uart7",
        UART7,                                 // uart peripheral index
        UART7_IRQn,                            // uart iqrn
        RCU_UART7, RCU_GPIOE, RCU_GPIOE,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOE, GPIO_AF_8, GPIO_PIN_0,          // tx port, tx alternate, tx pin
        GPIOE, GPIO_AF_8, GPIO_PIN_1,          // rx port, rx alternate, rx pin
#else
        GPIOE, GPIO_PIN_0,          // tx port, tx pin
        GPIOE, GPIO_PIN_1,          // rx port, rx pin
#endif
#ifdef RT_SERIAL_USING_DMA
		.dma_flag = RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX,
		.dma_rx =   &rx_dma_confings[UART7_INDEX],
		.dma_tx =   &tx_dma_confings[UART7_INDEX],
#endif
        &serial7,
    },
#endif
};

/**
* @brief UART MSP Initialization
*        This function configures the hardware resources used in this example:
*           - Peripheral's clock enable
*           - Peripheral's GPIO Configuration
*           - NVIC configuration for UART interrupt request enable
* @param huart: UART handle pointer
* @retval None
*/
void gd32_uart_gpio_init(struct gd32_uart *uart)
{
    /* enable USART clock */
    rcu_periph_clock_enable(uart->tx_gpio_clk);
    rcu_periph_clock_enable(uart->rx_gpio_clk);
    rcu_periph_clock_enable(uart->per_clk);

#if defined SOC_SERIES_GD32F4xx
    /* connect port to USARTx_Tx */
    gpio_af_set(uart->tx_port, uart->tx_af, uart->tx_pin);

    /* connect port to USARTx_Rx */
    gpio_af_set(uart->rx_port, uart->rx_af, uart->rx_pin);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(uart->tx_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, uart->tx_pin);
    gpio_output_options_set(uart->tx_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, uart->tx_pin);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(uart->rx_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, uart->rx_pin);
    gpio_output_options_set(uart->rx_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, uart->rx_pin);

#else
    /* connect port to USARTx_Tx */
    gpio_init(uart->tx_port, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, uart->tx_pin);

    /* connect port to USARTx_Rx */
    gpio_init(uart->rx_port, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, uart->rx_pin);
#endif

    NVIC_SetPriority(uart->irqn, 0);
    NVIC_EnableIRQ(uart->irqn);
}

/**
  * @brief  uart configure
  * @param  serial, cfg
  * @retval None
  */
static rt_err_t gd32_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
	RT_ASSERT(serial != RT_NULL);
	struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;;
	RT_ASSERT(uart != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    gd32_uart_gpio_init(uart);

    usart_baudrate_set(uart->uart_periph, cfg->baud_rate);

    switch (cfg->data_bits)
    {
    case DATA_BITS_9:
        usart_word_length_set(uart->uart_periph, USART_WL_9BIT);
        break;

    default:
        usart_word_length_set(uart->uart_periph, USART_WL_8BIT);
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        usart_stop_bit_set(uart->uart_periph, USART_STB_2BIT);
        break;
    default:
        usart_stop_bit_set(uart->uart_periph, USART_STB_1BIT);
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        usart_parity_config(uart->uart_periph, USART_PM_ODD);
        break;
    case PARITY_EVEN:
        usart_parity_config(uart->uart_periph, USART_PM_EVEN);
        break;
    default:
        usart_parity_config(uart->uart_periph, USART_PM_NONE);
        break;
    }
	
#ifdef RT_SERIAL_USING_DMA
    if (!(serial->parent.open_flag & RT_DEVICE_OFLAG_OPEN)) 
	{
        uart->dma_rx->remaining_cnt = cfg->bufsz;
    }
#endif
	
    usart_receive_config(uart->uart_periph, USART_RECEIVE_ENABLE);
    usart_transmit_config(uart->uart_periph, USART_TRANSMIT_ENABLE);
    usart_enable(uart->uart_periph);

    return RT_EOK;
}

/**
  * @brief  uart control
  * @param  serial, arg
  * @retval None
  */
static rt_err_t gd32_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
	RT_ASSERT(serial != RT_NULL);
	struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;
	
#ifdef RT_SERIAL_USING_DMA
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;
#endif
    RT_ASSERT(uart != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irqn);
        /* disable interrupt */
        usart_interrupt_disable(uart->uart_periph, USART_INT_RBNE);
#ifdef RT_SERIAL_USING_DMA
        /* disable DMA */
        if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX)
        {
			NVIC_DisableIRQ(uart->dma_rx->dma_irqn);
			dma_interrupt_disable(uart->dma_rx->dma_periph, uart->dma_rx->channel, DMA_CHXCTL_FTFIE|DMA_CHXCTL_HTFIE);
        }
        else if(ctrl_arg == RT_DEVICE_FLAG_DMA_TX)
        {
			NVIC_DisableIRQ(uart->dma_tx->dma_irqn);
			dma_interrupt_disable(uart->dma_tx->dma_periph, uart->dma_tx->channel, DMA_CHXCTL_FTFIE|DMA_CHXCTL_HTFIE);
        }
#endif
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irqn);
        /* enable interrupt */
        usart_interrupt_enable(uart->uart_periph, USART_INT_RBNE);
#ifdef RT_SERIAL_USING_DMA
        /* enable DMA */
        if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX)
        {
//			usart_flag_clear(uart->uart_periph, USART_FLAG_IDLE);
//			dma_interrupt_flag_clear(uart->dma_rx->dma_periph, uart->dma_rx->channel, DMA_INT_FLAG_FTF|DMA_INT_FLAG_HTF);
//			/* enable interrupt */
//			usart_interrupt_enable(uart->uart_periph, USART_INT_IDLE);
//			/* enable DMA rx irq */
//			NVIC_EnableIRQ(uart->dma_rx->dma_irqn);
//			/* enable DMA interrupt */
//			dma_interrupt_enable(uart->dma_rx->dma_periph, uart->dma_rx->channel, DMA_CHXCTL_FTFIE|DMA_CHXCTL_HTFIE);
        }
        else if(ctrl_arg == RT_DEVICE_FLAG_DMA_TX)
        {
//			/* clean TC flag */
//			usart_flag_clear(uart->uart_periph, USART_FLAG_TC);
//			/* clean DMA Full flag */
//			dma_interrupt_flag_clear(uart->dma_tx->dma_periph, uart->dma_tx->channel, DMA_INT_FLAG_FTF);
//			/* enable DMA Tx irq */
//			NVIC_EnableIRQ(uart->dma_tx->dma_irqn);
//			/* enable interrupt */
//			usart_interrupt_enable(uart->uart_periph, USART_INT_TC);
//			dma_interrupt_enable(uart->dma_tx->dma_periph, uart->dma_tx->channel, DMA_CHXCTL_FTFIE);
        }
#endif
        break;
#ifdef RT_SERIAL_USING_DMA
    case RT_DEVICE_CTRL_CONFIG:
        gd32_dma_config(serial, ctrl_arg);
        break;
#endif
	case RT_DEVICE_CTRL_CLOSE:
		
        break;
    }

    return RT_EOK;
}

/**
  * @brief  uart put char
  * @param  serial, ch
  * @retval None
  */
static int gd32_uart_putc(struct rt_serial_device *serial, char ch)
{
	RT_ASSERT(serial != RT_NULL);
    struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    usart_data_transmit(uart->uart_periph, ch);
    while((usart_flag_get(uart->uart_periph, USART_FLAG_TBE) == RESET));

    return RT_EOK;
}

/**
  * @brief  uart get char
  * @param  serial
  * @retval None
  */
static int gd32_uart_getc(struct rt_serial_device *serial)
{
    int ch;
    RT_ASSERT(serial != RT_NULL);
	struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    ch = -1;
    if (usart_flag_get(uart->uart_periph, USART_FLAG_RBNE) != RESET)
        ch = usart_data_receive(uart->uart_periph);
    return ch;
}

#ifdef RT_SERIAL_USING_DMA
static rt_ssize_t gd32_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
	RT_ASSERT(serial != RT_NULL);
    struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;
	RT_ASSERT(uart != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    if (size == 0)
    {
        return 0;
    }

    if (RT_SERIAL_DMA_TX == direction)
    {
		dma_channel_disable(uart->dma_tx->dma_periph, uart->dma_tx->channel);
		dma_memory_address_config(uart->dma_tx->dma_periph, uart->dma_tx->channel, DMA_MEMORY_0, (rt_uint32_t)buf);
        dma_transfer_number_config(uart->dma_tx->dma_periph, uart->dma_tx->channel, size);    	
        dma_channel_enable(uart->dma_tx->dma_periph, uart->dma_tx->channel);
		return size;
    }
    return 0;
}
#endif

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void GD32_UART_IRQHandler(struct rt_serial_device *serial)
{
    RT_ASSERT(serial != RT_NULL);
	struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;
	RT_ASSERT(uart != RT_NULL);

    /* UART in mode Receiver -------------------------------------------------*/
    if ((usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_RBNE) != RESET) &&
            (usart_flag_get(uart->uart_periph, USART_FLAG_RBNE) != RESET))
    {
        /* Clear RXNE interrupt flag */
		rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        usart_flag_clear(uart->uart_periph, USART_FLAG_RBNE);
    }
	else if(RESET != usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_RBNE_ORERR)) 
    {   
        usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_RBNE_ORERR);
		usart_data_receive(uart->uart_periph);
	}
#ifdef RT_SERIAL_USING_DMA
	else if ((usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_IDLE) != RESET) &&
            (usart_flag_get(uart->uart_periph, USART_FLAG_IDLE) != RESET))
    {
        /* Clear IDLE interrupt flag */
		usart_flag_clear(uart->uart_periph, USART_FLAG_IDLE);
		dma_recv_isr(serial, UART_RX_DMA_IT_IDLE_FLAG);
		/* must read data to clear flag, use api is invalid */
		usart_data_receive(uart->uart_periph);
    }
	else if ((usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_TC) != RESET) &&
            (usart_flag_get(uart->uart_periph, USART_FLAG_TC) != RESET))
    {
        if ((serial->parent.open_flag & RT_DEVICE_FLAG_DMA_TX) != 0)
        {
            _dma_tx_complete(serial);
        }
        usart_flag_clear(uart->uart_periph, USART_FLAG_TC);
    }
	
	if(dma_interrupt_flag_get(uart->dma_rx->dma_periph, uart->dma_rx->channel, DMA_INT_FLAG_FTF) != RESET) 
	{
	 	 /* clear DMA a channel flag */
		dma_interrupt_flag_clear(uart->dma_rx->dma_periph, uart->dma_rx->channel, DMA_INT_FLAG_FTF);
		dma_recv_isr(serial, UART_RX_DMA_IT_TC_FLAG);
	}
	else if(dma_interrupt_flag_get(uart->dma_rx->dma_periph, uart->dma_rx->channel, DMA_INT_FLAG_HTF) != RESET)
	{
		/* clear DMA a channel flag */
		dma_interrupt_flag_clear(uart->dma_rx->dma_periph, uart->dma_rx->channel, DMA_INT_FLAG_HTF);
		dma_recv_isr(serial, UART_RX_DMA_IT_HT_FLAG);
	}
	else if(dma_interrupt_flag_get(uart->dma_tx->dma_periph, uart->dma_tx->channel, DMA_INTF_FTFIF) != RESET)
	{
		 /* clear DMA a channel flag */
		dma_interrupt_flag_clear(uart->dma_tx->dma_periph, uart->dma_tx->channel, DMA_INTF_FTFIF);
	}
	else if(dma_interrupt_flag_get(uart->dma_tx->dma_periph, uart->dma_tx->channel, DMA_INT_FLAG_HTF) != RESET)
	{
		 /* clear DMA a channel flag */
		dma_interrupt_flag_clear(uart->dma_tx->dma_periph, uart->dma_tx->channel, DMA_INT_FLAG_HTF);
	}
#endif
}

static const struct rt_uart_ops gd32_uart_ops =
{
    .configure = gd32_uart_configure,
    .control = gd32_uart_control,
    .putc = gd32_uart_putc,
    .getc = gd32_uart_getc,
#ifdef RT_SERIAL_USING_DMA
    .dma_transmit = gd32_dma_transmit,
#else
	RT_NULL
#endif
};

/**
  * @brief  uart init
  * @param  None
  * @retval None
  */
int rt_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    int i;

    int result;

    for (i = 0; i < sizeof(uart_obj) / sizeof(uart_obj[0]); i++)
    {
        /* init UART object */
        uart_obj[i].serial->ops    = &gd32_uart_ops;
        uart_obj[i].serial->config = config;
		
        /* register UART1 device */
        result = rt_hw_serial_register(uart_obj[i].serial,
									   uart_obj[i].device_name,
#ifdef RT_SERIAL_USING_DMA
									   RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | uart_obj[i].dma_flag,
#else
									   RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
#endif
								       (void *)&uart_obj[i]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);
#endif

