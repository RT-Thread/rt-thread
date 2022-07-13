/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file drv_spi.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */

#include "drv_spi.h"

#if defined(RT_USING_SPI) && defined(RT_USING_PIN)
#include <rtdevice.h>

#if defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || \
    defined(BSP_USING_SPI3)

/* #define DEBUG */
#ifdef DEBUG
#define DEBUG_PRINTF(...)   rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)
#endif

/* private rt-thread spi ops function */

static rt_err_t configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration)
{
    SPI_InitType SPI_InitStructure;
    RCC_ClocksType RCC_ClockFreq;
    SPI_Module* spi_periph;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);
    
    RCC_GetClocksFreqValue(&RCC_ClockFreq);
    
    spi_periph = (SPI_Module*)device->bus->parent.user_data;
    
    if(spi_periph != SPI1 && spi_periph != SPI2 && spi_periph != SPI3)
    {
        return RT_EIO;
    }
    if(configuration->data_width <= 8)
    {
        SPI_InitStructure.DataLen = SPI_DATA_SIZE_8BITS;
    }
    else if(configuration->data_width <= 16)
    {
        SPI_InitStructure.DataLen = SPI_DATA_SIZE_16BITS;
    }
    else
    {
        return RT_EIO;
    }
    
    {
        rt_uint32_t spi_apb_clock;
        rt_uint32_t max_hz;

        max_hz = configuration->max_hz;

        DEBUG_PRINTF("sys   freq: %d\n", RCC_ClockFreq.SysclkFreq);
        DEBUG_PRINTF("CK_APB2 freq: %d\n", RCC_ClockFreq.Pclk2Freq);
        DEBUG_PRINTF("max   freq: %d\n", max_hz);

        if (spi_periph == SPI1)
        {
            spi_apb_clock = RCC_ClockFreq.Pclk2Freq;
        }
        else
        {
            spi_apb_clock = RCC_ClockFreq.Pclk1Freq;
        }

        if(max_hz >= spi_apb_clock/2)
        {
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_2;
        }
        else if (max_hz >= spi_apb_clock/4)
        {
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_4;
        }
        else if (max_hz >= spi_apb_clock/8)
        {
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_8;
        }
        else if (max_hz >= spi_apb_clock/16)
        {
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_16;
        }
        else if (max_hz >= spi_apb_clock/32)
        {
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_32;
        }
        else if (max_hz >= spi_apb_clock/64)
        {
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_64;
        }
        else if (max_hz >= spi_apb_clock/128)
        {
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_128;
        }
        else
        {
            /*  min prescaler 256 */
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_256;
        }
    } /* baudrate */
    
    switch(configuration->mode & RT_SPI_MODE_3)
    {
        case RT_SPI_MODE_0:
            SPI_InitStructure.CLKPOL        = SPI_CLKPOL_LOW;
            SPI_InitStructure.CLKPHA        = SPI_CLKPHA_FIRST_EDGE;    
            break;
        case RT_SPI_MODE_1:
            SPI_InitStructure.CLKPOL        = SPI_CLKPOL_LOW;
            SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
            break;
        case RT_SPI_MODE_2:
            SPI_InitStructure.CLKPOL        = SPI_CLKPOL_HIGH;
            SPI_InitStructure.CLKPHA        = SPI_CLKPHA_FIRST_EDGE;
            break;
        case RT_SPI_MODE_3:
            SPI_InitStructure.CLKPOL        = SPI_CLKPOL_HIGH;
            SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
            break;
    }
    
    /* MSB or LSB */
    if(configuration->mode & RT_SPI_MSB)
    {
        SPI_InitStructure.FirstBit = SPI_FB_MSB;
    }
    else
    {
        SPI_InitStructure.FirstBit = SPI_FB_LSB;
    }
    /*!< SPI configuration */
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
    SPI_InitStructure.CRCPoly       = 7; 
    
    SPI_Init(spi_periph, &SPI_InitStructure);

    /*!< Enable the sFLASH_SPI  */
    SPI_Enable(spi_periph, ENABLE);

    return RT_EOK;
}

