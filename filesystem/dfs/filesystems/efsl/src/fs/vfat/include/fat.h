/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : fat.h                                                            *
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

#ifndef __FAT_H_
#define __FAT_H_

/*****************************************************************************/
#include "config.h"
#include "error.h"
#include "file.h"
#include "debug.h"
#include "types.h"
/*****************************************************************************/

euint32 fat_getSectorAddressFatEntry(FileSystem *fs,euint32 cluster_addr);
euint32 fat_getNextClusterAddress(FileSystem *fs,	euint32 cluster_addr, euint16 *linear);
void fat_setNextClusterAddress(FileSystem *fs,euint32 cluster_addr,euint32 next_cluster_addr);
eint16 fat_isEocMarker(FileSystem *fs,euint32 fat_entry);
euint32 fat_giveEocMarker(FileSystem *fs);
euint32 fat_findClusterAddress(FileSystem *fs,euint32 cluster,euint32 offset, euint8 *linear);
euint32 fat_getNextClusterAddressWBuf(FileSystem *fs,euint32 cluster_addr, euint8 * buf);
void fat_setNextClusterAddressWBuf(FileSystem *fs,euint32 cluster_addr,euint32 next_cluster_addr,euint8 * buf);
esint16 fat_getNextClusterChain(FileSystem *fs, ClusterChain *Cache);
void fat_bogus(void);
esint16 fat_LogicToDiscCluster(FileSystem *fs, ClusterChain *Cache,euint32 logiccluster);
eint16 fat_allocClusterChain(FileSystem *fs,ClusterChain *Cache,euint32 num_clusters);
eint16 fat_unlinkClusterChain(FileSystem *fs,ClusterChain *Cache);
euint32 fat_countClustersInChain(FileSystem *fs,euint32 firstcluster);
euint32 fat_DiscToLogicCluster(FileSystem *fs,euint32 firstcluster,euint32 disccluster);
void fat_ShortnameToString(const euint8* src, eint8* nm);


#endif
