 /**********************************************************************
 * Copyright (C) 2014-2015 Cadence Design Systems, Inc.- http://www.cadence.com
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************
 * edd.c
 * Ethernet DMA MAC Driver,
 * for GEM GXL core part no. IP7014, from rev 1p05 up
 * for GEM XL  core part no. IP7012, from rev 1p01 up
 * and XGM GXL core part no. IP716,  from rev 1p01 up
 *
 * Main source file
 *****************************************************************************/

/****************************************************************************
* Modification by Infineon: To make this file compile with ModusToolbox
* toolchain
*****************************************************************************/

#include "cy_device.h"
#include "cy_syslib.h"

#if defined(CY_IP_MXETH)

#include "cdn_stdint.h"
#include "cdn_errno.h"
#include "log.h"
#include "cps_v2.h"
#include "emac_regs.h"
#include "cedi.h"
#include "edd_int.h"

#ifdef __cplusplus
    extern "C" {
#endif

#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
__STATIC_FORCEINLINE void SCB_InvalidateDCache_by_Addr (volatile void *addr, int32_t dsize);
__STATIC_FORCEINLINE void SCB_CleanDCache_by_Addr (volatile void *addr, int32_t dsize);
#endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
/******************************************************************************
 * Private Driver functions
 *****************************************************************************/

uint32_t CPS_UncachedRead32(volatile uint32_t* address) {
    /** Invalidate cache **/
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    SCB_InvalidateDCache_by_Addr(address, (int32_t)4);
#endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
    return (*((volatile uint32_t *)(address)));
}

void CPS_UncachedWrite32(volatile uint32_t* address, uint32_t value) {
    (*((volatile uint32_t *)(address)) = (value));
    /** Clean cache **/
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    SCB_CleanDCache_by_Addr(address, (int32_t)4);
#endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
    return;
}

void CPS_WritePhysAddress32(volatile uint32_t* address, uint32_t value) {
    (*((volatile uint32_t *)(address)) = (value));
    return;
}
/* Calculate the descriptor sizes (in bytes) for a given DMA config */
static void calcDescriptorSizes(const CEDI_Config *config,
                                uint16_t *txDescSize,
                                uint16_t *rxDescSize) {

    /* use 1 contiguous block for Tx descriptor lists
     * and another contiguous block for Rx descriptor lists */
    *txDescSize = CEDI_TWO_BD_WORD_SIZE;
    *rxDescSize = CEDI_TWO_BD_WORD_SIZE;

    if (config->dmaAddrBusWidth)  // DMA address bus width. 0 =32b , 1=64b
    {
         *txDescSize += CEDI_TWO_BD_WORD_SIZE;
         *rxDescSize += CEDI_TWO_BD_WORD_SIZE;
    }

    if (config->enTxExtBD){
        *txDescSize += CEDI_TWO_BD_WORD_SIZE;
    }

    if (config->enRxExtBD){
        *rxDescSize += CEDI_TWO_BD_WORD_SIZE;
    }
}

static uint32_t numTxDescriptors(CEDI_Config *config)
{
    uint16_t i;
    uint16_t sumTxDesc = 0;

    for (i=0; i<config->txQs; i++)
        /* allow 1 extra for "endstop" descriptor */
        sumTxDesc += ((uint32_t)((config->txQLen)[i]+CEDI_MIN_TXBD));
    return sumTxDesc;
}

static uint32_t numRxDescriptors(CEDI_Config *config)
{
    uint16_t i;
    uint16_t sumRxDesc = 0;

    for (i=0; i<config->rxQs; i++)
        /* allow 1 extra for "endstop" descriptor */
        sumRxDesc += ((uint32_t)((config->rxQLen)[i]+CEDI_MIN_RXBD));
    return sumRxDesc;
}

static uint32_t initTxDescLists(void *pD)
{
    uint8_t q;

    /* set start of Tx vAddr lists - place in pD block after
     * privateData struct */
    CEDI_PdVar(txQueue[0]).vAddrList =
                            (uintptr_t *)((uint8_t *)pD + sizeof(CEDI_PrivateData));
    for (q=0; q<CEDI_PdVar(cfg).txQs; q++)
        if (0!=emacResetTxQ(pD, q))
            return EINVAL;

    return 0;
}

/* Initialise Rx descriptor lists - also in pD block, after the Tx ones */
uint32_t initRxDescLists(void *pD)
{
    uint8_t q;
    uint32_t pAddr, i;
    uintptr_t vAddr;
    rxQueue_t *rxQ;
    rxDesc* descPtr;

    /* set start of Rx vAddr lists after Tx lists */
    CEDI_PdVar(rxQueue[0]).rxBufVAddr =
                (uintptr_t *)((uint8_t *)pD + sizeof(CEDI_PrivateData) +
                  sizeof(uintptr_t)*(numTxDescriptors(&CEDI_PdVar(cfg))));

    for (q=0; q<CEDI_PdVar(cfg).rxQs; q++) {

        rxQ = &(CEDI_PdVar(rxQueue[q]));
        rxQ->numRxDesc = CEDI_PdVar(cfg).rxQLen[q] + CEDI_MIN_RXBD;

        emacFindQBaseAddr(pD, q, rxQ, &pAddr, &vAddr);
        rxQ->rxDescStart = (rxDesc *)vAddr;

        /* initialise the descriptors */
        descPtr = rxQ->rxDescStart;
        for (i = 0; i<rxQ->numRxDesc; i++) {
            CPS_UncachedWrite32((uint32_t *)
                    &(descPtr->word[0]), i?0:CEDI_RXD_WRAP|CEDI_RXD_USED);
            CPS_UncachedWrite32((uint32_t *)
                    &(descPtr->word[1]), CEDI_RXD_EMPTY);
            descPtr = (rxDesc*) (((uintptr_t)(descPtr)) +
                    (CEDI_PdVar(rxDescriptorSize)));
        }

        if (0!=emacResetRxQ(pD, q, 0))
          return EINVAL;
    }

    return 0;
}


/* return the number of priority queues available in the h/w config */
static uint8_t maxHwQs(uintptr_t regBase) {
    uint8_t qCount = 1;
    uint32_t reg = CPS_UncachedRead32(
            (&(((struct emac_regs *)(regBase))->designcfg_debug6)));
    if (EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE1__READ(reg)) qCount++;
    if (EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE2__READ(reg)) qCount++;
    if (EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE3__READ(reg)) qCount++;
    if (EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE4__READ(reg)) qCount++;
    if (EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE5__READ(reg)) qCount++;
    if (EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE6__READ(reg)) qCount++;
    if (EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE7__READ(reg)) qCount++;
    if (EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE8__READ(reg)) qCount++;
    if (EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE9__READ(reg)) qCount++;
    if (EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE10__READ(reg)) qCount++;
    if (EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE11__READ(reg)) qCount++;
    if (EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE12__READ(reg)) qCount++;
    if (EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE13__READ(reg)) qCount++;
    if (EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE14__READ(reg)) qCount++;
    if (EMAC_REGS__DESIGNCFG_DEBUG6__DMA_PRIORITY_QUEUE15__READ(reg)) qCount++;
    return qCount;
}

static void disableAllInterrupts(void *pD)
{
#define CEDI_DISABLE_ALL_INT(Q)  if (CEDI_PdVar(numQs)>Q) \
        CPS_UncachedWrite32(CEDI_RegAddr(int_q##Q##_disable), 0xFFFFFFFF);

    CPS_UncachedWrite32(CEDI_RegAddr(int_disable), 0xFFFFFFFF);

    CEDI_DISABLE_ALL_INT(1);
    CEDI_DISABLE_ALL_INT(2);
/*  // Only Three Queues are supported
    CEDI_DISABLE_ALL_INT(3);
    CEDI_DISABLE_ALL_INT(4);
    CEDI_DISABLE_ALL_INT(5);
    CEDI_DISABLE_ALL_INT(6);
    CEDI_DISABLE_ALL_INT(7);
    CEDI_DISABLE_ALL_INT(8);
    CEDI_DISABLE_ALL_INT(9);
    CEDI_DISABLE_ALL_INT(10);
    CEDI_DISABLE_ALL_INT(11);
    CEDI_DISABLE_ALL_INT(12);
    CEDI_DISABLE_ALL_INT(13);
    CEDI_DISABLE_ALL_INT(14);
    CEDI_DISABLE_ALL_INT(15);
*/
}

static void clearAllInterrupts(void *pD)
{

#define CEDI_CLEAR_ALL_WRCLR_INT(Q)  if (CEDI_PdVar(numQs)>Q) \
        CPS_UncachedWrite32(CEDI_RegAddr(int_q##Q##_status), 0xFFFFFFFF);

#define CEDI_CLEAR_ALL_RDCLR_INT(Q)  if (CEDI_PdVar(numQs)>Q) \
        CPS_UncachedRead32(CEDI_RegAddr(int_q##Q##_status));

    if (0==CEDI_PdVar(hwCfg).irq_read_clear) {
        CPS_UncachedWrite32(CEDI_RegAddr(int_status), 0xFFFFFFFF);
        CEDI_CLEAR_ALL_RDCLR_INT(1);
        CEDI_CLEAR_ALL_RDCLR_INT(2);
/*      // Only Three Queues are supported
        CEDI_CLEAR_ALL_RDCLR_INT(3);
        CEDI_CLEAR_ALL_RDCLR_INT(4);
        CEDI_CLEAR_ALL_RDCLR_INT(5);
        CEDI_CLEAR_ALL_RDCLR_INT(6);
        CEDI_CLEAR_ALL_RDCLR_INT(7);
        CEDI_CLEAR_ALL_RDCLR_INT(8);
        CEDI_CLEAR_ALL_RDCLR_INT(9);
        CEDI_CLEAR_ALL_RDCLR_INT(10);
        CEDI_CLEAR_ALL_RDCLR_INT(11);
        CEDI_CLEAR_ALL_RDCLR_INT(12);
        CEDI_CLEAR_ALL_RDCLR_INT(13);
        CEDI_CLEAR_ALL_RDCLR_INT(14);
        CEDI_CLEAR_ALL_RDCLR_INT(15);
*/
    }
    else {
        CPS_UncachedRead32(CEDI_RegAddr(int_status));
        CEDI_CLEAR_ALL_WRCLR_INT(1);
        CEDI_CLEAR_ALL_WRCLR_INT(2);
/*      // Only Three Queues are supported
        CEDI_CLEAR_ALL_WRCLR_INT(3);
        CEDI_CLEAR_ALL_WRCLR_INT(4);
        CEDI_CLEAR_ALL_WRCLR_INT(5);
        CEDI_CLEAR_ALL_WRCLR_INT(6);
        CEDI_CLEAR_ALL_WRCLR_INT(7);
        CEDI_CLEAR_ALL_WRCLR_INT(8);
        CEDI_CLEAR_ALL_WRCLR_INT(9);
        CEDI_CLEAR_ALL_WRCLR_INT(10);
        CEDI_CLEAR_ALL_WRCLR_INT(11);
        CEDI_CLEAR_ALL_WRCLR_INT(12);
        CEDI_CLEAR_ALL_WRCLR_INT(13);
        CEDI_CLEAR_ALL_WRCLR_INT(14);
        CEDI_CLEAR_ALL_WRCLR_INT(15);
*/
    }
}

/* Return all registers to reset values */
static void initAllRegs(void *pD)
{
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), 0);
//    CPS_UncachedWrite32(CEDI_RegAddr(user_io_register), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(transmit_status), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(receive_q_ptr), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(transmit_q_ptr), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(receive_status), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(int_disable), 0xFFFFFFFF);
    CPS_UncachedWrite32(CEDI_RegAddr(phy_management), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(tx_pause_quantum), 0xFFFFFFFF);
    CPS_UncachedWrite32(CEDI_RegAddr(pbuf_txcutthru), 0x00003FFF);
    CPS_UncachedWrite32(CEDI_RegAddr(pbuf_rxcutthru), 0x000007FF);
    CPS_UncachedWrite32(CEDI_RegAddr(jumbo_max_length), 0x00002800);
//    CPS_UncachedWrite32(CEDI_RegAddr(external_fifo_interface), 0);
//    CPS_UncachedWrite32(CEDI_RegAddr(axi_max_pipeline), 0x00000101);
//    CPS_UncachedWrite32(CEDI_RegAddr(rsc_control), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(int_moderation), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(sys_wake_time), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(hash_bottom), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(hash_top), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(wol_register), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(stretch_ratio), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(stacked_vlan), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(tx_pfc_pause), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(mask_add1_bottom), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(mask_add1_top), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(dma_addr_or_mask), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(rx_ptp_unicast), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(tx_ptp_unicast), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(tsu_nsec_cmp), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(tsu_sec_cmp), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(tsu_msb_sec_cmp), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(dpram_fill_dbg), 0);
//    CPS_UncachedWrite32(CEDI_RegAddr(pcs_control), 0);
//    CPS_UncachedWrite32(CEDI_RegAddr(pcs_an_adv), 0);
//    CPS_UncachedWrite32(CEDI_RegAddr(pcs_an_np_tx), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(tx_pause_quantum1), 0xFFFFFFFF);
    CPS_UncachedWrite32(CEDI_RegAddr(tx_pause_quantum2), 0xFFFFFFFF);
    CPS_UncachedWrite32(CEDI_RegAddr(tx_pause_quantum3), 0xFFFFFFFF);
    CPS_UncachedWrite32(CEDI_RegAddr(rx_lpi), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(rx_lpi_time), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(tx_lpi), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(tx_lpi_time), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(dpram_fill_dbg), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(cbs_control), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(cbs_idleslope_q_a), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(cbs_idleslope_q_b), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(upper_tx_q_base_addr), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(upper_rx_q_base_addr), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(tx_bd_control), 0);
    CPS_UncachedWrite32(CEDI_RegAddr(rx_bd_control), 0);
}

/* Check the selected callback(s) have non-NULL call addresses.
 * Test all events selected, returning any with NULL callbacks.
 * @param selection - bit-flags defining callback selection
 * @return 0 if all OK (not NULL)
 * @return OR'd combination of events whose cb function pointers are NULL
 */
static uint32_t callbacksNullCheck(void *pD, uint32_t selection)
{
    uint32_t nullCbEvents = 0;

    if (!selection)
        return 0;

    if ((selection & (CEDI_EV_TX_COMPLETE | CEDI_EV_TX_USED_READ))
            && ((CEDI_PdVar(cb).txEvent)==NULL))
    {
        nullCbEvents |=
                (selection & (CEDI_EV_TX_COMPLETE | CEDI_EV_TX_USED_READ));
        selection &= ~(CEDI_EV_TX_COMPLETE | CEDI_EV_TX_USED_READ);
        if (!selection)
            return nullCbEvents;
    }

    if ((selection & CEDI_EV_RX_COMPLETE) &&
                ((CEDI_PdVar(cb).rxFrame)==NULL))
    {
        nullCbEvents |= (selection & CEDI_EV_RX_COMPLETE);
        selection ^= ~selection & CEDI_EV_RX_COMPLETE;
        if (!selection)
            return nullCbEvents;
    }
    if ((selection & (CEDI_EV_TX_UNDERRUN | CEDI_EV_TX_RETRY_EX_LATE_COLL
                        | CEDI_EV_TX_FR_CORRUPT )) &&
                ((CEDI_PdVar(cb).txError)==NULL))
    {
        nullCbEvents |= (selection & (CEDI_EV_TX_UNDERRUN |
                        CEDI_EV_TX_RETRY_EX_LATE_COLL | CEDI_EV_TX_FR_CORRUPT));
        selection &= ~(CEDI_EV_TX_UNDERRUN |
                        CEDI_EV_TX_RETRY_EX_LATE_COLL | CEDI_EV_TX_FR_CORRUPT);
        if (!selection)
            return nullCbEvents;
    }

    if ((selection & (CEDI_EV_RX_USED_READ | CEDI_EV_RX_OVERRUN)) &&
                ((((CEDI_PrivateData *)pD)->cb.rxError)==NULL))
    {
        nullCbEvents |= (selection & (CEDI_EV_RX_USED_READ | CEDI_EV_RX_OVERRUN));
        selection &= ~(CEDI_EV_RX_USED_READ | CEDI_EV_RX_OVERRUN);
        if (!selection)
            return nullCbEvents;
    }

    if ((selection & CEDI_EV_MAN_FRAME) &&
            ((CEDI_PdVar(cb).phyManComplete)==NULL))
    {
        nullCbEvents |= CEDI_EV_MAN_FRAME;
        selection &= ~CEDI_EV_MAN_FRAME;
        if (!selection)
            return nullCbEvents;
    }

    if ((selection & CEDI_EV_HRESP_NOT_OK) &&
                ((CEDI_PdVar(cb).hrespError)==NULL))
    {
        nullCbEvents |= CEDI_EV_HRESP_NOT_OK;
        selection &= ~CEDI_EV_HRESP_NOT_OK;
        if (!selection)
            return nullCbEvents;
    }

    if ((selection & CEDI_EV_PCS_LP_PAGE_RX) &&
                ((CEDI_PdVar(cb).lpPageRx)==NULL))
    {
        nullCbEvents |= CEDI_EV_PCS_LP_PAGE_RX;
        selection &= ~CEDI_EV_PCS_LP_PAGE_RX;
        if (!selection)
            return nullCbEvents;
    }

    if ((selection & CEDI_EV_PCS_AN_COMPLETE) &&
                ((CEDI_PdVar(cb).anComplete)==NULL))
    {
        nullCbEvents |= CEDI_EV_PCS_AN_COMPLETE;
        selection &= ~CEDI_EV_PCS_AN_COMPLETE;
        if (!selection)
            return nullCbEvents;
    }

    if ((selection & CEDI_EV_PCS_LINK_CHANGE_DET) &&
                ((CEDI_PdVar(cb).linkChange)==NULL))
    {
        nullCbEvents |= CEDI_EV_PCS_LINK_CHANGE_DET;
        selection &= ~CEDI_EV_PCS_LINK_CHANGE_DET;
        if (!selection)
            return nullCbEvents;
    }

    if ((selection & (CEDI_EV_TSU_SEC_INC | CEDI_EV_TSU_TIME_MATCH)) &&
                ((CEDI_PdVar(cb).tsuEvent)==NULL))
    {
        nullCbEvents |= (selection &
                        (CEDI_EV_TSU_SEC_INC | CEDI_EV_TSU_TIME_MATCH));
        selection &= ~(CEDI_EV_TSU_SEC_INC | CEDI_EV_TSU_TIME_MATCH);
        if (!selection)
            return nullCbEvents;
    }

    if ((selection & (CEDI_EV_PAUSE_FRAME_TX | CEDI_EV_PAUSE_TIME_ZERO |
            CEDI_EV_PAUSE_NZ_QU_RX)) &&
                ((CEDI_PdVar(cb).pauseEvent)==NULL))
    {
        nullCbEvents |= (selection & (CEDI_EV_PAUSE_FRAME_TX |
                CEDI_EV_PAUSE_TIME_ZERO | CEDI_EV_PAUSE_NZ_QU_RX));
        selection &= ~(CEDI_EV_PAUSE_FRAME_TX | CEDI_EV_PAUSE_TIME_ZERO |
                            CEDI_EV_PAUSE_NZ_QU_RX);
        if (!selection)
            return nullCbEvents;
    }

    if ((selection & (CEDI_EV_PTP_TX_DLY_REQ | CEDI_EV_PTP_TX_SYNC)) &&
                ((CEDI_PdVar(cb).ptpPriFrameTx)==NULL))
    {
        nullCbEvents |= (selection &
                        (CEDI_EV_PTP_TX_DLY_REQ | CEDI_EV_PTP_TX_SYNC));
        selection &= ~(CEDI_EV_PTP_TX_DLY_REQ | CEDI_EV_PTP_TX_SYNC);
        if (!selection)
            return nullCbEvents;
    }


    if ((selection & (CEDI_EV_PTP_TX_PDLY_REQ | CEDI_EV_PTP_TX_PDLY_RSP)) &&
                ((CEDI_PdVar(cb).ptpPeerFrameTx)==NULL))
    {
        nullCbEvents |= (selection &
                        (CEDI_EV_PTP_TX_PDLY_REQ | CEDI_EV_PTP_TX_PDLY_RSP ));
        selection &= ~(CEDI_EV_PTP_TX_PDLY_REQ | CEDI_EV_PTP_TX_PDLY_RSP );
        if (!selection)
            return nullCbEvents;
    }

    if ((selection & (CEDI_EV_PTP_RX_DLY_REQ | CEDI_EV_PTP_RX_SYNC)) &&
                ((CEDI_PdVar(cb).ptpPriFrameRx)==NULL))
    {
        nullCbEvents |= (selection &
                        (CEDI_EV_PTP_RX_DLY_REQ | CEDI_EV_PTP_RX_SYNC));
        selection &= ~(CEDI_EV_PTP_RX_DLY_REQ | CEDI_EV_PTP_RX_SYNC);
        if (!selection)
            return nullCbEvents;
    }

    if ((selection & (CEDI_EV_PTP_RX_PDLY_REQ | CEDI_EV_PTP_RX_PDLY_RSP)) &&
                ((CEDI_PdVar(cb).ptpPeerFrameRx)==NULL))
    {
        nullCbEvents |= (selection &
                        (CEDI_EV_PTP_RX_PDLY_REQ | CEDI_EV_PTP_RX_PDLY_RSP));
        selection &= ~(CEDI_EV_PTP_RX_PDLY_REQ | CEDI_EV_PTP_RX_PDLY_RSP);
        if (!selection)
            return nullCbEvents;
    }

    if ((selection & CEDI_EV_LPI_CH_RX) && ((CEDI_PdVar(cb).lpiStatus)==NULL))
    {
        nullCbEvents |= CEDI_EV_LPI_CH_RX;
        selection &= ~CEDI_EV_LPI_CH_RX;
        if (!selection)
            return nullCbEvents;
    }

    if ((selection & CEDI_EV_WOL_RX) && ((CEDI_PdVar(cb).wolEvent)==NULL))
    {
        nullCbEvents |= CEDI_EV_WOL_RX;
        selection &= ~CEDI_EV_WOL_RX;
        if (!selection)
            return nullCbEvents;
    }

    if ((selection & CEDI_EV_EXT_INTR) && ((CEDI_PdVar(cb).extInpIntr)==NULL))
    {
        nullCbEvents |= CEDI_EV_EXT_INTR;
        selection &= ~CEDI_EV_EXT_INTR;
    }


    return nullCbEvents;
}

/* initializing the upper 32 bit buffer queue base addresses from config */
static void  initUpper32BuffQAddr(void *pD)
{
    uint32_t regData;

    regData = 0;

#ifdef EMAC_REGS__UPPER_RX_Q_BASE_ADDR__UPPER_RX_Q_BASE_ADDR__MODIFY
    EMAC_REGS__UPPER_TX_Q_BASE_ADDR__UPPER_TX_Q_BASE_ADDR__MODIFY(
            regData, CEDI_PdVar(cfg).upper32BuffTxQAddr);

    CPS_UncachedWrite32(CEDI_RegAddr(upper_tx_q_base_addr), regData);

    regData = 0;
    EMAC_REGS__UPPER_RX_Q_BASE_ADDR__UPPER_RX_Q_BASE_ADDR__MODIFY(
            regData, CEDI_PdVar(cfg).upper32BuffRxQAddr);

    CPS_UncachedWrite32(CEDI_RegAddr(upper_rx_q_base_addr), regData);
#else
    EMAC_REGS__MSB_BUFF_Q_BASE_ADDR_REG__MSB_BUFF_Q_BASE_ADDR__MODIFY(
            regData, CEDI_PdVar(cfg).upper32BuffTxQAddr);

    CPS_UncachedWrite32(CEDI_RegAddr(msb_buff_q_base_addr_reg), regData);
#endif
}

/* Initialise axi_max_pipeline register from config struct */
static void initAxiMaxPipelineReg(void *pD)
{
    CEDI_Config *config = &CEDI_PdVar(cfg);
    uint32_t regData, axiPipelineFifoDepth;

    regData = CPS_UncachedRead32(CEDI_RegAddr(axi_max_pipeline));
    axiPipelineFifoDepth = 1<<(CEDI_PdVar(hwCfg).axi_access_pipeline_bits);

    /* value of max pipeline must be >0 and not greater than fifo depth
     * (2^axi_access_pipeline) */
    if ((CEDI_PdVar(hwCfg).axi) && (config->aw2wMaxPipeline==0)) {
        vDbgMsg(DBG_GEN_MSG, 5, "%s\n",
            "*** Warning: aw2wMaxPipeline requested value = 0, increasing to 1");
        config->aw2wMaxPipeline = 1;
    } else if ((config->aw2wMaxPipeline) > axiPipelineFifoDepth) {
        vDbgMsg(DBG_GEN_MSG, 5, "*** Warning: aw2wMaxPipeline requested"\
            "value (%u) greater than fifo depth (%u), reducing to %u\n",
            config->aw2wMaxPipeline, axiPipelineFifoDepth, axiPipelineFifoDepth);
        config->aw2wMaxPipeline = axiPipelineFifoDepth;
    }
    EMAC_REGS__AXI_MAX_PIPELINE__AW2W_MAX_PIPELINE__MODIFY(
                                    regData, config->aw2wMaxPipeline);

    if ((CEDI_PdVar(hwCfg).axi) && (config->ar2rMaxPipeline==0)) {
        vDbgMsg(DBG_GEN_MSG, 5, "%s\n",
            "*** Warning: ar2rMaxPipeline requested value = 0, increasing to 1");
        config->ar2rMaxPipeline = 1;
    }
    else if ((config->ar2rMaxPipeline) > axiPipelineFifoDepth) {
        vDbgMsg(DBG_GEN_MSG, 5, "*** Warning: ar2rMaxPipeline requested"\
            "value (%u) greater than fifo depth (%u), reducing to %u\n",
            config->ar2rMaxPipeline, axiPipelineFifoDepth, axiPipelineFifoDepth);
        config->ar2rMaxPipeline = axiPipelineFifoDepth;
    }
    EMAC_REGS__AXI_MAX_PIPELINE__AR2R_MAX_PIPELINE__MODIFY(
                                    regData, config->ar2rMaxPipeline);

    CPS_UncachedWrite32(CEDI_RegAddr(axi_max_pipeline), regData);
}

/* Initialise Network Control register from config struct */
static void initNetControlReg(void *pD)
{
    CEDI_Config *config = &CEDI_PdVar(cfg);
    uint32_t regTmp;

    /* Disable everything first to be safe */
    regTmp = 0;
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), regTmp);

    if (config->enableMdio)
        EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__SET(regTmp);

    if (config->altSgmiiEn)
        EMAC_REGS__NETWORK_CONTROL__ALT_SGMII_MODE__SET(regTmp);

    if (config->storeUdpTcpOffset)
        EMAC_REGS__NETWORK_CONTROL__STORE_UDP_OFFSET__SET(regTmp);

    /* for ext. TSU require tsu configured */
    if ((config->enExtTsuPort) && CEDI_PdVar(hwCfg).tsu)
        EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__SET(regTmp);
    /* pfc multi quantum functionality */
    if(config->pfcMultiQuantum)
        EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__SET(regTmp);
    /* clear stats */
    EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__SET(regTmp);

    CPS_UncachedWrite32(CEDI_RegAddr(network_control), regTmp);
}

/* Initialise DMA Config register from config struct */
static void initDmaConfigReg(void *pD)
{
  CEDI_Config *config = &CEDI_PdVar(cfg);
  uint32_t regTmp = 0, tmp1;

  switch(config->dmaDataBurstLen) {
  case CEDI_DMA_DBUR_LEN_1:
      tmp1 = CEDI_AMBD_BURST_LEN_1;
      break;
  case CEDI_DMA_DBUR_LEN_4:
      tmp1 = CEDI_AMBD_BURST_LEN_4;
      break;
  case CEDI_DMA_DBUR_LEN_8:
      tmp1 = CEDI_AMBD_BURST_LEN_8;
      break;
  case CEDI_DMA_DBUR_LEN_16:
      tmp1 = CEDI_AMBD_BURST_LEN_16;
      break;
  default:
      tmp1 = CEDI_AMBD_BURST_LEN_4;
      break;
  }
  EMAC_REGS__DMA_CONFIG__AMBA_BURST_LENGTH__MODIFY(regTmp, tmp1);

  if (config->dmaEndianism & CEDI_END_SWAP_DESC)
      EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_MANAGEMENT__SET(regTmp);
  if (config->dmaEndianism & CEDI_END_SWAP_DATA)
      EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_PACKET__SET(regTmp);

  EMAC_REGS__DMA_CONFIG__RX_PBUF_SIZE__MODIFY(regTmp, config->rxPktBufSize);
  EMAC_REGS__DMA_CONFIG__TX_PBUF_SIZE__MODIFY(regTmp, config->txPktBufSize);

  if (config->chkSumOffEn & CEDI_CFG_CHK_OFF_TX)
      EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__SET(regTmp);

  EMAC_REGS__DMA_CONFIG__RX_BUF_SIZE__MODIFY(regTmp, config->rxBufLength[0]);

  if (config->dmaCfgFlags & CEDI_CFG_DMA_DISC_RXP)
      EMAC_REGS__DMA_CONFIG__FORCE_DISCARD_ON_ERR__SET(regTmp);

  if (config->dmaCfgFlags & CEDI_CFG_DMA_FRCE_RX_BRST)
      EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_RX__SET(regTmp);

  if (config->dmaCfgFlags & CEDI_CFG_DMA_FRCE_TX_BRST)
      EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_TX__SET(regTmp);

  if (config->dmaAddrBusWidth)
      EMAC_REGS__DMA_CONFIG__DMA_ADDR_BUS_WIDTH_1__SET(regTmp);

  if (config->enTxExtBD)
      EMAC_REGS__DMA_CONFIG__TX_BD_EXTENDED_MODE_EN__SET(regTmp);

  if (config->enRxExtBD)
      EMAC_REGS__DMA_CONFIG__RX_BD_EXTENDED_MODE_EN__SET(regTmp);

  CPS_UncachedWrite32(CEDI_RegAddr(dma_config), regTmp);
}

/* Initialise Network Config register from config struct */
static void initNetConfigReg(void *pD)
{
    CEDI_Config *config = &CEDI_PdVar(cfg);
    uint32_t regTmp = 0;

    if ((config->ifTypeSel==CEDI_IFSP_1000M_GMII) ||
            (config->ifTypeSel==CEDI_IFSP_1000M_SGMII) ||
            (config->ifTypeSel==CEDI_IFSP_1000BASE_X))
        EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__SET(regTmp);

    if ((config->ifTypeSel==CEDI_IFSP_10M_SGMII) ||
            (config->ifTypeSel==CEDI_IFSP_100M_SGMII) ||
            (config->ifTypeSel==CEDI_IFSP_1000M_SGMII) ||
            (config->ifTypeSel==CEDI_IFSP_1000BASE_X))
        EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__SET(regTmp);

    if ((config->ifTypeSel==CEDI_IFSP_10M_SGMII) ||
            (config->ifTypeSel==CEDI_IFSP_100M_SGMII) ||
            (config->ifTypeSel==CEDI_IFSP_1000M_SGMII))
        EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__SET(regTmp);

    if (config->uniDirEnable)
        EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__SET(regTmp);

    if ((config->ifTypeSel != CEDI_IFSP_10M_MII) &&
            (config->ifTypeSel != CEDI_IFSP_10M_SGMII))
        EMAC_REGS__NETWORK_CONFIG__SPEED__SET(regTmp);

    if (config->fullDuplex)
        EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__SET(regTmp);

    if (config->enRxHalfDupTx)
        EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__SET(regTmp);

    if (config->ignoreIpgRxEr)
        EMAC_REGS__NETWORK_CONFIG__IGNORE_IPG_RX_ER__SET(regTmp);

    if (config->enRxBadPreamble)
        EMAC_REGS__NETWORK_CONFIG__NSP_CHANGE__SET(regTmp);

    if (config->rxJumboFrEn)
        EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__SET(regTmp);

    if (config->rx1536ByteEn)
        EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__SET(regTmp);

    if (config->extAddrMatch)
        EMAC_REGS__NETWORK_CONFIG__EXTERNAL_ADDRESS_MATCH_ENABLE__SET(regTmp);

    EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__MODIFY(regTmp,
            config->rxBufOffset);

    if (config->rxLenErrDisc)
        EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__SET(
                regTmp);

    EMAC_REGS__NETWORK_CONFIG__MDC_CLOCK_DIVISION__MODIFY(regTmp,
            config->mdcPclkDiv);

    EMAC_REGS__NETWORK_CONFIG__DATA_BUS_WIDTH__MODIFY(regTmp,
            config->dmaBusWidth);

    if (config->disCopyPause)
        EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__SET(regTmp);

    if (config->chkSumOffEn & CEDI_CFG_CHK_OFF_RX)
        EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__SET(regTmp);

    CPS_UncachedWrite32(CEDI_RegAddr(network_config), regTmp);
}


/* set Rx buffer sizes for Q>0 */
static void setRxQBufferSizes(void *pD, const CEDI_Config *config)
{
#define CEDI_WR_RXQB_SIZE_N_CASE(Q) \
     case Q: CPS_UncachedWrite32(CEDI_RegAddr(dma_rxbuf_size_q##Q), reg);\
                    break;

    uint32_t reg, q;
    if (CEDI_PdVar(cfg).rxQs>1)
        for (q=1; q<=CEDI_PdVar(cfg).rxQs; q++) {
            reg = 0;
            EMAC_REGS__DMA_RXBUF_SIZE_Q__DMA_RX_Q_BUF_SIZE__MODIFY(
                                    reg, config->rxBufLength[q]);
            switch(q) {
            CEDI_WR_RXQB_SIZE_N_CASE(1);
            CEDI_WR_RXQB_SIZE_N_CASE(2);
/*          // Three queues are supported
            CEDI_WR_RXQB_SIZE_N_CASE(3);
            CEDI_WR_RXQB_SIZE_N_CASE(4);
            CEDI_WR_RXQB_SIZE_N_CASE(5);
            CEDI_WR_RXQB_SIZE_N_CASE(6);
            CEDI_WR_RXQB_SIZE_N_CASE(7);
            CEDI_WR_RXQB_SIZE_N_CASE(8);
            CEDI_WR_RXQB_SIZE_N_CASE(9);
            CEDI_WR_RXQB_SIZE_N_CASE(10);
            CEDI_WR_RXQB_SIZE_N_CASE(11);
            CEDI_WR_RXQB_SIZE_N_CASE(12);
            CEDI_WR_RXQB_SIZE_N_CASE(13);
            CEDI_WR_RXQB_SIZE_N_CASE(14);
            CEDI_WR_RXQB_SIZE_N_CASE(15);
*/
            }
        }
}

/*****************  Hardware Revision Compatibility Tests  *******************/

/* Return non-zero if h/w includes stateless offloads */
uint32_t offloadsSupport(void *pD)
{
    if (pD==NULL)
        return 0;
    else
        return (((CEDI_PdVar(hwCfg).moduleId==GEM_GXL_MODULE_ID_V0)
        || (CEDI_PdVar(hwCfg).moduleId==GEM_GXL_MODULE_ID_V1))
                && (CEDI_PdVar(hwCfg).moduleRev>=OFFLOADS_GEM_GXL_REV));
}

/* Return non-zero if h/w includes 24bit sub-ns timer increment resolution */
uint32_t subNsTsuInc24bSupport(void *pD)
{
    if (pD==NULL)
        return 0;
    else
    /* resolution increase came in at r1p06f2 */
        return (((CEDI_PdVar(hwCfg).moduleId==GEM_GXL_MODULE_ID_V0)
                 && (CEDI_PdVar(hwCfg).moduleRev==0x0106)
                 && (CEDI_PdVar(hwCfg).fixNumber>=2))
                || ((CEDI_PdVar(hwCfg).moduleId==GEM_GXL_MODULE_ID_V0)
                 && (CEDI_PdVar(hwCfg).moduleRev>0x0106))
        || (CEDI_PdVar(hwCfg).moduleId>=GEM_GXL_MODULE_ID_V1));
}

/* Read DesignConfig Debug registers into privateData for faster access.
 * pD must point to a privateData struct with cfg.regBase set */
uint32_t readDesignConfig(void *pD)
{
    uint32_t reg;

    if (pD==NULL)
        return EINVAL;

    /* read in revision & number of queues, which are also set by defs file */
    CEDI_PdVar(hwCfg).numQueues = maxHwQs(CEDI_PdVar(cfg).regBase);

    reg = CPS_UncachedRead32(CEDI_RegAddr(revision_reg));

    CEDI_PdVar(hwCfg).moduleId =
            EMAC_REGS__REVISION_REG__MODULE_IDENTIFICATION_NUMBER__READ(reg);
    CEDI_PdVar(hwCfg).moduleRev =
            EMAC_REGS__REVISION_REG__MODULE_REVISION__READ(reg);
    CEDI_PdVar(hwCfg).fixNumber =
#ifdef EMAC_REGS__REVISION_REG__FIX_NUMBER__READ
            EMAC_REGS__REVISION_REG__FIX_NUMBER__READ(reg);
#else
            0;
#endif

    reg = CPS_UncachedRead32(CEDI_RegAddr(designcfg_debug1));
    CEDI_PdVar(hwCfg).no_pcs =
            EMAC_REGS__DESIGNCFG_DEBUG1__NO_PCS__READ(reg);
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__SERDES__READ
    CEDI_PdVar(hwCfg).serdes =
            EMAC_REGS__DESIGNCFG_DEBUG1__SERDES__READ(reg);
#endif
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__RDC_50__READ
    CEDI_PdVar(hwCfg).RDC_50 =
            EMAC_REGS__DESIGNCFG_DEBUG1__RDC_50__READ(reg);
#endif
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__TDC_50__READ
    CEDI_PdVar(hwCfg).TDC_50 =
            EMAC_REGS__DESIGNCFG_DEBUG1__TDC_50__READ(reg);
#endif
    CEDI_PdVar(hwCfg).int_loopback =
            EMAC_REGS__DESIGNCFG_DEBUG1__INT_LOOPBACK__READ(reg);
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__NO_INT_LOOPBACK__READ
    CEDI_PdVar(hwCfg).no_int_loopback =
            EMAC_REGS__DESIGNCFG_DEBUG1__NO_INT_LOOPBACK__READ(reg);
#else
    CEDI_PdVar(hwCfg).no_int_loopback = !CEDI_PdVar(hwCfg).int_loopback;
#endif
    CEDI_PdVar(hwCfg).ext_fifo_interface =
            EMAC_REGS__DESIGNCFG_DEBUG1__EXT_FIFO_INTERFACE__READ(reg);

#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__APB_REV1__READ
    CEDI_PdVar(hwCfg).apb_rev1 =
            EMAC_REGS__DESIGNCFG_DEBUG1__APB_REV1__READ(reg);
#endif
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__APB_REV2__READ
    CEDI_PdVar(hwCfg).apb_rev2 =
            EMAC_REGS__DESIGNCFG_DEBUG1__APB_REV2__READ(reg);
#endif
    CEDI_PdVar(hwCfg).user_io =
            EMAC_REGS__DESIGNCFG_DEBUG1__USER_IO__READ(reg);
    CEDI_PdVar(hwCfg).user_out_width =
            EMAC_REGS__DESIGNCFG_DEBUG1__USER_OUT_WIDTH__READ(reg);
    CEDI_PdVar(hwCfg).user_in_width =
            EMAC_REGS__DESIGNCFG_DEBUG1__USER_IN_WIDTH__READ(reg);
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__NO_SCAN_PINS__READ
    CEDI_PdVar(hwCfg).no_scan_pins =
            EMAC_REGS__DESIGNCFG_DEBUG1__NO_SCAN_PINS__READ(reg);
#endif
    CEDI_PdVar(hwCfg).no_stats =
            EMAC_REGS__DESIGNCFG_DEBUG1__NO_STATS__READ(reg);
    CEDI_PdVar(hwCfg).no_snapshot =
            EMAC_REGS__DESIGNCFG_DEBUG1__NO_SNAPSHOT__READ(reg);
    CEDI_PdVar(hwCfg).irq_read_clear =
            EMAC_REGS__DESIGNCFG_DEBUG1__IRQ_READ_CLEAR__READ(reg);
#ifdef EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_CBS__READ
    /* need both compile-time test for macro and runtime test for feature
       support, to allow regression against older h/w */
    if (offloadsSupport(pD))
        CEDI_PdVar(hwCfg).exclude_cbs =
            EMAC_REGS__DESIGNCFG_DEBUG1__EXCLUDE_CBS__READ(reg);
#else
    CEDI_PdVar(hwCfg).exclude_cbs = 0;
#endif
    CEDI_PdVar(hwCfg).dma_bus_width =
            EMAC_REGS__DESIGNCFG_DEBUG1__DMA_BUS_WIDTH__READ(reg);
    CEDI_PdVar(hwCfg).axi_cache_value =
            EMAC_REGS__DESIGNCFG_DEBUG1__AXI_CACHE_VALUE__READ(reg);

    reg = CPS_UncachedRead32(CEDI_RegAddr(designcfg_debug2));
    CEDI_PdVar(hwCfg).jumbo_max_length =
            EMAC_REGS__DESIGNCFG_DEBUG2__JUMBO_MAX_LENGTH__READ(reg);
    CEDI_PdVar(hwCfg).hprot_value =
            EMAC_REGS__DESIGNCFG_DEBUG2__HPROT_VALUE__READ(reg);
    CEDI_PdVar(hwCfg).rx_pkt_buffer =
            EMAC_REGS__DESIGNCFG_DEBUG2__RX_PKT_BUFFER__READ(reg);
    CEDI_PdVar(hwCfg).tx_pkt_buffer =
            EMAC_REGS__DESIGNCFG_DEBUG2__TX_PKT_BUFFER__READ(reg);
    CEDI_PdVar(hwCfg).rx_pbuf_addr =
            EMAC_REGS__DESIGNCFG_DEBUG2__RX_PBUF_ADDR__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_addr =
            EMAC_REGS__DESIGNCFG_DEBUG2__TX_PBUF_ADDR__READ(reg);
    CEDI_PdVar(hwCfg).axi =
            EMAC_REGS__DESIGNCFG_DEBUG2__AXI__READ(reg);

    reg = CPS_UncachedRead32(CEDI_RegAddr(designcfg_debug3));
    CEDI_PdVar(hwCfg).num_spec_add_filters =
            EMAC_REGS__DESIGNCFG_DEBUG3__NUM_SPEC_ADD_FILTERS__READ(reg);

    reg = CPS_UncachedRead32(CEDI_RegAddr(designcfg_debug5));
    CEDI_PdVar(hwCfg).rx_fifo_cnt_width =
            EMAC_REGS__DESIGNCFG_DEBUG5__RX_FIFO_CNT_WIDTH__READ(reg);
    CEDI_PdVar(hwCfg).tx_fifo_cnt_width =
            EMAC_REGS__DESIGNCFG_DEBUG5__TX_FIFO_CNT_WIDTH__READ(reg);
    CEDI_PdVar(hwCfg).tsu =
            EMAC_REGS__DESIGNCFG_DEBUG5__TSU__READ(reg);
    CEDI_PdVar(hwCfg).phy_ident =
            EMAC_REGS__DESIGNCFG_DEBUG5__PHY_IDENT__READ(reg);
    CEDI_PdVar(hwCfg).dma_bus_width_def =
            EMAC_REGS__DESIGNCFG_DEBUG5__DMA_BUS_WIDTH_DEF__READ(reg);
    CEDI_PdVar(hwCfg).mdc_clock_div =
            EMAC_REGS__DESIGNCFG_DEBUG5__MDC_CLOCK_DIV__READ(reg);
    CEDI_PdVar(hwCfg).endian_swap_def =
            EMAC_REGS__DESIGNCFG_DEBUG5__ENDIAN_SWAP_DEF__READ(reg);
    CEDI_PdVar(hwCfg).rx_pbuf_size_def =
            EMAC_REGS__DESIGNCFG_DEBUG5__RX_PBUF_SIZE_DEF__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_size_def =
            EMAC_REGS__DESIGNCFG_DEBUG5__TX_PBUF_SIZE_DEF__READ(reg);
    CEDI_PdVar(hwCfg).rx_buffer_length_def =
            EMAC_REGS__DESIGNCFG_DEBUG5__RX_BUFFER_LENGTH_DEF__READ(reg);
    CEDI_PdVar(hwCfg).tsu_clk =
            EMAC_REGS__DESIGNCFG_DEBUG5__TSU_CLK__READ(reg);
    CEDI_PdVar(hwCfg).axi_prot_value =
            EMAC_REGS__DESIGNCFG_DEBUG5__AXI_PROT_VALUE__READ(reg);

    reg = CPS_UncachedRead32(CEDI_RegAddr(designcfg_debug6));
    CEDI_PdVar(hwCfg).tx_pbuf_queue_segment_size =
            EMAC_REGS__DESIGNCFG_DEBUG6__TX_PBUF_QUEUE_SEGMENT_SIZE__READ(reg);
    CEDI_PdVar(hwCfg).ext_tsu_timer =
            EMAC_REGS__DESIGNCFG_DEBUG6__EXT_TSU_TIMER__READ(reg);
    CEDI_PdVar(hwCfg).tx_add_fifo_if =
            EMAC_REGS__DESIGNCFG_DEBUG6__TX_ADD_FIFO_IF__READ(reg);
    CEDI_PdVar(hwCfg).host_if_soft_select =
            EMAC_REGS__DESIGNCFG_DEBUG6__HOST_IF_SOFT_SELECT__READ(reg);
    CEDI_PdVar(hwCfg).dma_addr_width =
            EMAC_REGS__DESIGNCFG_DEBUG6__DMA_ADDR_WIDTH_IS_64B__READ(reg);
    CEDI_PdVar(hwCfg).pfc_multi_quantum =
            EMAC_REGS__DESIGNCFG_DEBUG6__PFC_MULTI_QUANTUM__READ(reg);
    /* Offloads features: first available in GEM_GXL rev 1p07- */
    if (offloadsSupport(pD)) {
#ifdef EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_LSO__READ
        CEDI_PdVar(hwCfg).pbuf_lso =
                EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_LSO__READ(reg);
#else
        CEDI_PdVar(hwCfg).pbuf_lso = 0;
#endif
#ifdef EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_RSC__READ
        CEDI_PdVar(hwCfg).pbuf_rsc =
                EMAC_REGS__DESIGNCFG_DEBUG6__PBUF_RSC__READ(reg);
#else
        CEDI_PdVar(hwCfg).pbuf_rsc = 0;
#endif
        CEDI_PdVar(hwCfg).intrpt_mod = 1;
        CEDI_PdVar(hwCfg).hdr_split = 1;
    } else {
        CEDI_PdVar(hwCfg).pbuf_lso = 0;
        CEDI_PdVar(hwCfg).pbuf_rsc = 0;
        CEDI_PdVar(hwCfg).intrpt_mod = 0;
        CEDI_PdVar(hwCfg).hdr_split = 0;
    }
    reg = CPS_UncachedRead32(CEDI_RegAddr(designcfg_debug7));
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q0 =
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q0__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q1 =
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q1__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q2 =
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q2__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q3 =
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q3__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q4 =
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q4__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q5 =
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q5__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q6 =
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q6__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q7 =
            EMAC_REGS__DESIGNCFG_DEBUG7__TX_PBUF_NUM_SEGMENTS_Q7__READ(reg);

    reg = CPS_UncachedRead32(CEDI_RegAddr(designcfg_debug8));
    CEDI_PdVar(hwCfg).num_type1_screeners =
            EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE1_SCREENERS__READ(reg);
    CEDI_PdVar(hwCfg).num_type2_screeners =
            EMAC_REGS__DESIGNCFG_DEBUG8__NUM_TYPE2_SCREENERS__READ(reg);
    CEDI_PdVar(hwCfg).num_scr2_ethtype_regs =
            EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_ETHTYPE_REGS__READ(reg);
    CEDI_PdVar(hwCfg).num_scr2_compare_regs =
            EMAC_REGS__DESIGNCFG_DEBUG8__NUM_SCR2_COMPARE_REGS__READ(reg);

    reg = CPS_UncachedRead32(CEDI_RegAddr(designcfg_debug9));
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q8 =
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q8__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q9 =
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q9__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q10 =
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q10__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q11 =
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q11__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q12 =
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q12__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q13 =
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q13__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q14 =
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q14__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q15 =
            EMAC_REGS__DESIGNCFG_DEBUG9__TX_PBUF_NUM_SEGMENTS_Q15__READ(reg);

    reg = CPS_UncachedRead32(CEDI_RegAddr(designcfg_debug10));
    CEDI_PdVar(hwCfg).axi_access_pipeline_bits =
          EMAC_REGS__DESIGNCFG_DEBUG10__AXI_ACCESS_PIPELINE_BITS__READ(reg);
    CEDI_PdVar(hwCfg).rx_pbuf_data =
            EMAC_REGS__DESIGNCFG_DEBUG10__RX_PBUF_DATA__READ(reg);
    CEDI_PdVar(hwCfg).tx_pbuf_data =
            EMAC_REGS__DESIGNCFG_DEBUG10__TX_PBUF_DATA__READ(reg);

    return 0;
}

/******************************************************************************
 * Public Driver functions
 * ***************************************************************************/

uint32_t emacProbe(CEDI_Config *config, CEDI_SysReq *sysReq)
{
    uint32_t regTmp, regVal;
    uint16_t txDescSize, rxDescSize, sumTxDesc, sumRxDesc;
    struct emac_regs *regAddr;
    uint8_t paramErr = 0, numQs;
    uint16_t i;

    if ((config==NULL) || (sysReq==NULL)) {
        vDbgMsg(DBG_GEN_MSG, 5, "%s\n", "Error: NULL parameter supplied");
        return EINVAL;
    }

    vDbgMsg(DBG_GEN_MSG, 10, "%s entered (regBase %p)\n", __func__,
                    (void *)config->regBase);

    if (config->regBase % sizeof(uint32_t)) {
        vDbgMsg(DBG_GEN_MSG, 5,
                "%s\n", "Error: regBase address not 32-bit aligned");
        return EINVAL;
    }

    /* Module ID check */
    regAddr = ((struct emac_regs *)(config->regBase));
    regVal = CPS_UncachedRead32(&(regAddr->revision_reg));
    regTmp = EMAC_REGS__REVISION_REG__MODULE_IDENTIFICATION_NUMBER__READ(
                    regVal);
    if ((regTmp!=GEM_GXL_MODULE_ID_V0) &&
    (regTmp!=GEM_GXL_MODULE_ID_V1) &&
          (regTmp!=GEM_XL_MODULE_ID)) {
        vDbgMsg(DBG_GEN_MSG, 5,
          "Error: Module ID check failed - 0x%04X read, IP type not supported\n",
          regTmp);
#ifndef SANITY_CHECK_TESTS
        return EINVAL;
#endif //SANITY_CHECK_TESTS
    }
    else
    {
        /**/
#ifdef EMAC_REGS__REVISION_REG__FIX_NUMBER__READ
        vDbgMsg(DBG_GEN_MSG, 10,
                "Module ID = 0x%03X, design rev = 0x%04X, fix no. = %u\n",
                regTmp,
                EMAC_REGS__REVISION_REG__MODULE_REVISION__READ(regVal),
                EMAC_REGS__REVISION_REG__FIX_NUMBER__READ(regVal)
                );
#else
        vDbgMsg(DBG_GEN_MSG, 10, "Module ID = 0x%04X, design rev = 0x%04X\n", regTmp,
                EMAC_REGS__REVISION_REG__MODULE_REVISION__READ(regVal));
#endif
    }

    /* required config parameters range checking */
    paramErr = ((config->rxQs==0) || (config->txQs==0));

    /* limit numbers of queues to what is available */
    numQs = maxHwQs(config->regBase);
    if (config->rxQs>numQs) {
        vDbgMsg(DBG_GEN_MSG, 10,
            "Warning: Too many Rx queues requested (%u), only %u in h/w config\n",
            config->rxQs, numQs);
        config->rxQs = numQs;
    }
    if (config->txQs>numQs) {
        vDbgMsg(DBG_GEN_MSG, 10,
            "Warning: Too many Tx queues requested (%u), only %u in h/w config\n",
                config->txQs, numQs);
        config->txQs = numQs;
    }

    regTmp = EMAC_REGS__DESIGNCFG_DEBUG6__DMA_ADDR_WIDTH_IS_64B__READ(
                CPS_UncachedRead32(&(regAddr->designcfg_debug6)));

    // DMA address bus width. 0 =32b , 1=64b
    if ((config->dmaAddrBusWidth) && (!regTmp))
    {
        vDbgMsg(DBG_GEN_MSG, 10, "%s\n",
                  "Warning: 64-bit DMA addressing not supported in h/w config");
        config->dmaAddrBusWidth = 0;
    }

    for (i=0; i<config->rxQs; i++)
    {
        if (config->rxQLen[i]>CEDI_MAX_RBQ_LENGTH)
        {
            vDbgMsg(DBG_GEN_MSG, 10,
                "config->rxQLen(%u) (=%u) greater than maximum limit (%u)\n",
                i, config->rxQLen[i], CEDI_MAX_RBQ_LENGTH);
            paramErr = 1;
            break;
        }
    }
    if (!paramErr)
        for (i=0; i<config->txQs; i++)
        {
            if (config->txQLen[i]>CEDI_MAX_TBQ_LENGTH)
            {
                vDbgMsg(DBG_GEN_MSG, 10,
                    "config->txQLen(%u) (=%u) greater than maximum limit (%u)\n",
                    i, config->txQLen[i], CEDI_MAX_TBQ_LENGTH);
                paramErr = 1;
                break;
            }
        }

    if (paramErr)
    {
        vDbgMsg(DBG_GEN_MSG, 5, "%s\n", "Error: parameter out of range");
        return EINVAL;
    }

    /* required memory allocations */

    /* descriptor list sizes */
    calcDescriptorSizes(config, &txDescSize, &rxDescSize);

    sumTxDesc = numTxDescriptors(config);
    sysReq->txDescListSize = sumTxDesc * txDescSize;
    vDbgMsg(DBG_GEN_MSG, 10, "txQSize = %u\n", sysReq->txDescListSize);
    vDbgMsg(DBG_GEN_MSG, 10, "txDescSize = %u bytes\n", txDescSize);

    sumRxDesc = numRxDescriptors(config);
    sysReq->rxDescListSize = sumRxDesc * rxDescSize;
    vDbgMsg(DBG_GEN_MSG, 10, "rxQSize = %u\n", sysReq->rxDescListSize);
    vDbgMsg(DBG_GEN_MSG, 10, "rxDescSize = %u bytes\n", rxDescSize);

    /* privateData including vAddr lists */
    sysReq->privDataSize = sizeof(CEDI_PrivateData)
                                  + sizeof(uintptr_t)*(sumTxDesc+sumRxDesc);
    vDbgMsg(DBG_GEN_MSG, 10, "privDataSize = %u bytes\n",
            sysReq->privDataSize);
    sysReq->statsSize = sizeof(CEDI_Statistics);
    vDbgMsg(DBG_GEN_MSG, 10, "statsSize = %u bytes\n",
            sysReq->statsSize);

    return 0;
}

uint32_t emacInit(void *pD, const CEDI_Config *config,
    CEDI_Callbacks *callbacks)
{
#define CEDI_ADD_TX_PBUF_SEGS(Q)  if (CEDI_PdVar(numQs)>Q)\
          numQSegs += 1<<CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q##Q;

    uint8_t hwConfigErr = 0;
    uint32_t  paramErr = 0;
    int i;
    uint32_t numTxSegs, numQSegs;
    CEDI_T1Screen clrT1Scrn = {0, 0, 0, 0, 0};
    CEDI_T2Screen clrT2Scrn = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vDbgMsg(DBG_GEN_MSG, 10, "%s entered (regBase %08X)\n", __func__,
            (uint32_t)config->regBase);

    /* parameter validation */
    if ((pD==NULL) || (config==NULL) || (callbacks==NULL))
    {
        vDbgMsg(DBG_GEN_MSG, 5, "%s\n",
                "Error: NULL main parameter");
        return EINVAL;
    }

    if (!paramErr)
    {
        /* Copy config & callbacks into private data */
        ((CEDI_PrivateData *)pD)->cfg = *config;
        ((CEDI_PrivateData *)pD)->cb = *callbacks;

        paramErr = callbacksNullCheck(pD, config->intrEnable);

        if (paramErr)
        {
            /**/
            vDbgMsg(DBG_GEN_MSG, 5,
                    "Error: Callback =NULL for event(s) 0x%08X\n", paramErr);
        }

        readDesignConfig(pD);

        initAllRegs(pD);
    }

    if (!paramErr) {
        CEDI_PdVar(numQs) = CEDI_PdVar(hwCfg).numQueues;
        if ((config->rxQs==0) || (config->rxQs>CEDI_PdVar(numQs)) ||
                (config->txQs==0) || (config->txQs>CEDI_PdVar(numQs)))
        {
            vDbgMsg(DBG_GEN_MSG, 5, "%s\n",
                    "Error: out-of-range numQs parameter");
            paramErr = 1;
        }
    }

    if (!paramErr)
        for (i=0; i<config->rxQs; i++)
        {
            if (config->rxQLen[i]>CEDI_MAX_RBQ_LENGTH)
            {
                paramErr = 1;
                vDbgMsg(DBG_GEN_MSG, 5,
                        "Error: out-of-range rxQLen(%u) parameter\n", i);
                break;
            }
        }

    if (!paramErr) {
        if ((config->txQAddr==(uintptr_t)NULL) ||
                (config->txQPhyAddr==0) ||
                (config->rxQAddr==(uintptr_t)NULL) ||
                (config->rxQPhyAddr==0))
        {
            vDbgMsg(DBG_GEN_MSG, 5, "%s\n",
                    "Error: NULL Tx or Rx descriptor address parameter");
            paramErr = 1;
        }
    }

    if (!paramErr)
        for (i=0; i<config->txQs; i++)
        {
            if (config->txQLen[i]>CEDI_MAX_TBQ_LENGTH)
            {
                paramErr = 1;
                vDbgMsg(DBG_GEN_MSG, 5,
                        "Error: out-of-range txQLen(%u) parameter\n", i);
                break;
            }
        }

    if (!paramErr)  {
        if ((config->dmaAddrBusWidth) &&
                (!((CEDI_PrivateData *)pD)->hwCfg.dma_addr_width))
        {
            vDbgMsg(DBG_GEN_MSG, 5, "%s\n",
                    "Error: 64-bit DMA addressing not supported in h/w config");
            paramErr = 1;
        }
    }

    if (!paramErr)  {
        paramErr = ((config->txPktBufSize>1) || (config->rxPktBufSize>3));
        if (!paramErr)
            for (i=0; i<config->rxQs; i++) {
                paramErr = paramErr || (config->rxBufLength[i]==0);
            }
        if (paramErr)
        {
            /**/
            vDbgMsg(DBG_GEN_MSG, 5, "%s\n",
                    "Error: Invalid Packet buffer size or Rx buffer length");
        }
    }

    if (!paramErr)  {
        if (config->dmaDataBurstLen>CEDI_DMA_DBUR_LEN_16) {
            vDbgMsg(DBG_GEN_MSG, 5, "%s\n",
                    "Error: Requested DMA burst length value out of range");
            paramErr = 1;
        }
    }

    if (!paramErr)  {
        vDbgMsg(DBG_GEN_MSG, 10, "1 << config->dmaBusWidth = %u, "\
                "CEDI_PdVar(hwCfg).dma_bus_width = %u\n",
                1 << config->dmaBusWidth, CEDI_PdVar(hwCfg).dma_bus_width);
        if ((1 << config->dmaBusWidth)>CEDI_PdVar(hwCfg).dma_bus_width) {
            vDbgMsg(DBG_GEN_MSG, 5, "%s\n",
                    "Error: Requested DMA bus width greater than h/w allows");
            paramErr = 1;
        }
    }

    if (!paramErr)  {
        // enforce 32- or 64-bit alignment for RX buffers only
        if (config->dmaBusWidth==CEDI_DMA_BUS_WIDTH_32)
            paramErr = ((config->rxQPhyAddr) % 4);
        else   /* expect 64-bit word alignment for 64/128-bit bus */
            paramErr = ((config->rxQPhyAddr) % 8);

        if (paramErr)
        {
            /**/
            vDbgMsg(DBG_GEN_MSG, 5, "%s\n",
                    "Error: bad alignment of descriptor list memory");
        }
    }

    if (!paramErr) {
        if (0!=(paramErr = config->ifTypeSel>CEDI_IFSP_1000BASE_X))
        {
            vDbgMsg(DBG_GEN_MSG, 5,
                    "Error: ifTypeSel out of range 0-CEDI_IFSP_1000BASE_X (%u)\n",
                    CEDI_PdVar(cfg).ifTypeSel);
        }
    }

    if (!paramErr) {
        if (0!=(paramErr = CEDI_PdVar(cfg).rxBufOffset>3))
        {
            vDbgMsg(DBG_GEN_MSG, 5,
                    "Error: rxBufOffset out of range 0-3 bytes (%u)\n",
                    CEDI_PdVar(cfg).rxBufOffset);
        }
    }

    if (!paramErr) {
        if (0!=(paramErr = config->mdcPclkDiv>CEDI_MDC_DIV_BY_224))
        {
            vDbgMsg(DBG_GEN_MSG, 5,
                    "Error: mdcPclkDiv out of range (%u)\n",
                    config->mdcPclkDiv);
        }
    }

    if (!paramErr && (0==CEDI_PdVar(hwCfg).no_stats)) {
        paramErr = (config->statsRegs==(uintptr_t)NULL);
        if (paramErr)
        {
            /**/
            vDbgMsg(DBG_GEN_MSG, 5, "%s",
                    "Error: NULL statistics struct address\n");
        }
    }

    if (!paramErr && (0==CEDI_PdVar(hwCfg).pfc_multi_quantum)) {
        paramErr = (config->pfcMultiQuantum == 1);
        if (paramErr)
        {
            /**/
            vDbgMsg(DBG_GEN_MSG, 5, "%s",
                    "Error: pfc Multiple quantum not supported by h/w\n");
        }
    }

    /* sanity-check multi-queue packet buffer segments and distribution */
    if ((CEDI_PdVar(numQs)>1) && (CEDI_PdVar(hwCfg).tx_pkt_buffer))
    {
        if (CEDI_PdVar(hwCfg).tx_pbuf_queue_segment_size>=
                CEDI_PdVar(hwCfg).tx_pbuf_addr) {
            vDbgMsg(DBG_GEN_MSG, 5,
                    "Error: H/w configuration specifies Tx segment size %u, "\
                    "must be less than Tx pbuf addr (%u)\n",
                    CEDI_PdVar(hwCfg).tx_pbuf_queue_segment_size,
                    CEDI_PdVar(hwCfg).tx_pbuf_addr);
            hwConfigErr = 1;
        }

        numTxSegs = 1<<CEDI_PdVar(hwCfg).tx_pbuf_queue_segment_size;
        if (numTxSegs<CEDI_PdVar(numQs)) {
            vDbgMsg(DBG_GEN_MSG, 5, "Error: H/w configuration specifies %u"\
                    " queues but only %u packet buffer segments\n",
                    CEDI_PdVar(numQs), numTxSegs);
            hwConfigErr = 1;
        }

        numQSegs = 1<<CEDI_PdVar(hwCfg).tx_pbuf_num_segments_q0;
        CEDI_ADD_TX_PBUF_SEGS(1);
        CEDI_ADD_TX_PBUF_SEGS(2);
/*      // Three Queues are supported
        CEDI_ADD_TX_PBUF_SEGS(3);
        CEDI_ADD_TX_PBUF_SEGS(4);
        CEDI_ADD_TX_PBUF_SEGS(5);
        CEDI_ADD_TX_PBUF_SEGS(6);
        CEDI_ADD_TX_PBUF_SEGS(7);
        CEDI_ADD_TX_PBUF_SEGS(8);
        CEDI_ADD_TX_PBUF_SEGS(9);
        CEDI_ADD_TX_PBUF_SEGS(10);
        CEDI_ADD_TX_PBUF_SEGS(11);
        CEDI_ADD_TX_PBUF_SEGS(12);
        CEDI_ADD_TX_PBUF_SEGS(13);
        CEDI_ADD_TX_PBUF_SEGS(14);
        CEDI_ADD_TX_PBUF_SEGS(15);
*/

        if (numQSegs>numTxSegs) {
            vDbgMsg(DBG_GEN_MSG, 5,
                    "Error: H/w configuration allocates %u Tx packet buffer"\
                    " segments to queues out of %u total\n", numQSegs, numTxSegs);
            hwConfigErr = 1;
        }
    }


    /* Need PCS present for these interface types */
    if (((config->ifTypeSel==CEDI_IFSP_10M_SGMII) ||
            (config->ifTypeSel==CEDI_IFSP_100M_SGMII) ||
            (config->ifTypeSel==CEDI_IFSP_1000M_SGMII) ||
            (config->ifTypeSel==CEDI_IFSP_1000BASE_X))
        && (EMAC_REGS__DESIGNCFG_DEBUG1__NO_PCS__READ(
                CPS_UncachedRead32(CEDI_RegAddr(designcfg_debug1))))) {

        vDbgMsg(DBG_GEN_MSG, 5,
            "Error: config struct specifies interface type (%u) which requires"\
            " PCS but this is not present in EMAC h/w\n", config->ifTypeSel);
        hwConfigErr = 1;
    }

    if (hwConfigErr)
        return ENOTSUP;
    else if (paramErr)
      return EINVAL;

   /****************** Initialise driver internal data ************************/

    ((CEDI_PrivateData *)pD)->anLinkStat = 0;
    ((CEDI_PrivateData *)pD)->anRemFault = 0;
    ((CEDI_PrivateData *)pD)->autoNegActive = 0;
    ((CEDI_PrivateData *)pD)->basePageExp = 1;

    /* ensure all interrupt sources disabled */
    disableAllInterrupts(pD);
    /* ensure ISRs are cleared */
    clearAllInterrupts(pD);

    /****************** Initialise Tx & Rx descriptor lists ********************/

    calcDescriptorSizes(config, &CEDI_PdVar(txDescriptorSize),
                                 &CEDI_PdVar(rxDescriptorSize));

    /* DMA config register */
    initDmaConfigReg(pD);

    /* writing the upper 32 bit buffer queue base address from config */
    initUpper32BuffQAddr(pD);

    if (0!=initTxDescLists(pD))
        return EINVAL;
    if (0!=initRxDescLists(pD))
        return EINVAL;

    /****************************** Initialise hardware ************************/

    /* Network control register */
    initNetControlReg(pD);

    /* Network config register */
    initNetConfigReg(pD);

    /* AXI Max pipeline register */
    if(ETH_AXI_MASTER_PRESENT == 1)
    {
        initAxiMaxPipelineReg(pD);
    }

    setRxQBufferSizes(pD, config);

    /* Ensure specific address registers disabled */
    for (i=1; i<=CEDI_PdVar(hwCfg).num_spec_add_filters; i++)
        emacDisableSpecAddr(pD, i);

    /* and screener registers */
    for (i=0; i<CEDI_PdVar(hwCfg).num_type1_screeners-1; i++)
        emacSetType1ScreenReg(pD, i, &clrT1Scrn);
    for (i=0; i<CEDI_PdVar(hwCfg).num_type2_screeners-1; i++)
        emacSetType2ScreenReg(pD, i, &clrT2Scrn);

    /* and hash match register cleared */
    emacSetHashAddr(pD, 0, 0);

    /* clear statistics */
    emacClearStats(pD);

    /* User outputs */
    emacWriteUserOutputs(pD, 0);


    /* PCS - PCS Select is set by initNetConfigReg */
    if (EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)))) {
        emacSetAutoNegEnable(pD, 0);
        CEDI_PdVar(anLinkStat) = 1;
        CEDI_PdVar(anRemFault) = 0;
    }

    /* Transmit Status */
    emacClearTxStatus(pD, CEDI_TXS_USED_READ | CEDI_TXS_COLLISION |
            CEDI_TXS_RETRY_EXC | CEDI_TXS_FRAME_ERR | CEDI_TXS_TX_COMPLETE |
            CEDI_TXS_UNDERRUN | CEDI_TXS_LATE_COLL | CEDI_TXS_HRESP_ERR);

    /* Receive Status */
    emacClearRxStatus(pD, CEDI_RXS_NO_BUFF | CEDI_RXS_FRAME_RX |
                            CEDI_RXS_OVERRUN | CEDI_RXS_HRESP_ERR);

    return 0;
}

void emacDestroy(void *pD)
{
    if (pD==NULL) return;
    vDbgMsg(DBG_GEN_MSG, 10, "%s entered (regBase %08X)\n", __func__,
            (uint32_t)CEDI_PdVar(cfg).regBase);

    emacAbortTx(pD);
    emacDisableRx(pD);

  /* disable interrupts & ... */
    disableAllInterrupts(pD);
}

void emacStart(void *pD)
{
    if (pD==NULL) return;
    vDbgMsg(DBG_GEN_MSG, 10, "%s entered (regBase %08X)\n", __func__,
            (uint32_t)CEDI_PdVar(cfg).regBase);

    /* enable events for all queues */
    emacSetEventEnable(pD, CEDI_PdVar(cfg).intrEnable, 1, CEDI_ALL_QUEUES);

    emacEnableRx(pD);
    emacEnableTx(pD);
}

void emacStop(void *pD)
{
    uint32_t t;
    // uint8_t q;
    if (pD==NULL) return;

    vDbgMsg(DBG_GEN_MSG, 10, "%s entered (regBase %08X)\n", __func__,
            (uint32_t)CEDI_PdVar(cfg).regBase);

    /* Halt any Tx after present frame has finished */
    emacStopTx(pD);
    for (t=10000; (t && emacTransmitting(pD)); t--) ;
    if (emacTransmitting(pD))
        emacAbortTx(pD);

    emacDisableRx(pD);
//    emacResetPcs(pD);

    /* disable all interrupt sources */
    disableAllInterrupts(pD);

}

uint32_t emacIsr(void *pD)
{
#define CEDI_INT_STATUS_WR_CASE(Q) case Q: \
        CPS_UncachedWrite32(CEDI_RegAddr(int_q##Q##_status), isrReg); break;

    uint32_t isrReg, regVal;
    uint32_t events;
    uint16_t dat16;
    uint8_t  qNum, cond1, cond2, cond3, handled = 0;
    CEDI_AnNextPage nullNp;
    uint8_t linkState;
    if (pD==NULL) return EINVAL;

//  vDbgMsg(DBG_GEN_MSG, 10, "%s entered (regBase %08X), int_mask = 0x%08X\n",
//          __func__, CEDI_PdVar(cfg).regBase,
//          CPS_UncachedRead32(CEDI_RegAddr(int_mask)));

    /* test for any ISR bits set */

    for (qNum=CEDI_PdVar(numQs)-1; qNum<CEDI_MAX_TX_QUEUES; qNum--) {

        /* read Interrupt Status Register */
        switch(qNum) {
        default: /* default */
        case 0: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_status)); break;
        case 1: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_q1_status)); break;
        case 2: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_q2_status)); break;
        case 3: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_q3_status)); break;
        case 4: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_q4_status)); break;
        case 5: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_q5_status)); break;
        case 6: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_q6_status)); break;
        case 7: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_q7_status)); break;
        case 8: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_q8_status)); break;
        case 9: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_q9_status)); break;
        case 10: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_q10_status)); break;
        case 11: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_q11_status)); break;
        case 12: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_q12_status)); break;
        case 13: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_q13_status)); break;
        case 14: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_q14_status)); break;
        case 15: isrReg = CPS_UncachedRead32(CEDI_RegAddr(int_q15_status)); break;
        }

        if (isrReg) {

            handled = 1;

            /* do clear-write if required */
            if (0==CEDI_PdVar(hwCfg).irq_read_clear) {
                switch(qNum) {
                default: /* default */
                case 0: CPS_UncachedWrite32(CEDI_RegAddr(int_status), isrReg);
                break;
                CEDI_INT_STATUS_WR_CASE(1);
                CEDI_INT_STATUS_WR_CASE(2);
/*              // Three queues are supported
                CEDI_INT_STATUS_WR_CASE(3);
                CEDI_INT_STATUS_WR_CASE(4);
                CEDI_INT_STATUS_WR_CASE(5);
                CEDI_INT_STATUS_WR_CASE(6);
                CEDI_INT_STATUS_WR_CASE(7);
                CEDI_INT_STATUS_WR_CASE(8);
                CEDI_INT_STATUS_WR_CASE(9);
                CEDI_INT_STATUS_WR_CASE(10);
                CEDI_INT_STATUS_WR_CASE(11);
                CEDI_INT_STATUS_WR_CASE(12);
                CEDI_INT_STATUS_WR_CASE(13);
                CEDI_INT_STATUS_WR_CASE(14);
                CEDI_INT_STATUS_WR_CASE(15);
*/
                }
            }

            /*vDbgMsg(DBG_GEN_MSG, 10, "EMAC (0x%08X) ISR Q%u = 0x%08X\n",
                            (uint32_t)CEDI_PdVar(cfg).regBase, qNum, isrReg);*/

            /*** test all intr status bits & do associated callbacks ***/

            /************************ PHY MDIO Frame Tx'd **********************/
            if ((qNum==0) &&
                    (EMAC_REGS__INT_STATUS__MANAGEMENT_FRAME_SENT__READ(isrReg)))
            {
                regVal = CPS_UncachedRead32(CEDI_RegAddr(phy_management));
                cond1 = (EMAC_REGS__PHY_MANAGEMENT__OPERATION__READ(regVal)==2)?1:0;
                dat16 = EMAC_REGS__PHY_MANAGEMENT__PHY_WRITE_READ_DATA__READ(regVal);
                vDbgMsg(DBG_GEN_MSG, 10,
                        "EMAC (0x%08X) PHY Management Frame sent to PHY(0x%02X) "\
                        "reg=0x%02X - %s operation, data=0x%04X\n",
                        (uint32_t)(((CEDI_PrivateData *)pD)->cfg).regBase,
                        EMAC_REGS__PHY_MANAGEMENT__PHY_ADDRESS__READ(regVal),
                        EMAC_REGS__PHY_MANAGEMENT__REGISTER_ADDRESS__READ(regVal),
                        cond1?"read":"write",
                                dat16);

                (*(CEDI_PdVar(cb).phyManComplete))(pD, cond1, dat16);
            }

            /****************************** TxEvent ****************************/
            cond1 = 0;
            cond2 = 0;

            if (qNum==0) {
                cond1 = EMAC_REGS__INT_STATUS__TX_USED_BIT_READ__READ(isrReg);
                cond2 = EMAC_REGS__INT_STATUS__TRANSMIT_COMPLETE__READ(isrReg);
            }
            else {
                cond1 = 0;
                cond2 = EMAC_REGS__INT_Q_STATUS__TRANSMIT_COMPLETE__READ(isrReg);
            }
            if (cond1 || cond2)
            {
                events = cond1?CEDI_EV_TX_USED_READ:0;
                events |= cond2?CEDI_EV_TX_COMPLETE:0;

                /* report both events in one callback call */
                /*vDbgMsg(DBG_GEN_MSG, 10,
                        "EMAC (0x%08X) Tx Event:0x%08X queue:%u\n",
                        (uint32_t)CEDI_PdVar(cfg).regBase, events, qNum);*/

                (*(CEDI_PdVar(cb).txEvent))(pD, events, qNum);
            }

            /****************************** TxError ****************************/
            cond1 = 0;
            cond2 = 0;
            cond3 = 0;

            if (qNum==0) {
                cond1 = EMAC_REGS__INT_STATUS__TRANSMIT_UNDER_RUN__READ(isrReg);
                cond2 =
                         EMAC_REGS__INT_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__READ(
                                 isrReg);
                cond3 = EMAC_REGS__INT_STATUS__AMBA_ERROR__READ(isrReg);
            }
            else {
                cond2 =
                         EMAC_REGS__INT_Q_STATUS__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION__READ(
                                 isrReg);
                cond3 = EMAC_REGS__INT_Q_STATUS__AMBA_ERROR__READ(isrReg);
            }
            if (cond1 || cond2 || cond3)
            {
                events = cond1?CEDI_EV_TX_UNDERRUN:0;
                events |= cond2?CEDI_EV_TX_RETRY_EX_LATE_COLL:0;
                events |= cond3?CEDI_EV_TX_FR_CORRUPT:0;

#ifdef DEBUG
                /* read Q ptr for debug */
                switch(qNum) {
                default: /* default */
                case 0: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q_ptr)); break;
                case 1: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q1_ptr)); break;
                case 2: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q2_ptr)); break;
                case 3: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q3_ptr)); break;
                case 4: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q4_ptr)); break;
                case 5: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q5_ptr)); break;
                case 6: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q6_ptr)); break;
                case 7: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q7_ptr)); break;
                case 8: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q8_ptr)); break;
                case 9: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q9_ptr)); break;
                case 10: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q10_ptr)); break;
                case 11: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q11_ptr)); break;
                case 12: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q12_ptr)); break;
                case 13: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q13_ptr)); break;
                case 14: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q14_ptr)); break;
                case 15: regVal = CPS_UncachedRead32(CEDI_RegAddr(transmit_q15_ptr)); break;
                }

                vDbgMsg(DBG_GEN_MSG, 10,
                        "EMAC (0x%08X) Tx Error:0x%08X queue:%u tx_q_ptr:"\
                        "0x%08X  isr0=%08X\n", (uint32_t)CEDI_PdVar(cfg).regBase,
                        events, qNum, regVal, isrReg);
