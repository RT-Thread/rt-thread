/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright (C) 2001-2003 Red Hat, Inc.
 *
 * Created by Dominic Ostrowski <dominic.ostrowski@3glab.com>
 * Contributors: David Woodhouse, Nick Garnett, Richard Panton.
 *
 * For licensing information, see the file 'LICENCE' in this directory.
 *
 * $Id: flashio.c,v 1.1 2003/11/26 14:09:29 dwmw2 Exp $
 *
 */

#include <linux/kernel.h>
#include "nodelist.h"
#include <rtdevice.h>

int jffs2_flash_read(struct jffs2_sb_info * c, cyg_uint32 offset,
		const size_t size,
		size_t * return_size,
		unsigned char *buffer)
{
	uint32_t len;
	struct super_block *sb = OFNI_BS_2SFFJ(c);

	len = rt_mtd_nor_read(RT_MTD_NOR_DEVICE(sb->s_dev), offset, buffer, size);
	if (len != size)
		return -EIO;

	* return_size = len;
	return ENOERR;
}

int jffs2_flash_write(struct jffs2_sb_info * c,
		cyg_uint32 offset, const size_t size,
		size_t * return_size, unsigned char *buffer)
{
	uint32_t len;
	struct super_block *sb = OFNI_BS_2SFFJ(c);

	len = rt_mtd_nor_write(RT_MTD_NOR_DEVICE(sb->s_dev), offset, buffer, size);
	if (len != size)
		return -EIO;

	* return_size = len;
	return ENOERR;
}

int jffs2_flash_erase(struct jffs2_sb_info * c,
		struct jffs2_eraseblock * jeb)
{
	rt_err_t result;
	struct super_block *sb = OFNI_BS_2SFFJ(c);

	result = rt_mtd_nor_erase_block(RT_MTD_NOR_DEVICE(sb->s_dev), jeb->offset, c->sector_size);
	if (result != RT_EOK)
		return -EIO;

	return ENOERR;
}

int jffs2_flash_direct_writev(struct jffs2_sb_info *c,
		const struct iovec *vecs, unsigned long count, loff_t to,
		size_t * retlen)
{
	unsigned long i;
	size_t totlen = 0, thislen;
	int ret = 0;

	for (i = 0; i < count; i++)
	{
		// writes need to be aligned but the data we're passed may not be
		// Observation suggests most unaligned writes are small, so we
		// optimize for that case.

		if (((vecs[i].iov_len & (sizeof(int) - 1))) ||
			(((unsigned long) vecs[i].iov_base & (sizeof(unsigned long) - 1))))
		{
			// are there iov's after this one? Or is it so much we'd need
			// to do multiple writes anyway?
			if ((i + 1) < count || vecs[i].iov_len > 256)
			{
				// cop out and malloc
				unsigned long j;
				ssize_t sizetomalloc = 0, totvecsize = 0;
				char *cbuf, *cbufptr;

				for (j = i; j < count; j++)
					totvecsize += vecs[j].iov_len;

				// pad up in case unaligned
				sizetomalloc = totvecsize + sizeof(int) - 1;
				sizetomalloc &= ~(sizeof(int) - 1);
				cbuf = (char *) rt_malloc(sizetomalloc);
				// malloc returns aligned memory
				if (!cbuf)
				{
					ret = -ENOMEM;
					goto writev_out;
				}
				cbufptr = cbuf;
				for (j = i; j < count; j++)
				{
					memcpy(cbufptr, vecs[j].iov_base, vecs[j].iov_len);
					cbufptr += vecs[j].iov_len;
				}
				//rt_kprintf("direct_write: offset %d, size %d\n", to, sizetomalloc);
				ret = jffs2_flash_write(c, to, sizetomalloc, &thislen,
						(unsigned char *) cbuf);
				if (thislen > totvecsize) // in case it was aligned up
					thislen = totvecsize;
				totlen += thislen;
				rt_free(cbuf);
				goto writev_out;
			}
			else
			{
				// otherwise optimize for the common case
				int buf[256/sizeof(int)]; // int, so int aligned
				size_t lentowrite;

				lentowrite = vecs[i].iov_len;
				// pad up in case its unaligned
				lentowrite += sizeof(int) - 1;
				lentowrite &= ~(sizeof(int) - 1);
				memcpy(buf, vecs[i].iov_base, lentowrite);

				//rt_kprintf("direct_write: offset %d, size %d\n", to, lentowrite);
				ret = jffs2_flash_write(c, to, lentowrite, &thislen,
						(unsigned char *) &buf);
				if (thislen > vecs[i].iov_len)
					thislen = vecs[i].iov_len;
			}
		}
		else
		{
			//rt_kprintf("direct_writev: offset %d, size %d\n", to, vecs[i].iov_len);
			ret = jffs2_flash_write(c, to, vecs[i].iov_len, &thislen,
					vecs[i].iov_base);
		}
		totlen += thislen;
		if (ret || thislen != vecs[i].iov_len) break;
		to += vecs[i].iov_len;
	}

writev_out:
	if (retlen) *retlen = totlen;

	return ret;
}
