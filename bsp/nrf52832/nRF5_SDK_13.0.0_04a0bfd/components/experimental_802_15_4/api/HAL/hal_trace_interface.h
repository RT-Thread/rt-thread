/**
 * Copyright (c) 2016 - 2017 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
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
#ifndef HAL_TRACE_INTERFACE_H_INCLUDED
#define HAL_TRACE_INTERFACE_H_INCLUDED

#ifdef CONFIG_TRACE

#include "hal_uart.h"

#define HAL_TRACE_INTERFACE_REUSE(p_uart_desc) hal_trace_reuse(p_uart_desc)
#define HAL_TRACE_INTERFACE_INIT()             hal_trace_init()
#define HAL_TRACE_INTERFACE_PUTS(s)            hal_trace_puts(s)
#define HAL_TRACE_INTERFACE_FINALIZE()         hal_trace_finalize()

/**
 * @brief Trace interface initialization
 */
void hal_trace_init(void);

/**
 * @brief Initializes trace interface, using already initialized UART.
 *
 * @param[in]   p_uart_desc UART descriptor, which has been already initialized.
 */
void hal_trace_reuse(hal_uart_descriptor_t * p_uart_desc);

/**
 * @brief Sends a null-terminated string to the debug interface
 *
 * @details send debug data using debug interface
 *
 * @param[in]   p_data  null-terminated string.
 */
void hal_trace_puts(const char * p_data);


/**
 * @brief Finalizes buffered trace data output to UART,
 *          before commencing non-buffered assertion output
 */
void hal_trace_finalize(void);


#else

/* If debug is disabled, these macros are just a stub.*/
#define HAL_TRACE_INTERFACE_REUSE(p_uart_desc)
#define HAL_TRACE_INTERFACE_INIT()
#define HAL_TRACE_INTERFACE_PUTS(s)
#define HAL_TRACE_INTERFACE_FINALIZE()

#endif // CONFIG_DEBUG

#endif // HAL_TRACE_INTERFACE_H_INCLUDED
