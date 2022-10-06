/**
 *  \file   cpsw.h
 *
 *  \brief  CPSW APIs and macros.
 *
 *   This file contains the driver API prototypes and macro definitions.
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

#ifndef __CPSW_H__
#define __CPSW_H__

#include "hw_cpsw_ale.h"
#include "hw_cpsw_cpdma.h"
#include "hw_cpsw_port.h"
#include "hw_cpsw_sl.h"
#include "hw_cpsw_ss.h"
#include "hw_cpsw_wr.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/*
** Macros which can be used as 'mode' to pass to the API CPSWSlTransferModeSet
*/
#define CPSW_SLIVER_NON_GIG_FULL_DUPLEX        CPSW_SL_MACCONTROL_FULLDUPLEX
#define CPSW_SLIVER_NON_GIG_HALF_DUPLEX        (0x00u)
#define CPSW_SLIVER_GIG_FULL_DUPLEX            CPSW_SL_MACCONTROL_GIG
#define CPSW_SLIVER_INBAND                     CPSW_SL_MACCONTROL_EXT_EN

/*
** Macros which can be used as 'statFlag' to the API CPSWSlMACStatusGet
*/
#define CPSW_SLIVER_STATE                      CPSW_SL_MACSTATUS_IDLE
#define CPSW_SLIVER_EXT_GIG_INPUT_BIT          CPSW_SL_MACSTATUS_EXT_GIG
#define CPSW_SLIVER_EXT_FULL_DUPLEX_BIT        CPSW_SL_MACSTATUS_EXT_FULLDUPLEX
#define CPSW_SLIVER_RX_FLOWCTRL                CPSW_SL_MACSTATUS_RX_FLOW_ACT
#define CPSW_SLIVER_TX_FLOWCTRL                CPSW_SL_MACSTATUS_TX_FLOW_ACT

/*
** Macros returned by API CPSWSlMACStatusGet
*/
#define CPSW_SLIVER_STATE_IDLE                 CPSW_SL_MACSTATUS_IDLE
#define CPSW_SLIVER_EXT_GIG_INPUT_HIGH         CPSW_SL_MACSTATUS_EXT_GIG
#define CPSW_SLIVER_EXT_FULL_DUPLEX_HIGH       CPSW_SL_MACSTATUS_EXT_FULLDUPLEX
#define CPSW_SLIVER_RX_FLOWCTRL_ACTIVE         CPSW_SL_MACSTATUS_RX_FLOW_ACT
#define CPSW_SLIVER_TX_FLOWCTRL_ACTIVE         CPSW_SL_MACSTATUS_TX_FLOW_ACT

/*
** Macros which can be passed asi 'intFlag' to the API CPSWWrCoreIntEnable
** , CPSWWrCoreIntDisable and CPSWWrCoreIntStatusGet
*/
#define CPSW_CORE_INT_RX_THRESH                (0x00u)
#define CPSW_CORE_INT_RX_PULSE                 (0x04u)
#define CPSW_CORE_INT_TX_PULSE                 (0x08u)
#define CPSW_CORE_INT_MISC                     (0x0Cu)

/*
** Macros which can be passed as 'statFlag' to the API CPSWWrRGMIIStatusGet
*/
#define CPSW_RGMII2_DUPLEX                     CPSW_WR_RGMII_CTL_RGMII2_FULLDUPLEX
#define CPSW_RGMII2_SPEED                      CPSW_WR_RGMII_CTL_RGMII2_SPEED
#define CPSW_RGMII2_LINK_STAT                  CPSW_WR_RGMII_CTL_RGMII2_LINK
#define CPSW_RGMII1_DUPLEX                     CPSW_WR_RGMII_CTL_RGMII1_FULLDUPLEX
#define CPSW_RGMII1_SPEED                      CPSW_WR_RGMII_CTL_RGMII1_SPEED
#define CPSW_RGMII1_LINK_STAT                  CPSW_WR_RGMII_CTL_RGMII1_LINK

