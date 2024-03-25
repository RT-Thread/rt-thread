/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-02     Shell        init ver.
 */
#ifndef __FS_PTYFS_H__
#define __FS_PTYFS_H__
#include <rtthread.h>

typedef rt_base_t ptsno_t;

ptsno_t ptyfs_register_pts(rt_device_t ptmx, rt_device_t pts);

rt_err_t ptyfs_unregister_pts(rt_device_t ptmx, ptsno_t ptsno);

const char *ptyfs_get_rootpath(rt_device_t ptmx);

#endif /* __FS_PTYFS_H__ */
