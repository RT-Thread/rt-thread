/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-12     ChenYong     First version
 */

#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_posix.h>
#endif

#ifdef SAL_USING_TLS
#include <sal_tls.h>
#endif
#include <netdb.h>
#include <sal.h>

#include <netdev.h>

#ifdef SAL_USING_TLS

#if !defined(MBEDTLS_CONFIG_FILE)
#include <mbedtls/config.h>
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <tls_certificate.h>
#include <tls_client.h>

#ifndef SAL_MEBDTLS_BUFFER_LEN
#define SAL_MEBDTLS_BUFFER_LEN         1024
#endif

static void *mebdtls_socket(int socket)
{
    MbedTLSSession *session = RT_NULL;
    char *pers = "mbedtls";

    if (socket < 0)
    {
        return RT_NULL;
    }

    session = (MbedTLSSession *) tls_calloc(1, sizeof(MbedTLSSession));
    if (session == RT_NULL)
    {
        return RT_NULL;
    }

    session->buffer_len = SAL_MEBDTLS_BUFFER_LEN;
    session->buffer = tls_calloc(1, session->buffer_len);
    if (session->buffer == RT_NULL)
    {
        tls_free(session);
        session = RT_NULL;
        
        return RT_NULL;
    }

    /* initialize TLS Client sesison */
    if (mbedtls_client_init(session, (void *) pers, rt_strlen(pers)) != RT_EOK)
    {
        mbedtls_client_close(session);
        return RT_NULL;
    }  
    session->server_fd.fd = socket;

    return (void *)session;
}

int mbedtls_net_send_cb(void *ctx, const unsigned char *buf, size_t len)
{
    struct sal_socket *sock;
    int socket, ret;
    struct sal_proto_family *pf;

    RT_ASSERT(ctx);
    RT_ASSERT(buf);

    socket = ((mbedtls_net_context *) ctx)->fd;
    sock = sal_get_socket(socket);
    if (sock == RT_NULL)
    {
        return -1;
    }
    
    pf = (struct sal_proto_family *)sock->netdev->sal_user_data;

    /* Register scoket sendto option to TLS send data callback */
    ret = pf->skt_ops->sendto((int) sock->user_data, (void *)buf, len, 0, RT_NULL, RT_NULL);
    if (ret < 0)
    {
#ifdef RT_USING_DFS
        if ((fcntl(socket, F_GETFL) & O_NONBLOCK) == O_NONBLOCK)
            return MBEDTLS_ERR_SSL_WANT_WRITE;
#endif
        if (errno == ECONNRESET)
            return MBEDTLS_ERR_NET_CONN_RESET;
        if ( errno == EINTR)
            return MBEDTLS_ERR_SSL_WANT_READ;

        return MBEDTLS_ERR_NET_SEND_FAILED ;
    }

    return ret;
}

int mbedtls_net_recv_cb( void *ctx, unsigned char *buf, size_t len)
{
    struct sal_socket *sock;
    struct sal_proto_family *pf;
    int socket, ret;

    RT_ASSERT(ctx);
    RT_ASSERT(buf);

    socket = ((mbedtls_net_context *) ctx)->fd;
    sock = sal_get_socket(socket);
    if (sock == RT_NULL)
    {
        return -1;
    }

    pf = (struct sal_proto_family *)sock->netdev->sal_user_data;
    
    /* Register scoket recvfrom option to TLS recv data callback */
    ret = pf->skt_ops->recvfrom((int) sock->user_data, (void *)buf, len, 0, RT_NULL, RT_NULL);
    if (ret < 0)
    {
#ifdef RT_USING_DFS
        if ((fcntl(socket, F_GETFL) & O_NONBLOCK) == O_NONBLOCK)
            return MBEDTLS_ERR_SSL_WANT_WRITE;
#endif
        if (errno == ECONNRESET)
            return MBEDTLS_ERR_NET_CONN_RESET;
        if ( errno == EINTR)
            return MBEDTLS_ERR_SSL_WANT_READ;

        return MBEDTLS_ERR_NET_RECV_FAILED ;
    }

    return ret;
}

static int mbedtls_connect(void *sock)
{
    MbedTLSSession *session = RT_NULL;
    int ret = 0;

    RT_ASSERT(sock);

    session = (MbedTLSSession *) sock;

    /* Set the SSL Configure infromation */
    ret = mbedtls_client_context(session);
    if (ret < 0)
    {
        goto __exit;
    }

    /* Set the underlying BIO callbacks for write, read and read-with-timeout.  */
    mbedtls_ssl_set_bio(&session->ssl, &session->server_fd, mbedtls_net_send_cb, mbedtls_net_recv_cb, RT_NULL);

    while ((ret = mbedtls_ssl_handshake(&session->ssl)) != 0)
    {
        if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
        {
            goto __exit;
        }
    }

    /* Return the result of the certificate verification */
    ret = mbedtls_ssl_get_verify_result(&session->ssl);
    if (ret != 0)
    {
        rt_memset(session->buffer, 0x00, session->buffer_len);
        mbedtls_x509_crt_verify_info((char *)session->buffer, session->buffer_len, "  ! ", ret);
        goto __exit;
    }
    
    return ret;

__exit:
    if (session)
    {
        mbedtls_client_close(session);
    }

    return ret;
}

static int mbedtls_closesocket(void *sock)
{
    struct sal_socket *ssock;
    int socket;
    
    if (sock == RT_NULL)
    {
        return 0;
    }
    
    socket = ((MbedTLSSession *) sock)->server_fd.fd;
    ssock = sal_get_socket(socket);
    if (ssock == RT_NULL)
    {
        return -1;
    }
    
    /* Close TLS client session, and clean user-data in SAL socket */
    mbedtls_client_close((MbedTLSSession *) sock);
    ssock->user_data_tls = RT_NULL;
    
    return 0;
}

static const struct sal_proto_tls_ops mbedtls_proto_ops= 
{
    RT_NULL,
    mebdtls_socket,
    mbedtls_connect,
    (int (*)(void *sock, const void *data, size_t size)) mbedtls_client_write,
    (int (*)(void *sock, void *mem, size_t len)) mbedtls_client_read,
    mbedtls_closesocket,
};

static const struct sal_proto_tls mbedtls_proto =
{
    "mbedtls",
    &mbedtls_proto_ops,
};

int sal_mbedtls_proto_init(void)
{
    /* register MbedTLS protocol options to SAL */
    sal_proto_tls_register(&mbedtls_proto);

    return 0;
}
INIT_COMPONENT_EXPORT(sal_mbedtls_proto_init);

#endif /* SAL_USING_TLS */
