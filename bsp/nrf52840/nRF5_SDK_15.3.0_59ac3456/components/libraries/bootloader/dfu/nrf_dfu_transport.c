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
#include "nrf_dfu_transport.h"
#include "nrf_log.h"


#define DFU_TRANS_SECTION_ITEM_GET(i)       NRF_SECTION_ITEM_GET(dfu_trans, nrf_dfu_transport_t, (i))
#define DFU_TRANS_SECTION_ITEM_COUNT        NRF_SECTION_ITEM_COUNT(dfu_trans, nrf_dfu_transport_t)

NRF_SECTION_DEF(dfu_trans, const nrf_dfu_transport_t);


uint32_t nrf_dfu_transports_init(nrf_dfu_observer_t observer)
{
    uint32_t const num_transports = DFU_TRANS_SECTION_ITEM_COUNT;
    uint32_t ret_val = NRF_SUCCESS;

    NRF_LOG_DEBUG("Initializing transports (found: %d)", num_transports);

    for (uint32_t i = 0; i < num_transports; i++)
    {
        nrf_dfu_transport_t * const trans = DFU_TRANS_SECTION_ITEM_GET(i);
        ret_val = trans->init_func(observer);
        if (ret_val != NRF_SUCCESS)
        {
            NRF_LOG_DEBUG("Failed to initialize transport %d, error %d", i, ret_val);
            break;
        }
    }

    return ret_val;
}


uint32_t nrf_dfu_transports_close(nrf_dfu_transport_t const * p_exception)
{
    uint32_t const num_transports = DFU_TRANS_SECTION_ITEM_COUNT;
    uint32_t ret_val = NRF_SUCCESS;

    NRF_LOG_DEBUG("Shutting down transports (found: %d)", num_transports);

    for (uint32_t i = 0; i < num_transports; i++)
    {
        nrf_dfu_transport_t * const trans = DFU_TRANS_SECTION_ITEM_GET(i);
        ret_val = trans->close_func(p_exception);
        if (ret_val != NRF_SUCCESS)
        {
            NRF_LOG_DEBUG("Failed to shutdown transport %d, error %d", i, ret_val);
            break;
        }
    }

    return ret_val;
}
