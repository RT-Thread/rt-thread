/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : fat.c                                                            *
* Release  : 0.3 - devel                                                      *
* Description : This file contains all the functions dealing with the FAT     *
*               in a Microsoft FAT filesystem. It belongs under fs.c          *
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
/*****************************************************************************/

/* ****************************************************************************  
 * unsigned long fat_getSectorAddressFatEntry(FileSystem *fs,unsigned long cluster_addr)
 * Description: Returns the sectornumber that holds the fat entry for cluster cluster_addr.
 * This works for all FAT types.
 * Return value: Sectornumber, or 0. Warning, no boundary check.
*/
euint32 fat_getSectorAddressFatEntry(FileSystem *fs,euint32 cluster_addr)
{ 
	euint32 base = fs->volumeId.ReservedSectorCount,res;
	
	switch(fs->type){
		case FAT12:
			res=(cluster_addr*3/1024);
			if(res>=fs->FatSectorCount){
				return(0);
			}else{
				return(base+res);
			}
			break;
		case FAT16:
			res=cluster_addr/256;
			if(res>=fs->FatSectorCount){
				return(0);
			}else{
				return(base+res);
			}
			break;
		case FAT32:
			res=cluster_addr/128;
			if(res>=fs->FatSectorCount){
				return(0);
			}else{
				return(base+res);
			}
			break; 
	}
	return(0);
}
/*****************************************************************************/ 


/* ****************************************************************************  
 * unsigned long fat_getNextClusterAddress(FileSystem *fs,unsigned long cluster_addr
 * Description: This function loads the sector of the fat which contains the entry
 * for cluster_addr. It then fetches and (if required) calculates it's value.
 * This value is the EoC marker -or- the number of the next cluster in the chain.
 * Return value: Clusternumber or EoC
*/
euint32 fat_getNextClusterAddress(FileSystem *fs,euint32 cluster_addr,euint16 *linear)
{
	euint8 *buf; 
	euint8 hb,lb;
	euint16 offset;
	euint32 sector;
	euint32 nextcluster=0;
	
	sector=fat_getSectorAddressFatEntry(fs,cluster_addr);
	if( (fs->FatSectorCount <= (sector-fs->volumeId.ReservedSectorCount)) || sector==0 )
	{
		return(0);
	}
	
	buf=part_getSect(fs->part,sector,IOM_MODE_READONLY);
		
	switch(fs->type)
	{
		case FAT12:
			offset = ((cluster_addr%1024)*3/2)%512;
			hb = buf[offset];
			if(offset == 511){
				part_relSect(fs->part,buf);
				buf=part_getSect(fs->part,sector+1,IOM_MODE_READONLY);
				lb = buf[0];
			}else{
				lb = buf[offset + 1];
			}
			if(cluster_addr%2==0){
				nextcluster = ( ((lb&0x0F)<<8) + (hb) );
			}else{
				nextcluster = ( (lb<<4) + (hb>>4) );
			}
			break;
		case FAT16:
			offset=cluster_addr%256;
			nextcluster = *((euint16 *)buf + offset);
			break;
		case FAT32:
			offset=cluster_addr%128;
			nextcluster = *((euint32 *)buf + offset);
			break;
	}
	
	part_relSect(fs->part,buf);
	
	return(nextcluster);
}
/*****************************************************************************/ 


/* ****************************************************************************  
 * void fat_setNextClusterAddress(FileSystem *fs,unsigned long cluster_addr,unsigned long next_cluster_addr)
 * Description: This function makes an entry in the fattable for cluster_addr. The value it puts there
 * is next_cluster_addr. 
*/
void fat_setNextClusterAddress(FileSystem *fs,euint32 cluster_addr,euint32 next_cluster_addr)
{
	euint8 *buf,*buf2; 
	euint16 offset;
	euint32 sector;
	
	sector=fat_getSectorAddressFatEntry(fs,cluster_addr);
	if(fs->FatSectorCount<sector){
		DBG((TXT("HARDERROR:::fat_getNextClusterAddress READ PAST FAT BOUNDARY\n")));
		return;
	}
	
	buf=part_getSect(fs->part,sector,IOM_MODE_READWRITE);
		
	switch(fs->type){
		case FAT12:
			offset = ((cluster_addr%1024)*3/2)%512;
			if(offset == 511){
				if(cluster_addr%2==0){
					buf[offset]=next_cluster_addr&0xFF;
				}else{
					buf[offset]=(buf[offset]&0xF)+((next_cluster_addr<<4)&0xF0);
				}
				buf2=part_getSect(fs->part,fat_getSectorAddressFatEntry(fs,cluster_addr)+1,IOM_MODE_READWRITE);
				if(cluster_addr%2==0){
					buf2[0]=(buf2[0]&0xF0)+((next_cluster_addr>>8)&0xF);
				}else{
					buf2[0]=(next_cluster_addr>>4)&0xFF;
				}
				part_relSect(fs->part,buf2);
			}else{
				if(cluster_addr%2==0){
					buf[offset]=next_cluster_addr&0xFF;
					buf[offset+1]=(buf[offset+1]&0xF0)+((next_cluster_addr>>8)&0xF);
				}else{
					buf[offset]=(buf[offset]&0xF)+((next_cluster_addr<<4)&0xF0);
					buf[offset+1]=(next_cluster_addr>>4)&0xFF;
				}
			}
			part_relSect(fs->part,buf);
			break;
		case FAT16:
			offset=cluster_addr%256;
			*((euint16*)buf+offset)=next_cluster_addr;
			part_relSect(fs->part,buf);
			break;
		case FAT32:
			offset=cluster_addr%128;
			*((euint32*)buf+offset)=next_cluster_addr;
			part_relSect(fs->part,buf);
			break;
	}
	
}
/*****************************************************************************/ 


