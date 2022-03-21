/*
 * Copyright (c) 2013-2017 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * $Date:        2. Feb 2017
 * $Revision:    V1.1
 *
 * Project:      SAI (Serial Audio Interface) Driver definitions
 */

/* History:
 *  Version 1.1
 *    ARM_SAI_STATUS made volatile
 *  Version 1.0
 *    Initial release
 */

#ifndef DRIVER_SAI_H_
#define DRIVER_SAI_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_Common.h"

#define ARM_SAI_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,1)  /* API version */


/****** SAI Control Codes *****/

#define ARM_SAI_CONTROL_Msk             (0xFFU)
#define ARM_SAI_CONFIGURE_TX            (0x01U)     ///< Configure Transmitter;  arg1 and arg2 provide additional configuration
#define ARM_SAI_CONFIGURE_RX            (0x02U)     ///< Configure Receiver;     arg1 and arg2 provide additional configuration
#define ARM_SAI_CONTROL_TX              (0x03U)     ///< Control Transmitter;    arg1.0: 0=disable (default), 1=enable; arg1.1: mute
#define ARM_SAI_CONTROL_RX              (0x04U)     ///< Control Receiver;       arg1.0: 0=disable (default), 1=enable
#define ARM_SAI_MASK_SLOTS_TX           (0x05U)     ///< Mask Transmitter slots; arg1 = mask (bit: 0=active, 1=inactive); all configured slots are active by default
#define ARM_SAI_MASK_SLOTS_RX           (0x06U)     ///< Mask Receiver    slots; arg1 = mask (bit: 0=active, 1=inactive); all configured slots are active by default
#define ARM_SAI_ABORT_SEND              (0x07U)     ///< Abort \ref ARM_SAI_Send
#define ARM_SAI_ABORT_RECEIVE           (0x08U)     ///< Abort \ref ARM_SAI_Receive

/*----- SAI Control Codes: Configuration Parameters: Mode -----*/
#define ARM_SAI_MODE_Pos                 8
#define ARM_SAI_MODE_Msk                (1U << ARM_SAI_MODE_Pos)
#define ARM_SAI_MODE_MASTER             (1U << ARM_SAI_MODE_Pos)                ///< Master Mode
#define ARM_SAI_MODE_SLAVE              (0U << ARM_SAI_MODE_Pos)                ///< Slave Mode (default)

/*----- SAI Control Codes: Configuration Parameters: Synchronization -----*/
#define ARM_SAI_SYNCHRONIZATION_Pos      9
#define ARM_SAI_SYNCHRONIZATION_Msk     (1U << ARM_SAI_SYNCHRONIZATION_Pos)
#define ARM_SAI_ASYNCHRONOUS            (0U << ARM_SAI_SYNCHRONIZATION_Pos)     ///< Asynchronous (default)
#define ARM_SAI_SYNCHRONOUS             (1U << ARM_SAI_SYNCHRONIZATION_Pos)     ///< Synchronous

/*----- SAI Control Codes: Configuration Parameters: Protocol -----*/
#define ARM_SAI_PROTOCOL_Pos             10
#define ARM_SAI_PROTOCOL_Msk            (7U << ARM_SAI_PROTOCOL_Pos)
#define ARM_SAI_PROTOCOL_USER           (0U << ARM_SAI_PROTOCOL_Pos)            ///< User defined (default) 
#define ARM_SAI_PROTOCOL_I2S            (1U << ARM_SAI_PROTOCOL_Pos)            ///< I2S
#define ARM_SAI_PROTOCOL_MSB_JUSTIFIED  (2U << ARM_SAI_PROTOCOL_Pos)            ///< MSB (left) justified 
#define ARM_SAI_PROTOCOL_LSB_JUSTIFIED  (3U << ARM_SAI_PROTOCOL_Pos)            ///< LSB (right) justified
#define ARM_SAI_PROTOCOL_PCM_SHORT      (4U << ARM_SAI_PROTOCOL_Pos)            ///< PCM with short frame
#define ARM_SAI_PROTOCOL_PCM_LONG       (5U << ARM_SAI_PROTOCOL_Pos)            ///< PCM with long frame
#define ARM_SAI_PROTOCOL_AC97           (6U << ARM_SAI_PROTOCOL_Pos)            ///< AC'97

/*----- SAI Control Codes: Configuration Parameters: Data Size -----*/
#define ARM_SAI_DATA_SIZE_Pos            13
#define ARM_SAI_DATA_SIZE_Msk                    (0x1FU  << ARM_SAI_DATA_SIZE_Pos)
#define ARM_SAI_DATA_SIZE(n)            ((((n)-1)&0x1FU) << ARM_SAI_DATA_SIZE_Pos)  ///< Data size in bits (8..32)

