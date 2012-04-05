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
#include "uffs_config.h"
#include "uffs/uffs_os.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_fs.h"
#include "uffs/uffs_utils.h"
#include "uffs/uffs_core.h"
#include "uffs/uffs_mtb.h"

#include "cmdline.h"
#include "uffs_fileem.h"

#define PFX NULL
#define MSG(msg,...) uffs_PerrorRaw(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)
#define MSGLN(msg,...) uffs_Perror(UFFS_MSG_NORMAL, msg, ## __VA_ARGS__)

#if CONFIG_USE_STATIC_MEMORY_ALLOCATOR > 0
int main()
{
	MSGLN("Static memory allocator is not supported.");
	return 0;
}
#else

extern struct cli_commandset * get_helper_cmds(void);
extern struct cli_commandset * get_test_cmds(void);
extern void femu_init_uffs_device(uffs_Device *dev);

static int conf_command_line_mode = 0;
static int conf_verbose_mode = 0;

static int conf_exec_script = 0;
static char script_command[256];

#define DEFAULT_EMU_FILENAME "uffsemfile.bin"
const char * conf_emu_filename = DEFAULT_EMU_FILENAME;


/* default basic parameters of the NAND device */
#define PAGES_PER_BLOCK_DEFAULT			32
#define PAGE_DATA_SIZE_DEFAULT			512
#define PAGE_SPARE_SIZE_DEFAULT			16
#define STATUS_BYTE_OFFSET_DEFAULT		5
#define TOTAL_BLOCKS_DEFAULT			128
#define ECC_OPTION_DEFAULT				UFFS_ECC_SOFT
//#define ECC_OPTION_DEFAULT			UFFS_ECC_HW
//#define ECC_OPTION_DEFAULT			UFFS_ECC_HW_AUTO

#define MAX_MOUNT_TABLES		10
#define MAX_MOUNT_POINT_NAME	32

static int conf_pages_per_block = PAGES_PER_BLOCK_DEFAULT;
static int conf_page_data_size = PAGE_DATA_SIZE_DEFAULT;
static int conf_page_spare_size = PAGE_SPARE_SIZE_DEFAULT;
static int conf_status_byte_offset = STATUS_BYTE_OFFSET_DEFAULT;
static int conf_total_blocks = TOTAL_BLOCKS_DEFAULT;
static int conf_ecc_option = ECC_OPTION_DEFAULT;
static int conf_ecc_size = 0; // 0 - Let UFFS choose the size

static const char *g_ecc_option_strings[] = UFFS_ECC_OPTION_STRING;

static struct uffs_MountTableEntrySt conf_mounts[MAX_MOUNT_TABLES] = {{0}};
static uffs_Device conf_devices[MAX_MOUNT_TABLES] = {{0}};
static char mount_point_name[MAX_MOUNT_TABLES][MAX_MOUNT_POINT_NAME] = {{0}};

static void setup_storage(struct uffs_StorageAttrSt *attr)
{
	attr->total_blocks = conf_total_blocks;				/* total blocks */
	attr->page_data_size = conf_page_data_size;			/* page data size */
	attr->spare_size = conf_page_spare_size;			/* page spare size */
	attr->pages_per_block = conf_pages_per_block;		/* pages per block */

	attr->block_status_offs = conf_status_byte_offset;	/* block status offset is 5th byte in spare */
	attr->ecc_opt = conf_ecc_option;					/* ECC option */
	attr->ecc_size = conf_ecc_size;						/* ECC size */
	attr->layout_opt = UFFS_LAYOUT_UFFS;				/* let UFFS handle layout */
}


