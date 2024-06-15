/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-10     Bernard      The first version of rewrite dfs
 */
#include <rtthread.h>

#include "dfs.h"
#include "dfs_file.h"
#include "dfs_private.h"
#include "dfs_dentry.h"
#include "dfs_mnt.h"

#define DBG_TAG "DFS.dentry"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#define DFS_DENTRY_HASH_NR 32
struct dentry_hash_head
{
    rt_list_t head[DFS_DENTRY_HASH_NR];
};
static struct dentry_hash_head hash_head;

static uint32_t _dentry_hash(struct dfs_mnt *mnt, const char *path)
{
    uint32_t val = 0;

    if (path)
    {
        while (*path)
        {
            val = ((val << 5) + val) + *path++;
        }
    }
    return (val ^ (unsigned long) mnt) & (DFS_DENTRY_HASH_NR - 1);
}

static struct dfs_dentry *_dentry_create(struct dfs_mnt *mnt, char *path, rt_bool_t is_rela_path)
{
    struct dfs_dentry *dentry = RT_NULL;

    if (mnt == RT_NULL || path == RT_NULL)
    {
        return dentry;
    }

    dentry = (struct dfs_dentry *)rt_calloc(1, sizeof(struct dfs_dentry));
    if (dentry)
    {
        char *dentry_path = path;
        if (!is_rela_path)
        {
            int mntpoint_len = strlen(mnt->fullpath);

            if (rt_strncmp(mnt->fullpath, dentry_path, mntpoint_len) == 0)
            {
                dentry_path += mntpoint_len;
            }
        }

        dentry->pathname = strlen(dentry_path) ? rt_strdup(dentry_path) : rt_strdup(path);
        dentry->mnt = dfs_mnt_ref(mnt);

        rt_atomic_store(&(dentry->ref_count), 1);
        dentry->flags |= DENTRY_IS_ALLOCED;

        LOG_I("create a dentry:%p for %s", dentry, fullpath);
    }

    return dentry;
}

struct dfs_dentry *dfs_dentry_create(struct dfs_mnt *mnt, char *fullpath)
{
    return _dentry_create(mnt, fullpath, RT_FALSE);
}

struct dfs_dentry *dfs_dentry_create_rela(struct dfs_mnt *mnt, char *rela_path)
{
    return _dentry_create(mnt, rela_path, RT_TRUE);;
}

struct dfs_dentry * dfs_dentry_ref(struct dfs_dentry *dentry)
{
    if (dentry)
    {
        int ret = dfs_file_lock();
        if (ret == RT_EOK)
        {
            rt_atomic_add(&(dentry->ref_count), 1);
            if (dentry->vnode)
            {
                rt_atomic_add(&(dentry->vnode->ref_count), 1);
            }
            dfs_file_unlock();
        }
    }

    return dentry;
}

struct dfs_dentry *dfs_dentry_unref(struct dfs_dentry *dentry)
{
    rt_err_t ret = RT_EOK;

    if (dentry)
    {
        ret = dfs_file_lock();
        if (ret == RT_EOK)
        {
            if (dentry->flags & DENTRY_IS_ALLOCED)
            {
                rt_atomic_sub(&(dentry->ref_count), 1);
            }

            if (rt_atomic_load(&(dentry->ref_count)) == 0)
            {
                DLOG(msg, "dentry", "dentry", DLOG_MSG, "free dentry, ref_count=0");
                if (dentry->flags & DENTRY_IS_ADDHASH)
                {
                    rt_list_remove(&dentry->hashlist);
                }

                /* release vnode */
                if (dentry->vnode)
                {
                    dfs_vnode_unref(dentry->vnode);
                }

                /* release mnt */
                DLOG(msg, "dentry", "mnt", DLOG_MSG, "dfs_mnt_unref(dentry->mnt)");
                if (dentry->mnt)
                {
                    dfs_mnt_unref(dentry->mnt);
                }

                dfs_file_unlock();

                LOG_I("free a dentry: %p", dentry);
                rt_free(dentry->pathname);
                rt_free(dentry);
                dentry = RT_NULL;
            }
            else
            {
                if (dentry->vnode)
                {
                    rt_atomic_sub(&(dentry->vnode->ref_count), 1);
                }
                dfs_file_unlock();
                DLOG(note, "dentry", "dentry ref_count=%d", rt_atomic_load(&(dentry->ref_count)));
            }
        }
    }

    return dentry;
}

static struct dfs_dentry *_dentry_hash_lookup(struct dfs_mnt *mnt, const char *path)
{
    rt_err_t ret = RT_EOK;
    struct dfs_dentry *entry = RT_NULL;

    ret = dfs_file_lock();
    if (ret == RT_EOK)
    {
        rt_list_for_each_entry(entry, &hash_head.head[_dentry_hash(mnt, path)], hashlist)
        {
            if (entry->mnt == mnt && !strcmp(entry->pathname, path))
            {
                dfs_dentry_ref(entry);
                dfs_file_unlock();
                return entry;
            }
        }

        dfs_file_unlock();
    }

    return RT_NULL;
}

void dfs_dentry_insert(struct dfs_dentry *dentry)
{
    dfs_file_lock();
    rt_list_insert_after(&hash_head.head[_dentry_hash(dentry->mnt, dentry->pathname)], &dentry->hashlist);
    dentry->flags |= DENTRY_IS_ADDHASH;
    dfs_file_unlock();
}

/*
 * lookup a dentry, return this dentry and increase refcount if exist, otherwise return NULL
 */
struct dfs_dentry *dfs_dentry_lookup(struct dfs_mnt *mnt, const char *path, uint32_t flags)
{
    struct dfs_dentry *dentry;
    struct dfs_vnode *vnode = RT_NULL;
    int mntpoint_len = strlen(mnt->fullpath);

