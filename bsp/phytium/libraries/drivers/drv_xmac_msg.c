/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2025-05-28  huangjin     first commit
 */

#include"rtconfig.h"

#ifdef BSP_USING_ETH_MSG

#include "board.h"
#define LOG_TAG      "xmac_drv"
#include "drv_log.h"
#include "mm_aspace.h"
#ifdef RT_USING_SMART
    #include "ioremap.h"
#endif

#include "eth_board.h"
#include "drv_xmac_msg.h"
#include "fxmac_msg_common.h"
#include "cache.h"
#include "fcache.h"

#define FXMAC_MSG_BD_TO_INDEX(ringptr, bdptr) (((uintptr)bdptr - (uintptr)(ringptr)->base_bd_addr) / (ringptr)->separation)


// static void FXmacMsgInitOnError(FXmacMsgOs *instance_p);
static void FXmacMsgSetupIsr(FXmacMsgOs *instance_p);

static FXmacMsgOs fxmac_os_instace[FXMAC_MSG_NUM] =
{
#if defined(FXMAC0_MSG_ID)
    [FXMAC0_MSG_ID] =
    {
        .config = (0),
        .hwaddr = {0x98, 0x0e, 0x24, 0x00, 0x11, 0x0},

    },
#endif
#if defined(FXMAC1_MSG_ID)
    [FXMAC1_MSG_ID] =
    {
        .config = (0),
        .hwaddr = {0x98, 0x0e, 0x24, 0x00, 0x11, 0x1},

    },
#endif
#if defined(FXMAC2_MSG_ID)
    [FXMAC2_MSG_ID] =
    {
        .config = (0),
        .hwaddr = {0x98, 0x0e, 0x24, 0x00, 0x11, 0x2},
    },
#endif
#if defined(FXMAC3_MSG_ID)
    [FXMAC3_MSG_ID] =
    {
        .config = (0),
        .hwaddr = {0x98, 0x0e, 0x24, 0x00, 0x11, 0x3},
    },
#endif
};

int isr_calling_flg = 0;

/* queue */
void FXmacQueueInit(PqQueue *q)
{
    FASSERT(q != NULL);
    q->head = q->tail = q->len = 0;
}

int FXmacPqEnqueue(PqQueue *q, void *p)
{
    if (q->len == PQ_QUEUE_SIZE)
    {
        return -1;
    }

    q->data[q->head] = (uintptr)p;
    q->head = (q->head + 1) % PQ_QUEUE_SIZE;
    q->len++;

    return 0;
}

void *FXmacPqDequeue(PqQueue *q)
{
    int ptail;

    if (q->len == 0)
    {
        return NULL;
    }

    ptail = q->tail;
    q->tail = (q->tail + 1) % PQ_QUEUE_SIZE;
    q->len--;

    return (void *)q->data[ptail];
}

int FXmacPqQlength(PqQueue *q)
{
    return q->len;
}

/* dma */
/**
 * @name:  IsTxSpaceAvailable
 * @msg:   Get the number of free BDs in the Bdrings
 * @param {ethernetif} *ethernetif_p
 * @return {*}
 */
static u32 IsTxSpaceAvailable(FXmacMsgOs *instance_p)
{
    FXmacMsgBdRing *txring;
    u32 freecnt;
    FASSERT(instance_p != NULL);

    txring = &(FXMAC_MSG_GET_TXRING(instance_p->instance));

    /* tx space is available as long as there are valid BD's */
    freecnt = FXMAC_MSG_BD_RING_GET_FREE_CNT(txring);
    return freecnt;
}

/**
 * @name: FXmacMsgProcessSentBds
 * @msg:   Free up memory space of pbuf on the send queue
 * @return {*}
 * @param {ethernetif} *ethernetif_p
 * @param {FXmacMsgBdRing} *txring
 */
void FXmacMsgProcessSentBds(FXmacMsgOs *instance_p, FXmacMsgBdRing *txring)
{
    FXmacMsgBd *txbdset;
    FXmacMsgBd *curbdpntr;
    u32 n_bds;
    FError status;
    u32 n_pbufs_freed;
    u32 bdindex;
    struct pbuf *p;
    u32 *temp;

    while (1)
    {
        /* obtain processed BD's */
        n_bds = FXmacMsgBdRingFromHwTx(txring, FXMAC_MSG_TX_PBUFS_LENGTH, &txbdset);
        if (n_bds == 0)
        {
            return;
        }
        /* free the processed BD's */
        n_pbufs_freed = n_bds;
        curbdpntr = txbdset;
        while (n_pbufs_freed > 0)
        {
            bdindex = FXMAC_MSG_BD_TO_INDEX(txring, curbdpntr);
            temp = (u32 *)curbdpntr;
            *temp = 0; /* Word 0 */
            temp++;
            if (bdindex == (FXMAC_MSG_TX_PBUFS_LENGTH - 1))
            {
                *temp = 0xC0000000; /* Word 1 ,used/Wrap – marks last descriptor in transmit buffer descriptor list.*/
            }
            else
            {
                *temp = 0x80000000; /* Word 1 , Used – must be zero for GEM to read data to the transmit buffer.*/
            }


            p = (struct pbuf *)instance_p->buffer.tx_pbufs_storage[bdindex];

            if (p != NULL)
            {
                pbuf_free(p);
            }
            instance_p->buffer.tx_pbufs_storage[bdindex] = (uintptr)NULL;
            curbdpntr = FXMAC_MSG_BD_RING_NEXT(txring, curbdpntr);
            n_pbufs_freed--;

        }

        status = FXmacMsgBdRingFree(txring, n_bds, txbdset);
        if (status != FT_SUCCESS)
        {
            LOG_I("Failure while freeing in Tx Done ISR.");
        }
    }
    return;
}

