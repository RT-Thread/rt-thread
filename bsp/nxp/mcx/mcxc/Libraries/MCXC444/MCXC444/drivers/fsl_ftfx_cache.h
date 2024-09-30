/*
 * Copyright 2013-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef FSL_FTFX_CACHE_H
#define FSL_FTFX_CACHE_H

#include "fsl_ftfx_controller.h"

/*!
 * @addtogroup ftfx_cache_driver
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief FTFx prefetch speculation status.
 */
typedef struct _flash_prefetch_speculation_status
{
    bool instructionOff; /*!< Instruction speculation.*/
    bool dataOff;        /*!< Data speculation.*/
} ftfx_prefetch_speculation_status_t;

/*!
 * @brief Constants for execute-in-RAM flash function.
 */
enum _ftfx_cache_ram_func_constants
{
    kFTFx_CACHE_RamFuncMaxSizeInWords = 16U, /*!< The maximum size of execute-in-RAM function.*/
};

typedef union
{
    uint32_t commadAddr;
    void (*callFlashCommand)(FTFx_REG32_ACCESS_TYPE base, uint32_t bitMask, uint32_t bitShift, uint32_t bitValue);
} function_bit_operation_ptr_t;

/*! @brief FTFx cache driver state information.
 *
 * An instance of this structure is allocated by the user of the flash driver and
 * passed into each of the driver APIs.
 */
typedef struct _ftfx_cache_config
{
    uint8_t flashMemoryIndex; /*!< 0 - primary flash; 1 - secondary flash*/
    uint8_t reserved[3];
    function_bit_operation_ptr_t bitOperFuncAddr; /*!< An buffer point to the flash execute-in-RAM function. */
} ftfx_cache_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the global FTFx cache structure members.
 *
 * This function checks and initializes the Flash module for the other FTFx cache APIs.
 *
 * @param config Pointer to the storage for the driver runtime state.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully.
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 */
status_t FTFx_CACHE_Init(ftfx_cache_config_t *config);

/*!
 * @brief Process the cache/prefetch/speculation to the flash.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param isPreProcess The possible option used to control flash cache/prefetch/speculation
 * @retval #kStatus_FTFx_Success API was executed successfully.
 * @retval #kStatus_FTFx_InvalidArgument Invalid argument is provided.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 */
status_t FTFx_CACHE_ClearCachePrefetchSpeculation(ftfx_cache_config_t *config, bool isPreProcess);

/*!
 * @brief Sets the PFlash prefetch speculation to the intended speculation status.
 *
 * @param speculationStatus The expected protect status to set to the PFlash protection register. Each bit is
 * @retval #kStatus_FTFx_Success API was executed successfully.
 * @retval #kStatus_FTFx_InvalidSpeculationOption An invalid speculation option argument is provided.
 */
status_t FTFx_CACHE_PflashSetPrefetchSpeculation(ftfx_prefetch_speculation_status_t *speculationStatus);

/*!
 * @brief Gets the PFlash prefetch speculation status.
 *
 * @param speculationStatus  Speculation status returned by the PFlash IP.
 * @retval #kStatus_FTFx_Success API was executed successfully.
 */
status_t FTFx_CACHE_PflashGetPrefetchSpeculation(ftfx_prefetch_speculation_status_t *speculationStatus);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FTFX_CACHE_H */
