/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-11-30     aozima       the first version.
 * 2011-12-10     aozima       support dual ethernet.
 * 2011-12-21     aozima       cleanup code.
 * 2012-07-13     aozima       mask all GMAC MMC Interrupt.
 * 2012-07-20     aozima       fixed mask all GMAC MMC Interrupt,and read clear.
 * 2012-07-20     aozima       use memcpy replace byte copy.
 */

#include <rtthread.h>
#include <rthw.h>

#include "lwipopts.h"
#include <netif/ethernetif.h>
#include <netif/etharp.h>
#include <lwip/icmp.h>

#include "gd32f4xx.h"
#include "synopsys_emac.h"

#define ETHERNET_MAC0    ((struct rt_synopsys_eth *)(0x40020000U + 0x00008000U))

//#define EMAC_DEBUG
//#define EMAC_RX_DUMP
//#define EMAC_TX_DUMP

#ifdef EMAC_DEBUG
#define EMAC_TRACE          rt_kprintf
#else
#define EMAC_TRACE(...)
#endif

#define EMAC_RXBUFNB            4
#define EMAC_TXBUFNB            2

#define EMAC_PHY_AUTO           0
#define EMAC_PHY_10MBIT         1
#define EMAC_PHY_100MBIT        2

#define MAX_ADDR_LEN 6
struct gd32_emac
{
    /* inherit from Ethernet device */
    struct eth_device parent;

    rt_uint8_t phy_mode;
    /* interface address info. */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];     /* hw address   */

    struct rt_synopsys_eth * ETHERNET_MAC;
    IRQn_Type ETHER_MAC_IRQ;

    EMAC_DMADESCTypeDef  *DMATxDescToSet;
    EMAC_DMADESCTypeDef  *DMARxDescToGet;

#pragma pack(4)
    EMAC_DMADESCTypeDef DMARxDscrTab[EMAC_RXBUFNB];
#pragma pack(4)
    EMAC_DMADESCTypeDef DMATxDscrTab[EMAC_TXBUFNB];
#pragma pack(4)
    rt_uint8_t Rx_Buff[EMAC_RXBUFNB][EMAC_MAX_PACKET_SIZE];
#pragma pack(4)
    rt_uint8_t Tx_Buff[EMAC_TXBUFNB][EMAC_MAX_PACKET_SIZE];

    struct rt_semaphore tx_buf_free;
};

static struct gd32_emac gd32_emac_device0;

/**
  * Initializes the DMA Tx descriptors in chain mode.
  */
static void EMAC_DMA_tx_desc_init(EMAC_DMADESCTypeDef *DMATxDescTab, uint8_t* TxBuff, uint32_t TxBuffCount)
{
    uint32_t i = 0;
    EMAC_DMADESCTypeDef *DMATxDesc;

    /* Fill each DMATxDesc descriptor with the right values */
    for(i=0; i < TxBuffCount; i++)
    {
        /* Get the pointer on the ith member of the Tx Desc list */
        DMATxDesc = DMATxDescTab + i;
        /* Set Second Address Chained bit */
        DMATxDesc->Status = EMAC_DMATxDesc_TCH;

        /* Set Buffer1 address pointer */
        DMATxDesc->Buffer1Addr = (uint32_t)(&TxBuff[i*EMAC_MAX_PACKET_SIZE]);

        /* Initialize the next descriptor with the Next Descriptor Polling Enable */
        if(i < (TxBuffCount-1))
        {
            /* Set next descriptor address register with next descriptor base address */
            DMATxDesc->Buffer2NextDescAddr = (uint32_t)(DMATxDescTab+i+1);
        }
        else
        {
            /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
            DMATxDesc->Buffer2NextDescAddr = (uint32_t) DMATxDescTab;
        }
    }
}

/**
  * Initializes the DMA Rx descriptors in chain mode.
  */
