/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-02-17     Bernard      First version
 * 2018-05-17     ChenYong     Add socket abstraction layer
 */

#include <dfs.h>
#include <dfs_file.h>
#include <poll.h>
#include <dfs_net.h>
#include <sys/errno.h>
#include <sys/socket.h>

/**
 * @brief Accepts an incoming connection on a listening socket.
 *
 * This function extracts the first connection request from the queue of pending connections for
 * the listening socket specified by 's' and creates a new socket for the connection.
 *
 * @param s        The file descriptor of the listening socket. This socket must be created with
 *                 'socket()', bound with 'bind()', and set to listen with 'listen()'.
 * @param addr     A pointer to a 'sockaddr' structure that will receive the address of the connecting entity.
 *                 This structure is filled with the address of the client once the connection is accepted.
 *                 Can be 'NULL' if the address is not needed.
 * @param addrlen  A pointer to a variable containing the size of 'addr'. When the function returns, this
 *                 variable will hold the actual size of the address returned. Can be 'NULL' if 'addr' is 'NULL'.
 *
 * @return On success, returns a new file descriptor for the accepted connection. On failure, returns '-1'
 *         and sets errno to indicate the error.
 *
 * @note The original socket 's' remains open and continues to listen for additional incoming connections.
 *       The returned file descriptor is used for communication with the connected client.
 *
 * @see socket() Creates a socket for accepting connections.
 * @see bind() Binds the socket to a local address.
 * @see listen() Sets the socket to listen for incoming connections.
 * @see close()/closesocket() Closes a socket when it is no longer needed.
 */
int accept(int s, struct sockaddr *addr, socklen_t *addrlen)
{
    int new_socket = -1;
    int socket = dfs_net_getsocket(s);

    new_socket = sal_accept(socket, addr, addrlen);
    if (new_socket != -1)
    {
        /* this is a new socket, create it in file system fd */
        int fd;
        struct dfs_file *d;

        /* allocate a fd */
        fd = fd_new();
        if (fd < 0)
        {
            rt_set_errno(-ENOMEM);
            sal_closesocket(new_socket);
            return -1;
        }

        d = fd_get(fd);
        if(d)
        {
#ifdef RT_USING_DFS_V2
            d->fops = dfs_net_get_fops();
#endif
            /* this is a socket fd */
            d->vnode = (struct dfs_vnode *)rt_malloc(sizeof(struct dfs_vnode));
            if (!d->vnode)
            {
                /* release fd */
                fd_release(fd);
                rt_set_errno(-ENOMEM);
                return -1;
            }

            dfs_vnode_init(d->vnode, FT_SOCKET, dfs_net_get_fops());
            d->flags = O_RDWR; /* set flags as read and write */

            /* set socket to the data of dfs_file */
            d->vnode->data = (void *)(size_t)new_socket;

            return fd;
        }

        rt_set_errno(-ENOMEM);
        sal_closesocket(new_socket);
        return -1;
    }

    return -1;
}
RTM_EXPORT(accept);

/**
 * @brief Binds a socket to a specific local address and port.
 *
 * This function assigns a local address to a socket, defined by the 'name' parameter.
 * The address allows the socket to receive data sent to this address.
 *
 * @param s        The file descriptor of the socket to bind.
 * @param name     A pointer to a 'sockaddr' structure that specifies the address to bind to.
 *                 The structure varies based on the address family, such as 'sockaddr_in' for IPv4.
 * @param namelen  The length of the 'sockaddr' structure pointed to by 'name', in bytes.
 *
 * @return Returns '0' on success. On failure, returns '-1' and sets errno to indicate the error.
 *
 * @note The socket must be created with 'socket()' before calling 'bind()'.
 *       Binding is typically used for server sockets, specifying the local IP and port to listen on.
 *       If the port is set to '0', the system assigns an available port automatically.
 *
 * @see socket() Creates a socket for binding.
 * @see listen() Prepares the socket to listen for incoming connections after binding.
 * @see accept() Accepts connections on a bound and listening socket.
 */
int bind(int s, const struct sockaddr *name, socklen_t namelen)
{
    int socket = dfs_net_getsocket(s);

    return sal_bind(socket, name, namelen);
}
RTM_EXPORT(bind);

