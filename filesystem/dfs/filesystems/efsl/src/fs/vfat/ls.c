/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : ls.c                                                             *
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

/*****************************************************************************/
#include <dfs_fs.h>

#include "ls.h"
/*****************************************************************************/

esint8 ls_openDir(DirList *dlist,FileSystem *fs,eint8* dirname)
{
	FileLocation loc;
	euint32 fc;
	esint8 result;
	
	dlist->fs=fs;

	result = fs_findFile(dlist->fs,dirname,&loc,&fc);
	
	if(result == 2)
	{
		fs_initClusterChain(dlist->fs,&(dlist->Cache),fc);
		memClr(&(dlist->currentEntry),sizeof(dlist->currentEntry));
		dlist->rEntry=0;
		dlist->cEntry=0xFFFF;
			
		return(0);
	}
	else if(result == 1)
		dfs_log(DFS_DEBUG_INFO, ("%s is not a directory", dirname));
	else	
		dfs_log(DFS_DEBUG_INFO, ("can't find %s", dirname));
	
	return (-1);
}
/*****************************************************************************/

esint8 ls_getDirEntry(DirList *dlist)
{
	if(dlist->Cache.FirstCluster == 1){
		return(ls_getRootAreaEntry(dlist));
	}else if(dlist->Cache.FirstCluster){
		return(ls_getRealDirEntry(dlist));
	}
	return(-1);
}
/*****************************************************************************/

esint8 ls_getNext(DirList *dlist)
{
	do{
		if(ls_getDirEntry(dlist))return(-1);
		dlist->rEntry++;
	}while(!ls_isValidFileEntry(&(dlist->currentEntry)));
	dlist->cEntry++;
	return(0);
}
/*****************************************************************************/

esint8 ls_getRealDirEntry(DirList *dlist)
{
	euint8* buf;
	
	if(dlist->Cache.FirstCluster<=1)return(-1);
	
	if(fat_LogicToDiscCluster(dlist->fs,
						   &(dlist->Cache),
						   (dlist->rEntry)/(16 * dlist->fs->volumeId.SectorsPerCluster))){
		return(-1);
	}
	
	buf = part_getSect(dlist->fs->part,
					   fs_clusterToSector(dlist->fs,dlist->Cache.DiscCluster) + (dlist->rEntry/16)%dlist->fs->volumeId.SectorsPerCluster,
				       IOM_MODE_READONLY);
	
	/*memCpy(buf+(dlist->rEntry%16)*32,&(dlist->currentEntry),32);*/
	ls_fileEntryToDirListEntry(dlist,buf,32*(dlist->rEntry%16));
	
	part_relSect(dlist->fs->part,buf);
	
	return(0);
}
/*****************************************************************************/

esint8 ls_getRootAreaEntry(DirList *dlist)
{
	euint8 *buf=0;
	
	if((dlist->fs->type != FAT12) && (dlist->fs->type != FAT16))return(-1);
	if(dlist->rEntry>=dlist->fs->volumeId.RootEntryCount)return(-1);
	
	buf = part_getSect(dlist->fs->part,
					   dlist->fs->FirstSectorRootDir+dlist->rEntry/16,
					   IOM_MODE_READONLY);
	/*memCpy(buf+32*(dlist->rEntry%16),&(dlist->currentEntry),32);*/
	ls_fileEntryToDirListEntry(dlist,buf,32*(dlist->rEntry%16));
	part_relSect(dlist->fs->part,buf);
	return(0);
}
/*****************************************************************************/

esint8 ls_isValidFileEntry(ListDirEntry *entry)
{
	if(entry->FileName[0] == 0 || entry->FileName[0] == 0xE5 || entry->FileName[0] == '.')return(0);
	if((entry->Attribute&0x0F)==0x0F)return(0);
 	return(1);
}
/*****************************************************************************/

void ls_fileEntryToDirListEntry(DirList *dlist, euint8* buf, euint16 offset)
{
	if(offset>480 || offset%32)return;
	
	buf+=offset;
	memCpy(buf+OFFSET_DE_FILENAME,dlist->currentEntry.FileName,LIST_MAXLENFILENAME);
	dlist->currentEntry.Attribute = *(buf+OFFSET_DE_ATTRIBUTE);
	dlist->currentEntry.FileSize = ex_getb32(buf+OFFSET_DE_FILESIZE);
}
/*****************************************************************************/

