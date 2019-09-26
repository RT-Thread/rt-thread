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
 * \file uffs_fs.c
 * \brief basic file operations
 * \author Ricky Zheng, created 12th May, 2005
 */
#include "uffs_config.h"
#include "uffs/uffs_fs.h"
#include "uffs/uffs_pool.h"
#include "uffs/uffs_ecc.h"
#include "uffs/uffs_badblock.h"
#include "uffs/uffs_os.h"
#include "uffs/uffs_mtb.h"
#include "uffs/uffs_utils.h"
#include <string.h> 
#include <stdio.h>

#define PFX "fs  : "

#define GET_OBJ_NODE_SERIAL(obj) \
	( \
		(obj)->type == UFFS_TYPE_DIR ? \
			(obj)->node->u.dir.serial :	(obj)->node->u.file.serial \
	 )

#define GET_OBJ_NODE_FATHER(obj) \
	( \
		(obj)->type == UFFS_TYPE_DIR ? \
			(obj)->node->u.dir.parent :	(obj)->node->u.file.parent \
	 )

#define GET_SERIAL_FROM_OBJECT(obj) \
			((obj)->node ? GET_OBJ_NODE_SERIAL(obj) : obj->serial)

#define GET_FATHER_FROM_OBJECT(obj) \
			((obj)->node ? GET_OBJ_NODE_FATHER(obj) : obj->parent)


#define GET_BLOCK_FROM_NODE(obj) \
	( \
		(obj)->type == UFFS_TYPE_DIR ? \
			(obj)->node->u.dir.block : (obj)->node->u.file.block \
	 )

typedef enum {
	eDRY_RUN = 0,
	eREAL_RUN,
} RunOptionE;


static void do_ReleaseObjectResource(uffs_Object *obj);
static URET do_TruncateObject(uffs_Object *obj, u32 remain, RunOptionE run_opt);


static int _object_data[(sizeof(struct uffs_ObjectSt) * MAX_OBJECT_HANDLE) / sizeof(int)];

static uffs_Pool _object_pool;


uffs_Pool * uffs_GetObjectPool(void)
{
	return &_object_pool;
}

/**
 * initialise object buffers, called by UFFS internal
 */
URET uffs_InitObjectBuf(void)
{
	return uffs_PoolInit(&_object_pool, _object_data, sizeof(_object_data),
			sizeof(uffs_Object), MAX_OBJECT_HANDLE);
}

/**
 * Release object buffers, called by UFFS internal
 */
URET uffs_ReleaseObjectBuf(void)
{
	return uffs_PoolRelease(&_object_pool);
}

/**
 * Get free object handlers
 */
int uffs_GetFreeObjectHandlers(void)
{
	int count = 0;

	uffs_GlobalFsLockLock();
	count = uffs_PoolGetFreeCount(&_object_pool);
	uffs_GlobalFsLockUnlock();

	return count;
}

/**
 * Put all object which match dev
 */
int uffs_PutAllObjectBuf(uffs_Device *dev)
{
	int count = 0;
	uffs_Object * obj = NULL;

	do {
		obj = (uffs_Object *) uffs_PoolFindNextAllocated(&_object_pool, (void *)obj);
		if (obj && obj->dev && obj->dev->dev_num == dev->dev_num) {
			uffs_PutObject(obj);
			count++;
		}
	} while (obj);

	return count;
}

/**
 * alloc a new object structure
 * \return the new object
 */
uffs_Object * uffs_GetObject(void)
{
	uffs_Object * obj;

	obj = (uffs_Object *) uffs_PoolGet(&_object_pool);
	if (obj) {
		memset(obj, 0, sizeof(uffs_Object));
		obj->attr_loaded = U_FALSE;
		obj->open_succ = U_FALSE;
	}

	return obj;
}

/**
 * re-initialize an object.
 *
 * \return U_SUCC or U_FAIL if the object is openned.
 */
URET uffs_ReInitObject(uffs_Object *obj)
{
	if (obj == NULL)
		return U_FAIL;

	if (obj->open_succ == U_TRUE)
		return U_FAIL;	// can't re-init an openned object.

	memset(obj, 0, sizeof(uffs_Object));
	obj->attr_loaded = U_FALSE;
	obj->open_succ = U_FALSE;

	return U_SUCC;	
}

/**
 * put the object struct back to system
 */
void uffs_PutObject(uffs_Object *obj)
{
	if (obj)
		uffs_PoolPut(&_object_pool, obj);
}

/**
 * \return the internal index num of object
 */
int uffs_GetObjectIndex(uffs_Object *obj)
{
	return uffs_PoolGetIndex(&_object_pool, obj);
}

/**
 * \return the object by the internal index
 */
uffs_Object * uffs_GetObjectByIndex(int idx)
{
	return (uffs_Object *) uffs_PoolGetBufByIndex(&_object_pool, idx);
}

#ifdef CONFIG_PER_DEVICE_LOCK
static void uffs_ObjectDevLock(uffs_Object *obj)
{
	if (obj) {
		if (obj->dev) {
			uffs_DeviceLock(obj->dev);
			obj->dev_lock_count++;
		}
	}
}

static void uffs_ObjectDevUnLock(uffs_Object *obj)
{
	if (obj) {
		if (obj->dev) {
			obj->dev_lock_count--;
			uffs_DeviceUnLock(obj->dev);
		}
	}
} 
#else
#define uffs_ObjectDevLock(obj) do { } while (0)
#define uffs_ObjectDevUnLock(obj) do { } while (0)

#endif



/**
 * create a new object and open it if success
 */
URET uffs_CreateObject(uffs_Object *obj, const char *fullname, int oflag)
{
	URET ret = U_FAIL;

	oflag |= UO_CREATE;

	if (uffs_ParseObject(obj, fullname) == U_SUCC)
		uffs_CreateObjectEx(obj, obj->dev, obj->parent,
								obj->name, obj->name_len, oflag);

	if (obj->err == UENOERR) {
		ret = U_SUCC;
	}
	else {
		if (obj->dev) {
			uffs_PutDevice(obj->dev);
			obj->dev = NULL;
		}
		ret = U_FAIL;
	}

	return ret;
}



/**
 * return the dir length from a path.
 * for example, path = "abc/def/xyz", return 8 ("abc/def/")
 */
static int GetDirLengthFromPath(const char *path, int path_len)
{
	const char *p = path;

	if (path_len > 0) {
		if (path[path_len - 1] == '/')
			path_len--;		// skip the last '/'

		p = path + path_len - 1;
		while (p > path && *p != '/')
			p--; 
	}

	return p - path;
}

/**
 * Create an object under the given dir.
 *
 * \param[in|out] obj to be created, obj is returned from uffs_GetObject()
 * \param[in] dev uffs device
 * \param[in] dir object parent dir serial NO.
 * \param[in] name point to the object name
 * \param[in] name_len object name length
 * \param[in] oflag open flag. UO_DIR should be passed for an dir object.
 *
 * \return U_SUCC or U_FAIL (error code in obj->err).
 */
