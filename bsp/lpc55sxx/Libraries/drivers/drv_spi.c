/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-15     Magicoe      The first version for LPC55S6x
 */
#include "drv_spi.h"

#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_spi.h"


#if defined(BSP_USING_SPIBUS0) || \
    defined(BSP_USING_SPIBUS1) || \
    defined(BSP_USING_SPIBUS2) || \
    defined(BSP_USING_SPIBUS3) || \
    defined(BSP_USING_SPIBUS4) || \
    defined(BSP_USING_SPIBUS5) || \
    defined(BSP_USING_SPIBUS6) || \
    defined(BSP_USING_SPIBUS7) || \
    defined(BSP_USING_SPIBUS8)

#if defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL
    #error "Please don't define 'FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL'!"
#endif

struct lpc_spi
{iteopuywqt[riouqwyyyyyyyyyyyy
    SPI_Type *base;
    struct rt_spi_configuration *cfg;
    SYSCON_RSTn_t spi_rst;
};

struct lpc_sw_spi_cs
{
    rt_uint32_t pin;
};


static uint32_t lpc_get_spi_freq(SPI_Type *base)
{
    uint32_t freq = 0;

#if defined(BSP_USING_SPIBUS0)
    if(base == SPI0)
    {
        freq = CLOCK_GetFreq(kCLOCK_Flexcomm0);
    }
#endif

#if defined(BSP_USING_SPIBUS1)
    if(base == SPI1)
    {
        freq = CLOCK_GetFreq(kCLOCK_Flexcomm1);
    }
#endif

#if defined(BSP_USING_SPIBUS2)
    if(base == SPI2)
    {
        freq = CLOCK_GetFreq(kCLOCK_Flexcomm2);
    }
#endif

#if defined(BSP_USING_SPIBUS3)
    if(base == SPI3)
    {
        freq = CLOCK_GetFreq(kCLOCK_Flexcomm3);
    }
#endif

#if defined(BSP_USING_SPIBUS4)
    if(base == SPI4)
    {
        freq = CLOCK_GetFreq(kCLOCK_Flexcomm4);
    }
#endif

#if defined(BSP_USING_SPIBUS5)
    if(base == SPI5)
    {
        freq = CLOCK_GetFreq(kCLOCK_Flexcomm5);
    }
#endif

#if defined(BSP_USING_SPIBUS6)
    if(base == SPI6)
    {
        freq = CLOCK_GetFreq(kCLOCK_Flexcomm6);
    }
#endif

#if defined(BSP_USING_SPIBUS7)
    if(base == SPI7)
    {
        freq = CLOCK_GetFreq(kCLOCK_Flexcomm7);
    }
#endif

    /* High Speed SPI - 50MHz */
#if defined(BSP_USING_SPIBUS8)
    if(base == SPI8)
    {
        freq = CLOCK_GetFreq(kCLOCK_HsLspi);
    }
#endif

    return freq;
}

static rt_err_t lpc_spi_init(SPI_Type *base, struct rt_spi_configuration *cfg)
{
    spi_master_config_t masterConfig = {0};

    RT_ASSERT(cfg != RT_NULL);

    if(cfg->data_width != 8 && cfg->data_width != 16)
    {
        return (-RT_EINVAL);
    }


    SPI_MasterGetDefaultConfig(&masterConfig);

#if defined(BSP_USING_SPIBUS8)
    if(base == SPI8)
    {
        if(cfg->max_hz > 50*1000*1000)
        {
            cfg->max_hz = 50*1000*1000;
        }
    }
#else
    if(cfg->max_hz > 12*1000*1000)
    {
        cfg->max_hz = 12*1000*1000;
    }
#endif

    masterConfig.baudRate_Bps = cfg->max_hz;

    if(cfg->data_width == 8)
    {
        masterConfig.dataWidth = kSPI_Data8Bits;
    }
    else if(cfg->data_width == 16)
    {
        masterConfig.dataWidth = kSPI_Data16Bits;
    }

    if(cfg->mode & RT_SPI_MSB)
    {
        masterConfig.direction = kSPI_MsbFirst;
    }
    else
    {
        masterConfig.direction = kSPI_LsbFirst;
    }

    if(cfg->mode & RT_SPI_CPHA)
    {
        masterConfig.phase = kSPI_ClockPhaseSecondEdge;
    }
    else
    {
        masterConfig.phase = kSPI_ClockPhaseFirstEdge;
    }

    if(cfg->mode & RT_SPI_CPOL)
    {
        masterConfig.polarity = kSPI_ClockPolarityActiveLow;
    }
    else
    {
        masterConfig.polarity = kSPI_ClockPolarityActiveHigh;
    }

    SPI_MasterInit(base, &masterConfig, lpc_get_spi_freq(base));

    return RT_EOK;
}

rt_err_t lpc_spi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint32_t pin)
{
    rt_err_t ret = RT_EOK;

    struct rt_spi_device *spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    struct lpc_sw_spi_cs *cs_pin = (struct lpc_sw_spi_cs *)rt_malloc(sizeof(struct lpc_sw_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);

    cs_pin->pin = pin;
    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_pin_write(pin, PIN_HIGH);

    ret = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    return ret;
}

static rt_err_t spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    rt_err_t ret = RT_EOK;
    struct lpc_spi *spi = RT_NULL;

    RT_ASSERT(cfg != RT_NULL);
    RT_ASSERT(device != RT_NULL);

    spi = (struct lpc_spi *)(device->bus->parent.user_data);
    spi->cfg = cfg;
    ret = lpc_spi_init(spi->base, cfg);

    return ret;
}

