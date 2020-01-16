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

#if !defined(BSP_USING_SPI0) && !defined(BSP_USING_SPI1)
#ifdef RT_USING_SPI
#undef RT_USING_SPI
#endif
#endif

#ifdef RT_USING_SPI


static rt_uint8_t bcm2835_spi_bit_order = BCM283X_SPI_BIT_ORDER_MSBFIRST;
static rt_uint8_t bcm2835_byte_reverse_table[] =
{
    0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
    0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
    0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
    0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
    0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
    0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
    0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
    0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
    0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
    0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
    0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
    0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
    0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
    0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
    0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
    0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
    0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
    0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
    0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
    0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
    0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
    0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
    0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
    0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
    0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
    0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
    0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
    0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
    0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
    0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
    0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
    0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff
};

#define BSP_SPI_MAX_HZ (30* 1000 *1000)
#define SPITIMEOUT 0x0FFF

struct rt_spi_hw_config
{
    rt_int8_t sclk_pin;
    rt_int8_t sclk_mode;
    rt_int8_t mosi_pin;
    rt_int8_t mosi_mode;
    rt_int8_t miso_pin;
    rt_int8_t miso_mode;
    rt_int8_t cs_pin;
    rt_int8_t cs_mode;
    rt_uint32_t spi_base;
    rt_uint32_t clk_div;
};

struct rt_sw_spi_cs
{
    rt_uint32_t pin;
};

struct rt_spi
{
    char *device_name;
    struct rt_spi_bus *spi_bus;
    struct rt_spi_hw_config *hwcfg;
    struct rt_spi_configuration *cfg;
};

static rt_err_t raspi_hostspi_init(struct rt_spi_configuration *cfg)
{

    volatile rt_uint32_t addr = (PER_BASE + BCM283X_SPI0_BASE) + BCM283X_SPI0_CS;
    //volatile rt_uint32_t fifo = (PER_BASE + BCM283X_SPI0_BASE) + BCM283X_SPI0_FIFO;

    // spi clear fifo
    bcm283x_peri_set_bits(addr, BCM283X_SPI0_CS_CLEAR, BCM283X_SPI0_CS_CLEAR);

    //    /* Set TA = 1 */
    //    bcm2835_peri_set_bits(addr, BCM283X_SPI0_CS_TA, BCM283X_SPI0_CS_TA);

    /* Mask in the CPO and CPHA bits of CS */

    bcm283x_peri_set_bits(addr,  (rt_uint32_t)(cfg->mode << 2), BCM283X_SPI0_CS_CPOL | BCM283X_SPI0_CS_CPHA);

    //chipSelect
    bcm283x_peri_set_bits(addr, BCM283X_SPI_CS0, BCM283X_SPI0_CS_CS);

    rt_uint8_t shift = 21 + BCM283X_SPI_CS0;
    /* Mask in the appropriate CSPOLn bit */
    bcm283x_peri_set_bits(addr, LOW << shift, 1 << shift);


    if(cfg->max_hz > BSP_SPI_MAX_HZ)
    {
        cfg->max_hz = BSP_SPI_MAX_HZ;
    }

    volatile rt_uint32_t clk_addr = (PER_BASE + BCM283X_SPI0_BASE) + BCM283X_SPI0_CLK;
    bcm283x_peri_write(clk_addr, cfg->max_hz);

    return RT_EOK;
}

static rt_err_t raspi_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(cfg != RT_NULL);
    RT_ASSERT(device != RT_NULL);

    struct rt_spi *hspi = (struct rt_spi *)&device->bus->parent;
    hspi->cfg = cfg;

    raspi_hostspi_init(cfg);

    return RT_EOK;
}


rt_uint8_t correct_order(rt_uint8_t b)
{
    if (bcm2835_spi_bit_order == BCM283X_SPI_BIT_ORDER_LSBFIRST)
        return bcm2835_byte_reverse_table[b];
    else
        return b;
}