URET uffs_CreateObjectEx(uffs_Object *obj, uffs_Device *dev, 
						   int dir, const char *name, int name_len, int oflag)
{
	uffs_Buf *buf = NULL;
	uffs_FileInfo fi;
	TreeNode *node;

	obj->dev = dev;
	obj->parent = dir;
	obj->type = (oflag & UO_DIR ? UFFS_TYPE_DIR : UFFS_TYPE_FILE);
	obj->name = name;
	obj->name_len = name_len;

	if (obj->type == UFFS_TYPE_DIR) {
		if (name[obj->name_len - 1] == '/')		// get rid of ending '/' for dir
			obj->name_len--;
	}
	else {
		if (name[obj->name_len - 1] == '/') {	// file name can't end with '/'
			obj->err = UENOENT;
			goto ext;
		}
	}

	if (obj->name_len == 0) {	// empty name ?
		obj->err = UENOENT;
		goto ext;
	}

	obj->sum = uffs_MakeSum16(obj->name, obj->name_len);

	uffs_ObjectDevLock(obj);

	if (obj->type == UFFS_TYPE_DIR) {
		//find out whether have file with the same name
		node = uffs_TreeFindFileNodeByName(obj->dev, obj->name,
											obj->name_len, obj->sum,
											obj->parent);
		if (node != NULL) {
			obj->err = UEEXIST;	// we can't create a dir has the
								// same name with exist file.
			goto ext_1;
		}
		obj->node = uffs_TreeFindDirNodeByName(obj->dev, obj->name,
												obj->name_len, obj->sum,
												obj->parent);
		if (obj->node != NULL) {
			obj->err = UEEXIST; // we can't create a dir already exist.
			goto ext_1;
		}
	}
	else {
		//find out whether have dir with the same name
		node = uffs_TreeFindDirNodeByName(obj->dev, obj->name,
											obj->name_len, obj->sum,
											obj->parent);
		if (node != NULL) {
			obj->err = UEEXIST;
			goto ext_1;
		}
		obj->node = uffs_TreeFindFileNodeByName(obj->dev, obj->name,
												obj->name_len, obj->sum,
												obj->parent);
		if (obj->node) {
			/* file already exist, truncate it to zero length */
			obj->serial = GET_OBJ_NODE_SERIAL(obj);
			obj->open_succ = U_TRUE; // set open_succ to U_TRUE before
									 // call do_TruncateObject()
			if (do_TruncateObject(obj, 0, eDRY_RUN) == U_SUCC)
				do_TruncateObject(obj, 0, eREAL_RUN);
			goto ext_1;
		}
	}

	/* dir|file does not exist, create a new one */
	obj->serial = uffs_FindFreeFsnSerial(obj->dev);
	if (obj->serial == INVALID_UFFS_SERIAL) {
		uffs_Perror(UFFS_MSG_SERIOUS, "No free serial num!");
		obj->err = UENOMEM;
		goto ext_1;
	}

	if (obj->dev->tree.erased_count < obj->dev->cfg.reserved_free_blocks) {
		uffs_Perror(UFFS_MSG_NOISY,
					"insufficient block in create obj");
		obj->err = UENOMEM;
		goto ext_1;
	}

	buf = uffs_BufNew(obj->dev, obj->type, obj->parent, obj->serial, 0);
	if (buf == NULL) {
		uffs_Perror(UFFS_MSG_SERIOUS,
						"Can't create new buffer when create obj!");
		goto ext_1;
	}

	memset(&fi, 0, sizeof(uffs_FileInfo));
	fi.name_len = obj->name_len < sizeof(fi.name) ? obj->name_len : sizeof(fi.name) - 1;
	memcpy(fi.name, obj->name, fi.name_len);
	fi.name[fi.name_len] = '\0';

	fi.access = 0;
	fi.attr |= FILE_ATTR_WRITE;

	if (obj->type == UFFS_TYPE_DIR)
		fi.attr |= FILE_ATTR_DIR;

	fi.create_time = fi.last_modify = uffs_GetCurDateTime();

	uffs_BufWrite(obj->dev, buf, &fi, 0, sizeof(uffs_FileInfo));
	uffs_BufPut(obj->dev, buf);

	// flush buffer immediately,
	// so that the new node will be inserted into the tree
	uffs_BufFlushGroup(obj->dev, obj->parent, obj->serial);

	// update obj->node: after buf flushed,
	// the NEW node can be found in the tree
	if (obj->type == UFFS_TYPE_DIR)
		obj->node = uffs_TreeFindDirNode(obj->dev, obj->serial);
	else
		obj->node = uffs_TreeFindFileNode(obj->dev, obj->serial);

	if (obj->node == NULL) {
		uffs_Perror(UFFS_MSG_NOISY, "Can't find the node in the tree ?");
		obj->err = UEIOERR;
		goto ext_1;
	}

	if (obj->type == UFFS_TYPE_FILE)
		obj->node->u.file.len = 0;	//init the length to 0

	if (HAVE_BADBLOCK(obj->dev))
		uffs_BadBlockRecover(obj->dev);

	obj->open_succ = U_TRUE;

ext_1:
	uffs_ObjectDevUnLock(obj);
ext:
	return (obj->err == UENOERR ? U_SUCC : U_FAIL);
}

/**
 * Open object under the given dir.
 *
 * \param[in|out] obj to be open, obj is returned from uffs_GetObject()
 * \param[in] dev uffs device
 * \param[in] dir object parent dir serial NO.
 * \param[in] name point to the object name
 * \param[in] name_len object name length
 * \param[in] oflag open flag. UO_DIR should be passed for an dir object.
 *
 * \return U_SUCC or U_FAIL (error code in obj->err).
 */
URET uffs_OpenObjectEx(uffs_Object *obj, uffs_Device *dev, 
					   int dir, const char *name, int name_len, int oflag)
{

	obj->err = UENOERR;
	obj->open_succ = U_FALSE;

	if (dev == NULL) {
		obj->err = UEINVAL;
		goto ext;
	}

	if ((oflag & (UO_WRONLY | UO_RDWR)) == (UO_WRONLY | UO_RDWR)) {
		/* UO_WRONLY and UO_RDWR can't appear together */
		uffs_Perror(UFFS_MSG_NOISY,
					"UO_WRONLY and UO_RDWR can't appear together");
		obj->err = UEINVAL;
		goto ext;
	}

	obj->oflag = oflag;
	obj->parent = dir;
	obj->type = (oflag & UO_DIR ? UFFS_TYPE_DIR : UFFS_TYPE_FILE);
	obj->pos = 0;
	obj->dev = dev;
	obj->name = name;
	obj->name_len = name_len;

	// adjust the name length
	if (obj->type == UFFS_TYPE_DIR) {
		if (obj->name_len > 0 && name[obj->name_len - 1] == '/')
			obj->name_len--;	// truncate the ending '/' for dir
	}

	obj->sum = (obj->name_len > 0 ? uffs_MakeSum16(name, obj->name_len) : 0);
	obj->head_pages = obj->dev->attr->pages_per_block - 1;

	if (obj->type == UFFS_TYPE_DIR) {
		if (obj->name_len == 0) {
			if (dir != PARENT_OF_ROOT) {
				uffs_Perror(UFFS_MSG_SERIOUS, "Bad parent for root dir!");
				obj->err = UEINVAL;
			}
			else {
				obj->serial = ROOT_DIR_SERIAL;
			}
			goto ext;
		}
	}
	else {
		if (obj->name_len == 0 || name[obj->name_len - 1] == '/') {
			uffs_Perror(UFFS_MSG_SERIOUS, "Bad file name.");
			obj->err = UEINVAL;
		}
	}


	uffs_ObjectDevLock(obj);

	if (obj->type == UFFS_TYPE_DIR) {
		obj->node = uffs_TreeFindDirNodeByName(obj->dev, obj->name,
												obj->name_len, obj->sum,
												obj->parent);
	}
	else {
		obj->node = uffs_TreeFindFileNodeByName(obj->dev, obj->name,
												obj->name_len, obj->sum,
												obj->parent);
	}

	if (obj->node == NULL) {			// dir or file not exist
		if (obj->oflag & UO_CREATE) {	// expect to create a new one
			uffs_ObjectDevUnLock(obj);
			if (obj->name == NULL || obj->name_len == 0)
				obj->err = UEEXIST;
			else
				uffs_CreateObjectEx(obj, dev, dir, obj->name, obj->name_len, oflag);
			goto ext;
		}
		else {
			obj->err = UENOENT;
			goto ext_1;
		}
	}

	if ((obj->oflag & (UO_CREATE | UO_EXCL)) == (UO_CREATE | UO_EXCL)){
		obj->err = UEEXIST;
		goto ext_1;
	}

	obj->serial = GET_OBJ_NODE_SERIAL(obj);
	obj->open_succ = U_TRUE;

	if (obj->oflag & UO_TRUNC)
		if (do_TruncateObject(obj, 0, eDRY_RUN) == U_SUCC) {
			//NOTE: obj->err will be set in do_TruncateObject() if failed.
			do_TruncateObject(obj, 0, eREAL_RUN);
		}

ext_1:
	uffs_ObjectDevUnLock(obj);
ext:
	obj->open_succ = (obj->err == UENOERR ? U_TRUE : U_FALSE);

	return (obj->err == UENOERR ? U_SUCC : U_FAIL);
}


