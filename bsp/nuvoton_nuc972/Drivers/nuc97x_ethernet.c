/*
 * File      : nuc97x_ethernet.c
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */


#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_LWIP

#include <netif/ethernetif.h>
#include <netif/etharp.h>
#include <lwip/icmp.h>
#include "lwipopts.h"

#include "board.h"
#include "nuc97x_conf.h"

#include <string.h>

//#define ETH_DEBUG
//#define ETH_RX_DUMP
//#define ETH_TX_DUMP
#ifdef ETH_DEBUG
#define ETH_DBG(...)  rt_kprintf("[ETH]:"),rt_kprintf(__VA_ARGS__)
#else
#define ETH_DBG(...)
#endif /* ETH_DEBUG */

static void _delay(uint32_t dly)
{
    while(dly--);
}

static void mdio_write(ETH_Typedef *ETHx, uint8_t addr, uint8_t reg, uint16_t val)
{
    ETHx->EMACx->MIID = val;
    ETHx->EMACx->MIIDA = ((addr << 8) | reg | (MIIDA_WRITE_MSK|MIIDA_BUSY_MSK|MIIDA_MDCON_MSK));

    // wait busy flag clear
    while (ETHx->EMACx->MIIDA & MIIDA_BUSY_MSK) ;
}

static uint16_t mdio_read(ETH_Typedef *ETHx, uint8_t addr, uint8_t reg)
{
    ETHx->EMACx->MIIDA = ((addr << 8) | reg | (MIIDA_BUSY_MSK|MIIDA_MDCON_MSK));

    // wait busy flag clear
    while (ETHx->EMACx->MIIDA & MIIDA_BUSY_MSK) ;

    return (uint16_t)(ETHx->EMACx->MIID);
}

static int reset_phy(ETH_Typedef *ETHx)
{
    uint16_t reg;
    uint32_t delay;

    mdio_write(ETHx,CONFIG_PHY_ADDR, MII_BMCR, BMCR_RESET);

    delay = 2000;
    while (delay-- > 0)
    {
        if ((mdio_read(ETHx, CONFIG_PHY_ADDR, MII_BMCR) & BMCR_RESET) == 0)
            break;
    }

    if (delay == 0)
    {
        ETH_DBG("Reset phy failed\n");
        return (-1);
    }

    mdio_write(ETHx,CONFIG_PHY_ADDR, MII_ADVERTISE, ADVERTISE_CSMA
                                                       | ADVERTISE_10HALF
                                                       | ADVERTISE_10FULL
                                                       | ADVERTISE_100HALF
                                                       | ADVERTISE_100FULL);

    reg = mdio_read(ETHx,CONFIG_PHY_ADDR, MII_BMCR);
    mdio_write(ETHx,CONFIG_PHY_ADDR, MII_BMCR, reg | BMCR_ANRESTART);

    delay = 200000;
    while (delay-- > 0)
    {
        if ((mdio_read(ETHx,CONFIG_PHY_ADDR, MII_BMSR) & (BMSR_ANEGCOMPLETE | BMSR_LSTATUS)) \
                        == (BMSR_ANEGCOMPLETE | BMSR_LSTATUS))
            break;
    }

    if (delay == 0)
    {
        ETH_DBG("AN failed. Set to 100 FULL\n");
        ETHx->EMACx->MCMDR |= 0x140000;
        ETHx->plugged = 0;
        return (-1);
    }
    else
    {
        reg = mdio_read(ETHx,CONFIG_PHY_ADDR, MII_LPA);
        ETHx->plugged = 1;

        if (reg & ADVERTISE_100FULL)
        {
            ETH_DBG("100 full\n");
            ETHx->EMACx->MCMDR |= 0x140000;
        }
        else if (reg & ADVERTISE_100HALF)
        {
            ETH_DBG("100 half\n");
            ETHx->EMACx->MCMDR &= ~0x40000;
            ETHx->EMACx->MCMDR |= 0x100000;
        }
        else if (reg & ADVERTISE_10FULL)
        {
            ETH_DBG("10 full\n");
            ETHx->EMACx->MCMDR &= ~0x100000;
            ETHx->EMACx->MCMDR |= 0x40000;
        }
        else
        {
            ETH_DBG("10 half\n");
            ETHx->EMACx->MCMDR &= ~0x140000;
        }
    }

    return (0);
}

