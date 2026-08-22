/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <limits.h>

#include <dfs.h>
#include <dfs_file.h>
#include <rtservice.h>

#ifdef RT_USING_SMART
#include <lwp.h>
#endif

struct dfs_lock_range
{
    off_t start;
    off_t end;
    rt_bool_t to_eof;
};

struct dfs_record_lock
{
    rt_list_t list;
    struct dfs_vnode *vnode;
    struct dfs_fdtable *owner;
    pid_t pid;
    short type;
    struct dfs_lock_range range;
};

static rt_list_t _record_locks;
static struct rt_semaphore _record_lock_changed;
static int _record_lock_waiters;

static off_t _off_max(void)
{
    return sizeof(off_t) == sizeof(rt_int64_t) ? (off_t)INT64_MAX :
                                                (off_t)INT32_MAX;
}

static off_t _off_min(void)
{
    off_t max = _off_max();

    return -max - 1;
}

static int _add_offset(off_t left, off_t right, off_t *result)
{
    off_t max = _off_max();
    off_t min = _off_min();

    if ((right > 0 && left > max - right) ||
        (right < 0 && left < min - right))
    {
        return -EOVERFLOW;
    }

    *result = left + right;
    return 0;
}

static int _normalize_range(struct dfs_file *file, const struct flock *flock,
                            struct dfs_lock_range *range)
{
    off_t base;
    off_t origin;
    off_t end;
    int ret;

    switch (flock->l_whence)
    {
    case SEEK_SET:
        base = 0;
        break;
    case SEEK_CUR:
        base = dfs_file_get_fpos(file);
        break;
    case SEEK_END:
        if (file->vnode->size > (size_t)_off_max())
        {
            return -EOVERFLOW;
        }
        base = (off_t)file->vnode->size;
        break;
    default:
        return -EINVAL;
    }

    ret = _add_offset(base, flock->l_start, &origin);
    if (ret < 0 || origin < 0)
    {
        return ret < 0 ? ret : -EINVAL;
    }

    range->to_eof = RT_FALSE;
    if (flock->l_len == 0)
    {
        range->start = origin;
        range->end = 0;
        range->to_eof = RT_TRUE;
        return 0;
    }

    if (flock->l_len > 0)
    {
        ret = _add_offset(origin, flock->l_len - 1, &end);
        if (ret < 0)
        {
            return ret;
        }
        range->start = origin;
        range->end = end;
    }
    else
    {
        ret = _add_offset(origin, flock->l_len, &range->start);
        if (ret < 0 || range->start < 0 || origin == 0)
        {
            return ret < 0 ? ret : -EINVAL;
        }
        range->end = origin - 1;
    }

    if (range->end == _off_max())
    {
        range->end = 0;
        range->to_eof = RT_TRUE;
    }
    return 0;
}

static rt_bool_t _ranges_overlap(const struct dfs_lock_range *left,
                                 const struct dfs_lock_range *right)
{
    if (!left->to_eof && left->end < right->start)
    {
        return RT_FALSE;
    }
    if (!right->to_eof && right->end < left->start)
    {
        return RT_FALSE;
    }
    return RT_TRUE;
}

static rt_bool_t _ranges_touch(const struct dfs_lock_range *left,
                               const struct dfs_lock_range *right)
{
    if (_ranges_overlap(left, right))
    {
        return RT_TRUE;
    }
    if (!left->to_eof && left->end < _off_max() &&
        left->end + 1 == right->start)
    {
        return RT_TRUE;
    }
    if (!right->to_eof && right->end < _off_max() &&
        right->end + 1 == left->start)
    {
        return RT_TRUE;
    }
    return RT_FALSE;
}

static rt_bool_t _locks_conflict(short requested_type,
                                 const struct dfs_record_lock *lock,
                                 const struct dfs_lock_range *range,
                                 struct dfs_fdtable *owner)
{
    if (lock->owner == owner || !_ranges_overlap(&lock->range, range))
    {
        return RT_FALSE;
    }
    return requested_type == F_WRLCK || lock->type == F_WRLCK;
}

static struct dfs_record_lock *_find_conflict(
    struct dfs_vnode *vnode, struct dfs_fdtable *owner, short type,
    const struct dfs_lock_range *range)
{
    rt_list_t *node;
    struct dfs_record_lock *result = RT_NULL;

    rt_list_for_each(node, &_record_locks)
    {
        struct dfs_record_lock *lock;

        lock = rt_list_entry(node, struct dfs_record_lock, list);
        if (lock->vnode == vnode &&
            _locks_conflict(type, lock, range, owner) &&
            (result == RT_NULL || lock->range.start < result->range.start))
        {
            result = lock;
        }
    }
    return result;
}

