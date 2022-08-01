/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_PIO_H
#define _HARDWARE_STRUCTS_PIO_H

#include "hardware/address_mapped.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/pio.h"

typedef struct {
    io_rw_32 ctrl;
    io_ro_32 fstat;
    io_rw_32 fdebug;
    io_ro_32 flevel;
    io_wo_32 txf[NUM_PIO_STATE_MACHINES];
    io_ro_32 rxf[NUM_PIO_STATE_MACHINES];
    io_rw_32 irq;
    io_wo_32 irq_force;
    io_rw_32 input_sync_bypass;
    io_rw_32 dbg_padout;
    io_rw_32 dbg_padoe;
    io_rw_32 dbg_cfginfo;
    io_wo_32 instr_mem[32];
    struct pio_sm_hw {
        io_rw_32 clkdiv;
        io_rw_32 execctrl;
        io_rw_32 shiftctrl;
        io_ro_32 addr;
        io_rw_32 instr;
        io_rw_32 pinctrl;
    } sm[NUM_PIO_STATE_MACHINES];
    io_rw_32 intr;
    io_rw_32 inte0;
    io_rw_32 intf0;
    io_ro_32 ints0;
    io_rw_32 inte1;
    io_rw_32 intf1;
    io_ro_32 ints1;
} pio_hw_t;

#define pio0_hw ((pio_hw_t *const)PIO0_BASE)
#define pio1_hw ((pio_hw_t *const)PIO1_BASE)

#endif
