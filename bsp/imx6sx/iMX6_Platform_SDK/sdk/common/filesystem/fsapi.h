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
////////////////////////////////////////////////////////////////////////////////
//! \addtogroup os_fat
//! @{
//!
//  Copyright (c) 2005-2008 SigmaTel, Inc.
//!
//! \file    fsapi.h
//! \brief   Contains the FAT file system public API. Supports FAT32 and FAT16.
//!
////////////////////////////////////////////////////////////////////////////////
#ifndef _FS_API_H
#define _FS_API_H

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "sdk.h"
#include "os_filesystem_errordefs.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

#define FS_USE_MALLOC 1

#define SEEK_SET           	0
#define SEEK_CUR            1
#define SEEK_END            2

#define INVALID_FILESYSTEM	      (WORD)(3)

#ifndef MAX_FILENAME_LENGTH
#define MAX_FILENAME_LENGTH 256
#endif

#define ATTR_READ_ONLY      0x01
#define ATTR_HIDDEN         0x02
#define ATTR_SYSTEM         0x04
#define ATTR_VOLUME_ID      0x08
#define ATTR_DIRECTORY      0x10
#define ATTR_ARCHIVE        0x20
#define ATTR_LONG_NAME      (ATTR_READ_ONLY|ATTR_HIDDEN|ATTR_SYSTEM|ATTR_VOLUME_ID)
#define MAX_FILESNAME   13

typedef struct _FindData {
    uint8_t attrib;
    int32_t FileSize;
    uint8_t device;
    uint32_t startrecord;
    uint8_t name[MAX_FILESNAME];
    int64_t Key;
} FindData_t;

typedef struct {
    uint8_t Day;
    uint8_t Month;
    int16_t Year;
} DIR_DATE;

typedef struct {
    uint8_t Second;
    uint8_t Minute;
    uint8_t Hour;
} DIR_TIME;

// Use for 'crt_mod_date_time_para' parameter
#define CREATION_DATE       1
#define CREATION_TIME       2
#define MODIFICATION_DATE   3
#define MODIFICATION_TIME   4

// Use for 'dirattribute' parameter
#define READ_ONLY           0X01
#define HIDDEN              0X02
#define SYSTEM              0X04
#define VOLUME_ID           0X08
#define DIRECTORY           0X10
#define ARCHIVE             0X20

#define MAX_UNICODE_SIZE 512

////////////////////////////////////////////////////////////////////////////////
// Externs
////////////////////////////////////////////////////////////////////////////////

//! \brief Maximum number of drives supported by the file system. 
//! 
//! Typically, \c maxdevices is 2.
extern const int32_t maxdevices;

//! \brief Maximum number of handles available in the file system.
//! 
//! The number of handles available to the user is maxhandles - 2. 
//! Two handles are reserved by the file system for internal use only. 
//! The number of handles decides the number of files, which can 
//! simultaneously be open. Typically, \c maxhandles is 16.
extern const int32_t maxhandles;

//! \brief Total number of cache buffers. 
//! 
//! Increasing the number of cache buffers improves the performance of 
//! the file system when several threads are accessing the file system. 
//! Typically, \c maxcaches is 8.
extern const int32_t maxcaches;

//! \brief Assigns a drive letter to a drive.
//! 
//! For example, in the following sample code, \n
//!
//! \c A is assigned to drive 0,\n
//! \c B is assigned to drive 1, and \n
//! \c C is assigned to drive 2.
//! \code
//! int32_t DriveLetter[] = {'A','B','C'};
//! \endcode
extern const uint8_t DriveLetter[];

// The cache buffers are allocated in the X buffer.
//extern BYTE bufx[NUMCACHES*CACHEBUFSIZE];
#ifndef _WIN32
//#pragma alignvar(32)
__attribute__ ((aligned(32)))
#endif
//! \brief X memory buffer.
extern uint8_t bufx[];

#ifndef _WIN32
//#pragma alignvar(4)
__attribute__ ((aligned(4)))
#endif
//! \brief Y memory buffer.
extern uint8_t bufy[];

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif                          // __cplusplus

