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
#include "nrf_bootloader.h"

#include "compiler_abstraction.h"
#include "nrf.h"
#include "nrf_bootloader_app_start.h"
#include "nrf_log.h"
#include "nrf_dfu.h"
#include "nrf_error.h"


/** @brief Weak implemenation of nrf_dfu_init
 *
 * @note   This function will be overridden if nrf_dfu.c is
 *         compiled and linked with the project
 */
 #if (__LINT__ != 1)
__WEAK uint32_t nrf_dfu_init(void)
{
    NRF_LOG_DEBUG("in weak nrf_dfu_init\r\n");
    return NRF_SUCCESS;
}
#endif


/** @brief Weak implementation of nrf_dfu_init
 *
 * @note    This function must be overridden in application if
 *          user-specific initialization is needed.
 */
__WEAK uint32_t nrf_dfu_init_user(void)
{
    NRF_LOG_DEBUG("in weak nrf_dfu_init_user\r\n");
    return NRF_SUCCESS;
}


uint32_t nrf_bootloader_init(void)
{
    NRF_LOG_DEBUG("In nrf_bootloader_init\r\n");

    uint32_t ret_val = NRF_SUCCESS;

    #if 0
    // Call user-defined init function if implemented
    ret_val = nrf_dfu_init_user();
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }
    #endif

    // Call DFU init function if implemented
    ret_val = nrf_dfu_init();
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    NRF_LOG_DEBUG("After nrf_bootloader_init\r\n");
    return ret_val;
}
