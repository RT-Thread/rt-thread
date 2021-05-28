/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-19     MurphyZhao   the first version
 */

#include <rtthread.h>
#include <string.h>
#include <stdlib.h>

#include "utest.h"
#include <utest_log.h>

#undef DBG_TAG
#undef DBG_LVL

#define DBG_TAG          "utest"
#ifdef UTEST_DEBUG
#define DBG_LVL          DBG_LOG
#else
#define DBG_LVL          DBG_INFO
#endif
#include <rtdbg.h>

#if RT_CONSOLEBUF_SIZE < 256
#error "RT_CONSOLEBUF_SIZE is less than 256!"
#endif

#ifdef UTEST_THR_STACK_SIZE
#define UTEST_THREAD_STACK_SIZE UTEST_THR_STACK_SIZE
#else
#define UTEST_THREAD_STACK_SIZE (4096)
#endif

#ifdef UTEST_THR_PRIORITY
#define UTEST_THREAD_PRIORITY   UTEST_THR_PRIORITY
#else
#define UTEST_THREAD_PRIORITY   FINSH_THREAD_PRIORITY
#endif

static rt_uint8_t utest_log_lv = UTEST_LOG_ALL;
static utest_tc_export_t tc_table = RT_NULL;
static rt_size_t tc_num;
static rt_uint32_t tc_loop;
static struct utest local_utest = {UTEST_PASSED, 0, 0};

#if defined(__ICCARM__) || defined(__ICCRX__)         /* for IAR compiler */
#pragma section="UtestTcTab"
#endif

void utest_log_lv_set(rt_uint8_t lv)
{
    if (lv == UTEST_LOG_ALL || lv == UTEST_LOG_ASSERT)
    {
        utest_log_lv = lv;
    }
}

int utest_init(void)
{
    /* initialize the utest commands table.*/
#if defined(__CC_ARM) || defined(__CLANG_ARM)       /* ARM C Compiler */
    extern const int UtestTcTab$$Base;
    extern const int UtestTcTab$$Limit;
    tc_table = (utest_tc_export_t)&UtestTcTab$$Base;
    tc_num = (utest_tc_export_t)&UtestTcTab$$Limit - tc_table;
#elif defined (__ICCARM__) || defined(__ICCRX__)    /* for IAR Compiler */
    tc_table = (utest_tc_export_t)__section_begin("UtestTcTab");
    tc_num = (utest_tc_export_t)__section_end("UtestTcTab") - tc_table;
#elif defined (__GNUC__)                            /* for GCC Compiler */
    extern const int __rt_utest_tc_tab_start;
    extern const int __rt_utest_tc_tab_end;
    tc_table = (utest_tc_export_t)&__rt_utest_tc_tab_start;
    tc_num = (utest_tc_export_t) &__rt_utest_tc_tab_end - tc_table;
#endif

    LOG_I("utest is initialize success.");
    LOG_I("total utest testcase num: (%d)", tc_num);
    return tc_num;
}
INIT_COMPONENT_EXPORT(utest_init);

static void utest_tc_list(void)
{
    rt_size_t i = 0;

    LOG_I("Commands list : ");

    for (i = 0; i < tc_num; i++)
    {
        LOG_I("[testcase name]:%s; [run timeout]:%d", tc_table[i].name, tc_table[i].run_timeout);
    }
}
MSH_CMD_EXPORT_ALIAS(utest_tc_list, utest_list, output all utest testcase);

static const char *file_basename(const char *file)
{
    char *end_ptr = RT_NULL;
    char *rst = RT_NULL;

    if (!((end_ptr = strrchr(file, '\\')) != RT_NULL || \
        (end_ptr = strrchr(file, '/')) != RT_NULL) || \
        (rt_strlen(file) < 2))
    {
        rst = (char *)file;
    }
    else
    {
        rst = (char *)(end_ptr + 1);
    }
    return (const char *)rst;
}

