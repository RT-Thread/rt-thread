/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
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

#include <string.h>
#include "accelerometer/mma8451.h"

//! @brief I2C related constants for the MMA8451.
enum _mma8451_i2c_constants
{
    kMMA8451_I2C_Address = 0x1c,
    kMMA8451_I2C_Address_With_SAO_Set = kMMA8451_I2C_Address | 1
};

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

uint8_t mma8451_read_register(const mma8451_device_t * device, uint8_t reg_addr)
{
    imx_i2c_request_t rq = {0};
    uint8_t buf[1];

    rq.device = &device->addressInfo;
    rq.reg_addr = reg_addr;
    rq.reg_addr_sz = 1;
    rq.buffer_sz = 1;
    rq.buffer = buf;
    
    i2c_read(&rq);

    return buf[0];
}

int mma8451_write_register(const mma8451_device_t * device, uint8_t reg_addr, uint8_t reg_val)
{
    imx_i2c_request_t rq = {0};
    uint8_t buf[1];

    buf[0] = reg_val;

    rq.device = &device->addressInfo;
    rq.reg_addr = reg_addr;
    rq.reg_addr_sz = 1;
    rq.buffer_sz = 1;
    rq.buffer = buf;

    return i2c_write(&rq);
}

int mma8451_init(mma8451_device_t * device, const i2c_device_info_t * address)
{
    // Clear device struct.
    memset(device, 0, sizeof(*device));
    
    // Check the I2C address.
    if (address->address != kMMA8451_I2C_Address && address->address != kMMA8451_I2C_Address_With_SAO_Set)
    {
        return kMMA8451_Invalid_I2C_Address_Error;
    }
    
    // Save I2C device info struct.
    device->addressInfo = *address;
    
    // Init the I2C port.
    i2c_init(device->addressInfo.port, address->freq);

    unsigned char val = 0;
    
    // Read WHO_AM_I register.
    val = mma8451_read_register(device, kMMA8451_WHO_AM_I);
    if (val != kMMA8451_WHO_AM_I_Device_ID)
    {
        printf("MMA8451: Unexpected result from WHO_AM_I (0x%02x)\n", val);
        return 1;
    }

    // Put the mma8451 into standby mode 
    val = mma8451_read_register(device, kMMA8451_CTRL_REG1);
    val &= ~(0x01);
    mma8451_write_register(device, kMMA8451_CTRL_REG1, val);

    // Set the range, -8g to 8g 
    val = mma8451_read_register(device, kMMA8451_XYZ_DATA_CFG);
    val &= ~0x03;
    val |= 0x02;
    mma8451_write_register(device, kMMA8451_XYZ_DATA_CFG, val);

    // Set the F_MODE, disable FIFO 
    val = mma8451_read_register(device, kMMA8451_F_SETUP);
    val &= 0x3F;
    mma8451_write_register(device, kMMA8451_F_SETUP, val);

    // Put the mma8451 into active mode 
    val = mma8451_read_register(device, kMMA8451_CTRL_REG1);
    val |= 0x01;
    val &= ~0x02;               //set F_READ to 0
    mma8451_write_register(device, kMMA8451_CTRL_REG1, val);
    
    return SUCCESS;
}

int mma8451_get_acceleration(const mma8451_device_t * device, acceleration_t * accel)
{
    if (!accel)
    {
        return 0;
    }
    
    uint8_t ucVal1 = 0;
    uint8_t ucVal2 = 0;
    uint8_t ucStatus = 0;
    uint16_t iTemp = 0;
    int sign = 1;
//     char signch = '+';
    
    do {
        ucStatus = mma8451_read_register(device, kMMA8451_STATUS);
    } while (!(ucStatus & 0x08));

    ucVal1 = mma8451_read_register(device, kMMA8451_OUT_X_MSB);
    ucVal2 = mma8451_read_register(device, kMMA8451_OUT_X_LSB);
    sign = (ucVal1 & 0x80) ? (-1) : 1;
    iTemp = ((ucVal1 & 0x7F) << 6) + ((ucVal2) >> 2);
    if (sign == -1)             //2's completement
        iTemp = (~iTemp + 1) & 0x1FFF;
//     signch = (sign == -1) ? '-' : '+';
    accel->x = (float)(iTemp * sign) * 8.0 / 8192.0;
//     printf("\r 	  The acceleration is: (%c%01d.%02dg, ",
//            signch, iTemp * 8 / 0x2000, (iTemp & 0x3FF) * 800 / 0x2000);

    ucVal1 = mma8451_read_register(device, kMMA8451_OUT_Y_MSB);
    ucVal2 = mma8451_read_register(device, kMMA8451_OUT_Y_LSB);
    sign = (ucVal1 & 0x80) ? (-1) : 1;
    iTemp = ((ucVal1 & 0x7F) << 6) + ((ucVal2) >> 2);
    if (sign == -1)             //2's completement
        iTemp = (~iTemp + 1) & 0x1FFF;
//     signch = (sign == -1) ? '-' : '+';
    accel->y = (float)(iTemp * sign) * 8.0 / 8192.0;
//     printf(" %c%01d.%02dg, ", signch, iTemp * 8 / 0x2000, (iTemp & 0x3FF) * 800 / 0x2000);

    ucVal1 = mma8451_read_register(device, kMMA8451_OUT_Z_MSB);
    ucVal2 = mma8451_read_register(device, kMMA8451_OUT_Z_LSB);
    sign = (ucVal1 & 0x80) ? (-1) : 1;
    iTemp = ((ucVal1 & 0x7F) << 6) + ((ucVal2) >> 2);
    if (sign == -1)             //2's completement
        iTemp = (~iTemp + 1) & 0x1FFF;
//     signch = (sign == -1) ? '-' : '+';
    accel->z = (float)(iTemp * sign) * 8.0 / 8192.0;
//     printf(" %c%01d.%02dg)", signch, iTemp * 8 / 0x2000, (iTemp & 0x3FF) * 800 / 0x2000);

    return SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
