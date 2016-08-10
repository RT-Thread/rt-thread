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
#ifndef __FSL_LPSCI_HAL_H__
#define __FSL_LPSCI_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup lpsci_hal
 * @{
 */

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LPSCI_SHIFT (8U)

/*! @brief Error codes for the LPSCI driver. */
typedef enum _lpsci_status
{
    kStatus_LPSCI_Success                  = 0x00U,
    kStatus_LPSCI_Fail                     = 0x01U,
    kStatus_LPSCI_BaudRateCalculationError = 0x02U,
    kStatus_LPSCI_RxStandbyModeError       = 0x03U,
    kStatus_LPSCI_ClearStatusFlagError     = 0x04U,
    kStatus_LPSCI_TxNotDisabled            = 0x05U,
    kStatus_LPSCI_RxNotDisabled            = 0x06U,
    kStatus_LPSCI_TxOrRxNotDisabled        = 0x07U,
    kStatus_LPSCI_TxBusy                   = 0x08U,
    kStatus_LPSCI_RxBusy                   = 0x09U,
    kStatus_LPSCI_NoTransmitInProgress     = 0x0AU,
    kStatus_LPSCI_NoReceiveInProgress      = 0x0BU,
    kStatus_LPSCI_Timeout                  = 0x0CU,
    kStatus_LPSCI_Initialized              = 0x0DU,
    kStatus_LPSCI_NoDataToDeal             = 0x0EU,
    kStatus_LPSCI_RxOverRun                = 0x0FU
} lpsci_status_t;

/*!
 * @brief LPSCI number of stop bits.
 *
 * These constants define the number of allowable stop bits to configure in a LPSCI base.
 */
typedef enum _lpsci_stop_bit_count {
    kLpsciOneStopBit = 0U,  /*!< one stop bit */
    kLpsciTwoStopBit = 1U,  /*!< two stop bits */
} lpsci_stop_bit_count_t;

/*!
 * @brief LPSCI parity mode.
 *
 * These constants define the LPSCI parity mode options: disabled or enabled of type even or odd.
 */
typedef enum _lpsci_parity_mode {
    kLpsciParityDisabled = 0x0U,  /*!< parity disabled */
    kLpsciParityEven     = 0x2U,  /*!< parity enabled, type even, bit setting: PE|PT = 10 */
    kLpsciParityOdd      = 0x3U,  /*!< parity enabled, type odd,  bit setting: PE|PT = 11 */
} lpsci_parity_mode_t;

/*!
 * @brief LPSCI number of bits in a character.
 *
 * These constants define the number of allowable data bits per LPSCI character. Note, check the
 * LPSCI documentation to determine if the desired LPSCI base supports the desired number
 * of data bits per LPSCI character.
 */
typedef enum  _lpsci_bit_count_per_char {
    kLpsci8BitsPerChar = 0U,   /*!< 8-bit data characters */
    kLpsci9BitsPerChar = 1U,   /*!< 9-bit data characters */
} lpsci_bit_count_per_char_t;

/*!
 * @brief LPSCI operation configuration constants.
 *
 * This provides constants for LPSCI operational states: "operates normally"
 * or "stops/ceases operation"
 */
typedef enum _lpsci_operation_config {
    kLpsciOperates = 0U,  /*!< LPSCI continues to operate normally */
    kLpsciStops = 1U,     /*!< LPSCI ceases operation */
} lpsci_operation_config_t;

/*! @brief LPSCI receiver source select mode. */
typedef enum _lpsci_receiver_source {
    kLpsciLoopBack = 0U,  /*!< Internal loop back mode. */
    kLpsciSingleWire = 1U,/*!< Single wire mode. */
} lpsci_receiver_source_t ;

/*!
 * @brief LPSCI wakeup from standby method constants.
 *
 * This provides constants for the two LPSCI wakeup methods: idle-line or address-mark.
 */
typedef enum _lpsci_wakeup_method {
    kLpsciIdleLineWake = 0U,  /*!< The idle-line wakes LPSCI receiver from standby */
    kLpsciAddrMarkWake = 1U,  /*!< The address-mark wakes LPSCI receiver from standby */
} lpsci_wakeup_method_t;

/*!
 * @brief LPSCI idle-line detect selection types.
 *
 * This provides constants for the LPSCI idle character bit-count start: either after start or
 * stop bit.
 */
typedef enum _lpsci_idle_line_select {
    kLpsciIdleLineAfterStartBit = 0U,  /*!< LPSCI idle character bit count start after start bit */
    kLpsciIdleLineAfterStopBit = 1U,   /*!< LPSCI idle character bit count start after stop bit */
} lpsci_idle_line_select_t;

/*!
 * @brief LPSCI break character length settings for transmit/detect.
 *
 * This provides constants for the LPSCI break character length for both transmission and detection
 * purposes. Note that the actual maximum bit times may vary depending on the LPSCI base.
 */
typedef enum _lpsci_break_char_length {
    kLpsciBreakChar10BitMinimum = 0U, /*!< LPSCI break char length 10 bit times (if M = 0, SBNS = 0) or
                                     11 (if M = 1, SBNS = 0 or M = 0, SBNS = 1) or 12 (if M = 1,
                                     SBNS = 1 or M10 = 1, SNBS = 0) or 13 (if M10 = 1, SNBS = 1) */
    kLpsciBreakChar13BitMinimum = 1U, /*!< LPSCI break char length 13 bit times (if M = 0, SBNS = 0) or
                                     14 (if M = 1, SBNS = 0 or M = 0, SBNS = 1) or 15 (if M = 1,
                                     SBNS = 1 or M10 = 1, SNBS = 0) or 16 (if M10 = 1, SNBS = 1) */
} lpsci_break_char_length_t;

/*!
 * @brief LPSCI single-wire mode transmit direction.
 *
 *  This provides constants for the LPSCI transmit direction when configured for single-wire mode.
 *  The transmit line TXDIR is either an input or output.
 */
typedef enum _lpsci_singlewire_txdir {
    kLpsciSinglewireTxdirIn = 0U,  /*!< LPSCI Single-Wire mode TXDIR input */
    kLpsciSinglewireTxdirOut = 1U, /*!< LPSCI Single-Wire mode TXDIR output */
} lpsci_singlewire_txdir_t;

/*!
 * @brief LPSCI infrared transmitter pulse width options.
 *
 * This provides constants for the LPSCI infrared (IR) pulse widths. Options include 3/16, 1/16
 * 1/32, and 1/4 pulse widths.
 */
typedef enum _lpsci_ir_tx_pulsewidth {
    kLpsciIrThreeSixteenthsWidth = 0U,   /*!< 3/16 pulse */
    kLpsciIrOneSixteenthWidth = 1U,      /*!< 1/16 pulse */
    kLpsciIrOneThirtysecondsWidth = 2U,  /*!< 1/32 pulse */
    kLpsciIrOneFourthWidth = 3U,         /*!< 1/4 pulse */
} lpsci_ir_tx_pulsewidth_t;

/*!
 * @brief LPSCI status flags.
 *
 * This provides constants for the LPSCI status flags for use in the LPSCI functions.
 */
typedef enum _lpsci_status_flag {
    kLpsciTxDataRegEmpty = 0U << LPSCI_SHIFT | UART0_S1_TDRE_SHIFT, /*!< Transmit data register empty flag, sets when Tx buffer is empty */
    kLpsciTxComplete     = 0U << LPSCI_SHIFT | UART0_S1_TC_SHIFT,   /*!< Transmission complete flag, sets when transmission activity complete */
    kLpsciRxDataRegFull  = 0U << LPSCI_SHIFT | UART0_S1_RDRF_SHIFT, /*!< Receive data register full flag, sets when the receive data buffer is full */
    kLpsciIdleLineDetect = 0U << LPSCI_SHIFT | UART0_S1_IDLE_SHIFT, /*!< Idle line detect flag, sets when idle line detected */
    kLpsciRxOverrun      = 0U << LPSCI_SHIFT | UART0_S1_OR_SHIFT,   /*!< Rxr Overrun, sets when new data is received before data is read from receive register */
    kLpsciNoiseDetect    = 0U << LPSCI_SHIFT | UART0_S1_NF_SHIFT,   /*!< Rxr takes 3 samples of each received bit.  If any of these samples differ, noise flag sets */
    kLpsciFrameErr       = 0U << LPSCI_SHIFT | UART0_S1_FE_SHIFT,   /*!< Frame error flag, sets if logic 0 was detected where stop bit expected */
    kLpsciParityErr      = 0U << LPSCI_SHIFT | UART0_S1_PF_SHIFT,   /*!< If parity enabled, sets upon parity error detection */
    kLpsciLineBreakDetect    = 1U << LPSCI_SHIFT | UART0_S2_LBKDIF_SHIFT,  /*!< LIN break detect interrupt flag, sets when LIN break char detected and LIN circuit enabled */
    kLpsciRxActiveEdgeDetect = 1U << LPSCI_SHIFT | UART0_S2_RXEDGIF_SHIFT, /*!< Receive pin active edge interrupt flag, sets when active edge detected */
    kLpsciRxActive           = 1U << LPSCI_SHIFT | UART0_S2_RAF_SHIFT,     /*!< Receiver Active Flag (RAF), sets at beginning of valid start bit */
#if FSL_FEATURE_LPSCI_HAS_EXTENDED_DATA_REGISTER_FLAGS
    kLpsciNoiseInCurrentWord     = 2U << LPSCI_SHIFT | UART0_ED_NOISY_SHIFT,   /*!< NOISY bit, sets if noise detected in current data word */
    kLpsciParityErrInCurrentWord = 2U << LPSCI_SHIFT | UART0_ED_PARITYE_SHIFT, /*!< PARITYE bit, sets if noise detected in current data word */
#endif
} lpsci_status_flag_t;

/*!
 * @brief LPSCI interrupt configuration structure; default settings are 0 (disabled).
 *
 * This structure contains the settings for all LPSCI interrupt configurations.
 */
typedef enum _lpsci_interrupt {
    kLpsciIntLinBreakDetect  = 0U << LPSCI_SHIFT | UART0_BDH_LBKDIE_SHIFT,  /*!< LIN break detect. */
    kLpsciIntRxActiveEdge    = 0U << LPSCI_SHIFT | UART0_BDH_RXEDGIE_SHIFT, /*!< Receive Active Edge. */
    kLpsciIntTxDataRegEmpty  = 1U << LPSCI_SHIFT | UART0_C2_TIE_SHIFT,      /*!< Transmit data register empty. */
    kLpsciIntTxComplete      = 1U << LPSCI_SHIFT | UART0_C2_TCIE_SHIFT,     /*!< Transmission complete. */
    kLpsciIntRxDataRegFull   = 1U << LPSCI_SHIFT | UART0_C2_RIE_SHIFT,     /*!< Receiver data register full. */
    kLpsciIntIdleLine        = 1U << LPSCI_SHIFT | UART0_C2_ILIE_SHIFT,     /*!< Idle line. */
    kLpsciIntRxOverrun       = 2U << LPSCI_SHIFT | UART0_C3_ORIE_SHIFT,     /*!< Receiver Overrun. */
    kLpsciIntNoiseErrFlag    = 2U << LPSCI_SHIFT | UART0_C3_NEIE_SHIFT,     /*!< Noise error flag. */
    kLpsciIntFrameErrFlag    = 2U << LPSCI_SHIFT | UART0_C3_FEIE_SHIFT,     /*!< Framing error flag. */
    kLpsciIntParityErrFlag   = 2U << LPSCI_SHIFT | UART0_C3_PEIE_SHIFT,     /*!< Parity error flag. */
} lpsci_interrupt_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name LPSCI Common Configurations
 * @{
 */

/*!
 * @brief Initializes the LPSCI controller.
 *
 * This function initializes the module to a known state.
 *
 * @param   base LPSCI module base pointer.
 */
void LPSCI_HAL_Init(UART0_Type * base);

/*!
 * @brief Enables the LPSCI transmitter.
 *
 * This function allows the user to enable the LPSCI transmitter.
 *
 * @param   base LPSCI module base pointer.
 */
static inline void LPSCI_HAL_EnableTransmitter(UART0_Type * base)
{
    UART0_BWR_C2_TE(base, 1U);
}

/*!
 * @brief Disables the LPSCI transmitter.
 *
 * This function allows the user to disable the LPSCI transmitter.
 *
 * @param   base LPSCI module base pointer.
 */
static inline void LPSCI_HAL_DisableTransmitter(UART0_Type * base)
{
    UART0_BWR_C2_TE(base, 0U);
}

/*!
 * @brief Gets the LPSCI transmitter enabled/disabled configuration setting.
 *
 * This function allows the user to get the setting of the LPSCI transmitter.
 *
 * @param   base LPSCI module base pointer.
 * @return The state of LPSCI transmitter enable(true)/disable(false) setting.
 */
static inline bool LPSCI_HAL_IsTransmitterEnabled(UART0_Type * base)
{
    return (bool)UART0_BRD_C2_TE(base);
}

/*!
 * @brief Enables the LPSCI receiver.
 *
 * This function allows the user to enable the LPSCI receiver.
 *
 * @param   base LPSCI module base pointer.
 */
static inline void LPSCI_HAL_EnableReceiver(UART0_Type * base)
{
    UART0_BWR_C2_RE(base, 1U);
}

/*!
 * @brief Disables the LPSCI receiver.
 *
 *  This function allows the user to disable the LPSCI receiver.
 *
 * @param   base LPSCI module base pointer.
 */
static inline void LPSCI_HAL_DisableReceiver(UART0_Type * base)
{
    UART0_BWR_C2_RE(base, 0U);
}

/*!
 * @brief Gets the LPSCI receiver enabled/disabled configuration setting.
 *
 *  This function allows the user to get the setting of the LPSCI receiver.
 *
 * @param   base LPSCI module base pointer.
 * @return The state of LPSCI receiver enable(true)/disable(false) setting.
 */
static inline bool LPSCI_HAL_IsReceiverEnabled(UART0_Type * base)
{
    return (bool)UART0_BRD_C2_RE(base);
}

/*!
 * @brief Configures the LPSCI baud rate.
 *
 * This function programs the LPSCI baud rate to the desired value passed in by the user. The user
 * must also pass in the module source clock so that the function can calculate the baud
 * rate divisors to their appropriate values.
 * In some LPSCI bases it is required that the transmitter/receiver be disabled
 * before calling this function.
 * Generally this is applied to all LPSCIs to ensure safe operation.
 *
 * @param   base LPSCI module base pointer.
 * @param   sourceClockInHz LPSCI source input clock in Hz.
 * @param   baudRate LPSCI desired baud rate.
 * @return  An error code or kStatus_LPSCI_Success
 */
lpsci_status_t LPSCI_HAL_SetBaudRate(UART0_Type * base, uint32_t sourceClockInHz, uint32_t baudRate);

/*!
 * @brief Sets the LPSCI baud rate modulo divisor value.
 *
 * This function allows the user to program the baud rate divisor directly in situations
 * where the divisor value is known. In this case, the user may not want to call the
 * LPSCI_HAL_SetBaudRate() function because the divisor is already known.
 *
 * @param   base LPSCI module base pointer.
 * @param   baudRateDivisor The baud rate modulo division "SBR" value.
 */
void LPSCI_HAL_SetBaudRateDivisor(UART0_Type * base, uint16_t baudRateDivisor);

#if FSL_FEATURE_LPSCI_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT
/*!
 * @brief Sets the LPSCI baud rate fine adjust. Note that this feature is available on select
 *        LPSCI bases used with baud rate programming.
 *
 * This function, which programs the baud rate fine adjustment, is used with
 * programming the baud rate modulo divisor in situations where these divisors value are known.
 * In this case, the user may not want to call the LPSCI_HAL_SetBaudRate() function because the
 * divisors are already known.
 *
 * @param   base LPSCI module base pointer.
 * @param   baudFineAdjust Value of 5-bit field used to add more timing resolution to average
 *                          baud rate frequency is 1/32 increments.
 */
static inline void LPSCI_HAL_SetBaudRateFineAdjust(UART0_Type * base, uint8_t baudFineAdjust)
{
    assert(baudFineAdjust < 0x1F);
    UART0_BWR_C4_BRFA(base, baudFineAdjust);
}
#endif

/*!
 * @brief Configures the number of bits per character in the LPSCI controller.
 *
 * This function allows the user to configure the number of bits per character according to the
 * typedef lpsci_bit_count_per_char_t.
 *
 * @param   base LPSCI module base pointer.
 * @param   bitCountPerChar Number of bits per char (8, 9, or 10, depending on the LPSCI base).
 */
static inline void LPSCI_HAL_SetBitCountPerChar(UART0_Type * base,
                                          lpsci_bit_count_per_char_t bitCountPerChar)
{
    /* config 8- (M=0) or 9-bits (M=1) */
    UART0_BWR_C1_M(base, bitCountPerChar);
}

/*!
 * @brief Configures the parity mode in the LPSCI controller.
 *
 * This function allows the user to configure the parity mode of the LPSCI controller to disable
 * or enable it for even parity or odd parity.
 *
 * @param   base LPSCI module base pointer.
 * @param   parityMode Parity mode setting (enabled, disable, odd, even - see
 *          parity_mode_t struct).
 */
void LPSCI_HAL_SetParityMode(UART0_Type * base, lpsci_parity_mode_t parityMode);

#if FSL_FEATURE_LPSCI_HAS_STOP_BIT_CONFIG_SUPPORT
/*!
 * @brief Configures the number of stop bits in the LPSCI controller.
 *
 * This function allows the user to configure the number of stop bits in the LPSCI controller
 * to be one or two stop bits.
 *
 * @param   base LPSCI module base pointer.
 * @param   stopBitCount Number of stop bits setting (1 or 2 - see lpsci_stop_bit_count_t struct).
 * @return  An error code (an unsupported setting in some LPSCIs) or kStatus_LPSCI_Success.
 */
static inline void LPSCI_HAL_SetStopBitCount(UART0_Type * base, lpsci_stop_bit_count_t stopBitCount)
{
    UART0_BWR_BDH_SBNS(base, stopBitCount);
}
#endif

/*@}*/

/*!
 * @name LPSCI Interrupts and DMA
 * @{
 */

/*!
 * @brief Configures the LPSCI module interrupts to enable/disable various interrupt sources.
 *
 * @param   base LPSCI module base pointer.
 * @param   interrupt LPSCI interrupt configuration data.
 * @param   enable   true: enable, false: disable.
 */
void LPSCI_HAL_SetIntMode(UART0_Type * base, lpsci_interrupt_t interrupt, bool enable);

/*!
 * @brief Returns whether the LPSCI module interrupts are enabled/disabled.
 *
 * @param   base LPSCI module base pointer.
 * @param   interrupt LPSCI interrupt configuration data.
 * @return  true: enable, false: disable.
 */
bool LPSCI_HAL_GetIntMode(UART0_Type * base, lpsci_interrupt_t interrupt);

#if FSL_FEATURE_LPSCI_HAS_DMA_ENABLE
/*!
 * @brief  Enables or disables the LPSCI DMA request for the transmitter.
 *
 * This function allows the user to configure the receive data register full
 * flag to generate a DMA request.
 *
 * @param   base LPSCI module base pointer.
 * @param   enable Transmit DMA request configuration setting (enable: true /disable: false).
 */
void LPSCI_HAL_SetTxDmaCmd(UART0_Type * base, bool enable);

/*!
 * @brief  Enables or disables the LPSCI DMA request for the receiver.
 *
 * This function allows the user to configure the receive data register full
 * flag to generate a DMA request.
 *
 * @param   base LPSCI module base pointer.
 * @param   enable Receive DMA request configuration setting (enable: true/disable: false).
 */
void LPSCI_HAL_SetRxDmaCmd(UART0_Type * base, bool enable);

/*!
 * @brief  Gets the LPSCI transmit DMA request configuration setting.
 *
 * This function returns the configuration setting of the transmit DMA request.
 *
 * @param   base LPSCI module base pointer.
 * @return  Transmit DMA request configuration setting (enable: true /disable: false).
 */
static inline bool LPSCI_HAL_GetTxDmaCmd(UART0_Type * base)
{
    return UART0_BRD_C5_TDMAE(base);
}

/*!
 * @brief  Gets the LPSCI receive DMA request configuration setting.
 *
 * This function returns the configuration setting of the receive DMA request.
 *
 * @param   base LPSCI module base pointer.
 * @return  Receive DMA request configuration setting (enable: true /disable: false).
 */
static inline bool LPSCI_HAL_GetRxDmaCmd(UART0_Type * base)
{
    return UART0_BRD_C5_RDMAE(base);
}
#endif /* FSL_FEATURE_LPSCI_HAS_DMA_ENABLE */

/*!
 * @brief  Gets the LPSCI transmit/receive data register address.
 *
 * This function is used for DMA transfer.
 *
 * @param   base LPSCI module base address. 
 * @return  LPSCI tx/rx data register address.
 */
static inline uint32_t LPSCI_HAL_GetDataRegAddr(UART0_Type * base)
{
    return (uint32_t)(&UART0_D_REG(base));
}

/*@}*/

/*!
 * @name LPSCI Transfer Functions
 * @{
 */

/*!
 * @brief This function allows the user to send an 8-bit character from the LPSCI data register.
 *
 * @param   base LPSCI module base pointer.
 * @param   data The data to send of size 8-bit.
 */
static inline void LPSCI_HAL_Putchar(UART0_Type * base, uint8_t data)
{
    UART0_WR_D(base, data);
}

/*!
 * @brief This function allows the user to send a 9-bit character from the LPSCI data register.
 *
 * @param   base LPSCI module base pointer.
 * @param   data The data to send of size 9-bit.
 */
void LPSCI_HAL_Putchar9(UART0_Type * base, uint16_t data);

/*!
 * @brief This function allows the user to send a 10-bit character from the LPSCI data register.
 *
 * @param   base LPSCI module base pointer.
 * @param   data The data to send of size 10-bit.
 */
void LPSCI_HAL_Putchar10(UART0_Type * base, uint16_t data);

/*!
 * @brief This function gets a received 8-bit character from the LPSCI data register.
 *
 * @param   base LPSCI module base pointer.
 * @param   readData The received data read from data register of size 8-bit.
 */
static inline void LPSCI_HAL_Getchar(UART0_Type * base, uint8_t *readData)
{
    *readData = UART0_RD_D(base);
}

/*!
 * @brief This function gets a received 9-bit character from the LPSCI data register.
 *
 * @param base LPSCI module base pointer.
 * @param readData The received data read from data register of size 9-bit.
 */
void LPSCI_HAL_Getchar9(UART0_Type * base, uint16_t *readData);

/*!
 * @brief This function gets a received 10-bit character from the LPSCI data register.
 *
 * @param base LPSCI module base pointer.
 * @param readData The received data read from data register of size 10-bit.
 */
void LPSCI_HAL_Getchar10(UART0_Type * base, uint16_t *readData);

/*!
 * @brief Sends out multiple bytes of data using the polling method.
 *
 * This function only supports 8-bit transaction.
 *
 * @param base LPSCI module base pointer.
 * @param txBuff The buffer pointer which saves the data to be sent.
 * @param txSize Size of data to be sent in unit of byte.
 */
void LPSCI_HAL_SendDataPolling(UART0_Type * base, const uint8_t *txBuff, uint32_t txSize);

/*!
 * @brief Receives multiple bytes of data using the polling method.
 *
 * This function only supports 8-bit transaction.
 *
 * @param base LPSCI module base pointer.
 * @param rxBuff The buffer pointer which saves the data to be received.
 * @param rxSize Size of data need to be received in unit of byte.
 * @return Whether the transaction is success or receive overrun.
 */
lpsci_status_t LPSCI_HAL_ReceiveDataPolling(UART0_Type * base, uint8_t *rxBuff, uint32_t rxSize);

#if FSL_FEATURE_LPSCI_HAS_EXTENDED_DATA_REGISTER_FLAGS
/*!
 * @brief Configures the LPSCI bit 10 (if enabled) or bit 9 (if disabled) as the parity bit in the
 *         serial transmission.
 *
 * This function configures bit 10 or bit 9 to be the parity bit.  To configure bit 10 as the parity
 * bit, the function sets LPSCIx_C4[M10]. It also sets LPSCIx_C1[M] and LPSCIx_C1[PE] as required.
 *
 * @param base LPSCI module base pointer.
 * @param enable The setting to enable (true), which configures bit 10 as the parity bit or to
 *  disable (false), which configures bit 9 as the parity bit in the serial transmission.
 */
static inline void LPSCI_HAL_SetBit10AsParitybit(UART0_Type * base, bool enable)
{
    /* to enable the parity bit as the tenth data bit, along with enabling LPSCIx_C4[M10]
     * need to also enable parity and set LPSCIx_C1[M] bit
     * assumed that the user has already set the appropriate bits */
    UART0_BWR_C4_M10(base, enable);
}

/*!
 * @brief Gets the configuration of the LPSCI bit 10 (if enabled) or bit 9 (if disabled) as the
 *         parity bit in the serial transmission.
 *
 * This function returns true if bit 10 is configured as the parity bit. Otherwise it returns
 * false if bit 9 is configured as the parity bit.
 *
 * @param  base LPSCI module base pointer.
 * @return The configuration setting of bit 10 (true), or bit 9 (false) as the parity bit in
 * the serial transmission.
 */
static inline bool LPSCI_HAL_IsBit10SetAsParitybit(UART0_Type * base)
{
    /* to see if the parity bit is set as the tenth data bit,
     * return value of LPSCIx_C4[M10] */
    return UART0_BRD_C4_M10(base);
}

/*!
 * @brief  Determines whether the LPSCI received data word was received with noise.
 *
 * This function returns true if the received data word was received with noise. Otherwise,
 * it returns false indicating no noise was detected.
 *
 * @param   base LPSCI module base pointer.
 * @return  The status of the NOISY bit in the LPSCI extended data register.
 */
static inline bool LPSCI_HAL_IsCurrentDataWithNoise(UART0_Type * base)
{
    return UART0_BRD_ED_NOISY(base);
}

/*!
 * @brief  Determines whether the LPSCI received data word was received with a parity error.
 *
 * This function returns true if the received data word was received with a parity error.
 * Otherwise, it returns false indicating no parity error was detected.
 *
 * @param   base LPSCI module base pointer.
 * @return  The status of the PARITYE (parity error) bit in the LPSCI extended data register.
 */
static inline bool LPSCI_HAL_IsCurrentDataWithParityError(UART0_Type * base)
{
    return UART0_BRD_ED_PARITYE(base);
}

#endif  /* FSL_FEATURE_LPSCI_HAS_EXTENDED_DATA_REGISTER_FLAGS*/

/*@}*/

/*!
 * @name LPSCI Status Flags
 * @{
 */

/*!
 * @brief  Gets all  LPSCI status flag states.
 *
 * @param base LPSCI module base pointer.
 * @param statusFlag Status flag name.
 * @return The status flag states.
 */
bool LPSCI_HAL_GetStatusFlag(UART0_Type * base, lpsci_status_flag_t statusFlag);

/*!
 * @brief  Clears an individual and specific LPSCI status flag.
 *
 * This function allows the user to clear an individual and specific LPSCI status flag. Refer to
 * structure definition lpsci_status_flag_t for list of status bits.
 *
 * @param base LPSCI module base pointer.
 * @param statusFlag The desired LPSCI status flag to clear.
 * @return An error code or kStatus_LPSCI_Success.
 */
lpsci_status_t LPSCI_HAL_ClearStatusFlag(UART0_Type * base, lpsci_status_flag_t statusFlag);

/*@}*/

/*!
 * @name LPSCI Special Feature Configurations
 * @{
 */

/*!
 * @brief Configures the LPSCI to either operate or cease to operate in wait mode.
 *
 * The function configures the LPSCI to either operate or cease to operate when wait mode is
 * entered.
 *
 * @param   base LPSCI module base pointer.
 * @param   mode The LPSCI wait mode operation - operates or ceases to operate in wait mode.
 */
static inline void LPSCI_HAL_SetWaitModeOperation(UART0_Type * base, lpsci_operation_config_t mode)
{
	/*In CPU wait mode: 0 - LPSCI is enabled; 1 - LPSCI is disabled */
	UART0_BWR_C1_DOZEEN(base, mode);
}

/*!
 * @brief Determines if the LPSCI operates or ceases to operate in wait mode.
 *
 * This function returns kLpsciOperates if the LPSCI has been configured to operate in wait mode.
 * Else it returns KLpsciStops if the LPSCI has been configured to cease-to-operate in wait mode.
 *
 * @param   base LPSCI module base pointer.
 * @return The LPSCI WAIT mode operation configuration, returns either kLpsciOperates or KLpsciStops.
 */
static inline lpsci_operation_config_t LPSCI_HAL_GetWaitModeOperation(UART0_Type * base)
{
    /*In CPU wait mode: 0 - LPSCI is enabled; 1 - LPSCI is disabled */
    return (lpsci_operation_config_t)UART0_BRD_C1_DOZEEN(base);
}

/*!
 * @brief Configures the LPSCI loopback operation.
 *
 * This function enables or disables the LPSCI loopback operation.
 *
 * @param base LPSCI module base pointer.
 * @param enable The LPSCI loopback mode configuration, either disabled (false) or enabled (true).
 */
static inline void LPSCI_HAL_SetLoopCmd(UART0_Type * base, bool enable)
{
    UART0_BWR_C1_LOOPS(base, enable);
}

/*!
 * @brief Configures the LPSCI single-wire operation.
 *
 * This function enables or disables the LPSCI single-wire operation.
 * In some LPSCI bases it is required that the transmitter/receiver be disabled
 * before calling this function.
 * This may be applied to all LPSCIs to ensure safe operation.
 *
 * @param base LPSCI module base pointer.
 * @param source The LPSCI single-wire mode configuration, either disabled (false) or enabled (true).
 */
static inline void LPSCI_HAL_SetReceiverSource(UART0_Type * base, lpsci_receiver_source_t source)
{
    UART0_BWR_C1_RSRC(base, source);
}
/*!
 * @brief Configures the LPSCI transmit direction while in single-wire mode.
 *
 * This function configures the transmitter direction when the LPSCI is configured for single-wire
 * operation.
 *
 * @param   base LPSCI module base pointer.
 * @param   direction The LPSCI single-wire mode transmit direction configuration of type
 *                    lpsci_singlewire_txdir_t (either kLpsciSinglewireTxdirIn or
 *                    kLpsciSinglewireTxdirOut.
 */
static inline void LPSCI_HAL_SetTransmitterDir(UART0_Type * base, lpsci_singlewire_txdir_t direction)
{
    /* configure LPSCI transmit direction (input or output) when in single-wire mode
     * it is assumed LPSCI is in single-wire mode */
    UART0_BWR_C3_TXDIR(base, direction);
}

/*!
 * @brief  Places the LPSCI receiver in standby mode.
 *
 * This function, when called, places the LPSCI receiver into standby mode.
 * In some LPSCI bases, there are conditions that must be met before placing the receive in standby mode.
 * Before placing LPSCI in standby, determine if receiver is set to
 * wake on idle, and if receiver is already in idle state.
 * NOTE: RWU should only be set with C1[WAKE] = 0 (wakeup on idle) if the channel is currently
 * not idle.
 * This can be determined by the S2[RAF] flag. If set to wake up FROM an IDLE event and the channel
 * is already idle, it is possible that the LPSCI discards data because data must be received
 * (or a LIN break detect) after an IDLE is detected before IDLE is allowed to be reasserted.
 *
 * @param base LPSCI module base pointer.
 * @return Error code or kStatus_LPSCI_Success.
 */
lpsci_status_t LPSCI_HAL_PutReceiverInStandbyMode(UART0_Type * base);

/*!
 * @brief  Places the LPSCI receiver in normal mode (disable standby mode operation).
 *
 * This function, when called, places the LPSCI receiver into normal mode and out of
 * standby mode.
 *
 * @param   base LPSCI module base pointer.
 */
static inline void LPSCI_HAL_PutReceiverInNormalMode(UART0_Type * base)
{
    UART0_CLR_C2(base, UART0_C2_RWU_MASK);
}

/*!
 * @brief  Determines if the LPSCI receiver is currently in standby mode.
 *
 * This function determines the state of the LPSCI receiver. If it returns true,
 * the LPSCI receiver is in standby mode. If it returns false, the LPSCI receiver
 * is in normal mode.
 *
 * @param   base LPSCI module base pointer.
 * @return The LPSCI receiver is in normal mode (false) or standby mode (true).
 */
static inline bool LPSCI_HAL_IsReceiverInStandby(UART0_Type * base)
{
    return UART0_BRD_C2_RWU(base);
}

/*!
 * @brief  Selects the LPSCI receiver wakeup method (idle-line or address-mark) from standby mode.
 *
 * This function configures the wakeup method of the LPSCI receiver from standby mode.  The options
 * are idle-line wake or address-mark wake.
 *
 * @param   base LPSCI module base pointer.
 * @param   method The LPSCI receiver wakeup method options: kLpsciIdleLineWake - Idle-line wake or
 *                 kLpsciAddrMarkWake - address-mark wake.
 */
static inline void LPSCI_HAL_SetReceiverWakeupMethod(UART0_Type * base, lpsci_wakeup_method_t method)
{
    UART0_BWR_C1_WAKE(base, method);
}

/*!
 * @brief  Gets the LPSCI receiver wakeup method (idle-line or address-mark) from standby mode.
 *
 * This function returns how the LPSCI receiver is configured to wake from standby mode. The
 * wake method options that can be returned are kLpsciIdleLineWake or kLpsciAddrMarkWake.
 *
 * @param   base LPSCI module base pointer.
 * @return  The LPSCI receiver wakeup from standby method, false: kLpsciIdleLineWake (idle-line wake)
 *          or true: kLpsciAddrMarkWake (address-mark wake).
 */
static inline lpsci_wakeup_method_t LPSCI_HAL_GetReceiverWakeupMethod(UART0_Type * base)
{
    return (lpsci_wakeup_method_t)UART0_BRD_C1_WAKE(base);
}

/*!
 * @brief  Configures the operation options of the LPSCI idle line detect.
 *
 * This function allows the user to configure the LPSCI idle-line detect operation. There are two
 * separate operations for the user to configure, the idle line bit-count start and the receive
 * wake up affect on IDLE status bit. The user passes in a structure of type
 * lpsci_idle_line_config_t.
 *
 * @param   base LPSCI module base pointer.
 * @param   idleLine Idle bit count start: 0 - after start bit (default), 1 - after stop bit
 * @param   rxWakeIdleDetect Receiver Wake Up Idle Detect. IDLE status bit operation during receive
 *          standby. Controls whether idle character that wakes up receiver will also set IDLE status
 *          bit. 0 - IDLE status bit doesn't get set (default), 1 - IDLE status bit gets set
 */
void LPSCI_HAL_ConfigIdleLineDetect(UART0_Type * base, uint8_t idleLine, uint8_t rxWakeIdleDetect);

/*!
 * @brief  Configures the LPSCI break character transmit length.
 *
 * This function allows the user to configure the LPSCI break character transmit length. See
 * the typedef lpsci_break_char_length_t for setting options.
 * In some LPSCI bases it is required that the transmitter be disabled before calling
 * this function. This may be applied to all LPSCIs to ensure safe operation.
 *
 * @param base LPSCI module base pointer.
 * @param length The LPSCI break character length setting of type lpsci_break_char_length_t, either a
 *               minimum 10-bit times or a minimum 13-bit times.
 */
static inline void LPSCI_HAL_SetBreakCharTransmitLength(UART0_Type * base,
                                                        lpsci_break_char_length_t length)
{
    /* Configure BRK13 - Break Character transmit length configuration
     * LPSCI break character length setting:
     * 0 - minimum 10-bit times (default),
     * 1 - minimum 13-bit times */
    UART0_BWR_S2_BRK13(base, length);
}

/*!
 * @brief  Configures the LPSCI break character detect length.
 *
 * This function allows the user to configure the LPSCI break character detect length. See
 * the typedef lpsci_break_char_length_t for setting options.
 *
 * @param base LPSCI module base pointer.
 * @param length The LPSCI break character length setting of type lpsci_break_char_length_t, either a
 *               minimum 10-bit times or a minimum 13-bit times.
 */
static inline void LPSCI_HAL_SetBreakCharDetectLength(UART0_Type * base,
                                                      lpsci_break_char_length_t length)
{
    /* Configure LBKDE - Break Character detect length configuration
     * LPSCI break character length setting:
     * 0 - minimum 10-bit times (default),
     * 1 - minimum 13-bit times */
    UART0_BWR_S2_LBKDE(base, length);
}

/*!
 * @brief  Configures the LPSCI transmit send break character operation.
 *
 * This function allows the user to queue a LPSCI break character to send.  If true is passed into
 * the function, a break character is queued for transmission.  A break character is
 * continuously be queued until this function is called again when a false is passed into this
 * function.
 *
 * @param   base LPSCI module base pointer.
 * @param   enable If false, the LPSCI normal/queue break character setting is disabled, which
 *                 configures the LPSCI for normal transmitter operation. If true, a break
 *                 character is queued for transmission.
 */
static inline void LPSCI_HAL_SetBreakCharCmd(UART0_Type * base, bool enable)
{
    UART0_BWR_C2_SBK(base, enable);
}

/*!
 * @brief  Configures the LPSCI match address mode control operation. Note that this feature is available on
 *         select LPSCI bases.
 *
 * The function allows the user to configure the LPSCI match address control operation. The user
 * has the option to enable the match address mode and to program the match address value. There
 * are two match address modes, each with its own enable and programmable match address value.
 *
 * @param  base LPSCI module base pointer.
 * @param  matchAddrMode1 If true, this enables match address mode 1 (MAEN1), where false disables.
 * @param  matchAddrMode2 If true, this enables match address mode 2 (MAEN2), where false disables.
 * @param  matchAddrValue1 The match address value to program for match address mode 1.
 * @param  matchAddrValue2 The match address value to program for match address mode 2.
 */
void LPSCI_HAL_SetMatchAddress(UART0_Type * base, bool matchAddrMode1, bool matchAddrMode2,
                              uint8_t matchAddrValue1, uint8_t matchAddrValue2);

#if FSL_FEATURE_LPSCI_HAS_BIT_ORDER_SELECT
/*!
 * @brief Configures the LPSCI to send data MSB first.
 * Note that this feature is available on select LPSCI bases.
 *
 * The function allows the user to configure the LPSCI to send data either MSB first or LSB first.
 * In some LPSCI bases it is required that the transmitter/receiver be disabled
 * before calling this function.
 * This may be applied to all LPSCIs to ensure safe operation.
 *
 * @param   base LPSCI module base pointer.
 * @param   enable This configures send MSB first mode configuration. If true, the data is sent MSB
 *                 first; if false, it is sent LSB first.
 */
static inline void LPSCI_HAL_SetSendMsbFirstCmd(UART0_Type * base, bool enable)
{
    UART0_BWR_S2_MSBF(base, enable);
}
#endif

#if FSL_FEATURE_LPSCI_HAS_MODEM_SUPPORT
/*!
 * @brief  Enables the LPSCI receiver request-to-send functionality.
 *
 * This function allows the user to enable the LPSCI receiver request-to-send (RTS) functionality.
 * By enabling, it allows the RTS output to control the CTS input of the transmitting device to
 * prevent receiver overrun. RTS is deasserted if the number of characters in the receiver data
 * register (FIFO) is equal to or greater than RWFIFO[RXWATER]. RTS is asserted when the
 * number of characters in the receiver data register (FIFO) is less than RWFIFO[RXWATER].
 * Do not set both RXRTSE and TXRTSE.
 *
 * @param   base LPSCI module base pointer.
 * @param   enable   Enable or disable receiver rts.
 */
static inline void LPSCI_HAL_SetReceiverRtsCmd(UART0_Type * base, bool enable)
{
    UART0_BWR_MODEM_RXRTSE(base, enable);
}

/*!
 * @brief  Enables the LPSCI transmitter request-to-send functionality.
 *
 * This function allows the user to enable the LPSCI transmitter request-to-send (RTS) functionality.
 * When enabled, it allows the LPSCI to control the RTS assertion before and after a transmission
 * such that when a character is placed into an empty transmitter data buffer, RTS
 * asserts one bit time before the start bit is transmitted. RTS deasserts one bit time after all
 * characters in the transmitter data buffer and shift register are completely sent, including
 * the last stop bit.
 *
 * @param   base LPSCI module base pointer.
 * @param   enable   Enable or disable transmitter RTS.
 */
static inline void LPSCI_HAL_SetTransmitterRtsCmd(UART0_Type * base, bool enable)
{
    UART0_BWR_MODEM_TXRTSE(base, enable);
}

/*!
 * @brief  Configures the LPSCI transmitter RTS polarity.
 *
 * This function allows the user configure the transmitter RTS polarity to be either active low
 * or active high.
 *
 * @param base LPSCI module base pointer.
 * @param polarity The LPSCI transmitter RTS polarity setting (false - active low,
 *                 true - active high).
 */
static inline void LPSCI_HAL_SetTransmitterRtsPolarityMode(UART0_Type * base, bool polarity)
{
    UART0_BWR_MODEM_TXRTSPOL(base, polarity);
}

/*!
 * @brief  Enables the LPSCI transmitter clear-to-send functionality.
 *
 * This function allows the user to enable the LPSCI transmitter clear-to-send (CTS) functionality.
 * When enabled, the transmitter checks the state of CTS each time it is ready to send a character.
 * If CTS is asserted, the character is sent. If CTS is deasserted, the signal TXD remains in
 * the mark state and transmission is delayed until CTS is asserted. Changes in CTS as a
 * character is being sent do not affect its transmission.
 *
 * @param   base LPSCI module base pointer.
 * @param   enable   Enable or disable transmitter CTS.
 */
static inline void LPSCI_HAL_SetTransmitterCtsCmd(UART0_Type * base, bool enable)
{
    UART0_BWR_MODEM_TXCTSE(base, enable);
}

#endif  /* FSL_FEATURE_LPSCI_HAS_MODEM_SUPPORT*/

#if FSL_FEATURE_LPSCI_HAS_IR_SUPPORT
/*!
 * @brief  Configures the LPSCI infrared operation.
 *
 * The function allows the user to enable or disable the LPSCI infrared (IR) operation
 * and to configure the IR pulse width.
 *
 * @param   base LPSCI module base pointer.
 * @param   enable Enable (true) or disable (false) the infrared operation.
 * @param   pulseWidth The LPSCI transmit narrow pulse width setting of type lpsci_ir_tx_pulsewidth_t.
 */
void LPSCI_HAL_SetInfraredOperation(UART0_Type * base,
                                    bool enable,
                                    lpsci_ir_tx_pulsewidth_t pulseWidth);
#endif  /* FSL_FEATURE_LPSCI_HAS_IR_SUPPORT*/

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_LPSCI_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

