/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-1      hywing       The first version for MCXA
 */
#include "rtdevice.h"
#include "drv_spi.h"
#include "fsl_lpspi.h"


#ifdef RT_USING_SPI

#define DBG_TAG    "drv.spi"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

enum
{
#ifdef BSP_USING_SPI0
    SPI0_INDEX,
#endif
#ifdef BSP_USING_SPI1
    SPI1_INDEX,
#endif
};

struct lpc_spi
{
    struct rt_spi_bus           parent;
    LPSPI_Type                  *LPSPIx;
    clock_attach_id_t           clock_attach_id;
    clock_div_name_t            clock_div_name;
    clock_name_t                clock_name;


    rt_sem_t                    sem;
    char                        *name;
};

static struct lpc_spi lpc_obj[] =
{
#ifdef BSP_USING_SPI0
    {
        .LPSPIx = LPSPI0,
#if (defined(CPU_MCXA346VLH) || defined(CPU_MCXA346VLL) || defined(CPU_MCXA346VLQ) || defined(CPU_MCXA346VPN))
        kFRO_LF_DIV_to_LPSPI0,
#else
        .clock_attach_id = kFRO12M_to_LPSPI0,
#endif
        .clock_div_name = kCLOCK_DivLPSPI0,
        .clock_name = kCLOCK_Fro12M,
        .name = "spi0",
    },
#endif
#ifdef BSP_USING_SPI1
    {
        .LPSPIx = LPSPI1,
#if (defined(CPU_MCXA346VLH) || defined(CPU_MCXA346VLL) || defined(CPU_MCXA346VLQ) || defined(CPU_MCXA346VPN))
        kFRO_LF_DIV_to_LPSPI1,
#else
        .clock_attach_id = kFRO12M_to_LPSPI1,
#endif
        .clock_div_name = kCLOCK_DivLPSPI1,
        .clock_name = kCLOCK_Fro12M,
        .name = "spi1",
    },
#endif
};

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t pin)
{
    struct rt_spi_device *spi_device = rt_malloc(sizeof(struct rt_spi_device));
    if (!spi_device)
    {
        return -RT_ENOMEM;
    }

    return rt_spi_bus_attach_device_cspin(spi_device, device_name, bus_name, pin, NULL);
}

static rt_err_t spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    return RT_EOK;
}



static rt_ssize_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    lpspi_transfer_t transfer = {0};
    status_t status;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);

    struct lpc_spi *spi = device->bus->parent.user_data;

    if (message->cs_take)
    {
        rt_pin_write(device->cs_pin, PIN_LOW);
    }

    transfer.dataSize = message->length;
    transfer.rxData   = (uint8_t *)(message->recv_buf);
    transfer.txData   = (uint8_t *)(message->send_buf);
    transfer.configFlags = kLPSPI_MasterPcs0;

    // Use blocking transfer instead of DMA
    status = LPSPI_MasterTransferBlocking(spi->LPSPIx, &transfer);

    if (message->cs_release)
    {
        rt_pin_write(device->cs_pin, PIN_HIGH);
    }

    if (status != kStatus_Success)
    {
        return 0; // Transfer failed
    }

    return message->length;
}


static struct rt_spi_ops lpc_spi_ops =
{
    .configure = spi_configure,
    .xfer      = spixfer
};

int rt_hw_spi_init(void)
{
    int i;

    for (i = 0; i < ARRAY_SIZE(lpc_obj); i++)
    {
        CLOCK_SetClockDiv(lpc_obj[i].clock_div_name, 1u);
        CLOCK_AttachClk(lpc_obj[i].clock_attach_id);

        lpc_obj[i].parent.parent.user_data = &lpc_obj[i];
        lpc_obj[i].sem = rt_sem_create("sem_spi", 0, RT_IPC_FLAG_FIFO);

        lpspi_master_config_t masterConfig;
        LPSPI_MasterGetDefaultConfig(&masterConfig);
        masterConfig.baudRate = 10 * 1000 * 1000;
        masterConfig.pcsToSckDelayInNanoSec        = 1000000000U / masterConfig.baudRate * 1U;
        masterConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / masterConfig.baudRate * 1U;
        masterConfig.betweenTransferDelayInNanoSec = 1000000000U / masterConfig.baudRate * 1U;

        LPSPI_MasterInit(lpc_obj[i].LPSPIx, &masterConfig, CLOCK_GetFreq(lpc_obj[i].clock_name));

        rt_spi_bus_register(&lpc_obj[i].parent, lpc_obj[i].name, &lpc_spi_ops);
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_spi_init);

#endif /* RT_USING_SPI */

