/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * COPYRIGHT (C) 2006-2010, RT-Thread Development Team
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
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-07-07     Bernard      fix send mail to mailbox issue.
 * 2011-07-30     mbbill       port lwIP 1.4.0 to RT-Thread
 * 2012-04-10     Bernard      add more compatible with RT-Thread.
 * 2012-11-12     Bernard      The network interface can be initialized
 *                             after lwIP initialization.
 * 2013-02-28     aozima       fixed list_tcps bug: ipaddr_ntoa isn't reentrant.
 */

#include <rtthread.h>

#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include "lwip/netif.h"
#include "lwip/stats.h"
#include "lwip/tcpip.h"

#include "netif/etharp.h"
#include "netif/ethernetif.h"
#include "lwip/inet.h"

#define netifapi_netif_set_link_up(n)      netifapi_netif_common(n, netif_set_link_up, NULL)
#define netifapi_netif_set_link_down(n)    netifapi_netif_common(n, netif_set_link_down, NULL)

#ifndef RT_LWIP_ETHTHREAD_PRIORITY
#define RT_ETHERNETIF_THREAD_PREORITY	0x90
#else
#define RT_ETHERNETIF_THREAD_PREORITY	RT_LWIP_ETHTHREAD_PRIORITY
#endif

#ifndef LWIP_NO_TX_THREAD
/**
 * Tx message structure for Ethernet interface
 */
struct eth_tx_msg
{
    struct netif 	*netif;
    struct pbuf 	*buf;
};

static struct rt_mailbox eth_tx_thread_mb;
static struct rt_thread eth_tx_thread;
#ifndef RT_LWIP_ETHTHREAD_MBOX_SIZE
static char eth_tx_thread_mb_pool[32 * 4];
static char eth_tx_thread_stack[512];
#else
static char eth_tx_thread_mb_pool[RT_LWIP_ETHTHREAD_MBOX_SIZE * 4];
static char eth_tx_thread_stack[RT_LWIP_ETHTHREAD_STACKSIZE];
#endif
#endif

#ifndef LWIP_NO_RX_THREAD
static struct rt_mailbox eth_rx_thread_mb;
static struct rt_thread eth_rx_thread;
#ifndef RT_LWIP_ETHTHREAD_MBOX_SIZE
static char eth_rx_thread_mb_pool[48 * 4];
static char eth_rx_thread_stack[1024];
#else
static char eth_rx_thread_mb_pool[RT_LWIP_ETHTHREAD_MBOX_SIZE * 4];
static char eth_rx_thread_stack[RT_LWIP_ETHTHREAD_STACKSIZE];
#endif
#endif

#ifdef RT_USING_NETDEV

#include "lwip/ip.h"
#include "lwip/init.h"
#include "lwip/netdb.h"
#include <netdev.h>

static int lwip_netdev_set_up(struct netdev *netif)
{
    netif_set_up((struct netif *)netif->user_data);
    return ERR_OK;
}

static int lwip_netdev_set_down(struct netdev *netif)
{
    netif_set_down((struct netif *)netif->user_data);
    return ERR_OK;
}

static int lwip_netdev_set_addr_info(struct netdev *netif, ip_addr_t *ip_addr, ip_addr_t *netmask, ip_addr_t *gw)
{
    if (ip_addr && netmask && gw)
    {
        netif_set_addr((struct netif *)netif->user_data, ip_addr, netmask, gw);
    }
    else
    {
        if (ip_addr)
        {
            netif_set_ipaddr((struct netif *)netif->user_data, ip_addr);
        }

        if (netmask)
        {
            netif_set_netmask((struct netif *)netif->user_data, netmask);
        }

        if (gw)
        {
            netif_set_gw((struct netif *)netif->user_data, gw);
        }
    }

    return ERR_OK;
}

#ifdef RT_LWIP_DNS
static int lwip_netdev_set_dns_server(struct netdev *netif, uint8_t dns_num, ip_addr_t *dns_server)
{
    extern void set_dns(uint8_t dns_num, char* dns_server);
    set_dns(dns_num, ipaddr_ntoa(dns_server));
    return ERR_OK;
}
#endif /* RT_LWIP_DNS */

