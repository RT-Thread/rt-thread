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
 * edd_rx.c
 * Ethernet DMA MAC Driver
 *
 * Rx-related functions source file
 *****************************************************************************/
/****************************************************************************
* Modification by Infineon: To make this file compile with ModusToolbox
* toolchain
*****************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_MXETH)

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
/******************************************************************************
 * Driver API functions
 *****************************************************************************/

/* Identify max Rx pkt size for queues - determined by size of Rx packet buffer
 * (if using full store & forward mode), and the current maximum frame size,
 * e.g. 1518, 1536 or jumbo frame.
 * @param pD - driver private state info specific to this instance
 * @param maxSize - pointer for returning max frame size, same for each Rx queue
 * @return 0 if successful
 * @return EINVAL if invalid parameters
 */
uint32_t emacCalcMaxRxFrameSize(void *pD, uint32_t *maxSize) {
    uint16_t ram_word_size, ram_addr_bits;
    uint32_t ram_size, max_size, tmp;
    uint8_t enabled = 0;
    uint16_t length;

    if ((pD==NULL) || (maxSize==NULL)) return EINVAL;

    if (0!=emacGetJumboFramesRx(pD,&enabled))
        return EINVAL;

    if (enabled) {
        if (0!=emacGetJumboFrameRxMaxLen(pD, &length))
            return EINVAL;
        max_size = length;
    } else {
        if (0!=emacGet1536ByteFramesRx(pD,&enabled))
            return EINVAL;
        if (enabled)
            max_size = 1536;
        else
            max_size = 1518;
    }

    if (0!=emacGetRxPartialStFwd(pD, &tmp, &enabled))
        return EINVAL;

    if ((!enabled) && CEDI_PdVar(hwCfg).rx_pkt_buffer)
    {
        // What is word size of SRAM in bytes
        ram_word_size = (CEDI_PdVar(hwCfg).rx_pbuf_data >> 1)+1;
        //vDbgMsg(DBG_GEN_MSG, 10, "RAM word size = %u (x32 bits)\n", CEDI_PdVar(hwCfg).rx_pbuf_data);
        ram_addr_bits = CEDI_PdVar(hwCfg).rx_pbuf_addr;
        //vDbgMsg(DBG_GEN_MSG, 10, "RAM Rx addr bits = %u\n", ram_addr_bits);

        ram_size = (1<<(ram_addr_bits + ram_word_size + 1)) - 96;
        vDbgMsg(DBG_GEN_MSG, 10, "RAM size = %u\n", ram_size);

        if (ram_size<max_size)
            max_size = ram_size;
    }
    vDbgMsg(DBG_GEN_MSG, 10, "Max Rx frame size = %u\n", max_size);

    *maxSize = max_size;
    return 0;
}

/* Add a buffer (size determined by rxBufLength in CEDI_Config) to the end of
 * the receive buffer queue.  This function is intended to be used during
 * setting up the receive buffers, and should not be called while Rx is
 * enabled or unread data remains in the queue.
 * @param pD - driver private state info specific to this instance
 * @param queueNum - number of the Rx queue (range 0 to rxQs-1)
 * @param buf - pointer to struct for virtual and physical addresses of buffer.
 *      Physical address checked for word-alignment in 64/128-bit width cases.
 * @param init - if <>0 then initialise the buffer data to all zeros
 * @return 0 if successful, EINVAL if invalid queueNum, buffer alignment, or
 *    bufStart pointer/addresses
 */
uint32_t emacAddRxBuf(void *pD, uint8_t queueNum, CEDI_BuffAddr *buf, uint8_t init)
{
    uint32_t tmp, bufLenWords;
    rxQueue_t *rxQ;

    if (!pD) return EINVAL;

    if (queueNum>=(CEDI_PdVar(cfg)).rxQs) {
        vDbgMsg(DBG_GEN_MSG, 5, "Error: Invalid Rx queue number: %u\n", queueNum);
        return EINVAL;
    }

    if ((buf==0) || (buf->vAddr==0) || (buf->pAddr==0)) {
        vDbgMsg(DBG_GEN_MSG, 5, "%s\n", "Error: NULL buf parameter");
        return EINVAL;
    }
//    vDbgMsg(DBG_GEN_MSG, 10, "%s entered (regBase %08X) bufV=0x%08X bufP=0x%08X\n", __func__,
//            CEDI_PdVar(cfg).regBase, buf->vAddr, buf->pAddr);

    rxQ = &(CEDI_PdVar(rxQueue[queueNum]));

    if (rxQ->numRxBufs>=((CEDI_PdVar(cfg)).rxQLen[queueNum])) {
        vDbgMsg(DBG_GEN_MSG, 5, "%s\n", "Error: Rx descriptor list full");
        return EINVAL;
    }

    /* alignment checking */
    switch (CEDI_PdVar(cfg).dmaBusWidth) {
    case CEDI_DMA_BUS_WIDTH_32:
        tmp = 4; break;
    case CEDI_DMA_BUS_WIDTH_64:
        tmp = 8; break;
    case CEDI_DMA_BUS_WIDTH_128:
        tmp = 16; break;
    default: tmp = 4; break;
    }
    if ((buf->pAddr)%tmp) {
        vDbgMsg(DBG_GEN_MSG, 5, "%s\n", "Error: Rx buffer not word-aligned");
        return EINVAL;
    }

    /* save virtual address */
    *(rxQ->rxEndVA) = buf->vAddr;

    bufLenWords = (CEDI_PdVar(cfg).rxBufLength[queueNum])<<4;
    if (init)
        for (tmp=0; tmp<bufLenWords; tmp++)
            CPS_UncachedWrite32((uint32_t *)(buf->vAddr)+tmp, 0);

    /* clear wrap & used on old end, add new buffer */
    CPS_UncachedWrite32(&(rxQ->rxDescEnd->word[0]),
                            buf->pAddr & CEDI_RXD_ADDR_MASK);
    /* upper 32 bits if 64 bit addressing */
    if (CEDI_PdVar(cfg).dmaAddrBusWidth) {
#ifdef CEDI_64B_COMPILE
        /* 64-bit addressing */
        CPS_UncachedWrite32(&(rxQ->rxDescEnd->word[2]),
                             (buf->pAddr & 0xFFFFFFFF00000000)>>32);
#else
        /* 32-bit addressing */
        CPS_UncachedWrite32(&(rxQ->rxDescEnd->word[2]), 0x00000000);
#endif
    }

    /* put known pattern into word[1] for debugging */
    CPS_UncachedWrite32(&(rxQ->rxDescEnd->word[1]), CEDI_RXD_EMPTY);

    /* inc end & stop pointer */
    rxQ->rxDescEnd = (rxDesc *)(((uintptr_t)rxQ->rxDescEnd) +
            (CEDI_PdVar(rxDescriptorSize)));
    rxQ->rxDescStop = rxQ->rxDescEnd;

    /* inc VA end & stop pointers & buffer count */
    rxQ->rxEndVA++;
    rxQ->rxStopVA++;
    *(rxQ->rxStopVA) = 0;
    rxQ->numRxBufs++;

    /* write new end(-stop) descriptor */
    CPS_UncachedWrite32(&(rxQ->rxDescEnd->word[0]),
                             CEDI_RXD_WRAP | CEDI_RXD_USED );

    return 0;
}

/* Get the number of useable buffers/descriptors present in the specified
 * Rx queue, excluding the end-stop descriptor.
 * @param pD - driver private state info specific to this instance
 * @param queueNum - number of the Rx queue (range 0 to rxQs-1)
 * @param numBufs - pointer for returning number of descriptors
 * @return 0 if successful
 * @return EINVAL if invalid parameter
 */
uint32_t emacNumRxBufs(void *pD, uint8_t queueNum, uint16_t *numBufs)
{
    if ((pD==NULL) || (numBufs==NULL) || (queueNum>=(CEDI_PdVar(cfg)).rxQs))
        return EINVAL;

    *numBufs = (CEDI_PdVar(rxQueue[queueNum])).numRxBufs;
    return 0;
}

/* Get the number of buffers/descriptors marked "used" in the specified Rx
 *   queue (excluding unuseable end-stop), i.e. those holding unread data.
 * @param pD - driver private state info specific to this instance
 * @param queueNum - number of the Rx queue (range 0 to rxQs-1)
 * @return number of used buffers
 * @return 0 if invalid parameter
 */
uint32_t emacNumRxUsed(void *pD, uint8_t queueNum)
{
    uint32_t tmp, thisWd, count=0;
    rxDesc *thisDesc;
    rxQueue_t *rxQ;

    if ((pD==NULL) || (queueNum>=(CEDI_PdVar(cfg)).rxQs))
        return 0;

    rxQ = &(CEDI_PdVar(rxQueue[queueNum]));
    /* count forward from tail, until used not set */
    thisDesc =  rxQ->rxDescTail;
    for (tmp = 0; tmp<rxQ->numRxBufs; tmp++)
    {
        thisWd = CPS_UncachedRead32(&(thisDesc->word[0]));
        if (thisWd & CEDI_RXD_USED)
            count++;
        else
            break;
        if (thisWd & CEDI_RXD_WRAP)
            thisDesc = rxQ->rxDescStart;
        else
            thisDesc = (rxDesc *)(((uintptr_t)(thisDesc))
                                    + (CEDI_PdVar(rxDescriptorSize)));
    }
    return count;
}

/**
 * Read first unread descriptor (at tail of queue): if new data is available
 * it swaps out the buffer and replaces it with a new one, clears the
 * descriptor for re-use, then updates the driver queue-pointer.
 * Checks for Start Of Frame (SOF) and End Of Frame (EOF) flags in the
 * descriptors, passing back in return value.
 * If EOF set, the descriptor status is returned via rxDescStat.
 * @param[in] pD driver private state info specific to this instance
 * @param[in] queueNum
 *   number of the Rx queue
 * @param[in,out] buf pointer to address of memory for new buffer to add to Rx
 *   descriptor queue, if data is available the buffer addresses for this are
 *   returned in buf, else if no data available the new buffer can be re-used.
 *   Physical address of buffer is checked for word-alignment in 64/128-bit
 *   width cases.
 * @param[in] init if >0 then initialise the (new) buffer data to all zeros.
 *    Ignored if no data available.
 * @param[out] descData pointer for returning status & descriptor data
 *   Struct fields:
 *
 *    uint32_t rxDescStat  - Rx descriptor status word
 *
 *    uint8_t status    - Rx data status, one of the following values:
 *      CEDI_RXDATA_SOF_EOF  :data available, single-buffer frame (SOF & EOF
 *                            set)
 *      CEDI_RXDATA_SOF_ONLY :data available, start of multi-buffer frame
 *      CEDI_RXDATA_NO_FLAG  :data available, intermediate buffer of multi-
 *                            buffer frame
 *      CEDI_RXDATA_EOF_ONLY :data available, end of multi-buffer frame
 *      CEDI_RXDATA_NODATA   :no data available
 *
 *    CEDI_TimeStampData rxTsData - Rx descriptor timestamp when valid
 *                                  (rxTsData->tsValid will be set to 1)
 *
 * @return 0 if successful,
 * @return EINVAL if invalid queueNum, buf, rxDescStat or
 *    status parameters
 */
