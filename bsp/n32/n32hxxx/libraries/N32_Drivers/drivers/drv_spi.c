/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#ifdef BSP_USING_SPI

#if defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3) || defined(BSP_USING_SPI4) || defined(BSP_USING_SPI5) || defined(BSP_USING_SPI6) || defined(BSP_USING_SPI7)


#include "drv_spi.h"
#include "drv_config.h"
#include <string.h>

//#define DRV_DEBUG
#define LOG_TAG "drv.spi"
#include <drv_log.h>

enum
{
#ifdef BSP_USING_SPI1
    SPI1_INDEX,
#endif
#ifdef BSP_USING_SPI2
    SPI2_INDEX,
#endif
#ifdef BSP_USING_SPI3
    SPI3_INDEX,
#endif
#ifdef BSP_USING_SPI4
    SPI4_INDEX,
#endif
#ifdef BSP_USING_SPI5
    SPI5_INDEX,
#endif
#ifdef BSP_USING_SPI6
    SPI6_INDEX,
#endif
#ifdef BSP_USING_SPI7
    SPI7_INDEX,
#endif
};


static struct n32_spi_config spi_config[] = {
#ifdef BSP_USING_SPI1
    SPI1_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI2
    SPI2_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI3
    SPI3_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI4
    SPI4_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI5
    SPI5_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI6
    SPI6_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI7
    SPI7_BUS_CONFIG,
#endif
};

static struct n32_spi spi_bus_obj[sizeof(spi_config) / sizeof(spi_config[0])] = { 0 };


#if defined(SOC_SERIES_N32H7xx)
/* Static 0xFF fill source for 4-wire full-duplex MASTER receive-only DMA.
 * A recv-only master still has to clock the bus, so the TX DMA pushes this
 * fill pattern onto MOSI while the RX DMA captures into the caller's buffer.
 * Sized for the widest single read of the buffer: one DMA block holds at
 * most 4095 items, and at 16-bit width that is 4095 * 2 = 8190B (8-bit:
 * 4095B). LLI nodes never read further because n32_spi_dma_arm re-points
 * every node's SrcAddr at the base, so each node re-reads at most one block
 * from the start. Filled once in rt_hw_spi_bus_init and read-only afterwards
 * -> one shared instance for every SPI bus is safe. */
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6010050)
#define N32_SPI_DUMMY_ALIGN32 __align(32)
#else
#define N32_SPI_DUMMY_ALIGN32 __attribute__((aligned(32)))
#endif
N32_SPI_DUMMY_ALIGN32 static rt_uint8_t spi_fd_rxonly_dummy[8192];
#endif /* SOC_SERIES_N32H7xx */


#if defined(SOC_SERIES_N32H7xx)
/* Build an LLI chain for a 'size'-byte transfer: the memory side advances
 * 4095B per node while the peripheral (DAT) address stays fixed. Only the
 * last node has IntEn=1, so the whole chain raises a single TC interrupt. */
static rt_uint16_t n32_spi_lli_build(DMA_LinkListItemType *lli, const DMA_ChInitType *ch,
                                     rt_uint32_t periph_addr, rt_uint32_t mem_addr,
                                     rt_bool_t mem_is_src, rt_uint16_t size)
{
    rt_uint16_t n = (rt_uint16_t)((size + SPI_DMA_BLOCK_MAX - 1U) / SPI_DMA_BLOCK_MAX);
    rt_uint16_t i;
    rt_uint16_t rest = size;

    for (i = 0; i < n; i++)
    {
        DMA_LinkListItemType *node = &lli[i];
        rt_uint16_t blk = (rest > SPI_DMA_BLOCK_MAX) ? SPI_DMA_BLOCK_MAX : rest;
        rt_bool_t has_next = (i + 1U < n) ? RT_TRUE : RT_FALSE;

        node->SrcAddr = mem_is_src ? (mem_addr + (rt_uint32_t)i * SPI_DMA_BLOCK_MAX) : periph_addr;
        node->DstAddr = mem_is_src ? periph_addr : (mem_addr + (rt_uint32_t)i * SPI_DMA_BLOCK_MAX);
        node->pNext = has_next ? &lli[i + 1U] : RT_NULL;
        node->IntEn = has_next ? 0U : 1U;
        node->DstTfrWidth = ch->DstTfrWidth;
        node->SrcTfrWidth = ch->SrcTfrWidth;
        node->DstAddrCountMode = ch->DstAddrCountMode;
        node->SrcAddrCountMode = ch->SrcAddrCountMode;
        node->DstBurstLen = ch->DstBurstLen;
        node->SrcBurstLen = ch->SrcBurstLen;
        node->SrcGatherEn = ch->SrcGatherEn;
        node->DstScatterEn = ch->DstScatterEn;
        node->TfrTypeFlowCtrl = ch->TfrTypeFlowCtrl;
        node->DstLinkedListEn = has_next ? 1U : 0U;
        node->SrcLinkedListEn = has_next ? 1U : 0U;
        node->BlkTfrSize = blk;
        rest -= blk;
    }
    return n;
}

/* Arm one RX/TX DMA channel:
 *  - size <= 4095       : single-block transfer (original behaviour)
 *  - size > 4095        : seamless LLI-chain transfer (no software gap
 *                         between blocks, so a clock-driven slave never
 *                         drops bytes)
 *  - active == RT_FALSE : arm the channel as an empty block (this direction
 *                         does not take part in this transfer) */
static rt_err_t n32_spi_dma_arm(struct n32_spi *spi_drv, rt_bool_t is_rx,
                                rt_bool_t active, uint8_t *buf, rt_uint16_t size)
{
    struct dma_config *cfg = is_rx ? spi_drv->config->dma_rx : spi_drv->config->dma_tx;
    DMA_ChInitType *ch = is_rx ? &spi_drv->dma.RX_DMA_ChInitStr : &spi_drv->dma.TX_DMA_ChInitStr;
    DMA_LinkListItemType *lli = is_rx ? spi_drv->dma.lli_rx : spi_drv->dma.lli_tx;

    DMA_ChannelCmd(cfg->Instance, cfg->dma_channel, DISABLE);

    if (!DMA_ControllerIsEnabled(cfg->Instance))
    {
        DMA_ControllerCmd(cfg->Instance, ENABLE);
    }
    DMA_ControllerCmd(cfg->Instance, ENABLE);

    if (!active)
    {
        /* Empty arm: this direction does not take part in this transfer */
        ch->IntEn = 0U;
        if (is_rx)
        {
            ch->DstAddr = (uint32_t)RT_NULL;
        }
        else
        {
            ch->SrcAddr = (uint32_t)RT_NULL;
        }
        ch->BlkTfrSize = 0U;
        ch->pLinkListItem = RT_NULL;
        ch->TfrType = DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK;
        if (DMA_ChannelInit(cfg->Instance, ch, cfg->dma_channel) != 0U)
        {
            LOG_E(is_rx ? "Master DMA Rx channel initialization failed."
                        : "Master DMA Tx channel initialization failed.");
            return -RT_ERROR;
        }
        return RT_EOK;
    }

    /* Active direction: load the buffer address and block size */
    if (is_rx)
    {
        /* Unconditionally drain any stale DAT/RNE byte before arming: once
         * RDMAEN is set, the first DMA transfer would swallow a leftover byte
         * as rx[0] (slave first-byte right-shift plus trailing RNE=1).
         * Cross-case residue is exactly this source. */
        SPI_I2S_ReceiveData(spi_drv->config->SPIx);
        SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);

        ch->DstAddr = (uint32_t)buf;
    }
    else
    {
        ch->SrcAddr = (uint32_t)buf;
    }

    if (size > SPI_DMA_BLOCK_MAX)
    {
        /* Seamless chain transfer: the whole message is one DMA task, so
         * there is no reload gap between blocks */
        rt_uint16_t nodes;

        nodes = n32_spi_lli_build(lli, ch, (uint32_t)&spi_drv->config->SPIx->DAT,
                                  (uint32_t)buf, !is_rx, size);
        if ((!is_rx) && spi_drv->fd_rxonly_dummy_tx)
        {
            /* FD master recv-only: the TX source is the 0xFF fill buffer.
             * Re-point every LLI node at its base - without this the chain
             * steps 4095B per node and would walk past the fill buffer.
             * Each node then re-reads its own block (<= 4095 items, <= the
             * 8192B fill) from the base, which is exactly the constant 0xFF
             * stream this path must clock. */
            rt_uint16_t k;

            for (k = 0U; k < nodes; k++)
            {
                lli[k].SrcAddr = (uint32_t)buf;
            }
        }
        ch->pLinkListItem = &lli[0];
        ch->TfrType = DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_LINKED_DSTADR_LINKED;
        ch->BlkTfrSize = SPI_DMA_BLOCK_MAX; /* channel's first block matches lli[0] */
    }
    else
    {
        ch->pLinkListItem = RT_NULL;
        ch->TfrType = DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK;
        ch->BlkTfrSize = size;
    }
    ch->IntEn = 1U;

    if (DMA_ChannelInit(cfg->Instance, ch, cfg->dma_channel) == 0U)
    {
        /* Clear stale TC/error events first: a TC flag left by the previous
         * case would fire a bogus completion interrupt as soon as the channel
         * is enabled, completing the slave DMA before the real data has
         * arrived (BUSY stuck; mode2 symptom). */
        DMA_ClearChannelEventStatus(cfg->Instance, cfg->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE);
        DMA_ClearChannelEventStatus(cfg->Instance, cfg->dma_channel, DMA_CH_EVENT_ERROR);

        /* Enable transaction complete interrupt event */
        DMA_ChannelEventCmd(cfg->Instance, cfg->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, ENABLE);

        /* Order matters: set the SPI-side RDMAEN/TDMAEN first, then enable the
         * DMA channel. The reverse order leaves a window in which a first byte
         * received by a clock-driven slave is not moved out by any DMA request
         * and stays in DAT, shifting all following real data (slave rx
         * right-shift, first byte lost). A slave is armed before the master
         * clock starts, so this order is safe. */
        SPI_I2S_EnableDma(spi_drv->config->SPIx,
                          is_rx ? SPI_I2S_DMA_RX : SPI_I2S_DMA_TX, ENABLE);

        /* Enable the specified DMA channel */
        DMA_ChannelCmd(cfg->Instance, cfg->dma_channel, ENABLE);
    }
    else
    {
        LOG_E("DMA channel init fail: %s ch%u size=%u (leaving RDMAEN off)",
              is_rx ? "RX" : "TX", cfg->dma_channel, size);
        return -RT_ERROR;
    }
    return RT_EOK;
}
#endif /* SOC_SERIES_N32H7xx */

/* True when this device is a mode2 (CPOL=1/CPHA=0) full-duplex master. Such
 * transfers use the "engine always-on + warm-engine level-triggered DMA"
 * scheme (see the SPI_DMA_TransmitReceive notes, the spixfer message tail and
 * the n32_spi_init configure pre-enable). On the always-selected 4-wire
 * cross-wiring used by the test board (SPI1 master <-> SPI2 slave), a mode2
 * slave counts the SCK LOW->HIGH edge of the master SPIEN 0->1 into its bit
 * phase and the whole frame grid shifts (the slave SPIEN 0->1 by itself also
 * pulls SCK low; no GPIO pull can fight an ms-scale gap - the vendor demo
 * only passes because its two enables are ns apart, a timing coincidence
 * disproved by a log-delay experiment). Keeping the master engine on makes
 * the slave arm against an SCK line already clamped idle-high by the master's
 * push-pull driver, and message start no longer creates a 0->1 edge. */
static rt_bool_t n32_spi_mode2_fd_master(struct n32_spi *spi_drv)
{
    return (spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_MASTER) &&
           (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_DOUBLELINE_FULLDUPLEX) &&
           (spi_drv->SPI_InitStructure.CLKPOL == SPI_CLKPOL_HIGH) &&
           (spi_drv->SPI_InitStructure.CLKPHA == SPI_CLKPHA_FIRST_EDGE);
}

/* Same always-on treatment for a 3-wire (single-line) mode2 master. Its
 * per-message cold start (SPIEN 0->1) drops the SCK pad low first and then
 * rises into the already-enabled mode2 slave, so the slave bit counter
 * gains one spurious edge and the whole frame grid shifts by one bit
 * (rx[j] = (b[j-1] & 1) << 7 | b[j] >> 1; modes 0/1/3 sample after the
 * data lands and are immune). Keeping this engine on clamps SCK idle-high
 * exactly like the FD variant. Mutually exclusive with it: FD requires
 * DOUBLELINE_FULLDUPLEX, this requires SINGLELINE, so a bus never matches
 * both. */
static rt_bool_t n32_spi_mode2_3w_master(struct n32_spi *spi_drv)
{
    return (spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_MASTER) &&
           (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_TX ||
            spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_RX) &&
           (spi_drv->SPI_InitStructure.CLKPOL == SPI_CLKPOL_HIGH) &&
           (spi_drv->SPI_InitStructure.CLKPHA == SPI_CLKPHA_FIRST_EDGE);
}

/* Warm (SPIEN=1) BIDI direction flip for the always-on mode2 3-wire master.
 * SPI_Init cannot do a TX->RX flip on a live engine: the vendor CLR_MASK
 * (0xF9F7, n32h7xx_spi.c) preserves bit14 (BIDIOE) under its &=, so Init
 * with SINGLELINE_RX silently leaves the engine in TX and a BA leg then
 * waits for an RX-DMA interrupt that can never fire. Toggle only the
 * BIDI output-enable bit instead, keeping SPIEN=1 so SCK never drops:
 * bit14 set = TX (master drives, line clamped idle-high, nothing clocks
 * until DAT is written); bit14 clear = RX (the mode2 receiver free-runs
 * from that moment until the direction leaves RX, so the RX DMA must be
 * armed before the clear). */
static void n32_spi_mode2_3w_set_dir(struct n32_spi *spi_drv, uint16_t dir)
{
    if (dir == SPI_DIR_SINGLELINE_TX)
    {
        spi_drv->config->SPIx->CTRL1 |= SPI_BIDIRECTION_TX;
    }
    else
    {
        spi_drv->config->SPIx->CTRL1 &= SPI_BIDIRECTION_RX;
    }
    spi_drv->SPI_InitStructure.DataDirection = dir;
}

/* Error/abort path for the always-on mode2 3-wire master: a failed or
 * aborted receive must not leave the RX engine free-running (it clocks
 * SCK continuously until the direction leaves RX), so flip back to the
 * TX-idle rest posture and clear the stale byte. No-op for every other
 * role/direction. */
static void n32_spi_mode2_3w_rx_abort(struct n32_spi *spi_drv)
{
    if (n32_spi_mode2_3w_master(spi_drv))
    {
        n32_spi_mode2_3w_set_dir(spi_drv, SPI_DIR_SINGLELINE_TX);
        SPI_I2S_ReceiveData(spi_drv->config->SPIx);
        SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);
    }
}

/* Switch the 3-wire single-line data direction. A mode2 3-wire master keeps
 * its engine on, so its flip must not drop SPIEN (that would pull SCK low
 * and re-introduce the spurious-edge shift on the enabled slave): its warm
 * flip is a direct BIDIOE toggle (n32_spi_mode2_3w_set_dir - SPI_Init
 * cannot clear BIDIOE warm, see above). Everyone else keeps the legacy cold
 * cycle (disable + peripheral DeInit + Init), whose reset also re-zeros the
 * slave bit counter. */
