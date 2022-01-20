/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-12-12      Wayne            First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_EMAC) && defined(RT_USING_LWIP)

#include <rtdevice.h>
#include "NuMicro.h"
#include <netif/ethernetif.h>
#include <netif/etharp.h>
#include <lwip/icmp.h>
#include <lwip/pbuf.h>
#include "lwipopts.h"

#include "drv_sys.h"
//#include "drv_pdma.h"

/* Private define ---------------------------------------------------------------*/
// RT_DEV_NAME_PREFIX e

#define NU_EMAC_DEBUG
#if defined(NU_EMAC_DEBUG)
    //#define NU_EMAC_RX_DUMP
    //#define NU_EMAC_TX_DUMP
    #define NU_EMAC_TRACE         rt_kprintf
#else
    #define NU_EMAC_TRACE(...)
#endif

#define NU_EMAC_TID_STACK_SIZE  1024

/* Private typedef --------------------------------------------------------------*/
enum
{
    EMAC_START = -1,
#if defined(BSP_USING_EMAC0)
    EMAC0_IDX,
#endif
#if defined(BSP_USING_EMAC1)
    EMAC1_IDX,
#endif
    EMAC_CNT
};

struct nu_emac_lwip_pbuf
{
    struct pbuf_custom p;  // lwip pbuf
    EMAC_FRAME_T *psPktFrameDataBuf; // gmac descriptor
    EMAC_MEMMGR_T *psMemMgr;
    EMAC_DESCRIPTOR_T *rx_desc;
    const struct memp_desc *memp_rx_pool;
};
typedef struct nu_emac_lwip_pbuf *nu_emac_lwip_pbuf_t;

struct nu_emac
{
    struct eth_device   eth;
    char               *name;
    EMAC_MEMMGR_T       memmgr;
    IRQn_Type           irqn_tx;
    IRQn_Type           irqn_rx;
    E_SYS_IPRST         rstidx;
    E_SYS_IPCLK         clkidx;
    rt_thread_t         link_monitor;
    rt_uint8_t          mac_addr[6];
    struct rt_semaphore eth_sem;
    const struct memp_desc *memp_rx_pool;
};
typedef struct nu_emac *nu_emac_t;

/* Private functions ------------------------------------------------------------*/
#if defined(NU_EMAC_RX_DUMP) || defined(NU_EMAC_TX_DUMP)
    static void nu_emac_pkt_dump(const char *msg, const struct pbuf *p);
#endif
#if LWIP_IPV4 && LWIP_IGMP
    static err_t nu_igmp_mac_filter(struct netif *netif, const ip4_addr_t *ip4_addr, enum netif_mac_filter_action action);
#endif
static void nu_emac_halt(nu_emac_t);
static void nu_emac_reinit(nu_emac_t);
static void link_monitor(void *param);
static rt_err_t nu_emac_init(rt_device_t dev);

static rt_err_t nu_emac_open(rt_device_t dev, rt_uint16_t oflag);
static rt_err_t nu_emac_close(rt_device_t dev);
static rt_size_t nu_emac_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
static rt_size_t nu_emac_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
static rt_err_t nu_emac_control(rt_device_t dev, int cmd, void *args);
static rt_err_t nu_emac_tx(rt_device_t dev, struct pbuf *p);
static struct pbuf *nu_emac_rx(rt_device_t dev);
static void rt_hw_nu_emac_assign_macaddr(nu_emac_t psNuEMAC);
static int rt_hw_nu_emac_init(void);
static void *nu_emac_memcpy(void *dest, void *src, unsigned int count);
static void nu_emac_tx_isr(int vector, void *param);
static void nu_emac_rx_isr(int vector, void *param);

/* Public functions -------------------------------------------------------------*/

/* Private variables ------------------------------------------------------------*/
#if defined(BSP_USING_EMAC0)
    LWIP_MEMPOOL_DECLARE(emac0_rx, EMAC_RX_DESC_SIZE, sizeof(struct nu_emac_lwip_pbuf), "EMAC0 RX PBUF pool");
#endif