/*----- SAI Control Codes: Configuration Parameters: Bit Order -----*/
#define ARM_SAI_BIT_ORDER_Pos            18
#define ARM_SAI_BIT_ORDER_Msk           (1U << ARM_SAI_BIT_ORDER_Pos)
#define ARM_SAI_MSB_FIRST               (0U << ARM_SAI_BIT_ORDER_Pos)           ///< Data is transferred with MSB first (default)
#define ARM_SAI_LSB_FIRST               (1U << ARM_SAI_BIT_ORDER_Pos)           ///< Data is transferred with LSB first; User Protocol only (ignored otherwise)

/*----- SAI Control Codes: Configuration Parameters: Mono Mode -----*/
#define ARM_SAI_MONO_MODE               (1U << 19)                              ///< Mono Mode (only for I2S, MSB/LSB justified)

/*----- SAI Control Codes:Configuration Parameters: Companding -----*/
#define ARM_SAI_COMPANDING_Pos           20
#define ARM_SAI_COMPANDING_Msk          (3U << ARM_SAI_COMPANDING_Pos)
#define ARM_SAI_COMPANDING_NONE         (0U << ARM_SAI_COMPANDING_Pos)          ///< No companding (default)
#define ARM_SAI_COMPANDING_A_LAW        (2U << ARM_SAI_COMPANDING_Pos)          ///< A-Law companding
#define ARM_SAI_COMPANDING_U_LAW        (3U << ARM_SAI_COMPANDING_Pos)          ///< u-Law companding

/*----- SAI Control Codes: Configuration Parameters: Clock Polarity -----*/
#define ARM_SAI_CLOCK_POLARITY_Pos       23
#define ARM_SAI_CLOCK_POLARITY_Msk      (1U << ARM_SAI_CLOCK_POLARITY_Pos)
#define ARM_SAI_CLOCK_POLARITY_0        (0U << ARM_SAI_CLOCK_POLARITY_Pos)      ///< Drive on falling edge, Capture on rising  edge (default)
#define ARM_SAI_CLOCK_POLARITY_1        (1U << ARM_SAI_CLOCK_POLARITY_Pos)      ///< Drive on rising  edge, Capture on falling edge

/*----- SAI Control Codes: Configuration Parameters: Master Clock Pin -----*/
#define ARM_SAI_MCLK_PIN_Pos             24
#define ARM_SAI_MCLK_PIN_Msk            (3U << ARM_SAI_MCLK_PIN_Pos)
#define ARM_SAI_MCLK_PIN_INACTIVE       (0U << ARM_SAI_MCLK_PIN_Pos)            ///< MCLK not used (default)
#define ARM_SAI_MCLK_PIN_OUTPUT         (1U << ARM_SAI_MCLK_PIN_Pos)            ///< MCLK is output (Master only)
#define ARM_SAI_MCLK_PIN_INPUT          (2U << ARM_SAI_MCLK_PIN_Pos)            ///< MCLK is input  (Master only)


/****** SAI Configuration (arg1) *****/

/*----- SAI Configuration (arg1): Frame Length -----*/
#define ARM_SAI_FRAME_LENGTH_Pos          0
#define ARM_SAI_FRAME_LENGTH_Msk                  (0x3FFU  << ARM_SAI_FRAME_LENGTH_Pos)
#define ARM_SAI_FRAME_LENGTH(n)          ((((n)-1)&0x3FFU) << ARM_SAI_FRAME_LENGTH_Pos)     ///< Frame length in bits (8..1024); default depends on protocol and data

/*----- SAI Configuration (arg1): Frame Sync Width -----*/
#define ARM_SAI_FRAME_SYNC_WIDTH_Pos      10
#define ARM_SAI_FRAME_SYNC_WIDTH_Msk              (0xFFU  << ARM_SAI_FRAME_SYNC_WIDTH_Pos)
#define ARM_SAI_FRAME_SYNC_WIDTH(n)      ((((n)-1)&0xFFU) << ARM_SAI_FRAME_SYNC_WIDTH_Pos)  ///< Frame Sync width in bits (1..256); default=1; User Protocol only (ignored otherwise)

