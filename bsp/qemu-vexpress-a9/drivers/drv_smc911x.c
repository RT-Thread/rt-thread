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
    return *(volatile uint32_t*)(dev->iobase + offset);
}

rt_inline void smc911x_reg_write(struct eth_device_smc911x *dev, uint32_t offset, uint32_t val)
{
    *(volatile uint32_t*)(dev->iobase + offset) = val;
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
    { CHIP_89218,"LAN89218" },
    { CHIP_9115, "LAN9115" },
    { CHIP_9116, "LAN9116" },
    { CHIP_9117, "LAN9117" },
    { CHIP_9118, "LAN9118" },
    { CHIP_9211, "LAN9211" },
    { CHIP_9215, "LAN9215" },
    { CHIP_9216, "LAN9216" },
    { CHIP_9217, "LAN9217" },
    { CHIP_9218, "LAN9218" },
    { CHIP_9220, "LAN9220" },
    { CHIP_9221, "LAN9221" },
    { 0, RT_NULL },
};

static uint32_t smc911x_get_mac_csr(struct eth_device_smc911x *dev, uint8_t reg)
{
    while (smc911x_reg_read(dev, MAC_CSR_CMD) & MAC_CSR_CMD_CSR_BUSY) ;

    smc911x_reg_write(dev, MAC_CSR_CMD, MAC_CSR_CMD_CSR_BUSY | MAC_CSR_CMD_R_NOT_W | reg);

    while (smc911x_reg_read(dev, MAC_CSR_CMD) & MAC_CSR_CMD_CSR_BUSY) ;

    return smc911x_reg_read(dev, MAC_CSR_DATA);
}

static void smc911x_set_mac_csr(struct eth_device_smc911x *dev, uint8_t reg, uint32_t data)
{
    while (smc911x_reg_read(dev, MAC_CSR_CMD) & MAC_CSR_CMD_CSR_BUSY) ;

    smc911x_reg_write(dev, MAC_CSR_DATA, data);
    smc911x_reg_write(dev, MAC_CSR_CMD, MAC_CSR_CMD_CSR_BUSY | reg);

    while (smc911x_reg_read(dev, MAC_CSR_CMD) & MAC_CSR_CMD_CSR_BUSY) ;
}

static int smc911x_detect_chip(struct eth_device_smc911x *dev)
{
    unsigned long val, i;

    val = smc911x_reg_read(dev, BYTE_TEST);
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

    val = smc911x_reg_read(dev, ID_REV) >> 16;
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
    *  Device is already wake up if PMT_CTRL_READY bit is set
    */
    if ((smc911x_reg_read(dev, PMT_CTRL) & PMT_CTRL_READY) == 0)
    {
        /* Write to the bytetest will take out of powerdown */
        smc911x_reg_write(dev, BYTE_TEST, 0x0);

        timeout = 10;

        while (timeout-- && !(smc911x_reg_read(dev, PMT_CTRL) & PMT_CTRL_READY))
            udelay(10);

        if (timeout < 0)
        {
            rt_kprintf(DRIVERNAME
                       ": timeout waiting for PM restore\n");
            return;
        }
    }

    /* Disable interrupts */
    smc911x_reg_write(dev, INT_EN, 0);
    smc911x_reg_write(dev, HW_CFG, HW_CFG_SRST);

    timeout = 1000;
    while (timeout-- && smc911x_reg_read(dev, E2P_CMD) & E2P_CMD_EPC_BUSY)
        udelay(10);

    if (timeout < 0)
    {
        rt_kprintf(DRIVERNAME ": reset timeout\n");
        return;
    }

    /* Reset the FIFO level and flow control settings */
    smc911x_set_mac_csr(dev, FLOW, FLOW_FCPT | FLOW_FCEN);
    smc911x_reg_write(dev, AFC_CFG, 0x0050287F);

    /* Set to LED outputs */
    smc911x_reg_write(dev, GPIO_CFG, 0x70070000);
}

