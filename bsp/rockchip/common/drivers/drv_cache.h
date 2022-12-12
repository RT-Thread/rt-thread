/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    drv_cache.h
  * @version V0.1
  * @brief   cpu cache interface
  *
  * Change Logs:
  * Date           Author          Notes
  * 2019-04-01     Cliff.Chen      first implementation
  *
  ******************************************************************************
  */
#ifndef __DRV_CACHE_H__
#define __DRV_CACHE_H__

#include <rtthread.h>

int rt_hw_cpu_cache_init(void);
#endif
