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

///////////////////////////////////////////////////////////////////////////////
//! \addtogroup os_fat_io
//! @brief Low level IO interface for FAT32 driver.
//! @ingroup os_fat
//! @{
//! \file cache_wrappers.c
//! \brief Contains wrappers for the cache read and write calls.
///////////////////////////////////////////////////////////////////////////////

#include "fat_internal.h"
#include "media_cache.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "usdhc/usdhc_ifc.h"
#include <assert.h>

uint32_t g_usdhc_instance = HW_USDHC3;
extern int totalFileOpened;
int cache_line = 32;
typedef struct fat_cache_s {
    uint8_t *buffer;
    uint8_t *token;             // for memory release
    int32_t sector;
    bool isValid;
    int32_t refIndex;
    struct fat_cache_s *next;
} fat_cache_t;

static fat_cache_t *g_fatCache = { 0 };
uint32_t g_u32MbrStartSector = 0;
RtStatus_t FsFlushCache(void *cache);

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

RtStatus_t media_cache_pinned_write(MediaCacheParamBlock_t * pb)
{
    RtStatus_t status;
    status = card_data_read(g_usdhc_instance, (int *)pb->buffer, 512,
                            (pb->sector + g_u32MbrStartSector) * 512);
    status = SUCCESS;

    return status;
}

RtStatus_t media_cache_release(uint32_t token)
{
    free((void *)token);
    return 0;
}

fat_cache_t *fatCacheAllocate(int32_t sector)
{
    /*allocate fat cache */
    fat_cache_t *FatCache = (fat_cache_t *) calloc(1, sizeof(fat_cache_t));
    if (!FatCache)
        return NULL;

    FatCache->token = (uint8_t *) malloc(512 + 2 * cache_line);
    if (!FatCache->token) {
        free(FatCache);
        return NULL;
    } else {
        FatCache->buffer =
            (uint8_t *) (((uint32_t) FatCache->token + cache_line) & (~(cache_line - 1)));
    }
    FatCache->sector = sector;
    FatCache->refIndex = totalFileOpened;
    FatCache->isValid = 0;

    /*add the fat cache into list */
    if (!g_fatCache) {
        g_fatCache = FatCache;
    } else {
        /*add to the tail */
        fat_cache_t *tmpFatCache = g_fatCache;
        while (tmpFatCache->next)
            tmpFatCache = tmpFatCache->next;

        tmpFatCache->next = FatCache;
    }

    return FatCache;
}

void updateFatCacheRefIndex(int32_t index)
{
    fat_cache_t *tmpFatCache = g_fatCache;

    while (tmpFatCache) {
        if (tmpFatCache->refIndex > index) {
            tmpFatCache->refIndex--;
        }

        tmpFatCache = tmpFatCache->next;
    }
}

void *getFatCache(int32_t sector)
{
    fat_cache_t *FatCache = NULL, *tmpFatCache = g_fatCache, *lastUnusedCache = NULL;

    if (sector == -1)           // allocate new
    {
        FatCache = fatCacheAllocate(sector);
        return (void *)FatCache;
    }

    /*find the cache from existing list */
    while (tmpFatCache) {
        if (tmpFatCache->sector == sector) {
            FatCache = tmpFatCache;
            updateFatCacheRefIndex(FatCache->refIndex);
            FatCache->refIndex = totalFileOpened;   // tag the found cache as recently used
            FatCache->isValid = 1;
            return (void *)FatCache;
        }

        if (tmpFatCache->refIndex == 0)
            lastUnusedCache = tmpFatCache;

        tmpFatCache = tmpFatCache->next;
    }

    if (!lastUnusedCache)       // Empty Cache list
    {
        lastUnusedCache = fatCacheAllocate(sector);
    } else {
        //flush the cache to be updated
        FsFlushCache(lastUnusedCache);
        lastUnusedCache->isValid = 0;   // need to reload
        updateFatCacheRefIndex(lastUnusedCache->refIndex);
        lastUnusedCache->refIndex = totalFileOpened;
    }

    lastUnusedCache->sector = sector;

    return (void *)lastUnusedCache;
}