/**
 * @brief Shuts down part of a full-duplex connection on a socket.
 *
 * This function disables further sends or receives on the specified socket, depending on the value
 * of the 'how' parameter. It does not close the socket, which must still be closed separately using
 * 'close()' or 'closesocket()'.
 *
 * @param s     The file descriptor of the socket to shut down.
 * @param how   Specifies the type of shutdown to perform. The 'how' parameter can be one of the following:
 *              - 'SHUT_RD': Disables further reading on the socket. The socket will not receive data.
 *              - 'SHUT_WR': Disables further writing on the socket. The socket will not send data.
 *              - 'SHUT_RDWR': Disables both reading and writing on the socket. The socket will be fully shut down.
 *
 * @return Returns '0' on success. On failure, returns '-1' and sets errno to indicate the error.
 *
 * @note The 'shutdown()' function is used to gracefully close a socket in one or both directions
 *       (read/write). It is commonly used in scenarios like closing the write side of a TCP connection
 *       when a server has finished sending data but still expects to receive data.
 *
 * @see socket() Creates the socket used for communication.
 * @see close()/closesocket() Closes the socket after the shutdown is complete.
 * @see recv() Receives data on a socket.
 * @see send() Sends data on a socket.
 */
int shutdown(int s, int how)
{
    int error = 0;
    int socket = -1;
    struct dfs_file *d;

    socket = dfs_net_getsocket(s);
    if (socket < 0)
    {
        rt_set_errno(-ENOTSOCK);
        return -1;
    }

    d = fd_get(s);
    if (d == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    if (sal_shutdown(socket, how) == 0)
    {
        error = 0;
    }
    else
    {
        rt_set_errno(-ENOTSOCK);
        error = -1;
    }

    return error;
}
RTM_EXPORT(shutdown);

/**
 * @brief Retrieves the address of the peer connected to a socket.
 *
 * This function obtains the address of the peer (remote end) connected to the socket 's'.
 * It is typically used on connected sockets (e.g., TCP) to retrieve information about the peer.
 *
 * @param s        The file descriptor of the connected socket.
 * @param name     A pointer to a 'sockaddr' structure that will be filled with the address of the peer.
 *                 The structure type (e.g., 'sockaddr_in' for IPv4) depends on the address family of the socket.
 * @param namelen  A pointer to a variable that initially specifies the size of the 'name' structure.
 *                 On return, it contains the actual size of the address returned.
 *
 * @return Returns '0' on success. On failure, returns '-1' and sets errno to indicate the error.
 *
 * @note The 'getpeername()' function is useful for retrieving information about the remote end of a connection,
 *       such as the IP address and port of a peer in a TCP connection. This function is only valid for sockets
 *       that are in a connected state.
 *
 * @see socket() Creates the socket used for the connection.
 * @see connect() Connects the socket to a remote address.
 * @see getsockname() Retrieves the local address of a socket.
 */
int getpeername(int s, struct sockaddr *name, socklen_t *namelen)
{
    int socket = dfs_net_getsocket(s);

    return sal_getpeername(socket, name, namelen);
}
RTM_EXPORT(getpeername);

/**
 * @brief Retrieves the local address of a socket.
 *
 * This function obtains the local address (IP address and port) associated with the socket 's'.
 * It is typically used to determine the local address and port of a bound or connected socket.
 *
 * @param s        The file descriptor of the socket.
 * @param name     A pointer to a 'sockaddr' structure that will be filled with the local address
 *                 of the socket. The structure type (e.g., 'sockaddr_in' for IPv4) depends on the
 *                 address family of the socket.
 * @param namelen  A pointer to a variable that initially specifies the size of the 'name' structure.
 *                 Upon return, this variable contains the actual size of the address returned.
 *
 * @return Returns '0' on success. On failure, returns '-1' and sets errno to indicate the error.
 *
 * @note The 'getsockname()' function is useful for retrieving the local address information of a socket,
 *       which can be especially useful in cases where the socket was bound with an ephemeral port (port 0),
 *       allowing you to discover the actual port number assigned by the system.
 *
 * @see socket() Creates the socket for communication.
 * @see bind() Binds the socket to a specific local address.
 * @see getpeername() Retrieves the address of the peer connected to a socket.
 */
int getsockname(int s, struct sockaddr *name, socklen_t *namelen)
{
    int socket = dfs_net_getsocket(s);

    return sal_getsockname(socket, name, namelen);
}
RTM_EXPORT(getsockname);

/**
 * @brief Retrieves options for a socket.
 *
 * This function retrieves the current value for a specified option on a socket, identified
 * by the file descriptor 's'. The option is specified by the 'level' and 'optname' parameters.
 *
 * @param s        The file descriptor of the socket from which to retrieve the option.
 * @param level    The protocol level at which the option resides. Common levels include:
 *                 - 'SOL_SOCKET': To retrieve socket-level options.
 *                 - 'IPPROTO_IP': To retrieve IPv4 options.
 *                 - 'IPPROTO_TCP': To retrieve TCP options.
 * @param optname  The name of the option to retrieve. Some common options include:
 *                 - 'SO_REUSEADDR': Checks if address reuse is enabled.
 *                 - 'SO_RCVBUF': Retrieves the receive buffer size.
 *                 - 'TCP_NODELAY': Checks if Nagle's algorithm is disabled for TCP sockets.
 * @param optval   A pointer to a buffer where the value of the option will be stored.
 *                 The buffer must be large enough to hold the option value.
 * @param optlen   A pointer to a variable that initially specifies the size of 'optval'.
 *                 On return, it contains the actual size of the option value returned.
 *
 * @return Returns '0' on success. On failure, returns '-1' and sets errno to indicate the error.
 *
 * @note The 'getsockopt()' function is useful for inspecting socket configuration and current settings.
 *       It can provide information about options such as buffer sizes, timeouts, and protocol-specific features.
 *
 * @see socket() Creates the socket to retrieve options from.
 * @see setsockopt() Sets options for the socket.
 */
int getsockopt(int s, int level, int optname, void *optval, socklen_t *optlen)
{
    int socket = dfs_net_getsocket(s);

    return sal_getsockopt(socket, level, optname, optval, optlen);
}
RTM_EXPORT(getsockopt);

/**
 * @brief Sets options on a socket.
 *
 * This function sets the specified option for the socket referenced by the file descriptor 's'.
 * Socket options affect the behavior of the socket and are specified by the 'level' and 'optname' parameters.
 *
 * @param s       The file descriptor of the socket on which to set the option.
 * @param level   The protocol level at which the option resides. Common levels include:
 *                - 'SOL_SOCKET': To configure socket-level options.
 *                - 'IPPROTO_IP': To configure IPv4 options.
 *                - 'IPPROTO_TCP': To configure TCP options.
 * @param optname The name of the option to set. Some common options include:
 *                - 'SO_REUSEADDR': Allows reuse of local addresses.
 *                - 'SO_RCVBUF': Sets the receive buffer size.
 *                - 'TCP_NODELAY': Disables Nagle's algorithm for TCP sockets.
 * @param optval  A pointer to the buffer containing the value to set for the specified option.
 *                The type of data in this buffer depends on the option being set.
 * @param optlen  The size, in bytes, of the option value pointed to by 'optval'.
 *
 * @return Returns '0' on success. On failure, returns '-1' and sets errno to indicate the error.
 *
 * @note The 'setsockopt()' function is useful for configuring various socket behaviors, such as
 *       setting timeouts, buffer sizes, and enabling or disabling certain protocol features.
 *       The changes may affect socket performance and resource usage.
 *
 * @see socket() Creates the socket to configure.
 * @see getsockopt() Retrieves options set on the socket.
 * @see bind() Binds the socket to a local address.
 */
int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen)
{
    int socket = dfs_net_getsocket(s);

    return sal_setsockopt(socket, level, optname, optval, optlen);
}
RTM_EXPORT(setsockopt);

