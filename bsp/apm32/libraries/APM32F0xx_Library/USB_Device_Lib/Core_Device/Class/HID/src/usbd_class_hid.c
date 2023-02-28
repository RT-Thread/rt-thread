/*!
 * @file        usbd_class_hid.c
 *
 * @brief       HID Class handler file
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

/* Includes */
#include "usbd_class_hid.h"

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

static uint8_t s_hidIdleState;
static uint8_t s_hidProtocol;

/**@} end of group HID_Variables */

/** @defgroup HID_Functions Functions
  @{
*/

/*!
 * @brief       USB HID Class request handler
 *
 * @param       reqData : point to USBD_DevReqData_T structure
 *
 * @retval      None
 */
void USBD_ClassHandler(USBD_DevReqData_T* reqData)
{
    switch (reqData->byte.bRequest)
    {
        case HID_CLASS_REQ_SET_IDLE:
            s_hidIdleState = reqData->byte.wValue[1];
            USBD_CtrlInData(NULL, 0);
            break;

        case HID_CLASS_REQ_GET_IDLE:
            USBD_CtrlInData(&s_hidIdleState, 1);
            break;

        case HID_CLASS_REQ_SET_PROTOCOL:
            s_hidProtocol = reqData->byte.wValue[0];
            USBD_CtrlInData(NULL, 0);
            break;

        case HID_CLASS_REQ_GET_PROTOCOL:
            USBD_CtrlInData(&s_hidProtocol, 1);
            break;

        default:
            break;
    }
}

/**@} end of group HID_Functions */
/**@} end of group HID */
/**@} end of group Class */
/**@} end of group Core_Device */
/**@} end of group USB_Driver_Library */