static void init_tx_desc(ETH_Typedef *ETHx)
{
    uint32_t i;

    ETHx->cur_tx_desc_ptr = ETHx->fin_tx_desc_ptr = (struct eth_tx_descriptor *)UNCACHE_BUFFER(&ETHx->tx_desc[0]);
    for (i = 0; i < TX_DESCRIPTOR_NUM; i++)
    {
        ETHx->tx_desc[i].mode   = PADDINGMODE | CRCMODE | MACTXINTEN;
        ETHx->tx_desc[i].buffer = (uint32_t)UNCACHE_BUFFER(&ETHx->tx_buf[i][0]);
        ETHx->tx_desc[i].sl     = 0;
        ETHx->tx_desc[i].next   = (struct eth_tx_descriptor *) UNCACHE_BUFFER(&ETHx->tx_desc[(i + 1) % TX_DESCRIPTOR_NUM]);

    }

    ETHx->EMACx->TXDLSA = (uint32_t)UNCACHE_BUFFER(&ETHx->tx_desc[0]);
    return;
}

static void init_rx_desc(ETH_Typedef *ETHx)
{
    uint32_t i;

    ETHx->cur_rx_desc_ptr = (struct eth_rx_descriptor *) UNCACHE_BUFFER(&ETHx->rx_desc[0]);
    for (i = 0; i < RX_DESCRIPTOR_NUM; i++)
    {
        ETHx->rx_desc[i].sl         = OWNERSHIP_EMAC;
        ETHx->rx_desc[i].buffer     = (uint32_t) UNCACHE_BUFFER(&ETHx->rx_buf[i][0]);
        ETHx->rx_desc[i].reserved   = 0;
        ETHx->rx_desc[i].next       = (struct eth_rx_descriptor *) UNCACHE_BUFFER(&ETHx->rx_desc[(i + 1) % RX_DESCRIPTOR_NUM]);

    }

    ETHx->EMACx->RXDLSA = (uint32_t) UNCACHE_BUFFER(& ETHx->rx_desc[0]);
    return;
}

static void set_mac_addr(ETH_Typedef *ETHx,uint8_t *addr)
{
    ETHx->EMACx->CAM0M = (addr[0] << 24) | (addr[1] << 16) | (addr[2] << 8) | addr[3];
    ETHx->EMACx->CAM0L = (addr[4] << 24) | (addr[5] << 16);

    ETHx->EMACx->CAMCMR = (CAMCMR_ECMP|CAMCMR_ABP|CAMCMR_AMP);

    // Enable CAM entry 0
    ETHx->EMACx->CAMEN = 1;
}


void ETH_halt(ETH_Typedef *ETHx)
{
    // disable tx/rx on
    ETHx->EMACx->MCMDR &= ~0x101;
}

void ETH_chk_link(ETH_Typedef *ETHx)
{
    uint32_t reg;

    reg = mdio_read(ETHx,CONFIG_PHY_ADDR, MII_BMSR);

    if (reg & BMSR_LSTATUS)
    {
        if (!ETHx->plugged)
        {
            ETHx->plugged = 1;

            rt_hw_interrupt_umask(ETHx->tx_vector);
            rt_hw_interrupt_umask(ETHx->rx_vector);
        }
    }
    else
    {
        if (ETHx->plugged)
        {
            ETHx->plugged = 0;
            rt_hw_interrupt_mask(ETHx->tx_vector);
            rt_hw_interrupt_mask(ETHx->rx_vector);
        }
    }
}

