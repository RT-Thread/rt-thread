/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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

#ifndef __NRF_STACK_GUARD_H__
#define __NRF_STACK_GUARD_H__

/**
* @defgroup nrf_stack_guard Stack guard
* @{
* @ingroup app_common
* @brief Functions for enabling stack violation control.
*/
#include "sdk_config.h"
#include "app_util.h"

#ifdef __cplusplus
extern "C" {
#endif

#define STACK_SIZE          (((int32_t)(STACK_TOP)) - (int32_t)((void *)(STACK_BASE)))
#if NRF_STACK_GUARD_ENABLED
#define STACK_GUARD_SIZE    (1ul << NRF_STACK_GUARD_CONFIG_SIZE)
#define STACK_GUARD_BASE    (((uint32_t)((void *)(STACK_BASE)) + STACK_GUARD_SIZE - 1) \
                              & ~(STACK_GUARD_SIZE - 1))
#define REAL_STACK_SIZE     (STACK_SIZE - STACK_GUARD_SIZE)
#else /* !NRF_STACK_GUARD_ENABLED */
#define REAL_STACK_SIZE     STACK_SIZE
#endif /* NRF_STACK_GUARD_ENABLED */

/**@brief Function for initializing the Stack Guard Page.
 *
 * @note When this module is enabled, the usable stack size is reduced by @ref NRF_STACK_GUARD_CONFIG_SIZE.
 * */
ret_code_t nrf_stack_guard_init(void);

#if NRF_STACK_GUARD_ENABLED
#define NRF_STACK_GUARD_INIT() nrf_stack_guard_init()
#else
#define NRF_STACK_GUARD_INIT() NRF_SUCCESS
#endif

#ifdef __cplusplus
}
#endif

#endif //__NRF_STACK_GUARD_H__
/** @} */
