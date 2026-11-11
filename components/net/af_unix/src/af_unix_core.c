/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <limits.h>
#include <stddef.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>

#include <af_unix.h>
#include "af_unix_internal.h"

static struct rt_mutex af_unix_core_lock;
static struct af_unix_socket *af_unix_handles[SAL_SOCKETS_NUM];

int af_unix_error(int error)
{
    rt_set_errno(error);
    return -1;
}

void af_unix_lock(void)
{
    rt_mutex_take(&af_unix_core_lock, RT_WAITING_FOREVER);
}

void af_unix_unlock(void)
{
    rt_mutex_release(&af_unix_core_lock);
}

int af_unix_is_nonblocking(const struct af_unix_socket *sock, int flags)
{
    return ((sock->flags & O_NONBLOCK) != 0 || (flags & MSG_DONTWAIT) != 0);
}

int af_unix_wait(rt_wqueue_t *queue, int timeout)
{
    int result;

    result = rt_wqueue_wait_interruptible(queue, 0, timeout);
    if (result == -RT_EINTR)
    {
        return af_unix_error(EINTR);
    }
    if (result != RT_EOK)
    {
        return af_unix_error(EAGAIN);
    }
    return 0;
}

static void af_unix_message_queue_clear_locked(struct af_unix_socket *sock)
{
    while (!rt_list_isempty(&sock->message_queue))
    {
        struct af_unix_message *message;

        message = rt_list_entry(sock->message_queue.next,
                                struct af_unix_message, node);
        rt_list_remove(&message->node);
        if (message->rights != RT_NULL)
        {
            af_unix_rights_defer_locked(message->rights);
        }
        rt_free(message);
    }
    sock->message_count = 0;
}

static void af_unix_socket_destroy_locked(struct af_unix_socket *sock)
{
    af_unix_message_queue_clear_locked(sock);
    af_unix_rights_list_defer_locked(&sock->rights_queue);
    if (sock->stream_buffer != RT_NULL)
    {
        rt_free(sock->stream_buffer);
    }
    rt_free(sock);
}

void af_unix_socket_ref_locked(struct af_unix_socket *sock)
{
    RT_ASSERT(sock != RT_NULL);
    RT_ASSERT(sock->ref_count > 0);
    sock->ref_count++;
}

void af_unix_socket_unref_locked(struct af_unix_socket *sock)
{
    RT_ASSERT(sock != RT_NULL);
    RT_ASSERT(sock->ref_count > 0);

    sock->ref_count--;
    if (sock->ref_count == 0)
    {
        af_unix_socket_destroy_locked(sock);
    }
}

struct af_unix_socket *af_unix_socket_create_locked(int type)
{
    struct af_unix_socket *sock;

    sock = (struct af_unix_socket *)rt_calloc(1, sizeof(*sock));
    if (sock == RT_NULL)
    {
        return RT_NULL;
    }

    if (type == SOCK_STREAM)
    {
        sock->stream_buffer = (char *)rt_malloc(AF_UNIX_STREAM_BUFFER_SIZE);
        if (sock->stream_buffer == RT_NULL)
        {
            rt_free(sock);
            return RT_NULL;
        }
    }

    sock->handle = -1;
    sock->type = type;
    sock->ref_count = 1;
    sock->receive_timeout = RT_WAITING_FOREVER;
    sock->send_timeout = RT_WAITING_FOREVER;
    rt_wqueue_init(&sock->wait_queue);
    rt_list_init(&sock->message_queue);
    rt_list_init(&sock->rights_queue);
    rt_list_init(&sock->pending_queue);
    rt_list_init(&sock->pending_node);
    af_unix_address_set(&sock->local_address, &sock->local_length, RT_NULL);
    af_unix_address_set(&sock->peer_address, &sock->peer_length, RT_NULL);

    return sock;
}

int af_unix_handle_alloc_locked(struct af_unix_socket *sock)
{
    int handle;

    for (handle = 0; handle < SAL_SOCKETS_NUM; handle++)
    {
        if (af_unix_handles[handle] == RT_NULL)
        {
            af_unix_handles[handle] = sock;
            sock->handle = handle;
            return handle;
        }
    }

    return -1;
}

