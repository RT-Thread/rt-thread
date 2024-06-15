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
 $Archive: /Fatfs/FileSystem/Fat32/higherapi/Chdir.c $                                        
 $Revision: 7 $                                       
 $Date: 9/13/03 12:22p $                                           
 Description: Chdir.c
 Notes:	This file read provides higherlevel API function to change the current working directory
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
		File Includes
----------------------------------------------------------------------------*/
#include <types.h>
#include "fstypes.h"
#include "fat_internal.h"
#include "filesystem/fsapi.h"
#include "bootsecoffset.h"
#include "diroffset.h"
#include <string.h>

// Previously the size of the following global variable was 
// MAX_FILENAME_LENGTH*2.  That's not nearly enough since
// Artist name and Album name can both be of size
// MAX_FILENAME_LENGTH.
#ifdef CWD_STRING

// This padding is here to provide a safety buffer if code writes to negative offsets
// from the start of gCurrentWorkingdirectory. This is a possibility because the cwd
// is treated as both ASCII and UTF-16 at the same time, interchangeably even
// within a single function. Not good.  
uint8_t __fs_padding[4];

uint8_t gCurrentWorkingdirectory[MAX_FILENAME_LENGTH * 2];

#endif // CWD_STRING

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t Chdir(uint8_t *filepath)

   FunctionType:   Reentrant

   Inputs:         1) Pointer to file name
				   
   Outputs:        SUCCESS or error code if error occurs      
   
   Description:    Searches for the given directoy path and if the path is found 
                   then changes the current working directoy to the given directory path 
----------------------------------------------------------------------------*/
RtStatus_t Chdir(uint8_t * filepath)
{
    uint32_t HandleNumber = 0, strlen;
    RtStatus_t Retval;
    int32_t clusterno = 0;
    int32_t RecordNo;
    int32_t Dir_Attr;
#ifdef CWD_STRING
    uint32_t Firstchar, secondchar;
    int32_t offset = 0, currentposition = 0, offset_dest = 0;
#endif
    int32_t index = 0;
    uint8_t buf[32];

    /* Take temporary(directory)handle for searching the directory by changing path */
    HandleNumber = DIRECTORY_HANDLE;

    /* if the temporary handle is already active then change path is not possible */
    if (Handleactive(HandleNumber) == SUCCESS)
        return ERROR_OS_FILESYSTEM_CHANGEPATH_NOT_POSSIBLE;
    Handle[HandleNumber].HandleActive = 1;

    /* first set the handle for search */
    if ((Retval = SetHandleforsearch(HandleNumber, filepath, kDBCSEncoding, &index)) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
    }

    if (Retval != END_OF_DIR_PATH) {
        strlen = Strlength(filepath);
        /* Change the path to the specified path given */
        if ((clusterno = Changepath(HandleNumber, filepath, kDBCSEncoding, strlen, index)) < 0) {
            Freehandle(HandleNumber);
            return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
        }
        UpdateHandle(HandleNumber, clusterno);
    }
    if (Retval != END_OF_DIR_PATH) {
        RecordNo = Handle[HandleNumber].CurrentOffset >> 5;
        /* check the attribute if it is not a directory, return error */
        if (ReadDirectoryRecord(HandleNumber, RecordNo, buf) < 0) {
            Freehandle(HandleNumber);
            return ERROR_OS_FILESYSTEM_INVALID_RECORD_NUMBER;
        }

        Dir_Attr = FSGetByte(buf, DIR_ATTRIBUTEOFFSET);
        if (!(Dir_Attr & DIRECTORY)) {
            Freehandle(HandleNumber);
            return ERROR_OS_FILESYSTEM_CHANGEPATH_NOT_POSSIBLE;
        }

        /* set the handle to original position */
        if (Handle[HandleNumber].StartingCluster != 0) {
            if ((Retval = Fseek(HandleNumber, -DIRRECORDSIZE, SEEK_CUR)) < 0)
                return Retval;
        }
    }
    /* copy the handle to handle 0 to change the current working directory */
    Handle[0] = Handle[HandleNumber];

    /* Free the handle used for file search */
    Freehandle(HandleNumber);
#ifdef CWD_STRING
    currentposition = Strlength((uint8_t *) gCurrentWorkingdirectory);

    /* set the gCurrentWorkingdirectory buffer to the changed directory */
    offset = 0;
    Firstchar = GetChar(filepath, &offset);
    secondchar = GetChar(filepath, &offset);
    strlen = Strlength(filepath);
    if (secondchar == ':') {
        // Need to copy three Null terminating characters.  That is the
        // reason for strlen+2 and not strlen. This causes code that sees cwd as either ASCII or UTF-16
        // to see the same end of string.
        Strcpy(filepath, (uint8_t *) gCurrentWorkingdirectory, strlen + 2, 0);
        return (SUCCESS);
    }

    else if (Firstchar == '/') {
        PutChar((uint8_t *) gCurrentWorkingdirectory, &offset, 0);
        currentposition = Strlength((uint8_t *) gCurrentWorkingdirectory);
    }

    else if (Firstchar == '.') {
        if (secondchar != '.') {
            currentposition = Strlength((uint8_t *) gCurrentWorkingdirectory);
        } else {
            offset = 0;
            currentposition = 0;
            strlen = Strlength((uint8_t *) gCurrentWorkingdirectory);
            while (Firstchar == '.' && secondchar == '.') {
                strlen =
                    Extractfilename((uint8_t *) gCurrentWorkingdirectory, strlen, &currentposition);
                if ((ExtractPath(filepath, &offset)) == END_OF_DIR_PATH)
                    break;
                offset_dest = offset;
                Firstchar = GetChar(filepath, &offset_dest);
                secondchar = GetChar(filepath, &offset_dest);
            }
            index = offset;
            currentposition = strlen - 1;
        }
    }

    Setcwd(filepath, (uint8_t *) gCurrentWorkingdirectory, index, currentposition);
#endif
    return (SUCCESS);
}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t Chdirw(uint8_t *filepath)

   FunctionType:   Reentrant

   Inputs:         1) Pointer to file name
				   
   Outputs:        SUCCESS or error code if error occurs      
   
   Description:    Searches for the given directoy path for UTF16 string and if the path is found 
                   then changes the current working directoy to the given directory path 