void fatCacheRelease(void *FatCache)
{
    fat_cache_t *tmpFatCache = (fat_cache_t *) FatCache;
    if (!tmpFatCache)           // release the least used
    {
        tmpFatCache = g_fatCache;
        while (tmpFatCache) {
            if (tmpFatCache->refIndex == 0)
                break;
            tmpFatCache = tmpFatCache->next;
        }
    }

    fat_cache_t *tmp = g_fatCache;
    /*Flush all fat cache */
    while (tmp) {
        FsFlushCache(tmp);
        tmp = tmp->next;
    }

    /*remove the fat cache in the cache list */
    tmp = g_fatCache;
    if (g_fatCache == tmpFatCache) {
        g_fatCache = g_fatCache->next;
    } else {
        while (tmp->next != tmpFatCache)
            tmp = tmp->next;

        tmp->next = tmpFatCache->next;
    }
    updateFatCacheRefIndex(tmpFatCache->refIndex);

    /*free the cache memory */
    free(tmpFatCache->token);
    free(tmpFatCache);
}

//! \brief Determines if a sector is within the first FAT.
static bool IsFATSector(uint32_t drive, uint32_t sector)
{
    uint32_t start = MediaTable[drive].RsvdSectors + g_u32MbrStartSector;
    uint32_t end = start + MediaTable[drive].FATSize;
    return (sector >= start) && (sector < end);
}

void print_media_fat_info(uint32_t DeviceNum)
{
    printf("BytesPerSector = %X\n", MediaTable[DeviceNum].BytesPerSector);
    printf("SectorsPerCluster = %X\n", MediaTable[DeviceNum].SectorsPerCluster);
    printf("RsvdSectors = %X\n", MediaTable[DeviceNum].RsvdSectors);
    printf("NoOfFATs = %X\n", MediaTable[DeviceNum].NoOfFATs);
    printf("MaxRootDirEntries = %X\n", MediaTable[DeviceNum].MaxRootDirEntries);
    printf("TotalSectors = %X\n", MediaTable[DeviceNum].TotalSectors);
    printf("FATSize = %X\n", MediaTable[DeviceNum].FATSize);
    printf("RootdirCluster = %X\n", MediaTable[DeviceNum].RootdirCluster);
    printf("NextFreeCluster = %X\n", MediaTable[DeviceNum].NextFreeCluster);
    printf("TotalFreeClusters = %X\n", MediaTable[DeviceNum].TotalFreeClusters);
    printf("RootDirSectors = %X\n", MediaTable[DeviceNum].RootDirSectors);
    printf("FIRSTDataSector = %X\n", MediaTable[DeviceNum].FIRSTDataSector);
    printf("FATType = %X\n", MediaTable[DeviceNum].FATType);
    printf("TotalNoofclusters = %X\n", MediaTable[DeviceNum].TotalNoofclusters);
    printf("ClusterMask = %X\n", MediaTable[DeviceNum].ClusterMask);
    printf("ClusterShift = %X\n", MediaTable[DeviceNum].ClusterShift);
    printf("SectorShift = %X\n", MediaTable[DeviceNum].SectorShift);
    printf("SectorMask = %X\n", MediaTable[DeviceNum].SectorMask);
    printf("DevicePresent = %X\n", MediaTable[DeviceNum].DevicePresent);
    printf("FirRootdirsec = %X\n", MediaTable[DeviceNum].FirRootdirsec);
    printf("FSInfoSector = %X\n", MediaTable[DeviceNum].FSInfoSector);
}

RtStatus_t FsFlushCache(void *cache)
{
    int sectorSize = 512;
    fat_cache_t *fatCache = (fat_cache_t *) cache;

    if (fatCache->isValid == FALSE)
        return SUCCESS;

    card_wait_xfer_done(g_usdhc_instance);
    card_data_write(g_usdhc_instance, (int *)fatCache->buffer, sectorSize,
                    fatCache->sector * sectorSize);
    card_wait_xfer_done(g_usdhc_instance);

    fatCache->isValid = FALSE;

    return SUCCESS;
}

