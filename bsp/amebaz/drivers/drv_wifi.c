/*
 * File      : drv_wifi.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-5-30      Bernard      the first version
 * 2018-5-30      flyingcys    add amebaz wifi driver
 */

#include <rtthread.h>
#include <wlan_dev.h>
#include <skbuff.h>

#include "amebaz_wlan.h"

//#define ETH_RX_DUMP
//#define ETH_TX_DUMP
//#define MINI_DUMP

struct sk_buff * rltk_wlan_get_recv_skb(int idx);
struct sk_buff * rltk_wlan_alloc_skb(unsigned int total_len);

#define     MAX_ADDR_LEN        6

struct ameba_wifi
{
    struct rt_wlan_device parent;

    rt_uint8_t dev_addr[MAX_ADDR_LEN];
    
    int idx;
    int connected;
};

#ifdef RT_USING_WLAN_STA
static struct ameba_wifi wifi_sta;
#endif

#ifdef RT_USING_WLAN_AP
static struct ameba_wifi wifi_ap;
#endif

#if defined(ETH_RX_DUMP) ||  defined(ETH_TX_DUMP)
static void packet_dump(const char *msg, const struct pbuf *p)
{
    const struct pbuf *q;
    rt_uint32_t i, j;
    rt_uint8_t *ptr;

    rt_kprintf("%s %d byte\n", msg, p->tot_len);

#ifdef MINI_DUMP
	return;
#endif

    i = 0;
    for (q = p; q != RT_NULL; q = q->next)
    {
        ptr = q->payload;

        for (j = 0; j < q->len; j++)
        {
            if ((i % 8) == 0)
            {
                rt_kprintf("  ");
            }
            
            if ((i % 16) == 0)
            {
                rt_kprintf("\r\n");
            }
            rt_kprintf("%02x ", *ptr);

            i++;
            ptr++;
        }
    }

    rt_kprintf("\n\n");
}
#endif /* dump */

#define netifapi_netif_set_link_up(n)      netifapi_netif_common(n, netif_set_link_up, NULL)
#define netifapi_netif_set_link_down(n)    netifapi_netif_common(n, netif_set_link_down, NULL)

void netif_set_connected(int connected)
{
    wifi_sta.connected = connected;
    if (connected)
    {
        netifapi_netif_set_link_up(wifi_sta.parent.parent.netif);
    }
    else
    {
        netifapi_netif_set_link_down(wifi_sta.parent.parent.netif);
    }
} 

void rltk_wlan_set_netif_info(int idx_wlan, void * dev, unsigned char * dev_addr)
{
    struct ameba_wifi *wifi;
    
    if(idx_wlan == 0)
         wifi = &wifi_sta;
    
    rtw_memcpy(wifi->dev_addr, dev_addr, 6);
    rt_hw_wifi_init();
}

void netif_rx(int idx, unsigned int len)
{
    struct ameba_wifi *wifi;
	struct pbuf *p, *q;
	int sg_len = 0;
	struct sk_buff *skb = RT_NULL;

    if(idx == 0)
         wifi = &wifi_sta;
    
#if CONFIG_WLAN
    if(!wifi->connected || !rltk_wlan_running(idx))
        return;
#endif

    skb = rltk_wlan_get_recv_skb(idx);
    if(!skb)
    {
        rt_kprintf("netif_rx rltk_wlan_get_recv_skb NULL.\n");
        return;
    }
    
	p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
	if (p != RT_NULL)
	{
        pbuf_take(p, skb->data, len);
        skb_pull(skb, len);
        
#ifdef ETH_RX_DUMP
        packet_dump("RX dump", p);
#endif /* ETH_RX_DUMP */

        if(wifi->parent.parent.netif->input(p, wifi->parent.parent.netif) != ERR_OK)
        {
            pbuf_free(p);
        }
    }
    else
    {
		rt_kprintf("pbuf_alloc NULL for wifi RX.\n");
	}
}
      
int netif_is_valid_IP(int idx, unsigned char *ip_dest)
{

	struct netif * pnetif;
	struct ip_addr addr = { 0 };
	u32_t *ip_dest_addr  = (u32_t*)ip_dest;

    if(idx == 0)
        pnetif = wifi_sta.parent.parent.netif;
    
	addr.addr = *ip_dest_addr;

    if(pnetif == RT_NULL)
        return 0;
    
	if(pnetif->ip_addr.addr == 0)
		return 1;
	
	if(ip_addr_ismulticast(&addr) || ip_addr_isbroadcast(&addr,pnetif))
    {
		return 1;
	}
		
	if(ip_addr_cmp(&(pnetif->ip_addr), &addr))
		return 1;

	return 0;
}
       
void netif_post_sleep_processing(void)
{

}

void netif_pre_sleep_processing(void)
{

}

unsigned char *rltk_wlan_get_ip(int idx)
{
    struct ameba_wifi *wifi;

    if(idx == 0)
        wifi = &wifi_sta;

    return (unsigned char *)&(wifi->parent.parent.netif->ip_addr);
}

struct netif *rltk_wlan_get_netif(int idx)
{
    struct netif *netif;
    
    if(idx == 0)
        netif = wifi_sta.parent.parent.netif;
    else if(idx == 1)
        netif = wifi_ap.parent.parent.netif;

    return netif;
}


rt_err_t rt_ameba_wifi_init(rt_device_t dev)
{
    return RT_EOK;
}

rt_err_t rt_ameba_wifi_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

rt_err_t rt_ameba_wifi_close(rt_device_t dev)
{
    return RT_EOK;
}

rt_size_t rt_ameba_wifi_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

rt_size_t rt_ameba_wifi_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

