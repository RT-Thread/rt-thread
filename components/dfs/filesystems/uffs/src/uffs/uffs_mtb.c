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
 * \file uffs_mtb.c
 * \brief mount table operations
 * \author Ricky Zheng, created 11th July, 2009
 */

#include "uffs/uffs_types.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_config.h"
#include "uffs/uffs_tree.h"
#include "uffs/uffs_mtb.h"
#include "uffs/uffs_fd.h"
#include <string.h>

#define PFX "mtb:  "

static struct uffs_MountTableEntrySt *g_mtb_head = NULL;

uffs_MountTable * uffs_GetMountTable(void)
{
	return g_mtb_head;
}

int uffs_RegisterMountTable(uffs_MountTable *mtab)
{
	uffs_MountTable *work = g_mtb_head;

	if (mtab == NULL) 
		return -1;

	if (work == NULL) {
		g_mtb_head = mtab;
		return 0;
	}

	while (work) {
		if (mtab == work) {
			/* already registered */
			return 0;
		}
		if (work->next == NULL) {
			work->next = mtab;
			mtab->next = NULL;
			return 0;
		}
		work = work->next;
	}

	return -1;
}


URET uffs_InitMountTable(void)
{
	struct uffs_MountTableEntrySt *tbl = uffs_GetMountTable();
	struct uffs_MountTableEntrySt *work;
	int dev_num = 0;

	for (work = tbl; work; work = work->next) {
		uffs_Perror(UFFS_ERR_NOISY, "init device for mount point %s ...", work->mount);
		if (work->dev->Init(work->dev) == U_FAIL) {
			uffs_Perror(UFFS_ERR_SERIOUS, "init device for mount point %s fail", work->mount);
			return U_FAIL;
		}

		work->dev->par.start = work->start_block;
		if (work->end_block < 0) 
		{
			work->dev->par.end = work->dev->attr->total_blocks + work->end_block;
		}
		else 
		{
			work->dev->par.end = work->end_block;
		}
		uffs_Perror(UFFS_ERR_NOISY, "mount partiton: %d,%d",
			work->dev->par.start, work->dev->par.end);

		if (uffs_InitDevice(work->dev) != U_SUCC) 
		{
			uffs_Perror(UFFS_ERR_SERIOUS, "init device fail !");
			return U_FAIL;
		}
		work->dev->dev_num = dev_num++;
	}

	if (uffs_InitObjectBuf() == U_SUCC) {
		if (uffs_InitDirEntryBuf() == U_SUCC) {
			return U_SUCC;
		}
	}

	return U_FAIL;
}

URET uffs_ReleaseMountTable(void)
{
	struct uffs_MountTableEntrySt *tbl = uffs_GetMountTable();
	struct uffs_MountTableEntrySt *work;

	for (work = tbl; work; work = work->next) {
		uffs_ReleaseDevice(work->dev);
		work->dev->Release(work->dev);
	}

	if (uffs_ReleaseObjectBuf() == U_SUCC) {
		if (uffs_ReleaseDirEntryBuf() == U_SUCC) {
			return U_SUCC;
		}
	}

	return U_FAIL;
}



/**
 * find the matched mount point from a given full absolute path.
 *
 * \param[in] path full path
 * \return the length of mount point.
 */
int uffs_GetMatchedMountPointSize(const char *path)
{
	int pos;
	uffs_Device *dev;

	if (path[0] != '/')
		return 0;

	pos = strlen(path);

	while (pos > 0) {
		if ((dev = uffs_GetDeviceFromMountPointEx(path, pos)) != NULL ) {
			uffs_PutDevice(dev);
			return pos;
		}
		else {
			if (path[pos-1] == '/') 
				pos--;
			//back forward search the next '/'
			for (; pos > 0 && path[pos-1] != '/'; pos--)
				;
		}
	}

	return pos;
}

/**
 * get device from mount point.
 *
 * \param[in] mount mount point name.
 * \return NULL if mount point is not found.
 */
uffs_Device * uffs_GetDeviceFromMountPoint(const char *mount)
{
	struct uffs_MountTableEntrySt *devTab = uffs_GetMountTable();

	while (devTab) {
		if (strcmp(mount, devTab->mount) == 0) {
			devTab->dev->ref_count++;
			return devTab->dev;
		}
		devTab = devTab->next;
	}

	return NULL;
}

/**
 * get device from mount point.
 *
 * \param[in] mount mount point name.
 * \param[in] len mount point name length.
 * \return NULL if mount point is not found.
 */
uffs_Device * uffs_GetDeviceFromMountPointEx(const char *mount, int len)
{
	struct uffs_MountTableEntrySt *devTab = uffs_GetMountTable();

	while (devTab) {
		if (strlen(devTab->mount) == len && strncmp(mount, devTab->mount, len) == 0) {
			devTab->dev->ref_count++;
			return devTab->dev;
		}
		devTab = devTab->next;
	}

	return NULL;
}


/**
 * return mount point from device
 *
 * \param[in] dev uffs device
 * \return NULL if mount point is not found, otherwise return mount point name in mount table.
 */
const char * uffs_GetDeviceMountPoint(uffs_Device *dev)
{
	struct uffs_MountTableEntrySt * devTab = uffs_GetMountTable();

	while (devTab) {
		if (devTab->dev == dev) {
			return devTab->mount;
		}
		devTab = devTab->next;
	}

	return NULL;	
}

void uffs_PutDevice(uffs_Device *dev)
{
	dev->ref_count--;
}


