/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <string.h> 
#include "fsl_enet_hal.h"
#if FSL_FEATURE_SOC_ENET_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/
 
/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetTxInterPacketGap
 * Description: Sets the transmit inter-packet gap.
 *END*********************************************************************/
static void ENET_HAL_SetTxInterPacketGap(ENET_Type * base, uint32_t ipgValue);

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetTxFifo
 * Description: Configure ENET transmit FIFO.  
 *END*********************************************************************/
static void ENET_HAL_SetTxFifo(ENET_Type * base, enet_config_tx_fifo_t *thresholdCfg);

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetRxFifo
 * Description: Configure ENET receive FIFO.  
 *END*********************************************************************/
static void ENET_HAL_SetRxFifo(ENET_Type * base,enet_config_rx_fifo_t *thresholdCfg );
 
 /*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_InitRxBuffDescriptors
 * Description: Initialize an ENET receive buffer descriptor. The buffer is
 * is the data buffer address, this address must always be evenly divisible by 16.
 *END*********************************************************************/
static void ENET_HAL_InitRxBuffDescriptors(volatile enet_bd_struct_t *rxBds, \
  uint8_t *rxBuff, uint32_t rxbdNum, uint32_t rxBuffSizeAlign);

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_InitTxBuffDescriptors
 * Description: Initialize an ENET transmit buffer descriptor.
 *END*********************************************************************/

static void ENET_HAL_InitTxBuffDescriptors(volatile enet_bd_struct_t *txBds, \
  uint8_t *txBuff, uint32_t txbdNum, uint32_t txBuffSizeAlign);

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetMacAddr
 * Description: Sets the six-byte Mac address of the ENET device.
 * 
 *END*********************************************************************/
static void ENET_HAL_SetMacAddr(ENET_Type * base, uint8_t *hwAddr);

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_Init
 * Return Value: The execution status.
 * Description: Init ENET to reset status.
 * 
 *END*********************************************************************/
