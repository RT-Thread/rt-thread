/*
 * Copyright (c)
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date        Author    Email                    Notes
 * 2022-04-06  Kevin.Liu kevin.liu.mchp@gmail.com First Release
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>

#include <netif/ethernetif.h>
#include <lwipopts.h>

#include <atmel_start.h>
#include <peripheral_clk_config.h>
#include <ieee8023_mii_standard_config.h>

#include "board.h"
#include "sam_gmac.h"

#ifdef RT_USING_LWIP

struct rt_sam_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;

    struct mac_async_descriptor    *macif;
    struct ethernet_phy_descriptor *phyif;

#ifdef RT_USING_TIMER_SOFT
    rt_timer_t  phy_monitor_timer;
#else
    rt_thread_t phy_monitor_tid;
#endif

    /* ethernet MAC address */
    rt_uint8_t  mac_addr[NETIF_MAX_HWADDR_LEN];

    /* GMAC Link Speed */
    gmac_speed_type  link_speed;
    /* GMAC Link Mode */
    gmac_duplex_type link_mode;
};

static struct rt_sam_eth sam_eth_device;

/**
 * @brief Called by GMAC RX interrupt, will notify RX task
 *
 * @note  Will call eth_device_ready to notify RX task.
 *
 * @param
 *
 * @return
 */
static void rt_sam_gmac_rxcb(void)
{
    rt_err_t result;

    /* enter interrupt */
    rt_interrupt_enter();

    result = eth_device_ready(&sam_eth_device.parent);
    if (result != RT_EOK)
        LOG_E("rt_sam_gmac_rxcb error");

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * @brief Initialize the MAC hardware
 *
 * @note  Will set MAC filter by using input MAC address.
 *
 * @param gmac_dev GMAC device description.
 *
 * @return
 */
static inline void rt_sam_gmac_init(struct rt_sam_eth *gmac_dev)
{
    struct mac_async_filter filter;

    /* set MAC hardware address */
    rt_memcpy(filter.mac, sam_eth_device.mac_addr, NETIF_MAX_HWADDR_LEN);
    filter.tid_enable = false;
    mac_async_set_filter(gmac_dev->macif, 0, &filter);
    mac_async_register_callback(gmac_dev->macif, MAC_ASYNC_RECEIVE_CB, (FUNC_PTR)rt_sam_gmac_rxcb);
}

static rt_err_t rt_sam_eth_init(rt_device_t dev)
{
    LOG_D("gmac init");
    return RT_EOK;
}

static rt_err_t rt_sam_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("gmac open");
    return RT_EOK;
}

static rt_err_t rt_sam_eth_close(rt_device_t dev)
{
    LOG_D("gmac close");
    return RT_EOK;
}

static rt_ssize_t rt_sam_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("gmac read");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_sam_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    LOG_D("gmac write");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_sam_eth_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t ret = RT_EOK;

    switch (cmd)
    {
        case NIOCTL_GADDR:
            /* get mac address */
            if (args)
                rt_memcpy(args, sam_eth_device.mac_addr, 6);
            break;

        default :
            break;
    }

    return ret;
}

/**
 * @brief Transmission packet though the MAC hardware
 *
 * @note  Send package to MAC.
 *
 * @param dev the RT net device input.
 *
 * @param p stored message will be sent to MAC.
 *
 * @return RT_EOK.
 */
rt_err_t rt_sam_eth_tx(rt_device_t dev, struct pbuf *p)
{
    struct rt_sam_eth *gmac_dev = (struct rt_sam_eth *)dev->user_data;
    struct pbuf *      q;
    void *             tbuf;
    uint8_t *          pos;

#if ETH_PAD_SIZE
    pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

    if (p->tot_len == p->len)
    {
        mac_async_write(gmac_dev->macif, p->payload, p->tot_len);
    }
    else
    {
        tbuf = mem_malloc(LWIP_MEM_ALIGN_SIZE(p->tot_len));
        pos  = tbuf;
        if (tbuf == NULL)
        {
            return ERR_MEM;
        }
        for (q = p; q != NULL; q = q->next)
        {
            rt_memcpy(pos, q->payload, q->len);
            pos += q->len;
        }
        mac_async_write(gmac_dev->macif, tbuf, p->tot_len);
        mem_free(tbuf);
    }

#if ETH_PAD_SIZE
    pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

    LINK_STATS_INC(link.xmit);

    return ERR_OK;
}