/*----- SAI Configuration (arg1): Frame Sync Polarity -----*/
#define ARM_SAI_FRAME_SYNC_POLARITY_Pos   18
#define ARM_SAI_FRAME_SYNC_POLARITY_Msk  (1U << ARM_SAI_FRAME_SYNC_POLARITY_Pos)
#define ARM_SAI_FRAME_SYNC_POLARITY_HIGH (0U << ARM_SAI_FRAME_SYNC_POLARITY_Pos)            ///< Frame Sync is active high (default); User Protocol only (ignored otherwise)
#define ARM_SAI_FRAME_SYNC_POLARITY_LOW  (1U << ARM_SAI_FRAME_SYNC_POLARITY_Pos)            ///< Frame Sync is active low; User Protocol only (ignored otherwise)

/*----- SAI Configuration (arg1): Frame Sync Early -----*/
#define ARM_SAI_FRAME_SYNC_EARLY         (1U << 19)                                         ///< Frame Sync one bit before the first bit of the frame; User Protocol only (ignored otherwise)

/*----- SAI Configuration (arg1): Slot Count -----*/
#define ARM_SAI_SLOT_COUNT_Pos            20
#define ARM_SAI_SLOT_COUNT_Msk                    (0x1FU  << ARM_SAI_SLOT_COUNT_Pos)
#define ARM_SAI_SLOT_COUNT(n)            ((((n)-1)&0x1FU) << ARM_SAI_SLOT_COUNT_Pos)        ///< Number of slots in frame (1..32); default=1; User Protocol only (ignored otherwise)

/*----- SAI Configuration (arg1): Slot Size -----*/
#define ARM_SAI_SLOT_SIZE_Pos             25
#define ARM_SAI_SLOT_SIZE_Msk            (3U << ARM_SAI_SLOT_SIZE_Pos)
#define ARM_SAI_SLOT_SIZE_DEFAULT        (0U << ARM_SAI_SLOT_SIZE_Pos)                      ///< Slot size is equal to data size (default)
#define ARM_SAI_SLOT_SIZE_16             (1U << ARM_SAI_SLOT_SIZE_Pos)                      ///< Slot size = 16 bits; User Protocol only (ignored otherwise)
#define ARM_SAI_SLOT_SIZE_32             (3U << ARM_SAI_SLOT_SIZE_Pos)                      ///< Slot size = 32 bits; User Protocol only (ignored otherwise)

/*----- SAI Configuration (arg1): Slot Offset -----*/
#define ARM_SAI_SLOT_OFFSET_Pos           27
#define ARM_SAI_SLOT_OFFSET_Msk               (0x1FU  << ARM_SAI_SLOT_OFFSET_Pos)
#define ARM_SAI_SLOT_OFFSET(n)           (((n)&0x1FU) << ARM_SAI_SLOT_OFFSET_Pos)           ///< Offset of first data bit in slot (0..31); default=0; User Protocol only (ignored otherwise)

/****** SAI Configuration (arg2) *****/

/*----- SAI Control Codes: Configuration Parameters: Audio Frequency (Master only) -----*/
#define ARM_SAI_AUDIO_FREQ_Msk          (0x0FFFFFU)                                         ///< Audio frequency mask

/*----- SAI Control Codes: Configuration Parameters: Master Clock Prescaler (Master only and MCLK Pin) -----*/
#define ARM_SAI_MCLK_PRESCALER_Pos       20
#define ARM_SAI_MCLK_PRESCALER_Msk      (0xFFFU << ARM_SAI_MCLK_PRESCALER_Pos)
#define ARM_SAI_MCLK_PRESCALER(n)       ((((n)-1)&0xFFFU) << ARM_SAI_MCLK_PRESCALER_Pos)    ///< MCLK prescaler; Audio_frequency = MCLK/n; n = 1..4096 (default=1)


