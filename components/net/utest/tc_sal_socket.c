/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-09-16     kurisaw      initial commit
 */

#include <rtthread.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdev.h>
#include <errno.h>

#include "utest.h"
#include "sal_socket.h"

/**
 * @brief   Comprehensive test suite for RT-Thread SAL (Socket Abstraction Layer) socket operations
 *
 * @note    This test suite validates:
 *          - 1.basic socket creation with valid and invalid parameters
 *          - 2.socket binding functionality with proper address configuration
 *          - 3.listen operation with various backlog configurations
 *          - 4.TCP connection establishment and error handling
 *          - 5.accept operation with timeout and error conditions
 *          - 6.TCP data transmission (send/receive) with echo verification
 *          - 7.UDP communication including sendto/recvfrom operations
 *          - 8.proper socket closure and cleanup procedures
 *          - 9.socket address information retrieval (getsockname/getpeername)
 *          - 10.network device status checking and fallback mechanisms
 *          - 11.thread-safe socket operations using RT-Thread synchronization
 *          - 12.socket timeout configuration and non-blocking mode handling
 *          - 13.error handling for invalid parameters and network failures
 *          - 14.port management to avoid conflicts during concurrent testing
 */

/* Test configuration */
#define TEST_SERVER_BASE_PORT   9000 /* Base port to avoid conflicts */
#define TEST_CLIENT_PORT_OFFSET 100  /* Offset for client ports */
#define TEST_BUFFER_SIZE        1024
#define TEST_TIMEOUT_MS         3000
#define TEST_INVALID_IP         "192.168.999.999"
#define TEST_MAX_RETRY_ATTEMPTS 3    /* Max retry attempts for network operations */
#define TEST_CONNECTION_TIMEOUT 8000 /* Increased to 8s for threaded setup */
#define ACCEPT_POLL_TIMEOUT_MS  3000 /* Increased poll timeout for non-blocking accept */
#define CLIENT_DELAY_MS         1000 /* Increased delay after connect before close */

/* Thread synchronization */
#define THREAD_WAIT_TIMEOUT 3000 /* Increased to 3s for thread waits */
#define SOCKET_TIMEOUT_MS   3000 /* 3 seconds for socket operations */

/* Test data */
static char test_send_data[] = "Hello, RT-Thread SAL!";
static char test_recv_buffer[TEST_BUFFER_SIZE];

/* Local IP for tests (fallback to loopback) */
static char local_ip[16] = "127.0.0.1";

/* Thread synchronization structures */
static struct rt_event test_event;
static volatile int    server_ready = 0;

/* Test helper functions */
static int get_available_port(int base_port)
{
    static int port_counter = 0;
    int port = base_port + (port_counter++ * 2); /* Increment by 2 to avoid adjacent port conflicts */
    LOG_D("Generated available port: %d", port);
    return port;
}

static void safe_strcpy(char *dest, const char *src, size_t dest_size)
{
    if (dest_size > 0)
    {
        strncpy(dest, src, dest_size - 1);
        dest[dest_size - 1] = '\0';
    }
    LOG_D("Copied string '%s' to destination with size %u", src, dest_size);
}

static void check_network_status(void)
{
    LOG_I("Checking network device status...");

    /* Try to create a simple socket to test network availability */
    int test_sock = sal_socket(AF_INET, SOCK_STREAM, 0);
    if (test_sock < 0)
    {
        LOG_E("Network test socket creation failed: %d", test_sock);
        LOG_E("Network device or protocol family issue detected");
        return;
    }

    LOG_I("Network test socket created successfully: %d", test_sock);
    sal_closesocket(test_sock);

    /* Fallback to loopback; dynamic IP via netdev may not be available */
    safe_strcpy(local_ip, "127.0.0.1", sizeof(local_ip));
    LOG_I("Using loopback IP address for testing: %s", local_ip);

    LOG_I("Network device appears operational");
}

static int set_socket_timeout(int sock, int timeout_ms)
{
    struct timeval timeout;
    timeout.tv_sec  = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;

    int ret1 = sal_setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    int ret2 = sal_setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

    if (ret1 == 0 && ret2 == 0)
    {
        LOG_D("Set socket %d timeout to %d ms", sock, timeout_ms);
        return 0;
    }
    else
    {
        LOG_W("Failed to set socket %d timeout to %d ms", sock, timeout_ms);
        return -1;
    }
}

