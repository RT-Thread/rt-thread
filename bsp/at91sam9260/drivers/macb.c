/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-18     weety      first version
 */

#include <rtthread.h>
#include <netif/ethernetif.h>
#include "lwipopts.h"
#include <at91sam926x.h>
#include "macb.h"

#define MMU_NOCACHE_ADDR(a)         ((rt_uint32_t)a | (1UL<<31))

extern void mmu_clean_dcache(rt_uint32_t buffer, rt_uint32_t size);
extern void mmu_invalidate_dcache(rt_uint32_t buffer, rt_uint32_t size);

/* Cache macros - Packet buffers would be from pbuf pool which is cached */
#define EMAC_VIRT_NOCACHE(addr) (addr)
#define EMAC_CACHE_INVALIDATE(addr, size) \
    mmu_invalidate_dcache((rt_uint32_t)addr, size)
#define EMAC_CACHE_WRITEBACK(addr, size) \
    mmu_clean_dcache((rt_uint32_t)addr, size)
#define EMAC_CACHE_WRITEBACK_INVALIDATE(addr, size) \
    mmu_clean_invalidated_dcache((rt_uint32_t)addr, size)

/* EMAC has BD's in cached memory - so need cache functions */
#define BD_CACHE_INVALIDATE(addr, size)
#define BD_CACHE_WRITEBACK(addr, size)
#define BD_CACHE_WRITEBACK_INVALIDATE(addr, size)

/* EMAC internal utility function */
rt_inline unsigned long emac_virt_to_phys(unsigned long addr)
{
    return addr;
}


#define AT91SAM9260_SRAM0_VIRT_BASE (0x90000000)

#define MACB_TX_SRAM

#if defined(MACB_TX_SRAM)
#define MACB_TX_RING_SIZE       2
#define MACB_TX_BUFFER_SIZE     (1536 * MACB_TX_RING_SIZE)
#define TX_RING_BYTES           (sizeof(struct macb_dma_desc) * MACB_TX_RING_SIZE)
#else
#define MACB_TX_RING_SIZE       16
#define MACB_TX_BUFFER_SIZE     (1536 * MACB_TX_RING_SIZE)
#endif

#define MACB_RX_BUFFER_SIZE     (4096*4)
#define MACB_RX_RING_SIZE       (MACB_RX_BUFFER_SIZE / 128)

#define DEF_TX_RING_PENDING (MACB_TX_RING_SIZE)

#define TX_RING_GAP(macb)                       \
    (MACB_TX_RING_SIZE - (macb)->tx_pending)

#define TX_BUFFS_AVAIL(macb)                    \
    (((macb)->tx_tail <= (macb)->tx_head) ?         \
     (macb)->tx_tail + (macb)->tx_pending - (macb)->tx_head :   \
     (macb)->tx_tail - (macb)->tx_head - TX_RING_GAP(macb))

#define NEXT_TX(n)      (((n) + 1) & (MACB_TX_RING_SIZE - 1))

#define NEXT_RX(n)      (((n) + 1) & (MACB_RX_RING_SIZE - 1))

/* minimum number of free TX descriptors before waking up TX process */
#define MACB_TX_WAKEUP_THRESH   (MACB_TX_RING_SIZE / 4)

#define MACB_RX_INT_FLAGS   (MACB_BIT(RCOMP) | MACB_BIT(RXUBR)  \
                 | MACB_BIT(ISR_ROVR))

#define MACB_TX_TIMEOUT     1000
#define MACB_AUTONEG_TIMEOUT    5000000
#define MACB_LINK_TIMEOUT       500000

#define CONFIG_RMII

struct macb_dma_desc {
    rt_uint32_t addr;
    rt_uint32_t ctrl;
};

#define RXADDR_USED     0x00000001
#define RXADDR_WRAP     0x00000002

