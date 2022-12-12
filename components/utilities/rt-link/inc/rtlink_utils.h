/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-15     Sherman      the first version
 */
#ifndef __RT_LINK_UTILITIES_H__
#define __RT_LINK_UTILITIES_H__

#include <rtthread.h>

/* Calculate the number of '1' */
int rt_link_utils_num1(rt_uint32_t n);

rt_err_t rt_link_sf_crc32_reset(void);
rt_uint32_t rt_link_sf_crc32(rt_uint8_t *data, rt_size_t len);

#endif /* __RT_LINK_UTILITIES_H__ */
