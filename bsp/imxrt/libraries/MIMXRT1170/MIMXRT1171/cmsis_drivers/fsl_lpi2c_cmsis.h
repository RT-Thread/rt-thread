/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2017,2020,2024-2025 NXP. Not a Contribution.
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

#ifndef FSL_LPI2C_CMSIS_H_
#define FSL_LPI2C_CMSIS_H_

#include "fsl_common.h"
#include "Driver_I2C.h"
#include "RTE_Device.h"
#include "fsl_lpi2c.h"
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
#include "fsl_dmamux.h"
#endif
#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)
#include "fsl_lpi2c_dma.h"
#endif
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
#include "fsl_lpi2c_edma.h"
#endif

#if (defined(LPI2C0) || defined(LPI2C_0)) && defined(RTE_I2C0) && RTE_I2C0
extern ARM_DRIVER_I2C Driver_I2C0;
#endif /* LPI2C0 */

#if (defined(LPI2C1) || defined(LPI2C_1)) && defined(RTE_I2C1) && RTE_I2C1
extern ARM_DRIVER_I2C Driver_I2C1;
#endif /* LPI2C1 */

#if (defined(LPI2C2) || defined(LPI2C_2)) && defined(RTE_I2C2) && RTE_I2C2
extern ARM_DRIVER_I2C Driver_I2C2;
#endif /* LPI2C2 */

#if (defined(LPI2C3) || defined(LPI2C_3)) && defined(RTE_I2C3) && RTE_I2C3
extern ARM_DRIVER_I2C Driver_I2C3;
#endif /* LPI2C3 */

#if (defined(LPI2C4) || defined(LPI2C_4)) && defined(RTE_I2C4) && RTE_I2C4
extern ARM_DRIVER_I2C Driver_I2C4;
#endif /* LPI2C4 */

#if (defined(LPI2C5) || defined(LPI2C_5)) && defined(RTE_I2C5) && RTE_I2C5
extern ARM_DRIVER_I2C Driver_I2C5;
#endif /* LPI2C5 */

#if (defined(LPI2C6) || defined(LPI2C_6)) && defined(RTE_I2C6) && RTE_I2C6
extern ARM_DRIVER_I2C Driver_I2C6;
#endif /* LPI2C6 */

#if (defined(LPI2C7) || defined(LPI2C_7)) && defined(RTE_I2C7) && RTE_I2C7
extern ARM_DRIVER_I2C Driver_I2C7;
#endif /* LPI2C7 */

#if (defined(LPI2C8) || defined(LPI2C_8)) && defined(RTE_I2C8) && RTE_I2C8
extern ARM_DRIVER_I2C Driver_I2C8;
#endif /* LPI2C8 */

#if (defined(LPI2C9) || defined(LPI2C_9)) && defined(RTE_I2C9) && RTE_I2C9
extern ARM_DRIVER_I2C Driver_I2C9;
#endif /* LPI2C9 */

#if (defined(LPI2C10) || defined(LPI2C_10)) && defined(RTE_I2C10) && RTE_I2C10
extern ARM_DRIVER_I2C Driver_I2C10;
#endif /* LPI2C10 */

#if (defined(LPI2C11) || defined(LPI2C_11)) && defined(RTE_I2C11) && RTE_I2C11
extern ARM_DRIVER_I2C Driver_I2C11;
#endif /* LPI2C11 */

#if (defined(LPI2C12) || defined(LPI2C_12)) && defined(RTE_I2C12) && RTE_I2C12
extern ARM_DRIVER_I2C Driver_I2C12;
#endif /* LPI2C12 */

#if (defined(LPI2C13) || defined(LPI2C_13)) && defined(RTE_I2C13) && RTE_I2C13
extern ARM_DRIVER_I2C Driver_I2C13;
#endif /* LPI2C13 */

#if (defined(LPI2C14) || defined(LPI2C_14)) && defined(RTE_I2C14) && RTE_I2C14
extern ARM_DRIVER_I2C Driver_I2C14;
#endif /* LPI2C14 */

#if (defined(LPI2C15) || defined(LPI2C_15)) && defined(RTE_I2C15) && RTE_I2C15
extern ARM_DRIVER_I2C Driver_I2C15;
#endif /* LPI2C15 */

#if (defined(LPI2C16) || defined(LPI2C_16)) && defined(RTE_I2C16) && RTE_I2C16
extern ARM_DRIVER_I2C Driver_I2C16;
#endif /* LPI2C16 */

#if (defined(LPI2C17) || defined(LPI2C_17)) && defined(RTE_I2C17) && RTE_I2C17
extern ARM_DRIVER_I2C Driver_I2C17;
#endif /* LPI2C17 */

#if (defined(LPI2C18) || defined(LPI2C_18)) && defined(RTE_I2C18) && RTE_I2C18
extern ARM_DRIVER_I2C Driver_I2C18;
#endif /* LPI2C18 */

#if (defined(LPI2C19) || defined(LPI2C_19)) && defined(RTE_I2C19) && RTE_I2C19
extern ARM_DRIVER_I2C Driver_I2C19;
#endif /* LPI2C19 */

#if (defined(LPI2C20) || defined(LPI2C_20)) && defined(RTE_I2C20) && RTE_I2C20
extern ARM_DRIVER_I2C Driver_I2C20;
#endif /* LPI2C20 */

/* I2C Driver state flags */
#define I2C_FLAG_UNINIT (0UL)
#define I2C_FLAG_INIT   (1UL << 0)
#define I2C_FLAG_POWER  (1UL << 1)

#endif /* FSL_LPI2C_CMSIS_H_ */
