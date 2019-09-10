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
 * \file uffs_fd.c
 * \brief POSIX like, hight level file operations
 * \author Ricky Zheng, created 8th Jun, 2005
 */

#include <string.h>
#include "uffs_config.h"
#include "uffs/uffs_fs.h"
#include "uffs/uffs_fd.h"
#include "uffs/uffs_utils.h"
#include "uffs/uffs_version.h"
#include "uffs/uffs_mtb.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_find.h"

#define PFX "fd  : "

/**
 * \brief POSIX DIR
 */
struct uffs_dirSt {
    struct uffs_ObjectSt   *obj;		/* dir object */
    struct uffs_FindInfoSt f;			/* find info */
    struct uffs_ObjectInfoSt info;		/* object info */
    struct uffs_dirent dirent;			/* dir entry */
};


#define FD_OFFSET		3	//!< just make file handler more like POSIX (0, 1, 2 for stdin/stdout/stderr)

#define OBJ2FD(obj)	\
	( \
		( \
			uffs_PoolGetIndex(uffs_GetObjectPool(), obj) | \
			(_fd_signature << FD_SIGNATURE_SHIFT) \
		) \
		+ FD_OFFSET \
	)

/**
 * check #fd signature, convert #fd to #obj
 * if success, hold global file system lock, otherwise return with #ret
 */
#define CHK_OBJ_LOCK(fd, obj, ret)	\
	do { \
		uffs_GlobalFsLockLock(); \
		fd -= FD_OFFSET; \
		if ( (fd >> FD_SIGNATURE_SHIFT) != _fd_signature ) { \
			uffs_set_error(-UEBADF); \
			uffs_Perror(UFFS_MSG_NOISY, "invalid fd: %d (sig: %d, expect: %d)", \
					fd + FD_OFFSET, fd >> FD_SIGNATURE_SHIFT, _fd_signature); \
			uffs_GlobalFsLockUnlock(); \
			return (ret); \
		} \
		fd = fd & ((1 << FD_SIGNATURE_SHIFT) - 1); \
		obj = (uffs_Object *)uffs_PoolGetBufByIndex(uffs_GetObjectPool(), fd); \
		if ((obj) == NULL || \
				uffs_PoolVerify(uffs_GetObjectPool(), (obj)) == U_FALSE || \
				uffs_PoolCheckFreeList(uffs_GetObjectPool(), (obj)) == U_TRUE) { \
			uffs_set_error(-UEBADF); \
			uffs_Perror(UFFS_MSG_NOISY, "invalid obj"); \
			uffs_GlobalFsLockUnlock(); \
			return (ret); \
		} \
	} while(0)

/**
 * check #dirp signature,
 * if success, hold global file system lock,
 * otherwise return with #ret
 */
#define CHK_DIR_LOCK(dirp, ret)	\
	do { \
		uffs_GlobalFsLockLock(); \
		if ((dirp) == NULL || \
				uffs_PoolVerify(&_dir_pool, (dirp)) == U_FALSE || \
				uffs_PoolCheckFreeList(&_dir_pool, (dirp)) == U_TRUE) { \
			uffs_set_error(-UEBADF); \
			uffs_Perror(UFFS_MSG_NOISY, "invalid dirp"); \
			uffs_GlobalFsLockUnlock(); \
			return (ret); \
		} \
	} while(0)

/**
 * check #dirp signature,
 * if success, hold global file system lock,
 * otherwise return void
 */
#define CHK_DIR_VOID_LOCK(dirp)	\
	do { \
		uffs_GlobalFsLockLock(); \
		if ((dirp) == NULL || \
				uffs_PoolVerify(&_dir_pool, (dirp)) == U_FALSE || \
				uffs_PoolCheckFreeList(&_dir_pool, (dirp)) == U_TRUE) { \
			uffs_set_error(-UEBADF); \
			uffs_Perror(UFFS_MSG_NOISY, "invalid dirp"); \
			uffs_GlobalFsLockUnlock(); \
			return; \
		} \
	} while(0)


