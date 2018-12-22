/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/** @file
 *
 * @defgroup mem_manager Memory Manager
 * @{
 * @ingroup app_common
 * @brief Memory Manager for the @nRFXX SDK
 *
 * @details This module allows for dynamic use of memory. Currently,
 * this module can be used only to allocate and free memory in the RAM.
 *
 * The Memory Manager manages static memory blocks of fixed sizes. These blocks can be requested for
 * usage, and freed when the application no longer needs them. A maximum of seven block categories
 * can be managed by the module. These block categories are identified by xxsmall, xmall, small,
 * medium, large, xlarge, and xxlarge. They are ordered in increasing block sizes.
 * The size and the count of each of the block categories can be configured based on the application
 * requirements in the configuration file @c sdk_config.h.
 * To use fewer than seven buffer pools, do not define the count for the unwanted block
 * or explicitly set it to zero. At least one block category must be configured
 * for this module to function as expected.
 */

#ifndef MEM_MANAGER_H__
#define MEM_MANAGER_H__

#include "sdk_common.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Initializes Memory Manager.
 *
 * @details API to initialize the Memory Manager. Always call this API before using any of the other
 *          APIs of the module. This API should be called only once.
 *
 * @retval NRF_SUCCESS If initialization was successful.
 *         Otherwise, an error code that indicates the reason for the failure is returned.
 *
 * @warning   If this API fails, the application shall not proceed with using other APIs of this
 *            module.
 */
uint32_t nrf_mem_init(void);


/**@brief Reserves a block of memory for the application.
 *
 * @details API to request a contiguous memory block of the given length. If
 *          the memory allocation succeeds, pp_buffer points to the memory block. If
 *          the memory allocation fails, pp_buffer points to NULL and the return value of
 *          the API indicates the reason for the failure. The memory block reserved using this API can
 *          be freed using the @ref nrf_free function.
 *
 * @param[out]   pp_buffer             Pointer to the allocated memory block if memory allocation
 *                                     succeeds; otherwise points to NULL.
 * @param[inout] p_size                Requested memory size. This parameter returns the actual size
 *                                     allocated. If the procedure was successful, the actual size
 *                                     returned is always greater than or equal to requested size,
 *                                     never less.
 *
 * @retval     NRF_SUCCESS             If memory was successfully allocated.
 *                                     Otherwise, an error code indicating the reason for failure.
 * @retval     NRF_ERROR_INVALID_PARAM If the requested memory size is zero or greater than the
 *                                     largest memory block that the module is configured to
 *                                     support.
 * @retval     NRF_ERROR_NO_MEM        If there is no memory available of the requested size.
 */
uint32_t nrf_mem_reserve(uint8_t ** pp_buffer, uint32_t * p_size);


/**@brief 'malloc' styled memory allocation function.
 *
 * @details API to allocate memory, same as nrf_mem_reserve but uses malloc signature.
 *
 * @param[in]  size  Requested memory size.
 *
 * @retval     Valid memory location if the procedure was successful, else, NULL.
 */
void * nrf_malloc(uint32_t size);


/**@brief 'calloc' styled memory allocation function.
 *
 * @details API to allocate zero-initialized memory of size count*size.
 *
 * @param[in]  nmemb  Number of elements of 'size' bytes.
 * @param[in]  size   Size of each element allocated.
 *
 * @retval     Valid, zero-initialized memory location if the procedure was successful, else, NULL.
 */
void * nrf_calloc(uint32_t nmemb, uint32_t size);


/**@brief Free allocated memory - standard 'free' styles API.
 *
 * @details API to resubmit memory allocated, same in functionality nrf_free.
 *
 * @param[out] p_buffer   Pointer to the memory block that is being freed.
 */
void nrf_free(void * p_buffer);


/**@brief Memory reallocation (trim) function.
 *
 * @details API to reallocate memory or to trim it. Trim is mentioned here to avoid use of API to
 *          request memory size larger than original memory allocated.
 *
 * @param[in] p_buffer   Pointer to the memory block that needs to be trimmed.
 * @param[in] size       Size of memory at the beginning of the buffer to be left untrimmed.
 *
 * @retval    Pointer to memory location with trimmed size, else, NULL.
 */
void * nrf_realloc(void *p_buffer, uint32_t size);

#ifdef MEM_MANAGER_ENABLE_DIAGNOSTICS

/**@brief Function to print statstics related to memory blocks managed by memory manager.
 *
 * @details This API prints information with respects to each block function, including size, total
 *          block count, number of blocks in use at the time of printing, smallest memory size
 *          allocated in the block and the largest one. This  API is intended to help developers
 *          tune the block sizes to make optimal use of memory for the application.
 *          This functionality is never needed in final application and therefore, is disabled by
 *          default.
 */
void nrf_mem_diagnose(void);

#endif // MEM_MANAGER_ENABLE_DIAGNOSTICS


#ifdef __cplusplus
}
#endif

#endif // MEM_MANAGER_H__
/** @} */
