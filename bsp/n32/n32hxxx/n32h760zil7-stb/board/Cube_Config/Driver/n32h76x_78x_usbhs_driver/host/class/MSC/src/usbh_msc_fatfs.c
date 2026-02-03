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
 * @file usbh_msc_fatfs.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "usbhs_conf.h"
#include "usbh_core.h"
#include "diskio.h"
#include "usbh_msc_scsi.h"
#include "usbh_msc_bot.h"

DWORD get_fattime(void);

static volatile DSTATUS Stat = STA_NOINIT;	/* Disk status */

extern USB_CORE_MODULE USBHS_Core;
extern USBH_HOST USB_Host;

/**
*\*\name    disk_initialize.
*\*\fun     Initialize Disk Drive.
*\*\param   drv: Physical drive number.
*\*\return  Stat.
*\*\
**/
DSTATUS disk_initialize(BYTE drv)/* Physical drive number (0) */
{
    if(HOST_IsDeviceConnected(&USBHS_Core))
    {  
        Stat &= ~STA_NOINIT;
    }

    return Stat;
}

/**
*\*\name    disk_status.
*\*\fun     Get Disk Status.
*\*\param   drv: Physical drive number.
*\*\return  Stat.
*\*\
**/
DSTATUS disk_status(BYTE drv) /* Physical drive number (0) */
{
    if (drv) return STA_NOINIT;   /* Supports only single drive */
    return Stat;
}

/**
*\*\name    disk_read.
*\*\fun     Read Sector(s).
*\*\param   pdrv: Physical drive number.
*\*\param   buff: Pointer to the data buffer to store read data.
*\*\param   sector: Start sector number.
*\*\param   count: Sector count.
*\*\return  Stat.
*\*\
**/
DRESULT disk_read (BYTE pdrv, BYTE *buff, DWORD sector, UINT count)
{
    BYTE status = USBH_MSC_OK;

    if (pdrv || !count) return RES_PARERR;
    if (Stat & STA_NOINIT) return RES_NOTRDY;


    if(HOST_IsDeviceConnected(&USBHS_Core))
    {
        do
        {
            status = USBH_MSC_Read10(&USBHS_Core, buff,sector,512 * count);
            USBH_MSC_HandleBOTXfer(&USBHS_Core ,&USB_Host);
          
            if(!HOST_IsDeviceConnected(&USBHS_Core))
            { 
                return RES_ERROR;
            }
        }
        while(status == USBH_MSC_BUSY );
    }
    if(status == USBH_MSC_OK)
    return RES_OK;
    return RES_ERROR;
}

#if _READONLY == 0

/**
*\*\name    disk_write.
*\*\fun     Write Sector(s).
*\*\param   pdrv: Physical drive number.
*\*\param   buff: Pointer to the data buffer to be written.
*\*\param   sector: Start sector number.
*\*\param   count: Sector count.
*\*\return  Stat.
*\*\
**/
DRESULT disk_write (BYTE pdrv, const BYTE *buff, DWORD sector, UINT count)
{
    BYTE status = USBH_MSC_OK;
    if (pdrv || !count) return RES_PARERR;
    if (Stat & STA_NOINIT) return RES_NOTRDY;
    if (Stat & STA_PROTECT) return RES_WRPRT;


    if(HOST_IsDeviceConnected(&USBHS_Core))
    {  
        do
        {
            status = USBH_MSC_Write10(&USBHS_Core,(BYTE*)buff,sector,512 * count);
            USBH_MSC_HandleBOTXfer(&USBHS_Core, &USB_Host);

            if(!HOST_IsDeviceConnected(&USBHS_Core))
            { 
                return RES_ERROR;
            }
        }
        while(status == USBH_MSC_BUSY );
    }

    if(status == USBH_MSC_OK)
    return RES_OK;
    return RES_ERROR;
}
#endif /* _READONLY == 0 */

#if _USE_IOCTL != 0
/**
*\*\name    disk_ioctl.
*\*\fun     Miscellaneous Functions.
*\*\param   pdrv: Physical drive number.
*\*\param   ctrl: Control code.
*\*\param   buff: Buffer to send/receive control data.
*\*\return  res.
*\*\
**/
DRESULT disk_ioctl (BYTE drv, BYTE ctrl, void *buff)
{
    DRESULT res = RES_OK;

    if (drv) return RES_PARERR;

    res = RES_ERROR;

    if (Stat & STA_NOINIT) return RES_NOTRDY;

    switch (ctrl) 
    {
        case CTRL_SYNC :        /* Make sure that no pending write process */
            res = RES_OK;
            break;

        case GET_SECTOR_COUNT : /* Get number of sectors on the disk (DWORD) */

            *(DWORD*)buff = (DWORD) USBH_MSC_Param.MSCapacity;
            res = RES_OK;
            break;

        case GET_SECTOR_SIZE :  /* Get R/W sector size (WORD) */
            *(WORD*)buff = 512;
            res = RES_OK;
            break;

        case GET_BLOCK_SIZE :   /* Get erase block size in unit of sector (DWORD) */
            *(DWORD*)buff = 512;
            break;

        default:
        res = RES_PARERR;
    }
    return res;
}

/**
*\*\name    get_fattime.
*\*\fun     Gets Time from RTC .
*\*\param   none.
*\*\return  Time in DWORD.
*\*\
**/
DWORD get_fattime(void)
{
    return 0;
}

#endif /* _USE_IOCTL != 0 */
