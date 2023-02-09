/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-01-13     weety     first version
 */


#include <rtthread.h>
#include <netif/ethernetif.h>
#include <lwipopts.h>
#include <dm36x.h>
#include "davinci_emac.h"

#define MMU_NOCACHE_ADDR(a)         ((rt_uint32_t)a | (1UL<<29))
#define CACHE_LINE_SIZE 32

extern void mmu_clean_dcache(rt_uint32_t buffer, rt_uint32_t size);
extern void mmu_invalidate_dcache(rt_uint32_t buffer, rt_uint32_t size);

/* EMAC internal utility function */
static inline rt_uint32_t emac_virt_to_phys(void *addr)
{
    return (rt_uint32_t)addr;
}

static inline rt_uint32_t virt_to_phys(void *addr)
{
    return (rt_uint32_t)addr;
}

/* Cache macros - Packet buffers would be from pbuf pool which is cached */
#define EMAC_VIRT_NOCACHE(addr) (addr)
#define EMAC_CACHE_INVALIDATE(addr, size) \
    mmu_invalidate_dcache(addr, size)
#define EMAC_CACHE_WRITEBACK(addr, size) \
    mmu_clean_dcache(addr, size)
#define EMAC_CACHE_WRITEBACK_INVALIDATE(addr, size) \
    mmu_clean_invalidated_dcache(addr, size)

/* DM644x does not have BD's in cached memory - so no cache functions */
#define BD_CACHE_INVALIDATE(addr, size)
#define BD_CACHE_WRITEBACK(addr, size)
#define BD_CACHE_WRITEBACK_INVALIDATE(addr, size)


static struct emac_priv davinci_emac_device;

/* clock frequency for EMAC */
static unsigned long emac_bus_frequency;
static unsigned long mdio_max_freq;

#define EMAC_AUTONEG_TIMEOUT    5000000
#define EMAC_LINK_TIMEOUT           500000


/* EMAC TX Host Error description strings */
static char *emac_txhost_errcodes[16] = {
    "No error", "SOP error", "Ownership bit not set in SOP buffer",
    "Zero Next Buffer Descriptor Pointer Without EOP",
    "Zero Buffer Pointer", "Zero Buffer Length", "Packet Length Error",
    "Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved"
};

/* EMAC RX Host Error description strings */
static char *emac_rxhost_errcodes[16] = {
    "No error", "Reserved", "Ownership bit not set in input buffer",
    "Reserved", "Zero Buffer Pointer", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved"
};

#define emac_read(reg)        davinci_readl(priv->emac_base + (reg))
#define emac_write(reg, val)      davinci_writel(val, priv->emac_base + (reg))

#define emac_ctrl_read(reg)   davinci_readl((priv->ctrl_base + (reg)))
#define emac_ctrl_write(reg, val) davinci_writel(val, (priv->ctrl_base + (reg)))

#define emac_mdio_read(reg)   davinci_readl(priv->mdio_base + (reg))
#define emac_mdio_write(reg, val) davinci_writel(val, (priv->mdio_base + (reg)))

static void emac_int_enable(struct emac_priv *priv);
static void emac_int_disable(struct emac_priv *priv);
static int emac_init_txch(struct emac_priv *priv, rt_uint32_t ch);

/* PHY/MII bus related */

/* Wait until mdio is ready for next command */
#define MDIO_WAIT_FOR_USER_ACCESS\
        while ((emac_mdio_read((MDIO_USERACCESS(0))) &\
            MDIO_USERACCESS_GO) != 0)

static int emac_mii_read(struct emac_priv *priv, int phy_id, int phy_reg)
{
    unsigned int phy_data = 0;
    unsigned int phy_control;

    /* Wait until mdio is ready for next command */
    MDIO_WAIT_FOR_USER_ACCESS;

    phy_control = (MDIO_USERACCESS_GO |
               MDIO_USERACCESS_READ |
               ((phy_reg << 21) & MDIO_USERACCESS_REGADR) |
               ((phy_id << 16) & MDIO_USERACCESS_PHYADR) |
               (phy_data & MDIO_USERACCESS_DATA));
    emac_mdio_write(MDIO_USERACCESS(0), phy_control);

    /* Wait until mdio is ready for next command */
    MDIO_WAIT_FOR_USER_ACCESS;

    return emac_mdio_read(MDIO_USERACCESS(0)) & MDIO_USERACCESS_DATA;

}

static int emac_mii_write(struct emac_priv *priv, int phy_id,
              int phy_reg, rt_uint16_t phy_data)
{

    unsigned int control;

    /*  until mdio is ready for next command */
    MDIO_WAIT_FOR_USER_ACCESS;

    control = (MDIO_USERACCESS_GO |
           MDIO_USERACCESS_WRITE |
           ((phy_reg << 21) & MDIO_USERACCESS_REGADR) |
           ((phy_id << 16) & MDIO_USERACCESS_PHYADR) |
           (phy_data & MDIO_USERACCESS_DATA));
    emac_mdio_write(MDIO_USERACCESS(0), control);

    return 0;
}

static int emac_mii_reset(struct emac_priv *priv)
{
    unsigned int clk_div;
    int mdio_bus_freq = emac_bus_frequency;

    if (mdio_max_freq && mdio_bus_freq)
        clk_div = ((mdio_bus_freq / mdio_max_freq) - 1);
    else
        clk_div = 0xFF;

    clk_div &= MDIO_CONTROL_CLKDIV;

    /* Set enable and clock divider in MDIOControl */
    emac_mdio_write(MDIO_CONTROL, (clk_div | MDIO_CONTROL_ENABLE));

    return 0;

}



/* Duplex, half or full. */
#define DUPLEX_HALF     0x00
#define DUPLEX_FULL     0x01

static void udelay(rt_uint32_t us)
{
    rt_uint32_t len;
    for (;us > 0; us --)
        for (len = 0; len < 10; len++ );
}

