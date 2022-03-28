/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-27     flybreak     the first version.
 */

#include "condition_variable"

namespace std
{
    void condition_variable::wait(unique_lock<mutex>& lock)
    {
        int err = pthread_cond_wait(&_m_cond, lock.mutex()->native_handle());

        if (err)
        {
            throw_system_error(err, "condition_variable::wait: failed to wait on a condition");
        }
    }

    void notify_all_at_thread_exit(condition_variable& cond, unique_lock<mutex> lk)
    {
        // TLS currently not available
        mutex* mut = lk.release();
        mut->unlock();
        cond.notify_all();
    }


} // namespace std