#define RXBUF_FRMLEN_MASK   0x00000fff
#define RXBUF_FRAME_START   0x00004000
#define RXBUF_FRAME_END     0x00008000
#define RXBUF_TYPEID_MATCH  0x00400000
#define RXBUF_ADDR4_MATCH   0x00800000
#define RXBUF_ADDR3_MATCH   0x01000000
#define RXBUF_ADDR2_MATCH   0x02000000
#define RXBUF_ADDR1_MATCH   0x04000000
#define RXBUF_BROADCAST     0x80000000

#define TXBUF_FRMLEN_MASK   0x000007ff
#define TXBUF_FRAME_END     0x00008000
#define TXBUF_NOCRC     0x00010000
#define TXBUF_EXHAUSTED     0x08000000
#define TXBUF_UNDERRUN      0x10000000
#define TXBUF_MAXRETRY      0x20000000
#define TXBUF_WRAP      0x40000000
#define TXBUF_USED      0x80000000

/* Duplex, half or full. */
#define DUPLEX_HALF     0x00
#define DUPLEX_FULL     0x01

#define MAX_ADDR_LEN 6
struct rt_macb_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;

    unsigned int        regs;

    unsigned int        rx_tail;
    unsigned int        tx_head;
    unsigned int        tx_tail;
    unsigned int        rx_pending;
    unsigned int        tx_pending;

    void            *rx_buffer;
    void            *tx_buffer;
    struct macb_dma_desc    *rx_ring;
    struct macb_dma_desc    *tx_ring;

    unsigned long       rx_buffer_dma;
    unsigned long       tx_buffer_dma;
    unsigned long       rx_ring_dma;
    unsigned long       tx_ring_dma;

    unsigned int        tx_stop;

    /* interface address info. */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];     /* hw address   */
    unsigned short      phy_addr;

    struct rt_semaphore mdio_bus_lock;
    struct rt_semaphore tx_lock;
    struct rt_semaphore rx_lock;
    struct rt_semaphore tx_ack;
    rt_uint32_t  speed;
    rt_uint32_t  duplex;
    rt_uint32_t link;
    struct rt_timer  timer;
};
static struct rt_macb_eth macb_device;

static void macb_tx(struct rt_macb_eth *macb);

static void udelay(rt_uint32_t us)
{
    rt_uint32_t len;
    for (;us > 0; us --)
        for (len = 0; len < 10; len++ );
}

static void rt_macb_isr(int irq, void *param)
{
    struct rt_macb_eth *macb = (struct rt_macb_eth *)param;
    rt_device_t dev = &(macb->parent.parent);
    rt_uint32_t status, rsr, tsr;

    status = macb_readl(macb, ISR);

    while (status) {

        if (status & MACB_RX_INT_FLAGS)
        {
            rsr = macb_readl(macb, RSR);
            macb_writel(macb, RSR, rsr);
            /* a frame has been received */
            eth_device_ready(&(macb_device.parent));

        }

        if (status & (MACB_BIT(TCOMP) | MACB_BIT(ISR_TUND) |
                MACB_BIT(ISR_RLE)))
        {
            macb_tx(macb);
        }

        /*
         * Link change detection isn't possible with RMII, so we'll
         * add that if/when we get our hands on a full-blown MII PHY.
         */

        if (status & MACB_BIT(HRESP))
        {
            /*
             * TODO: Reset the hardware, and maybe move the printk
             * to a lower-priority context as well (work queue?)
             */
            rt_kprintf("%s: DMA bus error: HRESP not OK\n",
                   dev->parent.name);
        }

        status = macb_readl(macb, ISR);
    }


}

static int macb_mdio_write(struct rt_macb_eth *macb, rt_uint8_t reg, rt_uint16_t value)
{
    unsigned long netctl;
    unsigned long netstat;
    unsigned long frame;

    rt_sem_take(&macb->mdio_bus_lock, RT_WAITING_FOREVER);
    netctl = macb_readl(macb, NCR);
    netctl |= MACB_BIT(MPE);
    macb_writel(macb, NCR, netctl);

    frame = (MACB_BF(SOF, 1)
         | MACB_BF(RW, 1)
         | MACB_BF(PHYA, macb->phy_addr)
         | MACB_BF(REGA, reg)
         | MACB_BF(CODE, 2)
         | MACB_BF(DATA, value));
    macb_writel(macb, MAN, frame);

    do {
        netstat = macb_readl(macb, NSR);
    } while (!(netstat & MACB_BIT(IDLE)));

    netctl = macb_readl(macb, NCR);
    netctl &= ~MACB_BIT(MPE);
    macb_writel(macb, NCR, netctl);
    rt_sem_release(&macb->mdio_bus_lock);
}

