/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2017,2020,2021,2024-2025 NXP. Not a Contribution.
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

#ifndef FSL_LPSPI_CMSISI_H_
#define FSL_LPSPI_CMSISI_H_

#include "fsl_common.h"
#include "RTE_Device.h"
#include "Driver_SPI.h"
#include "fsl_lpspi.h"
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
#include "fsl_lpspi_edma.h"
#endif
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
#include "fsl_dmamux.h"
#endif

#if (defined(LPSPI0) || defined(LPSPI_0)) && defined(RTE_SPI0) && RTE_SPI0
extern ARM_DRIVER_SPI Driver_SPI0;
#endif /* LPSPI0 */

#if (defined(LPSPI1) || defined(LPSPI_1)) && defined(RTE_SPI1) && RTE_SPI1
extern ARM_DRIVER_SPI Driver_SPI1;
#endif /* LPSPI1 */

#if (defined(LPSPI2) || defined(LPSPI_2)) && defined(RTE_SPI2) && RTE_SPI2
extern ARM_DRIVER_SPI Driver_SPI2;
#endif /* LPSPI2 */

#if (defined(LPSPI3) || defined(LPSPI_3)) && defined(RTE_SPI3) && RTE_SPI3
extern ARM_DRIVER_SPI Driver_SPI3;
#endif /* LPSPI3 */

#if (defined(LPSPI4) || defined(LPSPI_4)) && defined(RTE_SPI4) && RTE_SPI4
extern ARM_DRIVER_SPI Driver_SPI4;
#endif /* LPSPI4 */

#if (defined(LPSPI5) || defined(LPSPI_5)) && defined(RTE_SPI5) && RTE_SPI5
extern ARM_DRIVER_SPI Driver_SPI5;
#endif /* LPSPI5 */

#if (defined(LPSPI6) || defined(LPSPI_6)) && defined(RTE_SPI6) && RTE_SPI6
extern ARM_DRIVER_SPI Driver_SPI6;
#endif /* LPSPI6 */

#if (defined(LPSPI7) || defined(LPSPI_7)) && defined(RTE_SPI7) && RTE_SPI7
extern ARM_DRIVER_SPI Driver_SPI7;
#endif /* LPSPI7 */

#if (defined(LPSPI8) || defined(LPSPI_8)) && defined(RTE_SPI8) && RTE_SPI8
extern ARM_DRIVER_SPI Driver_SPI8;
#endif /* LPSPI8 */

#if (defined(LPSPI9) || defined(LPSPI_9)) && defined(RTE_SPI9) && RTE_SPI9
extern ARM_DRIVER_SPI Driver_SPI9;
#endif /* LPSPI9 */

#if (defined(LPSPI10) || defined(LPSPI_10)) && defined(RTE_SPI10) && RTE_SPI10
extern ARM_DRIVER_SPI Driver_SPI10;
#endif /* LPSPI10 */

#if (defined(LPSPI11) || defined(LPSPI_11)) && defined(RTE_SPI11) && RTE_SPI11
extern ARM_DRIVER_SPI Driver_SPI11;
#endif /* LPSPI11 */

#if (defined(LPSPI12) || defined(LPSPI_12)) && defined(RTE_SPI12) && RTE_SPI12
extern ARM_DRIVER_SPI Driver_SPI12;
#endif /* LPSPI12 */

#if (defined(LPSPI13) || defined(LPSPI_13)) && defined(RTE_SPI13) && RTE_SPI13
extern ARM_DRIVER_SPI Driver_SPI13;
#endif /* LPSPI13 */

#if (defined(LPSPI14) || defined(LPSPI_14)) && defined(RTE_SPI14) && RTE_SPI14
extern ARM_DRIVER_SPI Driver_SPI14;
#endif /* LPSPI14 */

#if (defined(LPSPI15) || defined(LPSPI_15)) && defined(RTE_SPI15) && RTE_SPI15
extern ARM_DRIVER_SPI Driver_SPI15;
#endif /* LPSPI15 */

#if (defined(LPSPI16) || defined(LPSPI_16)) && defined(RTE_SPI16) && RTE_SPI16
extern ARM_DRIVER_SPI Driver_SPI16;
#endif /* LPSPI16 */

#if (defined(LPSPI17) || defined(LPSPI_17)) && defined(RTE_SPI17) && RTE_SPI17
extern ARM_DRIVER_SPI Driver_SPI17;
#endif /* LPSPI17 */

#if (defined(LPSPI18) || defined(LPSPI_18)) && defined(RTE_SPI18) && RTE_SPI18
extern ARM_DRIVER_SPI Driver_SPI18;
#endif /* LPSPI18 */

#if (defined(LPSPI19) || defined(LPSPI_19)) && defined(RTE_SPI19) && RTE_SPI19
extern ARM_DRIVER_SPI Driver_SPI19;
#endif /* LPSPI19 */

#if (defined(LPSPI20) || defined(LPSPI_20)) && defined(RTE_SPI20) && RTE_SPI20
extern ARM_DRIVER_SPI Driver_SPI20;
#endif /* LPSPI20 */

/* SPI Driver state flags */
#define SPI_FLAG_UNINIT     (0UL)
#define SPI_FLAG_INIT       (1UL << 0)
#define SPI_FLAG_POWER      (1UL << 1)
#define SPI_FLAG_CONFIGURED (1UL << 2)

#endif
