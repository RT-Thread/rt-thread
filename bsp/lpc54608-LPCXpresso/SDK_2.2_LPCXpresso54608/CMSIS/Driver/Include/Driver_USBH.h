/* -----------------------------------------------------------------------------
 * Copyright (c) 2013-2014 ARM Ltd.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software. Permission is granted to anyone to use this
 * software for any purpose, including commercial applications, and to alter
 * it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *
 * $Date:        3. September 2014
 * $Revision:    V2.01
 *
 * Project:      USB Host Driver definitions
 * -------------------------------------------------------------------------- */

/* History:
 *  Version 2.01
 *    Renamed structure ARM_USBH_EP_HANDLE to ARM_USBH_PIPE_HANDLE
 *    Renamed functions ARM_USBH_Endpoint... to ARM_USBH_Pipe...
 *    Renamed function ARM_USBH_SignalEndpointEvent to ARM_USBH_SignalPipeEvent
 *  Version 2.00
 *    Replaced function ARM_USBH_PortPowerOnOff with ARM_USBH_PortVbusOnOff
 *    Changed function ARM_USBH_EndpointCreate parameters
 *    Replaced function ARM_USBH_EndpointConfigure with ARM_USBH_EndpointModify
 *    Replaced function ARM_USBH_EndpointClearHalt with ARM_USBH_EndpointReset
 *    Replaced function ARM_USBH_URB_Submit with ARM_USBH_EndpointTransfer
 *    Replaced function ARM_USBH_URB_Abort with ARM_USBH_EndpointTransferAbort
 *    Added function ARM_USBH_EndpointTransferGetResult
 *    Added function ARM_USBH_GetFrameNumber
 *    Changed prefix ARM_DRV -> ARM_DRIVER
 *  Version 1.20
 *    Added API for OHCI/EHCI Host Controller Interface (HCI)
 *  Version 1.10
 *    Namespace prefix ARM_ added
 *  Version 1.00
 *    Initial release
 */

#ifndef __DRIVER_USBH_H
#define __DRIVER_USBH_H

#include "Driver_USB.h"

#define ARM_USBH_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2,01)  /* API version */


/**
\brief USB Host Port State
*/
typedef struct _ARM_USBH_PORT_STATE {
  uint32_t connected   : 1;             ///< USB Host Port connected flag
  uint32_t overcurrent : 1;             ///< USB Host Port overcurrent flag
  uint32_t speed       : 2;             ///< USB Host Port speed setting (ARM_USB_SPEED_xxx)
} ARM_USBH_PORT_STATE;

/**
\brief USB Host Pipe Handle
*/
typedef uint32_t ARM_USBH_PIPE_HANDLE;
#define ARM_USBH_EP_HANDLE ARM_USBH_PIPE_HANDLE  /* Legacy name */


/****** USB Host Packet Information *****/
#define ARM_USBH_PACKET_TOKEN_Pos         0
#define ARM_USBH_PACKET_TOKEN_Msk        (0x0FUL << ARM_USBH_PACKET_TOKEN_Pos)
#define ARM_USBH_PACKET_SETUP            (0x01UL << ARM_USBH_PACKET_TOKEN_Pos)  ///< SETUP Packet
#define ARM_USBH_PACKET_OUT              (0x02UL << ARM_USBH_PACKET_TOKEN_Pos)  ///< OUT Packet
#define ARM_USBH_PACKET_IN               (0x03UL << ARM_USBH_PACKET_TOKEN_Pos)  ///< IN Packet
#define ARM_USBH_PACKET_PING             (0x04UL << ARM_USBH_PACKET_TOKEN_Pos)  ///< PING Packet

#define ARM_USBH_PACKET_DATA_Pos          4
#define ARM_USBH_PACKET_DATA_Msk         (0x0FUL << ARM_USBH_PACKET_DATA_Pos)
#define ARM_USBH_PACKET_DATA0            (0x01UL << ARM_USBH_PACKET_DATA_Pos)   ///< DATA0 PID
#define ARM_USBH_PACKET_DATA1            (0x02UL << ARM_USBH_PACKET_DATA_Pos)   ///< DATA1 PID

