/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : ui.c                                                             *
* Release  : 0.3 - devel                                                      *
* Description : This file contains functions which will be presented to the   *
*               user of this library.                                         *
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
#include "ui.h"
#include "ls.h"
#include "efs.h"
/*****************************************************************************/

/* ****************************************************************************  
* unlink dir or file@yi.qiu,2008-08-19 
*/
esint16 un_link(FileSystem *fs,euint8* filename)
{
	FileLocation loc;
	ClusterChain cache;
	DirList *dlist;	
	euint8* buf;
	euint8 attr;
	euint32 firstCluster=0;
	euint32 fc;

	if ( filename[0] == '/' && filename[1] == '\0')
	{
		/* it's the root directory */
		dfs_log(DFS_DEBUG_INFO, ("Can't delete root directory"));
		return -DFS_STATUS_EISDIR;
	}
	
	if((fs_findFile(fs,(eint8*)filename,&loc,&fc)) > 0)
	{
		buf = part_getSect(fs->part,loc.Sector,IOM_MODE_READWRITE);
		firstCluster = ex_getb16(buf+loc.Offset*32+20);
		firstCluster <<= 16;
		firstCluster += ex_getb16(buf+loc.Offset*32+26);
		attr = ex_getb16(buf+loc.Offset*32+11);
		if(attr == ATTR_DIRECTORY)
		{
			dlist = (DirList *)rt_malloc(sizeof(DirList));
			if(dlist == RT_NULL)
			{
				part_relSect(fs->part,buf);
				
				dfs_log(DFS_DEBUG_INFO, ("Memory alloc failed"));				
				return -DFS_STATUS_ENOMEM;	
			}
			
			if(firstCluster != 0)
			{
				dlist->fs = fs;
				fs_initClusterChain(fs,&(dlist->Cache),fc);
				memClr(&(dlist->currentEntry),sizeof(dlist->currentEntry));
				dlist->rEntry = 0;
				dlist->cEntry = 0xFFFF;

				while(1)
				{
					/* it's the end of file */
					if(ls_getNext(dlist) == 0) 
					{
						/* '.' and '..' */
						if(dlist->currentEntry.FileName[0] == '.') continue;
						
						part_relSect(fs->part,buf);
						
						dfs_log(DFS_DEBUG_INFO, ("Directory not empty"));
						return -DFS_STATUS_ENOTEMPTY;
					}
					else break;
				}
			}
		}

		memClr(buf+(loc.Offset*32),32);
		part_relSect(fs->part,buf);
		cache.DiscCluster = cache.LastCluster = cache.Linear = cache.LogicCluster = 0;
		cache.FirstCluster = firstCluster;
 		fat_unlinkClusterChain(fs,&cache);
		
		return 0;
	}
	return -DFS_STATUS_ENOENT;
}

/*****************************************************************************/
esint8 mk_dir(FileSystem *fs,eint8* dirname)
{
	FileLocation loc;
	FileRecord direntry;
	euint32 nc,parentdir;
	euint8* buf;
	eint8 ffname[11];
	
	if( fs_findFile(fs,dirname,&loc,&parentdir) )
	{
		dfs_log(DFS_DEBUG_INFO, ("directory %s has existed", dirname));		
		return(-1);
	}
	if(parentdir==0)
	{
		dfs_log(DFS_DEBUG_INFO, ("parent directory doesn't existe"));
		return(-2);
	}	
	
	if(!fs_findFreeFile(fs,dirname,&loc,0))
	{
		dfs_log(DFS_DEBUG_INFO, ("can't find free entry"));
		return(-3);
	}	
	
	/* You may never search for a free cluster, and the call
	 * functions that may cause changes to the FAT table, that
	 * is why getNextFreeCluster has to be called AFTER calling
	 * fs_findFreeFile, which may have to expand a directory in
	 * order to store the new filerecord !! 
	 */
	
	nc = fs_getNextFreeCluster(fs,fs_giveFreeClusterHint(fs));
	if(nc==0)
	{
		dfs_log(DFS_DEBUG_INFO, ("no free cluster"));		
		return(0);
	}
	
	fs_clearCluster(fs,nc);
	
	buf = part_getSect(fs->part,loc.Sector,IOM_MODE_READWRITE);

	dir_getFatFileName(dirname,ffname);
	memClr(&direntry,sizeof(direntry));
	memCpy(ffname,&direntry,11);
	direntry.FileSize = 0;
	direntry.FirstClusterHigh=nc>>16;
	direntry.FirstClusterLow=nc&0xFFFF;
	direntry.Attribute = ATTR_DIRECTORY;
	memCpy(&direntry,buf+(32*loc.Offset),32);
		
	part_relSect(fs->part,buf);
	
	buf = part_getSect(fs->part,fs_clusterToSector(fs,nc),IOM_MODE_READWRITE);
	
	memClr(&direntry,sizeof(direntry));
	memCpy(".          ",&direntry,11);
	direntry.Attribute = ATTR_DIRECTORY;
	direntry.FileSize = 0;
	direntry.FirstClusterHigh=nc>>16;
	direntry.FirstClusterLow=nc&0xFFFF;
	memCpy(&direntry,buf,32);
	
	if(fs->type == FAT32 && parentdir == fs->volumeId.RootCluster)
		parentdir = 0;
	
	if(fs->type != FAT32 && parentdir<=1)
		parentdir = 0;
	
	memClr(&direntry,sizeof(direntry));
	memCpy("..         ",&direntry,11);
	direntry.Attribute = ATTR_DIRECTORY;
	direntry.FileSize = 0;
	direntry.FirstClusterHigh=parentdir>>16;
	direntry.FirstClusterLow=parentdir&0xFFFF;
	memCpy(&direntry,buf+32,32);

	part_relSect(fs->part,buf);
	
	fat_setNextClusterAddress(fs,nc,fat_giveEocMarker(fs));

	return(0);
}
