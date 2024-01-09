/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
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
