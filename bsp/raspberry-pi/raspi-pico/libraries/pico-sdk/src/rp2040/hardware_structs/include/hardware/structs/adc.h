/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _HARDWARE_STRUCTS_ADC_H
#define _HARDWARE_STRUCTS_ADC_H

#include "hardware/address_mapped.h"
#include "hardware/regs/adc.h"

typedef struct {
    io_rw_32 cs;
    io_rw_32 result;
    io_rw_32 fcs;
    io_rw_32 fifo;
    io_rw_32 div;
    io_rw_32 intr;
    io_rw_32 inte;
    io_rw_32 intf;
    io_rw_32 ints;
} adc_hw_t;

check_hw_layout(adc_hw_t, ints, ADC_INTS_OFFSET);

#define adc_hw ((adc_hw_t *const)ADC_BASE)

#endif
