/*******************************************************************************
* Copyright (C) 2019 Maxim Integrated Products, Inc., All Rights Reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
* OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of Maxim Integrated
* Products, Inc. shall not be used except as stated in the Maxim Integrated
* Products, Inc. Branding Policy.
*
* The mere transfer of this software does not imply any licenses
* of trade secrets, proprietary technology, copyrights, patents,
* trademarks, maskwork rights, or any other form of intellectual
* property whatsoever. Maxim Integrated Products, Inc. retains all
* ownership rights.
*******************************************************************************
* @file MAX31875.h
*******************************************************************************
*/
#ifndef MAX31875_H
#define MAX31875_H
#include <stdint.h>

#define MAX31875_NO_ERROR   0
#define MAX31875_ERROR      -1

#define MAX31875_REG_TEMPERATURE      0X00
#define MAX31875_REG_CONFIGURATION    0X01
#define MAX31875_REG_THYST_LOW_TRIP   0X02
#define MAX31875_REG_TOS_HIGH_TRIP    0X03
#define MAX31875_REG_MAX              0X03

#define MAX31875_CFG_ONE_SHOT_START   (1) /* Start one-shot measurement */

#define MAX31875_CFG_CONV_RATE_0_25   (0x00 << 1) /* 0.25 conversions/sec */
#define MAX31875_CFG_CONV_RATE_1      (0x01 << 1) /* 1.0 conversions/sec */
#define MAX31875_CFG_CONV_RATE_4      (0x02 << 1) /* 4.0 conversions/sec */
#define MAX31875_CFG_CONV_RATE_8      (0x03 << 1) /* 8.0 conversions/sec */
#define MAX31875_WAIT_CONV_RATE_0_25 (4.002)
#define MAX31875_WAIT_CONV_RATE_1    (1.0)
#define MAX31875_WAIT_CONV_RATE_4    (0.25)
#define MAX31875_WAIT_CONV_RATE_8    (0.125)

#define MAX31875_CFG_RESOLUTION_9BIT  (0x00 << 5)
#define MAX31875_CFG_RESOLUTION_10BIT (0x01 << 5)
#define MAX31875_CFG_RESOLUTION_11BIT (0x02 << 5)
#define MAX31875_CFG_RESOLUTION_12BIT (0x03 << 5)

#define MAX31875_CFG_NORMAL_FORMAT    (0X00 << 7)
#define MAX31875_CFG_EXTENDED_FORMAT  (0X01 << 7)

#define MAX31875_CFG_CONTINUOUS       (0X00 << 8)
#define MAX31875_CFG_SHUTDOWN         (0X01 << 8)

#define MAX31875_CFG_COMPARATOR_MODE  (0X00 << 9)
#define MAX31875_CFG_INTERRUPT_MODE   (0X01 << 9)


#define MAX31875_CFG_FAULT_FILTER_1   (0x00 << 11)
#define MAX31875_CFG_FAULT_FILTER_2   (0x01 << 11)
#define MAX31875_CFG_FAULT_FILTER_4   (0x02 << 11)
#define MAX31875_CFG_FAULT_FILTER_6   (0x03 << 11)

#define MAX31875_CFG_OVER_TEMP_MASK   (0x80)


#define MAX31875_I2C_SLAVE_ADR_R0 (0x90 >> 1) // code uses the 7 bit address
#define MAX31875_I2C_SLAVE_ADR_R1 (0x92 >> 1)
#define MAX31875_I2C_SLAVE_ADR_R2 (0x94 >> 1)
#define MAX31875_I2C_SLAVE_ADR_R3 (0x96 >> 1)
#define MAX31875_I2C_SLAVE_ADR_R4 (0x98 >> 1)
#define MAX31875_I2C_SLAVE_ADR_R5 (0x9A >> 1)
#define MAX31875_I2C_SLAVE_ADR_R6 (0x9C >> 1)
#define MAX31875_I2C_SLAVE_ADR_R7 (0x9E >> 1)

#define MAX31875_CF_NORMAL_FORMAT (0.00390625F)
#define MAX31875_CF_EXTENDED_FORMAT (0.0078125F)

/** @union max31875_raw_data
 * @brief union data structure for byte word manipulations
 */
typedef union
{
    struct
    {
        uint8_t lsb;
        uint8_t msb;
    } s_lm;
    struct
    {
        uint16_t magnitude_bits: 15;
        uint16_t sign_bit: 1;
    } s_ms;
    uint16_t uwrd;
    int16_t swrd;
} max31875_raw_data;

#define MAX31875_U16_MAX     ((uint16_t)~0U)
#define MAX31875_S16_MAX     ((int16_t)(MAX31875_U16_MAX>>1))
#define MAX31875_S16_MIN     ((int16_t)(-MAX31875_S16_MAX - 1))

#endif/* MAX31875_H */
