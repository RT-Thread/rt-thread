/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <rtdef.h>
#include <rtatomic.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <riscv_io.h>
#include <mmu.h>
#include <cache.h>
#include <page.h>
#include "board.h"
#include "ioremap.h"
#include "drv_hardlock.h"
#include "drv_pdma.h"
#include <rtdbg.h>

#define DBG_TAG "drv_pdma"
#ifdef RT_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_WARNING
#endif
#define DBG_COLOR

/**
 * @brief PDMA controller instance initialization
 */
static pdma_controller_t pdma_ctrl = {0};

#define PDMA_CH_MENUCONFIG_ENABLED(ch) \
    (((ch) >= 0 && (ch) < PDMA_CH_MAX) ? \
        (pdma_ctrl.chan[(ch)].menuconfig_enabled) : \
        (RT_FALSE))

/**
 * @brief Acquire PDMA hardware lock
 * @note Busy-waits until lock is acquired
 */
#define PDMA_LOCK()   while (kd_hardlock_lock(pdma_ctrl.hardlock) != 0)

/**
 * @brief Release PDMA hardware lock
 */
#define PDMA_UNLOCK() kd_hardlock_unlock(pdma_ctrl.hardlock)

/*--------------------- Channel Enable Control ---------------------*/
/**
 * @brief Enable specific PDMA channel
 */
#define PDMA_CH_ENABLE(ch) \
    (pdma_write32(&pdma_ctrl.reg->pdma_ch_en, pdma_read32(&pdma_ctrl.reg->pdma_ch_en) | (1U << (ch))))

/**
 * @brief Disable specific PDMA channel
 */
#define PDMA_CH_DISABLE(ch) \
    (pdma_write32(&pdma_ctrl.reg->pdma_ch_en, pdma_read32(&pdma_ctrl.reg->pdma_ch_en) & ~(1U << (ch))))

/**
 * @brief Check if PDMA channel is enabled
 */
#define PDMA_CH_IS_ENABLED(ch) \
    (pdma_read32(&pdma_ctrl.reg->pdma_ch_en) & (1U << (ch)))


/*--------------------- Interrupt Control ---------------------*/
/**
 * @brief Enable interrupts for specific PDMA channel
 */
#define PDMA_CH_INT_ENABLE(ch, mask) \
    (pdma_write32(&pdma_ctrl.reg->dma_int_mask, pdma_read32(&pdma_ctrl.reg->dma_int_mask) & ~((mask) << (ch))))

/**
 * @brief Disable interrupts for specific PDMA channel
 */
#define PDMA_CH_INT_DISABLE(ch, mask) \
    (pdma_write32(&pdma_ctrl.reg->dma_int_mask, pdma_read32(&pdma_ctrl.reg->dma_int_mask) | ((mask) << (ch))))

/**
 * @brief Disable all interrupts for specific PDMA channel
 */
#define PDMA_CH_INT_DISABLE_ALL(ch) \
    PDMA_CH_INT_DISABLE(ch, PDMA_ALL_INTS)

/**
 * @brief Clear interrupt status for specific PDMA channel
 */
#define PDMA_CH_INT_CLEAR(ch, intr) \
    (pdma_write32(&pdma_ctrl.reg->dma_int_stat, (intr) << (ch)))

/**
 * @brief Clear all interrupt status for specific PDMA channel
 */
#define PDMA_CH_INT_CLEAR_ALL(ch) \
    PDMA_CH_INT_CLEAR(ch, PDMA_ALL_INTS)

/**
 * @brief Check if interrupt is triggered for specific PDMA channel
 */
#define PDMA_CH_INT_IS_TRIGGERED(ch, intr) \
    (pdma_read32(&pdma_ctrl.reg->dma_int_stat) & ((intr) << (ch)))


/*--------------------- Status Check ---------------------*/
/**
 * @brief Check if PDMA channel is busy
 */
#define PDMA_CH_IS_BUSY(ch) \
    (pdma_read32(&pdma_ctrl.reg->pdma_ch_reg[ch].ch_status) & PDMA_STATE_BUSY)

/**
 * @brief Check if PDMA channel is paused
 */
#define PDMA_CH_IS_PAUSED(ch) \
    (pdma_read32(&pdma_ctrl.reg->pdma_ch_reg[ch].ch_status) & PDMA_STATE_PAUSE)


