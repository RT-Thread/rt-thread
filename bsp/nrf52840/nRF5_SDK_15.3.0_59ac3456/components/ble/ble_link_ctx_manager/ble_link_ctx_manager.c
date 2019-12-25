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
#include "ble_link_ctx_manager.h"
#include "sdk_common.h"


ret_code_t blcm_link_ctx_get(blcm_link_ctx_storage_t const * const p_link_ctx_storage,
                             uint16_t                        const conn_handle,
                             void                         ** const pp_ctx_data)
{
    uint8_t conn_id;

    if (pp_ctx_data == NULL)
    {
        return NRF_ERROR_NULL;
    }
    else
    {
        *pp_ctx_data = NULL;
    }

    VERIFY_PARAM_NOT_NULL(p_link_ctx_storage);
    VERIFY_PARAM_NOT_NULL(p_link_ctx_storage->p_ctx_data_pool);
    VERIFY_TRUE((p_link_ctx_storage->link_ctx_size % BYTES_PER_WORD) == 0, NRF_ERROR_INVALID_PARAM);

    conn_id = ble_conn_state_conn_idx(conn_handle);

    if (conn_id == BLE_CONN_STATE_MAX_CONNECTIONS)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    if (conn_id >= p_link_ctx_storage->max_links_cnt)
    {
        return NRF_ERROR_NO_MEM;
    }

    *pp_ctx_data = (void *) ((uint8_t *) p_link_ctx_storage->p_ctx_data_pool + 
                             conn_id * p_link_ctx_storage->link_ctx_size);
    return NRF_SUCCESS;
}

