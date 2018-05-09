/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
 * @ingroup  sdk_nrf_dfu
 */

#ifndef NRF_DFU_FLASH_H__
#define NRF_DFU_FLASH_H__

#include <stdint.h>
#include <stdbool.h>
#include "fstorage.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@brief   fstorage event handler function for DFU fstorage operations.
 *
 * This function is intended to be registered to the fstorage module as the event handler for all DFU flash operations.
 * When each flash operation has completed or failed this function will be called.
 *
 * See ::fs_cb_t for implementation details.
 */
typedef fs_cb_t dfu_flash_callback_t;

/**@brief Function for initializing the flash module.
 *
 * You can use this module with or without a SoftDevice:
 * - If the module is initialized with the SoftDevice enabled flag set, the @ref fstorage
 *   module is used as back end for all flash operations. Flash storage calls
 *   are asynchronous; the SoftDevice manages when the actual operation in
 *   flash is done.
 * - If the module is initialized with the SoftDevice enabled flag not set,
 *   the non-volatile memory controller (NVMC) driver handles the flash operations
 *   by directly accessing flash. These operations are synchronous.
 *
 * @param[in]  sd_enabled Set the flash handling to run with or without the SoftDevice enabled.
 *
 * @retval NRF_SUCCESS             If the operation was successful.
 * @retval NRF_ERROR_INVALID_STATE If the fstorage module could not be initiated or the SoftDevice could not set the event handler.
 */
uint32_t nrf_dfu_flash_init(bool sd_enabled);


/**@brief Function for storing data to flash (with or without the SoftDevice enabled).
 *
 * @warning The content to be stored must be kept at @p p_src until the operation is
 *          complete. Without SoftDevice, the operation is complete when the function
 *          returns. With SoftDevice, the operation is complete when the fstorage event is received.
 *
 * @param[in]  p_dest    Pointer to the address where the data should be stored.
 * @param[in]  p_src     Pointer to the address where the data should be copied from.
 *                       This address can be in flash or RAM.
 * @param[in]  len_words The number of words to be copied from @p p_src to @p p_dest.
 * @param[in]  callback  Pointer to the callback function.
 *
 * @retval  FS_SUCCESS                If the operation was successful.
 * @retval  FS_ERR_FAILURE_SINCE_LAST If an error occurred in another transaction and fstorage cannot continue before
 *                                   the event has been dealt with.
 * @retval  FS_ERR_UNALIGNED_ADDR     If @p p_src or @p p_dest is not word-aligned. Ensure that the address pointed to is divisible by four.
 * @retval  FS_ERR_INVALID_ARG        If @p len_words is zero. It is not possible to write zero words.
 * @retval  FS_ERR_NULL_ARG           If @p p_src or @p p_dest is NULL.
 *
 * @retval  FS_ERR_NOT_INITIALIZED  If the fstorage module is not initialized.
 * @retval  FS_ERR_INVALID_CFG      If the initialization of the fstorage module is invalid.
 * @retval  FS_ERR_QUEUE_FULL       If the internal operation queue of the fstorage module is full.
 */
fs_ret_t nrf_dfu_flash_store(uint32_t const * p_dest, uint32_t const * const p_src, uint32_t len_words, dfu_flash_callback_t callback);


/**@brief Function for erasing data from flash (with or without the SoftDevice enabled).
 *
 * @param[in]  p_dest    The address of the first byte to be deleted.
 * @param[in]  num_pages The number of flash pages to be deleted.
 * @param[in]  callback  Pointer to the callback function.
 *
 * @retval  FS_SUCCESS              If the operation was successful.
 * @retval  FS_ERR_UNALIGNED_ADDR   If @p p_dest is not aligned to a page boundary.
 * @retval  FS_ERR_INVALID_ADDR     If @p p_dest does not point to the start of a flash page or the operation would
 *                                  go beyond the flash memory boundary.
 * @retval  FS_ERR_NOT_INITIALIZED  If the fstorage module is not initialized.
 * @retval  FS_ERR_INVALID_CFG      If the initialization of the fstorage module is invalid.
 * @retval  FS_ERR_NULL_ARG         If @p p_dest is NULL.
 * @retval  FS_ERR_INVALID_ARG      If @p num_pages is zero.
 * @retval  FS_ERR_QUEUE_FULL       If the internal operation queue of the fstorage module is full.
 */
fs_ret_t nrf_dfu_flash_erase(uint32_t const * p_dest, uint32_t num_pages, dfu_flash_callback_t callback);


/**@brief Function for clearing an error that has occurred during fstorage operations.
 */
void nrf_dfu_flash_error_clear(void);


/**@brief Function for waiting for an event from fstorage.
 *
 * This function halts execution until an event is received from the SoftDevice.
 * You can use this function to halt execution until a flash operation has completed, to prevent
 * tampering with the source data until fstorage is done with it.
 *
 * @retval FS_SUCCESS                If the operation was successful.
 * @retval FS_ERR_FAILURE_SINCE_LAST If an error has occurred in another transaction and fstorage cannot continue before
 *                                   the event has been dealt with.
 */
fs_ret_t nrf_dfu_flash_wait(void);


#ifdef __cplusplus
}
#endif


#endif // NRF_DFU_FLASH_H__
/** @} */
