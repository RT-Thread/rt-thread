/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-04     Haley        the first version
 */

#ifndef __SMBUS_H_
#define __SMBUS_H_

#include <rtthread.h>

/**
 * @brief External function definitions
 *
 */
int rt_hw_smbus_init(void);
rt_uint8_t am_smbus_tx_then_tx(rt_uint8_t SlaveAddress, rt_uint8_t command, rt_uint8_t* pBuffer, rt_uint16_t bytesNumber);
rt_uint8_t am_smbus_tx_then_rx(rt_uint8_t SlaveAddress, rt_uint8_t command, rt_uint8_t* pBuffer, rt_uint16_t bytesNumber);
void am_smbus_scl_high(void);
void am_smbus_scl_low(void);

#endif // __SMBUS_H_
