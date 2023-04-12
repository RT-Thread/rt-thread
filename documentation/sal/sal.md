# Socket Abstraction Layer: SAL

## SAL Introduction

In order to adapt to more network protocol stack types and avoid the system's dependence on a single network protocol stack, the RT-Thread system provides a SAL (Socket Abstraction Layer) components that implement different network protocol stacks or network implementations. The abstraction of the interface provides a set of standard BSD Socket APIs to the upper layer, so that developers only need to care about and use the network interface provided by the network application layer, without concern for the underlying specific network protocol stack type and implementation, which greatly improves the system's compatibility makes it easy for developers to complete protocol stack adaptation and network-related development. Main features of the SAL component are as follows:

- Abstract and unified multiple network protocol stack interfaces;；
- Provide Socket-level TLS encrypted transport feature;
- Support standard BSD Socket APIs；
- Unified FD management for easy operation of network functions using read/write poll/select；

### SAL Network Framework

The SAL network framework of RT-Thread is mainly shown in the following structure:

![SAL 网络框架图](figures/sal_frame.jpg)

The top layer is the network's application layer, provides a set of standard BSD Socket APIs, such as `socket`, `connect` and other functions, for most of the system network development applications.

The second part is the virtual file system layer. In the RT-Thread system, the DFS file system program can implement different file system operations using standard interface functions.The network socket interface also supports the file system structure. The network socket descriptor created when using the network socket interface is uniformly managed by the file system. Therefore, the network socket descriptor can also use the standard file operation interface.The interfaces provided for the upper application layer are: `read`, `write`, `close`, `poll`/`select`, and so on.

The third part is the socket abstraction layer, through which RT-thread system can adapt to different network protocol stacks in the lower layer and provide unified network programming interface in the upper layer to facilitate access of different protocol stacks. The socket abstraction layer provides interfaces for the upper application layer, such as `accept`, `connect`, `send`, `recv`, etc.

The fourth part is the protocol stack layer, which includes several commonly used TCP/IP protocol stacks, such as lwIP, a light TCP/IP protocol stack commonly used in embedded development, and AT Socket network function implementation developed by rt-thread. These protocol stacks or network functions directly contact the hardware to complete the transformation of data from the network layer to the transmission layer.

The network application layer of RT-thread provides interfaces mainly based on the standard BSD Socket API, which ensures that programs can be written on PC, debugged, and then ported to the RT-thread operating system.

### Working Principles

The working principle of SAL component is mainly divided into the following three parts:

- Unified abstract functions of multi-protocol stack access and interface functions；
- SAL TLS encryption transmission function；

#### Multi-Protocol Stack Access and Unified Abstract Function Of Interface Function

For different protocol stacks or network function implementations, the names of network interfaces may be different. Take the `connect` connection function as an example. The interface name in the lwIP protocol stack is `lwip_connect`, and the interface name in the AT Socket network implementation is `at_connect`. The SAL component provides abstraction and unification of the interface of different protocol stacks or networks. When the socket is created, the component **judges the protocol stack or network function used by judging the incoming protocol domain type**, and completes the RT-Thread.

Currently, the protocol stack or network implementation types supported by the SAL component are: **lwIP protocol stack**, **AT Socket protocol stack**, **WIZnet hardware TCP/IP protocol stack**.

```c
int socket(int domain, int type, int protocol);
```

The above is the definition of the socket creation function in the standard BSD Socket API. The `domain` indicates that the protocol domain is also called the protocol domain. It is used to determine which protocol stack or network implementation to use. The domain type used by the AT Socket protocol stack is **AF_AT**, lwIP protocol stack uses protocol domain type **AF_INET**, etc., WIZnet protocol stack uses protocol domain type **AF_WIZ**.

For different software packages, the protocol domain type passed to the socket may be fixed and will not change depending on how the SAL component is accessed. **In order to dynamically adapt access to different protocol stacks or network implementations**, the SAL component provides two protocol domain type matching methods for each protocol stack or network implementation: **Primary protocol domain type and secondary protocol domain type**. When socket is created, it first determines whether the incoming protocol domain type has the supported primary protocol type. If it is, it uses the corresponding protocol stack or network implementation, if not, determine whether the subprotocol cluster type supports. The current system support protocol domain types are as follows:

