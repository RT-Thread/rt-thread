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
 $Archive: /Fatfs/FileSystem/Fat32/common/Fsinit.c $              
 $Revision: 4 $                                       
 $Date: 9/18/03 10:37a $      
 Description: Fsinit.c
 Notes:
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
		File Includes
----------------------------------------------------------------------------*/
#include <string.h>

#include "types.h"
#include "fstypes.h"
#include "filesystem/fsapi.h"
#include "handletable.h"
#include "devicetable.h"
#include "filespec.h"
#include "fat_internal.h"

/*----------------------------------------------------------------------------
		Globals and Declarations
----------------------------------------------------------------------------*/

int32_t g_FSinitErrorCode = 0;
HandleTable_t *Handle;
FileSystemMediaTable_t *MediaTable;
FileSpecs_t *filespec;

/* start sector */
extern uint32_t g_u32MbrStartSector;

/*----------------------------------------------------------------------------

>  Function Name:  RtStatus_t FSInit(uint8_t *bufx, uint8_t *bufy, int32_t maxdevices, int32_t maxhandles, int32_t maxcaches)

   FunctionType:   Non-reentrant

   Inputs:         a) Pointer to X buffer for allocation of cache buffers.
                   b) Pointer to Y buffer for allocation of handles, descriptors, etc.
                   c) Max number of internal + external media supported.
                   d) Max handles supported.
                   e) Max cache buffers supported.

   Outputs:        Returns 0, if Success else an ERROR CODE

   Description:    Initialization of FileSystem.
<
--------- -------------------------------------------------------------------*/

RtStatus_t FSInit
    (uint8_t * bufx, uint8_t * bufy, int32_t maxdevices, int32_t maxhandles, int32_t maxcaches) {
    // Assign pointers
    MediaTable = (FileSystemMediaTable_t *) & bufy[0];
    Handle = (HandleTable_t *) & bufy[maxdevices * sizeof(FileSystemMediaTable_t)];
    filespec = (FileSpecs_t *) & bufy[maxdevices * sizeof(FileSystemMediaTable_t) +
                                      maxhandles * sizeof(HandleTable_t)];

    // Now initialize the handle table to 0.
    memset(&Handle[0], 0, sizeof(Handle[0]) * maxhandles);

    return SUCCESS;
}

/*----------------------------------------------------------------------------

>  Function Name:  int32_t FSDriveInit(int32_t DeviceNumber)

   FunctionType:  
                   
   Inputs:         Single input param is logical data drive number.
   

   Outputs:        Returns 0, if Success, else ERROR CODE
                   Writes g_FSinitErrorCode static.
                   
                   
   Description:    Initialization of FileSystem.
<
--------- -------------------------------------------------------------------*/
int32_t FSDriveInit(int32_t DeviceNumber)
{
    int32_t RetValue;

    /* Clear drive buffer */

    FSClearDriveBuf(DeviceNumber, maxhandles);

    Cleardevicerecord(DeviceNumber);

    //if MMC then Shift g_FSinitErrorCode 2 bits left    (comment doesn't match code)
    g_FSinitErrorCode = (g_FSinitErrorCode << 1);

    // Read sector 0 to get PBS address
    // Read PBS itself
    // Verify PBS.
    if ((RetValue = FSDataDriveInit(DeviceNumber)) != 0)    // Non zero return value indicates error
    {
        // Could not find or confirm the PBS

        if (RetValue == INVALID_FILESYSTEM) {
            g_FSinitErrorCode = (g_FSinitErrorCode | 0x01);
            RetValue = ERROR_OS_FILESYSTEM_FILESYSTEM_NOT_FOUND;
        }
        return RetValue;
    }
    // Formerly, this code called FileSystemPresent(DeviceNumber) read
    // and confirm the PBS signature.  However,
    // At this point the PBS has been verified by FSDataDriveInit(), so there is no need to check it
    // again with FileSystemPresent(DeviceNumber)
    if ((RetValue = Readdevicerecord(DeviceNumber, BOOTSECTOR)) != 0) {
        if (RetValue == INVALID_FILESYSTEM) {
            g_FSinitErrorCode = (g_FSinitErrorCode | 0x01);
            RetValue = ERROR_OS_FILESYSTEM_FILESYSTEM_NOT_FOUND;
        }
        return RetValue;
    }

    return SUCCESS;
}