#endif

                (*(CEDI_PdVar(cb).txError))(pD, events, qNum);
            }

            /*************************** RxFrame *******************************/
            if (((qNum==0) &&
                    (EMAC_REGS__INT_STATUS__RECEIVE_COMPLETE__READ(isrReg)))
                    ||
                    ((qNum>0) &&
                            (EMAC_REGS__INT_Q_STATUS__RECEIVE_COMPLETE__READ(isrReg))))
            {
                /*vDbgMsg(DBG_GEN_MSG, 10,
                        "EMAC (0x%08X) Rx Frame Complete, queue:%u\n",
                        (uint32_t)CEDI_PdVar(cfg).regBase, qNum);*/
                (*(CEDI_PdVar(cb).rxFrame))(pD, qNum);
            }

            /*************************** RxError *******************************/
            cond1 = 0;
            cond2 = 0;

            if (qNum==0) {
                cond1 = EMAC_REGS__INT_STATUS__RX_USED_BIT_READ__READ(isrReg);
                cond2 = EMAC_REGS__INT_STATUS__RECEIVE_OVERRUN__READ(isrReg);
            }
            else {
                cond1 = EMAC_REGS__INT_Q_STATUS__RX_USED_BIT_READ__READ(isrReg);
                cond2 = EMAC_REGS__INT_Q_STATUS__RECEIVE_OVERRUN__READ(isrReg);
            }
            if (cond1 || cond2)
            {
                events = cond1?CEDI_EV_RX_USED_READ:0;
                events |= cond2?CEDI_EV_RX_OVERRUN:0;

                vDbgMsg(DBG_GEN_MSG, 10,
                        "EMAC (0x%08X) Rx Error:0x%08X queue:%u\n",
                        (uint32_t)CEDI_PdVar(cfg).regBase, events, qNum);
                (*(CEDI_PdVar(cb).rxError))(pD, events, qNum);
            }

            /************************ HResp not OK Event ***********************/
            if (((qNum==0) &&
                    (EMAC_REGS__INT_STATUS__RESP_NOT_OK__READ(isrReg)))
                    ||
                    ((qNum>0) &&
                            (EMAC_REGS__INT_Q_STATUS__RESP_NOT_OK__READ(isrReg))))
            {
                vDbgMsg(DBG_GEN_MSG, 10,
                        "EMAC (0x%08X) HResp not OK, queue:%u\n",
                        (uint32_t)CEDI_PdVar(cfg).regBase, qNum);

                (*(CEDI_PdVar(cb).hrespError))(pD, qNum);
            }

             /************************* AN LP Page Rx ***************************/
             if ((qNum==0) &&
                     EMAC_REGS__INT_STATUS__PCS_LINK_PARTNER_PAGE_RECEIVED__READ(isrReg))
             {
                 if (CEDI_PdVar(basePageExp)) {
                     CEDI_PdVar(lpPageRx).nextPage = 0;
                     /* Read base page data */
                     emacGetLpAbilityPage(pD, &CEDI_PdVar(lpPageRx).lpPageDat.lpBasePage);
                 }
                 else {
                     CEDI_PdVar(lpPageRx).nextPage = 1;
                     /* Read next page data */
                     emacGetLpNextPage(pD, &CEDI_PdVar(lpPageRx).lpPageDat.lpNextPage);
                 }

                 vDbgMsg(DBG_GEN_MSG, 10, "EMAC (0x%08X) AN Link Partner %s Page Rx\n",
                         (uint32_t)CEDI_PdVar(cfg).regBase,
                         CEDI_PdVar(basePageExp)?"Base":"Next");
                 if (CEDI_PdVar(basePageExp))
                 {
                     /**/
                     vDbgMsg(DBG_GEN_MSG, 10, "LpNextPage: %u  LpAck: %u  FullDuplex: %u  HalfDuplex: %u  Pause Capability: %u RemoteFault: %u\n",
                             CEDI_PdVar(lpPageRx).lpPageDat.lpBasePage.ablInfo.defLpAbl.lpNextPage,
                             CEDI_PdVar(lpPageRx).lpPageDat.lpBasePage.ablInfo.defLpAbl.lpAck,
                             CEDI_PdVar(lpPageRx).lpPageDat.lpBasePage.ablInfo.defLpAbl.fullDuplex,
                             CEDI_PdVar(lpPageRx).lpPageDat.lpBasePage.ablInfo.defLpAbl.halfDuplex,
                             CEDI_PdVar(lpPageRx).lpPageDat.lpBasePage.ablInfo.defLpAbl.pauseCap,
                             CEDI_PdVar(lpPageRx).lpPageDat.lpBasePage.ablInfo.defLpAbl.remFlt);
                 }

                 /* write Null message next page as default, can be overridden in callback or later */
                 nullNp.ack2 = 0;
                 nullNp.message = 0x001;
                 nullNp.msgPage = 1;
                 nullNp.np = 0;
                 emacSetNextPageTx(pD, &nullNp);

                 (*(CEDI_PdVar(cb).lpPageRx))(pD, &CEDI_PdVar(lpPageRx));

                 CEDI_PdVar(basePageExp) = 0;
             }

            /************************* AN Complete *****************************/
            if ((qNum==0) &&
                    EMAC_REGS__INT_STATUS__PCS_AUTO_NEGOTIATION_COMPLETE__READ(isrReg))
            {
                CEDI_PdVar(basePageExp) = 1;
                CEDI_PdVar(autoNegActive) = 0;

                regVal = CPS_UncachedRead32(CEDI_RegAddr(network_status));
                CEDI_PdVar(anStatus).duplexRes =
                        EMAC_REGS__NETWORK_STATUS__MAC_FULL_DUPLEX__READ(regVal);
                CEDI_PdVar(anStatus).linkState =
                        EMAC_REGS__NETWORK_STATUS__PCS_LINK_STATE__READ(regVal);
                CEDI_PdVar(anStatus).pauseRxRes =
                        EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_RX_EN__READ(regVal);
                CEDI_PdVar(anStatus).pauseTxRes =
                        EMAC_REGS__NETWORK_STATUS__MAC_PAUSE_TX_EN__READ(regVal);

                vDbgMsg(DBG_GEN_MSG, 10, "EMAC (0x%08X) Auto-negotiation Complete\n",
                        (uint32_t)CEDI_PdVar(cfg).regBase);

                (*(CEDI_PdVar(cb).anComplete))(pD, &CEDI_PdVar(anStatus));
            }

            /*********************** Link State Change *************************/
            if ((qNum==0) && EMAC_REGS__INT_STATUS__LINK_CHANGE__READ(isrReg))
            {
                if (CEDI_PdVar(autoNegActive)) {
                    emacGetLinkStatus(pD, &linkState);
                }
                else {
                    linkState = EMAC_REGS__NETWORK_STATUS__PCS_LINK_STATE__READ(
                            CPS_UncachedRead32(CEDI_RegAddr(network_status)));
                }

                vDbgMsg(DBG_GEN_MSG, 10, "EMAC (0x%08X) Link State changed - state = %u\n",
                        (uint32_t)CEDI_PdVar(cfg).regBase, linkState);

                (*(CEDI_PdVar(cb).linkChange))(pD, linkState);
            }

             /************************ Pause Event ******************************/
             if (qNum==0) {
                 cond1 =
                         EMAC_REGS__INT_STATUS__PAUSE_FRAME_TRANSMITTED__READ(isrReg);
                 cond2 = EMAC_REGS__INT_STATUS__PAUSE_TIME_ELAPSED__READ(isrReg);
                 cond3 =
                         EMAC_REGS__INT_STATUS__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED__READ(isrReg);

                 if (cond1 || cond2 || cond3)
                 {
                     events = cond1?CEDI_EV_PAUSE_FRAME_TX:0;
                     events |= cond2?CEDI_EV_PAUSE_TIME_ZERO:0;
                     events |= cond3?CEDI_EV_PAUSE_NZ_QU_RX:0;

                     vDbgMsg(DBG_GEN_MSG, 10, "EMAC (0x%08X) Pause Event, type:0x%08X\n",
                             (uint32_t)CEDI_PdVar(cfg).regBase, events);

                     (*(CEDI_PdVar(cb).pauseEvent))(pD, events);
                 }
             }

            /***************** PTP Primary Frame Tx Event **********************/
            if (qNum==0) {
                cond1 =
                        EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_TRANSMITTED__READ(
                                isrReg);
                cond2 = EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_TRANSMITTED__READ(
                        isrReg);

                if (cond1 || cond2)
                {
                    events = cond1?CEDI_EV_PTP_TX_DLY_REQ:0;
                    events |= cond2?CEDI_EV_PTP_TX_SYNC:0;

                    vDbgMsg(DBG_GEN_MSG, 10,
                            "EMAC (0x%08X) PTP Primary Frame Tx, type:0x%08X\n",
                            (uint32_t)CEDI_PdVar(cfg).regBase, events);

                    if (0!=emacGetPtpFrameTxTime(pD, &CEDI_PdVar(ptpTime))) {
                        CEDI_PdVar(ptpTime).secsUpper = 0;
                        CEDI_PdVar(ptpTime).secsLower = 0;
                        CEDI_PdVar(ptpTime).nanosecs = 0;
                    }
                    (*(CEDI_PdVar(cb).ptpPriFrameTx))(pD, events, &CEDI_PdVar(ptpTime));
                }
            }

            /******************* PTP Peer Frame Tx Event ***********************/
            if (qNum==0) {
                cond1 =
                        EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_TRANSMITTED__READ(
                                isrReg);
                cond2 =
                        EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_TRANSMITTED__READ(
                                isrReg);

                if (cond1 || cond2)
                {
                    events = cond1?CEDI_EV_PTP_TX_PDLY_REQ:0;
                    events |= cond2?CEDI_EV_PTP_TX_PDLY_RSP:0;

                    vDbgMsg(DBG_GEN_MSG, 10,
                            "EMAC (0x%08X) PTP Peer Frame Tx, type:0x%08X\n",
                            (uint32_t)CEDI_PdVar(cfg).regBase, events);

                    if (0!=emacGetPtpPeerFrameTxTime(pD, &CEDI_PdVar(ptpTime))) {
                        CEDI_PdVar(ptpTime).secsUpper = 0;
                        CEDI_PdVar(ptpTime).secsLower = 0;
                        CEDI_PdVar(ptpTime).nanosecs = 0;
                    }
                    (*(CEDI_PdVar(cb).ptpPeerFrameTx))(pD, events, &CEDI_PdVar(ptpTime));
                }
            }

            /***************** PTP Primary Frame Rx Event **********************/
            if (qNum==0) {
                cond1 =
                        EMAC_REGS__INT_STATUS__PTP_DELAY_REQ_FRAME_RECEIVED__READ(
                                isrReg);
                cond2 = EMAC_REGS__INT_STATUS__PTP_SYNC_FRAME_RECEIVED__READ(
                        isrReg);

                if (cond1 || cond2)
                {
                    events = cond1?CEDI_EV_PTP_RX_DLY_REQ:0;
                    events |= cond2?CEDI_EV_PTP_RX_SYNC:0;

                    vDbgMsg(DBG_GEN_MSG, 10,
                            "EMAC (0x%08X) PTP Primary Frame Rx, type:0x%08X\n",
                            (uint32_t)CEDI_PdVar(cfg).regBase, events);

                    if (0!=emacGetPtpFrameRxTime(pD, &CEDI_PdVar(ptpTime))) {
                        CEDI_PdVar(ptpTime).secsUpper = 0;
                        CEDI_PdVar(ptpTime).secsLower = 0;
                        CEDI_PdVar(ptpTime).nanosecs = 0;
                    }
                    (*(CEDI_PdVar(cb).ptpPriFrameRx))(pD, events, &CEDI_PdVar(ptpTime));
                }
            }

            /******************* PTP Peer Frame Rx Event ***********************/
            if (qNum==0) {
                cond1 =
                        EMAC_REGS__INT_STATUS__PTP_PDELAY_REQ_FRAME_RECEIVED__READ(
                                isrReg);
                cond2 =
                        EMAC_REGS__INT_STATUS__PTP_PDELAY_RESP_FRAME_RECEIVED__READ(
                                isrReg);

                if (cond1 || cond2)
                {
                    events = cond1?CEDI_EV_PTP_RX_PDLY_REQ:0;
                    events |= cond2?CEDI_EV_PTP_RX_PDLY_RSP:0;

                    vDbgMsg(DBG_GEN_MSG, 10,
                            "EMAC (0x%08X) PTP Peer Frame Rx, type:0x%08X\n",
                            (uint32_t)CEDI_PdVar(cfg).regBase, events);

                    if (0!=emacGetPtpPeerFrameRxTime(pD, &CEDI_PdVar(ptpTime))) {
                        CEDI_PdVar(ptpTime).secsUpper = 0;
                        CEDI_PdVar(ptpTime).secsLower = 0;
                        CEDI_PdVar(ptpTime).nanosecs = 0;
                    }
                    (*(CEDI_PdVar(cb).ptpPeerFrameRx))(pD, events, &CEDI_PdVar(ptpTime));
                }
            }

            /************************* TSU Event *******************************/
            if (qNum==0) {
                cond1 =
                        EMAC_REGS__INT_STATUS__TSU_SECONDS_REGISTER_INCREMENT__READ(
                                isrReg);
                cond2 =
                        EMAC_REGS__INT_STATUS__TSU_TIMER_COMPARISON_INTERRUPT__READ(
                                isrReg);

                if (cond1 || cond2)
                {
                    events = cond1?CEDI_EV_TSU_SEC_INC:0;
                    events |= cond2?CEDI_EV_TSU_TIME_MATCH:0;

                    vDbgMsg(DBG_GEN_MSG, 10, "EMAC (0x%08X) TSU Event, type:0x%08X\n",
                            (uint32_t)CEDI_PdVar(cfg).regBase, events);

                    (*(CEDI_PdVar(cb).tsuEvent))(pD, events);
                }
            }

            /************************* LPI Status Change ***********************/
            if ((qNum==0) &&
                    EMAC_REGS__INT_STATUS__RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE__READ(isrReg))
            {
                vDbgMsg(DBG_GEN_MSG, 10, "EMAC (0x%08X) LPI Status change Event\n",

                        (uint32_t)CEDI_PdVar(cfg).regBase);

                (*(CEDI_PdVar(cb).lpiStatus))(pD);
            }

            /************************* Wake On LAN Event ***********************/
            if ((qNum==0) && EMAC_REGS__INT_STATUS__WOL_INTERRUPT__READ(isrReg))
            {
                vDbgMsg(DBG_GEN_MSG, 10, "EMAC (0x%08X) Wake on LAN Event\n",
                        (uint32_t)CEDI_PdVar(cfg).regBase);

                (*(CEDI_PdVar(cb).wolEvent))(pD);
            }

            /****************** External Input Interrupt Event *****************/
            if ((qNum==0) && EMAC_REGS__INT_STATUS__EXTERNAL_INTERRUPT__READ(isrReg))
            {
                vDbgMsg(DBG_GEN_MSG, 10, "EMAC (0x%08X) External Input Interrupt\n",
                        (uint32_t)CEDI_PdVar(cfg).regBase);

                (*(CEDI_PdVar(cb).extInpIntr))(pD);
            }

        }  /* for qNum */
    }

    if (handled)
        return 0;
    else
        return ECANCELED;
}

