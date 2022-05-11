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
 * $Revision:    V2.0
 *
 * Project:      USB Driver common definitions
 */

/* History:
 *  Version 2.0
 *  Version 1.10
 *    Namespace prefix ARM_ added
 *  Version 1.01
 *    Added PID Types
 *  Version 1.00
 *    Initial release
 */

#ifndef DRIVER_USB_H_
#define DRIVER_USB_H_

#include "Driver_Common.h"

/* USB Role */
#define ARM_USB_ROLE_NONE               (0)
#define ARM_USB_ROLE_HOST               (1)
#define ARM_USB_ROLE_DEVICE             (2)

/* USB Pins */
#define ARM_USB_PIN_DP                  (1 << 0) ///< USB D+ pin
#define ARM_USB_PIN_DM                  (1 << 1) ///< USB D- pin
#define ARM_USB_PIN_VBUS                (1 << 2) ///< USB VBUS pin
#define ARM_USB_PIN_OC                  (1 << 3) ///< USB OverCurrent pin
#define ARM_USB_PIN_ID                  (1 << 4) ///< USB ID pin

/* USB Speed */
#define ARM_USB_SPEED_LOW               (0)      ///< Low-speed USB
#define ARM_USB_SPEED_FULL              (1)      ///< Full-speed USB
#define ARM_USB_SPEED_HIGH              (2)      ///< High-speed USB

/* USB PID Types */
#define ARM_USB_PID_OUT                 (1)
#define ARM_USB_PID_IN                  (9)
#define ARM_USB_PID_SOF                 (5)
#define ARM_USB_PID_SETUP               (13)
#define ARM_USB_PID_DATA0               (3)
#define ARM_USB_PID_DATA1               (11)
#define ARM_USB_PID_DATA2               (7)
#define ARM_USB_PID_MDATA               (15)
#define ARM_USB_PID_ACK                 (2)
#define ARM_USB_PID_NAK                 (10)
#define ARM_USB_PID_STALL               (14)
#define ARM_USB_PID_NYET                (6)
#define ARM_USB_PID_PRE                 (12)
#define ARM_USB_PID_ERR                 (12)
#define ARM_USB_PID_SPLIT               (8)
#define ARM_USB_PID_PING                (4)
#define ARM_USB_PID_RESERVED            (0)

/* USB Endpoint Address (bEndpointAddress) */
#define ARM_USB_ENDPOINT_NUMBER_MASK    (0x0F)
#define ARM_USB_ENDPOINT_DIRECTION_MASK (0x80)

/* USB Endpoint Type */
#define ARM_USB_ENDPOINT_CONTROL        (0)      ///< Control Endpoint
#define ARM_USB_ENDPOINT_ISOCHRONOUS    (1)      ///< Isochronous Endpoint
#define ARM_USB_ENDPOINT_BULK           (2)      ///< Bulk Endpoint
#define ARM_USB_ENDPOINT_INTERRUPT      (3)      ///< Interrupt Endpoint

/* USB Endpoint Maximum Packet Size (wMaxPacketSize) */
#define ARM_USB_ENDPOINT_MAX_PACKET_SIZE_MASK           (0x07FF)
#define ARM_USB_ENDPOINT_MICROFRAME_TRANSACTIONS_MASK   (0x1800)
#define ARM_USB_ENDPOINT_MICROFRAME_TRANSACTIONS_1      (0x0000)
#define ARM_USB_ENDPOINT_MICROFRAME_TRANSACTIONS_2      (0x0800)
#define ARM_USB_ENDPOINT_MICROFRAME_TRANSACTIONS_3      (0x1000)

#endif /* DRIVER_USB_H_ */
