/**
 * @file    i2s.c
 * @brief   Inter-Integrated Sound (I2S) driver implementation.
 */

/* ****************************************************************************
 * Copyright (C) 2017 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2018-12-18 15:37:22 -0600 (Tue, 18 Dec 2018) $
 * $Revision: 40072 $
 *
 *************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include "mxc_config.h"
#include "mxc_assert.h"
#include "mxc_lock.h"
#include "mxc_sys.h"
#include "dma.h"
#include "i2s.h"

#define I2S_CHANNELS 2
#define I2S_WIDTH    16

int dma_channel = -1;

int I2S_Init(const i2s_cfg_t *cfg, void (*dma_ctz_cb)(int, int), const sys_cfg_i2s_t* sys_cfg_i2s)
{
    unsigned int i2s_clk, baud;
    uint16_t clocks;
    uint8_t ctz_en;
    int err;

    SYS_I2S_Init(sys_cfg_i2s);

    /* Setup SPI_MSS as master, mode 0, 16 bit transfers as I2S Requires */
    MXC_SPIMSS->ctrl = MXC_F_SPIMSS_CTRL_MMEN;
    MXC_SPIMSS->mod = MXC_V_SPIMSS_MOD_NUMBITS_BITS16 | MXC_F_SPIMSS_MOD_SSIO;
    MXC_SPIMSS->dma = MXC_S_SPIMSS_DMA_TX_FIFO_LEVEL_ENTRIES8;

    /* Setup I2S register from i2s_cfg_t */
    MXC_SPIMSS->i2s_ctrl =  cfg->left_justify << MXC_F_SPIMSS_I2S_CTRL_I2S_LJ_POS |
                            cfg->mono_audio << MXC_F_SPIMSS_I2S_CTRL_I2S_MONO_POS;

    /* Determine divisor for baud rate generator */
    baud = cfg->sample_rate*I2S_CHANNELS*I2S_WIDTH;

    i2s_clk = SYS_I2S_GetFreq(MXC_SPIMSS);

    if (i2s_clk/4 < baud) {
        return E_BAD_PARAM;
    }

    clocks = i2s_clk / (2*baud);
    MXC_SPIMSS->brg = clocks;

    /* Prepare SPIMSS DMA register for DMA setup */
    if (dma_ctz_cb == NULL) {
        ctz_en = 0;
    } else {
        ctz_en = 1;
    }

    /* Initialize DMA */
    if (cfg->audio_direction % 2) {
        MXC_SPIMSS->dma |= MXC_F_SPIMSS_DMA_TX_DMA_EN | MXC_F_SPIMSS_DMA_TX_FIFO_CLEAR;
        if ((err = DMA_Init()) != E_NO_ERROR) {
            if (err != E_BAD_STATE) {
                return err;
            }
        }

        if ((err = DMA_AcquireChannel()) < 0) {
            return err;
        }

        dma_channel = err;

        DMA_ConfigChannel(dma_channel, DMA_PRIO_MEDHIGH,
              sys_cfg_i2s->dma_reqsel_tx, 1, DMA_TIMEOUT_512_CLK,
              DMA_PRESCALE_DIV64K, DMA_WIDTH_HALFWORD, 1,
              DMA_WIDTH_HALFWORD, 0, 16, 0, ctz_en);

        if (ctz_en) {
            DMA_SetCallback(dma_channel, dma_ctz_cb);
            DMA_EnableInterrupt(dma_channel);
        }
    }
    if (cfg->audio_direction / 2) {
        MXC_SPIMSS->dma = MXC_F_SPIMSS_DMA_RX_DMA_EN | MXC_F_SPIMSS_DMA_RX_FIFO_CLEAR;
        if ((err = DMA_Init()) != E_NO_ERROR) {
            if (err != E_BAD_STATE) {    //DMA already initialized
                return err;
            }
        }

        if ((err = DMA_AcquireChannel()) < 0) {
            return err;
        }

        dma_channel = err;

        DMA_ConfigChannel(dma_channel, DMA_PRIO_MEDHIGH,
                        sys_cfg_i2s->dma_reqsel_rx, 1, DMA_TIMEOUT_512_CLK,
                        DMA_PRESCALE_DIV64K, DMA_WIDTH_HALFWORD, 0,
                        DMA_WIDTH_HALFWORD, 1, 8, 0, ctz_en);

        if (ctz_en) {
            DMA_SetCallback(dma_channel, dma_ctz_cb);
            DMA_EnableInterrupt(dma_channel);
        }
    }

    I2S_DMA_SetAddrCnt(cfg->dma_src_addr, cfg->dma_dst_addr, cfg->dma_cnt);
    if (cfg->dma_reload_en) {
        I2S_DMA_SetReload(cfg->dma_src_addr, cfg->dma_dst_addr, cfg->dma_cnt);
    }

    if (cfg->start_immediately) {
        return I2S_Start();
    }
    return E_NO_ERROR;
}

int I2S_Shutdown(void)
{
    MXC_SPIMSS->ctrl = 0;
    MXC_SPIMSS->i2s_ctrl = 0;
    MXC_SPIMSS->brg = 0;
    MXC_SPIMSS->mod = 0;
    MXC_SPIMSS->dma = 0;
    SYS_I2S_Shutdown();
    return DMA_ReleaseChannel(dma_channel);
}

int I2S_Mute(void)
{
    MXC_SPIMSS->i2s_ctrl |= MXC_F_SPIMSS_I2S_CTRL_I2S_MUTE;
    return E_NO_ERROR;
}

int I2S_Unmute(void)
{
    MXC_SPIMSS->i2s_ctrl &= ~MXC_F_SPIMSS_I2S_CTRL_I2S_MUTE;
    return E_NO_ERROR;
}

int I2S_Pause(void)
{
    MXC_SPIMSS->i2s_ctrl |= MXC_F_SPIMSS_I2S_CTRL_I2S_PAUSE;
    return E_NO_ERROR;
}

int I2S_Unpause(void)
{
    MXC_SPIMSS->i2s_ctrl &= ~MXC_F_SPIMSS_I2S_CTRL_I2S_PAUSE;
    return E_NO_ERROR;
}

int I2S_Stop(void)
{
    MXC_SPIMSS->ctrl &= ~MXC_F_SPIMSS_CTRL_SPIEN;
    MXC_SPIMSS->i2s_ctrl &= ~MXC_F_SPIMSS_I2S_CTRL_I2S_EN;
    return DMA_Stop(dma_channel);
}

int I2S_Start(void)
{
    MXC_SPIMSS->ctrl |= MXC_F_SPIMSS_CTRL_SPIEN;
    MXC_SPIMSS->i2s_ctrl |= MXC_F_SPIMSS_I2S_CTRL_I2S_EN;
    return DMA_Start(dma_channel);
}

int I2S_DMA_ClearFlags(void)
{
    return DMA_ClearFlags(dma_channel);
}

int I2S_DMA_SetAddrCnt(void *src_addr, void *dst_addr, unsigned int count)
{
    return DMA_SetSrcDstCnt(dma_channel, src_addr, dst_addr, count);
}

int I2S_DMA_SetReload(void *src_addr, void *dst_addr, unsigned int count)
{
    return DMA_SetReload(dma_channel, src_addr, dst_addr, count);
}
