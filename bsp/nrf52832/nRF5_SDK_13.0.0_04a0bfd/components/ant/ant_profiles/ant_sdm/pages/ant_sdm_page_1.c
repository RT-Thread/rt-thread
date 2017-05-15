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
#if NRF_MODULE_ENABLED(ANT_SDM)

#include "ant_sdm_page_1.h"
#include "ant_sdm_utils.h"

#define NRF_LOG_MODULE_NAME "ANT_SDM_PAGE_1"
#if ANT_SDM_PAGE_1_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_SDM_PAGE_1_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_SDM_PAGE_1_INFO_COLOR
#else // ANT_SDM_PAGE_1_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_SDM_PAGE_1_LOG_ENABLED
#include "nrf_log.h"

/**@brief SDM page 1 data layout structure. */
typedef struct
{
    uint8_t time_fractional;
    uint8_t time_integer;
    uint8_t distance_integer;
    uint8_t reserved0           : 4;
    uint8_t distance_fractional : 4;
    uint8_t reserved1;
    uint8_t strides;
    uint8_t update_latency;
}ant_sdm_page1_data_layout_t;

STATIC_ASSERT(ANT_SDM_UPDATE_LATENCY_DISP_PRECISION == 1000); ///< Display format need to be updated
STATIC_ASSERT(ANT_SDM_TIME_DISP_PRECISION == 1000);           ///< Display format need to be updated
STATIC_ASSERT(ANT_SDM_DISTANCE_DISP_PRECISION == 10);         ///< Display format need to be updated

/**@brief Function for tracing page 1 and common data.
 *
 * @param[in]  p_common_data    Pointer to the common data.
 * @param[in]  p_page_data      Pointer to the page 1 data.
 */
static void page_1_data_log(ant_sdm_page1_data_t const  * p_page_data,
                            ant_sdm_common_data_t const * p_common_data)
{
    uint32_t strides        = p_common_data->strides;
    uint64_t distance       = ANT_SDM_DISTANCE_RESCALE(p_common_data->distance);
    uint16_t update_latency = ANT_SDM_UPDATE_LATENCY_RESCALE(p_page_data->update_latency);
    uint32_t time           = ANT_SDM_TIME_RESCALE(p_page_data->time);

    NRF_LOG_INFO("Update latency                        %u.%03u s\r\n",
              update_latency / ANT_SDM_UPDATE_LATENCY_DISP_PRECISION,
              update_latency % ANT_SDM_UPDATE_LATENCY_DISP_PRECISION);
    NRF_LOG_INFO("Time                                  %u.%03u s\r\n",
              (unsigned int)(time / ANT_SDM_TIME_DISP_PRECISION),
              (unsigned int)(time % ANT_SDM_TIME_DISP_PRECISION));
    NRF_LOG_INFO("Distance                              %u.%01um \r\n",
              (unsigned int)(distance / ANT_SDM_DISTANCE_DISP_PRECISION),
              (unsigned int)(distance % ANT_SDM_DISTANCE_DISP_PRECISION));
    NRF_LOG_INFO("Strides                               %u\r\n", (unsigned int)strides);
}


void ant_sdm_page_1_encode(uint8_t                     * p_page_buffer,
                           ant_sdm_page1_data_t const  * p_page_data,
                           ant_sdm_common_data_t const * p_common_data)
{
    ant_sdm_page1_data_layout_t * p_outcoming_data = (ant_sdm_page1_data_layout_t *)p_page_buffer;
    uint32_t                      distance         = p_common_data->distance;
    uint16_t                      time             = p_page_data->time;

    p_outcoming_data->time_fractional  = time % ANT_SDM_TIME_UNIT_REVERSAL;
    p_outcoming_data->time_integer     = time / ANT_SDM_TIME_UNIT_REVERSAL;
    p_outcoming_data->distance_integer =
        (UINT8_MAX & (distance / ANT_SDM_DISTANCE_UNIT_REVERSAL)); // Only LSB
    p_outcoming_data->distance_fractional = distance % ANT_SDM_DISTANCE_UNIT_REVERSAL;
    p_outcoming_data->strides             = (UINT8_MAX & p_common_data->strides); // Only LSB
    p_outcoming_data->update_latency      = p_page_data->update_latency;

    page_1_data_log(p_page_data, p_common_data);
}


void ant_sdm_page_1_decode(uint8_t const         * p_page_buffer,
                           ant_sdm_page1_data_t  * p_page_data,
                           ant_sdm_common_data_t * p_common_data)
{
    ant_sdm_page1_data_layout_t const * p_incoming_data =
        (ant_sdm_page1_data_layout_t *)p_page_buffer;

    uint16_t distance = p_incoming_data->distance_integer * ANT_SDM_DISTANCE_UNIT_REVERSAL
                        + p_incoming_data->distance_fractional;
    uint16_t time     = p_incoming_data->time_integer * ANT_SDM_TIME_UNIT_REVERSAL
                        + p_incoming_data->time_fractional;

    uint8_t prev_strides = p_common_data->strides;

    p_common_data->strides += ((p_incoming_data->strides - prev_strides) & UINT8_MAX);

    uint16_t prev_distance = p_common_data->distance;
    p_common_data->distance += ((distance - prev_distance) & 0xFFF);

    p_page_data->update_latency = p_incoming_data->update_latency;
    p_page_data->time           = time;
    p_page_data->strides        = p_incoming_data->strides;

    page_1_data_log(p_page_data, p_common_data);
}

#endif // NRF_MODULE_ENABLED(ANT_SDM)
