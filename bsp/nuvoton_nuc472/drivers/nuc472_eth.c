/*
 * Copyright (c) 2013 Nuvoton Technology Corp.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 * Description:   NUC472 MAC driver source file
 */

#include <rtconfig.h>

#ifdef RT_USING_LWIP
#include <rtthread.h>
#include "nuc472_eth.h"
#include <netif/ethernetif.h>
#include <netif/etharp.h>
#include <lwip/icmp.h>
#include "lwipopts.h"

#define ETH_TRIGGER_RX()    EMAC->RXST = 0
#define ETH_TRIGGER_TX()    EMAC->TXST = 0
#define ETH_ENABLE_TX()     EMAC->CTL |= EMAC_CTL_TXON
#define ETH_ENABLE_RX()     EMAC->CTL |= EMAC_CTL_RXON
#define ETH_DISABLE_TX()    EMAC->CTL &= ~EMAC_CTL_TXON
#define ETH_DISABLE_RX()    EMAC->CTL &= ~EMAC_CTL_RXON
   
rt_uint8_t ethaddr[] = {0x00, 0x00, 0x00, 0x59, 0x16, 0x88};

struct rt_nuc472_emac
{
    struct eth_device parent;

    EMAC_T *emac_base;

    rt_uint8_t dev_addr[6];
    struct eth_descriptor volatile *cur_tx_desc_ptr, *cur_rx_desc_ptr, *fin_tx_desc_ptr;

    struct eth_descriptor rx_desc[RX_DESCRIPTOR_NUM];
    struct eth_descriptor tx_desc[TX_DESCRIPTOR_NUM];
    rt_uint8_t rx_buf[RX_DESCRIPTOR_NUM][PACKET_BUFFER_SIZE];
    rt_uint8_t tx_buf[TX_DESCRIPTOR_NUM][PACKET_BUFFER_SIZE];      
};
typedef struct rt_nuc472_emac* rt_nuc472_emac_t;
struct rt_nuc472_emac nuc472_emac_device;

static void mdio_write(rt_nuc472_emac_t emac, rt_uint8_t addr, rt_uint8_t reg, rt_uint16_t val)
{
    EMAC_T *emac_base = emac->emac_base;

    emac_base->MIIMDAT = val;
    emac_base->MIIMCTL = (addr << EMAC_MIIMCTL_PHYADDR_Pos) | reg | EMAC_MIIMCTL_BUSY_Msk | EMAC_MIIMCTL_WRITE_Msk | EMAC_MIIMCTL_MDCON_Msk;

    while (emac_base->MIIMCTL & EMAC_MIIMCTL_BUSY_Msk);

}

static rt_uint16_t mdio_read(rt_nuc472_emac_t emac, rt_uint8_t addr, rt_uint8_t reg)
{
    EMAC_T *emac_base = emac->emac_base;

    emac_base->MIIMCTL = (addr << EMAC_MIIMCTL_PHYADDR_Pos) | reg | EMAC_MIIMCTL_BUSY_Msk | EMAC_MIIMCTL_MDCON_Msk;
    while (emac_base->MIIMCTL & EMAC_MIIMCTL_BUSY_Msk);

    return(emac_base->MIIMDAT);
}

static int reset_phy(rt_nuc472_emac_t emac)
{
    rt_uint16_t reg;
    rt_uint32_t delay;
    EMAC_T *emac_base = emac->emac_base;

    mdio_write(emac, CONFIG_PHY_ADDR, MII_BMCR, BMCR_RESET);

    delay = 2000;
    while(delay-- > 0) 
    {
        if((mdio_read(emac, CONFIG_PHY_ADDR, MII_BMCR) & BMCR_RESET) == 0)
            break;
    }

    if(delay == 0) 
    {
        rt_kprintf("Reset phy failed\n");
        return(-1);
    }

    mdio_write(emac, CONFIG_PHY_ADDR, MII_ADVERTISE, ADVERTISE_CSMA |
               ADVERTISE_10HALF |
               ADVERTISE_10FULL |
               ADVERTISE_100HALF |
               ADVERTISE_100FULL);

    reg = mdio_read(emac, CONFIG_PHY_ADDR, MII_BMCR);
    mdio_write(emac, CONFIG_PHY_ADDR, MII_BMCR, reg | BMCR_ANRESTART);

    delay = 200000;
    while(delay-- > 0) 
    {
        if((mdio_read(emac, CONFIG_PHY_ADDR, MII_BMSR) & (BMSR_ANEGCOMPLETE | BMSR_LSTATUS))
                == (BMSR_ANEGCOMPLETE | BMSR_LSTATUS))
            break;
    }

    if(delay == 0) 
    {
        rt_kprintf("AN failed. Set to 100 FULL\n");
        emac_base->CTL |= (EMAC_CTL_OPMODE_Msk | EMAC_CTL_FUDUP_Msk);
        return(-1);
    } 
    else 
    {
        reg = mdio_read(emac, CONFIG_PHY_ADDR, MII_LPA);

        if(reg & ADVERTISE_100FULL) 
        {
            rt_kprintf("100 full\n");
            emac_base->CTL |= (EMAC_CTL_OPMODE_Msk | EMAC_CTL_FUDUP_Msk);
        }
        else if(reg & ADVERTISE_100HALF) 
        {
            rt_kprintf("100 half\n");
            emac_base->CTL = (EMAC->CTL & ~EMAC_CTL_FUDUP_Msk) | EMAC_CTL_OPMODE_Msk;
        } 
        else if(reg & ADVERTISE_10FULL) 
        {
            rt_kprintf("10 full\n");
            emac_base->CTL = (EMAC->CTL & ~EMAC_CTL_OPMODE_Msk) | EMAC_CTL_FUDUP_Msk;
        } else 
        {
            rt_kprintf("10 half\n");
            emac_base->CTL &= ~(EMAC_CTL_OPMODE_Msk | EMAC_CTL_FUDUP_Msk);
        }
    }

    return(0);
}

