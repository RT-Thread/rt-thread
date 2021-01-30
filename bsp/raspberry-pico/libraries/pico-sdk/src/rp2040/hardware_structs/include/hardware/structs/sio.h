/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_SIO_H
#define _HARDWARE_STRUCTS_SIO_H

#include "hardware/address_mapped.h"
#include "hardware/regs/sio.h"
#include "hardware/structs/interp.h"

typedef struct {
    io_ro_32 cpuid;
    io_ro_32 gpio_in;
    io_ro_32 gpio_hi_in;
    uint32_t _pad;

    io_wo_32 gpio_out;
    io_wo_32 gpio_set;
    io_wo_32 gpio_clr;
    io_wo_32 gpio_togl;

    io_wo_32 gpio_oe;
    io_wo_32 gpio_oe_set;
    io_wo_32 gpio_oe_clr;
    io_wo_32 gpio_oe_togl;

    io_wo_32 gpio_hi_out;
    io_wo_32 gpio_hi_set;
    io_wo_32 gpio_hi_clr;
    io_wo_32 gpio_hi_togl;

    io_wo_32 gpio_hi_oe;
    io_wo_32 gpio_hi_oe_set;
    io_wo_32 gpio_hi_oe_clr;
    io_wo_32 gpio_hi_oe_togl;

    io_rw_32 fifo_st;
    io_wo_32 fifo_wr;
    io_ro_32 fifo_rd;
    io_ro_32 spinlock_st;

    io_rw_32 div_udividend;
    io_rw_32 div_udivisor;
    io_rw_32 div_sdividend;
    io_rw_32 div_sdivisor;

    io_rw_32 div_quotient;
    io_rw_32 div_remainder;
    io_rw_32 div_csr;

    uint32_t _pad2;

    interp_hw_t interp[2];
} sio_hw_t;

#define sio_hw ((sio_hw_t *)SIO_BASE)

#endif
