/*!
 * @file        usbd_core.c
 *
 * @brief       USB protocol core handler
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
#include "usbd_core.h"
#include "usbd_stdReq.h"

/** @addtogroup USB_Driver_Library USB Driver Library
  @{
*/

/** @addtogroup Core_Device Core Device
  @{
*/

/** @addtogroup Standrad
  @{
*/

/** @addtogroup Core
  @{
*/

/** @defgroup Core_Macros Macros
  @{
*/

/**@} end of group Core_Macros */

/** @defgroup Core_Enumerations Enumerations
  @{
*/

/**@} end of group Core_Enumerations */

/** @defgroup Core_Structures Structures
  @{
*/

/**@} end of group Core_Structures */

/** @defgroup Core_Variables Variables
  @{
*/

/* USB information */
USBD_Info_T g_usbDev;

/**@} end of group Core_Variables */

/** @defgroup Core_Functions Functions
  @{
*/

/*!
 * @brief       Endpoint 0 Setup process
 *
 * @param       None
 *
 * @retval      None
 */
void USBD_SetupProcess(void)
{
    uint8_t reqType;
    uint8_t dataBuf[8];
    USBD_DevReqData_T* pReqData = &g_usbDev.reqData;
    uint16_t xferLen = USBD_ReadEPRxCnt(USBD_EP_0);

    if (xferLen)
    {
        USBD_ReadDataFromEP(USBD_EP_0, (uint8_t*)dataBuf, xferLen);
    }
    else
    {
        return;
    }

    pReqData->byte.bmRequestType.byte = dataBuf[0];
    pReqData->byte.bRequest = dataBuf[1];
    pReqData->byte.wValue[0] = dataBuf[2];
    pReqData->byte.wValue[1] = dataBuf[3];
    pReqData->byte.wIndex[0] = dataBuf[4];
    pReqData->byte.wIndex[1] = dataBuf[5];
    pReqData->byte.wLength[0] = dataBuf[6];
    pReqData->byte.wLength[1] = dataBuf[7];

    reqType = pReqData->byte.bmRequestType.bit.type;

    if (reqType == USBD_REQ_TYPE_STANDARD)
    {
        USBD_StandardReqeust();
    }
    else if (reqType == USBD_REQ_TYPE_CLASS)
    {
        if (g_usbDev.classReqHandler)
        {
            g_usbDev.classReqHandler(pReqData);
        }
    }
    else if (reqType == USBD_REQ_TYPE_VENDOR)
    {
        if (g_usbDev.vendorReqHandler)
        {
            g_usbDev.vendorReqHandler(pReqData);
        }
    }
    else
    {
        USBD_SetEPTxRxStatus(USBD_EP_0, USBD_EP_STATUS_STALL, USBD_EP_STATUS_STALL);
    }
}


/*!
 * @brief       Endpoint 0 USB Control in process
 *
 * @param       None
 *
 * @retval      None
 */
void USBD_CtrlInProcess(void)
{
    uint32_t tmp;

    if (g_usbDev.ctrlState == USBD_CTRL_STATE_DATA_IN)
    {
        if (g_usbDev.inBuf[0].packNum)
        {
            tmp = USB_MIN(g_usbDev.inBuf[0].bufLen, g_usbDev.inBuf[0].maxPackSize);

            USBD_WriteDataToEP(USBD_EP_0, g_usbDev.inBuf[0].pBuf, tmp);
            USBD_SetEPTxCnt(USBD_EP_0, tmp);
            USBD_SetEPTxRxStatus(USBD_EP_0, USBD_EP_STATUS_VALID, USBD_EP_STATUS_NAK);

            g_usbDev.inBuf[0].pBuf += tmp;
            g_usbDev.inBuf[0].bufLen -= tmp;
            g_usbDev.inBuf[0].packNum--;
        }
        else
        {
            if (g_usbDev.inBuf[USBD_EP_0].zeroPackFill)
            {
                USBD_SetEPTxCnt(USBD_EP_0, 0);
                USBD_SetEPTxStatus(USBD_EP_0, USBD_EP_STATUS_VALID);
                g_usbDev.inBuf[USBD_EP_0].zeroPackFill = 0;
            }
            else
            {
                if (g_usbDev.rxStatusHandler)
                {
                    g_usbDev.rxStatusHandler();
                }

                g_usbDev.ctrlState = USBD_CTRL_STATE_WAIT_STATUS_OUT;
                USBD_SetEPTxRxStatus(USBD_EP_0, USBD_EP_STATUS_NAK, USBD_EP_STATUS_VALID);
            }

        }
    }
    else if (g_usbDev.ctrlState == USBD_CTRL_STATE_WAIT_STATUS_IN)
    {
        if (g_usbDev.reqData.byte.bRequest == USBD_SET_ADDRESS)
        {
            USBD_SetDeviceAddr(g_usbDev.reqData.byte.wValue[0]);
        }
    }
}