/*--------------------- Data Transfer Control ---------------------*/
/**
 * @brief Start PDMA transfer on specific channel
 */
#define PDMA_CH_START(ch) \
    (pdma_write32(&pdma_ctrl.reg->pdma_ch_reg[ch].ch_ctl, PDMA_CMD_START))

/**
 * @brief Stop PDMA transfer on specific channel
 */
#define PDMA_CH_STOP(ch) \
    (pdma_write32(&pdma_ctrl.reg->pdma_ch_reg[ch].ch_ctl, PDMA_CMD_STOP))

/**
 * @brief Resume paused PDMA transfer on specific channel
 */
#define PDMA_CH_RESUME(ch) \
    (pdma_write32(&pdma_ctrl.reg->pdma_ch_reg[ch].ch_ctl, PDMA_CMD_RESUME))


static void  _k230_pdma_llt_free(rt_uint8_t ch);
static rt_uint32_t *_k230_pdma_llt_cal(rt_uint8_t ch, usr_pdma_cfg_t *pdma_cfg);
static rt_err_t _k230_pdma_safe_stop(rt_uint8_t ch, rt_uint32_t timeout_ms);

/**
 * @brief Set callback function for specified PDMA channel
 * @param ch PDMA channel number
 * @param func Callback function pointer
 * @return RT_EOK on success, -RT_EINVAL on invalid parameters
 */
rt_err_t k230_pdma_set_callback(rt_uint8_t ch, k230_pdma_callback_t func)
{
    /* Validate channel and callback function */
    if (!PDMA_CH_MENUCONFIG_ENABLED(ch) || func == RT_NULL)
    {
        return -RT_EINVAL;
    }

    /*
     * Safely set callback function by masking interrupts during update
     * This prevents potential race conditions with DMA interrupts
     */
    rt_hw_interrupt_mask(pdma_ctrl.chan[ch].irq_num);
    pdma_ctrl.chan[ch].cb.callback = func;
    rt_hw_interrupt_umask(pdma_ctrl.chan[ch].irq_num);

    return RT_EOK;
}

/**
 * @brief Request an available PDMA channel
 * @param ch [out] Pointer to store the allocated channel number
 * @return rt_err_t RT_EOK if success, error code otherwise
 */
rt_err_t k230_pdma_request_channel(rt_uint8_t *ch)
{
    if (ch == RT_NULL)
    {
        LOG_E("PDMA: Invalid channel pointer");
        return -RT_EINVAL;
    }

    rt_base_t level;
    level = rt_hw_interrupt_disable();
    PDMA_LOCK();

    for (rt_uint8_t i = 0; i < PDMA_CH_MAX; i++)
    {
        if (!PDMA_CH_MENUCONFIG_ENABLED(i))
        {
            LOG_D("PDMA: Channel %d not enabled in menuconfig", i);
            continue;
        }

        if (PDMA_CH_IS_ENABLED(i))
        {
            LOG_D("PDMA: Channel %d already enabled", i);
            continue;
        }

        PDMA_CH_ENABLE(i);
        LOG_D("PDMA: Trying channel %d", i);

        if (!PDMA_CH_IS_ENABLED(i))
        {
            LOG_W("PDMA: Channel %d failed to enable - possible hardware issue", i);
            continue;
        }

        if (PDMA_CH_IS_BUSY(i))
        {
            LOG_W("PDMA: Channel %d is busy, disabling", i);
            PDMA_CH_DISABLE(i);
            continue;
        }

        *ch = i;
        PDMA_CH_INT_DISABLE_ALL(i);

        PDMA_UNLOCK();
        rt_hw_interrupt_enable(level);

        pdma_ctrl.chan[i].cb.callback = RT_NULL;
        pdma_ctrl.chan[i].is_hw_configured = RT_FALSE;
        pdma_ctrl.chan[i].llt_va =RT_NULL;
        pdma_ctrl.chan[i].page_size = 0;
        rt_hw_interrupt_umask(pdma_ctrl.chan[i].irq_num);

        LOG_I("PDMA: Allocated channel %d", i);
        return RT_EOK;
    }

    *ch = PDMA_CH_MAX;
    PDMA_UNLOCK();
    rt_hw_interrupt_enable(level);

    LOG_E("PDMA: No available channel found");
    return -RT_EBUSY;
}

