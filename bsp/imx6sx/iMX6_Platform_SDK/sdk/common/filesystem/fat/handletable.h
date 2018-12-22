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
#ifndef _HANDLE_TABLE_H_

#define _HANDLE_TABLE_H_

#include <types.h>
#include "fstypes.h"

#define NUM_SEEKPOINTS_CACHED 10

// Propagate changes to this table to the appropriate structure in fstypes.h
// In this case, the HANDLEENTRYSIZE should be updated.

typedef struct {
    uint8_t HandleActive;
    int8_t Device;
    uint8_t Mode;
    int32_t StartingCluster;
    int32_t CurrentOffset;
    int32_t CurrentCluster;
    int32_t CurrentSector;
    int32_t BytePosInSector;
    uint8_t SectorPosInCluster;
    int32_t DirSector;
    int32_t diroffset;
    int32_t ErrorCode;
    int32_t FileSize;
    int32_t SeekPointsClusters[NUM_SEEKPOINTS_CACHED];
    int32_t SeekPointsClusterStep;  // the cluster step in the SeekPoint cluster buffer
    int32_t SeekPointsBaseFileSize; //The file size based to calculate SeekPointsClusterStep.
    // We need this because file size will change with mode "w+"

} HandleTable_t;

#endif // !_HANDLE_TABLE_H_