static int _dir_pool_data[sizeof(uffs_DIR) * MAX_DIR_HANDLE / sizeof(int)];
static uffs_Pool _dir_pool;
static int _uffs_errno = 0;


//
// What is fd signature ? fd signature is for detecting file system get formated by other party.
//   A thread open a file, read()...sleep()...write()...sleep()...
//   B thread format UFFS partition, increase fd signature.
//   A thread ...sleep()...read() --> Opps, fd signature changed ! read() return error(expected).
//
#define MAX_FD_SIGNATURE_ROUND  (100)
static int _fd_signature = 0;

//
// only get called when formating UFFS partition
//
void uffs_FdSignatureIncrease(void)
{
	if (_fd_signature++ > MAX_FD_SIGNATURE_ROUND)
		_fd_signature = 0;
}

/**
 * initialise uffs_DIR buffers, called by UFFS internal
 */
URET uffs_DirEntryBufInit(void)
{
	return uffs_PoolInit(&_dir_pool, _dir_pool_data,
							sizeof(_dir_pool_data),
							sizeof(uffs_DIR), MAX_DIR_HANDLE);
}

/**
 * Release uffs_DIR buffers, called by UFFS internal
 */
URET uffs_DirEntryBufRelease(void)
{
	return uffs_PoolRelease(&_dir_pool);
}

/**
 * Put all dir entry buf match dev
 */
int uffs_DirEntryBufPutAll(uffs_Device *dev)
{
	int count = 0;
	uffs_DIR *dirp = NULL;

	do {
		dirp = (uffs_DIR *) uffs_PoolFindNextAllocated(&_dir_pool, dirp);
		if (dirp && dirp->obj && dirp->obj->dev &&
				dirp->obj->dev->dev_num == dev->dev_num) {
			uffs_PoolPut(&_dir_pool, dirp);
			count++;
		}
	} while (dirp);

	return count;
}


uffs_Pool * uffs_DirEntryBufGetPool(void)
{
	return &_dir_pool;
}

static uffs_DIR * GetDirEntry(void)
{
	uffs_DIR *dirp = (uffs_DIR *) uffs_PoolGet(&_dir_pool);

	if (dirp)
		memset(dirp, 0, sizeof(uffs_DIR));

	return dirp;
}

static void PutDirEntry(uffs_DIR *p)
{
	uffs_PoolPut(&_dir_pool, p);
}


/** get global errno
 */
int uffs_get_error(void)
{
	return _uffs_errno;
}

/** set global errno
 */
int uffs_set_error(int err)
{
	return (_uffs_errno = err);
}

/* POSIX compliant file system APIs */

int uffs_open(const char *name, int oflag, ...)
{
	uffs_Object *obj;
	int ret = 0;

	uffs_GlobalFsLockLock();

	obj = uffs_GetObject();
	if (obj == NULL) {
		uffs_set_error(-UEMFILE);
		ret = -1;
	}
	else {
		if (uffs_OpenObject(obj, name, oflag) == U_FAIL) {
			uffs_set_error(-uffs_GetObjectErr(obj));
			uffs_PutObject(obj);
			ret = -1;
		}
		else {
			ret = OBJ2FD(obj);
		}
	}

	uffs_GlobalFsLockUnlock();

	return ret;
}

int uffs_close(int fd)
{
	int ret = 0;
	uffs_Object *obj;

	CHK_OBJ_LOCK(fd, obj, -1);

	uffs_ClearObjectErr(obj);
	if (uffs_CloseObject(obj) == U_FAIL) {
		uffs_set_error(-uffs_GetObjectErr(obj));
		ret = -1;
	}
	else {
		uffs_PutObject(obj);
		ret = 0;
	}

	uffs_GlobalFsLockUnlock();

	return ret;
}

int uffs_read(int fd, void *data, int len)
{
	int ret;
	uffs_Object *obj;

	CHK_OBJ_LOCK(fd, obj, -1);
	uffs_ClearObjectErr(obj);
	ret = uffs_ReadObject(obj, data, len);
	uffs_set_error(-uffs_GetObjectErr(obj));

	uffs_GlobalFsLockUnlock();

	return ret;
}