static struct dfs_record_lock *_split_lock_needed(
    struct dfs_vnode *vnode, struct dfs_fdtable *owner,
    const struct dfs_lock_range *range)
{
    rt_list_t *node;

    if (range->to_eof)
    {
        return RT_NULL;
    }

    rt_list_for_each(node, &_record_locks)
    {
        struct dfs_record_lock *lock;

        lock = rt_list_entry(node, struct dfs_record_lock, list);
        if (lock->vnode == vnode && lock->owner == owner &&
            lock->range.start < range->start &&
            (lock->range.to_eof || lock->range.end > range->end))
        {
            return lock;
        }
    }
    return RT_NULL;
}

static int _remove_owner_range(struct dfs_vnode *vnode,
                               struct dfs_fdtable *owner,
                               const struct dfs_lock_range *range)
{
    struct dfs_record_lock *split_source;
    struct dfs_record_lock *split = RT_NULL;
    rt_list_t *node;
    rt_list_t *next;

    split_source = _split_lock_needed(vnode, owner, range);
    if (split_source != RT_NULL)
    {
        split = rt_malloc(sizeof(*split));
        if (split == RT_NULL)
        {
            return -ENOLCK;
        }
        *split = *split_source;
        rt_list_init(&split->list);
        split->range.start = range->end + 1;
        rt_list_insert_after(&split_source->list, &split->list);
    }

    rt_list_for_each_safe(node, next, &_record_locks)
    {
        struct dfs_record_lock *lock;

        lock = rt_list_entry(node, struct dfs_record_lock, list);
        if (lock == split || lock->vnode != vnode || lock->owner != owner ||
            !_ranges_overlap(&lock->range, range))
        {
            continue;
        }

        if (lock->range.start < range->start)
        {
            lock->range.end = range->start - 1;
            lock->range.to_eof = RT_FALSE;
        }
        else if (!range->to_eof &&
                 (lock->range.to_eof || lock->range.end > range->end))
        {
            lock->range.start = range->end + 1;
        }
        else
        {
            rt_list_remove(&lock->list);
            rt_free(lock);
        }
    }
    return 0;
}

static void _merge_owner_locks(struct dfs_record_lock *target)
{
    rt_list_t *node;
    rt_list_t *next;
    rt_bool_t merged;

    do
    {
        merged = RT_FALSE;
        rt_list_for_each_safe(node, next, &_record_locks)
        {
            struct dfs_record_lock *lock;

            lock = rt_list_entry(node, struct dfs_record_lock, list);
            if (lock == target || lock->vnode != target->vnode ||
                lock->owner != target->owner || lock->type != target->type ||
                !_ranges_touch(&lock->range, &target->range))
            {
                continue;
            }

            if (lock->range.start < target->range.start)
            {
                target->range.start = lock->range.start;
            }
            if (lock->range.to_eof || target->range.to_eof)
            {
                target->range.to_eof = RT_TRUE;
                target->range.end = 0;
            }
            else if (lock->range.end > target->range.end)
            {
                target->range.end = lock->range.end;
            }
            rt_list_remove(&lock->list);
            rt_free(lock);
            merged = RT_TRUE;
        }
    }
    while (merged);
}

static void _wake_waiter(void)
{
    if (_record_lock_waiters > 0)
    {
        rt_sem_release(&_record_lock_changed);
    }
}

static pid_t _owner_pid(struct dfs_fdtable *owner)
{
#ifdef RT_USING_SMART
    if (owner != RT_NULL && owner != dfs_fdtable_get_global())
    {
        struct rt_lwp *lwp;

        lwp = rt_container_of(owner, struct rt_lwp, fdt);
        return lwp->pid;
    }
#endif
    return 0;
}

