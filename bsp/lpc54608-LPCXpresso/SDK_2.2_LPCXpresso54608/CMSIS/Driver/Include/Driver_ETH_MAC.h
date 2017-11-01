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
 * $Date:        30. May 2014
 * $Revision:    V2.01
 *
 * Project:      Ethernet MAC (Media Access Control) Driver definitions
 * -------------------------------------------------------------------------- */

/* History:
 *  Version 2.01
 *    Added ARM_ETH_MAC_SLEEP Control
 *  Version 2.00
 *    Changed MAC Address handling:
 *      moved from ARM_ETH_MAC_Initialize
 *      to new functions ARM_ETH_MAC_GetMacAddress and ARM_ETH_MAC_SetMacAddress
 *    Replaced ARM_ETH_MAC_SetMulticastAddr function with ARM_ETH_MAC_SetAddressFilter
 *    Extended ARM_ETH_MAC_SendFrame function with flags
 *    Added ARM_ETH_MAC_Control function:
 *      more control options (Broadcast, Multicast, Checksum offload, VLAN, ...)
 *      replaces ARM_ETH_MAC_SetMode
 *      replaces ARM_ETH_MAC_EnableTx, ARM_ETH_MAC_EnableRx
 *    Added optional event on transmitted frame
 *    Added support for PTP (Precision Time Protocol) through new functions:
 *       ARM_ETH_MAC_ControlTimer
 *       ARM_ETH_MAC_GetRxFrameTime
 *       ARM_ETH_MAC_GetTxFrameTime
 *    Changed prefix ARM_DRV -> ARM_DRIVER
 *    Changed return values of some functions to int32_t
 *  Version 1.10
 *    Name space prefix ARM_ added
 *  Version 1.01
 *    Renamed capabilities items for checksum offload
 *  Version 1.00
 *    Initial release
 */

#ifndef __DRIVER_ETH_MAC_H
#define __DRIVER_ETH_MAC_H

#include "Driver_ETH.h"

#define ARM_ETH_MAC_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2,01)  /* API version */


#define _ARM_Driver_ETH_MAC_(n)      Driver_ETH_MAC##n
#define  ARM_Driver_ETH_MAC_(n) _ARM_Driver_ETH_MAC_(n)


/****** Ethernet MAC Control Codes *****/

#define ARM_ETH_MAC_CONFIGURE           (0x01)      ///< Configure MAC; arg = configuration
#define ARM_ETH_MAC_CONTROL_TX          (0x02)      ///< Transmitter; arg: 0=disabled (default), 1=enabled
#define ARM_ETH_MAC_CONTROL_RX          (0x03)      ///< Receiver; arg: 0=disabled (default), 1=enabled
#define ARM_ETH_MAC_FLUSH               (0x04)      ///< Flush buffer; arg = ARM_ETH_MAC_FLUSH_...
#define ARM_ETH_MAC_SLEEP               (0x05)      ///< Sleep mode; arg: 1=enter and wait for Magic packet, 0=exit
#define ARM_ETH_MAC_VLAN_FILTER         (0x06)      ///< VLAN Filter for received frames; arg15..0: VLAN Tag; arg16: optional ARM_ETH_MAC_VLAN_FILTER_ID_ONLY; 0=disabled (default)

/*----- Ethernet MAC Configuration -----*/
#define ARM_ETH_MAC_SPEED_Pos            0
#define ARM_ETH_MAC_SPEED_Msk           (3UL                 << ARM_ETH_MAC_SPEED_Pos)
#define ARM_ETH_MAC_SPEED_10M           (ARM_ETH_SPEED_10M   << ARM_ETH_MAC_SPEED_Pos)  ///< 10 Mbps link speed
#define ARM_ETH_MAC_SPEED_100M          (ARM_ETH_SPEED_100M  << ARM_ETH_MAC_SPEED_Pos)  ///< 100 Mbps link speed
#define ARM_ETH_MAC_SPEED_1G            (ARM_ETH_SPEED_1G    << ARM_ETH_MAC_SPEED_Pos)  ///< 1 Gpbs link speed
#define ARM_ETH_MAC_DUPLEX_Pos           2
#define ARM_ETH_MAC_DUPLEX_Msk          (1UL                 << ARM_ETH_MAC_DUPLEX_Pos)
#define ARM_ETH_MAC_DUPLEX_HALF         (ARM_ETH_DUPLEX_HALF << ARM_ETH_MAC_DUPLEX_Pos) ///< Half duplex link
#define ARM_ETH_MAC_DUPLEX_FULL         (ARM_ETH_DUPLEX_FULL << ARM_ETH_MAC_DUPLEX_Pos) ///< Full duplex link
#define ARM_ETH_MAC_LOOPBACK            (1UL << 4)  ///< Loop-back test mode
#define ARM_ETH_MAC_CHECKSUM_OFFLOAD_RX (1UL << 5)  ///< Receiver Checksum offload
#define ARM_ETH_MAC_CHECKSUM_OFFLOAD_TX (1UL << 6)  ///< Transmitter Checksum offload
#define ARM_ETH_MAC_ADDRESS_BROADCAST   (1UL << 7)  ///< Accept frames with Broadcast address
#define ARM_ETH_MAC_ADDRESS_MULTICAST   (1UL << 8)  ///< Accept frames with any Multicast address
#define ARM_ETH_MAC_ADDRESS_ALL         (1UL << 9)  ///< Accept frames with any address (Promiscuous Mode)