/**
 * Parse the full path name, initialize obj.
 *
 * \param[out] obj object to be initialize.
 * \param[in] name full path name.
 *
 * \return U_SUCC if the name is parsed correctly,
 *			 U_FAIL if failed, and obj->err is set.
 *
 *	\note the following fields in obj will be initialized:
 *			obj->dev
 *			obj->parent
 *			obj->name
 *			obj->name_len
 */
URET uffs_ParseObject(uffs_Object *obj, const char *name)
{
	int len, m_len, d_len;
	uffs_Device *dev;
	const char *start, *p, *dname;
	u16 dir;
	TreeNode *node;
	u16 sum;

	if (uffs_ReInitObject(obj) == U_FAIL)
		return U_FAIL;

	len = strlen(name);
	m_len = uffs_GetMatchedMountPointSize(name);
	dev = uffs_GetDeviceFromMountPointEx(name, m_len);

	if (dev) {
		start = name + m_len;
		d_len = GetDirLengthFromPath(start, len - m_len);
		p = start;
		obj->dev = dev;
		if (m_len == len) {
			obj->parent = PARENT_OF_ROOT;
			obj->name = NULL;
			obj->name_len = 0;
		}
		else {
			dir = ROOT_DIR_SERIAL;
			dname = start;
			while (p - start < d_len) {
				while (*p != '/') p++;
				sum = uffs_MakeSum16(dname, p - dname);
				node = uffs_TreeFindDirNodeByName(dev, dname, p - dname, sum, dir);
				if (node == NULL) {
					obj->err = UENOENT;
					break;
				}
				else {
					dir = node->u.dir.serial;
					p++; // skip the '/'
					dname = p;
				}
			}
			obj->parent = dir;
			obj->name = start + (d_len > 0 ? d_len + 1 : 0);
			obj->name_len = len - (d_len > 0 ? d_len + 1 : 0) - m_len;
		}

		if (obj->err != UENOERR) {
			uffs_PutDevice(obj->dev);
			obj->dev = NULL;
		}
	}
	else {
		obj->err = UENOENT;
	}

	return (obj->err == UENOERR ? U_SUCC : U_FAIL);
}


static void do_ReleaseObjectResource(uffs_Object *obj)
{
	if (obj) {
		if (obj->dev) {
			if (HAVE_BADBLOCK(obj->dev))
				uffs_BadBlockRecover(obj->dev);
			if (obj->dev_lock_count > 0) {
				uffs_ObjectDevUnLock(obj);
			}
			uffs_PutDevice(obj->dev);
			obj->dev = NULL;
			obj->open_succ = U_FALSE;
		}
	}
}

/**
 * Open a UFFS object
 *
 * \param[in|out] obj the object to be open
 * \param[in] name the full name of the object
 * \param[in] oflag open flag
 *
 * \return U_SUCC if object is opened successfully,
 *			 U_FAIL if failed, error code will be set to obj->err.
 */
URET uffs_OpenObject(uffs_Object *obj, const char *name, int oflag)
{
	URET ret;

	if (obj == NULL)
		return U_FAIL;

 	if ((ret = uffs_ParseObject(obj, name)) == U_SUCC) {
		ret = uffs_OpenObjectEx(obj, obj->dev, obj->parent,
									obj->name, obj->name_len, oflag);
 	}
 	if (ret != U_SUCC)
 		do_ReleaseObjectResource(obj);

	return ret;
}

static URET do_FlushObject(uffs_Object *obj)
{
	uffs_Device *dev;
	URET ret = U_SUCC;
	TreeNode *node = NULL;

	dev = obj->dev;
	if (obj->node) {
		node = obj->node;
		if (obj->type == UFFS_TYPE_DIR)
			ret = uffs_BufFlushGroup(dev, obj->node->u.dir.parent,
										obj->node->u.dir.serial);
		else {
			ret = (
				uffs_BufFlushGroupMatchParent(dev, obj->node->u.file.serial) == U_SUCC &&
				uffs_BufFlushGroup(dev, obj->node->u.file.parent, obj->node->u.file.serial) == U_SUCC
				) ? U_SUCC : U_FAIL;
		}
		uffs_Assert(node == obj->node, "obj->node change!\n");
	}

	return ret;
}

/**
 * Flush object data.
 *
 * \param[in] obj object to be flushed
 * \return U_SUCC or U_FAIL (error code in obj->err).
 */
URET uffs_FlushObject(uffs_Object *obj)
{
	if(obj->dev == NULL || obj->open_succ != U_TRUE) {
		obj->err = UEBADF;
		goto ext;
	}

	uffs_ObjectDevLock(obj);

	if (do_FlushObject(obj) != U_SUCC)
		obj->err = UEIOERR;

	uffs_ObjectDevUnLock(obj);

ext:
	return (obj->err == UENOERR ? U_SUCC : U_FAIL);
}

/**
 * Close an openned object.
 *
 * \param[in] obj object to be closed
 * \return U_SUCC or U_FAIL (error code in obj->err).
 */
URET uffs_CloseObject(uffs_Object *obj)
{
#ifdef CONFIG_CHANGE_MODIFY_TIME
	uffs_Device *dev;
	uffs_Buf *buf;
	uffs_FileInfo fi;
#endif

	if(obj->dev == NULL || obj->open_succ != U_TRUE) {
		obj->err = UEBADF;
		goto ext;
	}


	uffs_ObjectDevLock(obj);

	if (obj->oflag & (UO_WRONLY|UO_RDWR|UO_APPEND|UO_CREATE|UO_TRUNC)) {

#ifdef CONFIG_CHANGE_MODIFY_TIME
        dev = obj->dev;
		if (obj->node) {
			//need to change the last modify time stamp
			if (obj->type == UFFS_TYPE_DIR)
				buf = uffs_BufGetEx(dev, UFFS_TYPE_DIR, obj->node, 0, obj->oflag);
			else
				buf = uffs_BufGetEx(dev, UFFS_TYPE_FILE, obj->node, 0, obj->oflag);

			if(buf == NULL) {
				uffs_Perror(UFFS_MSG_SERIOUS, "can't get file header");
				do_FlushObject(obj);
				uffs_ObjectDevUnLock(obj);
				goto ext;
			}
			uffs_BufRead(dev, buf, &fi, 0, sizeof(uffs_FileInfo));
			fi.last_modify = uffs_GetCurDateTime();
			uffs_BufWrite(dev, buf, &fi, 0, sizeof(uffs_FileInfo));
			uffs_BufPut(dev, buf);
		}
#endif
		do_FlushObject(obj);
	}

	uffs_ObjectDevUnLock(obj);

ext:
	do_ReleaseObjectResource(obj);

	return (obj->err == UENOERR ? U_SUCC : U_FAIL);
}