/* ****************************************************************************  
 * short fat_isEocMarker(FileSystem *fs,unsigned long fat_entry)
 * Description: Checks if a certain value is the EoC marker for the filesystem
 * noted in fs->type.
 * Return value: Returns 0 when it is the EoC marker, and 1 otherwise.
*/
eint16 fat_isEocMarker(FileSystem *fs,euint32 fat_entry)
{
	switch(fs->type){
		case FAT12:
			if(fat_entry<0xFF8){
				return(0);
			}
			break;
		case FAT16:
			if(fat_entry<0xFFF8){
				return(0);
			}
			break;
		case FAT32:
			if((fat_entry&0x0FFFFFFF)<0xFFFFFF8){
				return(0);
			}
			break;
	}
	return(1);
}
/*****************************************************************************/ 


/* ****************************************************************************  
 * unsigned long fat_giveEocMarker(FileSystem *fs)
 * Description: Returns an EoC markernumber valid for the filesystem noted in
 * fs->type.
 * Note, for FAT32, the upper 4 bits are set to zero, although they should be un
 * touched according to MicroSoft specifications. I didn't care.
 * Return value: The EoC marker cast to an ulong.
*/
euint32 fat_giveEocMarker(FileSystem *fs)
{
	switch(fs->type)
	{
		case FAT12:
			return(0xFFF);
			break;
		case FAT16:
			return(0xFFFF);
			break;
		case FAT32:
			return(0x0FFFFFFF);
			break;
	}
	return(0);
}
/*****************************************************************************/ 

/* ****************************************************************************  
 * euint32 fat_getNextClusterAddressWBuf(FileSystem *fs,euint32 cluster_addr, euint8* buf)
 * Description: This function retrieves the contents of a FAT field. It does not fetch
 * it's own buffer, it is given as a parameter. (ioman makes this function rather obsolete)
 * Only in the case of a FAT12 crosssector data entry a sector is retrieved here.
 * Return value: The value of the clusterfield is returned.
*/
euint32 fat_getNextClusterAddressWBuf(FileSystem *fs,euint32 cluster_addr, euint8* buf)
{
	euint8  *buf2; /* For FAT12 fallover only */
	euint8 hb,lb;
	euint16 offset;
	euint32 nextcluster=0;
	
	switch(fs->type)
	{
		case FAT12:
			offset = ((cluster_addr%1024)*3/2)%512;
			hb = buf[offset];
			if(offset == 511){
				buf2=part_getSect(fs->part,fat_getSectorAddressFatEntry(fs,cluster_addr)+1,IOM_MODE_READONLY);
				lb = buf2[0];
				part_relSect(fs->part,buf2);
			}else{
				lb = buf[offset + 1];
			}
			if(cluster_addr%2==0){
				nextcluster = ( ((lb&0x0F)<<8) + (hb) );
			}else{
				nextcluster = ( (lb<<4) + (hb>>4) );
			}
			break;
		case FAT16:
			offset=cluster_addr%256;
			nextcluster = *((euint16*)buf + offset);
			break;
		case FAT32:
			offset=cluster_addr%128;
			nextcluster = *((euint32*)buf + offset);
			break;
	}
	return(nextcluster);
}
/*****************************************************************************/ 