static void EMAC_DMA_rx_desc_init(EMAC_DMADESCTypeDef *DMARxDescTab, uint8_t *RxBuff, uint32_t RxBuffCount)
{
    uint32_t i = 0;
    EMAC_DMADESCTypeDef *DMARxDesc;

    /* Fill each DMARxDesc descriptor with the right values */
    for(i=0; i < RxBuffCount; i++)
    {
        /* Get the pointer on the ith member of the Rx Desc list */
        DMARxDesc = DMARxDescTab+i;
        /* Set Own bit of the Rx descriptor Status */
        DMARxDesc->Status = EMAC_DMARxDesc_OWN;

        /* Set Buffer1 size and Second Address Chained bit */
        DMARxDesc->ControlBufferSize = EMAC_DMARxDesc_RCH | (uint32_t)EMAC_MAX_PACKET_SIZE;
        /* Set Buffer1 address pointer */
        DMARxDesc->Buffer1Addr = (uint32_t)(&RxBuff[i*EMAC_MAX_PACKET_SIZE]);

        /* Initialize the next descriptor with the Next Descriptor Polling Enable */
        if(i < (RxBuffCount-1))
        {
            /* Set next descriptor address register with next descriptor base address */
            DMARxDesc->Buffer2NextDescAddr = (uint32_t)(DMARxDescTab+i+1);
        }
        else
        {
            /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
            DMARxDesc->Buffer2NextDescAddr = (uint32_t)(DMARxDescTab);
        }
    }
}

static rt_err_t gd32_emac_init(rt_device_t dev)
{
    struct gd32_emac * gd32_emac_device;
    struct rt_synopsys_eth * ETHERNET_MAC;

    gd32_emac_device = (struct gd32_emac *)dev;
    ETHERNET_MAC = gd32_emac_device->ETHERNET_MAC;

    /* Software reset */
    ETHERNET_MAC->BMR |= (1<<0); /* [bit0]SWR (Software Reset) */

    /* Wait for software reset */
    while(ETHERNET_MAC->BMR & (1<<0));

    /* Configure ETHERNET */
    EMAC_init(ETHERNET_MAC, SystemCoreClock);

    /* mask all GMAC MMC Interrupt.*/
    ETHERNET_MAC->mmc_cntl = (1<<3) | (1<<0); /* MMC Counter Freeze and reset. */
    ETHERNET_MAC->mmc_intr_mask_rx = 0xFFFFFFFF;
    ETHERNET_MAC->mmc_intr_mask_tx = 0xFFFFFFFF;
    ETHERNET_MAC->mmc_ipc_intr_mask_rx = 0xFFFFFFFF;

    /* Enable DMA Receive interrupt (need to enable in this case Normal interrupt) */
    EMAC_INT_config(ETHERNET_MAC, EMAC_DMA_INT_NIS | EMAC_DMA_INT_R | EMAC_DMA_INT_T , ENABLE);

    /* Initialize Tx Descriptors list: Chain Mode */
    EMAC_DMA_tx_desc_init(gd32_emac_device->DMATxDscrTab, &gd32_emac_device->Tx_Buff[0][0], EMAC_TXBUFNB);
    gd32_emac_device->DMATxDescToSet = gd32_emac_device->DMATxDscrTab;
    /* Set Transmit Descriptor List Address Register */
    ETHERNET_MAC->TDLAR = (uint32_t) gd32_emac_device->DMATxDescToSet;

    /* Initialize Rx Descriptors list: Chain Mode  */
    EMAC_DMA_rx_desc_init(gd32_emac_device->DMARxDscrTab, &gd32_emac_device->Rx_Buff[0][0], EMAC_RXBUFNB);
    gd32_emac_device->DMARxDescToGet = gd32_emac_device->DMARxDscrTab;
    /* Set Receive Descriptor List Address Register */
    ETHERNET_MAC->RDLAR = (uint32_t) gd32_emac_device->DMARxDescToGet;

    /* MAC address configuration */
    EMAC_MAC_Addr_config(ETHERNET_MAC, EMAC_MAC_Address0, (uint8_t*)&gd32_emac_device->dev_addr[0]);

    NVIC_EnableIRQ( gd32_emac_device->ETHER_MAC_IRQ );

    /* Enable MAC and DMA transmission and reception */
    EMAC_start(ETHERNET_MAC);

    return RT_EOK;
}

static rt_err_t gd32_emac_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t gd32_emac_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t gd32_emac_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    return -RT_ENOSYS;
}

static rt_ssize_t gd32_emac_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    return -RT_ENOSYS;
}

