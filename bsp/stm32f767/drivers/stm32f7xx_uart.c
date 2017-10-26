/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-25     ZYH      first implementation
 */

#include <rtdevice.h>
#include <stm32f7xx_hal.h>
static void RCC_DMA1_CLK_ENABLE(void)
{
    __HAL_RCC_DMA1_CLK_ENABLE();
}
static void RCC_USART3_CLK_ENABLE(void)
{
    __HAL_RCC_USART3_CLK_ENABLE();
}

typedef struct stm32_uart_dma
{
    DMA_Stream_TypeDef *Instance;
    uint32_t Channel;
    IRQn_Type irq;
    void (*rcc)(void);
		DMA_HandleTypeDef hdma;
} *stm32_uart_dma_t;

typedef struct stm32_uart
{
    UART_HandleTypeDef *huart;
    IRQn_Type irq;
    struct stm32_uart_dma dma_tx;
    struct stm32_uart_dma dma_rx;
    void (*rcc)(void);
} *stm32_uart_t;

static void stm32_uart_dma_config(struct rt_serial_device *serial,
                                  rt_uint32_t ctrl_arg)
{
    DMA_HandleTypeDef * hdma;
    stm32_uart_t stm32_uart;
    stm32_uart = (stm32_uart_t)serial->parent.user_data;
    switch (ctrl_arg)
    {
    case RT_DEVICE_FLAG_DMA_RX:
				stm32_uart->dma_rx.rcc();
        HAL_NVIC_SetPriority(stm32_uart->dma_rx.irq, 5, 0);
        HAL_NVIC_EnableIRQ(stm32_uart->dma_rx.irq);
				hdma = &stm32_uart->dma_rx.hdma;
        hdma->Instance = stm32_uart->dma_rx.Instance;
        hdma->Init.Channel = stm32_uart->dma_rx.Channel;
        hdma->Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma->Init.Mode = DMA_CIRCULAR;
				hdma->Init.PeriphInc = DMA_PINC_DISABLE;
				hdma->Init.MemInc = DMA_MINC_ENABLE;
				hdma->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
				hdma->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
				hdma->Init.Priority = DMA_PRIORITY_LOW;
				hdma->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
				HAL_DMA_Init(hdma);
				
        __HAL_LINKDMA(stm32_uart->huart, hdmarx, (*hdma));
        break;
    case RT_DEVICE_FLAG_DMA_TX:
        /* USART3_TX Init */
				stm32_uart->dma_tx.rcc();
        HAL_NVIC_SetPriority(stm32_uart->dma_tx.irq, 0, 0);
        HAL_NVIC_EnableIRQ(stm32_uart->dma_tx.irq);
				hdma = &stm32_uart->dma_tx.hdma;
        hdma->Instance = stm32_uart->dma_tx.Instance;
        hdma->Init.Channel = stm32_uart->dma_tx.Channel;
        hdma->Init.Direction = DMA_MEMORY_TO_PERIPH;
        hdma->Init.Mode = DMA_NORMAL;//DMA_NORMAL
				hdma->Init.PeriphInc = DMA_PINC_DISABLE;
				hdma->Init.MemInc = DMA_MINC_ENABLE;
				hdma->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
				hdma->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
				hdma->Init.Priority = DMA_PRIORITY_LOW;
				hdma->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
				HAL_DMA_Init(hdma);
        __HAL_LINKDMA(stm32_uart->huart, hdmatx, (*hdma));
				HAL_NVIC_SetPriority(stm32_uart->irq, 5, 0);
        HAL_NVIC_EnableIRQ(stm32_uart->irq);
        break;
    }
		
}