static rt_err_t  spi_transfernb(rt_uint8_t* tbuf, rt_uint8_t* rbuf, rt_uint32_t len)
{
    volatile rt_uint32_t paddr = SPI0_BASE_ADDR + BCM283X_SPI0_CS;
    volatile rt_uint32_t fifo = SPI0_BASE_ADDR + BCM283X_SPI0_FIFO;
    rt_uint32_t TXCnt=0;
    rt_uint32_t RXCnt=0;

    /* Clear TX and RX fifos */
    bcm283x_peri_set_bits(paddr, BCM283X_SPI0_CS_CLEAR, BCM283X_SPI0_CS_CLEAR);

    /* Set TA = 1 */
    bcm283x_peri_set_bits(paddr, BCM283X_SPI0_CS_TA, BCM283X_SPI0_CS_TA);

    /* Use the FIFO's to reduce the interbyte times */
    while ((TXCnt < len) || (RXCnt < len))
    {
        /* TX fifo not full, so add some more bytes */
        while (((bcm283x_peri_read(paddr) & BCM283X_SPI0_CS_TXD)) && (TXCnt < len))
        {
            bcm283x_peri_write_nb(fifo, correct_order(tbuf[TXCnt]));
            TXCnt++;
        }
        /* Rx fifo not empty, so get the next received bytes */
        while (((bcm283x_peri_read(paddr) & BCM283X_SPI0_CS_RXD)) && (RXCnt < len))
        {
            rbuf[RXCnt] = correct_order(bcm283x_peri_read_nb(fifo));
            RXCnt++;
        }
    }
    /* Wait for DONE to be set */
    while (!(bcm283x_peri_read_nb(paddr) & BCM283X_SPI0_CS_DONE));

    /* Set TA = 0, and also set the barrier */
    bcm283x_peri_set_bits(paddr, 0, BCM283X_SPI0_CS_TA);
    return RT_EOK;

}

static rt_uint32_t raspi_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_err_t res;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    RT_ASSERT(message->send_buf != RT_NULL || message->recv_buf != RT_NULL);

    struct rt_spi *hspi = (struct rt_spi *)&device->bus->parent;
    /* only send data */
    if (message->recv_buf == RT_NULL)
    {
        if (message->cs_take)
        {
            bcm283x_gpio_write(hspi->hwcfg->cs_pin, 0);
        }
        res = spi_transfernb((rt_uint8_t *)message->send_buf, RT_NULL,(rt_int32_t)message->length);
        if (message->cs_release)
        {
            bcm283x_gpio_write(hspi->hwcfg->cs_pin, 1);

        }
        if (res != RT_EOK)
            return RT_ERROR;
    }

    /* only receive data */
    if (message->send_buf == RT_NULL)
    {
        if (message->cs_take)
        {
            bcm283x_gpio_write(hspi->hwcfg->cs_pin, 0);
        }
        res = spi_transfernb(RT_NULL,(rt_uint8_t *)message->recv_buf, (rt_int32_t)message->length);
        if (message->cs_release)
        {
            bcm283x_gpio_write(hspi->hwcfg->cs_pin, 1);
        }
        if (res != RT_EOK)
            return RT_ERROR;
    }
    /* send & receive */
    else
    {
        if (message->cs_take)
        {
            bcm283x_gpio_write(hspi->hwcfg->cs_pin, 0);
        }
        res = spi_transfernb((rt_uint8_t *)message->send_buf, (rt_uint8_t *)message->recv_buf,
                (rt_int32_t)message->length);
        if (message->cs_release)
        {
            bcm283x_gpio_write(hspi->hwcfg->cs_pin, 1);
        }
        if (res != RT_EOK)
            return RT_ERROR;
    }

    return message->length;
}

