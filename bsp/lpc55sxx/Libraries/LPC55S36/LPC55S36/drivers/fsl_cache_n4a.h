/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_CACHE_H_
#define _FSL_CACHE_H_

#include "fsl_common.h"

/*!
 * @addtogroup cache_lpcac
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief cache driver version */
#define FSL_CACHE_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name cache control for the L1 low power cache controller
 *@{
 */

/*!
 * @brief Enables the processor code bus cache.
 *
 */
static inline void L1CACHE_EnableCodeCache(void)
{
    SYSCON->LPCAC_CTRL &= ~SYSCON_LPCAC_CTRL_DIS_LPCAC_MASK;
}

/*!
 * @brief Disables the processor code bus cache.
 *
 */
static inline void L1CACHE_DisableCodeCache(void)
{
    SYSCON->LPCAC_CTRL |= SYSCON_LPCAC_CTRL_DIS_LPCAC_MASK;
}

/*!
 * @brief  Clears cache.
 *
 */
static inline void L1CACHE_InvalidateCodeCache(void)
{
    SYSCON->LPCAC_CTRL &= ~SYSCON_LPCAC_CTRL_CLR_LPCAC_MASK;
}

/*!
 * @brief Enables allocation.
 *
 */
static inline void L1CACHE_EnableAllocation(void)
{
    SYSCON->LPCAC_CTRL &= ~SYSCON_LPCAC_CTRL_FRC_NO_ALLOC_MASK;
}

/*!
 * @brief Disables allocation.
 *
 */
static inline void L1CACHE_DisableAllocation(void)
{
    SYSCON->LPCAC_CTRL |= SYSCON_LPCAC_CTRL_FRC_NO_ALLOC_MASK;
}

/*!
 * @brief Enables parity.
 *
 */
static inline void L1CACHE_EnableParity(void)
{
    SYSCON->LPCAC_CTRL |= SYSCON_LPCAC_CTRL_PARITY_MISS_EN_MASK;
}

/*!
 * @brief Disable parity.
 *
 */
static inline void L1CACHE_DisableParity(void)
{
    SYSCON->LPCAC_CTRL &= ~SYSCON_LPCAC_CTRL_PARITY_MISS_EN_MASK;
}

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_CACHE_H_*/
