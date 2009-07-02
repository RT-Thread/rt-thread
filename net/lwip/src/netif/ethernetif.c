#include <rtthread.h>

#include "lwip/debug.h"
#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include "lwip/netif.h"
#include "lwip/stats.h"
#include "lwip/tcpip.h"

#include "netif/etharp.h"
#include "netif/ethernetif.h"

/* eth rx/tx thread */
static struct rt_mailbox eth_rx_thread_mb;
static struct rt_thread eth_rx_thread;
#ifndef RT_LWIP_ETHTHREAD_PRIORITY
#define RT_ETHERNETIF_THREAD_PREORITY	0x90
static char eth_rx_thread_mb_pool[48 * 4];
static char eth_rx_thread_stack[1024];
#else
#define RT_ETHERNETIF_THREAD_PREORITY	RT_LWIP_ETHTHREAD_PRIORITY
static char eth_rx_thread_mb_pool[RT_LWIP_ETHTHREAD_MBOX_SIZE * 4];
static char eth_rx_thread_stack[RT_LWIP_ETHTHREAD_STACKSIZE];
#endif

struct eth_tx_msg
{
	struct netif 	*netif;
	struct pbuf 	*buf;
};
static struct rt_mailbox eth_tx_thread_mb;
static struct rt_thread eth_tx_thread;
#ifndef RT_LWIP_ETHTHREAD_PRIORITY
static char eth_tx_thread_mb_pool[32 * 4];
static char eth_tx_thread_stack[512];
#else
static char eth_tx_thread_mb_pool[RT_LWIP_ETHTHREAD_MBOX_SIZE * 4];
static char eth_tx_thread_stack[RT_LWIP_ETHTHREAD_STACKSIZE];
#endif

/* the interface provided to LwIP */
err_t eth_init(struct netif *netif)
{
	return ERR_OK;
}

err_t eth_input(struct pbuf *p, struct netif *inp)
{
	struct eth_hdr *ethhdr;

	if(p != RT_NULL)
	{
#ifdef LINK_STATS
		LINK_STATS_INC(link.recv);
#endif /* LINK_STATS */

		ethhdr = p->payload;

		switch(htons(ethhdr->type))
		{
		case ETHTYPE_IP:
			etharp_ip_input(inp, p);
			pbuf_header(p, -14);
			tcpip_input(p, inp);
			break;

		case ETHTYPE_ARP:
			etharp_arp_input(inp, (struct eth_addr *)inp->hwaddr, p);
			break;

		default:
			pbuf_free(p);
			p = RT_NULL;
			break;
		}
	}

	return ERR_OK;
}

err_t ethernetif_output(struct netif *netif, struct pbuf *p, struct ip_addr *ipaddr)
{
	return etharp_output(netif, p, ipaddr);
}

err_t ethernetif_linkoutput(struct netif *netif, struct pbuf *p)
{
	struct eth_tx_msg msg;
	struct eth_device* enetif;
	
	enetif = (struct eth_device*)netif->state;

	/* send a message to eth tx thread */
	msg.netif = netif;
	msg.buf   = p;
	rt_mb_send(&eth_tx_thread_mb, (rt_uint32_t) &msg);
	
	/* waiting for ack */
	rt_sem_take(&(enetif->tx_ack), RT_WAITING_FOREVER);

	return ERR_OK;
}

/* ethernetif APIs */
rt_err_t eth_device_init(struct eth_device* dev, const char* name)
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
	/* register to rt-thread device manager */
	rt_device_register(&(dev->parent), name, RT_DEVICE_FLAG_RDWR);
	dev->parent.type = RT_Device_Class_NetIf;
	rt_sem_init(&(dev->tx_ack), name, 0, RT_IPC_FLAG_FIFO);

	/* set name */
	netif->name[0] = name[0];
	netif->name[1] = name[1];

	/* set hw address to 6 */
	netif->hwaddr_len	= 6;
	/* maximum transfer unit */
	netif->mtu			= ETHERNET_MTU;
	/* broadcast capability */
	netif->flags		= NETIF_FLAG_BROADCAST;

	/* get hardware address */
	rt_device_control(&(dev->parent), NIOCTL_GADDR, netif->hwaddr);

	/* set output */
	netif->output		= ethernetif_output;
	netif->linkoutput	= ethernetif_linkoutput;

	/* add netif to lwip */
	if (netif_add(netif, IP_ADDR_ANY, IP_ADDR_BROADCAST, IP_ADDR_ANY, dev,
		eth_init, eth_input) == RT_NULL)
	{
		/* failed, unregister device and free netif */
		rt_device_unregister(&(dev->parent));
		rt_free(netif);
		return -RT_ERROR;
	}

	netif_set_default(netif);

	return RT_EOK;
}

/* ethernet buffer */
void eth_tx_thread_entry(void* parameter)
{
	struct eth_tx_msg* msg;

	while (1)
	{
		if (rt_mb_recv(&eth_tx_thread_mb, (rt_uint32_t*)&msg, RT_WAITING_FOREVER) == RT_EOK)
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
					rt_kprintf("transmit eth packet failed\n");
				}
			}

			/* send ack */
			rt_sem_release(&(enetif->tx_ack));
		}
	}
}

/* ethernet buffer */
void eth_rx_thread_entry(void* parameter)
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
					eth_input(p, device->netif);
				}
				else break;
			}
		}
	}
}

rt_err_t eth_device_ready(struct eth_device* dev)
{
	/* post message to ethernet thread */
	return rt_mb_send(&eth_rx_thread_mb, (rt_uint32_t)dev);
}

rt_err_t eth_system_device_init()
{
	rt_err_t result = RT_EOK;

	/* init rx thread */
	/* init mailbox and create ethernet thread */
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

	/* init tx thread */
	/* init mailbox and create ethernet thread */
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

	return result;
}
