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
#include <stdint.h>
#include "nrf_bootloader_app_start.h"
#include "nrf_log.h"
#include "nrf_dfu_mbr.h"

extern void nrf_bootloader_app_start_impl(uint32_t start_addr);

void nrf_bootloader_app_start(uint32_t start_addr)
{
    NRF_LOG_DEBUG("Running nrf_bootloader_app_start with address: 0x%08x\r\n", start_addr);
    uint32_t err_code;

    // Disable interrupts
    NRF_LOG_DEBUG("Disabling interrupts\r\n");

    NVIC->ICER[0]=0xFFFFFFFF;
#if defined(__NRF_NVIC_ISER_COUNT) && __NRF_NVIC_ISER_COUNT == 2
    NVIC->ICER[1]=0xFFFFFFFF;
#endif

    NRF_LOG_DEBUG("Setting MBR vector table base: 0x%08x\r\n", start_addr);
    err_code = nrf_dfu_mbr_vector_table_set(start_addr, true);
    if(err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Failed running nrf_dfu_mbr_vector_table_set\r\n");
        return;
    }

    // Run application
    nrf_bootloader_app_start_impl(start_addr);
}

