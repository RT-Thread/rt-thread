/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
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
#ifndef NRF_LOG_TYPES_H
#define NRF_LOG_TYPES_H

#include <stdint.h>

/**
 * @brief Logger severity levels.
 */
typedef enum
{
    NRF_LOG_SEVERITY_NONE,
    NRF_LOG_SEVERITY_ERROR,
    NRF_LOG_SEVERITY_WARNING,
    NRF_LOG_SEVERITY_INFO,
    NRF_LOG_SEVERITY_DEBUG,
    NRF_LOG_SEVERITY_INFO_RAW, /* Artificial level to pass information about skipping string postprocessing.*/
} nrf_log_severity_t;

/**
 * @brief Structure holding dynamic data associated with a module.
 *
 * See @ref NRF_LOG_MODULE_REGISTER and @ref NRF_LOG_INSTANCE_REGISTER.
 */
typedef struct
{
    uint16_t     order_idx;     ///< Ordered index of the module (used for auto-completion).
    uint16_t     filter;        ///< Current highest severity level accepted (redundant to @ref nrf_log_module_filter_data_t::filter_lvls, used for optimization)
} nrf_log_module_dynamic_data_t;

/**
 * @brief Structure holding dynamic filters associated with a module or instance if filtering is enabled (@ref NRF_LOG_FILTERS_ENABLED).
 *
 * @note Backend filters logically are part of @ref nrf_log_module_dynamic_data_t but they are kept separated to enable storing them in non-volatile memory.
 */
typedef struct
{
    uint32_t     filter_lvls;   ///< Current severity levels for each backend (3 bits per backend).
} nrf_log_module_filter_data_t;

/**
 * @brief Structure holding constant data associated with a module or instance.
 *
 * See @ref NRF_LOG_MODULE_REGISTER and @ref NRF_LOG_INSTANCE_REGISTER.
 */
typedef struct
{
    const char *       p_module_name;    ///< Module or instance name.
    uint8_t            info_color_id;    ///< Color code of info messages.
    uint8_t            debug_color_id;   ///< Color code of debug messages.
    nrf_log_severity_t compiled_lvl;     ///< Compiled highest severity level.
    nrf_log_severity_t initial_lvl;      ///< Severity level for given module or instance set on backend initialization.
} nrf_log_module_const_data_t;

#endif //NRF_LOG_TYPES_H
