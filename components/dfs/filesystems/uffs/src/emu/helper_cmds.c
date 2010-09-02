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
 * \file helper_cmds.c
 * \brief helper commands for test uffs
 * \author Ricky Zheng
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uffs/uffs_config.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_fs.h"
#include "uffs/uffs_utils.h"
#include "uffs/uffs_core.h"
#include "uffs/uffs_mtb.h"
#include "uffs/uffs_find.h"
#include "cmdline.h"
#include "uffs/uffs_fd.h"

#define PFX "cmd: "


#define MAX_PATH_LENGTH 128


BOOL cmdFormat(const char *tail)
{
	URET ret;
	const char *mount = "/";
	uffs_Device *dev;

	if (tail) {
		mount = cli_getparam(tail, NULL);
	}
	uffs_Perror(UFFS_ERR_NORMAL, "Formating %s ... ", mount);

	dev = uffs_GetDeviceFromMountPoint(mount);
	if (dev == NULL) {
		uffs_Perror(UFFS_ERR_NORMAL, "Can't get device from mount point.");
	}
	else {
		if (dev->ref_count == 1) {
			ret = uffs_FormatDevice(dev);
			if (ret != U_SUCC) {
				uffs_Perror(UFFS_ERR_NORMAL, "Format fail.");
			}
			else {
				uffs_Perror(UFFS_ERR_NORMAL, "Format succ.");
			}
		}
		else {
			uffs_Perror(UFFS_ERR_NORMAL, "dev->ref_count: %d, can't format this device.", dev->ref_count);
		}
		uffs_PutDevice(dev);
	}
	return TRUE;	
}

BOOL cmdMkf(const char *tail)
{
	int fd;
	const char *name;
	int oflags = UO_RDWR | UO_CREATE;

	if (tail == NULL) {
		return FALSE;
	}

	name = cli_getparam(tail, NULL);
	fd = uffs_open(name, oflags);
	if (fd < 0) {
		uffs_Perror(UFFS_ERR_NORMAL, "Create %s fail, err: %d", name, uffs_get_error());
	}
	else {
		uffs_Perror(UFFS_ERR_NORMAL, "Create %s succ.", name);
		uffs_close(fd);
	}
	
	return TRUE;
}

BOOL cmdMkdir(const char *tail)
{
	const char *name;

	if (tail == NULL) {
		return FALSE;
	}

	name = cli_getparam(tail, NULL);
	
	if (uffs_mkdir(name) < 0) {
		uffs_Perror(UFFS_ERR_NORMAL, "Create %s fail, err: %d", name, uffs_get_error());
	}
	else {
		uffs_Perror(UFFS_ERR_NORMAL, "Create %s succ.", name);
	}	
	return TRUE;
}


static int CountObjectUnder(const char *dir)
{
	int count = 0;
	uffs_DIR *dirp;

	dirp = uffs_opendir(dir);
	if (dirp) {
		while (uffs_readdir(dirp) != NULL)
			count++;
		uffs_closedir(dirp);
	}
	return count;
}

BOOL cmdPwd(const char *tail)
{
	uffs_Perror(UFFS_ERR_NORMAL, "not supported.");
	return TRUE;
}

BOOL cmdCd(const char *tail)
{
	uffs_Perror(UFFS_ERR_NORMAL, "Not supported");
	return TRUE;
}

