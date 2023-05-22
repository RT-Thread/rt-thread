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
 ***********************************************************************
 * edd_int.h
 * Private declarations for Ethernet DMA-MAC Driver
 *
 ***********************************************************************/

 /****************************************************************************
* Modification by Infineon: To make this file compile with ModusToolbox
* toolchain
*****************************************************************************/

#ifndef _EDD_INT_H_
#define _EDD_INT_H_

#include "cy_device_headers.h"
#include "cedi.h"

#ifndef ETH_AXI_MASTER_PRESENT
  // Assumed that if "ETH_AXI_MASTER_PRESENT" did not exist in Cypress header file, AXI is present.
  #define ETH_AXI_MASTER_PRESENT 1
#endif

/******************************************************************************
 * Private Constants
 *****************************************************************************/

#define GEM_GXL_MODULE_ID_V0    (0x0007)
#define GEM_GXL_MODULE_ID_V1    (0x0107)
#define GEM_XL_MODULE_ID        (0x0008)

#define XGM_GXL_MODULE_ID       (0x000B)

#define OFFLOADS_GEM_GXL_REV    (0x0107)

#define CEDI_MIN_TXBD           1
#define CEDI_MIN_RXBD           1

#define MAX_JUMBO_FRAME_LENGTH  (16383)

/* Tx Descriptor flags/status - word 1 only */
#define CEDI_TXD_LAST_BUF       (1 << 15)
#define CEDI_TXD_NO_AUTO_CRC    (1 << 16)
#define CEDI_TXD_UFO_ENABLE     (1 << 17)
#define CEDI_TXD_TSO_ENABLE     (1 << 18)
#define CEDI_TXD_AUTOSEQ_SEL    (1 << 19)
#define CEDI_TXD_CHKOFF_SHIFT   (20)
#define CEDI_TXD_CHKOFF_MASK    (7 << CEDI_TXD_CHKOFF_SHIFT)
#define CEDI_TXD_TS_VALID       (1 << 23)
#define CEDI_TXD_STREAM_SHIFT   (24)
#define CEDI_TXD_STREAM_MASK    (3 << CEDI_TXD_STREAM_SHIFT)
#define CEDI_TXD_LATE_COLL      (1 << 26)
#define CEDI_TXD_FR_CORR        (1 << 27)
#define CEDI_TXD_UNDERRUN       (1 << 28)
#define CEDI_TXD_RETRY_EXC      (1 << 29)
#define CEDI_TXD_WRAP           (1 << 30)
#define CEDI_TXD_USED           (1 << 31)
/* MSS/MFS only used on word 1 of 2nd descriptor */
#define CEDI_TXD_MSSMFS_SHIFT   (16)
#define CEDI_TXD_MSSMFS_MASK    (0x3FFF << CEDI_TXD_MSSMFS_SHIFT)
#define CEDI_TXD_LEN_MASK       ((1 << 14) - 1)

/* Rx Descriptor flags - word 0 */
#define CEDI_RXD_USED        (1 << 0)
#define CEDI_RXD_WRAP        (1 << 1)
#define CEDI_RXD_TS_VALID    (1 << 2)
#define CEDI_RXD_ADDR_MASK   (0xFFFFFFFC)
#define CEDI_RXD_ADDR_SHIFT  (2)

/* Rx Descriptor flags/status - word 1 */
#define CEDI_RXD_LEN_MASK        ((1 << 13) - 1)
/*** need to include bit 13 if jumbo frames enabled ***/
#define CEDI_RXD_LEN13_FCS_STAT  (1 << 13)
#define CEDI_RXD_SOF             (1 << 14)
#define CEDI_RXD_EOF             (1 << 15)
#define CEDI_RXD_CFI             (1 << 16)
#define CEDI_RXD_VLAN_PRI_SHIFT  (17)
#define CEDI_RXD_VLAN_PRI_MASK   (7 << CEDI_RXD_VLAN_PRI_SHIFT)
/* if header-data splitting, these definitions are valid when not EOF: */
#define CEDI_RXD_HDR             (1 << 16)  /* header buffer */
#define CEDI_RXD_EOH             (1 << 17)  /* end of header */

