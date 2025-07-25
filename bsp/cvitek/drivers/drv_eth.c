/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/04/25     flyingcys    first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"

#define DBG_TAG     "drv.eth"
#define DBG_LEVEL   DBG_INFO
#include <rtdbg.h>

#include <lwip/sys.h>
#include <netif/ethernetif.h>

#include "drv_eth.h"


// #define ETH_TX_DUMP
// #define ETH_RX_DUMP

#define MAX_ADDR_LEN        6
#define DETECT_THREAD_PRIORITY         RT_THREAD_PRIORITY_MAX - 2
#define DETECT_THREAD_STACK_SIZE       4096

struct _dw_eth
{
    rt_ubase_t base;
    rt_uint32_t irq;

    struct eth_device parent;               /* inherit from ethernet device */

    rt_uint8_t dev_addr[MAX_ADDR_LEN];      /* interface address info, hw address */

    struct rt_semaphore rx_sem;
};
static struct _dw_eth dw_eth_device = {0};

#define GMAC_BUF_LEN (1500 + 20)
static uint8_t g_mac_addr[6] = {0xf2, 0x42, 0x9f, 0xa5, 0x0a, 0x72};
static uint8_t g_mac_phy_init_finish = 0;
static eth_mac_handle_t g_mac_handle;
static eth_phy_handle_t g_phy_handle;

static uint8_t SendDataBuf[GMAC_BUF_LEN];
static uint8_t RecvDataBuf[GMAC_BUF_LEN];

static void cvi_ephy_id_init(void)
{
    // set rg_ephy_apb_rw_sel 0x0804@[0]=1/APB by using APB interface
    mmio_write_32(ETH_PHY_BASE + 0x804, 0x0001);

    // Release 0x0800[0]=0/shutdown
    mmio_write_32(ETH_PHY_BASE + 0x800, 0x0900);

    // Release 0x0800[2]=1/dig_rst_n, Let mii_reg can be accessabile
    mmio_write_32(ETH_PHY_BASE + 0x800, 0x0904);

    // PHY_ID
    mmio_write_32(ETH_PHY_BASE + 0x008, 0x0043);
    mmio_write_32(ETH_PHY_BASE + 0x00c, 0x5649);

    // switch to MDIO control by ETH_MAC
    mmio_write_32(ETH_PHY_BASE + 0x804, 0x0000);
}

static int cvi_eth_mac_phy_enable(uint32_t enable)
{
    eth_mac_addr_t addr;
    int32_t ret;

    if ((g_mac_phy_init_finish == 0) && enable)
    {
        /* startup mac */
        ret = cvi_eth_mac_control(g_mac_handle, CSI_ETH_MAC_CONFIGURE, 1);
        if (ret != 0)
        {
           LOG_E("Failed to control mac");
            return -1;
        }

        /* Start up the PHY */
        ret = cvi_eth_phy_power_control(g_phy_handle, CSI_ETH_POWER_FULL);
        if (ret != 0)
        {
           LOG_E("Failed to control phy, ret:0x%d", ret);
            return -1;
        }
    }

    /* enable mac TX/RX */
    ret = cvi_eth_mac_control(g_mac_handle, CSI_ETH_MAC_CONTROL_TX, enable ? 1 : 0);
    if (ret != 0)
    {
       LOG_E("Failed to enable mac TX");
       return ret;
    }

    ret = cvi_eth_mac_control(g_mac_handle, CSI_ETH_MAC_CONTROL_RX, enable ? 1 : 0);
    if (ret != 0)
    {
       LOG_E("Failed to enable mac RX");
       return ret;
    }

    /* set mac address */
    rt_memcpy(addr.b, g_mac_addr, sizeof(g_mac_addr));
    ret = cvi_eth_mac_set_macaddr(g_mac_handle, &addr);
    if (ret != 0)
    {
       LOG_E("Failed to set mac address");
        return -1;
    }

    /* adjust mac link parameter */
    ret = cvi_eth_mac_control(g_mac_handle, DRV_ETH_MAC_ADJUST_LINK, 1);
    if (ret != 0)
    {
       LOG_E("Failed to adjust link");
        return -1;
    }

    return 0;
}

static int32_t fn_phy_read(uint8_t phy_addr, uint8_t reg_addr, uint16_t *data)
{
    return dw_eth_mac_phy_read(g_mac_handle, phy_addr, reg_addr, data);
}

