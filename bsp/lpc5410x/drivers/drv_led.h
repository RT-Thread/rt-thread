/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __DRV_LED_H__
#define __DRV_LED_H__

int rt_led_hw_init(void);
void Led_Control(rt_uint32_t Set_led, rt_uint32_t value);

#endif
