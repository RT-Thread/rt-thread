/**
 * Copyright (c) 2016 - 2019 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 *
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
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
#ifndef HAL_DEBUG_INTERFACE_H_INCLUDED
#define HAL_DEBUG_INTERFACE_H_INCLUDED


#if defined(NRF52) || defined(NRF52840_XXAA)

#include "nrf_assert.h"

#endif // NRF52

/** 
 * @defgroup hal_debug_interface HAL Debug Interface
 * @ingroup hal_15_4
 * @{
 * @brief Module to declare HAL debug interface
 */

#ifdef CONFIG_DEBUG

#include <stdint.h>

#define HAL_DEBUG_INTERFACE_INIT()           hal_debug_init()
#define HAL_DEBUG_INTERFACE_PUT(c, n)        hal_debug_put(c, n)
#define HAL_DEBUG_INTERFACE_PUTC(c)          hal_debug_putc(c)
#define HAL_DEBUG_INTERFACE_PUTS(s)          hal_debug_puts(s)

/**
 * @brief Debug interface initialization
 */
void hal_debug_init(void);

/**
 * @brief Sends string to the debug interface
 *
 * @details send debug data using debug interface
 *
 * @param[in]   p_data  debug string.
 * @param[in]   len string length.
 */
void hal_debug_put(const void * p_data, uint8_t len);

/**
 * @brief Sends char symbol to the debug interface
 *
 * @details send debug data using debug interface
 *
 * @param[in]   data  char symbol.
 */
void hal_debug_putc(const char data);

/**
 * @brief Sends a null-terminated string to the debug interface
 *
 * @details send debug data using debug interface
 *
 * @param[in]   p_data  null-terminated string.
 */
void hal_debug_puts(const char * p_data);

#else

/* If debug is disabled, these macros are just a stub.*/
#define HAL_DEBUG_INTERFACE_INIT()
#define HAL_DEBUG_INTERFACE_PUT(c, n)
#define HAL_DEBUG_INTERFACE_PUTC(c)
#define HAL_DEBUG_INTERFACE_PUTS(s)

#endif // CONFIG_DEBUG

/** @} */

#endif // HAL_DEBUG_INTERFACE_H_INCLUDED