static rt_err_t gd32_emac_control(rt_device_t dev, int cmd, void *args)
{
    struct gd32_emac * gd32_emac_device = (struct gd32_emac *)dev;

    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args) memcpy(args, &gd32_emac_device->dev_addr[0], MAX_ADDR_LEN);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

static void EMAC_IRQHandler(struct gd32_emac * gd32_emac_device)
{
    rt_uint32_t status, ier;
    struct rt_synopsys_eth * ETHERNET_MAC;

    ETHERNET_MAC = gd32_emac_device->ETHERNET_MAC;

    /* get DMA IT status */
    status = ETHERNET_MAC->SR;
    ier = ETHERNET_MAC->IER;

    /* GMAC MMC Interrupt. */
    if(status & EMAC_DMA_INT_GMI)
    {
        volatile rt_uint32_t dummy;
        volatile rt_uint32_t * reg;

        EMAC_TRACE("EMAC_DMA_INT_GMI\r\n");

        /* read clear all MMC interrupt. */
        reg = &ETHERNET_MAC->mmc_cntl;
        while((uint32_t)reg < (uint32_t)&ETHERNET_MAC->rxicmp_err_octets)
        {
            dummy = *reg++;
        }
    }

    /* Normal interrupt summary. */
    if(status & EMAC_DMA_INT_NIS)
    {
        rt_uint32_t nis_clear = EMAC_DMA_INT_NIS;

        /* [0]:Transmit Interrupt. */
        if((status & ier) & EMAC_DMA_INT_T) /* packet transmission */
        {
            rt_sem_release(&gd32_emac_device->tx_buf_free);

            nis_clear |= EMAC_DMA_INT_T;
        }

        /* [2]:Transmit Buffer Unavailable. */

        /* [6]:Receive Interrupt. */
        if((status & ier) & EMAC_DMA_INT_R) /* packet reception */
        {
            /* a frame has been received */
            eth_device_ready(&(gd32_emac_device->parent));

            nis_clear |= EMAC_DMA_INT_R;
        }

        /* [14]:Early Receive Interrupt. */

        EMAC_clear_pending(ETHERNET_MAC, nis_clear);
    }

    /* Abnormal interrupt summary. */
    if( status & EMAC_DMA_INT_AIS)
    {
        rt_uint32_t ais_clear = EMAC_DMA_INT_AIS;

        /* [1]:Transmit Process Stopped. */
        /* [3]:Transmit Jabber Timeout. */
        /* [4]: Receive FIFO Overflow. */
        /* [5]: Transmit Underflow. */
        /* [7]: Receive Buffer Unavailable. */
        /* [8]: Receive Process Stopped. */
        /* [9]: Receive Watchdog Timeout. */
        /* [10]: Early Transmit Interrupt. */
        /* [13]: Fatal Bus Error. */

        EMAC_clear_pending(ETHERNET_MAC, ais_clear);
    }
}

void ENET_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    EMAC_IRQHandler(&gd32_emac_device0);

    /* leave interrupt */
    rt_interrupt_leave();
}


