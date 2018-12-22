/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*----------------------------------------------------------------------------
 SigmaTel Inc
 $Archive: /Fatfs/FileSystem/Fat32/fatapi/FATsector.c $                                        
 $Revision: 5 $                                       
 $Date: 9/13/03 12:21p $                                           
 Description: FATsector.c
 Notes:	This file read provides FAT sector no and FATentry offset for the given cluster no.
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
		File Includes
----------------------------------------------------------------------------*/
#include <types.h>
#include "fstypes.h"
#include "fat_internal.h"
#include "filesystem/fsapi.h"
#include "bootsecoffset.h"
#include <stdlib.h>
#include <string.h>

// Define as 0 by default or 1 to see Compute Free Clx result and error codes on tss
#define VERBOSE_CFC_LOGGING 0

// Defines
#define FS_CACHE_SIZE 1024*1024
// Use the stub blank version by default. Debug tool only for active error analysis.
//#define MODULE_ASSERT(a)  assert(a)
#define MODULE_ASSERT(a)

/*----------------------------------------------------------------------------
>  Function Name: int32_t FATsectorno(int32_t DeviceNum,int32_t clusterno,int32_t *FATNtryOffsetInBytes)

   FunctionType:  Reentrant

   Inputs:        1) Device number
				  2) clusterno
				  3) pointer to a variable to receive the FAT entry offset

   Outputs:       Returns a sector-offset (in sectors) from the start of the device.
                  Also, *FATNtryOffsetInBytes is modified to be the offset of the associated FAT entry,
                  in bytes, within that sector.

   Description:   Background: Entries in the FAT refer to clusters on the device.

                  Given a cluster on the device designated by "clusterno", this 
                  function computes the sector on the device that contains
                  the FAT entry that refers to that cluster.
                  An offset to that sector from the start of the device
                  is returned, and "*FATNtryOffsetInBytes" is modified
                  to be the offset in bytes of that FAT entry in that
                  sector.
<
----------------------------------------------------------------------------*/
int32_t FATsectorno(int32_t DeviceNum, int32_t clusterno, int32_t * FATNtryOffsetInBytes)
{
    int32_t FAToffsetInBytes = 0;

    if (MediaTable[DeviceNum].FATType == FAT12)
        FAToffsetInBytes = clusterno + (clusterno >> 1);

    else if (MediaTable[DeviceNum].FATType == FAT16)
        FAToffsetInBytes = clusterno << 1;

    else if (MediaTable[DeviceNum].FATType == FAT32)
        FAToffsetInBytes = clusterno << 2;

    else
        return ERROR_OS_FILESYSTEM_MEDIA_TYPE_NOT_SUPPORTED;

    *FATNtryOffsetInBytes = FAToffsetInBytes & MediaTable[DeviceNum].SectorMask;

    return (MediaTable[DeviceNum].RsvdSectors) +
        (FAToffsetInBytes >> MediaTable[DeviceNum].SectorShift);

}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t Computefreecluster(int32_t DeviceNumber)

   FunctionType:   Reentrant

   Inputs:         1) Device number

   Outputs:        SUCCESS or negative error code. Writes static media table struct. 

   Description:    Determines & sets MediaTable[DeviceNumber].TotalFreeClusters 
                   by first checking FAT type (16|32)
<
----------------------------------------------------------------------------*/
int32_t Computefreecluster(int32_t DeviceNumber)
{
    int32_t totalfreeclusters;

    if (MediaTable[DeviceNumber].DevicePresent) {
        if ((totalfreeclusters = Totalfreecluster(DeviceNumber)) < 0) {
#if VERBOSE_CFC_LOGGING
            tss_logtext_Print(LOGTEXT_EVENT_OS_FILESYSTEM_GROUP | LOGTEXT_VERBOSITY_3,
                              "Totfreecx(%d) er:x%x\r\n", DeviceNumber, totalfreeclusters);
#endif

            // return negative err code.
            return (int32_t) totalfreeclusters;
        }

        MediaTable[DeviceNumber].TotalFreeClusters = totalfreeclusters;

#if VERBOSE_CFC_LOGGING
        tss_logtext_Print(LOGTEXT_EVENT_OS_FILESYSTEM_GROUP | LOGTEXT_VERBOSITY_3,
                          "Compfreecx(%d): %d\r\n", DeviceNumber, totalfreeclusters);
#endif
    } else {
#if VERBOSE_CFC_LOGGING
        tss_logtext_Print(LOGTEXT_EVENT_OS_FILESYSTEM_GROUP | LOGTEXT_VERBOSITY_3, "Compfreecx: no device\r\n");    // should this case return error? 
#endif
    }

    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t Findnextcluster(int32_t DeviceNum,int32_t clusterno)
  
   FunctionType:   Reentrant

   Inputs:         1) Device number
                   2) Cluster number

   Outputs:        Returns Next cluster no.

   Description:    Determines Next cluster no. by first finding the FAT sector and offset
                   in that sector for the entry of the given cluster no. 
