/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __VIRTIO_INTERNAL_H__
#define __VIRTIO_INTERNAL_H__

#include <drivers/virtio.h>
#include <drivers/core/dm.h>

rt_inline rt_bool_t virtio_legacy_is_little_endian(void)
{
#ifdef ARCH_CPU_BIG_ENDIAN
    return RT_FALSE;
#else
    return RT_TRUE;
#endif
}

rt_inline rt_bool_t virtio_is_little_endian(struct rt_virtio_device *vdev)
{
    return rt_virtio_has_feature(vdev, VIRTIO_F_VERSION_1) ||
            virtio_legacy_is_little_endian();
}

#ifdef __CHECKER__
#define FORCE __attribute__((force))
#else
#define FORCE
#endif

rt_inline rt_uint16_t virtio16_to_cpu(struct rt_virtio_device *vdev, rt_uint16_t val)
{
    if (virtio_is_little_endian(vdev))
    {
        return rt_le16_to_cpu((FORCE rt_le16_t)val);
    }
    else
    {
        return rt_be16_to_cpu((FORCE rt_be16_t)val);
    }
}

rt_inline rt_uint16_t cpu_to_virtio16(struct rt_virtio_device *vdev, rt_uint16_t val)
{
    if (virtio_is_little_endian(vdev))
    {
        return (FORCE rt_le16_t)rt_cpu_to_le16(val);
    }
    else
    {
        return (FORCE rt_be16_t)rt_cpu_to_be16(val);
    }
}

rt_inline rt_uint32_t virtio32_to_cpu(struct rt_virtio_device *vdev, rt_uint32_t val)
{
    if (virtio_is_little_endian(vdev))
    {
        return rt_le32_to_cpu((FORCE rt_le32_t)val);
    }
    else
    {
        return rt_be32_to_cpu((FORCE rt_be32_t)val);
    }
}

rt_inline rt_uint32_t cpu_to_virtio32(struct rt_virtio_device *vdev, rt_uint32_t val)
{
    if (virtio_is_little_endian(vdev))
    {
        return (FORCE rt_le32_t)rt_cpu_to_le32(val);
    }
    else
    {
        return (FORCE rt_be32_t)rt_cpu_to_be32(val);
    }
}

rt_inline rt_uint64_t virtio64_to_cpu(struct rt_virtio_device *vdev, rt_uint64_t val)
{
    if (virtio_is_little_endian(vdev))
    {
        return rt_le64_to_cpu((FORCE rt_le64_t)val);
    }
    else
    {
        return rt_be64_to_cpu((FORCE rt_be64_t)val);
    }
}

rt_inline rt_uint64_t cpu_to_virtio64(struct rt_virtio_device *vdev, rt_uint64_t val)
{
    if (virtio_is_little_endian(vdev))
    {
        return (FORCE rt_le64_t)rt_cpu_to_le64(val);
    }
    else
    {
        return (FORCE rt_be64_t)rt_cpu_to_be64(val);
    }
}

#undef FORCE

#endif /* __VIRTIO_INTERNAL_H__ */