/* EtherNet Device Interface */
rt_err_t gd32_emac_tx( rt_device_t dev, struct pbuf* p)
{
    struct pbuf* q;
    char * to;
    struct gd32_emac * gd32_emac_device;
    struct rt_synopsys_eth * ETHERNET_MAC;

    gd32_emac_device = (struct gd32_emac *)dev;
    ETHERNET_MAC = gd32_emac_device->ETHERNET_MAC;

    /* get free tx buffer */
    {
        rt_err_t result;
        result = rt_sem_take(&gd32_emac_device->tx_buf_free, RT_TICK_PER_SECOND/10);
        if (result != RT_EOK) return -RT_ERROR;
    }

    to = (char *)gd32_emac_device->DMATxDescToSet->Buffer1Addr;

    for (q = p; q != NULL; q = q->next)
    {
        /* Copy the frame to be sent into memory pointed by the current ETHERNET DMA Tx descriptor */
        memcpy(to, q->payload, q->len);
        to += q->len;
    }

#ifdef EMAC_TX_DUMP
    {
        rt_uint32_t i;
        rt_uint8_t *ptr = (rt_uint8_t*)(gd32_emac_device->DMATxDescToSet->Buffer1Addr);

        EMAC_TRACE("\r\n%c%c tx_dump:", gd32_emac_device->parent.netif->name[0], gd32_emac_device->parent.netif->name[1]);
        for(i=0; i<p->tot_len; i++)
        {
            if( (i%8) == 0 )
            {
                EMAC_TRACE("  ");
            }
            if( (i%16) == 0 )
            {
                EMAC_TRACE("\r\n");
            }
            EMAC_TRACE("%02x ",*ptr);
            ptr++;
        }
        EMAC_TRACE("\r\ndump done!\r\n");
    }
#endif

    /* Setting the Frame Length: bits[12:0] */
    gd32_emac_device->DMATxDescToSet->ControlBufferSize = (p->tot_len & EMAC_DMATxDesc_TBS1);
    /* Setting the last segment and first segment bits (in this case a frame is transmitted in one descriptor) */
    gd32_emac_device->DMATxDescToSet->Status |= EMAC_DMATxDesc_LS | EMAC_DMATxDesc_FS;
    /* Enable TX Completion Interrupt */
    gd32_emac_device->DMATxDescToSet->Status |= EMAC_DMATxDesc_IC;
#ifdef CHECKSUM_BY_HARDWARE
    gd32_emac_device->DMATxDescToSet->Status |= EMAC_DMATxDesc_ChecksumTCPUDPICMPFull;
    /* clean ICMP checksum */
    {
        struct eth_hdr *ethhdr = (struct eth_hdr *)(gd32_emac_device->DMATxDescToSet->Buffer1Addr);
        /* is IP ? */
        if( ethhdr->type == htons(ETHTYPE_IP) )
        {
            struct ip_hdr *iphdr = (struct ip_hdr *)(gd32_emac_device->DMATxDescToSet->Buffer1Addr + SIZEOF_ETH_HDR);
            /* is ICMP ? */
            if( IPH_PROTO(iphdr) == IP_PROTO_ICMP )
            {
                struct icmp_echo_hdr *iecho = (struct icmp_echo_hdr *)(gd32_emac_device->DMATxDescToSet->Buffer1Addr + SIZEOF_ETH_HDR + sizeof(struct ip_hdr) );
                iecho->chksum = 0;
            }
        }
    }
#endif
    /* Set Own bit of the Tx descriptor Status: gives the buffer back to ETHERNET DMA */
    gd32_emac_device->DMATxDescToSet->Status |= EMAC_DMATxDesc_OWN;
    /* When Tx Buffer unavailable flag is set: clear it and resume transmission */
    if ((ETHERNET_MAC->SR & EMAC_DMASR_TBUS) != (uint32_t)RESET)
    {
        /* Clear TBUS ETHERNET DMA flag */
        ETHERNET_MAC->SR = EMAC_DMASR_TBUS;
        /* Transmit Poll Demand to resume DMA transmission*/
        ETHERNET_MAC->TPDR = 0;
    }

    /* Update the ETHERNET DMA global Tx descriptor with next Tx decriptor */
    /* Chained Mode */
    /* Selects the next DMA Tx descriptor list for next buffer to send */
    gd32_emac_device->DMATxDescToSet = (EMAC_DMADESCTypeDef*) (gd32_emac_device->DMATxDescToSet->Buffer2NextDescAddr);

    /* Return SUCCESS */
    return RT_EOK;
}

/* reception a Ethernet packet. */
struct pbuf * gd32_emac_rx(rt_device_t dev)
{
    struct pbuf* p;
    rt_uint32_t framelength = 0;
    struct gd32_emac * gd32_emac_device;
    struct rt_synopsys_eth * ETHERNET_MAC;

    gd32_emac_device = (struct gd32_emac *)dev;
    ETHERNET_MAC = gd32_emac_device->ETHERNET_MAC;

    /* init p pointer */
    p = RT_NULL;

    /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
    if(((gd32_emac_device->DMARxDescToGet->Status & EMAC_DMARxDesc_OWN) != (uint32_t)RESET))
    {
        return p;
    }