#define CEDI_RXD_PRI_TAG         (1 << 20)
#define CEDI_RXD_VLAN_TAG        (1 << 21)
                // either Type ID match register or
                // (if Rx chksum offload enabled) checksum status
#define CEDI_RXD_TYP_IDR_CHK_STA_SHIFT (22)
#define CEDI_RXD_TYP_IDR_CHK_STA_MASK (3 << CEDI_RXD_TYP_IDR_CHK_STA_SHIFT)
                // either Type ID matched or
                // (if Rx chksum offload enabled) SNAP encoded and no CFI
#define CEDI_RXD_TYP_MAT_SNP_NCFI   (1 << 24)
#define CEDI_RXD_SPEC_REG_SHIFT     (25)
#define CEDI_RXD_SPEC_REG_MASK      (3 << CEDI_RXD_SPEC_REG_SHIFT)
#define CEDI_RXD_SPEC_ADD_MAT       (1 << 27)
#define CEDI_RXD_EXT_ADD_MAT        (1 << 28)
#define CEDI_RXD_UNI_HASH_MAT       (1 << 29)
#define CEDI_RXD_MULTI_HASH_MAT     (1 << 30)
#define CEDI_RXD_BROADCAST_DET      (1 << 31)

/* For Tx/Rx time stamp extraction from descriptor words */
#define CEDI_TS_NANO_SEC_MASK       (0x3FFFFFFF)
#define CEDI_TS_SEC0_SHIFT          (30)
#define CEDI_TS_SEC1_MASK           (0x0F)
#define CEDI_TS_SEC1_POS_SHIFT      (2)
#define CEDI_TS_SEC_WIDTH           (6U)
#define CEDI_TS_SEC_TOP             (1U << CEDI_TS_SEC_WIDTH)
#define CEDI_TS_SEC_MASK            (CEDI_TS_SEC_TOP - 1U)



#define CEDI_RXD_EMPTY              (0xFFAA0000)

#define CEDI_PHY_ADDR_OP             (0)
#define CEDI_PHY_WRITE_OP            (1)
#define CEDI_PHY_CL22_READ_OP        (2)
#define CEDI_PHY_CL45_READ_INC_OP    (2)
#define CEDI_PHY_CL45_READ_OP        (3)


#define CEDI_TWO_BD_WORD_SIZE        (8)    // Size required for two buffer descriptor word (in bytes).
#define CEDI_BYTES_PER_WORD_SHIFT    (2)    // Shift variable for number of bytes in a word
#define CEDI_DESC_WORD_NUM_MAX       (6)    // Maximum number of words allowed in a descriptor.

#define CEDI_AMBD_BURST_LEN_1     (0x01)    // for CEDI_DMA_DBUR_LEN_1
#define CEDI_AMBD_BURST_LEN_4     (0x04)    // for CEDI_DMA_DBUR_LEN_4
#define CEDI_AMBD_BURST_LEN_8     (0x08)    // for CEDI_DMA_DBUR_LEN_8
#define CEDI_AMBD_BURST_LEN_16    (0x10)    // for CEDI_DMA_DBUR_LEN_16

/******************************************************************************
 * Local macros - assume pD is privateData parameter in function scope, and
 * cfg has been initialised with register base address
 *****************************************************************************/

/* access a privateData field, via the local void *pD parameter */
#define CEDI_PdVar(var) (((CEDI_PrivateData *)pD)->var)
/* get register address via the privateDat->cfg.regBase field */
#define CEDI_RegAddr(reg) (&(((struct emac_regs *)(CEDI_PdVar(cfg).regBase))->reg))

/******************************************************************************
 * Types
 *****************************************************************************/

/* Tx Descriptor defs */
typedef struct {
    uint32_t word[CEDI_DESC_WORD_NUM_MAX];
} txDesc;

typedef struct {
    txDesc      *bdBase;        // base address of descriptor ring
    txDesc      *bdHead;        // first available descriptor
    txDesc      *bdTail;        // first descriptor waiting to be freed
    txDesc      *bd1stBuf;      // first buffer of current frame
    uint16_t    descMax;        // total number of descriptors
    uint16_t    descFree;       // number of descriptors that can accept buffers
    uintptr_t   *vHead;         // virt address corresponding to head BD
    uintptr_t   *vTail;         // end of virt address circular array
    uintptr_t   *vAddrList;     // pointer to virt addresses storage
    uint8_t     firstToFree;    // flag indicating stage of frame clean-up: set
                                // when about to clear first buffer of frame
    uint8_t     descNum;        // descriptor counter used by qTxBuf: stays at 0 until
                                // start 2nd desc of frame, then inc to 1, etc.
} txQueue_t;

