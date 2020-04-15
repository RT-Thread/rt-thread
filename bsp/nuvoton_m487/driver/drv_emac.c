/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-1-20      bluebear233  first version
 */

#include <rtthread.h>

#ifdef RT_USING_LWIP
#include "NuMicro.h"
#include "drv_emac.h"
#include <netif/ethernetif.h>
#include <netif/etharp.h>
#include <lwip/icmp.h>
#include "lwipopts.h"

#define ETH_DEBUG
//#define ETH_RX_DUMP
//#define ETH_TX_DUMP

#ifdef ETH_DEBUG
#define ETH_TRACE         rt_kprintf
#else
#define ETH_TRACE(...)
#endif /* ETH_DEBUG */


#if defined(ETH_RX_DUMP) ||  defined(ETH_TX_DUMP)
static void packet_dump(const char * msg, const struct pbuf* p)
{
    rt_uint32_t i;
    rt_uint8_t *ptr = p->payload;

    ETH_TRACE("%s %d byte\n", msg, p->tot_len);

    for(i=0; i<p->tot_len; i++)
    {
        if( (i%8) == 0 )
        {
            ETH_TRACE("  ");
        }
        if( (i%16) == 0 )
        {
            ETH_TRACE("\r\n");
        }
        ETH_TRACE("%02x ",*ptr);
        ptr++;
    }
    ETH_TRACE("\n\n");
}
#endif /* dump */

#define ETH_TRIGGER_RX()    EMAC->RXST = 0
#define ETH_TRIGGER_TX()    EMAC->TXST = 0
#define ETH_ENABLE_TX()     EMAC->CTL |= EMAC_CTL_TXON
#define ETH_ENABLE_RX()     EMAC->CTL |= EMAC_CTL_RXON
#define ETH_DISABLE_TX()    EMAC->CTL &= ~EMAC_CTL_TXON
#define ETH_DISABLE_RX()    EMAC->CTL &= ~EMAC_CTL_RXON

#define EMAC_DMARXDESC_CRCEIF_Msk (1ul << 17)

#define ETH_TID_STACK 256

static rt_uint8_t volatile phy_speed = 0;
static rt_uint8_t eth_addr[6];
static struct eth_device eth;
static struct rt_semaphore eth_sem;
static struct rt_thread eth_tid;
static rt_uint32_t eth_stack[ETH_TID_STACK / 4];
static struct eth_descriptor volatile *cur_tx_desc_ptr, *cur_rx_desc_ptr, *fin_tx_desc_ptr;
static struct eth_descriptor rx_desc[RX_DESCRIPTOR_NUM];
static struct eth_descriptor tx_desc[TX_DESCRIPTOR_NUM];

static rt_uint32_t rx_buf[RX_DESCRIPTOR_NUM][PACKET_BUFFER_SIZE];
static rt_uint32_t tx_buf[TX_DESCRIPTOR_NUM][PACKET_BUFFER_SIZE];


static void mdio_write(rt_uint8_t addr, rt_uint8_t reg, rt_uint16_t val)
{
    EMAC->MIIMDAT = val;
    EMAC->MIIMCTL = (addr << EMAC_MIIMCTL_PHYADDR_Pos) | reg | EMAC_MIIMCTL_BUSY_Msk | EMAC_MIIMCTL_WRITE_Msk | EMAC_MIIMCTL_MDCON_Msk;

    while (EMAC->MIIMCTL & EMAC_MIIMCTL_BUSY_Msk);
}

static rt_uint16_t mdio_read(rt_uint8_t addr, rt_uint8_t reg)
{
    EMAC->MIIMCTL = (addr << EMAC_MIIMCTL_PHYADDR_Pos) | reg | EMAC_MIIMCTL_BUSY_Msk | EMAC_MIIMCTL_MDCON_Msk;
    while (EMAC->MIIMCTL & EMAC_MIIMCTL_BUSY_Msk);

    return EMAC->MIIMDAT;
}