static int utest_help(void)
{
    rt_kprintf("\n");
    rt_kprintf("Command: utest_run\n");
    rt_kprintf("   info: Execute test cases.\n");
    rt_kprintf(" format: utest_run [-thread or -help] [testcase name] [loop num]\n");
    rt_kprintf("  usage:\n");
    rt_kprintf("         1. utest_run\n");
    rt_kprintf("            Do not specify a test case name. Run all test cases.\n");
    rt_kprintf("         2. utest_run -thread\n");
    rt_kprintf("            Do not specify a test case name. Run all test cases in threaded mode.\n");
    rt_kprintf("         3. utest_run testcaseA\n");
    rt_kprintf("            Run 'testcaseA'.\n");
    rt_kprintf("         4. utest_run testcaseA 10\n");
    rt_kprintf("            Run 'testcaseA' ten times.\n");
    rt_kprintf("         5. utest_run -thread testcaseA\n");
    rt_kprintf("            Run 'testcaseA' in threaded mode.\n");
    rt_kprintf("         6. utest_run -thread testcaseA 10\n");
    rt_kprintf("            Run 'testcaseA' ten times in threaded mode.\n");
    rt_kprintf("         7. utest_run test*\n");
    rt_kprintf("            support '*' wildcard. Run all test cases starting with 'test'.\n");
    rt_kprintf("         8. utest_run -help\n");
    rt_kprintf("            Show utest help information\n");
    rt_kprintf("\n");
    return 0;
}

static void utest_run(const char *utest_name)
{
    rt_size_t i;
    rt_uint32_t index;
    rt_bool_t is_find;

    rt_thread_mdelay(1000);

    for (index = 0; index < tc_loop; index ++)
    {
        i = 0;
        is_find = RT_FALSE;
        LOG_I("[==========] [ utest    ] loop %d/%d", index + 1, tc_loop);
        LOG_I("[==========] [ utest    ] started");
        while(i < tc_num)
        {
            if (utest_name)
            {
                int len = strlen(utest_name);
                if (utest_name[len - 1] == '*')
                {
                    len -= 1;
                }
                if (rt_memcmp(tc_table[i].name, utest_name, len) != 0)
                {
                    i++;
                    continue;
                }
            }
            is_find = RT_TRUE;

            LOG_I("[----------] [ testcase ] (%s) started", tc_table[i].name);
            if (tc_table[i].init != RT_NULL)
            {
                if (tc_table[i].init() != RT_EOK)
                {
                    LOG_E("[  FAILED  ] [ result   ] testcase (%s)", tc_table[i].name);
                    goto __tc_continue;
                }
            }

            if (tc_table[i].tc != RT_NULL)
            {
                tc_table[i].tc();
                if (local_utest.failed_num == 0)
                {
                    LOG_I("[  PASSED  ] [ result   ] testcase (%s)", tc_table[i].name);
                }
                else
                {
                    LOG_E("[  FAILED  ] [ result   ] testcase (%s)", tc_table[i].name);
                }
            }
            else
            {
                LOG_E("[  FAILED  ] [ result   ] testcase (%s)", tc_table[i].name);
            }

            if (tc_table[i].cleanup != RT_NULL)
            {
                if (tc_table[i].cleanup() != RT_EOK)
                {
                    LOG_E("[  FAILED  ] [ result   ] testcase (%s)", tc_table[i].name);
                    goto __tc_continue;
                }
            }

    __tc_continue:
            LOG_I("[----------] [ testcase ] (%s) finished", tc_table[i].name);

            i++;
        }

        if (i == tc_num && is_find == RT_FALSE && utest_name != RT_NULL)
        {
            LOG_I("[==========] [ utest    ] Not find (%s)", utest_name);
            LOG_I("[==========] [ utest    ] finished");
            break;
        }

        LOG_I("[==========] [ utest    ] finished");
    }
}

