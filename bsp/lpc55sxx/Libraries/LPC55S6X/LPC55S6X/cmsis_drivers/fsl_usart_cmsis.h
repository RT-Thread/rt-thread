/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2017 NXP. Not a Contribution.
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

#ifndef _FSL_USART_CMSIS_H_
#define _FSL_USART_CMSIS_H_

#include "fsl_common.h"
#include "Driver_USART.h"
#include "RTE_Device.h"
#include "fsl_usart.h"
#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)
#include "fsl_usart_dma.h"
#endif

#if defined(USART0) && defined(RTE_USART0) && RTE_USART0
extern ARM_DRIVER_USART Driver_USART0;
#endif /* USART0 */

#if defined(USART1) && defined(RTE_USART1) && RTE_USART1
extern ARM_DRIVER_USART Driver_USART1;
#endif /* USART1 */

#if defined(USART2) && defined(RTE_USART2) && RTE_USART2
extern ARM_DRIVER_USART Driver_USART2;
#endif /* USART2 */

#if defined(USART3) && defined(RTE_USART3) && RTE_USART3
extern ARM_DRIVER_USART Driver_USART3;
#endif /* USART3 */

#if defined(USART4) && defined(RTE_USART4) && RTE_USART4
extern ARM_DRIVER_USART Driver_USART4;
#endif /* USART4 */

#if defined(USART5) && defined(RTE_USART5) && RTE_USART5
extern ARM_DRIVER_USART Driver_USART5;
#endif /* USART5 */

#if defined(USART6) && defined(RTE_USART6) && RTE_USART6
extern ARM_DRIVER_USART Driver_USART6;
#endif /* USART6 */

#if defined(USART7) && defined(RTE_USART7) && RTE_USART7
extern ARM_DRIVER_USART Driver_USART7;
#endif /* USART7 */

#if defined(USART8) && defined(RTE_USART8) && RTE_USART8
extern ARM_DRIVER_USART Driver_USART8;
#endif /* USART8 */

#if defined(USART9) && defined(RTE_USART9) && RTE_USART9
extern ARM_DRIVER_USART Driver_USART9;
#endif /* USART9 */

#if defined(USART10) && defined(RTE_USART10) && RTE_USART10
extern ARM_DRIVER_USART Driver_USART10;
#endif /* USART10 */

#if defined(USART11) && defined(RTE_USART11) && RTE_USART11
extern ARM_DRIVER_USART Driver_USART11;
#endif /* USART11 */

#if defined(USART12) && defined(RTE_USART12) && RTE_USART12
extern ARM_DRIVER_USART Driver_USART12;
#endif /* USART12 */

#if defined(USART13) && defined(RTE_USART13) && RTE_USART13
extern ARM_DRIVER_USART Driver_USART13;
#endif /* USART13 */

/* USART Driver state flags */
#define USART_FLAG_UNINIT     (0UL)
#define USART_FLAG_INIT       (1UL << 0)
#define USART_FLAG_POWER      (1UL << 1)
#define USART_FLAG_CONFIGURED (1UL << 2)

#endif /* _FSL_USART_CMSIS_H_ */
