#include <rtthread.h>

#include <sys/socket.h> /* 使用BSD socket，需要包含socket.h头文件 */
#include "netdb.h"

#define BUFSZ       (1024)

static const char send_data[] = "This is TCP Server from RT-Thread."; /* 发送用到的数据 */
static void tcpserv(void *parameter)
{
    char *recv_data; /* 用于接收的指针，后面会做一次动态分配以请求可用内存 */
    socklen_t sin_size;
    int sock, connected, bytes_received;
    struct sockaddr_in server_addr, client_addr;
    rt_bool_t stop = RT_FALSE; /* 停止标志 */
    int ret;

    recv_data = rt_malloc(BUFSZ + 1); /* 分配接收用的数据缓冲 */
    if (recv_data == RT_NULL)
    {
        rt_kprintf("No memory\n");
        return;
    }

    /* 一个socket在使用前，需要预先创建出来，指定SOCK_STREAM为TCP的socket */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        /* 创建失败的错误处理 */
        rt_kprintf("Socket error\n");

        /* 释放已分配的接收缓冲 */
        rt_free(recv_data);
        return;
    }

    /* 初始化服务端地址 */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000); /* 服务端工作的端口 */
    server_addr.sin_addr.s_addr = INADDR_ANY;
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    /* 绑定socket到服务端地址 */
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        /* 绑定失败 */
        rt_kprintf("Unable to bind\n");

        /* 释放已分配的接收缓冲 */
        rt_free(recv_data);
        return;
    }

    /* 在socket上进行监听 */
    if (listen(sock, 5) == -1)
    {
        rt_kprintf("Listen error\n");

        /* release recv buffer */
        rt_free(recv_data);
        return;
    }

    rt_kprintf("\nTCPServer Waiting for client on port 5000...\n");
    while (stop != RT_TRUE)
    {
        sin_size = sizeof(struct sockaddr_in);

        /* 接受一个客户端连接socket的请求，这个函数调用是阻塞式的 */
        connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);
        /* 返回的是连接成功的socket */
        if (connected < 0)
        {
            rt_kprintf("accept connection failed! errno = %d\n", errno);
            continue;
        }

        /* 接受返回的client_addr指向了客户端的地址信息 */
        rt_kprintf("I got a connection from (%s , %d)\n",
                   inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        /* 客户端连接的处理 */
        while (1)
        {
            /* 发送数据到connected socket */
            ret = send(connected, send_data, strlen(send_data), 0);
            if (ret < 0)
            {
                /* 发送失败，关闭这个连接 */
                closesocket(connected);
                rt_kprintf("\nsend error,close the socket.\r\n");
                break;
            }
            else if (ret == 0)
            {
                /* 打印send函数返回值为0的警告信息 */
                rt_kprintf("\n Send warning,send function return 0.\r\n");
            }

            /* 从connected socket中接收数据，接收buffer是1024大小，但并不一定能够收到1024大小的数据 */
            bytes_received = recv(connected, recv_data, BUFSZ, 0);
            if (bytes_received < 0)
            {
                /* 接收失败，关闭这个connected socket */
                closesocket(connected);
                break;
            }
            else if (bytes_received == 0)
            {
                /* 打印recv函数返回值为0的警告信息 */
                rt_kprintf("\nReceived warning,recv function return 0.\r\n");
                closesocket(connected);
                break;
            }

            /* 有接收到数据，把末端清零 */
            recv_data[bytes_received] = '\0';
            if (strcmp(recv_data, "q") == 0 || strcmp(recv_data, "Q") == 0)
            {
                /* 如果是首字母是q或Q，关闭这个连接 */
                closesocket(connected);
                break;
            }
            else if (strcmp(recv_data, "exit") == 0)
            {
                /* 如果接收的是exit，则关闭整个服务端 */
                closesocket(connected);
                stop = RT_TRUE;
                break;
            }
            else
            {
                /* 在控制终端显示收到的数据 */
                rt_kprintf("RECEIVED DATA = %s \n", recv_data);
            }
        }
    }

    /* 退出服务 */
    closesocket(sock);

    /* 释放接收缓冲 */
    rt_free(recv_data);

    return ;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
/* 输出tcpserv函数到finsh shell中 */
FINSH_FUNCTION_EXPORT(tcpserv, startup tcp server);
#endif
