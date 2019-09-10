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
 * \file test_cmds.c
 * \brief commands for test uffs
 * \author Ricky Zheng
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uffs_config.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_fd.h"
#include "uffs/uffs_utils.h"
#include "uffs/uffs_core.h"
#include "uffs/uffs_mtb.h"
#include "uffs/uffs_find.h"
#include "uffs/uffs_badblock.h"
#include "cmdline.h"
#include "api_test.h"

#define PFX "test: "

#define	MAX_TEST_BUF_LEN	8192

#define SEQ_INIT	10
#define SEQ_MOD_LEN	120

#define MSG(msg,...) uffs_PerrorRaw(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)
#define MSGLN(msg,...) uffs_Perror(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)


static void memcp_seq(void *des, int size, int start_pos)
{
	int i;
	u8 *p = (u8 *)des;
	
	for (i = 0; i < size; i++, p++) {
		*p = (start_pos + SEQ_INIT + i) % SEQ_MOD_LEN;
	}
}

static UBOOL check_entry_exist(const char *name)
{
	struct uffs_stat sb;

	return uffs_stat(name, &sb) < 0 ? U_FALSE : U_TRUE;
}

static URET do_write_test_file(int fd, int size)
{
	long pos;
	unsigned char buf[100];
	int len;

	while (size > 0) {
		pos = uffs_seek(fd, 0, USEEK_CUR);
		len = (size > sizeof(buf) ? sizeof(buf) : size);
		memcp_seq(buf, len, pos);
		if (uffs_write(fd, buf, len) != len) {
			MSGLN("Write file failed, size %d at %d", len, pos);
			return U_FAIL;
		}
		size -= len;
	}

	return U_SUCC;
}

static URET test_write_file(const char *file_name, int pos, int size)
{
	int ret = U_FAIL;
	int fd = -1;

	if ((fd = uffs_open(file_name, UO_RDWR|UO_CREATE)) < 0) {
		MSGLN("Can't open file %s for write.", file_name);
		goto test_exit;
	}

	if (uffs_seek(fd, pos, USEEK_SET) != pos) {
		MSGLN("Can't seek file %s at pos %d", file_name, pos);
		goto test_failed;
	}

	if (do_write_test_file(fd, size) == U_FAIL) {
		MSGLN("Write file %s failed.", file_name);
		goto test_failed;
	}
	ret = U_SUCC;

test_failed:
	uffs_close(fd);

test_exit:

	return ret;
}


static URET test_verify_file(const char *file_name, UBOOL noecc)
{
	int fd;
	int ret = U_FAIL;
	unsigned char buf[100];
	int i, pos, len;
	u8 x;

	if ((fd = uffs_open(file_name, (noecc ? UO_RDONLY|UO_NOECC : UO_RDONLY))) < 0) {
		MSGLN("Can't open file %s for read.", file_name);
		goto test_exit;
	}

	pos = 0;
	while (!uffs_eof(fd)) {
		len = uffs_read(fd, buf, sizeof(buf));
		if (len <= 0)
			goto test_failed;
		for (i = 0; i < len; i++) {
			x = (SEQ_INIT + pos + i) % SEQ_MOD_LEN;
			if (buf[i] != x) {
				MSGLN("Verify file %s failed at: %d, expect 0x%02x but got 0x%02x", file_name, pos + i, x, buf[i]);
				goto test_failed;
			}
		}
		pos += len;
	}

	if (pos != uffs_seek(fd, 0, USEEK_END)) {
		MSGLN("Verify file %s failed. invalid file length.", file_name);
		goto test_failed;
	}

	MSGLN("Verify file %s succ.", file_name);
	ret = U_SUCC;

test_failed:
	uffs_close(fd);

test_exit:

	return ret;
}