/*!
 * @brief       Endpoint 0 USB Control out process
 *
 * @param       None
 *
 * @retval      None
 */
void USBD_CtrlOutProcess(void)
{
    uint32_t len;

    if (g_usbDev.ctrlState == USBD_CTRL_STATE_DATA_OUT)
    {
        if (g_usbDev.outBuf[0].packNum)
        {
            len = USB_MIN(g_usbDev.outBuf[0].bufLen, g_usbDev.outBuf[0].maxPackSize);

            USBD_ReadDataFromEP(USBD_EP_0, g_usbDev.outBuf[0].pBuf, len);

            g_usbDev.outBuf[0].bufLen -= len;
            g_usbDev.outBuf[0].pBuf += len;
            g_usbDev.outBuf[0].packNum--;

            if (g_usbDev.outBuf[0].packNum)
            {
                USBD_CtrlOutData(g_usbDev.outBuf[0].pBuf, g_usbDev.outBuf[0].bufLen);
            }
            else
            {
                USBD_CtrlTxStatus();
            }
        }
        else
        {
            if (g_usbDev.txStatusHandler)
            {
                g_usbDev.txStatusHandler();
            }

            USBD_CtrlTxStatus();
        }
    }
}

/*!
 * @brief       Send data or status in control in transation
 *
 * @param       buf:    Buffer pointer
 *
 * @param       len:    Buffer length
 *
 * @retval      None
 */
void USBD_CtrlInData(uint8_t* buf, uint32_t len)
{
    uint16_t maxPackSize = g_usbDev.inBuf[0].maxPackSize;
    uint16_t reqLen = *(uint16_t*)g_usbDev.reqData.byte.wLength;

    if (len)
    {
        if ((len < reqLen) && ((len % maxPackSize) == 0))
        {
            g_usbDev.inBuf[USBD_EP_0].zeroPackFill = 1;
        }

        if (len >= g_usbDev.inBuf[0].maxPackSize)
        {
            /* Send a packet */
            USBD_WriteDataToEP(USBD_EP_0, buf, g_usbDev.inBuf[0].maxPackSize);
            USBD_SetEPTxCnt(USBD_EP_0, g_usbDev.inBuf[0].maxPackSize);
            USBD_SetEPTxRxStatus(USBD_EP_0, USBD_EP_STATUS_VALID, USBD_EP_STATUS_NAK);

            /* deal with buffer */
            g_usbDev.inBuf[0].bufLen = len - g_usbDev.inBuf[0].maxPackSize;
            g_usbDev.inBuf[0].pBuf = buf + g_usbDev.inBuf[0].maxPackSize;
            g_usbDev.inBuf[0].packNum = (g_usbDev.inBuf[0].bufLen + (maxPackSize - 1)) / maxPackSize;

            g_usbDev.ctrlState = USBD_CTRL_STATE_DATA_IN;
        }
        else
        {
            USBD_WriteDataToEP(USBD_EP_0, buf, len);
            USBD_SetEPTxCnt(USBD_EP_0, len);
            USBD_SetEPTxRxStatus(USBD_EP_0, USBD_EP_STATUS_VALID, USBD_EP_STATUS_NAK);

            g_usbDev.ctrlState = g_usbDev.reqData.byte.bmRequestType.bit.dir ? \
                                 USBD_CTRL_STATE_DATA_IN : \
                                 USBD_CTRL_STATE_WAIT_STATUS_IN;
        }
    }
    else
    {
        USBD_SetEPTxCnt(USBD_EP_0, 0);
        USBD_SetEPTxStatus(USBD_EP_0, USBD_EP_STATUS_VALID);

        g_usbDev.ctrlState = g_usbDev.reqData.byte.bmRequestType.bit.dir ? \
                             USBD_CTRL_STATE_DATA_IN : \
                             USBD_CTRL_STATE_WAIT_STATUS_IN;
    }
}

/*!
 * @brief       Read data or status in control out transation
 *
 * @param       buf:    Buffer pointer
 *
 * @param       len:    Buffer length
 *
 * @retval      None
 */
void USBD_CtrlOutData(uint8_t* buf, uint32_t len)
{
    uint16_t maxPackSize = g_usbDev.outBuf[USBD_EP_0].maxPackSize;

    if (len)
    {
        g_usbDev.outBuf[USBD_EP_0].pBuf = buf;
        g_usbDev.outBuf[USBD_EP_0].bufLen = len;
        g_usbDev.outBuf[USBD_EP_0].packNum = (len + (maxPackSize - 1)) / maxPackSize;

        len = USB_MIN(g_usbDev.outBuf[0].bufLen, maxPackSize);

        USBD_SetEPTxRxStatus(USBD_EP_0, USBD_EP_STATUS_NAK, USBD_EP_STATUS_VALID);

        g_usbDev.ctrlState = USBD_CTRL_STATE_DATA_OUT;
    }
    else
    {
        g_usbDev.ctrlState = USBD_CTRL_STATE_WAIT_STATUS_OUT;
    }

    USBD_SetEPTxRxStatus(USBD_EP_0, USBD_EP_STATUS_NAK, USBD_EP_STATUS_VALID);
}