----------------------------------------------------------------------------*/
RtStatus_t Chdirw(uint8_t * filepath)
{
    uint32_t HandleNumber = 0, strlen;
    RtStatus_t Retval;
    int32_t clusterno = 0;
#ifdef CWD_STRING
    int32_t Firstword, secondword;
    int32_t offset = 0, currentposition = 0, offset_dest = 0;
#endif
    int32_t index = 0;
    uint8_t buf[32];
    int32_t RecordNo;
    int32_t Dir_Attr;

    /* Take temporary(directory)handle for searching the directory by changing path */
    HandleNumber = DIRECTORY_HANDLE;

    /* if the temporary handle is already active then change path is not possible */
    if (Handleactive(HandleNumber) == SUCCESS)
        return ERROR_OS_FILESYSTEM_CHANGEPATH_NOT_POSSIBLE;
    Handle[HandleNumber].HandleActive = 1;

    /* first set the handle for search */
    if ((Retval = SetHandleforsearch(HandleNumber, filepath, kUTF16Encoding, &index)) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
    }

    if (Retval != END_OF_DIR_PATH) {
        strlen = StrlengthW((uint8_t *) filepath);
        /* Change the path to the specified path given */
        if ((clusterno = Changepath(HandleNumber, filepath, kUTF16Encoding, strlen * 2, index)) < 0) {
            Freehandle(HandleNumber);
            return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
        }
        UpdateHandle(HandleNumber, clusterno);
    }
    /*Any one try to change the file without extension using chdir function then return error */
    if (Retval != END_OF_DIR_PATH) {
        RecordNo = Handle[HandleNumber].CurrentOffset >> 5;
        /* check the attribute if it is not a directory, return error */
        if (ReadDirectoryRecord(HandleNumber, RecordNo, buf) < 0) {
            Freehandle(HandleNumber);
            return ERROR_OS_FILESYSTEM_INVALID_RECORD_NUMBER;
        }

        Dir_Attr = FSGetByte(buf, DIR_ATTRIBUTEOFFSET);
        if (!(Dir_Attr & DIRECTORY)) {
            Freehandle(HandleNumber);
            return ERROR_OS_FILESYSTEM_CHANGEPATH_NOT_POSSIBLE;
        }
    }

    /* copy the handle to handle 0 to change the current working directory */
    Handle[0] = Handle[HandleNumber];

    /* Free the handle used for file search */
    Freehandle(HandleNumber);
#ifdef CWD_STRING
    currentposition = StrlengthW((uint8_t *) gCurrentWorkingdirectory);

    /* set the gCurrentWorkingdirectory buffer to the changed directory */
    offset = 0;
    Firstword = GetCharW(filepath, &offset);
    secondword = GetCharW(filepath, &offset);
    strlen = StrlengthW(filepath);
    if (secondword == ':') {
        Strcpyw(filepath, (uint8_t *) gCurrentWorkingdirectory, strlen * 2, 0);
        return (SUCCESS);
    }

    else if (Firstword == '/') {
        PutCharW((uint8_t *) gCurrentWorkingdirectory, &offset, 0);
        currentposition = StrlengthW((uint8_t *) gCurrentWorkingdirectory);
    }

    else if (Firstword == '.') {
        if (secondword != '.') {
            currentposition = StrlengthW((uint8_t *) gCurrentWorkingdirectory);
        } else {
            offset = 0;
            currentposition = 0;
            strlen = StrlengthW((uint8_t *) gCurrentWorkingdirectory);
            strlen += strlen;
            while (Firstword == '.' && secondword == '.') {
                strlen =
                    Extractdirnamew((uint8_t *) gCurrentWorkingdirectory, strlen, &currentposition);
                if ((ExtractPathW(filepath, &offset)) == END_OF_DIR_PATH)
                    break;
                offset_dest = offset;
                Firstword = GetCharW(filepath, &offset_dest);
                secondword = GetCharW(filepath, &offset_dest);
            }
            index = offset;
            currentposition = strlen - 2;
        }
    }
    SetcwdW(filepath, (uint8_t *) gCurrentWorkingdirectory, index, currentposition);
#endif
    return (SUCCESS);
}

/*----------------------------------------------------------------------------
>  Function Name: uint8_t *Getcwd(void)

   FunctionType:  Reentrant

   Inputs:        void
				   
   Outputs:       Pointer to current working directory buffer      
   
   Description:   This function returns the pointer to the gCurrentWorkingdirectory
                  string buffer.
----------------------------------------------------------------------------*/
uint8_t *Getcwd(void)
{
#ifdef CWD_STRING
    return gCurrentWorkingdirectory;
#else
    return NULL;
#endif

}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t Changepath(int32_t HandleNumber,uint8_t *filepath,int32_t stringtype,int32_t startposition,int32_t index)

   FunctionType:   Reentrant

   Inputs:         1) Handle number
                   2) Pointer to file name
				   3) string type
                   4) start position
                   5) index

   Outputs:        Returns ERROR_OS_FILESYSTEM_FILE_FOUND  if the file is found otherwise ERROR_OS_FILESYSTEM_FILE_NOT_FOUND

   Description:    This function searches for file or directory in the directory
                   identified by the given file handle. Every time when directory
                   within the file path is found the handle is updated according
                   to the directory record.
----------------------------------------------------------------------------*/
RtStatus_t Changepath(int32_t HandleNumber, uint8_t * filepath, int32_t stringtype,
                      int32_t startposition, int32_t index)
{
    int32_t strlength, length;
    int32_t clusterno = 0;
    int32_t currentposition = index;
    int32_t RecordNum = 0;
#if 0                           //def FS_USE_MALLOC <-- there is a bug in this function with this enabled, see SDK-4470
    uint8_t *Buffer;
    Buffer = malloc(512 * sizeof(uint8_t));
    if (NULL == Buffer) {
        return ERROR_OS_FILESYSTEM_MEMORY;
    }
#else
    uint8_t Buffer[512];
#endif

    if (stringtype == kDBCSEncoding) {
        strlength = startposition;
        while (currentposition < strlength) {
            length = Getname(filepath, currentposition);
            if ((clusterno =
                 Searchdirectory(HandleNumber, filepath, stringtype, 1, length, currentposition,
                                 Buffer, 0, &RecordNum)) >= 0) {
                currentposition = length;
                if (currentposition < strlength) {
                    UpdateHandle(HandleNumber, clusterno);
                }
            } else {
#if 0                           //def FS_USE_MALLOC
                free(Buffer);
#endif
                return (ERROR_OS_FILESYSTEM_FILE_NOT_FOUND);
            }
        }
    }

    if (stringtype == kUTF16Encoding) {
        strlength = startposition;
        while (currentposition < strlength) {
            length = GetnameW(filepath, currentposition);
            if ((clusterno =
                 Searchdirectory(HandleNumber, filepath, stringtype, 1, length, currentposition,
                                 Buffer, 0, &RecordNum)) >= 0) {
                currentposition = length;
                if (currentposition < strlength) {
                    UpdateHandle(HandleNumber, clusterno);
                }
            } else {
#if 0                           //def FS_USE_MALLOC
                free(Buffer);
#endif
                return (ERROR_OS_FILESYSTEM_FILE_NOT_FOUND);
            }
            currentposition = currentposition + 2;
        }
    }
#if 0                           //def FS_USE_MALLOC
    free(Buffer);
#endif
    return ((RtStatus_t) clusterno);

}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t ChangeToRootdirectory(int32_t HandleNumber)

   FunctionType:  Reentrant

   Inputs:        1)HandleNumber
                 
   Outputs:       Returns SUCCESS or an error code if an Error occurs

   Description:   Sets the handle to Root directory of given device number
