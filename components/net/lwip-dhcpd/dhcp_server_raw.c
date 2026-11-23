/*
 * File      : dhcp_server_raw.c
 *             A simple DHCP server implementation
 * COPYRIGHT (C) 2011-2023, Shanghai Real-Thread Technology Co., Ltd
 * http://www.rt-thread.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-04-01     Ren.Haibo    the first version
 * 2018-06-12     aozima       ignore DHCP_OPTION_SERVER_ID.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <rtthread.h>

#include <lwip/opt.h>
#include <lwip/sockets.h>
#include <lwip/inet_chksum.h>
#include <netif/etharp.h>
#include <netif/ethernetif.h>
#include <lwip/ip.h>
#include <lwip/init.h>
#include <lwip/sys.h>
#include <lwip/timeouts.h>
#include <lwip/tcpip.h>

#if (LWIP_VERSION) < 0x02000000U
// cppcheck-suppress preprocessorErrorDirective
#error "not support old LWIP"
#endif

#if !LWIP_IPV4
#error "must enable IPV4"
#endif

#if (LWIP_VERSION) >= 0x02000000U
#include <lwip/prot/dhcp.h>
#endif

/* DHCP server option */

/* allocated client ip range */
#ifndef DHCPD_CLIENT_IP_MIN
#define DHCPD_CLIENT_IP_MIN 2
#endif
#ifndef DHCPD_CLIENT_IP_MAX
#define DHCPD_CLIENT_IP_MAX 254
#endif

/* the DHCP server address */
#ifndef DHCPD_SERVER_IP
#define DHCPD_SERVER_IP "192.168.169.1"
#endif

#define DHCP_DEBUG_PRINTF

#ifdef DHCP_DEBUG_PRINTF
#define DEBUG_PRINTF       \
    rt_kprintf("[DHCP] "); \
    rt_kprintf
#else
#define DEBUG_PRINTF(...)
#endif /* DHCP_DEBUG_PRINTF */

/* we need some routines in the DHCP of lwIP */
#undef LWIP_DHCP
#define LWIP_DHCP 1
#include <lwip/dhcp.h>

/** Mac address length  */
#define DHCP_MAX_HLEN 6
/** dhcp default lease time in seconds */
#define DHCP_DEFAULT_LIVE_TIME 86400
/** dhcp default lease time in milliseconds */
#define DHCP_DEFAULT_LEASE_TIME_MS (DHCP_DEFAULT_LIVE_TIME * 1000U)

/** Minimum length for request before packet is parsed */
#define DHCP_MIN_REQUEST_LEN 44

/* How often the TCP/IP thread scans all servers for expired leases. */
#ifndef DHCPD_RECYCLE_INTERVAL_MS
#define DHCPD_RECYCLE_INTERVAL_MS 60000
#endif

#ifndef DHCP_SERVER_PORT
#define DHCP_SERVER_PORT 67
#endif

/**
* The dhcp client node struct.
*/
struct dhcp_client_node
{
    struct dhcp_client_node *next;
    u8_t chaddr[DHCP_MAX_HLEN];
    ip4_addr_t ipaddr;
    u32_t lease_end; /* lease expiry in sys_now() milliseconds */
};

/**
* The dhcp server struct.
*/
struct dhcp_server
{
    struct dhcp_server *next;
    struct netif *netif;
    struct udp_pcb *pcb;
    struct dhcp_client_node *node_list;
    ip4_addr_t start;
    ip4_addr_t end;
    ip4_addr_t current;
};

static u8_t *dhcp_server_option_find(u8_t *buf, u16_t len, u8_t option);

/**
* The dhcp server struct list.
*/
static struct dhcp_server *lw_dhcp_server;

/**
* Find a dhcp client node by mac address
*
* @param dhcpserver The dhcp server
* @param chaddr Mac address
* @param hlen   Mac address length
* @return dhcp client node
*/
static struct dhcp_client_node *
dhcp_client_find_by_mac(struct dhcp_server *dhcpserver, const u8_t *chaddr, u8_t hlen)
{
    struct dhcp_client_node *node;

    /*
     * Leases are stored as full Ethernet addresses. Comparing only hlen bytes
     * would let a client with a shorter (e.g. one byte) hardware address claim
     * the lease of any node that shares that prefix.
     */
    if (hlen != DHCP_MAX_HLEN)
    {
        return NULL;
    }

    for (node = dhcpserver->node_list; node != NULL; node = node->next)
    {
        if (memcmp(node->chaddr, chaddr, DHCP_MAX_HLEN) == 0)
        {
            return node;
        }
    }

    return NULL;
}