static void init_tx_desc(void)
{
    rt_uint32_t i;

    cur_tx_desc_ptr = fin_tx_desc_ptr = &tx_desc[0];

    for(i = 0; i < TX_DESCRIPTOR_NUM; i++) 
    {
        tx_desc[i].status1 = TXFD_PADEN | TXFD_CRCAPP | TXFD_INTEN;
        tx_desc[i].buf = (rt_uint8_t*)tx_buf[i];
        tx_desc[i].status2 = 0;
        tx_desc[i].next = &tx_desc[(i + 1) % TX_DESCRIPTOR_NUM];
    }
    EMAC->TXDSA = (unsigned int)&tx_desc[0];
    return;
}

static void init_rx_desc(void)
{
    rt_uint32_t i;

    cur_rx_desc_ptr = &rx_desc[0];

    for(i = 0; i < RX_DESCRIPTOR_NUM; i++)
    {
        rx_desc[i].status1 = OWNERSHIP_EMAC;
        rx_desc[i].buf = (rt_uint8_t*)rx_buf[i];
        rx_desc[i].status2 = 0;
        rx_desc[i].next = &rx_desc[(i + 1) % RX_DESCRIPTOR_NUM];
    }
    EMAC->RXDSA = (unsigned int)&rx_desc[0];
    return;
}

static void add_mac_addr(const rt_uint8_t *addr)
{
    rt_uint32_t *EMAC_CAMxM;
    rt_uint32_t *EMAC_CAMxL;
    rt_uint8_t index = 0;
    rt_uint8_t mac[6];

    for(; index < 13; index ++)
    {
        EMAC_CAMxM = (rt_uint32_t *)((rt_uint32_t)&EMAC->CAM0M + (index * 8));
        EMAC_CAMxL = (rt_uint32_t *)((rt_uint32_t)&EMAC->CAM0L + (index * 8));

        mac[0] = (*EMAC_CAMxM >> 24) & 0xff;
        mac[1] = (*EMAC_CAMxM >> 16) & 0xff;
        mac[2] = (*EMAC_CAMxM >> 8) & 0xff;
        mac[3] = (*EMAC_CAMxM) & 0xff;
        mac[4] = (*EMAC_CAMxL >> 24) & 0xff;
        mac[5] = (*EMAC_CAMxL >> 16) & 0xff;

        if(memcmp(mac, addr, sizeof(mac)) == 0)
        {
            return;
        }

        if(*EMAC_CAMxM == 0 && *EMAC_CAMxL == 0)
        {
            break;
        }
    }

    RT_ASSERT(index < 13)

    *EMAC_CAMxM  = (addr[0] << 24) |
                  (addr[1] << 16) |
                  (addr[2] << 8) |
                  addr[3];

    *EMAC_CAMxL = (addr[4] << 24) |
                  (addr[5] << 16);

    EMAC->CAMEN |= (1 << index);
}

void EMAC_init()
{
    // Reset MAC
    EMAC->CTL = EMAC_CTL_RST_Msk;
    while(EMAC->CTL & EMAC_CTL_RST_Msk);

    init_tx_desc();
    init_rx_desc();

    EMAC->CAMCTL = EMAC_CAMCTL_CMPEN_Msk | EMAC_CAMCTL_ABP_Msk;
    add_mac_addr(eth_addr);

    EMAC->CTL |= EMAC_CTL_STRIPCRC_Msk | EMAC_CTL_RXON_Msk | EMAC_CTL_TXON_Msk | EMAC_CTL_RMIIEN_Msk;
    EMAC->INTEN = EMAC_INTEN_RXIEN_Msk |
                   EMAC_INTEN_RXGDIEN_Msk |
                   EMAC_INTEN_RDUIEN_Msk |
                   EMAC_INTEN_RXBEIEN_Msk |
                   EMAC_INTEN_TXIEN_Msk |
                   EMAC_INTEN_TXBEIEN_Msk;

    /* Limit the max receive frame length to 1514 + 4 */
    EMAC->MRFL = PACKET_BUFFER_SIZE;
    EMAC->RXST = 0;  // trigger Rx
}