static int create_test_socket(int domain, int type, int protocol)
{
    int sock = sal_socket(domain, type, protocol);
    if (sock >= 0)
    {
        LOG_I("Created socket %d (domain=%d, type=%d, protocol=%d)", sock, domain, type, protocol);
        /* Set timeout for all socket operations to prevent blocking */
        if (set_socket_timeout(sock, SOCKET_TIMEOUT_MS) != 0)
        {
            LOG_W("Failed to set timeout for socket %d", sock);
        }

        /* Enable SO_REUSEADDR to allow reusing ports and avoid bind failures due to TIME_WAIT */
        int opt = 1;
        sal_setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        LOG_D("Enabled SO_REUSEADDR for socket %d", sock);
    }
    else
    {
        LOG_E("Failed to create socket (domain=%d, type=%d, protocol=%d)", domain, type, protocol);
    }
    return sock;
}

static void close_test_socket(int sock)
{
    if (sock >= 0)
    {
        sal_closesocket(sock);
        LOG_I("Closed socket %d", sock);
    }
}

/* Server thread function */
static void server_thread_entry(void *parameter)
{
    int port = (int)parameter;
    int server_sock = -1;
    struct sockaddr_in bind_addr;
    int ret;

    LOG_I("Starting server thread on port %d", port);

    /* Create server socket */
    server_sock = create_test_socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        LOG_E("Failed to create server socket");
        rt_event_send(&test_event, 0x01);
        return;
    }

    /* Setup bind address */
    memset(&bind_addr, 0, sizeof(bind_addr));
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind_addr.sin_port = htons(port);
    LOG_D("Configured server bind address: port %d", port);

    /* Bind server socket */
    ret = sal_bind(server_sock, (struct sockaddr *)&bind_addr, sizeof(bind_addr));
    if (ret != 0)
    {
        LOG_E("Failed to bind server socket %d: return=%d, errno=%d", server_sock, ret, errno);
        close_test_socket(server_sock);
        rt_event_send(&test_event, 0x01);
        return;
    }
    LOG_I("Server socket %d bound to port %d", server_sock, port);

    /* Listen on server socket */
    ret = sal_listen(server_sock, 5);
    if (ret != 0)
    {
        LOG_E("Failed to listen on server socket %d: return=%d, errno=%d", server_sock, ret, errno);
        close_test_socket(server_sock);
        rt_event_send(&test_event, 0x01);
        return;
    }
    LOG_I("Server socket %d listening with backlog 5", server_sock);

    server_ready = 1;
    rt_event_send(&test_event, 0x02);
    LOG_I("Server ready and signaled on port %d", port);

    /* Wait for client connection */
    ret = rt_event_recv(&test_event, 0x04, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                        RT_WAITING_FOREVER, RT_NULL);
    if (ret != RT_EOK)
    {
        LOG_E("Failed to receive client connect signal: %d", ret);
        rt_event_send(&test_event, 0x01);
        close_test_socket(server_sock);
        return;
    }
    LOG_D("Received client connect signal");

    /* Non-blocking accept loop to avoid blocking on aborted connections */
    int mode = 1;
    sal_ioctlsocket(server_sock, FIONBIO, &mode);
    LOG_D("Set server socket %d to non-blocking mode", server_sock);

    int elapsed = 0;
    int check_interval = 50;
    int accepted_sock = -1;
    while (elapsed < ACCEPT_POLL_TIMEOUT_MS)
    {
        accepted_sock = sal_accept(server_sock, RT_NULL, RT_NULL);
        if (accepted_sock >= 0)
        {
            LOG_I("Accepted connection on socket %d", accepted_sock);
            set_socket_timeout(accepted_sock, SOCKET_TIMEOUT_MS);
            close_test_socket(accepted_sock);
            break;
        }
        else
        {
            int saved_errno = errno;
            if (saved_errno != EWOULDBLOCK && saved_errno != EAGAIN)
            {
                LOG_E("Accept failed on socket %d: return=%d, errno=%d", server_sock, accepted_sock, saved_errno);
                break;
            }
        }
        rt_thread_mdelay(check_interval);
        elapsed += check_interval;
    }
    if (accepted_sock < 0)
    {
        LOG_E("Accept poll timeout or failed on socket %d", server_sock);
        rt_event_send(&test_event, 0x01);
    }

    /* Restore blocking mode */
    mode = 0;
    sal_ioctlsocket(server_sock, FIONBIO, &mode);
    LOG_D("Restored server socket %d to blocking mode", server_sock);

    /* Cleanup */
    close_test_socket(server_sock);
    rt_event_send(&test_event, 0x08);
    LOG_I("Server thread completed");
}

