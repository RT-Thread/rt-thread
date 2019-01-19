/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-14     tyx          the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <wlan_dev.h>
#include <wlan_prot.h>
#include <wlan_workqueue.h>

#ifdef RT_USING_LWIP
#include <netif/ethernetif.h>
#include <lwip/netifapi.h>
#ifdef LWIP_USING_DHCPD
#include <dhcp_server.h>
#endif

#define DBG_ENABLE
#ifdef RT_WLAN_LWIP_DEBUG
#define DBG_LEVEL DBG_LOG
#else
#define DBG_LEVEL DBG_INFO
#endif
#define DBG_SECTION_NAME  "WLAN.lwip"
#define DBG_COLOR
#include <rtdbg.h>

#ifndef IPADDR_STRLEN_MAX
#define IPADDR_STRLEN_MAX    (32)
#endif

struct lwip_prot_des
{
    struct rt_wlan_prot prot;
    struct eth_device eth;
    rt_int8_t connected_flag;
    struct rt_timer timer;
    struct rt_work work;
};

static void netif_is_ready(struct rt_work *work, void *parameter)
{
    ip_addr_t ip_addr_zero = { 0 };
    struct rt_wlan_device *wlan = parameter;
    struct lwip_prot_des *lwip_prot = (struct lwip_prot_des *)wlan->prot;
    struct eth_device *eth_dev = &lwip_prot->eth;
    rt_base_t level;
    struct rt_wlan_buff buff;
    rt_uint32_t ip_addr[4];
    char str[IPADDR_STRLEN_MAX];

    rt_timer_stop(&lwip_prot->timer);
    if (ip_addr_cmp(&(eth_dev->netif->ip_addr), &ip_addr_zero) != 0)
    {
        rt_timer_start(&lwip_prot->timer);
        goto exit;
    }
    rt_memset(&ip_addr, 0, sizeof(ip_addr));
#if LWIP_IPV4 && LWIP_IPV6
    if (eth_dev->netif->ip_addr.type == IPADDR_TYPE_V4)
    {
        ip_addr[0] = ip4_addr_get_u32(&eth_dev->netif->ip_addr.u_addr.ip4);
        buff.data = &ip_addr[0];
        buff.len = sizeof(ip_addr[0]);
    }
    else if (eth_dev->netif->ip_addr.type == IPADDR_TYPE_V6)
    {
        *(ip6_addr_t *)(&ip_addr[0]) = eth_dev->netif->ip_addr.u_addr.ip6;
        buff.data = ip_addr;
        buff.len = sizeof(ip_addr);
    }
    else
    {
        LOG_W("F:%s L:%d ip addr type not support", __FUNCTION__, __LINE__);
    }
#else
#if LWIP_IPV4
    ip_addr[0] = ip4_addr_get_u32(&eth_dev->netif->ip_addr);
    buff.data = &ip_addr[0];
    buff.len = sizeof(ip_addr[0]);
#else
    *(ip_addr_t *)(&ip_addr[0]) = eth_dev->netif->ip_addr;
    buff.data = ip_addr;
    buff.len = sizeof(ip_addr);
#endif
#endif
    if (rt_wlan_prot_ready(wlan, &buff) != 0)
    {
        rt_timer_start(&lwip_prot->timer);
        goto exit;
    }
    rt_memset(str, 0, IPADDR_STRLEN_MAX);
    rt_enter_critical();
    rt_memcpy(str, ipaddr_ntoa(&(eth_dev->netif->ip_addr)), IPADDR_STRLEN_MAX);
    rt_exit_critical();
    LOG_I("Got IP address : %s", str);
exit:
    level = rt_hw_interrupt_disable();
    rt_memset(work, 0, sizeof(struct rt_work));
    rt_hw_interrupt_enable(level);
}

static void timer_callback(void *parameter)
{
    struct rt_workqueue *workqueue;
    struct rt_wlan_device *wlan = parameter;
    struct lwip_prot_des *lwip_prot = (struct lwip_prot_des *)wlan->prot;
    struct rt_work *work = &lwip_prot->work;
    rt_base_t level;

    workqueue = rt_wlan_get_workqueue();
    if (workqueue != RT_NULL)
    {
        level = rt_hw_interrupt_disable();
        rt_work_init(work, netif_is_ready, parameter);
        rt_hw_interrupt_enable(level);
        if (rt_workqueue_dowork(workqueue, work) != RT_EOK)
        {
            level = rt_hw_interrupt_disable();
            rt_memset(work, 0, sizeof(struct rt_work));
            rt_hw_interrupt_enable(level);
        }
    }
}