/* ****************************************************************************  
 * void fat_setNextClusterAddressWBuf(FileSystem *fs,euint32 cluster_addr,euint32 next_cluster_addr,euint8* buf)
 * Description: This function fills in a fat entry. The entry is cluster_addr and the
 * data entered is next_cluster_addr. This function is also given a *buf, so it does
 * not write the data itself, except in the case of FAT 12 cross sector data, where
 * the second sector is handled by this function.
 * Return value:
*/
void fat_setNextClusterAddressWBuf(FileSystem *fs,euint32 cluster_addr,euint32 next_cluster_addr,euint8* buf)
{
	euint16 offset;
	euint8 *buf2;
		
	switch(fs->type)
	{
		case FAT12:
			offset = ((cluster_addr%1024)*3/2)%512;
			if(offset == 511){
				if(cluster_addr%2==0){
					buf[offset]=next_cluster_addr&0xFF;
				}else{
					buf[offset]=(buf[offset]&0xF)+((next_cluster_addr<<4)&0xF0);
				}
				buf2=part_getSect(fs->part,fat_getSectorAddressFatEntry(fs,cluster_addr)+1,IOM_MODE_READWRITE);
				if(cluster_addr%2==0){
					buf2[0]=(buf2[0]&0xF0)+((next_cluster_addr>>8)&0xF);
				}else{
					buf2[0]=(next_cluster_addr>>4)&0xFF;
				}
				part_relSect(fs->part,buf2);
			}else{
				if(cluster_addr%2==0){
					buf[offset]=next_cluster_addr&0xFF;
					buf[offset+1]=(buf[offset+1]&0xF0)+((next_cluster_addr>>8)&0xF);
				}else{
					buf[offset]=(buf[offset]&0xF)+((next_cluster_addr<<4)&0xF0);
					buf[offset+1]=(next_cluster_addr>>4)&0xFF;
				}
			}
			break;
		case FAT16:
			offset=cluster_addr%256;
			*((euint16*)buf+offset)=next_cluster_addr;
			break;
		case FAT32:
			offset=cluster_addr%128;
			*((euint32*)buf+offset)=next_cluster_addr;
			break;
	}
}
/*****************************************************************************/

/* ****************************************************************************  
 * esint16 fat_getNextClusterChain(FileSystem *fs, ClusterChain *Cache)
 * Description: This function is to advance the clusterchain of a Cache.
 * First, the function verifies if the Cache is valid. It could correct it if it 
 * is not, but this is not done at the time. If the cachen is valid, the next step is
 * to see what the next cluster is, if this is the End of Clustermark, the cache is
 * updated to know the lastcluster but will remain untouched otherwise. -1 is returned.
 * If there are more clusters the function scans the rest of the chain until the next
 * cluster is no longer lineair, or until it has run out of fat data (only 1 sector) is
 * examined, namely the one fetched to check for EoC.
 * With lineair is meant that logical cluster n+1 should be 1 more than logical cluster n
 * at the disc level.
 * Return value: 0 on success, or -1 when EoC.
*/
esint16 fat_getNextClusterChain(FileSystem *fs, ClusterChain *Cache)
{
	euint32 sect,lr,nlr,dc;
	esint16 lin=0;
	euint8 *buf;

	if(Cache->DiscCluster==0)
	{
		return(-1);
	}

	sect=fat_getSectorAddressFatEntry(fs,Cache->DiscCluster);
	buf=part_getSect(fs->part,sect,IOM_MODE_READONLY);
	dc=fat_getNextClusterAddressWBuf(fs,Cache->DiscCluster,buf);
	if(fat_isEocMarker(fs,dc))
	{
		Cache->LastCluster=Cache->DiscCluster;
		part_relSect(fs->part,buf);
		return(-1);
	}
	
	Cache->DiscCluster=dc;
	Cache->LogicCluster++;
		
	lr=Cache->DiscCluster-1;
	nlr=lr+1;
	
	while(nlr-1==lr && fat_getSectorAddressFatEntry(fs,nlr)==sect)
	{
		lr=nlr;
		nlr=fat_getNextClusterAddressWBuf(fs,lr,buf);
		lin++;	
	}
	
	Cache->Linear=lin-1<0?0:lin-1;
	
	part_relSect(fs->part,buf);
	return(0);
}
/*****************************************************************************/


/* ****************************************************************************  
 * esint16 fat_LogicToDiscCluster(FileSystem *fs, ClusterChain *Cache,euint32 logiccluster)
 * Description: This function is used to follow clusterchains. When called it will convert
 * a logical cluster, to a disc cluster, using a Cache object. All it does is call
 * getNextClusterChain in the proper manner, and rewind clusterchains if required.
 * It is NOT recommended to go backwards in clusterchains, since this will require
 * scanning the entire chain every time.
 * Return value: 0 on success and -1 on failure (meaning out of bounds).
*/
esint16 fat_LogicToDiscCluster(FileSystem *fs, ClusterChain *Cache,euint32 logiccluster)
{
	if(logiccluster<Cache->LogicCluster || Cache->DiscCluster==0){
		Cache->LogicCluster=0;
		Cache->DiscCluster=Cache->FirstCluster;
		Cache->Linear=0;
	}
	
	if(Cache->LogicCluster==logiccluster){
		return(0);
	}
	
	while(Cache->LogicCluster!=logiccluster)
	{
		if(Cache->Linear!=0)
		{
			Cache->Linear--;
			Cache->LogicCluster++;
			Cache->DiscCluster++;
		}
		else
		{
			if((fat_getNextClusterChain(fs,Cache))!=0){
				return(-1);
			}
		}
	}
	return(0);
}
/*****************************************************************************/

