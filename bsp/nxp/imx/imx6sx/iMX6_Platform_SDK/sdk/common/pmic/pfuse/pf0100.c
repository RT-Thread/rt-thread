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
 * @file pf0100.c
 * @brief Driver and test for pf0100 through I2C controller.
 *
 * @ingroup pmic
 */

#include "i2c/imx_i2c.h"
#include "soc_memory_map.h"
#include "sdk.h"
#include "utility/menu.h"

const char g_pmic_pf0100_i2c_device_id_test_name[] = "PMIC PF0100 I2C Device ID Test";

/*!
 * Function to read a register of pf0100.
 *
 * @param reg_addr register address
 *
 * @return the value of the read register
 */
unsigned char pf0100_reg_read(unsigned char reg_addr)
{
    struct imx_i2c_request rq = {0};
    unsigned char buf;

    rq.ctl_addr = g_pmic_pf0100_i2c_device.port;
    rq.dev_addr = g_pmic_pf0100_i2c_device.address;
    rq.reg_addr = reg_addr;
    rq.reg_addr_sz = 1;
    rq.buffer_sz = 1;
    rq.buffer = &buf;
    rq.device = NULL;

    i2c_xfer(&rq, I2C_READ);

    return buf;
}

/*!
 * Function to write a register of pf0100.
 *
 * @param reg_addr register address
 *
 * @param reg_data written data
 *
 */
void pf0100_reg_write(unsigned char reg_addr, unsigned char reg_data)
{
    struct imx_i2c_request rq = {0};

    rq.ctl_addr = g_pmic_pf0100_i2c_device.port;
    rq.dev_addr = g_pmic_pf0100_i2c_device.address;
    rq.reg_addr = reg_addr;
    rq.reg_addr_sz = 1;
    rq.buffer_sz = 1;
    rq.buffer = &reg_data;
    rq.device = NULL;

    i2c_xfer(&rq, I2C_WRITE);
}

/*!
 * Function to generate vgen1--1.2V
 */
void pf0100_enable_vgen1_1v2(void)
{
    unsigned char data;

    i2c_init(g_pmic_pf0100_i2c_device.port, 170000);
    data = pf0100_reg_read(108);
    pf0100_reg_write(108, 0x18);
}

/*!
 * Function to generate vgen2--1.5V
 */
void pf0100_enable_vgen2_1v5(void)
{
    unsigned char data;

    i2c_init(g_pmic_pf0100_i2c_device.port, 170000);
    data = pf0100_reg_read(109);
    pf0100_reg_write(109, 0x1E);
}

/*!
 * Function to generate vgen3--1.8V
 */ 
void pf0100_enable_vgen3_1v8(void)
{
    unsigned char data;

    i2c_init(g_pmic_pf0100_i2c_device.port, 170000);
    data = pf0100_reg_read(110);
    pf0100_reg_write(110, 0x10);
}

/*!
 * Function to generate vgen4--1.8V
 */
void pf0100_enable_vgen4_1v8(void)
{
    unsigned char data;

    i2c_init(g_pmic_pf0100_i2c_device.port, 170000);
    data = pf0100_reg_read(111);
    pf0100_reg_write(111, 0x10);
}

/*!
 * Function to generate vgen2--2.5V
 */
void pf0100_enable_vgen4_2v5(void)
{
    unsigned char data;

    i2c_init(g_pmic_pf0100_i2c_device.port, 170000);
    data = pf0100_reg_read(112);
    pf0100_reg_write(112, 0x17);
}

/*!
 * Function to generate vgen6--2.8V
 */
void pf0100_enable_vgen6_2v8(void)
{
    unsigned char data;

    i2c_init(g_pmic_pf0100_i2c_device.port, 170000);
    data = pf0100_reg_read(113);
    pf0100_reg_write(113, 0x1A);
}

test_return_t pf0100_i2c_device_id_check(void)
{
    unsigned char data;
	const char* indent = menu_get_indent();

    i2c_init(g_pmic_pf0100_i2c_device.port, 170000);

    data = 0x0;
    data = pf0100_reg_read(0x0);    //Device ID
    if (!(data & 0x10)) {       //bit 4 should be set, 0b0001xxxx
        printf("%sExpected id 0b0001xxxx (PF0100), read 0x%X\n", indent, data);
        return TEST_FAILED;
    }
    printf("%sPF0100 ID: 0b0001xxxx, read: 0x%X\n", indent, data);
    printf("%s PMIC PF0100 ID test passed.\n", indent);

    return TEST_PASSED;
}

