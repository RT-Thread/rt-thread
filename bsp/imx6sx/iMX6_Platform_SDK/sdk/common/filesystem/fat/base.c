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
 $Archive: /Fatfs/FileSystem/Fat32/base/Fcreate.c $
 $Revision: 18 $                                       
 $Date: 9/18/03 7:14p $
 Description: Fcreate.c
 Notes:	
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
		File Includes
----------------------------------------------------------------------------*/
#include <types.h>
#include "fstypes.h"
#include "filesystem/fsapi.h"
#include "usdhc/usdhc_ifc.h"
#include "fat_internal.h"
#include "diroffset.h"
#include <string.h>

#define INVALID_CLUSTER     0x7fffffff

/*----------------------------------------------------------------------------

>  Function Name: RtStatus_t Fcreate(int32_t HandleNumber,uint8_t *FileName,int32_t stringtype,int32_t length,int32_t index)

   FunctionType:  Reentrant

   Inputs:        1)HandleNumber
                  2)Pointer to File Name
                  3)stringtype
                  4)length
                  5)index

   Outputs:       Returns HandleNumber if Success, or ERROR Code if  Error Occurs

   Description:   Creates a new file in a given directory

<
----------------------------------------------------------------------------*/
RtStatus_t Fcreate(int32_t HandleNumber, uint8_t * FileName, int32_t stringtype, int32_t length,
                   int32_t index)
{
    RtStatus_t RetValue = SUCCESS;
    uint8_t UnicodeBuffer[MAX_UNICODE_SIZE];

    EnterNonReentrantSection();
    if ((Handle[HandleNumber].Mode & READ_MODE) != READ_MODE) {
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_DIRECTORY_IS_NOT_WRITABLE;
    }

    ddi_ldl_push_media_task("Fcreate");

    if ((RetValue =
         CreateDirRecord(FileName, HandleNumber, 0, ARCHIVE, stringtype, length, index,
                         UnicodeBuffer, 0)) < 0) {
        ddi_ldl_pop_media_task();
        LeaveNonReentrantSection();
        return RetValue;
    }

    if (Handle[HandleNumber].StartingCluster != 0) {
        if ((RetValue = Fseek(HandleNumber, -DIRRECORDSIZE, SEEK_CUR)) < 0) {
            ddi_ldl_pop_media_task();
            LeaveNonReentrantSection();
            return RetValue;
        }
    }

    Handle[HandleNumber].FileSize = 0;
    UpdateHandle(HandleNumber, 0);

    LeaveNonReentrantSection();
    ddi_ldl_pop_media_task();
    return SUCCESS;
}

/*----------------------------------------------------------------------------

>  Function Name:  RtStatus_t  Fflush(int32_t HandleNumber)

   FunctionType:  Reentrant

   Inputs:        1)HandleNumber

   Outputs:       Returns 0 if Success Else an ErrorCode

   Description:   Flushes the Buffer

<
----------------------------------------------------------------------------*/
RtStatus_t Fflush(int32_t HandleNumber)
{
    RtStatus_t RetValue;
    int32_t i32WriteFlag = 0;
    uint32_t filesizeread, *readBuffer, fsizeoffset;
    uint32_t cacheToken;

    if ((HandleNumber < 0) || (HandleNumber >= maxhandles)) {
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;
    }

    if ((RetValue = Handleactive(HandleNumber)) < 0) {
        return ERROR_OS_FILESYSTEM_HANDLE_NOT_ACTIVE;
    }

    ddi_ldl_push_media_task("Fflush");

    if ((RetValue =
         FSFlushSector(Handle[HandleNumber].Device, Handle[HandleNumber].CurrentSector,
                       WRITE_TYPE_RANDOM, -1, &i32WriteFlag)) < 0) {
        ddi_ldl_pop_media_task();
        return RetValue;
    }

    EnterNonReentrantSection();
    if ((readBuffer =
         (uint32_t *) FSReadSector(Handle[HandleNumber].Device, Handle[HandleNumber].DirSector,
                                   WRITE_TYPE_RANDOM, &cacheToken)) <= 0) {
        ddi_ldl_pop_media_task();
        LeaveNonReentrantSection();
        return RetValue;
    }

    fsizeoffset = (DIR_FILESIZEOFFSET + Handle[HandleNumber].diroffset) / sizeof(uint32_t);
    filesizeread = *(readBuffer + fsizeoffset);

    FSReleaseSector(cacheToken);

    LeaveNonReentrantSection();

    if (filesizeread != Handle[HandleNumber].FileSize) {
        if ((RetValue = UpdateFileSize(HandleNumber, 0)) < 0) {
            return ERROR_OS_FILESYSTEM_EOF;
        }

        if ((RetValue = FSWriteSector(Handle[HandleNumber].Device, Handle[HandleNumber].DirSector,
                                      DIR_FILESIZEOFFSET + Handle[HandleNumber].diroffset,
                                      (uint8_t *) & Handle[HandleNumber].FileSize, 0, 4,
                                      WRITE_TYPE_RANDOM)) < 0) {
            ddi_ldl_pop_media_task();
            return RetValue;
        }
    }

    if (i32WriteFlag == 1) {
        if ((RetValue = FSFlushDriveCache(Handle[HandleNumber].Device)) != SUCCESS) {
            ddi_ldl_pop_media_task();
            return RetValue;
        }
    }
    ddi_ldl_pop_media_task();
    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t GetFileSize(int32_t HandleNumber)

   FunctionType:  Reentrant

   Inputs:        1)HandleNumber

   Outputs:       Returns 0 or ERROR Code if  Error Occurs

   Description:   Gets the size of the File