#define SPISTEP(datalen) (((datalen) == 8) ? 1 : 2)
static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    uint32_t length;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);

    struct lpc_spi *spi = (struct lpc_spi *)(device->bus->parent.user_data);
    struct lpc_sw_spi_cs *cs = device->parent.user_data;

    if(message->cs_take)
    {
        rt_pin_write(cs->pin, PIN_LOW);
    }

    length = message->length;
    const rt_uint8_t *txData  = (uint8_t *)(message->send_buf);
    rt_uint8_t *rxData  = (uint8_t *)(message->recv_buf);

    rt_kprintf("*** spi send %d\r\n", length);

    while (length)
    {
        /* clear tx/rx errors and empty FIFOs */
        spi->base->FIFOCFG |= SPI_FIFOCFG_EMPTYTX_MASK | SPI_FIFOCFG_EMPTYRX_MASK;
        spi->base->FIFOSTAT |= SPI_FIFOSTAT_TXERR_MASK | SPI_FIFOSTAT_RXERR_MASK;
        spi->base->FIFOWR = *txData | 0x07300000;
        /* wait if TX FIFO of previous transfer is not empty */
        while ((spi->base->FIFOSTAT & SPI_FIFOSTAT_RXNOTEMPTY_MASK) == 0) {
        }
        if(rxData != NULL)
        {
            *rxData = spi->base->FIFORD;
            rxData += SPISTEP(spi->cfg->data_width);
        }
        txData += SPISTEP(spi->cfg->data_width);;
        length--;
    }

    if(message->cs_release)
    {
        rt_pin_write(cs->pin, PIN_HIGH);
    }

    return (message->length - length);
}

#if defined(BSP_USING_SPIBUS0)
static struct lpc_spi spi0 =
{
    .base = SPI0
};
static struct rt_spi_bus spi0_bus =
{
    .parent.user_data = &spi0
};
#endif

#if defined(BSP_USING_SPIBUS1)
static struct lpc_spi spi1 =
{
    .base = SPI1
};
static struct rt_spi_bus spi1_bus =
{
    .parent.user_data = &spi1
};
#endif

#if defined(BSP_USING_SPIBUS2)
static struct lpc_spi spi2 =
{
    .base = SPI2
};
static struct rt_spi_bus spi2_bus =
{
    .parent.user_data = &spi2
};
#endif

#if defined(BSP_USING_SPIBUS3)
static struct lpc_spi spi3 =
{
    .base = SPI3
};
static struct rt_spi_bus spi3_bus =
{
    .parent.user_data = &spi3
};
#endif

