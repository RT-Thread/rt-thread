/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(ANT_ENCRYPT_NEGOTIATION_SLAVE)
#include <stdlib.h>
#include <string.h>
#include "ant_encrypt_config.h"
#include "ant_interface.h"
#include "ant_parameters.h"
#include "nrf_error.h"
#include "app_error.h"

#include "ant_encrypt_negotiation_slave.h"

/** Number of supported channels. */
#define NUMBER_OF_CHANNELS (NRF_SDH_ANT_TOTAL_CHANNELS_ALLOCATED)

/** Flag to block other channels from attempting to enable encryption while
 * another encryption is in the process.
 */
static volatile bool m_can_enable_crypto = true;

/** Array to keep track of which channels are currently tracking. */
static ant_encrypt_tracking_state_t m_encrypt_channel_states[NUMBER_OF_CHANNELS];

/** Array for the slave channels' encryption settings. */
static ant_encrypt_channel_settings_t m_slave_channel_conf[MAX_ANT_CHANNELS];



void ant_channel_encryp_tracking_state_set(uint8_t                      channel_number,
                                           ant_encrypt_tracking_state_t state)
{
    m_encrypt_channel_states[channel_number] = state;
}


void ant_channel_encryp_negotiation_slave_init(void)
{
    for (uint32_t channel = 0; channel < NUMBER_OF_CHANNELS; channel++)
    {
        ant_channel_encryp_tracking_state_set(channel, ANT_ENC_CHANNEL_STAT_TRACKING_UNSUPPORTED);
    }

    m_can_enable_crypto   = true;
}


ant_encrypt_tracking_state_t ant_channel_encryp_tracking_state_get(uint8_t channel_number)
{
    return m_encrypt_channel_states[channel_number];
}


void ant_slave_channel_encrypt_config(uint8_t                                      channel_number,
                                      ant_encrypt_channel_settings_t const * const p_crypto_config)
{
    memcpy(&m_slave_channel_conf[channel_number], p_crypto_config,
           sizeof(ant_encrypt_channel_settings_t));
}


/**@brief Function for handling ANT RX channel events.
 *
 * @param[in] p_event_message_buffer The ANT event message buffer.
 */
static void ant_slave_encrypt_try_enable(uint8_t ant_channel,
                                         uint8_t ant_message_id)
{
    uint32_t                     err_code;
    ant_encrypt_tracking_state_t track_stat;


    switch (ant_message_id)
    {
        // Broadcast data received.
        case MESG_BROADCAST_DATA_ID:

            track_stat = ant_channel_encryp_tracking_state_get(ant_channel);
            // If the encryption has not yet been negotiated for this channel and another channel
            // is not currently trying to enable encryption, enable encryption
            if ((track_stat != ANT_ENC_CHANNEL_STAT_TRACKING_DECRYPTED)
                && (track_stat != ANT_ENC_CHANNEL_STAT_NEGOTIATING)
                && m_can_enable_crypto)
            {
                // Block other channels from trying to enable encryption until this channel
                // is finished
                m_can_enable_crypto = false;
                ant_channel_encryp_tracking_state_set(ant_channel,
                                                      ANT_ENC_CHANNEL_STAT_NEGOTIATING);

                // Enable encryption on ant_channel
                err_code =
                    ant_channel_encrypt_config_perform(ant_channel,
                                                       &m_slave_channel_conf[ant_channel]);
                APP_ERROR_CHECK(err_code);
            }
            break;

        default:
            break;
    }
}


void ant_slave_encrypt_negotiation(ant_evt_t * p_ant_evt)
{
    ant_encrypt_tracking_state_t track_state =
        ant_channel_encryp_tracking_state_get(p_ant_evt->channel);

    if (track_state == ANT_ENC_CHANNEL_STAT_TRACKING_UNSUPPORTED)
        return;

    switch (p_ant_evt->event)
    {
        case EVENT_RX_FAIL_GO_TO_SEARCH:
            if (track_state == ANT_ENC_CHANNEL_STAT_NEGOTIATING)
            {
                m_can_enable_crypto = true;
            }

            ant_channel_encryp_tracking_state_set(p_ant_evt->channel,
                                                  ANT_ENC_CHANNEL_STAT_NOT_TRACKING);
            break;

        case EVENT_RX:
            ant_slave_encrypt_try_enable(p_ant_evt->channel,
                                         p_ant_evt->message.ANT_MESSAGE_ucMesgID);
            break;

        case EVENT_ENCRYPT_NEGOTIATION_SUCCESS:
            m_can_enable_crypto = true;
            ant_channel_encryp_tracking_state_set(p_ant_evt->channel,
                                                  ANT_ENC_CHANNEL_STAT_TRACKING_DECRYPTED);
            break;

        case EVENT_ENCRYPT_NEGOTIATION_FAIL:
            m_can_enable_crypto = true;
            ant_channel_encryp_tracking_state_set(p_ant_evt->channel,
                                                  ANT_ENC_CHANNEL_STAT_TRACKING_ENCRYPTED);
            break;

        default:
            break;
    }
}

#endif // NRF_MODULE_ENABLED(ANT_ENCRYPT_NEGOTIATION_SLAVE)
