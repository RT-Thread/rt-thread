/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __SCMI_SHMEM_H__
#define __SCMI_SHMEM_H__

#include <rtthread.h>
#include <rtdevice.h>

struct scmi_shared_mem;

rt_err_t scmi_shmem_msg_write(struct scmi_shared_mem *shmem, struct rt_scmi_msg *msg);
rt_err_t scmi_shmem_msg_read(struct scmi_shared_mem *shmem, struct rt_scmi_msg *msg);
void scmi_shmem_clear_channel(struct scmi_shared_mem *shmem);

#endif /* __SCMI_SHMEM_H__ */