/**
 * @brief Release an allocated PDMA channel
 * @param ch Channel number to release
 * @return rt_err_t RT_EOK if success, error code otherwise
 */
rt_err_t k230_pdma_release_channel(rt_uint8_t ch)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    PDMA_LOCK();

    /* Validate channel configuration and status */
    if (!PDMA_CH_MENUCONFIG_ENABLED(ch) || !PDMA_CH_IS_ENABLED(ch))
    {
        PDMA_UNLOCK();
        rt_hw_interrupt_enable(level);
        LOG_E("PDMA: Invalid channel %d to release", ch);
        return -RT_EINVAL;
    }

    PDMA_UNLOCK();
    rt_hw_interrupt_enable(level);

    rt_hw_interrupt_mask(pdma_ctrl.chan[ch].irq_num);

    /* Clear any registered callback */
    pdma_ctrl.chan[ch].cb.callback = RT_NULL;

    /* Safely stop DMA operation and release resources */
    rt_err_t err = _k230_pdma_safe_stop(ch, PDMA_MAX_WAIT_MS);
    if (err != RT_EOK)
    {
        LOG_E("PDMA: Failed to safely stop channel %d (err:%d)", ch, err);
        return err;
    }

    pdma_ctrl.chan[ch].is_hw_configured = RT_FALSE;

    /* Disable the channel */
    level = rt_hw_interrupt_disable();
    PDMA_LOCK();
    PDMA_CH_DISABLE(ch);
    PDMA_UNLOCK();
    rt_hw_interrupt_enable(level);

    LOG_I("PDMA: Channel %d released successfully", ch);
    return RT_EOK;
}

/**
 * @brief Start a PDMA channel operation
 * @param ch The channel number to start
 * @return RT_EOK on success, error code on failure
 */
rt_err_t k230_pdma_start(rt_uint8_t ch)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    PDMA_LOCK();

    LOG_D("Starting PDMA channel %d", ch);

    /* Basic channel validation */
    if (!PDMA_CH_MENUCONFIG_ENABLED(ch) || !PDMA_CH_IS_ENABLED(ch))
    {
        LOG_E("Channel %d not enabled in menuconfig or not enabled", ch);
        PDMA_UNLOCK();
        rt_hw_interrupt_enable(level);
        return -RT_EINVAL;
    }

    /* Only start DMA if channel is properly configured to prevent unclosable channel */
    if (pdma_ctrl.chan[ch].is_hw_configured == RT_FALSE)
    {
        LOG_E("Channel %d not properly configured", ch);
        PDMA_UNLOCK();
        rt_hw_interrupt_enable(level);
        return -RT_ERROR;
    }

    /* Enable completion, pause and timeout interrupts */
    PDMA_CH_INT_ENABLE(ch, PDMA_PDONE_INT | PDMA_PPAUSE_INT | PDMA_PTOUT_INT);

    PDMA_UNLOCK();
    rt_hw_interrupt_enable(level);

    /* Start the channel operation */
    PDMA_CH_START(ch);
    LOG_I("Successfully started PDMA channel %d", ch);

    /* Clear configuration flag */
    pdma_ctrl.chan[ch].is_hw_configured == RT_FALSE;

    return RT_EOK;
}

/**
 * @brief Stop an active PDMA channel operation
 * @param ch The channel number to stop
 * @return RT_EOK on success, error code on failure
 */
rt_err_t k230_pdma_stop(rt_uint8_t ch)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    PDMA_LOCK();

    LOG_D("Attempting to stop PDMA channel %d", ch);

    /* Basic channel validation */
    if (!PDMA_CH_MENUCONFIG_ENABLED(ch) || !PDMA_CH_IS_ENABLED(ch))
    {
        LOG_E("Channel %d not enabled in menuconfig or not enabled", ch);
        PDMA_UNLOCK();
        rt_hw_interrupt_enable(level);
        return -RT_EINVAL;
    }

    PDMA_UNLOCK();
    rt_hw_interrupt_enable(level);

    /* Safely stop the channel operation */
    rt_err_t ret = _k230_pdma_safe_stop(ch, PDMA_MAX_WAIT_MS);
    if (ret == RT_EOK)
    {
        LOG_I("Successfully stopped PDMA channel %d", ch);
    }
    else
    {
        LOG_E("Failed to stop PDMA channel %d (error: %d)", ch, ret);
    }

    return ret;
}

