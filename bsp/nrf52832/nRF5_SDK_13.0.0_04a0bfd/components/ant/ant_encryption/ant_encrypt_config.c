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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_ENCRYPT_CONFIG)
#include <stdlib.h>
#include "ant_encrypt_config.h"
#include "ant_interface.h"
#include "ant_parameters.h"

#ifdef ANT_ENCRYPT_NEGOTIATION_SLAVE_ENABLED
    #include "ant_encrypt_negotiation_slave.h"
#endif

 /*lint -e551 -save*/
/** Flag for checking if stack was configured for encryption. */
static bool m_stack_encryption_configured = false;
 /*lint -restore */

 /** Pointer to handler of module's events. */
static ant_encryp_user_handler_t m_ant_enc_evt_handler = NULL;

static ret_code_t ant_enc_advance_burs_config_apply(
    ant_encrypt_adv_burst_settings_t const * const p_adv_burst_set);

ret_code_t ant_stack_encryption_config(ant_encrypt_stack_settings_t const * const p_crypto_set)
{
    ret_code_t err_code;

    for ( uint32_t i = 0; i < p_crypto_set->key_number; i++)
    {
        err_code = sd_ant_crypto_key_set(i, p_crypto_set->pp_key[i]);
        VERIFY_SUCCESS(err_code);
    }

    if (p_crypto_set->p_adv_burst_config != NULL)
    {
        err_code = ant_enc_advance_burs_config_apply(p_crypto_set->p_adv_burst_config);
        VERIFY_SUCCESS(err_code);
    }

    // subcomands LUT for @ref sd_ant_crypto_info_set calls
    const uint8_t set_enc_info_param_lut[] =
    {
        ENCRYPTION_INFO_SET_CRYPTO_ID,
        ENCRYPTION_INFO_SET_CUSTOM_USER_DATA,
        ENCRYPTION_INFO_SET_RNG_SEED
    };

    for ( uint32_t i = 0; i < sizeof(set_enc_info_param_lut); i++)
    {
        if ( p_crypto_set->info.pp_array[i] != NULL)
        {
            err_code = sd_ant_crypto_info_set(set_enc_info_param_lut[i],
                                              p_crypto_set->info.pp_array[i]);

            VERIFY_SUCCESS(err_code);
        }
    }

    #ifdef ANT_ENCRYPT_NEGOTIATION_SLAVE_ENABLED
        // all ANT channels have unsupported slave encryption tracking (even master's channel)
        ant_channel_encryp_negotiation_slave_init();
    #endif

    m_ant_enc_evt_handler = NULL;

    m_stack_encryption_configured = true;

    return NRF_SUCCESS;
}


/**
 * @brief Function for configuring advanced burst settings according to encryption requirements.
 *
 * @param p_adv_burst_set  Pointer to ANT advanced burst settings.
 *
 * @retval Value returned by @ref sd_ant_adv_burst_config_set.
 */
static ret_code_t ant_enc_advance_burs_config_apply(
    ant_encrypt_adv_burst_settings_t const * const p_adv_burst_set)
{
    uint8_t adv_burst_conf_str[ADV_BURST_CFG_MIN_SIZE] =
    { ADV_BURST_MODE_ENABLE, 0, 0, 0, 0, 0, 0, 0 };

    adv_burst_conf_str[ADV_BURST_CFG_PACKET_SIZE_INDEX] = p_adv_burst_set->packet_length;
    adv_burst_conf_str[ADV_BURST_CFG_REQUIRED_FEATURES] = p_adv_burst_set->required_feature;
    adv_burst_conf_str[ADV_BURST_CFG_OPTIONAL_FEATURES] = p_adv_burst_set->optional_feature;

    return sd_ant_adv_burst_config_set(adv_burst_conf_str, sizeof(adv_burst_conf_str));
}


