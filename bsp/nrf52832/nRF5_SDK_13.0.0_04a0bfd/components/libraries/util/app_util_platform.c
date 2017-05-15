/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
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
#include "app_util_platform.h"

#ifdef SOFTDEVICE_PRESENT
/* Global nvic state instance, required by nrf_nvic.h */
nrf_nvic_state_t nrf_nvic_state;
#endif

static uint32_t m_in_critical_region = 0;

void app_util_disable_irq(void)
{
    __disable_irq();
    m_in_critical_region++;
}

void app_util_enable_irq(void)
{
    m_in_critical_region--;
    if (m_in_critical_region == 0)
    {
        __enable_irq();
    }
}

void app_util_critical_region_enter(uint8_t *p_nested)
{
#if __CORTEX_M == (0x04U)
    ASSERT(APP_LEVEL_PRIVILEGED == privilege_level_get())
#endif

#if defined(SOFTDEVICE_PRESENT)
    /* return value can be safely ignored */
    (void) sd_nvic_critical_region_enter(p_nested);
#else
    app_util_disable_irq();
#endif
}

void app_util_critical_region_exit(uint8_t nested)
{
#if __CORTEX_M == (0x04U)
    ASSERT(APP_LEVEL_PRIVILEGED == privilege_level_get())
#endif

#if defined(SOFTDEVICE_PRESENT)
    /* return value can be safely ignored */
    (void) sd_nvic_critical_region_exit(nested);
#else
    app_util_enable_irq();
#endif
}


uint8_t privilege_level_get(void)
{
#if __CORTEX_M == (0x00U) || defined(_WIN32) || defined(__unix) || defined(__APPLE__)
    /* the Cortex-M0 has no concept of privilege */
    return APP_LEVEL_PRIVILEGED;
#elif __CORTEX_M == (0x04U)
    uint32_t isr_vector_num = __get_IPSR() & IPSR_ISR_Msk ;
    if (0 == isr_vector_num)
    {
        /* Thread Mode, check nPRIV */
        int32_t control = __get_CONTROL();
        return control & CONTROL_nPRIV_Msk ? APP_LEVEL_UNPRIVILEGED : APP_LEVEL_PRIVILEGED;
    }
    else
    {
        /* Handler Mode, always privileged */
        return APP_LEVEL_PRIVILEGED;
    }
#endif
}


uint8_t current_int_priority_get(void)
{
    uint32_t isr_vector_num = __get_IPSR() & IPSR_ISR_Msk ;
    if (isr_vector_num > 0)
    {
        int32_t irq_type = ((int32_t)isr_vector_num - EXTERNAL_INT_VECTOR_OFFSET);
        return (NVIC_GetPriority((IRQn_Type)irq_type) & 0xFF);
    }
    else
    {
        return APP_IRQ_PRIORITY_THREAD;
    }
}
