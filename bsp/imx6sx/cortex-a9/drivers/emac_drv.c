/*
 * COPYRIGHT (C) 2018, Real-Thread Information Technology Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-07-15     Bernard      The first version
 */

#include <rtthread.h>
#include <netif/ethernetif.h>

#include <soc_memory_map.h>
#include <stdint.h>
#include <enet/enet.h>
#include <lwipopts.h>
#include "emac_drv.h"

#define MAX_ADDR_LEN            6
#define IMX_EMAC_DEVICE(eth)    (struct emac_device*)(eth)

struct emac_device
{
    /* inherit from Ethernet device */
    struct eth_device parent;

    imx_enet_priv_t enet_priv;
    /* interface address info. */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];         /* MAC address  */
};
static struct emac_device _emac;

#define ENET_PHY_ADDR 1
extern int imx_enet_mii_type(imx_enet_priv_t * dev, enum imx_mii_type mii_type);
extern void imx_enet_iomux(void);
extern void imx_enet_phy_reset(void);

static unsigned char s_pkt_send[2048];
static unsigned char s_pkt_recv[2048];

void init_enet(struct emac_device* emac)
{
    // setup iomux for ENET
    imx_enet_iomux();
    imx_enet_phy_reset();

    // init enet0
    imx_enet_init(&emac->enet_priv, ENET_BASE_ADDR, ENET_PHY_ADDR);
    imx_enet_mii_type(&emac->enet_priv, RGMII);

    // init phy0.
    imx_enet_phy_init(&emac->enet_priv);

    // Check PHY link status.
    if (!(emac->enet_priv.status & ENET_STATUS_LINK_ON))
    {
        rt_kprintf("ENET link status check fail\n");
    }

    imx_enet_start(&emac->enet_priv, emac->dev_addr);
}

void imx_enet_isr(int vector, void *param)
{
    unsigned int value = 0;
    imx_enet_priv_t * dev = &(_emac.enet_priv);
    volatile hw_enet_t *enet_reg = dev->enet_reg;

    value = enet_reg->EIR.U;
    enet_reg->EIR.U = value & (~ENET_EVENT_MII);

    if (value & ENET_EVENT_TX_ERR)
    {
        dev->tx_busy = 0;
    }
    else if (value & ENET_EVENT_TX)
    {
        dev->tx_busy = 0;
    }

    if (value & ENET_EVENT_RX)
    {
        eth_device_ready(&(_emac.parent));
    }

    if (value & ENET_EVENT_HBERR)
    {
        // printf("WARNGING[POLL]: Hearbeat error!\n");
    }

    if (value & ENET_EVENT_EBERR)
    {
        // printf("WARNING[POLL]: Ethernet Bus Error!\n");
    }
}

static rt_err_t imx_emac_init(rt_device_t dev)
{
    struct emac_device *emac;

    emac = IMX_EMAC_DEVICE(dev);

    /* initialize enet */
    init_enet(emac);
    return RT_EOK;
}

static rt_err_t imx_emac_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t imx_emac_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t imx_emac_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t imx_emac_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t imx_emac_control(rt_device_t dev, int cmd, void *args)
{
    struct emac_device *emac;

    emac = IMX_EMAC_DEVICE(dev);
    RT_ASSERT(emac != RT_NULL);

    switch(cmd)
    {
    case NIOCTL_GADDR:
        /* get MAC address */
        if(args) rt_memcpy(args, emac->dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

/* Ethernet device interface */
/* transmit packet. */
rt_err_t imx_emac_tx(rt_device_t dev, struct pbuf* p)
{
    rt_err_t result = RT_EOK;
    struct emac_device *emac;

    emac = IMX_EMAC_DEVICE(dev);
    RT_ASSERT(emac != RT_NULL);

    /* copy pbuf to a whole ETH frame */
    pbuf_copy_partial(p, s_pkt_send, p->tot_len, 0);
    /* send to the enet */
    imx_enet_send(&emac->enet_priv, s_pkt_send, p->tot_len, 1);

    return result;
}

/* reception packet. */
struct pbuf *imx_emac_rx(rt_device_t dev)
{
    int len;
    struct pbuf* p = RT_NULL;
    struct emac_device *emac;

    emac = IMX_EMAC_DEVICE(dev);
    RT_ASSERT(emac != RT_NULL);

    imx_enet_recv(&emac->enet_priv, s_pkt_recv, &len);
    if (len > 0)
    {
        /* We allocate a pbuf chain of pbufs from the pool. */
        p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
        if (p != RT_NULL)
        {
            pbuf_take(p, s_pkt_recv, len);
        }
    }

    return p;
}

int imx_emac_hw_init(void)
{
    /* test MAC address */
    _emac.dev_addr[0] = 0x00;
    _emac.dev_addr[1] = 0x11;
    _emac.dev_addr[2] = 0x22;
    _emac.dev_addr[3] = 0x33;
    _emac.dev_addr[4] = 0x44;
    _emac.dev_addr[5] = 0x55;

    _emac.parent.parent.init       = imx_emac_init;
    _emac.parent.parent.open       = imx_emac_open;
    _emac.parent.parent.close      = imx_emac_close;
    _emac.parent.parent.read       = imx_emac_read;
    _emac.parent.parent.write      = imx_emac_write;
    _emac.parent.parent.control    = imx_emac_control;
    _emac.parent.parent.user_data  = RT_NULL;

    _emac.parent.eth_rx     = imx_emac_rx;
    _emac.parent.eth_tx     = imx_emac_tx;

    /* register ETH device */
    eth_device_init(&(_emac.parent), "e0");

    return 0;
}
INIT_DEVICE_EXPORT(imx_emac_hw_init);
