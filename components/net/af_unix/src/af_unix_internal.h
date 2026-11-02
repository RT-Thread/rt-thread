/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AF_UNIX_INTERNAL_H__
#define AF_UNIX_INTERNAL_H__

#include <rtthread.h>
#include <dfs.h>
#include <dfs_file.h>
#include <poll.h>
#include <sal_low_lvl.h>
#include <sal_socket.h>

#ifndef AF_UNIX_DGRAM_MAX_SIZE
#define AF_UNIX_DGRAM_MAX_SIZE 4096
#endif

#ifndef AF_UNIX_DGRAM_QUEUE_LEN
#define AF_UNIX_DGRAM_QUEUE_LEN 16
#endif

#ifndef AF_UNIX_STREAM_BUFFER_SIZE
#define AF_UNIX_STREAM_BUFFER_SIZE 4096
#endif

#ifndef AF_UNIX_LISTEN_BACKLOG_MAX
#define AF_UNIX_LISTEN_BACKLOG_MAX 16
#endif

#ifndef AF_UNIX_RIGHTS_MAX
#define AF_UNIX_RIGHTS_MAX 16
#endif

#define AF_UNIX_PATH_MAX ((int)sizeof(((struct sockaddr_un *)0)->sun_path))

struct af_unix_rights
{
    rt_list_t node;
    rt_uint64_t offset;
    size_t count;
    struct dfs_file *files[1];
};

struct af_unix_message
{
    rt_list_t node;
    size_t length;
    struct sockaddr_un source;
    socklen_t source_length;
    struct af_unix_rights *rights;
    char data[1];
};

struct af_unix_socket
{
    int handle;
    int type;
    int flags;
    int ref_count;
    int closed;
    int bound;
    int connected;
    int listening;
    int read_shutdown;
    int write_shutdown;
    int socket_error;
    int receive_timeout;
    int send_timeout;

    struct sockaddr_un local_address;
    socklen_t local_length;
    struct sockaddr_un peer_address;
    socklen_t peer_length;
    struct af_unix_socket *peer;
    void *namespace_entry;

    rt_wqueue_t wait_queue;
    rt_list_t message_queue;
    rt_size_t message_count;

    char *stream_buffer;
    rt_size_t stream_head;
    rt_size_t stream_length;
    rt_uint64_t stream_read_offset;
    rt_uint64_t stream_write_offset;
    rt_list_t rights_queue;

    rt_list_t pending_queue;
    rt_list_t pending_node;
    int pending;
    int backlog;
    int pending_count;
};

void af_unix_lock(void);
void af_unix_unlock(void);
int af_unix_error(int error);
int af_unix_is_nonblocking(const struct af_unix_socket *sock, int flags);
int af_unix_wait(rt_wqueue_t *queue, int timeout);

int af_unix_rights_create(const struct msghdr *message,
                          struct af_unix_rights **rights);
void af_unix_rights_release(struct af_unix_rights *rights);
void af_unix_rights_list_release(rt_list_t *list);
void af_unix_rights_defer_locked(struct af_unix_rights *rights);
void af_unix_rights_list_defer_locked(rt_list_t *list);
void af_unix_rights_drain(void);
int af_unix_rights_deliver(rt_list_t *list, struct msghdr *message);
int af_unix_rights_init(void);

struct af_unix_socket *af_unix_socket_create_locked(int type);
struct af_unix_socket *af_unix_socket_get(int handle);
void af_unix_socket_ref_locked(struct af_unix_socket *sock);
void af_unix_socket_unref_locked(struct af_unix_socket *sock);
void af_unix_socket_put(struct af_unix_socket *sock);
int af_unix_handle_alloc_locked(struct af_unix_socket *sock);
void af_unix_handle_remove_locked(struct af_unix_socket *sock);
void af_unix_socket_close_locked(struct af_unix_socket *sock);
void af_unix_wakeup_writable_locked(struct af_unix_socket *sock);
int af_unix_connect_peers_locked(struct af_unix_socket *first,
                                 struct af_unix_socket *second);
void af_unix_set_peer_locked(struct af_unix_socket *sock,
                             struct af_unix_socket *peer);

int af_unix_address_parse(const struct sockaddr *address, socklen_t length,
                          char path[AF_UNIX_PATH_MAX]);
void af_unix_address_set(struct sockaddr_un *address, socklen_t *length,
                         const char *path);
int af_unix_address_copy(struct sockaddr *address, socklen_t *length,
                         const struct sockaddr_un *source,
                         socklen_t source_length);
int af_unix_namespace_bind(struct af_unix_socket *sock,
                           const struct sockaddr *address, socklen_t length);
struct af_unix_socket *af_unix_namespace_lookup(
    const struct sockaddr *address, socklen_t length, int type,
    struct sockaddr_un *normalized_address, socklen_t *normalized_length);
void af_unix_namespace_detach_locked(struct af_unix_socket *sock);
int af_unix_namespace_init(void);

int af_unix_dgram_connect(struct af_unix_socket *sock,
                          const struct sockaddr *address, socklen_t length);
int af_unix_dgram_send(struct af_unix_socket *sock, const void *data,
                       size_t size, int flags, const struct sockaddr *to,
                       socklen_t to_length, struct af_unix_rights *rights);
int af_unix_dgram_receive(struct af_unix_socket *sock, void *data,
                          size_t size, int flags, struct sockaddr *from,
                          socklen_t *from_length, rt_list_t *rights);

int af_unix_stream_listen(struct af_unix_socket *sock, int backlog);
int af_unix_stream_connect(struct af_unix_socket *sock,
                           const struct sockaddr *address, socklen_t length);
int af_unix_stream_accept(struct af_unix_socket *sock,
                          struct sockaddr *address, socklen_t *length);
int af_unix_stream_send(struct af_unix_socket *sock, const void *data,
                        size_t size, int flags,
                        struct af_unix_rights *rights);
int af_unix_stream_receive(struct af_unix_socket *sock, void *data,
                           size_t size, int flags, rt_list_t *rights);
int af_unix_stream_shutdown(struct af_unix_socket *sock, int how);

#endif /* AF_UNIX_INTERNAL_H__ */
