/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include "af_unix_internal.h"

static void af_unix_stream_buffer_write_locked(struct af_unix_socket *sock,
                                               const char *data,
                                               size_t length)
{
    size_t first_length;
    size_t tail;

    tail = (sock->stream_head + sock->stream_length) %
           AF_UNIX_STREAM_BUFFER_SIZE;
    first_length = AF_UNIX_STREAM_BUFFER_SIZE - tail;
    if (first_length > length)
    {
        first_length = length;
    }
    rt_memcpy(sock->stream_buffer + tail, data, first_length);
    if (length > first_length)
    {
        rt_memcpy(sock->stream_buffer, data + first_length,
                  length - first_length);
    }
    sock->stream_length += length;
    sock->stream_write_offset += length;
}

static void af_unix_stream_buffer_read_locked(struct af_unix_socket *sock,
                                              char *data, size_t length,
                                              int peek)
{
    size_t first_length;

    first_length = AF_UNIX_STREAM_BUFFER_SIZE - sock->stream_head;
    if (first_length > length)
    {
        first_length = length;
    }
    rt_memcpy(data, sock->stream_buffer + sock->stream_head, first_length);
    if (length > first_length)
    {
        rt_memcpy(data + first_length, sock->stream_buffer,
                  length - first_length);
    }

    if (!peek)
    {
        sock->stream_head = (sock->stream_head + length) %
                            AF_UNIX_STREAM_BUFFER_SIZE;
        sock->stream_length -= length;
        sock->stream_read_offset += length;
    }
}

static void af_unix_stream_collect_rights_locked(struct af_unix_socket *sock,
                                                 rt_list_t *rights)
{
    while (!rt_list_isempty(&sock->rights_queue))
    {
        struct af_unix_rights *entry;

        entry = rt_list_entry(sock->rights_queue.next,
                              struct af_unix_rights, node);
        if (entry->offset >= sock->stream_read_offset)
        {
            break;
        }
        rt_list_remove(&entry->node);
        rt_list_insert_before(rights, &entry->node);
    }
}

int af_unix_stream_listen(struct af_unix_socket *sock, int backlog)
{
    int result = 0;

    af_unix_lock();
    if (sock->closed)
    {
        result = af_unix_error(EBADF);
    }
    else if (sock->type != SOCK_STREAM)
    {
        result = af_unix_error(EOPNOTSUPP);
    }
    else if (!sock->bound)
    {
        result = af_unix_error(EINVAL);
    }
    else if (sock->connected)
    {
        result = af_unix_error(EINVAL);
    }
    else
    {
        if (backlog < 1)
        {
            backlog = 1;
        }
        if (backlog > AF_UNIX_LISTEN_BACKLOG_MAX)
        {
            backlog = AF_UNIX_LISTEN_BACKLOG_MAX;
        }
        sock->backlog = backlog;
        sock->listening = 1;
    }
    af_unix_unlock();
    return result;
}