BOOL cmdLs(const char *tail)
{
	uffs_DIR *dirp;
	struct uffs_dirent *ent;
	struct uffs_stat stat_buf;
	int count = 0;
	char buf[MAX_PATH_LENGTH+2];
	char *name = (char *)tail;
	char *sub;

	if (name == NULL) {
		uffs_Perror(UFFS_ERR_NORMAL, "Must provide file/dir name.");
		return FALSE;
	}

	dirp = uffs_opendir(name);
	if (dirp == NULL) {
		uffs_Perror(UFFS_ERR_NORMAL, "Can't open '%s' for list", name);
	}
	else {
		uffs_PerrorRaw(UFFS_ERR_NORMAL, "------name-----------size---------serial-----" TENDSTR);
		ent = uffs_readdir(dirp);
		while (ent) {
			uffs_PerrorRaw(UFFS_ERR_NORMAL, "%9s", ent->d_name);
			strcpy(buf, name);
			sub = buf;
			if (name[strlen(name)-1] != '/')
				sub = strcat(buf, "/");
			sub = strcat(sub, ent->d_name);
			if (ent->d_type & FILE_ATTR_DIR) {
				sub = strcat(sub, "/");
				uffs_PerrorRaw(UFFS_ERR_NORMAL, "/  \t<%8d>", CountObjectUnder(sub));
			}
			else {
				uffs_stat(sub, &stat_buf);
				uffs_PerrorRaw(UFFS_ERR_NORMAL, "   \t %8d ", stat_buf.st_size);
			}
			uffs_PerrorRaw(UFFS_ERR_NORMAL, "\t%6d" TENDSTR, ent->d_ino);
			count++;
			ent = uffs_readdir(dirp);
		}
		
		uffs_closedir(dirp);

		uffs_PerrorRaw(UFFS_ERR_NORMAL, "Total: %d objects." TENDSTR, count);
	}

	return TRUE;
}


BOOL cmdRm(const char *tail)
{
	const char *name = NULL;
	int ret = 0;
	struct uffs_stat st;

	if (tail == NULL) return FALSE;

	name = cli_getparam(tail, NULL);

	if (uffs_stat(name, &st) < 0) {
		uffs_Perror(UFFS_ERR_NORMAL, "Can't stat '%s'", name);
		return TRUE;
	}

	if (st.st_mode & US_IFDIR) {
		ret = uffs_rmdir(name);
	}
	else {
		ret = uffs_remove(name);
	}

	if (ret == 0)
		uffs_Perror(UFFS_ERR_NORMAL, "Delete '%s' succ.", name);
	else
		uffs_Perror(UFFS_ERR_NORMAL, "Delete '%s' fail!", name);

	return TRUE;
}

BOOL cmdRen(const char *tail)
{
	const char *oldname;
	const char *newname;

	if (tail == NULL) 
		return FALSE;
	oldname = cli_getparam(tail, &newname);
	if (newname == NULL)
		return FALSE;

	if (uffs_rename(oldname, newname) == 0) {
		uffs_Perror(UFFS_ERR_NORMAL, "Rename from '%s' to '%s' succ.", oldname, newname);
	}
	else {
		uffs_Perror(UFFS_ERR_NORMAL, "Rename from '%s' to '%s' fail!", oldname, newname);
	}
	return TRUE;
}

