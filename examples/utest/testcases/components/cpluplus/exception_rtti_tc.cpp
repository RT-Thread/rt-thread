/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-06     liukang      the first version
 */

#include <rtthread.h>
#include "utest.h"
#include <exception>
#include <stdexcept>
#include <typeinfo>
#include <typeindex>

static void test_exception_throwcatch(void)
{
    std::string result;
    try {
        throw std::logic_error("logic_exception");
    } catch (const std::exception& e) {
        result = e.what();
    } catch (...) {
        result = "...";
    }

    if (result != "logic_exception")
    {
        uassert_false(1);
    }

    result = "";
    try {
        throw std::string("string_exception");
    } catch (const std::exception& e) {
        result = e.what();
    } catch (...) {
        result = "...";
    }

    if (result != "...")
    {
        uassert_false(1);
    }
    uassert_true(1);
}

static std::string handle_eptr(std::exception_ptr eptr) // passing by value is ok
{
    try {
        if (eptr) {
            std::rethrow_exception(eptr);
        }
    } catch(const std::exception& e) {
        return e.what();
    }
    return "";
}

static void test_exception_capture(void)
{
    std::exception_ptr eptr;
    try {
        throw std::logic_error("logic_exception");
    } catch (...) {
        eptr = std::current_exception(); // capture
    }
    auto what = handle_eptr(eptr);

    if (what != "logic_exception")
    {
        uassert_false(1);
    }
    uassert_true(1);
}

static void test_exception_typeid_and_info(void)
{
    std::string str;
    const std::type_info& info1 = typeid(str);
    const std::type_info& info2 = typeid(std::string);

    if (info2 != info1)
    {
        uassert_false(1);
    }

    if (info1.hash_code() != info2.hash_code())
    {
        uassert_false(1);
    }

    if (std::type_index(info1) != std::type_index(info2))
    {
        uassert_false(1);
    }
    uassert_true(1);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_exception_throwcatch);
    // UTEST_UNIT_RUN(test_exception_capture);
    UTEST_UNIT_RUN(test_exception_typeid_and_info);
}
UTEST_TC_EXPORT(testcase, "components.cplusplus.exception_rtti_tc", utest_tc_init, utest_tc_cleanup, 10);
