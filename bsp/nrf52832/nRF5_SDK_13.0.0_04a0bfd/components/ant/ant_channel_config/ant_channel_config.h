/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#ifndef ANT_CHANNEL_CONFIG_H__
#define ANT_CHANNEL_CONFIG_H__

/** @file
 *
 * @defgroup ant_channel_config ANT channel configuration
 * @{
 * @ingroup ant_sdk_utils
 * @brief ANT channel configuration module.
 */

#include <stdint.h>
#include "sdk_config.h"


#ifndef ANT_CONFIG_ENCRYPTED_CHANNELS
    #error Undefined ANT_CONFIG_ENCRYPTED_CHANNELS. It should be defined in sdk_config.h file.
#elif ANT_CONFIG_ENCRYPTED_CHANNELS > 0
    #include "ant_encrypt_config.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**@brief ANT channel configuration structure. */
typedef struct
{
    uint8_t  channel_number;        ///< Assigned channel number.
    uint8_t  channel_type;          ///< Channel type (see Assign Channel Parameters in ant_parameters.h: @ref ant_parameters).
    uint8_t  ext_assign;            ///< Extended assign (see Ext. Assign Channel Parameters in ant_parameters.h: @ref ant_parameters).
    uint8_t  rf_freq;               ///< Radio frequency offset from 2400 MHz (for example, 2466 MHz, rf_freq = 66).
    uint8_t  transmission_type;     ///< Transmission type.
    uint8_t  device_type;           ///< Device type.
    uint16_t device_number;         ///< Device number.
    uint16_t channel_period;        ///< The period in 32 kHz counts.
    uint8_t  network_number;        ///< Network number denoting the network key.

#if ANT_CONFIG_ENCRYPTED_CHANNELS > 0
    ant_encrypt_channel_settings_t * p_crypto_settings; ///< Pointer to cryptographic settings, NULL if this configuration have to be omitted.
#endif

} ant_channel_config_t;

/**@brief Function for configuring the ANT channel.
 *
 * @param[in]  p_config        Pointer to the channel configuration structure.
 *
 * @retval     NRF_SUCCESS     If the channel was successfully configured. Otherwise, an error code is returned.
 */
uint32_t ant_channel_init(ant_channel_config_t const * p_config);


#ifdef __cplusplus
}
#endif

#endif // ANT_CHANNEL_CONFIG_H__
/** @} */
