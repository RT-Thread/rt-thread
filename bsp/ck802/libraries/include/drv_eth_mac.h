/**
 * Copyright (C) 2016 CSI Project. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _CSI_ETH_H_
#define _CSI_ETH_H_

#include "drv_eth.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *eth_mac_handle_t;

#define MAX_FRAMELEN   1518        /*  (note: maximum ethernet frame length would be 1518) */

#define CSI_ETH_MAC_API_VERSION CSI_DRIVER_VERSION_MAJOR_MINOR(2,1)  /* API version */

#define _CSI_Driver_ETH_MAC_(n)      Driver_ETH_MAC##n
#define  CSI_Driver_ETH_MAC_(n) _CSI_Driver_ETH_MAC_(n)

/****** Ethernet MAC Control Codes *****/

#define CSI_ETH_MAC_CONFIGURE           (0x01)      ///< Configure MAC; arg = configuration
#define CSI_ETH_MAC_CONTROL_TX          (0x02)      ///< Transmitter; arg: 0=disabled (default), 1=enabled
#define CSI_ETH_MAC_CONTROL_RX          (0x03)      ///< Receiver; arg: 0=disabled (default), 1=enabled
#define CSI_ETH_MAC_FLUSH               (0x04)      ///< Flush buffer; arg = CSI_ETH_MAC_FLUSH_...
#define CSI_ETH_MAC_SLEEP               (0x05)      ///< Sleep mode; arg: 1=enter and wait for Magic packet, 0=exit
#define CSI_ETH_MAC_VLAN_FILTER         (0x06)      ///< VLAN Filter for received frames; arg15..0: VLAN Tag; arg16: optional CSI_ETH_MAC_VLAN_FILTER_ID_ONLY; 0=disabled (default)

/*----- Ethernet MAC Configuration -----*/
#define CSI_ETH_MAC_SPEED_Pos            0
#define CSI_ETH_MAC_SPEED_Msk           (3UL                 << CSI_ETH_MAC_SPEED_Pos)
#define CSI_ETH_MAC_SPEED_10M           (CSI_ETH_SPEED_10M   << CSI_ETH_MAC_SPEED_Pos)  ///< 10 Mbps link speed
#define CSI_ETH_MAC_SPEED_100M          (CSI_ETH_SPEED_100M  << CSI_ETH_MAC_SPEED_Pos)  ///< 100 Mbps link speed
#define CSI_ETH_MAC_SPEED_1G            (CSI_ETH_SPEED_1G    << CSI_ETH_MAC_SPEED_Pos)  ///< 1 Gpbs link speed
#define CSI_ETH_MAC_DUPLEX_Pos           2
#define CSI_ETH_MAC_DUPLEX_Msk          (1UL                 << CSI_ETH_MAC_DUPLEX_Pos)
#define CSI_ETH_MAC_DUPLEX_HALF         (CSI_ETH_DUPLEX_HALF << CSI_ETH_MAC_DUPLEX_Pos) ///< Half duplex link
#define CSI_ETH_MAC_DUPLEX_FULL         (CSI_ETH_DUPLEX_FULL << CSI_ETH_MAC_DUPLEX_Pos) ///< Full duplex link
#define CSI_ETH_MAC_LOOPBACK            (1UL << 4)  ///< Loop-back test mode
#define CSI_ETH_MAC_CHECKSUM_OFFLOAD_RX (1UL << 5)  ///< Receiver Checksum offload
#define CSI_ETH_MAC_CHECKSUM_OFFLOAD_TX (1UL << 6)  ///< Transmitter Checksum offload
#define CSI_ETH_MAC_ADDRESS_BROADCAST   (1UL << 7)  ///< Accept frames with Broadcast address
#define CSI_ETH_MAC_ADDRESS_MULTICAST   (1UL << 8)  ///< Accept frames with any Multicast address
#define CSI_ETH_MAC_ADDRESS_ALL         (1UL << 9)  ///< Accept frames with any address (Promiscuous Mode)

/*----- Ethernet MAC Flush Flags -----*/
#define CSI_ETH_MAC_FLUSH_RX            (1UL << 0)  ///< Flush Receive buffer
#define CSI_ETH_MAC_FLUSH_TX            (1UL << 1)  ///< Flush Transmit buffer

