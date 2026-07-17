/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 * 2026-06-16     li.mengmeng      implement for N32H7xx
 */

#ifndef __DRV_FLASH_H7XX_H__
#define __DRV_FLASH_H7XX_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>

#ifdef __cplusplus
extern "C" {
#endif

int n32_flash_read(rt_uint32_t addr, rt_uint8_t *buf, size_t size);
int n32_flash_write(rt_uint32_t addr, const rt_uint8_t *buf, size_t size);
int n32_flash_erase(rt_uint32_t addr, size_t size);

#ifdef __cplusplus
}
#endif

#endif  /* __DRV_FLASH_H7XX_H__ */
