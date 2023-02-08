/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-09     Carl        the first version
 */

#include "board.h"
#include <netif/ethernetif.h>
#include "lwipopts.h"
#include "ft_parameters.h"
#include "ft_gmac.h"
#include "ft_cache.h"
#include "ft_gmac_hw.h"
#include "ft_status.h"
#include "ft_io.h"
#include "drv_eth.h"

#ifdef BSP_USING_GMAC

#define LOG_TAG "drv.gmac"
#include <drv_log.h>

#define MAX_ADDR_LEN 6

#define LINK_THREAD_STACK_LENGTH 0x400

struct drv_gmac
{
    struct eth_device parent; /* inherit from ethernet device */
    Ft_Gmac_t Gmac;           /* Gmac driver */
#ifndef PHY_USING_INTERRUPT_MODE
    rt_timer_t poll_link_timer;
#endif
    rt_uint8_t *rx_buffer;             /* Buffer for RxDesc */
    rt_uint8_t *tx_buffer;             /* Buffer for TxDesc */
    uint32_t eth_speed;                /* eth_speed */
    uint32_t eth_mode;                 /* ETH_Duplex_Mode */
    rt_uint8_t dev_addr[MAX_ADDR_LEN]; /* MAC address  */
    struct rt_event link_event;

    struct rt_thread _link_thread;
    rt_uint8_t _link_thread_stack[LINK_THREAD_STACK_LENGTH];

    rt_thread_t _debug_tid;
};

static void rt_ft2004_status_check(void *Args, u32 MacPhyStatus);

//
#if defined(RAW_DATA_PRINT)
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
#endif

/**
 * @name: rt_gmacmem_create
 * @msg:  Initialize the Gmac TX/Rx Describe Memory 。
 * @param {*}
 * @return {*}
 */
static void rt_gmacmem_create(struct drv_gmac *pOsGmac)
{
    pOsGmac->rx_buffer = rt_calloc(1, RX_DESCNUM * GMAC_MAX_PACKET_SIZE);
    if (pOsGmac->rx_buffer == NULL)
    {
        LOG_E("rx_buffer Malloc is error ");
        RT_ASSERT(0)
    }

    pOsGmac->tx_buffer = rt_calloc(1, TX_DESCNUM * GMAC_MAX_PACKET_SIZE);
    if (pOsGmac->tx_buffer == NULL)
    {
        LOG_E("tx_buffer Malloc is error ");
        RT_ASSERT(0)
    }

    pOsGmac->Gmac.TxDesc = rt_calloc(1, TX_DESCNUM * sizeof(FGmac_DmaDesc_t));
    if (pOsGmac->Gmac.TxDesc == NULL)
    {
        LOG_E("TxDesc Malloc is error ");
        RT_ASSERT(0)
    }

    pOsGmac->Gmac.RxDesc = rt_calloc(1, RX_DESCNUM * sizeof(FGmac_DmaDesc_t) + 128);
    if (pOsGmac->Gmac.RxDesc == NULL)
    {
        LOG_E("RxDesc Malloc is error ");
        RT_ASSERT(0)
    }

#define ROUND_UP(x, align) (((long)(x) + ((long)align - 1)) & \
                            ~((long)align - 1))

    pOsGmac->Gmac.RxDesc = (FGmac_DmaDesc_t *)ROUND_UP(pOsGmac->Gmac.RxDesc, 128);
    LOG_D("RxDesc fit after addr %x ", pOsGmac->Gmac.RxDesc);
}

static void rt_gmacmem_free(struct drv_gmac *pOsGmac)
{
    if (pOsGmac->rx_buffer)
    {
        rt_free(pOsGmac->rx_buffer);
    }

    if (pOsGmac->tx_buffer)
    {
        rt_free(pOsGmac->tx_buffer);
    }

    if (pOsGmac->Gmac.RxDesc)
    {
        rt_free(pOsGmac->Gmac.RxDesc);
    }

    if (pOsGmac->Gmac.TxDesc)
    {
        rt_free(pOsGmac->Gmac.TxDesc);
    }
}

