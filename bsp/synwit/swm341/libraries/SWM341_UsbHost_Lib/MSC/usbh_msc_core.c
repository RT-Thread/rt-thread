/******************************************************************************************************************************************
* 文件名称: usbh_msc_core.c
* 功能说明:
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.1.0      2020年11月3日
* 升级记录:
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology
*******************************************************************************************************************************************/
#include "SWM341.h"
#include "usbh_core.h"
#include "usbh_stdreq.h"
#include "usbh_msc_bot.h"
#include "usbh_msc_core.h"
#include "usbh_msc_scsi.h"


USBH_Class_cb_t USBH_MSC_cb =
{
    USBH_MSC_Init,
    USBH_MSC_DeInit,
    USBH_MSC_Request,
    USBH_MSC_Process,
};


volatile USBH_MSC_Info_t USBH_MSC_Info;
volatile USBH_BOTXfer_t  USBH_BOTXfer;


static uint8_t DataInBuffer[64];


/******************************************************************************************************************************************
* 函数名称: USBH_MSC_Init()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MSC_Init(USBH_Info_t *phost)
{
    USB_EpDesc_t *pEpIn, *pEpOut;

    if((phost->Device.Intf_Desc[0].bInterfaceClass == USB_MSC_CLASS) && \
       (phost->Device.Intf_Desc[0].bInterfaceProtocol == USB_MSC_BOT))
    {
        if(phost->Device.Ep_Desc[0][0].bEndpointAddress & USB_EP_IN)
        {
            pEpIn  = &phost->Device.Ep_Desc[0][0];
            pEpOut = &phost->Device.Ep_Desc[0][1];
        }
        else
        {
            pEpIn  = &phost->Device.Ep_Desc[0][1];
            pEpOut = &phost->Device.Ep_Desc[0][0];
        }

        USBH_MSC_Info.InEp      = pEpIn->bEndpointAddress;
        USBH_MSC_Info.InEpSize  = pEpIn->wMaxPacketSize;
        USBH_MSC_Info.OutEp     = pEpOut->bEndpointAddress;
        USBH_MSC_Info.OutEpSize = pEpOut->wMaxPacketSize;

        USBH_MSC_DeInit(phost);
    }
    else
    {
        if(phost->usr_cb->DeviceNotSupported)
            phost->usr_cb->DeviceNotSupported();
    }

    return USBH_OK ;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MSC_DeInit()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBH_MSC_DeInit(USBH_Info_t *phost)
{
    USBH_MSC_Info.Ready = 0;
    USBH_MSC_Info.InEpDATAX  = 0;
    USBH_MSC_Info.OutEpDATAX = 0;

    USBH_MSC_BOT_Init();
}


/******************************************************************************************************************************************
* 函数名称: USBH_MSC_Request()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MSC_Request(USBH_Info_t *phost)
{
    USBH_BOTXfer.MSCState = USBH_MSC_GET_MAXLUN;

    return USBH_OK;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MSC_Process()
* 功能说明:  MSC state machine handler
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MSC_Process(USBH_Info_t *phost)
{
    USBH_Status status = USBH_BUSY;

    uint8_t mscStatus;
    uint8_t appStatus;

    switch(USBH_BOTXfer.MSCState)
    {
    case USBH_MSC_GET_MAXLUN:
        status = USBH_MSC_getMaxLUN(phost);
        if(status == USBH_OK)
        {
            USBH_MSC_Info.MaxLUN = DataInBuffer[0];

            USBH_BOTXfer.MSCState = USBH_MSC_TEST_UNIT_READY;
        }
        else if(status == USBH_NOT_SUPPORTED)
        {
            /* 清除 STALL 后，进入 USBH_MSC_TEST_UNIT_READY */
            USBH_BOTXfer.MSCStateBkp = USBH_MSC_TEST_UNIT_READY;

            USBH_BOTXfer.MSCState = USBH_MSC_CLEAR_STALL;
        }
        break;

    case USBH_MSC_CLEAR_STALL:
        status = USBH_ClrFeature(phost, USBH_MSC_Info.InEp);
        if(status == USBH_OK)
        {
            USBH_MSC_Info.MaxLUN = 0;   // 不支持 GetMaxLUN 请求，假设只有一个逻辑单元

            USBH_BOTXfer.MSCState = USBH_BOTXfer.MSCStateBkp;
        }
        break;

    case USBH_MSC_TEST_UNIT_READY:
        mscStatus = USBH_MSC_TestUnitReady();
        if(mscStatus == USBH_MSC_OK)
        {
            USBH_BOTXfer.MSCState = USBH_MSC_READ_CAPACITY10;

            status = USBH_OK;
        }
        else
        {
            USBH_MSC_ErrorHandle(mscStatus);
        }
        break;

    case USBH_MSC_READ_CAPACITY10:
        mscStatus = USBH_MSC_ReadCapacity10();
        if(mscStatus == USBH_MSC_OK)
        {
            USBH_BOTXfer.MSCState = USBH_MSC_DEFAULT_APP;

            USBH_MSC_Info.Ready = 1;

            status = USBH_OK;
        }
        else
        {
            USBH_MSC_ErrorHandle(mscStatus);
        }
        break;

    case USBH_MSC_MODE_SENSE6:
        /* Issue ModeSense6 SCSI command for detecting if device is write-protected */
        mscStatus = USBH_MSC_ModeSense6();
        if(mscStatus == USBH_MSC_OK)
        {
            USBH_BOTXfer.MSCState = USBH_MSC_DEFAULT_APP;

            status = USBH_OK;
        }
        else
        {
            USBH_MSC_ErrorHandle(mscStatus);
        }
        break;

    case USBH_MSC_DEFAULT_APP:
        /* Process Application callback for MSC */
        appStatus = phost->usr_cb->UserApplication();
        if(appStatus == 1)
        {
            /* De-init requested from application layer */
            status =  USBH_APPLY_DEINIT;
        }
        break;

    case USBH_MSC_BOT_TRANSFER:
        USBH_MSC_BOT_Process(phost);
        break;

    case USBH_MSC_UNRECOVERED_STATE:
        status = USBH_UNRECOVERED_ERROR;
        break;

    case USBH_MSC_REQUEST_SENSE:
        /* Issue RequestSense SCSI command for retrieving error code */
        mscStatus = USBH_MSC_RequestSense();
        if(mscStatus == USBH_MSC_OK)
        {
            USBH_BOTXfer.MSCState = USBH_BOTXfer.MSCStateBkp;

            status = USBH_OK;
        }
        else
        {
            USBH_MSC_ErrorHandle(mscStatus);
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MSC_getMaxLUN()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MSC_getMaxLUN(USBH_Info_t *phost)
{
    phost->Ctrl.setup.bRequestType = USB_REQ_D2H | USB_REQ_CLASS | USB_REQ_TO_INTERFACE;

    phost->Ctrl.setup.bRequest = 0xFE;
    phost->Ctrl.setup.wValue = 0;
    phost->Ctrl.setup.wIndex = 0;
    phost->Ctrl.setup.wLength = 1;

    return USBH_CtrlTransfer(phost, DataInBuffer , 1);
}


/******************************************************************************************************************************************
* 函数名称: USBH_MSC_ErrorHandle()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBH_MSC_ErrorHandle(uint8_t status)
{
    if(status == USBH_MSC_FAIL)
    {
        /* Try MSC level error recovery, Issue the request Sense to get Drive error reason  */
        USBH_BOTXfer.MSCState = USBH_MSC_REQUEST_SENSE;
    }
    else if(status == USBH_MSC_PHASE_ERROR)
    {
        /* Phase error, Go to Unrecovered state */
        USBH_BOTXfer.MSCState = USBH_MSC_UNRECOVERED_STATE;
    }
}