void EMAC_Reinit(void)
{
    rt_uint32_t EMAC_CAMxM[13];
    rt_uint32_t EMAC_CAMxL[13];
    rt_uint32_t EMAC_CAMEN;

    EMAC_CAMEN = EMAC->CAMEN;
    for(rt_uint8_t index = 0 ; index < 13; index ++)
    {
        rt_uint32_t *CAMxM = (rt_uint32_t *)((rt_uint32_t)&EMAC->CAM0M + (index * 8));
        rt_uint32_t *CAMxL = (rt_uint32_t *)((rt_uint32_t)&EMAC->CAM0L + (index * 8));

        EMAC_CAMxM[index] = *CAMxM;
        EMAC_CAMxL[index] = *CAMxL;
    }

    EMAC_init();

    for(rt_uint8_t index = 0 ; index < 13; index ++)
    {
        rt_uint32_t *CAMxM = (rt_uint32_t *)((rt_uint32_t)&EMAC->CAM0M + (index * 8));
        rt_uint32_t *CAMxL = (rt_uint32_t *)((rt_uint32_t)&EMAC->CAM0L + (index * 8));

        *CAMxM = EMAC_CAMxM[index];
        *CAMxL = EMAC_CAMxL[index];
    }
    EMAC->CAMEN = EMAC_CAMEN;

    phy_speed = 0;
}

void ETH_halt(void)
{
    EMAC->CTL &= ~(EMAC_CTL_RXON_Msk | EMAC_CTL_TXON_Msk);
}

__inline static rt_uint8_t *emac_get_tx_buf(void)
{
    if(cur_tx_desc_ptr->status1 & OWNERSHIP_EMAC)
    {
        return(RT_NULL);
    }
    else
    {
        return(cur_tx_desc_ptr->buf);
    }
}

__inline static void ETH_trigger_tx(rt_uint16_t length)
{
    struct eth_descriptor volatile *desc;
    
    cur_tx_desc_ptr->status2 = (unsigned int)length;
    desc = cur_tx_desc_ptr->next;    // in case TX is transmitting and overwrite next pointer before we can update cur_tx_desc_ptr
    cur_tx_desc_ptr->status1 |= OWNERSHIP_EMAC;
    cur_tx_desc_ptr = desc;
}