1.
   lwIP Protocol stack： family = AF_INET、sec_family = AF_INET

2. AT Socket Protocol stack： family = AF_AT、sec_family = AF_INET

3. WIZnet hardware TCP/IP Protocol stack： family = AF_WIZ、sec_family = AF_INET



The main function of the SAL component is to unify the underlying BSD Socket API interface. The following takes the `connect` function call flow as an example to illustrate the SAL component function call method:

- `connect`: The abstract BSD Socket API provided by the SAL component for unified FD management；
- `sal_connect`: The `connect` implementation function in the SAL component that is used to call the `operation` function registered by the underlying stack.。
- `lwip_connect`: The layer `connect` connection function provided by the underlying protocol stack is registered in the SAL component when the NIC is initialized, and the final call operation function。

```c
/* SAL component provides BSD Socket APIs for the application layer  */
int connect(int s, const struct sockaddr *name, socklen_t namelen)
{
    /* Get the SAL socket descriptor */
    int socket = dfs_net_getsocket(s);

    /* Execute the sal_connect function with a SAL socket descriptor*/
    return sal_connect(socket, name, namelen);
}

/* SAL component abstract function interface implementation */
int sal_connect(int socket, const struct sockaddr *name, socklen_t namelen)
{
    struct sal_socket *sock;
    struct sal_proto_family *pf;
    int ret;

    /* Check if the SAL socket structure is normal */
    SAL_SOCKET_OBJ_GET(sock, socket);

    /* Check if the current socket network connection status is normal. */
    SAL_NETDEV_IS_COMMONICABLE(sock->netdev);
    /* Check if the underlying operation function corresponding to the current socket is normal.  */
    SAL_NETDEV_SOCKETOPS_VALID(sock->netdev, pf, connect);

    /* The connect operation function that performs the underlying registration */
    ret = pf->skt_ops->connect((int) sock->user_data, name, namelen);
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

/* The underlying connect function of the lwIP protocol stack function */
int lwip_connect(int socket, const struct sockaddr *name, socklen_t namelen)
{
    ...
}
```

#### SAL TLS Encrypted Transmission Function

**1. SAL TLS Feature**

In the transmission of protocol data such as TCP and UDP, since the data packet is plaintext, it is likely to be intercepted and parsed by others, which has a great impact on the secure transmission of information. In order to solve such problems, users generally need to add the SSL/TLS protocol between the application layer and the transport layer.

TLS (Transport Layer Security) is a protocol based on the transport layer TCP protocol. Its predecessor is SSL (Secure Socket Layer). Its main function is to encrypt the application layer message asymmetrically and then transmit it by TCP protocol, so as to achieve secure data encryption interaction.

Currently used TLS methods: **MbedTLS, OpenSSL, s2n**, etc., but for different encryption methods, you need to use their specified encryption interface and process for encryption, the migration of some application layer protocols is more complicated. Therefore, the SAL TLS function is generated, the main function is to **provide TLS-encrypted transmission characteristics at the Socket level, abstract multiple TLS processing methods, and provide a unified interface for completing TLS data interaction**.

**2. How to use the SAL TLS feature**

The process is as follows:

- Configure to enable any network protocol stack support (such as lwIP protocol stack)；

- Configure to enable the MbedTLS package (currently only supports MbedTLS type encryption)；

- Configure to enable SAL_TLS support (as shown in the configuration options section below)；

After the configuration is complete, as long as the `protocol` type passed in the socket creation uses **PROTOCOL_TLS** or **PROTOCOL_DTLS **, the standard BSD Socket API interface can be used to complete the establishment of the TLS connection and the data transmission and reception. The sample code is as follows:

