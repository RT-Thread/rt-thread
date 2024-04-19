/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-10-23     zhangyan     first version
 *
 */

#ifndef LOG_TAG
    #define DBG_TAG               "drv"
#else
    #define DBG_TAG               LOG_TAG
#endif /* LOG_TAG */

#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_ERROR
#endif /* DRV_DEBUG */

#include <rtdbg.h>
