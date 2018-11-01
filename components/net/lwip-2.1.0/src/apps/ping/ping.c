/*
 * netutils: ping implementation
 */

#include "lwip/opt.h"

#include "lwip/mem.h"
#include "lwip/icmp.h"
#include "lwip/netif.h"
#include "lwip/sys.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"
#include "lwip/inet_chksum.h"
#include "lwip/ip.h"

/**
 * PING_DEBUG: Enable debugging for PING.
 */
#ifndef PING_DEBUG
#define PING_DEBUG     LWIP_DBG_ON
#endif

/** ping receive timeout - in milliseconds */
#define PING_RCV_TIMEO rt_tick_from_millisecond(2000)
/** ping delay - in milliseconds */
#define PING_DELAY     rt_tick_from_millisecond(1000)

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
    for(i = 0; i < data_len; i++)
    {
        ((char*)iecho)[sizeof(struct icmp_echo_hdr) + i] = (char)i;
    }

    iecho->chksum = inet_chksum(iecho, len);
}

/* Ping using the socket ip */
static err_t ping_send(int s, ip_addr_t *addr, int size)
{
    int err;
    struct icmp_echo_hdr *iecho;
    struct sockaddr_in to;
    size_t ping_size = sizeof(struct icmp_echo_hdr) + size;
    LWIP_ASSERT("ping_size is too big", ping_size <= 0xffff);

    iecho = rt_malloc(ping_size);
    if (iecho == RT_NULL)
    {
        return ERR_MEM;
    }

    ping_prepare_echo(iecho, (u16_t)ping_size);

    to.sin_len = sizeof(to);
    to.sin_family = AF_INET;
    to.sin_addr.s_addr = addr->addr;

    err = lwip_sendto(s, iecho, ping_size, 0, (struct sockaddr*)&to, sizeof(to));
    rt_free(iecho);

    return (err == ping_size ? ERR_OK : ERR_VAL);
}

static int ping_recv(int s, int *ttl)
{
    char buf[64];
    int fromlen = sizeof(struct sockaddr_in), len;
    struct sockaddr_in from;
    struct ip_hdr *iphdr;
    struct icmp_echo_hdr *iecho;

    while((len = lwip_recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&from, (socklen_t*)&fromlen)) > 0)
    {
        if (len >= (sizeof(struct ip_hdr)+sizeof(struct icmp_echo_hdr)))
        {
            iphdr = (struct ip_hdr *)buf;
            iecho = (struct icmp_echo_hdr *)(buf+(IPH_HL(iphdr) * 4));
            if ((iecho->id == PING_ID) && (iecho->seqno == htons(ping_seq_num)))
            {
                *ttl = iphdr->_ttl;
                return len;
            }
        }
    }

    return len;
}

rt_err_t ping(char* target, rt_uint32_t times, rt_size_t size)
{
    int s, ttl, recv_len;
    struct timeval timeout = { PING_RCV_TIMEO / RT_TICK_PER_SECOND, PING_RCV_TIMEO % RT_TICK_PER_SECOND };
    ip_addr_t ping_target;
    rt_uint32_t send_times;
    rt_tick_t recv_start_tick;
    struct _ip_addr
    {
        rt_uint8_t addr0, addr1, addr2, addr3;
    } *addr;

    send_times = 0;
    ping_seq_num = 0;

    if(size == 0)
        size = PING_DATA_SIZE;

    if (inet_aton(target, &ping_target) == 0)
    {
        rt_kprintf("ping: unknown host %s\n", target);
        return -RT_ERROR;
    }
    addr = (struct _ip_addr*)&ping_target;

    if ((s = lwip_socket(AF_INET, SOCK_RAW, IP_PROTO_ICMP)) < 0)
    {
        rt_kprintf("ping: create socket failled\n");
        return -RT_ERROR;
    }

    lwip_setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(struct timeval));

    while (1)
    {
        if (ping_send(s, &ping_target, size) == ERR_OK)
        {
            recv_start_tick = rt_tick_get();
            if ((recv_len = ping_recv(s, &ttl)) >= 0)
            {
                rt_kprintf("%d bytes from %d.%d.%d.%d icmp_seq=%d ttl=%d time=%d ticks\n", recv_len, addr->addr0,
                        addr->addr1, addr->addr2, addr->addr3, send_times, ttl, rt_tick_get() - recv_start_tick);
            }
            else
            {
                rt_kprintf("From %d.%d.%d.%d icmp_seq=%d timeout\n", addr->addr0, addr->addr1, addr->addr2,
                        addr->addr3, send_times);
            }
        }
        else
        {
            rt_kprintf("Send %d.%d.%d.%d - error\n", addr->addr0, addr->addr1, addr->addr2, addr->addr3);
        }

        send_times ++;
        if (send_times >= times) break; /* send ping times reached, stop */

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
FINSH_FUNCTION_EXPORT_ALIAS(cmd_ping, __cmd_ping, ping network host);
#endif