/* The values, one of which will be returned by CPSWWrRGMIIStatusGet */
#define CPSW_RGMII2_DUPLEX_FULL                CPSW_WR_RGMII_CTL_RGMII2_FULLDUPLEX 
#define CPSW_RGMII2_DUPLEX_HALF                (0x00u)
#define CPSW_RGMII2_SPEED_10M                  (0x00u << CPSW_WR_RGMII_CTL_RGMII2_SPEED_SHIFT)
#define CPSW_RGMII2_SPEED_100M                 (0x01u << CPSW_WR_RGMII_CTL_RGMII2_SPEED_SHIFT)
#define CPSW_RGMII2_SPEED_1000M                (0x02u << CPSW_WR_RGMII_CTL_RGMII2_SPEED_SHIFT)
#define CPSW_RGMII2_LINK_UP                    CPSW_WR_RGMII_CTL_RGMII2_LINK 
#define CPSW_RGMII2_LINK_DOWN                  (0x00u)
#define CPSW_RGMII1_DUPLEX_FULL                CPSW_WR_RGMII_CTL_RGMII1_FULLDUPLEX 
#define CPSW_RGMII1_DUPLEX_HALF                (0x00u)
#define CPSW_RGMII1_SPEED_10M                  (0x00u << CPSW_WR_RGMII_CTL_RGMII1_SPEED_SHIFT)
#define CPSW_RGMII1_SPEED_100M                 (0x01u << CPSW_WR_RGMII_CTL_RGMII1_SPEED_SHIFT)
#define CPSW_RGMII1_SPEED_1000M                (0x02u << CPSW_WR_RGMII_CTL_RGMII1_SPEED_SHIFT)
#define CPSW_RGMII1_LINK_UP                    CPSW_WR_RGMII_CTL_RGMII1_LINK
#define CPSW_RGMII1_LINK_DOWN                  (0x00u)

/*
** Macros which can be passed as 'pacFlag' to the API CPSWWrIntPacingEnable 
** CPSWWrIntPacingDisable
*/
#define CPSW_INT_PACING_C0_RX_PULSE            (0x01 << CPSW_WR_INT_CONTROL_INT_PACE_EN_SHIFT) 
#define CPSW_INT_PACING_C0_TX_PULSE            (0x02 << CPSW_WR_INT_CONTROL_INT_PACE_EN_SHIFT)
#define CPSW_INT_PACING_C1_RX_PULSE            (0x04 << CPSW_WR_INT_CONTROL_INT_PACE_EN_SHIFT)
#define CPSW_INT_PACING_C1_TX_PULSE            (0x08 << CPSW_WR_INT_CONTROL_INT_PACE_EN_SHIFT)
#define CPSW_INT_PACING_C2_RX_PULSE            (0x10 << CPSW_WR_INT_CONTROL_INT_PACE_EN_SHIFT)
#define CPSW_INT_PACING_C2_TX_PULSE            (0x20 << CPSW_WR_INT_CONTROL_INT_PACE_EN_SHIFT)

/*
** Macros which can be passed as 'portState' to CPSWALEPortStateSet
*/
#define CPSW_ALE_PORT_STATE_FWD                (0x03u)
#define CPSW_ALE_PORT_STATE_LEARN              (0x02u)
#define CPSW_ALE_PORT_STATE_BLOCKED            (0x01u)
#define CPSW_ALE_PORT_STATE_DISABLED           (0x00u)
 
/*
** Macros which can be passed as 'eoiFlag' to CPSWCPDMAEndOfIntVectorWrite
*/
#define CPSW_EOI_TX_PULSE                      (0x02u)
#define CPSW_EOI_RX_PULSE                      (0x01u)
#define CPSW_EOI_RX_THRESH_PULSE               (0x00u)
#define CPSW_EOI_MISC_PULSE                    (0x03u)

/*
** Macro which can be passed as 'statFlag' to CPSWCPDMAStatusGet
** The same value can be used to compare against the idle status
*/
#define CPDMA_STAT_IDLE                        (CPSW_CPDMA_DMASTATUS_IDLE)

/*
** Macro which can be passed as 'statFlag' to CPSWCPDMAStatusGet
*/
#define CPDMA_STAT_TX_HOST_ERR_CODE            (CPSW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE)

/* The return values for the above 'statFlag' */
#define CPDMA_STAT_TX_NO_ERR                   (0x00u << CPSW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE_SHIFT) 
#define CPDMA_STAT_TX_SOP_ERR                  (0x01u << CPSW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_TX_OWN_ERR                  (0x02u << CPSW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_TX_ZERO_DESC                (0x03u << CPSW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_TX_ZERO_BUF_PTR             (0x04u << CPSW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_TX_ZERO_BUF_LEN             (0x05u << CPSW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_TX_PKT_LEN_ERR              (0x06u << CPSW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE_SHIFT)

/*
** Macro which can be passed as 'statFlag' to CPSWCPDMAStatusGet
*/
#define CPDMA_STAT_RX_HOST_ERR_CODE            (CPSW_CPDMA_DMASTATUS_RX_HOST_ERR_CODE)