static void init_tx_desc(rt_nuc472_emac_t emac)
{
    EMAC_T *emac_base = emac->emac_base;
    rt_uint32_t i;

    emac->cur_tx_desc_ptr = emac->fin_tx_desc_ptr = &emac->tx_desc[0];

    for(i = 0; i < TX_DESCRIPTOR_NUM; i++) 
    {
        emac->tx_desc[i].status1 = TXFD_PADEN | TXFD_CRCAPP | TXFD_INTEN;
        emac->tx_desc[i].buf = &emac->tx_buf[i][0];
        emac->tx_desc[i].status2 = 0;
        emac->tx_desc[i].next = &emac->tx_desc[(i + 1) % TX_DESCRIPTOR_NUM];
    }
    emac_base->TXDSA = (unsigned int)&emac->tx_desc[0];
    return;
}

static void init_rx_desc(rt_nuc472_emac_t emac)
{
    EMAC_T *emac_base = emac->emac_base;
    rt_uint32_t i;

    emac->cur_rx_desc_ptr = &emac->rx_desc[0];

    for(i = 0; i < RX_DESCRIPTOR_NUM; i++)
    {
        emac->rx_desc[i].status1 = OWNERSHIP_EMAC;
        emac->rx_desc[i].buf = &emac->rx_buf[i][0];
        emac->rx_desc[i].status2 = 0;
        emac->rx_desc[i].next = &emac->rx_desc[(i + 1) % RX_DESCRIPTOR_NUM];
    }
    emac_base->RXDSA = (unsigned int)&emac->rx_desc[0];
    return;
}

static void set_mac_addr(rt_nuc472_emac_t emac, rt_uint8_t *addr)
{
    EMAC_T *emac_base = emac->emac_base;

    emac_base->CAM0M = (addr[0] << 24) |
                  (addr[1] << 16) |
                  (addr[2] << 8) |
                  addr[3];

    emac_base->CAM0L = (addr[4] << 24) |
                  (addr[5] << 16);

    emac_base->CAMCTL = EMAC_CAMCTL_CMPEN_Msk | EMAC_CAMCTL_AMP_Msk | EMAC_CAMCTL_ABP_Msk;
    emac_base->CAMEN = 1;    // Enable CAM entry 0
}