/**
 * @brief Initiates a connection on a socket.
 *
 * This function connects the socket specified by 's' to the server address specified by 'name'.
 * The socket must have been created with 'socket()' and, for some types of sockets, may need
 * to be bound to a local address with 'bind()' before calling 'connect()'.
 *
 * @param s        The file descriptor of the socket to connect.
 * @param name     A pointer to a 'sockaddr' structure that specifies the address of the server to connect to.
 *                 The specific structure (e.g., 'sockaddr_in' for IPv4) depends on the address family.
 * @param namelen  The length, in bytes, of the address structure pointed to by 'name'.
 *
 * @return Returns '0' on success. On failure, returns '-1' and sets errno to indicate the error.
 *
 * @note 'connect()' is typically used by client sockets to establish a connection with a server.
 *       For connection-oriented protocols (e.g., TCP), this initiates the connection handshake.
 *       For connectionless protocols (e.g., UDP), it defines a fixed peer address.
 *
 * @see socket() Creates the socket to be connected.
 * @see bind() Binds the socket to a local address (optional for client sockets).
 * @see accept() Used by server sockets to accept incoming connections.
 * @see close()/closesocket() Closes the socket when done.
 */
int connect(int s, const struct sockaddr *name, socklen_t namelen)
{
    int socket = dfs_net_getsocket(s);
    return sal_connect(socket, name, namelen);
}
RTM_EXPORT(connect);

