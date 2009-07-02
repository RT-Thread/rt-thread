/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : dir.h                                                            *
* Release  : 0.3 - devel                                                      *
* Description : The functions of dir.c are part of fs.c, they deal with all   *
*               the directory specific stuff.                                 *
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

#ifndef __DDIR_H__
#define __DDIR_H__

/*****************************************************************************/
#include "config.h"
#include "error.h"
#include "fat.h"
#include "plibc.h"
#include "types.h"
// #include "ioman.h"
#include "tm.h"
#include "fs.h"
#include <dfs_cache.h>
/*****************************************************************************/

#define ATTR_READ_ONLY  0x01
#define ATTR_HIDDEN     0x02
#define ATTR_SYSTEM     0x04
#define ATTR_VOLUME_ID  0x08
#define ATTR_DIRECTORY  0x10
#define ATTR_ARCHIVE    0x20

#define OFFSET_DE_FILENAME            0
#define OFFSET_DE_ATTRIBUTE          11
#define OFFSET_DE_NTRESERVED         12
#define OFFSET_DE_CRTIMETNT          13
#define OFFSET_DE_CREATETIME         14
#define OFFSET_DE_CREATEDATE         16
#define OFFSET_DE_LASTACCESSDATE     18
#define OFFSET_DE_FIRSTCLUSTERHIGH   20
#define OFFSET_DE_WRITETIME          22
#define OFFSET_DE_WRITEDATE          24
#define OFFSET_DE_FIRSTCLUSTERLOW    26
#define OFFSET_DE_FILESIZE           28

#define DIRFIND_FILE 0
#define DIRFIND_FREE 1

void dir_getFileStructure(FileSystem *fs,FileRecord *filerec,FileLocation *loc);
void dir_createDirectoryEntry(FileSystem *fs,FileRecord *filerec,FileLocation *loc);
void dir_createDefaultEntry(FileSystem *fs,FileRecord *filerec,eint8* fatfilename);
void dir_setFirstCluster(FileSystem *fs,FileLocation *loc,euint32 cluster_addr);
void dir_setFileSize(FileSystem *fs,FileLocation *loc,euint32 numbytes);
euint32 dir_findinRoot(FileSystem *fs,eint8 * fatname, FileLocation *loc);
euint32 dir_findinDir(FileSystem *fs, eint8 * fatname, euint32 startCluster, FileLocation *loc, euint8 mode);
euint32 dir_findinBuf(euint8 *buf,eint8 *fatname, FileLocation *loc, euint8 mode);
euint32 dir_findinCluster(FileSystem *fs,euint32 cluster,eint8 *fatname, FileLocation *loc, euint8 mode);
euint32 dir_findinRootArea(FileSystem *fs,eint8* fatname, FileLocation *loc, euint8 mode);
esint8 dir_getFatFileName(eint8* filename, eint8* fatfilename);
esint8 dir_updateDirectoryEntry(FileSystem *fs,FileRecord *entry,FileLocation *loc);
esint8 dir_addCluster(FileSystem *fs,euint32 firstCluster);
#endif
