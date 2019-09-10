/*
  This file is part of UFFS, the Ultra-low-cost Flash File System.
  
  Copyright (C) 2005-2009 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

  UFFS is free software; you can redistribute it and/or modify it under
  the GNU Library General Public License as published by the Free Software 
  Foundation; either version 2 of the License, or (at your option) any
  later version.

  UFFS is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
  or GNU Library General Public License, as applicable, for more details.
 
  You should have received a copy of the GNU General Public License
  and GNU Library General Public License along with UFFS; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA  02110-1301, USA.

  As a special exception, if other files instantiate templates or use
  macros or inline functions from this file, or you compile this file
  and link it with other works to produce a work based on this file,
  this file does not by itself cause the resulting work to be covered
  by the GNU General Public License. However the source code for this
  file must still be made available in accordance with section (3) of
  the GNU General Public License v2.
 
  This exception does not invalidate any other reasons why a work based
  on this file might be covered by the GNU General Public License.
*/

/** 
 * \file uffs_flash.c
 * \brief UFFS flash interface
 * \author Ricky Zheng, created 17th July, 2009
 */
#include "uffs_config.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_ecc.h"
#include "uffs/uffs_flash.h"
#include "uffs/uffs_device.h"
#include "uffs/uffs_badblock.h"
#include "uffs/uffs_crc.h"
#include <string.h>

#define PFX "flsh: "

#define SPOOL(dev) &((dev)->mem.spare_pool)
#define HEADER(buf) ((struct uffs_MiniHeaderSt *)(buf)->header)

#define ECC_SIZE(dev)	((dev)->attr->ecc_size)
#define NOMINAL_ECC_SIZE(dev) (3 * ((((dev)->attr->page_data_size - 1) / 256) + 1))

#define TAG_STORE_SIZE	(sizeof(struct uffs_TagStoreSt))

#define SEAL_BYTE(dev, spare)  spare[(dev)->mem.spare_data_size - 1]	// seal byte is the last byte of spare data

#if defined(CONFIG_UFFS_AUTO_LAYOUT_USE_MTD_SCHEME)
/** Linux MTD spare layout for 512 and 2K page size */
static const u8 MTD512_LAYOUT_ECC[] =	{0, 4, 6, 2, 0xFF, 0};
static const u8 MTD512_LAYOUT_DATA[] = {8, 8, 0xFF, 0};
static const u8 MTD2K_LAYOUT_ECC[] = {40, 24, 0xFF, 0};
static const u8 MTD2K_LAYOUT_DATA[] = {2, 38, 0xFF, 0};
#endif

static void TagMakeEcc(struct uffs_TagStoreSt *ts)
{
	ts->tag_ecc = 0xFFF;
	ts->tag_ecc = uffs_EccMake8(ts, sizeof(struct uffs_TagStoreSt));
}

static int TagEccCorrect(struct uffs_TagStoreSt *ts)
{
	u16 ecc_store, ecc_read;
	int ret;

	ecc_store = ts->tag_ecc;
	ts->tag_ecc = 0xFFF;
	ecc_read = uffs_EccMake8(ts, sizeof(struct uffs_TagStoreSt));
	ret = uffs_EccCorrect8(ts, ecc_read, ecc_store, sizeof(struct uffs_TagStoreSt));
	ts->tag_ecc = ecc_store;	// restore tag ecc

	return ret;

}

/** setup UFFS spare data & ecc layout */
static void InitSpareLayout(uffs_Device *dev)
{
	u8 s; // status byte offset
	u8 *p;

	s = dev->attr->block_status_offs;

	if (s < TAG_STORE_SIZE) {	/* status byte is within 0 ~ TAG_STORE_SIZE-1 */

		/* spare data layout */
		p = dev->attr->_uffs_data_layout;
		if (s > 0) {
			*p++ = 0;
			*p++ = s;
		}
		*p++ = s + 1;
		*p++ = TAG_STORE_SIZE - s;
		*p++ = 0xFF;
		*p++ = 0;

		/* spare ecc layout */
		p = dev->attr->_uffs_ecc_layout;
		if (dev->attr->ecc_opt != UFFS_ECC_NONE) {
			*p++ = TAG_STORE_SIZE + 1;
			*p++ = ECC_SIZE(dev);
		}
		*p++ = 0xFF;
		*p++ = 0;
	}
	else {	/* status byte > TAG_STORE_SIZE-1 */

		/* spare data layout */
		p = dev->attr->_uffs_data_layout;
		*p++ = 0;
		*p++ = TAG_STORE_SIZE;
		*p++ = 0xFF;
		*p++ = 0;

		/* spare ecc layout */
		p = dev->attr->_uffs_ecc_layout;
		if (dev->attr->ecc_opt != UFFS_ECC_NONE) {
			if (s < TAG_STORE_SIZE + ECC_SIZE(dev)) {
				if (s > TAG_STORE_SIZE) {
					*p++ = TAG_STORE_SIZE;
					*p++ = s - TAG_STORE_SIZE;
				}
				*p++ = s + 1;
				*p++ = TAG_STORE_SIZE + ECC_SIZE(dev) - s;
			}
			else {
				*p++ = TAG_STORE_SIZE;
				*p++ = ECC_SIZE(dev);
			}
		}
		*p++ = 0xFF;
		*p++ = 0;
	}

	dev->attr->data_layout = dev->attr->_uffs_data_layout;
	dev->attr->ecc_layout = dev->attr->_uffs_ecc_layout;
}

