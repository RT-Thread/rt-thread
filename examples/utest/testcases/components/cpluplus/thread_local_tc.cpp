// /*
//  * Copyright (c) 2006-2019, RT-Thread Development Team
//  *
//  * SPDX-License-Identifier: Apache-2.0
//  *
//  * Change Logs:
//  * Date           Author       Notes
//  * 2021-09-03     liukang      the first version
//  */

// #include <rtthread.h>
// #include "utest.h"
// #include <thread>
// #include <atomic>

// static thread_local int g_tls_count = 123;

// static void test_thread_local(void)
// {
//     auto func = [&]() mutable
//     {
//         rt_kprintf("g_tls_count: %d\n", g_tls_count);
//         if (g_tls_count != 123)
//         {
//             uassert_false(1);
//         }
//         for (int i = 0; i < 100; ++i)
//         {
//             ++g_tls_count;
//         }
//         if (g_tls_count != 223)
//         {
//             rt_kprintf("g_tls_count: %d\n", g_tls_count);
//             uassert_false(1);
//         }
//     };

//     if (g_tls_count != 123)
//     {
//         rt_kprintf("g_tls_count: %d\n", g_tls_count);
//         uassert_false(1);
//     }

//     std::thread t1(func);
//     t1.join();

//     std::thread t2(func);
//     t2.join();

//     if (g_tls_count != 123)
//     {
//         uassert_false(1);
//     }

//     uassert_true(1);
// }

// static std::atomic<int> &get_atomic_x()
// {
//     static std::atomic<int> ai(0);
//     return ai;
// }

// static std::atomic<int> &get_atomic_y()
// {
//     static std::atomic<int> ai(0);
//     return ai;
// }

// struct Object
// {
//     explicit Object(int value_) : value(value_)
//     {
//         get_atomic_x() += 1;
//     }
//     ~Object()
//     {
//         get_atomic_y() += 1;
//     }

//     int value;
// };

// static thread_local Object g_tls_object(123);

// static void test_thread_local_object(void)
// {
//     auto func = [&]() mutable
//     {
//         if (g_tls_object.value != 123)
//         {
//             uassert_false(1);
//         }

//         for (int i = 0; i < 100; ++i)
//         {
//             ++g_tls_object.value;
//         }

//         if (g_tls_object.value != 223)
//         {
//             uassert_false(1);
//         }
//     };

//     if (g_tls_object.value != 123)
//     {
//         uassert_false(1);
//     }

//     if (get_atomic_x().load() != 1)
//     {
//         uassert_false(1);
//     }
//     if (get_atomic_y().load() != 0)
//     {
//         uassert_false(1);
//     }

//     std::thread t1(func);
//     t1.join();
//     if (get_atomic_x().load() != 2)
//     {
//         uassert_false(1);
//     }
//     if (get_atomic_y().load() != 1)
//     {
//         uassert_false(1);
//     }
//     std::thread t2(func);
//     t2.join();
//     if (get_atomic_x().load() != 3)
//     {
//         uassert_false(1);
//     }
//     if (get_atomic_y().load() != 2)
//     {
//         uassert_false(1);
//     }

//     std::thread t3([] {});
//     t3.join();
//     if (get_atomic_x().load() != 3)
//     {
//         uassert_false(1);
//     }
//     if (get_atomic_y().load() != 2)
//     {
//         uassert_false(1);
//     }

//     if (g_tls_object.value != 123)
//     {
//         uassert_false(1);
//     }

//     uassert_true(1);
// }

// static rt_err_t utest_tc_init(void)
// {
//     return RT_EOK;
// }

// static rt_err_t utest_tc_cleanup(void)
// {
//     return RT_EOK;
// }

// static void testcase(void)
// {
//     UTEST_UNIT_RUN(test_thread_local);
//     UTEST_UNIT_RUN(test_thread_local_object);
// }
// UTEST_TC_EXPORT(testcase, "components.cplusplus.thread_local_tc", utest_tc_init, utest_tc_cleanup, 10);
