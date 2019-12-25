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
#ifndef NRF_LOG_INSTANCE_H
#define NRF_LOG_INSTANCE_H

#include "sdk_config.h"
#include "nrf_section.h"
#include "nrf_log_types.h"
#include <stdint.h>


/*
 * For GCC, sections are sorted in the group by the linker. For IAR and KEIL, it is assumed that linker will sort
 * dynamic and const section in the same order (but in different locations). Proper message formatting
 * is based on that assumption.
 */
#if defined(__GNUC__)
#define NRF_LOG_DYNAMIC_SECTION_NAME(_module_name) CONCAT_2(log_dynamic_data_,_module_name)
#define NRF_LOG_FILTER_SECTION_NAME(_module_name) CONCAT_2(log_filter_data_,_module_name)
#define NRF_LOG_CONST_SECTION_NAME(_module_name) CONCAT_2(log_const_data_,_module_name)
#else
#define NRF_LOG_DYNAMIC_SECTION_NAME(_module_name) log_dynamic_data
#define NRF_LOG_FILTER_SECTION_NAME(_module_name) log_filter_data
#define NRF_LOG_CONST_SECTION_NAME(_module_name)   log_const_data
#endif

#define NRF_LOG_ITEM_DATA(_name)         CONCAT_3(m_nrf_log_,_name,_logs_data)
#define NRF_LOG_ITEM_DATA_DYNAMIC(_name) CONCAT_2(NRF_LOG_ITEM_DATA(_name),_dynamic)
#define NRF_LOG_ITEM_DATA_FILTER(_name)  CONCAT_2(NRF_LOG_ITEM_DATA(_name),_filter)
#define NRF_LOG_ITEM_DATA_CONST(_name)   CONCAT_2(NRF_LOG_ITEM_DATA(_name),_const)

#ifdef UNIT_TEST
#define _CONST
#else
#define _CONST const
#endif

/*lint -save -esym(526,log_const_data*) -esym(526,log_dynamic_data*)*/
NRF_SECTION_DEF(log_dynamic_data, nrf_log_module_dynamic_data_t);
NRF_SECTION_DEF(log_filter_data, nrf_log_module_filter_data_t);
NRF_SECTION_DEF(log_const_data, nrf_log_module_const_data_t);
/*lint -restore*/

#define NRF_LOG_INTERNAL_CONST_ITEM_REGISTER(                                             \
            _name, _str_name, _info_color, _debug_color, _initial_lvl, _compiled_lvl)     \
            NRF_SECTION_ITEM_REGISTER(NRF_LOG_CONST_SECTION_NAME(_name),                  \
            _CONST nrf_log_module_const_data_t NRF_LOG_ITEM_DATA_CONST(_name)) = {        \
                .p_module_name   = _str_name,                                             \
                .info_color_id   = (_info_color),                                         \
                .debug_color_id  = (_debug_color),                                        \
                .compiled_lvl    = (nrf_log_severity_t)(_compiled_lvl),                   \
                .initial_lvl     = (nrf_log_severity_t)(_initial_lvl),                    \
            }

#if NRF_LOG_FILTERS_ENABLED
#define NRF_LOG_INTERNAL_ITEM_REGISTER( \
                         _name, _str_name, _info_color, _debug_color, _initial_lvl, _compiled_lvl) \
    NRF_LOG_INTERNAL_CONST_ITEM_REGISTER(_name,                                                    \
                                         _str_name,                                                \
                                         _info_color,                                              \
                                         _debug_color,                                             \
                                         _initial_lvl,                                             \
                                         _compiled_lvl);                                           \
    NRF_SECTION_ITEM_REGISTER(NRF_LOG_DYNAMIC_SECTION_NAME(_name),                                 \
                    nrf_log_module_dynamic_data_t NRF_LOG_ITEM_DATA_DYNAMIC(_name));               \
    NRF_SECTION_ITEM_REGISTER(NRF_LOG_FILTER_SECTION_NAME(_name),                                  \
                          nrf_log_module_filter_data_t NRF_LOG_ITEM_DATA_FILTER(_name))

#else
#define NRF_LOG_INTERNAL_ITEM_REGISTER( \
                         _name, _str_name, _info_color, _debug_color, _initial_lvl, _compiled_lvl) \
    NRF_LOG_INTERNAL_CONST_ITEM_REGISTER(_name,                                                    \
                                         _str_name,                                                \
                                         _info_color,                                              \
                                         _debug_color,                                             \
                                         _initial_lvl,                                             \
                                         _compiled_lvl)

#endif
/**@file
 *
 * @defgroup nrf_log_instance Macros for logging on instance level
 * @{
 * @ingroup nrf_log
 *
 * @brief Macros for logging on instance level
 */

/** @def NRF_LOG_INSTANCE_PTR_DECLARE
 * @brief Macro for declaring a logger instance pointer in the module stucture.
 */

/** @def NRF_LOG_INSTANCE_REGISTER
 * @brief Macro for creating an independent module instance.
 *
 * Module instance provides filtering of logs on instance level instead of module level.
 */

/** @def NRF_LOG_INSTANCE_PTR_INIT
 * @brief Macro for initializing a pointer to the logger instance.
 */
 
 
 /** @} */
#if NRF_LOG_ENABLED && NRF_LOG_FILTERS_ENABLED
#define NRF_LOG_INSTANCE_PTR_DECLARE(_p_name) nrf_log_module_dynamic_data_t * _p_name;

#define NRF_LOG_INSTANCE_REGISTER( \
               _module_name, _inst_name, _info_color, _debug_color, _initial_lvl, _compiled_lvl)   \
               NRF_LOG_INTERNAL_ITEM_REGISTER(CONCAT_3(_module_name,_,_inst_name),                 \
                                              STRINGIFY(_module_name._inst_name),                  \
                                              _info_color,                                         \
                                              _debug_color,                                        \
                                              _initial_lvl,                                        \
                                              _compiled_lvl)

#define NRF_LOG_INSTANCE_PTR_INIT(_p_name, _module_name, _inst_name) \
                       ._p_name = &NRF_LOG_ITEM_DATA_DYNAMIC(CONCAT_3(_module_name,_,_inst_name)),

#else
#define NRF_LOG_INSTANCE_PTR_DECLARE(_p_name)
#define NRF_LOG_INSTANCE_REGISTER(_module_name, _inst_name, info_color, debug_color, _initial_lvl, compiled_lvl)
#define NRF_LOG_INSTANCE_PTR_INIT(_p_name, _module_name, _inst_name)
#endif

#endif //NRF_LOG_INSTANCE_H
