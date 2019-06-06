/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
<<<<<<< HEAD
 * 2018-11-15     SummerGift   change to new framework
=======
 * 2018-11-15     SummerGift   first version
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
 */

/*
 * NOTE: DO NOT include this file on the header file.
 */

<<<<<<< HEAD
#define DBG_ENABLE
#define DBG_COLOR

#ifndef LOG_TAG
#define DBG_SECTION_NAME               "drv"
#else
#define DBG_SECTION_NAME               LOG_TAG
#endif /* LOG_TAG */

#ifdef DRV_DEBUG
#define DBG_LEVEL                      DBG_LOG
#else
#define DBG_LEVEL                      DBG_INFO
=======
#ifndef LOG_TAG
#define DBG_TAG               "drv"
#else
#define DBG_TAG               LOG_TAG
#endif /* LOG_TAG */

#ifdef DRV_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#endif /* DRV_DEBUG */

#include <rtdbg.h>
