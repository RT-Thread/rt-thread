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
 * $Date:        20. May 2014
 * $Revision:    V2.00
 *
 * Project:      USB Driver common definitions
 * -------------------------------------------------------------------------- */

/* History:
 *  Version 2.00
 *  Version 1.10
 *    Namespace prefix ARM_ added
 *  Version 1.01
 *    Added PID Types
 *  Version 1.00
 *    Initial release
 */

#ifndef __DRIVER_USB_H
#define __DRIVER_USB_H

#include "Driver_Common.h"

/* USB Role */
#define ARM_USB_ROLE_NONE                0
#define ARM_USB_ROLE_HOST                1
#define ARM_USB_ROLE_DEVICE              2

/* USB Pins */
#define ARM_USB_PIN_DP                  (1 << 0) ///< USB D+ pin
#define ARM_USB_PIN_DM                  (1 << 1) ///< USB D- pin
#define ARM_USB_PIN_VBUS                (1 << 2) ///< USB VBUS pin
#define ARM_USB_PIN_OC                  (1 << 3) ///< USB OverCurrent pin
#define ARM_USB_PIN_ID                  (1 << 4) ///< USB ID pin

/* USB Speed */
#define ARM_USB_SPEED_LOW                0       ///< Low-speed USB
#define ARM_USB_SPEED_FULL               1       ///< Full-speed USB
#define ARM_USB_SPEED_HIGH               2       ///< High-speed USB

/* USB PID Types */
#define ARM_USB_PID_OUT                  1
#define ARM_USB_PID_IN                   9
#define ARM_USB_PID_SOF                  5
#define ARM_USB_PID_SETUP                13
#define ARM_USB_PID_DATA0                3
#define ARM_USB_PID_DATA1                11
#define ARM_USB_PID_DATA2                7
#define ARM_USB_PID_MDATA                15
#define ARM_USB_PID_ACK                  2
#define ARM_USB_PID_NAK                  10
#define ARM_USB_PID_STALL                14
#define ARM_USB_PID_NYET                 6
#define ARM_USB_PID_PRE                  12
#define ARM_USB_PID_ERR                  12
#define ARM_USB_PID_SPLIT                8
#define ARM_USB_PID_PING                 4
#define ARM_USB_PID_RESERVED             0

/* USB Endpoint Address (bEndpointAddress) */
#define ARM_USB_ENDPOINT_NUMBER_MASK     0x0F
#define ARM_USB_ENDPOINT_DIRECTION_MASK  0x80

/* USB Endpoint Type */
#define ARM_USB_ENDPOINT_CONTROL         0       ///< Control Endpoint
#define ARM_USB_ENDPOINT_ISOCHRONOUS     1       ///< Isochronous Endpoint
#define ARM_USB_ENDPOINT_BULK            2       ///< Bulk Endpoint
#define ARM_USB_ENDPOINT_INTERRUPT       3       ///< Interrupt Endpoint

/* USB Endpoint Maximum Packet Size (wMaxPacketSize) */
#define ARM_USB_ENDPOINT_MAX_PACKET_SIZE_MASK           0x07FF
#define ARM_USB_ENDPOINT_MICROFRAME_TRANSACTIONS_MASK   0x1800
#define ARM_USB_ENDPOINT_MICROFRAME_TRANSACTIONS_1      0x0000
#define ARM_USB_ENDPOINT_MICROFRAME_TRANSACTIONS_2      0x0800
#define ARM_USB_ENDPOINT_MICROFRAME_TRANSACTIONS_3      0x1000

#endif /* __DRIVER_USB_H */