```c
#include <stdio.h>
#include <string.h>

#include <rtthread.h>
#include <sys/socket.h>
#include <netdb.h>

/* RT-Thread offical website，supporting TLS function */
#define SAL_TLS_HOST    "www.rt-thread.org"
#define SAL_TLS_PORT    443
#define SAL_TLS_BUFSZ   1024

static const char *send_data = "GET /download/rt-thread.txt HTTP/1.1\r\n"
    "Host: www.rt-thread.org\r\n"
    "User-Agent: rtthread/4.0.1 rtt\r\n\r\n";

void sal_tls_test(void)
{
    int ret, i;
    char *recv_data;
    struct hostent *host;
    int sock = -1, bytes_received;
    struct sockaddr_in server_addr;

    /* Get the host address through the function entry parameter url (if it is a domain name, it will do domain name resolution) */
    host = gethostbyname(SAL_TLS_HOST);

    recv_data = rt_calloc(1, SAL_TLS_BUFSZ);
    if (recv_data == RT_NULL)
    {
        rt_kprintf("No memory\n");
        return;
    }

    /* Create a socket of type SOCKET_STREAM, TCP protocol, TLS type */
    if ((sock = socket(AF_INET, SOCK_STREAM, PROTOCOL_TLS)) < 0)
    {
        rt_kprintf("Socket error\n");
        goto __exit;
    }

    /* Initialize the server address */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SAL_TLS_PORT);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        rt_kprintf("Connect fail!\n");
        goto __exit;
    }

    /* Send data to the socket connection */
    ret = send(sock, send_data, strlen(send_data), 0);
    if (ret <= 0)
    {
        rt_kprintf("send error,close the socket.\n");
        goto __exit;
    }

    /* Receive and print the response data, using encrypted data transmission */
    bytes_received = recv(sock, recv_data, SAL_TLS_BUFSZ  - 1, 0);
    if (bytes_received <= 0)
    {
        rt_kprintf("received error,close the socket.\n");
        goto __exit;
    }

    rt_kprintf("recv data:\n");
    for (i = 0; i < bytes_received; i++)
    {
        rt_kprintf("%c", recv_data[i]);
    }

__exit:
    if (recv_data)
        rt_free(recv_data);

    if (sock >= 0)
        closesocket(sock);
}

#ifdef FINSH_USING_MSH
#include <finsh.h>
MSH_CMD_EXPORT(sal_tls_test, SAL TLS function test);
#endif /* FINSH_USING_MSH */
```

### Configuration Options

When we use the SAL component we need to define the following macro definition in rtconfig.h：

|   **Macro definition**   | **Description**                      |
|--------------------------------|--------------------------------|
| RT_USING_SAL  | Enable the SAL function |
| SAL_USING_LWIP  | Enable lwIP stack support |
| SAL_USING_AT | Enable AT Socket protocol stack support |
| SAL_USING_TLS | Enable SAL TLS feature support |
| SAL_USING_POSIX   | Enable POSIX file system related function support, such as read, write, select/poll, etc. |

Currently, the SAL abstraction layer supports the lwIP protocol stack, the AT Socket protocol stack, and the WIZnet hardware TCP/IP protocol stack. To enable SAL in the system, at least one protocol stack support is required.

The above configuration options can be added directly to the `rtconfig.h` file or added by the component package management tool Env configuration option. The specific configuration path in the Env tool is as follows:

```c
RT-Thread Components  --->
    Network  --->
        Socket abstraction layer  --->
        [*] Enable socket abstraction layer
            protocol stack implement --->
            [ ] Support lwIP stack
            [ ] Support AT Commands stack
            [ ] Support MbedTLS protocol
        [*]    Enable BSD socket operated by file system API
```

After the configuration is complete, you can use the `scons` command to regenerate the function and complete the addition of the SAL component.

## Initialization ##

配置开启 SAL 选项之后，需要在启动时对它进行初始化，开启 SAL 功能，如果程序中已经使用了组件自动初始化，则不再需要额外进行单独的初始化，否则需要在初始化任务中调用如下函数：

```c
int sal_init(void);
```

The initialization function is mainly for initializing the SAL component, supporting the component to repeatedly initialize the judgment, and completing the initialization of the resource such as the mutex used in the component. There is no new thread created in the SAL component, which means that the SAL component resource is very small. Currently, the **SAL component resource is occupied by ROM 2.8K and RAM 0.6K**.


