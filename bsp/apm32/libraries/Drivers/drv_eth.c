/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-20     luobeihai    first version
 * 2023-01-10     luobeihai    fix Eanble HARDWARE_CHECKSUM bug
 */

#include <board.h>

#ifdef BSP_USING_ETH

#include <netif/ethernetif.h>
#include <netif/etharp.h>
#include <lwip/icmp.h>
#include "lwipopts.h"
#include "lwip/ip.h"
#include "drv_eth.h"

/* debug option */
//#define DRV_DEBUG
//#define ETH_RX_DUMP
//#define ETH_TX_DUMP
#define LOG_TAG             "drv.emac"
#include <drv_log.h>

/* Global pointers on Tx and Rx descriptor used to transmit and receive descriptors */
extern ETH_DMADescConfig_T  *DMATxDescToSet, *DMARxDescToGet;

/* Ethernet Rx & Tx DMA Descriptors */
extern ETH_DMADescConfig_T  DMARxDscrTab[ETH_RXBUFNB];
extern ETH_DMADescConfig_T  DMATxDscrTab[ETH_TXBUFNB];

/* Ethernet Receive and Transmit buffers */
extern uint8_t Rx_Buff[ETH_RXBUFNB][ETH_RX_BUF_SIZE];
extern uint8_t Tx_Buff[ETH_TXBUFNB][ETH_TX_BUF_SIZE];

/* phy address */
static uint8_t phy_addr = 0xFF;

#define MAX_ADDR_LEN 6
struct rt_apm32_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;

    rt_timer_t poll_link_timer;

    /* interface address info. */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];         /* hw address   */

    uint32_t    ETH_Speed; /*!< @ref ETH_Speed */
    uint32_t    ETH_Mode;  /*!< @ref ETH_Duplex_Mode */

    uint32_t ETH_HashTableHigh;
    uint32_t ETH_HashTableLow;
};
static struct rt_apm32_eth apm32_eth_device;
static struct rt_semaphore tx_wait;
static rt_bool_t tx_is_waiting = RT_FALSE;

#if defined(ETH_RX_DUMP) || defined(ETH_TX_DUMP)
#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
static void dump_hex(const rt_uint8_t *ptr, rt_size_t buflen)
{
    unsigned char *buf = (unsigned char *)ptr;
    int i, j;

    for (i = 0; i < buflen; i += 16)
    {
        rt_kprintf("%08X: ", i);

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                rt_kprintf("%02X ", buf[i + j]);
            else
                rt_kprintf("   ");
        rt_kprintf(" ");

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                rt_kprintf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
        rt_kprintf("\n");
    }
}
#endif