/*----- Ethernet MAC Flush Flags -----*/
#define ARM_ETH_MAC_FLUSH_RX            (1UL << 0)  ///< Flush Receive buffer
#define ARM_ETH_MAC_FLUSH_TX            (1UL << 1)  ///< Flush Transmit buffer

/*----- Ethernet MAC VLAN Filter Flag -----*/
#define ARM_ETH_MAC_VLAN_FILTER_ID_ONLY (1UL << 16) ///< Compare only the VLAN Identifier (12-bit)


/****** Ethernet MAC Frame Transmit Flags *****/
#define ARM_ETH_MAC_TX_FRAME_FRAGMENT   (1UL << 0)  ///< Indicate frame fragment
#define ARM_ETH_MAC_TX_FRAME_EVENT      (1UL << 1)  ///< Generate event when frame is transmitted
#define ARM_ETH_MAC_TX_FRAME_TIMESTAMP  (1UL << 2)  ///< Capture frame time stamp


/****** Ethernet MAC Timer Control Codes *****/
#define ARM_ETH_MAC_TIMER_GET_TIME      (0x01)      ///< Get current time
#define ARM_ETH_MAC_TIMER_SET_TIME      (0x02)      ///< Set new time
#define ARM_ETH_MAC_TIMER_INC_TIME      (0x03)      ///< Increment current time
#define ARM_ETH_MAC_TIMER_DEC_TIME      (0x04)      ///< Decrement current time
#define ARM_ETH_MAC_TIMER_SET_ALARM     (0x05)      ///< Set alarm time
#define ARM_ETH_MAC_TIMER_ADJUST_CLOCK  (0x06)      ///< Adjust clock frequency; time->ns: correction factor * 2^31


/**
\brief Ethernet MAC Time
*/
typedef struct _ARM_ETH_MAC_TIME {
  uint32_t ns;                          ///< Nano seconds
  uint32_t sec;                         ///< Seconds
} ARM_ETH_MAC_TIME;


/****** Ethernet MAC Event *****/
#define ARM_ETH_MAC_EVENT_RX_FRAME      (1UL << 0)  ///< Frame Received
#define ARM_ETH_MAC_EVENT_TX_FRAME      (1UL << 1)  ///< Frame Transmitted
#define ARM_ETH_MAC_EVENT_WAKEUP        (1UL << 2)  ///< Wake-up (on Magic Packet)
#define ARM_ETH_MAC_EVENT_TIMER_ALARM   (1UL << 3)  ///< Timer Alarm


