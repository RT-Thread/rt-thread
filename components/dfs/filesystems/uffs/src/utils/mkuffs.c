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
 * \file uffs_test.c
 * \brief uffs test main entry
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

#include "cmdline.h"
#include "uffs_fileem.h"

#if CONFIG_USE_STATIC_MEMORY_ALLOCATOR > 0
int main()
{
	printf("Static memory allocator is not supported.\n");
	return 0;
}
#else

extern struct cli_commandset * get_helper_cmds(void);
extern struct cli_commandset * get_test_cmds(void);
extern void femu_init_uffs_device(uffs_Device *dev);

#if CONFIG_USE_NATIVE_MEMORY_ALLOCATOR > 0
static int conf_memory_pool_size_kb = 800; /* default allocate 100k memory. */
static void *memory_pool = NULL;
#endif

static int conf_command_line_mode = 0;
static int conf_verbose_mode = 0;

static int conf_exec_script = 0;
static char script_file_name[256];

#define DEFAULT_EMU_FILENAME "uffsemfile.bin"
const char * conf_emu_filename = DEFAULT_EMU_FILENAME;


/* default basic parameters of the NAND device */
int conf_pages_per_block = 32;
int conf_pages_data_size = 512;
int conf_pages_spare_size = 16;
int conf_status_byte_offset = 5;
int conf_total_blocks =	128;

#define PAGE_SIZE				(conf_pages_data_size + conf_pages_spare_size)
#define BLOCK_DATA_SIZE				(conf_pages_per_block * conf_pages_data_size)
#define TOTAL_DATA_SIZE				(conf_total_blocks * BLOCK_DATA_SIZE)
#define BLOCK_SIZE				(conf_pages_per_block * PAGE_SIZE)
#define TOTAL_SIZE				(BLOCK_SIZE * conf_total_blocks)

#define MAX_MOUNT_TABLES			10
#define MAX_MOUNT_POINT_NAME			32

static struct uffs_MountTableEntrySt conf_mounts[MAX_MOUNT_TABLES] = {0};
static uffs_Device conf_devices[MAX_MOUNT_TABLES] = {0};
static char mount_point_name[MAX_MOUNT_TABLES][MAX_MOUNT_POINT_NAME] = {0};

static struct uffs_StorageAttrSt emu_storage = {0};
static struct uffs_FileEmuSt emu_private = {0};



#if CONFIG_USE_NATIVE_MEMORY_ALLOCATOR > 0
BOOL cmdMeminfo(const char *tail)
{
	const char *mount = "/";
	int i;
	HeapMm *mm;
	int count = 0;
	int blocks = 0;

	uffs_Device *dev;
	
	if (tail) 
		mount = cli_getparam(tail, NULL);

	dev = uffs_GetDeviceFromMountPoint(mount);

	if (!dev) {
		printf("can't get device from mount point %s\n", mount);
		return TRUE;
	}
	
	for (i = 0; i < HEAP_HASH_SIZE; i++) {
		mm = dev->mem.tbl[i];
		while (mm) {
			printf("%d, ", mm->size);
			count += mm->size;
			blocks++;
			mm = mm->next;
		}
	}
	printf("\n>>> total allocated %d blocks (%d bytes), max %d bytes. <<<\n", blocks, count, dev->mem.maxused);
	
	uffs_PutDevice(dev);

	return TRUE;
}
#endif


static struct cli_commandset basic_cmdset[] = 
{
#if CONFIG_USE_NATIVE_MEMORY_ALLOCATOR > 0
    { cmdMeminfo,	"mem",			"<mount>",			"show native memory allocator infomation" },
#endif
    { NULL, NULL, NULL, NULL }
};


static void setup_emu_storage(struct uffs_StorageAttrSt *attr)
{
	attr->total_blocks = conf_total_blocks;				/* total blocks */
	attr->page_data_size = conf_pages_data_size;		/* page data size */
	attr->spare_size = conf_pages_spare_size;			/* page spare size */
	attr->pages_per_block = conf_pages_per_block;		/* pages per block */

	attr->block_status_offs = conf_status_byte_offset;	/* block status offset is 5th byte in spare */
	attr->ecc_opt = UFFS_ECC_SOFT;				/* let UFFS handle the ECC */
	attr->layout_opt = UFFS_LAYOUT_UFFS;		/* let UFFS handle layout */
}

static void setup_emu_private(uffs_FileEmu *emu)
{
	memset(emu, 0, sizeof(uffs_FileEmu));
	emu->emu_filename = conf_emu_filename;
}