static u16 GetFdnByOfs(uffs_Object *obj, u32 ofs)
{
	uffs_Device *dev = obj->dev;

	if (ofs < (u32)(obj->head_pages * dev->com.pg_data_size)) {
		return 0;
	}
	else {
		ofs -= obj->head_pages * dev->com.pg_data_size;
		return (ofs / (dev->com.pg_data_size * dev->attr->pages_per_block)) + 1;
	}
}


static u32 GetStartOfDataBlock(uffs_Object *obj, u16 fdn)
{
	if (fdn == 0) {
		return 0;
	}
	else {
		return (obj->head_pages * obj->dev->com.pg_data_size) +
					(fdn - 1) * (obj->dev->com.pg_data_size	*
						obj->dev->attr->pages_per_block);
	}
}


static int do_WriteNewBlock(uffs_Object *obj,
						  const void *data, u32 len,
						  u16 parent,
						  u16 serial)
{
	uffs_Device *dev = obj->dev;
	u16 page_id;
	int wroteSize = 0;
	int size;
	uffs_Buf *buf;
	URET ret;

	for (page_id = 0; page_id < dev->attr->pages_per_block; page_id++) {
		size = (len - wroteSize) > dev->com.pg_data_size ?
					dev->com.pg_data_size : len - wroteSize;
		if (size <= 0)
			break;

		buf = uffs_BufNew(dev, UFFS_TYPE_DATA, parent, serial, page_id);
		if (buf == NULL) {
			uffs_Perror(UFFS_MSG_SERIOUS, "can't create a new page ?");
			break;
		}
		// Note: if data == NULL, we will fill '\0'
		ret = uffs_BufWrite(dev, buf, data == NULL ? NULL : (u8 *)data + wroteSize, 0, size);
		uffs_BufPut(dev, buf);

		if (ret != U_SUCC) {
			uffs_Perror(UFFS_MSG_SERIOUS, "write data fail!");
			break;
		}
		wroteSize += size;
		obj->node->u.file.len += size;
	}

	return wroteSize;
}

static int do_WriteInternalBlock(uffs_Object *obj,
							   TreeNode *node,
							   u16 fdn,
							   const void *data,
							   u32 len,
							   u32 blockOfs)
{
	uffs_Device *dev = obj->dev;
	u16 maxPageID;
	u16 page_id;
	u32 size;
	u32 pageOfs;
	u32 wroteSize = 0;
	URET ret;
	uffs_Buf *buf;
	u32 block_start;
	u8 type;
	u16 parent, serial;

	block_start = GetStartOfDataBlock(obj, fdn);

	if (fdn == 0) {
		type = UFFS_TYPE_FILE;
		parent = node->u.file.parent;
		serial = node->u.file.serial;
	}
	else {
		type = UFFS_TYPE_DATA;
		parent = node->u.data.parent;
		serial = fdn;
	}

	if (fdn == 0)
		maxPageID = obj->head_pages;
	else
		maxPageID = dev->attr->pages_per_block - 1;


	while (wroteSize < len) {
		page_id = blockOfs / dev->com.pg_data_size;
		if (fdn == 0)
			page_id++; //in file header, page_id start from 1, not 0.
		if (page_id > maxPageID) 
			break;

		pageOfs = blockOfs % dev->com.pg_data_size;
		size = (len - wroteSize + pageOfs) > dev->com.pg_data_size ?
					(dev->com.pg_data_size - pageOfs) : (len - wroteSize);

		if ((obj->node->u.file.len % dev->com.pg_data_size) == 0 &&
			(blockOfs + block_start) == obj->node->u.file.len) {

			buf = uffs_BufNew(dev, type, parent, serial, page_id);

			if(buf == NULL) {
				uffs_Perror(UFFS_MSG_SERIOUS, "can create a new buf!");
				break;
			}
		}
		else {
			buf = uffs_BufGetEx(dev, type, node, page_id, obj->oflag);
			if (buf == NULL) {
				uffs_Perror(UFFS_MSG_SERIOUS, "can't get buffer ?");
				break;
			}
		}

		// Note: if data == NULL, then we will fill '\0'
		ret = uffs_BufWrite(dev, buf, data == NULL ? NULL : (u8 *)data + wroteSize, pageOfs, size);

		uffs_BufPut(dev, buf);

		if (ret == U_FAIL) {
			uffs_Perror(UFFS_MSG_SERIOUS, "write inter data fail!");
			break;
		}

		wroteSize += size;
		blockOfs += size;

		if (block_start + blockOfs > obj->node->u.file.len)
			obj->node->u.file.len = block_start + blockOfs;

	}

	return wroteSize;
}


/**
 * write data to obj, return remain data (0 if all data been written).
 */
static int do_WriteObject(uffs_Object *obj, const void *data, int len)
{
	uffs_Device *dev = obj->dev;
	TreeNode *fnode = obj->node;
	int remain = len;
	u16 fdn;
	u32 write_start;
	TreeNode *dnode;
	u32 size;

	while (remain > 0) {
		write_start = obj->pos + len - remain;
		if (write_start > fnode->u.file.len) {
			uffs_Perror(UFFS_MSG_SERIOUS, "write point out of file ?");
			break;
		}

		fdn = GetFdnByOfs(obj, write_start);

		if (write_start == fnode->u.file.len && fdn > 0 &&
			write_start == GetStartOfDataBlock(obj, fdn)) {
			if (dev->tree.erased_count < dev->cfg.reserved_free_blocks) {
				uffs_Perror(UFFS_MSG_NOISY, "insufficient block in write obj, new block");
				break;
			}
			size = do_WriteNewBlock(obj, data ? (u8 *)data + len - remain : NULL,
										remain, fnode->u.file.serial, fdn);

			//
			// Flush the new block buffers immediately, so that the new data node will be
			// created and put in the tree.
			//
			// But before do that, we need to make sure the previous
			// data block (if exist) been flushed first.
			//
			if (fdn > 1) {
				uffs_BufFlushGroup(dev, fnode->u.file.serial, fdn - 1);
			}
			else {
				uffs_BufFlushGroup(dev, fnode->u.file.parent, fnode->u.file.serial);
			}
			// Now flush the new block.
			uffs_BufFlushGroup(dev, fnode->u.file.serial, fdn);

			if (size == 0) 
				break;

			remain -= size;
		}
		else {

			if(fdn == 0)
				dnode = obj->node;
			else
				dnode = uffs_TreeFindDataNode(dev, fnode->u.file.serial, fdn);

			if(dnode == NULL) {
				uffs_Perror(UFFS_MSG_SERIOUS, "can't find data node in tree ?");
				obj->err = UEUNKNOWN_ERR;
				break;
			}
			size = do_WriteInternalBlock(obj, dnode, fdn,
									data ? (u8 *)data + len - remain : NULL, remain,
									write_start - GetStartOfDataBlock(obj, fdn));
#ifdef CONFIG_FLUSH_BUF_AFTER_WRITE
			if (fdn == 0)
				uffs_BufFlushGroup(dev, fnode->u.file.parent, fnode->u.file.serial);
			else
				uffs_BufFlushGroup(dev, fnode->u.file.serial, fdn);
#endif
			if (size == 0)
				break;

			remain -= size;
		}
	}

	uffs_Assert(fnode == obj->node, "obj->node change!\n");

	return remain;
}


