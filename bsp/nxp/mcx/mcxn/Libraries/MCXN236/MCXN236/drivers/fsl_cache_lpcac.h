/*
 * Copyright 2021-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_CACHE_LPCAC_H_
#define FSL_CACHE_LPCAC_H_

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
#define FSL_CACHE_LPCAC_DRIVER_VERSION (MAKE_VERSION(2, 1, 1))
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
    SYSCON->LPCAC_CTRL |= SYSCON_LPCAC_CTRL_CLR_LPCAC_MASK;
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

#if defined(FSL_FEATURE_LPCAC_SUPPORT_WRITE_BUFFER_CONTROL) && FSL_FEATURE_LPCAC_SUPPORT_WRITE_BUFFER_CONTROL
/*!
 * @brief Enables write through buffer.
 *
 */
static inline void L1CACHE_EnableWriteBuffer(void)
{
    SYSCON->LPCAC_CTRL &= ~SYSCON_LPCAC_CTRL_DIS_LPCAC_WTBF_MASK;
}

/*!
 * @brief Disables write through buffer.
 *
 */
static inline void L1CACHE_DisableWriteBuffer(void)
{
    SYSCON->LPCAC_CTRL |= SYSCON_LPCAC_CTRL_DIS_LPCAC_WTBF_MASK;
}

/*!
 * @brief Limits write through buffer.
 *
 */
static inline void L1CACHE_LimitWriteBuffer(void)
{
    SYSCON->LPCAC_CTRL &= ~SYSCON_LPCAC_CTRL_LIM_LPCAC_WTBF_MASK;
}

/*!
 * @brief Unlimits write through buffer.
 *
 */
static inline void L1CACHE_UnlimitParity(void)
{
    SYSCON->LPCAC_CTRL |= SYSCON_LPCAC_CTRL_LIM_LPCAC_WTBF_MASK;
}

/*!
 * @brief Enables parity error report.
 *
 */
static inline void L1CACHE_EnableParityErrorReport(void)
{
    SYSCON->LPCAC_CTRL |= SYSCON_LPCAC_CTRL_PARITY_FAULT_EN_MASK;
}

/*!
 * @brief Disables parity error report.
 *
 */
static inline void L1CACHE_DisableParityErrorReport(void)
{
    SYSCON->LPCAC_CTRL &= ~SYSCON_LPCAC_CTRL_PARITY_FAULT_EN_MASK;
}

/*!
 * @brief Enables XOM(eXecute-Only-Memory) control.
 *
 */
static inline void L1CACHE_EnableXOMControl(void)
{
    SYSCON->LPCAC_CTRL |= SYSCON_LPCAC_CTRL_LPCAC_XOM_MASK;
}

/*!
 * @brief Disables XOM(eXecute-Only-Memory) control.
 *
 */
static inline void L1CACHE_DisableXOMControl(void)
{
    SYSCON->LPCAC_CTRL &= ~SYSCON_LPCAC_CTRL_LPCAC_XOM_MASK;
}
#endif

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_CACHE_LPCAC_H_*/
