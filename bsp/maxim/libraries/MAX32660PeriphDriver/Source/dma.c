/* *****************************************************************************
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
 * $Date: 2019-07-01 11:06:19 -0500 (Mon, 01 Jul 2019) $
 * $Revision: 44383 $
 *
 **************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include "mxc_config.h"
#include "mxc_assert.h"
#include "mxc_lock.h"
#include "mxc_sys.h"
#include "dma.h"

/*
 * Structure type
 */
typedef struct {
    unsigned int valid;         /* Flag to invalidate this resource */
    unsigned int instance;      /* Hardware instance of this DMA controller */
    unsigned int id;            /* Channel ID, which matches the index into the underlying hardware */
    mxc_dma_ch_regs_t *regs;    /* Pointer to the registers for this channel */
    void (*cb)(int, int);       /* Pointer to a callback function type */
} dma_channel_t;

#define CHECK_HANDLE(x) ((x >= 0) && (x < MXC_DMA_CHANNELS) && (dma_resource[x].valid))

/* DMA driver must be initialized once before use, and may not be initialized again without shutdown, as it is a shared resource */
static unsigned int dma_initialized = 0;

static dma_channel_t dma_resource[MXC_DMA_CHANNELS];

static uint32_t dma_lock;

/* Initialize DMA to known state */
int DMA_Init(void)
{
    int i;
    
    if (dma_initialized) {
        return E_BAD_STATE;
    }
    
    /* Initialize any system-level DMA settings */
    SYS_DMA_Init();
    
    /* Initialize mutex */
    mxc_free_lock(&dma_lock);
    if (mxc_get_lock(&dma_lock, 1) != E_NO_ERROR) {
        return E_BUSY;
    }
    
    /* Ensure all channels are disabled at start, clear flags, init handles */
    MXC_DMA->cn = 0;
    for (i = 0; i < MXC_DMA_CHANNELS; i++) {
        dma_resource[i].valid = 0;
        dma_resource[i].instance = 0;
        dma_resource[i].id = i;
        dma_resource[i].regs = (mxc_dma_ch_regs_t *)&MXC_DMA->ch[i];
        dma_resource[i].regs->cfg = 0;
        dma_resource[i].regs->st = dma_resource[i].regs->st;
        
        dma_resource[i].cb = NULL;
    }
    dma_initialized++;
    mxc_free_lock(&dma_lock);
    
    return E_NO_ERROR;
}

/* Shut down DMA in an orderly manner, informing clients that their requests did not complete */
int DMA_Shutdown(void)
{
    int i;
    
    if (!dma_initialized) {
        /* Never initialized, so shutdown is not appropriate */
        return E_BUSY;
    }
    
    if (mxc_get_lock(&dma_lock, 1) != E_NO_ERROR) {
        return E_BUSY;
    }
    
    /* Prevent any new resource allocation by this API */
    dma_initialized = 0;
    /* Disable interrupts, preventing future callbacks */
    MXC_DMA->cn = 0;
    
    /* For each channel:
     *  - invalidate the handles held by clients
     *  - stop any transfer in progress
     */
    for (i = 0; i < MXC_DMA_CHANNELS; i++) {
        dma_resource[i].regs->cfg = 0;
        if (dma_resource[i].valid) {
            dma_resource[i].valid = 0;
            if (dma_resource[i].cb != NULL) {
                dma_resource[i].cb(i, E_SHUTDOWN);
            }
        }
    }
    
    /* Disable any system-level DMA settings */
    SYS_DMA_Shutdown();
    
    mxc_free_lock(&dma_lock);
    
    return E_NO_ERROR;
}

/* Request DMA channel */
/* Once "owned", this channel may be used directly via the DMA_GetCHRegs(ch) pointer, or */
/* configured via the API functions */
int DMA_AcquireChannel(void)
{
    int i, channel;
    
    /* Check for initialization */
    if (!dma_initialized) {
        return E_BAD_STATE;
    }
    
    /* If DMA is locked return busy */
    if (mxc_get_lock(&dma_lock, 1) != E_NO_ERROR) {
        return E_BUSY;
    }
    
    /* Default is no channel available */
    channel = E_NONE_AVAIL;
    if (dma_initialized) {
        for (i = 0; i < MXC_DMA_CHANNELS; i++) {
            if (!dma_resource[i].valid) {
                /* Found one */
                channel = i;
                dma_resource[i].valid = 1;
                dma_resource[i].regs->cfg = 0;
                dma_resource[i].regs->cnt_rld = 0; /* Used by DMA_Start() to conditionally set RLDEN */
                break;
            }
        }
    }
    mxc_free_lock(&dma_lock);
    
    return channel;
}

/* Release DMA channel */
/* Callbacks will not be called */
int DMA_ReleaseChannel(int ch)
{
    if (CHECK_HANDLE(ch)) {
        if (mxc_get_lock(&dma_lock, 1) != E_NO_ERROR) {
            return E_BUSY;
        }
        dma_resource[ch].valid = 0;
        dma_resource[ch].regs->cfg = 0;
        dma_resource[ch].regs->st = dma_resource[ch].regs->st;
        mxc_free_lock(&dma_lock);
    } else {
        return E_BAD_PARAM;
    }
    
    return E_NO_ERROR;
}

