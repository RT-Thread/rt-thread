/*
 * File      : drv_spi.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-06-05     tanek        first implementation.
 */
 
#include "drv_spi.h"

#include <board.h>
#include <finsh.h>

//#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTF(...)   rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)   
#endif

/* private rt-thread spi ops function */
static rt_err_t configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration);
static rt_uint32_t xfer(struct rt_spi_device* device, struct rt_spi_message* message);

static struct rt_spi_ops stm32_spi_ops =
{
    configure,
    xfer
};

#ifdef SPI_USE_DMA
static uint8_t dummy = 0xFF;
static void DMA_RxConfiguration(struct rt_spi_bus * spi_bus,
                                struct rt_spi_message* message)
{
    struct stm32f4_spi *f4_spi = (struct stm32f4_spi *)spi_bus->parent.user_data;
    
    DMA_HandleTypeDef * hdma_tx = &f4_spi->hdma_tx;
    DMA_HandleTypeDef * hdma_rx = &f4_spi->hdma_rx;
     
    HAL_DMA_DeInit(hdma_tx);
    HAL_DMA_DeInit(hdma_rx);
        
    /* Check if the DMA Stream is disabled before enabling it.
       Note that this step is useful when the same Stream is used multiple times:
       enabled, then disabled then re-enabled... In this case, the DMA Stream disable
       will be effective only at the end of the ongoing data transfer and it will
       not be possible to re-configure it before making sure that the Enable bit
       has been cleared by hardware. If the Stream is used only once, this step might
       be bypassed. */    
    while (hdma_tx->Instance->CR & DMA_SxCR_EN);
    while (hdma_rx->Instance->CR & DMA_SxCR_EN);

    if(message->recv_buf != RT_NULL)
    {
        hdma_rx->Init.MemInc = DMA_MINC_ENABLE;
    }
    else
    {
        message->recv_buf = &dummy;
        hdma_rx->Init.MemInc = DMA_MINC_DISABLE;
    }
    HAL_DMA_Init(hdma_rx);
    
    __HAL_LINKDMA(&f4_spi->spi_handle, hdmarx, f4_spi->hdma_rx);
        
    if(message->send_buf != RT_NULL)
    {
        hdma_tx->Init.MemInc = DMA_MINC_ENABLE;
    }
    else
    {
        dummy = 0xFF;
        message->send_buf = &dummy;
        hdma_tx->Init.MemInc = DMA_MINC_DISABLE;
    }
    HAL_DMA_Init(hdma_tx);
    
    __HAL_LINKDMA(&f4_spi->spi_handle, hdmatx, f4_spi->hdma_tx);
    
    /* NVIC configuration for DMA transfer complete interrupt*/
    HAL_NVIC_SetPriority(f4_spi->hdma_tx_irq, 0, 1);
    HAL_NVIC_EnableIRQ(f4_spi->hdma_tx_irq);

    /* NVIC configuration for DMA transfer complete interrupt*/
    HAL_NVIC_SetPriority(f4_spi->hdma_rx_irq, 0, 0);   
    HAL_NVIC_EnableIRQ(f4_spi->hdma_rx_irq);
    
}
#endif

static rt_err_t configure(struct rt_spi_device* device,
                          struct rt_spi_configuration* configuration)
{
    struct rt_spi_bus * spi_bus = (struct rt_spi_bus *)device->bus;	
    struct stm32f4_spi *f4_spi = (struct stm32f4_spi *)spi_bus->parent.user_data;
	SPI_HandleTypeDef * SpiHandle = &f4_spi->spi_handle;

	RT_ASSERT(device != RT_NULL);
	RT_ASSERT(configuration != RT_NULL);

    /* data_width */
    if(configuration->data_width <= 8)
    {
        SpiHandle->Init.DataSize = SPI_DATASIZE_8BIT;
    }
    else if(configuration->data_width <= 16)
    {
        SpiHandle->Init.DataSize = SPI_DATASIZE_16BIT;
    }
    else
    {
        return RT_EIO;
    }