static void setup_device(uffs_Device *dev)
{
	dev->Init = femu_InitDevice;
	dev->Release = femu_ReleaseDevice;
	dev->attr = femu_GetStorage();
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
	struct uffs_ConfigSt cfg = {
		0,			// bc_caches - default
		0,			// page_buffers - default
		0,			// dirty_pages - default
		0,			// dirty_groups - default
		0,			// reserved_free_blocks - default
	};

	if (bIsFileSystemInited)
		return -4;

	bIsFileSystemInited = 1;

	while (mtbl->dev) {

		memcpy(&mtbl->dev->cfg, &cfg, sizeof(struct uffs_ConfigSt));

#if CONFIG_USE_SYSTEM_MEMORY_ALLOCATOR > 0
		uffs_MemSetupSystemAllocator(&mtbl->dev->mem);
#endif
		setup_device(mtbl->dev);
		uffs_RegisterMountTable(mtbl);
		mtbl++;
	}

	// mount partitions
	for (mtbl = &(conf_mounts[0]); mtbl->mount != NULL; mtbl++) {
		uffs_Mount(mtbl->mount);
	}

	return uffs_InitFileSystemObjects() == U_SUCC ? 0 : -1;
}

static int release_uffs_fs(void)
{
	int ret = 0;
	uffs_MountTable *mtb;

	for (mtb = &(conf_mounts[0]); ret == 0 && mtb->mount != NULL; mtb++) {
		uffs_UnMount(mtb->mount);
	}

	if (ret == 0)
		ret = (uffs_ReleaseFileSystemObjects() == U_SUCC ? 0 : -1);

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
	int i;

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
                else if (sscanf(argv[iarg], "%i", &conf_page_data_size) < 1)
					usage++;
				if (conf_page_data_size <= 0 || conf_page_data_size > UFFS_MAX_PAGE_SIZE) {
					MSGLN("ERROR: Invalid page data size");
					usage++;
				}
            }
            else if (!strcmp(arg, "-s") || !strcmp(arg, "--spare-size")) {
                if (++iarg >= argc) 
					usage++;
                else if (sscanf(argv[iarg], "%i", &conf_page_spare_size) < 1) 
					usage++;
				if (conf_page_spare_size < sizeof(struct uffs_TagStoreSt) + 1 ||
					(conf_page_spare_size % 4) != 0 || conf_page_spare_size > UFFS_MAX_SPARE_SIZE) {
					MSGLN("ERROR: Invalid spare size");
					usage++;
				}
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
				conf_verbose_mode++;
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
					sprintf(script_command, "script %s", argv[iarg]);
					conf_exec_script = 1;
				}
			}
			else if (!strcmp(arg, "-x") || !strcmp(arg, "--ecc-option")) {
				if (++iarg > argc)
					usage++;
				else {
					for (i = 0; i < ARRAY_SIZE(g_ecc_option_strings); i++) {
						if (!strcmp(argv[iarg], g_ecc_option_strings[i])) {
							conf_ecc_option = i;
							break;
						}
					}
					if (i == ARRAY_SIZE(g_ecc_option_strings)) {
						MSGLN("ERROR: Invalid ECC option");
						usage++;
					}
				}
			}
			else if (!strcmp(arg, "-z") || !strcmp(arg, "--ecc-size")) {
                if (++iarg >= argc)
					usage++;
                else if (sscanf(argv[iarg], "%i", &conf_ecc_size) < 1)
					usage++;
				if (conf_ecc_size < 0 || conf_ecc_size > UFFS_MAX_ECC_SIZE) {
					MSGLN("ERROR: Invalid ecc size");
					usage++;
				}
			}
            else {
                MSGLN("Unknown option: %s, try %s --help", arg, argv[0]);
				return -1;
            }
        }
        else {
            MSGLN("Unexpected parameter: %s, try %s --help", arg, argv[0]);
			return -1;
        }
    }
    
    if (usage) {
        MSGLN("Usage: %s [options]", argv[0]);
        MSGLN("  -h  --help                                show usage");
        MSGLN("  -c  --command-line                        command line mode");
        MSGLN("  -v  --verbose                             verbose mode");
        MSGLN("  -f  --file           <file>               uffs image file");
        MSGLN("  -p  --page-size      <n>                  page data size, default=%d", PAGE_DATA_SIZE_DEFAULT);
        MSGLN("  -s  --spare-size     <n>                  page spare size, default=%d", PAGE_SPARE_SIZE_DEFAULT);
		MSGLN("  -o  --status-offset  <n>                  status byte offset, default=%d", STATUS_BYTE_OFFSET_DEFAULT);
        MSGLN("  -b  --block-pages    <n>                  pages per block, default=%d", PAGES_PER_BLOCK_DEFAULT);
        MSGLN("  -t  --total-blocks   <n>                  total blocks");
        MSGLN("  -m  --mount          <mount_point,start,end> , for example: -m /,0,-1");
		MSGLN("  -x  --ecc-option     <none|soft|hw|auto>  ECC option, default=%s", g_ecc_option_strings[ECC_OPTION_DEFAULT]);
		MSGLN("  -z  --ecc-size       <n>                  ECC size, default=0 (auto)");
        MSGLN("  -e  --exec           <file>               execute a script file");
        MSGLN("");

        return -1;
    }

	if (m_idx == 0) {
		// if not given mount information, use default ('/' for whole partition)
		parse_mount_point("/,0,-1", 0);
	}

	return 0;
}


