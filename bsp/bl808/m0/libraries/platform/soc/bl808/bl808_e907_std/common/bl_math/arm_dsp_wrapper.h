/**
 * @file arm_dsp_wrapper.c
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

#ifndef __MY_MATH_F_H__
#define __MY_MATH_F_H__

#include "misc.h"
#include "math.h"

typedef float float32_t;

__INLINE__ float32_t arm_sqrt_f32(float32_t x)
{
    return sqrtf(x);
}

__INLINE__ float32_t arm_cos_f32(float32_t x)
{
    return cosf(x);
}

void arm_fill_f32(float32_t value, float32_t *pDst, uint32_t blockSize);

#endif