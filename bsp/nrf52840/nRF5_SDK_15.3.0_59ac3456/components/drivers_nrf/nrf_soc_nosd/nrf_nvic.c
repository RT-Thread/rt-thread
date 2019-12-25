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
#include <stdlib.h>
#include "nrf_soc.h"
#include "nrf_error.h"

static uint8_t m_in_critical_region = 0;

uint32_t sd_nvic_EnableIRQ(IRQn_Type IRQn)
{
    NVIC_EnableIRQ(IRQn);
    return NRF_SUCCESS;
}

uint32_t sd_nvic_DisableIRQ(IRQn_Type IRQn)
{
    NVIC_DisableIRQ(IRQn);
    return NRF_SUCCESS;
}

uint32_t sd_nvic_GetPendingIRQ(IRQn_Type IRQn, uint32_t * p_pending_irq)
{
    if (p_pending_irq != NULL)
    {
        *p_pending_irq = NVIC_GetPendingIRQ(IRQn);
        return NRF_SUCCESS;
    }
    return NRF_ERROR_NULL;
}

uint32_t sd_nvic_SetPendingIRQ(IRQn_Type IRQn)
{
    NVIC_SetPendingIRQ(IRQn);
    return NRF_SUCCESS;
}

uint32_t sd_nvic_ClearPendingIRQ(IRQn_Type IRQn)
{
    NVIC_ClearPendingIRQ(IRQn);
    return NRF_SUCCESS;
}

uint32_t sd_nvic_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
    NVIC_SetPriority(IRQn, priority);
    return NRF_SUCCESS;
}

uint32_t sd_nvic_GetPriority(IRQn_Type IRQn, uint32_t * p_priority)
{
    if (p_priority != NULL)
    {
        *p_priority = NVIC_GetPriority(IRQn);
        return NRF_SUCCESS;
    }

    return NRF_ERROR_NULL;
}

uint32_t sd_nvic_SystemReset(void)
{
    NVIC_SystemReset();
    return NRF_SUCCESS;
}

uint32_t sd_nvic_critical_region_enter(uint8_t * p_is_nested_critical_region)
{
    __disable_irq();

    *p_is_nested_critical_region = (m_in_critical_region != 0);
    m_in_critical_region++;

    return NRF_SUCCESS;
}

uint32_t sd_nvic_critical_region_exit(uint8_t is_nested_critical_region)
{
    m_in_critical_region--;

    if (is_nested_critical_region == 0)
    {
        m_in_critical_region = 0;
        __enable_irq();
    }
    return NRF_SUCCESS;
}
