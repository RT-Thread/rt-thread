/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-12     armink       first version
 */

/*
 * NOTE: DO NOT include this file on the header file.
 */

#define DBG_ENABLE
#define DBG_COLOR

#ifndef LOG_TAG
#define DBG_SECTION_NAME               "at"
#else
#define DBG_SECTION_NAME               LOG_TAG
#endif /* LOG_TAG */

#ifdef AT_DEBUG
#define DBG_LEVEL                      DBG_LOG
#else
#define DBG_LEVEL                      DBG_INFO
#endif /* AT_DEBUG */

#include <rtdbg.h>
