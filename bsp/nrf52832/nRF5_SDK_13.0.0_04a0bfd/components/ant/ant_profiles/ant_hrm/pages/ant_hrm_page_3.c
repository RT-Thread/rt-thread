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
#if NRF_MODULE_ENABLED(ANT_HRM)

#include "ant_hrm_page_3.h"

#define NRF_LOG_MODULE_NAME "ANT_HRM_PAGE_3"
#if ANT_HRM_PAGE_3_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_HRM_PAGE_3_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_HRM_PAGE_3_INFO_COLOR
#else // ANT_HRM_PAGE_3_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_HRM_PAGE_3_LOG_ENABLED
#include "nrf_log.h"

/**@brief HRM page 3 data layout structure. */
typedef struct
{
    uint8_t hw_version;
    uint8_t sw_version;
    uint8_t model_num;
    uint8_t reserved[4];
}ant_hrm_page3_data_layout_t;

/**@brief Function for tracing page 3 and common data.
 *
 * @param[in]  p_common_data    Pointer to the common data.
 * @param[in]  p_page_data      Pointer to the page 3 data.
 */
static void page3_data_log(ant_hrm_page3_data_t const * p_page_data)
{
    NRF_LOG_INFO("Hardware Rev ID                   %u\r\n", (unsigned int)p_page_data->hw_version);
    NRF_LOG_INFO("Model                             %u\r\n", (unsigned int)p_page_data->model_num);
    NRF_LOG_INFO("Software Ver ID                   %u\r\n\n", (unsigned int)p_page_data->sw_version);
}


void ant_hrm_page_3_encode(uint8_t                    * p_page_buffer,
                           ant_hrm_page3_data_t const * p_page_data)
{
    ant_hrm_page3_data_layout_t * p_outcoming_data = (ant_hrm_page3_data_layout_t *)p_page_buffer;

    p_outcoming_data->hw_version = (uint8_t)p_page_data->hw_version;
    p_outcoming_data->sw_version = (uint8_t)p_page_data->sw_version;
    p_outcoming_data->model_num  = (uint8_t)p_page_data->model_num;

    page3_data_log(p_page_data);
}


void ant_hrm_page_3_decode(uint8_t const        * p_page_buffer,
                           ant_hrm_page3_data_t * p_page_data)
{
    ant_hrm_page3_data_layout_t const * p_incoming_data =
        (ant_hrm_page3_data_layout_t *)p_page_buffer;

    p_page_data->hw_version = (uint32_t)p_incoming_data->hw_version;
    p_page_data->sw_version = (uint32_t)p_incoming_data->sw_version;
    p_page_data->model_num  = (uint32_t)p_incoming_data->model_num;

    page3_data_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_HRM)