#if defined(BSP_USING_EMAC1)
    LWIP_MEMPOOL_DECLARE(emac1_rx, EMAC_RX_DESC_SIZE, sizeof(struct nu_emac_lwip_pbuf), "EMAC1 RX PBUF pool");
#endif

static struct nu_emac nu_emac_arr[] =
{
#if defined(BSP_USING_EMAC0)
    {
        .name            =  "e0",
        .memmgr.psEmac   = (EMAC_T *)EMC0_BA,
        .irqn_tx         =  IRQ_EMC0_TX,
        .irqn_rx         =  IRQ_EMC0_RX,
        .rstidx          =  EMAC0RST,
        .clkidx          =  EMAC0CKEN,
        .memp_rx_pool    =  &memp_emac0_rx
    },
#endif
#if defined(BSP_USING_EMAC1)
    {
        .name           =  "e1",
        .memmgr.psEmac  = (EMAC_T *)EMC1_BA,
        .irqn_tx        =  IRQ_EMC1_TX,
        .irqn_rx        =  IRQ_EMC1_RX,
        .rstidx         =  EMAC1RST,
        .clkidx         =  EMAC1CKEN,
        .memp_rx_pool   =  &memp_emac1_rx
    },
#endif
};

#if defined(NU_EMAC_RX_DUMP) ||  defined(NU_EMAC_TX_DUMP)
static void nu_emac_pkt_dump(const char *msg, const struct pbuf *p)
{
    rt_uint32_t i;
    rt_uint8_t *ptr = p->payload;

    NU_EMAC_TRACE("%s %d byte\n", msg, p->tot_len);

    for (i = 0; i < p->tot_len; i++)
    {
        if ((i % 8) == 0)
        {
            NU_EMAC_TRACE("  ");
        }
        if ((i % 16) == 0)
        {
            NU_EMAC_TRACE("\r\n");
        }
        NU_EMAC_TRACE("%02x ", *ptr);
        ptr++;
    }
    NU_EMAC_TRACE("\n\n");
}
#endif /* dump */

static void nu_emac_halt(nu_emac_t psNuEmac)
{
    EMAC_T *EMAC = psNuEmac->memmgr.psEmac;
    EMAC_DISABLE_RX(EMAC);
    EMAC_DISABLE_TX(EMAC);
}

static void *nu_emac_memcpy(void *dest, void *src, unsigned int count)
{
    return rt_memcpy(dest, src, count);
}

static void nu_emac_reinit(nu_emac_t psNuEmac)
{
    rt_uint32_t EMAC_CAMxM[EMAC_CAMENTRY_NB];
    rt_uint32_t EMAC_CAMxL[EMAC_CAMENTRY_NB];
    rt_uint32_t EMAC_CAMEN;
    EMAC_T *EMAC = psNuEmac->memmgr.psEmac;

    // Backup MAC address.
    EMAC_CAMEN = EMAC->CAMEN;
    for (rt_uint8_t index = 0 ; index < EMAC_CAMENTRY_NB; index ++)
    {
        rt_uint32_t *CAMxM = (rt_uint32_t *)((rt_uint32_t)&EMAC->CAM0M + (index * 8));
        rt_uint32_t *CAMxL = (rt_uint32_t *)((rt_uint32_t)&EMAC->CAM0L + (index * 8));

        EMAC_CAMxM[index] = *CAMxM;
        EMAC_CAMxL[index] = *CAMxL;
    }

    nu_emac_halt(psNuEmac);
    EMAC_Close(EMAC);
    EMAC_Open(&psNuEmac->memmgr, (uint8_t *)&psNuEmac->mac_addr[0]);
    EMAC_ENABLE_TX(EMAC);
    EMAC_ENABLE_RX(EMAC);

    // Restore MAC address.
    for (rt_uint8_t index = 0 ; index < EMAC_CAMENTRY_NB; index ++)
    {
        rt_uint32_t *CAMxM = (rt_uint32_t *)((rt_uint32_t)&EMAC->CAM0M + (index * 8));
        rt_uint32_t *CAMxL = (rt_uint32_t *)((rt_uint32_t)&EMAC->CAM0L + (index * 8));

        *CAMxM = EMAC_CAMxM[index];
        *CAMxL = EMAC_CAMxL[index];
    }
    EMAC->CAMEN = EMAC_CAMEN;
}