<	 
----------------------------------------------------------------------------*/
RtStatus_t ChangeToRootdirectory(int32_t HandleNumber)
{
    int32_t DeviceNum;

    if ((HandleNumber < 0) || (HandleNumber >= maxhandles))
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;

    DeviceNum = Handle[HandleNumber].Device;

    if (MediaTable[DeviceNum].FATType == FAT12 || MediaTable[DeviceNum].FATType == FAT16) {
        Handle[HandleNumber].StartingCluster = 0;
        Handle[HandleNumber].CurrentCluster = 0;
        Handle[HandleNumber].CurrentSector = MediaTable[DeviceNum].FirRootdirsec;
    }

    else if (MediaTable[DeviceNum].FATType == FAT32) {
        Handle[HandleNumber].StartingCluster = MediaTable[DeviceNum].RootdirCluster;
        Handle[HandleNumber].CurrentCluster = MediaTable[DeviceNum].RootdirCluster;
        Handle[HandleNumber].CurrentSector =
            Firstsectorofcluster(DeviceNum, MediaTable[DeviceNum].RootdirCluster);
    } else
        return ERROR_OS_FILESYSTEM_MEDIA_TYPE_NOT_SUPPORTED;

    Handle[HandleNumber].CurrentOffset = 0;
    Handle[HandleNumber].BytePosInSector = 0;
    Handle[HandleNumber].SectorPosInCluster = 0;
    Handle[HandleNumber].DirSector = 0;
    Handle[HandleNumber].diroffset = 0;
    Handle[HandleNumber].FileSize = 0;

    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t Searchdirectory(int32_t HandleNumber,uint8_t *file,int32_t stringtype,int32_t Flag,int32_t length,int32_t index,uint8_t *Buffer,BOOL bInputIsSFN)

   FunctionType:   Reentrant

   Inputs:         1) Handle Number
                   2) Pointer to file name
				   3) String type
                   4) Flag
                   5) Length
                   6) Index
                   7) Pointer to buffer 
                   8) bInputIsSFN 
				   
   Outputs:        Starting cluster of the directory found or an error code
                   if function fails. 
   
   Description:    This function checks the directory record from record number 0 
                   to the end of directory for matching the file/directory name.  
----------------------------------------------------------------------------*/
int32_t Searchdirectory(int32_t HandleNumber, uint8_t * file, int32_t stringtype, int32_t Flag,
                        int32_t length, int32_t index, uint8_t * Buffer, bool bSearchFlag,
                        int32_t * pLastRecordnum)
{
    int32_t clusterlo, filefound = 0, strlen, offset;
    int32_t Char, dirattribute, Flag1 = 0;
    uint8_t buf[32];
    int32_t clusterno;
    int32_t byte, byte1;
    int32_t RecordNo;

    int64_t Retval;
    int32_t i32ScanFlag = 0;

#ifdef FS_USE_MALLOC
    uint8_t *Shortname;
    int32_t *ucs2buffer;
    Shortname = malloc(256 * sizeof(uint8_t));
    if (NULL == Shortname) {
        return ERROR_OS_FILESYSTEM_MEMORY;
    }
    ucs2buffer = malloc(128 * sizeof(int32_t));
    if (NULL == ucs2buffer) {
        free(Shortname);
        return ERROR_OS_FILESYSTEM_MEMORY;
    }
#else
    uint8_t Shortname[256];
    int32_t ucs2buffer[128];
#endif

    offset = index;

    byte = GetChar(file, &offset);
    byte1 = GetChar(file, &offset);
    strlen = length - index - 1;
    /* Special case of .. entry */
    if ((byte == 0x2e && byte1 == 0x2e) && strlen == 2) {
        PutWord(Shortname, 0x2e2e, 0);
        PutByte(Shortname, 0, 2);
    } else {
        if (stringtype == kDBCSEncoding)    //Check whether string type is kDBCSEncoding or kUTF16Encoding 
        {
            length = DiscardTrailigPeriods(file, length, index, 1);
            Flag1 = ConverToShortname(file, (uint8_t *) Shortname, index, length);
            Uppercase((uint8_t *) Shortname);
        } else                  //If kUTF16Encoding then create shortname for long directory and pass this buffer to MatchdirRecordW.

        {
            Strcpyw((uint8_t *) file, (uint8_t *) ucs2buffer, length, index);
            UnicodeToOEM((uint8_t *) ucs2buffer, (uint8_t *) Shortname, length - index, 0);
            Uppercase((uint8_t *) Shortname);
        }
    }
#ifdef FS_USE_MALLOC
    free(ucs2buffer);
#endif

    if (bSearchFlag == 0) {
        RecordNo = 0;
        *pLastRecordnum = 0;
    } else {
        RecordNo = *pLastRecordnum;
    }

    do {
        if ((Retval = ReadDirectoryRecord(HandleNumber, RecordNo, buf)) < 0) {
#ifdef FS_USE_MALLOC
            free(Shortname);
#endif
            return ERROR_OS_FILESYSTEM_FILE_NOT_FOUND;
        }

        Char = 0;
        Char = GetChar((uint8_t *) buf, &Char);
        // A free record is found, if Char is 0
        if (Char == 0) {
            if (bSearchFlag == 1) {
                RecordNo = 0;
                i32ScanFlag++;
            } else
                break;
        }
        dirattribute = FSGetByte(buf, DIR_ATTRIBUTEOFFSET);
        if (stringtype == kDBCSEncoding) {
            if (!(dirattribute & VOLUME_ID)) {
                if (dirattribute != LONGDIRATTRIBUTE) {
                    filefound =
                        Shortdirmatch(HandleNumber, RecordNo, file, (uint8_t *) Shortname, buf,
                                      Flag1, index, length, Buffer);
                }

            }
        }
        if (stringtype == kUTF16Encoding) {
            if ((filefound =
                 MatchdirRecordW(HandleNumber, RecordNo, file, buf, index, length,
                                 (uint8_t *) Shortname)) == ERROR_OS_FILESYSTEM_FILE_FOUND) {
                dirattribute = FSGetByte(buf, DIR_ATTRIBUTEOFFSET);
                if (dirattribute == LONGDIRATTRIBUTE) {
                    if (!((FSGetWord(file, index) == 0x2E) && (FSGetWord(file, (index + 2)) == 0x2E)
                          && ((length - index) == 4))) {
                        RecordNo++;
                        if ((Retval = ReadDirectoryRecord(HandleNumber, RecordNo, buf)) < 0) {
#ifdef FS_USE_MALLOC
                            free(Shortname);
#endif
                            return ERROR_OS_FILESYSTEM_FILE_NOT_FOUND;
                        }
                    }
                }
            }
        }

        if (filefound == ERROR_OS_FILESYSTEM_FILE_FOUND) {
            if (Handle[HandleNumber].StartingCluster != 0)
                Fseek(HandleNumber, RecordNo * 32, SEEK_SET);
            else
                SetcurrentPos(HandleNumber, RecordNo);

            clusterlo = FSGetWord(buf, DIR_FSTCLUSLOOFFSET);
            clusterno = FSGetWord(buf, DIR_FSTCLUSHIOFFSET);
            clusterno = (int32_t) clusterlo + (clusterno << 16);
            Handle[HandleNumber].FileSize = FSGetDWord((uint8_t *) buf, DIR_FILESIZEOFFSET);
            if (bSearchFlag == 1) {
                *pLastRecordnum = RecordNo;
            }
#ifdef FS_USE_MALLOC
            free(Shortname);
#endif
            return (clusterno);
        }

        RecordNo++;
        if (i32ScanFlag) {
            if (RecordNo >= *pLastRecordnum)
                break;
        }
    } while (1);
#ifdef FS_USE_MALLOC
    free(Shortname);
#endif

    //change is applied upto end of file    
    // changes added to support special short file names  16/9/2004
    // When five or more files exist that can result in duplicate short file names, Windows XP Professional
    // uses a slightly different method for creating short file names.
    // For the fifth and subsequent files, Windows XP Professional:
    //    Uses only the first two letters of the long file name. 
    //Generates the next four letters of the short file name by mathematically manipulating the remaining letters of the long file name. 
    // to support this we have to again go for long directory name match if string type is kDBCSEncoding and if this function is not called from setshortfilename()

    if (stringtype == kDBCSEncoding && Flag == 1) {
        RecordNo = 0;
        do {
            if ((Retval = ReadDirectoryRecord(HandleNumber, RecordNo, buf)) < 0)
                return ERROR_OS_FILESYSTEM_FILE_NOT_FOUND;

            Char = 0;
            Char = FSGetByte(buf, 0);
            if (Char == 0)
                break;
            dirattribute = FSGetByte(buf, DIR_ATTRIBUTEOFFSET);

            if (dirattribute == LONGDIRATTRIBUTE) {
                if (Char == 1 || Char == 0x41) {
                    RecordNo++;
                    DBCStoUnicode(file, (uint8_t *) Buffer, index, length);
                    strlen = StrlengthW((uint8_t *) Buffer);
                    strlen = strlen << 1;
                    filefound =
                        Longdirmatch(HandleNumber, RecordNo, (uint8_t *) Buffer, 0, strlen, UCS2s);

                    if (filefound == ERROR_OS_FILESYSTEM_FILE_FOUND) {
                        if ((Retval = ReadDirectoryRecord(HandleNumber, RecordNo, buf)) < 0) {
                            return ERROR_OS_FILESYSTEM_FILE_NOT_FOUND;
                        }
                        if (Handle[HandleNumber].StartingCluster != 0)
                            Fseek(HandleNumber, RecordNo * 32, SEEK_SET);
                        else
                            SetcurrentPos(HandleNumber, RecordNo);
                        clusterlo = FSGetWord(buf, DIR_FSTCLUSLOOFFSET);
                        clusterno = FSGetWord(buf, DIR_FSTCLUSHIOFFSET);
                        clusterno = (int32_t) clusterlo + (clusterno << 16);
                        Handle[HandleNumber].FileSize =
                            FSGetDWord((uint8_t *) buf, DIR_FILESIZEOFFSET);
                        return (clusterno);
                    }
                }
            }

            RecordNo++;

        } while (Retval != 0);

    }
    return (ERROR_OS_FILESYSTEM_FILE_NOT_FOUND);
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t SetHandleforsearch(int32_t HandleNumber,uint8_t *filepath,int32_t stringtype,int32_t *index)

   FunctionType:  Reentrant

   Inputs:        1) Handle Number 
                  2) Pointer to file name
                  3) Stringtype
                  4) Index
				   
   Outputs:       Fields of Handle is set according to the given file path. 

   Description:   This function searches whether the file path is from root directory,
                  current working directory or parent directory based on the 
                  file path given. It sets the given handle based on this search.