///////////////////////////////////////////////////////////////////////////////
//! \brief Redirects an Fclose request
//!                  
//! \fntype Function                  
//!                  
//! Redirects an Fclose request to the appropriate handler based on the
//! specified file handle.
//!                  
//! \param[in]  handleNumber Handle of the file to close
//!         
//! \return Value of the steering function or an error.
//! \retval ERROR_OS_FILESYSTEM_NO_STEERING_FUNCTION If there is no steering function defined for \c filehandle
//!
//! \internal
//! \see To view the function definition, see fs_steering.c.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t Fclose(int32_t handleNumber);

///////////////////////////////////////////////////////////////////////////////
//! \brief Redirects an Fread request
//!                  
//! \fntype Function                  
//!                  
//! Redirects an Fread request to the appropriate handler based on the
//! specified file handle.
//!                  
//! \param[in]  handleNumber   Handle of the file to read from
//! \param[out] pBuffer        Buffer in which the data to be read is placed
//! \param[in]  numBytesToRead Number of bytes to read from the file
//!                  
//! \return Number of bytes read if the steering function was successful or an RtStatus_t error.
//! \retval ERROR_OS_FILESYSTEM_NO_STEERING_FUNCTION If there is no steering function defined for \c filehandle
//!
//! \internal
//! \see To view the function definition, see fs_steering.c.
///////////////////////////////////////////////////////////////////////////////
    int32_t Fread(int32_t handleNumber, uint8_t * pBuffer, int32_t numBytesToRead);

///////////////////////////////////////////////////////////////////////////////
//! \brief Redirects an Fwrite request
//!                  
//! \fntype Function                  
//!                  
//! Redirects an Fwrite request to the appropriate handler based on the
//! specified file handle.
//!                  
//! \param[in]  handleNumber   Handle of the file to write to
//! \param[in]  pBuffer        Buffer holding the data to be written
//! \param[in]  numBytesToWrite Number of bytes to write to the file
//!                  
//! \return Number of bytes read if the steering function was successful or an RtStatus_t error.
//! \retval ERROR_OS_FILESYSTEM_NO_STEERING_FUNCTION If there is no steering function defined for \c filehandle
//!
//! \internal
//! \see To view the function definition, see fs_steering.c.
///////////////////////////////////////////////////////////////////////////////
    int32_t Fwrite(int32_t handleNumber, uint8_t * pBuffer, int32_t numBytesToWrite);

///////////////////////////////////////////////////////////////////////////////
//! \brief Redirects an Fseek request
//!                  
//! \fntype Function                  
//!                  
//! Redirects an Fseek request to the appropriate handler based on the
//! specified file handle.
//!                  
//! \param[in]  handleNumber   Handle of the file to seek
//! \param[in]  numBytesToSeek Relative number of bytes to seek
//! \param[in]  seekPosition   Value indicating where to seek from
//!                  
//! \retval ERROR_OS_FILESYSTEM_NO_STEERING_FUNCTION If there is no steering function defined for \c filehandle
//! \retval RtStatus_t The return value of the steering function
//! \internal
//! \see To view the function definition, see fs_steering.c.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t Fseek(int32_t handleNumber, int32_t numBytesToSeek, int32_t seekPosition);

////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Fopen Opens a file for subsequent access.
//!
//! \param[in] filepath Pointer to a null-terminated ASCII string that contains the name of the file to open.
//!
//! \param[in] mode Null-terminated ASCII string that specifies how the file will be accessed. It must be one of the following:
//!
//!     -   "r"     =   open for reading only
//!     -   "r+"        =   same as "r", also allows writing
//!     -   "w"     =   open for writing only, file will be created if it does 
//!                     not exist, and will be overwritten if it does exist
//!     -   "w+"        =   same as "w", also allows reading
//!     -   "a"     =   open for appending to end of file, upon opening
//!                     file position is set to end-of-file
//!     -   "a+"        =   same as "a", also allows reading/writing
//!
//!
//!  \param[out] handle Returns an int32_t which uniquely identifies the file while it is open, and which must be
//!  used on all subsequent file system calls to access this file If this value is negative, then an error occurred.
//!
//!
//!  Long file name considerations
//!
//!    
//!  When creating a file (opening it with either "w" or "w+" modes) the
//!  FAT file system uses the following considerations to determine whether
//!  the file name will be stored on the media with a short name only (older
//!  style) or with both a short name and a long name.
//!
//! -   The file name is parsed into 2 parts, the part before the period (filespec) and the part after (extension)
//!
//! -   If more than one period is found during parsing, a long file name is created.
//!
//! -   If the filespec is more than 11 characters long a long file name is created.
//!
//! -   If the extension is more than 3 characters long a long file name is created
//!
//! -   If the filespec or the extension contains a space character or any one of +,;=[](plus-sign,comma,semi-colon,
//!     equal-sign,open-brace,close-brace) then a long file name is created.
//!
//! -   If a long file name is not used, the filepec and extension are converted 
//!     to upper case, and the resulting short file name is created.
//!
//!
//!  \internal
//!
//!   All of the checking listed above actually takes place in
//!   the function 'IsShortNameValid()' (which is in 'isshortnamevalid.c')
//!
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t Fopen(uint8_t * filepath, uint8_t * mode);

