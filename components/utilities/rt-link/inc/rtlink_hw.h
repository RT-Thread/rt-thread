/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-02     xiangxistu   the first version
 * 2021-07-13     Sherman      add reconnect API
 *
 */
#ifndef __RT_LINK_HW_H__
#define __RT_LINK_HW_H__

#include <rtdef.h>

rt_size_t rt_link_hw_recv_len(struct rt_link_receive_buffer *buffer);
void rt_link_hw_copy(rt_uint8_t *dst, rt_uint8_t *src, rt_size_t count);
void rt_link_hw_buffer_point_shift(rt_uint8_t **pointer_address, rt_size_t length);

rt_err_t rt_link_hw_init(void);
rt_err_t rt_link_hw_deinit(void);
rt_err_t rt_link_hw_reconnect(void);
rt_size_t rt_link_hw_send(void *data, rt_size_t length);

#endif /* _RT_LINK_PORT_INTERNAL_H_ */
