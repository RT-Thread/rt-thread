/*
 * Copyright (c) 2018, Synopsys, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mux_hal.h"
#include "mux.h"

static MUX_REG *mux_ctrl_regs = (MUX_REG *)0;

/** initialize i2c controller and set slave device address */
void mux_init(MUX_REG *mux_regs)
{
    // Initialize Mux controller registers by default values
    mux_regs[PMOD_MUX_CTRL] = PMOD_MUX_CTRL_DEFAULT;
    mux_regs[SPI_MAP_CTRL] =  SPI_MAP_CTRL_DEFAULT;
    mux_regs[UART_MAP_CTRL] = UART_MAP_CTRL_DEFAULT;
    mux_ctrl_regs = mux_regs;
}

/** Get mux ctrl register pointer, only valid after mux_init */
MUX_REG *get_mux_regs(void)
{
    return mux_ctrl_regs;
}

/** set PMOD muxer scheme */
void set_pmod_mux(MUX_REG *mux_regs, uint32_t val)
{
    mux_regs[PMOD_MUX_CTRL] = val;
}

/** get PMOD muxer scheme */
uint32_t get_pmod_mux(MUX_REG *mux_regs)
{
    return (uint32_t) mux_regs[PMOD_MUX_CTRL];
}

/** set PMOD muxer scheme */
void change_pmod_mux(MUX_REG *mux_regs, uint32_t val, uint32_t change_bits)
{
    mux_regs[PMOD_MUX_CTRL] = ((mux_regs[PMOD_MUX_CTRL] & ~change_bits) | val);
}

/** set SPI connection scheme */
void set_spi_map(MUX_REG *mux_regs, uint32_t val)
{
    mux_regs[SPI_MAP_CTRL] = val;
}

/** get SPI connection scheme */
uint32_t get_spi_map(MUX_REG *mux_regs)
{
    return (uint32_t) mux_regs[SPI_MAP_CTRL];
}

/** set UART connection scheme */
void set_uart_map(MUX_REG *mux_regs, uint32_t val)
{
    mux_regs[UART_MAP_CTRL] = val;
}

/** get UART connection scheme */
uint32_t get_uart_map(MUX_REG *mux_regs)
{
    return (uint32_t) mux_regs[UART_MAP_CTRL];
}