static void n32_spi_singleline_dir(struct n32_spi *spi_drv, uint16_t dir)
{
    if (n32_spi_mode2_3w_master(spi_drv))
    {
        n32_spi_mode2_3w_set_dir(spi_drv, dir);
    }
    else
    {
        /* Disable the sFLASH_SPI */
        SPI_Enable(spi_drv->config->SPIx, DISABLE);
        /* DeInitializes the sFLASH_SPI */
        SPI_I2S_DeInit(spi_drv->config->SPIx);
        spi_drv->SPI_InitStructure.DataDirection = dir;
        SPI_Init(spi_drv->config->SPIx, &spi_drv->SPI_InitStructure);
    }
}

static rt_err_t SPI_DMA_TransmitReceive(struct n32_spi *spi_drv, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
    RT_ASSERT(spi_drv != RT_NULL);
    RT_ASSERT((spi_drv->cfg->mode & RT_SPI_3WIRE) != RT_SPI_3WIRE);

    if (spi_drv->dma.DMA_Rx_Init != RT_TRUE || spi_drv->dma.DMA_Tx_Init != RT_TRUE)
    {
        LOG_E("In full-duplex mode, both TX DMA and RX DMA did not complete initialization.");
        return -RT_ERROR;
    }

    /* Clear any stale RX residue BEFORE arming RX/TX DMA: once RDMAEN is set
     * the first DMA transfer would swallow a leftover byte in DAT as rx[0]
     * (slave-side 1-byte right-shift + trailing RNE=1 symptom). For a slave
     * the master has not started clocking yet, so no real first byte can be
     * lost here. */
    SPI_I2S_ReceiveData(spi_drv->config->SPIx);
    SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);

    /* FD engine cold-start scheme (non-mode2 path): each transfer disables
     * first, then arms, and enables at the end. While SPIEN=0 the TE=0 keeps
     * the TX DMA request away; TE becomes 1 only after the SPIEN 0->1, so the
     * request looks like a "TE 0->1 edge trigger" (warm-engine probes proved
     * the request is actually level-triggered; see the mode2 notes below).
     * The 3-wire path uses the same scheme in SPI_DMA_Transmit (verified).
     *
     * But SPIEN 1->0 pulls the SCK pad low on CPOL=1 (idle-high) configs: the
     * slave bit counter counts falling edges, so a stray edge shifts the
     * whole round's frame grid by k bits; and SPIEN 0->1 does not clear the
     * slave bit counter (measured: mode3 rounds>=1 shift the whole frame by k
     * bits - slave receives (prev.byte bit0<<7)|(this.byte>>1), master
     * receives (this.byte<<1)|(next.byte>>7); byte-level deterministic.
     * Modes 0/1 with CPOL=0 idle-low have no transition and are immune).
     * Mitigation (see the marked places below):
     *  a) Slave: run a peripheral DeInit+Init here (the same one configure
     *     uses) - only a peripheral reset clears the bit counter, so the
     *     slave phase is zeroed before frame 0 of every round;
     *  b) Master: never drop the line at the top of an arm - the disable
     *     always happens at the message tail (the spixfer bus-release point),
     *     making the disable here a no-op for master and slave; the tail drop
     *     falls into the slave's own finish period of this round and is
     *     cleared by the slave's next arm reset.
     *
     * mode2 (CPOL=1, CPHA=0) extra problem: the scheme above cold-starts the
     * master SPIEN 0->1 after the slave is enabled, and that 0->1 SCK
     * LOW->HIGH rising edge is counted by a mode2 slave -> whole-frame k-bit
     * offset from the first frame (pad-bit fingerprints b2 67 9d 52...,
     * matched byte-for-byte on a full 4096B frame). A mode2 FD master
     * therefore never cold-starts: the engine is pre-enabled at configure and
     * kept across messages (not disabled at the spixfer message tail), and no
     * disable/enable cycle happens here. On a warm engine the TX DMA request
     * is level-triggered: with TE=1 the channel enable alone fires it (after
     * RX/TX arm with no CPU write at all, TE goes 1->0, data flows by itself
     * and the ISR completes normally; during a cold start SPIEN=0 keeps TE=0,
     * so the request only appears after SPIEN 0->1 and looks edge-triggered).
     * The original CPU-seed write raced the DMA self-start (the seed written
     * into a full DAT was swallowed and the first byte shifted) and has been
     * removed. When the engine is (unexpectedly) off, fall back to the
     * traditional cold-start cycle as before. */
    /* Warm re-arm: arming a MASTER whose SPIEN is still set is legitimate
     * only for (a) the always-on mode2 FD master (see the notes above) and
     * (b) a non-first chunk of a 4-wire full-duplex message -- spixfer marks
     * (b) with fd_chunk_cont because it keeps the engine on across chunk
     * boundaries (only the message tail disables). In both cases SPIEN must
     * NOT be dropped here: the 1->0 pulls the SCK pad low on CPOL=1
     * (idle-high) and the 0->1 re-enable raises it again -- both edges land
     * on the enabled mid-arm slave, whose bit counter counts them and shifts
     * its TX reply (a chunked 8192-element mode3 message corrupts from byte
     * 4096 onward). On the warm engine the TX
     * DMA request is level-triggered (note above): the channel enable alone
     * fires it, so no SPI enable is needed either. Every other arm -- slave
     * (phase reset below) or a master whose engine is off -- keeps the
     * traditional cold-start cycle. */
    rt_bool_t engine_warm = RT_FALSE;
    if (spi_drv->fd_chunk_cont &&
        (spi_drv->SPI_InitStructure.SpiMode != SPI_MODE_SLAVE) &&
        ((spi_drv->config->SPIx->CTRL2 & SPI_CTRL2_SPIEN) != 0U))
    {
        engine_warm = RT_TRUE;
    }
    else if (n32_spi_mode2_fd_master(spi_drv) &&
             (Size > 1U) &&
             ((spi_drv->config->SPIx->CTRL2 & SPI_CTRL2_SPIEN) != 0U))
    {
        engine_warm = RT_TRUE;
    }
    else
    {
        SPI_Enable(spi_drv->config->SPIx, DISABLE);
    }
    if (spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE)
    {
        SPI_I2S_DeInit(spi_drv->config->SPIx);
        SPI_Init(spi_drv->config->SPIx, &spi_drv->SPI_InitStructure);
    }

    if (spi_drv->dma.DMA_Rx_Init == RT_TRUE)
    {
#if defined(SOC_SERIES_N32H7xx)
        /* SPI RX DMA receive (single block or seamless LLI chain) */
        if (n32_spi_dma_arm(spi_drv, RT_TRUE, RT_TRUE, pRxData, Size) != RT_EOK)
        {
            SPI_Enable(spi_drv->config->SPIx, ENABLE);
            return -RT_ERROR;
        }
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
        /* SPI RX DMA Receive Data for H49X */
        DMA_EnableChannel(spi_drv->config->dma_rx->DMAChx, DISABLE);

        /* Configure DMA request remapping */
        DMA_RequestRemap(spi_drv->config->dma_rx->request, spi_drv->config->dma_rx->DMAChx, ENABLE);

        spi_drv->dma.RX_DMA_ChInitStr.MemAddr = (uint32_t)pRxData;
        spi_drv->dma.RX_DMA_ChInitStr.BufSize = Size;

        DMA_Init(spi_drv->config->dma_rx->DMAChx, &spi_drv->dma.RX_DMA_ChInitStr);

        /* Enable transfer complete interrupt */
        DMA_ConfigInt(spi_drv->config->dma_rx->DMAChx, DMA_INT_TXC, ENABLE);

        /* Enable the specified DMA channel */
        DMA_EnableChannel(spi_drv->config->dma_rx->DMAChx, ENABLE);

        SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_RX, ENABLE);
#endif
    }
    else
    {
        LOG_E("In full-duplex mode, RX DMA did not complete initialization.");
        return -RT_ERROR;
    }

    if (spi_drv->dma.DMA_Tx_Init == RT_TRUE)
    {
#if defined(SOC_SERIES_N32H7xx)
        /* SPI TX DMA send (single block or seamless LLI chain). On a warm
         * engine (engine_warm) the channel enable level-triggers the transfer
         * (see the big note above); the first byte goes out from the source
         * start address, no seed needed. */
        if (n32_spi_dma_arm(spi_drv, RT_FALSE, RT_TRUE, pTxData, Size) != RT_EOK)
        {
            SPI_Enable(spi_drv->config->SPIx, ENABLE);
            return -RT_ERROR;
        }
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
        /* SPI TX DMA Send Data for H49X */
        DMA_EnableChannel(spi_drv->config->dma_tx->DMAChx, DISABLE);

        /* Configure DMA request remapping */
        DMA_RequestRemap(spi_drv->config->dma_tx->request, spi_drv->config->dma_tx->DMAChx, ENABLE);

        spi_drv->dma.TX_DMA_ChInitStr.MemAddr = (uint32_t)pTxData;
        spi_drv->dma.TX_DMA_ChInitStr.BufSize = Size;

        DMA_Init(spi_drv->config->dma_tx->DMAChx, &spi_drv->dma.TX_DMA_ChInitStr);

        /* Enable transfer complete interrupt */
        DMA_ConfigInt(spi_drv->config->dma_tx->DMAChx, DMA_INT_TXC, ENABLE);

        /* Enable the specified DMA channel */
        DMA_EnableChannel(spi_drv->config->dma_tx->DMAChx, ENABLE);

        SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_TX, ENABLE);
#endif
    }
    else
    {
        LOG_E("In full-duplex mode, TX DMA did not complete initialization.");
        SPI_Enable(spi_drv->config->SPIx, ENABLE);
        return -RT_ERROR;
    }

    /* Enable Error Interrupt */
    SPI_I2S_EnableInt(spi_drv->config->SPIx, SPI_I2S_INT_ERR, ENABLE);

    /* Set SPI Direction */
    spi_drv->Direct = SPI_Tx_Rx;

    if (!engine_warm)
    {
        /* Enable 0->1 after arming: the TE rising edge happens only once
         * RDMAEN/TDMAEN and both DMA channels are ready, so the first-byte TX
         * request can actually go out (see the note above). */
        SPI_Enable(spi_drv->config->SPIx, ENABLE);
    }

    return RT_EOK;
}

static rt_err_t SPI_DMA_Transmit(struct n32_spi *spi_drv, uint8_t *pData, uint16_t Size)
{
    RT_ASSERT(spi_drv != RT_NULL);

    if (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_RX ||
        spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_TX)
    {
        n32_spi_singleline_dir(spi_drv, SPI_DIR_SINGLELINE_TX);
    }

    if (spi_drv->dma.DMA_Rx_Init == RT_TRUE)
    {
#if defined(SOC_SERIES_N32H7xx)
        /* Send mode: the RX channel is armed as an empty block (this direction does not take part) */
        if (n32_spi_dma_arm(spi_drv, RT_TRUE, RT_FALSE, RT_NULL, 0U) != RT_EOK)
        {
            return -RT_ERROR;
        }
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)

        DMA_EnableChannel(spi_drv->config->dma_rx->DMAChx, DISABLE);
        spi_drv->dma.RX_DMA_ChInitStr.MemAddr = 0;
        spi_drv->dma.RX_DMA_ChInitStr.BufSize = 0;

        DMA_EnableChannel(spi_drv->config->dma_rx->DMAChx, ENABLE);
        DMA_Init(spi_drv->config->dma_rx->DMAChx, &spi_drv->dma.RX_DMA_ChInitStr);
#endif
    }

    if (spi_drv->dma.DMA_Tx_Init == RT_TRUE)
    {
#if defined(SOC_SERIES_N32H7xx)
        /* SPI TX DMA send (single block or seamless LLI chain) */
        n32_spi_dma_arm(spi_drv, RT_FALSE, RT_TRUE, pData, Size);
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
        /* SPI TX DMA Send Data for H49X */
        DMA_EnableChannel(spi_drv->config->dma_tx->DMAChx, DISABLE);

        /* Configure DMA request remapping */
        DMA_RequestRemap(spi_drv->config->dma_tx->request, spi_drv->config->dma_tx->DMAChx, ENABLE);

        spi_drv->dma.TX_DMA_ChInitStr.MemAddr = (uint32_t)pData;
        spi_drv->dma.TX_DMA_ChInitStr.BufSize = Size;

        DMA_Init(spi_drv->config->dma_tx->DMAChx, &spi_drv->dma.TX_DMA_ChInitStr);

        /* Enable transfer complete interrupt */
        DMA_ConfigInt(spi_drv->config->dma_tx->DMAChx, DMA_INT_TXC, ENABLE);

        /* Enable the specified DMA channel */
        DMA_EnableChannel(spi_drv->config->dma_tx->DMAChx, ENABLE);

        SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_TX, ENABLE);
#endif
    }
    else
    {
        LOG_E("SPI DMA TX Mode, TX DMA did not complete initialization.");
        return -RT_ERROR;
    }

    /* Set SPI Direction */
    spi_drv->Direct = SPI_Tx;

    /* Check if the SPI is already enabled */
    if ((spi_drv->config->SPIx->CTRL2 & SPI_CTRL2_SPIEN) != SPI_CTRL2_SPIEN)
    {
        SPI_Enable(spi_drv->config->SPIx, ENABLE);
    }

    return RT_EOK;
}

static rt_err_t SPI_DMA_Receive(struct n32_spi *spi_drv, uint8_t *pData, uint16_t Size)
{
    RT_ASSERT(spi_drv != RT_NULL);

    if (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_DOUBLELINE_FULLDUPLEX && spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_MASTER)
    {
#if defined(SOC_SERIES_N32H7xx)
        /* Master recv-only in 4-wire full-duplex still has to clock the bus,
         * but must not echo the caller's RX buffer onto MOSI (the old bug:
         * TX DMA sourced pData itself and pushed the pre-message RX contents
         * out on MOSI). The TX leg now reads the static 0xFF fill buffer; the
         * fd_rxonly_dummy_tx flag makes n32_spi_dma_arm re-point every LLI TX
         * node at the fill base. RX keeps capturing into pData and the arm
         * order / Direct / ISR / warm-arm (engine_warm) semantics of
         * SPI_DMA_TransmitReceive are unchanged (it stays textually
         * untouched; completion still arrives via spi_rx_dma_isr on
         * Direct == SPI_Tx_Rx). */
        rt_err_t result;

        spi_drv->fd_rxonly_dummy_tx = RT_TRUE;
        result = SPI_DMA_TransmitReceive(spi_drv, spi_fd_rxonly_dummy, pData, Size);
        spi_drv->fd_rxonly_dummy_tx = RT_FALSE;
        return result;
#else
        return SPI_DMA_TransmitReceive(spi_drv, pData, pData, Size);
#endif
    }

    rt_bool_t m2warm_rx_defer = RT_FALSE;

    if (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_RX ||
        spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_TX)
    {
        if (n32_spi_mode2_3w_master(spi_drv))
        {
            /* Always-on mode2 master: defer the RX flip until both DMA
             * channels are armed below. The flip itself starts the
             * free-running receiver, so the residue drain and the arms must
             * come first or the opening bytes are missed; a cold engine
             * additionally needs the SPIEN 0->1 enable after the arms,
             * which the deferred flip then also covers. */
            m2warm_rx_defer = RT_TRUE;
        }
        else
        {
            n32_spi_singleline_dir(spi_drv, SPI_DIR_SINGLELINE_RX);
        }
    }

    /* Clear any stale RX residue BEFORE arming the RX DMA channel: once
     * RDMAEN is set the first DMA transfer would swallow a leftover byte in
     * DAT as rx[0] (slave-side 1-byte right-shift + trailing RNE=1 symptom).
     * For a slave the master has not started clocking yet, so no real first
     * byte can be lost here. */
    SPI_I2S_ReceiveData(spi_drv->config->SPIx);
    SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);

    if (spi_drv->dma.DMA_Rx_Init == RT_TRUE)
    {
#if defined(SOC_SERIES_N32H7xx)
        /* SPI RX DMA receive (single block or seamless LLI chain) */
        n32_spi_dma_arm(spi_drv, RT_TRUE, RT_TRUE, pData, Size);
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
        /* SPI RX DMA Receive Data for H49X */
        DMA_EnableChannel(spi_drv->config->dma_rx->DMAChx, DISABLE);

        /* Configure DMA request remapping */
        DMA_RequestRemap(spi_drv->config->dma_rx->request, spi_drv->config->dma_rx->DMAChx, ENABLE);

        spi_drv->dma.RX_DMA_ChInitStr.MemAddr = (uint32_t)pData;
        spi_drv->dma.RX_DMA_ChInitStr.BufSize = Size;

        DMA_Init(spi_drv->config->dma_rx->DMAChx, &spi_drv->dma.RX_DMA_ChInitStr);

        /* Enable transfer complete interrupt */
        DMA_ConfigInt(spi_drv->config->dma_rx->DMAChx, DMA_INT_TXC, ENABLE);

        /* Enable the specified DMA channel */
        DMA_EnableChannel(spi_drv->config->dma_rx->DMAChx, ENABLE);

        SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_RX, ENABLE);
