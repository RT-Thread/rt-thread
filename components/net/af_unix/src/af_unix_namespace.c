/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <string.h>

#include "af_unix_internal.h"

struct af_unix_namespace_entry
{
    rt_list_t node;
    char path[AF_UNIX_PATH_MAX];
    struct af_unix_socket *sock;
};

static rt_list_t af_unix_namespace;

static struct af_unix_namespace_entry *af_unix_namespace_find_locked(
    const char *path)
{
    struct af_unix_namespace_entry *entry;

    rt_list_for_each_entry(entry, &af_unix_namespace, node)
    {
        if (rt_strcmp(entry->path, path) == 0)
        {
            return entry;
        }
    }
    return RT_NULL;
}

int af_unix_address_parse(const struct sockaddr *address, socklen_t length,
                          char path[AF_UNIX_PATH_MAX])
{
    int index;
    int path_length;
    char input_path[AF_UNIX_PATH_MAX];
    char *normalized;
    const struct sockaddr_un *unix_address;
    const int path_offset = (int)offsetof(struct sockaddr_un, sun_path);

    if (address == RT_NULL || length <= (socklen_t)path_offset ||
        length > sizeof(struct sockaddr_un))
    {
        return af_unix_error(EINVAL);
    }

    unix_address = (const struct sockaddr_un *)address;
    if (unix_address->sa_family != AF_UNIX)
    {
        return af_unix_error(EAFNOSUPPORT);
    }

    path_length = (int)length - path_offset;
    if (path_length > AF_UNIX_PATH_MAX)
    {
        path_length = AF_UNIX_PATH_MAX;
    }
    for (index = 0; index < path_length; index++)
    {
        if (unix_address->sun_path[index] == '\0')
        {
            break;
        }
    }
    if (index == 0)
    {
        return af_unix_error(EINVAL);
    }
    if (index == path_length || index >= AF_UNIX_PATH_MAX)
    {
        return af_unix_error(ENAMETOOLONG);
    }

    rt_memcpy(input_path, unix_address->sun_path, index);
    input_path[index] = '\0';
    normalized = dfs_normalize_path(RT_NULL, input_path);
    if (normalized == RT_NULL)
    {
        return af_unix_error(ENOMEM);
    }
    if (rt_strlen(normalized) >= AF_UNIX_PATH_MAX)
    {
        rt_free(normalized);
        return af_unix_error(ENAMETOOLONG);
    }
    rt_strncpy(path, normalized, AF_UNIX_PATH_MAX);
    path[AF_UNIX_PATH_MAX - 1] = '\0';
    rt_free(normalized);
    return 0;
}

void af_unix_address_set(struct sockaddr_un *address, socklen_t *length,
                         const char *path)
{
    size_t path_length = 0;

    rt_memset(address, 0, sizeof(*address));
    address->sa_family = AF_UNIX;
    if (path != RT_NULL)
    {
        path_length = rt_strlen(path);
        if (path_length >= sizeof(address->sun_path))
        {
            path_length = sizeof(address->sun_path) - 1;
        }
        rt_memcpy(address->sun_path, path, path_length);
    }
    *length = (socklen_t)(offsetof(struct sockaddr_un, sun_path) +
                          path_length + (path != RT_NULL ? 1 : 0));
}

int af_unix_address_copy(struct sockaddr *address, socklen_t *length,
                         const struct sockaddr_un *source,
                         socklen_t source_length)
{
    socklen_t copy_length;

    if (address == RT_NULL)
    {
        return 0;
    }
    if (length == RT_NULL)
    {
        return af_unix_error(EINVAL);
    }

    copy_length = *length;
    if (copy_length > source_length)
    {
        copy_length = source_length;
    }
    if (copy_length > 0)
    {
        rt_memcpy(address, source, copy_length);
    }
    *length = source_length;
    return 0;
}