<
----------------------------------------------------------------------------*/
RtStatus_t GetFileSize(int32_t HandleNumber)
{
    RtStatus_t RetValue;

    EnterNonReentrantSection();

    if ((HandleNumber < 0) || (HandleNumber >= maxhandles)) {
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;
    }

    if ((RetValue = Handleactive(HandleNumber)) < 0) {
        LeaveNonReentrantSection();
        return RetValue;
    }

    LeaveNonReentrantSection();
    return Handle[HandleNumber].FileSize;
}

/*----------------------------------------------------------------------------

>  Function Name: RtStatus_t Fread(int32_t HandleNumber, uint8_t *Buffer, int32_t NumBytesToRead)

   FunctionType:  Reentrant

   Inputs:        1)HandleNumber
                  2)Pointer to Buffer
                  3)Number of Bytes To Read

   Outputs:       Returns Number of bytes read upon success or 
                                 0 upon failures - ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED,
                                                        ERROR_OS_FILESYSTEM_INVALID_MODE,
                                                        NumBytesToRead < 0,
                                                        ERROR_OS_FILESYSTEM_EOF,
                                                        ERROR_OS_FILESYSTEM_HANDLE_NOT_ACTIVE

   Description:   Reads the Specified number of Bytes from the FILE

<
----------------------------------------------------------------------------*/
RtStatus_t Fread_FAT(int32_t HandleNumber, uint8_t * Buffer, int32_t NumBytesToRead)
{
    RtStatus_t RetValue = SUCCESS;
    uint8_t *buf;
    int32_t FileSize, RemainBytesToRead;
    int32_t Device, BuffOffset = 0, BytesToCopy;
    int32_t RemainBytesInSector, BytesPerSector;
    uint32_t cacheToken;

    if ((HandleNumber < 0) || (HandleNumber >= maxhandles)) {
        // Error - ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED 
        return 0;
    }

    Device = Handle[HandleNumber].Device;
    BytesPerSector = MediaTable[Device].BytesPerSector;

    if ((RetValue = Handleactive(HandleNumber)) < 0) {
        Handle[HandleNumber].ErrorCode = RetValue;
        return 0;
    }

    if ((Handle[HandleNumber].Mode & READ_MODE) != READ_MODE) {
        Handle[HandleNumber].ErrorCode = ERROR_OS_FILESYSTEM_INVALID_MODE;
        return 0;
    }
    // We treat directories as files, so a special read mode for these.
    if (Handle[HandleNumber].Mode & DIRECTORY_MODE) {
        FileSize = 0x7fffffff;  // Set the file size as the largest +ve number
    } else {
        FileSize = GET_FILE_SIZE(HandleNumber);
    }

    if (FileSize < (NumBytesToRead + Handle[HandleNumber].CurrentOffset)) {
        Handle[HandleNumber].ErrorCode = ERROR_OS_FILESYSTEM_EOF;
        NumBytesToRead = FileSize - Handle[HandleNumber].CurrentOffset;
    }

    RemainBytesToRead = NumBytesToRead;
    if (RemainBytesToRead < 0) {
        return 0;
    }
    // On EOF
    if (NumBytesToRead == 0) {
        Handle[HandleNumber].ErrorCode = ERROR_OS_FILESYSTEM_EOF;
        return 0;
    }

    ddi_ldl_push_media_task("Fread_FAT");

    RemainBytesInSector = BytesPerSector - Handle[HandleNumber].BytePosInSector;

    while (RemainBytesToRead > 0) {
        if (((RemainBytesInSector != 0) && (RemainBytesToRead > RemainBytesInSector)) ||
            (RemainBytesToRead <= BytesPerSector)) {
            /*if the start point of the data is not aligned to sector, read a single sector and get the data */
            if (((RemainBytesInSector != 0) && (RemainBytesToRead > RemainBytesInSector))) {
                BytesToCopy = RemainBytesInSector;
                RemainBytesInSector = 0;
            } else {
                BytesToCopy = RemainBytesToRead;
            }

            if ((RetValue = UpdateHandleOffsets(HandleNumber))) {
                Handle[HandleNumber].ErrorCode = RetValue;
                ddi_ldl_pop_media_task();
                return (NumBytesToRead - RemainBytesToRead);
            }

            EnterNonReentrantSection();
            if ((buf =
                 (uint8_t *) FSReadSector(Device, Handle[HandleNumber].CurrentSector,
                                          WRITE_TYPE_RANDOM, &cacheToken)) == (uint8_t *) 0) {
                Handle[HandleNumber].ErrorCode = ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
                LeaveNonReentrantSection();
                ddi_ldl_pop_media_task();

                return NumBytesToRead - RemainBytesToRead;  // READSECTOR_FAIL return here in 2.6 version fixes mmc eject bug 7183.
            }

            RemainBytesToRead -= BytesToCopy;

            memcpy(Buffer + BuffOffset, buf + Handle[HandleNumber].BytePosInSector, BytesToCopy);

            FSReleaseSector(cacheToken);
            LeaveNonReentrantSection();

            Handle[HandleNumber].CurrentOffset += BytesToCopy;
            Handle[HandleNumber].BytePosInSector += BytesToCopy;

            BuffOffset += BytesToCopy;
        } else {
            /*Multiple sectors read for large chunk of data */
            int sectorNum = 0, sectorStart = 0;
            int prevSectorPos = 0, prevSectorIndex = 0, sectorToBeRead = 0, prevClusterIndex = 0;
            BytesToCopy = RemainBytesToRead - RemainBytesToRead % BytesPerSector;   // need to aligned to sector
            sectorNum = BytesToCopy / BytesPerSector;

            while (sectorNum--) {
                Handle[HandleNumber].BytePosInSector = BytesPerSector;  //always aligned to sector

                if ((RetValue = UpdateHandleOffsets(HandleNumber))) // increase the sector address by 1
                {
                    Handle[HandleNumber].ErrorCode = RetValue;
                    ddi_ldl_pop_media_task();
                    return (NumBytesToRead - RemainBytesToRead);
                }

                if (sectorStart == 0) {
                    sectorStart = Handle[HandleNumber].CurrentSector;
                    prevSectorIndex = Handle[HandleNumber].CurrentSector;
                    prevClusterIndex = Handle[HandleNumber].CurrentCluster;
                    sectorToBeRead++;
                    continue;
                }

                if (prevSectorIndex + 1 == Handle[HandleNumber].CurrentSector) {    /*adjacent sectors */
                    sectorToBeRead++;
                    prevSectorIndex = Handle[HandleNumber].CurrentSector;
                    prevClusterIndex = Handle[HandleNumber].CurrentCluster;
                    prevSectorPos = Handle[HandleNumber].SectorPosInCluster;
                } else {
                    /*backwards to the previous sector index, if the sector is not continous in physical address. */
                    Handle[HandleNumber].CurrentSector = prevSectorIndex;
                    Handle[HandleNumber].CurrentCluster = prevClusterIndex;
                    Handle[HandleNumber].SectorPosInCluster = prevSectorPos;
                    break;
                }
            }

            BytesToCopy = sectorToBeRead * BytesPerSector;

            EnterNonReentrantSection();

            /*reuse the buffer to avoid extra memory copy */
            if ((buf = (uint8_t *) FSReadMultiSectors(Device, sectorStart, WRITE_TYPE_RANDOM,
                                                      (uint8_t *) (Buffer + BuffOffset),
                                                      BytesToCopy)) == (uint8_t *) 0) {
                Handle[HandleNumber].ErrorCode = ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
                LeaveNonReentrantSection();
                ddi_ldl_pop_media_task();

                return NumBytesToRead - RemainBytesToRead;  // READSECTOR_FAIL return here in 2.6 version fixes mmc eject bug 7183.
            }

            RemainBytesToRead -= BytesToCopy;

            Handle[HandleNumber].CurrentOffset += BytesToCopy;

            Handle[HandleNumber].BytePosInSector = BytesPerSector;  //always aligned to sector

            LeaveNonReentrantSection();

            BuffOffset += BytesToCopy;
        }
    }

    ddi_ldl_pop_media_task();

    // Force to RtStatus - all errors are negative so this will still work.
    return (RtStatus_t) NumBytesToRead;
}