/* Rx Descriptor defs */
typedef struct {
    uint32_t word[CEDI_DESC_WORD_NUM_MAX];
} rxDesc;

typedef struct {
    rxDesc *rxDescStart;        // start of Rx descriptor list
    rxDesc *rxDescStop;         // end-stop Rx descriptor, trails behind "Tail";
                                //  always kept "used" but with no buffer
    rxDesc *rxDescTail;         // next Rx descriptor to process (one after end-stop)
    rxDesc *rxDescEnd;          // last descriptor in Rx list
    uint16_t numRxDesc;         // total number of descriptors in the list,
                                //  including unused end-stop
    uint16_t numRxBufs;         // number of useable buffers/descriptors in list
    uintptr_t *rxTailVA;        // tail Rx virtual addr
    uintptr_t *rxStopVA;        // end-stop Rx virtual addr, corr. to rxDescStop
    uintptr_t *rxEndVA;         // end Rx virtual addr
    uintptr_t *rxBufVAddr;      // list of buffer virtual addresses in sync
                            // with physical addresses held in descriptor lists
} rxQueue_t;

/* Driver private data - place the tx & rx virtual address lists after this
 * (with these included in privateData memory requirement) */
typedef struct {
    CEDI_Config      cfg;            // copy of CEDI_Config info supplied to init
    CEDI_Callbacks   cb;             // pointers to callback functions
    CEDI_DesignCfg   hwCfg;          // copy of DesignCfg Debug registers
    uint8_t         numQs;          // number of Qs in this h/w config.
    txQueue_t txQueue[CEDI_MAX_TX_QUEUES];   // tx queue info
    rxQueue_t rxQueue[CEDI_MAX_RX_QUEUES];   // rx queue info
//    CPS_LockHandle  isrLock;        // lock used during isr calls
    uint8_t         anLinkStat;     // retain link status (low) until read
    uint8_t         anRemFault;     // retain link partner remote fault status
                                    //  (high) until read
    uint8_t         autoNegActive;  // auto-negotiation in progress flag
    uint8_t         basePageExp;    // data expected from link partner: set
                                    // initially to indicate base page, clear
                                    // after first received to denote next page
                                    // expected. Set on start auto-negotiation.

    CEDI_LpPageRx    lpPageRx;       // reserved for passing page Rx in callback
    CEDI_NetAnStatus anStatus;       // reserved for a-n status in callback
    CEDI_1588TimerVal ptpTime;       // reserved for passing ptp event times
//    CPS_LockHandle  autoNegLock;    // lock to protect auto-neg flags and next
                                    // page register when isr writes null
                                    // message page
    uint16_t txDescriptorSize;      // bytes per Tx descriptor
    uint16_t rxDescriptorSize;      // bytes per Rx descriptor
} CEDI_PrivateData;


/*********************** Internal Driver functions ***************************/

uint32_t initRxDescLists(void *pD);
uint32_t subNsTsuInc24bSupport(void *pD);

/* Driver API function prototypes (only required if called within API) */

uint32_t emacSetEventEnable(void *pD, uint32_t events, uint8_t enable,
        uint8_t queueNum);
uint32_t emacResetPcs(void *pD);
uint32_t emacWriteUserOutputs(void *pD, uint16_t outVal);
uint32_t emacGetJumboFramesRx(void *pD, uint8_t *enable);
uint32_t emacGetJumboFrameRxMaxLen(void *pD, uint16_t *length);
uint32_t emacGet1536ByteFramesRx(void *pD, uint8_t *enable);
uint32_t emacGetPtpFrameTxTime(void *pD, CEDI_1588TimerVal *time);
uint32_t emacGetPtpFrameRxTime(void *pD, CEDI_1588TimerVal *time);
uint32_t emacGetPtpPeerFrameTxTime(void *pD, CEDI_1588TimerVal *time);
uint32_t emacGetPtpPeerFrameRxTime(void *pD, CEDI_1588TimerVal *time);
uint32_t emacClearStats(void *pD);

