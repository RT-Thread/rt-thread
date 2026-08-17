/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include "af_unix_internal.h"

int af_unix_dgram_connect(struct af_unix_socket *sock,
                          const struct sockaddr *address, socklen_t length)
{
    int result = 0;
    struct sockaddr_un peer_address;
    socklen_t peer_length;
    struct af_unix_socket *peer;

    peer = af_unix_namespace_lookup(address, length, SOCK_DGRAM,
                                    &peer_address, &peer_length);
    if (peer == RT_NULL)
    {
        return -1;
    }

    af_unix_lock();
    if (sock->closed)
    {
        result = af_unix_error(EBADF);
    }
    else if (sock->write_shutdown)
    {
        result = af_unix_error(EPIPE);
    }
    else
    {
        af_unix_set_peer_locked(sock, peer);
        sock->peer_address = peer_address;
        sock->peer_length = peer_length;
        sock->connected = 1;
    }
    af_unix_unlock();
    af_unix_socket_put(peer);
    return result;
}

static struct af_unix_socket *af_unix_dgram_target_get(
    struct af_unix_socket *sock, const struct sockaddr *to,
    socklen_t to_length)
{
    struct af_unix_socket *peer = RT_NULL;

    if (to != RT_NULL)
    {
        return af_unix_namespace_lookup(to, to_length, SOCK_DGRAM,
                                        RT_NULL, RT_NULL);
    }

    af_unix_lock();
    if (sock->connected && sock->peer != RT_NULL)
    {
        peer = sock->peer;
        af_unix_socket_ref_locked(peer);
    }
    af_unix_unlock();

    if (peer == RT_NULL)
    {
        af_unix_error(EDESTADDRREQ);
    }
    return peer;
}

int af_unix_dgram_send(struct af_unix_socket *sock, const void *data,
                       size_t size, int flags, const struct sockaddr *to,
                       socklen_t to_length, struct af_unix_rights *rights)
{
    int error;
    int result;
    int nonblocking;
    int timeout;
    struct af_unix_socket *peer;
    struct af_unix_message *message;

    if (size > AF_UNIX_DGRAM_MAX_SIZE)
    {
        return af_unix_error(EMSGSIZE);
    }
    if (size != 0 && data == RT_NULL)
    {
        return af_unix_error(EINVAL);
    }

    peer = af_unix_dgram_target_get(sock, to, to_length);
    if (peer == RT_NULL)
    {
        return -1;
    }

    message = (struct af_unix_message *)rt_malloc(sizeof(*message) + size);
    if (message == RT_NULL)
    {
        af_unix_socket_put(peer);
        return af_unix_error(ENOMEM);
    }
    rt_list_init(&message->node);
    message->length = size;
    message->rights = rights;
    if (size != 0)
    {
        rt_memcpy(message->data, data, size);
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
        if (sock->write_shutdown)
        {
            result = af_unix_error(EPIPE);
            af_unix_unlock();
            break;
        }
        if (peer->closed)
        {
            result = af_unix_error(ECONNREFUSED);
            af_unix_unlock();
            break;
        }
        if (peer->read_shutdown)
        {
            result = af_unix_error(EPIPE);
            af_unix_unlock();
            break;
        }
        if (peer->message_count < AF_UNIX_DGRAM_QUEUE_LEN)
        {
            message->source = sock->local_address;
            message->source_length = sock->local_length;
            rt_list_insert_before(&peer->message_queue, &message->node);
            peer->message_count++;
            rt_wqueue_wakeup_all(&peer->wait_queue,
                                 (void *)(rt_ubase_t)POLLIN);
            af_unix_unlock();
            af_unix_socket_put(peer);
            return (int)size;
        }

        nonblocking = af_unix_is_nonblocking(sock, flags);
        timeout = sock->send_timeout;
        af_unix_unlock();
        if (nonblocking)
        {
            result = af_unix_error(EAGAIN);
            break;
        }
        if (af_unix_wait(&peer->wait_queue, timeout) < 0)
        {
            result = -1;
            break;
        }
    }

    error = rt_get_errno();
    rt_free(message);
    af_unix_socket_put(peer);
    rt_set_errno(error);
    return result;
}

int af_unix_dgram_receive(struct af_unix_socket *sock, void *data,
                          size_t size, int flags, struct sockaddr *from,
                          socklen_t *from_length, rt_list_t *rights)
{
    int result;
    int nonblocking;
    int timeout;
    size_t copy_length;
    struct af_unix_message *message;

    if (size != 0 && data == RT_NULL)
    {
        return af_unix_error(EINVAL);
    }

    for (;;)
    {
        af_unix_lock();
        if (sock->closed)
        {
            af_unix_unlock();
            return af_unix_error(EBADF);
        }
        if (!rt_list_isempty(&sock->message_queue))
        {
            message = rt_list_entry(sock->message_queue.next,
                                    struct af_unix_message, node);
            copy_length = message->length;
            if (copy_length > size)
            {
                copy_length = size;
            }
            if (copy_length != 0)
            {
                rt_memcpy(data, message->data, copy_length);
            }
            result = af_unix_address_copy(from, from_length,
                                          &message->source,
                                          message->source_length);
            if (result < 0)
            {
                af_unix_unlock();
                return result;
            }
            if ((flags & MSG_PEEK) == 0)
            {
                rt_list_remove(&message->node);
                sock->message_count--;
                if (message->rights != RT_NULL)
                {
                    rt_list_insert_before(rights, &message->rights->node);
                    message->rights = RT_NULL;
                }
                af_unix_wakeup_writable_locked(sock);
                rt_free(message);
            }
            af_unix_unlock();
            return (int)copy_length;
        }
        if (sock->read_shutdown)
        {
            af_unix_unlock();
            return 0;
        }

        nonblocking = af_unix_is_nonblocking(sock, flags);
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
