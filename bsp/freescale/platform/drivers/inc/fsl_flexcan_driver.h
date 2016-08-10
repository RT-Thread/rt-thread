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
#ifndef __FSL_FLEXCAN_DRIVER_H__
#define __FSL_FLEXCAN_DRIVER_H__

#include "fsl_flexcan_hal.h"
#include "fsl_os_abstraction.h"
#if FSL_FEATURE_SOC_FLEXCAN_COUNT

/*!
 * @addtogroup flexcan_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Table of base addresses for FlexCAN instances. */
extern CAN_Type * const g_flexcanBase[];

/*! @brief Table to save RX Warning IRQ numbers for FlexCAN instances. */
extern const IRQn_Type g_flexcanRxWarningIrqId[];
/*! @brief Table to save TX Warning IRQ numbers for FlexCAN instances. */
extern const IRQn_Type g_flexcanTxWarningIrqId[];
/*! @brief Table to save wakeup IRQ numbers for FlexCAN instances. */
extern const IRQn_Type g_flexcanWakeUpIrqId[];
/*! @brief Table to save error IRQ numbers for FlexCAN instances. */
extern const IRQn_Type g_flexcanErrorIrqId[];
/*! @brief Table to save Bus off IRQ numbers for FlexCAN instances. */
extern const IRQn_Type g_flexcanBusOffIrqId[];
/*! @brief Table to save message buffer IRQ numbers for FlexCAN instances. */
extern const IRQn_Type g_flexcanOredMessageBufferIrqId[];

/*!
 * @brief Internal driver state information.
 *
 * @note The contents of this structure are internal to the driver and should not be
 *      modified by users. Also, contents of the structure are subject to change in
 *      future releases.
 */
typedef struct FlexCANState {
    flexcan_msgbuff_t *fifo_message;           /*!< The FlexCAN receive FIFO data*/
    flexcan_msgbuff_t *mb_message;		      /*!< The FlexCAN receive MB data*/
    volatile uint32_t rx_mb_idx;          /*!< Index of the message buffer for receiving*/
    volatile uint32_t tx_mb_idx;          /*!< Index of the message buffer for transmitting*/
    semaphore_t txIrqSync;                /*!< Used to wait for ISR to complete its TX business.*/
    semaphore_t rxIrqSync;                /*!< Used to wait for ISR to complete its RX business.*/
    volatile bool isTxBusy;        /*!< True if there is an active transmit. */
    volatile bool isRxBusy;        /*!< True if there is an active receive. */
    volatile bool isTxBlocking;    /*!< True if transmit is blocking transaction. */
    volatile bool isRxBlocking;    /*!< True if receive is blocking transaction. */
} flexcan_state_t;

/*! @brief FlexCAN data info from user*/
typedef struct FlexCANDataInfo {
    flexcan_msgbuff_id_type_t msg_id_type;            /*!< Type of message ID (standard or extended)*/
    uint32_t data_length;                        /*!< Length of Data in Bytes*/
} flexcan_data_info_t;

/*! @brief FlexCAN configuration
 * @internal gui name="Common configuration" id="flexcanCfg"
 */