void EMAC_init(rt_nuc472_emac_t emac, rt_uint8_t *mac_addr)
{
    EMAC_T *emac_base = emac->emac_base;  
    RT_ASSERT(emac->dev_addr != RT_NULL);

    CLK_EnableModuleClock(EMAC_MODULE);

    // Configure MDC clock rate to HCLK / (127 + 1) = 656 kHz if system is running at 84 MHz
    CLK_SetModuleClock(EMAC_MODULE, 0, CLK_CLKDIV3_EMAC(127));

    // Configure RMII pins
    SYS->GPC_MFPL = SYS_GPC_MFPL_PC0MFP_EMAC_REFCLK |
                    SYS_GPC_MFPL_PC1MFP_EMAC_MII_RXERR |
                    SYS_GPC_MFPL_PC2MFP_EMAC_MII_RXDV |
                    SYS_GPC_MFPL_PC3MFP_EMAC_MII_RXD1 |
                    SYS_GPC_MFPL_PC4MFP_EMAC_MII_RXD0 |
                    SYS_GPC_MFPL_PC6MFP_EMAC_MII_TXD0 |
                    SYS_GPC_MFPL_PC7MFP_EMAC_MII_TXD1;

    SYS->GPC_MFPH = SYS_GPC_MFPH_PC8MFP_EMAC_MII_TXEN;
    // Enable high slew rate on all RMII pins
    PC->SLEWCTL |= 0x1DF;

    // Configure MDC, MDIO at PB14 & PB15
    SYS->GPB_MFPH = SYS_GPB_MFPH_PB14MFP_EMAC_MII_MDC | SYS_GPB_MFPH_PB15MFP_EMAC_MII_MDIO;
  
    // Reset MAC
    emac_base->CTL = EMAC_CTL_RST_Msk;

    init_tx_desc(emac);
    init_rx_desc(emac);

    set_mac_addr(emac, mac_addr);  // need to reconfigure hardware address 'cos we just RESET emc...
    reset_phy(emac);

    emac_base->CTL |= EMAC_CTL_STRIPCRC_Msk | EMAC_CTL_RXON_Msk | EMAC_CTL_TXON_Msk | EMAC_CTL_RMIIEN_Msk | EMAC_CTL_RMIIRXCTL_Msk;
    emac_base->INTEN |= EMAC_INTEN_RXIEN_Msk |
                   EMAC_INTEN_RXGDIEN_Msk |
                   EMAC_INTEN_RDUIEN_Msk |
                   EMAC_INTEN_RXBEIEN_Msk |
                   EMAC_INTEN_TXIEN_Msk |
                   EMAC_INTEN_TXABTIEN_Msk |
                   EMAC_INTEN_TXCPIEN_Msk |
                   EMAC_INTEN_TXBEIEN_Msk;
    emac_base->RXST = 0;  // trigger Rx
    
    //NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
    NVIC_SetPriority(EMAC_TX_IRQn, 0);
    NVIC_EnableIRQ(EMAC_TX_IRQn);
    NVIC_SetPriority(EMAC_RX_IRQn, 1);
    NVIC_EnableIRQ(EMAC_RX_IRQn);
}

void  ETH_halt(rt_nuc472_emac_t emac)
{
    EMAC_T *emac_base = emac->emac_base;

    emac_base->CTL &= ~(EMAC_CTL_RXON_Msk | EMAC_CTL_TXON_Msk);
}

void emac_emac_done(rt_nuc472_emac_t emac)
{
    EMAC_T *emac_base = emac->emac_base;
    unsigned int status;

    status = emac_base->INTSTS & 0xFFFF0000;
    emac_base->INTSTS = status;
    if(status & EMAC_INTSTS_TSALMIF_Msk)
    {
        // TODO: time stamp alarm. write me!!
    }
    if(status & EMAC_INTSTS_TXBEIF_Msk) 
    {
        // Shouldn't goes here, unless descriptor corrupted
        return;
    }
}

rt_uint8_t *emac_get_tx_buf(rt_nuc472_emac_t emac)
{
    if(emac->cur_tx_desc_ptr->status1 & OWNERSHIP_EMAC)
    {
        return(RT_NULL);
    }
    else
    {
        return(emac->cur_tx_desc_ptr->buf);
    }
}

void ETH_trigger_tx(rt_nuc472_emac_t emac, rt_uint16_t length)
{
    struct eth_descriptor volatile *desc;
    
    emac->cur_tx_desc_ptr->status2 = (unsigned int)length;
    desc = emac->cur_tx_desc_ptr->next;    // in case TX is transmitting and overwrite next pointer before we can update cur_tx_desc_ptr
    emac->cur_tx_desc_ptr->status1 |= OWNERSHIP_EMAC;
    emac->cur_tx_desc_ptr = desc;
    
    ETH_TRIGGER_TX();
}

/*
 * NUC472 EMAC Driver for RT-Thread
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-31     Bluebear233  first implementation
 */
void rt_nuc472_emac_tx_isr(rt_nuc472_emac_t emac)
{
    emac_emac_done(emac);
}

void rt_nuc472_emac_rx_isr(rt_nuc472_emac_t emac)
{
    EMAC_T *emac_base = emac->emac_base;
  
    unsigned int status = emac_base->INTSTS & 0xFFFF;
    emac_base->INTSTS = status;
    
    eth_device_ready(&emac->parent);
}

void EMAC_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    
    rt_nuc472_emac_tx_isr(&nuc472_emac_device);

    /* leave interrupt */
    rt_interrupt_leave();
}

