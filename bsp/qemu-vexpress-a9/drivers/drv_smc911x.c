/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/12/31     Bernard      Add license info
 */

#include <board.h>
#include <rtthread.h>
#include <netif/ethernetif.h>
#include <lwipopts.h>
#include <automac.h>

#define MAX_ADDR_LEN                6
#define SMC911X_EMAC_DEVICE(eth)    (struct eth_device_smc911x*)(eth)

#include "drv_smc911x.h"

#define DRIVERNAME "EMAC"

struct eth_device_smc911x
{
    /* inherit from Ethernet device */
    struct eth_device parent;
    /* interface address info. */
    rt_uint8_t enetaddr[MAX_ADDR_LEN];         /* MAC address  */

    uint32_t iobase;
    uint32_t irqno;
};
static struct eth_device_smc911x _emac;

int udelay(int value)
{
    return 0;
}

int mdelay(int value)
{
    return 0;
}

#if defined (CONFIG_SMC911X_32_BIT)
rt_inline uint32_t smc911x_reg_read(struct eth_device_smc911x *dev, uint32_t offset)
{
    return *(volatile uint32_t *)(dev->iobase + offset);
}

rt_inline void smc911x_reg_write(struct eth_device_smc911x *dev, uint32_t offset, uint32_t val)
{
    *(volatile uint32_t *)(dev->iobase + offset) = val;
}

#elif defined (CONFIG_SMC911X_16_BIT)
rt_inline uint32_t smc911x_reg_read(struct eth_device_smc911x *dev, uint32_t offset)
{
    volatile uint16_t *addr_16 = (uint16_t *)(dev->iobase + offset);
    return ((*addr_16 & 0x0000ffff) | (*(addr_16 + 1) << 16));
}

rt_inline void smc911x_reg_write(struct eth_device_smc911x *dev, uint32_t offset, uint32_t val)
{
    *(volatile uint16_t *)(dev->iobase + offset) = (uint16_t)val;
    *(volatile uint16_t *)(dev->iobase + offset + 2) = (uint16_t)(val >> 16);
}
#else
#error "SMC911X: undefined bus width"
#endif /* CONFIG_SMC911X_16_BIT */

struct chip_id
{
    uint16_t id;
    char *name;
};

static const struct chip_id chip_ids[] =
{
    { LAN9118_ID_89218, "LAN89218" },
    { LAN9118_ID_9115, "LAN9115" },
    { LAN9118_ID_9116, "LAN9116" },
    { LAN9118_ID_9117, "LAN9117" },
    { LAN9118_ID_9118, "LAN9118" },
    { LAN9210_ID_9211, "LAN9211" },
    { LAN9218_ID_9215, "LAN9215" },
    { LAN9218_ID_9216, "LAN9216" },
    { LAN9218_ID_9217, "LAN9217" },
    { LAN9218_ID_9218, "LAN9218" },
    { LAN9220_ID_9220, "LAN9220" },
    { LAN9220_ID_9221, "LAN9221" },
    { 0, RT_NULL },
};

static uint32_t smc911x_get_mac_csr(struct eth_device_smc911x *dev, uint8_t reg)
{
    while (smc911x_reg_read(dev, LAN9118_MAC_CSR_CMD) & LAN9118_MAC_CSR_CMD_BUSY) ;

    smc911x_reg_write(dev, LAN9118_MAC_CSR_CMD, LAN9118_MAC_CSR_CMD_BUSY | LAN9118_MAC_CSR_CMD_R | reg);

    while (smc911x_reg_read(dev, LAN9118_MAC_CSR_CMD) & LAN9118_MAC_CSR_CMD_BUSY) ;

    return smc911x_reg_read(dev, LAN9118_MAC_CSR_DATA);
}

static void smc911x_set_mac_csr(struct eth_device_smc911x *dev, uint8_t reg, uint32_t data)
{
    while (smc911x_reg_read(dev, LAN9118_MAC_CSR_CMD) & LAN9118_MAC_CSR_CMD_BUSY) ;

    smc911x_reg_write(dev, LAN9118_MAC_CSR_DATA, data);
    smc911x_reg_write(dev, LAN9118_MAC_CSR_CMD, LAN9118_MAC_CSR_CMD_BUSY | reg);

    while (smc911x_reg_read(dev, LAN9118_MAC_CSR_CMD) & LAN9118_MAC_CSR_CMD_BUSY) ;
}