## BSD Socket API Introduction ##

The SAL component abstracts the standard BSD Socket API interface. The following is an introduction to common network interfaces:

### Create a Socket (socket)

``` c
int socket(int domain, int type, int protocol);
```

|   **Parameter**   | **Description**                       |
|--------|-------------------------------------|
|  domain  | protocol domain type  |
|   type   | protocol type               |
| protocol | Transport layer protocol for actual use |
|   **back**   | --                                 |
|  >=0  | Success, an integer representing the socket descriptor will be returned |
|    -1    | Fail                              |

This function is used to assign a socket descriptor and the resources it USES based on the specified address family, data type, and protocol.

**domain ( protocol domain type )：**

-   AF_INET： IPv4
-   AF_INET6： IPv6

**type ( protocol type )：**

-   SOCK_STREAM：Stream socket
-   SOCK_DGRAM： Datagram socket
-   SOCK_RAW： Raw socket

### Bind Socket (bind)

```c
int bind(int s, const struct sockaddr *name, socklen_t namelen);
```

|   **P**arameter   | **Description**                               |
|---------|---------------------------------------------|
|     s     | socket descriptor                |
|    name   | a pointer to the sockaddr structure representing the address to bind to |
| namelen | length of sockaddr structure |
|   **back**   | --                                         |
|     0     | success                                   |
|     -1    | fail                                      |

This function is used to bind the port number and IP address to the specified socket。

SAL components depend on the `netdev` components, when using ` bind () ` function, can get  IP address information through the netdev nic name, is used to create Socket bound to the specified object of network interface card. The following example completes the process of binding the IP address of the network interface card and connecting to the server through the name of the incoming network interface card：

```c
#include <rtthread.h>
#include <arpa/inet.h>
#include <netdev.h>

#define SERVER_HOST   "192.168.1.123"
#define SERVER_PORT   1234

static int bing_test(int argc, char **argv)
{
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
    struct netdev *netdev = RT_NULL;
    int sockfd = -1;

    if (argc != 2)
    {
        rt_kprintf("bind_test [netdev_name]  --bind network interface device by name.\n");
        return -RT_ERROR;
    }

    /* Get the netdev network interface card object by name */
    netdev = netdev_get_by_name(argv[1]);
    if (netdev == RT_NULL)
    {
        rt_kprintf("get network interface device(%s) failed.\n", argv[1]);
        return -RT_ERROR;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        rt_kprintf("Socket create failed.\n");
        return -RT_ERROR;
    }

    /* Initializes the client address to bind to */
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(8080);
    /* Gets the IP address information in the network interface card object */
    client_addr.sin_addr.s_addr = netdev->ip_addr.addr;
    rt_memset(&(client_addr.sin_zero), 0, sizeof(client_addr.sin_zero));

    if (bind(sockfd, (struct sockaddr *)&client_addr, sizeof(struct sockaddr)) < 0)
    {
        rt_kprintf("socket bind failed.\n");
        closesocket(sockfd);
        return -RT_ERROR;
    }
    rt_kprintf("socket bind network interface device(%s) success!\n", netdev->name);

    /* Initializes the server address for the pre-connection */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_HOST);
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    /* Connect to the server */
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        rt_kprintf("socket connect failed!\n");
        closesocket(sockfd);
        return -RT_ERROR;
    }
    else
    {
        rt_kprintf("socket connect success!\n");
    }

    /* Close the connection */
    closesocket(sockfd);
    return RT_EOK;
}

#ifdef FINSH_USING_MSH
#include <finsh.h>
MSH_CMD_EXPORT(bing_test, bind network interface device test);
#endif /* FINSH_USING_MSH */
```

### Listen Socket (listen)

```c
int listen(int s, int backlog);
```

|  **Parameter**  | **Description**                 |
|-------|-------------------------------|
|    s    | socket descriptor  |
| backlog | represents the maximum number of connections that can wait at a time |
|  **back**  | --                           |
|    0    | success                    |
|    -1   | fail                     |

