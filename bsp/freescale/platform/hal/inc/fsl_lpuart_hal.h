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
#ifndef __FSL_LPUART_HAL_H__
#define __FSL_LPUART_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup lpuart_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LPUART_SHIFT (16U)
#define LPUART_BAUD_REG_ID (0U)
#define LPUART_STAT_REG_ID (1U)
#define LPUART_CTRL_REG_ID (2U)
#define LPUART_DATA_REG_ID (3U)
#define LPUART_MATCH_REG_ID (4U)
#define LPUART_MODIR_REG_ID (5U)
#define LPUART_FIFO_REG_ID (6U)
#define LPUART_WATER_REG_ID (7U)

/*! @brief Error codes for the LPUART driver.*/
typedef enum _lpuart_status
{
    kStatus_LPUART_Success                  = 0x00U,
    kStatus_LPUART_Fail                     = 0x01U,
    kStatus_LPUART_BaudRateCalculationError = 0x02U,
    kStatus_LPUART_RxStandbyModeError       = 0x03U,
    kStatus_LPUART_ClearStatusFlagError     = 0x04U,
    kStatus_LPUART_TxNotDisabled            = 0x05U,
    kStatus_LPUART_RxNotDisabled            = 0x06U,
    kStatus_LPUART_TxOrRxNotDisabled        = 0x07U,
    kStatus_LPUART_TxBusy                   = 0x08U,
    kStatus_LPUART_RxBusy                   = 0x09U,
    kStatus_LPUART_NoTransmitInProgress     = 0x0AU,
    kStatus_LPUART_NoReceiveInProgress      = 0x0BU,
    kStatus_LPUART_Timeout                  = 0x0CU,
    kStatus_LPUART_Initialized              = 0x0DU,
    kStatus_LPUART_NoDataToDeal             = 0x0EU,
    kStatus_LPUART_RxOverRun                = 0x0FU
} lpuart_status_t;

/*! @brief LPUART number of stop bits*/
typedef enum _lpuart_stop_bit_count {
    kLpuartOneStopBit = 0x0U, /*!< one stop bit @internal gui name="1" */
    kLpuartTwoStopBit = 0x1U, /*!< two stop bits @internal gui name="2" */
} lpuart_stop_bit_count_t;

/*! @brief LPUART parity mode*/
typedef enum _lpuart_parity_mode {
    kLpuartParityDisabled = 0x0U, /*!< parity disabled @internal gui name="Disabled" */
    kLpuartParityEven     = 0x2U, /*!< parity enabled, type even, bit setting: PE|PT = 10 @internal gui name="Even" */
    kLpuartParityOdd      = 0x3U, /*!< parity enabled, type odd,  bit setting: PE|PT = 11 @internal gui name="Odd" */
} lpuart_parity_mode_t;

/*! @brief LPUART number of bits in a character*/
typedef enum  _lpuart_bit_count_per_char {
    kLpuart8BitsPerChar  = 0x0U, /*!< 8-bit data characters @internal gui name="8" */
    kLpuart9BitsPerChar  = 0x1U, /*!< 9-bit data characters @internal gui name="9" */
    kLpuart10BitsPerChar = 0x2U, /*!< 10-bit data characters @internal gui name="10" */
} lpuart_bit_count_per_char_t;

/*! @brief LPUART operation configuration constants*/
typedef enum _lpuart_operation_config {
    kLpuartOperates = 0x0U, /*!< LPUART continues to operate normally.*/
    kLpuartStops    = 0x1U, /*!< LPUART stops operation. */
} lpuart_operation_config_t;

/*! @brief LPUART wakeup from standby method constants*/
typedef enum _lpuart_wakeup_method {
    kLpuartIdleLineWake = 0x0U, /*!< Idle-line wakes the LPUART receiver from standby. */
    kLpuartAddrMarkWake = 0x1U, /*!< Addr-mark wakes LPUART receiver from standby.*/
} lpuart_wakeup_method_t;

/*! @brief LPUART idle line detect selection types*/
typedef enum _lpuart_idle_line_select {
    kLpuartIdleLineAfterStartBit = 0x0U, /*!< LPUART idle character bit count start after start bit */
    kLpuartIdleLineAfterStopBit  = 0x1U, /*!< LPUART idle character bit count start after stop bit */
} lpuart_idle_line_select_t;

/*!
 * @brief LPUART break character length settings for transmit/detect.
 *
 * The actual maximum bit times may vary depending on the LPUART instance.
 */
typedef enum _lpuart_break_char_length {
    kLpuartBreakChar10BitMinimum = 0x0U, /*!< LPUART break char length 10 bit times (if M = 0, SBNS = 0)
                                      or 11 (if M = 1, SBNS = 0 or M = 0, SBNS = 1) or 12 (if M = 1,
                                      SBNS = 1 or M10 = 1, SNBS = 0) or 13 (if M10 = 1, SNBS = 1) */
    kLpuartBreakChar13BitMinimum = 0x1U, /*!< LPUART break char length 13 bit times (if M = 0, SBNS = 0
                                           or M10 = 0, SBNS = 1) or 14 (if M = 1, SBNS = 0 or M = 1,
                                           SBNS = 1) or 15 (if M10 = 1, SBNS = 1 or M10 = 1, SNBS = 0) */
} lpuart_break_char_length_t;

/*! @brief LPUART single-wire mode TX direction*/
typedef enum _lpuart_singlewire_txdir {
    kLpuartSinglewireTxdirIn  = 0x0U, /*!< LPUART Single Wire mode TXDIR input*/
    kLpuartSinglewireTxdirOut = 0x1U, /*!< LPUART Single Wire mode TXDIR output*/
} lpuart_singlewire_txdir_t;

/*! @brief LPUART Configures the match addressing mode used.*/
typedef enum _lpuart_match_config {
    kLpuartAddressMatchWakeup    = 0x0U, /*!< Address Match Wakeup*/
    kLpuartIdleMatchWakeup       = 0x1U, /*!< Idle Match Wakeup*/
    kLpuartMatchOnAndMatchOff    = 0x2U, /*!< Match On and Match Off*/
    kLpuartEnablesRwuOnDataMatch = 0x3U, /*!< Enables RWU on Data Match and Match On/Off for transmitter CTS input*/
} lpuart_match_config_t;

/*! @brief LPUART infra-red transmitter pulse width options*/
typedef enum _lpuart_ir_tx_pulsewidth {
    kLpuartIrThreeSixteenthsWidth  = 0x0U, /*!< 3/16 pulse*/
    kLpuartIrOneSixteenthWidth     = 0x1U, /*!< 1/16 pulse*/
    kLpuartIrOneThirtysecondsWidth = 0x2U, /*!< 1/32 pulse*/
    kLpuartIrOneFourthWidth        = 0x3U, /*!< 1/4 pulse*/
} lpuart_ir_tx_pulsewidth_t;

