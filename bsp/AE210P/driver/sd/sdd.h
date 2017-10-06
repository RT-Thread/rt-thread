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
 *   sdd.h
 *
 * DESCRIPTION
 *
 *   SD driver implementation kernel mode header file.
 *   (Nucleus I/O Driver Architecture)
 *
 * DATA STRUCTURES
 *
 *   None
 *
 * DEPENDENCIES
 *
 *   sd.h           SD driver interface exported to user applications
 *   ag101regs.h    SoC register address header file
 *   ag101defs.h    SoC register constant definition header file
 *
 ****************************************************************************/
#ifndef __SDD_H__
#define __SDD_H__

#include <hal.h>
#include <dma/dmad.h>
#include "sd.h"

/* configuration section */
/* Note: SD clock -- please check "ag101defs.h". */
#define SDD_SMALL_FOOTPRINT             0	/* non-zero to disable extra features for small footprint */
#define SDD_SMALL_SD_FOOTPRINT          0	/* non-zero to skip compiling and linking of unsed SD command routines. */
#define SDD_DEBUG_TRACE                 0	/* non-zero to enable debug trace message */
#define SDD_VFS_SUPPORT                 1       /* non-zero to enable VFS support */

/* Define sector size that should be common for all file systems. */
/* Todo: Check if this the common case. */
#define SDD_SECTOR_SIZE             512
#define SDD_POWER_OF_SECTOR_SIZE    9
#define SDD_BYTES_TO_SECTORS(b)     ((uint32_t)(b) >> 9)

/* SDD enums */
typedef enum _SDD_CARD_SPEC {

	SDD_SPEC_1XX,		/* the card is a spec 1.x implementation */
	SDD_SPEC_200		/* the card is a spec 2.0 implementation */

} SDD_CARD_SPEC;

typedef enum _SDD_CARD_CCS {

	SDD_CCS_SD,		/* the card is a standard capacity card */
	SDD_CCS_SDHC		/* the card is a high capacity card */

} SDD_CARD_CCS;

typedef enum _SDD_VDD_WINDOW {

	SDD_VDD_2_7 = 0x00008000,	/* VDD 2.7 ~ 2.8 */
	SDD_VDD_2_8 = 0x00010000,	/* VDD 2.8 ~ 2.9 */
	SDD_VDD_2_9 = 0x00020000,	/* VDD 2.9 ~ 3.0 */
	SDD_VDD_3_0 = 0x00040000,	/* VDD 3.0 ~ 3.1 */
	SDD_VDD_3_1 = 0x00080000,	/* VDD 3.1 ~ 3.2 */
	SDD_VDD_3_2 = 0x00100000,	/* VDD 3.2 ~ 3.3 */
	SDD_VDD_3_3 = 0x00200000,	/* VDD 3.3 ~ 3.4 */
	SDD_VDD_3_4 = 0x00400000,	/* VDD 3.4 ~ 3.5 */
	SDD_VDD_3_5 = 0x00800000,	/* VDD 3.5 ~ 3.6 */

} SDD_VDD_WINDOW;

/*
 * SD card device parameters
 * Note:
 *  1. This struct supports a single card.
 *  2. Watch out 32-bit alignment after remarking unnecessary fields.
 */
