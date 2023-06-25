/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-01-24     ChungHsuan   improve code comments
 */

#include <rtthread.h>
#include <string.h>

#if !defined(SAL_USING_POSIX)
#error "Please enable SAL_USING_POSIX!"
#else
#include <sys/time.h>
#include <sys/select.h>
#endif
#include <sys/socket.h> /* socket.h header file is needed when using BSD socket */ /* 使用BSD socket，需要包含socket.h头文件 */
#include "netdb.h"

#define DEBUG_UDP_SERVER

#define DBG_TAG               "UDP"
#ifdef DEBUG_UDP_SERVER
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO /* DBG_ERROR */
#endif
#include <rtdbg.h>

#define BUFSZ   1024

static int started = 0;
static int is_running = 0;
static int port = 5000;

/**
* @brief  This function is for creating a udp server on RT-Thread
*/
static void udpserv(void *paramemter)
{
    int sock;
    int bytes_read;
    char *recv_data;
    socklen_t addr_len;
    struct sockaddr_in server_addr, client_addr;

    struct timeval timeout;
    fd_set readset;
    /* Allocate space for recv_data */
    /* 分配接收用的数据缓冲 */
    recv_data = rt_malloc(BUFSZ);
    if (recv_data == RT_NULL)
    {
        LOG_E("No memory");
        return;
    }
    /* Create a socket and set it to SOCK_DGRAM(UDP) */
    /* 创建一个socket，类型是SOCK_DGRAM，UDP类型 */
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        LOG_E("Create socket error");
        goto __exit;
    }
    /* Initialize server side address */
    /* 初始化服务端地址 */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));
    /* Bind socket to server side address */
    /* 绑定socket到服务端地址 */
    if (bind(sock, (struct sockaddr *)&server_addr,
             sizeof(struct sockaddr)) == -1)
    {
        LOG_E("Unable to bind");
        goto __exit;
    }

    addr_len = sizeof(struct sockaddr);
    LOG_I("UDPServer Waiting for client on port %d...", port);

    started = 1;
    is_running = 1;

    timeout.tv_sec = 3;
    timeout.tv_usec = 0;

    while (is_running)
    {
        FD_ZERO(&readset);
        FD_SET(sock, &readset);

        /* Wait for read or write */
        if (select(sock + 1, &readset, RT_NULL, RT_NULL, &timeout) == 0)
            continue;
        /* The maximum size received from sock is BUFSZ-1 bytes*/
        /* 从sock中收取最大BUFSZ - 1字节数据 */
        bytes_read = recvfrom(sock, recv_data, BUFSZ - 1, 0,
                              (struct sockaddr *)&client_addr, &addr_len);
        if (bytes_read < 0)
        {
            LOG_E("Received error, close the connect.");
            goto __exit;
        }
        else if (bytes_read == 0)
        {
            LOG_W("Received warning, recv function returns 0.");
            continue;
        }
        else
        {
            recv_data[bytes_read] = '\0'; /* Append '\0' at the end of message *//* 把末端清零 */
            /* Output received message */
            /* 输出接收的数据 */
            LOG_D("Received data = %s", recv_data);
            /* If the message received is 'exit', quit. */
            /* 如果接收数据是exit，退出 */
            if (strcmp(recv_data, "exit") == 0)
            {
                goto __exit;
            }
        }
    }

__exit:
    if (recv_data)
    {
        rt_free(recv_data);
        recv_data = RT_NULL;
    }
    if (sock >= 0)
    {
        closesocket(sock);
        sock = -1;
    }
    started = 0;
    is_running = 0;
}

/**
* @brief    The usage description of udp server on rt-Thread
*/
static void usage(void)
{
    rt_kprintf("Usage: udpserver -p <port>\n");
    rt_kprintf("       udpserver --stop\n");
    rt_kprintf("       udpserver --help\n");
    rt_kprintf("\n");
    rt_kprintf("Miscellaneous:\n");
    rt_kprintf("  -p           Specify the host port number\n");
    rt_kprintf("  --stop       Stop udpserver program\n");
    rt_kprintf("  --help       Print help information\n");
}

/**
* @brief    This function is for testing udp server on rt-Thread
*/
static void udpserver_test(int argc, char** argv)
{
    rt_thread_t tid;

    if (argc == 1 || argc > 3)
    {
        LOG_I("Please check the command you entered!\n");
        goto __usage;
    }
    else
    {
        if (rt_strcmp(argv[1], "--help") == 0)
        {
            goto __usage;
        }
        else if (rt_strcmp(argv[1], "--stop") == 0)
        {
            is_running = 0;
            return;
        }
        else if (rt_strcmp(argv[1], "-p") == 0)
        {
            if (started)
            {
                LOG_I("The udpserver has started!");
                LOG_I("Please stop udpserver firstly, by: udpserver --stop");
                return;
            }

            port = atoi(argv[2]);
        }
        else
        {
            goto __usage;
        }
    }

    tid = rt_thread_create("udp_serv",
        udpserv, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3, 20);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    return;

__usage:
    usage();
}

#ifdef RT_USING_FINSH
MSH_CMD_EXPORT_ALIAS(udpserver_test, udpserver,
    Start a udp server. Help: udpserver --help);
#endif