static void netif_set_connected(void *parameter)
{
    struct rt_wlan_device *wlan = parameter;
    struct lwip_prot_des *lwip_prot = wlan->prot;
    struct eth_device *eth_dev = &lwip_prot->eth;

    if (lwip_prot->connected_flag)
    {
        if (wlan->mode == RT_WLAN_STATION)
        {
            LOG_D("F:%s L:%d dhcp start run", __FUNCTION__, __LINE__);
            netifapi_netif_common(eth_dev->netif, netif_set_link_up, NULL);
#ifdef RT_LWIP_DHCP
            dhcp_start(eth_dev->netif);
#endif
            rt_timer_start(&lwip_prot->timer);
        }
        else if (wlan->mode == RT_WLAN_AP)
        {
            LOG_D("F:%s L:%d dhcpd start run", __FUNCTION__, __LINE__);

            netifapi_netif_common(eth_dev->netif, netif_set_link_up, NULL);
#ifdef LWIP_USING_DHCPD
            {
                char netif_name[8];
                int i;

                rt_memset(netif_name, 0, sizeof(netif_name));
                for (i = 0; i < sizeof(eth_dev->netif->name); i++)
                {
                    netif_name[i] = eth_dev->netif->name[i];
                }
                dhcpd_start(netif_name);
            }
#endif
        }
    }
    else
    {
        if (wlan->mode == RT_WLAN_STATION)
        {
            LOG_D("F:%s L:%d dhcp stop run", __FUNCTION__, __LINE__);
            netifapi_netif_common(eth_dev->netif, netif_set_link_down, NULL);
#ifdef RT_LWIP_DHCP
            {
                ip_addr_t ip_addr = { 0 };
                dhcp_stop(eth_dev->netif);
                netif_set_addr(eth_dev->netif, &ip_addr, &ip_addr, &ip_addr);
            }
#endif
            rt_timer_stop(&lwip_prot->timer);
        }
        else if (wlan->mode == RT_WLAN_AP)
        {
            LOG_D("F:%s L:%d dhcpd stop run", __FUNCTION__, __LINE__);
            netifapi_netif_common(eth_dev->netif, netif_set_link_down, NULL);
        }
    }
}

static void rt_wlan_lwip_event_handle(struct rt_wlan_prot *port, struct rt_wlan_device *wlan, int event)
{
    struct lwip_prot_des *lwip_prot = (struct lwip_prot_des *)wlan->prot;
    rt_bool_t flag_old;

    flag_old = lwip_prot->connected_flag;

    switch (event)
    {
    case RT_WLAN_PROT_EVT_CONNECT:
    {
        LOG_D("event: CONNECT");
        lwip_prot->connected_flag = RT_TRUE;
        break;
    }
    case RT_WLAN_PROT_EVT_DISCONNECT:
    {
        LOG_D("event: DISCONNECT");
        lwip_prot->connected_flag = RT_FALSE;
        break;
    }
    case RT_WLAN_PROT_EVT_AP_START:
    {
        LOG_D("event: AP_START");
        lwip_prot->connected_flag = RT_TRUE;
        break;
    }
    case RT_WLAN_PROT_EVT_AP_STOP:
    {
        LOG_D("event: AP_STOP");
        lwip_prot->connected_flag = RT_FALSE;
        break;
    }
    case RT_WLAN_PROT_EVT_AP_ASSOCIATED:
    {
        LOG_D("event: ASSOCIATED");
        break;
    }
    case RT_WLAN_PROT_EVT_AP_DISASSOCIATED:
    {
        LOG_D("event: DISASSOCIATED");
        break;
    }
    default :
    {
        LOG_D("event: UNKNOWN");
        break;
    }
    }
    if (flag_old != lwip_prot->connected_flag)
    {
        rt_wlan_workqueue_dowork(netif_set_connected, wlan);
        // netif_set_connected(wlan);
    }
}