static void rt_hw_gmac_isr(int irqno, void *param)
{
    FGmac_IntrHandler(param);
}

static void rt_hw_gmac_recv_isr(void *Args)
{
    struct drv_gmac *pOsMac;
    rt_err_t result = 0;

    if (RT_NULL == Args)
    {
        LOG_E("Args is NULL");
        return;
    }

    pOsMac = (struct drv_gmac *)Args;
    result = eth_device_ready(&(pOsMac->parent));
    if (result != RT_EOK)
    {
        LOG_I("RxCpltCallback err = %d", result);
    }
}

static rt_err_t
rt_ft2004_gmac_start(struct drv_gmac *pOsMac)
{
    Ft_Gmac_t *pGmac;
    pGmac = &pOsMac->Gmac;

    if (FST_SUCCESS != Ft_Gmac_HwInitialize(pGmac))
    {
        return -RT_ERROR;
    }

    FGmac_SetHandler(pGmac, FT_GMAC_RX_COMPLETE_CB_ID, rt_hw_gmac_recv_isr, pOsMac);
    FGmac_SetHandler(pGmac, FT_GMAC_MAC_PHY_STATUS_CB_ID, rt_ft2004_status_check, pOsMac);

    /* Initialize Rx Description list : ring Mode */
    FGmac_DmaRxDescRingInit(pGmac, pGmac->RxDesc, pOsMac->rx_buffer, GMAC_MAX_PACKET_SIZE, RX_DESCNUM);

    /* Initialize Tx Description list : ring Mode */
    FGmac_DmaTxDescRingInit(pGmac, pGmac->TxDesc, pOsMac->tx_buffer, GMAC_MAX_PACKET_SIZE, TX_DESCNUM);

    Ft_Gmac_Start(pGmac);
    /* Gmac interrupt init */
    rt_hw_interrupt_install(pGmac->Config.IRQ_NUM, rt_hw_gmac_isr, pGmac, "Gmac");
    rt_hw_interrupt_umask(pGmac->Config.IRQ_NUM);
    return RT_EOK;
}

void rt_ft2004_gmac_stop(struct drv_gmac *pOsMac)
{
    Ft_Gmac_t *pGmac;
    pGmac = &pOsMac->Gmac;
    Ft_Gmac_Stop(pGmac);
}

/* GMAC initialization function */
static rt_err_t rt_ft2004_gmac_init(rt_device_t dev)
{
    struct drv_gmac *pOsMac;
    struct eth_device *pGmacParent;
    FGmac_Config_t *pConfig;

    pGmacParent = rt_container_of(dev, struct eth_device, parent);
    if (NULL == pGmacParent)
    {
        return -RT_ENOMEM;
    }

    pOsMac = rt_container_of(pGmacParent, struct drv_gmac, parent);
    if (NULL == pOsMac)
    {
        return -RT_ENOMEM;
    }

    pConfig = Ft_Gmac_LookupConfig(pOsMac->Gmac.Config.InstanceId);
    if (NULL == pConfig)
    {
        return -RT_ENOMEM;
    }

    Ft_Gmac_UseDefaultMacAddr(&pOsMac->Gmac, pOsMac->Gmac.Config.MacAddr);

    if (FST_SUCCESS != Ft_GmacCfgInitialize(&pOsMac->Gmac, pConfig))
    {
        return -RT_ERROR;
    }

    return rt_ft2004_gmac_start(pOsMac);
}

static rt_err_t rt_ft2004_gmac_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("gmac open");
    return RT_EOK;
}

static rt_err_t rt_ft2004_gmac_close(rt_device_t dev)
{
    LOG_D("gmac close");
    return RT_EOK;
}

