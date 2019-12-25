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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_BSC)

#include "ant_bsc_page_2.h"

#define NRF_LOG_MODULE_NAME ant_bcs_page_2
#if ANT_BSC_PAGE_2_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_BSC_PAGE_2_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_BSC_PAGE_2_INFO_COLOR
#else // ANT_BSC_PAGE_2_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_BSC_PAGE_2_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief BSC page 2 data layout structure. */
typedef struct
{
    uint8_t manuf_id;
    uint8_t serial_num_LSB;
    uint8_t serial_num_MSB;
    uint8_t reserved[4];
}ant_bsc_page2_data_layout_t;

/**@brief Function for printing speed or cadence page2 data. */
static void page2_data_log(ant_bsc_page2_data_t const * p_page_data)
{
    NRF_LOG_INFO("Manufacturer ID:           %u", (unsigned int)p_page_data->manuf_id);
    NRF_LOG_INFO("Serial No (upper 16-bits): 0x%X",
              (unsigned int)p_page_data->serial_num);
}

void ant_bsc_page_2_encode(uint8_t * p_page_buffer, ant_bsc_page2_data_t const * p_page_data)
{
    ant_bsc_page2_data_layout_t * p_outcoming_data = (ant_bsc_page2_data_layout_t *)p_page_buffer;
    uint32_t serial_num                            = p_page_data->serial_num;

    p_outcoming_data->manuf_id       = (uint8_t)p_page_data->manuf_id;
    p_outcoming_data->serial_num_LSB = (uint8_t)(serial_num & UINT8_MAX);
    p_outcoming_data->serial_num_MSB = (uint8_t)((serial_num >> 8) & UINT8_MAX);

    page2_data_log( p_page_data);
}

void ant_bsc_page_2_decode(uint8_t const * p_page_buffer, ant_bsc_page2_data_t * p_page_data)
{
    ant_bsc_page2_data_layout_t const * p_incoming_data = (ant_bsc_page2_data_layout_t *)p_page_buffer;
    uint32_t serial_num = (uint32_t)((p_incoming_data->serial_num_MSB << 8)
                          + p_incoming_data->serial_num_LSB);

    p_page_data->manuf_id            = (uint32_t)p_incoming_data->manuf_id;
    p_page_data->serial_num          = serial_num;

    page2_data_log( p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_BSC)