// Function documentation
/**
  \fn          ARM_DRIVER_VERSION ARM_ETH_MAC_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION
*/
/**
  \fn          ARM_ETH_MAC_CAPABILITIES ARM_ETH_MAC_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref ARM_ETH_MAC_CAPABILITIES
*/
/**
  \fn          int32_t ARM_ETH_MAC_Initialize (ARM_ETH_MAC_SignalEvent_t cb_event)
  \brief       Initialize Ethernet MAC Device.
  \param[in]   cb_event  Pointer to \ref ARM_ETH_MAC_SignalEvent
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_MAC_Uninitialize (void)
  \brief       De-initialize Ethernet MAC Device.
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_MAC_PowerControl (ARM_POWER_STATE state)
  \brief       Control Ethernet MAC Device Power.
  \param[in]   state  Power state
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_MAC_GetMacAddress (ARM_ETH_MAC_ADDR *ptr_addr)
  \brief       Get Ethernet MAC Address.
  \param[in]   ptr_addr  Pointer to address
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_MAC_SetMacAddress (const ARM_ETH_MAC_ADDR *ptr_addr)
  \brief       Set Ethernet MAC Address.
  \param[in]   ptr_addr  Pointer to address
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_MAC_SetAddressFilter (const ARM_ETH_MAC_ADDR *ptr_addr,
                                                           uint32_t          num_addr)
  \brief       Configure Address Filter.
  \param[in]   ptr_addr  Pointer to addresses
  \param[in]   num_addr  Number of addresses to configure
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_MAC_SendFrame (const uint8_t *frame, uint32_t len, uint32_t flags)
  \brief       Send Ethernet frame.
  \param[in]   frame  Pointer to frame buffer with data to send
  \param[in]   len    Frame buffer length in bytes
  \param[in]   flags  Frame transmit flags (see ARM_ETH_MAC_TX_FRAME_...)
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_MAC_ReadFrame (uint8_t *frame, uint32_t len)
  \brief       Read data of received Ethernet frame.
  \param[in]   frame  Pointer to frame buffer for data to read into
  \param[in]   len    Frame buffer length in bytes
  \return      number of data bytes read or execution status
                 - value >= 0: number of data bytes read
                 - value < 0: error occurred, value is execution status as defined with \ref execution_status 
*/
/**
  \fn          uint32_t ARM_ETH_MAC_GetRxFrameSize (void)
  \brief       Get size of received Ethernet frame.
  \return      number of bytes in received frame
*/
/**
  \fn          int32_t ARM_ETH_MAC_GetRxFrameTime (ARM_ETH_MAC_TIME *time)
  \brief       Get time of received Ethernet frame.
  \param[in]   time  Pointer to time structure for data to read into
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_MAC_GetTxFrameTime (ARM_ETH_MAC_TIME *time)
  \brief       Get time of transmitted Ethernet frame.
  \param[in]   time  Pointer to time structure for data to read into
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_MAC_Control (uint32_t control, uint32_t arg)
  \brief       Control Ethernet Interface.
  \param[in]   control  Operation
  \param[in]   arg      Argument of operation (optional)
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_MAC_ControlTimer (uint32_t control, ARM_ETH_MAC_TIME *time)
  \brief       Control Precision Timer.
  \param[in]   control  Operation
  \param[in]   time     Pointer to time structure
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_MAC_PHY_Read (uint8_t phy_addr, uint8_t reg_addr, uint16_t *data)
  \brief       Read Ethernet PHY Register through Management Interface.
  \param[in]   phy_addr  5-bit device address
  \param[in]   reg_addr  5-bit register address
  \param[out]  data      Pointer where the result is written to
  \return      \ref execution_status
*/
/**
  \fn          int32_t ARM_ETH_MAC_PHY_Write (uint8_t phy_addr, uint8_t reg_addr, uint16_t data)
  \brief       Write Ethernet PHY Register through Management Interface.
  \param[in]   phy_addr  5-bit device address
  \param[in]   reg_addr  5-bit register address
  \param[in]   data      16-bit data to write
  \return      \ref execution_status
*/

/**
  \fn          void ARM_ETH_MAC_SignalEvent (uint32_t event)
  \brief       Callback function that signals a Ethernet Event.
  \param[in]   event  event notification mask
  \return      none
*/

typedef void (*ARM_ETH_MAC_SignalEvent_t) (uint32_t event);  ///< Pointer to \ref ARM_ETH_MAC_SignalEvent : Signal Ethernet Event.


/**
\brief Ethernet MAC Capabilities
*/
typedef struct _ARM_ETH_MAC_CAPABILITIES {
  uint32_t checksum_offload_rx_ip4  : 1;        ///< 1 = IPv4 header checksum verified on receive
  uint32_t checksum_offload_rx_ip6  : 1;        ///< 1 = IPv6 checksum verification supported on receive
  uint32_t checksum_offload_rx_udp  : 1;        ///< 1 = UDP payload checksum verified on receive
  uint32_t checksum_offload_rx_tcp  : 1;        ///< 1 = TCP payload checksum verified on receive
  uint32_t checksum_offload_rx_icmp : 1;        ///< 1 = ICMP payload checksum verified on receive
  uint32_t checksum_offload_tx_ip4  : 1;        ///< 1 = IPv4 header checksum generated on transmit
  uint32_t checksum_offload_tx_ip6  : 1;        ///< 1 = IPv6 checksum generation supported on transmit
  uint32_t checksum_offload_tx_udp  : 1;        ///< 1 = UDP payload checksum generated on transmit
  uint32_t checksum_offload_tx_tcp  : 1;        ///< 1 = TCP payload checksum generated on transmit
  uint32_t checksum_offload_tx_icmp : 1;        ///< 1 = ICMP payload checksum generated on transmit
  uint32_t media_interface          : 2;        ///< Ethernet Media Interface type
  uint32_t mac_address              : 1;        ///< 1 = driver provides initial valid MAC address
  uint32_t event_rx_frame           : 1;        ///< 1 = callback event \ref ARM_ETH_MAC_EVENT_RX_FRAME generated
  uint32_t event_tx_frame           : 1;        ///< 1 = callback event \ref ARM_ETH_MAC_EVENT_TX_FRAME generated
  uint32_t event_wakeup             : 1;        ///< 1 = wakeup event \ref ARM_ETH_MAC_EVENT_WAKEUP generated
  uint32_t precision_timer          : 1;        ///< 1 = Precision Timer supported
} ARM_ETH_MAC_CAPABILITIES;


