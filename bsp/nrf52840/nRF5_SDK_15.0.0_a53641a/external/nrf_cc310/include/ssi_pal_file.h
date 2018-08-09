/**************************************************************************************
* Copyright (c) 2016-2017, ARM Limited or its affiliates. All rights reserved         *
*                                                                                     *
* This file and the related binary are licensed under the following license:          *
*                                                                                     *
* ARM Object Code and Header Files License, v1.0 Redistribution.                      *
*                                                                                     *
* Redistribution and use of object code, header files, and documentation, without     *
* modification, are permitted provided that the following conditions are met:         *
*                                                                                     *
* 1) Redistributions must reproduce the above copyright notice and the                *
*    following disclaimer in the documentation and/or other materials                 *
*    provided with the distribution.                                                  *
*                                                                                     *
* 2) Unless to the extent explicitly permitted by law, no reverse                     *
*    engineering, decompilation, or disassembly of is permitted.                      *
*                                                                                     *
* 3) Redistribution and use is permitted solely for the purpose of                    *
*    developing or executing applications that are targeted for use                   *
*    on an ARM-based product.                                                         *
*                                                                                     *
* DISCLAIMER. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND                  *
* CONTRIBUTORS "AS IS." ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT             *
* NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT,        *
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          *
* COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED            *
* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR              *
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF              *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING                *
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS                  *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                        *
**************************************************************************************/



#ifndef _SSI_PAL_FILE_H
#define _SSI_PAL_FILE_H