/**
 * @brief Convert PDMA channel configuration structure to register value
 * @param cfg Pointer to the channel configuration structure
 * @return 32-bit register value representing the configuration
 */
static rt_uint32_t _k230_pdma_ch_cfg_to_reg(const pdma_ch_cfg_t *cfg)
{
    rt_uint32_t reg = 0;

    /* Source type configuration */
    reg |= (cfg->ch_src_type & 0x1) << 0;

    /* Device horizontal size */
    reg |= (cfg->ch_dev_hsize & 0x3) << 1;

    /* Data endianness configuration */
    reg |= (cfg->ch_dat_endian & 0x3) << 4;

    /* Device burst length */
    reg |= (cfg->ch_dev_blen & 0xF) << 8;

    /* Channel priority */
    reg |= (cfg->ch_priority & 0xF) << 12;

    /* Device timeout */
    reg |= (cfg->ch_dev_tout & 0xFFF) << 16;

    return reg;
}

/**
 * @brief Configure PDMA channel with user settings
 * @param ch Channel number to configure
 * @param ucfg Pointer to user configuration structure
 * @return RT_EOK on success, error code on failure
 */
static rt_err_t _k230_pdma_config(rt_uint8_t ch, usr_pdma_cfg_t *ucfg)
{
    volatile rt_uint32_t *ch_cfg = (volatile rt_uint32_t*)(&(pdma_ctrl.reg->pdma_ch_reg[ch].ch_cfg));

    LOG_D("Configuring PDMA channel %d", ch);

    /* Convert configuration to register format */
    rt_uint32_t reg_val = _k230_pdma_ch_cfg_to_reg(&ucfg->pdma_ch_cfg);

    /* Write configuration to hardware registers */
    pdma_write32(ch_cfg, reg_val);
    pdma_write32(&(pdma_ctrl.reg->ch_peri_dev_sel[ch]), ucfg->device);

    LOG_I("PDMA channel %d configured successfully", ch);
    return RT_EOK;
}

/**
 * @brief Validate user configuration parameters
 * @param ucfg Pointer to user configuration structure
 * @return RT_EOK if valid, error code if invalid
 */
static rt_err_t _k230_ucfg_check(usr_pdma_cfg_t *ucfg)
{
    /* Parameter NULL check */
    if (ucfg == RT_NULL)
    {
        LOG_E("Configuration pointer is NULL");
        return -RT_EINVAL;
    }

    /* Device range validation */
    if ((ucfg->device > PDM_IN) || (ucfg->device < UART0_TX))
    {
        LOG_E("Invalid device selection: %d", ucfg->device);
        return -RT_EINVAL;
    }

    /* Validate peripheral data word width */
    if ((ucfg->pdma_ch_cfg.ch_dev_hsize > PSBYTE4) ||
        (ucfg->pdma_ch_cfg.ch_dev_hsize < PSBYTE1))
    {
        LOG_E("Invalid peripheral data width: %d (1-4 bytes supported)",
            ucfg->pdma_ch_cfg.ch_dev_hsize);
        return -RT_EINVAL;
    }

    /* Address and size alignment check */
    if (((rt_uintptr_t)ucfg->src_addr % 4) ||
        ((rt_uintptr_t)ucfg->dst_addr % 4) ||
        (ucfg->line_size % 4))
    {
        LOG_E("Alignment error - src: 0x%08X, dst: 0x%08X, size: %d",
              ucfg->src_addr, ucfg->dst_addr, ucfg->line_size);
        return -RT_EINVAL;
    }

    LOG_D("User configuration validation passed");
    return RT_EOK;
}

/**
 * @brief Configure a PDMA channel with user settings
 * @param ch Channel number to configure (0-PDMA_MAX_CHANNELS-1)
 * @param ucfg Pointer to user configuration structure
 * @return RT_EOK on success, error code on failure
 */