/**
* Find a dhcp client node by ip address
*
* @param dhcpserver The dhcp server
* @param ip IP address
* @return dhcp client node
*/
static struct dhcp_client_node *
dhcp_client_find_by_ip(struct dhcp_server *dhcpserver, const ip4_addr_t *ip)
{
    struct dhcp_client_node *node;

    for (node = dhcpserver->node_list; node != NULL; node = node->next)
    {
        if (ip4_addr_cmp(&node->ipaddr, ip))
        {
            return node;
        }
    }

    return NULL;
}

/**
* Check whether a dhcp client lease has expired.
*
* @param node The dhcp client node
* @return 1 if expired, 0 otherwise
*/
static rt_bool_t dhcp_client_lease_expired(const struct dhcp_client_node *node)
{
    u32_t lease_start = node->lease_end - DHCP_DEFAULT_LEASE_TIME_MS;

    /* Unsigned elapsed check avoids the ~24.8-day signed half-range false negative. */
    return (u32_t)(sys_now() - lease_start) >= DHCP_DEFAULT_LEASE_TIME_MS;
}

/**
* Renew the lease of a dhcp client node.
*
* @param node The dhcp client node
*/
static void dhcp_client_lease_renew(struct dhcp_client_node *node)
{
    node->lease_end = sys_now() + DHCP_DEFAULT_LEASE_TIME_MS;
}

/**
* Remove expired dhcp client nodes from the list.
*
* @param dhcpserver The dhcp server
*/
static void dhcp_client_remove_expired(struct dhcp_server *dhcpserver)
{
    struct dhcp_client_node *node = dhcpserver->node_list;
    struct dhcp_client_node *prev = NULL;
    struct dhcp_client_node *next;

    while (node != NULL)
    {
        next = node->next;

        if (dhcp_client_lease_expired(node))
        {
            if (prev == NULL)
            {
                dhcpserver->node_list = next;
            }
            else
            {
                prev->next = next;
            }
            mem_free(node);
        }
        else
        {
            prev = node;
        }
        node = next;
    }
}

/**
* Tell whether a received frame is a DHCP request this server can serve.
*
* The server only serves Ethernet clients. A hardware address length other
* than 6 cannot be matched against the stored leases, so such a request is
* dropped at the entry instead of being compared byte by byte.
*
* @param msg The dhcp message
* @return 1 if the message may be handled, 0 otherwise
*/
static rt_bool_t dhcp_msg_usable(const struct dhcp_msg *msg)
{
    return msg->op == DHCP_BOOTREQUEST &&
           msg->cookie == PP_HTONL(DHCP_MAGIC_COOKIE) &&
           msg->hlen == DHCP_MAX_HLEN;
}

/**
* Tell whether a lease node belongs to the client of the dhcp message.
*
* @param node The dhcp client node
* @param msg The dhcp message
* @return 1 if the stored lease belongs to that client, 0 otherwise
*/
static rt_bool_t dhcp_chaddr_equal(const struct dhcp_client_node *node,
                                   const struct dhcp_msg *msg)
{
    return msg->hlen == DHCP_MAX_HLEN &&
           memcmp(node->chaddr, msg->chaddr, DHCP_MAX_HLEN) == 0;
}

/**
* Find a dhcp client node by dhcp message
*
* @param dhcpserver is the dhcp server
* @param msg is the dhcp message
* @param opt_buf is the optional buffer
* @param len is the buffer length
* @return dhcp client node
*/
static struct dhcp_client_node *
dhcp_client_find(struct dhcp_server *dhcpserver, struct dhcp_msg *msg,
                 u8_t *opt_buf, u16_t len)
{
    struct dhcp_client_node *node;

    LWIP_UNUSED_ARG(opt_buf);
    LWIP_UNUSED_ARG(len);

    if (!dhcp_msg_usable(msg))
    {
        return NULL;
    }

    node = dhcp_client_find_by_mac(dhcpserver, msg->chaddr, msg->hlen);
    if (node != NULL)
    {
        return node;
    }

    /*
     * A REQUESTED_IP lookup cannot grant anything here: the MAC scan above
     * covered the whole list, so a node at the requested IP belongs to a
     * different client.
     */
    return NULL;
}

