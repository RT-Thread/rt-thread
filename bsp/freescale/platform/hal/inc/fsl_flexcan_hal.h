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
#ifndef __FSL_FLEXCAN_HAL_H__
#define __FSL_FLEXCAN_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_FLEXCAN_COUNT

/*!
 * @addtogroup flexcan_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief FlexCAN constants*/
enum _flexcan_constants
{
    kFlexCanMessageSize = 8,               /*!< FlexCAN message buffer data size in bytes*/
};

/*! @brief The Status enum is used to report current status of the FlexCAN interface.*/
enum _flexcan_err_status
{
    kFlexCanRxWrn   = 0x0080U, /*!< Reached warning level for RX errors*/
    kFlexCanTxWrn   = 0x0100U, /*!< Reached warning level for TX errors*/
    kFlexCanStfErr  = 0x0200U, /*!< Stuffing Error*/
    kFlexCanFrmErr  = 0x0400U, /*!< Form Error*/
    kFlexCanCrcErr  = 0x0800U, /*!< Cyclic Redundancy Check Error*/
    kFlexCanAckErr  = 0x1000U, /*!< Received no ACK on transmission*/
    kFlexCanBit0Err = 0x2000U, /*!< Unable to send dominant bit*/
    kFlexCanBit1Err = 0x4000U  /*!< Unable to send recessive bit*/
};

/*! @brief FlexCAN status return codes*/
typedef enum _flexcan_status
{
    kStatus_FLEXCAN_Success = 0,
    kStatus_FLEXCAN_OutOfRange,
    kStatus_FLEXCAN_UnknownProperty,
    kStatus_FLEXCAN_InvalidArgument,
    kStatus_FLEXCAN_Fail,
    kStatus_FLEXCAN_TimeOut,
    kStatus_FLEXCAN_TxBusy,
    kStatus_FLEXCAN_RxBusy,
    kStatus_FLEXCAN_NoTransmitInProgress,
    kStatus_FLEXCAN_NoReceiveInProgress
} flexcan_status_t;


/*! @brief FlexCAN operation modes*/
typedef enum _flexcan_operation_modes {
    kFlexCanNormalMode,        /*!< Normal mode or user mode @internal gui name="Normal" */
    kFlexCanListenOnlyMode,    /*!< Listen-only mode @internal gui name="Listen-only" */
    kFlexCanLoopBackMode,      /*!< Loop-back mode @internal gui name="Loop back" */
    kFlexCanFreezeMode,        /*!< Freeze mode @internal gui name="Freeze" */
    kFlexCanDisableMode        /*!< Module disable mode @internal gui name="Disabled" */
} flexcan_operation_modes_t;

/*! @brief FlexCAN message buffer code for receive buffers*/
typedef enum _flexcan_msgbuff_code_rx {
    kFlexCanRXInactive  = 0x0, /*!< MB is not active.*/
    kFlexCanRXFull      = 0x2, /*!< MB is full.*/
    kFlexCanRXEmpty     = 0x4, /*!< MB is active and empty.*/
    kFlexCanRXOverrun   = 0x6, /*!< MB is overwritten into a full buffer.*/
    kFlexCanRXBusy      = 0x8, /*!< FlexCAN is updating the contents of the MB.*/
                                /*!  The CPU must not access the MB.*/
    kFlexCanRXRanswer   = 0xA, /*!< A frame was configured to recognize a Remote Request Frame*/
                                /*!  and transmit a Response Frame in return.*/
    kFlexCanRXNotUsed   = 0xF  /*!< Not used*/
} flexcan_msgbuff_code_rx_t;

/*! @brief FlexCAN message buffer code for transmit buffers*/
typedef enum _flexcan_msgbuff_code_tx {
    kFlexCanTXInactive  = 0x08, /*!< MB is not active.*/
    kFlexCanTXAbort     = 0x09, /*!< MB is aborted.*/
    kFlexCanTXData      = 0x0C, /*!< MB is a transmit data frame(MB RTR must be 0).*/
    kFlexCanTXRemote    = 0x1C, /*!< MB is a transmit remote request frame (MB RTR must be 1).*/
    kFlexCanTXTanswer   = 0x0E, /*!< MB is a transmit response request frame from.*/
                                 /*!  an incoming remote request frame.*/
    kFlexCanTXNotUsed   = 0xF  /*!< Not used*/
} flexcan_msgbuff_code_tx_t;

