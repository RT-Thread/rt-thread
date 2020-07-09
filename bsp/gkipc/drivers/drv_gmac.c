/*
 * File      : drv_gmac.c
 * This file is part of GK710X BSP for RT-Thread distribution.
 *
 * Copyright (c) 2017 GOKE Microelectronics Co., Ltd.
 * All rights reserved
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
 *  Visit http://www.goke.com to get contact with Goke.
 *
 * Change Logs:
 * Date           Author       Notes
 */

/*****************************************************************************
 *  Include Section
 *  add all #include here
 *****************************************************************************/
#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <netif/ethernetif.h>
#include "lwipopts.h"
#include "drv_gmac.h"
#include "gtypes.h"
#include "gd_ethernet.h"

#ifdef RT_USING_GMAC
/*****************************************************************************
 * Define section
 * add all #define here
 *****************************************************************************/
#define GMAC_TX_BUFFER_SIZE 2048
#define GMAC_RX_BUFFER_SIZE 2048

#define MAC_ADDR0   0x11
#define MAC_ADDR1   0x10
#define MAC_ADDR2   0xAA
#define MAC_ADDR3   0xBB
#define MAC_ADDR4   0xCC
#define MAC_ADDR5   0x01


/****************************************************************************
 * ADT section
 *  add definition of user defined Data Type that only be used in this file here
 ***************************************************************************/

#define MAX_ADDR_LEN 6
typedef struct gk_gmac_object
{
    /* inherit from ethernet device */
    struct eth_device parent;

    GD_ETH_InitParamsT init_param;
    GD_ETH_OpenParamsT params;
    GD_HANDLE eth_handle;

    int link;
    struct rt_timer timer;
    U8 local_mac_address[MAX_ADDR_LEN];

    U8* rx_buffer;
    U16 rx_len;
    struct rt_semaphore rx_lock;
#if 0
    UINT8 local_mac_address[MAX_ADDR_LEN];
    unsigned short phy_addr;
    int full_duplex;  // read only
    int speed_100m;   // read only

    UINT8* rx_ring_original;
    UINT8* tx_ring_original;
    UINT8* rx_buffer_original;
    UINT8* tx_buffer_original;

    UINT8* rx_buffer;
    UINT8* tx_buffer;

    Gmac_Rx_DMA_Descriptors* rx_ring;
    Gmac_Tx_DMA_Descriptors* tx_ring;

    unsigned long rx_buffer_dma;
    unsigned long tx_buffer_dma;
    unsigned long rx_ring_dma;
    unsigned long tx_ring_dma;

    unsigned int tx_stop;

    struct rt_semaphore tx_lock;
    struct rt_semaphore rx_lock;
    struct rt_semaphore tx_ack;
    struct rt_semaphore rx_ack;
    struct rt_semaphore mdio_bus_lock;
    int speed;
    int duplex;
    int link;
    int phy_interface;
    struct rt_timer timer;
    struct rt_timer rx_poll_timer;

    gk_gmac_stats_t stats;

    unsigned int rx_cur_desc;
    unsigned int tx_cur_desc;
    unsigned int get_frame_no;
    struct rt_workqueue* rx_queue;
    struct rt_work* rx_work;
#endif

} gk_gmac_object_t;

static int recv_state = 0;
static void recv_isr_callback(volatile U8* buffer, U16 len);

/******************************************************************************
 * Function prototype section
 * add prototypes for all functions called by this file,execepting those
 * declared in header file
 *****************************************************************************/
