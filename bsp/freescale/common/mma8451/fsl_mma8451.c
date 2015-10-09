/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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
#include "fsl_mma8451.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

uint8_t mma8451_read_register(mma8451_device_t * device, uint8_t reg_addr)
{
    uint8_t buf[1]={0};

    I2C_DRV_MasterReceiveDataBlocking(device->i2cInstance, &device->i2cDevice, &reg_addr ,1, buf, sizeof(buf),1000U);

    return buf[0];
}

mma8451_status_t mma8451_write_register(mma8451_device_t * device, uint8_t reg_addr, uint8_t reg_val)
{
    I2C_DRV_MasterSendDataBlocking(device->i2cInstance, &device->i2cDevice, &reg_addr ,1, &reg_val, sizeof(reg_val),1000U);
    return kStatus_Success;
}

mma8451_status_t mma8451_init(mma8451_device_t * device)
{
    uint8_t val = 0;
        /* The master structure initialize */
    I2C_DRV_MasterInit(device->i2cInstance, &device->state);
    /* Configure the device info of I2C */
    I2C_DRV_MasterSetBaudRate(device->i2cInstance, &device->i2cDevice);

    /* Put the mma8451 into standby mode */
    val = mma8451_read_register(device, kMMA8451_CTRL_REG1);
    val &= ~(0x01U);
    mma8451_write_register(device, kMMA8451_CTRL_REG1, val);

    /* Set the range, -4g to 4g */
    val = mma8451_read_register(device, kMMA8451_XYZ_DATA_CFG);
    val &= ~0x03U;
    val |= 0x01;
    mma8451_write_register(device, kMMA8451_XYZ_DATA_CFG, val);

    /* Set the F_MODE, disable FIFO */
    val = mma8451_read_register(device, kMMA8451_F_SETUP);
    val &= 0x3F;
    mma8451_write_register(device, kMMA8451_F_SETUP, val);

    /* Put the mma8451 into active mode */
    val = mma8451_read_register(device, kMMA8451_CTRL_REG1);
    val |= 0x01;
    val &= ~0x02U;               /*set F_READ to 0*/
    mma8451_write_register(device, kMMA8451_CTRL_REG1, val);

    return kStatus_Success;
}

mma8451_status_t mma8451_get_acceleration(mma8451_device_t * device, acceleration_t * accel)
{
    if (!accel)
    {
        return kStatusFail;
    }

    uint8_t ucVal1 = 0;
    uint8_t ucVal2 = 0;
    uint8_t ucStatus = 0;

    do {
        ucStatus = mma8451_read_register(device, kMMA8451_STATUS);
    } while (!(ucStatus & 0x08));

    ucVal1 = mma8451_read_register(device, kMMA8451_OUT_X_MSB);
    ucVal2 = mma8451_read_register(device, kMMA8451_OUT_X_LSB);
    accel->x = (int16_t)(ucVal1<<8|ucVal2);

    ucVal1 = mma8451_read_register(device, kMMA8451_OUT_Y_MSB);
    ucVal2 = mma8451_read_register(device, kMMA8451_OUT_Y_LSB);
    accel->y = (int16_t)(ucVal1<<8|ucVal2);

    ucVal1 = mma8451_read_register(device, kMMA8451_OUT_Z_MSB);
    ucVal2 = mma8451_read_register(device, kMMA8451_OUT_Z_LSB);
    accel->z = (int16_t)(ucVal1<<8|ucVal2);

    return kStatus_Success;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
