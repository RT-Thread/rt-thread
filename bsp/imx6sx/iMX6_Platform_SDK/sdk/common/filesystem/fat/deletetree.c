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
 $Archive: /Fatfs/FileSystem/Fat32/higherapi/DeleteTree.c $              
 $Revision: 16 $                                       
 $Date: 10/08/03 2:53p $      
 Description: DeleteTree.c
 Notes:
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
		File Includes
----------------------------------------------------------------------------*/
#include <types.h>
#include "fstypes.h"
#include "filesystem/fsapi.h"
#include "fat_internal.h"
#include "filespec.h"
#include "diroffset.h"

/*----------------------------------------------------------------------------
		Extern Declarations
----------------------------------------------------------------------------*/
extern RtStatus_t FindNext(int32_t HandleNumber, FindData_t * _finddata);
extern RtStatus_t FindFirst(FindData_t * _finddata, uint8_t * FileName);
/*----------------------------------------------------------------------------
		Global Declarations
----------------------------------------------------------------------------*/
RtStatus_t DeleteAllRecords(int32_t StartingCluster, FindData_t * _finddata);
RtStatus_t FileRemove(int32_t RecordNumber, int32_t HandleNumber);
RtStatus_t DelGetRecordNumber(int32_t HandleNumber, int32_t ClusterNumber);
RtStatus_t ChangeToLowLevelDir(int32_t HandleNumber, FindData_t * _finddata,
                               int32_t StartingCluster);
void ClearData(FindData_t * _finddata);
/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t DeleteTree(uint8_t *filePath)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to the directory path

   Outputs:       Returns 0 on success else an error code
                   
   Description:   Deletes all the files and directories of the specified path
<
----------------------------------------------------------------------------*/
RtStatus_t DeleteTree(uint8_t * filePath)
{
    RtStatus_t RetValue = SUCCESS;
    int32_t HandleNumber = 0;
    int32_t StartingCluster;
    FindData_t _finddata;
    uint8_t Buf[32];
    HandleTable_t TempHandle;
//  int64_t lTemp;

    if ((RetValue = Chdir(filePath)) < 0)
        return RetValue;

    TempHandle = Handle[CWD_HANDLE];

    if ((HandleNumber = Searchfreehandleallocate()) < 0)
        return (RtStatus_t) HandleNumber;

    Handle[HandleNumber] = Handle[CWD_HANDLE];

    if ((Handle[HandleNumber].StartingCluster) ==
        MediaTable[Handle[HandleNumber].Device].RootdirCluster)
        return ERROR_OS_FILESYSTEM_DIR_NOT_REMOVABLE;

    if ((ReadDirectoryRecord(HandleNumber, 1, Buf)) <= 0)
        return ERROR_OS_FILESYSTEM_INVALID_RECORD_NUMBER;

    // sdk 2.6 first corrected the shift direction to left instead of right.  3.095 release had left since it had fix from sdk2.6.
    StartingCluster =
        ((FSGetWord(Buf, DIR_FSTCLUSLOOFFSET)) | (FSGetWord(Buf, DIR_FSTCLUSHIOFFSET) << 16));

    if ((RetValue = Fseek(HandleNumber, 0, SEEK_SET)) < 0)
        return RetValue;

    Freehandle(HandleNumber);

    if ((RetValue =
         DeleteAllRecords(StartingCluster, &_finddata)) == ERROR_OS_FILESYSTEM_DIR_NOT_REMOVABLE) {
        Handle[CWD_HANDLE] = TempHandle;
        return SUCCESS;
    } else {
        Handle[CWD_HANDLE] = TempHandle;
        return RetValue;
    }
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t DeleteAllRecords(int32_t StartingCluster,FindData_t *_finddata)

   FunctionType:  Reentrant

   Inputs:        1) StartingCluster
                  2) FindData_t structure  

   Outputs:       Returns an Error if function fails 
                   
   Description:   Deletes all the files and directories of the specified path
