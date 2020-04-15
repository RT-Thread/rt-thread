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
 * $Revision:    V2.3
 *
 * Project:      I2C (Inter-Integrated Circuit) Driver definitions
 */

/* History:
 *  Version 2.3
 *    ARM_I2C_STATUS made volatile
 *  Version 2.2
 *    Removed function ARM_I2C_MasterTransfer in order to simplify drivers
 *      and added back parameter "xfer_pending" to functions
 *      ARM_I2C_MasterTransmit and ARM_I2C_MasterReceive
 *  Version 2.1
 *    Added function ARM_I2C_MasterTransfer and removed parameter "xfer_pending"
 *      from functions ARM_I2C_MasterTransmit and ARM_I2C_MasterReceive
 *    Added function ARM_I2C_GetDataCount
 *    Removed flag "address_nack" from ARM_I2C_STATUS
 *    Replaced events ARM_I2C_EVENT_MASTER_DONE and ARM_I2C_EVENT_SLAVE_DONE
 *      with event ARM_I2C_EVENT_TRANSFER_DONE
 *    Added event ARM_I2C_EVENT_TRANSFER_INCOMPLETE
 *    Removed parameter "arg" from function ARM_I2C_SignalEvent
 *  Version 2.0
 *    New simplified driver:
 *      complexity moved to upper layer (especially data handling)
 *      more unified API for different communication interfaces
 *    Added:
 *      Slave Mode
 *    Changed prefix ARM_DRV -> ARM_DRIVER
 *  Version 1.10
 *    Namespace prefix ARM_ added
 *  Version 1.00
 *    Initial release
 */

#ifndef DRIVER_I2C_H_
#define DRIVER_I2C_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_Common.h"

#define ARM_I2C_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2,3)  /* API version */


/****** I2C Control Codes *****/

#define ARM_I2C_OWN_ADDRESS             (0x01)      ///< Set Own Slave Address; arg = address 
#define ARM_I2C_BUS_SPEED               (0x02)      ///< Set Bus Speed; arg = speed
#define ARM_I2C_BUS_CLEAR               (0x03)      ///< Execute Bus clear: send nine clock pulses
#define ARM_I2C_ABORT_TRANSFER          (0x04)      ///< Abort Master/Slave Transmit/Receive

/*----- I2C Bus Speed -----*/
#define ARM_I2C_BUS_SPEED_STANDARD      (0x01)      ///< Standard Speed (100kHz)
#define ARM_I2C_BUS_SPEED_FAST          (0x02)      ///< Fast Speed     (400kHz)
#define ARM_I2C_BUS_SPEED_FAST_PLUS     (0x03)      ///< Fast+ Speed    (  1MHz)
#define ARM_I2C_BUS_SPEED_HIGH          (0x04)      ///< High Speed     (3.4MHz)


/****** I2C Address Flags *****/

#define ARM_I2C_ADDRESS_10BIT           (0x0400)    ///< 10-bit address flag
#define ARM_I2C_ADDRESS_GC              (0x8000)    ///< General Call flag


/**
\brief I2C Status
*/
typedef volatile struct _ARM_I2C_STATUS {
  uint32_t busy             : 1;        ///< Busy flag
  uint32_t mode             : 1;        ///< Mode: 0=Slave, 1=Master
  uint32_t direction        : 1;        ///< Direction: 0=Transmitter, 1=Receiver
  uint32_t general_call     : 1;        ///< General Call indication (cleared on start of next Slave operation)
  uint32_t arbitration_lost : 1;        ///< Master lost arbitration (cleared on start of next Master operation)
  uint32_t bus_error        : 1;        ///< Bus error detected (cleared on start of next Master/Slave operation)
  uint32_t reserved         : 26;
} ARM_I2C_STATUS;


/****** I2C Event *****/
#define ARM_I2C_EVENT_TRANSFER_DONE       (1UL << 0)  ///< Master/Slave Transmit/Receive finished
#define ARM_I2C_EVENT_TRANSFER_INCOMPLETE (1UL << 1)  ///< Master/Slave Transmit/Receive incomplete transfer
#define ARM_I2C_EVENT_SLAVE_TRANSMIT      (1UL << 2)  ///< Slave Transmit operation requested
#define ARM_I2C_EVENT_SLAVE_RECEIVE       (1UL << 3)  ///< Slave Receive operation requested
#define ARM_I2C_EVENT_ADDRESS_NACK        (1UL << 4)  ///< Address not acknowledged from Slave
#define ARM_I2C_EVENT_GENERAL_CALL        (1UL << 5)  ///< General Call indication
#define ARM_I2C_EVENT_ARBITRATION_LOST    (1UL << 6)  ///< Master lost arbitration
#define ARM_I2C_EVENT_BUS_ERROR           (1UL << 7)  ///< Bus error detected (START/STOP at illegal position)
#define ARM_I2C_EVENT_BUS_CLEAR           (1UL << 8)  ///< Bus clear finished