/**
 * @brief Receive packet from the MAC hardware
 *
 * @note  Returned pbuf filled with the received packet (including MAC header)
 *
 * @param dev the RT net device input.
 *
 * @return NULL on memory error
 */
struct pbuf *rt_sam_eth_rx(rt_device_t dev)
{
    struct rt_sam_eth *gmac_dev = (struct rt_sam_eth *)dev->user_data;
    struct pbuf *      p;
    u16_t              len;

    len = mac_async_read_len(gmac_dev->macif); /* Obtain the size of the packet */
    if (len == 0)
    {
        return NULL;
    }

#if ETH_PAD_SIZE
    len += ETH_PAD_SIZE; /* allow room for Ethernet padding */
#endif

    /* Allocate a pbuf as one large chunk, This include protocol header */
    p = pbuf_alloc(PBUF_RAW, len, PBUF_RAM);

    if (p != NULL)
    {
#if ETH_PAD_SIZE
        pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

        /* Read the entire packet into the pbuf. */
        mac_async_read(gmac_dev->macif, p->payload, p->len);

#if ETH_PAD_SIZE
        pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

        LINK_STATS_INC(link.recv);
    }
    else
    {
        mac_async_read(gmac_dev->macif, NULL, 0);
        LINK_STATS_INC(link.memerr);
        LINK_STATS_INC(link.drop);
    }

    return p;
}

/**
 * @brief  PHY link status monitor task - timer task or thread
 *
 * @note   Will check link status, link mode and link speed
 *
 * @param parameter input parameter passing to the function.
 *
 * @return
 */
static void rt_sam_eth_monitor(void *parameter)
{
    struct rt_sam_eth *sam_eth = (struct rt_sam_eth *)parameter;
    bool link_up;
    int32_t  ret;
    uint16_t val;
    static rt_uint8_t link_count = 0;

#ifndef RT_USING_TIMER_SOFT
    while (1)
    {
#endif
        ret = ethernet_phy_get_link_status(sam_eth->phyif, &link_up);
        if (ERR_NONE == ret)
        {
            if (link_up)
            {
                /* send link up. */
                eth_device_linkchange(&sam_eth->parent, RT_TRUE);
            }
            else
            {
                /* send link down. */
                eth_device_linkchange(&sam_eth->parent, RT_FALSE);;
            }
        }

        ret = ethernet_phy_read_reg(sam_eth->phyif, MDIO_REG1_BMSR, &val);
        if (ERR_NONE == ret)
        {
            if (val & (MDIO_REG1_BIT_100BASE_TX_FD | MDIO_REG1_BIT_100BASE_TX_HD))
            {
                LOG_D("100Mbps");
                sam_eth_device.link_speed = GMAC_SPEED_100MBPS;
            }
            else
            {
                LOG_D("10Mbps");
                sam_eth_device.link_speed = GMAC_SPEED_10MBPS;
            }

            if (val & (MDIO_REG1_BIT_100BASE_TX_FD | MDIO_REG1_BIT_10BASE_T_FD))
            {
                LOG_D("100Mbps");
                sam_eth_device.link_mode = GMAC_FULL_DUPLEX;
            }
            else
            {
                LOG_D("10Mbps");
                sam_eth_device.link_mode = GMAC_HALF_DUPLEX;
            }
        }

        if (link_count >= 10)
        {
            link_count = 0;

            /* Restart an auto-negotiation */
            ethernet_phy_restart_autoneg(sam_eth->phyif);
        }

#ifndef RT_USING_TIMER_SOFT
        rt_thread_mdelay(1000);
    }
#endif
}