BOOL cmdSt(const char *tail)
{
	uffs_Device *dev;
	const char *mount = "/";
	uffs_FlashStat *s;
	TreeNode *node;

	if (tail) {
		mount = cli_getparam(tail, NULL);
	}

	dev = uffs_GetDeviceFromMountPoint(mount);
	if (dev == NULL) {
		uffs_Perror(UFFS_ERR_NORMAL, "Can't get device from mount point %s", mount);
		return TRUE;
	}

	s = &(dev->st);

	uffs_PerrorRaw(UFFS_ERR_NORMAL, "----------- basic info -----------" TENDSTR);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "TreeNode size:         %d" TENDSTR, sizeof(TreeNode));
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "TagStore size:         %d" TENDSTR, sizeof(struct uffs_TagStoreSt));
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "MaxCachedBlockInfo:    %d" TENDSTR, MAX_CACHED_BLOCK_INFO);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "MaxPageBuffers:        %d" TENDSTR, MAX_PAGE_BUFFERS);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "MaxDirtyPagesPerBlock: %d" TENDSTR, MAX_DIRTY_PAGES_IN_A_BLOCK);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "MaxPathLength:         %d" TENDSTR, MAX_PATH_LENGTH);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "MaxObjectHandles:      %d" TENDSTR, MAX_OBJECT_HANDLE);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "FreeObjectHandles:     %d" TENDSTR, uffs_PoolGetFreeCount(uffs_GetObjectPool()));
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "MaxDirHandles:         %d" TENDSTR, MAX_DIR_HANDLE);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "FreeDirHandles:        %d" TENDSTR, uffs_PoolGetFreeCount(uffs_GetDirEntryBufPool()));

	uffs_PerrorRaw(UFFS_ERR_NORMAL, "----------- statistics for '%s' -----------" TENDSTR, mount);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "Block Erased:          %d" TENDSTR, s->block_erase_count);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "Write Page:            %d" TENDSTR, s->page_write_count);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "Write Spare:           %d" TENDSTR, s->spare_write_count);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "Read Page:             %d" TENDSTR, s->page_read_count - s->page_header_read_count);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "Read Header:           %d" TENDSTR, s->page_header_read_count);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "Read Spare:            %d" TENDSTR, s->spare_read_count);

	uffs_PerrorRaw(UFFS_ERR_NORMAL, "--------- partition info for '%s' ---------" TENDSTR, mount);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "Space total:           %d" TENDSTR, uffs_GetDeviceTotal(dev));
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "Space used:            %d" TENDSTR, uffs_GetDeviceUsed(dev));
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "Space free:            %d" TENDSTR, uffs_GetDeviceFree(dev));
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "Page Size:             %d" TENDSTR, dev->attr->page_data_size);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "Spare Size:            %d" TENDSTR, dev->attr->spare_size);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "Pages Per Block:       %d" TENDSTR, dev->attr->pages_per_block);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "Block size:            %d" TENDSTR, dev->attr->page_data_size * dev->attr->pages_per_block);
	uffs_PerrorRaw(UFFS_ERR_NORMAL, "Total blocks:          %d of %d" TENDSTR, (dev->par.end - dev->par.start + 1), dev->attr->total_blocks);
	if (dev->tree.bad) {
		uffs_PerrorRaw(UFFS_ERR_NORMAL, "Bad blocks: ");
		node = dev->tree.bad;
		while(node) {
			uffs_PerrorRaw(UFFS_ERR_NORMAL, "%d, ", node->u.list.block);
			node = node->u.list.next;
		}
		uffs_PerrorRaw(UFFS_ERR_NORMAL, TENDSTR);
	}

	uffs_BufInspect(dev);

	uffs_PutDevice(dev);

	return TRUE;

}


BOOL cmdCp(const char *tail)
{
	const char *src;
	const char *des;
	char buf[100];
	int fd1 = -1, fd2 = -1;
	int len;
	BOOL src_local = FALSE, des_local = FALSE;
	FILE *fp1 = NULL, *fp2 = NULL;

	if (!tail) 
		return FALSE;

	src = cli_getparam(tail, &des);

	if (!des)
		return FALSE;

	if (memcmp(src, "::", 2) == 0) {
		src += 2;
		src_local = TRUE;
	}
	if (memcmp(des, "::", 2) == 0) {
		des += 2;
		des_local = TRUE;
	}
	
	if (src_local) {
		if ((fp1 = fopen(src, "rb")) == NULL) {
			uffs_Perror(UFFS_ERR_NORMAL, "Can't open %s for copy.", src);
			goto fail_ext;
		}
	}
	else {
		if ((fd1 = uffs_open(src, UO_RDONLY)) < 0) {
			uffs_Perror(UFFS_ERR_NORMAL, "Can't open %s for copy.", src);
			goto fail_ext;
		}
	}

	if (des_local) {
		if ((fp2 = fopen(des, "wb")) == NULL) {
			uffs_Perror(UFFS_ERR_NORMAL, "Can't open %s for copy.", des);
			goto fail_ext;
		}
	}
	else {
		if ((fd2 = uffs_open(des, UO_RDWR|UO_CREATE|UO_TRUNC)) < 0) {
			uffs_Perror(UFFS_ERR_NORMAL, "Can't open %s for copy.", des);
			goto fail_ext;
		}
	}

	while (	(src_local ? (feof(fp1) == 0) : (uffs_eof(fd1) == 0)) ) {
		if (src_local) {
			len = fread(buf, 1, sizeof(buf), fp1);
		}
		else {
			len = uffs_read(fd1, buf, sizeof(buf));
		}
		if (len == 0) 
			break;
		if (len < 0) {
			uffs_Perror(UFFS_ERR_NORMAL, "read file %s fail ?", src);
			break;
		}
		if (des_local) {
			if ((int)fwrite(buf, 1, len, fp2) != len) {
				uffs_Perror(UFFS_ERR_NORMAL, "write file %s fail ? ", des);
				break;
			}
		}
		else {
			if (uffs_write(fd2, buf, len) != len) {
				uffs_Perror(UFFS_ERR_NORMAL, "write file %s fail ? ", des);
				break;
			}
		}
	}

fail_ext:
	if (fd1 > 0)
		uffs_close(fd1);
	if (fd2 > 0)
		uffs_close(fd2);
	if (fp1) 
		fclose(fp1);
	if (fp2)
		fclose(fp2);

	return TRUE;
}