rt_err_t  rt_ameba_wifi_control(rt_device_t dev, int cmd, void *args)
{
    switch(cmd)
    {
    case NIOCTL_GADDR:
    {
        struct ameba_wifi *wifi = (struct ameba_wifi *)dev;
        if(args)
            memcpy(args, wifi->dev_addr, MAX_ADDR_LEN);
        else
            return -RT_ERROR;
    }
        break;

    case WIFI_INIT:
    {
        rt_wlan_mode_t mode = *(rt_wlan_mode_t *)args;
        rt_kprintf("mode:%d\n", mode);
    }
        break;    

    case WIFI_SCAN:
    {
        struct rt_wlan_scan_result *dst = RT_NULL;
        dst = (struct rt_wlan_scan_result *)rt_malloc(sizeof(struct rt_wlan_scan_result));
        if(dst == RT_NULL)
        {
            rt_kprintf("rt_malloc for scan result failed!\n");
            return -RT_ENOMEM;
        }

        memset(dst, 0, sizeof(struct rt_wlan_scan_result));
        if(amebaz_wifi_scan(dst) != RT_EOK)
        {
            rt_kprintf("amebaz_wifi_scan failed...\n");
            return -RT_ERROR;
        }

        *(struct rt_wlan_scan_result **)args = dst;
    }
        break;

    case WIFI_JOIN:
        
        break;
    
    case WIFI_EASYJOIN:
    {
        struct rt_wlan_device *wlan = (struct rt_wlan_device *)dev;
        if(amebaz_wifi_connect(wlan->info->ssid, (char *)args) != RT_EOK)
        {
            rt_kprintf("amebaz_wifi_connect failed...\n");
            return -RT_ERROR;
        }
    }
        break;
        
    case WIFI_SOFTAP:
    {
        struct rt_wlan_device *wlan = (struct rt_wlan_device *)dev;
        if(amebaz_wifi_ap_start(wlan->info->ssid, (char *)args, wlan->info->channel) != RT_EOK)
        {
            rt_kprintf("amebaz_wifi_ap_start failed...\n");
            return -RT_ERROR;
        }
    }
        break;
        
    case WIFI_DISCONNECT:
        if(amebaz_wifi_disconnect() != RT_EOK)
        {
            rt_kprintf("amebaz_wifi_disconnect failed...\n");
            return -RT_ERROR;
        }
        break;
        
    case WIFI_GET_RSSI:
    {
        int *rssi = (int *)args;
        
        *rssi = amebaz_wifi_get_rssi();
    }
        break;
        
    case WIFI_ENTER_POWERSAVE:
        
        break;
        
    case WIFI_CFG_MONITOR:

        break;
        
    case WIFI_SET_CHANNEL:
    {
        int channel = *(int *)args;
        
        amebaz_wifi_set_channel(channel);
    }
        break;
        
    case WIFI_GET_CHANNEL:
    {
        int *channel = (int *)args;

        *channel = amebaz_wifi_get_channel();
    }
        break;
        
    case WIFI_SET_MONITOR_CALLBACK:
        
        break;
    }

    return RT_EOK;
}

rt_err_t rt_ameba_wifi_tx(rt_device_t dev, struct pbuf* p)
{
    rt_err_t result = RT_EOK;
    struct ameba_wifi *wifi = (struct ameba_wifi *)dev;
    int idx;
    rt_base_t level;
	struct sk_buff *skb = RT_NULL;

    idx = wifi->idx;

    level = rt_hw_interrupt_disable();
	if(wifi->connected && rltk_wlan_check_isup(idx))
		rltk_wlan_tx_inc(idx);
    else
    {
        rt_hw_interrupt_enable(level);
//		rt_kprintf("is not: connected && rltk_wlan_check_isup(idx)\n");

        result = -RT_ERROR;
        goto _exit;
    }

    rt_hw_interrupt_enable(level);
    
#ifdef ETH_TX_DUMP
    packet_dump("TX dump", p);
#endif /* ETH_TX_DUMP */

    skb = rltk_wlan_alloc_skb(p->tot_len); 
    if(skb != RT_NULL)
    {
		/* copy pbuf to a whole ETH frame */
		pbuf_copy_partial(p, skb->tail, p->tot_len, 0);
        skb_put(skb, p->tot_len);
        
    	rltk_wlan_send_skb(idx, skb);
    }
	else
	{
		rt_kprintf("rltk_wlan_alloc_skb NULL for WIFI TX.\n");
        result = -RT_ENOMEM;
	}

_exit:  
    level = rt_hw_interrupt_disable();
    rltk_wlan_tx_dec(idx);
    rt_hw_interrupt_enable(level);
    
    return result;
}

int rt_hw_wifi_init(void)
{
    rt_kprintf("%s %d\n", __FUNCTION__, __LINE__);
    
#ifdef RT_USING_WLAN_STA
    wifi_sta.parent.parent.parent.init = rt_ameba_wifi_init;
    wifi_sta.parent.parent.parent.open = rt_ameba_wifi_open;
    wifi_sta.parent.parent.parent.close = rt_ameba_wifi_close;
    wifi_sta.parent.parent.parent.read = rt_ameba_wifi_read;
    wifi_sta.parent.parent.parent.write = rt_ameba_wifi_write;
    wifi_sta.parent.parent.parent.control = rt_ameba_wifi_control;
    wifi_sta.parent.parent.parent.user_data = RT_NULL;
    //
    wifi_sta.idx = 0;
    //
    wifi_sta.parent.parent.eth_rx = RT_NULL;
    wifi_sta.parent.parent.eth_tx = rt_ameba_wifi_tx;

    /* register wifi device */
    eth_device_init(&wifi_sta.parent.parent, WIFI_DEVICE_STA_NAME);   
#endif

#ifdef RT_USING_WLAN_AP

#endif
    
    return RT_EOK;
}

