/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-11-18     greedyhao         first version
 */

#ifndef DRV_COMMON_H__
#define DRV_COMMON_H__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#define GET_PIN(PORTx,PIN) (uint8_t)__AB32_GET_PIN_##PORTx(PIN)

#endif // DRV_COMMON_H__