This function is used by the TCP server to listen for a specified socket connection。

### Accept Connection (accept)

```c
int accept(int s, struct sockaddr *addr, socklen_t *addrlen);
```

|  **Parameter**  | **Descrption**                 |
|-------|-------------------------------|
|    s    | socket descriptor  |
|   addr  | represents the maximum number of connections that can wait at a time |
| addrlen | length of client device address structure |
|  **back**  | --                           |
|    0    | success, return the newly created socket descriptor |
|    -1   | fail                        |

When the application listens for connections from other hosts, the connection is initialized with the `accept()` function, and `accept()` creates a new socket for each connection and removes the connection from the listen queue.

### Establish Connection (connect)

```c
int connect(int s, const struct sockaddr *name, socklen_t namelen);
```

|  **Parameter**  | **Description** |
|-------|-------------------------------|
|    s    | socket descriptor  |
|   name  | server address information |
| namelen | server address structure length |
|  **back**  | --                    |
|    0    | successful, return the newly created socket descriptor |
|    -1   | fail                 |

This function is used to establish a connection to the specified socket.

### Send TCP Data (send)

```c
int send(int s, const void *dataptr, size_t size, int flags);
```

|  **Parameter**  | **Description**             |
|-------|---------------------------|
|    s    | socket descriptor |
| dataptr | sent data pointer |
|   size  | length of sent data |
|  flags  | flags, usually 0 |
|  **back**  | --                       |
|  >0  | success, the length of the sent data  is returned |
|  <=0 | Fail                    |

This function is commonly used to send data over a TCP connection。

### Receive TCP Data (recv)

```c
int recv(int s, void *mem, size_t len, int flags);
```

| **Parameter** | **Description**             |
|-----|---------------------------|
|   s   | socket descriptor |
|  mem  | received data pointer |
|  len  | length of received data |
| flags | flags, usually 0 |
| **back** | --                       |
| >0 | success, the length of the received data will be returned |
|   =0  | the destination address has been transmitted and the connection is closed |
| <0 | fail                                                         |

This function is used to receive data over a TCP connection。

### Send UDP Data (sendto)

```c
int sendto(int s, const void *dataptr, size_t size, int flags, const struct sockaddr *to, socklen_t tolen);
```

|  **Parameter**  | **Description**            |
|-------|---------------------------|
|    s    | socket descriptor |
| dataptr | sent data pointer |
|   size  | length of sent data |
|  flags  | flags, usually 0 |
|    to   | target address structure pointer |
|  tolen  | length of the target address structure |
| **return** | --                       |
|  >0  | success, the length of the received data will be returned |
|  <=0 | fail                    |

This function is used for UDP connections to send data。

### Receive  UDP Data (recvfrom)

```c
int recvfrom(int s, void *mem, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen);
```

|  **Parameter**  | **Description**           |
|-------|---------------------------|
|    s    | socket descriptor |
|   mem   | received data pointer |
|   len   | length of data received |
|  flags  | flags, usually 0 |
|   from  | received address structure pointer |
| fromlen | length of received address structure |
|  **back**  | --                       |
|  >0  | success, return the length of the received data |
|    =0   | the receiving address has been transferred and the connection is closed |
|  <0  | fail                    |

This function is used to receive data on a UDP connection。

### Close Socket (closesocket）

```c
int closesocket(int s);
```

| **Parameter** | **Description** |
|----|-------------|
|   s  | Socket descriptor |
| **back** | --         |
|   0  | success   |
|  -1  | fail      |

This function is used to close the connection and release the resource.。

### Shutdown The Socket By Setting（shutdown）

```c
int shutdown(int s, int how);
```

| **Parameter** | **Descrption**    |
|----|-----------------|
|   s  | socket descriptor |
|  how | socket control |
| **back** | --             |
|   0  | fail          |
|  -1  | success       |

This function provides more permissions to control the closing process of the socket.。

**How ( socket control )：**

-   0： Stop receiving current data and reject future data reception；
-   1： Stop sending data and discard unsent data；
-   2： Stop receiving and sending data。

### Set Socket Options（setsockopt）

