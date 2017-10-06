/*****************************************************************************
 *
 *            Copyright Andes Technology Corporation 2007-2008
 *                         All Rights Reserved.
 *
 *  Revision History:
 *
 *    Aug.21.2007     Created.
 ****************************************************************************/

/*****************************************************************************
 *
 * FILE NAME                                         VERSION
 *
 *   sd.h                     
 *
 * DESCRIPTION
 *
 *   SD controller driver interfaces for client applications.
 *   (Nucleus I/O Driver Architecture)
 *
 * DATA STRUCTURES
 *
 *   None
 *
 * DEPENDENCIES
 *
 *   ag101regs.h
 *   ag101defs.h
 *
 ****************************************************************************/
#ifndef __SD_H__
#define __SD_H__

#include <inttypes.h>
/*
 * SDD I/O control code, used for clients not using driver wrapper routines,
 * i.e., when not using middle-ware interfaces.  Driver implementation target
 * is that almost every IOCTL should exist a corresponding wrapper routine.
 */
typedef enum SDD_IOCTL {
	SDD_IOCTL_READ_SECTORS,		/* Parameter: pointer to SDD_IOCTL_READ_SECTORS_PARAM struct */
	SDD_IOCTL_WRITE_SECTORS,	/* Parameter: pointer to SDD_IOCTL_WRITE_SECTORS_PARAM struct */
} SDD_IOCTL;

/* Parameter struct for SDD_IOCTL_ */
typedef struct _SDD_IOCTL_READ_SECTORS_PARAM {

	uint32_t lba_sector;	/* start sector number */
	uint32_t sector_count;	/* number of sectors included in this operation */
	uint32_t sector_size;	/* sector size in bytes */
	void *io_buff;		/* buffer pointer */

} SDD_IOCTL_READ_SECTORS_PARAM;

typedef struct _SDD_IOCTL_WRITE_SECTORS_PARAM {

	uint32_t lba_sector;	/* start sector number */
	uint32_t sector_count;	/* number of sectors included in this operation */
	uint32_t sector_size;	/* sector size in bytes */
	void *io_buff;		/* buffer pointer */

} SDD_IOCTL_WRITE_SECTORS_PARAM;

typedef enum SDD_EVENTS {

	SDD_EVENT_CD = 0x00000001,	/* Card-detection event. Event parameter: SDD_CD_EVENT */

} SDD_EVENTS;

typedef enum SDD_CD_EVENT_PARAM {
	SDD_CD_CARD_INSERTED = 1,
	SDD_CD_CARD_REMOVED = 0,

} SDD_CD_EVENT_PARAM;

typedef enum SDD_DMA_MODE {
	SDD_DMA_NONE = 0,	/* no dma, deivce i/o is through pio */
	SDD_DMA_DCH = 1,	/* dma channel is dynamically allocated on i/o request and get free after dma. */
	SDD_DMA_SCH = 2,	/* dma channel is allocated and occupied during device initialization. */

} SDD_DMA_MODE;

/* Define data structures for management of CF device. */
typedef struct SDD_DEVICE_STRUCT {

	void *bdev_id;		/* (reserved) The block device context. This field is reserved by the driver. */
	uint8_t dma;		/* (in)  one of the enum value in SDD_DMA_MODE. */
	uint8_t func;		/* (in)  (Reserved currently) Preferred SD card function mode (SD Memory, SD/IO, SPI) */
	uint8_t padding[2];	/* stuff bytes */

} SDD_DEVICE;

/*****************************************************************************
 * Note: Everything below is designed as an interface wrapper to access 
 *       SD driver.
 *
 * [Structures]
 *
 * [Functions]
 *
 *
 ****************************************************************************/

/* driver generic error code for SDC */
#define SDD_SUCCESS              0x00
#define SDD_INVALID_INIT         0x01
#define SDD_INVALID_REQUEST      0x02
#define SDD_NOT_SUPPORTED        0x03

#define SDD_INVALID_FUNCTION     0x11
#define SDD_INVALID_PARAMETER    0x12
#define SDD_CARD_REMOVED         0x13
#define SDD_INVALID_MEDIA        0x14
#define SDD_INVALID_IOCTL        0x15
#define SDD_WRITE_DATA_ERROR     0x16
#define SDD_READ_DATA_ERROR      0x17
#define SDD_INVLAID_ADDRESS      0x18
#define SDD_INVLAID_ADDR_RANGE   0x19

#define SDD_CMD_TIMEOUT          0x21
#define SDD_CMD_ERROR            0x22
#define SDD_RSP_TIMEOUT          0x23
#define SDD_RSP_CRC_ERROR        0x24
#define SDD_NOT_SUPPORT_ACMD     0x25
#define SDD_CSR_ERROR            0x26
#define SDD_INVALID_STATE        0x27
#define SDD_WAIT_TIMEOUT         0x28
#define SDD_WRITE_PROTECTED      0x29
#define SDD_CARD_LOCKED          0x30

extern void _sdd_lisr(int vector);
extern void _sdd_hisr(void *param);
extern uint32_t NDS_SD_Init(SDD_DEVICE * sdd_dev);
extern void NDS_SD_Unload(void);
extern uint32_t NDS_SD_ReadSectors(SDD_DEVICE * sdd_dev, uint32_t sector,
				   uint32_t sector_count, uint32_t sector_size,
				   void *buffer);
extern uint32_t NDS_SD_WriteSectors(SDD_DEVICE * sdd_dev, uint32_t sector,
				    uint32_t sector_count, uint32_t sector_size,
				    void *buffer);

#endif /* __SD_H__ */
