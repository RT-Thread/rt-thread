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


#ifndef _CSI_NET_H_
#define _CSI_NET_H_

#ifdef __cplusplus
extern "C" {
#endif

#define CSI_ETH_VERSION_MAJOR_MINOR(major,minor) (((major) << 8) | (minor))

/**
\brief Driver Version
*/
typedef struct csi_driver_version {
  uint16_t api;                         ///< API version
  uint16_t drv;                         ///< Driver version
} csi_drv_version_t;

/* General return codes */
#define CSI_ETH_OK                 0 ///< Operation succeeded
#define CSI_ETH_ERROR             CSI_DRV_ERRNO_ETH_BASE+1 ///< Unspecified error
#define CSI_ETH_ERROR_BUSY        CSI_DRV_ERRNO_ETH_BASE+2 ///< Driver is busy
#define CSI_ETH_ERROR_TIMEOUT     CSI_DRV_ERRNO_ETH_BASE+3 ///< Timeout occurred
#define CSI_ETH_ERROR_UNSUPPORTED CSI_DRV_ERRNO_ETH_BASE+4 ///< Operation not supported
#define CSI_ETH_ERROR_PARAMETER   CSI_DRV_ERRNO_ETH_BASE+5 ///< Parameter error
#define CSI_ETH_ERROR_SPECIFIC    CSI_DRV_ERRNO_ETH_BASE+6 ///< Start of driver specific errors

/**
\brief General power states
*/
typedef enum eth_power_state {
  CSI_ETH_POWER_OFF,                        ///< Power off: no operation possible
  CSI_ETH_POWER_LOW,                        ///< Low Power mode: retain state, detect and signal wake-up events
  CSI_ETH_POWER_FULL                        ///< Power on: full operation at maximum performance
} eth_power_state_t;

/**
\brief Ethernet Media Interface type
*/
#define CSI_ETH_INTERFACE_MII           (0)     ///< Media Independent Interface (MII)
#define CSI_ETH_INTERFACE_RMII          (1)     ///< Reduced Media Independent Interface (RMII)
#define CSI_ETH_INTERFACE_SMII          (2)     ///< Serial Media Independent Interface (SMII)

/**
\brief Ethernet link speed
*/
#define CSI_ETH_SPEED_10M               (0)     ///< 10 Mbps link speed
#define CSI_ETH_SPEED_100M              (1)     ///< 100 Mbps link speed
#define CSI_ETH_SPEED_1G                (2)     ///< 1 Gpbs link speed

/**
\brief Ethernet duplex mode
*/
#define CSI_ETH_DUPLEX_HALF             (0)     ///< Half duplex link
#define CSI_ETH_DUPLEX_FULL             (1)     ///< Full duplex link

/**
\brief Ethernet link state
*/
typedef enum eth_link_state {
  ETH_LINK_DOWN,                    ///< Link is down
  ETH_LINK_UP                       ///< Link is up
} eth_link_state_t;

/**
\brief Ethernet link information
*/
typedef volatile struct eth_link_info {
  uint32_t speed              : 2;                ///< Link speed: 0= 10 MBit, 1= 100 MBit, 2= 1 GBit
  uint32_t duplex             : 1;                ///< Duplex mode: 0= Half, 1= Full
  uint32_t Autonegotiation    : 1;                ///< Set the interface to Auto Negotiation mode of transmission parameters
  uint32_t Loopback           : 1;                ///< Set the interface into a Loop-back test mode
  uint32_t Isolation          : 1;                ///< Set to indicate electrical isolation of PHY interface from MII/RMII interface
  uint32_t reserved           : 26;
} eth_link_info_t;

/**
\brief Ethernet MAC Address
*/
typedef struct eth_mac_addr {
  uint8_t b[6];                         ///< MAC Address (6 bytes), MSB first
} eth_mac_addr_t;

#ifdef __cplusplus
}
#endif

#endif /* CSI_NET_H_ */