rt_err_t k230_pdma_config(rt_uint8_t ch, usr_pdma_cfg_t *ucfg)
{
    rt_err_t err;
    rt_base_t level;

    LOG_D("[CH%d] Starting PDMA configuration", ch);

    /* Enter critical section */
    level = rt_hw_interrupt_disable();
    PDMA_LOCK();

    /* Channel availability check */
    if (!PDMA_CH_MENUCONFIG_ENABLED(ch) || !PDMA_CH_IS_ENABLED(ch))
    {
        LOG_E("[CH%d] Channel not enabled in menuconfig or hardware", ch);
        PDMA_UNLOCK();
        rt_hw_interrupt_enable(level);
        return -RT_EINVAL;
    }

    PDMA_UNLOCK();
    rt_hw_interrupt_enable(level);

    /* Validate user configuration */
    err = _k230_ucfg_check(ucfg);
    if (err != RT_EOK)
    {
        LOG_E("[CH%d] Configuration validation failed", ch);
        return err;
    }

    /* Safely stop channel if active */
    err = _k230_pdma_safe_stop(ch, PDMA_MAX_WAIT_MS);
    if (err != RT_EOK)
    {
        LOG_E("[CH%d] Failed to stop channel (err: %d)", ch, err);
        return err;
    }

    /* Apply hardware configuration */
    _k230_pdma_config(ch, ucfg);
    LOG_D("[CH%d] Hardware registers configured", ch);

    /* Build DMA transfer linked list */
    rt_uint32_t* llt_saddr = _k230_pdma_llt_cal(ch, ucfg);
    if (llt_saddr == RT_NULL)
    {
        LOG_E("[CH%d] Failed to allocate memory for linked list", ch);
        return -RT_ENOMEM;
    }

    /* Program linked list starting address */
    pdma_write32(&(pdma_ctrl.reg->pdma_ch_reg[ch].ch_llt_saddr), (rt_uint32_t)(rt_uintptr_t)llt_saddr);
    LOG_D("[CH%d] Linked list programmed (addr: 0x%p)", ch, llt_saddr);

    /* Mark channel as configured */
    pdma_ctrl.chan[ch].is_hw_configured = RT_TRUE;
    LOG_I("[CH%d] Configuration completed successfully", ch);

    return RT_EOK;
}

/**
 * @brief Safely stop a PDMA channel operation
 * @param ch Channel number to stop (0-PDMA_MAX_CHANNELS-1)
 * @param timeout_ms Maximum wait time in milliseconds (0 for no timeout)
 * @return RT_EOK on success, -RT_ETIMEOUT on timeout, other errors
 */
static rt_err_t _k230_pdma_safe_stop(rt_uint8_t ch, rt_uint32_t timeout_ms)
{
    rt_err_t err = RT_EOK;
    rt_tick_t start_tick;

    LOG_D("[CH%d] Attempting safe stop (timeout: %dms)", ch, timeout_ms);

    /* Immediately request channel stop */
    PDMA_CH_STOP(ch);

    /* Wait for channel to become inactive */
    start_tick = rt_tick_get();
    while (PDMA_CH_IS_BUSY(ch))
    {
        /* Check for timeout if specified */
        if (timeout_ms > 0 &&
            (rt_tick_get_delta(start_tick) >= rt_tick_from_millisecond(timeout_ms)))
        {
            LOG_E("[CH%d] Stop operation timed out", ch);
            return -RT_ETIMEOUT;
        }

        rt_thread_mdelay(1);
    }

    /* Enter critical section for register cleanup */
    rt_base_t level = rt_hw_interrupt_disable();
    PDMA_LOCK();

    /* Clear and disable all interrupts */
    PDMA_CH_INT_CLEAR_ALL(ch);
    PDMA_CH_INT_DISABLE_ALL(ch);
    LOG_D("[CH%d] Interrupts cleared and disabled", ch);

    PDMA_UNLOCK();
    rt_hw_interrupt_enable(level);

    /* Free linked list memory */
    _k230_pdma_llt_free(ch);
    LOG_D("[CH%d] Linked list memory freed", ch);

    pdma_ctrl.chan[ch].is_hw_configured = RT_FALSE;

    LOG_I("[CH%d] Successfully stopped", ch);
    return RT_EOK;
}

/**
 * @brief Calculate and allocate PDMA linked list table (LLT)
 * @param ch Channel number (0-PDMA_MAX_CHANNELS-1)
 * @param pdma_cfg Pointer to PDMA configuration structure
 * @return Physical address of LLT on success, RT_NULL on failure
 */