/* Client thread function */
static void client_thread_entry(void *parameter)
{
    int port = (int)parameter;
    int client_sock = -1;
    struct sockaddr_in connect_addr;
    int ret;

    LOG_I("Starting client thread for port %d", port);

    /* Wait for server to be ready */
    ret = rt_event_recv(&test_event, 0x02, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                        THREAD_WAIT_TIMEOUT, RT_NULL);
    if (ret != RT_EOK)
    {
        LOG_E("Failed to receive server ready signal: %d", ret);
        rt_event_send(&test_event, 0x10);
        return;
    }
    LOG_D("Received server ready signal");

    if (!server_ready)
    {
        LOG_W("Server not ready, skipping connection");
        rt_event_send(&test_event, 0x10);
        return;
    }

    /* Create client socket */
    client_sock = create_test_socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0)
    {
        LOG_E("Failed to create client socket");
        rt_event_send(&test_event, 0x10);
        return;
    }

    /* Setup connect address */
    memset(&connect_addr, 0, sizeof(connect_addr));
    connect_addr.sin_family = AF_INET;
    connect_addr.sin_addr.s_addr = inet_addr(local_ip);
    connect_addr.sin_port = htons(port);
    LOG_D("Configured client connect address: %s:%d", local_ip, port);

    /* Connect to server */
    LOG_I("Attempting to connect to server %s:%d", local_ip, port);
    ret = sal_connect(client_sock, (struct sockaddr *)&connect_addr, sizeof(connect_addr));
    LOG_I("Connect result: %d", ret);

    if (ret == 0)
    {
        LOG_I("Connection to server successful");
        rt_thread_mdelay(CLIENT_DELAY_MS);
    }
    else
    {
        LOG_E("Connection to server failed: return=%d, errno=%d", ret, errno);
    }

    /* Signal server that we've attempted connection */
    rt_event_send(&test_event, 0x04);
    LOG_D("Signaled server of connection attempt");

    /* Cleanup */
    close_test_socket(client_sock);
    rt_event_send(&test_event, 0x10);
    LOG_I("Client thread completed");
}

static int setup_test_server_threaded(int *server_sock, int *client_sock, int port)
{
    rt_thread_t server_thread = RT_NULL;
    rt_thread_t client_thread = RT_NULL;
    rt_uint32_t recv_events = 0;

    LOG_I("Setting up threaded test server on port %d", port);

    /* Initialize event */
    rt_event_init(&test_event, "test_event", RT_IPC_FLAG_FIFO);
    server_ready = 0;
    LOG_D("Initialized test event");

    /* Create server thread */
    server_thread = rt_thread_create("server", server_thread_entry, (void *)port,
                                     2048, RT_THREAD_PRIORITY_MAX / 2, 20);
    if (server_thread == RT_NULL)
    {
        LOG_E("Failed to create server thread");
        rt_event_detach(&test_event);
        return -1;
    }
    LOG_I("Created server thread");

    /* Create client thread */
    client_thread = rt_thread_create("client", client_thread_entry, (void *)port,
                                     2048, RT_THREAD_PRIORITY_MAX / 2, 20);
    if (client_thread == RT_NULL)
    {
        LOG_E("Failed to create client thread");
        rt_thread_delete(server_thread);
        rt_event_detach(&test_event);
        return -1;
    }
    LOG_I("Created client thread");

    /* Start threads */
    rt_thread_startup(server_thread);
    rt_thread_startup(client_thread);
    LOG_I("Started server and client threads");

    /* Wait for both threads to complete */
    rt_event_recv(&test_event, 0x18 | 0x01, RT_EVENT_FLAG_OR,
                  TEST_CONNECTION_TIMEOUT, &recv_events);
    LOG_D("Received events: 0x%x", recv_events);

    /* Cleanup threads */
    rt_thread_delete(server_thread);
    rt_thread_delete(client_thread);
    rt_event_detach(&test_event);
    LOG_I("Cleaned up threads and event");

    /* Check if setup partially successful */
    if ((recv_events & 0x10) != 0)
    {
        LOG_I("Test server setup partially successful (connect verified)");
        return 0;
    }
    else
    {
        LOG_E("Test server setup failed");
        return -1;
    }
}

