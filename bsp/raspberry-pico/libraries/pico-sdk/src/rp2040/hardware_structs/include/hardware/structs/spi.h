/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_SPI_H
#define _HARDWARE_STRUCTS_SPI_H

#include "hardware/address_mapped.h"
#include "hardware/regs/spi.h"

typedef struct {
    io_rw_32 cr0;
    io_rw_32 cr1;
    io_rw_32 dr;
    io_rw_32 sr;
    io_rw_32 cpsr;
    io_rw_32 imsc;
    io_rw_32 ris;
    io_rw_32 mis;
    io_rw_32 icr;
    io_rw_32 dmacr;
} spi_hw_t;

#define spi0_hw ((spi_hw_t *const)SPI0_BASE)
#define spi1_hw ((spi_hw_t *const)SPI1_BASE)

#endif