/**
 * Enable or disable the specified interrupts.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] events
 *    OR'd combination of bit-flags selecting the events to
 *    be enabled or disabled
 * @param[in] enable if equal 1 enable the events, if 0 then disable
 * @param[in] queueNum between 0 and config->rxQs-1, or =CEDI_ALL_QUEUES -
 *    number of Tx or Rx priority queue, relevant to some of
 *    Tx and Rx events:
 *    CEDI_EV_TX_COMPLETE, CEDI_EV_TX_FR_CORRUPT,
 *    CEDI_EV_RX_COMPLETE, CEDI_EV_RX_USED_READ, CEDI_EV_RX_OVERRUN,
 *    CEDI_EV_HRESP_NOT_OK
 *    Must be =0 or CEDI_ALL_QUEUES for other events.
 *    To dis/enable on all available Qs, set queueNum to CEDI_ALL_QUEUES and
 *    set events to CEDI_EVSET_ALL_Q0_EVENTS.
 * @return EINVAL for invalid pD pointer or enable
 * @return EINVAL for invalid queueNum
 * @return EINVAL for invalid event,
 *    e.g. CEDI_EV_PAUSE_FRAME_TX when queueNum = 2
 * @return EINVAL for NULL callback for event to be enabled
 * @return 0 for success
 */

