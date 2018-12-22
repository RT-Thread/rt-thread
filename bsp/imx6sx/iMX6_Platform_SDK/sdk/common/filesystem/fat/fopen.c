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
 $Archive: /Fatfs/FileSystem/Fat32/higherapi/Fopen.c $                                        
 $Revision: 18 $                                       
 $Date: 9/18/03 11:50a $                                           
 Description: Fopen.c
 Notes:	This file read provides higherlevel API function to open a file
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
#include "media_cache.h"

int totalFileOpened = 0;

/*----------------------------------------------------------------------------
>  Function Name: int32_t Fopen(uint8_t *filepath,uint8_t *mode)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to file name
                  2) Mode 
				   
   Outputs:       HandleNumber of free handle populated by the given filename 
                  or error if function fails      
   
   Description:   Opens the specified file in specified mode. It considers
                  the string as DBCS.
----------------------------------------------------------------------------*/
int32_t Fopen(uint8_t * filepath, uint8_t * mode)
{
    int32_t HandleNumber, RecordNo, strlen = 0, currentposition = 0, index = 0;
    FileSystemModeTypes_t Mode;
    RtStatus_t Retval;
    int32_t clusterno;
    uint8_t buf[32];

    int32_t clusterlo, clusterhi;

    /* set the Mode according to the mode given */
    if ((mode[0]) == 'r') {
        if ((mode[1]) == '+')
            Mode = RPLUS;
        else
            Mode = READ_MODE;
    } else if ((mode[0]) == 'w') {
        if ((mode[1]) == '+')
            Mode = WPLUS;
        else
            Mode = WRITE_MODE;
    } else if ((mode[0]) == 'a') {
        if ((mode[1]) == '+')
            Mode = APLUS;
        else
            Mode = APPEND_MODE;
    } else
        return ERROR_OS_FILESYSTEM_MODE_NOT_SUPPORTED;

    /* Search for free handle and allocate it */
    if ((HandleNumber = Searchfreehandleallocate()) < 0)
        return (ERROR_OS_FILESYSTEM_NO_FREE_HANDLE);

    /* set the handle for search */
    if (SetHandleforsearch(HandleNumber, filepath, kDBCSEncoding, &index) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
    }
    /* search for the specified file */
    strlen = Strlength(filepath);
    currentposition = Extractfilename(filepath, strlen, &index);

    /* Go to the specified directory level by changing the path */
    if (currentposition != index) {
        if ((clusterno =
             Changepath(HandleNumber, filepath, kDBCSEncoding, currentposition, index)) < 0) {
            Freehandle(HandleNumber);
            return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
        }
        UpdateHandle(HandleNumber, clusterno);
    }

    /* search for the specified file */
    index = 0;
    if ((clusterno =
         Changepath(HandleNumber, filepath, kDBCSEncoding, strlen, currentposition)) < 0) {
        /* File was not found */

        /* If the file was to be opened for reading, then the caller must be NACKed. */
        if (Mode == READ_MODE || Mode == RPLUS) {
            Freehandle(HandleNumber);
            return (ERROR_OS_FILESYSTEM_FILE_NOT_FOUND);
        }
        /* If the file is to be opened in w, w+(write), a or a+(append) mode and 
           if the file is not found then create a new file of the name 
           specified in the specified directory */
        if ((Retval = Fcreate(HandleNumber, filepath, kDBCSEncoding, strlen, currentposition)) < 0) {
            Freehandle(HandleNumber);
            return Retval;
        }
    }

    /* If file is found and is to be opened for w, w+(write), a or a+(append)
       mode then check the file attribute. If it is READ_ONLY then  return error
       ERROR_OS_FILESYSTEM_FILE_WRITE_FAILED */
    else {
        /* The file was found */

        RecordNo = Handle[HandleNumber].CurrentOffset >> 5;
        if ((ReadDirectoryRecord(HandleNumber, RecordNo, buf)) < 0)
            return ERROR_OS_FILESYSTEM_INVALID_RECORD_NUMBER;

        Handle[HandleNumber].FileSize = FSGetDWord((uint8_t *) buf, DIR_FILESIZEOFFSET);
        if (FSGetByte(buf, DIR_ATTRIBUTEOFFSET) & DIRECTORY_MODE) {
            Freehandle(HandleNumber);
            return (ERROR_OS_FILESYSTEM_CANNOT_OPEN_DIRECTORY);
        }

        if (Mode != READ_MODE) {
            /* The file was to be opened for something more than reading. */

            if (FSGetByte(buf, DIR_ATTRIBUTEOFFSET) & READ_ONLY) {
                Freehandle(HandleNumber);
                return (ERROR_OS_FILESYSTEM_FILE_WRITE_FAILED);
            }

            if (Handle[HandleNumber].StartingCluster != 0)
                Fseek(HandleNumber, -DIRRECORDSIZE, SEEK_CUR);

            UpdateHandle(HandleNumber, clusterno);
            Updatehandlemode(HandleNumber, READ_MODE + WRITE_MODE);

            /* If file is found and is to be opened for w, w+(write), a or a+(append)
               mode then check if the file is already opened for write mode. If file is
               already opened for write mode then return error 'File can not be opened in write mode'. */

            if (IsHandleWriteAllocated(HandleNumber) == WRITE_MODE) {
                Freehandle(HandleNumber);
                return (ERROR_OS_FILESYSTEM_FILE_WRITE_FAILED);
            }

            /* If file is to be opened in write mode (i.e. W or WPLUS) then 
               delete the contents of the file. */

            if (Mode == WRITE_MODE || Mode == WPLUS) {
                if (Handle[HandleNumber].StartingCluster != 0) {
                    //if((Retval = DeleteContent(HandleNumber,1)) <0)
                    if ((Retval = DeleteContent(HandleNumber, 0)) < 0) {
                        Freehandle(HandleNumber);
                        return Retval;
                    }
                    if ((Retval = UpdateFileSize(HandleNumber, 1)) < 0) {
                        Freehandle(HandleNumber);
                        return Retval;
                    }
                    Handle[HandleNumber].StartingCluster = 0;
                    Handle[HandleNumber].CurrentCluster = 0;
                    Handle[HandleNumber].CurrentSector = 0;
                    clusterlo = 0;
                    clusterhi = 0;

                    if ((Retval =
                         FSWriteSector(Handle[HandleNumber].Device, Handle[HandleNumber].DirSector,
                                       (Handle[HandleNumber].diroffset + DIR_FSTCLUSLOOFFSET),
                                       (uint8_t *) & clusterlo, 0, 2, WRITE_TYPE_RANDOM)) < 0)
                        return Retval;

                    if ((Retval =
                         FSWriteSector(Handle[HandleNumber].Device, Handle[HandleNumber].DirSector,
                                       (Handle[HandleNumber].diroffset + DIR_FSTCLUSHIOFFSET),
                                       (uint8_t *) & clusterhi, 0, 2, WRITE_TYPE_RANDOM)) < 0)
                        return Retval;

                }
            }
            /* If file is to be opened in append mode then set the current offset
               in the handle table to the end of file. */
            if (Mode == APPEND_MODE || Mode == APLUS) {
                if ((Retval = Fseek(HandleNumber, 0, SEEK_END)) < 0) {
                    Freehandle(HandleNumber);
                    return Retval;
                }
            }
        } else {
            if (Handle[HandleNumber].StartingCluster != 0)
                Fseek(HandleNumber, -DIRRECORDSIZE, SEEK_CUR);

            UpdateHandle(HandleNumber, clusterno);
        }
    }
    /*  Update the mode of handle table according to the given mode */
    if (Mode == RPLUS || Mode == WPLUS)
        Mode = (FileSystemModeTypes_t) (READ_MODE + WRITE_MODE);
    else if (Mode == APPEND_MODE)
        Mode = (FileSystemModeTypes_t) (WRITE_MODE + APPEND_MODE);
    else if (Mode == APLUS)
        Mode = (FileSystemModeTypes_t) (READ_MODE + WRITE_MODE + APPEND_MODE);

    Updatehandlemode(HandleNumber, Mode);

    /*get file cache for this handle */
    totalFileOpened++;
    getFatCache(-1);

    return (HandleNumber);
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t Fopenw(uint8_t *filepath,uint8_t *mode)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to file name
                  2) Open mode 
				   
   Outputs:       HandleNumber of free handle populated by the given filename 
                  or error if function fails      
   
   Description:   Opens the specified file in specified mode. It considers
                  the string as UTF16.
