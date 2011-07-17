#ifndef __RT_WLAN_DEV_H__
#define __RT_WLAN_DEV_H__
#include <netif/ethernetif.h>
#include "lwipopts.h"
#include "wlan_types.h"
#define WLANMACADDRESSLENGTH (6)
//#define CMD
struct WLAN_IO_CTRL_PAR
{

    /** parameters Header */
    u16 inputlength;
    u16 outputlength;

    /** Command Body */
    union 
    {
	u8 MacAdd[MRVDRV_ETH_ADDR_LEN];
    } params;
};
struct rt_wlan_dev
{
    /* inherit from ethernet device */
    struct eth_device parent;
    void * 	priv ;
    unsigned int irq;
    char			name[16];
	char dev_addr[6];
};

int rt_hw_wlan_dev_init(void);
#endif