/**
* Allocate a dhcp client node by dhcp message
*
* @param dhcpserver is the dhcp server
* @param msg is the dhcp message
* @param opt_buf is the optional buffer
* @param len is the buffer length
* @return dhcp client node
*/
static struct dhcp_client_node *
dhcp_client_alloc(struct dhcp_server *dhcpserver, struct dhcp_msg *msg,
                  u8_t *opt_buf, u16_t len)
{
    u32_t ipaddr;
    u32_t first_candidate;
    struct dhcp_client_node *node;

    LWIP_UNUSED_ARG(opt_buf);
    LWIP_UNUSED_ARG(len);

    if (!dhcp_msg_usable(msg))
    {
        return NULL;
    }

    node = dhcp_client_find_by_mac(dhcpserver, msg->chaddr, msg->hlen);
    if (node != NULL)
    {
        dhcp_client_lease_renew(node);
        return node;
    }

    /* keep the current client's node, reclaim expired nodes of other clients */
    dhcp_client_remove_expired(dhcpserver);

    /*
     * The requested IP was already looked up by MAC above.  If it is in use,
     * the ownership check there rejected it; the pool walk below only skips
     * addresses that are still leased, so a foreign REQUESTED_IP can never be
     * handed to the requester.
     */

    /* Check each pool address at most once. */
    first_candidate = dhcpserver->current.addr;
    do
    {
        node = dhcp_client_find_by_ip(dhcpserver, &dhcpserver->current);
        if (node == NULL)
        {
            break;
        }

        ipaddr = (ntohl(dhcpserver->current.addr) + 1);
        if (ipaddr > ntohl(dhcpserver->end.addr))
        {
            ipaddr = ntohl(dhcpserver->start.addr);
        }
        dhcpserver->current.addr = htonl(ipaddr);
    } while (dhcpserver->current.addr != first_candidate);

    if (node != NULL)
    {
        return NULL;
    }

    node = (struct dhcp_client_node *)mem_malloc(sizeof(struct dhcp_client_node));
    if (node == NULL)
    {
        return NULL;
    }
    memset(node->chaddr, 0, sizeof(node->chaddr));
    SMEMCPY(node->chaddr, msg->chaddr, DHCP_MAX_HLEN);
    node->ipaddr = dhcpserver->current;
    dhcp_client_lease_renew(node);

    node->next = dhcpserver->node_list;
    dhcpserver->node_list = node;

    return node;
}

/**
* find option from buffer.
*
* @param buf The buffer to find option
* @param len The buffer length
* @param option Which option to find
* @return dhcp option buffer
*/
static u8_t *
dhcp_server_option_find(u8_t *buf, u16_t len, u8_t option)
{
    u8_t *end = buf + len;
    u16_t remaining;

    while ((buf < end) && (*buf != DHCP_OPTION_END))
    {
        remaining = end - buf;

        /* need at least option + length */
        if (remaining < 2)
        {
            break;
        }

        /* option data must stay within the received packet */
        if (buf[1] > remaining - 2)
        {
            break;
        }

        if (*buf == option)
        {
            return buf;
        }
        buf += (buf[1] + 2);
    }
    return NULL;
}

