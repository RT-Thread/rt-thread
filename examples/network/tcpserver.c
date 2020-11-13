#include <rtthread.h>
#include <string.h>

#if !defined(SAL_USING_POSIX)
#error "Please enable SAL_USING_POSIX!"
#else
#include <sys/time.h>
#include <sys/select.h>
#endif
#include <sys/socket.h> /* 使用BSD socket，需要包含socket.h头文件 */
#include "netdb.h"

#define DEBUG_TCP_SERVER

#define DBG_TAG               "TCP"
#ifdef DEBUG_TCP_SERVER
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO /* DBG_ERROR */
#endif
#include <rtdbg.h>

#define BUFSZ       (1024)

static int started = 0;
static int is_running = 0;
static int port = 5000;
static const char send_data[] = "This is TCP Server from RT-Thread."; /* 发送用到的数据 */

static void tcpserv(void *arg)
{
    int ret;
    char *recv_data; /* 用于接收的指针，后面会做一次动态分配以请求可用内存 */
    int sock, connected, bytes_received;
    struct sockaddr_in server_addr, client_addr;

    struct timeval timeout;
    fd_set readset, readset_c;
    socklen_t sin_size = sizeof(struct sockaddr_in);

    recv_data = rt_malloc(BUFSZ + 1); /* 分配接收用的数据缓冲 */
    if (recv_data == RT_NULL)
    {
        LOG_E("No memory");
        return;
    }

    /* 一个socket在使用前，需要预先创建出来，指定SOCK_STREAM为TCP的socket */
    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
        LOG_E("Create socket error");
        goto __exit;
    }

    /* 初始化服务端地址 */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port); /* 服务端工作的端口 */
    server_addr.sin_addr.s_addr = INADDR_ANY;
    rt_memset(&(server_addr.sin_zero), 0x0, sizeof(server_addr.sin_zero));

    /* 绑定socket到服务端地址 */
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        LOG_E("Unable to bind");
        goto __exit;
    }

    /* 在socket上进行监听 */
    if (listen(sock, 10) == -1)
    {
        LOG_E("Listen error");
        goto __exit;
    }

    LOG_I("\nTCPServer Waiting for client on port %d...\n", port);

    started = 1;
    is_running = 1;

    timeout.tv_sec = 3;
    timeout.tv_usec = 0;

    while (is_running)
    {
        FD_ZERO(&readset);
        FD_SET(sock, &readset);

        LOG_I("Waiting for a new connection...");

        /* Wait for read or write */
        if (select(sock + 1, &readset, RT_NULL, RT_NULL, &timeout) == 0)
            continue;

        /* 接受一个客户端连接socket的请求，这个函数调用是阻塞式的 */
        connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);
        /* 返回的是连接成功的socket */
        if (connected < 0)
        {
            LOG_E("accept connection failed! errno = %d", errno);
            continue;
        }

        /* 接受返回的client_addr指向了客户端的地址信息 */
        LOG_I("I got a connection from (%s , %d)\n",
                   inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        /* 客户端连接的处理 */
        while (is_running)
        {
            FD_ZERO(&readset_c);
            FD_SET(connected, &readset_c);

            /* Wait for read or write */
            if (select(connected + 1, &readset_c, RT_NULL, RT_NULL, &timeout) == 0)
                continue;

            /* 从connected socket中接收数据，接收buffer是1024大小，但并不一定能够收到1024大小的数据 */
            bytes_received = recv(connected, recv_data, BUFSZ, 0);
            if (bytes_received < 0)
            {
                LOG_E("Received error, close the connect.");
                closesocket(connected);
                connected = -1;
                break;
            }
            else if (bytes_received == 0)
            {
                /* 打印recv函数返回值为0的警告信息 */
                LOG_W("Received warning, recv function return 0.");
                continue;
            }
            else
            {
                /* 有接收到数据，把末端清零 */
                recv_data[bytes_received] = '\0';
                if (strcmp(recv_data, "q") == 0 || strcmp(recv_data, "Q") == 0)
                {
                    /* 如果是首字母是q或Q，关闭这个连接 */
                    LOG_I("Got a 'q' or 'Q', close the connect.");
                    closesocket(connected);
                    connected = -1;
                    break;
                }
                else if (strcmp(recv_data, "exit") == 0)
                {
                    /* 如果接收的是exit，则关闭整个服务端 */
                    closesocket(connected);
                    connected = -1;
                    goto __exit;
                }
                else
                {
                    /* 在控制终端显示收到的数据 */
                    LOG_D("Received data = %s", recv_data);
                }
            }

            /* 发送数据到connected socket */
            ret = send(connected, send_data, rt_strlen(send_data), 0);
            if (ret < 0)
            {
                LOG_E("send error, close the connect.");
                closesocket(connected);
                connected = -1;
                break;
            }
            else if (ret == 0)
            {
                /* 打印send函数返回值为0的警告信息 */
                LOG_W("Send warning, send function return 0.");
            }
        }
    }

__exit:
    if (recv_data)
    {
        rt_free(recv_data);
        recv_data = RT_NULL;
    }
    if (connected >= 0)
    {
        closesocket(connected);
        connected = -1;
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

static void usage(void)
{
    rt_kprintf("Usage: tcpserver -p <port>\n");
    rt_kprintf("       tcpserver --stop\n");
    rt_kprintf("       tcpserver --help\n");
    rt_kprintf("\n");
    rt_kprintf("Miscellaneous:\n");
    rt_kprintf("  -p           Specify the host port number\n");
    rt_kprintf("  --stop       Stop tcpserver program\n");
    rt_kprintf("  --help       Print help information\n");
}

static void tcpserver_test(int argc, char** argv)
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
                LOG_I("The tcpserver has started!");
                LOG_I("Please stop tcpserver firstly, by: tcpserver --stop");
                return;
            }

            port = atoi(argv[2]);
        }
        else
        {
            goto __usage;
        }
    }

    tid = rt_thread_create("tcp_serv",
        tcpserv, RT_NULL,
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
MSH_CMD_EXPORT_ALIAS(tcpserver_test, tcpserver,
    Start a tcp server. Help: tcpserver --help);
#endif
