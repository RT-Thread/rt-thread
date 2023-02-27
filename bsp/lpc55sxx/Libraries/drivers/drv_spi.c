/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-15     Magicoe      The first version for LPC55S6x
 */
#include "rtdevice.h"

#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_spi.h"
#include "fsl_spi_dma.h"


enum
{
#ifdef BSP_USING_SPI3
    SPI3_INDEX,
#endif
#ifdef BSP_USING_SPI8
    SPI8_INDEX,
#endif
};


struct lpc_spi
{
    struct rt_spi_bus           parent;
    SPI_Type                    *SPIx;
    clock_attach_id_t           clock_attach_id;
    clock_ip_name_t             clock_name;

    DMA_Type                    *DMAx;
    uint8_t                     tx_dma_chl;
    uint8_t                     rx_dma_chl;
    dma_handle_t                dma_tx_handle;
    dma_handle_t                dma_rx_handle;
    spi_dma_handle_t            spi_dma_handle;

    rt_sem_t                    sem;
    char                        *device_name;
};


static struct lpc_spi lpc_obj[] =
{
#ifdef BSP_USING_SPI3
        {
            .SPIx = SPI3,
            .clock_attach_id = kMAIN_CLK_to_FLEXCOMM3,
            .clock_name = kCLOCK_FlexComm3,
            .device_name = "spi3",

            .DMAx = DMA0,
            .tx_dma_chl = 9,
            .rx_dma_chl = 8,

        },
#endif
       #ifdef BSP_USING_SPI8
        {
            .SPIx = SPI8,
            .clock_attach_id = kMAIN_CLK_to_HSLSPI,
            .clock_name = kCLOCK_Hs_Lspi,
            .device_name = "spi8",

            .DMAx = DMA0,
            .tx_dma_chl = 3,
            .rx_dma_chl = 2,

        },
#endif
};


struct lpc_sw_spi_cs
{
    rt_uint32_t pin;
};


static uint32_t lpc_get_spi_freq(SPI_Type *base)
{
    uint32_t freq = 0;


    if(base == SPI3)
    {
        freq = CLOCK_GetFlexCommClkFreq(kCLOCK_FlexComm3);
    }

    if(base == SPI8)
    {
        freq = CLOCK_GetFlexCommClkFreq(kCLOCK_Hs_Lspi);
    }
    return freq;
}

static rt_err_t lpc_spi_init(SPI_Type *base, struct rt_spi_configuration *cfg)
{
    spi_master_config_t masterConfig = {0};

    SPI_MasterGetDefaultConfig(&masterConfig);

    if(cfg->data_width != 8 && cfg->data_width != 16)
    {
        cfg->data_width = 8;
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

    SPI_MasterInit(base, &masterConfig, lpc_get_spi_freq(base));

    return RT_EOK;
}

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t pin)
{
    rt_err_t ret = RT_EOK;

    struct rt_spi_device *spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    struct lpc_sw_spi_cs *cs_pin = (struct lpc_sw_spi_cs *)rt_malloc(sizeof(struct lpc_sw_spi_cs));

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
    spi = (struct lpc_spi *)(device->bus->parent.user_data);
    ret = lpc_spi_init(spi->SPIx, cfg);

    return ret;
}


static void SPI_MasterUserCallback(SPI_Type *base, spi_dma_handle_t *handle, status_t status, void *userData)
{
    struct lpc_spi *spi = (struct lpc_spi*)userData;
    rt_sem_release(spi->sem);
}

static rt_ssize_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    int i;
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
    transfer.configFlags = kSPI_FrameAssert;

  //  if(message->length < MAX_DMA_TRANSFER_SIZE)
    if(0)
    {
        SPI_MasterTransferBlocking(spi->SPIx, &transfer);
    }
    else
    {
        uint32_t block, remain;
        block = message->length / DMA_MAX_TRANSFER_COUNT;
        remain = message->length % DMA_MAX_TRANSFER_COUNT;

        for(i=0; i<block; i++)
        {
            transfer.dataSize = DMA_MAX_TRANSFER_COUNT;
            if(message->recv_buf) transfer.rxData   = (uint8_t *)(message->recv_buf + i*DMA_MAX_TRANSFER_COUNT);
            if(message->send_buf) transfer.txData   = (uint8_t *)(message->send_buf + i*DMA_MAX_TRANSFER_COUNT);

            SPI_MasterTransferDMA(spi->SPIx, &spi->spi_dma_handle, &transfer);
            rt_sem_take(spi->sem, RT_WAITING_FOREVER);
        }

        if(remain)
        {
            transfer.dataSize = remain;
            if(message->recv_buf) transfer.rxData   = (uint8_t *)(message->recv_buf + i*DMA_MAX_TRANSFER_COUNT);
            if(message->send_buf) transfer.txData   = (uint8_t *)(message->send_buf + i*DMA_MAX_TRANSFER_COUNT);

            SPI_MasterTransferDMA(spi->SPIx, &spi->spi_dma_handle, &transfer);
            rt_sem_take(spi->sem, RT_WAITING_FOREVER);
        }
    }



    if(message->cs_release)
    {
        rt_pin_write(cs->pin, PIN_HIGH);
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

    for(i=0; i<ARRAY_SIZE(lpc_obj); i++)
    {
        CLOCK_AttachClk(lpc_obj[i].clock_attach_id);
        lpc_obj[i].parent.parent.user_data = &lpc_obj[i];
        lpc_obj[i].sem = rt_sem_create("sem_spi", 0, RT_IPC_FLAG_FIFO);

        DMA_EnableChannel(lpc_obj[i].DMAx, lpc_obj[i].tx_dma_chl);
        DMA_EnableChannel(lpc_obj[i].DMAx, lpc_obj[i].rx_dma_chl);
        DMA_SetChannelPriority(lpc_obj[i].DMAx, lpc_obj[i].tx_dma_chl, kDMA_ChannelPriority3);
        DMA_SetChannelPriority(lpc_obj[i].DMAx, lpc_obj[i].rx_dma_chl, kDMA_ChannelPriority2);
        DMA_CreateHandle(&lpc_obj[i].dma_tx_handle, lpc_obj[i].DMAx, lpc_obj[i].tx_dma_chl);
        DMA_CreateHandle(&lpc_obj[i].dma_rx_handle, lpc_obj[i].DMAx, lpc_obj[i].rx_dma_chl);
        SPI_MasterTransferCreateHandleDMA(lpc_obj[i].SPIx, &lpc_obj[i].spi_dma_handle, SPI_MasterUserCallback, &lpc_obj[i], &lpc_obj[i].dma_tx_handle, &lpc_obj[i].dma_rx_handle);
        rt_spi_bus_register(&lpc_obj[i].parent, lpc_obj[i].device_name, &lpc_spi_ops);
    }
    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_spi_init);