void af_unix_handle_remove_locked(struct af_unix_socket *sock)
{
    int handle;

    handle = sock->handle;
    if (handle >= 0 && handle < SAL_SOCKETS_NUM &&
        af_unix_handles[handle] == sock)
    {
        af_unix_handles[handle] = RT_NULL;
        sock->handle = -1;
        af_unix_socket_unref_locked(sock);
    }
}

struct af_unix_socket *af_unix_socket_get(int handle)
{
    struct af_unix_socket *sock = RT_NULL;

    af_unix_lock();
    if (handle >= 0 && handle < SAL_SOCKETS_NUM)
    {
        sock = af_unix_handles[handle];
        if (sock != RT_NULL)
        {
            af_unix_socket_ref_locked(sock);
        }
    }
    af_unix_unlock();

    if (sock == RT_NULL)
    {
        af_unix_error(EBADF);
    }
    return sock;
}

void af_unix_socket_put(struct af_unix_socket *sock)
{
    int error;

    error = rt_get_errno();
    af_unix_lock();
    af_unix_socket_unref_locked(sock);
    af_unix_unlock();
    af_unix_rights_drain();
    rt_set_errno(error);
}

static void af_unix_disconnect_locked(struct af_unix_socket *sock)
{
    int reciprocal;
    struct af_unix_socket *peer;

    peer = sock->peer;
    if (peer == RT_NULL)
    {
        return;
    }

    rt_wqueue_wakeup_all(&sock->wait_queue,
                         (void *)(rt_ubase_t)(POLLIN | POLLOUT | POLLHUP));
    rt_wqueue_wakeup_all(&peer->wait_queue,
                         (void *)(rt_ubase_t)(POLLIN | POLLOUT | POLLHUP));

    reciprocal = (peer->peer == sock);
    sock->peer = RT_NULL;
    if (reciprocal)
    {
        peer->peer = RT_NULL;
        af_unix_socket_unref_locked(sock);
    }
    af_unix_socket_unref_locked(peer);
}

void af_unix_set_peer_locked(struct af_unix_socket *sock,
                             struct af_unix_socket *peer)
{
    if (sock->peer == peer)
    {
        return;
    }
    if (sock->peer != RT_NULL)
    {
        af_unix_disconnect_locked(sock);
    }
    if (peer != RT_NULL)
    {
        af_unix_socket_ref_locked(peer);
        sock->peer = peer;
    }
}

int af_unix_connect_peers_locked(struct af_unix_socket *first,
                                 struct af_unix_socket *second)
{
    if (first->peer != RT_NULL || second->peer != RT_NULL)
    {
        return af_unix_error(EISCONN);
    }

    af_unix_socket_ref_locked(second);
    first->peer = second;
    af_unix_socket_ref_locked(first);
    second->peer = first;
    first->connected = 1;
    second->connected = 1;
    return 0;
}

void af_unix_socket_close_locked(struct af_unix_socket *sock)
{
    if (sock->closed)
    {
        return;
    }

    sock->closed = 1;
    sock->read_shutdown = 1;
    sock->write_shutdown = 1;
    af_unix_namespace_detach_locked(sock);

    while (!rt_list_isempty(&sock->pending_queue))
    {
        struct af_unix_socket *pending;

        pending = rt_list_entry(sock->pending_queue.next,
                                struct af_unix_socket, pending_node);
        rt_list_remove(&pending->pending_node);
        pending->pending = 0;
        sock->pending_count--;
        af_unix_handle_remove_locked(pending);
        af_unix_socket_close_locked(pending);
    }

    af_unix_message_queue_clear_locked(sock);
    rt_wqueue_wakeup_all(&sock->wait_queue,
                         (void *)(rt_ubase_t)(POLLIN | POLLOUT | POLLHUP | POLLERR));
    af_unix_disconnect_locked(sock);
}

void af_unix_wakeup_writable_locked(struct af_unix_socket *sock)
{
    int handle;
    struct af_unix_socket *other;

    rt_wqueue_wakeup_all(&sock->wait_queue, (void *)(rt_ubase_t)POLLOUT);
    for (handle = 0; handle < SAL_SOCKETS_NUM; handle++)
    {
        other = af_unix_handles[handle];
        if (other != RT_NULL && other->peer == sock)
        {
            rt_wqueue_wakeup_all(&other->wait_queue,
                                 (void *)(rt_ubase_t)POLLOUT);
        }
    }
}