/*----------------------------------------------------------------------------

>  Function Name:  int32_t FSInit(int32_t _X *bufx, int32_t _Y *bufy, int32_t maxdevices, int32_t maxhandles, int32_t maxcaches)

   FunctionType:  

   Inputs:         a) Pointer to X buffer for allocation of cache buffers
                   b) Pointer to Y buffer for allocation of handles, descriptors, etc
                   c) Max number of internal + external media supported.
                   d) Max handles supported.
                   e) Max cache buffers supported.

   Outputs:        Returns 0, if Success, else ERROR CODE

   Description:    Initialization of FileSystem.
<
--------- -------------------------------------------------------------------*/
void FSClearDriveBuf(int32_t DriveNumber, int32_t maxhandles)
{
    int32_t i;

    // setup handle
    for (i = 0; i < maxhandles; i++) {
        if (Handle[i].Device == DriveNumber)
            Handle[i].HandleActive = 0;
    }

}

/*----------------------------------------------------------------------------

>  Function Name:  int32_t FSDriveShutdown(int32_t DeviceNumber)

   FunctionType:  

   Inputs:         a) Pointer to X buffer for allocation of cache buffers
                   b) Pointer to Y buffer for allocation of handles, descriptors, etc
                   c) Max number of internal + external media supported.
                   d) Max handles supported.
                   e) Max cache buffers supported.

   Outputs:        Returns 0, if Success, else ERROR CODE

   Description:    Initialization of FileSystem.
<
--------- -------------------------------------------------------------------*/
int32_t FSDriveShutdown(int32_t deviceNumber)
{
    int32_t i;

    /* Close all the active handles */

    for (i = 0; i < maxhandles; i++) {
        if ((Handleactive(i)) == SUCCESS) {
            int32_t iDeviceNumberCheck;
            if (GetDeviceFromHandle(i, &iDeviceNumberCheck) == SUCCESS) {
                if (iDeviceNumberCheck == deviceNumber) {
                    Fclose(i);
                }
            }
        }
    }

    /* Flush the drive cache */

    FSFlushDriveCache(deviceNumber);

    /* Clear the drive buff */

    FSClearDriveBuf(deviceNumber, maxhandles);

    /* Deallocate drive_specific system resource */
    /* TODOFSINITSHUTDOWN */

    /* Clear drive specific file system data structures */

    Cleardevicerecord(deviceNumber);

    return SUCCESS;
}

/*----------------------------------------------------------------------------

>  Function Name:  RtStatus_t FSShutdown(void)

   FunctionType:   Reentrant

   Inputs:         Nil

   Outputs:        Returns 0 on success else an error code
                   
   Description:    Shutdown the file system  
                    
<
----------------------------------------------------------------------------*/
RtStatus_t FSShutdown(void)
{
    int32_t i = 0;
    RtStatus_t RetValue = SUCCESS;

    /* Close all the active file handles */

    for (i = 0; i < maxhandles; i++) {
        if ((Handleactive(i)) == SUCCESS) {
            if (Fclose(i) < 0)
                continue;
        }
    }

    /* Flush the cache */

    if ((RetValue = (RtStatus_t) FlushCache()) != SUCCESS) {
        return RetValue;
    }

    /* Shutdown external and internal drive */

    for (i = 0; i < maxdevices - 1; i++) {
        FSDriveShutdown(i);
    }

    /* Clear any global data */
    /* TODOFSINITSHUTDOWN */

    return RetValue;
}
