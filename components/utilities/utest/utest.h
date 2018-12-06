/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-19     MurphyZhao   the first version
 */

#ifndef __UTEST_H__
#define __UTEST_H__

#include <rtthread.h>
#include "utest_log.h"

#define UTEST_SW_VERSION                  "0.0.1"

enum utest_error
{
    UTEST_PASSED  = 0,
    UTEST_FAILED  = 1,
    UTEST_SKIPPED = 2
};
typedef enum utest_error utest_err_e;

struct utest
{
    utest_err_e error;
    uint32_t passed_num;
    uint32_t failed_num;
};
typedef struct utest *utest_t;

struct utest_tc_export {
    const char  *name;
    uint32_t     run_timeout;
    rt_err_t   (*init)(void);
    void       (*tc)(void);
    rt_err_t   (*cleanup)(void);
};
typedef struct utest_tc_export *utest_tc_export_t;

typedef void (*test_unit_func)(void);

#define TC_LOG_I(...)  LOG_I(__VA_ARGS__)
#define TC_LOG_D(...)  LOG_D(__VA_ARGS__)
#define TC_LOG_E(...)  LOG_E(__VA_ARGS__)
#define TC_LOG_W(...)  LOG_W(__VA_ARGS__)

void utest_unit_run(test_unit_func func, const char *unit_func_name);
utest_t utest_handle_get(void);

#define UTEST_NAME_MAX_LEN (128u)

#define UTEST_TC_EXPORT(testcase, name, init, cleanup, timeout)                \
    RT_USED static const struct utest_tc_export _utest_testcase                \
    SECTION("UtestTcTab") =                                                    \
    {                                                                          \
        name,                                                                  \
        timeout,                                                               \
        init,                                                                  \
        testcase,                                                              \
        cleanup                                                                \
    }

#define UTEST_UNIT_RUN(test_unit_func)                                         \
    utest_unit_run(test_unit_func, #test_unit_func);                           \
    if(utest_handle_get()->failed_num != 0) return;

#endif
