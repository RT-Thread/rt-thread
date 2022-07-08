/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-21     shelton      first version
 */

/*
 * NOTE: DO NOT include this file on the header file.
 */

#ifndef LOG_TAG
#define DBG_TAG                         "drv"
#else
#define DBG_TAG                         LOG_TAG
#endif /* LOG_TAG */

#ifdef DRV_DEBUG
#define DBG_LVL                         DBG_LOG
#else
#define DBG_LVL                         DBG_INFO
#endif /* DRV_DEBUG */

#include <rtdbg.h>