///////////////////////////////////////////////////////////////////////////////
//!
//! \brief Fopenw Opens a file for subsequent access.
//!
//! \param[in] filepath Pointer to a null-terminated UNICODE string that contains the name of the file to open.
//!
//! \param[in] mode Null-terminated ASCII string that specifies how the file will be accessed. It must be one of the following:
//!
//!     -   "r"     =   open for reading only
//!     -   "r+"        =   same as "r", also allows writing
//!     -   "w"     =   open for writing only, file will be created if it does 
//!                     not exist, and will be overwritten if it does exist
//!     -   "w+"        =   same as "w", also allows reading
//!     -   "a"     =   open for appending to end of file, upon opening
//!                     file position is set to end-of-file
//!     -   "a+"        =   same as "a", also allows reading/writing
//!
//!
//!  \param[out] handle Returns an int32_t which uniquely identifies the file while it is open, and which must be
//!  used on all subsequent file system calls to access this file If this value is negative, then an error occurred.
//!
//!
//!  Long file name considerations
//!
//!  Since the input filepath is in UNICODE, this function ALWAYS creates a long file name
//!
    RtStatus_t Fopenw(uint8_t * filepath, uint8_t * mode);

    RtStatus_t Fclose_FAT(int32_t HandleNumber);
    RtStatus_t Fgetc(int32_t HandleNumber);
    RtStatus_t Fputc(int32_t HandleNumber, int32_t ByteToWrite);
    uint8_t *Fgets(int32_t HandleNumber, int32_t NumBytes, uint8_t * Buffer);
    uint8_t *Fputs(int32_t HandleNumber, uint8_t * Buffer);
    RtStatus_t Fread_FAT(int32_t HandleNumber, uint8_t * Buffer, int32_t NumBytesToRead);
    RtStatus_t Fwrite_FAT(int32_t HandleNumber, uint8_t * Buffer, int32_t NumBytesToWrite);
    int32_t Feof(int32_t HandleNumber);
    int32_t Ftell(int32_t HandleNumber);
    int32_t Ferror(int32_t HandleNumber);
    RtStatus_t Fseek_FAT(int32_t HandleNumber, int32_t NumBytesToSeek, int32_t SeekPosition);
    RtStatus_t Fflush(int32_t HandleNumber);
    RtStatus_t Fremove(const uint8_t * filepath);
    RtStatus_t Fremovew(uint8_t * filepath);

////////////////////////////////////////////////////////////////////////////////
// Miscellaneous File System Prototypes
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//! \brief Initializes the file system.
//!
//! \param[in] bufx       Pointer to X buffer for allocation of cache buffers.
//! \param[in] bufy       Pointer to Y buffer for allocation of handles, descriptors, etc.
//! \param[in] maxdevices Max number of internal + external media supported.
//! \param[in] maxhandles Max handles supported.
//! \param[in] maxcaches  Max cache buffers supported.
//!
//! \return Status of the call.
//! \retval 0 If the call was successful.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t FSInit(uint8_t * bufx, uint8_t * bufy, int32_t maxdevices, int32_t maxhandles,
                      int32_t maxcaches);

    int32_t FSDriveInit(int32_t DeviceNumber);
    int32_t FSDriveShutdown(int32_t DeviceNumber);

///////////////////////////////////////////////////////////////////////////////
//! \brief Determines free space by reading the all records 
//!
//! \return Status of the call.
//! \retval 0 If successful.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t FSShutdown(void);

///////////////////////////////////////////////////////////////////////////////
//! \brief Determines total free clusters by first checking FAT type.
//!
//! \param[in] DeviceNumber Device number.
//!
//! \return Returns total number of free clusters.
///////////////////////////////////////////////////////////////////////////////
    int32_t Computefreecluster(int32_t DeviceNumber);

