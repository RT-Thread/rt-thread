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
 * $Revision:    V2.1
 *
 * Project:      Ethernet PHY and MAC Driver common definitions
 */

/* History:
 *  Version 2.1
 *    ARM_ETH_LINK_INFO made volatile
 *  Version 2.0
 *    Removed ARM_ETH_STATUS enumerator
 *    Removed ARM_ETH_MODE enumerator
 *  Version 1.10
 *    Namespace prefix ARM_ added
 *  Version 1.00
 *    Initial release
 */

#ifndef DRIVER_ETH_H_
#define DRIVER_ETH_H_

#include "Driver_Common.h"

/**
\brief Ethernet Media Interface type
*/
#define ARM_ETH_INTERFACE_MII           (0)     ///< Media Independent Interface (MII)
#define ARM_ETH_INTERFACE_RMII          (1)     ///< Reduced Media Independent Interface (RMII)
#define ARM_ETH_INTERFACE_SMII          (2)     ///< Serial Media Independent Interface (SMII)

/**
\brief Ethernet link speed
*/
#define ARM_ETH_SPEED_10M               (0)     ///< 10 Mbps link speed
#define ARM_ETH_SPEED_100M              (1)     ///< 100 Mbps link speed
#define ARM_ETH_SPEED_1G                (2)     ///< 1 Gpbs link speed

/**
\brief Ethernet duplex mode
*/
#define ARM_ETH_DUPLEX_HALF             (0)     ///< Half duplex link
#define ARM_ETH_DUPLEX_FULL             (1)     ///< Full duplex link

/**
\brief Ethernet link state
*/
typedef enum _ARM_ETH_LINK_STATE {
  ARM_ETH_LINK_DOWN,                    ///< Link is down
  ARM_ETH_LINK_UP                       ///< Link is up
} ARM_ETH_LINK_STATE;

/**
\brief Ethernet link information
*/
typedef volatile struct _ARM_ETH_LINK_INFO {
  uint32_t speed    : 2;                ///< Link speed: 0= 10 MBit, 1= 100 MBit, 2= 1 GBit
  uint32_t duplex   : 1;                ///< Duplex mode: 0= Half, 1= Full
  uint32_t reserved : 29;
} ARM_ETH_LINK_INFO;

/**
\brief Ethernet MAC Address
*/
typedef struct _ARM_ETH_MAC_ADDR {
  uint8_t b[6];                         ///< MAC Address (6 bytes), MSB first
} ARM_ETH_MAC_ADDR;

#endif /* DRIVER_ETH_H_ */