uint32_t emacReadRxBuf(void *pD, uint8_t queueNum, CEDI_BuffAddr *buf,
                        uint8_t init, CEDI_RxDescData *descData)
{
    uint32_t tmp, bufLenWords, descWd0;
    CEDI_BuffAddr oldbuf;
    uint8_t wdNum, tailWrap;
    uint32_t tsLowerWd, tsUpperWd;
    rxQueue_t *rxQ;

    if (!pD) return EINVAL;

//    vDbgMsg(DBG_GEN_MSG, 10, "%s entered (regBase %08lX)\n", __func__,
//                CEDI_PdVar(cfg).regBase);

    if (buf==NULL) {
        vDbgMsg(DBG_GEN_MSG, 5, "%s\n", "Error: NULL buf parameter");
        return EINVAL;
    }

    if (descData==NULL) {
        vDbgMsg(DBG_GEN_MSG, 5, "%s\n", "Error: NULL descData parameter");
        return EINVAL;
    }

    if (queueNum>=(CEDI_PdVar(cfg)).rxQs) {
        vDbgMsg(DBG_GEN_MSG, 5, "Error: Invalid Rx queue number - %u\n", queueNum);
        return EINVAL;
    }

    if ((buf->vAddr==0) || (buf->pAddr==0)) {
        vDbgMsg(DBG_GEN_MSG, 5, "%s\n", "Error: NULL buf address");
        return EINVAL;
    }

    /* alignment checking for new buffer */
    switch (CEDI_PdVar(cfg).dmaBusWidth) {
    case CEDI_DMA_BUS_WIDTH_32:
        tmp = 4; break;
    case CEDI_DMA_BUS_WIDTH_64:
        tmp = 8; break;
    case CEDI_DMA_BUS_WIDTH_128:
        tmp = 16; break;
    default: tmp = 4; break;
    }
    if ((buf->pAddr)%tmp) {
        vDbgMsg(DBG_GEN_MSG, 5, "%s\n", "Error: Rx buffer not word-aligned");
        return EINVAL;
    }

    rxQ = &(CEDI_PdVar(rxQueue[queueNum]));

    /* get first descriptor & test used bit */
    descWd0 = CPS_UncachedRead32(&(rxQ->rxDescTail->word[0]));

    if (descWd0 & CEDI_RXD_USED) {
        /* new data received - read & process descriptor */

        /* get old physical address */
        oldbuf.pAddr = descWd0 & CEDI_RXD_ADDR_MASK;

#ifdef CEDI_64B_COMPILE
        /* upper 32 bits if 64 bit addressing */
        if (CEDI_PdVar(cfg).dmaAddrBusWidth)
            oldbuf.pAddr |= ((uint64_t)CPS_UncachedRead32(
                                        &(rxQ->rxDescTail->word[2])))<<32;
#endif

        /* get old virtual address & clear from list */
        oldbuf.vAddr = *(rxQ->rxTailVA);
        *(rxQ->rxTailVA) = 0;

        /* save new virtual address */
        *(rxQ->rxStopVA) = buf->vAddr;

        bufLenWords = (CEDI_PdVar(cfg).rxBufLength[queueNum])<<4;
        if (init)
            for (tmp=0; tmp<bufLenWords; tmp++)
                CPS_UncachedWrite32((uint32_t *)(buf->vAddr+4*tmp), 0);

        /* read Rx status */
        descData->rxDescStat = CPS_UncachedRead32(&(rxQ->rxDescTail->word[1]));

        /* extract timestamp if available */
        if ((CEDI_PdVar(cfg).enRxExtBD) && (descWd0 & CEDI_RXD_TS_VALID)) {
        uint32_t reg;
            descData->rxTsData.tsValid = 1;
                        // position depends on 32/64 bit addr
            wdNum = (CEDI_PdVar(cfg).dmaAddrBusWidth)?4:2;

            tsLowerWd = CPS_UncachedRead32(&(rxQ->rxDescTail->word[wdNum]));
            tsUpperWd = CPS_UncachedRead32(&(rxQ->rxDescTail->word[wdNum+1]));

            descData->rxTsData.tsNanoSec = tsLowerWd & CEDI_TS_NANO_SEC_MASK;
            descData->rxTsData.tsSecs =
                    (((tsUpperWd & CEDI_TS_SEC1_MASK)<<CEDI_TS_SEC1_POS_SHIFT)
                        | (tsLowerWd >> CEDI_TS_SEC0_SHIFT));

        /* The timestamp only contains lower few bits of seconds, so add value from 1588 timer */
        reg =  CPS_UncachedRead32(CEDI_RegAddr(tsu_timer_sec));
        /* If the top bit is set in the timestamp, but not in 1588 timer, it has rolled over, so subtract max size */
        if ((descData->rxTsData.tsSecs & (CEDI_TS_SEC_TOP>>1)) && !(reg & (CEDI_TS_SEC_TOP>>1))) {
        descData->rxTsData.tsSecs -= (CEDI_TS_SEC_TOP<<1);

        }
        descData->rxTsData.tsSecs += ((~CEDI_TS_SEC_MASK) & EMAC_REGS__TSU_TIMER_SEC__TIMER__READ(reg));
    }
    else
    {
        descData->rxTsData.tsValid = 0;
    }

        /* save this for later */
        tailWrap = descWd0 & CEDI_RXD_WRAP;

                /* write back to descriptors */
        CPS_UncachedWrite32(&(rxQ->rxDescTail->word[1]), CEDI_RXD_EMPTY);
        /* zero buf physical address & set used - this will be new end-stop */
        CPS_UncachedWrite32(&(rxQ->rxDescTail->word[0]),
                                CEDI_RXD_USED | (tailWrap?CEDI_RXD_WRAP:0));

        /* handle old "stop" descriptor now */
        /* insert new buf physical address & clear used */
        descWd0 = CPS_UncachedRead32(&(rxQ->rxDescStop->word[0]));
        descWd0 = ((buf->pAddr) & CEDI_RXD_ADDR_MASK) |
                    (descWd0 & CEDI_RXD_WRAP);
        CPS_UncachedWrite32(&(rxQ->rxDescStop->word[0]), descWd0);
        /* upper 32 bits if 64 bit addressing */
        if (CEDI_PdVar(cfg).dmaAddrBusWidth) {
#ifdef CEDI_64B_COMPILE
            /* 64-bit addressing */
            CPS_UncachedWrite32(&(rxQ->rxDescStop->word[2]),
                             (buf->pAddr & 0xFFFFFFFF00000000)>>32);
#else
            /* 32-bit addressing */
            CPS_UncachedWrite32(&(rxQ->rxDescStop->word[2]), 0x00000000);
#endif
        }

        /* update pointers */
        rxQ->rxDescStop = rxQ->rxDescTail;
        rxQ->rxStopVA = rxQ->rxTailVA;
        if (tailWrap) {
            rxQ->rxDescTail = rxQ->rxDescStart;
            rxQ->rxTailVA = rxQ->rxBufVAddr;
        }
        else {
            rxQ->rxDescTail = (rxDesc *)(((uintptr_t)(rxQ->rxDescTail))
                                        + (CEDI_PdVar(rxDescriptorSize)));
            rxQ->rxTailVA++;
        }

        /* return old buffer addresses */
        buf->pAddr = oldbuf.pAddr;
        buf->vAddr = oldbuf.vAddr;
/*        vDbgMsg(DBG_GEN_MSG, 10, "%s vAddr=%p pAddr=%p\n",
                      __func__, (void *)buf->vAddr, (void *)buf->pAddr);*/


        /* work out read frame status */
        if ((descData->rxDescStat) & CEDI_RXD_SOF) {
            if ((descData->rxDescStat) & CEDI_RXD_EOF)
                descData->status = CEDI_RXDATA_SOF_EOF;
            else
                descData->status = CEDI_RXDATA_SOF_ONLY;
        }
        else
        {
            if ((descData->rxDescStat) & CEDI_RXD_EOF)
                descData->status = CEDI_RXDATA_EOF_ONLY;
            else
                descData->status = CEDI_RXDATA_NO_FLAG;
        }
    }
    else
        descData->status = CEDI_RXDATA_NODATA;

    return 0;
}

/* Decode the Rx descriptor status into a bit-field struct
 * @param pD - driver private state info specific to this instance
 * @param rxDStatWord - Rx descriptor status word
 * @param rxDStat - pointer to bit-field struct for decoded status fields
 */
void emacGetRxDescStat(void *pD, uint32_t rxDStatWord, CEDI_RxDescStat *rxDStat)
{
    uint32_t reg, wd1;

    if ((NULL==pD) || (NULL==rxDStat)) return;

    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));

    wd1 = rxDStatWord;
    rxDStat->bufLen = wd1 & CEDI_RXD_LEN_MASK;
    if (EMAC_REGS__NETWORK_CONFIG__JUMBO_FRAMES__READ(reg) ||
        (EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__READ(reg)==0)) {
        rxDStat->bufLen |= wd1 & CEDI_RXD_LEN13_FCS_STAT;
        rxDStat->fcsStatus = 0;
    }
    else
        rxDStat->fcsStatus = (wd1 & CEDI_RXD_LEN13_FCS_STAT)?1:0;

    rxDStat->sof = (wd1 & CEDI_RXD_SOF)?1:0;
    rxDStat->eof = (wd1 & CEDI_RXD_EOF)?1:0;
    rxDStat->header = (!rxDStat->eof && (wd1 & CEDI_RXD_HDR))?1:0;
    rxDStat->eoh = (!rxDStat->eof && (wd1 & CEDI_RXD_EOH))?1:0;
    rxDStat->vlanTagDet = (wd1 & CEDI_RXD_VLAN_TAG)?1:0;
    rxDStat->cfi = ((wd1 & CEDI_RXD_CFI) && rxDStat->vlanTagDet)?1:0;
    if (rxDStat->vlanTagDet)
        rxDStat->vlanPri =
                (wd1 & CEDI_RXD_VLAN_PRI_MASK)>>CEDI_RXD_VLAN_PRI_SHIFT;
    else
        rxDStat->vlanPri = 0;
    rxDStat->priTagDet = (wd1 & CEDI_RXD_PRI_TAG)?1:0;
    if (EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__READ(reg)) {
        rxDStat->chkOffStat = (wd1 & CEDI_RXD_TYP_IDR_CHK_STA_MASK)\
                                    >>CEDI_RXD_TYP_IDR_CHK_STA_SHIFT;
        rxDStat->snapNoVlanCfi = (wd1 & CEDI_RXD_TYP_MAT_SNP_NCFI)?1:0;
        rxDStat->typeMatchReg = 0;
        rxDStat->typeIdMatch = 0;
    }
    else {
        rxDStat->chkOffStat = 0;
        rxDStat->snapNoVlanCfi = 0;
        rxDStat->typeMatchReg = (wd1 & CEDI_RXD_TYP_IDR_CHK_STA_MASK)\
                                    >>CEDI_RXD_TYP_IDR_CHK_STA_SHIFT;
        rxDStat->typeIdMatch = (wd1 & CEDI_RXD_TYP_MAT_SNP_NCFI)?1:0;
    }

    rxDStat->specAddReg = (wd1 & CEDI_RXD_SPEC_REG_MASK)\
                                >>CEDI_RXD_SPEC_REG_SHIFT;
    if (CEDI_PdVar(hwCfg).rx_pkt_buffer &&
            (CEDI_PdVar(hwCfg).num_spec_add_filters>4))
    {   /* extra spec. addr matching variation */
        rxDStat->specAddReg += ((wd1 & CEDI_RXD_SPEC_ADD_MAT)?1:0) << 2;
        rxDStat->specAddMatch = (wd1 & CEDI_RXD_EXT_ADD_MAT)?1:0;
        rxDStat->extAddrMatch = 0;
    }
    else
    {
        rxDStat->specAddMatch = (wd1 & CEDI_RXD_SPEC_ADD_MAT)?1:0;
        rxDStat->extAddrMatch = (wd1 & CEDI_RXD_EXT_ADD_MAT)?1:0;
    }
    rxDStat->uniHashMatch = (wd1 & CEDI_RXD_UNI_HASH_MAT)?1:0;
    rxDStat->multiHashMatch = (wd1 & CEDI_RXD_MULTI_HASH_MAT)?1:0;
    rxDStat->broadcast = (wd1 & (uint32_t)CEDI_RXD_BROADCAST_DET)?1:0;
}