/**
* If an incoming DHCP message is in response to us, then trigger the state machine
*/
static void
dhcp_server_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *recv_addr, u16_t port)
{
    struct dhcp_server *dhcp_server = (struct dhcp_server *)arg;
    struct dhcp_msg *msg;
    struct pbuf *q;
    u8_t *opt_buf;
    u8_t *opt;
    struct dhcp_client_node *node;
    u8_t msg_type;
    u16_t length;
    ip_addr_t addr = *recv_addr;
    u32_t tmp;

    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("[%s:%d] %c%c recv %d\n", __FUNCTION__, __LINE__, dhcp_server->netif->name[0], dhcp_server->netif->name[1], p->tot_len));
    /* prevent warnings about unused arguments */
    LWIP_UNUSED_ARG(pcb);
    LWIP_UNUSED_ARG(addr);
    LWIP_UNUSED_ARG(port);

    if (p->len < DHCP_MIN_REQUEST_LEN || p->tot_len < DHCP_OPTIONS_OFS)
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING, ("DHCP request message or pbuf too short\n"));
        pbuf_free(p);
        return;
    }

    q = pbuf_alloc(PBUF_TRANSPORT, 1500, PBUF_RAM);
    if (q == NULL)
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING, ("pbuf_alloc dhcp_msg failed!\n"));
        pbuf_free(p);
        return;
    }
    if (q->tot_len < p->tot_len)
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING, ("pbuf_alloc dhcp_msg too small %d:%d\n", q->tot_len, p->tot_len));
        pbuf_free(q);
        pbuf_free(p);
        return;
    }

    /* Parse only bytes actually received, not the whole allocated buffer. */
    length = p->tot_len - DHCP_OPTIONS_OFS;
    pbuf_copy(q, p);
    pbuf_free(p);

    msg = (struct dhcp_msg *)q->payload;
    if (!dhcp_msg_usable(msg))
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING,
                    ("drop DHCP frame: op %" U16_F " cookie 0x%08" X32_F " hlen %" U16_F "\n",
                     (u16_t)msg->op, msg->cookie, (u16_t)msg->hlen));
        goto free_pbuf_and_return;
    }

    opt_buf = (u8_t *)msg + DHCP_OPTIONS_OFS;
    opt = dhcp_server_option_find(opt_buf, length, DHCP_OPTION_MESSAGE_TYPE);
    if (opt && opt[1] >= 1)
    {
        msg_type = *(opt + 2);
        if (msg_type == DHCP_DISCOVER)
        {
            node = dhcp_client_alloc(dhcp_server, msg, opt_buf, length);
            if (node == NULL)
            {
                goto free_pbuf_and_return;
            }
            /* create dhcp offer and send */
            msg->op = DHCP_BOOTREPLY;
            msg->hops = 0;
            msg->secs = 0;
            SMEMCPY(&msg->siaddr, &(dhcp_server->netif->ip_addr), 4);
            msg->sname[0] = '\0';
            msg->file[0] = '\0';
            msg->cookie = PP_HTONL(DHCP_MAGIC_COOKIE);
            SMEMCPY(&msg->yiaddr, &node->ipaddr, 4);

            opt_buf = (u8_t *)msg + DHCP_OPTIONS_OFS;
            /* add msg type */
            *opt_buf++ = DHCP_OPTION_MESSAGE_TYPE;
            *opt_buf++ = 1;
            *opt_buf++ = DHCP_OFFER;

            /* add server id */
            *opt_buf++ = DHCP_OPTION_SERVER_ID;
            *opt_buf++ = 4;
            SMEMCPY(opt_buf, &(dhcp_server->netif->ip_addr), 4);
            opt_buf += 4;

            /* add_lease_time */
            *opt_buf++ = DHCP_OPTION_LEASE_TIME;
            *opt_buf++ = 4;
            tmp = PP_HTONL(DHCP_DEFAULT_LIVE_TIME);
            SMEMCPY(opt_buf, &tmp, 4);
            opt_buf += 4;

            /* add config */
            *opt_buf++ = DHCP_OPTION_SUBNET_MASK;
            *opt_buf++ = 4;
            SMEMCPY(opt_buf, &ip_2_ip4(&dhcp_server->netif->netmask)->addr, 4);
            opt_buf += 4;

            *opt_buf++ = DHCP_OPTION_DNS_SERVER;
            *opt_buf++ = 4;
#ifdef DHCP_DNS_SERVER_IP
            {
                ip_addr_t dns_addr;
                ipaddr_aton(DHCP_DNS_SERVER_IP, &dns_addr);
                SMEMCPY(opt_buf, &ip_2_ip4(&dns_addr)->addr, 4);
            }
#else
            /* default use gatewary dns server */
            SMEMCPY(opt_buf, &(dhcp_server->netif->ip_addr), 4);
#endif /* DHCP_DNS_SERVER_IP */
            opt_buf += 4;

            *opt_buf++ = DHCP_OPTION_ROUTER;
            *opt_buf++ = 4;
            SMEMCPY(opt_buf, &ip_2_ip4(&dhcp_server->netif->ip_addr)->addr, 4);
            opt_buf += 4;

            /* add option end */
            *opt_buf++ = DHCP_OPTION_END;

            length = (u32_t)opt_buf - (u32_t)msg;
            if (length < q->tot_len)
            {
                pbuf_realloc(q, length);
            }

            ip_2_ip4(&addr)->addr = INADDR_BROADCAST;
            udp_sendto_if(pcb, q, &addr, port, dhcp_server->netif);
        }
        else
        {
            if (1)
            {
                if (msg_type == DHCP_REQUEST)
                {
                    node = dhcp_client_find(dhcp_server, msg, opt_buf, length);
                    if (node != NULL)
                    {
                        /* Send ack */
                        dhcp_client_lease_renew(node);
                        /* create dhcp offer and send */
                        msg->op = DHCP_BOOTREPLY;
                        msg->hops = 0;
                        msg->secs = 0;
                        SMEMCPY(&msg->siaddr, &(dhcp_server->netif->ip_addr), 4);
                        msg->sname[0] = '\0';
                        msg->file[0] = '\0';
                        msg->cookie = PP_HTONL(DHCP_MAGIC_COOKIE);
                        SMEMCPY(&msg->yiaddr, &node->ipaddr, 4);
                        opt_buf = (u8_t *)msg + DHCP_OPTIONS_OFS;

                        /* add msg type */
                        *opt_buf++ = DHCP_OPTION_MESSAGE_TYPE;
                        *opt_buf++ = 1;
                        *opt_buf++ = DHCP_ACK;

                        /* add server id */
                        *opt_buf++ = DHCP_OPTION_SERVER_ID;
                        *opt_buf++ = 4;
                        SMEMCPY(opt_buf, &(dhcp_server->netif->ip_addr), 4);
                        opt_buf += 4;

                        /* add_lease_time */
                        *opt_buf++ = DHCP_OPTION_LEASE_TIME;
                        *opt_buf++ = 4;
                        tmp = PP_HTONL(DHCP_DEFAULT_LIVE_TIME);
                        SMEMCPY(opt_buf, &tmp, 4);
                        opt_buf += 4;

                        /* add config */
                        *opt_buf++ = DHCP_OPTION_SUBNET_MASK;
                        *opt_buf++ = 4;
                        SMEMCPY(opt_buf, &ip_2_ip4(&dhcp_server->netif->netmask)->addr, 4);
                        opt_buf += 4;

                        *opt_buf++ = DHCP_OPTION_DNS_SERVER;
                        *opt_buf++ = 4;
#ifdef DHCP_DNS_SERVER_IP
                        {
                            ip_addr_t dns_addr;
                            ipaddr_aton(DHCP_DNS_SERVER_IP, &dns_addr);
                            SMEMCPY(opt_buf, &ip_2_ip4(&dns_addr)->addr, 4);
                        }
#else
                        /* default use gatewary dns server */
                        SMEMCPY(opt_buf, &(dhcp_server->netif->ip_addr), 4);
#endif /* DHCP_DNS_SERVER_IP */
                        opt_buf += 4;

                        *opt_buf++ = DHCP_OPTION_ROUTER;
                        *opt_buf++ = 4;
                        SMEMCPY(opt_buf, &ip_2_ip4(&dhcp_server->netif->ip_addr)->addr, 4);
                        opt_buf += 4;

                        /* add option end */
                        *opt_buf++ = DHCP_OPTION_END;

                        length = (u32_t)opt_buf - (u32_t)msg;
                        if (length < q->tot_len)
                        {
                            pbuf_realloc(q, length);
                        }

                        ip_2_ip4(&addr)->addr = INADDR_BROADCAST;
                        udp_sendto_if(pcb, q, &addr, port, dhcp_server->netif);
                    }
                    else
                    {
                        /* Send no ack */
                        /* create dhcp offer and send */
                        msg->op = DHCP_BOOTREPLY;
                        msg->hops = 0;
                        msg->secs = 0;
                        SMEMCPY(&msg->siaddr, &(dhcp_server->netif->ip_addr), 4);
                        msg->sname[0] = '\0';
                        msg->file[0] = '\0';
                        msg->cookie = PP_HTONL(DHCP_MAGIC_COOKIE);
                        memset(&msg->yiaddr, 0, 4);
                        opt_buf = (u8_t *)msg + DHCP_OPTIONS_OFS;

                        /* add msg type */
                        *opt_buf++ = DHCP_OPTION_MESSAGE_TYPE;
                        *opt_buf++ = 1;
                        *opt_buf++ = DHCP_NAK;

                        /* add server id */
                        *opt_buf++ = DHCP_OPTION_SERVER_ID;
                        *opt_buf++ = 4;
                        SMEMCPY(opt_buf, &(dhcp_server->netif->ip_addr), 4);
                        opt_buf += 4;

                        /* add option end */
                        *opt_buf++ = DHCP_OPTION_END;
                        length = (u32_t)opt_buf - (u32_t)msg;
                        if (length < q->tot_len)
                        {
                            pbuf_realloc(q, length);
                        }

                        ip_2_ip4(&addr)->addr = INADDR_BROADCAST;
                        udp_sendto_if(pcb, q, &addr, port, dhcp_server->netif);
                    }
                }
                else if (msg_type == DHCP_RELEASE)
                {
                    struct dhcp_client_node *node_prev = NULL;

                    for (node = dhcp_server->node_list; node != NULL; node = node->next)
                    {
                        if (dhcp_chaddr_equal(node, msg))
                        {
                            if (node == dhcp_server->node_list)
                            {
                                dhcp_server->node_list = node->next;
                            }
                            else
                            {
                                node_prev->next = node->next;
                            }
                            break;
                        }
                        node_prev = node;
                    }

                    if (node != NULL)
                    {
                        mem_free(node);
                    }
                }
                else if (msg_type == DHCP_DECLINE)
                {
                    ;
                }
                else if (msg_type == DHCP_INFORM)
                {
                    ;
                }
            }
        }
        /* Reclaim expired leases on incoming packets too, shortening gaps between checks. */
        dhcp_client_remove_expired(dhcp_server);
    }