static int CalculateSpareDataSize(uffs_Device *dev)
{
	const u8 *p;
	int ecc_last = 0, tag_last = 0;
	int ecc_size, tag_size;
	int n;

	ecc_size = (dev->attr->ecc_opt == UFFS_ECC_NONE ? 0 : ECC_SIZE(dev));
	
	p = dev->attr->ecc_layout;
	if (p) {
		while (*p != 0xFF && ecc_size > 0) {
			n = (p[1] > ecc_size ? ecc_size : p[1]);
			ecc_last = p[0] + n;
			ecc_size -= n;
			p += 2;
		}
	}

	tag_size = TAG_STORE_SIZE;
	p = dev->attr->data_layout;
	if (p) {
		while (*p != 0xFF && tag_size > 0) {
			n = (p[1] > tag_size ? tag_size : p[1]);
			tag_last = p[0] + n;
			tag_size -= n;
			p += 2;
		}
	}

	n = (ecc_last > tag_last ? ecc_last : tag_last);
	n = (n > dev->attr->block_status_offs + 1 ?
			n : dev->attr->block_status_offs + 1);

	return n + 1;		// plus one seal byte.
}


/**
 * Initialize UFFS flash interface
 */
URET uffs_FlashInterfaceInit(uffs_Device *dev)
{
	URET ret = U_FAIL;
	struct uffs_StorageAttrSt *attr = dev->attr;
	uffs_Pool *pool = SPOOL(dev);

	if (dev->mem.spare_pool_size == 0) {
		if (dev->mem.malloc) {
			dev->mem.spare_pool_buf = dev->mem.malloc(dev, UFFS_SPARE_BUFFER_SIZE);
			if (dev->mem.spare_pool_buf)
				dev->mem.spare_pool_size = UFFS_SPARE_BUFFER_SIZE;
		}
	}

	if (UFFS_SPARE_BUFFER_SIZE > dev->mem.spare_pool_size) {
		uffs_Perror(UFFS_MSG_DEAD,
					"Spare buffer require %d but only %d available.",
					UFFS_SPARE_BUFFER_SIZE, dev->mem.spare_pool_size);
		memset(pool, 0, sizeof(uffs_Pool));
		goto ext;
	}

	uffs_Perror(UFFS_MSG_NOISY,
					"alloc spare buffers %d bytes.",
					UFFS_SPARE_BUFFER_SIZE);
	uffs_PoolInit(pool, dev->mem.spare_pool_buf,
					dev->mem.spare_pool_size,
					UFFS_MAX_SPARE_SIZE, MAX_SPARE_BUFFERS);

	// init flash driver
	if (dev->ops->InitFlash) {
		if (dev->ops->InitFlash(dev) < 0)
			goto ext;
	}

	if (dev->ops->WritePage == NULL && dev->ops->WritePageWithLayout == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS, "Flash driver must provide 'WritePage' or 'WritePageWithLayout' function!");
		goto ext;
	}

	if (dev->ops->ReadPage == NULL && dev->ops->ReadPageWithLayout == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS, "Flash driver must provide 'ReadPage' or 'ReadPageWithLayout' function!");
		goto ext;
	}

	if (dev->attr->layout_opt == UFFS_LAYOUT_UFFS) {
		/* sanity check */

		if (dev->attr->ecc_size == 0 && dev->attr->ecc_opt != UFFS_ECC_NONE) {
			dev->attr->ecc_size = NOMINAL_ECC_SIZE(dev);
		}

		uffs_Perror(UFFS_MSG_NORMAL, "ECC size %d", dev->attr->ecc_size);

		if ((dev->attr->data_layout && !dev->attr->ecc_layout) ||
			(!dev->attr->data_layout && dev->attr->ecc_layout)) {
			uffs_Perror(UFFS_MSG_SERIOUS,
						"Please setup data_layout and ecc_layout, "
						"or leave them all NULL !");
			goto ext;
		}

		if (!attr->data_layout && !attr->ecc_layout) {
#if defined(CONFIG_UFFS_AUTO_LAYOUT_USE_MTD_SCHEME)
			switch(attr->page_data_size) {
			case 512:
				attr->ecc_layout = MTD512_LAYOUT_ECC;
				attr->data_layout = MTD512_LAYOUT_DATA;
				break;
			case 2048:
				attr->ecc_layout = MTD2K_LAYOUT_ECC;
				attr->data_layout = MTD2K_LAYOUT_DATA;
				break;
			default:
				InitSpareLayout(dev);
				break;
			}
#else
			InitSpareLayout(dev);
#endif
		}
	}
	else if (dev->attr->layout_opt == UFFS_LAYOUT_FLASH) {
		if (dev->ops->WritePageWithLayout == NULL || dev->ops->ReadPageWithLayout == NULL) {
			uffs_Perror(UFFS_MSG_SERIOUS, "When using UFFS_LAYOUT_FLASH option, "
				"flash driver must provide 'WritePageWithLayout' and 'ReadPageWithLayout' function!");
			goto ext;
		}
	}
	else {
		uffs_Perror(UFFS_MSG_SERIOUS, "Invalid layout_opt: %d", dev->attr->layout_opt);
		goto ext;
	}

	if (dev->ops->EraseBlock == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS, "Flash driver MUST implement 'EraseBlock()' function !");
		goto ext;
	}

	dev->mem.spare_data_size = CalculateSpareDataSize(dev);
	uffs_Perror(UFFS_MSG_NORMAL, "UFFS consume spare data size %d", dev->mem.spare_data_size);

	if (dev->mem.spare_data_size > dev->attr->spare_size) {
		uffs_Perror(UFFS_MSG_SERIOUS, "NAND spare(%dB) can't hold UFFS spare data(%dB) !",
						dev->attr->spare_size, dev->mem.spare_data_size);
		goto ext;
	}

	ret = U_SUCC;