static void davinci_emac_phy_reset(rt_device_t dev)
{
    int i;
    rt_uint16_t status, adv;
    struct emac_priv *priv = dev->user_data;;

    adv = ADVERTISE_CSMA | ADVERTISE_ALL;
    emac_mii_write(priv, priv->phy_addr, MII_ADVERTISE, adv);
    rt_kprintf("%s: Starting autonegotiation...\n", dev->parent.name);
    emac_mii_write(priv, priv->phy_addr, MII_BMCR, (BMCR_ANENABLE
                     | BMCR_ANRESTART));

    for (i = 0; i < EMAC_AUTONEG_TIMEOUT / 100; i++) {
        status = emac_mii_read(priv, priv->phy_addr, MII_BMSR);
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


static int davinci_emac_phy_init(rt_device_t dev)
{
    struct emac_priv *priv = dev->user_data;
    rt_uint16_t phy_id, status, adv, lpa;
    int media, speed, duplex;
    int i;

    /* Check if the PHY is up to snuff... */
    phy_id = emac_mii_read(priv, priv->phy_addr, MII_PHYSID1);
    if (phy_id == 0xffff) {
        rt_kprintf("%s: No PHY present\n", dev->parent.name);
        return 0;
    }

    status = emac_mii_read(priv, priv->phy_addr, MII_BMSR);
    if (!(status & BMSR_LSTATUS)) {
        /* Try to re-negotiate if we don't have link already. */
        davinci_emac_phy_reset(dev);

        for (i = 0; i < EMAC_LINK_TIMEOUT / 100; i++) {
            status = emac_mii_read(priv, priv->phy_addr, MII_BMSR);
            if (status & BMSR_LSTATUS)
                break;
            udelay(100);
        }
    }

    if (!(status & BMSR_LSTATUS)) {
        rt_kprintf("%s: link down (status: 0x%04x)\n",
               dev->parent.name, status);
        priv->link = 0;
        eth_device_linkchange(&priv->parent, RT_FALSE);
        return 0;
    } else {
        adv = emac_mii_read(priv, priv->phy_addr, MII_ADVERTISE);
        lpa = emac_mii_read(priv, priv->phy_addr, MII_LPA);
        media = mii_nway_result(lpa & adv);
        speed = (media & (ADVERTISE_100FULL | ADVERTISE_100HALF)
             ? 1 : 0);
        duplex = (media & ADVERTISE_FULL) ? 1 : 0;
        rt_kprintf("%s: link up, %sMbps %s-duplex (lpa: 0x%04x)\n",
               dev->parent.name,
               speed ? "100" : "10",
               duplex ? "full" : "half",
               lpa);
        priv->speed = speed;
        priv->duplex = duplex;
        priv->link = 1;
        eth_device_linkchange(&priv->parent, RT_TRUE);

        return 1;
    }
}

/**
 * emac_update_phystatus: Update Phy status
 * @priv: The DaVinci EMAC driver private structure
 *
 * Updates phy status and takes action for network queue if required
 * based upon link status
 *
 */
static void emac_update_phystatus(struct emac_priv *priv)
{
    rt_uint32_t mac_control;
    rt_uint32_t new_duplex;
    rt_uint32_t cur_duplex;

    mac_control = emac_read(EMAC_MACCONTROL);
    cur_duplex = (mac_control & EMAC_MACCONTROL_FULLDUPLEXEN) ?
            DUPLEX_FULL : DUPLEX_HALF;
    if (priv->phy_mask)
        new_duplex = priv->duplex;
    else
        new_duplex = DUPLEX_FULL;

    /* We get called only if link has changed (speed/duplex/status) */
    if ((priv->link) && (new_duplex != cur_duplex)) {
        priv->duplex = new_duplex;
        if (DUPLEX_FULL == priv->duplex)
            mac_control |= (EMAC_MACCONTROL_FULLDUPLEXEN);
        else
            mac_control &= ~(EMAC_MACCONTROL_FULLDUPLEXEN);
    }

    if (priv->speed == SPEED_1000 && (priv->version == EMAC_VERSION_2)) {
        mac_control = emac_read(EMAC_MACCONTROL);
        mac_control |= (EMAC_DM646X_MACCONTORL_GIG |
                EMAC_DM646X_MACCONTORL_GIGFORCE);
    } else {
        /* Clear the GIG bit and GIGFORCE bit */
        mac_control &= ~(EMAC_DM646X_MACCONTORL_GIGFORCE |
                    EMAC_DM646X_MACCONTORL_GIG);

        if (priv->rmii_en && (priv->speed == SPEED_100))
            mac_control |= EMAC_MACCONTROL_RMIISPEED_MASK;
        else
            mac_control &= ~EMAC_MACCONTROL_RMIISPEED_MASK;
    }

    /* Update mac_control if changed */
    emac_write(EMAC_MACCONTROL, mac_control);
#if 0
    if (priv->link) {
        /* link ON */
    /* reactivate the transmit queue if it is stopped */
    } else {
        /* link OFF */
    }
#endif
}


void davinci_emac_update_link(void *param)
{
    struct emac_priv *priv = param;
    rt_device_t dev = &(priv->parent.parent);
    rt_uint32_t status, status_change = 0;
    rt_uint32_t link;
    rt_uint32_t media;
    rt_uint16_t adv, lpa;

    status = emac_mii_read(priv, priv->phy_addr, MII_BMSR);
    if ((status & BMSR_LSTATUS) == 0)
        link = 0;
    else
        link = 1;

    if (link != priv->link) {
        priv->link = link;
        status_change = 1;
    }

    if (status_change) {
        if (priv->link) {
            adv = emac_mii_read(priv, priv->phy_addr, MII_ADVERTISE);
            lpa = emac_mii_read(priv, priv->phy_addr, MII_LPA);
            media = mii_nway_result(lpa & adv);
            priv->speed = (media & (ADVERTISE_100FULL | ADVERTISE_100HALF)
                 ? 100 : 10);
            priv->duplex = (media & ADVERTISE_FULL) ? 1 : 0;
            rt_kprintf("%s: link up (%dMbps/%s-duplex)\n",
                    dev->parent.name, priv->speed,
                    DUPLEX_FULL == priv->duplex ? "Full":"Half");
            eth_device_linkchange(&priv->parent, RT_TRUE);
        } else {
            rt_kprintf("%s: link down\n", dev->parent.name);
            eth_device_linkchange(&priv->parent, RT_FALSE);
        }
        emac_update_phystatus(priv);

    }

}


/**
 * emac_net_tx_complete: TX packet completion function
 * @priv: The DaVinci EMAC driver private structure
 * @net_data_tokens: packet token - pbuf pointer
 * @num_tokens: number of pbuf's to free
 * @ch: TX channel number
 *
 * Frees the pbuf once packet is transmitted
 *
 */
static int emac_net_tx_complete(struct emac_priv *priv,
                void **net_data_tokens,
                int num_tokens, rt_uint32_t ch)
{
    rt_uint32_t cnt;

    for (cnt = 0; cnt < num_tokens; cnt++) {
        struct pbuf *p = (struct pbuf *)net_data_tokens[cnt];
        if (p == RT_NULL)
            continue;
        priv->net_dev_stats.tx_packets++;
        priv->net_dev_stats.tx_bytes += p->len;
        //free pbuf
    }

    return 0;
}

/**
 * emac_txch_teardown: TX channel teardown
 * @priv: The DaVinci EMAC driver private structure
 * @ch: TX channel number
 *
 * Called to teardown TX channel
 *
 */
static void emac_txch_teardown(struct emac_priv *priv, rt_uint32_t ch)
{
    rt_uint32_t teardown_cnt = 0xFFFFFFF0; /* Some high value */
    struct emac_txch *txch = priv->txch[ch];
    struct emac_tx_bd __iomem *curr_bd;

    while ((emac_read(EMAC_TXCP(ch)) & EMAC_TEARDOWN_VALUE) !=
           EMAC_TEARDOWN_VALUE) {
        /* wait till tx teardown complete */
        --teardown_cnt;
        if (0 == teardown_cnt) {
            rt_kprintf("EMAC: TX teardown aborted\n");
            break;
        }
    }
    emac_write(EMAC_TXCP(ch), EMAC_TEARDOWN_VALUE);

    /* process sent packets and return pbuf's to upper layer */
    if (1 == txch->queue_active) {
        curr_bd = txch->active_queue_head;
        while (curr_bd != RT_NULL) {
            emac_net_tx_complete(priv, (void *)
                    &curr_bd->buf_token, 1, ch);
            if (curr_bd != txch->active_queue_tail)
                curr_bd = curr_bd->next;
            else
                break;
        }
        txch->bd_pool_head = txch->active_queue_head;
        txch->active_queue_head =
        txch->active_queue_tail = RT_NULL;
    }
}


/**
 * emac_stop_txch: Stop TX channel operation
 * @priv: The DaVinci EMAC driver private structure
 * @ch: TX channel number
 *
 * Called to stop TX channel operation
 *
 */
static void emac_stop_txch(struct emac_priv *priv, rt_uint32_t ch)
{
    struct emac_txch *txch = priv->txch[ch];

    if (txch) {
        txch->teardown_pending = 1;
        emac_write(EMAC_TXTEARDOWN, 0);
        emac_txch_teardown(priv, ch);
        txch->teardown_pending = 0;
        emac_write(EMAC_TXINTMASKCLEAR, BIT(ch));
    }
}



/**
 * emac_tx_bdproc: TX buffer descriptor (packet) processing
 * @priv: The DaVinci EMAC driver private structure
 * @ch: TX channel number to process buffer descriptors for
 * @budget: number of packets allowed to process
 * @pending: indication to caller that packets are pending to process
 *
 * Processes TX buffer descriptors after packets are transmitted - checks
 * ownership bit on the TX * descriptor and requeues it to free pool & frees
 * the PBUF buffer. Only "budget" number of packets are processed and
 * indication of pending packets provided to the caller
 *
 * Returns number of packets processed
 */
static int emac_tx_bdproc(struct emac_priv *priv, rt_uint32_t ch, rt_uint32_t budget)
{
    unsigned long flags;
    rt_uint32_t frame_status;
    rt_uint32_t pkts_processed = 0;
    rt_uint32_t tx_complete_cnt = 0;
    struct emac_tx_bd __iomem *curr_bd;
    struct emac_txch *txch = priv->txch[ch];
    rt_uint32_t *tx_complete_ptr = txch->tx_complete;

    if (1 == txch->teardown_pending) {
        rt_kprintf("DaVinci EMAC:emac_tx_bdproc: "\
                "teardown pending\n");
        return 0;  /* dont handle any pkt completions */
    }

    ++txch->proc_count;
    rt_sem_take(&priv->tx_lock, RT_WAITING_FOREVER);
    curr_bd = txch->active_queue_head;
    if (RT_NULL == curr_bd) {
        emac_write(EMAC_TXCP(ch),
               emac_virt_to_phys(txch->last_hw_bdprocessed));
        txch->no_active_pkts++;
        rt_sem_release(&priv->tx_lock);
        return 0;
    }
    BD_CACHE_INVALIDATE(curr_bd, EMAC_BD_LENGTH_FOR_CACHE);
    frame_status = curr_bd->mode;
    while ((curr_bd) &&
          ((frame_status & EMAC_CPPI_OWNERSHIP_BIT) == 0) &&
          (pkts_processed < budget)) {
        emac_write(EMAC_TXCP(ch), emac_virt_to_phys(curr_bd));
        txch->active_queue_head = curr_bd->next;
        if (frame_status & EMAC_CPPI_EOQ_BIT) {
            if (curr_bd->next) {    /* misqueued packet */
                emac_write(EMAC_TXHDP(ch), curr_bd->h_next);
                ++txch->mis_queued_packets;
            } else {
                txch->queue_active = 0; /* end of queue */
            }
        }
        *tx_complete_ptr = (rt_uint32_t) curr_bd->buf_token;
        ++tx_complete_ptr;
        ++tx_complete_cnt;
        curr_bd->next = txch->bd_pool_head;
        txch->bd_pool_head = curr_bd;
        --txch->active_queue_count;
        pkts_processed++;
        txch->last_hw_bdprocessed = curr_bd;
        curr_bd = txch->active_queue_head;
        if (curr_bd) {
            BD_CACHE_INVALIDATE(curr_bd, EMAC_BD_LENGTH_FOR_CACHE);
            frame_status = curr_bd->mode;
        }
    } /* end of pkt processing loop */

    emac_net_tx_complete(priv,
                 (void *)&txch->tx_complete[0],
                 tx_complete_cnt, ch);
    rt_sem_release(&priv->tx_lock);
    return pkts_processed;
}


#define EMAC_ERR_TX_OUT_OF_BD -1

/**
 * emac_send: EMAC Transmit function (internal)
 * @priv: The DaVinci EMAC driver private structure
 * @pkt: packet pointer (contains pbuf ptr)
 * @ch: TX channel number
 *
 * Called by the transmit function to queue the packet in EMAC hardware queue
 *
 * Returns success(0) or error code (typically out of desc's)
 */
static int emac_send(struct emac_priv *priv, struct emac_netpktobj *pkt, rt_uint32_t ch)
{
    unsigned long flags;
    struct emac_tx_bd __iomem *curr_bd;
    struct emac_txch *txch;
    struct emac_netbufobj *buf_list;
    rt_uint32_t num_pkts = 0;
    int retry = 0;

    txch = priv->txch[ch];
    buf_list = pkt->buf_list;   /* get handle to the buffer array */

    /* check packet size and pad if short */
    if (pkt->pkt_length < EMAC_DEF_MIN_ETHPKTSIZE) {
        buf_list->length += (EMAC_DEF_MIN_ETHPKTSIZE - pkt->pkt_length);
        pkt->pkt_length = EMAC_DEF_MIN_ETHPKTSIZE;
    }

try:
    rt_sem_take(&priv->tx_lock, RT_WAITING_FOREVER);
    curr_bd = txch->bd_pool_head;
    if (curr_bd == RT_NULL) {
        txch->out_of_tx_bd++;
        rt_sem_release(&priv->tx_lock);
        num_pkts = emac_tx_bdproc(priv, EMAC_DEF_TX_CH,
                      EMAC_DEF_TX_MAX_SERVICE);
        if (!num_pkts) {
            retry++;
            if (retry > 5)
                return EMAC_ERR_TX_OUT_OF_BD;
            rt_thread_delay(1);
        }
        goto try;
    }

    txch->bd_pool_head = curr_bd->next;
    curr_bd->buf_token = buf_list->buf_token;
    curr_bd->buff_ptr = virt_to_phys(buf_list->data_ptr);
    curr_bd->off_b_len = buf_list->length;
    curr_bd->h_next = 0;
    curr_bd->next = RT_NULL;
    curr_bd->mode = (EMAC_CPPI_SOP_BIT | EMAC_CPPI_OWNERSHIP_BIT |
             EMAC_CPPI_EOP_BIT | pkt->pkt_length);

    /* flush the packet from cache if write back cache is present */
    BD_CACHE_WRITEBACK_INVALIDATE(curr_bd, EMAC_BD_LENGTH_FOR_CACHE);

    /* send the packet */
    if (txch->active_queue_head == RT_NULL) {
        txch->active_queue_head = curr_bd;
        txch->active_queue_tail = curr_bd;
        if (1 != txch->queue_active) {
            emac_write(EMAC_TXHDP(ch),
                    emac_virt_to_phys(curr_bd));
            txch->queue_active = 1;
        }
        ++txch->queue_reinit;
    } else {
        register struct emac_tx_bd __iomem *tail_bd;
        register rt_uint32_t frame_status;

        tail_bd = txch->active_queue_tail;
        tail_bd->next = curr_bd;
        txch->active_queue_tail = curr_bd;
        tail_bd = EMAC_VIRT_NOCACHE(tail_bd);
        tail_bd->h_next = (int)emac_virt_to_phys(curr_bd);
        frame_status = tail_bd->mode;
        if (frame_status & EMAC_CPPI_EOQ_BIT) {
            emac_write(EMAC_TXHDP(ch), emac_virt_to_phys(curr_bd));
            frame_status &= ~(EMAC_CPPI_EOQ_BIT);
            tail_bd->mode = frame_status;
            ++txch->end_of_queue_add;
        }
    }
    txch->active_queue_count++;
    rt_sem_release(&priv->tx_lock);
    return 0;
}

/**
 * emac_dev_xmit: EMAC Transmit function
 * @pbuf: PBUF pointer
 * @priv: The DaVinci EMAC driver private structure
 *
 * Called by the system to transmit a packet  - we queue the packet in
 * EMAC hardware transmit queue
 *
 * Returns success(RT_EOK) or error code (typically out of desc's)
 */
static int emac_dev_xmit(struct pbuf *p, struct emac_priv *priv)
{
    int ret_code;
    struct emac_netbufobj tx_buf; /* buffer obj-only single frame support */
    struct emac_netpktobj tx_packet;  /* packet object */

    /* If no link, return */
    if (!priv->link) {
            rt_kprintf("DaVinci EMAC: No link to transmit\n");
        return -RT_EBUSY;
    }

    /* Build the buffer and packet objects - Since only single fragment is
     * supported, need not set length and token in both packet & object.
     * Doing so for completeness sake & to show that this needs to be done
     * in multifragment case
     */
    tx_packet.buf_list = &tx_buf;
    tx_packet.num_bufs = 1; /* only single fragment supported */
    tx_packet.pkt_length = p->len;
    tx_packet.pkt_token = (void *)p;
    tx_buf.length = p->len;
    tx_buf.buf_token = (void *)p;
    tx_buf.data_ptr = p->payload;
    EMAC_CACHE_WRITEBACK((unsigned long)p->payload, p->len);
    ret_code = emac_send(priv, &tx_packet, EMAC_DEF_TX_CH);
    if (ret_code != 0) {
        if (ret_code == EMAC_ERR_TX_OUT_OF_BD) {
            rt_kprintf("DaVinci EMAC: xmit() fatal"\
                    " err. Out of TX BD's\n");
        }
        priv->net_dev_stats.tx_dropped++;
        return -RT_EBUSY;
    }

    return RT_EOK;
}

/**
 * emac_cleanup_txch: Book-keep function to clean TX channel resources
 * @priv: The DaVinci EMAC private adapter structure
 * @ch: TX channel number
 *
 * Called to clean up TX channel resources
 *
 */
static void emac_cleanup_txch(struct emac_priv *priv, rt_uint32_t ch)
{
    struct emac_txch *txch = priv->txch[ch];

    if (txch) {
        if (txch->bd_mem)
            txch->bd_mem = NULL;
        rt_free(txch->tx_complete);
        rt_free(txch);
        priv->txch[ch] = NULL;
    }
}


/**
 * emac_dev_tx_timeout: EMAC Transmit timeout function
 * @ndev: The DaVinci EMAC network adapter
 *
 * Called when system detects that a skb timeout period has expired
 * potentially due to a fault in the adapter in not being able to send
 * it out on the wire. We teardown the TX channel assuming a hardware
 * error and re-initialize the TX channel for hardware operation
 *
 */
static void emac_dev_tx_timeout(struct emac_priv *priv)
{
    rt_kprintf("emac tx timeout.\n");
    priv->net_dev_stats.tx_errors++;
    emac_int_disable(priv);
    emac_stop_txch(priv, EMAC_DEF_TX_CH);
    emac_cleanup_txch(priv, EMAC_DEF_TX_CH);
    emac_init_txch(priv, EMAC_DEF_TX_CH);
    emac_write(EMAC_TXHDP(0), 0);
    emac_write(EMAC_TXINTMASKSET, BIT(EMAC_DEF_TX_CH));
    emac_int_enable(priv);
}


/* ethernet device interface */
/* transmit packet. */
rt_err_t rt_davinci_emac_tx( rt_device_t dev, struct pbuf* p)
{
    rt_err_t err;
    struct emac_priv *priv = dev->user_data;

    err = emac_dev_xmit(p, priv);
    if (err != RT_EOK)
    {
        emac_dev_tx_timeout(priv);
    }

    return RT_EOK;
}

/**
 * emac_addbd_to_rx_queue: Recycle RX buffer descriptor
 * @priv: The DaVinci EMAC driver private structure
 * @ch: RX channel number to process buffer descriptors for
 * @curr_bd: current buffer descriptor
 * @buffer: buffer pointer for descriptor
 * @buf_token: buffer token (stores pbuf information)
 *
 * Prepares the recycled buffer descriptor and addes it to hardware
 * receive queue - if queue empty this descriptor becomes the head
 * else addes the descriptor to end of queue
 *
 */
static void emac_addbd_to_rx_queue(struct emac_priv *priv, rt_uint32_t ch,
        struct emac_rx_bd __iomem *curr_bd,
        char *buffer, void *buf_token)
{
    struct emac_rxch *rxch = priv->rxch[ch];

    /* populate the hardware descriptor */
    curr_bd->h_next = 0;
    curr_bd->buff_ptr = virt_to_phys(buffer);
    curr_bd->off_b_len = rxch->buf_size;
    curr_bd->mode = EMAC_CPPI_OWNERSHIP_BIT;
    curr_bd->next = RT_NULL;
    curr_bd->data_ptr = buffer;
    curr_bd->buf_token = buf_token;

    /* write back  */
    BD_CACHE_WRITEBACK_INVALIDATE(curr_bd, EMAC_BD_LENGTH_FOR_CACHE);
    if (rxch->active_queue_head == RT_NULL) {
        rxch->active_queue_head = curr_bd;
        rxch->active_queue_tail = curr_bd;
        if (0 != rxch->queue_active) {
            emac_write(EMAC_RXHDP(ch),
                   emac_virt_to_phys(rxch->active_queue_head));
            rxch->queue_active = 1;
        }
    } else {
        struct emac_rx_bd __iomem *tail_bd;
        rt_uint32_t frame_status;

        tail_bd = rxch->active_queue_tail;
        rxch->active_queue_tail = curr_bd;
        tail_bd->next = curr_bd;
        tail_bd = EMAC_VIRT_NOCACHE(tail_bd);
        tail_bd->h_next = emac_virt_to_phys(curr_bd);
        frame_status = tail_bd->mode;
        if (frame_status & EMAC_CPPI_EOQ_BIT) {
            emac_write(EMAC_RXHDP(ch),
                    emac_virt_to_phys(curr_bd));
            frame_status &= ~(EMAC_CPPI_EOQ_BIT);
            tail_bd->mode = frame_status;
            ++rxch->end_of_queue_add;
        }
    }
    ++rxch->recycled_bd;
}

/**
 * emac_net_rx_cb: Prepares packet and sends to upper layer
 * @priv: The DaVinci EMAC driver private structure
 * @net_pkt_list: Network packet list (received packets)
 *
 * Invalidates packet buffer memory and sends the received packet to upper
 * layer
 *
 * Returns success or appropriate error code (none as of now)
 */
static int emac_net_rx_cb(struct emac_priv *priv,
              struct emac_netpktobj *net_pkt_list)
{
    struct eth_device *device = &priv->parent;
    struct pbuf *p;
    p = (struct pbuf *)net_pkt_list->pkt_token;
    /* set length of packet */
    p->tot_len = net_pkt_list->pkt_length;
    p->len = net_pkt_list->pkt_length;
    EMAC_CACHE_INVALIDATE((unsigned long)p->payload, p->len);
    if (device->netif->input(p, device->netif) != RT_EOK)
    {
        pbuf_free(p);
    }
    priv->net_dev_stats.rx_bytes += net_pkt_list->pkt_length;
    priv->net_dev_stats.rx_packets++;
    return 0;
}

/**
 * emac_net_alloc_rx_buf: Allocate a pbuf for RX
 * @priv: The DaVinci EMAC driver private structure
 * @buf_size: size of PBUF data buffer to allocate
 * @data_token: data token returned (pbuf handle for storing in buffer desc)
 * @ch: RX channel number
 *
 * Called during RX channel setup - allocates pbuf buffer of required size
 * and provides the pbuf handle and allocated buffer data pointer to caller
 *
 * Returns pbuf data pointer or 0 on failure to alloc pbuf
 */
static void *emac_net_alloc_rx_buf(struct emac_priv *priv, int buf_size,
        void **data_token, rt_uint32_t ch)
{
    struct pbuf* p;

    p = pbuf_alloc(PBUF_LINK, buf_size, PBUF_RAM);
    if (RT_NULL == p) {
        rt_kprintf("DaVinci EMAC: failed to alloc pbuf\n");
        return RT_NULL;
    }

    /* set device pointer in p and reserve space for extra bytes */
    *data_token = (void *) p;
    EMAC_CACHE_WRITEBACK_INVALIDATE((unsigned long)p->payload, buf_size);
    return p->payload;
}


/**
 * emac_rx_bdproc: RX buffer descriptor (packet) processing
 * @priv: The DaVinci EMAC driver private structure
 * @ch: RX channel number to process buffer descriptors for
 * @budget: number of packets allowed to process
 *
 * Processes RX buffer descriptors - checks ownership bit on the RX buffer
 * descriptor, sends the receive packet to upper layer, allocates a new PBUF
 * and recycles the buffer descriptor (requeues it in hardware RX queue).
 * Only "budget" number of packets are processed and indication of pending
 * packets provided to the caller.
 *
 * Returns number of packets processed (and indication of pending packets)
 */
static int emac_rx_bdproc(struct emac_priv *priv, rt_uint32_t ch, rt_uint32_t budget)
{
    unsigned long flags;
    rt_uint32_t frame_status;
    rt_uint32_t pkts_processed = 0;
    char *new_buffer;
    struct emac_rx_bd __iomem *curr_bd;
    struct emac_rx_bd __iomem *last_bd;
    struct emac_netpktobj *curr_pkt, pkt_obj;
    struct emac_netbufobj buf_obj;
    struct emac_netbufobj *rx_buf_obj;
    void *new_buf_token;
    struct emac_rxch *rxch = priv->rxch[ch];

    if (1 == rxch->teardown_pending)
        return 0;
    ++rxch->proc_count;
    rt_sem_take(&priv->rx_lock, RT_WAITING_FOREVER);
    pkt_obj.buf_list = &buf_obj;
    curr_pkt = &pkt_obj;
    curr_bd = rxch->active_queue_head;
    BD_CACHE_INVALIDATE(curr_bd, EMAC_BD_LENGTH_FOR_CACHE);
    frame_status = curr_bd->mode;

    while ((curr_bd) &&
           ((frame_status & EMAC_CPPI_OWNERSHIP_BIT) == 0) &&
           (pkts_processed < budget)) {

        new_buffer = emac_net_alloc_rx_buf(priv, rxch->buf_size,
                    &new_buf_token, EMAC_DEF_RX_CH);
        if (RT_NULL == new_buffer) {
            ++rxch->out_of_rx_buffers;
            goto end_emac_rx_bdproc;
        }

        /* populate received packet data structure */
        rx_buf_obj = &curr_pkt->buf_list[0];
        rx_buf_obj->data_ptr = (char *)curr_bd->data_ptr;
        rx_buf_obj->length = curr_bd->off_b_len & EMAC_RX_BD_BUF_SIZE;
        rx_buf_obj->buf_token = curr_bd->buf_token;
        curr_pkt->pkt_token = curr_pkt->buf_list->buf_token;
        curr_pkt->num_bufs = 1;
        curr_pkt->pkt_length =
            (frame_status & EMAC_RX_BD_PKT_LENGTH_MASK);
        emac_write(EMAC_RXCP(ch), emac_virt_to_phys(curr_bd));
        ++rxch->processed_bd;
        last_bd = curr_bd;
        curr_bd = last_bd->next;
        rxch->active_queue_head = curr_bd;

        /* check if end of RX queue ? */
        if (frame_status & EMAC_CPPI_EOQ_BIT) {
            if (curr_bd) {
                ++rxch->mis_queued_packets;
                emac_write(EMAC_RXHDP(ch),
                       emac_virt_to_phys(curr_bd));
            } else {
                ++rxch->end_of_queue;
                rxch->queue_active = 0;
            }
        }

        /* recycle BD */
        emac_addbd_to_rx_queue(priv, ch, last_bd, new_buffer,
                       new_buf_token);

        /* return the packet to the user - BD ptr passed in
         * last parameter for potential *future* use */
        rt_sem_release(&priv->rx_lock);
        emac_net_rx_cb(priv, curr_pkt);//???
        rt_sem_take(&priv->rx_lock, RT_WAITING_FOREVER);
        curr_bd = rxch->active_queue_head;
        if (curr_bd) {
            BD_CACHE_INVALIDATE(curr_bd, EMAC_BD_LENGTH_FOR_CACHE);
            frame_status = curr_bd->mode;
        }
        ++pkts_processed;
    }

end_emac_rx_bdproc:
    rt_sem_release(&priv->rx_lock);
    return pkts_processed;
}


/* reception packet. */
struct pbuf *rt_davinci_emac_rx(rt_device_t dev)
{
    struct emac_priv *priv = dev->user_data;
    struct pbuf* p = RT_NULL;
    rt_uint32_t len;
    void *buffer;

    struct pbuf* q;
    rt_uint8_t *buf = RT_NULL;
    unsigned int mask;
    rt_uint32_t status = 0;
    rt_uint32_t num_pkts = 0;

    /* Check interrupt vectors and call packet processing */
    status = emac_read(EMAC_MACINVECTOR);

    mask = EMAC_DM644X_MAC_IN_VECTOR_TX_INT_VEC;

    if (priv->version == EMAC_VERSION_2)
        mask = EMAC_DM646X_MAC_IN_VECTOR_TX_INT_VEC;

    if (status & mask) {
        num_pkts = emac_tx_bdproc(priv, EMAC_DEF_TX_CH,
                      EMAC_DEF_TX_MAX_SERVICE);
    } /* TX processing */

    /*if (num_pkts)
        //return budget;
        return RT_NULL;*/

    mask = EMAC_DM644X_MAC_IN_VECTOR_RX_INT_VEC;

    if (priv->version == EMAC_VERSION_2)
        mask = EMAC_DM646X_MAC_IN_VECTOR_RX_INT_VEC;

    if (status & mask) {
        num_pkts = emac_rx_bdproc(priv, EMAC_DEF_RX_CH, EMAC_DEF_RX_MAX_SERVICE);
    } /* RX processing */

    /*if (num_pkts < EMAC_DEF_RX_MAX_SERVICE) {
        emac_int_enable(priv);
    }*/

    mask = EMAC_DM644X_MAC_IN_VECTOR_HOST_INT;
    if (priv->version == EMAC_VERSION_2)
        mask = EMAC_DM646X_MAC_IN_VECTOR_HOST_INT;

    if (status & mask) {
        rt_uint32_t ch, cause;
        rt_kprintf("DaVinci EMAC: Fatal Hardware Error\n");

        status = emac_read(EMAC_MACSTATUS);
        cause = ((status & EMAC_MACSTATUS_TXERRCODE_MASK) >>
             EMAC_MACSTATUS_TXERRCODE_SHIFT);
        if (cause) {
            ch = ((status & EMAC_MACSTATUS_TXERRCH_MASK) >>
                  EMAC_MACSTATUS_TXERRCH_SHIFT);
        }
        cause = ((status & EMAC_MACSTATUS_RXERRCODE_MASK) >>
             EMAC_MACSTATUS_RXERRCODE_SHIFT);
        if (cause) {
            ch = ((status & EMAC_MACSTATUS_RXERRCH_MASK) >>
                  EMAC_MACSTATUS_RXERRCH_SHIFT);
        }
    } /* Host error processing */

    //return num_pkts;
    //return p;
    emac_int_enable(priv);
    return RT_NULL;
}


/**
 * emac_set_type0addr: Set EMAC Type0 mac address
 * @priv: The DaVinci EMAC driver private structure
 * @ch: RX channel number
 * @mac_addr: MAC address to set in device
 *
 * Called internally to set Type0 mac address of the Device
 *
 * Returns success (0) or appropriate error code (none as of now)
 */
static void emac_set_type0addr(struct emac_priv *priv, rt_uint32_t ch, char *mac_addr)
{
    rt_uint32_t val;
    val = ((mac_addr[5] << 8) | (mac_addr[4]));
    emac_write(EMAC_MACSRCADDRLO, val);

    val = ((mac_addr[3] << 24) | (mac_addr[2] << 16) | \
           (mac_addr[1] << 8) | (mac_addr[0]));
    emac_write(EMAC_MACSRCADDRHI, val);
    val = emac_read(EMAC_RXUNICASTSET);
    val |= BIT(ch);
    emac_write(EMAC_RXUNICASTSET, val);
    val = emac_read(EMAC_RXUNICASTCLEAR);
    val &= ~BIT(ch);
    emac_write(EMAC_RXUNICASTCLEAR, val);
}

/**
 * emac_set_type1addr: Set EMAC Type1 mac address
 * @priv: The DaVinci EMAC driver private structure
 * @ch: RX channel number
 * @mac_addr: MAC address to set in device
 *
 * Called internally to set Type1 mac address of the Device
 *
 * Returns success (0) or appropriate error code (none as of now)
 */
static void emac_set_type1addr(struct emac_priv *priv, rt_uint32_t ch, char *mac_addr)
{
    rt_uint32_t val;
    emac_write(EMAC_MACINDEX, ch);
    val = ((mac_addr[5] << 8) | mac_addr[4]);
    emac_write(EMAC_MACADDRLO, val);
    val = ((mac_addr[3] << 24) | (mac_addr[2] << 16) | \
           (mac_addr[1] << 8) | (mac_addr[0]));
    emac_write(EMAC_MACADDRHI, val);
    emac_set_type0addr(priv, ch, mac_addr);
}

/**
 * emac_set_type2addr: Set EMAC Type2 mac address
 * @priv: The DaVinci EMAC driver private structure
 * @ch: RX channel number
 * @mac_addr: MAC address to set in device
 * @index: index into RX address entries
 * @match: match parameter for RX address matching logic
 *
 * Called internally to set Type2 mac address of the Device
 *
 * Returns success (0) or appropriate error code (none as of now)
 */
static void emac_set_type2addr(struct emac_priv *priv, rt_uint32_t ch,
                   char *mac_addr, int index, int match)
{
    rt_uint32_t val;
    emac_write(EMAC_MACINDEX, index);
    val = ((mac_addr[3] << 24) | (mac_addr[2] << 16) | \
           (mac_addr[1] << 8) | (mac_addr[0]));
    emac_write(EMAC_MACADDRHI, val);
    val = ((mac_addr[5] << 8) | mac_addr[4] | ((ch & 0x7) << 16) | \
           (match << 19) | BIT(20));
    emac_write(EMAC_MACADDRLO, val);
    emac_set_type0addr(priv, ch, mac_addr);
}

/**
 * emac_setmac: Set mac address in the adapter (internal function)
 * @priv: The DaVinci EMAC driver private structure
 * @ch: RX channel number
 * @mac_addr: MAC address to set in device
 *
 * Called internally to set the mac address of the Device
 *
 * Returns success (0) or appropriate error code (none as of now)
 */
static void emac_setmac(struct emac_priv *priv, rt_uint32_t ch, char *mac_addr)
{
    if (priv->rx_addr_type == 0) {
        emac_set_type0addr(priv, ch, mac_addr);
    } else if (priv->rx_addr_type == 1) {
        rt_uint32_t cnt;
        for (cnt = 0; cnt < EMAC_MAX_TXRX_CHANNELS; cnt++)
            emac_set_type1addr(priv, ch, mac_addr);
    } else if (priv->rx_addr_type == 2) {
        emac_set_type2addr(priv, ch, mac_addr, ch, 1);
        emac_set_type0addr(priv, ch, mac_addr);
    } else {
        rt_kprintf("DaVinci EMAC: Wrong addressing\n");
    }
}


/** EMAC on-chip buffer descriptor memory
 *
 * WARNING: Please note that the on chip memory is used for both TX and RX
 * buffer descriptor queues and is equally divided between TX and RX desc's
 * If the number of TX or RX descriptors change this memory pointers need
 * to be adjusted. If external memory is allocated then these pointers can
 * pointer to the memory
 *
 */
#define EMAC_TX_BD_MEM(priv)    ((priv)->emac_ctrl_ram)
#define EMAC_RX_BD_MEM(priv)    ((priv)->emac_ctrl_ram + \
                (((priv)->ctrl_ram_size) >> 1))

/**
 * emac_init_txch: TX channel initialization
 * @priv: The DaVinci EMAC driver private structure
 * @ch: RX channel number
 *
 * Called during device init to setup a TX channel (allocate buffer desc
 * create free pool and keep ready for transmission
 *
 * Returns success(0) or mem alloc failures error code
 */
static int emac_init_txch(struct emac_priv *priv, rt_uint32_t ch)
{
    rt_uint32_t cnt, bd_size;
    void __iomem *mem;
    struct emac_tx_bd __iomem *curr_bd;
    struct emac_txch *txch = RT_NULL;

    txch = rt_malloc(sizeof(struct emac_txch));
    if (RT_NULL == txch) {
        rt_kprintf("DaVinci EMAC: TX Ch mem alloc failed");
        return -RT_ENOMEM;
    }
    rt_memset(txch, 0, sizeof(struct emac_txch));
    priv->txch[ch] = txch;
    txch->service_max = EMAC_DEF_TX_MAX_SERVICE;
    txch->active_queue_head = RT_NULL;
    txch->active_queue_tail = RT_NULL;
    txch->queue_active = 0;
    txch->teardown_pending = 0;

    /* allocate memory for TX CPPI channel on a 4 byte boundry */
    txch->tx_complete = rt_malloc(txch->service_max * sizeof(rt_uint32_t));
    if (RT_NULL == txch->tx_complete) {
        rt_kprintf("DaVinci EMAC: Tx service mem alloc failed");
        rt_free(txch);
        return -RT_ENOMEM;
    }
    memset(txch->tx_complete, 0, txch->service_max * sizeof(rt_uint32_t));

    /* allocate buffer descriptor pool align every BD on four word
     * boundry for future requirements */
    bd_size = (sizeof(struct emac_tx_bd) + 0xF) & ~0xF;
    txch->num_bd = (priv->ctrl_ram_size >> 1) / bd_size;
    txch->alloc_size = (((bd_size * txch->num_bd) + 0xF) & ~0xF);

    /* alloc TX BD memory */
    txch->bd_mem = EMAC_TX_BD_MEM(priv);
    rt_memset((void *)txch->bd_mem, 0, txch->alloc_size);

    /* initialize the BD linked list */
    mem = (void __iomem *)
            (((rt_uint32_t) txch->bd_mem + 0xF) & ~0xF);
    txch->bd_pool_head = RT_NULL;
    for (cnt = 0; cnt < txch->num_bd; cnt++) {
        curr_bd = mem + (cnt * bd_size);
        curr_bd->next = txch->bd_pool_head;
        txch->bd_pool_head = curr_bd;
    }

    /* reset statistics counters */
    txch->out_of_tx_bd = 0;
    txch->no_active_pkts = 0;
    txch->active_queue_count = 0;

    return 0;
}

/**
 * emac_init_rxch: RX channel initialization
 * @priv: The DaVinci EMAC driver private structure
 * @ch: RX channel number
 * @param: mac address for RX channel
 *
 * Called during device init to setup a RX channel (allocate buffers and
 * buffer descriptors, create queue and keep ready for reception
 *
 * Returns success(0) or mem alloc failures error code
 */
static int emac_init_rxch(struct emac_priv *priv, rt_uint32_t ch, char *param)
{
    rt_uint32_t cnt, bd_size;
    void __iomem *mem;
    struct emac_rx_bd __iomem *curr_bd;
    struct emac_rxch *rxch = RT_NULL;

    rxch = rt_malloc(sizeof(struct emac_rxch));
    if (RT_NULL == rxch) {
        rt_kprintf("DaVinci EMAC: RX Ch mem alloc failed");
        return -ENOMEM;
    }
    rt_memset(rxch, 0, sizeof(struct emac_rxch));
    priv->rxch[ch] = rxch;
    rxch->buf_size = priv->rx_buf_size;
    rxch->service_max = EMAC_DEF_RX_MAX_SERVICE;
    rxch->queue_active = 0;
    rxch->teardown_pending = 0;

    /* save mac address */
    for (cnt = 0; cnt < 6; cnt++)
        rxch->mac_addr[cnt] = param[cnt];

    /* allocate buffer descriptor pool align every BD on four word
     * boundry for future requirements */
    bd_size = (sizeof(struct emac_rx_bd) + 0xF) & ~0xF;
    rxch->num_bd = (priv->ctrl_ram_size >> 1) / bd_size;
    rxch->alloc_size = (((bd_size * rxch->num_bd) + 0xF) & ~0xF);
    rxch->bd_mem = EMAC_RX_BD_MEM(priv);

    rt_memset((void *)rxch->bd_mem, 0, rxch->alloc_size);
    rxch->pkt_queue.buf_list = &rxch->buf_queue;

    /* allocate RX buffer and initialize the BD linked list */
    mem = (void __iomem *)
            (((rt_uint32_t) rxch->bd_mem + 0xF) & ~0xF);
    rxch->active_queue_head = RT_NULL;
    rxch->active_queue_tail = mem;
    for (cnt = 0; cnt < rxch->num_bd; cnt++) {
        curr_bd = mem + (cnt * bd_size);
        /* for future use the last parameter contains the BD ptr */
        curr_bd->data_ptr = emac_net_alloc_rx_buf(priv,
                    rxch->buf_size,
                    (void **)&curr_bd->buf_token,
                    EMAC_DEF_RX_CH);
        if (curr_bd->data_ptr == RT_NULL) {
            rt_kprintf("DaVinci EMAC: RX buf mem alloc " \
                "failed for ch %d\n", ch);
            rt_free(rxch);
            return -RT_ENOMEM;
        }

        /* populate the hardware descriptor */
        curr_bd->h_next = emac_virt_to_phys(rxch->active_queue_head);
        curr_bd->buff_ptr = virt_to_phys(curr_bd->data_ptr);
        curr_bd->off_b_len = rxch->buf_size;
        curr_bd->mode = EMAC_CPPI_OWNERSHIP_BIT;

        /* write back to hardware memory */
        BD_CACHE_WRITEBACK_INVALIDATE((rt_uint32_t) curr_bd,
                          EMAC_BD_LENGTH_FOR_CACHE);
        curr_bd->next = rxch->active_queue_head;
        rxch->active_queue_head = curr_bd;
    }

    /* At this point rxCppi->activeQueueHead points to the first
       RX BD ready to be given to RX HDP and rxch->active_queue_tail
       points to the last RX BD
     */
    return 0;
}


/**
 * emac_int_disable: Disable EMAC module interrupt
 * @priv: The DaVinci EMAC driver private structure
 *
 * Disable EMAC interrupt
 *
 */
static void emac_int_disable(struct emac_priv *priv)
{
    if (priv->version == EMAC_VERSION_2) {
        unsigned long flags;

        rt_interrupt_enter();

        /* Program C0_Int_En to zero to turn off
        * interrupts to the CPU */
        emac_ctrl_write(EMAC_DM646X_CMRXINTEN, 0x0);
        emac_ctrl_write(EMAC_DM646X_CMTXINTEN, 0x0);
        /* NOTE: Rx Threshold and Misc interrupts are not disabled */

        rt_interrupt_leave();

    } else {
        /* Set DM644x control registers for interrupt control */
        emac_ctrl_write(EMAC_CTRL_EWCTL, 0x0);
    }
}


/**
 * emac_int_enable: Enable EMAC module interrupt
 * @priv: The DaVinci EMAC driver private structure
 *
 * Enable EMAC interrupt
 *
 */
static void emac_int_enable(struct emac_priv *priv)
{
    if (priv->version == EMAC_VERSION_2) {
        /*if (priv->int_enable)
            priv->int_enable();*/

        emac_ctrl_write(EMAC_DM646X_CMRXINTEN, 0xff);
        emac_ctrl_write(EMAC_DM646X_CMTXINTEN, 0xff);

        /* In addition to turning on interrupt Enable, we need
         * ack by writing appropriate values to the EOI
         * register */

        /* NOTE: Rx Threshold and Misc interrupts are not enabled */

        /* ack rxen only then a new pulse will be generated */
        emac_write(EMAC_DM646X_MACEOIVECTOR,
            EMAC_DM646X_MAC_EOI_C0_RXEN);

        /* ack txen- only then a new pulse will be generated */
        emac_write(EMAC_DM646X_MACEOIVECTOR,
            EMAC_DM646X_MAC_EOI_C0_TXEN);

    } else {
        /* Set DM644x control registers for interrupt control */
        emac_ctrl_write(EMAC_CTRL_EWCTL, 0x1);
    }
}


/**
 * emac_irq: EMAC interrupt handler
 * @irq: interrupt number
 * @param: EMAC isr parameters
 *
 */
static void emac_irq(int irq, void *param)
{
    struct emac_priv *priv = param;

    ++priv->isr_count;
    emac_int_disable(priv);
    eth_device_ready(&priv->parent);
}



/**
 * emac_hw_enable: Enable EMAC hardware for packet transmission/reception
 * @priv: The DaVinci EMAC private adapter structure
 *
 * Enables EMAC hardware for packet processing - enables PHY, enables RX
 * for packet reception and enables device interrupts
 *
 * Returns success (0) or appropriate error code (none right now)
 */
static int emac_hw_enable(struct emac_priv *priv)
{
    rt_uint32_t ch, val, mbp_enable, mac_control;

    /* Soft reset */
    emac_write(EMAC_SOFTRESET, 1);
    while (emac_read(EMAC_SOFTRESET));

    /* Disable interrupt & Set pacing for more interrupts initially */
    emac_int_disable(priv);

    /* Full duplex enable bit set when auto negotiation happens */
    mac_control =
        (((EMAC_DEF_TXPRIO_FIXED) ? (EMAC_MACCONTROL_TXPTYPE) : 0x0) |
        ((priv->speed == 1000) ? EMAC_MACCONTROL_GIGABITEN : 0x0) |
        ((EMAC_DEF_TXPACING_EN) ? (EMAC_MACCONTROL_TXPACEEN) : 0x0) |
        ((priv->duplex == DUPLEX_FULL) ? 0x1 : 0));
    emac_write(EMAC_MACCONTROL, mac_control);

    mbp_enable =
        (((EMAC_DEF_PASS_CRC) ? (EMAC_RXMBP_PASSCRC_MASK) : 0x0) |
        ((EMAC_DEF_QOS_EN) ? (EMAC_RXMBP_QOSEN_MASK) : 0x0) |
         ((EMAC_DEF_NO_BUFF_CHAIN) ? (EMAC_RXMBP_NOCHAIN_MASK) : 0x0) |
         ((EMAC_DEF_MACCTRL_FRAME_EN) ? (EMAC_RXMBP_CMFEN_MASK) : 0x0) |
         ((EMAC_DEF_SHORT_FRAME_EN) ? (EMAC_RXMBP_CSFEN_MASK) : 0x0) |
         ((EMAC_DEF_ERROR_FRAME_EN) ? (EMAC_RXMBP_CEFEN_MASK) : 0x0) |
         ((EMAC_DEF_PROM_EN) ? (EMAC_RXMBP_CAFEN_MASK) : 0x0) |
         ((EMAC_DEF_PROM_CH & EMAC_RXMBP_CHMASK) << \
            EMAC_RXMBP_PROMCH_SHIFT) |
         ((EMAC_DEF_BCAST_EN) ? (EMAC_RXMBP_BROADEN_MASK) : 0x0) |
         ((EMAC_DEF_BCAST_CH & EMAC_RXMBP_CHMASK) << \
            EMAC_RXMBP_BROADCH_SHIFT) |
         ((EMAC_DEF_MCAST_EN) ? (EMAC_RXMBP_MULTIEN_MASK) : 0x0) |
         ((EMAC_DEF_MCAST_CH & EMAC_RXMBP_CHMASK) << \
            EMAC_RXMBP_MULTICH_SHIFT));
    emac_write(EMAC_RXMBPENABLE, mbp_enable);
    emac_write(EMAC_RXMAXLEN, (EMAC_DEF_MAX_FRAME_SIZE &
                   EMAC_RX_MAX_LEN_MASK));
    emac_write(EMAC_RXBUFFEROFFSET, (EMAC_DEF_BUFFER_OFFSET &
                     EMAC_RX_BUFFER_OFFSET_MASK));
    emac_write(EMAC_RXFILTERLOWTHRESH, 0);
    emac_write(EMAC_RXUNICASTCLEAR, EMAC_RX_UNICAST_CLEAR_ALL);
    priv->rx_addr_type = (emac_read(EMAC_MACCONFIG) >> 8) & 0xFF;

    val = emac_read(EMAC_TXCONTROL);
    val |= EMAC_TX_CONTROL_TX_ENABLE_VAL;
    emac_write(EMAC_TXCONTROL, val);
    val = emac_read(EMAC_RXCONTROL);
    val |= EMAC_RX_CONTROL_RX_ENABLE_VAL;
    emac_write(EMAC_RXCONTROL, val);
    emac_write(EMAC_MACINTMASKSET, EMAC_MAC_HOST_ERR_INTMASK_VAL);

    for (ch = 0; ch < EMAC_DEF_MAX_TX_CH; ch++) {
        emac_write(EMAC_TXHDP(ch), 0);
        emac_write(EMAC_TXINTMASKSET, BIT(ch));
    }
    for (ch = 0; ch < EMAC_DEF_MAX_RX_CH; ch++) {
        struct emac_rxch *rxch = priv->rxch[ch];
        emac_setmac(priv, ch, rxch->mac_addr);
        emac_write(EMAC_RXINTMASKSET, BIT(ch));
        rxch->queue_active = 1;
        emac_write(EMAC_RXHDP(ch),
               (unsigned int)(rxch->active_queue_head)); /* physcal addr */
    }

    /* Enable MII */
    val = emac_read(EMAC_MACCONTROL);
    val |= (EMAC_MACCONTROL_GMIIEN);
    emac_write(EMAC_MACCONTROL, val);

    /* Enable interrupts */
    emac_int_enable(priv);
    return 0;

}

/**
 * emac_dev_getnetstats: EMAC get statistics function
 * @ndev: The DaVinci EMAC network adapter
 *
 * Called when system wants to get statistics from the device.
 *
 * We return the statistics in net_device_stats structure pulled from emac
 */
static struct net_device_stats *emac_dev_getnetstats(struct emac_priv *priv)
{
    rt_uint32_t mac_control;
    rt_uint32_t stats_clear_mask;

    /* update emac hardware stats and reset the registers*/

    mac_control = emac_read(EMAC_MACCONTROL);

    if (mac_control & EMAC_MACCONTROL_GMIIEN)
        stats_clear_mask = EMAC_STATS_CLR_MASK;
    else
        stats_clear_mask = 0;

    priv->net_dev_stats.multicast += emac_read(EMAC_RXMCASTFRAMES);
    emac_write(EMAC_RXMCASTFRAMES, stats_clear_mask);

    priv->net_dev_stats.collisions += (emac_read(EMAC_TXCOLLISION) +
                       emac_read(EMAC_TXSINGLECOLL) +
                       emac_read(EMAC_TXMULTICOLL));
    emac_write(EMAC_TXCOLLISION, stats_clear_mask);
    emac_write(EMAC_TXSINGLECOLL, stats_clear_mask);
    emac_write(EMAC_TXMULTICOLL, stats_clear_mask);

    priv->net_dev_stats.rx_length_errors += (emac_read(EMAC_RXOVERSIZED) +
                        emac_read(EMAC_RXJABBER) +
                        emac_read(EMAC_RXUNDERSIZED));
    emac_write(EMAC_RXOVERSIZED, stats_clear_mask);
    emac_write(EMAC_RXJABBER, stats_clear_mask);
    emac_write(EMAC_RXUNDERSIZED, stats_clear_mask);

    priv->net_dev_stats.rx_over_errors += (emac_read(EMAC_RXSOFOVERRUNS) +
                           emac_read(EMAC_RXMOFOVERRUNS));
    emac_write(EMAC_RXSOFOVERRUNS, stats_clear_mask);
    emac_write(EMAC_RXMOFOVERRUNS, stats_clear_mask);

    priv->net_dev_stats.rx_fifo_errors += emac_read(EMAC_RXDMAOVERRUNS);
    emac_write(EMAC_RXDMAOVERRUNS, stats_clear_mask);

    priv->net_dev_stats.tx_carrier_errors +=
        emac_read(EMAC_TXCARRIERSENSE);
    emac_write(EMAC_TXCARRIERSENSE, stats_clear_mask);

    priv->net_dev_stats.tx_fifo_errors = emac_read(EMAC_TXUNDERRUN);
    emac_write(EMAC_TXUNDERRUN, stats_clear_mask);

    return &priv->net_dev_stats;
}


/* RT-Thread Device Interface */
/* initialize the interface */

static rt_err_t rt_davinci_emac_init(rt_device_t dev)
{
    struct emac_priv *priv = dev->user_data;
    unsigned long paddr;
    rt_uint32_t ch, rc;
    int i;

    /* Configuration items */
    priv->rx_buf_size = EMAC_DEF_MAX_FRAME_SIZE + NET_IP_ALIGN;

    /* Clear basic hardware */
    for (ch = 0; ch < EMAC_MAX_TXRX_CHANNELS; ch++) {
        emac_write(EMAC_TXHDP(ch), 0);
        emac_write(EMAC_RXHDP(ch), 0);
        emac_write(EMAC_RXHDP(ch), 0);
        emac_write(EMAC_RXINTMASKCLEAR, EMAC_INT_MASK_CLEAR);
        emac_write(EMAC_TXINTMASKCLEAR, EMAC_INT_MASK_CLEAR);
    }
    priv->mac_hash1 = 0;
    priv->mac_hash2 = 0;
    emac_write(EMAC_MACHASH1, 0);
    emac_write(EMAC_MACHASH2, 0);

    /* multi ch not supported - open 1 TX, 1RX ch by default */
    rc = emac_init_txch(priv, EMAC_DEF_TX_CH);
    if (0 != rc) {
        rt_kprintf("DaVinci EMAC: emac_init_txch() failed");
        return rc;
    }
    rc = emac_init_rxch(priv, EMAC_DEF_RX_CH, priv->mac_addr);
    if (0 != rc) {
        rt_kprintf("DaVinci EMAC: emac_init_rxch() failed");
        return rc;
    }

    rt_hw_interrupt_install(IRQ_DM365_EMAC_RXPULSE, emac_irq,
                            (void *)priv, "EMAC_RXPULSE");
    rt_hw_interrupt_umask(IRQ_DM365_EMAC_RXPULSE);
    rt_hw_interrupt_install(IRQ_DM365_EMAC_TXPULSE, emac_irq,
                            (void *)priv, "EMAC_TXPULSE");
    rt_hw_interrupt_umask(IRQ_DM365_EMAC_TXPULSE);
    rt_hw_interrupt_install(IRQ_DM365_EMAC_RXTHRESH, emac_irq,
                            (void *)priv, "EMAC_RXTHRESH");
    rt_hw_interrupt_umask(IRQ_DM365_EMAC_RXTHRESH);
    rt_hw_interrupt_install(IRQ_DM365_EMAC_MISCPULSE, emac_irq,
                            (void *)priv, "EMAC_MISCPULSE");
    rt_hw_interrupt_umask(IRQ_DM365_EMAC_MISCPULSE);

    emac_mii_reset(priv);
    davinci_emac_phy_init(dev);

    /* Start/Enable EMAC hardware */
    emac_hw_enable(priv);

    rt_timer_init(&priv->timer, "link_timer",
        davinci_emac_update_link,
        (void *)priv,
        RT_TICK_PER_SECOND,
        RT_TIMER_FLAG_PERIODIC);

    rt_timer_start(&priv->timer);
    rt_kprintf("davinci emac initialized\n");

    return RT_EOK;
}

static rt_err_t rt_davinci_emac_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_davinci_emac_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t rt_davinci_emac_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    return -RT_ENOSYS;
}

