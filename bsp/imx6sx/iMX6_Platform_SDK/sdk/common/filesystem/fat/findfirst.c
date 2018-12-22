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
 $Archive: /Fatfs/FileSystem/Fat32/higherapi/FindFirst.c $
 $Revision: 12 $
 $Date: 10/17/03 9:43a $
 Description: FindFirst.c
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
extern FileSpecs_t *filespec;
// extern RtStatus_t FindNext(int32_t HandleNumber,FindData_t *_finddata);

/*----------------------------------------------------------------------------
		Global Declarations
----------------------------------------------------------------------------*/
static uint8_t *CharacterSearch(uint8_t * buf, uint8_t Character);
static int32_t StringCompare(uint8_t * Buffer, uint8_t * DestBufffer, int32_t StringLength,
                             int32_t Offset);

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t FindFirst(FindData_t *_finddata,uint8_t *FileName)

   FunctionType:  Reentrant but this function should not be called from multiple task

   Inputs:        1) File Specification(Structure)
				  2) Pointer to file name

   Outputs:       Returns 0 on Success else an ErrorCode if Error occurs

   Description:   It provides base, the file name and the extension of the file
   				  to the FindNext() function
<
----------------------------------------------------------------------------*/
RtStatus_t FindFirst(FindData_t * _finddata, uint8_t * FileName)
{
    int32_t StringLength;
    uint8_t Buffer[MAX_FILESNAME * 3];
    int32_t HandleNumber;
    uint8_t *Ptr, *Ptr1;
    int32_t i;

    if ((StringLength = Strlength(FileName)) > (MAX_FILESNAME - 1))
        return ERROR_OS_FILESYSTEM_LONG_FILE_NAME;

    _finddata->startrecord = 0; //modify: It must start from 0th record
    for (i = 0; i < MAX_FILESNAME * 3; i++)
        Buffer[i] = 0;
    if ((HandleNumber = Searchfreehandleallocate()) < 0)
        return (RtStatus_t) HandleNumber;

    Handle[HandleNumber] = Handle[CWD_HANDLE];

    Handle[HandleNumber].Mode = (FileSystemModeTypes_t) (READ_MODE | DIRECTORY_MODE);

    Uppercase(FileName);

    for (i = 0; i < StringLength; i++) {
        Buffer[i] = FSGetByte(FileName, i);
    }

    filespec[HandleNumber].DirAttribute = _finddata->attrib;
    filespec[HandleNumber].FileExtension[0] = 0;
    Ptr = CharacterSearch(Buffer, '.');
    if (Ptr) {
        Ptr1 = CharacterSearch(Ptr, '*');

        if (Ptr1)
            *Ptr1 = 0;
        for (i = 0; i < 4; i++) {
            filespec[HandleNumber].FileExtension[i] = FSGetByte(Ptr, i + 1);
        }
        Ptr[0] = 0;
    }

    if (CharacterSearch(Buffer, '*')) {
        *CharacterSearch(Buffer, '*') = 0;
    }

    for (i = 0; i < 9; i++) {
        filespec[HandleNumber].FileName[i] = FSGetByte(Buffer, i);
    }
    filespec[HandleNumber].gCurrentRecord = _finddata->startrecord;

    if (!(FindNext(HandleNumber, _finddata)))
        return (RtStatus_t) HandleNumber;
    else {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_NO_MATCHING_RECORD;
    }
}

/*----------------------------------------------------------------------------
>  Function Name: uint8_t *CharacterSearch(uint8_t *buf,uint8_t Character)

   FunctionType:  Non-Reentrant

   Inputs:        1) Pointer to buffer
                  2) Character

   Outputs:       Pointer to character

   Description:   It searches the character
<
----------------------------------------------------------------------------*/
//Use the exact same prototype of the static function to convert

uint8_t *CharacterSearch(uint8_t * buf, uint8_t Character)
{
    uint8_t *Buf = buf;
    while (Buf[0] != '\0') {
        if (*Buf == Character)
            return Buf;
//      *Buf++; //original code, not sure it is right ???
        Buf++;
    }

    return (uint8_t *) 0;
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t FindNext(int32_t HandleNumber,FindData_t *_finddata)

   FunctionType:  Reentrant but this function should not be called from multiple task

   Inputs:        1)Handle Number
                  2)File Specification Structure

   Outputs:       Returns 0 on Success else an ErrorCode if Error occurs 

   Description:   It reads the directory record from the given record and finds 
   				  the first file or directory which matches the specifications.