/**
 * write data to obj, from obj->pos
 *
 * \param[in] obj file obj
 * \param[in] data data pointer
 * \param[in] len length of data to be write
 *
 * \return bytes wrote to obj
 */
int uffs_WriteObject(uffs_Object *obj, const void *data, int len)
{
	uffs_Device *dev = obj->dev;
	TreeNode *fnode = NULL;
	int remain;
	u32 pos;
	int wrote = 0;

	if (obj == NULL) 
		return 0;

	if (obj->dev == NULL || obj->open_succ != U_TRUE) {
		obj->err = UEBADF;
		return 0;
	}

	if (obj->type == UFFS_TYPE_DIR) {
		uffs_Perror(UFFS_MSG_NOISY, "Can't write to an dir object!");
		obj->err = UEACCES;
		return 0;
	}

	if (obj->oflag == UO_RDONLY) {
		obj->err = UEACCES;  // can't write to 'read only' mode opened file
		return 0;
	}

	fnode = obj->node;

	uffs_ObjectDevLock(obj);

	if (obj->oflag & UO_APPEND)
		obj->pos = fnode->u.file.len;
	else {
		if (obj->pos > fnode->u.file.len) {
			// current pos pass over the end of file, need to fill the gap with '\0'
			pos = obj->pos;	// save desired pos
			obj->pos = fnode->u.file.len; // filling gap from the end of the file.
			remain = do_WriteObject(obj, NULL, pos - fnode->u.file.len);  // Write filling bytes. Note: the filling data does not count as 'wrote' in this write operation.
			obj->pos = pos - remain;
			if (remain > 0)	// fail to fill the gap ? stop.
				goto ext;
		}
	}

	remain = do_WriteObject(obj, data, len);
	wrote = len - remain;
	obj->pos += wrote;

ext:
	if (HAVE_BADBLOCK(dev))
		uffs_BadBlockRecover(dev);

	uffs_ObjectDevUnLock(obj);

	uffs_Assert(fnode == obj->node, "obj->node change!\n");

	return wrote;
}

/**
 * read data from obj
 *
 * \param[in] obj uffs object
 * \param[out] data output data buffer
 * \param[in] len required length of data to be read from object->pos
 *
 * \return return bytes of data have been read
 */
int uffs_ReadObject(uffs_Object *obj, void *data, int len)
{
	uffs_Device *dev = obj->dev;
	TreeNode *fnode = NULL;
	u32 remain = len;
	u16 fdn;
	u32 read_start;
	TreeNode *dnode;
	u32 size;
	uffs_Buf *buf;
	u32 blockOfs;
	u16 page_id;
	u8 type;
	u32 pageOfs;

	if (obj == NULL)
		return 0;

	fnode = obj->node;

	if (obj->dev == NULL || obj->open_succ == U_FALSE) {
		obj->err = UEBADF;
		return 0;
	}

	if (obj->type == UFFS_TYPE_DIR) {
		uffs_Perror(UFFS_MSG_NOISY, "Can't read data from a dir object!");
		obj->err = UEBADF;
		return 0;
	}

	if (obj->pos > fnode->u.file.len) {
		return 0; //can't read file out of range
	}

	if (obj->oflag & UO_WRONLY) {
		obj->err = UEACCES;
		return 0;
	}

	uffs_ObjectDevLock(obj);

	while (remain > 0) {
		read_start = obj->pos + len - remain;
		if (read_start >= fnode->u.file.len) {
			//uffs_Perror(UFFS_MSG_NOISY, "read point out of file ?");
			break;
		}

		fdn = GetFdnByOfs(obj, read_start);
		if (fdn == 0) {
			dnode = obj->node;
			type = UFFS_TYPE_FILE;
		}
		else {
			type = UFFS_TYPE_DATA;
			dnode = uffs_TreeFindDataNode(dev, fnode->u.file.serial, fdn);
			if (dnode == NULL) {
				uffs_Perror(UFFS_MSG_SERIOUS, "can't get data node in entry!");
				obj->err = UEUNKNOWN_ERR;
				break;
			}
		}

		blockOfs = GetStartOfDataBlock(obj, fdn);
		page_id = (read_start - blockOfs) / dev->com.pg_data_size;

		if (fdn == 0) {
			/**
			 * fdn == 0: this means that the reading is start from the first block,
			 * since the page 0 is for file attr, so we move to the next page ID.
			 */
			page_id++;
		}

		buf = uffs_BufGetEx(dev, type, dnode, (u16)page_id, obj->oflag);
		if (buf == NULL) {
			uffs_Perror(UFFS_MSG_SERIOUS, "can't get buffer when read obj.");
			obj->err = UEIOERR;
			break;
		}

		pageOfs = read_start % dev->com.pg_data_size;
		if (pageOfs >= buf->data_len) {
			//uffs_Perror(UFFS_MSG_NOISY, "read data out of page range ?");
			uffs_BufPut(dev, buf);
			break;
		}
		size = (remain + pageOfs > buf->data_len ? buf->data_len - pageOfs : remain);

		uffs_BufRead(dev, buf, (u8 *)data + len - remain, pageOfs, size);
		uffs_BufPut(dev, buf);

		remain -= size;
	}

	obj->pos += (len - remain);

	if (HAVE_BADBLOCK(dev)) 
		uffs_BadBlockRecover(dev);

	uffs_ObjectDevUnLock(obj);

	uffs_Assert(fnode == obj->node, "obj->node change!\n");

	return len - remain;
}

/**
 * move the file pointer
 *
 * \param[in] obj uffs object
 * \param[in] offset offset from origin
 * \param[in] origin the origin position, one of:
 *				#USEEK_CUR, #USEEK_SET or #USEEK_END
 *
 * \return the new file pointer position if success,
 *			or -1 if the new position would be negative.
 */
long uffs_SeekObject(uffs_Object *obj, long offset, int origin)
{
	if (obj->type == UFFS_TYPE_DIR) {
		uffs_Perror(UFFS_MSG_NOISY, "Can't seek a dir object!");
		obj->err = UEACCES;
	}
	else {
		uffs_ObjectDevLock(obj);
		switch (origin) {
			case USEEK_CUR:
				if ((long)obj->pos + offset < 0) {
					obj->err = UEINVAL;
				}
				else {
					obj->pos += offset;
				}
				break;
			case USEEK_SET:
				if (offset < 0) {
					obj->err = UEINVAL;
				}
				else {
					obj->pos = offset;
				}
				break;
			case USEEK_END:
				if ((long)obj->node->u.file.len + offset < 0) {
					obj->err = UEINVAL;
				}
				else {
					obj->pos = obj->node->u.file.len + offset;
				}
				break;
		}
		uffs_ObjectDevUnLock(obj);
	}

	return (obj->err == UENOERR ? (long)obj->pos : -1);
}

