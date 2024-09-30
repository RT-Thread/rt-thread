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
#include "fsl_lpspi_edma.h"

#define DMA_MAX_TRANSFER_SIZE (32767)

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

    DMA_Type                    *DMAx;
    uint8_t                     tx_dma_chl;
    uint8_t                     rx_dma_chl;
    edma_handle_t               dma_tx_handle;
    edma_handle_t               dma_rx_handle;
    dma_request_source_t        tx_dma_request;
    dma_request_source_t        rx_dma_request;
    lpspi_master_edma_handle_t  spi_dma_handle;

    rt_sem_t                    sem;
    char                        *name;
};

static struct lpc_spi lpc_obj[] =
{
#ifdef BSP_USING_SPI0
    {
        .LPSPIx = LPSPI0,
        .clock_attach_id = kFRO12M_to_LPSPI0,
        .clock_div_name = kCLOCK_DivLPSPI0,
        .clock_name = kCLOCK_Fro12M,
        .tx_dma_request = kDma0RequestLPSPI0Tx,
        .rx_dma_request = kDma0RequestLPSPI0Rx,
        .DMAx = DMA0,
        .tx_dma_chl = 0,
        .rx_dma_chl = 1,
        .name = "spi0",
    },
#endif
#ifdef BSP_USING_SPI1
    {
        .LPSPIx = LPSPI1,
        .clock_attach_id = kFRO12M_to_LPSPI1,
        .clock_div_name = kCLOCK_DivLPSPI1,
        .clock_name = kCLOCK_Fro12M,
        .tx_dma_request = kDma0RequestLPSPI1Tx,
        .rx_dma_request = kDma0RequestLPSPI1Rx,
        .DMAx = DMA0,
        .tx_dma_chl = 0,
        .rx_dma_chl = 1,
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

static void LPSPI_MasterUserCallback(LPSPI_Type *base, lpspi_master_edma_handle_t *handle, status_t status, void *userData)
{
    struct lpc_spi *spi = (struct lpc_spi *)userData;
    rt_sem_release(spi->sem);

}

static rt_ssize_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    int i;
    lpspi_transfer_t transfer = {0};

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

    /*  if(message->length < MAX_DMA_TRANSFER_SIZE)*/
    uint32_t block, remain;
    block = message->length / DMA_MAX_TRANSFER_SIZE;
    remain = message->length % DMA_MAX_TRANSFER_SIZE;

    for (i = 0; i < block; i++)
    {
        transfer.dataSize = DMA_MAX_TRANSFER_SIZE;
        if (message->recv_buf) transfer.rxData   = (uint8_t *)(message->recv_buf + i *DMA_MAX_TRANSFER_SIZE);
        if (message->send_buf) transfer.txData   = (uint8_t *)(message->send_buf + i *DMA_MAX_TRANSFER_SIZE);

        LPSPI_MasterTransferEDMA(spi->LPSPIx, &spi->spi_dma_handle, &transfer);
        rt_sem_take(spi->sem, RT_WAITING_FOREVER);
    }

    if (remain)
    {
        transfer.dataSize = remain;
        if (message->recv_buf) transfer.rxData   = (uint8_t *)(message->recv_buf + i *DMA_MAX_TRANSFER_SIZE);
        if (message->send_buf) transfer.txData   = (uint8_t *)(message->send_buf + i *DMA_MAX_TRANSFER_SIZE);

        LPSPI_MasterTransferEDMA(spi->LPSPIx, &spi->spi_dma_handle, &transfer);
        rt_sem_take(spi->sem, RT_WAITING_FOREVER);
    }

    if (message->cs_release)
    {
        rt_pin_write(device->cs_pin, PIN_HIGH);
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
        masterConfig.baudRate = 1 * 1000 * 1000;
        masterConfig.pcsToSckDelayInNanoSec        = 1000000000U / masterConfig.baudRate * 1U;
        masterConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / masterConfig.baudRate * 1U;
        masterConfig.betweenTransferDelayInNanoSec = 1000000000U / masterConfig.baudRate * 1U;

        LPSPI_MasterInit(lpc_obj[i].LPSPIx, &masterConfig, CLOCK_GetFreq(lpc_obj[i].clock_name));

        EDMA_CreateHandle(&lpc_obj[i].dma_tx_handle, lpc_obj[i].DMAx, lpc_obj[i].tx_dma_chl);
        EDMA_CreateHandle(&lpc_obj[i].dma_rx_handle, lpc_obj[i].DMAx, lpc_obj[i].rx_dma_chl);

        EDMA_SetChannelMux(lpc_obj[i].DMAx, lpc_obj[i].tx_dma_chl, lpc_obj[i].tx_dma_request);
        EDMA_SetChannelMux(lpc_obj[i].DMAx, lpc_obj[i].rx_dma_chl, lpc_obj[i].rx_dma_request);

        LPSPI_MasterTransferCreateHandleEDMA(lpc_obj[i].LPSPIx, &lpc_obj[i].spi_dma_handle, LPSPI_MasterUserCallback, &lpc_obj[i], &lpc_obj[i].dma_rx_handle, &lpc_obj[i].dma_tx_handle);

        rt_spi_bus_register(&lpc_obj[i].parent, lpc_obj[i].name, &lpc_spi_ops);
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_spi_init);