///////////////////////////////////////////////////////////////////////////////
//! \brief Gets the size of the file.
//!
//! \param[in] HandleNumber File handle.
//!
//! \return Status of the call.
//! \retval 0 If the call was successful.
//! \retval error If an error occurred.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t GetFileSize(int32_t HandleNumber);

///////////////////////////////////////////////////////////////////////////////
//! \brief Flushes only the dirty cache buffers that contain valid
//!        data to the disk, but invalidates all cache entries.
//!
//! \return Status of the call.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t FlushCache(void);

///////////////////////////////////////////////////////////////////////////////
//! \brief For device "deviceNumber", flushes only the dirty cache buffers that contain valid
//!        data to the disk, and invalidates their cache entries.
///////////////////////////////////////////////////////////////////////////////
    int32_t FSFlushDriveCache(int32_t deviceNumber);    //The real code calls for RtStatus_t

///////////////////////////////////////////////////////////////////////////////
//! \brief Returns FAT type.
//!
//! \param[in] DeviceNum
///////////////////////////////////////////////////////////////////////////////
    int32_t FSFATType(int32_t DeviceNum);

///////////////////////////////////////////////////////////////////////////////
//! \brief Returns a value that indicates whether the specified device is present.
//!
//! \param[in] DeviceNum Device number of the specified device.
//!
//! \return A value that indicates whether the device is present.
///////////////////////////////////////////////////////////////////////////////
    int32_t FSMediaPresent(int32_t DeviceNum);

    int32_t FSFreeClusters(int32_t Device);
    int64_t FSFreeSpace(int32_t Device);
    int64_t FSFreeSpaceFromHandle(int32_t HandleNumber);
    int32_t FSSize(int32_t DeviceNum);

////////////////////////////////////////////////////////////////////////////////
// Directory API
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//! \brief Searches for the given directoy path and if the path is found 
//!        then changes the current working directoy to the given directory path.
//!
//! \param[in] filepath Pointer to file name.
//!
//! \return Status of the call.
//! \retval SUCCESS
//! \retval Error If error occurs.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t Chdir(uint8_t * filepath);

///////////////////////////////////////////////////////////////////////////////
//! \brief Searches for the given directoy path for UNICODE string and if the path is found 
//!        then changes the current working directoy to the given directory path.
//!
//! \param[in] filepath Pointer to the file name.
//!
//! \return Status of the call.
//! \retval SUCCESS
//! \retval Error If error occurs.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t Chdirw(uint8_t * filepath);

    RtStatus_t Mkdir(uint8_t * filepath);
    RtStatus_t Mkdirw(uint8_t * filepath);

///////////////////////////////////////////////////////////////////////////////
//! \brief Searches for the given directory, and if it is found, empties and 
//!        deletes the directory.
//!
//! \param[in] filepath Pointer to the file name.
//!
//! \return Status of the call.
//! \retval FS_SUCCESS If call was successful.
//! \retval Error      If error occurs.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t Rmdir(uint8_t * filepath);

///////////////////////////////////////////////////////////////////////////////
//! \brief Searches for the given directory, and if it is found, empties and 
//!        deletes the directory. 
//!
//! \param[in] filepath Pointer to the file name.
//!
//! \return Status of the call.
//! \retval FS_SUCCESS If call was successful.
//! \retval Error      If error occurs.
//!
//! \note This function considers the string to be Unicode.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t Rmdirw(uint8_t * filepath);

///////////////////////////////////////////////////////////////////////////////
//! \brief Deletes all the files and directories of the specified path.
//!
//! \param[in] Path Pointer to the directory path.
//!
//! \return Status of the call.
//! \retval 0     If the call was successful.
//! \retval Error If an error occurs.
///////////////////////////////////////////////////////////////////////////////
    int32_t DeleteTree(uint8_t * Path);

    int32_t Frename(uint8_t * oldFilename, uint8_t * newFilename);

///////////////////////////////////////////////////////////////////////////////
//! \brief Returns the pointer to the \c gCurrentWorkingdirectory string buffer.
//!
//! \return Pointer to current working directory buffer.
///////////////////////////////////////////////////////////////////////////////
    uint8_t *Getcwd(void);

