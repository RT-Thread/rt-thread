/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#ifndef __DRV_FLASH_H__
#define __DRV_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

int air32_flash_read(rt_uint32_t addr, rt_uint8_t *buf, rt_size_t size);
int air32_flash_write(rt_uint32_t addr, const rt_uint8_t *buf, rt_size_t size);
int air32_flash_erase(rt_uint32_t addr, rt_size_t size);

#ifdef __cplusplus
}
#endif

#endif  /* __DRV_FLASH_H__ */
