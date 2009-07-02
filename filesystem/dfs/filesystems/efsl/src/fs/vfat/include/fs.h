/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : fs.h                                                             *
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

#ifndef __FS_H_
#define __FS_H_

/*****************************************************************************/
#include "config.h"
#include "types.h"
#include "error.h"
#include "partition.h"
#include "debug.h"
#include "tm.h"
#include "extract.h"
/*****************************************************************************/

#define FAT12 1
#define FAT16 2
#define FAT32 3

#define FS_INFO_SECTOR 1
#define FSINFO_MAGIC_BEGIN 0x41615252
#define FSINFO_MAGIC_END   0xAA550000

/*****************************************************************************************\
              VolumeId
               ------  
* ushort BytesPerSector		Must be 512 or shit happens.
* uchar  SectorsPerCluster	Must be multiple of 2 (1,2,4,8,16 or 32)
* ushort ReservedSectorCount	Number of sectors after which the first FAT begins.
* uchar	 NumberOfFats		Should be 2
* ushort RootEntryCount		Number of filerecords the Rootdir can contain. NOT for FAT32
* ushort SectorCount16		Number of Sectors for 12/16 bit FAT 
* ushort FatSectorCount16	Number of Sectors for 1 FAT on FAT12/16 bit FAT's
* ulong  SectorCount32		Number of Sectors for 32 bit FAT
* ulong FatSectorCount32	Number of Sectors for 1 FAT on FAT32 
* ulong RootCluster			Clusternumber of the first cluster of the RootDir on FAT 32
This is NOT a complete volumeId copy, no direct I/O is possible.
\*****************************************************************************************/
struct _VolumeId{
	euint16 BytesPerSector;
	euint8 SectorsPerCluster;
	euint16 ReservedSectorCount;
	euint8 NumberOfFats;
	euint16 RootEntryCount;
	euint16 SectorCount16;
	euint16 FatSectorCount16;
	euint32 SectorCount32;
	euint32 FatSectorCount32;
	euint32 RootCluster;
};
typedef struct _VolumeId VolumeId;

/**************************************************************************************************\
              FileSystem
               --------
* Partition* 	part		Pointer to partition on which this FS resides.
* VolumeId		volumeId	Contains important FS info.
* ulong			DataClusterCount	Number of dataclusters. This number determines the FATType.
* ulong			FatSectorCount		Number of sectors for 1 FAT, regardless of FATType
* ulong			SectorCount			Number of sectors, regardless of FATType
* ulong 		FirstSectorRootDir	First sector of the RootDir. 
* uchar			type				Determines FATType (FAT12 FAT16 or FAT32 are defined)

\**************************************************************************************************/
struct _FileSystem{
	Partition *part;
	VolumeId volumeId;
	euint32 DataClusterCount;
	euint32 FatSectorCount;
	euint32 SectorCount;
	euint32 FirstSectorRootDir;
	euint32 FirstClusterCurrentDir;
	euint32 FreeClusterCount;
	euint32 NextFreeCluster;
	euint8 type;
};
typedef struct _FileSystem FileSystem;

/**************************************************************************************************\              
		FileLocation
               ----------
* euint32		Sector				Sector where the directoryentry of the file/directory can be found.
* euint8		Offset				Offset (in 32byte segments) where in the sector the entry is.

\**************************************************************************************************/
struct _FileLocation{
	euint32 Sector;
	euint8 Offset;
	euint8 attrib;
};
typedef struct _FileLocation FileLocation;

/*****************************************************************************\
*                               FileCache                                    
*                              -----------                                   
* This struct acts as cache for the current file. It contains the current    
* FATPointer (next location in the FAT table), LogicCluster                  
* (the last part of the file that was read) and DataCluster                  
* (the last cluster that was read).     
* euint8		Linear				For how many more clusters the file is nonfragmented
* euint32		LogicCluster		This field determines the n'th cluster of the file as current
* euint32		DiscCluster		If this field is 0, it means the cache is invalid. Otherwise
									it is the clusternumber corresponding with 
									logic(FirstCluster+LogicCluster).
* euint32		FirstCluster		First cluster of the chain. Zero or one are invalid.
* euint32		LastCluster		Last cluster of the chain (is not always filled in)
\*****************************************************************************/
struct _ClusterChain{
	euint8 Linear;
	esint32 LogicCluster;
	euint32 DiscCluster;
	euint32 FirstCluster;
	euint32 LastCluster;
};
typedef struct _ClusterChain ClusterChain;

/*****************************************************************************\
*                               FileRecord                                    *
*                              ------------                                   *
* This struct represents a 32 byte file entry as it occurs in the data area   *
* of the filesystem. Direct I/O is possible.                                  *
\*****************************************************************************/
struct _FileRecord{
	euint8 FileName[11];
	euint8 Attribute;
	euint8 NTReserved;
	euint8 MilliSecTimeStamp;
	euint16 CreatedTime;
	euint16 CreatedDate;
	euint16 AccessDate;
	euint16 FirstClusterHigh;
	euint16 WriteTime;
	euint16 WriteDate;
	euint16 FirstClusterLow;
	euint32 FileSize;
};
typedef struct _FileRecord FileRecord;


eint16 fs_initFs(FileSystem *fs,Partition *part);
eint16 fs_isValidFat(Partition *part);
void fs_loadVolumeId(FileSystem *fs, Partition *part);
esint16 fs_verifySanity(FileSystem *fs);
void fs_countDataSectors(FileSystem *fs);
void fs_determineFatType(FileSystem *fs);
void fs_findFirstSectorRootDir(FileSystem *fs);
void fs_initCurrentDir(FileSystem *fs);
euint32 fs_getSectorAddressRootDir(FileSystem *fs,euint32 secref);
euint32 fs_clusterToSector(FileSystem *fs,euint32 cluster);
euint32 fs_sectorToCluster(FileSystem *fs,euint32 sector);
euint32 fs_getNextFreeCluster(FileSystem *fs,euint32 startingcluster);
euint32 fs_giveFreeClusterHint(FileSystem *fs);
esint16 fs_findFreeFile(FileSystem *fs,eint8* filename,FileLocation *loc,euint8 mode);
esint8 fs_findFile(FileSystem *fs,eint8* filename,FileLocation *loc,euint32 *lastDir);
esint8 fs_findFile_broken(FileSystem *fs,eint8* filename,FileLocation *loc);
euint32 fs_getLastCluster(FileSystem *fs,ClusterChain *Cache);
euint32 fs_getFirstClusterRootDir(FileSystem *fs);
euint16 fs_makeDate(void);
euint16 fs_makeTime(void);
void fs_setFirstClusterInDirEntry(FileRecord *rec,euint32 cluster_addr);
void fs_initClusterChain(FileSystem *fs,ClusterChain *cache,euint32 cluster_addr);
esint8 fs_flushFs(FileSystem *fs);
esint8 fs_umount(FileSystem *fs);
esint8 fs_clearCluster(FileSystem *fs,euint32 cluster);
esint8 fs_getFsInfo(FileSystem *fs);
esint8 fs_setFsInfo(FileSystem *fs);

#endif