static int _set_lock(struct dfs_file *file, int cmd, struct flock *flock,
                     const struct dfs_lock_range *range)
{
    struct dfs_fdtable *owner = dfs_fdtable_get();
    struct dfs_record_lock *new_lock = RT_NULL;
    rt_bool_t waiting = RT_FALSE;
    int ret;

    if (flock->l_type != F_UNLCK)
    {
        new_lock = rt_malloc(sizeof(*new_lock));
        if (new_lock == RT_NULL)
        {
            return -ENOLCK;
        }
        new_lock->vnode = file->vnode;
        new_lock->owner = owner;
        new_lock->pid = _owner_pid(owner);
        new_lock->type = flock->l_type;
        new_lock->range = *range;
        rt_list_init(&new_lock->list);
    }

    for (;;)
    {
        if (dfs_file_lock() != RT_EOK)
        {
            ret = -ENOSYS;
            break;
        }

        if (flock->l_type != F_UNLCK &&
            _find_conflict(file->vnode, owner, flock->l_type, range) != RT_NULL)
        {
            if (cmd == F_SETLK)
            {
                dfs_file_unlock();
                ret = -EAGAIN;
                break;
            }
            if (!waiting)
            {
                _record_lock_waiters++;
                waiting = RT_TRUE;
            }
            dfs_file_unlock();
            if (rt_sem_take_interruptible(&_record_lock_changed,
                                          RT_WAITING_FOREVER) != RT_EOK)
            {
                ret = -EINTR;
                break;
            }
            continue;
        }

        ret = _remove_owner_range(file->vnode, owner, range);
        if (ret == 0 && new_lock != RT_NULL)
        {
            rt_list_insert_before(&_record_locks, &new_lock->list);
            _merge_owner_locks(new_lock);
            new_lock = RT_NULL;
        }
        if (waiting)
        {
            _record_lock_waiters--;
            waiting = RT_FALSE;
        }
        if (ret == 0)
        {
            _wake_waiter();
        }
        dfs_file_unlock();
        break;
    }

    if (waiting && dfs_file_lock() == RT_EOK)
    {
        _record_lock_waiters--;
        dfs_file_unlock();
    }
    if (new_lock != RT_NULL)
    {
        rt_free(new_lock);
    }
    return ret;
}

int dfs_record_lock_init(void)
{
    rt_list_init(&_record_locks);
    _record_lock_waiters = 0;
    return rt_sem_init(&_record_lock_changed, "freclck", 0,
                       RT_IPC_FLAG_FIFO);
}

int dfs_record_lock_fcntl(struct dfs_file *file, int cmd, struct flock *flock)
{
    struct dfs_lock_range range;
    struct dfs_record_lock *conflict;
    struct dfs_fdtable *owner;
    int access;
    int ret;

    if (file == RT_NULL || file->vnode == RT_NULL || flock == RT_NULL)
    {
        return -EBADF;
    }
    if (flock->l_type != F_RDLCK && flock->l_type != F_WRLCK &&
        (flock->l_type != F_UNLCK || cmd == F_GETLK))
    {
        return -EINVAL;
    }

    access = dfs_fflags(file->flags);
    if ((flock->l_type == F_RDLCK && !(access & DFS_F_FREAD)) ||
        (flock->l_type == F_WRLCK && !(access & DFS_F_FWRITE)))
    {
        return -EBADF;
    }

    ret = _normalize_range(file, flock, &range);
    if (ret < 0)
    {
        return ret;
    }
    if (cmd != F_GETLK)
    {
        return _set_lock(file, cmd, flock, &range);
    }

    owner = dfs_fdtable_get();
    if (dfs_file_lock() != RT_EOK)
    {
        return -ENOSYS;
    }
    conflict = _find_conflict(file->vnode, owner, flock->l_type, &range);
    if (conflict == RT_NULL)
    {
        flock->l_type = F_UNLCK;
    }
    else
    {
        flock->l_type = conflict->type;
        flock->l_whence = SEEK_SET;
        flock->l_start = conflict->range.start;
        flock->l_len = conflict->range.to_eof ? 0 :
            conflict->range.end - conflict->range.start + 1;
        flock->l_pid = conflict->pid;
    }
    dfs_file_unlock();
    return 0;
}

void dfs_record_lock_release(struct dfs_file *file, struct dfs_fdtable *owner)
{
    rt_list_t *node;
    rt_list_t *next;
    rt_bool_t changed = RT_FALSE;

    if (file == RT_NULL || file->vnode == RT_NULL || owner == RT_NULL ||
        dfs_file_lock() != RT_EOK)
    {
        return;
    }

    rt_list_for_each_safe(node, next, &_record_locks)
    {
        struct dfs_record_lock *lock;

        lock = rt_list_entry(node, struct dfs_record_lock, list);
        if (lock->vnode == file->vnode && lock->owner == owner)
        {
            rt_list_remove(&lock->list);
            rt_free(lock);
            changed = RT_TRUE;
        }
    }
    if (changed)
    {
        _wake_waiter();
    }
    dfs_file_unlock();
}
