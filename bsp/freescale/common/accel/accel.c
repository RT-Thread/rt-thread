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
#include <stdio.h>
#include <string.h>
#include "accel.h"
#include "mma8451_api.h"
#include "fxos_api.h"
#include "fsl_debug_console.h"


#define kAccel_WHO_AM_I     0x0d

/******************************************************************************
 * Code
 ******************************************************************************/
uint8_t accel_read_reg(const accel_dev_t *dev, uint8_t reg_addr)
{
    uint8_t outVal = 0;

    if (dev->i2c->i2c_read(dev->bus, &dev->slave, &reg_addr, 1,
                &outVal, 1, 200) == kStatus_I2C_Success)
    {
        return outVal;
    }
    else
    {
        return 0;
    }
}

int32_t accel_write_reg(const accel_dev_t *dev, uint8_t reg_addr, uint8_t reg_val)
{
    if (dev->i2c->i2c_write(dev->bus, &dev->slave, &reg_addr, 1,
                &reg_val, 1, 200) == kStatus_I2C_Success)
    {
        return 0;
    }
    else
    {
        return -1;
    }

}

int32_t accel_init(accel_dev_t *dev)
{
    uint8_t val = 0;
    int8_t error = 0;
    if (!dev)
    {
        PRINTF("No Device founded!\r\n");
        error = -1;
    }

    if (!dev->i2c)
    {
        PRINTF("No I2C interface founded!\r\n");
        error = -1;
    }
    if(!error)
    {
        /* Init i2c */
        dev->i2c->i2c_init(dev->bus, &dev->state);

        /* Read WHO_AM_I register. */
        val = accel_read_reg(dev, kAccel_WHO_AM_I);

        switch (val) {
        case kMMA8451_WHO_AM_I_Device_ID:
        dev->accel->accel_init = mma8451_init;
        dev->accel->accel_read_sensor_data = mma8451_read_sensor_data;
        val = ACCEL_MMA8451;
        break;
        case kFXOS_WHO_AM_I_Device_ID:
        dev->accel->accel_init = fxos_init;
        dev->accel->accel_read_sensor_data = fxos_read_sensor_data;
        val = ACCEL_FXOS;
        break;
        default:
        PRINTF("Accel: Unexpected result from WHO_AM_I (0x%02x)\r\n", val);
        error = -1;
        }
        if(!error) dev->accel->accel_init(dev);
    }

    return error;
}

/******************************************************************************
 * EOF
 ******************************************************************************/