void ETH_init(ETH_Typedef *ETHx, uint8_t *mac_addr)
{
    if(ETHx->EMACx == EMAC0)
    {
        outpw(REG_CLK_HCLKEN, inpw(REG_CLK_HCLKEN) | (1 << 16));            // EMAC0 clk
        outpw(REG_CLK_DIVCTL8, (inpw(REG_CLK_DIVCTL8) & ~0xFF) | 0xA0);     // MDC clk divider
        _delay(0xFFFF);

        // Multi function pin setting
        outpw(REG_SYS_GPF_MFPL, 0x11111111);
        outpw(REG_SYS_GPF_MFPH, (inpw(REG_SYS_GPF_MFPH) & ~0xFF) | 0x11);
        _delay(0xFFFF);
    }
    else if(ETHx->EMACx == EMAC1)
    {
        outpw(REG_CLK_HCLKEN, inpw(REG_CLK_HCLKEN) | (1 << 17));             // EMAC1 clk
        outpw(REG_CLK_DIVCTL8, (inpw(REG_CLK_DIVCTL8) & ~0xFF) | 0xA0);     // MDC clk divider
        _delay(0xFFFF);

        // Multi function pin setting
        outpw(REG_SYS_GPE_MFPL, (inpw(REG_SYS_GPE_MFPH) & ~0xFFFFFF00) | 0x11111100);
        outpw(REG_SYS_GPE_MFPH, (inpw(REG_SYS_GPE_MFPH) & ~0xFFFF) | 0x1111);
        _delay(0xFFFF);
    }

    // Reset MAC
    ETHx->EMACx->MCMDR = MCMDR_SWR;
    _delay(0xFFFF);

    init_tx_desc(ETHx);
    init_rx_desc(ETHx);

    set_mac_addr(ETHx,mac_addr);            // need to reconfigure hardware address 'cos we just RESET emc...
    reset_phy(ETHx);
    _delay(0xFFFF);

    ETHx->EMACx->MCMDR |= (MCMDR_SPCRC | MCMDR_RXON | MCMDR_TXON);                      // strip CRC, TX on, Rx on
    ETHx->EMACx->MIEN  |= (MIEN_RXIEN | MIEN_RXGDIEN | MIEN_RDUIEN | MIEN_RXBEIEN
                         | MIEN_TXIEN | MIEN_TXCPIEN | MIEN_TXABTIEN | MIEN_TXBEIEN);   // Except tx/rx ok, enable rdu, txabt, tx/rx bus error.
    _delay(0xFFFF);
    ETH_TRIGGER_RX(ETHx->EMACx);
    _delay(0xFFFF);
}

uint8_t *ETH_get_tx_buf(ETH_Typedef *ETHx)
{
    if(ETHx->cur_tx_desc_ptr->sl & OWNERSHIP_EMAC)
        return(NULL);
    else
        return (uint8_t *)(ETHx->cur_tx_desc_ptr->buffer);
}

void ETH_start_tx(ETH_Typedef *ETHx,uint8_t * buffer,uint16_t length)
{
    rt_base_t   level;
    struct eth_tx_descriptor volatile *txdesc = ETHx->cur_tx_desc_ptr->next;

    level = rt_hw_interrupt_disable();
    ETHx->cur_tx_desc_ptr->mode |= OWNERSHIP_EMAC;
    ETHx->cur_tx_desc_ptr->sl = length;
    ETH_TRIGGER_TX(ETHx->EMACx);
    ETHx->cur_tx_desc_ptr = ETHx->cur_tx_desc_ptr->next;
    rt_hw_interrupt_enable(level);
}

void ETH_start_rx(ETH_Typedef *ETHx)
{
    rt_base_t   level;
    uint32_t status;
    do
    {
        status = ETHx->cur_rx_desc_ptr->sl;

        if (status & OWNERSHIP_EMAC)
        {
            break;
        }

        level = rt_hw_interrupt_disable();
        ETHx->cur_rx_desc_ptr->sl = OWNERSHIP_EMAC;
        ETHx->cur_rx_desc_ptr = ETHx->cur_rx_desc_ptr->next;
        rt_hw_interrupt_enable(level);
    } while (1) ;

    ETH_TRIGGER_RX(ETHx->EMACx);
}



