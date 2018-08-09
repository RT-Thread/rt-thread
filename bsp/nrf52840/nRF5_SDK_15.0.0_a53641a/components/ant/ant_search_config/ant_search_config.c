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
#if NRF_MODULE_ENABLED(ANT_SEARCH_CONFIG)

#include "ant_search_config.h"
#include "ant_interface.h"

uint32_t ant_search_init(ant_search_config_t const * p_config)
{
    uint32_t err_code;

    if (p_config->low_priority_timeout == ANT_LOW_PRIORITY_SEARCH_DISABLE
     && p_config->high_priority_timeout == ANT_HIGH_PRIORITY_SEARCH_DISABLE)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    err_code = sd_ant_search_channel_priority_set(p_config->channel_number,
                                                  p_config->search_priority);
    VERIFY_SUCCESS(err_code);

    err_code = sd_ant_search_waveform_set(p_config->channel_number,
                                          p_config->waveform);
    VERIFY_SUCCESS(err_code);

    err_code = sd_ant_channel_rx_search_timeout_set(p_config->channel_number,
                                                    p_config->high_priority_timeout);
    VERIFY_SUCCESS(err_code);

    err_code = sd_ant_channel_low_priority_rx_search_timeout_set(p_config->channel_number,
                                                                 p_config->low_priority_timeout);
    VERIFY_SUCCESS(err_code);

    err_code = sd_ant_active_search_sharing_cycles_set(p_config->channel_number,
                                                       p_config->search_sharing_cycles);
    return err_code;
}

#endif // NRF_MODULE_ENABLED(ANT_SEARCH_CONFIG)
