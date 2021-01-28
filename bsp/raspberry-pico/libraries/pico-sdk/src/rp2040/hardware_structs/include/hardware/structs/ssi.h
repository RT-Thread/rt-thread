/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_SSI_H
#define _HARDWARE_STRUCTS_SSI_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/ssi.h"

typedef struct {
    io_rw_32 ctrlr0;
    io_rw_32 ctrlr1;
    io_rw_32 ssienr;
    io_rw_32 mwcr;
    io_rw_32 ser;
    io_rw_32 baudr;
    io_rw_32 txftlr;
    io_rw_32 rxftlr;
    io_rw_32 txflr;
    io_rw_32 rxflr;
    io_rw_32 sr;
    io_rw_32 imr;
    io_rw_32 isr;
    io_rw_32 risr;
    io_rw_32 txoicr;
    io_rw_32 rxoicr;
    io_rw_32 rxuicr;
    io_rw_32 msticr;
    io_rw_32 icr;
    io_rw_32 dmacr;
    io_rw_32 dmatdlr;
    io_rw_32 dmardlr;
    io_rw_32 idr;
    io_rw_32 ssi_version_id;
    io_rw_32 dr0;
    uint32_t _pad[(0xf0 - 0x60) / 4 - 1];
    io_rw_32 rx_sample_dly;
    io_rw_32 spi_ctrlr0;
    io_rw_32 txd_drive_edge;
} ssi_hw_t;

#define ssi_hw ((ssi_hw_t *const)XIP_SSI_BASE)
#endif
