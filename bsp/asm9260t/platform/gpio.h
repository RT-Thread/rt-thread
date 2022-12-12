/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-04-14     ArdaFu      first version
 */
#ifndef __GPIO_H__
#define __GPIO_H__

extern void HW_SetPinMux(rt_uint8_t port, rt_uint8_t pin, rt_uint8_t mux_type);
extern void HW_GpioSetDir(rt_uint8_t port, rt_uint8_t pin, rt_uint8_t isOut);
extern void HW_GpioSetVal(rt_uint8_t port, rt_uint8_t pin);
extern void HW_GpioClrVal(rt_uint8_t port, rt_uint8_t pin);
#endif
