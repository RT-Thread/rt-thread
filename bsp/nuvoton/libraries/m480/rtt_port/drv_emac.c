/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-2-7        Wayne            First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_EMAC)

#if defined(RT_USING_LWIP)

#include <rtdevice.h>
#include <NuMicro.h>
#include <netif/ethernetif.h>
#include <netif/etharp.h>
#include <lwip/icmp.h>
#include "lwipopts.h"


#include "drv_pdma.h"

/* Private define ---------------------------------------------------------------*/
// RT_DEV_NAME_PREFIX e

#if !defined(NU_EMAC_PDMA_MEMCOPY)
    #define NU_EMAC_PDMA_MEMCOPY
#endif

#if !defined(NU_EMAC_PDMA_MEMCOPY_THRESHOLD)
    #define NU_EMAC_PDMA_MEMCOPY_THRESHOLD  128
#endif

#define NU_EMAC_DEBUG
#if defined(NU_EMAC_DEBUG)
    //      #define NU_EMAC_RX_DUMP
    //      #define NU_EMAC_TX_DUMP
    #define NU_EMAC_TRACE         rt_kprintf
#else
    #define NU_EMAC_TRACE(...)
#endif

#define NU_EMAC_TID_STACK_SIZE  256

/* Private typedef --------------------------------------------------------------*/
struct nu_emac
{
    struct eth_device   eth;
    rt_uint8_t   mac_addr[6];
    struct rt_semaphore eth_sem;
};
typedef struct nu_emac *nu_emac_t;

/* Private functions ------------------------------------------------------------*/
#if defined(NU_EMAC_RX_DUMP) || defined(NU_EMAC_TX_DUMP)
    static void nu_emac_pkt_dump(const char *msg, const struct pbuf *p);
#endif
#if LWIP_IPV4 && LWIP_IGMP
    static err_t nu_igmp_mac_filter(struct netif *netif, const ip4_addr_t *ip4_addr, enum netif_mac_filter_action action);
#endif
static void nu_emac_halt(void);
static void nu_emac_reinit(void);
static void link_monitor(void *param);
static rt_err_t nu_emac_init(rt_device_t dev);

static rt_err_t nu_emac_open(rt_device_t dev, rt_uint16_t oflag);
static rt_err_t nu_emac_close(rt_device_t dev);
static rt_size_t nu_emac_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
static rt_size_t nu_emac_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
static rt_err_t nu_emac_control(rt_device_t dev, int cmd, void *args);
static rt_err_t nu_emac_tx(rt_device_t dev, struct pbuf *p);
static struct pbuf *nu_emac_rx(rt_device_t dev);
static rt_err_t rt_hw_nu_emac_register(char *dev_name);
static int rt_hw_nu_emac_init(void);
static void *nu_emac_memcpy(void *dest, void *src, unsigned int count);

/* Public functions -------------------------------------------------------------*/

/* Private variables ------------------------------------------------------------*/
static struct nu_emac nu_emac_dev = {0};
static struct rt_thread eth_tid;
static rt_uint8_t eth_stack[NU_EMAC_TID_STACK_SIZE];

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

static void nu_emac_halt(void)
{
    EMAC_DISABLE_RX();
    EMAC_DISABLE_TX();
}

static void *nu_emac_memcpy(void *dest, void *src, unsigned int count)
{
#if defined(NU_EMAC_PDMA_MEMCOPY)
    if (count >= NU_EMAC_PDMA_MEMCOPY_THRESHOLD)
        return nu_pdma_memcpy(dest, src, count);
#endif
    return memcpy(dest, src, count);
}

