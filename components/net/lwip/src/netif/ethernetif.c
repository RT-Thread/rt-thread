/*
 * File      : ethernetif.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-07-07     Bernard      fix send mail to mailbox issue.
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
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

/* configurations */
#ifndef RT_LWIP_ETHTHREAD_PRIORITY
#define RT_LWIP_ETHTHREAD_PRIORITY 0x90
#endif

#ifndef RT_LWIP_ETHTHREAD_MBOX_SIZE
#define RT_LWIP_ETHTHREAD_MBOX_SIZE 48
#endif

#ifndef RT_LWIP_ETHTHREAD_STACKSIZE
#define RT_LWIP_ETHTHREAD_STACKSIZE 1024
#endif


/* eth rx thread */
static struct rt_mailbox eth_rx_thread_mb;
static struct rt_thread eth_rx_thread;

static char eth_rx_thread_mb_pool[RT_LWIP_ETHTHREAD_MBOX_SIZE * 4];
static char eth_rx_thread_stack[RT_LWIP_ETHTHREAD_STACKSIZE];


/* Ugly hacks for old drivers compatible */
/* ===================================== */
#if 1
static struct eth_device * ptmpdev;
struct eth_device * get_eth_dev(void)
{
	return ptmpdev;
}
int eth_device_init(struct eth_device * dev, char *name)
{
	ptmpdev = dev;
	dev->parent.type = RT_Device_Class_NetIf;
	rt_device_register(&(dev->parent), "eth0", RT_DEVICE_FLAG_RDWR);
	return 0;
}
void lwip_sys_init(void)
{
	lwip_enetif_init();
}
void eth_system_device_init()
{
}
rt_err_t eth_device_ready(struct eth_device* dev)
{
	return eth_rx_ready(dev);
}
#endif
/* ===================================== */



