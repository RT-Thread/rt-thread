/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : fs.c                                                             *
* Release  : 0.3 - devel                                                      *
* Description : These are general filesystem functions, supported by the      *
*               functions of dir.c and fat.c  file.c uses these functions     *
*               heavily, but is not used by fs.c (not true anymore)           *
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
#include "fs.h"
#include "fat.h"
#include "dir.h"
/*****************************************************************************/

/* ****************************************************************************  
 * eint16 fs_initFs(FileSystem *fs,Partition *part)
 * Description: This functions glues the initialisation of the filesystem together.
 * It loads the volumeID, computes the FS type and searches for the rootsector.
 * Return value: Returns 0 on succes and -1 on error (if magic code is wrong)
*/
eint16 fs_initFs(FileSystem *fs,Partition *part)
{
	if(!fs_isValidFat(part)){
		return(-1);
	}
	fs->part=part;
	fs_loadVolumeId(fs,part);
	if(!fs_verifySanity(fs))return(-2);
  	fs_countDataSectors(fs);
	fs_determineFatType(fs);
	fs_findFirstSectorRootDir(fs);
	fs_initCurrentDir(fs); 

	return(0);
}
/*****************************************************************************/ 

/* ****************************************************************************  
 * eint16 fs_isValidFat(Partition *part)
 * Description: This functions loads the volumeID and checks if the magic
 * value is present.
 * Return value: returns 0 when magic code is missing, 1 if it is there.
*/
eint16 fs_isValidFat(Partition *part)
{
	euint8 *buf;
	
	buf=part_getSect(part,0,IOM_MODE_READONLY|IOM_MODE_EXP_REQ); /* Load Volume label */
	if( ex_getb16(buf+0x1FE) != 0xAA55 ){
		return (0);
	}
	part_relSect(part,buf);
	return(1);
}
/*****************************************************************************/ 

/* ****************************************************************************  
 * void fs_loadVolumeId(FileSystem *fs, Partition *part)
 * Description: This function loads all relevant fields from the volumeid.
*/
void fs_loadVolumeId(FileSystem *fs, Partition *part)
{
	euint8 *buf;
	
	buf=part_getSect(part,0,IOM_MODE_READONLY|IOM_MODE_EXP_REQ);
	
	fs->volumeId.BytesPerSector=ex_getb16(buf+0x0B);
	fs->volumeId.SectorsPerCluster=*((eint8*)(buf+0x0D));
	fs->volumeId.ReservedSectorCount=ex_getb16(buf+0x0E);
	fs->volumeId.NumberOfFats=*((eint8*)(buf+0x10));
	fs->volumeId.RootEntryCount=ex_getb16(buf+0x11);
	fs->volumeId.SectorCount16=ex_getb16(buf+0x13);
	fs->volumeId.FatSectorCount16=ex_getb16(buf+0x16);
	fs->volumeId.SectorCount32=ex_getb32(buf+0x20);
	fs->volumeId.FatSectorCount32=ex_getb32(buf+0x24);
	fs->volumeId.RootCluster=ex_getb32(buf+0x2C);
	
	part_relSect(part,buf);
	
}
/*****************************************************************************/ 

/* ****************************************************************************  
 * esint16 fs_verifySanity(FileSystem *fs)
 * Description: Does some sanity calculations.
 * Return value: 1 on success, 0 when discrepancies were found.
*/
esint16 fs_verifySanity(FileSystem *fs)
{
	esint16 sane=1; /* Sane until proven otherwise */
	/* First check, BPS, we only support 512 */
	if(fs->volumeId.BytesPerSector!=512)sane=0;
	/* Check is SPC is valid (multiple of 2, and clustersize >=32KB */
	if(!((fs->volumeId.SectorsPerCluster == 1 ) |
	     (fs->volumeId.SectorsPerCluster == 2 ) |
	     (fs->volumeId.SectorsPerCluster == 4 ) |
	     (fs->volumeId.SectorsPerCluster == 8 ) |
	     (fs->volumeId.SectorsPerCluster == 16) |
	     (fs->volumeId.SectorsPerCluster == 32) |
	     (fs->volumeId.SectorsPerCluster == 64) ))sane=0;
	/* Any number of FAT's should be supported... (untested) */
	/* There should be at least 1 reserved sector */
	if(fs->volumeId.ReservedSectorCount==0)sane=0;

	return(sane);
}
/*****************************************************************************/