/**
 * @brief    Register the GMAC Ethernet device.
 *
 * @note
 *
 * @param
 *
 * @return   RT_OK or RT_ERROR.
 */

static int rt_hw_sam_eth_init(void)
{
    rt_err_t   state = RT_EOK;
#if CONF_AT24MAC_ADDRESS != 0
    rt_uint8_t addr  = 0x9A;
#endif

    sam_eth_device.macif = &MACIF;
    sam_eth_device.phyif = &MACIF_PHY_desc;

    sam_eth_device.link_speed = GMAC_SPEED_100MBPS;
    sam_eth_device.link_mode  = GMAC_FULL_DUPLEX;

#if CONF_AT24MAC_ADDRESS != 0
    i2c_m_sync_enable(&I2C_0);
    i2c_m_sync_set_slaveaddr(&I2C_0, CONF_AT24MAC_ADDRESS, I2C_M_SEVEN);
    io_write(&(I2C_0.io), &addr, 1);
    io_read(&(I2C_0.io),  sam_eth_device.mac_addr, 6);
#else
    /* set mac to 0x11 if no EEPROM mounted */
    memset(sam_eth_device.mac_addr, 0x11, 6);
#endif

    sam_eth_device.parent.parent.init      = rt_sam_eth_init;
    sam_eth_device.parent.parent.open      = rt_sam_eth_open;
    sam_eth_device.parent.parent.close     = rt_sam_eth_close;
    sam_eth_device.parent.parent.read      = rt_sam_eth_read;
    sam_eth_device.parent.parent.write     = rt_sam_eth_write;
    sam_eth_device.parent.parent.control   = rt_sam_eth_control;
    sam_eth_device.parent.parent.user_data = (void *)&sam_eth_device;

    sam_eth_device.parent.eth_rx = rt_sam_eth_rx;
    sam_eth_device.parent.eth_tx = rt_sam_eth_tx;

    rt_sam_gmac_init(&sam_eth_device);

    /* register eth device */
    state = eth_device_init(&(sam_eth_device.parent), "e0");

    if (RT_EOK == state)
    {
        LOG_D("gmac device init success");
    }
    else
    {
        LOG_E("gmac device init faild: %d", state);
        state = -RT_ERROR;
        goto outs;
    }

    /* start SAM PHY monitor */
#ifdef RT_USING_TIMER_SOFT
    sam_eth_device.phy_monitor_timer = rt_timer_create("phylnk",
                                                       rt_sam_eth_monitor,
                                                       (void *)&sam_eth_device,
                                                       10*RT_TICK_PER_SECOND,
                                                       RT_TIMER_FLAG_PERIODIC);

    if (RT_NULL != sam_eth_device.phy_monitor_timer)
    {
        rt_timer_start(sam_eth_device.phy_monitor_timer);
    }
    else
    {
        state = -RT_ERROR;
        LOG_E("gmac rt_timer_create faild: %d", state);
    }
#else
    sam_eth_device.phy_monitor_tid = rt_thread_create("phy",
                                                      rt_sam_eth_monitor,
                                                      (void *)&sam_eth_device,
                                                      1024,
                                                      RT_THREAD_PRIORITY_MAX - 2,
                                                      2);
    if (sam_eth_device.phy_monitor_tid != RT_NULL)
    {
        rt_thread_startup(sam_eth_device.phy_monitor_tid);
    }
    else
    {
        state = -RT_ERROR;
        LOG_E("gmac rt_thread_create faild: %d", state);
    }
#endif

outs:
    return state;
}
INIT_DEVICE_EXPORT(rt_hw_sam_eth_init);

#endif /* BSP_USING_ETH_ARTPI */
