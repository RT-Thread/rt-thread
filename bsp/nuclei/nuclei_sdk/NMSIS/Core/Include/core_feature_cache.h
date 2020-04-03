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
#ifndef __CORE_FEATURE_CACHE_H__
#define __CORE_FEATURE_CACHE_H__
/*!
 * @file     core_feature_cache.h
 * @brief    Cache feature API header file for Nuclei N/NX Core
 */
/*
 * Cache Feature Configuration Macro:
 * 1. __ICACHE_PRESENT:  Define whether I-Cache Unit is present or not.
 *   * 0: Not present
 *   * 1: Present
 * 1. __DCACHE_PRESENT:  Define whether D-Cache Unit is present or not.
 *   * 0: Not present
 *   * 1: Present
 */
#ifdef __cplusplus
 extern "C" {
#endif

#if defined(__ICACHE_PRESENT) && (__ICACHE_PRESENT == 1)

/* ##########################  Cache functions  #################################### */
/**
 * \defgroup NMSIS_Core_Cache       Cache Functions
 * \brief    Functions that configure Instruction and Data Cache.
 * @{
 */

/** @} */ /* End of Doxygen Group NMSIS_Core_Cache */

/**
 * \defgroup NMSIS_Core_ICache      I-Cache Functions
 * \ingroup  NMSIS_Core_Cache
 * \brief    Functions that configure Instruction Cache.
 * @{
 */
/**
 * \brief  Enable ICache
 * \details
 * This function enable I-Cache
 * \remarks
 * - This \ref CSR_MCACHE_CTL register control I Cache enable.
 * \sa
 * - \ref DisableICache
*/
__STATIC_FORCEINLINE void EnableICache (void)
{
    __RV_CSR_SET(CSR_MCACHE_CTL, CSR_MCACHE_CTL_IE);
}

/**
 * \brief  Disable ICache
 * \details
 * This function Disable I-Cache
 * \remarks
 * - This \ref CSR_MCACHE_CTL register control I Cache enable.
 * \sa
 * - \ref EnableICache
 */
__STATIC_FORCEINLINE void DisableICache (void)
{
    __RV_CSR_CLEAR(CSR_MCACHE_CTL, CSR_MCACHE_CTL_IE);
}
/** @} */ /* End of Doxygen Group NMSIS_Core_ICache */
#endif /* defined(__ICACHE_PRESENT) && (__ICACHE_PRESENT == 1) */

#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1)
/**
 * \defgroup NMSIS_Core_DCache      D-Cache Functions
 * \ingroup  NMSIS_Core_Cache
 * \brief    Functions that configure Data Cache.
 * @{
 */
/**
 * \brief  Enable DCache
 * \details
 * This function enable D-Cache
 * \remarks
 * - This \ref CSR_MCACHE_CTL register control D Cache enable.
 * \sa
 * - \ref DisableDCache
*/
__STATIC_FORCEINLINE void EnableDCache (void)
{
    __RV_CSR_SET(CSR_MCACHE_CTL, CSR_MCACHE_CTL_DE);
}

/**
 * \brief  Disable DCache
 * \details
 * This function Disable D-Cache
 * \remarks
 * - This \ref CSR_MCACHE_CTL register control D Cache enable.
 * \sa
 * - \ref EnableDCache
 */
__STATIC_FORCEINLINE void DisableDCache (void)
{
    __RV_CSR_CLEAR(CSR_MCACHE_CTL, CSR_MCACHE_CTL_DE);
}
/** @} */ /* End of Doxygen Group NMSIS_Core_DCache */
#endif /* defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1) */

#ifdef __cplusplus
}
#endif
#endif /** __CORE_FEATURE_CACHE_H__ */