<
----------------------------------------------------------------------------*/
RtStatus_t DeleteAllRecords(int32_t StartingCluster, FindData_t * _finddata)
{
    RtStatus_t RetValue = SUCCESS;
    int32_t HandleNumber = 0;
    uint8_t Buf[5];
    int32_t TemphandleNumber = 0;

    ClearData(_finddata);

    PutWord(Buf, 0x2e2a, 0);
    Buf[2] = 0x2a;

    while (1) {
        TemphandleNumber = HandleNumber;
        if ((HandleNumber = FindFirst(_finddata, (uint8_t *) Buf)) < 0) {
            /* FindFirst function returns handle number with setting mode = READ + DIRECTORY 
               so we have to set write mode for this handle */
            HandleNumber = TemphandleNumber;
            Handle[HandleNumber].HandleActive = 1;
            Handle[HandleNumber].Mode =
                (FileSystemModeTypes_t) (Handle[HandleNumber].Mode | WRITE_MODE);

            if ((RetValue = ChangeToLowLevelDir(HandleNumber, _finddata, StartingCluster)) < 0) {
                Freehandle(HandleNumber);
                return RetValue;
            }

            ClearData(_finddata);
            Freehandle(HandleNumber);
            continue;
        }
        Handle[HandleNumber].Mode =
            (FileSystemModeTypes_t) (Handle[HandleNumber].Mode | WRITE_MODE);
        if ((_finddata->attrib & DIRECTORY) == DIRECTORY) {
            if ((RetValue = ChangeToLowLevelDir(HandleNumber, _finddata, StartingCluster)) < 0) {
                Freehandle(HandleNumber);
                return RetValue;
            }

            ClearData(_finddata);
            Freehandle(HandleNumber);
            continue;
        } else {
            if ((RetValue = FileRemove(_finddata->startrecord - 1, HandleNumber)) < 0) {
                Freehandle(HandleNumber);
                return RetValue;
            }
        }
        while (1) {
            if ((RetValue = FindNext(HandleNumber, _finddata)) < 0) {
                if ((RetValue = ChangeToLowLevelDir(HandleNumber, _finddata, StartingCluster)) < 0) {
                    Freehandle(HandleNumber);
                    return RetValue;
                }
                ClearData(_finddata);
                Freehandle(HandleNumber);
                break;
            }

            if ((_finddata->attrib & DIRECTORY) == DIRECTORY) {
                if ((RetValue = ChangeToLowLevelDir(HandleNumber, _finddata, StartingCluster)) < 0) {
                    Freehandle(HandleNumber);
                    return RetValue;
                }

                ClearData(_finddata);
                Freehandle(HandleNumber);
                break;
            } else {
                if ((RetValue = FileRemove(_finddata->startrecord - 1, HandleNumber)) < 0) {
                    Freehandle(HandleNumber);
                    return RetValue;
                }
            }
        }
    }                           // while(1)
}

/*----------------------------------------------------------------------------
>  Function Name: void ClearData(FindData_t *_finddata)

   FunctionType:  Reentrant

   Inputs:        1) FindData_t Structure
                  
   Outputs:       Cleares FindData_t Structure
<
----------------------------------------------------------------------------*/
void ClearData(FindData_t * _finddata)
{
    int32_t i;
    _finddata->startrecord = 0;
    _finddata->attrib = 0;
    _finddata->FileSize = 0;
    for (i = 0; i < MAX_FILESNAME / 3; i++) {
        _finddata->name[i] = 0;
    }
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t ChangeToLowLevelDir(int32_t HandleNumber,FindData_t *_finddata,int32_t StartingCluster)

   FunctionType:  Reentrant

   Inputs:        1) Handle Number
                  2) FindData_t Structure  
                  3) Starting Cluster

   Outputs:       Returns SUCCESS on success else an Error Code
                   
   Description:   Changes to low level directory if available within the given directory 
                  and updates the Handle
<
----------------------------------------------------------------------------*/
RtStatus_t ChangeToLowLevelDir(int32_t HandleNumber, FindData_t * _finddata,
                               int32_t StartingCluster)
{
    RtStatus_t RetValue = SUCCESS;
    int32_t RecordNumber;
    uint8_t Buffer[32];
    int32_t ClusterNumber = 0;
    uint8_t Buf[5];
    // int64_t lTemp;

    PutWord(Buf, 0x2e2e, 0);

    if ((RetValue = Fseek(HandleNumber, -DIRRECORDSIZE, SEEK_CUR)))
        return RetValue;

    if ((RetValue = Isdirectoryempty(HandleNumber)) == SUCCESS) {
        if ((ReadDirectoryRecord(HandleNumber, 0, Buffer)) <= 0)
            return ERROR_OS_FILESYSTEM_NO_MATCHING_RECORD;

        // sdk2.6 changed this from right shift to a left shift.   
        ClusterNumber =
            ((FSGetWord(Buffer, DIR_FSTCLUSLOOFFSET)) |
             (FSGetWord(Buffer, DIR_FSTCLUSHIOFFSET) << 16));

        if ((RetValue = Fseek(HandleNumber, 0, SEEK_SET)) < 0)
            return RetValue;

        if ((RetValue = Chdir((uint8_t *) & Buf)) < 0)
            return RetValue;

        Handle[HandleNumber] = Handle[CWD_HANDLE];

        if ((RecordNumber = DelGetRecordNumber(HandleNumber, ClusterNumber)) < 0)
            return ERROR_OS_FILESYSTEM_NO_MATCHING_RECORD;

        if ((RetValue = FileRemove(RecordNumber, HandleNumber)) < 0)
            return RetValue;

        if (Handle[HandleNumber].StartingCluster ==
            MediaTable[Handle[HandleNumber].Device].RootdirCluster
            || Handle[HandleNumber].StartingCluster == StartingCluster)
            return ERROR_OS_FILESYSTEM_DIR_NOT_REMOVABLE;

        return SUCCESS;
    }

    if ((ReadDirectoryRecord(HandleNumber, (_finddata->startrecord - 1), Buffer)) <= 0)
        return ERROR_OS_FILESYSTEM_NO_MATCHING_RECORD;

    if ((RetValue = Fseek(HandleNumber, -DIRRECORDSIZE, SEEK_CUR)))
        return RetValue;

    // sdk2.6 changed this from a right shift to a left shift.
    ClusterNumber =
        ((FSGetWord(Buffer, DIR_FSTCLUSLOOFFSET)) | (FSGetWord(Buffer, DIR_FSTCLUSHIOFFSET) << 16));

    UpdateHandle(HandleNumber, ClusterNumber);

    Handle[CWD_HANDLE] = Handle[HandleNumber];

    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t DelGetRecordNumber(int32_t HandleNumber,int32_t StartingCluster)

   FunctionType:  Reentrant

   Inputs:        1) Handle Number
                  2) Starting Cluster  

   Outputs:       Updated Record number else an Error 
                   
   Description:   Updates Record Number as per deleted directory record
