/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-27     flybreak     the first version.
 */

#include "mutex"

namespace std
{
    // use a set of global and static objects
    // a proxy function to pthread_once

    function<void()> once_functor;

    mutex& get_once_mutex()
    {
        static mutex once_mutex;
        return once_mutex;
    }

    inline unique_lock<mutex>*& get_once_functor_lock_ptr()
    {
        static unique_lock<mutex>* once_functor_mutex_ptr = nullptr;
        return once_functor_mutex_ptr;
    }

    void set_once_functor_lock_ptr(unique_lock<mutex>* m_ptr)
    {
        get_once_functor_lock_ptr() = m_ptr;
    }

    extern "C"  
    {
        void once_proxy()
        {
            // need to first transfer the functor's ownership so as to call it
            function<void()> once_call = std::move(once_functor);

            // no need to hold the lock anymore
            unique_lock<mutex>* lock_ptr = get_once_functor_lock_ptr();            
            get_once_functor_lock_ptr() = nullptr;
            lock_ptr->unlock();

            once_call();
        }
    }
}
