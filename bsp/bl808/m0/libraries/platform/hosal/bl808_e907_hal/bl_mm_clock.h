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
#ifndef __BL_MM_CLOCK__
#define __BL_MM_CLOCK__
/*MM XCLK select*/
typedef enum {
    XCLK_RC32M = 0,
    XCLK_XTAL,
}mm_xclk_type;

/*MM BCLK1x select*/
typedef enum {
    BCLK_XCLK = 0,
    BCLK_MUXPLL_160M = 2,
    BCLK_MUXPLL_240M = 3,
}mm_bclk_type;

/*MM CPU PLL select*/
typedef enum {
    CPU_CLK_MUXPLL_240M = 0,
    CPU_CLK_MUXPLL_320M,
    CPU_CLK_MUXPLL_400M,
}mm_cpu_clk_type;

/*MM CPU ROOT CLK select*/
typedef enum {
    CPU_ROOT_CLK_XCLK = 0,
    CPU_ROOT_CLK_PLL,
}mm_cpu_root_clk_type;

/*MM SPI CLK select*/
typedef enum {
    SPI_CLK_MUXPLL_160M = 0,
    SPI_CLK_XCLK,
}mm_spi_clk_type;

/*MM I2C CLK select*/
typedef enum {
    I2C_CLK_BCLK = 0,
    I2C_CLK_XCLK,
}mm_i2c_clk_type;

/*MM UART CLK select*/
typedef enum {
    UART_CLK_BCLK = 0,
    UART_CLK_MUXPLL_160M,
    UART_CLK_XCLK1, //2 or 3 all select MM XCLK
    UART_CLK_XCLK2,
}mm_uart_clk_type;

void bl_mm_clk_dump(void);
void bl_mm_xclk_config(mm_xclk_type xclk_num);
void bl_mm_bclk_config(mm_bclk_type bclk_num);
void bl_mm_cpu_clk_config(mm_cpu_clk_type cpu_clk_num);
void bl_mm_cpu_root_clk_config(mm_cpu_root_clk_type cpu_root_clk_num);
void bl_mm_spi_clk_config(mm_spi_clk_type spi_clk_num);
void bl_mm_i2c_clk_config(mm_i2c_clk_type i2c_clk_num);
void bl_mm_uart_clk_config(mm_uart_clk_type uart_clk_num);
#endif
