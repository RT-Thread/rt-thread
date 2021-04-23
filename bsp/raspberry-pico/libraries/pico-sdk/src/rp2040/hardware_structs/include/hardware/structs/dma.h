/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_DMA_H
#define _HARDWARE_STRUCTS_DMA_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/dma.h"
#include "pico/assert.h"


// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_DMA, Enable/disable DMA assertions, type=bool, default=0, group=hardware_dma
#ifndef PARAM_ASSERTIONS_ENABLED_DMA
#define PARAM_ASSERTIONS_ENABLED_DMA 0
#endif

typedef struct {
    io_rw_32 read_addr;
    io_rw_32 write_addr;
    io_rw_32 transfer_count;
    io_rw_32 ctrl_trig;
    io_rw_32 al1_ctrl;
    io_rw_32 al1_read_addr;
    io_rw_32 al1_write_addr;
    io_rw_32 al1_transfer_count_trig;
    io_rw_32 al2_ctrl;
    io_rw_32 al2_transfer_count;
    io_rw_32 al2_read_addr;
    io_rw_32 al2_write_addr_trig;
    io_rw_32 al3_ctrl;
    io_rw_32 al3_write_addr;
    io_rw_32 al3_transfer_count;
    io_rw_32 al3_read_addr_trig;
}  dma_channel_hw_t;

typedef struct {
    dma_channel_hw_t ch[NUM_DMA_CHANNELS];
    uint32_t _pad0[16 * (16 - NUM_DMA_CHANNELS)];
    io_ro_32 intr;
    io_rw_32 inte0;
    io_rw_32 intf0;
    io_rw_32 ints0;
    uint32_t _pad1[1];
    io_rw_32 inte1;
    io_rw_32 intf1;
    io_rw_32 ints1;
    io_rw_32 timer[2];
    uint32_t _pad2[2];
    io_wo_32 multi_channel_trigger;
    io_rw_32 sniff_ctrl;
    io_rw_32 sniff_data;
    uint32_t _pad3[1];
    io_ro_32 fifo_levels;
    io_wo_32 abort;
} dma_hw_t;

typedef struct {
    struct dma_debug_hw_channel {
        io_ro_32 ctrdeq;
        io_ro_32 tcr;
        uint32_t pad[14];
    } ch[NUM_DMA_CHANNELS];
} dma_debug_hw_t;

#define dma_hw ((dma_hw_t *const)DMA_BASE)
#define dma_debug_hw ((dma_debug_hw_t *const)(DMA_BASE + DMA_CH0_DBG_CTDREQ_OFFSET))

static inline void check_dma_channel_param(uint channel) {
#if PARAM_ASSERTIONS_ENABLED(DMA)
    // this method is used a lot by inline functions so avoid code bloat by deferring to function
    extern void check_dma_channel_param_impl(uint channel);
    check_dma_channel_param_impl(channel);
#endif
}

inline static dma_channel_hw_t *dma_channel_hw_addr(uint channel) {
    check_dma_channel_param(channel);
    return &dma_hw->ch[channel];
}

#endif