#endif
    }
    else
    {
        LOG_E("SPI DMA RX Mode, RX DMA did not complete initialization.");
        return -RT_ERROR;
    }

    if (spi_drv->dma.DMA_Tx_Init == RT_TRUE)
    {
#if defined(SOC_SERIES_N32H7xx)
        /* Receive mode: the TX channel is armed as an empty block (this direction does not take part) */
        if (n32_spi_dma_arm(spi_drv, RT_FALSE, RT_FALSE, RT_NULL, 0U) != RT_EOK)
        {
            return -RT_ERROR;
        }
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)

        DMA_EnableChannel(spi_drv->config->dma_tx->DMAChx, DISABLE);

        spi_drv->dma.TX_DMA_ChInitStr.MemAddr = 0;
        spi_drv->dma.TX_DMA_ChInitStr.BufSize = 0;

        DMA_EnableChannel(spi_drv->config->dma_tx->DMAChx, ENABLE);
        DMA_Init(spi_drv->config->dma_tx->DMAChx, &spi_drv->dma.TX_DMA_ChInitStr);

#endif
    }

    /* Enable Error Interrupt */
    SPI_I2S_EnableInt(spi_drv->config->SPIx, SPI_I2S_INT_ERR, ENABLE);

    /* Set SPI Direction */
    spi_drv->Direct = SPI_Rx;

    /* Check if the SPI is already enabled */
    if ((spi_drv->config->SPIx->CTRL2 & SPI_CTRL2_SPIEN) != SPI_CTRL2_SPIEN)
    {
        SPI_Enable(spi_drv->config->SPIx, ENABLE);
    }

    if (m2warm_rx_defer)
    {
        /* Start the always-on RX engine (see the note at the flip site):
         * the live BIDIOE clear makes the mode2 receiver free-run, so the
         * RX DMA must already be armed (it is - above) to catch every byte
         * from the very first clock. */
        n32_spi_mode2_3w_set_dir(spi_drv, SPI_DIR_SINGLELINE_RX);
    }

    return RT_EOK;
}

static rt_err_t SPI_Transmit_Receive(struct n32_spi *spi_drv, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
    uint16_t Tx_Size_Const = Size;
    uint16_t Tx_Size = Size;
    uint16_t Rx_Size = Size;
    uint32_t tickstart;

    RT_ASSERT(spi_drv != RT_NULL);

    /* Bidirectional PIO is master-only: a slave cannot meet the per-byte
     * service deadline by CPU polling. The master owns SCLK (slave has no
     * flow control) and the master/slave threads on one core interleave at
     * the ms scheduler quantum, far coarser than the byte time - see the
     * DMA_TRANS_MIN_LEN note in spixfer for the full reasoning. In DMA-on
     * builds a slave message never reaches this gate (slave is forced
     * through DMA); in a no-DMA build it does and fails fast with -EIO
     * instead of silently dropping bytes. */
    if (!((spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_MASTER) && (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_DOUBLELINE_FULLDUPLEX)))
    {
        return -RT_EIO;
    }

    if ((spi_drv->config->SPIx->CTRL2 & SPI_CTRL2_SPIEN) != SPI_CTRL2_SPIEN)
    {
        SPI_Enable(spi_drv->config->SPIx, ENABLE);
    }

    if (spi_drv->SPI_InitStructure.DataLen == SPI_DATA_SIZE_16BITS)
    {
        if ((spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE) || (Tx_Size_Const == 1U))
        {
            spi_drv->config->SPIx->DAT = *((const uint16_t *)pTxData);
            pTxData += sizeof(uint16_t);
            Tx_Size--;
        }

        while ((Tx_Size > 0U) || (Rx_Size > 0U))
        {
            if (Tx_Size > 0U)
            {
                tickstart = rt_tick_get();
                /*  Loop while DAT register in not emplty */
                while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
                {
                    if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                    {
                        LOG_E("Checking TE flag timeout befor send data in full-duplex mode.");
                        return -RT_ETIMEOUT;
                    }
                }

                /* Send byte through the SPI1 peripheral */
                SPI_I2S_TransmitData(spi_drv->config->SPIx, *(const uint16_t *)pTxData);
                pTxData += sizeof(uint16_t);

                Tx_Size--;
            }

            tickstart = rt_tick_get();
            /* Wait for DATA send has complete */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking TE flag timeout after send data in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            tickstart = rt_tick_get();
            /* Wait for SPI bus idle */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_BUSY_FLAG) != RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking BUSY flag timeout in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            tickstart = rt_tick_get();
            /* Wait to receive a byte */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_RNE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking RNE flag timeout after send data in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            /* Return the byte read from the SPI bus */
            *((uint16_t *)pRxData) = (uint16_t)SPI_I2S_ReceiveData(spi_drv->config->SPIx);
            pRxData += sizeof(uint16_t);

            Rx_Size--;
        }
    }
    else if (spi_drv->SPI_InitStructure.DataLen == SPI_DATA_SIZE_8BITS)
    {
        if ((spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE) || (Tx_Size_Const == 1U))
        {
            spi_drv->config->SPIx->DAT = *((const uint8_t *)pTxData);
            pTxData += sizeof(uint8_t);
            Tx_Size--;
        }

        while ((Tx_Size > 0U) || (Rx_Size > 0U))
        {
            if (Tx_Size > 0U)
            {
                tickstart = rt_tick_get();
                /*  Loop while DAT register in not emplty */
                while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
                {
                    if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                    {
                        LOG_E("Checking TE flag timeout befor send data in full-duplex mode.");
                        return -RT_ETIMEOUT;
                    }
                }

                /* Send byte through the SPI1 peripheral */
                SPI_I2S_TransmitData(spi_drv->config->SPIx, *(const uint8_t *)pTxData);
                pTxData += sizeof(uint8_t);

                Tx_Size--;
            }

            tickstart = rt_tick_get();
            /* Wait for DATA send has complete */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking TE flag timeout after send data in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            tickstart = rt_tick_get();
            /* Wait for SPI bus idle */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_BUSY_FLAG) != RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking BUSY flag timeout in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            tickstart = rt_tick_get();
            /* Wait to receive a byte */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_RNE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking RNE flag timeout after send data in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            /*!< Return the byte read from the SPI bus */
            *((uint8_t *)pRxData) = (uint8_t)SPI_I2S_ReceiveData(spi_drv->config->SPIx);
            pRxData += sizeof(uint8_t);

            Rx_Size--;
        }
    }
    else
    {
        return -RT_EINVAL;
    }

    if (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG) != RESET)
    {
        volatile uint32_t reg_tmp;
        reg_tmp = spi_drv->config->SPIx->DAT;
        reg_tmp = spi_drv->config->SPIx->STS;
        (void)reg_tmp;
    }

    return RT_EOK;
}

static rt_err_t SPI_Transmit(struct n32_spi *spi_drv, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint16_t Tx_Size_Const = Size;
    uint16_t Transfer_Size = Size;
    uint32_t tickstart;

    RT_ASSERT(spi_drv != RT_NULL);

    if (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_RX ||
        spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_TX)
    {
        n32_spi_singleline_dir(spi_drv, SPI_DIR_SINGLELINE_TX);
    }

    if ((spi_drv->config->SPIx->CTRL2 & SPI_CTRL2_SPIEN) != SPI_CTRL2_SPIEN)
    {
        SPI_Enable(spi_drv->config->SPIx, ENABLE);
    }


    if (spi_drv->SPI_InitStructure.DataLen == SPI_DATA_SIZE_16BITS)
    {
        if ((spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE) || (Tx_Size_Const == 1U))
        {
            spi_drv->config->SPIx->DAT = *((const uint16_t *)pData);
            pData += sizeof(uint16_t);
            Transfer_Size--;
        }

        while ((Transfer_Size > 0U))
        {
            tickstart = rt_tick_get();
            /*  Loop while DAT register in not emplty */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking TE flag timeout.");
                    return -RT_ETIMEOUT;
                }
            }


            /* Send byte through the SPI1 peripheral */
            SPI_I2S_TransmitData(spi_drv->config->SPIx, *(const uint16_t *)pData);
            pData += sizeof(uint16_t);

            Transfer_Size--;
        }
    }
    else if (spi_drv->SPI_InitStructure.DataLen == SPI_DATA_SIZE_8BITS)
    {
        if ((spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE) || (Tx_Size_Const == 1U))
        {
            spi_drv->config->SPIx->DAT = *((const uint8_t *)pData);
            pData += sizeof(uint8_t);
            Transfer_Size--;
        }
        while ((Transfer_Size > 0U))
        {
            tickstart = rt_tick_get();
            /*  Loop while DAT register in not emplty */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking TE flag timeout.");
                    return -RT_ETIMEOUT;
                }
            }


            /* Send byte through the SPI1 peripheral */
            SPI_I2S_TransmitData(spi_drv->config->SPIx, *(const uint8_t *)pData);
            pData += sizeof(uint8_t);

            Transfer_Size--;
        }
    }
    else
    {
    }

    tickstart = rt_tick_get();
    /* Wait for DATA send has complete */
    while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
    {
        if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
        {
            LOG_E("After sending the data, check the TE flag for timeout.");
            return -RT_ETIMEOUT;
        }
    }

    tickstart = rt_tick_get();
    /* Wait for SPI bus idle */
    while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_BUSY_FLAG) != RESET)
    {
        if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
        {
            LOG_E("After sending the data, check the BUSY flag for timeout.");
            return -RT_ETIMEOUT;
        }
    }

    if (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG) != RESET)
    {
        volatile uint32_t reg_tmp;
        reg_tmp = spi_drv->config->SPIx->DAT;
        reg_tmp = spi_drv->config->SPIx->STS;
        (void)reg_tmp;
    }

    return RT_EOK;
}

/* 4-wire full-duplex MASTER receive-only (PIO): a recv-only master still has
 * to clock the bus and must put a deterministic 0xFF fill on MOSI (the old
 * path echoed the caller's RX buffer into the TX slot). This mirrors
 * SPI_Transmit_Receive's per-frame discipline - per frame: wait TE, write the
 * fill, wait TE, wait BUSY clear, wait RNE, read the response - with the TX
 * source replaced by a constant write, so no TX buffer is touched at all
 * (no RX-buffer echo, no dummy-buffer length bound; any PIO length is safe).
 * The master-only FD gate mirrors SPI_Transmit_Receive (bidirectional PIO is
 * master-only; why: see the DMA_TRANS_MIN_LEN note in spixfer). Callers:
 * SP_Receive's full-duplex master recv-only shortcut.
 * The pre-drain of RNE/OVER belongs to the caller (SP_Receive does it). */
static rt_err_t SPI_Transmit_Receive_Fill(struct n32_spi *spi_drv, uint8_t *pData,
                                          uint16_t Size, uint32_t Timeout)
{
    uint16_t Tx_Size_Const = Size;
    uint16_t Tx_Size = Size;
    uint16_t Rx_Size = Size;
    uint32_t tickstart;

    RT_ASSERT(spi_drv != RT_NULL);

    if (!((spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_MASTER) && (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_DOUBLELINE_FULLDUPLEX)))
    {
        return -RT_EIO;
    }

    if ((spi_drv->config->SPIx->CTRL2 & SPI_CTRL2_SPIEN) != SPI_CTRL2_SPIEN)
    {
        SPI_Enable(spi_drv->config->SPIx, ENABLE);
    }

    if (spi_drv->SPI_InitStructure.DataLen == SPI_DATA_SIZE_16BITS)
    {
        if (Tx_Size_Const == 1U)
        {
            /* Fill word: a recv-only master clocks a deterministic 0xFFFF */
            spi_drv->config->SPIx->DAT = 0xFFFFU;
            Tx_Size--;
        }

        while ((Tx_Size > 0U) || (Rx_Size > 0U))
        {
            if (Tx_Size > 0U)
            {
                tickstart = rt_tick_get();
                /*  Loop while DAT register in not emplty */
                while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
                {
                    if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                    {
                        LOG_E("Checking TE flag timeout befor send data in full-duplex mode.");
                        return -RT_ETIMEOUT;
                    }
                }

                /* Fill word: a recv-only master clocks a deterministic 0xFFFF */
                SPI_I2S_TransmitData(spi_drv->config->SPIx, 0xFFFFU);
                Tx_Size--;
            }

            tickstart = rt_tick_get();
            /* Wait for DATA send has complete */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking TE flag timeout after send data in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            tickstart = rt_tick_get();
            /* Wait for SPI bus idle */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_BUSY_FLAG) != RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking BUSY flag timeout in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            tickstart = rt_tick_get();
            /* Wait to receive a byte */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_RNE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking RNE flag timeout after send data in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            /* Return the byte read from the SPI bus */
            *((uint16_t *)pData) = (uint16_t)SPI_I2S_ReceiveData(spi_drv->config->SPIx);
            pData += sizeof(uint16_t);

            Rx_Size--;
        }
    }
    else if (spi_drv->SPI_InitStructure.DataLen == SPI_DATA_SIZE_8BITS)
    {
        if (Tx_Size_Const == 1U)
        {
            /* Fill byte: a recv-only master clocks a deterministic 0xFF */
            spi_drv->config->SPIx->DAT = 0xFFU;
            Tx_Size--;
        }

        while ((Tx_Size > 0U) || (Rx_Size > 0U))
        {
            if (Tx_Size > 0U)
            {
                tickstart = rt_tick_get();
                /*  Loop while DAT register in not emplty */
                while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
                {
                    if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                    {
                        LOG_E("Checking TE flag timeout befor send data in full-duplex mode.");
                        return -RT_ETIMEOUT;
                    }
                }

                /* Fill byte: a recv-only master clocks a deterministic 0xFF */
                SPI_I2S_TransmitData(spi_drv->config->SPIx, 0xFFU);
                Tx_Size--;
            }

            tickstart = rt_tick_get();
            /* Wait for DATA send has complete */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking TE flag timeout after send data in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            tickstart = rt_tick_get();
            /* Wait for SPI bus idle */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_BUSY_FLAG) != RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking BUSY flag timeout in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            tickstart = rt_tick_get();
            /* Wait to receive a byte */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_RNE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("Checking RNE flag timeout after send data in full-duplex mode.");
                    return -RT_ETIMEOUT;
                }
            }

            /*!< Return the byte read from the SPI bus */
            *((uint8_t *)pData) = (uint8_t)SPI_I2S_ReceiveData(spi_drv->config->SPIx);
            pData += sizeof(uint8_t);

            Rx_Size--;
        }
    }
    else
    {
        return -RT_EINVAL;
    }

    if (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG) != RESET)
    {
        volatile uint32_t reg_tmp;
        reg_tmp = spi_drv->config->SPIx->DAT;
        reg_tmp = spi_drv->config->SPIx->STS;
        (void)reg_tmp;
    }

    return RT_EOK;
}


