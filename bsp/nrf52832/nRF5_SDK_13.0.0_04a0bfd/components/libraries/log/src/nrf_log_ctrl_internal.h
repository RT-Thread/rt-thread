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
#ifndef NRF_LOG_CTRL_INTERNAL_H
#define NRF_LOG_CTRL_INTERNAL_H
/**
 * @cond (NODOX)
 * @defgroup nrf_log_ctrl_internal Auxiliary internal types declarations
 * @{
 * @internal
 */

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_LOG)
#include "app_util_platform.h"

#define NRF_LOG_INTERNAL_INIT(timestamp_func) \
    nrf_log_init(timestamp_func)

#if (NRF_LOG_DEFERRED == 0)
#define NRF_LOG_INTERNAL_PROCESS() false
#define NRF_LOG_INTERNAL_FLUSH()
#define NRF_LOG_INTERNAL_FINAL_FLUSH()
#else
#define NRF_LOG_INTERNAL_PROCESS() nrf_log_frontend_dequeue()
#define NRF_LOG_INTERNAL_FLUSH()            \
    do {                                    \
        while (NRF_LOG_INTERNAL_PROCESS()); \
    } while(0)

#if NRF_LOG_BACKEND_SERIAL_USES_RTT
#define NRF_LOG_INTERNAL_BACKEND_FINAL NRF_BREAKPOINT_COND
#else
#define NRF_LOG_INTERNAL_BACKEND_FINAL
#endif

#define NRF_LOG_INTERNAL_FINAL_FLUSH()      \
    do {                                    \
    (void)nrf_log_blocking_backend_set();   \
        NRF_LOG_INTERNAL_FLUSH();           \
        NRF_LOG_INTERNAL_BACKEND_FINAL;     \
    } while(0)

#endif

#define NRF_LOG_INTERNAL_HANDLERS_SET(default_handler, bytes_handler) \
    nrf_log_handlers_set(default_handler, bytes_handler)

#else // NRF_MODULE_ENABLED(NRF_LOG)
#define NRF_LOG_INTERNAL_PROCESS()            false
#define NRF_LOG_INTERNAL_FLUSH()
#define NRF_LOG_INTERNAL_INIT(timestamp_func) NRF_SUCCESS
#define NRF_LOG_INTERNAL_HANDLERS_SET(default_handler, bytes_handler) \
    UNUSED_PARAMETER(default_handler); UNUSED_PARAMETER(bytes_handler)
#define NRF_LOG_INTERNAL_FINAL_FLUSH()
#endif // NRF_MODULE_ENABLED(NRF_LOG)

/** @}
 * @endcond
 */
#endif // NRF_LOG_CTRL_INTERNAL_H
