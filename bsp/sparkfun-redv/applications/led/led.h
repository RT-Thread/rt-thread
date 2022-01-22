/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-10-28     luhuadong         first version
 */

#ifndef __LED_H__
#define __LED_H__

#define LED_ON          1
#define LED_OFF         0

void led_init(void);
void led_set(rt_uint8_t val);
void led_toggle(void);

#endif /* __LED_H__ */
