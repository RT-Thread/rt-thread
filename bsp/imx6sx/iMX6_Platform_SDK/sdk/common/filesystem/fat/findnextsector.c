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
 $Archive: /Fatfs/FileSystem/Fat32/Utility/FindNextSector.c $
 $Revision: 11 $                                       
 $Date: 9/18/03 3:45p $
 Description: FindNextSector.c
 Notes:	
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
		File Includes
----------------------------------------------------------------------------*/
#include <types.h>
#include "fstypes.h"
#include "filesystem/fsapi.h"
#include "fat_internal.h"

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t UpdateHandleOffsets(int32_t HandleNumber)

   FunctionType:  Reentrant

   Inputs:        1)HandleNumber

   Outputs:       Returns ERROR_OS_FILESYSTEM_EOF or an Error Code if error occurs

   Description:   Updates handle entries after each read and/or write
<
----------------------------------------------------------------------------*/
RtStatus_t UpdateHandleOffsets(int32_t HandleNumber)
{
    HandleTable_t *handle = &Handle[HandleNumber];
    int32_t Device = handle->Device;
    FileSystemMediaTable_t *media = &MediaTable[Device];
    uint32_t bytesPerSector = media->BytesPerSector;
    uint32_t sectorsPerCluster = media->SectorsPerCluster;
    RtStatus_t RetValue = SUCCESS;

    while (handle->BytePosInSector >= bytesPerSector) {
        handle->BytePosInSector -= bytesPerSector;
        handle->CurrentSector++;
        handle->SectorPosInCluster++;

        if (handle->SectorPosInCluster >= sectorsPerCluster) {
            if ((RetValue = FindNextSector(Device, HandleNumber)) == ERROR_OS_FILESYSTEM_EOF) {
                handle->BytePosInSector = bytesPerSector;
                handle->SectorPosInCluster = sectorsPerCluster - 1;
                return RetValue;
            }

            if (RetValue == ERROR_OS_FILESYSTEM_INVALID_CLUSTER_NO) {
                return ERROR_OS_FILESYSTEM_INVALID_CLUSTER_NO;
            }
        }
    }

    return RetValue;
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t FindNextSector(int32_t Device,int32_t HandleNumber)

   FunctionType:  Reentrant

   Inputs:        1) Device
                  2) HandleNumber

   Outputs:       Returns 0 else an error code

   Description:   Finds the next cluster and sector 
<
----------------------------------------------------------------------------*/
RtStatus_t FindNextSector(int32_t Device, int32_t HandleNumber)
{
    HandleTable_t *handle = &Handle[HandleNumber];
    int32_t ClusterNumber = Findnextcluster(Device, handle->CurrentCluster);
    if (ClusterNumber == ERROR_OS_FILESYSTEM_EOF) {
        return ERROR_OS_FILESYSTEM_EOF;
    } else if (ClusterNumber <= 0) {
        return ERROR_OS_FILESYSTEM_INVALID_CLUSTER_NO;
    }

    handle->CurrentCluster = ClusterNumber;
    handle->SectorPosInCluster = 0;
    handle->CurrentSector = Firstsectorofcluster(Device, handle->CurrentCluster);

    return SUCCESS;
}
