/*
 * Copyright (C) 2010 - 2019 Xilinx, Inc.
 * Copyright (C) 2021 WangHuachen.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 */

#include "lwipopts.h"
#include "lwip/stats.h"
#include "lwip/sys.h"
#include "lwip/inet_chksum.h"

#include "netif/xadapter.h"
#include "netif/xemacpsif.h"
#include "xstatus.h"

#include "xlwipconfig.h"
#include "xparameters.h"
#include "xparameters_ps.h"
// #include "xil_exception.h"
#include "xil_mmu.h"
#if defined (ARMR5)
#include "xreg_cortexr5.h"
#endif
#ifdef CONFIG_XTRACE
#include "xtrace.h"
#endif
#ifdef OS_IS_FREERTOS
#include "FreeRTOS.h"
#include "semphr.h"
#include "timers.h"
#endif

#include <stdio.h>

#define INTC_BASE_ADDR        XPAR_SCUGIC_0_CPU_BASEADDR
#define INTC_DIST_BASE_ADDR    XPAR_SCUGIC_0_DIST_BASEADDR

/* Byte alignment of BDs */
#define BD_ALIGNMENT (XEMACPS_DMABD_MINIMUM_ALIGNMENT*2)

/* A max of 4 different ethernet interfaces are supported */
static UINTPTR tx_pbufs_storage[4*XLWIP_CONFIG_N_TX_DESC];
static UINTPTR rx_pbufs_storage[4*XLWIP_CONFIG_N_RX_DESC];

static s32_t emac_intr_num;

/******************************************************************************
 * Each BD is of 8 bytes of size and the BDs (BD chain) need to be  put
 * at uncached memory location. If they are not put at uncached
 * locations, the user needs to flush or invalidate for each BD/packet.
 * However, the flush or invalidate can happen over a cache line which can
 * span multiple BDs. This means a flush or invalidate of one BD can actually
 * flush/invalidate multiple BDs adjacent to the targeted BD.Assuming that
 * the user and hardware both update the BD fields, this operation from user
 * can potentially overwrite the updates done by hardware or user.
 * To avoid this, it is always safe to put the BD chains for Rx and tx side
 * at uncached memory location.
 *
 * The Xilinx standalone BSP for Cortex A9 implements only primary page tables.
 * Each table entry corresponds to 1 MB of address map. This means, if a memory
 * region has to be made uncached, the minimum granularity will be of 1 MB.
 *
 * The implementation below allocates a 1 MB of u8 array aligned to 1 MB.
 * This ensures that this array is put at 1 MB aligned memory (e.g. 0x1200000)
 * and accupies memory of 1 MB. The init_dma function then changes 1 MB of this
 * region to make it uncached (strongly ordered).
 * This increases the bss section of the program significantly and can be a
 * wastage of memory. The reason beings, BDs will hardly occupy few KBs of
 * memory and the rest of 1 MB of memory will be unused.
 *
 * If a program uses other peripherals that have DMAs/bus masters and need
 * uncached memory, they may also end of following the same approach. This
 * definitely aggravates the memory wastage issue. To avoid all this, the user
 * can create a new 1 MB section in the linker script and reserve it for such
 * use cases that need uncached memory location. They can then have their own
 * memory allocation logic in their application that allocates uncached memory
 * from this 1 MB location. For such a case, changes need to be done in this
 * file and appropriate uncached memory allocated through other means can be
 * used.
 *
 * The present implementation here allocates 1 MB of uncached memory. It
 * reserves of 64 KB of memory for each BD chain. 64 KB of memory means 8192 of
 * BDs for each BD chain which is more than enough for any application.
 * Assuming that both emac0 and emac1 are present, 256 KB of memory is allocated
 * for BDs. The rest 768 KB of memory is just unused.
 *********************************************************************************/

#if defined __aarch64__
u8_t bd_space[0x200000] __attribute__ ((aligned (0x200000)));
#else
u8_t bd_space[0x100000] __attribute__ ((aligned (0x100000)));
#endif
static volatile u32_t bd_space_index = 0;
static volatile u32_t bd_space_attr_set = 0;

#ifdef OS_IS_FREERTOS
long xInsideISR = 0;
#endif

#define XEMACPS_BD_TO_INDEX(ringptr, bdptr)                \
    (((UINTPTR)bdptr - (UINTPTR)(ringptr)->BaseBdAddr) / (ringptr)->Separation)


s32_t is_tx_space_available(xemacpsif_s *emac)
{
    XEmacPs_BdRing *txring;
    s32_t freecnt = 0;

    txring = &(XEmacPs_GetTxRing(&emac->emacps));

    /* tx space is available as long as there are valid BD's */
    freecnt = XEmacPs_BdRingGetFreeCnt(txring);
    return freecnt;
}