static URET test_append_file(const char *file_name, int size)
{
	int ret = U_FAIL;
	int fd = -1;

	if ((fd = uffs_open(file_name, UO_RDWR|UO_APPEND|UO_CREATE)) < 0) {
		MSGLN("Can't open file %s for append.", file_name);
		goto test_exit;
	}

	uffs_seek(fd, 0, USEEK_END);

	if (do_write_test_file(fd, size) == U_FAIL) {
		MSGLN("Write file %s failed.", file_name);
		goto test_failed;
	}
	ret = U_SUCC;

test_failed:
	uffs_close(fd);

test_exit:

	return ret;
}


/* test create file, write file and read back */
static int cmd_t1(int argc, char *argv[])
{
	int fd;
	URET ret;
	char buf[100];
	const char *name;

	if (argc < 2) {
		return CLI_INVALID_ARG;
	}

	name = argv[1];

	fd = uffs_open(name, UO_RDWR|UO_CREATE|UO_TRUNC);
	if (fd < 0) {
		MSGLN("Can't open %s", name);
		goto fail;
	}

	sprintf(buf, "123456789ABCDEF");
	ret = uffs_write(fd, buf, strlen(buf));
	MSGLN("write %d bytes to file, content: %s", ret, buf);

	ret = uffs_seek(fd, 3, USEEK_SET);
	MSGLN("new file position: %d", ret);

	memset(buf, 0, sizeof(buf));
	ret = uffs_read(fd, buf, 5);
	MSGLN("read %d bytes, content: %s", ret, buf);

	uffs_close(fd);

	return 0;
fail:

	return -1;
}