static int32_t fn_phy_write(uint8_t phy_addr, uint8_t reg_addr, uint16_t data)
{
    return dw_eth_mac_phy_write(g_mac_handle, phy_addr, reg_addr, data);
}

static void dw_gmac_handler_irq(int vector, void *param)
{
    gmac_dev_t *mac_dev = (gmac_dev_t *)param;
    struct dw_gmac_dma_regs *dma_reg = mac_dev->priv->dma_regs_p;
    uint32_t dma_status;
    uint32_t event = 0;

    /* no ephy or ephy link down */
    if (!mac_dev->phy_dev || !mac_dev->phy_dev->link_state)
        return;

    /* read and clear dma interrupt */
    dma_status = dma_reg->status;

    /* Clear the interrupt by writing a logic 1 to the CSR5[15-0] */
    dma_reg->status = dma_status & 0x1ffff;

    if (dma_status & CVI_DMA_STATUS_RI)
    {
        LOG_D("CVI_DMA_STATUS_RI");

        /* a frame has been received */
        eth_device_ready(&(dw_eth_device.parent));
    }

    if (dma_status & CVI_DMA_STATUS_TI)
    {
        LOG_D("CVI_DMA_STATUS_TI");
    }

    if (dma_status & CVI_DMA_STATUS_ERI)
    {
        LOG_D("CVI_DMA_STATUS_TI");
    }
}

static void phy_link_detect(void *param)
{
    int link_status = -1;
    int link_status_old = -1;
    int ret = -1;

    while (1)
    {
        link_status = eth_phy_update_link(g_phy_handle);
        LOG_D("eth link status: %d", link_status);

        if (link_status_old != link_status)
        {
            if (link_status == 0)
            {
                LOG_I("eth link up");
                eth_device_linkchange(&(dw_eth_device.parent), RT_TRUE);
            }
            else
            {
                LOG_I("eth link down");
                eth_device_linkchange(&(dw_eth_device.parent), RT_FALSE);
            }

            link_status_old = link_status;
        }
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}

static rt_err_t rt_dw_eth_init(rt_device_t dev)
{
    struct _dw_eth *dw_eth;
    struct eth_device *eth_dev;

    RT_ASSERT(dev != RT_NULL);
    eth_dev = rt_container_of(dev, struct eth_device, parent);
    if (eth_dev == RT_NULL)
        return -RT_ERROR;

    dw_eth = rt_container_of(eth_dev, struct _dw_eth, parent);
    if (dw_eth == RT_NULL)
        return -RT_ERROR;

    /* init phy id */
    cvi_ephy_id_init();

    /* initialize MAC & PHY */
    g_mac_handle = cvi_eth_mac_init(dw_eth->base);
    if (g_mac_handle == NULL)
        return -RT_ERROR;

    g_phy_handle = cvi_eth_phy_init(fn_phy_read, fn_phy_write);

    dw_eth_mac_connect_phy(g_mac_handle, g_phy_handle);

    if (cvi_eth_mac_phy_enable(1))
    {
       LOG_E("PHY MAC init fail");
        return -RT_ERROR;
    }

    rt_hw_interrupt_install(dw_eth->irq, dw_gmac_handler_irq, g_mac_handle, "e0");
    rt_hw_interrupt_umask(dw_eth->irq);

    LOG_D("PHY MAC init success");

    rt_thread_t link_detect;
    link_detect = rt_thread_create("link_detect",
                            phy_link_detect,
                            (void *)&dw_eth_device,
                            DETECT_THREAD_STACK_SIZE,
                            DETECT_THREAD_PRIORITY,
                            2);
    if (link_detect != RT_NULL)
    {
        rt_thread_startup(link_detect);
    }
    else
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t rt_dw_eth_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
        case NIOCTL_GADDR:
            if (args)
                rt_memcpy(args, g_mac_addr, MAX_ADDR_LEN);
        break;

        default:

        break;
    }

    return RT_EOK;
}

#if defined(ETH_RX_DUMP) || defined(ETH_TX_DUMP)
static void packet_dump(const char *msg, const struct pbuf *p)
{
    const struct pbuf *q;
    rt_uint32_t i, j;
    rt_uint8_t *ptr;

    rt_kprintf("%s %d byte\n", msg, p->tot_len);

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

            i ++;
            ptr ++;
        }
    }

    rt_kprintf("\n\n");
}
#endif