static int init_uffs_fs(void)
{
	static int bIsFileSystemInited = 0;
	struct uffs_MountTableEntrySt *mtbl = &(conf_mounts[0]);

	if(bIsFileSystemInited) return -4;
	bIsFileSystemInited = 1;

#if CONFIG_USE_NATIVE_MEMORY_ALLOCATOR > 0
	// init protected heap for native memory allocator
	memory_pool = malloc(conf_memory_pool_size_kb * 1024);
	if (memory_pool)
		uffs_MemInitHeap(memory_pool, conf_memory_pool_size_kb * 1024);
	else {
		uffs_Perror(UFFS_ERR_SERIOUS, "Can't alloc memory (size = %dKB) for uffs.", conf_memory_pool_size_kb);
		return -1;
	}
#endif

	setup_emu_storage(&emu_storage);
	setup_emu_private(&emu_private);
	emu_storage._private = &emu_private;
	
	while (mtbl->dev) {
		mtbl->dev->attr = &emu_storage;
#if CONFIG_USE_NATIVE_MEMORY_ALLOCATOR > 0
		uffs_MemSetupNativeAllocator(&mtbl->dev->mem);
#endif

#if CONFIG_USE_SYSTEM_MEMORY_ALLOCATOR > 0
		uffs_MemSetupSystemAllocator(&mtbl->dev->mem);
#endif
		uffs_fileem_setup_device(mtbl->dev);
		uffs_RegisterMountTable(mtbl);
		mtbl++;
	}

	return uffs_InitMountTable() == U_SUCC ? 0 : -1;
}

static int release_uffs_fs(void)
{
	int ret;
	ret = uffs_ReleaseMountTable();
#if CONFIG_USE_NATIVE_MEMORY_ALLOCATOR > 0
	if (memory_pool) {
		free(memory_pool);
		memory_pool = NULL;
	}
#endif
	return ret;
}

/* mount point arg: /sys/,100,-1 */
static int parse_mount_point(char *arg, int m_idx)
{
	int start = 0, end = -1;
	char *p = arg;
	struct uffs_MountTableEntrySt *mtbl = &(conf_mounts[m_idx]);

	while(*p && *p != ',' && *p != ' ' && *p != '\t')
		p++;

	if (*p == 0 || p == arg) 
		return -1;

	mtbl->mount = &(mount_point_name[m_idx][0]);
	memcpy((char *)mtbl->mount, arg, p - arg);
	((char *)(mtbl->mount))[p - arg] = 0;

	p++;
	arg = p;
	while(*p && *p != ',' && *p != ' ' && *p != '\t')
		p++;

	if (p != arg) {
		if (sscanf(arg, "%i", &start) < 1) 
			return -1;
		p++;
		arg = p;

		while(*p && *p != ',' && *p != ' ' && *p != '\t')
			p++;

		if (p != arg) {
			if (sscanf(arg, "%i", &end) < 1)
				return -1;
		}
	}
	mtbl->start_block = start;
	mtbl->end_block = end;
	mtbl->dev = &(conf_devices[m_idx]);

	return 0;
}

static int parse_options(int argc, char *argv[])
{
    int iarg;
    int usage = 0;
	int m_idx = 0;
    static char em_file[128];

    for (iarg = 1; iarg < argc && !usage; iarg++) {
        const char *arg = argv[iarg];
        
        if (arg[0] == '-') {
            if (!strcmp(arg, "-h") || !strcmp(arg, "--help")) {
                usage++;
            }
            else if (!strcmp(arg, "-f") || !strcmp(arg, "--file")) {
                if (++iarg >= argc)
					usage++;
				else {
					strcpy(em_file, argv[iarg]);
					conf_emu_filename = (const char *)em_file;
				}
            }
            else if (!strcmp(arg, "-c") || !strcmp(arg, "--command-line")) {
				conf_command_line_mode = 1;
            }
            else if (!strcmp(arg, "-p") || !strcmp(arg, "--page-size")) {
                if (++iarg >= argc) 
					usage++;
                else if (sscanf(argv[iarg], "%i", &conf_pages_data_size) < 1)
					usage++;
				if (conf_pages_data_size <= 0 || (conf_pages_data_size % 512))
					usage++;
            }
            else if (!strcmp(arg, "-s") || !strcmp(arg, "--spare-size")) {
                if (++iarg >= argc) 
					usage++;
                else if (sscanf(argv[iarg], "%i", &conf_pages_spare_size) < 1) 
					usage++;
				if (conf_pages_spare_size < 16 || (conf_pages_spare_size % 4))
					usage++;
            }
            else if (!strcmp(arg, "-o") || !strcmp(arg, "--status-offset")) {
                if (++iarg >= argc) 
					usage++;
                else if (sscanf(argv[iarg], "%i", &conf_status_byte_offset) < 1) 
					usage++;
				if (conf_status_byte_offset < 0)
					usage++;
            }
            else if (!strcmp(arg, "-b") || !strcmp(arg, "--block-pages")) {
                if (++iarg >= argc)
					usage++;
                else if (sscanf(argv[iarg], "%i", &conf_pages_per_block) < 1)
					usage++;
				if (conf_pages_per_block < 2)
					usage++;
            }
            else if (!strcmp(arg, "-t") || !strcmp(arg, "--total-blocks")) {
                if (++iarg >= argc) 
					usage++;
                else if (sscanf(argv[iarg], "%i", &conf_total_blocks) < 1)
					usage++;
				if (conf_total_blocks < 2)
					usage++;
            }
            else if (!strcmp(arg, "-v") || !strcmp(arg, "--verbose")) {
				conf_verbose_mode = 1;
            }
            else if (!strcmp(arg, "-m") || !strcmp(arg, "--mount")) {
				if (++iarg > argc)
					usage++;
				else if (parse_mount_point(argv[iarg], m_idx) < 0)
					usage++;
				m_idx++;
            }
			else if (!strcmp(arg, "-e") || !strcmp(arg, "--exec")) {
				if (++iarg > argc)
					usage++;
				else {
					strcpy(script_file_name, argv[iarg]);
					conf_exec_script = 1;
				}
			}
#if CONFIG_USE_NATIVE_MEMORY_ALLOCATOR > 0
			else if (!strcmp(arg, "-a") || !strcmp(arg, "--alloc")) {
				if (++iarg > argc) 
					usage++;
				else if (sscanf(argv[iarg], "%d", &conf_memory_pool_size_kb) < 1)
					usage++;
				if (conf_memory_pool_size_kb <= 0) 
					usage++;
			}
#endif
            else {
                printf("Unknown option: %s, try %s --help\n", arg, argv[0]);
				return -1;
            }
        }
        else {
            printf("Unexpected parameter: %s, try %s --help\n", arg, argv[0]);
			return -1;
        }
    }
    
    if (usage) {
        printf("Usage: %s [options]\n", argv[0]);
        printf("  -h  --help                        show usage\n");
        printf("  -c  --command-line                command line mode\n");
        printf("  -v  --verbose                     verbose mode\n");
        printf("  -f  --file           <file>       uffs image file\n");
        printf("  -p  --page-size      <n>          page data size, default=512\n");
        printf("  -s  --spare-size     <n>          page spare size, default=16\n");
		printf("  -o  --status-offset  <n>          status byte offset, default=5\n");
        printf("  -b  --block-pages    <n>          pages per block\n");
        printf("  -t  --total-blocks   <n>          total blocks\n");
        printf("  -m  --mount          <mount_point,start,end> , for example: -m /,0,-1\n");
		printf("  -i  --id-man         <id>         set manufacture ID, default=0xEC\n");
        printf("  -e  --exec           <file>       execute a script file\n");
#if CONFIG_USE_NATIVE_MEMORY_ALLOCATOR > 0
		printf("  -a  --alloc          <size>       allocate size(KB) of memory for uffs, default 100\n");
#endif		
        printf("\n");

        return -1;
    }

	if (m_idx == 0) {
		parse_mount_point("/,0,-1", 0);
	}

	return 0;
}