<
----------------------------------------------------------------------------*/
int32_t Findnextcluster(int32_t DeviceNum, int32_t clusterno)
{
    int32_t FATNtryoffset;
    int32_t FATsector, FATentry;

    ddi_ldl_push_media_task("Findnextcluster");
    FATsector = FATsectorno(DeviceNum, clusterno, &FATNtryoffset);
    if (FATsector <= 0) {
        ddi_ldl_pop_media_task();
        return ERROR_OS_FILESYSTEM_NOT_VALID_SECTOR;
    }
    FATentry = ReadFATentry(DeviceNum, FATsector, FATNtryoffset, clusterno);
    ddi_ldl_pop_media_task();
    return (FATentry);
}

/*----------------------------------------------------------------------------
>  Function Name:  REENTRANT int32_t FirstfreeAndallocate(int32_t DeviceNum)

   FunctionType:   Reentrant

   Inputs:         1) Device number

   Outputs:        Returns Cluster no. of free cluster 

   Description:    Determines free cluster by checking FAT entry in FAT table
<
----------------------------------------------------------------------------*/
REENTRANT int32_t FirstfreeAndallocate(int32_t DeviceNum)
{
    int32_t FATentry, FATntryoffset, FAToffset;
    int32_t clusterNum, FATsectorNo;
    uint8_t *buf;
    uint32_t cacheToken = 0;

    if (DeviceNum >= maxdevices || DeviceNum < 0) {
        return ERROR_OS_FILESYSTEM_MAX_DEVICES_EXCEEDED;
    }

    ddi_ldl_push_media_task("FirstfreeAndallocate");

    if ((FATsectorNo =
         FATsectorno(DeviceNum, (MediaTable[DeviceNum].NextFreeCluster + 1), &FATntryoffset)) < 0) {
        ddi_ldl_pop_media_task();
        return FATsectorNo;
    }

    if ((clusterNum = MediaTable[DeviceNum].NextFreeCluster) < 0) {
        ddi_ldl_pop_media_task();
        return ERROR_OS_FILESYSTEM_INVALID_CLUSTER_NO;
    }

    if (MediaTable[DeviceNum].TotalFreeClusters == 0) {
        ddi_ldl_pop_media_task();
        return (ERROR_OS_FILESYSTEM_NO_FREE_CLUSTER);
    }

    EnterNonReentrantSection();
    if ((buf = ((uint8_t *) FSReadSector(DeviceNum, FATsectorNo, 0, &cacheToken))) == (uint8_t *) 0) {
        ddi_ldl_pop_media_task();
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
    }

    if (MediaTable[DeviceNum].FATType == FAT12) {
        do {
            clusterNum++;
            if (clusterNum > MediaTable[DeviceNum].TotalNoofclusters) {
                clusterNum = 2;
                FATsectorNo = MediaTable[DeviceNum].RsvdSectors;

                // Release previous sector before reading the next.
                FSReleaseSector(cacheToken);

                if ((buf =
                     (uint8_t *) FSReadSector(DeviceNum, FATsectorNo, 0,
                                              &cacheToken)) == (uint8_t *) 0) {
                    ddi_ldl_pop_media_task();
                    LeaveNonReentrantSection();
                    return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
                }
            }

            FAToffset = clusterNum + (clusterNum >> 1);
            FATntryoffset = FAToffset & MediaTable[DeviceNum].SectorMask;
            buf =
                ReadFAT12Entry(DeviceNum, (int32_t *) & FATsectorNo, FATntryoffset, clusterNum, buf,
                               &FATentry, &cacheToken);

        } while (FATentry != 0);

        if (FATntryoffset == (MediaTable[DeviceNum].BytesPerSector - 1)) {
            FATsectorNo--;
        }
        // Have to release the cache entry from reading before we can write into it.
        FSReleaseSector(cacheToken);

        WriteFATentry(DeviceNum, FATsectorNo, FATntryoffset, clusterNum, FAT12EOF);
    } else if (MediaTable[DeviceNum].FATType == FAT16) {
        FATntryoffset = FATntryoffset - 2;
        do {
            clusterNum++;
            if (clusterNum > MediaTable[DeviceNum].TotalNoofclusters) {
                clusterNum = 2;
                FATntryoffset = 4;
                FATsectorNo = MediaTable[DeviceNum].RsvdSectors;

                // Release previous sector before reading the next.
                FSReleaseSector(cacheToken);

                if ((buf =
                     (uint8_t *) FSReadSector(DeviceNum, FATsectorNo, 0,
                                              &cacheToken)) == (uint8_t *) 0) {
                    ddi_ldl_pop_media_task();
                    LeaveNonReentrantSection();
                    return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
                }
            } else {
                FATntryoffset = FATntryoffset + 2;
            }

            if (FATntryoffset == MediaTable[DeviceNum].BytesPerSector) {
                FATntryoffset = 0;
                FATsectorNo++;

                // Release previous sector.
                FSReleaseSector(cacheToken);

                if ((buf =
                     (uint8_t *) FSReadSector(DeviceNum, FATsectorNo, 0,
                                              &cacheToken)) == (uint8_t *) 0) {
                    ddi_ldl_pop_media_task();
                    LeaveNonReentrantSection();
                    return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
                }
            }
            FATentry = FSGetWord((uint8_t *) buf, FATntryoffset);

        } while (FATentry != 0);

        // Have to release the cache entry from reading before we can write into it.
        FSReleaseSector(cacheToken);

        WriteFATentry(DeviceNum, FATsectorNo, FATntryoffset, clusterNum, FAT32EOF);
    } else if (MediaTable[DeviceNum].FATType == FAT32) {
        buf =
            FirstfreeAndallocateFAT32(DeviceNum, FATsectorNo, FATntryoffset, buf, &clusterNum,
                                      cacheToken);
    }

    MediaTable[DeviceNum].NextFreeCluster = clusterNum;
    MediaTable[DeviceNum].TotalFreeClusters--;

    LeaveNonReentrantSection();
    ddi_ldl_pop_media_task();
    return (MediaTable[DeviceNum].NextFreeCluster);

}