ext:
	return ret;
}

/**
 * Release UFFS flash interface
 */
URET uffs_FlashInterfaceRelease(uffs_Device *dev)
{
	uffs_Pool *pool;

	pool = SPOOL(dev);
	if (pool->mem && dev->mem.free) {
		dev->mem.free(dev, pool->mem);
		pool->mem = NULL;
		dev->mem.spare_pool_size = 0;
	}
	uffs_PoolRelease(pool);
	memset(pool, 0, sizeof(uffs_Pool));

	// release flash driver
	if (dev->ops->ReleaseFlash) {
		if (dev->ops->ReleaseFlash(dev) < 0)
			return U_FAIL;
	}

	return U_SUCC;
}

/**
 * unload spare to tag and ecc.
 */
void uffs_FlashUnloadSpare(uffs_Device *dev,
						const u8 *spare, struct uffs_TagStoreSt *ts, u8 *ecc)
{
	u8 *p_tag = (u8 *)ts;
	int tag_size = TAG_STORE_SIZE;
	int ecc_size = dev->attr->ecc_size;
	int n;
	const u8 *p;

	// unload ecc
	p = dev->attr->ecc_layout;
	if (p && ecc) {
		while (*p != 0xFF && ecc_size > 0) {
			n = (p[1] > ecc_size ? ecc_size : p[1]);
			memcpy(ecc, spare + p[0], n);
			ecc_size -= n;
			ecc += n;
			p += 2;
		}
	}

	// unload tag
	if (ts) {
		p = dev->attr->data_layout;
		while (*p != 0xFF && tag_size > 0) {
			n = (p[1] > tag_size ? tag_size : p[1]);
			memcpy(p_tag, spare + p[0], n);
			tag_size -= n;
			p_tag += n;
			p += 2;
		}
	}
}