static int af_unix_socket_create(int domain, int type, int protocol)
{
    int handle;
    struct af_unix_socket *sock;

    if (domain != AF_UNIX || protocol != 0 ||
        (type != SOCK_DGRAM && type != SOCK_STREAM))
    {
        return af_unix_error(EPROTONOSUPPORT);
    }

    af_unix_lock();
    sock = af_unix_socket_create_locked(type);
    if (sock == RT_NULL)
    {
        af_unix_unlock();
        return af_unix_error(ENOMEM);
    }

    handle = af_unix_handle_alloc_locked(sock);
    if (handle < 0)
    {
        af_unix_socket_unref_locked(sock);
        af_unix_unlock();
        return af_unix_error(EMFILE);
    }
    af_unix_unlock();
    return handle;
}

static int af_unix_close(int handle)
{
    struct af_unix_socket *sock;

    sock = af_unix_socket_get(handle);
    if (sock == RT_NULL)
    {
        return -1;
    }

    af_unix_lock();
    af_unix_handle_remove_locked(sock);
    af_unix_socket_close_locked(sock);
    af_unix_unlock();
    af_unix_socket_put(sock);
    return 0;
}

static int af_unix_bind(int handle, const struct sockaddr *address,
                        socklen_t length)
{
    int result;
    struct af_unix_socket *sock;

    sock = af_unix_socket_get(handle);
    if (sock == RT_NULL)
    {
        return -1;
    }
    result = af_unix_namespace_bind(sock, address, length);
    af_unix_socket_put(sock);
    return result;
}

static int af_unix_listen(int handle, int backlog)
{
    int result;
    struct af_unix_socket *sock;

    sock = af_unix_socket_get(handle);
    if (sock == RT_NULL)
    {
        return -1;
    }
    result = af_unix_stream_listen(sock, backlog);
    af_unix_socket_put(sock);
    return result;
}

static int af_unix_connect(int handle, const struct sockaddr *address,
                           socklen_t length)
{
    int result;
    struct af_unix_socket *sock;

    sock = af_unix_socket_get(handle);
    if (sock == RT_NULL)
    {
        return -1;
    }
    if (sock->type == SOCK_DGRAM)
    {
        result = af_unix_dgram_connect(sock, address, length);
    }
    else
    {
        result = af_unix_stream_connect(sock, address, length);
    }
    af_unix_socket_put(sock);
    return result;
}

static int af_unix_accept(int handle, struct sockaddr *address,
                          socklen_t *length)
{
    int result;
    struct af_unix_socket *sock;

    sock = af_unix_socket_get(handle);
    if (sock == RT_NULL)
    {
        return -1;
    }
    result = af_unix_stream_accept(sock, address, length);
    af_unix_socket_put(sock);
    return result;
}

static int af_unix_sendto_with_rights(
    int handle, const void *data, size_t size, int flags,
    const struct sockaddr *to, socklen_t to_length,
    struct af_unix_rights *rights)
{
    int result;
    struct af_unix_socket *sock;

    sock = af_unix_socket_get(handle);
    if (sock == RT_NULL)
    {
        return -1;
    }
    if (sock->type == SOCK_DGRAM)
    {
        result = af_unix_dgram_send(sock, data, size, flags, to, to_length,
                                    rights);
    }
    else
    {
        if (to != RT_NULL)
        {
            result = af_unix_error(EISCONN);
        }
        else
        {
            result = af_unix_stream_send(sock, data, size, flags, rights);
        }
    }
    af_unix_socket_put(sock);
    return result;
}

static int af_unix_sendto(int handle, const void *data, size_t size, int flags,
                          const struct sockaddr *to, socklen_t to_length)
{
    return af_unix_sendto_with_rights(handle, data, size, flags, to,
                                      to_length, RT_NULL);
}

static int af_unix_recvfrom_with_rights(
    int handle, void *data, size_t size, int flags, struct sockaddr *from,
    socklen_t *from_length, rt_list_t *rights)
{
    int result;
    struct af_unix_socket *sock;

    sock = af_unix_socket_get(handle);
    if (sock == RT_NULL)
    {
        return -1;
    }
    if (sock->type == SOCK_DGRAM)
    {
        result = af_unix_dgram_receive(sock, data, size, flags,
                                       from, from_length, rights);
    }
    else
    {
        result = af_unix_stream_receive(sock, data, size, flags, rights);
        if (result >= 0 && from != RT_NULL)
        {
            (void)af_unix_address_copy(from, from_length,
                                       &sock->peer_address,
                                       sock->peer_length);
        }
    }
    af_unix_socket_put(sock);
    return result;
}

