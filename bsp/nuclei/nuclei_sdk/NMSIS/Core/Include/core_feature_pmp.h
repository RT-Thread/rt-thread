/*
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __CORE_FEATURE_PMP_H__
#define __CORE_FEATURE_PMP_H__
/*!
 * @file     core_feature_pmp.h
 * @brief    PMP feature API header file for Nuclei N/NX Core
 */
/*
 * PMP Feature Configuration Macro:
 * 1. __PMP_PRESENT:  Define whether Physical Memory Protection(PMP) is present or not
 *   * 0: Not present
 *   * 1: Present
 * 2. __PMP_ENTRY_NUM:  Define the number of PMP entries, only 8 or 16 is configurable.
 */
#ifdef __cplusplus
 extern "C" {
#endif

#if defined(__PMP_PRESENT) && (__PMP_PRESENT == 1)
/* ===== PMP Operations ===== */
/**
 * \defgroup NMSIS_Core_PMP_Functions   PMP Functions
 * \ingroup  NMSIS_Core
 * \brief    Functions that related to the RISCV Phyiscal Memory Protection.
 * \details
 * Optional physical memory protection (PMP) unit provides per-hart machine-mode
 * control registers to allow physical memory access privileges (read, write, execute)
 * to be specified for each physical memory region.
 *
 * The PMP can supports region access control settings as small as four bytes.
 *
 *   @{
 */
#ifndef __PMP_ENTRY_NUM
/* numbers of PMP entries(__PMP_ENTRY_NUM) should be defined in <Device.h> */
#error "__PMP_ENTRY_NUM is not defined, please check!"
#endif

/**
 * \brief   Get 8bit PMPxCFG Register by PMP entry index
 * \details Return the content of the PMPxCFG Register.
 * \param [in]    idx    PMP region index(0-15)
 * \return               PMPxCFG Register value
 */
__STATIC_INLINE uint8_t __get_PMPxCFG(uint32_t idx)
{
    rv_csr_t pmpcfg = 0;

    if (idx >= __PMP_ENTRY_NUM) return 0;
#if __RISCV_XLEN == 32
    if (idx < 4) {
        pmpcfg = __RV_CSR_READ(CSR_PMPCFG0);
    } else if ((idx >=4) && (idx < 8)) {
        idx -= 4;
        pmpcfg = __RV_CSR_READ(CSR_PMPCFG1);
    } else if ((idx >=8) && (idx < 12)) {
        idx -= 8;
        pmpcfg = __RV_CSR_READ(CSR_PMPCFG2);
    } else {
        idx -= 12;
        pmpcfg = __RV_CSR_READ(CSR_PMPCFG3);
    }

    idx = idx << 3;
    return (uint8_t)((pmpcfg>>idx) & 0xFF);
#elif __RISCV_XLEN == 64
    if (idx < 8) {
        pmpcfg = __RV_CSR_READ(CSR_PMPCFG0);
    } else {
        idx -= 8;
        pmpcfg = __RV_CSR_READ(CSR_PMPCFG2);
    }
    idx = idx << 3;
    return (uint8_t)((pmpcfg>>idx) & 0xFF);
#else
    // TODO Add RV128 Handling
    return 0;
#endif
}

/**
 * \brief   Set 8bit PMPxCFG by pmp entry index
 * \details Set the given pmpxcfg value to the PMPxCFG Register.
 * \param [in]    idx      PMPx region index(0-15)
 * \param [in]    pmpxcfg  PMPxCFG register value to set
 */
__STATIC_INLINE void __set_PMPxCFG(uint32_t idx, uint8_t pmpxcfg)
{
    rv_csr_t pmpcfgx = 0;
    if (idx >= __PMP_ENTRY_NUM) return;

#if __RISCV_XLEN == 32
    if (idx < 4) {
        pmpcfgx = __RV_CSR_READ(CSR_PMPCFG0);
        idx = idx << 3;
        pmpcfgx = (pmpcfgx & ~(0xFFUL << idx)) | ((rv_csr_t)pmpxcfg << idx);
        __RV_CSR_WRITE(CSR_PMPCFG0, pmpcfgx);
    } else if ((idx >=4) && (idx < 8)) {
        idx -= 4;
        pmpcfgx = __RV_CSR_READ(CSR_PMPCFG1);
        idx = idx << 3;
        pmpcfgx = (pmpcfgx & ~(0xFFUL << idx)) | ((rv_csr_t)pmpxcfg << idx);
        __RV_CSR_WRITE(CSR_PMPCFG1, pmpcfgx);
    } else if ((idx >=8) && (idx < 12)) {
        idx -= 8;
        pmpcfgx = __RV_CSR_READ(CSR_PMPCFG2);
        idx = idx << 3;
        pmpcfgx = (pmpcfgx & ~(0xFFUL << idx)) | ((rv_csr_t)pmpxcfg << idx);
        __RV_CSR_WRITE(CSR_PMPCFG2, pmpcfgx);
    } else {
        idx -= 12;
        pmpcfgx = __RV_CSR_READ(CSR_PMPCFG3);
        idx = idx << 3;
        pmpcfgx = (pmpcfgx & ~(0xFFUL << idx)) | ((rv_csr_t)pmpxcfg << idx);
        __RV_CSR_WRITE(CSR_PMPCFG3, pmpcfgx);
    }
#elif __RISCV_XLEN == 64
    if (idx < 8) {
        pmpcfgx = __RV_CSR_READ(CSR_PMPCFG0);
        idx = idx << 3;
        pmpcfgx = (pmpcfgx & ~(0xFFULL << idx)) | ((rv_csr_t)pmpxcfg << idx);
        __RV_CSR_WRITE(CSR_PMPCFG0, pmpcfgx);
    } else {
        idx -= 8;
        pmpcfgx = __RV_CSR_READ(CSR_PMPCFG2);
        idx = idx << 3;
        pmpcfgx = (pmpcfgx & ~(0xFFULL << idx)) | ((rv_csr_t)pmpxcfg << idx);
        __RV_CSR_WRITE(CSR_PMPCFG2, pmpcfgx);
    }
#else
    // TODO Add RV128 Handling
#endif
}

/**
 * \brief   Get PMPCFGx Register by index
 * \details Return the content of the PMPCFGx Register.
 * \param [in]    idx    PMPCFG CSR index(0-3)
 * \return               PMPCFGx Register value
 * \remark
 * - For RV64, only idx = 0 and idx = 2 is allowed.
 *   pmpcfg0 and pmpcfg2 hold the configurations
 *   for the 16 PMP entries, pmpcfg1 and pmpcfg3 are illegal
 * - For RV32, pmpcfg0–pmpcfg3, hold the configurations
 *   pmp0cfg–pmp15cfg for the 16 PMP entries
 */
__STATIC_INLINE rv_csr_t __get_PMPCFGx(uint32_t idx)
{
    switch (idx) {
        case 0: return __RV_CSR_READ(CSR_PMPCFG0);
        case 1: return __RV_CSR_READ(CSR_PMPCFG1);
        case 2: return __RV_CSR_READ(CSR_PMPCFG2);
        case 3: return __RV_CSR_READ(CSR_PMPCFG3);
        default: return 0;
    }
}

/**
 * \brief   Set PMPCFGx by index
 * \details Write the given value to the PMPCFGx Register.
 * \param [in]    idx      PMPCFG CSR index(0-3)
 * \param [in]    pmpcfg   PMPCFGx Register value to set
 * \remark
 * - For RV64, only idx = 0 and idx = 2 is allowed.
 *   pmpcfg0 and pmpcfg2 hold the configurations
 *   for the 16 PMP entries, pmpcfg1 and pmpcfg3 are illegal
 * - For RV32, pmpcfg0–pmpcfg3, hold the configurations
 *   pmp0cfg–pmp15cfg for the 16 PMP entries
 */
__STATIC_INLINE void __set_PMPCFGx(uint32_t idx, rv_csr_t pmpcfg)
{
    switch (idx) {
        case 0: __RV_CSR_WRITE(CSR_PMPCFG0, pmpcfg); break;
        case 1: __RV_CSR_WRITE(CSR_PMPCFG1, pmpcfg); break;
        case 2: __RV_CSR_WRITE(CSR_PMPCFG2, pmpcfg); break;
        case 3: __RV_CSR_WRITE(CSR_PMPCFG3, pmpcfg); break;
        default: return;
    }
}

/**
 * \brief   Get PMPADDRx Register by index
 * \details Return the content of the PMPADDRx Register.
 * \param [in]    idx    PMP region index(0-15)
 * \return               PMPADDRx Register value
 */
__STATIC_INLINE rv_csr_t __get_PMPADDRx(uint32_t idx)
{
    switch (idx) {
        case 0: return __RV_CSR_READ(CSR_PMPADDR0);
        case 1: return __RV_CSR_READ(CSR_PMPADDR1);
        case 2: return __RV_CSR_READ(CSR_PMPADDR2);
        case 3: return __RV_CSR_READ(CSR_PMPADDR3);
        case 4: return __RV_CSR_READ(CSR_PMPADDR4);
        case 5: return __RV_CSR_READ(CSR_PMPADDR5);
        case 6: return __RV_CSR_READ(CSR_PMPADDR6);
        case 7: return __RV_CSR_READ(CSR_PMPADDR7);
        case 8: return __RV_CSR_READ(CSR_PMPADDR8);
        case 9: return __RV_CSR_READ(CSR_PMPADDR9);
        case 10: return __RV_CSR_READ(CSR_PMPADDR10);
        case 11: return __RV_CSR_READ(CSR_PMPADDR11);
        case 12: return __RV_CSR_READ(CSR_PMPADDR12);
        case 13: return __RV_CSR_READ(CSR_PMPADDR13);
        case 14: return __RV_CSR_READ(CSR_PMPADDR14);
        case 15: return __RV_CSR_READ(CSR_PMPADDR15);
        default: return 0;
    }
}

/**
 * \brief   Set PMPADDRx by index
 * \details Write the given value to the PMPADDRx Register.
 * \param [in]    idx      PMP region index(0-15)
 * \param [in]    pmpaddr  PMPADDRx Register value to set
 */
__STATIC_INLINE void __set_PMPADDRx(uint32_t idx, rv_csr_t pmpaddr)
{
    switch (idx) {
        case 0: __RV_CSR_WRITE(CSR_PMPADDR0, pmpaddr); break;
        case 1: __RV_CSR_WRITE(CSR_PMPADDR1, pmpaddr); break;
        case 2: __RV_CSR_WRITE(CSR_PMPADDR2, pmpaddr); break;
        case 3: __RV_CSR_WRITE(CSR_PMPADDR3, pmpaddr); break;
        case 4: __RV_CSR_WRITE(CSR_PMPADDR4, pmpaddr); break;
        case 5: __RV_CSR_WRITE(CSR_PMPADDR5, pmpaddr); break;
        case 6: __RV_CSR_WRITE(CSR_PMPADDR6, pmpaddr); break;
        case 7: __RV_CSR_WRITE(CSR_PMPADDR7, pmpaddr); break;
        case 8: __RV_CSR_WRITE(CSR_PMPADDR8, pmpaddr); break;
        case 9: __RV_CSR_WRITE(CSR_PMPADDR9, pmpaddr); break;
        case 10: __RV_CSR_WRITE(CSR_PMPADDR10, pmpaddr); break;
        case 11: __RV_CSR_WRITE(CSR_PMPADDR11, pmpaddr); break;
        case 12: __RV_CSR_WRITE(CSR_PMPADDR12, pmpaddr); break;
        case 13: __RV_CSR_WRITE(CSR_PMPADDR13, pmpaddr); break;
        case 14: __RV_CSR_WRITE(CSR_PMPADDR14, pmpaddr); break;
        case 15: __RV_CSR_WRITE(CSR_PMPADDR15, pmpaddr); break;
        default: return;
    }
}
/** @} */ /* End of Doxygen Group NMSIS_Core_PMP_Functions */
#endif /* defined(__PMP_PRESENT) && (__PMP_PRESENT == 1) */

#ifdef __cplusplus
}
#endif
#endif /** __CORE_FEATURE_PMP_H__  */
