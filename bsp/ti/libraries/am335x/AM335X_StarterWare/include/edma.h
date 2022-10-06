/**
 *  \file       edma.h
 *
 *  \brief      This file contains the function prototypes for the device
 *              abstraction layer for EDMA. It also contains some
 *              related macro definitions and some files to be included.
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef __EDMA_H__
#define __EDMA_H__

#include <stdio.h>
#include <stdlib.h>
#include "hw_edma3cc.h"
#include "hw_edma3tc.h"

#ifdef __cplusplus
extern "C" {
#endif
//***********************************************************************
//  Values that can be used by the application for configuration via APIs
//***********************************************************************/

/** Maximum number of EDMA Shadow regions available */
#define EDMA3_MAX_REGIONS                     (2u)

/** Number of PaRAM Sets available */
#define EDMA3_NUM_PARAMSET                    (128u)

/** Number of Event Queues available */
#define EDMA3_0_NUM_EVTQUE                    (2u)

/** Number of Transfer Controllers available */
#define EDMA3_0_NUM_TC                        (2u)

/** Interrupt no. for Transfer Completion */
#define EDMA3_0_CC_XFER_COMPLETION_INT        (11u)

/** Interrupt no. for CC Error */
#define EDMA3_0_CC0_ERRINT                    (12u)

/** Interrupt no. for TCs Error */
#define EDMA3_0_TC0_ERRINT                    (13u)
#define EDMA3_0_TC1_ERRINT                    (32u)

#define EDMA3CC_DMA_CHANNELS                  (32u)
#define EDMA3CC_QDMA_CHANNELS                 (8u)

/** DMAQNUM bits Clear */
#define EDMA3CC_DMAQNUM_CLR(chNum)            ( ~ (0x7u << (((chNum) % 8u) \
                                                                      * 4u)))
/** DMAQNUM bits Set */
#define EDMA3CC_DMAQNUM_SET(chNum,queNum)     ((0x7u & (queNum)) << \
                                                       (((chNum) % 8u) * 4u))
/** QDMAQNUM bits Clear */
#define EDMA3CC_QDMAQNUM_CLR(chNum)           ( ~ (0x7u << ((chNum) * 4u)))
/** QDMAQNUM bits Set */
#define EDMA3CC_QDMAQNUM_SET(chNum,queNum)    ((0x7u & (queNum)) << \
                                                           ((chNum) * 4u))

#define EDMA3CC_QCHMAP_PAENTRY_CLR            (~EDMA3CC_QCHMAP_PAENTRY)
/** QCHMAP-PaRAMEntry bitfield Set */
#define EDMA3CC_QCHMAP_PAENTRY_SET(paRAMId)   (((EDMA3CC_QCHMAP_PAENTRY >> \
                                              EDMA3CC_QCHMAP_PAENTRY_SHIFT) & \
                                              (paRAMId)) << \
                                              EDMA3CC_QCHMAP_PAENTRY_SHIFT)
/** QCHMAP-TrigWord bitfield Clear */
#define EDMA3CC_QCHMAP_TRWORD_CLR             (~EDMA3CC_QCHMAP_TRWORD)
/** QCHMAP-TrigWord bitfield Set */
#define EDMA3CC_QCHMAP_TRWORD_SET(paRAMId)    (((EDMA3CC_QCHMAP_TRWORD >> \
                                              EDMA3CC_QCHMAP_TRWORD_SHIFT) & \
                                              (paRAMId)) << \
                                              EDMA3CC_QCHMAP_TRWORD_SHIFT)

/** OPT-TCC bitfield Clear */
#define EDMA3CC_OPT_TCC_CLR                   (~EDMA3CC_OPT_TCC)

/** OPT-TCC bitfield Set */
#define EDMA3CC_OPT_TCC_SET(tcc)              (((EDMA3CC_OPT_TCC >> \
                                              EDMA3CC_OPT_TCC_SHIFT) & \
                                              (tcc)) << EDMA3CC_OPT_TCC_SHIFT)

#define EDMA3_SET_ALL_BITS                    (0xFFFFFFFFu)
#define EDMA3_CLR_ALL_BITS                    (0x00000000u)

