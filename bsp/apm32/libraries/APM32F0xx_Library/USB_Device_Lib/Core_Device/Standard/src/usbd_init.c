/*!
 * @file        usbd_init.c
 *
 * @brief       USB initialization management
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
#include "usbd_init.h"
#include "usb_bsp.h"

/** @addtogroup USB_Driver_Library USB Driver Library
  @{
*/

/** @addtogroup Core_Device Core Device
  @{
*/

/** @addtogroup Standrad
  @{
*/

/** @addtogroup Init
  @{
*/

/** @defgroup Init_Macros Macros
  @{
*/

/**@} end of group Init_Macros */

/** @defgroup Init_Enumerations Enumerations
  @{
*/

/**@} end of group Init_Enumerations */

/** @defgroup Init_Structures Structures
  @{
*/

/**@} end of group Init_Structures */

/** @defgroup Init_Variables Variables
  @{
*/

/**@} end of group Init_Variables */

/** @defgroup Init_Functions Functions
  @{
*/

static USBD_REG_EP_TYPE_T USBD_ConvertEPType(USBD_EP_TYPE_T epType);

/*!
 * @brief       USB initialization
 *
 * @param       param: Initialization parameter
 *
 * @retval      None
 */
void USBD_Init(USBD_InitParam_T* param)
{
    g_usbDev.pDeviceDesc = param->pDeviceDesc;
    g_usbDev.pConfigurationDesc = param->pConfigurationDesc;
    g_usbDev.pStringDesc = param->pStringDesc;
    g_usbDev.pQualifierDesc = param->pQualifierDesc;
    g_usbDev.pHidReportDesc = param->pHidReportDesc;

    g_usbDev.pStdReqCallback = param->pStdReqCallback;
    g_usbDev.classReqHandler = param->classReqHandler;
    g_usbDev.vendorReqHandler = param->vendorReqHandler;
    g_usbDev.stdReqExceptionHandler = param->stdReqExceptionHandler;

    g_usbDev.txStatusHandler = param->txStatusHandler;
    g_usbDev.rxStatusHandler = param->rxStatusHandler;

    g_usbDev.inEpHandler = param->inEpHandler;
    g_usbDev.outEpHandler = param->outEpHandler;

    g_usbDev.resetHandler = param->resetHandler;
    g_usbDev.intHandler = param->intHandler;

    USBD_HardWareInit();

#ifndef APM32F0xx_USB
#if USB_SELECT == USB1
    USBD2_Disable();
#else
    USB2_Enable();
#endif
#endif

    USBD_PowerOn();
}

/*!
 * @brief       Init parameter in param
 *
 * @param       param: Initialization parameter
 *
 * @retval      None
 */
void USBD_InitParamStructInit(USBD_InitParam_T* param)
{
    param->pStdReqCallback = NULL;
    param->stdReqExceptionHandler = NULL;
    param->classReqHandler = NULL;
    param->vendorReqHandler = NULL;

    param->txStatusHandler = NULL;
    param->rxStatusHandler = NULL;

    param->outEpHandler = NULL;
    param->inEpHandler = NULL;

    param->resetHandler = NULL;
    param->intHandler = NULL;
}

/*!
 * @brief       USB Power on
 *
 * @param       None
 *
 * @retval      None
 */
void USBD_PowerOn(void)
{
    USBD_ResetPowerDown();

    USBD_SetForceReset();
    USBD_ResetForceReset();

    USBD_DisableInterrupt(USBD_INT_ALL);
    USBD_ClearIntFlag(USBD_INT_ALL);

    USBD_EnableInterrupt(USB_INT_SOURCE);
}

/*!
 * @brief       USB Power off
 *
 * @param       None
 *
 * @retval      None
 */
void USBD_PowerOff(void)
{
    USBD_DisableInterrupt(USBD_INT_ALL);
    USBD_ClearIntFlag(USBD_INT_ALL);

    /* Power down and Force USB Reset */
    USBD_SetRegCTRL(0X03);
}


/*!
 * @brief       Open OUT endpoint.
 *
 * @param       epConfig: Point to USBD_EPConfig_T structure
 *
 * @retval      None
 */
void USBD_OpenOutEP(USBD_EPConfig_T* epConfig)
{
    g_usbDev.outBuf[epConfig->epNum].maxPackSize = epConfig->maxPackSize;

    USBD_SetEPType(epConfig->epNum, USBD_ConvertEPType(epConfig->epType));

    if (epConfig->epKind)
    {
        USBD_SetEPKind(epConfig->epNum);
    }
    else
    {
        USBD_ResetEPKind(epConfig->epNum);
    }

    USBD_SetEPRxAddr(epConfig->epNum, epConfig->epBufAddr);
    USBD_SetEPRxCnt(epConfig->epNum, epConfig->maxPackSize);
    USBD_SetEPRxStatus(epConfig->epNum, epConfig->epStatus);
}

/*!
 * @brief       Open IN endpoint.
 *
 * @param       epConfig: Point to USBD_EPConfig_T structure
 *
 * @retval      None
 */
void USBD_OpenInEP(USBD_EPConfig_T* epConfig)
{
    g_usbDev.inBuf[epConfig->epNum].maxPackSize = epConfig->maxPackSize;

    USBD_SetEPType(epConfig->epNum, USBD_ConvertEPType(epConfig->epType));

    if (epConfig->epKind)
    {
        USBD_SetEPKind(epConfig->epNum);
    }
    else
    {
        USBD_ResetEPKind(epConfig->epNum);
    }

    USBD_SetEPTxAddr(epConfig->epNum, epConfig->epBufAddr);
    USBD_SetEPTxStatus(epConfig->epNum, epConfig->epStatus);
}

/*!
 * @brief       Close OUT endpoint.
 *
 * @param       ep: OUT endpoint Number
 *
 * @retval      None
 */
void USBD_CloseOutEP(USBD_EP_T ep)
{
    g_usbDev.outBuf[ep].maxPackSize = 0;

    USBD_SetEPRxStatus(ep, USBD_EP_STATUS_DISABLE);
}

/*!
 * @brief       Close IN endpoint.
 *
 * @param       ep: IN endpoint Number
 *
 * @retval      None
 */
void USBD_CloseInEP(USBD_EP_T ep)
{
    g_usbDev.inBuf[ep].maxPackSize = 0;

    USBD_SetEPTxStatus(ep, USBD_EP_STATUS_DISABLE);
}

/*!
 * @brief       Convert endpoint Type.
 *
 * @param       epType: endpoint type
 *
 * @retval      Value of USBD_REG_EP_TYPE_T
 */
static USBD_REG_EP_TYPE_T USBD_ConvertEPType(USBD_EP_TYPE_T epType)
{
    switch (epType)
    {
        case USBD_EP_TYPE_CONTROL :
            return USBD_REG_EP_TYPE_CONTROL;
        case USBD_EP_TYPE_ISO :
            return USBD_REG_EP_TYPE_ISO;
        case USBD_EP_TYPE_BULK :
            return USBD_REG_EP_TYPE_BULK;
        case USBD_EP_TYPE_INTERRUPT :
            return USBD_REG_EP_TYPE_INTERRUPT;
        default :
            return USBD_REG_EP_TYPE_CONTROL;
    }
}

/**@} end of group Init_Functions */
/**@} end of group Init */
/**@} end of group Standard */
/**@} end of groupInit_Device */
/**@} end of group USB_Driver_Library */