    if (rt_strncmp(mnt->fullpath, path, mntpoint_len) == 0)
    {
        path += mntpoint_len;
        if ((*path) == '\0')
        {
            /* root */
            path = "/";
        }
    }
    dfs_file_lock();
    dentry = _dentry_hash_lookup(mnt, path);
    if (!dentry)
    {
        if (mnt->fs_ops->lookup)
        {
            DLOG(activate, "dentry");
            /* not in hash table, create it */
            DLOG(msg, "dentry", "dentry", DLOG_MSG, "dfs_dentry_create_rela(mnt=%s, path=%s)", mnt->fullpath, path);
            dentry = dfs_dentry_create_rela(mnt, (char*)path);
            if (dentry)
            {
                DLOG(msg, "dentry", mnt->fs_ops->name, DLOG_MSG, "vnode=fs_ops->lookup(dentry)");

                if (dfs_is_mounted(mnt) == 0)
                {
                    vnode = mnt->fs_ops->lookup(dentry);
                }

                if (vnode)
                {
                    DLOG(msg, mnt->fs_ops->name, "dentry", DLOG_MSG_RET, "return vnode");
                    dentry->vnode = vnode; /* the refcount of created vnode is 1. no need to reference */
                    dfs_file_lock();
                    rt_list_insert_after(&hash_head.head[_dentry_hash(mnt, path)], &dentry->hashlist);
                    dentry->flags |= DENTRY_IS_ADDHASH;
                    dfs_file_unlock();

                    if (dentry->flags & (DENTRY_IS_ALLOCED | DENTRY_IS_ADDHASH)
                        && !(dentry->flags & DENTRY_IS_OPENED))
                    {
                        rt_err_t ret = dfs_file_lock();
                        if (ret == RT_EOK)
                        {
                            dentry->flags |= DENTRY_IS_OPENED;
                            dfs_file_unlock();
                        }
                    }
                }
                else
                {
                    DLOG(msg, mnt->fs_ops->name, "dentry", DLOG_MSG_RET, "no dentry");

                    DLOG(msg, "dentry", "dentry", DLOG_MSG, "dfs_dentry_unref(dentry)");
                    dfs_dentry_unref(dentry);
                    dentry = RT_NULL;
                }
            }
            DLOG(deactivate, "dentry");
        }
    }
    else
    {
        DLOG(note, "dentry", "found dentry");
    }
    dfs_file_unlock();
    return dentry;
}

char* dfs_dentry_full_path(struct dfs_dentry* dentry)
{
    char *path = NULL;

    if (dentry && dentry->mnt)
    {
        int mnt_len = strlen(dentry->mnt->fullpath);
        int path_len = strlen(dentry->pathname);

        path = (char *) rt_malloc(mnt_len + path_len + 3);
        if (path)
        {
            if (dentry->pathname[0] == '/' || dentry->mnt->fullpath[mnt_len - 1] == '/')
            {
                rt_snprintf(path, mnt_len + path_len + 2, "%s%s", dentry->mnt->fullpath,
                    dentry->pathname);
            }
            else
            {
                rt_snprintf(path, mnt_len + path_len + 2, "%s/%s", dentry->mnt->fullpath,
                    dentry->pathname);
            }
        }
    }

    return path;
}

char* dfs_dentry_pathname(struct dfs_dentry* dentry)
{
    char *pathname = RT_NULL;
    char *index = RT_NULL;

    index = strrchr(dentry->pathname, '/');
    if (index)
    {
        int length = index - dentry->pathname;
        int path_length = strlen(dentry->mnt->fullpath) + length + 3;

        pathname = (char*) rt_malloc(path_length);
        if (pathname)
        {
            if (dentry->pathname[0] == '/')
            {
                rt_snprintf(pathname, path_length - 1, "%s%.*s", dentry->mnt->fullpath,
                    length, dentry->pathname);
            }
            else
            {
                rt_snprintf(pathname, path_length - 1, "%s/%.*s", dentry->mnt->fullpath,
                    length, dentry->pathname);
            }
        }
    }
    else
    {
        pathname = rt_strdup(dentry->mnt->fullpath);
    }

    return pathname;
}

uint32_t dfs_dentry_full_path_crc32(struct dfs_dentry* dentry)
{
    uint32_t crc32 = 0xFFFFFFFF;
    char *fullpath = dfs_dentry_full_path(dentry);
    if (fullpath)
    {
        int i = 0;

        while(fullpath[i] != '\0')
        {
            for (uint8_t b = 1; b; b <<= 1)
            {
                crc32 ^= (fullpath[i] & b) ? 1 : 0;
                crc32 = (crc32 & 1) ? crc32 >> 1 ^ 0xEDB88320 : crc32 >> 1;
            }
            i ++;
        }
        rt_free(fullpath);
    }
    return crc32;
}

int dfs_dentry_init(void)
{
    int i = 0;

    for(i = 0; i < DFS_DENTRY_HASH_NR; i++)
    {
        rt_list_init(&hash_head.head[i]);
    }

    return 0;
}

int dfs_dentry_dump(int argc, char** argv)
{
    int index = 0;
    struct dfs_dentry *entry = RT_NULL;

    dfs_lock();
    for (index = 0; index < DFS_DENTRY_HASH_NR; index ++)
    {
        rt_list_for_each_entry(entry, &hash_head.head[index], hashlist)
        {
            printf("dentry: %s%s @ %p, ref_count = %zd\n", entry->mnt->fullpath, entry->pathname, entry, (size_t)rt_atomic_load(&entry->ref_count));
        }
    }
    dfs_unlock();

    return 0;
}
MSH_CMD_EXPORT_ALIAS(dfs_dentry_dump, dentry_dump, dump dentry in the system);
