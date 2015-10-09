/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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

#include "fsl_lpsci_hal.h"

#if FSL_FEATURE_SOC_LPSCI_COUNT
/*******************************************************************************
 * Code
 ******************************************************************************/
/*******************************************************************************
 * LPSCI Common Configurations
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_Init
 * Description   : This function initializes the module to a known state.
 *
 *END**************************************************************************/
void LPSCI_HAL_Init(UART0_Type * base)
{
    UART0_WR_BDH(base, 0U);
    UART0_WR_BDL(base, 4U);
    UART0_WR_C1(base, 0U);
    UART0_WR_C2(base, 0U);
    UART0_WR_S2(base, 0U);
    UART0_WR_C3(base, 0U);
#if FSL_FEATURE_LPSCI_HAS_ADDRESS_MATCHING
    UART0_WR_MA1(base, 0U);
    UART0_WR_MA2(base, 0U);
#endif
    UART0_WR_C4(base, 0U);
#if FSL_FEATURE_LPSCI_HAS_DMA_ENABLE
    UART0_WR_C5(base, 0U);
#endif
#if FSL_FEATURE_LPSCI_HAS_MODEM_SUPPORT
    UART0_WR_MODEM(base, 0U);
#endif
#if FSL_FEATURE_LPSCI_HAS_IR_SUPPORT
    UART0_WR_IR(base, 0U);
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_SetBaudRate
 * Description   : Configure the LPSCI baud rate.
 * This function programs the LPSCI baud rate to the desired value passed in by
 * the user. The user must also pass in the module source clock so that the
 * function can calculate the baud rate divisors to their appropriate values.
 *
 *END**************************************************************************/
lpsci_status_t LPSCI_HAL_SetBaudRate(UART0_Type * base,
                                     uint32_t sourceClockInHz,
                                     uint32_t baudRate)
{
    uint16_t sbrTemp;
    uint32_t osr, sbr;
    uint8_t i;
    uint32_t tempDiff, calculatedBaud, baudDiff;

    /* This uart instantiation uses a slightly different baud rate calculation
     * The idea is to use the best OSR (over-sampling rate) possible
     * Note, osr is typically hard-set to 16 in other uart instantiations
     * First calculate the baud rate using the minimum OSR possible (4). */
    osr = 4;
    sbr = (sourceClockInHz/(baudRate * osr));
    calculatedBaud = (sourceClockInHz / (osr * sbr));

    if (calculatedBaud > baudRate)
    {
        baudDiff = calculatedBaud - baudRate;
    }
    else
    {
        baudDiff = baudRate - calculatedBaud;
    }

    /* loop to find the best osr value possible, one that generates minimum baudDiff
     * iterate through the rest of the supported values of osr */
    for (i = 5; i <= 32; i++)
    {
        /* calculate the temporary sbr value   */
        sbrTemp = (sourceClockInHz/(baudRate * i));
        /* calculate the baud rate based on the temporary osr and sbr values*/
        calculatedBaud = (sourceClockInHz / (i * sbrTemp));

        if (calculatedBaud > baudRate)
        {
            tempDiff = calculatedBaud - baudRate;
        }
        else
        {
            tempDiff = baudRate - calculatedBaud;
        }

        if (tempDiff <= baudDiff)
        {
            baudDiff = tempDiff;
            osr = i;  /* update and store the best osr value calculated*/
            sbr = sbrTemp;  /* update store the best sbr value calculated*/
        }
    }

    /* next, check to see if actual baud rate is within 3% of desired baud rate
     * based on the best calculate osr value */
    if (baudDiff < ((baudRate / 100) * 3))
    {
        /* Acceptable baud rate */
        /* Check if osr is between 4x and 7x oversampling*/
        /* If so, then "BOTHEDGE" sampling must be turned on*/
        if ((osr > 3) && (osr < 8))
        {
            UART0_SET_C5(base, UART0_C5_BOTHEDGE_MASK);
        }

        /* program the osr value (bit value is one less than actual value)*/
        UART0_BWR_C4_OSR(base, osr-1);

        /* program the sbr (divider) value obtained above*/
        UART0_BWR_BDH_SBR(base, (uint8_t)(sbr >> 8));
        UART0_WR_BDL(base, (uint8_t)sbr);
    }
    else
    {
        /* Unacceptable baud rate difference of more than 3%*/
        return kStatus_LPSCI_BaudRateCalculationError ;
    }

    return kStatus_LPSCI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_SetBaudRateDivisor
 * Description   : Set the LPSCI baud rate modulo divisor value.
 * This function allows the user to program the baud rate divisor directly in
 * situations where the divisor value is known. In this case, the user may not
 * want to call the LPSCI_HAL_SetBaudRate() function as the divisor is already
 * known to them.
 *
 *END**************************************************************************/
void LPSCI_HAL_SetBaudRateDivisor(UART0_Type * base, uint16_t baudRateDivisor)
{
    /* check to see if baudRateDivisor is out of range of register bits */
    assert( (baudRateDivisor < 0x1FFF) && (baudRateDivisor > 1) );

    /* program the sbr (baudRateDivisor) value to the BDH and BDL registers*/
    UART0_BWR_BDH_SBR(base, (uint8_t)(baudRateDivisor >> 8));
    UART0_WR_BDL(base, (uint8_t)baudRateDivisor);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_SetTxRxInversionCmd
 * Description   : Configures the parity mode in the LPSCI controller.
 * This function allows the user to configure the parity mode of the LPSCI
 * controller to disable it or enable it for even parity or for odd parity.
 *
 *END**************************************************************************/
void LPSCI_HAL_SetParityMode(UART0_Type * base, lpsci_parity_mode_t parityMode)
{
    UART0_BWR_C1_PE(base, parityMode >> 1U);
    UART0_BWR_C1_PT(base, parityMode & 1U);
}

/*******************************************************************************
 * LPSCI Transfer Functions
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_Putchar9
 * Description   : This function allows the user to send a 9-bit character from
 * the LPSCI data register.
 *
 *END**************************************************************************/
void LPSCI_HAL_Putchar9(UART0_Type * base, uint16_t data)
{
    uint8_t ninthDataBit;

    ninthDataBit = (data >> 8U) & 0x1U;

    /* Write to the ninth data bit (bit position T8) */
    UART0_BWR_C3_R9T8(base, ninthDataBit);

    UART0_WR_D(base, (uint8_t)data);
}
/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_Putchar10
 * Description   : This function allows the user to send a 10-bit character from
 * the LPSCI data register.
 *
 *END**************************************************************************/
void LPSCI_HAL_Putchar10(UART0_Type * base, uint16_t data)
{
    uint8_t ninthDataBit, tenthDataBit;

    ninthDataBit = (data >> 8U) & 0x1U;
    tenthDataBit = (data >> 9U) & 0x1U;

    /* Write to the tenth data bit (bit position T9) */
    UART0_BWR_C3_R8T9(base, tenthDataBit);

    /* Write to the ninth data bit (bit position T8) */
    UART0_BWR_C3_R9T8(base, ninthDataBit);

    UART0_WR_D(base, (uint8_t)data);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_Getchar9
 * Description   : This function gets a received 9-bit character from the LPSCI
 * data register.
 *
 *END**************************************************************************/
void LPSCI_HAL_Getchar9(UART0_Type * base, uint16_t *readData)
{
    *readData = (uint16_t)UART0_BRD_C3_R8T9(base) << 8;
    *readData |= UART0_RD_D(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_Getchar10
 * Description   : This function gets a received 10-bit character from the LPSCI
 * data register.
 *
 *END**************************************************************************/
void LPSCI_HAL_Getchar10(UART0_Type * base, uint16_t *readData)
{
    *readData = (uint16_t)((uint32_t)(UART0_BRD_C3_R9T8(base)) << 9U);
    *readData |= (uint16_t)((uint32_t)(UART0_BRD_C3_R8T9(base)) << 8U);
    *readData |= UART0_RD_D(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_SendDataPolling
 * Description   : Send out multiple bytes of data using polling method.
 * This function only supports 8-bit transaction.
 *
 *END**************************************************************************/
void LPSCI_HAL_SendDataPolling(UART0_Type * base,
                               const uint8_t *txBuff,
                               uint32_t txSize)
{
    while (txSize--)
    {
        while (!UART0_BRD_S1_TDRE(base))
        {}

        LPSCI_HAL_Putchar(base, *txBuff++);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_ReceiveDataPolling
 * Description   : Receive multiple bytes of data using polling method.
 * This function only supports 8-bit transaction.
 *
 *END**************************************************************************/
lpsci_status_t LPSCI_HAL_ReceiveDataPolling(UART0_Type * base,
                                            uint8_t *rxBuff,
                                            uint32_t rxSize)
{
    lpsci_status_t retVal = kStatus_LPSCI_Success;

    while (rxSize--)
    {
        while (!UART0_BRD_S1_RDRF(base))
        {}

        LPSCI_HAL_Getchar(base, rxBuff++);

        /* Clear the Overrun flag since it will block receiving */
        if(UART0_BRD_S1_OR(base))
        {
            UART0_BWR_S1_OR(base, 1U);
            retVal = kStatus_LPSCI_RxOverRun;
        }
    }

    return retVal;
}

/*******************************************************************************
 * LPSCI Interrupts and DMA
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_ConfigureInterrupts
 * Description   : Configure the LPSCI module interrupts to enable/disable
 * various interrupt sources.
 *
 *END**************************************************************************/
void LPSCI_HAL_SetIntMode(UART0_Type * base, lpsci_interrupt_t interrupt, bool enable)
{
    uint8_t reg = (uint32_t)interrupt >> LPSCI_SHIFT;
    uint32_t temp = 1U << (uint8_t)interrupt;

    switch ( reg )
    {
        case 0 :
            enable ? UART0_SET_BDH(base, temp) : UART0_CLR_BDH(base, temp);
            break;
        case 1 :
            enable ? UART0_SET_C2(base, temp) : UART0_CLR_C2(base, temp);
            break;
        case 2 :
            enable ? UART0_SET_C3(base, temp) : UART0_CLR_C3(base, temp);
            break;
        default :
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_GetIntMode
 * Description   : Return whether the LPSCI module interrupts is enabled/disabled.
 *
 *END**************************************************************************/
bool LPSCI_HAL_GetIntMode(UART0_Type * base, lpsci_interrupt_t interrupt)
{
    uint8_t reg = (uint32_t)interrupt >> LPSCI_SHIFT;
    uint8_t temp = 0;

    switch ( reg )
    {
        case 0 :
            temp = UART0_RD_BDH(base) >> (uint8_t)(interrupt) & 1U;
            break;
        case 1 :
            temp = UART0_RD_C2(base) >> (uint8_t)(interrupt) & 1U;
            break;
        case 2 :
            temp = UART0_RD_C3(base) >> (uint8_t)(interrupt) & 1U;
            break;
        default :
            break;
    }
    return (bool)temp;
}

#if FSL_FEATURE_LPSCI_HAS_DMA_ENABLE
/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_SetTxDmaCmd
 * Description   : Enable or disable LPSCI DMA request for Transmitter.
 * This function allows the user to configure the receive data register full
 * flag to generate a DMA request.
 *
 *END**************************************************************************/
void LPSCI_HAL_SetTxDmaCmd(UART0_Type * base, bool enable)
{
    UART0_BWR_C5_TDMAE(base, enable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_SetRxDmaCmd
 * Description   : Enable or disable LPSCI DMA request for Receiver.
 * This function allows the user to configure the receive data register full
 * flag to generate a DMA request.
 *
 *END**************************************************************************/
void LPSCI_HAL_SetRxDmaCmd(UART0_Type * base, bool enable)
{
    UART0_BWR_C5_RDMAE(base, enable);
}
#endif

/*******************************************************************************
 * LPSCI LPSCI Status Flags
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_GetStatusFlag
 * Description   : Get LPSCI status flag states.
 *
 *END**************************************************************************/
bool LPSCI_HAL_GetStatusFlag(UART0_Type * base, lpsci_status_flag_t statusFlag)
{
    uint8_t reg = (uint32_t)statusFlag >> LPSCI_SHIFT;
    uint8_t temp = 0;

    switch ( reg )
    {
        case 0 :
            temp = UART0_RD_S1(base) >> (uint8_t)(statusFlag) & 1U;
            break;
        case 1 :
            temp = UART0_RD_S2(base) >> (uint8_t)(statusFlag) & 1U;
            break;
#if FSL_FEATURE_LPSCI_HAS_EXTENDED_DATA_REGISTER_FLAGS
        case 2 :
            temp = UART0_RD_ED(base) >> (uint8_t)(statusFlag) & 1U;
            break;
#endif
        default :
            break;
    }
    return (bool)temp;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_ClearStatusFlag
 * Description   : Clear an individual and specific LPSCI status flag.
 * This function allows the user to clear an individual and specific LPSCI
 * status flag. Refer to structure definition lpsci_status_flag_t for list of
 * status bits.
 *
 *END**************************************************************************/
lpsci_status_t LPSCI_HAL_ClearStatusFlag(UART0_Type * base,
                                         lpsci_status_flag_t statusFlag)
{
    lpsci_status_t returnCode = kStatus_LPSCI_Success;

    switch(statusFlag)
    {
        /* These flags are cleared automatically by other lpuart operations
         * and cannot be manually cleared, return error code */
        case kLpsciTxDataRegEmpty:
        case kLpsciTxComplete:
        case kLpsciRxDataRegFull:
        case kLpsciRxActive:
 #if FSL_FEATURE_LPSCI_HAS_EXTENDED_DATA_REGISTER_FLAGS
        case kLpsciNoiseInCurrentWord:
        case kLpsciParityErrInCurrentWord:
#endif
            returnCode = kStatus_LPSCI_ClearStatusFlagError;
            break;

        case kLpsciIdleLineDetect:
            UART0_WR_S1(base, UART0_S1_IDLE_MASK);
            break;

        case kLpsciRxOverrun:
            UART0_WR_S1(base, UART0_S1_OR_MASK);
            break;

        case kLpsciNoiseDetect:
            UART0_WR_S1(base, UART0_S1_NF_MASK);
            break;

        case kLpsciFrameErr:
            UART0_WR_S1(base, UART0_S1_FE_MASK);
            break;

        case kLpsciParityErr:
            UART0_WR_S1(base, UART0_S1_PF_MASK);
            break;

        case kLpsciLineBreakDetect:
            UART0_WR_S2(base, UART0_S2_LBKDIF_MASK);
            break;

        case kLpsciRxActiveEdgeDetect:
            UART0_WR_S2(base, UART0_S2_RXEDGIF_MASK);
            break;

        default:
            returnCode = kStatus_LPSCI_ClearStatusFlagError;
            break;
    }

    return (returnCode);
}

/*******************************************************************************
 * LPSCI Special Feature Configurations
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_PutReceiverInStandbyMode
 * Description   : Place the LPSCI receiver in standby mode.
 * This function, when called, will place the LPSCI receiver into standby mode.
 * In some LPSCI, there is a condition that must be met before placing rx in
 * standby mode. Before placing LPSCI in standby, you need to first determine
 * if receiver is set to wake on idle and if receiver is already in idle state.
 *
 *END**************************************************************************/
lpsci_status_t LPSCI_HAL_PutReceiverInStandbyMode(UART0_Type * base)
{
    lpsci_wakeup_method_t rxWakeMethod;
    bool lpsci_current_rx_state;

    /* see if wake is set for idle or */
    rxWakeMethod = LPSCI_HAL_GetReceiverWakeupMethod(base);
    lpsci_current_rx_state = LPSCI_HAL_GetStatusFlag(base, kLpsciRxActive);

    /* if both rxWakeMethod is set for idle and current rx state is idle,
     * don't put in standy*/
    if ((rxWakeMethod == kLpsciIdleLineWake) && (lpsci_current_rx_state == 0))
    {
        return kStatus_LPSCI_RxStandbyModeError;
    }
    else
    {
        /* set the RWU bit to place receiver into standby mode*/
        UART0_SET_C2(base, UART0_C2_RWU_MASK);
        return kStatus_LPSCI_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_ConfigIdleLineDetect
 * Description   : Configure the operation options of the LPSCI idle line detect.
 * This function allows the user to configure the LPSCI idle-line detect
 * operation. There are two separate operations for the user to configure, the
 * idle line bit-count start and the receive wake up affect on IDLE status bit.
 * The user will pass in a stucture of type lpsci_idle_line_config_t.
 *
 *END**************************************************************************/
void LPSCI_HAL_ConfigIdleLineDetect(UART0_Type * base,
                                    uint8_t idleLine,
                                    uint8_t rxWakeIdleDetect)
{
    /* Configure the idle line detection configuration as follows:
     * configure the ILT to bit count after start bit or stop bit
     * configure RWUID to set or not set IDLE status bit upon detection of
     * an idle character when recevier in standby */
    UART0_BWR_C1_ILT(base, idleLine);
    UART0_BWR_S2_RWUID(base, rxWakeIdleDetect);
}

#if FSL_FEATURE_LPSCI_HAS_ADDRESS_MATCHING
/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_SetMatchAddress
 * Description   : Configure the LPSCI match address mode control operation. The
 * function allows the user to configure the LPSCI match address control
 * operation. The user has the option to enable the match address mode and to
 * program the match address value. There are two match address modes, each with
 * it's own enable and programmable match address value.
 *
 *END**************************************************************************/
void LPSCI_HAL_SetMatchAddress(UART0_Type * base,
                               bool matchAddrMode1,
                               bool matchAddrMode2,
                               uint8_t matchAddrValue1,
                               uint8_t matchAddrValue2)
{
    /* Match Address Mode Enable 1 */
    UART0_BWR_C4_MAEN1(base, matchAddrMode1);
    /* Match Address Mode Enable 2 */
    UART0_BWR_C4_MAEN2(base, matchAddrMode2);
    /* match address register 1 */
    UART0_WR_MA1(base, matchAddrValue1);
    /* match address register 2 */
    UART0_WR_MA2(base, matchAddrValue2);
}
#endif

#if FSL_FEATURE_LPSCI_HAS_IR_SUPPORT
/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_HAL_SetInfraredOperation
 * Description   : Configure the LPSCI infrared operation.
 * The function allows the user to enable or disable the LPSCI infrared (IR)
 * operation and to configure the IR pulse width.
 *
 *END**************************************************************************/
void LPSCI_HAL_SetInfraredOperation(UART0_Type * base,
                                    bool enable,
                                    lpsci_ir_tx_pulsewidth_t pulseWidth)
{
    /* enable or disable infrared */
    UART0_BWR_IR_IREN(base, enable);
    /* configure the narrow pulse width of the IR pulse */
    UART0_BWR_IR_TNP(base, pulseWidth);
}
#endif  /* FSL_FEATURE_LPSCI_HAS_IR_SUPPORT */

#endif /* FSL_FEATURE_SOC_LPSCI_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