typedef struct _SDD_CARD_DESC {

	/* OCR (acmd41) */
	uint8_t version;		/* one of the enum value of SDD_CARD_SPEC */
	uint8_t card_ccs;		/* one of the enum value of SDD_CARD_CCS */
	uint8_t padding1[2];
	uint32_t vdd_window;		/* one of the mask bits defined in SDD_VDD_WINDOW */

	/* CID (cmd2) */
	uint8_t mfg_id;			/* Manufacturer ID */
	char oem_id[3];			/* OEM/Application ID (2 char + 1 null-sz) */
	char prod_name[6];		/* Product name (5 char + 1 null-sz) */
	char prod_rev[4];		/* Product revision (x.y + 1 null-sz) */
	uint8_t padding2[2];
	uint32_t prod_sn;		/* Product serial number */
	uint16_t mfg_year;		/* Manufacturing date */
	uint16_t mfg_month;

	/* RCA (cmd3) */
	uint32_t rca;			/* [31:16] RCA, [15:0] zero. */

	/*
	 * Driver will check this before data transfer. */
	/* CSD (cmd9) */
	/* Todo: This is a tedious list and most fields are only for information purpose. */
	/*       Remove unnecessary fields after debugging. */
	uint8_t csd_ver;		/* CSD version */
	uint8_t padding3[3];

	uint32_t async_access_time;	/* data read access time 1 (TAAC, x10, unit of ns) (2.0 is fixed value) */
	uint32_t read_access_clks;	/* data read access time 2 (NSAC, clock cycles) (2.0 is fixed value) */
	uint32_t prog_factor;		/* multiplication factor of time for typical block program (2.0 is fixed value) */
	uint32_t max_dataline_rate;	/* max data transfer rate (unit of kbps) (2.0 is fixed value) */

	uint32_t cmd_class;		/* card command classes */

	uint16_t max_read_block_len;	/* read block length in bytes (2.0 is fixed value) */
	uint8_t partial_block_read;	/* non-zero if the card supports small block size (minimum to 1 bytes) (2.0 is fixed value) */
	uint8_t read_block_misalign;	/* capability to read accross physical blocks (2.0 is fixed value) */

	uint16_t max_write_block_len;	/* write block length in bytes (2.0 is fixed value) */
	uint8_t partial_block_write;	/* non-zero if the card supports small block size (minimum to 1 bytes) (2.0 is fixed value) */
	uint8_t write_block_misalign;	/* capability to write accross physical blocks (2.0 is fixed value) */

	uint8_t erase_single_block;	/* non-zero if able to erase single block (2.0 is fixed value) */
	uint8_t erase_sector_size;	/* erase unit, number of write block size (not the meaning of disk sectors) (2.0 is fixed value) */
	uint8_t file_format;		/* enum of SDD_FILE_FORMAT (2.0 is fixed value) */
	uint8_t padding4;

	uint8_t wp_group_size;		/* write protect group size, number of erase sector size. (2.0 is fixed value) */
	uint8_t wp_group_enable;	/* zero means no group write protection possible (2.0 is fixed value) */
	uint8_t wp_permanent;		/* card is permanently write protected */
	uint8_t wp_temp;		/* card is temporarily write protected */

	uint8_t copy;			/* indicates if the content is original (0) or copied (1 for OTP/MTP devices) */
	uint8_t dsr_imp;		/* non-zero if configurable driver stage register is supported */
	uint32_t c_size;		/* C_SIZE */
	uint32_t c_size_mult;		/* C_SIZE_MULT (2.0 is obsolete) */

#if 0
	uint8_t max_c_read_at_vdd_min;	/* max read current at vdd min (2.0 is obsolete) */
	uint8_t max_c_read_at_vdd_max;	/* max read current at vdd max (2.0 is obsolete) */
	uint8_t max_c_write_at_vdd_min;	/* max write current at vdd min (2.0 is obsolete) */
	uint8_t max_c_write_at_vdd_max;	/* max write current at vdd max (2.0 is obsolete) */
#endif

	/* SCR (acmd51) */
	uint8_t scr_ver;		/* SCR version */
	uint8_t spec_ver;		/* SD memory card spec version */
	uint8_t erase_val;		/* data status after erase (0 or 1) */
	uint8_t security_ver;		/* security specification version */
	uint8_t bus_width;		/* data bus width, 1 or 4. */

	/* derived fields */
	uint32_t card_capacity;		/* card size, in unit of 512-bytes */
	uint32_t sdc_clk_div;		/* clock division value to setup SDC SDC_CLK_DIV register */
	uint32_t sdc_clk_freq;		/* SDC clock frequency (info only) */
	uint32_t read_timeout_clks;	/* read timeout value to setup SDC DATA_TIMER register (fixed 100ms for SDHC) */
	uint32_t write_timeout_clks;	/* write timeout value to setup SDC DATA_TIMER register (fixed 250ms for SDHC) */

} SDD_CARD_DESC;

/* HISR definitions */
#define SDD_HISR_PRIORITY       0	/* 0: highest, 2: lowest */
#define SDD_HISR_STACK_SIZE     2048	/* Please align to 32-bit */

enum SDD_HISR_AS {

	SDD_HISR_AS_CD = 0x00000001,	/* Card Detect */

};

/* Driver data structure, one instance per system */
typedef struct SDD_DATA_STRUCT {

	uint8_t valid;			/* Indicates whether the device driver is instanciated or not */
	uint8_t lisr_registered;	/* SD cd LISR registeration status */
	uint8_t hisr_registered;	/* SD cd HISR registeration status */
	uint8_t dma;			/* One of the enum value in SDD_DMA_MODE for SD data transfer */

	SDD_CARD_DESC card_desc;	/* SD card parameters obtained from various card registers. */

	hal_mutex_t semaphore;		/* control exclusive access to driver */
	hal_semaphore_t dma_sem;	/* obtain dma completion notification from DMA hisr */

	/* HISR resources */
	hal_bh_t hisr;			/* HISR kernel object, used to perform deffered tasks of LISR */
	uint32_t hisr_as;		/* HISR activation state (for the single HISR to identify why activated it) */

	/* DMA resources */
	DMAD_CHANNEL_REQUEST_DESC dma_ch;	/* DMA channel descriptor initialized before data transfer */

} SDD_DATA;

/* Driver-occupied memory pool definitions */
#define SDD_MEM_POOL_BASE_SIZE          40960	/* base pool size for driver before counting size of ? */
#define SDD_MEM_ALLOC_GRANULARITY       8

/* Debug trace mechanism */
#if (SDD_DEBUG_TRACE)

#define SDD_TRACE(x)	      printf x
#define SDD_STRACE(x)	      printf x

#else /* SDD_DEBUG_TRACE */

#define SDD_TRACE(x)
#define SDD_STRACE(x)

#endif /* SDD_DEBUG_TRACE */

#endif /* __SDD_H__ */