FError FXmacMsgSgsend(FXmacMsgOs *instance_p, struct pbuf *p)
{
    struct pbuf *q;
    u32 n_pbufs;
    FXmacMsgBd *txbdset, *txbd, *last_txbd = NULL;
    FXmacMsgBd *temp_txbd;
    FError status;
    FXmacMsgBdRing *txring;
    u32 bdindex;
    uintptr tx_payload ;
    u32 max_fr_size;


    txring = &(FXMAC_MSG_GET_TXRING(instance_p->instance));

    /* first count the number of pbufs */
    for (q = p, n_pbufs = 0; q != NULL; q = q->next)
    {
        n_pbufs++;
    }

    /* obtain as many BD's */
    status = FXmacMsgBdRingAlloc(txring, n_pbufs, &txbdset);
    if (status != FT_SUCCESS)
    {
        LOG_I("sgsend: Error allocating TxBD.");
        return ERR_GENERAL;
    }

    for (q = p, txbd = txbdset; q != NULL; q = q->next)
    {
        bdindex = FXMAC_MSG_BD_TO_INDEX(txring, txbd);

        if (instance_p->buffer.tx_pbufs_storage[bdindex])
        {
            LOG_I("txbd %p, txring->base_bd_addr %p", txbd, txring->base_bd_addr);
            LOG_I("PBUFS not available bdindex is %d ", bdindex);
            LOG_I("instance_p->buffer.tx_pbufs_storage[bdindex] %p ", instance_p->buffer.tx_pbufs_storage[bdindex]);
            return ERR_GENERAL;
        }

        /* Send the data from the pbuf to the interface, one pbuf at a
           time. The size of the data in each pbuf is kept in the ->len
           variable. */
        tx_payload = (uintptr)q->payload;
#ifdef RT_USING_SMART
        tx_payload += PV_OFFSET;
#endif
        FXMAC_MSG_BD_SET_ADDRESS_TX(txbd, (uintptr)tx_payload);

        if (instance_p->config & FXMAC_MSG_OS_CONFIG_JUMBO)
        {
            max_fr_size = FXMAC_MSG_MAX_FRAME_SIZE_JUMBO;
        }
        else
        {
            max_fr_size = FXMAC_MSG_MAX_FRAME_SIZE;
        }

        if (q->len > max_fr_size)
        {
            FXMAC_MSG_BD_SET_LENGTH(txbd, max_fr_size & 0x3FFF);
        }
        else
        {
            FXMAC_MSG_BD_SET_LENGTH(txbd, q->len & 0x3FFF);
        }

        instance_p->buffer.tx_pbufs_storage[bdindex] = (uintptr)q;

        pbuf_ref(q);
        last_txbd = txbd;
        FXMAC_MSG_BD_CLEAR_LAST(txbd);
        txbd = FXMAC_MSG_BD_RING_NEXT(txring, txbd);
    }
    FXMAC_MSG_BD_SET_LAST(last_txbd);

    bdindex = FXMAC_MSG_BD_TO_INDEX(txring, txbd);

    /* For fragmented packets, remember the 1st BD allocated for the 1st
       packet fragment. The used bit for this BD should be cleared at the end
       after clearing out used bits for other fragments. For packets without
       just remember the allocated BD. */
    temp_txbd = txbdset;
    txbd = txbdset;
    txbd = FXMAC_MSG_BD_RING_NEXT(txring, txbd);
    q = p->next;
    for (; q != NULL; q = q->next)
    {
        FXMAC_MSG_BD_CLEAR_TX_USED(txbd);

        txbd = FXMAC_MSG_BD_RING_NEXT(txring, txbd);
    }
    FXMAC_MSG_BD_CLEAR_TX_USED(temp_txbd);


    status = FXmacMsgBdRingToHw(txring, n_pbufs, txbdset);
    if (status != FT_SUCCESS)
    {
        LOG_I("sgsend: Error submitting TxBD.");
        return ERR_GENERAL;
    }

    /* Start transmit */
    FXMAC_MSG_WRITE((&instance_p->instance), FXMAC_MSG_TX_PTR(0), bdindex);
    return status;
}

void SetupRxBds(FXmacMsgOs *instance_p, FXmacMsgBdRing *rxring)
{
    FXmacMsgBd *rxbd;
    FError status;
    struct pbuf *p;
    u32 freebds;
    u32 bdindex;
    u32 *temp;
    uintptr_t pl_paddr;
    freebds = FXMAC_MSG_BD_RING_GET_FREE_CNT(rxring);
    while (freebds > 0)
    {
        freebds--;

        if (instance_p->config & FXMAC_MSG_OS_CONFIG_JUMBO)
        {
            p = pbuf_alloc(PBUF_RAW, FXMAC_MSG_MAX_FRAME_SIZE_JUMBO, PBUF_RAM);
        }
        else
        {
            p = pbuf_alloc(PBUF_RAW, FXMAC_MSG_MAX_FRAME_SIZE, PBUF_RAM);
        }

        if (!p)
        {
#if LINK_STATS
            lwip_stats.link.memerr++;
            lwip_stats.link.drop++;
#endif
            LOG_I("Unable to alloc pbuf in recv_handler.");
            return;
        }
        status = FXmacMsgBdRingAlloc(rxring, 1, &rxbd);
        if (status != FT_SUCCESS)
        {
            LOG_I("SetupRxBds: Error allocating RxBD.");
            pbuf_free(p);
            return;
        }
        status = FXmacMsgBdRingToHw(rxring, 1, rxbd);
        if (status != FT_SUCCESS)
        {
            LOG_I("Error committing RxBD to hardware: ");
            if (status == FXMAC_MSG_ERR_SG_LIST)
            {
                LOG_I("XST_DMA_SG_LIST_ERROR: this function was called out of sequence with FXmacMsgBdRingAlloc().");
            }
            else
            {
                LOG_I("Set of BDs was rejected because the first BD did not have its start-of-packet bit set, or the last BD did not have its end-of-packet bit set, or any one of the BD set has 0 as length value.");
            }

            pbuf_free(p);
            FXmacMsgBdRingUnAlloc(rxring, 1, rxbd);
            return;
        }

        bdindex = FXMAC_MSG_BD_TO_INDEX(rxring, rxbd);
        temp = (u32 *)rxbd;
        if (bdindex == (FXMAC_MSG_RX_PBUFS_LENGTH - 1))
        {
            *temp = 0x00000002;
        }
        else
        {
            *temp = 0;
        }
        temp++;
        *temp = 0;
        pl_paddr = (uintptr)p->payload;
#ifdef RT_USING_SMART
        pl_paddr += PV_OFFSET;
#endif
        FXMAC_MSG_BD_SET_ADDRESS_RX(rxbd, (uintptr)pl_paddr);
        instance_p->buffer.rx_pbufs_storage[bdindex] = (uintptr)p;
    }
}

void FXmacMsgRecvSemaphoreHandler(void *arg)
{
    FXmacMsgOs *instance_p;
    rt_err_t result;

    if (RT_NULL == arg)
    {
        LOG_E("Args is NULL");
        return;
    }

    instance_p = (FXmacMsgOs *)arg;

    /* 禁用接收完成中断 */
    FXmacMsgDisableIrq(&instance_p->instance, 0, FXMAC_MSG_INT_RX_COMPLETE);
    result = eth_device_ready(&(instance_p->parent));
    if (result != RT_EOK)
    {
        LOG_I("RxCpltCallback err = %d", result);
    }

}

void FXmacMsgRecvHandler(void *arg)
{
    struct pbuf *p;
    FXmacMsgBd *rxbdset, *curbdptr;
    FXmacMsgBd *rxtailbdptr = NULL;
    FXmacMsgBdRing *rxring;
    volatile u32 bd_processed;
    u32 rx_bytes, k;
    u32 bdindex = 0;
    // u32 regval;
    u32 rx_tail_bd_index = 0;
    FXmacMsgOs *instance_p;
    FASSERT(arg != NULL);

    instance_p = (FXmacMsgOs *)arg;
    rxring = &FXMAC_MSG_GET_RXRING(instance_p->instance);

    /* If Reception done interrupt is asserted, call RX call back function
     to handle the processed BDs and then raise the according flag.*/
    /* IOP模式没有 发送/接收状态寄存器 */
    // regval = FXMAC_READREG32(instance_p->instance.config.base_address, FXMAC_RXSR_OFFSET);
    // FXMAC_WRITEREG32(instance_p->instance.config.base_address, FXMAC_RXSR_OFFSET, regval);

    while (1)
    {
        bd_processed = FXmacMsgBdRingFromHwRx(rxring, FXMAC_MSG_RX_PBUFS_LENGTH, &rxbdset);
        if (bd_processed <= 0)
        {
            break;
        }

        for (k = 0, curbdptr = rxbdset; k < bd_processed; k++)
        {
            bdindex = FXMAC_MSG_BD_TO_INDEX(rxring, curbdptr);
            p = (struct pbuf *)instance_p->buffer.rx_pbufs_storage[bdindex];
            /*
             * Adjust the buffer size to the actual number of bytes received.
             */
            if (instance_p->config & FXMAC_MSG_OS_CONFIG_JUMBO)
            {
                rx_bytes = FXMAC_MSG_GET_RX_FRAME_SIZE(curbdptr);
            }
            else
            {
                rx_bytes = FXMAC_MSG_BD_GET_LENGTH(curbdptr);
            }

            pbuf_realloc(p, rx_bytes);

            /* Invalidate RX frame before queuing to handle
             * L1 cache prefetch conditions on any architecture.
             */
            // FCacheDCacheInvalidateRange((uintptr)p->payload, rx_bytes);
            // rt_hw_cpu_icache_invalidate((void *)p->payload, rx_bytes);

            /* store it in the receive queue,
             * where it'll be processed by a different handler
             */
            if (FXmacPqEnqueue(&instance_p->recv_q, (void *)p) < 0)
            {
#if LINK_STATS
                lwip_stats.link.memerr++;
                lwip_stats.link.drop++;
#endif
                pbuf_free(p);
            }
            instance_p->buffer.rx_pbufs_storage[bdindex] = (uintptr)NULL;
            curbdptr = FXMAC_MSG_BD_RING_NEXT(rxring, curbdptr);
            rxtailbdptr = curbdptr;
        }

        /* free up the BD's */
        FXmacMsgBdRingFree(rxring, bd_processed, rxbdset);
        SetupRxBds(instance_p, rxring);
    }

    /* 接收尾指针的使用 */
    rx_tail_bd_index = FXMAC_MSG_BD_TO_INDEX(rxring, rxtailbdptr);
    DSB();
    FXMAC_MSG_WRITE((&instance_p->instance), FXMAC_MSG_RX_PTR(0), rx_tail_bd_index);

    return;
}


