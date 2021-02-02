/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-31     ZYH          first version
 * 2018-12-10     Zohar_Lee    format file
 * 2020-07-10     lik          format file
 */

#include "drv_spi.h"

#ifdef RT_USING_SPI
#ifdef BSP_USING_SPI

//#define DRV_DEBUG
#define LOG_TAG "drv.spi"
#include <drv_log.h>

static struct swm_spi_cfg spi_cfg[] =
    {
#ifdef BSP_USING_SPI0
        SPI0_BUS_CONFIG,
#endif
#ifdef BSP_USING_SPI1
        SPI1_BUS_CONFIG,
#endif
};

static struct swm_spi spi_bus_drv[sizeof(spi_cfg) / sizeof(spi_cfg[0])] = {0};

static rt_err_t swm_spi_init(struct swm_spi *spi_drv, struct rt_spi_configuration *configure)
{
    RT_ASSERT(spi_drv != RT_NULL);
    RT_ASSERT(configure != RT_NULL);

    struct swm_spi_cfg *cfg = spi_drv->cfg;

    if (configure->mode & RT_SPI_SLAVE)
    {
        cfg->spi_initstruct.Master = 0;
    }
    else
    {
        cfg->spi_initstruct.Master = 1;
    }

    if (configure->mode & RT_SPI_3WIRE)
    {
        return RT_EINVAL;
    }

    if (configure->data_width == 8)
    {
        cfg->spi_initstruct.WordSize = 8;
    }
    else if (configure->data_width == 16)
    {
        cfg->spi_initstruct.WordSize = 16;
    }
    else
    {
        return RT_EIO;
    }

    if (configure->mode & RT_SPI_CPHA)
    {
        cfg->spi_initstruct.SampleEdge = SPI_SECOND_EDGE;
    }
    else
    {
        cfg->spi_initstruct.SampleEdge = SPI_FIRST_EDGE;
    }

    if (configure->mode & RT_SPI_CPOL)
    {
        cfg->spi_initstruct.IdleLevel = SPI_HIGH_LEVEL;
    }
    else
    {
        cfg->spi_initstruct.IdleLevel = SPI_LOW_LEVEL;
    }

    if (configure->max_hz >= SystemCoreClock / 4)
    {
        cfg->spi_initstruct.clkDiv = SPI_CLKDIV_4;
    }
    else if (configure->max_hz >= SystemCoreClock / 8)
    {
        cfg->spi_initstruct.clkDiv = SPI_CLKDIV_8;
    }
    else if (configure->max_hz >= SystemCoreClock / 16)
    {
        cfg->spi_initstruct.clkDiv = SPI_CLKDIV_16;
    }
    else if (configure->max_hz >= SystemCoreClock / 32)
    {
        cfg->spi_initstruct.clkDiv = SPI_CLKDIV_32;
    }
    else if (configure->max_hz >= SystemCoreClock / 64)
    {
        cfg->spi_initstruct.clkDiv = SPI_CLKDIV_64;
    }
    else if (configure->max_hz >= SystemCoreClock / 128)
    {
        cfg->spi_initstruct.clkDiv = SPI_CLKDIV_128;
    }
    else if (configure->max_hz >= SystemCoreClock / 256)
    {
        cfg->spi_initstruct.clkDiv = SPI_CLKDIV_256;
    }
    else
    {
        /*  min prescaler 512 */
        cfg->spi_initstruct.clkDiv = SPI_CLKDIV_512;
    }

    SPI_Init(cfg->SPIx, &(cfg->spi_initstruct));
    SPI_Open(cfg->SPIx);
    LOG_D("%s init done", cfg->name);
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

static rt_err_t spitxrx1b(struct swm_spi *spi_drv, void *rcvb, const void *sndb)
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
    while (SPI_IsTXFull(spi_drv->cfg->SPIx))
        ;
    SPISEND_1(spi_drv->cfg->SPIx->DATA, sndb, spi_drv->cfg->spi_initstruct.WordSize);
    while (SPI_IsRXEmpty(spi_drv->cfg->SPIx))
        ;
    SPIRECV_1(spi_drv->cfg->SPIx->DATA, rcvb, spi_drv->cfg->spi_initstruct.WordSize);
    return RT_EOK;
}