int af_unix_stream_connect(struct af_unix_socket *sock,
                           const struct sockaddr *address, socklen_t length)
{
    int handle;
    int nonblocking;
    int timeout;
    int result = -1;
    struct sockaddr_un peer_address;
    socklen_t peer_length;
    struct af_unix_socket *listener;
    struct af_unix_socket *accepted;

    listener = af_unix_namespace_lookup(address, length, SOCK_STREAM,
                                        &peer_address, &peer_length);
    if (listener == RT_NULL)
    {
        return -1;
    }

    for (;;)
    {
        af_unix_lock();
        if (sock->closed)
        {
            result = af_unix_error(EBADF);
            af_unix_unlock();
            break;
        }
        if (sock->connected)
        {
            result = af_unix_error(EISCONN);
            af_unix_unlock();
            break;
        }
        if (listener->closed || !listener->listening)
        {
            result = af_unix_error(ECONNREFUSED);
            af_unix_unlock();
            break;
        }
        if (listener->pending_count < listener->backlog)
        {
            accepted = af_unix_socket_create_locked(SOCK_STREAM);
            if (accepted == RT_NULL)
            {
                result = af_unix_error(ENOMEM);
                af_unix_unlock();
                break;
            }
            handle = af_unix_handle_alloc_locked(accepted);
            if (handle < 0)
            {
                af_unix_socket_unref_locked(accepted);
                result = af_unix_error(EMFILE);
                af_unix_unlock();
                break;
            }

            result = af_unix_connect_peers_locked(sock, accepted);
            if (result < 0)
            {
                af_unix_handle_remove_locked(accepted);
                af_unix_unlock();
                break;
            }

            sock->peer_address = peer_address;
            sock->peer_length = peer_length;
            accepted->local_address = listener->local_address;
            accepted->local_length = listener->local_length;
            accepted->peer_address = sock->local_address;
            accepted->peer_length = sock->local_length;
            accepted->pending = 1;
            rt_list_insert_before(&listener->pending_queue,
                                  &accepted->pending_node);
            listener->pending_count++;
            rt_wqueue_wakeup_all(&listener->wait_queue,
                                 (void *)(rt_ubase_t)POLLIN);
            af_unix_unlock();
            result = 0;
            break;
        }

        nonblocking = af_unix_is_nonblocking(sock, 0);
        timeout = sock->send_timeout;
        af_unix_unlock();
        if (nonblocking)
        {
            result = af_unix_error(EAGAIN);
            break;
        }
        if (af_unix_wait(&listener->wait_queue, timeout) < 0)
        {
            result = -1;
            break;
        }
    }

    af_unix_socket_put(listener);
    return result;
}

int af_unix_stream_accept(struct af_unix_socket *sock,
                          struct sockaddr *address, socklen_t *length)
{
    int handle;
    int nonblocking;
    int timeout;
    int result;
    struct af_unix_socket *accepted;

    for (;;)
    {
        af_unix_lock();
        if (sock->closed)
        {
            af_unix_unlock();
            return af_unix_error(EBADF);
        }
        if (!sock->listening)
        {
            af_unix_unlock();
            return af_unix_error(EINVAL);
        }
        if (!rt_list_isempty(&sock->pending_queue))
        {
            accepted = rt_list_entry(sock->pending_queue.next,
                                     struct af_unix_socket, pending_node);
            result = af_unix_address_copy(address, length,
                                          &accepted->peer_address,
                                          accepted->peer_length);
            if (result < 0)
            {
                af_unix_unlock();
                return result;
            }
            rt_list_remove(&accepted->pending_node);
            accepted->pending = 0;
            sock->pending_count--;
            handle = accepted->handle;
            rt_wqueue_wakeup_all(&sock->wait_queue,
                                 (void *)(rt_ubase_t)POLLOUT);
            af_unix_unlock();
            return handle;
        }

        nonblocking = af_unix_is_nonblocking(sock, 0);
        timeout = sock->receive_timeout;
        af_unix_unlock();
        if (nonblocking)
        {
            return af_unix_error(EAGAIN);
        }
        if (af_unix_wait(&sock->wait_queue, timeout) < 0)
        {
            return -1;
        }
    }
}

int af_unix_stream_send(struct af_unix_socket *sock, const void *data,
                        size_t size, int flags,
                        struct af_unix_rights *rights)
{
    int nonblocking;
    int timeout;
    size_t copy_length;
    size_t space;
    struct af_unix_socket *peer;

    if (size != 0 && data == RT_NULL)
    {
        return af_unix_error(EINVAL);
    }
    if (size == 0)
    {
        return 0;
    }

    for (;;)
    {
        af_unix_lock();
        if (sock->closed)
        {
            af_unix_unlock();
            return af_unix_error(EBADF);
        }
        if (sock->write_shutdown)
        {
            af_unix_unlock();
            return af_unix_error(EPIPE);
        }
        peer = sock->peer;
        if (!sock->connected || peer == RT_NULL)
        {
            af_unix_unlock();
            return af_unix_error(ENOTCONN);
        }
        if (peer->closed || peer->read_shutdown)
        {
            af_unix_unlock();
            return af_unix_error(EPIPE);
        }

        space = AF_UNIX_STREAM_BUFFER_SIZE - peer->stream_length;
        if (space != 0)
        {
            copy_length = size;
            if (copy_length > space)
            {
                copy_length = space;
            }
            if (rights != RT_NULL)
            {
                rights->offset = peer->stream_write_offset;
                rt_list_insert_before(&peer->rights_queue, &rights->node);
            }
            af_unix_stream_buffer_write_locked(peer, (const char *)data,
                                               copy_length);
            rt_wqueue_wakeup_all(&peer->wait_queue,
                                 (void *)(rt_ubase_t)POLLIN);
            af_unix_unlock();
            return (int)copy_length;
        }

        nonblocking = af_unix_is_nonblocking(sock, flags);
        timeout = sock->send_timeout;
        af_unix_socket_ref_locked(peer);
        af_unix_unlock();
        if (nonblocking)
        {
            af_unix_socket_put(peer);
            return af_unix_error(EAGAIN);
        }
        if (af_unix_wait(&peer->wait_queue, timeout) < 0)
        {
            af_unix_socket_put(peer);
            return -1;
        }
        af_unix_socket_put(peer);
    }
}

