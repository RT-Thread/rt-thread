/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-27     flybreak     the first version.
 */

#pragma once

#include <cstdlib>
#include <system_error>
#include <chrono>
#include <ratio>

#include <rtthread.h>

#define RT_USING_CPP_EXCEPTION

inline void throw_system_error(int err, const char *what_msg)
{
#ifdef RT_USING_CPP_EXCEPTION
    throw std::system_error(std::error_code(err, std::system_category()), what_msg);
#else
    (void)err;
    (void)what_msg;
    ::abort();
#endif
}

class tick_clock
{
public:
    typedef clock_t rep;
    typedef std::ratio<1, RT_TICK_PER_SECOND> period;

    typedef std::chrono::duration<tick_clock::rep, tick_clock::period> duration;
    typedef std::chrono::time_point<tick_clock> time_point;

    constexpr static bool is_ready = true;

    static time_point now();
};

class real_time_clock
{
public:
    typedef std::chrono::nanoseconds duration;
    typedef duration::rep rep;
    typedef duration::period period;
    typedef std::chrono::time_point<real_time_clock, duration> time_point;

    static constexpr bool is_steady = true;

    static time_point
    now() noexcept;
};