ret_code_t ant_channel_encrypt_config_perform(uint8_t                          channel_number,
                                              ant_encrypt_channel_settings_t * p_crypto_config)
{
    return sd_ant_crypto_channel_enable(channel_number,
                                        p_crypto_config->mode,
                                        p_crypto_config->key_index,
                                        p_crypto_config->decimation_rate);
}


ret_code_t ant_channel_encrypt_config(uint8_t                          channel_type,
                                      uint8_t                          channel_number,
                                      ant_encrypt_channel_settings_t * p_crypto_config)
{
    ret_code_t err_code;

    if (p_crypto_config != NULL)
    {
        // encryption of the stack should be initialized previously
        if (m_stack_encryption_configured == false)
        {
            return NRF_ERROR_MODULE_NOT_INITIALZED;
        }

        switch (channel_type)
        {
            case CHANNEL_TYPE_MASTER:
                err_code = ant_channel_encrypt_config_perform(channel_number, p_crypto_config);
#ifdef ANT_ENCRYPT_NEGOTIATION_SLAVE_ENABLED
                ant_channel_encryp_tracking_state_set(channel_number,
                                                      ANT_ENC_CHANNEL_STAT_TRACKING_UNSUPPORTED);
#endif
                break;

#ifdef ANT_ENCRYPT_NEGOTIATION_SLAVE_ENABLED
            case CHANNEL_TYPE_SLAVE:
                ant_slave_channel_encrypt_config(channel_number, p_crypto_config);

                if (p_crypto_config->mode == ENCRYPTION_DISABLED_MODE)
                {
                    err_code = ant_channel_encrypt_config_perform(channel_number, p_crypto_config);
                    ant_channel_encryp_tracking_state_set(channel_number,
                                                          ANT_ENC_CHANNEL_STAT_TRACKING_UNSUPPORTED);
                }
                else
                {
                    ant_channel_encryp_tracking_state_set(channel_number,
                                                          ANT_ENC_CHANNEL_STAT_NOT_TRACKING);
                    err_code = NRF_SUCCESS;
                }
                break;
#endif

            default:
                err_code = NRF_ERROR_INVALID_PARAM;
                break;
        }
    }
    else
    {
#ifdef ANT_ENCRYPT_NEGOTIATION_SLAVE_ENABLED
        ant_channel_encryp_tracking_state_set(channel_number,
                                              ANT_ENC_CHANNEL_STAT_TRACKING_UNSUPPORTED);
#endif
        err_code = NRF_SUCCESS;
    }

    return err_code;
}

/** @brief Function for calling the handler of module events.*/
static void ant_encrypt_user_handler_try_to_run(uint8_t ant_channel, ant_encrypt_user_evt_t event)
{
    if (m_ant_enc_evt_handler != NULL)
    {
        m_ant_enc_evt_handler(ant_channel, event);
    }
}

void ant_encrypt_event_handler(ant_evt_t * p_ant_evt)
{
    uint8_t const ant_channel = p_ant_evt->channel;

#ifdef ANT_ENCRYPT_NEGOTIATION_SLAVE_ENABLED
    ant_slave_encrypt_negotiation(p_ant_evt);
#endif

    switch (p_ant_evt->event)
    {
        case EVENT_RX_FAIL_GO_TO_SEARCH:
            ant_encrypt_user_handler_try_to_run(ant_channel, ANT_ENC_EVT_CHANNEL_LOST);
            break;

        case EVENT_ENCRYPT_NEGOTIATION_SUCCESS:
             ant_encrypt_user_handler_try_to_run(ant_channel, ANT_ENC_EVT_NEGOTIATION_SUCCESS);
             break;

        case EVENT_ENCRYPT_NEGOTIATION_FAIL:
            ant_encrypt_user_handler_try_to_run(ant_channel, ANT_ENC_EVT_NEGOTIATION_FAIL);
            break;
    }
}

void ant_enc_event_handler_register(ant_encryp_user_handler_t user_handler_func)
{
    m_ant_enc_evt_handler = user_handler_func;
}

#endif // NRF_MODULE_ENABLED(ANT_ENCRYPT_CONFIG)
