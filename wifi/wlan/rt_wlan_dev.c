#include <rtthread.h>
#include <netif/ethernetif.h>

#include "rt_wlan_dev.h"
#include "wlan_dev.h"
#include <rtthread.h>
 #define WLAN_DEV		1 
#if WLAN_DEV
#define DEV_TRACE 	rt_kprintf
#else
#define DEV_TRACE(...)
#endif

#define MAX_ADDR_LEN 6

static struct rt_wlan_dev wlan_eth;

extern int wlan_init_module(struct rt_wlan_dev * wlan_dev);
/* RT-Thread Device Interface */
/* initialize the interface */
static rt_err_t rt_wlan_dev_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_wlan_dev_open(rt_device_t dev, rt_uint16_t oflag)
{
	rt_err_t  error=RT_EOK;

	if(dev==RT_NULL||dev->user_data==RT_NULL)
	{
		error=-RT_EEMPTY;
		goto done;
	}
	
	
done:
	return error;
}

static rt_err_t rt_wlan_dev_close(rt_device_t dev)
{

	return RT_EOK;
}

static rt_size_t rt_wlan_dev_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_size_t rt_wlan_dev_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}
rt_err_t rt_wlan_dev_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	rt_err_t  error=RT_EOK;
	struct rt_wlan_dev * wlan_dev;
	wlan_private *priv = NULL;
	struct WLAN_IO_CTRL_PAR * par;
		char addressbuf[6]={0xff,0xff,0xff,0xff,0xff,0xff};
	if(dev==RT_NULL||dev->user_data==RT_NULL)
	{
		error=-RT_EEMPTY;
		goto done;
	}
	wlan_dev=dev->user_data;
	priv=wlan_dev->priv;
	switch (cmd)
	{
	case NIOCTL_GADDR:
		/* get mac address */
		//if (args) rt_memcpy(args, dm9000_device.dev_addr, 6);
		//else return -RT_ERROR;
	
		
		if(rt_memcmp(priv->adapter->CurrentAddr,addressbuf,6)==0)
		{
			error=-RT_ERROR;
			break;
		}
		else{
			rt_memcpy((u8*)args,priv->adapter->CurrentAddr,6);
		
		}
		break;

	default :
		break;
	}
done:
	return error;
}
/* ethernet device interface */
/* transmit packet. */
extern void
netif_set_addr(struct netif *netif, struct ip_addr *ipaddr, struct ip_addr *netmask,
    struct ip_addr *gw);
int wlan_set_addr(rt_uint32_t ipaddr,rt_uint32_t mask,rt_uint32_t gwaddr)
{
	struct ip_addr myip,gwip,maskip;
	   /*	myip 192.168.1.66->C0,A8,1,42*/
    myip.addr=ipaddr;
   	/*gwip 192.168.1.1->C0,A8,1,1	*/
    gwip.addr=gwaddr;
	/*maskip255.255.255.0,FF,FF,FF,0*/
    maskip.addr=mask;
	netif_set_addr(wlan_eth.parent.netif,&myip,&maskip,&gwip);
}
extern rt_err_t rt_wlan_dev_tx( rt_device_t dev, struct pbuf* p);
extern  struct pbuf *rt_wlan_dev_rx(rt_device_t dev);
int rt_hw_wlan_dev_init(void)
{

	rt_int32_t value=0;
	rt_err_t  error=RT_EOK;

	/*
	 * SRAM Tx/Rx pointer automatically return to start address,
	 * Packet Transmitted, Packet Received
	 */
	wlan_eth.parent.parent.init	   	   = rt_wlan_dev_init;
	wlan_eth.parent.parent.open	   = rt_wlan_dev_open;
	wlan_eth.parent.parent.close	   = rt_wlan_dev_close;
	wlan_eth.parent.parent.read	   = rt_wlan_dev_read;
	wlan_eth.parent.parent.write	   = rt_wlan_dev_write;
	wlan_eth.parent.parent.control	   = rt_wlan_dev_control;
	wlan_eth.parent.parent.user_data  =(void *)&wlan_eth ;

	wlan_eth.parent.eth_rx	 = rt_wlan_dev_rx;
	wlan_eth.parent.eth_tx	 = rt_wlan_dev_tx;
	value=gspihost_init();
	if(value<0)
	{
		error=-RT_ERROR;
		goto done;
	}
	value=wlan_init_module(&wlan_eth);
	if(value<0)
	{
		error=-RT_ERROR;
		goto done;
	}
	eth_device_init(&(wlan_eth.parent), "wlan_eth0");
done:
	return error;	

}


