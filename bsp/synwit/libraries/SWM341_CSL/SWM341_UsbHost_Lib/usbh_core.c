/******************************************************************************************************************************************
* 文件名称: usbh_core.c
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


USBH_Info_t USBH_Info;


/******************************************************************************************************************************************
* 函数名称: USBH_Init()
* 功能说明: USB Host 初始化
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBH_Init(USBH_Class_cb_t *class_cb, USBH_User_cb_t *usr_cb)
{
    USBH_HW_Init();

    USBH_DeInit();

    /* Register class and user callbacks */
    USBH_Info.class_cb = class_cb;
    USBH_Info.usr_cb = usr_cb;

    /* Upon Init call usr call back */
    if(USBH_Info.usr_cb->Init)
        USBH_Info.usr_cb->Init();
}


/******************************************************************************************************************************************
* 函数名称: USBH_DeInit()
* 功能说明: USB Host Re-Initialize
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBH_DeInit(void)
{
    USBH->PORTSR = USBH_PORTSR_CONNCHG_Msk |    // 清零标志位
                   USBH_PORTSR_RSTCHG_Msk  |
                   USBH_PORTSR_ENACHG_Msk;

    USBH_Info.State = HOST_IDLE;
    USBH_Info.EnumState = ENUM_GET_DEV_DESC;

    USBH_Info.Ctrl.pksz = 8;

    USBH_Info.Ctrl.toggle_in = 0;
    USBH_Info.Ctrl.toggle_out = 0;

    USBH_Info.Ctrl.state = CTRL_IDLE;

    USBH_Info.Device.Address = 0;
}


/******************************************************************************************************************************************
* 函数名称: USBH_Process()
* 功能说明: USB Host core main state machine process
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBH_Process(void)
{
    static uint32_t frameNbr;
    USBH_Status status = USBH_FAIL;

    if(USBH_Info.State != HOST_IDLE)
    {
        if(!USBH_IsDeviceConnected())
            USBH_Info.State = HOST_DEV_DETACHED;
    }

    switch(USBH_Info.State)
    {
    case HOST_IDLE:
        if(USBH_IsDeviceConnected())
        {
            USBH_Info.State = HOST_DEV_ATTACHED;

            if(USBH_Info.usr_cb->DeviceAttached)
                USBH_Info.usr_cb->DeviceAttached();

            frameNbr = USBH->FRAMENR;
        }
        break;

    case HOST_DEV_ATTACHED:
        if(abs((int)frameNbr - (int)USBH->FRAMENR) > 100)
        {
            USBH_Info.State = HOST_PORT_RESETED;

            USBH_ResetPort();
        }
        break;

    case HOST_PORT_RESETED:
        if(USBH_IsPortEnabled())
        {
            USBH_Info.State = HOST_PORT_ENABLED;

            frameNbr = USBH->FRAMENR;
        }
        break;

    case HOST_PORT_ENABLED:
        if(abs((int)frameNbr - (int)USBH->FRAMENR) > 10)
        {
            USBH_Info.State = HOST_ENUMERATION;

            USBH_Info.Device.Speed = USBH_GetDeviceSpeed();

            if(USBH_Info.usr_cb->DeviceSpeedDetected)
                USBH_Info.usr_cb->DeviceSpeedDetected(USBH_Info.Device.Speed);
        }
        break;

    case HOST_ENUMERATION:
        if(USBH_HandleEnum(&USBH_Info) == USBH_OK)
        {
            USBH_Info.State = HOST_USR_INPUT;

            if(USBH_Info.usr_cb->EnumerationDone)
                USBH_Info.usr_cb->EnumerationDone();
        }
        break;

    case HOST_USR_INPUT:
        /* The function should return user response true to move to class state */
        if(USBH_Info.usr_cb->UserInput())
        {
            if((USBH_Info.class_cb->Init(&USBH_Info)) == USBH_OK)
            {
                USBH_Info.State = HOST_CLASS_REQUEST;
            }
        }
        break;

    case HOST_CLASS_REQUEST:
        /* process class standard control requests state machine */
        status = USBH_Info.class_cb->Request(&USBH_Info);
        if(status == USBH_OK)
        {
            USBH_Info.State = HOST_CLASS;
        }
        else
        {
            USBH_ErrorHandle(&USBH_Info, status);
        }
        break;

    case HOST_CLASS:
        /* process class state machine */
        status = USBH_Info.class_cb->Process(&USBH_Info);
        USBH_ErrorHandle(&USBH_Info, status);
        break;

    case HOST_CTRL_XFER:
        /* process control transfer state machine */
        USBH_HandleControl(&USBH_Info);
        break;

    case HOST_DEV_DETACHED:
        if(USBH_Info.usr_cb->DeviceDisconnected)
            USBH_Info.usr_cb->DeviceDisconnected();

        /* Re-Initialize Host for new Enumeration */
        USBH_DeInit();
        if(USBH_Info.usr_cb->DeInit)
            USBH_Info.usr_cb->DeInit();
        USBH_Info.class_cb->DeInit(&USBH_Info);

        USBH_Info.State = HOST_IDLE;
        break;

    default :
        break;
    }
}


