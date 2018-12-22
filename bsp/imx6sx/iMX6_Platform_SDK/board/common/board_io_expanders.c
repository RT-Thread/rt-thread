/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "sdk.h"
#include "board_io_expanders.h"
#include "registers/regsi2c.h"
#include "registers/regsiomuxc.h"

////////////////////////////////////////////////////////////////////////////////
// Globals
////////////////////////////////////////////////////////////////////////////////

imx_i2c_request_t max7310_i2c_req_array[MAX7310_NBR];

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void board_ioexpander_init(void)
{
#if defined(BOARD_SABRE_AI)
    // Bring max7310 out of reset
    // (this iomux setting should be done in gpio_iomux_config())
    gpio_set_gpio(GPIO_PORT1, 15);
    gpio_set_direction(GPIO_PORT1, 15, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT1, 15, GPIO_HIGH_LEVEL);
 
    // for I2C3 steering
    // Select ALT5 mode of EIM_A24 for GPIO5_4 - EIMD18_I2C3_STEER(EIM_A24)
    // high output to select I2C3 option
    // (this iomux setting should be done in gpio_iomux_config())
    gpio_set_gpio(GPIO_PORT5, 4);
    gpio_set_direction(GPIO_PORT5, 4, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT5, 4, GPIO_HIGH_LEVEL);
#endif

    // Build array of I2C request structures.
#if defined(BOARD_EVB) || defined(BOARD_SABRE_AI)
    // Configure some board signals through I/O expanders
    max7310_i2c_req_array[0].ctl_addr = HW_I2C3; // the I2C controller base address
    max7310_i2c_req_array[0].dev_addr = MAX7310_I2C_ID0;    // the I2C DEVICE address
    max7310_init(0, MAX7310_ID0_DEF_DIR, MAX7310_ID0_DEF_VAL);
    
    max7310_i2c_req_array[1].ctl_addr = HW_I2C3; // the I2C controller base address
    max7310_i2c_req_array[1].dev_addr = MAX7310_I2C_ID1;    // the I2C DEVICE address
    max7310_init(1, MAX7310_ID1_DEF_DIR, MAX7310_ID1_DEF_VAL);
#endif
#if defined(BOARD_SABRE_AI)
    max7310_i2c_req_array[2].ctl_addr = HW_I2C3; // the I2C controller base address
    max7310_i2c_req_array[2].dev_addr = MAX7310_I2C_ID2;    // the I2C DEVICE address
    max7310_init(2, MAX7310_ID2_DEF_DIR, MAX7310_ID2_DEF_VAL);
#endif
}

void board_ioexpander_iomux_config(void)
{
#if defined(BOARD_SABRE_AI)

    i2c3_iomux_config();

#if !defined(BOARD_REV_A)
    /*
     * for I2C3 steering:
     *
     * i2c3_iomux_config() selected ALT5 mode of EIM_A24
     * for GPIO5_4 - EIMD18_I2C3_STEER(EIM_A24)
     *
     * high output to select I2C3 option
     */
    gpio_set_direction(GPIO_PORT5, 4, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT5, 4, GPIO_HIGH_LEVEL);

#endif // !defined(BOARD_REV_A)

#endif // defined(BOARD_SABRE_AI)
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
