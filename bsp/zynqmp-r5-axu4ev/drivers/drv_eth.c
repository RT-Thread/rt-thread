/*
 * Copyright (c) 2021, WangHuachen
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-5-10     WangHuachen  the first version
 */
#include "board.h"
#include <netif/ethernetif.h>
#include "lwipopts.h"
#include "lwip/opt.h"
#include "drv_eth.h"
#include "lwip/netif.h"
#include "netif/xadapter.h"
#include "netif/xemacpsif.h"
#include "xparameters.h"
#include "xemacps.h"

#define DBG_TAG             "drv.emac"
#define DBG_LEVEL           DBG_INFO
#include <rtdbg.h>

#define MAC_BASE_ADDR       XPAR_PSU_ETHERNET_3_BASEADDR
#define MAX_ADDR_LEN        6

struct rt_zynqmp_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;

    /* interface address info, hw address */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];

    struct xemac_s *xemac;
};

static struct rt_zynqmp_eth zynqmp_eth_device;
extern XEmacPs_Config *mac_config;
extern struct netif *NetIf;

static void rt_hw_eth_isr(int irqno, void *param)
{
    struct rt_zynqmp_eth *eth_dev = (struct rt_zynqmp_eth *)param;
    xemacpsif_s *xemacpsif = (xemacpsif_s *)eth_dev->xemac->state;
    XEmacPs_IntrHandler(&xemacpsif->emacps);
}

extern enum ethernet_link_status eth_link_status;
extern u32_t phy_link_detect(XEmacPs *xemacp, u32_t phy_addr);
extern u32_t phy_autoneg_status(XEmacPs *xemacp, u32_t phy_addr);
extern u32_t phyaddrforemac;

void rt_zynqmp_eth_link_detect(struct rt_zynqmp_eth *eth_dev)
{
    u32_t link_speed, phy_link_status;
    struct xemac_s *xemac = eth_dev->xemac;
    xemacpsif_s *xemacs = (xemacpsif_s *)(xemac->state);
    XEmacPs *xemacp = &xemacs->emacps;

    if ((xemacp->IsReady != (u32)XIL_COMPONENT_IS_READY) ||
            (eth_link_status == ETH_LINK_UNDEFINED))
        return;

    phy_link_status = phy_link_detect(xemacp, phyaddrforemac);

    if ((eth_link_status == ETH_LINK_UP) && (!phy_link_status))
        eth_link_status = ETH_LINK_DOWN;

    switch (eth_link_status) {
        case ETH_LINK_UNDEFINED:
        case ETH_LINK_UP:
            return;
        case ETH_LINK_DOWN:
            eth_device_linkchange(&zynqmp_eth_device.parent, RT_FALSE);
            eth_link_status = ETH_LINK_NEGOTIATING;
            LOG_D("Ethernet Link down");
            break;
        case ETH_LINK_NEGOTIATING:
            if (phy_link_status &&
                phy_autoneg_status(xemacp, phyaddrforemac)) {

                /* Initiate Phy setup to get link speed */
                link_speed = phy_setup_emacps(xemacp,
                                phyaddrforemac);
                XEmacPs_SetOperatingSpeed(xemacp, link_speed);

                eth_device_linkchange(&zynqmp_eth_device.parent, RT_TRUE);
                eth_link_status = ETH_LINK_UP;
                LOG_D("Ethernet Link up");
            }
            break;
    }
}

static void phy_monitor_thread(void *parameter)
{
    struct rt_zynqmp_eth *eth_dev = (struct rt_zynqmp_eth *)parameter;

    while (1)
    {
        rt_zynqmp_eth_link_detect(eth_dev);
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}

static rt_err_t rt_zynqmp_eth_init(rt_device_t dev)
{
    struct rt_zynqmp_eth *eth_dev = (struct rt_zynqmp_eth *)dev->user_data;
    struct netif *netif = eth_dev->parent.netif;
    struct xemac_s *xemac;
    xemacpsif_s *xemacpsif;
    u32 dmacrreg;
    s32_t status = XST_SUCCESS;
    struct xtopology_t *xtopologyp;

    if (eth_dev->xemac != RT_NULL)
    {
        LOG_W("rt_zynqmp_eth_init: device has been initialized");
        return -RT_ERROR;
    }

    NetIf = netif;

    xemacpsif = rt_malloc(sizeof *xemacpsif);
    if (xemacpsif == NULL)
    {
        LOG_E("rt_zynqmp_eth_init: out of memory");
        return -RT_ENOMEM;
    }

    xemac = rt_malloc(sizeof *xemac);
    if (xemac == NULL)
    {
        LOG_E("rt_zynqmp_eth_init: out of memory");
        return -RT_ENOMEM;
    }

    xemac->state = (void *)xemacpsif;
    xemac->topology_index = xtopology_find_index(MAC_BASE_ADDR);
    xemac->type = xemac_type_emacps;
    xemac->rt_eth_device = &eth_dev->parent;

    xemacpsif->send_q = NULL;
    xemacpsif->recv_q = pq_create_queue();
    if (!xemacpsif->recv_q)
        return -RT_ENOMEM;

    eth_dev->xemac = xemac;

    /* obtain config of this emac */
    mac_config = (XEmacPs_Config *)xemacps_lookup_config(MAC_BASE_ADDR);

    status = XEmacPs_CfgInitialize(&xemacpsif->emacps, mac_config,
                                   mac_config->BaseAddress);
    if (status != XST_SUCCESS)
    {
        LOG_W("In %s:EmacPs Configuration Failed....", __func__);
        return -RT_ERROR;
    }

    /* initialize the mac */
    init_emacps(xemacpsif, netif);

    dmacrreg = XEmacPs_ReadReg(xemacpsif->emacps.Config.BaseAddress,
                               XEMACPS_DMACR_OFFSET);
    dmacrreg = dmacrreg | (0x00000010);
    XEmacPs_WriteReg(xemacpsif->emacps.Config.BaseAddress,
                     XEMACPS_DMACR_OFFSET, dmacrreg);

    setup_isr(xemac);
    init_dma(xemac);

    xtopologyp = &xtopology[xemac->topology_index];
    /*
    * Connect the device driver handler that will be called when an
    * interrupt for the device occurs, the handler defined above performs
    * the specific interrupt processing for the device.
    */
    rt_hw_interrupt_install(xtopologyp->scugic_emac_intr, rt_hw_eth_isr, (void *)eth_dev, "eth");
    /*
    * Enable the interrupt for emacps.
    */
    rt_hw_interrupt_umask(xtopologyp->scugic_emac_intr);

    start_emacps(xemacpsif);

    if (eth_link_status == ETH_LINK_UP)
        eth_device_linkchange(&eth_dev->parent, RT_TRUE);

    rt_thread_t tid;
    tid = rt_thread_create("phylnk",
                           phy_monitor_thread,
                           eth_dev,
                           1024,
                           RT_THREAD_PRIORITY_MAX - 2,
                           2);
    if (tid != RT_NULL)
        rt_thread_startup(tid);
    else
        return -RT_ERROR;

    return RT_EOK;
}

static rt_err_t rt_zynqmp_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("emac open");
    return RT_EOK;
}

