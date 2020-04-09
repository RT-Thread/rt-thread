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
 * $Revision:    V2.2
 *
 * Project:      USB Device Driver definitions
 */

/* History:
 *  Version 2.2
 *    ARM_USBD_STATE made volatile
 *  Version 2.1
 *    Added ARM_USBD_ReadSetupPacket function
 *  Version 2.0
 *    Removed ARM_USBD_DeviceConfigure function
 *    Removed ARM_USBD_SET_ADDRESS_STAGE parameter from ARM_USBD_DeviceSetAddress function
 *    Removed ARM_USBD_EndpointReadStart function
 *    Replaced ARM_USBD_EndpointRead and ARM_USBD_EndpointWrite functions with ARM_USBD_EndpointTransfer
 *    Added ARM_USBD_EndpointTransferGetResult function
 *    Renamed ARM_USBD_EndpointAbort function to ARM_USBD_EndpointTransferAbort
 *    Changed prefix ARM_DRV -> ARM_DRIVER
 *    Changed return values of some functions to int32_t
 *  Version 1.10
 *    Namespace prefix ARM_ added
 *  Version 1.00
 *    Initial release
 */

#ifndef DRIVER_USBD_H_
#define DRIVER_USBD_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_USB.h"

#define ARM_USBD_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2,2)  /* API version */


/**
\brief USB Device State
*/
typedef volatile struct _ARM_USBD_STATE {
  uint32_t vbus     : 1;                ///< USB Device VBUS flag
  uint32_t speed    : 2;                ///< USB Device speed setting (ARM_USB_SPEED_xxx)
  uint32_t active   : 1;                ///< USB Device active flag
  uint32_t reserved : 28;
} ARM_USBD_STATE;


/****** USB Device Event *****/
#define ARM_USBD_EVENT_VBUS_ON          (1UL << 0)      ///< USB Device VBUS On
#define ARM_USBD_EVENT_VBUS_OFF         (1UL << 1)      ///< USB Device VBUS Off
#define ARM_USBD_EVENT_RESET            (1UL << 2)      ///< USB Reset occurred
#define ARM_USBD_EVENT_HIGH_SPEED       (1UL << 3)      ///< USB switch to High Speed occurred
#define ARM_USBD_EVENT_SUSPEND          (1UL << 4)      ///< USB Suspend occurred
#define ARM_USBD_EVENT_RESUME           (1UL << 5)      ///< USB Resume occurred

/****** USB Endpoint Event *****/
#define ARM_USBD_EVENT_SETUP            (1UL << 0)      ///< SETUP Packet
#define ARM_USBD_EVENT_OUT              (1UL << 1)      ///< OUT Packet(s)
#define ARM_USBD_EVENT_IN               (1UL << 2)      ///< IN Packet(s)


#ifndef __DOXYGEN_MW__                  // exclude from middleware documentation