rt_err_t raspi_spi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint32_t pin)
{
    rt_err_t ret;
    rt_int16_t gpio_pin;
    struct rt_spi_device *spi_device;
    struct rt_sw_spi_cs *cs_pin;

    gpio_pin = phypin_index[pin].bcm_id;

    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    cs_pin = (struct rt_sw_spi_cs *)rt_malloc(sizeof(struct rt_sw_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);

    cs_pin->pin = gpio_pin;

    ret = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    return ret;
}

#define DIV_ROUND_UP(n,d)    (((n) + (d) - 1) / (d))
rt_uint16_t spi_clockdivider(rt_uint32_t speed_hz)
{
    rt_uint16_t divider;

    if (speed_hz < (rt_uint32_t) BCM283X_AUX_SPI_CLOCK_MIN)
    {
        speed_hz = (rt_uint32_t) BCM283X_AUX_SPI_CLOCK_MIN;
    }
    else if (speed_hz > (rt_uint32_t) BCM283X_AUX_SPI_CLOCK_MAX)
    {
        speed_hz = (rt_uint32_t) BCM283X_AUX_SPI_CLOCK_MAX;
    }

    divider = (rt_uint16_t) DIV_ROUND_UP(BCM283X_CORE_CLK_HZ, 2 * speed_hz) - 1;

    if (divider > (rt_uint16_t) BCM283X_AUX_SPI_CNTL0_SPEED_MAX)
    {
        return (rt_uint16_t) BCM283X_AUX_SPI_CNTL0_SPEED_MAX;
    }

    return divider;
}

rt_err_t raspi_spi_hw_init(struct rt_spi_hw_config *hwcfg)
{
    volatile rt_uint32_t enable = PER_BASE + BCM283X_AUX_BASE + BCM283X_AUX_ENABLE;
    volatile rt_uint32_t cntl0 = PER_BASE + BCM283X_SPI1_BASE + BCM283X_AUX_SPI_CNTL0;
    volatile rt_uint32_t cntl1 = PER_BASE + BCM283X_SPI1_BASE + BCM283X_AUX_SPI_CNTL1;

    bcm283x_gpio_fsel(hwcfg->sclk_pin, hwcfg->sclk_mode);
    bcm283x_gpio_fsel(hwcfg->miso_pin, hwcfg->miso_mode);
    bcm283x_gpio_fsel(hwcfg->mosi_pin, hwcfg->mosi_mode);
    bcm283x_gpio_fsel(hwcfg->cs_pin, hwcfg->cs_mode);

    hwcfg->clk_div = spi_clockdivider(1000000);     // Default 1MHz SPI

    bcm283x_peri_write(enable, BCM283X_AUX_ENABLE_SPI0);
    bcm283x_peri_write(cntl1, 0);
    bcm283x_peri_write(cntl0, BCM283X_AUX_SPI_CNTL0_CLEARFIFO);

    return RT_EOK;
}

const static struct rt_spi_ops raspi_spi_ops =
{
    .configure = raspi_spi_configure,
    .xfer = raspi_spi_xfer
};

#if defined (BSP_USING_SPI0)
#define SPI0BUS_NAME  "spi0.0"

struct rt_spi_bus raspi_spi0_bus =
{
    .ops = &raspi_spi_ops,
    .parent.user_data = spi0
};

struct rt_spi_hw_config raspi_spi0_hw =
{
    .sclk_pin = BCM_GPIO_PIN_11,
    .sclk_mode = BCM283X_GPIO_FSEL_ALT0,
    .mosi_pin = BCM_GPIO_PIN_10,
    .mosi_mode = BCM283X_GPIO_FSEL_ALT0,
    .miso_pin = BCM_GPIO_PIN_9,
    .miso_mode = BCM283X_GPIO_FSEL_ALT0,
    .cs_pin = BCM_GPIO_PIN_8,
    .cs_mode = BCM283X_GPIO_FSEL_ALT0,
    .spi_base = (PER_BASE + BCM283X_SPI0_BASE),
    .clk_div = 0,
};

struct rt_spi spi0 =
{
    .device_name = SPI0BUS_NAME,
    .spi_bus = &raspi_spi0_bus,
    .hwcfg = &raspi_spi0_hw,
};

#endif

#if defined (BSP_USING_SPI1)
#define SPI1BUS_NAME  "spi0.1"

struct rt_spi_bus raspi_spi1_bus =
{
    .ops = &raspi_spi_ops,
    .parent.user_data = spi1
};

struct rt_spi_hw_config raspi_spi1_hw =
{
    .sclk_pin = BCM_GPIO_PIN_11,
    .sclk_mode = BCM283X_GPIO_FSEL_ALT0,
    .mosi_pin = BCM_GPIO_PIN_10,
    .mosi_mode = BCM283X_GPIO_FSEL_ALT0,
    .miso_pin = BCM_GPIO_PIN_9,
    .miso_mode = BCM283X_GPIO_FSEL_ALT0,
    .cs_pin = BCM_GPIO_PIN_7,
    .cs_mode = BCM283X_GPIO_FSEL_ALT0,
    .spi_base = (PER_BASE + BCM283X_SPI0_BASE),
    .clk_div = 0,
};

struct rt_spi spi1 =
{
    .device_name = SPI1BUS_NAME,
    .spi_bus = &raspi_spi1_bus,
    .hwcfg = &raspi_spi1_hw,
};
#endif

int rt_hw_spi_bus_init(void)
{
#if defined (BSP_USING_SPI0)
    raspi_spi_hw_init(spi0.hwcfg);
    rt_spi_bus_register(spi0.spi_bus, spi0.device_name, spi0.spi_bus->ops);
#endif

#if defined (BSP_USING_SPI1)
    raspi_spi_hw_init(spi1.hwcfg);
    rt_spi_bus_register(spi1.spi_bus, spi1.device_name, spi1.spi_bus->ops);
#endif

    return RT_EOK;
}
INIT_PREV_EXPORT(rt_hw_spi_bus_init);

#endif
