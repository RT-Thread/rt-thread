/******************************************************************************************************************************************
* 文件名称: usbh_msc_bot.c
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


#define MSC_CBW_SIGNATURE   0x43425355
#define MSC_CBW_TAG         0x20304050
#define MSC_CSW_SIGNATURE   0x53425355
#define MSC_CBW_LENGTH      31
#define MSC_CSW_LENGTH      13


USBH_CBWPkt_t USBH_CBWData;
USBH_CSWPkt_t USBH_CSWData;


static uint32_t BOT_StallCount;
static uint32_t BOT_ErrorCount;


/******************************************************************************************************************************************
* 函数名称: USBH_MSC_BOT_Init()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBH_MSC_BOT_Init(void)
{
    USBH_CBWData.CBWSignature = MSC_CBW_SIGNATURE;
    USBH_CBWData.CBWTag = MSC_CBW_TAG;
    USBH_CBWData.CBWLUN = 0;

    BOT_StallCount = 0;
    BOT_ErrorCount = 0;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MSC_BOT_Process()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBH_MSC_BOT_Process(USBH_Info_t *phost)
{
    static uint32_t remLen;     // remaining length
    static uint8_t *pdBuff;
    USBH_Status stat;
    USBH_Resp resp;
    uint32_t size;

    switch(USBH_BOTXfer.BOTState)
    {
    case USBH_MSC_BOT_CBW:
        if(USBH_SendOutPacket(phost->Device.Address, USBH_MSC_Info.OutEp, USBH_MSC_Info.OutEpDATAX, (uint8_t *)&USBH_CBWData, MSC_CBW_LENGTH))
        {
            USBH_BOTXfer.BOTStateBkp = USBH_BOTXfer.BOTState;
            USBH_BOTXfer.BOTState = USBH_MSC_BOT_CBW_WAIT;
            BOT_ErrorCount = 0;
        }
        break;

    case USBH_MSC_BOT_CBW_WAIT:
        resp = USBH_State();
        if(resp == USBR_ACK)
        {
            BOT_StallCount = 0;

            USBH_MSC_Info.OutEpDATAX ^= 1;

            if(USBH_CBWData.CBWTransferLength != 0)
            {
                remLen = USBH_CBWData.CBWTransferLength;
                pdBuff = USBH_BOTXfer.pDataBuffer;

                if((USBH_CBWData.CBWFlags & USB_REQ_DIR_MASK) == USB_REQ_D2H)
                {
                    USBH_BOTXfer.BOTState = USBH_MSC_BOT_DIN;
                }
                else
                {
                    USBH_BOTXfer.BOTState = USBH_MSC_BOT_DOUT;
                }
            }
            else    // NO Data Transfer Stage
            {
                USBH_BOTXfer.BOTState = USBH_MSC_BOT_CSW;
            }
        }
        else if(resp == USBR_NAK)
        {
            USBH_BOTXfer.BOTState = USBH_BOTXfer.BOTStateBkp;
        }
        else if(resp == USBR_STALL)
        {
            USBH_BOTXfer.BOTState = USBH_MSC_BOT_HANDLE_STALL_OUT;
        }
        else if(resp == USBR_ERROR)
        {
            USBH_BOTXfer.BOTState = USBH_MSC_BOT_HANDLE_ERROR;
        }
        break;

    case USBH_MSC_BOT_DIN:
        size = (remLen > USBH_MSC_Info.InEpSize) ? USBH_MSC_Info.InEpSize : remLen;
        if(USBH_SendInPacket(phost->Device.Address, USBH_MSC_Info.InEp, USBH_MSC_Info.InEpDATAX, size))
        {
            USBH_BOTXfer.BOTStateBkp = USBH_BOTXfer.BOTState;
            USBH_BOTXfer.BOTState = USBH_MSC_BOT_DIN_WAIT;
        }
        break;

    case USBH_MSC_BOT_DIN_WAIT:
        resp = USBH_State();
        if(resp == USBR_ACK)
        {
            BOT_StallCount = 0;

            USBH_MSC_Info.InEpDATAX ^= 1;

            if(remLen > USBH_MSC_Info.InEpSize)
            {
                USBH_ReadRxBuffer(pdBuff, USBH_MSC_Info.InEpSize);

                remLen -= USBH_MSC_Info.InEpSize;
                pdBuff += USBH_MSC_Info.InEpSize;

                USBH_BOTXfer.BOTState = USBH_MSC_BOT_DIN;
            }
            else
            {
                USBH_ReadRxBuffer(pdBuff, remLen);

                USBH_BOTXfer.BOTState = USBH_MSC_BOT_CSW;
            }
        }
        else if(resp == USBR_NAK)
        {
            USBH_BOTXfer.BOTState = USBH_BOTXfer.BOTStateBkp;
        }
        else if(resp == USBR_STALL)
        {
            USBH_BOTXfer.BOTState = USBH_MSC_BOT_HANDLE_STALL_IN;
        }
        else if(resp == USBR_ERROR)
        {
            USBH_BOTXfer.BOTState = USBH_MSC_BOT_HANDLE_ERROR;
        }
        break;

    case USBH_MSC_BOT_DOUT:
        size = (remLen > USBH_MSC_Info.OutEpSize) ? USBH_MSC_Info.OutEpSize : remLen;
        if(USBH_SendOutPacket(phost->Device.Address, USBH_MSC_Info.OutEp, USBH_MSC_Info.OutEpDATAX, pdBuff, size))
        {
            USBH_BOTXfer.BOTStateBkp = USBH_BOTXfer.BOTState;
            USBH_BOTXfer.BOTState = USBH_MSC_BOT_DOUT_WAIT;
        }
        break;

    case USBH_MSC_BOT_DOUT_WAIT:
        resp = USBH_State();
        if(resp == USBR_ACK)
        {
            BOT_StallCount = 0;

            USBH_MSC_Info.OutEpDATAX ^= 1;

            if(remLen > USBH_MSC_Info.OutEpSize)
            {
                remLen -= USBH_MSC_Info.OutEpSize;
                pdBuff += USBH_MSC_Info.OutEpSize;

                USBH_BOTXfer.BOTState = USBH_MSC_BOT_DOUT;
            }
            else
            {
                USBH_BOTXfer.BOTState = USBH_MSC_BOT_CSW;
            }
        }
        else if(resp == USBR_NAK)
        {
            USBH_BOTXfer.BOTState = USBH_BOTXfer.BOTStateBkp;
        }
        else if(resp == USBR_STALL)
        {
            USBH_BOTXfer.BOTState = USBH_MSC_BOT_HANDLE_STALL_OUT;
        }
        else if(resp == USBR_ERROR)
        {
            USBH_BOTXfer.BOTState = USBH_MSC_BOT_HANDLE_ERROR;
        }
        break;

    case USBH_MSC_BOT_CSW:
        if(USBH_SendInPacket(phost->Device.Address, USBH_MSC_Info.InEp, USBH_MSC_Info.InEpDATAX, MSC_CSW_LENGTH))
        {
            USBH_BOTXfer.BOTStateBkp = USBH_BOTXfer.BOTState;
            USBH_BOTXfer.BOTState = USBH_MSC_BOT_CSW_WAIT;
        }
        break;

    case USBH_MSC_BOT_CSW_WAIT:
        resp = USBH_State();
        if(resp == USBR_ACK)
        {
            BOT_StallCount = 0;

            USBH_MSC_Info.InEpDATAX ^= 1;

            USBH_ReadRxBuffer((uint8_t *)&USBH_CSWData, MSC_CSW_LENGTH);
            USBH_BOTXfer.bCSWStatus = USBH_MSC_BOT_DecodeCSW(phost);

            USBH_BOTXfer.MSCState = USBH_BOTXfer.MSCStateBkp;
        }
        else if(resp == USBR_NAK)
        {
            USBH_BOTXfer.BOTState = USBH_BOTXfer.BOTStateBkp;
        }
        else if(resp == USBR_STALL)
        {
            USBH_BOTXfer.BOTState = USBH_MSC_BOT_HANDLE_STALL_IN;
        }
        else if(resp == USBR_ERROR)
        {
            USBH_BOTXfer.BOTState = USBH_MSC_BOT_HANDLE_ERROR;
        }
        break;

    case USBH_MSC_BOT_HANDLE_ERROR:
        BOT_ErrorCount++;
        if(BOT_ErrorCount < 5)
        {
            USBH_BOTXfer.BOTState = USBH_BOTXfer.BOTStateBkp;   // retry
        }
        else
        {
            USBH_BOTXfer.bCSWStatus = USBH_MSC_PHASE_ERROR;     // unrecovered error

            USBH_BOTXfer.MSCState = USBH_BOTXfer.MSCStateBkp;
        }
        break;

    case USBH_MSC_BOT_HANDLE_STALL_IN:
        stat = USBH_ClrFeature(phost, USBH_MSC_Info.InEp);
        if(stat == USBH_OK)
        {
            USBH_MSC_Info.InEpDATAX = 0;

            USBH_BOTXfer.BOTState = USBH_BOTXfer.BOTStateBkp;
        }
        break;

    case USBH_MSC_BOT_HANDLE_STALL_OUT:
        stat = USBH_ClrFeature(phost, USBH_MSC_Info.OutEp);
        if(stat == USBH_OK)
        {
            USBH_MSC_Info.OutEpDATAX = 0;

            USBH_BOTXfer.BOTState = USBH_BOTXfer.BOTStateBkp;
        }
        break;

    default:
        break;
    }
}


/******************************************************************************************************************************************
* 函数名称: USBH_MSC_BOT_DecodeCSW()
* 功能说明:
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t USBH_MSC_BOT_DecodeCSW(USBH_Info_t *phost)
{
    uint8_t status;

    if(USBH_CSWData.CSWSignature == MSC_CSW_SIGNATURE)
    {
        if(USBH_CSWData.CSWTag == USBH_CBWData.CBWTag)
        {
            status = USBH_CSWData.CSWStatus;
        }
        else    // CSW Tag Error
        {
            status = USBH_MSC_PHASE_ERROR;
        }
    }
    else        // CSW Signature Error
    {
        status = USBH_MSC_PHASE_ERROR;
    }

    return status;
}

