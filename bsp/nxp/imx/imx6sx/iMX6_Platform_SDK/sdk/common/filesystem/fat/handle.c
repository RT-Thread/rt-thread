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
 $Archive: /Fatfs/FileSystem/Fat32/handle/Handle.c $ 
 $Revision: 18 $                                       
 $Date: 9/27/03 5:32p $
 Description: Handle.c
 Notes:
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
		File Includes
----------------------------------------------------------------------------*/
#include <types.h>
#include "fstypes.h"
#include "fat_internal.h"
#include "filesystem/fsapi.h"

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t Freehandle(int32_t HandleNumber)

   FunctionType:   Reentrant

   Inputs:         1)Handle number

   Outputs:        Returns 0 or an ERROR CODE if HandleNumber exceeds maxhandles

   Description:    marks the given handle number in the handle table as free
<
----------------------------------------------------------------------------*/
RtStatus_t Freehandle(int32_t HandleNumber)
{

    // Ensure the handle table pointer is not NULL.
    assert(Handle);

    // Check whether the passed handle number is within range
    if ((HandleNumber < 0) || (HandleNumber >= maxhandles))
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;

    Handle[HandleNumber].HandleActive = 0;
    Handle[HandleNumber].ErrorCode = 0;

    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t Updatehandlemode(int32_t HandleNumber,int32_t Mode)

   FunctionType:  Reentrant

   Inputs:        1) Handle number
                  2) Mode 

   Outputs:       Returns SUCCESS or Error if the mode can not be updated.

   Description:   Updates the mode field of the given handle number with
                  the specified mode.
<
----------------------------------------------------------------------------*/
RtStatus_t Updatehandlemode(int32_t HandleNumber, int32_t Mode)
{
    // Ensure the handle table pointer is not NULL.
    assert(Handle);

    // Check whether the passed handle number is within range
    if ((HandleNumber < 0) || (HandleNumber >= maxhandles))
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;

    Handle[HandleNumber].Mode = (FileSystemModeTypes_t) Mode;
    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t Gethandlemode(int32_t HandleNumber,int32_t Mode)

   FunctionType:  Reentrant

   Inputs:        1) Handle number
                  2) Mode 

   Outputs:       Returns HandleMode or an Error.

   Description:   Updates the mode field of the given handle number with
                  the specified mode.
<
----------------------------------------------------------------------------*/
int32_t Gethandlemode(int32_t HandleNumber)
{
    // Ensure the handle table pointer is not NULL.
    assert(Handle);

    // Check whether the passed handle number is within range
    if ((HandleNumber < 0) || (HandleNumber >= maxhandles))
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;
    return Handle[HandleNumber].Mode;
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t IsHandleWriteAllocated(int32_t HandleNumber)

   FunctionType:  Reentrant

   Inputs:        1) Handle number

   Outputs:       Returns WRITE_MODE if Handle is allocated for Write,
                  if not then returns NOT_WRITE_MODE (0)

   Description:   Checks whether the file associated with the given
                  handle number is already opened for write mode or not.