static inline
u32_t get_base_index_txpbufsstorage (xemacpsif_s *xemacpsif)
{
    u32_t index;
#ifdef XPAR_XEMACPS_0_BASEADDR
    if (xemacpsif->emacps.Config.BaseAddress == XPAR_XEMACPS_0_BASEADDR) {
        index = 0;
    }
#endif
#ifdef XPAR_XEMACPS_1_BASEADDR
    if (xemacpsif->emacps.Config.BaseAddress == XPAR_XEMACPS_1_BASEADDR) {
        index = XLWIP_CONFIG_N_TX_DESC;
    }
#endif
#ifdef XPAR_XEMACPS_2_BASEADDR
    if (xemacpsif->emacps.Config.BaseAddress == XPAR_XEMACPS_2_BASEADDR) {
        index = 2 * XLWIP_CONFIG_N_TX_DESC;
    }
#endif
#ifdef XPAR_XEMACPS_3_BASEADDR
    if (xemacpsif->emacps.Config.BaseAddress == XPAR_XEMACPS_3_BASEADDR) {
        index = 3 * XLWIP_CONFIG_N_TX_DESC;
    }
#endif
    return index;
}

static inline
u32_t get_base_index_rxpbufsstorage (xemacpsif_s *xemacpsif)
{
    u32_t index;
#ifdef XPAR_XEMACPS_0_BASEADDR
    if (xemacpsif->emacps.Config.BaseAddress == XPAR_XEMACPS_0_BASEADDR) {
        index = 0;
    }
#endif
#ifdef XPAR_XEMACPS_1_BASEADDR
    if (xemacpsif->emacps.Config.BaseAddress == XPAR_XEMACPS_1_BASEADDR) {
        index = XLWIP_CONFIG_N_RX_DESC;
    }
#endif
#ifdef XPAR_XEMACPS_2_BASEADDR
    if (xemacpsif->emacps.Config.BaseAddress == XPAR_XEMACPS_2_BASEADDR) {
        index = 2 * XLWIP_CONFIG_N_RX_DESC;
    }
#endif
#ifdef XPAR_XEMACPS_3_BASEADDR
    if (xemacpsif->emacps.Config.BaseAddress == XPAR_XEMACPS_3_BASEADDR) {
        index = 3 * XLWIP_CONFIG_N_RX_DESC;
    }
#endif
    return index;
}

void process_sent_bds(xemacpsif_s *xemacpsif, XEmacPs_BdRing *txring)
{
    XEmacPs_Bd *txbdset;
    XEmacPs_Bd *curbdpntr;
    s32_t n_bds;
    XStatus status;
    s32_t n_pbufs_freed = 0;
    u32_t bdindex;
    struct pbuf *p;
    u32 *temp;
    u32_t index;

    index = get_base_index_txpbufsstorage (xemacpsif);

    while (1) {
        /* obtain processed BD's */
        n_bds = XEmacPs_BdRingFromHwTx(txring,
                                XLWIP_CONFIG_N_TX_DESC, &txbdset);
        if (n_bds == 0)  {
            return;
        }
        /* free the processed BD's */
        n_pbufs_freed = n_bds;
        curbdpntr = txbdset;
        while (n_pbufs_freed > 0) {
            bdindex = XEMACPS_BD_TO_INDEX(txring, curbdpntr);
            temp = (u32 *)curbdpntr;
            *temp = 0;
            temp++;
            if (bdindex == (XLWIP_CONFIG_N_TX_DESC - 1)) {
                *temp = 0xC0000000;
            } else {
                *temp = 0x80000000;
            }
            dsb();
            p = (struct pbuf *)tx_pbufs_storage[index + bdindex];
            if (p != NULL) {
                pbuf_free(p);
            }
            tx_pbufs_storage[index + bdindex] = 0;
            curbdpntr = XEmacPs_BdRingNext(txring, curbdpntr);
            n_pbufs_freed--;
            dsb();
        }

        status = XEmacPs_BdRingFree(txring, n_bds, txbdset);
        if (status != XST_SUCCESS) {
            LWIP_DEBUGF(NETIF_DEBUG, ("Failure while freeing in Tx Done ISR\r\n"));
        }
    }
    return;
}