int gk_gmac_init(rt_device_t dev)
{
    GERR ret = GD_OK;
    int open_retry = 3;
    GD_ETH_MacT macaddr;
    gk_gmac_object_t* gmac;
    gmac = (gk_gmac_object_t*)dev->user_data;

    // eth init .....
    gmac->init_param.bHWReset = GFALSE;
    gmac->init_param.phyreset = GD_GPIO_0;
    gmac->init_param.phyType = 0;
    ret = GD_ETH_Init(&(gmac->init_param));
    if (ret != GD_OK)
    {
        rt_kprintf("GD_ETH_Init error", ret);
        return -1;
    }

    gmac->eth_handle = 0;
    // Open eth device.
    gmac->params.addr = GD_ETH_PHY_EXTERNAL_AUTO;
    gmac->params.workmode.speed       = GD_ETH_SPEED_100M;
    gmac->params.workmode.duplex      = GD_ETH_FULL_DUPLEX;
    gmac->params.workmode.loopback    = GD_ETH_LOOP_OFF;
    gmac->params.workmode.mode        = GD_ETH_PHY_IF_MODE_RMII;

    ret = GD_ETH_Open(&(gmac->params), &(gmac->eth_handle));
    while ((ret != GD_OK) && (open_retry--)) {
        rt_kprintf("GD_ETH_Open: device open failed(%ld)"
                                            ", retry %ld\n", ret, open_retry);
        rt_thread_delay(10);
        ret = GD_ETH_Open(&(gmac->params), &(gmac->eth_handle));
    }
    if  (ret == GD_OK) {
        rt_kprintf("GD_ETH_Open: device open successed 0x%x.\n", gmac->eth_handle);
    }

    ret = GD_ETH_GetMacAddress(gmac->eth_handle, &macaddr);
    if (ret != GD_OK) {
        rt_kprintf("GD_ETH_GetMacAddress: device getMacAddress failed, use default.\n");

        macaddr[0] = MAC_ADDR0;
        macaddr[1] = MAC_ADDR1;
        macaddr[2] = MAC_ADDR2;
        macaddr[3] = MAC_ADDR3;
        macaddr[4] = MAC_ADDR4;
        macaddr[5] = MAC_ADDR5;
    }

    rt_memcpy(gmac->local_mac_address, macaddr, MAX_ADDR_LEN);

    // set data coming callback.
    GD_ETH_SetNetReceiveFuc(recv_isr_callback);

    return 0;
}

void gk_gmac_update_link(void* param)
{
    gk_gmac_object_t* gmac;
    gmac = (gk_gmac_object_t*)param;

    rt_device_t dev = &gmac->parent.parent;
    GD_ETH_StatParamsT ethstat;

    GD_ETH_GetStat(gmac->eth_handle, &ethstat);
    if (gmac->link != ethstat.linkup)
    {
        rt_kprintf("ipc ethif link is %s\n", (ethstat.linkup == GD_ETH_LINKUP ?"UP":"DOWN"));
        rt_kprintf("  speed is %d\n", (int)ethstat.speed);
        rt_kprintf("  duplex is %d\n", (int)ethstat.duplex);

        if (ethstat.linkup == GD_ETH_LINKUP)
        {
            rt_kprintf("%s: link up\n", dev->parent.name);
            eth_device_linkchange(&gmac->parent, RT_TRUE);
        }
        else
        {
            rt_kprintf("%s: link down\n", dev->parent.name);
            eth_device_linkchange(&gmac->parent, RT_FALSE);
        }

        gmac->link = ethstat.linkup;
    }
}


/*********************
 *
 * up level use interface
 *
 *********************/
static rt_err_t rt_gk_gmac_init(rt_device_t dev)
{
    int ret;
    gk_gmac_object_t* gmac;
    gmac = (gk_gmac_object_t*)dev->user_data;

    rt_timer_init(&gmac->timer, "link_timer", gk_gmac_update_link, (void*)gmac,
                  RT_TICK_PER_SECOND, RT_TIMER_FLAG_PERIODIC);

    rt_timer_start(&gmac->timer);

    return RT_EOK;
}

