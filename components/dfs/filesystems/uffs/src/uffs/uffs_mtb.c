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
#include "uffs_config.h"
#include "uffs/uffs_types.h"
#include "uffs/uffs_public.h"
#include "uffs/uffs_tree.h"
#include "uffs/uffs_mtb.h"
#include "uffs/uffs_fd.h"
#include "uffs/uffs_utils.h"
#include "uffs/uffs_fs.h"
#include <string.h>

#define PFX "mtb : "

static struct uffs_MountTableEntrySt *m_head = NULL;		// list of mounted entries
static struct uffs_MountTableEntrySt *m_free_head = NULL;	// list of unmounted entries

/** Return mounted entries header */
uffs_MountTable * uffs_MtbGetMounted(void)
{
	return m_head;
}

/** Return unmounted entries header */
uffs_MountTable * uffs_MtbGetUnMounted(void)
{
	return m_free_head;
}

/**
 * \brief Register mount table
 * \param mtb mount table entry
 * \return 0 succ
 *         -1 failed (e.g. already registered and mounted)
 */
int uffs_RegisterMountTable(uffs_MountTable *mtb)
{
	uffs_MountTable *work = NULL;
	static int dev_num = 0;

	if (mtb == NULL) 
		return -1;

	for (work = m_head; work; work = work->next) {
		if (work == mtb)
			return -1; // already mounted ?
	}

	for (work = m_free_head; work; work = work->next) {
		if (work == mtb)
			return 0; // already registered.
	}

	/* replace the free head */
	if (m_free_head)
		m_free_head->prev = mtb;
	mtb->prev = NULL;
	mtb->next = m_free_head;
	m_free_head = mtb;
	
	mtb->dev->dev_num = ++dev_num;

	return 0;
}

/**
 * \brief Remove mount entry from the table
 * \param mtb mount table entry
 * \return 0 removed succ
 *         -1 entry in used or not in the 'unmounted' list
 */
int uffs_UnRegisterMountTable(uffs_MountTable *mtb)
{
	uffs_MountTable *work = NULL;

	if (mtb == NULL)
		return -1;

	for (work = m_head; work; work = work->next) {
		if (work == mtb)
			return -1;	// in the mounted list ? busy, return
	}

	for (work = m_free_head; work; work = work->next) {
		if (work == mtb) {
			// found, remove it from the list
			if (work->next)
				work->next->prev = work->prev;
			if (work->prev)
				work->prev->next = work->next;
			if (work == m_free_head)
				m_free_head = work->next;

			break;
		}
	}

	return work ? 0 : -1;
}

static uffs_MountTable * uffs_GetMountTableByMountPoint(const char *mount, uffs_MountTable *head)
{
	uffs_MountTable *work = NULL;

	for (work = head; work; work = work->next) {
		if (strcmp(work->mount, mount) == 0)
			break;
	}	
	return work;
}

/**
 * \brief mount partition
 * \param[in] mount partition mount point
 * \return 0 succ
 *         <0 fail
 *
 * \note use uffs_RegisterMountTable() register mount entry before you can mount it.
 *       mount point should ended with '/', e.g. '/sys/'
 */
int uffs_Mount(const char *mount)
{
	uffs_MountTable *mtb;

	if (uffs_GetMountTableByMountPoint(mount, m_head) != NULL) {
		uffs_Perror(UFFS_MSG_NOISY,	"'%s' already mounted", mount);
		return -1; // already mounted ?
	}
	
	mtb = uffs_GetMountTableByMountPoint(mount, m_free_head);
	if (mtb == NULL) {
		uffs_Perror(UFFS_MSG_NOISY,	"'%s' not registered", mount);
		return -1;	// not registered ?
	}

	uffs_Perror(UFFS_MSG_NOISY,
				"init device for mount point %s ...",
				mtb->mount);

	mtb->dev->par.start = mtb->start_block;
	if (mtb->end_block < 0) {
		mtb->dev->par.end = 
			mtb->dev->attr->total_blocks + mtb->end_block;
	}
	else {
		mtb->dev->par.end = mtb->end_block;
	}

	if (mtb->dev->Init(mtb->dev) == U_FAIL) {
		uffs_Perror(UFFS_MSG_SERIOUS,
					"init device for mount point %s fail",
					mtb->mount);
		return -1;
	}

	uffs_Perror(UFFS_MSG_NOISY, "mount partiton: %d,%d",
		mtb->dev->par.start, mtb->dev->par.end);

	if (uffs_InitDevice(mtb->dev) != U_SUCC) {
		uffs_Perror(UFFS_MSG_SERIOUS, "init device fail !");
		return -1;
	}

	/* now break it from unmounted list */
	if (mtb->prev)
		mtb->prev->next = mtb->next;
	if (mtb->next)
		mtb->next->prev = mtb->prev;
	if (m_free_head == mtb)
		m_free_head = mtb->next;

	/* link to mounted list */
	mtb->prev = NULL;
	mtb->next = m_head;
	if (m_head)
		m_head->prev = mtb;
	m_head = mtb;

	return 0;
}

/**
 * \brief unmount parttion
 * \param[in] mount partition mount point
 * \return 0 succ
 *         <0 fail
 */
int uffs_UnMount(const char *mount)
{
	uffs_MountTable *mtb = uffs_GetMountTableByMountPoint(mount, m_head);

	if (mtb == NULL) {
		uffs_Perror(UFFS_MSG_NOISY,	"'%s' not mounted ?", mount);
		return -1;  // not mounted ?
	}

	if (uffs_GetMountTableByMountPoint(mount, m_free_head) != NULL) {
		uffs_Perror(UFFS_MSG_NOISY,	"'%s' already unmounted ?", mount);
		return -1;  // already unmounted ?
	}

	if (mtb->dev->ref_count != 0) {
		uffs_Perror(UFFS_MSG_NORMAL, "Can't unmount '%s' - busy", mount);
		return -1;
	}

	if (uffs_ReleaseDevice(mtb->dev) == U_FAIL) {
		uffs_Perror(UFFS_MSG_NORMAL, "Can't release device for mount point '%s'", mount);
		return -1;
	}

	mtb->dev->Release(mtb->dev);

	// break from mounted list
	if (mtb->prev)
		mtb->prev->next = mtb->next;
	if (mtb->next)
		mtb->next->prev = mtb->prev;
	if (mtb == m_head)
		m_head = mtb->next;

	// put to unmounted list
	mtb->prev = NULL;
	mtb->next = m_free_head;
	if (m_free_head)
		m_free_head->prev = mtb;
	m_free_head = mtb;

	return 0;
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
	uffs_MountTable *mtb = uffs_GetMountTableByMountPoint(mount, m_head);

	if (mtb) {
		mtb->dev->ref_count++;
		return mtb->dev;
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
	uffs_MountTable *work = NULL;

	for (work = m_head; work; work = work->next) {
		if (strlen(work->mount) == len &&
				strncmp(mount, work->mount, len) == 0) {
			work->dev->ref_count++;
			return work->dev;
		}
	}

	return NULL;
}


/**
 * return mount point from device
 *
 * \param[in] dev uffs device
 * \return NULL if mount point is not found, 
 *		otherwise return mount point name in mount table.
 */
const char * uffs_GetDeviceMountPoint(uffs_Device *dev)
{
	uffs_MountTable *work = NULL;

	for (work = m_head; work; work = work->next) {
		if (work->dev == dev) {
			return work->mount;
		}
	}

	return NULL;	
}

void uffs_PutDevice(uffs_Device *dev)
{
	dev->ref_count--;
}


