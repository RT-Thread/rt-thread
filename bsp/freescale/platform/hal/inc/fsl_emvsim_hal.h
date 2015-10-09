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
#ifndef __FSL_EMVSIM_HAL_H__
#define __FSL_EMVSIM_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup emvsim_hal
 * @{
 */

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Module basic parameter selections */
typedef enum _emvsim_module_param {
    kEmvsimParamVersion = 0U,  /*!< Module version @internal gui name="1" */
    kEmvsimParamTxFifoSize = 1U,  /*!< Transmit FIFO size @internal gui name="2" */
    kEmvsimParamRxFifoSize = 2U,  /*!< Receive FIFO size @internal gui name="3" */
} emvsim_module_param_t;

/*! @brief General Purpose Counter clock selections */
typedef enum _emvsim_gpc_clock_select {
    kEmvsimGPCClockDisable = 0U,  /*!< Disabled @internal gui name="1" */
    kEmvsimGPCCardClock = 1U,  /*!< Card clock @internal gui name="2" */
    kEmvsimGPCRxClock = 2U,  /*!< Receive clock @internal gui name="3" */
    kEmvsimGPCTxClock = 3U,  /*!< Transmit ETU clock @internal gui name="4" */
} emvsim_gpc_clock_select_t;

/*! @brief CRC bit flip control */
typedef enum _emvsim_crc_flip_control {
    kEmvsimCrcNoFlip = 0U,  /*!< Bits are not  reversed @internal gui name="1" */
    kEmvsimCrcFlip = 1U,  /*!< Bits  are reversed @internal gui name="2" */
} emvsim_crc_flip_control_t;

/*! @brief CRC bit inversion control */
typedef enum _emvsim_crc_inv_control {
    kEmvsimCrcNoInv = 0U,  /*!< Bits are not inverted @internal gui name="1" */
    kEmvsimCrcInv = 1U,  /*!< Bits are inverted @internal gui name="2" */
} emvsim_crc_inv_control_t;

/*! @brief EMVSIM STOP instruction clock control */
typedef enum _emvsim_stop_clock_control {
    kEmvsimStopDownAllClocks = 0U,  /*!< Shut down all clocks @internal gui name="1" */
    kEmvsimStopDownAllButCardClock = 1U,  /*!< Shut down all but card clock @internal gui name="2" */
} emvsim_stop_clock_control_t;

/*! @brief EMVSIM DOZE instruction clock control */
typedef enum _emvsim_doze_clock_control {
    kEmvsimDozeDownAllClocks = 0U,  /*!< Shut down all clocks @internal gui name="1" */
    kEmvsimDozeDownNoClocks = 1U,  /*!< Don't shut down clocks @internal gui name="2" */
} emvsim_doze_clock_control_t;

/*! @brief EMVSIM data convention */
typedef enum _emvsim_data_convention {
    kEmvsimDirectConvention = 0U,  /*!< Direct convention @internal gui name="1" */
    kEmvsimInverseConvention = 1U,  /*!< Inverse convention @internal gui name="2" */
} emvsim_data_convention_t;

/*! @brief EMVSIM character mode */
typedef enum _emvsim_character_mode {
    kEmvsimCharacter12EtuMode = 0U,  /*!< 12 ETU character mode @internal gui name="1" */
    kEmvsimCharacter11EtuMode = 1U,  /*!< 11 ETU character mode @internal gui name="2" */
} emvsim_character_mode_t;

/*! @brief EMVSIM Control functions */
typedef enum _emvsim_control {
    kEmvsimCtrlInverseConvention = 0U,    /*!< Select direct or inverse convention @internal gui name="1" */
    kEmvsimCtrlinitialCharacterMode = 1U, /*!< Enable/disable initial character detection @internal gui name="2" */
    kEmvsimCtrlANACKEnable = 2U,          /*!< Enable/disable Auto NACK function @internal gui name="3" */
    kEmvsimCtrlONACKEnable = 3U,          /*!< Enable/disable NACK on Overflow function @internal gui name="4" */
    kEmvsimCtrlFlushRx = 8U,              /*!< Reset receiver or in normal operation @internal gui name="5" */
    kEmvsimCtrlFlushTx = 9U,              /*!< Reset transmitter or in normal operation @internal gui name="6" */
    kEmvsimCtrlSwRst = 10U,               /*!< Reset EMVSIM or in normal operation @internal gui name="7" */
    kEmvsimCtrlKillClocks = 11U,          /*!< Enable/disable EMVSIM input clock @internal gui name="8" */
    kEmvsimCtrlDozeEnable = 12U,          /*!< Enable/disable DOZE instruction effect on clocks @internal gui name="9" */
    kEmvsimCtrlStopEnable = 13U,          /*!< Enable/disable STOP instruction effect on clocks @internal gui name="10" */
    kEmvsimCtrlReceiverEnable = 16U,      /*!< Enable/disable receiver @internal gui name="11" */
    kEmvsimCtrlTransmitterEnable = 17U,   /*!< Enable/disable transmitter @internal gui name="12" */
    kEmvsimCtrlRcvr11ModeEnable = 18U,    /*!< Configure receiver in 12 or 11 etu mode @internal gui name="13" */
    kEmvsimCtrlRxDmaEnable = 19U,         /*!< Enable/disable receiver DMA @internal gui name="14" */
    kEmvsimCtrlTxDmaEnable = 20U,         /*!< Enable/disable transmitter DMA @internal gui name="15" */
    kEmvsimCtrlInvertCrcOutput = 24U,     /*!< Controls CRC output to be inverted or not @internal gui name="16" */
    kEmvsimCtrlFlipCrcOutput = 25U,       /*!< Controls CRC output to be flipped or not @internal gui name="17" */
    kEmvsimCtrlFlipCrcInput = 26U,        /*!< Controls CRC input to be flipped or not @internal gui name="18" */
    kEmvsimCtrlCWTEnable = 27U,           /*!< Enable/disable CWT timer @internal gui name="19" */
    kEmvsimCtrlLrcEnable = 28U,           /*!< Enable/disable LRC operation @internal gui name="20" */
    kEmvsimCtrlCrcEnable = 29U,           /*!< Enable/disable CRC operation @internal gui name="21" */
    kEmvsimCtrlXmtCrcOrLrcEnable = 30U,   /*!< Enable/disable CRC or LRC operation in transmission @internal gui name="22" */
    kEmvsimCtrlBWTEnable = 31U,           /*!< Enable/disable BWT timer @internal gui name="23" */
} emvsim_control_t;

/*! @brief EMVSIM interrupt status/reasons */
typedef enum _emvsim_interrupt {
    kEmvsimIntRxData    = 0U, /*!< Receive data interrupt */
    kEmvsimIntGPCnt1    = 1U, /*!< General purpose counter 1 timeout interrupt */
    kEmvsimIntBGTErr    = 2U, /*!< Block guard time error interrupt */
    kEmvsimIntBWTErr    = 3U, /*!< Block wait time error interrupt */
    kEmvsimIntRxNackThreshold    = 4U, /*!< Receiver NACK threshold interrupt */
    kEmvsimIntCWTErr    = 5U, /*!< Character wait time error interrupt */
    kEmvsimIntGPCnt0    = 6U, /*!< General purpose counter 0 timeout interrupt */
    kEmvsimIntTxDataThreshold    = 7U, /*!< Transmit data threshold interrupt */
    kEmvsimIntTxFIFOFull    = 8U, /*!< Transmit FIFO full interrupt */
    kEmvsimIntTxNackThresold    = 9U, /*!< Transmit NACK threshold interrupt */
    kEmvsimIntTxFIFOEmpty    = 10U, /*!< Transmit FIFO empty interrupt */
    kEmvsimIntEarlyTxComplete    = 11U, /*!< Early transmit complete interrupt */
    kEmvsimIntRxFIFOOverflow    = 12U, /*!< Receive FIFO overflow interrupt */
    kEmvsimIntTxComplete    = 13U, /*!< Transmit complete interrupt */
    kEmvsimIntRxDataThreshold    = 14U, /*!< Receive data threshold interrupt */
    kEmvsimIntPresenceDetect    = 15U, /*!< Card presence detect interrupt */
} emvsim_interrupt_t;

/*! @brief EMVSIM receive status flags */
typedef enum _emvsim_rx_status {
    kEmvsimFrameErr    = 0U, /*!< Frame error flag */
    kEmvsimParityErr    = 1U, /*!< Parity error flag */
    kEmvsimBGTErr    = 2U, /*!< Block guard time error flag */
    kEmvsimBWTErr    = 3U, /*!< Block wait time error flag */
    kEmvsimRxNackThresholdErr    = 4U, /*!< Received NACK threshold error flag */
    kEmvsimCWTErr    = 5U, /*!< Character wait time error flag */
    kEmvsimCRCCheckOk    = 6U, /*!< CRC check OK flag */
    kEmvsimLRCCheckOk    = 7U, /*!< LRC check OK flag */
    kEmvsimRxDataThreshold    = 8U, /*!< Received data threshold interrupt flag */
    kEmvsimRxData    = 9U, /*!< Receive data interrupt flag */
    kEmvsimRxDataOverflow    = 10U, /*!< Receive data overflow flag */
    kEmvsimRxAllStatus = 11U, /*!< All receive status flags */
} emvsim_rx_status_t;

/*! @brief EMVSIM transmit status flags */
typedef enum _emvsim_tx_status {
    kEmvsimGPCNT1Timeout    = 0U, /*!< General purpose counter 1 timeout flag */
    kEmvsimGPCNT0Timeout    = 1U, /*!< General purpose counter 0 timeout flag */
    kEmvsimTxDataThreshold    = 2U, /*!< Transmit data threshold flag */
    kEmvsimTxFIFOFull    = 3U, /*!< Transmit FIFO full flag */
    kEmvsimTxComplete    = 4U, /*!< Transmit complete flag */
    kEmvsimEarlyTxComplete    = 5U, /*!< Early transmit complete flag */
    kEmvsimTxFIFOEmpty    = 6U, /*!< Transmit FIFO empty flag */
    kEmvsimTxNackThresholdErr    = 7U, /*!< Transmit NACK threshold error flag */
    kEmvsimTxAllStatus = 8U, /*!< All transmit status flags */
} emvsim_tx_status_t;

/*! @brief EMVSIM card presence detection edge control */
typedef enum _presence_detect_edge {
    kEmvsimPDOnFallingEdge    = 0U, /*!< Presence detected on falling edge */
    kEmvsimPDOnRisingEdge    = 1U, /*!< Presence detected on rising edge */
} emvsim_presence_detect_edge_t;

/*! @brief EMVSIM card presence detection status */
typedef enum _presence_detect_status {
    kEmvsimPDPinIsLow    = 0U, /*!< Presence detected pin is logic low */
    kEmvsimPDPinIsHigh    = 1U, /*!< Presence detected pin is logic high */
} emvsim_presence_detect_status_t;

/*! @brief EMVSIM card clock polarity control when card clock is disabled */
typedef enum _card_clock_stop_polarity {
    kEmvsimCardClockStopPolarityIsLow    = 0U, /*!< Card clock stop polarity is logic low */
    kEmvsimCardClockStopPolarityIsHigh    = 1U, /*!< Card clock stop polarity is logic high */
} emvsim_card_clock_stop_polarity_t;

/*! @brief EMVSIM card reset control */
typedef enum _reset_card {
    kEmvsimResetAssert    = 0U, /*!< Smart card reset is assert */
    kEmvsimResetDeassert    = 1U, /*!< Smart card reset de-assert */
} emvsim_reset_card_t;

/*! @brief EMVSIM card voltage enable signal polarity control */
typedef enum _vcc_en_polarity {
    kEmvsimVccEnIsHigh    = 0U, /*!< VCC_EN polarity is active high */
    kEmvsimVccEnIsLow    = 1U, /*!< VCC_EN polarity is active low */
} emvsim_vcc_en_polarity_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name EMVSIM Common Configurations
 * @{
 */

/*!
 * @brief Initializes the EMVSIM controller.
 *
 * This function initializes the module to a known state.
 *
 * @param   base EMVSIM module base pointer.
 */
void EMVSIM_HAL_Init(EMVSIM_Type * base);

/*!
 * @brief Returns the EMVSIM controller version, transmit and receive FIFO sizes.
 *
 * This function returns the EMVSIM controller version and transmit and receive FIFO sizes.
 *
 * @param   base EMVSIM module base pointer.
 * @param   param Parameter type.
 * @returns Version number, transmit or receive FIFO sizes.
 */
uint32_t EMVSIM_HAL_GetModuleParameter(EMVSIM_Type * base, emvsim_module_param_t param);

/*!
 * @brief Returns the EMVSIM controller transmit FIFO size.
 *
 * This function returns the EMVSIM transmit FIFO size.
 *
 * @param   base EMVSIM module base pointer.
 * @return  Transmit FIFO size.
 */
static inline uint8_t EMVSIM_HAL_GetTxFifoSize(EMVSIM_Type * base)
{
    return EMVSIM_RD_PARAM_TX_FIFO_DEPTH(base);
}

/*!
 * @brief Returns the EMVSIM controller receive FIFO size.
 *
 * This function returns the EMVSIM receive FIFO size.
 *
 * @param   base EMVSIM module base pointer.
 * @return  Receive FIFO size.
 */
static inline uint8_t EMVSIM_HAL_GetRxFifoSize(EMVSIM_Type * base)
{
    return EMVSIM_RD_PARAM_RX_FIFO_DEPTH(base);
}

/*!
 * @brief Selects the EMVSIM general purpose counter clock.
 *
 * This function selects the clock for the general purpose counters.
 *
 * @param   base EMVSIM module base pointer.
 * @param   gpcNumber General purpose counter number.
 * @param   gpcClockSel Clock selection input.
 */
void EMVSIM_HAL_SetGPCClockSelect(EMVSIM_Type * base, uint8_t gpcNumber, emvsim_gpc_clock_select_t gpcClockSel);

/*!
 * @brief Sets the clock prescaler for the EMVSIM controller.
 *
 * This function sets the clock prescaler value of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   prescaler Clock prescaler value.
 */
static inline void EMVSIM_HAL_SetClockPrescaler(EMVSIM_Type * base, uint8_t prescaler)
{
    EMVSIM_WR_CLKCFG_CLK_PRSC(base, prescaler);
}

/*!
 * @brief Sets the baudrate divisor for the EMVSIM controller.
 *
 * This function sets the baudrate divisor value of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   divisor Baudrate divisor value. 
 */
static inline void EMVSIM_HAL_SetBaudrateDivisor(EMVSIM_Type * base, uint16_t divisor)
{
    EMVSIM_WR_DIVISOR_DIVISOR_VALUE(base, (divisor & 0x1FFU));
}

/*!
 * @brief Enables/disables different control functions of the EMVSIM controller.
 *
 * This function enables/disables different control functions of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   control Control functions as described in emvsim_control_t
 * @param   enable Enable/disable control function
 */
void EMVSIM_HAL_SetControl(EMVSIM_Type * base, emvsim_control_t control, bool enable);

/*!
 * @brief Returns the current state of different control functions of the EMVSIM controller.
 *
 * This function returns the current state of different control functions of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   control Control functions as described in emvsim_control_t
 * @returns true - The control function is enabled
 *          false - The control function is disabled
 */
bool EMVSIM_HAL_GetControl(EMVSIM_Type * base, emvsim_control_t control);

/*!
 * @brief Enables/disables the EMVSIM controller interrupt reasons to raise an interrupt.
 *
 * This function enables/disables the different interrupt reasons of the 
 * EMVSIM controller to raise an interrupt.
 *
 * @param   base EMVSIM module base pointer.
 * @param   interrupt - interrupt reasons
 * @param   enable true - enable interrupt (unmask)
 *                 false - disable interrupt (mask)
 */
void EMVSIM_HAL_SetIntMode(EMVSIM_Type *base, emvsim_interrupt_t interrupt, bool enable);

/*!
 * @brief Returns whether different interrupt reasons are masked or unmasked in the 
 * EMVSIM controller.
 *
 * This function returns whether different interrupt masks are enabled/disabled 
 * for different interrupt reasons of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   interrupt - interrupt reasons
 * @returns true - interrupt enabled (unmasked)
 *          false - interrupt disabled (masked)
 */
bool EMVSIM_HAL_GetIntMode(EMVSIM_Type *base, emvsim_interrupt_t interrupt);

/*!
 * @brief Sets the receiver NACK threshold value of the EMVSIM controller.
 *
 * This function sets a value for the receiver NACK threshold in the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   rnackThreshold Receiver NACK threshold value
 */
static inline void EMVSIM_HAL_SetReceiverNackThreshold(EMVSIM_Type *base, uint8_t rnackThreshold)
{
    EMVSIM_WR_RX_THD_RNCK_THD(base, (rnackThreshold & 0xFU));
}

/*!
 * @brief Returns the receiver NACK threshold value of the EMVSIM controller.
 *
 * This function returns the value for the receiver NACK threshold in the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns Receiver NACK threshold value
 */
static inline uint8_t EMVSIM_HAL_GetReceiverNackThreshold(EMVSIM_Type *base)
{
    return (EMVSIM_RD_RX_THD_RNCK_THD(base) & 0xFU);
}

/*!
 * @brief Sets the receiver data threshold value of the EMVSIM controller.
 *
 * This function sets a value for the receiver data threshold value in the 
 * EMVSIM controller, i.e., the number of bytes that must exist in the 
 * receive FIFO to trigger the corresponding interrupt flag.
 *
 * @param   base EMVSIM module base pointer.
 * @param   rdt Receiver data threshold value
 */
static inline void EMVSIM_HAL_SetReceiverDataThreshold(EMVSIM_Type *base, uint8_t rdt)
{
    EMVSIM_WR_RX_THD_RDT(base, (rdt & 0xFU));
}

/*!
 * @brief Returns the receiver data threshold value of the EMVSIM controller.
 *
 * This function returns the value for the receiver data threshold value in the 
 * EMVSIM controller, i.e., the number of bytes that must exist in the 
 * receive FIFO to trigger the corresponding interrupt flag.
 *
 * @param   base EMVSIM module base pointer.
 * @returns Receiver data threshold value
 */
static inline uint8_t EMVSIM_HAL_GetReceiverDataThreshold(EMVSIM_Type *base)
{
    return (EMVSIM_RD_RX_THD_RDT(base) & 0xFU);
}

/*!
 * @brief Sets the transmitter NACK threshold value of the EMVSIM controller.
 *
 * This function sets a value for the transmitter NACK threshold value in the 
 * EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   tnackThreshold Transmitter NACK threshold value
 */
static inline void EMVSIM_HAL_SetTransmitterNackThreshold(EMVSIM_Type *base, uint8_t tnackThreshold)
{
    EMVSIM_WR_TX_THD_TNCK_THD(base, (tnackThreshold & 0xFU));
}

/*!
 * @brief Returns the transmitter NACK threshold value of the EMVSIM controller.
 *
 * This function returns the value for the transmitter NACK threshold value in the 
 * EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns Transmitter NACK threshold value
 */
static inline uint8_t EMVSIM_HAL_GetTransmitterNackThreshold(EMVSIM_Type *base)
{
    return (EMVSIM_RD_TX_THD_TNCK_THD(base) & 0xFU);
}

/*!
 * @brief Sets the transmitter data threshold value of the EMVSIM controller.
 *
 * This function sets a value for the transmitter data threshold value in the 
 * EMVSIM controller, i.e., the the threshold value for the transmit FIFO 
 * at which the corresponding interrupt flag is set.
 *
 * @param   base EMVSIM module base pointer.
 * @param   tdt Transmitter data threshold value
 */
static inline void EMVSIM_HAL_SetTransmitterDataThreshold(EMVSIM_Type *base, uint8_t tdt)
{
    EMVSIM_WR_TX_THD_TDT(base, (tdt & 0xFU));
}

/*!
 * @brief Returns the transmitter data threshold value of EMVSIM controller.
 *
 * This function returns the value for transmitter data threshold value in the 
 * EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns Transmitter data threshold value
 */
static inline uint8_t EMVSIM_HAL_GetTransmitterDataThreshold(EMVSIM_Type *base)
{
    return (EMVSIM_RD_TX_THD_TDT(base) & 0xFU);
}

/*!
 * @brief Returns the state of the received FIFO (either empty or has bytes to read from EMVSIM controller).
 *
 * This function the state of receive FIFO (either empty or has bytes to read from the
 * EMVSIM controller).
 *
 * @param   base EMVSIM module base pointer.
 * @returns true - Receive FIFO is empty
 *          false - Receive FIFO has bytes to read.
 */
static inline bool EMVSIM_HAL_IsReceiveFifoEmpty(EMVSIM_Type *base)
{
    return (bool)(EMVSIM_RD_RX_STATUS_RX_CNT(base) > 0)?false:true;
}

/*!
 * @brief Returns the state of the transmitted FIFO (either full or bytes can be written 
 * into the transmit FIFO of the EMVSIM controller).
 *
 * This function returns the state of the transmitted FIFO (either full or bytes can be 
 * written into the transmit FIFO of the EMVSIM controller).
 *
 * @param   base EMVSIM module base pointer.
 * @returns true - Transmit FIFO is full
 *          false - Data bytes can be written into transmit FIFO
 */
static inline bool EMVSIM_HAL_IsTransmitFifoFull(EMVSIM_Type *base)
{
    return (bool)(( EMVSIM_RD_TX_STATUS_TX_CNT(base) == EMVSIM_RD_PARAM_TX_FIFO_DEPTH(base))?true:false);
    
}

/*!
 * @brief Returns the receive status of the EMVSIM controller.
 *
 * This function returns the receive status of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   rxStatus Indicates a particular receive status information to return.
 * @returns true - Indicate the particular receive status is set,
 *          false - Indicate the particular receive status is clear
 */
bool EMVSIM_HAL_GetReceiveStatus(EMVSIM_Type *base, emvsim_rx_status_t rxStatus);

/*!
 * @brief Clears the receive status of the EMVSIM controller.
 *
 * This function clears the receive status of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   rxStatus Indicates a particular receive status to clear.
 */
void EMVSIM_HAL_ClearReceiveStatus(EMVSIM_Type *base, emvsim_rx_status_t rxStatus);

/*!
 * @brief Returns the transmit status of the EMVSIM controller.
 *
 * This function returns the transmit status of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   txStatus Indicates a particular transmit status information to return.
 * @returns true - Indicate the particular transmit status is set,
 *          false - Indicate the particular transmit status is clear
 */
bool EMVSIM_HAL_GetTransmitStatus(EMVSIM_Type *base, emvsim_tx_status_t txStatus);

/*!
 * @brief Clears the transmit status of the EMVSIM controller.
 *
 * This function clears the transmit status of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   txStatus Indicates a particular transmit status to clear.
 */
void EMVSIM_HAL_ClearTransmitStatus(EMVSIM_Type *base, emvsim_tx_status_t txStatus);

/*!
 * @brief Sets the card presence detection edge of the EMVSIM controller.
 *
 * This function sets the card presence detection edge of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   spdes kEmvsimPDOnFallingEdge - presence detection on falling edge,
 *                kEmvsimPDOnRisingEdge - presence detection on rising edge
 */
static inline void EMVSIM_HAL_SetCardPresenceDetectEdge(EMVSIM_Type *base, emvsim_presence_detect_edge_t spdes)
{
    EMVSIM_WR_PCSR_SPDES(base, spdes);
}

/*!
 * @brief Returns the current setting of the card presence detection edge 
 * of the EMVSIM controller.
 *
 * This function returns the current setting of the card presence detection edge 
 * of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns kEmvsimPDOnFallingEdge - presence detection on falling edge,
 *          kEmvsimPDOnRisingEdge - presence detection on rising edge
 */
static inline emvsim_presence_detect_edge_t EMVSIM_HAL_GetCardPresenceDetectEdge(EMVSIM_Type *base)
{
    return (emvsim_presence_detect_edge_t)EMVSIM_RD_PCSR_SPDES(base);
}

/*!
 * @brief Returns the card presence detection pin level of the EMVSIM controller.
 *
 * This function returns the card presence detection pin level of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns kEmvsimPDPinIsLow - presence detection pin level is LOW,
 *          kEmvsimPDPinIsHigh - presence detection pin level is HIGH
 */
static inline emvsim_presence_detect_status_t EMVSIM_HAL_GetCardPresenceDetectPinStatus(EMVSIM_Type *base)
{
    return (emvsim_presence_detect_status_t)EMVSIM_RD_PCSR_SPDP(base);
}

/*!
 * @brief Returns the card presence detection interrupt status of the EMVSIM controller.
 *
 * This function returns the card presence detection interrupt status of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns true - card presence has been detected,
 *          false - card presence has not been detected
 */
static inline bool EMVSIM_HAL_GetCardPresenceDetectInterruptStatus(EMVSIM_Type *base)
{
    return (bool)EMVSIM_RD_PCSR_SPDIF(base);
}

/*!
 * @brief Clears the card presence detection interrupt status of the EMVSIM controller.
 *
 * This function clears the card presence detection interrupt status of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 */
static inline void EMVSIM_HAL_ClearCardPresenceDetectInterruptStatus(EMVSIM_Type *base)
{
    EMVSIM_WR_PCSR_SPDIF(base, 1U);
}

/*!
 * @brief Enables/disables the auto power down of the EMVSIM controller.
 *
 * This function enables/disables the auto power down of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   spd true - Start auto power down,
 *              false - No effect.
 */
static inline void EMVSIM_HAL_SetAutoPowerDown(EMVSIM_Type *base, bool spd)
{
    EMVSIM_WR_PCSR_SPD(base, spd);
}

/*!
 * @brief Returns whether the state of auto power down of the EMVSIM controller.
 *
 * This function returns the state of auto power down of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns true - Auto power down has been started or in progress,
 *          false - Auto power down is not activated.
 */
static inline bool EMVSIM_HAL_GetAutoPowerDown(EMVSIM_Type *base)
{
    return (bool)EMVSIM_RD_PCSR_SPD(base);
}

/*!
 * @brief Sets the clock signal polarity during clock stop of EMVSIM controller.
 *
 * This function sets clock signal polarity during clock stop of EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns scsp kEmvsimCardClockStopPolarityIsLow - clock stop polarity is LOW,
 *               kEmvsimCardClockStopPolarityIsHigh - clock stop polarity is HIGH.
 */
static inline void EMVSIM_HAL_SetCardClockStopPolarity(EMVSIM_Type *base, emvsim_card_clock_stop_polarity_t scsp)
{
    EMVSIM_WR_PCSR_SCSP(base, scsp);
}

/*!
 * @brief Returns the current setting of the clock signal polarity during the clock stop 
 * of the EMVSIM controller.
 *
 * This function returns the current setting of the clock signal polarity 
 * during the clock stop of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns kEmvsimCardClockStopPolarityIsLow - clock stop polarity is LOW,
 *          kEmvsimCardClockStopPolarityIsHigh - clock stop polarity is HIGH.
 */
static inline emvsim_card_clock_stop_polarity_t EMVSIM_HAL_GetCardClockStopPolarity(EMVSIM_Type *base)
{
    return (emvsim_card_clock_stop_polarity_t)EMVSIM_RD_PCSR_SCSP(base);
}

/*!
 * @brief Enables the card clock from the EMVSIM controller.
 *
 * This function enables the card clock from the the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 */
static inline void EMVSIM_HAL_EnableCardClock(EMVSIM_Type *base)
{
    EMVSIM_WR_PCSR_SCEN(base, 1U);
}

/*!
 * @brief Disables the card clock from the EMVSIM controller.
 *
 * This function disables the card clock from the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 */
static inline void EMVSIM_HAL_DisableCardClock(EMVSIM_Type *base)
{
    EMVSIM_WR_PCSR_SCEN(base, 0U);
}

/*!
 * @brief Returns the current setting of the card clock from the EMVSIM controller.
 *
 * This function returns the current setting of the card clock from 
 * the EMVSIM controller, whether it is enabled or disabled.
 *
 * @param   base EMVSIM module base pointer.
 * @returns true - Card clock is enabled,
 *          false - Card clock is disabled.
 */
static inline bool EMVSIM_HAL_IsCardClockEnabled(EMVSIM_Type *base)
{
    return (bool)EMVSIM_RD_PCSR_SCEN(base);
}

/*!
 * @brief Asserts/de-asserts the card reset signal from the EMVSIM controller.
 *
 * This function asserts/de-asserts the card reset signal from the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   srst - kEmvsimResetAssert - Card reset signal is asserted,
 *                 kEmvsimResetDeassert - Card reset signal is de-asserted.
 */
static inline void EMVSIM_HAL_ResetCard(EMVSIM_Type *base, emvsim_reset_card_t srst)
{
    EMVSIM_WR_PCSR_SRST(base, srst);
}

/*!
 * @brief Returns whether the card reset signal has been asserted from the EMVSIM controller.
 *
 * This function returns whether the card reset signal has been asserted/de-asserted 
 * from the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns kEmvsimResetAssert - Card reset signal is asserted,
 *          kEmvsimResetDeassert - Card reset signal is de-asserted.
 */
static inline emvsim_reset_card_t EMVSIM_HAL_GetCardResetState(EMVSIM_Type *base)
{
    return (emvsim_reset_card_t)EMVSIM_RD_PCSR_SRST(base);
}

/*!
 * @brief Sets the polarity of the VCC enable signal from the EMVSIM controller.
 *
 * This function sets the polarity of the VCC enable signal from the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   vccenp - kEmvsimVccEnIsHigh - VCC enable signal polarity is HIGH,
 *                 - kEmvsimVccEnIsLow- VCC enable signal polarity is LOW.
 */
static inline void EMVSIM_HAL_SetCardVCCEnablePolarity(EMVSIM_Type *base, emvsim_vcc_en_polarity_t vccenp)
{
    EMVSIM_WR_PCSR_VCCENP(base, vccenp);
}

/*!
 * @brief Returns the polarity of the VCC enable signal from the EMVSIM controller.
 *
 * This function returns the polarity of the VCC enable signal from the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns kEmvsimVccEnIsHigh - VCC enable signal polarity is HIGH,
 *          kEmvsimVccEnIsLow- VCC enable signal polarity is LOW.
 */
static inline emvsim_vcc_en_polarity_t EMVSIM_HAL_GetCardVCCEnablePolarity(EMVSIM_Type *base)
{
    return (emvsim_vcc_en_polarity_t)EMVSIM_RD_PCSR_VCCENP(base);
}

/*!
 * @brief Controls the state of the VCC enable signal from the EMVSIM controller.
 *
 * This function controls the state of the VCC enable signal from the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   svccEnable - true - Smart card voltage is enabled,
 *                     - false - Smart card voltage is disabled.
 */
static inline void EMVSIM_HAL_SetVCCEnable(EMVSIM_Type *base, bool svccEnable)
{
    EMVSIM_WR_PCSR_SVCC_EN(base, svccEnable);
}

/*!
 * @brief Returns the state of the VCC enable signal from the EMVSIM controller.
 *
 * This function returns the state of the VCC enable signal from the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns true - Smart card voltage is enabled,
 *          false - Smart card voltage is disabled.
 */
static inline bool EMVSIM_HAL_GetVCCEnable(EMVSIM_Type *base)
{
    return (bool)EMVSIM_RD_PCSR_SVCC_EN(base);
}

/*!
 * @brief Enables the auto power down feature of the EMVSIM controller.
 *
 * This function enables the auto power down feature of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 */
static inline void EMVSIM_HAL_EnableAutoPowerDown(EMVSIM_Type *base)
{
    EMVSIM_WR_PCSR_SAPD(base, 1U);
}

/*!
 * @brief Disables the auto power down feature of the EMVSIM controller.
 *
 * This function disables the auto power down feature of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 */
static inline void EMVSIM_HAL_DisableAutoPowerDown(EMVSIM_Type *base)
{
    EMVSIM_WR_PCSR_SAPD(base, 0U);
}

/*!
 * @brief Returns the current state of the auto power down feature of the EMVSIM controller.
 *
 * This function returns the current state of the auto power down feature 
 * of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns true - Auto power down feature is enabled,
 *          false - Auto power down feature is disabled.
 */
static inline bool EMVSIM_HAL_IsAutoPowerDownEnabled(EMVSIM_Type *base)
{
    return (bool)EMVSIM_RD_PCSR_SAPD(base);
}

/*!
 * @brief Reads the received data byte from the EMVSIM controller.
 *
 * This function reads the byte value from the top of the received FIFO of the
 * EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   readData Pointer to memory where the read data byte must be stored
 */
static inline void EMVSIM_HAL_GetChar(EMVSIM_Type *base, uint8_t *readData)
{
    *readData = EMVSIM_RD_RX_BUF_RX_BYTE(base);
}

/*!
 * @brief Returns the address of the receive data byte register of the EMVSIM controller.
 *
 * This function returns the address of the receive data byte register of the 
 * EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns Address of receive data register
 */
static inline uint32_t EMVSIM_HAL_GetRxDataRegAddr(EMVSIM_Type * base)
{
    return (uint32_t)(&EMVSIM_RX_BUF_REG(base));
}

/*!
 * @brief Writes a byte data to the transmit data byte of the EMVSIM controller.
 *
 * This function writes a data byte to the transmit data FIFO of the
 * EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   writeData Data byte value to be written to transmit data FIFO
 */
static inline void EMVSIM_HAL_PutChar(EMVSIM_Type *base, uint8_t writeData)
{
    EMVSIM_WR_TX_BUF_TX_BYTE(base, writeData);
}

/*!
 * @brief Returns the address of the transmit data byte register of the EMVSIM controller.
 *
 * This function returns the address of the transmit data byte register of the 
 * EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns Address of transmit data register
 */
static inline uint32_t EMVSIM_HAL_GetTxDataRegAddr(EMVSIM_Type * base)
{
    return (uint32_t)(&EMVSIM_TX_BUF_REG(base));
}

/*!
 * @brief Sets an additional transmitter guard time value of the EMVSIM controller.
 *
 * This function sets an additional transmitter guard time value of the 
 * EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   getu Additional ETU guard time to be inserted between bytes to be transmitted
 */
static inline void EMVSIM_HAL_SetAdditionalTransmitterGuardTime(EMVSIM_Type *base, uint8_t getu)
{
    EMVSIM_WR_TX_GETU_GETU(base, getu);
}

/*!
 * @brief Returns the current setting of the additional transmitter guard time 
 * value of the EMVSIM controller.
 *
 * This function returns the currently set value of the additional transmitter 
 * guard time of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns Additional ETU guard time to be inserted between bytes to be transmitted
 */
static inline uint8_t EMVSIM_HAL_GetAdditionalTransmitterGuardTime(EMVSIM_Type *base)
{
    return EMVSIM_RD_TX_GETU_GETU(base);
}

/*!
 * @brief Sets the character wait time value of the EMVSIM controller.
 *
 * This function sets the character wait time value of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   cwt Wait time value between characters
 */
static inline void EMVSIM_HAL_SetCharacterWaitTime(EMVSIM_Type *base, uint16_t cwt)
{
    EMVSIM_WR_CWT_VAL_CWT(base, cwt);
}

/*!
 * @brief Returns the character wait time value of the EMVSIM controller.
 *
 * This function returns the character wait time value of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns Wait time value between characters
 */
static inline uint16_t EMVSIM_HAL_GetCharacterWaitTime(EMVSIM_Type *base)
{
    return EMVSIM_RD_CWT_VAL_CWT(base);
}

/*!
 * @brief Sets the block wait time value of the EMVSIM controller.
 *
 * This function sets the block wait time value of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   bwt Wait time value between the strat bit of last byte sent from 
 *              EMVSIM module and the start bit of the first byte received from smart card
 */
static inline void EMVSIM_HAL_SetBlockWaitTime(EMVSIM_Type *base, uint32_t bwt)
{
    EMVSIM_WR_BWT_VAL(base, bwt);
}

/*!
 * @brief Returns the block wait time value of the EMVSIM controller.
 *
 * This function returns the block wait time value of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns Wait time value between the strat bit of last byte sent from 
 *          EMVSIM module and the start bit of the first byte received from smart card
 */
static inline uint32_t EMVSIM_HAL_GetBlockWaitTime(EMVSIM_Type *base)
{
    return EMVSIM_RD_BWT_VAL(base);
}

/*!
 * @brief Sets the block guard time value of the EMVSIM controller.
 *
 * This function sets the guard wait time value of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   bgt Guard time value between the strat bit of last byte sent from 
 *              EMVSIM module and the start bit of the first byte received from smart card
 */
static inline void EMVSIM_HAL_SetBlockGuardTime(EMVSIM_Type *base, uint16_t bgt)
{
    EMVSIM_WR_BGT_VAL_BGT(base, bgt);
}

/*!
 * @brief Returns the block guard time value of the EMVSIM controller.
 *
 * This function returns the guard wait time value of the EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @returns Guard time value between the strat bit of last byte sent from 
 *          EMVSIM module and the start bit of the first byte received from smart card
 */
static inline uint16_t EMVSIM_HAL_GetBlockGuardTime(EMVSIM_Type *base)
{
    return EMVSIM_RD_BGT_VAL_BGT(base);
}

/*!
 * @brief Sets the timeout value of the general purpose counters of the
 * EMVSIM controller.
 *
 * This function sets the timeout values of the general purpose counters of the 
 * EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   gpcntIndex Index to general purpose counters
 * @param   gpcntVal Timer timeout value
 */
void EMVSIM_HAL_SetGPCNTValue(EMVSIM_Type *base, uint8_t gpcntIndex, uint16_t gpcntVal);

/*!
 * @brief Returns the timeout value of the general purpose counters of the 
 * EMVSIM controller.
 *
 * This function returns the timeout values of the general purpose counters of the 
 * EMVSIM controller.
 *
 * @param   base EMVSIM module base pointer.
 * @param   gpcntIndex Index to general purpose counters
 * @returns Timer timeout value
 */
uint16_t EMVSIM_HAL_GetGPCNTValue(EMVSIM_Type *base, uint8_t gpcntIndex);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_UART_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

