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

#include "ant_bsc_page_4.h"
#include "ant_bsc_utils.h"
#include "app_util.h"

#define NRF_LOG_MODULE_NAME ant_bcs_page_4
#if ANT_BSC_PAGE_4_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_BSC_PAGE_4_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_BSC_PAGE_4_INFO_COLOR
#else // ANT_BSC_PAGE_4_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_BSC_PAGE_4_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief BSC page 4 data layout structure. */
typedef struct
{
    uint8_t reserved_byte;
    uint8_t fract_bat_volt;
    uint8_t coarse_bat_volt   : 4;
    uint8_t bat_status        : 3;
    uint8_t bitfield_reserved : 1;
    uint8_t reserved[4];
}ant_bsc_page4_data_layout_t;

/* Display precission must be updated. */
STATIC_ASSERT(ANT_BSC_BAT_VOLTAGE_PRECISION == 1000);

/**@brief Function for printing speed or cadence page4 data. */
static void page4_data_log( ant_bsc_page4_data_t const * p_page_data)
{
    NRF_LOG_INFO("Battery voltage:           %u.%03uV",
              (unsigned int)p_page_data->coarse_bat_volt,
              (unsigned int)ANT_BSC_BAT_VOLTAGE_FRACTION_MV(p_page_data->fract_bat_volt));
    NRF_LOG_INFO("Battery status:            %u", (unsigned int)p_page_data->bat_status);
}

void ant_bsc_page_4_encode(uint8_t * p_page_buffer, ant_bsc_page4_data_t const * p_page_data)
{
    ant_bsc_page4_data_layout_t * p_outcoming_data = (ant_bsc_page4_data_layout_t *)p_page_buffer;

    p_outcoming_data->reserved_byte     = UINT8_MAX;
    p_outcoming_data->fract_bat_volt    = p_page_data->fract_bat_volt;
    p_outcoming_data->coarse_bat_volt   = p_page_data->coarse_bat_volt;
    p_outcoming_data->bat_status        = p_page_data->bat_status;
    p_outcoming_data->bitfield_reserved = 0;

    page4_data_log( p_page_data);
}

void ant_bsc_page_4_decode(uint8_t const * p_page_buffer, ant_bsc_page4_data_t * p_page_data)
{
    ant_bsc_page4_data_layout_t const * p_incoming_data = (ant_bsc_page4_data_layout_t *)p_page_buffer;

    p_page_data->fract_bat_volt  = p_incoming_data->fract_bat_volt;
    p_page_data->coarse_bat_volt = p_incoming_data->coarse_bat_volt;
    p_page_data->bat_status      = p_incoming_data->bat_status;

    page4_data_log( p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_BSC)