<
----------------------------------------------------------------------------*/
int32_t Fopenw(uint8_t * filepath, uint8_t * mode)
{
    int32_t HandleNumber, RecordNo, strlen, index = 0, currentposition = 0;
    FileSystemModeTypes_t Mode;
    RtStatus_t Retval;
    uint8_t buf[32];
    int32_t clusterno;

    int32_t clusterlo, clusterhi;

    /* set the Mode according to the mode given */
    if ((mode[0]) == 'r') {
        if ((mode[1]) == '+')
            Mode = RPLUS;
        else
            Mode = READ_MODE;
    } else if ((mode[0]) == 'w') {
        if ((mode[1]) == '+')
            Mode = WPLUS;
        else
            Mode = WRITE_MODE;
    } else if ((mode[0]) == 'a') {
        if ((mode[1]) == '+')
            Mode = APLUS;
        else
            Mode = APPEND_MODE;
    } else
        return ERROR_OS_FILESYSTEM_MODE_NOT_SUPPORTED;

    /* Search for free handle and allocate it */
    if ((HandleNumber = Searchfreehandleallocate()) < 0)
        return (ERROR_OS_FILESYSTEM_NO_FREE_HANDLE);

    /* set the handle for search */
    if (SetHandleforsearch(HandleNumber, (uint8_t *) filepath, kUTF16Encoding, &index) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
    }
    strlen = StrlengthW((uint8_t *) filepath);
    currentposition = Extractfilenamew((uint8_t *) filepath, &index);

    /* Go to the specified directory level by changing the path */
    if (currentposition != index) {
        if ((clusterno =
             Changepath(HandleNumber, (uint8_t *) filepath, kUTF16Encoding, currentposition,
                        index)) < 0) {
            Freehandle(HandleNumber);
            return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
        }
        UpdateHandle(HandleNumber, clusterno);
    }

    /* search for the specified file */
    if (currentposition == 0)
        currentposition = index;

    //modify: double the string length for unicode
    if ((clusterno =
         Changepath(HandleNumber, (uint8_t *) filepath, kUTF16Encoding, strlen * 2,
                    currentposition)) < 0) {
        if (Mode == READ_MODE || Mode == RPLUS) {
            Freehandle(HandleNumber);
            return (ERROR_OS_FILESYSTEM_FILE_NOT_FOUND);
        }
        /* If file is to be opened in w, w+(write), a or a+(append) mode and 
           if the file is not found then create a new file of the name 
           specified in the specified directory */

        if ((Retval =
             Fcreate(HandleNumber, (uint8_t *) filepath, kUTF16Encoding, strlen * 2,
                     currentposition)) < 0) {
            Freehandle(HandleNumber);
            return Retval;
        }
    }
    /* If file is found and is to be opened for w, w+(write), a or a+(append)
       mode then check the file attribute. If it is READ_ONLY then  return error
       ERROR_OS_FILESYSTEM_FILE_WRITE_FAILED */
    else {
        if (Mode != READ_MODE) {
            RecordNo = Handle[HandleNumber].CurrentOffset >> 5;
            if (ReadDirectoryRecord(HandleNumber, RecordNo, buf) < 0)
                return ERROR_OS_FILESYSTEM_INVALID_RECORD_NUMBER;

            Handle[HandleNumber].FileSize = FSGetDWord((uint8_t *) buf, DIR_FILESIZEOFFSET);
            if (FSGetByte(buf, DIR_ATTRIBUTEOFFSET) & READ_ONLY) {
                Freehandle(HandleNumber);
                return (ERROR_OS_FILESYSTEM_FILE_WRITE_FAILED);
            }

            if (Handle[HandleNumber].StartingCluster != 0)
                Fseek(HandleNumber, -DIRRECORDSIZE, SEEK_CUR);

            UpdateHandle(HandleNumber, clusterno);
            Updatehandlemode(HandleNumber, READ_MODE + WRITE_MODE);
            /* If file is found and is to be opened for w, w+(write), a or a+(append)
               mode then check if the file is already opened for write mode. If file is 
               already opened for write mode then return error 'File can not be opened in write mode' */

            if (IsHandleWriteAllocated(HandleNumber) == WRITE_MODE) {
                Freehandle(HandleNumber);
                return (ERROR_OS_FILESYSTEM_FILE_WRITE_FAILED);
            }
            /* If file is to be opened in write mode (i.e. W or WPLUS) then 
               delete the contents of the file. */
            if (Mode == WRITE_MODE || Mode == WPLUS) {
                if (Handle[HandleNumber].StartingCluster != 0) {
                    //if((Retval = DeleteContent(HandleNumber,1)) <0) // 3.05 had this line commented out.
                    if ((Retval = DeleteContent(HandleNumber, 0)) < 0)  // 3.05 and 3.1prelim had this line active.
                    {
                        Freehandle(HandleNumber);
                        return Retval;
                    }
                    if ((Retval = UpdateFileSize(HandleNumber, 1)) < 0) {
                        Freehandle(HandleNumber);
                        return Retval;
                    }
                    Handle[HandleNumber].StartingCluster = 0;
                    Handle[HandleNumber].CurrentCluster = 0;
                    Handle[HandleNumber].CurrentSector = 0;
                    clusterlo = 0;
                    clusterhi = 0;

                    if ((Retval =
                         FSWriteSector(Handle[HandleNumber].Device, Handle[HandleNumber].DirSector,
                                       (Handle[HandleNumber].diroffset + DIR_FSTCLUSLOOFFSET),
                                       (uint8_t *) & clusterlo, 0, 2, WRITE_TYPE_RANDOM)) < 0)
                        return Retval;

                    if ((Retval =
                         FSWriteSector(Handle[HandleNumber].Device, Handle[HandleNumber].DirSector,
                                       (Handle[HandleNumber].diroffset + DIR_FSTCLUSHIOFFSET),
                                       (uint8_t *) & clusterhi, 0, 2, WRITE_TYPE_RANDOM)) < 0)
                        return Retval;
                }
            }
            /* If file is to be opened in append mode then set the current offset
               in the handle table to the end of file. */
            if (Mode == APPEND_MODE || Mode == APLUS) {
                if ((Retval = Fseek(HandleNumber, 0, SEEK_END)) < 0) {
                    Freehandle(HandleNumber);
                    return Retval;
                }
            }
        } else                  //   Mode == READ_MODE
        {
// SDK-6915: No need to seek the directory offset since we are at the right position already
//            if (Handle[HandleNumber].StartingCluster != 0)
//                Fseek(HandleNumber,-DIRRECORDSIZE,SEEK_CUR);

            UpdateHandle(HandleNumber, clusterno);
        }
    }
    /* Update the mode of handle table according to the given mode */
    if (Mode == RPLUS || Mode == WPLUS)
        Mode = (FileSystemModeTypes_t) (READ_MODE + WRITE_MODE);
    else if (Mode == APPEND_MODE)
        Mode = (FileSystemModeTypes_t) (WRITE_MODE + APPEND_MODE);
    else if (Mode == APLUS)
        Mode = (FileSystemModeTypes_t) (READ_MODE + WRITE_MODE + APPEND_MODE);

    Updatehandlemode(HandleNumber, Mode);
    return (HandleNumber);
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t Fremove(uint8_t *filepath)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to file name
				   
   Outputs:       SUCCESS or an error code if error occurs
   
   Description:   This function marks the specified file as deleted by making 
                  the first byte (character) of the file name in the directory 
                  entry as 0xE5.
----------------------------------------------------------------------------*/
RtStatus_t Fremove(const uint8_t * filepath)
{
    int32_t HandleNumber, RecordNo, index = 0, strlen = 0;
    int32_t Dir_Attr;
    RtStatus_t Retval;
    uint8_t buf[32];
    int32_t clusterno;

    /* Take temporary(directory) handle for searching the directory by changing path */
    HandleNumber = DIRECTORY_HANDLE;
    /* If the temporary handle is already active then change path is not possible */
    if (Handleactive(HandleNumber) == SUCCESS)
        return ERROR_OS_FILESYSTEM_CHANGEPATH_NOT_POSSIBLE;
    Handle[HandleNumber].HandleActive = 1;
    /* set the handle for search */
    if (SetHandleforsearch(HandleNumber, (uint8_t *) filepath, kDBCSEncoding, &index) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
    }

    strlen = Strlength((uint8_t *) filepath);
    /* search for the specified file by changing the path */
    if ((clusterno =
         Changepath(HandleNumber, (uint8_t *) filepath, kDBCSEncoding, strlen, index)) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_FILE_NOT_FOUND;
    }

    {
        BOOL protected = false;
        // Check for Write Protected media
        //! @todo Bring bach write protected media check.
//         DriveGetInfo( Handle[HandleNumber].Device,
//                       kDriveInfoIsWriteProtected,
//                      (void*)&protected );
        if (protected) {
            Freehandle(HandleNumber);
            return ERROR_OS_FILESYSTEM_FILE_DELETE_FAILED;
        }
    }

    /* Check file attribute, if file attribute is system, volume 
       or directory then file can not be deleted. Return error */
    RecordNo = Handle[HandleNumber].CurrentOffset >> 5;
    /* check for root directory */
    if ((ReadDirectoryRecord(HandleNumber, RecordNo, buf)) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_INVALID_RECORD_NUMBER;
    }

    Dir_Attr = FSGetByte(buf, DIR_ATTRIBUTEOFFSET);

    if (Dir_Attr & READ_ONLY || Dir_Attr & SYSTEM || Dir_Attr & DIRECTORY || Dir_Attr & VOLUME_ID) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_FILE_DELETE_FAILED;
    }

    Handle[HandleNumber].FileSize = FSGetDWord((uint8_t *) buf, DIR_FILESIZEOFFSET);

    /* Set the handle to original position */
    if (Handle[HandleNumber].StartingCluster != 0) {
        if ((Retval = Fseek(HandleNumber, -DIRRECORDSIZE, SEEK_CUR)) < 0) {
            Freehandle(HandleNumber);
            return Retval;
        }
    }
    /* Check whether the file is opened, if file is opened it can not be 
       deleted. Return error */

    if (Isfileopen(HandleNumber) == ERROR_OS_FILESYSTEM_FILE_OPEN) {
        Freehandle(HandleNumber);
        // We should return with this error code ( ERROR_OS_FILESYSTEM_FILE_OPEN ) so that top level code comes
        // to know that this file is open so don't remove it.
        // To Fix -> Stmp00014623
        return ERROR_OS_FILESYSTEM_FILE_OPEN;
    }

    /* Delete the directory record of the file */
    if ((Retval = DeleteRecord(HandleNumber, RecordNo)) < 0) {
        Freehandle(HandleNumber);
        return Retval;
    }

    /* Set the Handle to original position */
    Fseek(HandleNumber, (RecordNo * DIRRECORDSIZE), SEEK_SET);
    /* Update the handle to associate with the file to be deleted */
    UpdateHandle(HandleNumber, clusterno);

    if (Handle[HandleNumber].FileSize == 0) {
        Freehandle(HandleNumber);
        return (SUCCESS);
    }
    /* Delete the contents of the file (i.e. mark all the clusters occupied by 
       the file as zero in FAT Table). */
    if ((Retval = DeleteContent(HandleNumber, 0)) < 0) {
        Freehandle(HandleNumber);
        return Retval;
    }

    /* Free the handle used for file search */
    Freehandle(HandleNumber);

    return (SUCCESS);
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t Fremovew(uint8_t *filepath)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to file name
				   
   Outputs:       SUCCESS or an error code if error occurs
   
   Description:   This function marks the specified file as deleted by making 
                  the first byte (character) of the file name in the directory 
                  entry as 0xE5. It considers the string as UTF16.
----------------------------------------------------------------------------*/
RtStatus_t Fremovew(uint8_t * filepath)
{
    int32_t HandleNumber, RecordNo, index = 0, strlen;
    int32_t Dir_Attr;
    RtStatus_t Retval;
    uint8_t buf[32];
    int32_t clusterno;

    /* Take temporary(directory) handle for searching the directory by changing path */
    HandleNumber = DIRECTORY_HANDLE;

    /* If the temporary handle is already active then change path is not possible */
    if (Handleactive(HandleNumber) == SUCCESS)
        return ERROR_OS_FILESYSTEM_CHANGEPATH_NOT_POSSIBLE;
    Handle[HandleNumber].HandleActive = 1;

    /* set the handle for search */
    if (SetHandleforsearch(HandleNumber, filepath, kUTF16Encoding, &index) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
    }

    strlen = StrlengthW(filepath);
    /* search for the specified file by changing the path */
    if ((clusterno = Changepath(HandleNumber, filepath, kUTF16Encoding, strlen, index)) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_FILE_NOT_FOUND;
    }

    /* Check file attribute, if file attribute is system, volume 
       or directory then file can not be deleted. Return error */
    RecordNo = Handle[HandleNumber].CurrentOffset >> 5;

    /* check for root directory */
    if (ReadDirectoryRecord(HandleNumber, RecordNo, buf) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_INVALID_RECORD_NUMBER;
    }

    Dir_Attr = FSGetByte(buf, DIR_ATTRIBUTEOFFSET);

    if (Dir_Attr & READ_ONLY || Dir_Attr & SYSTEM || Dir_Attr & DIRECTORY || Dir_Attr & VOLUME_ID) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_FILE_DELETE_FAILED;
    }

    Handle[HandleNumber].FileSize = FSGetDWord((uint8_t *) buf, DIR_FILESIZEOFFSET);

    /* Set the handle to original position */
    if (Handle[HandleNumber].StartingCluster != 0) {
        if ((Retval = Fseek(HandleNumber, -DIRRECORDSIZE, SEEK_CUR)) < 0) {
            Freehandle(HandleNumber);
            return Retval;
        }
    }
    /* Check whether the file is opened, if file is opened it can not be 
       deleted. Return error */
    if (Isfileopen(HandleNumber) == ERROR_OS_FILESYSTEM_FILE_OPEN) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_FILE_DELETE_FAILED;
    }
    /* Delete the directory record of the file */
    if ((Retval = DeleteRecord(HandleNumber, RecordNo)) < 0) {
        Freehandle(HandleNumber);
        return Retval;
    }

    /* Set the Handle to original position */
    Fseek(HandleNumber, (RecordNo * DIRRECORDSIZE), SEEK_SET);
    /* update the handle to associate with the file to be deleted */
    UpdateHandle(HandleNumber, clusterno);

    /* Delete the contents of the file (i.e. Mark all the clusters occupied by 
       the file as zero in FAT Table). */
    if ((Retval = DeleteContent(HandleNumber, 0)) < 0) {
        Freehandle(HandleNumber);
        return Retval;
    }

    /* Free the handle used for file search */
    Freehandle(HandleNumber);
    return (SUCCESS);
}