static rt_err_t stm32_uart_configure(struct rt_serial_device *serial,
                                     struct serial_configure *cfg)
{
    UART_HandleTypeDef *huart;
    huart = ((stm32_uart_t)serial->parent.user_data)->huart;
    ((stm32_uart_t)serial->parent.user_data)->rcc();
    huart->Init.BaudRate = cfg->baud_rate;
    switch (cfg->data_bits)
    {
    case DATA_BITS_7:
        huart->Init.WordLength = UART_WORDLENGTH_7B;
        break;
    case DATA_BITS_8:
        huart->Init.WordLength = UART_WORDLENGTH_8B;
        break;
    case DATA_BITS_9:
        huart->Init.WordLength = UART_WORDLENGTH_9B;
        break;
    default:
        return RT_ERROR;
    }
    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        huart->Init.StopBits = UART_STOPBITS_1;
        break;
    case STOP_BITS_2:
        huart->Init.StopBits = UART_STOPBITS_2;
        break;
    default:
        return RT_ERROR;
    }
    switch (cfg->parity)
    {
    case PARITY_NONE:
        huart->Init.Parity = UART_PARITY_NONE;
        break;
    case PARITY_ODD:
        huart->Init.Parity = UART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        huart->Init.Parity = UART_PARITY_EVEN;
        break;
    default:
        return RT_ERROR;
    }
    huart->Init.Mode = UART_MODE_TX_RX;
    huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart->Init.OverSampling = UART_OVERSAMPLING_16;
    huart->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    if (HAL_UART_Init(huart) != HAL_OK)
    {
        return RT_ERROR;
    }
    return RT_EOK;
}
static rt_err_t stm32_uart_control(struct rt_serial_device *serial, int cmd,
                                   void *arg)
{
    stm32_uart_t stm32_uart;
    stm32_uart = (stm32_uart_t)serial->parent.user_data;
    rt_uint32_t ctrl_arg = (rt_uint32_t)(arg);
    RT_ASSERT(serial != RT_NULL);
    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        HAL_NVIC_DisableIRQ(stm32_uart->irq);
				__HAL_UART_DISABLE_IT(stm32_uart->huart, UART_IT_RXNE);
        break;
    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        HAL_NVIC_SetPriority(stm32_uart->irq, 5, 0);
        HAL_NVIC_EnableIRQ(stm32_uart->irq);
				__HAL_UART_ENABLE_IT(stm32_uart->huart, UART_IT_RXNE);
        break;
    /* USART config */
    case RT_DEVICE_CTRL_CONFIG:
        stm32_uart_dma_config(serial, ctrl_arg);
        break;
    }
    return RT_EOK;
}
static int stm32_uart_putc(struct rt_serial_device *serial, char c)
{
		stm32_uart_t stm32_uart;
    stm32_uart = (stm32_uart_t)serial->parent.user_data;
		if (serial->parent.open_flag & RT_DEVICE_FLAG_INT_TX)
    {
			return HAL_UART_Transmit_IT(stm32_uart->huart, (uint8_t *)&c, 1) == HAL_OK ?1:-1;
		}
		else
		{
			while((__HAL_UART_GET_FLAG(stm32_uart->huart, UART_FLAG_TXE) == RESET));
			HAL_UART_Transmit(stm32_uart->huart, (uint8_t *)&c, 1,0xff);
		}
		
    return 1;
}
static int stm32_uart_getc(struct rt_serial_device *serial)
{
		int ch;
		stm32_uart_t stm32_uart;
    stm32_uart = (stm32_uart_t)serial->parent.user_data;
	  ch = -1;
    if (stm32_uart->huart->Instance->ISR & UART_FLAG_RXNE)
    {
        ch = stm32_uart->huart->Instance->RDR & 0xff;
    }
    return ch;
}
static rt_size_t stm32_uart_dma_transmit(struct rt_serial_device *serial,
        rt_uint8_t *buf, rt_size_t size,
        int direction)
{
    stm32_uart_t stm32_uart;
    stm32_uart = (stm32_uart_t)serial->parent.user_data;
    switch (direction)
    {
    case RT_SERIAL_DMA_RX:
        HAL_UART_Receive_DMA(stm32_uart->huart, buf, size);
        break;
    case RT_SERIAL_DMA_TX:
				SCB_CleanDCache();
        HAL_UART_Transmit_DMA(stm32_uart->huart, buf, size);
        break;
    }
    return size;
}
static struct rt_uart_ops stm32_uart_ops =
{
    stm32_uart_configure, stm32_uart_control,      stm32_uart_putc,
    stm32_uart_getc,      stm32_uart_dma_transmit,
};