/* ****************************************************************************  
 * eint16 fat_allocClusterChain(FileSystem *fs,ClusterChain *Cache,euint32 num_clusters)
 * Description: This function extends a clusterchain by num_clusters. It returns the
 * number of clusters it *failed* to allocate. 
 * Return value: 0 on success, all other values are the number of clusters it could
 * not allocate.
*/
eint16 fat_allocClusterChain(FileSystem *fs,ClusterChain *Cache,euint32 num_clusters)
{
	euint32 cc,ncl=num_clusters,lc;
	euint8 *bufa=0,*bufb=0;
	euint8  overflow=0;

	if(Cache->FirstCluster<=1)return(num_clusters);
	
	lc=fs_getLastCluster(fs,Cache);
	cc=lc;
	
	while(ncl > 0){
		cc++;
		if(cc>=fs->DataClusterCount+1){
			if(overflow){
				bufa=part_getSect(fs->part,fat_getSectorAddressFatEntry(fs,lc),IOM_MODE_READWRITE);
				fat_setNextClusterAddressWBuf(fs,lc,fat_giveEocMarker(fs),bufa);
				Cache->LastCluster=lc;
				part_relSect(fs->part,bufa);
				return(num_clusters-ncl);
			}
			cc=2;
			overflow++;
		}
		bufa=part_getSect(fs->part,fat_getSectorAddressFatEntry(fs,cc),IOM_MODE_READONLY);
		if(fat_getNextClusterAddressWBuf(fs,cc,bufa)==0){
			bufb=part_getSect(fs->part,fat_getSectorAddressFatEntry(fs,lc),IOM_MODE_READWRITE);
			fat_setNextClusterAddressWBuf(fs,lc,cc,bufb);
			part_relSect(fs->part,bufb);
			ncl--;
			lc=cc;
		}
		part_relSect(fs->part,bufa);
		if(ncl==0){
			bufa=part_getSect(fs->part,fat_getSectorAddressFatEntry(fs,lc),IOM_MODE_READWRITE);
			fat_setNextClusterAddressWBuf(fs,lc,fat_giveEocMarker(fs),bufa);
			Cache->LastCluster=lc;
			part_relSect(fs->part,bufa);
		}
	}
	return(0);
}

/* ****************************************************************************  
 * eint16 fat_unlinkClusterChain(FileSystem *fs,ClusterChain *Cache)
 * Description: This function removes a clusterchain. Starting at FirstCluster
 * it follows the chain until the end, resetting all values to 0.
 * Return value: 0 on success.
*/
eint16 fat_unlinkClusterChain(FileSystem *fs,ClusterChain *Cache)
{
	euint32 c,tbd=0;
	
	Cache->LogicCluster=0;
	Cache->DiscCluster=Cache->FirstCluster;
	
	c=0;
	
	while(!fat_LogicToDiscCluster(fs,Cache,c++)){
		if(tbd!=0){
			fat_setNextClusterAddress(fs,tbd,0);
		}
		tbd=Cache->DiscCluster;
	}
	fat_setNextClusterAddress(fs,Cache->DiscCluster,0);
 	return(0);
}

euint32 fat_countClustersInChain(FileSystem *fs,euint32 firstcluster)
{
	ClusterChain cache;
	euint32 c=0;
	
	if(firstcluster<=1)return(0);
	
	cache.DiscCluster = cache.LogicCluster = cache.LastCluster = cache.Linear = 0;
	cache.FirstCluster = firstcluster;
	
	while(!(fat_LogicToDiscCluster(fs,&cache,c++)));
	
	return(c-1);
}

euint32 fat_DiscToLogicCluster(FileSystem *fs,euint32 firstcluster,euint32 disccluster)
{
	ClusterChain cache;
	euint32 c=0,r=0;
	
	cache.DiscCluster = cache.LogicCluster = cache.LastCluster = cache.Linear = 0;
	cache.FirstCluster = firstcluster;
	
	while(!(fat_LogicToDiscCluster(fs,&cache,c++)) && !r){
		if(cache.DiscCluster == disccluster){
			r = cache.LogicCluster;
		}
	}
	return(r);
}

void fat_ShortnameToString(const euint8* src, eint8* nm)
{
	register eint32 i;

	i = 8;
	while (i-- && *src != ' ')
	{
		*nm++ = *src++;
	}

	src += i + 1;
	if (*src > ' ')
	{
		*nm++ = '.';
		i = 3;
		while (i-- && *src != ' ')
		{
			*nm++ = *src++;
		}
	}

	*nm = '\0';
}
