/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2017,2020,2021 NXP. Not a Contribution.
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

#ifndef _FSL_LPUART_CMSIS_H_
#define _FSL_LPUART_CMSIS_H_

#include "fsl_common.h"
#include "Driver_USART.h"
#include "RTE_Device.h"
#include "fsl_lpuart.h"
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
#include "fsl_dmamux.h"
#endif
#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)
#include "fsl_lpuart_dma.h"
#endif
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
#include "fsl_lpuart_edma.h"
#endif

#if defined(LPUART0) && defined(RTE_USART0) && RTE_USART0
extern ARM_DRIVER_USART Driver_USART0;
#endif /* LPUART0 */

#if defined(LPUART1) && defined(RTE_USART1) && RTE_USART1
extern ARM_DRIVER_USART Driver_USART1;
#endif /* LPUART1 */

#if defined(LPUART2) && defined(RTE_USART2) && RTE_USART2
extern ARM_DRIVER_USART Driver_USART2;
#endif /* LPUART2 */

#if defined(LPUART3) && defined(RTE_USART3) && RTE_USART3
extern ARM_DRIVER_USART Driver_USART3;
#endif /* LPUART3 */

#if defined(LPUART4) && defined(RTE_USART4) && RTE_USART4
extern ARM_DRIVER_USART Driver_USART4;
#endif /* LPUART4 */

#if defined(LPUART5) && defined(RTE_USART5) && RTE_USART5
extern ARM_DRIVER_USART Driver_USART5;
#endif /* LPUART5 */

#if defined(LPUART6) && defined(RTE_USART6) && RTE_USART6
extern ARM_DRIVER_USART Driver_USART6;
#endif /* LPUART6 */

#if defined(LPUART7) && defined(RTE_USART7) && RTE_USART7
extern ARM_DRIVER_USART Driver_USART7;
#endif /* LPUART7 */

#if defined(LPUART8) && defined(RTE_USART8) && RTE_USART8
extern ARM_DRIVER_USART Driver_USART8;
#endif /* LPUART8 */

#if defined(LPUART9) && defined(RTE_USART9) && RTE_USART9
extern ARM_DRIVER_USART Driver_USART9;
#endif /* LPUART9 */

#if defined(LPUART10) && defined(RTE_USART10) && RTE_USART10
extern ARM_DRIVER_USART Driver_USART10;
#endif /* LPUART10 */

#if defined(LPUART11) && defined(RTE_USART11) && RTE_USART11
extern ARM_DRIVER_USART Driver_USART11;
#endif /* LPUART11 */

#if defined(LPUART12) && defined(RTE_USART12) && RTE_USART12
extern ARM_DRIVER_USART Driver_USART12;
#endif /* LPUART12 */

#if (FSL_FEATURE_SOC_LPUART_COUNT == 1) && (FSL_FEATURE_SOC_UART_COUNT == 3)
extern ARM_DRIVER_USART Driver_USART3;
#endif

#if (FSL_FEATURE_SOC_LPUART_COUNT == 1) && (FSL_FEATURE_SOC_UART_COUNT == 4)
extern ARM_DRIVER_USART Driver_USART4;
#endif

#if (FSL_FEATURE_SOC_LPUART_COUNT == 1) && (FSL_FEATURE_SOC_UART_COUNT == 5)
extern ARM_DRIVER_USART Driver_USART5;
#endif

/* USART Driver state flags */
#define USART_FLAG_UNINIT     (0UL)
#define USART_FLAG_INIT       (1UL << 0)
#define USART_FLAG_POWER      (1UL << 1)
#define USART_FLAG_CONFIGURED (1UL << 2)

#endif /* _FSL_LPUART_CMSIS_H_ */