#ifdef RT_LWIP_DHCP
static int lwip_netdev_set_dhcp(struct netdev *netif, rt_bool_t is_enabled)
{
    netdev_low_level_set_dhcp_status(netif, is_enabled);
    return ERR_OK;
}
#endif /* RT_LWIP_DHCP */

#ifdef RT_LWIP_USING_PING
extern int lwip_ping_recv(int s, int *ttl);
extern err_t lwip_ping_send(int s, ip_addr_t *addr, int size);

int lwip_netdev_ping(struct netdev *netif, const char *host, size_t data_len, 
                        uint32_t timeout, struct netdev_ping_resp *ping_resp)
{
    int s, ttl, recv_len, result = 0;
    int elapsed_time;
    rt_tick_t recv_start_tick;
#if LWIP_VERSION_MAJOR >= 2U
    struct timeval recv_timeout = { timeout / RT_TICK_PER_SECOND, timeout % RT_TICK_PER_SECOND };
#else
    int recv_timeout = timeout * 1000UL / RT_TICK_PER_SECOND;
#endif
    ip_addr_t target_addr;
    struct addrinfo hint, *res = RT_NULL;
    struct sockaddr_in *h = RT_NULL;
    struct in_addr ina;
    
    RT_ASSERT(netif);
    RT_ASSERT(host);
    RT_ASSERT(ping_resp);

    rt_memset(&hint, 0x00, sizeof(hint));
    /* convert URL to IP */
    if (lwip_getaddrinfo(host, RT_NULL, &hint, &res) != 0)
    {
        return -RT_ERROR;
    }
    rt_memcpy(&h, &res->ai_addr, sizeof(struct sockaddr_in *));
    rt_memcpy(&ina, &h->sin_addr, sizeof(ina));
    lwip_freeaddrinfo(res);
    if (inet_aton(inet_ntoa(ina), &target_addr) == 0)
    {
        return -RT_ERROR;
    }
    rt_memcpy(&(ping_resp->ip_addr), &target_addr, sizeof(ip_addr_t));
    
    /* new a socket */
    if ((s = lwip_socket(AF_INET, SOCK_RAW, IP_PROTO_ICMP)) < 0)
    {
        return -RT_ERROR;
    }

    lwip_setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout));

    if (lwip_ping_send(s, &target_addr, data_len) == ERR_OK)
    {
        recv_start_tick = rt_tick_get();
        if ((recv_len = lwip_ping_recv(s, &ttl)) >= 0)
        {
            elapsed_time = (rt_tick_get() - recv_start_tick) * 1000UL / RT_TICK_PER_SECOND;
            ping_resp->data_len = recv_len;
            ping_resp->ttl = ttl;
            ping_resp->ticks = elapsed_time;
        }
        else
        {
            result = -RT_ETIMEOUT;
            goto __exit;
        }
    }
    else
    {
        result = -RT_ETIMEOUT;
        goto __exit;
    }

__exit:
    lwip_close(s);

    return result;
}
#endif /* RT_LWIP_USING_PING */

#if defined (RT_LWIP_TCP) || defined (RT_LWIP_UDP)
void lwip_netdev_netstat(struct netdev *netif)
{
    extern void list_tcps(void);
    extern void list_udps(void);

#ifdef RT_LWIP_TCP
    list_tcps();
#endif
#ifdef RT_LWIP_UDP
    list_udps();
#endif
}
#endif /* RT_LWIP_TCP || RT_LWIP_UDP */

const struct netdev_ops lwip_netdev_ops =
{
    lwip_netdev_set_up,
    lwip_netdev_set_down,

    lwip_netdev_set_addr_info,
#ifdef RT_LWIP_DNS
    lwip_netdev_set_dns_server,
#else 
    NULL,
#endif /* RT_LWIP_DNS */

#ifdef RT_LWIP_DHCP
    lwip_netdev_set_dhcp,
#else
    NULL,
#endif /* RT_LWIP_DHCP */

#ifdef RT_LWIP_USING_PING
    lwip_netdev_ping,
#else
    NULL,
#endif /* RT_LWIP_USING_PING */

#if defined (RT_LWIP_TCP) || defined (RT_LWIP_UDP)
    lwip_netdev_netstat,
#endif /* RT_LWIP_TCP || RT_LWIP_UDP */
};

