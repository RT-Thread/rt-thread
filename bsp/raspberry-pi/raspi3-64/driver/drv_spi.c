/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */
#include "drv_spi.h"
#include "raspi.h"

#ifdef RT_USING_SPI

#define RPI_CORE_CLK_HZ        250000000
#define BSP_SPI_MAX_HZ (30* 1000 *1000)
#define SPITIMEOUT 0x0FFF

void spi_gpio_write(rt_uint8_t pin, rt_uint8_t val)
{
    if (val)
        BCM283X_GPIO_GPSET((pin / 32)) = 1 << (pin % 32);
    else
        BCM283X_GPIO_GPCLR((pin / 32)) = 1 << (pin % 32);
}

struct raspi_spi_hw_config
{
    rt_uint8_t spi_num;
    raspi_gpio_pin sclk_pin;
    raspi_pin_select sclk_mode;
    raspi_gpio_pin mosi_pin;
    raspi_pin_select mosi_mode;
    raspi_gpio_pin miso_pin;
    raspi_pin_select miso_mode;
#if defined (BSP_USING_SPI0_DEVICE0) || defined (BSP_USING_SPI1_DEVICE0)
    raspi_gpio_pin ce0_pin;
    raspi_pin_select ce0_mode;
#endif

#if defined (BSP_USING_SPI0_DEVICE1) || defined (BSP_USING_SPI1_DEVICE1)
    raspi_gpio_pin ce1_pin;
    raspi_pin_select ce1_mode;
#endif

#if defined (BSP_USING_SPI1_DEVICE2)
    raspi_gpio_pin ce2_pin;
    raspi_pin_select ce2_mode;
#endif
};

struct raspi_spi_device
{
    char *device_name;
    struct rt_spi_bus *spi_bus;
    struct rt_spi_device *spi_device;
    raspi_gpio_pin cs_pin;
};

static rt_err_t raspi_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(cfg != RT_NULL);
    RT_ASSERT(device != RT_NULL);
    rt_uint16_t divider;

    // spi clear fifo
    BCM283X_SPI0_CS(BCM283X_SPI0_BASE) |= BCM283X_SPI0_CS_CLEAR;

    if (cfg->mode & RT_SPI_CPOL)
        BCM283X_SPI0_CS(BCM283X_SPI0_BASE) |= BCM283X_SPI0_CS_CPOL;

    if (cfg->mode & RT_SPI_CPHA)
        BCM283X_SPI0_CS(BCM283X_SPI0_BASE) |= BCM283X_SPI0_CS_CPHA;

    if (cfg->mode & RT_SPI_CS_HIGH)
        BCM283X_SPI0_CS(BCM283X_SPI0_BASE) |= BCM283X_SPI0_CS_CSPOL;

    //set clk
    if (cfg->max_hz > BSP_SPI_MAX_HZ)
        cfg->max_hz = BSP_SPI_MAX_HZ;

    divider = (rt_uint16_t) ((rt_uint32_t) RPI_CORE_CLK_HZ / cfg->max_hz);
    divider &= 0xFFFE;

    BCM283X_SPI0_CLK(BCM283X_SPI0_BASE) = divider;

    return RT_EOK;
}

rt_uint8_t correct_order(rt_uint8_t b, rt_uint8_t flag)
{
    if (flag)
        return raspi_byte_reverse_table[b];
    else
        return b;
}

static rt_err_t spi_transfernb(rt_uint8_t* tbuf, rt_uint8_t* rbuf, rt_uint32_t len, rt_uint8_t flag)
{
    rt_uint32_t TXCnt=0;
    rt_uint32_t RXCnt=0;

    /* Clear TX and RX fifos */
    BCM283X_SPI0_CS(BCM283X_SPI0_BASE) |= (BCM283X_SPI0_CS_CLEAR & BCM283X_SPI0_CS_CLEAR);

    /* Set TA = 1 */
    BCM283X_SPI0_CS(BCM283X_SPI0_BASE) |= (BCM283X_SPI0_CS_TA & BCM283X_SPI0_CS_TA);


    /* Use the FIFO's to reduce the interbyte times */
    while ((TXCnt < len) || (RXCnt < len))
    {
        /* TX fifo not full, so add some more bytes */
        while (((BCM283X_SPI0_CS(BCM283X_SPI0_BASE) & BCM283X_SPI0_CS_TXD)) && (TXCnt < len))
        {
            BCM283X_SPI0_FIFO(BCM283X_SPI0_BASE) = correct_order(tbuf[TXCnt],flag);
            TXCnt++;
        }
        /* Rx fifo not empty, so get the next received bytes */
        while (((BCM283X_SPI0_CS(BCM283X_SPI0_BASE) & BCM283X_SPI0_CS_RXD)) && (RXCnt < len))
        {
            rbuf[RXCnt] = correct_order(BCM283X_SPI0_FIFO(BCM283X_SPI0_BASE),flag);
            RXCnt++;
        }
    }
    /* Wait for DONE to be set */
    while (!(BCM283X_SPI0_CS(BCM283X_SPI0_BASE) & BCM283X_SPI0_CS_DONE));

    /* Set TA = 0, and also set the barrier */
    BCM283X_SPI0_CS(BCM283X_SPI0_BASE) |= (0 & BCM283X_SPI0_CS_TA);
    return RT_EOK;
}

