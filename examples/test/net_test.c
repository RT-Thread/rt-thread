/*
 * Net Test Utilities for RT-Thread
 */
#include <rtthread.h>
#include <finsh.h>
#include <lwip/api.h>
#include <lwip/sockets.h>
#include <lwip/init.h>

/* 
 * UDP echo server
 */
#define UDP_ECHO_PORT   7
rt_thread_t udpecho_tid = RT_NULL;
void udpecho_entry(void *parameter)
{
    struct netconn *conn;
    struct netbuf *buf;
    struct ip_addr *addr;
    unsigned short port;

    conn = netconn_new(NETCONN_UDP);
    if(conn == NULL)
    {
        rt_kprintf("no memory error\n");
        return;
    }
    netconn_bind(conn, IP_ADDR_ANY, 7);

    while(1)
    {
        /* received data to buffer */
#if LWIP_VERSION_MINOR==3U 
        buf = netconn_recv(conn);
#else
        netconn_recv(conn, &buf);
#endif
        if(buf == NULL)	
        {
            break;
        }
        addr = netbuf_fromaddr(buf);
        port = netbuf_fromport(buf);

        /* send the data to buffer */
        netconn_connect(conn, addr, port);

        /* reset address, and send to client */
#if LWIP_VERSION_MINOR==3U 		
        buf->addr = RT_NULL;
#else
        buf->addr = *IP_ADDR_ANY;
#endif
		
        netconn_send(conn, buf);
		
        /* release buffer */
        netbuf_delete(buf);
    }
	
    netconn_delete(conn);
}
/*
 * UDP socket echo server
 */
#define UDP_SOCKET_ECHO_PORT	700
#define UDP_SOCKET_BUFFER_SIZE	4096
rt_thread_t udpecho_socket_tid = RT_NULL;
void udpecho_socket_entry(void *parameter)
{
    int sock;
    int bytes_read;
    char *recv_data;
    rt_uint32_t addr_len;
    struct sockaddr_in server_addr, client_addr;

    /* allocate the data buffer */
    recv_data = rt_malloc(UDP_SOCKET_BUFFER_SIZE);
    if (recv_data == RT_NULL)
    {
        /* no memory yet */
        rt_kprintf("no memory\n");
        return;
    }
    /* create a UDP socket */
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        rt_kprintf("create socket error\n");
        goto _exit;
    }

    /* initialize server address */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(UDP_SOCKET_ECHO_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    rt_memset(&(server_addr.sin_zero),0, sizeof(server_addr.sin_zero));

    /* bind socket to server address */
    if (bind(sock,(struct sockaddr *)&server_addr,
        sizeof(struct sockaddr)) == -1)
    {
        /* bind failed */
        rt_kprintf("bind error\n");
        goto _exit;
    }

    addr_len = sizeof(struct sockaddr);
    while (1)
    {
        /* try to receive from UDP socket */
        bytes_read = recvfrom(sock, recv_data, UDP_SOCKET_BUFFER_SIZE, 0,
            (struct sockaddr *)&client_addr, &addr_len);
	    
        /* send back */
        sendto(sock, recv_data, bytes_read, 0,
            (struct sockaddr *)&client_addr, addr_len);
    }

_exit:
    rt_free(recv_data);
    return;
}

/*
 * TCP echo server
 */
#define TCP_ECHO_PORT   7
rt_thread_t tcpecho_tid = RT_NULL;
void tcpecho_entry(void *parameter)
{
    struct netconn *conn, *newconn;
    err_t err;

    /* Create a new connection identifier. */
    conn = netconn_new(NETCONN_TCP);
    if(conn == NULL)
    {
        rt_kprintf("no memory error\n");
        return;
    }

    /* Bind connection to well known port number 7. */
    netconn_bind(conn, NULL, TCP_ECHO_PORT);

    /* Tell connection to go into listening mode. */
    netconn_listen(conn);

    while(1)
    {
        /* Grab new connection. */
#if LWIP_VERSION_MINOR==3U 
        newconn = netconn_accept(conn);
        if(newconn != NULL)
#else
        err = netconn_accept(conn, &newconn);
        if(err == ERR_OK)
#endif
        /* Process the new connection. */
        {
            struct netbuf *buf;
            void *data;
            u16_t len;
#if LWIP_VERSION_MINOR==3U
            while((buf = netconn_recv(newconn)) != NULL)
#else
            while((err = netconn_recv(newconn, &buf)) == ERR_OK)
#endif
            {
                do
                {
                    netbuf_data(buf, &data, &len);
                    err = netconn_write(newconn, data, len, NETCONN_COPY);
                    if(err != ERR_OK)
                    {
                        break;			    
                    }
                }while(netbuf_next(buf) >= 0);
		    
                netbuf_delete(buf);
            }
            /* Close connection and discard connection identifier. */
            netconn_delete(newconn);
        }
    }
	
    netconn_delete(conn);
}