free_pbuf_and_return:
    pbuf_free(q);
}

/*
 * The DHCP server lifecycle must run on the lwIP TCP/IP thread.
 *
 * sys_timeout() / sys_untimeout() are not safe from any other thread:
 *  - lwIP 2.0.3 (the RT-Thread default) runs sys_timeouts_mbox_fetch() and
 *    sys_check_timeouts() outside LOCK_TCPIP_CORE(), so posting or cancelling
 *    a timeout from another thread races with the tcpip thread on the
 *    next_timeout list - even when LWIP_TCPIP_CORE_LOCKING == 1;
 *  - when LWIP_TCPIP_CORE_LOCKING == 0, LOCK_TCPIP_CORE() is an empty macro
 *    and protects nothing at all;
 *  - a timeout posted from outside does not wake a blocked tcpip thread, so
 *    the periodic recycle would be delayed until unrelated traffic arrives.
 *
 * dhcp_server_recv() and dhcp_server_periodic_recycle() already run on that
 * thread, so the start/stop entry points are marshalled there with
 * tcpip_callback().  The server, its lease list and its timeout then live in
 * one context on every supported lwIP (2.0.3 / 2.1.2 / 2.2.1) and with either
 * setting of LWIP_TCPIP_CORE_LOCKING.
 */