#define ARM_USBH_PACKET_SPLIT_Pos         8
#define ARM_USBH_PACKET_SPLIT_Msk        (0x0FUL << ARM_USBH_PACKET_SPLIT_Pos)
#define ARM_USBH_PACKET_SSPLIT           (0x08UL << ARM_USBH_PACKET_SPLIT_Pos)  ///< SSPLIT Packet
#define ARM_USBH_PACKET_SSPLIT_S         (0x09UL << ARM_USBH_PACKET_SPLIT_Pos)  ///< SSPLIT Packet: Data Start
#define ARM_USBH_PACKET_SSPLIT_E         (0x0AUL << ARM_USBH_PACKET_SPLIT_Pos)  ///< SSPLIT Packet: Data End
#define ARM_USBH_PACKET_SSPLIT_S_E       (0x0BUL << ARM_USBH_PACKET_SPLIT_Pos)  ///< SSPLIT Packet: Data All
#define ARM_USBH_PACKET_CSPLIT           (0x0CUL << ARM_USBH_PACKET_SPLIT_Pos)  ///< CSPLIT Packet

#define ARM_USBH_PACKET_PRE              (1UL << 12)                            ///< PRE Token


/****** USB Host Port Event *****/
#define ARM_USBH_EVENT_CONNECT           (1UL << 0)     ///< USB Device Connected to Port
#define ARM_USBH_EVENT_DISCONNECT        (1UL << 1)     ///< USB Device Disconnected from Port
#define ARM_USBH_EVENT_OVERCURRENT       (1UL << 2)     ///< USB Device caused Overcurrent
#define ARM_USBH_EVENT_RESET             (1UL << 3)     ///< USB Reset completed
#define ARM_USBH_EVENT_SUSPEND           (1UL << 4)     ///< USB Suspend occurred
#define ARM_USBH_EVENT_RESUME            (1UL << 5)     ///< USB Resume occurred
#define ARM_USBH_EVENT_REMOTE_WAKEUP     (1UL << 6)     ///< USB Device activated Remote Wakeup

/****** USB Host Pipe Event *****/
#define ARM_USBH_EVENT_TRANSFER_COMPLETE (1UL << 0)     ///< Transfer completed
#define ARM_USBH_EVENT_HANDSHAKE_NAK     (1UL << 1)     ///< NAK Handshake received
#define ARM_USBH_EVENT_HANDSHAKE_NYET    (1UL << 2)     ///< NYET Handshake received
#define ARM_USBH_EVENT_HANDSHAKE_MDATA   (1UL << 3)     ///< MDATA Handshake received
#define ARM_USBH_EVENT_HANDSHAKE_STALL   (1UL << 4)     ///< STALL Handshake received
#define ARM_USBH_EVENT_HANDSHAKE_ERR     (1UL << 5)     ///< ERR Handshake received
#define ARM_USBH_EVENT_BUS_ERROR         (1UL << 6)     ///< Bus Error detected


#ifndef __DOXYGEN_MW__                  // exclude from middleware documentation

