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
 $Archive: /Fatfs/FileSystem/Fat32/device/Readdevicerecord.c $                                        
 $Revision: 11 $                                       
 $Date: 9/18/03 2:41p $                                           
 Description: Readdevicerecord.c
 Notes: This file read provides initialization of Media table
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Includes
----------------------------------------------------------------------------*/
#include <types.h>
#include "fstypes.h"
#include "fat_internal.h"
#include "filesystem/fsapi.h"
#include <string.h>
#include "bootsecoffset.h"
#include "ddi_media.h"
#include "diroffset.h"

/*----------------------------------------------------------------------------
    Extern Declarations
----------------------------------------------------------------------------*/
//extern int32_t Totalfreecluster(int32_t DeviceNum);

/*----------------------------------------------------------------------------

>  Function Name: RtStatus_t Readdevicerecord(int32_t DeviceNum)
 
   FunctionType:  Reentrant

   Inputs:        1)Device number

   Outputs:       SUCCESS else an error

   Description:   Initializes Media Table by reading the Boot sector.
                  If the content of the boot sector cannot be read or
                  verified, then this function just errors out without
                  touching the Media Table.
<
----------------------------------------------------------------------------*/
RtStatus_t Readdevicerecord(int32_t DeviceNum, int32_t SectorNum)
{
    int64_t DataSec;
    int32_t *buf;
    int32_t shift, temp;
    uint32_t cacheToken;
    uint16_t fsInfoSector;
    RtStatus_t rtStatus;

    if ((DeviceNum < 0) || (DeviceNum >= maxdevices)) {
        return ERROR_OS_FILESYSTEM_DEVICE_NOT_SUPPORTED;
    }

    EnterNonReentrantSection();

    /* Read the BootSector */
    if ((buf = FSReadSector(DeviceNum, SectorNum, WRITE_TYPE_RANDOM, &cacheToken)) == (int32_t *) 0) {
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
    }
    // Confirm that this is really the boot sector.
    rtStatus = FileSystemBootSectorVerify((uint8_t *) buf);
    if (SUCCESS != rtStatus) {
        FSReleaseSector(cacheToken);
        LeaveNonReentrantSection();
        return (RtStatus_t) INVALID_FILESYSTEM;
    }

    MediaTable[DeviceNum].DevicePresent = 1;
    MediaTable[DeviceNum].BytesPerSector = FSGetWord((uint8_t *) buf, BYTESPERSECTOROFFSET);
    MediaTable[DeviceNum].SectorsPerCluster = FSGetByte((uint8_t *) buf, SECPERCLUSTEROFFSET);
    MediaTable[DeviceNum].RsvdSectors = FSGetWord((uint8_t *) buf, RSVDSECOFFSET);
    MediaTable[DeviceNum].NoOfFATs = FSGetByte((uint8_t *) buf, NOFATSOFFSET);

    // Make the fat type invalid before we can confirm
    MediaTable[DeviceNum].FATType = FAT_TYPE_INVALID;

    if (MediaTable[DeviceNum].NoOfFATs == 0) {
        FSReleaseSector(cacheToken);
        LeaveNonReentrantSection();
        return (RtStatus_t) INVALID_FILESYSTEM;
    }

    MediaTable[DeviceNum].MaxRootDirEntries = FSGetWord((uint8_t *) buf, ROOTDIRENTRYOFFSET);
    MediaTable[DeviceNum].TotalSectors = FSGetWord((uint8_t *) buf, TOTSECTOROFFSET);
    /* if total sectors are zero then this is FAT32 and find total sectors 
       from total big sector offset */
    if (MediaTable[DeviceNum].TotalSectors == 0)
        MediaTable[DeviceNum].TotalSectors = FSGetDWord((uint8_t *) buf, TOTBIGSECOFFSET);

    if (MediaTable[DeviceNum].TotalSectors == 0) {
        FSReleaseSector(cacheToken);
        LeaveNonReentrantSection();
        return (RtStatus_t) INVALID_FILESYSTEM;
    }

    MediaTable[DeviceNum].FATSize = FSGetWord((uint8_t *) buf, FATSIZEOFFSET);
    /* if FAT size is zero then this is FAT32 and find FAT size 
       from FAT32 size offset */

    MediaTable[DeviceNum].RootdirCluster = 0;

    if (MediaTable[DeviceNum].FATSize == 0) {
        MediaTable[DeviceNum].FATSize = FSGetDWord((uint8_t *) buf, FAT32SIZEOFFSET);
        MediaTable[DeviceNum].RootdirCluster = FSGetDWord((uint8_t *) buf, FAT32ROOTCLUSOFFSET);
    }
    // Read FSInfo sector while we still own the buffer.
    fsInfoSector = FSGetWord((uint8_t *) buf, FAT32FSINFOOFFSET);

    FSReleaseSector(cacheToken);
    LeaveNonReentrantSection();

    if (MediaTable[DeviceNum].FATSize == 0) {
        return (RtStatus_t) INVALID_FILESYSTEM;
    }

    temp = MediaTable[DeviceNum].BytesPerSector * MediaTable[DeviceNum].SectorsPerCluster;
    MediaTable[DeviceNum].ClusterMask = temp - 1;
    shift = 0;
    while (temp >>= 1) {
        shift++;
    }
    MediaTable[DeviceNum].ClusterShift = shift;

    temp = MediaTable[DeviceNum].BytesPerSector;
    shift = 0;
    while (temp >>= 1) {
        shift++;
    }
    MediaTable[DeviceNum].SectorShift = shift;

    MediaTable[DeviceNum].SectorMask = MediaTable[DeviceNum].BytesPerSector - 1;

    // Expected values:
    //  MaxRootDirEntries   = 512 (FAT16) or 0 (FAT32)
    //  SectorShift         = Used to divide by the quantity of bytes in a sector. {512 (FAT16), 2k, or 4k}
    //  RootDirSectors      = 0 or 1.
    //
    MediaTable[DeviceNum].RootDirSectors =
        (MediaTable[DeviceNum].MaxRootDirEntries *
         DIRRECORDSIZE) >> MediaTable[DeviceNum].SectorShift;

    /* First data sector after reserved sectors, primary and secondary FAT table and 
       Root directory sectors */
    MediaTable[DeviceNum].FIRSTDataSector =
        MediaTable[DeviceNum].RsvdSectors +
        (MediaTable[DeviceNum].NoOfFATs * MediaTable[DeviceNum].FATSize) +
        MediaTable[DeviceNum].RootDirSectors;

    /* To determine FATtype find total no of clusters on the volume */
    DataSec = MediaTable[DeviceNum].TotalSectors - (MediaTable[DeviceNum].RsvdSectors +
                                                    (MediaTable[DeviceNum].NoOfFATs *
                                                     MediaTable[DeviceNum].FATSize)
                                                    + MediaTable[DeviceNum].RootDirSectors);

    temp = MediaTable[DeviceNum].SectorsPerCluster;
    shift = 0;
    while (temp >>= 1) {
        shift++;
    }
    MediaTable[DeviceNum].TotalNoofclusters = (DataSec >> shift);

    /* if total data clusters are less than 4085, File system is FAT12 type */
    if (MediaTable[DeviceNum].TotalNoofclusters < 4085) {
        MediaTable[DeviceNum].FATType = FAT12;
    }
    /* if total data clusters are less than 65525, File system is FAT16 type */
    else if (MediaTable[DeviceNum].TotalNoofclusters < 65525) {
        MediaTable[DeviceNum].FATType = FAT16;
    } else {                    /* total data clusters are more than 65525, so File system is FAT32 type */
        MediaTable[DeviceNum].FATType = FAT32;
    }

    if (MediaTable[DeviceNum].FATType == FAT32) {
        DataSec = MediaTable[DeviceNum].RootdirCluster;
        MediaTable[DeviceNum].FirRootdirsec =
            ((DataSec - 2) * MediaTable[DeviceNum].SectorsPerCluster) +
            MediaTable[DeviceNum].FIRSTDataSector;
        MediaTable[DeviceNum].FSInfoSector = fsInfoSector;

        /* Add a fix here for the Win98 support */
        EnterNonReentrantSection();

        /* Write undertermined FSinfo size into the FAT, so that we can force the Win98 
           to compute for free cluster count. This operation should not affect Win2000, WinXP */
        DataSec = 0xFFFFFFFFFFFF;   /* To save some memory let's reuse this variable */

        /* Write FAT32FSIFREECOUNT with 0xffffffff to make it become unknown size for FAT32. 
           Ignore the return code for FSWriteSector because this is not a crucial operation, 
           if it fails we are still OK */

        if (FSWriteSector(DeviceNum, MediaTable[DeviceNum].FSInfoSector, FAT32FSIFREECOUNTOFFSET, (uint8_t *) & DataSec, 0, FAT32FSIFREECOUNTSIZE, WRITE_TYPE_RANDOM) != 0) {;  /* (DebugBuildAssert(0); */
        }
        LeaveNonReentrantSection();
    }
    /* end FAT32 case. */
    /* if FAT Type is FAT12 or FAT16 then root directory starts after reserved sector 
       and primary and secondary FAT table */
    else if ((MediaTable[DeviceNum].FATType == FAT12) || (MediaTable[DeviceNum].FATType == FAT16)) {
        MediaTable[DeviceNum].FirRootdirsec =
            MediaTable[DeviceNum].RsvdSectors +
            (MediaTable[DeviceNum].NoOfFATs * MediaTable[DeviceNum].FATSize);
    }

    /* Modified for i.MX SDK */
    Computefreecluster(DeviceNum);

    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t FSSize(int32_t DeviceNum, int32_t TYPE)

   FunctionType:  Non-Reentrant

   Inputs:        1) Device number
                  2) Type

   Outputs:       File size