typedef void (*dhcpd_tcpip_fn)(void *arg);

struct dhcpd_tcpip_call
{
    dhcpd_tcpip_fn fn;
    void *arg;
    sys_sem_t done;
};

/*
 * Tell whether the caller already runs on the lwIP TCP/IP thread: posting a
 * callback from that thread and waiting for it would deadlock.  The tcpip
 * thread is created by the lwIP port with TCPIP_THREAD_NAME, the same way
 * components/net/lwip/port/ethernetif.c identifies it.
 */
static rt_bool_t dhcpd_in_tcpip_thread(void)
{
    rt_thread_t self = rt_thread_self();

    if (self == RT_NULL)
    {
        return RT_FALSE;
    }

    return self == rt_thread_find(TCPIP_THREAD_NAME);
}

static void dhcpd_tcpip_call_entry(void *arg)
{
    struct dhcpd_tcpip_call *call = (struct dhcpd_tcpip_call *)arg;

    call->fn(call->arg);
    sys_sem_signal(&call->done);
}

/*
 * Run fn on the tcpip thread and wait for its completion.
 *
 * The callback message is handled with the core lock held by lwIP (2.0.3,
 * 2.1.2 and 2.2.1 alike), so fn must not take LOCK_TCPIP_CORE() again.
 *
 * @return ERR_OK when fn ran, or the tcpip_callback()/sys_sem_new() error
 */
static err_t dhcpd_run_in_tcpip(dhcpd_tcpip_fn fn, void *arg)
{
    struct dhcpd_tcpip_call call;
    err_t err;

    if (dhcpd_in_tcpip_thread())
    {
        fn(arg);
        return ERR_OK;
    }

    err = sys_sem_new(&call.done, 0);
    if (err != ERR_OK)
    {
        return err;
    }

    call.fn = fn;
    call.arg = arg;

    err = tcpip_callback(dhcpd_tcpip_call_entry, &call);
    if (err != ERR_OK)
    {
        sys_sem_free(&call.done);
        return err;
    }

    sys_sem_wait(&call.done);
    sys_sem_free(&call.done);

    return ERR_OK;
}

/**
* Periodically reclaim expired leases from every registered server.
*
* Registered and unregistered from the tcpip thread only, and itself executed
* by the lwIP timeout path on that same thread, so no lock is needed to walk
* the server list or the lease lists.
*/
static void dhcp_server_periodic_recycle(void *arg)
{
    struct dhcp_server *server;
    LWIP_UNUSED_ARG(arg);

    for (server = lw_dhcp_server; server != NULL; server = server->next)
    {
        dhcp_client_remove_expired(server);
    }

    if (lw_dhcp_server != NULL)
    {
        sys_timeout(DHCPD_RECYCLE_INTERVAL_MS, dhcp_server_periodic_recycle, NULL);
    }
}

