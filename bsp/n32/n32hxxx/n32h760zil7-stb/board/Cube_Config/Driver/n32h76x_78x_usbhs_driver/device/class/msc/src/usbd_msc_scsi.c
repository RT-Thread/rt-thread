/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file usbd_msc_scsi.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "usbd_msc_bot.h"
#include "usbd_msc_scsi.h"
#include "usbd_msc_mem.h"
#include "usbd_msc_data.h"

SCSI_Sense_TypeDef     SCSI_Sense [SENSE_LIST_DEEPTH];
uint8_t   SCSI_Sense_Head;
uint8_t   SCSI_Sense_Tail;

uint32_t  SCSI_blk_size;
uint32_t  SCSI_blk_nbr;

uint32_t  SCSI_blk_addr;
uint32_t  SCSI_blk_len;

USB_CORE_MODULE  *cdev;

static int8_t SCSI_TestUnitReady(uint8_t lun, uint8_t *params);
static int8_t SCSI_Inquiry(uint8_t lun, uint8_t *params);
static int8_t SCSI_ReadFormatCapacity(uint8_t lun, uint8_t *params);
static int8_t SCSI_ReadCapacity10(uint8_t lun, uint8_t *params);
static int8_t SCSI_RequestSense (uint8_t lun, uint8_t *params);
static int8_t SCSI_StartStopUnit(uint8_t lun, uint8_t *params);
static int8_t SCSI_ModeSense6 (uint8_t lun, uint8_t *params);
static int8_t SCSI_ModeSense10 (uint8_t lun, uint8_t *params);
static int8_t SCSI_Write10(uint8_t lun , uint8_t *params);
static int8_t SCSI_Read10(uint8_t lun , uint8_t *params);
static int8_t SCSI_Verify10(uint8_t lun, uint8_t *params);
static int8_t SCSI_CheckAddressRange (uint8_t lun ,
                                      uint32_t blk_offset ,
                                      uint16_t blk_nbr);
static int8_t SCSI_ProcessRead (uint8_t lun);

static int8_t SCSI_ProcessWrite (uint8_t lun);

/**
*\*\name   SCSI_ProcessCmd.
*\*\fun    Process SCSI commands.
*\*\param  pdev: USB device
*\*\param  lun: Logical unit number
*\*\param  params: Command parameters
*\*\return status
**/
int8_t SCSI_ProcessCmd(USB_CORE_MODULE  *pdev, uint8_t lun, uint8_t *params)
{
    cdev = pdev;

    switch (params[0])
    {
        case SCSI_TEST_UNIT_READY:
            return SCSI_TestUnitReady(lun, params);

        case SCSI_REQUEST_SENSE:
            return SCSI_RequestSense (lun, params);
        case SCSI_INQUIRY:
            return SCSI_Inquiry(lun, params);

        case SCSI_START_STOP_UNIT:
            return SCSI_StartStopUnit(lun, params);

        case SCSI_ALLOW_MEDIUM_REMOVAL:
            return SCSI_StartStopUnit(lun, params);

        case SCSI_MODE_SENSE6:
            return SCSI_ModeSense6 (lun, params);

        case SCSI_MODE_SENSE10:
            return SCSI_ModeSense10 (lun, params);

        case SCSI_READ_FORMAT_CAPACITIES:
            return SCSI_ReadFormatCapacity(lun, params);

        case SCSI_READ_CAPACITY10:
            return SCSI_ReadCapacity10(lun, params);

        case SCSI_READ10:
            return SCSI_Read10(lun, params);

        case SCSI_WRITE10:
            return SCSI_Write10(lun, params);

        case SCSI_VERIFY10:
            return SCSI_Verify10(lun, params);

        default:
            SCSI_SenseCode(lun, ILLEGAL_REQUEST, INVALID_CDB);
        return -1;
    }
}

