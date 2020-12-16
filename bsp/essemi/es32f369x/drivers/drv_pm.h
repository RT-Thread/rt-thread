/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-04-01     wangyq        the first version
 */

#ifndef DRV_PM_H__
#define DRV_PM_H__

#include <rthw.h>
#include <board.h>
#include <rtdevice.h>
#include <ald_cmu.h>
#include <ald_pmu.h>
#include "shell.h"

int rt_hw_pm_init(void);

extern void save_register(void *p_head,uint32_t size,void *p_save);
 
extern void load_register(void *p_head,uint32_t size,void *p_load);

#endif
