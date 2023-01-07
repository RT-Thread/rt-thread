/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdint.h>
#include <stdio.h>
#include "bl_mm_clock.h"
//FIXME no BL808/BL606p header file including is Allowed here
#ifdef BL808
#include <bl808_glb.h>
#include <mm_glb_reg.h>
#elif defined(BL606P)
//TODO BL606P H FILE
#include <bl606p_glb.h>
#include <mm_glb_reg.h>
#else
#error "Use CHIP BL808/BL606P for this module"
#endif

static void get_mm_xclk(uint32_t reg_val)
{
    uint32_t cpu_pll_clk = 0;
    cpu_pll_clk = BL_GET_REG_BITS_VAL(reg_val, MM_GLB_REG_XCLK_CLK_SEL);

    switch (cpu_pll_clk) {
        case 0:
            printf("XCLK select RC32M\r\n");
            break;
        case 1:
            printf("XCLK select XTAL\r\n");
            break;
        default:
              break;
    }
}

static void get_mm_cpu_pll_clk(uint32_t reg_val)
{
    uint32_t cpu_pll_clk = 0;
    cpu_pll_clk = BL_GET_REG_BITS_VAL(reg_val, MM_GLB_REG_CPU_CLK_SEL);

    switch (cpu_pll_clk) {
        case 0:
            printf("MM CPU select 240Mhz\r\n");
            break;
        case 1:
            printf("MM CPU select 320Mhz\r\n");
            break;
        case 2:
            printf("MM CPU select 400Mhz\r\n");
            break;
        default:
            break;
    }

}

static void dump_mm_cpu_clk(void)
{
    uint32_t tmpVal = 0, cpu_root_clk = 0;
 
    tmpVal = BL_RD_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    cpu_root_clk = BL_GET_REG_BITS_VAL(tmpVal, MM_GLB_REG_CPU_ROOT_CLK_SEL);
    switch (cpu_root_clk) {
        case 0:
            printf("MM CPU select XCLK--->");
            get_mm_xclk(tmpVal);
            break;
        case 1:
            printf("MM CPU select PLL--->");
            get_mm_cpu_pll_clk(tmpVal);
            break;
        default:
            break;
    }
}

static void dump_mm_bus_clk(void)
{
    uint32_t tmpVal = 0, mm_bus_clk = 0;

    tmpVal = BL_RD_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    mm_bus_clk = BL_GET_REG_BITS_VAL(tmpVal, MM_GLB_REG_BCLK1X_SEL);

    switch (mm_bus_clk) {
        case 0:
            printf("MM BUS CLK select XCLK--->");
            get_mm_xclk(tmpVal);
            break;
        case 2:
            printf("MM BUS CLK select 160Mhz\r\n");
            break;
        case 3:
            printf("MM BUS CLK select 240Mhz\r\n");
            break;
        default:
            break;
    }

}

static void dump_mm_xclk(void)
{
    uint32_t tmpVal = 0;
    tmpVal = BL_RD_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    get_mm_xclk(tmpVal);
}

static void dump_mm_uart_clk(void)
{
    uint32_t tmpVal = 0, mm_uart_clk = 0;

    tmpVal = BL_RD_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    mm_uart_clk = BL_GET_REG_BITS_VAL(tmpVal, MM_GLB_REG_UART_CLK_SEL);

    switch (mm_uart_clk) {
        case 0:
            printf("UART CLK select MM BUS CLK--->");
            dump_mm_bus_clk();
            break;
        case 1:
            printf("UART CLK select 160Mhz\r\n");
            break;
        case 2:
        case 3:
            printf("UART CLK select MM XCLK--->");
            get_mm_xclk(tmpVal);
            break;
        default:
            break;
    }
}

static void dump_mm_i2c_clk(void)
{
    uint32_t tmpVal = 0, mm_i2c_clk = 0;

    tmpVal = BL_RD_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    mm_i2c_clk = BL_GET_REG_BITS_VAL(tmpVal, MM_GLB_REG_I2C_CLK_SEL);

    switch (mm_i2c_clk) {
        case 0:
            printf("I2C CLK select MM BUS CLK--->");
            dump_mm_bus_clk();
            break;
        case 1:
            printf("I2C CLK select MM XCLK--->");
            get_mm_xclk(tmpVal);
            break;
        default:
            break;
    }
}

static void dump_mm_spi_clk(void)
{
    uint32_t tmpVal = 0, mm_spi_clk = 0;

    tmpVal = BL_RD_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    mm_spi_clk = BL_GET_REG_BITS_VAL(tmpVal, MM_GLB_REG_SPI_CLK_SEL);

    switch (mm_spi_clk) {
        case 0:
            printf("SPI CLK select 160Mhz\r\n");
            break;
        case 1:
            printf("SPI CLK select MM XCLK--->");
            get_mm_xclk(tmpVal);
            break;
        default:
            break;
    }
}

void bl_mm_clk_dump(void)
{
    dump_mm_cpu_clk();
    dump_mm_uart_clk();
    dump_mm_i2c_clk();
    dump_mm_spi_clk();
    dump_mm_bus_clk();
    dump_mm_xclk();
}

void bl_mm_xclk_config(mm_xclk_type xclk_num)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_XCLK_CLK_SEL, xclk_num);

    BL_WR_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);
}

void bl_mm_bclk_config(mm_bclk_type bclk_num)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_BCLK1X_SEL, bclk_num);

    BL_WR_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);
}

void bl_mm_cpu_root_clk_config(mm_cpu_root_clk_type cpu_root_clk_num)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_CPU_ROOT_CLK_SEL, cpu_root_clk_num);

    BL_WR_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);
}

void bl_mm_cpu_clk_config(mm_cpu_clk_type cpu_clk_num)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_CPU_CLK_SEL, cpu_clk_num);

    BL_WR_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);
}

void bl_mm_spi_clk_config(mm_spi_clk_type spi_clk_num)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_SPI_CLK_SEL, spi_clk_num);

    BL_WR_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);
}

void bl_mm_i2c_clk_config(mm_i2c_clk_type i2c_clk_num)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_I2C_CLK_SEL, i2c_clk_num);

    BL_WR_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);
}

void bl_mm_uart_clk_config(mm_uart_clk_type uart_clk_num)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_UART_CLK_SEL, uart_clk_num);

    BL_WR_REG(CLKRST_CTRL_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);
}