static int netdev_add(struct netif *lwip_netif)
{
#define LWIP_NETIF_NAME_LEN 2
    int result = 0;
    struct netdev *netdev = RT_NULL;
    char name[LWIP_NETIF_NAME_LEN + 1] = {0};

    RT_ASSERT(lwip_netif);

    netdev = (struct netdev *)rt_calloc(1, sizeof(struct netdev));
    if (netdev == RT_NULL)
    {
        return -ERR_IF;
    }

#ifdef SAL_USING_LWIP
    extern int sal_lwip_netdev_set_pf_info(struct netdev *netdev);
    /* set the lwIP network interface device protocol family information */
    sal_lwip_netdev_set_pf_info(netdev);
#endif /* SAL_USING_LWIP */

    rt_strncpy(name, lwip_netif->name, LWIP_NETIF_NAME_LEN);
    result = netdev_register(netdev, name, (void *)lwip_netif);
    
    /* Update netdev info after registered */
    netdev->flags = lwip_netif->flags;
    netdev->mtu = lwip_netif->mtu;
    netdev->ops = &lwip_netdev_ops;
    netdev->hwaddr_len =  lwip_netif->hwaddr_len;
    rt_memcpy(netdev->hwaddr, lwip_netif->hwaddr, lwip_netif->hwaddr_len);
    netdev->ip_addr = lwip_netif->ip_addr;
    netdev->gw = lwip_netif->gw;
    netdev->netmask = lwip_netif->netmask;
	
#ifdef RT_LWIP_DHCP
    netdev_low_level_set_dhcp_status(netdev, RT_TRUE);
#endif

    return result;
}

/* synchronize lwIP network interface device and network interface device flags */
static int netdev_flags_sync(struct netif *lwip_netif)
{
    struct netdev *netdev = NULL;

    RT_ASSERT(lwip_netif);

    netdev = netdev_get_by_name(lwip_netif->name);
    if (netdev == RT_NULL)
    {
        return -ERR_IF;
    }

    netdev->flags |= lwip_netif->flags;

    return ERR_OK;
}
#endif /* RT_USING_NETDEV */

static err_t ethernetif_linkoutput(struct netif *netif, struct pbuf *p)
{
#ifndef LWIP_NO_TX_THREAD
    struct eth_tx_msg msg;
    struct eth_device* enetif;

	RT_ASSERT(netif != RT_NULL);
    enetif = (struct eth_device*)netif->state;

    /* send a message to eth tx thread */
    msg.netif = netif;
    msg.buf   = p;
    if (rt_mb_send(&eth_tx_thread_mb, (rt_uint32_t) &msg) == RT_EOK)
    {
        /* waiting for ack */
        rt_sem_take(&(enetif->tx_ack), RT_WAITING_FOREVER);
    }
#else
    struct eth_device* enetif;

	RT_ASSERT(netif != RT_NULL);
    enetif = (struct eth_device*)netif->state;

	if (enetif->eth_tx(&(enetif->parent), p) != RT_EOK)
	{
		return ERR_IF;
	}
#endif
    return ERR_OK;
}

static err_t eth_netif_device_init(struct netif *netif)
{
    struct eth_device *ethif;

    ethif = (struct eth_device*)netif->state;
    if (ethif != RT_NULL)
    {
        rt_device_t device;

#ifdef RT_USING_NETDEV
    /* network interface device register */
    netdev_add(netif);
#endif /* RT_USING_NETDEV */

        /* get device object */
        device = (rt_device_t) ethif;
        if (rt_device_init(device) != RT_EOK)
        {
            return ERR_IF;
        }

        /* copy device flags to netif flags */
        netif->flags = (ethif->flags & 0xff);

        /* set default netif */
        if (netif_default == RT_NULL)
            netif_set_default(ethif->netif);

#if LWIP_DHCP
        if (ethif->flags & NETIF_FLAG_DHCP)
        {
            /* if this interface uses DHCP, start the DHCP client */
            dhcp_start(ethif->netif);
        }
        else
#endif
        {
            /* set interface up */
            netif_set_up(ethif->netif);
        }

        if (!(ethif->flags & ETHIF_LINK_PHYUP))
        {
            /* set link_up for this netif */
            netif_set_link_up(ethif->netif);
        }

        return ERR_OK;
    }

    return ERR_IF;
}