/*!
 * @brief LPUART Configures the number of idle characters that must be received
 * before the IDLE flag is set.
 */
typedef enum _lpuart_idle_char {
    kLpuart_1_IdleChar   = 0x0U, /*!< 1 idle character*/
    kLpuart_2_IdleChar   = 0x1U, /*!< 2 idle character*/
    kLpuart_4_IdleChar   = 0x2U, /*!< 4 idle character*/
    kLpuart_8_IdleChar   = 0x3U, /*!< 8 idle character*/
    kLpuart_16_IdleChar  = 0x4U, /*!< 16 idle character*/
    kLpuart_32_IdleChar  = 0x5U, /*!< 32 idle character*/
    kLpuart_64_IdleChar  = 0x6U, /*!< 64 idle character*/
    kLpuart_128_IdleChar = 0x7U, /*!< 128 idle character*/
} lpuart_idle_char_t;

/*! @brief LPUART Transmits the CTS Configuration. Configures the source of the CTS input.*/
typedef enum _lpuart_cts_source {
    kLpuartCtsSourcePin = 0x0U,  /*!< CTS input is the LPUART_CTS pin.*/
    kLpuartCtsSourceInvertedReceiverMatch = 0x1U, /*!< CTS input is the inverted Receiver Match result.*/
} lpuart_cts_source_t;

/*!
 * @brief LPUART Transmits CTS Source.Configures if the CTS state is checked at
 * the start of each character or only when the transmitter is idle.
 */
typedef enum _lpuart_cts_config {
    kLpuartCtsSampledOnEachChar = 0x0U, /*!< CTS input is sampled at the start of each character.*/
    kLpuartCtsSampledOnIdle     = 0x1U, /*!< CTS input is sampled when the transmitter is idle.*/
} lpuart_cts_config_t;

/*! @brief Structure for idle line configuration settings*/
typedef struct LpuartIdleLineConfig {
    unsigned idleLineType : 1; /*!< ILT, Idle bit count start: 0 - after start bit (default),
                                    1 - after stop bit */
    unsigned rxWakeIdleDetect : 1; /*!< RWUID, Receiver Wake Up Idle Detect. IDLE status bit
                                        operation during receive standbyControls whether idle
                                        character that wakes up receiver will also set
                                        IDLE status bit 0 - IDLE status bit doesn't
                                        get set (default), 1 - IDLE status bit gets set*/
} lpuart_idle_line_config_t;

/*! @brief LPUART Receiver Idle Empty Enable constants.*/
typedef enum _lpuart_rx_idle_empty_config {
    kLpuartRxidDisabled         = 0x0U,  /*!< Disable RDRF assertion due to partially filled FIFO when receiver is idle.*/
    kLpuartRxidEnabledFor1Char  = 0x1U,  /*!< Enable RDRF assertion due to partially filled FIFO when receiver is idle for 1 character.*/
    kLpuartRxidEnabledFor2Char  = 0x2U,  /*!< Enable RDRF assertion due to partially filled FIFO when receiver is idle for 2 characters.*/
    kLpuartRxidEnabledFor4Char  = 0x3U,  /*!< Enable RDRF assertion due to partially filled FIFO when receiver is idle for 4 characters.*/
    kLpuartRxidEnabledFor8Char  = 0x4U,  /*!< Enable RDRF assertion due to partially filled FIFO when receiver is idle for 8 characters.*/
    kLpuartRxidEnabledFor16Char = 0x5U,  /*!< Enable RDRF assertion due to partially filled FIFO when receiver is idle for 16 characters.*/
    kLpuartRxidEnabledFor32Char = 0x6U,  /*!< Enable RDRF assertion due to partially filled FIFO when receiver is idle for 32 characters.*/
    kLpuartRxidEnabledFor64Char = 0x7U,  /*!< Enable RDRF assertion due to partially filled FIFO when receiver is idle for 64 characters.*/
} lpuart_rx_idle_empty_config_t;

/*!
 * @brief LPUART status flags.
 *
 * This provides constants for the LPUART status flags for use in the UART functions.
 */
typedef enum _lpuart_status_flag {
    kLpuartTxDataRegEmpty         = LPUART_STAT_REG_ID << LPUART_SHIFT | LPUART_STAT_TDRE_SHIFT,    /*!< Transmit data register empty flag, sets when transmit buffer is empty */
    kLpuartTxComplete             = LPUART_STAT_REG_ID << LPUART_SHIFT | LPUART_STAT_TC_SHIFT,      /*!< Transmission complete flag, sets when transmission activity complete */
    kLpuartRxDataRegFull          = LPUART_STAT_REG_ID << LPUART_SHIFT | LPUART_STAT_RDRF_SHIFT,    /*!< Receive data register full flag, sets when the receive data buffer is full */
    kLpuartIdleLineDetect         = LPUART_STAT_REG_ID << LPUART_SHIFT | LPUART_STAT_IDLE_SHIFT,    /*!< Idle line detect flag, sets when idle line detected */
    kLpuartRxOverrun              = LPUART_STAT_REG_ID << LPUART_SHIFT | LPUART_STAT_OR_SHIFT,      /*!< Receive Overrun, sets when new data is received before data is read from receive register */
    kLpuartNoiseDetect            = LPUART_STAT_REG_ID << LPUART_SHIFT | LPUART_STAT_NF_SHIFT,      /*!< Receive takes 3 samples of each received bit.  If any of these samples differ, noise flag sets */
    kLpuartFrameErr               = LPUART_STAT_REG_ID << LPUART_SHIFT | LPUART_STAT_FE_SHIFT,      /*!< Frame error flag, sets if logic 0 was detected where stop bit expected */
    kLpuartParityErr              = LPUART_STAT_REG_ID << LPUART_SHIFT | LPUART_STAT_PF_SHIFT,      /*!< If parity enabled, sets upon parity error detection */
    kLpuartLineBreakDetect        = LPUART_STAT_REG_ID << LPUART_SHIFT | LPUART_STAT_LBKDE_SHIFT,   /*!< LIN break detect interrupt flag, sets when LIN break char detected and LIN circuit enabled */
    kLpuartRxActiveEdgeDetect     = LPUART_STAT_REG_ID << LPUART_SHIFT | LPUART_STAT_RXEDGIF_SHIFT, /*!< Receive pin active edge interrupt flag, sets when active edge detected */
    kLpuartRxActive               = LPUART_STAT_REG_ID << LPUART_SHIFT | LPUART_STAT_RAF_SHIFT,     /*!< Receiver Active Flag (RAF), sets at beginning of valid start bit */
    kLpuartNoiseInCurrentWord     = LPUART_DATA_REG_ID << LPUART_SHIFT | LPUART_DATA_NOISY_SHIFT,     /*!< NOISY bit, sets if noise detected in current data word */
    kLpuartParityErrInCurrentWord = LPUART_DATA_REG_ID << LPUART_SHIFT | LPUART_DATA_PARITYE_SHIFT,   /*!< PARITYE bit, sets if noise detected in current data word */
#if FSL_FEATURE_LPUART_HAS_ADDRESS_MATCHING
    kLpuartMatchAddrOne           = LPUART_STAT_REG_ID << LPUART_SHIFT | LPUART_STAT_MA1F_SHIFT,    /*!< Address one match flag */
    kLpuartMatchAddrTwo           = LPUART_STAT_REG_ID << LPUART_SHIFT | LPUART_STAT_MA2F_SHIFT,    /*!< Address two match flag */
#endif
#if FSL_FEATURE_LPUART_HAS_FIFO
    kLpuartTxBuffEmpty              = LPUART_FIFO_REG_ID << LPUART_SHIFT | LPUART_FIFO_TXEMPT_SHIFT,  /*!< TXEMPT bit, sets if transmit buffer is empty */
    kLpuartRxBuffEmpty              = LPUART_FIFO_REG_ID << LPUART_SHIFT | LPUART_FIFO_RXEMPT_SHIFT,  /*!< RXEMPT bit, sets if receive buffer is empty */
    kLpuartTxBuffOverflow           = LPUART_FIFO_REG_ID << LPUART_SHIFT | LPUART_FIFO_TXOF_SHIFT,    /*!< TXOF bit, sets if transmit buffer overflow occurred */
    kLpuartRxBuffUnderflow          = LPUART_FIFO_REG_ID << LPUART_SHIFT | LPUART_FIFO_RXUF_SHIFT,    /*!< RXUF bit, sets if receive buffer underflow occurred */
#endif
} lpuart_status_flag_t;

