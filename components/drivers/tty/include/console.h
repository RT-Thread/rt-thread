/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021.12.07     linzhenxing      first version
 */
#ifndef __CONSOLE_
#define __CONSOLE_
#include <rtthread.h>
#include "tty.h"

struct tty_struct *console_tty_get(void);
struct rt_device *console_get_iodev(void);
struct rt_device *console_set_iodev(struct rt_device *iodev);
rt_err_t console_register(const char *name, struct rt_device *iodev);
#endif