// Function documentation
/**
  \fn          ARM_DRIVER_VERSION ARM_USBD_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION
*/
/**
  \fn          ARM_USBD_CAPABILITIES ARM_USBD_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref ARM_USBD_CAPABILITIES
*/
/**
  \fn          int32_t ARM_USBD_Initialize (ARM_USBD_SignalDeviceEvent_t   cb_device_event,
                                            ARM_USBD_SignalEndpointEvent_t cb_endpoint_event)
  \brief       Initialize USB Device Interface.
  \param[in]   cb_device_event    Pointer to \ref ARM_USBD_SignalDeviceEvent
  \param[in]   cb_endpoint_event  Pointer to \ref ARM_USBD_SignalEndpointEvent
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBD_Uninitialize (void)
  \brief       De-initialize USB Device Interface.
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBD_PowerControl (ARM_POWER_STATE state)
  \brief       Control USB Device Interface Power.
  \param[in]   state  Power state
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBD_DeviceConnect (void)
  \brief       Connect USB Device.
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBD_DeviceDisconnect (void)
  \brief       Disconnect USB Device.
  \return      \ref execution_status
*/
/**
  \fn          ARM_USBD_STATE ARM_USBD_DeviceGetState (void)
  \brief       Get current USB Device State.
  \return      Device State \ref ARM_USBD_STATE
*/
/**
  \fn          int32_t ARM_USBD_DeviceRemoteWakeup (void)
  \brief       Trigger USB Remote Wakeup.
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBD_DeviceSetAddress (uint8_t dev_addr)
  \brief       Set USB Device Address.
  \param[in]   dev_addr  Device Address
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBD_ReadSetupPacket (uint8_t *setup)
  \brief       Read setup packet received over Control Endpoint.
  \param[out]  setup  Pointer to buffer for setup packet
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBD_EndpointConfigure (uint8_t  ep_addr,
                                                   uint8_t  ep_type,
                                                   uint16_t ep_max_packet_size)
  \brief       Configure USB Endpoint.
  \param[in]   ep_addr  Endpoint Address
                - ep_addr.0..3: Address
                - ep_addr.7:    Direction
  \param[in]   ep_type  Endpoint Type (ARM_USB_ENDPOINT_xxx)
  \param[in]   ep_max_packet_size Endpoint Maximum Packet Size
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBD_EndpointUnconfigure (uint8_t ep_addr)
  \brief       Unconfigure USB Endpoint.
  \param[in]   ep_addr  Endpoint Address
                - ep_addr.0..3: Address
                - ep_addr.7:    Direction
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBD_EndpointStall (uint8_t ep_addr, bool stall)
  \brief       Set/Clear Stall for USB Endpoint.
  \param[in]   ep_addr  Endpoint Address
                - ep_addr.0..3: Address
                - ep_addr.7:    Direction
  \param[in]   stall  Operation
                - \b false Clear
                - \b true Set
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBD_EndpointTransfer (uint8_t ep_addr, uint8_t *data, uint32_t num)
  \brief       Read data from or Write data to USB Endpoint.
  \param[in]   ep_addr  Endpoint Address
                - ep_addr.0..3: Address
                - ep_addr.7:    Direction
  \param[out]  data Pointer to buffer for data to read or with data to write
  \param[in]   num  Number of data bytes to transfer
  \return      \ref execution_status
*/
/**
  \fn          uint32_t ARM_USBD_EndpointTransferGetResult (uint8_t ep_addr)
  \brief       Get result of USB Endpoint transfer.
  \param[in]   ep_addr  Endpoint Address
                - ep_addr.0..3: Address
                - ep_addr.7:    Direction
  \return      number of successfully transferred data bytes
*/
/**
  \fn          int32_t ARM_USBD_EndpointTransferAbort (uint8_t ep_addr)
  \brief       Abort current USB Endpoint transfer.
  \param[in]   ep_addr  Endpoint Address
                - ep_addr.0..3: Address
                - ep_addr.7:    Direction
  \return      \ref execution_status
*/
/**
  \fn          uint16_t ARM_USBD_GetFrameNumber (void)
  \brief       Get current USB Frame Number.
  \return      Frame Number
*/

/**
  \fn          void ARM_USBD_SignalDeviceEvent (uint32_t event)
  \brief       Signal USB Device Event.
  \param[in]   event \ref USBD_dev_events
  \return      none
*/
/**
  \fn          void ARM_USBD_SignalEndpointEvent (uint8_t ep_addr, uint32_t event)
  \brief       Signal USB Endpoint Event.
  \param[in]   ep_addr  Endpoint Address
                - ep_addr.0..3: Address
                - ep_addr.7:    Direction
  \param[in]   event \ref USBD_ep_events
  \return      none
*/

typedef void (*ARM_USBD_SignalDeviceEvent_t)   (uint32_t event);                    ///< Pointer to \ref ARM_USBD_SignalDeviceEvent : Signal USB Device Event.
typedef void (*ARM_USBD_SignalEndpointEvent_t) (uint8_t ep_addr, uint32_t event);   ///< Pointer to \ref ARM_USBD_SignalEndpointEvent : Signal USB Endpoint Event.


