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
#ifndef NRF_SECTION_H__
#define NRF_SECTION_H__

#include "nordic_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup section_vars Section variables
 * @ingroup app_common
 * @{
 *
 * @brief Section variables.
 */
#if defined(__ICCARM__)
// Enable IAR language extensions
#pragma language=extended
#endif

/**@brief   Macro for obtaining the address of the beginning of a section.
 *
 * param[in]    section_name    Name of the section.
 */
#if defined(__CC_ARM)
//lint -save -e27 Illegal character (0x24)
#define NRF_SECTION_START_ADDR(section_name)       &CONCAT_2(section_name, $$Base)
//lint -restore

#elif defined(__GNUC__)
#define NRF_SECTION_START_ADDR(section_name)       &CONCAT_2(__start_, section_name)

#elif defined(__ICCARM__)
#define NRF_SECTION_START_ADDR(section_name)       __section_begin(STRINGIFY(section_name))
#endif

/**@brief    Macro for obtaining the address of the end of a section.
 *
 * @param[in]   section_name    Name of the section.
 */
#if defined(__CC_ARM)
//lint -save -e27 Illegal character (0x24)
#define NRF_SECTION_END_ADDR(section_name)         &CONCAT_2(section_name, $$Limit)
//lint -restore

#elif defined(__GNUC__)
#define NRF_SECTION_END_ADDR(section_name)         &CONCAT_2(__stop_, section_name)

#elif defined(__ICCARM__)
#define NRF_SECTION_END_ADDR(section_name)         __section_end(STRINGIFY(section_name))
#endif

/**@brief   Macro for retrieving the length of a given section, in bytes.
 *
 * @param[in]   section_name    Name of the section.
 */
#define NRF_SECTION_LENGTH(section_name)                        \
    ((size_t)NRF_SECTION_END_ADDR(section_name) -               \
     (size_t)NRF_SECTION_START_ADDR(section_name))

/**@brief   Macro for creating a section.
 *
 * @param[in]   section_name    Name of the section.
 * @param[in]   data_type       Data type of the variables to be registered in the section.
 *
 * @warning Data type must be word aligned to prevent padding.
 */
#if defined(__CC_ARM)
//lint -save -e27 Illegal character (0x24)
#define NRF_SECTION_DEF(section_name, data_type)                \
    extern data_type * CONCAT_2(section_name, $$Base);          \
    extern void      * CONCAT_2(section_name, $$Limit)
//lint -restore

#elif defined(__GNUC__)
#define NRF_SECTION_DEF(section_name, data_type)                \
    extern data_type * CONCAT_2(__start_, section_name);        \
    extern void      * CONCAT_2(__stop_, section_name)

#elif defined(__ICCARM__)
#define NRF_SECTION_DEF(section_name, data_type)                \
    _Pragma(STRINGIFY(section = STRINGIFY(section_name)));

#endif

/**@brief   Macro for declaring a variable and registering it in a section.
 *
 * @details Declares a variable and registers it in a named section. This macro ensures that the
 *          variable is not stripped away when using optimizations.
 *
 * @note The order in which variables are placed in a section is dependent on the order in
 *       which the linker script encounters the variables during linking.
 *
 * @param[in]   section_name    Name of the section.
 * @param[in]   section_var     Variable in which to register the given section.
 */
#if defined(__CC_ARM)
#define NRF_SECTION_ITEM_REGISTER(section_name, section_var) \
    static section_var __attribute__ ((section(STRINGIFY(section_name)))) __attribute__((used))

#elif defined(__GNUC__)
#define NRF_SECTION_ITEM_REGISTER(section_name, section_var) \
    static section_var __attribute__ ((section("."STRINGIFY(section_name)))) __attribute__((used))

#elif defined(__ICCARM__)
#define NRF_SECTION_ITEM_REGISTER(section_name, section_var) \
    __root section_var @ STRINGIFY(section_name)
#endif

/**@brief   Macro for retrieving a variable from a section.
 *
 * @warning     The stored symbol can only be resolved using this macro if the
 *              type of the data is word aligned. The operation of acquiring
 *              the stored symbol relies on the size of the stored type. No
 *              padding can exist in the named section in between individual
 *              stored items or this macro will fail.
 *
 * @param[in]   section_name    Name of the section.
 * @param[in]   data_type       Data type of the variable.
 * @param[in]   i               Index of the variable in section.
 */
#define NRF_SECTION_ITEM_GET(section_name, data_type, i) \
    ((data_type*)NRF_SECTION_START_ADDR(section_name) + (i))

/**@brief   Macro for getting the number of variables in a section.
 *
 * @param[in]   section_name    Name of the section.
 * @param[in]   data_type       Data type of the variables in the section.
 */
#define NRF_SECTION_ITEM_COUNT(section_name, data_type) \
    NRF_SECTION_LENGTH(section_name) / sizeof(data_type)

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_SECTION_H__