/**
 * @brief Marks a socket as a passive socket, ready to accept incoming connections.
 *
 * This function prepares a socket to accept incoming connection requests. The socket
 * must first be created with 'socket()' and bound to a local address with 'bind()'.
 *
 * @param s        The file descriptor of the socket to set to listening mode.
 * @param backlog  The maximum number of pending connections that can be queued for acceptance.
 *                 If more incoming connections arrive than the backlog limit, they may be rejected
 *                 or ignored until the server accepts some of the pending connections.
 *
 * @return Returns '0' on success. On failure, returns '-1' and sets errno to indicate the error.
 *
 * @note After calling 'listen()', the socket can be used with 'accept()' to handle connection requests.
 *       The backlog size affects how many connections can wait to be accepted before being rejected.
 *
 * @see socket() Creates the socket.
 * @see bind() Binds the socket to a specific address.
 * @see accept() Accepts a pending connection request on the listening socket.
 */
int listen(int s, int backlog)
{
    int socket = dfs_net_getsocket(s);

    return sal_listen(socket, backlog);
}
RTM_EXPORT(listen);

/**
 * @brief Receives data from a connected socket.
 *
 * This function reads data from a connected socket and stores it in the specified buffer.
 * It is typically used with connection-oriented protocols (e.g., TCP).
 *
 * @param s      The file descriptor of the connected socket to receive data from.
 * @param mem    A pointer to the buffer where the received data will be stored.
 * @param len    The maximum number of bytes to read into the buffer.
 * @param flags  Specifies the behavior of the receive operation. Common flags include:
 *               - '0': Default operation.
 *               - 'MSG_DONTWAIT': Non-blocking operation.
 *               - 'MSG_PEEK': Peeks at the incoming data without removing it from the queue.
 *
 * @return Returns the number of bytes received on success. On failure, returns '-1' and sets errno to indicate the error.
 *         A return value of '0' indicates that the connection has been closed by the remote peer.
 *
 * @note The 'recv()' function may not receive all the requested bytes in a single call.
 *       Multiple calls to 'recv()' may be needed to read the complete data.
 *
 * @see socket() Creates the socket to be used for receiving data.
 * @see connect() Connects the socket to a remote address (for connection-oriented protocols).
 * @see recvfrom() Receives data from a specific address, typically used with connectionless sockets.
 * @see send() Sends data on a connected socket.
 */
int recv(int s, void *mem, size_t len, int flags)
{
    int socket = dfs_net_getsocket(s);

    return sal_recvfrom(socket, mem, len, flags, NULL, NULL);
}
RTM_EXPORT(recv);

