/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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

#include <stdint.h>
#include "nrf.h"
#include "nrf_assert.h"
#include "nrf_strerror.h"
#include "nrf_mpu_lib.h"
#include "nrf_stack_guard.h"

#define NRF_LOG_MODULE_NAME stack_guard

#if NRF_STACK_GUARD_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       NRF_STACK_GUARD_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NRF_STACK_GUARD_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR NRF_STACK_GUARD_CONFIG_DEBUG_COLOR
#endif
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#if NRF_STACK_GUARD_ENABLED
STATIC_ASSERT(STACK_GUARD_SIZE >= 32);

ret_code_t nrf_stack_guard_init(void)
{
    nrf_mpu_lib_region_t region;
    uint32_t attributes;
    ret_code_t status;

    ASSERT((STACK_GUARD_BASE + STACK_GUARD_SIZE) < (uint32_t)((void *)(STACK_TOP)));

    attributes = (0x05 << MPU_RASR_TEX_Pos) | (1 << MPU_RASR_B_Pos) |   /* Normal memory, WBWA/WBWA */
                 (0x07 << MPU_RASR_AP_Pos) | (1 << MPU_RASR_XN_Pos);    /* Access: RO/RO, XN */

    status = nrf_mpu_lib_region_create(&region,
                                       (void *)(STACK_GUARD_BASE),
                                       STACK_GUARD_SIZE,
                                       attributes);

    if (status == NRF_SUCCESS)
    {
        NRF_LOG_INFO("Stack Guard (%u bytes): 0x%08X-0x%08X (total stack size: %u bytes, usable stack area: %u bytes)",
                     STACK_GUARD_SIZE,
                     STACK_GUARD_BASE,
                     STACK_GUARD_BASE + STACK_GUARD_SIZE - 1,
                     STACK_SIZE,
                     REAL_STACK_SIZE);
    }
    else
    {
        NRF_LOG_ERROR("Cannot create stack guard page! Error: %u [%s]", status, (uint32_t)nrf_strerror_get(status));
    }

    return status;
}

#endif /* NRF_STACK_GUARD_ENABLED */