/*
 * TCP socket echo server
 */
#define TCP_SOCKET_ECHO_PORT	700
#define TCP_SOCKET_BUFFER_SIZE	4096
rt_thread_t tcpecho_socket_tid = RT_NULL;
void tcpecho_socket_entry(void *parameter)
{
    char *recv_data;
    rt_uint32_t sin_size;
    int sock = -1, connected, bytes_received;
    struct sockaddr_in server_addr, client_addr;

    recv_data = rt_malloc(TCP_SOCKET_BUFFER_SIZE);
    if (recv_data == RT_NULL)
    {
        rt_kprintf("no memory\n");
        return;
    }

    /* create a TCP socket */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        rt_kprintf("create socket error\n");
        goto _exit;
    }

    /* initialize server address */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(TCP_SOCKET_ECHO_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    rt_memset(&(server_addr.sin_zero),8, sizeof(server_addr.sin_zero));

    /* bind to server address */
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        rt_kprintf("bind address failed\n");
        goto _exit;
    }

    /* listen */
    if (listen(sock, 5) == -1)
    {
        rt_kprintf("listen error\n");
        goto _exit;
    }

    sin_size = sizeof(struct sockaddr_in);
    while(1)
    {
        /* accept client connected */
        connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);
        if (connected > 0)
        {
            int timeout;
			
            /* set timeout option */
            timeout = 5000; /* 5second */
            setsockopt(connected, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

            /* handle this client */
            while (1)
            {
                /* receive data from this connection */
                bytes_received = recv(connected,recv_data, TCP_SOCKET_BUFFER_SIZE, 0);
                if (bytes_received <= 0)
                {
                    rt_kprintf("close client connection, errno: %d\n", rt_get_errno());
                    /* connection closed. */
                    lwip_close(connected);
                    break;
                }

                /* send data to client */
                send(connected, recv_data, bytes_received, 0);
            }
        }
    }

_exit:
    /* close socket */
    if (sock != -1) lwip_close(sock);
    rt_free(recv_data);

    return;
}

/*
 * NetIO TCP server
 */

/* network test utilities entry */
void net_test(void)
{
    /* start UDP echo server */
    if (udpecho_tid == RT_NULL)
    {
        udpecho_tid = rt_thread_create("uecho",
                                       udpecho_entry,
                                       RT_NULL, 
                                       512, 
                                       RT_THREAD_PRIORITY_MAX/2, 5);
        if (udpecho_tid != RT_NULL)
        {
            rt_thread_startup(udpecho_tid);
        }
    }

    if (udpecho_socket_tid == RT_NULL)
    {
        udpecho_socket_tid = rt_thread_create("uecho_s",
                                              udpecho_socket_entry,
                                              RT_NULL,
                                              512, 
                                              RT_THREAD_PRIORITY_MAX/2 + 1, 5);
        if (udpecho_socket_tid != RT_NULL)
        {
            rt_thread_startup(udpecho_socket_tid);
        }
    }

    if (tcpecho_tid == RT_NULL)
    {
        tcpecho_tid = rt_thread_create("techo",
                                       tcpecho_entry, 
                                       RT_NULL,
                                       512, 
                                       RT_THREAD_PRIORITY_MAX/2 + 2, 5);
        if (tcpecho_tid != RT_NULL)
        {
            rt_thread_startup(tcpecho_tid);
        }
    }
	
    if (tcpecho_socket_tid == RT_NULL)
    {
        tcpecho_socket_tid = rt_thread_create("techo_s",
                                              tcpecho_socket_entry, 
                                              RT_NULL,
                                              512, 
                                              RT_THREAD_PRIORITY_MAX/2 + 3, 5);
    if (tcpecho_socket_tid != RT_NULL)
    {
        rt_thread_startup(tcpecho_socket_tid);
    }
}
FINSH_FUNCTION_EXPORT(net_test, network test);