static rt_err_t SP_Receive(struct n32_spi *spi_drv, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint16_t Transfer_Size = Size;
    uint32_t tickstart;

    RT_ASSERT(spi_drv != RT_NULL);

    tickstart = rt_tick_get();
    while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_RNE_FLAG) != RESET || SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG) != RESET)
    {
        volatile uint32_t reg_tmp;
        reg_tmp = spi_drv->config->SPIx->DAT;
        reg_tmp = spi_drv->config->SPIx->STS;
        (void)reg_tmp;

        if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
        {
            LOG_E("Before receiving data, check the OVER and RNE flags for timeout.");
            return -RT_ETIMEOUT;
        }
    }

    if (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_DOUBLELINE_FULLDUPLEX && spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_MASTER)
    {
        return SPI_Transmit_Receive_Fill(spi_drv, pData, Size, Timeout);
    }

    if (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_RX ||
        spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_TX)
    {
        n32_spi_singleline_dir(spi_drv, SPI_DIR_SINGLELINE_RX);
    }

    if ((spi_drv->config->SPIx->CTRL2 & SPI_CTRL2_SPIEN) != SPI_CTRL2_SPIEN)
    {
        SPI_Enable(spi_drv->config->SPIx, ENABLE);
    }

    if (spi_drv->SPI_InitStructure.DataLen == SPI_DATA_SIZE_16BITS)
    {
        while ((Transfer_Size > 0U))
        {
            tickstart = rt_tick_get();
            /* Wait to receive a byte */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_RNE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("During receiving data, check the RNE flags for timeout.");
                    n32_spi_mode2_3w_rx_abort(spi_drv);
                    return -RT_ETIMEOUT;
                }
            }

            /*!< Return the byte read from the SPI bus */
            *((uint16_t *)pData) = (uint16_t)SPI_I2S_ReceiveData(spi_drv->config->SPIx);
            pData += sizeof(uint16_t);

            Transfer_Size--;
        }
    }
    else if (spi_drv->SPI_InitStructure.DataLen == SPI_DATA_SIZE_8BITS)
    {
        while ((Transfer_Size > 0U))
        {
            tickstart = rt_tick_get();
            /* Wait to receive a byte */
            while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_RNE_FLAG) == RESET)
            {
                if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
                {
                    LOG_E("During receiving data, check the RNE flags for timeout.");
                    n32_spi_mode2_3w_rx_abort(spi_drv);
                    return -RT_ETIMEOUT;
                }
            }

            /*!< Return the byte read from the SPI bus */
            *((uint8_t *)pData) = (uint8_t)SPI_I2S_ReceiveData(spi_drv->config->SPIx);
            pData += sizeof(uint8_t);

            Transfer_Size--;
        }
    }
    else
    {
    }

    if ((spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_DOUBLELINE_RONLY ||
         spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_RX) &&
        spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_MASTER)
    {
        if (n32_spi_mode2_3w_master(spi_drv))
        {
            /* Always-on mode2 3-wire master: dropping the engine would pull
             * SCK low into the enabled slave (the mode2 edge problem), so
             * instead leave RX and rest idle in TX - the bit14 set stops the
             * free-running receiver, which otherwise clocks continuously. */
            n32_spi_mode2_3w_set_dir(spi_drv, SPI_DIR_SINGLELINE_TX);
        }
        else
        {
            /* Disable the sFLASH_SPI  */
            SPI_Enable(spi_drv->config->SPIx, DISABLE);
        }
    }

    tickstart = rt_tick_get();
    /* Wait for SPI bus idle */
    while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_BUSY_FLAG) != RESET)
    {
        if ((((rt_tick_get() - tickstart) >= Timeout) && (Timeout != 0xFFFFFFFFU)) || (Timeout == 0U))
        {
            LOG_E("After receiving data, check the BUSY flags for timeout.");
            return -RT_ETIMEOUT;
        }
    }

    if (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG) != RESET)
    {
        volatile uint32_t reg_tmp;
        reg_tmp = spi_drv->config->SPIx->DAT;
        reg_tmp = spi_drv->config->SPIx->STS;
        (void)reg_tmp;
    }

    return RT_EOK;
}


