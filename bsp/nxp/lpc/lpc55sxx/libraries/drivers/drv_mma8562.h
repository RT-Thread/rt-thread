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

/*!
 * @file
 * @brief Public interface for the MMA8562 accelerometer driver.
 * @ingroup diag_accel
 */

#ifndef __MMA8562_H__
#define __MMA8562_H__

#include "stdint.h"

//! @addtogroup diag_accel
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Error codes for the MMA8562 driver.
enum _mma8562_errors
{
    kMMA8562_Invalid_I2C_Address_Error = -128
};

//! @brief Register definitions for the MMA8562.
enum _mma8562_constants
{
    kMMA8562_STATUS = 0x00,
    kMMA8562_OUT_X_MSB = 0x01,
    kMMA8562_OUT_X_LSB = 0x02,
    kMMA8562_OUT_Y_MSB = 0x03,
    kMMA8562_OUT_Y_LSB = 0x04,
    kMMA8562_OUT_Z_MSB = 0x05,
    kMMA8562_OUT_Z_LSB = 0x06,
    kMMA8562_F_SETUP = 0x09,
    kMMA8562_TRIG_CFG = 0x0a,
    kMMA8562_SYSMOD = 0x0b,
    kMMA8562_INT_SOURCE = 0x0c,
    kMMA8562_WHO_AM_I = 0x0d,
    kMMA8562_WHO_AM_I_Device_ID = 0x4a,
    kMMA8562_XYZ_DATA_CFG = 0x0e,
    kMMA8562_CTRL_REG1 = 0x2a,
    kMMA8562_CTRL_REG2 = 0x2b,
    kMMA8562_CTRL_REG3 = 0x2c,
    kMMA8562_CTRL_REG4 = 0x2d,
    kMMA8562_CTRL_REG5 = 0x2e
};

//! @brief 3D acceleration values.
typedef struct _acceleration {
    int16_t x;
    int16_t y;
    int16_t z;
} acceleration_t;

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

extern int mma8562_hw_init(void);

extern void get_mma8562(uint8_t data);

extern rt_err_t mma8562_read_reg(rt_uint8_t reg, rt_uint8_t len, rt_uint8_t *buf);

extern rt_err_t mma8562_write_reg(rt_uint8_t reg, rt_uint8_t data);

#if defined(__cplusplus)
}
#endif

//! @}

#endif //__MMA8562_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
