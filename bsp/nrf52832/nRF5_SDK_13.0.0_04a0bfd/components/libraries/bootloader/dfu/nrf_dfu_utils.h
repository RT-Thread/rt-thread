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
 * @defgroup sdk_nrf_dfu_utils DFU utilities
 * @{
 * @ingroup  sdk_nrf_dfu
 */

#ifndef NRF_DFU_UTILS_H__
#define NRF_DFU_UTILS_H__

#include <stdint.h>
#include <stdbool.h>
#include "nrf_dfu_types.h"
#include "app_timer.h"

#ifdef __cplusplus
extern "C"
{
#endif

// 3400ms is the smallest stable value with nrf connect for PC v1.1.1.
// 7500ms is the smallest stable value with nrf connect for Android v1.1.1.
// Smaller values may allow the device to reset before the next DFU transation is started.
#define RESET_DELAY_LENGTH_MS   10000
extern const app_timer_id_t nrf_dfu_utils_reset_delay_timer;

/** @brief Function for continuing an ongoing DFU operation.
 *
 * @details     This function initiates or continues the DFU copy-back
 *              routines. These routines are fail-safe operations to activate
 *              either a new SoftDevice, Bootloader, combination of SoftDevice and
 *              Bootloader, or a new application.
 *
 * @details     This function relies on accessing MBR commands through supervisor calls.
 *              It does not rely on the SoftDevice for flash operations.
 *
 * @note        When updating the bootloader or both bootloader and SoftDevice in combination,
 *              this function does not return, but rather initiate a reboot to activate
 *              the new bootloader.
 *
 * @param[in,out] p_enter_dfu_mode    True if the continuation failed or the update requires DFU mode.
 *
 * @retval  NRF_SUCCESS     If the DFU operation was continued successfully.
 *                          Any other error code indicates that the DFU operation could
 *                          not be continued.
 */
uint32_t nrf_dfu_continue(uint32_t * p_enter_dfu_mode);


/** @brief Function for checking if the main application is valid.
 *
 * @details     This function checks if there is a valid application
 *              located at Bank 0.
 *
 * @retval  true  If a valid application has been detected.
 * @retval  false If there is no valid application.
 */
bool nrf_dfu_app_is_valid(void);


/** @brief Function for finding a cache write location for the DFU process.
 *
 * @details This function checks the size requirements and selects a location for
 *          placing the cache of the DFU images.
 *          The function tries to find enough space in Bank 1. If there is not enough space,
 *          the present application is erased.
 *
 * @param[in]   size_req        Requirements for the size of the new image.
 * @param[in]   dual_bank_only  True to enforce dual-bank updates. In this case, if there
 *                              is not enough space for caching the DFU image, the existing
 *                              application is retained and the function returns an error.
 * @param[out]  p_address       Updated to the cache address if a cache location is found.
 *
 * @retval      NRF_SUCCESS         If a cache location was found for the DFU process.
 * @retval      NRF_ERROR_NO_MEM    If there is no space available on the device to continue the DFU process.
 */
uint32_t nrf_dfu_find_cache(uint32_t size_req, bool dual_bank_only, uint32_t * p_address);


#ifdef __cplusplus
}
#endif

#endif // NRF_DFU_UTILS_H__

/** @} */
