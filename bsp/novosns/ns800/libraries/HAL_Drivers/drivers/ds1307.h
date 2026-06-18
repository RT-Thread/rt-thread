/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-18     coworkspace  first version
 */
#ifndef __DS1307_H__
#define __DS1307_H__

#include <rtthread.h>
#include <time.h>

rt_err_t ds1307_init(void);
rt_err_t ds1307_get_time(struct tm *time);
rt_err_t ds1307_set_time(struct tm *time);

#endif
