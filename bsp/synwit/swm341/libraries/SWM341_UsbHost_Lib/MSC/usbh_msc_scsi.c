/******************************************************************************************************************************************
* 文件名称: usbh_msc_scsi.c
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
#include "usbh_msc_bot.h"
#include "usbh_msc_core.h"
#include "usbh_msc_scsi.h"


#define OPCODE_TEST_UNIT_READY      0X00
#define OPCODE_READ_CAPACITY10      0x25
#define OPCODE_MODE_SENSE6          0x1A
#define OPCODE_READ10               0x28
#define OPCODE_WRITE10              0x2A
#define OPCODE_REQUEST_SENSE        0x03

#define DATLEN_READ_CAPACITY10      8       // Data Stage Length
#define DATLEN_MODE_SENSE6          63
#define DATLEN_REQUEST_SENSE        18


static uint8_t SCSI_Busy = 0;

static uint8_t DataInBuffer[64];


/******************************************************************************************************************************************
* 函数名称: USBH_MSC_TestUnitReady()
* 功能说明: Issues 'Test unit ready' command to the device.
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_MSC_Status USBH_MSC_TestUnitReady(void)
{
    USBH_MSC_Status status = USBH_MSC_BUSY;

    if(!SCSI_Busy)
    {
        USBH_CBWData.CBWTransferLength = 0; // No Data Stage
        USBH_CBWData.CBWCBLength = 6;
        USBH_CBWData.CBWCB[0] = OPCODE_TEST_UNIT_READY;
        for(uint8_t i = 1; i < 16; i++) USBH_CBWData.CBWCB[i] = 0;

        USBH_BOTXfer.bCSWStatus = USBH_MSC_BUSY;
        USBH_BOTXfer.BOTState = USBH_MSC_BOT_CBW;

        USBH_BOTXfer.MSCStateBkp = USBH_BOTXfer.MSCState;
        USBH_BOTXfer.MSCState = USBH_MSC_BOT_TRANSFER;

        SCSI_Busy = 1;
    }
    else
    {
        if(USBH_BOTXfer.bCSWStatus != USBH_MSC_BUSY)
        {
            status = USBH_BOTXfer.bCSWStatus;

            SCSI_Busy = 0;
        }
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MSC_ReadCapacity10()
* 功能说明: Issue the read capacity command to the device.
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_MSC_Status USBH_MSC_ReadCapacity10(void)
{
    USBH_MSC_Status status = USBH_MSC_BUSY;

    if(!SCSI_Busy)
    {
        USBH_CBWData.CBWTransferLength = DATLEN_READ_CAPACITY10;
        USBH_CBWData.CBWFlags = USB_REQ_D2H;
        USBH_CBWData.CBWCBLength = 10;
        USBH_CBWData.CBWCB[0]  = OPCODE_READ_CAPACITY10;
        for(uint8_t i = 1; i < 16; i++) USBH_CBWData.CBWCB[i] = 0;

        USBH_BOTXfer.pDataBuffer = DataInBuffer;

        USBH_BOTXfer.bCSWStatus = USBH_MSC_BUSY;
        USBH_BOTXfer.BOTState = USBH_MSC_BOT_CBW;

        USBH_BOTXfer.MSCStateBkp = USBH_BOTXfer.MSCState;
        USBH_BOTXfer.MSCState = USBH_MSC_BOT_TRANSFER;

        SCSI_Busy = 1;
    }
    else
    {
        if(USBH_BOTXfer.bCSWStatus != USBH_MSC_BUSY)
        {
            if(USBH_BOTXfer.bCSWStatus == USBH_MSC_OK)
            {
                /* assign the capacity */
                ((uint8_t *)&USBH_MSC_Info.Capacity)[3] = DataInBuffer[0];
                ((uint8_t *)&USBH_MSC_Info.Capacity)[2] = DataInBuffer[1];
                ((uint8_t *)&USBH_MSC_Info.Capacity)[1] = DataInBuffer[2];
                ((uint8_t *)&USBH_MSC_Info.Capacity)[0] = DataInBuffer[3];

                /* assign the page length */
                ((uint8_t *)&USBH_MSC_Info.PageSize)[1] = DataInBuffer[6];
                ((uint8_t *)&USBH_MSC_Info.PageSize)[0] = DataInBuffer[7];
            }

            status = USBH_BOTXfer.bCSWStatus;

            SCSI_Busy = 0;
        }
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MSC_ModeSense6()
* 功能说明: Issue the Mode Sense6 Command to the device.
*           Used for reading the WriteProtect Status of the Mass-Storage device.
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_MSC_Status USBH_MSC_ModeSense6(void)
{
    USBH_MSC_Status status = USBH_MSC_BUSY;

    if(!SCSI_Busy)
    {
        USBH_CBWData.CBWTransferLength = DATLEN_MODE_SENSE6;
        USBH_CBWData.CBWFlags = USB_REQ_D2H;
        USBH_CBWData.CBWCBLength = 10;
        USBH_CBWData.CBWCB[0] = OPCODE_MODE_SENSE6;
        USBH_CBWData.CBWCB[1] = 0x00;
        USBH_CBWData.CBWCB[2] = 0x3F;
        USBH_CBWData.CBWCB[3] = 0x00;
        USBH_CBWData.CBWCB[4] = DATLEN_MODE_SENSE6;
        for(uint8_t i = 5; i < 16; i++) USBH_CBWData.CBWCB[i] = 0;

        USBH_BOTXfer.pDataBuffer = DataInBuffer;

        USBH_BOTXfer.bCSWStatus = USBH_MSC_BUSY;
        USBH_BOTXfer.BOTState = USBH_MSC_BOT_CBW;

        USBH_BOTXfer.MSCStateBkp = USBH_BOTXfer.MSCState;
        USBH_BOTXfer.MSCState = USBH_MSC_BOT_TRANSFER;

        SCSI_Busy = 1;
    }
    else
    {
        if(USBH_BOTXfer.bCSWStatus != USBH_MSC_BUSY)
        {
            if(USBH_BOTXfer.bCSWStatus == USBH_MSC_OK)
            {
                /* Assign the Write Protect status */
                if(DataInBuffer[2] & 0x80)
                {
                    USBH_MSC_Info.WProtect = 1;
                }
                else
                {
                    USBH_MSC_Info.WProtect = 0;
                }
            }

            status = USBH_BOTXfer.bCSWStatus;

            SCSI_Busy = 0;
        }
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MSC_Read10()
* 功能说明: Issue the read command to the device.
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_MSC_Status USBH_MSC_Read10(uint8_t *buffer, uint32_t address, uint32_t nbOfbytes)
{
    USBH_MSC_Status status = USBH_MSC_BUSY;
    uint16_t nbOfPages;

    if(!SCSI_Busy)
    {
        USBH_CBWData.CBWTransferLength = nbOfbytes;
        USBH_CBWData.CBWFlags = USB_REQ_D2H;
        USBH_CBWData.CBWCBLength = 10;
        USBH_CBWData.CBWCB[0] = OPCODE_READ10;
        USBH_CBWData.CBWCB[1] = 0x00;
        /*logical block address*/
        USBH_CBWData.CBWCB[2] = ((uint8_t *)&address)[3];
        USBH_CBWData.CBWCB[3] = ((uint8_t *)&address)[2];
        USBH_CBWData.CBWCB[4] = ((uint8_t *)&address)[1];
        USBH_CBWData.CBWCB[5] = ((uint8_t *)&address)[0];
        USBH_CBWData.CBWCB[6] = 0x00;
        /*Transfer length */
        nbOfPages = nbOfbytes / USBH_MSC_Info.PageSize;
        USBH_CBWData.CBWCB[7] = ((uint8_t *)&nbOfPages)[1];
        USBH_CBWData.CBWCB[8] = ((uint8_t *)&nbOfPages)[0];
        for(uint8_t i = 9; i < 16; i++) USBH_CBWData.CBWCB[i] = 0;

        USBH_BOTXfer.pDataBuffer = buffer;

        USBH_BOTXfer.bCSWStatus = USBH_MSC_BUSY;
        USBH_BOTXfer.BOTState = USBH_MSC_BOT_CBW;

        USBH_BOTXfer.MSCStateBkp = USBH_BOTXfer.MSCState;
        USBH_BOTXfer.MSCState = USBH_MSC_BOT_TRANSFER;

        SCSI_Busy = 1;
    }
    else
    {
        if(USBH_BOTXfer.bCSWStatus != USBH_MSC_BUSY)
        {
            status = USBH_BOTXfer.bCSWStatus;

            SCSI_Busy = 0;
        }
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MSC_Write10()
* 功能说明: Issue the write command to the device.
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_MSC_Status USBH_MSC_Write10(uint8_t *buffer, uint32_t address, uint32_t nbOfbytes)
{
    USBH_MSC_Status status = USBH_MSC_BUSY;
    uint16_t nbOfPages;

    if(!SCSI_Busy)
    {
        USBH_CBWData.CBWTransferLength = nbOfbytes;
        USBH_CBWData.CBWFlags = USB_REQ_H2D;
        USBH_CBWData.CBWCBLength = 10;
        USBH_CBWData.CBWCB[0] = OPCODE_WRITE10;
        USBH_CBWData.CBWCB[1] = 0x00;
        /*logical block address*/
        USBH_CBWData.CBWCB[2] = ((uint8_t *)&address)[3];
        USBH_CBWData.CBWCB[3] = ((uint8_t *)&address)[2];
        USBH_CBWData.CBWCB[4] = ((uint8_t *)&address)[1];
        USBH_CBWData.CBWCB[5] = ((uint8_t *)&address)[0];
        USBH_CBWData.CBWCB[6] = 0x00;
        /*Transfer length */
        nbOfPages = nbOfbytes / USBH_MSC_Info.PageSize;
        USBH_CBWData.CBWCB[7] = ((uint8_t *)&nbOfPages)[1];
        USBH_CBWData.CBWCB[8] = ((uint8_t *)&nbOfPages)[0];
        for(uint8_t i = 9; i < 16; i++) USBH_CBWData.CBWCB[i] = 0;

        USBH_BOTXfer.pDataBuffer = buffer;

        USBH_BOTXfer.bCSWStatus = USBH_MSC_BUSY;
        USBH_BOTXfer.BOTState = USBH_MSC_BOT_CBW;

        USBH_BOTXfer.MSCStateBkp = USBH_BOTXfer.MSCState;
        USBH_BOTXfer.MSCState = USBH_MSC_BOT_TRANSFER;

        SCSI_Busy = 1;
    }
    else
    {
        if(USBH_BOTXfer.bCSWStatus != USBH_MSC_BUSY)
        {
            status = USBH_BOTXfer.bCSWStatus;

            SCSI_Busy = 0;
        }
    }

    return status;
}


/******************************************************************************************************************************************
* 函数名称: USBH_MSC_RequestSense()
* 功能说明: Issues the Request Sense command to the device.
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
USBH_MSC_Status USBH_MSC_RequestSense(void)
{
    USBH_MSC_Status status = USBH_MSC_BUSY;

    if(!SCSI_Busy)
    {
        USBH_CBWData.CBWTransferLength = DATLEN_REQUEST_SENSE;
        USBH_CBWData.CBWFlags = USB_REQ_D2H;
        USBH_CBWData.CBWCBLength = 6;
        USBH_CBWData.CBWCB[0]  = OPCODE_REQUEST_SENSE;
        USBH_CBWData.CBWCB[1]  = 0x00;
        USBH_CBWData.CBWCB[2]  = 0x00;
        USBH_CBWData.CBWCB[3]  = 0x00;
        USBH_CBWData.CBWCB[4]  = DATLEN_REQUEST_SENSE;
        for(uint8_t i = 5; i < 16; i++) USBH_CBWData.CBWCB[i] = 0;

        USBH_BOTXfer.pDataBuffer = DataInBuffer;

        USBH_BOTXfer.bCSWStatus = USBH_MSC_BUSY;
        USBH_BOTXfer.BOTState = USBH_MSC_BOT_CBW;

        USBH_BOTXfer.MSCState = USBH_MSC_BOT_TRANSFER;

        SCSI_Busy = 1;
    }
    else
    {
        if(USBH_BOTXfer.bCSWStatus != USBH_MSC_BUSY)
        {
            if(USBH_BOTXfer.bCSWStatus == USBH_MSC_OK)
            {
                /* Assign Sense data*/
                ((uint8_t *)&USBH_MSC_Info.SenseKey)[3] = DataInBuffer[0];
                ((uint8_t *)&USBH_MSC_Info.SenseKey)[2] = DataInBuffer[1];
                ((uint8_t *)&USBH_MSC_Info.SenseKey)[1] = DataInBuffer[2];
                ((uint8_t *)&USBH_MSC_Info.SenseKey)[0] = DataInBuffer[3];

                status = USBH_MSC_OK;
            }

            status = USBH_BOTXfer.bCSWStatus;

            SCSI_Busy = 0;
        }
    }

    return status;
}
