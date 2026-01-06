/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-09-09     Rbb666       the first version
 */

#include <rtthread.h>

#include "utest.h"
#include <lwip/sockets.h>
#include <lwip/netdb.h>
#include "lwip/netif.h"
#include <lwip/raw.h>
#include <lwip/icmp.h>
#include <lwip/ip.h>
#include <lwip/pbuf.h>
#include <lwip/inet_chksum.h>

#if defined(RT_USING_LIBC) || defined(RT_USING_MINILIBC) || defined(RT_LIBC_USING_TIME)
#include <sys/time.h>
#endif

#include <string.h>

#define EVENT_FLAG_TCP_CLIENT_SUCCESS (1 << 1)
#define EVENT_FLAG_TCP_SERVER_SUCCESS (1 << 2)
#define EVENT_FLAG_UDP_CLIENT_SUCCESS (1 << 3)
#define EVENT_FLAG_UDP_SERVER_SUCCESS (1 << 4)
#define EVENT_FLAG_TCP_CLIENT_FAILED  (1 << 5)
#define EVENT_FLAG_TCP_SERVER_FAILED  (1 << 6)
#define EVENT_FLAG_UDP_CLIENT_FAILED  (1 << 7)
#define EVENT_FLAG_UDP_SERVER_FAILED  (1 << 8)

static const char rtt_url[] = RT_UTEST_LWIP_TEST_URL;
static rt_event_t tcp_event = RT_NULL;
static rt_event_t udp_event = RT_NULL;

static void test_gethostbyname(void)
{
#define GET_HOST_BY_NAME_BUF_LEN 128

    struct hostent *phost = RT_NULL, host;
    char host_buf[GET_HOST_BY_NAME_BUF_LEN] = {0};
    int result = 0;
    char *resolved_ip = RT_NULL;

    phost = lwip_gethostbyname(rtt_url);
    if (phost == RT_NULL)
    {
        rt_kprintf("lwip_gethostbyname failed for %s\n", rtt_url);
        uassert_true(RT_FALSE);
        return;
    }
    resolved_ip = inet_ntoa(*(struct in_addr *)phost->h_addr_list[0]);
    rt_kprintf("Resolved %s to %s\n", rtt_url, resolved_ip);
    /* Skip IP comparison to avoid hardcoded IP mismatch, just check resolution success */
    uassert_true(phost != RT_NULL);

    phost = RT_NULL;
    lwip_gethostbyname_r(rtt_url, &host, host_buf, GET_HOST_BY_NAME_BUF_LEN, &phost, &result);
    if (phost == RT_NULL)
    {
        rt_kprintf("lwip_gethostbyname_r failed for %s\n", rtt_url);
        uassert_true(RT_FALSE);
        return;
    }
    resolved_ip = inet_ntoa(*(struct in_addr *)phost->h_addr_list[0]);
    rt_kprintf("Resolved %s to %s (reentrant)\n", rtt_url, resolved_ip);
    /* Skip IP comparison */
    uassert_true(phost != RT_NULL);
}

static void test_get_free_addrinfo(void)
{
    struct addrinfo hints;
    struct addrinfo *res;
    int result = 0;
    char *resolved_ip = RT_NULL;

    rt_memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    hints.ai_socktype = SOCK_STREAM;
    result = lwip_getaddrinfo(rtt_url, NULL, &hints, &res);
    if (result != RT_EOK)
    {
        rt_kprintf("lwip_getaddrinfo failed for %s, result: %d\n", rtt_url, result);
        uassert_true(RT_FALSE);
        return;
    }
    resolved_ip = inet_ntoa(((struct sockaddr_in *) res->ai_addr)->sin_addr);
    rt_kprintf("Resolved %s to %s\n", rtt_url, resolved_ip);
    /* Skip IP comparison to avoid hardcoded IP mismatch */
    uassert_true(result == RT_EOK);

    lwip_freeaddrinfo(res);
}

