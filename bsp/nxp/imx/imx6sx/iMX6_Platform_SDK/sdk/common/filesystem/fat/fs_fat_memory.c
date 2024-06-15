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
//! \addtogroup os_fat_memory
//! @brief Memory for FAT32 filesystem.
//! @ingroup os_fat
//! @{
//!
//  Copyright (c) 2005-2007 SigmaTel, Inc.
//!
//! \file    fs_fat_memory.c
//! \brief   FAT file system module data definition.
//!
//! This file defines the global data objects used by the FAT file system.
//! It is included in the FAT library. If you need to override the default
//! definitions, add this file and your custom definitions to your 'Program'
//! project. For example, to change the number of devices to 4, add the
//! following lines to your project.
//!
//! \code
//! os\filesystem\fat\fs_fat_memory.c
//!    -DNUMDEVICES=4
//! \endcode
//!
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "fstypes.h"
#include "fat_internal.h"
#include "filespec.h"
#include "sectordef.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

// Include filesystem memory only if the number of filesystem devices is non-zero.
#if (NUMDEVICES > 0)

const int32_t maxcaches = NUMCACHES;
const int32_t maxdevices = NUMDEVICES;
const int32_t maxhandles = NUMHANDLES;
const uint8_t DriveLetter[] = DRIVELETTERS;

//! All other global, custom configurable data is in Y memory.
//! Two handles are reserved by the file system, so the number of handles must be more than 2
uint8_t bufy[NUMDEVICES * sizeof(FileSystemMediaTable_t) +
             NUMHANDLES * sizeof(HandleTable_t) +
             NUMHANDLES * sizeof(FileSpecs_t)] __attribute__ ((aligned(4)));

#endif //#if (NUMDEVICES > 0)

// eof fs_fat_memory.c
//! @}
