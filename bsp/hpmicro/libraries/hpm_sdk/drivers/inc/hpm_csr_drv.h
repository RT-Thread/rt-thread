/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_CSR_DRV_H
#define HPM_CSR_DRV_H

#include "hpm_csr_regs.h"
#include "riscv/riscv_core.h"


/**
 * @brief CSR driver APIs
 * @defgroup csr_interface CSR driver APIs
 * @ingroup csr_interfaces
 * @{
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enable access to CSR_CYCLE and CSR_MCYCLEH
 * @note This Function can be called in Machine mode only
 *
 */
static inline void hpm_csr_enable_access_to_csr_cycle(void)
{
    uint32_t mcounter_en = read_csr(CSR_MCOUNTEREN);
    write_csr(CSR_MCOUNTEREN, mcounter_en | CSR_MCOUNTEREN_CY_MASK);
}

/**
 * @brief Disable access to CSR_CYCLE and CSR_MCYCLEH
 * @note This Function can be called in Machine mode only
 *
 */
static inline void hpm_csr_disable_access_to_csr_cycle(void)
{
    uint32_t mcounter_en = read_csr(CSR_MCOUNTEREN);
    write_csr(CSR_MCOUNTEREN, mcounter_en & ~CSR_MCOUNTEREN_CY_MASK);
}

/**
 * @brief Get the core cycle value
 * @note The CY bit in MCOUNTEREN must be enabled before using this API whendevice is :
 *          - in supervisor mode if the device supports M/S/U mode, or
 *          - in user mode if the device supports M/U mode
 *
 * @return CSR cycle value in 64-bit
 */
static inline uint64_t hpm_csr_get_core_cycle(void)
{
    uint64_t result;
    uint32_t resultl_first = read_csr(CSR_CYCLE);
    uint32_t resulth = read_csr(CSR_CYCLEH);
    uint32_t resultl_second = read_csr(CSR_CYCLE);
    if (resultl_first < resultl_second) {
        result = ((uint64_t)resulth << 32) | resultl_first; /* if CYCLE didn't roll over, return the value directly */
    } else {
        resulth = read_csr(CSR_CYCLEH);
        result = ((uint64_t)resulth << 32) | resultl_second; /* if CYCLE rolled over, need to get the CYCLEH again */
    }
    return result;
 }

/**
 * @brief Get the core mcycle value
 * @note This function can be called in machine mode only
 *
 * @return CSR mcycle value in 64-bit
 */
static inline uint64_t hpm_csr_get_core_mcycle(void)
{
    uint64_t result;
    uint32_t resultl_first = read_csr(CSR_MCYCLE);
    uint32_t resulth = read_csr(CSR_MCYCLEH);
    uint32_t resultl_second = read_csr(CSR_MCYCLE);
    if (resultl_first < resultl_second) {
        result = ((uint64_t)resulth << 32) | resultl_first; /* if MCYCLE didn't roll over, return the value directly */
    } else {
        resulth = read_csr(CSR_MCYCLEH);
        result = ((uint64_t)resulth << 32) | resultl_second; /* if MCYCLE rolled over, need to get the MCYCLEH again */
    }
    return result;
 }


#ifdef __cplusplus
}
#endif

/**
 * @}
 */


#endif /* HPM_CSR_DRV_H */