typedef struct FLEXCANUserConfig {
    uint32_t max_num_mb;                            /*!< The maximum number of Message Buffers @internal gui name="Maximum number of message buffers" id="max_num_mb" */
    flexcan_rx_fifo_id_filter_num_t num_id_filters; /*!< The number of RX FIFO ID filters needed @internal gui name="Number of RX FIFO ID filters" id="num_id_filters" */
    bool is_rx_fifo_needed;                         /*!< 1 if needed; 0 if not. This controls whether the Rx FIFO feature is enabled or not. @internal gui name="Use rx fifo" id="is_rx_fifo_needed" */
    flexcan_operation_modes_t flexcanMode;          /*!< User configurable FlexCAN operation modes. @internal gui name="Flexcan Operation Mode" id="flexcanMode"*/
} flexcan_user_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Bit rate
 * @{
 */

/*!
 * @brief Sets the FlexCAN bit rate.
 *
 * @param   instance    A FlexCAN instance number
 * @param   bitrate     A pointer to the FlexCAN bit rate settings.
 *
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_DRV_SetBitrate(uint8_t instance, flexcan_time_segment_t *bitrate);

/*!
 * @brief Gets the FlexCAN bit rate.
 *
 * @param   instance    A FlexCAN instance number
 * @param   bitrate     A pointer to a variable for returning the FlexCAN bit rate settings
 *
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_DRV_GetBitrate(uint8_t instance, flexcan_time_segment_t *bitrate);

/*@}*/

/*!
 * @name Global mask
 * @{
 */

/*!
 * @brief Sets the RX masking type.
 *
 * @param   instance     A FlexCAN instance number
 * @param   type         The FlexCAN RX mask type
 */
void FLEXCAN_DRV_SetRxMaskType(uint8_t instance, flexcan_rx_mask_type_t type);

/*!
 * @brief Sets the FlexCAN RX FIFO global standard or extended mask.
 *
 * @param   instance    A FlexCAN instance number
 * @param   id_type     Standard ID or extended ID
 * @param   mask        Mask value
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_DRV_SetRxFifoGlobalMask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint32_t mask);

/*!
 * @brief Sets the FlexCAN RX MB global standard or extended mask.
 *
 * @param   instance    A FlexCAN instance number
 * @param   id_type     Standard ID or extended ID
 * @param   mask        Mask value
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_DRV_SetRxMbGlobalMask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint32_t mask);

/*!
 * @brief Sets the FlexCAN RX individual standard or extended mask.
 *
 * @param   instance  A FlexCAN instance number
 * @param   id_type   A standard ID or an extended ID
 * @param   mb_idx    Index of the message buffer
 * @param   mask      Mask value
 *
 * @return  0 if successful; non-zero failed.
 */
flexcan_status_t FLEXCAN_DRV_SetRxIndividualMask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint32_t mb_idx,
    uint32_t mask);

/*@}*/

/*!
 * @name Initialization and Shutdown
 * @{
 */

/*!
 * @brief Initializes the FlexCAN peripheral.
 *
 * This function initializes
 * @param   instance                   A FlexCAN instance number
 * @param   state                      Pointer to the FlexCAN driver state structure.
 * @param   data                       The FlexCAN platform data
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_DRV_Init(
	   uint32_t instance,
	   flexcan_state_t *state,
	   const flexcan_user_config_t *data);

/*!
 * @brief Shuts down a FlexCAN instance.
 *
 * @param   instance    A FlexCAN instance number
 * @return  0 if successful; non-zero failed
 */
uint32_t FLEXCAN_DRV_Deinit(uint8_t instance);

/*@}*/

/*!
 * @name Send configuration
 * @{
 */

/*!
 * @brief FlexCAN transmit message buffer field configuration.
 *
 * @param   instance                   A FlexCAN instance number
 * @param   mb_idx                     Index of the message buffer
 * @param   tx_info                    Data info
 * @param   msg_id                     ID of the message to transmit
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_DRV_ConfigTxMb(
    uint8_t instance,
    uint32_t mb_idx,
    flexcan_data_info_t *tx_info,
    uint32_t msg_id);

/*!
 * @brief Sends FlexCAN messages.
 *
 * @param   instance   A FlexCAN instance number
 * @param   mb_idx     Index of the message buffer
 * @param   tx_info    Data info
 * @param   msg_id     ID of the message to transmit
 * @param   mb_data    Bytes of the FlexCAN message
 * @param   timeout_ms A timeout for the transfer in milliseconds.
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_DRV_SendBlocking(
    uint8_t instance,
    uint32_t mb_idx,
    flexcan_data_info_t *tx_info,
    uint32_t msg_id,
    uint8_t *mb_data,
    uint32_t timeout_ms);

/*!
 * @brief Sends FlexCAN messages.
 *
 * @param   instance   A FlexCAN instance number
 * @param   mb_idx     Index of the message buffer
 * @param   tx_info    Data info
 * @param   msg_id     ID of the message to transmit
 * @param   mb_data    Bytes of the FlexCAN message.
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_DRV_Send(
    uint8_t instance,
    uint32_t mb_idx,
    flexcan_data_info_t *tx_info,
    uint32_t msg_id,
    uint8_t *mb_data);


/*@}*/

/*!
 * @name Receive configuration
 * @{
 */