/**
 * Read tag from page spare
 *
 * \param[in] dev uffs device
 * \param[in] block flash block num
 * \param[in] page flash page num
 * \param[out] tag tag to be filled
 *
 * \return	#UFFS_FLASH_NO_ERR: success and/or has no flip bits.
 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
 *			#UFFS_FLASH_ECC_FAIL: spare data has flip bits and ecc correct failed.
 *			#UFFS_FLASH_ECC_OK: spare data has flip bits and corrected by ecc.
*/
int uffs_FlashReadPageTag(uffs_Device *dev,
							int block, int page, uffs_Tags *tag)
{
	uffs_FlashOps *ops = dev->ops;
	u8 * spare_buf;
	int ret = UFFS_FLASH_UNKNOWN_ERR;
	int tmp_ret;
	UBOOL is_bad = U_FALSE;

	spare_buf = (u8 *) uffs_PoolGet(SPOOL(dev));
	if (spare_buf == NULL)
		goto ext;

	if (ops->ReadPageWithLayout) {
		ret = ops->ReadPageWithLayout(dev, block, page, NULL, 0, NULL, tag ? &tag->s : NULL, NULL);
		if (tag)
			tag->seal_byte = (ret == UFFS_FLASH_NOT_SEALED ? 0xFF : 0);
	}
	else {
		ret = ops->ReadPage(dev, block, page, NULL, 0, NULL,
									spare_buf, dev->mem.spare_data_size);

		if (tag) {
			tag->seal_byte = SEAL_BYTE(dev, spare_buf);

			if (!UFFS_FLASH_HAVE_ERR(ret))
				uffs_FlashUnloadSpare(dev, spare_buf, &tag->s, NULL);
		}
	}

	if (UFFS_FLASH_IS_BAD_BLOCK(ret))
		is_bad = U_TRUE;

	if (UFFS_FLASH_HAVE_ERR(ret))
		goto ext;

	if (tag) {
		if (!TAG_IS_SEALED(tag))	// not sealed ? don't try tag ECC correction
			goto ext;

		if (!TAG_IS_VALID(tag)) {
			if (dev->attr->ecc_opt != UFFS_ECC_NONE) {
				/*
				 * There could be a special case if:
				 *  a) tag is sealed (so we are here), and
				 *  b) s.valid == 1 and this bit is a 'bad' bit, and
				 *  c) after tag ECC (corrected by tag ECC) s.valid == 0.
				 *
				 * So we need to try tag ECC (don't treat it as bad block if ECC failed)
				 */

				struct uffs_TagStoreSt s;

				memcpy(&s, &tag->s, sizeof(s));
				tmp_ret = TagEccCorrect(&s);

				if (tmp_ret <= 0 || !TAG_IS_VALID(tag))	// can not corrected by ECC.
					goto ext;
			}
			else {
				goto ext;
			}				
		}

		// do tag ecc correction
		if (dev->attr->ecc_opt != UFFS_ECC_NONE) {
			ret = TagEccCorrect(&tag->s);
			ret = (ret < 0 ? UFFS_FLASH_ECC_FAIL :
					(ret > 0 ? UFFS_FLASH_ECC_OK : UFFS_FLASH_NO_ERR));

			if (UFFS_FLASH_IS_BAD_BLOCK(ret))
				is_bad = U_TRUE;

			if (UFFS_FLASH_HAVE_ERR(ret))
				goto ext;
		}
	}

ext:
	if (is_bad) {
		uffs_BadBlockAdd(dev, block);
		uffs_Perror(UFFS_MSG_NORMAL,
					"A new bad block (%d) is detected.", block);
	}

	if (spare_buf)
		uffs_PoolPut(SPOOL(dev), spare_buf);

	return ret;
}

/**
 * Read page data to buf (do ECC error correction if needed)
 * \param[in] dev uffs device
 * \param[in] block flash block num
 * \param[in] page flash page num of the block
 * \param[out] buf holding the read out data
 * \param[in] skip_ecc skip ecc when reading data from flash
 *
 * \return	#UFFS_FLASH_NO_ERR: success and/or has no flip bits.
 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
 *			#UFFS_FLASH_ECC_FAIL: spare data has flip bits and ecc correct failed.
 *			#UFFS_FLASH_ECC_OK: spare data has flip bits and corrected by ecc.
 *			#UFFS_FLASH_CRC_ERR: CRC verification failed.
 *			#UFFS_FLASH_UNKNOWN_ERR:
 *
 * \note if skip_ecc is U_TRUE, skip CRC as well.
 */
