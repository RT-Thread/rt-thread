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
 * \file uffs_find.c
 * \brief find objects under dir
 * \author Ricky Zheng, created 13th July, 2009
 */

#include <string.h> 
#include <stdio.h>
#include "uffs_config.h"
#include "uffs/uffs_find.h"

#define TPOOL(dev) &((dev)->mem.tree_pool)

static void ResetFindInfo(uffs_FindInfo *f)
{
	f->hash = 0;
	f->work = NULL;
	f->step = 0;
	f->pos = 0;
}

static URET _LoadObjectInfo(uffs_Device *dev,
							TreeNode *node,
							uffs_ObjectInfo *info,
							int type,
							int *err)
{
	uffs_Buf *buf;

	buf = uffs_BufGetEx(dev, (u8)type, node, 0, 0);

	if (buf == NULL) {
		if (err)
			*err = UENOMEM;
		return U_FAIL;
	}

	memcpy(&(info->info), buf->data, sizeof(uffs_FileInfo));

	if (type == UFFS_TYPE_DIR) {
		info->len = 0;
		info->serial = node->u.dir.serial;
	}
	else {
		info->len = node->u.file.len;
		info->serial = node->u.file.serial;
	}

	uffs_BufPut(dev, buf);

	return U_SUCC;
}

/**
 * get object information
 *
 * \param[in] obj the object to be revealed
 * \param[out] info object information will be loaded to info
 * \param[out] err return error code if failed
 *
 * \return U_SUCC or U_FAIL
 *
 * \node the obj should be openned before call this function.
 */
URET uffs_GetObjectInfo(uffs_Object *obj, uffs_ObjectInfo *info, int *err)
{
	uffs_Device *dev = obj->dev;
	URET ret = U_FAIL;

	uffs_DeviceLock(dev);

	if (obj && dev && info) {
		if (obj->parent == PARENT_OF_ROOT) {
			// this is ROOT. UFFS does not physically has root, just fake it ...
			memset(info, 0, sizeof(uffs_ObjectInfo));
			info->serial = obj->serial;
			info->info.attr |= (FILE_ATTR_DIR | FILE_ATTR_WRITE);
			if (err)
				*err = UENOERR;
			ret = U_SUCC;
		}
		else
			ret = _LoadObjectInfo(dev, obj->node, info, obj->type, err);
	}
	else {
		if (err)
			*err = UEINVAL;
	}

	uffs_DeviceUnLock(dev);

	return ret;
}


/**
 * Open a FindInfo for finding objects under dir
 *
 * \param[out] f uffs_FindInfo structure
 * \param[in] dir an openned dir object (openned by uffs_OpenObject() ). 
 *
 * \return U_SUCC if success, U_FAIL if invalid param or the dir
 *			is not been openned.
 */
URET uffs_FindObjectOpen(uffs_FindInfo *f, uffs_Object *dir)
{
	if (f == NULL || dir == NULL ||
			dir->dev == NULL || dir->open_succ != U_TRUE)
		return U_FAIL;

	f->dev = dir->dev;
	f->serial = dir->serial;
	ResetFindInfo(f);

	return U_SUCC;
}

/**
 * Open a FindInfo for finding objects under dir
 *
 * \param[out] f uffs_FindInfo structure
 * \param[in] dev uffs device
 * \param[in] dir serial number of the dir to be searched
 *
 * \return U_SUCC if success, U_FAIL if invalid param or the dir
 *			serial number is not valid.
 */
URET uffs_FindObjectOpenEx(uffs_FindInfo *f, uffs_Device *dev, int dir)
{
	TreeNode *node;

	if (f == NULL || dev == NULL)
		return U_FAIL;

	node = uffs_TreeFindDirNode(dev, dir);

	if (node == NULL)
		return U_FAIL;

	f->serial = dir;
	f->dev = dev;
	ResetFindInfo(f);

	return U_SUCC;
}