void emacps_send_handler(void *arg)
{
    struct xemac_s *xemac;
    xemacpsif_s   *xemacpsif;
    XEmacPs_BdRing *txringptr;
    u32_t regval;
#ifdef OS_IS_FREERTOS
    xInsideISR++;
#endif
    xemac = (struct xemac_s *)(arg);
    xemacpsif = (xemacpsif_s *)(xemac->state);
    txringptr = &(XEmacPs_GetTxRing(&xemacpsif->emacps));
    regval = XEmacPs_ReadReg(xemacpsif->emacps.Config.BaseAddress, XEMACPS_TXSR_OFFSET);
    XEmacPs_WriteReg(xemacpsif->emacps.Config.BaseAddress,XEMACPS_TXSR_OFFSET, regval);

    /* If Transmit done interrupt is asserted, process completed BD's */
    /* Since RT-Thread does not support freeing memory in interrupts, comment it out */
    // process_sent_bds(xemacpsif, txringptr);
#ifdef OS_IS_FREERTOS
    xInsideISR--;
#endif
}

XStatus emacps_sgsend(xemacpsif_s *xemacpsif, struct pbuf *p)
{
    struct pbuf *q;
    s32_t n_pbufs;
    XEmacPs_Bd *txbdset, *txbd, *last_txbd = NULL;
    XEmacPs_Bd *temp_txbd;
    XStatus status;
    XEmacPs_BdRing *txring;
    u32_t bdindex;
    u32_t lev;
    u32_t index;
    u32_t max_fr_size;

    lev = mfcpsr();
    mtcpsr(lev | 0x000000C0);

    txring = &(XEmacPs_GetTxRing(&xemacpsif->emacps));

    index = get_base_index_txpbufsstorage (xemacpsif);

    /* first count the number of pbufs */
    for (q = p, n_pbufs = 0; q != NULL; q = q->next)
        n_pbufs++;

    /* obtain as many BD's */
    status = XEmacPs_BdRingAlloc(txring, n_pbufs, &txbdset);
    if (status != XST_SUCCESS) {
        mtcpsr(lev);
        LWIP_DEBUGF(NETIF_DEBUG, ("sgsend: Error allocating TxBD\r\n"));
        return XST_FAILURE;
    }

    for(q = p, txbd = txbdset; q != NULL; q = q->next) {
        bdindex = XEMACPS_BD_TO_INDEX(txring, txbd);
        if (tx_pbufs_storage[index + bdindex] != 0) {
            mtcpsr(lev);
            LWIP_DEBUGF(NETIF_DEBUG, ("PBUFS not available\r\n"));
            return XST_FAILURE;
        }

        /* Send the data from the pbuf to the interface, one pbuf at a
           time. The size of the data in each pbuf is kept in the ->len
           variable. */
        if (xemacpsif->emacps.Config.IsCacheCoherent == 0) {
            Xil_DCacheFlushRange((UINTPTR)q->payload, (UINTPTR)q->len);
        }

        XEmacPs_BdSetAddressTx(txbd, (UINTPTR)q->payload);

#ifdef ZYNQMP_USE_JUMBO
        max_fr_size = MAX_FRAME_SIZE_JUMBO - 18;
#else
        max_fr_size = XEMACPS_MAX_FRAME_SIZE - 18;
#endif
        if (q->len > max_fr_size)
            XEmacPs_BdSetLength(txbd, max_fr_size & 0x3FFF);
        else
            XEmacPs_BdSetLength(txbd, q->len & 0x3FFF);

        tx_pbufs_storage[index + bdindex] = (UINTPTR)q;

        pbuf_ref(q);
        last_txbd = txbd;
        XEmacPs_BdClearLast(txbd);
        txbd = XEmacPs_BdRingNext(txring, txbd);
    }
    XEmacPs_BdSetLast(last_txbd);
    /* For fragmented packets, remember the 1st BD allocated for the 1st
       packet fragment. The used bit for this BD should be cleared at the end
       after clearing out used bits for other fragments. For packets without
       just remember the allocated BD. */
    temp_txbd = txbdset;
    txbd = txbdset;
    txbd = XEmacPs_BdRingNext(txring, txbd);
    q = p->next;
    for(; q != NULL; q = q->next) {
        XEmacPs_BdClearTxUsed(txbd);
        dsb();
        txbd = XEmacPs_BdRingNext(txring, txbd);
    }
    XEmacPs_BdClearTxUsed(temp_txbd);
    dsb();

    status = XEmacPs_BdRingToHw(txring, n_pbufs, txbdset);
    if (status != XST_SUCCESS) {
        mtcpsr(lev);
        LWIP_DEBUGF(NETIF_DEBUG, ("sgsend: Error submitting TxBD\r\n"));
        return XST_FAILURE;
    }
    /* Start transmit */
    XEmacPs_WriteReg((xemacpsif->emacps).Config.BaseAddress,
    XEMACPS_NWCTRL_OFFSET,
    (XEmacPs_ReadReg((xemacpsif->emacps).Config.BaseAddress,
    XEMACPS_NWCTRL_OFFSET) | XEMACPS_NWCTRL_STARTTX_MASK));

    mtcpsr(lev);
    return status;
}

