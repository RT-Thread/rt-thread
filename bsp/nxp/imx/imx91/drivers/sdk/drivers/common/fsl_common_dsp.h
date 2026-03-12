/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_COMMON_DSP_H_
#define FSL_COMMON_DSP_H_

/*!
 * @addtogroup ksdk_common
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Timer utilities */
/*! @{ */
/*! Macro to convert a microsecond period to raw count value */
#define USEC_TO_COUNT(us, clockFreqInHz) (uint64_t)(((uint64_t)(us) * (clockFreqInHz)) / 1000000U)
/*! Macro to convert a raw count value to microsecond */
#define COUNT_TO_USEC(count, clockFreqInHz) (uint64_t)((uint64_t)(count) * 1000000U / (clockFreqInHz))

/*! Macro to convert a millisecond period to raw count value */
#define MSEC_TO_COUNT(ms, clockFreqInHz) (uint64_t)((uint64_t)(ms) * (clockFreqInHz) / 1000U)
/*! Macro to convert a raw count value to millisecond */
#define COUNT_TO_MSEC(count, clockFreqInHz) (uint64_t)((uint64_t)(count) * 1000U / (clockFreqInHz))
/*! @} */

#define SDK_ISR_EXIT_BARRIER

/*! @name Alignment variable definition macros */
/*! @{ */
/*! Macro to define a variable with alignbytes alignment */
#define SDK_ALIGN(var, alignbytes) var __attribute__((aligned(alignbytes)))

/*! Macro to define a variable with L1 d-cache line size alignment */
#if defined(FSL_FEATURE_L1DCACHE_LINESIZE_BYTE)
#define SDK_L1DCACHE_ALIGN(var) SDK_ALIGN(var, FSL_FEATURE_L1DCACHE_LINESIZE_BYTE)
#endif

/*! Macro to define a variable with L2 cache line size alignment */
#if defined(FSL_FEATURE_L2CACHE_LINESIZE_BYTE)
#define SDK_L2CACHE_ALIGN(var) SDK_ALIGN(var, FSL_FEATURE_L2CACHE_LINESIZE_BYTE)
#endif

/*! Macro to change a value to a given size aligned value */
#define SDK_SIZEALIGN(var, alignbytes) \
    ((unsigned int)((var) + ((alignbytes)-1U)) & (unsigned int)(~(unsigned int)((alignbytes)-1U)))
/*! @} */

/*! @name Non-cacheable region definition macros */
/* For initialized non-zero non-cacheable variables, please using "AT_NONCACHEABLE_SECTION_INIT(var) ={xx};" or
 * "AT_NONCACHEABLE_SECTION_ALIGN_INIT(var) ={xx};" in your projects to define them, for zero-inited non-cacheable variables,
 * please using "AT_NONCACHEABLE_SECTION(var);" or "AT_NONCACHEABLE_SECTION_ALIGN(var);" to define them, these zero-inited variables
 * will be initialized to zero in system startup.
 */
/*! @{ */

#define AT_NONCACHEABLE_SECTION_INIT(var) __attribute__((section("NonCacheable.init"))) var
#define AT_NONCACHEABLE_SECTION(var) __attribute__((section("NonCacheable"))) var
#define AT_NONCACHEABLE_SECTION_ALIGN_INIT(var, alignbytes) \
    __attribute__((section("NonCacheable.init"))) var __attribute__((aligned(alignbytes)))
#define AT_NONCACHEABLE_SECTION_ALIGN(var, alignbytes) \
    __attribute__((section("NonCacheable"))) var __attribute__((aligned(alignbytes)))

/*! @} */

/*!
 * @name Time sensitive region
 * @{
 */
#if (defined(FSL_SDK_DRIVER_QUICK_ACCESS_ENABLE) && FSL_SDK_DRIVER_QUICK_ACCESS_ENABLE)

#define AT_QUICKACCESS_SECTION_CODE(func) __attribute__((section("CodeQuickAccess"), __noinline__)) func
#define AT_QUICKACCESS_SECTION_DATA(func) __attribute__((section("DataQuickAccess"))) func

#else /* __FSL_SDK_DRIVER_QUICK_ACCESS_ENABLE */

#define AT_QUICKACCESS_SECTION_CODE(func) func
#define AT_QUICKACCESS_SECTION_DATA(func) func

#endif /* __FSL_SDK_DRIVER_QUICK_ACCESS_ENABLE */
/*! @} */

/* Macros for compatibility. */
#define NVIC_SetPriorityGrouping(value) do {} while(0)
#define NVIC_GetPriorityGrouping() do {} while(0)
#define NVIC_SetPriority(irq, value) do {} while(0)
#define NVIC_GetPriority(irq) do {} while(0)
#define NVIC_EnableIRQ(value) do {} while(0)
#define NVIC_GetEnableIRQ(value) do {} while(0)
#define NVIC_DisableIRQ(value) do {} while(0)
#define NVIC_GetPendingIRQ(value) do {} while(0)
#define NVIC_SetPendingIRQ(value) do {} while(0)
#define NVIC_ClearPendingIRQ(value) do {} while(0)
#define NVIC_GetActive(value) do {} while(0)
#define MSDK_REG_SECURE_ADDR(x) (x)
#define MSDK_REG_NONSECURE_ADDR(x) (x)

/*
 * The fsl_clock.h is included here because it needs MAKE_VERSION/MAKE_STATUS/status_t
 * defined in previous of this file.
 */
#include "fsl_clock.h"

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Enable specific interrupt.
 *
 * Empty function for build compatibility.
 *
 * @param interrupt The IRQ number.
 * @return Always return kStatus_Success.
 */
static inline status_t EnableIRQ(IRQn_Type interrupt)
{
    return kStatus_Success;
}

/*!
 * @brief Disable specific interrupt.
 *
 * Empty function for build compatibility.
 *
 * @param interrupt The IRQ number.
 * @return Always return kStatus_Success.
 */
static inline status_t DisableIRQ(IRQn_Type interrupt)
{
    return kStatus_Success;
}

/*!
 * @brief Disable the global IRQ
 *
 * Empty function for build compatibility.
 *
 * @return Always return 0;
 */
static inline uint32_t DisableGlobalIRQ(void)
{
    return 0;
}

/*!
 * @brief Enable the global IRQ
 *
 * Empty function for build compatibility.
 *
 * @param primask Not used.
 */
static inline void EnableGlobalIRQ(uint32_t primask)
{
}

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_COMMON_DSP_H_ */
