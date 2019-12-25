/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#ifndef ANT_KEY_MANAGER_H__
#define ANT_KEY_MANAGER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 */
/**
 * @defgroup ant_key_manager ANT key manager
 * @{
 * @ingroup ant_sdk_utils
 * @brief Module for registering common and custom ANT network keys.
 */

/**@brief Function for registering a custom network key.
 *
 * @param[in]  network_number   Network key number.
 * @param[in]  p_network_key    Pointer to the custom ANT network key.
 *
 * @return A SoftDevice error code.
 */
uint32_t ant_custom_key_set(uint8_t network_number, uint8_t * p_network_key);

/**@brief Function for registering an ANT+ network key.
 *
 * The key must be defined by @ref ANT_PLUS_NETWORK_KEY.
 *
 * @note The ANT+ Network Key is available for ANT+ Adopters. Go to http://thisisant.com
 *       to become an ANT+ Adopter and access the key.
 *
 * @param[in]  network_number   Network key number.
 *
 * @return A SoftDevice error code.
 */
uint32_t ant_plus_key_set(uint8_t network_number);

/**@brief Function for registering an ANT-FS network key.
 *
 * The key must be defined by @ref ANT_FS_NETWORK_KEY.
 *
 * @note The ANT+ Network Key is available for ANT+ Adopters. Go to http://thisisant.com
 *       to become an ANT+ Adopter and access the key.
 *
 * @param[in]  network_number   Network key number.
 *
 * @return A SoftDevice error code.
 */
uint32_t ant_fs_key_set(uint8_t network_number);


/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif // ANT_KEY_MANAGER_H__
