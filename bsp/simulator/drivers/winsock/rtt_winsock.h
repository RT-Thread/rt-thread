/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-30     xiangxistu   first version
 */

#define DNS_MAX_NAME_LENGTH 256

/*
 * 1. Define the structure to avoid conflict with winsock's structure.
 * 2. And the same time, in the "af_inet_winsock.c" shouldn't include header files aboult "sal",
 *  if include header files aboult "sal", the complier in the vs2012 will give me "structure redefined error".
 *
 * So, i define the same structure with "sal" but not include header files aboult "sal".
 * The same sturcture means the same memory in the system. I can offer wonderful compatibility with "sal" ,"winsock", "lwip" and so on.
 *
 *
 * Aross the way, "WinSock2.h" only be included in the "af_inet_winsock.c", the more software packages aboult network can
 * work that useless modification is required for "winsock".
 *
 */
typedef uint32_t sal_type_socklen_t;
typedef uint16_t in_port_t;
typedef uint8_t sa_family_t;
typedef uint32_t in_addr_t;

typedef struct sal_type_ip4_addr
{
    uint32_t addr;
} sal_type_ip4_addr_t;
typedef sal_type_ip4_addr_t sal_type_ip_addr_t;

struct sal_type_sockaddr
{
    uint8_t        sa_len;
    sa_family_t    sa_family;
    char           sa_data[14];
};

struct sal_type_in_addr
{
    in_addr_t sal_type_s_addr;
};

struct sal_type_sockaddr_in
{
    uint8_t        sin_len;
    sa_family_t    sin_family;
    in_port_t      sin_port;
    struct sal_type_in_addr sin_addr;
#define SIN_ZERO_LEN 8
    char            sin_zero[SIN_ZERO_LEN];
};

struct sal_type_sockaddr_storage
{
    uint8_t        s2_len;
    sa_family_t    ss_family;
    char           s2_data1[2];
    uint32_t       s2_data2[3];
#if NETDEV_IPV6
    uint32_t       s2_data3[3];
#endif /* NETDEV_IPV6 */
};

struct sal_type_addrinfo {
    int               ai_flags;             /* Input flags. */
    int               ai_family;            /* Address family of socket. */
    int               ai_socktype;          /* Socket type. */
    int               ai_protocol;          /* Protocol of socket. */
    socklen_t         ai_addrlen;           /* Length of socket address. */
    struct sal_type_sockaddr* ai_addr;      /* Socket address of socket. */
    char* ai_canonname;                     /* Canonical name of service location. */
    struct sal_type_addrinfo* ai_next;      /* Pointer to next in list. */
};

struct sal_type_hostent {
    char* h_name;                           /* Official name of the host. */
    char** h_aliases;                       /* A pointer to an array of pointers to alternative host names,
                                                terminated by a null pointer. */
    int    h_addrtype;                      /* Address type. */
    int    h_length;                        /* The length, in bytes, of the address. */
    char** h_addr_list;                     /* A pointer to an array of pointers to network addresses (in
                                                network byte order) for the host, terminated by a null pointer. */
#define h_addr h_addr_list[0]               /* for backward compatibility */
};


/* sal_socket_ops */
int win_socket(int domain, int type, int protocol);
int win_closesocket(int s);
int win_bind(int s, const struct sal_type_sockaddr* name, sal_type_socklen_t namelen);
int win_listen(int s, int backlog);
int win_connect(int s, const struct sal_type_sockaddr* name, sal_type_socklen_t namelen);
int win_accept(int s, struct sal_type_sockaddr* addr, sal_type_socklen_t* addrlen);
int win_sendto(int s, const void* data, size_t size, int flags, const struct sal_type_sockaddr* to, sal_type_socklen_t tolen);
int win_recvfrom(int s, void* mem, size_t len, int flags, struct sal_type_sockaddr* from, sal_type_socklen_t* fromlen);
int win_getsockopt(int s, int level, int optname, void* optval, sal_type_socklen_t* optlen);
int win_setsockopt(int s, int level, int optname, const void* optval, sal_type_socklen_t optlen);
int win_shutdown(int s, int how);
int win_getpeername(int s, struct sal_type_sockaddr* name, sal_type_socklen_t* namelen);
int win_getsockname(int s, struct sal_type_sockaddr* name, sal_type_socklen_t* namelen);
int win_ioctlsocket(int s, long cmd, void* arg);

#ifdef SAL_USING_POSIX
int inet_poll(struct dfs_file* file, struct rt_pollreq* req);
#endif /* SAL_USING_POSIX */


/* sal_netdb_ops */
struct sal_type_hostent* win_gethostbyname(const char* name);
int win_getaddrinfo(const char* nodename, const char* servname, const struct sal_type_addrinfo* hints, struct sal_type_addrinfo** res);
void win_freeaddrinfo(struct sal_type_addrinfo* ai);
