/******************************************************************************************************************************************
* 文件名称: usbh_mtp.c
* 功能说明: This file is the MTP Layer Handlers for USB Host MTP class.
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
#include "usbh_mtp.h"


static USBH_Status USBH_MTP_Init(USBH_Info_t *phost);
static void        USBH_MTP_DeInit(USBH_Info_t *phost);
static USBH_Status USBH_MTP_Request(USBH_Info_t *phost);
static USBH_Status USBH_MTP_Process(USBH_Info_t *phost);

USBH_Class_cb_t USBH_MTP_cb =
{
    USBH_MTP_Init,
    USBH_MTP_DeInit,
    USBH_MTP_Request,
    USBH_MTP_Process,
};


USBH_MTP_Info_t USBH_MTP_Info;


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_Init()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
static USBH_Status USBH_MTP_Init(USBH_Info_t *phost)
{
    USB_EpDesc_t *pEpIn, *pEpOut, *pEpNotify;

    for(int i = 0; i < phost->Device.Cfg_Desc.bNumInterfaces; i++)
    {
        if(((phost->Device.Intf_Desc[i].bInterfaceClass == USB_MTP_CLASS) && (phost->Device.Intf_Desc[i].bNumEndpoints == 3)) ||
           ((phost->Device.Intf_Desc[i].bInterfaceClass == 0xFF)          && (phost->Device.Intf_Desc[i].bNumEndpoints == 3)))
        {
#define EpVerify(ep, dir, type)  (((phost->Device.Ep_Desc[i][ep].bEndpointAddress & USB_EP_IN) == dir) && \
                                  ((phost->Device.Ep_Desc[i][ep].bmAttributes & USB_EP_INT) == type))
            if(EpVerify(0, USB_EP_IN, USB_EP_INT) && EpVerify(1, USB_EP_IN, USB_EP_BULK) && EpVerify(2, USB_EP_OUT, USB_EP_BULK))
            {
                pEpNotify = &phost->Device.Ep_Desc[i][0];
                pEpIn     = &phost->Device.Ep_Desc[i][1];
                pEpOut    = &phost->Device.Ep_Desc[i][2];
            }
            else if(EpVerify(0, USB_EP_IN, USB_EP_INT) && EpVerify(2, USB_EP_IN, USB_EP_BULK) && EpVerify(1, USB_EP_OUT, USB_EP_BULK))
            {
                pEpNotify = &phost->Device.Ep_Desc[i][0];
                pEpIn     = &phost->Device.Ep_Desc[i][2];
                pEpOut    = &phost->Device.Ep_Desc[i][1];
            }
            else if(EpVerify(1, USB_EP_IN, USB_EP_INT) && EpVerify(0, USB_EP_IN, USB_EP_BULK) && EpVerify(2, USB_EP_OUT, USB_EP_BULK))
            {
                pEpNotify = &phost->Device.Ep_Desc[i][1];
                pEpIn     = &phost->Device.Ep_Desc[i][0];
                pEpOut    = &phost->Device.Ep_Desc[i][2];
            }
            else if(EpVerify(1, USB_EP_IN, USB_EP_INT) && EpVerify(2, USB_EP_IN, USB_EP_BULK) && EpVerify(0, USB_EP_OUT, USB_EP_BULK))
            {
                pEpNotify = &phost->Device.Ep_Desc[i][1];
                pEpIn     = &phost->Device.Ep_Desc[i][2];
                pEpOut    = &phost->Device.Ep_Desc[i][0];
            }
            else if(EpVerify(2, USB_EP_IN, USB_EP_INT) && EpVerify(0, USB_EP_IN, USB_EP_BULK) && EpVerify(1, USB_EP_OUT, USB_EP_BULK))
            {
                pEpNotify = &phost->Device.Ep_Desc[i][2];
                pEpIn     = &phost->Device.Ep_Desc[i][0];
                pEpOut    = &phost->Device.Ep_Desc[i][1];
            }
            else if(EpVerify(2, USB_EP_IN, USB_EP_INT) && EpVerify(1, USB_EP_IN, USB_EP_BULK) && EpVerify(0, USB_EP_OUT, USB_EP_BULK))
            {
                pEpNotify = &phost->Device.Ep_Desc[i][2];
                pEpIn     = &phost->Device.Ep_Desc[i][1];
                pEpOut    = &phost->Device.Ep_Desc[i][0];
            }
            else
            {
                continue;
            }

            USBH_MTP_Info.InEp         = pEpIn->bEndpointAddress;
            USBH_MTP_Info.InEpSize     = pEpIn->wMaxPacketSize;
            USBH_MTP_Info.OutEp        = pEpOut->bEndpointAddress;
            USBH_MTP_Info.OutEpSize    = pEpOut->wMaxPacketSize;
            USBH_MTP_Info.NotifyEp     = pEpNotify->bEndpointAddress;
            USBH_MTP_Info.NotifyEpSize = pEpNotify->wMaxPacketSize;

            USBH_MTP_Info.events.poll  = pEpNotify->bInterval;

            SW_LOG_INFO("InEp: %x, InEpSize: %d", pEpIn->bEndpointAddress, pEpIn->wMaxPacketSize);
            SW_LOG_INFO("OutEp: %x, OutEpSize: %d", pEpOut->bEndpointAddress, pEpOut->wMaxPacketSize);
            SW_LOG_INFO("NotifyEp: %x, NotifyEpSize: %d, NotifyInterval: %d", pEpNotify->bEndpointAddress, pEpNotify->wMaxPacketSize, pEpNotify->bInterval);

            USBH_MTP_DeInit(phost);

            return USBH_OK;
        }
        else
        {
            continue;
        }
    }

    if(phost->usr_cb->DeviceNotSupported)
        phost->usr_cb->DeviceNotSupported();

    return USBH_NOT_SUPPORTED;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_DeInit()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
static void USBH_MTP_DeInit(USBH_Info_t *phost)
{
    USBH_MTP_Info.is_ready = 0;

    USBH_MTP_Info.InEpDATAX = 0;
    USBH_MTP_Info.OutEpDATAX = 0;
    USBH_MTP_Info.NotifyEpDATAX = 0;

    USBH_MTP_Info.XferState = USBH_MTP_XFER_IDLE;
    USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;

    USBH_MTP_Info.state = USBH_MTP_GETDEVICEINFO;
    USBH_MTP_Info.stateReq = USBH_MTP_IDLE;

    SW_LOG_INFO("USBH_MTP_DeInit");
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_Request()
* 功能说明: Used for handling Standard requests for MTP class.
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
static USBH_Status USBH_MTP_Request(USBH_Info_t *phost)
{
    return USBH_OK;
}


void USBH_MTP_XferProcess(USBH_Info_t *phost);
/******************************************************************************************************************************************
* 函数名称: USBH_MTP_Process()
* 功能说明: Used for managing state machine for MTP data transfers.
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
static USBH_Status USBH_MTP_Process(USBH_Info_t *phost)
{
    USBH_Resp resp;
    USBH_Status status = USBH_BUSY;

    if((USBH_MTP_Info.state != USBH_MTP_EVENT_WAIT) &&
       (USBH_MTP_Info.state != USBH_MTP_EVENT_CHECK))
    {
        if(USBH_MTP_Info.stateReq != USBH_MTP_IDLE)
        {
            USBH_MTP_Info.stateBkp = USBH_MTP_Info.state;
            USBH_MTP_Info.state = USBH_MTP_Info.stateReq;

            USBH_MTP_Info.stateReq = USBH_MTP_IDLE;
        }
    }

    switch(USBH_MTP_Info.state)
    {
    case USBH_MTP_GETDEVICEINFO:
        status = USBH_MTP_GetDeviceInfo(phost, &USBH_MTP_Info.devinfo);
        if(status == USBH_OK)
        {
            SW_LOG_INFO("MTP Device Information");
            SW_LOG_INFO("  Standard version : %x", USBH_MTP_Info.devinfo.StandardVersion);
            SW_LOG_INFO("  Vendor ExtID : %s",     USBH_MTP_Info.devinfo.VendorExtensionID == 6 ? "MTP" : "NOT SUPPORTED");
            SW_LOG_INFO("  Functional mode : %s",  USBH_MTP_Info.devinfo.FunctionalMode == 0 ? "Standard" : "Vendor");
            SW_LOG_INFO("  Number of Supported Operation(s) : %d", USBH_MTP_Info.devinfo.OperationsSupportedNbr);
            SW_LOG_INFO("  Number of Supported Events(s) : %d",    USBH_MTP_Info.devinfo.EventsSupportedNbr);
            SW_LOG_INFO("  Number of Supported Proprieties : %d",  USBH_MTP_Info.devinfo.DevicePropertiesSupportedNbr);
            SW_LOG_INFO("  Manufacturer : %s",   USBH_MTP_Info.devinfo.Manufacturer);
            SW_LOG_INFO("  Model : %s",          USBH_MTP_Info.devinfo.Model);
            SW_LOG_INFO("  Device version : %s", USBH_MTP_Info.devinfo.DeviceVersion);
            SW_LOG_INFO("  Serial number : %s",  USBH_MTP_Info.devinfo.SerialNumber);

            USBH_MTP_Info.state = USBH_MTP_OPENSESSION;
        }
        break;

    case USBH_MTP_OPENSESSION:
        status = USBH_MTP_OpenSession(phost, 1);
        if(status == USBH_OK)
        {
            SW_LOG_INFO("MTP Session #1 Opened");

            USBH_MTP_Info.state = USBH_MTP_GETSTORAGEIDS;
        }
        break;

    case USBH_MTP_GETSTORAGEIDS:
        status = USBH_MTP_GetStorageIds(phost, &USBH_MTP_Info.storids);
        if(status == USBH_OK)
        {
            SW_LOG_INFO("Number of storage ID items : %d", USBH_MTP_Info.storids.n);
            for(int i  = 0; i < USBH_MTP_Info.storids.n; i++)
            {
                SW_LOG_INFO("storage#%d ID : %x", i, USBH_MTP_Info.storids.Storage[i]);
            }

            USBH_MTP_Info.CurrentStorage = 0;
            if(USBH_MTP_Info.storids.n)
                USBH_MTP_Info.state = USBH_MTP_GETSTORAGEINFO;
        }
        break;

    case USBH_MTP_GETSTORAGEINFO:
        status = USBH_MTP_GetStorageInfo(phost, USBH_MTP_Info.storids.Storage[USBH_MTP_Info.CurrentStorage],
                                               &USBH_MTP_Info.storinfo[USBH_MTP_Info.CurrentStorage]);
        if(status == USBH_OK)
        {
            SW_LOG_INFO("Volume#%u: %s   [%s]", USBH_MTP_Info.CurrentStorage, USBH_MTP_Info.storinfo[USBH_MTP_Info.CurrentStorage].StorageDescription,
                                                                                 USBH_MTP_Info.storinfo[USBH_MTP_Info.CurrentStorage].VolumeLabel);
            USBH_MTP_Info.is_ready = 1;
            USBH_MTP_Info.state = USBH_MTP_IDLE;
        }
        break;

    case USBH_MTP_IDLE:
        if(abs((int)USBH->FRAMENR - (int)USBH_MTP_Info.events.timer) >= USBH_MTP_Info.events.poll)
        {
            USBH_MTP_Info.events.timer = USBH->FRAMENR;

            USBH_MTP_Info.state = USBH_MTP_EVENT;
        }
        else
        {
            status = USBH_OK;
        }
        break;

    case USBH_MTP_EVENT_CHECK:
        if(abs((int)USBH->FRAMENR - (int)USBH_MTP_Info.events.timer) >= USBH_MTP_Info.events.poll)
        {
            USBH_MTP_Info.events.timer = USBH->FRAMENR;

            USBH_MTP_Info.state = USBH_MTP_EVENT;
        }
        else
        {
            USBH_MTP_Info.state = USBH_MTP_TRANSFER;    // Event 查询是在数据传输中间插入的，返回数据传输
        }
        break;

    case USBH_MTP_EVENT:
        if(USBH_SendInPacket(phost->Device.Address, USBH_MTP_Info.NotifyEp, USBH_MTP_Info.NotifyEpDATAX, USBH_MTP_Info.NotifyEpSize))
        {
            USBH_MTP_Info.state = USBH_MTP_EVENT_WAIT;
        }
        break;

    case USBH_MTP_EVENT_WAIT:
        resp = USBH_State();
        if(resp == USBR_ACK)
        {
            USBH_MTP_Info.NotifyEpDATAX ^= 1;

            USBH_ReadRxBuffer((uint8_t *)&USBH_MTP_Info.events.container, USBH_MTP_Info.NotifyEpSize);

            USBH_MTP_EventsCallback(phost, USBH_MTP_Info.events.container.code, USBH_MTP_Info.events.container.param1);
        }

        if((USBH_MTP_Info.XferState == USBH_MTP_XFER_DATA_OUT) ||
           (USBH_MTP_Info.XferState == USBH_MTP_XFER_DATA_IN))
        {
            USBH_MTP_Info.state = USBH_MTP_TRANSFER;    // Event 查询是在数据传输中间插入的，返回数据传输
        }
        else
        {
            USBH_MTP_Info.state = USBH_MTP_IDLE;
        }
        break;

    case USBH_MTP_TRANSFER:
        USBH_MTP_XferProcess(phost);
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_XferProcess()
* 功能说明:
* 输    入: USBH_Info_t *phost
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBH_MTP_XferProcess(USBH_Info_t *phost)
{
    USBH_Resp resp;
    uint32_t size;

    USBH_MTP_Info.XferStatus = USBH_BUSY;

    switch(USBH_MTP_Info.XferState)
    {
    case USBH_MTP_XFER_OP_REQ:
        if(USBH_SendOutPacket(phost->Device.Address, USBH_MTP_Info.OutEp, USBH_MTP_Info.OutEpDATAX, (uint8_t *)&USBH_MTP_Info.op_container, USBH_MTP_Info.op_container.length))
        {
            USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ_WAIT;
        }
        break;

    case USBH_MTP_XFER_OP_REQ_WAIT:
        resp = USBH_State();
        if(resp == USBR_ACK)
        {
            USBH_MTP_Info.OutEpDATAX ^= 1;

            if(USBH_MTP_Info.flags == PTP_DP_NODATA)
            {
                USBH_MTP_Info.XferState = USBH_MTP_XFER_RESP;
            }
            else if(USBH_MTP_Info.flags == PTP_DP_SENDDATA)
            {
                USBH_MTP_Info.XferState = USBH_MTP_XFER_DATA_OUT;
            }
            else if(USBH_MTP_Info.flags == PTP_DP_GETDATA)
            {
                USBH_MTP_Info.XferState = USBH_MTP_XFER_DATA_IN;
            }
        }
        else if(resp == USBR_NAK)
        {
            USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;     // Resend Request
        }
        else if(resp == USBR_STALL)
        {
            USBH_MTP_Info.XferState = USBH_MTP_XFER_ERROR;
        }
        break;

    case USBH_MTP_XFER_DATA_OUT:
        size = USBH_MTP_Info.data_len > USBH_MTP_Info.OutEpSize ? USBH_MTP_Info.OutEpSize : USBH_MTP_Info.data_len;
        if(USBH_SendOutPacket(phost->Device.Address, USBH_MTP_Info.OutEp, USBH_MTP_Info.OutEpDATAX, USBH_MTP_Info.data_ptr, size))
        {
            USBH_MTP_Info.XferState  = USBH_MTP_XFER_DATA_OUT_WAIT;
        }
        break;

    case USBH_MTP_XFER_DATA_OUT_WAIT:
        resp = USBH_State();
        if(resp == USBR_ACK)
        {
            USBH_MTP_Info.OutEpDATAX ^= 1;

            if(USBH_MTP_Info.data_len > USBH_MTP_Info.OutEpSize)
            {
                USBH_MTP_Info.data_ptr += USBH_MTP_Info.OutEpSize;
                USBH_MTP_Info.data_len -= USBH_MTP_Info.OutEpSize;
            }
            else
            {
                USBH_MTP_Info.data_len = 0;
            }

            if(USBH_MTP_Info.data_len > 0)
            {
                USBH_MTP_Info.XferState = USBH_MTP_XFER_DATA_OUT;
            }
            else
            {
                USBH_MTP_Info.XferState = USBH_MTP_XFER_RESP;
            }
        }
        else if(resp == USBR_NAK)
        {
            USBH_MTP_Info.XferState = USBH_MTP_XFER_DATA_OUT;       // Resend same data

            USBH_MTP_Info.state = USBH_MTP_EVENT_CHECK;     // 从机返回 NAK 时，主机查询一下是否需要执行 Event 查询
        }
        else if(resp == USBR_STALL)
        {
            USBH_MTP_Info.XferState = USBH_MTP_XFER_ERROR;
        }
        break;

    case USBH_MTP_XFER_DATA_IN:
        if(USBH_SendInPacket(phost->Device.Address, USBH_MTP_Info.InEp, USBH_MTP_Info.InEpDATAX, USBH_MTP_Info.InEpSize))
        {
            USBH_MTP_Info.XferState  = USBH_MTP_XFER_DATA_IN_WAIT;
        }
        break;

    case USBH_MTP_XFER_DATA_IN_WAIT:
        resp = USBH_State();
        if(resp == USBR_ACK)
        {
            USBH_MTP_Info.InEpDATAX ^= 1;

            uint32_t len = USBH_ReadRxBuffer(USBH_MTP_Info.data_ptr, USBH_MTP_Info.InEpSize);

            if(USBH_MTP_Info.first_packet)
            {
                USBH_MTP_Info.data_len = *(uint32_t *)(void *)USBH_MTP_Info.data_ptr;

                if(USBH_MTP_Info.first_packet == 3)
                {
                    len -= PTP_USB_BULK_HDR_LEN;
                    USBH_MTP_Info.data_len -= PTP_USB_BULK_HDR_LEN;
                    memcpy(USBH_MTP_Info.data_ptr, USBH_MTP_Info.data_ptr + PTP_USB_BULK_HDR_LEN, len);
                }

                USBH_MTP_Info.first_packet = 0;
            }

            USBH_MTP_Info.data_ptr += len;
            USBH_MTP_Info.data_len -= len;

            if((USBH_MTP_Info.data_len > 0) || (len == USBH_MTP_Info.InEpSize))
            {
                USBH_MTP_Info.XferState = USBH_MTP_XFER_DATA_IN;
            }
            else
            {
                USBH_MTP_Info.XferState = USBH_MTP_XFER_RESP;
            }
        }
        else if(resp == USBR_NAK)
        {
            USBH_MTP_Info.XferState = USBH_MTP_XFER_DATA_IN;

            USBH_MTP_Info.state = USBH_MTP_EVENT_CHECK;     // 从机返回 NAK 时，主机查询一下是否需要执行 Event 查询
        }
        else if(resp == USBR_STALL)
        {
            USBH_MTP_Info.XferState = USBH_MTP_XFER_ERROR;
        }
        break;

    case USBH_MTP_XFER_RESP:
        if(USBH_SendInPacket(phost->Device.Address, USBH_MTP_Info.InEp, USBH_MTP_Info.InEpDATAX, USBH_MTP_Info.InEpSize))
        {
            USBH_MTP_Info.XferState = USBH_MTP_XFER_RESP_WAIT;
        }
        break;

    case USBH_MTP_XFER_RESP_WAIT:
        resp = USBH_State();
        if(resp == USBR_ACK)
        {
            USBH_MTP_Info.InEpDATAX ^= 1;

            USBH_ReadRxBuffer((uint8_t *)&USBH_MTP_Info.resp_container, USBH_MTP_Info.InEpSize);

            if(USBH_MTP_Info.resp_container.code == PTP_RC_OK)
            {
                USBH_MTP_Info.XferStatus = USBH_OK;
            }
            else
            {
                USBH_MTP_Info.XferStatus = USBH_FAIL;
            }
            USBH_MTP_Info.state = USBH_MTP_Info.stateBkp;
        }
        else if(resp == USBR_NAK)
        {
            USBH_MTP_Info.XferState = USBH_MTP_XFER_RESP;
        }
        else if(resp == USBR_STALL)
        {
            USBH_MTP_Info.XferState = USBH_MTP_XFER_ERROR;
        }
        break;

    case USBH_MTP_XFER_ERROR:
        USBH_MTP_Info.XferStatus = USBH_FAIL;
        USBH_MTP_Info.state = USBH_MTP_Info.stateBkp;
        break;

    default:
        break;
    }
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_GetDeviceInfo()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MTP_GetDeviceInfo(USBH_Info_t *phost, PTP_DeviceInfo_t *dev_info)
{
    USBH_Status status = USBH_BUSY;

    switch(USBH_MTP_Info.OpState)
    {
    case USBH_MTP_OP_SEND:
        /* Set operation request type */
        USBH_MTP_Info.flags = PTP_DP_GETDATA;
        USBH_MTP_Info.data_ptr = (uint8_t *)(void *)&USBH_MTP_Info.data_container;
        USBH_MTP_Info.data_len = 0;
        USBH_MTP_Info.first_packet = 1;

        /* Fill operation request params */
        USBH_MTP_Info.op_container.type = PTP_USB_CONTAINER_COMMAND;
        USBH_MTP_Info.op_container.code = PTP_OC_GetDeviceInfo;
        USBH_MTP_Info.op_container.trans_id = USBH_MTP_Info.transaction_id++;
        USBH_MTP_Info.op_container.length = PTP_USB_BULK_HDR_LEN + sizeof(uint32_t) * 0;

        /* Setup State machine and start transfer */
        USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;
        USBH_MTP_Info.OpState = USBH_MTP_OP_WAIT;

        USBH_MTP_Info.stateReq = USBH_MTP_TRANSFER;
        break;

    case USBH_MTP_OP_WAIT:
        if(USBH_MTP_Info.XferStatus != USBH_BUSY)
        {
            status = USBH_MTP_Info.XferStatus;
            USBH_MTP_Info.XferStatus = USBH_BUSY;

            USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;
        }
        if(status == USBH_OK)
        {
            PTP_DecodeDeviceInfo(phost, dev_info);
        }
        break;

    default:
        break;
    }
    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_OpenSession()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MTP_OpenSession(USBH_Info_t *phost, uint32_t session)
{
    USBH_Status status = USBH_BUSY;

    switch(USBH_MTP_Info.OpState)
    {
    case USBH_MTP_OP_SEND:
        /* Init session params */
        USBH_MTP_Info.transaction_id = 0x00000000U;
        USBH_MTP_Info.session_id = session;
        USBH_MTP_Info.flags = PTP_DP_NODATA;

        /* Fill operation request params */
        USBH_MTP_Info.op_container.type = PTP_USB_CONTAINER_COMMAND;
        USBH_MTP_Info.op_container.code = PTP_OC_OpenSession;
        USBH_MTP_Info.op_container.trans_id = USBH_MTP_Info.transaction_id++;
        USBH_MTP_Info.op_container.param1 = session;
        USBH_MTP_Info.op_container.length = PTP_USB_BULK_HDR_LEN + sizeof(uint32_t) * 1;

        /* Setup State machine and start transfer */
        USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;
        USBH_MTP_Info.OpState = USBH_MTP_OP_WAIT;

        USBH_MTP_Info.stateReq = USBH_MTP_TRANSFER;
        break;

    case USBH_MTP_OP_WAIT:
        if(USBH_MTP_Info.XferStatus != USBH_BUSY)
        {
            status = USBH_MTP_Info.XferStatus;
            USBH_MTP_Info.XferStatus = USBH_BUSY;

            USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_GetStorageIds()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MTP_GetStorageIds(USBH_Info_t *phost, PTP_StorageIDs_t *storage_ids)
{
    USBH_Status status = USBH_BUSY;

    switch(USBH_MTP_Info.OpState)
    {
    case USBH_MTP_OP_SEND:
        /* Set operation request type */
        USBH_MTP_Info.flags = PTP_DP_GETDATA;
        USBH_MTP_Info.data_ptr = (uint8_t *)(void *)&USBH_MTP_Info.data_container;
        USBH_MTP_Info.data_len = 0;
        USBH_MTP_Info.first_packet = 1;

        /* Fill operation request params */
        USBH_MTP_Info.op_container.type = PTP_USB_CONTAINER_COMMAND;
        USBH_MTP_Info.op_container.code = PTP_OC_GetStorageIDs;
        USBH_MTP_Info.op_container.trans_id = USBH_MTP_Info.transaction_id++;
        USBH_MTP_Info.op_container.length = PTP_USB_BULK_HDR_LEN + sizeof(uint32_t) * 0;

        /* Setup State machine and start transfer */
        USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;
        USBH_MTP_Info.OpState = USBH_MTP_OP_WAIT;

        USBH_MTP_Info.stateReq = USBH_MTP_TRANSFER;
        break;

    case USBH_MTP_OP_WAIT:
        if(USBH_MTP_Info.XferStatus != USBH_BUSY)
        {
            status = USBH_MTP_Info.XferStatus;
            USBH_MTP_Info.XferStatus = USBH_BUSY;

            USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;
        }
        if(status == USBH_OK)
        {
            storage_ids->n = PTP_GetArray32(storage_ids->Storage, USBH_MTP_Info.data_container.payload, 0U);
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_GetStorageInfo()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MTP_GetStorageInfo(USBH_Info_t *phost, uint32_t storage_id, PTP_StorageInfo_t *storage_info)
{
    USBH_Status status = USBH_BUSY;

    switch(USBH_MTP_Info.OpState)
    {
    case USBH_MTP_OP_SEND:
        /* Set operation request type */
        USBH_MTP_Info.flags = PTP_DP_GETDATA;
        USBH_MTP_Info.data_ptr = (uint8_t *)(void *)&USBH_MTP_Info.data_container;
        USBH_MTP_Info.data_len = 0;
        USBH_MTP_Info.first_packet = 1;

        /* Fill operation request params */
        USBH_MTP_Info.op_container.type = PTP_USB_CONTAINER_COMMAND;
        USBH_MTP_Info.op_container.code = PTP_OC_GetStorageInfo;
        USBH_MTP_Info.op_container.trans_id = USBH_MTP_Info.transaction_id++;
        USBH_MTP_Info.op_container.param1 = storage_id;
        USBH_MTP_Info.op_container.length = PTP_USB_BULK_HDR_LEN + sizeof(uint32_t) * 1;

        /* Setup State machine and start transfer */
        USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;
        USBH_MTP_Info.OpState = USBH_MTP_OP_WAIT;

        USBH_MTP_Info.stateReq = USBH_MTP_TRANSFER;
        break;

    case USBH_MTP_OP_WAIT:
        if(USBH_MTP_Info.XferStatus != USBH_BUSY)
        {
            status = USBH_MTP_Info.XferStatus;
            USBH_MTP_Info.XferStatus = USBH_BUSY;

            USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;
        }
        if(status == USBH_OK)
        {
            PTP_DecodeStorageInfo(phost, storage_info);
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_GetNumObjects()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MTP_GetNumObjects(USBH_Info_t *phost, uint32_t storage_id, uint32_t format, uint32_t folder, uint32_t *numobs)
{
    USBH_Status status = USBH_BUSY;

    switch(USBH_MTP_Info.OpState)
    {
    case USBH_MTP_OP_SEND:
        /* Set operation request type */
        USBH_MTP_Info.flags = PTP_DP_NODATA;

        /* Fill operation request params */
        USBH_MTP_Info.op_container.type = PTP_USB_CONTAINER_COMMAND;
        USBH_MTP_Info.op_container.code = PTP_OC_GetNumObjects;
        USBH_MTP_Info.op_container.trans_id = USBH_MTP_Info.transaction_id++;
        USBH_MTP_Info.op_container.param1 = storage_id;
        USBH_MTP_Info.op_container.param2 = format;
        USBH_MTP_Info.op_container.param3 = folder;
        USBH_MTP_Info.op_container.length = PTP_USB_BULK_HDR_LEN + sizeof(uint32_t) * 3;

        /* Setup State machine and start transfer */
        USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;
        USBH_MTP_Info.OpState = USBH_MTP_OP_WAIT;

        USBH_MTP_Info.stateReq = USBH_MTP_TRANSFER;
        break;

    case USBH_MTP_OP_WAIT:
        if(USBH_MTP_Info.XferStatus != USBH_BUSY)
        {
            status = USBH_MTP_Info.XferStatus;
            USBH_MTP_Info.XferStatus = USBH_BUSY;

            USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;
        }
        if(status == USBH_OK)
        {
            *numobs = USBH_MTP_Info.resp_container.param1;
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_GetObjectHandles()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MTP_GetObjectHandles(USBH_Info_t *phost, uint32_t storage_id, uint32_t format, uint32_t folder, PTP_ObjectHandles_t *handles)
{
    USBH_Status status = USBH_BUSY;

    switch(USBH_MTP_Info.OpState)
    {
    case USBH_MTP_OP_SEND:
        /* Set operation request type */
        USBH_MTP_Info.flags = PTP_DP_GETDATA;
        USBH_MTP_Info.data_ptr = (uint8_t *)(void *)&USBH_MTP_Info.data_container;
        USBH_MTP_Info.data_len = 0;
        USBH_MTP_Info.first_packet = 1;

        /* Fill operation request params */
        USBH_MTP_Info.op_container.type = PTP_USB_CONTAINER_COMMAND;
        USBH_MTP_Info.op_container.code = PTP_OC_GetObjectHandles;
        USBH_MTP_Info.op_container.trans_id = USBH_MTP_Info.transaction_id++;
        USBH_MTP_Info.op_container.param1 = storage_id;
        USBH_MTP_Info.op_container.param2 = format;
        USBH_MTP_Info.op_container.param3 = folder;
        USBH_MTP_Info.op_container.length = PTP_USB_BULK_HDR_LEN + sizeof(uint32_t) * 3;

        /* Setup State machine and start transfer */
        USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;
        USBH_MTP_Info.OpState = USBH_MTP_OP_WAIT;

        USBH_MTP_Info.stateReq = USBH_MTP_TRANSFER;
        break;

    case USBH_MTP_OP_WAIT:
        if(USBH_MTP_Info.XferStatus != USBH_BUSY)
        {
            status = USBH_MTP_Info.XferStatus;
            USBH_MTP_Info.XferStatus = USBH_BUSY;

            USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;
        }
        if(status == USBH_OK)
        {
            handles->n = PTP_GetArray32(handles->Handler, USBH_MTP_Info.data_container.payload, 0U);
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_GetObjectInfo()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MTP_GetObjectInfo(USBH_Info_t *phost, uint32_t handle, PTP_ObjectInfo_t *object_info)
{
    USBH_Status status = USBH_BUSY;

    switch(USBH_MTP_Info.OpState)
    {
    case USBH_MTP_OP_SEND:
        /* Set operation request type */
        USBH_MTP_Info.flags = PTP_DP_GETDATA;
        USBH_MTP_Info.data_ptr = (uint8_t *)(void *)&USBH_MTP_Info.data_container;
        USBH_MTP_Info.data_len = 0;
        USBH_MTP_Info.first_packet = 1;

        /* Fill operation request params */
        USBH_MTP_Info.op_container.type = PTP_USB_CONTAINER_COMMAND;
        USBH_MTP_Info.op_container.code = PTP_OC_GetObjectInfo;
        USBH_MTP_Info.op_container.trans_id = USBH_MTP_Info.transaction_id++;
        USBH_MTP_Info.op_container.param1 = handle;
        USBH_MTP_Info.op_container.length = PTP_USB_BULK_HDR_LEN + sizeof(uint32_t) * 1;

        /* Setup State machine and start transfer */
        USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;
        USBH_MTP_Info.OpState = USBH_MTP_OP_WAIT;

        USBH_MTP_Info.stateReq = USBH_MTP_TRANSFER;
        break;

    case USBH_MTP_OP_WAIT:
        if(USBH_MTP_Info.XferStatus != USBH_BUSY)
        {
            status = USBH_MTP_Info.XferStatus;
            USBH_MTP_Info.XferStatus = USBH_BUSY;

            USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;
        }
        if(status == USBH_OK)
        {
            PTP_DecodeObjectInfo(phost, object_info);
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_GetObject()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MTP_GetObject(USBH_Info_t *phost, uint32_t handle, uint8_t *object)
{
    USBH_Status status = USBH_BUSY;

    switch(USBH_MTP_Info.OpState)
    {
    case USBH_MTP_OP_SEND:
        /* Set operation request type */
        USBH_MTP_Info.flags = PTP_DP_GETDATA;
        USBH_MTP_Info.data_ptr = object;
        USBH_MTP_Info.data_len = 0;
        USBH_MTP_Info.first_packet = 3;

        /* Fill operation request params */
        USBH_MTP_Info.op_container.type = PTP_USB_CONTAINER_COMMAND;
        USBH_MTP_Info.op_container.code = PTP_OC_GetObject;
        USBH_MTP_Info.op_container.trans_id = USBH_MTP_Info.transaction_id++;
        USBH_MTP_Info.op_container.param1 = handle;
        USBH_MTP_Info.op_container.length = PTP_USB_BULK_HDR_LEN + sizeof(uint32_t) * 1;

        /* Setup State machine and start transfer */
        USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;
        USBH_MTP_Info.OpState = USBH_MTP_OP_WAIT;

        USBH_MTP_Info.stateReq = USBH_MTP_TRANSFER;
        break;

    case USBH_MTP_OP_WAIT:
        if(USBH_MTP_Info.XferStatus != USBH_BUSY)
        {
            status = USBH_MTP_Info.XferStatus;
            USBH_MTP_Info.XferStatus = USBH_BUSY;

            USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_GetPartialObject()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MTP_GetPartialObject(USBH_Info_t *phost, uint32_t handle, uint32_t offset, uint32_t maxbytes, uint8_t *object, uint32_t *len)
{
    USBH_Status status = USBH_BUSY;

    switch(USBH_MTP_Info.OpState)
    {
    case USBH_MTP_OP_SEND:
        /* Set operation request type */
        USBH_MTP_Info.flags = PTP_DP_GETDATA;
        USBH_MTP_Info.data_ptr = object;
        USBH_MTP_Info.data_len = 0;
        USBH_MTP_Info.first_packet = 3;

        /* Fill operation request params */
        USBH_MTP_Info.op_container.type = PTP_USB_CONTAINER_COMMAND;
        USBH_MTP_Info.op_container.code = PTP_OC_GetPartialObject;
        USBH_MTP_Info.op_container.trans_id = USBH_MTP_Info.transaction_id++;
        USBH_MTP_Info.op_container.param1 = handle;
        USBH_MTP_Info.op_container.param2 = offset;
        USBH_MTP_Info.op_container.param3 = maxbytes;
        USBH_MTP_Info.op_container.length = PTP_USB_BULK_HDR_LEN + sizeof(uint32_t) * 3;

        /* Setup State machine and start transfer */
        USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;
        USBH_MTP_Info.OpState = USBH_MTP_OP_WAIT;

        USBH_MTP_Info.stateReq = USBH_MTP_TRANSFER;
        break;

    case USBH_MTP_OP_WAIT:
        if(USBH_MTP_Info.XferStatus != USBH_BUSY)
        {
            status = USBH_MTP_Info.XferStatus;
            USBH_MTP_Info.XferStatus = USBH_BUSY;

            USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;
        }
        if(status == USBH_OK)
        {
            *len = USBH_MTP_Info.resp_container.param1;
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_DeleteObject()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MTP_DeleteObject(USBH_Info_t *phost, uint32_t handle, uint32_t format)
{
    USBH_Status status = USBH_BUSY;

    switch(USBH_MTP_Info.OpState)
    {
    case USBH_MTP_OP_SEND:
        /* Set operation request type */
        USBH_MTP_Info.flags = PTP_DP_NODATA;

        /* Fill operation request params */
        USBH_MTP_Info.op_container.type = PTP_USB_CONTAINER_COMMAND;
        USBH_MTP_Info.op_container.code = PTP_OC_DeleteObject;
        USBH_MTP_Info.op_container.trans_id = USBH_MTP_Info.transaction_id++;
        USBH_MTP_Info.op_container.param1 = handle;
        USBH_MTP_Info.op_container.param2 = format;
        USBH_MTP_Info.op_container.length = PTP_USB_BULK_HDR_LEN + sizeof(uint32_t) * 2;

        /* Setup State machine and start transfer */
        USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;
        USBH_MTP_Info.OpState = USBH_MTP_OP_WAIT;

        USBH_MTP_Info.stateReq = USBH_MTP_TRANSFER;
        break;

    case USBH_MTP_OP_WAIT:
        if(USBH_MTP_Info.XferStatus != USBH_BUSY)
        {
            status = USBH_MTP_Info.XferStatus;
            USBH_MTP_Info.XferStatus = USBH_BUSY;

            USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_SendObject()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MTP_SendObject(USBH_Info_t *phost, uint32_t handle, uint8_t *object, uint32_t size)
{
    USBH_Status status = USBH_BUSY;

    switch(USBH_MTP_Info.OpState)
    {
    case USBH_MTP_OP_SEND:
        /* Set operation request type */
        USBH_MTP_Info.flags = PTP_DP_SENDDATA;
        USBH_MTP_Info.data_ptr = (uint8_t *)(void *)&USBH_MTP_Info.data_container;
        USBH_MTP_Info.data_len = size + PTP_USB_BULK_HDR_LEN;
        USBH_MTP_Info.first_packet = 1;

        /* Fill operation request params */
        USBH_MTP_Info.op_container.type = PTP_USB_CONTAINER_COMMAND;
        USBH_MTP_Info.op_container.code = PTP_OC_SendObject;
        USBH_MTP_Info.op_container.trans_id = USBH_MTP_Info.transaction_id++;
        USBH_MTP_Info.op_container.length = PTP_USB_BULK_HDR_LEN + sizeof(uint32_t) * 0;

        /* Fill data_container */
        USBH_MTP_Info.data_container.length = USBH_MTP_Info.data_len;
        USBH_MTP_Info.data_container.type = PTP_USB_CONTAINER_DATA;
        USBH_MTP_Info.data_container.code = USBH_MTP_Info.op_container.code;
        USBH_MTP_Info.data_container.trans_id = USBH_MTP_Info.op_container.trans_id;
        memcpy(USBH_MTP_Info.data_container.payload, object, size);

        /* Setup State machine and start transfer */
        USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;
        USBH_MTP_Info.OpState = USBH_MTP_OP_WAIT;

        USBH_MTP_Info.stateReq = USBH_MTP_TRANSFER;
        break;

    case USBH_MTP_OP_WAIT:
        if(USBH_MTP_Info.XferStatus != USBH_BUSY)
        {
            status = USBH_MTP_Info.XferStatus;
            USBH_MTP_Info.XferStatus = USBH_BUSY;

            USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_GetDevicePropDesc()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MTP_GetDevicePropDesc(USBH_Info_t *phost, uint16_t propcode, PTP_DevicePropDesc_t *devicepropertydesc)
{
    USBH_Status status = USBH_BUSY;

    switch(USBH_MTP_Info.OpState)
    {
    case USBH_MTP_OP_SEND:
        /* Set operation request type */
        USBH_MTP_Info.flags = PTP_DP_GETDATA;
        USBH_MTP_Info.data_ptr = (uint8_t *)(void *)&USBH_MTP_Info.data_container;
        USBH_MTP_Info.data_len = 0;
        USBH_MTP_Info.first_packet = 1;

        /* Fill operation request params */
        USBH_MTP_Info.op_container.type = PTP_USB_CONTAINER_COMMAND;
        USBH_MTP_Info.op_container.code = PTP_OC_GetDevicePropDesc;
        USBH_MTP_Info.op_container.trans_id = USBH_MTP_Info.transaction_id++;
        USBH_MTP_Info.op_container.param1 = propcode;
        USBH_MTP_Info.op_container.length = PTP_USB_BULK_HDR_LEN + sizeof(uint32_t) * 1;

        /* Setup State machine and start transfer */
        USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;
        USBH_MTP_Info.OpState = USBH_MTP_OP_WAIT;

        USBH_MTP_Info.stateReq = USBH_MTP_TRANSFER;
        break;

    case USBH_MTP_OP_WAIT:
        if(USBH_MTP_Info.XferStatus != USBH_BUSY)
        {
            status = USBH_MTP_Info.XferStatus;
            USBH_MTP_Info.XferStatus = USBH_BUSY;

            USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;
        }
        if(status == USBH_OK)
        {
            uint8_t *data = USBH_MTP_Info.data_container.payload;

            devicepropertydesc->DevicePropertyCode = PTP_LE16(&data[PTP_dpd_DevicePropertyCode]);
            devicepropertydesc->DataType = PTP_LE16(&data[PTP_dpd_DataType]);
            devicepropertydesc->GetSet = *(uint8_t *)(&data[PTP_dpd_GetSet]);
            devicepropertydesc->FormFlag = PTP_DPFF_None;
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_GetObjectPropsSupported()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MTP_GetObjectPropsSupported(USBH_Info_t *phost, uint16_t ofc, uint32_t *propnum, uint16_t *props)
{
    USBH_Status status = USBH_BUSY;

    switch(USBH_MTP_Info.OpState)
    {
    case USBH_MTP_OP_SEND:
        /* Set operation request type */
        USBH_MTP_Info.flags = PTP_DP_GETDATA;
        USBH_MTP_Info.data_ptr = (uint8_t *)(void *)&USBH_MTP_Info.data_container;
        USBH_MTP_Info.data_len = 0;
        USBH_MTP_Info.first_packet = 1;

        /* Fill operation request params */
        USBH_MTP_Info.op_container.type = PTP_USB_CONTAINER_COMMAND;
        USBH_MTP_Info.op_container.code = PTP_OC_GetObjectPropsSupported;
        USBH_MTP_Info.op_container.trans_id = USBH_MTP_Info.transaction_id++;
        USBH_MTP_Info.op_container.param1 = ofc;
        USBH_MTP_Info.op_container.length = PTP_USB_BULK_HDR_LEN + sizeof(uint32_t) * 1;

        /* Setup State machine and start transfer */
        USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;
        USBH_MTP_Info.OpState = USBH_MTP_OP_WAIT;

        USBH_MTP_Info.stateReq = USBH_MTP_TRANSFER;
        break;

    case USBH_MTP_OP_WAIT:
        if(USBH_MTP_Info.XferStatus != USBH_BUSY)
        {
            status = USBH_MTP_Info.XferStatus;
            USBH_MTP_Info.XferStatus = USBH_BUSY;

            USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;
        }
        if(status == USBH_OK)
        {
            *propnum = PTP_GetArray16(props, USBH_MTP_Info.data_container.payload, 0U);
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_GetObjectPropDesc()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MTP_GetObjectPropDesc(USBH_Info_t *phost, uint16_t opc, uint16_t ofc, PTP_ObjectPropDesc_t *opd)
{
    USBH_Status status = USBH_BUSY;

    switch(USBH_MTP_Info.OpState)
    {
    case USBH_MTP_OP_SEND:
        /* Set operation request type */
        USBH_MTP_Info.flags = PTP_DP_GETDATA;
        USBH_MTP_Info.data_ptr = (uint8_t *)(void *)&USBH_MTP_Info.data_container;
        USBH_MTP_Info.data_len = 0;
        USBH_MTP_Info.first_packet = 1;

        /* Fill operation request params */
        USBH_MTP_Info.op_container.type = PTP_USB_CONTAINER_COMMAND;
        USBH_MTP_Info.op_container.code = PTP_OC_GetObjectPropDesc;
        USBH_MTP_Info.op_container.trans_id = USBH_MTP_Info.transaction_id++;
        USBH_MTP_Info.op_container.param1 = opc;
        USBH_MTP_Info.op_container.param2 = ofc;
        USBH_MTP_Info.op_container.length = PTP_USB_BULK_HDR_LEN + sizeof(uint32_t) * 2;

        /* Setup State machine and start transfer */
        USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;
        USBH_MTP_Info.OpState = USBH_MTP_OP_WAIT;

        USBH_MTP_Info.stateReq = USBH_MTP_TRANSFER;
        break;

    case USBH_MTP_OP_WAIT:
        if(USBH_MTP_Info.XferStatus != USBH_BUSY)
        {
            status = USBH_MTP_Info.XferStatus;
            USBH_MTP_Info.XferStatus = USBH_BUSY;

            USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;
        }
        if(status == USBH_OK)
        {
            PTP_DecodeObjectPropDesc(phost, opd, USBH_MTP_Info.data_len);
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_GetObjectPropList()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_Status USBH_MTP_GetObjectPropList(USBH_Info_t *phost, uint32_t handle, MTP_Properties_t *pprops, uint32_t *nrofprops)
{
    USBH_Status status = USBH_BUSY;

    switch(USBH_MTP_Info.OpState)
    {
    case USBH_MTP_OP_SEND:
        /* Set operation request type */
        USBH_MTP_Info.flags = PTP_DP_GETDATA;
        USBH_MTP_Info.data_ptr = (uint8_t *)(void *)&USBH_MTP_Info.data_container;
        USBH_MTP_Info.data_len = 0;
        USBH_MTP_Info.first_packet = 1;

        /* Fill operation request params */
        USBH_MTP_Info.op_container.type = PTP_USB_CONTAINER_COMMAND;
        USBH_MTP_Info.op_container.code = PTP_OC_GetObjPropList;
        USBH_MTP_Info.op_container.trans_id = USBH_MTP_Info.transaction_id++;
        USBH_MTP_Info.op_container.param1 = handle;
        USBH_MTP_Info.op_container.param2 = 0x00000000U;  /* 0x00000000U should be "all formats" */
        USBH_MTP_Info.op_container.param3 = 0xFFFFFFFFU;  /* 0xFFFFFFFFU should be "all properties" */
        USBH_MTP_Info.op_container.param4 = 0x00000000U;
        USBH_MTP_Info.op_container.param5 = 0xFFFFFFFFU;  /* Return full tree below the Param1 handle */
        USBH_MTP_Info.op_container.length = PTP_USB_BULK_HDR_LEN + sizeof(uint32_t) * 5;

        /* Setup State machine and start transfer */
        USBH_MTP_Info.XferState = USBH_MTP_XFER_OP_REQ;
        USBH_MTP_Info.OpState = USBH_MTP_OP_WAIT;

        USBH_MTP_Info.stateReq = USBH_MTP_TRANSFER;
        break;

    case USBH_MTP_OP_WAIT:
        if(USBH_MTP_Info.XferStatus != USBH_BUSY)
        {
            status = USBH_MTP_Info.XferStatus;
            USBH_MTP_Info.XferStatus = USBH_BUSY;

            USBH_MTP_Info.OpState = USBH_MTP_OP_SEND;
        }
        if(status == USBH_OK)
        {
            PTP_DecodeObjectPropList(phost, pprops, USBH_MTP_Info.data_len);
        }
        break;

    default:
        break;
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MTP_EventsCallback()
* 功能说明: The function informs that host has received an event
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
__attribute__((weak)) void USBH_MTP_EventsCallback(USBH_Info_t *phost, uint32_t event, uint32_t param)
{
}