void CleanDmaTxdescs(FXmacMsgOs *instance_p)
{
    FXmacMsgBd bdtemplate;
    FXmacMsgBdRing *txringptr;

    txringptr = &FXMAC_MSG_GET_TXRING((instance_p->instance));
    FXMAC_MSG_BD_CLEAR(&bdtemplate);
    FXMAC_MSG_BD_SET_STATUS(&bdtemplate, FXMAC_MSG_TXBUF_USED_MASK);

    FXmacMsgBdRingCreate(txringptr, (uintptr)instance_p->buffer.tx_bdspace,
                      (uintptr)instance_p->buffer.tx_bdspace, BD_ALIGNMENT,
                      sizeof(instance_p->buffer.tx_bdspace));

    FXmacMsgBdRingClone(txringptr, &bdtemplate, FXMAC_MSG_SEND);
}

FError FXmacMsgInitDma(FXmacMsgOs *instance_p)
{
    FXmacMsgBd bdtemplate;
    FXmacMsgBdRing *rxringptr, *txringptr;
    FXmacMsgBd *rxbd;
    struct pbuf *p;
    FError status;
    int i;
    u32 bdindex;
    u32 *temp;
    uintptr rx_paddr;
    uintptr tx_paddr;
    uintptr pl_paddr;

    /*
     * The BDs need to be allocated in uncached memory. Hence the 1 MB
     * address range allocated for Bd_Space is made uncached
     * by setting appropriate attributes in the translation table.
     * The Bd_Space is aligned to 1MB and has a size of 1 MB. This ensures
     * a reserved uncached area used only for BDs.
     */

    rxringptr = &FXMAC_MSG_GET_RXRING(instance_p->instance);
    txringptr = &FXMAC_MSG_GET_TXRING(instance_p->instance);
    LOG_I("rxringptr: 0x%08x", rxringptr);
    LOG_I("txringptr: 0x%08x", txringptr);

    LOG_I("rx_bdspace: %p ", instance_p->buffer.rx_bdspace);
    LOG_I("tx_bdspace: %p ", instance_p->buffer.tx_bdspace);

    /* Setup RxBD space. */
    FXMAC_MSG_BD_CLEAR(&bdtemplate);
    rx_paddr = (uintptr)instance_p->buffer.rx_bdspace;
#ifdef RT_USING_SMART
    rx_paddr += PV_OFFSET;
#endif

    /* Create the RxBD ring */
    status = FXmacMsgBdRingCreate(rxringptr, (uintptr)rx_paddr,
                               (uintptr)instance_p->buffer.rx_bdspace, BD_ALIGNMENT,
                               FXMAC_MSG_RX_PBUFS_LENGTH);

    if (status != FT_SUCCESS)
    {
        LOG_I("Error setting up RxBD space.");
        return ERR_IF;
    }

    status = FXmacMsgBdRingClone(rxringptr, &bdtemplate, FXMAC_MSG_RECV);
    if (status != FT_SUCCESS)
    {
        LOG_I("Error initializing RxBD space.");
        return ERR_IF;
    }

    FXMAC_MSG_BD_CLEAR(&bdtemplate);
    FXMAC_MSG_BD_SET_STATUS(&bdtemplate, FXMAC_MSG_TXBUF_USED_MASK);

    tx_paddr = (uintptr)instance_p->buffer.tx_bdspace;
#ifdef RT_USING_SMART
    tx_paddr += PV_OFFSET;
#endif
    /* Create the TxBD ring */
    status = FXmacMsgBdRingCreate(txringptr, (uintptr)tx_paddr,
                               (uintptr)instance_p->buffer.tx_bdspace, BD_ALIGNMENT,
                               FXMAC_MSG_TX_PBUFS_LENGTH);

    if (status != FT_SUCCESS)
    {
        return ERR_IF;
    }

    /* We reuse the bd template, as the same one will work for both rx and tx. */
    status = FXmacMsgBdRingClone(txringptr, &bdtemplate, FXMAC_MSG_SEND);
    if (status != FT_SUCCESS)
    {
        return ERR_IF;
    }

    /*
     * Allocate RX descriptors, 1 RxBD at a time.
     */
    for (i = 0; i < FXMAC_MSG_RX_PBUFS_LENGTH; i++)
    {
        if (instance_p->config & FXMAC_MSG_OS_CONFIG_JUMBO)
        {
            p = pbuf_alloc(PBUF_RAW, FXMAC_MSG_MAX_FRAME_SIZE_JUMBO, PBUF_RAM);
        }
        else
        {
            p = pbuf_alloc(PBUF_RAW, FXMAC_MSG_MAX_FRAME_SIZE, PBUF_RAM);
        }

        if (!p)
        {
#if LINK_STATS
            lwip_stats.link.memerr++;
            lwip_stats.link.drop++;
#endif
            LOG_E("Unable to alloc pbuf in InitDma.");
            return ERR_IF;
        }
        status = FXmacMsgBdRingAlloc(rxringptr, 1, &rxbd);
        if (status != FT_SUCCESS)
        {
            LOG_E("InitDma: Error allocating RxBD.");
            pbuf_free(p);
            return ERR_IF;
        }
        /* Enqueue to HW */
        status = FXmacMsgBdRingToHw(rxringptr, 1, rxbd);
        if (status != FT_SUCCESS)
        {
            LOG_E("Error: committing RxBD to HW.");
            pbuf_free(p);
            FXmacMsgBdRingUnAlloc(rxringptr, 1, rxbd);
            return ERR_IF;
        }

        bdindex = FXMAC_MSG_BD_TO_INDEX(rxringptr, rxbd);
        temp = (u32 *)rxbd;
        *temp = 0;
        if (bdindex == (FXMAC_MSG_RX_PBUFS_LENGTH - 1))
        {
            *temp = 0x00000002;
        }
        temp++;
        *temp = 0;

        pl_paddr = (uintptr)p->payload;
#ifdef RT_USING_SMART
        pl_paddr += PV_OFFSET;
#endif
        FXMAC_MSG_BD_SET_ADDRESS_RX(rxbd, (uintptr)pl_paddr);

        instance_p->buffer.rx_pbufs_storage[bdindex] = (uintptr)p;
    }

    FXmacMsgSetQueuePtr(&(instance_p->instance), instance_p->instance.tx_bd_queue.bdring.phys_base_addr, 0, (u16)FXMAC_MSG_SEND);
    FXmacMsgSetQueuePtr(&(instance_p->instance), instance_p->instance.rx_bd_queue.bdring.phys_base_addr, 0, (u16)FXMAC_MSG_RECV);

    return 0;
}

