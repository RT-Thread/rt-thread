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

#include "fsl_uart_hal.h"

#if FSL_FEATURE_SOC_UART_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/
/*******************************************************************************
 * UART Common Configurations
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_Init
 * Description   : This function initializes the module to a known state.
 *
 *END**************************************************************************/
void UART_HAL_Init(UART_Type * base)
{
    UART_WR_BDH(base, 0U);
    UART_WR_BDL(base, 4U);
    UART_WR_C1(base, 0U);
    UART_WR_C2(base, 0U);
    UART_WR_S2(base, 0U);
    UART_WR_C3(base, 0U);
#if FSL_FEATURE_UART_HAS_ADDRESS_MATCHING
    UART_WR_MA1(base, 0U);
    UART_WR_MA2(base, 0U);
#endif
    UART_WR_C4(base, 0U);
#if FSL_FEATURE_UART_HAS_DMA_ENABLE
    UART_WR_C5(base, 0U);
#endif
#if FSL_FEATURE_UART_HAS_MODEM_SUPPORT
    UART_WR_MODEM(base, 0U);
#endif
#if FSL_FEATURE_UART_HAS_IR_SUPPORT
    UART_WR_IR(base, 0U);
#endif
#if FSL_FEATURE_UART_HAS_FIFO
    UART_WR_PFIFO(base, 0U);
    UART_WR_CFIFO(base, 0U);
    UART_WR_SFIFO(base, 0xC0U);
    UART_WR_TWFIFO(base, 0U);
    UART_WR_RWFIFO(base, 1U);
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetBaudRate
 * Description   : Configure the UART baud rate.
 * This function programs the UART baud rate to the desired value passed in by
 * the user. The user must also pass in the module source clock so that the
 * function can calculate the baud rate divisors to their appropriate values.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_SetBaudRate(UART_Type * base, uint32_t sourceClockInHz,
                                   uint32_t baudRate)
{
    /* BaudRate = (SourceClkInHz)/[16 * (SBR +  BRFA)] */
    uint16_t sbr;

    /* calculate the baud rate modulo divisor, sbr*/
    sbr = sourceClockInHz / (baudRate * 16);

    /* check to see if sbr is out of range of register bits */
    if ( (sbr > 0x1FFF) || (sbr < 1) )
    {
        /* unsupported baud rate for given source clock input*/
        return kStatus_UART_BaudRateCalculationError;
    }

    /* write the sbr value to the BDH and BDL registers*/
    UART_BWR_BDH_SBR(base, (uint8_t)(sbr >> 8));
    UART_WR_BDL(base, (uint8_t)sbr);

#if FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT
    /* determine if a fractional divider is needed to fine tune closer to the
     * desired baud, each value of brfa is in 1/32 increments,
     * hence the multiply-by-32. */
    uint16_t brfa = (32*sourceClockInHz/(baudRate*16)) - 32*sbr;

    /* write the brfa value to the register*/
    UART_BWR_C4_BRFA(base, brfa);
#endif

    return kStatus_UART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetBaudRateDivisor
 * Description   : Set the UART baud rate modulo divisor value.
 * This function allows the user to program the baud rate divisor directly in
 * situations where the divisor value is known. In this case, the user may not
 * want to call the UART_HAL_SetBaudRate() function as the divisor is already
 * known to them.
 *
 *END**************************************************************************/
void UART_HAL_SetBaudRateDivisor(UART_Type * base, uint16_t baudRateDivisor)
{
    /* check to see if baudRateDivisor is out of range of register bits */
    assert( (baudRateDivisor < 0x1FFF) && (baudRateDivisor > 1) );

    /* program the sbr (baudRateDivisor) value to the BDH and BDL registers*/
    UART_BWR_BDH_SBR(base, (uint8_t)(baudRateDivisor >> 8));
    UART_WR_BDL(base, (uint8_t)baudRateDivisor);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetParityMode
 * Description   : Configures the parity mode in the UART controller.
 * This function allows the user to configure the parity mode of the UART
 * controller to disable it or enable it for even parity or for odd parity.
 *
 *END**************************************************************************/
void UART_HAL_SetParityMode(UART_Type * base, uart_parity_mode_t parityMode)
{
    UART_BWR_C1_PE(base, parityMode >> 1U);
    UART_BWR_C1_PT(base, parityMode & 1U);
}

/*******************************************************************************
 * UART Transfer Functions
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_Putchar
 * Description   : This function allows the user to send an 8-bit character
 * from the UART data register.
 *
 *END**************************************************************************/
void UART_HAL_Putchar(UART_Type * base, uint8_t data)
{
    /* In addition to sending a char, this function also clears the transmit
     * status flags for this uart base, there is a two step process to clear
     * the transmit status flags:
     * 1. Read the status register with the status bit set
     * 2. write to the data register */
    uint8_t dummy = UART_RD_S1(base);
    dummy++; /* For unused variable warning */
    UART_WR_D(base, data);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_Putchar9
 * Description   : This function allows the user to send a 9-bit character from
 * the UART data register.
 *
 *END**************************************************************************/
void UART_HAL_Putchar9(UART_Type * base, uint16_t data)
{
    uint8_t ninthDataBit = (data >> 8U) & 0x1U;

    /* Write to the ninth data bit (bit position T8, where T[0:7]=8-bits,
     * T8=9th bit)*/
    UART_BWR_C3_T8(base, ninthDataBit);

    /* in addition to sending a char, this function also clears the transmit
     * status flags for this uart base, there is a two step process to
     * clear the transmit status flags:
     * 1. Read the status register with the status bit set
     * 2. write to the data register */
    uint8_t dummy = UART_RD_S1(base);
    dummy++; /* For unused variable warning */
    UART_WR_D(base, (uint8_t)data);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_Getchar
 * Description   : This function gets a received 8-bit character from the UART
 * data register.
 *
 *END**************************************************************************/
void UART_HAL_Getchar(UART_Type * base, uint8_t *readData)
{
    /* in addition to getting a char, this function also clears the receive
     * status flag RDRF along with IDLE, OR, NF, FE, and PF (these can also be
     * cleared in separate functions)
     * for this uart base, there is a two step process to clear the receive
     * status flag:
     * 1. Read the status register with the status bit set
     * 2. read from the data register */
    uint8_t dummy = UART_RD_S1(base);
    dummy++; /* For unused variable warning */
    *readData = UART_RD_D(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_Getchar9
 * Description   : This function gets a received 9-bit character from the UART
 * data register.
 *
 *END**************************************************************************/
void UART_HAL_Getchar9(UART_Type * base, uint16_t *readData)
{
    /* read ninth data bit and left shift to bit position R8 before reading
     * the 8 other data bits R[7:0]*/
    *readData = (uint16_t)UART_BRD_C3_R8(base) << 8;

    /* in addition to getting a char, this function also clears the receive
     * status flag RDRF along with IDLE, OR, NF, FE, and PF (these can also
     * be cleared in separate functions)
     * for this uart base, there is a two step process to clear the receive
     * status flag:
     * 1. Read the status register with the status bit set
     * 2. read from the data register */
    uint8_t dummy = UART_RD_S1(base);
    dummy++; /* For unused variable warning */
    *readData |= UART_RD_D(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SendDataPolling
 * Description   : Send out multiple bytes of data using polling method.
 * This function only supports 8-bit transaction.
 *
 *END**************************************************************************/
void UART_HAL_SendDataPolling(UART_Type * base,
                              const uint8_t *txBuff,
                              uint32_t txSize)
{
    while (txSize--)
    {
        while (!UART_BRD_S1_TDRE(base))
        {}

        UART_HAL_Putchar(base, *txBuff++);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_ReceiveDataPolling
 * Description   : Receive multiple bytes of data using polling method.
 * This function only supports 8-bit transaction.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_ReceiveDataPolling(UART_Type * base,
                                          uint8_t *rxBuff,
                                          uint32_t rxSize)
{
    uart_status_t retVal = kStatus_UART_Success;
    uint8_t dummy = 0;

    while (rxSize--)
    {
        while (!UART_BRD_S1_RDRF(base))
        {}

        UART_HAL_Getchar(base, rxBuff++);

        /* Clear the Overrun flag since it will block receiving */
        if (UART_BRD_S1_OR(base))
        {
            dummy = UART_RD_S1(base);
            dummy = UART_RD_D(base);
            dummy++; /* For unused variable warning */
            retVal = kStatus_UART_RxOverRun;
        }
    }

    return retVal;
}

/*******************************************************************************
 * UART Interrupts and DMA
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_ConfigureInterrupts
 * Description   : Configure the UART module interrupts to enable/disable various
 * interrupt sources.
 *
 *END**************************************************************************/
void UART_HAL_SetIntMode(UART_Type * base, uart_interrupt_t interrupt, bool enable)
{
    uint8_t reg = (uint32_t)interrupt >> UART_SHIFT;
    uint32_t temp = 1U << (uint8_t)interrupt;

    switch ( reg )
    {
        case 0 :
            enable ? UART_SET_BDH(base, temp) : UART_CLR_BDH(base, temp);
            break;
        case 1 :
            enable ? UART_SET_C2(base, temp) : UART_CLR_C2(base, temp);
            break;
        case 2 :
            enable ? UART_SET_C3(base, temp) : UART_CLR_C3(base, temp);
            break;
#if FSL_FEATURE_UART_HAS_FIFO
        case 3 :
            enable ? UART_SET_CFIFO(base, temp) : UART_CLR_CFIFO(base, temp);
            break;
#endif
        default :
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_GetIntMode
 * Description   : Return whether the UART module interrupts is enabled/disabled.
 *
 *END**************************************************************************/
bool UART_HAL_GetIntMode(UART_Type * base, uart_interrupt_t interrupt)
{
    uint8_t reg = (uint32_t)interrupt >> UART_SHIFT;
    uint8_t temp = 0;

    switch ( reg )
    {
        case 0 :
            temp = UART_RD_BDH(base) >> (uint8_t)(interrupt) & 1U;
            break;
        case 1 :
            temp = UART_RD_C2(base) >> (uint8_t)(interrupt) & 1U;
            break;
        case 2 :
            temp = UART_RD_C3(base) >> (uint8_t)(interrupt) & 1U;
            break;
#if FSL_FEATURE_UART_HAS_FIFO
        case 3 :
            temp = UART_RD_CFIFO(base) >> (uint8_t)(interrupt) & 1U;
            break;
#endif
        default :
            break;
    }
    return (bool)temp;
}

#if FSL_FEATURE_UART_HAS_DMA_SELECT
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetTxDmaCmd
 * Description   : Enable or disable UART DMA request for Transmitter.
 * This function allows the user to configure the receive data register full
 * flag to generate a DMA request.
 *
 *END**************************************************************************/
void UART_HAL_SetTxDmaCmd(UART_Type * base, bool enable)
{
    /* TDMAS configures the transmit data register empty flag, TDRE, to
     * generate interrupt or DMA requests if TIE is set.
     * NOTE: If UART_C2[TIE] is cleared, TDRE DMA and TDRE interrupt request
     * signals are not asserted when the TDRE flag is set, regardless of the
     * state of TDMAS. If UART_C2[TIE] and TDMAS are both set, then UART_C2[TCIE]
     * must be cleared, and UART_D must not be written outside of servicing of
     * a DMA request.
     * 0 If TIE is set and the TDRE flag is set, the TDRE interrupt request
     * signal is asserted to request interrupt service.
     * 1 If TIE is set and the TDRE flag is set, the TDRE DMA request signal
     * is asserted to request a DMA transfer. */
    if (enable)
    {
#if FSL_FEATURE_UART_IS_SCI
        UART_BWR_C4_TDMAS(base, 1U);
#else
        UART_BWR_C5_TDMAS(base, 1U);
#endif
        UART_BWR_C2_TCIE(base, 0U);
        UART_BWR_C2_TIE(base, 1U);
    }
    else
    {
        UART_BWR_C2_TIE(base, 0U);
#if FSL_FEATURE_UART_IS_SCI
        UART_BWR_C4_TDMAS(base, 0U);
#else
        UART_BWR_C5_TDMAS(base, 0U);
#endif
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetRxDmaCmd
 * Description   : Enable or disable UART DMA request for Receiver.
 * This function allows the user to configure the receive data register full
 * flag to generate a DMA request.
 *
 *END**************************************************************************/
void UART_HAL_SetRxDmaCmd(UART_Type * base, bool enable)
{
    /* RDMAS configures the receiver data register full flag, RDRF, to generate
     * interrupt or DMA requests if RIEis set.
     * NOTE: If RIE is cleared, the RDRF DMA and RDRF interrupt request signals
     * are not asserted when the RDRF flag is set, regardless of the state of
     * RDMAS.
     * 0 If RIE is set and the RDRF flag is set, the RDRF interrupt request
     * signal is asserted to request interrupt service.
     * 1 If RIE is set and the RDRF flag is set, the RDRF DMA request signal
     * is asserted to request a DMA transfer. */
#if FSL_FEATURE_UART_IS_SCI
    UART_BWR_C4_RDMAS(base, enable);
#else
    UART_BWR_C5_RDMAS(base, enable);
#endif
    UART_BWR_C2_RIE(base, enable);
}
#endif /* FSL_FEATURE_UART_HAS_DMA_SELECT */

#if FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetISO7816IntMode
 * Description   : Configure the UART module ISO7816 feature specific interrupts
 * to enable/disable various
 * interrupt sources.
 *
 *END**************************************************************************/
void UART_HAL_SetISO7816IntMode(UART_Type * base, uart_iso7816_interrupt_t interrupt, bool enable)
{
    switch (interrupt)
    {
    case kUartIntIso7816RxThreasholdExceeded:
        enable ? UART_BWR_IE7816_RXTE(base, 1U) : UART_BWR_IE7816_RXTE(base, 0U);
        break;
    case kUartIntIso7816TxThresholdExceeded:
        enable ? UART_BWR_IE7816_TXTE(base, 1U) : UART_BWR_IE7816_TXTE(base, 0U);
        break;
    case kUartIntIso7816GuardTimerViolated:
        enable ? UART_BWR_IE7816_GTVE(base, 1U) : UART_BWR_IE7816_GTVE(base, 0U);
        break;
#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
    case kUartIntIso7816AtrDurationTimer:
        enable ? UART_BWR_IE7816_ADTE(base, 1U) : UART_BWR_IE7816_ADTE(base, 0U);
        break;
#endif
    case kUartIntIso7816InitialCharDetected:
        enable ? UART_BWR_IE7816_INITDE(base, 1U) : UART_BWR_IE7816_INITDE(base, 0U);
        break;
    case kUartIntIso7816BlockWaitTimer:
        enable ? UART_BWR_IE7816_BWTE(base, 1U) : UART_BWR_IE7816_BWTE(base, 0U);
        break;
    case kUartIntIso7816CharWaitTimer:
        enable ? UART_BWR_IE7816_CWTE(base, 1U) : UART_BWR_IE7816_CWTE(base, 0U);
        break;
    case kUartIntIso7816WaitTimer:
        enable ? UART_BWR_IE7816_WTE(base, 1U) : UART_BWR_IE7816_WTE(base, 0U);
        break;
    case kUartIntIso7816All:
        enable ? UART_WR_IE7816(base, 0xFFU) : UART_WR_IE7816(base, 0x00U);
        break;
    default: break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_GetISO7816IntMode
 * Description   : Return whether the UART module ISO7816 feature specific interrupts
 * is enabled/disabled.
 *
 *END**************************************************************************/
bool UART_HAL_GetISO7816IntMode(UART_Type * base, uart_iso7816_interrupt_t interrupt)
{
    uint8_t temp = 0;

    switch (interrupt)
    {
    case kUartIntIso7816RxThreasholdExceeded:
      temp = UART_BRD_IE7816_RXTE(base);
      break;
    case kUartIntIso7816TxThresholdExceeded:
      temp = UART_BRD_IE7816_TXTE(base);
      break;
    case kUartIntIso7816GuardTimerViolated:
      temp = UART_BRD_IE7816_GTVE(base);
      break;
#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
    case kUartIntIso7816AtrDurationTimer:
      temp = UART_BRD_IE7816_ADTE(base);
      break;
#endif
    case kUartIntIso7816InitialCharDetected:
      temp = UART_BRD_IE7816_INITDE(base);
      break;
    case kUartIntIso7816BlockWaitTimer:
      temp = UART_BRD_IE7816_BWTE(base);
      break;
    case kUartIntIso7816CharWaitTimer:
      temp = UART_BRD_IE7816_CWTE(base);
      break;
    case kUartIntIso7816WaitTimer:
      temp = UART_BRD_IE7816_WTE(base);
      break;
    default: break;
    }

    return (bool)temp;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_ClearISO7816InterruptStatus
 * Description   : Clears the UART module ISO7816 feature specific interrupts
 *
 *END**************************************************************************/
void UART_HAL_ClearISO7816InterruptStatus(UART_Type * base, uart_iso7816_interrupt_t interrupt)
{
    if(interrupt == kUartIntIso7816All)
    {
        /* Clear all interrupt bits */
        UART_WR_IS7816(base, 0xFFU);
    }
    else
    {
        /* Clear the specific interrupt bit */
        UART_WR_IS7816(base, (1 << interrupt));
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_GetISO7816InterruptStatus
 * Description   : Returns the UART module ISO7816 feature specific interrupts bit state
 *
 *END**************************************************************************/
bool UART_HAL_GetISO7816InterruptStatus(UART_Type * base, uart_iso7816_interrupt_t interrupt)
{
    return (bool)((UART_RD_IS7816(base) & (uint8_t)(1 << interrupt)) >> interrupt);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetISO7816Etu
 * Description   : Sets the basic Elementaty Time Unit of UART instance in ISO7816
 * mode.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_SetISO7816Etu(UART_Type * base, uint32_t sourceClockInHz, uint32_t sCClock, uint16_t Fi, uint8_t Di)
{
    /* BaudRate = (SourceClkInHz)/[16 * (SBR +  BRFA)] */
    uint32_t brfa, sbr;
    uint32_t sourceClockInKHz = sourceClockInHz/1000;
    uint32_t sCClockInKHz = sCClock/1000;

    /* BaudRate = (SourceClkInHz)/[16 * (SBR +  BRFA)] */
    sbr = (uint16_t)(sourceClockInKHz * Fi/(Di* sCClockInKHz * 16));

    /* check to see if sbr is out of range of register bits */
    if ( (sbr > 0x1FFF) || (sbr < 1) )
    {
        /* unsupported baud rate for given source clock input*/
        return kStatus_UART_BaudRateCalculationError;
    }

    UART_BWR_BDH_SBR(base, (uint8_t)(sbr >> 8));
    UART_WR_BDL(base, (uint8_t)sbr);

#if FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT
    /* determine if a fractional divider is needed to fine tune closer to the
     * desired baud, each value of brfa is in 1/32 increments,
     * hence the multiply-by-32. */
    brfa = (32*sourceClockInKHz*Fi)/(Di*sCClockInKHz*16);
    brfa -= (uint16_t)(32*sbr);

    /* write the brfa value to the register*/
    UART_BWR_C4_BRFA(base, brfa);
#endif

    return kStatus_UART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_ResetISO7816WaitTimer
 * Description   : Resets the UART module ISO7816 Wait Timer
 *
 *END**************************************************************************/
void UART_HAL_ResetISO7816WaitTimer(UART_Type * base)
{
    uint8_t temp;

    /* save the current value of IE7816 registrer */
    temp = UART_RD_IE7816(base);

    /* disable 7816 function */
    UART_BWR_C7816_ISO_7816E(base, 0U);

    /* clear any pending WT interrupt flag */
    UART_BWR_IS7816_WT(base, 1U);

    /* enable 7816 function */
    UART_BWR_C7816_ISO_7816E(base, 1U);

    /* re-enable all interrupts */
    UART_WR_IE7816(base, temp);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_ResetISO7816CharacterWaitTimer
 * Description   : Resets the UART module ISO7816 Character Wait Timer
 *
 *END**************************************************************************/
void UART_HAL_ResetISO7816CharacterWaitTimer(UART_Type * base)
{
    uint8_t temp;

    /* save the current value of IE7816 registrer */
    temp = UART_RD_IE7816(base);

    /* disable 7816 function */
    UART_BWR_C7816_ISO_7816E(base, 0U);

    /* clear any pending Character WT interrupt flag */
    UART_BWR_IS7816_CWT(base, 1U);

    /* enable 7816 function */
    UART_BWR_C7816_ISO_7816E(base, 1U);

    /* re-enable all interrupts */
    UART_WR_IE7816(base, temp);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_ResetISO7816BlockWaitTimer
 * Description   : Resets UART module ISO7816 Block Wait Timer
 *
 *END**************************************************************************/
void UART_HAL_ResetISO7816BlockWaitTimer(UART_Type * base)
{
    uint8_t temp;

    /* save the current value of IE7816 registrer */
    temp = UART_RD_IE7816(base);

    /* disable 7816 function */
    UART_BWR_C7816_ISO_7816E(base, 0U);

    /* clear any pending Block WT interrupt flag */
    UART_BWR_IS7816_BWT(base, 1U);

    /* enable 7816 function */
    UART_BWR_C7816_ISO_7816E(base, 1U);

    /* re-enable all interrupts */
    UART_WR_IE7816(base, temp);
}
#endif  /* FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT */

#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
void UART_HAL_ResetWaitTimeMultipllier(UART_Type * base, uint8_t mWtx)
{
    uint8_t temp;

    temp = UART_RD_IE7816(base);
    UART_BWR_C7816_ISO_7816E(base, 0U);
    UART_WR_WP7816(base, mWtx);
    UART_WR_IE7816(base, temp);
}
#endif
/*******************************************************************************
 * UART UART Status Flags
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_GetStatusFlag
 * Description   : Get UART status flag states.
 *
 *END**************************************************************************/
bool UART_HAL_GetStatusFlag(UART_Type * base, uart_status_flag_t statusFlag)
{
    uint8_t reg = (uint32_t)statusFlag >> UART_SHIFT;
    uint8_t temp = 0;

    switch ( reg )
    {
        case 0 :
            temp = UART_RD_S1(base) >> (uint8_t)(statusFlag) & 1U;
            break;
        case 1 :
            temp = UART_RD_S2(base) >> (uint8_t)(statusFlag) & 1U;
            break;
#if FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS
        case 2 :
            temp = UART_RD_ED(base) >> (uint8_t)(statusFlag) & 1U;
            break;
#endif
#if FSL_FEATURE_UART_HAS_FIFO
        case 3 :
            temp = UART_RD_SFIFO(base) >> (uint8_t)(statusFlag) & 1U;
            break;
#endif
        default :
            break;
    }
    return (bool)temp;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_ClearStatusFlag
 * Description   : Clear an individual and specific UART status flag.
 * This function allows the user to clear an individual and specific UART
 * status flag. Refer to structure definition uart_status_flag_t for list of
 * status bits.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_ClearStatusFlag(UART_Type * base, uart_status_flag_t statusFlag)
{
    uart_status_t retVal = kStatus_UART_Success;
    uint8_t dummy = 0;
    dummy++; /* For unused variable warning */

    switch(statusFlag)
    {
        /* These flags are cleared automatically by other uart operations and
         * cannot be manually cleared, return error code. */
        case kUartTxDataRegEmpty:
        case kUartTxComplete:
        case kUartRxDataRegFull:
        case kUartRxActive:
#if FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS
        case kUartNoiseInCurrentWord:
        case kUartParityErrInCurrentWord:
#endif
#if FSL_FEATURE_UART_HAS_FIFO
        case kUartTxBuffEmpty:
        case kUartRxBuffEmpty:
#endif
            retVal = kStatus_UART_ClearStatusFlagError;
            break;

        case kUartIdleLineDetect:
        case kUartRxOverrun:
        case kUartNoiseDetect:
        case kUartFrameErr:
        case kUartParityErr:
            dummy = UART_RD_S1(base);
            dummy = UART_RD_D(base);
            break;

#if FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT
        case kUartLineBreakDetect:
            UART_WR_S2(base, UART_S2_LBKDIF_MASK);
            break;
#endif

        case kUartRxActiveEdgeDetect:
            UART_WR_S2(base, UART_S2_RXEDGIF_MASK);
            break;

#if FSL_FEATURE_UART_HAS_FIFO
        case kUartTxBuffOverflow:
            UART_WR_SFIFO(base, UART_SFIFO_TXOF_MASK);
            break;

        case kUartRxBuffUnderflow:
            UART_WR_SFIFO(base, UART_SFIFO_RXUF_MASK);
            break;
#endif
        default:
            break;
    }

    return retVal;
}

/*******************************************************************************
 * UART FIFO Configurations
 ******************************************************************************/
#if FSL_FEATURE_UART_HAS_FIFO
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetTxFifo
 * Description   : Enable or disable the UART transmit FIFO.
 * This function allows the user to enable or disable the UART transmit FIFO.
 * It is required that the transmitter/receiver should be disabled before
 * calling this function and when the FIFO is empty. Additionally, TXFLUSH and
 * RXFLUSH commands should be issued after calling this function.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_SetTxFifoCmd(UART_Type * base, bool enable)
{
    /* before enabling the tx fifo, UARTx_C2[TE] (transmitter) and
     * UARTx_C2[RE] (receiver) must be disabled.
     * if not, return an error code */
    uint8_t txEnable = UART_BRD_C2_TE(base);
    uint8_t rxEnable = UART_BRD_C2_RE(base);

    if (txEnable || rxEnable)
    {
        return kStatus_UART_TxOrRxNotDisabled;
    }
    else
    {
        UART_BWR_PFIFO_TXFE(base, enable);
        return kStatus_UART_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetRxFifoCmd
 * Description   : Enable or disable the UART receive FIFO.
 * This function allows the user to enable or disable the UART receive FIFO.
 * It is required that the transmitter/receiver should be disabled before calling
 * this function and when the FIFO is empty. Additionally, TXFLUSH and RXFLUSH
 * commands should be issued after calling this function.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_SetRxFifoCmd(UART_Type * base, bool enable)
{
    /* before enabling the rx fifo, UARTx_C2[TE] (transmitter) and
     * UARTx_C2[RE] (receiver) must be disabled
     * if not, return an error code */
    uint8_t txEnable = UART_BRD_C2_TE(base);
    uint8_t rxEnable = UART_BRD_C2_RE(base);

    if (txEnable || rxEnable)
    {
        return kStatus_UART_TxOrRxNotDisabled;
    }
    else
    {
        UART_BWR_PFIFO_RXFE(base, enable);
        return kStatus_UART_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_FlushTxFifo
 * Description   : Flush the UART transmit FIFO.
 * This function allows you to flush the UART transmit FIFO for a particular
 * module base. Flushing the FIFO may result in data loss. It is recommended
 * that the transmitter should be disabled before calling this function.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_FlushTxFifo(UART_Type * base)
{
    /* in order to flush the tx fifo, UARTx_C2[TE] (transmitter) must be
     * disabled. If not, return an error code */
    if (UART_BRD_C2_TE(base) != 0)
    {
        return kStatus_UART_TxNotDisabled;
    }
    else
    {
        /* Set the bit to flush fifo*/
        UART_BWR_CFIFO_TXFLUSH(base, 1U);
        return kStatus_UART_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_FlushRxFifo
 * Description   : Flush the UART receive FIFO.
 * This function allows you to flush the UART receive FIFO for a particular
 * module base. Flushing the FIFO may result in data loss. It is recommended
 * that the receiver should be disabled before calling this function.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_FlushRxFifo(UART_Type * base)
{
    /* in order to flush the rx fifo, UARTx_C2[RE] (receiver) must be disabled
     * if not, return an error code. */
    if (UART_BRD_C2_RE(base) != 0)
    {
        return kStatus_UART_RxNotDisabled;
    }
    else
    {
        /* Set the bit to flush fifo*/
        UART_BWR_CFIFO_RXFLUSH(base, 1U);
        return kStatus_UART_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetTxFifoWatermark
 * Description   : Set the UART transmit FIFO watermark value.
 * Programming the transmit watermark should be done when UART the transmitter is
 * disabled and the value must be set less than the size obtained from
 * UART_HAL_GetTxFifoSize.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_SetTxFifoWatermark(UART_Type * base, uint8_t watermark)
{
    /* in order to set the tx watermark, UARTx_C2[TE] (transmitter) must be
     * disabled. If not, return an error code */
    if (UART_BRD_C2_TE(base) != 0)
    {
        return kStatus_UART_TxNotDisabled;
    }
    else
    {
        /* Programming the transmit watermark should be done when the
         * transmitter is disabled and the value must be set less than
         * the size given in PFIFO[TXFIFOSIZE] */
        UART_WR_TWFIFO(base, watermark);
        return kStatus_UART_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetRxFifoWatermark
 * Description   : Set the UART receive FIFO watermark value.
 * Programming the receive watermark should be done when the receiver is disabled
 * and the value must be set less than the size obtained from UART_HAL_GetRxFifoSize
 * and greater than zero.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_SetRxFifoWatermark(UART_Type * base, uint8_t watermark)
{
    /* in order to set the rx watermark, UARTx_C2[RE] (receiver) must be disabled
     * if not, return an error code. */
    if (UART_BRD_C2_RE(base) != 0)
    {
        return kStatus_UART_RxNotDisabled;
    }
    else
    {
        /* Programming the receive watermark should be done when the receiver is
         * disabled and the value must be set less than the size given in
         * PFIFO[RXFIFOSIZE] and greater than zero.  */
        UART_WR_RWFIFO(base, watermark);
        return kStatus_UART_Success;
    }
}
#endif  /* FSL_FEATURE_UART_HAS_FIFO*/

/*******************************************************************************
 * UART Special Feature Configurations
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_PutReceiverInStandbyMode
 * Description   : Place the UART receiver in standby mode.
 * This function, when called, will place the UART receiver into standby mode.
 * In some UART bases, there is a condition that must be met before placing
 * rx in standby mode. Before placing UART in standby, you need to first
 * determine if receiver is set to wake on idle and if receiver is already in
 * idle state. Per ref manual:
 * NOTE: RWU should only be set with C1[WAKE] = 0 (wakeup on idle) if the
 * channel is currently not idle.
 * This can be determined by the S2[RAF] flag. If set to wake up FROM an IDLE
 * event and the channel is already idle, it is possible that the UART will
 * discard data since data must be received (or a LIN break detect) after an
 * IDLE is detected before IDLE is allowed to reasserted.
 *
 *END**************************************************************************/
uart_status_t UART_HAL_PutReceiverInStandbyMode(UART_Type * base)
{
    uart_wakeup_method_t rxWakeMethod;
    bool uart_current_rx_state;

    /* see if wake is set for idle or */
    rxWakeMethod = UART_HAL_GetReceiverWakeupMethod(base);
    uart_current_rx_state = UART_HAL_GetStatusFlag(base, kUartRxActive);

    /* if both rxWakeMethod is set for idle and current rx state is idle,
     * don't put in standy*/
    if ((rxWakeMethod == kUartIdleLineWake) && (uart_current_rx_state == 0))
    {
        return kStatus_UART_RxStandbyModeError;
    }
    else
    {
        /* set the RWU bit to place receiver into standby mode*/
        UART_SET_C2(base, UART_C2_RWU_MASK);
        return kStatus_UART_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_ConfigIdleLineDetect
 * Description   : Configure the operation options of the UART idle line detect.
 * This function allows the user to configure the UART idle-line detect
 * operation. There are two separate operations for the user to configure,
 * the idle line bit-count start and the receive wake up affect on IDLE status
 * bit. The user will pass in a stucture of type uart_idle_line_config_t.
 *
 *END**************************************************************************/
void UART_HAL_ConfigIdleLineDetect(UART_Type * base, uint8_t idleLine,
                                   uint8_t rxWakeIdleDetect)
{
    UART_BWR_C1_ILT(base, idleLine);
    UART_BWR_S2_RWUID(base, rxWakeIdleDetect);
}

#if FSL_FEATURE_UART_HAS_ADDRESS_MATCHING
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetMatchAddress
 * Description   : Configure the UART match address mode control operation.
 * (Note: Feature available on select UART bases)
 * The function allows the user to configure the UART match address control
 * operation. The user has the option to enable the match address mode and to
 * program the match address value. There are two match address modes, each with
 * it's own enable and programmable match address value.
 *
 *END**************************************************************************/
void UART_HAL_SetMatchAddress(UART_Type * base,
                              bool matchAddrMode1,
                              bool matchAddrMode2,
                              uint8_t matchAddrValue1,
                              uint8_t matchAddrValue2)
{
    /* Match Address Mode Enable 1 */
    UART_BWR_C4_MAEN1(base, matchAddrMode1);
    /* Match Address Mode Enable 2 */
    UART_BWR_C4_MAEN2(base, matchAddrMode2);
    /* match address register 1 */
    UART_WR_MA1(base, matchAddrValue1);
    /* match address register 2 */
    UART_WR_MA2(base, matchAddrValue2);
}
#endif

#if FSL_FEATURE_UART_HAS_IR_SUPPORT
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_HAL_SetInfraredOperation
 * Description   : Configure the UART infrared operation.
 * The function allows the user to enable or disable the UART infrared (IR)
 * operation and to configure the IR pulse width.
 *
 *END**************************************************************************/
void UART_HAL_SetInfraredOperation(UART_Type * base, bool enable,
                                   uart_ir_tx_pulsewidth_t pulseWidth)
{
    /* enable or disable infrared */
    UART_BWR_IR_IREN(base, enable);
    /* configure the narrow pulse width of the IR pulse */
    UART_BWR_IR_TNP(base, pulseWidth);
}
#endif  /* FSL_FEATURE_UART_HAS_IR_SUPPORT */

#endif /* FSL_FEATURE_SOC_UART_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/