static rt_uint32_t *_k230_pdma_llt_cal(rt_uint8_t ch, usr_pdma_cfg_t *pdma_cfg)
{
    rt_int32_t i;
    rt_uint32_t list_num;
    pdma_llt_t *llt_list;
    rt_bool_t mem_to_dev;

    LOG_D("[CH%d] Calculating LLT parameters", ch);

    /* Calculate number of LLT entries needed */
    list_num = (pdma_cfg->line_size - 1) / PDMA_MAX_LINE_SIZE + 1;
    LOG_D("[CH%d] Line size: %d, requires %d LLT entries",
          ch, pdma_cfg->line_size, list_num);

    /* Determine transfer direction */
    mem_to_dev = (pdma_cfg->pdma_ch_cfg.ch_src_type == CONTINUE) ? RT_TRUE : RT_FALSE;
    LOG_D("[CH%d] Transfer direction: %s", ch, mem_to_dev ? "Memory->Device" : "Device->Memory");

    /* Allocate memory for LLT */
    pdma_ctrl.chan[ch].page_size = rt_page_bits(sizeof(pdma_llt_t) * list_num);
    llt_list = (pdma_llt_t *)rt_pages_alloc(pdma_ctrl.chan[ch].page_size);

    if (llt_list == RT_NULL)
    {
        pdma_ctrl.chan[ch].page_size = 0 ;

        LOG_E("[CH%d] Failed to allocate memory for LLT", ch);
        return RT_NULL;
    }
    LOG_D("[CH%d] Allocated %d bytes for LLT", ch, sizeof(pdma_llt_t) * list_num);

    pdma_ctrl.chan[ch].llt_va = llt_list;

    /* Initialize LLT entries */
    for (i = 0; i < list_num; i++)
    {
        /* Set source and destination addresses */
        if (mem_to_dev)
        {
            llt_list[i].src_addr = ((rt_uint32_t)(intptr_t)pdma_cfg->src_addr + PDMA_MAX_LINE_SIZE * i);
            llt_list[i].dst_addr = ((rt_uint32_t)(intptr_t)pdma_cfg->dst_addr);  /* Device address remains fixed */
        }
        else
        {
            llt_list[i].src_addr = ((rt_uint32_t)(intptr_t)pdma_cfg->src_addr);  /* Device address remains fixed */
            llt_list[i].dst_addr = ((rt_uint32_t)(intptr_t)pdma_cfg->dst_addr + PDMA_MAX_LINE_SIZE * i);
        }

        /* Set transfer size and next pointer */
        if (i == list_num - 1)
        {
            /* Last entry uses remaining size */
            llt_list[i].line_size = (pdma_cfg->line_size % PDMA_MAX_LINE_SIZE) ?
                                   (pdma_cfg->line_size % PDMA_MAX_LINE_SIZE) :
                                   PDMA_MAX_LINE_SIZE;
            llt_list[i].next_llt_addr = 0;  /* Terminate list */
            LOG_D("[CH%d] Last LLT entry: size=%d", ch, llt_list[i].line_size);
        }
        else
        {
            llt_list[i].line_size = PDMA_MAX_LINE_SIZE;
            /* Convert virtual address of next entry to physical address */
            void *next_llt_va = &llt_list[i+1];
            llt_list[i].next_llt_addr = (rt_uint32_t)(intptr_t)rt_kmem_v2p(next_llt_va);
        }
        llt_list[i].pause = 0;
    }

    /* Handle cache coherency based on transfer direction */
    if (mem_to_dev)
    {
        /* Memory to Device: clean source data cache */
        void *src_va = rt_kmem_p2v(pdma_cfg->src_addr);
        rt_hw_cpu_dcache_clean(src_va, pdma_cfg->line_size);
        LOG_D("[CH%d] Cleaned source cache (va: %p, size: %d)",
              ch, src_va, pdma_cfg->line_size);
    }
    else
    {
        /* Device to Memory: invalidate destination cache */
        void *dst_va = rt_kmem_p2v(pdma_cfg->dst_addr);
        rt_hw_cpu_dcache_invalidate(dst_va, pdma_cfg->line_size);
        LOG_D("[CH%d] Invalidated destination cache (va: %p, size: %d)",
              ch, dst_va, pdma_cfg->line_size);
    }

    /* Ensure LLT is visible to DMA */
    rt_hw_cpu_dcache_clean((void*)llt_list, sizeof(pdma_llt_t) * list_num);
    LOG_D("[CH%d] Cleaned LLT cache (va: %p, size: %d)",
          ch, llt_list, sizeof(pdma_llt_t) * list_num);

    /* Return physical address of LLT */
    void *llt_list_pa = rt_kmem_v2p(llt_list);
    LOG_I("[CH%d] LLT calculation complete (pa: %p)", ch, llt_list_pa);

    return (rt_uint32_t *)llt_list_pa;
}