void setup_rx_bds(xemacpsif_s *xemacpsif, XEmacPs_BdRing *rxring)
{
    XEmacPs_Bd *rxbd;
    XStatus status;
    struct pbuf *p;
    u32_t freebds;
    u32_t bdindex;
    u32 *temp;
    u32_t index;

    index = get_base_index_rxpbufsstorage (xemacpsif);

    freebds = XEmacPs_BdRingGetFreeCnt (rxring);
    while (freebds > 0) {
        freebds--;
#ifdef ZYNQMP_USE_JUMBO
        p = pbuf_alloc(PBUF_RAW, MAX_FRAME_SIZE_JUMBO, PBUF_POOL);
#else
        p = pbuf_alloc(PBUF_RAW, XEMACPS_MAX_FRAME_SIZE, PBUF_POOL);
#endif
        if (!p) {
#if LINK_STATS
            lwip_stats.link.memerr++;
            lwip_stats.link.drop++;
#endif
            rt_kprintf("unable to alloc pbuf in recv_handler\r\n");
            return;
        }
        status = XEmacPs_BdRingAlloc(rxring, 1, &rxbd);
        if (status != XST_SUCCESS) {
            LWIP_DEBUGF(NETIF_DEBUG, ("setup_rx_bds: Error allocating RxBD\r\n"));
            pbuf_free(p);
            return;
        }
        status = XEmacPs_BdRingToHw(rxring, 1, rxbd);
        if (status != XST_SUCCESS) {
            LWIP_DEBUGF(NETIF_DEBUG, ("Error committing RxBD to hardware: "));
            if (status == XST_DMA_SG_LIST_ERROR) {
                LWIP_DEBUGF(NETIF_DEBUG, ("XST_DMA_SG_LIST_ERROR: this function was called out of sequence with XEmacPs_BdRingAlloc()\r\n"));
            }
            else {
                LWIP_DEBUGF(NETIF_DEBUG, ("set of BDs was rejected because the first BD did not have its start-of-packet bit set, or the last BD did not have its end-of-packet bit set, or any one of the BD set has 0 as length value\r\n"));
            }

            pbuf_free(p);
            XEmacPs_BdRingUnAlloc(rxring, 1, rxbd);
            return;
        }
#ifdef ZYNQMP_USE_JUMBO
        if (xemacpsif->emacps.Config.IsCacheCoherent == 0) {
            Xil_DCacheInvalidateRange((UINTPTR)p->payload, (UINTPTR)MAX_FRAME_SIZE_JUMBO);
        }
#else
        if (xemacpsif->emacps.Config.IsCacheCoherent == 0) {
            Xil_DCacheInvalidateRange((UINTPTR)p->payload, (UINTPTR)XEMACPS_MAX_FRAME_SIZE);
        }
#endif
        bdindex = XEMACPS_BD_TO_INDEX(rxring, rxbd);
        temp = (u32 *)rxbd;
        if (bdindex == (XLWIP_CONFIG_N_RX_DESC - 1)) {
            *temp = 0x00000002;
        } else {
            *temp = 0;
        }
        temp++;
        *temp = 0;
        dsb();

        XEmacPs_BdSetAddressRx(rxbd, (UINTPTR)p->payload);
        rx_pbufs_storage[index + bdindex] = (UINTPTR)p;
    }
}