/* The return values for the above 'statFlag' */
#define CPDMA_STAT_RX_NO_ERR                   (0x00u << CPSW_CPDMA_DMASTATUS_RX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_RX_OWN_NOT_SET              (0x02u << CPSW_CPDMA_DMASTATUS_RX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_RX_ZERO_BUF_PTR             (0x04u << CPSW_CPDMA_DMASTATUS_RX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_RX_ZERO_BUF_LEN             (0x05u << CPSW_CPDMA_DMASTATUS_RX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_RX_SOP_BUF_LEN_ERR          (0x06u << CPSW_CPDMA_DMASTATUS_RX_HOST_ERR_CODE_SHIFT)

/*
** Macros which can be passed as 'statFlag' to CPSWCPDMAStatusGet
*/
#define CPDMA_STAT_TX_HOST_ERR_CHAN            (CPSW_CPDMA_DMASTATUS_TX_ERR_CH | 0x10u)
#define CPDMA_STAT_RX_HOST_ERR_CHAN            (CPSW_CPDMA_DMASTATUS_RX_ERR_CH | 0x08u)

/*
** Macro which can be passed as 'cfg' to the API CPSWCPDMAConfig
** The values for individual fields are also listed below.
*/
#define CPDMA_CFG(tx_rlim, rx_cef, cmd_idle, rx_offlen_blk, rx_own, tx_ptype) \
             (tx_rlim | rx_cef | cmd_idle | rx_offlen_blk | rx_own | tx_ptype)
/* Values for 'tx_rlim' */
#define CPDMA_CFG_TX_RATE_LIM_CH_7             (0x80u << CPSW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)
#define CPDMA_CFG_TX_RATE_LIM_CH_7_TO_6        (0xC0u << CPSW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)
#define CPDMA_CFG_TX_RATE_LIM_CH_7_TO_5        (0xE0u << CPSW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)
#define CPDMA_CFG_TX_RATE_LIM_CH_7_TO_4        (0xF0u << CPSW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)
#define CPDMA_CFG_TX_RATE_LIM_CH_7_TO_3        (0xF8u << CPSW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)
#define CPDMA_CFG_TX_RATE_LIM_CH_7_TO_2        (0xFCu << CPSW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)
#define CPDMA_CFG_TX_RATE_LIM_CH_7_TO_1        (0xFEu << CPSW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)
#define CPDMA_CFG_TX_RATE_LIM_CH_7_TO_0        (0xFFu << CPSW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)

/* Values for 'rx_cef' */
#define CPDMA_CFG_COPY_ERR_FRAMES              (CPSW_CPDMA_DMACONTROL_RX_CEF)
#define CPDMA_CFG_NO_COPY_ERR_FRAMES           (0x00u)

/* Values for 'cmd_idle' */
#define CPDMA_CFG_IDLE_COMMAND                 (CPSW_CPDMA_DMACONTROL_CMD_IDLE)
#define CPDMA_CFG_IDLE_COMMAND_NONE            (0x00u)

/* Values for 'rx_offlen_blk' */
#define CPDMA_CFG_BLOCK_RX_OFF_LEN_WRITE       (CPSW_CPDMA_DMACONTROL_RX_OFFLEN_BLOCK)
#define CPDMA_CFG_NOT_BLOCK_RX_OFF_LEN_WRITE   (0x00u)

/* Values for 'rx_own' */
#define CPDMA_CFG_RX_OWN_1                     (CPSW_CPDMA_DMACONTROL_RX_OWNERSHIP)
#define CPDMA_CFG_RX_OWN_0                     (0x00u)

/* Values for 'tx_ptype' */
#define CPDMA_CFG_TX_PRI_ROUND_ROBIN           (CPSW_CPDMA_DMACONTROL_TX_PTYPE)
#define CPDMA_CFG_TX_PRI_FIXED                 (0x00u)

/*
** Macros which can be passed as 'intType' to CPSWCPDMARxIntStatRawGet
** and CPSWCPDMARxIntStatMaskedGet
*/
#define CPDMA_RX_INT_THRESH_PEND               (0x08u)
#define CPDMA_RX_INT_PULSE_PEND                (0x00u)

#define CPSW_MAX_NUM_ALE_ENTRY                 (1024)
#define CPSW_SIZE_CPPI_RAM                     (8192)