/*----------------------------------------------------------------------------

>  Function Name: RtStatus_t Fwrite(int32_t HandleNumber, 
                       uint8_t *Buffer, 
                       int32_t NumBytesToWrite,
                      )

   FunctionType:  Reentrant

   Inputs:        1)HandleNumber
                  2)Pointer to Buffer
                  3)Number of Bytes To Write

   Outputs:       Returns   Number of bytes written upon success or
                                   0 upon failures - ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED,
                                                          ERROR_OS_FILESYSTEM_INVALID_MODE,
                                                          NumBytesToWrite <= 0,
                                                          ERROR_OS_FILESYSTEM_HANDLE_NOT_ACTIVE,
                                                          ERROR_OS_FILESYSTEM_NO_FREE_CLUSTER,
                                                          ERROR_OS_FILESYSTEM_INVALID_CLUSTER_NO

   Description:   Writes the Specified number of Bytes to the FILE

<
----------------------------------------------------------------------------*/
RtStatus_t Fwrite_FAT(int32_t HandleNumber, uint8_t * Buffer, int32_t NumBytesToWrite)
{
    int32_t BytesToCopy, clusterlo, clusterhi;
    RtStatus_t RetValue = SUCCESS;
    int32_t Device, BytesPerSector, RemainBytesInSector, Mode;
    int32_t BuffOffset = 0, clusterno;
    int32_t RemainBytesToWrite = NumBytesToWrite, FileSize = 0;
    if ((HandleNumber < 0) || (HandleNumber >= maxhandles)) {
        // Error - ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED
        return 0;
    }
    if (NumBytesToWrite <= 0)
        return 0;

    Device = Handle[HandleNumber].Device;
    BytesPerSector = MediaTable[Device].BytesPerSector;
    if ((RetValue = Handleactive(HandleNumber)) < 0) {
        Handle[HandleNumber].ErrorCode = RetValue;
        return 0;
    }
    if (((Handle[HandleNumber].Mode) & WRITE_MODE) != WRITE_MODE) {
        Handle[HandleNumber].ErrorCode = ERROR_OS_FILESYSTEM_INVALID_MODE;
        return 0;
    }
    ddi_ldl_push_media_task("Fwrite_FAT");

    /* If zero length file is opened, its starting cluster is zero, so we have to
       allocate one cluster to the file and update the directory record */
    if ((Handle[HandleNumber].StartingCluster) == 0) {
        if ((clusterno = FirstfreeAndallocate(Device)) < 0) {
            ddi_ldl_pop_media_task();
            return 0;
        }
        Handle[HandleNumber].StartingCluster = clusterno;
        Handle[HandleNumber].CurrentCluster = clusterno;
        Handle[HandleNumber].CurrentSector = Firstsectorofcluster(Device, clusterno);
        clusterlo = clusterno & 0x00ffff;
        clusterhi = (int32_t) ((clusterno >> 16) & 0x00ffff);

        //! todo - check this - RetValue wasn't being set previously.
        //if((RetValue = myFSWriteSector(Device,
        if ((RetValue = FSWriteSector(Device,
                                      Handle[HandleNumber].DirSector,
                                      (Handle[HandleNumber].diroffset + DIR_FSTCLUSLOOFFSET),
                                      (uint8_t *) & clusterlo, 0, 2, WRITE_TYPE_RANDOM)) < 0) {
            ddi_ldl_pop_media_task();
            return RetValue;
        }
        //if((RetValue = myFSWriteSector(Device,
        if ((RetValue = FSWriteSector(Device,
                                      Handle[HandleNumber].DirSector,
                                      (Handle[HandleNumber].diroffset + DIR_FSTCLUSHIOFFSET),
                                      (uint8_t *) & clusterhi, 0, 2, WRITE_TYPE_RANDOM))
            < 0) {
            ddi_ldl_pop_media_task();
            return RetValue;
        }
    }

    if (Handle[HandleNumber].Mode & DIRECTORY_MODE) {
        FileSize = 0x7fffffff;  // Set the file size as the largest +ve number
    } else {
        FileSize = GET_FILE_SIZE(HandleNumber);
    }
    //In append mode seek to the end of file and write at the end
    if (((Handle[HandleNumber].Mode) & APPEND_MODE) == APPEND_MODE) {
        if (FileSize != Handle[HandleNumber].CurrentOffset) {
            Fseek(HandleNumber, 0, SEEK_END);
        }
    }

    RemainBytesInSector = BytesPerSector - Handle[HandleNumber].BytePosInSector;

    while (RemainBytesToWrite > 0) {
        if (RemainBytesInSector || (RemainBytesToWrite < BytesPerSector)) { /*head and tail */
            if ((RetValue = UpdateHandleOffsets(HandleNumber))) //update the sector information
            {
                if ((RetValue = GetNewcluster(HandleNumber)) < 0) {
                    Handle[HandleNumber].ErrorCode = RetValue;
                    ddi_ldl_pop_media_task();
                    return (NumBytesToWrite - RemainBytesToWrite);
                }
                if (Handle[HandleNumber].Mode & CREATE_MODE) {
                    if ((RetValue = ClearCluster(HandleNumber)) < 0) {
                        ddi_ldl_pop_media_task();
                        return RetValue;
                    }
                }
            }

            if ((RemainBytesInSector != 0) && (RemainBytesToWrite > RemainBytesInSector)) {
                BytesToCopy = RemainBytesInSector;
                RemainBytesInSector = 0;
            } else {
                BytesToCopy = RemainBytesToWrite;
                if (BytesToCopy > BytesPerSector) {
                    BytesToCopy = BytesPerSector;
                }
            }
            RemainBytesToWrite -= BytesToCopy;

            if ((FileSize - Handle[HandleNumber].CurrentOffset) <= 0) {
                Handle[HandleNumber].Mode |= SEQ_WRITE_MODE;
                Mode = WRITE_TYPE_NOREADBACK;

            } else
                Mode = WRITE_TYPE_RANDOM;

            if ((RetValue = FSWriteSector(Device,
                                          Handle[HandleNumber].CurrentSector,
                                          Handle[HandleNumber].BytePosInSector,
                                          Buffer, BuffOffset, BytesToCopy, Mode))
                < 0) {
                ddi_ldl_pop_media_task();
                return RetValue;
            }

            Handle[HandleNumber].CurrentOffset += BytesToCopy;
            Handle[HandleNumber].BytePosInSector += BytesToCopy;

            BuffOffset += BytesToCopy;
        } else {
            int sectorNum = 0, sectorStart = 0;
            int prevSectorPos = 0, prevSectorIndex = 0, sectorToWrite = 0, prevClusterIndex = 0;
            BytesToCopy = RemainBytesToWrite - RemainBytesToWrite % BytesPerSector; // need to aligned to sector
            sectorNum = BytesToCopy / BytesPerSector;
            sectorNum = (sectorNum > 4096) ? 4096 : sectorNum;  // limit one access no more than 1M

            while (sectorNum--) {
                Handle[HandleNumber].BytePosInSector = BytesPerSector;  //always aligned to sector                
                if ((RetValue = UpdateHandleOffsets(HandleNumber))) //update the sector information
                {
                    if ((RetValue = GetNewcluster(HandleNumber)) < 0) {
                        Handle[HandleNumber].ErrorCode = RetValue;
                        ddi_ldl_pop_media_task();
                        return (NumBytesToWrite - RemainBytesToWrite);
                    }
                    if (Handle[HandleNumber].Mode & CREATE_MODE) {
                        if ((RetValue = ClearCluster(HandleNumber)) < 0) {
                            ddi_ldl_pop_media_task();
                            return RetValue;
                        }
                    }
                }

                if (sectorStart == 0) {
                    sectorStart = Handle[HandleNumber].CurrentSector;
                    prevSectorIndex = Handle[HandleNumber].CurrentSector;
                    prevClusterIndex = Handle[HandleNumber].CurrentCluster;
                    sectorToWrite++;
                    continue;
                }

                if (prevSectorIndex + 1 == Handle[HandleNumber].CurrentSector) {    /*adjacent sectors */
                    sectorToWrite++;
                    prevSectorIndex = Handle[HandleNumber].CurrentSector;
                    prevClusterIndex = Handle[HandleNumber].CurrentCluster;
                    prevSectorPos = Handle[HandleNumber].SectorPosInCluster;
                } else {
                    /*backwards to the previous sector index, if the sector is not continous in physical address. */
                    Handle[HandleNumber].CurrentSector = prevSectorIndex;
                    Handle[HandleNumber].CurrentCluster = prevClusterIndex;
                    Handle[HandleNumber].SectorPosInCluster = prevSectorPos;
                    break;
                }

            }
            BytesToCopy = sectorToWrite * BytesPerSector;
            if (read_usdhc_adma_mode() && (((uint32_t) Buffer + BuffOffset) & 0x3)) 
             // in ADMA mode, the buffer address must be word-aligned
            {
                uint8_t *tempBuffer = 0;
                uint8_t *tempToken = 0;
                extern int cache_line;
                tempToken = malloc(BytesToCopy + 2 * cache_line);
                tempBuffer =
                    (uint8_t *) (((uint32_t) tempToken + cache_line) & (~(cache_line - 1)));
                memcpy(tempBuffer, (uint8_t *) (Buffer + BuffOffset), BytesToCopy);
                if ((RetValue = FSWriteMultiSectors(Device,
                                                    sectorStart,
                                                    WRITE_TYPE_RANDOM, tempBuffer, BytesToCopy))
                    < 0) {
                    ddi_ldl_pop_media_task();
                    return RetValue;
                }
                free(tempToken);
            } else {
                if ((RetValue = FSWriteMultiSectors(Device,
                                                    sectorStart,
                                                    WRITE_TYPE_RANDOM,
                                                    (uint8_t *) (Buffer + BuffOffset), BytesToCopy))
                    < 0) {
                    ddi_ldl_pop_media_task();
                    return RetValue;
                }
            }

            if ((FileSize - Handle[HandleNumber].CurrentOffset) <= 0) {
                Handle[HandleNumber].Mode |= SEQ_WRITE_MODE;
                Mode = WRITE_TYPE_NOREADBACK;

            } else
                Mode = WRITE_TYPE_RANDOM;

            Handle[HandleNumber].CurrentOffset += BytesToCopy;
            Handle[HandleNumber].BytePosInSector = BytesPerSector;
            RemainBytesToWrite -= BytesToCopy;
            BuffOffset += BytesToCopy;
        }

    }

    if ((FileSize - Handle[HandleNumber].CurrentOffset) < 0) {
        Handle[HandleNumber].Mode |= SEQ_WRITE_MODE;
        UpdateFileSize(HandleNumber, 0);
    }

    ddi_ldl_pop_media_task();
    return NumBytesToWrite;
}