void emacps_recv_handler(void *arg)
{
    struct pbuf *p;
    XEmacPs_Bd *rxbdset, *curbdptr;
    struct xemac_s *xemac;
    xemacpsif_s *xemacpsif;
    XEmacPs_BdRing *rxring;
    volatile s32_t bd_processed;
    s32_t rx_bytes, k;
    u32_t bdindex;
    u32_t regval;
    u32_t index;
    u32_t gigeversion;

    xemac = (struct xemac_s *)(arg);
    xemacpsif = (xemacpsif_s *)(xemac->state);
    rxring = &XEmacPs_GetRxRing(&xemacpsif->emacps);

#ifdef OS_IS_FREERTOS
    xInsideISR++;
#endif

    gigeversion = ((Xil_In32(xemacpsif->emacps.Config.BaseAddress + 0xFC)) >> 16) & 0xFFF;
    index = get_base_index_rxpbufsstorage (xemacpsif);
    /*
     * If Reception done interrupt is asserted, call RX call back function
     * to handle the processed BDs and then raise the according flag.
     */
    regval = XEmacPs_ReadReg(xemacpsif->emacps.Config.BaseAddress, XEMACPS_RXSR_OFFSET);
    XEmacPs_WriteReg(xemacpsif->emacps.Config.BaseAddress, XEMACPS_RXSR_OFFSET, regval);
    if (gigeversion <= 2) {
            resetrx_on_no_rxdata(xemacpsif);
    }

    while(1) {

        bd_processed = XEmacPs_BdRingFromHwRx(rxring, XLWIP_CONFIG_N_RX_DESC, &rxbdset);
        if (bd_processed <= 0) {
            break;
        }
        for (k = 0, curbdptr=rxbdset; k < bd_processed; k++) {

            bdindex = XEMACPS_BD_TO_INDEX(rxring, curbdptr);
            p = (struct pbuf *)rx_pbufs_storage[index + bdindex];
            /*
             * Adjust the buffer size to the actual number of bytes received.
             */
#ifdef ZYNQMP_USE_JUMBO
            rx_bytes = XEmacPs_GetRxFrameSize(&xemacpsif->emacps, curbdptr);
#else
            rx_bytes = XEmacPs_BdGetLength(curbdptr);
#endif
            pbuf_realloc(p, rx_bytes);
            /* Invalidate RX frame before queuing to handle
             * L1 cache prefetch conditions on any architecture.
             */
            Xil_DCacheInvalidateRange((UINTPTR)p->payload, rx_bytes);
            /* store it in the receive queue,
             * where it'll be processed by a different handler
             */
            if (pq_enqueue(xemacpsif->recv_q, (void*)p) < 0) {
#if LINK_STATS
                lwip_stats.link.memerr++;
                lwip_stats.link.drop++;
#endif
                pbuf_free(p);
            }
            curbdptr = XEmacPs_BdRingNext( rxring, curbdptr);
        }
        /* free up the BD's */
        XEmacPs_BdRingFree(rxring, bd_processed, rxbdset);
        setup_rx_bds(xemacpsif, rxring);
        eth_device_ready(xemac->rt_eth_device);
    }

#ifdef OS_IS_FREERTOS
    xInsideISR--;
#endif
    return;
}

void clean_dma_txdescs(struct xemac_s *xemac)
{
    XEmacPs_Bd bdtemplate;
    XEmacPs_BdRing *txringptr;
    xemacpsif_s *xemacpsif = (xemacpsif_s *)(xemac->state);

    txringptr = &XEmacPs_GetTxRing(&xemacpsif->emacps);

    XEmacPs_BdClear(&bdtemplate);
    XEmacPs_BdSetStatus(&bdtemplate, XEMACPS_TXBUF_USED_MASK);

    /*
     * Create the TxBD ring
     */
    XEmacPs_BdRingCreate(txringptr, (UINTPTR) xemacpsif->tx_bdspace,
            (UINTPTR) xemacpsif->tx_bdspace, BD_ALIGNMENT,
                 XLWIP_CONFIG_N_TX_DESC);
    XEmacPs_BdRingClone(txringptr, &bdtemplate, XEMACPS_SEND);
}