#define EDMA3CC_COMPL_HANDLER_RETRY_COUNT     (10u)
#define EDMA3CC_ERR_HANDLER_RETRY_COUNT       (10u)

#define EDMA3_TRIG_MODE_MANUAL                (0u)
#define EDMA3_TRIG_MODE_QDMA                  (1u)
#define EDMA3_TRIG_MODE_EVENT                 (2u)

#define EDMA3_CHANNEL_TYPE_DMA                (0u)
#define EDMA3_CHANNEL_TYPE_QDMA               (1u)


#define EDMA3_XFER_COMPLETE                   (0u)
#define EDMA3_CC_DMA_EVT_MISS                 (1u)
#define EDMA3_CC_QDMA_EVT_MISS                (2u)

#define EDMA3_SYNC_A                          (0u)
#define EDMA3_SYNC_AB                         (1u)

#define EDMA3CC_CLR_TCCERR                     EDMA3CC_CCERRCLR_TCCERR
#define EDMA3CC_CLR_QTHRQ0                     EDMA3CC_CCERRCLR_QTHRXCD0
#define EDMA3CC_CLR_QTHRQ1                     EDMA3CC_CCERRCLR_QTHRXCD1


/* paRAMEntry Fields*/
    /**
     * The OPT field (Offset Address 0x0 Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_OPT            (0x0u)

    /**
     * The SRC field (Offset Address 0x4 Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_SRC            (0x1u)

    /**
     * The (ACNT+BCNT) field (Offset Address 0x8 Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_ACNT_BCNT      (0x2u)

    /**
     * The DST field (Offset Address 0xC Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_DST            (0x3u)

    /**
     * The (SRCBIDX+DSTBIDX) field (Offset Address 0x10 Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_SRC_DST_BIDX   (0x4u)

    /**
     * The (LINK+BCNTRLD) field (Offset Address 0x14 Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_LINK_BCNTRLD   (0x5u)

    /**
     * The (SRCCIDX+DSTCIDX) field (Offset Address 0x18 Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_SRC_DST_CIDX   (0x6u)

    /**
     * The (CCNT+RSVD) field (Offset Address 0x1C Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_CCNT           (0x7u)


/** The offset for each PaRAM Entry field  */
#define    EDMA3CC_PARAM_FIELD_OFFSET         (0x4u)

/** Number of PaRAM Entry fields
  * OPT, SRC, A_B_CNT, DST, SRC_DST_BIDX, LINK_BCNTRLD, SRC_DST_CIDX
  * and CCNT
  */
#define    EDMA3CC_PARAM_ENTRY_FIELDS         (0x8u)


#define    EDMA_REVID_AM335X                  (0x02u)

#if defined(am335x) || defined(am335x_13x13) || defined(am335x_15x15) || \
    defined(c6a811x) || defined(am386x) || defined(c6741x)
#define SOC_EDMA3_NUM_DMACH                 64
#define SOC_EDMA3_NUM_QDMACH                8
#define SOC_EDMA3_NUM_PARAMSETS             256
#define SOC_EDMA3_NUM_EVQUE                 4
#define SOC_EDMA3_CHMAPEXIST                0
#define SOC_EDMA3_NUM_REGIONS               8
#define SOC_EDMA3_MEMPROTECT                0
#endif

#if defined(am1808) || defined(omapl138) || defined(c6748)
#define SOC_EDMA3_NUM_DMACH                 32
#define SOC_EDMA3_NUM_QDMACH                8
#define SOC_EDMA3_NUM_PARAMSETS             128
#define SOC_EDMA3_NUM_EVQUE                 2
#define SOC_EDMA3_CHMAPEXIST                0
#define SOC_EDMA3_NUM_REGIONS               4
#define SOC_EDMA3_MEMPROTECT                0
#endif

/** Number of TCCS available */
#define EDMA3_NUM_TCC                        SOC_EDMA3_NUM_DMACH

/**
 * \brief EDMA3 Parameter RAM Set in User Configurable format
 *
 * This is a mapping of the EDMA3 PaRAM set provided to the user
 * for ease of modification of the individual fields
 */
