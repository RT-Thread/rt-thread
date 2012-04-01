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
#define PING_RCV_TIMEO 1000
/** ping delay - in milliseconds */
#define PING_DELAY     100

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
static err_t ping_send(int s, struct ip_addr *addr)
{
	int err;
	struct icmp_echo_hdr *iecho;
	struct sockaddr_in to;
	size_t ping_size = sizeof(struct icmp_echo_hdr) + PING_DATA_SIZE;
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

	return (err ? ERR_OK : ERR_VAL);
}

static void ping_recv(int s)
{
	char buf[64];
	int fromlen, len;
	struct sockaddr_in from;
	struct ip_hdr *iphdr;
	struct icmp_echo_hdr *iecho;
	struct _ip_addr *addr;

	while((len = lwip_recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&from, (socklen_t*)&fromlen)) > 0)
	{
		if (len >= (sizeof(struct ip_hdr)+sizeof(struct icmp_echo_hdr)))
		{
			addr = (struct _ip_addr *)&(from.sin_addr);
			rt_kprintf("ping: recv %d.%d.%d.%d\n", addr->addr0, addr->addr1, addr->addr2, addr->addr3);

			iphdr = (struct ip_hdr *)buf;
			iecho = (struct icmp_echo_hdr *)(buf+(IPH_HL(iphdr) * 4));
			if ((iecho->id == PING_ID) && (iecho->seqno == htons(ping_seq_num)))
			{
				return;
			}
			else
			{
				rt_kprintf("ping: drop\n");
			}
		}
	}

	if (len <= 0)
	{
		rt_kprintf("ping: timeout\n");
	}
}

rt_err_t ping(char* target, rt_uint32_t time, rt_size_t size)
{
	int s;
	int timeout = PING_RCV_TIMEO;
	struct ip_addr ping_target;
	rt_uint32_t send_time;
	struct _ip_addr
	{
		rt_uint8_t addr0, addr1, addr2, addr3;
	} *addr;

    send_time = 0;

	if (inet_aton(target, (struct in_addr*)&ping_target) == 0) return -RT_ERROR;
	addr = (struct _ip_addr*)&ping_target;

	if ((s = lwip_socket(AF_INET, SOCK_RAW, IP_PROTO_ICMP)) < 0)
	{
	    rt_kprintf("create socket failled\n");
		return -RT_ERROR;
	}

	lwip_setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

	while (1)
	{
		if (ping_send(s, &ping_target) == ERR_OK)
		{
			rt_kprintf("ping: send %d.%d.%d.%d\n", addr->addr0, addr->addr1, addr->addr2, addr->addr3);
			ping_recv(s);
		}
		else
		{
			rt_kprintf("ping: send %d.%d.%d.%d - error\n", addr->addr0, addr->addr1, addr->addr2, addr->addr3);
		}

		send_time ++;
		if (send_time >= time) break; /* send ping times reached, stop */

		rt_thread_delay(PING_DELAY); /* take a delay */
	}

	return RT_EOK;
}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(ping, ping network host);
#endif
