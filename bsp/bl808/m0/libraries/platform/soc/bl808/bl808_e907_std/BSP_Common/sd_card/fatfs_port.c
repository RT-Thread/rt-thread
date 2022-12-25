/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "bsp_sdio_sdcard.h"
#include "bflb_platform.h"

static sd_card_t gSDCardInfo;

int RAM_disk_status()
{
    return 0;
}

int MMC_disk_status()
{
    return 0;
}

int USB_disk_status()
{
    return 0;
}

int RAM_disk_initialize()
{
    return 0;
}

int MMC_disk_initialize()
{
    static uint8_t inited=0;

    if(inited==0){
        if(SDH_Init(SDH_DATA_BUS_WIDTH_4BITS,&gSDCardInfo)==SD_OK){
            inited=1;
            return 0;
        }else {
            return -1;
        }
    }
    return 0;
}

int USB_disk_initialize()
{
    return 0;
}

int RAM_disk_read(BYTE* buff, LBA_t sector, UINT count)
{
    return 0;
}

int MMC_disk_read(BYTE* buff, LBA_t sector, UINT count)
{
    if(SD_OK==SDH_ReadMultiBlocks(buff,sector,gSDCardInfo.blockSize,count)){
		return 0;
	}else {
		return -1;
	}
}

int USB_disk_read(BYTE* buff, LBA_t sector, UINT count)
{
    return 0;
}

int RAM_disk_write(const BYTE* buff, LBA_t sector, UINT count)
{
    return 0;
}

int MMC_disk_write(const BYTE* buff, LBA_t sector, UINT count)
{
    if(SD_OK==SDH_WriteMultiBlocks((uint8_t *)buff,sector,gSDCardInfo.blockSize,count)){
		return 0;
	}else {
		return -1;
	}
}

int USB_disk_write(const BYTE* buff, LBA_t sector, UINT count)
{
    return 0;
}

int RAM_disk_ioctl(BYTE cmd, void* buff)
{
    return 0;
}

int MMC_disk_ioctl(BYTE cmd, void* buff)
{
	switch (cmd) 
	{
		// Get R/W sector size (WORD) 
		case GET_SECTOR_SIZE :    
			*(WORD * )buff = gSDCardInfo.blockSize;
		break;
		// Get erase block size in unit of sector (DWORD)
		case GET_BLOCK_SIZE :      
			*(DWORD * )buff = 1;
		break;

		case GET_SECTOR_COUNT:
			*(DWORD * )buff = gSDCardInfo.blockCount;
			break;
		case CTRL_SYNC :
			break;
		default:
			break;
	}
	return 0;
}

int USB_disk_ioctl(BYTE cmd, void* buff)
{
    return 0;
}

DWORD get_fattime(void) {
	return	  ((DWORD)(2015 - 1980) << 25)	/* Year 2015 */
			| ((DWORD)1 << 21)				/* Month 1 */
			| ((DWORD)1 << 16)				/* Mday 1 */
			| ((DWORD)0 << 11)				/* Hour 0 */
			| ((DWORD)0 << 5)				  /* Min 0 */
			| ((DWORD)0 >> 1);				/* Sec 0 */
}