static rt_uint32_t raspi_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->parent.user_data != RT_NULL);
    RT_ASSERT(message->send_buf != RT_NULL || message->recv_buf != RT_NULL);

    rt_err_t res;
    rt_uint8_t flag;
    struct rt_spi_configuration config = device->config;
    raspi_gpio_pin cs_pin = (raspi_gpio_pin)device->parent.user_data;

    if (config.mode & RT_SPI_MSB)
        flag = 0;
    else
        flag = 1;
    if (message->cs_take);
      //  (config.mode & RT_SPI_CS_HIGH)?
      //          spi_gpio_write(cs_pin, 1):
      //          spi_gpio_write(cs_pin, 0);

    /* deal data */
    res = spi_transfernb((rt_uint8_t *)message->send_buf, (rt_uint8_t *)message->recv_buf,
            (rt_int32_t)message->length, flag);

    if (message->cs_release)
        (config.mode & RT_SPI_CS_HIGH)?
                spi_gpio_write(cs_pin, 0):
                spi_gpio_write(cs_pin, 1);

    if (res != RT_EOK)
           return RT_ERROR;

    return message->length;
}

rt_err_t raspi_spi_bus_attach_device(const char *bus_name, struct raspi_spi_device *device)
{
    rt_err_t ret;
    RT_ASSERT(device != RT_NULL);
    ret = rt_spi_bus_attach_device(device->spi_device, device->device_name, bus_name, (void *)(device->cs_pin));
    return ret;
}

rt_err_t raspi_spi_hw_init(struct raspi_spi_hw_config *hwcfg)
{
    GPIO_FSEL(hwcfg->sclk_pin, hwcfg->sclk_mode);
    GPIO_FSEL(hwcfg->miso_pin, hwcfg->miso_mode);
    GPIO_FSEL(hwcfg->mosi_pin, hwcfg->mosi_mode);

#if defined (BSP_USING_SPI0_DEVICE0)
    GPIO_FSEL(hwcfg->ce0_pin, hwcfg->ce0_mode);
#endif

#if defined (BSP_USING_SPI0_DEVICE1)
    GPIO_FSEL(hwcfg->ce1_pin, hwcfg->ce1_mode);
#endif

    BCM283X_SPI0_CS(BCM283X_SPI0_BASE) = 0;
    BCM283X_SPI0_CS(BCM283X_SPI0_BASE) = BCM283X_SPI0_CS_CLEAR;

    //enable chip select
#if defined (BSP_USING_SPI0_DEVICE0)
    BCM283X_SPI0_CS(BCM283X_SPI0_BASE) |= 0;
#endif

#if defined (BSP_USING_SPI0_DEVICE1)
    BCM283X_SPI0_CS(BCM283X_SPI0_BASE) |= 0x2;
#endif

#if defined (BSP_USING_SPI0_DEVICE0) && defined (BSP_USING_SPI0_DEVICE1)
    BCM283X_SPI0_CS(BCM283X_SPI0_BASE) |= BCM283X_SPI0_CS_CS;
#endif
    return RT_EOK;
}

static struct rt_spi_ops raspi_spi_ops =
{
    .configure = raspi_spi_configure,
    .xfer = raspi_spi_xfer
};

#if defined (BSP_USING_SPI0_BUS)
#define SPI0_BUS_NAME  "spi0"
#define SPI0_DEVICE0_NAME  "spi0.0"
#define SPI0_DEVICE1_NAME  "spi0.1"

struct rt_spi_bus spi0_bus;

#if defined (BSP_USING_SPI0_DEVICE0)
struct rt_spi_device spi0_device0;
#endif

#if defined (BSP_USING_SPI0_DEVICE1)
static struct rt_spi_device spi0_device1;
#endif

struct raspi_spi_hw_config raspi_spi0_hw =
{
    .spi_num = 0,
    .sclk_pin = RPI_GPIO_P1_23,
    .sclk_mode = BCM283X_GPIO_FSEL_ALT0,
    .mosi_pin = RPI_GPIO_P1_19,
    .mosi_mode = BCM283X_GPIO_FSEL_ALT0,
    .miso_pin = RPI_GPIO_P1_21,
    .miso_mode = BCM283X_GPIO_FSEL_ALT0,

#if defined (BSP_USING_SPI0_DEVICE0)
    .ce0_pin = RPI_GPIO_P1_24,
    .ce0_mode = BCM283X_GPIO_FSEL_ALT0,
#endif

#if defined (BSP_USING_SPI0_DEVICE1)
    .ce1_pin = RPI_GPIO_P1_26,
    .ce1_mode = BCM283X_GPIO_FSEL_ALT0,
#endif
};
#endif

int rt_hw_spi_init(void)
{

#if defined (BSP_USING_SPI0_BUS)
    raspi_spi_hw_init(&raspi_spi0_hw);
    rt_spi_bus_register(&spi0_bus, SPI0_BUS_NAME, &raspi_spi_ops);

#if defined (BSP_USING_SPI0_DEVICE0)
    struct raspi_spi_device raspi_spi0_device0 =
    {
        .device_name = SPI0_DEVICE0_NAME,
        .spi_bus = &spi0_bus,
        .spi_device = &spi0_device0,
        .cs_pin = raspi_spi0_hw.ce0_pin,
    };
    raspi_spi_bus_attach_device(SPI0_BUS_NAME, &raspi_spi0_device0);
#endif

#if defined (BSP_USING_SPI0_DEVICE1)
    struct raspi_spi_device raspi_spi0_device1 =
    {
        .device_name = SPI0_DEVICE1_NAME,
        .spi_bus = &spi0_bus,
        .spi_device = &spi0_device1,
        .cs_pin = raspi_spi0_hw.ce1_pin,
    };
    raspi_spi_bus_attach_device(SPI0_BUS_NAME, &raspi_spi0_device1);
#endif
#endif
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_spi_init);

#endif