static rt_ssize_t rt_davinci_emac_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    return -RT_ENOSYS;
}

static rt_err_t rt_davinci_emac_control(rt_device_t dev, int cmd, void *args)
{
    struct emac_priv *priv = dev->user_data;
    switch(cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if(args) rt_memcpy(args, priv->mac_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

void dm365_emac_gpio_init(void)
{
    rt_uint32_t arm_intmux;

    /*
     * EMAC interrupts are multiplexed with GPIO interrupts
     * Details are available at the DM365 ARM
     * Subsystem Users Guide(sprufg5.pdf) pages 133 - 134
     */
    arm_intmux = davinci_readl(DM365_ARM_INTMUX);
    arm_intmux |= (1 << 14)|(1 << 15)|(1 << 16)|(1 << 17);
    davinci_writel(arm_intmux, DM365_ARM_INTMUX);
}

int rt_hw_davinci_emac_init()
{
    struct emac_priv *priv = &davinci_emac_device;
    struct clk  *emac_clk;
    emac_clk = clk_get("EMACCLK");
    emac_bus_frequency = clk_get_rate(emac_clk);
    psc_change_state(DAVINCI_DM365_LPSC_CPGMAC, PSC_ENABLE);
    dm365_emac_gpio_init();
    rt_memset(&davinci_emac_device, 0, sizeof(davinci_emac_device));
    davinci_emac_device.emac_base = (void __iomem *)DM365_EMAC_CNTRL_BASE;
    davinci_emac_device.ctrl_base = (void __iomem *)DM365_EMAC_WRAP_CNTRL_BASE;
    davinci_emac_device.ctrl_ram_size = DM365_EMAC_CNTRL_RAM_SIZE;
    davinci_emac_device.emac_ctrl_ram = (void __iomem *)DM365_EMAC_WRAP_RAM_BASE;
    davinci_emac_device.mdio_base = (void __iomem *)DM365_EMAC_MDIO_BASE;
    davinci_emac_device.version = EMAC_VERSION_2;
    davinci_emac_device.rmii_en = 0;
    davinci_emac_device.phy_addr = 0x09;
    rt_sem_init(&priv->tx_lock, "tx_lock", 1, RT_IPC_FLAG_FIFO);
    rt_sem_init(&priv->rx_lock, "rx_lock", 1, RT_IPC_FLAG_FIFO);

    davinci_emac_device.mac_addr[0] = 0x00;
    davinci_emac_device.mac_addr[1] = 0x60;
    davinci_emac_device.mac_addr[2] = 0x6E;
    davinci_emac_device.mac_addr[3] = 0x11;
    davinci_emac_device.mac_addr[4] = 0x22;
    davinci_emac_device.mac_addr[5] = 0x33;

    davinci_emac_device.parent.parent.init       = rt_davinci_emac_init;
    davinci_emac_device.parent.parent.open       = rt_davinci_emac_open;
    davinci_emac_device.parent.parent.close      = rt_davinci_emac_close;
    davinci_emac_device.parent.parent.read       = rt_davinci_emac_read;
    davinci_emac_device.parent.parent.write      = rt_davinci_emac_write;
    davinci_emac_device.parent.parent.control    = rt_davinci_emac_control;
    davinci_emac_device.parent.parent.user_data  = &davinci_emac_device;

    davinci_emac_device.parent.eth_rx     = rt_davinci_emac_rx;
    davinci_emac_device.parent.eth_tx     = rt_davinci_emac_tx;

    eth_device_init(&(davinci_emac_device.parent), "e0");

}

INIT_DEVICE_EXPORT(rt_hw_davinci_emac_init);


#ifdef RT_USING_FINSH
#include <finsh.h>

void dump_emac_stats(void)
{
    int i;
    struct emac_priv *emac;
    struct net_device_stats *stats;
    rt_device_t dev = rt_device_find("e0");

    if(dev == RT_NULL)
        return;

    emac = (struct emac_priv *)dev->user_data;

    stats = emac_dev_getnetstats(emac);
    rt_kprintf("rx_packets      = %d\n"
                "tx_packets      = %d\n"
                "rx_bytes        = %d\n"
                "tx_bytes        = %d\n"
                "rx_errors       = %d\n"
                "tx_errors       = %d\n"
                "rx_dropped      = %d\n"
                "tx_dropped      = %d\n"
                "multicast       = %d\n"
                "collisions      = %d\n",
        stats->rx_packets,
        stats->tx_packets,
        stats->rx_bytes,
        stats->tx_bytes,
        stats->rx_errors,
        stats->tx_errors,
        stats->rx_dropped,
        stats->tx_dropped,
        stats->multicast,
        stats->collisions);

    rt_kprintf("rx_length_errors = %d\n"
                "rx_over_errors   = %d\n"
                "rx_crc_errors    = %d\n"
                "rx_frame_errors  = %d\n"
                "rx_fifo_errors   = %d\n"
                "rx_missed_errors = %d\n",
        stats->rx_length_errors,
        stats->rx_over_errors,
        stats->rx_crc_errors,
        stats->rx_frame_errors,
        stats->rx_fifo_errors,
        stats->rx_missed_errors);

    rt_kprintf("tx_aborted_errors   = %d\n"
                "tx_carrier_errors   = %d\n"
                "tx_fifo_errors      = %d\n"
                "tx_heartbeat_errors = %d\n"
                "tx_window_errors    = %d\n",
        stats->tx_aborted_errors,
        stats->tx_carrier_errors,
        stats->tx_fifo_errors,
        stats->tx_heartbeat_errors,
        stats->tx_window_errors);

    rt_kprintf("rx_compressed  = %d\n"
                "tx_compressed  = %d\n",
        stats->rx_compressed,
        stats->tx_compressed);

    rt_kprintf("\n");
}

FINSH_FUNCTION_EXPORT(dump_emac_stats, dump emac statistics);

#ifdef FINSH_USING_MSH
int cmd_dump_emac_stats(int argc, char** argv)
{
    dump_emac_stats();
    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_dump_emac_stats, dump_emac_stats, dump emac statistics);
#endif

#endif
