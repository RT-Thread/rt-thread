/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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

#define DEBUG_TCP_CLIENT

#define DBG_TAG               "TCP"
#ifdef DEBUG_TCP_CLIENT
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO /* DBG_ERROR */
#endif
#include <rtdbg.h>

#include "lwip_demo.h"

#ifdef SAM_LWIP_EXAMPLE

#define BUFSZ   1024

static int started = 0;
static int is_running = 0;
static char url[256] = "www.baidu.com";
static int port = 8080;
static const char send_data[] = "This is TCP Client from RT-Thread."; /* The message be sent */ /* 发送用到的数据 */

/**
* @brief  This function is for creating a tcp client on RT-Thread
*/
static void tcpclient(void *arg)
{
    int ret;
    char *recv_data;
    int bytes_received;
    int sock = -1;
    struct hostent *host = RT_NULL;
    struct sockaddr_in server_addr;

    struct timeval timeout;
    fd_set readset;
    /* Get host address by parameter url(Domain name resolution if input domain) */
    /* 通过函数入口参数url获得host地址（如果是域名，会做域名解析） */
    host = gethostbyname(url);
    if (host == RT_NULL)
    {
        LOG_E("Get host by name failed!");
        return;
    }
    /* Allocate space for recv_data */
    /* 分配用于存放接收数据的缓冲 */
    recv_data = rt_malloc(BUFSZ);
    if (recv_data == RT_NULL)
    {
        LOG_E("No memory");
        return;
    }
    /* Create a socket and set it to SOCK_STREAM(TCP) */
    /* 创建一个socket，类型是SOCKET_STREAM，TCP类型 */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        /* Failed on creating socket */
        /* 创建socket失败 */
        LOG_E("Create socket error");
        goto __exit;
    }
    /* Initialize server side address */
    /* 初始化预连接的服务端地址 */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));
    /* Connect to server */
    /* 连接到服务端 */
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        /* Failed on connecting to server */
        /* 连接失败 */
        LOG_E("Connect fail!");
        goto __exit;
    }

    started = 1;
    is_running = 1;

    timeout.tv_sec = 3;
    timeout.tv_usec = 0;

    while (is_running)
    {
        FD_ZERO(&readset);
        FD_SET(sock, &readset);

        /* Wait for read */
        if (select(sock + 1, &readset, RT_NULL, RT_NULL, &timeout) == 0)
            continue;
        /* Receive the maximum size 1024 bytes from socket */
        /* 从sock连接中接收最大BUFSZ - 1字节数据 */
        bytes_received = recv(sock, recv_data, BUFSZ - 1, 0);
        if (bytes_received < 0)
        {
            /* Receive failed and close the connection */
            /* 接收失败，关闭这个连接 */
            LOG_E("Received error, close the socket.");
            goto __exit;
        }
        else if (bytes_received == 0)
        {
            /* Print warning message when recv function returns 0 */
            /* 打印recv函数返回值为0的警告信息 */
            LOG_W("Received warning, recv function returns 0.");
            continue;
        }
        else
        {
            /* Receive data successfully and append '\0' at the end of message */
            /* 有接收到数据，把末端清零 */
            recv_data[bytes_received] = '\0';

            if (rt_strcmp(recv_data, "q") == 0 || rt_strcmp(recv_data, "Q") == 0)
            {
                /* If the first letter is 'q' or 'Q', close the connection */
                /* 如果是首字母是q或Q，关闭这个连接 */
                LOG_I("Got a 'q' or 'Q', close the socket.");
                goto __exit;
            }
            else
            {
                /* Show the message in terminal */
                /* 在控制终端显示收到的数据 */
                LOG_D("Received data = %s", recv_data);
            }
        }
        /* Send message to connected socket */
        /* 发送数据到sock连接 */
        ret = send(sock, send_data, rt_strlen(send_data), 0);
        if (ret < 0)
        {
            /* Send failed, close the connection */
            /* 发送失败，关闭这个连接 */
            LOG_I("send error, close the socket.");
            goto __exit;
        }
        else if (ret == 0)
        {
            /* Print warning message when send function returns 0 */
            /* 打印send函数返回值为0的警告信息 */
            LOG_W("Send warning, send function returns 0.");
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
    return;
}

/**
 * @brief    Call this function will run LWIP example code.
 *
 * @note     .
 *
 * @param    None.
 *
 * @return   RT_OK or -RT_ERROR.
 */

rt_err_t lwip_demo_run(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("tcp_client",
                           tcpclient, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX/3, 20);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }

    return RT_EOK;
}
#endif

/*@}*/
