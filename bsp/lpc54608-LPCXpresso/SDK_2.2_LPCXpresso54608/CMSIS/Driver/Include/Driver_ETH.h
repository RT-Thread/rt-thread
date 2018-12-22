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
 * $Date:        7. Mar 2014
 * $Revision:    V2.00
 *
 * Project:      Ethernet PHY and MAC Driver common definitions
 * -------------------------------------------------------------------------- */

/* History:
 *  Version 2.00
 *    Removed ARM_ETH_STATUS enumerator
 *    Removed ARM_ETH_MODE enumerator
 *  Version 1.10
 *    Namespace prefix ARM_ added
 *  Version 1.00
 *    Initial release
 */

#ifndef __DRIVER_ETH_H
#define __DRIVER_ETH_H

#include "Driver_Common.h"

/**
\brief Ethernet Media Interface type
*/
#define ARM_ETH_INTERFACE_MII           0       ///< Media Independent Interface (MII)
#define ARM_ETH_INTERFACE_RMII          1       ///< Reduced Media Independent Interface (RMII)
#define ARM_ETH_INTERFACE_SMII          2       ///< Serial Media Independent Interface (SMII)

/**
\brief Ethernet link speed
*/
#define ARM_ETH_SPEED_10M               0       ///< 10 Mbps link speed
#define ARM_ETH_SPEED_100M              1       ///< 100 Mbps link speed
#define ARM_ETH_SPEED_1G                2       ///< 1 Gpbs link speed

/**
\brief Ethernet duplex mode
*/
#define ARM_ETH_DUPLEX_HALF             0       ///< Half duplex link
#define ARM_ETH_DUPLEX_FULL             1       ///< Full duplex link

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
typedef struct _ARM_ETH_LINK_INFO {
  uint32_t speed  : 2;                  ///< Link speed: 0= 10 MBit, 1= 100 MBit, 2= 1 GBit
  uint32_t duplex : 1;                  ///< Duplex mode: 0= Half, 1= Full
} ARM_ETH_LINK_INFO;

/**
\brief Ethernet MAC Address
*/
typedef struct _ARM_ETH_MAC_ADDR {
  uint8_t b[6];                         ///< MAC Address (6 bytes), MSB first
} ARM_ETH_MAC_ADDR;

#endif /* __DRIVER_ETH_H */
