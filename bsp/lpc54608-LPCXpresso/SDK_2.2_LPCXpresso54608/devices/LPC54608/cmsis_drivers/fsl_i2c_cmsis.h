/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.

 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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

#ifndef _FSL_I2C_CMSIS_H_
#define _FSL_I2C_CMSIS_H_
#include "fsl_common.h"
#include "Driver_I2C.h"
#include "RTE_Device.h"
#include "fsl_i2c.h"
#include "fsl_flexcomm.h"
#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)
#include "fsl_i2c_dma.h"
#endif

#if defined(I2C0)
extern ARM_DRIVER_I2C Driver_I2C0;
#endif

#if defined(I2C1)
extern ARM_DRIVER_I2C Driver_I2C1;
#endif

#if defined(I2C2)
extern ARM_DRIVER_I2C Driver_I2C2;
#endif

#if defined(I2C3)
extern ARM_DRIVER_I2C Driver_I2C3;
#endif

#if defined(I2C4)
extern ARM_DRIVER_I2C Driver_I2C4;
#endif

#if defined(I2C5)
extern ARM_DRIVER_I2C Driver_I2C5;
#endif

#if defined(I2C6)
extern ARM_DRIVER_I2C Driver_I2C6;
#endif

#if defined(I2C7)
extern ARM_DRIVER_I2C Driver_I2C7;
#endif

#if defined(I2C8)
extern ARM_DRIVER_I2C Driver_I2C8;
#endif

#if defined(I2C9)
extern ARM_DRIVER_I2C Driver_I2C9;
#endif

#endif