/*----------------------------------------------------------------------------

>  Function Name: RtStatus_t UpdateFileSize(int32_t HandleNumber,int32_t DeleteContentFlag)

   FunctionType:  Reentrant

   Inputs:        1)HandleNumber
                  2)DeleteContentFlag (if it is set, Update the file size)   

   Outputs:       Returns 0 on Success or ERROR Code if  Error Occurs

   Description:   Updates the file size if data is written 
<
----------------------------------------------------------------------------*/
RtStatus_t UpdateFileSize(int32_t HandleNumber, int32_t DeleteContentFlag)
{
    int32_t FileSize;
    int32_t i = 0;

    EnterNonReentrantSection();

    if (Handle[HandleNumber].Mode & DIRECTORY_MODE) {
        FileSize = 0x7fffffff;  // Set the file size as the largest +ve number
    } else {
        FileSize = GET_FILE_SIZE(HandleNumber);
    }

    if (Handle[HandleNumber].CurrentOffset > FileSize || DeleteContentFlag == 1) {
        Handle[HandleNumber].FileSize = Handle[HandleNumber].CurrentOffset;

        for (i = FIRST_VALID_HANDLE; i < maxhandles; i++) {
            if (i != HandleNumber) {
                if (Handle[HandleNumber].Device == Handle[i].Device) {
                    if (Handle[i].HandleActive == 1) {
                        if (Handle[HandleNumber].DirSector == Handle[i].DirSector) {
                            if (Handle[HandleNumber].diroffset == Handle[i].diroffset)
                                Handle[i].FileSize = Handle[HandleNumber].FileSize;

                        }
                    }
                }
            }
        }
    }

    LeaveNonReentrantSection();
    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name: void SeekPoint_InitializeBuffer(int32_t HandleNumber)

   FunctionType:  Reentrant

   Inputs:        1)Handle number

   Outputs:       Nil

   Description:   Initialize seekpoint buffer and seekpoint step
   