----------------------------------------------------------------------------*/
int32_t SetHandleforsearch(int32_t HandleNumber, uint8_t * filepath, int32_t stringtype,
                           int32_t * index)
{
    int32_t Firstword = 0, secondword = 0, clusterlo, offset = 0;
    int64_t NumBytesRead;
    int32_t i;
    uint8_t buf[32];
    int32_t clusterno;
    int32_t Firstchar = 0, secondchar = 0;
    int32_t numdots = 0, Byte, Count = 0;

    *index = 0;
    if (HandleNumber > maxhandles)
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;

    Count = Strlength(filepath);
    for (i = 0; i <= Count; i++) {
        Byte = FSGetByte((uint8_t *) filepath, i);
        if (Byte == 0x2e) {
            //This is to check number of .(dots) in between '/'(slashes) or '\0' (null character)
            //If .(dots) are greater than 2 return error
            while (1) {
                Byte = FSGetByte((uint8_t *) filepath, i);
                i++;
                if (Byte == 0x2e)
                    numdots++;
                if (Byte != 0x2e)
                    break;
            }
            if ((numdots > 2) && ((Byte == '\0') || (Byte == '/')))
                return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
            //Reset the .(dot) count as new set of .(dots) will start with new count
            numdots = 0;
        }
    }
    if (stringtype == kDBCSEncoding) {
        Firstchar = GetChar(filepath, &offset);
        secondchar = GetChar(filepath, &offset);
    } else if (stringtype == kUTF16Encoding) {
        Firstword = FSGetWord(filepath, 0);
        secondword = FSGetWord(filepath, 2);
    }

    if (secondchar == ':' || secondword == ':') {

        Handle[HandleNumber].Device = -1;
        for (i = 0; i < maxdevices; i++) {
            if (Firstchar == DriveLetter[i] || Firstword == DriveLetter[i]) {
                if (MediaTable[i].DevicePresent) {
                    Handle[HandleNumber].Device = i;
                    break;
                }
            }
            Firstchar = Changecase(Firstchar);
            Firstword = Changecase(Firstword);

            if (Firstchar == DriveLetter[i] || Firstword == DriveLetter[i]) {
                if (MediaTable[i].DevicePresent) {
                    Handle[HandleNumber].Device = i;
                    break;
                }
            }
        }                       // for (maxdevices)
        if (Handle[HandleNumber].Device < 0)
            return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;

        Handle[HandleNumber].Mode = (FileSystemModeTypes_t) (DIRECTORY_MODE + READ_MODE + WRITE_MODE);  // set mode to directory to read the directory 
        if ((ChangeToRootdirectory(HandleNumber)) < 0)
            return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
        if (stringtype == kDBCSEncoding) {
            if ((ExtractPath(filepath, index)) == END_OF_DIR_PATH)
                return END_OF_DIR_PATH;
        } else if (stringtype == kUTF16Encoding) {
            if ((ExtractPathW(filepath, index)) == END_OF_DIR_PATH)
                return END_OF_DIR_PATH;
        }

    }

    else if (Firstchar == '/' || Firstword == '/') {
        Handle[HandleNumber].Device = Handle[0].Device;
        Handle[HandleNumber].Mode = (FileSystemModeTypes_t) (DIRECTORY_MODE + READ_MODE + WRITE_MODE);  // set mode to directory to read the directory 
        if ((ChangeToRootdirectory(HandleNumber)) < 0)
            return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
        if (stringtype == kDBCSEncoding) {
            if ((ExtractPath(filepath, index)) == END_OF_DIR_PATH)
                return END_OF_DIR_PATH;
        } else if (stringtype == kUTF16Encoding) {
            if ((ExtractPathW(filepath, index)) == END_OF_DIR_PATH)
                return END_OF_DIR_PATH;
        }

    }

    else {
        Handle[HandleNumber] = Handle[CWD_HANDLE];
        Handle[CWD_HANDLE].Mode = (FileSystemModeTypes_t) (DIRECTORY_MODE + READ_MODE + WRITE_MODE);    // set mode to directory to read the directory 

        if (Firstchar == 0x2E || Firstword == 0x2E) {
            if (secondchar == 0x2E || secondword == 0x2E) {
                if (Handle[HandleNumber].StartingCluster ==
                    MediaTable[Handle[HandleNumber].Device].RootdirCluster)
                    return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
                NumBytesRead = ReadDirectoryRecord(HandleNumber, 1, buf);
                clusterlo = FSGetWord(buf, DIR_FSTCLUSLOOFFSET);
                clusterno = FSGetWord(buf, DIR_FSTCLUSHIOFFSET);
                clusterno = (int32_t) clusterlo + (clusterno << 16);
                if (clusterno == 0)
                    clusterno = MediaTable[Handle[HandleNumber].Device].RootdirCluster;
                UpdateHandle(HandleNumber, clusterno);
            }
            if (stringtype == kDBCSEncoding) {
                if ((ExtractPath(filepath, index)) == END_OF_DIR_PATH)
                    return END_OF_DIR_PATH;
            } else if (stringtype == kUTF16Encoding) {
                if ((ExtractPathW(filepath, index)) == END_OF_DIR_PATH)
                    return END_OF_DIR_PATH;
            }
        }
    }

    (void)NumBytesRead;
    return (SUCCESS);

}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t Mkdir(uint8_t *filepath)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to file name
				   
   Outputs:       SUCCESS or an error code if error occurs      
   
   Description:   Searches for given directory path, if path is found then creates
                  given directory in the directoy path.
