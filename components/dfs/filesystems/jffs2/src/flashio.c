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

//#include <cyg/io/io.h>   mod by prife
//#include <cyg/io/config_keys.h>
//#include <cyg/io/flash.h>

// #include <stdio.h>
// #include <stdlib.h>

//#include <io.h>
//#include <fcntl.h>
// #include <string.h>
//#include <sys/stat.h>

#include <rtthread.h>

cyg_bool jffs2_flash_read(struct jffs2_sb_info * c,
			  cyg_uint32 read_buffer_offset, const size_t size,
			  size_t * return_size, unsigned char *write_buffer)
{
	cyg_uint32 len;
	struct super_block *sb = OFNI_BS_2SFFJ(c);

	D2(printf("FLASH READ\n"));
	D2(printf("read address = %x\n", CYGNUM_FS_JFFS2_BASE_ADDRESS + read_buffer_offset));
	D2(printf("write address = %x\n", write_buffer));
	D2(printf("size = %x\n", size));
//	err = cyg_io_bread(sb->s_dev, write_buffer, &len, read_buffer_offset);
	len = rt_device_read(sb->s_dev, read_buffer_offset, write_buffer, size);

//    lseek(file_handle, read_buffer_offset, SEEK_SET);
//    len = read(file_handle, write_buffer, size);
    if (len != size)
        return -EIO;

	*return_size = (size_t) len;
	return ENOERR;
}

cyg_bool jffs2_flash_write(struct jffs2_sb_info * c,
			   cyg_uint32 write_buffer_offset, const size_t size,
			   size_t * return_size, unsigned char *read_buffer)
{
	cyg_uint32 len;
	struct super_block *sb = OFNI_BS_2SFFJ(c);

	D2(printf("FLASH WRITE ENABLED!!!\n"));
	D2(printf("write address = %x\n", CYGNUM_FS_JFFS2_BASE_ADDRESS + write_buffer_offset));
	D2(printf("read address = %x\n", read_buffer));
	D2(printf("size = %x\n", size));

	len = rt_device_write(sb->s_dev, write_buffer_offset, read_buffer, size);
	*return_size = (size_t) len;
	if (len != size)
		return -EIO;
	return ENOERR;
	//return ((err == ENOERR) ? ENOERR : -EIO);

	// Cyg_ErrNo err;
	// cyg_uint32 len;
	// struct super_block *sb = OFNI_BS_2SFFJ(c);

	// lseek(file_handle, write_buffer_offset, SEEK_SET);
	// len = write(file_handle, read_buffer, size);
    // if (len < 0)
        // return -EIO;

    // *return_size = (size_t) len;
    // return ENOERR;
}

int
jffs2_flash_direct_writev(struct jffs2_sb_info *c, const struct iovec *vecs,
		   unsigned long count, loff_t to, size_t * retlen)
{
	unsigned long i;
	size_t totlen = 0, thislen;
	int ret = 0;

	for (i = 0; i < count; i++) {
		// writes need to be aligned but the data we're passed may not be
		// Observation suggests most unaligned writes are small, so we
		// optimize for that case.

		if (((vecs[i].iov_len & (sizeof (int) - 1))) ||
		    (((unsigned long) vecs[i].
		      iov_base & (sizeof (unsigned long) - 1)))) {
			// are there iov's after this one? Or is it so much we'd need
			// to do multiple writes anyway?
			if ((i + 1) < count || vecs[i].iov_len > 256) {
				// cop out and malloc
				unsigned long j;
				ssize_t sizetomalloc = 0, totvecsize = 0;
				char *cbuf, *cbufptr;

				for (j = i; j < count; j++)
					totvecsize += vecs[j].iov_len;

				// pad up in case unaligned
				sizetomalloc = totvecsize + sizeof (int) - 1;
				sizetomalloc &= ~(sizeof (int) - 1);
				cbuf = (char *) malloc(sizetomalloc);
				// malloc returns aligned memory
				if (!cbuf) {
					ret = -ENOMEM;
					goto writev_out;
				}
				cbufptr = cbuf;
				for (j = i; j < count; j++) {
					memcpy(cbufptr, vecs[j].iov_base,
					       vecs[j].iov_len);
					cbufptr += vecs[j].iov_len;
				}
				ret =
				    jffs2_flash_write(c, to, sizetomalloc,
						      &thislen, (unsigned char *)cbuf);
				if (thislen > totvecsize)	// in case it was aligned up
					thislen = totvecsize;
				totlen += thislen;
				free(cbuf);
				goto writev_out;
			} else {
				// otherwise optimize for the common case
				int buf[256 / sizeof (int)];	// int, so int aligned
				size_t lentowrite;

				lentowrite = vecs[i].iov_len;
				// pad up in case its unaligned
				lentowrite += sizeof (int) - 1;
				lentowrite &= ~(sizeof (int) - 1);
				memcpy(buf, vecs[i].iov_base, lentowrite);

				ret =
				    jffs2_flash_write(c, to, lentowrite,
						      &thislen, (unsigned char *) &buf);
				if (thislen > vecs[i].iov_len)
					thislen = vecs[i].iov_len;
			}	// else
		} else
			ret =
			    jffs2_flash_write(c, to, vecs[i].iov_len, &thislen,
					      vecs[i].iov_base);
		totlen += thislen;
		if (ret || thislen != vecs[i].iov_len)
			break;
		to += vecs[i].iov_len;
	}
      writev_out:
	if (retlen)
		*retlen = totlen;

	return ret;
}

cyg_bool jffs2_flash_erase(struct jffs2_sb_info * c,
			   struct jffs2_eraseblock * jeb)
{
	int res;
	struct super_block *sb = OFNI_BS_2SFFJ(c);

	D2(printf("FLASH ERASE ENABLED!!!\n"));
	D2(printf("erase address = %x\n", CYGNUM_FS_JFFS2_BASE_ADDRESS + jeb->offset));
	D2(printf("size = %x\n", c->sector_size));

	// err = cyg_io_get_config(sb->s_dev, CYG_IO_GET_CONFIG_FLASH_ERASE,
				// &e, &len);
				
	res = rt_device_control(sb->s_dev, RT_DEVICE_CTRL_BLK_ERASE, (void *)(jeb->offset));
	return ((res == RT_EOK) ? ENOERR : -EIO);
	
    //这里 jeb数据结构
    // int i;
    // char block_buf[4096];
	// cyg_uint32 len;
	// struct super_block *sb = OFNI_BS_2SFFJ(c);

	// lseek(file_handle, jeb->offset, SEEK_SET);

	// c->sector_size 是sector大小还是block大小呢？？ //fixme
	// 这里的jeb->offset 是字节为偏移地址吗？？？   //fixme
    // memset(&block_buf, 0xff, sizeof(block_buf) );
	// for(i=0; i<(BLOCK_SIZE/4096); i++)
        // write(file_handle, &block_buf, sizeof(block_buf));

	// return ENOERR;
}

