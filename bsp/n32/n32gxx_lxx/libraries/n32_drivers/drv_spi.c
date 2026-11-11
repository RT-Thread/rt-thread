/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
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

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    if (spi_periph != SPI1 && spi_periph != SPI2 && spi_periph != SPI3)
    {
        return -RT_EIO;
    }
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    if (spi_periph != SPI1 && spi_periph != SPI2)
    {
        return -RT_EIO;
    }
#endif

    if (configuration->data_width <= 8)
    {
        SPI_InitStructure.DataLen = SPI_DATA_SIZE_8BITS;
    }
    else if (configuration->data_width <= 16)
    {
        SPI_InitStructure.DataLen = SPI_DATA_SIZE_16BITS;
    }
    else
    {
        return -RT_EIO;
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

        if (max_hz >= spi_apb_clock/2)
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

    switch (configuration->mode & RT_SPI_MODE_3)
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
    if (configuration->mode & RT_SPI_MSB)
    {
        SPI_InitStructure.FirstBit = SPI_FB_MSB;
    }
    else
    {
        SPI_InitStructure.FirstBit = SPI_FB_LSB;
    }
    /* SPI configuration */
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
    SPI_InitStructure.CRCPoly       = 7;

    SPI_Init(spi_periph, &SPI_InitStructure);

    /* Enable the sFLASH_SPI  */
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
    if (message->cs_take)
    {
        rt_pin_write(cs_pin->GPIO_Pin, PIN_LOW);
        DEBUG_PRINTF("spi take cs\n");
    }

        if (config->data_width <= 8)
        {
            const rt_uint8_t * send_ptr = message->send_buf;
            rt_uint8_t * recv_ptr = message->recv_buf;
            rt_uint32_t size = message->length;

            DEBUG_PRINTF("spi poll transfer start: %d\n", size);

            while (size--)
            {
                rt_uint8_t data = 0xA5;

                if (send_ptr != RT_NULL)
                {
                    data = *send_ptr++;
                }

                /* Loop while DAT register in not emplty */
                while (SPI_I2S_GetStatus(spi_periph, SPI_I2S_TE_FLAG) == RESET);

                /* Send the byte */
                SPI_I2S_TransmitData(spi_periph, data);

                /* Wait until a data is received */
                while (SPI_I2S_GetStatus(spi_periph, SPI_I2S_RNE_FLAG) == RESET);

                /* Get the received data */
                data = SPI_I2S_ReceiveData(spi_periph);

                if (recv_ptr != RT_NULL)
                {
                        *recv_ptr++ = data;
                }
            }
            DEBUG_PRINTF("spi poll transfer finsh\n");
        }
        else if (config->data_width <= 16)
        {
            const rt_uint16_t * send_ptr = message->send_buf;
            rt_uint16_t * recv_ptr = message->recv_buf;
            rt_uint32_t size = message->length;

            while (size--)
            {
                rt_uint16_t data = 0xFF;

                if (send_ptr != RT_NULL)
                {
                    data = *send_ptr++;
                }

                /* Loop while DAT register in not emplty */
                while (SPI_I2S_GetStatus(spi_periph, SPI_I2S_TE_FLAG) == RESET);

                /* Send the byte */
                SPI_I2S_TransmitData(spi_periph, data);

                /* Wait until a data is received */
                while (RESET == SPI_I2S_GetStatus(spi_periph, SPI_I2S_RNE_FLAG));

                /* Get the received data */
                data = SPI_I2S_ReceiveData(spi_periph);

                if (recv_ptr != RT_NULL)
                {
                        *recv_ptr++ = data;
                }
            }
        }

    /* release CS */
    if (message->cs_release)
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
    GPIO_InitType GPIO_InitStructure;

#ifdef BSP_USING_SPI1
    static struct rt_spi_bus spi_bus1;
    spi_bus1.parent.user_data = (void *)SPI1;

    result = rt_spi_bus_register(&spi_bus1, "spi1", &spi_ops);

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_SPI1, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);

    /* Confige SPI1_SCLK(PA5) and SPI1_MOSI(PA7) */
    GPIO_InitStructure.Pin        = GPIO_PIN_5 | GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* Confige SPI1_MISO(PA6) */
    GPIO_InitStructure.Pin        = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI1 | RCC_APB2_PERIPH_AFIO, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Confige SPI1_SCLK(PA5) and SPI1_MISO(PA6) and SPI1_MOSI(PA7) */
    GPIO_InitStructure.Pin            = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_SPI1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
#endif
#endif

#ifdef BSP_USING_SPI2
    static struct rt_spi_bus spi_bus2;
    spi_bus2.parent.user_data = (void *)SPI2;

    result = rt_spi_bus_register(&spi_bus2, "spi2", &spi_ops);

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI2, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);

    /* Confige SPI2_SCLK(PB13) and SPI2_MOSI(PB15) */
    GPIO_InitStructure.Pin        = GPIO_PIN_13 | GPIO_PIN_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    /* Confige SPI2_MISO(PB14) */
    GPIO_InitStructure.Pin        = GPIO_PIN_14;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI2 | RCC_APB2_PERIPH_AFIO, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Confige SPI2_SCLK(PB13) and SPI2_MISO(PB14) and SPI2_MOSI(PB15) */
    GPIO_InitStructure.Pin            = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_SPI2;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
#endif
#endif

#ifdef BSP_USING_SPI3
    static struct rt_spi_bus spi_bus3;
    spi_bus3.parent.user_data = (void *)SPI3;

    result = rt_spi_bus_register(&spi_bus3, "spi3", &spi_ops);

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI3, ENABLE);

    GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_SW_ENABLE, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);

    /* Confige SPI3_SCLK(PB3) and SPI3_MOSI(PB5) */
    GPIO_InitStructure.Pin        = GPIO_PIN_3 | GPIO_PIN_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    /* Confige SPI3_MISO(PB4) */
    GPIO_InitStructure.Pin        = GPIO_PIN_4;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
#endif
    return result;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3) */
#endif
