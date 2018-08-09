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




#ifndef _SSI_PAL_FILE_INT_H
#define _SSI_PAL_FILE_INT_H


#ifdef __cplusplus
extern "C"
{
#endif

#include "stdio.h"

/**
* @brief File Description:
*        This file contains wrapper functions for file related operations.
*/

/**** ----- Files General Definitions ----- ****/

/* Definitions for file modes */
#define SASI_PAL_MAX_SIZE_MODE            4
#define SASI_PAL_NUM_OF_SUPPORT_MODES     12

typedef char SaSiPalFileModeStr_t[SASI_PAL_MAX_SIZE_MODE];

typedef SaSiPalFileModeStr_t SaSiPalFileModesTable_t[SASI_PAL_NUM_OF_SUPPORT_MODES];

extern const SaSiPalFileModeStr_t SaSiPalFileModeTable[];
/**** ------------------------------------- ****/

//#define   _SaSiFile_t   FILE

/*----------------------------
      PUBLIC FUNCTIONS
-----------------------------------*/
/**
* @brief A wrapper for fopen functionality (to create a new file, the file is opened for read and
*        write).
*
*/
#define _SaSi_PalFileCreate(aFileName)   SaSi_PalFOpen(aFileName, SASI_PAL_WriteAndRead)

/**
* @brief A wrapper for fopen functionality. SaSiPalFileModeTable contains all possible modes
*        for fopen
*
*/
#define _SaSi_PalFOpen(aFileName, aFileMode)  ((SaSiFile_t)fopen(aFileName, SaSiPalFileModeTable[aFileMode]))

/**
 * @brief A wrapper for fclose functionality.
 *
 */
#define _SaSi_PalFClose(aFileHandle)    fclose((FILE*)aFileHandle)

/**
 * @brief A wrapper for fseek functionality
 *
 */
#define _SaSi_PalFSeek(aFileHandle, aOffset, aSeekOrigin)     fseek((FILE*)aFileHandle, aOffset, aSeekOrigin)

/**
 * @brief A wrapper for ftell functionality
 *
 */
#define _SaSi_PalFTell(aFileHandle)  ftell((FILE*)aFileHandle)

/**
* @brief A wrapper for fread functionality
*
*/
#define _SaSi_PalFRead(aFileHandle, aBuffer, aSize)  fread(aBuffer, 1, aSize, (FILE*)aFileHandle)

/**
* @brief A wrapper for fwrite functionality
*
*/
#define _SaSi_PalFWrite(aFileHandle, aBuffer, aSize)  fwrite(aBuffer, 1, aSize, (FILE*)aFileHandle)
/**
 * @brief A wrapper for fflush functionality
 *
 */
#define _SaSi_PalFFlush(aFileHandle)    fflush((FILE*)aFileHandle)


#ifdef __cplusplus
}
#endif

#endif


