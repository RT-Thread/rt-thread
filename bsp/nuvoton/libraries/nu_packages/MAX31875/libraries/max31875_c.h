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
* @file max31875_c.h
*******************************************************************************
*/
#ifndef MAX31875_C_H
#define MAX31875_C_H

#include <stdint.h>
#include <stdio.h>
#include "max31875.h"

//Define I2C class to instead of mbed API.
typedef struct
{
    uint32_t address;
    int (*read)(int address, const char *reg, int reg_length, char *data, int length);
    int (*write)(int address, const char *data, int length);
} S_MAX31875;

/*****************************************************************************/
/*  C header for MAX31875 driver                                             */
/*****************************************************************************/

int max31875_init(uint8_t slaveAddress);

int max31875_read_reg(uint16_t *value, char reg, S_MAX31875 *psObj);

float max31875_read_reg_as_temperature(uint8_t reg, S_MAX31875 *psObj);

int max31875_write_reg(uint16_t value, char reg, S_MAX31875 *psObj);

int max31875_write_cfg(uint16_t cfg, S_MAX31875 *psObj);

int max31875_write_trip_low(float temperature, S_MAX31875 *psObj);

int max31875_write_trip_high(float temperature, S_MAX31875 *psObj);

float max31875_celsius_to_fahrenheit(float temp_c);

#endif/* MAX31875_C_H */
