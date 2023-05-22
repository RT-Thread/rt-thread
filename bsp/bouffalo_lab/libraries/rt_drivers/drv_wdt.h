/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-03-14     wcx1024979076 first version
 */

#ifndef __DRV_WDT_H__
#define __DRV_WDT_H__

#include "board.h"
#include "bflb_wdg.h"
#include "bflb_clock.h"
#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>

int rt_hw_wdt_init(void);

#endif /* __DRV_WDT_H__ */