static void print_mount_points(void)
{
	struct uffs_MountTableEntrySt *m;

	m = &(conf_mounts[0]);
	while (m->dev) {
		printf ("Mount point: %s, start: %d, end: %d\n", m->mount, m->start_block, m->end_block);
		m++;
	}
}

static void print_params(void)
{
	printf("uffs image file: %s\n", conf_emu_filename);
	printf("page size: %d\n", conf_pages_data_size);
	printf("page spare size: %d\n", conf_pages_spare_size);
	printf("pages per block: %d\n", conf_pages_per_block);
	printf("total blocks: %d\n", conf_total_blocks);
}

static void exec_script()
{
	char line_buf[256];
	char *p;
	FILE *fp;

	fp = fopen(script_file_name, "r");
	if (fp) {
		memset(line_buf, 0, sizeof(line_buf));
		while (fgets(line_buf, sizeof(line_buf) - 1, fp)) {
			p = line_buf + sizeof(line_buf) - 1;
			while (*p == 0 && p > line_buf)
				p--;
			while ((*p == '\r' || *p == '\n') && p > line_buf) {
				*p-- = 0;
			}
			if (conf_verbose_mode) 
				printf("%s\r\n", line_buf);
			cliInterpret(line_buf);
			memset(line_buf, 0, sizeof(line_buf));
		}
		fclose(fp);
	}
}

int main(int argc, char *argv[])
{

	int ret;

	if (parse_options(argc, argv) < 0) {
		return -1;
	}
	
	if (conf_verbose_mode) {
		print_mount_points();
		print_params();
		#if 0
		printf("TreeNode size: %d\n", sizeof(TreeNode));
		printf("struct BlockListSt: %d\n", sizeof(struct BlockListSt));
		printf("struct DirhSt: %d\n", sizeof(struct DirhSt));
		printf("struct FilehSt: %d\n", sizeof(struct FilehSt));
		printf("struct FdataSt: %d\n", sizeof(struct FdataSt));
		#endif
	}

	ret = init_uffs_fs();
	if (ret != 0) {
		printf ("Init file system fail: %d\n", ret);
		return -1;
	}

	cli_add_commandset(get_helper_cmds());
	cli_add_commandset(get_test_cmds());
	cli_add_commandset(basic_cmdset);
	if (conf_command_line_mode) {
		if (conf_exec_script) {
			exec_script();
		}
		cliMain();
	}
	else {
		if (conf_exec_script) {
			exec_script();
		}
		else {
			cliMain();
		}
	}

	release_uffs_fs();

	return 0;
}
#endif



