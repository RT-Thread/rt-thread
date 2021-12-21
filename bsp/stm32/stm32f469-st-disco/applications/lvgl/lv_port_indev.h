/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-18     Meco Man     The first version
 */
#ifndef LV_PORT_INDEV_H
#define LV_PORT_INDEV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lv_hal_indev.h>

extern lv_indev_t * button_indev;

void lv_port_indev_init(void);
void lv_port_indev_input(rt_int16_t x, rt_int16_t y, lv_indev_state_t state);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
