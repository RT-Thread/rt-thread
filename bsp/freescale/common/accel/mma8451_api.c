/*
 * Copyright (c) 2013-2015, Freescale Semiconductor, Inc.
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

#include <stdio.h>
#include <string.h>
#include "accel.h"
#include "mma8451_api.h"

/******************************************************************************
 * Code
 ******************************************************************************/
int32_t mma8451_init(accel_dev_t *dev)
{
    uint8_t val = 0;

    /* Put the mma8451 into standby mode */
    val = accel_read_reg(dev, kMMA8451_CTRL_REG1);
    val &= (uint8_t)(~(0x01));
    accel_write_reg(dev, kMMA8451_CTRL_REG1, val);

    /* Set the range, -4g to 4g */
    val = accel_read_reg(dev, kMMA8451_XYZ_DATA_CFG);
    val &= (uint8_t)(~0x03);
    val |= 0x01;
    accel_write_reg(dev, kMMA8451_XYZ_DATA_CFG, val);

    /* Set the F_MODE, disable FIFO */
    val = accel_read_reg(dev, kMMA8451_F_SETUP);
    val &= 0x3F;
    accel_write_reg(dev, kMMA8451_F_SETUP, val);

    /* Put the mma8451 into active mode */
    val = accel_read_reg(dev, kMMA8451_CTRL_REG1);
    val |= 0x01;
    val &= (uint8_t)(~0x02);               /* set F_READ to 0 */
    accel_write_reg(dev, kMMA8451_CTRL_REG1, val);

    return 0;
}


int32_t mma8451_read_sensor_data(const accel_dev_t * device, accel_sensor_data_t * accel)
{
    if (!accel)
    {
        return 0;
    }

    uint8_t ucStatus = 0;

    do {
        ucStatus = accel_read_reg(device, kMMA8451_STATUS);
    } while (!(ucStatus & 0x08));

    accel->mma8451_data.accelXMSB = accel_read_reg(device, kMMA8451_OUT_X_MSB);
    accel->mma8451_data.accelXLSB = accel_read_reg(device, kMMA8451_OUT_X_LSB);

    accel->mma8451_data.accelYMSB = accel_read_reg(device, kMMA8451_OUT_Y_MSB);
    accel->mma8451_data.accelYLSB = accel_read_reg(device, kMMA8451_OUT_Y_LSB);

    accel->mma8451_data.accelZMSB = accel_read_reg(device, kMMA8451_OUT_Z_MSB);
    accel->mma8451_data.accelZLSB = accel_read_reg(device, kMMA8451_OUT_Z_LSB);

    return 1;
}

/******************************************************************************
 * EOF
 ******************************************************************************/