#if defined(BSP_USING_SPIBUS4)
static struct lpc_spi spi4 =
{
    .base = SPI4
};
static struct rt_spi_bus spi4_bus =
{
    .parent.user_data = &spi4
};
#endif

#if defined(BSP_USING_SPIBUS5)
static struct lpc_spi spi5 =
{
    .base = SPI5
};
static struct rt_spi_bus spi5_bus =
{
    .parent.user_data = &spi5
};
#endif

#if defined(BSP_USING_SPIBUS6)
static struct lpc_spi spi6 =
{
    .base = SPI6
};
static struct rt_spi_bus spi6_bus =
{
    .parent.user_data = &spi6
};
#endif

#if defined(BSP_USING_SPIBUS7)
static struct lpc_spi spi7 =
{
    .base = SPI7
};
static struct rt_spi_bus spi7_bus =
{
    .parent.user_data = &spi7
};
#endif

#if defined(BSP_USING_SPIBUS8)
static struct lpc_spi spi8 =
{
    .base = SPI8
};
static struct rt_spi_bus spi8_bus =
{
    .parent.user_data = &spi8
};
#endif


static struct rt_spi_ops lpc_spi_ops =
{
    .configure = spi_configure,
    .xfer      = spixfer
};

int rt_hw_spi_init(void)
{
#if defined(BSP_USING_SPIBUS0)
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM0);
    RESET_PeripheralReset(kFC0_RST_SHIFT_RSTn);
    spi0.cfg = RT_NULL;
    rt_spi_bus_register(&spi0_bus, "spi0", &lpc_spi_ops);
#endif

#if defined(BSP_USING_SPIBUS1)
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM1);
    RESET_PeripheralReset(kFC1_RST_SHIFT_RSTn);

    spi1.cfg = RT_NULL;
    rt_spi_bus_register(&spi1_bus, "spi1", &lpc_spi_ops);
#endif

#if defined(BSP_USING_SPIBUS2)
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);
    RESET_PeripheralReset(kFC2_RST_SHIFT_RSTn);
    spi2.cfg = RT_NULL;
    rt_spi_bus_register(&spi2_bus, "spi2", &lpc_spi_ops);
#endif

#if defined(BSP_USING_SPIBUS3)
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM3);
    RESET_PeripheralReset(kFC3_RST_SHIFT_RSTn);
    spi3.cfg = RT_NULL;
    rt_spi_bus_register(&spi3_bus, "spi3", &lpc_spi_ops);
#endif

#if defined(BSP_USING_SPIBUS4)
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4);
    RESET_PeripheralReset(kFC4_RST_SHIFT_RSTn);
    spi4.cfg = RT_NULL;
    rt_spi_bus_register(&spi4_bus, "spi4", &lpc_spi_ops);
#endif

#if defined(BSP_USING_SPIBUS5)
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM5);
    RESET_PeripheralReset(kFC5_RST_SHIFT_RSTn);
    spi5.cfg = RT_NULL;
    rt_spi_bus_register(&spi5_bus, "spi5", &lpc_spi_ops);
#endif

#if defined(BSP_USING_SPIBUS6)
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM6);
    RESET_PeripheralReset(kFC6_RST_SHIFT_RSTn);
    spi6.cfg = RT_NULL;
    rt_spi_bus_register(&spi6_bus, "spi6", &lpc_spi_ops);
#endif

#if defined(BSP_USING_SPIBUS7)
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM7);
    RESET_PeripheralReset(kFC7_RST_SHIFT_RSTn);
    spi7.cfg = RT_NULL;
    rt_spi_bus_register(&spi7_bus, "spi7", &lpc_spi_ops);
#endif

#if defined(BSP_USING_SPIBUS8)
    CLOCK_AttachClk(kMAIN_CLK_to_HSLSPI);
    RESET_PeripheralReset(kHSLSPI_RST_SHIFT_RSTn);
    spi8.cfg = RT_NULL;
    spi8.spi_rst = kHSLSPI_RST_SHIFT_RSTn;
    rt_spi_bus_register(&spi8_bus, "spi8", &lpc_spi_ops);
#endif

    return RT_EOK;
}

INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif
