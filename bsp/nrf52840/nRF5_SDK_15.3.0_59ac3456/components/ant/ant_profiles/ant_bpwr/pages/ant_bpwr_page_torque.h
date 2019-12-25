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
#ifndef ANT_BPWR_PAGE_TORQUE_COMMON_H__
#define ANT_BPWR_PAGE_TORQUE_COMMON_H__

/** @file
 *
 * @defgroup ant_sdk_profiles_bicycle_p_page_torque Bicycle Power profile pages 17, 18 (commons)
 * @{
 * @ingroup ant_sdk_profiles_bpwr_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Common data structure for Bicycle Power data pages 17, 18.
 *
 * @note This structure implements specific data that is common for pages 17, 18.
 */
typedef struct
{
    uint8_t  update_event_count;    ///< Power event count.
    uint8_t  tick;                  ///< Wheel/crank revolutions counter.
    uint16_t period;                ///< Accumulated wheel/crank period (1/2048 s).
    uint16_t accumulated_torque;    ///< Accumulated wheel/torque (1/32 Nm).
} ant_bpwr_page_torque_data_t;

/**@brief Initialize page torque.
 */
#define DEFAULT_ANT_BPWR_PAGE_TORQUE(up_evt_cnt, def_tick, def_period, acc_torque)  \
    {                                                                               \
        .update_event_count    = (up_evt_cnt),                                      \
        .tick                  = (def_tick),                                        \
        .period                = (def_period),                                      \
        .accumulated_torque    = (acc_torque)                                       \
    }

/**@brief Function for encoding pages 17, 18.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_bpwr_page_torque_encode(uint8_t                           * p_page_buffer,
                                 ant_bpwr_page_torque_data_t const * p_page_data);

/**@brief Function for decoding pages 17, 18.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_bpwr_page_torque_decode(uint8_t const               * p_page_buffer,
                                 ant_bpwr_page_torque_data_t * p_page_data);

/**@brief Function for logging pages 17, 18.
 *
 * @param[in] p_page_data      Pointer to the page data.
 */
void ant_bpwr_page_torque_log(ant_bpwr_page_torque_data_t const * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_BPWR_PAGE_TORQUE_COMMON_H__
/** @} */
