/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2024-07-26     Ltbonewstart  the first version
 *
 */
#ifndef __DRV_CHIPFLASH_H__
#define __DRV_CHIPFLASH_H__

#include <rtthread.h>
#include <rtdevice.h>

extern rt_err_t rt_onchipflash_init(const char* mtd_name);

#endif