static rt_err_t n32_spi_init(struct n32_spi *spi_drv, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(spi_drv != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    /* Force a clean start: DeInit resets the peripheral (clearing stale
     * 3WIRE/BIDIR/DMA-enable/OVER state); otherwise leftovers of a previous
     * configuration (e.g. a half-duplex 3WIRE run), such as BIDIR/TDMAEN,
     * would pollute this one. */
    SPI_I2S_DeInit(spi_drv->config->SPIx);

    SPI_InitStruct(&spi_drv->SPI_InitStructure);

    if (cfg->mode & RT_SPI_SLAVE)
    {
        spi_drv->SPI_InitStructure.SpiMode = SPI_MODE_SLAVE;
    }
    else
    {
        spi_drv->SPI_InitStructure.SpiMode = SPI_MODE_MASTER;
    }

    if (cfg->mode & RT_SPI_3WIRE)
    {
        /* Switch TX/RX direction dynamically according to the application */
        spi_drv->SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_RX;
        /* NOTE: mode2 (CPOL=1, CPHA=0) corrupts data as long as the engine
         * cold-starts per message: the SPIEN 0->1 pulls SCK low then rises
         * into the already-enabled mode2 slave, its bit counter gains one
         * spurious edge and the whole frame grid shifts by one bit
         * (rx[j] = (b[j-1] & 1) << 7 | b[j] >> 1; a whole 4096B frame
         * matches this deterministically; m0/1/3 sample after the data
         * lands, so they are immune). Not a silicon defect: the vendor
         * full-duplex soft-NSS demo on the same chip passes mode2 with an
         * always-on engine. Fixed for the 3-wire master exactly like the
         * 4-wire FD master: the engine is pre-enabled at configure (in the
         * TX posture) and kept across message tails; the per-message
         * direction flip toggles CTRL1's BIDIOE bit directly without
         * dropping SPIEN (re-running SPI_Init cannot switch TX->RX warm: its
         * CLR_MASK 0xF9F7 preserves bit14, making the flip a silent no-op;
         * see n32_spi_mode2_3w_set_dir / n32_spi_singleline_dir). The 3-wire
         * slave keeps its legacy cold cycle per message (its enable now
         * happens on an SCK line clamped idle-high by the master, so no
         * spurious edge is possible). FD mode2 uses the same always-on
         * scheme via n32_spi_mode2_fd_master. */
    }
    else
    {
        spi_drv->SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    }

    if (cfg->data_width == 8)
    {
        spi_drv->SPI_InitStructure.DataLen = SPI_DATA_SIZE_8BITS;
    }
    else if (cfg->data_width == 16)
    {
        spi_drv->SPI_InitStructure.DataLen = SPI_DATA_SIZE_16BITS;
    }
    else
    {
        return -RT_EIO;
    }

    if (cfg->mode & RT_SPI_CPHA)
    {
        spi_drv->SPI_InitStructure.CLKPHA = SPI_CLKPHA_SECOND_EDGE;
    }
    else
    {
        spi_drv->SPI_InitStructure.CLKPHA = SPI_CLKPHA_FIRST_EDGE;
    }

    if (cfg->mode & RT_SPI_CPOL)
    {
        spi_drv->SPI_InitStructure.CLKPOL = SPI_CLKPOL_HIGH;
    }
    else
    {
        spi_drv->SPI_InitStructure.CLKPOL = SPI_CLKPOL_LOW;
    }

    spi_drv->SPI_InitStructure.NSS = SPI_NSS_SOFT;
    spi_drv->SPI_InitStructure.CRCPoly = 7;

    uint32_t SPI_CLOCK = 0UL;

#if defined(SOC_SERIES_N32H7xx)
    RCC_ClocksTypeDef RCC_Clocks = { 0 };

    RCC_GetClocksFreqValue(&RCC_Clocks);

    if ((spi_drv->config->SPIx == SPI1) || (spi_drv->config->SPIx == SPI2))
    {
        SPI_CLOCK = RCC_Clocks.APB2ClkFreq;
    }
    else if (spi_drv->config->SPIx == SPI3)
    {
        SPI_CLOCK = RCC_Clocks.APB1ClkFreq;
    }
    else if ((spi_drv->config->SPIx == SPI4) || (spi_drv->config->SPIx == SPI5) || (spi_drv->config->SPIx == SPI6) || (spi_drv->config->SPIx == SPI7))
    {
        SPI_CLOCK = RCC_Clocks.APB5ClkFreq;
    }
    else
    {
        return -RT_EIO;
    }
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)

    RCC_ClocksType RCC_ClockFreq = { 0 };

    RCC_GetClocksFreqValue(&RCC_ClockFreq);

    if ((spi_drv->config->SPIx == SPI1) || (spi_drv->config->SPIx == SPI4) || (spi_drv->config->SPIx == SPI5) || (spi_drv->config->SPIx == SPI6))
    {
        SPI_CLOCK = RCC_ClockFreq.Pclk2Freq;
    }
    else if ((spi_drv->config->SPIx == SPI2) || (spi_drv->config->SPIx == SPI3))
    {
        SPI_CLOCK = RCC_ClockFreq.Pclk1Freq;
    }
#endif

    if (cfg->max_hz >= SPI_CLOCK / 2)
    {
        spi_drv->SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_2;
    }
    else if (cfg->max_hz >= SPI_CLOCK / 4)
    {
        spi_drv->SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_4;
    }
    else if (cfg->max_hz >= SPI_CLOCK / 8)
    {
        spi_drv->SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_8;
    }
    else if (cfg->max_hz >= SPI_CLOCK / 16)
    {
        spi_drv->SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_16;
    }
    else if (cfg->max_hz >= SPI_CLOCK / 32)
    {
        spi_drv->SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_32;
    }
    else if (cfg->max_hz >= SPI_CLOCK / 64)
    {
        spi_drv->SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_64;
    }
    else if (cfg->max_hz >= SPI_CLOCK / 128)
    {
        spi_drv->SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_128;
    }
    else
    {
        /*  min prescaler 256 */
        spi_drv->SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_256;
    }

    if (cfg->mode & RT_SPI_MSB)
    {
        spi_drv->SPI_InitStructure.FirstBit = SPI_FB_MSB;
    }
    else
    {
        spi_drv->SPI_InitStructure.FirstBit = SPI_FB_LSB;
    }

    /* Initializes the SPIx peripheral */
    SPI_Init(spi_drv->config->SPIx, &spi_drv->SPI_InitStructure);

    /* Disable leftover DMA channels/events: SPI_Init does not clear DMA
     * enables or TC events, so residue across configurations keeps the
     * previous channels alive (notably on 3WIRE->FD switches). */
#if defined(SOC_SERIES_N32H7xx)
    if (spi_drv->config->dma_rx)
    {
        DMA_ChannelCmd(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, DISABLE);
    }
    if (spi_drv->config->dma_tx)
    {
        DMA_ChannelCmd(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, DISABLE);
    }
#endif

    /* DMA configuration */
    if (spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG)
    {
        if (cfg->data_width == 8)
        {
#if defined(SOC_SERIES_N32H7xx)
            spi_drv->dma.RX_DMA_ChInitStr.SrcTfrWidth = DMA_CH_TRANSFER_WIDTH_8;
            spi_drv->dma.RX_DMA_ChInitStr.DstTfrWidth = DMA_CH_TRANSFER_WIDTH_8;
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
            spi_drv->dma.RX_DMA_ChInitStr.PeriphDataSize = DMA_PERIPH_DATA_WIDTH_BYTE;
            spi_drv->dma.RX_DMA_ChInitStr.MemDataSize = DMA_MEM_DATA_WIDTH_BYTE;
#endif
        }
        else if (cfg->data_width == 16)
        {
#if defined(SOC_SERIES_N32H7xx)
            spi_drv->dma.RX_DMA_ChInitStr.SrcTfrWidth = DMA_CH_TRANSFER_WIDTH_16;
            spi_drv->dma.RX_DMA_ChInitStr.DstTfrWidth = DMA_CH_TRANSFER_WIDTH_16;
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
            spi_drv->dma.RX_DMA_ChInitStr.PeriphDataSize = DMA_PERIPH_DATA_WIDTH_HALFWORD;
            spi_drv->dma.RX_DMA_ChInitStr.MemDataSize = DMA_MEM_DATA_WIDTH_HALFWORD;
#endif
        }

        /* enable dma irq */
        NVIC_SetPriority(spi_drv->config->dma_rx->dma_irq, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
        NVIC_EnableIRQ(spi_drv->config->dma_rx->dma_irq);
    }

    if (spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG)
    {
        if (cfg->data_width == 8)
        {
#if defined(SOC_SERIES_N32H7xx)
            spi_drv->dma.TX_DMA_ChInitStr.SrcTfrWidth = DMA_CH_TRANSFER_WIDTH_8;
            spi_drv->dma.TX_DMA_ChInitStr.DstTfrWidth = DMA_CH_TRANSFER_WIDTH_8;
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
            spi_drv->dma.TX_DMA_ChInitStr.PeriphDataSize = DMA_PERIPH_DATA_WIDTH_BYTE;
            spi_drv->dma.TX_DMA_ChInitStr.MemDataSize = DMA_MEM_DATA_WIDTH_BYTE;
#endif
        }
        else if (cfg->data_width == 16)
        {
#if defined(SOC_SERIES_N32H7xx)
            spi_drv->dma.TX_DMA_ChInitStr.SrcTfrWidth = DMA_CH_TRANSFER_WIDTH_16;
            spi_drv->dma.TX_DMA_ChInitStr.DstTfrWidth = DMA_CH_TRANSFER_WIDTH_16;
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
            spi_drv->dma.TX_DMA_ChInitStr.PeriphDataSize = DMA_PERIPH_DATA_WIDTH_HALFWORD;
            spi_drv->dma.TX_DMA_ChInitStr.MemDataSize = DMA_MEM_DATA_WIDTH_HALFWORD;
#endif
        }

        /* enable dma irq */
        NVIC_SetPriority(spi_drv->config->dma_tx->dma_irq, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
        NVIC_EnableIRQ(spi_drv->config->dma_tx->dma_irq);
    }

    if (spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG || spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG)
    {
        /* enable dma irq */
        NVIC_SetPriority(spi_drv->config->irq_type, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
        NVIC_EnableIRQ(spi_drv->config->irq_type);
    }

    /* Pre-enable the engine of a mode2 master (FD or 3-wire single-line,
     * see the big note in SPI_DMA_TransmitReceive): configuration itself
     * does the 0->1 start and clamps SCK idle-high -- the peer slave engine
     * is off at that moment (its message tail disabled it), so the rising
     * edge on a dead slave is harmless. Every later slave arm then happens
     * on an idle-high SCK and the message self-starts via the warm-engine
     * DMA level trigger (no more SPIEN 0->1). Non-mode2 configurations keep
     * the engine off (SPI_I2S_DeInit+Init already reset it) and keep the
     * legacy cold-start semantics per message. */
    if (n32_spi_mode2_fd_master(spi_drv) || n32_spi_mode2_3w_master(spi_drv))
    {
        if (n32_spi_mode2_3w_master(spi_drv))
        {
            /* Pre-enable in the TX posture (bit14 set): a single-line RX
             * engine free-runs SCK as soon as SPIEN=1 (measured: OVER=1
             * garbage polluting the first message after the mode boundary),
             * while TX idles quietly until DAT is written. */
            n32_spi_mode2_3w_set_dir(spi_drv, SPI_DIR_SINGLELINE_TX);
        }
        SPI_Enable(spi_drv->config->SPIx, ENABLE);
    }

    LOG_D("%s init done", spi_drv->config->bus_name);
    return RT_EOK;
}


static rt_err_t spi_configure(struct rt_spi_device *device,
                              struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    struct n32_spi *spi_drv = rt_container_of(device->bus, struct n32_spi, spi_bus);
    spi_drv->cfg = configuration;

    return n32_spi_init(spi_drv, configuration);
}


static rt_ssize_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
#define DMA_TRANS_MIN_LEN 10 /* Slave messages never use CPU-polled (PIO)
                                  transfer, and the PIO helpers are
                                  master-only. Why:

                                  An SPI slave has no flow control: the
                                  master owns SCLK, so the slave must service
                                  every byte within one byte time (at 1 MHz
                                  that is 8 us - drain RNE / refill DAT before
                                  the next shift) or the frame is lost.
                                  Under RT-Thread the master and slave SPIs
                                  are driven by two threads on one core, so
                                  they can never be serviced at the same
                                  time; the interleave granularity is the
                                  scheduler quantum (ms), about three orders
                                  of magnitude coarser than the per-byte
                                  deadline -> thread polling drops bytes the
                                  moment a message outlives one quantum. Only
                                  DMA (hardware moves each byte the instant
                                  the SPI requests it) or a per-byte
                                  RNE/TE interrupt could meet the deadline;
                                  this driver implements DMA and polling but
                                  no per-byte IRQ path, so DMA is the only
                                  viable slave path. Hence every slave
                                  message (>= 1B) is forced through DMA
                                  (SpiMode == SPI_MODE_SLAVE overrides this
                                  length limit at every dispatch), and the
                                  PIO helpers reject SLAVE with -RT_EIO. A
                                  no-DMA build therefore has no working slave
                                  path at all - expected by design (no partial
                                  frames are produced either). Master
                                  messages below this length (and any master
                                  message in a no-DMA build) are CPU-polled,
                                  which a master can afford because it owns
                                  the clock and paces itself. */

    rt_err_t state = RT_EOK;
    uint32_t tickstart;
    rt_size_t message_length, already_send_length;
    rt_uint16_t send_length;
    rt_uint8_t *recv_buf;
    const rt_uint8_t *send_buf;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    struct n32_spi *spi_drv = rt_container_of(device->bus, struct n32_spi, spi_bus);

    if (message->cs_take && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
        {
            rt_pin_write(device->cs_pin, PIN_HIGH);
        }
        else
        {
            rt_pin_write(device->cs_pin, PIN_LOW);
        }
    }

    LOG_D("%s transfer prepare and start", spi_drv->config->bus_name);
    LOG_D("%s sendbuf: %X, recvbuf: %X, length: %d",
          spi_drv->config->bus_name,
          (uint32_t)message->send_buf,
          (uint32_t)message->recv_buf, message->length);

    message_length = message->length;
    recv_buf = message->recv_buf;
    send_buf = message->send_buf;
    /* Whether this message is 4-wire full-duplex (send and recv both set).
     * An FD message must disable SPI at its tail (see the message-tail
     * note) -- both DMA and PIO ones (PIO = non-mode2 master len<10): if a
     * PIO FD message leaves the engine ON, the next message's cold-start
     * disable->enable produces spurious SCK edges on the already-enabled
     * slave (a short PIO mode3 message corrupts from its first byte). The
     * mode2 FD master with its always-on engine is the only exception (see
     * the message-tail note). */
    rt_bool_t fd_msg = (message->send_buf && message->recv_buf) ? RT_TRUE : RT_FALSE;

    while (message_length)
    {
#if defined(SOC_SERIES_N32H7xx)
        /* One DMA arm covers up to ARM_MAX elements on the clock-driving
         * side only; a longer message is split into consecutive arms. The
         * engine stays on across chunk boundaries (only the message tail
         * disables -- see the loop bottom) and chunk-2+ master arms re-arm
         * the live engine warm (fd_chunk_cont, see SPI_DMA_TransmitReceive).
         * The slave must NOT chunk: its DMA legs are request-driven (they
         * only advance under the master's clock), so a single
         * request-driven arm of up to CHAIN_MAX absorbs the master's
         * inter-arm clock gaps without any re-arm -- a slave chunk boundary
         * would instead race the master's continuous clock (its thread must
         * re-arm the RX channel while the master is already clocking the
         * next chunk; every 8192-element case loses that race at the
         * boundary). The cap keeps each master arm under the N32H7xx
         * per-arm transfer ceiling (~4128 items at the 20 MHz top rate, see
         * SPI_DMA_ARM_MAX) -- a ceiling that applies to a clock-driving arm,
         * i.e. one that keeps the engine on for its whole length while a
         * second DMA channel competes for the bus.
         *
         * A single-line (3-wire) master message arms exactly one channel
         * with data (SPI_DMA_Transmit / SPI_DMA_Receive arm the other one as
         * an empty block), so it never meets that dual-channel arm and it
         * gets the chain cap like the slave. Chunking a 3-wire master leg is
         * not merely unnecessary, it CORRUPTS: every chunk-2+ arm takes the
         * cold path (n32_spi_singleline_dir -> DISABLE + DeInit + Init for
         * every mode but mode2), so the mid-message peripheral restart puts
         * a spurious SCK edge onto the peer whose frame grid is already
         * mid-message, and the 3-wire tail DISABLE block below used to fire
         * at every chunk tail as well. Every len=8192 case with CPHA=1 then
         * fails with the first wrong byte at index 4096, in both 3-wire
         * directions and byte for byte identically at 1 MHz and at 100 kHz
         * -- which rules out a re-arm timing race and pins it on the
         * edge/phase corruption of the restart. A 4-wire message keeps the
         * bounded arm (both channels live: FD, or the recv-only master that
         * clocks through the 0xFF dummy TX). */
        rt_uint32_t arm_max;
        if (spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE)
        {
            arm_max = SPI_DMA_CHAIN_MAX;
        }
        else if ((device->config.mode & RT_SPI_3WIRE) && !fd_msg)
        {
            arm_max = SPI_DMA_CHAIN_MAX;
        }
        else
        {
            arm_max = SPI_DMA_ARM_MAX;
        }
        if (message_length > arm_max)
        {
            send_length = arm_max;
            message_length = message_length - arm_max;
        }
        else
        {
            send_length = message_length;
            message_length = 0;
        }
#else
        /* DMA uses a single block, with a maximum of 4095 per block */
        if (message_length > 4095)
        {
            send_length = 4095;
            message_length = message_length - 4095;
        }
        else
        {
            send_length = message_length;
            message_length = 0;
        }
#endif

        /* calculate the start address */
        already_send_length = message->length - send_length - message_length;
        /* Mark a non-first chunk of a 4-wire full-duplex message for the
         * arm (fd_chunk_cont): chunks keep the engine on, so this chunk's
         * SPI_DMA_TransmitReceive arm must re-arm the live engine warm
         * rather than drop SPIEN and re-enable -- that mid-message cycle
         * puts CPOL=1 SCK edges onto the enabled slave and shifts its frame
         * grid (see the warm re-arm note). Slaves never chunk below
         * SPI_DMA_CHAIN_MAX and ignore the flag anyway. */
        spi_drv->fd_chunk_cont = (fd_msg && (already_send_length != 0U)) ? RT_TRUE : RT_FALSE;
        /* avoid null pointer problems */
        if (message->send_buf)
        {
            send_buf = (rt_uint8_t *)message->send_buf + already_send_length;
        }
        if (message->recv_buf)
        {
            recv_buf = (rt_uint8_t *)message->recv_buf + already_send_length;
        }

        rt_uint32_t *dma_aligned_buffer = RT_NULL; /* TX staging buffer (copy path only) */
        rt_uint32_t *dma_rx_staging = RT_NULL;     /* RX staging buffer (copy path only) */
        rt_uint32_t *p_tx_buffer = RT_NULL;        /* real source that TX DMA reads   */
        rt_uint32_t *p_rx_buffer = RT_NULL;        /* real destination RX DMA writes to */
        /* Which legs of this chunk the DMA serves: the PIO length gate plus
         * two exceptions - a slave never PIO-polls, and neither does a
         * 3-wire master receive (see the dispatch note for the measured
         * reason). The 3-wire exception is receive-only by construction
         * (send_buf == RT_NULL): a bidirectional 3-wire message below the
         * gate is served by the PIO helper, which writes the caller's
         * buffers directly, so staging such a message would only copy an
         * uninitialized buffer back over the real data.
         * Every site below that stages, dispatches, synchronizes or tails a
         * leg reads these - they must all agree. If they disagree - a
         * 3-wire receive dispatch on the DMA gate whose completion wait and
         * tail still use the PIO gate - the receive returns before its DMA
         * has run: zero bytes received, instant return, at every rate. */
        rt_bool_t tx_leg_dma = ((spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG) != 0U) &&
                               (send_buf != RT_NULL) &&
                               ((send_length >= DMA_TRANS_MIN_LEN) ||
                                (spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE));
        rt_bool_t rx_leg_dma = ((spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG) != 0U) &&
                               (recv_buf != RT_NULL) &&
                               ((send_length >= DMA_TRANS_MIN_LEN) ||
                                (spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE) ||
                                ((send_buf == RT_NULL) && ((device->config.mode & RT_SPI_3WIRE) != 0)));
        rt_bool_t msg_dma = tx_leg_dma || rx_leg_dma;
        /* Loop work vars: declared above the error gotos so a chunk-exit
         * jump never bypasses an initialization (armcc #546-D) */
        rt_tick_t busy_to;
        rt_bool_t busy_to_ok;
        rt_bool_t dma_leg;

        /* TX source preparation: allocate/use directly only when data is
         * actually being sent. The direct path (p_tx_buffer == send_buf) is
         * kept apart from the copy path so full-duplex DMA never shares one
         * buffer between TX and RX (an RX echo would overwrite the TX source
         * and recv_buf would never see data - fixed). */
        if (tx_leg_dma)
        {
#if defined(SOC_SERIES_N32H7xx)
            /* send_length counts elements: buffer/copy/cache sizes must be
             * converted to bytes by the data width */
            rt_uint32_t send_bytes = send_length * (spi_drv->cfg->data_width / 8u);
            if (RT_IS_ALIGN((rt_uint32_t)send_buf, 32)) /* aligned with 32 bytes? */
            {
                p_tx_buffer = (rt_uint32_t *)send_buf; /* send_buf aligns with 32 bytes, DMA reads it directly */
            }
            else
            {
                /* send_buf doesn't align with 32 bytes, so creat a cache buffer with 32 bytes aligned */
                dma_aligned_buffer = (rt_uint32_t *)rt_malloc_align(send_bytes, 32);
                if (dma_aligned_buffer == RT_NULL)
                {
                    LOG_E("malloc TX align buf failed, len=%u", send_length);
                    state = -RT_ENOMEM;
                    goto spi_staging_free;
                }
                rt_memcpy(dma_aligned_buffer, send_buf, send_bytes);
                p_tx_buffer = dma_aligned_buffer;
            }
            if ((SCB->CCR & (uint32_t)SCB_CCR_DC_Msk) != 0U)
            {
                /* flush the REAL DMA source: direct path must flush send_buf too */
                rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, p_tx_buffer, send_bytes);
            }
#else
            if (RT_IS_ALIGN((rt_uint32_t)send_buf, 4) && send_buf != RT_NULL) /* aligned with 4 bytes? */
            {
                p_tx_buffer = (rt_uint32_t *)send_buf; /* send_buf aligns with 4 bytes, no more operations */
            }
            else
            {
                /* send_buf doesn't align with 4 bytes, so creat a cache buffer with 4 bytes aligned */
                dma_aligned_buffer = (rt_uint32_t *)rt_malloc(send_length); /* aligned with RT_ALIGN_SIZE (8 bytes by default) */
                if (dma_aligned_buffer == RT_NULL)
                {
                    LOG_E("SPI DMA TX buffer malloc failed!");
                    state = -RT_ENOMEM;
                    goto spi_staging_free;
                }
                rt_memcpy(dma_aligned_buffer, send_buf, send_length);
                p_tx_buffer = dma_aligned_buffer;
            }
#endif
        }

        /* RX destination preparation: allocate/use directly only when data
         * is actually being received. The direct path (p_rx_buffer ==
         * recv_buf) is kept apart from the staging path; staging is always
         * copied back on completion. */
        if (rx_leg_dma)
        {
#if defined(SOC_SERIES_N32H7xx)
            /* send_length counts elements: the RX staging buffer is likewise
             * allocated in bytes (x2 for 16-bit data) */
            rt_uint32_t recv_bytes = send_length * (spi_drv->cfg->data_width / 8u);
            if (RT_IS_ALIGN((rt_uint32_t)recv_buf, 32))
            {
                p_rx_buffer = (rt_uint32_t *)recv_buf; /* DMA writes straight into caller's buffer */
            }
            else
            {
                dma_rx_staging = (rt_uint32_t *)rt_malloc_align(recv_bytes, 32);
                if (dma_rx_staging == RT_NULL)
                {
                    LOG_E("malloc RX staging buf failed, len=%u", send_length);
                    state = -RT_ENOMEM;
                    goto spi_staging_free;
                }
                p_rx_buffer = dma_rx_staging;
            }
#else
            p_rx_buffer = (rt_uint32_t *)recv_buf;
#endif
        }

        tickstart = rt_tick_get();
        /* Check the SPI RNE Flag */
        while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_RNE_FLAG) != RESET)
        {
            /*clear RX buff*/
            volatile rt_uint32_t dummy = spi_drv->config->SPIx->DAT;
            (void)dummy;

            if ((rt_tick_get() - tickstart) > 1000U)
            {
                state = -RT_ERROR;
                LOG_E("Checking the RNE flag timeout before transmission begins!");
                break;
            }
        }

        tickstart = rt_tick_get();
        /* Check the SPI OVER Flag */
        while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG) != RESET)
        {
            /*clear RX buff*/
            volatile rt_uint32_t dummy = spi_drv->config->SPIx->DAT;
            (void)dummy;
            SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);

            if ((rt_tick_get() - tickstart) > 1000U)
            {
                state = -RT_ERROR;
                LOG_E("Checking the OVER flag timeout before transmission begins!");
                break;
            }
        }

        /* start once data exchange in DMA mode */
        if (message->send_buf && message->recv_buf)
        {
            if ((spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG) && (spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG) && ((send_length >= DMA_TRANS_MIN_LEN || spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE)))
            {
                /* TX/RX buffer separation: even when send_buf and recv_buf
                 * differ, DMA TX/RX must never share one source */
                if ((p_tx_buffer == RT_NULL) || (p_rx_buffer == RT_NULL))
                {
                    LOG_E("full-duplex DMA: TX %p RX %p buf missing (from %p,%p len=%u)",
                          p_tx_buffer, p_rx_buffer, send_buf, recv_buf, send_length);
                    state = -RT_ERROR;
                    goto spi_staging_free;
                }
                state = SPI_DMA_TransmitReceive(spi_drv, (uint8_t *)p_tx_buffer, (uint8_t *)p_rx_buffer, send_length);
            }
            else if ((spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG) && ((send_length >= DMA_TRANS_MIN_LEN || spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE)))
            {
                state = SPI_DMA_Transmit(spi_drv, (uint8_t *)p_tx_buffer, send_length);
            }
            else if ((spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG) && ((send_length >= DMA_TRANS_MIN_LEN || spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE)))
            {
                state = -RT_ERROR;
                LOG_E("It shoule be enabled both BSP_SPIx_TX_USING_DMA and BSP_SPIx_TX_USING_DMA flag, if wants to use SPI DMA Rx singly.");
                goto spi_staging_free;
            }
            else
            {
                state = SPI_Transmit_Receive(spi_drv, (uint8_t *)send_buf, (uint8_t *)recv_buf, send_length, 1000);
            }
        }
        else if (message->send_buf)
        {
            if ((spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG) && ((send_length >= DMA_TRANS_MIN_LEN || spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_SLAVE)))
            {
                if (p_tx_buffer == RT_NULL)
                {
                    LOG_E("SPI DMA TX: source buf missing");
                    state = -RT_ERROR;
                    goto spi_staging_free;
                }
                state = SPI_DMA_Transmit(spi_drv, (uint8_t *)p_tx_buffer, send_length);
            }
            else
            {
                state = SPI_Transmit(spi_drv, (uint8_t *)send_buf, send_length, 1000);
            }
        }
        else if (message->recv_buf)
        {
            /* rx_leg_dma: a 3-wire master receive must never be PIO-polled.
             * The 3-wire master receiver free-runs SCLK the moment the
             * direction flips to RX, so SP_Receive has no deadline it can
             * meet by construction - it occasionally reads DAT while a byte
             * is still shifting in and stores the partial shift register.
             * The stored value is always the expected byte shifted right by
             * k bits with the idle-high tail filled (0xc6 read back as
             * 0x01/0x03/0x07/0x0d/0x19, 0x31 as 0x01) - a deterministic per
             * (rate, mode, len) beat rather than a rare glitch, so retrying
             * does not help. The DMA path never showed it at any rate up to
             * 16384 elements. 4-wire messages (incl. the
             * recv-only 4-wire master that clocks via SPI_Transmit_Receive_
             * Fill) keep the PIO gate unchanged. */
            if (rx_leg_dma)
            {
                if (p_rx_buffer == RT_NULL)
                {
                    LOG_E("SPI DMA RX: dest buf missing");
                    state = -RT_ERROR;
                    goto spi_staging_free;
                }
                state = SPI_DMA_Receive(spi_drv, (uint8_t *)p_rx_buffer, send_length);
            }
            else
            {
                /* clear the old error flag */
                __IO uint32_t tmpreg = 0x00U;
                tmpreg = spi_drv->config->SPIx->DAT;
                tmpreg = spi_drv->config->SPIx->STS;
                (void)tmpreg;

                state = SP_Receive(spi_drv, (uint8_t *)recv_buf, send_length, 1000);
            }
        }
        else
        {
            state = -RT_ERROR;
            LOG_E("message->send_buf and message->recv_buf are both NULL!");
        }

        if (state != RT_EOK)
        {
            LOG_E("SPI transfer error: %d", state);
            message->length = 0;
            goto spi_staging_free;
        }
        else
        {
            LOG_D("%s transfer done", spi_drv->config->bus_name);
        }

        /* For simplicity reasons, this example is just waiting till the end of the
           transfer, but application may perform other tasks while transfer operation
           is ongoing. */
        if (msg_dma)
        {
            /* blocking the thread,and the other tasks can run */
            if (rt_completion_wait(&spi_drv->cpt, 1000) != RT_EOK)
            {
                state = -RT_ERROR;
                LOG_E("wait for DMA interrupt overtime!");
                /* Always-on mode2 3-wire master: a timed-out RX leg would
                 * otherwise keep its free-running engine clocking into the
                 * next message - stop it (no-op for every other role). */
                n32_spi_mode2_3w_rx_abort(spi_drv);
                goto spi_staging_free;
            }
        }

        /* The DMA leg (the if below) waits for BUSY with "benign timeout"
         * semantics; the non-DMA (PIO) leg keeps its original 1000-tick
         * ceiling and still errors on expiry:
         *  a) The DMA-send leg first waits for TE=1: DMA TC fires on the
         *     last DAT write, right after the second-to-last load, when the
         *     last byte is still in DAT waiting for the next frame-boundary
         *     load. If BUSY=0 were waited on directly, polling on a slow
         *     clock (<= 1MHz) can catch the momentary BUSY drop before the
         *     last byte is loaded (BUSY idles between two adjacent bytes)
         *     and move ahead to the 3-wire DISABLE -> the last byte never
         *     shifts out -> the peer receives an empty tail byte (measured:
         *     rx[len-1] always wrong). Follow the manual: wait for TE=1
         *     first (the last byte has left DAT into the shift register).
         *  b) Then wait for BUSY=0, but cap it with a short timeout derived
         *     from the configured bit clock (at 128 bit-times there is >= 8x
         *     headroom over the real clock: prescaler rounding makes the
         *     actual baud rate > max_hz/2). On a single-wire slave transfer
         *     BUSY may never fall after all data has shifted out/in (DMA TC
         *     proves the last byte arrived: CPHA=1 (mode1/3) slave sending,
         *     CPOL=1+CPHA=0 (mode2) slave receiving -- the engine waits for a
         *     frame-boundary clock that never comes; measured: all wire data
         *     correct, peer compare passed). Timeout expiry is treated as
         *     end-of-transfer and the tail finishes as a success -- treating
         *     it as an error would skip the 3-wire DISABLE and leave SPIEN=1
         *     stuck.
         *     In mode0 BUSY falls normally and the flag exits immediately;
         *     this timeout never applies. */
        busy_to = 1000U;
        busy_to_ok = RT_FALSE; /* DMA-leg timeout expiry = benign end */
        dma_leg = msg_dma;
        if (dma_leg)
        {
            busy_to_ok = RT_TRUE;
            if (message->send_buf && (spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG))
            {
                tickstart = rt_tick_get();
                while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_TE_FLAG) == RESET)
                {
                    if ((rt_tick_get() - tickstart) > 1000U)
                    {
                        state = -RT_ERROR;
                        LOG_E("Wait SPI TE Flag Timeout!");
                        break;
                    }
                }
            }
            if (state == RT_EOK)
            {
                rt_uint32_t hz = spi_drv->cfg->max_hz;
                if (hz != 0U)
                {
                    rt_uint32_t ms = (128000U + hz - 1U) / hz; /* 128 bit-times -> ms */
                    busy_to = (rt_tick_t)ms * RT_TICK_PER_SECOND / 1000U;
                    if (busy_to < 1U)
                    {
                        busy_to = 1U;
                    }
                }
            }
        }

        tickstart = rt_tick_get();
        while (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_BUSY_FLAG) != RESET)
        {
            if ((rt_tick_get() - tickstart) > busy_to)
            {
                if (!busy_to_ok)
                {
                    state = -RT_ERROR;
                    LOG_E("Wait SPI BUSY Flag Timeout!");
                }
                break;
            }
        }

        /* 3-wire has no CS line: disable SPI once the message (chunk) really
         * ends to release the bus. DISABLE must come after the DMA completes
         * and BUSY clears: disabling right after the DMA is armed (as the
         * old send-only branch did) cuts the clock that drives the slave TX
         * DMA -> the DMA never completes -> 3-wire leg BA (slave send-only)
         * wait DMA interrupt overtime. The mode2 3-wire master engine stays
         * on (pre-enabled at configure, never disabled between messages):
         * dropping it would pull the idle-high SCK low and the next slave
         * arm (which precedes the master clock) would land on a low line ->
         * the mode2 spurious-edge problem returns.
         *
         * Message tail only (message_length == 0), exactly like the FD block
         * below: a 3-wire master message is armed as one single-line leg
         * (CHAIN_MAX, see the arm_max note) so an intermediate chunk exists
         * only past 65520 elements, but should it ever happen, disabling
         * mid-message would put a spurious SCK edge on the peer same as the
         * FD case. The last chunk still disables -- the 3-wire mode3 skew
         * fix (single-chunk messages included) depends on that. */
        if ((device->config.mode & RT_SPI_3WIRE) && message->cs_release && (state == RT_EOK) &&
            (message_length == 0U))
        {
            if (!n32_spi_mode2_3w_master(spi_drv))
            {
                SPI_Enable(spi_drv->config->SPIx, DISABLE);
            }
        }

        /* RX data out: the staging path copies back unconditionally; the
         * direct path (dma_rx_staging == NULL) only needs a cache flush */
        if ((recv_buf != RT_NULL) && (p_rx_buffer != RT_NULL))
        {
#if defined(SOC_SERIES_N32H7xx)
            /* RX buffer/cache sizes are in bytes (16-bit elements x2) */
            rt_uint32_t recv_bytes = send_length * (spi_drv->cfg->data_width / 8u);
            if ((SCB->CCR & (uint32_t)SCB_CCR_DC_Msk) != 0U)
            {
                rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, p_rx_buffer, recv_bytes);
            }