/*this is only for single sector!!*/
RtStatus_t FSWriteSector(int32_t deviceNumber, int32_t sectorNumber, int32_t destOffset,
                         uint8_t * sourceBuffer, int32_t sourceOffset, int32_t numBytesToWrite,
                         int32_t writeType)
{
    assert(deviceNumber == 0);
    RtStatus_t status;
    uint32_t sectorSize = MediaTable[deviceNumber].BytesPerSector;
    uint8_t *buffer;
    int writeSize = 0;
    int destAddrOffset = (sectorNumber + g_u32MbrStartSector) * sectorSize;

    // Handle FAT cache.
    bool isFat = false;
    isFat = IsFATSector(deviceNumber, sectorNumber + g_u32MbrStartSector);
    fat_cache_t *fatCache = NULL;

    /*Note:  destination and write size should be align with the sector size */
    if ((numBytesToWrite % sectorSize) || destOffset) {
        writeSize = sectorSize; // this is for single sector reading

        if (isFat) {
            fatCache = (fat_cache_t *) getFatCache(sectorNumber + g_u32MbrStartSector);
            if (fatCache->isValid)  // already in RAM
            {
                /*copy the fat entry into the cache */
                memcpy((uint8_t *) ((uint32_t) fatCache->buffer + destOffset),
                       (uint8_t *) (sourceBuffer + sourceOffset), numBytesToWrite);
                return SUCCESS;
            } else {
                card_wait_xfer_done(g_usdhc_instance);
                status =
                    card_data_read(g_usdhc_instance, (int *)fatCache->buffer, writeSize,
                                   destAddrOffset);
                card_wait_xfer_done(g_usdhc_instance);
                memcpy((uint8_t *) ((uint32_t) fatCache->buffer + destOffset),
                       (uint8_t *) (sourceBuffer + sourceOffset), numBytesToWrite);
                return SUCCESS;
            }
        } else {
            uint8_t *buffer_token = (uint8_t *) malloc(sectorSize + 2 * cache_line);
            if (!buffer_token) {
                return FAIL;
            } else {
                buffer = (uint8_t *) (((uint32_t) buffer_token + cache_line) & (~(cache_line - 1)));
            }

            card_wait_xfer_done(g_usdhc_instance);
            status = card_data_read(g_usdhc_instance, (int *)buffer, writeSize, destAddrOffset);
            card_wait_xfer_done(g_usdhc_instance);

            memcpy((uint8_t *) ((uint32_t) buffer + destOffset),
                   (uint8_t *) (sourceBuffer + sourceOffset), numBytesToWrite);
            status = card_data_write(g_usdhc_instance, (int *)buffer, writeSize, destAddrOffset);
            card_wait_xfer_done(g_usdhc_instance);
            free(buffer_token);
        }
    } else {
        writeSize = numBytesToWrite;
        card_wait_xfer_done(g_usdhc_instance);
        status =
            card_data_write(g_usdhc_instance, (int *)(sourceBuffer + sourceOffset), writeSize,
                            destAddrOffset);
        card_wait_xfer_done(g_usdhc_instance);  // wait tranfer done is import since the buffer will be release after return

    }

    status = SUCCESS;

    return status;
}

RtStatus_t FSWriteMultiSectors(int32_t deviceNumber, int32_t sectorNumber, int32_t writeType,
                               uint8_t * buffer, int size)
{
    assert(deviceNumber == 0);

    int status = 0;
    uint32_t actualSectorNumber = sectorNumber + g_u32MbrStartSector;
    uint32_t sectorSize = MediaTable[deviceNumber].BytesPerSector;

    card_wait_xfer_done(g_usdhc_instance);
    status = card_data_write(g_usdhc_instance, (int *)buffer, size,
                             actualSectorNumber * sectorSize);
    card_wait_xfer_done(g_usdhc_instance);

    return SUCCESS;
}

// Used only in clearcluster() in the FAT filesystem. Can replace with call to writesector.
RtStatus_t FSEraseSector(int32_t deviceNumber, int32_t sectorNumber)
{
    RtStatus_t status;
    uint8_t *buffer;

    // Acquire a buffer to hold the empty sector.
    uint32_t bufferSize = MediaTable[deviceNumber].BytesPerSector;
    uint8_t *buffer_token = (uint8_t *) malloc(bufferSize + 2 * cache_line);
    if (!buffer_token) {
        return FAIL;
    } else {
        buffer = (uint8_t *) (((uint32_t) buffer_token + cache_line) & (~(cache_line - 1)));
    }

    // Clear the sector buffer to all zeroes.
    memset(buffer, 0, MediaTable[deviceNumber].BytesPerSector);

    status = FSWriteSector(deviceNumber, sectorNumber, 0, buffer, 0, bufferSize, 0);

    // Let go of the sector buffer.
    free(buffer_token);

    return status;
}