/**
* start dhcp server for a netif
*
* @param netif The netif which use dhcp server
* @param start The Start IP address
* @param end The End IP address
* @return lwIP error code
* - ERR_OK - No error
* - ERR_MEM - Out of memory
*
* Must run on the lwIP tcpip thread, see dhcpd_run_in_tcpip().
*/
static err_t dhcp_server_start_core(struct netif *netif, ip4_addr_t *start, ip4_addr_t *end)
{
    struct dhcp_server *dhcp_server;
    err_t err;

    /* If this netif alreday use the dhcp server. */
    for (dhcp_server = lw_dhcp_server; dhcp_server != NULL; dhcp_server = dhcp_server->next)
    {
        if (dhcp_server->netif == netif)
        {
            dhcp_server->start = *start;
            dhcp_server->end = *end;
            dhcp_server->current = *start;
            return ERR_OK;
        }
    }

    dhcp_server = NULL;
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcp_server_start(): starting new DHCP server\n"));
    dhcp_server = (struct dhcp_server *)mem_malloc(sizeof(struct dhcp_server));
    if (dhcp_server == NULL)
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcp_server_start(): could not allocate dhcp\n"));
        return ERR_MEM;
    }

    /* clear data structure */
    memset(dhcp_server, 0, sizeof(struct dhcp_server));

    dhcp_server->netif = netif;
    dhcp_server->node_list = NULL;
    dhcp_server->start = *start;
    dhcp_server->end = *end;
    dhcp_server->current = *start;

    /* allocate UDP PCB */
    dhcp_server->pcb = udp_new();
    if (dhcp_server->pcb == NULL)
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcp_server_start(): could not obtain pcb\n"));
        mem_free(dhcp_server);
        return ERR_MEM;
    }

    ip_set_option(dhcp_server->pcb, SOF_BROADCAST);
    /* set up local and remote port for the pcb */
    err = udp_bind(dhcp_server->pcb, IP_ADDR_ANY, DHCP_SERVER_PORT);
    if (err != ERR_OK)
    {
        LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcp_server_start(): could not bind pcb, err=%d\n", (int)err));
        udp_remove(dhcp_server->pcb);
        mem_free(dhcp_server);
        return err;
    }
    //udp_connect(dhcp_server->pcb, IP_ADDR_ANY, DHCP_CLIENT_PORT);

    /* set up the recv callback and argument */
    udp_recv(dhcp_server->pcb, dhcp_server_recv, dhcp_server);

    /* Publish the server only after all resources are ready. */
    if (lw_dhcp_server == NULL)
    {
        sys_timeout(DHCPD_RECYCLE_INTERVAL_MS, dhcp_server_periodic_recycle, NULL);
    }
    dhcp_server->next = lw_dhcp_server;
    lw_dhcp_server = dhcp_server;
    LWIP_DEBUGF(DHCP_DEBUG | LWIP_DBG_TRACE, ("dhcp_server_start(): starting DHCP server\n"));

    return ERR_OK;
}

struct dhcp_server_start_args
{
    struct netif *netif;
    ip4_addr_t start;
    ip4_addr_t end;
    err_t err;
};

static void dhcp_server_start_entry(void *arg)
{
    struct dhcp_server_start_args *args = (struct dhcp_server_start_args *)arg;

    args->err = dhcp_server_start_core(args->netif, &args->start, &args->end);
}

err_t dhcp_server_start(struct netif *netif, ip4_addr_t *start, ip4_addr_t *end)
{
    struct dhcp_server_start_args args;
    err_t err;

    args.netif = netif;
    args.start = *start;
    args.end = *end;
    args.err = ERR_MEM; /* reported when the callback never runs */

    err = dhcpd_run_in_tcpip(dhcp_server_start_entry, &args);

    return (err == ERR_OK) ? args.err : err;
}

extern void set_if(const char *netif_name, const char *ip_addr, const char *gw_addr, const char *nm_addr);