static int smc911x_detect_chip(struct eth_device_smc911x *dev)
{
    unsigned long val, i;

    val = smc911x_reg_read(dev, LAN9118_BYTE_TEST);
    if (val == 0xffffffff)
    {
        /* Special case -- no chip present */
        return -1;
    }
    else if (val != 0x87654321)
    {
        rt_kprintf(DRIVERNAME ": Invalid chip endian 0x%08lx\n", val);
        return -1;
    }

    val = smc911x_reg_read(dev, LAN9118_ID_REV) >> 16;
    for (i = 0; chip_ids[i].id != 0; i++)
    {
        if (chip_ids[i].id == val) break;
    }

    if (!chip_ids[i].id)
    {
        rt_kprintf(DRIVERNAME ": Unknown chip ID %04lx\n", val);
        return -1;
    }

    return 0;
}

static void smc911x_reset(struct eth_device_smc911x *dev)
{
    int timeout;

    /*
    *  Take out of PM setting first
    *  Device is already wake up if LAN9118_PMT_CTRL_READY bit is set
    */
    if ((smc911x_reg_read(dev, LAN9118_PMT_CTRL) & LAN9118_PMT_CTRL_READY) == 0)
    {
        /* Write to the bytetest will take out of powerdown */
        smc911x_reg_write(dev, LAN9118_BYTE_TEST, 0x0);

        timeout = 10;

        while (timeout-- && !(smc911x_reg_read(dev, LAN9118_PMT_CTRL) & LAN9118_PMT_CTRL_READY))
            udelay(10);

        if (timeout < 0)
        {
            rt_kprintf(DRIVERNAME
                       ": timeout waiting for PM restore\n");
            return;
        }
    }

    /* Disable interrupts */
    smc911x_reg_write(dev, LAN9118_INT_EN, 0);
    smc911x_reg_write(dev, LAN9118_HW_CFG, LAN9118_HW_CFG_SRST);

    timeout = 1000;
    while (timeout-- && smc911x_reg_read(dev, LAN9118_E2P_CMD) & LAN9118_E2P_CMD)
        udelay(10);

    if (timeout < 0)
    {
        rt_kprintf(DRIVERNAME ": reset timeout\n");
        return;
    }

    /* Reset the FIFO level and flow control settings */
    smc911x_set_mac_csr(dev, LAN9118_FLOW, LAN9118_FLOW_FCPT(0xffff) | LAN9118_FLOW_FCEN);
    smc911x_reg_write(dev, LAN9118_AFC_CFG, 0x0050287F);

    /* Set to LED outputs */
    smc911x_reg_write(dev, LAN9118_GPIO_CFG, 0x70070000);
}

static void smc911x_handle_mac_address(struct eth_device_smc911x *dev)
{
    unsigned long addrh, addrl;
    uint8_t *m = dev->enetaddr;

    addrl = m[0] | (m[1] << 8) | (m[2] << 16) | (m[3] << 24);
    addrh = m[4] | (m[5] << 8);

    smc911x_set_mac_csr(dev, LAN9118_ADDRL, addrl);
    smc911x_set_mac_csr(dev, LAN9118_ADDRH, addrh);
}

static int smc911x_eth_phy_read(struct eth_device_smc911x *dev,
                                uint8_t phy, uint8_t reg, uint16_t *val)
{
    while (smc911x_get_mac_csr(dev, LAN9118_MII_ACC) & LAN9118_MII_ACC_MIIBZY) ;

    smc911x_set_mac_csr(dev, LAN9118_MII_ACC, phy << 11 | reg << 6 | LAN9118_MII_ACC_MIIBZY);

    while (smc911x_get_mac_csr(dev, LAN9118_MII_ACC) & LAN9118_MII_ACC_MIIBZY) ;

    *val = smc911x_get_mac_csr(dev, LAN9118_MII_DATA);

    return 0;
}