<
----------------------------------------------------------------------------*/
FileSystemModeTypes_t IsHandleWriteAllocated(int32_t HandleNumber)
{
    int32_t i;

    // Ensure the handle table pointer is not NULL.
    assert(Handle);

    EnterNonReentrantSection();
    // Check whether the passed handle number is within range
    if ((HandleNumber < 0) || (HandleNumber >= maxhandles)) {
        LeaveNonReentrantSection();
        // Cast to FileSystem mode to prevent errors.
        return (FileSystemModeTypes_t) ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;
    }

    for (i = FIRST_VALID_HANDLE; i < maxhandles; i++) {
        if (i != HandleNumber) {
            if (Handle[i].HandleActive == 1) {
                if (Handle[HandleNumber].Device == Handle[i].Device) {
                    if (Handle[HandleNumber].DirSector == Handle[i].DirSector) {
                        if (Handle[HandleNumber].diroffset == Handle[i].diroffset)
                            if (Handle[i].Mode & WRITE_MODE) {
                                LeaveNonReentrantSection();
                                return WRITE_MODE;
                            }
                    }
                }
            }
        }
    }
    LeaveNonReentrantSection();
    return NOT_WRITE_MODE;
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t Searchfreehandleallocate(void)

   FunctionType:  Reentrant

   Inputs:        Nil

   Outputs:       Handle number of free handle or error(NofreeHandle) if no 
                  free handle is available

   Description:   Searches in the handle table for free handle. If free handle is found 
                  then mark this handle  as active in the handle table
<
----------------------------------------------------------------------------*/
int32_t Searchfreehandleallocate(void)
{
    int32_t i;

    // Ensure the handle table pointer is not NULL.
    assert(Handle);

    EnterNonReentrantSection();
    for (i = FIRST_VALID_HANDLE; i < maxhandles; i++) {
        if (Handle[i].HandleActive == 0) {
            Handle[i].HandleActive = 1;
            Handle[i].ErrorCode = 0;
            Handle[i].FileSize = 0;
            Handle[i].Mode = 0;
            Handle[i].DirSector = 0;
            Handle[i].diroffset = 0;
            SeekPoint_InitializeBuffer(i);
            LeaveNonReentrantSection();
            return i;
        }
    }

    LeaveNonReentrantSection();
    return ERROR_OS_FILESYSTEM_NO_FREE_HANDLE;
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t Isfileopen(int32_t HandleNumber)

   FunctionType:  Reentrant

   Inputs:        1) Handle number

   Outputs:       Returns ERROR_OS_FILESYSTEM_FILE_OPEN if file is opened else SUCCESS

   Description:   Checks whether the file associated with the given
                  handle number is already opened or not.
<
----------------------------------------------------------------------------*/
RtStatus_t Isfileopen(int32_t HandleNumber)
{
    int32_t i;

    // Ensure the handle table pointer is not NULL.
    assert(Handle);

    // Check whether the passed handle number is within range
    // To Fix -> stmp00014483.
    if ((HandleNumber < FIRST_VALID_HANDLE - 1) || (HandleNumber >= maxhandles))
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;

    for (i = FIRST_VALID_HANDLE - 1; i < maxhandles; i++) {
        if (i != HandleNumber) {
            if (Handle[HandleNumber].Device == Handle[i].Device) {
                if (Handle[i].HandleActive == 1) {
                    if (Handle[HandleNumber].CurrentSector == Handle[i].DirSector) {
                        if (Handle[HandleNumber].BytePosInSector == Handle[i].diroffset)
                            return ERROR_OS_FILESYSTEM_FILE_OPEN;
                    }
                }
            }
        }
    }
    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t IsCurrWorkDir(int32_t HandleNumber)

   FunctionType:  Reentrant

   Inputs:        1) Handle number

   Outputs:       Returns ERROR_OS_FILESYSTEM_CURRENT_WORK_DIR if given directory is current working
                  directory else SUCCESS

   Description:   Checks whether the directory associated with the given
                  handle number is current working directory.
<
----------------------------------------------------------------------------*/
RtStatus_t IsCurrWorkDir(int32_t HandleNumber)
{
    // Ensure the handle table pointer is not NULL.
    assert(Handle);

    EnterNonReentrantSection();
    if ((HandleNumber < 0) || (HandleNumber >= maxhandles)) {
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;
    }

    if (Handle[HandleNumber].Device == Handle[CWD_HANDLE].Device) {
        if (Handle[HandleNumber].DirSector == Handle[CWD_HANDLE].DirSector) {
            if (Handle[HandleNumber].diroffset == Handle[CWD_HANDLE].diroffset) {
                LeaveNonReentrantSection();
                return ERROR_OS_FILESYSTEM_CURRENT_WORK_DIR;
            }
        }
    }

    LeaveNonReentrantSection();
    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t GetCWDHandle(void)

   FunctionType:  Reentrant

   Inputs:        None

   Outputs:       Returns Handle Number of the new free hnadle found or error if function fails

   Description:   Finds a free handle and copies the handle 0 (CWD handle) to this new handle.
<----------------------------------------------------------------------------*/
int32_t GetCWDHandle(void)
{
    int32_t HandleNumber;

    // Ensure the handle table pointer is not NULL.
    assert(Handle);

    if ((HandleNumber = Searchfreehandleallocate()) < 0)
        return (ERROR_OS_FILESYSTEM_NO_FREE_HANDLE);

    EnterNonReentrantSection();

    /* copy the handle 0 (CWD handle) to this new handle found */
    Handle[HandleNumber] = Handle[CWD_HANDLE];

    LeaveNonReentrantSection();

    /* Remove Handle Write Mode */
    Handle[HandleNumber].Mode = (FileSystemModeTypes_t) (DIRECTORY_MODE + READ_MODE);

    return HandleNumber;
}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t GetDeviceFromHandle(int32_t HandleNumber, int32_t *pDeviceNumber)

   FunctionType:   Reentrant

   Inputs:         1) Handle number
				   2) Device number pointer

   Outputs:        Writes the device handle to the device number pointer address

   Description:    Reads the handle's device number