/* ****************************************************************************  
 * void fs_countDataSectors(FileSystem *fs)
 * Description: This functions calculates the sectorcounts, fatsectorcounts and
 * dataclustercounts. It fills in the general fields.
*/
void fs_countDataSectors(FileSystem *fs)
{
  euint32 rootDirSectors,dataSectorCount;

  rootDirSectors=((fs->volumeId.RootEntryCount*32) +
                 (fs->volumeId.BytesPerSector - 1)) /
                 fs->volumeId.BytesPerSector;

  if(fs->volumeId.FatSectorCount16 != 0)
  {
    fs->FatSectorCount=fs->volumeId.FatSectorCount16;
    fs->volumeId.FatSectorCount32=0;
  }
  else
  {
    fs->FatSectorCount=fs->volumeId.FatSectorCount32;
    fs->volumeId.FatSectorCount16=0;
  }

  if(fs->volumeId.SectorCount16!=0)
  {
    fs->SectorCount=fs->volumeId.SectorCount16;
    fs->volumeId.SectorCount32=0;
  }
  else
  {
    fs->SectorCount=fs->volumeId.SectorCount32;
    fs->volumeId.SectorCount16=0;
  }

  dataSectorCount=fs->SectorCount - (
                  fs->volumeId.ReservedSectorCount +
                  (fs->volumeId.NumberOfFats * fs->FatSectorCount) +
                  rootDirSectors);

  fs->DataClusterCount=dataSectorCount/fs->volumeId.SectorsPerCluster;
}
/*****************************************************************************/ 

/* ****************************************************************************  
 * void fs_determineFatType(FileSystem *fs)
 * Description: This function looks af the Dataclustercount and determines the
 * FAT type. It fills in fs->type.
*/
void fs_determineFatType(FileSystem *fs)
{
	if(fs->DataClusterCount < 4085)
	{
		fs->type=FAT12;
		fs->volumeId.RootCluster=0;
	}
	else if(fs->DataClusterCount < 65525)
	{
		fs->type=FAT16;
		fs->volumeId.RootCluster=0;
	}
	else
	{
		fs->type=FAT32;
	}
}
/*****************************************************************************/ 

/* ****************************************************************************  
 * void fs_findFirstSectorRootDir(FileSystem *fs)
 * Description: This functions fills in the fs->FirstSectorRootDir field, even
 * for FAT32, although that is not necessary (because you have FirstClusterRootDir).
*/
void fs_findFirstSectorRootDir(FileSystem *fs)
{
	if(fs->type==FAT32)
		fs->FirstSectorRootDir = fs->volumeId.ReservedSectorCount + 
		                         (fs->volumeId.NumberOfFats*fs->volumeId.FatSectorCount32) +
								 (fs->volumeId.RootCluster-2)*fs->volumeId.SectorsPerCluster;
	else
		fs->FirstSectorRootDir = fs->volumeId.ReservedSectorCount + 
		                         (fs->volumeId.NumberOfFats*fs->volumeId.FatSectorCount16);
}
/*****************************************************************************/ 

void fs_initCurrentDir(FileSystem *fs)
{
	fs->FirstClusterCurrentDir = fs_getFirstClusterRootDir(fs);
}
/*****************************************************************************/

/* ****************************************************************************  
 * long fs_clusterToSector(FileSystem *fs,euint32 cluster)
 * Description: This function converts a clusternumber in the effective sector
 * number where this cluster starts. Boundary check is not implemented
 * Return value: A long is returned representing the sectornumber.
*/
euint32 fs_clusterToSector(FileSystem *fs,euint32 cluster)
{
	eint32 base;
	
	if(fs->type==FAT32)
	{
		base=
			fs->volumeId.ReservedSectorCount+
			fs->FatSectorCount*fs->volumeId.NumberOfFats;
	}
	else
	{
		base=
			fs->volumeId.ReservedSectorCount+
			fs->FatSectorCount*fs->volumeId.NumberOfFats+
			fs->volumeId.RootEntryCount/16;
	}
	return( base + (cluster-2)*fs->volumeId.SectorsPerCluster );
}
/*****************************************************************************/ 