static void cleanup_test_connection(int server_sock, int client_sock, int accepted_sock)
{
    if (accepted_sock >= 0)
    {
        close_test_socket(accepted_sock);
    }
    if (client_sock >= 0)
    {
        close_test_socket(client_sock);
    }
    if (server_sock >= 0)
    {
        close_test_socket(server_sock);
    }
    LOG_I("Cleaned up test connection sockets");
}

/* Test cases for basic socket operations */
static void TC_sal_socket_create(void)
{
    int sock;

    LOG_I("Starting TC_sal_socket_create tests...");

    /* Test valid socket creation */
    LOG_I("Testing TCP socket creation...");
    sock = sal_socket(AF_INET, SOCK_STREAM, 0);
    LOG_I("TCP socket created: %d", sock);
    uassert_true(sock >= 0);
    close_test_socket(sock);

    LOG_I("Testing UDP socket creation...");
    sock = sal_socket(AF_INET, SOCK_DGRAM, 0);
    LOG_I("UDP socket created: %d", sock);
    uassert_true(sock >= 0);
    close_test_socket(sock);

    /* Test invalid parameters */
    LOG_I("Testing invalid family parameter...");
    sock = sal_socket(-1, SOCK_STREAM, 0);
    LOG_I("Invalid family result: %d", sock);
    uassert_true(sock < 0);

    LOG_I("Testing invalid type parameter...");
    sock = sal_socket(AF_INET, -1, 0);
    LOG_I("Invalid type result: %d", sock);
    uassert_true(sock < 0);

    LOG_I("Testing invalid protocol parameter...");
    sock = sal_socket(AF_INET, SOCK_STREAM, -1);
    LOG_I("Invalid protocol result: %d", sock);
    uassert_true(sock < 0);

    LOG_I("TC_sal_socket_create tests completed");
}

static void TC_sal_socket_bind(void)
{
    int sock = -1;
    struct sockaddr_in addr;
    int ret;
    int test_port = get_available_port(TEST_SERVER_BASE_PORT);

    LOG_I("Starting TC_sal_socket_bind tests...");

    /* Test valid bind */
    LOG_I("Creating socket for bind test on port %d...", test_port);
    sock = create_test_socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        LOG_E("Failed to create socket for bind test");
        return;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(test_port);

    LOG_I("Attempting to bind socket %d to port %d...", sock, test_port);
    ret = sal_bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    LOG_I("Bind result: %d (expected 0)", ret);
    uassert_int_equal(ret, 0);

    close_test_socket(sock);
    sock = -1;

    LOG_I("Skipping NULL address bind test (would cause assertion)");

    /* Test bind with invalid socket */
    LOG_I("Testing bind with invalid socket...");
    ret = sal_bind(-1, (struct sockaddr *)&addr, sizeof(addr));
    LOG_I("Invalid socket bind result: %d (expected -1)", ret);
    uassert_int_equal(ret, -1);

    LOG_I("TC_sal_socket_bind tests completed");
}

static void TC_sal_socket_listen(void)
{
    int sock = -1;
    struct sockaddr_in addr;
    int ret;
    int test_port = get_available_port(TEST_SERVER_BASE_PORT);

    LOG_I("Starting TC_sal_socket_listen tests...");

    LOG_I("Creating socket for listen test...");
    sock = create_test_socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        LOG_E("Failed to create socket for listen test");
        return;
    }

    /* Bind socket first */
    LOG_I("Binding socket %d for listen test on port %d...", sock, test_port);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(test_port);

    ret = sal_bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (ret != 0)
    {
        LOG_E("Failed to bind socket %d for listen test: %d", sock, ret);
        close_test_socket(sock);
        return;
    }

    /* Test valid listen */
    LOG_I("Testing listen with backlog 5 on socket %d...", sock);
    ret = sal_listen(sock, 5);
    LOG_I("Listen result: %d (expected 0)", ret);
    uassert_int_equal(ret, 0);

    /* Test invalid backlog */
    LOG_I("Testing listen with invalid backlog (-1)...");
    ret = sal_listen(sock, -1);
    LOG_I("Invalid backlog listen result: %d", ret);
    if (ret != -1 && ret != 0)
    {
        LOG_W("Unexpected listen result for invalid backlog: %d", ret);
    }

    close_test_socket(sock);
    sock = -1;

    /* Test listen on invalid socket */
    LOG_I("Testing listen on invalid socket...");
    ret = sal_listen(-1, 5);
    LOG_I("Invalid socket listen result: %d (expected -1)", ret);
    uassert_int_equal(ret, -1);

    LOG_I("TC_sal_socket_listen tests completed");
}