#if LWIP_IPV4 && LWIP_IGMP
static err_t nu_igmp_mac_filter(struct netif *netif, const ip4_addr_t *ip4_addr, enum netif_mac_filter_action action)
{
    nu_emac_t psNuEmac = (nu_emac_t)netif->state;
    rt_uint8_t mac[6];
    int32_t ret = 0;
    const uint8_t *p = (const uint8_t *)ip4_addr;

    mac[0] = 0x01;
    mac[1] = 0x00;
    mac[2] = 0x5E;
    mac[3] = *(p + 1) & 0x7F;
    mac[4] = *(p + 2);
    mac[5] = *(p + 3);

    ret = EMAC_FillCamEntry(psNuEmac->memmgr.psEmac, (uint8_t *)&mac[0]);
    if (ret >= 0)
    {
        NU_EMAC_TRACE("%s %s %s ", __FUNCTION__, (action == NETIF_ADD_MAC_FILTER) ? "add" : "del", ip4addr_ntoa(ip4_addr));
        NU_EMAC_TRACE("%02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    }

    return (ret >= 0) ? RT_EOK : -(RT_ERROR);
}
#endif /* LWIP_IPV4 && LWIP_IGMP */

static void link_monitor(void *param)
{
    nu_emac_t psNuEmac = (nu_emac_t)param;
    EMAC_T *EMAC = psNuEmac->memmgr.psEmac;
    uint32_t LinkStatus_Last = EMAC_LINK_DOWN;

    EMAC_PhyInit(EMAC);

    while (1)
    {
        uint32_t LinkStatus_Current = EMAC_CheckLinkStatus(EMAC);
        /* linkchange */
        if (LinkStatus_Last != LinkStatus_Current)
        {

            switch (LinkStatus_Current)
            {
            case EMAC_LINK_DOWN:
                NU_EMAC_TRACE("[%s] Link status: Down\n", psNuEmac->name);
                break;

            case EMAC_LINK_100F:
                NU_EMAC_TRACE("[%s] Link status: 100F\n", psNuEmac->name);
                break;

            case EMAC_LINK_100H:
                NU_EMAC_TRACE("[%s] Link status: 100H\n", psNuEmac->name);
                break;

            case EMAC_LINK_10F:
                NU_EMAC_TRACE("[%s] Link status: 10F\n", psNuEmac->name);
                break;

            case EMAC_LINK_10H:
                NU_EMAC_TRACE("[%s] Link status: 10H\n", psNuEmac->name);
                break;
            } /* switch( LinkStatus_Current ) */

            /* Send link status to upper layer. */
            if (LinkStatus_Current == EMAC_LINK_DOWN)
            {
                eth_device_linkchange(&psNuEmac->eth, RT_FALSE);
            }
            else
            {
                eth_device_linkchange(&psNuEmac->eth, RT_TRUE);
            }
            LinkStatus_Last = LinkStatus_Current;

        } /* if ( LinkStatus_Last != LinkStatus_Current ) */

        rt_thread_delay(RT_TICK_PER_SECOND);

    } /* while(1) */

}

static void nu_memmgr_init(EMAC_MEMMGR_T *psMemMgr)
{
    psMemMgr->u32TxDescSize = EMAC_TX_DESC_SIZE;
    psMemMgr->u32RxDescSize = EMAC_RX_DESC_SIZE;

    psMemMgr->psTXDescs = (EMAC_DESCRIPTOR_T *) rt_malloc_align(sizeof(EMAC_DESCRIPTOR_T) * psMemMgr->u32TxDescSize, 32);
    RT_ASSERT(psMemMgr->psTXDescs != RT_NULL);

    psMemMgr->psRXDescs = (EMAC_DESCRIPTOR_T *) rt_malloc_align(sizeof(EMAC_DESCRIPTOR_T) * psMemMgr->u32RxDescSize, 32);
    RT_ASSERT(psMemMgr->psRXDescs != RT_NULL);

    psMemMgr->psTXFrames = (EMAC_FRAME_T *) rt_malloc_align(sizeof(EMAC_FRAME_T) * psMemMgr->u32TxDescSize, 32);
    RT_ASSERT(psMemMgr->psTXFrames != RT_NULL);

    psMemMgr->psRXFrames = (EMAC_FRAME_T *) rt_malloc_align(sizeof(EMAC_FRAME_T) * psMemMgr->u32RxDescSize, 32);
    RT_ASSERT(psMemMgr->psRXFrames != RT_NULL);
}

static rt_err_t nu_emac_init(rt_device_t dev)
{
    nu_emac_t psNuEmac = (nu_emac_t)dev;
    EMAC_T *EMAC = psNuEmac->memmgr.psEmac;
    char szTmp[16];
    rt_err_t ret = RT_EOK;

    nu_memmgr_init(&psNuEmac->memmgr);

    snprintf(szTmp, sizeof(szTmp), "%sphy", psNuEmac->name);

    ret = rt_sem_init(&psNuEmac->eth_sem, "eth_sem", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(ret == RT_EOK);

    EMAC_Reset(EMAC);

    EMAC_Close(EMAC);
    EMAC_Open(&psNuEmac->memmgr, (uint8_t *)&psNuEmac->mac_addr[0]);

#if defined(BSP_USING_MMU)
    mmu_clean_invalidated_dcache((uint32_t)psNuEmac->memmgr.psTXDescs, sizeof(EMAC_DESCRIPTOR_T)*psNuEmac->memmgr.u32TxDescSize);
    mmu_clean_invalidated_dcache((uint32_t)psNuEmac->memmgr.psRXDescs, sizeof(EMAC_DESCRIPTOR_T)*psNuEmac->memmgr.u32RxDescSize);
#endif

    EMAC_ENABLE_RX(EMAC);
    EMAC_ENABLE_TX(EMAC);

    EMAC_TRIGGER_RX(EMAC);

#if defined(LWIP_IPV4) && defined(LWIP_IGMP)
    netif_set_igmp_mac_filter(psNuEmac->eth.netif, nu_igmp_mac_filter);
#endif /* LWIP_IPV4 && LWIP_IGMP */

    psNuEmac->link_monitor =  rt_thread_create((const char *)szTmp,
                              link_monitor,
                              (void *)psNuEmac,
                              NU_EMAC_TID_STACK_SIZE,
                              RT_THREAD_PRIORITY_MAX - 2,
                              10);
    RT_ASSERT(psNuEmac->link_monitor != RT_NULL);

    ret = rt_thread_startup(psNuEmac->link_monitor);
    RT_ASSERT(ret == RT_EOK);

    return RT_EOK;
}

static rt_err_t nu_emac_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t nu_emac_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t nu_emac_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t nu_emac_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t nu_emac_control(rt_device_t dev, int cmd, void *args)
{
    nu_emac_t psNuEMAC = (nu_emac_t)dev;
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* Get MAC address */
        if (args)
            rt_memcpy(args, &psNuEMAC->mac_addr[0], 6);
        else
            return -RT_ERROR;

        break;
    default :
        break;
    }

    return RT_EOK;
}

static rt_err_t nu_emac_tx(rt_device_t dev, struct pbuf *p)
{
    nu_emac_t psNuEmac = (nu_emac_t)dev;
    EMAC_T *EMAC = psNuEmac->memmgr.psEmac;
    struct pbuf *q;
    rt_uint32_t offset = 0;
    rt_uint8_t *buf;

    buf = (rt_uint8_t *)EMAC_ClaimFreeTXBuf(&psNuEmac->memmgr);
    /* Get free TX buffer */
    if (buf == RT_NULL)
    {
        rt_err_t result;

        result = rt_sem_control(&psNuEmac->eth_sem, RT_IPC_CMD_RESET, 0);
        RT_ASSERT(result != RT_EOK);

        EMAC_CLEAR_INT_FLAG(EMAC, EMAC_INTSTS_TXCPIF_Msk);
        EMAC_ENABLE_INT(EMAC, EMAC_INTEN_TXCPIEN_Msk);

        do
        {
            result = rt_sem_take(&psNuEmac->eth_sem, 10);
            buf = (rt_uint8_t *)EMAC_ClaimFreeTXBuf(&psNuEmac->memmgr);
        }
        while (buf == RT_NULL);
    }

    for (q = p; q != NULL; q = q->next)
    {
        rt_uint8_t *ptr;
        rt_uint32_t len;

        len = q->len;
        ptr = q->payload;

        nu_emac_memcpy(&buf[offset], ptr, len);

        offset += len;
    }

#if defined(NU_EMAC_TX_DUMP)
    nu_emac_pkt_dump("TX dump", p);
#endif

    /* Return SUCCESS? */
    return (EMAC_SendPktWoCopy(&psNuEmac->memmgr, offset) == 1) ? RT_EOK : RT_ERROR;
}

void nu_emac_pbuf_free(struct pbuf *p)
{
    nu_emac_lwip_pbuf_t my_buf = (nu_emac_lwip_pbuf_t)p;

    SYS_ARCH_DECL_PROTECT(old_level);
    SYS_ARCH_PROTECT(old_level);

    //rt_kprintf("%08x %08x\n",my_buf, my_buf->rx_desc);

    /* Update RX descriptor & trigger */
    EMAC_RxTrigger(my_buf->psMemMgr, my_buf->rx_desc);

    memp_free_pool(my_buf->memp_rx_pool, my_buf);
    SYS_ARCH_UNPROTECT(old_level);
}

static struct pbuf *nu_emac_rx(rt_device_t dev)
{
    nu_emac_t psNuEmac = (nu_emac_t)dev;
    struct pbuf *p = RT_NULL;
    uint8_t *pu8DataBuf = NULL;
    unsigned int avaialbe_size;
    EMAC_T *EMAC = psNuEmac->memmgr.psEmac;

    /* Check available data. */
    if ((avaialbe_size = EMAC_GetAvailRXBufSize(&psNuEmac->memmgr, &pu8DataBuf)) > 0)
    {
        EMAC_DESCRIPTOR_T *cur_rx = EMAC_RecvPktDoneWoRxTrigger(&psNuEmac->memmgr);
        nu_emac_lwip_pbuf_t my_pbuf  = (nu_emac_lwip_pbuf_t)memp_malloc_pool(psNuEmac->memp_rx_pool);
        if (my_pbuf != RT_NULL)
        {

            my_pbuf->p.custom_free_function = nu_emac_pbuf_free;
            my_pbuf->psPktFrameDataBuf      = (EMAC_FRAME_T *)pu8DataBuf;
            my_pbuf->rx_desc                = cur_rx;
            my_pbuf->psMemMgr               = &psNuEmac->memmgr;
            my_pbuf->memp_rx_pool           = psNuEmac->memp_rx_pool;

#if defined(BSP_USING_MMU)
            mmu_invalidate_dcache((rt_uint32_t)pu8DataBuf, (rt_uint32_t)avaialbe_size);
#endif
            //rt_kprintf("%08x, %08x, %d\n", my_pbuf, cur_rx, avaialbe_size);
            p = pbuf_alloced_custom(PBUF_RAW,
                                    avaialbe_size,
                                    PBUF_REF,
                                    &my_pbuf->p,
                                    pu8DataBuf,
                                    EMAC_MAX_PKT_SIZE);
            if (p == RT_NULL)
            {
                rt_kprintf("%s : failed to alloted %08x\n", __func__, p);
                EMAC_RxTrigger(&psNuEmac->memmgr, cur_rx);
            }
        }
        else
        {
            rt_kprintf("LWIP_MEMPOOL_ALLOC < 0!!\n");
            EMAC_RxTrigger(&psNuEmac->memmgr, cur_rx);
        }
    }
    else    /* If it hasn't RX packet, it will enable interrupt. */
    {
        /* No available RX packet, we enable RXGD/RDUIEN interrupts. */
        if (!(EMAC->INTEN & EMAC_INTEN_RDUIEN_Msk))
        {
            EMAC_CLEAR_INT_FLAG(EMAC, (EMAC_INTSTS_RDUIF_Msk | EMAC_INTSTS_RXGDIF_Msk));
            EMAC_ENABLE_INT(EMAC, (EMAC_INTEN_RDUIEN_Msk | EMAC_INTEN_RXGDIEN_Msk));
        }
        else
        {
            EMAC_CLEAR_INT_FLAG(EMAC, EMAC_INTSTS_RXGDIF_Msk);
            EMAC_ENABLE_INT(EMAC, EMAC_INTEN_RXGDIEN_Msk);
        }
    }

    return p;
}

static void nu_emac_rx_isr(int vector, void *param)
{
    nu_emac_t psNuEmac = (nu_emac_t)param;
    EMAC_T *EMAC = psNuEmac->memmgr.psEmac;

    unsigned int status = EMAC->INTSTS & 0xFFFF;

    /* No RX descriptor available, we need to get data from RX pool */
    if (EMAC_GET_INT_FLAG(EMAC, EMAC_INTSTS_RDUIF_Msk))
    {
        EMAC_DISABLE_INT(EMAC, (EMAC_INTEN_RDUIEN_Msk | EMAC_INTEN_RXGDIEN_Msk));
        eth_device_ready(&psNuEmac->eth);
    }
    /* A good packet ready. */
    else if (EMAC_GET_INT_FLAG(EMAC, EMAC_INTSTS_RXGDIF_Msk))
    {
        EMAC_DISABLE_INT(EMAC, EMAC_INTEN_RXGDIEN_Msk);
        eth_device_ready(&psNuEmac->eth);
    }

    /* Receive Bus Error Interrupt */
    if (EMAC_GET_INT_FLAG(EMAC, EMAC_INTSTS_RXBEIF_Msk))
    {
        NU_EMAC_TRACE("Reinit Rx EMAC\n");
        EMAC_CLEAR_INT_FLAG(EMAC, EMAC_INTSTS_RXBEIF_Msk);
        nu_emac_reinit(psNuEmac);
    }

    EMAC->INTSTS = status;
}

static void nu_emac_tx_isr(int vector, void *param)
{
    nu_emac_t psNuEmac = (nu_emac_t)param;
    EMAC_T *EMAC = psNuEmac->memmgr.psEmac;
    rt_err_t result = RT_EOK;

    unsigned int status = EMAC->INTSTS & 0xFFFF0000;

    /* Wake-up suspended process to send */
    if (EMAC_GET_INT_FLAG(EMAC, EMAC_INTSTS_TXCPIF_Msk))
    {
        EMAC_DISABLE_INT(EMAC, EMAC_INTEN_TXCPIEN_Msk);

        result = rt_sem_release(&psNuEmac->eth_sem);
        RT_ASSERT(result == RT_EOK);
    }

    if (EMAC_GET_INT_FLAG(EMAC, EMAC_INTSTS_TXBEIF_Msk))
    {
        NU_EMAC_TRACE("Reinit Tx EMAC\n");
        nu_emac_reinit(psNuEmac);
    }
    else
        EMAC_SendPktDone(&psNuEmac->memmgr);

    EMAC->INTSTS = status;
}

static void rt_hw_nu_emac_assign_macaddr(nu_emac_t psNuEMAC)
{
    static rt_uint32_t value = 0x94539453;

    /* Assign MAC address */
    psNuEMAC->mac_addr[0] = 0x82;
    psNuEMAC->mac_addr[1] = 0x06;
    psNuEMAC->mac_addr[2] = 0x21;
    psNuEMAC->mac_addr[3] = (value >> 16) & 0xff;
    psNuEMAC->mac_addr[4] = (value >> 8) & 0xff;
    psNuEMAC->mac_addr[5] = (value) & 0xff;

    NU_EMAC_TRACE("MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n", \
                  psNuEMAC->mac_addr[0], \
                  psNuEMAC->mac_addr[1], \
                  psNuEMAC->mac_addr[2], \
                  psNuEMAC->mac_addr[3], \
                  psNuEMAC->mac_addr[4], \
                  psNuEMAC->mac_addr[5]);
    value++;
}

static int rt_hw_nu_emac_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;
    char szTmp[32];

    /* MDC CLK divider */
    outpw(REG_CLK_DIVCTL8, (inpw(REG_CLK_DIVCTL8) & ~0xFF) | 0xA0);

    for (i = (EMAC_START + 1); i < EMAC_CNT; i++)
    {
        nu_emac_t psNuEMAC = (nu_emac_t)&nu_emac_arr[i];

        nu_sys_ipclk_enable(psNuEMAC->clkidx);

        nu_sys_ip_reset(psNuEMAC->rstidx);

        rt_hw_nu_emac_assign_macaddr(psNuEMAC);

        /* Register member functions */
        psNuEMAC->eth.parent.init       = nu_emac_init;
        psNuEMAC->eth.parent.open       = nu_emac_open;
        psNuEMAC->eth.parent.close      = nu_emac_close;
        psNuEMAC->eth.parent.read       = nu_emac_read;
        psNuEMAC->eth.parent.write      = nu_emac_write;
        psNuEMAC->eth.parent.control    = nu_emac_control;
        psNuEMAC->eth.parent.user_data  = psNuEMAC;
        psNuEMAC->eth.eth_rx            = nu_emac_rx;
        psNuEMAC->eth.eth_tx            = nu_emac_tx;

        snprintf(szTmp, sizeof(szTmp), "%s_tx", psNuEMAC->name);
        rt_hw_interrupt_install(psNuEMAC->irqn_tx, nu_emac_tx_isr, (void *)psNuEMAC, szTmp);
        rt_hw_interrupt_umask(psNuEMAC->irqn_tx);

        snprintf(szTmp, sizeof(szTmp), "%s_rx", psNuEMAC->name);
        rt_hw_interrupt_install(psNuEMAC->irqn_rx, nu_emac_rx_isr, (void *)psNuEMAC, szTmp);
        rt_hw_interrupt_umask(psNuEMAC->irqn_rx);

        /* Initial zero_copy rx pool */
        memp_init_pool(psNuEMAC->memp_rx_pool);

        /* Register eth device */
        ret = eth_device_init(&psNuEMAC->eth, psNuEMAC->name);
        RT_ASSERT(ret == RT_EOK);
    }

    return 0;
}

INIT_APP_EXPORT(rt_hw_nu_emac_init);


#if 0
/*
    Remeber src += lwipiperf_SRCS in components\net\lwip-*\SConscript
*/
#include "lwip/apps/lwiperf.h"

static void
lwiperf_report(void *arg, enum lwiperf_report_type report_type,
               const ip_addr_t *local_addr, u16_t local_port, const ip_addr_t *remote_addr, u16_t remote_port,
               u32_t bytes_transferred, u32_t ms_duration, u32_t bandwidth_kbitpsec)
{
    LWIP_UNUSED_ARG(arg);
    LWIP_UNUSED_ARG(local_addr);
    LWIP_UNUSED_ARG(local_port);

    rt_kprintf("IPERF report: type=%d, remote: %s:%d, total bytes: %"U32_F", duration in ms: %"U32_F", kbits/s: %"U32_F"\n",
               (int)report_type, ipaddr_ntoa(remote_addr), (int)remote_port, bytes_transferred, ms_duration, bandwidth_kbitpsec);
}

void lwiperf_example_init(int argc, char **argv)
{
    lwiperf_start_tcp_server_default(lwiperf_report, NULL);
}
MSH_CMD_EXPORT(lwiperf_example_init, start lwip tcp server);
#endif

#endif /* #if defined( BSP_USING_EMAC ) && defined( RT_USING_LWIP )*/