/* Provide the size of descriptor calculated for the current configuration.
 * @param pD - driver private state info specific to this instance
 * @param rxDescSize - pointer to Rx descriptor Size
 */
void emacGetRxDescSize(void *pD, uint32_t *rxDescSize)
{
    if ((pD==NULL)||(rxDescSize==NULL))
        return;
    *rxDescSize = CEDI_PdVar(rxDescriptorSize);
}

/* Get state of receiver
 * @param pD - driver private state info specific to this instance
 * @return 1 if enabled
 * @return 0 if disabled or pD==NULL
 */
uint32_t emacRxEnabled(void *pD)
{
    uint32_t reg;
    if (pD==NULL) return 0;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    return EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__READ(reg);
}

/* Enable the receive circuit.
 * @param pD - driver private state info specific to this instance
 */
void emacEnableRx(void *pD)
{
    uint32_t reg;
    if (!pD) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__SET(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);
}

/* Disable the receive circuit.
 * @param pD - driver private state info specific to this instance
 */
void emacDisableRx(void *pD)
{
    uint32_t reg;
    if (!pD) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_control));
    EMAC_REGS__NETWORK_CONTROL__ENABLE_RECEIVE__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_control), reg);
}

/* Remove a buffer from the end of the receive buffer queue.  This function is
 * intended to be used when shutting down the driver, prior to deallocating the
 * receive buffers, and should not be called while Rx is enabled or unread
 * data remains in the queue.
 * @param pD - driver private state info specific to this instance
 * @param queueNum - number of the Rx queue (range 0 to rxQs-1)
 * @param buf - pointer to struct for returning virtual and physical addresses
 *  of buffer.
 * @return 0 if successful
 * @return EINVAL if invalid queueNum, ENOENT if no buffers left to free
 */
uint32_t emacRemoveRxBuf(void *pD, uint8_t queueNum, CEDI_BuffAddr *buf)
{
    uint32_t tmp;
    rxQueue_t *rxQ;

    if (!pD) return EINVAL;

    if (queueNum>=(CEDI_PdVar(cfg)).rxQs) {
        vDbgMsg(DBG_GEN_MSG, 5, "Error: Invalid Rx queue number: %u\n", queueNum);
        return EINVAL;
    }

    if (buf==0) {
        vDbgMsg(DBG_GEN_MSG, 5, "%s\n", "Error: NULL buf parameter");
        return EINVAL;
    }

    rxQ = &(CEDI_PdVar(rxQueue[queueNum]));

    if (0==rxQ->numRxBufs)
        return ENOENT;

    /* skip "stop" descriptor since no buffer there */
    if ((rxQ->rxDescEnd==rxQ->rxDescStop) && (rxQ->rxDescEnd!=rxQ->rxDescStart))
    {
        rxQ->rxDescEnd = (rxDesc*)
                ((uintptr_t)(rxQ->rxDescEnd) - CEDI_PdVar(rxDescriptorSize));
    rxQ->rxEndVA--;
    }

    /* get physical address */
    buf->pAddr = CPS_UncachedRead32(&(rxQ->rxDescEnd->word[0]))
                                            & CEDI_RXD_ADDR_MASK;
    /* get virtual address */
    buf->vAddr = *(rxQ->rxEndVA);

    /* dec end/tail pointers unless already at start of list */
    if (rxQ->rxDescEnd!=rxQ->rxDescStart) {
        rxQ->rxDescEnd = (rxDesc*)
                ((uintptr_t)(rxQ->rxDescEnd) - CEDI_PdVar(rxDescriptorSize));
        rxQ->rxEndVA--;

        /* set wrap on new end descriptor */
        tmp = CPS_UncachedRead32(&(rxQ->rxDescEnd->word[0]));
        CPS_UncachedWrite32(&(rxQ->rxDescEnd->word[0]), tmp | CEDI_RXD_WRAP);
    }
    rxQ->numRxBufs--;

    return 0;
}

void emacFindQBaseAddr(void *pD, uint8_t queueNum, rxQueue_t *rxQ,
                        uint32_t *pAddr, uintptr_t *vAddr) {
    uint8_t q = 0;
    /* find start addresses for this rxQ */
    *vAddr = CEDI_PdVar(cfg).rxQAddr;
    *pAddr = CEDI_PdVar(cfg).rxQPhyAddr;

    if (queueNum>0)
        rxQ->rxBufVAddr = (CEDI_PdVar(rxQueue[0]).rxBufVAddr);
    while (q<queueNum) {
        *vAddr += (rxQ->numRxDesc)*(CEDI_PdVar(rxDescriptorSize));//sizeof(rxDesc);
        *pAddr += (rxQ->numRxDesc)*(CEDI_PdVar(rxDescriptorSize));//sizeof(rxDesc);
        rxQ->rxBufVAddr += rxQ->numRxDesc;
        q++;
    }
    vDbgMsg(DBG_GEN_MSG, 10, "%s: base address Q%u virt=%08lX phys=%08X vAddrList=%p\n",
            __func__, queueNum, *vAddr, *pAddr, rxQ->rxBufVAddr);
}
/* Reset Rx buffer descriptor list/ buffer virtual address list to initial
 * empty state, clearing all descriptors.  For use by init or after a fatal
 * error. Disables receive circuit.
 * @param pD - driver private state info specific to this instance
 * @param queueNum - number of the Rx queue (range 0 to rxQs-1)
 * @param ptrsOnly - if =1, then reset pointers and clearing used bits only
 *          after a link down/up event (assume buffers already assigned)
 *          if =0, initialise all list fields for this queue, including
 *          clearing buffer addresses
 * @return 0 if successful
 * @return EINVAL if invalid parameter
 */
uint32_t emacResetRxQ(void *pD, uint8_t queueNum, uint8_t ptrsOnly)
{
#define CEDI_WR_RXQ_PTR_REG_N_CASE(Q) case Q:\
        CPS_UncachedWrite32(CEDI_RegAddr(receive_q##Q##_ptr), regTmp);\
        break;

    uint32_t regTmp;
    uint16_t i;
    uint32_t pAddr;
    uintptr_t vAddr;
    rxDesc* descPtr;
    rxQueue_t *rxQ;

    if ((pD==NULL) || (queueNum>=CEDI_PdVar(cfg).rxQs) || (ptrsOnly>1))
        return EINVAL;

    emacDisableRx(pD);

    rxQ = &(CEDI_PdVar(rxQueue[queueNum]));
    emacFindQBaseAddr(pD, queueNum, rxQ, &pAddr, &vAddr);

    /* want the virtual addresses here: */
    if (ptrsOnly) {
        if (rxQ->rxDescStop!=rxQ->rxDescEnd) {
        /* copy buffer addresses from new "stop" descriptor to old one,
         * before reset pointers */
            CPS_UncachedWrite32((uint32_t *)&(rxQ->rxDescStop->word[0]),
                CPS_UncachedRead32((uint32_t *)&(rxQ->rxDescEnd->word[0])));
            *(rxQ->rxStopVA) = *(rxQ->rxEndVA);
        }
    }
    else
    {
    rxQ->rxDescStart = (rxDesc *)vAddr;
        rxQ->rxDescEnd = (rxDesc *)vAddr;
    }
    rxQ->rxDescStop = (rxDesc *)vAddr;
    rxQ->rxDescTail = (rxDesc *)vAddr;
    rxQ->rxTailVA = rxQ->rxBufVAddr;
    rxQ->rxStopVA = rxQ->rxBufVAddr;
    if (!ptrsOnly) {
        rxQ->rxEndVA = rxQ->rxBufVAddr;
        *(rxQ->rxStopVA) = 0;
        rxQ->numRxBufs = 0;
    }

    /* full reset: clear used flags except stop & set wrap flag, only expand
     * available size as buffers are added - if ptrsOnly, then buffers already
     * in ring, preserve addresses & only clear used bits/wd1  */
    descPtr = rxQ->rxDescStart;
    for (i = 0; i<rxQ->numRxDesc; i++) {
        if (ptrsOnly) {
            if (rxQ->rxDescStop==rxQ->rxDescEnd) {
                CPS_UncachedWrite32((uint32_t *)&(rxQ->rxDescStop->word[0]),
                                          CEDI_RXD_WRAP|CEDI_RXD_USED );
                CPS_UncachedWrite32(&(rxQ->rxDescStop->word[1]), CEDI_RXD_EMPTY);
                *(rxQ->rxStopVA) = 0;
            }
            else
            {
                pAddr = CPS_UncachedRead32((uint32_t *)&(rxQ->rxDescStop->word[0]));
                CPS_UncachedWrite32((uint32_t *)&(rxQ->rxDescStop->word[0]),
                                    pAddr & ~(CEDI_RXD_WRAP|CEDI_RXD_USED));
                CPS_UncachedWrite32(&(rxQ->rxDescStop->word[1]), CEDI_RXD_EMPTY);
                /* inc stop pointer */
                rxQ->rxDescStop = (rxDesc *)(((uintptr_t)rxQ->rxDescStop) +
                                    (CEDI_PdVar(rxDescriptorSize)));
                /* inc VA stop pointer */
                rxQ->rxStopVA++;
            }
        }
        else {
        CPS_UncachedWrite32((uint32_t *)
                &(descPtr->word[0]), i?0:CEDI_RXD_WRAP|CEDI_RXD_USED);
        CPS_UncachedWrite32((uint32_t *)
                &(descPtr->word[1]), CEDI_RXD_EMPTY);
            descPtr = (rxDesc*) (((uintptr_t)(descPtr)) +
                (CEDI_PdVar(rxDescriptorSize)));
        }
    }

    if (!ptrsOnly) {
        /* write hardware base address register */
        regTmp = 0;
        EMAC_REGS__RECEIVE_Q_PTR__DMA_RX_Q_PTR__MODIFY(regTmp, pAddr>>2);
        switch (queueNum) {
        case 0:
            CPS_UncachedWrite32(CEDI_RegAddr(receive_q_ptr), regTmp);
            break;
        CEDI_WR_RXQ_PTR_REG_N_CASE(1);
        CEDI_WR_RXQ_PTR_REG_N_CASE(2);
        CEDI_WR_RXQ_PTR_REG_N_CASE(3);
        CEDI_WR_RXQ_PTR_REG_N_CASE(4);
        CEDI_WR_RXQ_PTR_REG_N_CASE(5);
        CEDI_WR_RXQ_PTR_REG_N_CASE(6);
        CEDI_WR_RXQ_PTR_REG_N_CASE(7);
        CEDI_WR_RXQ_PTR_REG_N_CASE(8);
        CEDI_WR_RXQ_PTR_REG_N_CASE(9);
        CEDI_WR_RXQ_PTR_REG_N_CASE(10);
        CEDI_WR_RXQ_PTR_REG_N_CASE(11);
        CEDI_WR_RXQ_PTR_REG_N_CASE(12);
        CEDI_WR_RXQ_PTR_REG_N_CASE(13);
        CEDI_WR_RXQ_PTR_REG_N_CASE(14);
        CEDI_WR_RXQ_PTR_REG_N_CASE(15);
        }
    }
    return 0;
}

/* Return the content of EMAC receive status register
 * @param pD - driver private state info specific to this instance
 * @param status - pointer to struct with fields for each flag
 * @return =1 if any flags set, =0 if not or status=NULL.
 */
uint32_t emacGetRxStatus(void *pD, CEDI_RxStatus *status)
{
    uint32_t reg;
    if ((pD==NULL)||(status==NULL))
        return 0;

    reg = CPS_UncachedRead32(CEDI_RegAddr(receive_status));

    status->buffNotAvail =
            EMAC_REGS__RECEIVE_STATUS__BUFFER_NOT_AVAILABLE__READ(reg);
    status->frameRx =
            EMAC_REGS__RECEIVE_STATUS__FRAME_RECEIVED__READ(reg);
    status->rxOverrun =
            EMAC_REGS__RECEIVE_STATUS__RECEIVE_OVERRUN__READ(reg);
    status->hRespNotOk =
            EMAC_REGS__RECEIVE_STATUS__RESP_NOT_OK__READ(reg);

    return reg?1:0;
}

/* Reset the bits of EMAC receive status register as selected in resetStatus
 * @param pD - driver private state info specific to this instance
 * @param resetStatus - OR'd combination of CEDI_RXS_ bit-fields
 */
void emacClearRxStatus(void *pD, uint32_t resetStatus)
{
    uint32_t reg = 0;
    if (!pD) return;

    if (resetStatus & CEDI_RXS_NO_BUFF)
        reg |= CEDI_RXS_NO_BUFF;

    if (resetStatus & CEDI_RXS_FRAME_RX)
        reg |= CEDI_RXS_FRAME_RX;

    if (resetStatus & CEDI_RXS_OVERRUN)
        reg |= CEDI_RXS_OVERRUN;

    if (resetStatus & CEDI_RXS_HRESP_ERR)
        reg |= CEDI_RXS_HRESP_ERR;

    CPS_UncachedWrite32(CEDI_RegAddr(receive_status), reg);
}

/**
 *  Enable/disable header-data split feature.
 *  When enabled, frame L2/L3/L4 headers will written to separate
 *  buffer, before data starts in a second buffer (if not zero payload)
 */
uint32_t emacSetHdrDataSplit(void *pD, uint8_t enable) {

    uint32_t reg;
    if ((pD==NULL) || (enable>1))
        return EINVAL;
    if (CEDI_PdVar(hwCfg).hdr_split==0)
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(dma_config));
    if (enable)
        EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__SET(reg);
    else
        EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__CLR(reg);

    CPS_UncachedWrite32(CEDI_RegAddr(dma_config), reg);
    return EOK;
}

/**
 * Read enable/disable status for header-data split feature
 */
uint32_t emacGetHdrDataSplit(void *pD, uint8_t *enable) {

    if ((pD==NULL) || (enable==NULL))
        return EINVAL;
    if (CEDI_PdVar(hwCfg).hdr_split==0)
        return ENOTSUP;

    *enable = EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__READ(
                CPS_UncachedRead32(CEDI_RegAddr(dma_config)));

    return EOK;
}

/**
 *  Enable/disable Receive Segment Coalescing function.
 *  When enabled, consecutive TCP/IP frames on a priority queue
 *  will be combined to form a single large frame
 */
uint32_t emacSetRscEnable(void *pD, uint8_t queue, uint8_t enable) {

    uint32_t reg, enableField;
    if (pD==NULL)
        return EINVAL;
    if (CEDI_PdVar(hwCfg).pbuf_rsc==0)
        return ENOTSUP;
    if ((queue<1) || (queue>=(CEDI_PdVar(cfg)).rxQs) || (enable>1))
        return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(rsc_control));
    enableField = EMAC_REGS__RSC_CONTROL__RSC_CONTROL__READ(reg);

    if (enable)
        enableField |= (1 << (queue-1));
    else
        enableField &= ~(1 << (queue-1));

    EMAC_REGS__RSC_CONTROL__RSC_CONTROL__MODIFY(reg, enableField);
    CPS_UncachedWrite32(CEDI_RegAddr(rsc_control), reg);

    return EOK;
}

