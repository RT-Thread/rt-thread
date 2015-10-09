/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
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

#include "fsl_emvsim_hal.h"

#if FSL_FEATURE_SOC_EMVSIM_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/
/*******************************************************************************
 * UART Common Configurations
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : EMVSIM_HAL_Init
 * Description   : This function initializes the module to a known state.
 *
 *END**************************************************************************/
void EMVSIM_HAL_Init(EMVSIM_Type * base)
{
    EMVSIM_WR_CLKCFG(base, 0U);
    EMVSIM_WR_DIVISOR(base, 372U);
    EMVSIM_WR_CTRL(base, 0x300U);
    EMVSIM_WR_INT_MASK(base, 0x7FFFU);
    EMVSIM_WR_RX_THD(base, 1U);
    EMVSIM_WR_TX_THD(base, 0U);
    EMVSIM_WR_PCSR(base, 0x1000000U);
    EMVSIM_WR_TX_GETU(base, 0U);
    EMVSIM_WR_CWT_VAL(base, 0xFFFFU);
    EMVSIM_WR_BWT_VAL(base, 0xFFFFFFFFU);
    EMVSIM_WR_BGT_VAL(base, 0U);
    EMVSIM_WR_GPCNT0_VAL(base, 0xFFFFU);
    EMVSIM_WR_GPCNT1_VAL(base, 0xFFFFU);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EMVSIM_HAL_GetModuleParameter
 * Description   : This function returns returns EMVSIM controller version, 
 *                 transmit and receive FIFO sizes.
 *
 *END**************************************************************************/
uint32_t EMVSIM_HAL_GetModuleParameter(EMVSIM_Type * base, emvsim_module_param_t param)
{
    uint32_t retVal = 0;
    
    switch (param)
    {
    case kEmvsimParamVersion: retVal = EMVSIM_RD_VER_ID(base);
    break;
    
    case kEmvsimParamTxFifoSize: retVal = EMVSIM_RD_PARAM_TX_FIFO_DEPTH(base);
    break;
    
    case kEmvsimParamRxFifoSize: retVal = EMVSIM_RD_PARAM_RX_FIFO_DEPTH(base);
    break;
    
    default: break;
    }
    
    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EMVSIM_HAL_SetGPCClockSelect
 * Description   : This function selects a clock source for general purpose 
 *                 counters in the module.
 *
 *END**************************************************************************/
void EMVSIM_HAL_SetGPCClockSelect(EMVSIM_Type * base, uint8_t gpcNumber, emvsim_gpc_clock_select_t gpcClockSel)
{
    switch(gpcNumber)
    {
    case 0: EMVSIM_WR_CLKCFG_GPCNT0_CLK_SEL(base, gpcClockSel);
    break;
    
    case 1: EMVSIM_WR_CLKCFG_GPCNT1_CLK_SEL(base, gpcClockSel);
    break;
    
    default: break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EMVSIM_HAL_SetControl
 * Description   : This function enables/disables different control functions of 
 *                 EMVSIM controller.
 *
 *END**************************************************************************/
void EMVSIM_HAL_SetControl(EMVSIM_Type * base, emvsim_control_t control, bool enable)
{
    switch(control)
    {
    case kEmvsimCtrlInverseConvention: EMVSIM_WR_CTRL_IC(base, enable);
    break;
    
    case kEmvsimCtrlinitialCharacterMode: EMVSIM_WR_CTRL_ICM(base, enable);
    break;
    
    case kEmvsimCtrlANACKEnable: EMVSIM_WR_CTRL_ANACK(base, enable);
    break;
    
    case kEmvsimCtrlONACKEnable: EMVSIM_WR_CTRL_ONACK(base, enable);
    break;
    
    case kEmvsimCtrlFlushRx: EMVSIM_WR_CTRL_FLSH_RX(base, enable);
    break;
    
    case kEmvsimCtrlFlushTx: EMVSIM_WR_CTRL_FLSH_TX(base, enable);
    break;
    
    case kEmvsimCtrlSwRst: EMVSIM_WR_CTRL_SW_RST(base, enable);
    break;
    
    case kEmvsimCtrlKillClocks: EMVSIM_WR_CTRL_KILL_CLOCKS(base, enable);
    break;
    
    case kEmvsimCtrlDozeEnable: EMVSIM_WR_CTRL_DOZE_EN(base, enable);
    break;
    
    case kEmvsimCtrlStopEnable: EMVSIM_WR_CTRL_STOP_EN(base, enable);
    break;
    
    case kEmvsimCtrlReceiverEnable: EMVSIM_WR_CTRL_RCV_EN(base, enable);
    break;
    
    case kEmvsimCtrlTransmitterEnable: EMVSIM_WR_CTRL_XMT_EN(base, enable);
    break;
    
    case kEmvsimCtrlRcvr11ModeEnable: EMVSIM_WR_CTRL_RCVR_11(base, enable);
    break;
    
    case kEmvsimCtrlRxDmaEnable: EMVSIM_WR_CTRL_RX_DMA_EN(base, enable);
    break;
    
    case kEmvsimCtrlTxDmaEnable: EMVSIM_WR_CTRL_TX_DMA_EN(base, enable);
    break;
    
    case kEmvsimCtrlInvertCrcOutput: EMVSIM_WR_CTRL_INV_CRC_VAL(base, enable);
    break;
    
    case kEmvsimCtrlFlipCrcOutput: EMVSIM_WR_CTRL_CRC_OUT_FLIP(base, enable);
    break;
    
    case kEmvsimCtrlFlipCrcInput: EMVSIM_WR_CTRL_CRC_IN_FLIP(base, enable);
    break;
    
    case kEmvsimCtrlCWTEnable: EMVSIM_WR_CTRL_CWT_EN(base, enable);
    break;
    
    case kEmvsimCtrlLrcEnable: EMVSIM_WR_CTRL_LRC_EN(base, enable);
    break;
    
    case kEmvsimCtrlCrcEnable: EMVSIM_WR_CTRL_CRC_EN(base, enable);
    break;
    
    case kEmvsimCtrlXmtCrcOrLrcEnable: EMVSIM_WR_CTRL_XMT_CRC_LRC(base, enable);
    break;
    
    case kEmvsimCtrlBWTEnable: EMVSIM_WR_CTRL_BWT_EN(base, enable);
    break;
        
    default: break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EMVSIM_HAL_GetControl
 * Description   : This function returns whether a control function is 
 *                 enabled/disabled in the EMVSIM controller.
 *
 *END**************************************************************************/
bool EMVSIM_HAL_GetControl(EMVSIM_Type * base, emvsim_control_t control)
{
    bool retVal = false;
    
    switch(control)
    {
    case kEmvsimCtrlInverseConvention: retVal = (bool)EMVSIM_RD_CTRL_IC(base);
    break;
    
    case kEmvsimCtrlinitialCharacterMode: retVal = (bool)EMVSIM_RD_CTRL_ICM(base);
    break;
    
    case kEmvsimCtrlANACKEnable: retVal = (bool)EMVSIM_RD_CTRL_ANACK(base);
    break;
    
    case kEmvsimCtrlONACKEnable: retVal = (bool)EMVSIM_RD_CTRL_ONACK(base);
    break;
    
    case kEmvsimCtrlFlushRx: break;
    
    case kEmvsimCtrlFlushTx: break;
    
    case kEmvsimCtrlSwRst: break;
    
    case kEmvsimCtrlKillClocks: retVal = (bool)EMVSIM_RD_CTRL_KILL_CLOCKS(base);
    break;
    
    case kEmvsimCtrlDozeEnable: retVal = (bool)EMVSIM_RD_CTRL_DOZE_EN(base);
    break;
    
    case kEmvsimCtrlStopEnable: retVal = (bool)EMVSIM_RD_CTRL_STOP_EN(base);
    break;
    
    case kEmvsimCtrlReceiverEnable: retVal = (bool)EMVSIM_RD_CTRL_RCV_EN(base);
    break;
    
    case kEmvsimCtrlTransmitterEnable: retVal = (bool)EMVSIM_RD_CTRL_XMT_EN(base);
    break;
    
    case kEmvsimCtrlRcvr11ModeEnable: retVal = (bool)EMVSIM_RD_CTRL_RCVR_11(base);
    break;
    
    case kEmvsimCtrlRxDmaEnable: retVal = (bool)EMVSIM_RD_CTRL_RX_DMA_EN(base);
    break;
    
    case kEmvsimCtrlTxDmaEnable: retVal = (bool)EMVSIM_RD_CTRL_TX_DMA_EN(base);
    break;
    
    case kEmvsimCtrlInvertCrcOutput: retVal = (bool)EMVSIM_RD_CTRL_INV_CRC_VAL(base);
    break;
    
    case kEmvsimCtrlFlipCrcOutput: retVal = (bool)EMVSIM_RD_CTRL_CRC_OUT_FLIP(base);
    break;
    
    case kEmvsimCtrlFlipCrcInput: retVal = (bool)EMVSIM_RD_CTRL_CRC_IN_FLIP(base);
    break;
    
    case kEmvsimCtrlCWTEnable: retVal = (bool)EMVSIM_RD_CTRL_CWT_EN(base);
    break;
    
    case kEmvsimCtrlLrcEnable: retVal = (bool)EMVSIM_RD_CTRL_LRC_EN(base);
    break;
    
    case kEmvsimCtrlCrcEnable: retVal = (bool)EMVSIM_RD_CTRL_CRC_EN(base);
    break;
    
    case kEmvsimCtrlXmtCrcOrLrcEnable: retVal = (bool)EMVSIM_RD_CTRL_XMT_CRC_LRC(base);
    break;
    
    case kEmvsimCtrlBWTEnable: retVal = (bool)EMVSIM_RD_CTRL_BWT_EN(base);
    break;
        
    default: break;
    }
    
    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EMVSIM_HAL_SetIntMode
 * Description   : This function masks/un-maskes the specific interrupt reasons 
 *                 to raise interrupt.
 *
 *END**************************************************************************/
void EMVSIM_HAL_SetIntMode(EMVSIM_Type *base, emvsim_interrupt_t interrupt, bool enable)
{
    switch ( interrupt )
    {
    case kEmvsimIntRxData :
        EMVSIM_WR_INT_MASK_RX_DATA_IM(base, (!enable));
        break;
    case kEmvsimIntGPCnt1 :
        EMVSIM_WR_INT_MASK_GPCNT1_IM(base, (!enable));
        break;
    case kEmvsimIntBGTErr :
        EMVSIM_WR_INT_MASK_BGT_ERR_IM(base, (!enable));
        break;
    case kEmvsimIntBWTErr :
        EMVSIM_WR_INT_MASK_BWT_ERR_IM(base, (!enable));
        break;
    case kEmvsimIntRxNackThreshold :
        EMVSIM_WR_INT_MASK_RNACK_IM(base, (!enable));
        break;
    case kEmvsimIntCWTErr :
        EMVSIM_WR_INT_MASK_CWT_ERR_IM(base, (!enable));
        break;
    case kEmvsimIntGPCnt0 :
        EMVSIM_WR_INT_MASK_GPCNT0_IM(base, (!enable));
        break;
    case kEmvsimIntTxDataThreshold :
        EMVSIM_WR_INT_MASK_TDT_IM(base, (!enable));
        break;
    case kEmvsimIntTxFIFOFull :
        EMVSIM_WR_INT_MASK_TFF_IM(base, (!enable));
        break;
    case kEmvsimIntTxNackThresold :
        EMVSIM_WR_INT_MASK_TNACK_IM(base, (!enable));
        break;
    case kEmvsimIntTxFIFOEmpty :
        EMVSIM_WR_INT_MASK_TFE_IM(base, (!enable));
        break;
    case kEmvsimIntEarlyTxComplete :
        EMVSIM_WR_INT_MASK_ETC_IM(base, (!enable));
        break;
    case kEmvsimIntRxFIFOOverflow :
        EMVSIM_WR_INT_MASK_RFO_IM(base, (!enable));
        break;
    case kEmvsimIntTxComplete :
        EMVSIM_WR_INT_MASK_TC_IM(base, (!enable));
        break;
    case kEmvsimIntRxDataThreshold :
        EMVSIM_WR_INT_MASK_RDT_IM(base, (!enable));
        break;
        
    case kEmvsimIntPresenceDetect :
        EMVSIM_WR_PCSR_SPDIM(base, (!enable));
        break;
        
    default:
        break;
    }
}
    
/*FUNCTION**********************************************************************
 *
 * Function Name : EMVSIM_HAL_GetIntMode
 * Description   : This function returns the current masks/un-maskes the specific 
 *                 interrupt reasons.
 *
 *END**************************************************************************/
bool EMVSIM_HAL_GetIntMode(EMVSIM_Type *base, emvsim_interrupt_t interrupt)
{
    uint8_t temp = 0;

    switch ( interrupt )
    {
    case kEmvsimIntRxData :
        temp = EMVSIM_RD_INT_MASK_RX_DATA_IM(base);
        break;
    case kEmvsimIntGPCnt1 :
        temp = EMVSIM_RD_INT_MASK_GPCNT1_IM(base);
        break;
    case kEmvsimIntBGTErr :
        temp = EMVSIM_RD_INT_MASK_BGT_ERR_IM(base);
        break;
    case kEmvsimIntBWTErr :
        temp = EMVSIM_RD_INT_MASK_BWT_ERR_IM(base);
        break;
    case kEmvsimIntRxNackThreshold :
        temp = EMVSIM_RD_INT_MASK_RNACK_IM(base);
        break;
    case kEmvsimIntCWTErr :
        temp = EMVSIM_RD_INT_MASK_CWT_ERR_IM(base);
        break;
    case kEmvsimIntGPCnt0 :
        temp = EMVSIM_RD_INT_MASK_GPCNT0_IM(base);
        break;
    case kEmvsimIntTxDataThreshold :
        temp = EMVSIM_RD_INT_MASK_TDT_IM(base);
        break;
    case kEmvsimIntTxFIFOFull :
        temp = EMVSIM_RD_INT_MASK_TFF_IM(base);
        break;
    case kEmvsimIntTxNackThresold :
        temp = EMVSIM_RD_INT_MASK_TNACK_IM(base);
        break;
    case kEmvsimIntTxFIFOEmpty :
        temp = EMVSIM_RD_INT_MASK_TFE_IM(base);
        break;
    case kEmvsimIntEarlyTxComplete :
        temp = EMVSIM_RD_INT_MASK_ETC_IM(base);
        break;
    case kEmvsimIntRxFIFOOverflow :
        temp = EMVSIM_RD_INT_MASK_RFO_IM(base);
        break;
    case kEmvsimIntTxComplete :
        temp = EMVSIM_RD_INT_MASK_TC_IM(base);
        break;
    case kEmvsimIntRxDataThreshold :
        temp = EMVSIM_RD_INT_MASK_RDT_IM(base);
        break;
        
    case kEmvsimIntPresenceDetect :
        temp = EMVSIM_RD_PCSR_SPDIM(base);
        break;
        
    default:
        break;
    }
    return (bool)(!temp);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EMVSIM_HAL_GetReceiveStatus
 * Description   : This function returns the receive status bit/flag states.
 *
 *END**************************************************************************/
bool EMVSIM_HAL_GetReceiveStatus(EMVSIM_Type *base, emvsim_rx_status_t rxStatus)
{
    uint8_t temp = 0;
    
    switch ( rxStatus )
    {
    case kEmvsimFrameErr :
        temp = EMVSIM_RD_RX_STATUS_FEF(base);
        break;
        
    case kEmvsimParityErr :
        temp = EMVSIM_RD_RX_STATUS_PEF(base);
        break;
        
    case kEmvsimBGTErr :
        temp = EMVSIM_RD_RX_STATUS_BGT_ERR(base);
        break;
        
    case kEmvsimBWTErr :
        temp = EMVSIM_RD_RX_STATUS_BWT_ERR(base);
        break;
        
    case kEmvsimRxNackThresholdErr :
        temp = EMVSIM_RD_RX_STATUS_RTE(base);
        break;
        
    case kEmvsimCWTErr :
        temp = EMVSIM_RD_RX_STATUS_CWT_ERR(base);
        break;
        
    case kEmvsimCRCCheckOk :
        temp = EMVSIM_RD_RX_STATUS_CRC_OK(base);
        break;
        
    case kEmvsimLRCCheckOk :
        temp = EMVSIM_RD_RX_STATUS_LRC_OK(base);
        break;
        
    case kEmvsimRxDataThreshold :
        temp = EMVSIM_RD_RX_STATUS_RDTF(base);
        break;
        
    case kEmvsimRxData :
        temp = EMVSIM_RD_RX_STATUS_RX_DATA(base);
        break;
        
    case kEmvsimRxDataOverflow :
        temp = EMVSIM_RD_RX_STATUS_RFO(base);
        break;
        
    default :
        break;
    }    
    return (bool)temp;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EMVSIM_HAL_ClearReceiveStatuss
 * Description   : This function clears the receive status bit/flag states.
 *
 *END**************************************************************************/
void EMVSIM_HAL_ClearReceiveStatus(EMVSIM_Type *base, emvsim_rx_status_t rxStatus)
{
    switch ( rxStatus )
    {
    case kEmvsimFrameErr :
        EMVSIM_WR_RX_STATUS_FEF(base, 1U);
        break;
        
    case kEmvsimParityErr :
        EMVSIM_WR_RX_STATUS_PEF(base, 1U);
        break;
        
    case kEmvsimBGTErr :
        EMVSIM_WR_RX_STATUS_BGT_ERR(base, 1U);
        break;
        
    case kEmvsimBWTErr :
	/* Reset the counter */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlBWTEnable, false);
	/* Clear error */
        EMVSIM_WR_RX_STATUS_BWT_ERR(base, 1U);
        break;
        
    case kEmvsimRxNackThresholdErr :
        EMVSIM_WR_RX_STATUS_RTE(base, 1U);
        break;
        
    case kEmvsimCWTErr :
	/* Reset the counter */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlCWTEnable, false);
	/* Clear error */
        EMVSIM_WR_RX_STATUS_CWT_ERR(base, 1U);
        break;
        
    case kEmvsimRxData :
        EMVSIM_WR_RX_STATUS_RX_DATA(base, 1U);
        break;
        
    case kEmvsimRxDataOverflow :
        EMVSIM_WR_RX_STATUS_RFO(base, 1U);
        break;
        
    case kEmvsimRxAllStatus:
        EMVSIM_WR_RX_STATUS(base, 0xFFFFFFFFU);
        break;
        
    default :
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EMVSIM_HAL_GetTransmitStatus
 * Description   : This function returns the transmit status bit/flag states.
 *
 *END**************************************************************************/
bool EMVSIM_HAL_GetTransmitStatus(EMVSIM_Type *base, emvsim_tx_status_t txStatus)
{
    uint8_t temp = 0;
    
    switch ( txStatus )
    {
    case kEmvsimGPCNT1Timeout :
        temp = EMVSIM_RD_TX_STATUS_GPCNT1_TO(base);
        break;
        
    case kEmvsimGPCNT0Timeout :
        temp = EMVSIM_RD_TX_STATUS_GPCNT0_TO(base);
        break;
        
    case kEmvsimTxDataThreshold :
        temp = EMVSIM_RD_TX_STATUS_TDTF(base);
        break;
        
    case kEmvsimTxFIFOFull :
        temp = EMVSIM_RD_TX_STATUS_TFF(base);
        break;
        
    case kEmvsimTxComplete :
        temp = EMVSIM_RD_TX_STATUS_TCF(base);
        break;
        
    case kEmvsimEarlyTxComplete :
        temp = EMVSIM_RD_TX_STATUS_ETCF(base);
        break;
        
    case kEmvsimTxFIFOEmpty :
        temp = EMVSIM_RD_TX_STATUS_TFE(base);
        break;
        
    case kEmvsimTxNackThresholdErr :
        temp = EMVSIM_RD_TX_STATUS_TNTE(base);
        break;
        
    default :
        break;
    }
    return (bool)temp;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EMVSIM_HAL_ClearTransmitStatus
 * Description   : This function clears the transmit status bit/flag states.
 *
 *END**************************************************************************/
void EMVSIM_HAL_ClearTransmitStatus(EMVSIM_Type *base, emvsim_tx_status_t txStatus)
{
    switch ( txStatus )
    {
    case kEmvsimGPCNT1Timeout :
        EMVSIM_WR_TX_STATUS_GPCNT1_TO(base, 1U);
        break;
        
    case kEmvsimGPCNT0Timeout :
        EMVSIM_WR_TX_STATUS_GPCNT0_TO(base, 1U);
        break;
                
    case kEmvsimTxFIFOFull :
        EMVSIM_WR_TX_STATUS_TFF(base, 1U);
        break;
        
    case kEmvsimTxComplete :
        EMVSIM_WR_TX_STATUS_TCF(base, 1U);
        break;
        
    case kEmvsimEarlyTxComplete :
        EMVSIM_WR_TX_STATUS_ETCF(base, 1U);
        break;
        
    case kEmvsimTxFIFOEmpty :
        EMVSIM_WR_TX_STATUS_TFE(base, 1U);
        break;
        
    case kEmvsimTxNackThresholdErr :
        EMVSIM_WR_TX_STATUS_TNTE(base, 1U);
        break;
        
    case kEmvsimTxAllStatus :
        EMVSIM_WR_TX_STATUS(base, 0xFFFFFFFFU);
        break;
        
    default :
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EMVSIM_HAL_SetGPCNTValue
 * Description   : This function sets the timeout value of the general purpose counter.
 *
 *END**************************************************************************/
void EMVSIM_HAL_SetGPCNTValue(EMVSIM_Type *base, uint8_t gpcntIndex, uint16_t gpcntVal)
{
    switch ( gpcntIndex )
    {
    case 0 :
        EMVSIM_WR_GPCNT0_VAL_GPCNT0(base, gpcntVal);
        break;
        
    case 1 :
        EMVSIM_WR_GPCNT1_VAL_GPCNT1(base, gpcntVal);
        break;
        
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EMVSIM_HAL_GetGPCNTValue
 * Description   : This function returns the timeout value set to the 
 *                 general purpose counter.
 *
 *END**************************************************************************/
uint16_t EMVSIM_HAL_GetGPCNTValue(EMVSIM_Type *base, uint8_t gpcntIndex)
{
    uint16_t gpcntVal = 0;
    
    switch ( gpcntIndex )
    {
    case 0 :
        gpcntVal = EMVSIM_RD_GPCNT0_VAL_GPCNT0(base);
        break;
        
    case 1 :
        gpcntVal = EMVSIM_RD_GPCNT1_VAL_GPCNT1(base);
        break;
        
    default:
        break;
    }
    return gpcntVal;
}

#endif /* FSL_FEATURE_SOC_EMVSIM_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/