static int macb_mdio_read(struct rt_macb_eth *macb, rt_uint8_t reg)
{
    unsigned long netctl;
    unsigned long netstat;
    unsigned long frame;

    rt_sem_take(&macb->mdio_bus_lock, RT_WAITING_FOREVER);
    netctl = macb_readl(macb, NCR);
    netctl |= MACB_BIT(MPE);
    macb_writel(macb, NCR, netctl);

    frame = (MACB_BF(SOF, 1)
         | MACB_BF(RW, 2)
         | MACB_BF(PHYA, macb->phy_addr)
         | MACB_BF(REGA, reg)
         | MACB_BF(CODE, 2));
    macb_writel(macb, MAN, frame);

    do {
        netstat = macb_readl(macb, NSR);
    } while (!(netstat & MACB_BIT(IDLE)));

    frame = macb_readl(macb, MAN);

    netctl = macb_readl(macb, NCR);
    netctl &= ~MACB_BIT(MPE);
    macb_writel(macb, NCR, netctl);
    rt_sem_release(&macb->mdio_bus_lock);

    return MACB_BFEXT(DATA, frame);
}

static void macb_phy_reset(rt_device_t dev)
{
    int i;
    rt_uint16_t status, adv;
    struct rt_macb_eth *macb = dev->user_data;;

    adv = ADVERTISE_CSMA | ADVERTISE_ALL;
    macb_mdio_write(macb, MII_ADVERTISE, adv);
    rt_kprintf("%s: Starting autonegotiation...\n", dev->parent.name);
    macb_mdio_write(macb, MII_BMCR, (BMCR_ANENABLE
                     | BMCR_ANRESTART));

    for (i = 0; i < MACB_AUTONEG_TIMEOUT / 100; i++)
    {
        status = macb_mdio_read(macb, MII_BMSR);
        if (status & BMSR_ANEGCOMPLETE)
            break;
        udelay(100);
    }

    if (status & BMSR_ANEGCOMPLETE)
        rt_kprintf("%s: Autonegotiation complete\n", dev->parent.name);
    else
        rt_kprintf("%s: Autonegotiation timed out (status=0x%04x)\n",
               dev->parent.name, status);
}


static int macb_phy_init(rt_device_t dev)
{
    struct rt_macb_eth *macb = dev->user_data;
    rt_uint32_t ncfgr;
    rt_uint16_t phy_id, status, adv, lpa;
    int media, speed, duplex;
    int i;

    /* Check if the PHY is up to snuff... */
    phy_id = macb_mdio_read(macb, MII_PHYSID1);
    if (phy_id == 0xffff)
    {
        rt_kprintf("%s: No PHY present\n", dev->parent.name);
        return 0;
    }

    status = macb_mdio_read(macb, MII_BMSR);
    if (!(status & BMSR_LSTATUS))
    {
        /* Try to re-negotiate if we don't have link already. */
        macb_phy_reset(dev);

        for (i = 0; i < MACB_LINK_TIMEOUT / 100; i++)
        {
            status = macb_mdio_read(macb, MII_BMSR);
            if (status & BMSR_LSTATUS)
                break;
            udelay(100);
        }
    }

    if (!(status & BMSR_LSTATUS))
    {
        rt_kprintf("%s: link down (status: 0x%04x)\n",
               dev->parent.name, status);
        return 0;
    }
    else
    {
        adv = macb_mdio_read(macb, MII_ADVERTISE);
        lpa = macb_mdio_read(macb, MII_LPA);
        media = mii_nway_result(lpa & adv);
        speed = (media & (ADVERTISE_100FULL | ADVERTISE_100HALF)
             ? 1 : 0);
        duplex = (media & ADVERTISE_FULL) ? 1 : 0;
        rt_kprintf("%s: link up, %sMbps %s-duplex (lpa: 0x%04x)\n",
               dev->parent.name,
               speed ? "100" : "10",
               duplex ? "full" : "half",
               lpa);

        ncfgr = macb_readl(macb, NCFGR);
        ncfgr &= ~(MACB_BIT(SPD) | MACB_BIT(FD));
        if (speed)
            ncfgr |= MACB_BIT(SPD);
        if (duplex)
            ncfgr |= MACB_BIT(FD);
        macb_writel(macb, NCFGR, ncfgr);
        return 1;
    }
}

