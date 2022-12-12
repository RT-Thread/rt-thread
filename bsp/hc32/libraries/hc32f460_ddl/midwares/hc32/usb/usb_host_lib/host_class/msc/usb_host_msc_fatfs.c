/**
 *******************************************************************************
 * @file  usb_host_msc_fatfs.c
 * @brief The fatfs functions.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_app_conf.h"
#include "usb_host_driver.h"
#ifdef USB_MSC_FAT_VALID
#include "ff.h"
#include "diskio.h"
#include "usb_host_msc_class.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_MSC
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static volatile DSTATUS Stat = STA_NOINIT;  /* Disk status */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

extern usb_core_instance          usb_app_instance;
extern USBH_HOST                  usb_app_host;

/**
 * @brief  Initialize Disk Drive
 * @param  [in] drv     Physical drive number (0)
 * @retval DSTATUS
 */
DSTATUS disk_initialize(BYTE drv)
{
    if (host_driver_ifdevconnected(&usb_app_instance) != 0UL) {
        Stat &= (DSTATUS)~STA_NOINIT;
    }
    return Stat;
}

/**
 * @brief  Get Disk Status
 * @param  [in] drv Physical drive number (0)
 * @retval DSTATUS
 */
DSTATUS disk_status(BYTE drv)
{
    DSTATUS status = Stat;
    if (drv != 0U) {
        status = STA_NOINIT;        /* Supports only single drive */
    }
    return status;
}

/**
 * @brief  Read Sector(s)
 * @param  [in] drv     Physical drive number (0)
 * @param  [in] buff    Pointer to the data buffer to store read data
 * @param  [in] sector  Start sector number (LBA)
 * @param  [in] count   Sector count (1..255)
 * @retval DSTATUS
 */
DRESULT disk_read(BYTE pdrv, BYTE *buff, LBA_t sector, UINT count)
{
    USB_HOST_MSC_STATUS status = USB_HOST_MSC_OK;

    if ((pdrv != 0U) || (count == 0UL)) {
        return RES_PARERR;
    }
    if ((Stat & STA_NOINIT) == STA_NOINIT) {
        return RES_NOTRDY;
    }

    if (host_driver_ifdevconnected(&usb_app_instance) != 0UL) {

        do {
            status = usb_host_msc_Read10(&usb_app_instance, buff, sector, 512UL * (uint32_t)count);
            usb_host_msc_botxferprocess(&usb_app_instance, &usb_app_host);

            if (host_driver_ifdevconnected(&usb_app_instance) == 0UL) {
                return RES_ERROR;
            }
        } while (status == USB_HOST_MSC_BUSY);
    }

    if (status == USB_HOST_MSC_OK) {
        return RES_OK;
    }
    return RES_ERROR;

}


#if _READONLY == 0
/**
 * @brief  Write Sector(s)
 * @param  [in] drv     Physical drive number (0)
 * @param  [in] buff    Pointer to the data to be written
 * @param  [in] sector  Start sector number (LBA)
 * @param  [in] count   Sector count (1..255)
 * @retval DSTATUS
 */
DRESULT disk_write(BYTE pdrv, const BYTE *buff, LBA_t sector, UINT count)
{
    USB_HOST_MSC_STATUS status = USB_HOST_MSC_OK;

    if ((pdrv != 0U) || (count == 0UL)) {
        return RES_PARERR;
    }
    if ((Stat & STA_NOINIT) == STA_NOINIT) {
        return RES_NOTRDY;
    }
    if ((Stat & STA_PROTECT) == STA_PROTECT) {
        return RES_WRPRT;
    }
    if (host_driver_ifdevconnected(&usb_app_instance) != 0UL) {
        do {
            status = usb_host_msc_Write10(&usb_app_instance, (BYTE *)buff, sector, 512UL * (uint32_t)count);
            usb_host_msc_botxferprocess(&usb_app_instance, &usb_app_host);

            if (host_driver_ifdevconnected(&usb_app_instance) == 0UL) {
                return RES_ERROR;
            }
        } while (status == USB_HOST_MSC_BUSY);
    }

    if (status == USB_HOST_MSC_OK) {
        return RES_OK;
    }
    return RES_ERROR;
}
#endif /* _READONLY == 0 */

//#if _USE_IOCTL != 0
/**
 * @brief  Miscellaneous Functions
 * @param  [in] drv     Physical drive number (0)
 * @param  [in] ctrl    Control code
 * @param  [in] buff    Buffer to send/receive control data
 **
 * @retval DSTATUS
 */
DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void *buff)
{
    DRESULT res;

    if (pdrv != 0U) {
        return RES_PARERR;
    }

    res = RES_ERROR;

    if ((Stat & STA_NOINIT) == STA_NOINIT) {
        return RES_NOTRDY;
    }

    switch (cmd) {
        case CTRL_SYNC :        /* Make sure that no pending write process */
            res = RES_OK;
            break;
        case GET_SECTOR_COUNT : /* Get number of sectors on the disk (DWORD) */
            *(DWORD *)buff = (DWORD) USB_HOST_MSC_Param.MSC_Capacity;
            res = RES_OK;
            break;
        case GET_SECTOR_SIZE :  /* Get R/W sector size (WORD) */
            *(WORD *)buff = 512U;
            res = RES_OK;
            break;
        case GET_BLOCK_SIZE :   /* Get erase block size in unit of sector (DWORD) */
            *(DWORD *)buff = 512UL;
            break;
        default:
            res = RES_PARERR;
            break;
    }
    return res;
}
//#endif
#endif /* _USE_IOCTL != 0 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