static void print_mount_points(void)
{
	struct uffs_MountTableEntrySt *m;

	m = &(conf_mounts[0]);
	while (m->dev) {
		MSGLN ("Mount point: %s, start: %d, end: %d", m->mount, m->start_block, m->end_block);
		m++;
	}
}

static void print_params(void)
{
	MSGLN("Parameters summary:");
	MSGLN("  uffs image file: %s", conf_emu_filename);
	MSGLN("  page size: %d", conf_page_data_size);
	MSGLN("  page spare size: %d", conf_page_spare_size);
	MSGLN("  pages per block: %d", conf_pages_per_block);
	MSGLN("  total blocks: %d", conf_total_blocks);
	MSGLN("  ecc option: %d (%s)", conf_ecc_option, g_ecc_option_strings[conf_ecc_option]);
	MSGLN("  ecc size: %d%s", conf_ecc_size, conf_ecc_size == 0 ? " (auto)" : "");
	MSGLN("  bad block status offset: %d", conf_status_byte_offset);
	MSGLN("");
}

#ifdef UNIX
#include <execinfo.h>
#include <signal.h>
void crash_handler(int sig)
{
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, 2);
  exit(1);
}
#endif

int main(int argc, char *argv[])
{
	int ret;

#ifdef UNIX
	signal(SIGSEGV, crash_handler);
#endif

	uffs_SetupDebugOutput(); 	// setup debug output as early as possible

	if (parse_options(argc, argv) < 0) {
		return -1;
	}
	
	if (conf_verbose_mode) {
		#if 1
		MSGLN("Internal data structure size:");
		MSGLN("  TreeNode: %d", sizeof(TreeNode));
		MSGLN("  struct BlockListSt: %d", sizeof(struct BlockListSt));
		MSGLN("  struct DirhSt: %d", sizeof(struct DirhSt));
		MSGLN("  struct FilehSt: %d", sizeof(struct FilehSt));
		MSGLN("  struct FdataSt: %d", sizeof(struct FdataSt));
		MSGLN("  struct uffs_TagStoreSt: %d", sizeof(struct uffs_TagStoreSt));
		MSGLN("  uffs_Buf: %d", sizeof(uffs_Buf));
		MSGLN("  struct uffs_BlockInfoSt: %d", sizeof(struct uffs_BlockInfoSt));
		MSGLN("");
		#endif
		print_params();
		print_mount_points();
	}

	// setup file emulator storage with parameters from command line
	setup_storage(femu_GetStorage());

	// setup file emulator private data
	setup_emu_private(femu_GetPrivate());

	ret = init_uffs_fs();
	if (ret != 0) {
		MSGLN ("Init file system fail: %d", ret);
		return -1;
	}

	cli_add_commandset(get_helper_cmds());
	cli_add_commandset(get_test_cmds());
	if (conf_command_line_mode) {
		if (conf_exec_script) {
			cli_interpret(script_command);
		}
		cli_main_entry();
	}
	else {
		if (conf_exec_script) {
			cli_interpret(script_command);
		}
		else {
			cli_main_entry();
		}
	}

	release_uffs_fs();

	return 0;
}
#endif