/*----------------------------------------------------------------------------
>  Function Name:  REENTRANT uint8_t *FirstfreeAndallocateFAT32(int32_t DeviceNum ,int32_t FATsectorNo,int32_t FAToffset,uint8_t *buf, int32_t *FATval)

   FunctionType:   Reentrant

   Inputs:         1)Device number
                   2)FATsectorNo
                   3)FAToffset
                   4)pointer to buffer
                   5)pointer to FATvalue

   Outputs:        Returns cluster no. of free cluster 

   Description:    Determines free cluster depending upon the entry in FAT Table
<
----------------------------------------------------------------------------*/
uint8_t *FirstfreeAndallocateFAT32(int32_t DeviceNum, int32_t FATsectorNo, int32_t FAToffset,
                                   uint8_t * buf, int32_t * FATval, uint32_t cacheToken)
{
    int32_t clusterNum, FATentry;

    clusterNum = MediaTable[DeviceNum].NextFreeCluster;
    FAToffset = FAToffset - 4;
    do {
        clusterNum++;
        if (clusterNum > MediaTable[DeviceNum].TotalNoofclusters) {
            clusterNum = 2;
            FAToffset = 8;
            FATsectorNo = MediaTable[DeviceNum].RsvdSectors;

            FSReleaseSector(cacheToken);

            if ((buf =
                 (uint8_t *) FSReadSector(DeviceNum, FATsectorNo, 0,
                                          &cacheToken)) == (uint8_t *) 0) {
                return (uint8_t *) 0;
            }
        } else {
            FAToffset = FAToffset + 4;
        }

        if (FAToffset == MediaTable[DeviceNum].BytesPerSector) {
            FAToffset = 0;
            FATsectorNo++;

            FSReleaseSector(cacheToken);

            if ((buf =
                 (uint8_t *) FSReadSector(DeviceNum, FATsectorNo, 0,
                                          &cacheToken)) == (uint8_t *) 0) {
                return (uint8_t *) 0;
            }
        }
        FATentry = FSGetDWord((uint8_t *) buf, FAToffset);
    } while (FATentry != 0);

    // Have to release the cache entry from reading before we can write into it.
    FSReleaseSector(cacheToken);

    WriteFATentry(DeviceNum, FATsectorNo, FAToffset, clusterNum, FAT32EOF);

    *FATval = clusterNum;
    return buf;
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t Firstsectorofcluster(int32_t DeviceNum,int32_t clusterno)

   FunctionType:  Reentrant

   Inputs:        1) Device number
				  2) cluster no.

   Outputs:       Returns First sector no. of given cluster 

   Description:   Determines First sector of given cluster by considering sector per cluter
                  and first data sector 
<
----------------------------------------------------------------------------*/
int32_t Firstsectorofcluster(int32_t DeviceNum, int32_t clusterno)
{
    int32_t sectorno;

    if (clusterno < 0)
        return ERROR_OS_FILESYSTEM_INVALID_CLUSTER_NO;
    else if (clusterno == 0)
        sectorno = MediaTable[DeviceNum].FirRootdirsec;
    else
        sectorno =
            ((clusterno - 2) * MediaTable[DeviceNum].SectorsPerCluster) +
            MediaTable[DeviceNum].FIRSTDataSector;

    return (sectorno);
}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t GetNewcluster(int32_t Handlenumber)

   FunctionType:   Reentrant

   Inputs:         1) Handlenumber

   Outputs:        Updates the handle according to the new cluster.
                   Returns ERROR_OS_FILESYSTEM_NO_FREE_CLUSTER if no free cluster is available else error NOSPACEINROOTDIRECTORY

   Description:    Finds a new free cluster and writes its value in the FAT table
                   for current cluster's entry.  