uint32_t emacSetEventEnable(void *pD, uint32_t events, uint8_t enable,
        uint8_t queueNum)
{
#define CEDI_ENABLE_INT(Q) if ((queueNum==Q) || (queueNum==CEDI_ALL_QUEUES)) \
                    CPS_UncachedWrite32(CEDI_RegAddr(int_q##Q##_enable), regVal);

#define CEDI_DISABLE_INT(Q) if ((queueNum==Q) || (queueNum==CEDI_ALL_QUEUES))\
                    CPS_UncachedWrite32(CEDI_RegAddr(int_q##Q##_disable), regVal);

    uint32_t regVal, paramErr;

    if (pD==NULL) {
        vDbgMsg(DBG_GEN_MSG, 5, "%s", "*** Error: NULL pD parameter\n");
        return EINVAL;
    }
    if ((queueNum>=CEDI_PdVar(numQs)) && (queueNum!=CEDI_ALL_QUEUES)) {
        vDbgMsg(DBG_GEN_MSG, 5,
                "*** Error: Invalid parameter, queueNum: %u\n", queueNum);
        return EINVAL;
    }
    if (enable>1) {
        vDbgMsg(DBG_GEN_MSG, 5,
                "*** Error: Invalid parameter, enable: %u\n", enable);
        return EINVAL;
    }
    /* test for invalid events */
    if ((events &(~(((queueNum==0)||(queueNum==CEDI_ALL_QUEUES))
                    ?CEDI_EVSET_ALL_Q0_EVENTS:CEDI_EVSET_ALL_QN_EVENTS)))!=0) {
        vDbgMsg(DBG_GEN_MSG, 5,
                "*** Error: Invalid parameter, events: 0x%08X (queueNum=%u)\n",
                events, queueNum);
        return EINVAL;
    }

    regVal = 0;

    if (events)
    {
        if (enable) {
            paramErr=callbacksNullCheck(pD, events);
            if (0 != paramErr) {
                vDbgMsg(DBG_GEN_MSG, 5,
                    "*** Error: Callback =NULL for event(s) 0x%08X\n", paramErr);
                return EINVAL;
            }

            if ((queueNum==0) || (queueNum==CEDI_ALL_QUEUES)) {
                regVal = 0;
                if (events & CEDI_EV_MAN_FRAME)
                    EMAC_REGS__INT_ENABLE__ENABLE_MANAGEMENT_DONE_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_RX_COMPLETE)
                    EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_RX_USED_READ)
                    EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_USED_BIT_READ_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_TX_USED_READ)
                    EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_TX_UNDERRUN)
                    EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__SET
                    (regVal);

                if (events & CEDI_EV_TX_RETRY_EX_LATE_COLL)
                    EMAC_REGS__INT_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET
                    (regVal);

                if (events & CEDI_EV_PCS_LINK_CHANGE_DET)
                    EMAC_REGS__INT_ENABLE__ENABLE_LINK_CHANGE_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_PCS_AN_COMPLETE)
                    EMAC_REGS__INT_ENABLE__ENABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__SET
                    (regVal);

                if (events & CEDI_EV_PCS_LP_PAGE_RX)
                    EMAC_REGS__INT_ENABLE__ENABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__SET(regVal);

                if (events & CEDI_EV_TSU_SEC_INC)
                    EMAC_REGS__INT_ENABLE__ENABLE_TSU_SECONDS_REGISTER_INCREMENT__SET(regVal);

                if (events & CEDI_EV_TSU_TIME_MATCH)
                    EMAC_REGS__INT_ENABLE__ENABLE_TSU_TIMER_COMPARISON_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_TX_FR_CORRUPT)
                    EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET
                    (regVal);

                if (events & CEDI_EV_TX_COMPLETE)
                    EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_RX_OVERRUN)
                    EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_OVERRUN_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_HRESP_NOT_OK)
                    EMAC_REGS__INT_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_PAUSE_NZ_QU_RX)
                    EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__SET
                    (regVal);

                if (events & CEDI_EV_PAUSE_TIME_ZERO)
                    EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_TIME_ZERO_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_PAUSE_FRAME_TX)
                    EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_EXT_INTR)
                    EMAC_REGS__INT_ENABLE__ENABLE_EXTERNAL_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_PTP_RX_DLY_REQ)
                    EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_RECEIVED__SET(regVal);

                if (events & CEDI_EV_PTP_RX_SYNC)
                    EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_RECEIVED__SET(regVal);

                if (events & CEDI_EV_PTP_TX_DLY_REQ)
                    EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__SET(regVal);

                if (events & CEDI_EV_PTP_TX_SYNC)
                    EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_TRANSMITTED__SET(regVal);

                if (events & CEDI_EV_PTP_RX_PDLY_REQ)
                    EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__SET(regVal);

                if (events & CEDI_EV_PTP_RX_PDLY_RSP)
                    EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__SET(regVal);

                if (events & CEDI_EV_PTP_TX_PDLY_REQ)
                    EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__SET(regVal);

                if (events & CEDI_EV_PTP_TX_PDLY_RSP)
                    EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__SET(regVal);

                if (events & CEDI_EV_LPI_CH_RX)
                    EMAC_REGS__INT_ENABLE__ENABLE_RX_LPI_INDICATION_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_WOL_RX)
                    EMAC_REGS__INT_ENABLE__ENABLE_WOL_EVENT_RECEIVED_INTERRUPT__SET(regVal);

                CPS_UncachedWrite32(CEDI_RegAddr(int_enable), regVal);
            }
            if (queueNum>0) {
                regVal = 0;
                if (events & CEDI_EV_RX_COMPLETE)
                    EMAC_REGS__INT_Q_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_RX_USED_READ)
                    EMAC_REGS__INT_Q_ENABLE__ENABLE_RX_USED_BIT_READ_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_TX_RETRY_EX_LATE_COLL)
                    EMAC_REGS__INT_Q_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET
                    (regVal);

                if (events & CEDI_EV_TX_FR_CORRUPT)
                    EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET
                    (regVal);

                if (events & CEDI_EV_TX_COMPLETE)
                    EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_HRESP_NOT_OK)
                    EMAC_REGS__INT_Q_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__SET(regVal);


                /* write to interrupt enable register */
                CEDI_ENABLE_INT(1);
                CEDI_ENABLE_INT(2);