#if LWIP_IPV4 && LWIP_IGMP
static err_t igmp_mac_filter( struct netif *netif, const ip4_addr_t *ip4_addr, u8_t action )
{
    rt_uint8_t mac[6];
    const uint8_t *p = (const uint8_t *)ip4_addr;

    mac[0] = 0x01;
    mac[1] = 0x00;
    mac[2] = 0x5E;
    mac[3] = *(p+1) & 0x7F;
    mac[4] = *(p+2);
    mac[5] = *(p+3);

    add_mac_addr(mac);

    if(1)
    {
        rt_kprintf("%s %s %s ", __FUNCTION__, (action==NETIF_ADD_MAC_FILTER)?"add":"del", ip4addr_ntoa(ip4_addr));
        rt_kprintf("%02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    }

    return 0;
}
#endif /* LWIP_IPV4 && LWIP_IGMP */

/*
 * M480 EMAC Driver for RT-Thread
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-31     Bluebear233  first implementation
 */
void EMAC_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    
    unsigned int status = EMAC->INTSTS;

    if(status & EMAC_INTSTS_RDUIF_Msk)
    {
        EMAC->INTEN &= ~(EMAC_INTEN_RDUIEN_Msk | EMAC_INTEN_RXGDIEN_Msk);
        eth_device_ready(&eth);
    }
    else if(status & EMAC_INTSTS_RXGDIF_Msk)
    {
        EMAC->INTEN &= ~EMAC_INTEN_RXGDIEN_Msk;
        eth_device_ready(&eth);
    }

    if(status & EMAC_INTSTS_RXBEIF_Msk)
    {
        ETH_TRACE("Reinit Rx EMAC\n");
        EMAC->INTSTS = EMAC_INTSTS_RXBEIF_Msk;
        EMAC_Reinit();
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

void EMAC_TX_IRQHandler(void)
{
    rt_interrupt_enter();

    unsigned int status = EMAC->INTSTS;

    if(status & EMAC_INTSTS_TXCPIF_Msk)
    {
        EMAC->INTEN &= ~EMAC_INTEN_TXCPIEN_Msk;
        rt_sem_release(&eth_sem);
    }

    if(status & EMAC_INTSTS_TXBEIF_Msk)
    {
        ETH_TRACE("Reinit Tx EMAC\n");
        EMAC->INTSTS = EMAC_INTSTS_TXBEIF_Msk;
        EMAC_Reinit();
    }

    rt_interrupt_leave();
}

#define PHY_LINK_MASK       (1<<0)
#define PHY_10FULL_MASK     (1<<1)
#define PHY_100FULL_MASK    (1<<2)
#define PHY_10HALF_MASK     (1<<3)
#define PHY_100HALF_MASK    (1<<4)

#define PHY_ANLPA_DR100_TX_FULL   (1UL << 8UL)
#define PHY_ANLPA_DR100_TX_HALF   (1UL << 7UL)
#define PHY_ANLPA_DR10_TX_FULL    (1UL << 6UL)
#define PHY_ANLPA_DR10_TX_HALF    (1UL << 5UL)

void eth_entry(void *param)
{
    uint8_t phy_addr = 0xFF;
    uint8_t phy_speed_new = 0;

    /* phy search */
    {
        rt_uint32_t i;
        rt_uint16_t temp;

        for(i=0; i<=0x1F; i++)
        {
            temp = mdio_read(i, 0x02);
            if( temp != 0xFFFF )
            {
                phy_addr = i;
                break;
            }
        }
    } /* phy search */

    if(phy_addr == 0xFF)
    {
        ETH_TRACE("phy not probe!\n");
        return;
    }
    else
    {
        ETH_TRACE("found a phy, address:0x%02X\n", phy_addr);
    }

    /* RESET PHY */
    mdio_write(phy_addr, MII_BMCR, BMCR_RESET);
    while (1)
    {
        rt_thread_delay(RT_TICK_PER_SECOND);

        rt_uint16_t reg = mdio_read(phy_addr, MII_BMCR);
        if ((reg & BMCR_RESET) == 0)
        {
            break;
        }
    }

    mdio_write(phy_addr, MII_ADVERTISE, ADVERTISE_CSMA |
               ADVERTISE_10HALF |
               ADVERTISE_10FULL |
               ADVERTISE_100HALF |
               ADVERTISE_100FULL);
    {
        uint16_t reg = mdio_read(phy_addr, MII_BMCR);
        mdio_write(phy_addr, MII_BMCR, reg | BMCR_ANRESTART);
    }

    while(1)
    {
        uint16_t status = mdio_read(phy_addr, MII_BMSR);
        phy_speed_new = 0;

        if((status & (BMSR_ANEGCAPABLE | BMSR_LSTATUS)) == (BMSR_ANEGCAPABLE | BMSR_LSTATUS))
        {
            phy_speed_new = PHY_LINK_MASK;

            status = mdio_read(phy_addr, MII_LPA);

            if(status & PHY_ANLPA_DR100_TX_FULL)
            {
                phy_speed_new |= PHY_100FULL_MASK;
            }
            else if(status & PHY_ANLPA_DR100_TX_HALF)
            {
                phy_speed_new |= PHY_100HALF_MASK;
            }
            else if(status & PHY_ANLPA_DR10_TX_FULL)
            {
                phy_speed_new |= PHY_10FULL_MASK;
            }
            else if(status & PHY_ANLPA_DR10_TX_HALF)
            {
                phy_speed_new |= PHY_10HALF_MASK;
            }
        }

        /* linkchange */
        if(phy_speed_new != phy_speed)
        {
            if(phy_speed_new & PHY_LINK_MASK)
            {
                ETH_TRACE("link up ");

                if(phy_speed_new & PHY_100FULL_MASK)
                {
                    ETH_TRACE("100Mbps full-duplex\n");
                    EMAC->CTL |= (EMAC_CTL_OPMODE_Msk | EMAC_CTL_FUDUP_Msk);
                }
                else if(phy_speed_new & PHY_100HALF_MASK)
                {
                    ETH_TRACE("100Mbps half-duplex\n");
                    EMAC->CTL = (EMAC->CTL & ~EMAC_CTL_FUDUP_Msk) | EMAC_CTL_OPMODE_Msk;
                }
                else if(phy_speed_new & PHY_10FULL_MASK)
                {
                    ETH_TRACE("10Mbps full-duplex\n");
                    EMAC->CTL = (EMAC->CTL & ~EMAC_CTL_OPMODE_Msk) | EMAC_CTL_FUDUP_Msk;
                }
                else
                {
                    ETH_TRACE("10Mbps half-duplex\n");
                    EMAC->CTL &= ~(EMAC_CTL_OPMODE_Msk | EMAC_CTL_FUDUP_Msk);
                }

                /* send link up. */
                eth_device_linkchange(&eth, RT_TRUE);
            } /* link up. */
            else
            {
                ETH_TRACE("link down\r\n");

                /* send link down. */
                eth_device_linkchange(&eth, RT_FALSE);
            } /* link down. */

            phy_speed = phy_speed_new;
        } /* linkchange */

        rt_thread_delay(RT_TICK_PER_SECOND);
    } /* while(1) */
}

static rt_err_t rt_m480_emac_init(rt_device_t dev)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    CLK_EnableModuleClock(EMAC_MODULE);

    // Configure MDC clock rate to HCLK / (127 + 1) = 1.5 MHz if system is running at 192 MHz
    CLK_SetModuleClock(EMAC_MODULE, 0, CLK_CLKDIV3_EMAC(127));

    // Configure RMII pins
//    SYS->GPA_MFPL |= SYS_GPA_MFPL_PA6MFP_EMAC_RMII_RXERR | SYS_GPA_MFPL_PA7MFP_EMAC_RMII_CRSDV;
    SYS->GPA_MFPL |= SYS_GPA_MFPL_PA7MFP_EMAC_RMII_CRSDV;
    SYS->GPC_MFPL |= SYS_GPC_MFPL_PC6MFP_EMAC_RMII_RXD1 | SYS_GPC_MFPL_PC7MFP_EMAC_RMII_RXD0;
    SYS->GPC_MFPH |= SYS_GPC_MFPH_PC8MFP_EMAC_RMII_REFCLK;
    SYS->GPE_MFPH |= SYS_GPE_MFPH_PE8MFP_EMAC_RMII_MDC |
                     SYS_GPE_MFPH_PE9MFP_EMAC_RMII_MDIO |
                     SYS_GPE_MFPH_PE10MFP_EMAC_RMII_TXD0 |
                     SYS_GPE_MFPH_PE11MFP_EMAC_RMII_TXD1 |
                     SYS_GPE_MFPH_PE12MFP_EMAC_RMII_TXEN;

    // Enable high slew rate on all RMII TX output pins
    PE->SLEWCTL = (GPIO_SLEWCTL_HIGH << GPIO_SLEWCTL_HSREN10_Pos) |
                  (GPIO_SLEWCTL_HIGH << GPIO_SLEWCTL_HSREN11_Pos) |
                  (GPIO_SLEWCTL_HIGH << GPIO_SLEWCTL_HSREN12_Pos);

        /* Lock protected registers */
    SYS_LockReg();

    EMAC_init();

    NVIC_SetPriority(EMAC_TX_IRQn, 1);
    NVIC_EnableIRQ(EMAC_TX_IRQn);
    NVIC_SetPriority(EMAC_RX_IRQn, 1);
    NVIC_EnableIRQ(EMAC_RX_IRQn);

    rt_sem_init(&eth_sem, "eth_sem", 0, RT_IPC_FLAG_FIFO);

    rt_thread_init(&eth_tid, "eth", eth_entry, RT_NULL, eth_stack, sizeof(eth_stack), RT_THREAD_PRIORITY_MAX - 2, 10);

    rt_thread_startup(&eth_tid);


#if LWIP_IPV4 && LWIP_IGMP
    netif_set_igmp_mac_filter(eth.netif, igmp_mac_filter);
#endif /* LWIP_IPV4 && LWIP_IGMP */
    
    return RT_EOK;
}

static rt_err_t rt_m480_emac_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_m480_emac_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t rt_m480_emac_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t rt_m480_emac_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_m480_emac_control(rt_device_t dev, int cmd, void *args)
{
    switch(cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if(args) rt_memcpy(args, eth_addr, 6);
        else return -RT_ERROR;

        break;

    default :
        break;
    }

    return RT_EOK;
}

rt_err_t rt_m480_emac_tx(rt_device_t dev, struct pbuf* p)
{
    struct pbuf* q;
    rt_uint32_t offset;
    rt_uint8_t *buf;

    buf = emac_get_tx_buf();

    /* get free tx buffer */
    if(buf == RT_NULL)
    {
        rt_sem_control(&eth_sem, RT_IPC_CMD_RESET, 0);

        EMAC->INTSTS = EMAC_INTSTS_TXCPIF_Msk;
        EMAC->INTEN |= EMAC_INTEN_TXCPIEN_Msk;

        do{
            rt_sem_take(&eth_sem, 1);

            buf = emac_get_tx_buf();
        }while(buf == RT_NULL);
    }


    offset = 0;
    for (q = p; q != NULL; q = q->next)
    {
        rt_uint8_t* ptr;
        rt_uint32_t len;

        len = q->len;
        ptr = q->payload;

        // todo 优化复制
        memcpy(&buf[offset], ptr, len);

        offset += len;
    }


#ifdef ETH_TX_DUMP
    packet_dump("TX dump", p);
#endif

    ETH_trigger_tx(offset);

    if(EMAC->INTSTS & EMAC_INTSTS_TDUIF_Msk)
    {
        EMAC->INTSTS = EMAC_INTSTS_TDUIF_Msk;
        ETH_TRIGGER_TX();
    }

    /* Return SUCCESS */
    return RT_EOK;
}

struct pbuf *rt_m480_emac_rx(rt_device_t dev)
{
    unsigned int status;
    struct pbuf* p;

    /* init p pointer */
    p = RT_NULL;

start:
    status = cur_rx_desc_ptr->status1;

    if(status & OWNERSHIP_EMAC)
    {
        goto end;
    }

    if ((status & RXFD_RXGD) && !(status & EMAC_DMARXDESC_CRCEIF_Msk))
    {
        p = pbuf_alloc(PBUF_RAW, status & 0xFFFF, PBUF_RAM);
        if (p != RT_NULL)
        {
            RT_ASSERT(p->next == RT_NULL);

            const char * from = (const char *)(cur_rx_desc_ptr->buf);

            // todo 优化复制
            memcpy(p->payload, from, p->len);
        }
    }

#ifdef ETH_RX_DUMP
    packet_dump("RX dump", p);
#endif /* ETH_RX_DUMP */

    cur_rx_desc_ptr->status1 = OWNERSHIP_EMAC;
    cur_rx_desc_ptr = cur_rx_desc_ptr->next;

    if(p == RT_NULL)
    {
        goto start;
    }

    return p;
    
end:
    if(!(EMAC->INTEN & EMAC_INTEN_RDUIEN_Msk))
    {
        EMAC->INTSTS = (EMAC_INTSTS_RDUIF_Msk | EMAC_INTSTS_RXGDIF_Msk);
        EMAC->INTEN |= (EMAC_INTEN_RDUIEN_Msk | EMAC_INTEN_RXGDIEN_Msk);

        ETH_TRIGGER_RX();
    }
    else
    {
        EMAC->INTSTS = EMAC_INTSTS_RXGDIF_Msk;
        EMAC->INTEN |= EMAC_INTEN_RXGDIEN_Msk;
    }
    
    return RT_NULL;
}

static void rt_hw_m480_emac_register(char *dev_name)
{
    rt_uint32_t value = 0;

    SYS_UnlockReg();
    FMC_Open();

    for (rt_uint8_t i = 0; i < 3; i++)
    {
        value += FMC_ReadUID(i);
    }

    FMC_Close();
    SYS_LockReg();

    eth_addr[0] = 0x00;
    eth_addr[1] = 0x00;
    eth_addr[2] = 0x00;
    eth_addr[3] = (value >> 16) & 0xff;
    eth_addr[4] = (value >> 8) & 0xff;
    eth_addr[5] = (value) & 0xff;

    eth.parent.init       = rt_m480_emac_init;
    eth.parent.open       = rt_m480_emac_open;
    eth.parent.close      = rt_m480_emac_close;
    eth.parent.read       = rt_m480_emac_read;
    eth.parent.write      = rt_m480_emac_write;
    eth.parent.control    = rt_m480_emac_control;
    eth.parent.user_data  = RT_NULL;

    eth.eth_rx     = rt_m480_emac_rx;
    eth.eth_tx     = rt_m480_emac_tx;

    /* register eth device */
    eth_device_init(&eth, dev_name);
}

static int rt_hw_nuc487_emac_init(void)
{
    rt_hw_m480_emac_register("eh0");

    return RT_EOK;
}

INIT_APP_EXPORT(rt_hw_nuc487_emac_init);
#endif