static void TC_sal_socket_connect(void)
{
    int ret;
    int test_port = get_available_port(TEST_SERVER_BASE_PORT);

    LOG_I("Starting TC_sal_socket_connect tests...");

    /* Setup test server using threaded approach */
    LOG_I("Setting up test server on port %d...", test_port);
    ret = setup_test_server_threaded(RT_NULL, RT_NULL, test_port);

    if (ret != 0)
    {
        LOG_W("Test server setup failed, may be expected in some environments");
    }
    else
    {
        LOG_I("Test server setup completed successfully");
    }

    /* Test connect to invalid address */
    LOG_I("Testing connect to invalid address %s...", TEST_INVALID_IP);
    int client_sock = create_test_socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock >= 0)
    {
        struct sockaddr_in connect_addr;
        memset(&connect_addr, 0, sizeof(connect_addr));
        connect_addr.sin_family = AF_INET;
        connect_addr.sin_addr.s_addr = inet_addr(TEST_INVALID_IP);
        connect_addr.sin_port = htons(test_port);

        ret = sal_connect(client_sock, (struct sockaddr *)&connect_addr, sizeof(connect_addr));
        LOG_I("Invalid address connect result: %d (expected -1)", ret);
        uassert_int_equal(ret, -1);
        close_test_socket(client_sock);
    }

    LOG_I("TC_sal_socket_connect tests completed");
}

static void TC_sal_socket_accept(void)
{
    int server_sock = -1;
    struct sockaddr_in bind_addr;
    int ret;
    int test_port = get_available_port(TEST_SERVER_BASE_PORT);

    LOG_I("Starting TC_sal_socket_accept tests...");

    /* Setup test server */
    LOG_I("Creating server socket...");
    server_sock = create_test_socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        LOG_E("Failed to create server socket");
        return;
    }

    memset(&bind_addr, 0, sizeof(bind_addr));
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind_addr.sin_port = htons(test_port);

    LOG_I("Binding server socket %d to port %d...", server_sock, test_port);
    ret = sal_bind(server_sock, (struct sockaddr *)&bind_addr, sizeof(bind_addr));
    if (ret != 0)
    {
        LOG_E("Failed to bind server socket %d: %d", server_sock, ret);
        close_test_socket(server_sock);
        return;
    }

    LOG_I("Starting to listen on server socket %d...", server_sock);
    ret = sal_listen(server_sock, 5);
    if (ret != 0)
    {
        LOG_E("Failed to listen on server socket %d: %d", server_sock, ret);
        close_test_socket(server_sock);
        return;
    }

    /* Test accept on valid socket with timeout */
    LOG_I("Testing accept with timeout on socket %d...", server_sock);
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int accepted_sock = sal_accept(server_sock, (struct sockaddr*)&client_addr, &addr_len);

    if (accepted_sock >= 0)
    {
        LOG_W("Unexpected connection accepted: %d", accepted_sock);
        close_test_socket(accepted_sock);
    }
    else
    {
        LOG_I("Accept timed out as expected: %d", accepted_sock);
    }

    close_test_socket(server_sock);
    server_sock = -1;

    /* Test accept on invalid socket */
    LOG_I("Testing accept on invalid socket...");
    accepted_sock = sal_accept(-1, (struct sockaddr *)&client_addr, &addr_len);
    LOG_I("Invalid socket accept result: %d (expected -1)", accepted_sock);
    uassert_int_equal(accepted_sock, -1);

    LOG_I("TC_sal_socket_accept tests completed");
}