/*              // Three queues are supported
                CEDI_ENABLE_INT(3);
                CEDI_ENABLE_INT(4);
                CEDI_ENABLE_INT(5);
                CEDI_ENABLE_INT(6);
                CEDI_ENABLE_INT(7);
                CEDI_ENABLE_INT(8);
                CEDI_ENABLE_INT(9);
                CEDI_ENABLE_INT(10);
                CEDI_ENABLE_INT(11);
                CEDI_ENABLE_INT(12);
                CEDI_ENABLE_INT(13);
                CEDI_ENABLE_INT(14);
                CEDI_ENABLE_INT(15);
*/
            }
        }
        else  /* enable==0, i.e. disabling specified events */
        {
            if ((queueNum==0) || (queueNum==CEDI_ALL_QUEUES)) {
                regVal = 0;
                if (events & CEDI_EV_MAN_FRAME)
                    EMAC_REGS__INT_DISABLE__DISABLE_MANAGEMENT_DONE_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_RX_COMPLETE)
                    EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_RX_USED_READ)
                    EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_USED_BIT_READ_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_TX_USED_READ)
                    EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_TX_UNDERRUN)
                    EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__SET
                    (regVal);

                if (events & CEDI_EV_TX_RETRY_EX_LATE_COLL)
                    EMAC_REGS__INT_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET
                    (regVal);

                if (events & CEDI_EV_PCS_LINK_CHANGE_DET)
                    EMAC_REGS__INT_DISABLE__DISABLE_LINK_CHANGE_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_PCS_AN_COMPLETE)
                    EMAC_REGS__INT_DISABLE__DISABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__SET
                    (regVal);

                if (events & CEDI_EV_PCS_LP_PAGE_RX)
                    EMAC_REGS__INT_DISABLE__DISABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__SET(regVal);

                if (events & CEDI_EV_TSU_SEC_INC)
                    EMAC_REGS__INT_DISABLE__DISABLE_TSU_SECONDS_REGISTER_INCREMENT__SET(regVal);

                if (events & CEDI_EV_TSU_TIME_MATCH)
                    EMAC_REGS__INT_DISABLE__DISABLE_TSU_TIMER_COMPARISON_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_TX_FR_CORRUPT)
                    EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET
                    (regVal);

                if (events & CEDI_EV_TX_COMPLETE)
                    EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_RX_OVERRUN)
                    EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_OVERRUN_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_HRESP_NOT_OK)
                    EMAC_REGS__INT_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_PAUSE_NZ_QU_RX)
                    EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__SET
                    (regVal);

                if (events & CEDI_EV_PAUSE_TIME_ZERO)
                    EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_TIME_ZERO_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_PAUSE_FRAME_TX)
                    EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_EXT_INTR)
                    EMAC_REGS__INT_DISABLE__DISABLE_EXTERNAL_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_PTP_RX_DLY_REQ)
                    EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_RECEIVED__SET(regVal);

                if (events & CEDI_EV_PTP_RX_SYNC)
                    EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_RECEIVED__SET(regVal);

                if (events & CEDI_EV_PTP_TX_DLY_REQ)
                    EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__SET(regVal);

                if (events & CEDI_EV_PTP_TX_SYNC)
                    EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_TRANSMITTED__SET(regVal);

                if (events & CEDI_EV_PTP_RX_PDLY_REQ)
                    EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__SET(regVal);

                if (events & CEDI_EV_PTP_RX_PDLY_RSP)
                    EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__SET(regVal);

                if (events & CEDI_EV_PTP_TX_PDLY_REQ)
                    EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__SET(regVal);

                if (events & CEDI_EV_PTP_TX_PDLY_RSP)
                    EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__SET(regVal);

                if (events & CEDI_EV_LPI_CH_RX)
                    EMAC_REGS__INT_DISABLE__DISABLE_RX_LPI_INDICATION_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_WOL_RX)
                    EMAC_REGS__INT_DISABLE__DISABLE_WOL_EVENT_RECEIVED_INTERRUPT__SET(regVal);

                CPS_UncachedWrite32(CEDI_RegAddr(int_disable), regVal);
            }
            if (queueNum>0) {
                regVal = 0;
                if (events & CEDI_EV_RX_COMPLETE)
                    EMAC_REGS__INT_Q_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_RX_USED_READ)
                    EMAC_REGS__INT_Q_DISABLE__DISABLE_RX_USED_BIT_READ_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_TX_RETRY_EX_LATE_COLL)
                    EMAC_REGS__INT_Q_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET
                    (regVal);

                if (events & CEDI_EV_TX_FR_CORRUPT)
                    EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET
                    (regVal);

                if (events & CEDI_EV_TX_COMPLETE)
                    EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(regVal);

                if (events & CEDI_EV_HRESP_NOT_OK)
                    EMAC_REGS__INT_Q_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__SET(regVal);


                /* write to interrupt disable register */
                CEDI_DISABLE_INT(1);
                CEDI_DISABLE_INT(2);
/*              // Three queues are supported
                CEDI_DISABLE_INT(3);
                CEDI_DISABLE_INT(4);
                CEDI_DISABLE_INT(5);
                CEDI_DISABLE_INT(6);
                CEDI_DISABLE_INT(7);
                CEDI_DISABLE_INT(8);
                CEDI_DISABLE_INT(9);
                CEDI_DISABLE_INT(10);
                CEDI_DISABLE_INT(11);
                CEDI_DISABLE_INT(12);
                CEDI_DISABLE_INT(13);
                CEDI_DISABLE_INT(14);
                CEDI_DISABLE_INT(15);
*/
            }
        }
    }
    return 0;
}

uint32_t emacGetEventEnable(void *pD, uint8_t queueNum, uint32_t *event)
{
#define CEDI_READ_INT_MASK_CASE(Q) case Q:\
     regVal = ~CPS_UncachedRead32(CEDI_RegAddr(int_q##Q##_mask)); break;

    uint32_t ret = 0;
    uint32_t regVal = 0;

    if ((pD==NULL)||(event==NULL))
      return EINVAL;

    if (queueNum>=CEDI_PdVar(numQs))
        return EINVAL;

    if (queueNum==0) {
        regVal = ~CPS_UncachedRead32(CEDI_RegAddr(int_mask));
        if (regVal) {
            if (EMAC_REGS__INT_MASK__MANAGEMENT_DONE_INTERRUPT_MASK__READ(regVal))
                ret |= CEDI_EV_MAN_FRAME;

            if (EMAC_REGS__INT_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__READ(regVal))
                ret |= CEDI_EV_RX_COMPLETE;

            if (EMAC_REGS__INT_MASK__RECEIVE_USED_BIT_READ_INTERRUPT_MASK__READ(
                    regVal))
                ret |= CEDI_EV_RX_USED_READ;

            if (EMAC_REGS__INT_MASK__TRANSMIT_USED_BIT_READ_INTERRUPT_MASK__READ(
                    regVal))
                ret |= CEDI_EV_TX_USED_READ;

            if (EMAC_REGS__INT_MASK__TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT_MASK__READ(
                    regVal))
                ret |= CEDI_EV_TX_UNDERRUN;

            if (EMAC_REGS__INT_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_MASK__READ(
                    regVal))
                ret |= CEDI_EV_TX_RETRY_EX_LATE_COLL;

            if (EMAC_REGS__INT_MASK__LINK_CHANGE_INTERRUPT_MASK__READ(regVal))
                ret |= CEDI_EV_PCS_LINK_CHANGE_DET;

            if (EMAC_REGS__INT_MASK__PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT_MASK__READ(
                    regVal))
                ret |= CEDI_EV_PCS_AN_COMPLETE;

            if (EMAC_REGS__INT_MASK__PCS_LINK_PARTNER_PAGE_MASK__READ(regVal))
                ret |= CEDI_EV_PCS_LP_PAGE_RX;

            if (EMAC_REGS__INT_MASK__TSU_SECONDS_REGISTER_INCREMENT_MASK__READ(
                    regVal))
                ret |= CEDI_EV_TSU_SEC_INC;

            if (EMAC_REGS__INT_MASK__TSU_TIMER_COMPARISON_MASK__READ(regVal))
                ret |= CEDI_EV_TSU_TIME_MATCH;

            if (EMAC_REGS__INT_MASK__AMBA_ERROR_INTERRUPT_MASK__READ(regVal))
                ret |= CEDI_EV_TX_FR_CORRUPT;

            if (EMAC_REGS__INT_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__READ(regVal))
                ret |= CEDI_EV_TX_COMPLETE;

            if (EMAC_REGS__INT_MASK__RECEIVE_OVERRUN_INTERRUPT_MASK__READ(regVal))
                ret |= CEDI_EV_RX_OVERRUN;

            if (EMAC_REGS__INT_MASK__RESP_NOT_OK_INTERRUPT_MASK__READ(regVal))
                ret |= CEDI_EV_HRESP_NOT_OK;

            if (EMAC_REGS__INT_MASK__PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT_MASK__READ(
                    regVal))
                ret |= CEDI_EV_PAUSE_NZ_QU_RX;

            if (EMAC_REGS__INT_MASK__PAUSE_TIME_ZERO_INTERRUPT_MASK__READ(regVal))
                ret |= CEDI_EV_PAUSE_TIME_ZERO;

            if (EMAC_REGS__INT_MASK__PAUSE_FRAME_TRANSMITTED_INTERRUPT_MASK__READ(
                    regVal))
                ret |= CEDI_EV_PAUSE_FRAME_TX;

            if (EMAC_REGS__INT_MASK__EXTERNAL_INTERRUPT_MASK__READ(regVal))
                ret |= CEDI_EV_EXT_INTR;

            if (EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_RECEIVED_MASK__READ(regVal))
                ret |= CEDI_EV_PTP_RX_DLY_REQ;

            if (EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_RECEIVED_MASK__READ(regVal))
                ret |= CEDI_EV_PTP_RX_SYNC;

            if (EMAC_REGS__INT_MASK__PTP_DELAY_REQ_FRAME_TRANSMITTED_MASK__READ(
                    regVal))
                ret |= CEDI_EV_PTP_TX_DLY_REQ;

            if (EMAC_REGS__INT_MASK__PTP_SYNC_FRAME_TRANSMITTED_MASK__READ(regVal))
                ret |= CEDI_EV_PTP_TX_SYNC;

            if (EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_RECEIVED_MASK__READ(
                    regVal))
                ret |= CEDI_EV_PTP_RX_PDLY_REQ;

            if (EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_RECEIVED_MASK__READ(
                    regVal))
                ret |= CEDI_EV_PTP_RX_PDLY_RSP;

            if (EMAC_REGS__INT_MASK__PTP_PDELAY_REQ_FRAME_TRANSMITTED_MASK__READ(
                    regVal))
                ret |= CEDI_EV_PTP_TX_PDLY_REQ;

            if (EMAC_REGS__INT_MASK__PTP_PDELAY_RESP_FRAME_TRANSMITTED_MASK__READ(
                    regVal))
                ret |= CEDI_EV_PTP_TX_PDLY_RSP;

            if (EMAC_REGS__INT_MASK__RX_LPI_INDICATION_MASK__READ(regVal))
                ret |= CEDI_EV_LPI_CH_RX;

            if (EMAC_REGS__INT_MASK__WOL_EVENT_RECEIVED_MASK__READ(regVal))
                ret |= CEDI_EV_WOL_RX;
        }
    }
    else
    {
        switch(queueNum) {
            CEDI_READ_INT_MASK_CASE(1);
            CEDI_READ_INT_MASK_CASE(2);
/*          // Three queues are supported
            CEDI_READ_INT_MASK_CASE(3);
            CEDI_READ_INT_MASK_CASE(4);
            CEDI_READ_INT_MASK_CASE(5);
            CEDI_READ_INT_MASK_CASE(6);
            CEDI_READ_INT_MASK_CASE(7);
            CEDI_READ_INT_MASK_CASE(8);
            CEDI_READ_INT_MASK_CASE(9);
            CEDI_READ_INT_MASK_CASE(10);
            CEDI_READ_INT_MASK_CASE(11);
            CEDI_READ_INT_MASK_CASE(12);
            CEDI_READ_INT_MASK_CASE(13);
            CEDI_READ_INT_MASK_CASE(14);
            CEDI_READ_INT_MASK_CASE(15);
*/
        }

        if (regVal) {
            if (EMAC_REGS__INT_Q_MASK__RECEIVE_COMPLETE_INTERRUPT_MASK__READ(
                    regVal))
                ret |= CEDI_EV_RX_COMPLETE;

            if (EMAC_REGS__INT_Q_MASK__RX_USED_INTERRUPT_MASK__READ(
                    regVal))
                ret |= CEDI_EV_RX_USED_READ;

            if (EMAC_REGS__INT_Q_MASK__RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT_MASK__READ(
                    regVal))
                ret |= CEDI_EV_TX_RETRY_EX_LATE_COLL;

            if (EMAC_REGS__INT_Q_MASK__AMBA_ERROR_INTERRUPT_MASK__READ(regVal))
                ret |= CEDI_EV_TX_FR_CORRUPT;

            if (EMAC_REGS__INT_Q_MASK__TRANSMIT_COMPLETE_INTERRUPT_MASK__READ(
                    regVal))
                ret |= CEDI_EV_TX_COMPLETE;

            if (EMAC_REGS__INT_Q_MASK__RESP_NOT_OK_INTERRUPT_MASK__READ(regVal))
                ret |= CEDI_EV_HRESP_NOT_OK;
        }
    }

    (*event) = ret;
    return 0;
}

uint32_t emacSetIntrptModerate(void *pD, uint8_t txIntDelay,
                                        uint8_t rxIntDelay)
{
    uint32_t reg;
    if (pD==NULL) return EINVAL;
    if ((CEDI_PdVar(hwCfg).intrpt_mod==0) && (txIntDelay || rxIntDelay))
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(int_moderation));
    EMAC_REGS__INT_MODERATION__TX_INT_MODERATION__MODIFY(reg, txIntDelay);
    EMAC_REGS__INT_MODERATION__RX_INT_MODERATION__MODIFY(reg, rxIntDelay);
    CPS_UncachedWrite32(CEDI_RegAddr(int_moderation), reg);
    return 0;
}

uint32_t emacGetIntrptModerate(void *pD, uint8_t *txIntDelay,
                                        uint8_t *rxIntDelay)
{
    uint32_t reg;
    if ((pD==NULL) || (txIntDelay==NULL) || (rxIntDelay==NULL))
        return EINVAL;

    if (CEDI_PdVar(hwCfg).intrpt_mod==0) {
        *txIntDelay = 0;
        *rxIntDelay = 0;
    } else {
        reg = CPS_UncachedRead32(CEDI_RegAddr(int_moderation));
        *txIntDelay=EMAC_REGS__INT_MODERATION__TX_INT_MODERATION__READ(reg);
        *rxIntDelay=EMAC_REGS__INT_MODERATION__RX_INT_MODERATION__READ(reg);
    }
    return 0;
}

uint32_t emacSetIfSpeed(void *pD, CEDI_IfSpeed speedSel)
{
    uint32_t reg;

//    vDbgMsg(DBG_GEN_MSG, 10, "%s entered:  speedSel = %u\n",
//            __func__, speedSel);

    if (pD==NULL) return EINVAL;
//yots    if ((speedSel<CEDI_SPEED_10M) || (speedSel>CEDI_SPEED_1000M))
//yots        return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    switch (speedSel) {
    case CEDI_SPEED_10M:
        EMAC_REGS__NETWORK_CONFIG__SPEED__CLR(reg);
        EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__CLR(reg);
        break;
    case CEDI_SPEED_100M:
        EMAC_REGS__NETWORK_CONFIG__SPEED__SET(reg);
        EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__CLR(reg);
        break;
    case CEDI_SPEED_1000M:
        EMAC_REGS__NETWORK_CONFIG__SPEED__CLR(reg);
        EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__SET(reg);
        break;
    }
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
    return 0;
}

uint32_t emacGetIfSpeed(void *pD, CEDI_IfSpeed *speedSel)
{
    uint32_t reg;

    if ((pD==NULL)||(speedSel==NULL))
      return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__READ(reg))
        *speedSel = CEDI_SPEED_1000M;
    else if (EMAC_REGS__NETWORK_CONFIG__SPEED__READ(reg))
        *speedSel = CEDI_SPEED_100M;
    else
        *speedSel = CEDI_SPEED_10M;

    return 0;
}

void emacSetJumboFramesRx(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return;
    if (enable>1) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

uint32_t emacGetJumboFramesRx(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;

    *enable=EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

uint32_t emacSetJumboFrameRxMaxLen(void *pD, uint16_t length)
{
    uint32_t reg;
    uint8_t enabled;
    if (pD==NULL) return EINVAL;
    if (length>MAX_JUMBO_FRAME_LENGTH)
        return EINVAL;

    emacGetJumboFramesRx(pD, &enabled);
    reg = CPS_UncachedRead32(CEDI_RegAddr(jumbo_max_length));
    if (enabled)
        emacSetJumboFramesRx(pD, 0);
    EMAC_REGS__JUMBO_MAX_LENGTH__JUMBO_MAX_LENGTH__MODIFY(reg, length);
    CPS_UncachedWrite32(CEDI_RegAddr(jumbo_max_length), reg);
    if (enabled)
        emacSetJumboFramesRx(pD, 1);
    return 0;
}

uint32_t emacGetJumboFrameRxMaxLen(void *pD, uint16_t *length)
{
    if ((pD==NULL)||(length==NULL))
      return EINVAL;

    *length=EMAC_REGS__JUMBO_MAX_LENGTH__JUMBO_MAX_LENGTH__READ(
            CPS_UncachedRead32(CEDI_RegAddr(jumbo_max_length)));

    return 0;
}

void emacSetUniDirEnable(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return;
    if (enable>1) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

uint32_t emacGetUniDirEnable(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;
    *enable= EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

uint32_t emacSetTxChecksumOffload(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return EINVAL;
    if (enable>1) return EINVAL;
    if (!CEDI_PdVar(hwCfg).tx_pkt_buffer)
        return EINVAL;
    vDbgMsg(DBG_GEN_MSG, 10, "%s entered: enable = %u\n",
                                __func__, enable);

    reg = CPS_UncachedRead32(CEDI_RegAddr(dma_config));
    if (enable)
        EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__SET(reg);
    else
        EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(dma_config), reg);
    return 0;
}

uint32_t emacGetTxChecksumOffload(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;
    *enable= EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__READ(
            CPS_UncachedRead32(CEDI_RegAddr(dma_config)));

    return 0;
}

uint32_t emacSetRxBufOffset(void *pD, uint8_t offset)
{
    uint32_t reg;
    if (pD==NULL) return EINVAL;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (offset>3) return EINVAL;
    EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__MODIFY(reg, offset);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
    return 0;
}

uint32_t emacGetRxBufOffset(void *pD, uint8_t *offset)
{
    if ((pD==NULL)||(offset==NULL))
      return EINVAL;
    *offset= EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

void emacSet1536ByteFramesRx(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return;
    if (enable>1) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

uint32_t emacGet1536ByteFramesRx(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;
    *enable= EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

void emacSetRxChecksumOffload(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return;
    if (enable>1) return;
    vDbgMsg(DBG_GEN_MSG, 10, "%s entered: enable = %u\n",
                                __func__, enable);

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

uint32_t emacGetRxChecksumOffload(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;
    *enable= EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

void emacSetFcsRemove(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return;
    if (enable>1) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

uint32_t emacGetFcsRemove(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;
    *enable= EMAC_REGS__NETWORK_CONFIG__FCS_REMOVE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

uint32_t emacSetRxDmaDataAddrMask(void *pD, uint8_t enableBit,
        uint8_t bitValues)
{
    uint32_t reg = 0;
    if (pD==NULL) return EINVAL;
    if ((enableBit>0xf) || (bitValues>0xf)) return EINVAL;

    EMAC_REGS__DMA_ADDR_OR_MASK__MASK_ENABLE__MODIFY(reg, enableBit);
    EMAC_REGS__DMA_ADDR_OR_MASK__MASK_VALUE__MODIFY(reg, bitValues);
    CPS_UncachedWrite32(CEDI_RegAddr(dma_addr_or_mask), reg);
    return 0;
}

uint32_t emacGetRxDmaDataAddrMask(void *pD, uint8_t *enableBit,
        uint8_t *bitValues)
{
    uint32_t reg;
    if (pD==NULL || !enableBit || !bitValues) return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(dma_addr_or_mask));
    *enableBit = EMAC_REGS__DMA_ADDR_OR_MASK__MASK_ENABLE__READ(reg);
    *bitValues = EMAC_REGS__DMA_ADDR_OR_MASK__MASK_VALUE__READ(reg);
    return 0;
}

void emacSetRxBadPreamble(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return;
    if (enable>1) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__NSP_CHANGE__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__NSP_CHANGE__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

uint32_t emacGetRxBadPreamble(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;
    *enable= EMAC_REGS__NETWORK_CONFIG__NSP_CHANGE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

void emacSetFullDuplex(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return;
    if (enable>1) return;
    vDbgMsg(DBG_GEN_MSG, 10, "%s entered: set to %s duplex\n",
            __func__, enable?"full":"half");

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

uint32_t emacGetFullDuplex(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;

    *enable=EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

void emacSetIgnoreFcsRx(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return;
    if (enable>1) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

uint32_t emacGetIgnoreFcsRx(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;
    *enable= EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

void emacSetRxHalfDuplexInTx(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return;
    if (enable>1) return;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

uint32_t emacGetRxHalfDuplexInTx(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;

    *enable= EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}


uint32_t emacGetIfCapabilities(void *pD, uint32_t *cap)
{
    if ((pD==NULL)||(cap==NULL))
        return EINVAL;

    *cap = 0;

// TODO: temporary detection based on header-data splitting until get LSO-related define
#ifdef EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__READ
    *cap |= CEDI_CAP_LSO;
#endif
// TODO: RSC, RSS,...

    return EOK;
}

/******************************** Pause Control ******************************/

void emacSetPauseEnable(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return;
    if (enable>1) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

uint32_t emacGetPauseEnable(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;
    *enable= EMAC_REGS__NETWORK_CONFIG__PAUSE_ENABLE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

void emacTxPauseFrame(void *pD)
{
    uint32_t reg;
    if (pD==NULL) return;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_REQ__SET(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);
    return;
}

void emacTxZeroQPause(void *pD)
{
    uint32_t reg;
    if (pD==NULL) return;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    EMAC_REGS__NETWORK_CONTROL__TX_PAUSE_FRAME_ZERO__SET(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);
    return;
}

uint32_t emacGetRxPauseQuantum(void *pD, uint16_t *value)
{
    if ((pD==NULL)||(value==NULL))
      return EINVAL;

    *value = EMAC_REGS__PAUSE_TIME__QUANTUM__READ(
            CPS_UncachedRead32(CEDI_RegAddr(pause_time)));
    return 0;
}

uint32_t emacSetTxPauseQuantum(void *pD, uint16_t value, uint8_t qpriority)
{
    uint32_t reg;
    if (pD==NULL) return EINVAL;
    if (qpriority >= CEDI_QUANTA_PRIORITY_MAX) return EINVAL;
    if ((CEDI_PdVar(hwCfg).pfc_multi_quantum==0)
                           && (qpriority>0)) {
        return ENOTSUP;
    }

    switch (qpriority) {
    default: /* default */
    case 0:
        reg = CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum));
        EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM__MODIFY(reg, value);
        CPS_UncachedWrite32(CEDI_RegAddr(tx_pause_quantum), reg);
        break;
    case 1:
        reg = CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum));
        EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM_P1__MODIFY(reg, value);
        CPS_UncachedWrite32(CEDI_RegAddr(tx_pause_quantum), reg);
        break;
    case 2:
        reg = CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum1));
        EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P2__MODIFY(reg, value);
        CPS_UncachedWrite32(CEDI_RegAddr(tx_pause_quantum1), reg);
        break;
    case 3:
        reg = CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum1));
        EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P3__MODIFY(reg, value);
        CPS_UncachedWrite32(CEDI_RegAddr(tx_pause_quantum1), reg);
        break;
    case 4:
        reg = CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum2));
        EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P4__MODIFY(reg, value);
        CPS_UncachedWrite32(CEDI_RegAddr(tx_pause_quantum2), reg);
        break;
    case 5:
        reg = CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum2));
        EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P5__MODIFY(reg, value);
        CPS_UncachedWrite32(CEDI_RegAddr(tx_pause_quantum2), reg);
        break;
    case 6:
        reg = CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum3));
        EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P6__MODIFY(reg, value);
        CPS_UncachedWrite32(CEDI_RegAddr(tx_pause_quantum3), reg);
        break;
    case 7:
        reg = CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum3));
        EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P7__MODIFY(reg, value);
        CPS_UncachedWrite32(CEDI_RegAddr(tx_pause_quantum3), reg);
        break;
    }
    return EOK;
}

uint32_t emacGetTxPauseQuantum(void *pD, uint16_t *value, uint8_t qpriority)
{
    if ((pD==NULL)||(value==NULL))
      return EINVAL;
    if ((CEDI_PdVar(hwCfg).pfc_multi_quantum==0)
                        && (qpriority>0)) {
        return ENOTSUP;
    }
    if (qpriority >= CEDI_QUANTA_PRIORITY_MAX)
      return EINVAL;

    switch(qpriority){
    default: /* default */
    case 0:
        *value= EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM__READ(
                    CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum)));
        break;
    case 1:
        *value= EMAC_REGS__TX_PAUSE_QUANTUM__QUANTUM_P1__READ(
                    CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum)));
        break;
    case 2:
        *value= EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P2__READ(
                    CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum1)));
        break;
    case 3:
        *value= EMAC_REGS__TX_PAUSE_QUANTUM1__QUANTUM_P3__READ(
                    CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum1)));
        break;
    case 4:
        *value= EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P4__READ(
                    CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum2)));
        break;
    case 5:
        *value= EMAC_REGS__TX_PAUSE_QUANTUM2__QUANTUM_P5__READ(
                    CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum2)));
        break;
    case 6:
        *value= EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P6__READ(
                    CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum3)));
        break;
    case 7:
        *value= EMAC_REGS__TX_PAUSE_QUANTUM3__QUANTUM_P7__READ(
                    CPS_UncachedRead32(CEDI_RegAddr(tx_pause_quantum3)));
        break;
    }

    return EOK;
}