/*!
 * @brief       USB Data in process except endpoint 0
 *
 * @param       ep : endpoint Number except endpoint 0
 *
 * @retval      None
 */
void USBD_DataInProcess(USBD_EP_T ep)
{
    uint16_t len;

    if (g_usbDev.inBuf[ep].packNum)
    {
        len = g_usbDev.inBuf[ep].bufLen > g_usbDev.inBuf[ep].maxPackSize ? \
              g_usbDev.inBuf[ep].maxPackSize : g_usbDev.inBuf[ep].bufLen;


        USBD_WriteDataToEP(ep, g_usbDev.inBuf[ep].pBuf, len);
        USBD_SetEPTxCnt(ep, len);
        USBD_SetEPTxStatus(ep, USBD_EP_STATUS_VALID);

        g_usbDev.inBuf[ep].pBuf += len;
        g_usbDev.inBuf[ep].bufLen -= len;
        g_usbDev.inBuf[ep].packNum--;
    }
    else
    {
        if (g_usbDev.inEpHandler)
        {
            g_usbDev.inEpHandler(ep);
        }
    }
}

/*!
 * @brief       USB Data out process except endpoint 0
 *
 * @param       ep : endpoint Number except endpoint 0
 *
 * @retval      None
 */
void USBD_DataOutProcess(USBD_EP_T ep)
{
    if (g_usbDev.outBuf[ep].packNum)
    {
        g_usbDev.outBuf[ep].xferCnt = USBD_ReadEPRxCnt(ep);

        if ((g_usbDev.outBuf[ep].xferCnt != 0) && (g_usbDev.outBuf[ep].pBuf != NULL))
        {
            USBD_ReadDataFromEP(ep, g_usbDev.outBuf[ep].pBuf, g_usbDev.outBuf[ep].xferCnt);

            g_usbDev.outBuf[ep].bufLen -= g_usbDev.outBuf[ep].xferCnt;
            g_usbDev.outBuf[ep].pBuf += g_usbDev.outBuf[ep].xferCnt;
            g_usbDev.outBuf[ep].packNum--;
        }
        if (g_usbDev.outBuf[ep].packNum)
        {
            USBD_SetEPRxStatus(ep, USBD_EP_STATUS_VALID);
        }
    }

    if (g_usbDev.outEpHandler && !g_usbDev.outBuf[ep].packNum)
    {
        g_usbDev.outEpHandler(ep);
    }
}

/*!
 * @brief       Transfer data to host(except endpoint 0)
 *
 * @param       ep:     Endpoint number except endpoint 0
 *
 * @param       buf:    Buffer pointer
 *
 * @param       len:    Buffer length
 *
 * @retval      None
 */
void USBD_TxData(uint8_t ep, uint8_t* buf, uint32_t len)
{
    uint16_t maxPackSize = g_usbDev.inBuf[ep].maxPackSize;

    if (len >= maxPackSize)
    {
        USBD_WriteDataToEP(ep, buf, maxPackSize);
        USBD_SetEPTxCnt(ep, maxPackSize);
        USBD_SetEPTxStatus(ep, USBD_EP_STATUS_VALID);

        g_usbDev.inBuf[ep].pBuf = buf + maxPackSize;
        g_usbDev.inBuf[ep].bufLen = len - maxPackSize;
        g_usbDev.inBuf[ep].packNum = (g_usbDev.inBuf[ep].bufLen + (maxPackSize - 1)) / maxPackSize;
    }
    else
    {
        USBD_WriteDataToEP(ep, buf, len);
        USBD_SetEPTxCnt(ep, len);
        USBD_SetEPTxStatus(ep, USBD_EP_STATUS_VALID);

        g_usbDev.inBuf[ep].packNum = 0;
        g_usbDev.inBuf[ep].bufLen = 0;
    }
}

/*!
 * @brief       Receive data from host(except endpoint 0)
 *
 * @param       ep:     Endpoint number except endpoint 0
 *
 * @param       buf:    Buffer pointer
 *
 * @param       len:    Buffer length
 *
 * @retval      None
 */
void USBD_RxData(uint8_t ep, uint8_t* buf, uint32_t len)
{
    uint16_t maxPackSize = g_usbDev.outBuf[ep].maxPackSize;

    g_usbDev.outBuf[ep].pBuf = buf;
    g_usbDev.outBuf[ep].bufLen = len;
    g_usbDev.outBuf[ep].packNum = (len + (maxPackSize - 1)) / maxPackSize;

    USBD_SetEPRxCnt(ep, USB_MIN(len, maxPackSize));

    USBD_SetEPRxStatus(ep, USBD_EP_STATUS_VALID);
}

/**@} end of group Core_Functions */
/**@} end of group Core */
/**@} end of group Standard */
/**@} end of group Core_Device */
/**@} end of group USB_Driver_Library */