typedef struct EDMA3CCPaRAMEntry {
        /** OPT field of PaRAM Set */
        unsigned int opt;

        /**
         * \brief Starting byte address of Source
         * For FIFO mode, srcAddr must be a 256-bit aligned address.
         */
        unsigned int srcAddr;

        /**
         * \brief Number of bytes in each Array (ACNT)
         */
        unsigned short aCnt;

        /**
         * \brief Number of Arrays in each Frame (BCNT)
         */
        unsigned short bCnt;

        /**
         * \brief Starting byte address of destination
         * For FIFO mode, destAddr must be a 256-bit aligned address.
         * i.e. 5 LSBs should be 0.
         */
        unsigned int destAddr;

        /**
         * \brief Index between consec. arrays of a Source Frame (SRCBIDX)
         */
        short  srcBIdx;

        /**
         * \brief Index between consec. arrays of a Destination Frame (DSTBIDX)
         */
        short  destBIdx;

        /**
         * \brief Address for linking (AutoReloading of a PaRAM Set)
         * This must point to a valid aligned 32-byte PaRAM set
         * A value of 0xFFFF means no linking
         */
        unsigned short linkAddr;

        /**
         * \brief Reload value of the numArrInFrame (BCNT)
         * Relevant only for A-sync transfers
         */
        unsigned short bCntReload;

        /**
         * \brief Index between consecutive frames of a Source Block (SRCCIDX)
         */
        short  srcCIdx;

        /**
         * \brief Index between consecutive frames of a Dest Block (DSTCIDX)
         */
        short  destCIdx;

        /**
         * \brief Number of Frames in a block (CCNT)
         */
        unsigned short cCnt;

        /**
         * \brief  This field is Reserved. Write zero to this field.
         */
        unsigned short rsvd;

}EDMA3CCPaRAMEntry;

/*
** Structure to store the EDMA context
*/
typedef struct edmaContext {
    /* Channel mapping reg Val */
    unsigned int dchMap[64];
    /* DMA Queue Number Register Val */    
    unsigned int dmaQNum[8];    
    
    /* DMA Region Access Enable Register val */    
    unsigned int regAccEnableLow;    
    unsigned int regAccEnableHigh;        

    /* Event Set Register value */    
    unsigned int eventSetRegLow;
    unsigned int eventSetRegHigh;    
    
    /* Enable Event Set Register value */    
    unsigned int enableEvtSetRegLow;
    unsigned int enableEvtSetRegHigh;
    
    /* Interrupt Enable Set Register value */            
    unsigned int intEnableSetRegLow;        
    unsigned int intEnableSetRegHigh;    
    
    struct EDMA3CCPaRAMEntry dmaParEntry[512];    
    
} EDMACONTEXT;

/****************************************************************************
**                 API FUNCTION PROTOTYPES
****************************************************************************/


void EDMA3Init(unsigned int baseAdd,
               unsigned int queNum);

void EDMA3EnableChInShadowReg(unsigned int baseAdd,
                              unsigned int chType,
                              unsigned int chNum);

void EDMA3DisableChInShadowReg(unsigned int baseAdd,
                               unsigned int chType,
                               unsigned int chNum);

void EDMA3MapChToEvtQ(unsigned int baseAdd,
                      unsigned int chType,
                      unsigned int chNum,
                      unsigned int evtQNum);

void EDMA3UnmapChToEvtQ(unsigned int baseAdd,
                        unsigned int chType,
                        unsigned int chNum);

void EDMA3MapQdmaChToPaRAM(unsigned int baseAdd,
                           unsigned int chNum,
                           unsigned int *paRAMId);

void EDMA3SetQdmaTrigWord(unsigned int baseAdd,
                          unsigned int chNum,
                          unsigned int trigWord);

void EDMA3ClrMissEvt(unsigned int baseAdd,
                     unsigned int chNum);

void EDMA3QdmaClrMissEvt(unsigned int baseAdd,
                         unsigned int chNum);

void EDMA3ClrCCErr(unsigned int baseAdd,
                   unsigned int Flags);

