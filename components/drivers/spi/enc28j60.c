#include "enc28j60.h"

#define NET_TRACE
#define ETH_RX_DUMP
#define ETH_TX_DUMP

#ifdef NET_TRACE
#define NET_DEBUG         rt_kprintf
#else
#define NET_DEBUG(...)
#endif /* #ifdef NET_TRACE */

struct enc28j60_tx_list_typedef
{
    struct enc28j60_tx_list_typedef * prev;
    struct enc28j60_tx_list_typedef * next;
    rt_uint32_t addr; /* pkt addr in buffer */
    rt_uint32_t len;  /* pkt len */
    volatile rt_bool_t free; /* 0:busy, 1:free */
};
static struct enc28j60_tx_list_typedef enc28j60_tx_list[2];
static volatile struct enc28j60_tx_list_typedef * tx_current;
static volatile struct enc28j60_tx_list_typedef * tx_ack;
static struct rt_event tx_event;

/* private enc28j60 define */
/* enc28j60 spi interface function */
static uint8_t spi_read_op(struct rt_spi_device * spi_device, uint8_t op, uint8_t address);
static void spi_write_op(struct rt_spi_device * spi_device, uint8_t op, uint8_t address, uint8_t data);

static uint8_t spi_read(struct rt_spi_device * spi_device, uint8_t address);
static void spi_write(struct rt_spi_device * spi_device, rt_uint8_t address, rt_uint8_t data);

static void enc28j60_clkout(struct rt_spi_device * spi_device, rt_uint8_t clk);
static void enc28j60_set_bank(struct rt_spi_device * spi_device, uint8_t address);
static uint32_t enc28j60_interrupt_disable(struct rt_spi_device * spi_device);
static void enc28j60_interrupt_enable(struct rt_spi_device * spi_device, uint32_t level);

static uint16_t enc28j60_phy_read(struct rt_spi_device * spi_device, rt_uint8_t address);
static void enc28j60_phy_write(struct rt_spi_device * spi_device, rt_uint8_t address, uint16_t data);
static rt_bool_t enc28j60_check_link_status(struct rt_spi_device * spi_device);

#define enc28j60_lock(dev)      rt_mutex_take(&((struct net_device*)dev)->lock, RT_WAITING_FOREVER);
#define enc28j60_unlock(dev)    rt_mutex_release(&((struct net_device*)dev)->lock);

static struct net_device  enc28j60_dev;
static uint8_t  Enc28j60Bank;
//struct rt_spi_device * spi_device;
static uint16_t NextPacketPtr;

static void _delay_us(uint32_t us)
{
    volatile uint32_t len;
    for (; us > 0; us --)
        for (len = 0; len < 20; len++ );
}

/* enc28j60 spi interface function */
static uint8_t spi_read_op(struct rt_spi_device * spi_device, uint8_t op, uint8_t address)
{
    uint8_t send_buffer[2];
    uint8_t recv_buffer[1];
    uint32_t send_size = 1;

    send_buffer[0] = op | (address & ADDR_MASK);
    send_buffer[1] = 0xFF;

    /* do dummy read if needed (for mac and mii, see datasheet page 29). */
    if(address & 0x80)
    {
        send_size = 2;
    }

    rt_spi_send_then_recv(spi_device, send_buffer, send_size, recv_buffer, 1);
    return (recv_buffer[0]);
}

static void spi_write_op(struct rt_spi_device * spi_device, uint8_t op, uint8_t address, uint8_t data)
{
    uint32_t level;
    uint8_t buffer[2];

    level = rt_hw_interrupt_disable();

    buffer[0] = op | (address & ADDR_MASK);
    buffer[1] = data;
    rt_spi_send(spi_device, buffer, 2);

    rt_hw_interrupt_enable(level);
}

/* enc28j60 function */
static void enc28j60_clkout(struct rt_spi_device * spi_device, rt_uint8_t clk)
{
    /* setup clkout: 2 is 12.5MHz: */
    spi_write(spi_device, ECOCON, clk & 0x7);
}

static void enc28j60_set_bank(struct rt_spi_device * spi_device, uint8_t address)
{
    /* set the bank (if needed) .*/
    if((address & BANK_MASK) != Enc28j60Bank)
    {
        /* set the bank. */
        spi_write_op(spi_device, ENC28J60_BIT_FIELD_CLR, ECON1, (ECON1_BSEL1|ECON1_BSEL0));
        spi_write_op(spi_device, ENC28J60_BIT_FIELD_SET, ECON1, (address & BANK_MASK)>>5);
        Enc28j60Bank = (address & BANK_MASK);
    }
}