// static void FreeOnlyTxPbufs(FXmacMsgOs *instance_p)
// {
//     u32 index;
//     struct pbuf *p;

//     for (index = 0; index < (FXMAC_MSG_TX_PBUFS_LENGTH); index++)
//     {
//         if (instance_p->buffer.tx_pbufs_storage[index] != 0)
//         {
//             p = (struct pbuf *)instance_p->buffer.tx_pbufs_storage[index];
//             pbuf_free(p);
//             instance_p->buffer.tx_pbufs_storage[index] = (uintptr)NULL;
//         }
//         instance_p->buffer.tx_pbufs_storage[index] = (uintptr)0;
//     }
// }


// static void FreeOnlyRxPbufs(FXmacMsgOs *instance_p)
// {
//     u32 index;
//     struct pbuf *p;

//     for (index = 0; index < (FXMAC_MSG_RX_PBUFS_LENGTH); index++)
//     {
//         if (instance_p->buffer.rx_pbufs_storage[index] != 0)
//         {
//             p = (struct pbuf *)instance_p->buffer.rx_pbufs_storage[index];
//             pbuf_free(p);
//             instance_p->buffer.rx_pbufs_storage[index] = (uintptr)0;
//         }
//     }
// }


// static void FreeTxRxPbufs(FXmacMsgOs *instance_p)
// {
//     u32 rx_queue_len;
//     struct pbuf *p;
//     /* first :free PqQueue data */
//     rx_queue_len = FXmacPqQlength(&instance_p->recv_q);

//     while (rx_queue_len)
//     {
//         /* return one packet from receive q */
//         p = (struct pbuf *)FXmacPqDequeue(&instance_p->recv_q);
//         pbuf_free(p);
//         LOG_E("Delete queue %p", p);
//         rx_queue_len--;
//     }
//     FreeOnlyTxPbufs(instance_p);
//     FreeOnlyRxPbufs(instance_p);

// }

/* interrupt */
// static void FXmacMsgHandleDmaTxError(FXmacMsgOs *instance_p)
// {
//     s32_t status = FT_SUCCESS;
//     u32 dmacrreg;

//     FreeTxRxPbufs(instance_p);
//     status = FXmacMsgCfgInitialize(&instance_p->instance, &instance_p->instance.config);

//     if (status != FT_SUCCESS)
//     {
//         LOG_E("In %s:EmacPs Configuration Failed....", __func__);
//     }

//     /* initialize the mac */
//     FXmacMsgInitOnError(instance_p); /* need to set mac filter address */

//     /* IOP模式下可以直接操作该寄存器吗？ */
//     dmacrreg = FXMAC_READREG32(instance_p->instance.config.base_address, FXMAC_DMACR_OFFSET);
//     dmacrreg = dmacrreg | (FXMAC_DMACR_ORCE_DISCARD_ON_ERR_MASK); /* force_discard_on_err */
//     FXMAC_WRITEREG32(instance_p->instance.config.base_address, FXMAC_DMACR_OFFSET, dmacrreg);
//     FXmacMsgSetupIsr(instance_p);
//     FXmacMsgInitDma(instance_p);

//     FXmacMsgStart(&instance_p->instance);
// }

// void FXmacMsgHandleTxErrors(FXmacMsgOs *instance_p)
// {
//     u32 netctrlreg;

//     netctrlreg = FXMAC_READREG32(instance_p->instance.config.base_address, FXMAC_NWCTRL_OFFSET);
//     netctrlreg = netctrlreg & (~FXMAC_NWCTRL_TXEN_MASK);
//     FXMAC_WRITEREG32(instance_p->instance.config.base_address, FXMAC_NWCTRL_OFFSET, netctrlreg);
//     FreeOnlyTxPbufs(instance_p);

//     CleanDmaTxdescs(instance_p);
//     netctrlreg = FXMAC_READREG32(instance_p->instance.config.base_address, FXMAC_NWCTRL_OFFSET);
//     netctrlreg = netctrlreg | (FXMAC_NWCTRL_TXEN_MASK);
//     FXMAC_WRITEREG32(instance_p->instance.config.base_address, FXMAC_NWCTRL_OFFSET, netctrlreg);
// }

// void FXmacMsgErrorHandler(void *arg, u8 direction, u32 error_word)
// {
//     FXmacMsgBdRing *rxring;
//     FXmacMsgBdRing *txring;
//     FXmacMsgOs *instance_p;

//     instance_p = (FXmacMsgOs *)arg;
//     rxring = &FXMAC_MSG_GET_RXRING(instance_p->instance);
//     txring = &FXMAC_MSG_GET_TXRING(instance_p->instance);

//     if (error_word != 0)
//     {
//         switch (direction)
//         {
//             case FXMAC_MSG_RECV:
//                 if (error_word & FXMAC_RXSR_HRESPNOK_MASK)
//                 {
//                     LOG_I("Receive DMA error.");
//                     // FXmacMsgHandleDmaTxError(instance_p);
//                 }
//                 if (error_word & FXMAC_RXSR_RXOVR_MASK)
//                 {
//                     LOG_I("Receive over run.");
//                     FXmacMsgRecvHandler(arg);
//                 }
//                 if (error_word & FXMAC_RXSR_BUFFNA_MASK)
//                 {
//                     LOG_I("Receive buffer not available.");
//                     FXmacMsgRecvHandler(arg);
//                 }
//                 break;
//             case FXMAC_MSG_SEND:
//                 if (error_word & FXMAC_TXSR_HRESPNOK_MASK)
//                 {
//                     LOG_I("Transmit DMA error.");
//                     // FXmacMsgHandleDmaTxError(instance_p);
//                 }
//                 if (error_word & FXMAC_TXSR_URUN_MASK)
//                 {
//                     LOG_I("Transmit under run.");
//                     // FXmacMsgHandleTxErrors(instance_p);
//                 }
//                 if (error_word & FXMAC_TXSR_BUFEXH_MASK)
//                 {
//                     LOG_I("Transmit buffer exhausted.");
//                     // FXmacMsgHandleTxErrors(instance_p);
//                 }
//                 if (error_word & FXMAC_TXSR_RXOVR_MASK)
//                 {
//                     LOG_I("Transmit retry excessed limits.");
//                     // FXmacMsgHandleTxErrors(instance_p);
//                 }
//                 if (error_word & FXMAC_TXSR_FRAMERX_MASK)
//                 {
//                     LOG_I("Transmit collision.");
//                     FXmacMsgProcessSentBds(instance_p, txring);
//                 }
//                 break;
//         }
//     }
// }

