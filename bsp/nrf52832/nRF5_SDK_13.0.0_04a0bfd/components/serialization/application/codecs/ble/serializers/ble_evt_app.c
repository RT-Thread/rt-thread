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
#include "ble_serialization.h"
#include "ble_struct_serialization.h"
#include "cond_field_serialization.h"
#include "app_util.h"
#include "ble_evt_app.h"
#include "app_ble_user_mem.h"


// Helper definitions for common event type names to be compliant with
// event serialization macros.
#define ble_common_evt_tx_complete_t         ble_evt_tx_complete_t
#define ble_common_evt_user_mem_request_t    ble_evt_user_mem_request_t
#define ble_common_evt_user_mem_release_t    ble_evt_user_mem_release_t
#define ble_common_evt_data_length_changed_t ble_evt_data_length_changed_t


extern ser_ble_user_mem_t m_app_user_mem_table[];

uint32_t ble_evt_user_mem_release_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      ble_evt_t * const     p_event,
                                      uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_EVT_USER_MEM_RELEASE, common, user_mem_release);

    SER_PULL_uint16(&p_event->evt.common_evt.conn_handle);
    SER_PULL_uint8(&p_event->evt.common_evt.params.user_mem_release.type);
    SER_PULL_uint16(&p_event->evt.common_evt.params.user_mem_release.mem_block.len);

    //Set the memory pointer to not-null value.
    p_event->evt.common_evt.params.user_mem_release.mem_block.p_mem = (uint8_t *)~0;
    SER_PULL_COND(&p_event->evt.common_evt.params.user_mem_release.mem_block.p_mem, NULL);
    if (p_event->evt.common_evt.params.user_mem_release.mem_block.p_mem)
    {
        // Using connection handle find which mem block to release in Application Processor
        uint32_t user_mem_table_index;
        err_code = app_ble_user_mem_context_find(p_event->evt.common_evt.conn_handle, &user_mem_table_index);
        SER_ASSERT(err_code == NRF_SUCCESS, err_code);
        p_event->evt.common_evt.params.user_mem_release.mem_block.p_mem =
            m_app_user_mem_table[user_mem_table_index].mem_block.p_mem;
    }

    // Now user memory context can be released
    err_code = app_ble_user_mem_context_destroy(p_event->evt.common_evt.conn_handle);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    SER_EVT_DEC_END;
}

uint32_t ble_evt_user_mem_request_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      ble_evt_t * const     p_event,
                                      uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_EVT_USER_MEM_REQUEST, common, user_mem_request);

    SER_PULL_uint16(&p_event->evt.common_evt.conn_handle);
    SER_PULL_uint8(&p_event->evt.common_evt.params.user_mem_request.type);

    SER_EVT_DEC_END;
}

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t ble_evt_tx_complete_dec(uint8_t const * const p_buf,
                                 uint32_t              packet_len,
                                 ble_evt_t * const     p_event,
                                 uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_EVT_TX_COMPLETE, common, tx_complete);

    SER_PULL_uint16(&p_event->evt.common_evt.conn_handle);
    SER_PULL_uint8(&p_event->evt.common_evt.params.tx_complete.count);

    SER_EVT_DEC_END;
}


uint32_t ble_evt_data_length_changed_dec(uint8_t const * const p_buf,
                                         uint32_t              packet_len,
                                         ble_evt_t * const     p_event,
                                         uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_EVT_DATA_LENGTH_CHANGED, common, data_length_changed);

    SER_PULL_uint16(&p_event->evt.common_evt.conn_handle);
    SER_PULL_FIELD(&p_event->evt.common_evt.params.data_length_changed, ble_evt_data_length_changed_t_dec);

    SER_EVT_DEC_END;
}
#endif