// Function documentation
/**
  \fn          ARM_DRIVER_VERSION ARM_USBH_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION
*/
/**
  \fn          ARM_USBH_CAPABILITIES ARM_USBH_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref ARM_USBH_CAPABILITIES
*/
/**
  \fn          int32_t ARM_USBH_Initialize (ARM_USBH_SignalPortEvent_t cb_port_event,
                                            ARM_USBH_SignalPipeEvent_t cb_pipe_event)
  \brief       Initialize USB Host Interface.
  \param[in]   cb_port_event  Pointer to \ref ARM_USBH_SignalPortEvent
  \param[in]   cb_pipe_event  Pointer to \ref ARM_USBH_SignalPipeEvent
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBH_Uninitialize (void)
  \brief       De-initialize USB Host Interface.
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBH_PowerControl (ARM_POWER_STATE state)
  \brief       Control USB Host Interface Power.
  \param[in]   state  Power state
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBH_PortVbusOnOff (uint8_t port, bool vbus)
  \brief       Root HUB Port VBUS on/off.
  \param[in]   port  Root HUB Port Number
  \param[in]   vbus
                - \b false VBUS off
                - \b true  VBUS on
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBH_PortReset (uint8_t port)
  \brief       Do Root HUB Port Reset.
  \param[in]   port  Root HUB Port Number
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBH_PortSuspend (uint8_t port)
  \brief       Suspend Root HUB Port (stop generating SOFs).
  \param[in]   port  Root HUB Port Number
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBH_PortResume (uint8_t port)
  \brief       Resume Root HUB Port (start generating SOFs).
  \param[in]   port  Root HUB Port Number
  \return      \ref execution_status
*/
/**
  \fn          ARM_USBH_PORT_STATE ARM_USBH_PortGetState (uint8_t port)
  \brief       Get current Root HUB Port State.
  \param[in]   port  Root HUB Port Number
  \return      Port State \ref ARM_USBH_PORT_STATE
*/
/**
  \fn          ARM_USBH_PIPE_HANDLE ARM_USBH_PipeCreate (uint8_t  dev_addr,
                                                         uint8_t  dev_speed,
                                                         uint8_t  hub_addr,
                                                         uint8_t  hub_port,
                                                         uint8_t  ep_addr,
                                                         uint8_t  ep_type,
                                                         uint16_t ep_max_packet_size,
                                                         uint8_t  ep_interval)
  \brief       Create Pipe in System.
  \param[in]   dev_addr   Device Address
  \param[in]   dev_speed  Device Speed
  \param[in]   hub_addr   Hub Address
  \param[in]   hub_port   Hub Port
  \param[in]   ep_addr    Endpoint Address
                - ep_addr.0..3: Address
                - ep_addr.7:    Direction
  \param[in]   ep_type    Endpoint Type (ARM_USB_ENDPOINT_xxx)
  \param[in]   ep_max_packet_size Endpoint Maximum Packet Size
  \param[in]   ep_interval        Endpoint Polling Interval
  \return      Pipe Handle \ref ARM_USBH_PIPE_HANDLE
*/
/**
  \fn          int32_t ARM_USBH_PipeModify (ARM_USBH_PIPE_HANDLE pipe_hndl,
                                            uint8_t              dev_addr,
                                            uint8_t              dev_speed,
                                            uint8_t              hub_addr,
                                            uint8_t              hub_port,
                                            uint16_t             ep_max_packet_size)
  \brief       Modify Pipe in System.
  \param[in]   pipe_hndl  Pipe Handle
  \param[in]   dev_addr   Device Address
  \param[in]   dev_speed  Device Speed
  \param[in]   hub_addr   Hub Address
  \param[in]   hub_port   Hub Port
  \param[in]   ep_max_packet_size Endpoint Maximum Packet Size
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBH_PipeDelete (ARM_USBH_PIPE_HANDLE pipe_hndl)
  \brief       Delete Pipe from System.
  \param[in]   pipe_hndl  Pipe Handle
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBH_PipeReset (ARM_USBH_PIPE_HANDLE pipe_hndl)
  \brief       Reset Pipe.
  \param[in]   pipe_hndl  Pipe Handle
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBH_PipeTransfer (ARM_USBH_PIPE_HANDLE pipe_hndl,
                                              uint32_t             packet,
                                              uint8_t             *data,
                                              uint32_t             num)
  \brief       Transfer packets through USB Pipe.
  \param[in]   pipe_hndl  Pipe Handle
  \param[in]   packet     Packet information
  \param[in]   data       Pointer to buffer with data to send or for data to receive
  \param[in]   num        Number of data bytes to transfer
  \return      \ref execution_status
*/
/**
  \fn          uint32_t ARM_USBH_PipeTransferGetResult (ARM_USBH_PIPE_HANDLE pipe_hndl)
  \brief       Get result of USB Pipe transfer.
  \param[in]   pipe_hndl  Pipe Handle
  \return      number of successfully transferred data bytes
*/
/**
  \fn          int32_t ARM_USBH_PipeTransferAbort (ARM_USBH_PIPE_HANDLE pipe_hndl)
  \brief       Abort current USB Pipe transfer.
  \param[in]   pipe_hndl  Pipe Handle
  \return      \ref execution_status
*/
/**
  \fn          uint16_t ARM_USBH_GetFrameNumber (void)
  \brief       Get current USB Frame Number.
  \return      Frame Number
*/

/**
  \fn          void ARM_USBH_SignalPortEvent (uint8_t port, uint32_t event)
  \brief       Signal Root HUB Port Event.
  \param[in]   port  Root HUB Port Number
  \param[in]   event \ref USBH_port_events
  \return      none
*/
/**
  \fn          void ARM_USBH_SignalPipeEvent (ARM_USBH_PIPE_HANDLE pipe_hndl, uint32_t event)
  \brief       Signal Pipe Event.
  \param[in]   pipe_hndl  Pipe Handle
  \param[in]   event  \ref USBH_pipe_events
  \return      none
*/