#ifdef RT_USING_UART3
static UART_HandleTypeDef huart3 = {.Instance = USART3};
static struct stm32_uart uart3 = {.huart = &huart3,
           .irq = USART3_IRQn,
            .dma_tx = {.Instance = DMA1_Stream4,
                       .Channel = DMA_CHANNEL_7,
                       .irq = DMA1_Stream4_IRQn,
                       .rcc = RCC_DMA1_CLK_ENABLE
                      },
             .dma_rx = {.Instance = DMA1_Stream1,
                        .Channel = DMA_CHANNEL_4,
                        .irq = DMA1_Stream1_IRQn,
                        .rcc = RCC_DMA1_CLK_ENABLE
                       },
              .rcc = RCC_USART3_CLK_ENABLE
};

static struct rt_serial_device serial3;

static void MX_USART3_UART_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
void DMA1_Stream1_IRQHandler(void)
{
    /* USER CODE BEGIN DMA1_Stream1_IRQn 0 */
rt_interrupt_enter();
    /* USER CODE END DMA1_Stream1_IRQn 0 */
    HAL_DMA_IRQHandler(huart3.hdmarx);
    /* USER CODE BEGIN DMA1_Stream1_IRQn 1 */
 rt_interrupt_leave();
    /* USER CODE END DMA1_Stream1_IRQn 1 */
}

/**
 * @brief This function handles DMA1 stream4 global interrupt.
 */
void DMA1_Stream4_IRQHandler(void)
{
    /* USER CODE BEGIN DMA1_Stream4_IRQn 0 */
rt_interrupt_enter();
    /* USER CODE END DMA1_Stream4_IRQn 0 */
    HAL_DMA_IRQHandler(huart3.hdmatx);
    /* USER CODE BEGIN DMA1_Stream4_IRQn 1 */
 rt_interrupt_leave();
    /* USER CODE END DMA1_Stream4_IRQn 1 */
}

/**
 * @brief This function handles USART3 global interrupt.
 */
void USART3_IRQHandler(void)
{
    /* USER CODE BEGIN USART3_IRQn 0 */
rt_interrupt_enter();
		stm32_uart_t stm32_uart;
    stm32_uart = (stm32_uart_t)serial3.parent.user_data;
    /* USER CODE END USART3_IRQn 0 */
		if ((__HAL_UART_GET_IT(stm32_uart->huart, UART_IT_RXNE) != RESET) && (__HAL_UART_GET_IT_SOURCE(stm32_uart->huart, UART_IT_RXNE) != RESET))
    {
        rt_hw_serial_isr(&serial3, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        __HAL_UART_SEND_REQ(stm32_uart->huart, UART_RXDATA_FLUSH_REQUEST);
    }else{
			HAL_UART_IRQHandler(stm32_uart->huart);
		}
    /* USER CODE BEGIN USART3_IRQn 1 */
 rt_interrupt_leave();
    /* USER CODE END USART3_IRQn 1 */
}
#endif

int rt_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate = BAUD_RATE_115200;
    //config.bufsz = 0;
#ifdef RT_USING_UART3
    MX_USART3_UART_Init();
    serial3.ops = &stm32_uart_ops;
    serial3.config = config;
    rt_hw_serial_register(&serial3, "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_DMA_RX |
                          RT_DEVICE_FLAG_DMA_TX | RT_DEVICE_FLAG_INT_RX |RT_DEVICE_FLAG_INT_TX,
                          &uart3);
#endif
    return 0;
}

INIT_BOARD_EXPORT(rt_hw_usart_init);

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
#ifdef RT_USING_UART3
		if(serial3.parent.open_flag & RT_DEVICE_FLAG_DMA_TX)
		{
			rt_hw_serial_isr(&serial3, RT_SERIAL_EVENT_TX_DMADONE);
		}else if(serial3.parent.open_flag & RT_DEVICE_FLAG_INT_TX){
			rt_hw_serial_isr(&serial3, RT_SERIAL_EVENT_TX_DONE);
		}
#endif
    }
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
#ifdef RT_USING_UART3
			if(serial3.parent.open_flag & RT_DEVICE_FLAG_DMA_RX)
			{
				rt_hw_serial_isr(&serial3, RT_SERIAL_EVENT_RX_DMADONE);
			}
        
#endif
    }
}