/* Channel configuration */
int DMA_ConfigChannel(int ch,
                      dma_priority_t prio,
                      dma_reqsel_t reqsel, unsigned int reqwait_en,
                      dma_timeout_t tosel, dma_prescale_t pssel,
                      dma_width_t srcwd, unsigned int srcinc_en,
                      dma_width_t dstwd, unsigned int dstinc_en,
                      unsigned int burst_size, unsigned int chdis_inten,
                      unsigned int ctz_inten)
{
    if (CHECK_HANDLE(ch) && (burst_size > 0)) {
        /* Designed to be safe, not speedy. Should not be called often */
        dma_resource[ch].regs->cfg =
            ((reqwait_en ? MXC_F_DMA_CFG_REQWAIT : 0) |
             (srcinc_en ? MXC_F_DMA_CFG_SRCINC : 0)   |
             (dstinc_en ? MXC_F_DMA_CFG_DSTINC : 0)   |
             (chdis_inten ? MXC_F_DMA_CFG_CHDIEN : 0) |
             (ctz_inten ? MXC_F_DMA_CFG_CTZIEN : 0)   |
             prio |reqsel | tosel | pssel | 
             (srcwd << MXC_F_DMA_CFG_SRCWD_POS) |
             (dstwd << MXC_F_DMA_CFG_DSTWD_POS) |
             (((burst_size - 1) << MXC_F_DMA_CFG_BRST_POS) & MXC_F_DMA_CFG_BRST));
    } else {
        return E_BAD_PARAM;
    }
    
    return E_NO_ERROR;
}

/*
 * DMA request selects for peripherals will override either src_addr or dst_addr.
 * In these cases, the overridden address is a don't care and may be 0.
 */
int DMA_SetSrcDstCnt(int ch,
                     void *src_addr,
                     void *dst_addr,
                     unsigned int count)
{
    if (CHECK_HANDLE(ch)) {
        dma_resource[ch].regs->src = (unsigned int)src_addr;
        dma_resource[ch].regs->dst = (unsigned int)dst_addr;
        dma_resource[ch].regs->cnt = count;
    } else {
        return E_BAD_PARAM;
    }
    
    return E_NO_ERROR;
}

/* Must set en_reload == 1 to have any effect */
int DMA_SetReload(int ch,
                  void *src_addr_reload,
                  void *dst_addr_reload,
                  unsigned int count_reload)
{
    if (CHECK_HANDLE(ch)) {
        dma_resource[ch].regs->src_rld = (unsigned int)src_addr_reload;
        dma_resource[ch].regs->dst_rld = (unsigned int)dst_addr_reload;
        if (dma_resource[ch].regs->cfg & MXC_F_DMA_CFG_CHEN) {
            /* If channel is already running, set RLDEN to enable next reload */
            dma_resource[ch].regs->cnt_rld = MXC_F_DMA_CNT_RLD_RLDEN | count_reload;
        } else {
            /* Otherwise, this is the initial setup, so DMA_Start() will handle setting that bit */
            dma_resource[ch].regs->cnt_rld = count_reload;
        }
    } else {
        return E_BAD_PARAM;
    }
    
    return E_NO_ERROR;
}

int DMA_SetCallback(int ch, void (*callback)(int, int))
{
    if (CHECK_HANDLE(ch)) {
        /* Callback for interrupt handler, no checking is done, as NULL is valid for (none)  */
        dma_resource[ch].cb = callback;
    } else {
        return E_BAD_PARAM;
    }
    
    return E_NO_ERROR;
}

/* Interrupt enable/disable */
int DMA_EnableInterrupt(int ch)
{
    if (CHECK_HANDLE(ch)) {
        MXC_DMA->cn |= (1 << ch);
    } else {
        return E_BAD_PARAM;
    }
    
    return E_NO_ERROR;
}

int DMA_DisableInterrupt(int ch)
{
    if (CHECK_HANDLE(ch)) {
        MXC_DMA->cn &= ~(1 << ch);
    } else {
        return E_BAD_PARAM;
    }
    
    return E_NO_ERROR;
}

/* Channel interrupt flags */
int DMA_GetFlags(int ch, unsigned int *fl)
{
    if (CHECK_HANDLE(ch) && fl) {
        *fl = dma_resource[ch].regs->st;
    } else {
        return E_BAD_PARAM;
    }
    
    return E_NO_ERROR;
}

int DMA_ClearFlags(int ch)
{
    if (CHECK_HANDLE(ch)) {
        dma_resource[ch].regs->st = dma_resource[ch].regs->st;
    } else {
        return E_BAD_PARAM;
    }
    
    return E_NO_ERROR;
}

/* Start channel */
int DMA_Start(int ch)
{
    if (CHECK_HANDLE(ch)) {
        DMA_ClearFlags(ch);
        if (dma_resource[ch].regs->cnt_rld) {
            dma_resource[ch].regs->cfg |= (MXC_F_DMA_CFG_CHEN | MXC_F_DMA_CFG_RLDEN);
        } else {
            dma_resource[ch].regs->cfg |= MXC_F_DMA_CFG_CHEN;
        }
    } else {
        return E_BAD_PARAM;
    }
    
    return E_NO_ERROR;
}

/* Stop channel */
int DMA_Stop(int ch)
{
    if (CHECK_HANDLE(ch)) {
        dma_resource[ch].regs->cfg &= ~MXC_F_DMA_CFG_CHEN;
    } else {
        return E_BAD_PARAM;
    }
    
    return E_NO_ERROR;
}

/* Get pointer to registers, for advanced users */
mxc_dma_ch_regs_t *DMA_GetCHRegs(int ch)
{
    if (CHECK_HANDLE(ch)) {
        return dma_resource[ch].regs;
    } else {
        return NULL;
    }
}

/* */
void DMA_Handler(int ch)
{
    /* Do callback, if enabled */
    if (dma_resource[ch].cb != NULL) {
        dma_resource[ch].cb(ch, E_NO_ERROR);
    }
    DMA_ClearFlags(ch);
}
