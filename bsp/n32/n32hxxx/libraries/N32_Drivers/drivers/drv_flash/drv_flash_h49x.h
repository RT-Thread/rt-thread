/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-08-07     li.mengmeng      implement for N32H49x
 */

#ifndef __DRV_FLASH_H49X_H__
#define __DRV_FLASH_H49X_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

int n32_flash_read(rt_uint32_t addr, rt_uint8_t *buf, size_t size);
int n32_flash_write(rt_uint32_t addr, const rt_uint8_t *buf, size_t size);
int n32_flash_erase(rt_uint32_t addr, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_FLASH_H49X_H__ */