int af_unix_namespace_bind(struct af_unix_socket *sock,
                           const struct sockaddr *address, socklen_t length)
{
    int result;
    char path[AF_UNIX_PATH_MAX];
    struct af_unix_namespace_entry *entry;
    struct af_unix_namespace_entry *new_entry;

    result = af_unix_address_parse(address, length, path);
    if (result < 0)
    {
        return result;
    }

    af_unix_lock();
    if (sock->closed)
    {
        af_unix_unlock();
        return af_unix_error(EBADF);
    }
    if (sock->bound)
    {
        af_unix_unlock();
        return af_unix_error(EINVAL);
    }
    af_unix_unlock();

    result = dfs_file_mknod(path, FT_SOCKET,
                            S_IRWXU | S_IRWXG | S_IRWXO);
    if (result < 0)
    {
        return af_unix_error(result == -EEXIST ? EADDRINUSE : -result);
    }

    new_entry = (struct af_unix_namespace_entry *)rt_calloc(1,
                                                            sizeof(*new_entry));
    if (new_entry == RT_NULL)
    {
        (void)dfs_file_unlink(path);
        return af_unix_error(ENOMEM);
    }
    rt_strncpy(new_entry->path, path, sizeof(new_entry->path));
    new_entry->path[sizeof(new_entry->path) - 1] = '\0';
    rt_list_init(&new_entry->node);

    af_unix_lock();
    if (sock->closed || sock->bound)
    {
        af_unix_unlock();
        rt_free(new_entry);
        (void)dfs_file_unlink(path);
        return af_unix_error(sock->closed ? EBADF : EINVAL);
    }

    entry = af_unix_namespace_find_locked(path);
    if (entry == RT_NULL)
    {
        entry = new_entry;
        new_entry = RT_NULL;
        rt_list_insert_before(&af_unix_namespace, &entry->node);
    }
    entry->sock = sock;
    sock->namespace_entry = entry;
    sock->bound = 1;
    af_unix_address_set(&sock->local_address, &sock->local_length, path);
    af_unix_unlock();

    if (new_entry != RT_NULL)
    {
        rt_free(new_entry);
    }
    return 0;
}

struct af_unix_socket *af_unix_namespace_lookup(
    const struct sockaddr *address, socklen_t length, int type,
    struct sockaddr_un *normalized_address, socklen_t *normalized_length)
{
    int result;
    char path[AF_UNIX_PATH_MAX];
    struct stat file_stat;
    struct af_unix_socket *sock = RT_NULL;
    struct af_unix_namespace_entry *entry;

    result = af_unix_address_parse(address, length, path);
    if (result < 0)
    {
        return RT_NULL;
    }
    result = dfs_file_stat(path, &file_stat);
    if (result < 0)
    {
        af_unix_error(ENOENT);
        return RT_NULL;
    }
    if (!S_ISSOCK(file_stat.st_mode))
    {
        af_unix_error(EPROTOTYPE);
        return RT_NULL;
    }

    af_unix_lock();
    entry = af_unix_namespace_find_locked(path);
    if (entry != RT_NULL && entry->sock != RT_NULL && !entry->sock->closed)
    {
        if (entry->sock->type == type)
        {
            sock = entry->sock;
            af_unix_socket_ref_locked(sock);
        }
        else
        {
            af_unix_error(EPROTOTYPE);
        }
    }
    else
    {
        af_unix_error(ECONNREFUSED);
    }
    af_unix_unlock();

    if (sock != RT_NULL && normalized_address != RT_NULL &&
        normalized_length != RT_NULL)
    {
        af_unix_address_set(normalized_address, normalized_length, path);
    }
    return sock;
}

void af_unix_namespace_detach_locked(struct af_unix_socket *sock)
{
    struct af_unix_namespace_entry *entry;

    entry = (struct af_unix_namespace_entry *)sock->namespace_entry;
    if (entry != RT_NULL && entry->sock == sock)
    {
        entry->sock = RT_NULL;
        rt_list_remove(&entry->node);
        rt_free(entry);
    }
    sock->namespace_entry = RT_NULL;
}

int af_unix_namespace_init(void)
{
    rt_list_init(&af_unix_namespace);
    return RT_EOK;
}
