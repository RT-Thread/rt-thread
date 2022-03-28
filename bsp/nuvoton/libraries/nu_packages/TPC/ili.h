/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-25     Wayne        the first version
 */

#ifndef __ILI_H__
#define __ILI_H__

#include "touch.h"

int rt_hw_ili_tpc_init(const char *name, struct rt_touch_config *cfg);

#endif /* ili2130.h */