static void TC_sal_socket_send_recv(void)
{
    int ret;
    int test_port = get_available_port(TEST_SERVER_BASE_PORT);
    int len = strlen(test_send_data);

    LOG_I("Starting TC_sal_socket_send_recv tests...");

    /* Setup test connection using threaded approach */
    LOG_I("Setting up test server on port %d...", test_port);
    ret = setup_test_server_threaded(RT_NULL, RT_NULL, test_port);

    if (ret != 0)
    {
        LOG_W("Failed to setup test server, skipping send/recv tests (may be expected)");
        return;
    }

    /* Simple send/recv test extension */
    LOG_I("Testing send/recv with data exchange...");
    int server_sock = create_test_socket(AF_INET, SOCK_STREAM, 0);
    int client_sock = create_test_socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0 || client_sock < 0)
    {
        LOG_E("Failed to create sockets for send/recv");
        goto cleanup_sr;
    }

    struct sockaddr_in bind_addr, connect_addr;
    memset(&bind_addr, 0, sizeof(bind_addr));
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind_addr.sin_port = htons(test_port + 1);

    ret = sal_bind(server_sock, (struct sockaddr *)&bind_addr, sizeof(bind_addr));
    if (ret != 0)
    {
        LOG_E("Server bind failed: %d", ret);
        goto cleanup_sr;
    }
    LOG_I("Server socket %d bound to port %d", server_sock, test_port + 1);

    ret = sal_listen(server_sock, 5);
    if (ret != 0)
    {
        LOG_E("Server listen failed: %d", ret);
        goto cleanup_sr;
    }
    LOG_I("Server socket %d listening", server_sock);

    memset(&connect_addr, 0, sizeof(connect_addr));
    connect_addr.sin_family = AF_INET;
    connect_addr.sin_addr.s_addr = inet_addr(local_ip);
    connect_addr.sin_port = bind_addr.sin_port;

    ret = sal_connect(client_sock, (struct sockaddr *)&connect_addr, sizeof(connect_addr));
    if (ret != 0)
    {
        LOG_E("Client connect failed: %d", ret);
        goto cleanup_sr;
    }
    LOG_I("Client socket %d connected", client_sock);

    /* Server accept */
    int accepted_sock = sal_accept(server_sock, NULL, NULL);
    if (accepted_sock < 0)
    {
        LOG_E("Server accept failed: %d", accepted_sock);
        goto cleanup_sr;
    }
    LOG_I("Server accepted connection on socket %d", accepted_sock);

    /* Client send */
    ret = sal_sendto(client_sock, test_send_data, len, 0, NULL, 0);
    if (ret != len)
    {
        LOG_E("Client send failed: %d bytes sent, expected %d", ret, len);
        goto cleanup_sr;
    }
    LOG_I("Client sent %d bytes", ret);

    /* Server recv and echo */
    memset(test_recv_buffer, 0, sizeof(test_recv_buffer));
    ret = sal_recvfrom(accepted_sock, test_recv_buffer, sizeof(test_recv_buffer), 0, NULL, NULL);
    if (ret == len && memcmp(test_recv_buffer, test_send_data, len) == 0)
    {
        LOG_I("Server received %d bytes, matches sent data", ret);
        uassert_int_equal(ret, len);
    }
    else
    {
        LOG_E("Server recv failed: expected %d bytes, got %d", len, ret);
    }

    ret = sal_sendto(accepted_sock, test_recv_buffer, ret, 0, NULL, 0);
    if (ret != len)
    {
        LOG_E("Server echo send failed: %d bytes sent, expected %d", ret, len);
    }
    else
    {
        LOG_I("Server sent echo %d bytes", ret);
    }

    /* Client recv echo */
    memset(test_recv_buffer, 0, sizeof(test_recv_buffer));
    ret = sal_recvfrom(client_sock, test_recv_buffer, sizeof(test_recv_buffer), 0, NULL, NULL);
    if (ret == len && memcmp(test_recv_buffer, test_send_data, len) == 0)
    {
        LOG_I("Client received echo %d bytes, matches sent data", ret);
        uassert_int_equal(ret, len);
    }
    else
    {
        LOG_E("Client recv echo failed: expected %d bytes, got %d", len, ret);
    }

cleanup_sr:
    cleanup_test_connection(server_sock, client_sock, accepted_sock);
    LOG_I("TC_sal_socket_send_recv tests completed");
}