XStatus init_dma(struct xemac_s *xemac)
{
    XEmacPs_Bd bdtemplate;
    XEmacPs_BdRing *rxringptr, *txringptr;
    XEmacPs_Bd *rxbd;
    struct pbuf *p;
    XStatus status;
    s32_t i;
    u32_t bdindex;
    volatile UINTPTR tempaddress;
    u32_t index;
    u32_t gigeversion;
    XEmacPs_Bd *bdtxterminate;
    XEmacPs_Bd *bdrxterminate;
    u32 *temp;

    xemacpsif_s *xemacpsif = (xemacpsif_s *)(xemac->state);
    struct xtopology_t *xtopologyp = &xtopology[xemac->topology_index];

    index = get_base_index_rxpbufsstorage (xemacpsif);
    gigeversion = ((Xil_In32(xemacpsif->emacps.Config.BaseAddress + 0xFC)) >> 16) & 0xFFF;
    /*
     * The BDs need to be allocated in uncached memory. Hence the 1 MB
     * address range allocated for Bd_Space is made uncached
     * by setting appropriate attributes in the translation table.
     * The Bd_Space is aligned to 1MB and has a size of 1 MB. This ensures
     * a reserved uncached area used only for BDs.
     */
    if (bd_space_attr_set == 0) {
#if defined (ARMR5)
    Xil_SetTlbAttributes((s32_t)bd_space, STRONG_ORDERD_SHARED | PRIV_RW_USER_RW); // addr, attr
#else
#if defined __aarch64__
    Xil_SetTlbAttributes((u64)bd_space, NORM_NONCACHE | INNER_SHAREABLE);
#else
    Xil_SetTlbAttributes((s32_t)bd_space, DEVICE_MEMORY); // addr, attr
#endif
#endif
        bd_space_attr_set = 1;
    }

    rxringptr = &XEmacPs_GetRxRing(&xemacpsif->emacps);
    txringptr = &XEmacPs_GetTxRing(&xemacpsif->emacps);
    LWIP_DEBUGF(NETIF_DEBUG, ("rxringptr: 0x%08x\r\n", rxringptr));
    LWIP_DEBUGF(NETIF_DEBUG, ("txringptr: 0x%08x\r\n", txringptr));

    /* Allocate 64k for Rx and Tx bds each to take care of extreme cases */
    tempaddress = (UINTPTR)&(bd_space[bd_space_index]);
    xemacpsif->rx_bdspace = (void *)tempaddress;
    bd_space_index += 0x10000;
    tempaddress = (UINTPTR)&(bd_space[bd_space_index]);
    xemacpsif->tx_bdspace = (void *)tempaddress;
    bd_space_index += 0x10000;
    if (gigeversion > 2) {
        tempaddress = (UINTPTR)&(bd_space[bd_space_index]);
        bdrxterminate = (XEmacPs_Bd *)tempaddress;
        bd_space_index += 0x10000;
        tempaddress = (UINTPTR)&(bd_space[bd_space_index]);
        bdtxterminate = (XEmacPs_Bd *)tempaddress;
        bd_space_index += 0x10000;
    }

    LWIP_DEBUGF(NETIF_DEBUG, ("rx_bdspace: %p \r\n", xemacpsif->rx_bdspace));
    LWIP_DEBUGF(NETIF_DEBUG, ("tx_bdspace: %p \r\n", xemacpsif->tx_bdspace));

    if (!xemacpsif->rx_bdspace || !xemacpsif->tx_bdspace) {
        xil_printf("%s@%d: Error: Unable to allocate memory for TX/RX buffer descriptors",
                __FILE__, __LINE__);
        return ERR_IF;
    }

    /*
     * Setup RxBD space.
     *
     * Setup a BD template for the Rx channel. This template will be copied to
     * every RxBD. We will not have to explicitly set these again.
     */
    XEmacPs_BdClear(&bdtemplate);

    /*
     * Create the RxBD ring
     */

    status = XEmacPs_BdRingCreate(rxringptr, (UINTPTR) xemacpsif->rx_bdspace,
                (UINTPTR) xemacpsif->rx_bdspace, BD_ALIGNMENT,
                     XLWIP_CONFIG_N_RX_DESC);

    if (status != XST_SUCCESS) {
        LWIP_DEBUGF(NETIF_DEBUG, ("Error setting up RxBD space\r\n"));
        return ERR_IF;
    }

    status = XEmacPs_BdRingClone(rxringptr, &bdtemplate, XEMACPS_RECV);
    if (status != XST_SUCCESS) {
        LWIP_DEBUGF(NETIF_DEBUG, ("Error initializing RxBD space\r\n"));
        return ERR_IF;
    }

    XEmacPs_BdClear(&bdtemplate);
    XEmacPs_BdSetStatus(&bdtemplate, XEMACPS_TXBUF_USED_MASK);
    /*
     * Create the TxBD ring
     */
    status = XEmacPs_BdRingCreate(txringptr, (UINTPTR) xemacpsif->tx_bdspace,
                (UINTPTR) xemacpsif->tx_bdspace, BD_ALIGNMENT,
                     XLWIP_CONFIG_N_TX_DESC);

    if (status != XST_SUCCESS) {
        return ERR_IF;
    }

    /* We reuse the bd template, as the same one will work for both rx and tx. */
    status = XEmacPs_BdRingClone(txringptr, &bdtemplate, XEMACPS_SEND);
    if (status != XST_SUCCESS) {
        return ERR_IF;
    }

    /*
     * Allocate RX descriptors, 1 RxBD at a time.
     */
    for (i = 0; i < XLWIP_CONFIG_N_RX_DESC; i++) {
#ifdef ZYNQMP_USE_JUMBO
        p = pbuf_alloc(PBUF_RAW, MAX_FRAME_SIZE_JUMBO, PBUF_POOL);
#else
        p = pbuf_alloc(PBUF_RAW, XEMACPS_MAX_FRAME_SIZE, PBUF_POOL);
#endif
        if (!p) {
#if LINK_STATS
            lwip_stats.link.memerr++;
            lwip_stats.link.drop++;
#endif
            rt_kprintf("unable to alloc pbuf in init_dma\r\n");
            return ERR_IF;
        }
        status = XEmacPs_BdRingAlloc(rxringptr, 1, &rxbd);
        if (status != XST_SUCCESS) {
            LWIP_DEBUGF(NETIF_DEBUG, ("init_dma: Error allocating RxBD\r\n"));
            pbuf_free(p);
            return ERR_IF;
        }
        /* Enqueue to HW */
        status = XEmacPs_BdRingToHw(rxringptr, 1, rxbd);
        if (status != XST_SUCCESS) {
            LWIP_DEBUGF(NETIF_DEBUG, ("Error: committing RxBD to HW\r\n"));
            pbuf_free(p);
            XEmacPs_BdRingUnAlloc(rxringptr, 1, rxbd);
            return ERR_IF;
        }

        bdindex = XEMACPS_BD_TO_INDEX(rxringptr, rxbd);
        temp = (u32 *)rxbd;
        *temp = 0;
        if (bdindex == (XLWIP_CONFIG_N_RX_DESC - 1)) {
            *temp = 0x00000002;
        }
        temp++;
        *temp = 0;
        dsb();
#ifdef ZYNQMP_USE_JUMBO
        if (xemacpsif->emacps.Config.IsCacheCoherent == 0) {
            Xil_DCacheInvalidateRange((UINTPTR)p->payload, (UINTPTR)MAX_FRAME_SIZE_JUMBO);
        }
#else
        if (xemacpsif->emacps.Config.IsCacheCoherent == 0) {
            Xil_DCacheInvalidateRange((UINTPTR)p->payload, (UINTPTR)XEMACPS_MAX_FRAME_SIZE);
        }
#endif
        XEmacPs_BdSetAddressRx(rxbd, (UINTPTR)p->payload);

        rx_pbufs_storage[index + bdindex] = (UINTPTR)p;
    }
    XEmacPs_SetQueuePtr(&(xemacpsif->emacps), xemacpsif->emacps.RxBdRing.BaseBdAddr, 0, XEMACPS_RECV);
    if (gigeversion > 2) {
        XEmacPs_SetQueuePtr(&(xemacpsif->emacps), xemacpsif->emacps.TxBdRing.BaseBdAddr, 1, XEMACPS_SEND);
    }else {
        XEmacPs_SetQueuePtr(&(xemacpsif->emacps), xemacpsif->emacps.TxBdRing.BaseBdAddr, 0, XEMACPS_SEND);
    }
    if (gigeversion > 2)
    {
        /*
         * This version of GEM supports priority queuing and the current
         * driver is using tx priority queue 1 and normal rx queue for
         * packet transmit and receive. The below code ensure that the
         * other queue pointers are parked to known state for avoiding
         * the controller to malfunction by fetching the descriptors
         * from these queues.
         */
        XEmacPs_BdClear(bdrxterminate);
        XEmacPs_BdSetAddressRx(bdrxterminate, (XEMACPS_RXBUF_NEW_MASK |
                        XEMACPS_RXBUF_WRAP_MASK));
        XEmacPs_Out32((xemacpsif->emacps.Config.BaseAddress + XEMACPS_RXQ1BASE_OFFSET),
                   (UINTPTR)bdrxterminate);
        XEmacPs_BdClear(bdtxterminate);
        XEmacPs_BdSetStatus(bdtxterminate, (XEMACPS_TXBUF_USED_MASK |
                        XEMACPS_TXBUF_WRAP_MASK));
        XEmacPs_Out32((xemacpsif->emacps.Config.BaseAddress + XEMACPS_TXQBASE_OFFSET),
                   (UINTPTR)bdtxterminate);
    }

    /*
     * Connect the device driver handler that will be called when an
     * interrupt for the device occurs, the handler defined above performs
     * the specific interrupt processing for the device.
     */
    // XScuGic_RegisterHandler(INTC_BASE_ADDR, xtopologyp->scugic_emac_intr,
    //             (Xil_ExceptionHandler)XEmacPs_IntrHandler,
    //                     (void *)&xemacpsif->emacps);
    /*
     * Enable the interrupt for emacps.
     */
    // XScuGic_EnableIntr(INTC_DIST_BASE_ADDR, (u32) xtopologyp->scugic_emac_intr);
    emac_intr_num = (u32) xtopologyp->scugic_emac_intr;
    return 0;
}