/****** SAI specific error codes *****/
#define ARM_SAI_ERROR_SYNCHRONIZATION       (ARM_DRIVER_ERROR_SPECIFIC - 1)     ///< Specified Synchronization not supported
#define ARM_SAI_ERROR_PROTOCOL              (ARM_DRIVER_ERROR_SPECIFIC - 2)     ///< Specified Protocol not supported
#define ARM_SAI_ERROR_DATA_SIZE             (ARM_DRIVER_ERROR_SPECIFIC - 3)     ///< Specified Data size not supported
#define ARM_SAI_ERROR_BIT_ORDER             (ARM_DRIVER_ERROR_SPECIFIC - 4)     ///< Specified Bit order not supported
#define ARM_SAI_ERROR_MONO_MODE             (ARM_DRIVER_ERROR_SPECIFIC - 5)     ///< Specified Mono mode not supported
#define ARM_SAI_ERROR_COMPANDING            (ARM_DRIVER_ERROR_SPECIFIC - 6)     ///< Specified Companding not supported
#define ARM_SAI_ERROR_CLOCK_POLARITY        (ARM_DRIVER_ERROR_SPECIFIC - 7)     ///< Specified Clock polarity not supported
#define ARM_SAI_ERROR_AUDIO_FREQ            (ARM_DRIVER_ERROR_SPECIFIC - 8)     ///< Specified Audio frequency not supported
#define ARM_SAI_ERROR_MCLK_PIN              (ARM_DRIVER_ERROR_SPECIFIC - 9)     ///< Specified MCLK Pin setting not supported
#define ARM_SAI_ERROR_MCLK_PRESCALER        (ARM_DRIVER_ERROR_SPECIFIC - 10)    ///< Specified MCLK Prescaler not supported
#define ARM_SAI_ERROR_FRAME_LENGHT          (ARM_DRIVER_ERROR_SPECIFIC - 11)    ///< Specified Frame length not supported
#define ARM_SAI_ERROR_FRAME_SYNC_WIDTH      (ARM_DRIVER_ERROR_SPECIFIC - 12)    ///< Specified Frame Sync width not supported
#define ARM_SAI_ERROR_FRAME_SYNC_POLARITY   (ARM_DRIVER_ERROR_SPECIFIC - 13)    ///< Specified Frame Sync polarity not supported
#define ARM_SAI_ERROR_FRAME_SYNC_EARLY      (ARM_DRIVER_ERROR_SPECIFIC - 14)    ///< Specified Frame Sync early not supported
#define ARM_SAI_ERROR_SLOT_COUNT            (ARM_DRIVER_ERROR_SPECIFIC - 15)    ///< Specified Slot count not supported
#define ARM_SAI_ERROR_SLOT_SIZE             (ARM_DRIVER_ERROR_SPECIFIC - 16)    ///< Specified Slot size not supported
#define ARM_SAI_ERROR_SLOT_OFFESET          (ARM_DRIVER_ERROR_SPECIFIC - 17)    ///< Specified Slot offset not supported


/**
\brief SAI Status
*/
typedef volatile struct _ARM_SAI_STATUS {
  uint32_t tx_busy          : 1;        ///< Transmitter busy flag
  uint32_t rx_busy          : 1;        ///< Receiver busy flag
  uint32_t tx_underflow     : 1;        ///< Transmit data underflow detected (cleared on start of next send operation)
  uint32_t rx_overflow      : 1;        ///< Receive data overflow detected (cleared on start of next receive operation)
  uint32_t frame_error      : 1;        ///< Sync Frame error detected (cleared on start of next send/receive operation)
  uint32_t reserved         : 27;
} ARM_SAI_STATUS;


/****** SAI Event *****/
#define ARM_SAI_EVENT_SEND_COMPLETE     (1U << 0)   ///< Send completed
#define ARM_SAI_EVENT_RECEIVE_COMPLETE  (1U << 1)   ///< Receive completed
#define ARM_SAI_EVENT_TX_UNDERFLOW      (1U << 2)   ///< Transmit data not available
#define ARM_SAI_EVENT_RX_OVERFLOW       (1U << 3)   ///< Receive data overflow
#define ARM_SAI_EVENT_FRAME_ERROR       (1U << 4)   ///< Sync Frame error in Slave mode (optional)


// Function documentation
/**
  \fn          ARM_DRIVER_VERSION ARM_SAI_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION

  \fn          ARM_SAI_CAPABILITIES ARM_SAI_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref ARM_SAI_CAPABILITIES

  \fn          int32_t ARM_SAI_Initialize (ARM_SAI_SignalEvent_t cb_event)
  \brief       Initialize SAI Interface.
  \param[in]   cb_event  Pointer to \ref ARM_SAI_SignalEvent
  \return      \ref execution_status

  \fn          int32_t ARM_SAI_Uninitialize (void)
  \brief       De-initialize SAI Interface.
  \return      \ref execution_status

  \fn          int32_t ARM_SAI_PowerControl (ARM_POWER_STATE state)
  \brief       Control SAI Interface Power.
  \param[in]   state  Power state
  \return      \ref execution_status

  \fn          int32_t ARM_SAI_Send (const void *data, uint32_t num)
  \brief       Start sending data to SAI transmitter.
  \param[in]   data  Pointer to buffer with data to send to SAI transmitter
  \param[in]   num   Number of data items to send
  \return      \ref execution_status

  \fn          int32_t ARM_SAI_Receive (void *data, uint32_t num)
  \brief       Start receiving data from SAI receiver.
  \param[out]  data  Pointer to buffer for data to receive from SAI receiver
  \param[in]   num   Number of data items to receive
  \return      \ref execution_status

  \fn          uint32_t ARM_SAI_GetTxCount (void)
  \brief       Get transmitted data count.
  \return      number of data items transmitted

  \fn          uint32_t ARM_SAI_GetRxCount (void)
  \brief       Get received data count.
  \return      number of data items received

  \fn          int32_t ARM_SAI_Control (uint32_t control, uint32_t arg1, uint32_t arg2)
  \brief       Control SAI Interface.
  \param[in]   control  Operation
  \param[in]   arg1     Argument 1 of operation (optional)
  \param[in]   arg2     Argument 2 of operation (optional)
  \return      common \ref execution_status and driver specific \ref sai_execution_status

  \fn          ARM_SAI_STATUS ARM_SAI_GetStatus (void)
  \brief       Get SAI status.
  \return      SAI status \ref ARM_SAI_STATUS

  \fn          void ARM_SAI_SignalEvent (uint32_t event)
  \brief       Signal SAI Events.
  \param[in]   event \ref SAI_events notification mask
  \return      none
*/