static int smc911x_eth_phy_write(struct eth_device_smc911x *dev,
                                 uint8_t phy, uint8_t reg, uint16_t  val)
{
    while (smc911x_get_mac_csr(dev, LAN9118_MII_ACC) & LAN9118_MII_ACC_MIIBZY)
        ;

    smc911x_set_mac_csr(dev, LAN9118_MII_DATA, val);
    smc911x_set_mac_csr(dev, LAN9118_MII_ACC,
                        phy << 11 | reg << 6 | LAN9118_MII_ACC_MIIBZY | LAN9118_MII_ACC_MIIWNR);

    while (smc911x_get_mac_csr(dev, LAN9118_MII_ACC) & LAN9118_MII_ACC_MIIBZY)
        ;
    return 0;
}

static int smc911x_phy_reset(struct eth_device_smc911x *dev)
{
    uint32_t reg;

    reg = smc911x_reg_read(dev, LAN9118_PMT_CTRL);
    reg &= ~0xfffff030;
    reg |= LAN9118_PMT_CTRL_PHY_RST;
    smc911x_reg_write(dev, LAN9118_PMT_CTRL, reg);

    mdelay(100);

    return 0;
}

static void smc911x_phy_configure(struct eth_device_smc911x *dev)
{
    int timeout;
    uint16_t status;

    smc911x_phy_reset(dev);

    smc911x_eth_phy_write(dev, 1, LAN9118_MII_BMCR, LAN9118_BMCR_RESET);
    mdelay(1);
    smc911x_eth_phy_write(dev, 1, LAN9118_MII_ADVERTISE, 0x01e1);
    smc911x_eth_phy_write(dev, 1, LAN9118_MII_BMCR, LAN9118_BMCR_ANENABLE | LAN9118_BMCR_ANRESTART);

    timeout = 5000;
    do
    {
        mdelay(1);
        if ((timeout--) == 0)
            goto err_out;

        if (smc911x_eth_phy_read(dev, 1, LAN9118_MII_BMSR, &status) != 0)
            goto err_out;
    }
    while (!(status & LAN9118_BMSR_LSTATUS));

    return;

err_out:
    rt_kprintf(DRIVERNAME ": autonegotiation timed out\n");
}

static void smc911x_enable(struct eth_device_smc911x *dev)
{
    /* Enable TX */
    smc911x_reg_write(dev, LAN9118_HW_CFG, 8 << 16 | LAN9118_HW_CFG_SF);

    smc911x_reg_write(dev, LAN9118_GPT_CFG, LAN9118_GPT_CFG_TIMER_EN | 10000);

    smc911x_reg_write(dev, LAN9118_TX_CFG, LAN9118_TX_CFG_TX_ON);

    /* no padding to start of packets */
    smc911x_reg_write(dev, LAN9118_RX_CFG, 0);

    smc911x_set_mac_csr(dev, LAN9118_MAC_CR, LAN9118_MAC_CR_TXEN | LAN9118_MAC_CR_RXEN |
                        LAN9118_MAC_CR_HBDIS);
}

#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
/* wrapper for smc911x_eth_phy_read */
static int smc911x_miiphy_read(struct mii_dev *bus, int phy, int devad,
                               int reg)
{
    uint16_t val = 0;
    struct eth_device_smc911x *dev = eth_get_dev_by_name(bus->name);
    if (dev)
    {
        int retval = smc911x_eth_phy_read(dev, phy, reg, &val);
        if (retval < 0)
            return retval;
        return val;
    }
    return -ENODEV;
}

/* wrapper for smc911x_eth_phy_write */
static int smc911x_miiphy_write(struct mii_dev *bus, int phy, int devad,
                                int reg, uint16_t val)
{
    struct eth_device_smc911x *dev = eth_get_dev_by_name(bus->name);
    if (dev)
        return smc911x_eth_phy_write(dev, phy, reg, val);
    return -ENODEV;
}
#endif

static void smc911x_isr(int vector, void *param)
{
    uint32_t status;
    struct eth_device_smc911x *emac;

    emac = SMC911X_EMAC_DEVICE(param);

    status = smc911x_reg_read(emac, LAN9118_INT_STS);

    if (status & LAN9118_INT_STS_RSFL)
    {
        eth_device_ready(&emac->parent);
    }
    smc911x_reg_write(emac, LAN9118_INT_STS, status);

    return ;
}

