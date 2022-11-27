/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2020 NXP. Not a Contribution.
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

#if defined(I2C0) && defined(RTE_I2C0) && RTE_I2C0
extern ARM_DRIVER_I2C Driver_I2C0;
#endif

#if defined(I2C1) && defined(RTE_I2C1) && RTE_I2C1
extern ARM_DRIVER_I2C Driver_I2C1;
#endif

#if defined(I2C2) && defined(RTE_I2C2) && RTE_I2C2
extern ARM_DRIVER_I2C Driver_I2C2;
#endif

#if defined(I2C3) && defined(RTE_I2C3) && RTE_I2C3
extern ARM_DRIVER_I2C Driver_I2C3;
#endif

#if defined(I2C4) && defined(RTE_I2C4) && RTE_I2C4
extern ARM_DRIVER_I2C Driver_I2C4;
#endif

#if defined(I2C5) && defined(RTE_I2C5) && RTE_I2C5
extern ARM_DRIVER_I2C Driver_I2C5;
#endif

#if defined(I2C6) && defined(RTE_I2C6) && RTE_I2C6
extern ARM_DRIVER_I2C Driver_I2C6;
#endif

#if defined(I2C7) && defined(RTE_I2C7) && RTE_I2C7
extern ARM_DRIVER_I2C Driver_I2C7;
#endif

#if defined(I2C8) && defined(RTE_I2C8) && RTE_I2C8
extern ARM_DRIVER_I2C Driver_I2C8;
#endif

#if defined(I2C9) && defined(RTE_I2C9) && RTE_I2C9
extern ARM_DRIVER_I2C Driver_I2C9;
#endif

#if defined(I2C10) && defined(RTE_I2C10) && RTE_I2C10
extern ARM_DRIVER_I2C Driver_I2C10;
#endif

#if defined(I2C11) && defined(RTE_I2C11) && RTE_I2C11
extern ARM_DRIVER_I2C Driver_I2C11;
#endif

#if defined(I2C12) && defined(RTE_I2C12) && RTE_I2C12
extern ARM_DRIVER_I2C Driver_I2C12;
#endif

#if defined(I2C13) && defined(RTE_I2C13) && RTE_I2C13
extern ARM_DRIVER_I2C Driver_I2C13;
#endif

/* I2C Driver state flags */
#define I2C_FLAG_UNINIT (0UL)
#define I2C_FLAG_INIT   (1UL << 0)
#define I2C_FLAG_POWER  (1UL << 1)

#endif