/*----- Ethernet MAC VLAN Filter Flag -----*/
#define CSI_ETH_MAC_VLAN_FILTER_ID_ONLY (1UL << 16) ///< Compare only the VLAN Identifier (12-bit)


/****** Ethernet MAC Frame Transmit Flags *****/
#define CSI_ETH_MAC_TX_FRAME_FRAGMENT   (1UL << 0)  ///< Indicate frame fragment
#define CSI_ETH_MAC_TX_FRAME_EVENT      (1UL << 1)  ///< Generate event when frame is transmitted
#define CSI_ETH_MAC_TX_FRAME_TIMESTAMP  (1UL << 2)  ///< Capture frame time stamp


/****** Ethernet MAC Timer Control Codes *****/
#define CSI_ETH_MAC_TIMER_GET_TIME      (0x01)      ///< Get current time
#define CSI_ETH_MAC_TIMER_SET_TIME      (0x02)      ///< Set new time
#define CSI_ETH_MAC_TIMER_INC_TIME      (0x03)      ///< Increment current time
#define CSI_ETH_MAC_TIMER_DEC_TIME      (0x04)      ///< Decrement current time
#define CSI_ETH_MAC_TIMER_SET_ALCSI     (0x05)      ///< Set alarm time
#define CSI_ETH_MAC_TIMER_ADJUST_CLOCK  (0x06)      ///< Adjust clock frequency; time->ns: correction factor * 2^31


/**
\brief Ethernet MAC Time
*/
typedef struct eth_mac_time {
  uint32_t ns;                          ///< Nano seconds
  uint32_t sec;                         ///< Seconds
} eth_mac_time_t;


/****** Ethernet MAC Event *****/
#define CSI_ETH_MAC_EVENT_RX_FRAME      (1UL << 0)  ///< Frame Received
#define CSI_ETH_MAC_EVENT_TX_FRAME      (1UL << 1)  ///< Frame Transmitted
#define CSI_ETH_MAC_EVENT_WAKEUP        (1UL << 2)  ///< Wake-up (on Magic Packet)
#define CSI_ETH_MAC_EVENT_TIMER_ALCSI   (1UL << 3)  ///< Timer Alarm
#define CSI_ETH_MAC_EVENT_LINK_CHANGE   (1UL << 4)  ///< Link state

typedef void (*eth_event_cb_t)(eth_mac_handle_t handle, uint32_t event);  ///< Pointer to \ref eth_event_cb_t : Signal Ethernet Event.

typedef enum
{
    FRAME_FILTER_RULE_POSITIVE_MATCHING  = 0,       /*!< Specifies that a filter should match a given pattern     */
    FRAME_FILTER_RULE_NEGATIVE_MATCHING  = 1,       /*!< Specifies that a filter should NOT match a given pattern */
} frame_filter_rule_t;

/**
\brief Ethernet MAC Capabilities
*/
typedef struct eth_capabilities {
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
  uint32_t event_rx_frame           : 1;        ///< 1 = callback event generated
  uint32_t event_tx_frame           : 1;        ///< 1 = callback event generated
  uint32_t event_wakeup             : 1;        ///< 1 = wakeup event generated
  uint32_t precision_timer          : 1;        ///< 1 = Precision Timer supported
  uint32_t reserved                 : 15;       ///< Reserved (must be zero)
} eth_capabilities_t;

#if 0
/**
\brief Ethernet Frame filter
*/
typedef struct eth_frame_filter {
  struct {
    uint32_t and_or                 : 1;        ///< 1 = AND: Packets will be rejected unless all enabled filters accept the packet; 0 = OR: Packets will be accepted unless all enabled filters reject the packet
    uint32_t unicast_en             : 1;        ///< 1 = Packets with a destination address matching the local MAC address will be accepted
    uint32_t multicast_en           : 1;        ///< 1 = Packets which have the Least Significant bit set in the destination address will be accepted
    uint32_t broadcast_en           : 1;        ///< 1 = Packets which have a destination address of FF-FF-FF-FF-FF-FF will be accepted
    uint32_t crc_en                 : 1;        ///< 1 = All packets with an invalid CRC will be discarded
    uint32_t patten_match_en        : 1;        ///< 1 = Packets which meet the Pattern Match criteria will be accepted
    uint32_t magic_packet_en        : 1;        ///< 1 = Magic Packets for the local MAC address will be accepted
    uint32_t hash_table_en          : 1;        ///< 1 = Packets which meet the Hash Table criteria will be accepted
  } sum;                                ///< summary
  uint32_t patten_match;                ///< patten match filter
  uint32_t magic_packet;                ///< patten match filter
  uint32_t hash_table;                  ///< hash table filter
} eth_frame_filter_t;
#else
/**
 * Structure describing a frame filter list item
 */