static void utest_testcase_run(int argc, char** argv)
{
    void *thr_param = RT_NULL;

    static char utest_name[UTEST_NAME_MAX_LEN];
    rt_memset(utest_name, 0x0, sizeof(utest_name));

    tc_loop = 1;

    if (argc == 1)
    {
        utest_run(RT_NULL);
        return;
    }
    else if (argc == 2 || argc == 3 || argc == 4)
    {
        if (rt_strcmp(argv[1], "-thread") == 0)
        {
            rt_thread_t tid = RT_NULL;
            if (argc == 3 || argc == 4)
            {
                rt_strncpy(utest_name, argv[2], sizeof(utest_name) -1);
                thr_param = (void*)utest_name;

                if (argc == 4) tc_loop = atoi(argv[3]);
            }
            tid = rt_thread_create("utest",
                                    (void (*)(void *))utest_run, thr_param,
                                    UTEST_THREAD_STACK_SIZE, UTEST_THREAD_PRIORITY, 10);
            if (tid != NULL)
            {
                rt_thread_startup(tid);
            }
        }
        else if (rt_strcmp(argv[1], "-help") == 0)
        {
            utest_help();
        }
        else
        {
            rt_strncpy(utest_name, argv[1], sizeof(utest_name) -1);
            if (argc == 3) tc_loop = atoi(argv[2]);
            utest_run(utest_name);
        }
    }
    else
    {
        LOG_E("[  error   ] at (%s:%d), in param error.", __func__, __LINE__);
        utest_help();
    }
}
MSH_CMD_EXPORT_ALIAS(utest_testcase_run, utest_run, utest_run [-thread or -help] [testcase name] [loop num]);

utest_t utest_handle_get(void)
{
    return (utest_t)&local_utest;
}

void utest_unit_run(test_unit_func func, const char *unit_func_name)
{
    // LOG_I("[==========] utest unit name: (%s)", unit_func_name);
    local_utest.error = UTEST_PASSED;
    local_utest.passed_num = 0;
    local_utest.failed_num = 0;

    if (func != RT_NULL)
    {
        func();
    }
}

void utest_assert(int value, const char *file, int line, const char *func, const char *msg)
{
    if (!(value))
    {
        local_utest.error = UTEST_FAILED;
        local_utest.failed_num ++;
        LOG_E("[  ASSERT  ] [ unit     ] at (%s); func: (%s:%d); msg: (%s)", file_basename(file), func, line, msg);
    }
    else
    {
        if (utest_log_lv == UTEST_LOG_ALL)
        {
            LOG_D("[    OK    ] [ unit     ] (%s:%d) is passed", func, line);
        }
        local_utest.error = UTEST_PASSED;
        local_utest.passed_num ++;
    }
}

void utest_assert_string(const char *a, const char *b, rt_bool_t equal, const char *file, int line, const char *func, const char *msg)
{
    if (a == RT_NULL || b == RT_NULL)
    {
        utest_assert(0, file, line, func, msg);
    }

    if (equal)
    {
        if (rt_strcmp(a, b) == 0)
        {
            utest_assert(1, file, line, func, msg);
        }
        else
        {
            utest_assert(0, file, line, func, msg);
        }
    }
    else
    {
        if (rt_strcmp(a, b) == 0)
        {
            utest_assert(0, file, line, func, msg);
        }
        else
        {
            utest_assert(1, file, line, func, msg);
        }
    }
}

void utest_assert_buf(const char *a, const char *b, rt_size_t sz, rt_bool_t equal, const char *file, int line, const char *func, const char *msg)
{
    if (a == RT_NULL || b == RT_NULL)
    {
        utest_assert(0, file, line, func, msg);
    }

    if (equal)
    {
        if (rt_memcmp(a, b, sz) == 0)
        {
            utest_assert(1, file, line, func, msg);
        }
        else
        {
            utest_assert(0, file, line, func, msg);
        }
    }
    else
    {
        if (rt_memcmp(a, b, sz) == 0)
        {
            utest_assert(0, file, line, func, msg);
        }
        else
        {
            utest_assert(1, file, line, func, msg);
        }
    }
}