/* interrupt service routine */
void ETH_IRQHandler(void)
{
    rt_uint32_t status, ier;

    /* enter interrupt */
    rt_interrupt_enter();

    /* ETH DMA status registor */
    status = ETH->DMASTS;
    /* ETH DMA interrupt resgitor */
    ier = ETH->DMAINTEN;

    if(status & ETH_DMA_INT_MMC)
    {
        ETH_ClearDMAIntFlag(ETH_DMA_INT_MMC);
    }

    if(status & ETH_DMA_INT_NIS)
    {
        rt_uint32_t nis_clear = ETH_DMA_INT_NIS;

        /* [0]:Transmit Interrupt. */
        if((status & ier) & ETH_DMA_INT_TX) /* packet transmission */
        {
            if (tx_is_waiting == RT_TRUE)
            {
                tx_is_waiting = RT_FALSE;
                rt_sem_release(&tx_wait);
            }

            nis_clear |= ETH_DMA_INT_TX;
        }

        /* [2]:Transmit Buffer Unavailable. */

        /* [6]:Receive Interrupt. */
        if((status & ier) & ETH_DMA_INT_RX) /* packet reception */
        {
            /* a frame has been received */
            eth_device_ready(&(apm32_eth_device.parent));

            nis_clear |= ETH_DMA_INT_RX;
        }

        /* [14]:Early Receive Interrupt. */

        ETH_ClearDMAIntFlag(nis_clear);
    }

    if(status & ETH_DMA_INT_AIS)
    {
        rt_uint32_t ais_clear = ETH_DMA_INT_AIS;

        /* [1]:Transmit Process Stopped. */
        if(status & ETH_DMA_INT_TPS)
        {
            ais_clear |= ETH_DMA_INT_TPS;
        }

        /* [3]:Transmit Jabber Timeout. */
        if(status & ETH_DMA_INT_TJT)
        {
            ais_clear |= ETH_DMA_INT_TJT;
        }

        /* [4]: Receive FIFO Overflow. */
        if(status & ETH_DMA_INT_RO)
        {
            ais_clear |= ETH_DMA_INT_RO;
        }

        /* [5]: Transmit Underflow. */
        if(status & ETH_DMA_INT_TU)
        {
            ais_clear |= ETH_DMA_INT_TU;
        }

        /* [7]: Receive Buffer Unavailable. */
        if(status & ETH_DMA_INT_RBU)
        {
            ais_clear |= ETH_DMA_INT_RBU;
        }

        /* [8]: Receive Process Stopped. */
        if(status & ETH_DMA_INT_RPS)
        {
            ais_clear |= ETH_DMA_INT_RPS;
        }

        /* [9]: Receive Watchdog Timeout. */
        if(status & ETH_DMA_INT_RWT)
        {
            ais_clear |= ETH_DMA_INT_RWT;
        }

        /* [10]: Early Transmit Interrupt. */

        /* [13]: Fatal Bus Error. */
        if(status & ETH_DMA_INT_FBE)
        {
            ais_clear |= ETH_DMA_INT_FBE;
        }

        ETH_ClearDMAIntFlag(ais_clear);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

#if (LWIP_IPV4 && LWIP_IGMP) || (LWIP_IPV6 && LWIP_IPV6_MLD)
/* polynomial: 0x04C11DB7 */
static uint32_t ethcrc(const uint8_t *data, size_t length)
{
    uint32_t crc = 0xffffffff;
    size_t i;
    int j;

    for (i = 0; i < length; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (((crc >> 31) ^ (data[i] >> j)) & 0x01)
            {
                /* x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1 */
                crc = (crc << 1) ^ 0x04C11DB7;
            }
            else
            {
                crc = crc << 1;
            }
        }
    }

    return ~crc;
}

#define HASH_BITS   6       /* #bits in hash */
static void register_multicast_address(struct rt_apm32_eth *apm32_eth, const uint8_t *mac)
{
    uint32_t crc;
    uint8_t hash;

    /* calculate crc32 value of mac address */
    crc = ethcrc(mac, 6);

    /* only upper 6 bits (HASH_BITS) are used
    * which point to specific bit in he hash registers
    */
    hash = (crc >> 26) & 0x3F;
    //rt_kprintf("register_multicast_address crc: %08X hash: %02X\n", crc, hash);

    if (hash > 31)
    {
        apm32_eth->ETH_HashTableHigh |= 1 << (hash - 32);
        ETH->HTH = apm32_eth->ETH_HashTableHigh;
    }
    else
    {
        apm32_eth->ETH_HashTableLow |= 1 << hash;
        ETH->HTL = apm32_eth->ETH_HashTableLow;
    }
}
#endif /* (LWIP_IPV4 && LWIP_IGMP) || (LWIP_IPV6 && LWIP_IPV6_MLD) */

#if LWIP_IPV4 && LWIP_IGMP
static err_t igmp_mac_filter( struct netif *netif, const ip4_addr_t *ip4_addr, enum netif_mac_filter_action action )
{
    uint8_t mac[6];
    const uint8_t *p = (const uint8_t *)ip4_addr;
    struct rt_apm32_eth *apm32_eth = (struct rt_apm32_eth *)netif->state;

    mac[0] = 0x01;
    mac[1] = 0x00;
    mac[2] = 0x5E;
    mac[3] = *(p+1) & 0x7F;
    mac[4] = *(p+2);
    mac[5] = *(p+3);

    register_multicast_address(apm32_eth, mac);

    if(1)
    {
        rt_kprintf("%s %s %s ", __FUNCTION__, (action==NETIF_ADD_MAC_FILTER)?"add":"del", ip4addr_ntoa(ip4_addr));
        rt_kprintf("%02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    }

    return 0;
}
#endif /* LWIP_IPV4 && LWIP_IGMP */

#if LWIP_IPV6 && LWIP_IPV6_MLD
static err_t mld_mac_filter( struct netif *netif, const ip6_addr_t *ip6_addr, enum netif_mac_filter_action action )
{
    uint8_t mac[6];
    const uint8_t *p = (const uint8_t *)&ip6_addr->addr[3];
    struct rt_apm32_eth *apm32_eth = (struct rt_apm32_eth *)netif->state;

    mac[0] = 0x33;
    mac[1] = 0x33;
    mac[2] = *(p+0);
    mac[3] = *(p+1);
    mac[4] = *(p+2);
    mac[5] = *(p+3);

    register_multicast_address(apm32_eth, mac);

    if(1)
    {
        rt_kprintf("%s %s %s ", __FUNCTION__, (action==NETIF_ADD_MAC_FILTER)?"add":"del", ip6addr_ntoa(ip6_addr));
        rt_kprintf("%02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    }

    return 0;
}
#endif /* LWIP_IPV6 && LWIP_IPV6_MLD */

/* initialize the interface */
static rt_err_t rt_apm32_eth_init(rt_device_t dev)
{
    struct rt_apm32_eth * apm32_eth = (struct rt_apm32_eth *)dev;
    ETH_Config_T ETH_InitStructure;

    /* Enable ETHERNET clock  */
#if defined(SOC_SERIES_APM32F1)
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_ETH_MAC | RCM_AHB_PERIPH_ETH_MAC_TX |
                             RCM_AHB_PERIPH_ETH_MAC_RX);
#elif defined(SOC_SERIES_APM32F4)
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_ETH_MAC | RCM_AHB1_PERIPH_ETH_MAC_Tx |
                              RCM_AHB1_PERIPH_ETH_MAC_Rx);
#endif

    /* Reset ETHERNET on AHB Bus */
    ETH_Reset();

    /* Software reset */
    ETH_SoftwareReset();

    /* Wait for software reset */
    while(ETH_ReadSoftwareReset() == SET);

    /* ETHERNET Configuration --------------------------------------------------*/
    /* Call ETH_StructInit if you don't like to configure all ETH_InitStructure parameter */
    ETH_ConfigStructInit(&ETH_InitStructure);

    /* Fill ETH_InitStructure parametrs */
    /*------------------------   MAC   -----------------------------------*/
    ETH_InitStructure.autoNegotiation = ETH_AUTONEGOTIATION_ENABLE;
    ETH_InitStructure.speed = (ETH_SPEED_T)apm32_eth->ETH_Speed;
    ETH_InitStructure.mode  = (ETH_MODE_T)apm32_eth->ETH_Mode;

    ETH_InitStructure.loopbackMode = ETH_LOOPBACKMODE_DISABLE;
    ETH_InitStructure.retryTransmission = ETH_RETRYTRANSMISSION_DISABLE;
    ETH_InitStructure.automaticPadCRCStrip = ETH_AUTOMATICPADCRCSTRIP_DISABLE;
    ETH_InitStructure.receiveAll = ETH_RECEIVEAll_DISABLE;
    ETH_InitStructure.broadcastFramesReception = ETH_BROADCASTFRAMESRECEPTION_ENABLE;
    ETH_InitStructure.promiscuousMode = ETH_PROMISCUOUS_MODE_DISABLE;
    ETH_InitStructure.multicastFramesFilter = ETH_MULTICASTFRAMESFILTER_HASHTABLE;
    ETH_InitStructure.hashTableHigh = apm32_eth->ETH_HashTableHigh;
    ETH_InitStructure.hashTableLow  = apm32_eth->ETH_HashTableLow;
    ETH_InitStructure.unicastFramesFilter = ETH_UNICASTFRAMESFILTER_PERFECT;
#ifdef RT_LWIP_USING_HW_CHECKSUM
    ETH_InitStructure.checksumOffload = ETH_CHECKSUMOFFLAOD_ENABLE;
#endif

    /*------------------------   DMA   -----------------------------------*/

    /* When we use the Checksum offload feature, we need to enable the Store and Forward mode:
    the store and forward guarantee that a whole frame is stored in the FIFO, so the MAC can insert/verify the checksum,
    if the checksum is OK the DMA can handle the frame otherwise the frame is dropped */
    ETH_InitStructure.dropTCPIPChecksumErrorFrame = ETH_DROPTCPIPCHECKSUMERRORFRAME_ENABLE;
    ETH_InitStructure.receiveStoreForward = ETH_RECEIVESTOREFORWARD_ENABLE;
    ETH_InitStructure.flushReceivedFrame = ETH_FLUSHRECEIVEDFRAME_DISABLE;
    ETH_InitStructure.transmitStoreForward = ETH_TRANSMITSTOREFORWARD_ENABLE;

    ETH_InitStructure.forwardErrorFrames = ETH_FORWARDERRORFRAMES_DISABLE;
    ETH_InitStructure.forwardUndersizedGoodFrames = ETH_FORWARDUNDERSIZEDGOODFRAMES_DISABLE;
    ETH_InitStructure.secondFrameOperate = ETH_SECONDFRAMEOPERARTE_ENABLE;
    ETH_InitStructure.addressAlignedBeats = ETH_ADDRESSALIGNEDBEATS_ENABLE;
    ETH_InitStructure.fixedBurst = ETH_FIXEDBURST_ENABLE;
    ETH_InitStructure.rxDMABurstLength = ETH_RXDMABURSTLENGTH_32BEAT;
    ETH_InitStructure.txDMABurstLength = ETH_TXDMABURSTLENGTH_32BEAT;
    ETH_InitStructure.DMAArbitration = ETH_DMAARBITRATION_ROUNDROBIN_RXTX_2_1;

    /* configure Ethernet */
    ETH_Config(&ETH_InitStructure, phy_addr);

    /* Enable DMA Receive interrupt (need to enable in this case Normal interrupt) */
    ETH_EnableDMAInterrupt(ETH_DMA_INT_NIS | ETH_DMA_INT_RX | ETH_DMA_INT_TX);
    NVIC_EnableIRQ(ETH_IRQn);

    /* Initialize Tx Descriptors list: Chain Mode */
    ETH_ConfigDMATxDescChain(DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);
    /* Initialize Rx Descriptors list: Chain Mode  */
    ETH_ConfigDMARxDescChain(DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);

    /* MAC address configuration */
    ETH_ConfigMACAddress(ETH_MAC_ADDRESS0, (u8*)&apm32_eth_device.dev_addr[0]);

    /* Enable MAC and DMA transmission and reception */
    ETH_Start();

#if LWIP_IPV4 && LWIP_IGMP
    netif_set_igmp_mac_filter(apm32_eth->parent.netif, igmp_mac_filter);
#endif /* LWIP_IPV4 && LWIP_IGMP */

#if LWIP_IPV6 && LWIP_IPV6_MLD
    netif_set_mld_mac_filter(apm32_eth->parent.netif, mld_mac_filter);
#endif /* LWIP_IPV6 && LWIP_IPV6_MLD */

    return RT_EOK;
}

static rt_err_t rt_apm32_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_apm32_eth_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t rt_apm32_eth_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_apm32_eth_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_apm32_eth_control(rt_device_t dev, int cmd, void *args)
{
    switch(cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if(args) rt_memcpy(args, apm32_eth_device.dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

/* ethernet device interface */
/* transmit packet. */
rt_err_t rt_apm32_eth_tx( rt_device_t dev, struct pbuf* p)
{
    struct pbuf* q;
    rt_uint32_t offset;

    /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
    while ((DMATxDescToSet->Status & ETH_DMATXDESC_OWN) != (uint32_t)RESET)
    {
        rt_err_t result;
        rt_uint32_t level;

        level = rt_hw_interrupt_disable();
        tx_is_waiting = RT_TRUE;
        rt_hw_interrupt_enable(level);

        /* it's own bit set, wait it */
        result = rt_sem_take(&tx_wait, RT_WAITING_FOREVER);
        if (result == RT_EOK) break;
        if (result == -RT_ERROR) return -RT_ERROR;
    }

    offset = 0;
    for (q = p; q != NULL; q = q->next)
    {
        uint8_t *to;

        /* Copy the frame to be sent into memory pointed by the current ETHERNET DMA Tx descriptor */
        to = (uint8_t*)((DMATxDescToSet->Buffer1Addr) + offset);
        SMEMCPY(to, q->payload, q->len);
        offset += q->len;
    }
#ifdef ETH_TX_DUMP
    rt_kprintf("tx_dump, len:%d\r\n", p->tot_len);
    dump_hex((rt_uint8_t*)(DMATxDescToSet->Buffer1Addr), p->tot_len);
#endif

    /* Setting the Frame Length: bits[12:0] */
    DMATxDescToSet->ControlBufferSize = (p->tot_len & ETH_DMATXDESC_TXBS1);
    /* Setting the last segment and first segment bits (in this case a frame is transmitted in one descriptor) */
    DMATxDescToSet->Status |= ETH_DMATXDESC_LS | ETH_DMATXDESC_FS;
    /* Enable TX Completion Interrupt */
    DMATxDescToSet->Status |= ETH_DMATXDESC_INTC;
#ifdef RT_LWIP_USING_HW_CHECKSUM
    DMATxDescToSet->Status |= ETH_DMATXDESC_CHECKSUMTCPUDPICMPFULL;
    /* clean ICMP checksum APM32F need */
    {
        struct eth_hdr *ethhdr = (struct eth_hdr *)(DMATxDescToSet->Buffer1Addr);
        /* is IP ? */
        if( ethhdr->type == htons(ETHTYPE_IP) )
        {
            struct ip_hdr *iphdr = (struct ip_hdr *)(DMATxDescToSet->Buffer1Addr + SIZEOF_ETH_HDR);
            /* is ICMP ? */
            if( IPH_PROTO(iphdr) == IP_PROTO_ICMP )
            {
                struct icmp_echo_hdr *iecho = (struct icmp_echo_hdr *)(DMATxDescToSet->Buffer1Addr + SIZEOF_ETH_HDR + sizeof(struct ip_hdr) );
                iecho->chksum = 0;
            }
        }
    }
#endif
    /* Set Own bit of the Tx descriptor Status: gives the buffer back to ETHERNET DMA */
    DMATxDescToSet->Status |= ETH_DMATXDESC_OWN;
    /* When Tx Buffer unavailable flag is set: clear it and resume transmission */
    if ((ETH->DMASTS & BIT2) != (u32)RESET)
    {
        /** Clear TBUS ETHERNET DMA flag */
        ETH->DMASTS = BIT2;
        /** Resume DMA transmission*/
        ETH->DMATXPD = 0;
    }

    /* Update the ETHERNET DMA global Tx descriptor with next Tx decriptor */
    /* Chained Mode */
    /* Selects the next DMA Tx descriptor list for next buffer to send */
    DMATxDescToSet = (ETH_DMADescConfig_T*) (DMATxDescToSet->Buffer2NextDescAddr);

    /* Return SUCCESS */
    return RT_EOK;
}

/* reception packet. */
struct pbuf *rt_apm32_eth_rx(rt_device_t dev)
{
    struct pbuf* p;
    rt_uint32_t offset = 0, framelength = 0;

    /* init p pointer */
    p = RT_NULL;

    /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
    if(((DMARxDescToGet->Status & ETH_DMARXDESC_OWN) != (uint32_t)RESET))
        return p;

    if (((DMARxDescToGet->Status & ETH_DMARXDESC_ERRS) == (uint32_t)RESET) &&
            ((DMARxDescToGet->Status & ETH_DMARXDESC_LDES) != (uint32_t)RESET) &&
            ((DMARxDescToGet->Status & ETH_DMARXDESC_FDES) != (uint32_t)RESET))
    {
        /* Get the Frame Length of the received packet: substruct 4 bytes of the CRC */
        framelength = ((DMARxDescToGet->Status & ETH_DMARXDESC_FL) >> ETH_DMARXDESC_FRAME_LENGTHSHIFT) - 4;

        /* allocate buffer */
        p = pbuf_alloc(PBUF_LINK, framelength, PBUF_RAM);
        if (p != RT_NULL)
        {
            struct pbuf* q;

            for (q = p; q != RT_NULL; q= q->next)
            {
                /* Copy the received frame into buffer from memory pointed by the current ETHERNET DMA Rx descriptor */
                SMEMCPY(q->payload, (uint8_t *)((DMARxDescToGet->Buffer1Addr) + offset), q->len);
                offset += q->len;
            }
#ifdef ETH_RX_DUMP
            rt_kprintf("rx_dump, len:%d\r\n", p->tot_len);
            dump_hex((rt_uint8_t*)(DMARxDescToGet->Buffer1Addr), p->tot_len);
#endif
        }
    }

    /* Set Own bit of the Rx descriptor Status: gives the buffer back to ETHERNET DMA */
    DMARxDescToGet->Status = ETH_DMARXDESC_OWN;

    /* When Rx Buffer unavailable flag is set: clear it and resume reception */
    if ((ETH->DMASTS & BIT7) != (u32)RESET)
    {
        /* Clear RBUS ETHERNET DMA flag */
        ETH->DMASTS = BIT7;
        /* Resume DMA reception */
        ETH->DMARXPD = 0;
    }

    /* Update the ETHERNET DMA global Rx descriptor with next Rx decriptor */
    /* Chained Mode */
    if((DMARxDescToGet->ControlBufferSize & ETH_DMARXDESC_RXCH) != (uint32_t)RESET)
    {
        /* Selects the next DMA Rx descriptor list for next buffer to read */
        DMARxDescToGet = (ETH_DMADescConfig_T*) (DMARxDescToGet->Buffer2NextDescAddr);
    }
    else /* Ring Mode */
    {
        if((DMARxDescToGet->ControlBufferSize & ETH_DMARXDESC_RXER) != (uint32_t)RESET)
        {
            /* Selects the first DMA Rx descriptor for next buffer to read: last Rx descriptor was used */
            DMARxDescToGet = (ETH_DMADescConfig_T*) (ETH->DMARXDLADDR);
        }
        else
        {
            /* Selects the next DMA Rx descriptor list for next buffer to read */
            DMARxDescToGet = (ETH_DMADescConfig_T*) ((uint32_t)DMARxDescToGet + 0x10 + ((ETH->DMABMOD & 0x0000007C) >> 2));
        }
    }

    return p;
}

enum {
    PHY_LINK        = (1 << 0),
    PHY_100M        = (1 << 1),
    PHY_FULL_DUPLEX = (1 << 2),
};

static void phy_linkchange(void)
{
    uint8_t phy_speed_new = 0;
    static uint8_t phy_speed = 0;
    uint16_t status  = ETH_ReadPHYRegister(phy_addr, PHY_BSR);

    LOG_D("phy basic status reg is 0x%X", status);

    if(status & (PHY_AUTONEGO_COMPLETE | PHY_LINKED_STATUS))
    {
        uint16_t SR;

        phy_speed_new |= PHY_LINK;

        SR = ETH_ReadPHYRegister(phy_addr, PHY_Status_REG);
        LOG_D("phy control status reg is 0x%X", SR);

        if (PHY_Status_SPEED_100M(SR))
        {
            phy_speed_new |= PHY_100M;
        }

        if (PHY_Status_FULL_DUPLEX(SR))
        {
            phy_speed_new |= PHY_FULL_DUPLEX;
        }
    }

    /* linkchange */
    if(phy_speed_new != phy_speed)
    {
        if(phy_speed_new & PHY_LINK)
        {
            LOG_D("link up ");

            if(phy_speed_new & PHY_100M)
            {
                LOG_D("100Mbps");
                apm32_eth_device.ETH_Speed = ETH_SPEED_100M;
            }
            else
            {
                apm32_eth_device.ETH_Speed = ETH_SPEED_10M;
                LOG_D("10Mbps");
            }

            if(phy_speed_new & PHY_FULL_DUPLEX)
            {
                LOG_D("full-duplex\r\n");
                apm32_eth_device.ETH_Mode = ETH_MODE_FULLDUPLEX;
            }
            else
            {
                LOG_D("half-duplex\r\n");
                apm32_eth_device.ETH_Mode = ETH_MODE_HALFDUPLEX;
            }
            rt_apm32_eth_init((rt_device_t)&apm32_eth_device);

            /* send link up. */
            eth_device_linkchange(&apm32_eth_device.parent, RT_TRUE);
        } /* link up. */
        else
        {
            LOG_I("link down\r\n");
            /* send link down. */
            eth_device_linkchange(&apm32_eth_device.parent, RT_FALSE);
        } /* link down. */

        phy_speed = phy_speed_new;
    } /* linkchange */
}

static void phy_monitor_thread_entry(void *parameter)
{
    uint8_t detected_count = 0;

    while(phy_addr == 0xFF)
    {
        /* phy search */
        rt_uint32_t i, temp;
        for (i = 0; i <= 0x1F; i++)
        {
            temp = ETH_ReadPHYRegister(i, PHY_ID1_REG);

            if (temp != 0xFFFF && temp != 0x00)
            {
                phy_addr = i;
                break;
            }
        }

        detected_count++;
        rt_thread_mdelay(1000);

        if (detected_count > 10)
        {
            LOG_E("No PHY device was detected, please check hardware!");
        }
    }

    LOG_D("Found a phy, address:0x%02X", phy_addr);

    /* RESET PHY */
    LOG_D("RESET PHY!\r\n");
    ETH_WritePHYRegister(phy_addr, PHY_BCR, PHY_RESET);
    rt_thread_delay(RT_TICK_PER_SECOND * 2);
    ETH_WritePHYRegister(phy_addr, PHY_BCR, PHY_AUTONEGOTIATION);

    phy_linkchange();

    apm32_eth_device.poll_link_timer = rt_timer_create("phylnk", (void (*)(void*))phy_linkchange,
                                        NULL, RT_TICK_PER_SECOND, RT_TIMER_FLAG_PERIODIC);
    if (!apm32_eth_device.poll_link_timer || rt_timer_start(apm32_eth_device.poll_link_timer) != RT_EOK)
    {
        LOG_E("Start link change detection timer failed");
    }
}

static int rt_hw_apm32_eth_init(void)
{
    /* reset phy */
    extern void phy_reset(void);
    phy_reset();

    /* apm32 eth gpio init */
    extern void apm32_msp_eth_init(void *instance);
    apm32_msp_eth_init(RT_NULL);

    apm32_eth_device.ETH_Speed = ETH_SPEED_100M;
    apm32_eth_device.ETH_Mode  = ETH_MODE_FULLDUPLEX;

    /* set mac address. */
    apm32_eth_device.dev_addr[0] = 0x00;
    apm32_eth_device.dev_addr[1] = 0x00;
    apm32_eth_device.dev_addr[2] = 0x00;
    apm32_eth_device.dev_addr[3] = 0x00;
    apm32_eth_device.dev_addr[4] = 0x00;
    apm32_eth_device.dev_addr[5] = 0x08;

    apm32_eth_device.parent.parent.init       = rt_apm32_eth_init;
    apm32_eth_device.parent.parent.open       = rt_apm32_eth_open;
    apm32_eth_device.parent.parent.close      = rt_apm32_eth_close;
    apm32_eth_device.parent.parent.read       = rt_apm32_eth_read;
    apm32_eth_device.parent.parent.write      = rt_apm32_eth_write;
    apm32_eth_device.parent.parent.control    = rt_apm32_eth_control;
    apm32_eth_device.parent.parent.user_data  = RT_NULL;

    apm32_eth_device.parent.eth_rx     = rt_apm32_eth_rx;
    apm32_eth_device.parent.eth_tx     = rt_apm32_eth_tx;

    /* init tx semaphore */
    rt_sem_init(&tx_wait, "tx_wait", 0, RT_IPC_FLAG_FIFO);

    /* register eth device */
    eth_device_init(&(apm32_eth_device.parent), "e0");

    /* start phy monitor */
    {
        rt_thread_t tid;
        tid = rt_thread_create("phy",
                               phy_monitor_thread_entry,
                               RT_NULL,
                               512,
                               RT_THREAD_PRIORITY_MAX - 2,
                               2);
        if (tid != RT_NULL)
            rt_thread_startup(tid);
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_apm32_eth_init);

#endif /* BSP_USING_ETH */
