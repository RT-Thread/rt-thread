/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <string.h>

#include <dfs_net.h>

#include "af_unix_internal.h"

static struct rt_mutex af_unix_deferred_lock;
static rt_list_t af_unix_deferred_rights;

static size_t af_unix_cmsg_next(size_t offset, size_t length,
                                size_t control_length)
{
    size_t next;

    next = offset + CMSG_ALIGN(length);
    if (next > control_length)
    {
        next = offset + length;
    }
    return next;
}

static int af_unix_file_is_unix_socket(const struct dfs_file *file)
{
    int sal_handle;
    struct sal_socket *sal_sock;

    if (file == RT_NULL || file->vnode == RT_NULL ||
        file->vnode->type != FT_SOCKET)
    {
        return 0;
    }
    if (file->vnode->fops != dfs_net_get_fops() &&
        file->fops != dfs_net_get_fops())
    {
        return 0;
    }

    sal_handle = (int)(size_t)file->vnode->data;
    sal_sock = sal_get_socket(sal_handle);
    return (sal_sock != RT_NULL && sal_sock->domain == AF_UNIX);
}

int af_unix_rights_create(const struct msghdr *message,
                          struct af_unix_rights **out_rights)
{
    int fds[AF_UNIX_RIGHTS_MAX];
    int result;
    size_t count = 0;
    size_t file_index;
    size_t offset = 0;
    const char *control;
    struct af_unix_rights *rights;

    *out_rights = RT_NULL;
    if (message->msg_controllen == 0)
    {
        return 0;
    }
    if (message->msg_control == RT_NULL)
    {
        return af_unix_error(EINVAL);
    }

    control = (const char *)message->msg_control;
    while (offset < message->msg_controllen)
    {
        size_t data_length;
        size_t fd_count;
        size_t index;
        size_t next;
        const struct cmsghdr *cmsg;

        if (message->msg_controllen - offset < sizeof(*cmsg))
        {
            return af_unix_error(EINVAL);
        }
        cmsg = (const struct cmsghdr *)(control + offset);
        if (cmsg->cmsg_len < sizeof(*cmsg) ||
            cmsg->cmsg_len > message->msg_controllen - offset)
        {
            return af_unix_error(EINVAL);
        }
        if (cmsg->cmsg_level != SOL_SOCKET || cmsg->cmsg_type != SCM_RIGHTS)
        {
            return af_unix_error(EOPNOTSUPP);
        }

        data_length = cmsg->cmsg_len - sizeof(*cmsg);
        if (data_length == 0 || data_length % sizeof(int) != 0)
        {
            return af_unix_error(EINVAL);
        }
        fd_count = data_length / sizeof(int);
        if (fd_count > AF_UNIX_RIGHTS_MAX - count)
        {
            return af_unix_error(EMSGSIZE);
        }
        for (index = 0; index < fd_count; index++)
        {
            rt_memcpy(&fds[count],
                      (const char *)CMSG_DATA(cmsg) + index * sizeof(int),
                      sizeof(int));
            count++;
        }

        next = af_unix_cmsg_next(offset, cmsg->cmsg_len,
                                 message->msg_controllen);
        if (next <= offset || next > message->msg_controllen)
        {
            return af_unix_error(EINVAL);
        }
        offset = next;
    }

    rights = (struct af_unix_rights *)rt_calloc(
        1, sizeof(*rights) + (count - 1) * sizeof(rights->files[0]));
    if (rights == RT_NULL)
    {
        return af_unix_error(ENOMEM);
    }
    rt_list_init(&rights->node);
    rights->count = count;

    result = dfs_file_get_refs(fds, count, rights->files);
    if (result < 0)
    {
        rt_free(rights);
        return af_unix_error(-result);
    }

    /* Passing AF_UNIX sockets can form an unreclaimable reference
     * cycle between the in-flight right and the destination queue. */
    for (file_index = 0; file_index < count; file_index++)
    {
        if (af_unix_file_is_unix_socket(rights->files[file_index]))
        {
            af_unix_rights_release(rights);
            return af_unix_error(EOPNOTSUPP);
        }
    }

    *out_rights = rights;
    return 0;
}

void af_unix_rights_release(struct af_unix_rights *rights)
{
    size_t index;

    if (rights == RT_NULL)
    {
        return;
    }
    for (index = 0; index < rights->count; index++)
    {
        if (rights->files[index] != RT_NULL)
        {
            dfs_file_put_ref(rights->files[index]);
        }
    }
    rt_free(rights);
}

void af_unix_rights_list_release(rt_list_t *list)
{
    while (!rt_list_isempty(list))
    {
        struct af_unix_rights *rights;

        rights = rt_list_entry(list->next, struct af_unix_rights, node);
        rt_list_remove(&rights->node);
        af_unix_rights_release(rights);
    }
}