static int af_unix_recvfrom(int handle, void *data, size_t size, int flags,
                            struct sockaddr *from, socklen_t *from_length)
{
    int result;
    rt_list_t rights;

    rt_list_init(&rights);
    result = af_unix_recvfrom_with_rights(handle, data, size, flags, from,
                                          from_length, &rights);
    af_unix_rights_list_release(&rights);
    return result;
}

static int af_unix_sendmsg(int handle, const struct msghdr *message, int flags)
{
    int error;
    int result;
    int index;
    size_t total = 0;
    size_t offset = 0;
    char *buffer = RT_NULL;
    struct af_unix_rights *rights = RT_NULL;

    if (message == RT_NULL || message->msg_iov == RT_NULL ||
        message->msg_iovlen < 0)
    {
        return af_unix_error(EINVAL);
    }
    for (index = 0; index < message->msg_iovlen; index++)
    {
        if (SIZE_MAX - total < message->msg_iov[index].iov_len)
        {
            return af_unix_error(EMSGSIZE);
        }
        total += message->msg_iov[index].iov_len;
    }
    if (message->msg_controllen != 0 && total == 0)
    {
        return af_unix_error(EINVAL);
    }
    if (af_unix_rights_create(message, &rights) < 0)
    {
        return -1;
    }

    if (total != 0)
    {
        buffer = (char *)rt_malloc(total);
        if (buffer == RT_NULL)
        {
            af_unix_rights_release(rights);
            return af_unix_error(ENOMEM);
        }
        for (index = 0; index < message->msg_iovlen; index++)
        {
            rt_memcpy(buffer + offset, message->msg_iov[index].iov_base,
                      message->msg_iov[index].iov_len);
            offset += message->msg_iov[index].iov_len;
        }
    }

    result = af_unix_sendto_with_rights(
        handle, buffer, total, flags,
        (const struct sockaddr *)message->msg_name,
        message->msg_namelen, rights);
    if (result >= 0)
    {
        rights = RT_NULL;
    }
    if (buffer != RT_NULL)
    {
        error = rt_get_errno();
        rt_free(buffer);
        rt_set_errno(error);
    }
    af_unix_rights_release(rights);
    return result;
}

static int af_unix_recvmsg(int handle, struct msghdr *message, int flags)
{
    int error;
    int result;
    int index;
    size_t total = 0;
    size_t offset = 0;
    char *buffer = RT_NULL;
    rt_list_t rights;

    if (message == RT_NULL || message->msg_iov == RT_NULL ||
        message->msg_iovlen < 0)
    {
        return af_unix_error(EINVAL);
    }

    for (index = 0; index < message->msg_iovlen; index++)
    {
        if (SIZE_MAX - total < message->msg_iov[index].iov_len)
        {
            return af_unix_error(EMSGSIZE);
        }
        total += message->msg_iov[index].iov_len;
    }
    if (total != 0)
    {
        buffer = (char *)rt_malloc(total);
        if (buffer == RT_NULL)
        {
            return af_unix_error(ENOMEM);
        }
    }

    rt_list_init(&rights);
    message->msg_flags = 0;
    result = af_unix_recvfrom_with_rights(
        handle, buffer, total, flags,
        (struct sockaddr *)message->msg_name, &message->msg_namelen,
        &rights);
    if (result >= 0)
    {
        size_t remaining = (size_t)result;

        for (index = 0; index < message->msg_iovlen && remaining != 0; index++)
        {
            size_t copy_length = message->msg_iov[index].iov_len;

            if (copy_length > remaining)
            {
                copy_length = remaining;
            }
            rt_memcpy(message->msg_iov[index].iov_base,
                      buffer + offset, copy_length);
            offset += copy_length;
            remaining -= copy_length;
        }
        if ((flags & MSG_PEEK) != 0)
        {
            message->msg_controllen = 0;
        }
        else
        {
            (void)af_unix_rights_deliver(&rights, message);
        }
    }
    af_unix_rights_list_release(&rights);
    if (buffer != RT_NULL)
    {
        error = rt_get_errno();
        rt_free(buffer);
        rt_set_errno(error);
    }
    return result;
}