<
----------------------------------------------------------------------------*/
void SeekPoint_InitializeBuffer(int32_t HandleNumber)
{
    int32_t i;

    Handle[HandleNumber].SeekPointsClusterStep = INVALID_CLUSTER;
    Handle[HandleNumber].SeekPointsBaseFileSize = 0;
    for (i = 0; i < NUM_SEEKPOINTS_CACHED; i++)
        Handle[HandleNumber].SeekPointsClusters[i] = INVALID_CLUSTER;
}

/*----------------------------------------------------------------------------
>  Function Name: void SeekPoint_CalculateSeekPointStep(int32_t HandleNumber, int32_t FileSize)

   FunctionType:  Reentrant

   Inputs:        1)Handle number
                  2)old File size
                  3)new File size

   Outputs:       Nil

   Description:   Calculate seekpoint step according to the file size
   
<
----------------------------------------------------------------------------*/
void SeekPoint_CalculateSeekPointStep(int32_t HandleNumber, int32_t oldFileSize,
                                      int32_t newFileSize)
{
    if (Handle[HandleNumber].SeekPointsClusterStep == INVALID_CLUSTER || oldFileSize != newFileSize) {
        int32_t SeekPointsClusterStep, oldSeekPointsClusterStep;

        //First calculate how many clusters the file uses              
        SeekPointsClusterStep = newFileSize >> MediaTable[Handle[HandleNumber].Device].ClusterShift;

        // calculate the step of the seekpoint
        SeekPointsClusterStep /= NUM_SEEKPOINTS_CACHED;
        if (SeekPointsClusterStep == 0) {
            SeekPointsClusterStep = 1;
        }

        oldSeekPointsClusterStep = Handle[HandleNumber].SeekPointsClusterStep;
        Handle[HandleNumber].SeekPointsClusterStep = SeekPointsClusterStep;
        Handle[HandleNumber].SeekPointsBaseFileSize = newFileSize;

        //if file size increases, we need adjust SeekPointsClusterStep and move the seekpoint buffer
        //this case happens when file is opened with mode "w+", 
        if ((oldSeekPointsClusterStep != INVALID_CLUSTER)
            && (oldSeekPointsClusterStep != SeekPointsClusterStep)) {
            int32_t i, cnt;
            int32_t ClusterOffsetInFile = oldSeekPointsClusterStep;
            int32_t SeekPointsClustersBackup[NUM_SEEKPOINTS_CACHED];
            int32_t *pSeekPointsClusters = Handle[HandleNumber].SeekPointsClusters;

            //backup the old seekpoint buffer
            memcpy(SeekPointsClustersBackup, pSeekPointsClusters,
                   sizeof(int32_t) * NUM_SEEKPOINTS_CACHED);

            for (i = 0; i < NUM_SEEKPOINTS_CACHED; i++) {
                //The file size only increases ( we don't support file shrink)
                //So the seekpoint can only move backward.
                pSeekPointsClusters[i] = INVALID_CLUSTER;
                if (SeekPointsClustersBackup[i] != INVALID_CLUSTER) {
                    // ClusterOffsetInFile presents the cluster position of old seekpoint buffer
                    // check whether the old seekpoint should move to the new seekpoint buffer
                    // Because file increases, seekpoint step increases, we need discard some old seekpoint
                    if (ClusterOffsetInFile >= SeekPointsClusterStep &&
                        ClusterOffsetInFile % SeekPointsClusterStep == 0) {
                        cnt = ClusterOffsetInFile / SeekPointsClusterStep - 1;
                        pSeekPointsClusters[cnt] = SeekPointsClustersBackup[i];
                    }
                }
                ClusterOffsetInFile += oldSeekPointsClusterStep;
            }

        }
    }
}