static URET DoTest2(void)
{
	int fd = -1;
	URET ret = U_FAIL;
	char buf[100], buf_1[100];

	fd = uffs_open("/abc/", UO_RDWR|UO_DIR);
	if (fd < 0) {
		MSGLN("Can't open dir abc, err: %d", uffs_get_error());
		MSGLN("Try to create a new one...");
		fd = uffs_open("/abc/", UO_RDWR|UO_CREATE|UO_DIR);
		if (fd < 0) {
			MSGLN("Can't create new dir /abc/");
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
		MSGLN("Can't open /abc/test.txt");
		goto exit_test;
	}

	sprintf(buf, "123456789ABCDEF");
	ret = uffs_write(fd, buf, strlen(buf));
	MSGLN("write %d bytes to file, content: %s", ret, buf);

	ret = uffs_seek(fd, 3, USEEK_SET);
	MSGLN("new file position: %d", ret);

	memset(buf_1, 0, sizeof(buf_1));
	ret = uffs_read(fd, buf_1, 5);
	MSGLN("read %d bytes, content: %s", ret, buf_1);

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


static int cmd_t2(int argc, char *argv[])
{
	URET ret;
	MSGLN("Test return: %s !", (ret = DoTest2()) == U_SUCC ? "succ" : "failed");

	return (ret == U_SUCC) ? 0 : -1;
}


static int cmd_VerifyFile(int argc, char *argv[])
{
	const char *name;
	UBOOL noecc = U_FALSE;

	if (argc < 2) {
		return CLI_INVALID_ARG;
	}

	name = argv[1];
	if (argc > 2 && strcmp(argv[2], "noecc") == 0) {
		noecc = U_TRUE;
	}

	MSGLN("Check file %s ... ", name);
	if (test_verify_file(name, noecc) != U_SUCC) {
		MSGLN("Verify file %s failed.", name);
		return -1;
	}

	return 0;
}

/* Test file append and 'random' write */
static int cmd_t3(int argc, char *argv[])
{
	const char *name;
	int i;
	UBOOL noecc = U_FALSE;
	int write_test_seq[] = { 20, 10, 500, 40, 1140, 900, 329, 4560, 352, 1100 };

	if (argc < 2) {
		return CLI_INVALID_ARG;
	}

	name = argv[1];
	if (argv[2] && strcmp(argv[2], "noecc") == 0) {
		noecc = U_TRUE;
	}

	if (check_entry_exist(name)) {
		MSGLN("Check file %s ... ", name);
		if (test_verify_file(name, noecc) != U_SUCC) {
			MSGLN("Verify file %s failed.", name);
			return -1;
		}
	}

	MSGLN("Test append file %s ...", name);
	for (i = 1; i < 500; i += 29) {
		if (test_append_file(name, i) != U_SUCC) {
			MSGLN("Append file %s test failed at %d !", name, i);
			return -1;
		}
	}

	MSGLN("Check file %s ... ", name);
	if (test_verify_file(name, noecc) != U_SUCC) {
		MSGLN("Verify file %s failed.", name);
		return -1;
	}

	MSGLN("Test write file ...");
	for (i = 0; i < sizeof(write_test_seq) / sizeof(int) - 1; i++) {
		if (test_write_file(name, write_test_seq[i], write_test_seq[i+1]) != U_SUCC) {
			MSGLN("Test write file failed !");
			return -1;
		}
	}

	MSGLN("Check file %s ... ", name);
	if (test_verify_file(name, noecc) != U_SUCC) {
		MSGLN("Verify file %s failed.", name);
		return -1;
	}

	MSGLN("Test succ !");

	return 0;
}

/* open two files and test write */
static int cmd_t4(int argc, char *argv[])
{
	int fd1 = -1, fd2 = -1;

	MSGLN("open /a ...");
	if ((fd1 = uffs_open("/a", UO_RDWR | UO_CREATE)) < 0) {
		MSGLN("Can't open /a");
		goto fail_exit;
	}

	MSGLN("open /b ...");
	if ((fd2 = uffs_open("/b", UO_RDWR | UO_CREATE)) < 0) {
		MSGLN("Can't open /b");
		uffs_close(fd1);
		goto fail_exit;
	}

	MSGLN("write (1) to /a ...");
	uffs_write(fd1, "Hello,", 6);
	MSGLN("write (1) to /b ...");
	uffs_write(fd2, "Hello,", 6);
	MSGLN("write (2) to /a ...");
	uffs_write(fd1, "World.", 6);
	MSGLN("write (2) to /b ...");
	uffs_write(fd2, "World.", 6);
	MSGLN("close /a ...");
	uffs_close(fd1);
	MSGLN("close /b ...");
	uffs_close(fd2);

	return 0;

fail_exit:
	return -1;
}

/* test appending file */
static int cmd_t5(int argc, char *argv[])
{
	int fd = -1;
	URET ret;
	char buf[100];
	const char *name;

	if (argc < 2) {
		return CLI_INVALID_ARG;
	}

	name = argv[1];

	fd = uffs_open(name, UO_RDWR|UO_APPEND);
	if (fd < 0) {
		MSGLN("Can't open %s", name);
		goto fail;
	}

	sprintf(buf, "append test...");
	ret = uffs_write(fd, buf, strlen(buf));
	if (ret != strlen(buf)) {
		MSGLN("write file failed, %d/%d", ret, strlen(buf));
		ret = -1;
	}
	else {
		MSGLN("write %d bytes to file, content: %s", ret, buf);
		ret = 0;
	}

	uffs_close(fd);

	return ret;
fail:
	return -1;
}


/* usage: t_pgrw
 *
 * This test case test page read/write
 */
static int cmd_TestPageReadWrite(int argc, char *argv[])
{
	TreeNode *node = NULL;
	uffs_Device *dev;
	uffs_Tags local_tag;
	uffs_Tags *tag = &local_tag;
	int ret;
	u16 block;
	u16 page;
	uffs_Buf *buf = NULL;

	u32 i;
	int rc = -1;

	dev = uffs_GetDeviceFromMountPoint("/");
	if (!dev)
		goto ext;

	buf = uffs_BufClone(dev, NULL);
	if (!buf)
		goto ext;

	node = uffs_TreeGetErasedNode(dev);
	if (!node) {
		MSGLN("no free block ?");
		goto ext;
	}

	for (i = 0; i < dev->com.pg_data_size; i++) {
		buf->data[i] = i & 0xFF;
	}

	block = node->u.list.block;
	page = 1;

	TAG_DIRTY_BIT(tag) = TAG_DIRTY;
	TAG_VALID_BIT(tag) = TAG_VALID;
	TAG_DATA_LEN(tag) = dev->com.pg_data_size;
	TAG_TYPE(tag) = UFFS_TYPE_DATA;
	TAG_PAGE_ID(tag) = 3;
	TAG_PARENT(tag) = 100;
	TAG_SERIAL(tag) = 10;
	TAG_BLOCK_TS(tag) = 1;
	SEAL_TAG(tag);

	ret = uffs_FlashWritePageCombine(dev, block, page, buf, tag);
	if (UFFS_FLASH_HAVE_ERR(ret)) {
		MSGLN("Write page error: %d", ret);
		goto ext;
	}

	ret = uffs_FlashReadPage(dev, block, page, buf, U_FALSE);
	if (UFFS_FLASH_HAVE_ERR(ret)) {
		MSGLN("Read page error: %d", ret);
		goto ext;
	}

	for (i = 0; i < dev->com.pg_data_size; i++) {
		if (buf->data[i] != (i & 0xFF)) {
			MSGLN("Data verify fail at: %d", i);
			goto ext;
		}
	}

	ret = uffs_FlashReadPageTag(dev, block, page, tag);
	if (UFFS_FLASH_HAVE_ERR(ret)) {
		MSGLN("Read tag (page spare) error: %d", ret);
		goto ext;
	}
	
	// verify tag:
	if (!TAG_IS_SEALED(tag)) {
		MSGLN("not sealed ? Tag verify fail!");
		goto ext;
	}

	if (!TAG_IS_DIRTY(tag)) {
		MSGLN("not dirty ? Tag verify fail!");
		goto ext;
	}

	if (!TAG_IS_VALID(tag)) {
		MSGLN("not valid ? Tag verify fail!");
		goto ext;
	}

	if (TAG_DATA_LEN(tag) != dev->com.pg_data_size ||
		TAG_TYPE(tag) != UFFS_TYPE_DATA ||
		TAG_PAGE_ID(tag) != 3 ||
		TAG_PARENT(tag) != 100 ||
		TAG_SERIAL(tag) != 10 ||
		TAG_BLOCK_TS(tag) != 1) {

		MSGLN("Tag verify fail!");
		goto ext;
	}

	MSGLN("Page read/write test succ.");
	rc = 0;

ext:
	if (node) {
		uffs_FlashEraseBlock(dev, node->u.list.block);
		if (HAVE_BADBLOCK(dev))
			uffs_BadBlockProcess(dev, node);
		else
			uffs_TreeInsertToErasedListTail(dev, node);
	}

	if (dev)
		uffs_PutDevice(dev);

	if (buf)
		uffs_BufFreeClone(dev, buf);

	return rc;
}

/* t_format : test format partition */
static int cmd_TestFormat(int argc, char *argv[])
{
	URET ret;
	const char *mount = "/";
	uffs_Device *dev;
	UBOOL force = U_FALSE;
	const char *test_file = "/a.txt";
	int fd;
	int rc = -1;

	if (argc > 1) {
		mount = argv[1];
		if (argc > 2 && strcmp(argv[2], "-f") == 0)
			force = U_TRUE;
	}

	fd = uffs_open(test_file, UO_RDWR | UO_CREATE);
	if (fd < 0) {
		MSGLN("can't create test file %s", test_file);
		goto ext;
	}

	MSGLN("Formating %s ... ", mount);

	dev = uffs_GetDeviceFromMountPoint(mount);
	if (dev == NULL) {
		MSGLN("Can't get device from mount point.");
		goto ext;
	}
	else {
		ret = uffs_FormatDevice(dev, force);
		if (ret != U_SUCC) {
			MSGLN("Format fail.");
		}
		else {
			MSGLN("Format succ.");
			rc = 0;
		}
		uffs_PutDevice(dev);
	}

	uffs_close(fd);  // this should fail on signature check !
ext:
	return rc;
}



/**
 * usage: t_pfs <start> <n>
 *
 * for example: t_pfs /x/ 100
 *
 * This test case performs:
 *   1) create <n> files under <start>, write full file name as file content
 *   2) list files under <start>, check files are all listed once
 *   3) check file content aganist file name
 *   4) delete files on success
 */
static int cmd_TestPopulateFiles(int argc, char *argv[])
{
	const char *start = "/";
	int count = 80;
	int i, fd, num;
	char name[128];
	char buf[128];
	uffs_DIR *dirp;
	struct uffs_dirent *ent;
	unsigned long bitmap[50] = {0};	// one bit per file, maximu 32*50 = 1600 files
	UBOOL succ = U_TRUE;

#define SBIT(n) bitmap[(n)/(sizeof(bitmap[0]) * 8)] |= (1 << ((n) % (sizeof(bitmap[0]) * 8)))
#define GBIT(n) (bitmap[(n)/(sizeof(bitmap[0]) * 8)] & (1 << ((n) % (sizeof(bitmap[0]) * 8))))

	if (argc > 1) {
		start = argv[1];
		if (argc > 2) {
			count = strtol(argv[2], NULL, 10);
		}
	}

	if (count > sizeof(bitmap) * 8)
		count = sizeof(bitmap) * 8;

	for (i = 0, fd = -1; i < count; i++) {
		sprintf(name, "%sFile%03d", start, i);
		fd = uffs_open(name, UO_RDWR|UO_CREATE|UO_TRUNC);
		if (fd < 0) {
			MSGLN("Create file %s failed", name);
			break;
		}
		if (uffs_write(fd, name, strlen(name)) != strlen(name)) { // write full path name to file
			MSGLN("Write to file %s failed", name);
			uffs_close(fd);
			break;
		}
		uffs_close(fd);
	}

	if (i < count) {
		// not success, need to clean up
		for (; i >= 0; i--) {
			sprintf(name, "%sFile%03d", start, i);
			if (uffs_remove(name) < 0)
				MSGLN("Delete file %s failed", name);
		}
		succ = U_FALSE;
		goto ext;
	}

	MSGLN("%d files created.", count);

	// list files
	dirp = uffs_opendir(start);
	if (dirp == NULL) {
		MSGLN("Can't open dir %s !", start);
		succ = U_FALSE;
		goto ext;
	}
	ent = uffs_readdir(dirp);
	while (ent && succ) {

		if (!(ent->d_type & FILE_ATTR_DIR) &&					// not a dir
			ent->d_namelen == strlen("File000") &&				// check file name length
			memcmp(ent->d_name, "File", strlen("File")) == 0) {	// file name start with "File"
			
			MSGLN("List entry %s", ent->d_name);

			num = strtol(ent->d_name + 4, NULL, 10);
			if (GBIT(num)) {
				// file already listed ?
				MSGLN("File %d listed twice !", ent->d_name);
				succ = U_FALSE;
				break;
			}
			SBIT(num);

			// check file content
			sprintf(name, "%s%s", start, ent->d_name);
			fd = uffs_open(name, UO_RDONLY);
			if (fd < 0) {
				MSGLN("Open file %d for read failed !", name);
			}
			else {
				memset(buf, 0, sizeof(buf));
				num = uffs_read(fd, buf, sizeof(buf));
				if (num != strlen(name)) {
					MSGLN("%s Read data length expect %d but got %d !", name, strlen(name), num);
					succ = U_FALSE;
				}
				else {
					if (memcmp(name, buf, num) != 0) {
						MSGLN("File %s have wrong content '%s' !", name, buf);
						succ = U_FALSE;
					}
				}
				uffs_close(fd);
			}
		}
		ent = uffs_readdir(dirp);
	}
	uffs_closedir(dirp);

	// check absent files
	for (i = 0; i < count; i++) {
		if (GBIT(i) == 0) {
			sprintf(name, "%sFile%03d", start, i);
			MSGLN("File %s not listed !", name);
			succ = U_FALSE;
		}
	}
	
	// delete files if pass the test
	for (i = 0; succ && i < count; i++) {
		sprintf(name, "%sFile%03d", start, i);
		if (uffs_remove(name) < 0) {
			MSGLN("Delete file %s failed", name);
			succ = U_FALSE;
		}
	}

ext:
	MSGLN("Populate files test %s !", succ ? "SUCC" : "FAILED");
	return succ ? 0 : -1;

}

/**
 * Open <file> with <oflag>, save fd to $1
 *
 *		t_open <oflag> <file>
 */
static int cmd_topen(int argc, char *argv[])
{
	int fd;
	const char *name;
	char *p;
	int oflag = 0;

	CHK_ARGC(3, 3);

	name = argv[2];
	p = argv[1];
	while(*p) {
		switch(*p++) {
		case 'a':
			oflag |= UO_APPEND;
			break;
		case 'c':
			oflag |= UO_CREATE;
			break;
		case 't':
			oflag |= UO_TRUNC;
			break;
		case 'w':
			oflag |= UO_RDWR;
			break;
		case 'r':
			oflag |= UO_RDONLY;
			break;
		}
	}

	fd = uffs_open(name, oflag);

	if (fd >= 0) {
		cli_env_set('1', fd);
		return 0;
	}
	else {
		return -1;
	}
}

/**
 * seek file pointer
 *	t_seek <fd> <offset> [<origin>]
 * if success, $1 = file position after seek
 */
static int cmd_tseek(int argc, char *argv[])
{
	int origin = USEEK_SET;
	int offset;
	int fd;
	int ret;

	CHK_ARGC(3, 4);

	if (sscanf(argv[1], "%d", &fd) != 1 ||
		sscanf(argv[2], "%d", &offset) != 1)
	{
		return CLI_INVALID_ARG;
	}

	if (argc > 3) {
		switch(argv[3][0]) {
		case 's':
			origin = USEEK_SET;
			break;
		case 'c':
			origin = USEEK_CUR;
			break;
		case 'e':
			origin = USEEK_END;
			break;
		default:
			return CLI_INVALID_ARG;
		}
	}

	ret = uffs_seek(fd, offset, origin);
	if (ret >= 0) {
		cli_env_set('1', ret);
		return 0;
	}
	else {
		return -1;
	}
}

/**
 * close file
 *	t_close <fd>
 */
static int cmd_tclose(int argc, char *argv[])
{
	int fd;

	CHK_ARGC(2, 2);

	if (sscanf(argv[1], "%d", &fd) == 1) {
		return uffs_close(fd);
	}
	else
		return -1;
}

/**
 * write file
 *	t_write <fd> <txt> [..]
 */
static int cmd_twrite(int argc, char *argv[])
{
	int fd;
	int i, len = 0;
	int ret = 0;

	CHK_ARGC(3, 0);
	if (sscanf(argv[1], "%d", &fd) != 1) {
		return -1;
	}
	else {
		for (i = 2; i < argc; i++) {
			len = strlen(argv[i]);
			if (uffs_write(fd, argv[i], len) != len) {
				ret = -1;
				break;
			}
		}
	}

	if (ret == 0)
		cli_env_set('1', len);

	return ret;
}

/**
 * read and check seq file
 *	t_check_seq <fd> <size>
 */
static int cmd_tcheck_seq(int argc, char *argv[])
{
	int fd;
	int len, size;
	int ret = 0, r_ret = 0;
	long pos;
	u8 buf[MAX_TEST_BUF_LEN];
	int i;
	u8 x;

	CHK_ARGC(3, 3);

	if (sscanf(argv[1], "%d", &fd) != 1) {
		return -1;
	}

	if (sscanf(argv[2], "%d", &len) != 1) {
		return -1;
	}

	pos = uffs_tell(fd);
	while (len > 0) {
		size = (len > sizeof(buf) ? sizeof(buf) : len);
		if ((r_ret = uffs_read(fd, buf, size)) < 0) {
			MSGLN("Read fail! fd = %d, size = %d, pos = %ld", fd, size, pos);
			ret = -1;
			break;
		}

		// check seq
		for (i = 0; i < r_ret; i++) {
			x = (pos + SEQ_INIT + i) % SEQ_MOD_LEN;
			if (buf[i] != x) {
				MSGLN("Check fail! fd = %d, pos = %ld (expect 0x%02x but 0x%02x)\n", fd, pos + i, x, buf[i]);
				ret = -1;
				break;
			}
		}

		if (ret < 0)
			break;

		len -= r_ret;
		pos += r_ret;
	}

	return ret;
}



/**
 * write random seq to file
 *	t_write_seq <fd> <size>
 */
static int cmd_twrite_seq(int argc, char *argv[])
{
	int fd;
	int len = 0, size = 0;
	long pos = 0;
	int ret = 0, w_ret = 0;
	u8 buf[MAX_TEST_BUF_LEN];

	CHK_ARGC(3, 3);
	if (sscanf(argv[1], "%d", &fd) != 1) {
		return -1;
	}

	if (sscanf(argv[2], "%d", &len) != 1) {
		return -1;
	}

	pos = uffs_tell(fd);
	while (len > 0) {
		size = (len < sizeof(buf) ? len : sizeof(buf));
		memcp_seq(buf, size, pos);
		if ((w_ret = uffs_write(fd, buf, size)) < 0) {
			MSGLN("write fail! fd = %d, size = %d, pos = %ld", fd, size, pos);
			ret = -1;
			break;
		}
		pos += w_ret;
		len -= w_ret;
	}

	if (ret == 0)
		cli_env_set('1', len);

	return ret;
}


/**
 * read and check file
 *	t_read <fd> <txt>
 */
static int cmd_tread(int argc, char *argv[])
{
	int fd;
	int len, n;
	int ret = 0;
	char buf[64];
	char *p;

	CHK_ARGC(3, 3);

	if (sscanf(argv[1], "%d", &fd) != 1) {
		return -1;
	}
	else {
		len = strlen(argv[2]);
		n = 0;
		p = argv[2];
		while (n < len) {
			n = (len > sizeof(buf) ? sizeof(buf) : len);
			if (uffs_read(fd, buf, n) != n ||
				memcmp(buf, p, n) != 0) {
				ret = -1;
				break;
			}
			len -= n;
			p += n;
		}
	}

	return ret;
}


static void do_dump_page(uffs_Device *dev, uffs_Buf *buf)
{
	int i, j;
	const int line = 16;
	struct uffs_MiniHeaderSt *header = (struct uffs_MiniHeaderSt *)buf->header;
	MSG("  header.status = %d\n", header->status);
	if (header->status != 0xFF) {
		for (i = 0; i < 64; i += line) {
			MSG("    ");
			for (j = 0; j < line; j++)
				MSG("%02X ", buf->header[i+j]);
			MSG("\n");
		}
		MSG("\n");
	}
}

static void do_dump_tag(uffs_Device *dev, uffs_Tags *tag)
{
	MSG("  tag sealed: %s\n", TAG_IS_SEALED(tag) ? "yes" : "no");
	if (TAG_IS_GOOD(tag)) {
		if (TAG_IS_DIRTY(tag)) {
			MSG("    block_ts = %d\n", tag->s.block_ts);
			MSG("    type = %d\n", tag->s.type);
			MSG("    dirty = %d\n", tag->s.dirty);
			MSG("    page_id = %d\n", tag->s.page_id);
			MSG("    serial = %d\n", tag->s.serial);
			MSG("    parent = %d\n", tag->s.parent);
			MSG("    data_len = %d\n", tag->s.data_len);
		}
		else {
			MSG("  tag is GOOD but NOT DIRTY !!!???\n");
		}
	}
	else if (TAG_IS_SEALED(tag)) {
		MSG(" tag is INVALID\n");
	}
}

static void do_dump_device(uffs_Device *dev)
{
	URET ret;
	int block, page;
	uffs_Tags tag;
	uffs_Buf *buf;

	buf = uffs_BufClone(dev, NULL);
	if (buf == NULL) {
		MSGLN("Can't clone buf");
		return;
	}

	for (block = dev->par.start; block <= dev->par.end; block++) {
		MSG("---- block %d ----\n", block);
		for (page = 0; page < dev->attr->pages_per_block; page++) {
			MSG("  == page %d ==\n", page);
			ret = uffs_FlashReadPage(dev, block, page, buf, U_FALSE);
			if (UFFS_FLASH_HAVE_ERR(ret)) {
				MSG(" !!! Read page failed, ret = %d !!!\n", ret);
			}
			else {
				do_dump_page(dev, buf);
				if (buf->header[0] != 0xFF) {
					ret = uffs_FlashReadPageTag(dev, block, page, &tag);
					if (UFFS_FLASH_HAVE_ERR(ret)) {
						MSG(" !!! Read TAG failed, ret = %d !!!\n", ret);
					}
					else {
						do_dump_tag(dev, &tag);
					}
				}
			}
		}
	}
	uffs_BufFreeClone(dev, buf);
}

static int cmd_dump(int argc, char *argv[])
{
	const char *mount = "/";
	uffs_Device *dev;

	if (argc > 1) {
		mount = argv[1];
	}

	MSGLN("Dumping %s ... ", mount);

	dev = uffs_GetDeviceFromMountPoint(mount);
	if (dev == NULL) {
		MSGLN("Can't get device from mount point.");
	}
	else {
		do_dump_device(dev);
		uffs_PutDevice(dev);
	}

	return 0;
}

static int cmd_apisrv(int argc, char *argv[])
{
	return api_server_start();
}

static const struct cli_command test_cmds[] = 
{
    { cmd_t1,					"t1",			"<name>",			"test 1" },
    { cmd_t2,					"t2",			NULL,				"test 2" },
    { cmd_t3,					"t3",			"<name> [<noecc>]",	"test 3" },
    { cmd_t4,					"t4",			NULL,				"test 4" },
    { cmd_t5,					"t5",			"<name>",			"test 5" },
    { cmd_TestPageReadWrite,	"t_pgrw",		NULL,				"test page read/write" },
    { cmd_TestFormat,			"t_format",		NULL,				"test format file system" },
	{ cmd_TestPopulateFiles,	"t_pfs",		"[<start> [<n>]]",	"test populate <n> files under <start>" },
	{ cmd_VerifyFile,			"t_vf",			"<file> [<noecc>]", "verify file" },

	{ cmd_topen,				"t_open",		"<oflg> <file>",	"open file, fd save to $1", },
	{ cmd_tread,				"t_read",		"<fd> <txt>",		"read <fd> and check against <txt>", },
	{ cmd_tcheck_seq,			"t_check_seq",	"<fd> <size>",		"read seq file <fd> and check", },
	{ cmd_twrite,				"t_write",		"<fd> <txt> [...]",	"write <fd>", },
	{ cmd_twrite_seq,			"t_write_seq",	"<fd> <size>",	"write seq file <fd>", },
	{ cmd_tseek,				"t_seek",		"<fd> <offset> [<origin>]",	"seek <fd> file pointer to <offset> from <origin>", },
	{ cmd_tclose,				"t_close",		"<fd>",				"close <fd>", },
	{ cmd_dump,					"dump",			"<mount>",			"dump <mount>", },

	{ cmd_apisrv,				"apisrv",		NULL,				"start API test server", },

    { NULL, NULL, NULL, NULL }
};

static struct cli_commandset test_cmdset = {
	test_cmds,
};

struct cli_commandset * get_test_cmds()
{
	return &test_cmdset;
};