/* Keep old drivers compatible in RT-Thread */
rt_err_t eth_device_init_with_flag(struct eth_device *dev, const char *name, rt_uint16_t flags)
{
    struct netif* netif;

    netif = (struct netif*) rt_malloc (sizeof(struct netif));
    if (netif == RT_NULL)
    {
        rt_kprintf("malloc netif failed\n");
        return -RT_ERROR;
    }
    rt_memset(netif, 0, sizeof(struct netif));

    /* set netif */
    dev->netif = netif;
    /* device flags, which will be set to netif flags when initializing */
    dev->flags = flags;
    /* link changed status of device */
    dev->link_changed = 0x00;
    dev->parent.type = RT_Device_Class_NetIf;
    /* register to RT-Thread device manager */
    rt_device_register(&(dev->parent), name, RT_DEVICE_FLAG_RDWR);
    rt_sem_init(&(dev->tx_ack), name, 0, RT_IPC_FLAG_FIFO);

    /* set name */
    netif->name[0] = name[0];
    netif->name[1] = name[1];

    /* set hw address to 6 */
    netif->hwaddr_len 	= 6;
    /* maximum transfer unit */
    netif->mtu			= ETHERNET_MTU;

    /* get hardware MAC address */
    rt_device_control(&(dev->parent), NIOCTL_GADDR, netif->hwaddr);

    /* set output */
    netif->output		= etharp_output;
    netif->linkoutput	= ethernetif_linkoutput;

    /* if tcp thread has been started up, we add this netif to the system */
    if (rt_thread_find("tcpip") != RT_NULL)
    {
        struct ip_addr ipaddr, netmask, gw;

    #if LWIP_DHCP
        if (dev->flags & NETIF_FLAG_DHCP)
        {
            IP4_ADDR(&ipaddr, 0, 0, 0, 0);
            IP4_ADDR(&gw, 0, 0, 0, 0);
            IP4_ADDR(&netmask, 0, 0, 0, 0);
        }
        else
    #endif
        {
            ipaddr.addr = inet_addr(RT_LWIP_IPADDR);
            gw.addr = inet_addr(RT_LWIP_GWADDR);
            netmask.addr = inet_addr(RT_LWIP_MSKADDR);
        }

        netifapi_netif_add(netif, &ipaddr, &netmask, &gw, dev, eth_netif_device_init, tcpip_input);
    }

#ifdef RT_USING_NETDEV
    /* network interface device flags synchronize */
    netdev_flags_sync(netif);
#endif /* RT_USING_NETDEV */


    return RT_EOK;
}

rt_err_t eth_device_init(struct eth_device * dev, const char *name)
{
    rt_uint16_t flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;

#if LWIP_DHCP
    /* DHCP support */
    flags |= NETIF_FLAG_DHCP;
#endif

#if LWIP_IGMP
    /* IGMP support */
    flags |= NETIF_FLAG_IGMP;
#endif

    return eth_device_init_with_flag(dev, name, flags);
}

#ifndef LWIP_NO_RX_THREAD
rt_err_t eth_device_ready(struct eth_device* dev)
{
    if (dev->netif)
        /* post message to Ethernet thread */
        return rt_mb_send(&eth_rx_thread_mb, (rt_uint32_t)dev);
    else
        return ERR_OK; /* netif is not initialized yet, just return. */
}

