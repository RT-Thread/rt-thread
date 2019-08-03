/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-04     tyx          1st version
 */

#ifndef __DRV_FLASH_H__
#define __DRV_FLASH_H__

#include <rtthread.h>

int wm_flash_read(long offset, void *data, int size);
int wm_flash_write(long offset, void *data, int size);
int wm_flash_erase(long offset, int size);
int wm_flash_init(void);
rt_uint32_t wm_flash_total(void);
rt_uint32_t wm_flash_addr(void);
rt_uint32_t wm_flash_blksize(void);

#endif