static URET do_FindObject(uffs_FindInfo *f, uffs_ObjectInfo *info, u16 x)
{
	URET ret = U_SUCC;
	TreeNode *node;
	uffs_Device *dev = f->dev;

	if (f->step == 0) { //!< working on dirs
		while (x != EMPTY_NODE) {
			node = FROM_IDX(x, TPOOL(dev));
			if (node->u.dir.parent == f->serial) {
				f->work = node;
				f->pos++;
				if (info)
					ret = _LoadObjectInfo(dev, node, info, UFFS_TYPE_DIR, NULL);
				goto ext;
			}
			x = node->hash_next;
		}

		f->hash++; //come to next hash entry

		for (; f->hash < DIR_NODE_ENTRY_LEN; f->hash++) {
			x = dev->tree.dir_entry[f->hash];
			while (x != EMPTY_NODE) {
				node = FROM_IDX(x, TPOOL(dev));
				if (node->u.dir.parent == f->serial) {
					f->work = node;
					f->pos++;
					if (info)
						ret = _LoadObjectInfo(dev, node, info, UFFS_TYPE_DIR, NULL);
					goto ext;
				}
				x = node->hash_next;
			}
		}

		//no subdirs, then lookup files ..
		f->step++;
		f->hash = 0;
		x = dev->tree.file_entry[f->hash];
	}

	if (f->step == 1) {

		while (x != EMPTY_NODE) {
			node = FROM_IDX(x, TPOOL(dev));
			if (node->u.file.parent == f->serial) {
				f->work = node;
				f->pos++;
				if (info)
					ret = _LoadObjectInfo(dev, node, info, UFFS_TYPE_FILE, NULL);
				goto ext;
			}
			x = node->hash_next;
		}

		f->hash++; //come to next hash entry

		for (; f->hash < FILE_NODE_ENTRY_LEN; f->hash++) {
			x = dev->tree.file_entry[f->hash];
			while (x != EMPTY_NODE) {
				node = FROM_IDX(x, TPOOL(dev));
				if (node->u.file.parent == f->serial) {
					f->work = node;
					f->pos++;
					if (info) 
						ret = _LoadObjectInfo(dev, node, info, UFFS_TYPE_FILE, NULL);
					goto ext;
				}
				x = node->hash_next;
			}
		}

		//no any files, stopped.
		f->step++;
	}

	ret = U_FAIL;
ext:

	return ret;

}


/**
 * Find the first object
 *
 * \param[out] info the object information will be filled to info.
 *				if info is NULL, then skip this object.
 * \param[in] f uffs_FindInfo structure, openned by uffs_FindObjectOpen().
 *
 * \return U_SUCC if an object is found, U_FAIL if no object is found.
 */
URET uffs_FindObjectFirst(uffs_ObjectInfo * info, uffs_FindInfo * f)
{
	uffs_Device *dev = f->dev;
	URET ret = U_SUCC;

	uffs_DeviceLock(dev);
	ResetFindInfo(f);
	ret = do_FindObject(f, info, dev->tree.dir_entry[0]);
	uffs_DeviceUnLock(dev);

	return ret;
}

/**
 * Find the next object.
 *
 * \param[out] info the object information will be filled to info.
 *				if info is NULL, then skip this object.
 * \param[in] f uffs_FindInfo structure, openned by uffs_FindObjectOpen().
 *
 * \return U_SUCC if an object is found, U_FAIL if no object is found.
 *
 * \note uffs_FindObjectFirst() should be called before uffs_FindObjectNext().
 */
URET uffs_FindObjectNext(uffs_ObjectInfo *info, uffs_FindInfo * f)
{
	uffs_Device *dev = f->dev;
	URET ret = U_SUCC;

	if (dev == NULL || f->step > 1) 
		return U_FAIL;

	if (f->work == NULL)
		return uffs_FindObjectFirst(info, f);

	uffs_DeviceLock(dev);
	ret = do_FindObject(f, info, f->work->hash_next);
	uffs_DeviceUnLock(dev);

	return ret;
}

/**
 * Rewind a find object process.
 *
 * \note After rewind, you can call uffs_FindObjectFirst() to
 *			start find object process.
 */
URET uffs_FindObjectRewind(uffs_FindInfo *f)
{
	if (f == NULL)
		return U_FAIL;

	ResetFindInfo(f);

	return U_SUCC;
}

/**
 * Close Find Object.
 *
 * \param[in] f uffs_FindInfo structure, openned by uffs_FindObjectOpen().
 *
 * \return U_SUCC if success, U_FAIL if invalid param.
 */
URET uffs_FindObjectClose(uffs_FindInfo * f)
{
	if (f == NULL)
		return U_FAIL;

	f->dev = NULL;
	ResetFindInfo(f);

	return U_SUCC;
}

/**
 * Count objects
 *
 * \param[in] f uffs_FindInfo structure, openned by uffs_FindObjectOpen().
 *
 * \return object counts
 * \note after call this function, you need to call
 *		 uffs_FindObjectRewind() to start finding process.
 */
int uffs_FindObjectCount(uffs_FindInfo *f)
{
	if (uffs_FindObjectFirst(NULL, f) == U_SUCC) {
		while (uffs_FindObjectNext(NULL, f) == U_SUCC) { };
	}
	return f->pos;
}

/**
 * Return current finding position
 *
 * \param[in] f uffs_FindInfo structure, openned by uffs_FindObjectOpen().
 *
 * \return current finding position
 */
int uffs_FindObjectTell(uffs_FindInfo *f)
{
	return f->pos;
}