BOOL cmdCat(const char *tail)
{
	int fd;
	const char *name;
	const char *next;
	char buf[100];
	int start = 0, size = 0, printed = 0, n, len;

	if (!tail) 
		return FALSE;

	name = cli_getparam(tail, &next);

	if ((fd = uffs_open(name, UO_RDONLY)) < 0) {
		uffs_Perror(UFFS_ERR_NORMAL, "Can't open %s", name);
		goto fail;
	}

	if (next) {
		start = strtol(next, (char **) &next, 10);
		if (next) size = strtol(next, NULL, 10);
	}

	if (start >= 0)
		uffs_seek(fd, start, USEEK_SET);
	else
		uffs_seek(fd, -start, USEEK_END);

	while (uffs_eof(fd) == 0) {
		len = uffs_read(fd, buf, sizeof(buf) - 1);
		if (len == 0) 
			break;
		if (len > 0) {
			if (size == 0 || printed < size) {
				n = (size == 0 ? len : (size - printed > len ? len : size - printed));
				buf[n] = 0;
				uffs_PerrorRaw(UFFS_ERR_NORMAL, "%s", buf);
				printed += n;
			}
			else {
				break;
			}
		}
	}
	uffs_PerrorRaw(UFFS_ERR_NORMAL, TENDSTR);
	uffs_close(fd);

fail:

	return TRUE;
}


static URET test_verify_file(const char *file_name)
{
	int fd;
	int ret = U_FAIL;
	unsigned char buf[100];
	int i, pos, len;

	if ((fd = uffs_open(file_name, UO_RDONLY)) < 0) {
		uffs_Perror(UFFS_ERR_NORMAL, "Can't open file %s for read.", file_name);
		goto test_exit;
	}

	pos = 0;
	while (!uffs_eof(fd)) {
		len = uffs_read(fd, buf, sizeof(buf));
		if (len <= 0)
			goto test_failed;
		for (i = 0; i < len; i++) {
			if (buf[i] != (pos++ & 0xFF)) {
				pos--;
				uffs_Perror(UFFS_ERR_NORMAL, "Verify file %s failed at: %d, expect %x but got %x", file_name, pos, pos & 0xFF, buf[i]);
				goto test_failed;
			}
		}
	}

	if (pos != uffs_seek(fd, 0, USEEK_END)) {
		uffs_Perror(UFFS_ERR_NORMAL, "Verify file %s failed. invalid file length.", file_name);
		goto test_failed;
	}

	uffs_Perror(UFFS_ERR_NORMAL, "Verify file %s succ.", file_name);
	ret = U_SUCC;

test_failed:
	uffs_close(fd);

test_exit:

	return ret;
}