uint8_t  USBH_Cfg_Desc_Buffer[USBH_MAX_CFG_SIZE];
uint16_t USBH_Cfg_Desc_Length;
/******************************************************************************************************************************************
* 函数名称: USBH_HandleEnum()
* 功能说明: Handle the USB device enumeration state machine
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_HandleEnum(USBH_Info_t *phost)
{
    USBH_Status status = USBH_BUSY;

    switch(phost->EnumState)
    {
    case ENUM_GET_DEV_DESC:
        if(USBH_GetDescriptor(phost, USB_DESC_DEVICE, 0, (uint8_t *)&phost->Device.Dev_Desc, 8) == USBH_OK)
        {
            phost->EnumState = ENUM_GET_FULL_DEV_DESC;

            phost->Ctrl.pksz = phost->Device.Dev_Desc.bMaxPacketSize;
        }
        break;

    case ENUM_GET_FULL_DEV_DESC:
        if(USBH_GetDescriptor(phost, USB_DESC_DEVICE, 0, (uint8_t *)&phost->Device.Dev_Desc, sizeof(USB_DevDesc_t)) == USBH_OK)
        {
            phost->EnumState = ENUM_SET_ADDR;

            if(phost->usr_cb->DeviceDescAvailable)
                phost->usr_cb->DeviceDescAvailable(&phost->Device.Dev_Desc);
        }
        break;

    case ENUM_SET_ADDR:
        if(USBH_SetAddress(phost, USBH_DEVICE_ADDRESS) == USBH_OK)
        {
            phost->EnumState = ENUM_GET_CFG_DESC;

            phost->Device.Address = USBH_DEVICE_ADDRESS;

            if(phost->usr_cb->DeviceAddressAssigned)
                phost->usr_cb->DeviceAddressAssigned();
        }
        break;

    case ENUM_GET_CFG_DESC:
        if(USBH_GetDescriptor(phost, USB_DESC_CONFIG, 0, (uint8_t *)&phost->Device.Cfg_Desc, sizeof(USB_CfgDesc_t)) == USBH_OK)
        {
            if(phost->Device.Cfg_Desc.wTotalLength <= USBH_MAX_CFG_SIZE)
            {
                phost->EnumState = ENUM_GET_FULL_CFG_DESC;
            }
            else
            {
                status = USBH_NOT_SUPPORTED;
            }
        }
        break;

    case ENUM_GET_FULL_CFG_DESC:
        if(USBH_GetDescriptor(phost, USB_DESC_CONFIG, 0, USBH_Cfg_Desc_Buffer, phost->Device.Cfg_Desc.wTotalLength) == USBH_OK)
        {
            phost->EnumState = ENUM_GET_VENDOR_STRING_DESC;

            USBH_Cfg_Desc_Length = phost->Device.Cfg_Desc.wTotalLength;
            USBH_ParseCfgDesc(phost, USBH_Cfg_Desc_Buffer, USBH_Cfg_Desc_Length);

            if(phost->usr_cb->ConfigDescAvailable)
                phost->usr_cb->ConfigDescAvailable(&phost->Device.Cfg_Desc, phost->Device.Intf_Desc, phost->Device.Ep_Desc[0]);
        }
        break;

    case ENUM_GET_VENDOR_STRING_DESC:
        if(phost->Device.Dev_Desc.iManufacturer != 0)
        {
            USBH_Status stat = USBH_GetDescriptor(phost, USB_DESC_STRING, phost->Device.Dev_Desc.iManufacturer, (uint8_t *)phost->Device.strVender, sizeof(phost->Device.strVender));
            if(stat == USBH_OK)
            {
                phost->EnumState = ENUM_GET_PRODUCT_STRING_DESC;

                if(phost->usr_cb->VendorString)
                    phost->usr_cb->VendorString(phost->Device.strVender);
            }
            else if(stat == USBH_NOT_SUPPORTED)
            {
                phost->EnumState = ENUM_GET_PRODUCT_STRING_DESC;
            }
        }
        else
        {
            phost->EnumState = ENUM_GET_PRODUCT_STRING_DESC;
        }
        break;

    case ENUM_GET_PRODUCT_STRING_DESC:
        if(phost->Device.Dev_Desc.iProduct != 0)
        {
            USBH_Status stat = USBH_GetDescriptor(phost, USB_DESC_STRING, phost->Device.Dev_Desc.iProduct, (uint8_t *)phost->Device.strProduct, sizeof(phost->Device.strProduct));
            if(stat == USBH_OK)
            {
                phost->EnumState = ENUM_GET_SERIALNUM_STRING_DESC;

                if(phost->usr_cb->ProductString)
                    phost->usr_cb->ProductString(phost->Device.strProduct);
            }
            else if(stat == USBH_NOT_SUPPORTED)
            {
                phost->EnumState = ENUM_GET_SERIALNUM_STRING_DESC;
            }
        }
        else
        {
            phost->EnumState = ENUM_GET_SERIALNUM_STRING_DESC;
        }
        break;

    case ENUM_GET_SERIALNUM_STRING_DESC:
        if(phost->Device.Dev_Desc.iSerialNumber != 0)
        {
            USBH_Status stat = USBH_GetDescriptor(phost, USB_DESC_STRING, phost->Device.Dev_Desc.iSerialNumber, (uint8_t *)phost->Device.strSerialNumber, sizeof(phost->Device.strSerialNumber));
            if(stat == USBH_OK)
            {
                phost->EnumState = ENUM_SET_CONFIGURATION;

                if(phost->usr_cb->SerialNumString)
                    phost->usr_cb->SerialNumString(phost->Device.strSerialNumber);
            }
            else if(stat == USBH_NOT_SUPPORTED)
            {
                phost->EnumState = ENUM_SET_CONFIGURATION;
            }
        }
        else
        {
            phost->EnumState = ENUM_SET_CONFIGURATION;
        }
        break;

    case ENUM_SET_CONFIGURATION:
        if(USBH_SetConfiguration(phost, phost->Device.Cfg_Desc.bConfigurationValue) == USBH_OK)
        {
            phost->EnumState = ENUM_DEV_CONFIGURED;
        }
        break;

    case ENUM_DEV_CONFIGURED:
        status = USBH_OK;
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_HandleControl()
* 功能说明: Handle the USB control transfer state machine
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBH_HandleControl(USBH_Info_t *phost)
{
    static uint32_t size;
    uint32_t real_size;
    USBH_Resp resp;

    switch(phost->Ctrl.state)
    {
    case CTRL_SETUP:
        if(USBH_SendSetupPacket(phost->Device.Address, (uint8_t *)&phost->Ctrl.setup, 8))
        {
            phost->Ctrl.state = CTRL_SETUP_WAIT;
        }
        break;

    case CTRL_SETUP_WAIT:
        resp = USBH_State();
        if(resp == USBR_ACK)
        {
            phost->Ctrl.toggle_in = 1;
            phost->Ctrl.toggle_out = 1;

            if(phost->Ctrl.setup.wLength != 0)
            {
                if(phost->Ctrl.setup.bRequestType & USB_EP_IN)
                {
                    phost->Ctrl.state = CTRL_DATA_IN;
                }
                else
                {
                    phost->Ctrl.state = CTRL_DATA_OUT;
                }
            }
            else    // No Data Stage
            {
                if(phost->Ctrl.setup.bRequestType & USB_EP_IN)
                {
                    phost->Ctrl.state = CTRL_STATUS_OUT;
                }
                else
                {
                    phost->Ctrl.state = CTRL_STATUS_IN;
                }
            }
        }
        else if(resp == USBR_ERROR)
        {
            phost->Ctrl.state = CTRL_SETUP;         // retry
        }
        break;

    case CTRL_DATA_IN:
        size = (phost->Ctrl.size > phost->Ctrl.pksz) ? phost->Ctrl.pksz : phost->Ctrl.size;
        if(USBH_SendInPacket(phost->Device.Address, 0, phost->Ctrl.toggle_in, size))
        {
            phost->Ctrl.state = CTRL_DATA_IN_WAIT;
        }
        break;

    case CTRL_DATA_IN_WAIT:
        resp = USBH_State();
        if(resp == USBR_ACK)
        {
            phost->Ctrl.toggle_in ^= 1;

            real_size = USBH_ReadRxBuffer(phost->Ctrl.buff, size);
            if(real_size < size)
            {
                phost->Ctrl.state = CTRL_STATUS_OUT;
            }
            else
            {
                phost->Ctrl.size -= size;
                phost->Ctrl.buff += size;

                if(phost->Ctrl.size)
                {
                    phost->Ctrl.state = CTRL_DATA_IN;
                }
                else
                {
                    phost->Ctrl.state = CTRL_STATUS_OUT;
                }
            }
        }
        else if(resp == USBR_NAK)
        {
            phost->Ctrl.state = CTRL_DATA_IN;       // retry
        }
        else if(resp == USBR_STALL)
        {
            phost->Ctrl.state = CTRL_STALLED;
            phost->State = phost->StateBkp;
        }
        else if(resp == USBR_ERROR)
        {
            phost->Ctrl.state = CTRL_ERROR;
            phost->State = phost->StateBkp;
        }
        break;

    case CTRL_DATA_OUT:
        size = (phost->Ctrl.size > phost->Ctrl.pksz) ? phost->Ctrl.pksz : phost->Ctrl.size;
        if(USBH_SendOutPacket(phost->Device.Address, 0, phost->Ctrl.toggle_out, phost->Ctrl.buff, size))
        {
            phost->Ctrl.state = CTRL_DATA_OUT_WAIT;
        }
        break;

    case CTRL_DATA_OUT_WAIT:
        resp = USBH_State();
        if(resp == USBR_ACK)
        {
            phost->Ctrl.toggle_out ^= 1;

            phost->Ctrl.size -= size;
            phost->Ctrl.buff += size;

            if(phost->Ctrl.size)
            {
                phost->Ctrl.state = CTRL_DATA_OUT;
            }
            else
            {
                phost->Ctrl.state = CTRL_STATUS_IN;
            }
        }
        else if(resp == USBR_NAK)
        {
            phost->Ctrl.state = CTRL_DATA_OUT;      // retry
        }
        else if(resp == USBR_STALL)
        {
            phost->Ctrl.state = CTRL_STALLED;
            phost->State = phost->StateBkp;
        }
        else if(resp == USBR_ERROR)
        {
            phost->Ctrl.state = CTRL_ERROR;
            phost->State = phost->StateBkp;
        }
        break;

    case CTRL_STATUS_IN:
        if(USBH_SendInPacket(phost->Device.Address, 0, phost->Ctrl.toggle_in, 0))
        {
            phost->Ctrl.state = CTRL_STATUS_IN_WAIT;
        }
        break;

    case CTRL_STATUS_IN_WAIT:
        resp = USBH_State();
        if(resp == USBR_ACK)
        {
            phost->Ctrl.toggle_in ^= 1;

            phost->Ctrl.state = CTRL_COMPLETE;
            phost->State = phost->StateBkp;
        }
        else if(resp == USBR_NAK)
        {
            phost->Ctrl.state = CTRL_STATUS_IN;     // retry
        }
        else if(resp == USBR_STALL)
        {
            phost->Ctrl.state = CTRL_STALLED;
            phost->State = phost->StateBkp;
        }
        else if(resp == USBR_ERROR)
        {
            phost->Ctrl.state = CTRL_ERROR;
            phost->State = phost->StateBkp;
        }
        break;

    case CTRL_STATUS_OUT:
        if(USBH_SendOutPacket(phost->Device.Address, 0, phost->Ctrl.toggle_out, 0, 0))
        {
            phost->Ctrl.state = CTRL_STATUS_OUT_WAIT;
        }
        break;

    case CTRL_STATUS_OUT_WAIT:
        resp = USBH_State();
        if(resp == USBR_ACK)
        {
            phost->Ctrl.toggle_out ^= 1;

            phost->Ctrl.state = CTRL_COMPLETE;
            phost->State = phost->StateBkp;
        }
        else if(resp == USBR_NAK)
        {
            phost->Ctrl.state = CTRL_STATUS_OUT;    // retry
        }
        else if(resp == USBR_STALL)
        {
            phost->Ctrl.state = CTRL_STALLED;
            phost->State = phost->StateBkp;
        }
        else if(resp == USBR_ERROR)
        {
            phost->Ctrl.state = CTRL_ERROR;
            phost->State = phost->StateBkp;
        }
        break;

    default:
        break;
    }
}


/******************************************************************************************************************************************
* 函数名称: USBH_CtrlTransfer()
* 功能说明: 控制传输
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_CtrlTransfer(USBH_Info_t *phost, uint8_t *buff, uint16_t size)
{
    USBH_Status status = USBH_BUSY;

    if(phost->Ctrl.state == CTRL_IDLE)
    {
        phost->Ctrl.buff = buff;
        phost->Ctrl.size = size;
        phost->Ctrl.state = CTRL_SETUP;

        phost->StateBkp = phost->State;
        phost->State = HOST_CTRL_XFER;
    }
    else
    {
        switch(phost->Ctrl.state)
        {
        case CTRL_COMPLETE:     // Commands successfully sent and Response Received
            status = USBH_OK;
            phost->Ctrl.state = CTRL_IDLE;
            break;

        case CTRL_STALLED:
            status = USBH_NOT_SUPPORTED;
            phost->Ctrl.state = CTRL_IDLE;
            break;

        case CTRL_ERROR:
            status = USBH_FAIL;
            phost->Ctrl.state = CTRL_IDLE;
            break;

        default:
            break;
        }
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_ErrorHandle()
* 功能说明: Handles the Error on Host side.
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBH_ErrorHandle(USBH_Info_t *phost, USBH_Status errType)
{
    if(errType == USBH_UNRECOVERED_ERROR)
    {
        if(phost->usr_cb->UnrecoveredError)
            phost->usr_cb->UnrecoveredError();

        goto restart;
    }
    else if(errType == USBH_APPLY_DEINIT)   // USB host restart requested from application layer
    {
        phost->usr_cb->Init();

        goto restart;
    }

    return;

restart:
    /* Re-Initialize Host for new Enumeration */
    USBH_DeInit();
    USBH_Info.usr_cb->DeInit();
    USBH_Info.class_cb->DeInit(&USBH_Info);
}