///////////////////////////////////////////
//! \brief Renames a file or directory
//!
//! \fntype Function
//!
//! This function renames given file.  
//!
//! \param[in]  oldFilename
//! \param[in]  newFilename
//!
//! \return Status of call.
//! \retval 0      If no error has occurred
//!
///////////////////////////////////////////

int32_t Frename(uint8_t * oldFilename, uint8_t * newFilename)
{
    int32_t HandleNumber;
    int32_t RecordNo;
    int32_t strLength;
    int32_t index = 0;
    int32_t currentposition = 0;
    int32_t Retval;
    uint8_t buf[32];
    int32_t clusterno;
    int32_t clusterlo;
    int32_t clusterhi;
    int32_t DirAttr;
    int32_t FileSize;

#ifdef FS_USE_MALLOC
    uint8_t *UnicodeBuffer;
    UnicodeBuffer = malloc(MAX_UNICODE_SIZE * sizeof(uint8_t));
    if (NULL == UnicodeBuffer) {
        return ERROR_OS_FILESYSTEM_MEMORY;
    }
#else
    uint8_t UnicodeBuffer[MAX_UNICODE_SIZE];
#endif

    /* Search for free handle and allocate it */
    if ((HandleNumber = Searchfreehandleallocate()) < 0) {
#ifdef FS_USE_MALLOC
        free(UnicodeBuffer);
#endif
        return (ERROR_OS_FILESYSTEM_NO_FREE_HANDLE);
    }

    /* set the handle for search */
    if (SetHandleforsearch(HandleNumber, (uint8_t *) oldFilename, kUTF16Encoding, &index) < 0) {
        Freehandle(HandleNumber);
#ifdef FS_USE_MALLOC
        free(UnicodeBuffer);
#endif
        return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
    }

    strLength = StrlengthW((uint8_t *) oldFilename);

    currentposition = Extractfilenamew((uint8_t *) oldFilename, &index);

    /* Go to the specified directory level by changing the path */
    if (currentposition != index) {
        if ((clusterno =
             Changepath(HandleNumber, (uint8_t *) oldFilename, kUTF16Encoding, currentposition,
                        index)) < 0) {
            Freehandle(HandleNumber);
#ifdef FS_USE_MALLOC
            free(UnicodeBuffer);
#endif
            return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
        }
        UpdateHandle(HandleNumber, clusterno);
    }

    /* search for the specified file */
    if (currentposition == 0)
        currentposition = index;

    if ((clusterno =
         Changepath(HandleNumber, (uint8_t *) oldFilename, kUTF16Encoding, strLength * 2,
                    currentposition)) < 0) {
        Freehandle(HandleNumber);
#ifdef FS_USE_MALLOC
        free(UnicodeBuffer);
#endif
        return (ERROR_OS_FILESYSTEM_FILE_NOT_FOUND);
    } else {

        /* Directory entry of file-name has been located.  Now, change file-name. */

        RecordNo = Handle[HandleNumber].CurrentOffset >> 5;

        if (ReadDirectoryRecord(HandleNumber, RecordNo, buf) < 0) {
            Freehandle(HandleNumber);
#ifdef FS_USE_MALLOC
            free(UnicodeBuffer);
#endif
            return (ERROR_OS_FILESYSTEM_FILE_NOT_FOUND);
        }

        clusterlo = FSGetWord(buf, DIR_FSTCLUSLOOFFSET);

        clusterhi = FSGetWord(buf, DIR_FSTCLUSHIOFFSET);

        clusterno = (clusterhi << 16) | (clusterlo & 0xFFFF);

        DirAttr = buf[DIR_ATTRIBUTEOFFSET];

        FileSize = FSGetDWord((uint8_t *) buf, DIR_FILESIZEOFFSET);

        if (Handle[HandleNumber].StartingCluster != 0) {
            if ((Retval = Fseek(HandleNumber, -DIRRECORDSIZE, SEEK_CUR))) {
                Freehandle(HandleNumber);
#ifdef FS_USE_MALLOC
                free(UnicodeBuffer);
#endif
                return Retval;
            }
        }

        /* Delete the directory record of the file.  Contents are
         * intact, and as long as new record references old
         * cluster number, all is well
         */
        if ((Retval = DeleteRecord(HandleNumber, RecordNo)) < 0) {
            Freehandle(HandleNumber);
#ifdef FS_USE_MALLOC
            free(UnicodeBuffer);
#endif
            return Retval;
        }

        index = 0;

        currentposition = Extractfilenamew((uint8_t *) newFilename, &index);

        strLength = StrlengthW((uint8_t *) newFilename);

        Retval = (int32_t) CreateDirRecord(newFilename,
                                           HandleNumber,
                                           clusterno,
                                           DirAttr,
                                           kUTF16Encoding,
                                           strLength * 2,
                                           currentposition, (uint8_t *) UnicodeBuffer, FileSize);

        if (Retval < 0) {
            Freehandle(HandleNumber);
#ifdef FS_USE_MALLOC
            free(UnicodeBuffer);
#endif
            return Retval;
        }

    }                           /* else */

#ifdef FS_USE_MALLOC
    free(UnicodeBuffer);
#endif
    Freehandle(HandleNumber);

    FlushCache();

    return (0);
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t DeleteContent(int32_t HandleNumber,int32_t bUseVestigialClusterEraser)

   FunctionType:  Reentrant

   Inputs:        1) HandleNumber
                  2) bUseVestigialClusterEraser - If nonzero, then an old algorithm is used.  Not advisable.

   Outputs:       Returns an Error code if function fails otherwise SUCCESS

   Description:   This function deletes contents of the file referenced by the
                  handle no (i.e.  Marks the clusters occupied by the file as
                  zero in the FAT Table )
