/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-31     ZYH          first version
 * 2018-12-10     Zohar_Lee    format file
 */

#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <SWM320_port.h>
#include <rthw.h>
#include <drv_spi.h>

#define SPIRXEVENT 0x01
#define SPITXEVENT 0x02
#define SPITIMEOUT 2
#define SPICRCEN 0

struct swm320_spi
{
    SPI_TypeDef *swm320_spi;
    struct rt_spi_configuration *cfg;
};

static rt_err_t swm320_spi_init(SPI_TypeDef *spix,
                                struct rt_spi_configuration *cfg)
{
    SPI_InitStructure SPI_initStruct;
    if (cfg->mode & RT_SPI_SLAVE)
    {
        SPI_initStruct.Master = 0;
    }
    else
    {
        SPI_initStruct.Master = 1;
    }
    if (cfg->mode & RT_SPI_3WIRE)
    {
        return RT_EINVAL;
    }
    if (cfg->data_width == 8)
    {
        SPI_initStruct.WordSize = 8;
    }
    else if (cfg->data_width == 16)
    {
        SPI_initStruct.WordSize = 16;
    }
    else
    {
        return RT_EINVAL;
    }
    if (cfg->mode & RT_SPI_CPHA)
    {
        SPI_initStruct.SampleEdge = SPI_SECOND_EDGE;
    }
    else
    {
        SPI_initStruct.SampleEdge = SPI_FIRST_EDGE;
    }
    if (cfg->mode & RT_SPI_CPOL)
    {
        SPI_initStruct.IdleLevel = SPI_HIGH_LEVEL;
    }
    else
    {
        SPI_initStruct.IdleLevel = SPI_LOW_LEVEL;
    }
    if (cfg->max_hz >= SystemCoreClock / 4)
    {
        SPI_initStruct.clkDiv = SPI_CLKDIV_4;
    }
    else if (cfg->max_hz >= SystemCoreClock / 8)
    {
        SPI_initStruct.clkDiv = SPI_CLKDIV_8;
    }
    else if (cfg->max_hz >= SystemCoreClock / 16)
    {
        SPI_initStruct.clkDiv = SPI_CLKDIV_16;
    }
    else if (cfg->max_hz >= SystemCoreClock / 32)
    {
        SPI_initStruct.clkDiv = SPI_CLKDIV_32;
    }
    else if (cfg->max_hz >= SystemCoreClock / 64)
    {
        SPI_initStruct.clkDiv = SPI_CLKDIV_64;
    }
    else if (cfg->max_hz >= SystemCoreClock / 128)
    {
        SPI_initStruct.clkDiv = SPI_CLKDIV_128;
    }
    else if (cfg->max_hz >= SystemCoreClock / 256)
    {
        SPI_initStruct.clkDiv = SPI_CLKDIV_256;
    }
    else
    {
        /*  min prescaler 512 */
        SPI_initStruct.clkDiv = SPI_CLKDIV_512;
    }
    SPI_initStruct.FrameFormat = SPI_FORMAT_SPI;
    SPI_initStruct.RXHFullIEn = 0;
    SPI_initStruct.TXEmptyIEn = 0;
    SPI_initStruct.TXCompleteIEn = 0;
    SPI_Init(spix, &SPI_initStruct);
    SPI_Open(spix);
    return RT_EOK;
}

#define SPISTEP(datalen) (((datalen) == 8) ? 1 : 2)
#define SPISEND_1(reg, ptr, datalen)       \
    do                                     \
    {                                      \
        if (datalen == 8)                  \
        {                                  \
            (reg) = *(rt_uint8_t *)(ptr);  \
        }                                  \
        else                               \
        {                                  \
            (reg) = *(rt_uint16_t *)(ptr); \
        }                                  \
    } while (0)
#define SPIRECV_1(reg, ptr, datalen)      \
    do                                    \
    {                                     \
        if (datalen == 8)                 \
        {                                 \
            *(rt_uint8_t *)(ptr) = (reg); \
        }                                 \
        else                              \
        {                                 \
            *(rt_uint16_t *)(ptr) = reg;  \
        }                                 \
    } while (0)

static rt_err_t spitxrx1b(struct swm320_spi *hspi, void *rcvb, const void *sndb)
{
    rt_uint32_t padrcv = 0;
    rt_uint32_t padsnd = 0xFF;
    if (!rcvb && !sndb)
    {
        return RT_ERROR;
    }
    if (!rcvb)
    {
        rcvb = &padrcv;
    }
    if (!sndb)
    {
        sndb = &padsnd;
    }
    while (SPI_IsTXFull(hspi->swm320_spi));
    SPISEND_1(hspi->swm320_spi->DATA, sndb, hspi->cfg->data_width);
    while (SPI_IsRXEmpty(hspi->swm320_spi));
    SPIRECV_1(hspi->swm320_spi->DATA, rcvb, hspi->cfg->data_width);
    return RT_EOK;
}