void emacSetCopyPauseDisable(void *pD, uint8_t disable)
{
    uint32_t reg;
    if (pD==NULL) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (disable)
        EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

uint32_t emacGetCopyPauseDisable(void *pD, uint8_t *disable)
{
    if ((pD==NULL)||(disable==NULL))
      return EINVAL;
    *disable= EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

void emacSetPfcPriorityBasedPauseRx(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return;
    if (enable>1) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    if (enable)
        EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__SET(reg);
    else
        EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);
}

uint32_t emacGetPfcPriorityBasedPauseRx(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;
    *enable = EMAC_REGS__NETWORK_CONTROL__PFC_ENABLE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_control)));

    return 0;
}

uint32_t emacTxPfcPriorityBasedPause(void *pD)
{
    uint8_t fullDup = 1;
    uint32_t reg;

    if (pD==NULL)
        return EINVAL;
    emacGetFullDuplex(pD, &fullDup);
    if ((!fullDup) || !emacGetTxEnabled(pD))
        return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    EMAC_REGS__NETWORK_CONTROL__TRANSMIT_PFC_PRIORITY_BASED_PAUSE_FRAME__SET(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);
    return 0;
}

uint32_t emacSetTxPfcPauseFrameFields(void *pD, uint8_t priEnVector,
            uint8_t zeroQSelVector)
{
    uint32_t reg = 0;
    if (pD==NULL) return EINVAL;

    EMAC_REGS__TX_PFC_PAUSE__VECTOR_ENABLE__MODIFY(reg, priEnVector);
    EMAC_REGS__TX_PFC_PAUSE__VECTOR__MODIFY(reg, zeroQSelVector);
    CPS_UncachedWrite32(CEDI_RegAddr(tx_pfc_pause), reg);
    return 0;
}

uint32_t emacGetTxPfcPauseFrameFields(void *pD, uint8_t *priEnVector,
            uint8_t *zeroQSelVector)
{
    uint32_t reg = 0;
    if ((pD==NULL) || (priEnVector==NULL) || (zeroQSelVector==NULL))
      return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(tx_pfc_pause));
    *priEnVector = EMAC_REGS__TX_PFC_PAUSE__VECTOR_ENABLE__READ(reg);
    *zeroQSelVector = EMAC_REGS__TX_PFC_PAUSE__VECTOR__READ(reg);
    return 0;
}

uint32_t emacSetEnableMultiPfcPauseQuantum(void *pD, uint8_t enMultiPfcPause)
{
    uint32_t regVal = 0;
    if (pD==NULL) return EINVAL;
    if (enMultiPfcPause>1) return EINVAL;

    if ((CEDI_PdVar(hwCfg).pfc_multi_quantum==0) && (enMultiPfcPause==1))
        return ENOTSUP;

    regVal = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__MODIFY(regVal,enMultiPfcPause);

    CPS_UncachedWrite32(CEDI_RegAddr(network_control), regVal);
    return 0;
}

uint32_t emacGetEnableMultiPfcPauseQuantum(void *pD, uint8_t *enMultiPfcPause)
{
    uint32_t regVal = 0;
    if ((pD==NULL) || (enMultiPfcPause==NULL))
      return EINVAL;

    regVal = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    *enMultiPfcPause = EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__READ(regVal);
    return 0;
}


/****************************** Loopback Control *****************************/

/**
 * Enable or disable loop back mode in the EMAC.
 * @param pD - driver private state info specific to this instance
 * @param mode - enum selecting mode enable/disable:
 *    CEDI_SERDES_LOOPBACK :select loopback mode in PHY transceiver, if
 *        available
 *    CEDI_LOCAL_LOOPBACK  :select internal loopback mode. Tx and Rx should be
 *                        :disabled when enabling or disabling this mode.
 *                        :Only available if int_loopback defined.
 *    CEDI_NO_LOOPBACK     :disable loopback mode
 * @return ENOTSUP if CEDI_SERDES_LOOPBACK selected and no_pcs defined, or
 *    if CEDI_LOCAL_LOOPBACK selected and either
 *        (no_int_loopback defined or PCS mode is selected)
 * @return ENOTSUP if CEDI_LOCAL_LOOPBACK selected and no_int_loopback defined
 * @return 0 otherwise.
 */
uint32_t emacSetLoopback(void *pD, uint8_t mode)
{
    uint32_t reg;
    uint32_t reg2;
    if (pD==NULL) return EINVAL;
    if (mode>CEDI_SERDES_LOOPBACK) return EINVAL;

    if ((CEDI_PdVar(hwCfg).no_pcs && (mode==CEDI_SERDES_LOOPBACK)) ||
        (CEDI_PdVar(hwCfg).no_int_loopback &&
            (mode==CEDI_LOCAL_LOOPBACK)))
        return ENOTSUP;
    if ((EMAC_REGS__NETWORK_CONFIG__PCS_SELECT__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)))) &&
            (mode==CEDI_LOCAL_LOOPBACK))
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    reg2 = CPS_UncachedRead32(CEDI_RegAddr(pcs_control));
    EMAC_REGS__NETWORK_CONTROL__LOOPBACK__CLR(reg);
    if (mode==CEDI_LOCAL_LOOPBACK) {
        EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__SET(reg);
        EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__CLR(reg2);
    }
    else if (mode==CEDI_SERDES_LOOPBACK) {
        EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__CLR(reg);
        EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__SET(reg2);
    }
    else {  /* CEDI_NO_LOOPBACK */
        EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__CLR(reg);
        EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__CLR(reg2);
    }
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);
    CPS_UncachedWrite32(CEDI_RegAddr(pcs_control), reg2);

    return 0;
}

uint32_t emacGetLoopback(void *pD, uint8_t *mode)
{
    uint32_t reg;
    uint32_t reg2;
    if ((pD==NULL)||(mode==NULL))
      return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    reg2 = CPS_UncachedRead32(CEDI_RegAddr(pcs_control));
    if (EMAC_REGS__PCS_CONTROL__LOOPBACK_MODE__READ(reg2))
        *mode= CEDI_SERDES_LOOPBACK;
    else
    if (EMAC_REGS__NETWORK_CONTROL__LOOPBACK_LOCAL__READ(reg))
        *mode= CEDI_LOCAL_LOOPBACK;
    else
        *mode= CEDI_NO_LOOPBACK;

    return 0;
}

/**************************** PTP/1588 Support *******************************/

void emacSetUnicastPtpDetect(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return;
    if (enable>1) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    if (enable)
        EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__SET(reg);
    else
        EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);
}

uint32_t emacGetUnicastPtpDetect(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;
    *enable= EMAC_REGS__NETWORK_CONTROL__PTP_UNICAST_ENA__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_control)));

    return 0;
}

uint32_t emacSetPtpRxUnicastIpAddr(void *pD, uint32_t rxAddr)
{
    uint32_t reg = 0;
    uint32_t ret = 0;
    uint8_t enabled = 0;
    ret = emacGetUnicastPtpDetect(pD, &enabled);
    if (ret!=0)
      return ret;
    if (enabled)
      return ENOTSUP;
    EMAC_REGS__RX_PTP_UNICAST__ADDRESS__MODIFY(reg, rxAddr);
    CPS_UncachedWrite32(CEDI_RegAddr(rx_ptp_unicast), reg);
    return 0;
}

uint32_t emacGetPtpRxUnicastIpAddr(void *pD, uint32_t *rxAddr)
{
    if ((pD==NULL)||(rxAddr==NULL))
      return EINVAL;
    *rxAddr= EMAC_REGS__RX_PTP_UNICAST__ADDRESS__READ(
            CPS_UncachedRead32(CEDI_RegAddr(rx_ptp_unicast)));

    return 0;
}

uint32_t emacSetPtpTxUnicastIpAddr(void *pD, uint32_t txAddr)
{
    uint32_t reg = 0;
    uint32_t ret = 0;
    uint8_t enabled = 0;
    ret = emacGetUnicastPtpDetect(pD,&enabled);
    if (ret!=0)
      return ret;
    if (enabled)
      return ENOTSUP;
    EMAC_REGS__TX_PTP_UNICAST__ADDRESS__MODIFY(reg, txAddr);
    CPS_UncachedWrite32(CEDI_RegAddr(tx_ptp_unicast), reg);
    return 0;
}

uint32_t emacGetPtpTxUnicastIpAddr(void *pD, uint32_t *txAddr)
{
    if ((pD==NULL)||(txAddr==NULL))
      return EINVAL;
    *txAddr= EMAC_REGS__TX_PTP_UNICAST__ADDRESS__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tx_ptp_unicast)));

    return 0;
}

uint32_t emacSet1588Timer(void *pD, CEDI_1588TimerVal *time)
{
    uint32_t reg;
    if ((pD==NULL) || (time==NULL))
        return EINVAL;
    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;
    if (time->nanosecs>0x3FFFFFFF)
        return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(tsu_timer_msb_sec));
    EMAC_REGS__TSU_TIMER_MSB_SEC__TIMER__MODIFY(reg, time->secsUpper);
    CPS_UncachedWrite32(CEDI_RegAddr(tsu_timer_msb_sec), reg);
    /* write lower bits 2nd, for synchronised secs update */
    reg = 0;
    EMAC_REGS__TSU_TIMER_SEC__TIMER__MODIFY(reg, time->secsLower);
    CPS_UncachedWrite32(CEDI_RegAddr(tsu_timer_sec), reg);
    reg = 0;
    EMAC_REGS__TSU_TIMER_NSEC__TIMER__MODIFY(reg, time->nanosecs);
    CPS_UncachedWrite32(CEDI_RegAddr(tsu_timer_nsec), reg);
    return 0;
}

uint32_t emacGet1588Timer(void *pD, CEDI_1588TimerVal *time)
{
    uint32_t reg, first;
    if ((pD==NULL) || (time==NULL)) return EINVAL;
    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;

    first = EMAC_REGS__TSU_TIMER_NSEC__TIMER__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_timer_nsec)));
    time->secsLower = EMAC_REGS__TSU_TIMER_SEC__TIMER__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_timer_sec)));
    time->secsUpper = EMAC_REGS__TSU_TIMER_MSB_SEC__TIMER__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_timer_msb_sec)));
    /* test for nsec rollover */
    reg = CPS_UncachedRead32(CEDI_RegAddr(tsu_timer_nsec));
    if (first>(EMAC_REGS__TSU_TIMER_NSEC__TIMER__READ(reg))) {
        /* if so, use later read & re-read seconds
         * (assume all done within 1s) */
        time->nanosecs = EMAC_REGS__TSU_TIMER_NSEC__TIMER__READ(reg);
        time->secsLower = EMAC_REGS__TSU_TIMER_SEC__TIMER__READ(
                CPS_UncachedRead32(CEDI_RegAddr(tsu_timer_sec)));
        time->secsUpper = EMAC_REGS__TSU_TIMER_MSB_SEC__TIMER__READ(
                CPS_UncachedRead32(CEDI_RegAddr(tsu_timer_msb_sec)));
    }
    else
        time->nanosecs = first;

    return 0;
}

uint32_t emacAdjust1588Timer(void *pD, int32_t nSecAdjust)
{
    uint32_t reg;
    if (pD==NULL) return EINVAL;
    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;
    if ((nSecAdjust<(-0x3FFFFFFF)) || (nSecAdjust>0x3FFFFFFF))
        return EINVAL;

    reg = 0;
    if (nSecAdjust<0) {
        EMAC_REGS__TSU_TIMER_ADJUST__ADD_SUBTRACT__SET(reg);
        nSecAdjust = -nSecAdjust;
    }

    EMAC_REGS__TSU_TIMER_ADJUST__INCREMENT_VALUE__MODIFY(reg, nSecAdjust);
    CPS_UncachedWrite32(CEDI_RegAddr(tsu_timer_adjust), reg);
    return 0;
}

uint32_t emacSet1588TimerInc(void *pD, CEDI_TimerIncrement *incSettings)
{
    uint32_t reg;
    if ((pD==NULL) || (incSettings==NULL))
        return EINVAL;
    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;

#ifdef  EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__MODIFY
    reg = 0;
    EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR__MODIFY(reg,
                       incSettings->subNsInc);
    if (subNsTsuInc24bSupport(pD))
        EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__MODIFY(reg,
                          incSettings->lsbSubNsInc);
    CPS_UncachedWrite32(CEDI_RegAddr(tsu_timer_incr_sub_nsec), reg);

    reg = 0;
    EMAC_REGS__TSU_TIMER_INCR__NS_INCREMENT__MODIFY(reg,
                        incSettings->nanoSecsInc);
    EMAC_REGS__TSU_TIMER_INCR__ALT_NS_INCR__MODIFY(reg,
                        incSettings->altNanoSInc);
    EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__MODIFY(reg,
                        incSettings->altIncCount);
    CPS_UncachedWrite32(CEDI_RegAddr(tsu_timer_incr), reg);

#else
    reg = 0;
    EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__TIMER__MODIFY(reg,
                                                    incSettings->subNsInc);
    CPS_UncachedWrite32(CEDI_RegAddr(tsu_timer_incr_sub_nsec), reg);

    reg = 0;
    EMAC_REGS__TSU_TIMER_INCR__COUNT__MODIFY(reg, incSettings->nanoSecsInc);
    EMAC_REGS__TSU_TIMER_INCR__ALT_COUNT__MODIFY(reg,
                        incSettings->altNanoSInc);
    EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__MODIFY(reg, incSettings->altIncCount);
    CPS_UncachedWrite32(CEDI_RegAddr(tsu_timer_incr), reg);
#endif

    return 0;
}

uint32_t emacGet1588TimerInc(void *pD, CEDI_TimerIncrement *incSettings)
{
    uint32_t reg;
    if ((pD==NULL) || (incSettings==NULL))
        return EINVAL;
    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;

#ifdef  EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__READ
    reg = CPS_UncachedRead32(CEDI_RegAddr(tsu_timer_incr_sub_nsec));
    incSettings->subNsInc =
                EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR__READ(reg);
    if (subNsTsuInc24bSupport(pD))
        incSettings->lsbSubNsInc =
                EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__SUB_NS_INCR_LSB__READ(reg);
    else
        incSettings->lsbSubNsInc = 0;
    reg = CPS_UncachedRead32(CEDI_RegAddr(tsu_timer_incr));
    incSettings->nanoSecsInc =
                EMAC_REGS__TSU_TIMER_INCR__NS_INCREMENT__READ(reg);
    incSettings->altNanoSInc =
                EMAC_REGS__TSU_TIMER_INCR__ALT_NS_INCR__READ(reg);
    incSettings->altIncCount = EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__READ(reg);
#else
    incSettings->subNsInc = EMAC_REGS__TSU_TIMER_INCR_SUB_NSEC__TIMER__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_timer_incr_sub_nsec)));
    incSettings->lsbSubNsInc = 0;
    reg = CPS_UncachedRead32(CEDI_RegAddr(tsu_timer_incr));
    incSettings->nanoSecsInc = EMAC_REGS__TSU_TIMER_INCR__COUNT__READ(reg);
    incSettings->altNanoSInc = EMAC_REGS__TSU_TIMER_INCR__ALT_COUNT__READ(reg);
    incSettings->altIncCount = EMAC_REGS__TSU_TIMER_INCR__NUM_INCS__READ(reg);
#endif

    return 0;
}

uint32_t emacSetTsuTimerCompVal(void *pD, CEDI_TsuTimerVal *time)
{
    uint32_t reg;
    if ((pD==NULL) || (time==NULL))
        return EINVAL;
    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;
    if (time->nanosecs>0x003FFFFF)
        return EINVAL;

    reg = 0;
    EMAC_REGS__TSU_NSEC_CMP__COMPARISON_VALUE__MODIFY(reg, time->nanosecs);
    CPS_UncachedWrite32(CEDI_RegAddr(tsu_nsec_cmp), reg);
    reg = 0;
    EMAC_REGS__TSU_SEC_CMP__COMPARISON_VALUE__MODIFY(reg, time->secsLower);
    CPS_UncachedWrite32(CEDI_RegAddr(tsu_sec_cmp), reg);
    reg = 0;
    EMAC_REGS__TSU_MSB_SEC_CMP__COMPARISON_VALUE__MODIFY(reg, time->secsUpper);
    CPS_UncachedWrite32(CEDI_RegAddr(tsu_msb_sec_cmp), reg);
    return 0;
}

uint32_t emacGetTsuTimerCompVal(void *pD, CEDI_TsuTimerVal *time)
{
    if ((pD==NULL) || (time==NULL))
        return EINVAL;
    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;

    time->nanosecs = EMAC_REGS__TSU_NSEC_CMP__COMPARISON_VALUE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_nsec_cmp)));
    time->secsLower = EMAC_REGS__TSU_SEC_CMP__COMPARISON_VALUE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_sec_cmp)));
    time->secsUpper = EMAC_REGS__TSU_MSB_SEC_CMP__COMPARISON_VALUE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_msb_sec_cmp)));
    return 0;
}

uint32_t emacGetPtpFrameTxTime(void *pD, CEDI_1588TimerVal *time)
{
    if ((pD==NULL) || (time==NULL))
        return EINVAL;
    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;

    time->nanosecs = EMAC_REGS__TSU_PTP_TX_NSEC__TIMER__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_ptp_tx_nsec)));
    time->secsLower = EMAC_REGS__TSU_PTP_TX_SEC__TIMER__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_ptp_tx_sec)));
    time->secsUpper = EMAC_REGS__TSU_PTP_TX_MSB_SEC__TIMER_SECONDS__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_ptp_tx_msb_sec)));
    return 0;
}

uint32_t emacGetPtpFrameRxTime(void *pD, CEDI_1588TimerVal *time)
{
    if ((pD==NULL) || (time==NULL))
        return EINVAL;
    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;

    time->nanosecs = EMAC_REGS__TSU_PTP_RX_NSEC__TIMER__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_ptp_rx_nsec)));
    time->secsLower = EMAC_REGS__TSU_PTP_RX_SEC__TIMER__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_ptp_rx_sec)));
    time->secsUpper = EMAC_REGS__TSU_PTP_RX_MSB_SEC__TIMER_SECONDS__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_ptp_rx_msb_sec)));
    return 0;
}

uint32_t emacGetPtpPeerFrameTxTime(void *pD, CEDI_1588TimerVal *time)
{
    if ((pD==NULL) || (time==NULL))
        return EINVAL;
    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;

    time->nanosecs = EMAC_REGS__TSU_PEER_TX_NSEC__TIMER__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_peer_tx_nsec)));
    time->secsLower = EMAC_REGS__TSU_PEER_TX_SEC__TIMER__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_peer_tx_sec)));
    time->secsUpper = EMAC_REGS__TSU_PEER_TX_MSB_SEC__TIMER_SECONDS__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_peer_tx_msb_sec)));
    return 0;
}

uint32_t emacGetPtpPeerFrameRxTime(void *pD, CEDI_1588TimerVal *time)
{
    if ((pD==NULL) || (time==NULL))
        return EINVAL;
    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;

    time->nanosecs = EMAC_REGS__TSU_PEER_RX_NSEC__TIMER__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_peer_rx_nsec)));
    time->secsLower = EMAC_REGS__TSU_PEER_RX_SEC__TIMER__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_peer_rx_sec)));
    time->secsUpper = EMAC_REGS__TSU_PEER_RX_MSB_SEC__TIMER_SECONDS__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_peer_rx_msb_sec)));
    return 0;
}

uint32_t emacGet1588SyncStrobeTime(void *pD, CEDI_1588TimerVal *time)
{
    if ((pD==NULL) || (time==NULL))
        return EINVAL;
    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;

    time->nanosecs = EMAC_REGS__TSU_STROBE_NSEC__STROBE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_strobe_nsec)));
    time->secsLower = EMAC_REGS__TSU_STROBE_SEC__STROBE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_strobe_sec)));
    time->secsUpper =
            EMAC_REGS__TSU_STROBE_MSB_SEC__STROBE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tsu_strobe_msb_sec)));
    return 0;
}

uint32_t emacSetExtTsuPortEnable(void *pD, uint8_t enable)
{
    uint32_t reg;

    if (pD==NULL) return EINVAL;
    if (enable>1) return EINVAL;
    if (0==CEDI_PdVar(hwCfg).ext_tsu_timer)
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    if (enable)
        EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__SET(reg);
    else
        EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);

    return 0;
}

uint32_t emacGetExtTsuPortEnable(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;
    *enable= 0;

    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;

    *enable = EMAC_REGS__NETWORK_CONTROL__EXT_TSU_PORT_ENABLE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_control)));
    return 0;
}

uint32_t emacSet1588OneStepTxSyncEnable(void *pD, uint8_t enable)
{
    uint32_t reg;

    if (pD==NULL) return EINVAL;
    if (enable>1) return EINVAL;
    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    if (enable)
        EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__SET(reg);
    else
        EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);

    return 0;
}

uint32_t emacGet1588OneStepTxSyncEnable(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
        return EINVAL;
    *enable = 0;

    if (CEDI_PdVar(hwCfg).tsu)
    {
        *enable = EMAC_REGS__NETWORK_CONTROL__ONE_STEP_SYNC_MODE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_control)));
    }
    return 0;
}

/****************************** Time Stamping *********************************/