int32_t *FSReadSector(int32_t deviceNumber, int32_t sectorNumber, int32_t writeType,
                      uint32_t * token)
{
    assert(deviceNumber == 0);

    int status = 0;
    uint32_t actualSectorNumber = sectorNumber + g_u32MbrStartSector;
    uint32_t sectorSize = MediaTable[deviceNumber].BytesPerSector;
    fat_cache_t *fatCache = NULL;
    uint8_t *buffer = NULL;

    // Handle FAT cache.
    bool isFat = false;
    isFat = IsFATSector(deviceNumber, actualSectorNumber);
    if (isFat) {
        fatCache = (fat_cache_t *) getFatCache(actualSectorNumber);
        *token = 0;
        if (fatCache->isValid)  // already in RAM
            return (int32_t *) fatCache->buffer;
        else
            buffer = fatCache->buffer;
    } else {
        /* Not a fat sector, allocate a new buffer that will be released by FSReleaseSector() */
        buffer = (uint8_t *) malloc(sectorSize + 2 * cache_line);
        if (!buffer) {
            return NULL;
        } else {
            *token = (uint32_t) buffer;
            buffer = (uint8_t *) ((*token + cache_line) & (~(cache_line - 1))); // align the buffer
        }
    }

    card_wait_xfer_done(g_usdhc_instance);
    status = card_data_read(g_usdhc_instance, (int *)buffer, sectorSize,
                            actualSectorNumber * sectorSize);
    card_wait_xfer_done(g_usdhc_instance);

    // Give the caller the token so they can release the cache entry.
    if (status) {
        if (!isFat) {
            free((void *)(*token));
        }
        // An error occurred, so return NULL.
        return NULL;
    }

    if (isFat)                  // tag the Cache
    {
        fatCache->isValid = TRUE;
    }

    return (int32_t *) buffer;

}

/*! Note: multiple sectors reading is only for big data chunks, ignoring the FAT table fetching
 *	the buffer is reused from outside allocation, so need to use the token for further memory recycling.
 */
int32_t *FSReadMultiSectors(int32_t deviceNumber, int32_t sectorNumber, int32_t writeType,
                            uint8_t * buffer, int size)
{
    assert(deviceNumber == 0);

    int status = 0;
    uint32_t actualSectorNumber = sectorNumber + g_u32MbrStartSector;
    uint32_t sectorSize = MediaTable[deviceNumber].BytesPerSector;

    card_wait_xfer_done(g_usdhc_instance);
    status = card_data_read(g_usdhc_instance, (int *)buffer, size, actualSectorNumber * sectorSize);

    return (int32_t *) (buffer);
}

RtStatus_t FSReleaseSector(uint32_t token)
{
    if (token) {
        free((void *)token);
    }
    return SUCCESS;
}

RtStatus_t FSFlushSector(int32_t deviceNumber, int32_t sectorNumber, int32_t writeType, int32_t ix,
                         int32_t * writeFlag)
{
    return SUCCESS;
}

RtStatus_t FlushCache(void)
{
    return SUCCESS;
}

RtStatus_t FSFlushDriveCache(int32_t deviceNumber)
{
    return FlushCache();
}

////////////////////////////////////////////////////////////////////////////////
//! \brief Verify if the supplied sector contains valid fields of a
//!        Partition Boot Sector. Internal function.
//! \param[in] pSectorBuffer - Sector Data (presumably of a Partition Boot Sector)
//!
//! \retval SUCCESS
//! \retval ERROR_OS_FILESYSTEM_FILESYSTEM_NOT_FOUND 
//! \internal
////////////////////////////////////////////////////////////////////////////////
RtStatus_t VerifyPBS(uint8_t * pSectorData)
{
    uint32_t u8SecValue = 1;
    uint8_t u8SecPerClus = pSectorData[0x0d];
    uint32_t i;

    // Verify that the Sectors Per Cluster field is a power of 2 value
    for (i = 0; i < 8; i++) {
        if (u8SecPerClus == u8SecValue) {
            break;
        }
        u8SecValue <<= 1;
    }

    if ((u8SecValue == 256) || ((pSectorData[0] != 0xEB) && (pSectorData[0] != 0xE9))) {
        return ERROR_OS_FILESYSTEM_FILESYSTEM_NOT_FOUND;
    }
    // Verify the Boot Sector signature field (should be 0xAA55)
    if (((pSectorData[0x1fe] == 0x55) && (pSectorData[0x1ff] == 0xAA)) ||
        ((pSectorData[0x7fe] == 0x55) && (pSectorData[0x7ff] == 0xAA))) {
        return SUCCESS;
    }

    return ERROR_OS_FILESYSTEM_FILESYSTEM_NOT_FOUND;
}