<
----------------------------------------------------------------------------*/
RtStatus_t DeleteContent(int32_t HandleNumber, int32_t bUseVestigialClusterEraser)
{
    int32_t clusterno, nFileSizeInBytes, nFileSizeInClusters, FATentry;
    int32_t FATsector, iCluster, Device, FATNtryOffsetInBytesInThisSector,
        iFirstFATSectorOnTheDevice;
    BOOL exitCondition;
    int32_t oldFATSector;
#ifdef ENABLE_WRITE_FAT2        /* Write FAT2 */
    int32_t FATSize;
#endif

    uint8_t *p_u8_CopyOfASectorOfFAT;   // Like the name says, this points to a copy of
    // one sector of the FAT itself.
    // For performance reasons, a whole sector of the FAT is
    // read into this buffer at one time, the "DeleteContent"
    // procedure is performed, and then the sector is written back
    // to the FAT.

    int32_t SectorMask, BytesPerSector, ret, FAToffsetInBytes;
    int32_t FatType;
    int32_t FatShift;
    MediaCacheParamBlock_t pb = { 0 };

    if ((nFileSizeInBytes = GetFileSize(HandleNumber)) == 0) {
        nFileSizeInBytes = 0x7fffffff;  // Set the file size as the largest positive number for directory
    }
    Device = Handle[HandleNumber].Device;

    if (0x7fffffffL - nFileSizeInBytes >= MediaTable[Device].ClusterMask) {
        nFileSizeInClusters =
            (MediaTable[Device].ClusterMask + nFileSizeInBytes) >> MediaTable[Device].ClusterShift;
        //
        // Note: Right-shifting by "ClusterShift" gives the quantity
        // of clusters, but truncates that value.
        // A 0.5 cluster file would be truncated to zero clusters.
        // But that file still consumes a cluster, so "zero" is not the right answer.
        //
        // What's needed is a "ceiling" calculation.  We can have that calculation by adding
        // "clustersize-in-bytes - 1" to the file size, then truncating to the integer quantity
        // of clusters.  ClusterMask happens to equal "clustersize-in-bytes - 1". 
        //
        // This way, 0.5 clusters becomes 1, 1 cluster is unchanged, 1.5 clusters becomes 2, etc.
    } else {
        nFileSizeInClusters = (0x7fffffffL >> MediaTable[Device].ClusterShift) + 1;
    }

    clusterno = Handle[HandleNumber].StartingCluster;
    if (0 == clusterno) {       /* If starting cluster number is 0, there's no content to delete */
        return SUCCESS;
    }

    BytesPerSector = MediaTable[Device].BytesPerSector;

    if (bUseVestigialClusterEraser) {
        FATentry = Findnextcluster(Device, clusterno);
        if (FATentry == ERROR_OS_FILESYSTEM_EOF) {
            return SUCCESS;
        }
        if (FATentry <= 0) {
            return ERROR_OS_FILESYSTEM_INVALID_CLUSTER_NO;
        }
        FATsector = FATsectorno(Device, clusterno, &FATNtryOffsetInBytesInThisSector);
        WriteFATentry(Device, FATsector, FATNtryOffsetInBytesInThisSector, clusterno, FAT32EOF);
        clusterno = FATentry;
        nFileSizeInClusters--;
    }
    //
    // All subsequent reads and writes to the FAT will be sector-by-sector.
    // This is the first sector that contains the FAT:
    //
    iFirstFATSectorOnTheDevice = FATsectorno(Device, 0, &FATNtryOffsetInBytesInThisSector);

    FatType = MediaTable[Device].FATType;
    oldFATSector = -1;
#ifdef ENABLE_WRITE_FAT2        /* Write FAT2 */
    FATSize = MediaTable[Device].FATSize;
#endif
    SectorMask = MediaTable[Device].SectorMask;

    //
    // Check that HandleNumber refers to a real cluster, not free space nor
    // the end of a cluster chain.
    //
    if (FatType == FAT32) {     // end of cluster chain or free cluster?
        exitCondition = ((FAT32EOF == clusterno) || (0 == clusterno));
    } else if (FatType == FAT12) {
        exitCondition = ((((uint32_t) clusterno) > ((uint32_t) 0x0FF5)) || (0 == clusterno));
    } else                      // FAT16
    {
        exitCondition = ((((uint32_t) clusterno) > ((uint32_t) 0xFFF0)) || (0 == clusterno));
    }

    if (exitCondition) {
        // Free space or the end of a cluster chain.
        return SUCCESS;
    }
    //
    // Determine the number of sectors per cluster.
    //
    if (FatType == FAT32) {
        // shift to convert FAT32 cluster to FAT sector is sector size / 4 == sector shift - 2
        FatShift = MediaTable[Device].SectorShift - 2;
    } else if (FatType == FAT12) {
        //FatShift  = FAT12_ENTRIES_PER_512SECTOR * (MediaTable[Device].BytesPerSector >> 9);
        FatShift = ((BytesPerSector) * 8) / 12;
    } else                      // FAT16
    {
        // shift to convert FAT16 cluster to FAT sector is sector size / 2 == sector shift - 1
        FatShift = MediaTable[Device].SectorShift - 1;
    }

    EnterNonReentrantSection();

    //
    // Which sector in the FAT refers to this cluster?
    // Compute the sector number and read that sector in.
    //
    if (FatType == FAT12) {
        FATsector = clusterno / FatShift;
    } else {
        FATsector = clusterno >> FatShift;
    }

    // Set up the param block. Here we're using the media cache directly instead
    // of going through the cache wrapper functions because using a pinned write
    // is much more efficient than a separate read and write call with a temporary
    // buffer.
    pb.drive = Device;
    pb.sector = FATsector + iFirstFATSectorOnTheDevice;
    pb.requestSectorCount = 1;
    pb.mode = WRITE_TYPE_RANDOM;
    pb.weight = kMediaCacheWeight_High;
    pb.flags = kMediaCacheFlag_ApplyWeight;
    pb.buffer = malloc(MediaTable[Device].BytesPerSector);  // sectorSize

    if (media_cache_pinned_write(&pb) != SUCCESS) {
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
    }
    p_u8_CopyOfASectorOfFAT = pb.buffer;

    //
    // Loop over all clusters that contain the file, and mark those clusters
    // as free in the FAT.
    //
    for (iCluster = 1; iCluster <= nFileSizeInClusters; iCluster++) {
        //
        // Which sector in the FAT refers to this cluster?
        // Compute the sector number and read that sector in.
        //
        if (FatType == FAT12) {
            FATsector = clusterno / FatShift;
        } else {
            FATsector = clusterno >> FatShift;
        }

        if ((FATsector != oldFATSector) && (oldFATSector != -1))    // skipped in 1st loop. Write Sector only when new sector reached.
        {
            // We are looping through the FAT, and the current cluster is represented in a different
            // sector of the FAT than the previous cluster.
            // We need to write out our local sector buffer, and read in the next one.

            // sdk3.1 adds this ifndef check so when single fat mode enabled, don't write the second FAT.
#ifdef ENABLE_WRITE_FAT2        /* Write FAT2 */
            // Write the pinned sector contents (FAT1) to FAT2.
            pb.sector = oldFATSector + iFirstFATSectorOnTheDevice + FATSize;
            pb.writeOffset = 0;
            pb.writeByteCount = BytesPerSector;
            pb.weight = kMediaCacheWeight_Low;  // FAT2 has a low weighting
            pb.flags = kMediaCacheFlag_ApplyWeight;
            media_cache_write(&pb);
#endif

            // Complete the pinned write to commit our changes to the FAT sector.
            media_cache_release(pb.token);

            // Now set up a pinned write for the new sector.
            pb.sector = FATsector + iFirstFATSectorOnTheDevice;
            pb.weight = kMediaCacheWeight_High;
            pb.flags = kMediaCacheFlag_ApplyWeight;

            if (media_cache_pinned_write(&pb) != SUCCESS) {
                LeaveNonReentrantSection();
                return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
            }
            p_u8_CopyOfASectorOfFAT = pb.buffer;
        }
        /* if */
        //
        // What's the offset in bytes of the FAT entry that represents
        // clusterno?
        //
        if (FatType == FAT12) {
            FAToffsetInBytes = clusterno + (clusterno >> 1);
        }
        // clusterno * 4 or 2 gives offset into FAT32 or FAT16 table entry
        else if (FatType == FAT32) {
            FAToffsetInBytes = clusterno << 2;
        } else                  //Fat16
        {
            FAToffsetInBytes = clusterno << 1;
        }
        FATNtryOffsetInBytesInThisSector = FAToffsetInBytes & SectorMask;

        //
        // Read the current FAT entry (which may be a link to the next FAT entry),
        // overwrite the current FAT entry as "free",
        // and then see if there *was* actually a link to a next entry.
        //
        if (FatType == FAT32) {
            FATentry = FSGetDWord(p_u8_CopyOfASectorOfFAT, FATNtryOffsetInBytesInThisSector);
            PutDword(p_u8_CopyOfASectorOfFAT, FAT32FREECX, FATNtryOffsetInBytesInThisSector);
            exitCondition = ((0x0FFFFFFF == FATentry) || (0 == FATentry));
        } else if (FatType == FAT12) {
            FATentry = FSGetWord(p_u8_CopyOfASectorOfFAT, FATNtryOffsetInBytesInThisSector);
            FATentry &= (FATentry & FAT12EOF);
            exitCondition = ((((uint32_t) FATentry) > ((uint32_t) 0x0FF5)) || (0 == FATentry));
            ret = (FATentry & ~FAT12EOF);
            PutWord(p_u8_CopyOfASectorOfFAT, ret, FATNtryOffsetInBytesInThisSector);
        } else {
            FATentry = FSGetWord(p_u8_CopyOfASectorOfFAT, FATNtryOffsetInBytesInThisSector);
            PutWord(p_u8_CopyOfASectorOfFAT, FAT16FREECX, FATNtryOffsetInBytesInThisSector);
            exitCondition = ((((uint32_t) FATentry) > ((uint32_t) 0xFFF0)) || (0 == FATentry));
        }

        MediaTable[Device].TotalFreeClusters++;

        //
        // Check if FATentry refers to a real cluster, not free space nor
        // the end of a cluster chain.
        //
        if (exitCondition) {
            // Free space or the end of a cluster chain.
            break;
        }
        //
        // Set the new cluster number for the next loop.
        //
        clusterno = FATentry;

//      if(clusterno == FS_EOF) // early exit if early EOF hit
//         break;  // this was present in old ver below. Do we need this here too?  TOVERIFY5

        if (clusterno <= 0) {
            media_cache_release(pb.token);
            LeaveNonReentrantSection();
            return ERROR_OS_FILESYSTEM_INVALID_CLUSTER_NO;
        }
        //
        // Note the current sector in the FAT, before we loop.
        //
        oldFATSector = FATsector;

    }                           /* end for */

    // sdk3.1 adds this ifndef check so when single fat mode enabled, don't write the second FAT.
#ifdef ENABLE_WRITE_FAT2        /* Write FAT2   */
    // Write the pinned sector contents (FAT1) to FAT2.
    pb.sector = FATsector + iFirstFATSectorOnTheDevice + FATSize;
    pb.writeOffset = 0;
    pb.writeByteCount = BytesPerSector;
    pb.weight = kMediaCacheWeight_Low;  // FAT2 has a low weight
    pb.flags = kMediaCacheFlag_ApplyWeight;
    media_cache_write(&pb);
#endif

    // Complete the pinned write to commit our changes to the FAT sector.
    media_cache_release(pb.token);

    LeaveNonReentrantSection();

    free(pb.buffer);
    return SUCCESS;
}
