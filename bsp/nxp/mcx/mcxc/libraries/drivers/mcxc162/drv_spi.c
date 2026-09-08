/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtdevice.h>

#include "drv_spi.h"
#include "fsl_clock.h"
#include "fsl_lpspi.h"

#if defined(RT_USING_SPI) && defined(BSP_USING_SPI0)

#define MCXC162_LPSPI_INTERNAL_PCS      kLPSPI_Pcs3
#define MCXC162_LPSPI_INTERNAL_PCS_FLAG kLPSPI_MasterPcs3

static struct rt_spi_bus spi0_bus;

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name,
                                 rt_base_t cs_pin)
{
    struct rt_spi_device *device = rt_calloc(1U, sizeof(*device));
    rt_err_t result;

    if (device == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    if (cs_pin != PIN_NONE)
    {
        rt_pin_write(cs_pin, PIN_HIGH);
    }
    result = rt_spi_bus_attach_device_cspin(device, device_name, bus_name,
                                            cs_pin, RT_NULL);
    if (result != RT_EOK)
    {
        rt_free(device);
    }

    return result;
}

static rt_err_t mcxc162_spi_configure(struct rt_spi_device *device,
                                      struct rt_spi_configuration *cfg)
{
    lpspi_master_config_t config;
    uint32_t period_ns;

    (void)device;

    if ((cfg->mode & (RT_SPI_SLAVE | RT_SPI_3WIRE | RT_SPI_READY |
                      RT_SPI_CS_HIGH)) != 0U ||
        (cfg->data_width != 8U && cfg->data_width != 16U) || cfg->max_hz == 0U)
    {
        return -RT_EINVAL;
    }

    LPSPI_MasterGetDefaultConfig(&config);
    config.baudRate = cfg->max_hz;
    config.bitsPerFrame = cfg->data_width;
    config.cpol = (cfg->mode & RT_SPI_CPOL) != 0U ? kLPSPI_ClockPolarityActiveLow : kLPSPI_ClockPolarityActiveHigh;
    config.cpha = (cfg->mode & RT_SPI_CPHA) != 0U ? kLPSPI_ClockPhaseSecondEdge : kLPSPI_ClockPhaseFirstEdge;
    config.direction = (cfg->mode & RT_SPI_MSB) != 0U ? kLPSPI_MsbFirst : kLPSPI_LsbFirst;
    config.whichPcs = MCXC162_LPSPI_INTERNAL_PCS;
    config.pcsActiveHighOrLow = kLPSPI_PcsActiveLow;

    period_ns = 1000000000U / cfg->max_hz;
    config.pcsToSckDelayInNanoSec = period_ns / 2U;
    config.lastSckToPcsDelayInNanoSec = period_ns / 2U;
    config.betweenTransferDelayInNanoSec = period_ns / 2U;

    LPSPI_MasterInit(LPSPI0, &config, CLOCK_GetLpspiClkFreq(0U));
    return RT_EOK;
}

static void mcxc162_spi_set_cs(struct rt_spi_device *device, rt_bool_t active)
{
    rt_uint8_t level;

    if (device->cs_pin == PIN_NONE || (device->config.mode & RT_SPI_NO_CS) != 0U)
    {
        return;
    }

    level = (device->config.mode & RT_SPI_CS_HIGH) != 0U ? PIN_HIGH : PIN_LOW;
    rt_pin_write(device->cs_pin, active ? level : !level);
}

static rt_ssize_t mcxc162_spi_xfer(struct rt_spi_device *device,
                                   struct rt_spi_message *message)
{
    lpspi_transfer_t transfer = {
        .txData = message->send_buf,
        .rxData = message->recv_buf,
        .dataSize = message->length,
        .configFlags = MCXC162_LPSPI_INTERNAL_PCS_FLAG | kLPSPI_MasterPcsContinuous,
    };
    status_t status = kStatus_Success;

    if (message->cs_take != 0U)
    {
        mcxc162_spi_set_cs(device, true);
    }

    if (message->length != 0U)
    {
        status = LPSPI_MasterTransferBlocking(LPSPI0, &transfer);
    }

    if (status != kStatus_Success)
    {
        mcxc162_spi_set_cs(device, false);
        return -RT_EIO;
    }

    if (message->cs_release != 0U)
    {
        mcxc162_spi_set_cs(device, false);
    }

    return (rt_ssize_t)message->length;
}

static const struct rt_spi_ops mcxc162_spi_ops = {
    .configure = mcxc162_spi_configure,
    .xfer = mcxc162_spi_xfer,
};

int rt_hw_spi_init(void)
{
    lpspi_master_config_t config;

    CLOCK_SetClockDiv(kCLOCK_DivLPSPI0, 1U);
    CLOCK_AttachClk(kFRO_LF_DIV_to_LPSPI0);

    LPSPI_MasterGetDefaultConfig(&config);
    LPSPI_MasterInit(LPSPI0, &config, CLOCK_GetLpspiClkFreq(0U));

    return rt_spi_bus_register(&spi0_bus, "spi0", &mcxc162_spi_ops);
}
INIT_DEVICE_EXPORT(rt_hw_spi_init);

#endif /* RT_USING_SPI && BSP_USING_SPI0 */