    /* baudrate */
    {
        uint32_t SPI_APB_CLOCK;
        uint32_t max_hz;

        max_hz = configuration->max_hz;

        DEBUG_PRINTF("sys   freq: %d\n", HAL_RCC_GetSysClockFreq());
        DEBUG_PRINTF("pclk2 freq: %d\n", HAL_RCC_GetPCLK2Freq());

        SPI_APB_CLOCK = HAL_RCC_GetPCLK2Freq();

        if(max_hz >= SPI_APB_CLOCK/2)
        {
            SpiHandle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
        }
        else if(max_hz >= SPI_APB_CLOCK/4)
        {
            SpiHandle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
        }
        else if(max_hz >= SPI_APB_CLOCK/8)
        {
            SpiHandle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
        }
        else if(max_hz >= SPI_APB_CLOCK/16)
        {
            SpiHandle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
        }
        else if(max_hz >= SPI_APB_CLOCK/32)
        {
            SpiHandle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
        }
        else if(max_hz >= SPI_APB_CLOCK/64)
        {
            SpiHandle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
        }
        else if(max_hz >= SPI_APB_CLOCK/128)
        {
            SpiHandle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
        }
        else
        {
            /*  min prescaler 256 */
            SpiHandle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
        }
    } /* baudrate */

    /* CPOL */
    if(configuration->mode & RT_SPI_CPOL)
    {
        SpiHandle->Init.CLKPolarity = SPI_POLARITY_HIGH;
    }
    else
    {
        SpiHandle->Init.CLKPolarity = SPI_POLARITY_LOW;
    }
    /* CPHA */
    if(configuration->mode & RT_SPI_CPHA)
    {
		SpiHandle->Init.CLKPhase = SPI_PHASE_2EDGE;
    }
    else
    {
		SpiHandle->Init.CLKPhase = SPI_PHASE_1EDGE;
    }
    /* MSB or LSB */
    if(configuration->mode & RT_SPI_MSB)
    {
        SpiHandle->Init.FirstBit = SPI_FIRSTBIT_MSB;
    }
    else
    {
        SpiHandle->Init.FirstBit = SPI_FIRSTBIT_LSB;
    }
    SpiHandle->Init.Direction = SPI_DIRECTION_2LINES;
    SpiHandle->Init.Mode = SPI_MODE_MASTER;
    SpiHandle->Init.NSS  = SPI_NSS_SOFT;
	SpiHandle->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SpiHandle->Init.TIMode = SPI_TIMODE_DISABLE;

    /* init SPI */
    if (HAL_SPI_Init(SpiHandle) != HAL_OK)
	{
		return RT_ERROR;
	}
    /* Enable SPI_MASTER */
	__HAL_SPI_ENABLE(SpiHandle);
    
    DEBUG_PRINTF("spi configuration\n");

    return RT_EOK;
};

static rt_uint32_t xfer(struct rt_spi_device* device, struct rt_spi_message* message)
{
    struct rt_spi_bus * stm32_spi_bus = (struct rt_spi_bus *)device->bus;
    struct stm32f4_spi *f4_spi = (struct stm32f4_spi *)stm32_spi_bus->parent.user_data;
    struct rt_spi_configuration * config = &device->config;
    SPI_TypeDef * SPI = f4_spi->spi_handle.Instance;
    struct stm32_spi_cs * stm32_spi_cs = device->parent.user_data;
    rt_uint32_t size = message->length;

	RT_ASSERT(device != NULL);
	RT_ASSERT(message != NULL);
	
    /* take CS */
    if(message->cs_take)
    {
        HAL_GPIO_WritePin(stm32_spi_cs->GPIOx, stm32_spi_cs->GPIO_Pin, GPIO_PIN_RESET);
    }

#ifdef SPI_USE_DMA
    if(message->length > 32)
    {
        if(config->data_width <= 8)
        {
            HAL_StatusTypeDef state; 
            DEBUG_PRINTF("spi dma transfer start\n");
            DMA_RxConfiguration(stm32_spi_bus, message);
            DEBUG_PRINTF("dma configuration finish , send buf %X, rec buf %X, length: %d\n", 
                    (uint32_t)message->send_buf, (uint32_t)message->recv_buf, message->length);
            
            state = HAL_SPI_TransmitReceive_DMA(&f4_spi->spi_handle, 
                                                (uint8_t*)message->send_buf, 
                                                (uint8_t*)message->recv_buf, 
                                                message->length);
            if (state != HAL_OK) 
            {
                DEBUG_PRINTF("spi flash configuration error : %d\n", state);
                message->length = 0;
                //while(1);
            }
            else
            {
                DEBUG_PRINTF("spi dma transfer finish\n");            
            }
            
            while (HAL_SPI_GetState(&f4_spi->spi_handle) != HAL_SPI_STATE_READY);
            DEBUG_PRINTF("spi get state finish\n");
        }
        else
        {
            // Todo 
        }
    }
    else
#endif
    {
        if(config->data_width <= 8)
        {
            const rt_uint8_t * send_ptr = message->send_buf;
            rt_uint8_t * recv_ptr = message->recv_buf;

            while(size--)
            {
                rt_uint8_t data = 0xFF;

                if(send_ptr != RT_NULL)
                {
                    data = *send_ptr++;
                }
                
                // Todo: replace register read/write by stm32f4 lib
                //Wait until the transmit buffer is empty
                while ((SPI->SR & SPI_FLAG_TXE) == RESET);
                // Send the byte
				SPI->DR = data;

                //Wait until a data is received
                while ((SPI->SR & SPI_FLAG_RXNE) == RESET);
                // Get the received data
                data = SPI->DR;

                if(recv_ptr != RT_NULL)
                {
                    *recv_ptr++ = data;
                }
            }
        }
        else if(config->data_width <= 16)
        {
            const rt_uint16_t * send_ptr = message->send_buf;
            rt_uint16_t * recv_ptr = message->recv_buf;

            while(size--)
            {
                rt_uint16_t data = 0xFF;

                if(send_ptr != RT_NULL)
                {
                    data = *send_ptr++;
                }

                //Wait until the transmit buffer is empty
                while ((SPI->SR & SPI_FLAG_TXE) == RESET);
                // Send the byte
                SPI->DR = data;

                //Wait until a data is received
                while ((SPI->SR & SPI_FLAG_RXNE) == RESET);
                // Get the received data
                data = SPI->DR;

                if(recv_ptr != RT_NULL)
                {
                    *recv_ptr++ = data;
                }
            }
        }
    }

    /* release CS */
    if(message->cs_release)
    {
        //GPIO_SetBits(stm32_spi_cs->GPIOx, stm32_spi_cs->GPIO_Pin);
		HAL_GPIO_WritePin(stm32_spi_cs->GPIOx, stm32_spi_cs->GPIO_Pin, GPIO_PIN_SET);
    }

    return message->length;
};





