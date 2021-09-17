/*
 * netutils: ping implementation
 */

#include <rtthread.h>

#ifdef RT_LWIP_ICMP    /* don't build if not configured for use in rtconfig.h */
#include <lwip/opt.h>
#include <lwip/init.h>
#include <lwip/mem.h>
#include <lwip/icmp.h>
#include <lwip/netif.h>
#include <lwip/sys.h>
#include <lwip/inet.h>
#include <lwip/inet_chksum.h>
#include <lwip/ip.h>
#include <lwip/netdb.h>
#include <lwip/sockets.h>

/**
 * PING_DEBUG: Enable debugging for PING.
 */
#ifndef PING_DEBUG
#define PING_DEBUG     LWIP_DBG_ON
#endif

/** ping receive timeout - in milliseconds */
#define PING_RCV_TIMEO (2 * RT_TICK_PER_SECOND)
/** ping delay - in milliseconds */
#define PING_DELAY     (1 * RT_TICK_PER_SECOND)

/** ping identifier - must fit on a u16_t */
#ifndef PING_ID
#define PING_ID        0xAFAF
#endif

/** ping additional data size to include in the packet */
#ifndef PING_DATA_SIZE
#define PING_DATA_SIZE 32
#endif

/* ping variables */
static u16_t ping_seq_num;
struct _ip_addr
{
    rt_uint8_t addr0, addr1, addr2, addr3;
};

/** Prepare a echo ICMP request */
static void ping_prepare_echo( struct icmp_echo_hdr *iecho, u16_t len)
{
    size_t i;
    size_t data_len = len - sizeof(struct icmp_echo_hdr);

    ICMPH_TYPE_SET(iecho, ICMP_ECHO);
    ICMPH_CODE_SET(iecho, 0);
    iecho->chksum = 0;
    iecho->id     = PING_ID;
    iecho->seqno  = htons(++ping_seq_num);

    /* fill the additional data buffer with some data */
    for (i = 0; i < data_len; i++)
    {
        ((char*) iecho)[sizeof(struct icmp_echo_hdr) + i] = (char) i;
    }

#ifdef RT_LWIP_USING_HW_CHECKSUM
      iecho->chksum = 0;
#else
      iecho->chksum = inet_chksum(iecho, len);
#endif

}

/* Ping using the socket ip */
err_t lwip_ping_send(int s, ip_addr_t *addr, int size)
{
    int err;
    struct icmp_echo_hdr *iecho;
    struct sockaddr_in to;
    int ping_size = sizeof(struct icmp_echo_hdr) + size;
    LWIP_ASSERT("ping_size is too big", ping_size <= 0xffff);

    iecho = rt_malloc(ping_size);
    if (iecho == RT_NULL)
    {
        return ERR_MEM;
    }

    ping_prepare_echo(iecho, (u16_t) ping_size);

    to.sin_len = sizeof(to);
    to.sin_family = AF_INET;
#if LWIP_IPV4 && LWIP_IPV6
    to.sin_addr.s_addr = addr->u_addr.ip4.addr;
#elif LWIP_IPV4
    to.sin_addr.s_addr = addr->addr;
#elif LWIP_IPV6
#error Not supported IPv6.
#endif

    err = lwip_sendto(s, iecho, ping_size, 0, (struct sockaddr*) &to, sizeof(to));
    rt_free(iecho);

    return (err == ping_size ? ERR_OK : ERR_VAL);
}

int lwip_ping_recv(int s, int *ttl)
{
    char buf[64];
    int fromlen = sizeof(struct sockaddr_in), len;
    struct sockaddr_in from;
    struct ip_hdr *iphdr;
    struct icmp_echo_hdr *iecho;

    while ((len = lwip_recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*) &from, (socklen_t*) &fromlen)) > 0)
    {
        if (len >= (int)(sizeof(struct ip_hdr) + sizeof(struct icmp_echo_hdr)))
        {
            iphdr = (struct ip_hdr *) buf;
            iecho = (struct icmp_echo_hdr *) (buf + (IPH_HL(iphdr) * 4));
            if ((iecho->id == PING_ID) && (iecho->seqno == htons(ping_seq_num)))
            {
                *ttl = iphdr->_ttl;
                return len;
            }
        }
    }

    return len;
}

#ifndef RT_USING_NETDEV

/* using the lwIP custom ping */
rt_err_t ping(char* target_name, rt_uint32_t times, rt_size_t size)
{
#if LWIP_VERSION_MAJOR >= 2U
    struct timeval timeout = { PING_RCV_TIMEO / RT_TICK_PER_SECOND, PING_RCV_TIMEO % RT_TICK_PER_SECOND };
#else
    int timeout = PING_RCV_TIMEO * 1000UL / RT_TICK_PER_SECOND;
#endif

    int s, ttl, recv_len;
    ip_addr_t target_addr;
    rt_uint32_t send_times;
    rt_tick_t recv_start_tick;
    struct addrinfo hint, *res = NULL;
    struct sockaddr_in *h = NULL;
    struct in_addr ina;

    send_times = 0;
    ping_seq_num = 0;

    if (size == 0)
    {
        size = PING_DATA_SIZE;
    }

    memset(&hint, 0, sizeof(hint));
    /* convert URL to IP */
    if (lwip_getaddrinfo(target_name, NULL, &hint, &res) != 0)
    {
        rt_kprintf("ping: unknown host %s\n", target_name);
        return -RT_ERROR;
    }
    memcpy(&h, &res->ai_addr, sizeof(struct sockaddr_in *));
    memcpy(&ina, &h->sin_addr, sizeof(ina));
    lwip_freeaddrinfo(res);
    if (inet_aton(inet_ntoa(ina), &target_addr) == 0)
    {
        rt_kprintf("ping: unknown host %s\n", target_name);
        return -RT_ERROR;
    }
    /* new a socket */
    if ((s = lwip_socket(AF_INET, SOCK_RAW, IP_PROTO_ICMP)) < 0)
    {
        rt_kprintf("ping: create socket failed\n");
        return -RT_ERROR;
    }

    lwip_setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    while (1)
    {
        int elapsed_time;

        if (lwip_ping_send(s, &target_addr, size) == ERR_OK)
        {
            recv_start_tick = rt_tick_get();
            if ((recv_len = lwip_ping_recv(s, &ttl)) >= 0)
            {
                elapsed_time = (rt_tick_get() - recv_start_tick) * 1000UL / RT_TICK_PER_SECOND;
                rt_kprintf("%d bytes from %s icmp_seq=%d ttl=%d time=%d ms\n", recv_len, inet_ntoa(ina), send_times,
                        ttl, elapsed_time);
            }
            else
            {
                rt_kprintf("From %s icmp_seq=%d timeout\n", inet_ntoa(ina), send_times);
            }
        }
        else
        {
            rt_kprintf("Send %s - error\n", inet_ntoa(ina));
        }

        send_times++;
        if (send_times >= times)
        {
            /* send ping times reached, stop */
            break;
        }

        rt_thread_delay(PING_DELAY); /* take a delay */
    }

    lwip_close(s);

    return RT_EOK;
}
#ifdef RT_USING_FINSH
#include <finsh.h>

FINSH_FUNCTION_EXPORT(ping, ping network host);

int cmd_ping(int argc, char **argv)
{
    if (argc == 1)
    {
        rt_kprintf("Please input: ping <host address>\n");
    }
    else
    {
        ping(argv[1], 4, 0);
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_ping, ping, ping network host);
#endif /* RT_USING_FINSH */

#endif /* RT_USING_NETDEV */

#endif /* RT_LWIP_ICMP */