static rt_ssize_t rt_ft2004_gmac_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("gmac read");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_ft2004_gmac_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    LOG_D("gmac write");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_ft2004_gmac_control(rt_device_t dev, int cmd, void *args)
{

    struct drv_gmac *pOsMac;
    struct eth_device *pGmacParent;

    pGmacParent = rt_container_of(dev, struct eth_device, parent);
    if (NULL == pGmacParent)
    {
        return -RT_ENOMEM;
    }

    pOsMac = rt_container_of(pGmacParent, struct drv_gmac, parent);
    if (NULL == pOsMac)
    {
        return -RT_ENOMEM;
    }

    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args)
            rt_memcpy(args, pOsMac->dev_addr, 6);
        else
            return -RT_ERROR;
        break;

    default:
        break;
    }

    return RT_EOK;
}

rt_err_t rt_ft2004_gmac_tx(rt_device_t dev, struct pbuf *p)
{
    struct drv_gmac *pOsMac;
    Ft_Gmac_t *pGmac;
    struct eth_device *pGmacParent;

    err_t errval;
    struct pbuf *q;
    u8 *Buffer = NULL;
    volatile FGmac_DmaDesc_t *DmaTxDesc;

    u32 FrameLength = 0;
    u32 BufferOffset = 0;
    u32 BytesLeftToCopy = 0;
    u32 PayLoadOffset = 0;

    pGmacParent = rt_container_of(dev, struct eth_device, parent);
    if (NULL == pGmacParent)
    {
        return -RT_ENOMEM;
    }

    pOsMac = rt_container_of(pGmacParent, struct drv_gmac, parent);
    if (NULL == pOsMac)
    {
        return -RT_ENOMEM;
    }

    pGmac = &pOsMac->Gmac;
    DmaTxDesc = &pGmac->TxDesc[pGmac->TxDescRingData.DescBufIndex];
    Buffer = (u8 *)DmaTxDesc->Buffer1Addr;

    if (Buffer == NULL)
    {
        LOG_E("Buffer is NULL \r\n");
        RT_ASSERT(0)
    }

#if RT_LWIP_ETH_PAD_SIZE
    pbuf_header(p, -RT_LWIP_ETH_PAD_SIZE); /* reclaim the padding word */
#endif

    for (q = p; q != NULL; q = q->next)
    {
        /* Is this buffer available? If not, goto error */
        if ((DmaTxDesc->Status & DMA_TDES0_OWN) != 0)
        {
            errval = ERR_USE;
            LOG_E("error errval = ERR_USE; \r\n");
            goto error;
        }

        /* Get bytes in current lwIP buffer */
        BytesLeftToCopy = q->len;
        PayLoadOffset = 0;
        /* Check if the length of data to copy is bigger than Tx buffer size*/
        while ((BytesLeftToCopy + BufferOffset) > GMAC_MAX_PACKET_SIZE)
        {
            /* Copy data to Tx buffer*/
            memcpy((u8 *)((u8 *)Buffer + BufferOffset), (u8 *)((u8 *)q->payload + PayLoadOffset), (GMAC_MAX_PACKET_SIZE - BufferOffset));
            FCache_cpuDcacheClean((rt_uint32_t *)DmaTxDesc->Buffer1Addr, GMAC_MAX_PACKET_SIZE);
            GMAC_INC_DESC(pGmac->TxDescRingData.DescBufIndex, pGmac->TxDescRingData.DescMaxNumber);
            /* Point to next descriptor */
            DmaTxDesc = &pGmac->TxDesc[pGmac->TxDescRingData.DescBufIndex];

            /* Check if the Bufferis available */
            if ((DmaTxDesc->Status & DMA_TDES0_OWN) != (u32)0)
            {
                errval = ERR_USE;
                LOG_E("Check if the Bufferis available \r\n");
                goto error;
            }

            Buffer = (u8 *)(DmaTxDesc->Buffer1Addr);
            BytesLeftToCopy = BytesLeftToCopy - (GMAC_MAX_PACKET_SIZE - BufferOffset);
            PayLoadOffset = PayLoadOffset + (GMAC_MAX_PACKET_SIZE - BufferOffset);
            FrameLength = FrameLength + (GMAC_MAX_PACKET_SIZE - BufferOffset);
            BufferOffset = 0;

            if (Buffer == NULL)
            {
                LOG_E(" error Buffer is 0 \r\n");
                RT_ASSERT(0)
            }
        }

        /* Copy the remaining bytes */
        memcpy((u8 *)((u8 *)Buffer + BufferOffset), (u8 *)((u8 *)q->payload + PayLoadOffset), BytesLeftToCopy);
        BufferOffset = BufferOffset + BytesLeftToCopy;
        FrameLength = FrameLength + BytesLeftToCopy;
    }
    /* 指向下一个位置 */
    FCache_cpuDcacheClean((rt_uint32_t *)DmaTxDesc->Buffer1Addr, GMAC_MAX_PACKET_SIZE);
    GMAC_INC_DESC(pGmac->TxDescRingData.DescBufIndex, pGmac->TxDescRingData.DescMaxNumber);
#if RT_LWIP_ETH_PAD_SIZE
    pbuf_header(p, RT_LWIP_ETH_PAD_SIZE); /* reclaim the padding word */
#endif

#ifdef ETH_TX_DUMP
    dump_hex(Buffer, p->tot_len);
#endif

    FGmac_TransmitframeRingPoll(pGmac, FrameLength);
error:
    FGmac_SetTransmitUnderflow(pGmac);
    return errval;
}

