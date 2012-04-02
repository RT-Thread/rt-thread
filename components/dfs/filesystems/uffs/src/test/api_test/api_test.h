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
 * \file api_srv.h
 * \brief UFFS API test server definitions 
 * \author Ricky Zheng, created 16 Dec, 2011
 */
#include "uffs/uffs_types.h"
#include "uffs/uffs_fd.h"

#ifndef _UFFS_API_SRV_H_
#define _UFFS_API_SRV_H_

#define SRV_PORT        9018

#define UFFS_API_GET_VER_CMD            0
#define UFFS_API_OPEN_CMD               1
#define UFFS_API_CLOSE_CMD              2
#define UFFS_API_READ_CMD               3
#define UFFS_API_WRITE_CMD              4
#define UFFS_API_FLUSH_CMD              5
#define UFFS_API_SEEK_CMD               6
#define UFFS_API_TELL_CMD               7
#define UFFS_API_EOF_CMD                8
#define UFFS_API_RENAME_CMD             9
#define UFFS_API_REMOVE_CMD             10
#define UFFS_API_FTRUNCATE_CMD          11
#define UFFS_API_MKDIR_CMD              12
#define UFFS_API_RMDIR_CMD              13
#define UFFS_API_STAT_CMD               14
#define UFFS_API_LSTAT_CMD              15
#define UFFS_API_FSTAT_CMD              16
#define UFFS_API_OPEN_DIR_CMD           17
#define UFFS_API_CLOSE_DIR_CMD          18
#define UFFS_API_READ_DIR_CMD           19
#define UFFS_API_REWIND_DIR_CMD         20
#define UFFS_API_GET_ERR_CMD            21
#define UFFS_API_SET_ERR_CMD            22
#define UFFS_API_FORMAT_CMD             23
#define UFFS_API_SPACE_TOTAL_CMD        24
#define UFFS_API_SPACE_FREE_CMD         25
#define UFFS_API_SPACE_USED_CMD         26
#define UFFS_API_FLUSH_ALL_CMD          27

#define UFFS_API_CMD_LAST				27		// last test command id

#define UFFS_API_CMD(header)            ((header)->cmd & 0xFF)
#define UFFS_API_ACK_BIT                (1 << 31)

#define UFFS_API_MAX_PARAMS             8

struct uffs_ApiSrvMsgSt;

struct uffs_ApiSrvHeaderSt {
	u32 cmd;                // command
	u32 data_len;           // data length
	u32 n_params;           // parameter numbers
	u32 param_size[UFFS_API_MAX_PARAMS];    // parameter list
	u32 return_size[UFFS_API_MAX_PARAMS];	// return parameter list
	u16 data_crc;           // data CRC16
	u16 header_crc;         // header CRC16
};

struct uffs_ApiSrvIoSt {
	int (*open)(void *addr);
	int (*read)(int fd, void *buf, int len);
	int (*write)(int fd, const void *buf, int len);
	int (*close)(int fd);
	void *addr;
};

struct uffs_ApiSt {
	int (*uffs_version)(void);
	int (*uffs_open)(const char *name, int oflag, ...);
	int (*uffs_close)(int fd);
	int (*uffs_read)(int fd, void *data, int len);
	int (*uffs_write)(int fd, const void *data, int len);
	int (*uffs_flush)(int fd);
	long (*uffs_seek)(int fd, long offset, int origin);
	long (*uffs_tell)(int fd);
	int (*uffs_eof)(int fd);
	int (*uffs_rename)(const char *old_name, const char *new_name);
	int (*uffs_remove)(const char *name);
	int (*uffs_ftruncate)(int fd, long remain);
	int (*uffs_mkdir)(const char *name, ...);
	int (*uffs_rmdir)(const char *name);
	int (*uffs_stat)(const char *name, struct uffs_stat *buf);
	int (*uffs_lstat)(const char *name, struct uffs_stat *buf);
	int (*uffs_fstat)(int fd, struct uffs_stat *buf);
	uffs_DIR * (*uffs_opendir)(const char *path);
	int (*uffs_closedir)(uffs_DIR *dirp);
	struct uffs_dirent * (*uffs_readdir)(uffs_DIR *dirp);
	void (*uffs_rewinddir)(uffs_DIR *dirp);
	int (*uffs_get_error)(void);
	int (*uffs_set_error)(int err);
	int (*uffs_format)(const char *mount_point);
	long (*uffs_space_total)(const char *mount_point);
	long (*uffs_space_used)(const char *mount_point);
	long (*uffs_space_free)(const char *mount_point);
	void (*uffs_flush_all)(const char *mount_point);
};

struct uffs_ApiSrvMsgSt {
    struct uffs_ApiSrvHeaderSt header;
    u8 *data;
};

int apisrv_setup_io(struct uffs_ApiSrvIoSt *io);
int apisrv_serve(int fd, struct uffs_ApiSt *api);
void apisrv_print_stat(void);
struct uffs_ApiSt * apisrv_get_client(void);

/* from api_test_server_{platform}.c */
int api_server_start(void);

/* from api_test_client_{platform}.c */
int api_client_init(const char *server_addr);

#endif