----------------------------------------------------------------------------*/
RtStatus_t Mkdir(uint8_t * filepath)
{
    int32_t HandleNumber, strlen1;
    RtStatus_t Retvalue;
    int32_t index = 0, currentposition = 0;
    int32_t clusterno;
    int32_t byte, source_offset = 0;
    int32_t length;

    /* Take temporary(directory) handle for searching the directory by changing path */
    HandleNumber = DIRECTORY_HANDLE;

    /* If the temporary handle is already active then change path is not possible */
    if (Handleactive(HandleNumber) == SUCCESS)
        return ERROR_OS_FILESYSTEM_CHANGEPATH_NOT_POSSIBLE;
    Handle[HandleNumber].HandleActive = 1;

    /* first search for the given directory */
    if (SetHandleforsearch(HandleNumber, filepath, kDBCSEncoding, &index) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
    }
    length = Strlength(filepath);
    if (length == 0)
        return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
    /*if at the end of dirname Directory separator(/)is found then discard it. */
    source_offset = length - 1;
    byte = GetChar((uint8_t *) filepath, &source_offset);
    if (byte == 0x2f) {
        source_offset = length - 1;
        PutChar((uint8_t *) filepath, &source_offset, 0);
    }
    strlen1 = Strlength(filepath);
    currentposition = Extractfilename(filepath, strlen1, &index);

    /* Change the path to the specified path given */
    if (currentposition != index) {
        if ((clusterno =
             Changepath(HandleNumber, filepath, kDBCSEncoding, currentposition, index)) < 0) {
            Freehandle(HandleNumber);
            return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
        }
        UpdateHandle(HandleNumber, clusterno);
    }
    /* remove this, not required, due to compiler problem */
    index = 0;
    /* create given directory in the directory referenced by the handle */
    // Modified by SGTL_HK 
    //if((Retvalue = CreateDirectory(HandleNumber,filepath,strlen1,currentposition))< 0)
    if ((Retvalue =
         CreateDirectory(HandleNumber, filepath, strlen1, currentposition, kDBCSEncoding)) < 0) {
        Freehandle(HandleNumber);
        return Retvalue;
    }
    /* Free the handle used for search */
    Freehandle(HandleNumber);
    return (SUCCESS);
}

