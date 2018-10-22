/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __BOARD_H__
#define __BOARD_H__


#define MCK		50000000

void rt_hw_board_led_on(rt_uint32_t);
void rt_hw_board_led_off(rt_uint32_t);
void rt_hw_board_init(void);

#endif