void macb_update_link(void *param)
{
    struct rt_macb_eth *macb = (struct rt_macb_eth *)param;
    rt_device_t dev = &macb->parent.parent;
    int status, status_change = 0;
    rt_uint32_t link;
    rt_uint32_t media;
    rt_uint16_t adv, lpa;

    /* Do a fake read */
    status = macb_mdio_read(macb, MII_BMSR);
    if (status < 0)
        return;

    /* Read link and autonegotiation status */
    status = macb_mdio_read(macb, MII_BMSR);
    if (status < 0)
        return;

    if ((status & BMSR_LSTATUS) == 0)
        link = 0;
    else
        link = 1;

    if (link != macb->link)
    {
        macb->link = link;
        status_change = 1;
    }

    if (status_change)
    {
        if (macb->link)
        {
            adv = macb_mdio_read(macb, MII_ADVERTISE);
            lpa = macb_mdio_read(macb, MII_LPA);
            media = mii_nway_result(lpa & adv);
            macb->speed = (media & (ADVERTISE_100FULL | ADVERTISE_100HALF)
                 ? 100 : 10);
            macb->duplex = (media & ADVERTISE_FULL) ? 1 : 0;
            rt_kprintf("%s: link up (%dMbps/%s-duplex)\n",
                    dev->parent.name, macb->speed,
                    DUPLEX_FULL == macb->duplex ? "Full":"Half");
            eth_device_linkchange(&macb->parent, RT_TRUE);
        }
        else
        {
            rt_kprintf("%s: link down\n", dev->parent.name);
            eth_device_linkchange(&macb->parent, RT_FALSE);
        }

    }

}

/* RT-Thread Device Interface */
/* initialize the interface */