static rt_uint32_t xfer(struct rt_spi_device* device, struct rt_spi_message* message)
{
    struct n32_spi_cs *cs_pin = device->parent.user_data;
    SPI_Module* spi_periph = (SPI_Module*)device->bus->parent.user_data;
    struct rt_spi_configuration * config = &device->config;

    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    /* take CS */
    if(message->cs_take)
    {
        rt_pin_write(cs_pin->GPIO_Pin, PIN_LOW);
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
                rt_uint8_t data = 0xA5;

                if(send_ptr != RT_NULL)
                {
                    data = *send_ptr++;
                }
                                
                /*!< Loop while DAT register in not emplty */
                while (SPI_I2S_GetStatus(spi_periph, SPI_I2S_TE_FLAG) == RESET);
                
                // Send the byte
                SPI_I2S_TransmitData(spi_periph, data);

                //Wait until a data is received
                while(SPI_I2S_GetStatus(spi_periph, SPI_I2S_RNE_FLAG) == RESET);
                
                // Get the received data
                data = SPI_I2S_ReceiveData(spi_periph);
                
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
                
                 /*!< Loop while DAT register in not emplty */
                while (SPI_I2S_GetStatus(spi_periph, SPI_I2S_TE_FLAG) == RESET);
                
                // Send the byte
                SPI_I2S_TransmitData(spi_periph, data);

                //Wait until a data is received
                while(RESET == SPI_I2S_GetStatus(spi_periph, SPI_I2S_RNE_FLAG));
                
                // Get the received data
                data = SPI_I2S_ReceiveData(spi_periph);

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
        rt_pin_write(cs_pin->GPIO_Pin, PIN_HIGH);
        DEBUG_PRINTF("spi release cs\n");
    }

    return message->length;
}

static struct rt_spi_ops spi_ops =
{
    configure,
    xfer
};

int rt_hw_spi_init(void)
{
    int result = 0;
    
#ifdef BSP_USING_SPI1
    static struct rt_spi_bus spi_bus1;
    spi_bus1.parent.user_data = (void *)SPI1;

    result = rt_spi_bus_register(&spi_bus1, "spi1", &spi_ops);
	
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI1, ENABLE);    
    /* SPI1_SCK(PA5), SPI1_MISO(PA6) and SPI1_MOSI(PA7) GPIO pin configuration */
    GPIOInit(SPI1_SCK_GPIO_PORT, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, SPI1_SCK_PIN);
    GPIOInit(SPI1_MOSI_GPIO_PORT, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, SPI1_MOSI_PIN);
    GPIOInit(SPI1_MISO_GPIO_PORT, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, SPI1_MISO_PIN); 
        
#endif
#ifdef BSP_USING_SPI2
    static struct rt_spi_bus spi_bus2;
    spi_bus2.parent.user_data = (void *)SPI2;

    result = rt_spi_bus_register(&spi_bus2, "spi2", &spi_ops); 

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI2, ENABLE);   
    /* SPI2_SCK(PB13), SPI2_MISO(PB14) and SPI2_MOSI(PB15) GPIO pin configuration */
    GPIOInit(SPI2_SCK_GPIO_PORT, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, SPI2_SCK_PIN);
    GPIOInit(SPI2_MOSI_GPIO_PORT, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, SPI2_MOSI_PIN);
    GPIOInit(SPI2_MISO_GPIO_PORT, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, SPI2_MISO_PIN); 
    
#endif
#ifdef BSP_USING_SPI3
    static struct rt_spi_bus spi_bus3;
    spi_bus3.parent.user_data = (void *)SPI3;

    result = rt_spi_bus_register(&spi_bus3, "spi3", &spi_ops);
    
		/* Enable AFIO clock */
		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
	
    GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_SW_ENABLE, ENABLE);
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI3, ENABLE);
    
   /* SPI3_SCK(PB3), SPI3_MISO(PB4) and SPI3_MOSI(PB5) GPIO pin configuration */
    GPIOInit(SPI3_SCK_GPIO_PORT, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, SPI3_SCK_PIN);
    GPIOInit(SPI3_MOSI_GPIO_PORT, GPIO_Mode_AF_PP, GPIO_Speed_50MHz, SPI3_MOSI_PIN);
    GPIOInit(SPI3_MISO_GPIO_PORT, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz, SPI3_MISO_PIN); 
    
#endif
    return result;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3) */
#endif