<
----------------------------------------------------------------------------*/
int32_t FSSize(int32_t DeviceNum)
{
    int64_t fsize =
        (int64_t) MediaTable[DeviceNum].TotalNoofclusters *
        (int64_t) MediaTable[DeviceNum].SectorsPerCluster *
        (int64_t) MediaTable[DeviceNum].BytesPerSector;
    fsize = fsize >> 20;
    return fsize;
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t FSFreeClusters(int32_t Device)

   FunctionType:  Non-Reentrant

   Inputs:        1) Device number
                   
   Outputs:       TotalFreeClusters
<
//----------------------------------------------------------------------------*/
int32_t FSFreeClusters(int32_t Device)
{
    return MediaTable[Device].TotalFreeClusters;
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t BytesPerCluster(int32_t Device)

   FunctionType:  Non-Reentrant

   Inputs:        1) Device number
                   
   Outputs:       BytesPerCluster
<
//----------------------------------------------------------------------------*/
int32_t BytesPerCluster(int32_t Device)
{
    return (1 << MediaTable[Device].ClusterShift);
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t FSClusterShift(int32_t Device)

   FunctionType:  Non-Reentrant

   Inputs:        1) Device number
                   
   Outputs:       ClusterShift
<
//----------------------------------------------------------------------------*/
int32_t FSClusterShift(int32_t Device)
{
    return (MediaTable[Device].ClusterShift);
}

