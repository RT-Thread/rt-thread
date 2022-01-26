/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-04     Haley        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "am_mcu_apollo.h"
#include "spi.h"

/* SPI0 */
#define AM_SPI0_IOM_INST    0

#define SPI0_GPIO_SCK       5
#define SPI0_GPIO_CFG_SCK   AM_HAL_PIN_5_M0SCK
#define SPI0_GPIO_MISO      6
#define SPI0_GPIO_CFG_MISO  AM_HAL_PIN_6_M0MISO
#define SPI0_GPIO_MOSI      7
#define SPI0_GPIO_CFG_MOSI  AM_HAL_PIN_7_M0MOSI

/* SPI1 */
#define AM_SPI1_IOM_INST    1

static am_hal_iom_config_t g_sIOMConfig =
{
    AM_HAL_IOM_SPIMODE, // ui32InterfaceMode
    AM_HAL_IOM_400KHZ, // ui32ClockFrequency
    0, // bSPHA
    0, // bSPOL
    80, // ui8WriteThreshold
    80, // ui8ReadThreshold
};

/* AM spi driver */
struct am_spi_bus
{
    struct rt_spi_bus parent;
    rt_uint32_t u32Module;
};

//connect am drv to rt drv.
static rt_err_t configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration)
{
    struct am_spi_bus * am_spi_bus = (struct am_spi_bus *)device->bus;
    rt_uint32_t max_hz = configuration->max_hz;

    if(max_hz >= 24000000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_24MHZ;
    }
    else if(max_hz >= 16000000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_16MHZ;
    }
    else if(max_hz >= 12000000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_12MHZ;
    }
    else if(max_hz >= 8000000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_8MHZ;
    }
    else if(max_hz >= 6000000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_6MHZ;
    }
    else if(max_hz >= 4000000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_4MHZ;
    }
    else if(max_hz >= 3000000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_3MHZ;
    }
    else if(max_hz >= 2000000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_2MHZ;
    }
    else if(max_hz >= 1500000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_1_5MHZ;
    }
    else if(max_hz >= 1000000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_1MHZ;
    }
    else if(max_hz >= 750000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_750KHZ;
    }
    else if(max_hz >= 500000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_500KHZ;
    }
    else if(max_hz >= 400000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_400KHZ;
    }
    else if(max_hz >= 375000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_375KHZ;
    }
    else if(max_hz >= 250000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_250KHZ;
    }
    else if(max_hz >= 100000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_100KHZ;
    }
    else if(max_hz >= 50000)
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_50KHZ;
    }
    else
    {
        g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_10KHZ;
    }

    /* CPOL */
    if(configuration->mode & RT_SPI_CPOL)
    {
        g_sIOMConfig.bSPOL = 1;
    }
    else
    {
        g_sIOMConfig.bSPOL = 0;
    }

    /* CPHA */
    if(configuration->mode & RT_SPI_CPHA)
    {
        g_sIOMConfig.bSPHA= 1;
    }
    else
    {
        g_sIOMConfig.bSPHA= 0;
    }

    /* init SPI */
    am_hal_iom_disable(am_spi_bus->u32Module);
    am_hal_iom_config(am_spi_bus->u32Module, &g_sIOMConfig);
    am_hal_iom_enable(am_spi_bus->u32Module);

    return RT_EOK;
};