----------------------------------------------------------------------------*/
RtStatus_t GetNewcluster(int32_t Handlenumber)
{
    int32_t currentcluster, Devicenum;
    int32_t FATNtryoffset;
    int32_t FATsector;

    Devicenum = Handle[Handlenumber].Device;
    currentcluster = Handle[Handlenumber].CurrentCluster;

    EnterNonReentrantSection();

    ddi_ldl_push_media_task("GetNewcluster");

    if ((currentcluster = FirstfreeAndallocate(Devicenum)) < 0) {
        ddi_ldl_pop_media_task();
        LeaveNonReentrantSection();
        return (ERROR_OS_FILESYSTEM_NO_FREE_CLUSTER);
    }

    Handle[Handlenumber].CurrentSector = Firstsectorofcluster(Devicenum, currentcluster);

    if ((FATsector =
         FATsectorno(Devicenum, Handle[Handlenumber].CurrentCluster, &FATNtryoffset)) <= 0) {
        ddi_ldl_pop_media_task();
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_NOT_VALID_SECTOR;
    }

    /* write the entry in the sector no. at the offset in the sector */
    WriteFATentry(Devicenum, FATsector, FATNtryoffset, Handle[Handlenumber].CurrentCluster,
                  currentcluster);

    /* update the handle */

    Handle[Handlenumber].CurrentCluster = currentcluster;
    Handle[Handlenumber].BytePosInSector = 0;
    Handle[Handlenumber].SectorPosInCluster = 0;

    LeaveNonReentrantSection();
    ddi_ldl_pop_media_task();
    return (SUCCESS);
}

/*----------------------------------------------------------------------------
>  Function Name: uint8_t *ReadFAT12Entry(int32_t DeviceNum,int32_t *FATsectorNo,int32_t FATntryoffset,int32_t clusterNum,uint8_t *buf,int32_t *FATentry)
 
   FunctionType:  Reentrant

   Inputs:        1) Device number
				  2) FATsectorNo
				  3) FATntryoffset
				  4) cluster no.
                  5) pointer to buffer
                  6) pointer to FATentry 

   Outputs:       Returns FATentry of the given cluster no. 

   Description:   Determines FATentry for the given cluster no. from the FAT sector 
                  and FATentryoffset depending upon FAT type.
<
----------------------------------------------------------------------------*/
uint8_t *ReadFAT12Entry(int32_t DeviceNum, int32_t * FATsectorNo, int32_t FATntryoffset,
                        int32_t clusterNum, uint8_t * buf, int32_t * FATentry,
                        uint32_t * cacheToken)
{
    /* check boundary condition */
    /* if FATntryoffset is at the boundary of a sector then get low byte from the last byte
       of this sector and high byte from the first byte of next sector */
    EnterNonReentrantSection();

    if (FATntryoffset == (MediaTable[DeviceNum].BytesPerSector - 1)) {
        *FATentry = FSGetByte((uint8_t *) buf, FATntryoffset);
        *FATsectorNo = *FATsectorNo + 1;
        FSReleaseSector(*cacheToken);
        if ((buf =
             (uint8_t *) FSReadSector(DeviceNum, *FATsectorNo, WRITE_TYPE_RANDOM,
                                      cacheToken)) == (uint8_t *) 0) {
            LeaveNonReentrantSection();
            return (uint8_t *) 0;
        }
        *FATentry += (FSGetByte((uint8_t *) buf, 0) << 8);
    } else {
        *FATentry = FSGetWord((uint8_t *) buf, FATntryoffset);
    }

    LeaveNonReentrantSection();

    if (clusterNum & 0x0001) {
        *FATentry = (*FATentry >> 4);
    } else {
        *FATentry = (*FATentry & 0x0fff);
    }

    /* check boundary condition */
    /* if FATntryoffset is at the boundary of a sector then get the entry
       from the next sector */
    if ((FATntryoffset == (MediaTable[DeviceNum].BytesPerSector - 2)) && (clusterNum & 0x0001)) {
        *FATsectorNo = *FATsectorNo + 1;
        EnterNonReentrantSection();
        FSReleaseSector(*cacheToken);
        if ((buf =
             (uint8_t *) FSReadSector(DeviceNum, *FATsectorNo, WRITE_TYPE_RANDOM,
                                      cacheToken)) == (uint8_t *) 0) {
            LeaveNonReentrantSection();
            return (uint8_t *) 0;
        }
        LeaveNonReentrantSection();
    }
    return buf;
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t ReadFATentry(int32_t Devicenum,int32_t FATsector,int32_t FATNtryoffset,int32_t clusterno)
 
   FunctionType:   Reentrant

   Inputs:         1) Device number
				   2) FATsector
				   3) FATNtryoffset
				   4) cluster no.

   Outputs:        Returns FATentry of the given cluster no.

   Description:    Determines FATentry for the given cluster no. from the FAT sector 
                   and FATentryoffset depending upon FAT type.
