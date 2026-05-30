/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#define DBG_TAG "scmi.shmem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "shmem.h"

struct scmi_shared_mem
{
    rt_le32_t reserved;
    rt_le32_t channel_status;
#define SCMI_SHMEM_CHAN_STAT_CHANNEL_ERROR  rt_cpu_to_le32(RT_BIT(1))
#define SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE   rt_cpu_to_le32(RT_BIT(0))
    rt_le32_t reserved1[2];
    rt_le32_t flags;
#define SCMI_SHMEM_FLAG_INTR_ENABLED        rt_cpu_to_le32(RT_BIT(0))
    rt_le32_t length;
    rt_le32_t msg_header;
    rt_uint8_t msg_payload[];
};

rt_err_t scmi_shmem_msg_write(struct scmi_shared_mem *shmem,
        struct rt_scmi_msg *msg)
{
    if (!shmem || !msg)
    {
        return -RT_EINVAL;
    }

    if ((!msg->in_msg && msg->in_msg_size) || (!msg->out_msg && msg->out_msg_size))
    {
        return -RT_EINVAL;
    }

    if (!(shmem->channel_status & SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE))
    {
        LOG_E("Channel busy");

        return -RT_EBUSY;
    }

    /* Load message in shared memory */
    shmem->channel_status &= ~SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE;
    shmem->length = rt_cpu_to_le32(msg->in_msg_size + sizeof(shmem->msg_header));
    shmem->msg_header = rt_cpu_to_le32(scmi_header(
            msg->message_id, 0, msg->sdev->protocol_id, 0));

    if (msg->in_msg)
    {
        rt_memcpy(shmem->msg_payload, msg->in_msg, msg->in_msg_size);
    }

    return RT_EOK;
}

rt_err_t scmi_shmem_msg_read(struct scmi_shared_mem *shmem, struct rt_scmi_msg *msg)
{
    rt_size_t length;

    if (!shmem || !msg)
    {
        return -RT_EINVAL;
    }

    if (!(shmem->channel_status & SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE))
    {
        LOG_E("Channel unexpectedly busy");

        return -RT_EBUSY;
    }

    if (shmem->channel_status & SCMI_SHMEM_CHAN_STAT_CHANNEL_ERROR)
    {
        LOG_E("Channel error reported, reset channel");

        return -RT_EIO;
    }

    length = rt_le32_to_cpu(shmem->length);

    if (length > msg->out_msg_size + sizeof(shmem->msg_header))
    {
        LOG_E("Buffer < %u too small", length);

        return -RT_EINVAL;
    }

    msg->out_msg_size = length - sizeof(shmem->msg_header);

    rt_memcpy(msg->out_msg, shmem->msg_payload, msg->out_msg_size);

    return RT_EOK;
}

void scmi_shmem_clear_channel(struct scmi_shared_mem *shmem)
{
    if (shmem)
    {
        shmem->channel_status &= ~SCMI_SHMEM_CHAN_STAT_CHANNEL_ERROR;
    }
}