rt_err_t eth_device_linkchange(struct eth_device* dev, rt_bool_t up)
{
    rt_uint32_t level;

    RT_ASSERT(dev != RT_NULL);

    level = rt_hw_interrupt_disable();
    dev->link_changed = 0x01;
    if (up == RT_TRUE)
        dev->link_status = 0x01;
    else
        dev->link_status = 0x00;
    rt_hw_interrupt_enable(level);

    /* post message to ethernet thread */
    return rt_mb_send(&eth_rx_thread_mb, (rt_uint32_t)dev);
}
#else
/* NOTE: please not use it in interrupt when no RxThread exist */
rt_err_t eth_device_linkchange(struct eth_device* dev, rt_bool_t up)
{
	if (up == RT_TRUE)
		netifapi_netif_set_link_up(dev->netif);
	else
		netifapi_netif_set_link_down(dev->netif);

	return RT_EOK;
}
#endif

#ifndef LWIP_NO_TX_THREAD
/* Ethernet Tx Thread */
static void eth_tx_thread_entry(void* parameter)
{
    struct eth_tx_msg* msg;

    while (1)
    {
        if (rt_mb_recv(&eth_tx_thread_mb, (rt_ubase_t*)&msg, RT_WAITING_FOREVER) == RT_EOK)
        {
            struct eth_device* enetif;

            RT_ASSERT(msg->netif != RT_NULL);
            RT_ASSERT(msg->buf   != RT_NULL);

            enetif = (struct eth_device*)msg->netif->state;
            if (enetif != RT_NULL)
            {
                /* call driver's interface */
                if (enetif->eth_tx(&(enetif->parent), msg->buf) != RT_EOK)
                {
                    /* transmit eth packet failed */
                }
            }

            /* send ACK */
            rt_sem_release(&(enetif->tx_ack));
        }
    }
}
#endif

#ifndef LWIP_NO_RX_THREAD
/* Ethernet Rx Thread */
static void eth_rx_thread_entry(void* parameter)
{
    struct eth_device* device;

    while (1)
    {
        if (rt_mb_recv(&eth_rx_thread_mb, (rt_ubase_t*)&device, RT_WAITING_FOREVER) == RT_EOK)
        {
            struct pbuf *p;

            /* check link status */
            if (device->link_changed)
            {
                int status;
                rt_uint32_t level;

                level = rt_hw_interrupt_disable();
                status = device->link_status;
                device->link_changed = 0x00;
                rt_hw_interrupt_enable(level);

                if (status)
                    netifapi_netif_set_link_up(device->netif);
                else
                    netifapi_netif_set_link_down(device->netif);
            }

            /* receive all of buffer */
            while (1)
            {
            	if(device->eth_rx == RT_NULL) break;
            	
                p = device->eth_rx(&(device->parent));
                if (p != RT_NULL)
                {
                    /* notify to upper layer */
                    if( device->netif->input(p, device->netif) != ERR_OK )
                    {
                        LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: Input error\n"));
                        pbuf_free(p);
                        p = NULL;
                    }
                }
                else break;
            }
        }
        else
        {
            LWIP_ASSERT("Should not happen!\n",0);
        }
    }
}
#endif

int eth_system_device_init(void)
{
    rt_err_t result = RT_EOK;

    /* initialize Rx thread. */
#ifndef LWIP_NO_RX_THREAD
    /* initialize mailbox and create Ethernet Rx thread */
    result = rt_mb_init(&eth_rx_thread_mb, "erxmb",
                        &eth_rx_thread_mb_pool[0], sizeof(eth_rx_thread_mb_pool)/4,
                        RT_IPC_FLAG_FIFO);
    RT_ASSERT(result == RT_EOK);

    result = rt_thread_init(&eth_rx_thread, "erx", eth_rx_thread_entry, RT_NULL,
                            &eth_rx_thread_stack[0], sizeof(eth_rx_thread_stack),
                            RT_ETHERNETIF_THREAD_PREORITY, 16);
    RT_ASSERT(result == RT_EOK);
    result = rt_thread_startup(&eth_rx_thread);
    RT_ASSERT(result == RT_EOK);
#endif

    /* initialize Tx thread */
#ifndef LWIP_NO_TX_THREAD
    /* initialize mailbox and create Ethernet Tx thread */
    result = rt_mb_init(&eth_tx_thread_mb, "etxmb",
                        &eth_tx_thread_mb_pool[0], sizeof(eth_tx_thread_mb_pool)/4,
                        RT_IPC_FLAG_FIFO);
    RT_ASSERT(result == RT_EOK);

    result = rt_thread_init(&eth_tx_thread, "etx", eth_tx_thread_entry, RT_NULL,
                            &eth_tx_thread_stack[0], sizeof(eth_tx_thread_stack),
                            RT_ETHERNETIF_THREAD_PREORITY, 16);
    RT_ASSERT(result == RT_EOK);

    result = rt_thread_startup(&eth_tx_thread);
    RT_ASSERT(result == RT_EOK);
#endif

    return (int)result;
}
INIT_PREV_EXPORT(eth_system_device_init);