static rt_err_t smc911x_emac_init(rt_device_t dev)
{
    // uint32_t value;
    struct eth_device_smc911x *emac;

    emac = SMC911X_EMAC_DEVICE(dev);
    RT_ASSERT(emac != RT_NULL);

    smc911x_reset(emac);

    /* Configure the PHY, initialize the link state */
    smc911x_phy_configure(emac);
    smc911x_handle_mac_address(emac);

    /* Turn on Tx + Rx */
    smc911x_enable(emac);

#if 1
    /* Interrupt on every received packet */
    smc911x_reg_write(emac, LAN9118_FIFO_INT, 0x01 << 8);
    smc911x_reg_write(emac, LAN9118_INT_EN, LAN9118_INT_EN_RDFL_EN | LAN9118_INT_RSFL);

    /* enable interrupt */
    smc911x_reg_write(emac, LAN9118_IRQ_CFG, LAN9118_IRQ_CFG_IRQ_EN | LAN9118_IRQ_CFG_IRQ_POL | LAN9118_IRQ_CFG_IRQ_TYPE);
#else

    /* disable interrupt */
    smc911x_reg_write(emac, LAN9118_INT_EN, 0);
    value = smc911x_reg_read(emac, LAN9118_IRQ_CFG);
    value &= ~LAN9118_IRQ_CFG_IRQ_EN;
    smc911x_reg_write(emac, LAN9118_IRQ_CFG, value);
#endif

    rt_hw_interrupt_install(emac->irqno, smc911x_isr, emac, "smc911x");
    rt_hw_interrupt_umask(emac->irqno);

    return RT_EOK;
}

static rt_err_t smc911x_emac_control(rt_device_t dev, int cmd, void *args)
{
    struct eth_device_smc911x *emac;

    emac = SMC911X_EMAC_DEVICE(dev);
    RT_ASSERT(emac != RT_NULL);

    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get MAC address */
        if (args) rt_memcpy(args, emac->enetaddr, 6);
        else return -RT_ERROR;
        break;
    default :
        break;
    }
    return RT_EOK;
}

/* Ethernet device interface */
/* transmit packet. */
static uint8_t tx_buf[2048];
rt_err_t smc911x_emac_tx(rt_device_t dev, struct pbuf *p)
{
    struct eth_device_smc911x *emac;

    uint32_t *data;
    uint32_t tmplen;
    uint32_t status;
    uint32_t length;

    emac = SMC911X_EMAC_DEVICE(dev);
    RT_ASSERT(emac != RT_NULL);

    /* copy pbuf to a whole ETH frame */
    pbuf_copy_partial(p, tx_buf, p->tot_len, 0);

    /* send it out */
    data = (uint32_t *)tx_buf;
    length = p->tot_len;

    smc911x_reg_write(emac, LAN9118_TXDFIFOP, LAN9118_TXC_A_FS | LAN9118_TXC_A_LS | length);
    smc911x_reg_write(emac, LAN9118_TXDFIFOP, length);

    tmplen = (length + 3) / 4;
    while (tmplen--)
    {
        smc911x_reg_write(emac, LAN9118_TXDFIFOP, *data++);
    }

    /* wait for transmission */
    while (!(LAN9118_TX_FIFO_INF_TXSUSED(smc911x_reg_read(emac, LAN9118_TX_FIFO_INF))));

    /* get status. Ignore 'no carrier' error, it has no meaning for
     * full duplex operation
     */
    status = smc911x_reg_read(emac, LAN9118_TXSFIFOP) &
             (LAN9118_TXS_LOC | LAN9118_TXS_LCOL | LAN9118_TXS_ECOL |
              LAN9118_TXS_ED | LAN9118_TX_STS_UNDERRUN);

    if (!status) return 0;

    rt_kprintf(DRIVERNAME ": failed to send packet: %s%s%s%s%s\n",
               status & LAN9118_TXS_LOC ? "LAN9118_TXS_LOC " : "",
               status & LAN9118_TXS_LCOL ? "LAN9118_TXS_LCOL " : "",
               status & LAN9118_TXS_ECOL ? "LAN9118_TXS_ECOL " : "",
               status & LAN9118_TXS_ED ? "LAN9118_TXS_ED " : "",
               status & LAN9118_TX_STS_UNDERRUN ? "LAN9118_TX_STS_UNDERRUN" : "");

    return -RT_EIO;
}