/**
 * @brief Sends a message on a socket.
 *
 * The 'sendmsg()' function sends data on the socket 's' using the structured data in the 'msghdr'
 * structure. This function is commonly used for sending complex messages with multiple buffers,
 * control information, or for working with datagram sockets.
 *
 * @param s         The file descriptor of the socket to send the message on.
 * @param message   A pointer to an 'msghdr' structure, which contains the data, address, and control information:
 *                  - 'msg_name': Optional destination address (used for connectionless sockets).
 *                  - 'msg_namelen': Size of the destination address.
 *                  - 'msg_iov': An array of 'iovec' structures that point to the data buffers to be sent.
 *                  - 'msg_iovlen': The number of elements in the 'msg_iov' array.
 *                  - 'msg_control': Optional ancillary data, such as file descriptors for UNIX domain sockets.
 *                  - 'msg_controllen': The size of the ancillary data buffer.
 *                  - 'msg_flags': Flags related to the message.
 * @param flags     Specifies how the message should be sent. Common flags include:
 *                  - 'MSG_DONTWAIT': Sends the message in non-blocking mode.
 *                  - 'MSG_EOR': Indicates the end of a record (for record-oriented sockets).
 *
 * @return Returns the number of bytes sent on success. On failure, returns '-1' and sets errno to indicate the error.
 *
 * @note The 'sendmsg()' function is useful for sending messages with multiple buffers or ancillary data,
 *       allowing flexible communication options such as attaching file descriptors. This function can be
 *       used with both connection-oriented and connectionless sockets.
 *
 * @see recvmsg() Receives a message from a socket.
 * @see send() Sends data on a socket.
 * @see socket() Creates the socket to use with 'sendmsg()'.
 */
int sendmsg(int s, const struct msghdr *message, int flags)
{
    int socket = dfs_net_getsocket(s);

    return sal_sendmsg(socket, message, flags);
}
RTM_EXPORT(sendmsg);

/**
 * @brief Receives a message from a socket.
 *
 * The 'recvmsg()' function receives data from the socket 's' into the buffers described by
 * the 'msghdr' structure. This function allows for complex data structures, including multiple
 * data buffers and optional control information.
 *
 * @param s         The file descriptor of the socket to receive data from.
 * @param message   A pointer to an 'msghdr' structure, which will be filled with the received data and
 *                  information. The structure contains:
 *                  - 'msg_name': A buffer for the source address (used for connectionless sockets).
 *                  - 'msg_namelen': Specifies the size of the 'msg_name' buffer.
 *                  - 'msg_iov': An array of 'iovec' structures that point to the buffers to store received data.
 *                  - 'msg_iovlen': The number of elements in the 'msg_iov' array.
 *                  - 'msg_control': A buffer for ancillary data, such as received file descriptors.
 *                  - 'msg_controllen': The size of the ancillary data buffer.
 *                  - 'msg_flags': Flags set by the 'recvmsg()' call to indicate the message status.
 * @param flags     Specifies how the message should be received. Common flags include:
 *                  - 'MSG_DONTWAIT': Receives the message in non-blocking mode.
 *                  - 'MSG_PEEK': Peeks at the incoming message without removing it from the queue.
 *                  - 'MSG_WAITALL': Waits for the full amount of data to be received.
 *
 * @return Returns the number of bytes received on success. On failure, returns '-1' and sets errno to indicate the error.
 *
 * @note The 'recvmsg()' function is useful for receiving messages with multiple buffers or ancillary data.
 *       It can be used with both connection-oriented and connectionless sockets, making it versatile for
 *       different communication needs.
 *
 * @see sendmsg() Sends a message on a socket.
 * @see recv() Receives data on a socket.
 * @see socket() Creates the socket used with 'recvmsg()'.
 */
int recvmsg(int s, struct msghdr *message, int flags)
{
    int socket = dfs_net_getsocket(s);

    return sal_recvmsg(socket, message, flags);
}
RTM_EXPORT(recvmsg);

/**
 * @brief Receives data from a specific address using an unconnected socket.
 *
 * This function reads data from a socket and stores it in the specified buffer. It is commonly used
 * with connectionless protocols (e.g., UDP) to receive data from a specific source address.
 *
 * @param s        The file descriptor of the socket to receive data from.
 * @param mem      A pointer to the buffer where the received data will be stored.
 * @param len      The maximum number of bytes to read into the buffer.
 * @param flags    Specifies the behavior of the receive operation. Common flags include:
 *                 - '0': Default operation.
 *                 - 'MSG_DONTWAIT': Non-blocking operation.
 *                 - 'MSG_PEEK': Peeks at the incoming data without removing it from the queue.
 * @param from     A pointer to a 'sockaddr' structure that will be filled with the address of the
 *                 sending entity. This is the source address from which the data was received.
 * @param fromlen  A pointer to a variable that initially contains the size of the 'from' structure.
 *                 Upon return, this variable will hold the actual size of the address returned.
 *
 * @return Returns the number of bytes received on success. On failure, returns '-1' and sets errno to indicate the error.
 *         A return value of '0' indicates that the connection has been closed by the remote peer.
 *
 * @note The 'recvfrom()' function is useful for receiving data from an arbitrary source address,
 *       which makes it especially suited for connectionless protocols where the peer's address may vary.
 *       The 'from' parameter is filled with the sender's address, which can be useful for identifying
 *       the origin of the data.
 *
 * @see socket() Creates the socket used for receiving data.
 * @see sendto() Sends data to a specific address, typically used with connectionless sockets.
 * @see recv() Receives data on a connected socket.
 */
