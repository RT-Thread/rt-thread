/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-10-19     ChuShicheng       first version
 */

#ifndef __DRV_FLASH_H__
#define __DRV_FLASH_H__

#include <rtthread.h>

int _flash_read(rt_uint32_t addr, rt_uint8_t *buf, size_t size);
int _flash_write(rt_uint32_t addr, const rt_uint8_t *buf, size_t size);
int _flash_erase(rt_uint32_t addr, size_t size);

#endif  /* __DRV_FLASH_H__ */