uint32_t emacSetDescTimeStampMode(void *pD, CEDI_TxTsMode txMode,
                                    CEDI_RxTsMode rxMode)
{
    uint32_t regData;
    CEDI_Config *config = &CEDI_PdVar(cfg);

    if (pD==NULL)
        return EINVAL;
    if ((txMode>CEDI_TX_TS_ALL) || (rxMode>CEDI_RX_TS_ALL))
        return EINVAL;

    if (((config->enTxExtBD==0) && (txMode!=0))||
            ((config->enRxExtBD==0) && (rxMode!=0)))
    {
        vDbgMsg(DBG_GEN_MSG, 5, "%s","ERROR: Time stamping not enabled in DMA config ");
        return EINVAL;
    }

    regData = CPS_UncachedRead32(CEDI_RegAddr(tx_bd_control));
    EMAC_REGS__TX_BD_CONTROL__TX_BD_TS_MODE__MODIFY(regData,txMode);
    CPS_UncachedWrite32(CEDI_RegAddr(tx_bd_control),regData);

    regData = CPS_UncachedRead32(CEDI_RegAddr(rx_bd_control));
    EMAC_REGS__RX_BD_CONTROL__RX_BD_TS_MODE__MODIFY(regData,rxMode);
    CPS_UncachedWrite32(CEDI_RegAddr(rx_bd_control),regData);

    return 0;
}

uint32_t emacGetDescTimeStampMode(void *pD, CEDI_TxTsMode* txMode,
                                    CEDI_RxTsMode* rxMode)
{
    uint32_t regData;
    CEDI_Config *config = &CEDI_PdVar(cfg);

    if ((pD==NULL) || (txMode==NULL) || (rxMode==NULL))
        return EINVAL;
    if ((config->enTxExtBD==0)||(config->enRxExtBD==0))
        return ENOTSUP;

    regData = CPS_UncachedRead32(CEDI_RegAddr(tx_bd_control));
    *txMode = (CEDI_TxTsMode)EMAC_REGS__TX_BD_CONTROL__TX_BD_TS_MODE__READ(regData);

    regData = CPS_UncachedRead32(CEDI_RegAddr(rx_bd_control));
    *rxMode = (CEDI_RxTsMode)EMAC_REGS__RX_BD_CONTROL__RX_BD_TS_MODE__READ(regData);

    return 0;
}

uint32_t emacSetStoreRxTimeStamp(void *pD, uint8_t enable)
{
    uint32_t reg;

    if (pD==NULL) return EINVAL;
    if (enable>1) return EINVAL;
    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    if (enable)
        EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__SET(reg);
    else
        EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);
    return 0;
}

uint32_t emacGetStoreRxTimeStamp(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;
    *enable = 0;

    if (0==CEDI_PdVar(hwCfg).tsu)
        return ENOTSUP;

    *enable = EMAC_REGS__NETWORK_CONTROL__STORE_RX_TS__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_control)));
    return 0;
}

/********************** PCS Control/Auto-negotiation *************************/

uint32_t emacResetPcs(void *pD)
{
    uint32_t reg;
    if (pD==NULL) return EINVAL;
    vDbgMsg(DBG_GEN_MSG, 10, "%s entered (regBase %08X)\n", __func__,
            (uint32_t)CEDI_PdVar(cfg).regBase);
    if (CEDI_PdVar(hwCfg).no_pcs)
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(pcs_control));
    EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__SET(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(pcs_control), reg);

    CEDI_PdVar(basePageExp) = 1;
    CEDI_PdVar(autoNegActive) = 0;

    return 0;
}

uint32_t emacGetPcsReady(void *pD, uint8_t *ready)
{
    if ((pD==NULL)||(ready==NULL))
      return EINVAL;
    if (CEDI_PdVar(hwCfg).no_pcs)
        return ENOTSUP;

    *ready = (0==EMAC_REGS__PCS_CONTROL__PCS_SOFTWARE_RESET__READ(
            CPS_UncachedRead32(CEDI_RegAddr(pcs_control))));
    return 0;
}

uint32_t emacStartAutoNegotiation(void *pD, CEDI_AnAdvPage *advDat)
{
    uint32_t reg;
    uint32_t event;
    uint32_t ret;

    if ((pD==NULL)||(advDat==NULL))
        return EINVAL;

    if ((CEDI_PdVar(hwCfg).no_pcs) ||
       (EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)))))
        return ENOTSUP;
    if (CEDI_PdVar(autoNegActive))
        return EBUSY;

    //check if we have an event for auto negotiation complete:
    ret=emacGetEventEnable(pD,0,&event);
    if (ret!=0)
        return ret;
    if ((event & CEDI_EV_PCS_AN_COMPLETE) == 0)
        return EINVAL;

    if ((advDat->fullDuplex>1) || (advDat->halfDuplex>1) || (advDat->nextPage>1)
            || (advDat->pauseCap>CEDI_AN_PAUSE_CAP_BOTH)
            || (advDat->remFlt>CEDI_AN_REM_FLT_AN_ERR))
        return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(pcs_control));
    EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__SET(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(pcs_control), reg);

    emacSetAnAdvPage(pD, advDat);

    CEDI_PdVar(autoNegActive) = 1;
    CEDI_PdVar(basePageExp) = 1;

    reg = CPS_UncachedRead32(CEDI_RegAddr(pcs_control));
    EMAC_REGS__PCS_CONTROL__RESTART_AUTO_NEG__SET(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(pcs_control), reg);
    return 0;
}

uint32_t emacSetAutoNegEnable(void *pD, uint8_t enable)
{
    uint32_t reg;

    if (pD==NULL)
        return EINVAL;
    if (enable>1) return EINVAL;
    if (CEDI_PdVar(hwCfg).no_pcs ||
       (EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)))))
        return ENOTSUP;
    if ((enable) && CEDI_PdVar(autoNegActive))
        return EBUSY;

    reg = CPS_UncachedRead32(CEDI_RegAddr(pcs_control));
    if (enable) {
        EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__SET(reg);
    }
    else
    {
        EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__CLR(reg);
        CEDI_PdVar(autoNegActive) = 0;
    }
    CPS_UncachedWrite32(CEDI_RegAddr(pcs_control), reg);

    return 0;
}

uint32_t emacGetAutoNegEnable(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
        return EINVAL;
    if (CEDI_PdVar(hwCfg).no_pcs)
        return ENOTSUP;

    *enable = EMAC_REGS__PCS_CONTROL__ENABLE_AUTO_NEG__READ(
        CPS_UncachedRead32(CEDI_RegAddr(pcs_control)));
    return 0;
}

/* internal utility for reading PCS status & maintaining
 * "read-once" functionality of link status & remote fault
 */
uint32_t readPcsStatus(void *pD) {
    uint32_t reg = CPS_UncachedRead32(CEDI_RegAddr(pcs_status));
    if (0==EMAC_REGS__PCS_STATUS__LINK_STATUS__READ(reg))
        CEDI_PdVar(anLinkStat) = 0;
    if (1==EMAC_REGS__PCS_STATUS__REMOTE_FAULT__READ(reg))
        CEDI_PdVar(anRemFault) = 1;
    return reg;
}

uint32_t emacGetLinkStatus(void *pD, uint8_t *status)
{
    uint32_t reg;

    if ((pD==NULL)||(status==NULL))
      return EINVAL;

    reg = readPcsStatus(pD);
    /* return low if this has not been done yet */
    *status = CEDI_PdVar(anLinkStat);

    CEDI_PdVar(anLinkStat) =
            EMAC_REGS__PCS_STATUS__LINK_STATUS__READ(reg);

    return 0;
}

uint32_t emacGetAnRemoteFault(void *pD, uint8_t *status)
{
    uint32_t reg;

    if ((pD==NULL)||(status==NULL))
      return EINVAL;

    reg = readPcsStatus(pD);
    /* return high if this has not been done yet */
    *status = CEDI_PdVar(anRemFault);

    CEDI_PdVar(anRemFault) =
            EMAC_REGS__PCS_STATUS__REMOTE_FAULT__READ(reg);

    return 0;
}

uint32_t emacGetAnComplete(void *pD, uint8_t *status)
{
    if ((pD==NULL)||(status==NULL))
      return EINVAL;
    if (CEDI_PdVar(hwCfg).no_pcs)
        return ENOTSUP;

    *status = EMAC_REGS__PCS_STATUS__AUTO_NEG_COMPLETE__READ(readPcsStatus(pD));

    return 0;
}

uint32_t emacSetAnAdvPage(void *pD, CEDI_AnAdvPage *advDat)
{
    uint32_t reg;

    if ((pD==NULL)||(advDat==NULL))
        return EINVAL;
    if (CEDI_PdVar(hwCfg).no_pcs)
        return ENOTSUP;
    if ((advDat->fullDuplex>1) || (advDat->halfDuplex>1) || (advDat->nextPage>1)
            || (advDat->pauseCap>CEDI_AN_PAUSE_CAP_BOTH)
            || (advDat->remFlt>CEDI_AN_REM_FLT_AN_ERR))
        return EINVAL;

    reg = 0;
    if (advDat->fullDuplex)
        EMAC_REGS__PCS_AN_ADV__FULL_DUPLEX__SET(reg);
    if (advDat->halfDuplex)
        EMAC_REGS__PCS_AN_ADV__HALF_DUPLEX__SET(reg);
    EMAC_REGS__PCS_AN_ADV__PAUSE__MODIFY(reg, advDat->pauseCap);
    EMAC_REGS__PCS_AN_ADV__REMOTE_FAULT__MODIFY(reg, advDat->remFlt);
    if (advDat->nextPage)
        EMAC_REGS__PCS_AN_ADV__NEXT_PAGE__SET(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(pcs_an_adv), reg);

    return 0;
}

uint32_t emacGetAnAdvPage(void *pD, CEDI_AnAdvPage *advDat)
{
    uint32_t reg;

    if ((pD==NULL)||(advDat==NULL))
        return EINVAL;
    if (CEDI_PdVar(hwCfg).no_pcs)
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(pcs_an_adv));
    advDat->fullDuplex = EMAC_REGS__PCS_AN_ADV__FULL_DUPLEX__READ(reg);
    advDat->halfDuplex = EMAC_REGS__PCS_AN_ADV__HALF_DUPLEX__READ(reg);
    advDat->pauseCap = (CEDI_PauseCap)EMAC_REGS__PCS_AN_ADV__PAUSE__READ(reg);
    advDat->remFlt = (CEDI_RemoteFault)EMAC_REGS__PCS_AN_ADV__REMOTE_FAULT__READ(reg);
    advDat->nextPage = EMAC_REGS__PCS_AN_ADV__NEXT_PAGE__READ(reg);

    return 0;
}

uint32_t emacGetLpAbilityPage(void *pD, CEDI_LpAbilityPage *lpAbl)
{
    uint32_t reg;

    if ((pD==NULL) || (lpAbl==NULL))
         return EINVAL;
    if (CEDI_PdVar(hwCfg).no_pcs)
         return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(pcs_an_lp_base));

    if (EMAC_REGS__NETWORK_CONFIG__SGMII_MODE_ENABLE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config))))
    {
        /* SGMII mode format */
        lpAbl->sgmii = 1;
        lpAbl->ablInfo.sgmLpAbl.speed =
                (CEDI_IfSpeed)(EMAC_REGS__PCS_AN_LP_BASE__SPEED_RESERVED__READ(reg)>>1);
        lpAbl->ablInfo.sgmLpAbl.lpAck =
                EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_ACKNOWLEDGE__READ(reg);
        lpAbl->ablInfo.sgmLpAbl.linkStatus =
                EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_NEXT_PAGE_STATUS__READ(reg);
        lpAbl->ablInfo.sgmLpAbl.duplex =
                EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_REMOTE_FAULT_DUPLEX_MODE__READ(reg);
    }
    else
    {
        /* Default format */
        lpAbl->sgmii = 0;
        lpAbl->ablInfo.defLpAbl.fullDuplex =
                EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_FULL_DUPLEX__READ(reg);
        lpAbl->ablInfo.defLpAbl.halfDuplex =
                EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_HALF_DUPLEX__READ(reg);
        lpAbl->ablInfo.defLpAbl.pauseCap =
                (CEDI_PauseCap)EMAC_REGS__PCS_AN_LP_BASE__PAUSE__READ(reg);
        lpAbl->ablInfo.defLpAbl.lpAck =
                EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_ACKNOWLEDGE__READ(reg);
        lpAbl->ablInfo.defLpAbl.remFlt =
                (CEDI_RemoteFault)EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_REMOTE_FAULT_DUPLEX_MODE__READ(reg);
        lpAbl->ablInfo.defLpAbl.lpNextPage =
                EMAC_REGS__PCS_AN_LP_BASE__LINK_PARTNER_NEXT_PAGE_STATUS__READ(reg);
    }

    return 0;
}

uint32_t emacGetPageRx(void *pD)
{
    if (pD==NULL) return 0;
    if (CEDI_PdVar(hwCfg).no_pcs)
        return 0;

    return EMAC_REGS__PCS_AN_EXP__PAGE_RECEIVED__READ(
            CPS_UncachedRead32(CEDI_RegAddr(pcs_an_exp)));
}

uint32_t emacSetNextPageTx(void *pD, CEDI_AnNextPage *npDat)
{
    uint32_t reg;

    if ((pD==NULL)||(npDat==NULL))
      return EINVAL;
    if (CEDI_PdVar(hwCfg).no_pcs)
        return ENOTSUP;
    if ((npDat->message>0x7FF) || (npDat->ack2>1) || (npDat->msgPage>1)
            || (npDat->np>1))
        return EINVAL;

    reg = 0;
    EMAC_REGS__PCS_AN_NP_TX__MESSAGE__MODIFY(reg, npDat->message);
    if (npDat->ack2)
        EMAC_REGS__PCS_AN_NP_TX__ACKNOWLEDGE_2__SET(reg);
    if (npDat->msgPage)
        EMAC_REGS__PCS_AN_NP_TX__MESSAGE_PAGE_INDICATOR__SET(reg);
    if (npDat->np)
        EMAC_REGS__PCS_AN_NP_TX__NEXT_PAGE_TO_TRANSMIT__SET(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(pcs_an_np_tx), reg);

    return 0;
}

uint32_t emacGetNextPageTx(void *pD, CEDI_AnNextPage *npDat)
{
    uint32_t reg;

    if ((pD==NULL)||(npDat==NULL))
      return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(pcs_an_np_tx));
    npDat->message = EMAC_REGS__PCS_AN_NP_TX__MESSAGE__READ(reg);
    npDat->ack2 = EMAC_REGS__PCS_AN_NP_TX__ACKNOWLEDGE_2__READ(reg);
    npDat->msgPage = EMAC_REGS__PCS_AN_NP_TX__MESSAGE_PAGE_INDICATOR__READ(reg);
    npDat->np = EMAC_REGS__PCS_AN_NP_TX__NEXT_PAGE_TO_TRANSMIT__READ(reg);

    return 0;
}

uint32_t emacGetLpNextPage(void *pD, CEDI_LpNextPage *npDat)
{
    uint32_t reg;

    if ((pD==NULL)||(npDat==NULL))
      return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(pcs_an_lp_np));
    npDat->message = EMAC_REGS__PCS_AN_LP_NP__MESSAGE__READ(reg);
    npDat->toggle = EMAC_REGS__PCS_AN_LP_NP__TOGGLE__READ(reg);
    npDat->ack2 = EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE_2__READ(reg);
    npDat->msgPage = EMAC_REGS__PCS_AN_LP_NP__MESSAGE_PAGE_INDICATOR__READ(reg);
    npDat->ack = EMAC_REGS__PCS_AN_LP_NP__ACKNOWLEDGE__READ(reg);
    npDat->np = EMAC_REGS__PCS_AN_LP_NP__NEXT_PAGE_TO_RECEIVE__READ(reg);

    return 0;
}

/**************************** PHY Management *********************************/

uint32_t emacGetPhyId(void *pD, uint32_t *phyId)
{
    if ((pD==NULL)||(phyId==NULL))
      return EINVAL;

#ifdef EMAC_REGS__PCS_PHY_TOP_ID__ID_CODE__READ
    volatile uint32_t reg, retVal;
    reg = CPS_UncachedRead32(CEDI_RegAddr(pcs_phy_top_id));
    retVal = EMAC_REGS__PCS_PHY_TOP_ID__ID_CODE__READ(reg)<<16;
    reg = CPS_UncachedRead32(CEDI_RegAddr(pcs_phy_bot_id));
    retVal |= EMAC_REGS__PCS_PHY_BOT_ID__ID_CODE__READ(reg);
    *phyId= retVal;
    return 0;
#endif
    return ENOTSUP;
}

void emacSetMdioEnable(void *pD, uint8_t enable)
{
    uint32_t ncr;
    if (pD==NULL) return;
    if (enable>1) return;
    ncr = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    if (enable)
        EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__SET(ncr);
    else
        EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__CLR(ncr);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), ncr);
}

uint32_t emacGetMdioEnable(void *pD)
{
    if (pD==NULL) return 0;
    return EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__READ(
          CPS_UncachedRead32(CEDI_RegAddr(network_control)));
}

/* Initiate a write or set address operation on the MDIO interface.
 * Clause 45 devices require a call to set the register address (if
 * this is changing since last access), and then a write or read
 * operation.
 * The command writes to the shift register, which starts output on
 * the MDIO interface. Write completion is signalled by the
 * phyManComplete callback, or by polling getMdioIdle.
 * @param pD - driver private state info specific to this instance
 * @param flags - combination of 2 bit-flags:
 *        if CEDI_MDIO_FLG_CLAUSE_45 present, specifies clause 45 PHY
 *        (else clause 22).
 *        if CEDI_MDIO_FLG_SET_ADDR present, specifies a set address operation
 *        (else do a write operation)  Ignored if not clause 45.
 * @param phyAddr - PHY address
 * @param devReg - device type (clause 45) or register address (clause 22)
 *           - enum CEDI_MdioDevType is available to specify the device type
 * @param addrData - register address (if CEDI_MDIO_FLG_SET_ADDR) or data to write
 */
void emacPhyStartMdioWrite(void *pD, uint8_t flags, uint8_t phyAddr,
        uint8_t devReg, uint16_t addrData)
{
    uint32_t reg;
    if (pD==NULL) return;
    reg = 0;
    EMAC_REGS__PHY_MANAGEMENT__PHY_WRITE_READ_DATA__MODIFY(reg, addrData);
    EMAC_REGS__PHY_MANAGEMENT__WRITE10__MODIFY(reg, 2);
    EMAC_REGS__PHY_MANAGEMENT__REGISTER_ADDRESS__MODIFY(reg, devReg);
    EMAC_REGS__PHY_MANAGEMENT__PHY_ADDRESS__MODIFY(reg, phyAddr);
    if ((flags & CEDI_MDIO_FLG_CLAUSE_45) && (flags & CEDI_MDIO_FLG_SET_ADDR)) {
        EMAC_REGS__PHY_MANAGEMENT__OPERATION__MODIFY(reg, CEDI_PHY_ADDR_OP);
    }
    else
        EMAC_REGS__PHY_MANAGEMENT__OPERATION__MODIFY(reg, CEDI_PHY_WRITE_OP);
    if ((flags & CEDI_MDIO_FLG_CLAUSE_45)==0)
        EMAC_REGS__PHY_MANAGEMENT__WRITE1__SET(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(phy_management), reg);
}

/* Initiate a read operation on the MDIO interface.  If clause 45, the
 * register address will need to be set by a preceding phyStartMdioWrite
 * call, unless same as for last operation. Completion is signalled by the
 * phyManComplete callback, which will return the read data by a pointer
 * parameter. Alternatively polling getMdioIdle will indicate when
 * the operation completes, then getMdioReadDat will return the data.
 * @param pD - driver private state info specific to this instance
 * @param flags - combination of 2 bit-flags:
 *        if CEDI_MDIO_FLG_CLAUSE_45 present, specifies clause 45 PHY
 *        (else clause 22).
 *        if CEDI_MDIO_FLG_INC_ADDR present, and clause 45, then address will
 *        be incremented after the read operation.
 * @param phyAddr - PHY address
 * @param devReg - device type (clause 45) or register address (clause 22)
 *           - enum CEDI_MdioDevType is available to specify the device type
 */
void emacPhyStartMdioRead(void *pD, uint8_t flags, uint8_t phyAddr,
        uint8_t devReg)
{
    uint32_t reg;
    if (pD==NULL) return;
    reg = 0;
    EMAC_REGS__PHY_MANAGEMENT__WRITE10__MODIFY(reg, 2);
    EMAC_REGS__PHY_MANAGEMENT__REGISTER_ADDRESS__MODIFY(reg, devReg);
    EMAC_REGS__PHY_MANAGEMENT__PHY_ADDRESS__MODIFY(reg, phyAddr);
    if (flags & CEDI_MDIO_FLG_CLAUSE_45) {
        if (flags & CEDI_MDIO_FLG_INC_ADDR) {
            EMAC_REGS__PHY_MANAGEMENT__OPERATION__MODIFY(reg,
                    CEDI_PHY_CL45_READ_INC_OP);
        }
        else {
            EMAC_REGS__PHY_MANAGEMENT__OPERATION__MODIFY(reg,
                    CEDI_PHY_CL45_READ_OP);
        }
    }
    else
        EMAC_REGS__PHY_MANAGEMENT__OPERATION__MODIFY(reg, CEDI_PHY_CL22_READ_OP);
    if ((flags & CEDI_MDIO_FLG_CLAUSE_45)==0)
        EMAC_REGS__PHY_MANAGEMENT__WRITE1__SET(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(phy_management), reg);
}

uint32_t emacGetMdioReadData(void *pD, uint16_t *readData)
{
    if ((pD==NULL)||(readData==NULL))
      return EINVAL;
    *readData= EMAC_REGS__PHY_MANAGEMENT__PHY_WRITE_READ_DATA__READ(
           CPS_UncachedRead32(CEDI_RegAddr(phy_management)));

    return 0;
}

uint32_t emacGetMdioIdle(void *pD)
{
    if (pD==NULL) return 0;
    return EMAC_REGS__NETWORK_STATUS__MAN_DONE__READ(
           CPS_UncachedRead32(CEDI_RegAddr(network_status)));
}

/************************* Statistics Registers ******************************/

