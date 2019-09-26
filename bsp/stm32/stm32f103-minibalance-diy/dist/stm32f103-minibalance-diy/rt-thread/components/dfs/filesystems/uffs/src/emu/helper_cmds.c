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
#include <stdarg.h>
#include <stdlib.h>
#include "uffs_config.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_fs.h"
#include "uffs/uffs_utils.h"
#include "uffs/uffs_core.h"
#include "uffs/uffs_mtb.h"
#include "uffs/uffs_find.h"
#include "cmdline.h"
#include "uffs/uffs_fd.h"
#include "uffs/uffs_mtb.h"
#include "uffs_fileem.h"

#define PFX "cmd : "

#define MAX_PATH_LENGTH 128

#define MSGLN(msg,...) uffs_Perror(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)
#define MSG(msg,...) uffs_PerrorRaw(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)

/** format [<mount>] */
static int cmd_format(int argc, char *argv[])
{
	URET ret;
	const char *mount = "/";
	uffs_Device *dev;
	UBOOL force = U_FALSE;

	if (argc > 1) {
		mount = argv[1];
		if (argc > 2 && strcmp(argv[2], "-f") == 0)
			force = U_TRUE;
	}
	MSGLN("Formating %s ... ", mount);

	dev = uffs_GetDeviceFromMountPoint(mount);
	if (dev == NULL) {
		MSGLN("Can't get device from mount point.");
		return -1;
	}
	else {
		ret = uffs_FormatDevice(dev, force);
		if (ret != U_SUCC) {
			MSGLN("Format fail.");
			return -1;
		}
		else {
			MSGLN("Format succ.");
		}
		uffs_PutDevice(dev);
	}

	return 0;
}

/** mkf <file> */
static int cmd_mkf(int argc, char *argv[])
{
	int fd;
	const char *name;
	int oflags = UO_RDWR | UO_CREATE;

	CHK_ARGC(2, 2);

	name = argv[1];
	fd = uffs_open(name, oflags);
	if (fd < 0) {
		MSGLN("Create %s fail, err: %d", name, uffs_get_error());
		return -1;
	}
	else {
		MSGLN("Create %s succ.", name);
		uffs_close(fd);
	}
	
	return 0;
}

