/*!
 * @file        usbd_stdReq.c
 *
 * @brief       USB standard request process
 *
 * @version     V1.0.0
 *
 * @date        2021-12-30
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

#include "usbd_stdReq.h"
#include "usbd_core.h"
#include "usbd_descriptor.h"

static uint8_t USBD_StandardGetConfiguration(void);
static uint8_t USBD_StandardGetDescriptor(void);
static uint8_t USBD_StandardGetInterface(void);
static uint8_t USBD_StandardGetStatus(void);

static uint8_t USBD_StandardSetAddress(void);
static uint8_t USBD_StandardSetConfiguration(void);
static uint8_t USBD_StandardSetDescriptor(void);
static uint8_t USBD_StandardSetFeature(void);
static uint8_t USBD_StandardSetInterface(void);

static uint8_t USBD_StandardClearFeature(void);


/*!
 * @brief       USB request standard request
 *
 * @param       None
 *
 * @retval      None
 */
void USBD_StandardReqeust(void)
{
    uint8_t result = 1;

    uint8_t bRequest = g_usbDev.reqData.byte.bRequest;

    switch(bRequest)
    {
        case USBD_GET_CONFIGURATION:
            result = USBD_StandardGetConfiguration();
        break;

        case USBD_GET_DESCRIPTOR:
            result = USBD_StandardGetDescriptor();
        break;

        case USBD_GET_INTERFACE:
            result = USBD_StandardGetInterface();
        break;

        case USBD_GET_STATUS:
            result = USBD_StandardGetStatus();
        break;

        case USBD_SET_ADDRESS:
            result = USBD_StandardSetAddress();
        break;

        case USBD_SET_CONFIGURATION:
            result = USBD_StandardSetConfiguration();
        break;

        case USBD_SET_DESCRIPTOR:
            result = USBD_StandardSetDescriptor();
        break;

        case USBD_SET_FEATURE:
            result = USBD_StandardSetFeature();
        break;

        case USBD_SET_INTERFACE:
            result = USBD_StandardSetInterface();

        break;

        case USBD_CLEAR_FEATURE:
            result = USBD_StandardClearFeature();
        break;

        default:

            break;
    }

    if(!result)
    {
        if(g_usbDev.stdReqExceptionHandler != NULL)
        {
            g_usbDev.stdReqExceptionHandler(&g_usbDev.reqData);
        }
        else
        {
            USBD_SetEPTxRxStatus(USBD_EP_0, USBD_EP_STATUS_STALL, USBD_EP_STATUS_STALL);
        }
    }
}

/*!
 * @brief       Standard request get configuration
 *
 * @param       None
 *
 * @retval      ERROR: 0;  SUCCESS : 1
 */
static uint8_t USBD_StandardGetConfiguration(void)
{
    uint8_t recipient = g_usbDev.reqData.byte.bmRequestType.bit.recipient;

    if(recipient == USBD_RECIPIENT_DEVICE)
    {
        USBD_CtrlInData(&g_usbDev.curConfiguration, 1);

        if (g_usbDev.pStdReqCallback->getConfigurationHandler)
        {
            g_usbDev.pStdReqCallback->getConfigurationHandler();
        }


        return SUCCESS;
    }

    return ERROR;
}

/*!
 * @brief       Standard request get descriptor
 *
 * @param       None
 *
 * @retval      ERROR: 0;  SUCCESS : 1
 */
static uint8_t USBD_StandardGetDescriptor(void)
{
    uint8_t ret = SUCCESS;
    uint32_t len = 0;
    uint8_t wValue0 = g_usbDev.reqData.byte.wValue[0];
    uint8_t wValue1 = g_usbDev.reqData.byte.wValue[1];

    if(wValue1 == USBD_DESC_DEVICE)
    {
        len = USB_MIN(*(uint16_t *)g_usbDev.reqData.byte.wLength, g_usbDev.pDeviceDesc->size);
        USBD_CtrlInData((uint8_t *)g_usbDev.pDeviceDesc->pDesc, len);
    }
    else if(wValue1 == USBD_DESC_CONFIGURATION)
    {
        len = USB_MIN(*(uint16_t *)g_usbDev.reqData.byte.wLength, g_usbDev.pConfigurationDesc->size);
        USBD_CtrlInData((uint8_t *)g_usbDev.pConfigurationDesc->pDesc, len);
    }
    else if(wValue1 == USBD_DESC_STRING)
    {
        if (wValue0 < SRTING_DESC_NUM)
        {
            len = USB_MIN(*(uint16_t *)g_usbDev.reqData.byte.wLength, g_usbDev.pStringDesc[wValue0].size);
            USBD_CtrlInData((uint8_t *)g_usbDev.pStringDesc[wValue0].pDesc, len);
        }
        else
        {
            ret = ERROR;
        }

    }
    else
    {
        ret = ERROR;
    }

    return ret;
}

