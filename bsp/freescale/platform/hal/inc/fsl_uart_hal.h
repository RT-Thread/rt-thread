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
#ifndef __FSL_UART_HAL_H__
#define __FSL_UART_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup uart_hal
 * @{
 */

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define UART_SHIFT (8U)

/*! @brief Error codes for the UART driver. */
typedef enum _uart_status
{
    kStatus_UART_Success                  = 0x00U,
    kStatus_UART_Fail                     = 0x01U,
    kStatus_UART_BaudRateCalculationError = 0x02U,
    kStatus_UART_RxStandbyModeError       = 0x03U,
    kStatus_UART_ClearStatusFlagError     = 0x04U,
    kStatus_UART_TxNotDisabled            = 0x05U,
    kStatus_UART_RxNotDisabled            = 0x06U,
    kStatus_UART_TxOrRxNotDisabled        = 0x07U,
    kStatus_UART_TxBusy                   = 0x08U,
    kStatus_UART_RxBusy                   = 0x09U,
    kStatus_UART_NoTransmitInProgress     = 0x0AU,
    kStatus_UART_NoReceiveInProgress      = 0x0BU,
    kStatus_UART_Timeout                  = 0x0CU,
    kStatus_UART_Initialized              = 0x0DU,
    kStatus_UART_NoDataToDeal             = 0x0EU,
    kStatus_UART_RxOverRun                = 0x0FU
} uart_status_t;

/*!
 * @brief UART number of stop bits.
 *
 * These constants define the number of allowable stop bits to configure in a UART base.
 */
typedef enum _uart_stop_bit_count {
    kUartOneStopBit = 0U,  /*!< one stop bit @internal gui name="1" */
    kUartTwoStopBit = 1U,  /*!< two stop bits @internal gui name="2" */
} uart_stop_bit_count_t;

/*!
 * @brief UART parity mode.
 *
 * These constants define the UART parity mode options: disabled or enabled of type even or odd.
 */
typedef enum _uart_parity_mode {
    kUartParityDisabled = 0x0U,  /*!< parity disabled @internal gui name="Disabled" */
    kUartParityEven     = 0x2U,  /*!< parity enabled, type even, bit setting: PE|PT = 10 @internal gui name="Even" */
    kUartParityOdd      = 0x3U,  /*!< parity enabled, type odd,  bit setting: PE|PT = 11 @internal gui name="Odd" */
} uart_parity_mode_t;

/*!
 * @brief UART number of bits in a character.
 *
 * These constants define the number of allowable data bits per UART character. Note, check the
 * UART documentation to determine if the desired UART base supports the desired number
 * of data bits per UART character.
 */
typedef enum  _uart_bit_count_per_char {
    kUart8BitsPerChar = 0U,   /*!< 8-bit data characters @internal gui name="8" */
    kUart9BitsPerChar = 1U,   /*!< 9-bit data characters @internal gui name="9" */
} uart_bit_count_per_char_t;

/*!
 * @brief UART operation configuration constants.
 *
 * This provides constants for UART operational states: "operates normally"
 * or "stops/ceases operation"
 */
typedef enum _uart_operation_config {
    kUartOperates = 0U,  /*!< UART continues to operate normally */
    kUartStops = 1U,     /*!< UART ceases operation */
} uart_operation_config_t;

/*! @brief UART receiver source select mode. */
typedef enum _uart_receiver_source {
    kUartLoopBack = 0U,  /*!< Internal loop back mode. */
    kUartSingleWire = 1U,/*!< Single wire mode. */
} uart_receiver_source_t ;

/*!
 * @brief UART wakeup from standby method constants.
 *
 * This provides constants for the two UART wakeup methods: idle-line or address-mark.
 */
typedef enum _uart_wakeup_method {
    kUartIdleLineWake = 0U,  /*!< The idle-line wakes UART receiver from standby */
    kUartAddrMarkWake = 1U,  /*!< The address-mark wakes UART receiver from standby */
} uart_wakeup_method_t;

/*!
 * @brief UART idle-line detect selection types.
 *
 * This provides constants for the UART idle character bit-count start: either after start or
 * stop bit.
 */
typedef enum _uart_idle_line_select {
    kUartIdleLineAfterStartBit = 0U,  /*!< UART idle character bit count start after start bit */
    kUartIdleLineAfterStopBit = 1U,   /*!< UART idle character bit count start after stop bit */
} uart_idle_line_select_t;

/*!
 * @brief UART break character length settings for transmit/detect.
 *
 * This provides constants for the UART break character length for both transmission and detection
 * purposes. Note that the actual maximum bit times may vary depending on the UART base.
 */
typedef enum _uart_break_char_length {
    kUartBreakChar10BitMinimum = 0U, /*!< UART break char length 10 bit times (if M = 0, SBNS = 0) or
                                     11 (if M = 1, SBNS = 0 or M = 0, SBNS = 1) or 12 (if M = 1,
                                     SBNS = 1 or M10 = 1, SNBS = 0) or 13 (if M10 = 1, SNBS = 1) */
    kUartBreakChar13BitMinimum = 1U, /*!< UART break char length 13 bit times (if M = 0, SBNS = 0) or
                                     14 (if M = 1, SBNS = 0 or M = 0, SBNS = 1) or 15 (if M = 1,
                                     SBNS = 1 or M10 = 1, SNBS = 0) or 16 (if M10 = 1, SNBS = 1) */
} uart_break_char_length_t;

/*!
 * @brief UART single-wire mode transmit direction.
 *
 *  This provides constants for the UART transmit direction when configured for single-wire mode.
 *  The transmit line TXDIR is either an input or output.
 */
typedef enum _uart_singlewire_txdir {
    kUartSinglewireTxdirIn = 0U,  /*!< UART Single-Wire mode TXDIR input */
    kUartSinglewireTxdirOut = 1U, /*!< UART Single-Wire mode TXDIR output */
} uart_singlewire_txdir_t;

/*!
 * @brief UART infrared transmitter pulse width options.
 *
 * This provides constants for the UART infrared (IR) pulse widths. Options include 3/16, 1/16
 * 1/32, and 1/4 pulse widths.
 */
typedef enum _uart_ir_tx_pulsewidth {
    kUartIrThreeSixteenthsWidth = 0U,   /*!< 3/16 pulse */
    kUartIrOneSixteenthWidth = 1U,      /*!< 1/16 pulse */
    kUartIrOneThirtysecondsWidth = 2U,  /*!< 1/32 pulse */
    kUartIrOneFourthWidth = 3U,         /*!< 1/4 pulse */
} uart_ir_tx_pulsewidth_t;

/*!
 * @brief UART ISO7816 transport protocol type options.
 *
 * This provides constants for the UART ISO7816 transport ptotocol types.
 */
typedef enum _uart_iso7816_tranfer_protocoltype {
    kUartIso7816TransfertType0 = 0U,   /*!< Transfer type 0 */
    kUartIso7816TransfertType1 = 1U,   /*!< Transfer type 1 */
} uart_iso7816_transfer_protocoltype_t;

/*!
 * @brief UART ISO7816 ONACK generation.
 *
 * This provides constants for the UART ISO7816 module ONACK generation.
 */
typedef enum _uart_iso7816_onack_config{
    kUartIso7816OnackEnable     = 0U,   /*!< Enable ONACK generation */
    kUartIso7816OnackDisable    = 1U,   /*!< Disable ONACK generation */
} uart_iso7816_onack_config_t;

/*!
 * @brief UART ISO7816 ANACK generation.
 *
 * This provides constants for the UART ISO7816 module ANACK generation.
 */
typedef enum _uart_iso7816_anack_config{
    kUartIso7816AnackDisable    = 0U,   /*!< Disable ANACK generation */
    kUartIso7816AnackEnable     = 1U,   /*!< Enable ANACK generation */
} uart_iso7816_anack_config_t;

/*!
 * @brief UART ISO7816 Initial Character detection.
 *
 * This provides constants for the UART ISO7816 module Initial generation.
 */
typedef enum _uart_iso7816_initd_config{
    kUartIso7816InitdDisable     = 0U,   /*!< Disable Initial Character detection */
    kUartIso7816InitdEnable    = 1U,   /*!< Enable Initial Character detection */
} uart_iso7816_initd_config_t;

/*!
 * @brief UART status flags.
 *
 * This provides constants for the UART status flags for use in the UART functions.
 */
typedef enum _uart_status_flag {
    kUartTxDataRegEmpty = 0U << UART_SHIFT | UART_S1_TDRE_SHIFT, /*!< Transmit data register empty flag, sets when transmit buffer is empty */
    kUartTxComplete     = 0U << UART_SHIFT | UART_S1_TC_SHIFT,   /*!< Transmission complete flag, sets when transmission activity complete */
    kUartRxDataRegFull  = 0U << UART_SHIFT | UART_S1_RDRF_SHIFT, /*!< Receive data register full flag, sets when the receive data buffer is full */
    kUartIdleLineDetect = 0U << UART_SHIFT | UART_S1_IDLE_SHIFT, /*!< Idle line detect flag, sets when idle line detected */
    kUartRxOverrun      = 0U << UART_SHIFT | UART_S1_OR_SHIFT,   /*!< Receive Overrun, sets when new data is received before data is read from receive register */
    kUartNoiseDetect    = 0U << UART_SHIFT | UART_S1_NF_SHIFT,   /*!< Receive takes 3 samples of each received bit. If any of these samples differ, noise flag sets */
    kUartFrameErr       = 0U << UART_SHIFT | UART_S1_FE_SHIFT,   /*!< Frame error flag, sets if logic 0 was detected where stop bit expected */
    kUartParityErr      = 0U << UART_SHIFT | UART_S1_PF_SHIFT,   /*!< If parity enabled, sets upon parity error detection */
#if FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT
    kUartLineBreakDetect    = 1U << UART_SHIFT | UART_S2_LBKDIF_SHIFT,  /*!< LIN break detect interrupt flag, sets when LIN break char detected and LIN circuit enabled */
#endif
    kUartRxActiveEdgeDetect = 1U << UART_SHIFT | UART_S2_RXEDGIF_SHIFT, /*!< Receive pin active edge interrupt flag, sets when active edge detected */
    kUartRxActive           = 1U << UART_SHIFT | UART_S2_RAF_SHIFT,     /*!< Receiver Active Flag (RAF), sets at beginning of valid start bit */
#if FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS
    kUartNoiseInCurrentWord     = 2U << UART_SHIFT | UART_ED_NOISY_SHIFT,   /*!< NOISY bit, sets if noise detected in current data word */
    kUartParityErrInCurrentWord = 2U << UART_SHIFT | UART_ED_PARITYE_SHIFT, /*!< PARITYE bit, sets if noise detected in current data word */
#endif
#if FSL_FEATURE_UART_HAS_FIFO
    kUartTxBuffEmpty     = 3U << UART_SHIFT | UART_SFIFO_TXEMPT_SHIFT, /*!< TXEMPT bit, sets if transmit buffer is empty */
    kUartRxBuffEmpty     = 3U << UART_SHIFT | UART_SFIFO_RXEMPT_SHIFT, /*!< RXEMPT bit, sets if receive buffer is empty */
    kUartTxBuffOverflow  = 3U << UART_SHIFT | UART_SFIFO_TXOF_SHIFT,   /*!< TXOF bit, sets if transmit buffer overflow occurred */
    kUartRxBuffUnderflow = 3U << UART_SHIFT | UART_SFIFO_RXUF_SHIFT,   /*!< RXUF bit, sets if receive buffer underflow occurred */
#endif
} uart_status_flag_t;

/*!
 * @brief UART interrupt configuration structure, default settings are 0 (disabled).
 *
 * This structure contains the settings for all of the UART interrupt configurations.
 */
typedef enum _uart_interrupt {
#if FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT
    kUartIntLinBreakDetect  = 0U << UART_SHIFT | UART_BDH_LBKDIE_SHIFT,  /*!< LIN break detect. */
#endif
    kUartIntRxActiveEdge    = 0U << UART_SHIFT | UART_BDH_RXEDGIE_SHIFT, /*!< Receive Active Edge. */
    kUartIntTxDataRegEmpty  = 1U << UART_SHIFT | UART_C2_TIE_SHIFT,      /*!< Transmit data register empty. */
    kUartIntTxComplete      = 1U << UART_SHIFT | UART_C2_TCIE_SHIFT,     /*!< Transmission complete. */
    kUartIntRxDataRegFull   = 1U << UART_SHIFT | UART_C2_RIE_SHIFT,      /*!< Receiver data register full. */
    kUartIntIdleLine        = 1U << UART_SHIFT | UART_C2_ILIE_SHIFT,     /*!< Idle line. */
    kUartIntRxOverrun       = 2U << UART_SHIFT | UART_C3_ORIE_SHIFT,     /*!< Receiver Overrun. */
    kUartIntNoiseErrFlag    = 2U << UART_SHIFT | UART_C3_NEIE_SHIFT,     /*!< Noise error flag. */
    kUartIntFrameErrFlag    = 2U << UART_SHIFT | UART_C3_FEIE_SHIFT,     /*!< Framing error flag. */
    kUartIntParityErrFlag   = 2U << UART_SHIFT | UART_C3_PEIE_SHIFT,     /*!< Parity error flag. */
#if FSL_FEATURE_UART_HAS_FIFO
    kUartIntTxFifoOverflow  = 3U << UART_SHIFT | UART_CFIFO_TXOFE_SHIFT, /*!< Transmit FIFO Overflow. */
    kUartIntRxFifoUnderflow = 3U << UART_SHIFT | UART_CFIFO_RXUFE_SHIFT, /*!< Receive FIFO Underflow. */
#endif
} uart_interrupt_t;

/*!
 * @brief UART ISO7816-specific interrupt configuration.
 *
 * This enumeration contains the settings for all of the UART ISO7816 feature-specific interrupt configurations.
 */
typedef enum _uart_iso7816_interrupt {
    kUartIntIso7816RxThreasholdExceeded = 0U,   /*!< Receive Threshold Exceeded. */
    kUartIntIso7816TxThresholdExceeded  = 1U,   /*!< TransmitThresholdExceeded. */
    kUartIntIso7816GuardTimerViolated   = 2U,   /*!< Guard Timer Violated. */
    kUartIntIso7816AtrDurationTimer     = 3U,   /*!< ATR Duration Timer. */
    kUartIntIso7816InitialCharDetected  = 4U,   /*!< Initial Character Detected. */
    kUartIntIso7816BlockWaitTimer       = 5U,   /*!< Block Wait Timer. */
    kUartIntIso7816CharWaitTimer        = 6U,   /*!< Character Wait Timer. */
    kUartIntIso7816WaitTimer            = 7U,   /*!< Wait Timer. */
    kUartIntIso7816All                  = 8U,   /*<!All above. */
} uart_iso7816_interrupt_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name UART Common Configurations
 * @{
 */

/*!
 * @brief Initializes the UART controller.
 *
 * This function initializes the module to a known state.
 *
 * @param   base UART module base pointer.
 */
void UART_HAL_Init(UART_Type * base);

/*!
 * @brief Enables the UART transmitter.
 *
 * This function allows the user to enable the UART transmitter.
 *
 * @param   base UART module base pointer.
 */
static inline void UART_HAL_EnableTransmitter(UART_Type * base)
{
    UART_BWR_C2_TE(base, 1U);
}

/*!
 * @brief Disables the UART transmitter.
 *
 * This function allows the user to disable the UART transmitter.
 *
 * @param   base UART module base pointer.
 */
static inline void UART_HAL_DisableTransmitter(UART_Type * base)
{
    UART_BWR_C2_TE(base, 0U);
}

/*!
 * @brief Gets the UART transmitter enabled/disabled configuration setting.
 *
 * This function allows the user to get the setting of the UART transmitter.
 *
 * @param   base UART module base pointer.
 * @return The state of UART transmitter enable(true)/disable(false) setting.
 */
static inline bool UART_HAL_IsTransmitterEnabled(UART_Type * base)
{
    return (bool)UART_BRD_C2_TE(base);
}

/*!
 * @brief Enables the UART receiver.
 *
 *  This function allows the user to enable the UART receiver.
 *
 * @param   base UART module base pointer.
 */
static inline void UART_HAL_EnableReceiver(UART_Type * base)
{
    UART_BWR_C2_RE(base, 1U);
}

/*!
 * @brief Disables the UART receiver.
 *
 *  This function allows the user to disable the UART receiver.
 *
 * @param   base UART module base pointer.
 */
static inline void UART_HAL_DisableReceiver(UART_Type * base)
{
    UART_BWR_C2_RE(base, 0U);
}

/*!
 * @brief Gets the UART receiver enabled/disabled configuration setting.
 *
 *  This function allows the user to get the setting of the UART receiver.
 *
 * @param   base UART module base pointer.
 * @return The state of UART receiver enable(true)/disable(false) setting.
 */
static inline bool UART_HAL_IsReceiverEnabled(UART_Type * base)
{
    return (bool)UART_BRD_C2_RE(base);
}

/*!
 * @brief Configures the UART baud rate.
 *
 * This function programs the UART baud rate to the desired value passed in by the user. The user
 * must also pass in the module source clock so that the function can calculate the baud
 * rate divisors to their appropriate values.
 * In some UART bases it is required that the transmitter/receiver be disabled
 * before calling this function.
 * Generally this is applied to all UARTs to ensure safe operation.
 *
 * @param   base UART module base pointer.
 * @param   sourceClockInHz UART source input clock in Hz.
 * @param   baudRate UART desired baud rate.
 * @return  An error code or kStatus_UART_Success
 */
uart_status_t UART_HAL_SetBaudRate(UART_Type * base, uint32_t sourceClockInHz, uint32_t baudRate);

/*!
 * @brief Sets the UART baud rate modulo divisor value.
 *
 * This function allows the user to program the baud rate divisor directly in situations
 * where the divisor value is known. In this case, the user may not want to call the
 * UART_HAL_SetBaudRate() function, because the divisor is already known.
 *
 * @param   base UART module base pointer.
 * @param   baudRateDivisor The baud rate modulo division "SBR" value.
 */
void UART_HAL_SetBaudRateDivisor(UART_Type * base, uint16_t baudRateDivisor);

#if FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT
/*!
 * @brief Sets the UART baud rate fine adjust. (Note: Feature available on select
 *        UART bases used in conjunction with baud rate programming)
 *
 * This function, which programs the baud rate fine adjust, is used together with
 * programming the baud rate modulo divisor in situations where these divisors value are known.
 * In this case, the user may not want to call the UART_HAL_SetBaudRate() function, as the
 * divisors are already known.
 *
 * @param   base UART module base pointer.
 * @param   baudFineAdjust Value of 5-bit field used to add more timing resolution to average
 *                          baud rate frequency is 1/32 increments.
 */
static inline void UART_HAL_SetBaudRateFineAdjust(UART_Type * base, uint8_t baudFineAdjust)
{
    assert(baudFineAdjust < 0x1F);
    UART_BWR_C4_BRFA(base, baudFineAdjust);
}
#endif

/*!
 * @brief Configures the number of bits per character in the UART controller.
 *
 * This function allows the user to configure the number of bits per character according to the
 * typedef uart_bit_count_per_char_t.
 *
 * @param   base UART module base pointer.
 * @param   bitCountPerChar Number of bits per char (8, 9, or 10, depending on the UART base).
 */
static inline void UART_HAL_SetBitCountPerChar(UART_Type * base,
                                          uart_bit_count_per_char_t bitCountPerChar)
{
    /* config 8- (M=0) or 9-bits (M=1) */
    UART_BWR_C1_M(base, bitCountPerChar);
}

/*!
 * @brief Configures the parity mode in the UART controller.
 *
 * This function allows the user to configure the parity mode of the UART controller to disable
 * it or enable it for even parity or for odd parity.
 *
 * @param   base UART module base pointer.
 * @param   parityMode Parity mode setting (enabled, disable, odd, even - see
 *          parity_mode_t struct).
 */
void UART_HAL_SetParityMode(UART_Type * base, uart_parity_mode_t parityMode);

#if FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
/*!
 * @brief Configures the number of stop bits in the UART controller.
 *
 * This function allows the user to configure the number of stop bits in the UART controller
 * to be one or two stop bits.
 *
 * @param   base UART module base pointer.
 * @param   stopBitCount Number of stop bits setting (1 or 2 - see uart_stop_bit_count_t struct).
 * @return  An error code (an unsupported setting in some UARTs) or kStatus_UART_Success.
 */
static inline void UART_HAL_SetStopBitCount(UART_Type * base, uart_stop_bit_count_t stopBitCount)
{
    UART_BWR_BDH_SBNS(base, stopBitCount);
}
#endif

/*!
 * @brief  Get UART transmit/receive data register address.
 *
 * @param   base UART module base pointer.
 * @return  UART transmit/receive data register address.
 */
static inline uint32_t UART_HAL_GetDataRegAddr(UART_Type * base)
{
    return (uint32_t)(&UART_D_REG(base));
}

/*@}*/

/*!
 * @name UART Interrupts and DMA
 * @{
 */

/*!
 * @brief Configures the UART module interrupts to enable/disable various interrupt sources.
 *
 * @param   base UART module base pointer.
 * @param   interrupt UART interrupt configuration data.
 * @param   enable   true: enable, false: disable.
 */
void UART_HAL_SetIntMode(UART_Type * base, uart_interrupt_t interrupt, bool enable);

/*!
 * @brief Returns whether the UART module interrupts is enabled/disabled.
 *
 * @param   base UART module base pointer.
 * @param   interrupt UART interrupt configuration data.
 * @return  true: enable, false: disable.
 */
bool UART_HAL_GetIntMode(UART_Type * base, uart_interrupt_t interrupt);

#if FSL_FEATURE_UART_HAS_DMA_SELECT
/*!
 * @brief  Enables or disables the UART DMA request for Transmitter.
 *
 * This function allows the user to configure the receive data register full
 * flag to generate a DMA request.
 *
 * @param   base UART module base pointer.
 * @param   enable Transmit DMA request configuration setting (enable: true /disable: false).
 */
void UART_HAL_SetTxDmaCmd(UART_Type * base, bool enable);

/*!
 * @brief  Gets the UART Transmit DMA request configuration setting.
 *
 * This function returns the configuration setting of the Transmit DMA request.
 *
 * @param   base UART module base pointer.
 * @return  Transmit DMA request configuration setting (enable: true /disable: false).
 */
static inline bool UART_HAL_GetTxDmaCmd(UART_Type * base)
{
    return (!UART_BRD_C2_TCIE(base))
#if FSL_FEATURE_UART_IS_SCI
            && UART_BRD_C4_TDMAS(base)
#else
            && UART_BRD_C5_TDMAS(base)
#endif
            && UART_BRD_C2_TIE(base);
}

/*!
 * @brief  Enables or disables UART DMA request for Receiver.
 *
 * This function allows the user to configure the receive data register full
 * flag to generate a DMA request.
 *
 * @param   base UART module base pointer.
 * @param   enable Receive DMA request configuration setting (enable: true/disable: false).
 */
void UART_HAL_SetRxDmaCmd(UART_Type * base, bool enable);

/*!
 * @brief  Gets the UART Receive DMA request configuration setting.
 *
 * This function returns the configuration setting of the Receive DMA request.
 *
 * @param   base UART module base pointer.
 * @return  Receive DMA request configuration setting (enable: true /disable: false).
 */
static inline bool UART_HAL_GetRxDmaCmd(UART_Type * base)
{
    return UART_BRD_C2_RIE(base)
#if FSL_FEATURE_UART_IS_SCI
           && UART_BRD_C4_RDMAS(base);
#else
           && UART_BRD_C5_RDMAS(base);
#endif
}

#endif /* FSL_FEATURE_UART_HAS_DMA_SELECT */

/*@}*/

/*!
 * @name UART Transfer Functions
 * @{
 */

/*!
 * @brief This function allows the user to send an 8-bit character from the UART data register.
 *
 * @param   base UART module base pointer.
 * @param   data The data to send of size 8-bit.
 */
void UART_HAL_Putchar(UART_Type * base, uint8_t data);

/*!
 * @brief This function allows the user to send a 9-bit character from the UART data register.
 *
 * @param   base UART module base pointer.
 * @param   data The data to send of size 9-bit.
 */
void UART_HAL_Putchar9(UART_Type * base, uint16_t data);

/*!
 * @brief This function gets a received 8-bit character from the UART data register.
 *
 * @param   base UART module base pointer.
 * @param   readData The received data read from data register of size 8-bit.
 */
void  UART_HAL_Getchar(UART_Type * base, uint8_t *readData);

/*!
 * @brief This function gets a received 9-bit character from the UART data register.
 *
 * @param   base UART module base pointer.
 * @param   readData The received data read from data register of size 9-bit.
 */
void  UART_HAL_Getchar9(UART_Type * base, uint16_t *readData);

/*!
 * @brief Sends out multiple bytes of data using polling method.
 *
 * This function only supports 8-bit transaction.
 *
 * @param   base UART module base pointer.
 * @param   txBuff The buffer pointer which saves the data to be sent.
 * @param   txSize Size of data to be sent in unit of byte.
 */
void UART_HAL_SendDataPolling(UART_Type * base, const uint8_t *txBuff, uint32_t txSize);

/*!
 * @brief Receives multiple bytes of data using polling method.
 *
 * This function only supports 8-bit transaction.
 *
 * @param   base UART module base pointer.
 * @param   rxBuff The buffer pointer which saves the data to be received.
 * @param   rxSize Size of data need to be received in unit of byte.
 * @return  Whether the transaction is success or rx overrun.
 */
uart_status_t UART_HAL_ReceiveDataPolling(UART_Type * base, uint8_t *rxBuff, uint32_t rxSize);

#if FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS
/*!
 * @brief  Configures the UART bit 10 (if enabled) or bit 9 (if disabled) as the parity bit in the
 *         serial transmission.
 *
 * This function configures bit 10 or bit 9 to be the parity bit.  To configure bit 10 as the parity
 * bit, the function sets UARTx_C4[M10]; it also sets UARTx_C1[M] and UARTx_C1[PE] as required.
 *
 * @param  base UART module base pointer.
 * @param  enable The setting to enable (true), which configures bit 10 as the parity bit or to
 *                disable (false), which configures bit 9 as the parity bit in the serial
 *                transmission.
 */
static inline void UART_HAL_SetBit10AsParityBit(UART_Type * base, bool enable)
{
    /* to enable the parity bit as the tenth data bit, along with enabling UARTx_C4[M10]
     * need to also enable parity and set UARTx_C1[M] bit
     * assumed that the user has already set the appropriate bits */
    UART_BWR_C4_M10(base, enable);
}

/*!
 * @brief  Gets the configuration of the UART bit 10 (if enabled) or bit 9 (if disabled) as the
 *         parity bit in the serial transmission.
 *
 * This function returns true if bit 10 is configured as the parity bit, otherwise it returns
 * false if bit 9 is configured as the parity bit.
 *
 * @param   base UART module base pointer.
 * @return  The configuration setting of bit 10 (true), or bit 9 (false) as the
 *          parity bit in the serial transmission.
 */
static inline bool UART_HAL_IsBit10SetAsParityBit(UART_Type * base)
{
    return UART_BRD_C4_M10(base);
}

/*!
 * @brief  Determines whether the UART received data word was received with noise.
 *
 * This function returns true if the received data word was received with noise. Otherwise,
 * it returns false indicating no noise was detected.
 *
 * @param   base UART module base pointer.
 * @return  The status of the NOISY bit in the UART extended data register.
 */
static inline bool UART_HAL_IsCurrentDataWithNoise(UART_Type * base)
{
    return UART_BRD_ED_NOISY(base);
}

/*!
 * @brief  Determines whether the UART received data word was received with a parity error.
 *
 * This function returns true if the received data word was received with a parity error.
 * Otherwise, it returns false indicating no parity error was detected.
 *
 * @param   base UART module base pointer.
 * @return  The status of the PARITYE (parity error) bit in the UART extended data register.
 */
static inline bool UART_HAL_IsCurrentDataWithParityError(UART_Type * base)
{
    return UART_BRD_ED_PARITYE(base);
}

#endif  /* FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS*/

/*@}*/

/*!
 * @name UART Status Flags
 * @{
 */

/*!
 * @brief  Gets all  UART status flag states.
 *
 * @param   base UART module base pointer.
 * @param   statusFlag Status flag name.
 * @return  Whether the current status flag is set(true) or not(false).
 */
bool UART_HAL_GetStatusFlag(UART_Type * base, uart_status_flag_t statusFlag);

/*!
 * @brief  Clears an individual and specific UART status flag.
 *
 * This function allows the user to clear an individual and specific UART status flag. Refer to
 * structure definition uart_status_flag_t for list of status bits.
 *
 * @param base UART module base pointer.
 * @param statusFlag The desired UART status flag to clear.
 * @return An error code or kStatus_UART_Success.
 */
uart_status_t UART_HAL_ClearStatusFlag(UART_Type * base, uart_status_flag_t statusFlag);

/*@}*/

/*!
 * @name UART FIFO Configurations
 * @{
 */

#if FSL_FEATURE_UART_HAS_FIFO
/*!
 * @brief  Enables or disable the UART transmit FIFO.
 *
 * This function allows the user to enable or disable the UART transmit FIFO.
 * It is required that the transmitter/receiver be disabled before calling this function
 * when the FIFO is empty.
 * Additionally, TXFLUSH and RXFLUSH commands should be issued after calling this function.
 *
 * @param base UART module base pointer.
 * @param enable Enable or disable Tx FIFO.
 * @return Error code if it is detected that the transmitter or receiver is enabled or
 *         kStatus_UART_Success.
 */
uart_status_t UART_HAL_SetTxFifoCmd(UART_Type * base, bool enable);

/*!
 * @brief  Enables or disables the UART receive FIFO.
 *
 * This function allows the user to enable or disable the UART receive FIFO.
 * It is required that the transmitter/receiver be disabled before calling this function
 * when the FIFO is empty.
 * Additionally, TXFLUSH and RXFLUSH commands should be issued after calling this function.
 *
 * @param base UART module base pointer.
 * @param enable Enable or disable Rx FIFO.
 * @return Error code if it is detected that the transmitter or receiver is enabled or
 *         kStatus_UART_Success.
 */
uart_status_t UART_HAL_SetRxFifoCmd(UART_Type * base, bool enable);

/*!
 * @brief  Gets the size of the UART transmit FIFO.
 *
 * This function returns the size (number of entries) supported in the UART transmit FIFO for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @return  The UART transmit FIFO size as follows:
 *    0x0: 1 data word; 0x1: 4 data words; 0x2: 8 data words; 0x3: 16 data words
 *    0x4: 32 data words; 0x5: 64 data words; 0x6: 128 data words; 0x7: reserved
 */
static inline uint8_t UART_HAL_GetTxFifoSize(UART_Type * base)
{
    return UART_BRD_PFIFO_TXFIFOSIZE(base);
}

/*!
 * @brief  Gets the size of the UART receive FIFO.
 *
 * This function returns the size (number of entries) supported in the UART receive FIFO for
 * a particular module base.
 *
 * @param   base UART module base pointer.
 * @return  The receive FIFO size as follows:
 *    0x0: 1 data word; 0x1: 4 data words; 0x2: 8 data words; 0x3: 16 data words
 *    0x4: 32 data words; 0x5: 64 data words; 0x6: 128 data words; 0x7: reserved
 */
static inline uint8_t UART_HAL_GetRxFifoSize(UART_Type * base)
{
    return UART_BRD_PFIFO_RXFIFOSIZE(base);
}

/*!
 * @brief  Flushes the UART transmit FIFO.
 *
 * This function allows the user to flush the UART transmit FIFO for a particular module base.
 * Flushing the FIFO may result in data loss.
 * It is recommended that the transmitter be disabled before calling this function.
 *
 * @param base UART module base pointer.
 * @return Error code if it is detected that the transmitter or receiver is enabled or
 *         kStatus_UART_Success.
 */
uart_status_t UART_HAL_FlushTxFifo(UART_Type * base);

/*!
 * @brief  Flushes the UART receive FIFO.
 *
 * This function allows the user to flush the UART receive FIFO for a particular module base.
 * Flushing the FIFO may result in data loss.
 * It is recommended that the receiver be disabled before calling this function.
 *
 * @param base UART module base pointer.
 * @return Error code if it is detected that the transmitter or receiver is enabled or
 *         kStatus_UART_Success.
 */
uart_status_t UART_HAL_FlushRxFifo(UART_Type * base);

/*!
 * @brief  Gets the UART transmit FIFO empty status state.
 *
 * The function returns the state of the transmit FIFO empty status state, but does not take into
 * account data in the shift register.
 *
 * @param   base UART module base pointer.
 * @return  The UART transmit FIFO empty status: true=empty; false=not-empty.
 */
static inline bool UART_HAL_IsTxFifoEmpty(UART_Type * base)
{
    return UART_BRD_SFIFO_TXEMPT(base);
}

/*!
 * @brief  Gets the UART receive FIFO empty status state.
 *
 * The function returns the state of the receive FIFO empty status state, but does not take into
 * account data in the shift register.
 *
 * @param   base UART module base pointer.
 * @return  The UART receive FIFO empty status: true=empty; false=not-empty.
 */
static inline bool UART_HAL_IsRxFifoEmpty(UART_Type * base)
{
    return UART_BRD_SFIFO_RXEMPT(base);
}

/*!
 * @brief  Sets the UART transmit FIFO watermark value.
 *
 * Programming the transmit watermark should be done when UART the transmitter is disabled
 * and the value must be set less than the size obtained from UART_HAL_GetTxFifoSize.
 *
 * @param   base UART module base pointer.
 * @param   watermark  The UART transmit watermark value to be programmed.
 * @return  Error code if transmitter is enabled or kStatus_UART_Success.
 */
uart_status_t UART_HAL_SetTxFifoWatermark(UART_Type * base, uint8_t watermark);

/*!
 * @brief  Gets the UART transmit FIFO watermark value.
 *
 * @param   base UART module base pointer.
 * @return  The value currently programmed for the UART transmit watermark.
 */
static inline uint8_t UART_HAL_GetTxFifoWatermark(UART_Type * base)
{
    return UART_RD_TWFIFO(base);
}

/*!
 * @brief  Gets the UART transmit FIFO data word count (number of words in the transmit FIFO).
 *
 * The function UART_HAL_GetTxDatawordCountInFifo excludes any data that may
 * be in the UART transmit shift register
 *
 * @param   base UART module base pointer.
 * @return  The number of data words currently in the UART transmit FIFO.
 */
static inline uint8_t UART_HAL_GetTxDatawordCountInFifo(UART_Type * base)
{
    return UART_RD_TCFIFO(base);
}

/*!
 * @brief  Sets the UART receive FIFO watermark value.
 *
 * Programming the receive watermark should be done when the receiver is disabled
 * and the value must be set less than the size obtained from UART_HAL_GetRxFifoSize and
 * greater than zero.
 *
 * @param   base UART module base pointer.
 * @param  watermark  The UART receive watermark value to be programmed.
 * @return  Error code if receiver is enabled or kStatus_UART_Success.
 */
uart_status_t UART_HAL_SetRxFifoWatermark(UART_Type * base, uint8_t watermark);

/*!
 * @brief  Gets the UART receive FIFO data word count (number of words in the receive FIFO).
 *
 * The function UART_HAL_GetRxDatawordCountInFifo excludes any data that may be
 * in the receive shift register.
 *
 * @param   base UART module base pointer.
 * @return  The number of data words currently in the UART receive FIFO.
 */
static inline uint8_t UART_HAL_GetRxDatawordCountInFifo(UART_Type * base)
{
    return UART_RD_RCFIFO(base);
}

/*!
 * @brief  Gets the UART receive FIFO watermark value.
 *
 * @param   base UART module base pointer.
 * @return  The value currently programmed for the UART receive watermark.
 */
static inline uint8_t UART_HAL_GetRxFifoWatermark(UART_Type * base)
{
    return UART_RD_RWFIFO(base);
}

#endif  /* FSL_FEATURE_UART_HAS_FIFO*/

/*!
 * @name UART Special Feature Configurations
 * @{
 */

#if FSL_FEATURE_UART_HAS_WAIT_MODE_OPERATION
/*!
 * @brief Configures the UART to either operate or cease to operate in WAIT mode.
 *
 * The function configures the UART to either operate or cease to operate when WAIT mode is
 * entered.
 *
 * @param   base UART module base pointer.
 * @param   mode The UART WAIT mode operation - operates or ceases to operate in WAIT mode.
 */
static inline void UART_HAL_SetWaitModeOperation(UART_Type * base, uart_operation_config_t mode)
{
	/*In CPU wait mode: 0 - uart is enabled; 1 - uart is disabled */
	UART_BWR_C1_UARTSWAI(base, mode);
}

/*!
 * @brief Determines if the UART operates or ceases to operate in WAIT mode.
 *
 * This function returns kUartOperates if the UART has been configured to operate in WAIT mode.
 * Else it returns KUartStops if the UART has been configured to cease-to-operate in WAIT mode.
 *
 * @param   base UART module base pointer.
 * @return The UART WAIT mode operation configuration, returns either kUartOperates or KUartStops.
 */
static inline uart_operation_config_t UART_HAL_GetWaitModeOperation(UART_Type * base)
{
    /*In CPU wait mode: 0 - uart is enabled; 1 - uart is disabled */
    return (uart_operation_config_t)UART_BRD_C1_UARTSWAI(base);
}
#endif /* FSL_FEATURE_UART_HAS_WAIT_MODE_OPERATION */

/*!
 * @brief Configures the UART loopback operation.
 *
 * This function enables or disables the UART loopback operation.
 *
 * @param base UART module base pointer.
 * @param enable The UART loopback mode configuration, either disabled (false) or enabled (true).
 */
static inline void UART_HAL_SetLoopCmd(UART_Type * base, bool enable)
{
    UART_BWR_C1_LOOPS(base, enable);
}

/*!
 * @brief Configures the UART single-wire operation.
 *
 * This function enables or disables the UART single-wire operation.
 * In some UART bases it is required that the transmitter/receiver be disabled
 * before calling this function.
 * This may be applied to all UARTs to ensure safe operation.
 *
 * @param base UART module base pointer.
 * @param source The UART single-wire mode configuration.
 */
static inline void UART_HAL_SetReceiverSource(UART_Type * base, uart_receiver_source_t source)
{
    UART_BWR_C1_RSRC(base, source);
}

/*!
 * @brief Configures the UART transmit direction while in single-wire mode.
 *
 * This function configures the transmitter direction when the UART is configured for single-wire
 * operation.
 *
 * @param   base UART module base pointer.
 * @param   direction The UART single-wire mode transmit direction configuration of type
 *                    uart_singlewire_txdir_t (either kUartSinglewireTxdirIn or
 *                    kUartSinglewireTxdirOut.
 */
static inline void UART_HAL_SetTransmitterDir(UART_Type * base, uart_singlewire_txdir_t direction)
{
    /* configure UART transmit direction (input or output) when in single-wire mode
     * it is assumed UART is in single-wire mode. */
    UART_BWR_C3_TXDIR(base, direction);
}

/*!
 * @brief  Places the UART receiver in standby mode.
 *
 * This function, when called, places the UART receiver into standby mode.
 * In some UART bases, there are conditions that must be met before placing Rx in standby mode.
 * Before placing UART in standby, determine if receiver is set to
 * wake on idle, and if receiver is already in idle state.
 * NOTE: RWU should only be set with C1[WAKE] = 0 (wakeup on idle) if the channel is currently
 * not idle.
 * This can be determined by the S2[RAF] flag. If set to wake up FROM an IDLE event and the channel
 * is already idle, it is possible that the UART discards data because data must be received
 * (or a LIN break detect) after an IDLE is detected before IDLE is allowed to be reasserted.
 *
 * @param base UART module base pointer.
 * @return Error code or kStatus_UART_Success.
 */
uart_status_t UART_HAL_PutReceiverInStandbyMode(UART_Type * base);

/*!
 * @brief  Places the UART receiver in normal mode (disable standby mode operation).
 *
 * This function, when called, places the UART receiver into normal mode and out of
 * standby mode.
 *
 * @param   base UART module base pointer.
 */
static inline void UART_HAL_PutReceiverInNormalMode(UART_Type * base)
{
    UART_CLR_C2(base, UART_C2_RWU_MASK);
}

/*!
 * @brief  Determines if the UART receiver is currently in standby mode.
 *
 * This function determines the state of the UART receiver. If it returns true, this means
 * that the UART receiver is in standby mode; if it returns false, the UART receiver
 * is in normal mode.
 *
 * @param   base UART module base pointer.
 * @return The UART receiver is in normal mode (false) or standby mode (true).
 */
static inline bool UART_HAL_IsReceiverInStandby(UART_Type * base)
{
    return UART_BRD_C2_RWU(base);
}

/*!
 * @brief  Selects the UART receiver wakeup method (idle-line or address-mark) from standby mode.
 *
 * This function configures the wakeup method of the UART receiver from standby mode.  The options
 * are idle-line wake or address-mark wake.
 *
 * @param   base UART module base pointer.
 * @param   method The UART receiver wakeup method options: kUartIdleLineWake - Idle-line wake or
 *                 kUartAddrMarkWake - address-mark wake.
 */
static inline void UART_HAL_SetReceiverWakeupMethod(UART_Type * base, uart_wakeup_method_t method)
{
    UART_BWR_C1_WAKE(base, method);
}

/*!
 * @brief  Gets the UART receiver wakeup method (idle-line or address-mark) from standby mode.
 *
 * This function returns how the UART receiver is configured to wake from standby mode. The
 * wake method options that can be returned are kUartIdleLineWake or kUartAddrMarkWake.
 *
 * @param   base UART module base pointer.
 * @return  The UART receiver wakeup from standby method, false: kUartIdleLineWake (idle-line wake)
 *          or true: kUartAddrMarkWake (address-mark wake).
 */
static inline uart_wakeup_method_t UART_HAL_GetReceiverWakeupMethod(UART_Type * base)
{
    return (uart_wakeup_method_t)UART_BRD_C1_WAKE(base);
}

/*!
 * @brief  Configures the operation options of the UART idle line detect.
 *
 * This function allows the user to configure the UART idle-line detect operation. There are two
 * separate operations for the user to configure, the idle line bit-count start and the receive
 * wake up affect on IDLE status bit. The user passes in a structure of type
 * uart_idle_line_config_t.
 *
 * @param   base UART module base pointer.
 * @param   idleLine Idle bit count start: 0 - after start bit (default), 1 - after stop bit
 * @param   rxWakeIdleDetect Receiver Wake Up Idle Detect. IDLE status bit operation during receive
 *          standby. Controls whether idle character that wakes up receiver also sets IDLE status
 *          bit. 0 - IDLE status bit doesn't get set (default), 1 - IDLE status bit gets set
 */
void UART_HAL_ConfigIdleLineDetect(UART_Type * base, uint8_t idleLine, uint8_t rxWakeIdleDetect);

/*!
 * @brief  Configures the UART break character transmit length.
 *
 * This function allows the user to configure the UART break character transmit length. Refer to
 * the typedef uart_break_char_length_t for setting options.
 * In some UART bases it is required that the transmitter be disabled before calling
 * this function. This may be applied to all UARTs to ensure safe operation.
 *
 * @param base UART module base pointer.
 * @param length The UART break character length setting of type uart_break_char_length_t, either a
 *               minimum 10-bit times or a minimum 13-bit times.
 */
static inline void UART_HAL_SetBreakCharTransmitLength(UART_Type * base,
                                                       uart_break_char_length_t length)
{
    /* Configure BRK13 - Break Character transmit length configuration
     * UART break character length setting:
     * 0 - minimum 10-bit times (default),
     * 1 - minimum 13-bit times */
    UART_BWR_S2_BRK13(base, length);
}

#if FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT
/*!
 * @brief  Configures the UART break character detect length.
 *
 * This function allows the user to configure the UART break character detect length. Refer to
 * the typedef uart_break_char_length_t for setting options.
 *
 * @param base UART module base pointer.
 * @param length The UART break character length setting of type uart_break_char_length_t, either a
 *               minimum 10-bit times or a minimum 13-bit times.
 */
static inline void UART_HAL_SetBreakCharDetectLength(UART_Type * base, uart_break_char_length_t length)
{
    /* Configure LBKDE - Break Character detect length configuration
     * UART break character length setting:
     * 0 - minimum 10-bit times (default),
     * 1 - minimum 13-bit times */
    UART_BWR_S2_LBKDE(base, length);
}
#endif /* FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT */

/*!
 * @brief  Configures the UART transmit send break character operation.
 *
 * This function allows the user to queue a UART break character to send.  If true is passed into
 * the function, then a break character is queued for transmission.  A break character is
 * continuously  queued until this function is called again when a false is passed into this
 * function.
 *
 * @param   base UART module base pointer.
 * @param   enable If false, the UART normal/queue break character setting is disabled, which
 *                 configures the UART for normal transmitter operation. If true, a break
 *                 character is queued for transmission.
 */
static inline void UART_HAL_SetBreakCharCmd(UART_Type * base, bool enable)
{
    UART_BWR_C2_SBK(base, enable);
}

/*!
 * @brief  Configures the UART match address mode control operation. (Note: Feature available on
 *         select UART bases)
 *
 * The function allows the user to configure the UART match address control operation. The user
 * has the option to enable the match address mode and to program the match address value. There
 * are two match address modes, each with its own enable and programmable match address value.
 *
 * @param  base UART module base pointer.
 * @param  matchAddrMode1 If true, this enables match address mode 1 (MAEN1), where false disables.
 * @param  matchAddrMode2 If true, this enables match address mode 2 (MAEN2), where false disables.
 * @param  matchAddrValue1 The match address value to program for match address mode 1.
 * @param  matchAddrValue2 The match address value to program for match address mode 2.
 */
void UART_HAL_SetMatchAddress(UART_Type * base, bool matchAddrMode1, bool matchAddrMode2,
                              uint8_t matchAddrValue1, uint8_t matchAddrValue2);

#if FSL_FEATURE_UART_HAS_BIT_ORDER_SELECT
/*!
 * @brief Configures the UART to send data MSB first
 * (Note: Feature available on select UART bases)
 *
 * The function allows the user to configure the UART to send data MSB first or LSB first.
 * In some UART bases it is required that the transmitter/receiver be disabled
 * before calling this function.
 * This may be applied to all UARTs to ensure safe operation.
 *
 * @param   base UART module base pointer.
 * @param   enable This configures send MSB first mode configuration. If true, the data is sent MSB
 *                 first; if false, it is sent LSB first.
 */
static inline void UART_HAL_SetSendMsbFirstCmd(UART_Type * base, bool enable)
{
    UART_BWR_S2_MSBF(base, enable);
}
#endif

#if FSL_FEATURE_UART_HAS_MODEM_SUPPORT
/*!
 * @brief  Enables the UART receiver request-to-send functionality.
 *
 * This function allows the user to enable the UART receiver request-to-send (RTS) functionality.
 * By enabling, it allows the RTS output to control the CTS input of the transmitting device to
 * prevent receiver overrun. RTS is deasserted if the number of characters in the receiver data
 * register (FIFO) is equal to or greater than RWFIFO[RXWATER]. RTS is asserted when the
 * number of characters in the receiver data register (FIFO) is less than RWFIFO[RXWATER].
 * Do not set both RXRTSE and TXRTSE.
 *
 * @param   base UART module base pointer.
 * @param   enable   Enable or disable receiver rts.
 */
static inline void UART_HAL_SetReceiverRtsCmd(UART_Type * base, bool enable)
{
    UART_BWR_MODEM_RXRTSE(base, enable);
}

/*!
 * @brief  Enables the UART transmitter request-to-send functionality.
 *
 * This function allows the user to enable the UART transmitter request-to-send (RTS) functionality.
 * When enabled, it allows the UART to control the RTS assertion before and after a transmission
 * such that when a character is placed into an empty transmitter data buffer, RTS
 * asserts one bit time before the start bit is transmitted. RTS deasserts one bit time after all
 * characters in the transmitter data buffer and shift register are completely sent, including
 * the last stop bit.
 *
 * @param   base UART module base pointer.
 * @param   enable   Enable or disable transmitter RTS.
 */
static inline void UART_HAL_SetTransmitterRtsCmd(UART_Type * base, bool enable)
{
    UART_BWR_MODEM_TXRTSE(base, enable);
}

/*!
 * @brief  Configures the UART transmitter RTS polarity.
 *
 * This function allows the user configure the transmitter RTS polarity to be either active low
 * or active high.
 *
 * @param base UART module base pointer.
 * @param polarity The UART transmitter RTS polarity setting (false - active low,
 *                 true - active high).
 */
static inline void UART_HAL_SetTransmitterRtsPolarityMode(UART_Type * base, bool polarity)
{
    UART_BWR_MODEM_TXRTSPOL(base, polarity);
}

/*!
 * @brief  Enables the UART transmitter clear-to-send functionality.
 *
 * This function allows the user to enable the UART transmitter clear-to-send (CTS) functionality.
 * When enabled, the transmitter checks the state of CTS each time it is ready to send a character.
 * If CTS is asserted, the character is sent. If CTS is deasserted, the signal TXD remains in
 * the mark state and transmission is delayed until CTS is asserted. Changes in CTS as a
 * character is being sent do not affect its transmission.
 *
 * @param   base UART module base pointer.
 * @param   enable   Enable or disable transmitter CTS.
 */
static inline void UART_HAL_SetTransmitterCtsCmd(UART_Type * base, bool enable)
{
    UART_BWR_MODEM_TXCTSE(base, enable);
}

#endif  /* FSL_FEATURE_UART_HAS_MODEM_SUPPORT*/

#if FSL_FEATURE_UART_HAS_IR_SUPPORT
/*!
 * @brief  Configures the UART infrared operation.
 *
 * The function allows the user to enable or disable the UART infrared (IR) operation
 * and to configure the IR pulse width.
 *
 * @param   base UART module base pointer.
 * @param   enable Enable (true) or disable (false) the infrared operation.
 * @param   pulseWidth The UART transmit narrow pulse width setting of type uart_ir_tx_pulsewidth_t.
 */
void UART_HAL_SetInfraredOperation(UART_Type * base, bool enable,
                                   uart_ir_tx_pulsewidth_t pulseWidth);
#endif  /* FSL_FEATURE_UART_HAS_IR_SUPPORT*/

/*@}*/

/*!
 * @name UART ISO7816 Configurations
 * @{
 */

#if FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT
/*!
 * @brief  Enables UART ISO7816 feature.
 *
 * This function enables the ISO7816 feature in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 */
static inline void UART_HAL_EnableISO7816(UART_Type * base)
{
    UART_BWR_C7816_ISO_7816E(base, 1U);
}

/*!
 * @brief  Disables UART ISO7816 feature.
 *
 * This function disables the ISO7816 feature in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 */
static inline void UART_HAL_DisableISO7816(UART_Type * base)
{
    UART_BWR_C7816_ISO_7816E(base, 0U);
}

/*!
 * @brief Gets the UART module ISO7816 feature enabled/disabled configuration setting.
 *
 * This function allows the user to get the setting of the UART ISO7816 feature settings.
 *
 * @param   base UART module base pointer.
 * @return The state of UART module ISO7816 feature enable(true)/disable(false) setting.
 */
static inline bool UART_HAL_IsISO7816Enabled(UART_Type * base)
{
    return (bool)UART_BRD_C7816_ISO_7816E(base);
}

/*!
 * @brief  Enables/disables UART ISO7816 module ONACK generation feature.
 *
 * This function enables/disables the ONACK generation in ISO7816 module in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param onack = kUartIso7816OnackEnable to enable ONACK generation,
 *              = kUartIso7816Onackdisable to disable ONACK generation
 */
static inline void UART_HAL_ConfigureNackOnOverflow(UART_Type * base, uart_iso7816_onack_config_t onack)
{
    UART_BWR_C7816_ONACK(base, onack);
}

/*!
 * @brief Gets the UART module ISO7816 module ONACK generation feature enabled/disabled configuration
 * setting.
 *
 * This function allows the user to get the setting of the UART ISO7816 ONACK generaton feature settings.
 *
 * @param   base UART module base pointer.
 * @return The state of UART module ISO7816 ONACK feature enable(true)/disable(false) setting.
 */
static inline bool UART_HAL_Is6NackOnOverflowEnabled(UART_Type * base)
{
    return (bool)UART_BRD_C7816_ONACK(base);
}

/*!
 * @brief  Enables/disables UART ISO7816 module ANACK generation feature.
 *
 * This function enables the ANACK generation in ISO7816 module in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param anack = kUartIso7816AnackEnable to enable ANACK generation,
 *              = kUartIso7816AnackDisable to disable ANACK generation
 */
static inline void UART_HAL_ConfigureNackOnError(UART_Type * base, uart_iso7816_anack_config_t anack)
{
    UART_BWR_C7816_ANACK(base, anack);
}

/*!
 * @brief Gets the UART module ISO7816 module ANACK generation feature enabled/disabled configuration
 * setting.
 *
 * This function allows the user to get the setting of the UART ISO7816 ONACK generaton feature settings.
 *
 * @param   base UART module base pointer.
 * @return The state of UART module ISO7816 ANACK feature enable(true)/disable(false) setting.
 */
static inline bool UART_HAL_Is6NackOnOnErrorEnabled(UART_Type * base)
{
    return (bool)UART_BRD_C7816_ANACK(base);
}

/*!
 * @brief  Enables/Disables UART ISO7816 module initial character detection feature.
 *
 * This function enables/disables the initial character detection in ISO7816 module in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param initd = kUartIso7816InitdEnable, to enable initial character detection,
 *              = kUartIso7816InitdDisable, to disable initial character detection,
 */
static inline void UART_HAL_ConfigureInitialCharacterDetection(UART_Type * base, uart_iso7816_initd_config_t initd)
{
    UART_BWR_C7816_INIT(base, initd);
}

/*!
 * @brief Gets the UART module ISO7816 module initial character detection feature enabled/disabled
 * configuration setting.
 *
 * This function allows the user to get the setting of the UART ISO7816 initial character detection
 * feature settings.
 *
 * @param   base UART module base pointer.
 * @return The state of UART module ISO7816 initial character detection feature enable(true)/disable(false)
 * setting.
 *
 */
static inline bool UART_HAL_IsInitialCharacterDetectionEnabled(UART_Type * base)
{
    return (bool)UART_BRD_C7816_INIT(base);
}

/*!
 * @brief  Sets transfer protocol type for UART ISO7816 module.
 *
 * This function sets the transfer protocol type in ISO7816 module in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param transferType Transfer protocol type = kUartIso7816TransfertType0 or, kUartIso7816TransfertType1.
 */
static inline void UART_HAL_SetTransferProtocolType(UART_Type * base, uart_iso7816_transfer_protocoltype_t transferType)
{
    UART_BWR_C7816_TTYPE(base, transferType);
}

/*!
 * @brief  Gets transfer protocol type for UART ISO7816 module.
 *
 * This function gets the transfer protocol type in ISO7816 module in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @return The current settings of transfer Transfer protocol type.
 */
static inline uart_iso7816_transfer_protocoltype_t UART_HAL_GetTransferProtocolType(UART_Type * base)
{
    return (uart_iso7816_transfer_protocoltype_t)UART_BRD_C7816_TTYPE(base);
}

/*!
 * @brief Configures the UART module ISO7816 feature-specific interrupts to
 * enable/disable various interrupt sources.
 *
 * @param   base UART module base pointer.
 * @param   interrupt UART ISO7816 feature-specific interrupt configuration data.
 * @param   enable   true: enable, false: disable.
 */
void UART_HAL_SetISO7816IntMode(UART_Type * base, uart_iso7816_interrupt_t interrupt, bool enable);

/*!
 * @brief Returns whether the UART module ISO7816 feature-specific interrupts
 * is enabled/disabled.
 *
 * @param   base UART module base pointer.
 * @param   interrupt UART ISO7816 feature-specific interrupt configuration data.
 * @return  true: enable, false: disable.
 */
bool UART_HAL_GetISO7816IntMode(UART_Type * base, uart_iso7816_interrupt_t interrupt);

/*!
 * @brief Clears the UART module ISO7816 feature-specific interrupts status bits
 *
 * @param   base UART module base pointer.
 * @param   interrupt UART ISO7816 feature-specific interrupt configuration data.
 */
void UART_HAL_ClearISO7816InterruptStatus(UART_Type * base, uart_iso7816_interrupt_t interrupt);

/*!
 * @brief Returns whether the UART module ISO7816 feature-specific interrupt status
 * has been set or not.
 *
 * @param   base UART module base pointer.
 * @param   interrupt UART ISO7816 feature-specific interrupt configuration data.
 * @return  true, false.
 */
bool UART_HAL_GetISO7816InterruptStatus(UART_Type * base, uart_iso7816_interrupt_t interrupt);

/*!
 * @brief Sets the basic elementary Time Unit of UART instance in ISO7816 mode.
 *
 * @param   base UART module base pointer.
 * @param   sourceClockInHz Module source clock in Hz.
 * @param   sCClock Smart card clock in Hz.
 * @param   Fi Smart card frequency multiplier.
 * @param   Di Smart card baud rate divider.
 * @returns kStatus_UART_BaudRateCalculationError or kStatus_UART_Success
 */
uart_status_t UART_HAL_SetISO7816Etu(UART_Type * base, uint32_t sourceClockInHz, uint32_t sCClock, uint16_t Fi, uint8_t Di);

/*!
 * @brief Resets UART ISO7816-specific Wait Timer
 *
 * @param   base UART module base pointer.
 */
void UART_HAL_ResetISO7816WaitTimer(UART_Type * base);

/*!
 * @brief Resets UART ISO7816-specific Character Wait Timer
 *
 * @param   base UART module base pointer.
 */
void UART_HAL_ResetISO7816CharacterWaitTimer(UART_Type * base);

/*!
 * @brief Resets UART ISO7816-specific Block Wait Timer
 *
 * @param   base UART module base pointer.
 */
void UART_HAL_ResetISO7816BlockWaitTimer(UART_Type * base);

#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
/*!
 * @brief  Sets a value to Wait Time Multiplier.
 *
 * This function sets a value to the Wait Timer Multiplier in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param wtx value to set to UART module Wait Time Multiplier.
 */
static inline void UART_HAL_SetWaitTimeMultipllier(UART_Type * base, uint8_t wtx)
{
    UART_WR_WP7816(base, wtx);
}

/*!
 * @brief  Gets the current value of Wait Time Multiplier.
 *
 * This function gets the current value of the Wait Timer Multiplier in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @return current value of the UART module Wait Time Multiplier.
 */
static inline uint8_t UART_HAL_GetWaitTimeMultipllier(UART_Type * base)
{
    return UART_RD_WP7816(base);
}

/*!
 * @brief Resets UART ISO7816-specific Block Wait Timer
 *
 * @param base UART module base pointer.
 * @param mWtx Wait time multiplier.
 */
void UART_HAL_ResetWaitTimeMultipllier(UART_Type * base, uint8_t mWtx);
#endif

/*!
 * @brief  Sets a value to Guard Band Integer.
 *
 * This function sets a value to the Guard Band Integer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param gtn value to set to UART module Guard Band Integer.
 */
static inline void UART_HAL_SetGuardBandInteger(UART_Type * base, uint8_t gtn)
{
    UART_WR_WN7816(base, gtn);
}

/*!
 * @brief  Gets the current value of Guard Band Integer.
 *
 * This function gets the current value of the Guard Band Integer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @return Guard Band Integer value.
 */
static inline uint8_t UART_HAL_GetGuardBandInteger(UART_Type * base)
{
    return UART_RD_WN7816(base);
}

/*!
 * @brief  Sets a value to FD Multiplier.
 *
 * This function sets a value to the FD Multiplier in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param gtfd value to set to UART module Guard Band Integer.
 */
static inline void UART_HAL_SetFDMultiplier(UART_Type * base, uint8_t gtfd)
{
    UART_WR_WF7816(base, gtfd);
}

/*!
 * @brief  Gets the current value of FD Multiplier.
 *
 * This function gets the current value of the FD Multiplier in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @return current value of the UART module FD Multiplier.
 */
static inline uint8_t UART_HAL_GetFDMultiplier(UART_Type * base)
{
    return UART_RD_WF7816(base);
}

/*!
 * @brief  Sets a value to Transmit NACK Threshold.
 *
 * This function sets a value to the Transmit NACK Threshold in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param txThreshold value to set to UART module Transmit NACK Threshold.
 */
static inline void UART_HAL_SetTxNACKThreshold(UART_Type * base, uint8_t txThreshold)
{
    UART_BWR_ET7816_TXTHRESHOLD(base, txThreshold);
}

/*!
 * @brief  Gets the current value of Transmit NACK Threshold.
 *
 * This function gets the current value of the Transmit NACK Threshold in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @return current value of the UART module Transmit NACK Threshold.
 */
static inline uint8_t UART_HAL_GetTxNACKThreshold(UART_Type * base)
{
    return UART_BRD_ET7816_TXTHRESHOLD(base);
}

/*!
 * @brief  Sets a value to Receive NACK Threshold.
 *
 * This function sets a value to the Receive NACK Threshold in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param rxThreshold value to set to UART module Receive NACK Threshold.
 */
static inline void UART_HAL_SetRxNACKThreshold(UART_Type * base, uint8_t rxThreshold)
{
    UART_BWR_ET7816_RXTHRESHOLD(base, rxThreshold);
}

/*!
 * @brief  Gets the current value of Receive NACK Threshold.
 *
 * This function gets the current value of the Receive NACK Threshold in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @return current value of the UART module Receive NACK Threshold.
 */
static inline uint8_t UART_HAL_GetRxNACKThreshold(UART_Type * base)
{
    return UART_BRD_ET7816_RXTHRESHOLD(base);
}

/*!
 * @brief  Sets a value to Transmit Length in T=1 transfer protocol.
 *
 * This function sets a value to the Transmit Length field in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param tLen value to set to UART module Transmit Length field.
 */
static inline void UART_HAL_SetTLen(UART_Type * base, uint8_t tLen)
{
    UART_WR_TL7816(base, tLen);
}

/*!
 * @brief  Gets the current value of Transmit Length field .
 *
 * This function gets the current value of the Transmit Length field in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @return current value of the UART module Transmit Length field.
 */
static inline uint8_t UART_HAL_GetTLen(UART_Type * base)
{
    return UART_RD_TL7816(base);
}

#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
/*!
 * @brief  Sets a value to ATR Duration Timer.
 *
 * This function sets a value to the ATR Duration Timer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param atrDuration value to set to UART module ATR Duration Timer.
 */
static inline void UART_HAL_SetAtrDurationTimer(UART_Type * base, uint16_t atrDuration)
{
    UART_WR_AP7816A_T0(base, (uint8_t)(atrDuration >> 8));
    UART_WR_AP7816B_T0(base, (uint8_t)atrDuration);
}

/*!
 * @brief  Gets the current value of ATR Duration Timer.
 *
 * This function gets the current value of the ATR Duration Timer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @return current value of the UART module ATR Duration Timer.
 */
static inline uint16_t UART_HAL_GetAtrDurationTimer(UART_Type * base)
{
    return (uint16_t)((uint16_t)((uint16_t)UART_RD_AP7816A_T0(base) << 8) | UART_RD_AP7816B_T0(base));
}
#endif

#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
/*!
 * @brief  Sets a value to Work Wait Time Integer.
 *
 * This function sets a value to the Work Wait Time Integer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param wi value to set to UART module Work Wait Time Integer.
 */
static inline void UART_HAL_SetWorkWaitTimeInteger(UART_Type * base, uint16_t wi)
{
    UART_WR_WP7816A_T0(base, (uint8_t)(wi >> 8));
    UART_WR_WP7816B_T0(base, (uint8_t)wi);
}
#else
/*!
 * @brief  Sets a value to Work Wait Time Integer.
 *
 * This function sets a value to the Work Wait Time Integer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param wi value to set to UART module Work Wait Time Integer.
 */
static inline void UART_HAL_SetWorkWaitTimeInteger(UART_Type * base, uint8_t wi)
{
    UART_WR_WP7816T0(base, wi);
}
#endif

#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
/*!
 * @brief  Gets the current value of Work Wait Time Integer.
 *
 * This function gets the current value of the Work Wait Time Integer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @return current value of the UART module Work Wait Time Integer.
 */
static inline uint16_t UART_HAL_GetWorkWaitTimeInteger(UART_Type * base)
{
    return (uint16_t)(((uint16_t)(UART_RD_WP7816A_T0(base) >> 8)) | UART_RD_WP7816B_T0(base));
}
#else
/*!
 * @brief  Gets the current value of Work Wait Time Integer.
 *
 * This function gets the current value of the Work Wait Time Integer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @return current value of the UART module Work Wait Time Integer.
 */
static inline uint8_t UART_HAL_GetWorkWaitTimeInteger(UART_Type * base)
{
    return UART_RD_WP7816T0(base);
}
#endif

/*!
 * @brief  Sets a value to Character Wait Time Integer.
 *
 * This function sets a value to the Character Wait Time Integer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param cwi1 value used to set to UART module Character Wait Time.
 * @param cwi2 value used to set to UART module Character Wait Time.
 */
static inline void UART_HAL_SetCharacterWaitTimeInteger(UART_Type * base, uint8_t cwi1, uint8_t cwi2)
{
#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
    UART_BWR_WGP7816_T1_CWI1(base, cwi1);
    UART_BWR_WP7816C_T1_CWI2(base, cwi2);
#else
    UART_BWR_WP7816T1_CWI(base, (uint8_t)(cwi1 & 0xFU));
#endif
}

/*!
 * @brief  Gets the current value of Character Wait Time Integer.
 *
 * This function gets the current value of the Character Wait Time Integer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param ptrCwi1 pointer to hold return value of cwi1 parameter.
 * @param ptrCwi2 pointer to hold return value of cwi2 parameter.
 */
static inline void UART_HAL_GetCharacterWaitTimeInteger(UART_Type * base, uint8_t *ptrCwi1, uint8_t *ptrCwi2)
{
    assert(ptrCwi1 == NULL);
    assert(ptrCwi2 == NULL);

#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
    *ptrCwi1 = UART_BRD_WGP7816_T1_CWI1(base);
    *ptrCwi2 = UART_BRD_WP7816C_T1_CWI2(base);
#else
    *ptrCwi1 = UART_BRD_WP7816T1_CWI(base);
#endif
}

#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
/*!
 * @brief  Sets a value to Block Wait Time Integer.
 *
 * This function sets a value to the Block Wait Time Integer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param bwi value to set to UART module Block Wait Time Integer.
 */
static inline void UART_HAL_SetBlockWaitTimeInteger(UART_Type * base, uint16_t bwi)
{
    UART_WR_WP7816A_T1(base, (uint8_t)(bwi >> 8));
    UART_WR_WP7816B_T1(base, (uint8_t)bwi);
}
#else
/*!
 * @brief  Sets a value to Block Wait Time Integer.
 *
 * This function sets a value to the Block Wait Time Integer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param bwi value to set to UART module Block Wait Time Integer.
 */
static inline void UART_HAL_SetBlockWaitTimeInteger(UART_Type * base, uint8_t bwi)
{
    UART_WR_WP7816T1(base, (uint8_t)(bwi & 0xFU));
}
#endif

#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
/*!
 * @brief  Gets the current value of Block Wait Time Integer.
 *
 * This function gets the current value of the Block Wait Time Integer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @return current value of the UART module Block Wait Time Integer.
 */
static inline uint16_t UART_HAL_GetBlockWaitTimeInteger(UART_Type * base)
{
    return (uint16_t)((uint16_t)(UART_RD_WP7816A_T1(base) >> 8)| UART_RD_WP7816B_T1(base));
}
#else
/*!
 * @brief  Gets the current value of Block Wait Time Integer.
 *
 * This function gets the current value of the Block Wait Time Integer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @return current value of the UART module Block Wait Time Integer.
 */
static inline uint8_t UART_HAL_GetBlockWaitTimeInteger(UART_Type * base)
{
    return (uint8_t)(UART_RD_WP7816T1(base) & 0xFU);
}
#endif

#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
/*!
 * @brief  Sets a value to Block Guard Time Integer.
 *
 * This function sets a value to the Block Guard Time Integer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @param bgi value to set to UART module Block Guard Time Integer.
 */
static inline void UART_HAL_SetBlockGuardTimeInteger(UART_Type * base, uint8_t bgi)
{
    UART_BWR_WGP7816_T1_BGI(base, bgi);
}

/*!
 * @brief  Gets the current value of Block Guard Time Integer.
 *
 * This function gets the current value of the Block Guard Time Integer in the UART for
 * a particular module base.
 *
 * @param base UART module base pointer.
 * @return current value of the UART module Block Guard Time Integer.
 */
static inline uint8_t UART_HAL_GetBlockGuardTimeInteger(UART_Type * base)
{
    return UART_BRD_WGP7816_T1_BGI(base);
}
#endif

#endif  /* FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT */
/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_UART_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

