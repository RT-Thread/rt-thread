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
#ifndef ANT_ENCRYPT_NEGOTIATION_SLAVE_H__
#define ANT_ENCRYPT_NEGOTIATION_SLAVE_H__

/**@file
 *
 * @defgroup ant_encrypt_negotiation_slave ANT encryption negotiation
 * @{
 * @ingroup  ant_sdk_utils
 *
 * @brief    Encryption negotiation for encrypted ANT slave channels.
 *
 * After pairing, the slave starts negotiating the encryption with the master. After
 * successful negotiation, the slave can decrypt messages from the master, and all
 * future messages are sent encrypted.
 *
 */

#include <stdint.h>
#include "ant_stack_handler_types.h"
#include "ant_encrypt_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Encryption negotiation states for a slave channel. */
typedef enum
{
    ANT_ENC_CHANNEL_STAT_NOT_TRACKING,        ///< Not tracking the master.
    ANT_ENC_CHANNEL_STAT_TRACKING_ENCRYPTED,  ///< Tracking the master, but cannot decrypt messages.
    ANT_ENC_CHANNEL_STAT_NEGOTIATING,         ///< Encryption has been enabled and negotiation is in progress.
    ANT_ENC_CHANNEL_STAT_TRACKING_DECRYPTED,  ///< Tracking the master and can decrypt messages.
    ANT_ENC_CHANNEL_STAT_TRACKING_UNSUPPORTED ///< Tracking unsupported on this channel.
} ant_encrypt_tracking_state_t;


/**
 * @brief Function for setting the encryption negotiation state of a slave ANT channel.
 *
 * This function should be used by the @ref ant_encrypt_config module.
 *
 * @param[in] channel_number    ANT channel number.
 * @param[in] state             State to set.
 */
void ant_channel_encryp_tracking_state_set(uint8_t                      channel_number,
                                           ant_encrypt_tracking_state_t state);

/**
 * @brief Function for getting the encryption negotiation state of a slave ANT channel.
 *
 * @param[in] channel_number       ANT channel number.
 */
ant_encrypt_tracking_state_t ant_channel_encryp_tracking_state_get(uint8_t channel_number);

/**
 * @brief Function for initializing the module.
 *
 * This function initializes internal states of the module. It should
 * only be used by the @ref ant_encrypt_config module.
 *
 */
void ant_channel_encryp_negotiation_slave_init(void);

/**
 * @brief Function for setting the configuration for the slave channel.
 *
 * This function saves the channel's encryption configuration to a lookup table (LUT) for
 * future usage. The configuration can then be used to enable encryption.
 *
 * This function is intended to be used by the @ref ant_encrypt_config module.
 *
 * @param[in] channel_number   ANT channel number.
 * @param[in] p_crypto_config  Pointer to the encryption configuration.
 */
void ant_slave_channel_encrypt_config(uint8_t                                      channel_number,
                                      ant_encrypt_channel_settings_t const * const p_crypto_config);


/**
 * @brief Function for handling ANT encryption negotiation on slave nodes.
 *
 * This function should be used directly in the ANT event dispatching process. It
 * tries to enable slave channel encryption for all slave channels that are declared
 * as encrypted channels (if appropriate master channels are found).
 *
 * This function should be used by the @ref ant_encrypt_config module.
 *
 * @param[in] p_ant_evt  Pointer to the ANT stack event message structure.
 */
void ant_slave_encrypt_negotiation(ant_evt_t * p_ant_evt);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // ANT_ENCRYPT_NEGOTIATION_SLAVE_H__