static uint8_t spi_read(struct rt_spi_device * spi_device, uint8_t address)
{
    /* set the bank. */
    enc28j60_set_bank(spi_device, address);
    /* do the read. */
    return spi_read_op(spi_device, ENC28J60_READ_CTRL_REG, address);
}

static void spi_write(struct rt_spi_device * spi_device, rt_uint8_t address, rt_uint8_t data)
{
    /* set the bank. */
    enc28j60_set_bank(spi_device, address);
    /* do the write. */
    spi_write_op(spi_device, ENC28J60_WRITE_CTRL_REG, address, data);
}

static uint16_t enc28j60_phy_read(struct rt_spi_device * spi_device, rt_uint8_t address)
{
    uint16_t value;

    /* Set the right address and start the register read operation. */
    spi_write(spi_device, MIREGADR, address);
    spi_write(spi_device, MICMD, MICMD_MIIRD);

    _delay_us(15);

    /* wait until the PHY read completes. */
    while(spi_read(spi_device, MISTAT) & MISTAT_BUSY);

    /* reset reading bit */
    spi_write(spi_device, MICMD, 0x00);

    value = spi_read(spi_device, MIRDL) | spi_read(spi_device, MIRDH)<<8;

    return (value);
}

static void enc28j60_phy_write(struct rt_spi_device * spi_device, rt_uint8_t address, uint16_t data)
{
    /* set the PHY register address. */
    spi_write(spi_device, MIREGADR, address);

    /* write the PHY data. */
    spi_write(spi_device, MIWRL, data);
    spi_write(spi_device, MIWRH, data>>8);

    /* wait until the PHY write completes. */
    while(spi_read(spi_device, MISTAT) & MISTAT_BUSY)
    {
        _delay_us(15);
    }
}

static uint32_t enc28j60_interrupt_disable(struct rt_spi_device * spi_device)
{
    uint32_t level;

    /* switch to bank 0 */
    enc28j60_set_bank(spi_device, EIE);

    /* get last interrupt level */
    level = spi_read(spi_device, EIE);
    /* disable interrutps */
    spi_write_op(spi_device, ENC28J60_BIT_FIELD_CLR, EIE, level);

    return level;
}

static void enc28j60_interrupt_enable(struct rt_spi_device * spi_device, uint32_t level)
{
    /* switch to bank 0 */
    enc28j60_set_bank(spi_device, EIE);
    spi_write_op(spi_device, ENC28J60_BIT_FIELD_SET, EIE, level);
}

/*
 * Access the PHY to determine link status
 */
static rt_bool_t enc28j60_check_link_status(struct rt_spi_device * spi_device)
{
    uint16_t reg;
    int duplex;

    reg = enc28j60_phy_read(spi_device, PHSTAT2);
    duplex = reg & PHSTAT2_DPXSTAT;

    if (reg & PHSTAT2_LSTAT)
    {
        /* on */
        return RT_TRUE;
    }
    else
    {
        /* off */
        return RT_FALSE;
    }
}


/************************* RT-Thread Device Interface *************************/
void enc28j60_isr(void)
{
    eth_device_ready(&enc28j60_dev.parent);
    NET_DEBUG("enc28j60_isr\r\n");
}

static void _tx_chain_init(void)
{
    enc28j60_tx_list[0].next = &enc28j60_tx_list[1];
    enc28j60_tx_list[1].next = &enc28j60_tx_list[0];

    enc28j60_tx_list[0].prev = &enc28j60_tx_list[1];
    enc28j60_tx_list[1].prev = &enc28j60_tx_list[0];

    enc28j60_tx_list[0].addr = TXSTART_INIT;
    enc28j60_tx_list[1].addr = TXSTART_INIT + MAX_TX_PACKAGE_SIZE;

    enc28j60_tx_list[0].free = RT_TRUE;
    enc28j60_tx_list[1].free = RT_TRUE;

    tx_current = &enc28j60_tx_list[0];
    tx_ack = tx_current;
}