void EDMA3SetEvt(unsigned int baseAdd,
                 unsigned int chNum);

void EDMA3ClrEvt(unsigned int baseAdd,
                 unsigned int chNum);

void EDMA3EnableDmaEvt(unsigned int baseAdd,
                       unsigned int chNum);

void EDMA3DisableDmaEvt(unsigned int baseAdd,
                        unsigned int chNum);

void EDMA3EnableQdmaEvt(unsigned int baseAdd,
                        unsigned int chNum);

void EDMA3DisableQdmaEvt(unsigned int baseAdd,
                         unsigned int chNum);

unsigned int EDMA3GetIntrStatus(unsigned int baseAdd);

void EDMA3EnableEvtIntr(unsigned int baseAdd,
                        unsigned int chNum);

void EDMA3DisableEvtIntr(unsigned int baseAdd,
                         unsigned int chNum);

void EDMA3ClrIntr(unsigned int baseAdd, unsigned int value);

void EDMA3GetPaRAM(unsigned int baseAdd,
                   unsigned int chNum,
                   EDMA3CCPaRAMEntry* currPaRAM);

void EDMA3QdmaGetPaRAM(unsigned int baseAdd,
                       unsigned int chNum,
                       unsigned int paRAMId,
                       EDMA3CCPaRAMEntry* currPaRAM);

void EDMA3SetPaRAM(unsigned int baseAdd,
                   unsigned int chNum,
                   EDMA3CCPaRAMEntry* newPaRAM);

void EDMA3QdmaSetPaRAM(unsigned int baseAdd,
                       unsigned int chNum,
                       unsigned int paRAMId,
                       EDMA3CCPaRAMEntry* newPaRAM);

void EDMA3QdmaSetPaRAMEntry(unsigned int baseAdd,
                            unsigned int paRAMId,
                            unsigned int paRAMEntry,
                            unsigned int newPaRAMEntryVal);

unsigned int EDMA3QdmaGetPaRAMEntry(unsigned int baseAdd,
                                    unsigned int paRAMId,
                                    unsigned int paRAMEntry);

unsigned int EDMA3RequestChannel(unsigned int baseAdd, unsigned int chType,
                                 unsigned int chNum, unsigned int tccNum,
                                 unsigned int evtQNum);

unsigned int EDMA3FreeChannel(unsigned int baseAdd, unsigned int chType,
                              unsigned int chNum, unsigned int trigMode,
                              unsigned int tccNum, unsigned int evtQNum);

unsigned int EDMA3EnableTransfer(unsigned int baseAdd,
                                 unsigned int chNum,
                                 unsigned int trigMode);

unsigned int EDMA3DisableTransfer(unsigned int baseAdd,
                                  unsigned int chNum,
                                  unsigned int trigMode);

void EDMA3ClearErrorBits(unsigned int baseAdd,
                         unsigned int chNum,
                         unsigned int evtQNum);

unsigned int EDMA3GetCCErrStatus(unsigned int baseAdd);

unsigned int EDMA3GetErrIntrStatus(unsigned int baseAdd);

unsigned int EDMA3QdmaGetErrIntrStatus(unsigned int baseAdd);

void EDMA3CCErrorEvaluate(unsigned int baseAddr);

void EDMA3Deinit(unsigned int baseAdd,
                 unsigned int queNum);

unsigned int EDMAVersionGet(void);

unsigned int EDMA3PeripheralIdGet(unsigned int baseAdd);
unsigned int EDMA3IntrStatusHighGet(unsigned int baseAdd);
unsigned int EDMA3ErrIntrHighStatusGet(unsigned int baseAdd);

void EDMA3ChannelToParamMap(unsigned int baseAdd,
                            unsigned int channel,
                            unsigned int paramSet);

extern void EDMA3ContextSave(unsigned int baseAddr,
                                EDMACONTEXT *edmaCntxPtr);
extern void EDMA3ContextRestore(unsigned int baseAddr,
                                EDMACONTEXT *edmaCntxPtr);

#ifdef __cplusplus
}
#endif
#endif

/* !! EOF !!                                                                  */
