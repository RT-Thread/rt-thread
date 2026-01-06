/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-01     Shell        Init ver.
 */

#include "lwp_futex_internal.h"

static struct shared_futex_entry *_futex_hash_head;

/**
 * @brief Add a futex to the global hash table
 *
 * @param[in] key Pointer to the shared futex key structure
 * @param[in] futex The futex to be added to the table
 *
 * @return rt_err_t Returns RT_EOK on success, error code on failure
 */
rt_err_t futex_global_table_add(struct shared_futex_key *key, rt_futex_t futex)
{
    rt_err_t rc = 0;
    struct shared_futex_entry *entry = &futex->entry;
    futex->entry.key.mobj = key->mobj;
    futex->entry.key.offset = key->offset;

    RT_UTHASH_ADD(_futex_hash_head, key, sizeof(struct shared_futex_key), entry);
    return rc;
}

/**
 * @brief Find a futex in the global hash table
 *
 * @param[in] key Pointer to the shared futex key structure
 * @param[out] futex Pointer to store the found futex
 *
 * @return rt_err_t Returns RT_EOK if found, -RT_ENOENT if not found
 */
rt_err_t futex_global_table_find(struct shared_futex_key *key, rt_futex_t *futex)
{
    rt_err_t rc;
    rt_futex_t found_futex;
    struct shared_futex_entry *entry;

    RT_UTHASH_FIND(_futex_hash_head, key, sizeof(struct shared_futex_key), entry);
    if (entry)
    {
        rc = RT_EOK;
        found_futex = rt_container_of(entry, struct rt_futex, entry);
    }
    else
    {
        rc = -RT_ENOENT;
        found_futex = RT_NULL;
    }

    *futex = found_futex;
    return rc;
}

/**
 * @brief Delete a futex from the global hash table
 *
 * @param[in] key Pointer to the shared futex key structure
 *
 * @return rt_err_t Returns RT_EOK if deleted successfully, -RT_ENOENT if not found
 */
rt_err_t futex_global_table_delete(struct shared_futex_key *key)
{
    rt_err_t rc;
    struct shared_futex_entry *entry;

    RT_UTHASH_FIND(_futex_hash_head, key, sizeof(struct shared_futex_key), entry);
    if (entry)
    {
        RT_UTHASH_DELETE(_futex_hash_head, entry);
        rc = RT_EOK;
    }
    else
    {
        rc = -RT_ENOENT;
    }

    return rc;
}