enet_status_t ENET_HAL_Init(ENET_Type * base)
{
    uint32_t timeOut = 0;

    /* Reset ENET*/
    ENET_BWR_ECR_RESET(base, 1);
    /* Check for reset complete*/
    while(ENET_BRD_ECR_RESET(base) && (timeOut < kEnetMaxTimeout))
    {
        timeOut ++;
    }
    /* Check for Timeout*/
    if(timeOut == kEnetMaxTimeout)
    {
        return kStatus_ENET_InitTimeout;
    }

     /* Disable ENET interrupt and Clear interrupt events*/
    ENET_WR_EIMR(base, 0);
    ENET_HAL_ClearIntStatusFlag(base, kEnetAllInterrupt);

    /* Clear multicast group and individual hash register*/
    ENET_WR_GALR(base, 0);
    ENET_WR_GAUR(base, 0);
    ENET_WR_IALR(base, 0);
    ENET_WR_IAUR(base, 0);

    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetSMI
 * Description: Sets the SMI(MDC/MDIO) between Mac and PHY. The miiSpeed is 
 * a value that controls the frequency of the MDC, relative to the internal module clock(InterClockSrc).
 * A value of zero in this parameter turns the MDC off and leaves it in the low voltage state.
 * Any non-zero value results in the MDC frequency MDC = InterClockSrc/((miiSpeed + 1)*2).
 * So miiSpeed = InterClockSrc/(2*MDC) - 1.
 * The Maximum MDC clock is 2.5MHZ(maximum). The recommended action is to round up and plus one to simplify:
 *  miiSpeed = InterClockSrc/(2*2.5MHZ).
 */
static void ENET_HAL_SetSMI(ENET_Type * base, uint32_t miiSpeed, 
                              uint32_t clkCycle, bool isPreambleDisabled)
{
    assert(clkCycle <= kEnetMaxMdioHoldCycle);
    ENET_BWR_MSCR_MII_SPEED(base, miiSpeed);          /* MII speed set*/
    ENET_BWR_MSCR_DIS_PRE(base, isPreambleDisabled);  /* Preamble is disabled*/
    ENET_BWR_MSCR_HOLDTIME(base, clkCycle);  /* hold on clock cycles for MDIO output*/
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetMac
 * Description: Configure Mac controller of the ENET device.
 * 
 *END*********************************************************************/
static void ENET_HAL_SetMac(ENET_Type * base, const enet_mac_config_t *macCfgPtr, uint32_t sysClk)
{
    uint32_t ecrReg, rcrReg, tcrReg;
    uint32_t clkCycle = 0, macCtlConfigure = macCfgPtr->macCtlConfigure;
    assert(macCfgPtr);
    assert(sysClk);
    assert(macCfgPtr->pauseDuration <= ENET_OPD_PAUSE_DUR_MASK);
    assert(macCfgPtr->macSpecialCfg->rxMaxFrameLen <= macCfgPtr->macSpecialCfg->rxTruncLen);
    assert((macCfgPtr->macSpecialCfg->rxMaxFrameLen) <= (ENET_RCR_MAX_FL_MASK >> ENET_RCR_MAX_FL_SHIFT));
    assert(macCfgPtr->macSpecialCfg->rxTruncLen <= ENET_FTRL_TRUNC_FL_MASK);
	
    ecrReg = ENET_RD_ECR(base);
    /* Configure operate mode, stop control of MAC controller*/
    ecrReg &= (~(ENET_ECR_SLEEP_MASK | ENET_ECR_MAGICEN_MASK | ENET_ECR_STOPEN_MASK | ENET_ECR_DBGEN_MASK));
    ecrReg |= (ENET_ECR_SLEEP(macCfgPtr->macMode) | ENET_ECR_MAGICEN(macCfgPtr->macMode) | 
               ENET_ECR_STOPEN(!!(macCtlConfigure & kEnetStopModeEnable)) | 
                 ENET_ECR_DBGEN(!!(macCtlConfigure & kEnetDebugModeEnable)));  
    ENET_WR_ECR(base, ecrReg);
    /* Configure MAC receive controller*/
    /* Enables/disables the payload length check. */
    rcrReg = ENET_RD_RCR(base);
    rcrReg &= (~ENET_RCR_NLC_MASK);
    rcrReg |= ENET_RCR_NLC(!!(macCtlConfigure & kEnetPayloadlenCheckEnable));
    /* Enables/disables the flow control */
    rcrReg &= (~ENET_RCR_CFEN_MASK);
    rcrReg |= ENET_RCR_CFEN(!!(macCtlConfigure & kEnetRxFlowControlEnable));
    rcrReg &= (~ENET_RCR_FCE_MASK);
    rcrReg |= ENET_RCR_FCE(!!(macCtlConfigure & kEnetRxFlowControlEnable));
    /* Enables/disables forward the CRC field of the received frame. */
    rcrReg &= (~ENET_RCR_CRCFWD_MASK);
    rcrReg |= ENET_RCR_CRCFWD(!(macCtlConfigure & kEnetRxCrcFwdEnable));
    /* Enables/disables pause frames forwarding. */
    rcrReg &= (~ENET_RCR_PAUFWD_MASK);
    rcrReg |= ENET_RCR_PAUFWD(!!(macCtlConfigure & kEnetRxPauseFwdEnable));
    /* Enables/disables frame padding remove on receive. */
    rcrReg &= (~ENET_RCR_PADEN_MASK);
    rcrReg |= ENET_RCR_PADEN(!!(macCtlConfigure & kEnetRxPadRemoveEnable));
    /* Enables/disables the broadcast frame reject. */
    rcrReg &= (~ENET_RCR_BC_REJ_MASK);
    rcrReg |= ENET_RCR_BC_REJ(!!(macCtlConfigure & kEnetRxBcRejectEnable));
    /* Enables/disables the ENET promiscuous mode. */
    rcrReg &= (~ENET_RCR_PROM_MASK);
    rcrReg |= ENET_RCR_PROM(!!(macCtlConfigure & kEnetRxPromiscuousEnable));
    ENET_WR_RCR(base, rcrReg);
    /* Check the rmiiCfgMode if NULL use Default value*/
    if(!macCfgPtr->rmiiCfgPtr)
    {
        enet_config_rmii_t rmiiCfg;
        rmiiCfg.duplex = kEnetCfgFullDuplex;
        rmiiCfg.speed = kEnetCfgSpeed100M;
        rmiiCfg.mode = kEnetCfgRmii;
        rmiiCfg.isLoopEnabled = false;
        rmiiCfg.isRxOnTxDisabled = false;
        ENET_HAL_SetRMIIMode(base, &rmiiCfg);
    }
    else
    {
        ENET_HAL_SetRMIIMode(base, macCfgPtr->rmiiCfgPtr);
    }

    /* Configure MAC transmit controller*/
    if(macCtlConfigure & kEnetRxFlowControlEnable)
    {
        /* Sets the pause duration for the pause frame. */
        ENET_BWR_OPD_PAUSE_DUR(base, macCfgPtr->pauseDuration);		
    }
    tcrReg = ENET_RD_TCR(base);
    /* Enables/disables the forwarding frame from an application with the CRC for the transmitted frames. */
    tcrReg &= (~ENET_TCR_CRCFWD_MASK);
    tcrReg |= ENET_TCR_CRCFWD(!!(macCtlConfigure & kEnetTxCrcFwdEnable));
    /* Enables or disables Mac address modification on transmit. */
    tcrReg &= (~(ENET_TCR_ADDSEL_MASK | ENET_TCR_ADDINS_MASK));
    tcrReg |= (ENET_TCR_ADDSEL(0) | ENET_TCR_ADDINS(!!(macCtlConfigure & kEnetMacAddrInsert)));
    ENET_WR_TCR(base, tcrReg);
    /* Configure Accelerator control*/
    if(macCtlConfigure & kEnetTxAccelEnable)
    {
        ENET_WR_TACC(base, macCfgPtr->txAccelerCfg);
    }
    if(macCtlConfigure & kEnetRxAccelEnable)
    {
        ENET_WR_RACC(base, macCfgPtr->rxAccelerCfg);
    }

    /* Check if Special configure for MAC is required and default value is normally enough*/
    if(macCfgPtr->macSpecialCfg != NULL)
    {        
        /* Special configure for MAC to instead of default configure*/
	/* Sets the maximum receive frame length. */
	ENET_BWR_RCR_MAX_FL(base, macCfgPtr->macSpecialCfg->rxMaxFrameLen);
	/* Sets the receive frame truncation length. */
	ENET_BWR_FTRL_TRUNC_FL(base, macCfgPtr->macSpecialCfg->rxTruncLen);
        ENET_HAL_SetTxInterPacketGap(base, macCfgPtr->macSpecialCfg->txInterPacketGap);
    }

    /* Set hold time for MDIO output and set the MDC Clock*/
    clkCycle = (10 + kEnetNsecOneSec / sysClk - 1) / (kEnetNsecOneSec / sysClk) - 1;
    ENET_HAL_SetSMI(base, (sysClk/(2 * kEnetMdcFreq)), clkCycle, macCtlConfigure & kEnetSMIPreambleDisable);

    /* MIB control*/
    /* Sets the enable/disable of the MIB block.  */
    ENET_BWR_MIBC_MIB_DIS(base, !(macCtlConfigure & kEnetMacMibEnable));

    /* Configure enhanced MAC*/
    /* Enables or disables the enhanced functionality of the MAC(1588 feature). */
    ENET_BWR_ECR_EN1588(base, !!(macCtlConfigure & kEnetMacEnhancedEnable));

    /* Configure the Mac address*/
    ENET_HAL_SetMacAddr(base, macCfgPtr->macAddr);
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetTxBuffDescriptors
 * Description: Configure transmit buffer descriptors of the ENET device.
 * 
 *END*********************************************************************/
static void ENET_HAL_SetTxBuffDescriptors(ENET_Type * base, volatile enet_bd_struct_t * txBds, uint8_t * txBuffer, uint32_t txBdNumber, uint32_t txBuffSizeAlign)
{
    assert(txBuffSizeAlign >= kEnetMinBuffSize);
    /* Initialize transmit buffer descriptor rings start address*/
    ENET_WR_TDSR(base,(uint32_t)txBds);
    /* Initialize transmit buffer descriptors*/
    ENET_HAL_InitTxBuffDescriptors(txBds, txBuffer, txBdNumber, txBuffSizeAlign);
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetRxBuffDescriptors
 * Description: Configure receive buffer descriptors of the ENET device.
 * 
 *END*********************************************************************/
static void ENET_HAL_SetRxBuffDescriptors(ENET_Type * base, volatile enet_bd_struct_t *rxBds, uint8_t *rxBuffer, uint32_t rxBdNumber, uint32_t rxBuffSizeAlign)
{
    /* max buffer size must larger than 256 to minimize bus usage*/
    assert(rxBuffSizeAlign >= kEnetMinBuffSize); 
    /* Initialize receive buffer descriptor rings start address*/
    ENET_WR_RDSR(base,(uint32_t)rxBds); 
	
    ENET_WR_MRBR(base, (rxBuffSizeAlign & ENET_MRBR_R_BUF_SIZE_MASK));

    /* Initialize receive buffer descriptors*/
    ENET_HAL_InitRxBuffDescriptors(rxBds, rxBuffer, rxBdNumber, rxBuffSizeAlign);
}

#if 0
/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_Set1588TimerChnCmp
 * Description: Configure 1588 timer channel compare feature and enable the 
 * 1588 timer channel interupt. This is instead of TS_TIMER for the old silicon
 * which has no TS_TIMER interrup.
 * 
 *END*********************************************************************/
static void ENET_HAL_Set1588TimerChnCmp(ENET_Type * base, enet_timer_channel_t channel, uint32_t cmpValOld, uint32_t cmpValNew)
{
    assert(kEnetChannelToggleCompare <= (ENET_TCSR_TMODE_MASK >> ENET_TCSR_TMODE_SHIFT));
    /* Sets the compare value for the 1588 timer channel */
    ENET_WR_TCCR(base, channel, cmpValOld);
    /* Disable timer mode before set*/
    ENET_BWR_TCSR_TMODE(base, channel, 0);
    /* Set timer mode*/
    ENET_BWR_TCSR_TMODE(base, channel, kEnetChannelToggleCompare);
    /* Sets the 1588 time channel interrupt. */
    ENET_BWR_TCSR_TIE(base, channel, 1U);
    ENET_WR_TCCR(base, channel, cmpValNew);
}
#endif

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_Set1588Timer
 * Description: Initialize Ethernet ptp timer.
 *
 *END*********************************************************************/
static void ENET_HAL_Set1588Timer(ENET_Type * base, enet_config_ptp_timer_t *ptpCfgPtr)
{
    assert(ptpCfgPtr);

    ENET_BWR_ATINC_INC(base, ptpCfgPtr->clockIncease);   /* Set increase value for ptp timer*/
    ENET_WR_ATPER(base, ptpCfgPtr->period);         /* Set wrap time for ptp timer*/
    /* set periodical event and the event signal output assertion*/
    ENET_BWR_ATCR_PEREN(base, 1);
    ENET_BWR_ATCR_PINPER(base, 1);
    /* Set ptp timer slave/master mode*/
    ENET_BWR_ATCR_SLAVE(base, ptpCfgPtr->isSlaveEnabled); 
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_Start1588Timer
 * Description: Configure 1588 timer and run 1588 timer.
 * 
 *END*********************************************************************/
void ENET_HAL_Start1588Timer(ENET_Type * base, enet_config_ptp_timer_t * ptpCfgPtr)
{
    /* Restart 1588 timer*/
    ENET_BWR_ATCR_RESTART(base, 1);
   /* Init 1588 timer*/
    ENET_HAL_Set1588Timer(base, ptpCfgPtr);
   /* Active 1588 timer*/
    ENET_BWR_ATCR_EN(base, 1);
#if FSL_FEATURE_ENET_PTP_TIMER_CHANNEL_INTERRUPT_ERRATA_2579
    /* Initialize timer channel for timestamp interrupt for old silicon*/
    uint32_t compareValue = ptpCfgPtr->period - ptpCfgPtr->clockIncease;
    ENET_HAL_Set1588TimerChnCmp(base, ptpCfgPtr->channel, compareValue, compareValue);
#endif
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_Stop1588Timer
 * Description: Get the ENET hardware status.
 *
 *END*********************************************************************/
void ENET_HAL_Stop1588Timer(ENET_Type * base)
{
    ENET_BWR_ATCR_EN(base, 0);
    ENET_BWR_ATCR_RESTART(base,1);  
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetFifo
 * Description: Configure transmit and receive FIFO of the ENET device.
 * 
 *END*********************************************************************/
static void ENET_HAL_SetFifo(ENET_Type * base, const enet_mac_config_t *macCfgPtr)
{
    enet_config_tx_fifo_t txFifoCfg = {0};
    enet_config_rx_fifo_t rxFifoCfg = {0};

    assert(macCfgPtr);

    /* Check if macCfg FIFO configuration pointer is NULL, if NULL use default value is enough*/
    if(!macCfgPtr->txFifoPtr)
    {
        /* Initialize the transmit FIFO with default value*/
        txFifoCfg.txAlmostEmpty = kEnetMinFifoAlmostEmpty;
        txFifoCfg.txAlmostFull = kEnetDefaultTxFifoAlmostFull;
    }
    else
    {
        /* Initialize the transmit FIFO with new configuration*/
        txFifoCfg.isStoreForwardEnabled = macCfgPtr->txFifoPtr->isStoreForwardEnabled;
        txFifoCfg.txFifoWrite = macCfgPtr->txFifoPtr->txFifoWrite;
        txFifoCfg.txEmpty = macCfgPtr->txFifoPtr->txEmpty;
        txFifoCfg.txAlmostEmpty = macCfgPtr->txFifoPtr->txAlmostEmpty;
        txFifoCfg.txAlmostFull = macCfgPtr->txFifoPtr->txAlmostFull;
    }

    if(((macCfgPtr->macCtlConfigure & kEnetTxAccelEnable)
         && (macCfgPtr->txAccelerCfg &(kEnetTxAccelIpCheckEnabled | kEnetTxAccelProtoCheckEnabled)))
        || (macCfgPtr->macCtlConfigure & kEnetStoreAndFwdEnable))
    {
        txFifoCfg.isStoreForwardEnabled = 1;
    }
    ENET_HAL_SetTxFifo(base, &txFifoCfg);  

    if(!macCfgPtr->rxFifoPtr)
    {
        /* Initialize the receive FIFO with default value*/
        rxFifoCfg.rxAlmostFull = kEnetMinFifoAlmostEmpty;
        rxFifoCfg.rxAlmostEmpty = kEnetMinFifoAlmostEmpty;  
    }
    else
    {
        /* Initialize the receive FIFO with new configuration*/
        rxFifoCfg.rxFull = macCfgPtr->rxFifoPtr->rxFull;
        rxFifoCfg.rxAlmostFull = macCfgPtr->rxFifoPtr->rxAlmostFull;
        rxFifoCfg.rxEmpty = macCfgPtr->rxFifoPtr->rxEmpty;
        rxFifoCfg.rxAlmostEmpty = macCfgPtr->rxFifoPtr->rxAlmostEmpty;  
    }

    if(((macCfgPtr->macCtlConfigure & kEnetRxAccelEnable) 
          && (macCfgPtr->rxAccelerCfg & (kEnetTxAccelIpCheckEnabled | kEnetTxAccelProtoCheckEnabled)))
         || (macCfgPtr->macCtlConfigure & kEnetStoreAndFwdEnable))
    {
        rxFifoCfg.rxFull = 0;
    }
    ENET_HAL_SetRxFifo(base, &rxFifoCfg);

}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_GetMibRxStat
 * Description: Get all received statistics from MIB.
 *
 *END*********************************************************************/
static void ENET_HAL_GetMibRxStat(ENET_Type * base, enet_mib_rx_stat_t *rxStat)
{
    assert(rxStat); 
    /* Gets the receive packet count. */
    rxStat->rxPackets = ENET_BRD_RMON_R_PACKETS_COUNT(base);
    /*  Gets the receive broadcast packet count. */
    rxStat->rxBroadcastPackets = ENET_BRD_RMON_R_BC_PKT_COUNT(base);
    /* Gets the receive multicast packet count. */
    rxStat->rxMulticastPackets = ENET_BRD_RMON_R_MC_PKT_COUNT(base);
    /* Gets the receive packets less than 64-byte and good CRC. */
    rxStat->rxUnderSizeGoodPackets = ENET_BRD_RMON_R_UNDERSIZE_COUNT(base);
    /* Gets the receive packets less than 64-byte and bad CRC. */
    rxStat->rxUnderSizeBadPackets = ENET_BRD_RMON_R_FRAG_COUNT(base);
    /*  Gets the receive packets greater than MAX_FL and good CRC. */
    rxStat->rxOverSizeGoodPackets =  ENET_BRD_RMON_R_OVERSIZE_COUNT(base);
    /* Gets the receive packets greater than MAX_FL and bad CRC. */
    rxStat->rxOverSizeBadPackets = ENET_BRD_RMON_R_JAB_COUNT(base);
    /*  Gets the receive octets. */
    rxStat->rxOctets = ENET_RD_RMON_R_OCTETS(base);
    /* Gets the receive packets with 1024-byte to 2047-byte. */
    rxStat->rxByte1024to2047Packets = ENET_BRD_RMON_R_P1024TO2047_COUNT(base);
    /* Gets the receive packets with 128-byte to 255-byte. */
    rxStat->rxByte128to255Packets = ENET_BRD_RMON_R_P128TO255_COUNT(base);
    /* Gets the receive packets with 256-byte to 511-byte. */
    rxStat->rxByte256to511Packets = ENET_BRD_RMON_R_P256TO511_COUNT(base);
    /* Gets the receive packets with 64-byte. */
    rxStat->rxByte64Packets = ENET_BRD_RMON_R_P64_COUNT(base);
    /* Gets the receive packets with 65-byte to 127-byte. */
    rxStat->rxByte65to127Packets = ENET_BRD_RMON_R_P65TO127_COUNT(base);
    /* Gets the receive packets greater than 2048-byte. */
    rxStat->rxByteOver2048Packets = ENET_BRD_RMON_R_P_GTE2048_COUNT(base);
    /* Gets the receive packets with CRC/Align error. */
    rxStat->rxCrcAlignErrorPackets = ENET_BRD_RMON_R_CRC_ALIGN_COUNT(base);
    /* Gets the Frames received OK. */
    rxStat->ieeerxFrameOk = ENET_BRD_IEEE_R_FRAME_OK_COUNT(base);
    /* Gets the Frames received with CRC error. */
    rxStat->ieeerxFrameCrcErr = ENET_BRD_IEEE_R_CRC_COUNT(base);
    /* Gets the receive Frames not counted correctly. */
    rxStat->ieeerxFrameDrop = ENET_BRD_IEEE_R_DROP_COUNT(base);
    /* Gets the octet count for Frames received without Error. */
    rxStat->ieeeOctetsrxFrameOk = ENET_RD_IEEE_R_OCTETS_OK(base);
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_GetMibTxStat
 * Description: Get all transmitted statistics from MIB.
 *
 *END*********************************************************************/
static void ENET_HAL_GetMibTxStat(ENET_Type * base, enet_mib_tx_stat_t *txStat)
{
    assert(txStat);
 
    /* Gets the transmit packet count statistic. */
    txStat->txPackets = ENET_BRD_RMON_T_PACKETS_TXPKTS(base);
    /* Gets the transmit broadcast packet statistic. */
    txStat->txBroadcastPackets = ENET_BRD_RMON_T_BC_PKT_TXPKTS(base);
    /* Gets the transmit multicast packet statistic. */
    txStat->txMulticastPackets = ENET_BRD_RMON_T_MC_PKT_TXPKTS(base);
    /* Gets the transmit packets less than 64 bytes and good CRC. */
    txStat->txUnderSizeGoodPackets = ENET_BRD_RMON_T_UNDERSIZE_TXPKTS(base);
    /* Gets the transmit packets less than 64 bytes and bad CRC. */
    txStat->txUnderSizeBadPackets = ENET_BRD_RMON_T_FRAG_TXPKTS(base);
    /* Gets the transmit packets over than MAX_FL bytes and good CRC. */
    txStat->txOverSizeGoodPackets = ENET_BRD_RMON_T_OVERSIZE_TXPKTS(base);
    /* Gets the transmit packets over than MAX_FL bytes and bad CRC. */
    txStat->txOverSizeBadPackets = ENET_BRD_RMON_T_JAB_TXPKTS(base);
    /* Gets the transmit octets. */
    txStat->txOctets = ENET_RD_RMON_T_OCTETS(base);
    /* Gets the transmit packets 1024-byte to 2047-byte. */
    txStat->txByte1024to2047Packets = ENET_BRD_RMON_T_P1024TO2047_TXPKTS(base);
    /* Gets the transmit packets 128-byte to 255-byte. */
    txStat->txByte128to255Packets = ENET_BRD_RMON_T_P128TO255_TXPKTS(base);
    /* Gets the transmit packets 256-byte to 511-byte. */
    txStat->txByte256to511Packets = ENET_BRD_RMON_T_P256TO511_TXPKTS(base);
    /* Gets the transmit 64-byte packet statistic. */
    txStat->txByte64Packets = ENET_BRD_RMON_T_P64_TXPKTS(base);
    /* Gets the transmit 65-byte to 127-byte packet statistic. */
    txStat->txByte65to127Packets = ENET_BRD_RMON_T_P65TO127_TXPKTS(base);
    /* Gets the transmit packets greater than 2048-byte. */
    txStat->txByteOver2048Packets = ENET_BRD_RMON_T_P_GTE2048_TXPKTS(base);
    /* Gets the transmit packets with CRC/Align error. */
    txStat->txCrcAlignErrorPackets = ENET_BRD_RMON_T_CRC_ALIGN_TXPKTS(base);
    /* Gets the Frames transmitted OK. */
    txStat->ieeetxFrameOk = ENET_BRD_IEEE_T_FRAME_OK_COUNT(base);
    /* Gets the frames transmitted with carrier sense error. */
    txStat->ieeetxFrameCarrSenseErr= ENET_BRD_IEEE_T_CSERR_COUNT(base);
    /* Gets the frames transmitted after deferral delay. */
    txStat->ieeetxFrameDelay = ENET_BRD_IEEE_T_DEF_COUNT(base);
    /* Gets the frames transmitted with late collision. */
    txStat->ieeetxFrameLateCollison = ENET_BRD_IEEE_T_LCOL_COUNT(base);
    /* Gets the frames transmitted with multiple collision. */
    txStat->ieeetxFrameMultiCollison = ENET_BRD_IEEE_T_MCOL_COUNT(base);
    /*  Gets the Frames transmitted with single collision. */
    txStat->ieeetxFrameOneCollision = ENET_BRD_IEEE_T_1COL_COUNT(base);
    /* Gets the frames transmitted with the Tx FIFO underrun. */
    txStat->ieeetxFrameMacErr = ENET_BRD_IEEE_T_MACERR_COUNT(base);
    /* Gets the transmitted flow control Pause Frames. */
    txStat->ieeetxFramePause = ENET_BRD_IEEE_T_FDXFC_COUNT(base);
    /* Gets the octet count for frames transmitted without error. */
    txStat->ieeeOctetstxFrameOk = ENET_RD_IEEE_T_OCTETS_OK(base);
    /* Gets the frames transmitted with excessive collisions. */
    txStat->ieeetxFrmaeExcCollison = ENET_BRD_IEEE_T_EXCOL_COUNT(base);
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetMacAddr
 * Description: Sets the six-byte Mac address of the ENET device.
 * 
 *END*********************************************************************/
static void ENET_HAL_SetMacAddr(ENET_Type * base, uint8_t *hwAddr)
{
    uint32_t address;

    assert(hwAddr);	
    address = (uint32_t)(((uint32_t)hwAddr[0] << 24U)|((uint32_t)hwAddr[1] << 16U)|((uint32_t)hwAddr[2] << 8U)| (uint32_t)hwAddr[3]) ;
    ENET_WR_PALR(base,address);      /* Set low physical address */
    address = (uint32_t)(((uint32_t)hwAddr[4] << 8U)|((uint32_t)hwAddr[5]));
    ENET_BWR_PAUR_PADDR2(base, address); /* Set high physical address */
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetMulticastAddrHash
 * Description: Set multicast group address hash value to the mac register
 * To join the multicast group address.
 *END*********************************************************************/
void ENET_HAL_SetMulticastAddrHash(ENET_Type * base, uint32_t crcValue, enet_special_address_filter_t mode)
{
    switch (mode)
    {
        case kEnetSpecialAddressInit:           /* Clear group address register on ENET initialize */
            ENET_WR_GALR(base,0);
            ENET_WR_GAUR(base,0);			
            break;
        case kEnetSpecialAddressEnable:         /* Enable a multicast group address*/
            if (!((crcValue >> 31) & 1U))
            {
                ENET_SET_GALR(base,(1U << ((crcValue >> 26) & kEnetHashValMask))); 
            }
            else
            {
                ENET_SET_GAUR(base,(1U << ((crcValue >> 26) & kEnetHashValMask)));
            }
            break;
        case kEnetSpecialAddressDisable:       /* Disable a multicast group address*/
            if (!((crcValue >> 31) & 1U))
            {
                ENET_CLR_GALR(base,(1U << ((crcValue >> 26) & kEnetHashValMask)));
            }
            else
            {
                ENET_CLR_GAUR(base,(1U << ((crcValue>>26) & kEnetHashValMask))); 
            }
        break;
        default:
        break;
    }
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetTxFifo
 * Description: Configure ENET transmit FIFO.  
 *END*********************************************************************/
static void ENET_HAL_SetTxFifo(ENET_Type * base, enet_config_tx_fifo_t *thresholdCfg)
{
    assert(thresholdCfg);
    assert(thresholdCfg->txFifoWrite <= ENET_TFWR_TFWR_MASK);
    assert(thresholdCfg->txAlmostEmpty >= kEnetMinFifoAlmostEmpty);
    assert(thresholdCfg->txAlmostFull >= kEnetMinTxFifoAlmostFull);
    
    ENET_BWR_TFWR_STRFWD(base, thresholdCfg->isStoreForwardEnabled);   /* Set store and forward mode*/
    if(!thresholdCfg->isStoreForwardEnabled)
    {
        ENET_BWR_TFWR_TFWR(base, thresholdCfg->txFifoWrite);  /* Set transmit FIFO write bytes*/
    }
    ENET_BWR_TSEM_TX_SECTION_EMPTY(base,thresholdCfg->txEmpty);       /* Set transmit FIFO empty threshold*/
    ENET_BWR_TAEM_TX_ALMOST_EMPTY(base,thresholdCfg->txAlmostEmpty);  /* Set transmit FIFO almost empty threshold*/
    ENET_BWR_TAFL_TX_ALMOST_FULL(base,thresholdCfg->txAlmostFull);    /* Set transmit FIFO almost full threshold*/
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetRxFifo
 * Description: Configure ENET receive FIFO.  
 *END*********************************************************************/
static void ENET_HAL_SetRxFifo(ENET_Type * base,enet_config_rx_fifo_t *thresholdCfg )
{
    assert(thresholdCfg);
    assert(thresholdCfg->rxAlmostEmpty >= kEnetMinFifoAlmostEmpty);
    assert(thresholdCfg->rxAlmostFull >= kEnetMinFifoAlmostEmpty);
    
    if(thresholdCfg->rxFull > 0)
    {
       assert(thresholdCfg->rxFull > thresholdCfg->rxAlmostEmpty);
    }

    ENET_BWR_RSFL_RX_SECTION_FULL(base,thresholdCfg->rxFull);        /* Set receive FIFO full threshold*/
    ENET_BWR_RSEM_RX_SECTION_EMPTY(base,thresholdCfg->rxEmpty);      /* Set receive FIFO empty threshold*/
    ENET_BWR_RAEM_RX_ALMOST_EMPTY(base,thresholdCfg->rxAlmostEmpty); /* Set receive FIFO almost empty threshold*/
    ENET_BWR_RAFL_RX_ALMOST_FULL(base,thresholdCfg->rxAlmostFull);   /* Set receive FIFO almost full threshold*/    
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_InitRxBuffDescriptors
 * Description: Initialize an ENET receive buffer descriptor. The buffer is
 * is the data buffer address, this address must always be evenly divisible by 16.
 *END*********************************************************************/
static void ENET_HAL_InitRxBuffDescriptors(volatile enet_bd_struct_t *rxBds, uint8_t *rxBuff, uint32_t rxbdNum, uint32_t rxBuffSizeAlign)
{
    uint16_t count;
    volatile enet_bd_struct_t *curBd;
    assert(rxBds);
    assert(rxBuff);

    curBd = rxBds;
    for(count = 0; count < rxbdNum; count++)
    {
        curBd->buffer = (uint8_t *)BD_LONGSWAP((uint32_t)&rxBuff[count * rxBuffSizeAlign]); /* Set data buffer address */
        curBd->length = 0;    /* Initialize data length*/
    
        /*The last buffer descriptor should be set with the wrap flag*/
        if (count == rxbdNum - 1)
        {    
            curBd->control |= kEnetRxBdWrap; 
        }
        curBd->control |= kEnetRxBdEmpty;   /* Initialize bd with empty bit*/
        curBd->controlExtend1 |= kEnetRxBdIntrrupt;/* Enable receive interrupt*/
        curBd ++;
    }

}
/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_InitTxBuffDescriptors
 * Description: Initialize an ENET transmit buffer descriptor.
 *END*********************************************************************/

static void ENET_HAL_InitTxBuffDescriptors(volatile enet_bd_struct_t *txBds, uint8_t *txBuff, uint32_t txbdNum, uint32_t txBuffSizeAlign)
{
    uint32_t count;
    volatile enet_bd_struct_t *curBd;
    assert(txBds);
    assert(txBuff);

    curBd = txBds;
    for(count = 0; count < txbdNum; count++)
    {
        curBd->buffer = (uint8_t *)BD_LONGSWAP((uint32_t)&txBuff[count * txBuffSizeAlign]); /* Set data buffer address */
        curBd->length = 0; /* Set data length*/
    
        /*The last buffer descriptor should be set with the wrap flag*/
        if (count == txbdNum - 1)
        {
            curBd->control |= kEnetTxBdWrap;
        } 

        curBd ++;
    }
}


/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_ClrRxBdAfterHandled
 * Description: Update ENET receive buffer descriptors. The data is the 
 * buffer address and this address must always be evenly divisible by 16.
 *END*********************************************************************/
void ENET_HAL_ClrRxBdAfterHandled(volatile enet_bd_struct_t *rxBds, uint8_t *data, bool isbufferUpdate)
{
    assert(rxBds);

    if (isbufferUpdate)
    {
        assert(data);
        rxBds->buffer = (uint8_t *)BD_LONGSWAP((uint32_t)data);
    }
    rxBds->control &= kEnetRxBdWrap;  /* Clear status*/
    rxBds->control |= kEnetRxBdEmpty;   /* Set rx bd empty*/
    rxBds->controlExtend1 |= kEnetRxBdIntrrupt;/* Enable interrupt*/
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetTxBdBeforeSend
 * Description: Update ENET transmit buffer descriptors. The buffer is the 
 * data buffer address and this address must be evenly divided by 16.
 *END*********************************************************************/
void ENET_HAL_SetTxBdBeforeSend(volatile enet_bd_struct_t *txBds, /*uint8_t *packet,*/
               uint16_t length, bool isTxtsCfged, bool isTxCrcEnable, bool isLastOne)
{
    assert(txBds);
    
    txBds->length = BD_SHORTSWAP(length); /* Set data length*/
//    txBds->buffer = (uint8_t *)HTONL((uint32_t)packet);
    if(isLastOne)
    {
        txBds->control |= kEnetTxBdLast;
        if(isTxCrcEnable)
        {
            txBds->control |= kEnetTxBdTransmitCrc;  /* set control */   
        }
    }
    txBds->control |= kEnetTxBdReady;

    if (isTxtsCfged)
    {
         /* Set transmit and time stamp interrupt*/
        txBds->controlExtend1 |= (kEnetTxBdTxInterrupt | kEnetTxBdTimeStamp);	
    }
    else
    {
        /* Set transmit interrupt*/
        txBds->controlExtend1 |= kEnetTxBdTxInterrupt;	
    }
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetRMIIMode
 * Description: Configure (R)MII mode.
 *END*********************************************************************/
void ENET_HAL_SetRMIIMode(ENET_Type * base, enet_config_rmii_t *rmiiCfgPtr)
{
    uint32_t rcrReg;
    assert(rmiiCfgPtr);
    rcrReg = ENET_RD_RCR(base);
              
    rcrReg &= (~ENET_RCR_MII_MODE_MASK);                /* Set mii mode */
    rcrReg |= ENET_RCR_MII_MODE(1);
    rcrReg &= (~ENET_RCR_RMII_MODE_MASK);
    rcrReg |= ENET_RCR_RMII_MODE(rmiiCfgPtr->mode);     
    rcrReg &= (~ENET_RCR_RMII_10T_MASK);
    rcrReg |= ENET_RCR_RMII_10T(rmiiCfgPtr->speed);     /* Set speed mode	*/
    ENET_BWR_TCR_FDEN(base,rmiiCfgPtr->duplex);         /* Set duplex mode*/
    if ((!rmiiCfgPtr->duplex) && (rmiiCfgPtr->isRxOnTxDisabled))
    {      
        rcrReg &= (~ENET_RCR_DRT_MASK);                 /* Disable receive on transmit*/
        rcrReg |= ENET_RCR_DRT(1);
    }

    if (rmiiCfgPtr->mode == kEnetCfgMii)                /* Set internal loop only for mii mode*/
    {             
        rcrReg &= (~ENET_RCR_LOOP_MASK);
        rcrReg |= ENET_RCR_LOOP(rmiiCfgPtr->isLoopEnabled);
    }
    else
    { 
        rcrReg &= (~ENET_RCR_LOOP_MASK);               /* Clear internal loop for rmii mode*/
        rcrReg |= ENET_RCR_LOOP(0);
    }
    ENET_WR_RCR(base, rcrReg);
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetSMIWrite
 * Description: Set SMI(serial Management interface) command.
 *END*********************************************************************/
void ENET_HAL_SetSMIWrite(ENET_Type * base, uint32_t phyAddr, uint32_t phyReg, enet_mii_write_t operation, uint32_t data)
{
    uint32_t mmfrValue = 0 ;

    mmfrValue = ENET_MMFR_ST(1)| ENET_MMFR_OP(operation)| ENET_MMFR_PA(phyAddr) | ENET_MMFR_RA(phyReg)| ENET_MMFR_TA(2) | (data&0xFFFF); /* mii command*/
    ENET_WR_MMFR(base,mmfrValue);
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetSMIRead
 * Description: Set SMI(serial Management interface) command.
 *END*********************************************************************/
void ENET_HAL_SetSMIRead(ENET_Type * base, uint32_t phyAddr, uint32_t phyReg, enet_mii_read_t operation)
{
    uint32_t mmfrValue = 0 ;

    mmfrValue = ENET_MMFR_ST(1)| ENET_MMFR_OP(operation)| ENET_MMFR_PA(phyAddr) | ENET_MMFR_RA(phyReg)| ENET_MMFR_TA(2); /* mii command*/
    ENET_WR_MMFR(base,mmfrValue);
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetIntMode
 * Description: Enable or disable different Ethernet interrupts.
 *END*********************************************************************/
void ENET_HAL_SetIntMode(ENET_Type * base, enet_interrupt_request_t source, bool enable)
{
    if (enable)
    {
        ENET_SET_EIMR(base, (uint32_t)source);                     /* Enable interrupt */
    }
    else
    {
        ENET_CLR_EIMR(base, (uint32_t)source);                     /* Disable interrupt*/
    }
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_SetTxInterPacketGap
 * Description: Sets the transmit inter-packet gap.
 *END*********************************************************************/
static void ENET_HAL_SetTxInterPacketGap(ENET_Type * base, uint32_t ipgValue)
{
    assert(ipgValue <= ENET_TIPG_IPG_MASK);

    if (ipgValue >= kEnetMaxValidTxIpg)
    {

        ENET_BWR_TIPG_IPG(base, kEnetMaxValidTxIpg);  
    }
    else if (ipgValue <= kEnetMinValidTxIpg)
    {

        ENET_BWR_TIPG_IPG(base, kEnetMinValidTxIpg);          
    }
    else
    {
        ENET_BWR_TIPG_IPG(base, ipgValue);  
    }
   
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_Config
 * Description: Configure the ENET according to the user input.
 *
 *END*********************************************************************/
void ENET_HAL_Config(ENET_Type * base, const enet_mac_config_t *macCfgPtr, \
  const uint32_t sysClk, const enet_bd_config* bdConfig)
{
    assert(base);

    /* Configure MAC controller*/
    ENET_HAL_SetMac(base, macCfgPtr, sysClk);

    /* Initialize FIFO*/
    ENET_HAL_SetFifo(base, macCfgPtr);

    /* Initialize receive and transmit buffer descriptors*/    
    ENET_HAL_SetRxBuffDescriptors(base, bdConfig->rxBds, bdConfig->rxBuffer,
                    bdConfig->rxBdNumber, bdConfig->rxBuffSizeAlign);
    ENET_HAL_SetTxBuffDescriptors(base, bdConfig->txBds, bdConfig->txBuffer,
              bdConfig->txBdNumber, bdConfig->txBuffSizeAlign);
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_GetStatus
 * Description: Get the ENET hardware status.
 *
 *END*********************************************************************/
void ENET_HAL_GetStatus(ENET_Type * base, const uint32_t mask, enet_cur_status_t* curStatus)
{
    assert(base);
    
    memset((void*)curStatus, 0, sizeof(enet_cur_status_t));
    if(mask & ENET_GET_MIB_RX_STATIC_MASK)
    {
        ENET_HAL_GetMibRxStat(base, &(curStatus->rxStatic)); 
    }
    if(mask & ENET_GET_MIB_TX_STATIC_MASK)
    {
        ENET_HAL_GetMibTxStat(base, &(curStatus->txStatic));
    }
    if(mask & ENET_GET_TX_PAUSE_MASK)
    {
        if(ENET_BRD_TCR_TFC_PAUSE(base))
        {
            curStatus->statusFlags |= ENET_TX_PUASE_FLAG;
        }        
    }
    if(mask & ENET_GET_RX_PAUSE_MASK)
    {
        if(ENET_BRD_TCR_RFC_PAUSE(base))
        {
            curStatus->statusFlags |= ENET_RX_PAUSE_FLAG;
        }
    }
    if(mask & ENET_GET_SMI_CONFIG_MASK)
    {
        if(ENET_RD_MSCR(base)& 0x7E)
        {
            curStatus->statusFlags |= ENET_SMI_CONFIG_FLAG;
        }
    }
    if(mask & ENET_GET_MIB_UPDATE_MASK)
    {
        if(ENET_BRD_MIBC_MIB_IDLE(base))
        {
            curStatus->statusFlags |= ENET_MIB_UPDATE_FLAG;
        }
    }
    if(mask & ENET_GET_MAX_FRAME_LEN_MASK)
    {
        curStatus->maxFrameLen = ENET_BRD_RCR_MAX_FL(base);
    }
}
/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_GetBufDescripAttr
 * Description: Get the buffer descriptor attribute.
 *
 *END*********************************************************************/
void ENET_HAL_GetBufDescripAttr(volatile enet_bd_struct_t *curBd, const uint64_t mask, enet_bd_attr_t* resultAttr)
{
    uint16_t length;
    uint32_t timestamp; 
    assert(curBd);
    assert(mask);
    assert(resultAttr);
    memset((void*)resultAttr, 0, sizeof(enet_bd_attr_t));
    if(mask & ENET_BD_CTL_MASK)
    {
        resultAttr->bdCtl         = curBd->control;
    }
    if(mask & ENET_RX_BD_EXT_CTL_MASK)
    {
        resultAttr->rxBdExtCtl    = curBd->controlExtend0;
    }
    if(mask & ENET_RX_BD_EXT_CTL1_MASK)
    {
        resultAttr->rxBdExtCtl1   = curBd->controlExtend1;
    }
    if(mask & ENET_RX_BD_EXT_CTL2_MASK) 
    {
        resultAttr->rxBdExtCtl2   = curBd->controlExtend2;
    }
    if(mask & ENET_TX_BD_TIMESTAMP_FLAG_MASK)
    {      
        if(curBd->controlExtend1 & kEnetTxBdTimeStamp)
        {
            resultAttr->flags |= ENET_TX_BD_TIMESTAMP_FLAG;
        }
    }
    if(mask & ENET_BD_LEN_MASK)
    {
        length = curBd->length;
        resultAttr->bdLen = BD_SHORTSWAP(length);
    }
    if(mask & ENET_BD_TIMESTAMP_MASK)
    {
        timestamp = curBd->timestamp;
        resultAttr->bdTimestamp = BD_LONGSWAP(timestamp);
    }
    if(mask & ENET_RX_BD_WRAP_FLAG_MASK)
    {
        if(curBd->control & kEnetRxBdWrap)
        {
            resultAttr->flags |= ENET_RX_BD_WRAP_FLAG;
        }
    }
    if(mask & ENET_RX_BD_EMPTY_FLAG_MASK)
    {
        if(curBd->control & kEnetRxBdEmpty)
        {
            resultAttr->flags |= ENET_RX_BD_EMPTY_FLAG;
        }
    }
    if(mask & ENET_RX_BD_TRUNC_FLAG_MASK)
    {
        if(curBd->control & kEnetRxBdTrunc)
        {
            resultAttr->flags |= ENET_RX_BD_TRUNC_FLAG;
        }
    }
    if(mask & ENET_RX_BD_LAST_FLAG_MASK)
    {
        if(curBd->control & kEnetRxBdLast)
        {
            resultAttr->flags |= ENET_RX_BD_LAST_FLAG;
        }
    }
    if(mask & ENET_TX_BD_READY_FLAG_MASK)
    {
        if(curBd->control & kEnetTxBdReady)
        {
            resultAttr->flags |= ENET_TX_BD_READY_FLAG;
        }
    }
    if(mask & ENET_TX_BD_LAST_FLAG_MASK)
    {
        if(curBd->control & kEnetTxBdLast)
        {
            resultAttr->flags |= ENET_TX_BD_LAST_FLAG;
        }
    }
    if(mask & ENET_TX_BD_WRAP_FLAG_MASK)
    {
        if(curBd->control & kEnetTxBdWrap)
        {
            resultAttr->flags |= ENET_TX_BD_WRAP_FLAG;
        }
    }
    if(mask & ENET_RX_BD_OVERRUN_FLAG_MASK)
    {
        if(curBd->control & kEnetRxBdOverRun)
        {
            resultAttr->flags |= ENET_RX_BD_OVERRUN_FLAG;
        }
    }
    if(mask & ENET_RX_BD_LEN_VIOLAT_FLAG_MASK)
    {
        if(curBd->control & kEnetRxBdLengthViolation)
        {
            resultAttr->flags |= ENET_RX_BD_LEN_VIOLAT_FLAG;
        }
    }
    if(mask & ENET_RX_BD_NO_OCTET_FLAG_MASK)
    {
        if(curBd->control & kEnetRxBdNoOctet)
        {
            resultAttr->flags |= ENET_RX_BD_NO_OCTET_FLAG;
        }
    }
    if(mask & ENET_RX_BD_CRC_ERR_FLAG_MASK)
    {
        if(curBd->control & kEnetRxBdCrc)
        {
            resultAttr->flags |= ENET_RX_BD_CRC_ERR_FLAG;
        }
    }
    if(mask & ENET_RX_BD_COLLISION_FLAG_MASK)
    {
        if(curBd->control & kEnetRxBdCollision)
        {
            resultAttr->flags |= ENET_RX_BD_COLLISION_FLAG;
        }
    }
    
    /* Get extended control regions of the transmit buffer descriptor*/
    if(mask & ENET_TX_BD_TX_ERR_FLAG_MASK)
    {
        if(curBd->controlExtend0 & kEnetTxBdTxErr)
        {
            resultAttr->flags |= ENET_TX_BD_TX_ERR_FLAG;
        }
    }
    if(mask & ENET_TX_BD_EXC_COL_FLAG_MASK)
    {
        if(curBd->controlExtend0 & kEnetTxBdExcessCollisionErr)
        {
            resultAttr->flags |= ENET_TX_BD_EXC_COL_ERR_FLAG;
        }
    }
    if(mask & ENET_TX_BD_LATE_COL_FLAG_MASK)
    {
        if(curBd->controlExtend0 & kEnetTxBdLatecollisionErr)
        {
            resultAttr->flags |= ENET_TX_BD_LATE_COL_ERR_FLAG;
        }
    }
    if(mask & ENET_TX_BD_UNDERFLOW_FLAG_MASK)
    {
        if(curBd->controlExtend0 & kEnetTxBdTxUnderFlowErr)
        {
            resultAttr->flags |= ENET_TX_BD_UNDERFLOW_ERR_FLAG;
        }
    }
    if(mask & ENET_TX_BD_OVERFLOW_FLAG_MASK)
    {
        if(curBd->controlExtend0 & kEnetTxBdOverFlowErr)
        {
            resultAttr->flags |= ENET_TX_BD_OVERFLOW_FLAG;
        }
    }
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_GetBuffDescripData
 * Description: Get the buffer address of buffer descriptors.
 *END*********************************************************************/
uint8_t* ENET_HAL_GetBuffDescripData(volatile enet_bd_struct_t *curBd)
{
    uint32_t buffer;
    assert(curBd);

    buffer = (uint32_t)(curBd->buffer);
    return  (uint8_t *)BD_LONGSWAP(buffer);
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_HAL_EnAct
 * Description: Enable the dynamical action of mac.
 *
 *END*********************************************************************/
void ENET_HAL_EnDynamicalAct(ENET_Type * base, enet_en_dynamical_act_t action, bool enable)
{
    assert(base);

    switch(action)
    {
    case kEnGraceSendStop:
      {
        /* When this field is set, Mac stops transmission after a currently transmitted frame 
        is complete. */
        ENET_BWR_TCR_GTS(base, (enable ? 1U : 0U));
        break;
      }
    case kEnSendPauseFrame:
      {
        /* Start to transmit the pause frame to the remote device to indicate current 
        device is congested. This field is auto cleard after device sending a pause 
        frame complete. If this filed is cleared manually before the pause frame 
        is start complete, the frame will not be sent. */
        ENET_BWR_TCR_TFC_PAUSE(base, (enable ? 1U : 0U));
        break;
      }
    case kEnClearMibCounter:
      {
        /* Enables/disables to clear the MIB counter. This field is not self-clearing. 
        To clear the MIB counters set and then clear the field */
        ENET_BWR_MIBC_MIB_CLEAR(base, (enable ? 1U : 0U));
        break;
      }
    default:break;
    }
}

#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

