/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-5      SummerGift   first version
 */

#ifndef __DRV_FLASH_H__
#define __DRV_FLASH_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>

int stm32_flash_read(long offset, rt_uint8_t *buf, size_t size);
int stm32_flash_write(long offset, const rt_uint8_t *buf, size_t size);
int stm32_flash_erase(long offset, size_t size);

#endif  /* __DRV_FLASH_H__ */
