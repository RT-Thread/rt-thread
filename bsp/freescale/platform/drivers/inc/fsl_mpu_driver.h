/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
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
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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
#ifndef __FSL_MPU_DRIVER_H__
#define __FSL_MPU_DRIVER_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_mpu_hal.h"
#if FSL_FEATURE_SOC_MPU_COUNT

/*! 
 * @addtogroup mpu_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief Table of base addresses for MPU instances. */
extern MPU_Type * const g_mpuBase[];

 /*! @brief Table to save MPU IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_mpuIrqId[MPU_INSTANCE_COUNT];

/*! 
 * @brief Data The section describes the programming interface of the for MPU region initialization.
 *
 * This structure is used when calling the MPU_DRV_Init function.
 * 
 */
typedef struct MpuUserConfig{
    mpu_region_config_t  regionConfig;  /*!< region access permission      */
    struct MpuUserConfig *next;         /*!< pointer to the next structure */
}mpu_user_config_t;

/*!
 * @brief MPU driver user callback function.
 *
 * The contents of this structure provides a callback function.
 */

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! 
 * @name MPU Driver
 * @{
 */

  
/*!
 * @brief Initializes the MPU driver.
 *
 * @param instance The MPU peripheral instance number.
 * @param userConfigPtr The pointer to the MPU user configure structure, see #mpu_user_config_t.
 * @param userStatePtr The pointer of run time structure.
 * @return kStatus_MPU_Success means success. Otherwise, means failure.
 */
 mpu_status_t MPU_DRV_Init(uint32_t instance, const mpu_user_config_t *userConfigPtr);

/*!
 * @brief Deinitializes the MPU region.
 *
 * @param instance The MPU peripheral instance number.  
 */
void MPU_DRV_Deinit(uint32_t instance);

/*!
 * @brief Configures the MPU region.
 *
 * @param instance The MPU peripheral instance number.
 * @param regionConfigPtr The pointer to the MPU user configure structure, see #mpu_region_config_t.
 * @return kStatus_MPU_Success means success. Otherwise, means failure.
 */
mpu_status_t MPU_DRV_SetRegionConfig(uint32_t instance, const mpu_region_config_t *regionConfigPtr);

/*!
 * @brief Sets the region start address.
 *
 * @param instance The MPU peripheral instance number.
 * @param regionNum The region number.
 * @param startAddr Region start address.
 * @param endAddr Region end address.
 */
void MPU_DRV_SetRegionAddr(uint32_t instance, mpu_region_num_t regionNum, uint32_t startAddr, uint32_t endAddr);

/*!
 * @brief Configures the low master access permission.
 *
 * @param instance The MPU peripheral instance number.
 * @param regionNum The MPU region number.
 * @param masterNum The MPU master number.
 * @param accessRightsPtr A pointer to access permission structure.
 * @return kStatus_MPU_Success means success. Otherwise, means failure.
 */
mpu_status_t MPU_DRV_SetLowMasterAccessRights(uint32_t instance, mpu_region_num_t regionNum, mpu_master_t masterNum, const mpu_low_masters_access_rights_t *accessRightsPtr);

/*!
 * @brief Configures the high master access permission.
 *
 * @param instance The MPU peripheral instance number.
 * @param regionNum The MPU region number.
 * @param masterNum The MPU master number.
 * @param accessRightsPtr A pointer to access permission structure.
 * @return kStatus_MPU_Success means success. Otherwise, means failure.
 */
mpu_status_t MPU_DRV_SetHighMasterAccessRights(uint32_t instance, mpu_region_num_t regionNum, mpu_master_t masterNum, const mpu_high_masters_access_rights_t *accessRightsPtr);

 /*!
 * @brief Sets the MPU region valid.
 *
 * @param instance The MPU peripheral instance number.
 * @param regionNum MPU region number.
 * @param enable Enables or disables region.
 */
void MPU_DRV_SetRegionValidCmd(uint32_t instance, mpu_region_num_t regionNum, bool enable);

 /*!
 * @brief Gets the MPU access error detail information.
 *
 * @param instance The MPU peripheral instance number.
 * @param errInfoArrayPtr A pointer to access error info structure.
 * @return kStatus_MPU_Success means success. Otherwise, means failure.
 */
mpu_status_t MPU_DRV_GetDetailErrorAccessInfo(uint32_t instance,  mpu_access_err_info_t *errInfoArrayPtr);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_MPU_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/