static int af_unix_getsockname(int handle, struct sockaddr *address,
                               socklen_t *length)
{
    int result;
    struct af_unix_socket *sock;

    sock = af_unix_socket_get(handle);
    if (sock == RT_NULL)
    {
        return -1;
    }
    af_unix_lock();
    result = af_unix_address_copy(address, length, &sock->local_address,
                                  sock->local_length);
    af_unix_unlock();
    af_unix_socket_put(sock);
    return result;
}

static int af_unix_getpeername(int handle, struct sockaddr *address,
                               socklen_t *length)
{
    int result;
    struct af_unix_socket *sock;

    sock = af_unix_socket_get(handle);
    if (sock == RT_NULL)
    {
        return -1;
    }
    af_unix_lock();
    if (!sock->connected)
    {
        result = af_unix_error(ENOTCONN);
    }
    else
    {
        result = af_unix_address_copy(address, length, &sock->peer_address,
                                      sock->peer_length);
    }
    af_unix_unlock();
    af_unix_socket_put(sock);
    return result;
}

static int af_unix_timeout_from_timeval(const struct timeval *time_value)
{
    long long milliseconds;

    if (time_value->tv_sec < 0 || time_value->tv_usec < 0 ||
        time_value->tv_usec >= 1000000)
    {
        return -2;
    }
    if (time_value->tv_sec == 0 && time_value->tv_usec == 0)
    {
        return RT_WAITING_FOREVER;
    }

    milliseconds = (long long)time_value->tv_sec * 1000LL;
    milliseconds += ((long long)time_value->tv_usec + 999LL) / 1000LL;
    if (milliseconds > INT_MAX)
    {
        milliseconds = INT_MAX;
    }
    return (int)milliseconds;
}

static void af_unix_timeval_from_timeout(int timeout,
                                         struct timeval *time_value)
{
    if (timeout == RT_WAITING_FOREVER)
    {
        time_value->tv_sec = 0;
        time_value->tv_usec = 0;
    }
    else
    {
        time_value->tv_sec = timeout / 1000;
        time_value->tv_usec = (timeout % 1000) * 1000;
    }
}

static int af_unix_getsockopt(int handle, int level, int option,
                              void *value, socklen_t *length)
{
    int result = 0;
    int int_value = 0;
    struct timeval time_value;
    struct af_unix_socket *sock;

    if (level != SOL_SOCKET || value == RT_NULL || length == RT_NULL)
    {
        return af_unix_error(EINVAL);
    }

    sock = af_unix_socket_get(handle);
    if (sock == RT_NULL)
    {
        return -1;
    }
    af_unix_lock();
    switch (option)
    {
    case SO_RCVTIMEO:
    case SO_SNDTIMEO:
        if (*length < sizeof(time_value))
        {
            result = af_unix_error(EINVAL);
            break;
        }
        af_unix_timeval_from_timeout(option == SO_RCVTIMEO ? sock->receive_timeout : sock->send_timeout,
                                     &time_value);
        rt_memcpy(value, &time_value, sizeof(time_value));
        *length = sizeof(time_value);
        break;
    case SO_TYPE:
        int_value = sock->type;
        break;
    case SO_DOMAIN:
        int_value = AF_UNIX;
        break;
    case SO_PROTOCOL:
        int_value = 0;
        break;
    case SO_ACCEPTCONN:
        int_value = sock->listening;
        break;
    case SO_ERROR:
        int_value = sock->socket_error;
        sock->socket_error = 0;
        break;
    case SO_SNDBUF:
    case SO_RCVBUF:
        int_value = sock->type == SOCK_DGRAM ? AF_UNIX_DGRAM_MAX_SIZE : AF_UNIX_STREAM_BUFFER_SIZE;
        break;
    default:
        result = af_unix_error(ENOPROTOOPT);
        break;
    }

    if (result == 0 && option != SO_RCVTIMEO && option != SO_SNDTIMEO)
    {
        if (*length < sizeof(int_value))
        {
            result = af_unix_error(EINVAL);
        }
        else
        {
            rt_memcpy(value, &int_value, sizeof(int_value));
            *length = sizeof(int_value);
        }
    }
    af_unix_unlock();
    af_unix_socket_put(sock);
    return result;
}