/*! @brief FlexCAN message buffer transmission types*/
typedef enum _flexcan_msgbuff_transmission_type {
    kFlexCanMBStatusTypeTX,          /*!< Transmit MB*/
    kFlexCanMBStatusTypeTXRemote,    /*!< Transmit remote request MB*/
    kFlexCanMBStatusTypeRX,          /*!< Receive MB*/
    kFlexCanMBStatusTypeRXRemote,    /*!< Receive remote request MB*/
    kFlexCanMBStatusTypeRXTXRemote   /*!< FlexCAN remote frame receives remote request and*/
                                      /*!  transmits MB.*/
} flexcan_msgbuff_transmission_type_t;

typedef enum _flexcan_rx_fifo_id_element_format {
    kFlexCanRxFifoIdElementFormatA, /*!< One full ID (standard and extended) per ID Filter Table*/
                                     /*!  element.*/
    kFlexCanRxFifoIdElementFormatB, /*!< Two full standard IDs or two partial 14-bit (standard and*/
                                     /*!  extended) IDs per ID Filter Table element.*/
    kFlexCanRxFifoIdElementFormatC, /*!< Four partial 8-bit Standard IDs per ID Filter Table*/
                                     /*!  element.*/
    kFlexCanRxFifoIdElementFormatD  /*!< All frames rejected.*/
} flexcan_rx_fifo_id_element_format_t;
/*! @brief FlexCAN receive FIFO filters number*/
typedef enum _flexcan_rx_fifo_id_filter_number {
    kFlexCanRxFifoIDFilters_8   = 0x0,         /*!<   8 receive FIFO Filters. @internal gui name="8 receive FIFO Filters" */
    kFlexCanRxFifoIDFilters_16  = 0x1,         /*!<  16 receive FIFO Filters. @internal gui name="16 receive FIFO Filters" */
    kFlexCanRxFifoIDFilters_24  = 0x2,         /*!<  24 receive FIFO Filters. @internal gui name="24 receive FIFO Filters" */
    kFlexCanRxFifoIDFilters_32  = 0x3,         /*!<  32 receive FIFO Filters. @internal gui name="32 receive FIFO Filters" */
    kFlexCanRxFifoIDFilters_40  = 0x4,         /*!<  40 receive FIFO Filters. @internal gui name="40 receive FIFO Filters" */
    kFlexCanRxFifoIDFilters_48  = 0x5,         /*!<  48 receive FIFO Filters. @internal gui name="48 receive FIFO Filters" */
    kFlexCanRxFifoIDFilters_56  = 0x6,         /*!<  56 receive FIFO Filters. @internal gui name="56 receive FIFO Filters" */
    kFlexCanRxFifoIDFilters_64  = 0x7,         /*!<  64 receive FIFO Filters. @internal gui name="64 receive FIFO Filters" */
    kFlexCanRxFifoIDFilters_72  = 0x8,         /*!<  72 receive FIFO Filters. @internal gui name="72 receive FIFO Filters" */
    kFlexCanRxFifoIDFilters_80  = 0x9,         /*!<  80 receive FIFO Filters. @internal gui name="80 receive FIFO Filters" */
    kFlexCanRxFifoIDFilters_88  = 0xA,         /*!<  88 receive FIFO Filters. @internal gui name="88 receive FIFO Filters" */
    kFlexCanRxFifoIDFilters_96  = 0xB,         /*!<  96 receive FIFO Filters. @internal gui name="96 receive FIFO Filters" */
    kFlexCanRxFifoIDFilters_104 = 0xC,         /*!< 104 receive FIFO Filters. @internal gui name="104 receive FIFO Filters" */
    kFlexCanRxFifoIDFilters_112 = 0xD,         /*!< 112 receive FIFO Filters. @internal gui name="112 receive FIFO Filters" */
    kFlexCanRxFifoIDFilters_120 = 0xE,         /*!< 120 receive FIFO Filters. @internal gui name="120 receive FIFO Filters" */
    kFlexCanRxFifoIDFilters_128 = 0xF          /*!< 128 receive FIFO Filters. @internal gui name="128 receive FIFO Filters" */
} flexcan_rx_fifo_id_filter_num_t;

/*! @brief FlexCAN receive FIFO ID filter table structure*/
typedef struct FLEXCANIdTable {
    bool isRemoteFrame;      /*!< Remote frame*/
    bool isExtendedFrame;    /*!< Extended frame*/
    uint32_t *idFilter;    /*!< Receive FIFO ID filter elements*/
} flexcan_id_table_t;

