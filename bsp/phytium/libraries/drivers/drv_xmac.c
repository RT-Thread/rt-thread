/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2022-07-07  liuzhihong   first commit
 * 2023-07-14  liuzhihong   support RT-Smart
 */

#include "board.h"

#ifdef BSP_USING_ETH

#include "mm_aspace.h"
#ifdef RT_USING_SMART
    #include "ioremap.h"
#endif

#ifdef __aarch64__
    #include "faarch64.h"
#else
    #include "faarch32.h"
#endif

#include "drv_xmac.h"


#define FXMAC_OS_XMAC_DEBUG_TAG "FXMAC_OS_XMAC"
#define FXMAC_OS_XMAC_PRINT_E(format, ...) FT_DEBUG_PRINT_E(FXMAC_OS_XMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FXMAC_OS_XMAC_PRINT_I(format, ...) FT_DEBUG_PRINT_I(FXMAC_OS_XMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FXMAC_OS_XMAC_PRINT_D(format, ...) FT_DEBUG_PRINT_D(FXMAC_OS_XMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FXMAC_OS_XMAC_PRINT_W(format, ...) FT_DEBUG_PRINT_W(FXMAC_OS_XMAC_DEBUG_TAG, format, ##__VA_ARGS__)

#define LOG_E(format, ...) FT_DEBUG_PRINT_E(FXMAC_OS_XMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define LOG_I(format, ...) FT_DEBUG_PRINT_I(FXMAC_OS_XMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define LOG_D(format, ...) FT_DEBUG_PRINT_D(FXMAC_OS_XMAC_DEBUG_TAG, format, ##__VA_ARGS__)

#define FXMAC_BD_TO_INDEX(ringptr, bdptr) \
    (((uintptr)bdptr - (uintptr)(ringptr)->base_bd_addr) / (ringptr)->separation)


static char *os_drv_xmac0_name = "e0";

static void FXmacInitOnError(FXmacOs *instance_p);
static void FXmacSetupIsr(FXmacOs *instance_p);