typedef void (*ARM_USBH_SignalPortEvent_t) (uint8_t port, uint32_t event);                    ///< Pointer to \ref ARM_USBH_SignalPortEvent : Signal Root HUB Port Event.
typedef void (*ARM_USBH_SignalPipeEvent_t) (ARM_USBH_PIPE_HANDLE pipe_hndl, uint32_t event);  ///< Pointer to \ref ARM_USBH_SignalPipeEvent : Signal Pipe Event.
#define ARM_USBH_SignalEndpointEvent_t ARM_USBH_SignalPipeEvent_t  /* Legacy name */


/**
\brief USB Host Driver Capabilities.
*/
typedef struct _ARM_USBH_CAPABILITIES {
  uint32_t port_mask          : 15;     ///< Root HUB available Ports Mask
  uint32_t auto_split         :  1;     ///< Automatic SPLIT packet handling
  uint32_t event_connect      :  1;     ///< Signal Connect event
  uint32_t event_disconnect   :  1;     ///< Signal Disconnect event
  uint32_t event_overcurrent  :  1;     ///< Signal Overcurrent event
} ARM_USBH_CAPABILITIES;


/**
\brief Access structure of USB Host Driver.
*/
typedef struct _ARM_DRIVER_USBH {
  ARM_DRIVER_VERSION    (*GetVersion)            (void);                                     ///< Pointer to \ref ARM_USBH_GetVersion : Get driver version.
  ARM_USBH_CAPABILITIES (*GetCapabilities)       (void);                                     ///< Pointer to \ref ARM_USBH_GetCapabilities : Get driver capabilities.
  int32_t               (*Initialize)            (ARM_USBH_SignalPortEvent_t cb_port_event,            
                                                  ARM_USBH_SignalPipeEvent_t cb_pipe_event); ///< Pointer to \ref ARM_USBH_Initialize : Initialize USB Host Interface.
  int32_t               (*Uninitialize)          (void);                                     ///< Pointer to \ref ARM_USBH_Uninitialize : De-initialize USB Host Interface.
  int32_t               (*PowerControl)          (ARM_POWER_STATE state);                    ///< Pointer to \ref ARM_USBH_PowerControl : Control USB Host Interface Power.
  int32_t               (*PortVbusOnOff)         (uint8_t port, bool vbus);                  ///< Pointer to \ref ARM_USBH_PortVbusOnOff : Root HUB Port VBUS on/off.
  int32_t               (*PortReset)             (uint8_t port);                             ///< Pointer to \ref ARM_USBH_PortReset : Do Root HUB Port Reset.
  int32_t               (*PortSuspend)           (uint8_t port);                             ///< Pointer to \ref ARM_USBH_PortSuspend : Suspend Root HUB Port (stop generating SOFs).
  int32_t               (*PortResume)            (uint8_t port);                             ///< Pointer to \ref ARM_USBH_PortResume : Resume Root HUB Port (start generating SOFs).
  ARM_USBH_PORT_STATE   (*PortGetState)          (uint8_t port);                             ///< Pointer to \ref ARM_USBH_PortGetState : Get current Root HUB Port State.
  ARM_USBH_PIPE_HANDLE  (*PipeCreate)            (uint8_t dev_addr,
                                                  uint8_t dev_speed,
                                                  uint8_t hub_addr,
                                                  uint8_t hub_port,
                                                  uint8_t ep_addr,
                                                  uint8_t ep_type,
                                                  uint16_t ep_max_packet_size,
                                                  uint8_t ep_interval);                      ///< Pointer to \ref ARM_USBH_PipeCreate : Create Pipe in System.
  int32_t               (*PipeModify)            (ARM_USBH_PIPE_HANDLE pipe_hndl,
                                                  uint8_t dev_addr,
                                                  uint8_t dev_speed,
                                                  uint8_t hub_addr,
                                                  uint8_t hub_port,
                                                  uint16_t ep_max_packet_size);              ///< Pointer to \ref ARM_USBH_PipeModify : Modify Pipe in System.
  int32_t               (*PipeDelete)            (ARM_USBH_PIPE_HANDLE pipe_hndl);           ///< Pointer to \ref ARM_USBH_PipeDelete : Delete Pipe from System.
  int32_t               (*PipeReset)             (ARM_USBH_PIPE_HANDLE pipe_hndl);           ///< Pointer to \ref ARM_USBH_PipeReset : Reset Pipe.
  int32_t               (*PipeTransfer)          (ARM_USBH_PIPE_HANDLE pipe_hndl, 
                                                  uint32_t packet,
                                                  uint8_t *data,
                                                  uint32_t num);                             ///< Pointer to \ref ARM_USBH_PipeTransfer : Transfer packets through USB Pipe.
  uint32_t              (*PipeTransferGetResult) (ARM_USBH_PIPE_HANDLE pipe_hndl);           ///< Pointer to \ref ARM_USBH_PipeTransferGetResult : Get result of USB Pipe transfer.
  int32_t               (*PipeTransferAbort)     (ARM_USBH_PIPE_HANDLE pipe_hndl);           ///< Pointer to \ref ARM_USBH_PipeTransferAbort : Abort current USB Pipe transfer.
  uint16_t              (*GetFrameNumber)        (void);                                     ///< Pointer to \ref ARM_USBH_GetFrameNumber : Get current USB Frame Number.                    
} const ARM_DRIVER_USBH;