typedef struct
{
    uint32_t                       id;             /*!< Unique identifier for a packet filter item */
    frame_filter_rule_t            rule;           /*!< Filter matches are either POSITIVE or NEGATIVE matching */
    uint16_t                       offset;         /*!< Offset in bytes to start filtering (referenced to the start of the ethernet packet) */
    uint16_t                       mask_size;      /*!< Size of the mask in bytes */
    uint8_t*                       mask;           /*!< Pattern mask bytes to be ANDed with the pattern eg. "\xff00" (must be in network byte order) */
    uint8_t*                       pattern;        /*!< Pattern bytes used to filter eg. "\x0800"  (must be in network byte order) */
    bool                           enabled_status; /*!< When returned from mhd_get_packet_filters, indicates if the filter is enabled */
} eth_frame_filter_t;

struct eth_frame_filter_list
{
    struct eth_frame_filter_list*  next;
};
typedef struct eth_frame_filter_list eth_frame_filter_list_t;
#endif

typedef struct {
    eth_event_cb_t      cb_event;
    eth_capabilities_t  capabilities;
}eth_mac_priv_t;

/**
  \brief       Get driver version.
  \param[in]   handle  ethernet handle
  \return      ethernet version including chip version and driver version
*/
csi_drv_version_t csi_eth_mac_get_version(eth_mac_handle_t handle);

/**
  \brief       Get driver capabilities.
  \param[in]   handle  ethernet handle
  \return      ethernet capabilities
*/
eth_capabilities_t csi_eth_mac_get_capabilities(eth_mac_handle_t handle);

/**
  \brief       This function is used to initialize Ethernet device and related resource, an event callback is registered. It is called when the middleware component like TCPIP starts operation.
  \param[in]   cb  callback to handle ethernet event
  \return      return ethernet handle if success
 */
eth_mac_handle_t csi_eth_mac_initialize(eth_event_cb_t cb);

/**
  \brief       This function is used to de-initialize Ethernet device. It is called when the middleware component stops operation and releases the software resources used by the interface.
  \param[in]   handle  ethernet handle
  \return      error code
 */
int32_t csi_eth_mac_uninitialize(eth_mac_handle_t handle);

/**
  \brief       Control Ethernet MAC Device Power.
  \param[in]   handle  ethernet handle
  \param[in]   state  Power state
  \return      error code
*/
int32_t csi_eth_mac_power_control(eth_mac_handle_t handle, eth_power_state_t state);

/**
  \brief       Get Ethernet MAC Address.
  \param[in]   handle  ethernet handle
  \param[in]   mac  Pointer to address
  \return      error code
*/
int32_t csi_eth_mac_get_macaddr(eth_mac_handle_t handle, eth_mac_addr_t *mac);

/**
  \brief       Set Ethernet MAC Address.
  \param[in]   handle  ethernet handle
  \param[in]   mac  Pointer to address
  \return      error code
*/
int32_t csi_eth_mac_set_macaddr(eth_mac_handle_t handle, const eth_mac_addr_t *mac);

/**
  \brief       Configure Address Filter.
  \param[in]   handle  ethernet handle
  \param[in]   addr  Pointer to addresses
  \param[in]   num_addr  Number of addresses to configure
  \return      error code
*/
int32_t csi_eth_mac_set_addrfilter(eth_mac_handle_t handle, const eth_mac_addr_t *addr, uint32_t num_addr);

/**
  \brief       Send Ethernet frame.
  \param[in]   handle  ethernet handle
  \param[in]   frame  Pointer to frame buffer with data to send
  \param[in]   len    Frame buffer length in bytes
  \param[in]   flags  Frame transmit flags (see CSI_ETH_MAC_TX_FRAME_...)
  \return      error code
*/
int32_t csi_eth_mac_send_frame(eth_mac_handle_t handle, const uint8_t *frame, uint32_t len, uint32_t flags);