static URET do_write_test_file(int fd, int size)
{
	long pos;
	unsigned char buf[100];
	unsigned char data;
	int i, len;

	while (size > 0) {
		pos = uffs_seek(fd, 0, USEEK_CUR);
		len = (size > sizeof(buf) ? sizeof(buf) : size);
		data = pos & 0xFF;
		for (i = 0; i < len; i++, data++) {
			buf[i] = data;
		}
		if (uffs_write(fd, buf, len) != len) {
			uffs_Perror(UFFS_ERR_NORMAL, "Write file failed, size %d at %d", len, pos);
			return U_FAIL;
		}
		size -= len;
	}

	return U_SUCC;
}

static URET test_append_file(const char *file_name, int size)
{
	int ret = U_FAIL;
	int fd = -1;

	if ((fd = uffs_open(file_name, UO_RDWR|UO_APPEND|UO_CREATE)) < 0) {
		uffs_Perror(UFFS_ERR_NORMAL, "Can't open file %s for append.", file_name);
		goto test_exit;
	}

	uffs_seek(fd, 0, USEEK_END);

	if (do_write_test_file(fd, size) == U_FAIL) {
		uffs_Perror(UFFS_ERR_NORMAL, "Write file %s failed.", file_name);
		goto test_failed;
	}
	ret = U_SUCC;

test_failed:
	uffs_close(fd);

test_exit:

	return ret;
}

static URET test_write_file(const char *file_name, int pos, int size)
{
	int ret = U_FAIL;
	int fd = -1;

	if ((fd = uffs_open(file_name, UO_RDWR|UO_CREATE)) < 0) {
		uffs_Perror(UFFS_ERR_NORMAL, "Can't open file %s for write.", file_name);
		goto test_exit;
	}

	if (uffs_seek(fd, pos, USEEK_SET) != pos) {
		uffs_Perror(UFFS_ERR_NORMAL, "Can't seek file %s at pos %d", file_name, pos);
		goto test_failed;
	}

	if (do_write_test_file(fd, size) == U_FAIL) {
		uffs_Perror(UFFS_ERR_NORMAL, "Write file %s failed.", file_name);
		goto test_failed;
	}
	ret = U_SUCC;

test_failed:
	uffs_close(fd);

test_exit:

	return ret;
}


static URET DoTest2(void)
{
	int fd = -1;
	URET ret = U_FAIL;
	char buf[100], buf_1[100];

	fd = uffs_open("/abc/", UO_RDWR|UO_DIR);
	if (fd < 0) {
		uffs_Perror(UFFS_ERR_NORMAL, "Can't open dir abc, err: %d", uffs_get_error());
		uffs_Perror(UFFS_ERR_NORMAL, "Try to create a new one...");
		fd = uffs_open("/abc/", UO_RDWR|UO_CREATE|UO_DIR);
		if (fd < 0) {
			uffs_Perror(UFFS_ERR_NORMAL, "Can't create new dir /abc/");
			goto exit_test;
		}
		else {
			uffs_close(fd);
		}
	}
	else {
		uffs_close(fd);
	}
	
	fd = uffs_open("/abc/test.txt", UO_RDWR|UO_CREATE);
	if (fd < 0) {
		uffs_Perror(UFFS_ERR_NORMAL, "Can't open /abc/test.txt");
		goto exit_test;
	}

	sprintf(buf, "123456789ABCDEF");
	ret = uffs_write(fd, buf, strlen(buf));
	uffs_Perror(UFFS_ERR_NORMAL, "write %d bytes to file, content: %s", ret, buf);

	ret = uffs_seek(fd, 3, USEEK_SET);
	uffs_Perror(UFFS_ERR_NORMAL, "new file position: %d", ret);

	memset(buf_1, 0, sizeof(buf_1));
	ret = uffs_read(fd, buf_1, 5);
	uffs_Perror(UFFS_ERR_NORMAL, "read %d bytes, content: %s", ret, buf_1);

	if (memcmp(buf + 3, buf_1, 5) != 0) {
		ret = U_FAIL;
	}
	else {
		ret = U_SUCC;
	}

	uffs_close(fd);

exit_test:

	return ret;
}

