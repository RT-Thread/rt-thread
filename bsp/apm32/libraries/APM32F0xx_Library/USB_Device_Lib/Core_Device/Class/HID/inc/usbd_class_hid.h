/*!
 * @file        usbd_class_hid.h
 *
 * @brief       HID Class handler file head file
 *
 * @version     V1.0.1
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __USBD_HID_CLASS_
#define __USBD_HID_CLASS_

/* Includes */
#include "usbd_core.h"

/** @addtogroup USB_Driver_Library USB Driver Library
  @{
*/

/** @addtogroup Core_Device Core Device
  @{
*/

/** @addtogroup Class
  @{
*/

/** @addtogroup HID
  @{
*/

/** @defgroup HID_Macros Macros
  @{
*/

#define HID_CLASS_REQ_SET_PROTOCOL          0x0B
#define HID_CLASS_REQ_GET_PROTOCOL          0x03

#define HID_CLASS_REQ_SET_IDLE              0x0A
#define HID_CLASS_REQ_GET_IDLE              0x02

#define HID_CLASS_REQ_SET_REPORT            0x09
#define HID_CLASS_REQ_GET_REPORT            0x01

/**@} end of group HID_Macros */

/** @defgroup HID_Enumerations Enumerations
  @{
*/

/**@} end of group HID_Enumerations */

/** @defgroup HID_Structures Structures
  @{
*/

/**@} end of group HID_Structures */

/** @defgroup HID_Variables Variables
  @{
*/

/**@} end of group HID_Variables */

/** @defgroup HID_Functions Functions
  @{
*/

void USBD_ClassHandler(USBD_DevReqData_T* reqData);

#endif

/**@} end of group HID_Functions */
/**@} end of group HID */
/**@} end of group Class */
/**@} end of group Core_Device */
/**@} end of group USB_Driver_Library */