int uffs_write(int fd, const void *data, int len)
{
	int ret;
	uffs_Object *obj;

	CHK_OBJ_LOCK(fd, obj, -1);
	uffs_ClearObjectErr(obj);
	ret = uffs_WriteObject(obj, data, len);
	uffs_set_error(-uffs_GetObjectErr(obj));

	uffs_GlobalFsLockUnlock();

	return ret;
}

long uffs_seek(int fd, long offset, int origin)
{
	int ret;
	uffs_Object *obj;

	CHK_OBJ_LOCK(fd, obj, -1);
	uffs_ClearObjectErr(obj);
	ret = uffs_SeekObject(obj, offset, origin);
	uffs_set_error(-uffs_GetObjectErr(obj));
	
	uffs_GlobalFsLockUnlock();

	return ret;
}

long uffs_tell(int fd)
{
	long ret;
	uffs_Object *obj;

	CHK_OBJ_LOCK(fd, obj, -1);
	uffs_ClearObjectErr(obj);
	ret = (long) uffs_GetCurOffset(obj);
	uffs_set_error(-uffs_GetObjectErr(obj));
	
	uffs_GlobalFsLockUnlock();

	return ret;
}

int uffs_eof(int fd)
{
	int ret;
	uffs_Object *obj;

	CHK_OBJ_LOCK(fd, obj, -1);
	uffs_ClearObjectErr(obj);
	ret = uffs_EndOfFile(obj);
	uffs_set_error(-uffs_GetObjectErr(obj));
	
	uffs_GlobalFsLockUnlock();

	return ret;
}

int uffs_flush(int fd)
{
	int ret;
	uffs_Object *obj;

	CHK_OBJ_LOCK(fd, obj, -1);
	uffs_ClearObjectErr(obj);
	ret = (uffs_FlushObject(obj) == U_SUCC) ? 0 : -1;
	uffs_set_error(-uffs_GetObjectErr(obj));
	
	uffs_GlobalFsLockUnlock();

	return ret;
}

int uffs_rename(const char *old_name, const char *new_name)
{
	int err = 0;
	int ret = 0;

	uffs_GlobalFsLockLock();
	ret = (uffs_RenameObject(old_name, new_name, &err) == U_SUCC) ? 0 : -1;
	uffs_set_error(-err);
	uffs_GlobalFsLockUnlock();

	return ret;
}

int uffs_remove(const char *name)
{
	int err = 0;
	int ret = 0;
	struct uffs_stat st;

	if (uffs_stat(name, &st) < 0) {
		err = UENOENT;
		ret = -1;
	}
	else if (st.st_mode & US_IFDIR) {
		err = UEISDIR;
		ret = -1;
	}
	else {
		uffs_GlobalFsLockLock();
		if (uffs_DeleteObject(name, &err) == U_SUCC) {
			ret = 0;
		}
		else {
			ret = -1;
		}
		uffs_GlobalFsLockUnlock();
	}

	uffs_set_error(-err);
	return ret;
}

int uffs_ftruncate(int fd, long remain)
{
	int ret;
	uffs_Object *obj;

	CHK_OBJ_LOCK(fd, obj, -1);
	uffs_ClearObjectErr(obj);
	ret = (uffs_TruncateObject(obj, remain) == U_SUCC) ? 0 : -1;
	uffs_set_error(-uffs_GetObjectErr(obj));
	uffs_GlobalFsLockUnlock();
	
	return ret;
}