void FXmacMsgLinkChange(void *arg)
{
    u32 ctrl;
    u32 link, link_status;
    FXmacMsgCtrl *xmac_p;
    FXmacMsgOs *instance_p;

    instance_p = (FXmacMsgOs *)arg;
    xmac_p = &instance_p->instance;

    if (xmac_p->config.interface == FXMAC_MSG_PHY_INTERFACE_MODE_SGMII)
    {
        LOG_I("xmac_p->msg_regs: %p, xmac_p->mac_regs: %p", xmac_p->msg_regs, xmac_p->mac_regs);
        ctrl = FXMAC_MSG_READ(xmac_p, FXMAC_MSG_PCS_AN_LP);
        link = (ctrl & BIT(FXMAC_MSG_PCS_LINK_PARTNER_NEXT_PAGE_INDEX)) >> FXMAC_MSG_PCS_LINK_PARTNER_NEXT_PAGE_INDEX;


        switch (link)
        {
            case 0:
                LOG_I("Link status is down");
                link_status = FXMAC_MSG_LINKDOWN;
                break;
            case 1:
                LOG_I("Link status is up");
                link_status = FXMAC_MSG_LINKUP;
                break;
            default:
                LOG_E("Link status is error 0x%x ", link);
                return;
        }

        if (link_status == FXMAC_MSG_LINKUP)
        {
            if (link_status != xmac_p->link_status)
            {
                xmac_p->link_status = FXMAC_MSG_NEGOTIATING;
                LOG_I("Need NEGOTIATING.");
            }
        }
        else
        {
            xmac_p->link_status = FXMAC_MSG_LINKDOWN;
        }
    }
}

/* phy */
/**
 * @name: FXmacMsgPhyLinkDetect
 * @msg:  Get current link status
 * @note:
 * @param {FXmacMsgCtrl} *fxmac_p
 * @param {u32} phy_addr
 * @return {*} 1 is link up , 0 is link down
 */
static u32 FXmacMsgPhyLinkDetect(FXmacMsgCtrl *xmac_p, u32 phy_addr)
{
    u16 status;

    /* Read Phy Status register twice to get the confirmation of the current link status. */
    status = FXmacMsgMdioDataReadC22(xmac_p, phy_addr, PHY_STATUS_REG_OFFSET);

    if (status & PHY_STAT_LINK_STATUS)
    {
        return 1;
    }
    return 0;
}

static u32 FXmacMsgPhyAutonegStatus(FXmacMsgCtrl *xmac_p, u32 phy_addr)
{
    u16 status;

    /* Read Phy Status register twice to get the confirmation of the current link status. */
    status = FXmacMsgMdioDataReadC22(xmac_p, phy_addr, PHY_STATUS_REG_OFFSET);

    if (status & PHY_STATUS_AUTONEGOTIATE_COMPLETE)
    {
        return 1;
    }
    return 0;
}

enum lwip_port_link_status FXmacMsgLwipPortLinkDetect(FXmacMsgOs *instance_p)
{
    u32 phy_link_status;
    FXmacMsgCtrl *xmac_p = &instance_p->instance;

    if (xmac_p->is_ready != (u32)FT_COMPONENT_IS_READY)
    {
        return ETH_LINK_UNDEFINED;
    }

    phy_link_status = FXmacMsgPhyLinkDetect(xmac_p, xmac_p->phy_address);

    if ((xmac_p->link_status == FXMAC_MSG_LINKUP) && (!phy_link_status))
    {
        xmac_p->link_status = FXMAC_MSG_LINKDOWN;
    }

    switch (xmac_p->link_status)
    {
        case FXMAC_MSG_LINKUP:
            return ETH_LINK_UP;
        case FXMAC_MSG_LINKDOWN:
            xmac_p->link_status = FXMAC_MSG_NEGOTIATING;
            LOG_D("Ethernet Link down.");
            return ETH_LINK_DOWN;
        case FXMAC_MSG_NEGOTIATING:
            if ((phy_link_status == FXMAC_MSG_LINKUP) && FXmacMsgPhyAutonegStatus(xmac_p, xmac_p->phy_address))
            {
                err_t phy_ret;
                phy_ret = FXmacMsgPhyInit(xmac_p, xmac_p->config.speed, xmac_p->config.duplex, xmac_p->config.auto_neg, XMAC_MSG_PHY_RESET_DISABLE);

                if (phy_ret != FT_SUCCESS)
                {
                    LOG_E("FXmacMsgPhyInit is error.");
                    return ETH_LINK_DOWN;
                }
                FXmacMsgInterfaceConfig(xmac_p, 0);

                /* Initiate Phy setup to get link speed */
                xmac_p->link_status = FXMAC_MSG_LINKUP;
                LOG_D("Ethernet Link up.");
                return ETH_LINK_UP;
            }
            return ETH_LINK_DOWN;
        default:
            return ETH_LINK_DOWN;
    }
}

enum lwip_port_link_status FXmacMsgPhyReconnect(FXmacMsgOs *instance_p)
{
    FXmacMsgCtrl *xmac_p;

    xmac_p = &instance_p->instance;

    if (xmac_p->config.interface == FXMAC_MSG_PHY_INTERFACE_MODE_SGMII)
    {
        rt_hw_interrupt_mask(xmac_p->config.queue_irq_num[0]);
        if (xmac_p->link_status == FXMAC_MSG_NEGOTIATING)
        {
            /* auto negotiation again*/
            err_t phy_ret;
            phy_ret = FXmacMsgPhyInit(xmac_p, xmac_p->config.speed, xmac_p->config.duplex, xmac_p->config.auto_neg, XMAC_MSG_PHY_RESET_DISABLE);
            if (phy_ret != FT_SUCCESS)
            {
                LOG_I("FXmacMsgPhyInit is error.");
                rt_hw_interrupt_umask(xmac_p->config.queue_irq_num[0]);
                return ETH_LINK_DOWN;
            }
            FXmacMsgInterfaceConfig(xmac_p, 0);
            xmac_p->link_status = FXMAC_MSG_LINKUP;
        }

        rt_hw_interrupt_umask(xmac_p->config.queue_irq_num[0]);

        switch (xmac_p->link_status)
        {
            case FXMAC_MSG_LINKDOWN:
                return ETH_LINK_DOWN;
            case FXMAC_MSG_LINKUP:
                return ETH_LINK_UP;
            default:
                return ETH_LINK_DOWN;
        }
    }
    else if ((xmac_p->config.interface == FXMAC_MSG_PHY_INTERFACE_MODE_RMII) || (xmac_p->config.interface == FXMAC_MSG_PHY_INTERFACE_MODE_RGMII))
    {
        return FXmacMsgLwipPortLinkDetect(instance_p);
    }
    else
    {
        switch (xmac_p->link_status)
        {
            case FXMAC_MSG_LINKDOWN:
                return ETH_LINK_DOWN;
            case FXMAC_MSG_LINKUP:
                return ETH_LINK_UP;
            default:
                return ETH_LINK_DOWN;
        }
    }
}

static void FXmacMsgOsIntrHandler(s32 vector, void *args)
{
    isr_calling_flg++;
    FXmacMsgIntrHandler(vector, args);
    isr_calling_flg--;
}

void FXmacMsgSendHandler(void *arg)
{
    FXmacMsgOs *instance_p;
    FXmacMsgBdRing *txringptr;

    instance_p = (FXmacMsgOs *)arg;
    txringptr = &(FXMAC_MSG_GET_TXRING(instance_p->instance));

    /* If Transmit done interrupt is asserted, process completed BD's */
    FXmacMsgProcessSentBds(instance_p, txringptr);
}