static rt_err_t rt_macb_init(rt_device_t dev)
{
    struct rt_macb_eth *macb = dev->user_data;
    unsigned long paddr;
    rt_uint32_t hwaddr_bottom;
    rt_uint16_t hwaddr_top;
    int i;

    /*
     * macb_halt should have been called at some point before now,
     * so we'll assume the controller is idle.
     */

    /* initialize DMA descriptors */
    paddr = macb->rx_buffer_dma;
    for (i = 0; i < MACB_RX_RING_SIZE; i++)
    {
        if (i == (MACB_RX_RING_SIZE - 1))
            paddr |= RXADDR_WRAP;
        macb->rx_ring[i].addr = paddr;
        macb->rx_ring[i].ctrl = 0;
        paddr += 128;
    }
    paddr = macb->tx_buffer_dma;
    for (i = 0; i < MACB_TX_RING_SIZE; i++)
    {
        macb->tx_ring[i].addr = paddr;
        if (i == (MACB_TX_RING_SIZE - 1))
            macb->tx_ring[i].ctrl = TXBUF_USED | TXBUF_WRAP;
        else
            macb->tx_ring[i].ctrl = TXBUF_USED;
        paddr += 1536;
    }
    macb->rx_tail = macb->tx_head = macb->tx_tail = 0;

    BD_CACHE_WRITEBACK_INVALIDATE(macb->rx_ring, MACB_RX_RING_SIZE * sizeof(struct macb_dma_desc));
    BD_CACHE_WRITEBACK_INVALIDATE(macb->tx_ring, MACB_TX_RING_SIZE * sizeof(struct macb_dma_desc));
    macb_writel(macb, RBQP, macb->rx_ring_dma);
    macb_writel(macb, TBQP, macb->tx_ring_dma);

    /* set hardware address */
    hwaddr_bottom = (*((rt_uint32_t *)macb->dev_addr));
    macb_writel(macb, SA1B, hwaddr_bottom);
    hwaddr_top = (*((rt_uint16_t *)(macb->dev_addr + 4)));
    macb_writel(macb, SA1T, hwaddr_top);


    /* choose RMII or MII mode. This depends on the board */
#ifdef CONFIG_RMII
    macb_writel(macb, USRIO, MACB_BIT(RMII) | MACB_BIT(CLKEN));
#else
    macb_writel(macb, USRIO, MACB_BIT(CLKEN));
#endif /* CONFIG_RMII */

    if (!macb_phy_init(dev))
        return -RT_ERROR;

    /* Enable TX and RX */
    macb_writel(macb, NCR, MACB_BIT(TE) | MACB_BIT(RE) | MACB_BIT(MPE));

    /* Enable interrupts */
    macb_writel(macb, IER, (MACB_BIT(RCOMP)
                  | MACB_BIT(RXUBR)
                  | MACB_BIT(ISR_TUND)
                  | MACB_BIT(ISR_RLE)
                  | MACB_BIT(TXERR)
                  | MACB_BIT(TCOMP)
                  | MACB_BIT(ISR_ROVR)
                  | MACB_BIT(HRESP)));

    /* instal interrupt */
    rt_hw_interrupt_install(AT91SAM9260_ID_EMAC, rt_macb_isr,
                            (void *)macb, "emac");
    rt_hw_interrupt_umask(AT91SAM9260_ID_EMAC);

    rt_timer_init(&macb->timer, "link_timer",
        macb_update_link,
        (void *)macb,
        RT_TICK_PER_SECOND,
        RT_TIMER_FLAG_PERIODIC);

    rt_timer_start(&macb->timer);

    return RT_EOK;
}