#endif /* SOC_SERIES_N32H7xx */
            if (dma_rx_staging != RT_NULL)
            {
                rt_memcpy(recv_buf, p_rx_buffer, send_length * (spi_drv->cfg->data_width / 8u));
            }
        }

        /* Release the staging buffers (on success or failure). Chunk-exit
         * error paths jump here via goto: a failed transfer must never
         * leak the staging buffers it already allocated. */
    spi_staging_free:
#if defined(SOC_SERIES_N32H7xx)
        if (dma_aligned_buffer != RT_NULL)
        {
            rt_free_align(dma_aligned_buffer);
        }
        if (dma_rx_staging != RT_NULL)
        {
            rt_free_align(dma_rx_staging);
        }
#else
        if (dma_aligned_buffer != RT_NULL)
        {
            rt_free(dma_aligned_buffer);
        }
#endif /* SOC_SERIES_N32H7xx */

        if (state != RT_EOK)
        {
            /* Error: leave the chunk loop. Restore the between-message
             * engine posture (off for every role except the always-on
             * mode2 FD/3W masters) so the next message cold-starts exactly
             * as after a clean tail -- a mid-message error can leave the
             * engine enabled, and the next arm's cold cycle relies on
             * finding it off. */
            if (!n32_spi_mode2_fd_master(spi_drv) && !n32_spi_mode2_3w_master(spi_drv))
            {
                SPI_Enable(spi_drv->config->SPIx, DISABLE);
            }
            break; /* error: leave the chunk loop (tail returns -RT_ERROR) */
        }

        /* Disable SPI once an FD (4-wire) message really ends (DMA and PIO
         * alike) -- same semantics as the 3-wire case above (wait for DMA
         * completion + BUSY clear). A message chunked at SPI_DMA_ARM_MAX
         * keeps the engine ON across chunk boundaries: only the final chunk
         * (message_length == 0) disables here, and chunk-2+ arms re-arm the
         * live engine through the warm path (see SPI_DMA_TransmitReceive /
         * fd_chunk_cont). Dropping SPIEN at an intermediate chunk tail
         * would put the CPOL=1 idle-high SCK falling edge onto the slave,
         * which is mid-arm (single request-driven arm per message): the
         * slave counts the edge and its TX reply shifts -- measured as
         * chunk-2 corruption from byte 4096 of an 8192-element mode3
         * message at 20 MHz (mode0/1 are idle-low and have no edge; the
         * mode2 master never disables). For a single-chunk message this
         * block runs where it always did, at the message tail -- the mode3
         * skew fix depends on disabling SPI at the message tail. */
        if (fd_msg && message->cs_release && (message_length == 0U))
        {
            /* The mode2 FD master engine stays on (pre-enabled at
             * configure, never disabled between messages): disabling at the
             * tail would lose the idle-high SCK, and the next message's
             * slave arm (which precedes the master clock) would land on a
             * low line -> the mode2 spurious-edge problem returns (see the
             * SPI_DMA_TransmitReceive note). All other modes keep the
             * tail-disable semantics. */
            if (!n32_spi_mode2_fd_master(spi_drv))
            {
                SPI_Enable(spi_drv->config->SPIx, DISABLE);
            }
        }
    }

    if (message->cs_release && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
        {
            rt_pin_write(device->cs_pin, PIN_LOW);
        }
        else
        {
            rt_pin_write(device->cs_pin, PIN_HIGH);
        }
    }

    if (state != RT_EOK)
    {
        return -RT_ERROR;
    }
    return message->length;
}

static const struct rt_spi_ops n32_spi_ops = {
    .configure = spi_configure,
    .xfer = spixfer,
};


static int rt_hw_spi_bus_init(void)
{
    rt_err_t result;

#if defined(SOC_SERIES_N32H7xx)
    /* Fill the FD master recv-only TX dummy once: it is read-only afterwards
     * (every LLI node re-reads from its base), so a single init-time fill
     * and cache flush covers all buses and all subsequent messages. */
    rt_memset(spi_fd_rxonly_dummy, 0xFF, sizeof(spi_fd_rxonly_dummy));
    if ((SCB->CCR & SCB_CCR_DC_Msk) != 0U)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, spi_fd_rxonly_dummy, sizeof(spi_fd_rxonly_dummy));
    }
