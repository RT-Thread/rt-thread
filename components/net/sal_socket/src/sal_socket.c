/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-23     ChenYong     First version
 * 2018-11-12     ChenYong     Add TLS support
 */

#include <rtthread.h>
#include <rthw.h>

#include <sal_socket.h>
#include <sal_netdb.h>
#ifdef SAL_USING_TLS
#include <sal_tls.h>
#endif
#include <sal.h>

#define DBG_ENABLE
#define DBG_SECTION_NAME               "SAL_SOC"
#define DBG_LEVEL                      DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

#define SOCKET_TABLE_STEP_LEN          4

/* the socket table used to dynamic allocate sockets */
struct sal_socket_table
{
    uint32_t max_socket;
    struct sal_socket **sockets;
};

#ifdef SAL_USING_TLS
/* The global TLS protocol options */
static struct sal_proto_tls *proto_tls;
#endif

/* The global array of available protocol families */
static struct sal_proto_family proto_families[SAL_PROTO_FAMILIES_NUM];
/* The global socket table */
static struct sal_socket_table socket_table;
static struct rt_mutex sal_core_lock;
static rt_bool_t init_ok = RT_FALSE;

#define IS_SOCKET_PROTO_TLS(sock)                (((sock)->protocol == PROTOCOL_TLS) || \
                                                 ((sock)->protocol == PROTOCOL_DTLS))
#define SAL_SOCKOPS_PROTO_TLS_VALID(sock, name)  (proto_tls && (proto_tls->ops->name) && IS_SOCKET_PROTO_TLS(sock))

#define SAL_SOCKOPT_PROTO_TLS_EXEC(sock, name, optval, optlen)                    \
do                                                                                \
{                                                                                 \
    if (SAL_SOCKOPS_PROTO_TLS_VALID(sock, name))                                  \
    {                                                                             \
        return proto_tls->ops->name((sock)->user_data_tls, (optval), (optlen));   \
    }                                                                             \
}while(0)                                                                         \


/**
 * SAL (Socket Abstraction Layer) initialize.
 *
 * @return result  0: initialize success
 *                -1: initialize failed        
 */
int sal_init(void)
{
    int cn;
    
    if (init_ok)
    {
        LOG_D("Socket Abstraction Layer is already initialized.");
        return 0;
    }

    /* init sal socket table */
    cn = SOCKET_TABLE_STEP_LEN < SAL_SOCKETS_NUM ? SOCKET_TABLE_STEP_LEN : SAL_SOCKETS_NUM;
    socket_table.max_socket = cn;
    socket_table.sockets = rt_calloc(1, cn * sizeof(struct sal_socket *));
    if (socket_table.sockets == RT_NULL)
    {
        LOG_E("No memory for socket table.\n");
        return -1;
    }
    
    /* create sal socket lock */
    rt_mutex_init(&sal_core_lock, "sal_lock", RT_IPC_FLAG_FIFO);

    LOG_I("Socket Abstraction Layer initialize success.");
    init_ok = RT_TRUE;

    return 0;
}
INIT_COMPONENT_EXPORT(sal_init);

/**
 * This function will register TLS protocol to the global TLS protocol.
 *
 * @param pt TLS protocol object
 *
 * @return 0: TLS protocol object register success
 */
#ifdef SAL_USING_TLS
int sal_proto_tls_register(const struct sal_proto_tls *pt)
{
    RT_ASSERT(pt);
    proto_tls = (struct sal_proto_tls *) pt;

    return 0;
}
#endif

/**
 * This function will register protocol family to the global array of protocol families.
 *
 * @param pf protocol family object
 *
 * @return  0: protocol family object register success
 *         -1: the global array of available protocol families is full
 */
