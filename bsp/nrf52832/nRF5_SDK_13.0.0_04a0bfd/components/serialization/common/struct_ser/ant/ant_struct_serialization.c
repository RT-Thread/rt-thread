/**
 * Copyright (c) 2017 - 2017, Nordic Semiconductor ASA
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

#include "ant_interface.h"
#include "ant_struct_serialization.h"
#include "ant_stack_handler_types.h"
#include "ble_serialization.h"
#include "app_util.h"
#include "cond_field_serialization.h"
#include <string.h>


uint32_t ANT_ENABLE_enc(void const * const p_void_enable_params,
                        uint8_t * const    p_buf,
                        uint32_t           buf_len,
                        uint32_t * const   p_index)
{
    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_index);
    SER_ASSERT_NOT_NULL(p_void_enable_params);

    ANT_ENABLE * p_enable_params = (ANT_ENABLE *)p_void_enable_params;
    uint32_t err_code = NRF_SUCCESS;

    err_code = uint8_t_enc(&p_enable_params->ucTotalNumberOfChannels, p_buf, buf_len, p_index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = uint8_t_enc(&p_enable_params->ucNumberOfEncryptedChannels, p_buf, buf_len, p_index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = uint16_t_enc(&p_enable_params->usNumberOfEvents, p_buf, buf_len, p_index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = uint32_t_enc(&p_enable_params->pucMemoryBlockStartLocation, p_buf, buf_len, p_index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = uint16_t_enc(&p_enable_params->usMemoryBlockByteSize, p_buf, buf_len, p_index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}


uint32_t ANT_ENABLE_dec(uint8_t const * const p_buf,
                        uint32_t              buf_len,
                        uint32_t * const      p_index,
                        void * const          p_void_enable_params)

{
    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_index);
    SER_ASSERT_NOT_NULL(p_void_enable_params);

    ANT_ENABLE * p_enable_params = (ANT_ENABLE *)p_void_enable_params;
    uint32_t err_code = NRF_SUCCESS;

    err_code = uint8_t_dec(p_buf, buf_len, p_index, &p_enable_params->ucTotalNumberOfChannels);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = uint8_t_dec(p_buf, buf_len, p_index, &p_enable_params->ucNumberOfEncryptedChannels);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = uint16_t_dec(p_buf, buf_len, p_index, &p_enable_params->usNumberOfEvents);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = uint32_t_dec(p_buf, buf_len, p_index, &p_enable_params->pucMemoryBlockStartLocation);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = uint16_t_dec(p_buf, buf_len, p_index, &p_enable_params->usMemoryBlockByteSize);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t ant_evt_t_enc(void const * const p_void_ant_evt,
                       uint8_t * const    p_buf,
                       uint32_t           buf_len,
                       uint32_t * const   p_index)
{
    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_index);
    SER_ASSERT_NOT_NULL(p_void_ant_evt);

    ant_evt_t * p_ant_evt = (ant_evt_t *)p_void_ant_evt;
    uint32_t err_code = NRF_SUCCESS;

    memcpy(&p_buf[*p_index], p_ant_evt->msg.evt_buffer, ANT_STACK_EVT_MSG_BUF_SIZE); // Size + sizeof(size) & sizeof(msg id)
    *p_index += ANT_STACK_EVT_MSG_BUF_SIZE;

    err_code = uint8_t_enc(&p_ant_evt->event, p_buf, buf_len, p_index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = uint8_t_enc(&p_ant_evt->channel, p_buf, buf_len, p_index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return(err_code);
}

uint32_t ant_evt_t_dec(uint8_t const * const p_buf,
                       uint32_t              buf_len,
                       uint32_t * const      p_index,
                       void * const          p_void_ant_evt)

{
    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_index);
    SER_ASSERT_NOT_NULL(p_void_ant_evt);

    ant_evt_t * p_ant_evt = (ant_evt_t *)p_void_ant_evt;
    uint32_t err_code = NRF_SUCCESS;

    memcpy(p_ant_evt->msg.evt_buffer, &p_buf[*p_index], ANT_STACK_EVT_MSG_BUF_SIZE); // Size + sizeof(size) & sizeof(msg id)
    *p_index += ANT_STACK_EVT_MSG_BUF_SIZE;

    err_code = uint8_t_dec(p_buf, buf_len, p_index, &p_ant_evt->event);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = uint8_t_dec(p_buf, buf_len, p_index, &p_ant_evt->channel);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}