int af_unix_stream_receive(struct af_unix_socket *sock, void *data,
                           size_t size, int flags, rt_list_t *rights)
{
    int nonblocking;
    int timeout;
    int wait_all;
    size_t copy_length;
    size_t received = 0;
    struct af_unix_socket *peer;

    if (size != 0 && data == RT_NULL)
    {
        return af_unix_error(EINVAL);
    }
    if (size == 0)
    {
        return 0;
    }
    wait_all = ((flags & MSG_WAITALL) != 0 && (flags & MSG_PEEK) == 0);

    for (;;)
    {
        af_unix_lock();
        if (sock->closed)
        {
            af_unix_unlock();
            return received != 0 ? (int)received : af_unix_error(EBADF);
        }
        if (sock->read_shutdown)
        {
            af_unix_unlock();
            return (int)received;
        }
        if (sock->stream_length != 0)
        {
            copy_length = size - received;
            if (copy_length > sock->stream_length)
            {
                copy_length = sock->stream_length;
            }
            af_unix_stream_buffer_read_locked(sock,
                                              (char *)data + received,
                                              copy_length,
                                              (flags & MSG_PEEK) != 0);
            received += copy_length;
            if ((flags & MSG_PEEK) == 0)
            {
                af_unix_stream_collect_rights_locked(sock, rights);
                af_unix_wakeup_writable_locked(sock);
            }
            if (!wait_all || received == size)
            {
                af_unix_unlock();
                return (int)received;
            }
        }

        peer = sock->peer;
        if (peer == RT_NULL || peer->closed || peer->write_shutdown)
        {
            af_unix_unlock();
            return (int)received;
        }

        nonblocking = af_unix_is_nonblocking(sock, flags);
        timeout = sock->receive_timeout;
        af_unix_unlock();
        if (nonblocking)
        {
            return received != 0 ? (int)received : af_unix_error(EAGAIN);
        }
        if (af_unix_wait(&sock->wait_queue, timeout) < 0)
        {
            return received != 0 ? (int)received : -1;
        }
    }
}

int af_unix_stream_shutdown(struct af_unix_socket *sock, int how)
{
    int result = 0;
    struct af_unix_socket *peer;

    if (how < SHUT_RD || how > SHUT_RDWR)
    {
        return af_unix_error(EINVAL);
    }

    af_unix_lock();
    if (sock->closed)
    {
        result = af_unix_error(EBADF);
    }
    else if (!sock->connected)
    {
        result = af_unix_error(ENOTCONN);
    }
    else
    {
        if (how == SHUT_RD || how == SHUT_RDWR)
        {
            sock->read_shutdown = 1;
            sock->stream_head = 0;
            sock->stream_read_offset += sock->stream_length;
            sock->stream_length = 0;
            af_unix_rights_list_defer_locked(&sock->rights_queue);
        }
        if (how == SHUT_WR || how == SHUT_RDWR)
        {
            sock->write_shutdown = 1;
        }
        rt_wqueue_wakeup_all(&sock->wait_queue,
                             (void *)(rt_ubase_t)(POLLIN | POLLOUT));
        peer = sock->peer;
        if (peer != RT_NULL)
        {
            rt_wqueue_wakeup_all(&peer->wait_queue,
                                 (void *)(rt_ubase_t)(POLLIN | POLLOUT));
        }
    }
    af_unix_unlock();
    return result;
}