/*! @brief FlexCAN receive mask type.*/
typedef enum _flexcan_rx_mask_type {
    kFlexCanRxMaskGlobal,      /*!< Receive global mask*/
    kFlexCanRxMaskIndividual   /*!< Receive individual mask*/
} flexcan_rx_mask_type_t;

/*! @brief FlexCAN Message Buffer ID type*/
typedef enum _flexcan_msgbuff_id_type {
    kFlexCanMsgIdStd,         /*!< Standard ID*/
    kFlexCanMsgIdExt          /*!< Extended ID*/
} flexcan_msgbuff_id_type_t;

/*! @brief FlexCAN clock source*/
typedef enum _flexcan_clk_source {
    kFlexCanClkSourceOsc,    /*!< Oscillator clock*/
    kFlexCanClkSourceIpbus   /*!< Peripheral clock*/
} flexcan_clk_source_t;

/*! @brief FlexCAN error interrupt types*/
typedef enum _flexcan_int_type {
    kFlexCanIntRxwarning = CAN_CTRL1_RWRNMSK_MASK,     /*!< Receive warning interrupt*/
    kFlexCanIntTxwarning = CAN_CTRL1_TWRNMSK_MASK,     /*!< Transmit warning interrupt*/
    kFlexCanIntErr = CAN_CTRL1_ERRMSK_MASK,           /*!< Error interrupt*/
    kFlexCanIntBusoff = CAN_CTRL1_BOFFMSK_MASK,       /*!< Bus off interrupt*/
    kFlexCanIntWakeup = CAN_MCR_WAKMSK_MASK          /*!< Wake up interrupt*/
} flexcan_int_type_t;

/*! @brief FlexCAN bus error counters*/
typedef struct FLEXCANBuserrCounter {
    uint16_t txerr;           /*!< Transmit error counter*/
    uint16_t rxerr;           /*!< Receive error counter*/
} flexcan_buserr_counter_t;

/*! @brief FlexCAN Message Buffer code and status for transmit and receive */
typedef struct FLEXCANMsgBuffCodeStatus {
    uint32_t code;                    /*!< MB code for transmit or receive buffers.
                                        Defined by flexcan_mb_code_rx_t and flexcan_mb_code_tx_t */
    flexcan_msgbuff_id_type_t msgIdType; /*!< Type of message ID (standard or extended)*/
    uint32_t dataLen;             /*!< Length of Data in Bytes*/
} flexcan_msgbuff_code_status_t;

/*! @brief FlexCAN message buffer structure*/
typedef struct FLEXCANMsgBuff {
    uint32_t cs;                        /*!< Code and Status*/
    uint32_t msgId;                    /*!< Message Buffer ID*/
    uint8_t data[kFlexCanMessageSize];  /*!< Bytes of the FlexCAN message*/
} flexcan_msgbuff_t;