/*----------------------------------------------------------------------------

>  Function Name:  RtStatus_t Mkdirw(uint8_t *filepath)

   FunctionType:   Reentrant

   Inputs:        1) Pointer to file name (uint8_t)
				   
   Outputs:       FS_SUCCESS OR error code if error occurs      
   
   Description:   Searches for given directory path, if path is found then creates
                  given directory in the directoy path.
----------------------------------------------------------------------------*/
RtStatus_t Mkdirw(uint8_t * filepath)
{
    int32_t HandleNumber;
    RtStatus_t Retvalue;
    int32_t index = 0, currentposition = 0;
    int32_t clusterno;
    int32_t byte, source_offset = 0;
    int32_t length;

    /* Take temporary(directory)handle for searching the directory by changing path */
    HandleNumber = DIRECTORY_HANDLE;

    /* if the temporary handle is already active then change path is not possible */
    if (Handleactive(HandleNumber) == SUCCESS)
        return ERROR_OS_FILESYSTEM_CHANGEPATH_NOT_POSSIBLE;
    Handle[HandleNumber].HandleActive = 1;

    /* first search for the given directory */
    if (SetHandleforsearch(HandleNumber, filepath, kUTF16Encoding, &index) < 0)
        //if(SetHandleforsearch(HandleNumber,filepath,kDBCSEncoding,&index)<0)
    {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
    }

    length = StrlengthW((uint8_t *) filepath);
    if (length == 0)
        return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
    //length=Strlength(filepath);

    /*if at the end of dirname Directory separator(/)is found then discard it. */
    source_offset = length - 1;
    source_offset += source_offset;
    byte = filepath[source_offset];
    if (byte == 0x002f) {
        //source_offset=length-1;

        filepath[source_offset] = 0;
    }

    currentposition = Extractfilenamew((uint8_t *) filepath, &index);
    //currentposition=Extractfilename(filepath,strlen1,&index);

    /* Change the path to the specified path given */
    if (currentposition != index) {
        if ((clusterno =
             Changepath(HandleNumber, (uint8_t *) filepath, kUTF16Encoding, currentposition,
                        index)) < 0)
            //if((clusterno =  Changepath(HandleNumber,filepath,kDBCSEncoding,currentposition,index)) <0)
        {
            Freehandle(HandleNumber);
            return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
        }
        UpdateHandle(HandleNumber, clusterno);
    }

    /* remove this not required, due to compiler pbm */
    index = 0;
    /* create given directory in the directoy refernce by the handle */

    if ((Retvalue =
         CreateDirectory(HandleNumber, (uint8_t *) filepath, length * 2, currentposition,
                         kUTF16Encoding)) < 0)
        //if((Retvalue = CreateDirectory(HandleNumber,filepath,strlen1,currentposition))< 0)
    {
        Freehandle(HandleNumber);
        return Retvalue;
    }

    /* Free the handle used for search */
    Freehandle(HandleNumber);

    return (SUCCESS);
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t Rmdir(uint8_t *filepath)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to file name
				   
   Outputs:       SUCCESS or an error code if error occurs      
   
   Description:   Searches for the given directory and if it is found empty 
                  then delete the directory.
----------------------------------------------------------------------------*/
RtStatus_t Rmdir(uint8_t * filepath)
{
    int32_t HandleNumber, RecordNo, index = 0;
    RtStatus_t Retval;
    int32_t dirsector, diroffset, dirStartcluster, Byteposinsec, SecPos;
    int32_t clusterno, Currentsector, Curoffset;
    int32_t Dir_Attr, Strlen;
    uint8_t buf[32];

    /* Take temporary(directory) handle for searching the directory by changing path */
    HandleNumber = DIRECTORY_HANDLE;

    /* If the temporary handle is already active then change path is not possible */
    if (Handleactive(HandleNumber) == SUCCESS)
        return ERROR_OS_FILESYSTEM_CHANGEPATH_NOT_POSSIBLE;

    Handle[HandleNumber].HandleActive = 1;

    /* first set the handle for search */
    if ((Retval = SetHandleforsearch(HandleNumber, filepath, kDBCSEncoding, &index)) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
    }

    Strlen = Strlength(filepath);
    /* If directory is root directory or parent directory then it can not be 
       removed. Return Error */
    if ((Retval == END_OF_DIR_PATH) || (Strlen == index)) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_DIR_NOT_REMOVABLE;
    }

    /* Change the path to the specified path given */
    if ((clusterno = Changepath(HandleNumber, filepath, kDBCSEncoding, Strlen, index)) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_FILE_NOT_FOUND;
    }

    if (MediaTable[Handle[HandleNumber].Device].FATType == FAT32 && clusterno == 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_DIR_NOT_REMOVABLE;
    }

    RecordNo = Handle[HandleNumber].CurrentOffset >> 5;

    /* check the attribute if it is not a directory then return error */
    if (ReadDirectoryRecord(HandleNumber, RecordNo, buf) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_INVALID_RECORD_NUMBER;
    }

    Dir_Attr = FSGetByte(buf, DIR_ATTRIBUTEOFFSET);
    if (!(Dir_Attr & DIRECTORY)) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_FILE_DELETE_FAILED;
    }

    /* set the handle to original position */
    if (Handle[HandleNumber].StartingCluster != 0) {
        if ((Retval = Fseek(HandleNumber, -DIRRECORDSIZE, SEEK_CUR)) < 0)
            return Retval;
    }

    /* store the handle for deleting records */
    dirsector = Handle[HandleNumber].DirSector;
    diroffset = Handle[HandleNumber].diroffset;
    dirStartcluster = Handle[HandleNumber].StartingCluster;
    Currentsector = Handle[HandleNumber].CurrentSector;
    Byteposinsec = Handle[HandleNumber].BytePosInSector;
    Curoffset = Handle[HandleNumber].CurrentOffset;
    SecPos = Handle[HandleNumber].SectorPosInCluster;

    /* update the handle to associate with the directory to be deleted */
    UpdateHandle(HandleNumber, clusterno);
    /* check whether the directory is empty or not. If it is not empty, return error */
    if (Isdirectoryempty(HandleNumber) == ERROR_OS_FILESYSTEM_DIR_NOT_EMPTY) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_DIR_NOT_EMPTY;
    }
    /* check whether the directory is not current working directory. If it is, return error */
    if (IsCurrWorkDir(HandleNumber) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_CANNOT_DELETE_CWD;
    }
    /* Go one directory level up (directory to delete) */
    Handle[HandleNumber].DirSector = dirsector;
    Handle[HandleNumber].diroffset = diroffset;
    Handle[HandleNumber].StartingCluster = dirStartcluster;
    Handle[HandleNumber].CurrentSector = Currentsector;
    Handle[HandleNumber].CurrentCluster = dirStartcluster;
    Handle[HandleNumber].BytePosInSector = Byteposinsec;
    Handle[HandleNumber].SectorPosInCluster = SecPos;
    Handle[HandleNumber].CurrentOffset = Curoffset;

    /* Delete the directory record */
    if ((Retval = DeleteRecord(HandleNumber, RecordNo)) < 0) {
        Freehandle(HandleNumber);
        return Retval;
    }
    /* update the handle to associate with the directory to be deleted */
    UpdateHandle(HandleNumber, clusterno);
    /* Delete the contents of the directory (i.e. Mark all the clusters occupied by 
       the directory as zero in FAT Table). */
    if ((Retval = DeleteContent(HandleNumber, 0)) < 0) {
        Freehandle(HandleNumber);
        return Retval;
    }

    /* Free the handle used for file search */
    Freehandle(HandleNumber);
    return (SUCCESS);
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t Rmdirw(uint8_t *filepath)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to file name
				   
   Outputs:       SUCCESS or an error code if error occurs      
   
   Description:   Searches for the given directory and if it is found empty then
                  delete the directory. It considers the string as UTF16.
