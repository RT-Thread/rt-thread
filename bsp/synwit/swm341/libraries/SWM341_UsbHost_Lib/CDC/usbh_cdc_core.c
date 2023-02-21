/******************************************************************************************************************************************
* 文件名称: usbh_cdc_core.c
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
#include <stdlib.h>
#include <string.h>
#include "SWM341.h"
#include "usbh_core.h"
#include "usbh_stdreq.h"
#include "usbh_cdc_core.h"
#include "usbh_cdc_funct.h"


USBH_Class_cb_t USBH_CDC_cb =
{
    USBH_CDC_Init,
    USBH_CDC_DeInit,
    USBH_CDC_Request,
    USBH_CDC_Process
};


volatile USBH_CDC_Info_t USBH_CDC_Info;


/******************************************************************************************************************************************
* 函数名称: USBH_CDC_Init()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_CDC_Init(USBH_Info_t *phost)
{
    USB_EpDesc_t *pEpIn, *pEpOut, *pEpCtrl;

    if((phost->Device.Dev_Desc.bDeviceClass == USB_CDC_CLASS) &&
       (phost->Device.Intf_Desc[0].bInterfaceClass == USB_CDC_CTRL_CLASS) &&
       (phost->Device.Intf_Desc[1].bInterfaceClass == USB_CDC_DATA_CLASS))
    {
        pEpCtrl = &phost->Device.Ep_Desc[0][0];

        if(phost->Device.Ep_Desc[1][0].bEndpointAddress & USB_EP_IN)
        {
            pEpIn  = &phost->Device.Ep_Desc[1][0];
            pEpOut = &phost->Device.Ep_Desc[1][1];
        }
        else
        {
            pEpIn  = &phost->Device.Ep_Desc[1][1];
            pEpOut = &phost->Device.Ep_Desc[1][0];
        }

        USBH_CDC_Info.InEp       = pEpIn->bEndpointAddress;
        USBH_CDC_Info.InEpSize   = pEpIn->wMaxPacketSize;
        USBH_CDC_Info.OutEp      = pEpOut->bEndpointAddress;
        USBH_CDC_Info.OutEpSize  = pEpOut->wMaxPacketSize;
        USBH_CDC_Info.CtrlEp     = pEpCtrl->bEndpointAddress;
        USBH_CDC_Info.CtrlEpSize = pEpCtrl->wMaxPacketSize;

        USBH_CDC_DeInit(phost);
    }
    else
    {
        if(phost->usr_cb->DeviceNotSupported)
            phost->usr_cb->DeviceNotSupported();

        return USBH_NOT_SUPPORTED;
    }

    return USBH_OK;
}


/******************************************************************************************************************************************
* 函数名称: USBH_CDC_DeInit()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBH_CDC_DeInit(USBH_Info_t *phost)
{
    USBH_CDC_Info.InEpDATAX = 0;
    USBH_CDC_Info.OutEpDATAX = 0;
    USBH_CDC_Info.CtrlEpDATAX = 0;

    USBH_CDC_Info.TxWrPtr = 0;
    USBH_CDC_Info.TxRdPtr = 0;
    USBH_CDC_Info.RxWrPtr = 0;
    USBH_CDC_Info.RxRdPtr = 0;

    USBH_CDC_Info.state = USBH_CDC_SEND;
    USBH_CDC_Info.reqState = CDC_GET_LINE_CODING;
}


/******************************************************************************************************************************************
* 函数名称: USBH_CDC_Request()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_CDC_Request(USBH_Info_t *phost)
{
    USBH_Status status = USBH_BUSY;
    USBH_Status reqStatus;

    switch(USBH_CDC_Info.reqState)
    {
    case CDC_SET_LINE_CODING:
        reqStatus = USBH_CDC_SetLineCoding(phost);
        if(reqStatus == USBH_OK)
        {
            USBH_CDC_Info.reqState = CDC_GET_LINE_CODING ;
        }
        if(reqStatus == USBH_NOT_SUPPORTED)
        {
            USBH_CDC_Info.reqState = CDC_CLR_STALL;
        }
        break;

    case CDC_GET_LINE_CODING:
        reqStatus = USBH_CDC_GetLineCoding(phost);
        if(reqStatus == USBH_OK)
        {
            USBH_CDC_Info.reqState = CDC_SET_CONTROL_LINE;
        }
        break;

    case CDC_SET_CONTROL_LINE:
        reqStatus = USBH_CDC_SetControlLine(phost);
        if(reqStatus == USBH_OK)
        {
            status = USBH_OK;
        }
        break;

    case CDC_CLR_STALL:
        reqStatus = USBH_ClrFeature(phost, 0);
        if(reqStatus == USBH_OK )
        {
            phost->Ctrl.toggle_out = 0;

            USBH_CDC_Info.reqState = CDC_GET_LINE_CODING ;
        }
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_CDC_Process()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_CDC_Process(USBH_Info_t *phost)
{
    static uint32_t FrameNbr = 0;
    static uint32_t size;
    uint32_t available, space;
    USBH_Status status = USBH_OK;
    USBH_Resp resp;

    switch(USBH_CDC_Info.state)
    {
    case USBH_CDC_SEND:
        available = USBH_CDC_Info.TxWrPtr - USBH_CDC_Info.TxRdPtr;
        if((available >= USBH_CDC_Info.OutEpSize) || ((available > 0) && (abs((int)USBH->FRAMENR - (int)USBH_CDC_Info.TxFrameNbr) > 10)))
        {
            USBH_CDC_Info.TxFrameNbr = USBH->FRAMENR;

            size = (available > USBH_CDC_Info.OutEpSize) ? USBH_CDC_Info.OutEpSize : available;

            if(USBH_SendOutPacket(phost->Device.Address, USBH_CDC_Info.OutEp, USBH_CDC_Info.OutEpDATAX, (uint8_t *)&USBH_CDC_Info.TxBuff[USBH_CDC_Info.TxRdPtr], size))
            {
                USBH_CDC_Info.state = USBH_CDC_SEND_WAIT;
            }
        }
        else
        {
            USBH_CDC_Info.state = USBH_CDC_READ;
        }
        break;

    case USBH_CDC_SEND_WAIT:
        resp = USBH_State();
        if(resp != USBR_NO)
        {
            if(resp == USBR_ACK)
            {
                USBH_CDC_Info.OutEpDATAX ^= 1;

                USBH_CDC_Info.TxRdPtr += size;
                if(USBH_CDC_Info.TxRdPtr == USBH_CDC_Info.TxWrPtr)  // USBH_CDC_Info.TxBuff 中数据已全部发出
                {
                    USBH_CDC_Info.TxRdPtr = 0;
                    USBH_CDC_Info.TxWrPtr = 0;
                }
            }

            USBH_CDC_Info.state = USBH_CDC_READ;
        }
        break;

    case USBH_CDC_READ:
        space = USBH_CDC_BUFF_SIZE - USBH_CDC_Info.RxWrPtr;
        if((space >= USBH_CDC_Info.InEpSize) && (abs((int)USBH->FRAMENR - (int)USBH_CDC_Info.TxFrameNbr) > 10))
        {
            USBH_CDC_Info.RxFrameNbr = USBH->FRAMENR;

            if(USBH_SendInPacket(phost->Device.Address, USBH_CDC_Info.InEp, USBH_CDC_Info.InEpDATAX, USBH_CDC_Info.InEpSize))
            {
                USBH_CDC_Info.state = USBH_CDC_READ_WAIT;
            }
        }
        break;

    case USBH_CDC_READ_WAIT:
        resp = USBH_State();
        if(resp != USBR_NO)
        {
            if(resp == USBR_ACK)
            {
                USBH_CDC_Info.InEpDATAX ^= 1;

                size = USBH_ReadRxBuffer((uint8_t *)&USBH_CDC_Info.RxBuff[USBH_CDC_Info.RxWrPtr], USBH_CDC_Info.InEpSize);
                USBH_CDC_Info.RxWrPtr += size;
            }

            USBH_CDC_Info.state = USBH_CDC_SEND;
        }
        break;

    case USBH_CDC_CTRL:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_CDC_Process()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t USBH_CDC_Send(uint8_t *data, uint16_t size)
{
    uint16_t space = USBH_CDC_BUFF_SIZE - USBH_CDC_Info.TxWrPtr;    // 可写入数据个数

    if(space >= size)
    {
        __disable_irq();

        memcpy((uint8_t *)&USBH_CDC_Info.TxBuff[USBH_CDC_Info.TxWrPtr], data, size);
        USBH_CDC_Info.TxWrPtr += size;

        __enable_irq();

        return size;
    }

    return 0;
}


/******************************************************************************************************************************************
* 函数名称: USBH_CDC_Process()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t USBH_CDC_Read(uint8_t *buff, uint16_t size)
{
    uint16_t available = USBH_CDC_Info.RxWrPtr - USBH_CDC_Info.RxRdPtr;

    if(size > available)
        size = available;

    if(size)
    {
        __disable_irq();

        memcpy(buff, (uint8_t *)&USBH_CDC_Info.RxBuff[USBH_CDC_Info.RxRdPtr], size);

        USBH_CDC_Info.RxRdPtr += size;
        if(USBH_CDC_Info.RxRdPtr == USBH_CDC_Info.RxWrPtr)  // USBH_CDC_Info.RxBuff 中数据已全部读出
        {
            USBH_CDC_Info.RxRdPtr = 0;
            USBH_CDC_Info.RxWrPtr = 0;
        }

        __enable_irq();
    }

    return size;
}