static rt_uint32_t swm320_spi_xfer(struct rt_spi_device *device,
                                   struct rt_spi_message *message)
{
    rt_err_t res;
    struct swm320_spi *hspi = (struct swm320_spi *)device->bus->parent.user_data;
    struct swm320_spi_cs *cs = device->parent.user_data;
    const rt_uint8_t *sndb = message->send_buf;
    rt_uint8_t *rcvb = message->recv_buf;
    rt_int32_t length = message->length;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    if (message->cs_take)
    {
        rt_pin_write(cs->pin, 0);
    }
    while (length)
    {
        res = spitxrx1b(hspi, rcvb, sndb);
        if (rcvb)
        {
            rcvb += SPISTEP(hspi->cfg->data_width);
        }
        if (sndb)
        {
            sndb += SPISTEP(hspi->cfg->data_width);
        }
        if (res != RT_EOK)
        {
            break;
        }
        length--;
    }
    /* Wait until Busy flag is reset before disabling SPI */
    while (!SPI_IsTXEmpty(hspi->swm320_spi) && !SPI_IsRXEmpty(hspi->swm320_spi));
    if (message->cs_release)
    {
        rt_pin_write(cs->pin, 1);
    }
    return message->length - length;
}

static rt_err_t swm320_spi_configure(struct rt_spi_device *device,
                                     struct rt_spi_configuration *configuration)
{
    struct swm320_spi *hspi = (struct swm320_spi *)device->bus->parent.user_data;
    hspi->cfg = configuration;
    return swm320_spi_init(hspi->swm320_spi, configuration);
}
const static struct rt_spi_ops swm320_spi_ops =
{
    .configure = swm320_spi_configure,
    .xfer = swm320_spi_xfer,
};

#ifdef BSP_USING_SPI0
    static struct rt_spi_bus swm320_spi_bus0;
    static struct swm320_spi swm320_spi0;
#endif //BSP_USING_SPI0

#ifdef BSP_USING_SPI1
    static struct rt_spi_bus swm320_spi_bus1;
    static struct swm320_spi swm320_spi1;
#endif //BSP_USING_SPI1

static int swm320_spi_register_bus(SPI_TypeDef *SPIx, const char *name)
{
    struct rt_spi_bus *spi_bus;
    struct swm320_spi *swm320_spi;
    if (SPIx == SPI0)
    {
        PORT_Init(PORTC, PIN5, FUNMUX1_SPI0_SCLK, 0);
        PORT_Init(PORTC, PIN6, FUNMUX0_SPI0_MOSI, 0);
        PORT_Init(PORTC, PIN7, FUNMUX1_SPI0_MISO, 1);
        spi_bus = &swm320_spi_bus0;
        swm320_spi = &swm320_spi0;
    }
    else if (SPIx == SPI1)
    {
        PORT_Init(PORTM, PIN5, FUNMUX1_SPI1_SCLK, 0);
        PORT_Init(PORTC, PIN2, FUNMUX0_SPI1_MOSI, 0);
        PORT_Init(PORTC, PIN3, FUNMUX1_SPI1_MISO, 1);
        spi_bus = &swm320_spi_bus1;
        swm320_spi = &swm320_spi1;
    }
    else
    {
        return -1;
    }
    swm320_spi->swm320_spi = SPIx;
    spi_bus->parent.user_data = swm320_spi;
    return rt_spi_bus_register(spi_bus, name, &swm320_spi_ops);
}

//cannot be used before completion init
static rt_err_t swm320_spi_bus_attach_device(rt_uint32_t pin,
                                             const char *bus_name,
                                             const char *device_name)
{
    struct rt_spi_device *spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    struct swm320_spi_cs *cs_pin = (struct swm320_spi_cs *)rt_malloc(sizeof(struct swm320_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->pin = pin;
    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_pin_write(pin, 1);
    return rt_spi_bus_attach_device(spi_device,
                                    device_name,
                                    bus_name,
                                    (void *)cs_pin);
}

int rt_hw_spi_init(void)
{
    int result = 0;
#ifdef BSP_USING_SPI0
    result = swm320_spi_register_bus(SPI0, "spi0");
#endif
#ifdef BSP_USING_SPI1
    result = swm320_spi_register_bus(SPI1, "spi1");
#endif
    return result;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);