static rt_err_t rt_wlan_lwip_protocol_control(rt_device_t device, int cmd, void *args)
{
    struct eth_device *eth_dev = (struct eth_device *)device;
    struct rt_wlan_device *wlan;
    rt_err_t err = RT_EOK;

    RT_ASSERT(eth_dev != RT_NULL);

    LOG_D("F:%s L:%d device:0x%08x user_data:0x%08x", __FUNCTION__, __LINE__, eth_dev, eth_dev->parent.user_data);

    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get MAC address */
        wlan = eth_dev->parent.user_data;
        err = rt_device_control((rt_device_t)wlan, RT_WLAN_CMD_GET_MAC, args);
        break;
    default :
        break;
    }
    return err;
}

static rt_err_t rt_wlan_lwip_protocol_recv(struct rt_wlan_device *wlan, void *buff, int len)
{
    struct eth_device *eth_dev = &((struct lwip_prot_des *)wlan->prot)->eth;
    struct pbuf *p = RT_NULL;

    LOG_D("F:%s L:%d run", __FUNCTION__, __LINE__);

    if (eth_dev == RT_NULL)
    {
        return -RT_ERROR;
    }
#ifdef RT_WLAN_PROT_LWIP_PBUF_FORCE
    {
        p = buff;
        if ((eth_dev->netif->input(p, eth_dev->netif)) != ERR_OK)
        {
            return -RT_ERROR;
        }
        return RT_EOK;
    }
#else
    {
        int count = 0;

        while (p == RT_NULL)
        {
            p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
            if (p != RT_NULL)
                break;

            p = pbuf_alloc(PBUF_RAW, len, PBUF_RAM);
            if (p != RT_NULL)
                break;

            LOG_D("F:%s L:%d wait for pbuf_alloc!", __FUNCTION__, __LINE__);
            rt_thread_delay(1);
            count++;

            //wait for 10ms or give up!!
            if (count >= 10)
            {
                LOG_W("F:%s L:%d pbuf allocate fail!!!", __FUNCTION__, __LINE__);
                return -RT_ENOMEM;
            }
        }
        /*copy data dat -> pbuf*/
        pbuf_take(p, buff, len);
        if ((eth_dev->netif->input(p, eth_dev->netif)) != ERR_OK)
        {
            LOG_D("F:%s L:%d IP input error", __FUNCTION__, __LINE__);
            pbuf_free(p);
            p = RT_NULL;
        }
        LOG_D("F:%s L:%d netif iput success! len:%d", __FUNCTION__, __LINE__, len);
        return RT_EOK;
    }
#endif
}

static rt_err_t rt_wlan_lwip_protocol_send(rt_device_t device, struct pbuf *p)
{
    struct rt_wlan_device *wlan = ((struct eth_device *)device)->parent.user_data;

    LOG_D("F:%s L:%d run", __FUNCTION__, __LINE__);

    if (wlan == RT_NULL)
    {
        return RT_EOK;
    }

#ifdef RT_WLAN_PROT_LWIP_PBUF_FORCE
    {
        rt_wlan_prot_transfer_dev(wlan, p, p->tot_len);
        return RT_EOK;
    }
#else
    {
        rt_uint8_t *frame;

        /* sending data directly */
        if (p->len == p->tot_len)
        {
            frame = (rt_uint8_t *)p->payload;
            rt_wlan_prot_transfer_dev(wlan, frame, p->tot_len);
            LOG_D("F:%s L:%d run len:%d", __FUNCTION__, __LINE__, p->tot_len);
            return RT_EOK;
        }
        frame = rt_malloc(p->tot_len);
        if (frame == RT_NULL)
        {
            LOG_E("F:%s L:%d malloc out_buf fail\n", __FUNCTION__, __LINE__);
            return -RT_ENOMEM;
        }
        /*copy pbuf -> data dat*/
        pbuf_copy_partial(p, frame, p->tot_len, 0);
        /* send data */
        rt_wlan_prot_transfer_dev(wlan, frame, p->tot_len);
        LOG_D("F:%s L:%d run len:%d", __FUNCTION__, __LINE__, p->tot_len);
        rt_free(frame);
        return RT_EOK;
    }
#endif
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops wlan_lwip_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    rt_wlan_lwip_protocol_control
};
#endif