int uffs_FlashReadPage(uffs_Device *dev, int block, int page, uffs_Buf *buf, UBOOL skip_ecc)
{
	uffs_FlashOps *ops = dev->ops;
	struct uffs_StorageAttrSt *attr = dev->attr;
	int size = dev->com.pg_size;
	u8 ecc_buf[UFFS_MAX_ECC_SIZE];
	u8 ecc_store[UFFS_MAX_ECC_SIZE];
	UBOOL is_bad = U_FALSE;
#ifdef CONFIG_ENABLE_PAGE_DATA_CRC
	UBOOL crc_ok = U_TRUE;
#endif
	u8 * spare;

	int ret = UFFS_FLASH_UNKNOWN_ERR;

	spare = (u8 *) uffs_PoolGet(SPOOL(dev));
	if (spare == NULL)
		goto ext;

	if (ops->ReadPageWithLayout) {
		if (skip_ecc)
			ret = ops->ReadPageWithLayout(dev, block, page, buf->header, size, NULL, NULL, NULL);
		else
			ret = ops->ReadPageWithLayout(dev, block, page, buf->header, size, ecc_buf, NULL, ecc_store);
	}
	else {
		if (skip_ecc)
			ret = ops->ReadPage(dev, block, page, buf->header, size, NULL, NULL, 0);
		else
			ret = ops->ReadPage(dev, block, page, buf->header, size, ecc_buf, spare, dev->mem.spare_data_size);
	}

	if (UFFS_FLASH_IS_BAD_BLOCK(ret))
		is_bad = U_TRUE;

	if (UFFS_FLASH_HAVE_ERR(ret))
		goto ext;

#ifdef CONFIG_ENABLE_PAGE_DATA_CRC
	if (!skip_ecc) {
		crc_ok = (HEADER(buf)->crc == uffs_crc16sum(buf->data, size - sizeof(struct uffs_MiniHeaderSt)) ? U_TRUE : U_FALSE);

		if (crc_ok)
			goto ext;	// CRC is matched, no need to do ECC correction.
		else {
			if (dev->attr->ecc_opt == UFFS_ECC_NONE || dev->attr->ecc_opt == UFFS_ECC_HW_AUTO) {
				// ECC is not enabled or ecc correction already done, error return immediately,
				// otherwise, we try CRC check again after ecc correction.
				ret = UFFS_FLASH_CRC_ERR;
				goto ext;
			}
		}
	}
#endif

	// make ECC for UFFS_ECC_SOFT
	if (attr->ecc_opt == UFFS_ECC_SOFT && !skip_ecc)
		uffs_EccMake(buf->header, size, ecc_buf);

	// unload ecc_store if driver doesn't do the layout
	if (ops->ReadPageWithLayout == NULL) {
		if (!skip_ecc && (attr->ecc_opt == UFFS_ECC_SOFT || attr->ecc_opt == UFFS_ECC_HW))
			uffs_FlashUnloadSpare(dev, spare, NULL, ecc_store);
	}

	// check page data ecc
	if (!skip_ecc && (dev->attr->ecc_opt == UFFS_ECC_SOFT || dev->attr->ecc_opt == UFFS_ECC_HW)) {

		ret = uffs_EccCorrect(buf->header, size, ecc_store, ecc_buf);
		ret = (ret < 0 ? UFFS_FLASH_ECC_FAIL :
				(ret > 0 ? UFFS_FLASH_ECC_OK : UFFS_FLASH_NO_ERR));

		if (UFFS_FLASH_IS_BAD_BLOCK(ret))
			is_bad = U_TRUE;

		if (UFFS_FLASH_HAVE_ERR(ret))
			goto ext;
	}

#ifdef CONFIG_ENABLE_PAGE_DATA_CRC
	if (!skip_ecc && !UFFS_FLASH_HAVE_ERR(ret)) {
		// Everything seems ok, do CRC check again.
		if (HEADER(buf)->crc == uffs_crc16sum(buf->data, size - sizeof(struct uffs_MiniHeaderSt))) {
			ret = UFFS_FLASH_CRC_ERR;
			goto ext;
		}
	}
#endif

ext:
	switch(ret) {
		case UFFS_FLASH_IO_ERR:
			uffs_Perror(UFFS_MSG_NORMAL, "Read block %d page %d I/O error", block, page);
			break;
		case UFFS_FLASH_ECC_FAIL:
			uffs_Perror(UFFS_MSG_NORMAL, "Read block %d page %d ECC failed", block, page);
			ret = UFFS_FLASH_BAD_BLK;	// treat ECC FAIL as BAD BLOCK
			is_bad = U_TRUE;
			break;
		case UFFS_FLASH_ECC_OK:
			uffs_Perror(UFFS_MSG_NORMAL, "Read block %d page %d bit flip corrected by ECC", block, page);
			break;
		case UFFS_FLASH_BAD_BLK:
			uffs_Perror(UFFS_MSG_NORMAL, "Read block %d page %d BAD BLOCK found", block, page);
			break;
		case UFFS_FLASH_UNKNOWN_ERR:
			uffs_Perror(UFFS_MSG_NORMAL, "Read block %d page %d UNKNOWN error!", block, page);
			break;
		case UFFS_FLASH_CRC_ERR:
			uffs_Perror(UFFS_MSG_NORMAL, "Read block %d page %d CRC failed", block, page);
			break;
		default:
			break;
	}

	if (is_bad)
		uffs_BadBlockAdd(dev, block);

	if (spare)
		uffs_PoolPut(SPOOL(dev), spare);


	return ret;
}

/**
 * make spare from tag and ecc
 *
 * \param[in] dev uffs dev
 * \param[in] ts uffs tag store, NULL if don't pack tag store
 * \param[in] ecc ecc of data, NULL if don't pack ecc
 * \param[out] spare output buffer
 * \note spare buffer size: dev->mem.spare_data_size,
 *		 all unpacked bytes will be inited 0xFF
 */
