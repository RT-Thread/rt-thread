/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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
#if !defined(__BOARD_I2C_H__)
#define __BOARD_I2C_H__

#include "sdk_types.h"
#include "i2c/imx_i2c.h"

////////////////////////////////////////////////////////////////////////////////
// Externs
////////////////////////////////////////////////////////////////////////////////

//! @name Audio codecs
//@{
extern const i2c_device_info_t g_wm8958_i2c_device;
extern const i2c_device_info_t g_wm8962_i2c_device;
extern const i2c_device_info_t g_sgtl5000_i2c_device;
extern const i2c_device_info_t g_cs42888_i2c_device;
//@}

//! @name PMICs
//@{
extern const i2c_device_info_t g_pmic_ltc3589_i2c_device;
extern const i2c_device_info_t g_pmic_da9053_i2c_device;
extern const i2c_device_info_t g_pmic_pf0100_i2c_device;
extern const i2c_device_info_t g_pmic_max17135_i2c_device;
//@}

//! @brief ADV7180 video decoder
extern const i2c_device_info_t g_adv7180_i2c_device;

//! @brief OS81050 MLB MOST controller
extern const i2c_device_info_t g_os81050_i2c_device;

//! @brief P1003 touch screen controller
extern const i2c_device_info_t g_p1003_tsc_i2c_device;

//! @brief AT24Cxx EEPROM
extern const i2c_device_info_t g_at24cx_i2c_device;

//! @brief Si476x FM tuner
extern const i2c_device_info_t g_si476x_i2c_device;

//! @brief MMA8451 accelerometer.
extern const i2c_device_info_t g_mma8451_i2c_device;

#endif // __BOARD_I2C_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
