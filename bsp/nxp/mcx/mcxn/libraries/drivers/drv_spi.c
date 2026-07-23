/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-15     yandld      The first version for MCXN
 */
#include "rtdevice.h"

#include "fsl_common.h"
#include "fsl_lpspi.h"
#include "fsl_lpspi_edma.h"

#define DMA_MAX_TRANSFER_COUNT (32767)

enum
{
#ifdef BSP_USING_SPI1
    SPI1_INDEX,
#endif
#ifdef BSP_USING_SPI3
    SPI3_INDEX,
#endif

#ifdef BSP_USING_SPI6
    SPI6_INDEX,
#endif

#ifdef BSP_USING_SPI7
    SPI7_INDEX,
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
#ifdef BSP_USING_SPI1
    {
        .LPSPIx = LPSPI1,
        .clock_attach_id = kFRO_HF_DIV_to_FLEXCOMM1,
        .clock_div_name = kCLOCK_DivFlexcom1Clk,
        .clock_name = kCLOCK_FroHf,
        .tx_dma_request = kDma0RequestMuxLpFlexcomm1Tx,
        .rx_dma_request = kDma0RequestMuxLpFlexcomm1Rx,
        .DMAx = DMA0,
        .tx_dma_chl = 0,
        .rx_dma_chl = 1,
        .name = "spi1",
    },
#endif
#ifdef BSP_USING_SPI3
    {
        .LPSPIx = LPSPI3,
        .clock_attach_id = kFRO_HF_DIV_to_FLEXCOMM3,
        .clock_div_name = kCLOCK_DivFlexcom3Clk,
        .clock_name = kCLOCK_FroHf,
        .tx_dma_request = kDma0RequestMuxLpFlexcomm3Tx,
        .rx_dma_request = kDma0RequestMuxLpFlexcomm3Rx,
        .DMAx = DMA0,
        .tx_dma_chl = 2,
        .rx_dma_chl = 3,
        .name = "spi3",
    },
#endif /* BSP_USING_SPI3 */
#ifdef BSP_USING_SPI6
    {
        .LPSPIx = LPSPI6,
        .clock_attach_id = kFRO_HF_DIV_to_FLEXCOMM6,
        .clock_div_name = kCLOCK_DivFlexcom6Clk,
        .clock_name = kCLOCK_FroHf,
        .tx_dma_request = kDma0RequestMuxLpFlexcomm6Tx,
        .rx_dma_request = kDma0RequestMuxLpFlexcomm6Rx,
        .DMAx = DMA0,
        .tx_dma_chl = 4,
        .rx_dma_chl = 5,
        .name = "spi6",
    },
#endif /* BSP_USING_SPI6 */
#ifdef BSP_USING_SPI7
    {
        .LPSPIx = LPSPI7,
        .clock_attach_id = kFRO_HF_DIV_to_FLEXCOMM7,
        .clock_div_name = kCLOCK_DivFlexcom7Clk,
        .clock_name = kCLOCK_FroHf,
        .tx_dma_request = kDma0RequestMuxLpFlexcomm7Tx,
        .rx_dma_request = kDma0RequestMuxLpFlexcomm7Rx,
        .DMAx = DMA0,
        .tx_dma_chl = 2,
        .rx_dma_chl = 3,
        .name = "spi7",
    },
#endif /* BSP_USING_SPI7 */
};

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t pin)
{
    struct rt_spi_device *spi_device = rt_malloc(sizeof(struct rt_spi_device));
    if (!spi_device)
    {
        return -RT_ENOMEM;
    }

    return rt_spi_bus_attach_device_cspin(spi_device, device_name, bus_name, pin, RT_NULL);
}

static rt_err_t spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    rt_err_t ret = RT_EOK;
//    struct lpc_spi *spi = RT_NULL;
//    spi = (struct lpc_spi *)(device->bus->parent.user_data);
//    ret = lpc_spi_init(spi->SPIx, cfg);
    return ret;
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

    //  if(message->length < MAX_DMA_TRANSFER_SIZE)
    if (0)
    {
        LPSPI_MasterTransferBlocking(spi->LPSPIx, &transfer);
    }
    else
    {
        uint32_t block, remain;
        block = message->length / DMA_MAX_TRANSFER_COUNT;
        remain = message->length % DMA_MAX_TRANSFER_COUNT;

        for (i = 0; i < block; i++)
        {
            transfer.dataSize = DMA_MAX_TRANSFER_COUNT;
            if (message->recv_buf) transfer.rxData   = (uint8_t *)(message->recv_buf + i *DMA_MAX_TRANSFER_COUNT);
            if (message->send_buf) transfer.txData   = (uint8_t *)(message->send_buf + i *DMA_MAX_TRANSFER_COUNT);

            LPSPI_MasterTransferEDMA(spi->LPSPIx, &spi->spi_dma_handle, &transfer);
            rt_sem_take(spi->sem, RT_WAITING_FOREVER);
        }

        if (remain)
        {
            transfer.dataSize = remain;
            if (message->recv_buf) transfer.rxData   = (uint8_t *)(message->recv_buf + i *DMA_MAX_TRANSFER_COUNT);
            if (message->send_buf) transfer.txData   = (uint8_t *)(message->send_buf + i *DMA_MAX_TRANSFER_COUNT);

            LPSPI_MasterTransferEDMA(spi->LPSPIx, &spi->spi_dma_handle, &transfer);
            rt_sem_take(spi->sem, RT_WAITING_FOREVER);
        }
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
        CLOCK_SetClkDiv(lpc_obj[i].clock_div_name, 1u);
        CLOCK_AttachClk(lpc_obj[i].clock_attach_id);

        lpc_obj[i].parent.parent.user_data = &lpc_obj[i];
        lpc_obj[i].sem = rt_sem_create("sem_spi", 0, RT_IPC_FLAG_FIFO);

        lpspi_master_config_t masterConfig;
        LPSPI_MasterGetDefaultConfig(&masterConfig);
        masterConfig.baudRate = 24 * 1000 * 1000;
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