struct pbuf *rt_ft2004_gmac_rx(rt_device_t dev)
{
    struct drv_gmac *pOsMac;
    Ft_Gmac_t *pGmac;
    struct eth_device *pGmacParent;

    struct pbuf *p = NULL;
    struct pbuf *q = NULL;
    u16 Length = 0;
    u8 *Buffer;
    volatile FGmac_DmaDesc_t *DmaRxDesc;
    u32 BufferOffset = 0;
    u32 PayLoadOffset = 0;
    u32 BytesLeftToCopy = 0;
    u32 DescBufIndex; /* For Current Desc buffer buf position */

    pGmacParent = rt_container_of(dev, struct eth_device, parent);
    if (NULL == pGmacParent)
    {
        return RT_NULL;
    }

    pOsMac = rt_container_of(pGmacParent, struct drv_gmac, parent);
    if (NULL == pOsMac)
    {
        return RT_NULL;
    }

    pGmac = &pOsMac->Gmac;

    /* get received frame */
    if (FST_SUCCESS != FGmac_RingGetReceivedFrame_IT(pGmac))
    {
        return NULL;
    }

    DescBufIndex = pGmac->RxDescRingData.DescBufIndex;
    Length = (pGmac->RxDesc[DescBufIndex].Status & DMA_RDES0_FRAME_LEN_MASK) >> DMA_RDES0_FRAME_LEN_SHIFT;
    Buffer = (u8 *)pGmac->RxDesc[DescBufIndex].Buffer1Addr;

#if RT_LWIP_ETH_PAD_SIZE
    Length += RT_LWIP_ETH_PAD_SIZE; /* allow room for Ethernet padding */
#endif

    if (Length > 0)
    {
        /* We allocate a pbuf chain of pbufs from the Lwip buffer pool */
        p = pbuf_alloc(PBUF_RAW, Length, PBUF_POOL);
    }

#ifdef ETH_RX_DUMP
    dump_hex(Buffer, (u32)Length);
#endif