/**
*\*\name   SCSI_TestUnitReady.
*\*\fun    Process SCSI Test Unit Ready Command.
*\*\param  lun: Logical unit number
*\*\param  params: Command parameters
*\*\return status
**/
static int8_t SCSI_TestUnitReady(uint8_t lun, uint8_t *params)
{
    /* case 9 : Hi > D0 */
    if (MSC_BOT_cbw.dDataLength != 0)
    {
        SCSI_SenseCode(MSC_BOT_cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
        return -1;
    }
    if(USBD_STORAGE_fops->IsReady(lun) !=0 )
    {
        SCSI_SenseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
        return -1;
    }
    MSC_BOT_DataLen = 0;
    return 0;
}

/**
*\*\name   SCSI_Inquiry.
*\*\fun    Process Inquiry command.
*\*\param  lun: Logical unit number
*\*\param  params: Command parameters
*\*\return status
**/
static int8_t SCSI_Inquiry(uint8_t lun, uint8_t *params)
{
    uint8_t* pPage;
    uint16_t len;

    if (params[1] & 0x01)/*Evpd is set*/
    {
        pPage = (uint8_t *)MSC_Page00_Inquiry_Data;
        len = LENGTH_INQUIRY_PAGE00;
    }
    else
    {
        pPage = (uint8_t *)&USBD_STORAGE_fops->pInquiry[lun * USBD_STD_INQUIRY_LENGTH];
        len = pPage[4] + 5;
        if (params[4] <= len)
        {
            len = params[4];
        }
    }
    MSC_BOT_DataLen = len;

    while (len)
    {
        len--;
        MSC_BOT_Data[len] = pPage[len];
    }
    return 0;
}

/**
*\*\name   SCSI_ReadCapacity10.
*\*\fun    Process Read Capacity 10 command.
*\*\param  lun: Logical unit number
*\*\param  params: Command parameters
*\*\return status
**/
static int8_t SCSI_ReadCapacity10(uint8_t lun, uint8_t *params)
{
    if(USBD_STORAGE_fops->GetCapacity(lun, &SCSI_blk_nbr, &SCSI_blk_size) != 0)
    {
        SCSI_SenseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
        return -1;
    }
    else
    {
        MSC_BOT_Data[0] = (uint8_t)((SCSI_blk_nbr - 1) >> 24);
        MSC_BOT_Data[1] = (uint8_t)((SCSI_blk_nbr - 1) >> 16);
        MSC_BOT_Data[2] = (uint8_t)((SCSI_blk_nbr - 1) >>  8);
        MSC_BOT_Data[3] = (uint8_t)(SCSI_blk_nbr - 1);

        MSC_BOT_Data[4] = (uint8_t)(SCSI_blk_size >>  24);
        MSC_BOT_Data[5] = (uint8_t)(SCSI_blk_size >>  16);
        MSC_BOT_Data[6] = (uint8_t)(SCSI_blk_size >>  8);
        MSC_BOT_Data[7] = (uint8_t)(SCSI_blk_size);

        MSC_BOT_DataLen = 8;
        return 0;
    }
}

/**
*\*\name   SCSI_ReadFormatCapacity.
*\*\fun    Process Read Format Capacity command.
*\*\param  lun: Logical unit number
*\*\param  params: Command parameters
*\*\return status
**/
static int8_t SCSI_ReadFormatCapacity(uint8_t lun, uint8_t *params)
{
    uint32_t blk_size;
    uint32_t blk_nbr;
    uint16_t i;

    for(i=0 ; i < 12 ; i++)
    {
        MSC_BOT_Data[i] = 0;
    }

    if(USBD_STORAGE_fops->GetCapacity(lun, &blk_nbr, &blk_size) != 0)
    {
        SCSI_SenseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
        return -1;
    }
    else
    {
        MSC_BOT_Data[3] = 0x08;
        MSC_BOT_Data[4] = (uint8_t)((blk_nbr - 1) >> 24);
        MSC_BOT_Data[5] = (uint8_t)((blk_nbr - 1) >> 16);
        MSC_BOT_Data[6] = (uint8_t)((blk_nbr - 1) >>  8);
        MSC_BOT_Data[7] = (uint8_t)(blk_nbr - 1);

        MSC_BOT_Data[8] = 0x02;
        MSC_BOT_Data[9] = (uint8_t)(blk_size >>  16);
        MSC_BOT_Data[10] = (uint8_t)(blk_size >>  8);
        MSC_BOT_Data[11] = (uint8_t)(blk_size);

        MSC_BOT_DataLen = 12;
        return 0;
    }
}

/**
*\*\name   SCSI_ModeSense6.
*\*\fun    Process Mode Sense6 command.
*\*\param  lun: Logical unit number
*\*\param  params: Command parameters
*\*\return status
**/
static int8_t SCSI_ModeSense6 (uint8_t lun, uint8_t *params)
{
    uint16_t len = 8 ;
    MSC_BOT_DataLen = len;

    while (len)
    {
        len--;
        MSC_BOT_Data[len] = MSC_Mode_Sense6_data[len];
    }
    return 0;
}

/**
*\*\name   SCSI_ModeSense10.
*\*\fun    Process Mode Sense10 command.
*\*\param  lun: Logical unit number
*\*\param  params: Command parameters
*\*\return status
**/
static int8_t SCSI_ModeSense10 (uint8_t lun, uint8_t *params)
{
    uint16_t len = 8;

    MSC_BOT_DataLen = len;

    while (len)
    {
        len--;
        MSC_BOT_Data[len] = MSC_Mode_Sense10_data[len];
    }
    return 0;
}

/**
*\*\name   SCSI_RequestSense.
*\*\fun    Process Request Sense command.
*\*\param  lun: Logical unit number
*\*\param  params: Command parameters
*\*\return status
**/
static int8_t SCSI_RequestSense (uint8_t lun, uint8_t *params)
{
    uint8_t i;

    for(i=0 ; i < REQUEST_SENSE_DATA_LEN ; i++)
    {
        MSC_BOT_Data[i] = 0;
    }

    MSC_BOT_Data[0] = 0x70;
    MSC_BOT_Data[7] = REQUEST_SENSE_DATA_LEN - 6;

    if((SCSI_Sense_Head != SCSI_Sense_Tail)) 
    {

        MSC_BOT_Data[2]     = SCSI_Sense[SCSI_Sense_Head].Skey;
        MSC_BOT_Data[12]    = SCSI_Sense[SCSI_Sense_Head].w.b.ASCQ;
        MSC_BOT_Data[13]    = SCSI_Sense[SCSI_Sense_Head].w.b.ASC;
        SCSI_Sense_Head++;

        if (SCSI_Sense_Head == SENSE_LIST_DEEPTH)
        {
            SCSI_Sense_Head = 0;
        }
    }
    MSC_BOT_DataLen = REQUEST_SENSE_DATA_LEN;

    if (params[4] <= REQUEST_SENSE_DATA_LEN)
    {
        MSC_BOT_DataLen = params[4];
    }
    return 0;
}

/**
*\*\name   SCSI_SenseCode.
*\*\fun    Load the last error code in the error list.
*\*\param  lun: Logical unit number
*\*\param  sKey: Sense Key
*\*\param  ASC: Additional Sense Key
*\*\return none
**/
void SCSI_SenseCode(uint8_t lun, uint8_t sKey, uint8_t ASC)
{
    SCSI_Sense[SCSI_Sense_Tail].Skey  = sKey;
    SCSI_Sense[SCSI_Sense_Tail].w.ASC = ASC << 8;
    SCSI_Sense_Tail++;
    if (SCSI_Sense_Tail == SENSE_LIST_DEEPTH)
    {
        SCSI_Sense_Tail = 0;
    }
}

/**
*\*\name   SCSI_StartStopUnit.
*\*\fun    Process Start Stop Unit command.
*\*\param  lun: Logical unit number
*\*\param  params: Command parameters
*\*\return status
**/
static int8_t SCSI_StartStopUnit(uint8_t lun, uint8_t *params)
{
    MSC_BOT_DataLen = 0;
    return 0;
}

/**
*\*\name   SCSI_Read10.
*\*\fun    Process Read10 command.
*\*\param  lun: Logical unit number
*\*\param  params: Command parameters
*\*\return status
**/
static int8_t SCSI_Read10(uint8_t lun , uint8_t *params)
{
    if(MSC_BOT_State == BOT_IDLE)  /* Idle */
    {

        /* case 10 : Ho <> Di */

        if ((MSC_BOT_cbw.bmFlags & 0x80) != 0x80)
        {
            SCSI_SenseCode(MSC_BOT_cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
            return -1;
        }
        if(USBD_STORAGE_fops->IsReady(lun) !=0 )
        {
            SCSI_SenseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
            return -1;
        }

        SCSI_blk_addr = (params[2] << 24) | (params[3] << 16) | (params[4] <<  8) | params[5];
        SCSI_blk_len =  (params[7] <<  8) | params[8];
        
        if( SCSI_CheckAddressRange(lun, SCSI_blk_addr, SCSI_blk_len) < 0)
        {
            return -1; /* error */
        }

        MSC_BOT_State = BOT_DATA_IN;
        SCSI_blk_addr *= SCSI_blk_size;
        SCSI_blk_len  *= SCSI_blk_size;

        /* cases 4,5 : Hi <> Dn */
        if (MSC_BOT_cbw.dDataLength != SCSI_blk_len)
        {
            SCSI_SenseCode(MSC_BOT_cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
            return -1;
        }
    }
    MSC_BOT_DataLen = MSC_MEDIA_PACKET;

    return SCSI_ProcessRead(lun);
}

/**
*\*\name   SCSI_Write10.
*\*\fun    Process Write10 command.
*\*\param  lun: Logical unit number
*\*\param  params: Command parameters
*\*\return status
**/
static int8_t SCSI_Write10 (uint8_t lun , uint8_t *params)
{
    if (MSC_BOT_State == BOT_IDLE) /* Idle */
    {
        /* case 8 : Hi <> Do */

        if ((MSC_BOT_cbw.bmFlags & 0x80) == 0x80)
        {
            SCSI_SenseCode(MSC_BOT_cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
            return -1;
        }

        /* Check whether Media is ready */
        if(USBD_STORAGE_fops->IsReady(lun) !=0 )
        {
            SCSI_SenseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
            return -1;
        }

        /* Check If media is write-protected */
        if(USBD_STORAGE_fops->IsWriteProtected(lun) !=0 )
        {
            SCSI_SenseCode(lun, NOT_READY, WRITE_PROTECTED);
            return -1;
        }


        SCSI_blk_addr = (params[2] << 24) | (params[3] << 16) | (params[4] <<  8) | params[5];
        SCSI_blk_len = (params[7] <<  8) | params[8];

        /* check if LBA address is in the right range */
        if(SCSI_CheckAddressRange(lun, SCSI_blk_addr, SCSI_blk_len) < 0)
        {
            return -1; /* error */
        }

        SCSI_blk_addr *= SCSI_blk_size;
        SCSI_blk_len  *= SCSI_blk_size;

        /* cases 3,11,13 : Hn,Ho <> D0 */
        if (MSC_BOT_cbw.dDataLength != SCSI_blk_len)
        {
            SCSI_SenseCode(MSC_BOT_cbw.bLUN, ILLEGAL_REQUEST, INVALID_CDB);
            return -1;
        }

        /* Prepare EP to receive first data packet */
        MSC_BOT_State = BOT_DATA_OUT;
        USBDEV_EP_PrepareRx (cdev, MSC_OUT_EP, MSC_BOT_Data, MIN (SCSI_blk_len, MSC_MEDIA_PACKET));
    }
    else /* Write Process ongoing */
    {
        return SCSI_ProcessWrite(lun);
    }
    return 0;
}

/**
*\*\name   SCSI_Verify10.
*\*\fun    Process Verify10 command.
*\*\param  lun: Logical unit number
*\*\param  params: Command parameters
*\*\return status
**/
static int8_t SCSI_Verify10(uint8_t lun , uint8_t *params)
{
    if ((params[1]& 0x02) == 0x02)
    {
        SCSI_SenseCode (lun, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
        return -1; /* Error, Verify Mode Not supported*/
    }

    SCSI_blk_addr = (params[2] << 24) | (params[3] << 16) | (params[4] <<  8) | params[5];
    SCSI_blk_len = (params[7] <<  8) | params[8];

    if(SCSI_CheckAddressRange(lun, SCSI_blk_addr, SCSI_blk_len) < 0)
    {
        return -1; /* error */
    }
    MSC_BOT_DataLen = 0;
    return 0;
}

/**
*\*\name   SCSI_CheckAddressRange.
*\*\fun    Check address range.
*\*\param  lun: Logical unit number
*\*\param  blk_offset: first block address
*\*\param  blk_nbr: number of block to be processed
*\*\return status
**/
static int8_t SCSI_CheckAddressRange (uint8_t lun , uint32_t blk_offset , uint16_t blk_nbr)
{
    if ((blk_offset + blk_nbr) > SCSI_blk_nbr )
    {
        SCSI_SenseCode(lun, ILLEGAL_REQUEST, ADDRESS_OUT_OF_RANGE);
        return -1;
    }
    return 0;
}

/**
*\*\name   SCSI_ProcessRead.
*\*\fun    Handle Read Process.
*\*\param  lun: Logical unit number
*\*\return status
**/
static int8_t SCSI_ProcessRead (uint8_t lun)
{
    uint32_t len;

    len = MIN(SCSI_blk_len , MSC_MEDIA_PACKET);

    if( USBD_STORAGE_fops->Read(lun , MSC_BOT_Data, SCSI_blk_addr / SCSI_blk_size, len / SCSI_blk_size) < 0)
    {
        SCSI_SenseCode(lun, HARDWARE_ERROR, UNRECOVERED_READ_ERROR);
        return -1;
    }

    USBDEV_EP_Tx (cdev, MSC_IN_EP, MSC_BOT_Data, len);

    SCSI_blk_addr   += len;
    SCSI_blk_len    -= len;

    /* case 6 : Hi = Di */
    MSC_BOT_csw.dDataResidue -= len;

    if (SCSI_blk_len == 0)
    {
        MSC_BOT_State = BOT_LAST_DATA_IN;
    }
    return 0;
}

/**
*\*\name   SCSI_ProcessWrite.
*\*\fun    Handle Write Process.
*\*\param  lun: Logical unit number
*\*\return status
**/
static int8_t SCSI_ProcessWrite (uint8_t lun)
{
    uint32_t len;

    len = MIN(SCSI_blk_len , MSC_MEDIA_PACKET);

    if(USBD_STORAGE_fops->Write(lun , MSC_BOT_Data, SCSI_blk_addr / SCSI_blk_size, len / SCSI_blk_size) < 0)
    {
        SCSI_SenseCode(lun, HARDWARE_ERROR, WRITE_FAULT);
        return -1;
    }


    SCSI_blk_addr  += len;
    SCSI_blk_len   -= len;

    /* case 12 : Ho = Do */
    MSC_BOT_csw.dDataResidue -= len;

    if (SCSI_blk_len == 0)
    {
        MSC_BOT_SendCSW (cdev, CSW_CMD_PASSED);
    }
    else
    {
        /* Prapare EP to Receive next packet */
        USBDEV_EP_PrepareRx (cdev, MSC_OUT_EP, MSC_BOT_Data, MIN (SCSI_blk_len, MSC_MEDIA_PACKET));
    }

    return 0;
}