void uffs_FlashMakeSpare(uffs_Device *dev,
						 const uffs_TagStore *ts, const u8 *ecc, u8* spare)
{
	u8 *p_ts = (u8 *)ts;
	int ts_size = TAG_STORE_SIZE;
	int ecc_size = ECC_SIZE(dev);
	int n;
	const u8 *p;

	if (!uffs_Assert(spare != NULL, "invalid param"))
		return;

	memset(spare, 0xFF, dev->mem.spare_data_size);	// initialize as 0xFF.
	SEAL_BYTE(dev, spare) = 0;						// set seal byte = 0.

	// load ecc
	p = dev->attr->ecc_layout;
	if (p && ecc) {
		while (*p != 0xFF && ecc_size > 0) {
			n = (p[1] > ecc_size ? ecc_size : p[1]);
			memcpy(spare + p[0], ecc, n);
			ecc_size -= n;
			ecc += n;
			p += 2;
		}
	}

	p = dev->attr->data_layout;
	while (*p != 0xFF && ts_size > 0) {
		n = (p[1] > ts_size ? ts_size : p[1]);
		memcpy(spare + p[0], p_ts, n);
		ts_size -= n;
		p_ts += n;
		p += 2;
	}

	uffs_Assert(SEAL_BYTE(dev, spare) == 0, "Make spare fail!");
}

/**
 * write the whole page, include data and tag
 *
 * \param[in] dev uffs device
 * \param[in] block
 * \param[in] page
 * \param[in] buf contains data to be wrote
 * \param[in] tag tag to be wrote
 *
 * \return	#UFFS_FLASH_NO_ERR: success.
 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
 *			#UFFS_FLASH_BAD_BLK: a new bad block detected.
 */
int uffs_FlashWritePageCombine(uffs_Device *dev,
							   int block, int page,
							   uffs_Buf *buf, uffs_Tags *tag)
{
	uffs_FlashOps *ops = dev->ops;
	int size = dev->com.pg_size;
	u8 ecc_buf[UFFS_MAX_ECC_SIZE];
	u8 *ecc = NULL;
	u8 *spare;
	struct uffs_MiniHeaderSt *header;
	int ret = UFFS_FLASH_UNKNOWN_ERR;
	UBOOL is_bad = U_FALSE;
	uffs_Buf *verify_buf;
#ifdef CONFIG_PAGE_WRITE_VERIFY
	uffs_Tags chk_tag;
#endif
	
	spare = (u8 *) uffs_PoolGet(SPOOL(dev));
	if (spare == NULL)
		goto ext;

	// setup header
	header = HEADER(buf);
	memset(header, 0xFF, sizeof(struct uffs_MiniHeaderSt));
	header->status = 0;
#ifdef CONFIG_ENABLE_PAGE_DATA_CRC
	header->crc = uffs_crc16sum(buf->data, size - sizeof(struct uffs_MiniHeaderSt));
#endif

	// setup tag
	TAG_DIRTY_BIT(tag) = TAG_DIRTY;		//!< set dirty bit
	TAG_VALID_BIT(tag) = TAG_VALID;		//!< set valid bit
	SEAL_TAG(tag);						//!< seal tag (the real seal byte will be set in uffs_FlashMakeSpare())

	if (dev->attr->ecc_opt != UFFS_ECC_NONE)
		TagMakeEcc(&tag->s);
	else
		tag->s.tag_ecc = TAG_ECC_DEFAULT;
	
	if (dev->attr->ecc_opt == UFFS_ECC_SOFT) {
		uffs_EccMake(buf->header, size, ecc_buf);
		ecc = ecc_buf;
	}
	else if (dev->attr->ecc_opt == UFFS_ECC_HW) {
		ecc = ecc_buf;
	}

	if (ops->WritePageWithLayout) {
		ret = ops->WritePageWithLayout(dev, block, page,
							buf->header, size, ecc, &tag->s);
	}
	else {

		if (!uffs_Assert(!(dev->attr->layout_opt == UFFS_LAYOUT_FLASH ||
					dev->attr->ecc_opt == UFFS_ECC_HW ||
					dev->attr->ecc_opt == UFFS_ECC_HW_AUTO), "WritePageWithLayout() not implemented ?")) {
			ret = UFFS_FLASH_IO_ERR;
			goto ext;
		}

		uffs_FlashMakeSpare(dev, &tag->s, ecc, spare);

		ret = ops->WritePage(dev, block, page, buf->header, size, spare, dev->mem.spare_data_size);

	}
	
	if (UFFS_FLASH_IS_BAD_BLOCK(ret))
		is_bad = U_TRUE;

	if (UFFS_FLASH_HAVE_ERR(ret))
		goto ext;

#ifdef CONFIG_PAGE_WRITE_VERIFY
	verify_buf = uffs_BufClone(dev, NULL);
	if (verify_buf) {
		ret = uffs_FlashReadPage(dev, block, page, verify_buf, U_FALSE);
		if (!UFFS_FLASH_HAVE_ERR(ret)) {
			if (memcmp(buf->header, verify_buf->header, size) != 0) {
				uffs_Perror(UFFS_MSG_NORMAL,
							"Page write verify failed (block %d page %d)",
							block, page);
				ret = UFFS_FLASH_BAD_BLK;
			}
		}

		uffs_BufFreeClone(dev, verify_buf);
	}
	else {
		uffs_Perror(UFFS_MSG_SERIOUS, "Insufficient buf, clone buf failed.");
	}

	ret = uffs_FlashReadPageTag(dev, block, page, &chk_tag);
	if (UFFS_FLASH_HAVE_ERR(ret))
		goto ext;
	
	if (memcmp(&tag->s, &chk_tag.s, sizeof(uffs_TagStore)) != 0) {
		uffs_Perror(UFFS_MSG_NORMAL, "Page tag write verify failed (block %d page %d)",
					block, page);
		ret = UFFS_FLASH_BAD_BLK;
	}

	if (UFFS_FLASH_IS_BAD_BLOCK(ret))
		is_bad = U_TRUE;
	
#endif
ext:
	if (is_bad)
		uffs_BadBlockAdd(dev, block);

	if (spare)
		uffs_PoolPut(SPOOL(dev), spare);

	return ret;
}