    if (p != NULL)
    {
#if RT_LWIP_ETH_PAD_SIZE
        pbuf_header(p, -RT_LWIP_ETH_PAD_SIZE); /* drop the padding word */
#endif
        DmaRxDesc = &pGmac->RxDesc[DescBufIndex];
        BufferOffset = 0;
        for (q = p; q != NULL; q = q->next)
        {
            BytesLeftToCopy = q->len;
            PayLoadOffset = 0;
            /* Check if the length of bytes to copy in current pbuf is bigger than Rx buffer size*/
            while ((BytesLeftToCopy + BufferOffset) > GMAC_MAX_PACKET_SIZE)
            {
                /* Copy data to pbuf */
                memcpy((u8 *)((u8 *)q->payload + PayLoadOffset), (u8 *)((u8 *)Buffer + BufferOffset), (GMAC_MAX_PACKET_SIZE - BufferOffset));

                /* Point to next descriptor */
                GMAC_INC_DESC(DescBufIndex, pGmac->RxDescRingData.DescMaxNumber);
                if (DescBufIndex == pGmac->RxDescRingData.DescIndex)
                {
                    break;
                }

                DmaRxDesc = &pGmac->RxDesc[DescBufIndex];
                Buffer = (u8 *)(DmaRxDesc->Buffer1Addr);

                BytesLeftToCopy = BytesLeftToCopy - (GMAC_MAX_PACKET_SIZE - BufferOffset);
                PayLoadOffset = PayLoadOffset + (GMAC_MAX_PACKET_SIZE - BufferOffset);
                BufferOffset = 0;
            }
            /* Copy remaining data in pbuf */
            memcpy((u8 *)((u8 *)q->payload + PayLoadOffset), (u8 *)((u8 *)Buffer + BufferOffset), BytesLeftToCopy);
            BufferOffset = BufferOffset + BytesLeftToCopy;
        }

#if RT_LWIP_ETH_PAD_SIZE
        pbuf_header(p, RT_LWIP_ETH_PAD_SIZE); /* reclaim the padding word */
#endif
    }

    /* Release descriptors to DMA */
    /* Point to first descriptor */
    DmaRxDesc = &pGmac->RxDesc[DescBufIndex];
    /* Set Own bit in Rx descriptors: gives the buffers back to DMA */
    for (DescBufIndex = pGmac->RxDescRingData.DescBufIndex; DescBufIndex != pGmac->RxDescRingData.DescIndex; GMAC_INC_DESC(DescBufIndex, pGmac->RxDescRingData.DescMaxNumber))
    {
        FCache_cpuDcacheInvalidate((rt_uint32_t *)pGmac->RxDesc[DescBufIndex].Buffer1Addr, GMAC_MAX_PACKET_SIZE);
        DmaRxDesc->Status |= DMA_RDES0_OWN;
        DmaRxDesc = &pGmac->RxDesc[DescBufIndex];
    }

    /* Sync index */
    pGmac->RxDescRingData.DescBufIndex = pGmac->RxDescRingData.DescIndex;
    FGmac_ResumeTransmissionReception(pGmac);

    return p;
}

static void rt_ft2004_status_check(void *Args, u32 MacPhyStatus)
{
    struct drv_gmac *pOsMac;
    pOsMac = (struct drv_gmac *)Args;

    if (MacPhyStatus & 0x8)
    {
        rt_event_send(&pOsMac->link_event, FT_NETIF_LINKUP);
    }
    else
    {
        rt_event_send(&pOsMac->link_event, FT_NETIF_DOWN);
    }
}

static void ethernet_link_thread(void *Args)
{
    struct drv_gmac *pOsMac;
    rt_uint32_t status;
    u32 LastStatus = FT_NETIF_DOWN;
    u32 Flg;
    if (RT_NULL == Args)
    {
        return;
    }

    pOsMac = (struct drv_gmac *)Args;

    while (1)
    {
        status = 0;
        if (rt_event_recv(&pOsMac->link_event, FT_NETIF_LINKUP | FT_NETIF_DOWN, RT_EVENT_FLAG_CLEAR | RT_EVENT_FLAG_OR,
                          RT_WAITING_FOREVER, &status) != RT_EOK)
        {
            LOG_E("wait completed timeout");
            continue;
        }

        if (status & FT_NETIF_DOWN)
        {
            eth_device_linkchange(&pOsMac->parent, RT_FALSE);
            LastStatus = FT_NETIF_DOWN;
        }
        else if (status & FT_NETIF_LINKUP)
        {
            Flg = (LastStatus == FT_NETIF_LINKUP) ? 0 : 1;
            LastStatus = FT_NETIF_LINKUP;
        }
        else
        {
            LOG_I(" EventGroup is error \r\n");
            RT_ASSERT(0)
        }

        if (Flg)
        {
            Flg = 0;
            // eth_device_linkchange(&pOsMac->parent, RT_FALSE);
            LOG_I(" Start Linkup \r\n");
            rt_ft2004_gmac_stop(pOsMac);
            rt_ft2004_gmac_start(pOsMac);
            LOG_I(" HardWare is ok \r\n");
            if (LastStatus == FT_NETIF_LINKUP)
            {
                rt_thread_mdelay(5000);
                eth_device_linkchange(&pOsMac->parent, RT_TRUE);
            }
        }
    }
}