/**
 * @brief Free allocated PDMA linked list table (LLT) memory
 * @param ch Channel number (0-PDMA_MAX_CHANNELS-1) to free
 */
static void _k230_pdma_llt_free(rt_uint8_t ch)
{
    rt_uint32_t *llt_list_pa;
    void *llt_list_va;

    LOG_D("[CH%d] Freeing LLT memory", ch);

    if(pdma_ctrl.chan[ch].llt_va != RT_NULL)
    {
        /* Free the allocated pages */
        rt_pages_free(pdma_ctrl.chan[ch].llt_va, pdma_ctrl.chan[ch].page_size);
        pdma_ctrl.chan[ch].llt_va = 0;
        pdma_ctrl.chan[ch].page_size = 0;
        LOG_D("[CH%d] Freed %d bytes of LLT memory", ch,pdma_ctrl.chan[ch].page_size);
    }
}

/**
 * @brief PDMA interrupt service routine
 * @param irq Interrupt number (unused)
 * @param param Channel number passed as void pointer
 */
static void k230_pdma_isr(int irq, void *param)
{
    rt_uint8_t ch = (rt_uintptr_t)param;  /* Convert channel parameter */
    rt_bool_t success = RT_FALSE; /* Transfer result flag */
    k230_pdma_callback_t callback = RT_NULL; /* Callback function pointer */

    LOG_D("[CH%d] PDMA interrupt triggered", ch);

    PDMA_LOCK();

    /* Only process interrupts for enabled channels */
    if (PDMA_CH_MENUCONFIG_ENABLED(ch) && PDMA_CH_IS_ENABLED(ch))
    {
        /* Check for transfer complete interrupt */
        if (PDMA_CH_INT_IS_TRIGGERED(ch, PDMA_PDONE_INT))
        {
            success = RT_TRUE;
            callback = pdma_ctrl.chan[ch].cb.callback;
            LOG_D("[CH%d] Transfer complete", ch);
        }
        /* Check for timeout interrupt */
        else if (PDMA_CH_INT_IS_TRIGGERED(ch, PDMA_PTOUT_INT))
        {
            success = RT_FALSE;
            callback = pdma_ctrl.chan[ch].cb.callback;
            LOG_E("[CH%d] Transfer timeout", ch);
        }
        /* Check for pause interrupt */
        else if (PDMA_CH_INT_IS_TRIGGERED(ch, PDMA_PPAUSE_INT))
        {
            PDMA_CH_RESUME(ch);
            LOG_D("[CH%d] Transfer resumed", ch);
        }

        /* Clear all interrupt flags for this channel */
        PDMA_CH_INT_CLEAR_ALL(ch);
        LOG_D("[CH%d] Interrupts cleared", ch);
    }

    PDMA_UNLOCK();

    if (callback)
    {
        callback(ch, success);
    }
}

/**
 * @brief Initialize PDMA hardware device
 * @return RT_EOK on success, error code on failure
 */
