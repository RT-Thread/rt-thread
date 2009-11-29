/*-----------------------------------------------------------------------
/  Low level disk interface modlue include file  R0.04a   (C)ChaN, 2007
/-----------------------------------------------------------------------*/

#ifndef __SDCARD_H__
#define __SDCARD_H__

#define _READONLY	0	/* 1: Read-only mode */

#include <rtthread.h>


/* Status of Disk Functions */
typedef rt_uint8_t	DSTATUS;

/* Results of Disk Functions */
typedef enum {
	RES_OK = 0,		/* 0: Successful */
	RES_ERROR,		/* 1: R/W Error */
	RES_WRPRT,		/* 2: Write Protected */
	RES_NOTRDY,		/* 3: Not Ready */
	RES_PARERR		/* 4: Invalid Parameter */
} DRESULT;


/*---------------------------------------*/
/* Prototypes for disk control functions */

DSTATUS disk_initialize (rt_uint8_t);
DSTATUS disk_status (rt_uint8_t);
DRESULT disk_read (rt_uint8_t, rt_uint8_t*, rt_uint32_t, rt_uint8_t);
#if	_READONLY == 0
DRESULT disk_write (rt_uint8_t, const rt_uint8_t*, rt_uint32_t, rt_uint8_t);
#endif
DRESULT disk_ioctl (rt_uint8_t, rt_uint8_t, void*);
void	disk_timerproc (void);

/* Disk Status Bits (DSTATUS) */

#define STA_NOINIT		0x01	/* Drive not initialized */
#define STA_NODISK		0x02	/* No medium in the drive */
#define STA_PROTECT		0x04	/* Write protected */


/* Command code for disk_ioctrl() */

#define GET_SECTOR_COUNT	1
#define GET_SECTOR_SIZE		2
#define CTRL_SYNC			3
#define CTRL_POWER			4
#define CTRL_LOCK			5
#define CTRL_EJECT			6
#define MMC_GET_CSD			10
#define MMC_GET_CID			11
#define MMC_GET_OCR			12
#define ATA_GET_REV			20
#define ATA_GET_MODEL		21
#define ATA_GET_SN			22

#endif
