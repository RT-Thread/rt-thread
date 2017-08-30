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

#ifdef RT_USING_SPI

#if !defined(RT_USING_SPI0) && !defined(RT_USING_SPI1) && \
    !defined(RT_USING_SPI2) && !defined(RT_USING_SPI3)  && \
    !defined(RT_USING_SPI4) && !defined(RT_USING_SPI5)
#error "Please define at least one SPIx"
#endif

//#define DEBUG

#define ARR_LEN(__N)      (sizeof(__N) / sizeof(__N[0]))

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

static rt_err_t configure(struct rt_spi_device* device,
                          struct rt_spi_configuration* configuration)
{
    struct rt_spi_bus * spi_bus = (struct rt_spi_bus *)device->bus;	
    struct stm32f4_spi *f4_spi = (struct stm32f4_spi *)spi_bus->parent.user_data;
    
    spi_parameter_struct spi_init_struct;

    uint32_t spi_periph = f4_spi->spi_periph;


	RT_ASSERT(device != RT_NULL);
	RT_ASSERT(configuration != RT_NULL);

    /* data_width */
    if(configuration->data_width <= 8)
    {
        spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
    }
    else if(configuration->data_width <= 16)
    {
        spi_init_struct.frame_size = SPI_FRAMESIZE_16BIT;
    }
    else
    {
        return RT_EIO;
    }

    /* baudrate */
    {
        rcu_clock_freq_enum spi_src;
        uint32_t spi_apb_clock;
        uint32_t max_hz;

        max_hz = configuration->max_hz;

        DEBUG_PRINTF("sys   freq: %d\n", HAL_RCC_GetSysClockFreq());
        DEBUG_PRINTF("pclk2 freq: %d\n", HAL_RCC_GetPCLK2Freq());
        DEBUG_PRINTF("max   freq: %d\n", max_hz);

        if (spi_periph == SPI1 || spi_periph == SPI2)
        {
            spi_src = CK_APB1;
        }
        else
        {
            spi_src = CK_APB2;
        }
        spi_apb_clock = rcu_clock_freq_get(spi_src);

        if(max_hz >= spi_apb_clock/2)
        {
            spi_init_struct.prescale = SPI_PSC_2;
        }
        else if (max_hz >= spi_apb_clock/4)
        {
            spi_init_struct.prescale = SPI_PSC_4;
        }
        else if (max_hz >= spi_apb_clock/8)
        {
            spi_init_struct.prescale = SPI_PSC_8;
        }
        else if (max_hz >= spi_apb_clock/16)
        {
            spi_init_struct.prescale = SPI_PSC_16;
        }
        else if (max_hz >= spi_apb_clock/32)
        {
            spi_init_struct.prescale = SPI_PSC_32;
        }
        else if (max_hz >= spi_apb_clock/64)
        {
            spi_init_struct.prescale = SPI_PSC_64;
        }
        else if (max_hz >= spi_apb_clock/128)
        {
            spi_init_struct.prescale = SPI_PSC_128;
        }
        else
        {
            /*  min prescaler 256 */
            spi_init_struct.prescale = SPI_PSC_256;
        }
    } /* baudrate */
    
    switch(configuration->mode)
    {
    case RT_SPI_MODE_0:
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
        break;
    case RT_SPI_MODE_1:
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_2EDGE;
        break;        
    case RT_SPI_MODE_2:
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_1EDGE;
        break;    
    case RT_SPI_MODE_3:
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
        break;
    }
    
    /* MSB or LSB */
    if(configuration->mode & RT_SPI_MSB)
    {
        spi_init_struct.endian = SPI_ENDIAN_MSB;
    }
    else
    {
        spi_init_struct.endian = SPI_ENDIAN_LSB;
    }
    
    spi_init_struct.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode = SPI_MASTER;
    spi_init_struct.nss = SPI_NSS_SOFT;
    
    spi_crc_off(spi_periph);

    /* init SPI */
    spi_init(spi_periph, &spi_init_struct);
    /* Enable SPI_MASTER */
	spi_enable(spi_periph);
    
    return RT_EOK;
};