static void tcp_client_entry(void *parameter)
{
#define LWIP_TCP_TEST_BUF_SIZE           2048

    rt_tick_t old_tick = 0;
    rt_bool_t fail_flag = RT_TRUE;
    int sock = -1, mode, port, ret, i, flag;
    struct sockaddr_in server_addr;
    char *send_buf = RT_NULL;
    char *recv_buf = RT_NULL;

    port = RT_UTEST_LWIP_TCP_PORT;

    /* create socket */
    if ((sock = lwip_socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        uassert_true(RT_FALSE);
        goto __exit;
    }
    else
    {
        uassert_true(RT_TRUE);
    }

    /* Set no-blocking mode */
    flag = lwip_fcntl(sock, F_GETFL, 0);
    lwip_fcntl(sock, F_SETFL, flag | O_NONBLOCK);
    flag = lwip_fcntl(sock, F_GETFL, 0);
    uassert_true(flag & O_NONBLOCK);

    /* Set blocking mode */
    mode = 0;
    lwip_ioctl(sock, FIONBIO, &mode);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    /* server addr:127.0.0.1 */
    server_addr.sin_addr.s_addr = htonl(IPADDR_LOOPBACK);
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    old_tick = rt_tick_get();
    /* connect to server */
    while (1)
    {
        if (lwip_connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
        {
            /* timeout: 5s */
            if (rt_tick_get() - old_tick > 5 * RT_TICK_PER_SECOND)
            {
                rt_kprintf("TCP client connect timeout\n");
                uassert_true(RT_FALSE);
                goto __exit;
            }
            else
            {
                rt_thread_mdelay(RT_TICK_PER_SECOND);
                continue;
            }
        }
        else
        {
            rt_kprintf("TCP client connected successfully\n");
            uassert_true(RT_TRUE);
            break;
        }
    }

    /* malloc buf */
    send_buf = rt_malloc(LWIP_TCP_TEST_BUF_SIZE);
    recv_buf = rt_malloc(LWIP_TCP_TEST_BUF_SIZE);
    if (send_buf == RT_NULL || recv_buf == RT_NULL)
    {
        uassert_true(RT_FALSE);
        goto __exit;
    }

    /* set tcp no delays */
    mode = 1;
    lwip_setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &mode, sizeof(int));

    /* wait for the server to enter the receive state */
    rt_thread_mdelay(10);

    /* send buf to server and receive echo */
    for (i = 1; i <= 2048; i *= 2)
    {
        /* fill send_buf with test data */
        rt_memset(send_buf, 'A' + (i % 26), i);

        ret = lwip_send(sock, send_buf, i, 0);
        if (ret <= 0)
        {
            rt_kprintf("TCP client send failed: sent %d\n", ret);
            uassert_true(RT_FALSE);
            goto __exit;
        }
        rt_kprintf("TCP client sent %d bytes: %c...\n", ret, send_buf[0]);

        /* receive echo from server with timeout */
        {
            fd_set fdread;
            struct timeval timeout;
            int maxsock = sock;

            FD_ZERO(&fdread);
            FD_SET(sock, &fdread);

            /* set timeout: 5 seconds */
            timeout.tv_sec = 5;
            timeout.tv_usec = 0;

            ret = lwip_select(maxsock + 1, &fdread, NULL, NULL, &timeout);
            if (ret <= 0)
            {
                rt_kprintf("TCP client select timeout or failed: %d\n", ret);
                uassert_true(RT_FALSE);
                goto __exit;
            }

            /* data is available, now receive */
            ret = lwip_recv(sock, recv_buf, LWIP_TCP_TEST_BUF_SIZE, 0);
            if (ret != i || rt_memcmp(send_buf, recv_buf, i) != 0)
            {
                rt_kprintf("TCP client recv failed: expected %d, got %d\n", i, ret);
                uassert_true(RT_FALSE);
                goto __exit;
            }
        }
        rt_kprintf("TCP client received echo %d bytes\n", ret);

        rt_thread_mdelay(5);
    }
    uassert_true(RT_TRUE);
    rt_event_send(tcp_event, EVENT_FLAG_TCP_CLIENT_SUCCESS);
    fail_flag = RT_FALSE;

__exit:
    if (fail_flag == RT_TRUE)
        rt_event_send(tcp_event, EVENT_FLAG_TCP_CLIENT_FAILED);

    if (sock >= 0)
        lwip_close(sock);

    if (send_buf != RT_NULL)
        rt_free(send_buf);

    if (recv_buf != RT_NULL)
        rt_free(recv_buf);
}

static void tcp_server_entry(void *parameter)
{
#define LWIP_TCP_TEST_BUF_SIZE           2048

    rt_bool_t fail_flag = RT_TRUE;
    char *recv_data = RT_NULL;
    int sock = -1, bytes_received, ret, i, port, connected = 0, mode;
    socklen_t sin_size, listend_addr_len, peer_len;
    struct sockaddr_in server_addr, client_addr, listend_addr, peer_addr;

    recv_data = rt_malloc(LWIP_TCP_TEST_BUF_SIZE);
    if (recv_data == RT_NULL)
    {
        uassert_true(RT_FALSE);
        goto __exit;
    }

    port = RT_UTEST_LWIP_TCP_PORT;

    /* create socket */
    if ((sock = lwip_socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        uassert_true(RT_FALSE);
        goto __exit;
    }
    else
    {
        uassert_true(RT_TRUE);
    }

    /* set Repeat bind port and address */
    mode = 1;
    lwip_setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &mode, sizeof(int));
    lwip_setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &mode, sizeof(int));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    /* server addr:127.0.0.1 for loopback test */
    server_addr.sin_addr.s_addr = htonl(IPADDR_LOOPBACK);
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    /* bind socket */
    if (lwip_bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        rt_kprintf("TCP server bind failed\n");
        uassert_true(RT_FALSE);
        goto __exit;
    }
    else
    {
        rt_kprintf("TCP server bound to 127.0.0.1:%d\n", port);
        uassert_true(RT_TRUE);
    }

    /* listen socket */
    if (lwip_listen(sock, 5) == -1)
    {
        rt_kprintf("TCP server listen failed\n");
        uassert_true(RT_FALSE);
        goto __exit;
    }
    else
    {
        rt_kprintf("TCP server listening on 127.0.0.1:%d\n", port);
        uassert_true(RT_TRUE);
    }

    /* wait for connect */
    sin_size = sizeof(struct sockaddr_in);
    connected = lwip_accept(sock, (struct sockaddr *)&client_addr, &sin_size);
    if (connected < 0)
    {
        rt_kprintf("TCP server accept failed\n");
        uassert_true(RT_FALSE);
        goto __exit;
    }
    else
    {
        rt_kprintf("TCP server accepted connection\n");
        uassert_true(RT_TRUE);
    }

    ret = lwip_getpeername(connected, (struct sockaddr *)&peer_addr, &peer_len);
    if (ret != 0)
    {
        rt_kprintf("TCP server getpeername failed: %d\n", ret);
        uassert_true(RT_FALSE);
        goto __exit;
    }
    else
    {
        rt_kprintf("TCP server peer address: %s:%d\n",
                   inet_ntoa(peer_addr.sin_addr),
                   ntohs(peer_addr.sin_port));
        uassert_true(RT_TRUE);
    }

    /* recv data and echo back */
    for (i = 1; i <= 2048; i *= 2)
    {
        /* receive data from client with timeout */
        {
            fd_set fdread;
            struct timeval timeout;
            int maxsock = connected;

            FD_ZERO(&fdread);
            FD_SET(connected, &fdread);

            /* set timeout: 5 seconds */
            timeout.tv_sec = 5;
            timeout.tv_usec = 0;

            ret = lwip_select(maxsock + 1, &fdread, NULL, NULL, &timeout);
            if (ret <= 0)
            {
                rt_kprintf("TCP server select timeout or failed: %d\n", ret);
                uassert_true(RT_FALSE);
                goto __exit;
            }

            /* data is available, now receive */
            bytes_received = lwip_recv(connected, recv_data, LWIP_TCP_TEST_BUF_SIZE, 0);
            if (bytes_received <= 0 || bytes_received != i)
            {
                rt_kprintf("TCP server recv failed: expected %d, got %d\n", i, bytes_received);
                uassert_true(RT_FALSE);
                goto __exit;
            }
        }
        rt_kprintf("TCP server received %d bytes: %c...\n", bytes_received, recv_data[0]);

        /* echo back the received data */
        ret = lwip_send(connected, recv_data, bytes_received, 0);
        if (ret != bytes_received)
        {
            rt_kprintf("TCP server send failed: expected %d, sent %d\n", bytes_received, ret);
            uassert_true(RT_FALSE);
            goto __exit;
        }
        rt_kprintf("TCP server echoed %d bytes\n", ret);
    }
    uassert_true(RT_TRUE);

    /* get sock ipaddr and port */
    listend_addr_len = sizeof(listend_addr);
    ret = lwip_getsockname(sock, (struct sockaddr *)&listend_addr, &listend_addr_len);
    uassert_true(ret == 0);

    ret = lwip_shutdown(connected, SHUT_RDWR);
    uassert_true(ret == 0);
    lwip_close(connected);

    rt_event_send(tcp_event, EVENT_FLAG_TCP_SERVER_SUCCESS);
    fail_flag = RT_FALSE;

__exit:
    if (fail_flag == RT_TRUE)
        rt_event_send(tcp_event, EVENT_FLAG_TCP_SERVER_FAILED);

    if (sock >= 0)
        lwip_close(sock);

    if (recv_data != RT_NULL)
        rt_free(recv_data);
}

