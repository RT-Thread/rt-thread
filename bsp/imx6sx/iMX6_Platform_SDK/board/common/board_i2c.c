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

#include "sdk.h"
#include "board_i2c.h"
#include "registers/regsi2c.h"

////////////////////////////////////////////////////////////////////////////////
// Globals
////////////////////////////////////////////////////////////////////////////////

const i2c_device_info_t g_wm8958_i2c_device = { HW_I2C2, (0x34 >> 1), 100000 };

const i2c_device_info_t g_wm8962_i2c_device = { HW_I2C1, (0x34 >> 1), 48000 };

const i2c_device_info_t g_sgtl5000_i2c_device = { HW_I2C2, 0x0a, 100000 };

#if defined (BOARD_EVB)
const i2c_device_info_t g_cs42888_i2c_device = { HW_I2C1, (0x90 >> 1), 100000 };
#else
const i2c_device_info_t g_cs42888_i2c_device = { HW_I2C2, (0x90 >> 1), 100000 };
#endif

const i2c_device_info_t g_pmic_ltc3589_i2c_device = { HW_I2C2, (0x68 >> 1), 170000 };

const i2c_device_info_t g_pmic_da9053_i2c_device = { HW_I2C1, (0x90 >> 1), 170000 };

const i2c_device_info_t g_pmic_max17135_i2c_device = { HW_I2C1, (0x90 >> 1), 170000 };

const i2c_device_info_t g_pmic_pf0100_i2c_device = { HW_I2C2, (0x10 >> 1), 170000 };


#if defined(BOARD_EVB)
const i2c_device_info_t g_adv7180_i2c_device = { HW_I2C1, (0x42 >> 1), 50000 };
#else
const i2c_device_info_t g_adv7180_i2c_device = { HW_I2C3, (0x42 >> 1), 50000 };
#endif


const i2c_device_info_t g_os81050_i2c_device = { HW_I2C3, (0x40 >> 1), 50000 };

#if defined(BOARD_SMART_DEVICE)
const i2c_device_info_t g_p1003_tsc_i2c_device = { HW_I2C3, (0x8 >> 1), 50000 };
#else
const i2c_device_info_t g_p1003_tsc_i2c_device = { HW_I2C2, (0x8 >> 1), 50000 };
#endif

const i2c_device_info_t g_at24cx_i2c_device = { HW_I2C3, (0xa0 >> 1), 170000 };

const i2c_device_info_t g_si476x_i2c_device = { HW_I2C2, (0xC6 >> 1), 50000 };

#if defined(BOARD_SMART_DEVICE)
const i2c_device_info_t g_mma8451_i2c_device = { HW_I2C1, 0x1C, 170000 };
#elif defined(BOARD_SABRE_AI)
const i2c_device_info_t g_mma8451_i2c_device = { HW_I2C3, 0x1C, 170000 };
#endif

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
