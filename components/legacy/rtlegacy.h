/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-14     Meco Man     the first version
 */

#ifndef __RT_LEGACY_H__
#define __RT_LEGACY_H__

#include <rtconfig.h>
#include <rtdef.h>

/* legacy version macros */
#define RT_VERSION              RT_VERSION_MAJOR        /**< major version number */
#define RT_SUBVERSION           RT_VERSION_MINOR        /**< minor version number */
#define RT_REVISION             RT_VERSION_PATCH        /**< revise version number */

/* IPC */
#ifdef RT_USING_DEVICE_IPC
#include "ipc/workqueue_legacy.h"
#endif /* RT_USING_DEVICE_IPC */

/* FinSH */

#endif /* __RT_LEGACY_H__ */