    if (((gd32_emac_device->DMARxDescToGet->Status & EMAC_DMARxDesc_ES) == (uint32_t)RESET) &&
            ((gd32_emac_device->DMARxDescToGet->Status & EMAC_DMARxDesc_LS) != (uint32_t)RESET) &&
            ((gd32_emac_device->DMARxDescToGet->Status & EMAC_DMARxDesc_FS) != (uint32_t)RESET))
    {
        /* Get the Frame Length of the received packet: substruct 4 bytes of the CRC */
        framelength = ((gd32_emac_device->DMARxDescToGet->Status & EMAC_DMARxDesc_FL)
                       >> EMAC_DMARXDESC_FRAME_LENGTHSHIFT) - 4;

        /* allocate buffer */
        p = pbuf_alloc(PBUF_LINK, framelength, PBUF_RAM);
        if (p != RT_NULL)
        {
            const char * from;
            struct pbuf* q;

            from = (const char *)gd32_emac_device->DMARxDescToGet->Buffer1Addr;

            for (q = p; q != RT_NULL; q= q->next)
            {
                /* Copy the received frame into buffer from memory pointed by the current ETHERNET DMA Rx descriptor */
                memcpy(q->payload, from, q->len);
                from += q->len;
            }
#ifdef EMAC_RX_DUMP
            {
                rt_uint32_t i;
                rt_uint8_t *ptr = (rt_uint8_t*)(gd32_emac_device->DMARxDescToGet->Buffer1Addr);

                EMAC_TRACE("\r\n%c%c rx_dump:", gd32_emac_device->parent.netif->name[0], gd32_emac_device->parent.netif->name[1]);
                for(i=0; i<p->tot_len; i++)
                {
                    if( (i%8) == 0 )
                    {
                        EMAC_TRACE("  ");
                    }
                    if( (i%16) == 0 )
                    {
                        EMAC_TRACE("\r\n");
                    }
                    EMAC_TRACE("%02x ",*ptr);
                    ptr++;
                }
                EMAC_TRACE("\r\ndump done!\r\n");
            }
#endif
        }
    }

    /* Set Own bit of the Rx descriptor Status: gives the buffer back to ETHERNET DMA */
    gd32_emac_device->DMARxDescToGet->Status = EMAC_DMARxDesc_OWN;

    /* When Rx Buffer unavailable flag is set: clear it and resume reception */
    if ((ETHERNET_MAC->SR & EMAC_DMASR_RBUS) != (uint32_t)RESET)
    {
        /* Clear RBUS ETHERNET DMA flag */
        ETHERNET_MAC->SR = EMAC_DMASR_RBUS;
        /* Resume DMA reception */
        ETHERNET_MAC->RPDR = 0;
    }

    /* Update the ETHERNET DMA global Rx descriptor with next Rx decriptor */
    /* Chained Mode */
    if((gd32_emac_device->DMARxDescToGet->ControlBufferSize & EMAC_DMARxDesc_RCH) != (uint32_t)RESET)
    {
        /* Selects the next DMA Rx descriptor list for next buffer to read */
        gd32_emac_device->DMARxDescToGet = (EMAC_DMADESCTypeDef*) (gd32_emac_device->DMARxDescToGet->Buffer2NextDescAddr);
    }
    else /* Ring Mode */
    {
        if((gd32_emac_device->DMARxDescToGet->ControlBufferSize & EMAC_DMARxDesc_RER) != (uint32_t)RESET)
        {
            /* Selects the first DMA Rx descriptor for next buffer to read: last Rx descriptor was used */
            gd32_emac_device->DMARxDescToGet = (EMAC_DMADESCTypeDef*) (ETHERNET_MAC->RDLAR);
        }
        else
        {
            /* Selects the next DMA Rx descriptor list for next buffer to read */
            gd32_emac_device->DMARxDescToGet = (EMAC_DMADESCTypeDef*) ((uint32_t)gd32_emac_device->DMARxDescToGet + 0x10 + ((ETHERNET_MAC->BMR & EMAC_DMABMR_DSL) >> 2));
        }
    }

    return p;
}

