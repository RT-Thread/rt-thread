/*!
 * @file        usbd_class_msc.c
 *
 * @brief       MSC Class file
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

#include "usbd_class_msc.h"
#include "usbd_msc_bot.h"

static uint8_t s_mscMaxLen = 0;

/*!
 * @brief       USB MSC Class request handler
 *
 * @param       reqData : point to USBD_DevReqData_T structure
 *
 * @retval      None
 */
void USBD_MSC_ClassHandler(USBD_DevReqData_T *reqData)
{
    uint16_t wValue = ((uint16_t)reqData->byte.wValue[1] << 8) | \
                      reqData->byte.wValue[0];
    uint16_t wLength = ((uint16_t)reqData->byte.wLength[1] << 8) | \
                       reqData->byte.wLength[0];

    switch (reqData->byte.bRequest)
    {
    case BOT_GET_MAX_LUN :
        if ((wValue == 0) && (wLength == 1) && \
                (reqData->byte.bmRequestType.bit.dir == 1))
        {
            s_mscMaxLen = STORAGE_MAX_LUN - 1;

            USBD_CtrlInData(&s_mscMaxLen, 1);
        }
        else
        {
            USBD_SetEPTxRxStatus(USBD_EP_0, USBD_EP_STATUS_STALL, USBD_EP_STATUS_STALL);
        }
        break;
    case BOT_RESET :
        if ((wValue == 0) && (wLength == 0) && \
                (reqData->byte.bmRequestType.bit.dir == 0))
        {
            USBD_CtrlInData(NULL, 0);
            /** Reset */
            USBD_MSC_BOT_Reset();
        }
        else
        {
            USBD_SetEPTxRxStatus(USBD_EP_0, USBD_EP_STATUS_STALL, USBD_EP_STATUS_STALL);
        }

        break;

    default:
        USBD_SetEPTxRxStatus(USBD_EP_0, USBD_EP_STATUS_STALL, USBD_EP_STATUS_STALL);
        break;
    }
}