<
----------------------------------------------------------------------------*/
int32_t ReadFATentry(int32_t Devicenum, int32_t FATsector, int32_t FATNtryoffset, int32_t clusterno)
{
    int32_t FATntry = 0;
    uint8_t *buf;
    uint32_t cacheToken = 0;

    EnterNonReentrantSection();
    /* Read the FAT Sector */

    ddi_ldl_push_media_task("ReadFATentry");

    if ((buf =
         (uint8_t *) FSReadSector(Devicenum, FATsector, WRITE_TYPE_RANDOM,
                                  &cacheToken)) == (uint8_t *) 0) {
        ddi_ldl_pop_media_task();
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
    }
    /* if FAT type is FAT12 then take 12 bits for FAT entry */
    if (MediaTable[Devicenum].FATType == FAT12) {
        buf =
            ReadFAT12Entry(Devicenum, (int32_t *) & FATsector, FATNtryoffset, clusterno, buf,
                           (int32_t *) & FATntry, &cacheToken);
        if (FATntry == 0x0FFF) {
            FATntry = ERROR_OS_FILESYSTEM_EOF;
        }
    }
    /* if FAT type is FAT16 then take 16 bits (uint32_t) for FAT entry */
    else if (MediaTable[Devicenum].FATType == FAT16) {
        FATntry = FSGetWord((uint8_t *) buf, FATNtryoffset);
        if (FATntry == 0xFFFF) {
            FATntry = ERROR_OS_FILESYSTEM_EOF;
        }
    }
    /* if FAT type is FAT32 then take 32 bits (DWORD) for FAT entry */
    else if (MediaTable[Devicenum].FATType == FAT32) {
        FATntry = FS_GET_LITTLEENDIAN_INT32(buf, FATNtryoffset);
        if (FATntry == 0x0FFFFFFF) {
            FATntry = ERROR_OS_FILESYSTEM_EOF;
        }
    } else {
        FATntry = ERROR_OS_FILESYSTEM_MEDIA_TYPE_NOT_SUPPORTED;
    }
    FSReleaseSector(cacheToken);
    LeaveNonReentrantSection();
    ddi_ldl_pop_media_task();
    return (FATntry);
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t Totalfreecluster(int32_t DeviceNum)

   FunctionType:   Reentrant

   Inputs:         1) Device number

   Outputs:        Returns total no. of free clusters

   Description:    Determines total free clusters by first checking FAT type
<
----------------------------------------------------------------------------*/
int32_t Totalfreecluster(int32_t DeviceNum)
{
    const int32_t iSectorSize = MediaTable[DeviceNum].BytesPerSector;
    int32_t totalfreeclusters, FATsectorNo, FATentry;
    uint8_t *pu8LocalBuf;
    uint8_t *buf;
    int32_t FAToffset, clusterNum;
//    RtStatus_t      rVal;
    uint32_t cacheToken;

    totalfreeclusters = 0;
    FATsectorNo = MediaTable[DeviceNum].RsvdSectors;

    if (MediaTable[DeviceNum].FATType == FAT32) {
        // get a buffer
//        rVal = os_dmi_MemAlloc( (void**)&pu8LocalBuf, iSectorSize, true, DMI_MEM_SOURCE_FASTMEM );
//        if ( rVal != SUCCESS )
//        {
//            SystemHalt( );
//        }
        pu8LocalBuf = malloc(sizeof(uint8_t) * iSectorSize);

        EnterNonReentrantSection();
        if ((buf =
             (uint8_t *) FSReadSector(DeviceNum, FATsectorNo, WRITE_TYPE_RANDOM,
                                      &cacheToken)) == (uint8_t *) 0) {
            MODULE_ASSERT(false);
//            os_dmi_MemFree( pu8LocalBuf );
            free(pu8LocalBuf);
            LeaveNonReentrantSection();
            return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
        }
        // copy from cached buffer to local buffer so we can free the mutex protecting the file system(cache)
        memcpy(pu8LocalBuf, buf, iSectorSize);
        FSReleaseSector(cacheToken);
        LeaveNonReentrantSection();

        FAToffset = 8;

        /* Use dynamic allocation for data cache */
        uint8_t *buf = (uint8_t *) malloc(FS_CACHE_SIZE);
        if (buf == NULL) {
            return ERROR_OS_FILESYSTEM_MEMORY;
        }
        int cache_offset = 0;
        for (clusterNum = 2; clusterNum <= MediaTable[DeviceNum].TotalNoofclusters; clusterNum++) {
            FATentry = FSGetDWord((uint8_t *) pu8LocalBuf, FAToffset);
            if (FATentry == 0) {
                totalfreeclusters++;
                if (totalfreeclusters == 1)
                    MediaTable[DeviceNum].NextFreeCluster = clusterNum;
            }

            FAToffset = FAToffset + 4;

            /* check for boundary condition */
            if (FAToffset == MediaTable[DeviceNum].BytesPerSector) {
                FAToffset = 0;
                FATsectorNo++;

                EnterNonReentrantSection();
                if (cache_offset == 0) {
                    if ((buf =
                         (uint8_t *) FSReadMultiSectors(DeviceNum, FATsectorNo, WRITE_TYPE_RANDOM,
                                                        buf, FS_CACHE_SIZE)) == (uint8_t *) 0) {
                        MODULE_ASSERT(false);
//                    os_dmi_MemFree( pu8LocalBuf );
                        free(pu8LocalBuf);
                        LeaveNonReentrantSection();
                        return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
                    }
                }
                // copy from cached buffer to local buffer so we can free the mutex protecting the file system(cache)
                memcpy(pu8LocalBuf, buf + cache_offset, iSectorSize);
                cache_offset += MediaTable[DeviceNum].BytesPerSector;
                if (cache_offset == FS_CACHE_SIZE)
                    cache_offset = 0;   //wrap back to head
                LeaveNonReentrantSection();
            }
        }
//        os_dmi_MemFree( pu8LocalBuf );
        free(pu8LocalBuf);
        free(buf);              // release the cache buffer
    } else {
        totalfreeclusters = TotalfreeclusterFAT16(DeviceNum);
        MODULE_ASSERT(totalfreeclusters >= 0);  // catch error code in DEBUG builds. 
    }
    MODULE_ASSERT(totalfreeclusters >= 0);  // catch error code in DEBUG builds. 
    return (totalfreeclusters);

}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t TotalfreeclusterFAT16(int32_t DeviceNum)

   FunctionType:   Reentrant

   Inputs:         1) Device number

   Outputs:        Returns total no. of free clusters

   Description:    Determines total free clusters by first checking FAT type