```c
int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
```

|  **Parameter**  | **Description**         |
|-------|-----------------------|
|    s    | socket descriptor |
|  level  | protocol stack configuration options |
| optname | option name to be set |
|  optval | set the buffer address of the option value |
|  optlen | set the buffer length of the option value |
|  **back**  | --                   |
|    =0   | success             |
|  <0  | fail                |

This function is used to set the socket mode and modify the socket configuration options.。

**level ( protocol stack configuration options )：**

-   SOL_SOCKET：Socket layer
-   IPPROTO_TCP：TCP layer
-   IPPROTO_IP：IP layer

**optname ( Option name to be set ):**

-   SO_KEEPALIVE：Set keep alive options
-   SO_RCVTIMEO：Set socket data reception timeout
-   SO_SNDTIMEO：Set socket data sending timeout

### Get Socket Options（getsockopt）

```c
int getsockopt(int s, int level, int optname, void *optval, socklen_t *optlen);
```

|  **Parameter**  | **Description**             |
|-------|---------------------------|
|    s    | socket descriptor |
|  level  | protocol stack configuration options |
| optname | option name to be set |
|  optval | get the buffer address of the option value |
|  optlen | get the buffer length address of the option value |
|  **back**  | --                       |
|    =0   | success               |
|  <0  | fail                    |

This function is used to get the socket configuration options。

### Get Remote Address Information (getpeername)

```c
int getpeername(int s, struct sockaddr *name, socklen_t *namelen);
```

|  **Parameter**  | **Description**          |
|-------|-------------------------|
|    s    | socket descriptor |
|   name  | received address structure pointer |
| namelen | length of received address structure |
|  **back**  | --                     |
|    =0   | success               |
|  <0  | fail                  |

This function is used to get the remote address information associated with the socket。

### Get Local Address Information (getsockname)

```c
int getsockname(int s, struct sockaddr *name, socklen_t *namelen);
```

|  **Parameter**  | **Description**           |
|-------|-------------------------|
|    s    | Socket descriptor |
|   name  | received address structure pointer |
| namelen | length of received address structure |
|  **back**  | --                     |
|    =0   | success               |
|  <0  | fail                  |

This function is used to get local socket address information。

### Configure Socket Parameters (ioctlsocket)）

```c
int ioctlsocket(int s, long cmd, void *arg);
```

| **Parameter** | **Description**   |
|-----|-----------------|
|   s   | socket descriptor |
|  cmd  | socket operation command |
|  arg  | operation command's parameters |
| **back** | --             |
|   =0  | success      |
| <0 | fail          |

This function sets the socket control mode。

**The CMD supports following commands**

-   FIONBIO: Turns on or off the socket's non-blocking mode. Arg parameter 1 is open non-blocking and 0 is closed non-blocking.

## Network Protocol Stack Access

Access to the network protocol stack or network function implementation is mainly to initialize and register the protocol cluster structure, and add it to the protocol cluster list in SAL component. The protocol cluster structure is defined as follows：

```c
/* network interface socket opreations */
struct sal_socket_ops
{
    int (*socket)     (int domain, int type, int protocol);
    int (*closesocket)(int s);
    int (*bind)       (int s, const struct sockaddr *name, socklen_t namelen);
    int (*listen)     (int s, int backlog);
    int (*connect)    (int s, const struct sockaddr *name, socklen_t namelen);
    int (*accept)     (int s, struct sockaddr *addr, socklen_t *addrlen);
    int (*sendto)     (int s, const void *data, size_t size, int flags, const struct sockaddr *to, socklen_t tolen);
    int (*recvfrom)   (int s, void *mem, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen);
    int (*getsockopt) (int s, int level, int optname, void *optval, socklen_t *optlen);
    int (*setsockopt) (int s, int level, int optname, const void *optval, socklen_t optlen);
    int (*shutdown)   (int s, int how);
    int (*getpeername)(int s, struct sockaddr *name, socklen_t *namelen);
    int (*getsockname)(int s, struct sockaddr *name, socklen_t *namelen);
    int (*ioctlsocket)(int s, long cmd, void *arg);
#ifdef SAL_USING_POSIX
    int (*poll)       (struct dfs_file *file, struct rt_pollreq *req);
#endif
};

/* sal network database name resolving */
struct sal_netdb_ops
{
    struct hostent* (*gethostbyname)  (const char *name);
    int             (*gethostbyname_r)(const char *name, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop);
    int             (*getaddrinfo)    (const char *nodename, const char *servname, const struct addrinfo *hints, struct addrinfo **res);
    void            (*freeaddrinfo)   (struct addrinfo *ai);
};

/* Protocol domain structure definition */
struct sal_proto_family
{
    int family;                                  /* primary protocol families type */
    int sec_family;                              /* secondary protocol families type */
    const struct sal_socket_ops *skt_ops;        /* socket opreations */
    const struct sal_netdb_ops *netdb_ops;       /* network database opreations */
};

```

