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
#ifdef CHIP_MX6DQ

//#include "imx_i2c.h"
#include "sdk.h"
//#include "functions.h"

#define ADP1650_I2C_ADDR    0x30

/* Reset ADP 1650
    A low-to-high transition on the EN pin resets all registers to their default values.
    SMART_DEVICE -- EN pin: GPIO3_20
 */
static void ADP1650_reset(void)
{
    int reset_occupy = 1000, reset_delay = 1000;

    /* SMART_DEVICE: set camera LED_FLASH_EN through GPIO3_20 */
    gpio_set_gpio(GPIO_PORT3, 20);
    gpio_set_direction(GPIO_PORT3, 20, GPIO_GDIR_OUTPUT);

    gpio_set_level(GPIO_PORT3, 20, GPIO_LOW_LEVEL);
    hal_delay_us(reset_occupy);
    gpio_set_level(GPIO_PORT3, 20, GPIO_HIGH_LEVEL);
    hal_delay_us(reset_delay);
}

static unsigned char ADP1650_reg_read(unsigned int i2c_base_addr, unsigned char reg_addr)
{
    struct imx_i2c_request rq = {0};
    unsigned char buf[1];
    unsigned char reg_data = 0;
    rq.dev_addr = ADP1650_I2C_ADDR;
    rq.reg_addr = reg_addr;
    rq.reg_addr_sz = 1;
    rq.buffer_sz = 1;
    rq.buffer = buf;
    rq.ctl_addr = i2c_base_addr; 
    i2c_xfer(&rq, I2C_READ);
    reg_data = buf[0];
    return reg_data;
}

static int ADP1650_reg_write(unsigned int i2c_base_addr, unsigned char reg_addr,
                             unsigned char reg_val)
{
    struct imx_i2c_request rq = {0};
    unsigned char buf[1];

    buf[0] = reg_val;
    rq.ctl_addr = i2c_base_addr;
    rq.dev_addr = ADP1650_I2C_ADDR;
    rq.reg_addr = reg_addr;
    rq.reg_addr_sz = 1;
    rq.buffer_sz = 1;
    rq.buffer = buf;
    return i2c_xfer(&rq, I2C_WRITE);
}

/* Test ADP1650 device id
    Design Information Register: 0x00 -- Default 0x22
  */
int i2c_device_id_check_ADP1650(unsigned int i2c_base_addr)
{
    unsigned int data_reg = 0;

    printf("\nTest ADP1650 Device ID: ");

    i2c_init(i2c_base_addr, 170000);

    data_reg = ADP1650_reg_read(i2c_base_addr, 0x00);   //read Design Information

    if (0x22 == data_reg) {
        printf("passed 0x%02X\n", data_reg);
        return 0;
    } else {
        printf("failed, 0x22 vs 0x%02X\n", data_reg);
        return 1;
    }
}

/* Set ADP1650 as Flash Mode
    Flash Duration:  0x02
    Flash Current:   0x03
    Flash Mode:       0x04
  */
void ADP1650_FlashMode_init(void)
{
    ADP1650_reset();

    i2c_init(I2C2_BASE_ADDR, 170000);
    i2c_device_id_check_ADP1650(I2C2_BASE_ADDR);

    /* ADP1650 Setting */
    ADP1650_reg_write(I2C2_BASE_ADDR, 0x02, 0x0F);
    ADP1650_reg_write(I2C2_BASE_ADDR, 0x03, 0x74);
    ADP1650_reg_write(I2C2_BASE_ADDR, 0x04, 0x8F);
}

#endif