/* ethernet buffer */
static void eth_rx_thread_entry(void* parameter)
{
	struct eth_device* device;

	while (1)
	{
		if (rt_mb_recv(&eth_rx_thread_mb, (rt_uint32_t*)&device, RT_WAITING_FOREVER) == RT_EOK)
 		{
			struct pbuf *p;

			/* receive all of buffer */
			while (1)
			{
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



static err_t enetif_linkoutput(struct netif *pnetif, struct pbuf *p)
{
	struct eth_device *dev;

	dev = (struct eth_device *)(pnetif->state);
	return dev->eth_tx(&(dev->parent), p);
}


static err_t enetif_init(struct netif *pnetif)
{
	rt_err_t result = RT_EOK;
	struct eth_device *dev;
	rt_uint32_t level;

	/* init rx thread.
	 * init mailbox and create ethernet thread */
	result = rt_mb_init(&eth_rx_thread_mb, "erxmb",
		&eth_rx_thread_mb_pool[0], sizeof(eth_rx_thread_mb_pool)/4,
		RT_IPC_FLAG_FIFO);
	RT_ASSERT(result == RT_EOK);

	result = rt_thread_init(&eth_rx_thread, "erx", eth_rx_thread_entry, RT_NULL,
		&eth_rx_thread_stack[0], sizeof(eth_rx_thread_stack),
		RT_LWIP_ETHTHREAD_PRIORITY, 16);
	RT_ASSERT(result == RT_EOK);

	result = rt_thread_startup(&eth_rx_thread);
	RT_ASSERT(result == RT_EOK);


	dev = (struct eth_device *)(pnetif->state);

	pnetif->name[0] = dev->parent.parent.name[0];
	pnetif->name[1] = dev->parent.parent.name[1];

	pnetif->hwaddr_len	= 6;
	pnetif->mtu			= ETHERNET_MTU;
	pnetif->flags		= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;

#ifdef LWIP_IGMP
	pnetif->flags |= NETIF_FLAG_IGMP;
#endif

#ifdef LWIP_DHCP
	pnetif->flags |= NETIF_FLAG_DHCP;
#endif

	/* get hardware address */
	rt_device_control(&(dev->parent), NIOCTL_GADDR, pnetif->hwaddr);

	/* set output */
	pnetif->output		= etharp_output;
	pnetif->linkoutput	= enetif_linkoutput;

	/* finally, we connect netif and device together.
	 * We initialized eth_device first, but ethernetif is still not ready.
	 * Although we checked if dev->netif is null but we still must avoid
	 * concurrency problem here.*/
	level = rt_hw_interrupt_disable();
	dev->netif = pnetif;
	rt_hw_interrupt_enable(level);

	return ERR_OK;
}

rt_err_t eth_rx_ready(struct eth_device* dev)
{
	if (dev->netif)
		/* post message to ethernet thread */
		return rt_mb_send(&eth_rx_thread_mb, (rt_uint32_t)dev);
	else
		return ERR_OK; /* netif is not initialized yet, just return. */
}

/* Functions below shouldn't be here because they are application or usage related.
 * I just give an example of a right power-on procedure here. */
static struct netif ethernetif;
extern struct eth_device * get_eth_dev(void);

/* This function is called-back in tcpip thread, so we don't need to use msg api
 * to call those netif_xxx functions. But if we use these anywhere else, we must
 * use msg api to avoid concurrent problem.
 */
static void tcpip_init_done_callback(void *arg)
{
	ip_addr_t ipaddr, netmask, gw;

	LWIP_ASSERT("invalid arg.\n",arg);

#if LWIP_DHCP
	IP4_ADDR(&gw, 0,0,0,0);
	IP4_ADDR(&ipaddr, 0,0,0,0);
	IP4_ADDR(&netmask, 0,0,0,0);
#else
	IP4_ADDR(&ipaddr, RT_LWIP_IPADDR0, RT_LWIP_IPADDR1, RT_LWIP_IPADDR2, RT_LWIP_IPADDR3);
	IP4_ADDR(&gw, RT_LWIP_GWADDR0, RT_LWIP_GWADDR1, RT_LWIP_GWADDR2, RT_LWIP_GWADDR3);
	IP4_ADDR(&netmask, RT_LWIP_MSKADDR0, RT_LWIP_MSKADDR1, RT_LWIP_MSKADDR2, RT_LWIP_MSKADDR3);
#endif

	netif_add(&ethernetif, &ipaddr, &netmask, &gw, 
		get_eth_dev(), enetif_init, tcpip_input);

	netif_set_default(&ethernetif);

#if LWIP_DHCP
	dhcp_start(&ethernetif);
#else
	netif_set_up(&ethernetif);
#endif

	netif_set_link_up(&ethernetif);
	
	sys_sem_signal((sys_sem_t*)(&arg));
}


/* Make sure the 'dev' has already been initialized before calling this function.
 * This function will initialize the lwip tcpip stack as well as the ethernetif.
 * It will assign the dev->netif and netif->state field to make a connection between
 * eth driver and ethnetif.
 */
void lwip_enetif_init(void)
{
	sys_sem_t init_done_sem;

	if(sys_sem_new(&init_done_sem, 0) != ERR_OK)
	{
    	LWIP_ASSERT("Failed to create semaphore", 0);
		return;
	}
	tcpip_init(tcpip_init_done_callback,(void *)init_done_sem);

	sys_sem_wait(&init_done_sem);
	rt_kprintf("TCP/IP initialized.\n");

	sys_sem_free(&init_done_sem);
}

#if 0
#ifdef RT_USING_FINSH
#include <finsh.h>
#include "ipv4/lwip/inet.h"
void set_if(char* ip_addr, char* gw_addr, char* nm_addr)
{
	struct ip_addr *ip;
	struct in_addr addr;

	ip = (struct ip_addr *)&addr;

	/* set ip address */
	if ((ip_addr != RT_NULL) && inet_aton(ip_addr, &addr))
	{
		netif_set_ipaddr(netif_default, ip);
	}

	/* set gateway address */
	if ((gw_addr != RT_NULL) && inet_aton(gw_addr, &addr))
	{
		netif_set_gw(netif_default, ip);
	}

	/* set netmask address */
	if ((nm_addr != RT_NULL) && inet_aton(nm_addr, &addr))
	{
		netif_set_netmask(netif_default, ip);
	}
}
FINSH_FUNCTION_EXPORT(set_if, set network interface address);

#if LWIP_DNS
#include <lwip/dns.h>
void set_dns(char* dns_server)
{
	struct in_addr addr;
	
	if ((dns_server != RT_NULL) && inet_aton(dns_server, &addr))
	{
		dns_setserver(0, (struct ip_addr *)&addr);
	}
}
FINSH_FUNCTION_EXPORT(set_dns, set DNS server address);
#endif

void list_if()
{
	rt_kprintf("Default network interface: %c%c\n", netif_default->name[0], netif_default->name[1]);
	rt_kprintf("ip address: %s\n", inet_ntoa(*((struct in_addr*)&(netif_default->ip_addr))));
	rt_kprintf("gw address: %s\n", inet_ntoa(*((struct in_addr*)&(netif_default->gw))));
	rt_kprintf("net mask  : %s\n", inet_ntoa(*((struct in_addr*)&(netif_default->netmask))));

#if LWIP_DNS
	{
		struct ip_addr ip_addr;

		ip_addr = dns_getserver(0);
		rt_kprintf("dns server: %s\n", inet_ntoa(*((struct in_addr*)&(ip_addr))));
	}
#endif
}
FINSH_FUNCTION_EXPORT(list_if, list network interface information);
#endif
#endif