static void smc911x_handle_mac_address(struct eth_device_smc911x *dev)
{
    unsigned long addrh, addrl;
    uint8_t *m = dev->enetaddr;

    addrl = m[0] | (m[1] << 8) | (m[2] << 16) | (m[3] << 24);
    addrh = m[4] | (m[5] << 8);

    smc911x_set_mac_csr(dev, ADDRL, addrl);
    smc911x_set_mac_csr(dev, ADDRH, addrh);
}

static int smc911x_eth_phy_read(struct eth_device_smc911x *dev,
                                uint8_t phy, uint8_t reg, uint16_t *val)
{
    while (smc911x_get_mac_csr(dev, MII_ACC) & MII_ACC_MII_BUSY) ;

    smc911x_set_mac_csr(dev, MII_ACC, phy << 11 | reg << 6 | MII_ACC_MII_BUSY);

    while (smc911x_get_mac_csr(dev, MII_ACC) & MII_ACC_MII_BUSY) ;

    *val = smc911x_get_mac_csr(dev, MII_DATA);

    return 0;
}

static int smc911x_eth_phy_write(struct eth_device_smc911x *dev,
                                 uint8_t phy, uint8_t reg, uint16_t  val)
{
    while (smc911x_get_mac_csr(dev, MII_ACC) & MII_ACC_MII_BUSY)
        ;

    smc911x_set_mac_csr(dev, MII_DATA, val);
    smc911x_set_mac_csr(dev, MII_ACC,
                        phy << 11 | reg << 6 | MII_ACC_MII_BUSY | MII_ACC_MII_WRITE);

    while (smc911x_get_mac_csr(dev, MII_ACC) & MII_ACC_MII_BUSY)
        ;
    return 0;
}

static int smc911x_phy_reset(struct eth_device_smc911x *dev)
{
    uint32_t reg;

    reg = smc911x_reg_read(dev, PMT_CTRL);
    reg &= ~0xfffff030;
    reg |= PMT_CTRL_PHY_RST;
    smc911x_reg_write(dev, PMT_CTRL, reg);

    mdelay(100);

    return 0;
}

static void smc911x_phy_configure(struct eth_device_smc911x *dev)
{
    int timeout;
    uint16_t status;

    smc911x_phy_reset(dev);

    smc911x_eth_phy_write(dev, 1, MII_BMCR, BMCR_RESET);
    mdelay(1);
    smc911x_eth_phy_write(dev, 1, MII_ADVERTISE, 0x01e1);
    smc911x_eth_phy_write(dev, 1, MII_BMCR, BMCR_ANENABLE | BMCR_ANRESTART);

    timeout = 5000;
    do
    {
        mdelay(1);
        if ((timeout--) == 0)
            goto err_out;

        if (smc911x_eth_phy_read(dev, 1, MII_BMSR, &status) != 0)
            goto err_out;
    }
    while (!(status & BMSR_LSTATUS));

    return;

err_out:
    rt_kprintf(DRIVERNAME ": autonegotiation timed out\n");
}