static void nu_emac_reinit(void)
{
    rt_uint32_t EMAC_CAMxM[EMAC_CAMENTRY_NB];
    rt_uint32_t EMAC_CAMxL[EMAC_CAMENTRY_NB];
    rt_uint32_t EMAC_CAMEN;

    // Backup MAC address.
    EMAC_CAMEN = EMAC->CAMEN;
    for (rt_uint8_t index = 0 ; index < EMAC_CAMENTRY_NB; index ++)
    {
        rt_uint32_t *CAMxM = (rt_uint32_t *)((rt_uint32_t)&EMAC->CAM0M + (index * 8));
        rt_uint32_t *CAMxL = (rt_uint32_t *)((rt_uint32_t)&EMAC->CAM0L + (index * 8));

        EMAC_CAMxM[index] = *CAMxM;
        EMAC_CAMxL[index] = *CAMxL;
    }

    nu_emac_halt();
    EMAC_Close();
    EMAC_Open((uint8_t *)&nu_emac_dev.mac_addr[0]);
    EMAC_ENABLE_TX();
    EMAC_ENABLE_RX();

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
    rt_uint8_t mac[6];
    int32_t ret = 0;
    const uint8_t *p = (const uint8_t *)ip4_addr;

    mac[0] = 0x01;
    mac[1] = 0x00;
    mac[2] = 0x5E;
    mac[3] = *(p + 1) & 0x7F;
    mac[4] = *(p + 2);
    mac[5] = *(p + 3);

    ret = EMAC_FillCamEntry((uint8_t *)&mac[0]);
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
    nu_emac_t psNuEMAC = (nu_emac_t)param;
    uint32_t LinkStatus_Last = EMAC_LINK_DOWN;

    EMAC_PhyInit();

    while (1)
    {
        uint32_t LinkStatus_Current = EMAC_CheckLinkStatus();
        /* linkchange */
        if (LinkStatus_Last != LinkStatus_Current)
        {

            switch (LinkStatus_Current)
            {
            case EMAC_LINK_DOWN:
                NU_EMAC_TRACE("Link status: Down\n");
                break;

            case EMAC_LINK_100F:
                NU_EMAC_TRACE("Link status: 100F\n");
                break;

            case EMAC_LINK_100H:
                NU_EMAC_TRACE("Link status: 100H\n");
                break;

            case EMAC_LINK_10F:
                NU_EMAC_TRACE("Link status: 10F\n");
                break;

            case EMAC_LINK_10H:
                NU_EMAC_TRACE("Link status: 10H\n");
                break;
            } /* switch( LinkStatus_Current ) */

            /* Send link status to upper layer. */
            if (LinkStatus_Current == EMAC_LINK_DOWN)
                eth_device_linkchange(&psNuEMAC->eth, RT_FALSE);
            else
                eth_device_linkchange(&psNuEMAC->eth, RT_TRUE);

            LinkStatus_Last = LinkStatus_Current;

        } /* if ( LinkStatus_Last != LinkStatus_Current ) */

        rt_thread_delay(RT_TICK_PER_SECOND);

    } /* while(1) */

}

