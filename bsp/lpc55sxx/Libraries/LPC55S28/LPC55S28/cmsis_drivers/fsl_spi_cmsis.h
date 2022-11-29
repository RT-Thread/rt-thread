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

#ifndef _FSL_SPI_CMSIS_H_
#define _FSL_SPI_CMSIS_H_

#include "fsl_spi.h"
#include "RTE_Device.h"
#include "Driver_SPI.h"
#if defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT)
#include "fsl_spi_dma.h"
#endif

#if defined(SPI0) && defined(RTE_SPI0) && RTE_SPI0
extern ARM_DRIVER_SPI Driver_SPI0;
#endif /* SPI0 */

#if defined(SPI1) && defined(RTE_SPI1) && RTE_SPI1
extern ARM_DRIVER_SPI Driver_SPI1;
#endif /* SPI1 */

#if defined(SPI2) && defined(RTE_SPI2) && RTE_SPI2
extern ARM_DRIVER_SPI Driver_SPI2;
#endif /* SPI2 */

#if defined(SPI3) && defined(RTE_SPI3) && RTE_SPI3
extern ARM_DRIVER_SPI Driver_SPI3;
#endif /* SPI3 */

#if defined(SPI4) && defined(RTE_SPI4) && RTE_SPI4
extern ARM_DRIVER_SPI Driver_SPI4;
#endif /* SPI4 */

#if defined(SPI5) && defined(RTE_SPI5) && RTE_SPI5
extern ARM_DRIVER_SPI Driver_SPI5;
#endif /* SPI5 */

#if defined(SPI6) && defined(RTE_SPI6) && RTE_SPI6
extern ARM_DRIVER_SPI Driver_SPI6;
#endif /* SPI6 */

#if defined(SPI7) && defined(RTE_SPI7) && RTE_SPI7
extern ARM_DRIVER_SPI Driver_SPI7;
#endif /* SPI7 */

#if defined(SPI8) && defined(RTE_SPI8) && RTE_SPI8
extern ARM_DRIVER_SPI Driver_SPI8;
#endif /* SPI8 */

#if defined(SPI9) && defined(RTE_SPI9) && RTE_SPI9
extern ARM_DRIVER_SPI Driver_SPI9;
#endif /* SPI9 */

#if defined(SPI10) && defined(RTE_SPI10) && RTE_SPI10
extern ARM_DRIVER_SPI Driver_SPI10;
#endif /* SPI10 */

#if defined(SPI11) && defined(RTE_SPI11) && RTE_SPI11
extern ARM_DRIVER_SPI Driver_SPI11;
#endif /* SPI11 */

#if defined(SPI12) && defined(RTE_SPI12) && RTE_SPI12
extern ARM_DRIVER_SPI Driver_SPI12;
#endif /* SPI12 */

#if defined(SPI13) && defined(RTE_SPI13) && RTE_SPI13
extern ARM_DRIVER_SPI Driver_SPI13;
#endif /* SPI13 */

#define SPI_FLAG_UNINIT     (0UL)
#define SPI_FLAG_INIT       (1UL << 0)
#define SPI_FLAG_POWER      (1UL << 1)
#define SPI_FLAG_CONFIGURED (1UL << 2)
#define SPI_FLAG_MASTER     (1UL << 3)

#endif