static void FXmacMsgSetupIsr(FXmacMsgOs *instance_p)
{
    /* Setup callbacks */
    FXmacMsgSetHandler(&instance_p->instance, FXMAC_MSG_HANDLER_DMASEND, FXmacMsgSendHandler, instance_p);
    FXmacMsgSetHandler(&instance_p->instance, FXMAC_MSG_HANDLER_DMARECV, FXmacMsgRecvSemaphoreHandler, instance_p);
    // FXmacMsgSetHandler(&instance_p->instance, FXMAC_MSG_HANDLER_ERROR, FXmacMsgErrorHandler, instance_p);
    FXmacMsgSetHandler(&instance_p->instance, FXMAC_MSG_HANDLER_LINKCHANGE, FXmacMsgLinkChange, instance_p);

    rt_hw_interrupt_install(instance_p->instance.config.queue_irq_num[0], FXmacMsgOsIntrHandler, &instance_p->instance, "fxmac_msg");
    rt_hw_interrupt_umask(instance_p->instance.config.queue_irq_num[0]);
}

/*  init fxmac instance */
// static void FXmacMsgInitOnError(FXmacMsgOs *instance_p)
// {
//     FXmacMsgCtrl *xmac_p;
//     u32 status = FT_SUCCESS;
//     xmac_p = &instance_p->instance;

//     /* set mac address */
//     status = FXmacMsgSetMacAddress(xmac_p, (void *)(instance_p->hwaddr));
//     if (status != FT_SUCCESS)
//     {
//         LOG_E("In %s:Emac Mac Address set failed...", __func__);
//     }
// }

/* 设置特性 */
void FXmacMsgFeatureSetOptions(u32 feature, FXmacMsgCtrl* xmac_p)
{
    u16 cmd_id, cmd_subid;
    cmd_id = FXMAC_MSG_CMD_SET;

    /* 巨帧 */
    if (feature & FXMAC_MSG_OS_CONFIG_JUMBO)
    {
        cmd_subid = FXMAC_MSG_CMD_SET_ENABLE_JUMBO;
        FXmacMsgSendMessage(xmac_p, cmd_id, cmd_subid, NULL, 0, 0);
        LOG_I("FXMAC_MSG_JUMBO_ENABLE_OPTION is ok");
    }
    /* 单播 */
    if (feature & FXMAC_MSG_OS_CONFIG_UNICAST_ADDRESS_FILITER)
    {
        LOG_I("FXMAC_MSG_UNICAST_OPTION is ok");
    }
    /* 多播 */
    if (feature & FXMAC_MSG_OS_CONFIG_MULTICAST_ADDRESS_FILITER)
    {
        cmd_subid = FXMAC_MSG_CMD_SET_ENABLE_MC;
        FXmacMsgSendMessage(xmac_p, cmd_id, cmd_subid, NULL, 0, 1);
        LOG_I("FXMAC_MSG_MULTICAST_OPTION is ok");
    }
    /* 全帧 */
    if (feature & FXMAC_MSG_OS_CONFIG_COPY_ALL_FRAMES)
    {
        cmd_subid = FXMAC_MSG_CMD_SET_ENABLE_PROMISE;
        FXmacMsgSendMessage(xmac_p, cmd_id, cmd_subid, NULL, 0, 0);
        LOG_I("FXMAC_MSG_PROMISC_OPTION is ok");
    }
    /* 关闭FCS(帧校验序列)校验 */
    if (feature & FXMAC_MSG_OS_CONFIG_CLOSE_FCS_CHECK)
    {
        LOG_I("FXMAC_MSG_FCS_STRIP_OPTION is ok");
    }
}

/* step 1: initialize instance */
/* step 2: depend on config set some options : JUMBO / IGMP */
/* step 3: FXmacSelectClk */
/* step 4: FXmacInitInterface */
/* step 5: initialize phy */
/* step 6: initialize dma */
/* step 7: initialize interrupt */
/* step 8: start mac */
FError FXmacMsgOsInit(FXmacMsgOs *instance_p)
{
    FXmacMsgConfig mac_config;
    const FXmacMsgConfig *mac_config_p;
    FXmacMsgPhyInterface interface = FXMAC_MSG_PHY_INTERFACE_MODE_SGMII;
    FXmacMsgCtrl *xmac_p;
    FError status;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->mac_config.instance_id < FXMAC_MSG_NUM);

    xmac_p = &instance_p->instance;
    LOG_I("instance_id IS %d", instance_p->mac_config.instance_id);
    mac_config_p = FXmacMsgLookupConfig(instance_p->mac_config.instance_id);
    if (mac_config_p == NULL)
    {
        LOG_E("FXmacMsgLookupConfig is error , instance_id is %d", instance_p->mac_config.instance_id);
        return RTTHREAD_XMAC_MSG_INIT_ERROR;
    }
#ifdef RT_USING_SMART
    mac_config_p->base_address = (uintptr)rt_ioremap((void *)mac_config_p->base_address, 0x2000);
#endif
    mac_config = *mac_config_p;
    switch (instance_p->mac_config.interface)
    {
        case FXMAC_MSG_OS_INTERFACE_SGMII:
            interface = FXMAC_MSG_PHY_INTERFACE_MODE_SGMII;
            LOG_I("SGMII select.");
            break;
        case FXMAC_MSG_OS_INTERFACE_RMII:
            interface = FXMAC_MSG_PHY_INTERFACE_MODE_RMII;
            LOG_I("RMII select.");
            break;
        case FXMAC_MSG_OS_INTERFACE_RGMII:
            LOG_I("RGMII select.");
            interface = FXMAC_MSG_PHY_INTERFACE_MODE_RGMII;
            break;
        default:
            LOG_E("Update interface is error , interface is %d", instance_p->mac_config.instance_id);
            return RTTHREAD_XMAC_MSG_INIT_ERROR;
    }
    mac_config.interface = interface;

    if (instance_p->mac_config.autonegotiation)
    {
        mac_config.auto_neg = 1;
    }
    else
    {
        mac_config.auto_neg = 0;
    }

    switch (instance_p->mac_config.phy_speed)
    {
        case FXMAC_MSG_PHY_SPEED_10M:
            LOG_I("10M select.");
            mac_config.speed = FXMAC_MSG_SPEED_10;
            break;
        case FXMAC_MSG_PHY_SPEED_100M:
            LOG_I("100M select.");
            mac_config.speed = FXMAC_MSG_SPEED_100;
            break;
        case FXMAC_MSG_PHY_SPEED_1000M:
            LOG_I("1000M select.");
            mac_config.speed = FXMAC_MSG_SPEED_1000;
            break;
        default:
            LOG_E("Setting speed is not valid , speed is %d", instance_p->mac_config.phy_speed);
            return RTTHREAD_XMAC_MSG_INIT_ERROR;
    }

    switch (instance_p->mac_config.phy_duplex)
    {
        case FXMAC_MSG_PHY_HALF_DUPLEX:
            LOG_I("Half duplex select.");
            mac_config.duplex = 0;
            break;
        case FXMAC_MSG_PHY_FULL_DUPLEX:
            LOG_I("Full duplex select.");
            mac_config.duplex = 1;
            break;
    }

    status = FXmacMsgCfgInitialize(xmac_p, &mac_config);
    if (status != FT_SUCCESS)
    {
        LOG_E("In %s:EmacPs Configuration Failed....", __func__);
    }

    /* 初始化MSG消息队列 */
    FXmacMsgInitRing(xmac_p);

    /* 获取配置参数 */
    FXmacMsgGetFeatureAll(xmac_p);

    /* 硬件重置 */
    FXmacMsgResetHw(xmac_p);

    /* 设置特性 */
    LOG_I("FXmacMsgFeatureSetOptions: config is %x", instance_p->config);
    FXmacMsgFeatureSetOptions(instance_p->config, xmac_p);

    /* 初始化硬件 */
    FXmacMsgInitHw(xmac_p, instance_p->hwaddr);

    /* 初始化PHY */
    status = FXmacMsgPhyInit(xmac_p, xmac_p->config.speed, xmac_p->config.duplex, xmac_p->config.auto_neg, XMAC_MSG_PHY_RESET_ENABLE);
    if (status != FT_SUCCESS)
    {
        LOG_W("FXmacMsgPhyInit is error.");
    }

    /* 初始化PHY接口 */
    FXmacMsgInterfaceConfig(xmac_p, 0);

    /* 初始化DMA描述符 */
    FXmacMsgInitDma(instance_p);

    /* 初始化中断 */
    FXmacMsgSetupIsr(instance_p);

    return FT_SUCCESS;
}