uint32_t emacSetAutoNegEnable(void *pD, uint8_t enable);
uint32_t emacGetPcsReady(void *pD, uint8_t *ready);
uint32_t emacGetLinkStatus(void *pD, uint8_t *status);
uint32_t emacSetAnAdvPage(void *pD, CEDI_AnAdvPage *advDat);
uint32_t emacGetLpAbilityPage(void *pD, CEDI_LpAbilityPage *lpAbl);
uint32_t emacGetLpNextPage(void *pD, CEDI_LpNextPage *npDat);
uint32_t emacSetNextPageTx(void *pD, CEDI_AnNextPage *npDat);

/****************** API Prototypes for other source modules ******************/

/****************************** edd_tx.c *************************************/

uint32_t emacCalcMaxTxFrameSize(void *pD, CEDI_FrameSize *maxTxSize);

uint32_t emacQueueTxBuf(void *pD, uint8_t queueNum, CEDI_BuffAddr *bufAdd,
        uint32_t length, uint8_t flags);

uint32_t emacQTxBuf(void *pD, CEDI_qTxBufParams *prm);

uint32_t emacDeQTxBuf(void *pD, CEDI_qTxBufParams *prm);

uint32_t emacTxDescFree(void *pD, uint8_t queueNum, uint16_t *numFree);

uint32_t emacFreeTxDesc(void *pD, uint8_t queueNum, CEDI_TxDescData *descData);

void emacGetTxDescStat(void *pD, uint32_t txDStatWord, CEDI_TxDescStat *txDStat);

void emacGetTxDescSize(void *pD, uint32_t *txDescSize);

uint32_t emacResetTxQ(void *pD, uint8_t queueNum);

uint32_t emacStartTx(void *pD);

void emacStopTx(void *pD);

void emacAbortTx(void *pD);

uint32_t emacTransmitting(void *pD);

void emacEnableTx(void *pD);

uint32_t emacGetTxEnabled(void *pD);

uint32_t emacGetTxStatus(void *pD, CEDI_TxStatus *status);

void emacClearTxStatus(void *pD, uint32_t resetStatus);

uint32_t emacSetTxPartialStFwd(void *pD, uint32_t watermark, uint8_t enable);

uint32_t emacGetTxPartialStFwd(void *pD, uint32_t *watermark, uint8_t *enable);


uint32_t emacEnableCbs(void *pD, uint8_t qSel, uint32_t idleSlope);

void emacDisableCbs(void *pD, uint8_t qSel);

uint32_t emacGetCbsQSetting(void *pD, uint8_t qSel,
               uint8_t *enable, uint32_t *idleSlope);


uint32_t emacSetIpgStretch(void *pD, uint8_t enable, uint8_t multiplier,
        uint8_t divisor);

uint32_t emacGetIpgStretch(void *pD, uint8_t *enabled, uint8_t *multiplier,
        uint8_t *divisor);



/****************************** edd_rx.c *************************************/

uint32_t emacCalcMaxRxFrameSize(void *pD, uint32_t *maxSize);

uint32_t emacAddRxBuf(void *pD, uint8_t queueNum, CEDI_BuffAddr *buf,
        uint8_t init);

uint32_t emacNumRxBufs(void *pD, uint8_t queueNum, uint16_t *numBufs);

uint32_t emacNumRxUsed(void *pD, uint8_t queueNum);

uint32_t emacReadRxBuf(void *pD, uint8_t queueNum, CEDI_BuffAddr *buf,
                            uint8_t init, CEDI_RxDescData *descData);

void emacGetRxDescStat(void *pD, uint32_t rxDStatWord, CEDI_RxDescStat *rxDStat);

void emacGetRxDescSize(void *pD, uint32_t *rxDescSize);

uint32_t emacRxEnabled(void *pD);

void emacEnableRx(void *pD);

void emacDisableRx(void *pD);

uint32_t emacRemoveRxBuf(void *pD, uint8_t queueNum, CEDI_BuffAddr *buf);

void emacFindQBaseAddr(void *pD, uint8_t queueNum, rxQueue_t *rxQ,
                        uint32_t *pAddr, uintptr_t *vAddr);