<
----------------------------------------------------------------------------*/
RtStatus_t DelGetRecordNumber(int32_t HandleNumber, int32_t StartingCluster)
{

    int32_t RecordNumber = 0;
    uint8_t Buffer[32];
    int32_t Byte1, Byte2;
    int32_t ClusterNumber;
    //int64_t lTemp;

    while (1) {
        if (ReadDirectoryRecord(HandleNumber, RecordNumber, Buffer) < 0)
            return ERROR_OS_FILESYSTEM_NO_MATCHING_RECORD;

        if ((Byte1 = FSGetByte(Buffer, 0)) == 0)
            return ERROR_OS_FILESYSTEM_FS_ERROR;

        if (Byte1 == 0x2e) {
            RecordNumber++;
            continue;
        }

        if ((Byte2 = FSGetByte(Buffer, DIR_ATTRIBUTEOFFSET)) == LONGDIRATTRIBUTE) {
            RecordNumber++;
            continue;
        }
        // sdk2.6 changed this from a right shift to a left shift.
        ClusterNumber =
            ((FSGetWord(Buffer, DIR_FSTCLUSLOOFFSET)) |
             (FSGetWord(Buffer, DIR_FSTCLUSHIOFFSET) << 16));

        if ((Byte1 != 0xe5) && ((Byte2 & DIRECTORY) == DIRECTORY)
            && (StartingCluster == ClusterNumber))
            break;

        RecordNumber++;
    }
    return (RtStatus_t) RecordNumber;
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t FileRemove(int32_t RecordNumber,int32_t HandleNumber)

   FunctionType:  Reentrant

   Inputs:        1) Record Number
                  2) Handle Number  

   Outputs:       Returns SUCCESS on success else an Error Code 
                   
   Description:   Updates the handle to associate with the file to be deleted and
                  deletes the contents of the file i.e. marks all the clusters occupied by 
	              the file as zero in FAT Table.

<
----------------------------------------------------------------------------*/
RtStatus_t FileRemove(int32_t RecordNumber, int32_t HandleNumber)
{
    RtStatus_t RetValue = SUCCESS;
    uint8_t Buffer[32];
    int32_t ClusterNumber = 0, FileSize;
    HandleTable_t Temp;
    //  int64_t lTemp;

    Temp = Handle[HandleNumber];

    if (Handle[HandleNumber].StartingCluster != 0) {
        if ((RetValue = Fseek(HandleNumber, -DIRRECORDSIZE, SEEK_CUR)))
            return RetValue;
    }

    if (ReadDirectoryRecord(HandleNumber, RecordNumber, Buffer) < 0)
        return ERROR_OS_FILESYSTEM_NO_MATCHING_RECORD;

    if (Handle[HandleNumber].StartingCluster != 0) {
        if ((RetValue = Fseek(HandleNumber, -DIRRECORDSIZE, SEEK_CUR)))
            return RetValue;
    }

    if ((RetValue = DeleteRecord(HandleNumber, RecordNumber)) < 0)
        return RetValue;

    /* Set the Handle to original position */
    if ((RetValue = Fseek(HandleNumber, (RecordNumber * DIRRECORDSIZE), SEEK_SET)) < 0)
        return RetValue;

    FileSize = FSGetDWord(Buffer, DIR_FILESIZEOFFSET);

    // sdk2.6 changed this to left shift instead of right shift. 
    ClusterNumber =
        ((FSGetWord(Buffer, DIR_FSTCLUSLOOFFSET)) | (FSGetWord(Buffer, DIR_FSTCLUSHIOFFSET) << 16));

    if (((FSGetByte(Buffer, DIR_ATTRIBUTEOFFSET)) & DIRECTORY_MODE) == DIRECTORY_MODE)
        FileSize = 0x7fffffff;

    if ((ClusterNumber != 0) && (FileSize) != 0) {
        /* update the handle to associate with the file to be deleted */
        UpdateHandle(HandleNumber, ClusterNumber);

        /* Delete the contents of the file (i.e. Mark all the clusters occupied by 
           the file as zero in FAT Table) */
        if ((RetValue = DeleteContent(HandleNumber, 0)) < 0)
            return RetValue;
    }
    Handle[HandleNumber] = Temp;

    return SUCCESS;
}