typedef void (*ARM_SAI_SignalEvent_t) (uint32_t event);  ///< Pointer to \ref ARM_SAI_SignalEvent : Signal SAI Event.


/**
\brief SAI Driver Capabilities.
*/
typedef struct _ARM_SAI_CAPABILITIES {
  uint32_t asynchronous          : 1;   ///< supports asynchronous Transmit/Receive
  uint32_t synchronous           : 1;   ///< supports synchronous Transmit/Receive
  uint32_t protocol_user         : 1;   ///< supports user defined Protocol
  uint32_t protocol_i2s          : 1;   ///< supports I2S Protocol
  uint32_t protocol_justified    : 1;   ///< supports MSB/LSB justified Protocol
  uint32_t protocol_pcm          : 1;   ///< supports PCM short/long frame Protocol
  uint32_t protocol_ac97         : 1;   ///< supports AC'97 Protocol
  uint32_t mono_mode             : 1;   ///< supports Mono mode
  uint32_t companding            : 1;   ///< supports Companding
  uint32_t mclk_pin              : 1;   ///< supports MCLK (Master Clock) pin
  uint32_t event_frame_error     : 1;   ///< supports Frame error event: \ref ARM_SAI_EVENT_FRAME_ERROR
  uint32_t reserved              : 21;  ///< Reserved (must be zero)
} ARM_SAI_CAPABILITIES;


/**
\brief Access structure of the SAI Driver.
*/
typedef struct _ARM_DRIVER_SAI {
  ARM_DRIVER_VERSION   (*GetVersion)      (void);                                            ///< Pointer to \ref ARM_SAI_GetVersion : Get driver version.
  ARM_SAI_CAPABILITIES (*GetCapabilities) (void);                                            ///< Pointer to \ref ARM_SAI_GetCapabilities : Get driver capabilities.
  int32_t              (*Initialize)      (ARM_SAI_SignalEvent_t cb_event);                  ///< Pointer to \ref ARM_SAI_Initialize : Initialize SAI Interface.
  int32_t              (*Uninitialize)    (void);                                            ///< Pointer to \ref ARM_SAI_Uninitialize : De-initialize SAI Interface.
  int32_t              (*PowerControl)    (ARM_POWER_STATE state);                           ///< Pointer to \ref ARM_SAI_PowerControl : Control SAI Interface Power.
  int32_t              (*Send)            (const void *data, uint32_t num);                  ///< Pointer to \ref ARM_SAI_Send : Start sending data to SAI Interface.
  int32_t              (*Receive)         (      void *data, uint32_t num);                  ///< Pointer to \ref ARM_SAI_Receive : Start receiving data from SAI Interface.
  uint32_t             (*GetTxCount)      (void);                                            ///< Pointer to \ref ARM_SAI_GetTxCount : Get transmitted data count.
  uint32_t             (*GetRxCount)      (void);                                            ///< Pointer to \ref ARM_SAI_GetRxCount : Get received data count.
  int32_t              (*Control)         (uint32_t control, uint32_t arg1, uint32_t arg2);  ///< Pointer to \ref ARM_SAI_Control : Control SAI Interface.
  ARM_SAI_STATUS       (*GetStatus)       (void);                                            ///< Pointer to \ref ARM_SAI_GetStatus : Get SAI status.
} const ARM_DRIVER_SAI;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_SAI_H_ */