static int do_stat(uffs_Object *obj, struct uffs_stat *buf)
{
	uffs_ObjectInfo info;
	int ret = 0;
	int err = 0;

	if (uffs_GetObjectInfo(obj, &info, &err) == U_FAIL) {
		ret = -1;
	}
	else {
		buf->st_dev = obj->dev->dev_num;
		buf->st_ino = info.serial;
		buf->st_nlink = 0;
		buf->st_uid = 0;
		buf->st_gid = 0;
		buf->st_rdev = 0;
		buf->st_size = info.len;
		buf->st_blksize = obj->dev->com.pg_data_size;
		buf->st_blocks = 0;
		buf->st_atime = info.info.last_modify;
		buf->st_mtime = info.info.last_modify;
		buf->st_ctime = info.info.create_time;
		buf->st_mode = (info.info.attr & FILE_ATTR_DIR ? US_IFDIR : US_IFREG);
		if (info.info.attr & FILE_ATTR_WRITE)
			buf->st_mode |= US_IRWXU;
	}

	uffs_set_error(-err);
	return ret;
}

int uffs_stat(const char *name, struct uffs_stat *buf)
{
	uffs_Object *obj;
	int ret = 0;
	int err = 0;
	URET result;

	uffs_GlobalFsLockLock();

	obj = uffs_GetObject();
	if (obj) {
		if (*name && name[strlen(name) - 1] == '/') {
			result = uffs_OpenObject(obj, name, UO_RDONLY | UO_DIR);
		}
		else {
			if ((result = uffs_OpenObject(obj, name, UO_RDONLY)) != U_SUCC)	// try file
				result = uffs_OpenObject(obj, name, UO_RDONLY | UO_DIR);	// then try dir
		}
		if (result == U_SUCC) {
			ret = do_stat(obj, buf);
			uffs_CloseObject(obj);
		}
		else {
			err = uffs_GetObjectErr(obj);
			ret = -1;
		}
		uffs_PutObject(obj);
	}
	else {
		err = UENOMEM;
		ret = -1;
	}

	uffs_set_error(-err);
	uffs_GlobalFsLockUnlock();

	return ret;
}

int uffs_lstat(const char *name, struct uffs_stat *buf)
{
	return uffs_stat(name, buf);
}

int uffs_fstat(int fd, struct uffs_stat *buf)
{
	int ret;
	uffs_Object *obj;

	CHK_OBJ_LOCK(fd, obj, -1);

	ret = do_stat(obj, buf);
	uffs_GlobalFsLockUnlock();

	return ret;
}

int uffs_closedir(uffs_DIR *dirp)
{
	CHK_DIR_LOCK(dirp, -1);

	uffs_FindObjectClose(&dirp->f);
	if (dirp->obj) {
		uffs_CloseObject(dirp->obj);
		uffs_PutObject(dirp->obj);
	}
	PutDirEntry(dirp);
	uffs_GlobalFsLockUnlock();

	return 0;
}

uffs_DIR * uffs_opendir(const char *path)
{
	int err = 0;
	uffs_DIR *ret = NULL;
	uffs_DIR *dirp;

	uffs_GlobalFsLockLock();

	dirp = GetDirEntry();

	if (dirp) {
		dirp->obj = uffs_GetObject();
		if (dirp->obj) {
			if (uffs_OpenObject(dirp->obj, path, UO_RDONLY | UO_DIR) == U_SUCC) {
				if (uffs_FindObjectOpen(&dirp->f, dirp->obj) == U_SUCC) {
					ret = dirp;
					goto ext;
				}
				else {
					uffs_CloseObject(dirp->obj);
				}
			}
			else {
				err = uffs_GetObjectErr(dirp->obj);
			}
			uffs_PutObject(dirp->obj);
			dirp->obj = NULL;
		}
		else {
			err = UEMFILE;
		}
		PutDirEntry(dirp);
	}
	else {
		err = UEMFILE;
	}
ext:
	uffs_set_error(-err);
	uffs_GlobalFsLockUnlock();

	return ret;
}

struct uffs_dirent * uffs_readdir(uffs_DIR *dirp)
{
	struct uffs_dirent *ent = NULL;

	CHK_DIR_LOCK(dirp, NULL);