uint32_t emacReadStats(void *pD)
{
    CEDI_Statistics *stats;

    if (pD==NULL)
      return EINVAL;

    stats = ((CEDI_Statistics *)(CEDI_PdVar(cfg).statsRegs));

    if (CEDI_PdVar(hwCfg).no_stats)
        return ENOTSUP;

    stats->octetsTxLo = CPS_UncachedRead32(CEDI_RegAddr(octets_txed_bottom));
    stats->octetsTxHi = EMAC_REGS__OCTETS_TXED_TOP__COUNT__READ(
                         CPS_UncachedRead32(CEDI_RegAddr(octets_txed_top)));
    stats->framesTx = CPS_UncachedRead32(CEDI_RegAddr(frames_txed_ok));
    stats->broadcastTx = CPS_UncachedRead32(CEDI_RegAddr(broadcast_txed));
    stats->multicastTx = CPS_UncachedRead32(CEDI_RegAddr(multicast_txed));
    stats->pauseFrTx = EMAC_REGS__PAUSE_FRAMES_TXED__COUNT__READ(
                        CPS_UncachedRead32(CEDI_RegAddr(pause_frames_txed)));
    stats->fr64byteTx = CPS_UncachedRead32(CEDI_RegAddr(frames_txed_64));
    stats->fr65_127byteTx = CPS_UncachedRead32(CEDI_RegAddr(frames_txed_65));
    stats->fr128_255byteTx = CPS_UncachedRead32(CEDI_RegAddr(frames_txed_128));
    stats->fr256_511byteTx = CPS_UncachedRead32(CEDI_RegAddr(frames_txed_256));
    stats->fr512_1023byteTx = CPS_UncachedRead32(CEDI_RegAddr(frames_txed_512));
    stats->fr1024_1518byteTx =
                            CPS_UncachedRead32(CEDI_RegAddr(frames_txed_1024));
    stats->fr1519_byteTx = CPS_UncachedRead32(CEDI_RegAddr(frames_txed_1519));
    stats->underrunFrTx = EMAC_REGS__TX_UNDERRUNS__COUNT__READ(
                            CPS_UncachedRead32(CEDI_RegAddr(tx_underruns)));
    stats->singleCollFrTx =
                        CPS_UncachedRead32(CEDI_RegAddr(single_collisions));
    stats->multiCollFrTx =
                        CPS_UncachedRead32(CEDI_RegAddr(multiple_collisions));
    stats->excessCollFrTx = EMAC_REGS__EXCESSIVE_COLLISIONS__COUNT__READ(
                       CPS_UncachedRead32(CEDI_RegAddr(excessive_collisions)));
    stats->lateCollFrTx = EMAC_REGS__LATE_COLLISIONS__COUNT__READ(
                            CPS_UncachedRead32(CEDI_RegAddr(late_collisions)));
    stats->carrSensErrsTx = EMAC_REGS__CRS_ERRORS__COUNT__READ(
                              CPS_UncachedRead32(CEDI_RegAddr(crs_errors)));
    stats->deferredFrTx = CPS_UncachedRead32(CEDI_RegAddr(deferred_frames));
    stats->alignErrsRx = EMAC_REGS__ALIGNMENT_ERRORS__COUNT__READ(
                        CPS_UncachedRead32(CEDI_RegAddr(alignment_errors)));
    stats->octetsRxLo = CPS_UncachedRead32(CEDI_RegAddr(octets_rxed_bottom));
    stats->octetsRxHi = EMAC_REGS__OCTETS_RXED_TOP__COUNT__READ(
                          CPS_UncachedRead32(CEDI_RegAddr(octets_rxed_top)));
    stats->framesRx = CPS_UncachedRead32(CEDI_RegAddr(frames_rxed_ok));
    stats->broadcastRx = CPS_UncachedRead32(CEDI_RegAddr(broadcast_rxed));
    stats->multicastRx = CPS_UncachedRead32(CEDI_RegAddr(multicast_rxed));
    stats->pauseFrRx = EMAC_REGS__PAUSE_FRAMES_RXED__COUNT__READ(
                        CPS_UncachedRead32(CEDI_RegAddr(pause_frames_rxed)));
    stats->fr64byteRx = CPS_UncachedRead32(CEDI_RegAddr(frames_rxed_64));
    stats->fr65_127byteRx = CPS_UncachedRead32(CEDI_RegAddr(frames_rxed_65));
    stats->fr128_255byteRx = CPS_UncachedRead32(CEDI_RegAddr(frames_rxed_128));
    stats->fr256_511byteRx = CPS_UncachedRead32(CEDI_RegAddr(frames_rxed_256));
    stats->fr512_1023byteRx =
                            CPS_UncachedRead32(CEDI_RegAddr(frames_rxed_512));
    stats->fr1024_1518byteRx =
                            CPS_UncachedRead32(CEDI_RegAddr(frames_rxed_1024));
    stats->fr1519_byteRx =
                            CPS_UncachedRead32(CEDI_RegAddr(frames_rxed_1519));
    stats->undersizeFrRx = EMAC_REGS__UNDERSIZE_FRAMES__COUNT__READ(
                          CPS_UncachedRead32(CEDI_RegAddr(undersize_frames)));
    stats->oversizeFrRx = EMAC_REGS__EXCESSIVE_RX_LENGTH__COUNT__READ(
                    CPS_UncachedRead32(CEDI_RegAddr(excessive_rx_length)));
    stats->jabbersRx = EMAC_REGS__RX_JABBERS__COUNT__READ(
                            CPS_UncachedRead32(CEDI_RegAddr(rx_jabbers)));
    stats->fcsErrorsRx = EMAC_REGS__FCS_ERRORS__COUNT__READ(
                            CPS_UncachedRead32(CEDI_RegAddr(fcs_errors)));
    stats->lenChkErrRx = EMAC_REGS__RX_LENGTH_ERRORS__COUNT__READ(
                          CPS_UncachedRead32(CEDI_RegAddr(rx_length_errors)));
    stats->rxSymbolErrs = EMAC_REGS__RX_SYMBOL_ERRORS__COUNT__READ(
                        CPS_UncachedRead32(CEDI_RegAddr(rx_symbol_errors)));
    stats->rxResourcErrs =
                        CPS_UncachedRead32(CEDI_RegAddr(rx_resource_errors));
    stats->overrunFrRx = EMAC_REGS__RX_OVERRUNS__COUNT__READ(
                            CPS_UncachedRead32(CEDI_RegAddr(rx_overruns)));
    stats->ipChksumErrs = EMAC_REGS__RX_IP_CK_ERRORS__COUNT__READ(
                        CPS_UncachedRead32(CEDI_RegAddr(rx_ip_ck_errors)));
    stats->tcpChksumErrs = EMAC_REGS__RX_TCP_CK_ERRORS__COUNT__READ(
                        CPS_UncachedRead32(CEDI_RegAddr(rx_tcp_ck_errors)));
    stats->udpChksumErrs = EMAC_REGS__RX_UDP_CK_ERRORS__COUNT__READ(
                        CPS_UncachedRead32(CEDI_RegAddr(rx_udp_ck_errors)));
    stats->dmaRxPBufFlush = EMAC_REGS__AUTO_FLUSHED_PKTS__COUNT__READ(
                        CPS_UncachedRead32(CEDI_RegAddr(auto_flushed_pkts)));

/*
    vDbgMsg(DBG_GEN_MSG, 10, "Non-zero Error Stats: %s%u %s%u %s%u %s%u %s%u %s%u %s%u %s%u %s%u %s%u %s%u %s%u %s%u %s%u %s%u %s%u %s%u %s%u %s%u %s%u\n",
        stats->underrunFrTx?"Tx underruns=":"", stats->underrunFrTx,
        stats->singleCollFrTx?"Single coll=":"", stats->singleCollFrTx,
        stats->multiCollFrTx?"Multiple coll=":"", stats->multiCollFrTx,
        stats->excessCollFrTx?"Excessive coll=":"", stats->excessCollFrTx,
        stats->lateCollFrTx?"Late coll=":"", stats->lateCollFrTx,
        stats->deferredFrTx?"Deferred fr=":"", stats->deferredFrTx,
        stats->carrSensErrsTx?"CarrSense errs=":"", stats->carrSensErrsTx,
        stats->undersizeFrRx?"Undersize fr":"", stats->undersizeFrRx,
        stats->oversizeFrRx?"Excess rx len=":"", stats->oversizeFrRx,
        stats->jabbersRx?"Rx jabbers=":"", stats->jabbersRx,
        stats->fcsErrorsRx?"FCS errs=":"", stats->fcsErrorsRx,
        stats->lenChkErrRx?"Rx len errs=":"", stats->lenChkErrRx,
        stats->rxSymbolErrs?"Rx sym errs=":"", stats->rxSymbolErrs,
        stats->alignErrsRx?"Align errs=":"", stats->alignErrsRx,
        stats->rxResourcErrs?"Rx res. errs=":"", stats->rxResourcErrs,
        stats->overrunFrRx?"Rx overruns=":"", stats->overrunFrRx,
        stats->ipChksumErrs?"Rx IP chk errs=":"", stats->ipChksumErrs,
        stats->tcpChksumErrs?"Rx TCP chk errs=":"", stats->tcpChksumErrs,
        stats->udpChksumErrs?"Rx UDP chk errs=":"", stats->udpChksumErrs,
        stats->dmaRxPBufFlush?"Auto flushed pkts=":"", stats->dmaRxPBufFlush );
*/

    return 0;
}

uint32_t emacClearStats(void *pD)
{
    uint32_t reg;
    if (pD==NULL) return EINVAL;

    if (CEDI_PdVar(hwCfg).no_stats)
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__SET(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);
    return 0;
}

uint32_t emacTakeSnapshot(void *pD)
{
    uint32_t reg;

    if (pD==NULL) return EINVAL;
    if (CEDI_PdVar(hwCfg).no_snapshot || CEDI_PdVar(hwCfg).no_stats)
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    EMAC_REGS__NETWORK_CONTROL__STATS_TAKE_SNAP__SET(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);
    return 0;
}

uint32_t emacSetReadSnapshot(void *pD, uint8_t enable)
{
    uint32_t reg;

    if (pD==NULL) return EINVAL;
    if (enable>1) return EINVAL;
    if (CEDI_PdVar(hwCfg).no_snapshot || CEDI_PdVar(hwCfg).no_stats)
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    if (enable)
        EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__SET(reg);
    else
        EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);
    return 0;
}

uint32_t emacGetReadSnapshot(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
        return EINVAL;

    if (CEDI_PdVar(hwCfg).no_snapshot || CEDI_PdVar(hwCfg).no_stats)
        return ENOTSUP;

    *enable = EMAC_REGS__NETWORK_CONTROL__STATS_READ_SNAP__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_control)));
    return 0;
}

/************************ WakeOnLAN/EEE Support ******************************/

uint32_t emacSetWakeOnLanReg(void *pD, CEDI_WakeOnLanReg *regVals)
{
    uint32_t reg = 0;

    if ((pD==NULL) || (regVals==NULL) || (regVals->magPktEn>1) ||
      (regVals->arpEn>1) || (regVals->specAd1En>1) || (regVals->multiHashEn>1))
        return EINVAL;

    EMAC_REGS__WOL_REGISTER__ADDR__MODIFY(reg, regVals->wolReqAddr);
    if (regVals->magPktEn)
        EMAC_REGS__WOL_REGISTER__WOL_MASK_0__SET(reg);
    if (regVals->arpEn)
        EMAC_REGS__WOL_REGISTER__WOL_MASK_1__SET(reg);
    if (regVals->specAd1En)
        EMAC_REGS__WOL_REGISTER__WOL_MASK_2__SET(reg);
    if (regVals->multiHashEn)
        EMAC_REGS__WOL_REGISTER__WOL_MASK_3__SET(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(wol_register), reg);

    return 0;
}

uint32_t emacGetWakeOnLanReg(void *pD, CEDI_WakeOnLanReg *regVals)
{
    uint32_t reg = 0;

    if ((pD==NULL) || (regVals==NULL))
        return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(wol_register));
    regVals->wolReqAddr = EMAC_REGS__WOL_REGISTER__ADDR__READ(reg);
    regVals->magPktEn = EMAC_REGS__WOL_REGISTER__WOL_MASK_0__READ(reg);
    regVals->arpEn = EMAC_REGS__WOL_REGISTER__WOL_MASK_1__READ(reg);
    regVals->specAd1En = EMAC_REGS__WOL_REGISTER__WOL_MASK_2__READ(reg);
    regVals->multiHashEn = EMAC_REGS__WOL_REGISTER__WOL_MASK_3__READ(reg);

    return 0;
}

uint32_t emacSetLpiTxEnable(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return EINVAL;
    if (enable>1) return EINVAL;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    if (enable)
        EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__SET(reg);
    else
        EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);
    return 0;
}

uint32_t emacGetLpiTxEnable(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;

    *enable = EMAC_REGS__NETWORK_CONTROL__TX_LPI_EN__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_control)));
    return 0;
}

uint32_t emacGetLpiStats(void *pD, CEDI_LpiStats *lpiStats)
{
    if ((pD==NULL) || (lpiStats==NULL))
      return EINVAL;

    lpiStats->rxLpiTrans = EMAC_REGS__RX_LPI__COUNT__READ(
            CPS_UncachedRead32(CEDI_RegAddr(rx_lpi)));
    lpiStats->rxLpiTime = EMAC_REGS__RX_LPI_TIME__LPI_TIME__READ(
            CPS_UncachedRead32(CEDI_RegAddr(rx_lpi_time)));
    lpiStats->txLpiTrans = EMAC_REGS__TX_LPI__COUNT__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tx_lpi)));
    lpiStats->txLpiTime = EMAC_REGS__TX_LPI_TIME__LPI_TIME__READ(
            CPS_UncachedRead32(CEDI_RegAddr(tx_lpi_time)));
    return 0;
}

/**************************** Design Config **********************************/

uint32_t emacGetDesignConfig(void *pD, CEDI_DesignCfg *hwCfg)
{
    if ((pD==NULL) || (hwCfg==NULL))
        return EINVAL;

    /* Copy h/w config into user-supplied struct */
    *hwCfg = CEDI_PdVar(hwCfg);
    return 0;
}

/**************************** Debug Functionality ****************************/

uint32_t emacSetWriteStatsEnable(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return EINVAL;
    if (enable>1) return EINVAL;
    if (CEDI_PdVar(hwCfg).no_stats)
        return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    if (enable)
        EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__SET(reg);
    else
        EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);
    return 0;
}

uint32_t emacGetWriteStatsEnable(void *pD, uint8_t *enable)
{
    uint32_t reg;
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;

    if (CEDI_PdVar(hwCfg).no_stats)
        return EINVAL;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    *enable = EMAC_REGS__NETWORK_CONTROL__STATS_WRITE_EN__READ(reg);
    return 0;
}

uint32_t emacIncStatsRegs(void *pD)
{
    uint32_t reg;

    if (pD==NULL) return EINVAL;
    if (CEDI_PdVar(hwCfg).no_stats)
        return EINVAL;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    EMAC_REGS__NETWORK_CONTROL__INC_ALL_STATS_REGS__SET(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);
    return 0;
}

void emacSetRxBackPressure(void *pD, uint8_t enable)
{
    uint32_t ncr;
    if (pD==NULL) return;
    if (enable>1) return;
    ncr = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    if (enable)
        EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__SET(ncr);
    else
        EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__CLR(ncr);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), ncr);
}

uint32_t emacGetRxBackPressure(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;
    *enable= EMAC_REGS__NETWORK_CONTROL__BACK_PRESSURE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_control)));

    return 0;
}

uint32_t emacSetCollisionTest(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return EINVAL;
    if (enable>1) return EINVAL;
    if (CEDI_PdVar(hwCfg).no_pcs)
        return ENOTSUP;
    reg = CPS_UncachedRead32(CEDI_RegAddr(pcs_control));
    if (enable)
        EMAC_REGS__PCS_CONTROL__COLLISION_TEST__SET(reg);
    else
        EMAC_REGS__PCS_CONTROL__COLLISION_TEST__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(pcs_control), reg);
    return 0;
}

uint32_t emacGetCollisionTest(void *pD, uint8_t *enable)
{
    uint32_t reg;
    if ((pD==NULL)||(enable==NULL))
        return EINVAL;

    if (CEDI_PdVar(hwCfg).no_pcs || (enable==NULL))
        return ENOTSUP;
    reg = CPS_UncachedRead32(CEDI_RegAddr(pcs_control));
    *enable = EMAC_REGS__PCS_CONTROL__COLLISION_TEST__READ(reg);
    return 0;
}

void emacSetRetryTest(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (pD==NULL) return;
    if (enable>1) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

uint32_t emacGetRetryTest(void *pD, uint8_t *enable)
{
    if ((pD==NULL)||(enable==NULL))
      return EINVAL;
    *enable= EMAC_REGS__NETWORK_CONFIG__RETRY_TEST__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

uint32_t emacWriteUserOutputs(void *pD, uint16_t outVal)
{
    uint32_t tmp;
    if (pD==NULL) return EINVAL;
    if (0==CEDI_PdVar(hwCfg).user_io)
        return ENOTSUP;

    tmp = 0;
    EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__MODIFY(
            tmp, outVal);
    CPS_UncachedWrite32(CEDI_RegAddr(user_io_register), tmp);
    return 0;
}

uint32_t emacReadUserOutputs(void *pD, uint16_t *outVal)
{
    uint32_t reg;
    if ((pD==NULL) || (outVal==NULL))
        return EINVAL;
    if (0==CEDI_PdVar(hwCfg).user_io)
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(user_io_register));
    *outVal = EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__READ(reg);
    return 0;
}

uint32_t emacSetUserOutPin(void *pD, uint8_t pin, uint8_t state)
{
    uint32_t reg, val;
    if (pD==NULL) return EINVAL;
    if (0==CEDI_PdVar(hwCfg).user_io)
        return ENOTSUP;
    if (pin>=CEDI_PdVar(hwCfg).user_out_width)
        return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(user_io_register));
    val = EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__READ(reg);
    if (state) {
        val |= (1<<pin);
    }
    else {
        val &= ~(1<<pin);
    }
    EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_OUTPUTS__MODIFY(
            reg, val);
    CPS_UncachedWrite32(CEDI_RegAddr(user_io_register), reg);
    return 0;
}

uint32_t emacReadUserInputs(void *pD, uint16_t *inVal)
{
    uint32_t reg;
    if ((pD==NULL) || (inVal==NULL))
        return EINVAL;
    if (0==CEDI_PdVar(hwCfg).user_io)
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(user_io_register));
    *inVal = EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_INPUTS__READ(reg);
    return 0;
}

uint32_t emacGetUserInPin(void *pD, uint8_t pin, uint8_t *state)
{
    uint32_t reg, val;
    if ((pD==NULL) || (state==NULL))
        return EINVAL;
    if (0==CEDI_PdVar(hwCfg).user_io)
        return ENOTSUP;
    if (pin>=CEDI_PdVar(hwCfg).user_in_width)
        return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(user_io_register));
    val = EMAC_REGS__USER_IO_REGISTER__USER_PROGRAMMABLE_INPUTS__READ(reg);
    *state = (val & (1<<pin))?1:0;
    return 0;
}

uint32_t emacGetMdioInState(void *pD, uint8_t *state)
{
    if ((pD==NULL)||(state==NULL))
      return EINVAL;
    *state= EMAC_REGS__NETWORK_STATUS__MDIO_IN__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_status)));

    return 0;
}

uint32_t emacReadReg(void *pD, uint32_t offs, uint32_t *data)
{
    if ((pD==NULL) || (data==NULL) || (offs>=sizeof(struct emac_regs)))
        return EINVAL;

    *data = CPS_UncachedRead32((uint32_t *)(CEDI_PdVar(cfg).regBase + offs));
    return 0;
}

uint32_t emacWriteReg(void *pD, uint32_t offs, uint32_t data)
{
    if ((pD==NULL) || (offs>=sizeof(struct emac_regs)))
        return EINVAL;

    CPS_UncachedWrite32((uint32_t *)(CEDI_PdVar(cfg).regBase + offs), data);
    return 0;
}


CEDI_OBJ EmacDrv = {
    emacProbe,               // probe
    emacInit,                 // init
    emacDestroy,             // destroy
    emacStart,               // start
    emacStop,                // stop
    emacIsr,                 // isr
    emacSetEventEnable,
    emacGetEventEnable,
    emacSetIntrptModerate,
    emacGetIntrptModerate,
    emacSetIfSpeed,
    emacGetIfSpeed,
    emacSetJumboFramesRx,
    emacGetJumboFramesRx,
    emacSetJumboFrameRxMaxLen,
    emacGetJumboFrameRxMaxLen,
    emacSetUniDirEnable,
    emacGetUniDirEnable,
    emacSetTxChecksumOffload,
    emacGetTxChecksumOffload,
    emacSetRxBufOffset,
    emacGetRxBufOffset,
    emacSet1536ByteFramesRx,
    emacGet1536ByteFramesRx,
    emacSetRxChecksumOffload,
    emacGetRxChecksumOffload,
    emacSetFcsRemove,
    emacGetFcsRemove,
    emacSetTxPartialStFwd,
    emacGetTxPartialStFwd,
    emacSetRxPartialStFwd,
    emacGetRxPartialStFwd,
    emacSetRxDmaDataAddrMask,
    emacGetRxDmaDataAddrMask,
    emacSetRxBadPreamble,
    emacGetRxBadPreamble,
    emacSetFullDuplex,
    emacGetFullDuplex,
    emacSetIgnoreFcsRx,
    emacGetIgnoreFcsRx,
    emacSetRxHalfDuplexInTx,
    emacGetRxHalfDuplexInTx,
    emacGetIfCapabilities,
    emacSetLoopback,
    emacGetLoopback,

    emacCalcMaxTxFrameSize,
    emacQueueTxBuf,
    emacQTxBuf,
    emacDeQTxBuf,
    emacTxDescFree,
    emacFreeTxDesc,
    emacGetTxDescStat,
    emacGetTxDescSize,
    emacResetTxQ,
    emacStartTx,
    emacStopTx,
    emacAbortTx,
    emacTransmitting,
    emacEnableTx,
    emacGetTxEnabled,
    emacGetTxStatus,
    emacClearTxStatus,
    emacEnableCbs,
    emacDisableCbs,
    emacGetCbsQSetting,
    emacSetIpgStretch,
    emacGetIpgStretch,

    emacCalcMaxRxFrameSize,
    emacAddRxBuf,
    emacNumRxBufs,
    emacNumRxUsed,
    emacReadRxBuf,
    emacGetRxDescStat,
    emacGetRxDescSize,
    emacRxEnabled,
    emacEnableRx,
    emacDisableRx,
    emacRemoveRxBuf,
    emacResetRxQ,
    emacGetRxStatus,
    emacClearRxStatus,
    emacSetHdrDataSplit,
    emacGetHdrDataSplit,
    emacSetRscEnable,
    emacGetRscEnable,
    emacSetRscClearMask,
    emacSetSpecificAddr,
    emacGetSpecificAddr,
    emacSetSpecificAddr1Mask,
    emacGetSpecificAddr1Mask,
    emacDisableSpecAddr,
    emacSetTypeIdMatch,
    emacGetTypeIdMatch,
    emacSetUnicastEnable,
    emacGetUnicastEnable,
    emacSetMulticastEnable,
    emacGetMulticastEnable,
    emacSetNoBroadcast,
    emacGetNoBroadcast,
    emacSetVlanOnly,
    emacGetVlanOnly,
    emacSetStackedVlanReg,
    emacGetStackedVlanReg,
    emacSetCopyAllFrames,
    emacGetCopyAllFrames,
    emacSetHashAddr,
    emacGetHashAddr,
    emacSetLenErrDiscard,
    emacGetLenErrDiscard,
    emacGetNumScreenRegs,
    emacSetType1ScreenReg,
    emacGetType1ScreenReg,
    emacSetType2ScreenReg,
    emacGetType2ScreenReg,
    emacSetType2EthertypeReg,
    emacGetType2EthertypeReg,
    emacSetType2CompareReg,
    emacGetType2CompareReg,

    emacSetPauseEnable,
    emacGetPauseEnable,
    emacTxPauseFrame,
    emacTxZeroQPause,
    emacGetRxPauseQuantum,
    emacSetTxPauseQuantum,
    emacGetTxPauseQuantum,
    emacSetCopyPauseDisable,
    emacGetCopyPauseDisable,
    emacSetPfcPriorityBasedPauseRx,
    emacGetPfcPriorityBasedPauseRx,
    emacTxPfcPriorityBasedPause,
    emacSetTxPfcPauseFrameFields,
    emacGetTxPfcPauseFrameFields,
    emacSetEnableMultiPfcPauseQuantum,
    emacGetEnableMultiPfcPauseQuantum,

    emacSetUnicastPtpDetect,
    emacGetUnicastPtpDetect,
    emacSetPtpRxUnicastIpAddr,
    emacGetPtpRxUnicastIpAddr,
    emacSetPtpTxUnicastIpAddr,
    emacGetPtpTxUnicastIpAddr,
    emacSet1588Timer,
    emacGet1588Timer,
    emacAdjust1588Timer,
    emacSet1588TimerInc,
    emacGet1588TimerInc,
    emacSetTsuTimerCompVal,
    emacGetTsuTimerCompVal,
    emacGetPtpFrameTxTime,
    emacGetPtpFrameRxTime,
    emacGetPtpPeerFrameTxTime,
    emacGetPtpPeerFrameRxTime,
    emacGet1588SyncStrobeTime,
    emacSetExtTsuPortEnable,
    emacGetExtTsuPortEnable,
    emacSet1588OneStepTxSyncEnable,
    emacGet1588OneStepTxSyncEnable,
    emacSetDescTimeStampMode,
    emacGetDescTimeStampMode,
    emacSetStoreRxTimeStamp,
    emacGetStoreRxTimeStamp,

    emacResetPcs,
    emacGetPcsReady,
    emacStartAutoNegotiation,
    emacSetAutoNegEnable,
    emacGetAutoNegEnable,
    emacGetLinkStatus,
    emacGetAnRemoteFault,
    emacGetAnComplete,
    emacSetAnAdvPage,
    emacGetAnAdvPage,
    emacGetLpAbilityPage,
    emacGetPageRx,
    emacSetNextPageTx,
    emacGetNextPageTx,
    emacGetLpNextPage,

    emacGetPhyId,
    emacSetMdioEnable,
    emacGetMdioEnable,
    emacPhyStartMdioWrite,
    emacPhyStartMdioRead,
    emacGetMdioReadData,
    emacGetMdioIdle,

    emacReadStats,
    emacClearStats,
    emacTakeSnapshot,
    emacSetReadSnapshot,
    emacGetReadSnapshot,
    emacSetWakeOnLanReg,
    emacGetWakeOnLanReg,
    emacSetLpiTxEnable,
    emacGetLpiTxEnable,
    emacGetLpiStats,
    emacGetDesignConfig,

    emacSetWriteStatsEnable,
    emacGetWriteStatsEnable,
    emacIncStatsRegs,
    emacSetRxBackPressure,
    emacGetRxBackPressure,
    emacSetCollisionTest,
    emacGetCollisionTest,
    emacSetRetryTest,
    emacGetRetryTest,
    emacWriteUserOutputs,
    emacReadUserOutputs,
    emacSetUserOutPin,
    emacReadUserInputs,
    emacGetUserInPin,
    emacGetMdioInState,
    emacReadReg,
    emacWriteReg,
};

CEDI_OBJ *CEDI_GetInstance(void) {
    return &EmacDrv;
}

#ifdef __cplusplus
}
#endif

#endif /* CY_IP_MXETH */