<
----------------------------------------------------------------------------*/
int32_t TotalfreeclusterFAT16(int32_t DeviceNum)
{
    const int32_t iSectorSize = MediaTable[DeviceNum].BytesPerSector;
    int32_t totalfreeclusters;
    int32_t FATsectorNo, FAToffset, clusterNum, FATentry, FATntryoffset;
    uint8_t *pu8LocalBuf;
    uint8_t *buf;
//    RtStatus_t      rVal;
    uint32_t cacheToken;

    totalfreeclusters = 0;
    FATsectorNo = MediaTable[DeviceNum].RsvdSectors;
    EnterNonReentrantSection();
    if ((buf =
         (uint8_t *) FSReadSector(DeviceNum, FATsectorNo, WRITE_TYPE_RANDOM,
                                  &cacheToken)) == (uint8_t *) 0) {
        MODULE_ASSERT(false);
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
    }

    if (MediaTable[DeviceNum].FATType == FAT12) {
        // for fat12 we can't let go of the mutex protecting the underlaying cache buffer
        // so for this case, we'll keep it the entire time.  fortunately, fat12 is only for system files.
        for (clusterNum = 2; clusterNum <= MediaTable[DeviceNum].TotalNoofclusters; clusterNum++) {
            FAToffset = clusterNum + (clusterNum >> 1);
            FATntryoffset = FAToffset & MediaTable[DeviceNum].SectorMask;
            if ((buf =
                 ReadFAT12Entry(DeviceNum, &FATsectorNo, FATntryoffset, clusterNum, buf, &FATentry,
                                &cacheToken)) == (uint8_t *) 0) {
                MODULE_ASSERT(false);
                LeaveNonReentrantSection();
                return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
            }

            if (FATentry == 0) {
                totalfreeclusters++;
                if (totalfreeclusters == 1) {
                    MediaTable[DeviceNum].NextFreeCluster = clusterNum;
                }
            }

        }
        FSReleaseSector(cacheToken);
        LeaveNonReentrantSection();
    } else if (MediaTable[DeviceNum].FATType == FAT16) {
        // get a buffer
//        rVal = os_dmi_MemAlloc( (void**)&pu8LocalBuf, iSectorSize, true, DMI_MEM_SOURCE_FASTMEM );
//        if ( rVal != SUCCESS )
//        {
//            SystemHalt( ); // note: powers off in release builds.
//        }
        pu8LocalBuf = malloc(sizeof(uint8_t) * iSectorSize);

        // copy from cached buffer to local buffer so we can free the mutex protecting the file system(cache)
        memcpy(pu8LocalBuf, buf, iSectorSize);
        FSReleaseSector(cacheToken);
        LeaveNonReentrantSection();

        FATntryoffset = 4;
        for (clusterNum = 2; clusterNum <= MediaTable[DeviceNum].TotalNoofclusters; clusterNum++) {
            FATentry = FSGetWord((uint8_t *) pu8LocalBuf, FATntryoffset);
            if (FATentry == 0) {
                totalfreeclusters++;
                if (totalfreeclusters == 1)
                    MediaTable[DeviceNum].NextFreeCluster = clusterNum;
            }

            FATntryoffset = FATntryoffset + 2;
            /* check for boundary condition */
            if (FATntryoffset == MediaTable[DeviceNum].BytesPerSector) {
                FATntryoffset = 0;
                FATsectorNo++;

                EnterNonReentrantSection();
                if ((buf =
                     (uint8_t *) FSReadSector(DeviceNum, FATsectorNo, WRITE_TYPE_RANDOM,
                                              &cacheToken)) == (uint8_t *) 0) {
                    MODULE_ASSERT(false);
//                    os_dmi_MemFree( pu8LocalBuf );
                    free(pu8LocalBuf);
                    LeaveNonReentrantSection();
                    return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
                }
                // copy from cached buffer to local buffer so we can free the mutex protecting the file system(cache)
                memcpy(pu8LocalBuf, buf, iSectorSize);
                FSReleaseSector(cacheToken);
                LeaveNonReentrantSection();
            }
        }
//        os_dmi_MemFree( pu8LocalBuf );
        free(pu8LocalBuf);
    }

    else {
        // FAT32 case
        MODULE_ASSERT(false);
        FSReleaseSector(cacheToken);
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_MEDIA_TYPE_NOT_SUPPORTED;
    }

    return (totalfreeclusters);
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t  WriteFATentry(int32_t DeviceNum,
    int32_t FATsector,int32_t FATNtryoffset,int32_t clusterno,int32_t writentry)
 
   FunctionType:  Reentrant

   Inputs:        1) Device number
				  2) FATsector
				  3) FATNtryoffset
				  4) cluster no.
				  5) write entry

   Outputs:       Returns SUCCESS else an error code

   Description:   Writes FAT entry  for the given cluster no. at the given FAT sector 
                  and FATentryoffset depending upon FAT type.