/*----------------------------------------------------------------------------
>  Function Name: SeekPoint_FillSeekPoint(int32_t HandleNumber, int32_t ClusterOffsetInFile, int32_t CurrentCluster)

   FunctionType:  Reentrant

   Inputs:        1)Handle number
                  2)ClusterOffsetInFile: the cluster offset of the current cluster with the beginning of file
                  3)CurrentCluster:  

   Outputs:       Nil

   Description:   Fill seekpoint cache buffer
   
<
----------------------------------------------------------------------------*/
void SeekPoint_FillSeekPoint(int32_t HandleNumber, int32_t ClusterOffsetInFile,
                             int32_t CurrentCluster)
{
    // check whether the CurrentCluster should be cached.
    if (ClusterOffsetInFile >= Handle[HandleNumber].SeekPointsClusterStep &&
        ClusterOffsetInFile % Handle[HandleNumber].SeekPointsClusterStep == 0) {
        //Calculate the position in Seekpoint buffer
        int32_t cnt = ClusterOffsetInFile / Handle[HandleNumber].SeekPointsClusterStep - 1;
        if (Handle[HandleNumber].SeekPointsClusters[cnt] == INVALID_CLUSTER) {
            Handle[HandleNumber].SeekPointsClusters[cnt] = CurrentCluster;
        }
    }

}

