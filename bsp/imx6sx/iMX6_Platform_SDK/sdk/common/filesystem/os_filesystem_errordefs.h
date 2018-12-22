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

#ifndef _OS_FILESYSTEM_ERRORDEFS_H
#define _OS_FILESYSTEM_ERRORDEFS_H

#include "sdk_types.h"

///////////////////////////////////////////////////////////////////////////////
//! \addtogroup os_fat_errors
//! \ingroup os_fat
//! @{
//
// Copyright (c) 2004-2005 SigmaTel, Inc.
//
//! \file error.h
//! \brief  Contains error codes.
//!
//! \code
//! 0x00000000, 0xFFFFFFFF, and 0x8000000 - 0xAFFFFFFF reserved for Sigmatel
//! 0xB0000000 - 0xFFFFFFFE available for customer use
//! \endcode
//! 768 Major groups for Sigmatel, 1280 Major groups for customers\n
//! 256 Minor groups per Major group\n
//! 4096 errors per Minor group\n
//! \code
//! Bit            3322 2222 2222 1111 1111 11
//!                1098 7654 3210 9876 5432 1098 7654 3210
//!                ---------------------------------------
//! Major Groups:  ---- MMMM MMMM ---- ---- ---- ---- ----
//! Minor Groups:  ---- ---- ---- mmmm mmmm ---- ---- ----
//! Errors:        ---- ---- ---- ---- ---- eeee eeee eeee
//! \endcode
//!

#ifndef __LANGUAGE_ASM__
#ifndef RT_STATUS_T_DEFINED
#define RT_STATUS_T_DEFINED
typedef int32_t RtStatus_t;
#endif
#endif

//! @name Error mask
//@{
#define ERROR_MASK                      (-268435456)
//@}

//! @name Error groups
//@{
#define OS_GROUP                  (0x00300000)  //0x80300000
#define OS_FILESYSTEM_GROUP       (OS_GROUP|0x00005000)
#define ERROR_OS_FILESYSTEM_GROUP       (ERROR_MASK|OS_FILESYSTEM_GROUP)
//@}