///////////////////////////////////////////////////////////////////////////////
//! \brief TBD
//!
//! \param[in] DeviceNo Device number to set the cwd handle to root dir of
//!
//! \retval 0 If successful
///////////////////////////////////////////////////////////////////////////////
    int32_t SetCWDHandle(int32_t DeviceNo);

////////////////////////////////////////////////////////////////////////////////
// Find file API
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//! \brief Provides base, file name, and extension of the file to the FindNext() function.
//!
//! \param[in] _finddata File specification
//! \param[in] FileName  Pointer to the file name.
//!
//! \return Status of the call.
//! \retval 0 If successful.
//! \retval Error 
//!
//! \note This function should not be called from multiple tasks.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t FindFirstLFN(FindData_t * _finddata, uint8_t * FileName, void *);

    RtStatus_t FindFirst(FindData_t * _finddata, uint8_t * FileName);
    RtStatus_t FindNextLFN(int32_t HandleNumber, FindData_t * _finddata, void *);
    RtStatus_t FindNext(int32_t HandleNumber, FindData_t * _finddata);
    RtStatus_t FindClose(int32_t HandleNumber);

////////////////////////////////////////////////////////////////////////////////
// File attribute API
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//! \brief Finds the creation or modification date or time of 
//!                  the file referenced by the given handle number.
//!
//! \param[in] HandleNumber           Handle number.
//! \param[in] crt_mod_date_time_para Create-modify-date-time parameter.
//! \param[in] dirdate                Pointer to the DIR_DATE structure.
//! \param[in] dirtime                Pointer to the DIR_TIME structure.
//!
//! \return Status of the call.
//! \retval 0 If successful.
//! \retval ERROR If an error occurs.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t filegetdate(int32_t HandleNumber, int32_t crt_mod_date_time_para, DIR_DATE * dirdate,
                           DIR_TIME * dirtime);

///////////////////////////////////////////////////////////////////////////////
//! \brief Sets the creation or modification date or time of 
//!                  the file referenced by the given handle to the specified date or time.
//!
//! \param[in] FilePath               Pointer to the file path.
//! \param[in] crt_mod_date_time_para Create-modify-date-time parameter.
//! \param[in] dirdate                Pointer to the DIR_DATE structure.
//! \param[in] dirtime                Pointer to the DIR_TIME structure.
//!
//! \return Status of the call.
//! \retval 0 If successful.
//! \retval Error 
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t filesetdate(uint8_t * FilePath, int32_t crt_mod_date_time_para, DIR_DATE * dirdate,
                           DIR_TIME * dirtime);

///////////////////////////////////////////////////////////////////////////////
//! \brief Gets directory attributes for a file based on the file handle.
//!
//! \param[in] HandleNumber File Handle.
//!
//! \return Returns directory attributes for a file or an error Code if an error occurs.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t filegetattribhandle(int32_t HandleNumber);

///////////////////////////////////////////////////////////////////////////////
//! \brief Gets directory attributes for a file.
//!
//! \param[in] FilePath Pointer to the file path.
//!
//! \return Returns directory attributes for a file or an error Code if an error occurs.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t filegetattrib(uint8_t * FilePath);

///////////////////////////////////////////////////////////////////////////////
//! \brief Sets directory attributes for a file.
//!
//! \param[in] HandleNumber TBD
//! \param[in] dirattribute TBD
//!
//! \return Status of the call.
//! \retval SUCCESS If call was successful.
//! \retval ERROR   If an error occurs.
///////////////////////////////////////////////////////////////////////////////
    RtStatus_t filesetattrib(int32_t HandleNumber, int32_t dirattribute);

///////////////////////////////////////////////////////////////////////////////
//! \brief Provides long file name.
//!
//! \param[in] HandleNumber TBD
//! \param[in] RecordNumber TBD
//! \param[in] LFNBuffer    Pointer to the file name buffer.
//!
//! \return Returns length of the long file name string.
///////////////////////////////////////////////////////////////////////////////
    int32_t ConstructLongFileName(int32_t HandleNumber, int32_t RecordNumber, int8_t * LFNBuffer);

#if defined(__cplusplus)
}                               // extern "C"
#endif                          // __cplusplus
#endif                          //_FS_API_H
///////////////////////////////////////////////////////////////////////////////// End of file/////////////////////////////////////////////////////////////////////////////////! @}
