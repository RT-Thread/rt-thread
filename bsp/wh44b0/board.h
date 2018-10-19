/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-23     Bernard      first version
 * 2006-09-24     Bernard      add rt_hw_finsh_init declaration
 */

#ifndef __BOARD_H__
#define __BOARD_H__

void rt_hw_board_init(void);
void rt_hw_led_set(rt_uint32_t led);
void rt_hw_led_flash(void);

#ifdef RT_USING_FINSH
void rt_hw_finsh_init(void);
#endif

#endif