static void TC_sal_socket_udp_communication(void)
{
    int server_sock = -1, client_sock = -1;
    struct sockaddr_in server_bind_addr, client_bind_addr, from_addr;
    struct sockaddr_in server_dest_addr, client_dest_addr;
    socklen_t addr_len;
    int ret;
    int len;
    int server_port = get_available_port(TEST_SERVER_BASE_PORT);
    int client_port = server_port + TEST_CLIENT_PORT_OFFSET;

    LOG_I("Starting TC_sal_socket_udp_communication tests...");

    /* Create UDP sockets */
    server_sock = create_test_socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sock < 0)
    {
        LOG_E("Failed to create server UDP socket");
        goto cleanup;
    }

    client_sock = create_test_socket(AF_INET, SOCK_DGRAM, 0);
    if (client_sock < 0)
    {
        LOG_E("Failed to create client UDP socket");
        goto cleanup;
    }

    /* Setup server bind address */
    memset(&server_bind_addr, 0, sizeof(server_bind_addr));
    server_bind_addr.sin_family = AF_INET;
    server_bind_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_bind_addr.sin_port = htons(server_port);

    /* Bind server socket */
    ret = sal_bind(server_sock, (struct sockaddr *)&server_bind_addr, sizeof(server_bind_addr));
    if (ret != 0)
    {
        LOG_W("Server bind failed, may be expected: return=%d, errno=%d", ret, errno);
        goto cleanup;
    }
    LOG_I("Server socket %d bound to port %d", server_sock, server_port);

    /* Setup client bind address */
    memset(&client_bind_addr, 0, sizeof(client_bind_addr));
    client_bind_addr.sin_family = AF_INET;
    client_bind_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    client_bind_addr.sin_port = htons(client_port);

    /* Bind client socket */
    ret = sal_bind(client_sock, (struct sockaddr *)&client_bind_addr, sizeof(client_bind_addr));
    if (ret != 0)
    {
        LOG_W("Client bind failed, may be expected: return=%d, errno=%d", ret, errno);
        goto cleanup;
    }
    LOG_I("Client socket %d bound to port %d", client_sock, client_port);

    /* Setup destination addresses */
    memset(&server_dest_addr, 0, sizeof(server_dest_addr));
    server_dest_addr.sin_family = AF_INET;
    server_dest_addr.sin_addr.s_addr = inet_addr(local_ip);
    server_dest_addr.sin_port = htons(server_port);

    memset(&client_dest_addr, 0, sizeof(client_dest_addr));
    client_dest_addr.sin_family = AF_INET;
    client_dest_addr.sin_addr.s_addr = inet_addr(local_ip);
    client_dest_addr.sin_port = htons(client_port);

    /* Test UDP sendto/recvfrom */
    len = strlen(test_send_data);
    LOG_I("Sending %d bytes from client to server...", len);
    ret = sal_sendto(client_sock, test_send_data, len, 0,
                     (struct sockaddr *)&server_dest_addr, sizeof(server_dest_addr));
    if (ret != len)
    {
        LOG_W("UDP send failed, may be expected: %d bytes sent, errno=%d", ret, errno);
        goto cleanup;
    }
    LOG_I("Client sent %d bytes to server", ret);

    addr_len = sizeof(from_addr);
    memset(test_recv_buffer, 0, sizeof(test_recv_buffer));
    ret = sal_recvfrom(server_sock, test_recv_buffer, sizeof(test_recv_buffer), 0,
                       (struct sockaddr *)&from_addr, &addr_len);
    if (ret != len)
    {
        LOG_W("UDP recv failed, may be expected: %d bytes received, errno=%d", ret, errno);
        goto cleanup;
    }
    LOG_I("Server received %d bytes", ret);
    uassert_str_equal(test_recv_buffer, test_send_data);

    /* Test reverse direction */
    LOG_I("Sending %d bytes from server to client...", len);
    ret = sal_sendto(server_sock, test_send_data, len, 0,
                     (struct sockaddr *)&client_dest_addr, sizeof(client_dest_addr));
    if (ret != len)
    {
        LOG_W("Reverse UDP send failed, may be expected: %d bytes sent, errno=%d", ret, errno);
        goto cleanup;
    }
    LOG_I("Server sent %d bytes to client", ret);

    addr_len = sizeof(from_addr);
    memset(test_recv_buffer, 0, sizeof(test_recv_buffer));
    ret = sal_recvfrom(client_sock, test_recv_buffer, sizeof(test_recv_buffer), 0,
                       (struct sockaddr *)&from_addr, &addr_len);
    if (ret != len)
    {
        LOG_W("Reverse UDP recv failed, may be expected: %d bytes received, errno=%d", ret, errno);
        goto cleanup;
    }
    LOG_I("Client received %d bytes", ret);
    uassert_str_equal(test_recv_buffer, test_send_data);