----------------------------------------------------------------------------*/
RtStatus_t Rmdirw(uint8_t * filepath)
{
    int32_t HandleNumber, RecordNo, index = 0;
    RtStatus_t Retval;
    int32_t dirsector, diroffset, dirStartcluster, Currentsector, Byteposinsec, Curoffset, SecPos;
    int32_t clusterno;
    int32_t Dir_Attr, Strlen;
    uint8_t buf[32];

    /* Take temporary(directory) handle for searching the directory by changing path */
    HandleNumber = DIRECTORY_HANDLE;

    /* If the temporary handle is already active then change path is not possible */
    if (Handleactive(HandleNumber) == SUCCESS)
        return ERROR_OS_FILESYSTEM_CHANGEPATH_NOT_POSSIBLE;
    Handle[HandleNumber].HandleActive = 1;
    /* first set the handle for search */
    if ((Retval = SetHandleforsearch(HandleNumber, filepath, kUTF16Encoding, &index)) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
    }
    Strlen = StrlengthW(filepath);
    /* If directoy is root directory or parent directory then it can not be 
       removed. Return Error  */
    if ((Retval == END_OF_DIR_PATH) || (Strlen == index)) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_DIR_NOT_REMOVABLE;
    }

    /* Change the path to the specified path given */
    if ((clusterno = Changepath(HandleNumber, filepath, kUTF16Encoding, Strlen, index)) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_FILE_NOT_FOUND;
    }
    RecordNo = Handle[HandleNumber].CurrentOffset >> 5;
    /* check the attribute if it is not a directory, return error */
    if (ReadDirectoryRecord(HandleNumber, RecordNo, buf) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_INVALID_RECORD_NUMBER;
    }

    Dir_Attr = FSGetByte(buf, 32);
    if (!(Dir_Attr & DIRECTORY)) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_FILE_DELETE_FAILED;
    }

    /* set the handle to original position */
    if (Handle[HandleNumber].StartingCluster != 0) {
        if ((Retval = Fseek(HandleNumber, -DIRRECORDSIZE, SEEK_CUR)) < 0)
            return Retval;
    }

    /* store the handle for deleting records */
    dirsector = Handle[HandleNumber].DirSector;
    diroffset = Handle[HandleNumber].diroffset;
    dirStartcluster = Handle[HandleNumber].StartingCluster;
    Currentsector = Handle[HandleNumber].CurrentSector;
    Byteposinsec = Handle[HandleNumber].BytePosInSector;
    Curoffset = Handle[HandleNumber].CurrentOffset;
    SecPos = Handle[HandleNumber].SectorPosInCluster;

    /* update the handle to associate with the directory to be deleted */
    UpdateHandle(HandleNumber, clusterno);
    /* check whether the directory is empty or not. If it is not empty, return error */
    if (Isdirectoryempty(HandleNumber) == ERROR_OS_FILESYSTEM_DIR_NOT_EMPTY) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_DIR_NOT_EMPTY;
    }

    /* check whether the directory is not current working directory. If it is, return error */
    if (IsCurrWorkDir(HandleNumber) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_CANNOT_DELETE_CWD;
    }
    /* Go one directory level up (directory to delete) */
    Handle[HandleNumber].DirSector = dirsector;
    Handle[HandleNumber].diroffset = diroffset;
    Handle[HandleNumber].StartingCluster = dirStartcluster;
    Handle[HandleNumber].CurrentSector = Currentsector;
    Handle[HandleNumber].CurrentCluster = dirStartcluster;
    Handle[HandleNumber].BytePosInSector = Byteposinsec;
    Handle[HandleNumber].SectorPosInCluster = SecPos;
    Handle[HandleNumber].CurrentOffset = Curoffset;
    /* Delete the directory record */
    if ((Retval = DeleteRecord(HandleNumber, RecordNo)) < 0) {
        Freehandle(HandleNumber);
        return Retval;
    }
    /* update the handle to associate with the directory to be deleted */
    UpdateHandle(HandleNumber, clusterno);
    /* Delete the contents of the directory (i.e. Mark all the clusters occupied by 
       the directory as zero in FAT Table). */
    if ((Retval = DeleteContent(HandleNumber, 0)) < 0) {
        Freehandle(HandleNumber);
        return Retval;
    }
    /* Free the handle used for file search */
    Freehandle(HandleNumber);
    return (SUCCESS);
}

