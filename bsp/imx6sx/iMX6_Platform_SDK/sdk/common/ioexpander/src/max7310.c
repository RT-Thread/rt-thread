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

/*!
 * @file max7310.c
 * @brief Driver and test for the I/O expander MAX7310 controlled through I2C.
 *
 * @ingroup diag_ioexpander
 */

#include "ioexpander/max7310.h"
#include "max7310_registers.h"

/*!
 * @note In hardware.h an array of I2C requests is created as multiple I/O expanders
 *       could be used on a board.
 *       Thanks to board_init() in hardware.c, the requests are populated with addresses.
 *       The local I2C request used in this driver should point to the request of the
 *       IO expander that needs to be accessed.
 *       e.g.     max7310_i2c_req = &max7310_i2c_req_array[slave_id];
 */
static struct imx_i2c_request *max7310_i2c_req;

/*!
 * Function to read a register of the MAX7310.
 *
 * @param reg_addr   register address
 *
 * @return the value of the read register
 */
uint8_t max7310_reg_read(uint8_t reg_addr)
{
    uint8_t buf;

    max7310_i2c_req->reg_addr = reg_addr;
    max7310_i2c_req->buffer = &buf;
    i2c_read(max7310_i2c_req);
    return buf;
}

/*!
 * Function to read a register of the video A/D converter ADV7180.
 *
 * @param reg_addr   register address
 * @param data       written data
 *
 * @return 0 on success; non-zero otherwise
 */
int32_t max7310_reg_write(uint8_t reg_addr, uint8_t data)
{
    max7310_i2c_req->reg_addr = reg_addr;
    max7310_i2c_req->buffer = &data;
    return i2c_write(max7310_i2c_req);
}

int32_t max7310_init(uint32_t slave_id, uint32_t io_default_dir, uint32_t out_default_val)
{
    max7310_i2c_req = &max7310_i2c_req_array[slave_id];

    // I2C controller init
    i2c_init(max7310_i2c_req->ctl_addr, 170000);
    // initialize I2C request fixed elements
    max7310_i2c_req->reg_addr_sz = 1;
    max7310_i2c_req->buffer_sz = 1;
    // initialize I/O to output with all outputs at 0
    max7310_reg_write(polarity_reg, 0x00);  // non-inverted polarity
    max7310_reg_write(output_port_reg, out_default_val);
    max7310_reg_write(config_reg, io_default_dir);
    /* Disable timeout function that reset I2C bus in case of error
       and store a known value for ID test => which should obviously pass */
    max7310_reg_write(timeout_reg, 0xAC);

    return 0;
}

void max7310_set_gpio_output(uint32_t slave_id, uint32_t io_x, uint32_t level)
{
    uint8_t data;

    max7310_i2c_req = &max7310_i2c_req_array[slave_id];
    // read output state first through the input register
    data = max7310_reg_read(input_port_reg);
    // process it
    data &= ~(1 << io_x);
    data |= (level << io_x);
    // write result in output register
    max7310_reg_write(output_port_reg, data);
}