/**
 * @name: FXmacMsgOsRx
 * @msg: struct pbuf *FXmacMsgOsRx(FXmacMsgOs *instance_p)
 * @return {*}
 * @note:
 * @param {FXmacMsgOs} *instance_p
 */
struct pbuf *FXmacMsgOsRx(FXmacMsgOs *instance_p)
{
    FASSERT(instance_p != NULL);
    struct pbuf *p;

    /* see if there is data to process */
    if (FXmacPqQlength(&instance_p->recv_q) == 0)
    {
        return NULL;
    }
    /* return one packet from receive q */
    p = (struct pbuf *)FXmacPqDequeue(&instance_p->recv_q);

    return p;
}

static FError FXmacMsgOsOutput(FXmacMsgOs *instance_p, struct pbuf *p)
{
    FError status;

    status = FXmacMsgSgsend(instance_p, p);
    if (status != FT_SUCCESS)
    {
#if LINK_STATS
        lwip_stats.link.drop++;
#endif
    }

#if LINK_STATS
    lwip_stats.link.xmit++;
#endif /* LINK_STATS */

    return status;
}

FError FXmacMsgOsTx(FXmacMsgOs *instance_p, void *tx_buf)
{
    FXmacMsgBdRing *txring;
    FError ret;
    struct pbuf *p;
    FASSERT(instance_p != NULL);
    FASSERT(tx_buf != NULL);

    p = tx_buf;
    txring = &(FXMAC_MSG_GET_TXRING(instance_p->instance));
    FXmacMsgProcessSentBds(instance_p, txring);

    /* check if space is available to send */
    if (IsTxSpaceAvailable(instance_p))
    {
        ret = FXmacMsgOsOutput(instance_p, p);
    }
    else
    {
#if LINK_STATS
        lwip_stats.link.drop++;
#endif
        LOG_E("Pack dropped, no space.");
        ret = RTTHREAD_XMAC_MSG_NO_VALID_SPACE;
    }

    return ret;
}

FXmacMsgOs *FXmacMsgOsGetInstancePointer(FXmacMsgOsControl *config_p)
{
    FXmacMsgOs *instance_p;
    FASSERT(config_p != NULL);
    FASSERT(config_p->instance_id < FXMAC_MSG_NUM);
    FASSERT_MSG(config_p->interface < FXMAC_MSG_OS_INTERFACE_LENGTH, "config_p->interface %d is over %d", config_p->interface, FXMAC_MSG_OS_INTERFACE_LENGTH);
    FASSERT_MSG(config_p->autonegotiation <= 1, "config_p->autonegotiation %d is over 1", config_p->autonegotiation);
    FASSERT_MSG(config_p->phy_speed <= FXMAC_MSG_PHY_SPEED_1000M, "config_p->phy_speed %d is over 1000", config_p->phy_speed);
    FASSERT_MSG(config_p->phy_duplex <= FXMAC_MSG_PHY_FULL_DUPLEX, "config_p->phy_duplex %d is over FXMAC_MSG_PHY_FULL_DUPLEX", config_p->phy_duplex);

    instance_p = &fxmac_os_instace[config_p->instance_id];
    memcpy(&instance_p->mac_config, config_p, sizeof(FXmacMsgOsControl));
    return instance_p;
}

void FXmacMsgOsStart(FXmacMsgOs *instance_p)
{
    FASSERT(instance_p != NULL);

    /* start mac */
    instance_p->instance.mask &= (~(BIT(FXMAC_MSG_TXCOMP_INDEX)));
    FXmacMsgStart(&instance_p->instance);
}

static rt_err_t rt_xmac_msg_init(rt_device_t dev)
{
    struct eth_device *pXmacParent;
    FXmacMsgOs *pOsMac;

    FError ret;

    pXmacParent = rt_container_of(dev, struct eth_device, parent);
    if (NULL == pXmacParent)
    {
        return -RT_ENOMEM;
    }

    pOsMac = rt_container_of(pXmacParent, FXmacMsgOs, parent);
    if (NULL == pOsMac)
    {
        return -RT_ENOMEM;
    }


    ret = FXmacMsgOsInit(pOsMac);

    if (ret != FT_SUCCESS)
    {
        LOG_E("FXmacMsgOsInit is error\r\n");
        return -RT_ERROR;
    }
    rt_kprintf("FXMAC OS Init Success!\n");


    return RT_EOK;
}

static rt_err_t rt_xmac_msg_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("xmac open");
    return RT_EOK;
}

static rt_err_t rt_xmac_msg_close(rt_device_t dev)
{
    LOG_D("xmac close");
    return RT_EOK;
}

static rt_ssize_t rt_xmac_msg_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("xmac read");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_xmac_msg_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    LOG_D("xmac write");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_xmac_msg_control(rt_device_t dev, int cmd, void *args)
{

    FXmacMsgOs *pOsMac;
    struct eth_device *pXmacParent;


    pXmacParent = rt_container_of(dev, struct eth_device, parent);

    if (NULL == pXmacParent)
    {
        return -RT_ENOMEM;
    }

    pOsMac = rt_container_of(pXmacParent, FXmacMsgOs, parent);
    if (NULL == pOsMac)
    {
        return -RT_ENOMEM;
    }
    switch (cmd)
    {
        case NIOCTL_GADDR:
            /* get mac address */
            if (args)
            {
                rt_memcpy(args, pOsMac->hwaddr, 6);
            }

            else
            {
                return -RT_ERROR;
            }
            break;

        default:
            break;
    }

    return RT_EOK;
}

rt_err_t rt_xmac_msg_tx(rt_device_t dev, struct pbuf *p)
{
    FXmacMsgOs *pOsMac;
    struct eth_device *pXmacParent;
    FError  ret;

    pXmacParent = rt_container_of(dev, struct eth_device, parent);
    if (NULL == pXmacParent)
    {
        return -RT_ENOMEM;
    }

    pOsMac = rt_container_of(pXmacParent, FXmacMsgOs, parent);
    if (NULL == pOsMac)
    {
        return -RT_ENOMEM;
    }

#if RT_LWIP_ETH_PAD_SIZE
    pbuf_header(p, -RT_LWIP_ETH_PAD_SIZE); /* reclaim the padding word */
#endif
    ret = FXmacMsgOsTx(pOsMac, p);
#if RT_LWIP_ETH_PAD_SIZE
    pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif


    if (ret != FT_SUCCESS)
    {
        return ERR_MEM;
    }

    return RT_EOK;

}