// HCI (OHCI/EHCI)

// Function documentation
/**
  \fn          ARM_DRIVER_VERSION ARM_USBH_HCI_GetVersion (void)
  \brief       Get USB Host HCI (OHCI/EHCI) driver version.
  \return      \ref ARM_DRIVER_VERSION
*/
/**
  \fn          ARM_USBH_HCI_CAPABILITIES ARM_USBH_HCI_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref ARM_USBH_HCI_CAPABILITIES
*/
/**
  \fn          int32_t ARM_USBH_HCI_Initialize (ARM_USBH_HCI_Interrupt_t *cb_interrupt)
  \brief       Initialize USB Host HCI (OHCI/EHCI) Interface.
  \param[in]   cb_interrupt Pointer to Interrupt Handler Routine
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBH_HCI_Uninitialize (void)
  \brief       De-initialize USB Host HCI (OHCI/EHCI) Interface.
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBH_HCI_PowerControl (ARM_POWER_STATE state)
  \brief       Control USB Host HCI (OHCI/EHCI) Interface Power.
  \param[in]   state Power state
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_USBH_HCI_PortVbusOnOff (uint8_t port, bool vbus)
  \brief       USB Host HCI (OHCI/EHCI) Root HUB Port VBUS on/off.
  \param[in]   port  Root HUB Port Number
  \param[in]   vbus
                - \b false VBUS off
                - \b true  VBUS on
  \return      \ref execution_status
*/

/**
  \fn          void ARM_USBH_HCI_Interrupt (void)
  \brief       USB Host HCI Interrupt Handler.
  \return      none
*/

typedef void (*ARM_USBH_HCI_Interrupt_t) (void);  ///< Pointer to Interrupt Handler Routine.


/**
\brief USB Host HCI (OHCI/EHCI) Driver Capabilities.
*/
typedef struct _ARM_USBH_HCI_CAPABILITIES {
  uint32_t port_mask : 15;              ///< Root HUB available Ports Mask
} ARM_USBH_HCI_CAPABILITIES;


/**
  \brief Access structure of USB Host HCI (OHCI/EHCI) Driver.
*/
typedef struct _ARM_DRIVER_USBH_HCI {
  ARM_DRIVER_VERSION        (*GetVersion)      (void);                                  ///< Pointer to \ref ARM_USBH_HCI_GetVersion : Get USB Host HCI (OHCI/EHCI) driver version.
  ARM_USBH_HCI_CAPABILITIES (*GetCapabilities) (void);                                  ///< Pointer to \ref ARM_USBH_HCI_GetCapabilities : Get driver capabilities.
  int32_t                   (*Initialize)      (ARM_USBH_HCI_Interrupt_t cb_interrupt); ///< Pointer to \ref ARM_USBH_HCI_Initialize : Initialize USB Host HCI (OHCI/EHCI) Interface.
  int32_t                   (*Uninitialize)    (void);                                  ///< Pointer to \ref ARM_USBH_HCI_Uninitialize : De-initialize USB Host HCI (OHCI/EHCI) Interface.
  int32_t                   (*PowerControl)    (ARM_POWER_STATE state);                 ///< Pointer to \ref ARM_USBH_HCI_PowerControl : Control USB Host HCI (OHCI/EHCI) Interface Power.
  int32_t                   (*PortVbusOnOff)   (uint8_t port, bool vbus);               ///< Pointer to \ref ARM_USBH_HCI_PortVbusOnOff : USB Host HCI (OHCI/EHCI) Root HUB Port VBUS on/off.
} const ARM_DRIVER_USBH_HCI;

#endif /* __DOXYGEN_MW__ */

#endif /* __DRIVER_USBH_H */