<
----------------------------------------------------------------------------*/
RtStatus_t GetDeviceFromHandle(int32_t HandleNumber, int32_t * pDeviceNumber)
{
    // Ensure the handle table pointer is not NULL.
    assert(Handle);

    // Check whether the passed handle number is within range
    if ((HandleNumber < 0) || (HandleNumber >= maxhandles))
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;

    if (HandleNumber == 0)
        return ERROR_OS_FILESYSTEM_HANDLE_NOT_ACTIVE;

    if (Handle[HandleNumber].HandleActive != 0)
        return ERROR_OS_FILESYSTEM_HANDLE_NOT_ACTIVE;
    else {
        *pDeviceNumber = Handle[HandleNumber].Device;
        return SUCCESS;
    }
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t UpdateHandle(int32_t HandleNumber,int32_t clusterno)

   FunctionType:  Reentrant

   Inputs:        1) Handle Number
                  2) Cluster Number

   Outputs:       Returns 0

   Description:   Updates the handle entries according to the cluster number

<
----------------------------------------------------------------------------*/
RtStatus_t UpdateHandle(int32_t HandleNumber, int32_t clusterno)
{
    // Ensure the handle table pointer is not NULL.
    assert(Handle);

    if ((HandleNumber < 0) || (HandleNumber >= maxhandles))
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;

    Handle[HandleNumber].diroffset = Handle[HandleNumber].BytePosInSector;
    Handle[HandleNumber].DirSector = Handle[HandleNumber].CurrentSector;
    Handle[HandleNumber].StartingCluster = clusterno;
    Handle[HandleNumber].CurrentCluster = clusterno;
    Handle[HandleNumber].CurrentSector =
        Firstsectorofcluster(Handle[HandleNumber].Device, clusterno);
    Handle[HandleNumber].CurrentOffset = 0;
    Handle[HandleNumber].BytePosInSector = 0;
    Handle[HandleNumber].SectorPosInCluster = 0;

    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t Handleactive(int32_t HandleNumber)

   FunctionType:   Reentrant

   Inputs:         1) Handle number

   Outputs:        Returns 0 if Handle is active else an ERROR CODE

   Description:    Checks the handle active field of the given handle number.
<
----------------------------------------------------------------------------*/
RtStatus_t Handleactive(int32_t HandleNumber)
{
    // Check whether the passed handle number is within range
    if ((HandleNumber < 0) || (HandleNumber >= maxhandles))
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;

    if (HandleNumber == 0)
        return ERROR_OS_FILESYSTEM_HANDLE_NOT_ACTIVE;

    if (Handle == NULL)
        return ERROR_OS_FILESYSTEM_HANDLE_NOT_ACTIVE;

    if (Handle[HandleNumber].HandleActive == 1)
        return SUCCESS;

    else
        return ERROR_OS_FILESYSTEM_HANDLE_NOT_ACTIVE;
}

/*----------------------------------------------------------------------------
>  Function Name: uint8_t CheckMode(uint32_t HandleNumber)

   FunctionType:  Non-Reentrant

   Inputs:        1)HandleNumber

   Outputs:       Returns Mode field of the given HandleNumber

   Description:   Finds the Mode field of the given HandleNumber
<
----------------------------------------------------------------------------*/
uint8_t CheckMode(uint32_t HandleNumber)
{
    return Handle[HandleNumber].Mode;
}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t Ferror(int32_t HandleNumber)

   FunctionType:  Reentrant

   Inputs:        1) Handle Number

   Outputs:       Returns Error code for handle

   Description:   Finds the error code in the handle table
<
----------------------------------------------------------------------------*/
int32_t Ferror(int32_t HandleNumber)
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
    return Handle[HandleNumber].ErrorCode;
}
