/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_PLL_H
#define _HARDWARE_STRUCTS_PLL_H

#include "hardware/address_mapped.h"
#include "hardware/regs/pll.h"

/// \tag::pll_hw[]
typedef struct {
    io_rw_32 cs;
    io_rw_32 pwr;
    io_rw_32 fbdiv_int;
    io_rw_32 prim;
} pll_hw_t;

#define pll_sys_hw ((pll_hw_t *const)PLL_SYS_BASE)
#define pll_usb_hw ((pll_hw_t *const)PLL_USB_BASE)
/// \end::pll_hw[]

#endif