/**
 * get current file pointer
 *
 * \param[in] obj uffs object
 *
 * \return return the file pointer position if the obj is valid,
 *	 return -1 if obj is invalid.
 */
int uffs_GetCurOffset(uffs_Object *obj)
{
	if (obj) {
		if (obj->dev && obj->open_succ == U_TRUE)
			return obj->pos;
	}
	return -1;
}

/**
 * check whether the file pointer is at the end of file
 *
 * \param[in] obj uffs object
 *
 * \return return 1 if file pointer is at the end of file,
 *	 return -1 if error occur, else return 0.
 */
int uffs_EndOfFile(uffs_Object *obj)
{
	if (obj) {
		if (obj->dev && obj->type == UFFS_TYPE_FILE && obj->open_succ == U_TRUE) {
			if (obj->pos >= obj->node->u.file.len) {
				return 1;
			}
			else {
				return 0;
			}
		}
	}

	return -1;
}

//
// To trancate the file, this is the last block to be trancated.
// We need to discard one or more pages within this block, hence requires 'block recover'.
//
static URET do_TruncateInternalWithBlockRecover(uffs_Object *obj,
												u16 fdn, u32 remain, RunOptionE run_opt)
{
	uffs_Device *dev = obj->dev;
	TreeNode *fnode = obj->node;
	u16 page_id, max_page_id;
	TreeNode *node;
	uffs_Buf *buf = NULL;
	u8 type;
	u32 block_start;
	u16 parent, serial;
	int slot;
	uffs_BlockInfo *bc = NULL;
	int block = -1;

	if (fdn == 0) {
		node = fnode;
		type = UFFS_TYPE_FILE;
		max_page_id = obj->head_pages;
		block_start = 0;
		parent = node->u.file.parent;
		serial = node->u.file.serial;
		block = node->u.file.block;
	}
	else {
		node = uffs_TreeFindDataNode(dev, fnode->u.file.serial, fdn);
		if (node == NULL) {
			obj->err = UEIOERR;
			uffs_Perror(UFFS_MSG_SERIOUS,
						"can't find data node when truncate obj");
			goto ext;
		}
		block = node->u.data.block;
		type = UFFS_TYPE_DATA;
		max_page_id = dev->attr->pages_per_block - 1;
		block_start = obj->head_pages * dev->com.pg_data_size +
						(fdn - 1) * dev->com.pg_data_size *
						dev->attr->pages_per_block;
		parent = node->u.data.parent;
		serial = node->u.data.serial;
	}

	if (run_opt == eDRY_RUN) {
		// checking the buffer. this is the main reason why we need the 'dry run' mode.
		for (page_id = 0; page_id <= max_page_id; page_id++) {
			buf = uffs_BufFind(dev, parent, serial, page_id);
			if (buf) {
				//!< ok, the buffer was loaded before ...
				if (uffs_BufIsFree(buf) == U_FALSE) {
					obj->err = UEEXIST;
					break;	//!< and someone is still holding the buffer,
							//   can't truncate it !!!
				}
			}
		}
		buf = NULL;
		goto ext;
	}
	
	// find the last page *after* truncate
	for (page_id = (fdn == 0 ? 1 : 0); page_id <= max_page_id; page_id++) {
		if (block_start + (page_id + 1) * dev->com.pg_data_size >= remain)
			break;
	}

	if (!uffs_Assert(page_id <= max_page_id, "fdn = %d, block_start = %d, remain = %d\n", fdn, block_start, remain)) {
		obj->err = UEUNKNOWN_ERR;
		goto ext;
	}

	// flush buffer before performing block recovery
	uffs_BufFlushGroup(dev, parent, serial);

	// load the last page
	buf = uffs_BufGetEx(dev, type, node, page_id, obj->oflag);
	if (buf == NULL) {
		obj->err = UENOMEM;
		uffs_Perror(UFFS_MSG_SERIOUS, "Can't get buf");
		goto ext;
	}

	uffs_BufWrite(dev, buf, NULL, 0, 0); // just make this buf dirty

	// lock the group
	slot = uffs_BufFindGroupSlot(dev, parent, serial);
	uffs_BufLockGroup(dev, slot);

	if (remain == 0) // remain == 0: means discard all data in this block.
		buf->data_len = 0;
	else {
		remain = (remain % dev->com.pg_data_size);
		// remain == 0: means that we need to keep all data in this page.
		buf->data_len = (remain == 0 ? dev->com.pg_data_size : remain);
	}

	/* mark this buf as UFFS_BUF_EXT_MARK_TRUNC_TAIL, when flushing
		dirty buffers, UFFS will not do page recover for pages after
		this buf page id (because this file is ended at this page) */
	buf->ext_mark |= UFFS_BUF_EXT_MARK_TRUNC_TAIL;

	uffs_BufPut(dev, buf);

	// invalidate the rest page buf
	page_id++;
	for (; page_id <= max_page_id; page_id++) {
		buf = uffs_BufFind(dev, parent, serial, page_id);
		if (buf)
			uffs_BufMarkEmpty(dev, buf);
	}

	// flush dirty buffer immediately, forcing block recovery.
	uffs_BufFlushGroupEx(dev, parent, serial, U_TRUE);

	// unlock the group
	uffs_BufUnLockGroup(dev, slot);

	// Invalidate block info cache for the 'old' block
	bc = uffs_BlockInfoGet(dev, block);
	if (bc) {
		uffs_BlockInfoExpire(dev, bc, UFFS_ALL_PAGES);
		uffs_BlockInfoPut(dev, bc);
	}

ext:
	return (obj->err == UENOERR ? U_SUCC : U_FAIL);
}

/**
 * truncate an object
 *
 * \param[in] obj object to be truncated
 * \param[in] remain data bytes to be remained in this object
 *
 * \return U_SUCC or U_FAIL (error code in obj->err)
 */
URET uffs_TruncateObject(uffs_Object *obj, u32 remain)
{
	uffs_ObjectDevLock(obj);
	if (do_TruncateObject(obj, remain, eDRY_RUN) == U_SUCC)
		do_TruncateObject(obj, remain, eREAL_RUN);
	uffs_ObjectDevUnLock(obj);

	uffs_FlushObject(obj);

	return (obj->err == UENOERR ? U_SUCC : U_FAIL);
}

