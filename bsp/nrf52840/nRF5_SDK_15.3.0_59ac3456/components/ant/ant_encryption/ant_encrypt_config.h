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
#ifndef ANT_ENCRYPT_CONFIG__
#define ANT_ENCRYPT_CONFIG__

/**@file
 *
 * @defgroup ant_encrypt_config ANT encryption configuration
 * @{
 * @ingroup  ant_sdk_utils
 *
 * @brief    Encryption configuration for the ANT stack and channels.
 *
 */

#include <stdint.h>

#include "sdk_errors.h"
#include "nrf_sdh_ant.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @name Advanced burst configuration for encryption modules
 * @{
 */
#define ADV_BURST_CFG_MIN_SIZE          8 ///< Minimum size of the advance burst configuration data.
#define ADV_BURST_CFG_PACKET_SIZE_INDEX 1 ///< Index of the packet size field in the configuration data.
#define ADV_BURST_CFG_REQUIRED_FEATURES 2 ///< Index of the required features field in the configuration data.
#define ADV_BURST_CFG_OPTIONAL_FEATURES 5 ///< Index of the optional features field in the configuration data.
/**@} */

/** @brief ANT channel cryptographic configuration. */
typedef struct
{
    uint8_t mode;            ///< Encryption mode. See the encrypted channel defines in ant_parameters.h.
    uint8_t key_index;       ///< Index of encryption key.
    uint8_t decimation_rate; ///< Division of the master channel rate by the slave’s tracking channel rate.
} ant_encrypt_channel_settings_t;

/** @brief ANT encryption information. */
typedef union
{
    uint8_t * pp_array[3]; // For array access support.
    struct
    {
        uint8_t * p_encryption_id;   ///< Pointer to the encryption ID of the device (4 bytes).
        uint8_t * p_user_info;       ///< Pointer to the user information string (19 bytes).
        uint8_t * p_random_num_seed; ///< Pointer to the random number seed (16 bytes).
    } items;
} ant_encrypt_info_settings_t;

/** @brief Advanced burst settings used by the encrypted channel. */
typedef struct
{
    uint8_t packet_length;    ///< RF payload size. See the advanced burst configuration defines in ant_parameters.h.
    uint8_t required_feature; ///< Required advanced burst modes. See the advanced burst configuration defines in ant_parameters.h.
    uint8_t optional_feature; ///< Optional advanced burst modes. See the advanced burst configuration defines in ant_parameters.h.
} ant_encrypt_adv_burst_settings_t;

/**@brief ANT stack cryptographic configuration. */
typedef struct
{
    ant_encrypt_info_settings_t        info;               ///< Pointer to the encryption information structure.
    uint8_t                        * * pp_key;             ///< Pointer to an array for pointers to encryption keys. Each key must have a length of 16 bytes.
    uint8_t                            key_number;         ///< Number of encryption keys.
    ant_encrypt_adv_burst_settings_t * p_adv_burst_config; ///< Advanced burst configuration. If NULL, the advanced burst must be configured externally.
} ant_encrypt_stack_settings_t;

/**
 * @brief ANT encryption negotiation events.
 */
typedef enum
{
    ANT_ENC_EVT_NEGOTIATION_SUCCESS, ///< Negotiation success.
    ANT_ENC_EVT_NEGOTIATION_FAIL,    ///< Negotiation failure.
    ANT_ENC_EVT_CHANNEL_LOST         ///< Lost a channel. It's relevant only for slave channels.
} ant_encrypt_user_evt_t;

/**
 * @brief Event handler for ANT encryption user events.
 */
typedef void (* ant_encryp_user_handler_t)(uint8_t channel, ant_encrypt_user_evt_t event);

/**
 * @brief Macro for initializing an ANT encryption information structure.
 *
 * @param[in] P_ENC_ID         Pointer to the encryption ID of the device (4 bytes).
 * @param[in] P_USER_INFO      Pointer to the user information string (19 bytes).
 * @param[in] P_RAND_NUM_SEED  Pointer to the random number seed (16 bytes).
 */
#define ANT_CRYPTO_INFO_SETTINGS_INIT(P_ENC_ID, P_USER_INFO, P_RAND_NUM_SEED) \
    {                                                                         \
        .items =                                                              \
        {                                                                     \
            .p_encryption_id   = P_ENC_ID,                                    \
            .p_user_info       = P_USER_INFO,                                 \
            .p_random_num_seed = P_RAND_NUM_SEED                              \
        }                                                                     \
    }

/**
 * @brief Macro for declaring the basic cryptographic configuration for the ANT stack.
 *
 * This macro configures the following settings:
 * - Cryptographic key
 * - Encryption ID
 * - Advanced burst mode with the maximum RF payload size
 *
 * Use @ref ANT_ENCRYPT_STACK_SETTINGS_BASE to access the created configuration instance.
 *
 * @param[in] NAME   Name for the created data instance.
 * @param[in] P_KEY  Pointer to the cryptographic key (16 bytes).
 * @param[in] P_ENC_ID Pointer to the encryption ID (4 bytes).
 */
#define ANT_ENCRYPT_STACK_SETTINGS_BASE_DEF(NAME, P_KEY, P_ENC_ID)                 \
    ant_encrypt_adv_burst_settings_t NAME##_ant_enc_adv_burst_set =                \
    {                                                                              \
        .packet_length    = ADV_BURST_MODES_MAX_SIZE,                              \
        .required_feature = 0,                                                     \
        .optional_feature = 0                                                      \
    };                                                                             \
    uint8_t                    * pp_##NAME##_key[1] = {P_KEY};                     \
    ant_encrypt_stack_settings_t NAME ## _ant_crypto_settings =                    \
    {                                                                              \
        .info               = ANT_CRYPTO_INFO_SETTINGS_INIT(P_ENC_ID, NULL, NULL), \
        .pp_key             = pp_##NAME##_key,                                     \
        .key_number         = 1,                                                   \
        .p_adv_burst_config = &NAME##_ant_enc_adv_burst_set                        \
    }


/** @brief Macro for accessing the configuration instance created
 *  by @ref ANT_ENCRYPT_STACK_SETTINGS_BASE_DEF.
 *
 * @param[in] NAME   Name of the settings instance.
 */
#define ANT_ENCRYPT_STACK_SETTINGS_BASE(NAME) (NAME##_ant_crypto_settings)

/**
 * @brief Function for applying an encryption configuration to a slave channel.
 *
 * This function enables encryption on a channel.
 *
 * This function should be used by the @ref ant_encrypt_negotiation_slave module and this module.
 *
 * @param[in] channel_number   ANT channel number.
 * @param[in] p_crypto_config  Pointer to the encryption configuration.
 *
 * @return Value returned by @ref sd_ant_crypto_channel_enable (for example, NRF_SUCCESS if
 * the configuration was successful).
 */
ret_code_t ant_channel_encrypt_config_perform(uint8_t                          channel_number,
                                              ant_encrypt_channel_settings_t * p_crypto_config);

/**
 * @brief Function for applying an encryption configuration to a master or slave channel.
 *
 * When called for a master channel, this function enables encryption
 * for that channel. When called for a slave channel, it saves
 * the encryption configuration for future use.
 *
 * This function should be used by the @ref ant_channel_config module.
 *
 * @param[in] channel_type     ANT channel type: CHANNEL_TYPE_SLAVE or CHANNEL_TYPE_MASTER.
 * @param[in] channel_num      ANT channel number.
 * @param[in] p_crypto_config  Pointer to the encryption configuration.
 *
 * @retval NRF_SUCCESS                      If the function completed successfully.
 * @retval NRF_ERROR_INVALID_PARAM          If the channel type is invalid.
 * @retval NRF_ERROR_MODULE_NOT_INITIALIZED  If the stack is not configured for encryption.
 * @retval Other                            Otherwise, the error value returned by the @ref
 *                                          ant_channel_encrypt_config_perform function is returned.
 */
ret_code_t ant_channel_encrypt_config(uint8_t                          channel_type,
                                      uint8_t                          channel_num,
                                      ant_encrypt_channel_settings_t * p_crypto_config);

/**
 * @brief Function for configuring the cryptographic settings of the ANT stack.
 *
 * @param[in] p_crypto_info_set Pointer to the settings.
 */
ret_code_t ant_stack_encryption_config(ant_encrypt_stack_settings_t const * const p_crypto_info_set);

/**
 * @brief Function for registering an event handler for ANT encryption events.
 *
 * The event handler should support all of the events in @ref ant_encrypt_user_evt_t.
 *
 * @param[in] p_handler Pointer to a handler function.
 */
void ant_enc_event_handler_register(ant_encryp_user_handler_t p_handler);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // ANT_ENCRYPT_CONFIG__