void af_unix_rights_defer_locked(struct af_unix_rights *rights)
{
    if (rights == RT_NULL)
    {
        return;
    }

    rt_mutex_take(&af_unix_deferred_lock, RT_WAITING_FOREVER);
    rt_list_insert_before(&af_unix_deferred_rights, &rights->node);
    rt_mutex_release(&af_unix_deferred_lock);
}

void af_unix_rights_list_defer_locked(rt_list_t *list)
{
    while (!rt_list_isempty(list))
    {
        struct af_unix_rights *rights;

        rights = rt_list_entry(list->next, struct af_unix_rights, node);
        rt_list_remove(&rights->node);
        af_unix_rights_defer_locked(rights);
    }
}

void af_unix_rights_drain(void)
{
    rt_list_t pending;

    rt_list_init(&pending);
    rt_mutex_take(&af_unix_deferred_lock, RT_WAITING_FOREVER);
    while (!rt_list_isempty(&af_unix_deferred_rights))
    {
        rt_list_t *node = af_unix_deferred_rights.next;

        rt_list_remove(node);
        rt_list_insert_before(&pending, node);
    }
    rt_mutex_release(&af_unix_deferred_lock);

    af_unix_rights_list_release(&pending);
}

static size_t af_unix_rights_count(const rt_list_t *list)
{
    size_t count = 0;
    const rt_list_t *node;

    for (node = list->next; node != list; node = node->next)
    {
        const struct af_unix_rights *rights;

        rights = rt_list_entry(node, struct af_unix_rights, node);
        count += rights->count;
    }
    return count;
}

static size_t af_unix_rights_capacity(const struct msghdr *message,
                                      size_t total)
{
    size_t capacity;

    if (message->msg_control == RT_NULL ||
        message->msg_controllen < CMSG_SPACE(sizeof(int)))
    {
        return 0;
    }

    capacity = (message->msg_controllen - sizeof(struct cmsghdr)) /
               sizeof(int);
    if (capacity > total)
    {
        capacity = total;
    }
    while (capacity != 0 &&
           CMSG_SPACE(capacity * sizeof(int)) > message->msg_controllen)
    {
        capacity--;
    }
    return capacity;
}

int af_unix_rights_deliver(rt_list_t *list, struct msghdr *message)
{
    int install_result = 0;
    int *fds = RT_NULL;
    size_t capacity;
    size_t delivered = 0;
    size_t index;
    size_t total;
    struct dfs_file **files = RT_NULL;
    struct cmsghdr *cmsg;
    rt_list_t *node;

    total = af_unix_rights_count(list);
    capacity = af_unix_rights_capacity(message, total);
    if (capacity != 0)
    {
        files = (struct dfs_file **)rt_malloc(capacity * sizeof(*files));
        fds = (int *)rt_malloc(capacity * sizeof(*fds));
        if (files == RT_NULL || fds == RT_NULL)
        {
            capacity = 0;
        }
    }

    for (node = list->next; node != list && delivered < capacity;
         node = node->next)
    {
        struct af_unix_rights *rights;

        rights = rt_list_entry(node, struct af_unix_rights, node);
        for (index = 0; index < rights->count && delivered < capacity; index++)
        {
            files[delivered] = rights->files[index];
            delivered++;
        }
    }

    if (delivered != 0)
    {
        install_result = dfs_file_install_refs(files, delivered, fds);
        if (install_result < 0)
        {
            delivered = 0;
        }
    }

    if (delivered != 0)
    {
        size_t transferred = 0;

        for (node = list->next; node != list && transferred < delivered;
             node = node->next)
        {
            struct af_unix_rights *rights;

            rights = rt_list_entry(node, struct af_unix_rights, node);
            for (index = 0;
                 index < rights->count && transferred < delivered; index++)
            {
                rights->files[index] = RT_NULL;
                transferred++;
            }
        }

        cmsg = (struct cmsghdr *)message->msg_control;
        cmsg->cmsg_len = CMSG_LEN(delivered * sizeof(int));
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;
        rt_memcpy(CMSG_DATA(cmsg), fds, delivered * sizeof(int));
        message->msg_controllen = CMSG_SPACE(delivered * sizeof(int));
    }
    else
    {
        message->msg_controllen = 0;
    }

    if (delivered < total)
    {
        message->msg_flags |= MSG_CTRUNC;
    }

    if (files != RT_NULL)
    {
        rt_free(files);
    }
    if (fds != RT_NULL)
    {
        rt_free(fds);
    }
    af_unix_rights_list_release(list);
    return install_result;
}

int af_unix_rights_init(void)
{
    rt_list_init(&af_unix_deferred_rights);
    return rt_mutex_init(&af_unix_deferred_lock, "afuright",
                         RT_IPC_FLAG_PRIO);
}
