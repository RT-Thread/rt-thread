/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AB32VG1_HAL_H__
#define AB32VG1_HAL_H__

#include "ab32vg1_hal_conf.h"

void hal_set_tick_hook(void (*hook)(uint32_t ticks));
void hal_set_ticks(uint32_t ticks);
void hal_mdelay(uint32_t nms);
void hal_udelay(uint16_t nus);
void hal_printf(const char *fmt, ...);

#endif