/*!
 * @brief FlexCAN receive message buffer field configuration
 *
 * @param   instance                   A FlexCAN instance number
 * @param   mb_idx                     Index of the message buffer
 * @param   rx_info                    Data info
 * @param   msg_id                     ID of the message to transmit
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_DRV_ConfigRxMb(
    uint8_t instance,
    uint32_t mb_idx,
    flexcan_data_info_t *rx_info,
    uint32_t msg_id);

/*!
 * @brief FlexCAN RX FIFO field configuration
 *
 * @param   instance           A FlexCAN instance number
 * @param   id_format          The format of the RX FIFO ID Filter Table Elements
 * @param   id_filter_table    The ID filter table elements which contain RTR bit, IDE bit,
 *                             and RX message ID
 * @return  0 if successful; non-zero failed.
 */
flexcan_status_t FLEXCAN_DRV_ConfigRxFifo(
    uint8_t instance,
    flexcan_rx_fifo_id_element_format_t id_format,
    flexcan_id_table_t *id_filter_table);

/*!
 * @brief FlexCAN is waiting to receive data from the message buffer.
 *
 * @param   instance   A FlexCAN instance number
 * @param   mb_idx     Index of the message buffer
 * @param   data       The FlexCAN receive message buffer data.
 * @param   timeout_ms A timeout for the transfer in milliseconds.
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_DRV_RxMessageBufferBlocking(
    uint8_t instance,
    uint32_t mb_idx,
    flexcan_msgbuff_t *data,
    uint32_t timeout_ms);

/*!
 * @brief FlexCAN is waiting to receive data from the message buffer.
 *
 * @param   instance   A FlexCAN instance number
 * @param   mb_idx     Index of the message buffer
 * @param   data       The FlexCAN receive message buffer data.
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_DRV_RxMessageBuffer(
    uint8_t instance,
    uint32_t mb_idx,
    flexcan_msgbuff_t *data);

/*!
 * @brief FlexCAN is waiting to receive data from the message FIFO.
 *
 * @param   instance    A FlexCAN instance number
 * @param   data        The FlexCAN receive message buffer data.
 * @param   timeout_ms  A timeout for the transfer in milliseconds.
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_DRV_RxFifoBlocking(
    uint8_t instance,
    flexcan_msgbuff_t *data,
    uint32_t timeout_ms);

/*!
 * @brief FlexCAN is waiting to receive data from the message FIFO.
 *
 * @param   instance    A FlexCAN instance number
 * @param   data        The FlexCAN receive message buffer data.
 * @return  0 if successful; non-zero failed
 */
flexcan_status_t FLEXCAN_DRV_RxFifo(
    uint8_t instance,
    flexcan_msgbuff_t *data);

/*@}*/

/*!
 * @brief Interrupt handler for a FlexCAN instance.
 *
 * @param   instance    The FlexCAN instance number.
 */
void FLEXCAN_DRV_IRQHandler(uint8_t instance);

/*!
 * @brief Returns whether the previous FLEXCAN transmit has finished.
 *
 * When performing an async transmit, call this function to ascertain the state of the
 * current transmission: in progress (or busy) or complete (success).
 *
 * @param instance The FLEXCAN module base address.
 * @return The transmit status.
 * @retval kStatus_FLEXCAN_Success The transmit has completed successfully.
 * @retval kStatus_FLEXCAN_TxBusy The transmit is still in progress.
 */
flexcan_status_t FLEXCAN_DRV_GetTransmitStatus(uint32_t instance);

/*!
 * @brief Returns whether the previous FLEXCAN receive is complete.
 *
 * When performing an async receive, call this function to find out the state of the
 * current receive progress: in progress (or busy) or complete (success).
 *
 * @param instance The FLEXCAN module base address.
 * @param bytesRemaining A pointer to a value that is filled in with the number of bytes which
 *                       still need to be received in the active transfer.
 * @return The receive status.
 * @retval kStatus_FLEXCAN_Success The receive has completed successfully.
 * @retval kStatus_FLEXCAN_RxBusy The receive is still in progress.
 */
flexcan_status_t FLEXCAN_DRV_GetReceiveStatus(uint32_t instance);

#ifdef __cplusplus
}
#endif

/*! @}*/

#endif
#endif /* __FSL_FLEXCAN_DRIVER_H__*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