/*
 * resetrx_on_no_rxdata():
 *
 * It is called at regular intervals through the API xemacpsif_resetrx_on_no_rxdata
 * called by the user.
 * The EmacPs has a HW bug (SI# 692601) on the Rx path for heavy Rx traffic.
 * Under heavy Rx traffic because of the HW bug there are times when the Rx path
 * becomes unresponsive. The workaround for it is to check for the Rx path for
 * traffic (by reading the stats registers regularly). If the stats register
 * does not increment for sometime (proving no Rx traffic), the function resets
 * the Rx data path.
 *
 */

void resetrx_on_no_rxdata(xemacpsif_s *xemacpsif)
{
    u32_t regctrl;
    u32_t tempcntr;
    u32_t gigeversion;

    gigeversion = ((Xil_In32(xemacpsif->emacps.Config.BaseAddress + 0xFC)) >> 16) & 0xFFF;
    if (gigeversion == 2) {
        tempcntr = XEmacPs_ReadReg(xemacpsif->emacps.Config.BaseAddress, XEMACPS_RXCNT_OFFSET);
        if ((!tempcntr) && (!(xemacpsif->last_rx_frms_cntr))) {
            regctrl = XEmacPs_ReadReg(xemacpsif->emacps.Config.BaseAddress,
                    XEMACPS_NWCTRL_OFFSET);
            regctrl &= (~XEMACPS_NWCTRL_RXEN_MASK);
            XEmacPs_WriteReg(xemacpsif->emacps.Config.BaseAddress,
                    XEMACPS_NWCTRL_OFFSET, regctrl);
            regctrl = XEmacPs_ReadReg(xemacpsif->emacps.Config.BaseAddress, XEMACPS_NWCTRL_OFFSET);
            regctrl |= (XEMACPS_NWCTRL_RXEN_MASK);
            XEmacPs_WriteReg(xemacpsif->emacps.Config.BaseAddress, XEMACPS_NWCTRL_OFFSET, regctrl);
        }
        xemacpsif->last_rx_frms_cntr = tempcntr;
    }
}