uint32_t emacResetRxQ(void *pD, uint8_t queueNum, uint8_t ptrsOnly);

uint32_t emacGetRxStatus(void *pD, CEDI_RxStatus *status);

void emacClearRxStatus(void *pD, uint32_t resetStatus);


uint32_t emacSetHdrDataSplit(void *pD, uint8_t enable);

uint32_t emacGetHdrDataSplit(void *pD, uint8_t *enable);

uint32_t emacSetRscEnable(void *pD, uint8_t queue, uint8_t enable);

uint32_t emacGetRscEnable(void *pD, uint8_t queue, uint8_t *enable);

uint32_t emacSetRscClearMask(void *pD, uint8_t setMask);


uint32_t emacSetRxPartialStFwd(void *pD, uint32_t watermark, uint8_t enable);

uint32_t emacGetRxPartialStFwd(void *pD, uint32_t *watermark, uint8_t *enable);

uint32_t emacSetSpecificAddr(void *pD, uint8_t addrNum, CEDI_MacAddress *addr,
         uint8_t specFilterType,uint8_t byteMask);

uint32_t emacGetSpecificAddr(void *pD, uint8_t addrNum, CEDI_MacAddress *addr,
         uint8_t *specFilterType, uint8_t *byteMask);

uint32_t emacSetSpecificAddr1Mask(void *pD, CEDI_MacAddress *mask);

uint32_t emacGetSpecificAddr1Mask(void *pD, CEDI_MacAddress *mask);

uint32_t emacDisableSpecAddr(void *pD, uint8_t addrNum);

uint32_t emacSetTypeIdMatch(void *pD, uint8_t matchSel, uint16_t typeId,
        uint8_t enable);

uint32_t emacGetTypeIdMatch(void *pD, uint8_t matchSel, uint16_t *typeId,
        uint8_t *enabled);

void emacSetUnicastEnable(void *pD, uint8_t enable);

uint32_t emacGetUnicastEnable(void *pD, uint8_t *enable);

void emacSetMulticastEnable(void *pD, uint8_t enable);

uint32_t emacGetMulticastEnable(void *pD, uint8_t *enable);

void emacSetNoBroadcast(void *pD, uint8_t reject);

uint32_t emacGetNoBroadcast(void *pD, uint8_t *reject);

void emacSetVlanOnly(void *pD, uint8_t enable);

uint32_t emacGetVlanOnly(void *pD, uint8_t *enable);

void emacSetStackedVlanReg(void *pD, uint8_t enable, uint16_t vlanType);

void emacGetStackedVlanReg(void *pD, uint8_t *enable, uint16_t *vlanType);

void emacSetCopyAllFrames(void *pD, uint8_t enable);

uint32_t emacGetCopyAllFrames(void *pD, uint8_t *enable);

uint32_t emacSetHashAddr(void *pD, uint32_t hAddrTop, uint32_t hAddrBot);

uint32_t emacGetHashAddr(void *pD, uint32_t *hAddrTop, uint32_t *hAddrBot);

void emacSetLenErrDiscard(void *pD, uint8_t enable);

uint32_t emacGetLenErrDiscard(void *pD, uint8_t *enable);


uint32_t emacGetNumScreenRegs(void *pD, CEDI_NumScreeners *regNums);

uint32_t emacSetType1ScreenReg(void *pD, uint8_t regNum, CEDI_T1Screen *regVals);

uint32_t emacGetType1ScreenReg(void *pD, uint8_t regNum, CEDI_T1Screen *regVals);

uint32_t emacSetType2ScreenReg(void *pD, uint8_t regNum, CEDI_T2Screen *regVals);

uint32_t emacGetType2ScreenReg(void *pD, uint8_t regNum, CEDI_T2Screen *regVals);

uint32_t emacSetType2EthertypeReg(void *pD, uint8_t index, uint16_t eTypeVal);

uint32_t emacGetType2EthertypeReg(void *pD, uint8_t index, uint16_t *eTypeVal);

uint32_t emacSetType2CompareReg(void *pD, uint8_t index,
        CEDI_T2Compare *regVals);

uint32_t emacGetType2CompareReg(void *pD, uint8_t index,
        CEDI_T2Compare *regVals);


#endif /* multiple inclusion protection */