/*----------------------------------------------------------------------------

>  Function Name: RtStatus_t Fseek(int32_t HandleNumber, int32_t NumBytesToSeek, int32_t SeekPosition)

   FunctionType:  Reentrant

   Inputs:        1)HandleNumber
                  2)NumBytesToSeek
                  3)SeekPosition

   Outputs:       Returns 0 or ERROR Code if  Error Occurs

   Description:   Adjusts the current position by the no. of byte specified

<
----------------------------------------------------------------------------*/
RtStatus_t Fseek_FAT(int32_t HandleNumber, int32_t NumBytesToSeek, int32_t SeekPosition)
{
    int32_t NumClusterSeek, i;
    RtStatus_t RetValue = SUCCESS;
    int32_t RemainingByteOffsetInCluster, NumSectors;
    int32_t CurrentCluster, FileSize, CrtCLuster;
    int32_t Device;
    int32_t CurrentByteOffsetInCluster, RelativeSeekByteoffset;
    int32_t CurrentClusterByteOffsetInFile, SeekTargetByteOffset;
    int32_t ClusterOffsetInFile;

    if ((HandleNumber < 0) || (HandleNumber >= maxhandles)) {
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;
    }

    Device = Handle[HandleNumber].Device;

    if ((RetValue = Handleactive(HandleNumber)) < 0) {
        Handle[HandleNumber].ErrorCode = RetValue;
        return RetValue;
    }
    // We treat directories as files, so a special read mode for these.
    if (Handle[HandleNumber].Mode & DIRECTORY_MODE) {
        FileSize = 0x7fffffff;  // Set the file size as the largest +ve number
    } else {
        FileSize = GET_FILE_SIZE(HandleNumber);
        SeekPoint_CalculateSeekPointStep(HandleNumber, Handle[HandleNumber].SeekPointsBaseFileSize,
                                         FileSize);
    }

    if (SeekPosition == SEEK_SET)
        SeekTargetByteOffset = NumBytesToSeek;
    else if (SeekPosition == SEEK_CUR)
        SeekTargetByteOffset = NumBytesToSeek + Handle[HandleNumber].CurrentOffset;
    else if (SeekPosition == SEEK_END)
        SeekTargetByteOffset = FileSize + NumBytesToSeek;
    else {
        Handle[HandleNumber].ErrorCode = ERROR_OS_FILESYSTEM_FSEEK_FAILED;
        return ERROR_OS_FILESYSTEM_FSEEK_FAILED;
    }

    if (SeekTargetByteOffset < 0)
        SeekTargetByteOffset = 0;
    if (SeekTargetByteOffset >= FileSize)
        SeekTargetByteOffset = FileSize;

    // find the begining offset of current cluster

    CurrentByteOffsetInCluster =
        Handle[HandleNumber].CurrentOffset & MediaTable[Device].ClusterMask;

    // Check for boundary condition. We could be at the end of the sector and cluster.
    if (CurrentByteOffsetInCluster == 0) {
        if (Handle[HandleNumber].CurrentOffset) {

            CurrentByteOffsetInCluster =
                Handle[HandleNumber].BytePosInSector +
                Handle[HandleNumber].SectorPosInCluster * MediaTable[Device].BytesPerSector;
        }
    }

    CurrentClusterByteOffsetInFile =
        Handle[HandleNumber].CurrentOffset - CurrentByteOffsetInCluster;

    RelativeSeekByteoffset = SeekTargetByteOffset - CurrentClusterByteOffsetInFile;

    // if RelativeSeekByteoffset is positive then seek from file's current position, else seek from begining    
    if (RelativeSeekByteoffset >= 0) {

        NumClusterSeek = RelativeSeekByteoffset >> MediaTable[Device].ClusterShift;

        RemainingByteOffsetInCluster = RelativeSeekByteoffset & MediaTable[Device].ClusterMask;

        CurrentCluster = Handle[HandleNumber].CurrentCluster;

        NumSectors = (RemainingByteOffsetInCluster >> MediaTable[Device].SectorShift);

        ClusterOffsetInFile = CurrentClusterByteOffsetInFile >> MediaTable[Device].ClusterShift;

    } else {

        NumClusterSeek = SeekTargetByteOffset >> MediaTable[Device].ClusterShift;

        RemainingByteOffsetInCluster = SeekTargetByteOffset & MediaTable[Device].ClusterMask;

        CurrentCluster = Handle[HandleNumber].StartingCluster;

        NumSectors = (RemainingByteOffsetInCluster >> MediaTable[Device].SectorShift);

        ClusterOffsetInFile = 0;

    }

    // we don't use seekpoint cache for directory 
    // for directory the value of SeekPointsClusterStep is INVALID_CLUSTER
    if ((NumClusterSeek > 0) && (Handle[HandleNumber].SeekPointsClusterStep != INVALID_CLUSTER)) {
        int32_t *pSeekPointsClusters = Handle[HandleNumber].SeekPointsClusters;
        int32_t loopstart =
            (SeekTargetByteOffset >> MediaTable[Device].ClusterShift) /
            Handle[HandleNumber].SeekPointsClusterStep - 1;

        // find closest seekpoint cluster. 
        // loopstart is the closest seekpoint to the target seek position.
        // we start search backward from loopstart whether there is valid seekpoint
        if (loopstart >= NUM_SEEKPOINTS_CACHED)
            loopstart = NUM_SEEKPOINTS_CACHED - 1;
        for (i = loopstart; i >= 0; i--) {
            if (pSeekPointsClusters[i] != INVALID_CLUSTER) {
                int32_t SeekPointClusterByteOffsetInFile =
                    ((i +
                      1) *
                     Handle[HandleNumber].SeekPointsClusterStep) << MediaTable[Device].ClusterShift;

                //if it is seek forward, we need check seekpoint cluster and current cluster which is closer to target seek position
                if (RelativeSeekByteoffset >= 0) {
                    // current cluster is closer to target position, nothing to do.
                    if (CurrentClusterByteOffsetInFile >= SeekPointClusterByteOffsetInFile) {
                        break;
                    }
                }
                //we start from seekpoint cluster. update NumClusterSeek and CurrentCluster
                RelativeSeekByteoffset = SeekTargetByteOffset - SeekPointClusterByteOffsetInFile;
                NumClusterSeek = RelativeSeekByteoffset >> MediaTable[Device].ClusterShift;
                CurrentCluster = pSeekPointsClusters[i];
                ClusterOffsetInFile =
                    SeekPointClusterByteOffsetInFile >> MediaTable[Device].ClusterShift;
                break;
            }
        }
    }

    ddi_ldl_push_media_task("Fseek_FAT");

    // Find the target cluster
    for (i = 0; i < NumClusterSeek; i++) {
        CrtCLuster = CurrentCluster;
        CurrentCluster = Findnextcluster(Device, CurrentCluster);
        if ((CurrentCluster == ERROR_OS_FILESYSTEM_EOF) && (i == NumClusterSeek - 1)) {
            // reach the end of file
            CurrentCluster = CrtCLuster;
            NumSectors = MediaTable[Device].SectorsPerCluster - 1;
            // Since the cluster has not changed, the Remaining offset should be changed
            RemainingByteOffsetInCluster = (NumSectors + 1) * MediaTable[Device].BytesPerSector;
            break;
        }
        if (CurrentCluster < 0) {
            // error happens
            Handle[HandleNumber].ErrorCode = CurrentCluster;
            ddi_ldl_pop_media_task();
            return (RtStatus_t) CurrentCluster;
        }

        ClusterOffsetInFile++;
        // check whether the cluster should be saved in seekpoint buffer
        SeekPoint_FillSeekPoint(HandleNumber, ClusterOffsetInFile, CurrentCluster);
    }

    //Updated Handle Entries
    Handle[HandleNumber].CurrentOffset = SeekTargetByteOffset;
    Handle[HandleNumber].BytePosInSector =
        RemainingByteOffsetInCluster - NumSectors * MediaTable[Device].BytesPerSector;
    Handle[HandleNumber].SectorPosInCluster = NumSectors;
    Handle[HandleNumber].CurrentCluster = CurrentCluster;
    Handle[HandleNumber].CurrentSector = Handle[HandleNumber].SectorPosInCluster +
        Firstsectorofcluster(Device, CurrentCluster);
    ddi_ldl_pop_media_task();
    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t Ftell(int32_t HandleNumber)

   FunctionType:  Reentrant

   Inputs:        1) Handle Number

   Outputs:       Returns current offset or an Error

   Description:   Finds the current file position
