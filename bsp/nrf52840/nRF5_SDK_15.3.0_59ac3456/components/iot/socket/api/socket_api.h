/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**@file socket_api.h
 *
 * @defgroup iot_socket BSD Socket interface
 * @ingroup iot_sdk_socket
 * @{
 * @brief Nordic socket interface for IoT.
 *
 * @details This module provides the socket interface for writing IoT applications. The API is
 *          designed to be compatible with the POSIX/BSD socket interface for the purpose of
 *          making porting easy. The socket options API has been extended to support configuring
 *          Nordic BLE stack, tuning of RF parameters as well as security options.
 */
#ifndef SOCKET_API_H__
#define SOCKET_API_H__

#include <stdint.h>

#include "sdk_common.h"
#include "iot_defines.h"
#include "errno.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__GNUC__) || (__GNUC__ == 0)
typedef int32_t ssize_t;
#else
#include <sys/types.h>
#ifdef __SES_ARM
typedef int32_t ssize_t;
#endif
#endif

#ifndef htons
#define htons(x) HTONS(x)   /**< Convert byte order from host to network (short). */
#endif

#ifndef htonl
#define htonl(x) HTONL(x)   /**< Convert byte order from host to network (long). */
#endif

#ifndef ntohs
#define ntohs(x) NTOHS(x)   /**< Convert byte order from network to host (short). */
#endif

#ifndef ntohl
#define ntohl(x) NTOHL(x)   /**< Convert byte order from network to host (long). */
#endif

/**@defgroup socket_families Values for socket_family_t
 * @ingroup iot_socket
 * @{
 */
#define AF_INET             2   /**< IPv4 socket family.                 */
#define AF_INET6            10  /**< IPv6 socket family.                 */
#if defined(NRF52) || defined(NRF52_SERIES)
#define AF_NRF_CFG          39  /**< nRF configuration socket.*/
#endif
/**@} */

/**@defgroup socket_types Values for socket_type_t
 * @ingroup iot_socket
 * @{
 */
#define SOCK_STREAM         1        /**< TCP socket type. */
#define SOCK_DGRAM          2        /**< UDP socket type. */
/**@} */

/**@defgroup socket_protocols Values for socket_protocol_t
 * @ingroup iot_socket
 * @{
 */
#define IPPROTO_TCP         1       /**< Use TCP as transport protocol. */
#define IPPROTO_UDP         2       /**< Use UDP as transport protocol. */
/**@} */

/**@defgroup socket_send_recv_flags Socket send/recv flags
 * @ingroup iot_socket
 * @{
 */
#define MSG_DONTROUTE       0x01    /**< Send only to hosts on directly connected networks.                                */
#define MSG_DONTWAIT        0x02    /**< Enables non-blocking operation.                                                    */
#define MSG_OOB             0x04    /**< Sends out-of-band data on sockets that support this.                              */
#define MSG_PEEK            0x08    /**< Return data from the beginning of receive queue without removing data from the queue. */
#define MSG_WAITALL         0x10    /**< Request a blocking operation until the request is satisfied.                            */
/**@} */

#if defined(NRF52) || defined(NRF52_SERIES)
/**
 * @defgroup socket_option_levels Values for socket_opt_lvl_t
 * @ingroup iot_socket
 * @{
 */
#define SOL_SOCKET          1       /**< Standard socket options.                                             */
#define SOL_NRF_MEDIUM      2       /**< Nordic medium socket options. Use this to control medium parameters. */
/**@} */

/**@defgroup socket_medium_options Medium socket option level types
 * @ingroup iot_socket
 * @{
 */
#define MEDIUM_INIT_PARAMS  1       /**< Medium initialization parameters. */
/**@}
 */
#endif

/**@defgroup fcnt_commands fcntl commands
 * @ingroup iot_socket
 * @{
 */
#define F_SETFL             1       /**< Set flag. */
#define F_GETFL             2       /**< Get flag. */
/**@} */

/**@defgroup fcnt_flags fcntl flags
 * @ingroup iot_socket
 * @{
 */
#define O_NONBLOCK          0x01    /**< Use non-blocking I/O. */
/**@} */

/**
 * @brief Socket module size type.
 */
typedef uint32_t socklen_t;

/**
 * @brief Socket port type.
 */
typedef uint16_t in_port_t;

/**
 * @brief Structure specifying time interval.
 */
struct timeval
{
    uint32_t tv_sec;    /**< Time interval seconds. */
    uint32_t tv_usec;   /**< Time interval microseconds. */
};

/**
 * @brief Socket families.
 *
 * @details For a list of valid values, refer to @ref socket_families.
 */
typedef int socket_family_t;
typedef socket_family_t sa_family_t;

/**
 * @brief Socket types.
 *
 * @details For a list of valid values refer to @ref socket_types.
 */
typedef int socket_type_t;

/**
 * @brief Socket protocols.
 *
 * @details Use 0 if you do not want do specify socket protocol, which should be sufficient for most users.
 *          Other values are only provided for socket API compatibility, see @ref socket_protocols.
 */
typedef int socket_protocol_t;

/**
 * @if (IOT)
 * @brief Socket option levels.
 *
 * @details For a list of valid values, refer to @ref socket_option_levels.
 * @endif
 */
typedef int socket_opt_lvl_t;

/**
 * @brief Generic socket address.
 *
 * @details Only provided for API compatibility.
 */
struct sockaddr
{
    uint8_t         sa_len;
    socket_family_t sa_family;
    char            sa_data[];
};

/**
 * @brief IPv6 address.
 */
struct in6_addr
{
    uint8_t s6_addr[16];
};

/**
 * @brief IPv4 address.
 */
typedef uint32_t in_addr_t;

/**
 * @brief IPv4 address structure.
 */
struct in_addr
{
    in_addr_t s_addr;
};

/**
 * @brief Global IPv6 any-address.
 */
extern const struct in6_addr in6addr_any;

/**
 * @brief Global IPv4 any-address.
 */
extern const struct in_addr  inaddr_any;

/**
 * @brief Address record for IPv6 addresses.
 *
 * @details Contains the address and port of the host, as well as other socket options. All fields
 *          in this structure are compatible with the POSIX variant for API compatibility.
 */
struct sockaddr_in6
{
    uint8_t         sin6_len;               /**< Length of this data structure. */
    sa_family_t     sin6_family;            /**< Socket family. */
    in_port_t       sin6_port;              /**< Port, in network byte order. */

    uint32_t        sin6_flowinfo;          /**< IPv6 flow info parameters. Not used. */
    struct in6_addr sin6_addr;              /**< IPv6 address. */
    uint32_t        sin6_scope_id;          /**< IPv6 scope ID. Not used. */
};

/**
 * @brief Address record for IPv4 addresses.
 *
 * @details Contains the address and port of the host. All fields
 *          in this structure are compatible with the POSIX variant for API compatibility.
 */
struct sockaddr_in
{
    uint8_t         sin_len;               /**< Length of this data structure. */
    sa_family_t     sin_family;            /**< Socket family. */
    in_port_t       sin_port;              /**< Port, in network byte order. */

    struct in_addr  sin_addr;              /**< IPv4 address. */
};

typedef struct sockaddr     sockaddr_t;
typedef struct sockaddr_in6 sockaddr_in6_t;
typedef struct in6_addr     in6_addr_t;
typedef struct sockaddr_in  sockaddr_in_t;

/**
 * @brief Function for creating a socket.
 *
 * @details API to create a socket that can be used for network communication independently
 *          of lower protocol layers.
 *
 * @param[in] family    The protocol family of the network protocol to use. Currently, only
 *                      AF_INET6 is supported.
 * @param[in] type      The protocol type to use for this socket.
 * @param[in] protocol  The transport protocol to use for this socket.
 *
 * @return A non-negative socket descriptor on success, or -1 on error.
 */
int socket(socket_family_t family, socket_type_t type, socket_protocol_t protocol);

/**
 * @brief Function for closing a socket and freeing any resources held by it.
 *
 * @details If the socket is already closed, this function is a noop.
 *
 * @param[in] sock  The socket to close.
 *
 * @return 0 on success, or -1 on error.
 */
int close(int sock);

/**
 * @brief Function for controlling file descriptor options.
 *
 * @details Set or get file descriptor options or flags. For a list of supported commands, refer to @ref fcnt_commands.
 *          For a list of supported flags, refer to @ref fcnt_flags.
 *
 * @param[in] fd    The descriptor to set options on.
 * @param[in] cmd   The command class for options.
 * @param[in] flags The flags to set.
 */
int fcntl(int fd, int cmd, int flags);

/**
 * @brief Function for connecting to an endpoint with a given address.
 *
 * @details The socket handle must be a valid handle that has not yet been connected. Running
 *          connect on a connected handle will return an error.
 *
 * @param[in] sock          The socket to use for connection.
 * @param[in] p_servaddr    The address of the server to connect to. Currently, sockaddr_in6 is
 *                          the only supported type.
 * @param[in] addrlen       The size of the p_servaddr argument.
 *
 * @return 0 on success, or -1 on error.
 */
int connect(int sock, const void * p_servaddr, socklen_t addrlen);

/**
 * @brief Function for sending data through a socket.
 *
 * @details By default, this function will block unless the O_NONBLOCK
 *          socket option has been set, OR MSG_DONTWAIT is passed as a flag. In that case, the
 *          method will return immediately.
 *
 * @param[in] sock     The socket to write data to.
 * @param[in] p_buff   Buffer containing the data to send.
 * @param[in] nbytes   Size of data contained on p_buff.
 * @param[in] flags    Flags to control send behavior.
 *
 * @return The number of bytes that were sent on success, or -1 on error.
 */
ssize_t send(int sock, const void * p_buff, size_t nbytes, int flags);

/**
 * @brief Function for sending datagram through a socket.
 *
 * @details By default, this function will block if the lower layers are not able to process the
 *          packet, unless the O_NONBLOCK socket option has been set, OR MSG_DONTWAIT is passed as a flag.
 *          In that case, the method will return immediately.
 *
 * @param[in] sock          The socket to write data to.
 * @param[in] p_buff        Buffer containing the data to send.
 * @param[in] nbytes        Size of data contained in p_buff.
 * @param[in] flags         Flags to control send behavior.
 * @param[in] p_servaddr    The address of the server to send to. Currently, sockaddr_in6 is
 *                          the only supported type.
 * @param[in] addrlen       The size of the p_servaddr argument.
 *
 * @return The number of bytes that were sent on success, or -1 on error.
 */
ssize_t sendto(int          sock,
               const void * p_buff,
               size_t       nbytes,
               int          flags,
               const void * p_servaddr,
               socklen_t    addrlen);

/**
 * @brief Function for writing data to a socket. See \ref send() for details.
 *
 * @param[in] sock     The socket to write data to.
 * @param[in] p_buff   Buffer containing the data to send.
 * @param[in] nbytes   Size of data contained in p_buff.
 *
 * @return The number of bytes that were sent on success, or -1 on error.
 */
ssize_t write(int sock, const void * p_buff, size_t nbytes);

/**
 * @brief Function for receiving data on a socket.
 *
 * @details API for receiving data from a socket. By default, this function will block, unless the
 *          O_NONBLOCK socket option has been set, or MSG_DONTWAIT is passed as a flag.
 *
 * @param[in]  sock     The socket to receive data from.
 * @param[out] p_buff   Buffer to hold the data to be read.
 * @param[in]  nbytes   Number of bytes to read. Should not be larger than the size of p_buff.
 * @param[in]  flags    Flags to control receive behavior.
 *
 * @return The number of bytes that were read, or -1 on error.
 */
ssize_t recv(int sock, void * p_buff, size_t nbytes, int flags);

/**
 * @brief Function for receiving datagram on a socket.
 *
 * @details API for receiving data from a socket. By default, this function will block, unless the
 *          O_NONBLOCK socket option has been set, or MSG_DONTWAIT is passed as a flag.
 *
 * @param[in]    sock         The socket to receive data from.
 * @param[out]   p_buff       Buffer to hold the data to be read.
 * @param[in]    nbytes       Number of bytes to read. Should not be larger than the size of p_buff.
 * @param[in]    flags        Flags to control receive behavior.
 * @param[out]   p_cliaddr    Socket address that will be set to the client's address.
 * @param[inout] p_addrlen    The size of the p_cliaddr passed. Might be modified by the function.
 *
 * @return The number of bytes that were read, or -1 on error.
 */
ssize_t recvfrom(int         sock,
                 void      * p_buff,
                 size_t      nbytes,
                 int         flags,
                 void      * p_cliaddr,
                 socklen_t * p_addrlen);

/**
 * @brief Function for reading data from a socket. See \ref recv() for details.
 *
 * @param[in]  sock     The socket to receive data from.
 * @param[out] p_buff   Buffer to hold the data to be read.
 * @param[in]  nbytes   Number of bytes to read. Should not be larger than the size of p_buff.
 *
 * @return The number of bytes that were read, or -1 on error.
 */
ssize_t read(int sock, void * p_buff, size_t nbytes);

/**
 * @defgroup fd_set_api API for file descriptor set
 * @ingroup iot_socket
 * @details File descriptor sets are used as input to the select() function for doing I/O
 *          multiplexing. The maximum number of descriptors contained in a set is defined by
 *          FD_SETSIZE.
 *
 * @{
 */
#ifndef FD_ZERO

typedef uint32_t fd_set;
#define FD_ZERO(set)            (*(set) = 0)                   /**< Clear the entire set.                 */
#define FD_SET(fd, set)         (*(set) |= (1u << (fd)))       /**< Set a bit in the set.             */
#define FD_CLR(fd, set)         (*(set) &= ~(1u << (fd)))      /**< Clear a bit in the set.           */
#define FD_ISSET(fd, set)       (*(set) & (1u << (fd)))        /**< Check if a bit in the set is set. */
#define FD_SETSIZE              sizeof(fd_set)                 /**< The max size of a set.            */

#endif
/**@} */

/**
 * @brief Function for waiting for read, write, or exception events on a socket.
 *
 * @details Wait for a set of socket descriptors to be ready for reading, writing, or having
 *          exceptions. The set of socket descriptors is configured before calling this function.
 *          This function will block until any of the descriptors in the set has any of the required
 *          events. This function is mostly useful when using O_NONBLOCK or MSG_DONTWAIT options
 *          to enable async operation.
 *
 * @param[in]    nfds          The highest socket descriptor value contained in the sets.
 * @param[inout] p_readset     The set of descriptors for which to wait for read events. Set to NULL
 *                             if not used.
 * @param[inout] p_writeset    The set of descriptors for which to wait for write events. Set to NULL
 *                             if not used.
 * @param[inout] p_exceptset   The set of descriptors for which to wait for exception events. Set to
 *                             NULL if not used.
 * @param[in]    p_timeout     The timeout to use for select call. Set to NULL if waiting forever.
 *
 * @return The number of ready descriptors contained in the descriptor sets on success, or -1 on error.
 */
int select(int                    nfds,
           fd_set               * p_readset,
           fd_set               * p_writeset,
           fd_set               * p_exceptset,
           const struct timeval * p_timeout);

/**
 * @brief Function for setting socket options for a given socket.
 *
 * @details The options are grouped by level, and the option value should be the expected for the
 *          given option, and the lifetime must be longer than that of the socket.
 *
 * @param[in] sock      The socket for which to set the option.
 * @param[in] level     The level or group to which the option belongs.
 * @param[in] optname   The name of the socket option.
 * @param[in] p_optval  The value to be stored for this option.
 * @param[in] optlen    The size of p_optval.
 *
 * @return 0 on success, or -1 on error.
 */
int setsockopt(int              sock,
               socket_opt_lvl_t level,
               int              optname,
               const void     * p_optval,
               socklen_t        optlen);

/**
 * @brief Function for getting socket options for a given socket.
 *
 * @details The options are grouped by level, and the option value is the value described by the
 *          option name.
 *
 * @param[in]       sock      The socket for which to set the option.
 * @param[in]       level     The level or group to which the option belongs.
 * @param[in]       optname   The name of the socket option.
 * @param[out]      p_optval  Pointer to the storage for the option value.
 * @param[inout]    p_optlen  The size of p_optval. Can be modified to the actual size of p_optval.
 *
 * @return 0 on success, or -1 on error.
 */
int getsockopt(int              sock,
               socket_opt_lvl_t level,
               int              optname,
               void           * p_optval,
               socklen_t      * p_optlen);

/**
 * @brief Function for binding a socket to an address and port.
 *
 * @details The provided address must be supported by the socket protocol family.
 *
 * @param[in] sock      The socket descriptor to bind.
 * @param[in] p_myaddr  The address to bind this socket to.
 * @param[in] addrlen   The size of p_myaddr.
 *
 * @return 0 on success, or -1 on error.
 */
int bind(int sock, const void * p_myaddr, socklen_t addrlen);

/**
 * @brief Function for marking a socket as listenable.
 *
 * @details Once a socket is marked as listenable, it cannot be unmarked. It is important to
 *          consider the backlog parameter, as it will affect how much memory your application will
 *          use in the worst case.
 *
 * @param[in] sock      The socket descriptor on which to set the listening options.
 * @param[in] backlog   The max length of the queue of pending connections. A value of 0 means
 *                      infinite.
 *
 * @return 0 on success, or -1 on error.
 */
int listen(int sock, int backlog);

/**
 * @brief Function for waiting for the next client to connect.
 *
 * @details This function will block if there are no clients attempting to connect.
 *
 * @param[in]  sock         The socket descriptor to use for waiting on client connections.
 * @param[out] p_cliaddr    Socket address that will be set to the client's address.
 * @param[out] p_addrlen    The size of the p_cliaddr passed. Might be modified by the function.
 *
 * @return  A non-negative client descriptor on success, or -1 on error.
 */
int accept(int sock, void * p_cliaddr, socklen_t * p_addrlen);

/**
 * @brief Function for converting a human-readable IP address to a form usable by the socket API.
 *
 * @details This function will convert a string form of addresses and encode it into a byte array.
 *
 * @param[in]  af           Address family. Only AF_INET6 supported.
 * @param[in]  p_src        Null-terminated string containing the address to convert.
 * @param[out] p_dst        Pointer to a struct in6_addr where the address will be stored.
 *
 * @return 1 on success, 0 if src does not contain a valid address, -1 if af is not a valid address
 *         family.
 */
int inet_pton(socket_family_t af, const char * p_src, void * p_dst);

#ifdef __cplusplus
}
#endif

#endif //SOCKET_API_H__

/**@} */