static FXmacOs fxmac_os_instace[FXMAC_NUM] =
{
    [FXMAC0_ID] = {.config = (0)},
    [FXMAC1_ID] = {.config = (0)},
    [FXMAC2_ID] = {.config = (0)},
    [FXMAC3_ID] = {.config = (0)},
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
static u32 IsTxSpaceAvailable(FXmacOs *instance_p)
{
    FXmacBdRing *txring;
    u32 freecnt;
    FASSERT(instance_p != NULL);

    txring = &(FXMAC_GET_TXRING(instance_p->instance));

    /* tx space is available as long as there are valid BD's */
    freecnt = FXMAC_BD_RING_GET_FREE_CNT(txring);
    return freecnt;
}

/**
 * @name: FXmacProcessSentBds
 * @msg:   Free up memory space of pbuf on the send queue
 * @return {*}
 * @param {ethernetif} *ethernetif_p
 * @param {FXmacBdRing} *txring
 */
void FXmacProcessSentBds(FXmacOs *instance_p, FXmacBdRing *txring)
{
    FXmacBd *txbdset;
    FXmacBd *curbdpntr;
    u32 n_bds;
    FError status;
    u32 n_pbufs_freed;
    u32 bdindex;
    struct pbuf *p;
    u32 *temp;

    while (1)
    {
        /* obtain processed BD's */
        n_bds = FXmacBdRingFromHwTx(txring, FXMAX_TX_PBUFS_LENGTH, &txbdset);
        if (n_bds == 0)
        {
            return;
        }
        /* free the processed BD's */
        n_pbufs_freed = n_bds;
        curbdpntr = txbdset;
        while (n_pbufs_freed > 0)
        {
            bdindex = FXMAC_BD_TO_INDEX(txring, curbdpntr);
            temp = (u32 *)curbdpntr;
            *temp = 0; /* Word 0 */
            temp++;
            if (bdindex == (FXMAX_TX_PBUFS_LENGTH - 1))
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
            curbdpntr = FXMAC_BD_RING_NEXT(txring, curbdpntr);
            n_pbufs_freed--;

        }

        status = FXmacBdRingFree(txring, n_bds, txbdset);
        if (status != FT_SUCCESS)
        {
            FXMAC_OS_XMAC_PRINT_I("Failure while freeing in Tx Done ISR.");
        }
    }
    return;
}

void FXmacSendHandler(void *arg)
{
    FXmacOs *instance_p;
    FXmacBdRing *txringptr;
    u32 regval;

    instance_p = (FXmacOs *)arg;
    txringptr = &(FXMAC_GET_TXRING(instance_p->instance));
    regval = FXMAC_READREG32(instance_p->instance.config.base_address, FXMAC_TXSR_OFFSET);
    FXMAC_WRITEREG32(instance_p->instance.config.base_address, FXMAC_TXSR_OFFSET, regval); /* 清除中断状态位来停止中断 */

    /* If Transmit done interrupt is asserted, process completed BD's */
    FXmacProcessSentBds(instance_p, txringptr);
}

FError FXmacSgsend(FXmacOs *instance_p, struct pbuf *p)
{
    struct pbuf *q;
    u32 n_pbufs;
    FXmacBd *txbdset, *txbd, *last_txbd = NULL;
    FXmacBd *temp_txbd;
    FError status;
    FXmacBdRing *txring;
    u32 bdindex;
    uintptr tx_payload ;
    u32 max_fr_size;


    txring = &(FXMAC_GET_TXRING(instance_p->instance));

    /* first count the number of pbufs */
    for (q = p, n_pbufs = 0; q != NULL; q = q->next)
    {
        n_pbufs++;
    }

    /* obtain as many BD's */
    status = FXmacBdRingAlloc(txring, n_pbufs, &txbdset);
    if (status != FT_SUCCESS)
    {
        FXMAC_OS_XMAC_PRINT_I("sgsend: Error allocating TxBD.");
        return ERR_GENERAL;
    }

    for (q = p, txbd = txbdset; q != NULL; q = q->next)
    {
        bdindex = FXMAC_BD_TO_INDEX(txring, txbd);

        if (instance_p->buffer.tx_pbufs_storage[bdindex])
        {
            FXMAC_OS_XMAC_PRINT_I("txbd %p, txring->base_bd_addr %p", txbd, txring->base_bd_addr);
            FXMAC_OS_XMAC_PRINT_I("PBUFS not available bdindex is %d ", bdindex);
            FXMAC_OS_XMAC_PRINT_I("instance_p->buffer.tx_pbufs_storage[bdindex] %p ", instance_p->buffer.tx_pbufs_storage[bdindex]);
            return ERR_GENERAL;
        }

        /* Send the data from the pbuf to the interface, one pbuf at a
           time. The size of the data in each pbuf is kept in the ->len
           variable. */
        tx_payload = (uintptr)p->payload;
#ifdef RT_USING_SMART
        tx_payload += PV_OFFSET;
#endif
        FXMAC_BD_SET_ADDRESS_TX(txbd, (uintptr)tx_payload);
        if (instance_p->config & FXMAC_OS_CONFIG_JUMBO)
        {
            max_fr_size = FXMAC_MAX_FRAME_SIZE_JUMBO;
        }
        else
        {
            max_fr_size = FXMAC_MAX_FRAME_SIZE;
        }

        if (q->len > max_fr_size)
        {
            FXMAC_BD_SET_LENGTH(txbd, max_fr_size & 0x3FFF);
        }
        else
        {
            FXMAC_BD_SET_LENGTH(txbd, q->len & 0x3FFF);
        }

        instance_p->buffer.tx_pbufs_storage[bdindex] = (uintptr)q;

        pbuf_ref(q);
        last_txbd = txbd;
        FXMAC_BD_CLEAR_LAST(txbd);
        txbd = FXMAC_BD_RING_NEXT(txring, txbd);
    }
    FXMAC_BD_SET_LAST(last_txbd);
    /* For fragmented packets, remember the 1st BD allocated for the 1st
       packet fragment. The used bit for this BD should be cleared at the end
       after clearing out used bits for other fragments. For packets without
       just remember the allocated BD. */
    temp_txbd = txbdset;
    txbd = txbdset;
    txbd = FXMAC_BD_RING_NEXT(txring, txbd);
    q = p->next;
    for (; q != NULL; q = q->next)
    {
        FXMAC_BD_CLEAR_TX_USED(txbd);

        txbd = FXMAC_BD_RING_NEXT(txring, txbd);
    }
    FXMAC_BD_CLEAR_TX_USED(temp_txbd);


    status = FXmacBdRingToHw(txring, n_pbufs, txbdset);
    if (status != FT_SUCCESS)
    {
        FXMAC_OS_XMAC_PRINT_I("sgsend: Error submitting TxBD.");
        return ERR_GENERAL;
    }
    /* Start transmit */
    FXMAC_WRITEREG32((instance_p->instance).config.base_address,
                     FXMAC_NWCTRL_OFFSET,
                     (FXMAC_READREG32(instance_p->instance.config.base_address,
                                      FXMAC_NWCTRL_OFFSET) |
                      FXMAC_NWCTRL_STARTTX_MASK));

    return status;
}

void SetupRxBds(FXmacOs *instance_p, FXmacBdRing *rxring)
{
    FXmacBd *rxbd;
    FError status;
    struct pbuf *p;
    u32 freebds;
    u32 bdindex;
    u32 *temp;
    uintptr_t pl_paddr;
    freebds = FXMAC_BD_RING_GET_FREE_CNT(rxring);
    while (freebds > 0)
    {
        freebds--;

        if (instance_p->config & FXMAC_OS_CONFIG_JUMBO)
        {
            p = pbuf_alloc(PBUF_RAW, FXMAC_MAX_FRAME_SIZE_JUMBO, PBUF_POOL);
        }
        else
        {
            p = pbuf_alloc(PBUF_RAW, FXMAC_MAX_FRAME_SIZE, PBUF_POOL);
        }

        if (!p)
        {
#if LINK_STATS
            lwip_stats.link.memerr++;
            lwip_stats.link.drop++;
#endif
            FXMAC_OS_XMAC_PRINT_I("Unable to alloc pbuf in recv_handler.");
            return;
        }
        status = FXmacBdRingAlloc(rxring, 1, &rxbd);
        if (status != FT_SUCCESS)
        {
            FXMAC_OS_XMAC_PRINT_I("SetupRxBds: Error allocating RxBD.");
            pbuf_free(p);
            return;
        }
        status = FXmacBdRingToHw(rxring, 1, rxbd);
        if (status != FT_SUCCESS)
        {
            FXMAC_OS_XMAC_PRINT_I("Error committing RxBD to hardware: ");
            if (status == FXMAC_ERR_SG_LIST)
            {
                FXMAC_OS_XMAC_PRINT_I("XST_DMA_SG_LIST_ERROR: this function was called out of sequence with FXmacBdRingAlloc().");
            }
            else
            {
                FXMAC_OS_XMAC_PRINT_I("Set of BDs was rejected because the first BD did not have its start-of-packet bit set, or the last BD did not have its end-of-packet bit set, or any one of the BD set has 0 as length value.");
            }

            pbuf_free(p);
            FXmacBdRingUnAlloc(rxring, 1, rxbd);
            return;
        }

        bdindex = FXMAC_BD_TO_INDEX(rxring, rxbd);
        temp = (u32 *)rxbd;
        if (bdindex == (FXMAX_RX_PBUFS_LENGTH - 1))
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
        FXMAC_BD_SET_ADDRESS_RX(rxbd, (uintptr)pl_paddr);
        instance_p->buffer.rx_pbufs_storage[bdindex] = (uintptr)p;
    }
}
void FXmacRecvSemaphoreHandler(void *arg)
{
    FXmacOs *instance_p;
    rt_err_t result;

    if (RT_NULL == arg)
    {
        LOG_E("Args is NULL");
        return;
    }

    instance_p = (FXmacOs *)arg;

    result = eth_device_ready(&(instance_p->parent));
    if (result != RT_EOK)
    {
        LOG_I("RxCpltCallback err = %d", result);
    }

}
void FXmacRecvHandler(void *arg)
{
    struct pbuf *p;
    FXmacBd *rxbdset, *curbdptr;
    FXmacBdRing *rxring;
    volatile u32 bd_processed;
    u32 rx_bytes, k;
    u32 bdindex;
    u32 regval;
    FXmacOs *instance_p;
    FASSERT(arg != NULL);

    instance_p = (FXmacOs *)arg;
    rxring = &FXMAC_GET_RXRING(instance_p->instance);

    /* If Reception done interrupt is asserted, call RX call back function
     to handle the processed BDs and then raise the according flag.*/
    regval = FXMAC_READREG32(instance_p->instance.config.base_address, FXMAC_RXSR_OFFSET);
    FXMAC_WRITEREG32(instance_p->instance.config.base_address, FXMAC_RXSR_OFFSET, regval);

    while (1)
    {
        bd_processed = FXmacBdRingFromHwRx(rxring, FXMAX_RX_PBUFS_LENGTH, &rxbdset);
        if (bd_processed <= 0)
        {
            break;
        }

        for (k = 0, curbdptr = rxbdset; k < bd_processed; k++)
        {

            bdindex = FXMAC_BD_TO_INDEX(rxring, curbdptr);
            p = (struct pbuf *)instance_p->buffer.rx_pbufs_storage[bdindex];
            /*
             * Adjust the buffer size to the actual number of bytes received.
             */
            if (instance_p->config & FXMAC_OS_CONFIG_JUMBO)
            {
                rx_bytes = FXMAC_GET_RX_FRAME_SIZE(curbdptr);
            }
            else
            {
                rx_bytes = FXMAC_BD_GET_LENGTH(curbdptr);
            }

            pbuf_realloc(p, rx_bytes);

            /* Invalidate RX frame before queuing to handle
             * L1 cache prefetch conditions on any architecture.
             */
            // FCacheDCacheInvalidateRange((uintptr)p->payload, rx_bytes);

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
            curbdptr = FXMAC_BD_RING_NEXT(rxring, curbdptr);
        }

        /* free up the BD's */
        FXmacBdRingFree(rxring, bd_processed, rxbdset);
        SetupRxBds(instance_p, rxring);

    }

    return;
}


void CleanDmaTxdescs(FXmacOs *instance_p)
{
    FXmacBd bdtemplate;
    FXmacBdRing *txringptr;

    txringptr = &FXMAC_GET_TXRING((instance_p->instance));
    FXMAC_BD_CLEAR(&bdtemplate);
    FXMAC_BD_SET_STATUS(&bdtemplate, FXMAC_TXBUF_USED_MASK);

    FXmacBdRingCreate(txringptr, (uintptr)instance_p->buffer.tx_bdspace,
                      (uintptr)instance_p->buffer.tx_bdspace, BD_ALIGNMENT,
                      sizeof(instance_p->buffer.tx_bdspace));

    FXmacBdRingClone(txringptr, &bdtemplate, FXMAC_SEND);
}

FError FXmacInitDma(FXmacOs *instance_p)
{
    FXmacBd bdtemplate;
    FXmacBdRing *rxringptr, *txringptr;
    FXmacBd *rxbd;
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

    rxringptr = &FXMAC_GET_RXRING(instance_p->instance);
    txringptr = &FXMAC_GET_TXRING(instance_p->instance);
    FXMAC_OS_XMAC_PRINT_I("rxringptr: 0x%08x", rxringptr);
    FXMAC_OS_XMAC_PRINT_I("txringptr: 0x%08x", txringptr);

    FXMAC_OS_XMAC_PRINT_I("rx_bdspace: %p ", instance_p->buffer.rx_bdspace);
    FXMAC_OS_XMAC_PRINT_I("tx_bdspace: %p ", instance_p->buffer.tx_bdspace);

    /* Setup RxBD space. */
    FXMAC_BD_CLEAR(&bdtemplate);
    rx_paddr = (uintptr)instance_p->buffer.rx_bdspace;
#ifdef RT_USING_SMART
    rx_paddr += PV_OFFSET;
#endif

    /* Create the RxBD ring */
    status = FXmacBdRingCreate(rxringptr, (uintptr)rx_paddr,
                               (uintptr)instance_p->buffer.rx_bdspace, BD_ALIGNMENT,
                               FXMAX_RX_PBUFS_LENGTH);

    if (status != FT_SUCCESS)
    {
        FXMAC_OS_XMAC_PRINT_I("Error setting up RxBD space.");
        return ERR_IF;
    }

    status = FXmacBdRingClone(rxringptr, &bdtemplate, FXMAC_RECV);
    if (status != FT_SUCCESS)
    {
        FXMAC_OS_XMAC_PRINT_I("Error initializing RxBD space.");
        return ERR_IF;
    }

    FXMAC_BD_CLEAR(&bdtemplate);
    FXMAC_BD_SET_STATUS(&bdtemplate, FXMAC_TXBUF_USED_MASK);

    tx_paddr = (uintptr)instance_p->buffer.tx_bdspace;
#ifdef RT_USING_SMART
    tx_paddr += PV_OFFSET;
#endif
    /* Create the TxBD ring */
    status = FXmacBdRingCreate(txringptr, (uintptr)tx_paddr,
                               (uintptr)instance_p->buffer.tx_bdspace, BD_ALIGNMENT,
                               FXMAX_TX_PBUFS_LENGTH);

    if (status != FT_SUCCESS)
    {
        return ERR_IF;
    }

    /* We reuse the bd template, as the same one will work for both rx and tx. */
    status = FXmacBdRingClone(txringptr, &bdtemplate, FXMAC_SEND);
    if (status != FT_SUCCESS)
    {
        return ERR_IF;
    }

    /*
     * Allocate RX descriptors, 1 RxBD at a time.
     */
    for (i = 0; i < FXMAX_RX_PBUFS_LENGTH; i++)
    {
        if (instance_p->config & FXMAC_OS_CONFIG_JUMBO)
        {
            p = pbuf_alloc(PBUF_RAW, FXMAC_MAX_FRAME_SIZE_JUMBO, PBUF_POOL);
        }
        else
        {
            p = pbuf_alloc(PBUF_RAW, FXMAC_MAX_FRAME_SIZE, PBUF_POOL);
        }

        if (!p)
        {
#if LINK_STATS
            lwip_stats.link.memerr++;
            lwip_stats.link.drop++;
#endif
            FXMAC_OS_XMAC_PRINT_E("Unable to alloc pbuf in InitDma.");
            return ERR_IF;
        }
        status = FXmacBdRingAlloc(rxringptr, 1, &rxbd);
        if (status != FT_SUCCESS)
        {
            FXMAC_OS_XMAC_PRINT_E("InitDma: Error allocating RxBD.");
            pbuf_free(p);
            return ERR_IF;
        }
        /* Enqueue to HW */
        status = FXmacBdRingToHw(rxringptr, 1, rxbd);
        if (status != FT_SUCCESS)
        {
            FXMAC_OS_XMAC_PRINT_E("Error: committing RxBD to HW.");
            pbuf_free(p);
            FXmacBdRingUnAlloc(rxringptr, 1, rxbd);
            return ERR_IF;
        }

        bdindex = FXMAC_BD_TO_INDEX(rxringptr, rxbd);
        temp = (u32 *)rxbd;
        *temp = 0;
        if (bdindex == (FXMAX_RX_PBUFS_LENGTH - 1))
        {
            *temp = 0x00000002;
        }
        temp++;
        *temp = 0;

        pl_paddr = (uintptr)p->payload;
#ifdef RT_USING_SMART
        pl_paddr += PV_OFFSET;
#endif
        FXMAC_BD_SET_ADDRESS_RX(rxbd, (uintptr)pl_paddr);

        instance_p->buffer.rx_pbufs_storage[bdindex] = (uintptr)p;
    }

    FXmacSetQueuePtr(&(instance_p->instance), instance_p->instance.tx_bd_queue.bdring.phys_base_addr, 0, (u16)FXMAC_SEND);
    FXmacSetQueuePtr(&(instance_p->instance), instance_p->instance.rx_bd_queue.bdring.phys_base_addr, 0, (u16)FXMAC_RECV);

    return 0;
}

static void FreeOnlyTxPbufs(FXmacOs *instance_p)
{
    u32 index;
    struct pbuf *p;

    for (index = 0; index < (FXMAX_TX_PBUFS_LENGTH); index++)
    {
        if (instance_p->buffer.tx_pbufs_storage[index] != 0)
        {
            p = (struct pbuf *)instance_p->buffer.tx_pbufs_storage[index];
            pbuf_free(p);
            instance_p->buffer.tx_pbufs_storage[index] = (uintptr)NULL;
        }
        instance_p->buffer.tx_pbufs_storage[index] = (uintptr)0;
    }
}


static void FreeOnlyRxPbufs(FXmacOs *instance_p)
{
    u32 index;
    struct pbuf *p;

    for (index = 0; index < (FXMAX_RX_PBUFS_LENGTH); index++)
    {
        if (instance_p->buffer.rx_pbufs_storage[index] != 0)
        {
            p = (struct pbuf *)instance_p->buffer.rx_pbufs_storage[index];
            pbuf_free(p);
            instance_p->buffer.rx_pbufs_storage[index] = (uintptr)0;
        }
    }
}


static void FreeTxRxPbufs(FXmacOs *instance_p)
{
    u32 rx_queue_len;
    struct pbuf *p;
    /* first :free PqQueue data */
    rx_queue_len = FXmacPqQlength(&instance_p->recv_q);

    while (rx_queue_len)
    {
        /* return one packet from receive q */
        p = (struct pbuf *)FXmacPqDequeue(&instance_p->recv_q);
        pbuf_free(p);
        FXMAC_OS_XMAC_PRINT_E("Delete queue %p", p);
        rx_queue_len--;
    }
    FreeOnlyTxPbufs(instance_p);
    FreeOnlyRxPbufs(instance_p);

}

/* interrupt */
static void FXmacHandleDmaTxError(FXmacOs *instance_p)
{
    s32_t status = FT_SUCCESS;
    u32 dmacrreg;

    FreeTxRxPbufs(instance_p);
    status = FXmacCfgInitialize(&instance_p->instance, &instance_p->instance.config);

    if (status != FT_SUCCESS)
    {
        FXMAC_OS_XMAC_PRINT_E("In %s:EmacPs Configuration Failed....", __func__);
    }

    /* initialize the mac */
    FXmacInitOnError(instance_p); /* need to set mac filter address */
    dmacrreg = FXMAC_READREG32(instance_p->instance.config.base_address, FXMAC_DMACR_OFFSET);
    dmacrreg = dmacrreg | (FXMAC_DMACR_ORCE_DISCARD_ON_ERR_MASK); /* force_discard_on_err */
    FXMAC_WRITEREG32(instance_p->instance.config.base_address, FXMAC_DMACR_OFFSET, dmacrreg);
    FXmacSetupIsr(instance_p);
    FXmacInitDma(instance_p);

    FXmacStart(&instance_p->instance);

}

void FXmacHandleTxErrors(FXmacOs *instance_p)
{
    u32 netctrlreg;

    netctrlreg = FXMAC_READREG32(instance_p->instance.config.base_address,
                                 FXMAC_NWCTRL_OFFSET);
    netctrlreg = netctrlreg & (~FXMAC_NWCTRL_TXEN_MASK);
    FXMAC_WRITEREG32(instance_p->instance.config.base_address,
                     FXMAC_NWCTRL_OFFSET, netctrlreg);
    FreeOnlyTxPbufs(instance_p);

    CleanDmaTxdescs(instance_p);
    netctrlreg = FXMAC_READREG32(instance_p->instance.config.base_address, FXMAC_NWCTRL_OFFSET);
    netctrlreg = netctrlreg | (FXMAC_NWCTRL_TXEN_MASK);
    FXMAC_WRITEREG32(instance_p->instance.config.base_address, FXMAC_NWCTRL_OFFSET, netctrlreg);
}

void FXmacErrorHandler(void *arg, u8 direction, u32 error_word)
{
    FXmacBdRing *rxring;
    FXmacBdRing *txring;
    FXmacOs *instance_p;

    instance_p = (FXmacOs *)arg;
    rxring = &FXMAC_GET_RXRING(instance_p->instance);
    txring = &FXMAC_GET_TXRING(instance_p->instance);

    if (error_word != 0)
    {
        switch (direction)
        {
        case FXMAC_RECV:
            if (error_word & FXMAC_RXSR_HRESPNOK_MASK)
            {
                FXMAC_OS_XMAC_PRINT_I("Receive DMA error.");
                FXmacHandleDmaTxError(instance_p);
            }
            if (error_word & FXMAC_RXSR_RXOVR_MASK)
            {
                FXMAC_OS_XMAC_PRINT_I("Receive over run.");
                FXmacRecvHandler(instance_p);
                SetupRxBds(instance_p, rxring);
            }
            if (error_word & FXMAC_RXSR_BUFFNA_MASK)
            {
                FXMAC_OS_XMAC_PRINT_I("Receive buffer not available.");
                FXmacRecvHandler(arg);
                SetupRxBds(instance_p, rxring);
            }
            break;
        case FXMAC_SEND:
            if (error_word & FXMAC_TXSR_HRESPNOK_MASK)
            {
                FXMAC_OS_XMAC_PRINT_I("Transmit DMA error.");
                FXmacHandleDmaTxError(instance_p);
            }
            if (error_word & FXMAC_TXSR_URUN_MASK)
            {
                FXMAC_OS_XMAC_PRINT_I("Transmit under run.");
                FXmacHandleTxErrors(instance_p);
            }
            if (error_word & FXMAC_TXSR_BUFEXH_MASK)
            {
                FXMAC_OS_XMAC_PRINT_I("Transmit buffer exhausted.");
                FXmacHandleTxErrors(instance_p);
            }
            if (error_word & FXMAC_TXSR_RXOVR_MASK)
            {
                FXMAC_OS_XMAC_PRINT_I("Transmit retry excessed limits.");
                FXmacHandleTxErrors(instance_p);
            }
            if (error_word & FXMAC_TXSR_FRAMERX_MASK)
            {
                FXMAC_OS_XMAC_PRINT_I("Transmit collision.");
                FXmacProcessSentBds(instance_p, txring);
            }
            break;
        }
    }
}

void FXmacLinkChange(void *arg)
{
    u32 ctrl;
    u32 link, link_status;
    u32 speed;
    u32 speed_bit;
    u32 duplex;
    FXmac *xmac_p;
    FXmacOs *instance_p;

    instance_p = (FXmacOs *)arg;
    xmac_p = &instance_p->instance;

    if (xmac_p->config.interface == FXMAC_PHY_INTERFACE_MODE_SGMII)
    {
        FXMAC_OS_XMAC_PRINT_I("xmac_p->config.base_address is %p", xmac_p->config.base_address);
        ctrl = FXMAC_READREG32(xmac_p->config.base_address, FXMAC_PCS_AN_LP_OFFSET);
        link = (ctrl & FXMAC_PCS_LINK_PARTNER_NEXT_PAGE_STATUS) >> 15;
        FXMAC_OS_XMAC_PRINT_I("Link status is 0x%x", link);

        switch (link)
        {
        case 0:
            link_status = FXMAC_LINKDOWN;
            break;
        case 1:
            link_status = FXMAC_LINKUP;
            break;
        default:
            FXMAC_OS_XMAC_PRINT_E("Link status is error 0x%x ", link);
            return;
        }

        if (xmac_p->config.auto_neg == 0)
        {
            if (link_status == FXMAC_LINKUP)
            {
                FXMAC_OS_XMAC_PRINT_I("No neg link up (%d/%s)", xmac_p->config.speed, xmac_p->config.duplex == 1 ? "FULL" : "Half");
                xmac_p->link_status = FXMAC_NEGOTIATING;
            }
            else
            {
                FXMAC_OS_XMAC_PRINT_I("No neg link down.");
                xmac_p->link_status = FXMAC_LINKDOWN;
            }
        }

        /* read sgmii reg to get status */
        ctrl = FXMAC_READREG32(xmac_p->config.base_address, FXMAC_PCS_AN_LP_OFFSET);
        speed_bit = (ctrl & FXMAC_PCS_AN_LP_SPEED) >> FXMAC_PCS_AN_LP_SPEED_OFFSET;
        duplex = (ctrl & FXMAC_PCS_AN_LP_DUPLEX) >> FXMAC_PCS_AN_LP_DUPLEX_OFFSET;

        if (speed_bit == 2)
        {
            speed = FXMAC_SPEED_1000;
        }
        else if (speed_bit == 1)
        {
            speed = FXMAC_SPEED_100;
        }
        else
        {
            speed = FXMAC_SPEED_10;
        }

        if (link_status != xmac_p->link_status)
        {
            FXMAC_OS_XMAC_PRINT_I("Sgmii link_status has changed.");
        }

        /* add erase NCFGR config */
        if ((speed != xmac_p->config.speed) || (duplex != xmac_p->config.duplex))
        {
            FXMAC_OS_XMAC_PRINT_I("Sgmii link_status has changed.");
            FXMAC_OS_XMAC_PRINT_I("New speed is %d, duplex is %d", speed, duplex);
        }

        if (link_status == FXMAC_LINKUP)
        {
            if (link_status != xmac_p->link_status)
            {
                xmac_p->link_status = FXMAC_NEGOTIATING;
                FXMAC_OS_XMAC_PRINT_I("Need NEGOTIATING.");
            }
        }
        else
        {
            xmac_p->link_status = link_status;
            FXMAC_OS_XMAC_PRINT_I("Change status is 0x%x", link_status);
        }
    }
}

/* phy */

/**
 * @name: FXmacPhyLinkDetect
 * @msg:  Get current link status
 * @note:
 * @param {FXmac} *fxmac_p
 * @param {u32} phy_addr
 * @return {*} 1 is link up , 0 is link down
 */
static u32 FXmacPhyLinkDetect(FXmac *xmac_p, u32 phy_addr)
{
    u16 status;

    /* Read Phy Status register twice to get the confirmation of the current
     * link status.
     */

    FXmacPhyRead(xmac_p, phy_addr, PHY_STATUS_REG_OFFSET, &status);

    if (status & PHY_STAT_LINK_STATUS)
    {
        return 1;
    }
    return 0;
}

static u32 FXmacPhyAutonegStatus(FXmac *xmac_p, u32 phy_addr)
{
    u16 status;

    /* Read Phy Status register twice to get the confirmation of the current
     * link status.
     */
    FXmacPhyRead(xmac_p, phy_addr, PHY_STATUS_REG_OFFSET, &status);

    if (status & PHY_STATUS_AUTONEGOTIATE_COMPLETE)
    {
        return 1;
    }
    return 0;
}

enum lwip_port_link_status FXmacLwipPortLinkDetect(FXmacOs *instance_p)
{
    u32 phy_link_status;
    FXmac *xmac_p = &instance_p->instance;

    if (xmac_p->is_ready != (u32)FT_COMPONENT_IS_READY)
    {
        return ETH_LINK_UNDEFINED;
    }

    phy_link_status = FXmacPhyLinkDetect(xmac_p, xmac_p->phy_address);

    if ((xmac_p->link_status == FXMAC_LINKUP) && (!phy_link_status))
    {
        xmac_p->link_status = FXMAC_LINKDOWN;
    }

    switch (xmac_p->link_status)
    {
    case FXMAC_LINKUP:
        return ETH_LINK_UP;
    case FXMAC_LINKDOWN:
        xmac_p->link_status = FXMAC_NEGOTIATING;
        FXMAC_OS_XMAC_PRINT_D("Ethernet Link down.");
        return ETH_LINK_DOWN;
    case FXMAC_NEGOTIATING:
        if ((phy_link_status == FXMAC_LINKUP) && FXmacPhyAutonegStatus(xmac_p, xmac_p->phy_address))
        {
            err_t phy_ret;
            phy_ret = FXmacPhyInit(xmac_p, xmac_p->config.speed, xmac_p->config.duplex, xmac_p->config.auto_neg);

            if (phy_ret != FT_SUCCESS)
            {
                FXMAC_OS_XMAC_PRINT_E("FXmacPhyInit is error.");
                return ETH_LINK_DOWN;
            }
            FXmacSelectClk(xmac_p);
            FXmacInitInterface(xmac_p);

            /* Initiate Phy setup to get link speed */
            xmac_p->link_status = FXMAC_LINKUP;
            FXMAC_OS_XMAC_PRINT_D("Ethernet Link up.");
            return ETH_LINK_UP;
        }
        return ETH_LINK_DOWN;
    default:
        return ETH_LINK_DOWN;
    }
}

enum lwip_port_link_status FXmacPhyReconnect(FXmacOs *instance_p)
{
    FXmac *xmac_p;

    xmac_p = &instance_p->instance;

    if (xmac_p->config.interface == FXMAC_PHY_INTERFACE_MODE_SGMII)
    {
        rt_hw_interrupt_mask(xmac_p->config.queue_irq_num[0]);
        if (xmac_p->link_status == FXMAC_NEGOTIATING)
        {
            /* auto negotiation again*/
            err_t phy_ret;
            phy_ret = FXmacPhyInit(xmac_p, xmac_p->config.speed, xmac_p->config.duplex, xmac_p->config.auto_neg);
            if (phy_ret != FT_SUCCESS)
            {
                FXMAC_OS_XMAC_PRINT_I("FXmacPhyInit is error.");
                rt_hw_interrupt_umask(xmac_p->config.queue_irq_num[0]);
                return ETH_LINK_DOWN;
            }
            FXmacSelectClk(xmac_p);
            FXmacInitInterface(xmac_p);
            xmac_p->link_status = FXMAC_LINKUP;
        }

        rt_hw_interrupt_umask(xmac_p->config.queue_irq_num[0]);

        switch (xmac_p->link_status)
        {
        case FXMAC_LINKDOWN:
            return ETH_LINK_DOWN;
        case FXMAC_LINKUP:
            return ETH_LINK_UP;
        default:
            return ETH_LINK_DOWN;
        }
    }
    else if ((xmac_p->config.interface == FXMAC_PHY_INTERFACE_MODE_RMII) || (xmac_p->config.interface == FXMAC_PHY_INTERFACE_MODE_RGMII))
    {
        return FXmacLwipPortLinkDetect(instance_p);
    }
    else
    {
        switch (xmac_p->link_status)
        {
        case FXMAC_LINKDOWN:
            return ETH_LINK_DOWN;
        case FXMAC_LINKUP:
            return ETH_LINK_UP;
        default:
            return ETH_LINK_DOWN;
        }
    }
}

static void FxmacOsIntrHandler(s32 vector, void *args)
{
    isr_calling_flg++;
    FXmacIntrHandler(vector, args);
    isr_calling_flg--;
}

static void FXmacSetupIsr(FXmacOs *instance_p)
{
    u32 cpu_id;
    GetCpuId(&cpu_id);

    /* Setup callbacks */
    FXmacSetHandler(&instance_p->instance, FXMAC_HANDLER_DMASEND, FXmacSendHandler, instance_p);
    FXmacSetHandler(&instance_p->instance, FXMAC_HANDLER_DMARECV, FXmacRecvSemaphoreHandler, instance_p);
    FXmacSetHandler(&instance_p->instance, FXMAC_HANDLER_ERROR, FXmacErrorHandler, instance_p);
    FXmacSetHandler(&instance_p->instance, FXMAC_HANDLER_LINKCHANGE, FXmacLinkChange, instance_p);

    rt_hw_interrupt_install(instance_p->instance.config.queue_irq_num[0], FxmacOsIntrHandler, &instance_p->instance, "fxmac");
    rt_hw_interrupt_umask(instance_p->instance.config.queue_irq_num[0]);
}

/*  init fxmac instance */

static void FXmacInitOnError(FXmacOs *instance_p)
{
    FXmac *xmac_p;
    u32 status = FT_SUCCESS;
    xmac_p = &instance_p->instance;

    /* set mac address */
    status = FXmacSetMacAddress(xmac_p, (void *)(instance_p->hwaddr), 1);
    if (status != FT_SUCCESS)
    {
        FXMAC_OS_XMAC_PRINT_E("In %s:Emac Mac Address set failed...", __func__);
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

FError FXmacOsInit(FXmacOs *instance_p)
{
    FXmacConfig mac_config;
    FXmacConfig *mac_config_p;
    FXmacPhyInterface interface = FXMAC_PHY_INTERFACE_MODE_SGMII;
    FXmac *xmac_p;
    u32 dmacrreg;
    FError status;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->mac_config.instance_id < FXMAC_NUM);

    xmac_p = &instance_p->instance;
    FXMAC_OS_XMAC_PRINT_I("instance_id IS %d", instance_p->mac_config.instance_id);
    mac_config_p = FXmacLookupConfig(instance_p->mac_config.instance_id);
    if (mac_config_p == NULL)
    {
        FXMAC_OS_XMAC_PRINT_E("FXmacLookupConfig is error , instance_id is %d", instance_p->mac_config.instance_id);
        return FREERTOS_XMAC_INIT_ERROR;
    }
#ifdef RT_USING_SMART
    mac_config_p->base_address = (uintptr)rt_ioremap((void *)mac_config_p->base_address, 0x2000);
#endif
    mac_config = *mac_config_p;
    switch (instance_p->mac_config.interface)
    {
    case FXMAC_OS_INTERFACE_SGMII:
        interface = FXMAC_PHY_INTERFACE_MODE_SGMII;
        FXMAC_OS_XMAC_PRINT_I("SGMII select.");
        break;
    case FXMAC_OS_INTERFACE_RMII:
        interface = FXMAC_PHY_INTERFACE_MODE_RMII;
        FXMAC_OS_XMAC_PRINT_I("RMII select.");
        break;
    case FXMAC_OS_INTERFACE_RGMII:
        FXMAC_OS_XMAC_PRINT_I("RGMII select.");
        interface = FXMAC_PHY_INTERFACE_MODE_RGMII;
        break;
    default:
        FXMAC_OS_XMAC_PRINT_E("Update interface is error , interface is %d", instance_p->mac_config.instance_id);
        return FREERTOS_XMAC_INIT_ERROR;
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
    case FXMAC_PHY_SPEED_10M:
        mac_config.speed = FXMAC_SPEED_10;
        break;
    case FXMAC_PHY_SPEED_100M:
        mac_config.speed = FXMAC_SPEED_100;
        break;
    case FXMAC_PHY_SPEED_1000M:
        mac_config.speed = FXMAC_SPEED_1000;
        break;
    default:
        FXMAC_OS_XMAC_PRINT_E("Setting speed is not valid , speed is %d", instance_p->mac_config.phy_speed);
        return FREERTOS_XMAC_INIT_ERROR;
    }

    switch (instance_p->mac_config.phy_duplex)
    {
    case FXMAC_PHY_HALF_DUPLEX:
        mac_config.duplex = 0;
        break;
    case FXMAC_PHY_FULL_DUPLEX:
        mac_config.duplex = 1;
        break;
    }

    status = FXmacCfgInitialize(xmac_p, &mac_config);
    if (status != FT_SUCCESS)
    {
        FXMAC_OS_XMAC_PRINT_E("In %s:EmacPs Configuration Failed....", __func__);
    }

    if (instance_p->config & FXMAC_OS_CONFIG_JUMBO)
    {
        FXmacSetOptions(xmac_p, FXMAC_JUMBO_ENABLE_OPTION, 0);
    }

    if (instance_p->config & FXMAC_OS_CONFIG_MULTICAST_ADDRESS_FILITER)
    {
        FXmacSetOptions(xmac_p, FXMAC_MULTICAST_OPTION, 0);
    }

    /* enable copy all frames */
    if (instance_p->config & FXMAC_OS_CONFIG_COPY_ALL_FRAMES)
    {
        FXmacSetOptions(xmac_p, FXMAC_PROMISC_OPTION, 0);
    }

    status = FXmacSetMacAddress(xmac_p, (void *)(instance_p->hwaddr), 0);
    if (status != FT_SUCCESS)
    {
        FXMAC_OS_XMAC_PRINT_E("In %s:Emac Mac Address set failed...", __func__);
    }

    /* close fcs check */
    if (instance_p->config & FXMAC_OS_CONFIG_CLOSE_FCS_CHECK)
    {
        FXmacSetOptions(xmac_p, FXMAC_FCS_STRIP_OPTION, 0);
    }

    /* initialize phy */
    status = FXmacPhyInit(xmac_p, xmac_p->config.speed, xmac_p->config.duplex, xmac_p->config.auto_neg);
    if (status != FT_SUCCESS)
    {
        FXMAC_OS_XMAC_PRINT_W("FXmacPhyInit is error.");
    }

    FXmacSelectClk(xmac_p);
    FXmacInitInterface(xmac_p);

    /* initialize dma */
    dmacrreg = FXMAC_READREG32(xmac_p->config.base_address, FXMAC_DMACR_OFFSET);
    dmacrreg &= (~(FXMAC_DMACR_BLENGTH_MASK));
    dmacrreg |= (FXMAC_DMACR_INCR16_AHB_AXI_BURST); /* Attempt to use bursts of up to 16. */
    FXMAC_WRITEREG32(xmac_p->config.base_address, FXMAC_DMACR_OFFSET, dmacrreg);
    FXmacInitDma(instance_p);


    /* initialize interrupt */
    FXmacSetupIsr(instance_p);

    return FT_SUCCESS;
}




/**
 * @name: FXmacOsRx
 * @msg: struct pbuf *FXmacOsRx(FXmacOs *instance_p)
 * @return {*}
 * @note:
 * @param {FXmacOs} *instance_p
 */
struct pbuf *FXmacOsRx(FXmacOs *instance_p)
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

static FError FXmacOsOutput(FXmacOs *instance_p, struct pbuf *p)
{
    FError status;

    status = FXmacSgsend(instance_p, p);
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

FError FXmacOsTx(FXmacOs *instance_p, void *tx_buf)
{
    u32 freecnt;
    FXmacBdRing *txring;
    FError ret;
    struct pbuf *p;
    FASSERT(instance_p != NULL);
    if (tx_buf == NULL)
    {
        FXMAC_OS_XMAC_PRINT_E("tx_buf is null.");
        return FREERTOS_XMAC_PARAM_ERROR;
    }

    p = tx_buf;

    /* check if space is available to send */
    freecnt = IsTxSpaceAvailable(instance_p);

    if (freecnt <= 5)
    {
        txring = &(FXMAC_GET_TXRING(instance_p->instance));
        FXmacProcessSentBds(instance_p, txring);
    }

    if (IsTxSpaceAvailable(instance_p))
    {
        FXmacOsOutput(instance_p, p);
        ret = FT_SUCCESS;
    }
    else
    {
#if LINK_STATS
        lwip_stats.link.drop++;
#endif
        FXMAC_OS_XMAC_PRINT_E("Pack dropped, no space.");
        ret = FREERTOS_XMAC_NO_VALID_SPACE;
    }

    return ret;
}

FXmacOs *FXmacOsGetInstancePointer(FXmacOsControl *config_p)
{
    FXmacOs *instance_p;
    FASSERT(config_p != NULL);
    FASSERT(config_p->instance_id < FXMAC_NUM);
    FASSERT_MSG(config_p->interface < FXMAC_OS_INTERFACE_LENGTH, "config_p->interface %d is over %d", config_p->interface, FXMAC_OS_INTERFACE_LENGTH);
    FASSERT_MSG(config_p->autonegotiation <= 1, "config_p->autonegotiation %d is over 1", config_p->autonegotiation);
    FASSERT_MSG(config_p->phy_speed <= FXMAC_PHY_SPEED_1000M, "config_p->phy_speed %d is over 1000", config_p->phy_speed);
    FASSERT_MSG(config_p->phy_duplex <= FXMAC_PHY_FULL_DUPLEX, "config_p->phy_duplex %d is over FXMAC_PHY_FULL_DUPLEX", config_p->phy_duplex);

    instance_p = &fxmac_os_instace[config_p->instance_id];
    memcpy(&instance_p->mac_config, config_p, sizeof(FXmacOsControl));
    return instance_p;
}

void FXmacOsStart(FXmacOs *instance_p)
{
    FASSERT(instance_p != NULL);

    /* start mac */
    FXmacStart(&instance_p->instance);
}

static rt_err_t rt_xmac_init(rt_device_t dev)
{

    struct eth_device *pXmacParent;
    FXmacOs *pOsMac;

    FError ret;

    pXmacParent = rt_container_of(dev, struct eth_device, parent);
    if (NULL == pXmacParent)
    {
        return -RT_ENOMEM;
    }

    pOsMac = rt_container_of(pXmacParent, FXmacOs, parent);
    if (NULL == pOsMac)
    {
        return -RT_ENOMEM;
    }


    ret = FXmacOsInit(pOsMac);

    if (ret != FT_SUCCESS)
    {
        LOG_E("FXmacOsInit is error\r\n");
        return -RT_ERROR;
    }
    rt_kprintf("FXMAC OS Init Success!\n");


    return RT_EOK;
}

static rt_err_t rt_xmac_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("xmac open");
    return RT_EOK;
}

static rt_err_t rt_xmac_close(rt_device_t dev)
{
    LOG_D("xmac close");
    return RT_EOK;
}

static rt_ssize_t rt_xmac_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("xmac read");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_xmac_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    LOG_D("xmac write");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_xmac_control(rt_device_t dev, int cmd, void *args)
{

    FXmacOs *pOsMac;
    struct eth_device *pXmacParent;


    pXmacParent = rt_container_of(dev, struct eth_device, parent);

    if (NULL == pXmacParent)
    {
        return -RT_ENOMEM;
    }

    pOsMac = rt_container_of(pXmacParent, FXmacOs, parent);
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
            return -RT_ERROR;
        break;

    default:
        break;
    }

    return RT_EOK;
}

rt_err_t rt_xmac_tx(rt_device_t dev, struct pbuf *p)
{
    FXmacOs *pOsMac;
    struct eth_device *pXmacParent;
    rt_base_t level;
    FError  ret;

    pXmacParent = rt_container_of(dev, struct eth_device, parent);
    if (NULL == pXmacParent)
    {
        return -RT_ENOMEM;
    }

    pOsMac = rt_container_of(pXmacParent, FXmacOs, parent);
    if (NULL == pOsMac)
    {
        return -RT_ENOMEM;
    }


    level = rt_hw_interrupt_disable();
#if RT_LWIP_ETH_PAD_SIZE
    pbuf_header(p, -RT_LWIP_ETH_PAD_SIZE); /* reclaim the padding word */
#endif
    ret = FXmacOsTx(pOsMac, p);
#if RT_LWIP_ETH_PAD_SIZE
    pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif
    rt_hw_interrupt_enable(level);

    if (ret != FT_SUCCESS)
    {
        return ERR_MEM;
    }

    return RT_EOK;

}

struct pbuf *rt_xmac_rx(rt_device_t dev)
{
    FXmacOs *pOsMac;
    struct eth_device *pXmacParent;
    struct pbuf *p;
    rt_base_t level;

    pXmacParent = rt_container_of(dev, struct eth_device, parent);
    if (NULL == pXmacParent)
    {
        return RT_NULL;
    }

    pOsMac = rt_container_of(pXmacParent, FXmacOs, parent);
    if (NULL == pOsMac)
    {
        return RT_NULL;
    }

    level = rt_hw_interrupt_disable();
    FXmacRecvHandler(pOsMac);
    p = FXmacOsRx(pOsMac);
    rt_hw_interrupt_enable(level);
    return p;
}


enum lwip_port_link_status eth_link_detect(FXmacOs *instance_p)
{
    if (instance_p->instance.is_ready != FT_COMPONENT_IS_READY)
    {
        return ETH_LINK_UNDEFINED;
    }

    return  FXmacPhyReconnect(instance_p);
}


static void ethernet_link_thread(void *Args)
{
    FXmacOs *pOsMac;
    static int is_link_up = 0;
    if (RT_NULL == Args)
    {
        return;
    }

    pOsMac = (FXmacOs *)Args;

    while (1)
    {
        /* Call eth_link_detect() every 10ms to detect Ethernet link
         * change.
         */

        switch (eth_link_detect(pOsMac))
        {
        case ETH_LINK_UP:
            if (is_link_up == 0)
            {
                rt_kprintf("link up\n");
                is_link_up = 1;
                eth_device_linkchange(&pOsMac->parent, RT_TRUE);
            }
            break;
        case ETH_LINK_DOWN:
        default:
            if (is_link_up == 1)
            {
                rt_kprintf("link down\n");
                is_link_up = 0;
                eth_device_linkchange(&pOsMac->parent, RT_FALSE);
            }
            break;
        }
        rt_thread_mdelay(10);
    }
}




static int rt_hw_xmac_init(FXmacOs *pOsMac, const char *name)
{
    rt_err_t state = RT_EOK;

    pOsMac->parent.parent.init = rt_xmac_init;
    pOsMac->parent.parent.open = rt_xmac_open;
    pOsMac->parent.parent.close = rt_xmac_close;
    pOsMac->parent.parent.read = rt_xmac_read;
    pOsMac->parent.parent.write = rt_xmac_write;
    pOsMac->parent.parent.control = rt_xmac_control;
    pOsMac->parent.parent.user_data = RT_NULL;

    pOsMac->parent.eth_rx = rt_xmac_rx;
    pOsMac->parent.eth_tx = rt_xmac_tx;

    pOsMac->hwaddr[0] = 0x98;
    pOsMac->hwaddr[1] = 0x0e;
    pOsMac->hwaddr[2] = 0x24;
    pOsMac->hwaddr[3] = 0x00;
    pOsMac->hwaddr[4] = 0x11;
    pOsMac->hwaddr[5] = 0;

    /* register eth device */
    state = eth_device_init(&(pOsMac->parent), name);
    if (RT_EOK != state)
    {
        LOG_E("xmac device init faild: %d", state);
        return -RT_ERROR;
    }
    rt_kprintf("Xmac0 Initiailized!\n");


    state = rt_thread_init(&pOsMac->_link_thread,
                           "e0_link_detect",
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

    FXmacOsStart(pOsMac);

    return RT_EOK;
}
static int rt_hw_xmac_eth_init(void)
{
    rt_err_t state = RT_EOK;
    FXmacOsControl os_config;
    FXmacOs *pOsMac;


    /* os_config initialize，need to be set manually here */
    os_config.instance_id = 0;
    os_config.interface = FXMAC_OS_INTERFACE_SGMII;
    os_config.autonegotiation = 1; /* 1 is autonegotiation ,0 is manually set */
    os_config.phy_speed = FXMAC_PHY_SPEED_1000M;  /* FXMAC_PHY_SPEED_XXX */
    os_config.phy_duplex = FXMAC_PHY_FULL_DUPLEX; /* FXMAC_PHY_XXX_DUPLEX */

    pOsMac = FXmacOsGetInstancePointer(&os_config);
    if (pOsMac == NULL)
    {
        LOG_E("FXmacOsGetInstancePointer is error\r\n");
        return -RT_ERROR;
    }

    state = rt_hw_xmac_init(pOsMac, os_drv_xmac0_name);
    if (RT_EOK != state)
    {
        goto __exit;
    }


__exit:
    return state;
}
INIT_DEVICE_EXPORT(rt_hw_xmac_eth_init);

#endif