static int af_unix_setsockopt(int handle, int level, int option,
                              const void *value, socklen_t length)
{
    int result = 0;
    int timeout;
    const struct timeval *time_value;
    struct af_unix_socket *sock;

    if (level != SOL_SOCKET || value == RT_NULL)
    {
        return af_unix_error(EINVAL);
    }
    if (option != SO_RCVTIMEO && option != SO_SNDTIMEO)
    {
        return af_unix_error(ENOPROTOOPT);
    }
    if (length < sizeof(struct timeval))
    {
        return af_unix_error(EINVAL);
    }

    time_value = (const struct timeval *)value;
    timeout = af_unix_timeout_from_timeval(time_value);
    if (timeout == -2)
    {
        return af_unix_error(EINVAL);
    }

    sock = af_unix_socket_get(handle);
    if (sock == RT_NULL)
    {
        return -1;
    }
    af_unix_lock();
    if (option == SO_RCVTIMEO)
    {
        sock->receive_timeout = timeout;
    }
    else
    {
        sock->send_timeout = timeout;
    }
    af_unix_unlock();
    af_unix_socket_put(sock);
    return result;
}

static int af_unix_shutdown(int handle, int how)
{
    int result;
    struct af_unix_socket *sock;

    sock = af_unix_socket_get(handle);
    if (sock == RT_NULL)
    {
        return -1;
    }
    if (sock->type == SOCK_STREAM)
    {
        result = af_unix_stream_shutdown(sock, how);
    }
    else
    {
        if (how < SHUT_RD || how > SHUT_RDWR)
        {
            result = af_unix_error(EINVAL);
        }
        else
        {
            af_unix_lock();
            if (how == SHUT_RD || how == SHUT_RDWR)
            {
                sock->read_shutdown = 1;
            }
            if (how == SHUT_WR || how == SHUT_RDWR)
            {
                sock->write_shutdown = 1;
            }
            rt_wqueue_wakeup_all(&sock->wait_queue,
                                 (void *)(rt_ubase_t)(POLLIN | POLLOUT));
            af_unix_unlock();
            result = 0;
        }
    }
    af_unix_socket_put(sock);
    return result;
}

static int af_unix_ioctl(int handle, long command, void *argument)
{
    int result = 0;
    struct af_unix_socket *sock;

    sock = af_unix_socket_get(handle);
    if (sock == RT_NULL)
    {
        return -1;
    }

    af_unix_lock();
    switch (command)
    {
    case F_GETFL:
        result = sock->flags;
        break;
    case F_SETFL:
        sock->flags &= ~O_NONBLOCK;
        sock->flags |= ((int)(rt_base_t)argument & O_NONBLOCK);
        break;
    case FIONBIO:
        if (argument == RT_NULL)
        {
            result = af_unix_error(EINVAL);
        }
        else if (*(int *)argument != 0)
        {
            sock->flags |= O_NONBLOCK;
        }
        else
        {
            sock->flags &= ~O_NONBLOCK;
        }
        break;
    case FIONREAD:
        if (argument == RT_NULL)
        {
            result = af_unix_error(EINVAL);
        }
        else if (sock->type == SOCK_STREAM)
        {
            *(int *)argument = (int)sock->stream_length;
        }
        else if (rt_list_isempty(&sock->message_queue))
        {
            *(int *)argument = 0;
        }
        else
        {
            struct af_unix_message *message;

            message = rt_list_entry(sock->message_queue.next,
                                    struct af_unix_message, node);
            *(int *)argument = (int)message->length;
        }
        break;
    default:
        result = af_unix_error(EINVAL);
        break;
    }
    af_unix_unlock();
    af_unix_socket_put(sock);
    return result;
}

static int af_unix_socketpair(int domain, int type, int protocol, int *handles)
{
    int result = -1;
    struct af_unix_socket *first;
    struct af_unix_socket *second;

    if (domain != AF_UNIX || protocol != 0 || handles == RT_NULL ||
        (type != SOCK_DGRAM && type != SOCK_STREAM))
    {
        return af_unix_error(EINVAL);
    }

    first = af_unix_socket_get(handles[0]);
    if (first == RT_NULL)
    {
        return -1;
    }
    second = af_unix_socket_get(handles[1]);
    if (second == RT_NULL)
    {
        af_unix_socket_put(first);
        return -1;
    }

    af_unix_lock();
    if (first->type != type || second->type != type ||
        first->closed || second->closed)
    {
        result = af_unix_error(EINVAL);
    }
    else
    {
        result = af_unix_connect_peers_locked(first, second);
        if (result == 0)
        {
            af_unix_address_set(&first->peer_address, &first->peer_length,
                                RT_NULL);
            af_unix_address_set(&second->peer_address, &second->peer_length,
                                RT_NULL);
        }
    }
    af_unix_unlock();
    af_unix_socket_put(second);
    af_unix_socket_put(first);
    return result;
}