static void smc911x_enable(struct eth_device_smc911x *dev)
{
    /* Enable TX */
    smc911x_reg_write(dev, HW_CFG, 8 << 16 | HW_CFG_SF);

    smc911x_reg_write(dev, GPT_CFG, GPT_CFG_TIMER_EN | 10000);

    smc911x_reg_write(dev, TX_CFG, TX_CFG_TX_ON);

    /* no padding to start of packets */
    smc911x_reg_write(dev, RX_CFG, 0);

    smc911x_set_mac_csr(dev, MAC_CR, MAC_CR_TXEN | MAC_CR_RXEN |
                        MAC_CR_HBDIS);
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

    status = smc911x_reg_read(emac, INT_STS);
    
    if (status & INT_STS_RSFL)
    {
        eth_device_ready(&emac->parent);
    }
    smc911x_reg_write(emac, INT_STS, status);

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
    smc911x_reg_write(emac, FIFO_INT, 0x01 << 8);
    smc911x_reg_write(emac, INT_EN, INT_EN_RDFL_EN | INT_EN_RSFL_EN);

    /* enable interrupt */
    smc911x_reg_write(emac, INT_CFG, INT_CFG_IRQ_EN | INT_CFG_IRQ_POL | INT_CFG_IRQ_TYPE);
#else

    /* disable interrupt */
    smc911x_reg_write(emac, INT_EN, 0);
    value = smc911x_reg_read(emac, INT_CFG);
    value &= ~INT_CFG_IRQ_EN;
    smc911x_reg_write(emac, INT_CFG, value);
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

    switch(cmd)
    {
    case NIOCTL_GADDR:
        /* get MAC address */
        if(args) rt_memcpy(args, emac->enetaddr, 6);
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
rt_err_t smc911x_emac_tx(rt_device_t dev, struct pbuf* p)
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
    data = (uint32_t*)tx_buf;
    length = p->tot_len;

    smc911x_reg_write(emac, TX_DATA_FIFO, TX_CMD_A_INT_FIRST_SEG | TX_CMD_A_INT_LAST_SEG | length);
    smc911x_reg_write(emac, TX_DATA_FIFO, length);

    tmplen = (length + 3) / 4;
    while (tmplen--)
    {
        smc911x_reg_write(emac, TX_DATA_FIFO, *data++);
    }

    /* wait for transmission */
    while (!((smc911x_reg_read(emac, TX_FIFO_INF) & TX_FIFO_INF_TSUSED) >> 16));

    /* get status. Ignore 'no carrier' error, it has no meaning for
     * full duplex operation
     */
    status = smc911x_reg_read(emac, TX_STATUS_FIFO) &
             (TX_STS_LOC | TX_STS_LATE_COLL | TX_STS_MANY_COLL |
              TX_STS_MANY_DEFER | TX_STS_UNDERRUN);

    if (!status) return 0;

    rt_kprintf(DRIVERNAME ": failed to send packet: %s%s%s%s%s\n",
               status & TX_STS_LOC ? "TX_STS_LOC " : "",
               status & TX_STS_LATE_COLL ? "TX_STS_LATE_COLL " : "",
               status & TX_STS_MANY_COLL ? "TX_STS_MANY_COLL " : "",
               status & TX_STS_MANY_DEFER ? "TX_STS_MANY_DEFER " : "",
               status & TX_STS_UNDERRUN ? "TX_STS_UNDERRUN" : "");

    return -RT_EIO;
}

/* reception packet. */
struct pbuf *smc911x_emac_rx(rt_device_t dev)
{
    struct pbuf* p = RT_NULL;
    struct eth_device_smc911x *emac;

    emac = SMC911X_EMAC_DEVICE(dev);
    RT_ASSERT(emac != RT_NULL);

    /* take the emac buffer to the pbuf */
    if ((smc911x_reg_read(emac, RX_FIFO_INF) & RX_FIFO_INF_RXSUSED) >> 16)
    {
        uint32_t status;
        uint32_t pktlen, tmplen;

        status = smc911x_reg_read(emac, RX_STATUS_FIFO);

        /* get frame length */
        pktlen = (status & RX_STS_PKT_LEN) >> 16;

        smc911x_reg_write(emac, RX_CFG, 0);

        tmplen = (pktlen + 3) / 4;

        /* allocate pbuf */
        p = pbuf_alloc(PBUF_RAW, tmplen * 4, PBUF_RAM);
        if (p)
        {
            uint32_t *data = (uint32_t *)p->payload;
            while (tmplen--)
            {
                *data++ = smc911x_reg_read(emac, RX_DATA_FIFO);
            }
        }

        if (status & RX_STS_ES)
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
    smc911x_reg_write(&_emac, INT_CFG, INT_CFG_IRQ_POL | INT_CFG_IRQ_TYPE);

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