static rt_uint32_t swm_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_err_t res;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    struct swm_spi *spi_drv = rt_container_of(device->bus, struct swm_spi, spi_bus);
    struct swm_spi_cfg *cfg = spi_drv->cfg;
    struct swm_spi_cs *cs = device->parent.user_data;

    if (message->cs_take)
    {
        GPIO_ClrBit(cs->GPIOx, cs->gpio_pin);
    }

    LOG_D("%s transfer prepare and start", cfg->name);
    LOG_D("%s sendbuf: %X, recvbuf: %X, length: %d",
          cfg->name, (uint32_t)message->send_buf, (uint32_t)message->recv_buf, message->length);

    const rt_uint8_t *sndb = message->send_buf;
    rt_uint8_t *rcvb = message->recv_buf;
    rt_int32_t length = message->length;

    while (length)
    {
        res = spitxrx1b(spi_drv, rcvb, sndb);
        if (rcvb)
        {
            rcvb += SPISTEP(cfg->spi_initstruct.WordSize);
        }
        if (sndb)
        {
            sndb += SPISTEP(cfg->spi_initstruct.WordSize);
        }
        if (res != RT_EOK)
        {
            break;
        }
        length--;
    }
    /* Wait until Busy flag is reset before disabling SPI */
    while (!SPI_IsTXEmpty(cfg->SPIx) && !SPI_IsRXEmpty(cfg->SPIx))
        ;
    if (message->cs_release)
    {
        GPIO_SetBit(cs->GPIOx, cs->gpio_pin);
    }
    return message->length - length;
}

static rt_err_t swm_spi_configure(struct rt_spi_device *device,
                                  struct rt_spi_configuration *configure)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configure != RT_NULL);

    struct swm_spi *spi_drv = rt_container_of(device->bus, struct swm_spi, spi_bus);
    spi_drv->configure = configure;

    return swm_spi_init(spi_drv, configure);
}
const static struct rt_spi_ops swm_spi_ops =
    {
        .configure = swm_spi_configure,
        .xfer = swm_spi_xfer,
};

//cannot be used before completion init
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_TypeDef *cs_gpiox, uint32_t cs_gpio_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;
    struct swm_spi_cs *cs_pin;

    GPIO_Init(cs_gpiox, cs_gpio_pin, 1, 0, 0);
    GPIO_SetBit(cs_gpiox, cs_gpio_pin);

    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    cs_pin = (struct swm_spi_cs *)rt_malloc(sizeof(struct swm_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->GPIOx = cs_gpiox;
    cs_pin->gpio_pin = cs_gpio_pin;

    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);
    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }
    RT_ASSERT(result == RT_EOK);
    LOG_D("%s attach to %s done", device_name, bus_name);
    return result;
}

int rt_hw_spi_init(void)
{
    rt_err_t result;

#ifdef BSP_USING_SPI0
    PORT_Init(PORTA, PIN9, FUNMUX1_SPI0_SCLK, 0);
    PORT_Init(PORTA, PIN10, FUNMUX0_SPI0_MOSI, 0);
    PORT_Init(PORTA, PIN11, FUNMUX1_SPI0_MISO, 1);
#endif //BSP_USING_SPI0

#ifdef BSP_USING_SPI1
    PORT_Init(PORTC, PIN7, FUNMUX1_SPI1_SCLK, 0);
    PORT_Init(PORTC, PIN6, FUNMUX0_SPI1_MOSI, 0);
    PORT_Init(PORTC, PIN5, FUNMUX1_SPI1_MISO, 1);
#endif //BSP_USING_SPI1
    for (int i = 0; i < sizeof(spi_cfg) / sizeof(spi_cfg[0]); i++)
    {
        spi_bus_drv[i].cfg = &spi_cfg[i];
        spi_bus_drv[i].spi_bus.parent.user_data = &spi_cfg[i];
        result = rt_spi_bus_register(&spi_bus_drv[i].spi_bus, spi_cfg[i].name, &swm_spi_ops);
        RT_ASSERT(result == RT_EOK);

        LOG_D("%s bus init done", spi_config[i].bus_name);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* BSP_USING_SPI */
#endif /* RT_USING_SPI */