#ifdef RT_USING_SPI1

static struct stm32f4_spi stm32f4_spi1 = 
{
    /* .spi_handle = */{
        /* .Instance = */ SPI1,
    },
    /* .hdma_rx = */ {   
        DMA2_Stream2,
        DMA_CHANNEL_3,
    },
    /* .hdma_rx_irq = */ DMA2_Stream2_IRQn,

    /* .hdma_tx = */{
        DMA2_Stream3,
        DMA_CHANNEL_3,
    },
    /* .hdma_tx_irq = */ DMA2_Stream3_IRQn,
};

static struct rt_spi_bus spi1_bus;

/**
  * @brief  This function handles DMA Rx interrupt request.
  * @param  None
  * @retval None  
  */
void DMA2_Stream2_IRQHandler(void)
{
  HAL_DMA_IRQHandler(stm32f4_spi1.spi_handle.hdmarx);
}    
/**
  * @brief  This function handles DMA Tx interrupt request.  
  * @param  None
  * @retval None    
  */
void DMA2_Stream3_IRQHandler(void)
{
    HAL_DMA_IRQHandler(stm32f4_spi1.spi_handle.hdmatx);
}

#endif

#ifdef RT_USING_SPI2

struct stm32f4_spi stm32f4_spi2 = 
{
    /* .spi_handle = */{
        /* .Instance = */ SPI2,
    },
    /* .hdma_rx = */ {   
        DMA1_Stream3,
        DMA_CHANNEL_0,
    },
    /* .hdma_rx_irq = */ DMA1_Stream3_IRQn,

    /* .hdma_tx = */{
        DMA1_Stream4,
        DMA_CHANNEL_0,
    },
    /* .hdma_tx_irq = */ DMA1_Stream4_IRQn,
};

static struct rt_spi_bus spi2_bus;

/**
  * @brief  This function handles DMA Rx interrupt request.
  * @param  None
  * @retval None  
  */
void DMA1_Stream3_IRQHandler(void)
{
  HAL_DMA_IRQHandler(stm32f4_spi2.spi_handle.hdmarx);
}    
/**
  * @brief  This function handles DMA Tx interrupt request.  
  * @param  None
  * @retval None    
  */
void DMA1_Stream4_IRQHandler(void)
{
    HAL_DMA_IRQHandler(stm32f4_spi2.spi_handle.hdmatx);
}

#endif

#ifdef RT_USING_SPI3

struct stm32f4_spi stm32f4_spi3 = 
{
    /* .spi_handle = */{
        /* .Instance = */ SPI3,
    },
    /* .hdma_rx = */ {   
        DMA1_Stream0,
        DMA_CHANNEL_0,
    },
    /* .hdma_rx_irq = */ DMA1_Stream0_IRQn,

