/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __SCMI_AGENT_H__
#define __SCMI_AGENT_H__

#include <rtthread.h>
#include <rtdevice.h>

#include "shmem.h"

struct scmi_agent;

struct scmi_agent_ops
{
    const char *name;

    rt_err_t (*setup)(struct scmi_agent *agent, struct rt_device *dev);
    rt_err_t (*process_msg)(struct scmi_agent *agent, struct rt_scmi_msg *msg);
};

struct scmi_agent
{
    const struct scmi_agent_ops *ops;

    void *priv;
};

#endif /* __SCMI_AGENT_H__ */