/* test create file, write file and read back */
BOOL cmdTest1(const char *tail)
{
	int fd;
	URET ret;
	char buf[100];
	const char *name;

	if (!tail) {
		return FALSE;
	}

	name = cli_getparam(tail, NULL);

	fd = uffs_open(name, UO_RDWR|UO_CREATE|UO_TRUNC);
	if (fd < 0) {
		uffs_Perror(UFFS_ERR_NORMAL, "Can't open %s", name);
		goto fail;
	}

	sprintf(buf, "123456789ABCDEF");
	ret = uffs_write(fd, buf, strlen(buf));
	uffs_Perror(UFFS_ERR_NORMAL, "write %d bytes to file, content: %s", ret, buf);

	ret = uffs_seek(fd, 3, USEEK_SET);
	uffs_Perror(UFFS_ERR_NORMAL, "new file position: %d", ret);

	memset(buf, 0, sizeof(buf));
	ret = uffs_read(fd, buf, 5);
	uffs_Perror(UFFS_ERR_NORMAL, "read %d bytes, content: %s", ret, buf);

	uffs_close(fd);

fail:

	return TRUE;
}

BOOL cmdTest2(const char *tail)
{
	uffs_Perror(UFFS_ERR_NORMAL, "Test return: %s !", DoTest2() == U_SUCC ? "succ" : "failed");

	return TRUE;
}

/* Test file append and 'random' write */
BOOL cmdTest3(const char *tail)
{
	const char *name;
	int i;
	int write_test_seq[] = { 20, 10, 500, 40, 1140, 900, 329, 4560, 352, 1100 };

	if (!tail) {
		return FALSE;
	}

	name = cli_getparam(tail, NULL);
	uffs_Perror(UFFS_ERR_NORMAL, "Test append file %s ...", name);
	for (i = 1; i < 500; i += 29) {
		if (test_append_file(name, i) != U_SUCC) {
			uffs_Perror(UFFS_ERR_NORMAL, "Append file %s test failed at %d !", name, i);
			return TRUE;
		}
	}

	uffs_Perror(UFFS_ERR_NORMAL, "Check file %s ... ", name);
	if (test_verify_file(name) != U_SUCC) {
		uffs_Perror(UFFS_ERR_NORMAL, "Verify file %s failed.", name);
		return TRUE;
	}

	uffs_Perror(UFFS_ERR_NORMAL, "Test write file ...");
	for (i = 0; i < sizeof(write_test_seq) / sizeof(int) - 1; i++) {
		if (test_write_file(name, write_test_seq[i], write_test_seq[i+1]) != U_SUCC) {
			uffs_Perror(UFFS_ERR_NORMAL, "Test write file failed !");
			return TRUE;
		}
	}

	uffs_Perror(UFFS_ERR_NORMAL, "Check file %s ... ", name);
	if (test_verify_file(name) != U_SUCC) {
		uffs_Perror(UFFS_ERR_NORMAL, "Verify file %s failed.", name);
		return TRUE;
	}

	uffs_Perror(UFFS_ERR_NORMAL, "Test succ !");

	return TRUE;
}