int recvfrom(int s, void *mem, size_t len, int flags,
             struct sockaddr *from, socklen_t *fromlen)
{
    int socket = dfs_net_getsocket(s);

    return sal_recvfrom(socket, mem, len, flags, from, fromlen);
}
RTM_EXPORT(recvfrom);

/**
 * @brief Sends data on a connected socket.
 *
 * This function sends data to a connected socket, specified by the file descriptor 's'.
 * It is typically used with connection-oriented protocols (e.g., TCP).
 *
 * @param s        The file descriptor of the socket to send data on.
 *                 The socket must be connected to a remote peer.
 * @param dataptr  A pointer to the buffer containing the data to send.
 * @param size     The size, in bytes, of the data to be sent from the buffer.
 * @param flags    Specifies the behavior of the send operation. Common flags include:
 *                 - '0': Default operation.
 *                 - 'MSG_DONTWAIT': Non-blocking operation.
 *                 - 'MSG_NOSIGNAL': Prevents the sending of 'SIGPIPE' on errors.
 *
 * @return Returns the number of bytes sent on success. On failure, returns '-1' and sets errno to indicate the error.
 *         If the connection is closed by the remote peer, the return value may be '0'.
 *
 * @note The 'send()' function does not guarantee that all data will be sent in a single call.
 *       If fewer bytes are sent than requested, the remaining data should be sent in subsequent calls.
 *
 * @see socket() Creates the socket to be used for sending data.
 * @see connect() Connects the socket to a remote address (for connection-oriented protocols).
 * @see sendto() Sends data to a specific address, typically used with connectionless sockets.
 * @see recv() Receives data from a connected socket.
 */
int send(int s, const void *dataptr, size_t size, int flags)
{
    int socket = dfs_net_getsocket(s);

    return sal_sendto(socket, dataptr, size, flags, NULL, 0);
}
RTM_EXPORT(send);

/**
 * @brief Sends data to a specific address using an unconnected socket.
 *
 * This function is typically used with connectionless protocols (e.g., UDP) to send data
 * to a specific destination address, as specified by 'to'.
 *
 * @param s        The file descriptor of the socket to send data on.
 * @param dataptr  A pointer to the buffer containing the data to be sent.
 * @param size     The size, in bytes, of the data to be sent from the buffer.
 * @param flags    Specifies the behavior of the send operation. Common flags include:
 *                 - '0': Default operation.
 *                 - 'MSG_DONTWAIT': Non-blocking operation.
 *                 - 'MSG_NOSIGNAL': Prevents the sending of 'SIGPIPE' on errors.
 * @param to       A pointer to a 'sockaddr' structure that specifies the destination address.
 *                 The structure type (e.g., 'sockaddr_in' for IPv4) depends on the address family.
 * @param tolen    The length, in bytes, of the address structure pointed to by 'to'.
 *
 * @return Returns the number of bytes sent on success. On failure, returns '-1' and sets errno to indicate the error.
 *
 * @note Unlike 'send()', 'sendto()' can specify a target address for each message, allowing it to be used
 *       for both connected and unconnected sockets. In connectionless protocols, 'sendto()' is commonly
 *       used without prior calls to 'connect()'.
 *
 * @see socket() Creates the socket used for sending data.
 * @see recvfrom() Receives data from a specific address, typically used with connectionless sockets.
 * @see connect() Optional for connection-oriented protocols.
 * @see send() Sends data on a connected socket.
 */
int sendto(int s, const void *dataptr, size_t size, int flags,
           const struct sockaddr *to, socklen_t tolen)
{
    int socket = dfs_net_getsocket(s);

    return sal_sendto(socket, dataptr, size, flags, to, tolen);
}
RTM_EXPORT(sendto);