int rt_hw_pdma_device_init(void)
{
    LOG_I("Initializing PDMA controller");

    /* Map PDMA registers */
    pdma_ctrl.reg = rt_ioremap((void *)DMA_BASE_ADDR, DMA_IO_SIZE);
    if (RT_NULL == pdma_ctrl.reg)
    {
        LOG_E("Failed to map PDMA registers");
        return -RT_ERROR;
    }
    LOG_D("Mapped PDMA registers at 0x%08X", DMA_BASE_ADDR);

    if (kd_request_lock(HARDLOCK_PDMA))
    {
        pdma_ctrl.hardlock = -1;
        rt_iounmap(pdma_ctrl.reg);
        LOG_E("Failed to acquire PDMA hardware lock");
        return -RT_ERROR;
    }
    pdma_ctrl.hardlock = HARDLOCK_PDMA;
    LOG_D("Acquired PDMA hardware lock");

    /* Install and enable interrupts for configured channels */
#if defined(BSP_USING_PDMA_CHANNEL0)
    pdma_ctrl.chan[PDMA_CH_0].menuconfig_enabled = RT_TRUE;
    pdma_ctrl.chan[PDMA_CH_0].irq_num = PDMA_CHANNEL0_IRQn;
    rt_hw_interrupt_install(PDMA_CHANNEL0_IRQn, k230_pdma_isr, (void *)PDMA_CH_0, "pdma_ch0");
    LOG_D("Enabled interrupts for channel 0");
#endif

#if defined(BSP_USING_PDMA_CHANNEL1)
    pdma_ctrl.chan[PDMA_CH_1].menuconfig_enabled = RT_TRUE;
    pdma_ctrl.chan[PDMA_CH_1].irq_num = PDMA_CHANNEL1_IRQn;
    rt_hw_interrupt_install(PDMA_CHANNEL1_IRQn, k230_pdma_isr, (void *)PDMA_CH_1, "pdma_ch1");
    LOG_D("Enabled interrupts for channel 1");
#endif

#if defined(BSP_USING_PDMA_CHANNEL2)
    pdma_ctrl.chan[PDMA_CH_2].menuconfig_enabled = RT_TRUE;
    pdma_ctrl.chan[PDMA_CH_2].irq_num = PDMA_CHANNEL2_IRQn;
    rt_hw_interrupt_install(PDMA_CHANNEL2_IRQn, k230_pdma_isr, (void *)PDMA_CH_2, "pdma_ch2");
    LOG_D("Enabled interrupts for channel 2");
#endif

#if defined(BSP_USING_PDMA_CHANNEL3)
    pdma_ctrl.chan[PDMA_CH_3].menuconfig_enabled = RT_TRUE;
    pdma_ctrl.chan[PDMA_CH_3].irq_num = PDMA_CHANNEL3_IRQn;
    rt_hw_interrupt_install(PDMA_CHANNEL3_IRQn, k230_pdma_isr, (void *)PDMA_CH_3, "pdma_ch3");
    LOG_D("Enabled interrupts for channel 3");
#endif

#if defined(BSP_USING_PDMA_CHANNEL4)
    pdma_ctrl.chan[PDMA_CH_4].menuconfig_enabled = RT_TRUE;
    pdma_ctrl.chan[PDMA_CH_4].irq_num = PDMA_CHANNEL4_IRQn;
    rt_hw_interrupt_install(PDMA_CHANNEL4_IRQn, k230_pdma_isr, (void *)PDMA_CH_4, "pdma_ch4");
    LOG_D("Enabled interrupts for channel 4");
#endif

#if defined(BSP_USING_PDMA_CHANNEL5)
    pdma_ctrl.chan[PDMA_CH_5].menuconfig_enabled = RT_TRUE;
    pdma_ctrl.chan[PDMA_CH_5].irq_num = PDMA_CHANNEL5_IRQn;
    rt_hw_interrupt_install(PDMA_CHANNEL5_IRQn, k230_pdma_isr, (void *)PDMA_CH_5, "pdma_ch5");
    LOG_D("Enabled interrupts for channel 5");
#endif

#if defined(BSP_USING_PDMA_CHANNEL6)
    pdma_ctrl.chan[PDMA_CH_6].menuconfig_enabled = RT_TRUE;
    pdma_ctrl.chan[PDMA_CH_6].irq_num = PDMA_CHANNEL6_IRQn;
    rt_hw_interrupt_install(PDMA_CHANNEL6_IRQn, k230_pdma_isr, (void *)PDMA_CH_6, "pdma_ch6");
    LOG_D("Enabled interrupts for channel 6");
#endif

#if defined(BSP_USING_PDMA_CHANNEL7)
    pdma_ctrl.chan[PDMA_CH_7].menuconfig_enabled = RT_TRUE;
    pdma_ctrl.chan[PDMA_CH_7].irq_num = PDMA_CHANNEL7_IRQn;
    rt_hw_interrupt_install(PDMA_CHANNEL7_IRQn, k230_pdma_isr, (void *)PDMA_CH_7, "pdma_ch7");
    LOG_D("Enabled interrupts for channel 7");
#endif

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_pdma_device_init);