/*! @brief LPUART interrupt configuration structure, default settings are 0 (disabled)*/
typedef enum _lpuart_interrupt {
    kLpuartIntLinBreakDetect = LPUART_BAUD_REG_ID << LPUART_SHIFT | LPUART_BAUD_LBKDIE_SHIFT,  /*!< LIN break detect. */
    kLpuartIntRxActiveEdge   = LPUART_BAUD_REG_ID << LPUART_SHIFT | LPUART_BAUD_RXEDGIE_SHIFT, /*!< Receive Active Edge. */
    kLpuartIntTxDataRegEmpty = LPUART_CTRL_REG_ID << LPUART_SHIFT | LPUART_CTRL_TIE_SHIFT,     /*!< Transmit data register empty. */
    kLpuartIntTxComplete     = LPUART_CTRL_REG_ID << LPUART_SHIFT | LPUART_CTRL_TCIE_SHIFT,    /*!< Transmission complete. */
    kLpuartIntRxDataRegFull  = LPUART_CTRL_REG_ID << LPUART_SHIFT | LPUART_CTRL_RIE_SHIFT,     /*!< Receiver data register full. */
    kLpuartIntIdleLine       = LPUART_CTRL_REG_ID << LPUART_SHIFT | LPUART_CTRL_ILIE_SHIFT,    /*!< Idle line. */
    kLpuartIntRxOverrun      = LPUART_CTRL_REG_ID << LPUART_SHIFT | LPUART_CTRL_ORIE_SHIFT,    /*!< Receiver Overrun. */
    kLpuartIntNoiseErrFlag   = LPUART_CTRL_REG_ID << LPUART_SHIFT | LPUART_CTRL_NEIE_SHIFT,    /*!< Noise error flag. */
    kLpuartIntFrameErrFlag   = LPUART_CTRL_REG_ID << LPUART_SHIFT | LPUART_CTRL_FEIE_SHIFT,    /*!< Framing error flag. */
    kLpuartIntParityErrFlag  = LPUART_CTRL_REG_ID << LPUART_SHIFT | LPUART_CTRL_PEIE_SHIFT,    /*!< Parity error flag. */
#if FSL_FEATURE_LPUART_HAS_ADDRESS_MATCHING
    kLpuartIntMatchAddrOne   = LPUART_CTRL_REG_ID << LPUART_SHIFT | LPUART_CTRL_MA1IE_SHIFT,   /*!< Match address one flag. */
    kLpuartIntMatchAddrTwo   = LPUART_CTRL_REG_ID << LPUART_SHIFT | LPUART_CTRL_MA2IE_SHIFT,   /*!< Match address two flag. */
#endif
#if FSL_FEATURE_LPUART_HAS_FIFO
    kLpuartIntTxFifoOverflow  = LPUART_FIFO_REG_ID << LPUART_SHIFT | LPUART_FIFO_TXOFE_SHIFT,   /*!< Transmit FIFO Overflow. */
    kLpuartIntRxFifoUnderflow = LPUART_FIFO_REG_ID << LPUART_SHIFT | LPUART_FIFO_RXUFE_SHIFT,   /*!< Receive FIFO Underflow. */
#endif    
} lpuart_interrupt_t;