struct pbuf *rt_xmac_msg_rx(rt_device_t dev)
{
    FXmacMsgOs *pOsMac;
    struct eth_device *pXmacParent;
    struct pbuf *p;

    pXmacParent = rt_container_of(dev, struct eth_device, parent);
    if (NULL == pXmacParent)
    {
        return RT_NULL;
    }

    pOsMac = rt_container_of(pXmacParent, FXmacMsgOs, parent);
    if (NULL == pOsMac)
    {
        return RT_NULL;
    }

    /* 是否需要在接收完成中断里关闭对应中断，在这里重新打开所有中断 */
    FXmacMsgEnableIrq(&pOsMac->instance, 0, FXMAC_MSG_INT_RX_COMPLETE);
    FXmacMsgRecvHandler(pOsMac);
    p = FXmacMsgOsRx(pOsMac);
    return p;
}


enum lwip_port_link_status eth_link_detect(FXmacMsgOs *instance_p)
{
    if (instance_p->instance.is_ready != FT_COMPONENT_IS_READY)
    {
        return ETH_LINK_UNDEFINED;
    }

    return  FXmacMsgPhyReconnect(instance_p);
}


static void ethernet_link_thread(void *Args)
{

    if (RT_NULL == Args)
    {
        return;
    }

    FXmacMsgOs *pOsMac;
    pOsMac = (FXmacMsgOs *)Args;

    while (1)
    {
        /* Call eth_link_detect() every 500ms to detect Ethernet link
         * change.
         */

        switch (eth_link_detect(pOsMac))
        {
            case ETH_LINK_UP:
                if (pOsMac->is_link_up == 0)
                {
                    LOG_I("netif flag is link_up\n");
                    pOsMac->is_link_up = 1;
                    eth_device_linkchange(&pOsMac->parent, RT_TRUE);
                }
                break;
            case ETH_LINK_DOWN:
            default:
                if (pOsMac->is_link_up == 1)
                {
                    LOG_I("netif flag is link_down\n");
                    pOsMac->is_link_up = 0;
                    eth_device_linkchange(&pOsMac->parent, RT_FALSE);
                }
                break;
        }
        rt_thread_mdelay(500);
    }
}

#ifdef RT_USING_DEVICE_OPS
const struct rt_device_ops net_ops=
{
    rt_xmac_msg_init,
    rt_xmac_msg_open,
    rt_xmac_msg_close,
    rt_xmac_msg_read,
    rt_xmac_msg_write,
    rt_xmac_msg_control
};
#endif

static int rt_hw_xmac_msg_init(FXmacMsgOs *pOsMac, const char *name, const char *link_thread_name)
{
    rt_err_t state = RT_EOK;

    #ifdef RT_USING_DEVICE_OPS
    pOsMac->parent.parent.ops= &net_ops;
    #else
    pOsMac->parent.parent.init = rt_xmac_msg_init;
    pOsMac->parent.parent.open = rt_xmac_msg_open;
    pOsMac->parent.parent.close = rt_xmac_msg_close;
    pOsMac->parent.parent.read = rt_xmac_msg_read;
    pOsMac->parent.parent.write = rt_xmac_msg_write;
    pOsMac->parent.parent.control = rt_xmac_msg_control;
    #endif
    pOsMac->parent.parent.user_data = RT_NULL;

    pOsMac->parent.eth_rx = rt_xmac_msg_rx;
    pOsMac->parent.eth_tx = rt_xmac_msg_tx;

    /* register eth device */
    state = eth_device_init(&(pOsMac->parent), name);

    if (RT_EOK != state)
    {
        LOG_E("xmac device init faild: %d", state);
        return -RT_ERROR;
    }
    rt_kprintf("Xmac %s Initiailized!\n", name);



    state = rt_thread_init(&pOsMac->_link_thread,
                           link_thread_name,
                           ethernet_link_thread,
                           pOsMac,
                           &pOsMac->_link_thread_stack[0],
                           sizeof(pOsMac->_link_thread_stack),
                           12, 2);
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
static int rt_hw_xmac_msg_eth_init(void)
{
    rt_err_t state = RT_EOK;
    FXmacMsgOsControl os_config;
    FXmacMsgOs *pOsMac;

#if defined(RT_USING_XMAC0_MSG)
    /* os_config initialize，need to be set manually here */
    os_config.instance_id = MAC_NUM0_CONTROLLER;
    os_config.interface = MAC_NUM0_MII_INTERFACE;
    os_config.autonegotiation = 1; /* 1 is autonegotiation ,0 is manually set */
    os_config.phy_speed = FXMAC_MSG_PHY_SPEED_1000M;  /* FXMAC_PHY_SPEED_XXX */
    os_config.phy_duplex = FXMAC_MSG_PHY_FULL_DUPLEX; /* FXMAC_PHY_XXX_DUPLEX */

    pOsMac = FXmacMsgOsGetInstancePointer(&os_config);
    if (pOsMac == NULL)
    {
        LOG_E("FXmacMsgOsGetInstancePointer is error\r\n");
        return -RT_ERROR;
    }

    const char *os_drv_xmac0_name = "e0";
    const char *e0_thread_name = "e0_link_detect";

    state = rt_hw_xmac_msg_init(pOsMac, os_drv_xmac0_name, e0_thread_name);
    extern void set_if(const char *netif_name, const char *ip_addr, const char *gw_addr, const char *nm_addr);

    rt_kprintf("Set netif %s ip addr!\n", os_drv_xmac0_name);
    set_if(os_drv_xmac0_name, "192.168.4.10", "192.168.4.1", "255.255.255.0");
    if (RT_EOK != state)
    {
        goto __exit;
    }
#endif
#if defined(RT_USING_XMAC1_MSG)
    os_config.instance_id = MAC_NUM1_CONTROLLER;
    os_config.interface = MAC_NUM1_MII_INTERFACE;
    os_config.autonegotiation = 1; /* 1 is autonegotiation ,0 is manually set */
    os_config.phy_speed = FXMAC_MSG_PHY_SPEED_1000M;  /* FXMAC_PHY_SPEED_XXX */
    os_config.phy_duplex = FXMAC_MSG_PHY_FULL_DUPLEX; /* FXMAC_PHY_XXX_DUPLEX */

    pOsMac = FXmacMsgOsGetInstancePointer(&os_config);
    if (pOsMac == NULL)
    {
        LOG_E("FXmacMsgOsGetInstancePointer is error\r\n");
        return -RT_ERROR;
    }

    const char *os_drv_xmac1_name = "e1";
    const char *e1_thread_name = "e1_link_detect";

    state = rt_hw_xmac_msg_init(pOsMac, os_drv_xmac1_name, e1_thread_name);
    rt_kprintf("Set Xmac %s ip addr!\n", os_drv_xmac1_name);
    set_if(os_drv_xmac1_name, "192.168.4.11", "192.168.4.1", "255.255.255.0");
    if (RT_EOK != state)
    {
        goto __exit;
    }
#endif

#if defined(RT_USING_XMAC0_MSG)
        rt_kprintf("Start Xmac NUM0 \n");
        FXmacMsgOsStart(&fxmac_os_instace[MAC_NUM0_CONTROLLER]);
#endif
#if defined(RT_USING_XMAC1_MSG)
        rt_kprintf("Start Xmac NUM1 \n");
        FXmacMsgOsStart(&fxmac_os_instace[MAC_NUM1_CONTROLLER]);
#endif

__exit:
    return state;
}
INIT_DEVICE_EXPORT(rt_hw_xmac_msg_eth_init);
#endif