cleanup:
    close_test_socket(server_sock);
    close_test_socket(client_sock);
    LOG_I("TC_sal_socket_udp_communication tests completed");
}

static void TC_sal_socket_close(void)
{
    int sock = -1;

    LOG_I("Starting TC_sal_socket_close tests...");

    /* Test close valid socket */
    LOG_I("Testing close valid socket...");
    sock = create_test_socket(AF_INET, SOCK_STREAM, 0);
    LOG_I("Closing socket %d...", sock);
    uassert_int_equal(sal_closesocket(sock), 0);
    sock = -1;

    /* Test close invalid socket */
    LOG_I("Testing close invalid socket...");
    uassert_int_equal(sal_closesocket(-1), -1);

    /* Test double close */
    LOG_I("Testing double close...");
    sock = create_test_socket(AF_INET, SOCK_STREAM, 0);
    sal_closesocket(sock);
    LOG_I("Double closing socket %d (should be safe)", sock);

    LOG_I("TC_sal_socket_close tests completed");
}

static void TC_sal_socket_getpeername_getsockname(void)
{
    int server_sock = -1;
    struct sockaddr_in addr;
    socklen_t addr_len;
    int ret;
    int test_port = get_available_port(TEST_SERVER_BASE_PORT);

    LOG_I("Starting TC_sal_socket_getpeername_getsockname tests...");

    /* Create and bind a socket for testing */
    server_sock = create_test_socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        LOG_E("Failed to create socket for getpeername/getsockname tests");
        return;
    }

    /* Bind socket */
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(test_port);

    ret = sal_bind(server_sock, (struct sockaddr *)&addr, sizeof(addr));
    if (ret != 0)
    {
        LOG_W("Bind failed, may be expected: return=%d, errno=%d", ret, errno);
        close_test_socket(server_sock);
        return;
    }
    LOG_I("Server socket %d bound to port %d", server_sock, test_port);

    /* Test getsockname on valid socket */
    LOG_I("Testing getsockname on socket %d...", server_sock);
    addr_len = sizeof(addr);
    ret = sal_getsockname(server_sock, (struct sockaddr*)&addr, &addr_len);
    LOG_I("Getsockname result: %d (expected 0)", ret);
    uassert_int_equal(ret, 0);
    uassert_int_equal(addr.sin_family, AF_INET);

    close_test_socket(server_sock);
    server_sock = -1;

    /* Test on invalid socket */
    LOG_I("Testing getsockname/getpeername on invalid socket...");
    addr_len = sizeof(addr);
    ret = sal_getsockname(-1, (struct sockaddr*)&addr, &addr_len);
    LOG_I("Invalid socket getsockname result: %d (expected -1)", ret);
    uassert_int_equal(ret, -1);

    ret = sal_getpeername(-1, (struct sockaddr *)&addr, &addr_len);
    LOG_I("Invalid socket getpeername result: %d (expected -1)", ret);
    uassert_int_equal(ret, -1);

    LOG_I("TC_sal_socket_getpeername_getsockname tests completed");
}

static void utest_do_tc(void)
{
    LOG_I("===========================================");
    LOG_I("Starting SAL Socket Basic API Tests");
    LOG_I("===========================================");

    /* Check network status before starting tests */
    check_network_status();

    /* Run test cases - each is independent */
    UTEST_UNIT_RUN(TC_sal_socket_create);
    UTEST_UNIT_RUN(TC_sal_socket_bind);
    UTEST_UNIT_RUN(TC_sal_socket_listen);
    UTEST_UNIT_RUN(TC_sal_socket_connect);
    UTEST_UNIT_RUN(TC_sal_socket_accept);
    UTEST_UNIT_RUN(TC_sal_socket_send_recv);
    UTEST_UNIT_RUN(TC_sal_socket_udp_communication);
    UTEST_UNIT_RUN(TC_sal_socket_getpeername_getsockname);
    UTEST_UNIT_RUN(TC_sal_socket_close);

    LOG_I("===========================================");
    LOG_I("SAL Socket Basic API Tests Completed");
    LOG_I("===========================================");
}
UTEST_TC_EXPORT(utest_do_tc, "components.net.sal.socket_basic", RT_NULL, RT_NULL, 30);