/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name LPUART Common Configurations
 * @{
 */

/*!
 * @brief Initializes the LPUART controller to known state.
 *
 * @param base LPUART base pointer.
 */
void LPUART_HAL_Init(LPUART_Type * base);

/*!
 * @brief Enables/disables the LPUART transmitter.
 *
 * @param base LPUART base pointer.
 * @param enable Enable(true) or disable(false) transmitter.
 */
static inline void LPUART_HAL_SetTransmitterCmd(LPUART_Type * base, bool enable)
{
    LPUART_BWR_CTRL_TE(base, enable);
}

/*!
 * @brief Gets the LPUART transmitter enabled/disabled configuration.
 *
 * @param base LPUART base pointer
 * @return State of LPUART transmitter enable(true)/disable(false)
 */
static inline bool LPUART_HAL_GetTransmitterCmd(LPUART_Type * base)
{
    return LPUART_BRD_CTRL_TE(base);
}

/*!
 * @brief Enables/disables the LPUART receiver.
 *
 * @param base LPUART base pointer
 * @param enable Enable(true) or disable(false) receiver.
 */
static inline void LPUART_HAL_SetReceiverCmd(LPUART_Type * base, bool enable)
{
    LPUART_BWR_CTRL_RE(base, enable);
}

/*!
 * @brief Gets the LPUART receiver enabled/disabled configuration.
 *
 * @param base LPUART base pointer
 * @return State of LPUART receiver enable(true)/disable(false)
 */
static inline bool LPUART_HAL_GetReceiverCmd(LPUART_Type * base)
{
    return LPUART_BRD_CTRL_RE(base);
}

/*!
 * @brief Configures the LPUART baud rate.
 *
 *  In some LPUART instances the user must disable the transmitter/receiver
 *  before calling this function.
 *  Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param base LPUART base pointer.
 * @param sourceClockInHz LPUART source input clock in Hz.
 * @param desiredBaudRate LPUART desired baud rate.
 * @return  An error code or kStatus_Success
 */
lpuart_status_t LPUART_HAL_SetBaudRate(LPUART_Type * base,
                                       uint32_t sourceClockInHz,
                                       uint32_t desiredBaudRate);

/*!
 * @brief Sets the LPUART baud rate modulo divisor.
 *
 * @param base LPUART base pointer.
 * @param baudRateDivisor The baud rate modulo division "SBR"
 */
static inline void LPUART_HAL_SetBaudRateDivisor(LPUART_Type * base, uint32_t baudRateDivisor)
{
    assert ((baudRateDivisor < 0x1FFF) && (baudRateDivisor > 1));
    LPUART_BWR_BAUD_SBR(base, baudRateDivisor);
}

#if FSL_FEATURE_LPUART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT
/*!
 * @brief Sets the LPUART baud rate oversampling ratio. Note that this feature is available on select
 *        LPUART instances used together with baud rate programming.
 *        The oversampling ratio should be set between 4x (00011) and 32x (11111). Writing
 *        an invalid oversampling ratio results in an error and is set to a default
 *        16x (01111) oversampling ratio.
 *        IDisable the transmitter/receiver before calling
 *        this function.
 *
 * @param base LPUART base pointer.
 * @param overSamplingRatio The oversampling ratio "OSR"
 */
static inline void LPUART_HAL_SetOversamplingRatio(LPUART_Type * base, uint32_t overSamplingRatio)
{
    assert(overSamplingRatio < 0x1F);
    LPUART_BWR_BAUD_OSR(base, overSamplingRatio);
}
#endif

#if FSL_FEATURE_LPUART_HAS_BOTH_EDGE_SAMPLING_SUPPORT
/*!
 * @brief Configures the LPUART baud rate both edge sampling. Note that this feature is available on select
 *        LPUART instances used with baud rate programming.
 *        When enabled, the received data is sampled on both edges of the baud rate clock.
 *        This must be set when the oversampling ratio is between 4x and 7x.
 *        This function should only be called when the receiver is disabled.
 *
 * @param base LPUART base pointer.
 * @param enable   Enable (1) or Disable (0) Both Edge Sampling
 * @return An error code or kStatus_Success
 */
static inline void LPUART_HAL_SetBothEdgeSamplingCmd(LPUART_Type * base, bool enable)
{
    LPUART_BWR_BAUD_BOTHEDGE(base, enable);
}
#endif

/*!
 * @brief Configures the number of bits per character in the LPUART controller.
 *
 *  In some LPUART instances, the user should disable the transmitter/receiver
 *  before calling this function.
 *  Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param base LPUART base pointer.
 * @param bitCountPerChar  Number of bits per char (8, 9, or 10, depending on the LPUART instance)
 */
void LPUART_HAL_SetBitCountPerChar(LPUART_Type * base, lpuart_bit_count_per_char_t bitCountPerChar);

/*!
 * @brief Configures parity mode in the LPUART controller.
 *
 *  In some LPUART instances, the user should disable the transmitter/receiver
 *  before calling this function.
 *  Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param base LPUART base pointer.
 * @param parityModeType  Parity mode (enabled, disable, odd, even - see parity_mode_t struct)
 */
void LPUART_HAL_SetParityMode(LPUART_Type * base, lpuart_parity_mode_t parityModeType);

/*!
 * @brief Configures the number of stop bits in the LPUART controller.
 *  In some LPUART instances, the user should disable the transmitter/receiver
 *  before calling this function.
 *  Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param base LPUART base pointer.
 * @param stopBitCount Number of stop bits (1 or 2 - see lpuart_stop_bit_count_t struct)
 * @return  An error code (an unsupported setting in some LPUARTs) or kStatus_Success
 */
static inline void LPUART_HAL_SetStopBitCount(LPUART_Type * base, lpuart_stop_bit_count_t stopBitCount)
{
    LPUART_BWR_BAUD_SBNS(base, stopBitCount);
}

/*!
 * @brief  Gets the LPUART transmit/receive data register address.
 *
 * @param base LPUART base pointer.
 * @return  LPUART transmit/receive data register address.
 */
static inline uint32_t LPUART_HAL_GetDataRegAddr(LPUART_Type * base)
{
    return (uint32_t)(&LPUART_DATA_REG(base));
}

/*@}*/

/*!
 * @name LPUART Interrupts and DMA
 * @{
 */

/*!
 * @brief Configures the LPUART module interrupts to enable/disable various interrupt sources.
 *
 * @param   base LPUART module base pointer.
 * @param   interrupt LPUART interrupt configuration data.
 * @param   enable   true: enable, false: disable.
 */
void LPUART_HAL_SetIntMode(LPUART_Type * base, lpuart_interrupt_t interrupt, bool enable);

/*!
 * @brief Returns whether the LPUART module interrupts is enabled/disabled.
 *
 * @param   base LPUART module base pointer.
 * @param   interrupt LPUART interrupt configuration data.
 * @return  true: enable, false: disable.
 */
bool LPUART_HAL_GetIntMode(LPUART_Type * base, lpuart_interrupt_t interrupt);

#if FSL_FEATURE_LPUART_HAS_DMA_ENABLE
/*!
 * @brief  LPUART configures DMA requests for Transmitter and Receiver.
 *
 * @param base LPUART base pointer
 * @param enable Transmit DMA request configuration (enable:1 /disable: 0)
 */
static inline void LPUART_HAL_SetTxDmaCmd(LPUART_Type * base, bool enable)
{
    LPUART_BWR_BAUD_TDMAE(base, enable);
}

/*!
 * @brief  LPUART configures DMA requests for Transmitter and Receiver.
 *
 * @param base LPUART base pointer
 * @param enable Receive DMA request configuration (enable: 1/disable: 0)
 */
static inline void LPUART_HAL_SetRxDmaCmd(LPUART_Type * base, bool enable)
{
    LPUART_BWR_BAUD_RDMAE(base, enable);
}

/*!
 * @brief  Gets the LPUART Transmit DMA request configuration.
 *
 * @param base LPUART base pointer
 * @return Transmit DMA request configuration (enable: 1/disable: 0)
 */
static inline bool LPUART_HAL_IsTxDmaEnabled(LPUART_Type * base)
{
    return LPUART_BRD_BAUD_TDMAE(base);
}

/*!
 * @brief  Gets the LPUART receive DMA request configuration.
 *
 * @param base LPUART base pointer
 * @return Receives the DMA request configuration (enable: 1/disable: 0).
 */
static inline bool LPUART_HAL_IsRxDmaEnabled(LPUART_Type * base)
{
    return LPUART_BRD_BAUD_RDMAE(base);
}

#endif

/*@}*/

/*!
 * @name LPUART Transfer Functions
 * @{
 */

/*!
 * @brief Sends the LPUART 8-bit character.
 *
 * @param base LPUART Instance
 * @param data     data to send (8-bit)
 */
static inline void LPUART_HAL_Putchar(LPUART_Type * base, uint8_t data)
{
    LPUART_WR_DATA(base, data);
}

/*!
 * @brief Sends the LPUART 9-bit character.
 *
 * @param base LPUART Instance
 * @param data     data to send (9-bit)
 */
void LPUART_HAL_Putchar9(LPUART_Type * base, uint16_t data);

/*!
 * @brief Sends the LPUART 10-bit character. Note that this feature is available on select LPUART instances.
 *
 * @param base LPUART Instance
 * @param data   data to send (10-bit)
 * @return An error code or kStatus_Success
 */
lpuart_status_t LPUART_HAL_Putchar10(LPUART_Type * base, uint16_t data);

/*!
 * @brief Gets the LPUART 8-bit character.
 *
 * @param base LPUART base pointer
 * @param readData Data read from receive (8-bit)
 */
static inline void  LPUART_HAL_Getchar(LPUART_Type * base, uint8_t *readData)
{
    *readData = (uint8_t)LPUART_RD_DATA(base);
}

/*!
 * @brief Gets the LPUART 9-bit character.
 *
 * @param base LPUART base pointer
 * @param readData Data read from receive (9-bit)
 */
void LPUART_HAL_Getchar9(LPUART_Type * base, uint16_t *readData);

/*!
 * @brief Gets the LPUART 10-bit character.
 *
 * @param base LPUART base pointer
 * @param readData Data read from receive (10-bit)
 */
void LPUART_HAL_Getchar10(LPUART_Type * base, uint16_t *readData);

/*!
 * @brief Sends out multiple bytes of data using the polling method.
 *
 * This function only supports 8-bit transaction.
 *
 * @param   base LPUART module base pointer.
 * @param   txBuff The buffer pointer which saves the data to be sent.
 * @param   txSize Size of data to be sent in unit of byte.
 */
void LPUART_HAL_SendDataPolling(LPUART_Type * base, const uint8_t *txBuff, uint32_t txSize);

/*!
 * @brief Receives multiple bytes of data using the polling method.
 *
 * This function only supports 8-bit transaction.
 *
 * @param   base LPUART module base pointer.
 * @param   rxBuff The buffer pointer which saves the data to be received.
 * @param   rxSize Size of data need to be received in unit of byte.
 * @return  Whether the transaction is success or receive overrun.
 */
lpuart_status_t LPUART_HAL_ReceiveDataPolling(LPUART_Type * base, uint8_t *rxBuff, uint32_t rxSize);

/*@}*/

/*!
 * @name LPUART Status Flags
 * @{
 */

/*!
 * @brief  LPUART get status flag.
 *
 * @param base LPUART base pointer
 * @param statusFlag  The status flag to query
 * @return Whether the current status flag is set(true) or not(false).
 */
bool LPUART_HAL_GetStatusFlag(LPUART_Type * base, lpuart_status_flag_t statusFlag);

/*!
 * @brief LPUART clears an individual status flag (see lpuart_status_flag_t for list of status bits).
 *
 * @param base LPUART base pointer
 * @param statusFlag  Desired LPUART status flag to clear
 * @return An error code or kStatus_Success
 */
lpuart_status_t LPUART_HAL_ClearStatusFlag(LPUART_Type * base, lpuart_status_flag_t statusFlag);

/*@}*/

/*!
 * @name LPUART Special Feature Configurations
 * @{
 */

/*!
 * @brief Configures the number of idle characters that must be received before the IDLE flag is set.
 *
 * @param base LPUART base pointer
 * @param idleConfig Idle characters configuration
 */
static inline void LPUART_HAL_SetIdleChar(LPUART_Type * base, lpuart_idle_char_t idleConfig)
{
    LPUART_BWR_CTRL_IDLECFG(base, idleConfig);
}

/*!
 * @brief Gets the configuration of the number of idle characters that must be received
 * before the IDLE flag is set.
 *
 * @param base LPUART base pointer
 * @return  idle characters configuration
 */
static inline lpuart_idle_char_t LPUART_HAL_GetIdleChar(LPUART_Type * base)
{
    return (lpuart_idle_char_t)LPUART_BRD_CTRL_IDLECFG(base);
}

/*!
 * @brief  Checks whether the current data word was received with noise.
 *
 * @param base LPUART base pointer.
 * @return The status of the NOISY bit in the LPUART extended data register
 */
static inline bool LPUART_HAL_IsCurrentDataWithNoise(LPUART_Type * base)
{
    return LPUART_BRD_DATA_NOISY(base);
}

/*!
 * @brief Checks whether the current data word was received with frame error.
 *
 * @param base LPUART base pointer
 * @return The status of the FRETSC bit in the LPUART extended data register
 */
static inline bool LPUART_HAL_IsCurrentDataWithFrameError(LPUART_Type * base)
{
    return LPUART_BRD_DATA_FRETSC(base);
}

/*!
 * @brief Indicates a break or that the idle character is to be transmitted
 *        instead of the contents in DATA[T9:T0].
 *
 * @param base LPUART base pointer
 * @param specialChar T9 is used to indicate a break character when 0 an idle
 * character when 1, the contents of DATA[T8:T0] should be zero.
 */
static inline void LPUART_HAL_SetTxSpecialChar(LPUART_Type * base, uint8_t specialChar)
{
    LPUART_BWR_DATA_FRETSC(base, specialChar);
}

/*!
 * @brief Checks whether the current data word was received with parity error.
 *
 * @param base LPUART base pointer
 * @return The status of the PARITYE bit in the LPUART extended data register
 */
static inline bool LPUART_HAL_IsCurrentDataWithParityError(LPUART_Type * base)
{
    return LPUART_BRD_DATA_PARITYE(base);
}

/*!
 * @brief Checks whether the receive buffer is empty.
 *
 * @param base LPUART base pointer
 * @return TRUE if the receive-buffer is empty, else FALSE.
 */
static inline bool LPUART_HAL_IsReceiveBufferEmpty(LPUART_Type * base)
{
    return LPUART_BRD_DATA_RXEMPT(base);
}

/*!
 * @brief Checks whether the previous BUS state was idle before this byte is received.
 *
 * @param base LPUART base pointer
 * @return TRUE if the previous BUS state was IDLE, else FALSE.
 */
static inline bool LPUART_HAL_WasPreviousReceiverStateIdle(LPUART_Type * base)
{
    return LPUART_BRD_DATA_IDLINE(base);
}

/*!
 * @brief Configures the LPUART operation in wait mode (operates or stops operations in wait mode).
 *
 * In some LPUART instances, the user should disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param base LPUART base pointer
 * @param mode     LPUART wait mode operation - operates or stops to operate in wait mode.
 */
static inline void  LPUART_HAL_SetWaitModeOperation(LPUART_Type * base, lpuart_operation_config_t mode)
{
    /* In CPU wait mode: 0 - LPUART clocks continue to run; 1 - LPUART clocks freeze */
    LPUART_BWR_CTRL_DOZEEN(base, mode);
}

/*!
 * @brief Gets the LPUART operation in wait mode (operates or stops operations in wait mode).
 *
 * @param base LPUART base pointer
 * @return LPUART wait mode operation configuration
 *         - kLpuartOperates or KLpuartStops in wait mode
 */
static inline lpuart_operation_config_t LPUART_HAL_GetWaitModeOperation(LPUART_Type * base)
{
    /* In CPU wait mode: 0 - LPUART clocks continue to run; 1 - LPUART clocks freeze  */
    return (lpuart_operation_config_t)LPUART_BRD_CTRL_DOZEEN(base);
}

/*!
 * @brief Configures the LPUART loopback operation (enables/disables the loopback operation).
 *
 * In some LPUART instances, the user should disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param base LPUART base pointer
 * @param enable   LPUART loopback mode - disabled (0) or enabled (1)
 */
void LPUART_HAL_SetLoopbackCmd(LPUART_Type * base, bool enable);

/*!
 * @brief Configures the LPUART single-wire operation (enables/disables the single-wire mode).
 *
 * In some LPUART instances, the user should disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param base LPUART base pointer
 * @param enable   LPUART loopback mode - disabled (0) or enabled (1)
 */
void LPUART_HAL_SetSingleWireCmd(LPUART_Type * base, bool enable);

/*!
 * @brief Configures the LPUART transmit direction while in single-wire mode.
 *
 * @param base LPUART base pointer
 * @param direction LPUART single-wire transmit direction - input or output
 */
static inline void LPUART_HAL_SetTxdirInSinglewireMode(LPUART_Type * base,
                                                 lpuart_singlewire_txdir_t direction)
{
    LPUART_BWR_CTRL_TXDIR(base, direction);
}

/*!
 * @brief  Places the LPUART receiver in standby mode.
 *
 * @param base LPUART base pointer
 * @return Error code or kStatus_Success
 */
lpuart_status_t LPUART_HAL_SetReceiverInStandbyMode(LPUART_Type * base);

/*!
 * @brief  Places the LPUART receiver in a normal mode (disable standby mode operation).
 *
 * @param base LPUART base pointer
 */
static inline void LPUART_HAL_PutReceiverInNormalMode(LPUART_Type * base)
{
    LPUART_BWR_CTRL_RWU(base, 0);
}

/*!
 * @brief  Checks whether the LPUART receiver is in a standby mode.
 *
 * @param base LPUART base pointer
 * @return LPUART in normal more (0) or standby (1)
 */
static inline bool LPUART_HAL_IsReceiverInStandby(LPUART_Type * base)
{
    return LPUART_BRD_CTRL_RWU(base);
}

/*!
 * @brief  LPUART receiver wakeup method (idle line or addr-mark) from standby mode.
 *
 * @param base LPUART base pointer
 * @param method   LPUART wakeup method: 0 - Idle-line wake (default), 1 - addr-mark wake
 */
static inline void LPUART_HAL_SetReceiverWakeupMode(LPUART_Type * base,
                                                    lpuart_wakeup_method_t method)
{
    LPUART_BWR_CTRL_WAKE(base, method);
}

/*!
 * @brief  Gets the LPUART receiver wakeup method (idle line or addr-mark) from standby mode.
 *
 * @param base LPUART base pointer
 * @return  LPUART wakeup method: kLpuartIdleLineWake: 0 - Idle-line wake (default),
 *          kLpuartAddrMarkWake: 1 - addr-mark wake
 */
static inline lpuart_wakeup_method_t LPUART_HAL_GetReceiverWakeupMode(LPUART_Type * base)
{
    return (lpuart_wakeup_method_t)LPUART_BRD_CTRL_WAKE(base);
}

/*!
 * @brief  LPUART idle-line detect operation configuration (idle line bit-count start and wake
 *         up affect on IDLE status bit).
 *
 * In some LPUART instances, the user should disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param base LPUART base pointer
 * @param config   LPUART configuration data for idle line detect operation
 */
void LPUART_HAL_SetIdleLineDetect(LPUART_Type * base,
                                  const lpuart_idle_line_config_t *config);

/*!
 * @brief  LPUART break character transmit length configuration.
 *
 * In some LPUART instances, the user should disable the transmitter before calling
 * this function. Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param base LPUART base pointer
 * @param length   LPUART break character length setting: 0 - minimum 10-bit times (default),
 *                   1 - minimum 13-bit times
 */
static inline void LPUART_HAL_SetBreakCharTransmitLength(LPUART_Type * base,
                                             lpuart_break_char_length_t length)
{
    LPUART_BWR_STAT_BRK13(base, length);
}

/*!
 * @brief  LPUART break character detect length configuration.
 *
 * @param base LPUART base pointer
 * @param length  LPUART break character length setting: 0 - minimum 10-bit times (default),
 *                  1 - minimum 13-bit times
 */
static inline void LPUART_HAL_SetBreakCharDetectLength(LPUART_Type * base,
                                           lpuart_break_char_length_t length)
{
    LPUART_BWR_STAT_LBKDE(base, length);
}

/*!
 * @brief  LPUART transmit sends break character configuration.
 *
 * @param base LPUART base pointer
 * @param enable LPUART normal/queue break char - disabled (normal mode, default: 0) or
 *                 enabled (queue break char: 1)
 */
static inline void LPUART_HAL_QueueBreakCharToSend(LPUART_Type * base, bool enable)
{
    LPUART_BWR_CTRL_SBK(base, enable);
}

/*!
 * @brief LPUART configures match address mode control.
 *
 * @param base LPUART base pointer
 * @param config MATCFG: Configures the match addressing mode used.
 */
static inline void LPUART_HAL_SetMatchAddressMode(LPUART_Type * base, lpuart_match_config_t config)
{
    LPUART_BWR_BAUD_MATCFG(base, config);
}

/*!
 * @brief Configures address match register 1.
 *
 * The MAEN bit must be cleared before configuring the MA value. Therefore, the enable/disable
 * and set value must be included inside one function.
 *
 * @param base LPUART base pointer
 * @param enable Match address model enable (true)/disable (false)
 * @param value Match address value to program into match address register 1
 */
void LPUART_HAL_SetMatchAddressReg1(LPUART_Type * base, bool enable, uint8_t value);

/*!
 * @brief Configures address match register 2.
 *
 * The MAEN bit must be cleared before configuring MA value. Therefore, the enable/disable
 * and set value must be included inside one function.
 *
 * @param base LPUART base pointer
 * @param enable Match address model enable (true)/disable (false)
 * @param value Match address value to program into match address register 2
 */
void LPUART_HAL_SetMatchAddressReg2(LPUART_Type * base, bool enable, uint8_t value);

/*!
 * @brief LPUART sends the MSB first configuration.
 *
 * In some LPUART instances, the user should disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * @param base LPUART base pointer
 * @param enable  false - LSB (default, disabled), true - MSB (enabled)
 */
static inline void LPUART_HAL_SetSendMsbFirstCmd(LPUART_Type * base, bool enable)
{
    LPUART_BWR_STAT_MSBF(base, enable);
}

/*!
 * @brief  LPUART enable/disable re-sync of received data configuration.
 *
 * @param base LPUART base pointer
 * @param enable  re-sync of received data word configuration:
 *                true - re-sync of received data word (default)
 *                false - disable the re-sync
 */
static inline void LPUART_HAL_SetReceiveResyncCmd(LPUART_Type * base, bool enable)
{
    /* When disabled, the resynchronization of the received data word when a data
     * one followed by data zero transition is detected. This bit should only be
     * changed when the receiver is disabled. */
    LPUART_BWR_BAUD_RESYNCDIS(base, enable);
}

#if FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT
/*!
 * @brief  Transmits the CTS source configuration.
 *
 * @param base LPUART base pointer
 * @param source   LPUART CTS source
 */
static inline void LPUART_HAL_SetCtsSource(LPUART_Type * base,
                                           lpuart_cts_source_t source)
{
    LPUART_BWR_MODIR_TXCTSSRC(base, source);
}

/*!
 * @brief  Transmits the CTS configuration.
 *
 * Note: configures if the CTS state is checked at the start of each character
 * or only when the transmitter is idle.
 *
 * @param base LPUART base pointer
 * @param mode     LPUART CTS configuration
 */
static inline void LPUART_HAL_SetCtsMode(LPUART_Type * base, lpuart_cts_config_t mode)
{
    LPUART_BWR_MODIR_TXCTSC(base, mode);
}

/*!
 * @brief Enables/disables the transmitter clear-to-send.
 *
 * @param base LPUART base pointer
 * @param enable  disable(0)/enable(1) transmitter CTS.
 */
static inline void LPUART_HAL_SetTxCtsCmd(LPUART_Type * base, bool enable)
{
    LPUART_BWR_MODIR_TXCTSE(base, enable);
}

/*!
 * @brief  Enables/disables the receiver request-to-send.
 *
 * Note: do not enable both Receiver RTS (RXRTSE) and Transmit RTS (TXRTSE).
 *
 * @param base LPUART base pointer
 * @param enable  disable(0)/enable(1) receiver RTS.
 */
static inline void LPUART_HAL_SetRxRtsCmd(LPUART_Type * base, bool enable)
{
    LPUART_BWR_MODIR_RXRTSE(base, enable);
}

/*!
 * @brief  Enables/disables the transmitter request-to-send.
 * Note: do not enable both Receiver RTS (RXRTSE) and Transmit RTS (TXRTSE).
 *
 * @param base LPUART base pointer
 * @param enable  disable(0)/enable(1) transmitter RTS.
 */
static inline void LPUART_HAL_SetTxRtsCmd(LPUART_Type * base, bool enable)
{
    LPUART_BWR_MODIR_TXRTSE(base, enable);
}

/*!
 * @brief Configures the transmitter RTS polarity.
 *
 * @param base LPUART base pointer
 * @param polarity Settings to choose RTS polarity (0=active low, 1=active high)
 */
static inline void LPUART_HAL_SetTxRtsPolarityMode(LPUART_Type * base, bool polarity)
{
    LPUART_BWR_MODIR_TXRTSPOL(base, polarity);
}

#endif  /* FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT */

#if FSL_FEATURE_LPUART_HAS_IR_SUPPORT
/*!
 * @brief  Configures the LPUART infrared operation.
 *
 * @param base LPUART base pointer
 * @param enable    Enable (1) or disable (0) the infrared operation
 * @param pulseWidth The transmit narrow pulse width of type lpuart_ir_tx_pulsewidth_t
 */
void LPUART_HAL_SetInfrared(LPUART_Type * base, bool enable,
                            lpuart_ir_tx_pulsewidth_t pulseWidth);
#endif  /* FSL_FEATURE_LPUART_HAS_IR_SUPPORT */

/*!
 * @name LPUART FIFO Configurations
 * @{
 */

#if FSL_FEATURE_LPUART_HAS_FIFO
/*!
 * @brief  Enables or disable the LPUART transmit FIFO.
 *
 * This function allows the user to enable or disable the LPUART transmit FIFO.
 * It is required that the transmitter/receiver be disabled before calling this function
 * when the FIFO is empty.
 * Additionally, TXFLUSH and RXFLUSH commands should be issued after calling this function.
 *
 * @param base LPUART module base pointer.
 * @param enable Enable or disable Tx FIFO.
 * @return Error code if it is detected that the transmitter or receiver is enabled or
 *         kStatus_LPUART_Success.
 */
lpuart_status_t LPUART_HAL_SetTxFifoCmd(LPUART_Type * base, bool enable);

/*!
 * @brief  Enables or disables the LPUART receive FIFO.
 *
 * This function allows the user to enable or disable the LPUART receive FIFO.
 * It is required that the transmitter/receiver be disabled before calling this function
 * when the FIFO is empty.
 * Additionally, TXFLUSH and RXFLUSH commands should be issued after calling this function.
 *
 * @param base LPUART module base pointer.
 * @param enable Enable or disable Rx FIFO.
 * @return Error code if it is detected that the transmitter or receiver is enabled or
 *         kStatus_LPUART_Success.
 */
lpuart_status_t LPUART_HAL_SetRxFifoCmd(LPUART_Type * base, bool enable);

/*!
 * @brief  Gets the size of the LPUART transmit FIFO.
 *
 * This function returns the size (number of entries) supported in the LPUART transmit FIFO for
 * a particular module base.
 *
 * @param base LPUART module base pointer.
 * @return  The LPUART transmit FIFO size as follows:
 *    0x0: 1 data word; 0x1: 4 data words; 0x2: 8 data words; 0x3: 16 data words
 *    0x4: 32 data words; 0x5: 64 data words; 0x6: 128 data words; 0x7: 256 data words
 */
static inline uint8_t LPUART_HAL_GetTxFifoSize(LPUART_Type * base)
{
    return LPUART_BRD_FIFO_TXFIFOSIZE(base);
}

/*!
 * @brief  Gets the size of the LPUART receive FIFO.
 *
 * This function returns the size (number of entries) supported in the LPUART receive FIFO for
 * a particular module base.
 *
 * @param   base LPUART module base pointer.
 * @return  The receive FIFO size as follows:
 *    0x0: 1 data word; 0x1: 4 data words; 0x2: 8 data words; 0x3: 16 data words
 *    0x4: 32 data words; 0x5: 64 data words; 0x6: 128 data words; 0x7: 256 data words
 */
static inline uint8_t LPUART_HAL_GetRxFifoSize(LPUART_Type * base)
{
    return LPUART_BRD_FIFO_RXFIFOSIZE(base);
}

/*!
 * @brief  Flushes the LPUART transmit FIFO.
 *
 * This function allows the user to flush the LPUART transmit FIFO for a particular module base.
 * Flushing the FIFO may result in data loss.
 * It is recommended that the transmitter be disabled before calling this function.
 *
 * @param base LPUART module base pointer.
 * @return Error code if it is detected that the transmitter or receiver is enabled or
 *         kStatus_LPUART_Success.
 */
lpuart_status_t LPUART_HAL_FlushTxFifo(LPUART_Type * base);

/*!
 * @brief  Flushes the LPUART receive FIFO.
 *
 * This function allows the user to flush the LPUART receive FIFO for a particular module base.
 * Flushing the FIFO may result in data loss.
 * It is recommended that the receiver be disabled before calling this function.
 *
 * @param base LPUART module base pointer.
 * @return Error code if it is detected that the transmitter or receiver is enabled or
 *         kStatus_LPUART_Success.
 */
lpuart_status_t LPUART_HAL_FlushRxFifo(LPUART_Type * base);

/*!
 * @brief  Gets the LPUART transmit FIFO empty status state.
 *
 * The function returns the state of the transmit FIFO empty status state, but does not take into
 * account data in the shift register.
 *
 * @param   base LPUART module base pointer.
 * @return  The LPUART transmit FIFO empty status: true=empty; false=not-empty.
 */
static inline bool LPUART_HAL_IsTxFifoEmpty(LPUART_Type * base)
{
    return LPUART_BRD_FIFO_TXEMPT(base);
}

/*!
 * @brief  Gets the LPUART receive FIFO empty status state.
 *
 * The function returns the state of the receive FIFO empty status state, but does not take into
 * account data in the shift register.
 *
 * @param   base LPUART module base pointer.
 * @return  The LPUART receive FIFO empty status: true=empty; false=not-empty.
 */
static inline bool LPUART_HAL_IsRxFifoEmpty(LPUART_Type * base)
{
    return LPUART_BRD_FIFO_RXEMPT(base);
}

/*!
 * @brief  Configures the LPUART receiver idle empty enable value.
 *
 * The function enables configuration of the assertion of RDRF when the receiver is idle for a number of idle characters and the
 * FIFO is not empty.
 *
 * @param   base LPUART module base pointer.
 * @param   config Configures the number of idle characters that asserts RDRF.
 * @return  Error code if transmitter is enabled or kStatus_LPUART_Success.
 */
lpuart_status_t LPUART_HAL_SetRxIdleEmpty(LPUART_Type * base, lpuart_rx_idle_empty_config_t config);

/*!
 * @brief  Gets the LPUART receiver idle empty enable value.
 *
 * @param   base LPUART module base pointer.
 * @return  Current number of idle characters that asserts RDRF.
 */
static inline lpuart_rx_idle_empty_config_t LPUART_HAL_GetRxIdleEmpty(LPUART_Type * base)
{
    return (lpuart_rx_idle_empty_config_t)LPUART_BRD_FIFO_RXIDEN(base);
}

/*!
 * @brief  Sets the LPUART transmit FIFO watermark value.
 *
 * Programming the transmit watermark should be done when LPUART the transmitter is disabled
 * and the value must be set less than the size obtained from LPUART_HAL_GetTxFifoSize.
 *
 * @param   base LPUART module base pointer.
 * @param   watermark  The LPUART transmit watermark value to be programmed.
 * @return  Error code if transmitter is enabled or kStatus_LPUART_Success.
 */
lpuart_status_t LPUART_HAL_SetTxFifoWatermark(LPUART_Type * base, uint8_t watermark);

/*!
 * @brief  Gets the LPUART transmit FIFO watermark value.
 *
 * @param   base LPUART module base pointer.
 * @return  The value currently programmed for the LPUART transmit watermark.
 */
static inline uint8_t LPUART_HAL_GetTxFifoWatermark(LPUART_Type * base)
{
    return LPUART_BRD_WATER_TXWATER(base);
}

/*!
 * @brief  Gets the LPUART transmit FIFO data word count (number of words in the transmit FIFO).
 *
 * The function LPUART_HAL_GetTxDatawordCountInFifo excludes any data that may
 * be in the LPUART transmit shift register.
 *
 * @param   base LPUART module base pointer.
 * @return  The number of data words currently in the LPUART transmit FIFO.
 */
static inline uint8_t LPUART_HAL_GetTxDatawordCountInFifo(LPUART_Type * base)
{
    return LPUART_BRD_WATER_TXCOUNT(base);
}

/*!
 * @brief  Sets the LPUART receive FIFO watermark value.
 *
 * Programming the receive watermark should be done when the receiver is disabled
 * and the value must be set less than the size obtained from LPUART_HAL_GetRxFifoSize and
 * greater than zero.
 *
 * @param   base LPUART module base pointer.
 * @param  watermark  The LPUART receive watermark value to be programmed.
 * @return  Error code if receiver is enabled or kStatus_LPUART_Success.
 */
lpuart_status_t LPUART_HAL_SetRxFifoWatermark(LPUART_Type * base, uint8_t watermark);

/*!
 * @brief  Gets the LPUART receive FIFO data word count (number of words in the receive FIFO).
 *
 * The function LPUART_HAL_GetRxDatawordCountInFifo excludes any data that may be
 * in the receive shift register.
 *
 * @param   base LPUART module base pointer.
 * @return  The number of data words currently in the LPUART receive FIFO.
 */
static inline uint8_t LPUART_HAL_GetRxDatawordCountInFifo(LPUART_Type * base)
{
    return LPUART_BRD_WATER_RXCOUNT(base);
}

/*!
 * @brief  Gets the LPUART receive FIFO watermark value.
 *
 * @param   base LPUART module base pointer.
 * @return  The value currently programmed for the LPUART receive watermark.
 */
static inline uint8_t LPUART_HAL_GetRxFifoWatermark(LPUART_Type * base)
{
    return LPUART_BRD_WATER_RXWATER(base);
}

#endif  /* FSL_FEATURE_LPUART_HAS_FIFO*/

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_LPUART_HAL_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

