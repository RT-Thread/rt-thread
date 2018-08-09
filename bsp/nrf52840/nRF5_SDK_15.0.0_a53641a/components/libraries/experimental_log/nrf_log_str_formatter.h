/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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

/**@file
 *
 * @defgroup nrf_log_str_formatter String formatter for the logger messages
 * @{
 * @ingroup nrf_log
 */

#ifndef NRF_LOG_STR_FORMATTER_H
#define NRF_LOG_STR_FORMATTER_H

#include <stdint.h>
#include "nrf_fprintf.h"
#include "nrf_log_ctrl.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    uint32_t            timestamp;
    uint16_t            module_id;
    uint16_t            dropped;
    nrf_log_severity_t  severity;
    uint8_t             use_colors;
} nrf_log_str_formatter_entry_params_t;


void nrf_log_std_entry_process(char const * p_str,
                               uint32_t const * p_args,
                               uint32_t nargs,
                               nrf_log_str_formatter_entry_params_t * p_params,
                               nrf_fprintf_ctx_t * p_ctx);

void nrf_log_hexdump_entry_process(uint8_t * p_data,
                                   uint32_t data_len,
                                   nrf_log_str_formatter_entry_params_t * p_params,
                                   nrf_fprintf_ctx_t * p_ctx);

void nrf_log_str_formatter_timestamp_freq_set(uint32_t freq);
#ifdef __cplusplus
}
#endif

#endif //NRF_LOG_STR_FORMATTER_H
/** @} */
