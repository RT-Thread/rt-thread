/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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
#include "utest_assert.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * utest_error
 *
 * @brief Test result.
 *
 * @member UTEST_PASSED Test success.
 * @member UTEST_FAILED Test failed.
 * @member UTEST_PASSED Test skipped.
 *
*/
enum utest_error
{
    UTEST_PASSED  = 0,
    UTEST_FAILED  = 1,
    UTEST_SKIPPED = 2
};
typedef enum utest_error utest_err_e;

/**
 * utest
 *
 * @brief utest data structure.
 *
 * @member error      Error number from enum `utest_error`.
 * @member passed_num Total number of tests passed.
 * @member failed_num Total number of tests failed.
 *
*/
struct utest
{
    utest_err_e error;
    uint32_t passed_num;
    uint32_t failed_num;
};
typedef struct utest *utest_t;

/**
 * utest_tc_export
 *
 * @brief utest testcase data structure.
 *        Will export the data to `UtestTcTab` section in flash.
 *
 * @member name        Testcase name.
 * @member run_timeout Testcase maximum test time (Time unit: seconds).
 * @member init        Necessary initialization before executing the test case function.
 * @member tc          Total number of tests failed.
 * @member cleanup     Total number of tests failed.
 *
*/
struct utest_tc_export {
    const char  *name;
    uint32_t     run_timeout;
    rt_err_t   (*init)(void);
    void       (*tc)(void);
    rt_err_t   (*cleanup)(void);
};
typedef struct utest_tc_export *utest_tc_export_t;

/**
 * test_unit_func
 *
 * @brief Unit test handler function pointer.
 *
*/
typedef void (*test_unit_func)(void);

/**
 * utest_unit_run
 *
 * @brief Unit test function executor.
 *        No need for the user to call this function directly
 *
 * @param func           Unit test function.
 * @param unit_func_name Unit test function name.
 *
 * @return void
 *
*/
void utest_unit_run(test_unit_func func, const char *unit_func_name);

/**
 * utest_handle_get
 *
 * @brief Get the utest data structure handle.
 *        No need for the user to call this function directly
 *
 * @param void
 *
 * @return utest_t type. (struct utest *)
 *
*/
utest_t utest_handle_get(void);

/**
 * UTEST_NAME_MAX_LEN
 *
 * @brief Testcase name maximum length.
 *
*/
#define UTEST_NAME_MAX_LEN (128u)

/**
 * UTEST_TC_EXPORT
 *
 * @brief Export testcase function to `UtestTcTab` section in flash.
 *        Used in application layer.
 *
 * @param testcase The testcase function.
 * @param name     The testcase name.
 * @param init     The initialization function of the test case.
 * @param cleanup  The cleanup function of the test case.
 * @param timeout  Testcase maximum test time (Time unit: seconds).
 *
 * @return None
 *
*/
#ifdef _MSC_VER
#pragma section("UtestTcTab$f",read)
#define UTEST_TC_EXPORT(testcase, name, init, cleanup, timeout)                \
    __declspec(allocate("UtestTcTab$f"))                                       \
    static const struct utest_tc_export _utest_testcase =                      \
    {                                                                          \
        name,                                                                  \
        timeout,                                                               \
        init,                                                                  \
        testcase,                                                              \
        cleanup                                                                \
     }
#pragma comment(linker, "/merge:UtestTcTab=tctext")
#else
#define UTEST_TC_EXPORT(testcase, name, init, cleanup, timeout)                \
    rt_used static const struct utest_tc_export _utest_testcase                \
    rt_section("UtestTcTab") =                                                 \
    {                                                                          \
        name,                                                                  \
        timeout,                                                               \
        init,                                                                  \
        testcase,                                                              \
        cleanup                                                                \
    }
#endif /* _MSC_VER */

/**
 * UTEST_UNIT_RUN
 *
 * @brief Unit test function executor.
 *        Used in `testcase` function in application.
 *
 * @param test_unit_func Unit test function
 *
 * @return None
 *
*/
#define UTEST_UNIT_RUN(test_unit_func)                                         \
    utest_unit_run(test_unit_func, #test_unit_func);                           \
    if(utest_handle_get()->failed_num != 0) return;

#ifdef __cplusplus
}
#endif

#endif /* __UTEST_H__ */
