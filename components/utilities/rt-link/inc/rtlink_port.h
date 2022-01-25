/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-02     xiangxistu   the first version
 * 2021-05-15     Sherman      function rename
 * 2021-07-13     Sherman      add reconnect API
 */
#ifndef __RT_LINK_PORT_H__
#define __RT_LINK_PORT_H__

#include <rtdef.h>

/* Functions that need to be implemented at the hardware */
rt_err_t rt_link_port_init(void);
rt_err_t rt_link_port_deinit(void);
rt_err_t rt_link_port_reconnect(void);
rt_size_t rt_link_port_send(void *data, rt_size_t length);

#ifdef RT_LINK_USING_HW_CRC
    rt_err_t rt_link_hw_crc32_init(void);
    rt_err_t rt_link_hw_crc32_deinit(void);
    rt_err_t rt_link_hw_crc32_reset(void);
    rt_uint32_t rt_link_hw_crc32(rt_uint8_t *data, rt_size_t u32_size)
#endif

/* Called when the hardware receives data and the data is transferred to RTLink */
rt_size_t rt_link_hw_write_cb(void *data, rt_size_t length);

#endif /* __RT_LINK_PORT_H__ */