static rt_uint32_t xfer(struct rt_spi_device *device, struct rt_spi_message* message)
{
    struct am_spi_bus * am_spi_bus = (struct am_spi_bus *)device->bus;
    //struct rt_spi_configuration * config = &device->config;
    struct am_spi_cs * am_spi_cs = device->parent.user_data;
    rt_uint32_t * send_ptr = (rt_uint32_t *)message->send_buf;
    rt_uint32_t * recv_ptr = message->recv_buf;
    rt_uint32_t u32BytesRemaining = message->length;
    rt_uint32_t u32TransferSize = 0;

    /* take CS */
    if (message->cs_take)
    {
        am_hal_gpio_out_bit_clear(am_spi_cs->chip_select);
    }

    // 读数据
    if (recv_ptr != RT_NULL)
    {
        while (u32BytesRemaining)
        {
            /* Set the transfer size to either 64, or the number of remaining
               bytes, whichever is smaller */
            if (u32BytesRemaining > 64)
            {
                u32TransferSize = 64;
                am_hal_gpio_pin_config(SPI0_GPIO_MOSI, AM_HAL_GPIO_OUTPUT | AM_HAL_GPIO_PULL6K);
                am_hal_gpio_out_bit_set(SPI0_GPIO_MOSI);
                am_hal_iom_spi_read(am_spi_bus->u32Module, am_spi_cs->chip_select,
                                   (uint32_t *)recv_ptr, u32TransferSize, AM_HAL_IOM_RAW);
                am_hal_gpio_pin_config(SPI0_GPIO_MOSI, SPI0_GPIO_CFG_MOSI | AM_HAL_GPIO_PULL6K);
            }
            else
            {
                u32TransferSize = u32BytesRemaining;
                {
                    am_hal_gpio_pin_config(SPI0_GPIO_MOSI, AM_HAL_GPIO_OUTPUT | AM_HAL_GPIO_PULL6K);
                    am_hal_gpio_out_bit_set(SPI0_GPIO_MOSI);
                    am_hal_iom_spi_read(am_spi_bus->u32Module, am_spi_cs->chip_select,
                                   (uint32_t *)recv_ptr, u32TransferSize, AM_HAL_IOM_RAW);
                    am_hal_gpio_pin_config(SPI0_GPIO_MOSI, SPI0_GPIO_CFG_MOSI | AM_HAL_GPIO_PULL6K);
                }
            }

            u32BytesRemaining -= u32TransferSize;
            recv_ptr = (rt_uint32_t *)((rt_uint32_t)recv_ptr + u32TransferSize);
        }
    }

    // 写数据
    else
    {
        while (u32BytesRemaining)
        {
            /* Set the transfer size to either 32, or the number of remaining
               bytes, whichever is smaller */
            if (u32BytesRemaining > 64)
            {
                u32TransferSize = 64;
                am_hal_iom_spi_write(am_spi_bus->u32Module, am_spi_cs->chip_select,
                                    (uint32_t *)send_ptr, u32TransferSize, AM_HAL_IOM_RAW);

            }
            else
            {
                u32TransferSize = u32BytesRemaining;
                {
                    am_hal_iom_spi_write(am_spi_bus->u32Module, am_spi_cs->chip_select,
                              (uint32_t *)send_ptr, u32TransferSize, AM_HAL_IOM_RAW);
                }
            }

            u32BytesRemaining -= u32TransferSize;
            send_ptr = (rt_uint32_t *)((rt_uint32_t)send_ptr + u32TransferSize);
        }
    }

    /* release CS */
    if(message->cs_release)
    {
        am_hal_gpio_out_bit_set(am_spi_cs->chip_select);
    }

    return message->length;
}

static const struct rt_spi_ops am_spi_ops =
{
    configure,
    xfer
};

#ifdef RT_USING_SPI0
static struct am_spi_bus am_spi_bus_0 =
{
    {0},
    AM_SPI0_IOM_INST
};
#endif /* #ifdef RT_USING_SPI0 */

#ifdef RT_USING_SPI1
static struct am_spi_bus am_spi_bus_1 =
{
    {0},
    AM_SPI1_IOM_INST
};
#endif /* #ifdef RT_USING_SPI1 */

int yr_hw_spi_init(void)
{
    struct am_spi_bus* am_spi;

#ifdef RT_USING_SPI0
    /* init spi gpio */
    am_hal_gpio_pin_config(SPI0_GPIO_SCK, SPI0_GPIO_CFG_SCK);
    am_hal_gpio_pin_config(SPI0_GPIO_MISO, SPI0_GPIO_CFG_MISO | AM_HAL_GPIO_PULL6K);
    am_hal_gpio_pin_config(SPI0_GPIO_MOSI, SPI0_GPIO_CFG_MOSI | AM_HAL_GPIO_PULL6K);

    /* Initialize IOM 0 in SPI mode at 100KHz */
    am_hal_iom_pwrctrl_enable(AM_SPI0_IOM_INST);
    am_hal_iom_config(AM_SPI0_IOM_INST, &g_sIOMConfig);
    am_hal_iom_enable(AM_SPI0_IOM_INST);

    //init spi bus device
    am_spi = &am_spi_bus_0;
    rt_spi_bus_register(&am_spi->parent, "spi0", &am_spi_ops);
#endif

    //rt_kprintf("spi init!\n");

    return 0;
}
#ifdef RT_USING_COMPONENTS_INIT
INIT_BOARD_EXPORT(yr_hw_spi_init);
#endif

/*@}*/