<
----------------------------------------------------------------------------*/
RtStatus_t WriteFATentry(int32_t DeviceNum, int32_t FATsector, int32_t FATNtryoffset,
                         int32_t clusterno, int32_t writentry)
{
    int32_t writeFATntry, FAT12word;
    RtStatus_t RetValue;
    int32_t FATentry;
#ifdef ENABLE_WRITE_FAT2
    int32_t Flag = 0;
    int32_t FATsize;
#endif
    uint8_t *buffer;
    uint32_t cacheToken;

    EnterNonReentrantSection();
    ddi_ldl_push_media_task("WriteFATentry");

#ifdef ENABLE_WRITE_FAT2
    /* check whether the second FAT is present or not */
    if (MediaTable[DeviceNum].NoOfFATs == 2)
        Flag = 1;
    FATsize = MediaTable[DeviceNum].FATSize;
#endif
    if (MediaTable[DeviceNum].FATType == FAT12) {
        if ((buffer =
             (uint8_t *) FSReadSector(DeviceNum, FATsector, WRITE_TYPE_RANDOM,
                                      &cacheToken)) == (uint8_t *) 0) {
            ddi_ldl_pop_media_task();
            LeaveNonReentrantSection();
            return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
        }
        if (FATNtryoffset == (MediaTable[DeviceNum].BytesPerSector - 1)) {
            FAT12word = FSGetByte((uint8_t *) buffer, FATNtryoffset);
            FSReleaseSector(cacheToken);
            buffer =
                (uint8_t *) FSReadSector(DeviceNum, FATsector + 1, WRITE_TYPE_RANDOM, &cacheToken);
            FAT12word += (FSGetByte((uint8_t *) buffer, 0) << 8);
        } else {
            FAT12word = FSGetWord((uint8_t *) buffer, FATNtryoffset);
        }
        FSReleaseSector(cacheToken);

        if (clusterno & 0x0001) {
            writeFATntry = writentry << 4;
            FATentry = FAT12word & 0x000F;
        } else {
            writeFATntry = writentry & 0x0FFF;
            FATentry = FAT12word & 0xF000;
        }
        writeFATntry = (writeFATntry | FATentry);

        /* check for boundary condition */
        /* if the offset is at the boundary of a sector then write low byte to the last byte
           of this sector and high byte to the first byte of next sector */

        if (FATNtryoffset == (MediaTable[DeviceNum].BytesPerSector - 1)) {
            FATentry = writeFATntry & 0x00FF;   // low byte 
            if ((RetValue =
                 FSWriteSector(DeviceNum, FATsector, FATNtryoffset, (uint8_t *) & FATentry, 0, 1,
                               WRITE_TYPE_RANDOM)) < 0) {
                ddi_ldl_pop_media_task();
                LeaveNonReentrantSection();
                return RetValue;
            }
#ifdef ENABLE_WRITE_FAT2
            if (Flag == 1)
                if ((RetValue =
                     FSWriteSector(DeviceNum, (FATsector + FATsize), FATNtryoffset,
                                   (uint8_t *) & FATentry, 0, 1, WRITE_TYPE_RANDOM)) < 0) {
                    ddi_ldl_pop_media_task();
                    LeaveNonReentrantSection();
                    return RetValue;
                }
#endif
            FATentry = writeFATntry >> 8;   //  high byte
            if ((RetValue =
                 FSWriteSector(DeviceNum, (FATsector + 1), 0, (uint8_t *) & FATentry, 0, 1,
                               WRITE_TYPE_RANDOM)) < 0) {
                ddi_ldl_pop_media_task();
                LeaveNonReentrantSection();
                return RetValue;
            }
#ifdef ENABLE_WRITE_FAT2
            /* if second FAT is present duplicate the FAT Table */
            if (Flag == 1)
                if ((FSWriteSector
                     (DeviceNum, (FATsector + 1 + FATsize), 0, (uint8_t *) & FATentry, 0, 1,
                      WRITE_TYPE_RANDOM)) < 0) {
                    ddi_ldl_pop_media_task();
                    LeaveNonReentrantSection();
                    return RetValue;
                }
#endif
        } else {
            if ((RetValue =
                 FSWriteSector(DeviceNum, FATsector, FATNtryoffset, (uint8_t *) & writeFATntry, 0,
                               2, WRITE_TYPE_RANDOM)) < 0) {
                ddi_ldl_pop_media_task();
                LeaveNonReentrantSection();
                return RetValue;
            }
#ifdef ENABLE_WRITE_FAT2
            /* if second FAT is present duplicate the FAT Table */
            if (Flag == 1)
                if ((RetValue =
                     FSWriteSector(DeviceNum, (FATsector + FATsize), FATNtryoffset,
                                   (uint8_t *) & writeFATntry, 0, 2, WRITE_TYPE_RANDOM)) < 0) {
                    ddi_ldl_pop_media_task();
                    LeaveNonReentrantSection();
                    return RetValue;
                }
#endif
        }
    }

    else if (MediaTable[DeviceNum].FATType == FAT16) {
        if ((RetValue =
             FSWriteSector(DeviceNum, FATsector, FATNtryoffset, (uint8_t *) & writentry, 0, 2,
                           WRITE_TYPE_RANDOM)) < 0) {
            ddi_ldl_pop_media_task();
            LeaveNonReentrantSection();
            return RetValue;
        }
#ifdef ENABLE_WRITE_FAT2
        /* if second FAT is present duplicate the FAT Table */
        if (Flag == 1)
            if ((RetValue =
                 FSWriteSector(DeviceNum, (FATsector + FATsize), FATNtryoffset,
                               (uint8_t *) & writentry, 0, 2, WRITE_TYPE_RANDOM)) < 0) {
                ddi_ldl_pop_media_task();
                LeaveNonReentrantSection();
                return RetValue;
            }
#endif
    }

    else if (MediaTable[DeviceNum].FATType == FAT32) {
        if ((RetValue =
             FSWriteSector(DeviceNum, FATsector, FATNtryoffset, (uint8_t *) & writentry, 0, 4,
                           WRITE_TYPE_RANDOM)) < 0) {
            ddi_ldl_pop_media_task();
            LeaveNonReentrantSection();
            return RetValue;
        }
#ifdef ENABLE_WRITE_FAT2
        /* if second FAT is present duplicate the FAT Table */
        if (Flag == 1)
            if ((RetValue =
                 FSWriteSector(DeviceNum, (FATsector + FATsize), FATNtryoffset,
                               (uint8_t *) & writentry, 0, 4, WRITE_TYPE_RANDOM)) < 0) {
                ddi_ldl_pop_media_task();
                LeaveNonReentrantSection();
                return RetValue;
            }
#endif
    }
    ddi_ldl_pop_media_task();
    LeaveNonReentrantSection();
    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t ClearCluster(int32_t HandleNumber)

   FunctionType:  Reentrant

   Inputs:        HandleNumber

   Outputs:       Nil

   Description:   Cleares the whole Cluster
<
----------------------------------------------------------------------------*/
RtStatus_t ClearCluster(int32_t HandleNumber)
{
    int32_t Device = Handle[HandleNumber].Device, i, RetValue;
    int32_t SectorNumber = Handle[HandleNumber].CurrentSector;

    for (i = 0; i < MediaTable[Device].SectorsPerCluster; i++) {
        if ((RetValue = FSEraseSector(Device, SectorNumber)) < 0)
            return RetValue;
        SectorNumber++;
    }
    return SUCCESS;
}