#define MAX_ADDR_LEN        6
struct rt_nuc970_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;
    ETH_Typedef *ETHx;
    uint8_t dev_addr[6];
    struct rt_semaphore tx_buf_free;
};

#ifdef BOARD_USING_ETH0
rt_uint8_t nuc970_eth0_addr[6]= { 0x00, 0x00, 0x00, 0x51, 0x68, 0x88 } ;
static struct rt_nuc970_eth nuc970_eth0_device ;
ALIGN(32) static ETH_Typedef ETH0[1] ;
#endif

#ifdef BOARD_USING_ETH1
const uint8_t nuc970_eth1_addr[6] = { 0x00, 0x80, 0xE1, 0x59, 0x48, 0x81 };
static struct rt_nuc970_eth nuc970_eth1_device;
//static ETH_Typedef* ETH1 = (ETH_Typedef*)0xBC007000;
static ETH_Typedef* ETH1 = RT_NULL;
#endif

#if defined(ETH_RX_DUMP) ||  defined(ETH_TX_DUMP)
static void packet_dump(const char * msg, const struct pbuf* p)
{
    rt_uint32_t i;
    rt_uint8_t *ptr = p->payload;

    rt_kprintf("%s %d byte\n", msg, p->tot_len);

    for (i = 0; i < p->tot_len; i++)
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
        ptr++;
    }
    rt_kprintf("\n\n");
}
#endif /* dump */


void ETH_RX_IRQHandler(int vector,void *arg)
{
    struct rt_nuc970_eth *nuc970_eth ;
    ETH_Typedef *ETHx;
    rt_uint32_t status;

    RT_ASSERT(nuc970_eth != RT_NULL);
    nuc970_eth = (struct rt_nuc970_eth *)arg;
    ETHx = nuc970_eth->ETHx;

    /* clear status */
    status = ETHx->EMACx->MISTA & 0xFFFF;
    ETHx->EMACx->MISTA = status;

    if (status & MISTA_RXBERR)
    {
        // Shouldn't goes here, unless descriptor corrupted
        ETH_DBG("EMAC rx bus error\n");
        /* reset mac */

        return;
    }

    if (status & MISTA_RXGD)
    {
        /* Disable RX interrupt */
        ETHx->EMACx->MIEN &= ~MIEN_RXIEN;

        /* some frames has been received */
        eth_device_ready(&(nuc970_eth->parent));

        return;
    }
}


void ETH_TX_IRQHandler(int vector,void *arg)
{
    rt_base_t   level;
    struct rt_nuc970_eth *nuc970_eth = (struct rt_nuc970_eth *)arg;
    ETH_Typedef *ETHx;
    uint32_t cur_entry, status;

    RT_ASSERT(ETHx != RT_NULL);
    ETHx = nuc970_eth->ETHx;
    /* clear status */
    status = ETHx->EMACx->MISTA & 0xFFFF0000;
    ETHx->EMACx->MISTA = status;

    if (status & 0x1000000)
    {
        // Shouldn't goes here, unless descriptor corrupted
        return;
    }

    cur_entry = ETHx->EMACx->CTXDSA;
    while (cur_entry != (uint32_t) ETHx->fin_tx_desc_ptr)
    {
        level = rt_hw_interrupt_disable();
        ETHx->fin_tx_desc_ptr = ETHx->fin_tx_desc_ptr->next;
        rt_hw_interrupt_enable(level);

        rt_sem_release(&nuc970_eth->tx_buf_free);
    }

}