static rt_err_t nu_emac_init(rt_device_t dev)
{
    nu_emac_t psNuEMAC = (nu_emac_t)dev;

    EMAC_Close();
    EMAC_Open((uint8_t *)&psNuEMAC->mac_addr[0]);
    EMAC_ENABLE_RX();
    EMAC_ENABLE_TX();

    NVIC_SetPriority(EMAC_TX_IRQn, 1);
    NVIC_EnableIRQ(EMAC_TX_IRQn);
    NVIC_SetPriority(EMAC_RX_IRQn, 1);
    NVIC_EnableIRQ(EMAC_RX_IRQn);

    rt_sem_init(&psNuEMAC->eth_sem, "eth_sem", 0, RT_IPC_FLAG_FIFO);

    rt_thread_init(&eth_tid, "eth", link_monitor, (void *)psNuEMAC, eth_stack, sizeof(eth_stack), RT_THREAD_PRIORITY_MAX - 2, 10);
    rt_thread_startup(&eth_tid);

#if defined(LWIP_IPV4) && defined(LWIP_IGMP)
    netif_set_igmp_mac_filter(psNuEMAC->eth.netif, nu_igmp_mac_filter);
#endif /* LWIP_IPV4 && LWIP_IGMP */

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
    nu_emac_t psNuEMAC = (nu_emac_t)dev;
    struct pbuf *q;
    rt_uint32_t offset = 0;

    rt_uint8_t *buf = (rt_uint8_t *)EMAC_ClaimFreeTXBuf();

    /* Get free TX buffer */
    if (buf == RT_NULL)
    {
        rt_sem_control(&psNuEMAC->eth_sem, RT_IPC_CMD_RESET, 0);

        EMAC_CLEAR_INT_FLAG(EMAC, EMAC_INTSTS_TXCPIF_Msk);
        EMAC_ENABLE_INT(EMAC, EMAC_INTEN_TXCPIEN_Msk);

        do
        {
            rt_sem_take(&psNuEMAC->eth_sem, 1);
            buf = (rt_uint8_t *)EMAC_ClaimFreeTXBuf();
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

    /* Return SUCCESS */
    return (EMAC_SendPktWoCopy(offset) == 1) ? RT_EOK : RT_ERROR;
}

static struct pbuf *nu_emac_rx(rt_device_t dev)
{
    struct pbuf *p = RT_NULL;
    uint8_t *pu8DataBuf = NULL;
    unsigned int avaialbe_size;

    if ((avaialbe_size = EMAC_GetAvailRXBufSize(&pu8DataBuf)) > 0)
    {
        /* Allocate RX packet buffer. */
        p = pbuf_alloc(PBUF_RAW, avaialbe_size, PBUF_RAM);
        if (p != RT_NULL)
        {
            RT_ASSERT(p->next == RT_NULL);
            nu_emac_memcpy((void *)p->payload, (void *)pu8DataBuf, avaialbe_size);

#if defined(NU_EMAC_RX_DUMP)
            nu_emac_pkt_dump("RX dump", p);
#endif
        }
        else
        {
            NU_EMAC_TRACE("Can't allocate memory for RX packet.(%d)\n", avaialbe_size);
        }

        /* Update RX descriptor */
        EMAC_RecvPktDoneWoRxTrigger();

    } // if ( (avaialbe_size= EMAC_GetAvaiableRXBufSize()) > 0 )
    else
    {
        /* No avaiable RX packet, we enable RXGD/RDUIEN interrupts. */
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
        EMAC_TRIGGER_RX();
    } //else

    return p;
}

void EMAC_RX_IRQHandler(void)
{
    /* Enter interrupt */
    rt_interrupt_enter();

    /* No RX descriptor avaiable, we need to get data from RX pool */
    if (EMAC_GET_INT_FLAG(EMAC, EMAC_INTSTS_RDUIF_Msk))
    {
        EMAC_DISABLE_INT(EMAC, (EMAC_INTEN_RDUIEN_Msk | EMAC_INTEN_RXGDIEN_Msk));
        eth_device_ready(&nu_emac_dev.eth);
    }
    /* A good packet ready. */
    else if (EMAC_GET_INT_FLAG(EMAC, EMAC_INTSTS_RXGDIF_Msk))
    {
        EMAC_DISABLE_INT(EMAC, EMAC_INTEN_RXGDIEN_Msk);
        eth_device_ready(&nu_emac_dev.eth);
    }

    /* Receive Bus Error Interrupt */
    if (EMAC_GET_INT_FLAG(EMAC, EMAC_INTSTS_RXBEIF_Msk))
    {
        NU_EMAC_TRACE("Reinit Rx EMAC\n");
        EMAC_CLEAR_INT_FLAG(EMAC, EMAC_INTSTS_RXBEIF_Msk);
        nu_emac_reinit();
    }

    /* Leave interrupt */
    rt_interrupt_leave();
}

void EMAC_TX_IRQHandler(void)
{
    /* Enter interrupt */
    rt_interrupt_enter();

    unsigned int status = EMAC->INTSTS;

    /* Wake-up suspended process to send */
    if (EMAC_GET_INT_FLAG(EMAC, EMAC_INTSTS_TXCPIF_Msk))
    {
        EMAC_DISABLE_INT(EMAC, EMAC_INTEN_TXCPIEN_Msk);
        rt_sem_release(&nu_emac_dev.eth_sem);
    }

    if (EMAC_GET_INT_FLAG(EMAC, EMAC_INTSTS_TXBEIF_Msk))
    {
        NU_EMAC_TRACE("Reinit Tx EMAC\n");
        EMAC->INTSTS = EMAC_INTSTS_TXBEIF_Msk;
        EMAC_CLEAR_INT_FLAG(EMAC, EMAC_INTSTS_TXBEIF_Msk);
        nu_emac_reinit();
    }
    else
        EMAC_SendPktDone();

    /* Leave interrupt */
    rt_interrupt_leave();
}

static rt_err_t rt_hw_nu_emac_register(char *dev_name)
{
    rt_uint32_t value = 0;
    nu_emac_t psNuEMAC = (nu_emac_t)&nu_emac_dev;

    /* Read UID from FMC */
    SYS_UnlockReg();
    FMC_Open();
    for (rt_uint8_t i = 0; i < 3; i++)
    {
        value += FMC_ReadUID(i);
    }
    FMC_Close();
    SYS_LockReg();

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

    /* Register member functions */
    psNuEMAC->eth.parent.init       = nu_emac_init;
    psNuEMAC->eth.parent.open       = nu_emac_open;
    psNuEMAC->eth.parent.close      = nu_emac_close;
    psNuEMAC->eth.parent.read       = nu_emac_read;
    psNuEMAC->eth.parent.write      = nu_emac_write;
    psNuEMAC->eth.parent.control    = nu_emac_control;
    psNuEMAC->eth.parent.user_data  = RT_NULL;
    psNuEMAC->eth.eth_rx     = nu_emac_rx;
    psNuEMAC->eth.eth_tx     = nu_emac_tx;

    /* Register eth device */
    return eth_device_init(&nu_emac_dev.eth, dev_name);
}

static int rt_hw_nu_emac_init(void)
{
    return rt_hw_nu_emac_register("e0");
}

INIT_APP_EXPORT(rt_hw_nu_emac_init);

#endif /* #if defined( RT_USING_LWIP ) */

#endif /* #if defined( BSP_USING_EMAC ) */
