/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __VIRTIO_SCMI_H__
#define __VIRTIO_SCMI_H__

#define VIRTIO_SCMI_F_P2A_CHANNELS  0   /* Device implements some SCMI notifications, or delayed responses. */
#define VIRTIO_SCMI_F_SHARED_MEMORY 1   /* Device implements any SCMI statistics shared memory region */

rt_packed(struct virtio_scmi_request
{
    rt_le32_t hdr;
    rt_uint8_t params[];
});

rt_packed(struct virtio_scmi_response
{
    rt_le32_t hdr;
    rt_uint8_t ret_values[];
});

rt_packed(struct virtio_scmi_event_msg
{
    rt_le32_t hdr;
    rt_uint8_t payload[];
});

#endif /* __VIRTIO_SCMI_H__ */