/* initialize the interface */
static rt_err_t rt_nuc970_eth_init(rt_device_t dev)
{
    return RT_EOK;
}
static rt_err_t rt_nuc970_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_nuc970_eth_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t rt_nuc970_eth_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t rt_nuc970_eth_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_nuc970_eth_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    struct rt_nuc970_eth *nuc970_eth_device = (struct rt_nuc970_eth *)dev;
    switch (cmd)
    {
        case NIOCTL_GADDR:
            /* get mac address */
            if (args)
                memcpy(args, nuc970_eth_device->dev_addr, 6);
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
rt_err_t rt_nuc970_eth_tx( rt_device_t dev, struct pbuf* p)
{
    struct rt_nuc970_eth *nuc970_eth = (struct rt_nuc970_eth *) dev;
    ETH_Typedef *ETHx = nuc970_eth->ETHx;

    struct pbuf* q;
    rt_uint32_t status,offset;
    rt_uint8_t *tx_buf;

    /* get free tx buffer */
    {
        rt_err_t result;

        result = rt_sem_take(&nuc970_eth->tx_buf_free, RT_WAITING_FOREVER);
        if (result != RT_EOK)
            return -RT_ERROR;
    }

    /* Clear IRQ status */
    status = ETHx->EMACx->MISTA & 0xFFFF0000;
    ETHx->EMACx->MISTA = status;

    tx_buf = (rt_uint8_t *)ETHx->cur_tx_desc_ptr->buffer;
    offset = 0;
    for (q = p; q != NULL; q = q->next)
    {
        if((offset + q->len) > PACKET_BUFFER_SIZE)
            break;
        /* Copy the frame to be sent into memory pointed by the current ETHERNET DMA Tx descriptor */
        memcpy(tx_buf + offset,q->payload,q->len);
        offset += q->len;
    }

#ifdef ETH_TX_DUMP
    packet_dump("TX dump", p);
#endif

    ETH_start_tx(ETHx, RT_NULL, offset);

    /* Return SUCCESS */
    return RT_EOK;
}

/* reception packet. */
struct pbuf *rt_nuc970_eth_rx(rt_device_t dev)
{
    rt_base_t level;
    struct rt_nuc970_eth *nuc970_eth = (struct rt_nuc970_eth *) dev;
    ETH_Typedef *ETHx = nuc970_eth->ETHx;

    struct pbuf* p = RT_NULL;

    ETH_DBG("%d cur_rx_ptr = %08x,CRXDSA = %08x\n",__LINE__,(rt_uint32_t)ETHx->cur_rx_desc_ptr,ETHx->EMACx->CRXDSA);

    while ((uint32_t)ETHx->cur_rx_desc_ptr != ETHx->EMACx->CRXDSA)
    {
        rt_uint32_t status = 0;
        rt_uint32_t len = 0;

        status = ETHx->cur_rx_desc_ptr->sl;

        if((status & OWNERSHIP_EMAC) == OWNERSHIP_EMAC)
        {
            level = rt_hw_interrupt_disable();
            ETHx->cur_rx_desc_ptr->sl   = OWNERSHIP_EMAC;
            ETHx->cur_rx_desc_ptr       = ETHx->cur_rx_desc_ptr->next;
            rt_hw_interrupt_enable(level);
            continue;
        }

        if (status & RXDS_RXGD)
        {
            rt_uint8_t* from;
            struct pbuf* q;

            /* Get the Frame Length of the received packet: substruct 4 bytes of the CRC */
            len = status & 0xFFFF;

            /* allocate buffer */
            p = pbuf_alloc(PBUF_LINK, len, PBUF_RAM);
            if (p != RT_NULL)
            {
                from = (rt_uint8_t *) (ETHx->cur_rx_desc_ptr->buffer);
//                rt_hw_dcache_flush_range((rt_uint32_t)from ,(rt_uint32_t)from + PACKET_BUFFER_SIZE);

//                pbuf_take(p,from,len);
                for (q = p; q != RT_NULL; q = q->next)
                {
                    /* Copy the received frame into buffer from memory pointed by the current ETHERNET DMA Rx descriptor */
                    //memcpy((void *)((rt_uint32_t)q->payload | UNCACHE_MASK), from, q->len);
                    memcpy(q->payload, from, q->len);
                    from += q->len;
                }

#ifdef ETH_RX_DUMP
                packet_dump("RX dump", p);
#endif /* ETH_RX_DUMP */

                level = rt_hw_interrupt_disable();
                ETHx->cur_rx_desc_ptr->sl = OWNERSHIP_EMAC;
                ETHx->cur_rx_desc_ptr = ETHx->cur_rx_desc_ptr->next;
                rt_hw_interrupt_enable(level);
                return p;
            }
        }

        ETH_DBG("NO PBUF\n");
        level = rt_hw_interrupt_disable();
        ETHx->cur_rx_desc_ptr->sl   = OWNERSHIP_EMAC;
        ETHx->cur_rx_desc_ptr       = ETHx->cur_rx_desc_ptr->next;
        rt_hw_interrupt_enable(level);
    }

    ETH_DBG("%d cur_rx_ptr = %08x,CRXDSA = %08x\n",__LINE__,(rt_uint32_t)ETHx->cur_rx_desc_ptr,ETHx->EMACx->CRXDSA);

    //re-init cur_rx_desc_ptr->sl
    level = rt_hw_interrupt_disable();
    ETHx->cur_rx_desc_ptr->sl   = OWNERSHIP_EMAC;
    rt_hw_interrupt_enable(level);

    //Start RX and Enable RX interrupt
    ETH_TRIGGER_RX(ETHx->EMACx);
    ETHx->EMACx->MIEN |= MIEN_RXIEN;

    rt_thread_delay(1);
    return RT_NULL;
}

int rt_hw_nuc970_eth_init(void)
{
    struct rt_nuc970_eth *nuc970_eth_device;
    static ETH_Typedef* ETHx;
#ifdef BOARD_USING_ETH0
    rt_kprintf("ETH0 init ....\n");

    ETHx = ETH0;
    ETHx->EMACx     = EMAC0;
    ETHx->plugged   = 0;
    ETHx->tx_vector = EMC0_TX_IRQn;
    ETHx->rx_vector = EMC0_RX_IRQn;

    nuc970_eth_device = &nuc970_eth0_device;

    nuc970_eth_device->ETHx = ETHx;
    memcpy(nuc970_eth_device->dev_addr,nuc970_eth0_addr,sizeof(nuc970_eth0_addr));

    ETH_init(nuc970_eth_device->ETHx,nuc970_eth_device->dev_addr);

    /* RT ETH device interface init */
    nuc970_eth_device->parent.parent.init       = rt_nuc970_eth_init;
    nuc970_eth_device->parent.parent.open       = rt_nuc970_eth_open;
    nuc970_eth_device->parent.parent.close      = rt_nuc970_eth_close;
    nuc970_eth_device->parent.parent.read       = rt_nuc970_eth_read;
    nuc970_eth_device->parent.parent.write      = rt_nuc970_eth_write;
    nuc970_eth_device->parent.parent.control    = rt_nuc970_eth_control;
    nuc970_eth_device->parent.parent.user_data  = RT_NULL;

    nuc970_eth_device->parent.eth_rx            = rt_nuc970_eth_rx;
    nuc970_eth_device->parent.eth_tx            = rt_nuc970_eth_tx;

    /* init tx buffer free semaphore */
    rt_sem_init(&nuc970_eth_device->tx_buf_free,
                "e0txsem",
                TX_DESCRIPTOR_NUM,
                RT_IPC_FLAG_FIFO);

    /* register eth device */
    eth_device_init(&(nuc970_eth_device->parent), "e0");
    /* register interrupt */
    rt_hw_interrupt_install(nuc970_eth_device->ETHx->tx_vector,ETH_TX_IRQHandler,nuc970_eth_device,"e0txisr");
    rt_hw_interrupt_set_priority(nuc970_eth_device->ETHx->tx_vector,IRQ_LEVEL_1);
    rt_hw_interrupt_umask(nuc970_eth_device->ETHx->tx_vector);

    rt_hw_interrupt_install(nuc970_eth_device->ETHx->rx_vector,ETH_RX_IRQHandler,nuc970_eth_device,"e0rxisr");
    rt_hw_interrupt_set_priority(nuc970_eth_device->ETHx->rx_vector,IRQ_LEVEL_1);
    rt_hw_interrupt_umask(nuc970_eth_device->ETHx->rx_vector);

#endif

#ifdef BOARD_USING_ETH1
    ETH_init(&nuc970_eth1_device.ETHx,nuc970_eth1_device.dev_addr);

    /* init tx buffer free semaphore */
    rt_sem_init(&nuc970_eth1_device.tx_buf_free, "eth1_tx", TX_DESCRIPTOR_NUM, RT_IPC_FLAG_FIFO);

    /* register eth device */
    eth_device_init(&(nuc970_eth1_device.parent), "e1");

    /* register interrupt */
    rt_hw_interrupt_install(nuc970_eth1_device.ETHx.tx_vector,ETH_TX_IRQHandler,&nuc970_eth1_device,"e1txisr");
    rt_hw_interrupt_set_priority(nuc970_eth1_device.ETHx.tx_vector,IRQ_LEVEL_1);
    rt_hw_interrupt_umask(nuc970_eth1_device.ETHx.tx_vector);

    rt_hw_interrupt_install(nuc970_eth1_device.ETHx.rx_vector,ETH_RX_IRQHandler,&nuc970_eth1_device,"e1rxisr");
    rt_hw_interrupt_set_priority(nuc970_eth1_device.ETHx.rx_vector,IRQ_LEVEL_1);
    rt_hw_interrupt_umask(nuc970_eth1_device.ETHx.rx_vector);
#endif
    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_nuc970_eth_init);


void hw_eth_link_check_entry(void)
{
#ifdef BOARD_USING_ETH0
    int lastPlugged = 0;
#endif

#ifdef BOARD_USING_ETH0
        ETH_chk_link(ETH0);
        if(ETH0->plugged == 1)
        {
            eth_device_linkchange(&nuc970_eth0_device.parent,RT_TRUE);
        }
        else
        {
            eth_device_linkchange(&nuc970_eth0_device.parent,RT_FALSE);
        }
#endif

#ifdef BOARD_USING_ETH1
        ETH_chk_link(ETH1);
        if(ETH0->plugged == 1)
        {
            eth_device_linkchange(&nuc970_eth1_device.parent,RT_TRUE);
        }
#endif

    while(1)
    {
        rt_thread_delay(RT_TICK_PER_SECOND / 2);
#ifdef BOARD_USING_ETH0
        lastPlugged = ETH0->plugged;        //save
        ETH_chk_link(ETH0);
        if(lastPlugged != ETH0->plugged)
        {
            if(ETH0->plugged == 1)
            {
                eth_device_linkchange(&nuc970_eth0_device.parent,RT_TRUE);

                rt_kprintf("link up..\n");
            }
            else
            {
                eth_device_linkchange(&nuc970_eth0_device.parent,RT_FALSE);
                rt_kprintf("link down..\n");
            }
        }
#endif

#ifdef BOARD_USING_ETH1
        lastPlugged = ETH1->plugged;        //save
        ETH_chk_link(ETH1);
        if(lastPlugged != ETH1->plugged)
        {
            if(ETH1->plugged == 1)
            {
                eth_device_linkchange(&nuc970_eth1_device.parent,RT_TRUE);
            }
            else
            {
                eth_device_linkchange(&nuc970_eth1_device.parent,RT_FALSE);
            }
        }
#endif
    }
}
int hw_eth_link_check_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("linkCheck",
                           hw_eth_link_check_entry, RT_NULL,
                           1024,
                           RT_THREAD_PRIORITY_MAX - 3,
                           10);
    if (tid != RT_NULL)
        rt_thread_startup(tid);
}
INIT_ENV_EXPORT(hw_eth_link_check_init);
#endif