/* initialize the interface */
static rt_err_t enc28j60_init(rt_device_t dev)
{
    struct net_device * enc28j60 = (struct net_device *)dev;
    struct rt_spi_device * spi_device = enc28j60->spi_device;

    enc28j60_lock(dev);

    _tx_chain_init();

    // perform system reset
    spi_write_op(spi_device, ENC28J60_SOFT_RESET, 0, ENC28J60_SOFT_RESET);
    rt_thread_delay(RT_TICK_PER_SECOND/50); /* delay 20ms */

    NextPacketPtr = RXSTART_INIT;

    // Rx start
    spi_write(spi_device, ERXSTL, RXSTART_INIT&0xFF);
    spi_write(spi_device, ERXSTH, RXSTART_INIT>>8);
    // set receive pointer address
    spi_write(spi_device, ERXRDPTL, RXSTOP_INIT&0xFF);
    spi_write(spi_device, ERXRDPTH, RXSTOP_INIT>>8);
    // RX end
    spi_write(spi_device, ERXNDL, RXSTOP_INIT&0xFF);
    spi_write(spi_device, ERXNDH, RXSTOP_INIT>>8);

    // TX start
    spi_write(spi_device, ETXSTL, TXSTART_INIT&0xFF);
    spi_write(spi_device, ETXSTH, TXSTART_INIT>>8);
    // set transmission pointer address
    spi_write(spi_device, EWRPTL, TXSTART_INIT&0xFF);
    spi_write(spi_device, EWRPTH, TXSTART_INIT>>8);
    // TX end
    spi_write(spi_device, ETXNDL, TXSTOP_INIT&0xFF);
    spi_write(spi_device, ETXNDH, TXSTOP_INIT>>8);

    // do bank 1 stuff, packet filter:
    // For broadcast packets we allow only ARP packtets
    // All other packets should be unicast only for our mac (MAADR)
    //
    // The pattern to match on is therefore
    // Type     ETH.DST
    // ARP      BROADCAST
    // 06 08 -- ff ff ff ff ff ff -> ip checksum for theses bytes=f7f9
    // in binary these poitions are:11 0000 0011 1111
    // This is hex 303F->EPMM0=0x3f,EPMM1=0x30
    spi_write(spi_device, ERXFCON, ERXFCON_UCEN|ERXFCON_CRCEN|ERXFCON_BCEN);

    // do bank 2 stuff
    // enable MAC receive
    spi_write(spi_device, MACON1, MACON1_MARXEN|MACON1_TXPAUS|MACON1_RXPAUS);
    // enable automatic padding to 60bytes and CRC operations
    // spi_write_op(ENC28J60_BIT_FIELD_SET, MACON3, MACON3_PADCFG0|MACON3_TXCRCEN|MACON3_FRMLNEN);
    spi_write_op(spi_device, ENC28J60_BIT_FIELD_SET, MACON3, MACON3_PADCFG0 | MACON3_TXCRCEN | MACON3_FRMLNEN | MACON3_FULDPX);
    // bring MAC out of reset

    // set inter-frame gap (back-to-back)
    // spi_write(MABBIPG, 0x12);
    spi_write(spi_device, MABBIPG, 0x15);

    spi_write(spi_device, MACON4, MACON4_DEFER);
    spi_write(spi_device, MACLCON2, 63);

    // set inter-frame gap (non-back-to-back)
    spi_write(spi_device, MAIPGL, 0x12);
    spi_write(spi_device, MAIPGH, 0x0C);

    // Set the maximum packet size which the controller will accept
    // Do not send packets longer than MAX_FRAMELEN:
    spi_write(spi_device, MAMXFLL, MAX_FRAMELEN&0xFF);
    spi_write(spi_device, MAMXFLH, MAX_FRAMELEN>>8);

    // do bank 3 stuff
    // write MAC address
    // NOTE: MAC address in ENC28J60 is byte-backward
    spi_write(spi_device, MAADR0, enc28j60->dev_addr[5]);
    spi_write(spi_device, MAADR1, enc28j60->dev_addr[4]);
    spi_write(spi_device, MAADR2, enc28j60->dev_addr[3]);
    spi_write(spi_device, MAADR3, enc28j60->dev_addr[2]);
    spi_write(spi_device, MAADR4, enc28j60->dev_addr[1]);
    spi_write(spi_device, MAADR5, enc28j60->dev_addr[0]);

    /* output off */
    spi_write(spi_device, ECOCON, 0x00);

    // enc28j60_phy_write(PHCON1, 0x00);
    enc28j60_phy_write(spi_device, PHCON1, PHCON1_PDPXMD); // full duplex
    // no loopback of transmitted frames
    enc28j60_phy_write(spi_device, PHCON2, PHCON2_HDLDIS);

    enc28j60_set_bank(spi_device, ECON2);
    spi_write_op(spi_device, ENC28J60_BIT_FIELD_SET, ECON2, ECON2_AUTOINC);

    // switch to bank 0
    enc28j60_set_bank(spi_device, ECON1);
    // enable all interrutps
    spi_write_op(spi_device, ENC28J60_BIT_FIELD_SET, EIE, 0xFF);
    // enable packet reception
    spi_write_op(spi_device, ENC28J60_BIT_FIELD_SET, ECON1, ECON1_RXEN);

    /* clock out */
    enc28j60_clkout(spi_device, 2);

    enc28j60_phy_write(spi_device, PHLCON, 0xD76);	//0x476
    rt_thread_delay(RT_TICK_PER_SECOND/50); /* delay 20ms */

    enc28j60_unlock(dev);
    return RT_EOK;
}

