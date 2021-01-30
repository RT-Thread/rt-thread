/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _HARDWARE_STRUCTS_XIP_CTRL_H
#define _HARDWARE_STRUCTS_XIP_CTRL_H

#include "hardware/address_mapped.h"
#include "hardware/regs/xip.h"

typedef struct {
    io_rw_32 ctrl;
    io_rw_32 flush;
    io_rw_32 stat;
    io_rw_32 ctr_hit;
    io_rw_32 ctr_acc;
    io_rw_32 stream_addr;
    io_rw_32 stream_ctr;
    io_rw_32 stream_fifo;
} xip_ctrl_hw_t;

#define XIP_STAT_FIFO_FULL     0x4u
#define XIP_STAT_FIFO_EMPTY    0x2u
#define XIP_STAT_FLUSH_RDY     0x1u

#define xip_ctrl_hw ((xip_ctrl_hw_t *const)XIP_CTRL_BASE)

#endif
