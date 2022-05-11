/*!
 * @file        usbd_class_hid.h
 *
 * @brief       HID Class handler file head file
 *
 * @version     V1.0.0
 *
 * @date        2021-12-06
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "usbd_core.h"

#define HID_CLASS_REQ_SET_PROTOCOL          0x0B
#define HID_CLASS_REQ_GET_PROTOCOL          0x03

#define HID_CLASS_REQ_SET_IDLE              0x0A
#define HID_CLASS_REQ_GET_IDLE              0x02

#define HID_CLASS_REQ_SET_REPORT            0x09
#define HID_CLASS_REQ_GET_REPORT            0x01

void USBD_ClassHandler(USBD_DevReqData_T *reqData);