static rt_err_t rt_gk_gmac_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_gk_gmac_close(rt_device_t dev)
{
    gk_gmac_object_t* gmac;
    gmac = (gk_gmac_object_t*)dev->user_data;

    GD_ETH_Close(&(gmac->eth_handle));

    return RT_EOK;
}
static rt_size_t rt_gk_gmac_read(rt_device_t dev, rt_off_t pos, void* buffer,
                                 rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t rt_gk_gmac_write(rt_device_t dev, rt_off_t pos,
                                  const void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_gk_gmac_control(rt_device_t dev, int cmd, void* args)
{
    gk_gmac_object_t* gmac;
    gmac = (gk_gmac_object_t*)dev->user_data;

    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args)
            rt_memcpy(args, gmac->local_mac_address, MAX_ADDR_LEN);
        else
            return -RT_ERROR;

        break;

    default:
        break;
    }

    return RT_EOK;
}

/* ethernet device interface */
/* transmit packet. */
static rt_uint8_t g_output_buf[PBUF_POOL_BUFSIZE+20];
static rt_err_t rt_gk_gmac_tx(rt_device_t dev, struct pbuf* p)
{
    rt_err_t ret = RT_EOK;
    struct pbuf *q = NULL;
    gk_gmac_object_t* gmac;
    gmac = (gk_gmac_object_t*)dev->user_data;

    if (p == NULL)
    {
        rt_kprintf("rt_gk_gmac_tx: out_pbuf is NULL\n");
        ret = ERR_MEM;
        return ret;
    }
    if (gmac->eth_handle == 0)
    {
        rt_kprintf("rt_gk_gmac_tx: eth_handle is 0\n");
        ret = ERR_MEM;
        return ret;
    }

    rt_uint8_t *output_bufptr = p->payload;

    if (p->len != p->tot_len)
    {
        rt_uint8_t *bufptr = g_output_buf;
        for (q = p; q != NULL; q = q->next)
        {
            rt_memcpy(bufptr, q->payload, q->len);
            bufptr += q->len;
        }
        output_bufptr = g_output_buf;
    }/* (else)  write to ethernet, reduce memcpy */


    ret = GD_ETH_Write(gmac->eth_handle, (char *) output_bufptr, p->tot_len, GD_ETH_FRAME_END);
    if (ret != GD_OK)
    {
        rt_kprintf("rt_gk_gmac_tx: eth Write error, len = %d, ret = %lu\n", p->tot_len, ret);
        ret = RT_EIO;
    }
    else
    {
        ret = RT_EOK;
    }

    return ret;
}

static struct pbuf * _convert_data_to_pbuf(U8 *buffer, U32 len)
{
    struct pbuf *p, *q;
    U8 *bufptr;
    U32 buflen;

    if (len <= 0) {
        rt_kprintf("_convert_data_to_pbuf: len(%d) <= 0\n", len);
        return NULL;
    }
    buflen = len;
    p = pbuf_alloc(PBUF_RAW, buflen, PBUF_POOL);
    if (p != NULL) {

        bufptr = (U8 *) buffer;
        for (q = p; q != NULL; q = q->next) {
            SMEMCPY(q->payload, bufptr, q->len);
            bufptr += q->len;
        }

    } else {
        rt_kprintf("_convert_data_to_pbuf: can't alloc pbuf(len=%lu)\n", buflen);
        return NULL;
    }

    return p;
}

/* reception packet. */
static struct pbuf* rt_gk_gmac_rx(rt_device_t dev)
{
    gk_gmac_object_t* gmac;
    gmac = (gk_gmac_object_t*)dev->user_data;

    if (!recv_state)
    {
        return RT_NULL;
    }

    struct pbuf* temp_pbuf = RT_NULL;

    if (gmac->rx_len <= 0)
    {
        rt_kprintf("rt_gk_gmac_rx: len(%d) <= 0\n", gmac->rx_len);
        return RT_NULL;
    }

    rt_sem_take(&gmac->rx_lock, RT_WAITING_FOREVER);

    //rt_kprintf("rt_gk_gmac_rx buffer = 0x%x, len = %d\n", gmac->rx_buffer, gmac->rx_len);