/** truncate obj without lock device */
static URET do_TruncateObject(uffs_Object *obj, u32 remain, RunOptionE run_opt)
{
	uffs_Device *dev = obj->dev;
	TreeNode *fnode = obj->node;
	u16 fdn;
	u32 flen;
	u32 block_start;
	TreeNode *node;
	uffs_BlockInfo *bc;
	uffs_Buf *buf;
	u16 page;
	int pos;

	pos = obj->pos;   // save current file position

	if (obj->dev == NULL || obj->open_succ == U_FALSE || fnode == NULL) {
		obj->err = UEBADF;
		goto ext;
	}

	/* can't truncate a dir */
	/* TODO: delete files under dir ? */
	if (obj->type == UFFS_TYPE_DIR) {
		obj->err = UEEXIST;
		goto ext;
	}

	if (remain >= fnode->u.file.len) {
		goto ext;	//!< nothing to do ... 
	}

	flen = fnode->u.file.len;

	if (flen < remain) {
		// file is shorter than 'reamin', fill the gap with '\0'
		if (run_opt == eREAL_RUN) {
			obj->pos = flen;  // move file pointer to the end
			if (do_WriteObject(obj, NULL, remain - flen) > 0) {	// fill '\0' ...
				uffs_Perror(UFFS_MSG_SERIOUS, "Write object not finished. expect %d but only %d wrote.",
												remain - flen, fnode->u.file.len - flen);
				obj->err = UEIOERR;   // likely be an I/O error.
			}
			flen = obj->node->u.file.len;
		}
	}
	else {
		while (flen > remain) {
			fdn = GetFdnByOfs(obj, flen - 1);

			//uffs_BufFlushGroup(dev, obj->serial, fdn);	//!< flush the buffer

			block_start = GetStartOfDataBlock(obj, fdn);
			if (remain <= block_start && fdn > 0) {
				node = uffs_TreeFindDataNode(dev, obj->serial, fdn);
				if (node == NULL) {
					uffs_Perror(UFFS_MSG_SERIOUS,
								"can't find data node when trancate obj.");
					obj->err = UEIOERR;
					goto ext;
				}
				bc = uffs_BlockInfoGet(dev, node->u.data.block);
				if (bc == NULL) {
					uffs_Perror(UFFS_MSG_SERIOUS,
								"can't get block info when trancate obj.");
					obj->err = UEIOERR;
					goto ext;
				}

				for (page = 0; page < dev->attr->pages_per_block; page++) {
					buf = uffs_BufFind(dev, fnode->u.file.serial, fdn, page);
					if (buf) {
						//!< ok, the buffer was loaded before ...
						if (uffs_BufIsFree(buf) == U_FALSE) {
							uffs_BlockInfoPut(dev, bc);
							goto ext;	//!< and someone is still holding the buffer,
										//   can't truncate it !!!
						}
						else if (run_opt == eREAL_RUN)
							uffs_BufMarkEmpty(dev, buf);	//!< discard the buffer
					}
				}

				if (run_opt == eREAL_RUN) {
					uffs_BreakFromEntry(dev, UFFS_TYPE_DATA, node);
					uffs_FlashEraseBlock(dev, bc->block);
					node->u.list.block = bc->block;
					if (HAVE_BADBLOCK(dev))
						uffs_BadBlockProcess(dev, node);
					else
						uffs_TreeInsertToErasedListTail(dev, node);

					fnode->u.file.len = block_start;
				}

				flen = block_start;
				uffs_BlockInfoPut(dev, bc);
			}
			else {
				if (do_TruncateInternalWithBlockRecover(obj, fdn,
														remain, run_opt) == U_SUCC) {
					if (run_opt == eREAL_RUN)
						fnode->u.file.len = remain;
					flen = remain;
				}
			}
		}
	}

	if (HAVE_BADBLOCK(dev)) 
		uffs_BadBlockRecover(dev);
ext:
	obj->pos = pos;  // keep file pointer offset not changed.

	uffs_Assert(fnode == obj->node, "obj->node change!\n");

	return (obj->err == UENOERR ? U_SUCC : U_FAIL);

}

/**
 * \brief check if there are anyone holding buf of this obj.
 *        If no one holding the buffers, expire the buffer.
 * \return
 *		0	: no one holding any buf of this obj
 *		>0	: the ref_count of buf which refer to this obj.
 */
int _CheckObjBufRef(uffs_Object *obj)
{
	uffs_Device *dev = obj->dev;
	uffs_Buf *buf;
	TreeNode *node = obj->node;
	u16 parent, serial, last_serial;

	// check the DIR or FILE block
	for (buf = uffs_BufFind(dev, obj->parent, obj->serial, UFFS_ALL_PAGES);
		 buf != NULL;
		 buf = uffs_BufFindFrom(dev, buf->next, obj->parent, obj->serial, UFFS_ALL_PAGES))
	{
		if (buf->ref_count > 0) {
			// oops ...
			uffs_Perror(UFFS_MSG_SERIOUS, "someone still hold buf parent = %d, serial = %d, ref_count",
				obj->parent, obj->serial, buf->ref_count);

			return buf->ref_count;
		}
		else {
			buf->mark = UFFS_BUF_EMPTY;
		}
	}

	if (buf == NULL || buf->ref_count == 0) {
		// check the DATA block
		if (obj->type == UFFS_TYPE_FILE && node->u.file.len > 0) {

			parent = obj->serial;
			last_serial = GetFdnByOfs(obj, node->u.file.len - 1);
			for (serial = 1; serial <= last_serial; serial++) {

				for (buf = uffs_BufFind(dev, parent, serial, UFFS_ALL_PAGES);
					 buf != NULL;
					 buf = uffs_BufFindFrom(dev, buf->next, parent, serial, UFFS_ALL_PAGES))
				{
					if (buf->ref_count != 0) {
						// oops ...
						uffs_Perror(UFFS_MSG_SERIOUS, "someone still hold buf parent = %d, serial = %d, ref_count",
							parent, serial, buf->ref_count);

						return buf->ref_count;
					}
					else {
						buf->mark = UFFS_BUF_EMPTY;
					}
				}
			}
		}
	}

	return 0;
}



/**
 * \brief delete uffs object
 *
 * \param[in] name full name of object
 * \param[out] err return error code
 *
 * \return U_SUCC if object is deleted successfully. 
 *	return U_FAIL if error happen, error code is set to *err.
 */