#endif

    for (rt_size_t i = 0; i < sizeof(spi_config) / sizeof(spi_config[0]); i++)
    {
        spi_bus_obj[i].config = &spi_config[i];
        spi_bus_obj[i].spi_bus.parent.user_data = &spi_config[i];


        if (spi_bus_obj[i].spi_dma_flag & SPI_USING_RX_DMA_FLAG)
        {
#if defined(SOC_SERIES_N32H7xx)
            /* Configure the SPI RX DMA for Transmission process */
            /* Enable DMA clock */
            RCC_EnableAHB1PeriphClk3(spi_bus_obj[i].config->dma_rx->dma_rcc, ENABLE);
            /* Enable DMA MUXclock  */
            RCC_EnableAHB1PeriphClk1(RCC_AHB1_PERIPHEN_M7_DMAMUX1, ENABLE);

            /* Receive DMA Config */
            DMA_ChannelStructInit(&spi_bus_obj[i].dma.RX_DMA_ChInitStr);
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.IntEn = 0x1U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcAddr = (uint32_t)&spi_bus_obj[i].config->SPIx->DAT;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstAddr = NULL;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcTfrWidth = DMA_CH_TRANSFER_WIDTH_8;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstTfrWidth = DMA_CH_TRANSFER_WIDTH_8;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstAddrCountMode = DMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcAddrCountMode = DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstBurstLen = DMA_CH_BURST_LENGTH_1;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcBurstLen = DMA_CH_BURST_LENGTH_1;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcGatherEn = 0x0U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstScatterEn = 0x0U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.TfrTypeFlowCtrl = DMA_CH_TRANSFER_FLOW_P2M_DMA;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.BlkTfrSize = 0U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.pLinkListItem = NULL;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcGatherInterval = 0x0U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcGatherCount = 0x0U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstScatterInterval = 0x0U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstScatterCount = 0x0U;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.TfrType = DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.ChannelPriority = DMA_CH_PRIORITY_7;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcHandshaking = DMA_CH_SRC_HANDSHAKING_HARDWARE;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.DstHandshaking = DMA_CH_DST_HANDSHAKING_SOFTWARE;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.SrcHsInterface = spi_bus_obj[i].config->dma_rx->HsInterface;

            /* DMA controller must be enabled before initializing the channel */
            DMA_ControllerCmd(spi_bus_obj[i].config->dma_rx->Instance, ENABLE);

            /* Initialize the specified DMA channel and Whether the specified channel was successfully initialized */
            if (DMA_ChannelInit(spi_bus_obj[i].config->dma_rx->Instance, &spi_bus_obj[i].dma.RX_DMA_ChInitStr, spi_bus_obj[i].config->dma_rx->dma_channel) == 0U)
            {
                /* Configure DMAMUX */
                DMAMUX_SetRequestID(DMAMUX1_ID, spi_bus_obj[i].config->dma_rx->dmamux_channel, spi_bus_obj[i].config->dma_rx->dmamux_request);

                spi_bus_obj[i].dma.DMA_Rx_Init = RT_TRUE;
            }
            else
            {
                LOG_E("SPI RX DMA channel initialization failed!");
                return -RT_ERROR;
            }
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
            /* Configure the SPI RX DMA for Transmission process */
            /* Enable DMA clock */
            RCC_EnableAHBPeriphClk(spi_bus_obj[i].config->dma_rx->dma_rcc, ENABLE);

            /* Receive DMA Config */
            DMA_StructInit(&spi_bus_obj[i].dma.RX_DMA_ChInitStr);
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.PeriphAddr = (uint32_t)&spi_bus_obj[i].config->SPIx->DAT;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.MemAddr = 0;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.Direction = DMA_DIR_PERIPH_SRC;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.BufSize = 0;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.PeriphInc = DMA_PERIPH_INC_DISABLE;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.MemoryInc = DMA_MEM_INC_ENABLE;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.PeriphDataSize = DMA_PERIPH_DATA_WIDTH_BYTE;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.MemDataSize = DMA_MEM_DATA_WIDTH_BYTE;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.CircularMode = DMA_MODE_NORMAL;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.Priority = DMA_PRIORITY_HIGH;
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.Mem2Mem = DMA_M2M_DISABLE;
#if defined(SOC_SERIES_N32H49x)
            spi_bus_obj[i].dma.RX_DMA_ChInitStr.BurstCmd = DMA_BURST_DISABLE;
#endif
            /* Initialize the specified DMA channel and Whether the specified channel was successfully initialized */
            DMA_Init(spi_bus_obj[i].config->dma_rx->DMAChx, &spi_bus_obj[i].dma.RX_DMA_ChInitStr);

            /* Enable transfer complete interrupt */
            DMA_ConfigInt(spi_bus_obj[i].config->dma_rx->DMAChx, DMA_INT_TXC, ENABLE);

            spi_bus_obj[i].dma.DMA_Rx_Init = RT_TRUE;


#endif
        }

        if (spi_bus_obj[i].spi_dma_flag & SPI_USING_TX_DMA_FLAG)
        {
#if defined(SOC_SERIES_N32H7xx)
            /* Configure the SPI TX DMA for Transmission process */
            /* Enable DMA clock */
            RCC_EnableAHB1PeriphClk3(spi_bus_obj[i].config->dma_tx->dma_rcc, ENABLE);
            /* Enable DMA MUXclock  */
            RCC_EnableAHB1PeriphClk1(RCC_AHB1_PERIPHEN_M7_DMAMUX1, ENABLE);

            /* SPI_MASTER_Tx_DMA_Channel DMA1 Channel1 configuration ---------------------------------------------*/
            DMA_ChannelStructInit(&spi_bus_obj[i].dma.TX_DMA_ChInitStr);
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.IntEn = 0x1U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstAddr = (uint32_t)&spi_bus_obj[i].config->SPIx->DAT;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcAddr = NULL;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcTfrWidth = DMA_CH_TRANSFER_WIDTH_8;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstTfrWidth = DMA_CH_TRANSFER_WIDTH_8;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstAddrCountMode = DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcAddrCountMode = DMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstBurstLen = DMA_CH_BURST_LENGTH_1;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcBurstLen = DMA_CH_BURST_LENGTH_1;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcGatherEn = 0x0U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstScatterEn = 0x0U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.TfrTypeFlowCtrl = DMA_CH_TRANSFER_FLOW_M2P_DMA;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.BlkTfrSize = 0U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.pLinkListItem = NULL;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcGatherInterval = 0x0U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcGatherCount = 0x0U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstScatterInterval = 0x0U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstScatterCount = 0x0U;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.TfrType = DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.ChannelPriority = DMA_CH_PRIORITY_7;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.SrcHandshaking = DMA_CH_SRC_HANDSHAKING_SOFTWARE;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstHandshaking = DMA_CH_DST_HANDSHAKING_HARDWARE;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.DstHsInterface = spi_bus_obj[i].config->dma_tx->HsInterface;

            /* DMA controller must be enabled before initializing the channel */
            DMA_ControllerCmd(spi_bus_obj[i].config->dma_tx->Instance, ENABLE);

            /* Initialize the specified DMA channel and Whether the specified channel was successfully initialized */
            if (DMA_ChannelInit(spi_bus_obj[i].config->dma_tx->Instance, &spi_bus_obj[i].dma.TX_DMA_ChInitStr, spi_bus_obj[i].config->dma_tx->dma_channel) == 0U)
            {
                /* Configure DMAMUX */
                DMAMUX_SetRequestID(DMAMUX1_ID, spi_bus_obj[i].config->dma_tx->dmamux_channel, spi_bus_obj[i].config->dma_tx->dmamux_request);

                spi_bus_obj[i].dma.DMA_Tx_Init = RT_TRUE;
            }
            else
            {
                LOG_E("SPI TX DMA channel initialization failed!");
                return -RT_ERROR;
            }
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
            /* Configure the SPI TX DMA for Transmission process */
            /* Enable DMA clock */
            RCC_EnableAHBPeriphClk(spi_bus_obj[i].config->dma_tx->dma_rcc, ENABLE);

            /* SPI_MASTER_Tx_DMA_Channel DMA1 Channel1 configuration ---------------------------------------------*/
            DMA_StructInit(&spi_bus_obj[i].dma.TX_DMA_ChInitStr);
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.PeriphAddr = (uint32_t)&spi_bus_obj[i].config->SPIx->DAT;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.MemAddr = 0;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.Direction = DMA_DIR_PERIPH_DST;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.BufSize = 0;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.PeriphInc = DMA_PERIPH_INC_DISABLE;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.MemoryInc = DMA_MEM_INC_ENABLE;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.PeriphDataSize = DMA_PERIPH_DATA_WIDTH_BYTE;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.MemDataSize = DMA_MEM_DATA_WIDTH_BYTE;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.CircularMode = DMA_MODE_NORMAL;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.Priority = DMA_PRIORITY_HIGH;
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.Mem2Mem = DMA_M2M_DISABLE;
#if defined(SOC_SERIES_N32H49x)
            spi_bus_obj[i].dma.TX_DMA_ChInitStr.BurstCmd = DMA_BURST_DISABLE;
#endif
            /* Initialize the specified DMA channel and Whether the specified channel was successfully initialized */
            DMA_Init(spi_bus_obj[i].config->dma_tx->DMAChx, &spi_bus_obj[i].dma.TX_DMA_ChInitStr);

            /* Enable transfer complete interrupt */
            DMA_ConfigInt(spi_bus_obj[i].config->dma_tx->DMAChx, DMA_INT_TXC, ENABLE);

            spi_bus_obj[i].dma.DMA_Tx_Init = RT_TRUE;


#endif
        }


        /* initialize completion object */
        rt_completion_init(&spi_bus_obj[i].cpt);

        result = rt_spi_bus_register(&spi_bus_obj[i].spi_bus, spi_config[i].bus_name, &n32_spi_ops);
        RT_ASSERT(result == RT_EOK);

        LOG_D("%s bus init done", spi_config[i].bus_name);
    }

    return result;
}


/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    result = rt_spi_bus_attach_device_cspin(spi_device, device_name, bus_name, cs_pin, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    RT_ASSERT(result == RT_EOK);

    LOG_D("%s attach to %s done", device_name, bus_name);

    return result;
}


#if defined(BSP_SPI1_RX_USING_DMA) || defined(BSP_SPI1_TX_USING_DMA) || \
    defined(BSP_SPI2_RX_USING_DMA) || defined(BSP_SPI2_TX_USING_DMA) || \
    defined(BSP_SPI3_RX_USING_DMA) || defined(BSP_SPI3_TX_USING_DMA) || \
    defined(BSP_SPI4_RX_USING_DMA) || defined(BSP_SPI4_TX_USING_DMA) || \
    defined(BSP_SPI5_RX_USING_DMA) || defined(BSP_SPI5_TX_USING_DMA) || \
    defined(BSP_SPI6_RX_USING_DMA) || defined(BSP_SPI6_TX_USING_DMA) || \
    defined(BSP_SPI7_RX_USING_DMA) || defined(BSP_SPI7_TX_USING_DMA)
static void spi_isr(struct n32_spi *spi_drv)
{
    if (SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG) == SET)
    {
        SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_TX | SPI_I2S_DMA_RX, DISABLE);

        if (spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG)
        {
#if defined(SOC_SERIES_N32H7xx)
            DMA_ChannelEventCmd(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, DISABLE);
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
            DMA_ConfigInt(spi_drv->config->dma_tx->DMAChx, DMA_INT_TXC, DISABLE);
#endif
        }

        if (spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG)
        {
#if defined(SOC_SERIES_N32H7xx)
            DMA_ChannelEventCmd(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, DISABLE);
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
            DMA_ConfigInt(spi_drv->config->dma_rx->DMAChx, DMA_INT_TXC, DISABLE);
#endif
        }

        SPI_I2S_EnableInt(spi_drv->config->SPIx, SPI_I2S_INT_ERR, DISABLE);

        SPI_I2S_ReceiveData(spi_drv->config->SPIx);
        SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);
    }
}

#if defined(BSP_SPI1_RX_USING_DMA) || \
    defined(BSP_SPI2_RX_USING_DMA) || \
    defined(BSP_SPI3_RX_USING_DMA) || \
    defined(BSP_SPI4_RX_USING_DMA) || \
    defined(BSP_SPI5_RX_USING_DMA) || \
    defined(BSP_SPI6_RX_USING_DMA) || \
    defined(BSP_SPI7_RX_USING_DMA)
static void spi_rx_dma_isr(struct n32_spi *spi_drv)
{
#if defined(SOC_SERIES_N32H7xx)
    if (DMA_GetCombinedStatus(spi_drv->config->dma_rx->Instance))
    {
        if (DMA_GetChannelIntTfrStatus(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel) == SET)
        {
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
    DMA_Module *dma_module = (DMA_Module *)((uint32_t)spi_drv->config->dma_rx->DMAChx < DMA2_BASE ? DMA1 : DMA2);
    uint32_t dma_int_tc = 0;

    /* Obtain the corresponding interrupt flag macro based on the channel */
    if (spi_drv->config->dma_rx->DMAChx == DMA1_CH1)
    {
        dma_int_tc = DMA_INT_TXC1;
    }
    else if (spi_drv->config->dma_rx->DMAChx == DMA1_CH2)
    {
        dma_int_tc = DMA_INT_TXC2;
    }
    else if (spi_drv->config->dma_rx->DMAChx == DMA1_CH3)
    {
        dma_int_tc = DMA_INT_TXC3;
    }
    else if (spi_drv->config->dma_rx->DMAChx == DMA1_CH4)
    {
        dma_int_tc = DMA_INT_TXC4;
    }
    else if (spi_drv->config->dma_rx->DMAChx == DMA1_CH5)
    {
        dma_int_tc = DMA_INT_TXC5;
    }
    else if (spi_drv->config->dma_rx->DMAChx == DMA1_CH6)
    {
        dma_int_tc = DMA_INT_TXC6;
    }
    else if (spi_drv->config->dma_rx->DMAChx == DMA1_CH7)
    {
        dma_int_tc = DMA_INT_TXC7;
    }
    else if (spi_drv->config->dma_rx->DMAChx == DMA1_CH8)
    {
        dma_int_tc = DMA_INT_TXC8;
    }
    else if (spi_drv->config->dma_rx->DMAChx == DMA2_CH1)
    {
        dma_int_tc = DMA_INT_TXC1;
    }
    else if (spi_drv->config->dma_rx->DMAChx == DMA2_CH2)
    {
        dma_int_tc = DMA_INT_TXC2;
    }
    else if (spi_drv->config->dma_rx->DMAChx == DMA2_CH3)
    {
        dma_int_tc = DMA_INT_TXC3;
    }
    else if (spi_drv->config->dma_rx->DMAChx == DMA2_CH4)
    {
        dma_int_tc = DMA_INT_TXC4;
    }
    else if (spi_drv->config->dma_rx->DMAChx == DMA2_CH5)
    {
        dma_int_tc = DMA_INT_TXC5;
    }
    else if (spi_drv->config->dma_rx->DMAChx == DMA2_CH6)
    {
        dma_int_tc = DMA_INT_TXC6;
    }
    else if (spi_drv->config->dma_rx->DMAChx == DMA2_CH7)
    {
        dma_int_tc = DMA_INT_TXC7;
    }
    else if (spi_drv->config->dma_rx->DMAChx == DMA2_CH8)
    {
        dma_int_tc = DMA_INT_TXC8;
    }

    if (dma_int_tc != 0 && DMA_GetIntStatus(dma_int_tc, dma_module) == SET)
    {
#endif
            if (spi_drv->Direct == SPI_Tx_Rx)
            {
                SPI_I2S_EnableInt(spi_drv->config->SPIx, SPI_I2S_INT_ERR, DISABLE);

#if defined(SOC_SERIES_N32H7xx)
                DMA_ChannelEventCmd(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, DISABLE);
                DMA_ChannelEventCmd(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, DISABLE);
                /* Disable the RX/TX DMA channels: avoid leftover moves that
                 * RDMAEN would re-trigger after the slave completes */
                DMA_ChannelCmd(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, DISABLE);
                DMA_ChannelCmd(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, DISABLE);
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
                DMA_ConfigInt(spi_drv->config->dma_rx->DMAChx, DMA_INT_TXC, DISABLE);
                DMA_ConfigInt(spi_drv->config->dma_tx->DMAChx, DMA_INT_TXC, DISABLE);
#endif

                if (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_DOUBLELINE_FULLDUPLEX)
                {
                    /* After a full-duplex DMA completes, both master and
                     * slave must clear the SPI DMA enables: if RDMAEN/TDMAEN
                     * linger on the slave, a live DMA request would move the
                     * stale DAT byte of the next case -> the slave's first
                     * byte misaligns (rx[0] old value + right shift). */
                    SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_TX | SPI_I2S_DMA_RX, DISABLE);
                }

                SPI_I2S_ReceiveData(spi_drv->config->SPIx);
                SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);

                spi_drv->Direct = SPI_Idle;
                rt_completion_done(&spi_drv->cpt);
            }
            else if (spi_drv->Direct == SPI_Rx)
            {
                if (spi_drv->SPI_InitStructure.SpiMode == SPI_MODE_MASTER && (spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_SINGLELINE_RX ||
                                                                              spi_drv->SPI_InitStructure.DataDirection == SPI_DIR_DOUBLELINE_RONLY))
                {
                    if (n32_spi_mode2_3w_master(spi_drv))
                    {
                        /* Always-on mode2 3-wire master: the RX DMA is done,
                         * but the receiver free-runs until the direction
                         * leaves RX - flip back to TX (bit14 set, engine
                         * stays on; dropping SPIEN would pull SCK low into
                         * the enabled slave) so the next message starts from
                         * a quiet idle-high line. */
                        n32_spi_mode2_3w_set_dir(spi_drv, SPI_DIR_SINGLELINE_TX);
                    }
                    else
                    {
                        SPI_Enable(spi_drv->config->SPIx, DISABLE);
                    }
                }

                SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_RX, DISABLE);

                SPI_I2S_EnableInt(spi_drv->config->SPIx, SPI_I2S_INT_ERR, DISABLE);

#if defined(SOC_SERIES_N32H7xx)
                DMA_ChannelEventCmd(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, DISABLE);
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
                DMA_ConfigInt(spi_drv->config->dma_rx->DMAChx, DMA_INT_TXC, DISABLE);
#endif

                SPI_I2S_ReceiveData(spi_drv->config->SPIx);
                SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);

                spi_drv->Direct = SPI_Idle;
                rt_completion_done(&spi_drv->cpt);
            }

