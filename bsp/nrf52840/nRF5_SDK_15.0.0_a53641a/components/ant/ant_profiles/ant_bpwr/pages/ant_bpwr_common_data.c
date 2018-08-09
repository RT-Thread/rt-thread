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
#if NRF_MODULE_ENABLED(ANT_BPWR)

#include "ant_bpwr_common_data.h"
#include "ant_bpwr_utils.h"

#define NRF_LOG_MODULE_NAME ant_bpwr_common
#if ANT_BPWR_COMMON_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_BPWR_COMMON_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_BPWR_COMMON_INFO_COLOR
#else // ANT_BPWR_COMMON_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_BPWR_COMMON_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief BPWR common page data layout structure. */
typedef struct
{
    uint8_t reserved0[2];
    uint8_t instantaneous_cadence;
    uint8_t reserved1[4];
}ant_bpwr_cadence_data_layout_t;

/**@brief Function for tracing common data.
 *
 * @param[in]  p_common_data      Pointer to the common data.
 */
static void cadence_data_log(ant_bpwr_common_data_t const * p_common_data)
{
    if (p_common_data->instantaneous_cadence == 0xFF)
    {
        NRF_LOG_INFO("instantaneous cadence:               -- rpm\r\n\n");
    }
    else
    {
        NRF_LOG_INFO("instantaneous cadence:               %u rpm\r\n\n",
                    p_common_data->instantaneous_cadence);
    }
}

void ant_bpwr_cadence_encode(uint8_t                     * p_page_buffer,
                            ant_bpwr_common_data_t const * p_common_data)
{
    ant_bpwr_cadence_data_layout_t * p_outcoming_data = (ant_bpwr_cadence_data_layout_t *)p_page_buffer;
    p_outcoming_data->instantaneous_cadence           = p_common_data->instantaneous_cadence;

    cadence_data_log(p_common_data);
}

void ant_bpwr_cadence_decode(uint8_t const         * p_page_buffer,
                            ant_bpwr_common_data_t * p_common_data)
{
    ant_bpwr_cadence_data_layout_t const * p_incoming_data = (ant_bpwr_cadence_data_layout_t *)p_page_buffer;
    p_common_data->instantaneous_cadence                   = p_incoming_data->instantaneous_cadence;

    cadence_data_log(p_common_data);
}

#endif // NRF_MODULE_ENABLED(ANT_BPWR)