/**
  \brief       Read data of received Ethernet frame.
  \param[in]   handle  ethernet handle
  \param[in]   frame  Pointer to frame buffer for data to read into
  \param[in]   len    Frame buffer length in bytes
  \return      number of data bytes read or execution status
                 - value >= 0: number of data bytes read
                 - value < 0: error occurred, value is execution status as defined with execution_status
*/
int32_t csi_eth_mac_read_frame(eth_mac_handle_t handle, uint8_t *frame, uint32_t len);

/**
  \brief       Get size of received Ethernet frame.
  \param[in]   handle  ethernet handle
  \return      number of bytes in received frame
*/
int32_t csi_eth_mac_get_rx_framesize(eth_mac_handle_t handle);

/**
  \brief       Get time of received Ethernet frame.
  \param[in]   handle  ethernet handle
  \param[in]   time  Pointer to time structure for data to read into
  \return      error code
*/
int32_t csi_eth_mac_get_rx_frametime(eth_mac_handle_t handle, eth_mac_time_t *time);

/**
  \brief       Get time of transmitted Ethernet frame.
  \param[in]   handle  ethernet handle
  \param[in]   time  Pointer to time structure for data to read into
  \return      error code
*/
int32_t csi_eth_mac_get_tx_frametime(eth_mac_handle_t handle, eth_mac_time_t *time);

/**
  \brief       Control Ethernet Interface.
  \param[in]   handle  ethernet handle
  \param[in]   control  Operation
  \param[in]   arg      Argument of operation (optional)
  \return      error code
*/
int32_t csi_eth_mac_control(eth_mac_handle_t handle, uint32_t control, uint32_t arg);

/**
  \brief       Control Precision Timer.
  \param[in]   handle  ethernet handle
  \param[in]   control  Operation
  \param[in]   time     Pointer to time structure
  \return      error code
*/
int32_t csi_eth_mac_control_time(eth_mac_handle_t handle, uint32_t control, eth_mac_time_t *time);

/**
  \brief       Read Ethernet PHY Register through Management Interface.
  \param[in]   handle  ethernet handle
  \param[in]   phy_addr  5-bit device address
  \param[in]   reg_addr  5-bit register address
  \param[out]  data      Pointer where the result is written to
  \return      error code
*/
int32_t csi_eth_mac_phy_read(eth_mac_handle_t handle, uint8_t phy_addr, uint8_t reg_addr, uint16_t *data);

/**
  \brief       Write Ethernet PHY Register through Management Interface.
  \param[in]   handle  ethernet handle
  \param[in]   phy_addr  5-bit device address
  \param[in]   reg_addr  5-bit register address
  \param[in]   data      16-bit data to write
  \return      error code
*/
int32_t csi_eth_mac_phy_write(eth_mac_handle_t handle, uint8_t phy_addr, uint8_t reg_addr, uint16_t data);

/**
  \brief       Callback function that signals a Ethernet Event.
  \param[in]   handle  ethernet handle
  \param[in]   event  event notification mask
  \return      none
*/
void csi_eth_mac_signal_event(eth_mac_handle_t handle, uint32_t event);

/**
  \brief       Add Frame Filter Setting with Filter ID.
  \param[in]   handle  ethernet handle
  \param[in]   filter  Pointer to filter setting
  \return      error code
*/
int32_t csi_eth_mac_add_framefilter(eth_mac_handle_t handle, const eth_frame_filter_t *filter);

/**
  \brief       Remove Frame Filter Setting.
  \param[in]   handle  ethernet handle
  \param[in]   filter_id  Frame Filter ID
  \return      error code
*/
int32_t csi_eth_mac_remove_framefilter(eth_mac_handle_t handle, uint32_t filter_id);

/**
  \brief       Enable/Disable Specified Frame Filter ID.
  \param[in]   handle  ethernet handle
  \param[in]   filter_id  Frame Filter ID
  \param[in]   en  Enable or disable
  \return      error code
*/
int32_t csi_eth_mac_en_framefilter(eth_mac_handle_t handle, uint32_t filter_id, bool en);

/**
  \brief       Get frame filter table list.
  \param[in]   handle  ethernet handle
  \param[in]   list  frame filter table list
  \param[in]   count_out  the count of filter setting added
  \param[in]   max_count  max filter setting can be supported
  \return      error code
*/
int32_t csi_eth_mac_get_framefilter(eth_mac_handle_t handle, eth_frame_filter_list_t* list, uint32_t* count_out, uint32_t max_count);

#ifdef __cplusplus
}
#endif

#endif
