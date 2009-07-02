/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : ls.h                                                             *
* Release  : 0.3 - devel                                                      *
* Description : This file contains functions to list the files in a directory *
*                                                                             *
* This program is free software; you can redistribute it and/or               *
* modify it under the terms of the GNU General Public License                 *
* as published by the Free Software Foundation; version 2                     *
* of the License.                                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful,             *
* but WITHOUT ANY WARRANTY; without even the implied warranty of              *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
* GNU General Public License for more details.                                *
*                                                                             *
* As a special exception, if other files instantiate templates or             *
* use macros or inline functions from this file, or you compile this          *
* file and link it with other works to produce a work based on this file,     *
* this file does not by itself cause the resulting work to be covered         *
* by the GNU General Public License. However the source code for this         *
* file must still be made available in accordance with section (3) of         *
* the GNU General Public License.                                             *
*                                                                             *
* This exception does not invalidate any other reasons why a work based       *
* on this file might be covered by the GNU General Public License.            *
*                                                                             *
*                                                    (c)2006 Lennart Yseboodt *
*                                                    (c)2006 Michael De Nil   *
\*****************************************************************************/

#ifndef __LS_H__
#define __LS_H__

/*****************************************************************************/
#include "config.h"
#include "fs.h"
#include "dir.h"
#include "fat.h"
/*****************************************************************************/

struct _ListDirEntry{
	euint8 FileName[LIST_MAXLENFILENAME];
	euint32 FileSize;
	euint8 Attribute;
};
typedef struct _ListDirEntry ListDirEntry;

struct _DirList{
	FileSystem *fs;
	euint16 cEntry,rEntry;
	/*FileRecord currentEntry;*/
	ListDirEntry currentEntry;
	ClusterChain Cache;
};
typedef struct _DirList DirList;

esint8 ls_openDir(DirList *dlist,FileSystem *fs,eint8* dirname);
esint8 ls_getNext(DirList *dlist);

esint8 ls_getDirEntry(DirList *dlist);
esint8 ls_getRealDirEntry(DirList *dlist);
esint8 ls_getRootAreaEntry(DirList *dlist);
esint8 ls_isValidFileEntry(ListDirEntry *entry);
void   ls_fileEntryToDirListEntry(DirList *dlist, euint8* buf, euint16 offset);

#endif