/**
 * Read enabled status of RSC on a specified priority queue
 */
uint32_t emacGetRscEnable(void *pD, uint8_t queue, uint8_t *enable) {

    uint32_t reg;
    if ((pD==NULL) || (enable==NULL))
        return EINVAL;
    if ((queue<1)||(queue>=(CEDI_PdVar(cfg)).rxQs))
        return EINVAL;
    if (CEDI_PdVar(hwCfg).pbuf_rsc==0)
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(rsc_control));
    *enable = (EMAC_REGS__RSC_CONTROL__RSC_CONTROL__READ(reg)
                            & (1<<(queue-1)))?1:0;

    return EOK;
}

/**
 *  Set/Clear Mask of Receive Segment Coalescing disabling.
 *  When mask is set and RSC is enabled, the RSC operation is not
 *  disabled by receipt of frame with an end-coalesce flag set
 *  (SYN/FIN/RST/URG)
 */
uint32_t emacSetRscClearMask(void *pD, uint8_t setMask) {

    uint32_t reg;
    if ((pD==NULL) || (setMask>1))
        return EINVAL;
    if (CEDI_PdVar(hwCfg).pbuf_rsc==0)
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(rsc_control));
    if (setMask)
        reg |= (1<<16);
    else
        reg &= ~(1<<16);
    CPS_UncachedWrite32(CEDI_RegAddr(rsc_control), reg);

    return EOK;
}

uint32_t emacSetRxPartialStFwd(void *pD, uint32_t watermark, uint8_t enable)
{
    uint32_t reg;
    if (!pD) return EINVAL;
    if (CEDI_PdVar(hwCfg).rx_pkt_buffer==0)
        return ENOTSUP;
    if (enable>1) return EINVAL;
//    if ((enable) && (!CEDI_PdVar(hwCfg).rx_pkt_buffer))
//        return EINVAL;
    if (watermark>((1UL<<CEDI_PdVar(hwCfg).rx_pbuf_addr)-1))
        return EINVAL;

    reg = CPS_UncachedRead32(CEDI_RegAddr(pbuf_rxcutthru));
    if (enable) {
        EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU_THRESHOLD__MODIFY(reg,
                watermark);
        EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__SET(reg);
    }
    else
        EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__CLR(reg);

    CPS_UncachedWrite32(CEDI_RegAddr(pbuf_rxcutthru), reg);

    return 0;
}

uint32_t emacGetRxPartialStFwd(void *pD, uint32_t *watermark, uint8_t *enable)
{
    uint32_t reg;
    if ((pD==0)||(enable==0)||(watermark==0))
        return EINVAL;
    if (CEDI_PdVar(hwCfg).rx_pkt_buffer==0)
        return ENOTSUP;

    reg = CPS_UncachedRead32(CEDI_RegAddr(pbuf_rxcutthru));
    (*enable) = EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU__READ(reg);

    if (*enable)
        *watermark = EMAC_REGS__PBUF_RXCUTTHRU__DMA_RX_CUTTHRU_THRESHOLD__READ(reg);

    return 0;
}

/******************************** Rx Filtering ******************************/

  /**
   * Set specific address register to the given address value
   * @param[in] pD driver private state info specific to this instance
   * @param[in] addrNum number of specific address filters,
   *                in range 1 - num_spec_add_filters.
   *    $RANGE $FROM 1 $TO CEDI_DesignCfg.num_spec_add_filters$
   * @param[in] addr pointer to the 6-byte MAC address value to write
   * @param[in] specFilterType flag specifying whether to use MAC source or
   *    destination address to be compared for filtering. Source filter when =1.
   *    $RANGE $FROM 0 $TO 1 $
   * @param[in] byteMask  Bits masking out bytes of specific address from
   *    comparison.  When high, the associated address byte will be ignored.
   *    e.g. LSB of byteMask=1 implies first byte received should not be compared
   *    Ignored if addrNum=1, full bit masking available (SpecificAddr1Mask)
   *    $RANGE $FROM 0 $TO 0x3F $TEST_SUBSET 4 $
   * @return 0 if successful,
   * @return EINVAL if pD, addrNum, specFilterType or byteMask invalid
   * @return ENOTSUP if CEDI_DesignCfg.num_spec_add_filters==0
   */
