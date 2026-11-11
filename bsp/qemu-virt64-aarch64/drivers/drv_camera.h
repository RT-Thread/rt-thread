/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-07     GuEe-GUI     the first version
 */

#ifndef __DRV_CAMERA_H__
#define __DRV_CAMERA_H__

#include <rthw.h>
#include <rtthread.h>

#define RT_DEVICE_CTRL_CAMERA_GET_WIDTH         (RT_DEVICE_CTRL_BASE(Char) + 'V' + 1)
#define RT_DEVICE_CTRL_CAMERA_GET_HEIGHT        (RT_DEVICE_CTRL_BASE(Char) + 'V' + 2)
#define RT_DEVICE_CTRL_CAMERA_GET_FRAMEBUFFER   (RT_DEVICE_CTRL_BASE(Char) + 'V' + 3)

#endif /* __DRV_CAMERA_H__ */
