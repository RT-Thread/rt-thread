/*
 * File      : mmcsd_card.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2011-07-25     weety		first version
 */

#ifndef __MMCSD_CARD_H__
#define __MMCSD_CARD_H__

#include "mmcsd_host.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SD_SCR_BUS_WIDTH_1	(1 << 0)
#define SD_SCR_BUS_WIDTH_4	(1 << 2)

struct rt_mmcsd_cid {
	rt_uint8_t  mid;       /* ManufacturerID */
	rt_uint8_t  prv;       /* Product Revision */
	rt_uint16_t oid;       /* OEM/Application ID */
	rt_uint32_t psn;       /* Product Serial Number */
	rt_uint8_t  pnm[5];    /* Product Name */
	rt_uint8_t  reserved1;/* reserved */
	rt_uint16_t mdt;       /* Manufacturing Date */
	rt_uint8_t  crc;       /* CID CRC */
	rt_uint8_t  reserved2;/* not used, always 1 */
};

struct rt_mmcsd_csd {
	rt_uint8_t		csd_structure;	/* CSD register version */
	rt_uint8_t		taac;
	rt_uint8_t		nsac;
	rt_uint8_t		tran_speed;	/* max data transfer rate */
	rt_uint16_t		card_cmd_class;	/* card command classes */
	rt_uint8_t		rd_blk_len;	/* max read data block length */
	rt_uint8_t		rd_blk_part;
	rt_uint8_t		wr_blk_misalign;
	rt_uint8_t		rd_blk_misalign;
	rt_uint8_t		dsr_imp;	/* DSR implemented */
	rt_uint8_t		c_size_mult;	/* CSD 1.0 , device size multiplier */
	rt_uint32_t		c_size;		/* device size */
	rt_uint8_t		r2w_factor;
	rt_uint8_t		wr_blk_len;	/* max wtire data block length */
	rt_uint8_t		wr_blk_partial;
	rt_uint8_t		csd_crc;
	
};

struct rt_sd_scr {
	rt_uint8_t		sd_version;
	rt_uint8_t		sd_bus_widths;
};

struct rt_mmcsd_card {
	struct rt_mmcsd_host *host;
	rt_uint32_t	rca;		/* card addr */
	rt_uint32_t	resp_cid[4];	/* card CID register */
	rt_uint32_t	resp_csd[4];	/* card CSD register */
	rt_uint32_t	resp_scr[2];	/* card SCR register */

	rt_uint16_t	tacc_clks;	/* data access time by ns */
	rt_uint32_t	tacc_ns;	/* data access time by clk cycles */
	rt_uint32_t	max_data_rate;	/* max data transfer rate */
	rt_uint32_t	card_capacity;	/* card capacity, unit:KB */
	rt_uint32_t	card_blksize;	/* card block size */
	rt_uint32_t	card_type;
#define CARD_TYPE_MMC		(1 << 0)	/* MMC card */
#define CARD_TYPE_SD		(1 << 1)	/* SD card */
#define CARD_TYPE_SDIO		(1 << 2)	/* SDIO card */
#define CARD_TYPE_SDHC		(1 << 3)	/* SDHC card */
	struct rt_sd_scr	scr;
	struct rt_mmcsd_csd	csd;
	rt_uint32_t	hs_max_data_rate;	/* max data transfer rate in high speed mode */
	rt_uint32_t	flags;
#define CARD_MODE_HIGHSPEED	(1 << 0)
};

#ifdef __cplusplus
}
#endif

#endif