/* open two files and test write */
BOOL cmdTest4(const char *tail)
{
	int fd1 = -1, fd2 = -1;

	uffs_Perror(UFFS_ERR_NORMAL, "open /a ...");
	if ((fd1 = uffs_open("/a", UO_RDWR | UO_CREATE)) < 0) {
		uffs_Perror(UFFS_ERR_NORMAL, "Can't open /a");
		goto fail_exit;
	}

	uffs_Perror(UFFS_ERR_NORMAL, "open /b ...");
	if ((fd2 = uffs_open("/b", UO_RDWR | UO_CREATE)) < 0) {
		uffs_Perror(UFFS_ERR_NORMAL, "Can't open /b");
		uffs_close(fd1);
		goto fail_exit;
	}

	uffs_Perror(UFFS_ERR_NORMAL, "write (1) to /a ...");
	uffs_write(fd1, "Hello,", 6);
	uffs_Perror(UFFS_ERR_NORMAL, "write (1) to /b ...");
	uffs_write(fd2, "Hello,", 6);
	uffs_Perror(UFFS_ERR_NORMAL, "write (2) to /a ...");
	uffs_write(fd1, "World.", 6);
	uffs_Perror(UFFS_ERR_NORMAL, "write (2) to /b ...");
	uffs_write(fd2, "World.", 6);
	uffs_Perror(UFFS_ERR_NORMAL, "close /a ...");
	uffs_close(fd1);
	uffs_Perror(UFFS_ERR_NORMAL, "close /b ...");
	uffs_close(fd2);

	return TRUE;

fail_exit:
	return TRUE;
}

/* test appending file */
BOOL cmdTest5(const char *tail)
{
	int fd = -1;
	URET ret;
	char buf[100];
	const char *name;

	if (!tail) {
		return FALSE;
	}

	name = cli_getparam(tail, NULL);

	fd = uffs_open(name, UO_RDWR|UO_APPEND);
	if (fd < 0) {
		uffs_Perror(UFFS_ERR_NORMAL, "Can't open %s", name);
		goto fail;
	}

	sprintf(buf, "append test...");
	ret = uffs_write(fd, buf, strlen(buf));
	if (ret != strlen(buf)) {
		uffs_Perror(UFFS_ERR_NORMAL, "write file failed, %d/%d", ret, strlen(buf));
	}
	else {
		uffs_Perror(UFFS_ERR_NORMAL, "write %d bytes to file, content: %s", ret, buf);
	}

	uffs_close(fd);

fail:

	return TRUE;
}



BOOL cmdMount(const char *tail)
{
	uffs_MountTable *tab = uffs_GetMountTable();
	tail = tail;

	while (tab) {
		uffs_Perror(UFFS_ERR_NORMAL, " %s : (%d) ~ (%d)", tab->mount, tab->start_block, tab->end_block);
		tab = tab->next;
	}

	return TRUE;
}

static struct cli_commandset cmdset[] = 
{
    { cmdFormat,	"format",		"[<mount>]",		"Format device" },
    { cmdMkf,		"mkfile",		"<name>",			"create a new file" },
    { cmdMkdir,		"mkdir",		"<name>",			"create a new directory" },
    { cmdRm,		"rm",			"<name>",			"delete file/directory" },
    { cmdRen,		"mv|ren",		"<old> <new>",		"rename file/directory" },
    { cmdLs,		"ls",			"<dir>",			"list dirs and files" },
    { cmdSt,		"info|st",		"<mount>",			"show statistic infomation" },
    { cmdTest1,		"t1",			"<name>",			"test 1" },
    { cmdTest2,		"t2",			NULL,				"test 2" },
    { cmdTest3,		"t3",			"<name>",			"test 3" },
    { cmdTest4,		"t4",			NULL,				"test 4" },
    { cmdTest5,		"t5",			"<name>",			"test 5" },
    { cmdCp,		"cp",			"<src> <des>",		"copy files. the local file name start with '::'" },
    { cmdCat,		"cat",			"<name>",			"show file content" },
    { cmdPwd,		"pwd",			NULL,				"show current dir" },
    { cmdCd,		"cd",			"<path>",			"change current dir" },
    { cmdMount,		"mount",		NULL,				"list mounted file systems" },

    { NULL, NULL, NULL, NULL }
};


struct cli_commandset * get_helper_cmds()
{
	return cmdset;
};
