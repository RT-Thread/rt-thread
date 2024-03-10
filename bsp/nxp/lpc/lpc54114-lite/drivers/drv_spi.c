/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "drv_spi.h"

#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_spi.h"

struct lpc_spi
{
    SPI_Type *base;
    struct rt_spi_configuration *cfg;
};

static uint32_t get_spi_freq(SPI_Type *base)
{
    uint32_t freq = 0;

#if defined(BSP_USING_SPI2)
    if(base == SPI2)
    {
        freq = CLOCK_GetFreq(kCLOCK_Flexcomm2);
    }
#endif

    return freq;
}

static rt_err_t spi_init(SPI_Type *base, struct rt_spi_configuration *cfg)
{
    spi_master_config_t masterConfig = {0};

    RT_ASSERT(cfg != RT_NULL);

    if(cfg->data_width != 8 && cfg->data_width != 16)
    {
        return (-RT_EINVAL);
    }

    SPI_MasterGetDefaultConfig(&masterConfig);

    if(cfg->max_hz > 12*1000*1000)
    {
        cfg->max_hz = 12*1000*1000;
    }
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

    masterConfig.txWatermark = kSPI_TxFifo0,
    masterConfig.rxWatermark = kSPI_RxFifo1,

    // masterConfig.sselNum = kSPI_Ssel3;
    SPI_MasterInit(base, &masterConfig, get_spi_freq(base));

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

static rt_err_t configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    rt_err_t ret = RT_EOK;
    struct lpc_spi *spi = RT_NULL;

    RT_ASSERT(cfg != RT_NULL);
    RT_ASSERT(device != RT_NULL);

    spi = (struct lpc_spi *)(device->bus->parent.user_data);
    spi->cfg = cfg;
    ret = spi_init(spi->base, cfg);

    return ret;
}

static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    spi_transfer_t transfer = {0};

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);

    struct lpc_spi *spi = (struct lpc_spi *)(device->bus->parent.user_data);
    struct lpc_sw_spi_cs *cs = device->parent.user_data;

    if(message->cs_take)
    {
        rt_pin_write(cs->pin, PIN_LOW);
    }

    transfer.dataSize = message->length;
    transfer.rxData   = (uint8_t *)(message->recv_buf);
    transfer.txData   = (uint8_t *)(message->send_buf);
    transfer.configFlags |= kSPI_FrameAssert;

    SPI_MasterTransferBlocking(spi->base, &transfer);

    if(message->cs_release)
    {
        rt_pin_write(cs->pin, PIN_HIGH);
    }

    return message->length;
}

#if defined(BSP_USING_SPI2)
static struct lpc_spi spi2 = {0};
static struct rt_spi_bus spi2_bus = {0};
#endif

static struct rt_spi_ops lpc_spi_ops =
{
    configure,
    spixfer
};

int rt_hw_spi_init(void)
{
    CLOCK_EnableClock(kCLOCK_Iocon);

#if defined(BSP_USING_SPI2)
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);
    RESET_PeripheralReset(kFC2_RST_SHIFT_RSTn);

    spi2.base = SPI2;
    spi2.cfg = RT_NULL;
    spi2_bus.parent.user_data = &spi2;

    IOCON_PinMuxSet(IOCON, 0,  8, (IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN));  /* SPI2_MOSI */
    IOCON_PinMuxSet(IOCON, 0,  9, (IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN));  /* SPI2_MISO */
    IOCON_PinMuxSet(IOCON, 0, 10, (IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN));  /* SPI2_SCK  */

    rt_spi_bus_register(&spi2_bus, "spi2", &lpc_spi_ops);
#endif

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);