/*! @brief FlexCAN timing related structures*/
typedef struct FLEXCANTimeSegment {
    uint32_t propSeg;     /*!< Propagation segment*/
    uint32_t phaseSeg1;       /*!< Phase segment 1*/
    uint32_t phaseSeg2;       /*!< Phase segment 2*/
    uint32_t preDivider; /*!< Clock pre divider*/
    uint32_t rJumpwidth;         /*!< Resync jump width*/
} flexcan_time_segment_t;
#define RxFifoOcuppiedFirstMsgBuff      6U
#define RxFifoOcuppiedLastMsgBuff(x)    (5 + (x + 1) * 8 / 4)
#define RxFifoFilterElementNum(x)       ((x + 1) * 8)
#define FlexCanRxFifoAcceptRemoteFrame   1U
#define FlexCanRxFifoAcceptExtFrame      1U
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Configuration
 * @{
 */

/*!
 * @brief Enables FlexCAN controller.
 *
 * @param   base    The FlexCAN base address
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_Enable(CAN_Type * base);

/*!
 * @brief Disables FlexCAN controller.
 *
 * @param   base    The FlexCAN base address
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_Disable(CAN_Type * base);

/*!
 * @brief Selects the clock source for FlexCAN.
 *
 * @param   base The FlexCAN base address
 * @param   clk         The FlexCAN clock source
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_SelectClock(CAN_Type * base, flexcan_clk_source_t clk);

/*!
 * @brief Reads the clock source for FlexCAN Protocol Engine (PE).
 *
 * @param   base The FlexCAN base address
 * @return  0: if clock source is oscillator clock, 1: if clock source is peripheral clock
 */
static inline bool FLEXCAN_HAL_GetClock(CAN_Type * base)
{
    return CAN_BRD_CTRL1_CLKSRC(base);
}

/*!
 * @brief Initializes the FlexCAN controller.
 *
 * @param   base  The FlexCAN base address
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_Init(CAN_Type * base);

/*!
 * @brief Sets the FlexCAN time segments for setting up bit rate.
 *
 * @param   base The FlexCAN base address
 * @param   timeSeg    FlexCAN time segments, which need to be set for the bit rate.
 */
void FLEXCAN_HAL_SetTimeSegments(CAN_Type * base, flexcan_time_segment_t *timeSeg);

/*!
 * @brief Gets the  FlexCAN time segments to calculate the bit rate.
 *
 * @param   base The FlexCAN base address
 * @param   timeSeg    FlexCAN time segments read for bit rate
 */
void FLEXCAN_HAL_GetTimeSegments(CAN_Type * base, flexcan_time_segment_t *timeSeg);

/*!
 * @brief Unfreezes the FlexCAN module.
 *
 * @param   base     The FlexCAN base address
 */
void FLEXCAN_HAL_ExitFreezeMode(CAN_Type * base);

/*!
 * @brief Freezes the FlexCAN module.
 *
 * @param   base     The FlexCAN base address
 */
void FLEXCAN_HAL_EnterFreezeMode(CAN_Type * base);

/*!
 * @brief Sets  operation mode.
 *
 * @param   base  The FlexCAN base address
 * @param   mode  Set an operation mode
 * @return  0 if successful; non-zero failed.
 */
flexcan_status_t FLEXCAN_HAL_SetOperationMode(
    CAN_Type * base,
    flexcan_operation_modes_t mode);

/*!
 * @brief Exits operation mode.
 *
 * @param   base  The FlexCAN base address
 * @param   mode  Exit An operation mode
 * @return  0 if successful; non-zero failed.
 */
flexcan_status_t FLEXCAN_HAL_ExitOperationMode(
    CAN_Type * base,
    flexcan_operation_modes_t mode);

/*@}*/

/*!
 * @name Data transfer
 * @{
 */

/*!
 * @brief Sets the FlexCAN message buffer fields for transmitting.
 *
 * @param   base  The FlexCAN base address
 * @param   msgBuffIdx       Index of the message buffer
 * @param   cs           CODE/status values (TX)
 * @param   msgId       ID of the message to transmit
 * @param   msgData      Bytes of the FlexCAN message
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_SetTxMsgBuff(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    flexcan_msgbuff_code_status_t *cs,
    uint32_t msgId,
    uint8_t *msgData);

/*!
 * @brief Sets the FlexCAN message buffer fields for receiving.
 *
 * @param   base  The FlexCAN base address
 * @param   msgBuffIdx       Index of the message buffer
 * @param   cs           CODE/status values (RX)
 * @param   msgId       ID of the message to receive
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_SetRxMsgBuff(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    flexcan_msgbuff_code_status_t *cs,
    uint32_t msgId);

/*!
 * @brief Gets the FlexCAN message buffer fields.
 *
 * @param   base  The FlexCAN base address
 * @param   msgBuffIdx       Index of the message buffer
 * @param   msgBuff           The fields of the message buffer
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_GetMsgBuff(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    flexcan_msgbuff_t *msgBuff);

/*!
 * @brief Locks the FlexCAN receive message buffer.
 *
 * @param   base  The FlexCAN base address
 * @param   msgBuffIdx       Index of the message buffer
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_LockRxMsgBuff(
    CAN_Type * base,
    uint32_t msgBuffIdx);

/*!
 * @brief Unlocks the FlexCAN receive message buffer.
 *
 * @param   base     The FlexCAN base address
 * @return  0 if successful; non-zero failed
 */
static inline uint32_t FLEXCAN_HAL_UnlockRxMsgBuff(CAN_Type * base)
{
   uint32_t tmp;
    /* Unlock the mailbox */
   tmp = CAN_RD_TIMER(base);
	 return tmp;
}

/*!
 * @brief Enables the receive FIFO.
 *
 * @param   base     The FlexCAN base address
 * @param   numOfFilters    The number of receive FIFO filters
 */
void FLEXCAN_HAL_EnableRxFifo(CAN_Type * base, uint32_t numOfFilters);

/*!
 * @brief Disables the receive FIFO.
 *
 * @param   base     The FlexCAN base address
 */
void FLEXCAN_HAL_DisableRxFifo(CAN_Type * base);

/*!
 * @brief Sets the number of the receive FIFO filters.
 *
 * @param   base  The FlexCAN base address
 * @param   number       The number of receive FIFO filters
 */
void FLEXCAN_HAL_SetRxFifoFilterNum(CAN_Type * base, uint32_t number);

/*!
 * @brief Sets  the number of the last message buffer.
 *
 * @param   base  The FlexCAN base address
 * @param   maxMsgBuffNum     Number of the last Message Buffer
 */
void FLEXCAN_HAL_SetMaxMsgBuffNum(
    CAN_Type * base,
    uint32_t maxMsgBuffNum);

/*!
 * @brief Sets the FlexCAN receive FIFO fields.
 *
 * @param   base             The FlexCAN base address
 * @param   idFormat               The format of the receive FIFO ID Filter Table Elements
 * @param   idFilterTable         The ID filter table elements which contain RTR bit, IDE bit,
 *                                  and receive message ID.
 * @return  0 if successful; non-zero failed.
 */
flexcan_status_t FLEXCAN_HAL_SetRxFifoFilter(
    CAN_Type * base,
    flexcan_rx_fifo_id_element_format_t idFormat,
    flexcan_id_table_t *idFilterTable);

/*!
 * @brief Gets the FlexCAN receive FIFO data.
 *
 * @param   base  The FlexCAN base address
 * @param   rxFifo      The FlexCAN receive FIFO data
 * @return  0 if successful; non-zero failed.
 */
flexcan_status_t FLEXCAN_HAL_ReadRxFifo(
    CAN_Type * base,
    flexcan_msgbuff_t *rxFifo);

/*@}*/

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables/disables the FlexCAN message buffer interrupt.
 *
 * @param   base  The FlexCAN base address
 * @param   msgBuffIdx       Index of the message buffer
 * @param   enable       choose enable or disable
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_SetMsgBuffIntCmd(
    CAN_Type * base,
    uint32_t msgBuffIdx, bool enable);

/*!
 * @brief Enables the error interrupt of the FlexCAN module.
 * @param   base     The FlexCAN base address
 * @param   errType     The interrupt type
 * @param   enable       choose enable or disable
 */
void FLEXCAN_HAL_SetErrIntCmd(CAN_Type * base, flexcan_int_type_t errType, bool enable);

/*@}*/

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the value of the FlexCAN freeze ACK.
 *
 * @param   base     The FlexCAN base address
 * @return  freeze ACK state (1-freeze mode, 0-not in freeze mode).
 */
static inline uint32_t FLEXCAN_HAL_GetFreezeAck(CAN_Type * base)
{
    return CAN_BRD_MCR_FRZACK(base);
}

/*!
 * @brief Gets the individual FlexCAN MB interrupt flag.
 *
 * @param   base  The FlexCAN base address
 * @param   msgBuffIdx       Index of the message buffer
 * @return  the individual Message Buffer interrupt flag (0 and 1 are the flag value)
 */
uint8_t FLEXCAN_HAL_GetMsgBuffIntStatusFlag(
    CAN_Type * base,
    uint32_t msgBuffIdx);

/*!
 * @brief Gets all FlexCAN message buffer interrupt flags.
 *
 * @param   base     The FlexCAN base address
 * @return  all MB interrupt flags
 */
static inline uint32_t FLEXCAN_HAL_GetAllMsgBuffIntStatusFlag(CAN_Type * base)
{
    return CAN_RD_IFLAG1(base);
}

/*!
 * @brief Clears the interrupt flag of the message buffers.
 *
 * @param   base  The FlexCAN base address
 * @param   flag      The value to be written to the interrupt flag1 register.
 */
/* See fsl_flexcan_hal.h for documentation of this function.*/
static inline void FLEXCAN_HAL_ClearMsgBuffIntStatusFlag(
    CAN_Type * base,
    uint32_t flag)
{
    /* Clear the corresponding message buffer interrupt flag*/
    CAN_WR_IFLAG1(base, flag);
}

/*!
 * @brief Gets the transmit error counter and receives the error counter.
 *
 * @param   base  The FlexCAN base address
 * @param   errCount      Transmit error counter and receive error counter
 */
void FLEXCAN_HAL_GetErrCounter(
    CAN_Type * base,
    flexcan_buserr_counter_t *errCount);

/*!
 * @brief Gets an error and status.
 *
 * @param   base     The FlexCAN base address
 * @return  The current error and status
 */
static inline uint32_t FLEXCAN_HAL_GetErrStatus(CAN_Type * base)
{
    return CAN_RD_ESR1(base);
}

/*!
 * @brief Clears all other interrupts in ERRSTAT register (Error, Busoff, and Wakeup).
 *
 * @param   base     The FlexCAN base address
 */
void FLEXCAN_HAL_ClearErrIntStatusFlag(CAN_Type * base);

/*@}*/

/*!
 * @name Mask
 * @{
 */

/*!
 * @brief Sets the receive masking type.
 *
 * @param   base  The FlexCAN base address
 * @param   type         The FlexCAN receive mask type
 */
void FLEXCAN_HAL_SetRxMaskType(CAN_Type * base, flexcan_rx_mask_type_t type);

/*!
 * @brief Sets the FlexCAN receive FIFO global standard mask.
 *
 * @param   base  The FlexCAN base address
 * @param   stdMask     Standard mask
 */
void FLEXCAN_HAL_SetRxFifoGlobalStdMask(
    CAN_Type * base,
    uint32_t stdMask);

/*!
 * @brief Sets the FlexCAN receive FIFO global extended mask.
 *
 * @param   base  The FlexCAN base address
 * @param   extMask     Extended mask
 */
void FLEXCAN_HAL_SetRxFifoGlobalExtMask(
    CAN_Type * base,
    uint32_t extMask);

/*!
 * @brief Sets the FlexCAN receive individual standard mask for ID filtering in the receive MBs and the receive FIFO.
 *
 * @param   base  The FlexCAN base address
 * @param   msgBuffIdx       Index of the message buffer
 * @param   stdMask     Individual standard mask
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_SetRxIndividualStdMask(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    uint32_t stdMask);

/*!
 * @brief Sets the FlexCAN receive individual extended mask for ID filtering in the receive Message Buffers and the receive FIFO.
 *
 * @param   base  The FlexCAN base address
 * @param   msgBuffIdx       Index of the message buffer
 * @param   extMask     Individual extended mask
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_HAL_SetRxIndividualExtMask(
    CAN_Type * base,
    uint32_t msgBuffIdx,
    uint32_t extMask);

/*!
 * @brief Sets the FlexCAN receive Message Buffer global standard mask.
 *
 * @param   base  The FlexCAN base address
 * @param   stdMask     Standard mask
 */
void FLEXCAN_HAL_SetRxMsgBuffGlobalStdMask(
    CAN_Type * base,
    uint32_t stdMask);

/*!
 * @brief Sets the FlexCAN receive Message Buffer BUF14 standard mask.
 *
 * @param   base  The FlexCAN base address
 * @param   stdMask     Standard mask
 */
void FLEXCAN_HAL_SetRxMsgBuff14StdMask(
    CAN_Type * base,
    uint32_t stdMask);

/*!
 * @brief Sets the FlexCAN receive Message Buffer BUF15 standard mask.
 *
 * @param   base  The FlexCAN base address
 * @param   stdMask     Standard mask
 */
void FLEXCAN_HAL_SetRxMsgBuff15StdMask(
    CAN_Type * base,
    uint32_t stdMask);

/*!
 * @brief Sets the FlexCAN receive Message Buffer global extended mask.
 *
 * @param   base  The FlexCAN base address
 * @param   extMask     Extended mask
 */
void FLEXCAN_HAL_SetRxMsgBuffGlobalExtMask(
    CAN_Type * base,
    uint32_t extMask);

/*!
 * @brief Sets the FlexCAN receive Message Buffer BUF14 extended mask.
 *
 * @param   base  The FlexCAN base address
 * @param   extMask     Extended mask
 */
void FLEXCAN_HAL_SetRxMsgBuff14ExtMask(
    CAN_Type * base,
    uint32_t extMask);

/*!
 * @brief Sets the FlexCAN receive MB BUF15 extended mask.
 *
 * @param   base  The FlexCAN base address
 * @param   extMask     Extended mask
 */
void FLEXCAN_HAL_SetRxMsgBuff15ExtMask(
    CAN_Type * base,
    uint32_t extMask);

/*!
 * @brief Gets the FlexCAN ID acceptance filter hit indicator on receive FIFO.
 *
 * @param   base  The FlexCAN base address
 * @return  receive FIFO information
 */
static inline uint32_t  FLEXCAN_HAL_GetRxFifoHitIdAcceptanceFilter(CAN_Type * base)
{
    return CAN_BRD_RXFIR_IDHIT(base);
}

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_FLEXCAN_HAL_H__*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