#if defined(SOC_SERIES_N32H7xx)
            /* Clear interrupt event status */
            DMA_ClearChannelEventStatus(spi_drv->config->dma_rx->Instance, spi_drv->config->dma_rx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE);
        }
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
            /* Clear interrupt event status */
            DMA_ClrIntPendingBit(dma_int_tc, dma_module);
#endif
    }
}
#endif

static void spi_tx_dma_isr(struct n32_spi *spi_drv)
{
#if defined(SOC_SERIES_N32H7xx)
    if (DMA_GetCombinedStatus(spi_drv->config->dma_tx->Instance))
    {
        if (DMA_GetChannelIntTfrStatus(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel) == SET)
        {
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
    DMA_Module *dma_module = (DMA_Module *)((uint32_t)spi_drv->config->dma_tx->DMAChx < DMA2_BASE ? DMA1 : DMA2);
    uint32_t dma_int_tc = 0;

    if (spi_drv->config->dma_tx->DMAChx == DMA1_CH1)
    {
        dma_int_tc = DMA_INT_TXC1;
    }
    else if (spi_drv->config->dma_tx->DMAChx == DMA1_CH2)
    {
        dma_int_tc = DMA_INT_TXC2;
    }
    else if (spi_drv->config->dma_tx->DMAChx == DMA1_CH3)
    {
        dma_int_tc = DMA_INT_TXC3;
    }
    else if (spi_drv->config->dma_tx->DMAChx == DMA1_CH4)
    {
        dma_int_tc = DMA_INT_TXC4;
    }
    else if (spi_drv->config->dma_tx->DMAChx == DMA1_CH5)
    {
        dma_int_tc = DMA_INT_TXC5;
    }
    else if (spi_drv->config->dma_tx->DMAChx == DMA1_CH6)
    {
        dma_int_tc = DMA_INT_TXC6;
    }
    else if (spi_drv->config->dma_tx->DMAChx == DMA1_CH7)
    {
        dma_int_tc = DMA_INT_TXC7;
    }
    else if (spi_drv->config->dma_tx->DMAChx == DMA1_CH8)
    {
        dma_int_tc = DMA_INT_TXC8;
    }
    else if (spi_drv->config->dma_tx->DMAChx == DMA2_CH1)
    {
        dma_int_tc = DMA_INT_TXC1;
    }
    else if (spi_drv->config->dma_tx->DMAChx == DMA2_CH2)
    {
        dma_int_tc = DMA_INT_TXC2;
    }
    else if (spi_drv->config->dma_tx->DMAChx == DMA2_CH3)
    {
        dma_int_tc = DMA_INT_TXC3;
    }
    else if (spi_drv->config->dma_tx->DMAChx == DMA2_CH4)
    {
        dma_int_tc = DMA_INT_TXC4;
    }
    else if (spi_drv->config->dma_tx->DMAChx == DMA2_CH5)
    {
        dma_int_tc = DMA_INT_TXC5;
    }
    else if (spi_drv->config->dma_tx->DMAChx == DMA2_CH6)
    {
        dma_int_tc = DMA_INT_TXC6;
    }
    else if (spi_drv->config->dma_tx->DMAChx == DMA2_CH7)
    {
        dma_int_tc = DMA_INT_TXC7;
    }
    else if (spi_drv->config->dma_tx->DMAChx == DMA2_CH8)
    {
        dma_int_tc = DMA_INT_TXC8;
    }

    if (dma_int_tc != 0 && DMA_GetIntStatus(dma_int_tc, dma_module) == SET)
    {
#endif
            if (spi_drv->Direct == SPI_Tx)
            {
#if defined(SOC_SERIES_N32H7xx)
                DMA_ChannelEventCmd(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE, DISABLE);

                SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_TX, DISABLE);
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
                SPI_I2S_EnableInt(spi_drv->config->SPIx, SPI_I2S_INT_ERR, DISABLE);

                SPI_I2S_EnableDma(spi_drv->config->SPIx, SPI_I2S_DMA_TX, DISABLE);
#endif

                SPI_I2S_ReceiveData(spi_drv->config->SPIx);
                SPI_I2S_GetStatus(spi_drv->config->SPIx, SPI_I2S_OVER_FLAG);

                spi_drv->Direct = SPI_Idle;
                rt_completion_done(&spi_drv->cpt);
            }

#if defined(SOC_SERIES_N32H7xx)
            /* Clear interrupt event status */
            DMA_ClearChannelEventStatus(spi_drv->config->dma_tx->Instance, spi_drv->config->dma_tx->dma_channel, DMA_CH_EVENT_TRANSFER_COMPLETE);
        }
    }
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
            /* Clear interrupt event status */
            DMA_ClrIntPendingBit(dma_int_tc, dma_module);
    }
#endif
}
#endif

#if defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI1_RX_USING_DMA)
void SPI1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(&spi_bus_obj[SPI1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI1_RX_USING_DMA) */
#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_RX_USING_DMA)
void SPI1_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_rx_dma_isr(&spi_bus_obj[SPI1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI1) && defined(BSP_SPI1_RX_USING_DMA) */
#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_TX_USING_DMA)
void SPI1_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_tx_dma_isr(&spi_bus_obj[SPI1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI1) && defined(BSP_SPI1_TX_USING_DMA) */


#if defined(BSP_SPI2_TX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA)
#if defined(SOC_SERIES_N32H7xx)
void SPI2_IRQHandler(void)
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
void SPI2_I2S2_IRQHandler(void)
#endif
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(&spi_bus_obj[SPI2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI2_TX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA) */
#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_RX_USING_DMA)
void SPI2_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_rx_dma_isr(&spi_bus_obj[SPI2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI2) && defined(BSP_SPI2_RX_USING_DMA) */
#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_TX_USING_DMA)
void SPI2_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_tx_dma_isr(&spi_bus_obj[SPI2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI2) && defined(BSP_SPI2_TX_USING_DMA) */


#if defined(BSP_SPI3_TX_USING_DMA) || defined(BSP_SPI3_RX_USING_DMA)
#if defined(SOC_SERIES_N32H7xx)
void SPI3_IRQHandler(void)
#elif defined(SOC_SERIES_N32H49x) || defined(SOC_SERIES_N32H47x_48x)
void SPI3_I2S3_IRQHandler(void)
#endif
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(&spi_bus_obj[SPI3_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI3_TX_USING_DMA) || defined(BSP_SPI3_RX_USING_DMA) */
#if defined(BSP_USING_SPI3) && defined(BSP_SPI3_RX_USING_DMA)
void SPI3_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_rx_dma_isr(&spi_bus_obj[SPI3_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI3) && defined(BSP_SPI3_RX_USING_DMA) */
#if defined(BSP_USING_SPI3) && defined(BSP_SPI3_TX_USING_DMA)
void SPI3_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_tx_dma_isr(&spi_bus_obj[SPI3_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI3) && defined(BSP_SPI3_TX_USING_DMA) */


#if defined(BSP_SPI4_TX_USING_DMA) || defined(BSP_SPI4_RX_USING_DMA)
void SPI4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(&spi_bus_obj[SPI4_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI4_TX_USING_DMA) || defined(BSP_SPI4_RX_USING_DMA) */
#if defined(BSP_USING_SPI4) && defined(BSP_SPI4_RX_USING_DMA)
void SPI4_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_rx_dma_isr(&spi_bus_obj[SPI4_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI4) && defined(BSP_SPI4_RX_USING_DMA) */
#if defined(BSP_USING_SPI4) && defined(BSP_SPI4_TX_USING_DMA)
void SPI4_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_tx_dma_isr(&spi_bus_obj[SPI4_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI4) && defined(BSP_SPI4_TX_USING_DMA) */


#if defined(BSP_SPI5_TX_USING_DMA) || defined(BSP_SPI5_RX_USING_DMA)
void SPI5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(&spi_bus_obj[SPI5_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI5_TX_USING_DMA) || defined(BSP_SPI5_RX_USING_DMA) */
#if defined(BSP_USING_SPI5) && defined(BSP_SPI5_RX_USING_DMA)
void SPI5_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_rx_dma_isr(&spi_bus_obj[SPI5_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI5) && defined(BSP_SPI5_RX_USING_DMA) */
#if defined(BSP_USING_SPI5) && defined(BSP_SPI5_TX_USING_DMA)
void SPI5_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_tx_dma_isr(&spi_bus_obj[SPI5_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI5) && defined(BSP_SPI5_TX_USING_DMA) */


#if defined(BSP_SPI6_TX_USING_DMA) || defined(BSP_SPI6_RX_USING_DMA)
void SPI6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(&spi_bus_obj[SPI6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI6_TX_USING_DMA) || defined(BSP_SPI6_RX_USING_DMA) */
#if defined(BSP_USING_SPI6) && defined(BSP_SPI6_RX_USING_DMA)
void SPI6_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_rx_dma_isr(&spi_bus_obj[SPI6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI6) && defined(BSP_SPI6_RX_USING_DMA) */
#if defined(BSP_USING_SPI6) && defined(BSP_SPI6_TX_USING_DMA)
void SPI6_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_tx_dma_isr(&spi_bus_obj[SPI6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI6) && defined(BSP_SPI6_TX_USING_DMA) */


#if defined(BSP_SPI7_TX_USING_DMA) || defined(BSP_SPI7_RX_USING_DMA)
void SPI7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(&spi_bus_obj[SPI7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI7_TX_USING_DMA) || defined(BSP_SPI7_RX_USING_DMA) */
#if defined(BSP_USING_SPI7) && defined(BSP_SPI7_RX_USING_DMA)
void SPI7_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_rx_dma_isr(&spi_bus_obj[SPI7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI7) && defined(BSP_SPI7_RX_USING_DMA) */
#if defined(BSP_USING_SPI7) && defined(BSP_SPI7_TX_USING_DMA)
void SPI7_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_tx_dma_isr(&spi_bus_obj[SPI7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI7) && defined(BSP_SPI7_TX_USING_DMA) */

static void n32_spi_get_dma_config(void)
{
#ifdef BSP_USING_SPI1
    spi_bus_obj[SPI1_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI1_RX_USING_DMA
    spi_bus_obj[SPI1_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi1_dma_rx = SPI1_RX_DMA_CONFIG;
    spi_config[SPI1_INDEX].dma_rx = &spi1_dma_rx;
#endif /* BSP_SPI1_RX_USING_DMA */
#ifdef BSP_SPI1_TX_USING_DMA
    spi_bus_obj[SPI1_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi1_dma_tx = SPI1_TX_DMA_CONFIG;
    spi_config[SPI1_INDEX].dma_tx = &spi1_dma_tx;
#endif /* BSP_SPI1_TX_USING_DMA */
#endif /* BSP_USING_SPI1 */

#ifdef BSP_USING_SPI2
    spi_bus_obj[SPI2_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI2_RX_USING_DMA
    spi_bus_obj[SPI2_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi2_dma_rx = SPI2_RX_DMA_CONFIG;
    spi_config[SPI2_INDEX].dma_rx = &spi2_dma_rx;
#endif /* BSP_SPI2_RX_USING_DMA */
#ifdef BSP_SPI2_TX_USING_DMA
    spi_bus_obj[SPI2_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi2_dma_tx = SPI2_TX_DMA_CONFIG;
    spi_config[SPI2_INDEX].dma_tx = &spi2_dma_tx;
#endif /* BSP_SPI2_TX_USING_DMA */
#endif /* BSP_USING_SPI2 */

#ifdef BSP_USING_SPI3
    spi_bus_obj[SPI3_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI3_RX_USING_DMA
    spi_bus_obj[SPI3_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi3_dma_rx = SPI3_RX_DMA_CONFIG;
    spi_config[SPI3_INDEX].dma_rx = &spi3_dma_rx;
#endif /* BSP_SPI3_RX_USING_DMA */
#ifdef BSP_SPI3_TX_USING_DMA
    spi_bus_obj[SPI3_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi3_dma_tx = SPI3_TX_DMA_CONFIG;
    spi_config[SPI3_INDEX].dma_tx = &spi3_dma_tx;
#endif /* BSP_SPI3_TX_USING_DMA */
#endif /* BSP_USING_SPI3 */

#ifdef BSP_USING_SPI4
    spi_bus_obj[SPI4_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI4_RX_USING_DMA
    spi_bus_obj[SPI4_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi4_dma_rx = SPI4_RX_DMA_CONFIG;
    spi_config[SPI4_INDEX].dma_rx = &spi4_dma_rx;
#endif /* BSP_SPI4_RX_USING_DMA */
#ifdef BSP_SPI4_TX_USING_DMA
    spi_bus_obj[SPI4_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi4_dma_tx = SPI4_TX_DMA_CONFIG;
    spi_config[SPI4_INDEX].dma_tx = &spi4_dma_tx;
#endif /* BSP_SPI4_TX_USING_DMA */
#endif /* BSP_USING_SPI4 */

#ifdef BSP_USING_SPI5
    spi_bus_obj[SPI5_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI5_RX_USING_DMA
    spi_bus_obj[SPI5_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi5_dma_rx = SPI5_RX_DMA_CONFIG;
    spi_config[SPI5_INDEX].dma_rx = &spi5_dma_rx;
#endif /* BSP_SPI5_RX_USING_DMA */
#ifdef BSP_SPI5_TX_USING_DMA
    spi_bus_obj[SPI5_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi5_dma_tx = SPI5_TX_DMA_CONFIG;
    spi_config[SPI5_INDEX].dma_tx = &spi5_dma_tx;
#endif /* BSP_SPI5_TX_USING_DMA */
#endif /* BSP_USING_SPI5 */

#ifdef BSP_USING_SPI6
    spi_bus_obj[SPI6_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI6_RX_USING_DMA
    spi_bus_obj[SPI6_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi6_dma_rx = SPI6_RX_DMA_CONFIG;
    spi_config[SPI6_INDEX].dma_rx = &spi6_dma_rx;
#endif /* BSP_SPI6_RX_USING_DMA */
#ifdef BSP_SPI6_TX_USING_DMA
    spi_bus_obj[SPI6_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi6_dma_tx = SPI6_TX_DMA_CONFIG;
    spi_config[SPI6_INDEX].dma_tx = &spi6_dma_tx;
#endif /* BSP_SPI6_TX_USING_DMA */
#endif /* BSP_USING_SPI6 */

#ifdef BSP_USING_SPI7
    spi_bus_obj[SPI7_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI7_RX_USING_DMA
    spi_bus_obj[SPI7_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi7_dma_rx = SPI7_RX_DMA_CONFIG;
    spi_config[SPI7_INDEX].dma_rx = &spi7_dma_rx;
#endif /* BSP_SPI7_RX_USING_DMA */
#ifdef BSP_SPI7_TX_USING_DMA
    spi_bus_obj[SPI7_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi7_dma_tx = SPI7_TX_DMA_CONFIG;
    spi_config[SPI7_INDEX].dma_tx = &spi7_dma_tx;
#endif /* BSP_SPI7_TX_USING_DMA */
#endif /* BSP_USING_SPI7 */
}


int rt_hw_spi_init(void)
{
    n32_spi_get_dma_config();
    return rt_hw_spi_bus_init();
}
INIT_BOARD_EXPORT(rt_hw_spi_init);


#endif /* BSP_USING_SPI1 || BSP_USING_SPI2 || BSP_USING_SPI3 || BSP_USING_SPI4 || BSP_USING_SPI5 || BSP_USING_SPI6 || BSP_USING_SPI7 */
#endif /* BSP_USING_SPI */