static void dhcpd_start_core(const char *netif_name)
{
    struct netif *netif;
    err_t res;

    DEBUG_PRINTF("%s: %s\r\n", __FUNCTION__, netif_name);

    netif = netif_list;
    if (strlen(netif_name) > sizeof(netif->name))
    {
        DEBUG_PRINTF("network interface name too long!\r\n");
        goto _exit;
    }

    while (netif != RT_NULL)
    {
        if (strncmp(netif_name, netif->name, sizeof(netif->name)) == 0)
        {
            break;
        }

        netif = netif->next;
        if (netif == RT_NULL)
        {
            DEBUG_PRINTF("network interface: %s not found!\r\n", netif_name);
            break;
        }
    }

    if (netif == RT_NULL)
    {
        goto _exit;
    }

    if (1)
    {
        dhcp_stop(netif);

        set_if(netif_name, DHCPD_SERVER_IP, "0.0.0.0", "255.255.255.0");

        netif_set_up(netif);
    }

    {
        char str_tmp[4 * 4 + 4] = DHCPD_SERVER_IP;
        char *p = str_tmp;
        ip4_addr_t ip_start, ip_end;

        p = strchr(str_tmp, '.');
        if (p)
        {
            p = strchr(p + 1, '.');
            if (p)
            {
                p = strchr(p + 1, '.');
            }
        }
        if (!p)
        {
            DEBUG_PRINTF("DHCPD_SERVER_IP: %s error!\r\n", str_tmp);
            goto _exit;
        }
        p = p + 1; /* move to xxx.xxx.xxx.^ */

        snprintf(p, (size_t)(str_tmp + sizeof(str_tmp) - p), "%d", DHCPD_CLIENT_IP_MIN);
        ip4addr_aton(str_tmp, &ip_start);
        DEBUG_PRINTF("ip_start: [%s]\r\n", str_tmp);
        snprintf(p, (size_t)(str_tmp + sizeof(str_tmp) - p), "%d", DHCPD_CLIENT_IP_MAX);
        ip4addr_aton(str_tmp, &ip_end);
        DEBUG_PRINTF("ip_end: [%s]\r\n", str_tmp);

        res = dhcp_server_start_core(netif, &ip_start, &ip_end);
        if (res != 0)
        {
            DEBUG_PRINTF("dhcp_server_start res: %d.\r\n", (int)res);
        }
    }

_exit:
    return;
}

static void dhcpd_start_entry(void *arg)
{
    dhcpd_start_core((const char *)arg);
}

void dhcpd_start(const char *netif_name)
{
    err_t err = dhcpd_run_in_tcpip(dhcpd_start_entry, (void *)netif_name);

    if (err != ERR_OK)
    {
        DEBUG_PRINTF("%s: failed to run on the tcpip thread, err=%d\r\n",
                     __FUNCTION__, (int)err);
    }
}

static void dhcpd_stop_core(const char *netif_name)
{
    struct dhcp_server *dhcp_server, *server_node;
    struct netif *netif;
    struct dhcp_client_node *node, *next;

    DEBUG_PRINTF("%s: %s\r\n", __FUNCTION__, netif_name);

    netif = netif_list;
    if (strlen(netif_name) > sizeof(netif->name))
    {
        DEBUG_PRINTF("network interface name too long!\r\n");
        goto _exit;
    }

    while (netif != RT_NULL)
    {
        if (strncmp(netif_name, netif->name, sizeof(netif->name)) == 0)
        {
            break;
        }

        netif = netif->next;
        if (netif == RT_NULL)
        {
            DEBUG_PRINTF("network interface: %s not found!\r\n", netif_name);
            break;
        }
    }

    if (netif == RT_NULL)
    {
        goto _exit;
    }

    /* If this netif alreday use the dhcp server. */
    for (dhcp_server = lw_dhcp_server; dhcp_server != NULL; dhcp_server = dhcp_server->next)
    {
        if (dhcp_server->netif == netif)
        {
            break;
        }
    }
    if (dhcp_server == RT_NULL)
    {
        goto _exit;
    }

    /* remove dhcp server */
    if (dhcp_server == lw_dhcp_server)
    {
        lw_dhcp_server = lw_dhcp_server->next;
    }
    else
    {
        server_node = lw_dhcp_server;
        while (server_node->next && server_node->next != dhcp_server)
        {
            server_node = server_node->next;
        }
        if (server_node->next != RT_NULL)
        {
            server_node->next = server_node->next->next;
        }
    }

    udp_disconnect(dhcp_server->pcb);
    udp_remove(dhcp_server->pcb);

    /* remove all client node */
    for (node = dhcp_server->node_list; node != NULL; node = next)
    {
        next = node->next;
        mem_free(node);
    }

    mem_free(dhcp_server);
    if (lw_dhcp_server == NULL)
    {
        sys_untimeout(dhcp_server_periodic_recycle, NULL);
    }
    set_if(netif_name, "0.0.0.0", "0.0.0.0", "0.0.0.0");

_exit:
    return;
}

static void dhcpd_stop_entry(void *arg)
{
    dhcpd_stop_core((const char *)arg);
}

void dhcpd_stop(const char *netif_name)
{
    err_t err = dhcpd_run_in_tcpip(dhcpd_stop_entry, (void *)netif_name);

    if (err != ERR_OK)
    {
        DEBUG_PRINTF("%s: failed to run on the tcpip thread, err=%d\r\n",
                     __FUNCTION__, (int)err);
    }
}