	if (uffs_FindObjectNext(&dirp->info, &dirp->f) == U_SUCC) {
		ent = &dirp->dirent;
		ent->d_ino = dirp->info.serial;
		ent->d_namelen = dirp->info.info.name_len < (sizeof(ent->d_name) - 1) ? dirp->info.info.name_len : (sizeof(ent->d_name) - 1);
		memcpy(ent->d_name, dirp->info.info.name, ent->d_namelen);
		ent->d_name[ent->d_namelen] = '\0';
		ent->d_off = dirp->f.pos;
		ent->d_reclen = sizeof(struct uffs_dirent);
		ent->d_type = dirp->info.info.attr;
	}
	uffs_GlobalFsLockUnlock();

	return ent;
}

void uffs_rewinddir(uffs_DIR *dirp)
{
	CHK_DIR_VOID_LOCK(dirp);

	uffs_FindObjectRewind(&dirp->f);

	uffs_GlobalFsLockUnlock();
}


int uffs_mkdir(const char *name, ...)
{
	uffs_Object *obj;
	int ret = 0;
	int err = 0;

	uffs_GlobalFsLockLock();

	obj = uffs_GetObject();
	if (obj) {
		if (uffs_CreateObject(obj, name, UO_CREATE|UO_DIR) != U_SUCC) {
			err = obj->err;
			ret = -1;
		}
		else {
			uffs_CloseObject(obj);
			ret = 0;
		}
		uffs_PutObject(obj);
	}
	else {
		err = UEMFILE;
		ret = -1;
	}

	uffs_set_error(-err);
	uffs_GlobalFsLockUnlock();

	return ret;
}

int uffs_rmdir(const char *name)
{
	int err = 0;
	int ret = 0;
	struct uffs_stat st;

	if (uffs_stat(name, &st) < 0) {
		err = UENOENT;
		ret = -1;
	}
	else if ((st.st_mode & US_IFDIR) == 0) {
		err = UENOTDIR;
		ret = -1;
	}
	else {
		uffs_GlobalFsLockLock();
		if (uffs_DeleteObject(name, &err) == U_SUCC) {
			ret = 0;
		}
		else {
			ret = -1;
		}
		uffs_GlobalFsLockUnlock();
	}
	uffs_set_error(-err);
	return ret;
}

int uffs_version(void)
{
	return uffs_GetVersion();
}

int uffs_format(const char *mount_point)
{
	uffs_Device *dev = NULL;
	URET ret = U_FAIL;

	dev = uffs_GetDeviceFromMountPoint(mount_point);
	if (dev) {
		uffs_GlobalFsLockLock();
		ret = uffs_FormatDevice(dev, U_TRUE);
		uffs_GlobalFsLockUnlock();
	}

	return ret == U_SUCC ? 0 : -1;
}

long uffs_space_total(const char *mount_point)
{
	uffs_Device *dev = NULL;
	long ret = -1L;

	dev = uffs_GetDeviceFromMountPoint(mount_point);
	if (dev) {
		uffs_GlobalFsLockLock();
		ret = (long) uffs_GetDeviceTotal(dev);
		uffs_GlobalFsLockUnlock();
	}

	return ret;
}

long uffs_space_used(const char *mount_point)
{
	uffs_Device *dev = NULL;
	long ret = -1L;

	dev = uffs_GetDeviceFromMountPoint(mount_point);
	if (dev) {
		uffs_GlobalFsLockLock();
		ret = (long) uffs_GetDeviceUsed(dev);
		uffs_GlobalFsLockUnlock();
	}

	return ret;
}

long uffs_space_free(const char *mount_point)
{
	uffs_Device *dev = NULL;
	long ret = -1L;

	dev = uffs_GetDeviceFromMountPoint(mount_point);
	if (dev) {
		uffs_GlobalFsLockLock();
		ret = (long) uffs_GetDeviceFree(dev);
		uffs_GlobalFsLockUnlock();
	}

	return ret;
}


void uffs_flush_all(const char *mount_point)
{
	uffs_Device *dev = NULL;

	dev = uffs_GetDeviceFromMountPoint(mount_point);
	if (dev) {
		uffs_GlobalFsLockLock();
		uffs_BufFlushAll(dev);
		uffs_PutDevice(dev);
		uffs_GlobalFsLockUnlock();
	}
}

