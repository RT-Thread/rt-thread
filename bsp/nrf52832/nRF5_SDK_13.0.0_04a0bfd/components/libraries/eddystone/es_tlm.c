/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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

#include <string.h>
#include "app_timer.h"
#include "es_tlm.h"
#include "es_app_config.h"
#include "es_battery_voltage.h"
#include "es_stopwatch.h"
#include "nrf_soc.h"

#define TICKS_100_MS APP_TIMER_TICKS(100) //!< Tick count for 100ms.

static es_tlm_frame_t    m_tlm;
static uint32_t          m_le_adv_cnt;
static es_stopwatch_id_t m_time_sec_sw_id;
static es_stopwatch_id_t m_tlm_refresh_sw_id;

/**@brief Function for updating the ADV_SEC field of TLM*/
static void update_time(void)
{
    static uint32_t time_total_100_ms = 0;
    uint32_t        be_time_100_ms; // Big endian version of 0.1 second counter.

    time_total_100_ms += es_stopwatch_check(m_time_sec_sw_id);

    be_time_100_ms = BYTES_REVERSE_32BIT(time_total_100_ms);

    memcpy(m_tlm.sec_cnt, &be_time_100_ms, ES_TLM_SEC_CNT_LENGTH);
}


/**@brief Function for updating the TEMP field of TLM*/
static void update_temp(void)
{
    int32_t temp;                                        // variable to hold temp reading
    (void)sd_temp_get(&temp);                            // get new temperature
    int16_t temp_new = (int16_t) temp;                   // convert from int32_t to int16_t
    m_tlm.temp[0] = (uint8_t)((temp_new >> 2) & 0xFFUL); // Right-shift by two to remove decimal part
    m_tlm.temp[1] = (uint8_t)((temp_new << 6) & 0xFFUL); // Left-shift 6 to get fractional part with 0.25 degrees C resolution
}


/**@brief Function for updating the VBATT field of TLM*/
static void update_vbatt(void)
{
    uint16_t vbatt;                 // Variable to hold voltage reading
    es_battery_voltage_get(&vbatt); // Get new battery voltage
    m_tlm.vbatt[0] = (uint8_t)(vbatt >> 8);
    m_tlm.vbatt[1] = (uint8_t)vbatt;
}


static void update_adv_cnt(void)
{
    uint32_t be_adv_cnt = BYTES_REVERSE_32BIT(m_le_adv_cnt);
    memcpy(m_tlm.adv_cnt, (uint8_t *)(&be_adv_cnt), ES_TLM_ADV_CNT_LENGTH);
}


void es_tlm_tlm_get(es_tlm_frame_t * p_tlm_frame)
{
    // Note that frame type and TLM version fields are set in initialization.
    update_time();
    update_adv_cnt();

    if (es_stopwatch_check(m_tlm_refresh_sw_id) > 0)
    {
        update_temp();
        update_vbatt();
    }

    memcpy(p_tlm_frame, &m_tlm, sizeof(es_tlm_frame_t));
}


void es_tlm_adv_cnt_inc(void)
{
    m_le_adv_cnt++;
}


void es_tlm_init(void)
{
    ret_code_t err_code;

    memset(&m_tlm, 0, sizeof(m_tlm));
    m_tlm.frame_type = ES_FRAME_TYPE_TLM;
    m_tlm.version    = ES_TLM_VERSION_TLM;
    m_le_adv_cnt     = 0;

    update_time();
    update_vbatt();
    update_temp();

    err_code = es_stopwatch_create(&m_time_sec_sw_id, APP_TIMER_TICKS(100));
    APP_ERROR_CHECK(err_code);

    err_code = es_stopwatch_create(
        &m_tlm_refresh_sw_id,
        APP_TIMER_TICKS(APP_CONFIG_TLM_TEMP_VBATT_UPDATE_INTERVAL_SECONDS * 1000));
    APP_ERROR_CHECK(err_code);
}
