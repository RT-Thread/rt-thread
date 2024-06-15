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

#ifndef DEVICETABLE_H
#define DEVICETABLE_H

#include <types.h>
#include "fstypes.h"

//! \brief Structure to hold parameters from the BPB
//!
//! Media that contains a filesystem contains a BIOS Parameter Block (BPB).
//! This structure captures parameters from that BPB, and other values
//! that are computed based on the BPB.
typedef struct {
    /* *******************************************************************
       BPB variables
       ******************************************************************* */

    // BPB-mandated    Microsoft
    // size            Name
    // -------         ------
    int32_t BytesPerSector;     // 2               BPB_BytsPerSec    
    uint8_t SectorsPerCluster;  // 1               BPB_SecPerClus
    uint16_t RsvdSectors;       // 2               BPB_RsvdSecCnt
    uint8_t NoOfFATs;           // 1               BPB_NumFATs
    int32_t MaxRootDirEntries;  // 2               BPB_RootEntCnt   =0 for FAT32.  Nom. =512 for FAT16.
    int32_t TotalSectors;       // 2 (FAT16)       BPB_TotSec16
    // or 4 (FAT32)    BPB_TotSec32
    int32_t FATSize;            // 2 (FAT16)       BPB_FATSz16    size units: sectors
    // or 4 (FAT32)    BPB_FATSz32
    int32_t RootdirCluster;     // 4               BPB_RootClus
    //int32_t  FSInfoSector;  
    //int32_t  BkBootSector;  

    /* *******************************************************************
       Derived variables
       ******************************************************************* */

    int32_t NextFreeCluster;
    int32_t TotalFreeClusters;
    uint16_t RootDirSectors;    // Qty of sectors needed to hold the root directory.
    int32_t FIRSTDataSector;
    uint8_t FATType;
    int32_t TotalNoofclusters;
    int32_t ClusterMask;
    int32_t ClusterShift;
    int32_t SectorShift;        // Index of the MSB of the value in BytesPerSector.
    int32_t SectorMask;         // Mask of all bits up to SectorShift.
    uint8_t DevicePresent;
    int32_t FirRootdirsec;
    int32_t FSInfoSector;
} FileSystemMediaTable_t;

#endif /* #ifndef DEVICETABLE_H */