static rt_err_t rt_zynqmp_eth_close(rt_device_t dev)
{
    LOG_D("emac close");
    return RT_EOK;
}

static rt_ssize_t rt_zynqmp_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("emac read");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_zynqmp_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    LOG_D("emac write");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_zynqmp_eth_control(rt_device_t dev, int cmd, void *args)
{
    struct rt_zynqmp_eth *eth_dev = (struct rt_zynqmp_eth *)dev->user_data;
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args) rt_memcpy(args, eth_dev->dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

extern err_t _unbuffered_low_level_output(xemacpsif_s *xemacpsif, struct pbuf *p);
rt_err_t rt_zynqmp_eth_tx(rt_device_t dev, struct pbuf *p)
{
    rt_base_t lev;
    rt_err_t err;
    XEmacPs_BdRing *txring;

    struct rt_zynqmp_eth *eth_dev = (struct rt_zynqmp_eth *)dev->user_data;
    struct xemac_s *xemac = eth_dev->xemac;
    xemacpsif_s *xemacpsif = (xemacpsif_s *)(xemac->state);

    lev = rt_hw_interrupt_disable();

    txring = &(XEmacPs_GetTxRing(&xemacpsif->emacps));
    process_sent_bds(xemacpsif, txring);

    if (is_tx_space_available(xemacpsif))
    {
        _unbuffered_low_level_output(xemacpsif, p);
        err = RT_EOK;
    }
    else
    {
#if LINK_STATS
        lwip_stats.link.drop++;
#endif
        LOG_D("pack dropped, no space");
        err = -RT_ENOMEM;
    }

    rt_hw_interrupt_enable(lev);

    return err;
}

struct pbuf *rt_zynqmp_eth_rx(rt_device_t dev)
{
    rt_base_t lev;
    struct rt_zynqmp_eth *eth_dev = (struct rt_zynqmp_eth *)dev->user_data;
    struct xemac_s *xemac = eth_dev->xemac;
    xemacpsif_s *xemacpsif = (xemacpsif_s *)(xemac->state);
    struct pbuf *p;

    lev = rt_hw_interrupt_disable();

    /* see if there is data to process */
    if (pq_qlength(xemacpsif->recv_q) == 0)
        return NULL;

    /* return one packet from receive q */
    p = (struct pbuf *)pq_dequeue(xemacpsif->recv_q);

    rt_hw_interrupt_enable(lev);

    return p;
}

static int rt_hw_zynqmp_eth_init(void)
{
    rt_err_t state = RT_EOK;

    zynqmp_eth_device.xemac = RT_NULL;

    zynqmp_eth_device.dev_addr[0] = 0x00;
    zynqmp_eth_device.dev_addr[1] = 0x0A;
    zynqmp_eth_device.dev_addr[2] = 0x35;
    zynqmp_eth_device.dev_addr[3] = 0x00;
    zynqmp_eth_device.dev_addr[4] = 0x01;
    zynqmp_eth_device.dev_addr[5] = 0x02;

    zynqmp_eth_device.parent.parent.init       = rt_zynqmp_eth_init;
    zynqmp_eth_device.parent.parent.open       = rt_zynqmp_eth_open;
    zynqmp_eth_device.parent.parent.close      = rt_zynqmp_eth_close;
    zynqmp_eth_device.parent.parent.read       = rt_zynqmp_eth_read;
    zynqmp_eth_device.parent.parent.write      = rt_zynqmp_eth_write;
    zynqmp_eth_device.parent.parent.control    = rt_zynqmp_eth_control;
    zynqmp_eth_device.parent.parent.user_data  = &zynqmp_eth_device;

    zynqmp_eth_device.parent.eth_rx     = rt_zynqmp_eth_rx;
    zynqmp_eth_device.parent.eth_tx     = rt_zynqmp_eth_tx;

    /* register eth device */
    state = eth_device_init(&(zynqmp_eth_device.parent), "e0");
    if (RT_EOK == state)
    {
        LOG_D("emac device init success");
    }
    else
    {
        LOG_E("emac device init faild: %d", state);
        state = -RT_ERROR;
        return state;
    }

    return state;
}
INIT_DEVICE_EXPORT(rt_hw_zynqmp_eth_init);