static rt_uint32_t xfer(struct rt_spi_device* device, struct rt_spi_message* message)
{
    struct rt_spi_bus * stm32_spi_bus = (struct rt_spi_bus *)device->bus;
    struct stm32f4_spi *f4_spi = (struct stm32f4_spi *)stm32_spi_bus->parent.user_data;
    struct rt_spi_configuration * config = &device->config;
    struct stm32_spi_cs * stm32_spi_cs = device->parent.user_data;
    uint32_t spi_periph = f4_spi->spi_periph;

	RT_ASSERT(device != NULL);
	RT_ASSERT(message != NULL);
	
    /* take CS */
    if(message->cs_take)
    {
        gpio_bit_reset(stm32_spi_cs->GPIOx, stm32_spi_cs->GPIO_Pin);
        DEBUG_PRINTF("spi take cs\n");
    }

    {
        if(config->data_width <= 8)
        {
            const rt_uint8_t * send_ptr = message->send_buf;
            rt_uint8_t * recv_ptr = message->recv_buf;
            rt_uint32_t size = message->length;
            
            DEBUG_PRINTF("spi poll transfer start: %d\n", size);

            while(size--)
            {
                rt_uint8_t data = 0xFF;

                if(send_ptr != RT_NULL)
                {
                    data = *send_ptr++;
                }
                
                // Todo: replace register read/write by stm32f4 lib
                //Wait until the transmit buffer is empty
                while(RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_TBE));
                // Send the byte
				spi_i2s_data_transmit(spi_periph, data);

                //Wait until a data is received
                while(RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_RBNE));
                // Get the received data
                data = spi_i2s_data_receive(spi_periph);

                if(recv_ptr != RT_NULL)
                {
                    *recv_ptr++ = data;
                }
            }
            DEBUG_PRINTF("spi poll transfer finsh\n");
        }
        else if(config->data_width <= 16)
        {
            const rt_uint16_t * send_ptr = message->send_buf;
            rt_uint16_t * recv_ptr = message->recv_buf;
            rt_uint32_t size = message->length;

            while(size--)
            {
                rt_uint16_t data = 0xFF;

                if(send_ptr != RT_NULL)
                {
                    data = *send_ptr++;
                }

                //Wait until the transmit buffer is empty
                while(RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_TBE));
                // Send the byte
				spi_i2s_data_transmit(spi_periph, data);

                //Wait until a data is received
                while(RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_RBNE));
                // Get the received data
                data = spi_i2s_data_receive(spi_periph);

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
		gpio_bit_set(stm32_spi_cs->GPIOx, stm32_spi_cs->GPIO_Pin);
        DEBUG_PRINTF("spi release cs\n");
    }

    return message->length;
};


static struct rt_spi_bus spi_bus[];

static const struct stm32f4_spi spis[] = {
#ifdef RT_USING_SPI0
    {SPI0, RCU_SPI0, &spi_bus[0]},
#endif
    
#ifdef RT_USING_SPI1
    {SPI1, RCU_SPI1, &spi_bus[1]},
#endif

#ifdef RT_USING_SPI2
    {SPI2, RCU_SPI2, &spi_bus[2]},
#endif

#ifdef RT_USING_SPI3
    {SPI3, RCU_SPI3, &spi_bus[3]},
#endif
    
#ifdef RT_USING_SPI4
    {SPI4, RCU_SPI4, &spi_bus[4]},
#endif
    
#ifdef RT_USING_SPI5
    {SPI5, RCU_SPI5, &spi_bus[5]},
#endif
};

static struct rt_spi_bus spi_bus[ARR_LEN(spis)];

/** \brief init and register stm32 spi bus.
 *
 * \param SPI: STM32 SPI, e.g: SPI1,SPI2,SPI3.
 * \param spi_bus_name: spi bus name, e.g: "spi1"
 * \return
 *
 */
rt_err_t stm32_spi_bus_register(uint32_t spi_periph,
                            //struct stm32_spi_bus * stm32_spi,
                            const char * spi_bus_name)
{
    int i;
    
    RT_ASSERT(spi_bus_name != RT_NULL);
    
    for (i = 0; i < ARR_LEN(spis); i++)
    {
        if (spi_periph == spis[i].spi_periph)
        {
            rcu_periph_clock_enable(spis[i].spi_clk);
            spis[i].spi_bus->parent.user_data = (void *)&spis[i];
            rt_spi_bus_register(spis[i].spi_bus, spi_bus_name, &stm32_spi_ops);
            return RT_EOK;
        }
    }
    
    return RT_ERROR;
 
#ifdef SPI_USE_DMA
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
#endif
}
#endif
