/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : file.h                                                           *
* Release  : 0.3 - devel                                                      *
* Description : This file contains functions dealing with files such as:      *
*               fopen, fread and fwrite.                                      *
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

#ifndef __FILE_H_
#define __FILE_H_

/*****************************************************************************/
#include "config.h"
#include "error.h"
#include "tm.h"
#include "fs.h"
#include "dir.h"
#include "plibc.h"
#include "debug.h"
#include "types.h"
#include "fat.h"
/*****************************************************************************/

/* Operation flags */
#define EFSL_O_RDONLY		0
#define EFSL_O_WRONLY		1
#define EFSL_O_RDWR			2
#define EFSL_O_APPEND		8

#define FILE_STATUS_OPEN 0
#define FILE_STATUS_WRITE 1

/*****************************************************************************\
 *                              File                                         
 *                             ------                                        
 * FileRecord		DirEntry		Copy of the FileRecord for this file         
 * FileLocation	Location		Location of the direntry
 * FileSystem		*fs				Pointer to the filesystem this file is on    
 * FileCache		Cache			Pointer to the cache object of the file   
 * euint8			FileStatus		Contains bitfield regarding filestatus   
 * euint32			FilePtr			Offsetpointer for fread/fwrite functions
 * euint32 		FileSize		Working copy of the filesize, always use this,
 									it is more up to date than DirEntry->FileSize,
									which is only updated when flushing to disc.
\*****************************************************************************/
struct _File{
	FileRecord DirEntry;
	FileLocation Location; /* Location in directory!! */
	FileSystem *fs;
	ClusterChain Cache;
	euint8	FileStatus;
	euint32 FilePtr;
	euint32 FileSize;
	euint32 ref_count; /* Descriptor reference count */	
};
typedef struct _File File;


esint8 file_fopen(File *file, FileSystem *fs,eint8 *filename, eint32 mode);
esint8 file_fclose(File *file);
esint32 file_setpos(File *file,euint32 pos);
euint32 file_fread(File *file,euint32 offset, euint32 size,euint8 *buf);
euint32 file_read (File *file,euint32 size,euint8 *buf);
euint32 file_fwrite(File* file,euint32 offset,euint32 size,euint8* buf);
euint32 file_write (File* file,euint32 size,euint8* buf); 
eint8* file_normalToFatName(eint8* filename,eint8* fatfilename);
euint8 file_validateChar(euint8 c);
void file_initFile(File *file, FileSystem *fs, FileLocation *loc);
eint16 file_allocClusterChain(File *file,euint32 num_clusters);
void file_setAttr(File* file,euint8 attribute,euint8 val);
euint8 file_getAttr(File* file,euint8 attribute);
euint32 file_requiredCluster(File *file,euint32 offset, euint32 size);

#endif
