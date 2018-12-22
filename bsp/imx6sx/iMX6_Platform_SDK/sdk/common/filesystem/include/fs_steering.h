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
//! \addtogroup os_fat_steering
//! @ingroup os_fat
//! @{
// Copyright (c) 2004-2005 SigmaTel, Inc.
//
//! \file fs_steering.h
//! \brief Filesystem steering support
//! \version 1.0
//! \date June-2005
//! 
//! Prototypes, enumerations and defines for filesystem steering support.
//!                     
//! \see Implementations in fs_steering.c
//                     

#ifndef _FS_STEERING_H
#define _FS_STEERING_H

#include "filesystem/fsapi.h"
//#include "filesystem/resource/src/os_resource_internal.h"

// Minimum and maximum file handles for FAT file system
#define FAT_HANDLE_MIN      (0x00000000)
#define FAT_HANDLE_MAX      (0x000000FF)
// Minimum and maximum file handles for resource file system
#define RESOURCE_HANDLE_MIN (0x00000100)
#define RESOURCE_HANDLE_MAX (0x000001FF)
// Add more file system specific handle min and max values here when needed

//! Pointer to Fclose-type function
typedef RtStatus_t(*Fclose_t) (int32_t);

//! Pointer to Fread-type function
typedef RtStatus_t(*Fread_t) (int32_t, uint8_t *, int32_t);

//! Pointer to Fwrite-type function
typedef RtStatus_t(*Fwrite_t) (int32_t, uint8_t *, int32_t);

//! Pointer to Fseek-type function
typedef RtStatus_t(*Fseek_t) (int32_t, int32_t, int32_t);

//! Various filesystem types
typedef enum FsType {
    FS_TYPE_FAT = 0,
    FS_TYPE_RESOURCE = 1,
    // Add more file system types here when needed
    FS_TYPE_MAX
} FsType_t;

// Function to return the filesystem type enum based on the handle
FsType_t FileSystemType(int32_t handleNumber);

// Function to redirect Fclose
RtStatus_t Fclose(int32_t handleNumber);

// Function to redirect Fread
RtStatus_t Fread(int32_t handleNumber, uint8_t * pBuffer, int32_t numBytesToRead);

// Function to redirect Fwrite
RtStatus_t Fwrite(int32_t handleNumber, uint8_t * pBuffer, int32_t numBytesToWrite);

// Function to redirect Fseek
RtStatus_t Fseek(int32_t handleNumber, int32_t numBytesToSeek, int32_t seekPosition);

#endif // _FS_STEERING_H
//! @}