URET uffs_DeleteObject(const char * name, int *err)
{
	uffs_Object *obj, *work;
	TreeNode *node, *d_node;
	uffs_Device *dev = NULL;
	u16 block;
	u16 serial, parent, last_serial;
	UBOOL bad = U_FALSE;
	URET ret = U_FAIL;

	obj = uffs_GetObject();
	if (obj == NULL) {
		if (err)
			*err = UEMFILE;
		goto ext_unlock;
	}

	if (uffs_OpenObject(obj, name, UO_RDWR|UO_DIR) == U_FAIL) {
		if (uffs_OpenObject(obj, name, UO_RDWR) == U_FAIL) {
			if (err)
				*err = UENOENT;
			goto ext_unlock;
		}
	}

	dev = obj->dev;

	// working throught object pool see if the object is opened ...
	uffs_ObjectDevLock(obj);
	work = NULL;
	while ((work = (uffs_Object *)uffs_PoolFindNextAllocated(&_object_pool, work)) != NULL) {
		if (work != obj && 
			work->dev &&
			work->dev == obj->dev &&
			work->node &&
			work->node == obj->node) {
			// this object is opened, can't delete it.
			if (err)
				*err = UEACCES;
			goto ext_lock;
		}
	}

	if (obj->type == UFFS_TYPE_DIR) {
		// if the dir is not empty, can't delete it.
		node = uffs_TreeFindDirNodeWithParent(dev, obj->serial);
		if (node != NULL) {
			if (err)
				*err = UEACCES;
			goto ext_lock;  //have sub dirs ?
		}

		node = uffs_TreeFindFileNodeWithParent(dev, obj->serial);
		if (node != NULL) {
			if (err)
				*err = UEACCES;
			goto ext_lock;  //have sub files ?
		}
	}

	// before erase the block, we need to take care of the buffer ...
	uffs_BufFlushAll(dev);

	if (_CheckObjBufRef(obj) > 0) {
		if (err)
			*err = UEACCES;
		goto ext_lock;
	}

	node = obj->node;

	// ok, now we are safe to erase DIR/FILE block :-)
	block = GET_BLOCK_FROM_NODE(obj);
	parent = obj->serial;
	last_serial = (obj->type == UFFS_TYPE_FILE && node->u.file.len > 0 ? GetFdnByOfs(obj, node->u.file.len - 1) : 0);

	uffs_BreakFromEntry(dev, obj->type, node);
	uffs_FlashEraseBlock(dev, block);
	node->u.list.block = block;
	node->u.list.u.serial = obj->serial;

	// From now on, the object is gone physically,
	// but we need to 'suspend' this node so that no one will re-use
	// the serial number during deleting the reset part of object.

	if (HAVE_BADBLOCK(dev)) {
		uffs_BadBlockProcessSuspend(dev, node);
		bad = U_TRUE;  // will be put into 'bad' list later
	}
	else {
		uffs_TreeSuspendAdd(dev, node);
		bad = U_FALSE;	// will be put into erased list later
	}

	// now erase DATA blocks
	if (obj->type == UFFS_TYPE_FILE && last_serial > 0) {
		for (serial = 1; serial <= last_serial; serial++) {

			uffs_ObjectDevUnLock(obj);
			; // yield CPU to improve responsive when deleting large file.
			uffs_ObjectDevLock(obj);

			d_node = uffs_TreeFindDataNode(dev, parent, serial);
			if (uffs_Assert(d_node != NULL, "Can't find DATA node parent = %d, serial = %d\n", parent, serial)) {
				uffs_BreakFromEntry(dev, UFFS_TYPE_DATA, d_node);
				block = d_node->u.data.block;
				uffs_FlashEraseBlock(dev, block);
				d_node->u.list.block = block;
				if (HAVE_BADBLOCK(dev))
					uffs_BadBlockProcess(dev, d_node);
				else
					uffs_TreeInsertToErasedListTail(dev, d_node);
			}
		}
	}
	
	// now process the suspend node
	uffs_TreeRemoveSuspendNode(dev, node);
	if (bad)
		uffs_TreeInsertToBadBlockList(dev, node);
	else
		uffs_TreeInsertToErasedListTail(dev, node);

	ret = U_SUCC;

ext_lock:
	uffs_ObjectDevUnLock(obj);
ext_unlock:
	do_ReleaseObjectResource(obj);

	uffs_PutObject(obj);

	return ret;
}

/**
 * Remove object under a new parent, change object name.
 *
 * \param[in|out] obj
 * \param[in] new_parent new parent's serial number
 * \param[in] new_name new name of the object.
 *			 if new_name == NULL, keep the old name.
 * \param[in] name_len new name length.
 *
 * \return U_SUCC or U_FAIL (obj->err for the reason)
 */
URET uffs_MoveObjectEx(uffs_Object *obj,
					   int new_parent, const char *new_name, int name_len)
{
	uffs_Buf *buf;
	uffs_FileInfo fi;
	uffs_Device *dev = obj->dev;
	TreeNode *node = obj->node;

	if (dev == NULL || node == NULL || obj->open_succ != U_TRUE) {
		obj->err = UEBADF;
		goto ext;
	}

	uffs_ObjectDevLock(obj);

	obj->parent = new_parent;

	if (name_len > 0) {

		buf = uffs_BufGetEx(dev, obj->type, node, 0, obj->oflag);
		if (buf == NULL) {
			uffs_Perror(UFFS_MSG_SERIOUS, "can't get buf when rename!");
			obj->err = UEIOERR;
			goto ext_1;
		}

		memcpy(&fi, buf->data, sizeof(uffs_FileInfo));

		if (new_name[name_len-1] == '/')
			name_len--;

		memcpy(fi.name, new_name, name_len);
		fi.name[name_len] = 0;
		fi.name_len = name_len;
		fi.last_modify = uffs_GetCurDateTime();

		buf->parent = new_parent;	// !! need to manually change the 'parent' !!
		uffs_BufWrite(dev, buf, &fi, 0, sizeof(uffs_FileInfo));
		uffs_BufPut(dev, buf);

		// !! force a block recover so that all old tag will be expired !!
		// This is important so we only need to check
		// the first spare when mount UFFS :)
		uffs_BufFlushGroupEx(dev, obj->parent, obj->serial, U_TRUE);

		obj->name = new_name;
		obj->name_len = name_len;
		obj->sum = uffs_MakeSum16(fi.name, fi.name_len);
	}

	//update the check sum and new parent of tree node
	if (obj->type == UFFS_TYPE_DIR) {
		obj->node->u.dir.checksum = obj->sum;
		obj->node->u.dir.parent = new_parent;
	}
	else {
		obj->node->u.file.checksum = obj->sum;
		obj->node->u.file.parent = new_parent;
	}

ext_1:
	uffs_ObjectDevUnLock(obj);
ext:

	return (obj->err == UENOERR ? U_SUCC : U_FAIL);
}

/**
 * \brief rename(move) file or dir.
 * \return U_SUCC if success, otherwise return U_FAIL and set error code to *err.
 * \note rename/move file between different mount point is not allowed.
 */
URET uffs_RenameObject(const char *old_name, const char *new_name, int *err)
{
	uffs_Object *obj = NULL, *new_obj = NULL;
	URET ret = U_FAIL;
	int oflag;

	obj = uffs_GetObject();
	new_obj = uffs_GetObject();

	if (obj == NULL || new_obj == NULL) {
		if (err) 
			*err = UEINVAL;
		goto ext;
	}

	oflag = UO_RDONLY;
	if (uffs_OpenObject(new_obj, new_name, oflag) == U_SUCC) {
		uffs_CloseObject(new_obj);
		uffs_Perror(UFFS_MSG_NOISY, "new object already exist!");
		if (err)
			*err = UEEXIST;
		goto ext;
	}
	oflag |= UO_DIR;
	if (uffs_OpenObject(new_obj, new_name, oflag) == U_SUCC) {
		uffs_CloseObject(new_obj);
		uffs_Perror(UFFS_MSG_NOISY, "new object already exist!");
		if (err)
			*err = UEEXIST;
		goto ext;
	}

	if (uffs_ParseObject(new_obj, new_name) != U_SUCC) {
		uffs_Perror(UFFS_MSG_NOISY, "parse new name fail !");
		if (err)
			*err = UENOENT;
		goto ext;
	}

	if (new_obj->name_len == 0) {
		uffs_Perror(UFFS_MSG_NOISY, "invalid new name");
		if (err)
			*err = UEINVAL;
		goto ext;
	}

	oflag = UO_RDONLY;
	if (uffs_OpenObject(obj, old_name, oflag) != U_SUCC) {
		oflag |= UO_DIR;
		if (uffs_OpenObject(obj, old_name, oflag) != U_SUCC) {
			uffs_Perror(UFFS_MSG_NOISY, "Can't open old object !");
			if (err)
				*err = UEACCES;
			goto ext;
		}
	}

	if (obj->dev != new_obj->dev) {
		uffs_Perror(UFFS_MSG_NOISY,
					"Can't move object between different mount point");
		if (err)
			*err = UEACCES;
	}
	else {
		ret = uffs_MoveObjectEx(obj, new_obj->parent,
									new_obj->name, new_obj->name_len);
		if (ret == U_FAIL && err)
			*err = obj->err;
	}

	uffs_CloseObject(obj);

ext:
	if (obj) uffs_PutObject(obj);
	if (new_obj) {
		do_ReleaseObjectResource(new_obj);
		uffs_PutObject(new_obj);
	}

	return ret;
}

