/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>

#include <netdb.h>   /* 为了解析主机名，需要包含netdb.h头文件 */
#include <sys/socket.h> /* 使用BSD socket，需要包含socket.h头文件 */

void tcp_senddata(const char *url, int port, int length)
{
    struct hostent *host;
    int sock, err, result, timeout, index;
    struct sockaddr_in server_addr;
    rt_uint8_t *buffer_ptr;

    /* 通过函数入口参数url获得host地址（如果是域名，会做域名解析） */
    host = gethostbyname(url);
    /* 创建一个socket，类型是SOCKET_STREAM，TCP类型 */
    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
        /* 创建socket失败 */
        rt_kprintf("Socket error\n");
        return;
    }

    /* 申请内存 */
    buffer_ptr = rt_malloc(length);
    if(RT_NULL == buffer_ptr)
    {
        /* 申请内存失败 */
        rt_kprintf("No memory\n");
        return;
    }

    /* 构造发送数据 */
    for (index = 0; index < length; index ++)
        buffer_ptr[index] = index & 0xff;

    timeout = 100;
    /* 设置发送超时时间100ms */
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    /* 初始化预连接的服务端地址 */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    /* 连接到服务端 */
    err = connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    rt_kprintf("TCP thread connect error code: %d\n", err);

    while (1)
    {
        /* 发送数据到sock连接 */
        result = send(sock, buffer_ptr, length, MSG_DONTWAIT);
        if (result < 0) //数据发送错误处理
        {
            rt_kprintf("TCP thread send error: %d\n", result);
            closesocket(sock);

            /* 关闭连接，重新创建连接 */
            rt_thread_delay(10);

            if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
                rt_kprintf("TCP Socket error:%d\n", sock);

            err = connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
            rt_kprintf("TCP thread connect error code: %d\n", err);
        }
        else if (result == 0)
        {
            /* 打印send函数返回值为0的警告信息 */
            rt_kprintf("\n Send warning,send function returns 0.\r\n");
        }
    }
}

#ifdef RT_USING_FINSH
/* 输出tcpclient函数到finsh shell中 */
#endif