/* Function is unused, but may be usefull */
euint32 fs_sectorToCluster(FileSystem *fs,euint32 sector)
{
	eint32 base;
	
	if(fs->type==FAT32)
	{
		base=
			fs->volumeId.ReservedSectorCount+
			fs->FatSectorCount*fs->volumeId.NumberOfFats;
	}
	else
	{
		base=
			fs->volumeId.ReservedSectorCount+
			fs->FatSectorCount*fs->volumeId.NumberOfFats+
			fs->volumeId.RootEntryCount/16;
	}
	return(((sector-base)-((sector-base)%fs->volumeId.SectorsPerCluster))/fs->volumeId.SectorsPerCluster+2 );
}
/*****************************************************************************/

/* ****************************************************************************  
 * euint32 fs_getNextFreeCluster(FileSystem *fs,euint32 startingcluster)
 * Description: This functions searches for a free cluster, starting it's search at
 * cluster startingcluster. This allow to speed up searches and try to avoid 
 * fragmentation. Implementing rollover search is still to be done.
 * Return value: If a free cluster is found it's number is returned. If none is 
 * found 0 is returned.
*/
euint32 fs_getNextFreeCluster(FileSystem *fs,euint32 startingcluster)
{
	euint32 r;
	
	while(startingcluster<fs->DataClusterCount){
		r=fat_getNextClusterAddress(fs,startingcluster,0);
		if(r==0){
			return(startingcluster);
		}
		startingcluster++;
	}
	return(0);
}
/*****************************************************************************/ 

/* ****************************************************************************  
 * euint32 fs_giveFreeClusterHint(FileSystem *fs)
 * 
 * Description: This function should return a clusternumber that is free or
 * lies close before free clusters. The result MUST be checked to see if 
 * it is free! Implementationhint: search the largest clusternumber in the
 * files in the rootdirectory.
 * 
 * Return value: Returns it's best guess.
*/
euint32 fs_giveFreeClusterHint(FileSystem *fs)
{
	return(2); /* Now THIS is a hint ;) */
}
/*****************************************************************************/ 

/* ****************************************************************************
 * esint8 fs_findFile(FileSystem *fs,eint8* filename,FileLocation *loc,euint32 *lastDir)
 *
 * Description: This function looks if the given filename is on the given fs
 * and, if found, fills in its location in loc.
 * The function will first check if the pathname starts with a slash. If so it will
 * set the starting directory to the rootdirectory. Else, it will take the firstcluster-
 * currentdir (That you can change with chdir()) as startingpoint.
 * The lastdir pointer will be the first cluster of the last directory fs_findfile
 * enters. It starts out at the root/current dir and then traverses the path along with
 * fs_findFile. 
 * It is set to 0 in case of errors (like dir/dir/dir/file/dir/dir...)
 * Return value: Returns 0 when nothing was found, 1 when the thing found
 * was a file and 2 if the thing found was a directory.
*/

esint8 fs_findFile(FileSystem *fs,eint8* filename,FileLocation *loc,euint32 *lastDir)
{
	euint32 fccd,tmpclus;
	eint8 ffname[11],*next,it=0,filefound=0;
	
	if(*filename=='/'){
		fccd = fs_getFirstClusterRootDir(fs);
		filename++;
		if(!*filename){
			if(lastDir)*lastDir=fccd;
			return(2);
		}
	}else{
		fccd = fs->FirstClusterCurrentDir;
	}
	
	if(lastDir)*lastDir=fccd;
	
	while((next=file_normalToFatName(filename,ffname))!=0){
		if((tmpclus=dir_findinDir(fs,ffname,fccd,loc,DIRFIND_FILE))==0)return(0);
		it++;
		if(loc->attrib&ATTR_DIRECTORY){
			fccd = tmpclus;
			filename = next;
			if(lastDir)*lastDir=fccd;
			if(filefound)*lastDir=0;
		}else{
			filefound=1;
			if((file_normalToFatName(next,ffname))!=0){
				return(0);
			}else{
				filename=next;	
			}
		}
	}
	
	if(it==0)return(0);
	if(loc->attrib&ATTR_DIRECTORY || !filefound)return(2);
	return(1);
}
/*****************************************************************************/

