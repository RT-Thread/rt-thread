/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-01     Shell        Porting to RTT API
 */
#ifndef __LIBADT_RT_UTHASH_H__
#define __LIBADT_RT_UTHASH_H__

#include <rtthread.h>

#define uthash_malloc(sz)    rt_malloc(sz)
#define uthash_free(ptr, sz) rt_free(ptr)

/**
 * for performance consideration, using libc implementations
 * as the default case. If you care about the compatibility
 * problem, define the RT_UTHASH_CONFIG_COMPATIBILITY_FIRST
 * before including the rt_uthash.h.
 */
#ifndef RT_UTHASH_CONFIG_COMPATIBILITY_FIRST
#define uthash_bzero(a, n) memset(a, '\0', n)
#define uthash_strlen(s)   strlen(s)

#else
#define uthash_bzero(a, n) rt_memset(a, '\0', n)
#define uthash_strlen(s)   rt_strlen(s)

#endif /* RT_UTHASH_CONFIG_COMPATIBILITY_FIRST */

/* if any fatal happen, throw an exception and return a failure */
#define uthash_fatal(msg)  \
    do                     \
    {                      \
        LOG_E(msg);        \
        return -RT_ENOMEM; \
    } while (0)

#include "uthash.h"

#define DEFINE_RT_UTHASH_TYPE(entry_name, key_type, key_name) \
    typedef struct entry_name                                 \
    {                                                         \
        key_type key_name;                                    \
        UT_hash_handle hh;                                    \
    } *entry_name##_t;

#define RT_UTHASH_ADD(head, key_member, keylen_in, value) \
    HASH_ADD(hh, head, key_member, keylen_in, value)
#define RT_UTHASH_FIND(head, key_ptr, keylen_in, pval) \
    HASH_FIND(hh, head, key_ptr, keylen_in, pval)
#define RT_UTHASH_DELETE(head, pobj) HASH_DELETE(hh, head, pobj)

#endif /* __LIBADT_RT_UTHASH_H__ */