void free_txrx_pbufs(xemacpsif_s *xemacpsif)
{
    s32_t index;
    s32_t index1;
    struct pbuf *p;

    index1 = get_base_index_txpbufsstorage (xemacpsif);

    for (index = index1; index < (index1 + XLWIP_CONFIG_N_TX_DESC); index++) {
        if (tx_pbufs_storage[index] != 0) {
            p = (struct pbuf *)tx_pbufs_storage[index];
            pbuf_free(p);
            tx_pbufs_storage[index] = 0;
        }
    }

    for (index = index1; index < (index1 + XLWIP_CONFIG_N_TX_DESC); index++) {
        p = (struct pbuf *)rx_pbufs_storage[index];
        pbuf_free(p);

    }
}

void free_onlytx_pbufs(xemacpsif_s *xemacpsif)
{
    s32_t index;
    s32_t index1;
    struct pbuf *p;

    index1 = get_base_index_txpbufsstorage (xemacpsif);
    for (index = index1; index < (index1 + XLWIP_CONFIG_N_TX_DESC); index++) {
        if (tx_pbufs_storage[index] != 0) {
            p = (struct pbuf *)tx_pbufs_storage[index];
            pbuf_free(p);
            tx_pbufs_storage[index] = 0;
        }
    }
}

/* reset Tx and Rx DMA pointers after XEmacPs_Stop */
void reset_dma(struct xemac_s *xemac)
{
    u8 txqueuenum;
    u32_t gigeversion;
    xemacpsif_s *xemacpsif = (xemacpsif_s *)(xemac->state);
    XEmacPs_BdRing *txringptr = &XEmacPs_GetTxRing(&xemacpsif->emacps);
    XEmacPs_BdRing *rxringptr = &XEmacPs_GetRxRing(&xemacpsif->emacps);

    XEmacPs_BdRingPtrReset(txringptr, xemacpsif->tx_bdspace);
    XEmacPs_BdRingPtrReset(rxringptr, xemacpsif->rx_bdspace);

    gigeversion = ((Xil_In32(xemacpsif->emacps.Config.BaseAddress + 0xFC)) >> 16) & 0xFFF;
    if (gigeversion > 2) {
        txqueuenum = 1;
    } else {
        txqueuenum = 0;
    }

    XEmacPs_SetQueuePtr(&(xemacpsif->emacps), xemacpsif->emacps.RxBdRing.BaseBdAddr, 0, XEMACPS_RECV);
    XEmacPs_SetQueuePtr(&(xemacpsif->emacps), xemacpsif->emacps.TxBdRing.BaseBdAddr, txqueuenum, XEMACPS_SEND);
}

void emac_disable_intr(void)
{
    // XScuGic_DisableIntr(INTC_DIST_BASE_ADDR, emac_intr_num);
    rt_hw_interrupt_mask(emac_intr_num);
}

void emac_enable_intr(void)
{
    // XScuGic_EnableIntr(INTC_DIST_BASE_ADDR, emac_intr_num);
    rt_hw_interrupt_umask(emac_intr_num);
}