/*!
    \brief      configures the nested vectored interrupt controller
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void nvic_configuration(void)
{
    nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x0);
    nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
    nvic_irq_enable(ENET_IRQn, 0, 0);
}

/*!
    \brief      configures the different GPIO ports
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void enet_gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOG);
    rcu_periph_clock_enable(RCU_GPIOH);
    rcu_periph_clock_enable(RCU_GPIOI);

    gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_8);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_8);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_8);

    /* enable SYSCFG clock */
    rcu_periph_clock_enable(RCU_SYSCFG);

    /* choose DIV2 to get 50MHz from 200MHz on CKOUT0 pin (PA8) to clock the PHY */
    rcu_ckout0_config(RCU_CKOUT0SRC_PLLP, RCU_CKOUT0_DIV4);
    syscfg_enet_phy_interface_config(SYSCFG_ENET_PHY_RMII);

    /* PA1: ETH_RMII_REF_CLK */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_1);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_1);

    /* PA2: ETH_MDIO */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_2);

    /* PA7: ETH_RMII_CRS_DV */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_7);

    gpio_af_set(GPIOA, GPIO_AF_11, GPIO_PIN_1);
    gpio_af_set(GPIOA, GPIO_AF_11, GPIO_PIN_2);
    gpio_af_set(GPIOA, GPIO_AF_11, GPIO_PIN_7);

    /* PB11: ETH_RMII_TX_EN */
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_11);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_11);

    /* PB12: ETH_RMII_TXD0 */
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_12);

    /* PB13: ETH_RMII_TXD1 */
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_13);

    gpio_af_set(GPIOB, GPIO_AF_11, GPIO_PIN_11);
    gpio_af_set(GPIOB, GPIO_AF_11, GPIO_PIN_12);
    gpio_af_set(GPIOB, GPIO_AF_11, GPIO_PIN_13);

    /* PC1: ETH_MDC */
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_1);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_1);

    /* PC4: ETH_RMII_RXD0 */
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_4);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_4);

    /* PC5: ETH_RMII_RXD1 */
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_5);

    gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_1);
    gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_4);
    gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_5);
}


int rt_hw_gd32_eth_init(void)
{
    rt_kprintf("rt_gd32_eth_init...\n");

    /* enable ethernet clock  */
    rcu_periph_clock_enable(RCU_ENET);
    rcu_periph_clock_enable(RCU_ENETTX);
    rcu_periph_clock_enable(RCU_ENETRX);

    nvic_configuration();

    /* configure the GPIO ports for ethernet pins */
    enet_gpio_config();

    /* set autonegotiation mode */
    gd32_emac_device0.phy_mode = EMAC_PHY_AUTO;
    gd32_emac_device0.ETHERNET_MAC = ETHERNET_MAC0;
    gd32_emac_device0.ETHER_MAC_IRQ  = ENET_IRQn;

    // OUI 00-00-0E FUJITSU LIMITED
    gd32_emac_device0.dev_addr[0] = 0x00;
    gd32_emac_device0.dev_addr[1] = 0x00;
    gd32_emac_device0.dev_addr[2] = 0x0E;
    /* set mac address: (only for test) */
    gd32_emac_device0.dev_addr[3] = 0x12;
    gd32_emac_device0.dev_addr[4] = 0x34;
    gd32_emac_device0.dev_addr[5] = 0x56;

    gd32_emac_device0.parent.parent.init         = gd32_emac_init;
    gd32_emac_device0.parent.parent.open         = gd32_emac_open;
    gd32_emac_device0.parent.parent.close    = gd32_emac_close;
    gd32_emac_device0.parent.parent.read         = gd32_emac_read;
    gd32_emac_device0.parent.parent.write    = gd32_emac_write;
    gd32_emac_device0.parent.parent.control  = gd32_emac_control;
    gd32_emac_device0.parent.parent.user_data = RT_NULL;

    gd32_emac_device0.parent.eth_rx          = gd32_emac_rx;
    gd32_emac_device0.parent.eth_tx          = gd32_emac_tx;

    /* init tx buffer free semaphore */
    rt_sem_init(&gd32_emac_device0.tx_buf_free, "tx_buf0", EMAC_TXBUFNB, RT_IPC_FLAG_FIFO);
    eth_device_init(&(gd32_emac_device0.parent), "e0");

    /* change device link status */
    eth_device_linkchange(&(gd32_emac_device0.parent), RT_TRUE);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_gd32_eth_init);
