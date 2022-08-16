/******************************************************************************************************************************************
* 文件名称: usbh_hid_core.c
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
#include "usbh_hid_core.h"
#include "usbh_hid_keybd.h"
#include "usbh_hid_mouse.h"


USBH_Class_cb_t USBH_HID_cb =
{
    USBH_HID_Init,
    USBH_HID_DeInit,
    USBH_HID_Request,
    USBH_HID_Process,
};


volatile USBH_HID_Info_t USBH_HID_Info;


static uint8_t DataInBuffer[64];


/******************************************************************************************************************************************
* 函数名称: USBH_HID_Init()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_HID_Init(USBH_Info_t *phost)
{
    USB_EpDesc_t *pEpIn, *pEpOut;

    if(phost->Device.Intf_Desc[0].bInterfaceClass == USB_HID_CLASS)
    {
        if(phost->Device.Intf_Desc[0].bInterfaceProtocol == USB_HID_KEYBD)
        {
            USBH_HID_Info.hid_cb = &USBH_HID_KeyBD_cb;
        }
        else if(phost->Device.Intf_Desc[0].bInterfaceProtocol == USB_HID_MOUSE)
        {
            USBH_HID_Info.hid_cb = &USBH_HID_Mouse_cb;
        }

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

        USBH_HID_Info.InEp          = pEpIn->bEndpointAddress;
        USBH_HID_Info.InEpSize      = pEpIn->wMaxPacketSize;
        USBH_HID_Info.InEpInterval  = pEpIn->bInterval;
        USBH_HID_Info.OutEp         = pEpOut->bEndpointAddress;
        USBH_HID_Info.OutEpSize     = pEpOut->wMaxPacketSize;
        USBH_HID_Info.OutEpInterval = pEpOut->bInterval;

        USBH_HID_DeInit(phost);
    }
    else
    {
        if(phost->usr_cb->DeviceNotSupported)
            phost->usr_cb->DeviceNotSupported();
    }

    return USBH_OK;
}


/******************************************************************************************************************************************
* 函数名称: USBH_HID_DeInit()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBH_HID_DeInit(USBH_Info_t *phost)
{
    USBH_HID_Info.InEpDATAX     = 0;
    USBH_HID_Info.InEpFrameNbr  = 0;
    USBH_HID_Info.OutEpDATAX    = 0;
    USBH_HID_Info.OutEpFrameNbr = 0;

    USBH_HID_Info.state = USBH_HID_IDLE;
    USBH_HID_Info.reqState = USBH_HID_REQ_GET_REPORT_DESC;
}


/******************************************************************************************************************************************
* 函数名称: USBH_HID_Request()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_HID_Request(USBH_Info_t *phost)
{
    USBH_Status status    = USBH_BUSY;
    USBH_Status reqStatus = USBH_BUSY;

    switch(USBH_HID_Info.reqState)
    {
    case USBH_HID_REQ_GET_REPORT_DESC:
        reqStatus = USBH_GetDescriptorEx(phost, USB_REQ_STANDARD, USB_REQ_TO_INTERFACE, USB_DESC_HID_RPT, 0, 0, phost->Device.HIDReport_Desc[0], phost->Device.HID_Desc[0].wItemLength);
        if(reqStatus == USBH_OK)
        {
            USBH_HID_Info.reqState = USBH_HID_REQ_SET_IDLE;
        }
        break;

    case USBH_HID_REQ_SET_IDLE:
        reqStatus = USBH_Set_Idle(phost, 0, 0, 0);
        if(reqStatus == USBH_OK)
        {
            status = USBH_OK;
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_HID_Process()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_HID_Process(USBH_Info_t *phost)
{
    USBH_Status status = USBH_OK;
    USBH_Resp resp;

    switch(USBH_HID_Info.state)
    {
    case USBH_HID_IDLE:
        USBH_HID_Info.hid_cb->Init();
        USBH_HID_Info.state = USBH_HID_SYNC;

        USBH->IF = USBH_IF_SOF_Msk;
        break;

    case USBH_HID_SYNC:
        if(USBH->IF & USBH_IF_SOF_Msk)
        {
            USBH_HID_Info.state = USBH_HID_READ;
        }
        break;

    case USBH_HID_READ:
        if((USBH->FRAMENR + 65536 - USBH_HID_Info.InEpFrameNbr) % 65536 >= USBH_HID_Info.InEpInterval)
        {
            if(USBH_SendInPacket(phost->Device.Address, USBH_HID_Info.InEp, USBH_HID_Info.InEpDATAX, USBH_HID_Info.InEpSize))
            {
                USBH_HID_Info.InEpFrameNbr = USBH->FRAMENR;

                USBH_HID_Info.state = USBH_HID_READ_WAIT;
            }
        }
        break;

    case USBH_HID_READ_WAIT:
        resp = USBH_State();
        if(resp == USBR_ACK)
        {
            USBH_HID_Info.InEpDATAX ^= 1;

            USBH_ReadRxBuffer(DataInBuffer, USBH_HID_Info.InEpSize);
            USBH_HID_Info.hid_cb->Decode(DataInBuffer);

            USBH_HID_Info.state = USBH_HID_READ;
        }
        else if(resp == USBR_NAK)
        {
            USBH_HID_Info.state = USBH_HID_READ;
        }
        else if(resp == USBR_STALL)
        {
            USBH_HID_Info.state = USBH_HID_STALL_IN;
        }
        else if(resp == USBR_ERROR)
        {
            USBH_HID_Info.state = USBH_HID_READ;
        }
        break;

    case USBH_HID_STALL_IN:
        status = USBH_ClrFeature(phost, USBH_HID_Info.InEp);
        if(status == USBH_OK)
        {
            USBH_HID_Info.InEpDATAX = 0;

            USBH_HID_Info.state = USBH_HID_READ;
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_Set_Idle()
* 功能说明:
* 输    入: uint8_t interface
*           uint8_t reportID    Targeted report ID for Set Idle request
*           uint8_t duration    Duration for HID Idle request, 单位 4ms
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_Set_Idle(USBH_Info_t *phost, uint8_t interface, uint8_t reportId, uint8_t duration)
{
    phost->Ctrl.setup.bRequestType = USB_REQ_H2D | USB_REQ_CLASS | USB_REQ_TO_INTERFACE;
    phost->Ctrl.setup.bRequest = USB_HID_SET_IDLE;
    phost->Ctrl.setup.wValue = (duration << 8 ) | reportId;
    phost->Ctrl.setup.wIndex = interface;
    phost->Ctrl.setup.wLength = 0;

    return USBH_CtrlTransfer(phost, 0, 0);
}


/******************************************************************************************************************************************
* 函数名称: USBH_Set_Report()
* 功能说明:
* 输    入: uint8_t interface
*           uint8_t reportId    Targeted report ID for Set Report request
*           uint8_t reportType  1 Input，2 Output，3 Feature
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_Set_Report(USBH_Info_t *phost, uint8_t interface, uint8_t reportId, uint8_t reportType, uint8_t * reportData, uint16_t reportLen)
{
    phost->Ctrl.setup.bRequestType = USB_REQ_H2D | USB_REQ_CLASS | USB_REQ_TO_INTERFACE;
    phost->Ctrl.setup.bRequest = USB_HID_SET_REPORT;
    phost->Ctrl.setup.wValue = (reportType << 8 ) | reportId;
    phost->Ctrl.setup.wIndex = interface;
    phost->Ctrl.setup.wLength = reportLen;

    return USBH_CtrlTransfer(phost, reportData, reportLen);
}


/******************************************************************************************************************************************
* 函数名称: USBH_Set_Protocol()
* 功能说明:
* 输    入: uint8_t interface
*           uint8_t protocol    0 = Boot Protocol, 1 = Report Protocol
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_Set_Protocol(USBH_Info_t *phost, uint8_t interface, uint8_t protocol)
{
    phost->Ctrl.setup.bRequestType = USB_REQ_H2D | USB_REQ_CLASS | USB_REQ_TO_INTERFACE;
    phost->Ctrl.setup.bRequest = USB_HID_SET_PROTOCOL;
    phost->Ctrl.setup.wValue = protocol;
    phost->Ctrl.setup.wIndex = interface;
    phost->Ctrl.setup.wLength = 0;

    return USBH_CtrlTransfer(phost, 0, 0);
}
