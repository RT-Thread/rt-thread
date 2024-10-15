/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef FSL_FTFX_FEATURES_H
#define FSL_FTFX_FEATURES_H

#if (defined(BL_TARGET_FLASH) || defined(BL_TARGET_ROM) || defined(BL_TARGET_RAM))
#include <assert.h>
#include <string.h>
#include "fsl_device_registers.h"
#include "bootloader_common.h"
#else
#include "fsl_common.h"
#endif

#include "fsl_ftfx_adapter.h"

/*!
 * @addtogroup ftfx_feature
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @name FTFx configuration
 * @{
 */
/*! @brief Flash driver location. */
#if !defined(FTFx_DRIVER_IS_FLASH_RESIDENT)
#if (!defined(BL_TARGET_ROM) && !defined(BL_TARGET_RAM))
#define FTFx_DRIVER_IS_FLASH_RESIDENT 1U /*!< Used for the flash resident application. */
#else
#define FTFx_DRIVER_IS_FLASH_RESIDENT 0U /*!< Used for the non-flash resident application. */
#endif
#endif

/*! @brief Flash Driver Export option */
#if !defined(FTFx_DRIVER_IS_EXPORTED)
#if defined(BL_TARGET_ROM)
#define FTFx_DRIVER_IS_EXPORTED 1U /*!< Used for the ROM bootloader. */
#else
#define FTFx_DRIVER_IS_EXPORTED 0U /*!< Used for the MCUXpresso SDK application. */
#endif
#endif
/*! @} */

/*! @brief Indicates whether the secondary flash is supported in the Flash driver */
#if defined(FSL_FEATURE_FLASH_HAS_MULTIPLE_FLASH) || defined(FSL_FEATURE_FLASH_PFLASH_1_START_ADDRESS)
#define FTFx_DRIVER_HAS_FLASH1_SUPPORT (1U)
#define FTFx_FLASH_COUNT               (2U)
#else
#define FTFx_DRIVER_HAS_FLASH1_SUPPORT (0U)
#define FTFx_FLASH_COUNT               (1U)
#endif

/*!
 * @name Secondary flash configuration
 * @{
 */
/*! @brief Indicates whether the secondary flash has its own protection register in flash module. */
#if defined(FSL_FEATURE_FLASH_HAS_MULTIPLE_FLASH) && defined(FTFE_FPROTS_PROTS_MASK)
#define FTFx_FLASH1_HAS_PROT_CONTROL (1U)
#else
#define FTFx_FLASH1_HAS_PROT_CONTROL (0U)
#endif

/*! @brief Indicates whether the secondary flash has its own Execute-Only access register in flash module. */
#if defined(FSL_FEATURE_FLASH_HAS_MULTIPLE_FLASH) && defined(FTFE_FACSSS_SGSIZE_S_MASK)
#define FTFx_FLASH1_HAS_XACC_CONTROL (1U)
#else
#define FTFx_FLASH1_HAS_XACC_CONTROL (0U)
#endif
/*! @} */

#if FTFx_FLASH1_HAS_XACC_CONTROL || FTFx_FLASH1_HAS_PROT_CONTROL
#define FTFx_FLASH1_IS_INDEPENDENT_BLOCK (1U)
#else
#define FTFx_FLASH1_IS_INDEPENDENT_BLOCK (0U)
#endif

/*! @}*/

#endif /* FSL_FTFX_FEATURES_H */