// Function documentation
/**
  \fn          ARM_DRIVER_VERSION ARM_I2C_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION

  \fn          ARM_I2C_CAPABILITIES ARM_I2C_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref ARM_I2C_CAPABILITIES

  \fn          int32_t ARM_I2C_Initialize (ARM_I2C_SignalEvent_t cb_event)
  \brief       Initialize I2C Interface.
  \param[in]   cb_event  Pointer to \ref ARM_I2C_SignalEvent
  \return      \ref execution_status

  \fn          int32_t ARM_I2C_Uninitialize (void)
  \brief       De-initialize I2C Interface.
  \return      \ref execution_status

  \fn          int32_t ARM_I2C_PowerControl (ARM_POWER_STATE state)
  \brief       Control I2C Interface Power.
  \param[in]   state  Power state
  \return      \ref execution_status

  \fn          int32_t ARM_I2C_MasterTransmit (uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
  \brief       Start transmitting data as I2C Master.
  \param[in]   addr          Slave address (7-bit or 10-bit)
  \param[in]   data          Pointer to buffer with data to transmit to I2C Slave
  \param[in]   num           Number of data bytes to transmit
  \param[in]   xfer_pending  Transfer operation is pending - Stop condition will not be generated
  \return      \ref execution_status

  \fn          int32_t ARM_I2C_MasterReceive (uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
  \brief       Start receiving data as I2C Master.
  \param[in]   addr          Slave address (7-bit or 10-bit)
  \param[out]  data          Pointer to buffer for data to receive from I2C Slave
  \param[in]   num           Number of data bytes to receive
  \param[in]   xfer_pending  Transfer operation is pending - Stop condition will not be generated
  \return      \ref execution_status

  \fn          int32_t ARM_I2C_SlaveTransmit (const uint8_t *data, uint32_t num)
  \brief       Start transmitting data as I2C Slave.
  \param[in]   data  Pointer to buffer with data to transmit to I2C Master
  \param[in]   num   Number of data bytes to transmit
  \return      \ref execution_status

  \fn          int32_t ARM_I2C_SlaveReceive (uint8_t *data, uint32_t num)
  \brief       Start receiving data as I2C Slave.
  \param[out]  data  Pointer to buffer for data to receive from I2C Master
  \param[in]   num   Number of data bytes to receive
  \return      \ref execution_status

  \fn          int32_t ARM_I2C_GetDataCount (void)
  \brief       Get transferred data count.
  \return      number of data bytes transferred; -1 when Slave is not addressed by Master

  \fn          int32_t ARM_I2C_Control (uint32_t control, uint32_t arg)
  \brief       Control I2C Interface.
  \param[in]   control  Operation
  \param[in]   arg      Argument of operation (optional)
  \return      \ref execution_status

  \fn          ARM_I2C_STATUS ARM_I2C_GetStatus (void)
  \brief       Get I2C status.
  \return      I2C status \ref ARM_I2C_STATUS

  \fn          void ARM_I2C_SignalEvent (uint32_t event)
  \brief       Signal I2C Events.
  \param[in]   event  \ref I2C_events notification mask
*/

typedef void (*ARM_I2C_SignalEvent_t) (uint32_t event);  ///< Pointer to \ref ARM_I2C_SignalEvent : Signal I2C Event.


/**
\brief I2C Driver Capabilities.
*/
typedef struct _ARM_I2C_CAPABILITIES {
  uint32_t address_10_bit : 1;          ///< supports 10-bit addressing
  uint32_t reserved       : 31;         ///< Reserved (must be zero)
} ARM_I2C_CAPABILITIES;


/**
\brief Access structure of the I2C Driver.
*/
typedef struct _ARM_DRIVER_I2C {
  ARM_DRIVER_VERSION   (*GetVersion)     (void);                                                                ///< Pointer to \ref ARM_I2C_GetVersion : Get driver version.
  ARM_I2C_CAPABILITIES (*GetCapabilities)(void);                                                                ///< Pointer to \ref ARM_I2C_GetCapabilities : Get driver capabilities.
  int32_t              (*Initialize)     (ARM_I2C_SignalEvent_t cb_event);                                      ///< Pointer to \ref ARM_I2C_Initialize : Initialize I2C Interface.
  int32_t              (*Uninitialize)   (void);                                                                ///< Pointer to \ref ARM_I2C_Uninitialize : De-initialize I2C Interface.
  int32_t              (*PowerControl)   (ARM_POWER_STATE state);                                               ///< Pointer to \ref ARM_I2C_PowerControl : Control I2C Interface Power.
  int32_t              (*MasterTransmit) (uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending); ///< Pointer to \ref ARM_I2C_MasterTransmit : Start transmitting data as I2C Master.
  int32_t              (*MasterReceive)  (uint32_t addr,       uint8_t *data, uint32_t num, bool xfer_pending); ///< Pointer to \ref ARM_I2C_MasterReceive : Start receiving data as I2C Master.
  int32_t              (*SlaveTransmit)  (               const uint8_t *data, uint32_t num);                    ///< Pointer to \ref ARM_I2C_SlaveTransmit : Start transmitting data as I2C Slave.
  int32_t              (*SlaveReceive)   (                     uint8_t *data, uint32_t num);                    ///< Pointer to \ref ARM_I2C_SlaveReceive : Start receiving data as I2C Slave.
  int32_t              (*GetDataCount)   (void);                                                                ///< Pointer to \ref ARM_I2C_GetDataCount : Get transferred data count.
  int32_t              (*Control)        (uint32_t control, uint32_t arg);                                      ///< Pointer to \ref ARM_I2C_Control : Control I2C Interface.
  ARM_I2C_STATUS       (*GetStatus)      (void);                                                                ///< Pointer to \ref ARM_I2C_GetStatus : Get I2C status.
} const ARM_DRIVER_I2C;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_I2C_H_ */