uint32_t emacSetSpecificAddr(void *pD, uint8_t addrNum, CEDI_MacAddress *addr,
                            uint8_t specFilterType, uint8_t byteMask)
{
#define CEDI_WR_SPEC_ADDR_CASE(reg) \
          case(reg):EMAC_REGS__SPEC_ADD_BOTTOM__ADDRESS__MODIFY(regVal,\
                      addr->byte[0] + (addr->byte[1]<<8) + \
                      (addr->byte[2]<<16) + (addr->byte[3]<<24));\
                    CPS_UncachedWrite32((CEDI_RegAddr(spec_add##reg##_bottom)),\
                                          regVal);\
                    regVal = 0;\
                    if (reg==1) {\
                      EMAC_REGS__SPEC_ADD_TOP_NO_MASK__ADDRESS__MODIFY(regVal,\
                        addr->byte[4] + (addr->byte[5]<<8));\
                      EMAC_REGS__SPEC_ADD_TOP_NO_MASK__FILTER_TYPE__MODIFY( \
                           regVal,specFilterType);\
                    } else {\
                      EMAC_REGS__SPEC_ADD_TOP__ADDRESS__MODIFY(regVal,\
                        addr->byte[4] + (addr->byte[5]<<8));\
                      EMAC_REGS__SPEC_ADD_TOP__FILTER_TYPE__MODIFY( \
                        regVal,specFilterType);\
                      EMAC_REGS__SPEC_ADD_TOP__FILTER_BYTE_MASK__MODIFY( \
                        regVal,byteMask);\
                    }\
                    CPS_UncachedWrite32((CEDI_RegAddr(spec_add##reg##_top)),\
                                          regVal); break;

    uint32_t regVal;
    if ((!pD)||(addr==NULL)) return EINVAL;
    if ((!addrNum) || (addrNum>(CEDI_PdVar(hwCfg).num_spec_add_filters)))
        return EINVAL;
    if ((specFilterType>1) || (byteMask>0x3F))
        return EINVAL;

    if (CEDI_PdVar(hwCfg).num_spec_add_filters==0)
        return ENOTSUP;

    regVal = 0;
    switch(addrNum) {
            CEDI_WR_SPEC_ADDR_CASE(1)
            CEDI_WR_SPEC_ADDR_CASE(2)
            CEDI_WR_SPEC_ADDR_CASE(3)
            CEDI_WR_SPEC_ADDR_CASE(4)
            CEDI_WR_SPEC_ADDR_CASE(5)
            CEDI_WR_SPEC_ADDR_CASE(6)
            CEDI_WR_SPEC_ADDR_CASE(7)
            CEDI_WR_SPEC_ADDR_CASE(8)
            CEDI_WR_SPEC_ADDR_CASE(9)
            CEDI_WR_SPEC_ADDR_CASE(10)
            CEDI_WR_SPEC_ADDR_CASE(11)
            CEDI_WR_SPEC_ADDR_CASE(12)
            CEDI_WR_SPEC_ADDR_CASE(13)
            CEDI_WR_SPEC_ADDR_CASE(14)
            CEDI_WR_SPEC_ADDR_CASE(15)
            CEDI_WR_SPEC_ADDR_CASE(16)
            CEDI_WR_SPEC_ADDR_CASE(17)
            CEDI_WR_SPEC_ADDR_CASE(18)
            CEDI_WR_SPEC_ADDR_CASE(19)
            CEDI_WR_SPEC_ADDR_CASE(20)
            CEDI_WR_SPEC_ADDR_CASE(21)
            CEDI_WR_SPEC_ADDR_CASE(22)
            CEDI_WR_SPEC_ADDR_CASE(23)
            CEDI_WR_SPEC_ADDR_CASE(24)
            CEDI_WR_SPEC_ADDR_CASE(25)
            CEDI_WR_SPEC_ADDR_CASE(26)
            CEDI_WR_SPEC_ADDR_CASE(27)
            CEDI_WR_SPEC_ADDR_CASE(28)
            CEDI_WR_SPEC_ADDR_CASE(29)
            CEDI_WR_SPEC_ADDR_CASE(30)
            CEDI_WR_SPEC_ADDR_CASE(31)
            CEDI_WR_SPEC_ADDR_CASE(32)
}

    return EOK;
}

  /**
   * Get the value of a specific address register
   * @param[in] pD driver private state info specific to this instance
   * @param[in] addrNum number of specific address filters, in
   *                range 1 - num_spec_add_filters
   * @param[out] specFilterType flag specifying whether to use MAC source or
   *    destination address for filtering. When set to 1 use source address.
   * @param[out] byteMask Bits masking out bytes of specific address from
   *    comparison.  When high, the associated address byte will be ignored.
   *    e.g. LSB of byteMask=1 implies first byte received should not be compared
   *    Ignored if addrNum=1, full bit masking available (SpecificAddr1Mask)
   * @param[out] addr pointer to a 6-byte MAC address struct for returning the
   *    address value
   * @return 0 if successful
   * @return EINVAL if pD, addrNum, specFilterType or byteMask invalid
   * @return ENOTSUP if CEDI_DesignCfg.num_spec_add_filters==0
   */
uint32_t emacGetSpecificAddr(void *pD, uint8_t addrNum, CEDI_MacAddress *addr,
                        uint8_t *specFilterType, uint8_t *byteMask)
{

#define CEDI_RD_SPEC_ADDR_CASE(reg) \
              case(reg):\
              regAddrBottom = EMAC_REGS__SPEC_ADD_BOTTOM__ADDRESS__READ(\
                 CPS_UncachedRead32(CEDI_RegAddr(spec_add##reg##_bottom)));\
              regTopVal= CPS_UncachedRead32(CEDI_RegAddr(spec_add##reg##_top));\
              if (reg==1) {\
                regAddrTop = EMAC_REGS__SPEC_ADD_TOP_NO_MASK__ADDRESS__READ(\
                            regTopVal);\
                *specFilterType = \
                  EMAC_REGS__SPEC_ADD_TOP_NO_MASK__FILTER_TYPE__READ(regTopVal);\
                *byteMask = 0;\
              } else {\
                regAddrTop = EMAC_REGS__SPEC_ADD_TOP__ADDRESS__READ(regTopVal);\
                *specFilterType = \
                  EMAC_REGS__SPEC_ADD_TOP__FILTER_TYPE__READ(regTopVal);\
                *byteMask = \
                  EMAC_REGS__SPEC_ADD_TOP__FILTER_BYTE_MASK__READ(regTopVal);}\
              break;

    uint32_t regAddrTop, regAddrBottom, regTopVal;
    if ((pD==NULL)||(addr==NULL))
        return EINVAL;

    if ((specFilterType==NULL)||(byteMask==NULL))
        return EINVAL;

    if (CEDI_PdVar(hwCfg).num_spec_add_filters==0)
        return ENOTSUP;
    if ((!addrNum) || (addrNum>(CEDI_PdVar(hwCfg).num_spec_add_filters)))
        return EINVAL;
    regAddrTop = 0;
    regAddrBottom = 0;
    switch(addrNum) {
                CEDI_RD_SPEC_ADDR_CASE(1)
                CEDI_RD_SPEC_ADDR_CASE(2)
                CEDI_RD_SPEC_ADDR_CASE(3)
                CEDI_RD_SPEC_ADDR_CASE(4)
                CEDI_RD_SPEC_ADDR_CASE(5)
                CEDI_RD_SPEC_ADDR_CASE(6)
                CEDI_RD_SPEC_ADDR_CASE(7)
                CEDI_RD_SPEC_ADDR_CASE(8)
                CEDI_RD_SPEC_ADDR_CASE(9)
                CEDI_RD_SPEC_ADDR_CASE(10)
                CEDI_RD_SPEC_ADDR_CASE(11)
                CEDI_RD_SPEC_ADDR_CASE(12)
                CEDI_RD_SPEC_ADDR_CASE(13)
                CEDI_RD_SPEC_ADDR_CASE(14)
                CEDI_RD_SPEC_ADDR_CASE(15)
                CEDI_RD_SPEC_ADDR_CASE(16)
                CEDI_RD_SPEC_ADDR_CASE(17)
                CEDI_RD_SPEC_ADDR_CASE(18)
                CEDI_RD_SPEC_ADDR_CASE(19)
                CEDI_RD_SPEC_ADDR_CASE(20)
                CEDI_RD_SPEC_ADDR_CASE(21)
                CEDI_RD_SPEC_ADDR_CASE(22)
                CEDI_RD_SPEC_ADDR_CASE(23)
                CEDI_RD_SPEC_ADDR_CASE(24)
                CEDI_RD_SPEC_ADDR_CASE(25)
                CEDI_RD_SPEC_ADDR_CASE(26)
                CEDI_RD_SPEC_ADDR_CASE(27)
                CEDI_RD_SPEC_ADDR_CASE(28)
                CEDI_RD_SPEC_ADDR_CASE(29)
                CEDI_RD_SPEC_ADDR_CASE(30)
                CEDI_RD_SPEC_ADDR_CASE(31)
                CEDI_RD_SPEC_ADDR_CASE(32)
    }

//    vDbgMsg(DBG_GEN_MSG, 10, "top=%08X  bottom=%08X\n",
//                    regAddrTop, regAddrBottom);
    addr->byte[0] = (regAddrBottom & 0xFF);
    addr->byte[1] = ((regAddrBottom>>8) & 0xFF);
    addr->byte[2] = ((regAddrBottom>>16) & 0xFF);
    addr->byte[3] = ((regAddrBottom>>24) & 0xFF);
    addr->byte[4] = (regAddrTop & 0xFF);
    addr->byte[5] = ((regAddrTop>>8) & 0xFF);
    return EOK;
}

/* Set the specific address 1 mask register to the given value, allowing
 * address matching against a portion of the specific address 1 register
 * @param pD - driver private state info specific to this instance
 * @param mask - pointer to the address mask value to write
 * @return 0 if successful
 * @return EINVAL if mask=NULL
 * @return ENOTSUP if CEDI_DesignCfg.num_spec_add_filters==0
 */
uint32_t emacSetSpecificAddr1Mask(void *pD, CEDI_MacAddress *mask)
{
    uint32_t reg;

    if ((pD==NULL) || (mask==NULL))
        return EINVAL;
    if (CEDI_PdVar(hwCfg).num_spec_add_filters==0)
        return ENOTSUP;

    reg = 0;
    EMAC_REGS__MASK_ADD1_BOTTOM__ADDRESS_MASK__MODIFY(reg,
            mask->byte[0] + (mask->byte[1]<<8) + (mask->byte[2]<<16)
                        + (mask->byte[3]<<24));
    CPS_UncachedWrite32((CEDI_RegAddr(mask_add1_bottom)), reg);
    reg = 0;
    EMAC_REGS__MASK_ADD1_TOP__ADDRESS_MASK__MODIFY(reg,
            mask->byte[4] + (mask->byte[5]<<8));
    CPS_UncachedWrite32((CEDI_RegAddr(mask_add1_top)), reg);
    return EOK;
}

/* Get the value of the specific address 1 mask register
 * @param pD - driver private state info specific to this instance
 * @param mask - pointer to a 6-byte MAC address struct for returning the
 *    mask value
 * @return 0 if successful, EINVAL if addrNum invalid
 * @return ENOTSUP if CEDI_DesignCfg.num_spec_add_filters==0
 */
uint32_t emacGetSpecificAddr1Mask(void *pD, CEDI_MacAddress *mask)
{
    int reg1, reg2;
    if ((pD==NULL)||(mask==NULL)) return EINVAL;
    if (CEDI_PdVar(hwCfg).num_spec_add_filters==0)
        return ENOTSUP;

    reg1 = EMAC_REGS__MASK_ADD1_BOTTOM__ADDRESS_MASK__READ(
            CPS_UncachedRead32(CEDI_RegAddr(mask_add1_bottom)));
    reg2 = EMAC_REGS__MASK_ADD1_TOP__ADDRESS_MASK__READ(
            CPS_UncachedRead32(CEDI_RegAddr(mask_add1_top)));

//      vDbgMsg(DBG_GEN_MSG, 10, "top=%08X  bottom=%08X\n", reg2, reg1);
    mask->byte[0] = (reg1 & 0xFF);
    mask->byte[1] = ((reg1>>8) & 0xFF);
    mask->byte[2] = ((reg1>>16) & 0xFF);
    mask->byte[3] = ((reg1>>24) & 0xFF);
    mask->byte[4] = (reg2 & 0xFF);
    mask->byte[5] = ((reg2>>8) & 0xFF);
    return EOK;
}

/* Disable the specific address match stored at given register, by writing 0
 * to lower address register
 * @param pD - driver private state info specific to this instance
 * @param addrNum -
 *    number of specific address filters, in range 1 - num_spec_add_filters
 *    $RANGE $FROM 1 $TO CEDI_DesignCfg.num_spec_add_filters$
 * @return 0 if successful
 * @return EINVAL if invalid parameter
 * @return ENOTSUP if CEDI_DesignCfg.num_spec_add_filters==0
 */
uint32_t emacDisableSpecAddr(void *pD, uint8_t addrNum)
{
#define CEDI_DIS_SPEC_ADDR_CASE(reg) \
    case(reg): \
        CPS_UncachedWrite32((CEDI_RegAddr(spec_add##reg##_bottom)), 0); break;

    if (!pD) return EINVAL;
    if (CEDI_PdVar(hwCfg).num_spec_add_filters==0)
        return ENOTSUP;
    if ((!addrNum) || (addrNum>(CEDI_PdVar(hwCfg).num_spec_add_filters)))
        return EINVAL;

    switch(addrNum) {
                CEDI_DIS_SPEC_ADDR_CASE(1)
                CEDI_DIS_SPEC_ADDR_CASE(2)
                CEDI_DIS_SPEC_ADDR_CASE(3)
                CEDI_DIS_SPEC_ADDR_CASE(4)
                CEDI_DIS_SPEC_ADDR_CASE(5)
                CEDI_DIS_SPEC_ADDR_CASE(6)
                CEDI_DIS_SPEC_ADDR_CASE(7)
                CEDI_DIS_SPEC_ADDR_CASE(8)
                CEDI_DIS_SPEC_ADDR_CASE(9)
                CEDI_DIS_SPEC_ADDR_CASE(10)
                CEDI_DIS_SPEC_ADDR_CASE(11)
                CEDI_DIS_SPEC_ADDR_CASE(12)
                CEDI_DIS_SPEC_ADDR_CASE(13)
                CEDI_DIS_SPEC_ADDR_CASE(14)
                CEDI_DIS_SPEC_ADDR_CASE(15)
                CEDI_DIS_SPEC_ADDR_CASE(16)
                CEDI_DIS_SPEC_ADDR_CASE(17)
                CEDI_DIS_SPEC_ADDR_CASE(18)
                CEDI_DIS_SPEC_ADDR_CASE(19)
                CEDI_DIS_SPEC_ADDR_CASE(20)
                CEDI_DIS_SPEC_ADDR_CASE(21)
                CEDI_DIS_SPEC_ADDR_CASE(22)
                CEDI_DIS_SPEC_ADDR_CASE(23)
                CEDI_DIS_SPEC_ADDR_CASE(24)
                CEDI_DIS_SPEC_ADDR_CASE(25)
                CEDI_DIS_SPEC_ADDR_CASE(26)
                CEDI_DIS_SPEC_ADDR_CASE(27)
                CEDI_DIS_SPEC_ADDR_CASE(28)
                CEDI_DIS_SPEC_ADDR_CASE(29)
                CEDI_DIS_SPEC_ADDR_CASE(30)
                CEDI_DIS_SPEC_ADDR_CASE(31)
                CEDI_DIS_SPEC_ADDR_CASE(32)
    }

    return 0;
}

/**
 * En/Disable Type ID match field of the specified register, and set
 * type Id value if enabling
 * @param[in] pD driver private state info specific to this instance
 * @param[in] matchSel number of TypeID Match register, range 1 - 4
 *    $RANGE $FROM 1 $TO 4$
 * @param[in] typeId the Type ID match value to write,
 *    ignored if enable equal 0
 * @param[in] enable if equal 1 enables the type matching for this ID,
 *    if 0 then disables type matching for this ID
 *    $RANGE $FROM 0 $TO 1$
 * @return 0 if successful,
 * @return EINVAL if matchSel invalid
 * $VALIDFAIL if ((enable==0)&&((matchSel<1)||(matchSel>4)))
 *  $EXPECT_RETURN EINVAL $
 */
uint32_t emacSetTypeIdMatch(void *pD, uint8_t matchSel, uint16_t typeId,
        uint8_t enable)
{
    uint32_t regVal = 0;
    if ((pD==NULL) || (matchSel<1) || (matchSel>4)) return EINVAL;
    if (enable>1) return EINVAL;

    switch (matchSel) {
    case 1:
        if (enable) {
            EMAC_REGS__SPEC_TYPE1__ENABLE_COPY__SET(regVal);
            EMAC_REGS__SPEC_TYPE1__MATCH__MODIFY(regVal, typeId);
        }
        CPS_UncachedWrite32(CEDI_RegAddr(spec_type1),regVal);
        break;
    case 2:
        if (enable) {
            EMAC_REGS__SPEC_TYPE2__ENABLE_COPY__SET(regVal);
            EMAC_REGS__SPEC_TYPE2__MATCH__MODIFY(regVal, typeId);
        }
        CPS_UncachedWrite32(CEDI_RegAddr(spec_type2),regVal);
        break;
    case 3:
        if (enable) {
            EMAC_REGS__SPEC_TYPE3__ENABLE_COPY__SET(regVal);
            EMAC_REGS__SPEC_TYPE3__MATCH__MODIFY(regVal, typeId);
        }
        CPS_UncachedWrite32(CEDI_RegAddr(spec_type3),regVal);
        break;
    case 4:
        if (enable) {
            EMAC_REGS__SPEC_TYPE4__ENABLE_COPY__SET(regVal);
            EMAC_REGS__SPEC_TYPE4__MATCH__MODIFY(regVal, typeId);
        }
        CPS_UncachedWrite32(CEDI_RegAddr(spec_type4),regVal);
        break;
    }

    return 0;
}

/* Read the specified Type ID match register settings
 * @param pD - driver private state info specific to this instance
 * @param matchSel  - number of TypeID Match register, range 1 - 4
 * @param typeId - pointer for returning the Type ID match value read,
 *              ignored if disabled
 * @param enabled - pointer for returning enabled status: if value returned <>0
 *             then typeId matching is enabled for this register, else disabled
 * @return 0 if successful, EINVAL if invalid parameter
 */
uint32_t emacGetTypeIdMatch(void *pD, uint8_t matchSel, uint16_t *typeId,
        uint8_t *enabled)
{
    uint32_t regVal = 0;
    if (pD==NULL) return EINVAL;
    if ((matchSel<1) || (matchSel>4) || (enabled==NULL)) return EINVAL;
    if (*enabled && (typeId==NULL)) return EINVAL;

    switch (matchSel) {
    case 1:
        regVal = CPS_UncachedRead32(CEDI_RegAddr(spec_type1));
        *enabled = EMAC_REGS__SPEC_TYPE1__ENABLE_COPY__READ(regVal);
        *typeId = EMAC_REGS__SPEC_TYPE1__MATCH__READ(regVal);
        break;
    case 2:
        regVal = CPS_UncachedRead32(CEDI_RegAddr(spec_type2));
        *enabled = EMAC_REGS__SPEC_TYPE2__ENABLE_COPY__READ(regVal);
        *typeId = EMAC_REGS__SPEC_TYPE2__MATCH__READ(regVal);
        break;
    case 3:
        regVal = CPS_UncachedRead32(CEDI_RegAddr(spec_type3));
        *enabled = EMAC_REGS__SPEC_TYPE3__ENABLE_COPY__READ(regVal);
        *typeId = EMAC_REGS__SPEC_TYPE3__MATCH__READ(regVal);
        break;
    case 4:
        regVal = CPS_UncachedRead32(CEDI_RegAddr(spec_type4));
        *enabled = EMAC_REGS__SPEC_TYPE4__ENABLE_COPY__READ(regVal);
        *typeId = EMAC_REGS__SPEC_TYPE4__MATCH__READ(regVal);
        break;
    }

    return 0;
}

/* En/disable reception of unicast frames when hash register matched
 * @param pD - driver private state info specific to this instance
 * @param enable if<>0, enables reception, else disables
 */
void emacSetUnicastEnable(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (!pD) return;
    if (enable>1) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

/* Return state of unicast frame matching
 * @param pD - driver private state info specific to this instance
 * @return  =0 if disabled, =1 if enabled
 */
uint32_t emacGetUnicastEnable(void *pD, uint8_t *enable)
{
    if ((pD==0)||(enable==0))
      return EINVAL;
    *enable= EMAC_REGS__NETWORK_CONFIG__UNICAST_HASH_ENABLE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

/* En/disable reception of multicast frames when hash register matched
 * @param pD - driver private state info specific to this instance
 * @param enable if<>0, enables, else disables
 */
void emacSetMulticastEnable(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (!pD) return;
    if (enable>1) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

/* Return state of multicast frame matching
 * @param pD - driver private state info specific to this instance
 * @return =0 if disabled, =1 if enabled
 */
uint32_t emacGetMulticastEnable(void *pD, uint8_t *enable)
{
    if ((pD==0)||(enable==0))
      return EINVAL;
    *enable= EMAC_REGS__NETWORK_CONFIG__MULTICAST_HASH_ENABLE__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

/* Dis/Enable receipt of broadcast frames
 * @param pD - driver private state info specific to this instance
 * @param reject if =0 broadcasts are accepted, else they are rejected.
 */
void emacSetNoBroadcast(void *pD, uint8_t reject)
{
    uint32_t reg;
    if (!pD) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (reject)
        EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

/* Return broadcast rejection setting
 * @param pD - driver private state info specific to this instance
 * @return if =0, broadcasts being accepted, else rejected
 */
uint32_t emacGetNoBroadcast(void *pD, uint8_t *reject)
{
    if ((pD==0)||(reject==0))
      return EINVAL;
    *reject= EMAC_REGS__NETWORK_CONFIG__NO_BROADCAST__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

/* En/Disable receipt of only frames which have been VLAN tagged
 * @param pD - driver private state info specific to this instance
 * @param enable<>0 to reject non-VLAN-tagged frames.
 */
void emacSetVlanOnly(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (!pD) return;
    if (enable>1) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

/* Return VLAN-tagged filter setting
 * @param pD - driver private state info specific to this instance
 * @return <>0 if VLAN-only, else accept non-VLAN tagged frames
 */
uint32_t emacGetVlanOnly(void *pD, uint8_t *enable)
{
    if ((pD==0)||(enable==0))
      return EINVAL;
    *enable= EMAC_REGS__NETWORK_CONFIG__DISCARD_NON_VLAN_FRAMES__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

/* En/Disable stacked VLAN processing mode.
 * @param pD - driver private state info specific to this instance
 * @param enable - if <>0 enables stacked VLAN processing, if =0 disables it
 * @param vlanType - sets user defined VLAN type for matching first VLAN tag.
 *    Ignored if enable =0.
 */
void emacSetStackedVlanReg(void *pD, uint8_t enable, uint16_t vlanType)
{
    uint32_t reg;
    if (!pD) return;
    if (enable>1) return;

    reg = CPS_UncachedRead32(CEDI_RegAddr(stacked_vlan));
    if (enable) {
        EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__SET(reg);
        EMAC_REGS__STACKED_VLAN__MATCH__MODIFY(reg, vlanType);
    }
    else
        EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(stacked_vlan), reg);
}

/* Reads stacked VLAN register settings.
 * @param pD - driver private state info specific to this instance
 * @param enable - pointer for returning Enabled field: =1 if enabled, =0 if
 *    disabled.
 * @param vlanType - pointer for returning VLAN type field
 *
 */
void emacGetStackedVlanReg(void *pD, uint8_t *enable, uint16_t *vlanType)
{
    uint32_t reg;
    if ((pD==NULL)||(enable==NULL) || (vlanType==NULL)) return;

    reg = CPS_UncachedRead32(CEDI_RegAddr(stacked_vlan));
    *enable = EMAC_REGS__STACKED_VLAN__ENABLE_PROCESSING__READ(reg);
    *vlanType = EMAC_REGS__STACKED_VLAN__MATCH__READ(reg);
}

/* En/Disable copy all frames mode
 * @param pD - driver private state info specific to this instance
 * @param enable - if <>0, enables copy all frames mode, else this is
 *    disabled
 */
void emacSetCopyAllFrames(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (!pD) return;
    if (enable>1) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

/* Get "copy all" setting
 * @param pD - driver private state info specific to this instance
 * @return =0 if disabled, =1 if enabled
 */
uint32_t emacGetCopyAllFrames(void *pD, uint8_t *enable)
{
    if ((pD==0)||(enable==0))
      return EINVAL;
    *enable= EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

/* Set the hash address register.
 * @param pD - driver private state info specific to this instance
 * @param hAddrTop  -  most significant 32 bits of hash register
 * @param hAddrBot  - least significant 32 bits of hash register
 * @return EINVAL if pD=NULL, else 0.
 */
uint32_t emacSetHashAddr(void *pD, uint32_t hAddrTop, uint32_t hAddrBot)
{
    if (pD==NULL) return EINVAL;
    CPS_UncachedWrite32(CEDI_RegAddr(hash_bottom),
            EMAC_REGS__HASH_BOTTOM__ADDRESS__WRITE(hAddrBot));
    CPS_UncachedWrite32(CEDI_RegAddr(hash_top),
            EMAC_REGS__HASH_TOP__ADDRESS__WRITE(hAddrTop));
    return 0;
}

/* Read the hash address register.
 * @param pD - driver private state info specific to this instance
 * @param hAddrTop  -  pointer for returning most significant 32 bits of
 *    hash register
 * @param hAddrBot  - pointer for returning least significant 32 bits of
 *    hash register
 * @return EINVAL if any parameter =NULL, else 0.
 */
uint32_t emacGetHashAddr(void *pD, uint32_t *hAddrTop, uint32_t *hAddrBot)
{
    if ((pD==NULL) || (hAddrTop==NULL) || (hAddrBot==NULL)) return EINVAL;
    *hAddrBot = EMAC_REGS__HASH_BOTTOM__ADDRESS__READ(
                CPS_UncachedRead32(CEDI_RegAddr(hash_bottom)));
    *hAddrTop = EMAC_REGS__HASH_TOP__ADDRESS__READ(
                CPS_UncachedRead32(CEDI_RegAddr(hash_top)));
    return 0;
}

/* Enable/disable discard of frames with length shorter than given in length
 * field
 * @param pD - driver private state info specific to this instance
 * @param enable - if <>1 then enable, else disable.
 */
void emacSetLenErrDiscard(void *pD, uint8_t enable)
{
    uint32_t reg;
    if (!pD) return;
    if (enable>1) return;
    reg = CPS_UncachedRead32(CEDI_RegAddr(network_config));
    if (enable)
        EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__SET(reg);
    else
        EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__CLR(reg);
    CPS_UncachedWrite32(CEDI_RegAddr(network_config), reg);
}

/* Read enable/disable status for discard of frames with length shorter than
 * given in length field.
 * @param pD - driver private state info specific to this instance
 * @return 1 if enabled, 0 if disabled.
 */
uint32_t emacGetLenErrDiscard(void *pD, uint8_t *enable)
{
    if ((pD==0)||(enable==0))
      return EINVAL;
    *enable= EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__READ(
            CPS_UncachedRead32(CEDI_RegAddr(network_config)));

    return 0;
}

/******************************** Rx Priority Queues ******************************/

/* Return the numbers of screener, ethtype & compare registers present
 * @param pD - driver private state info specific to this instance
 * @param regNums - points to a CEDI_NumScreeners struct with the match parameters
 *    to be written
 * @return 0 if successful, EINVAL if parameter invalid
 */
uint32_t emacGetNumScreenRegs(void *pD, CEDI_NumScreeners *regNums)
{
    if ((pD==NULL) || (regNums==NULL))
        return EINVAL;

    regNums->type1ScrRegs = CEDI_PdVar(hwCfg).num_type1_screeners;
    regNums->type2ScrRegs = CEDI_PdVar(hwCfg).num_type2_screeners;
    regNums->ethtypeRegs = CEDI_PdVar(hwCfg).num_scr2_ethtype_regs;
    regNums->compareRegs = CEDI_PdVar(hwCfg).num_scr2_compare_regs;
    return 0;
}


/* Write Rx frame matching values to a Type 1 screening register, for allocating
 * to a priority queue.
 * @param pD - driver private state info specific to this instance
 * @param regNum - the Type 1 register number, range 0 to num_type1_screeners-1
 * @param regVals - points to a CEDI_T1Screen struct with the match parameters
 *    to be written
 * @return 0 if successful, EINVAL if parameter invalid
 */
uint32_t emacSetType1ScreenReg(void *pD, uint8_t regNum, CEDI_T1Screen *regVals)
{
#define CEDI_WR_SCRN_TYPE1_REG_CASE(rNum) \
    case(rNum):\
        CPS_UncachedWrite32(CEDI_RegAddr(screening_type_1_register_##rNum),reg);\
        break;

    uint32_t reg;
    if ((pD==NULL) || (regVals==NULL))
        return EINVAL;

    if (CEDI_PdVar(hwCfg).num_type1_screeners==0)
        return ENOTSUP;

    if ((regNum>=CEDI_PdVar(hwCfg).num_type1_screeners) ||
        (regVals->qNum>=CEDI_PdVar(cfg).rxQs) ||
        (regVals->udpEnable>1) || (regVals->dstcEnable>1))
        return EINVAL;

    reg = 0;
    EMAC_REGS__SCREENING_TYPE_1_REGISTER__QUEUE_NUMBER__MODIFY(reg,
                                                            regVals->qNum);
    EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_ENABLE__MODIFY(reg,
                                                        regVals->dstcEnable);
    EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_MATCH__MODIFY(reg,
                                                        regVals->dstcMatch);
    EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH_ENABLE__MODIFY(reg,
                                                    regVals->udpEnable);
    EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH__MODIFY(reg,
                                                        regVals->udpPort);

    switch (regNum) {
        CEDI_WR_SCRN_TYPE1_REG_CASE(0)
        CEDI_WR_SCRN_TYPE1_REG_CASE(1)
        CEDI_WR_SCRN_TYPE1_REG_CASE(2)
        CEDI_WR_SCRN_TYPE1_REG_CASE(3)
        CEDI_WR_SCRN_TYPE1_REG_CASE(4)
        CEDI_WR_SCRN_TYPE1_REG_CASE(5)
        CEDI_WR_SCRN_TYPE1_REG_CASE(6)
        CEDI_WR_SCRN_TYPE1_REG_CASE(7)
        CEDI_WR_SCRN_TYPE1_REG_CASE(8)
        CEDI_WR_SCRN_TYPE1_REG_CASE(9)
        CEDI_WR_SCRN_TYPE1_REG_CASE(10)
        CEDI_WR_SCRN_TYPE1_REG_CASE(11)
        CEDI_WR_SCRN_TYPE1_REG_CASE(12)
        CEDI_WR_SCRN_TYPE1_REG_CASE(13)
        CEDI_WR_SCRN_TYPE1_REG_CASE(14)
        CEDI_WR_SCRN_TYPE1_REG_CASE(15)
    }
    return 0;
}

/* Read Rx frame matching values from a Type1 screening register
 * @param pD - driver private state info specific to this instance
 * @param regNum - the Type 1 register number, range 0 to num_type1_screeners-1
 * @param regVals - points to a CEDI_T1Screen struct for returning the match
 *    parameters
 * @return 0 if successful, EINVAL if parameter invalid
 */
uint32_t emacGetType1ScreenReg(void *pD, uint8_t regNum, CEDI_T1Screen *regVals)
{
#define CEDI_RD_SCRN_TYPE1_REG_CASE(rNum) \
    case(rNum):\
        reg=CPS_UncachedRead32(CEDI_RegAddr(screening_type_1_register_##rNum));\
        break;

    uint32_t reg = 0;

    if ((pD==NULL) || (regVals==NULL))
        return EINVAL;

    if (CEDI_PdVar(hwCfg).num_type1_screeners==0)
        return ENOTSUP;

    if (regNum>=CEDI_PdVar(hwCfg).num_type1_screeners)
        return EINVAL;

    switch (regNum) {
        CEDI_RD_SCRN_TYPE1_REG_CASE(0)
        CEDI_RD_SCRN_TYPE1_REG_CASE(1)
        CEDI_RD_SCRN_TYPE1_REG_CASE(2)
        CEDI_RD_SCRN_TYPE1_REG_CASE(3)
        CEDI_RD_SCRN_TYPE1_REG_CASE(4)
        CEDI_RD_SCRN_TYPE1_REG_CASE(5)
        CEDI_RD_SCRN_TYPE1_REG_CASE(6)
        CEDI_RD_SCRN_TYPE1_REG_CASE(7)
        CEDI_RD_SCRN_TYPE1_REG_CASE(8)
        CEDI_RD_SCRN_TYPE1_REG_CASE(9)
        CEDI_RD_SCRN_TYPE1_REG_CASE(10)
        CEDI_RD_SCRN_TYPE1_REG_CASE(11)
        CEDI_RD_SCRN_TYPE1_REG_CASE(12)
        CEDI_RD_SCRN_TYPE1_REG_CASE(13)
        CEDI_RD_SCRN_TYPE1_REG_CASE(14)
        CEDI_RD_SCRN_TYPE1_REG_CASE(15)
    }
    regVals->qNum =
            EMAC_REGS__SCREENING_TYPE_1_REGISTER__QUEUE_NUMBER__READ(reg);
    regVals->dstcMatch =
            EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_MATCH__READ(reg);
    regVals->udpPort =
            EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH__READ(reg);
    regVals->dstcEnable =
            EMAC_REGS__SCREENING_TYPE_1_REGISTER__DSTC_ENABLE__READ(reg);
    regVals->udpEnable =
            EMAC_REGS__SCREENING_TYPE_1_REGISTER__UDP_PORT_MATCH_ENABLE__READ(
                    reg);
    return 0;
}

/* Write Rx frame matching values to a Type 2 screening register, for
 * allocating to a priority queue.
 * @param pD - driver private state info specific to this instance
 * @param regNum - the Type 2 register number, range 0 to num_type2_screeners-1
 * @param regVals - points to a CEDI_T2Screen struct with the match
 *    parameters to be written
 * @return 0 if successful, EINVAL if parameter invalid
 */
uint32_t emacSetType2ScreenReg(void *pD, uint8_t regNum, CEDI_T2Screen *regVals)
{
#define CEDI_WR_SCRN_TYPE2_REG_CASE(rNum) \
    case(rNum):\
        CPS_UncachedWrite32(CEDI_RegAddr(screening_type_2_register_##rNum),\
            reg); break;

    uint32_t reg;

    if ((pD==NULL) || (regVals==NULL))
        return EINVAL;

    if (CEDI_PdVar(hwCfg).num_type2_screeners==0)
        return ENOTSUP;

    if ((regNum>=CEDI_PdVar(hwCfg).num_type2_screeners) ||
        (regVals->qNum>=CEDI_PdVar(cfg).rxQs) ||
        (regVals->vlanEnable>1) ||
        (regVals->vlanEnable && (regVals->vlanPriority>=8)) ||
        (regVals->eTypeEnable>1) ||
        ((regVals->eTypeEnable) && (regVals->ethTypeIndex>=8)) ||
            ((regVals->eTypeEnable) &&
              (regVals->ethTypeIndex>=CEDI_PdVar(hwCfg).num_scr2_ethtype_regs)) ||
        (regVals->compAEnable>1) ||
        ((regVals->compAEnable) && (regVals->compAIndex>=32)) ||
            ((regVals->compAEnable) &&
              (regVals->compAIndex>=CEDI_PdVar(hwCfg).num_scr2_compare_regs)) ||
        (regVals->compBEnable>1) ||
        ((regVals->compBEnable) && (regVals->compBIndex>=32)) ||
            ((regVals->compBEnable) &&
              (regVals->compBIndex>=CEDI_PdVar(hwCfg).num_scr2_compare_regs)) ||
        (regVals->compCEnable>1) ||
        ((regVals->compCEnable) && (regVals->compCIndex>=32)) ||
            ((regVals->compCEnable) &&
              (regVals->compCIndex>=CEDI_PdVar(hwCfg).num_scr2_compare_regs)))
        return EINVAL;

    reg = 0;
    EMAC_REGS__SCREENING_TYPE_2_REGISTER__QUEUE_NUMBER__MODIFY(reg,
                                                            regVals->qNum);
    EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_ENABLE__MODIFY(reg,
                                                    regVals->vlanEnable);
    EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_PRIORITY__MODIFY(reg,
                                                    regVals->vlanPriority);
    EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_ENABLE__MODIFY(reg,
                                                    regVals->eTypeEnable);
    EMAC_REGS__SCREENING_TYPE_2_REGISTER__INDEX__MODIFY(reg,
                                                    regVals->ethTypeIndex);
    EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A_ENABLE__MODIFY(reg,
                                                    regVals->compAEnable);
    EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A__MODIFY(reg,
                                                    regVals->compAIndex);
    EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B_ENABLE__MODIFY(reg,
                                                    regVals->compBEnable);
    EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B__MODIFY(reg,
                                                    regVals->compBIndex);
    EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C_ENABLE__MODIFY(reg,
                                                    regVals->compCEnable);
    EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C__MODIFY(reg,
                                                    regVals->compCIndex);

    switch (regNum) {
        CEDI_WR_SCRN_TYPE2_REG_CASE(0)
        CEDI_WR_SCRN_TYPE2_REG_CASE(1)
        CEDI_WR_SCRN_TYPE2_REG_CASE(2)
        CEDI_WR_SCRN_TYPE2_REG_CASE(3)
        CEDI_WR_SCRN_TYPE2_REG_CASE(4)
        CEDI_WR_SCRN_TYPE2_REG_CASE(5)
        CEDI_WR_SCRN_TYPE2_REG_CASE(6)
        CEDI_WR_SCRN_TYPE2_REG_CASE(7)
        CEDI_WR_SCRN_TYPE2_REG_CASE(8)
        CEDI_WR_SCRN_TYPE2_REG_CASE(9)
        CEDI_WR_SCRN_TYPE2_REG_CASE(10)
        CEDI_WR_SCRN_TYPE2_REG_CASE(11)
        CEDI_WR_SCRN_TYPE2_REG_CASE(12)
        CEDI_WR_SCRN_TYPE2_REG_CASE(13)
        CEDI_WR_SCRN_TYPE2_REG_CASE(14)
        CEDI_WR_SCRN_TYPE2_REG_CASE(15)
    }
    return 0;
}

/* Read Rx frame matching values from a Type 2 screening register
 * @param pD - driver private state info specific to this instance
 * @param regNum - the Type 2 register number, range 0 to num_type2_screeners-1
 * @param regVals - points to a CEDI_T2Screen struct for returning the match
 *    parameters
 * @return 0 if successful, EINVAL if parameter invalid
 */
uint32_t emacGetType2ScreenReg(void *pD, uint8_t regNum, CEDI_T2Screen *regVals)
{
#define CEDI_RD_SCRN_TYPE2_REG_CASE(rNum) \
    case(rNum):\
        reg=CPS_UncachedRead32(CEDI_RegAddr(screening_type_2_register_##rNum));\
        break;

    uint32_t reg = 0;

    if ((pD==0)||(regVals==0))
        return EINVAL;

    if (CEDI_PdVar(hwCfg).num_type2_screeners==0)
        return ENOTSUP;

    if (regNum>=CEDI_PdVar(hwCfg).num_type2_screeners)
        return EINVAL;

    switch (regNum) {
        CEDI_RD_SCRN_TYPE2_REG_CASE(0)
        CEDI_RD_SCRN_TYPE2_REG_CASE(1)
        CEDI_RD_SCRN_TYPE2_REG_CASE(2)
        CEDI_RD_SCRN_TYPE2_REG_CASE(3)
        CEDI_RD_SCRN_TYPE2_REG_CASE(4)
        CEDI_RD_SCRN_TYPE2_REG_CASE(5)
        CEDI_RD_SCRN_TYPE2_REG_CASE(6)
        CEDI_RD_SCRN_TYPE2_REG_CASE(7)
        CEDI_RD_SCRN_TYPE2_REG_CASE(8)
        CEDI_RD_SCRN_TYPE2_REG_CASE(9)
        CEDI_RD_SCRN_TYPE2_REG_CASE(10)
        CEDI_RD_SCRN_TYPE2_REG_CASE(11)
        CEDI_RD_SCRN_TYPE2_REG_CASE(12)
        CEDI_RD_SCRN_TYPE2_REG_CASE(13)
        CEDI_RD_SCRN_TYPE2_REG_CASE(14)
        CEDI_RD_SCRN_TYPE2_REG_CASE(15)
    }
    regVals->qNum =
            EMAC_REGS__SCREENING_TYPE_2_REGISTER__QUEUE_NUMBER__READ(reg);
    regVals->vlanPriority =
            EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_PRIORITY__READ(reg);
    regVals->vlanEnable =
            EMAC_REGS__SCREENING_TYPE_2_REGISTER__VLAN_ENABLE__READ(reg);
    regVals->ethTypeIndex =
            EMAC_REGS__SCREENING_TYPE_2_REGISTER__INDEX__READ(reg);
    regVals->eTypeEnable =
            EMAC_REGS__SCREENING_TYPE_2_REGISTER__ETHERTYPE_ENABLE__READ(reg);
    regVals->compAIndex =
            EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A__READ(reg);
    regVals->compAEnable =
            EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_A_ENABLE__READ(reg);
    regVals->compBIndex =
            EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B__READ(reg);
    regVals->compBEnable =
            EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_B_ENABLE__READ(reg);
    regVals->compCIndex =
            EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C__READ(reg);
    regVals->compCEnable =
            EMAC_REGS__SCREENING_TYPE_2_REGISTER__COMPARE_C_ENABLE__READ(reg);
    return 0;
}

/* Write the ethertype compare value at the given index in the Ethertype
 * registers
 * @param pD - driver private state info specific to this instance
 * @param index - number of screener Type 2 Ethertype compare register to
 *    write, range 0 to num_scr2_ethtype_regs-1
 * @param eTypeVal - Ethertype compare value to write
 * @return 0 if successful, EINVAL if parameter invalid
 */
uint32_t emacSetType2EthertypeReg(void *pD, uint8_t index, uint16_t eTypeVal)
{
#define CEDI_WR_SCRN_TYPE2_ETHTYPE_REG_CASE(rNum) \
    case(rNum):\
        CPS_UncachedWrite32(CEDI_RegAddr(screening_type_2_ethertype_reg_##rNum),reg);\
        break;

    uint32_t reg;

    if (pD==NULL)
        return EINVAL;

    if ((CEDI_PdVar(hwCfg).num_type2_screeners==0) ||
            (CEDI_PdVar(hwCfg).num_scr2_ethtype_regs==0))
    return ENOTSUP;

    if (index>=CEDI_PdVar(hwCfg).num_scr2_ethtype_regs)
        return EINVAL;

    reg = 0;
    EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__COMPARE_VALUE__MODIFY(reg,
                                                                    eTypeVal);
    switch (index) {
        CEDI_WR_SCRN_TYPE2_ETHTYPE_REG_CASE(0)
        CEDI_WR_SCRN_TYPE2_ETHTYPE_REG_CASE(1)
        CEDI_WR_SCRN_TYPE2_ETHTYPE_REG_CASE(2)
        CEDI_WR_SCRN_TYPE2_ETHTYPE_REG_CASE(3)
        CEDI_WR_SCRN_TYPE2_ETHTYPE_REG_CASE(4)
        CEDI_WR_SCRN_TYPE2_ETHTYPE_REG_CASE(5)
        CEDI_WR_SCRN_TYPE2_ETHTYPE_REG_CASE(6)
        CEDI_WR_SCRN_TYPE2_ETHTYPE_REG_CASE(7)
    }
    return 0;
}

/* Read the ethertype compare value at the given index in the Ethertype
 * registers
 * @param pD - driver private state info specific to this instance
 * @param index - number of screener Type 2 Ethertype compare register to
 *    read, range 0 to num_scr2_ethtype_regs-1
 * @param eTypeVal - pointer for returning the Ethertype compare value
 * @return 0 if successful, EINVAL if parameter invalid
 */
uint32_t emacGetType2EthertypeReg(void *pD, uint8_t index, uint16_t *eTypeVal)
{
#define CEDI_RD_SCRN_TYPE2_ETHTYPE_REG_CASE(rNum) \
    case(rNum):\
        reg = CPS_UncachedRead32(CEDI_RegAddr(screening_type_2_ethertype_reg_##rNum));\
        break;

    uint32_t reg = 0;

    if ((pD==NULL)||(eTypeVal==NULL))
        return EINVAL;

    if ((CEDI_PdVar(hwCfg).num_type2_screeners==0) ||
            (CEDI_PdVar(hwCfg).num_scr2_ethtype_regs==0))
    return ENOTSUP;

    if (index>=CEDI_PdVar(hwCfg).num_scr2_ethtype_regs)
        return EINVAL;

    switch (index) {
        CEDI_RD_SCRN_TYPE2_ETHTYPE_REG_CASE(0)
        CEDI_RD_SCRN_TYPE2_ETHTYPE_REG_CASE(1)
        CEDI_RD_SCRN_TYPE2_ETHTYPE_REG_CASE(2)
        CEDI_RD_SCRN_TYPE2_ETHTYPE_REG_CASE(3)
        CEDI_RD_SCRN_TYPE2_ETHTYPE_REG_CASE(4)
        CEDI_RD_SCRN_TYPE2_ETHTYPE_REG_CASE(5)
        CEDI_RD_SCRN_TYPE2_ETHTYPE_REG_CASE(6)
        CEDI_RD_SCRN_TYPE2_ETHTYPE_REG_CASE(7)
    }
    *eTypeVal = (uint16_t)(
            EMAC_REGS__SCREENING_TYPE_2_ETHERTYPE_REG__COMPARE_VALUE__READ(reg));
    return 0;
}

/* Write the compare value at the given index in the Type 2 compare register
 * @param pD - driver private state info specific to this instance
 * @param index - number of the Type 2 compare register to write, range 0 to
 *    num_scr2_compare_regs-1
 * @param regVals - points to a CEDI_T2Compare struct with the compare
 *    parameters to be written
 * @return 0 if successful, EINVAL if parameter invalid
 */
uint32_t emacSetType2CompareReg(void *pD, uint8_t index, CEDI_T2Compare *regVals)
{
#define CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(rNum) \
    case(rNum):\
        CPS_UncachedWrite32(CEDI_RegAddr(type2_compare_##rNum##_word_0),reg0);\
        CPS_UncachedWrite32(CEDI_RegAddr(type2_compare_##rNum##_word_1),reg1);\
        break;

    uint32_t reg0, reg1;

    if ((pD==NULL)||(regVals==NULL))
        return EINVAL;

    if ((CEDI_PdVar(hwCfg).num_type2_screeners==0) ||
            (CEDI_PdVar(hwCfg).num_scr2_compare_regs==0))
    return ENOTSUP;

    if ((index>=CEDI_PdVar(hwCfg).num_scr2_compare_regs)
        || (regVals->offsetVal>0x3F)
        || (regVals->offsetPosition>CEDI_T2COMP_OFF_TCPUDP)
        || (regVals->disableMask>1))
        return EINVAL;

    reg0 = 0;
    reg1 = 0;
    EMAC_REGS__TYPE2_COMPARE_WORD_0__MASK_VALUE__MODIFY(reg0,
                                                        regVals->compMask);
    EMAC_REGS__TYPE2_COMPARE_WORD_0__COMPARE_VALUE__MODIFY(reg0,
                                                        regVals->compValue);
    EMAC_REGS__TYPE2_COMPARE_WORD_1__OFFSET_VALUE__MODIFY(reg1,
                                                        regVals->offsetVal);
    EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__MODIFY(reg1,
                                                    regVals->offsetPosition);
    EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__MODIFY(reg1,
                                                    regVals->disableMask);

    switch (index) {
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(0)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(1)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(2)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(3)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(4)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(5)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(6)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(7)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(8)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(9)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(10)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(11)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(12)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(13)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(14)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(15)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(16)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(17)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(18)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(19)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(20)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(21)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(22)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(23)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(24)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(25)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(26)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(27)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(28)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(29)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(30)
        CEDI_WR_SCRN_TYPE2_COMPARE_REG_CASE(31)
    }
    return 0;
}

/* Read the compare value at the given index in the Type 2 compare register
 * @param pD - driver private state info specific to this instance
 * @param index - number of the Type 2 compare register to read, range 0 to
 *    num_scr2_compare_regs-1
 * @param regVals - points to a CEDI_T2Compare struct for returning the
 *    compare parameters
 * @return 0 if successful, EINVAL if parameter invalid
 */
uint32_t emacGetType2CompareReg(void *pD, uint8_t index, CEDI_T2Compare *regVals)
{
#define CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(rNum) \
    case(rNum):\
        reg0=CPS_UncachedRead32(CEDI_RegAddr(type2_compare_##rNum##_word_0));\
        reg1=CPS_UncachedRead32(CEDI_RegAddr(type2_compare_##rNum##_word_1));\
        break;

    uint32_t reg0 = 0, reg1 = 0;

    if ((pD==0)||(regVals==0))
      return EINVAL;

    if ((CEDI_PdVar(hwCfg).num_type2_screeners==0) ||
            (CEDI_PdVar(hwCfg).num_scr2_compare_regs==0))
    return ENOTSUP;

    if (index>=CEDI_PdVar(hwCfg).num_scr2_compare_regs)
        return EINVAL;

    switch (index) {
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(0)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(1)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(2)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(3)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(4)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(5)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(6)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(7)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(8)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(9)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(10)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(11)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(12)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(13)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(14)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(15)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(16)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(17)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(18)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(19)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(20)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(21)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(22)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(23)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(24)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(25)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(26)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(27)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(28)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(29)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(30)
        CEDI_RD_SCRN_TYPE2_COMPARE_REG_CASE(31)
    }

    regVals->compMask =(uint16_t)(
        EMAC_REGS__TYPE2_COMPARE_WORD_0__MASK_VALUE__READ(reg0));
    regVals->compValue =(uint16_t)(
        EMAC_REGS__TYPE2_COMPARE_WORD_0__COMPARE_VALUE__READ(reg0));
    regVals->offsetVal =(uint8_t)(
        EMAC_REGS__TYPE2_COMPARE_WORD_1__OFFSET_VALUE__READ(reg1));
    regVals->offsetPosition =(CEDI_T2Offset)(
        EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__READ(reg1));
    regVals->disableMask = (uint8_t)(
        EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__READ(reg1));

    return 0;
}

#ifdef __cplusplus
}
#endif

#endif /* CY_IP_MXETH */
