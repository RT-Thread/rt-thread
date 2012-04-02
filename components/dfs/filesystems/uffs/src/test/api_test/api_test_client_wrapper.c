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
 * \file api_test_client_wrapper.c
 * \brief API test client wrapper
 * \author Ricky Zheng, created at 20 Dec, 2011
 */

#include "uffs/uffs_fd.h"
#include "api_test.h"

#define W(R, F, T, P) \
	R F T \
	{ \
		return apisrv_get_client()->F P ; \
	}

#define VW(F, T, P) \
	void F T \
	{ \
		apisrv_get_client()->F P ; \
	}

W(int, uffs_version, (), ())
W(int, uffs_open, (const char *name, int oflag, ...), (name, oflag))
W(int, uffs_close, (int fd), (fd))
W(int, uffs_read, (int fd, void *data, int len), (fd, data, len))
W(int, uffs_write, (int fd, const void *data, int len), (fd, data, len))
W(int, uffs_flush, (int fd), (fd))
W(long, uffs_seek, (int fd, long offset, int origin), (fd, offset, origin))
W(long, uffs_tell, (int fd), (fd))
W(int, uffs_eof, (int fd), (fd))
W(int, uffs_rename, (const char *oldname, const char *newname), (oldname, newname))
W(int, uffs_remove, (const char *name), (name))
W(int, uffs_ftruncate, (int fd, long remain), (fd, remain))
W(int, uffs_mkdir, (const char *name, ...), (name))
W(int, uffs_rmdir, (const char *name), (name))
W(int, uffs_stat, (const char *name, struct uffs_stat *buf), (name, buf))
W(int, uffs_lstat, (const char *name, struct uffs_stat *buf), (name, buf))
W(int, uffs_fstat, (int fd, struct uffs_stat *buf), (fd, buf))
W(uffs_DIR *, uffs_opendir, (const char *path), (path))
W(int, uffs_closedir, (uffs_DIR *dirp), (dirp))
W(struct uffs_dirent *, uffs_readdir, (uffs_DIR *dirp), (dirp))
VW(uffs_rewinddir, (uffs_DIR *dirp), (dirp))
W(int, uffs_get_error, (void), ())
W(int, uffs_set_error, (int err), (err))
W(int, uffs_format, (const char *mount), (mount))
W(long, uffs_space_total, (const char *mount), (mount))
W(long, uffs_space_used, (const char *mount), (mount))
W(long, uffs_space_free, (const char *mount), (mount))
VW(uffs_flush_all, (const char *mount), (mount))