<
----------------------------------------------------------------------------*/
int32_t Ftell(int32_t HandleNumber)
{
    RtStatus_t RetValue;        // Don't init to save memory.

    EnterNonReentrantSection();

    // Check whether the passed handle number is within range
    if ((HandleNumber < 0) || (HandleNumber >= maxhandles)) {
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;
    }

    if ((RetValue = Handleactive(HandleNumber)) < 0) {
        LeaveNonReentrantSection();
        return RetValue;
    }
    LeaveNonReentrantSection();
    return Handle[HandleNumber].CurrentOffset;
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t Feof(int32_t HandleNumber)

   FunctionType:  Reentrant

   Inputs:        1)Handle Number

   Outputs:       Returns EOF if end of file else number of bytes left in file

   Description:   Checks for the end of file condition
<
----------------------------------------------------------------------------*/
int32_t Feof(int32_t HandleNumber)
{
    int32_t BytesLeft;
    int32_t FileSize;

    if (HandleNumber > maxhandles)
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;

    if (Handle[HandleNumber].HandleActive != 1)
        return ERROR_OS_FILESYSTEM_HANDLE_NOT_ACTIVE;

    if (Handle[HandleNumber].Mode & DIRECTORY_MODE)
        FileSize = 0x7fffffff;  // Set the file size as the largest +ve number
    else
        FileSize = GetFileSize(HandleNumber);

    if ((BytesLeft = (FileSize - Ftell(HandleNumber))) > 0)
        return BytesLeft;

    return ERROR_OS_FILESYSTEM_EOF;
}