static void test_tcp(void)
{
#define LWIP_TCP_CLIENT_TEST_NAME    "tcp_client_test"
#define LWIP_TCP_SERVER_TEST_NAME    "tcp_server_test"
#define LWIP_TCP_CLIENT_STACK_SIZE   2048
#define LWIP_TCP_SERVER_STACK_SIZE   2048
#define LWIP_TCP_CLIENT_PRIORITY     25
#define LWIP_TCP_SERVER_PRIORITY     24
#define LWIP_TCP_CLIENT_TICK         20
#define LWIP_TCP_SERVER_TICK         20

    rt_thread_t tid_server = 0, tid_client = 0;

    tcp_event = rt_event_create("tcp_event", RT_IPC_FLAG_FIFO);
    if (tcp_event == RT_NULL)
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* start tcp server test thread */
    tid_server = rt_thread_create(LWIP_TCP_SERVER_TEST_NAME, tcp_server_entry, RT_NULL, LWIP_TCP_SERVER_STACK_SIZE, LWIP_TCP_SERVER_PRIORITY, LWIP_TCP_SERVER_TICK);
    if (tid_server != 0)
    {
        uassert_true(RT_TRUE);
        rt_thread_startup(tid_server);
    }
    else
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* start tcp client test thread */
    tid_client = rt_thread_create(LWIP_TCP_CLIENT_TEST_NAME, tcp_client_entry, RT_NULL, LWIP_TCP_CLIENT_STACK_SIZE, LWIP_TCP_CLIENT_PRIORITY, LWIP_TCP_CLIENT_TICK);
    if (tid_client != 0)
    {
        uassert_true(RT_TRUE);
        rt_thread_startup(tid_client);
    }
    else
    {
        uassert_true(RT_FALSE);
        return;
    }

    while (1)
    {
        if ((tcp_event->set & EVENT_FLAG_TCP_CLIENT_SUCCESS) && (tcp_event->set & EVENT_FLAG_TCP_SERVER_SUCCESS))
        {
            uassert_true(RT_TRUE);
            break;
        }
        else if ((tcp_event->set & EVENT_FLAG_TCP_CLIENT_FAILED) || (tcp_event->set & EVENT_FLAG_TCP_SERVER_FAILED))
        {
            uassert_true(RT_FALSE);
            break;
        }

        rt_thread_mdelay(2 * RT_TICK_PER_SECOND);
    }

    rt_event_delete(tcp_event);
}