/**
\brief Access structure of the Ethernet MAC Driver
*/
typedef struct _ARM_DRIVER_ETH_MAC {
  ARM_DRIVER_VERSION       (*GetVersion)      (void);                                                ///< Pointer to \ref ARM_ETH_MAC_GetVersion : Get driver version.
  ARM_ETH_MAC_CAPABILITIES (*GetCapabilities) (void);                                                ///< Pointer to \ref ARM_ETH_MAC_GetCapabilities : Get driver capabilities.
  int32_t                  (*Initialize)      (ARM_ETH_MAC_SignalEvent_t cb_event);                  ///< Pointer to \ref ARM_ETH_MAC_Initialize : Initialize Ethernet MAC Device.
  int32_t                  (*Uninitialize)    (void);                                                ///< Pointer to \ref ARM_ETH_MAC_Uninitialize : De-initialize Ethernet MAC Device.
  int32_t                  (*PowerControl)    (ARM_POWER_STATE state);                               ///< Pointer to \ref ARM_ETH_MAC_PowerControl : Control Ethernet MAC Device Power.
  int32_t                  (*GetMacAddress)   (      ARM_ETH_MAC_ADDR *ptr_addr);                    ///< Pointer to \ref ARM_ETH_MAC_GetMacAddress : Get Ethernet MAC Address.
  int32_t                  (*SetMacAddress)   (const ARM_ETH_MAC_ADDR *ptr_addr);                    ///< Pointer to \ref ARM_ETH_MAC_SetMacAddress : Set Ethernet MAC Address.
  int32_t                  (*SetAddressFilter)(const ARM_ETH_MAC_ADDR *ptr_addr, uint32_t num_addr); ///< Pointer to \ref ARM_ETH_MAC_SetAddressFilter : Configure Address Filter.
  int32_t                  (*SendFrame)       (const uint8_t *frame, uint32_t len, uint32_t flags);  ///< Pointer to \ref ARM_ETH_MAC_SendFrame : Send Ethernet frame.
  int32_t                  (*ReadFrame)       (      uint8_t *frame, uint32_t len);                  ///< Pointer to \ref ARM_ETH_MAC_ReadFrame : Read data of received Ethernet frame.
  uint32_t                 (*GetRxFrameSize)  (void);                                                ///< Pointer to \ref ARM_ETH_MAC_GetRxFrameSize : Get size of received Ethernet frame.
  int32_t                  (*GetRxFrameTime)  (ARM_ETH_MAC_TIME *time);                              ///< Pointer to \ref ARM_ETH_MAC_GetRxFrameTime : Get time of received Ethernet frame.
  int32_t                  (*GetTxFrameTime)  (ARM_ETH_MAC_TIME *time);                              ///< Pointer to \ref ARM_ETH_MAC_GetTxFrameTime : Get time of transmitted Ethernet frame.
  int32_t                  (*ControlTimer)    (uint32_t control, ARM_ETH_MAC_TIME *time);            ///< Pointer to \ref ARM_ETH_MAC_ControlTimer : Control Precision Timer.
  int32_t                  (*Control)         (uint32_t control, uint32_t arg);                      ///< Pointer to \ref ARM_ETH_MAC_Control : Control Ethernet Interface.
  int32_t                  (*PHY_Read)        (uint8_t phy_addr, uint8_t reg_addr, uint16_t *data);  ///< Pointer to \ref ARM_ETH_MAC_PHY_Read : Read Ethernet PHY Register through Management Interface.
  int32_t                  (*PHY_Write)       (uint8_t phy_addr, uint8_t reg_addr, uint16_t  data);  ///< Pointer to \ref ARM_ETH_MAC_PHY_Write : Write Ethernet PHY Register through Management Interface.
} const ARM_DRIVER_ETH_MAC;

#endif /* __DRIVER_ETH_MAC_H */
