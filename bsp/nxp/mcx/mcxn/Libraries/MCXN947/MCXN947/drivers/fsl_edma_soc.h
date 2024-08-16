/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_EDMA_SOC_H_
#define _FSL_EDMA_SOC_H_

#include "fsl_common.h"

/*!
 * @addtogroup edma_soc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief Driver version 1.0.0. */
#define FSL_EDMA_SOC_DRIVER_VERSION (MAKE_VERSION(1, 0, 0))
/*@}*/

/*!@brief DMA IP version */
#define FSL_EDMA_SOC_IP_DMA3 (1)
#define FSL_EDMA_SOC_IP_DMA4 (0)

/*!@brief DMA base table */
#define EDMA_BASE_PTRS \
    {                  \
        DMA0, DMA1     \
    }

#define EDMA_CHN_IRQS                                                                                               \
    {                                                                                                               \
        {EDMA_0_CH0_IRQn,  EDMA_0_CH1_IRQn,  EDMA_0_CH2_IRQn,  EDMA_0_CH3_IRQn, EDMA_0_CH4_IRQn,  EDMA_0_CH5_IRQn,  \
         EDMA_0_CH6_IRQn,  EDMA_0_CH7_IRQn,  EDMA_0_CH8_IRQn,  EDMA_0_CH9_IRQn, EDMA_0_CH10_IRQn, EDMA_0_CH11_IRQn, \
         EDMA_0_CH12_IRQn, EDMA_0_CH13_IRQn, EDMA_0_CH14_IRQn, EDMA_0_CH15_IRQn},                                   \
        {                                                                                                           \
            EDMA_1_CH0_IRQn, EDMA_1_CH1_IRQn, EDMA_1_CH2_IRQn, EDMA_1_CH3_IRQn, EDMA_1_CH4_IRQn, EDMA_1_CH5_IRQn,   \
                EDMA_1_CH6_IRQn, EDMA_1_CH7_IRQn, EDMA_1_CH8_IRQn, EDMA_1_CH9_IRQn, EDMA_1_CH10_IRQn,               \
                EDMA_1_CH11_IRQn, EDMA_1_CH12_IRQn, EDMA_1_CH13_IRQn, EDMA_1_CH14_IRQn, EDMA_1_CH15_IRQn            \
        }                                                                                                           \
    }

/*!@brief EDMA base address convert macro */
#define EDMA_CHANNEL_OFFSET           0x1000U
#define EDMA_CHANNEL_ARRAY_STEP(base) (0x1000U)

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _FSL_EDMA_SOC_H_ */