/** mkdir <dir> */
static int cmd_mkdir(int argc, char *argv[])
{
	const char *name;

	CHK_ARGC(2, 0);

	name = argv[1];
	
	if (uffs_mkdir(name) < 0) {
		MSGLN("Create %s fail, err: %d", name, uffs_get_error());
		return -1;
	}
	else {
		MSGLN("Create %s succ.", name);
	}

	return 0;
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

static int cmd_pwd(int argc, char *argv[])
{
	MSGLN("not supported.");
	return 0;
}

static int cmd_cd(int argc, char *argv[])
{
	MSGLN("Not supported");
	return 0;
}

/** ls [<dir>] */
static int cmd_ls(int argc, char *argv[])
{
	uffs_DIR *dirp;
	struct uffs_dirent *ent;
	struct uffs_stat stat_buf;
	int count = 0;
	char buf[MAX_PATH_LENGTH+2];
	const char *name = "/";
	char *sub;
	int ret = 0;

	CHK_ARGC(1, 2);

	if (argc > 1)
		name = argv[1];

	dirp = uffs_opendir(name);
	if (dirp == NULL) {
		MSGLN("Can't open '%s' for list", name);
		ret = -1;
	}
	else {
		MSG("------name-----------size---------serial-----" TENDSTR);
		ent = uffs_readdir(dirp);
		while (ent) {
			MSG("%9s", ent->d_name);
			strcpy(buf, name);
			sub = buf;
			if (name[strlen(name)-1] != '/')
				sub = strcat(buf, "/");
			sub = strcat(sub, ent->d_name);
			if (ent->d_type & FILE_ATTR_DIR) {
				sub = strcat(sub, "/");
				MSG("/  \t<%8d>", CountObjectUnder(sub));
			}
			else {
				uffs_stat(sub, &stat_buf);
				MSG("   \t %8d ", stat_buf.st_size);
			}
			MSG("\t%6d" TENDSTR, ent->d_ino);
			count++;
			ent = uffs_readdir(dirp);
		}
		
		uffs_closedir(dirp);

		MSG("Total: %d objects." TENDSTR, count);
	}

	return ret;
}

/** rm <obj> */
static int cmd_rm(int argc, char *argv[])
{
	const char *name = NULL;
	int ret = 0;
	struct uffs_stat st;

	CHK_ARGC(2, 2);

	name = argv[1];

	ret = uffs_stat(name, &st);
	if (ret < 0) {
		MSGLN("Can't stat '%s'", name);
		return ret;
	}

	if (st.st_mode & US_IFDIR) {
		ret = uffs_rmdir(name);
	}
	else {
		ret = uffs_remove(name);
	}

	if (ret == 0)
		MSGLN("Delete '%s' succ.", name);
	else
		MSGLN("Delete '%s' fail!", name);

	return ret;
}

/** ren|mv <old> <new> */
static int cmd_ren(int argc, char *argv[])
{
	const char *oldname;
	const char *newname;
	int ret;

	CHK_ARGC(3, 3);

	oldname = argv[1];
	newname = argv[2];

	if ((ret = uffs_rename(oldname, newname)) == 0) {
		MSGLN("Rename from '%s' to '%s' succ.", oldname, newname);
	}
	else {
		MSGLN("Rename from '%s' to '%s' fail!", oldname, newname);
	}

	return ret;
}

static void dump_msg_to_stdout(struct uffs_DeviceSt *dev, const char *fmt, ...)
{
	uffs_FileEmu *emu = (uffs_FileEmu *)(dev->attr->_private);
	va_list args;

	va_start(args, fmt);
	//vprintf(fmt, args);
	if (emu && emu->dump_fp)
		vfprintf(emu->dump_fp, fmt, args);
	va_end(args);
}

/** dump [<mount>] */
static int cmd_dump(int argc, char *argv[])
{
	uffs_Device *dev;
	uffs_FileEmu *emu;
	const char *mount = "/";
	const char *dump_file = "dump.txt";

	if (argc > 1) {
		mount = argv[1];
		if (argc > 2)
			dump_file = argv[2];
	}

	dev = uffs_GetDeviceFromMountPoint(mount);
	if (dev == NULL) {
		MSGLN("Can't get device from mount point %s", mount);
		return -1;
	}

	emu = (uffs_FileEmu *)(dev->attr->_private);
	emu->dump_fp = fopen(dump_file, "w");

	uffs_DumpDevice(dev, dump_msg_to_stdout);

	if (emu->dump_fp)
		fclose(emu->dump_fp);

	uffs_PutDevice(dev);

	return 0;
}

/** st [<mount>] */
static int cmd_st(int argc, char *argv[])
{
	uffs_Device *dev;
	const char *mount = "/";
	uffs_FlashStat *s;
	TreeNode *node;

	if (argc > 1) {
		mount = argv[1];
	}

	dev = uffs_GetDeviceFromMountPoint(mount);
	if (dev == NULL) {
		MSGLN("Can't get device from mount point %s", mount);
		return -1;
	}

	s = &(dev->st);

	MSG("----------- basic info -----------" TENDSTR);
	MSG("TreeNode size:         %d" TENDSTR, sizeof(TreeNode));
	MSG("TagStore size:         %d" TENDSTR, sizeof(struct uffs_TagStoreSt));
	MSG("MaxCachedBlockInfo:    %d" TENDSTR, dev->cfg.bc_caches);
	MSG("MaxPageBuffers:        %d" TENDSTR, dev->cfg.page_buffers);
	MSG("MaxDirtyPagesPerBlock: %d" TENDSTR, dev->cfg.dirty_pages);
	MSG("MaxPathLength:         %d" TENDSTR, MAX_PATH_LENGTH);
	MSG("MaxObjectHandles:      %d" TENDSTR, MAX_OBJECT_HANDLE);
	MSG("FreeObjectHandles:     %d" TENDSTR, uffs_GetFreeObjectHandlers());
	MSG("MaxDirHandles:         %d" TENDSTR, MAX_DIR_HANDLE);
	MSG("FreeDirHandles:        %d" TENDSTR, uffs_PoolGetFreeCount(uffs_DirEntryBufGetPool()));

	MSG("----------- statistics for '%s' -----------" TENDSTR, mount);
	MSG("Device Ref:            %d" TENDSTR, dev->ref_count);
	MSG("Block Erased:          %d" TENDSTR, s->block_erase_count);
	MSG("Write Page:            %d" TENDSTR, s->page_write_count);
	MSG("Write Spare:           %d" TENDSTR, s->spare_write_count);
	MSG("Read Page:             %d" TENDSTR, s->page_read_count - s->page_header_read_count);
	MSG("Read Header:           %d" TENDSTR, s->page_header_read_count);
	MSG("Read Spare:            %d" TENDSTR, s->spare_read_count);
	MSG("I/O Read:              %lu" TENDSTR, s->io_read);
	MSG("I/O Write:             %lu" TENDSTR, s->io_write);

	MSG("--------- partition info for '%s' ---------" TENDSTR, mount);
	MSG("Space total:           %d" TENDSTR, uffs_GetDeviceTotal(dev));
	MSG("Space used:            %d" TENDSTR, uffs_GetDeviceUsed(dev));
	MSG("Space free:            %d" TENDSTR, uffs_GetDeviceFree(dev));
	MSG("Page Size:             %d" TENDSTR, dev->attr->page_data_size);
	MSG("Spare Size:            %d" TENDSTR, dev->attr->spare_size);
	MSG("Pages Per Block:       %d" TENDSTR, dev->attr->pages_per_block);
	MSG("Block size:            %d" TENDSTR, dev->attr->page_data_size * dev->attr->pages_per_block);
	MSG("Total blocks:          %d of %d" TENDSTR, (dev->par.end - dev->par.start + 1), dev->attr->total_blocks);
	if (dev->tree.bad) {
		MSG("Bad blocks: ");
		node = dev->tree.bad;
		while(node) {
			MSG("%d, ", node->u.list.block);
			node = node->u.list.next;
		}
		MSG(TENDSTR);
	}

	uffs_PutDevice(dev);

	return 0;

}

/** cp <src> <des> */
static int cmd_cp(int argc, char *argv[])
{
	const char *src;
	const char *des;
	char buf[100];
	int fd1 = -1, fd2 = -1;
	int len;
	BOOL src_local = FALSE, des_local = FALSE;
	FILE *fp1 = NULL, *fp2 = NULL;
	int ret = -1;

	CHK_ARGC(3, 3);

	src = argv[1];
	des = argv[2];

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
			MSGLN("Can't open %s for copy.", src);
			goto fail_ext;
		}
	}
	else {
		if ((fd1 = uffs_open(src, UO_RDONLY)) < 0) {
			MSGLN("Can't open %s for copy.", src);
			goto fail_ext;
		}
	}

	if (des_local) {
		if ((fp2 = fopen(des, "wb")) == NULL) {
			MSGLN("Can't open %s for copy.", des);
			goto fail_ext;
		}
	}
	else {
		if ((fd2 = uffs_open(des, UO_RDWR|UO_CREATE|UO_TRUNC)) < 0) {
			MSGLN("Can't open %s for copy.", des);
			goto fail_ext;
		}
	}

	ret = 0;
	while (	(src_local ? (feof(fp1) == 0) : (uffs_eof(fd1) == 0)) ) {
		ret = -1;
		if (src_local) {
			len = fread(buf, 1, sizeof(buf), fp1);
		}
		else {
			len = uffs_read(fd1, buf, sizeof(buf));
		}
		if (len == 0) {
			ret = -1;
			break;
		}
		if (len < 0) {
			MSGLN("read file %s fail ?", src);
			break;
		}
		if (des_local) {
			if ((int)fwrite(buf, 1, len, fp2) != len) {
				MSGLN("write file %s fail ? ", des);
				break;
			}
		}
		else {
			if (uffs_write(fd2, buf, len) != len) {
				MSGLN("write file %s fail ? ", des);
				break;
			}
		}
		ret = 0;
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

	return ret;
}