int sal_proto_family_register(const struct sal_proto_family *pf)
{
    rt_base_t level;
    int idx;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* check protocol family is already registered */
    for(idx = 0; idx < SAL_PROTO_FAMILIES_NUM; idx++)
    {
        if (proto_families[idx].family == pf->family && proto_families[idx].create)
        {
            /* enable interrupt */
            rt_hw_interrupt_enable(level);
            LOG_E("%s protocol family is already registered!", pf->family);
            return -1;
        }
    }

    /* find an empty protocol family entry */
    for(idx = 0; idx < SAL_PROTO_FAMILIES_NUM && proto_families[idx].create; idx++);

    /* can't find an empty protocol family entry */
    if (idx == SAL_PROTO_FAMILIES_NUM)
    {
        /* enable interrupt */
        rt_hw_interrupt_enable(level);
        return -1;
    }

    proto_families[idx].family = pf->family;
    proto_families[idx].sec_family = pf->sec_family;
    proto_families[idx].create = pf->create;

    proto_families[idx].ops = pf->ops;
    proto_families[idx].ops->gethostbyname = pf->ops->gethostbyname;
    proto_families[idx].ops->gethostbyname_r = pf->ops->gethostbyname_r;
    proto_families[idx].ops->freeaddrinfo = pf->ops->freeaddrinfo;
    proto_families[idx].ops->getaddrinfo = pf->ops->getaddrinfo;

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return 0;
}

/**
 * This function removes a previously registered protocol family object.
 *
 * @param pf protocol family object
 *
 * @return >=0 : unregister protocol family index
 *          -1 : unregister failed
 */
int sal_proto_family_unregister(int family)
{
    int idx = 0;

    RT_ASSERT(family > 0 && family < AF_MAX);

    for(idx = 0; idx < SAL_PROTO_FAMILIES_NUM; idx++)
    {
        if (proto_families[idx].family == family && proto_families[idx].create)
        {
            rt_memset(&proto_families[idx], 0x00, sizeof(struct sal_proto_family));

            return idx;
        }
    }

    return -1;
}

/**
 * This function will judge whether protocol family is registered
 *
 * @param family protocol family number
 *
 * @return 1: protocol family is registered
 *         0: protocol family is not registered
 */