static rt_err_t rt_macb_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_macb_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t rt_macb_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t rt_macb_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_macb_control(rt_device_t dev, int cmd, void *args)
{
    switch(cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if(args) rt_memcpy(args, macb_device.dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

static void macb_tx(struct rt_macb_eth *macb)
{
    unsigned int tail;
    unsigned int head;
    rt_uint32_t status;

    status = macb_readl(macb, TSR);
    macb_writel(macb, TSR, status);

    /*rt_kprintf("macb_tx status = %02lx\n",
        (unsigned long)status);*/

    if (status & (MACB_BIT(UND) | MACB_BIT(TSR_RLE)))
    {
        int i;
        rt_kprintf("%s: TX %s, resetting buffers\n",
            macb->parent.parent.parent.name, status & MACB_BIT(UND) ?
            "underrun" : "retry limit exceeded");

        /* Transfer ongoing, disable transmitter, to avoid confusion */
        if (status & MACB_BIT(TGO))
            macb_writel(macb, NCR, macb_readl(macb, NCR) & ~MACB_BIT(TE));

        head = macb->tx_head;

        /*Mark all the buffer as used to avoid sending a lost buffer*/
        for (i = 0; i < MACB_TX_RING_SIZE; i++)
            macb->tx_ring[i].ctrl = MACB_BIT(TX_USED);

        /* free transmit buffer in upper layer*/

        macb->tx_head = macb->tx_tail = 0;

        /* Enable the transmitter again */
        if (status & MACB_BIT(TGO))
            macb_writel(macb, NCR, macb_readl(macb, NCR) | MACB_BIT(TE));
    }

    if (!(status & MACB_BIT(COMP)))
        /*
         * This may happen when a buffer becomes complete
         * between reading the ISR and scanning the
         * descriptors.  Nothing to worry about.
         */
        return;

    head = macb->tx_head;
    for (tail = macb->tx_tail; tail != head; tail = NEXT_TX(tail))
    {
        rt_uint32_t bufstat;

        bufstat = macb->tx_ring[tail].ctrl;

        if (!(bufstat & MACB_BIT(TX_USED)))
            break;
    }

    macb->tx_tail = tail;
    if ((macb->tx_stop == 1) &&
        TX_BUFFS_AVAIL(macb) > MACB_TX_WAKEUP_THRESH)
        rt_sem_release(&macb->tx_ack);
}


/* ethernet device interface */
/* transmit packet. */
rt_err_t rt_macb_tx( rt_device_t dev, struct pbuf* p)
{
    unsigned long ctrl;
    struct pbuf* q;
    rt_uint8_t* bufptr;
    rt_uint32_t mapping;
    struct rt_macb_eth *macb = dev->user_data;
    unsigned int tx_head = macb->tx_head;

    rt_sem_take(&macb->tx_lock, RT_WAITING_FOREVER);
    if (TX_BUFFS_AVAIL(macb) < 1)
    {
        rt_sem_release(&macb->tx_lock);
        rt_kprintf("Tx Ring full!\n");
        rt_kprintf("tx_head = %u, tx_tail = %u\n",
            macb->tx_head, macb->tx_tail);
        return -RT_ERROR;
    }

    macb->tx_stop = 0;

    ctrl = p->tot_len & TXBUF_FRMLEN_MASK;
    ctrl |= TXBUF_FRAME_END;
    if (tx_head == (MACB_TX_RING_SIZE - 1))
    {
        ctrl |= TXBUF_WRAP;
    }
#if defined(MACB_TX_SRAM)
    bufptr = macb->tx_buffer + tx_head * 1536;
#else
    mapping = (unsigned long)macb->tx_buffer + tx_head * 1536;
    bufptr = (rt_uint8_t *)mapping;
#endif

    for (q = p; q != NULL; q = q->next)
    {
        memcpy(bufptr, q->payload, q->len);
        bufptr += q->len;
    }
#if !defined(MACB_TX_SRAM)
    EMAC_CACHE_WRITEBACK(mapping, p->tot_len);
#endif
    macb->tx_ring[tx_head].ctrl = ctrl;
    BD_CACHE_WRITEBACK_INVALIDATE(&macb->tx_ring[tx_head], sizeof(struct macb_dma_desc));
    tx_head = NEXT_TX(tx_head);
    macb->tx_head = tx_head;
    macb_writel(macb, NCR, macb_readl(macb, NCR) | MACB_BIT(TSTART));
    macb_writel(macb, NCR, macb_readl(macb, NCR) | MACB_BIT(TSTART));

    if (TX_BUFFS_AVAIL(macb) < 1)
    {
        macb->tx_stop = 1;
        rt_sem_take(&macb->tx_ack, RT_WAITING_FOREVER);
    }
    rt_sem_release(&macb->tx_lock);

    return RT_EOK;
}

static void reclaim_rx_buffers(struct rt_macb_eth *macb,
                   unsigned int new_tail)
{
    unsigned int i;

    i = macb->rx_tail;
    while (i > new_tail)
    {
        macb->rx_ring[i].addr &= ~RXADDR_USED;
        i++;
        if (i > MACB_RX_RING_SIZE)
            i = 0;
    }

    while (i < new_tail)
    {
        macb->rx_ring[i].addr &= ~RXADDR_USED;
        i++;
    }

    macb->rx_tail = new_tail;
}

/* reception packet. */
struct pbuf *rt_macb_rx(rt_device_t dev)
{
    struct rt_macb_eth *macb = dev->user_data;
    struct pbuf* p = RT_NULL;
    rt_uint32_t len;
    unsigned int rx_tail = macb->rx_tail;
    void *buffer;
    int wrapped = 0;
    rt_uint32_t status;

    rt_sem_take(&macb->rx_lock, RT_WAITING_FOREVER);
    for (;;)
    {
        if (!(macb->rx_ring[rx_tail].addr & RXADDR_USED))
            break;

        status = macb->rx_ring[rx_tail].ctrl;
        if (status & RXBUF_FRAME_START)
        {
            if (rx_tail != macb->rx_tail)
                reclaim_rx_buffers(macb, rx_tail);
            wrapped = 0;
        }

        if (status & RXBUF_FRAME_END)
        {
            buffer = (void *)((unsigned int)macb->rx_buffer + 128 * macb->rx_tail);
            len = status & RXBUF_FRMLEN_MASK;
            p = pbuf_alloc(PBUF_LINK, len, PBUF_RAM);
            if (!p)
            {
                rt_kprintf("alloc pbuf failed\n");
                break;
            }
            if (wrapped)
            {
                unsigned int headlen, taillen;

                headlen = 128 * (MACB_RX_RING_SIZE
                         - macb->rx_tail);
                taillen = len - headlen;
                EMAC_CACHE_INVALIDATE(buffer, headlen);
                EMAC_CACHE_INVALIDATE(macb->rx_buffer, taillen);
                memcpy((void *)p->payload, buffer, headlen);
                memcpy((void *)((unsigned int)p->payload + headlen),
                       macb->rx_buffer, taillen);
            }
            else
            {
                EMAC_CACHE_INVALIDATE(buffer, len);
                memcpy((void *)p->payload, buffer, p->len);
            }

            if (++rx_tail >= MACB_RX_RING_SIZE)
                rx_tail = 0;
            reclaim_rx_buffers(macb, rx_tail);
            break;
        }
        else
        {
            if (++rx_tail >= MACB_RX_RING_SIZE)
            {
                wrapped = 1;
                rx_tail = 0;
            }
        }
    }

    rt_sem_release(&macb->rx_lock);

    return p;
}

void macb_gpio_init()
{
    /* Pins used for MII and RMII */
    at91_sys_write(AT91_PIOA + PIO_PDR, (1 << 19)|(1 << 17)|(1 << 14)|(1 << 15)|(1 << 18)|(1 << 16)|(1 << 12)|(1 << 13)|(1 << 21)|(1 << 20));
    at91_sys_write(AT91_PIOA + PIO_ASR, (1 << 19)|(1 << 17)|(1 << 14)|(1 << 15)|(1 << 18)|(1 << 16)|(1 << 12)|(1 << 13)|(1 << 21)|(1 << 20));

#ifndef GONFIG_RMII
    at91_sys_write(AT91_PIOA + PIO_PDR, (1 << 22)|(1 << 23)|(1 << 24)|(1 << 25)|(1 << 26)|(1 << 27)|(1 << 28)|(1 << 29));
    at91_sys_write(AT91_PIOA + PIO_ASR, (1 << 22)|(1 << 23)|(1 << 24)|(1 << 25)|(1 << 26)|(1 << 27)|(1 << 28)|(1 << 29));
#endif
}

rt_err_t macb_initialize()
{
    struct rt_macb_eth *macb = &macb_device;
    unsigned long macb_hz;
    rt_uint32_t ncfgr;

#if defined(MACB_TX_SRAM)
    macb->tx_ring_dma = AT91SAM9260_SRAM0_BASE;
    macb->tx_ring = (struct macb_dma_desc *)AT91SAM9260_SRAM0_VIRT_BASE;
    macb->tx_buffer = (char *) macb->tx_ring + TX_RING_BYTES;
    macb->tx_buffer_dma = macb->tx_ring_dma + TX_RING_BYTES;
#else
    macb->tx_ring = rt_malloc(MACB_RX_RING_SIZE * sizeof(struct macb_dma_desc));
    if (macb->tx_ring == RT_NULL)
        goto err1;
    EMAC_CACHE_INVALIDATE(macb->tx_ring, MACB_TX_RING_SIZE * sizeof(struct macb_dma_desc));
    macb->tx_ring_dma = emac_virt_to_phys((unsigned long)macb->tx_ring);
    macb->tx_ring = (struct macb_dma_desc *)MMU_NOCACHE_ADDR((unsigned long)macb->tx_ring);
    macb->tx_buffer = rt_malloc(MACB_TX_BUFFER_SIZE);
    if (macb->tx_buffer == RT_NULL)
        goto err2;
    macb->tx_buffer_dma = emac_virt_to_phys((unsigned long)macb->tx_buffer);
#endif

    macb->rx_ring = rt_malloc(MACB_RX_RING_SIZE * sizeof(struct macb_dma_desc));
    if (macb->rx_ring == RT_NULL)
        goto err3;
    EMAC_CACHE_INVALIDATE(macb->rx_ring, MACB_RX_RING_SIZE * sizeof(struct macb_dma_desc));
    macb->rx_ring_dma = emac_virt_to_phys((unsigned long)macb->rx_ring);
    macb->rx_ring = (struct macb_dma_desc *)MMU_NOCACHE_ADDR((unsigned long)macb->rx_ring);
    macb->rx_buffer = rt_malloc(MACB_RX_BUFFER_SIZE);
    if (macb->rx_buffer == RT_NULL)
        goto err4;
    macb->rx_buffer_dma = emac_virt_to_phys((unsigned long)macb->rx_buffer);

    macb->tx_pending = DEF_TX_RING_PENDING;

    macb->regs = AT91SAM9260_BASE_EMAC;
    macb->phy_addr = 0x00;

    /*
     * Do some basic initialization so that we at least can talk
     * to the PHY
     */
    macb_hz = clk_get_rate(clk_get("mck"));
    if (macb_hz < 20000000)
        ncfgr = MACB_BF(CLK, MACB_CLK_DIV8);
    else if (macb_hz < 40000000)
        ncfgr = MACB_BF(CLK, MACB_CLK_DIV16);
    else if (macb_hz < 80000000)
        ncfgr = MACB_BF(CLK, MACB_CLK_DIV32);
    else
        ncfgr = MACB_BF(CLK, MACB_CLK_DIV64);

    macb_writel(macb, NCFGR, ncfgr);

    macb->link = 0;

    return RT_EOK;

err4:
    rt_free(macb->rx_ring);
    macb->rx_ring = RT_NULL;
err3:
#if !defined(MACB_TX_SRAM)
    rt_free(macb->tx_buffer);
    macb->tx_buffer = RT_NULL;
err2:
    rt_free(macb->tx_ring);
    macb->tx_ring = RT_NULL;
err1:
#endif
    return -RT_ENOMEM;
}

int rt_hw_macb_init(void)
{
    rt_err_t ret;
    at91_sys_write(AT91_PMC + AT91_PMC_PCER, 1 << AT91SAM9260_ID_EMAC); //enable macb clock
    macb_gpio_init();
    rt_memset(&macb_device, 0, sizeof(macb_device));
    ret = macb_initialize();
    if (ret != RT_EOK)
    {
        rt_kprintf("AT91 EMAC initialized failed\n");
        return -1;
    }
    rt_sem_init(&macb_device.tx_ack, "tx_ack", 0, RT_IPC_FLAG_FIFO);
    rt_sem_init(&macb_device.tx_lock, "tx_lock", 1, RT_IPC_FLAG_FIFO);
    rt_sem_init(&macb_device.rx_lock, "rx_lock", 1, RT_IPC_FLAG_FIFO);

    macb_device.dev_addr[0] = 0x00;
    macb_device.dev_addr[1] = 0x60;
    macb_device.dev_addr[2] = 0x6E;
    macb_device.dev_addr[3] = 0x11;
    macb_device.dev_addr[4] = 0x22;
    macb_device.dev_addr[5] = 0x33;

    macb_device.parent.parent.init       = rt_macb_init;
    macb_device.parent.parent.open       = rt_macb_open;
    macb_device.parent.parent.close      = rt_macb_close;
    macb_device.parent.parent.read       = rt_macb_read;
    macb_device.parent.parent.write      = rt_macb_write;
    macb_device.parent.parent.control    = rt_macb_control;
    macb_device.parent.parent.user_data  = &macb_device;

    macb_device.parent.eth_rx     = rt_macb_rx;
    macb_device.parent.eth_tx     = rt_macb_tx;

    rt_sem_init(&macb_device.mdio_bus_lock, "mdio_bus_lock", 1, RT_IPC_FLAG_FIFO);

    eth_device_init(&(macb_device.parent), "e0");

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_macb_init);