/** cat <file> [<offset>] [<size>] */
static int cmd_cat(int argc, char *argv[])
{
	int fd;
	const char *name = NULL;
	char buf[100];
	int start = 0, size = 0, printed = 0, n, len;
	int ret = -1;

	CHK_ARGC(2, 4);

	name = argv[1];

	if ((fd = uffs_open(name, UO_RDONLY)) < 0) {
		MSGLN("Can't open %s", name);
		goto fail;
	}

	if (argc > 2) {
		start = strtol(argv[2], NULL, 10);
		if (argc > 3) size = strtol(argv[3], NULL, 10);
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
				MSG("%s", buf);
				printed += n;
			}
			else {
				break;
			}
		}
	}
	MSG(TENDSTR);
	uffs_close(fd);

	ret = 0;
fail:

	return ret;
}

/** mount partition or show mounted partitions
 *		mount [<mount>]
 */
static int cmd_mount(int argc, char *argv[])
{
	uffs_MountTable *tab;
	const char *mount = NULL;

	if (argc == 1) {
		tab = uffs_MtbGetMounted();
		while (tab) {
			MSG(" %s : (%d) ~ (%d)\n", tab->mount, tab->start_block, tab->end_block);
			tab = tab->next;
		}
	}
	else {
		mount = argv[1];
		if (uffs_Mount(mount) < 0) {
			MSGLN("Can't mount %s", mount);
			return -1;
		}
	}
	return 0;
}

