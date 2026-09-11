/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include "drv_dma.h"
#include <ipc/completion.h>
#include "drv_config.h"

#ifdef __cplusplus
extern "C" {
#endif

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin);

#ifdef __cplusplus
}
#endif

struct n32_spi_config
{
    SPI_Module *SPIx;
    char *bus_name;
    IRQn_Type irq_type;
    struct dma_config *dma_rx, *dma_tx;
};

struct n32_spi_device
{
    rt_uint32_t pin;
    char *bus_name;
    char *device_name;
};


#define SPI_USING_RX_DMA_FLAG (1 << 0)
#define SPI_USING_TX_DMA_FLAG (1 << 1)

/* Max bytes of a single DMA block (12-bit BlkTfrSize) */
#define SPI_DMA_BLOCK_MAX (4095U)
/* Number of LLI chain nodes per DMA leg (sizes lli_tx/lli_rx) */
#define SPI_DMA_CHAIN_NODES (16U)
#define SPI_DMA_CHAIN_MAX   (SPI_DMA_BLOCK_MAX * SPI_DMA_CHAIN_NODES)
/* Max elements of a single DMA arm: spixfer chunks every message at this
 * size. A N32H7xx DMA arm stalls past ~4128 items at the 20MHz top rate
 * (silicon-level: the LLI chain is verified intact and frozen mid-node;
 * sharp 4128 PASS / 4136 FAIL boundary, and the ceiling scales with the
 * bit clock so a 4096-item arm passes at every rate). 4096 items = 2 LLI
 * nodes (4095+1) -- the same per-arm shape as a standalone 4096-element
 * message. */
#define SPI_DMA_ARM_MAX (4096U)

typedef enum
{
    SPI_Tx_Rx = 0U,
    SPI_Tx,
    SPI_Rx,
    SPI_Idle,
} SPI_Work_Direct_t;

/* n32 spi dirver class */
struct n32_spi
{
    struct n32_spi_config *config;
    struct rt_spi_configuration *cfg;

    SPI_InitType SPI_InitStructure;
    SPI_Work_Direct_t Direct;

#if defined(SOC_SERIES_N32H7xx)
    struct
    {
        rt_bool_t DMA_Tx_Init;
        DMA_ChInitType TX_DMA_ChInitStr;

        rt_bool_t DMA_Rx_Init;
        DMA_ChInitType RX_DMA_ChInitStr;

        /* LLI node arrays: seamless single-task DMA for > SPI_DMA_BLOCK_MAX */
        DMA_LinkListItemType lli_rx[SPI_DMA_CHAIN_NODES];
        DMA_LinkListItemType lli_tx[SPI_DMA_CHAIN_NODES];
    } dma;
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
    struct
    {
        rt_bool_t DMA_Tx_Init;
        DMA_InitType TX_DMA_ChInitStr;

        rt_bool_t DMA_Rx_Init;
        DMA_InitType RX_DMA_ChInitStr;
    } dma;
#endif

    rt_uint8_t spi_dma_flag;
    /* TRUE while a 4-wire full-duplex MASTER receive-only message is being
     * armed: the TX DMA source is then the static 0xFF fill buffer, and
     * n32_spi_dma_arm re-points every LLI TX node at its base. Read only
     * inside n32_spi_dma_arm; set/cleared around the SPI_DMA_TransmitReceive
     * call in SPI_DMA_Receive. Per-bus messages are serialized by the
     * RT-Thread bus lock and no ISR reads the flag, so a plain rt_bool_t is
     * race-free. Unused on non-H7 series. */
    rt_bool_t fd_rxonly_dummy_tx;
    /* TRUE while a non-first chunk of a 4-wire full-duplex message is being
     * armed: spixfer keeps the SPI engine on across chunk boundaries (only
     * the message tail disables), so SPI_DMA_TransmitReceive re-arms the
     * live engine warm (no SPIEN drop/re-enable) instead of cold-starting
     * it. Read only inside SPI_DMA_TransmitReceive; set at the top of every
     * chunk in spixfer. Per-bus messages are serialized by the RT-Thread
     * bus lock and no ISR reads the flag, so a plain rt_bool_t is
     * race-free. Unused on non-H7 series. */
    rt_bool_t fd_chunk_cont;
    struct rt_spi_bus spi_bus;

    struct rt_completion cpt;
};

#endif /*__DRV_SPI_H__ */