/**
 * mark a clean page tag as 'dirty' and 'invalid'.
 *
 * \param[in] dev uffs device
 * \param[in] bc block info
 * \param[in] page
 *
 * \return	#UFFS_FLASH_NO_ERR: success.
 *			#UFFS_FLASH_IO_ERR: I/O error, expect retry ?
 *			#UFFS_FLASH_BAD_BLK: a new bad block detected.
 */
int uffs_FlashMarkDirtyPage(uffs_Device *dev, uffs_BlockInfo *bc, int page)
{
	u8 *spare;
	uffs_FlashOps *ops = dev->ops;
	UBOOL is_bad = U_FALSE;
	int ret = UFFS_FLASH_UNKNOWN_ERR;
	int block = bc->block;
	uffs_Tags *tag = GET_TAG(bc, page);
	struct uffs_TagStoreSt *ts = &tag->s;

	spare = (u8 *) uffs_PoolGet(SPOOL(dev));
	if (spare == NULL)
		goto ext;

	memset(ts, 0xFF, sizeof(struct uffs_TagStoreSt));
	ts->dirty = TAG_DIRTY;  // set only 'dirty' bit, leave 'valid' bit to 1 (invalid).
	
	if (dev->attr->ecc_opt != UFFS_ECC_NONE)
		TagMakeEcc(ts);

	if (ops->WritePageWithLayout) {
		ret = ops->WritePageWithLayout(dev, block, page, NULL, 0, NULL, ts);
	}
	else {
		uffs_FlashMakeSpare(dev, ts, NULL, spare);
		ret = ops->WritePage(dev, block, page, NULL, 0, spare, dev->mem.spare_data_size);
	}

	if (UFFS_FLASH_IS_BAD_BLOCK(ret))
		is_bad = U_TRUE;

ext:
	if (is_bad)
		uffs_BadBlockAdd(dev, block);

	if (spare)
		uffs_PoolPut(SPOOL(dev), spare);

	return ret;
}

/** Mark this block as bad block */
URET uffs_FlashMarkBadBlock(uffs_Device *dev, int block)
{
	int ret;
	uffs_BlockInfo *bc;

	uffs_Perror(UFFS_MSG_NORMAL, "Mark bad block: %d", block);

	bc = uffs_BlockInfoGet(dev, block);
	if (bc) {
		uffs_BlockInfoExpire(dev, bc, UFFS_ALL_PAGES);	// expire this block, just in case it's been cached before
		uffs_BlockInfoPut(dev, bc);
	}

	if (dev->ops->MarkBadBlock)
		return dev->ops->MarkBadBlock(dev, block) == 0 ? U_SUCC : U_FAIL;

#ifdef CONFIG_ERASE_BLOCK_BEFORE_MARK_BAD
	ret = dev->ops->EraseBlock(dev, block);
	if (ret != UFFS_FLASH_IO_ERR) {
		// note: even EraseBlock return UFFS_FLASH_BAD_BLK,
		//			we still process it ... not recommended for most NAND flash.
#endif
	if (dev->ops->WritePageWithLayout)
		ret = dev->ops->WritePageWithLayout(dev, block, 0, NULL, 0, NULL, NULL);
	else
		ret = dev->ops->WritePage(dev, block, 0, NULL, 0, NULL, 0);

#ifdef CONFIG_ERASE_BLOCK_BEFORE_MARK_BAD
	}
#endif

	return ret == UFFS_FLASH_NO_ERR ? U_SUCC : U_FAIL;
}