/** unmount parition or show unmounted partitions
 *		umount [<mount>]
 */
static int cmd_unmount(int argc, char *argv[])
{
	uffs_MountTable *tab;
	const char *mount = NULL;

	if (argc == 1) {
		tab = uffs_MtbGetUnMounted();
		while (tab) {
			MSG(" %s : (%d) ~ (%d)\n", tab->mount, tab->start_block, tab->end_block);
			tab = tab->next;
		}
	}
	else {
		mount = argv[1];
		if (uffs_UnMount(mount) < 0) {
			MSGLN("Can't unmount %s", mount);
			return -1;
		}
	}

	return 0;
}

/** inspect buffers
 *		inspb [<mount>]
 */
static int cmd_inspb(int argc, char *argv[])
{
	uffs_Device *dev;
	const char *mount = "/";

	CHK_ARGC(1, 2);

	dev = uffs_GetDeviceFromMountPoint(mount);
	if (dev == NULL) {
		MSGLN("Can't get device from mount point %s", mount);
		return -1;
	}
	uffs_BufInspect(dev);
	uffs_PutDevice(dev);

	return 0;

}

/** print block wear-leveling information
 *		wl [<mount>]
 */
static int cmd_wl(int argc, char *argv[])
{
	const char *mount = "/";
	uffs_Device *dev;
	struct uffs_PartitionSt *par;
	uffs_FileEmu *emu;
	int i, max;
	u32 n;

#define NUM_PER_LINE	10

	CHK_ARGC(1, 2);

	if (argc > 1) {
		mount = argv[1];
	}

	dev = uffs_GetDeviceFromMountPoint(mount);
	if (dev == NULL) {
		MSGLN("Can't get device from mount point %s", mount);
		return -1;
	}

	par = &dev->par;
	emu = (uffs_FileEmu *)(dev->attr->_private);
	max = -1;

	for (i = 0; i < par->end - par->start; i++) {
		if ((i % NUM_PER_LINE) == 0) {
			MSG("%04d:", i + par->start);
		}
		n = i + par->start;
		max = (max == -1 ? n :
				(emu->em_monitor_block[n] > emu->em_monitor_block[max] ? n : max)
			   );
		MSG(" %4d", emu->em_monitor_block[n]);
		if (uffs_TreeFindBadNodeByBlock(dev, n))
			MSG("%c", 'x');
		else if (uffs_TreeFindErasedNodeByBlock(dev, n))
			MSG("%c", ' ');
		else
			MSG("%c", '.');
		if (((i + 1) % NUM_PER_LINE) == 0)
			MSG("\n");
	}
	MSG("\n");
	MSG("Total blocks %d, peak erase count %d at block %d\n",
		par->end - par->start, max == -1 ? 0 : emu->em_monitor_block[max], max);

	uffs_PutDevice(dev);

	return 0;
}

static const struct cli_command helper_cmds[] = 
{
    { cmd_format,	"format",		"[<mount>]",		"Format device" },
    { cmd_mkf,		"mkfile",		"<name>",			"create a new file" },
    { cmd_mkdir,	"mkdir",		"<name>",			"create a new directory" },
    { cmd_rm,		"rm",			"<name>",			"delete file/directory" },
    { cmd_ren,		"mv|ren",		"<old> <new>",		"rename file/directory" },
    { cmd_ls,		"ls",			"<dir>",			"list dirs and files" },
    { cmd_st,		"info|st",		"<mount>",			"show statistic infomation" },
    { cmd_cp,		"cp",			"<src> <des>",		"copy files. the local file name start with '::'" },
    { cmd_cat,		"cat",			"<name>",			"show file content" },
    { cmd_pwd,		"pwd",			NULL,				"show current dir" },
    { cmd_cd,		"cd",			"<path>",			"change current dir" },
    { cmd_mount,	"mount",		"[<mount>]",		"mount partition or list mounted partitions" },
    { cmd_unmount,	"umount",		"[<mount>]",		"unmount partition" },
	{ cmd_dump,		"dump",			"[<mount>]",		"dump file system", },
	{ cmd_wl,		"wl",			"[<mount>]",		"show block wear-leveling info", },
	{ cmd_inspb,	"inspb",		"[<mount>]",		"inspect buffer", },
    { NULL, NULL, NULL, NULL }
};

static struct cli_commandset helper_cmdset = {
	helper_cmds,
};

struct cli_commandset * get_helper_cmds()
{
	return &helper_cmdset;
};
