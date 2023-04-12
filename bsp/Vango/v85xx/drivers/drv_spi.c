/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-06-05     tanek        first implementation.
 * 2018-04-19     misonyo      Porting for v85xxf30x
 * 2019-03-31     xuzhuoyi     Porting for v85xxe230
 * 2021-09-21     zhuxw        Porting for v85xx
 */

#include "drv_spi.h"
#include "board.h"
#include <rtthread.h>

#if defined(RT_USING_SPI) && defined(RT_USING_PIN)
#include <rtdevice.h>

#if !defined(RT_USING_SPI1) && !defined(RT_USING_SPI2)
#error "Please define at least one SPIx"
#endif

/* private rt-thread spi ops function */
static rt_err_t configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration);
static rt_uint32_t xfer(struct rt_spi_device* device, struct rt_spi_message* message);

static struct rt_spi_ops v85xx_spi_ops =
{
    configure,
    xfer
};

static rt_err_t configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration)
{
    SPI_InitType spi_init_struct;

    rt_uint32_t spi_periph = (rt_uint32_t)device->bus->parent.user_data;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    if(configuration->data_width > 8)
    {
        return -RT_EIO;
    }

    {
        rt_uint32_t spi_apb_clock;
        rt_uint32_t max_hz;

        max_hz = configuration->max_hz;

        spi_apb_clock = CLK_GetPCLKFreq();

        if(max_hz >= spi_apb_clock/2)
        {
            spi_init_struct.ClockDivision = SPI_CLKDIV_2;
        }
        else if (max_hz >= spi_apb_clock/4)
        {
            spi_init_struct.ClockDivision = SPI_CLKDIV_4;
        }
        else if (max_hz >= spi_apb_clock/8)
        {
            spi_init_struct.ClockDivision = SPI_CLKDIV_8;
        }
        else if (max_hz >= spi_apb_clock/16)
        {
            spi_init_struct.ClockDivision = SPI_CLKDIV_16;
        }
        else if (max_hz >= spi_apb_clock/32)
        {
            spi_init_struct.ClockDivision = SPI_CLKDIV_32;
        }
        else if (max_hz >= spi_apb_clock/64)
        {
            spi_init_struct.ClockDivision = SPI_CLKDIV_64;
        }
        else
        {
            /*  min prescaler 128 */
            spi_init_struct.ClockDivision = SPI_CLKDIV_128;
        }
    } /* baudrate */

    switch(configuration->mode & RT_SPI_MODE_3)
    {
    case RT_SPI_MODE_0:
        spi_init_struct.SPH = SPI_SPH_0;
        spi_init_struct.SPO = SPI_SPO_0;
        break;
    case RT_SPI_MODE_1:
        spi_init_struct.SPH = SPI_SPH_1;
        spi_init_struct.SPO = SPI_SPO_0;
        break;
    case RT_SPI_MODE_2:
        spi_init_struct.SPH = SPI_SPH_0;
        spi_init_struct.SPO = SPI_SPO_1;
        break;
    case RT_SPI_MODE_3:
        spi_init_struct.SPH = SPI_SPH_1;
        spi_init_struct.SPO = SPI_SPO_1;
        break;
    }

    if(!(configuration->mode & RT_SPI_MSB))
    {
        return -RT_EIO;
    }

    spi_init_struct.Mode = SPI_MODE_MASTER;
    spi_init_struct.CSNSoft = SPI_CSNSOFT_ENABLE;

    SPI_Init((SPI_TypeDef*)spi_periph, &spi_init_struct);

    SPI_Cmd((SPI_TypeDef*)spi_periph, ENABLE);

    return RT_EOK;
};

static rt_uint32_t xfer(struct rt_spi_device* device, struct rt_spi_message* message)
{
    rt_base_t v85xx_cs_pin = (rt_base_t)device->parent.user_data;
    rt_uint32_t spi_periph = (rt_uint32_t)device->bus->parent.user_data;
    struct rt_spi_configuration * config = &device->config;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    /* take CS */
    if(message->cs_take)
    {
        rt_pin_write(v85xx_cs_pin, PIN_LOW);
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

                //Wait until the transmit buffer is empty
                while(RESET == SPI_GetStatus((SPI_TypeDef*)spi_periph, SPI_STS_TXEMPTY));
                // Send the byte
                SPI_SendData((SPI_TypeDef*)spi_periph, data);

                //Wait until a data is received
                while(RESET == SPI_GetStatus((SPI_TypeDef*)spi_periph, SPI_STS_RNE));
                // Get the received data
                data = SPI_ReceiveData((SPI_TypeDef*)spi_periph);

                if(recv_ptr != RT_NULL)
                {
                    *recv_ptr++ = data;
                }
            }
            DEBUG_PRINTF("spi poll transfer finsh\n");
        }
    }

    /* release CS */
    if(message->cs_release)
    {
        rt_pin_write(v85xx_cs_pin, PIN_HIGH);
        DEBUG_PRINTF("spi release cs\n");
    }

    return message->length;
};

int v85xx_hw_spi_init(void)
{
    int result = 0;
#ifdef RT_USING_SPI1
    static struct rt_spi_bus spi_bus0;
    spi_bus0.parent.user_data = (void *)SPI1;

    result = rt_spi_bus_register(&spi_bus0, "spi1", &v85xx_spi_ops);

#endif

#ifdef RT_USING_SPI2
    static struct rt_spi_bus spi_bus1;
    spi_bus1.parent.user_data = (void *)SPI2;

    result = rt_spi_bus_register(&spi_bus1, "spi2", &v85xx_spi_ops);

#endif
    return result;
}
INIT_BOARD_EXPORT(v85xx_hw_spi_init);
#endif