/*
** Structure to save CPSW context
*/
typedef struct cpswContext {
    unsigned int aleBase;
    unsigned int ssBase;
    unsigned int port1Base;
    unsigned int port2Base;
    unsigned int cpdmaBase;
    unsigned int cppiRamBase;
    unsigned int wrBase;
    unsigned int sl1Base;
    unsigned int sl2Base;
    unsigned int aleCtrl;
    unsigned int alePortCtl[3];
    unsigned int aleEntry[CPSW_MAX_NUM_ALE_ENTRY * 3];
    unsigned int ssStatPortEn;
    unsigned int port1SaHi;
    unsigned int port1SaLo;
    unsigned int port2SaHi;
    unsigned int port2SaLo;
    unsigned int port1TxInCtl;
    unsigned int port1Vlan;
    unsigned int port2TxInCtl;
    unsigned int port2Vlan;
    unsigned int cpdmaRxFB;
    unsigned int cpdmaTxCtl;
    unsigned int cpdmaRxCtl;
    unsigned int cpdmaRxHdp;
    unsigned int txIntMaskSet;
    unsigned int rxIntMaskSet;
    unsigned int wrCoreIntTxPulse;
    unsigned int wrCoreIntRxPulse;
    unsigned int sl1MacCtl;
    unsigned int sl2MacCtl;
    unsigned int cppiRam[CPSW_SIZE_CPPI_RAM];
} CPSWCONTEXT;

/*****************************************************************************/
/*
** Prototypes for the APIs
*/
extern void CPSWSSReset(unsigned int baseAddr);
extern void CPSWSlControlExtEnable(unsigned int baseAddr);
extern void CPSWSlGigModeForceEnable(unsigned int baseAddr);
extern void CPSWSlGigModeForceDisable(unsigned int baseAddr);
extern void CPSWSlTransferModeSet(unsigned int baseAddr, unsigned int mode);
extern unsigned int CPSWSlMACStatusGet(unsigned int baseAddr, unsigned int statFlag);
extern void CPSWSlReset(unsigned int baseAddr);
extern void CPSWSlRxMaxLenSet(unsigned int baseAddr, unsigned int rxMaxLen);
extern void CPSWSlGMIIEnable(unsigned int baseAddr);
extern void CPSWSlRGMIIEnable(unsigned int baseAddr);
extern void CPSWWrReset(unsigned int baseAddr);
extern void CPSWWrControlRegReset(unsigned int baseAddr);
extern void CPSWWrCoreIntEnable(unsigned int baseAddr, unsigned int core,
                         unsigned int channel, unsigned int intFlag);
extern void CPSWWrCoreIntDisable(unsigned int baseAddr, unsigned int core,
                          unsigned int channel, unsigned int intFlag);
extern unsigned int CPSWWrCoreIntStatusGet(unsigned int baseAddr, unsigned int core,
                                    unsigned int channel, unsigned int intFlag);
extern unsigned int CPSWWrRGMIIStatusGet(unsigned int baseAddr, unsigned int statFlag);
extern void CPSWALEInit(unsigned int baseAddr);
extern void CPSWALEPortStateSet(unsigned int baseAddr, unsigned int portNum,
                         unsigned int portState);
extern void CPSWALETableEntrySet(unsigned int baseAddr, unsigned int aleTblIdx,
                          unsigned int *aleEntryPtr);
extern void CPSWALETableEntryGet(unsigned int baseAddr, unsigned int aleTblIdx,
                          unsigned int *aleEntryPtr);
extern unsigned int CPSWALEPrescaleGet(unsigned int baseAddr);
extern void CPSWALEPrescaleSet(unsigned int baseAddr, unsigned int psVal);
extern void CPSWALEBypassEnable(unsigned int baseAddr);
extern void CPSWALEBypassDisable(unsigned int baseAddr);
extern void CPSWRxFlowControlEnable(unsigned int baseAddr, unsigned int portNum);
extern void CPSWRxFlowControlDisable(unsigned int baseAddr, unsigned int portNum);
extern void CPSWSoftwareIdleEnable(unsigned int baseAddr);
extern void CPSWSoftwareIdleDisable(unsigned int baseAddr, unsigned int portNum);
extern void CPSWStatisticsEnable(unsigned int baseAddr);
extern void CPSWVLANAwareEnable(unsigned int baseAddr);
extern void CPSWVLANAwareDisable(unsigned int baseAddr);
extern void CPSWPortSrcAddrSet(unsigned int baseAddr, unsigned char *ethAddr);
extern unsigned int CPSWStatisticsGet(unsigned int baseAddr, unsigned int statReg);
extern void CPSWCPDMAReset(unsigned int baseAddr);
extern void CPSWCPDMACmdIdleEnable(unsigned int baseAddr);
extern void CPSWCPDMACmdIdleDisable(unsigned int baseAddr);
extern void CPSWCPDMATxIntEnable(unsigned int baseAddr, unsigned int channel);
extern void CPSWCPDMARxIntEnable(unsigned int baseAddr, unsigned int channel);
extern void CPSWCPDMATxIntDisable(unsigned int baseAddr, unsigned int channel);
extern void CPSWCPDMARxIntDisable(unsigned int baseAddr, unsigned int channel);
extern void CPSWCPDMATxEnable(unsigned int baseAddr);
extern void CPSWCPDMARxEnable(unsigned int baseAddr);
extern void CPSWCPDMATxHdrDescPtrWrite(unsigned int baseAddr, unsigned int descHdr,
                                unsigned int channel);
