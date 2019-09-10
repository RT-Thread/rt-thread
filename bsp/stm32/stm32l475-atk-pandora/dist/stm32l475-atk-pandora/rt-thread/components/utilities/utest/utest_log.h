/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-19     MurphyZhao   the first version
 */

#ifndef __UTEST_LOG_H__
#define __UTEST_LOG_H__

#include <rtthread.h>

#define UTEST_DEBUG

#undef DBG_TAG
#undef DBG_LVL

#define DBG_TAG              "testcase"
#ifdef UTEST_DEBUG
#define DBG_LVL              DBG_LOG
#else
#define DBG_LVL              DBG_INFO
#endif
#include <rtdbg.h>

#define UTEST_LOG_ALL    (1u)
#define UTEST_LOG_ASSERT (2u)

void utest_log_lv_set(rt_uint8_t lv);

#endif /* __UTEST_LOG_H__ */
