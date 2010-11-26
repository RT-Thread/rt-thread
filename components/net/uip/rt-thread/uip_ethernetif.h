#ifndef __NETIF_ETHERNETIF_H__
#define __NETIF_ETHERNETIF_H__

//#include "lwip/netif.h"
#include "uip_netif.h"
#include <rtthread.h>

#define NIOCTL_GADDR		0x01
#define ETHERNET_MTU		1500

struct eth_device
{
	/* inherit from rt_device */
	struct rt_device parent;

	struct eth_addr *ethaddr;
	struct netif *netif;
	struct rt_semaphore tx_ack;

	/* eth device interface */
	struct pbuf* (*eth_rx)(rt_device_t dev);
	rt_err_t (*eth_tx)(rt_device_t dev, struct pbuf* p);
};

rt_err_t eth_device_ready(struct eth_device* dev);

rt_err_t eth_device_init(struct eth_device* dev, const char* name);

rt_err_t eth_system_device_init(void);

#endif /* __NETIF_ETHERNETIF_H__ */