/*!
 * @brief       Standard request get interface
 *
 * @param       None
 *
 * @retval      ERROR: 0;  SUCCESS : 1
 */
static uint8_t USBD_StandardGetInterface(void)
{

    return ERROR;
}

/*!
 * @brief       Standard request get status
 *
 * @param       None
 *
 * @retval      ERROR: 0; SUCCESS : 1
 */
static uint8_t USBD_StandardGetStatus(void)
{
    uint8_t ret = 1;


    uint8_t status[2] = {0, 0};

    if((g_usbDev.reqData.byte.bmRequestType.bit.recipient) == USBD_RECIPIENT_DEVICE)
    {
        if(g_usbDev.curFeature & (1 << 5))
        {
            status[0] |= 0x02;
        }

        if(g_usbDev.curFeature & (1 << 6))
        {
            status[0] |= 0x01;
        }

        USBD_CtrlInData(status, 2);


    }

    else if((g_usbDev.reqData.byte.bmRequestType.bit.recipient) == USBD_RECIPIENT_INTERFACE)
    {
        USBD_CtrlInData(status, 2);


    }

    else if((g_usbDev.reqData.byte.bmRequestType.bit.recipient) == USBD_RECIPIENT_ENDPOINT)
    {

        if(g_usbDev.reqData.byte.wIndex[0] & 0x80)
        {
            if(USBD_ReadEPTxStatus(g_usbDev.reqData.byte.wIndex[0] & 0x0f) == USBD_EP_STATUS_STALL)
            {
                status[0] |= 0x01;
            }
        }
        else
        {
            if(USBD_ReadEPRxStatus(g_usbDev.reqData.byte.wIndex[0] & 0x0f) == USBD_EP_STATUS_STALL)
            {
                status[0] |= 0x01;
            }

        }
        USBD_CtrlInData(status, 2);

    }
    else
    {
        ret = 0;
    }

    return ret;
}

/*!
 * @brief       Standard request set address
 *
 * @param       None
 *
 * @retval      ERROR: 0; SUCCESS : 1
 */
static uint8_t USBD_StandardSetAddress(void)
{
    USBD_DevReqData_T *reqData = &g_usbDev.reqData;

    if((reqData->byte.wValue[0] < 127) && (reqData->byte.wValue[1] == 0) &&
        (reqData->byte.bmRequestType.bit.recipient == USBD_RECIPIENT_DEVICE))
    {
        USBD_CtrlInData((void *)0, 0);

        return 1;
    }

    return 0;
}

/*!
 * @brief       Standard request set configuration
 *
 * @param       None
 *
 * @retval      ERROR: 0;  SUCCESS : 1
 */
static uint8_t USBD_StandardSetConfiguration(void)
{
    USBD_DevReqData_T *reqData = &g_usbDev.reqData;

    if((reqData->byte.wValue[0] <= g_usbDev.configurationNum) && \
       (reqData->byte.bmRequestType.bit.recipient == USBD_RECIPIENT_DEVICE))
    {
        g_usbDev.curConfiguration = reqData->byte.wValue[0];

        if (g_usbDev.pStdReqCallback->setConfigurationHandler)
        {
            g_usbDev.pStdReqCallback->setConfigurationHandler();
        }

        USBD_CtrlInData((void *)0, 0);

        return 1;
    }

    return 0;
}

/*!
 * @brief       Standard request set descriptor
 *
 * @param       None
 *
 * @retval      0: Failed; 1: Success
 */
static uint8_t USBD_StandardSetDescriptor(void)
{

    return ERROR;
}

/*!
 * @brief       Standard request set feature
 *
 * @param       None
 *
 * @retval      0: Failed; 1: Success
 */
static uint8_t USBD_StandardSetFeature(void)
{
    uint8_t ret = 1;

    return ret;
}

/*!
 * @brief       Standard request set interface
 *
 * @param       None
 *
 * @retval      0: Failed; 1: Success
 */
static uint8_t USBD_StandardSetInterface(void)
{

    return 0;
}

/*!
 * @brief       Standard request clear feature
 *
 * @param       None
 *
 * @retval      0: Failed; 1: Success
 */
static uint8_t USBD_StandardClearFeature(void)
{
    return 0;
}
