/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _FSL_EFUSE_H_
#define _FSL_EFUSE_H_

#include "fsl_flash.h"

/*!
 * @addtogroup efuse_driver
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name EFUSE APIs
 * @{
 */

/*!
 * @brief Initialize EFUSE controller.
 *
 * This function enables EFUSE Controller clock.
 *
 * @retval #kStatus_Success 0 Operation succeeded without error.
 * @retval #kStatus_Fail 1 The operation failed with a generic error.
 * @retval #kStatus_ReadOnly 2 Requested value cannot be changed because it is read-only.
 * @retval #kStatus_OutOfRange 3 Requested value is out of range.
 * @retval #kStatus_InvalidArgument 4 The requested command's argument is undefined.
 * @retval #kStatus_Timeout An invalid 5 A timeout occurred
 * @retval #kStatus_NoTransferInProgress 6 No send in progress.
 */
status_t EFUSE_Init(void);

/*!
 * @brief De-Initialize EFUSE controller.
 *
 * This functin disables EFUSE Controller Clock.
 *
 * @retval #kStatus_Success 0 Operation succeeded without error.
 * @retval #kStatus_Fail 1 The operation failed with a generic error.
 * @retval #kStatus_ReadOnly 2 Requested value cannot be changed because it is read-only.
 * @retval #kStatus_OutOfRange 3 Requested value is out of range.
 * @retval #kStatus_InvalidArgument 4 The requested command's argument is undefined.
 * @retval #kStatus_Timeout An invalid 5 A timeout occurred
 * @retval #kStatus_NoTransferInProgress 6 No send in progress.
 */
status_t EFUSE_Deinit(void);

/*!
 * @brief Read Fuse value from eFuse word.
 *
 * This function read fuse data from eFuse word to specified data buffer.
 *
 * @param addr Fuse address
 * @param data Buffer to hold the data read from eFuse word
 *
 * @retval #kStatus_Success 0 Operation succeeded without error.
 * @retval #kStatus_Fail 1 The operation failed with a generic error.
 * @retval #kStatus_ReadOnly 2 Requested value cannot be changed because it is read-only.
 * @retval #kStatus_OutOfRange 3 Requested value is out of range.
 * @retval #kStatus_InvalidArgument 4 The requested command's argument is undefined.
 * @retval #kStatus_Timeout An invalid 5 A timeout occurred
 * @retval #kStatus_NoTransferInProgress 6 No send in progress.
 */
status_t EFUSE_Read(uint32_t addr, uint32_t *data);

/*!
 * @brief Program value to eFuse block.
 *
 * This function program data to specified eFuse address.
 *
 * @param addr Fuse address
 * @param data data to be programmed into eFuse Fuse block
 *
 * @retval #kStatus_Success 0 Operation succeeded without error.
 * @retval #kStatus_Fail 1 The operation failed with a generic error.
 * @retval #kStatus_ReadOnly 2 Requested value cannot be changed because it is read-only.
 * @retval #kStatus_OutOfRange 3 Requested value is out of range.
 * @retval #kStatus_InvalidArgument 4 The requested command's argument is undefined.
 * @retval #kStatus_Timeout An invalid 5 A timeout occurred
 * @retval #kStatus_NoTransferInProgress 6 No send in progress.
 */
status_t EFUSE_Program(uint32_t addr, uint32_t data);

/*@}*/

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /*! _FSL_EFUSE_H_ */
