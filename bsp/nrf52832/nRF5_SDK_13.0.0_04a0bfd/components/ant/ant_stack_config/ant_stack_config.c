/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_STACK_CONFIG)
#include "nrf_assert.h"
#include "ant_stack_config.h"
#include "ant_interface.h"
#include "ant_parameters.h"

#define ANT_BUFFER_SIZE_FOR_SD    ANT_ENABLE_GET_REQUIRED_SPACE(ANT_CONFIG_TOTAL_CHANNELS_ALLOCATED, \
                                                                ANT_CONFIG_ENCRYPTED_CHANNELS,       \
                                                                ANT_CONFIG_BURST_QUEUE_SIZE,         \
                                                                ANT_CONFIG_EVENT_QUEUE_SIZE)

static union
{
    uint8_t  u8[ANT_BUFFER_SIZE_FOR_SD];
    uint32_t u32[1]; // force allign to uint32_t
}ant_stack_buffer; /*!< Memory buffer provided in order to support channel configuration */

uint32_t ant_stack_static_config(void)
{
    ASSERT(ANT_CONFIG_TOTAL_CHANNELS_ALLOCATED <= MAX_ANT_CHANNELS);
    ASSERT(ANT_CONFIG_ENCRYPTED_CHANNELS <= ANT_CONFIG_TOTAL_CHANNELS_ALLOCATED);

    ANT_ENABLE m_ant_enable_cfg =
    {
        .ucTotalNumberOfChannels        = ANT_CONFIG_TOTAL_CHANNELS_ALLOCATED,
        .ucNumberOfEncryptedChannels    = ANT_CONFIG_ENCRYPTED_CHANNELS,
        .usNumberOfEvents               = ANT_CONFIG_EVENT_QUEUE_SIZE,
        .pucMemoryBlockStartLocation    = ant_stack_buffer.u8,
        .usMemoryBlockByteSize          = ANT_BUFFER_SIZE_FOR_SD
    };

    return sd_ant_enable(&m_ant_enable_cfg);
}

#endif // NRF_MODULE_ENABLED(ANT_STACK_CONFIG)