RtStatus_t FSDataDriveInit(DriveTag_t tag)
{
    uint32_t u32PbsTotalSectors;
    uint32_t ProbablePBSFlag = 0;
    uint8_t *pSectorData;
    RtStatus_t retval = SUCCESS;
    uint32_t pbsOffset;
    uint32_t token;

    /*Note by Ray: in this function, intialize the uSDHC controller */
    retval = card_init(g_usdhc_instance, 8);
    if (retval == 1) {
        return 1;
    }
    set_card_access_mode(1, 0);

    /* initialize with a default value before getting size from FAT table */
    MediaTable[(int)tag].BytesPerSector = 512;
    // Reset partition offset.
    g_u32MbrStartSector = 0;

    // First read sector 0
    pSectorData = (uint8_t *) FSReadSector(tag, 0, 0, &token);
    if (retval != SUCCESS || pSectorData == 0) {
        return ERROR_OS_FILESYSTEM_FILESYSTEM_NOT_FOUND;
    }
    // First, extract the assumed start sector. We don't want to set the g_u32MbrStartSector
    // global yet, because ReadSector() uses MediaRead(), which offsets based on that global's
    // value. Thus, we'd get a double offset when trying to read the PBS. maybe this is not enough
    // to determine if a sector is MBR or DBR, need to investigate more!!!
    /* Check the first sector is DBR or MBR. for removable disk there might be no MBR section */
    if ((pSectorData[0x00] == 0xEB) && (pSectorData[0x02] == 0x90) && (pSectorData[0x0E] == 0x20))  // JMP NOP indicates this is DBR
    {
        pbsOffset = 0x0;
    } else {
        pbsOffset =
            pSectorData[0x1c6] + (pSectorData[0x1c7] << 8) + (pSectorData[0x1c8] << 16) +
            (pSectorData[0x1c9] << 24);
    }

    FSReleaseSector(token);

    // Now read what may be the first sector of the first partition
    pSectorData = (uint8_t *) FSReadSector(tag, pbsOffset, 0, &token);
    if (retval != SUCCESS || pSectorData == 0) {
        // The read failed, hence we might not have this sector as MBR, assume PBS
        ProbablePBSFlag = 1;
    } else {
        if ((retval = VerifyPBS(pSectorData)) != SUCCESS) {
            // The verification failed, so assume PBS
            ProbablePBSFlag = 1;
        }
    }

    FSReleaseSector(token);

    // Ok, so Sector 0 might be a PBS, verify that this is indeed the case.
    if (ProbablePBSFlag == 1) {
        pbsOffset = 0;

        pSectorData = (uint8_t *) FSReadSector(tag, pbsOffset, 0, &token);
        if (retval != SUCCESS || pSectorData == 0) {
            // Not necessary to media_cache_release() here, because the read failed.

            retval = ERROR_OS_FILESYSTEM_FILESYSTEM_NOT_FOUND;
            return retval;
        }

        if ((retval = VerifyPBS(pSectorData)) != SUCCESS) {
            FSReleaseSector(token);
            return retval;
        }

        FSReleaseSector(token);
    } else {
        /* it usually ends here */
        g_u32MbrStartSector = pbsOffset;
    }

    // Get Total Sectors from PBS (first look at small 2-byte count field at 0x13&0x14)
    u32PbsTotalSectors = pSectorData[0x13] + (pSectorData[0x14] << 8);

    if (u32PbsTotalSectors == 0) {
        // Total Sectors is in the large 4-byte count field beginning at 0x20
        u32PbsTotalSectors =
            pSectorData[0x20] + (pSectorData[0x21] << 8) + (pSectorData[0x22] << 16) +
            (pSectorData[0x23] << 24);
    }

    if (u32PbsTotalSectors == 0) {
        return ERROR_OS_FILESYSTEM_FILESYSTEM_NOT_FOUND;
    }

    return SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
//! @}