struct pbuf* rt_dw_eth_rx(rt_device_t dev)
{
    struct pbuf *p = NULL;
    struct pbuf *q = NULL;
    uint32_t i = 0;

    int32_t len = cvi_eth_mac_read_frame(g_mac_handle, RecvDataBuf, GMAC_BUF_LEN);
    if ((len <= 0) || (len > GMAC_BUF_LEN))
    {
        return NULL;
    }

#if RT_LWIP_ETH_PAD_SIZE
  len += RT_LWIP_ETH_PAD_SIZE; /* allow room for Ethernet padding */
#endif

    p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
    if (p == NULL)
    {
        LOG_E("eth_rx: pbuf_alloc failed");
        len = 0;
        return NULL;
    }

#if RT_LWIP_ETH_PAD_SIZE
    pbuf_header(p, -RT_LWIP_ETH_PAD_SIZE); /* drop the padding word */
#endif

    /* We iterate over the pbuf chain until we have read the entire
     * packet into the pbuf. */
    for (q = p; q != NULL; q = q->next)
    {
        /* Read enough bytes to fill this pbuf in the chain. The
        * available data in the pbuf is given by the q->len
        * variable.
        * This does not necessarily have to be a memcpy, you can also preallocate
        * pbufs for a DMA-enabled MAC and after receiving truncate it to the
        * actually received size. In this case, ensure the tot_len member of the
        * pbuf is the sum of the chained pbuf len members.
        */
        rt_memcpy((u8_t*)q->payload, (u8_t*)&RecvDataBuf[i], q->len);
        i = i + q->len;
    }

    if ((i != p->tot_len) || (i > len))
    {
        return NULL;
    }

#ifdef ETH_RX_DUMP
    packet_dump("RX dump", p);
#endif /* ETH_RX_DUMP */

    return p;

}

rt_err_t rt_dw_eth_tx(rt_device_t dev, struct pbuf* p)
{
    rt_err_t ret = RT_EOK;

#ifdef ETH_TX_DUMP
    packet_dump("send", p);
#endif

    struct pbuf *q;
    uint32_t len = 0;


#if RT_LWIP_ETH_PAD_SIZE
    pbuf_header(p, -RT_LWIP_ETH_PAD_SIZE); /* drop the padding word */
#endif

    for (q = p; q != NULL; q = q->next)
    {
        /* Send the data from the pbuf to the interface, one pbuf at a
        time. The size of the data in each pbuf is kept in the ->len
        variable. */
        MEMCPY((uint8_t *)&SendDataBuf[len], (uint8_t *)q->payload, q->len);
        len = len + q->len;
        if ((len > GMAC_BUF_LEN) || (len > p->tot_len))
        {
            LOG_E("rt_dw_eth_tx: error, len=%d, tot_len=%d", len, p->tot_len);
            return -RT_ERROR;
        }
    }

    if (len == p->tot_len)
    {
        if (cvi_eth_mac_send_frame(g_mac_handle, SendDataBuf, len) < 0)
            ret = -RT_ERROR;
    }
    else
        ret = -RT_ERROR;

#if RT_LWIP_ETH_PAD_SIZE
    pbuf_header(p, RT_LWIP_ETH_PAD_SIZE); /* reclaim the padding word */
#endif

    return ret;
}

const static struct rt_device_ops dw_eth_ops =
{
    rt_dw_eth_init,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    rt_dw_eth_control
};

static int rthw_eth_init(void)
{
    rt_err_t ret = RT_EOK;

    dw_eth_device.base = (rt_ubase_t)DW_MAC_BASE;
    dw_eth_device.irq = DW_MAC_IRQ;

    dw_eth_device.parent.parent.ops = &dw_eth_ops;

    dw_eth_device.parent.eth_rx = rt_dw_eth_rx;
    dw_eth_device.parent.eth_tx = rt_dw_eth_tx;

    ret = rt_sem_init(&dw_eth_device.rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    if (ret != RT_EOK)
    {
        LOG_E("rt_sem_init failed: %d", ret);
        return ret;
    }

    ret = eth_device_init(&dw_eth_device.parent, "e0");
    if (ret != RT_EOK)
    {
        LOG_E("eth_device_init failed: %d", ret);
        return ret;
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rthw_eth_init);
