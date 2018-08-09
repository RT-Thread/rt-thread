/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
 * @defgroup nrf_dfu_settings DFU settings
 * @{
 * @ingroup  nrf_dfu
 */

#ifndef NRF_DFU_SETTINGS_H__
#define NRF_DFU_SETTINGS_H__

#include <stdint.h>
#include "nrf_dfu_types.h"
#include "nrf_dfu_flash.h"
#include "sdk_config.h"
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@brief   Global settings.
 *
 * @note Using this variable is not thread-safe.
 *
 */
extern nrf_dfu_settings_t s_dfu_settings;


/**@brief   Function for writing DFU settings to flash.
 *
 * @param[in]   callback    Pointer to a function that is called after completing the write operation.
 *
 * @retval  NRF_SUCCESS         If the write process was successfully initiated.
 * @retval  NRF_ERROR_INTERNAL  If a flash error occurred.
 */
ret_code_t nrf_dfu_settings_write(nrf_dfu_flash_callback_t callback);


/**@brief   Function for initializing the DFU settings module.
 *
 * @retval  NRF_SUCCESS         If the initialization was successful.
 * @retval  NRF_ERROR_INTERNAL  If a flash error occurred.
 */
ret_code_t nrf_dfu_settings_init(bool sd_irq_initialized);


#if defined(NRF_DFU_TRANSPORT_BLE) && NRF_DFU_TRANSPORT_BLE
/** @brief Function for storing peer data received through an SVCI call in DFU settings.
 *
 * @note The content of the type can be verified by a CRC value stored inside the struct
 *       If the CRC value is 0xFFFFFFFF, it means that no data is set.
 *
 * @note The storage operation is an asynchronous progress. Success will be notified
 *       through system events raised by the SoftDevice.
 *
 * @param[in]   p_data  Peer data to be stored in flash.
 *
 * @retval  NRF_SUCCESS     Asynchronous operation was successfully started.
 * @retval  NRF_ERROR_NULL  p_data was NULL.
 * @retval  Any other error code reported by SoftDevice API calls.
 */
ret_code_t nrf_dfu_settings_peer_data_write(nrf_dfu_peer_data_t * p_data);


/** @brief Function for copying peer data from DFU settings to RAM.
 *
 * @param[in,out] p_data    Structure to copy peer data to.
 *
 * @retval  NRF_SUCCESS     Peer data was successfully copied.
 * @retval  NRF_ERROR_NULL  p_data was NULL.
 */
ret_code_t nrf_dfu_settings_peer_data_copy(nrf_dfu_peer_data_t * p_data);


/** @brief Function for validating peer data in DFU settings.
 *
 * @retval  True if peer data is validated by CRC, false if not.
 */
bool nrf_dfu_settings_peer_data_is_valid(void);


/** @brief Function for storing an advertisement name received through an SVCI call in DFU settings.
 *
 * @note The content of the type is verifyable by a CRC-value stored inside the struct.
 *
 * @note The storage operation is an asynchronous progress. Success will be notified
 *       through system events raised by the SoftDevice.
 *
 * @param[in]   p_adv_name  Structure holding information about the new advertisement name.
 *
 * @retval  NRF_SUCCESS     Asynchronous operation was successfully started.
 * @retval  NRF_ERROR_NULL  p_adv_name was NULL.
 * @retval  Any other error code reported by SoftDevice API calls.
 */
ret_code_t nrf_dfu_settings_adv_name_write(nrf_dfu_adv_name_t * p_adv_name);


/** @brief Function for copying the advertisement name from DFU settings to RAM.
 *
 * @param[in,out]   p_adv_name  Structure to copy the new advertisement name to.
 *
 * @retval  NRF_SUCCESS     Advertisement name was successfully copied.
 * @retval  NRF_ERROR_NULL  p_adv_name was NULL.
 */
ret_code_t nrf_dfu_settings_adv_name_copy(nrf_dfu_adv_name_t * p_adv_name);


/** @brief Function for validating advertisement data in DFU settings.
 *
 * @retval  True if advertisement name is validated by CRC, false if not.
 */
bool nrf_dfu_settings_adv_name_is_valid(void);

#endif // NRF_DFU_TRANSPORT_BLE

/** @brief Function for erasing additional data in DFU settings.
 *
 * @note    Erasing additional data in DFU settings is only possible
 *          if nrf_dfu_flash is initialized to not use SoftDevice calls.
 *
 * @retval  NRF_SUCCESS     Additional data was successfully erased.
 * @retval  Any other error code reported by nrf_dfu_flash
 */
ret_code_t nrf_dfu_settings_additional_erase(void);


#ifdef __cplusplus
}
#endif

#endif // NRF_DFU_SETTINGS_H__

/**@} */