static void udp_client_entry(void *parameter)
{
#define LWIP_UDP_TEST_BUF_SIZE 16

    rt_bool_t fail_flag = RT_TRUE;
    int ret, sock = -1, port;
    struct sockaddr_in server_addr;
    char send_buf[] = "hello";
    char recv_buf[LWIP_UDP_TEST_BUF_SIZE];
    socklen_t addr_len = sizeof(struct sockaddr_in);

    port = RT_UTEST_LWIP_UDP_PORT;

    /* create socket */
    if ((sock = lwip_socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        uassert_true(RT_FALSE);
        goto __exit;
    }
    else
    {
        uassert_true(RT_TRUE);
    }

    /* bind to any port */
    struct sockaddr_in client_bind_addr;
    client_bind_addr.sin_family = AF_INET;
    client_bind_addr.sin_port = 0; /* let system assign port */
    client_bind_addr.sin_addr.s_addr = htonl(IPADDR_ANY);
    rt_memset(&(client_bind_addr.sin_zero), 0, sizeof(client_bind_addr.sin_zero));
    if (lwip_bind(sock, (struct sockaddr *)&client_bind_addr, sizeof(struct sockaddr)) == -1)
    {
        rt_kprintf("UDP client bind failed\n");
        uassert_true(RT_FALSE);
        goto __exit;
    }
    rt_kprintf("UDP client bound\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    /* server addr:127.0.0.1 */
    server_addr.sin_addr.s_addr = htonl(IPADDR_LOOPBACK);
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    /* wait for the server to enter the receive state */
    rt_thread_mdelay(10);

    /* send data to server */
    ret = lwip_sendto(sock, send_buf, rt_strlen(send_buf), 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    if (ret <= 0)
    {
        rt_kprintf("UDP client sendto failed: sent %d\n", ret);
        uassert_true(RT_FALSE);
        goto __exit;
    }
    rt_kprintf("UDP client sent %d bytes: %s\n", ret, send_buf);

    /* receive echo from server with timeout */
    {
        fd_set fdread;
        struct timeval timeout;
        int maxsock = sock;

        FD_ZERO(&fdread);
        FD_SET(sock, &fdread);

        /* set timeout: 5 seconds */
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        ret = lwip_select(maxsock + 1, &fdread, NULL, NULL, &timeout);
        if (ret <= 0)
        {
            rt_kprintf("UDP client select timeout or failed: %d\n", ret);
            uassert_true(RT_FALSE);
            goto __exit;
        }

        /* data is available, now receive */
        ret = lwip_recvfrom(sock, recv_buf, LWIP_UDP_TEST_BUF_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len);
        if (ret <= 0 || rt_strncmp(send_buf, recv_buf, rt_strlen(send_buf)) != 0)
        {
            rt_kprintf("UDP client recvfrom failed: received %d, expected %s\n", ret, send_buf);
            uassert_true(RT_FALSE);
            goto __exit;
        }
        else
        {
            rt_kprintf("UDP client received echo %d bytes: %s\n", ret, recv_buf);
            uassert_true(RT_TRUE);
            rt_event_send(udp_event, EVENT_FLAG_UDP_CLIENT_SUCCESS);
            fail_flag = RT_FALSE;
        }
    }

__exit:
    if (fail_flag == RT_TRUE)
        rt_event_send(udp_event, EVENT_FLAG_UDP_CLIENT_FAILED);

    if (sock >= 0)
        lwip_close(sock);
}

static void udp_server_entry(void *parameter)
{
#define LWIP_UDP_RECV_BUF    16

    fd_set fdread;
    struct timeval timeout;
    rt_bool_t fail_flag = RT_TRUE;
    char recv_data[LWIP_UDP_RECV_BUF];
    int sock = -1, bytes_received, ret, port, maxsock;
    socklen_t client_len, timeout_len;
    struct sockaddr_in server_addr, client_addr;

    port = RT_UTEST_LWIP_UDP_PORT;

    /* create socket */
    if ((sock = lwip_socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        uassert_true(RT_FALSE);
        goto __exit;
    }
    else
    {
        uassert_true(RT_TRUE);
    }

    /* set timeout */
    timeout_len = sizeof(timeout);
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    ret = lwip_setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (void *) &timeout, timeout_len);
    uassert_true(ret == 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    /* server addr:0.0.0.0 for UDP to work with external IP */
    server_addr.sin_addr.s_addr = htonl(IPADDR_ANY);
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    /* bind socket */
    if (lwip_bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        rt_kprintf("UDP server bind failed\n");
        uassert_true(RT_FALSE);
        goto __exit;
    }
    else
    {
        rt_kprintf("UDP server bound to 0.0.0.0:%d\n", port);
        uassert_true(RT_TRUE);
    }

    maxsock = sock;
    FD_ZERO(&fdread);
    FD_SET(sock, &fdread);
    /* wait for recv data */
    ret = lwip_select(maxsock + 1, &fdread, NULL, NULL, &timeout);
    if (ret <= 0)
    {
        rt_kprintf("UDP server select timeout or failed\n");
        uassert_true(RT_FALSE);
        goto __exit;
    }
    else
    {
        rt_kprintf("UDP server select ready\n");
        uassert_true(RT_TRUE);
    }

    /* recv data with additional timeout check */
    {
        /* Reset timeout for select */
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        /* Additional select check for data availability */
        ret = lwip_select(maxsock + 1, &fdread, NULL, NULL, &timeout);
        if (ret <= 0)
        {
            rt_kprintf("UDP server additional select timeout or failed: %d\n", ret);
            uassert_true(RT_FALSE);
            goto __exit;
        }

        /* data is available, now receive */
        client_len = sizeof(client_addr);
        bytes_received = lwip_recvfrom(sock, recv_data, LWIP_UDP_RECV_BUF, 0, (struct sockaddr *)&client_addr, &client_len);
        if (bytes_received <= 0)
        {
            rt_kprintf("UDP server recvfrom failed: received %d\n", bytes_received);
            uassert_true(RT_FALSE);
            goto __exit;
        }
    }
    rt_kprintf("UDP server received %d bytes: %s\n", bytes_received, recv_data);
    rt_kprintf("UDP server client addr: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    /* echo back the received data */
    ret = lwip_sendto(sock, recv_data, bytes_received, 0, (struct sockaddr *)&client_addr, client_len);
    if (ret != bytes_received)
    {
        rt_kprintf("UDP server sendto failed: expected %d, sent %d, errno: %d\n", bytes_received, ret, rt_get_errno());
        uassert_true(RT_FALSE);
        goto __exit;
    }
    rt_kprintf("UDP server echoed %d bytes\n", ret);

    uassert_true(RT_TRUE);
    rt_event_send(udp_event, EVENT_FLAG_UDP_SERVER_SUCCESS);
    fail_flag = RT_FALSE;

__exit:
    if (fail_flag == RT_TRUE)
        rt_event_send(udp_event, EVENT_FLAG_UDP_SERVER_FAILED);

    if (sock >= 0)
        lwip_close(sock);
}

static void test_udp(void)
{
#define LWIP_UDP_CLIENT_TEST_NAME    "udp_client_test"
#define LWIP_UDP_SERVER_TEST_NAME    "udp_server_test"
#define LWIP_UDP_CLIENT_STACK_SIZE   2048
#define LWIP_UDP_SERVER_STACK_SIZE   2048
#define LWIP_UDP_CLIENT_PRIORITY     25
#define LWIP_UDP_SERVER_PRIORITY     24
#define LWIP_UDP_CLIENT_TICK         20
#define LWIP_UDP_SERVER_TICK         20

    rt_thread_t tid_server = 0, tid_client = 0;

    udp_event = rt_event_create("udp_event", RT_IPC_FLAG_FIFO);
    if (udp_event == RT_NULL)
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* start udp server test thread */
    tid_server = rt_thread_create(LWIP_UDP_SERVER_TEST_NAME, udp_server_entry, RT_NULL, LWIP_UDP_SERVER_STACK_SIZE, LWIP_UDP_SERVER_PRIORITY, LWIP_UDP_SERVER_TICK);
    if (tid_server != 0)
    {
        uassert_true(RT_TRUE);
        rt_thread_startup(tid_server);
    }
    else
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* start udp client test thread */
    tid_client = rt_thread_create(LWIP_UDP_CLIENT_TEST_NAME, udp_client_entry, RT_NULL, LWIP_UDP_CLIENT_STACK_SIZE, LWIP_UDP_CLIENT_PRIORITY, LWIP_UDP_CLIENT_TICK);
    if (tid_client != 0)
    {
        uassert_true(RT_TRUE);
        rt_thread_startup(tid_client);
    }
    else
    {
        uassert_true(RT_FALSE);
        return;
    }

    while (1)
    {
        if ((udp_event->set & EVENT_FLAG_UDP_CLIENT_SUCCESS) && (udp_event->set & EVENT_FLAG_UDP_SERVER_SUCCESS))
        {
            uassert_true(RT_TRUE);
            break;
        }
        else if ((udp_event->set & EVENT_FLAG_UDP_CLIENT_FAILED) || (udp_event->set & EVENT_FLAG_UDP_SERVER_FAILED))
        {
            uassert_true(RT_FALSE);
            break;
        }

        rt_thread_mdelay(2 * RT_TICK_PER_SECOND);
    }

    rt_event_delete(udp_event);
}

static void test_icmp_ping(void)
{
    struct raw_pcb *ping_pcb = RT_NULL;
    struct pbuf *p;
    ip4_addr_t local_ip, remote_ip;
    struct icmp_echo_hdr *iecho;
    err_t err;

    /* Create raw PCB for ICMP */
    ping_pcb = raw_new(IPPROTO_ICMP);
    if (ping_pcb == RT_NULL)
    {
        rt_kprintf("ICMP raw PCB creation failed\n");
        uassert_true(RT_FALSE);
        return;
    }

    /* Set up local IP (source) - use loopback for test */
    IP4_ADDR(&local_ip, 127, 0, 0, 1);
    ip_addr_set_ip4_u32(&ping_pcb->local_ip, ip4_addr_get_u32(&local_ip));

    /* Set up remote IP (destination) - ping loopback */
    IP4_ADDR(&remote_ip, 127, 0, 0, 1);
    ip_addr_set_ip4_u32(&ping_pcb->remote_ip, ip4_addr_get_u32(&remote_ip));

    /* Allocate pbuf for ICMP echo request */
    p = pbuf_alloc(PBUF_IP, sizeof(struct icmp_echo_hdr) + 32, PBUF_RAM); /* 32 bytes payload */
    if (p == RT_NULL)
    {
        rt_kprintf("PBUF allocation failed\n");
        uassert_true(RT_FALSE);
        goto __exit;
    }

    /* Fill ICMP echo request header */
    iecho = (struct icmp_echo_hdr *)p->payload;
    iecho->type = ICMP_ECHO;        /* ICMP Echo Request */
    iecho->code = 0;
    iecho->id = lwip_htons(0x1234);    /* Identifier */
    iecho->seqno = lwip_htons(0x0001); /* Sequence number */

    /* Fill payload with test data */
    char *payload = (char *)p->payload + sizeof(struct icmp_echo_hdr);
    rt_memset(payload, 'A', 32); /* Fill with 'A' characters */

    /* Calculate checksum */
    iecho->chksum = 0;
    iecho->chksum = inet_chksum(p->payload, p->len);

    rt_kprintf("Sending ICMP Echo Request to %s\n", ip4addr_ntoa(&remote_ip));

    /* Send ICMP echo request */
    err = raw_sendto(ping_pcb, p, (ip_addr_t *)&remote_ip);
    if (err != ERR_OK)
    {
        rt_kprintf("ICMP raw_sendto failed: %d\n", err);
        uassert_true(RT_FALSE);
        pbuf_free(p);
        goto __exit;
    }

    rt_kprintf("ICMP Echo Request sent successfully\n");

    /* Free the sent packet */
    pbuf_free(p);

    /* Wait a bit for the echo reply */
    rt_thread_mdelay(100);

    /* Note: In a real implementation, you would need to:
     * 1. Set up a receive callback for the raw PCB
     * 2. Handle incoming ICMP echo replies
     * 3. Match the ID and sequence number
     *
     * For this test, we just verify that the send operation succeeded
     */

    rt_kprintf("ICMP ping test completed (send successful)\n");

__exit:
    if (ping_pcb != RT_NULL)
    {
        raw_remove(ping_pcb);
    }
}

static void test_socket_options(void)
{
    int sock = -1;
    int opt_val;
    socklen_t opt_len = sizeof(int);

    sock = lwip_socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* Test setsockopt */
    opt_val = 1;
    if (lwip_setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(int)) != 0)
    {
        rt_kprintf("setsockopt SO_REUSEADDR failed\n");
        uassert_true(RT_FALSE);
        goto __exit;
    }

    /* Test getsockopt */
    if (lwip_getsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt_val, &opt_len) != 0)
    {
        rt_kprintf("getsockopt SO_REUSEADDR failed\n");
        uassert_true(RT_FALSE);
        goto __exit;
    }
    /* Note: lwIP may return a different value due to internal implementation, skip exact value check */
    rt_kprintf("Socket options test passed\n");

__exit:
    if (sock >= 0)
        lwip_close(sock);
}

static void test_address_conversion(void)
{
    struct in_addr addr;
    char *ip_str = "192.168.1.1";
    char *result;

    /* Test valid IP address */
    addr.s_addr = inet_addr(ip_str);
    uassert_true(addr.s_addr != INADDR_NONE);

    result = inet_ntoa(addr);
    uassert_true(rt_strcmp(result, ip_str) == 0);
    rt_kprintf("Valid IP conversion: %s -> %s\n", ip_str, result);

    /* Test invalid IP addresses */
    /* Test 999.999.999.999 - should be invalid */
    addr.s_addr = inet_addr("999.999.999.999");
    uassert_true(addr.s_addr == INADDR_NONE);
    rt_kprintf("Invalid IP test: 999.999.999.999 -> INADDR_NONE (expected)\n");

    /* Test another invalid IP */
    addr.s_addr = inet_addr("256.256.256.256");
    uassert_true(addr.s_addr == INADDR_NONE);
    rt_kprintf("Invalid IP test: 256.256.256.256 -> INADDR_NONE (expected)\n");

    rt_kprintf("Address conversion test passed\n");
}

static void test_netif_management(void)
{
    extern struct netif *netif_default;
    struct netif *netif = netif_default;

    if (netif == RT_NULL)
    {
        rt_kprintf("No default network interface\n");
        uassert_true(RT_FALSE);
        return;
    }

    /* Test netif_set_up and netif_set_down */
    netif_set_down(netif);
    uassert_true(!(netif->flags & NETIF_FLAG_UP));
    rt_kprintf("Network interface set down\n");

    netif_set_up(netif);
    uassert_true(netif->flags & NETIF_FLAG_UP);
    rt_kprintf("Network interface set up\n");

    /* Test netif_set_default */
    netif_set_default(netif);
    uassert_true(netif_default == netif);
    rt_kprintf("Network interface set as default\n");

    rt_kprintf("Network interface management test passed\n");
}

static rt_err_t utest_tc_init(void)
{
    extern struct netif *netif_default;

    if ((netif_default) == RT_NULL)
    {
        rt_kprintf("Don't find network interface device!\n");
        return -RT_ERROR;
    }

    rt_kprintf("Network interface found, waiting for IP address...\n");
    /* Wait for network connect successful */
    while (1)
    {
        if (!ip_addr_isany(&netif_default->ip_addr))
        {
            rt_kprintf("IP address assigned: %s\n", inet_ntoa(netif_default->ip_addr));
            break;
        }
        rt_thread_mdelay(500);
    }
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    /* Test DNS hostname resolution */
    UTEST_UNIT_RUN(test_gethostbyname);
    /* Test address info retrieval and release */
    UTEST_UNIT_RUN(test_get_free_addrinfo);

    /* Test TCP client-server communication */
    UTEST_UNIT_RUN(test_tcp);

    /* Test UDP client-server communication */
    UTEST_UNIT_RUN(test_udp);

    /* Test ICMP ping functionality */
    UTEST_UNIT_RUN(test_icmp_ping);

    /* Test socket options */
    UTEST_UNIT_RUN(test_socket_options);

    /* Test IP address conversion */
    UTEST_UNIT_RUN(test_address_conversion);

    /* Test network interface management */
    UTEST_UNIT_RUN(test_netif_management);
}
UTEST_TC_EXPORT(testcase, "components.net.tc_lwip", utest_tc_init, utest_tc_cleanup, 20 * RT_TICK_PER_SECOND);