/**
 * @brief Creates a network socket.
 *
 * This function creates a socket and returns a file descriptor that can be used for network communication.
 *
 * @param domain The communication protocol family (address family) that defines the socket's protocol.
 *               Common values include:
 *               - 'AF_INET': IPv4
 *               - 'AF_INET6': IPv6
 *               - 'AF_UNIX': Local communication (inter-process communication on the same machine)
 *               - 'AF_AT': AT socket
 *               - 'AF_WIZ': WIZnet
 * @param type   The type of socket, which determines the characteristics of data transmission.
 *               Common values include:
 *               - 'SOCK_STREAM': Connection-oriented byte stream communication (e.g., TCP)
 *               - 'SOCK_DGRAM': Connectionless datagram communication (e.g., UDP)
 *               - 'SOCK_RAW': Provides raw network protocol access
 * @param protocol Specifies the protocol to be used with the socket. It is usually set to '0',
 *                 which allows the system to choose the default protocol:
 *                 - For 'SOCK_STREAM', the default is TCP.
 *                 - For 'SOCK_DGRAM', the default is UDP.
 *
 * @return On success, returns a file descriptor (a non-negative integer) representing the socket.
 *         On failure, returns '-1' and sets errno to indicate the error.
 *
 * @note The created socket can be used for binding, listening, receiving, and sending data.
 *
 * @see bind() Used to bind the socket to a local address.
 * @see listen() Used to set the socket to listen for incoming connections.
 * @see accept() Used to accept incoming connection requests.
 * @see connect() Used to connect to a remote host.
 */
int socket(int domain, int type, int protocol)
{
    /* create a BSD socket */
    int fd;
    int socket;
    struct dfs_file *d;

    /* allocate a fd */
    fd = fd_new();
    if (fd < 0)
    {
        rt_set_errno(-ENOMEM);

        return -1;
    }
    d = fd_get(fd);

#ifdef RT_USING_DFS_V2
    d->fops = dfs_net_get_fops();
#endif

    d->vnode = (struct dfs_vnode *)rt_malloc(sizeof(struct dfs_vnode));
    if (!d->vnode)
    {
        /* release fd */
        fd_release(fd);
        rt_set_errno(-ENOMEM);
        return -1;
    }

    /* create socket  and then put it to the dfs_file */
    socket = sal_socket(domain, type, protocol);
    if (socket >= 0)
    {
        dfs_vnode_init(d->vnode, FT_SOCKET, dfs_net_get_fops());
        d->flags = O_RDWR; /* set flags as read and write */

        /* set socket to the data of dfs_file */
        d->vnode->data = (void *)(size_t)socket;
    }
    else
    {
        /* release fd */
        fd_release(fd);
        rt_set_errno(-ENOMEM);
        return -1;
    }

    return fd;
}
RTM_EXPORT(socket);

/**
 * @brief Closes a socket.
 *
 * This function closes the socket specified by the file descriptor 's'. Once closed, the socket
 * can no longer be used for communication. Any pending data that has not been transmitted may be lost.
 *
 * @param s The file descriptor of the socket to close.
 *
 * @return Returns '0' on success. On failure, returns '-1' and sets errno to indicate the error.
 *
 * @note After calling 'closesocket()', the socket descriptor becomes invalid. The socket cannot
 *       be used for further communication or operations. It is important to close sockets when they are no longer needed
 *       to release system resources.
 *
 * @see socket() Creates a socket.
 * @see shutdown() Shuts down the socket for reading and/or writing, without closing it.
 * @see recv() Receives data from a socket.
 * @see send() Sends data on a socket.
 */
