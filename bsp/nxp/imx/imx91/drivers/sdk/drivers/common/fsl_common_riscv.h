/*
 * Copyright 2024-2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_COMMON_RISCV_H_
#define FSL_COMMON_RISCV_H_

#include "riscv_interrupt.h"

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

/*! Macro to change a value to a given size aligned value */
#define SDK_SIZEALIGN(var, alignbytes) \
    ((unsigned int)((var) + ((alignbytes)-1U)) & (unsigned int)(~(unsigned int)((alignbytes)-1U)))
/*! @} */

/*!
 * @def MSDK_REG_SECURE_ADDR(x)
 * Convert the register address to the one used in secure mode.
 *
 * @def MSDK_REG_NONSECURE_ADDR(x)
 * Convert the register address to the one used in unsecure mode.
 */
#define MSDK_REG_SECURE_ADDR(x) ((typeof(x))((uintptr_t)(x) | (0x1UL << 28)))
#define MSDK_REG_NONSECURE_ADDR(x) ((typeof(x))((uintptr_t)(x) & ~(0x1UL << 28)))

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
 * Disable the global IRQ.
 *
 * @return The global IRQ control register value before been disabled.
 */
static inline uint32_t DisableGlobalIRQ(void)
{
    return csr_read_clear(CSR_MSTATUS, CSR_MSTATUS_MIE);
}

/*!
 * @brief Enable the global IRQ
 *
 * Enable the global interrupt by setting the global IRQ control register.
 * Generally this value is the return value of DisableGlobalIRQ.
 *
 * @param intCtrl The global interrupt control register value.
 */
static inline void EnableGlobalIRQ(uint32_t intCtrl)
{
    csr_set(CSR_MSTATUS, intCtrl);
}

/*!
 * @brief Enable M-mode interrupt.
 *
 * @param mask M-mode interrupt mask.
 */
static inline void EnableMachineModeInt(ezhv_mie_mask_t mask)
{
    csr_set(CSR_MIE, mask);
}

/*!
 * @brief Disable M-mode interrupt.
 *
 * @param mask M-mode interrupt mask.
 */
static inline void DisableMachineModeInt(ezhv_mie_mask_t mask)
{
    csr_clear(CSR_MIE, mask);
}

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