/* control the interface */
static rt_err_t enc28j60_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    struct net_device * enc28j60 = (struct net_device *)dev;
    switch(cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if(args) rt_memcpy(args, enc28j60->dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

/* Open the ethernet interface */
static rt_err_t enc28j60_open(rt_device_t dev, uint16_t oflag)
{
    return RT_EOK;
}

/* Close the interface */
static rt_err_t enc28j60_close(rt_device_t dev)
{
    return RT_EOK;
}

/* Read */
static rt_size_t enc28j60_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return RT_EOK;
}

/* Write */
static rt_size_t enc28j60_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

/* ethernet device interface */
/* Transmit packet. */
static rt_err_t enc28j60_tx( rt_device_t dev, struct pbuf* p)
{
    struct net_device * enc28j60 = (struct net_device *)dev;
    struct rt_spi_device * spi_device = enc28j60->spi_device;
    struct pbuf* q;
    rt_uint32_t level;
#ifdef ETH_TX_DUMP
    rt_size_t dump_count = 0;
    rt_uint8_t * dump_ptr;
    rt_size_t dump_i;
#endif

    if(tx_current->free == RT_FALSE)
    {
        NET_DEBUG("[Tx] no empty buffer!\r\n");
        while(tx_current->free == RT_FALSE)
        {
            rt_err_t result;
            rt_uint32_t recved;

            /* there is no block yet, wait a flag */
            result = rt_event_recv(&tx_event, 0x01,
                                   RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved);

            RT_ASSERT(result == RT_EOK);
        }
        NET_DEBUG("[Tx] wait empty buffer done!\r\n");
    }

    enc28j60_lock(dev);

    /* disable enc28j60 interrupt */
    level = enc28j60_interrupt_disable(spi_device);

    // Set the write pointer to start of transmit buffer area
//    spi_write(EWRPTL, TXSTART_INIT&0xFF);
//    spi_write(EWRPTH, TXSTART_INIT>>8);
    spi_write(spi_device, EWRPTL, (tx_current->addr)&0xFF);
    spi_write(spi_device, EWRPTH, (tx_current->addr)>>8);
    // Set the TXND pointer to correspond to the packet size given
    tx_current->len = p->tot_len;
//    spi_write(ETXNDL, (TXSTART_INIT+ p->tot_len + 1)&0xFF);
//    spi_write(ETXNDH, (TXSTART_INIT+ p->tot_len + 1)>>8);

    // write per-packet control byte (0x00 means use macon3 settings)
    spi_write_op(spi_device, ENC28J60_WRITE_BUF_MEM, 0, 0x00);

#ifdef ETH_TX_DUMP
    NET_DEBUG("tx_dump, size:%d\r\n", p->tot_len);
#endif
    for (q = p; q != NULL; q = q->next)
    {
        uint8_t cmd = ENC28J60_WRITE_BUF_MEM;
        rt_spi_send_then_send(enc28j60->spi_device, &cmd, 1, q->payload, q->len);
#ifdef ETH_RX_DUMP
        dump_ptr = q->payload;
        for(dump_i=0; dump_i<q->len; dump_i++)
        {
            NET_DEBUG("%02x ", *dump_ptr);
            if( ((dump_count+1)%8) == 0 )
            {
                NET_DEBUG("  ");
            }
            if( ((dump_count+1)%16) == 0 )
            {
                NET_DEBUG("\r\n");
            }
            dump_count++;
            dump_ptr++;
        }
#endif
    }
#ifdef ETH_RX_DUMP
    NET_DEBUG("\r\n");
#endif

    // send the contents of the transmit buffer onto the network
    if(tx_current == tx_ack)
    {
        NET_DEBUG("[Tx] stop, restart!\r\n");
        // TX start
        spi_write(spi_device, ETXSTL, (tx_current->addr)&0xFF);
        spi_write(spi_device, ETXSTH, (tx_current->addr)>>8);
        // TX end
        spi_write(spi_device, ETXNDL, (tx_current->addr + tx_current->len)&0xFF);
        spi_write(spi_device, ETXNDH, (tx_current->addr + tx_current->len)>>8);

        spi_write_op(spi_device, ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRTS);
    }
    else
    {
        NET_DEBUG("[Tx] busy, add to chain!\r\n");
    }

    tx_current->free = RT_FALSE;
    tx_current = tx_current->next;

    /* Reset the transmit logic problem. See Rev. B4 Silicon Errata point 12. */
    if( (spi_read(spi_device, EIR) & EIR_TXERIF) )
    {
        spi_write_op(spi_device, ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRST);
    }

    /* enable enc28j60 interrupt */
    enc28j60_interrupt_enable(spi_device, level);

    enc28j60_unlock(dev);

    return RT_EOK;
}

/* recv packet. */
static struct pbuf *enc28j60_rx(rt_device_t dev)
{
    struct net_device * enc28j60 = (struct net_device *)dev;
    struct rt_spi_device * spi_device = enc28j60->spi_device;
    struct pbuf* p = RT_NULL;

    uint8_t eir, eir_clr;
    uint32_t pk_counter;
    rt_uint32_t level;
    rt_uint32_t len;
    rt_uint16_t rxstat;

    enc28j60_lock(dev);

    /* disable enc28j60 interrupt */
    level = enc28j60_interrupt_disable(spi_device);

    /* get EIR */
    eir = spi_read(spi_device, EIR);

    while(eir & ~EIR_PKTIF)
    {
        eir_clr = 0;

        /* clear PKTIF */
        if (eir & EIR_PKTIF)
        {
            NET_DEBUG("EIR_PKTIF\r\n");

            /* switch to bank 0. */
            enc28j60_set_bank(spi_device, EIE);
            /* disable rx interrutps. */
            spi_write_op(spi_device, ENC28J60_BIT_FIELD_CLR, EIE, EIE_PKTIE);
            eir_clr |= EIR_PKTIF;
//            enc28j60_set_bank(spi_device, EIR);
//            spi_write_op(spi_device, ENC28J60_BIT_FIELD_CLR, EIR, EIR_PKTIF);
        }

        /* clear DMAIF */
        if (eir & EIR_DMAIF)
        {
            NET_DEBUG("EIR_DMAIF\r\n");
            eir_clr |= EIR_DMAIF;
//            enc28j60_set_bank(spi_device, EIR);
//            spi_write_op(spi_device, ENC28J60_BIT_FIELD_CLR, EIR, EIR_DMAIF);
        }

        /* LINK changed handler */
        if ( eir & EIR_LINKIF)
        {
            rt_bool_t link_status;

            NET_DEBUG("EIR_LINKIF\r\n");
            link_status = enc28j60_check_link_status(spi_device);

            /* read PHIR to clear the flag */
            enc28j60_phy_read(spi_device, PHIR);
            eir_clr |= EIR_LINKIF;
//            enc28j60_set_bank(spi_device, EIR);
//            spi_write_op(spi_device, ENC28J60_BIT_FIELD_CLR, EIR, EIR_LINKIF);

            eth_device_linkchange(&(enc28j60->parent), link_status);
        }

        if (eir & EIR_TXIF)
        {
            /* A frame has been transmitted. */
            enc28j60_set_bank(spi_device, EIR);
            spi_write_op(spi_device, ENC28J60_BIT_FIELD_CLR, EIR, EIR_TXIF);

            tx_ack->free = RT_TRUE;
            tx_ack = tx_ack->next;
            if(tx_ack->free == RT_FALSE)
            {
                NET_DEBUG("[tx isr] Tx chain not empty, continue send the next pkt!\r\n");
                // TX start
                spi_write(spi_device, ETXSTL, (tx_ack->addr)&0xFF);
                spi_write(spi_device, ETXSTH, (tx_ack->addr)>>8);
                // TX end
                spi_write(spi_device, ETXNDL, (tx_ack->addr + tx_ack->len)&0xFF);
                spi_write(spi_device, ETXNDH, (tx_ack->addr + tx_ack->len)>>8);

                spi_write_op(spi_device, ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRTS);
            }
            else
            {
                NET_DEBUG("[tx isr] Tx chain empty, stop!\r\n");
            }

            /* set event */
            rt_event_send(&tx_event, 0x01);
        }

        /* wake up handler */
        if ( eir & EIR_WOLIF)
        {
            NET_DEBUG("EIR_WOLIF\r\n");
            eir_clr |= EIR_WOLIF;
//            enc28j60_set_bank(spi_device, EIR);
//            spi_write_op(spi_device, ENC28J60_BIT_FIELD_CLR, EIR, EIR_WOLIF);
        }

        /* TX Error handler */
        if ((eir & EIR_TXERIF) != 0)
        {
            NET_DEBUG("EIR_TXERIF re-start tx chain!\r\n");
            enc28j60_set_bank(spi_device, ECON1);
            spi_write_op(spi_device, ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRST);
            spi_write_op(spi_device, ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRST);
            eir_clr |= EIR_TXERIF;
//            enc28j60_set_bank(spi_device, EIR);
//            spi_write_op(spi_device, ENC28J60_BIT_FIELD_CLR, EIR, EIR_TXERIF);

            /* re-init tx chain */
            _tx_chain_init();
        }

        /* RX Error handler */
        if ((eir & EIR_RXERIF) != 0)
        {
            NET_DEBUG("EIR_RXERIF re-start rx!\r\n");

            NextPacketPtr = RXSTART_INIT;
            enc28j60_set_bank(spi_device, ECON1);
            spi_write_op(spi_device, ENC28J60_BIT_FIELD_SET, ECON1, ECON1_RXRST);
            spi_write_op(spi_device, ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_RXRST);
            /* switch to bank 0. */
            enc28j60_set_bank(spi_device, ECON1);
            /* enable packet reception. */
            spi_write_op(spi_device, ENC28J60_BIT_FIELD_SET, ECON1, ECON1_RXEN);
            eir_clr |= EIR_RXERIF;
//            enc28j60_set_bank(spi_device, EIR);
//            spi_write_op(spi_device, ENC28J60_BIT_FIELD_CLR, EIR, EIR_RXERIF);
        }

        enc28j60_set_bank(spi_device, EIR);
        spi_write_op(spi_device, ENC28J60_BIT_FIELD_CLR, EIR, eir_clr);

        eir = spi_read(spi_device, EIR);
    }

    /* read pkt */
    pk_counter = spi_read(spi_device, EPKTCNT);
    if(pk_counter)
    {
        /* Set the read pointer to the start of the received packet. */
        spi_write(spi_device, ERDPTL, (NextPacketPtr));
        spi_write(spi_device, ERDPTH, (NextPacketPtr)>>8);

        /* read the next packet pointer. */
        NextPacketPtr  = spi_read_op(spi_device, ENC28J60_READ_BUF_MEM, 0);
        NextPacketPtr |= spi_read_op(spi_device, ENC28J60_READ_BUF_MEM, 0)<<8;

        /* read the packet length (see datasheet page 43). */
        len  = spi_read_op(spi_device, ENC28J60_READ_BUF_MEM, 0);	    //0x54
        len |= spi_read_op(spi_device, ENC28J60_READ_BUF_MEM, 0)<<8;	//5554

        len-=4; //remove the CRC count

        // read the receive status (see datasheet page 43)
        rxstat  = spi_read_op(spi_device, ENC28J60_READ_BUF_MEM, 0);
        rxstat |= ((rt_uint16_t)spi_read_op(spi_device, ENC28J60_READ_BUF_MEM, 0))<<8;

        // check CRC and symbol errors (see datasheet page 44, table 7-3):
        // The ERXFCON.CRCEN is set by default. Normally we should not
        // need to check this.
        if ((rxstat & 0x80)==0)
        {
            // invalid
            len=0;
        }
        else
        {
            /* allocation pbuf */
            p = pbuf_alloc(PBUF_LINK, len, PBUF_RAM);
            if (p != RT_NULL)
            {
                struct pbuf* q;
#ifdef ETH_RX_DUMP
                rt_size_t dump_count = 0;
                rt_uint8_t * dump_ptr;
                rt_size_t dump_i;
                NET_DEBUG("rx_dump, size:%d\r\n", len);
#endif
                for (q = p; q != RT_NULL; q= q->next)
                {
                    uint8_t cmd = ENC28J60_READ_BUF_MEM;
                    rt_spi_send_then_recv(spi_device, &cmd, 1, q->payload, q->len);
#ifdef ETH_RX_DUMP
                    dump_ptr = q->payload;
                    for(dump_i=0; dump_i<q->len; dump_i++)
                    {
                        NET_DEBUG("%02x ", *dump_ptr);
                        if( ((dump_count+1)%8) == 0 )
                        {
                            NET_DEBUG("  ");
                        }
                        if( ((dump_count+1)%16) == 0 )
                        {
                            NET_DEBUG("\r\n");
                        }
                        dump_count++;
                        dump_ptr++;
                    }
#endif
                }
#ifdef ETH_RX_DUMP
                NET_DEBUG("\r\n");
#endif
            }
        }

        /* Move the RX read pointer to the start of the next received packet. */
        /* This frees the memory we just read out. */
        spi_write(spi_device, ERXRDPTL, (NextPacketPtr));
        spi_write(spi_device, ERXRDPTH, (NextPacketPtr)>>8);

        /* decrement the packet counter indicate we are done with this packet. */
        spi_write_op(spi_device, ENC28J60_BIT_FIELD_SET, ECON2, ECON2_PKTDEC);
    }
    else
    {
        /* switch to bank 0. */
        enc28j60_set_bank(spi_device, ECON1);
        /* enable packet reception. */
        spi_write_op(spi_device, ENC28J60_BIT_FIELD_SET, ECON1, ECON1_RXEN);

        level |= EIE_PKTIE;
    }

    /* enable enc28j60 interrupt */
    enc28j60_interrupt_enable(spi_device, level);

    enc28j60_unlock(dev);

    return p;
}

rt_err_t enc28j60_attach(const char * spi_device_name)
{
    struct rt_spi_device * spi_device;

    spi_device = (struct rt_spi_device *)rt_device_find(spi_device_name);
    if(spi_device == RT_NULL)
    {
        NET_DEBUG("spi device %s not found!\r\n", spi_device_name);
        return -RT_ENOSYS;
    }

    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible Modes 0 */
        cfg.max_hz = 20 * 1000 * 1000; /* SPI Interface with Clock Speeds Up to 20 MHz */
        rt_spi_configure(spi_device, &cfg);
    } /* config spi */

    memset(&enc28j60_dev, 0, sizeof(enc28j60_dev));

    rt_event_init(&tx_event, "eth_tx", RT_IPC_FLAG_FIFO);
    enc28j60_dev.spi_device = spi_device;

    /* detect device */
    {
        uint16_t value;

        /* perform system reset. */
        spi_write_op(spi_device, ENC28J60_SOFT_RESET, 0, ENC28J60_SOFT_RESET);
        rt_thread_delay(1); /* delay 20ms */

        enc28j60_dev.emac_rev = spi_read(spi_device, EREVID);
        value = enc28j60_phy_read(spi_device, PHHID2);
        enc28j60_dev.phy_rev = value&0x0F;
        enc28j60_dev.phy_pn = (value>>4)&0x3F;
        enc28j60_dev.phy_id = (enc28j60_phy_read(spi_device, PHHID1) | ((value>>10)<<16))<<3;

        if(enc28j60_dev.phy_id != 0x00280418)
        {
            NET_DEBUG("ENC28J60 PHY ID not correct!\r\n");
            NET_DEBUG("emac_rev:%d\r\n", enc28j60_dev.emac_rev);
            NET_DEBUG("phy_rev:%02X\r\n", enc28j60_dev.phy_rev);
            NET_DEBUG("phy_pn:%02X\r\n", enc28j60_dev.phy_pn);
            NET_DEBUG("phy_id:%08X\r\n", enc28j60_dev.phy_id);
            return RT_EIO;
        }
    }

    /* OUI 00-04-A3 (hex): Microchip Technology, Inc. */
    enc28j60_dev.dev_addr[0] = 0x00;
    enc28j60_dev.dev_addr[1] = 0x04;
    enc28j60_dev.dev_addr[2] = 0xA3;
    /* set MAC address, only for test */
    enc28j60_dev.dev_addr[3] = 0x12;
    enc28j60_dev.dev_addr[4] = 0x34;
    enc28j60_dev.dev_addr[5] = 0x56;

    /* init rt-thread device struct */
    enc28j60_dev.parent.parent.type    = RT_Device_Class_NetIf;
    enc28j60_dev.parent.parent.init    = enc28j60_init;
    enc28j60_dev.parent.parent.open    = enc28j60_open;
    enc28j60_dev.parent.parent.close   = enc28j60_close;
    enc28j60_dev.parent.parent.read    = enc28j60_read;
    enc28j60_dev.parent.parent.write   = enc28j60_write;
    enc28j60_dev.parent.parent.control = enc28j60_control;

    /* init rt-thread ethernet device struct */
    enc28j60_dev.parent.eth_rx  = enc28j60_rx;
    enc28j60_dev.parent.eth_tx  = enc28j60_tx;

    rt_mutex_init(&enc28j60_dev.lock, "enc28j60", RT_IPC_FLAG_FIFO);

    eth_device_init(&(enc28j60_dev.parent), "e0");

    return RT_EOK;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
/*
 * Debug routine to dump useful register contents
 */
static void enc28j60(void)
{
    struct rt_spi_device * spi_device = enc28j60_dev.spi_device;
    enc28j60_lock(&enc28j60_dev);

    rt_kprintf("-- enc28j60 registers:\n");
    rt_kprintf("HwRevID: 0x%02X\n", spi_read(spi_device, EREVID));

    rt_kprintf("Cntrl: ECON1 ECON2 ESTAT  EIR  EIE\n");
    rt_kprintf("       0x%02X  0x%02X  0x%02X  0x%02X  0x%02X\n",
               spi_read(spi_device, ECON1),
               spi_read(spi_device, ECON2),
               spi_read(spi_device, ESTAT),
               spi_read(spi_device, EIR),
               spi_read(spi_device, EIE));

    rt_kprintf("MAC  : MACON1 MACON3 MACON4\n");
    rt_kprintf("       0x%02X   0x%02X   0x%02X\n",
               spi_read(spi_device, MACON1),
               spi_read(spi_device, MACON3),
               spi_read(spi_device, MACON4));

    rt_kprintf("Rx   : ERXST  ERXND  ERXWRPT ERXRDPT ERXFCON EPKTCNT MAMXFL\n");
    rt_kprintf("       0x%04X 0x%04X 0x%04X  0x%04X  ",
               (spi_read(spi_device, ERXSTH) << 8) | spi_read(spi_device, ERXSTL),
               (spi_read(spi_device, ERXNDH) << 8) | spi_read(spi_device, ERXNDL),
               (spi_read(spi_device, ERXWRPTH) << 8) | spi_read(spi_device, ERXWRPTL),
               (spi_read(spi_device, ERXRDPTH) << 8) | spi_read(spi_device, ERXRDPTL));

    rt_kprintf("0x%02X    0x%02X    0x%04X\n",
               spi_read(spi_device, ERXFCON),
               spi_read(spi_device, EPKTCNT),
               (spi_read(spi_device, MAMXFLH) << 8) | spi_read(spi_device, MAMXFLL));

    rt_kprintf("Tx   : ETXST  ETXND  MACLCON1 MACLCON2 MAPHSUP\n");
    rt_kprintf("       0x%04X 0x%04X 0x%02X     0x%02X     0x%02X\n",
               (spi_read(spi_device, ETXSTH) << 8) | spi_read(spi_device, ETXSTL),
               (spi_read(spi_device, ETXNDH) << 8) | spi_read(spi_device, ETXNDL),
               spi_read(spi_device, MACLCON1),
               spi_read(spi_device, MACLCON2),
               spi_read(spi_device, MAPHSUP));

    rt_kprintf("PHY   : PHCON1 PHSTAT1\r\n");
    rt_kprintf("        0x%04X 0x%04X\r\n",
               enc28j60_phy_read(spi_device, PHCON1),
               enc28j60_phy_read(spi_device, PHSTAT1));

    enc28j60_unlock(&enc28j60_dev);
}
FINSH_FUNCTION_EXPORT(enc28j60, dump enc28j60 registers);
#endif
