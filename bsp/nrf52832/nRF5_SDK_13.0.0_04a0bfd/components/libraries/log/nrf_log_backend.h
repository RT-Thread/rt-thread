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
/**@file
 * @addtogroup nrf_log Logger module
 * @ingroup    app_common
 *
 * @defgroup nrf_log_backend Backend of nrf_log
 * @{
 * @ingroup  nrf_log
 * @brief    The nrf_log backend interface.
 */


#ifndef NRF_LOG_BACKEND_H__
#define NRF_LOG_BACKEND_H__

#include "nrf_log_ctrl.h"
#include "sdk_errors.h"
#include <stdbool.h>

/**
 * @brief Function for initializing the logger backend.
 *
 * param blocking Set true if handler functions should block until completion.
 *
 * @return NRF_SUCCESS after successful initialization, error code otherwise.
 */
ret_code_t nrf_log_backend_init(bool blocking);

/**
 * @brief Function for returning a pointer to a function for handling standard
 * log entries (@ref NRF_LOG_ERROR, etc.).
 *
 * @return Pointer to a handler.
 */
nrf_log_std_handler_t nrf_log_backend_std_handler_get(void);

/**
 * @brief Function for returning a pointer to a function for handling
 * hexdumps (@ref NRF_LOG_HEXDUMP_ERROR, etc.).
 *
 * @return Pointer to a handler.
 */
nrf_log_hexdump_handler_t nrf_log_backend_hexdump_handler_get(void);

/**
 * @brief Function for blocking reading of a byte from the backend.
 *
 * @return Byte.
 */
uint8_t nrf_log_backend_getchar(void);
#endif // NRF_LOG_BACKEND_H__
/** @} */
