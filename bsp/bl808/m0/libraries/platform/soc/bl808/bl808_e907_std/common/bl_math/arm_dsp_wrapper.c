/**
 * @file arm_dsp_wrapper.h
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */

#include "arm_dsp_wrapper.h"

void arm_fill_f32(float32_t value, float32_t *pDst, uint32_t blockSize)
{
    uint32_t blkCnt = blockSize >> 2u;

    float32_t in1 = value;
    float32_t in2 = value;
    float32_t in3 = value;
    float32_t in4 = value;

    while (blkCnt > 0u) {
        *pDst++ = in1;
        *pDst++ = in2;
        *pDst++ = in3;
        *pDst++ = in4;

        blkCnt--;
    }

    blkCnt = blockSize % 0x4u;

    while (blkCnt > 0u) {
        *pDst++ = value;
        blkCnt--;
    }
}