extern void CPSWCPDMARxHdrDescPtrWrite(unsigned int baseAddr, unsigned int descHdr,
                                unsigned int channel);
extern void CPSWCPDMAEndOfIntVectorWrite(unsigned int baseAddr, unsigned int eoiFlag);
extern void CPSWCPDMATxCPWrite(unsigned int baseAddr, unsigned int channel,
                        unsigned int comPtr);
extern void CPSWCPDMARxCPWrite(unsigned int baseAddr, unsigned int channel,
                        unsigned int comPtr);
extern void CPSWCPDMANumFreeBufSet(unsigned int baseAddr, unsigned int channel,
                            unsigned int nBuf);
extern unsigned int CPSWCPDMAStatusGet(unsigned int baseAddr, unsigned int statFlag);
extern void CPSWCPDMAConfig(unsigned int baseAddr, unsigned int cfg);
extern void CPSWCPDMARxBufOffsetSet(unsigned int baseAddr, unsigned int bufOff);
extern unsigned int CPSWCPDMATxIntStatRawGet(unsigned int baseAddr,
                                      unsigned int chanMask);
extern unsigned int CPSWCPDMATxIntStatMaskedGet(unsigned int baseAddr,
                                         unsigned int chanMask);
extern unsigned int CPSWCPDMARxIntStatRawGet(unsigned int baseAddr,
                                      unsigned int chanMask,
                                      unsigned int intType);
extern unsigned int CPSWCPDMARxIntStatMaskedGet(unsigned int baseAddr,
                                         unsigned int channel,
                                         unsigned int intFlag);
extern void CPSWContextSave(CPSWCONTEXT *contextPtr);
extern void CPSWContextRestore(CPSWCONTEXT *contextPtr);
extern void CPSWHostPortDualMacModeSet(unsigned int baseAddr);
extern void CPSWALEVLANAwareSet(unsigned int baseAddr);
extern void CPSWALEVLANAwareClear(unsigned int baseAddr);
extern void CPSWPortVLANConfig(unsigned int baseAddr, unsigned int vlanId,
                               unsigned int cfiBit, unsigned int vlanPri);
extern void CPSWALERateLimitTXMode(unsigned int baseAddr);
extern void CPSWALERateLimitRXMode(unsigned int baseAddr);
extern void CPSWALERateLimitEnable(unsigned int baseAddr);
extern void CPSWALERateLimitDisable(unsigned int baseAddr);
extern void CPSWALEAUTHModeSet(unsigned int baseAddr);
extern void CPSWALEAUTHModeClear(unsigned int baseAddr);
extern void CPSWALEUnknownUntaggedEgressSet(unsigned int baseAddr,
                                            unsigned int ueVal);
extern void CPSWALEUnknownRegFloodMaskSet(unsigned int baseAddr,
                                          unsigned int rfmVal);
extern void CPSWALEUnknownUnRegFloodMaskSet(unsigned int baseAddr,
                                            unsigned int ufmVal);
extern void CPSWALEUnknownMemberListSet(unsigned int baseAddr,
                                        unsigned int mlVal);
extern void CPSWALEBroadcastRateLimitSet(unsigned int baseAddr,
                                         unsigned int portNum,
                                         unsigned int bplVal);
extern void CPSWALEMulticastRateLimitSet(unsigned int baseAddr,
                                         unsigned int portNum,
                                         unsigned int mplVal);
extern void CPSWALEVIDIngressCheckSet(unsigned int baseAddr,
                                      unsigned int portNum);
extern void CPSWALEAgeOut(unsigned int baseAddr);
#ifdef __cplusplus
}
#endif

#endif /* __CPSW_H__ */