- `family`： Each protocol stack supports the main protocol cluster types, such as AF_INET for lwIP, AF_AT Socket, and AF_WIZ for WIZnet。
- `sec_family`：The type of sub-protocol domain supported by each protocol stack, used to support a single protocol stack or network implementation, that matches other types of protocol cluster types in the package。
- `skt_ops`： Define socket related functions, such as connect, send, recv, etc., each protocol cluster has a different set of implementation。
- `netdb_ops`：Define non-socket-related execution functions, such as `gethostbyname`, `getaddrinfo`, `freeaddrinfo`, etc. Each protocol cluster has a different set of implementations。

The following is the access registration process implemented by AT Socket network. Developers can refer to other protocol stacks or network implementations for access:

```c
#include <rtthread.h>
#include <netdb.h>
#include <sal_low_lvl.h>            /* SAL component structure holds the header file */
#include <at_socket.h>      /* AT Socket related header file */
#include <af_inet.h>

#include <netdev.h>         /*network interface card function related header file */

#ifdef SAL_USING_POSIX
#include <dfs_poll.h>       /* Poll function related header file */
#endif

#ifdef SAL_USING_AT

/* A custom poll execution function that handles the events received in the poll */
static int at_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    int mask = 0;
    struct at_socket *sock;
    struct socket *sal_sock;

    sal_sock = sal_get_socket((int) file->data);
    if(!sal_sock)
    {
        return -1;
    }

    sock = at_get_socket((int)sal_sock->user_data);
    if (sock != NULL)
    {
        rt_base_t level;

        rt_poll_add(&sock->wait_head, req);

        level = rt_hw_interrupt_disable();
        if (sock->rcvevent)
        {
            mask |= POLLIN;
        }
        if (sock->sendevent)
        {
            mask |= POLLOUT;
        }
        if (sock->errevent)
        {
            mask |= POLLERR;
        }
        rt_hw_interrupt_enable(level);
    }

    return mask;
}
#endif

/* Define and assign socket execution functions, and the SAL component calls the underlying function of the registration when it executes relevant functions */
static const struct proto_ops at_inet_stream_ops =
{
    at_socket,
    at_closesocket,
    at_bind,
    NULL,
    at_connect,
    NULL,
    at_sendto,
    at_recvfrom,
    at_getsockopt,
    at_setsockopt,
    at_shutdown,
    NULL,
    NULL,
    NULL,

#ifdef SAL_USING_POSIX
    at_poll,
#else
    NULL,
#endif /* SAL_USING_POSIX */
};

static const struct sal_netdb_ops at_netdb_ops =
{
    at_gethostbyname,
    NULL,
    at_getaddrinfo,
    at_freeaddrinfo,
};

/* define and assign AT Socket protocol domain structure */
static const struct sal_proto_family at_inet_family =
{
    AF_AT,
    AF_INET,
    &at_socket_ops,
    &at_netdb_ops,
};

/* Used to set the protocol domain information in the network interface card device */
int sal_at_netdev_set_pf_info(struct netdev *netdev)
{
    RT_ASSERT(netdev);

    netdev->sal_user_data = (void *) &at_inet_family;
    return 0;
}

#endif /* SAL_USING_AT */
```