/*----------------------------------------------------------------------------
>  Function Name: int64_t FSFreeSpace(int32_t Device)

   FunctionType:  Non-Reentrant

   Inputs:        1) Device number
                   
   Outputs:       int64_t FSFreeSpace in bytes or a negative error code.
<
----------------------------------------------------------------------------*/
int64_t FSFreeSpace(int32_t Device)
{
    //!todo Search for better ways to check for Drive's health here. Relates to SDK-1864.
    // Don't just return 0 when FSDriveInit and Computefreecluster() haven't succeeded yet.
    //      .DevicePresent is only set to non-zero by Readdevicerecord().
    // I don't think checking .DevicePresent is a reliable approach though.
    return (int64_t) (((uint64_t) MediaTable[Device].TotalFreeClusters) << MediaTable[Device].
                      ClusterShift);
}

/*----------------------------------------------------------------------------
>  Function Name: int64_t FSFreeSpaceFromHandle(int32_t HandleNumber)

   FunctionType:  Non-Reentrant

   Inputs:        1) Handle number

   Outputs:       FSFreeSpace or 0 for invalid handle
<
----------------------------------------------------------------------------*/
int64_t FSFreeSpaceFromHandle(int32_t HandleNumber)
{
    if (SUCCESS == Handleactive(HandleNumber))
        return FSFreeSpace(Handle[HandleNumber].Device);
    else
        return 0;
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t FSMediaPresent(int32_t DeviceNum)  

   FunctionType:  Non-Reentrant

   Inputs:        1) DeviceNum 
                   
   Outputs:       returns device is present or not