    //temp_pbuf = pbuf_alloc(PBUF_LINK, gmac->rx_len, PBUF_RAM);
    temp_pbuf = _convert_data_to_pbuf(gmac->rx_buffer, gmac->rx_len);
    if (!temp_pbuf)
    {
        rt_kprintf("alloc pbuf failed\n");
        rt_sem_release(&gmac->rx_lock);
        return RT_NULL;
    }

    //rt_memcpy(temp_pbuf->payload, gmac->rx_buffer, gmac->rx_len);

    recv_state = 0;

    rt_sem_release(&gmac->rx_lock);

    return temp_pbuf;
}

static void recv_isr_callback(volatile U8* buffer, U16 len)
{
    gk_gmac_object_t* gmac;
    int ret_eth;

    recv_state = 1;

    rt_device_t dev = rt_device_find("e0");
    if (dev == RT_NULL)
    {
        rt_kprintf("rt_device_find e0 == NULL\n");
        return;
    }

    gmac = (gk_gmac_object_t*)dev->user_data;

    if (buffer == NULL) {
        rt_kprintf("recv_isr_callback: error buffer == NULL\n");
        return;
    }

    if ((len <= 0) || (len > GMAC_RX_BUFFER_SIZE)) {
        rt_kprintf("recv_isr_callback: error len = %d(1~%d)\n", len, GMAC_RX_BUFFER_SIZE);
        return;
    }

    gmac->rx_buffer = (U8*)buffer;
    gmac->rx_len = len;
    //rt_kprintf("recv_isr_callback = 0x%x, len = %d\n", gmac->rx_buffer, gmac->rx_len);

    ret_eth = eth_device_ready(&(gmac->parent));
    if (ret_eth != RT_EOK)
    {
        rt_kprintf("eth_device_ready error %d\n",ret_eth);
    }
}

int rt_app_gk_gmac_init(void)
{
    gk_gmac_object_t* gmac;

    GD_ETH_MacT macaddr;
    gmac = (gk_gmac_object_t*)rt_malloc(sizeof(*gmac));
    if (gmac == NULL)
    {
        rt_kprintf("gk_eth_initialize: Cannot allocate Gmac_Object %d\n", 1);
        return (-1);
    }

    memset(gmac, 0, sizeof(gk_gmac_object_t));

    rt_sem_init(&gmac->rx_lock, "rx_lock", 1, RT_IPC_FLAG_FIFO);

    gmac->parent.parent.init      = rt_gk_gmac_init;
    gmac->parent.parent.open      = rt_gk_gmac_open;
    gmac->parent.parent.close     = rt_gk_gmac_close;
    gmac->parent.parent.read      = rt_gk_gmac_read;
    gmac->parent.parent.write     = rt_gk_gmac_write;
    gmac->parent.parent.control   = rt_gk_gmac_control;
    gmac->parent.parent.user_data = (void*)gmac;

    gmac->parent.eth_rx = rt_gk_gmac_rx;
    gmac->parent.eth_tx = rt_gk_gmac_tx;

    gk_gmac_init(&gmac->parent.parent);

    eth_device_init(&(gmac->parent), "e0");

    return 0;
}

#ifdef RT_USING_FINSH
#include "finsh.h"

void dump_rx_desc(void)
{
    int i;
    gk_gmac_object_t* gmac;
    rt_device_t dev = rt_device_find("e0");

    if (dev == RT_NULL) return;

    gmac = (gk_gmac_object_t*)dev->user_data;

    rt_kprintf("soft current desc is:%d\n", gmac->link);
}

void dump_tx_desc(void)
{
    int i;
    gk_gmac_object_t* gmac;
    rt_device_t dev = rt_device_find("e0");

    if (dev == RT_NULL) return;

    gmac = (gk_gmac_object_t*)dev->user_data;

    rt_kprintf("soft current desc is:%d\n", gmac->link);
}


FINSH_FUNCTION_EXPORT(dump_rx_desc, dump e0 rx desc);
FINSH_FUNCTION_EXPORT(dump_tx_desc, dump e0 tx desc);

#endif

#endif
