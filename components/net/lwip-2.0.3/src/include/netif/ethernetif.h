#ifndef __NETIF_ETHERNETIF_H__
#define __NETIF_ETHERNETIF_H__

#include "lwip/netif.h"
#include <rtthread.h>

#define NIOCTL_GADDR		0x01
#ifndef RT_LWIP_ETH_MTU
#define ETHERNET_MTU		1500
#else
#define ETHERNET_MTU		RT_LWIP_ETH_MTU
#endif

/* eth flag with auto_linkup or phy_linkup */
#define ETHIF_LINK_AUTOUP	0x0000
#define ETHIF_LINK_PHYUP	0x0100

struct eth_device
{
    /* inherit from rt_device */
    struct rt_device parent;

    /* network interface for lwip */
    struct netif *netif;
    struct rt_semaphore tx_ack;

    rt_uint16_t flags;
    rt_uint8_t  link_changed;
    rt_uint8_t  link_status;
    rt_uint8_t  rx_notice;

    /* eth device interface */
    struct pbuf* (*eth_rx)(rt_device_t dev);
    rt_err_t (*eth_tx)(rt_device_t dev, struct pbuf* p);
};

#ifdef __cplusplus
extern "C" {
#endif

    rt_err_t eth_device_ready(struct eth_device* dev);
    rt_err_t eth_device_init(struct eth_device * dev, const char *name);
    rt_err_t eth_device_init_with_flag(struct eth_device *dev, const char *name, rt_uint16_t flag);
    rt_err_t eth_device_linkchange(struct eth_device* dev, rt_bool_t up);
    void eth_device_deinit(struct eth_device *dev);

    int eth_system_device_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __NETIF_ETHERNETIF_H__ */