/**
\brief USB Device Driver Capabilities.
*/
typedef struct _ARM_USBD_CAPABILITIES {
  uint32_t vbus_detection  : 1;         ///< VBUS detection
  uint32_t event_vbus_on   : 1;         ///< Signal VBUS On event
  uint32_t event_vbus_off  : 1;         ///< Signal VBUS Off event
  uint32_t reserved        : 29;        ///< Reserved (must be zero)
} ARM_USBD_CAPABILITIES;


/**
\brief Access structure of the USB Device Driver.
*/
typedef struct _ARM_DRIVER_USBD {
  ARM_DRIVER_VERSION    (*GetVersion)                (void);                                              ///< Pointer to \ref ARM_USBD_GetVersion : Get driver version.
  ARM_USBD_CAPABILITIES (*GetCapabilities)           (void);                                              ///< Pointer to \ref ARM_USBD_GetCapabilities : Get driver capabilities.
  int32_t               (*Initialize)                (ARM_USBD_SignalDeviceEvent_t   cb_device_event,                     
                                                      ARM_USBD_SignalEndpointEvent_t cb_endpoint_event);  ///< Pointer to \ref ARM_USBD_Initialize : Initialize USB Device Interface. 
  int32_t               (*Uninitialize)              (void);                                              ///< Pointer to \ref ARM_USBD_Uninitialize : De-initialize USB Device Interface.
  int32_t               (*PowerControl)              (ARM_POWER_STATE state);                             ///< Pointer to \ref ARM_USBD_PowerControl : Control USB Device Interface Power.
  int32_t               (*DeviceConnect)             (void);                                              ///< Pointer to \ref ARM_USBD_DeviceConnect : Connect USB Device.
  int32_t               (*DeviceDisconnect)          (void);                                              ///< Pointer to \ref ARM_USBD_DeviceDisconnect : Disconnect USB Device.
  ARM_USBD_STATE        (*DeviceGetState)            (void);                                              ///< Pointer to \ref ARM_USBD_DeviceGetState : Get current USB Device State.
  int32_t               (*DeviceRemoteWakeup)        (void);                                              ///< Pointer to \ref ARM_USBD_DeviceRemoteWakeup : Trigger USB Remote Wakeup.
  int32_t               (*DeviceSetAddress)          (uint8_t dev_addr);                                  ///< Pointer to \ref ARM_USBD_DeviceSetAddress : Set USB Device Address.
  int32_t               (*ReadSetupPacket)           (uint8_t *setup);                                    ///< Pointer to \ref ARM_USBD_ReadSetupPacket : Read setup packet received over Control Endpoint.
  int32_t               (*EndpointConfigure)         (uint8_t ep_addr,
                                                      uint8_t ep_type,
                                                      uint16_t ep_max_packet_size);                       ///< Pointer to \ref ARM_USBD_EndpointConfigure : Configure USB Endpoint.
  int32_t               (*EndpointUnconfigure)       (uint8_t ep_addr);                                   ///< Pointer to \ref ARM_USBD_EndpointUnconfigure : Unconfigure USB Endpoint.
  int32_t               (*EndpointStall)             (uint8_t ep_addr, bool stall);                       ///< Pointer to \ref ARM_USBD_EndpointStall : Set/Clear Stall for USB Endpoint.
  int32_t               (*EndpointTransfer)          (uint8_t ep_addr, uint8_t *data, uint32_t num);      ///< Pointer to \ref ARM_USBD_EndpointTransfer : Read data from or Write data to USB Endpoint.
  uint32_t              (*EndpointTransferGetResult) (uint8_t ep_addr);                                   ///< Pointer to \ref ARM_USBD_EndpointTransferGetResult : Get result of USB Endpoint transfer.
  int32_t               (*EndpointTransferAbort)     (uint8_t ep_addr);                                   ///< Pointer to \ref ARM_USBD_EndpointTransferAbort : Abort current USB Endpoint transfer.
  uint16_t              (*GetFrameNumber)            (void);                                              ///< Pointer to \ref ARM_USBD_GetFrameNumber : Get current USB Frame Number.
} const ARM_DRIVER_USBD;

#endif /* __DOXYGEN_MW__ */

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_USBD_H_ */