static struct rt_wlan_prot *rt_wlan_lwip_protocol_register(struct rt_wlan_prot *prot, struct rt_wlan_device *wlan)
{
    struct eth_device *eth = RT_NULL;
    static rt_uint8_t id = 0;
    char eth_name[4], timer_name[16];
    rt_device_t device = RT_NULL;
    struct lwip_prot_des *lwip_prot;

    if (wlan == RT_NULL || prot == RT_NULL)
        return RT_NULL;;

    LOG_D("F:%s L:%d is run wlan:0x%08x", __FUNCTION__, __LINE__, wlan);

    do
    {
        /* find ETH device name */
        eth_name[0] = 'w';
        eth_name[1] = '0' + id++;
        eth_name[2] = '\0';
        device = rt_device_find(eth_name);
    }
    while (device);

    if (id > 9)
    {
        LOG_E("F:%s L:%d not find Empty name", __FUNCTION__, __LINE__, eth_name);
        return RT_NULL;
    }

    if (rt_device_open((rt_device_t)wlan, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        LOG_E("F:%s L:%d open wlan failed", __FUNCTION__, __LINE__);
        return RT_NULL;
    }

    lwip_prot = rt_malloc(sizeof(struct lwip_prot_des));
    if (lwip_prot == RT_NULL)
    {
        LOG_E("F:%s L:%d malloc mem failed", __FUNCTION__, __LINE__);
        rt_device_close((rt_device_t)wlan);
        return RT_NULL;
    }
    rt_memset(lwip_prot, 0, sizeof(struct lwip_prot_des));

    eth = &lwip_prot->eth;

#ifdef RT_USING_DEVICE_OPS
    eth->parent.ops        = &wlan_lwip_ops;
#else
    eth->parent.init       = RT_NULL;
    eth->parent.open       = RT_NULL;
    eth->parent.close      = RT_NULL;
    eth->parent.read       = RT_NULL;
    eth->parent.write      = RT_NULL;
    eth->parent.control    = rt_wlan_lwip_protocol_control;
#endif

    eth->parent.user_data  = wlan;
    eth->eth_rx     = RT_NULL;
    eth->eth_tx     = rt_wlan_lwip_protocol_send;

    /* register ETH device */
    if (eth_device_init(eth, eth_name) != RT_EOK)
    {
        LOG_E("eth device init failed");
        rt_device_close((rt_device_t)wlan);
        rt_free(lwip_prot);
        return RT_NULL;
    }
    rt_memcpy(&lwip_prot->prot, prot, sizeof(struct rt_wlan_prot));
    if (wlan->mode == RT_WLAN_STATION)
    {
        rt_sprintf(timer_name, "timer_%s", eth_name);
        rt_timer_init(&lwip_prot->timer, timer_name, timer_callback, wlan, rt_tick_from_millisecond(1000),
                      RT_TIMER_FLAG_SOFT_TIMER | RT_TIMER_FLAG_ONE_SHOT);
    }
    netif_set_up(eth->netif);
    LOG_I("eth device init ok name:%s", eth_name);

    return &lwip_prot->prot;
}

static void rt_wlan_lwip_protocol_unregister(struct rt_wlan_prot *prot, struct rt_wlan_device *wlan)
{
    /*TODO*/
    LOG_D("F:%s L:%d is run wlan:0x%08x", __FUNCTION__, __LINE__, wlan);
}

static struct rt_wlan_prot_ops ops =
{
    rt_wlan_lwip_protocol_recv,
    rt_wlan_lwip_protocol_register,
    rt_wlan_lwip_protocol_unregister
};

int rt_wlan_lwip_init(void)
{
    static struct rt_wlan_prot prot;
    rt_wlan_prot_event_t event;

    rt_memset(&prot, 0, sizeof(prot));
    rt_strncpy(&prot.name[0], RT_WLAN_PROT_LWIP, RT_WLAN_PROT_NAME_LEN);
    prot.ops = &ops;

    if (rt_wlan_prot_regisetr(&prot) != RT_EOK)
    {
        LOG_E("F:%s L:%d protocol regisetr failed", __FUNCTION__, __LINE__);
        return -1;
    }

    for (event = RT_WLAN_PROT_EVT_INIT_DONE; event < RT_WLAN_PROT_EVT_MAX; event++)
    {
        rt_wlan_prot_event_register(&prot, event, rt_wlan_lwip_event_handle);
    }

    return 0;
}
INIT_PREV_EXPORT(rt_wlan_lwip_init);

#endif