#ifdef RT_USING_FINSH
#include <finsh.h>
void set_if(char* netif_name, char* ip_addr, char* gw_addr, char* nm_addr)
{
    struct ip_addr *ip;
    struct ip_addr addr;
    struct netif * netif = netif_list;

    if(strlen(netif_name) > sizeof(netif->name))
    {
        rt_kprintf("network interface name too long!\r\n");
        return;
    }

    while(netif != RT_NULL)
    {
        if(strncmp(netif_name, netif->name, sizeof(netif->name)) == 0)
            break;

        netif = netif->next;
        if( netif == RT_NULL )
        {
            rt_kprintf("network interface: %s not found!\r\n", netif_name);
            return;
        }
    }

    ip = (struct ip_addr *)&addr;

    /* set ip address */
    if ((ip_addr != RT_NULL) && ipaddr_aton(ip_addr, &addr))
    {
        netif_set_ipaddr(netif, ip);
    }

    /* set gateway address */
    if ((gw_addr != RT_NULL) && ipaddr_aton(gw_addr, &addr))
    {
        netif_set_gw(netif, ip);
    }

    /* set netmask address */
    if ((nm_addr != RT_NULL) && ipaddr_aton(nm_addr, &addr))
    {
        netif_set_netmask(netif, ip);
    }
}
FINSH_FUNCTION_EXPORT(set_if, set network interface address);

#if LWIP_DNS
#include <lwip/dns.h>
void set_dns(uint8_t dns_num, char* dns_server)
{
    struct ip_addr addr;

    if ((dns_server != RT_NULL) && ipaddr_aton(dns_server, &addr))
    {
        dns_setserver(dns_num, &addr);
    }
}
FINSH_FUNCTION_EXPORT(set_dns, set DNS server address);
#endif

void list_if(void)
{
    rt_ubase_t index;
    struct netif * netif;

    rt_enter_critical();

    netif = netif_list;

    while( netif != RT_NULL )
    {
        rt_kprintf("network interface: %c%c%s\n",
                   netif->name[0],
                   netif->name[1],
                   (netif == netif_default)?" (Default)":"");
        rt_kprintf("MTU: %d\n", netif->mtu);
        rt_kprintf("MAC: ");
        for (index = 0; index < netif->hwaddr_len; index ++)
            rt_kprintf("%02x ", netif->hwaddr[index]);
        rt_kprintf("\nFLAGS:");
        if (netif->flags & NETIF_FLAG_UP) rt_kprintf(" UP");
        else rt_kprintf(" DOWN");
        if (netif->flags & NETIF_FLAG_LINK_UP) rt_kprintf(" LINK_UP");
        else rt_kprintf(" LINK_DOWN");
        if (netif->flags & NETIF_FLAG_DHCP) rt_kprintf(" DHCP");
        if (netif->flags & NETIF_FLAG_POINTTOPOINT) rt_kprintf(" PPP");
        if (netif->flags & NETIF_FLAG_ETHARP) rt_kprintf(" ETHARP");
        if (netif->flags & NETIF_FLAG_IGMP) rt_kprintf(" IGMP");
        rt_kprintf("\n");
        rt_kprintf("ip address: %s\n", ipaddr_ntoa(&(netif->ip_addr)));
        rt_kprintf("gw address: %s\n", ipaddr_ntoa(&(netif->gw)));
        rt_kprintf("net mask  : %s\n", ipaddr_ntoa(&(netif->netmask)));
        rt_kprintf("\r\n");

        netif = netif->next;
    }

#if LWIP_DNS
    {
        struct ip_addr ip_addr;

        for(index=0; index<DNS_MAX_SERVERS; index++)
        {
            ip_addr = dns_getserver(index);
            rt_kprintf("dns server #%d: %s\n", index, ipaddr_ntoa(&(ip_addr)));
        }
    }
#endif /**< #if LWIP_DNS */

    rt_exit_critical();
}
FINSH_FUNCTION_EXPORT(list_if, list network interface information);