//! @name Filesystem errors
//@{
#define ERROR_OS_FILESYSTEM_GENERAL                              (ERROR_OS_FILESYSTEM_GROUP)
#define ERROR_OS_FILESYSTEM_FILESYSTEM_NOT_FOUND                 (ERROR_OS_FILESYSTEM_GROUP + 1)
#define ERROR_OS_FILESYSTEM_HANDLE_NOT_ACTIVE                    (ERROR_OS_FILESYSTEM_GROUP + 2)
#define ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED                 (ERROR_OS_FILESYSTEM_GROUP + 3)
#define ERROR_OS_FILESYSTEM_NO_FREE_HANDLE                       (ERROR_OS_FILESYSTEM_GROUP + 4)
#define ERROR_OS_FILESYSTEM_FSEEK_FAILED                         (ERROR_OS_FILESYSTEM_GROUP + 5)
#define ERROR_OS_FILESYSTEM_INVALID_MODE                         (ERROR_OS_FILESYSTEM_GROUP + 6)
#define ERROR_OS_FILESYSTEM_NOSPACE_IN_ROOTDIRECTORY             (ERROR_OS_FILESYSTEM_GROUP + 7)
#define ERROR_OS_FILESYSTEM_EOF                                  (ERROR_OS_FILESYSTEM_GROUP + 8)
#define ERROR_OS_FILESYSTEM_SECTOR_FULL_OF_RECORD                (ERROR_OS_FILESYSTEM_GROUP + 9)
#define ERROR_OS_FILESYSTEM_NO_FREE_CLUSTER                      (ERROR_OS_FILESYSTEM_GROUP + 10)
#define ERROR_OS_FILESYSTEM_FILE_FOUND                           (ERROR_OS_FILESYSTEM_GROUP + 11)
#define ERROR_OS_FILESYSTEM_FILE_NOT_FOUND                       (ERROR_OS_FILESYSTEM_GROUP + 12)
#define ERROR_OS_FILESYSTEM_FILE_WRITE_FAILED                    (ERROR_OS_FILESYSTEM_GROUP + 13)
#define ERROR_OS_FILESYSTEM_DIRECTORY_IS_NOT_WRITABLE            (ERROR_OS_FILESYSTEM_GROUP + 14)
#define ERROR_OS_FILESYSTEM_CACHE_BUF_RELEASE_ERR                (ERROR_OS_FILESYSTEM_GROUP + 15)
#define ERROR_OS_FILESYSTEM_DIR_NOT_EMPTY                        (ERROR_OS_FILESYSTEM_GROUP + 16)
#define ERROR_OS_FILESYSTEM_FILE_OPEN                            (ERROR_OS_FILESYSTEM_GROUP + 17)
#define ERROR_OS_FILESYSTEM_FILE_DELETE_FAILED                   (ERROR_OS_FILESYSTEM_GROUP + 18)
#define ERROR_OS_FILESYSTEM_DUPLICATE_FILE_NAME                  (ERROR_OS_FILESYSTEM_GROUP + 19)
#define ERROR_OS_FILESYSTEM_INVALID_DIR_PATH                     (ERROR_OS_FILESYSTEM_GROUP + 20)
#define ERROR_OS_FILESYSTEM_CHANGEPATH_NOT_POSSIBLE              (ERROR_OS_FILESYSTEM_GROUP + 21)
#define ERROR_OS_FILESYSTEM_MAX_DEVICES_EXCEEDED                 (ERROR_OS_FILESYSTEM_GROUP + 22)
#define ERROR_OS_FILESYSTEM_MEDIA_TYPE_NOT_SUPPORTED             (ERROR_OS_FILESYSTEM_GROUP + 23)
#define ERROR_OS_FILESYSTEM_MODE_NOT_SUPPORTED                   (ERROR_OS_FILESYSTEM_GROUP + 24)
#define ERROR_OS_FILESYSTEM_INVALID_CLUSTER_NO                   (ERROR_OS_FILESYSTEM_GROUP + 25)
#define ERROR_OS_FILESYSTEM_CANNOT_DELETE_CWD                    (ERROR_OS_FILESYSTEM_GROUP + 26)
#define ERROR_OS_FILESYSTEM_CURRENT_WORK_DIR                     (ERROR_OS_FILESYSTEM_GROUP + 27)
#define ERROR_OS_FILESYSTEM_DIR_NOT_REMOVABLE                    (ERROR_OS_FILESYSTEM_GROUP + 28)
#define ERROR_OS_FILESYSTEM_INVALID_RECORD_NUMBER                (ERROR_OS_FILESYSTEM_GROUP + 29)
#define ERROR_OS_FILESYSTEM_LONG_FILE_NAME                       (ERROR_OS_FILESYSTEM_GROUP + 30)
#define ERROR_OS_FILESYSTEM_NO_MATCHING_RECORD                   (ERROR_OS_FILESYSTEM_GROUP + 31)
#define ERROR_OS_FILESYSTEM_NOT_VALID_SECTOR                     (ERROR_OS_FILESYSTEM_GROUP + 32)
#define ERROR_OS_FILESYSTEM_DEVICE_NOT_SUPPORTED                 (ERROR_OS_FILESYSTEM_GROUP + 33)
#define ERROR_OS_FILESYSTEM_FS_ERROR                             (ERROR_OS_FILESYSTEM_GROUP + 34)
#define ERROR_OS_FILESYSTEM_READSECTOR_FAIL                      (ERROR_OS_FILESYSTEM_GROUP + 35)
#define ERROR_OS_FILESYSTEM_DEVICE_NOT_ACTIVE                    (ERROR_OS_FILESYSTEM_GROUP + 36)
#define ERROR_OS_FILESYSTEM_ILLEGAL_FILENAME_CHARA               (ERROR_OS_FILESYSTEM_GROUP + 37)
#define ERROR_OS_FILESYSTEM_MEDIAREAD_FAILED                     (ERROR_OS_FILESYSTEM_GROUP + 38)
#define ERROR_OS_FILESYSTEM_MEDIAWRITE_FAILED                    (ERROR_OS_FILESYSTEM_GROUP + 39)
#define ERROR_OS_FILESYSTEM_CANNOT_OPEN_DIRECTORY                (ERROR_OS_FILESYSTEM_GROUP + 40)
#define ERROR_OS_FILESYSTEM_NO_STEERING_FUNCTION                 (ERROR_OS_FILESYSTEM_GROUP + 41)
#define ERROR_OS_FILESYSTEM_VOLUMELABEL_NOT_FOUND                (ERROR_OS_FILESYSTEM_GROUP + 42)
#define ERROR_OS_FILESYSTEM_RESOURCE_INIT_FAILED                 (ERROR_OS_FILESYSTEM_GROUP + 43)
#define ERROR_OS_FILESYSTEM_RESOURCE_INVALID_VALUE_PTR           (ERROR_OS_FILESYSTEM_GROUP + 44)
#define ERROR_OS_FILESYSTEM_RESOURCE_INVALID_HANDLE              (ERROR_OS_FILESYSTEM_GROUP + 45)
#define ERROR_OS_FILESYSTEM_RESOURCE_LOAD                        (ERROR_OS_FILESYSTEM_GROUP + 46)
#define ERROR_OS_FILESYSTEM_RESOURCE_TABLE_READ                  (ERROR_OS_FILESYSTEM_GROUP + 47)
#define ERROR_OS_FILESYSTEM_RESOURCE_SIZE_READ                   (ERROR_OS_FILESYSTEM_GROUP + 48)
#define ERROR_OS_FILESYSTEM_UNSUPPORTED_FS_TYPE                  (ERROR_OS_FILESYSTEM_GROUP + 49)
#define ERROR_OS_FILESYSTEM_MEMORY                               (ERROR_OS_FILESYSTEM_GROUP + 50)
#define ERROR_OS_FILESYSTEM_NOT_EOF                              (ERROR_OS_FILESYSTEM_GROUP + 51)
//@}

#endif //_OS_FILESYSTEM_ERRORDEFS_H