<
----------------------------------------------------------------------------*/
int32_t FSMediaPresent(int32_t DeviceNum)
{
    return MediaTable[DeviceNum].DevicePresent;
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t FSFATType (int32_t DeviceNum)
 
   FunctionType:  Non-Reentrant

   Inputs:        1) DeviceNum 

   Outputs:       Returns FAT type.
<
----------------------------------------------------------------------------*/
int32_t FSFATType(int32_t DeviceNum)
{
    return MediaTable[DeviceNum].FATType;
}

/*----------------------------------------------------------------------------

>  Function Name: RtStatus_t Cleardevicerecord(int32_t DeviceNum)
 
   FunctionType:  Reentrant

   Inputs:        1)Device number

   Outputs:       SUCCESS else an error

   Description:   Clear the device Media Table
<
----------------------------------------------------------------------------*/
RtStatus_t Cleardevicerecord(int32_t DeviceNum)
{

    if ((DeviceNum < 0) || (DeviceNum >= maxdevices))
        return ERROR_OS_FILESYSTEM_DEVICE_NOT_SUPPORTED;

    memset((void *)&MediaTable[DeviceNum], 0, sizeof(FileSystemMediaTable_t));

    return SUCCESS;
}

/*----------------------------------------------------------------------------

>  Function Name: RtStatus_t FileSystemPresent(int32_t DeviceNum)

   FunctionType:  Reentrant

   Inputs:        1) Device number

   Outputs:       Returns 0, if file system found else 
                  ERROR_OS_FILESYSTEM_READSECTOR_FAIL if the PBS cannot be read.
                  or
                  ERROR_OS_FILESYSTEM_FILESYSTEM_NOT_FOUND if the PBS is missing.

   Description:   Determines FAT file system by checking 0xaa55 signature
<
----------------------------------------------------------------------------*/
RtStatus_t FileSystemPresent(int32_t DeviceNum)
{
    uint8_t *buf;
    uint32_t cacheToken;
    RtStatus_t rtStatus = SUCCESS;

    if ((DeviceNum < 0) || (DeviceNum >= maxdevices)) {
        return ERROR_OS_FILESYSTEM_DEVICE_NOT_SUPPORTED;
    }

    EnterNonReentrantSection();
    /* Read the BootSector */
    if ((buf =
         (uint8_t *) FSReadSector(DeviceNum, BOOTSECTOR, WRITE_TYPE_RANDOM,
                                  &cacheToken)) == (uint8_t *) 0) {
        rtStatus = ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
        goto _exit;
    }

    rtStatus = FileSystemBootSectorVerify(buf);

  _exit:
    FSReleaseSector(cacheToken);
    LeaveNonReentrantSection();

    return rtStatus;
}

////////////////////////////////////////////////////////////////////////////////
//! \brief      Check for the standard PBS 0xaa55 signature.
//!
//! \fntype     Function
//!
//! In the given buffer "*buf", this function looks at the standard
//! offset to confirm the presence of the standard sector-0 PBS signature,
//! nominally "0xaa55".
//!
//! \param[in]  buf     Pointer to a buffer containing the contents of sector 0.
//!
//! \retval SUCCESS                                     If the signature is found.
//! \retval ERROR_OS_FILESYSTEM_FILESYSTEM_NOT_FOUND    If not found.
//!
////////////////////////////////////////////////////////////////////////////////
RtStatus_t FileSystemBootSectorVerify(uint8_t * buf)
{
    int32_t signature;

    // To determine whether the filesystem is present or not, get the two bytes of Bootsector
    // at offsets 510 and 511, regardless of the sector size.
    signature = FSGetWord((uint8_t *) buf, BPB_AND_FSI_SIGNATURE_OFFSET_512B_SECTOR);

    /* compare the last two bytes with the signature 0xaa55 */
    if (signature == BOOT_SECTOR_SIGNATURE) {
        return SUCCESS;
    } else {
        return ERROR_OS_FILESYSTEM_FILESYSTEM_NOT_FOUND;
    }

}