esint16 fs_findFreeFile(FileSystem *fs,eint8* filename,FileLocation *loc,euint8 mode)
{
	euint32 targetdir=0;
	eint8 ffname[11];
	
	if(fs_findFile(fs,filename,loc,&targetdir))return(0);
	if(!dir_getFatFileName(filename,ffname))return(0);
	if(dir_findinDir(fs,ffname,targetdir,loc,DIRFIND_FREE)){
		return(1);
	}else{
		if(dir_addCluster(fs,targetdir)){
			return(0);
		}else{
			if(dir_findinDir(fs,ffname,targetdir,loc,DIRFIND_FREE)){
				return(1);
			}
		}
	}
		
	return(0);
}
/*****************************************************************************/

/* ****************************************************************************  
 * euint32 fs_getLastCluster(FileSystem *fs,ClusterChain *Cache)
 * Description: This function searches the last cluster of a chain.
 * Return value: The LastCluster (also stored in cache);
*/
euint32 fs_getLastCluster(FileSystem *fs,ClusterChain *Cache)
{
	if(Cache->DiscCluster==0){
		Cache->DiscCluster=Cache->FirstCluster;
		Cache->LogicCluster=0;
	}
	
	if(Cache->LastCluster==0)
	{
		while(fat_getNextClusterChain(fs, Cache)==0)
		{
			Cache->LogicCluster+=Cache->Linear;
			Cache->DiscCluster+=Cache->Linear;
			Cache->Linear=0;
		}
	}
	return(Cache->LastCluster);
}
/*****************************************************************************/

euint32 fs_getFirstClusterRootDir(FileSystem *fs)
{
	if (fs->type == FAT32) 
		return fs->volumeId.RootCluster;
	
	return 1;
}
/*****************************************************************************/

void fs_initClusterChain(FileSystem *fs,ClusterChain *cache,euint32 cluster_addr)
{
	cache->FirstCluster=cluster_addr;
	cache->DiscCluster=cluster_addr;
	cache->LogicCluster=0;
	cache->LastCluster=0; /* Warning flag here */
	cache->Linear=0;
}
/*****************************************************************************/

void fs_setFirstClusterInDirEntry(FileRecord *rec,euint32 cluster_addr)
{
	rec->FirstClusterHigh=cluster_addr>>16;
	rec->FirstClusterLow=cluster_addr&0xFFFF;
}
/*****************************************************************************/

esint8 fs_flushFs(FileSystem *fs)
{
	return(part_flushPart(fs->part,0,fs->SectorCount));
}
/*****************************************************************************/

esint8 fs_umount(FileSystem *fs)
{
	return(fs_flushFs(fs));
}
/*****************************************************************************/

esint8 fs_clearCluster(FileSystem *fs,euint32 cluster)
{
	euint16 c;
	euint8* buf;
	
	for(c=0;c<(fs->volumeId.SectorsPerCluster);c++){
		buf = part_getSect(fs->part,fs_clusterToSector(fs,cluster)+c,IOM_MODE_READWRITE);
		memClr(buf,512);
		part_relSect(fs->part,buf);
	}
	return(0);
}

esint8 fs_getFsInfo(FileSystem *fs)
{
	euint8 *buf;
		
 	if(!fs->type==FAT32)return(0);
	buf = part_getSect(fs->part,FS_INFO_SECTOR,IOM_MODE_READONLY);
	if(ex_getb32(buf+0)!=FSINFO_MAGIC_BEGIN || ex_getb32(buf+508)!=FSINFO_MAGIC_END){
		part_relSect(fs->part,buf);
		return(-1);
	}
	fs->FreeClusterCount = ex_getb32(buf+488);
	fs->NextFreeCluster  = ex_getb32(buf+492);
	part_relSect(fs->part,buf);
	return(0);
}

esint8 fs_setFsInfo(FileSystem *fs)
{
	euint8* buf;

	if(!fs->type==FAT32)return(0);
	buf = part_getSect(fs->part,FS_INFO_SECTOR,IOM_MODE_READWRITE);
	if(ex_getb32(buf+0)!=FSINFO_MAGIC_BEGIN || ex_getb32(buf+508)!=FSINFO_MAGIC_END){
		part_relSect(fs->part,buf);
		return(-1);
	}
	ex_setb32(buf+488,fs->FreeClusterCount);
	ex_setb32(buf+492,fs->NextFreeCluster);
	part_relSect(fs->part,buf);
	return(0);
}

