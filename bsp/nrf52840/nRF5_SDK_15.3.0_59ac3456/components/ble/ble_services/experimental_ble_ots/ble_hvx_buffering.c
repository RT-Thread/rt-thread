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

#include "ble_hvx_buffering.h"
#include <string.h>

uint32_t ble_hvx_init(ble_hvx_buf_t * p_ble_hvx_buf)
{
    if (p_ble_hvx_buf == NULL)
    {
        return NRF_ERROR_NULL;
    }
    
    p_ble_hvx_buf->insert_index = 0;
    p_ble_hvx_buf->read_index    = 0;

    return NRF_SUCCESS;    
}

ble_hvx_t * ble_hvx_get_p_to_next_hvx(ble_hvx_buf_t * p_ble_hvx_buf)
{
    ble_hvx_t * p_hvx;
    p_hvx = &p_ble_hvx_buf->buf[p_ble_hvx_buf->insert_index++];
    
    p_hvx->params.p_data = p_hvx->data;
    p_hvx->params.p_len  = &p_hvx->data_len;
    
    p_ble_hvx_buf->insert_index &= BLE_HVX_BUF_MASK;
    return p_hvx;
}


uint32_t ble_hvx_buffer_process(ble_hvx_buf_t * p_ble_hvx_buf)
{
    uint32_t err_code;
    while (p_ble_hvx_buf->read_index != p_ble_hvx_buf->insert_index)
    {
        
        ble_gatts_hvx_params_t * p_hvx_params;
        
        p_hvx_params = &p_ble_hvx_buf->buf[p_ble_hvx_buf->read_index].params;
        err_code = sd_ble_gatts_hvx(p_ble_hvx_buf->buf[p_ble_hvx_buf->read_index].conn_handle, p_hvx_params);

        if (err_code == NRF_SUCCESS)
        {
            p_ble_hvx_buf->read_index++;
            p_ble_hvx_buf->read_index &= BLE_HVX_BUF_MASK;
        }
        else
        {
            if (err_code == NRF_ERROR_BUSY || err_code == NRF_ERROR_RESOURCES)
            {
                return NRF_SUCCESS; // not a critical error. 
            }
            else
            {
                // remove element from buffer
                p_ble_hvx_buf->insert_index--;
                p_ble_hvx_buf->insert_index &= BLE_HVX_BUF_MASK;
                return err_code;
            }
        }
    }
    return NRF_SUCCESS;
}