#if LWIP_TCP
#include <lwip/tcp.h>
#include <lwip/tcp_impl.h>

void list_tcps(void)
{
    rt_uint32_t num = 0;
    struct tcp_pcb *pcb;
    char local_ip_str[16];
    char remote_ip_str[16];

    extern struct tcp_pcb *tcp_active_pcbs;
    extern union tcp_listen_pcbs_t tcp_listen_pcbs;
    extern struct tcp_pcb *tcp_tw_pcbs;
    extern const char *tcp_state_str[];

    rt_enter_critical();
    rt_kprintf("Active PCB states:\n");
    for(pcb = tcp_active_pcbs; pcb != NULL; pcb = pcb->next)
    {
        strcpy(local_ip_str, ipaddr_ntoa(&(pcb->local_ip)));
        strcpy(remote_ip_str, ipaddr_ntoa(&(pcb->remote_ip)));

        rt_kprintf("#%d %s:%d <==> %s:%d snd_nxt 0x%08X rcv_nxt 0x%08X ",
                   num++,
                   local_ip_str,
                   pcb->local_port,
                   remote_ip_str,
                   pcb->remote_port,
                   pcb->snd_nxt,
                   pcb->rcv_nxt);
        rt_kprintf("state: %s\n", tcp_state_str[pcb->state]);
    }

    rt_kprintf("Listen PCB states:\n");
    num = 0;
    for(pcb = (struct tcp_pcb *)tcp_listen_pcbs.pcbs; pcb != NULL; pcb = pcb->next)
    {
        rt_kprintf("#%d local port %d ", num++, pcb->local_port);
        rt_kprintf("state: %s\n", tcp_state_str[pcb->state]);
    }

    rt_kprintf("TIME-WAIT PCB states:\n");
    num = 0;
    for(pcb = tcp_tw_pcbs; pcb != NULL; pcb = pcb->next)
    {
        strcpy(local_ip_str, ipaddr_ntoa(&(pcb->local_ip)));
        strcpy(remote_ip_str, ipaddr_ntoa(&(pcb->remote_ip)));

        rt_kprintf("#%d %s:%d <==> %s:%d snd_nxt 0x%08X rcv_nxt 0x%08X ",
                   num++,
                   local_ip_str,
                   pcb->local_port,
                   remote_ip_str,
                   pcb->remote_port,
                   pcb->snd_nxt,
                   pcb->rcv_nxt);
        rt_kprintf("state: %s\n", tcp_state_str[pcb->state]);
    }
    rt_exit_critical();
}
FINSH_FUNCTION_EXPORT(list_tcps, list all of tcp connections);
#endif

#if LWIP_UDP
#include "lwip/udp.h"
void list_udps(void)
{
    struct udp_pcb *pcb;
    rt_uint32_t num = 0;
    char local_ip_str[16];
    char remote_ip_str[16];

    rt_enter_critical();
    rt_kprintf("Active UDP PCB states:\n");
    for (pcb = udp_pcbs; pcb != NULL; pcb = pcb->next)
    {
        strcpy(local_ip_str, ipaddr_ntoa(&(pcb->local_ip)));
        strcpy(remote_ip_str, ipaddr_ntoa(&(pcb->remote_ip)));

        rt_kprintf("#%d %d %s:%d <==> %s:%d \n",
                   num, (int)pcb->flags,
                   local_ip_str,
                   pcb->local_port,
                   remote_ip_str,
                   pcb->remote_port);

        num++;
    }
    rt_exit_critical();
}
FINSH_FUNCTION_EXPORT(list_udps, list all of udp connections);
#endif /* LWIP_UDP */

#endif