int closesocket(int s)
{
    int error = 0;
    int socket = -1;
    struct dfs_file *d;

    socket = dfs_net_getsocket(s);
    if (socket < 0)
    {
        rt_set_errno(-ENOTSOCK);
        return -1;
    }

    d = fd_get(s);
    if (d == RT_NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    if (!d->vnode)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    if (sal_closesocket(socket) == 0)
    {
        error = 0;
    }
    else
    {
        rt_set_errno(-ENOTSOCK);
        error = -1;
    }

    /* socket has been closed, delete it from file system fd */
    fd_release(s);

    return error;
}
RTM_EXPORT(closesocket);

/**
 * @brief Creates a pair of connected sockets.
 *
 * The 'socketpair()' function creates two connected sockets, which can be used for bidirectional
 * communication between processes or threads on the same machine. This is commonly used for inter-process
 * communication (IPC) in UNIX-like operating systems.
 *
 * @param domain   The communication domain (or protocol family). Typically, 'AF_UNIX' (or 'AF_LOCAL')
 *                 is used to create sockets for local communication.
 * @param type     The type of socket to be created. Common values include:
 *                 - 'SOCK_STREAM': Provides reliable, connection-oriented communication.
 *                 - 'SOCK_DGRAM': Provides connectionless, unreliable communication.
 * @param protocol The protocol to be used with the sockets. Normally set to '0' to use the default protocol
 *                 for the specified 'domain' and 'type'.
 * @param fds      An array of two integers where the file descriptors for the two connected sockets will be stored.
 *                 After a successful call, 'fds[0]' and 'fds[1]' represent the two ends of the socket pair.
 *
 * @return Returns '0' on success. On failure, returns '-1' and sets 'errno' to indicate the error.
 *
 * @note The 'socketpair()' function is commonly used to create a communication channel between two processes
 *       (parent and child after 'fork()') or two threads. Data written to one socket is available for reading
 *       from the other. It is primarily supported on UNIX-like systems and may not be available on Windows.
 *
 * @see socket() Creates a single socket for network communication.
 * @see pipe() Creates an unidirectional communication channel between processes.
 */
int socketpair(int domain, int type, int protocol, int *fds)
{
    rt_err_t ret = 0;
    int sock_fds[2];

    fds[0] = socket(domain, type, protocol);
    if (fds[0] < 0)
    {
        fds[0] = 0;
        return -1;
    }

    fds[1] = socket(domain, type, protocol);
    if (fds[1] < 0)
    {
        closesocket(fds[0]);
        fds[0] = 0;
        fds[1] = 0;
        return -1;
    }

    sock_fds[0] = dfs_net_getsocket(fds[0]);
    sock_fds[1] = dfs_net_getsocket(fds[1]);

    ret = sal_socketpair(domain, type, protocol, sock_fds);

    if (ret < 0)
    {
        closesocket(fds[0]);
        closesocket(fds[1]);
    }

    return ret;
}
RTM_EXPORT(socketpair);

/**
 * @brief Controls socket I/O modes.
 *
 * The 'ioctlsocket()' function manipulates the I/O mode of the socket specified by the file descriptor 's'.
 * It is primarily used to enable or disable non-blocking mode on a socket or to perform other socket-specific
 * operations.
 *
 * @param s     The file descriptor of the socket to control.
 * @param cmd   The command that specifies the operation to perform. Some common commands include:
 *              - 'FIONBIO': Enables or disables non-blocking mode. Setting 'arg' to a non-zero value
 *                enables non-blocking mode; setting it to zero disables it.
 *              - 'FIONREAD': Retrieves the number of bytes available to read, storing the result in 'arg'.
 * @param arg   A pointer to an argument for the command. The type and meaning of this argument depend on the
 *              specified command ('cmd'). For example, in non-blocking mode ('FIONBIO'), it points to a 'long'
 *              that is either non-zero (to enable) or zero (to disable) non-blocking mode.
 *
 * @return Returns '0' on success. On failure, returns '-1' and sets errno (or 'WSAGetLastError()' on Windows) to indicate the error.
 *
 * @note This function is specific to Windows environments and is a part of the Winsock API. It performs
 *       similar functionality to the 'fcntl()' function on UNIX-like systems.
 *       The 'ioctlsocket()' function allows for various socket manipulations that affect how the socket
 *       operates in certain conditions, such as setting it to non-blocking mode.
 *
 * @see socket() Creates a socket to use with 'ioctlsocket()'.
 * @see fcntl() Performs similar operations on UNIX-like systems.
 */
int ioctlsocket(int s, long cmd, void *arg)
{
    int socket = dfs_net_getsocket(s);

    return sal_ioctlsocket(socket, cmd, arg);
}
RTM_EXPORT(ioctlsocket);