/* reception packet. */
struct pbuf *smc911x_emac_rx(rt_device_t dev)
{
    struct pbuf *p = RT_NULL;
    struct eth_device_smc911x *emac;

    emac = SMC911X_EMAC_DEVICE(dev);
    RT_ASSERT(emac != RT_NULL);

    /* take the emac buffer to the pbuf */
    if (LAN9118_RX_FIFO_INF_RXSUSED(smc911x_reg_read(emac, LAN9118_RX_FIFO_INF)))
    {
        uint32_t status;
        uint32_t pktlen, tmplen;

        status = smc911x_reg_read(emac, LAN9118_RXSFIFOP);

        /* get frame length */
        pktlen = (status & LAN9118_RX_STS_PKT_LEN) >> 16;

        smc911x_reg_write(emac, LAN9118_RX_CFG, 0);

        tmplen = (pktlen + 3) / 4;

        /* allocate pbuf */
        p = pbuf_alloc(PBUF_RAW, tmplen * 4, PBUF_RAM);
        if (p)
        {
            uint32_t *data = (uint32_t *)p->payload;
            while (tmplen--)
            {
                *data++ = smc911x_reg_read(emac, LAN9118_RXDFIFOP);
            }
        }

        if (status & LAN9118_RXS_ES)
        {
            rt_kprintf(DRIVERNAME ": dropped bad packet. Status: 0x%08x\n", status);
        }
    }

    return p;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops smc911x_emac_ops =
{
    smc911x_emac_init,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    smc911x_emac_control
};
#endif

int smc911x_emac_hw_init(void)
{
    _emac.iobase = VEXPRESS_ETH_BASE;
    _emac.irqno  = IRQ_VEXPRESS_A9_ETH;

    if (smc911x_detect_chip(&_emac))
    {
        rt_kprintf("no smc911x network interface found!\n");
        return -1;
    }

    /* set INT CFG */
    smc911x_reg_write(&_emac, LAN9118_IRQ_CFG, LAN9118_IRQ_CFG_IRQ_POL | LAN9118_IRQ_CFG_IRQ_TYPE);

    /* test MAC address */
    _emac.enetaddr[0] = AUTOMAC0;
    _emac.enetaddr[1] = AUTOMAC1;
    _emac.enetaddr[2] = AUTOMAC2;
    _emac.enetaddr[3] = AUTOMAC3;
    _emac.enetaddr[4] = AUTOMAC4;
    _emac.enetaddr[5] = AUTOMAC5;

#ifdef RT_USING_DEVICE_OPS
    _emac.parent.parent.ops        = &smc911x_emac_ops;
#else
    _emac.parent.parent.init       = smc911x_emac_init;
    _emac.parent.parent.open       = RT_NULL;
    _emac.parent.parent.close      = RT_NULL;
    _emac.parent.parent.read       = RT_NULL;
    _emac.parent.parent.write      = RT_NULL;
    _emac.parent.parent.control    = smc911x_emac_control;
#endif
    _emac.parent.parent.user_data  = RT_NULL;
    _emac.parent.eth_rx     = smc911x_emac_rx;
    _emac.parent.eth_tx     = smc911x_emac_tx;

    /* register ETH device */
    eth_device_init(&(_emac.parent), "e0");

#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
    {
        int retval;
        struct mii_dev *mdiodev = mdio_alloc();
        if (!mdiodev)
            return -ENOMEM;
        strncpy(mdiodev->name, dev->name, MDIO_NAME_LEN);
        mdiodev->read = smc911x_miiphy_read;
        mdiodev->write = smc911x_miiphy_write;

        retval = mdio_register(mdiodev);
        if (retval < 0)
            return retval;
    }
#endif

    eth_device_linkchange(&_emac.parent, RT_TRUE);
    return 0;
}
INIT_APP_EXPORT(smc911x_emac_hw_init);