void EMAC_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    
    rt_nuc472_emac_rx_isr(&nuc472_emac_device);

    /* leave interrupt */
    rt_interrupt_leave();
}

static rt_err_t rt_nuc472_emac_init(rt_device_t dev)
{
    rt_nuc472_emac_t emac = (rt_nuc472_emac_t)dev;

    EMAC_init(emac, emac->dev_addr);

#if LWIP_IPV4 && LWIP_IGMP
    netif_set_igmp_mac_filter(stm32_eth->parent.netif, igmp_mac_filter);
#endif /* LWIP_IPV4 && LWIP_IGMP */
    
    return RT_EOK;
}

static rt_err_t rt_nuc472_emac_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_nuc472_emac_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t rt_nuc472_emac_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t rt_nuc472_emac_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_nuc472_emac_control(rt_device_t dev, int cmd, void *args)
{
    rt_nuc472_emac_t emac = (rt_nuc472_emac_t)dev; 

    switch(cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if(args) rt_memcpy(args, emac->dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

rt_err_t rt_nuc472_emac_tx(rt_device_t dev, struct pbuf* p)
{
    rt_nuc472_emac_t emac = (rt_nuc472_emac_t)dev; 
    struct pbuf* q;
    rt_uint32_t offset;
    rt_uint8_t *buf = emac_get_tx_buf(emac);

    /* get free tx buffer */
    if(buf == RT_NULL)
    {
        rt_kprintf("none tx buf\n");
        return -RT_ERROR;
    }

    offset = 0;
    for (q = p; q != NULL; q = q->next)
    {
        rt_uint8_t* ptr;
        rt_uint32_t len;

        len = q->len;
        ptr = q->payload;

        /* Copy the frame to be sent into memory pointed by the current ETHERNET DMA Tx descriptor */
        while (len)
        {
            buf[offset] = *ptr;

            offset ++;
            ptr ++;
            len --;
        }
    }

    ETH_trigger_tx(emac, offset);    

    /* Return SUCCESS */
    return RT_EOK;
}

struct pbuf *rt_nuc472_emac_rx(rt_device_t dev)
{
    rt_nuc472_emac_t emac = (rt_nuc472_emac_t)dev;
    unsigned int status;
    struct pbuf* p;

    /* init p pointer */
    p = RT_NULL;

    status = emac->cur_rx_desc_ptr->status1;

    if(status & OWNERSHIP_EMAC)
    {
        goto end;
    }

    if (status & RXFD_RXGD) 
    {
            //ethernetif_input(status & 0xFFFF, cur_rx_desc_ptr->buf, cur_rx_desc_ptr->status2, (u32_t)cur_rx_desc_ptr->next);
                    /* allocate buffer */
        p = pbuf_alloc(PBUF_LINK, status & 0xFFFF, PBUF_RAM);
        if (p != RT_NULL)
        {
            const char * from;
            struct pbuf* q;

            from = (const char *)(emac->cur_rx_desc_ptr->buf);

            for (q = p; q != RT_NULL; q = q->next)
            {
                /* Copy the received frame into buffer from memory pointed by the current ETHERNET DMA Rx descriptor */
                memcpy(q->payload, from, q->len);
                from += q->len;
            }
        }
    }
        
    emac->cur_rx_desc_ptr->status1 = OWNERSHIP_EMAC;
    emac->cur_rx_desc_ptr = emac->cur_rx_desc_ptr->next;
        
    return p;
    
 end:
    ETH_TRIGGER_RX();
    
    return p;
}

static void rt_hw_nuc472_emac_register(rt_nuc472_emac_t emac, char *dev_name, EMAC_T *emac_base, rt_uint8_t *mac_addr)
{
    emac->emac_base = emac_base;

    rt_memcpy(emac->dev_addr, mac_addr, sizeof(emac->dev_addr));

    emac->parent.parent.init      = rt_nuc472_emac_init;
    emac->parent.parent.open       = rt_nuc472_emac_open;
    emac->parent.parent.close      = rt_nuc472_emac_close;
    emac->parent.parent.read       = rt_nuc472_emac_read;
    emac->parent.parent.write      = rt_nuc472_emac_write;
    emac->parent.parent.control    = rt_nuc472_emac_control;
    emac->parent.parent.user_data  = RT_NULL;

    emac->parent.eth_rx     = rt_nuc472_emac_rx;
    emac->parent.eth_tx     = rt_nuc472_emac_tx;

    /* register eth device */
    eth_device_init(&(emac->parent), dev_name);
}

void rt_hw_nuc472_emac_init(void)
{
    rt_hw_nuc472_emac_register(&nuc472_emac_device, "eh0", EMAC, ethaddr);
}

#endif