    /* .hdma_tx = */{
        DMA1_Stream2,
        DMA_CHANNEL_0,
    },
    /* .hdma_tx_irq = */ DMA1_Stream2_IRQn,
};

static struct rt_spi_bus spi3_bus;


/**
  * @brief  This function handles DMA Rx interrupt request.
  * @param  None
  * @retval None  
  */
void DMA1_Stream0_IRQHandler(void)
{
  HAL_DMA_IRQHandler(stm32f4_spi3.spi_handle.hdmarx);
}    
/**
  * @brief  This function handles DMA Tx interrupt request.  
  * @param  None
  * @retval None    
  */
void DMA1_Stream2_IRQHandler(void)
{
    HAL_DMA_IRQHandler(stm32f4_spi3.spi_handle.hdmatx);
}

#endif

#ifdef RT_USING_SPI4

struct stm32f4_spi stm32f4_spi4 = 
{
    /* .spi_handle = */{
        /* .Instance = */ SPI4,
    },
    /* .hdma_rx = */ {   
        DMA2_Stream0,
        DMA_CHANNEL_4,
    },
    /* .hdma_rx_irq = */ DMA2_Stream0_IRQn,

    /* .hdma_tx = */{
        DMA2_Stream1,
        DMA_CHANNEL_4,
    },
    /* .hdma_tx_irq = */ DMA2_Stream1_IRQn,
};

static struct rt_spi_bus spi4_bus;


/**
  * @brief  This function handles DMA Rx interrupt request.
  * @param  None
  * @retval None  
  */
void DMA2_Stream0_IRQHandler(void)
{
  HAL_DMA_IRQHandler(stm32f4_spi4.spi_handle.hdmarx);
}    
/**
  * @brief  This function handles DMA Tx interrupt request.  
  * @param  None
  * @retval None    
  */
void DMA2_Stream1_IRQHandler(void)
{
    HAL_DMA_IRQHandler(stm32f4_spi4.spi_handle.hdmatx);
}

#endif

#ifdef RT_USING_SPI5

struct stm32f4_spi stm32f4_spi5 = 
{
    /* .spi_handle = */{
        /* .Instance = */ SPI5,
    },
    /* .hdma_rx = */ {   
        DMA2_Stream3,
        DMA_CHANNEL_2,
    },
    /* .hdma_rx_irq = */ DMA2_Stream3_IRQn,

    /* .hdma_tx = */{
        DMA2_Stream4,
        DMA_CHANNEL_2,
    },
    /* .hdma_tx_irq = */ DMA2_Stream4_IRQn,
};

static struct rt_spi_bus spi5_bus;


/**
  * @brief  This function handles DMA Rx interrupt request.
  * @param  None
  * @retval None  
  */
void DMA2_Stream3_IRQHandler(void)
{
  HAL_DMA_IRQHandler(stm32f4_spi5.spi_handle.hdmarx);
}    
/**
  * @brief  This function handles DMA Tx interrupt request.  
  * @param  None
  * @retval None    
  */
void DMA2_Stream4_IRQHandler(void)
{
    HAL_DMA_IRQHandler(stm32f4_spi5.spi_handle.hdmatx);
}

#endif

#ifdef RT_USING_SPI6

struct stm32f4_spi stm32f4_spi6 = 
{
    /* .spi_handle = */{
        /* .Instance = */ SPI5,
    },
    /* .hdma_rx = */ {   
        DMA2_Stream6,
        DMA_CHANNEL_2,
    },
    /* .hdma_rx_irq = */ DMA2_Stream6_IRQn,

    /* .hdma_tx = */{
        DMA2_Stream5,
        DMA_CHANNEL_2,
    },
    /* .hdma_tx_irq = */ DMA2_Stream5_IRQn,
};

static struct rt_spi_bus spi6_bus;


/**
  * @brief  This function handles DMA Rx interrupt request.
  * @param  None
  * @retval None  
  */
void DMA2_Stream6_IRQHandler(void)
{
  HAL_DMA_IRQHandler(stm32f4_spi6.spi_handle.hdmarx);
}    
/**
  * @brief  This function handles DMA Tx interrupt request.  
  * @param  None
  * @retval None    
  */
void DMA2_Stream5_IRQHandler(void)
{
    HAL_DMA_IRQHandler(stm32f4_spi6.spi_handle.hdmatx);
}

#endif

