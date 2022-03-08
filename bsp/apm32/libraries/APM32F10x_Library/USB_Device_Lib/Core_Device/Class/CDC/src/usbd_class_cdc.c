/*!
 * @file        usbd_class_cdc.c
 *
 * @brief       CDC Class handler file
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

#include "usbd_class_cdc.h"

static uint8_t cmdBuf[8] = {0};

/*!
 * @brief       USB CDC Class request handler
 *
 * @param       reqData : point to USBD_DevReqData_T structure
 *
 * @retval      None
 */
void USBD_ClassHandler(USBD_DevReqData_T *reqData)
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
