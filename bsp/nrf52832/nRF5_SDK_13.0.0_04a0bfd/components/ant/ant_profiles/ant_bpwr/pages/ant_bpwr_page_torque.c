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
#if NRF_MODULE_ENABLED(ANT_BPWR)

#include <stdio.h>
#include "ant_bpwr_page_torque.h"
#include "ant_bpwr_utils.h"

#define NRF_LOG_MODULE_NAME "ANT_BPWR_PAGE_TORQUE"
#if ANT_BPWR_PAGE_TORQUE_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_BPWR_PAGE_TORQUE_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_BPWR_PAGE_TORQUE_INFO_COLOR
#else // ANT_BPWR_PAGE_TORQUE_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_BPWR_PAGE_TORQUE_LOG_ENABLED
#include "nrf_log.h"

/**@brief bicycle power page torque data layout structure. */
typedef struct
{
    uint8_t update_event_count;
    uint8_t tick;
    uint8_t reserved;
    uint8_t period[2];
    uint8_t accumulated_torque[2];
}ant_bpwr_page_torque_data_layout_t;

STATIC_ASSERT(ANT_BPWR_TORQUE_PERIOD_DISP_PRECISION == 1000); ///< Display format need to be updated
STATIC_ASSERT(ANT_BPWR_ACC_TORQUE_DISP_PRECISION == 10);      ///< Display format need to be updated

void ant_bpwr_page_torque_log(ant_bpwr_page_torque_data_t const * p_page_data)
{
    uint16_t period     = ANT_BPWR_TORQUE_PERIOD_RESCALE(p_page_data->period);
    uint32_t acc_torque = ANT_BPWR_ACC_TORQUE_RESCALE(p_page_data->accumulated_torque);

    NRF_LOG_INFO("event count:                    %u\r\n", p_page_data->update_event_count);
    NRF_LOG_INFO("tick:                           %u\r\n", p_page_data->tick);
    NRF_LOG_INFO("period:                         %u.%03us\r\n",
                  (unsigned int)(period / ANT_BPWR_TORQUE_PERIOD_DISP_PRECISION),
                  (unsigned int)(period % ANT_BPWR_TORQUE_PERIOD_DISP_PRECISION));
    NRF_LOG_INFO("accumulated torque:             %u.%01uNm\r\n",
                  (unsigned int)(acc_torque / ANT_BPWR_ACC_TORQUE_DISP_PRECISION),
                  (unsigned int)(acc_torque % ANT_BPWR_ACC_TORQUE_DISP_PRECISION));
}


void ant_bpwr_page_torque_encode(uint8_t                           * p_page_buffer,
                                 ant_bpwr_page_torque_data_t const * p_page_data)
{
    ant_bpwr_page_torque_data_layout_t * p_outcoming_data =
        (ant_bpwr_page_torque_data_layout_t *)p_page_buffer;

    p_outcoming_data->update_event_count    = p_page_data->update_event_count;
    p_outcoming_data->tick                  = p_page_data->tick;

    UNUSED_PARAMETER(uint16_encode(p_page_data->period, p_outcoming_data->period));
    UNUSED_PARAMETER(uint16_encode(p_page_data->accumulated_torque,
                                   p_outcoming_data->accumulated_torque));
}


void ant_bpwr_page_torque_decode(uint8_t const               * p_page_buffer,
                                 ant_bpwr_page_torque_data_t * p_page_data)
{
    ant_bpwr_page_torque_data_layout_t const * p_incoming_data =
        (ant_bpwr_page_torque_data_layout_t *)p_page_buffer;

    p_page_data->update_event_count    = p_incoming_data->update_event_count;
    p_page_data->tick                  = p_incoming_data->tick;
    p_page_data->period                = uint16_decode(p_incoming_data->period);
    p_page_data->accumulated_torque    = uint16_decode(p_incoming_data->accumulated_torque);
}

#endif // NRF_MODULE_ENABLED(ANT_BPWR)