#ifdef BSP_USING_GMAC0
struct drv_gmac os_drv_gmac0;
static char *os_drv_gmac0_name = "gmac0";
#endif

#ifdef BSP_USING_GMAC1
struct drv_gmac os_drv_gmac1;
static char *os_drv_gmac1_name = "gmac1";

#endif

static int rt_hw_gmac_init(struct drv_gmac *pOsMac, const char *name)
{
    rt_err_t state = RT_EOK;
    // rt_thread_t tid;
    rt_gmacmem_free(pOsMac);
    rt_gmacmem_create(pOsMac);

    pOsMac->eth_speed = GMAC_SPEED_1000M;
    pOsMac->eth_mode = GMAC_MODE_FULLDUPLEX;

    pOsMac->parent.parent.init = rt_ft2004_gmac_init;
    pOsMac->parent.parent.open = rt_ft2004_gmac_open;
    pOsMac->parent.parent.close = rt_ft2004_gmac_close;
    pOsMac->parent.parent.read = rt_ft2004_gmac_read;
    pOsMac->parent.parent.write = rt_ft2004_gmac_write;
    pOsMac->parent.parent.control = rt_ft2004_gmac_control;
    pOsMac->parent.parent.user_data = RT_NULL;

    pOsMac->parent.eth_rx = rt_ft2004_gmac_rx;
    pOsMac->parent.eth_tx = rt_ft2004_gmac_tx;
    Ft_Gmac_UseDefaultMacAddr(&pOsMac->Gmac, pOsMac->dev_addr);
    state = rt_event_init(&pOsMac->link_event, name, RT_IPC_FLAG_FIFO);
    LOG_I("rt_event_init is ok \r\n");
    if (RT_EOK != state)
    {
        rt_kprintf("init gmac0 event failed.\n");
        return -RT_ERROR;
    }

    /* register eth device */
    state = eth_device_init(&(pOsMac->parent), name);
    if (RT_EOK != state)
    {
        LOG_E("gmac device init faild: %d", state);
        return -RT_ERROR;
    }

    state = rt_thread_init(&pOsMac->_link_thread,
                           name,
                           ethernet_link_thread,
                           pOsMac,
                           &pOsMac->_link_thread_stack[0],
                           sizeof(pOsMac->_link_thread_stack),
                           10, 2);

    if (RT_EOK == state)
    {
        rt_thread_startup(&pOsMac->_link_thread);
    }
    else
    {
        LOG_E("rt_thread_init is error");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static int rt_hw_ft2004_eth_init(void)
{
    rt_err_t state = RT_EOK;

#ifdef BSP_USING_GMAC0
    os_drv_gmac0.Gmac.Config.InstanceId = 0;
    state = rt_hw_gmac_init(&os_drv_gmac0, os_drv_gmac0_name);
    if (RT_EOK != state)
    {
        goto __exit;
    }
#endif

#ifdef BSP_USING_GMAC1
    os_drv_gmac1.Gmac.Config.InstanceId = 1;
    state = rt_hw_gmac_init(&os_drv_gmac1, os_drv_gmac1_name);
    if (RT_EOK != state)
    {
        goto __exit;
    }
#endif

__exit:
    return state;
}

INIT_DEVICE_EXPORT(rt_hw_ft2004_eth_init);

#endif