static int af_unix_poll(struct dfs_file *file, struct rt_pollreq *request)
{
    int mask = 0;
    int sal_handle;
    struct sal_socket *sal_sock;
    struct af_unix_socket *sock;

    sal_handle = (int)(size_t)file->vnode->data;
    sal_sock = sal_get_socket(sal_handle);
    if (sal_sock == RT_NULL)
    {
        return POLLNVAL;
    }
    sock = af_unix_socket_get((int)(size_t)sal_sock->user_data);
    if (sock == RT_NULL)
    {
        return POLLNVAL;
    }

    /* Register only on this socket. The peer queue can be freed after
     * peer close, while poll teardown still owns the wait-queue node. */
    rt_poll_add(&sock->wait_queue, request);
    af_unix_lock();
    if (sock->closed)
    {
        mask = POLLHUP | POLLERR;
    }
    else if (sock->listening)
    {
        if (sock->pending_count > 0)
        {
            mask |= POLLIN;
        }
    }
    else if (sock->type == SOCK_DGRAM)
    {
        if (sock->message_count > 0 || sock->read_shutdown)
        {
            mask |= POLLIN;
        }
        if (!sock->write_shutdown)
        {
            if (sock->peer != RT_NULL)
            {
                if (!sock->peer->closed &&
                    sock->peer->message_count < AF_UNIX_DGRAM_QUEUE_LEN)
                {
                    mask |= POLLOUT;
                }
            }
            else
            {
                mask |= POLLOUT;
            }
        }
    }
    else
    {
        if (sock->stream_length > 0 || sock->read_shutdown ||
            sock->peer == RT_NULL || sock->peer->write_shutdown ||
            sock->peer->closed)
        {
            mask |= POLLIN;
        }
        if (sock->peer != RT_NULL)
        {
            if (!sock->write_shutdown && !sock->peer->closed &&
                !sock->peer->read_shutdown &&
                sock->peer->stream_length < AF_UNIX_STREAM_BUFFER_SIZE)
            {
                mask |= POLLOUT;
            }
            if (sock->peer->closed)
            {
                mask |= POLLHUP;
            }
        }
        else
        {
            mask |= POLLHUP;
        }
    }
    af_unix_unlock();
    af_unix_socket_put(sock);
    return mask;
}

static const struct sal_socket_ops af_unix_socket_ops = {
    .socket = af_unix_socket_create,
    .closesocket = af_unix_close,
    .bind = af_unix_bind,
    .listen = af_unix_listen,
    .connect = af_unix_connect,
    .accept = af_unix_accept,
    .sendto = af_unix_sendto,
    .sendmsg = af_unix_sendmsg,
    .recvmsg = af_unix_recvmsg,
    .recvfrom = af_unix_recvfrom,
    .getsockopt = af_unix_getsockopt,
    .setsockopt = af_unix_setsockopt,
    .shutdown = af_unix_shutdown,
    .getpeername = af_unix_getpeername,
    .getsockname = af_unix_getsockname,
    .ioctlsocket = af_unix_ioctl,
    .socketpair = af_unix_socketpair,
    .poll = af_unix_poll,
};

static const struct sal_proto_family af_unix_family = {
    .family = AF_UNIX,
    .sec_family = AF_UNIX,
    .skt_ops = &af_unix_socket_ops,
    .netdb_ops = RT_NULL,
};

int af_unix_init(void)
{
    int result;

    rt_memset(af_unix_handles, 0, sizeof(af_unix_handles));
    rt_mutex_init(&af_unix_core_lock, "afunix", RT_IPC_FLAG_PRIO);
    result = af_unix_rights_init();
    if (result != RT_EOK)
    {
        return result;
    }
    result = af_unix_namespace_init();
    if (result != RT_EOK)
    {
        return result;
    }
    return sal_proto_family_register(&af_unix_family);
}
INIT_ENV_EXPORT(af_unix_init);