<
----------------------------------------------------------------------------*/
RtStatus_t FindNext(int32_t HandleNumber, FindData_t * _finddata)
{
    int32_t RetValue = 0, Byte, i = 0, j = 0;
    uint8_t Buffer[32];
    RtStatus_t Return = ERROR_OS_FILESYSTEM_NO_MATCHING_RECORD;
    int64_t key;

    if ((HandleNumber < 0) || (HandleNumber >= maxhandles))
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;

    if ((RetValue = Handleactive(HandleNumber)) < 0)
        return ERROR_OS_FILESYSTEM_HANDLE_NOT_ACTIVE;

    while (1) {
        if ((key =
             ReadDirectoryRecord(HandleNumber, filespec[HandleNumber].gCurrentRecord++,
                                 Buffer)) <= 0)
            return ERROR_OS_FILESYSTEM_NO_MATCHING_RECORD;

        // Check for Long File name
        if ((FSGetByte(Buffer, DIR_ATTRIBUTEOFFSET)) == LONGDIRATTRIBUTE)
            continue;
        Byte = FSGetByte(Buffer, DIR_NAMEOFFSET);
        // Check for . and .. Entry
        if (Byte == '.')
            continue;
        // End of directories
        if (Byte == 0)
            break;
        else {
            if (Byte != 0xe5) { // Check for kanji fix
                if (Byte == 0x05)
                    PutByte(Buffer, 0xe5, 0);
                if (!
                    (RetValue =
                     StringCompare(Buffer, filespec[HandleNumber].FileName,
                                   Strlength(filespec[HandleNumber].FileName), 0))) {
                    if (!
                        (RetValue =
                         StringCompare(Buffer, filespec[HandleNumber].FileExtension,
                                       Strlength(filespec[HandleNumber].FileExtension), 8))) {
                        for (i = 0; i < 8; i++) {
                            if ((Byte = FSGetByte(Buffer, i)) == ' ')
                                break;
                            else
                                PutByte(_finddata->name, Byte, i);
                        }
                        if ((Byte = FSGetByte(Buffer, 8)) != ' ')
                            PutByte(_finddata->name, '.', i);
                        else
                            PutByte(_finddata->name, 0, i);
                        i++;

                        for (j = 8; j < 11; j++) {
                            if ((Byte = FSGetByte(Buffer, j)) == ' ')
                                break;
                            else
                                PutByte(_finddata->name, Byte, i++);
                        }
                        PutByte(_finddata->name, 0, i);
                        _finddata->attrib = FSGetByte(Buffer, DIR_ATTRIBUTEOFFSET);
                        _finddata->startrecord = filespec[HandleNumber].gCurrentRecord;
                        _finddata->FileSize = FSGetDWord(Buffer, DIR_FILESIZEOFFSET);
                        _finddata->Key = key;
                        Return = SUCCESS;
                        break;
                    }
                }
            }
        }
    }                           // while(1)

    (void)RetValue;
    return Return;
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t StringCompare(uint8_t *Buffer,uint8_t *DestBufffer,int32_t StringLength,int32_t Offset)

   FunctionType:  Non-Reentrant
   
   Inputs:        1)Pointer to buffer
                  2)Pointer to destination buffer
                  3)String length
                  4)Offset

   Outputs:       Returns 0  or  1

   Description:   Compares the string.
<
----------------------------------------------------------------------------*/
int32_t StringCompare(uint8_t * Buffer, uint8_t * DestBufffer, int32_t StringLength, int32_t Offset)
{
    int32_t i = 0, Byte, j = 0;
    int32_t RetValue = 1;
    for (i = 0; i < StringLength; i++) {
        if ((Byte = FSGetByte(DestBufffer, i)) == '\0')
            break;
        if ((Byte == FSGetByte(Buffer, i + Offset)))
            j++;
    }
    if (j == StringLength)
        return 0;

    return RetValue;
}
