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

#ifndef _FSL_LPSPI_CMSISI_H_
#define _FSL_LPSPI_CMSISI_H_

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

#if defined(LPSPI0) && defined(RTE_SPI0) && RTE_SPI0
extern ARM_DRIVER_SPI Driver_SPI0;
#endif /* LPSPI0 */

#if defined(LPSPI1) && defined(RTE_SPI1) && RTE_SPI1
extern ARM_DRIVER_SPI Driver_SPI1;
#endif /* LPSPI1 */

#if defined(LPSPI2) && defined(RTE_SPI2) && RTE_SPI2
extern ARM_DRIVER_SPI Driver_SPI2;
#endif /* LPSPI2 */

#if defined(LPSPI3) && defined(RTE_SPI3) && RTE_SPI3
extern ARM_DRIVER_SPI Driver_SPI3;
#endif /* LPSPI3 */

#if defined(LPSPI4) && defined(RTE_SPI4) && RTE_SPI4
extern ARM_DRIVER_SPI Driver_SPI4;
#endif /* LPSPI4 */

#if defined(LPSPI5) && defined(RTE_SPI5) && RTE_SPI5
extern ARM_DRIVER_SPI Driver_SPI5;
#endif /* LPSPI5 */

#if defined(LPSPI6) && defined(RTE_SPI6) && RTE_SPI6
extern ARM_DRIVER_SPI Driver_SPI6;
#endif /* LPSPI6 */

/* SPI Driver state flags */
#define SPI_FLAG_UNINIT     (0UL)
#define SPI_FLAG_INIT       (1UL << 0)
#define SPI_FLAG_POWER      (1UL << 1)
#define SPI_FLAG_CONFIGURED (1UL << 2)

#endif