rt_bool_t sal_proto_family_is_registered(int family)
{
    int idx = 0;

    RT_ASSERT(family > 0 && family < AF_MAX);

    for (idx = 0; idx < SAL_PROTO_FAMILIES_NUM; idx++)
    {
        if (proto_families[idx].family == family && proto_families[idx].create)
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

/**
 * This function will get protocol family object by family number.
 *
 * @param family protocol family number
 *
 * @return protocol family object
 */
struct sal_proto_family *sal_proto_family_find(int family)
{
    int idx = 0;

    RT_ASSERT(family > 0 && family < AF_MAX);

    for (idx = 0; idx < SAL_PROTO_FAMILIES_NUM; idx++)
    {
        if (proto_families[idx].family == family && proto_families[idx].create)
        {
            return &proto_families[idx];
        }
    }

    return RT_NULL;
}

/**
 * This function will get sal socket object by sal socket descriptor.
 *
 * @param socket sal socket index
 *
 * @return sal socket object of the current sal socket index
 */
struct sal_socket *sal_get_socket(int socket)
{
    struct sal_socket_table *st = &socket_table;

    if (socket < 0 || socket >= (int) st->max_socket)
    {
        return RT_NULL;
    }

    socket = socket - SAL_SOCKET_OFFSET;
    /* check socket structure valid or not */
    if (st->sockets[socket]->magic != SAL_SOCKET_MAGIC)
    {
        return RT_NULL;
    }

    return st->sockets[socket];
}

/**
 * This function will lock sal socket.
 *
 * @note please don't invoke it on ISR.
 */
static void sal_lock(void)
{
    rt_err_t result;

    result = rt_mutex_take(&sal_core_lock, RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        RT_ASSERT(0);
    }
}

/**
 * This function will lock sal socket.
 *
 * @note please don't invoke it on ISR.
 */
static void sal_unlock(void)
{
    rt_mutex_release(&sal_core_lock);
}

/**
 * This function will get protocol family structure by family type
 *
 * @param family  protocol family
 *
 * @return protocol family structure address
 */
static struct sal_proto_family *get_proto_family(int family)
{
    int idx;

    for (idx = 0; idx < SAL_PROTO_FAMILIES_NUM; idx++)
    {
        if (proto_families[idx].family == family && proto_families[idx].create)
        {
            return &proto_families[idx];
        }
    }
    /* compare the secondary protocol families when primary protocol families find failed */
    for (idx = 0; idx < SAL_PROTO_FAMILIES_NUM; idx++)
    {
        if (proto_families[idx].sec_family == family && proto_families[idx].create)
        {
            return &proto_families[idx];
        }
    }

    return RT_NULL;
}

/**
 * This function will initialize sal socket object and set socket options
 *
 * @param family    protocol family
 * @param type      socket type
 * @param protocol  transfer Protocol
 * @param res       sal socket object address
 *
 * @return  0 : socket initialize success
 *         -1 : input the wrong family
 *         -2 : input the wrong socket type
 *         -3 : get protocol family object failed
 *         -4 : set socket options failed
 */
static int socket_init(int family, int type, int protocol, struct sal_socket **res)
{
    struct sal_socket *sock;
    struct sal_proto_family *pf;

    if (family < 0 || family > AF_MAX)
    {
        return -1;
    }

    if (type < 0 || type > SOCK_MAX)
    {
        return -2;
    }

    sock = *res;
    sock->domain = family;
    sock->type = type;
    sock->protocol = protocol;

    /* get socket protocol family object */
    if ((pf = get_proto_family(family)) == RT_NULL)
    {
        return -3;
    }

    /* registered the current socket options */
    if (pf->create(sock, type, protocol) != 0)
    {
        return -4;
    }

    return 0;
}

static int socket_alloc(struct sal_socket_table *st, int f_socket)
{
    int idx;

    /* find an empty socket entry */
    for (idx = f_socket; idx < (int) st->max_socket; idx++)
    {
        if (st->sockets[idx] == RT_NULL)
            break;
        if (st->sockets[idx]->ops == RT_NULL)
            break;
    }

    /* allocate a larger sockte container */
    if (idx == (int) st->max_socket &&  st->max_socket < SAL_SOCKETS_NUM)
    {
        int cnt, index;
        struct sal_socket **sockets;

        /* increase the number of socket with 4 step length */
        cnt = st->max_socket + SOCKET_TABLE_STEP_LEN;
        cnt = cnt > SAL_SOCKETS_NUM ? SAL_SOCKETS_NUM : cnt;

        sockets = rt_realloc(st->sockets, cnt * sizeof(struct sal_socket *));
        if (sockets == RT_NULL)
            goto __result; /* return st->max_socket */

        /* clean the new allocated fds */
        for (index = st->max_socket; index < cnt; index++)
        {
            sockets[index] = RT_NULL;
        }

        st->sockets = sockets;
        st->max_socket = cnt;
    }

    /* allocate  'struct sal_socket' */
    if (idx < (int) st->max_socket && st->sockets[idx] == RT_NULL)
    {
        st->sockets[idx] = rt_calloc(1, sizeof(struct sal_socket));
        if (st->sockets[idx] == RT_NULL)
        {
            idx = st->max_socket;
        }
    }

__result:
    return idx;

}

static int socket_new(void)
{
    struct sal_socket *sock;
    struct sal_socket_table *st = &socket_table;
    int idx;

    sal_lock();

    /* find an empty sal socket entry */
    idx = socket_alloc(st, 0);

    /* can't find an empty sal socket entry */
    if (idx == (int) st->max_socket)
    {
        idx = -(1 + SAL_SOCKET_OFFSET);
        goto __result;
    }

    sock = st->sockets[idx];
    sock->socket = idx + SAL_SOCKET_OFFSET;
    sock->magic = SAL_SOCKET_MAGIC;
    sock->ops = RT_NULL;
    sock->user_data = RT_NULL;
#ifdef SAL_USING_TLS
    sock->user_data_tls = RT_NULL;
#endif

__result:
    sal_unlock();
    return idx + SAL_SOCKET_OFFSET;
}

int sal_accept(int socket, struct sockaddr *addr, socklen_t *addrlen)
{
    int new_socket;
    struct sal_socket *sock;

    sock = sal_get_socket(socket);
    if (!sock)
    {
        return -1;
    }

    if (sock->ops->accept == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    new_socket = sock->ops->accept((int) sock->user_data, addr, addrlen);
    if (new_socket != -1)
    {
        int retval;
        int new_sal_socket;
        struct sal_socket *new_sock;

        /* allocate a new socket structure and registered socket options */
        new_sal_socket = socket_new();
        if (new_sal_socket < 0)
        {
            sock->ops->closesocket(new_socket);
            return -1;
        }
        new_sock = sal_get_socket(new_sal_socket);

        retval = socket_init(sock->domain, sock->type, sock->protocol, &new_sock);
        if (retval < 0)
        {
            sock->ops->closesocket(new_socket);
            rt_memset(new_sock, 0x00, sizeof(struct sal_socket));
            LOG_E("New socket registered failed, return error %d.", retval);
            return -1;
        }

        /* socket struct user_data used to store the acquired new socket */
        new_sock->user_data = (void *) new_socket;

        return new_sal_socket;
    }

    return -1;
}

int sal_bind(int socket, const struct sockaddr *name, socklen_t namelen)
{
    struct sal_socket *sock;

    sock = sal_get_socket(socket);
    if (!sock)
    {
        return -1;
    }

    if (sock->ops->bind == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    return sock->ops->bind((int) sock->user_data, name, namelen);
}

int sal_shutdown(int socket, int how)
{
    struct sal_socket *sock;

    sock = sal_get_socket(socket);
    if (!sock)
    {
        return -1;
    }

    if (sock->ops->shutdown == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    if (sock->ops->shutdown((int) sock->user_data, how) == 0)
    {
#ifdef SAL_USING_TLS
        if (SAL_SOCKOPS_PROTO_TLS_VALID(sock, closesocket))
        {
            if (proto_tls->ops->closesocket(sock->user_data_tls) < 0)
            {
                return -1;
            }
        }
#endif
        rt_free(sock);
        socket_table.sockets[socket] = RT_NULL;
        return 0;
    }

    return -1;
}

int sal_getpeername(int socket, struct sockaddr *name, socklen_t *namelen)
{
    struct sal_socket *sock;

    sock = sal_get_socket(socket);
    if (!sock)
    {
        return -1;
    }

    if (sock->ops->getpeername == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    return sock->ops->getpeername((int) sock->user_data, name, namelen);
}

int sal_getsockname(int socket, struct sockaddr *name, socklen_t *namelen)
{
    struct sal_socket *sock;

    sock = sal_get_socket(socket);
    if (!sock)
    {
        return -1;
    }

    if (sock->ops->getsockname == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    return sock->ops->getsockname((int) sock->user_data, name, namelen);
}

int sal_getsockopt(int socket, int level, int optname, void *optval, socklen_t *optlen)
{
    struct sal_socket *sock;

    sock = sal_get_socket(socket);
    if (!sock)
    {
        return -1;
    }

    if (sock->ops->getsockopt == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    return sock->ops->getsockopt((int) sock->user_data, level, optname, optval, optlen);
}

int sal_setsockopt(int socket, int level, int optname, const void *optval, socklen_t optlen)
{
    struct sal_socket *sock;

    sock = sal_get_socket(socket);
    if (!sock)
    {
        return -1;
    }

    if (sock->ops->setsockopt == RT_NULL)
    {
        return -RT_ENOSYS;
    }

#ifdef SAL_USING_TLS
    if (level == SOL_TLS)
    {
        switch (optname)
        {
        case TLS_CRET_LIST:
            SAL_SOCKOPT_PROTO_TLS_EXEC(sock, set_cret_list, optval, optlen);
            break;

        case TLS_CIPHERSUITE_LIST:
            SAL_SOCKOPT_PROTO_TLS_EXEC(sock, set_ciphersurite, optval, optlen);
            break;

        case TLS_PEER_VERIFY:
            SAL_SOCKOPT_PROTO_TLS_EXEC(sock, set_peer_verify, optval, optlen);
            break;

        case TLS_DTLS_ROLE:
            SAL_SOCKOPT_PROTO_TLS_EXEC(sock, set_dtls_role, optval, optlen);
            break;

        default:
            return -1;
        }

        return 0;
    }
    else
    {
        return sock->ops->setsockopt((int) sock->user_data, level, optname, optval, optlen);
    }
#else
    return sock->ops->setsockopt((int) sock->user_data, level, optname, optval, optlen);
#endif /* SAL_USING_TLS */
}

int sal_connect(int socket, const struct sockaddr *name, socklen_t namelen)
{
    struct sal_socket *sock;
    int ret;

    sock = sal_get_socket(socket);
    if (!sock)
    {
        return -1;
    }

    if (sock->ops->connect == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    ret = sock->ops->connect((int) sock->user_data, name, namelen);
#ifdef SAL_USING_TLS
    if (ret >= 0 && SAL_SOCKOPS_PROTO_TLS_VALID(sock, connect))
    {
        if (proto_tls->ops->connect(sock->user_data_tls) < 0)
        {
            return -1;
        }
        
        return ret;
    }
#endif

    return ret;
}

int sal_listen(int socket, int backlog)
{
    struct sal_socket *sock;

    sock = sal_get_socket(socket);
    if (!sock)
    {
        return -1;
    }

    if (sock->ops->listen == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    return sock->ops->listen((int) sock->user_data, backlog);
}

int sal_recvfrom(int socket, void *mem, size_t len, int flags,
             struct sockaddr *from, socklen_t *fromlen)
{
    struct sal_socket *sock;

    sock = sal_get_socket(socket);
    if (!sock)
    {
        return -1;
    }

    if (sock->ops->recvfrom == RT_NULL)
    {
        return -RT_ENOSYS;
    }

#ifdef SAL_USING_TLS
    if (SAL_SOCKOPS_PROTO_TLS_VALID(sock, recv))
    {
        int ret;
        
        if ((ret = proto_tls->ops->recv(sock->user_data_tls, mem, len)) < 0)
        {
            return -1;
        }   
        return ret;
    }
    else
    {
        return sock->ops->recvfrom((int) sock->user_data, mem, len, flags, from, fromlen);
    }
#else
    return sock->ops->recvfrom((int) sock->user_data, mem, len, flags, from, fromlen);
#endif
}

int sal_sendto(int socket, const void *dataptr, size_t size, int flags,
           const struct sockaddr *to, socklen_t tolen)
{
    struct sal_socket *sock;

    sock = sal_get_socket(socket);
    if (!sock)
    {
        return -1;
    }

    if (sock->ops->sendto == RT_NULL)
    {
        return -RT_ENOSYS;
    }

#ifdef SAL_USING_TLS
    if (SAL_SOCKOPS_PROTO_TLS_VALID(sock, send))
    {
        int ret;
        
        if ((ret = proto_tls->ops->send(sock->user_data_tls, dataptr, size)) < 0)
        {
            return -1;
        }      
        return ret;
    }
    else
    {
        return sock->ops->sendto((int) sock->user_data, dataptr, size, flags, to, tolen);
    }
#else
    return sock->ops->sendto((int) sock->user_data, dataptr, size, flags, to, tolen);
#endif
}

int sal_socket(int domain, int type, int protocol)
{
    int retval;
    int socket, proto_socket;
    struct sal_socket *sock;

    /* allocate a new socket and registered socket options */
    socket = socket_new();
    if (socket < 0)
    {
        return -1;
    }
    sock = sal_get_socket(socket);

    retval = socket_init(domain, type, protocol, &sock);
    if (retval < 0)
    {
        LOG_E("SAL socket protocol family input failed, return error %d.", retval);
        return -1;
    }

    if (sock->ops->socket == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    proto_socket = sock->ops->socket(domain, type, protocol);
    if (proto_socket >= 0)
    {
#ifdef SAL_USING_TLS
        if (SAL_SOCKOPS_PROTO_TLS_VALID(sock, socket))
        {
            sock->user_data_tls = proto_tls->ops->socket(proto_socket);
            if (sock->user_data_tls == RT_NULL)
            {
                return -1;
            }
        }
#endif
        sock->user_data = (void *) proto_socket;
        return sock->socket;
    }

    return -1;
}

int sal_closesocket(int socket)
{
    struct sal_socket *sock;

    sock = sal_get_socket(socket);
    if (!sock)
    {
        return -1;
    }

    if (sock->ops->closesocket == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    if (sock->ops->closesocket((int) sock->user_data) == 0)
    {
#ifdef SAL_USING_TLS
        if (SAL_SOCKOPS_PROTO_TLS_VALID(sock, closesocket))
        {
            if (proto_tls->ops->closesocket(sock->user_data_tls) < 0)
            {
                return -1;
            }
        }
#endif
        rt_free(sock);        
        socket_table.sockets[socket] = RT_NULL;
        return 0;
    }

    return -1;
}

int sal_ioctlsocket(int socket, long cmd, void *arg)
{
    struct sal_socket *sock;

    sock = sal_get_socket(socket);
    if (!sock)
    {
        return -1;
    }

    if (sock->ops->ioctlsocket == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    return sock->ops->ioctlsocket((int) sock->user_data, cmd, arg);
}

#ifdef SAL_USING_POSIX
int sal_poll(struct dfs_fd *file, struct rt_pollreq *req)
{
    struct sal_socket *sock;
    int socket = (int) file->data;

    sock = sal_get_socket(socket);
    if (!sock)
    {
        return -1;
    }

    if (sock->ops->poll == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    return sock->ops->poll(file, req);
}
#endif

struct hostent *sal_gethostbyname(const char *name)
{
    int i;
    struct hostent *hst;

    for (i = 0; i < SAL_PROTO_FAMILIES_NUM; ++i)
    {
        if (proto_families[i].ops && proto_families[i].ops->gethostbyname)
        {
            hst = proto_families[i].ops->gethostbyname(name);
            if (hst != RT_NULL)
            {
                return hst;
            }
        }
    }

    return RT_NULL;
}

int sal_gethostbyname_r(const char *name, struct hostent *ret, char *buf,
                size_t buflen, struct hostent **result, int *h_errnop)
{
    int i, res;

    for (i = 0; i < SAL_PROTO_FAMILIES_NUM; ++i)
    {
        if (proto_families[i].ops && proto_families[i].ops->gethostbyname_r)
        {
            res = proto_families[i].ops->gethostbyname_r(name, ret, buf, buflen, result, h_errnop);
            if (res == 0)
            {
                return res;
            }
        }
    }

    return -1;
}

int sal_getaddrinfo(const char *nodename,
       const char *servname,
       const struct addrinfo *hints,
       struct addrinfo **res)
{
    int i, ret;

    for (i = 0; i < SAL_PROTO_FAMILIES_NUM; ++i)
    {
        if (proto_families[i].ops && proto_families[i].ops->getaddrinfo)
        {
            ret = proto_families[i].ops->getaddrinfo(nodename, servname, hints, res);
            if (ret == 0)
            {
                return ret;
            }
        }
    }

    return -1;
}

void sal_freeaddrinfo(struct addrinfo *ai)
{
    int i;

    for (i = 0; i < SAL_PROTO_FAMILIES_NUM; ++i)
    {
        if (proto_families[i].ops && proto_families[i].ops->freeaddrinfo)
        {
            proto_families[i].ops->freeaddrinfo(ai);
            return;
        }
    }
}
