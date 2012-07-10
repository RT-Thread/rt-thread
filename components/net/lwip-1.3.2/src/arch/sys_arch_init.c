#include <rtthread.h>

#include "lwip/debug.h"
#include "lwip/mem.h"
#include "lwip/sys.h"
#include "lwip/stats.h"
#include "lwip/tcpip.h"
#include "lwip/ip_addr.h"
#include "lwip/dhcp.h"

#include "netif/ethernetif.h"
#include "netif/etharp.h"

static err_t netif_device_init(struct netif *netif)
{
	struct eth_device *ethif;

	ethif = (struct eth_device*)netif->state;
	if (ethif != RT_NULL)
	{
		rt_device_t device;
		
		/* get device object */
		device = (rt_device_t) ethif;
		if (rt_device_init(device) != RT_EOK)
		{
			return ERR_IF;
		}
		return ERR_OK;
	}

	return ERR_IF;
}

static void tcpip_init_done_callback(void *arg)
{
	rt_device_t device;
	struct eth_device *ethif;
	struct ip_addr ipaddr, netmask, gw;
	struct rt_list_node* node;
	struct rt_object* object;
	struct rt_object_information *information;

	extern struct rt_object_information rt_object_container[];

	LWIP_ASSERT("invalid arg.\n",arg);

	IP4_ADDR(&gw, 0,0,0,0);
	IP4_ADDR(&ipaddr, 0,0,0,0);
	IP4_ADDR(&netmask, 0,0,0,0);

	/* enter critical */
	rt_enter_critical();

	/* for each network interfaces */
	information = &rt_object_container[RT_Object_Class_Device];
	for (node = information->object_list.next; node != &(information->object_list); node = node->next)
	{
		object = rt_list_entry(node, struct rt_object, list);
		device = (rt_device_t) object;
		if (device->type == RT_Device_Class_NetIf)
		{
			ethif = (struct eth_device*)device;

			/* leave critical */
			rt_exit_critical();

			netif_add(ethif->netif, &ipaddr, &netmask, &gw, 
				ethif, netif_device_init, tcpip_input);

			if (netif_default == RT_NULL)
				netif_set_default(ethif->netif);

#if LWIP_DHCP
			dhcp_start(ethif->netif);
#else
			netif_set_up(ethif->netif);
#endif

#ifdef LWIP_NETIF_LINK_CALLBACK
			netif_set_link_up(ethif->netif);
#endif

			/* enter critical */
			rt_enter_critical();
		}
	}

	/* leave critical */
	rt_exit_critical();

	rt_sem_release((rt_sem_t)arg);
}

/**
 * LwIP system initialization
 */
void lwip_system_init(void)
{
	rt_err_t rc;
	struct rt_semaphore done_sem;
	
	rc = rt_sem_init(&done_sem, "done", 0, RT_IPC_FLAG_FIFO);
	
	if(rc != RT_EOK)
	{
    	LWIP_ASSERT("Failed to create semaphore", 0);
		return;
	}

	tcpip_init(tcpip_init_done_callback,(void *)&done_sem);

	/* waiting for initialization done */
	if (rt_sem_take(&done_sem, RT_WAITING_FOREVER) != RT_EOK)
	{
		rt_sem_detach(&done_sem);
		return;
	}
	rt_sem_detach(&done_sem);

	/* set default ip address */
#if !LWIP_DHCP
	{
		struct ip_addr ipaddr, netmask, gw;

		IP4_ADDR(&ipaddr, RT_LWIP_IPADDR0, RT_LWIP_IPADDR1, RT_LWIP_IPADDR2, RT_LWIP_IPADDR3);
		IP4_ADDR(&gw, RT_LWIP_GWADDR0, RT_LWIP_GWADDR1, RT_LWIP_GWADDR2, RT_LWIP_GWADDR3);
		IP4_ADDR(&netmask, RT_LWIP_MSKADDR0, RT_LWIP_MSKADDR1, RT_LWIP_MSKADDR2, RT_LWIP_MSKADDR3);

		netifapi_netif_set_addr(netif_default, &ipaddr, &netmask, &gw);
	}
#endif
}

/**
 * Compatible with RT-Thread 0.2.x/0.3.x
 */
void lwip_sys_init(void)
{
	lwip_system_init();
}

