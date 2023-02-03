/*!
 * @file        usbd_class_cdc.c
 *
 * @brief       CDC Class handler file
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
#include "usbd_class_cdc.h"

/** @addtogroup USB_Driver_Library USB Driver Library
  @{
*/

/** @addtogroup Core_Device Core Device
  @{
*/

/** @addtogroup Class
  @{
*/

/** @addtogroup CDC
  @{
*/

/** @defgroup CDC_Macros Macros
  @{
*/

/**@} end of group CDC_Macros */

/** @defgroup CDC_Enumerations Enumerations
  @{
*/

/**@} end of group CDC_Enumerations */

/** @defgroup CDC_Structures Structures
  @{
*/

/**@} end of group CDC_Structures */

/** @defgroup CDC_Variables Variables
  @{
*/

static uint8_t cmdBuf[8] = {0};

/**@} end of group CDC_Variables */

/** @defgroup CDC_Functions Functions
  @{
*/

/*!
 * @brief       USB CDC Class request handler
 *
 * @param       reqData : point to USBD_DevReqData_T structure
 *
 * @retval      None
 */
void USBD_ClassHandler(USBD_DevReqData_T* reqData)
{
    uint16_t length = ((uint16_t)reqData->byte.wLength[1] << 8) | \
                      reqData->byte.wLength[0] ;

    if (!length)
    {
        if (!reqData->byte.bmRequestType.bit.dir)
        {
            USBD_CtrlTxStatus();
        }
        else
        {
            USBD_CtrlRxStatus();
        }
    }
    else
    {
        switch (reqData->byte.bRequest)
        {

            case 0x20:
                USBD_CtrlOutData(cmdBuf, length);
                break;
            case 0x21:
                USBD_CtrlInData(cmdBuf, length);
                break;
            case 0x22:
                USBD_CtrlOutData(cmdBuf, length);
                break;
            default:
                break;
        }
    }
}

/**@} end of group CDC_Functions */
/**@} end of group CDC */
/**@} end of group Class */
/**@} end of group Core_Device */
/**@} end of group USB_Driver_Library */
