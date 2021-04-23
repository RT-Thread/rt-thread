/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _HARDWARE_STRUCTS_BUS_CTRL_H
#define _HARDWARE_STRUCTS_BUS_CTRL_H

#include "hardware/address_mapped.h"
#include "hardware/regs/busctrl.h"

enum bus_ctrl_perf_counter {
    arbiter_rom_perf_event_access = 19,
    arbiter_rom_perf_event_access_contested = 18,
    arbiter_xip_main_perf_event_access = 17,
    arbiter_xip_main_perf_event_access_contested = 16,
    arbiter_sram0_perf_event_access = 15,
    arbiter_sram0_perf_event_access_contested = 14,
    arbiter_sram1_perf_event_access = 13,
    arbiter_sram1_perf_event_access_contested = 12,
    arbiter_sram2_perf_event_access = 11,
    arbiter_sram2_perf_event_access_contested = 10,
    arbiter_sram3_perf_event_access = 9,
    arbiter_sram3_perf_event_access_contested = 8,
    arbiter_sram4_perf_event_access = 7,
    arbiter_sram4_perf_event_access_contested = 6,
    arbiter_sram5_perf_event_access = 5,
    arbiter_sram5_perf_event_access_contested = 4,
    arbiter_fastperi_perf_event_access = 3,
    arbiter_fastperi_perf_event_access_contested = 2,
    arbiter_apb_perf_event_access = 1,
    arbiter_apb_perf_event_access_contested = 0
};

typedef struct {
    io_rw_32 priority;
    io_ro_32 priority_ack;
    struct {
        io_rw_32 value;
        io_rw_32 sel;
    } counter[4];
} bus_ctrl_hw_t;

check_hw_layout(bus_ctrl_hw_t, counter[0].value, BUSCTRL_PERFCTR0_OFFSET);

#define bus_ctrl_hw ((bus_ctrl_hw_t *const)BUSCTRL_BASE)

#endif
