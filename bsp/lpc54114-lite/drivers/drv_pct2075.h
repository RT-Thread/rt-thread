/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
#ifndef __DRV_PCT2075_H__ 
#define __DRV_PCT2075_H__ 

#include <rtthread.h> 
#include <rtdevice.h> 

int rt_hw_pct2075_init(void);
float pct2075_read(void);

#endif