#ifdef __cplusplus
extern "C"
{
#endif

#include "ssi_pal_types.h"
#include "ssi_pal_file_plat.h"
/**
* @brief File Description:
*        This file contains functions for file related operations. The functions implementations
*        are generally just wrappers to different operating system calls.
*        None of the described functions will check the input parameters so the behavior
*        of the APIs in illegal parameters case is dependent on the operating system behavior.
*
*/

/**** ----- Files General Definitions ----- ****/
typedef enum
{
    SASI_PAL_Read   =               0,   /* "r", read only */
    SASI_PAL_ReadAndWrite     =     1,   /* "r+", read and write */
    SASI_PAL_Write  =               2,   /* "w", write only */
    SASI_PAL_WriteAndRead =         3,   /* "w+", write and read */
    SASI_PAL_Append =               4,   /* "a", append to the end of file */
    SASI_PAL_AppendAndRead  =       5,   /* "a+", append (to the end of file) and read */
    SASI_PAL_ReadBinary     =       6,   /* "rb", read binary  */
    SASI_PAL_ReadAndWriteBinary =   7,   /* "r+b" read and write binary */
    SASI_PAL_WriteBinary  =         8,   /* "wb" write binary */
    SASI_PAL_WriteAndReadBinary =   9,   /* "w+b" write and read binary */
    SASI_PAL_AppendBinary =         10,   /* "ab" append binary */
    SASI_PAL_AppendAndReadBinary  = 11,    /* "a+b" append and read binary */

    SASI_PAL_DummyMode  = 0x7FFFFFFF

}SaSi_PalFileMode_t;

/* Definitions for SEEK positions */

#define SASI_PAL_SEEK_START 0     /* Seek from start of file */
#define SASI_PAL_SEEK_CUR   1     /* Seek from current position */
#define SASI_PAL_SEEK_END   2     /* Seek from end of file */

/* Definition for DxFile */
typedef struct _SaSiFile_t*  SaSiFile_t;
/**** ------------------------------------- ****/


/*----------------------------
      PUBLIC FUNCTIONS
-----------------------------------*/

/**
 * @brief This function purpose is to create a new file. The function will delete a file
 *        If it is already exist.
 *
 *
 * @param[in] aFileName - The file name to create
 *
 * @return The function returns a FILE handle to the opened file, in case of failure
 *         the function will return NULL
 */
SaSiFile_t SaSi_PalFileCreate(  char *aFileName  );

/* Definition for SaSi_PalFileCreate */
#define SaSi_PalFileCreate(aFileName)   _SaSi_PalFileCreate(aFileName)
/**
 * @brief This function purpose is to create a new file. The function will delete a file
 *        If it is already exist.
 *
 *
 * @param[in] aFileName - The file name to open
 * @param[in] aFileMode - The mode to open the file
 *
 * @return The function returns a FILE handle to the opened file, in case of failure
 *         the function will return NULL
 */
SaSiFile_t SaSi_PalFOpen(   char *aFileName, SaSi_PalFileMode_t aFileMode  );

/* Definition for fopen */
#define SaSi_PalFOpen(aFileName, aFileMode)      _SaSi_PalFOpen(aFileName, aFileMode)
/**
 * @brief This function purpose is to close a file (pointed by aFileHandle), The function
 *        will dissociate the file from the handle.
 *
 *
 * @param[in] aFileHandle - The file name to create
 *
 * @return The return values is according to operating system return values.
 */
SaSiError_t SaSi_PalFClose( SaSiFile_t aFileHandle  );

/* Definition for fclose */
#define SaSi_PalFClose(aFileHandle)   _SaSi_PalFClose(aFileHandle)

/**
 * @brief This function purpose is to change the file pointer position according to aOffset
 *
 *
 * @param[in] aFileHandle - The file handle
 * @param[in] aOffset - offset to move the file pointer inside the file
 * @param[in] aSeekOrigin - seek origin (current, end or start) to move aOffset from
 *
 * @return The return values is according to operating system return values.
 */
SaSiError_t SaSi_PalFSeek(  SaSiFile_t aFileHandle, int32_t aOffset, uint8_t aSeekOrigin );

/* Definition for fseek */
#define SaSi_PalFSeek(aFileHandle ,aOffset, aSeekOrigin)    _SaSi_PalFSeek(aFileHandle, aOffset, aSeekOrigin)

/**
 * @brief This function purpose is to return the file pointer position
 *
 *
 * @param[in] aFileHandle - The file handle
 *
 * @return The file pointer position
 */
uint32_t SaSi_PalFTell( SaSiFile_t aFileHandle );

/* definition for SaSi_PalFTell */
#define SaSi_PalFTell(aFileHandle)  _SaSi_PalFTell(aFileHandle)

/**
 * @brief This function purpose is to read aSize of bytes from the file and write it
 *        to aBuffer. In case EOF reached before aSize is read the returned size is smaller
 *        than aSize.
 *
 *
 * @param[in] aFileHandle - The file handle
 * @param[in] aBuffer - Pointer to buffer to read the data into
 * @param[in] aSize - Number of bytes to read from file
 *
 * @return The number of bytes read from the file
 */
uint32_t SaSi_PalFRead(SaSiFile_t aFileHandle, void *aBuffer, uint32_t aSize );

/* Definition for fread */
#define SaSi_PalFRead(aFileHandle, aBuffer, aSize)   _SaSi_PalFRead(aFileHandle, aBuffer, aSize)
/**
 * @brief This function purpose is to write aSize bytes from aBuffer to the file pointed
 *        by aFileHandle.
 *
 *
 * @param[in] aFileHandle - The file handle
 * @param[in] aBuffer - Pointer to buffer to read the data into
 * @param[in] aSize - Number of bytes to read from file
 *
 * @return The number of bytes written to the file
 */
uint32_t SaSi_PalFWrite(    SaSiFile_t aFileHandle, const void *aBuffer, uint32_t aSize );

#define SaSi_PalFWrite(aFileHandle, aBuffer, aSize)  _SaSi_PalFWrite(aFileHandle, aBuffer, aSize)
/**
 * @brief This function purpose is to save all buffered data to disk
 *
 *
 * @param[in] aFileHandle - The file handle
 *
 * @return The return values is according to operating system return values.
 */
SaSiError_t SaSi_PalFFlush( SaSiFile_t aFileHandle  );

/* Definition for fflush */
#define SaSi_PalFFlush(aFileHandle)   _SaSi_PalFFlush(aFileHandle)

/**
 * @brief This function purpose is to return the file size
 *
 *
 * @param[in] aFileHandle - The file handle
 * @param[out] aFileSize - The returned file size
 *
 * @return The function will return SASI_SUCCESS in case of success, else errors from
 *         ssi_pal_error.h is returned.
 */
SaSiError_t SaSi_PalFGetFileSize(   SaSiFile_t aFileHandle, uint32_t *aFileSize  );


#ifdef __cplusplus
}
#endif

#endif


