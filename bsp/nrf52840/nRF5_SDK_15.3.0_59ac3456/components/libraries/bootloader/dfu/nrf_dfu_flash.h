/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
/**@file
 *
 * @defgroup sdk_nrf_dfu_flash Flash operations
 * @{
 * @ingroup  nrf_dfu
 */

#ifndef NRF_DFU_FLASH_H__
#define NRF_DFU_FLASH_H__

#include <stdint.h>
#include <stdbool.h>
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@brief   nrf_fstorage event handler function for DFU fstorage operations.
 *
 * This function will be called after a flash operation has completed.
 */
typedef void (*nrf_dfu_flash_callback_t)(void * p_buf);


/**@brief Function for initializing the flash module.
 *
 * Depending on whether or not the SoftDevice is present and its IRQ have been initialized,
 * this function initializes the correct @ref nrf_fstorage backend.
 *
 * @param[in]   sd_irq_initialized  Whether or not the SoftDevice IRQ have been initialized.
 *
 * @retval NRF_SUCCESS  If the operation was successful.
  */
ret_code_t nrf_dfu_flash_init(bool sd_irq_initialized);


/**@brief Function for storing data to flash.
 *
 * This functions is asynchronous when the SoftDevice is enabled and synchronous when
 * the SoftDevice is not present or disabled. In both cases, if a callback function is provided,
 * it will be called when the operation has completed.
 *
 * @note The content of @p p_src should be kept in memory until the operation has completed.
 *
 * @param[in]  dest      The address where the data should be stored.
 * @param[in]  p_src     Pointer to the address where the data should be copied from.
 *                       This address can be in flash or RAM.
 * @param[in]  len       The number of bytes to be copied from @p p_src to @p dest.
 * @param[in]  callback  Callback function.
 *
 * @retval  NRF_SUCCESS                 If the operation was successful.
 * @retval  NRF_ERROR_INVALID_STATE     If nrf_dfu_flash is not initialized.
 * @retval  NRF_ERROR_INVALID_ADDR      If @p p_src or @p dest is not word-aligned.
 * @retval  NRF_ERROR_INVALID_LENGTH    If @p len is zero.
 * @retval  NRF_ERROR_NULL              If @p p_src is NULL.
 * @retval  NRF_ERROR_NO_MEM            If nrf_fstorage is out of memory.
 */
ret_code_t nrf_dfu_flash_store(uint32_t                     dest,
                               void                 const * p_src,
                               uint32_t                     len,
                               nrf_dfu_flash_callback_t     callback);


/**@brief Function for erasing data from flash.
 *
 * This functions is asynchronous when the SoftDevice is enabled and synchronous when
 * the SoftDevice is not present or disabled. In both cases, if a callback function is provided,
 * it will be called when the operation has completed.
 *
 * @param[in]  page_addr    The address of the first flash page to be deleted.
 * @param[in]  num_pages    The number of flash pages to be deleted.
 * @param[in]  callback     Callback function.
 *
 * @retval  NRF_SUCCESS                 If the operation was successful.
 * @retval  NRF_ERROR_INVALID_STATE     If nrf_dfu_flash is not initialized.
 * @retval  NRF_ERROR_INVALID_ADDR      If @p page_addr is not aligned to a page boundary or the
 *                                      operation would go beyond the flash memory boundaries.
 * @retval  NRF_ERROR_INVALID_LENGTH    If @p num_pages is zero.
 * @retval  NRF_ERROR_NULL              If @p page_addr is NULL.
 * @retval  NRF_ERROR_NO_MEM            If the queue of nrf_fstorage is full.
 */
ret_code_t nrf_dfu_flash_erase(uint32_t page_addr, uint32_t num_pages, nrf_dfu_flash_callback_t callback);


#ifdef __cplusplus
}
#endif


#endif // NRF_DFU_FLASH_H__
/** @} */