/*----------------------------------------------------------------------------

>  Function Name: RtStatus_t CreateDirectory(int32_t HandleNumber,uint8_t *Filepath,int32_t length,int32_t index,int32_t stringtype)

   FunctionType:  Reentrant

   Inputs:        1)HandleNumber
                  2)Pointer to File Name
                  3)length(end of string from file path)
                  4)index(points to start of the string from file path)  
		          5)stringtype(kUTF16Encoding or kDBCSEncoding)    
   Outputs:       Return HandleNumber if Success, or ERROR CODE if  Error Occurs

   Description:   Creates a new Directory  in a given directory

<
----------------------------------------------------------------------------*/
RtStatus_t CreateDirectory(int32_t HandleNumber, uint8_t * Filepath, int32_t length, int32_t index,
                           int32_t stringtype)
{
    uint8_t Buffer[33];
    uint8_t ShortName[12];
    int32_t ClusterNumber, NewClusterNum;
    int32_t Device = Handle[HandleNumber].Device;
    int32_t TempHandleActive = 0;
    int32_t TempDevice = 0;
    FileSystemModeTypes_t TempMode = NOT_WRITE_MODE;
    int32_t TempStartingCluster = 0;
    int32_t TempCurrentOffset = 0;
    int32_t TempCurrentCluster = 0;
    int32_t TempCurrentSector = 0;
    int32_t TempBytePosInSector = 0;
    int32_t TempSectorPosInCluster = 0;
    int32_t TempDirSector = 0;
    int32_t TempDirOffset = 0;
    int32_t RetValue;
    uint32_t TempFileSize = 0;
    int32_t k, Count, i, j;
    uint8_t Byte;
    int32_t Word;
    int32_t RecordNum = 0;

#ifdef FS_USE_MALLOC
    uint8_t *UnicodeBuffer;
    UnicodeBuffer = malloc(MAX_UNICODE_SIZE * sizeof(uint8_t));
    if (NULL == UnicodeBuffer) {
        return ERROR_OS_FILESYSTEM_MEMORY;
    }
#else
    uint8_t UnicodeBuffer[MAX_UNICODE_SIZE];
#endif

    EnterNonReentrantSection();
    for (k = 0; k < sizeof(ShortName); k++)
        ShortName[k] = 0x20;

    memset(Buffer, 0, sizeof(Buffer));

    //This HandleNumber will be Current dir HandleNumber=0
    if ((Handle[HandleNumber].Mode & READ_MODE) != READ_MODE) {
        LeaveNonReentrantSection();
#ifdef FS_USE_MALLOC
        free(UnicodeBuffer);
#endif
        return ERROR_OS_FILESYSTEM_DIRECTORY_IS_NOT_WRITABLE;
    }
    //Check if Directory is already present
    if (stringtype == kUTF16Encoding)   //check for kUTF16Encoding or kDBCSEncoding
    {
        if ((RetValue =
             Searchdirectory(HandleNumber, Filepath, kUTF16Encoding, 0, length, index,
                             (uint8_t *) UnicodeBuffer, 1, &RecordNum /*, TRUE */ )) >= 0) {
            LeaveNonReentrantSection();
#ifdef FS_USE_MALLOC
            free(UnicodeBuffer);
#endif
            return ERROR_OS_FILESYSTEM_DUPLICATE_FILE_NAME;
        }
    } else {
        if ((RetValue =
             Searchdirectory(HandleNumber, Filepath, kDBCSEncoding, 0, (length + 1), index,
                             (uint8_t *) UnicodeBuffer, 1, &RecordNum /*, FALSE */ )) >= 0) {
            LeaveNonReentrantSection();
#ifdef FS_USE_MALLOC
            free(UnicodeBuffer);
#endif
            return ERROR_OS_FILESYSTEM_DUPLICATE_FILE_NAME;
        }
    }
    if (stringtype == kDBCSEncoding) {  //check for kUTF16Encoding or kDBCSEncoding
        Count = Strlength(Filepath);

        for (i = 0; i <= Count; i++) {
            Byte = FSGetByte(Filepath, i);
            if (Byte == 0x2e) {
                //This is to check number of .or...(dots) are there in file path return with error
                //because it is invalid to create dir with only .or ..
                while (1) {
                    Byte = FSGetByte(Filepath, i);
                    i++;
                    if (Byte != 0x2e)
                        break;
                }
                if (Byte == '\0') {
                    LeaveNonReentrantSection();
#ifdef FS_USE_MALLOC
                    free(UnicodeBuffer);
#endif
                    return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
                }
            }
        }
    } else {

        Count = StrlengthW(Filepath);
        j = 0;
        for (i = 0; i <= Count * 2; i += 2) {
            Word = GetCharW(Filepath, &j);
            if (Word == 0x2e) {
                //This is to check number of .or...(dots) are there in file path return with error
                //because it is invalid to create dir with  only .or ..
                while (1) {
                    Word = GetCharW(Filepath, &j);
                    if (Word != 0x2e)
                        break;
                }
                if (Word == '\0') {
                    LeaveNonReentrantSection();
#ifdef FS_USE_MALLOC
                    free(UnicodeBuffer);
#endif
                    return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
                }
            }
        }
    }

    if ((ClusterNumber = FirstfreeAndallocate(Device)) <= 0) {
        LeaveNonReentrantSection();
#ifdef FS_USE_MALLOC
        free(UnicodeBuffer);
#endif
        return ClusterNumber;
    }
    //Copy the handle    
    TempHandleActive = Handle[HandleNumber].HandleActive;
    TempDevice = Handle[HandleNumber].Device;
    TempMode = (FileSystemModeTypes_t) Handle[HandleNumber].Mode;
    TempStartingCluster = Handle[HandleNumber].StartingCluster;
    TempCurrentOffset = Handle[HandleNumber].CurrentOffset;
    TempCurrentCluster = Handle[HandleNumber].CurrentCluster;
    TempCurrentSector = Handle[HandleNumber].CurrentSector;
    TempBytePosInSector = Handle[HandleNumber].BytePosInSector;
    TempSectorPosInCluster = Handle[HandleNumber].SectorPosInCluster;
    TempDirSector = Handle[HandleNumber].DirSector;
    TempDirOffset = Handle[HandleNumber].diroffset;
    TempFileSize = Handle[HandleNumber].FileSize;

    if (stringtype == kUTF16Encoding)   //check for kUTF16Encoding or kDBCSEncoding
    {
        if ((RetValue =
             (int32_t) CreateDirRecord(Filepath, HandleNumber, ClusterNumber, DIRECTORY + ARCHIVE,
                                       kUTF16Encoding, length, index, (uint8_t *) UnicodeBuffer,
                                       0)) < 0) {
            LeaveNonReentrantSection();
#ifdef FS_USE_MALLOC
            free(UnicodeBuffer);
#endif
            return RetValue;
        }
    } else {
        if ((RetValue =
             (int32_t) CreateDirRecord(Filepath, HandleNumber, ClusterNumber, DIRECTORY + ARCHIVE,
                                       kDBCSEncoding, length, index, UnicodeBuffer, 0)) < 0) {
            LeaveNonReentrantSection();
#ifdef FS_USE_MALLOC
            free(UnicodeBuffer);
#endif
            return RetValue;
        }
    }
    NewClusterNum = Handle[HandleNumber].StartingCluster;

    //This will update the handle to the created directory
    UpdateHandle(HandleNumber, ClusterNumber);

    if ((RetValue = (int32_t) ClearCluster(HandleNumber)) < 0) {
        LeaveNonReentrantSection();
#ifdef FS_USE_MALLOC
        free(UnicodeBuffer);
#endif
        return RetValue;
    }

    Handle[HandleNumber].Mode = (FileSystemModeTypes_t) (DIRECTORY_MODE + READ_MODE + WRITE_MODE);

    if (Handle[HandleNumber].StartingCluster != 0) {
        PutByte(ShortName, 0x2e, 0);

        if ((RetValue =
             (int32_t) CreateShortDirRecord(ShortName, HandleNumber, ClusterNumber,
                                            DIRECTORY + ARCHIVE, 0)) < 0) {
            LeaveNonReentrantSection();
#ifdef FS_USE_MALLOC
            free(UnicodeBuffer);
#endif
            return RetValue;
        }
        Handle[HandleNumber].Mode =
            (FileSystemModeTypes_t) (DIRECTORY_MODE + READ_MODE + WRITE_MODE);
        PutByte(ShortName, 0x2e, 1);

//        if(MediaTable[Handle[HandleNumber].Device].FATType==FAT32 && Handle[HandleNumber].StartingCluster==2)
        if (MediaTable[Handle[HandleNumber].Device].FATType == FAT32 && NewClusterNum == 2)
            NewClusterNum = 0;  //For FAT32 also starting cluster of .. entry should be zero

        if ((RetValue =
             (int32_t) CreateShortDirRecord(ShortName, HandleNumber, NewClusterNum,
                                            DIRECTORY + ARCHIVE, 0)) < 0) {
            LeaveNonReentrantSection();
#ifdef FS_USE_MALLOC
            free(UnicodeBuffer);
#endif
            return RetValue;
        }
    }
    //Restore the handle
    Handle[HandleNumber].HandleActive = TempHandleActive;
    Handle[HandleNumber].Device = TempDevice;
    Handle[HandleNumber].Mode = TempMode;
    Handle[HandleNumber].StartingCluster = TempStartingCluster;
    Handle[HandleNumber].CurrentOffset = TempCurrentOffset;
    Handle[HandleNumber].CurrentCluster = TempCurrentCluster;
    Handle[HandleNumber].CurrentSector = TempCurrentSector;
    Handle[HandleNumber].BytePosInSector = TempBytePosInSector;
    Handle[HandleNumber].SectorPosInCluster = TempSectorPosInCluster;
    Handle[HandleNumber].DirSector = TempDirSector;
    Handle[HandleNumber].diroffset = TempDirOffset;
    Handle[HandleNumber].FileSize = TempFileSize;
    LeaveNonReentrantSection();

#ifdef FS_USE_MALLOC
    free(UnicodeBuffer);
#endif
    return (int32_t) SUCCESS;
}

/*----------------------------------------------------------------------------

>  Function Name:  int32_t SetCWDHandle (int32_t DeviceNo)

   FunctionType:  

   Inputs:         Device number to set the cwd handle to root dir of

   Outputs:        Returns 0 for SUCCESS

   Description:     
<
--------- -------------------------------------------------------------------*/
int32_t SetCWDHandle(int32_t DeviceNo)
{

    /* set handle CWD_HANDLE (Handle 0) to Root directory of device 0 */
    Handle[CWD_HANDLE].HandleActive = 1;
    Handle[CWD_HANDLE].Device = DeviceNo;
    Handle[CWD_HANDLE].Mode = DIRECTORY_MODE + READ_MODE + WRITE_MODE;
    ChangeToRootdirectory(CWD_HANDLE);
#ifdef CWD_STRING
    /* set gCurrentWorkingdirectory string to device 0 */

    // Terminate with 3 nulls so code that treats cwd as either ASCII or UTF-16 will see the same end-of-string.

    PutByte(gCurrentWorkingdirectory, DriveLetter[0], 0);
    PutByte(gCurrentWorkingdirectory, ':', 1);
    PutByte(gCurrentWorkingdirectory, '\0', 2);
    PutByte(gCurrentWorkingdirectory, '\0', 3);
    PutByte(gCurrentWorkingdirectory, '\0', 4);

#endif
    return SUCCESS;
}