/** \brief init and register stm32 spi bus.
 *
 * \param SPI: STM32 SPI, e.g: SPI1,SPI2,SPI3.
 * \param spi_bus_name: spi bus name, e.g: "spi1"
 * \return
 *
 */
rt_err_t stm32_spi_bus_register(SPI_TypeDef * SPI,
                            //struct stm32_spi_bus * stm32_spi,
                            const char * spi_bus_name)
{
    struct stm32f4_spi * p_spi_bus;
    struct rt_spi_bus *  spi_bus;
    
    RT_ASSERT(SPI != RT_NULL);
    //RT_ASSERT(stm32_spi != RT_NULL);
    RT_ASSERT(spi_bus_name != RT_NULL);
        
#ifdef RT_USING_SPI1
    if(SPI == SPI1)
    {
    #ifdef SPI_USE_DMA
        __HAL_RCC_DMA2_CLK_ENABLE();
        p_spi_bus = &stm32f4_spi1;
    #endif
        __HAL_RCC_SPI1_CLK_ENABLE();
        spi_bus = &spi1_bus;
    }
#endif
    
#ifdef RT_USING_SPI2
    if(SPI == SPI2)
    {
    #ifdef SPI_USE_DMA
        __HAL_RCC_DMA1_CLK_ENABLE();
        p_spi_bus = &stm32f4_spi2;
    #endif
        __HAL_RCC_SPI2_CLK_ENABLE();
        spi_bus = &spi2_bus;
    }
#endif

#ifdef RT_USING_SPI3
    if(SPI == SPI3)
    {
    	//stm32_spi->spi_handle.Instance = SPI3;
    #ifdef SPI_USE_DMA
        __HAL_RCC_DMA1_CLK_ENABLE();
        p_spi_bus = &stm32f4_spi3;
    #endif
		__HAL_RCC_SPI3_CLK_ENABLE();
        spi_bus = &spi3_bus;
    }
#endif
    
#ifdef RT_USING_SPI4
    if(SPI == SPI4)
    {
#ifdef SPI_USE_DMA
        __HAL_RCC_DMA2_CLK_ENABLE();
#endif
		__HAL_RCC_SPI4_CLK_ENABLE();
        spi_bus = &spi4_bus;
    }
#endif

#ifdef RT_USING_SPI5
    if(SPI == SPI5)
    {
    #ifdef SPI_USE_DMA
        __HAL_RCC_DMA2_CLK_ENABLE();
        p_spi_bus = &stm32f4_spi5;		
    #endif
		__HAL_RCC_SPI5_CLK_ENABLE();
        spi_bus = &spi5_bus;
    }
#endif
 
#ifdef RT_USING_SPI6
    if(SPI == SPI6)
    {
    #ifdef SPI_USE_DMA
        __HAL_RCC_DMA2_CLK_ENABLE();
        p_spi_bus = &stm32f4_spi5;
    #endif
		__HAL_RCC_SPI6_CLK_ENABLE();
        spi_bus = &spi6_bus;
    }
#endif

    if (    (SPI != SPI1) && (SPI != SPI2) && (SPI != SPI3)
        &&  (SPI != SPI4) && (SPI != SPI5) && (SPI != SPI6))
    {
        return RT_ENOSYS;
    }
    
    /* Configure the DMA handler for Transmission process */
    p_spi_bus->hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    p_spi_bus->hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
    //p_spi_bus->hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;
    p_spi_bus->hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    p_spi_bus->hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    p_spi_bus->hdma_tx.Init.Mode                = DMA_NORMAL;
    p_spi_bus->hdma_tx.Init.Priority            = DMA_PRIORITY_LOW;
    p_spi_bus->hdma_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         
    p_spi_bus->hdma_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    p_spi_bus->hdma_tx.Init.MemBurst            = DMA_MBURST_INC4;
    p_spi_bus->hdma_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
    
    p_spi_bus->hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    p_spi_bus->hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
    //p_spi_bus->hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;
    p_spi_bus->hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    p_spi_bus->hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    p_spi_bus->hdma_rx.Init.Mode                = DMA_NORMAL;
    p_spi_bus->hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;
    p_spi_bus->hdma_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         
    p_spi_bus->hdma_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    p_spi_bus->hdma_rx.Init.MemBurst            = DMA_MBURST_INC4;
    p_spi_bus->hdma_rx.Init.PeriphBurst         = DMA_PBURST_INC4;

    spi_bus->parent.user_data = &stm32f4_spi5;
    
    return rt_spi_bus_register(spi_bus, spi_bus_name, &stm32_spi_ops);
}
