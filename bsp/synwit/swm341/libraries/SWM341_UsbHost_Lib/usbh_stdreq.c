/******************************************************************************************************************************************
* 文件名称: usbh_stdreq.c
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
#include <string.h>
#include "SWM341.h"
#include "usbh_core.h"
#include "usbh_stdreq.h"


/******************************************************************************************************************************************
* 函数名称: USBH_GetDescriptor()
* 功能说明: 获取描述符
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_GetDescriptor(USBH_Info_t *phost, uint8_t type, uint8_t index, uint8_t *buff, int size)
{
    phost->Ctrl.setup.bRequestType = USB_REQ_D2H | USB_REQ_STANDARD | USB_REQ_TO_DEVICE;
    phost->Ctrl.setup.bRequest = USB_GET_DESCRIPTOR;
    phost->Ctrl.setup.wValue = (type << 8) | index;
    phost->Ctrl.setup.wIndex = (type == USB_DESC_STRING) ? 0x0409 : 0;
    phost->Ctrl.setup.wLength = size;

    return USBH_CtrlTransfer(phost, buff, size);
}


/******************************************************************************************************************************************
* 函数名称: USBH_GetDescriptorEx()
* 功能说明: 获取描述符
* 输    入: uint8_t reqType           USB_REQ_STANDARD、USB_REQ_CLASS、USB_REQ_VENDOR
*           uint8_t reqTarget       USB_REQ_TO_DEVICE、USB_REQ_TO_INTERFACE、USB_REQ_TO_ENDPOINT
*           uint8_t type
*           uint8_t index
*           uint16_t wIndex
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_GetDescriptorEx(USBH_Info_t *phost, uint8_t reqType, uint8_t reqTarget, uint8_t type, uint8_t index, uint16_t wIndex, uint8_t *buff, int size)
{
    phost->Ctrl.setup.bRequestType = USB_REQ_D2H | reqType | reqTarget;
    phost->Ctrl.setup.bRequest = USB_GET_DESCRIPTOR;
    phost->Ctrl.setup.wValue = (type << 8) | index;
    phost->Ctrl.setup.wIndex = wIndex;
    phost->Ctrl.setup.wLength = size;

    return USBH_CtrlTransfer(phost, buff, size);
}


/******************************************************************************************************************************************
* 函数名称: USBH_SetAddress()
* 功能说明: 设置设备地址
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_SetAddress(USBH_Info_t *phost, uint8_t addr)
{
    phost->Ctrl.setup.bRequestType = USB_REQ_H2D | USB_REQ_STANDARD | USB_REQ_TO_DEVICE;
    phost->Ctrl.setup.bRequest = USB_SET_ADDRESS;
    phost->Ctrl.setup.wValue = addr;
    phost->Ctrl.setup.wIndex = 0;
    phost->Ctrl.setup.wLength = 0;

    return USBH_CtrlTransfer(phost, 0, 0);
}


/******************************************************************************************************************************************
* 函数名称: USBH_SetConfiguration()
* 功能说明: 设置 configuration
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_SetConfiguration(USBH_Info_t *phost, uint8_t cfg)
{
    phost->Ctrl.setup.bRequestType = USB_REQ_H2D | USB_REQ_STANDARD | USB_REQ_TO_DEVICE;
    phost->Ctrl.setup.bRequest = USB_SET_CONFIGURATION;
    phost->Ctrl.setup.wValue = cfg;
    phost->Ctrl.setup.wIndex = 0;
    phost->Ctrl.setup.wLength = 0;

    return USBH_CtrlTransfer(phost, 0, 0);
}


/******************************************************************************************************************************************
* 函数名称: USBH_SetInterface()
* 功能说明: 设置 interface altSetting
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_SetInterface(USBH_Info_t *phost, uint8_t intf, uint8_t altSetting)
{
    phost->Ctrl.setup.bRequestType = USB_REQ_H2D | USB_REQ_STANDARD | USB_REQ_TO_INTERFACE;
    phost->Ctrl.setup.bRequest = USB_SET_INTERFACE;
    phost->Ctrl.setup.wValue = altSetting;
    phost->Ctrl.setup.wIndex = intf;
    phost->Ctrl.setup.wLength = 0;

    return USBH_CtrlTransfer(phost, 0, 0);
}


/******************************************************************************************************************************************
* 函数名称: USBH_ClrFeature()
* 功能说明: 清除端点 STALL
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_ClrFeature(USBH_Info_t *phost, uint8_t ep)
{
    phost->Ctrl.setup.bRequestType = USB_REQ_H2D | USB_REQ_STANDARD | USB_REQ_TO_ENDPOINT;
    phost->Ctrl.setup.bRequest = USB_CLEAR_FEATURE;
    phost->Ctrl.setup.wValue = 0x00;
    phost->Ctrl.setup.wIndex = ep;
    phost->Ctrl.setup.wLength = 0;

    return USBH_CtrlTransfer(phost, 0, 0);
}

/******************************************************************************************************************************************
* 函数名称: USBH_ParseCfgDesc()
* 功能说明: 解析配置描述符
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_ParseCfgDesc(USBH_Info_t *phost, uint8_t *buff, uint16_t size)
{
    USB_DescHeader_t *pdesc = (USB_DescHeader_t *)buff;
    uint8_t if_ix, ep_ix;

    memcpy(&phost->Device.Cfg_Desc, pdesc, sizeof(USB_CfgDesc_t));

    if(phost->Device.Cfg_Desc.bNumInterfaces > USBH_MAX_NUM_INTERFACES)
    {
        return USBH_NOT_SUPPORTED;
    }

    while((uint8_t *)pdesc < &buff[size])
    {
        pdesc = (USB_DescHeader_t *)((uint8_t *)pdesc + pdesc->bLength);
        switch(pdesc->bDescriptorType)
        {
        case USB_DESC_INTERFACE:
            if_ix = ((USB_IntfDesc_t *)pdesc)->bInterfaceNumber;
            if(if_ix >= USBH_MAX_NUM_INTERFACES)
            {
                return USBH_NOT_SUPPORTED;
            }

            memcpy(&phost->Device.Intf_Desc[if_ix], pdesc, sizeof(USB_IntfDesc_t));

            if(phost->Device.Intf_Desc[if_ix].bNumEndpoints > USBH_MAX_NUM_ENDPOINTS)
            {
                return USBH_NOT_SUPPORTED;
            }
            ep_ix = 0;
            break;

        case USB_DESC_ENDPOINT:
            memcpy(&phost->Device.Ep_Desc[if_ix][ep_ix], pdesc, sizeof(USB_EpDesc_t));
            if(++ep_ix >= USBH_MAX_NUM_ENDPOINTS)
            {
                return USBH_NOT_SUPPORTED;
            }
            break;

        case USB_DESC_HID:
            memcpy(&phost->Device.HID_Desc[if_ix], pdesc, sizeof(USB_HIDDesc_t));
            break;

        default:
            break;
        }
    }

    return USBH_OK ;
}