/** Is this block a bad block ? */
UBOOL uffs_FlashIsBadBlock(uffs_Device *dev, int block)
{
	struct uffs_FlashOpsSt *ops = dev->ops;
	UBOOL ret = U_FALSE;

	if (ops->IsBadBlock) {
		/* if flash driver provide 'IsBadBlock' function, call it */
		ret = (ops->IsBadBlock(dev, block) == 0 ? U_FALSE : U_TRUE);
	}
	else {
		/* otherwise we call ReadPage[WithLayout]() to get bad block status byte */
		/* check the first page */
		if (ops->ReadPageWithLayout) {
			ret = (ops->ReadPageWithLayout(dev, block, 0, NULL, 0, NULL, NULL, NULL)
												== UFFS_FLASH_BAD_BLK ? U_TRUE : U_FALSE);
		}
		else {
			ret = (ops->ReadPage(dev, block, 0, NULL, 0, NULL, NULL, 0)
												== UFFS_FLASH_BAD_BLK ? U_TRUE : U_FALSE);
		}

		if (ret == U_FALSE) {
			/* check the second page */
			if (ops->ReadPageWithLayout) {
				ret = (ops->ReadPageWithLayout(dev, block, 0, NULL, 0, NULL, NULL, NULL) 
													== UFFS_FLASH_BAD_BLK ? U_TRUE : U_FALSE);
			}
			else {
				ret = (ops->ReadPage(dev, block, 0, NULL, 0, NULL, NULL, 0)
													== UFFS_FLASH_BAD_BLK ? U_TRUE : U_FALSE);
			}
		}
	}

	//uffs_Perror(UFFS_MSG_NOISY, "Block %d is %s", block, ret ? "BAD" : "GOOD");

	return ret;
}

/** Erase flash block */
URET uffs_FlashEraseBlock(uffs_Device *dev, int block)
{
	int ret;
	uffs_BlockInfo *bc;

	ret = dev->ops->EraseBlock(dev, block);

	if (UFFS_FLASH_IS_BAD_BLOCK(ret))
		uffs_BadBlockAdd(dev, block);

	bc = uffs_BlockInfoGet(dev, block);
	if (bc) {
		uffs_BlockInfoExpire(dev, bc, UFFS_ALL_PAGES);
		uffs_BlockInfoPut(dev, bc);
	}
	return UFFS_FLASH_HAVE_ERR(ret) ? U_FAIL : U_SUCC;
}

/**
 * Check the block by reading all pages.
 *
 * \return U_SUCC - all pages are clean,
 *         U_FAIL - block is not clean
 */
URET uffs_FlashCheckErasedBlock(uffs_Device *dev, int block)
{
	u8 *spare = NULL;
	uffs_FlashOps *ops = dev->ops;
	int ret = U_SUCC;
	int page;
	int flash_ret;
	u8 ecc_store[UFFS_MAX_ECC_SIZE];
	uffs_TagStore ts;
	uffs_Buf *buf = NULL;
	int size = dev->com.pg_size;
	int i;
	u8 *p;
	
	spare = (u8 *) uffs_PoolGet(SPOOL(dev));
	
	if (spare == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS, "Can't allocate spare buf.");
		goto ext;
	}
	
	buf = uffs_BufClone(dev, NULL);
	
	if (buf == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS, "Can't clone buf.");
		goto ext;
	}
	
	for (page = 0; page < dev->attr->pages_per_block; page++) {
		if (ops->ReadPageWithLayout) {
			
			flash_ret = ops->ReadPageWithLayout(dev, block, page, buf->header, size, NULL, &ts, ecc_store);
			
			if (flash_ret != UFFS_FLASH_IO_ERR) {
				// check page tag, should be all 0xFF
				for (i = 0, p = (u8 *)(&ts); i < sizeof(ts); i++, p++) {
					if (*p != 0xFF) {
						ret = U_FAIL;
						goto ext;
					}
				}
				
				// for hw or soft ecc, check stored ecc, should be all 0xFF
				if (dev->attr->ecc_opt == UFFS_ECC_HW ||
					dev->attr->ecc_opt == UFFS_ECC_SOFT)
				{
					for (i = 0, p = ecc_store; i < ECC_SIZE(dev); i++, p++) {
						if (*p != 0xFF) {
							ret = U_FAIL;
							goto ext;
						}
					}
				}
			}
		}
		else {
			
			flash_ret = ops->ReadPage(dev, block, page, buf->header, size, NULL, spare, dev->attr->spare_size);
			if (flash_ret != UFFS_FLASH_IO_ERR) {
				// check spare data, should be all 0xFF
				for (i = 0, p = spare; i < dev->attr->spare_size; i++, p++) {
					if (*p != 0xFF) {
						ret = U_FAIL;
						goto ext;
					}
				}
			}
		}
		
		if (flash_ret != UFFS_FLASH_IO_ERR) {
			// check page data, should be all 0xFF
			for (i = 0, p = buf->header; i < size; i++, p++) {
				if (*p != 0xFF) {
					ret = U_FAIL;
					goto ext;
				}
			}
		}
		
	}
	

ext:
	if (spare)
		uffs_PoolPut(SPOOL(dev), spare);
	
	if (buf)
		uffs_BufFreeClone(dev, buf);
	
	
	return ret;
}

