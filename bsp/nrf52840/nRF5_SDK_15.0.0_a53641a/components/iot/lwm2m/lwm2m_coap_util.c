/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
#include <string.h>
#include "coap_api.h"
#include "coap_message.h"
#include "coap_codes.h"
#include "lwm2m.h"


uint32_t lwm2m_respond_with_code(coap_msg_code_t code, coap_message_t * p_request)
{
    NULL_PARAM_CHECK(p_request);

    // Application helper function, no need for mutex.
    coap_message_conf_t response_config;
    memset (&response_config, 0, sizeof(coap_message_conf_t));

    if (p_request->header.type == COAP_TYPE_NON)
    {
        response_config.type = COAP_TYPE_NON;
    }
    else if (p_request->header.type == COAP_TYPE_CON)
    {
        response_config.type = COAP_TYPE_ACK;
    }

    // PIGGY BACKED RESPONSE
    response_config.code              = code;
    response_config.id                = p_request->header.id;
    response_config.port.port_number  = p_request->port.port_number;

    // Copy token.
    memcpy(&response_config.token[0], &p_request->token[0], p_request->header.token_len);
    // Copy token length.
    response_config.token_len = p_request->header.token_len;

    coap_message_t * p_response;
    uint32_t err_code = coap_message_new(&p_response, &response_config);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = coap_message_remote_addr_set(p_response, &p_request->remote);
    if (err_code != NRF_SUCCESS)
    {
        (void)coap_message_delete(p_response);
        return err_code;
    }

    memcpy(&p_response->remote, &p_request->remote, sizeof(coap_remote_t));

    uint32_t msg_handle;
    err_code = coap_message_send(&msg_handle, p_response);
    if (err_code != NRF_SUCCESS)
    {
        (void)coap_message_delete(p_response);
        return err_code;
    }

    err_code = coap_message_delete(p_response);

    return err_code;
}


uint32_t lwm2m_respond_with_payload(uint8_t * p_payload, uint16_t payload_len, coap_message_t * p_request)
{
    NULL_PARAM_CHECK(p_request);
    NULL_PARAM_CHECK(p_payload);

    // Application helper function, no need for mutex.
    coap_message_conf_t response_config;
    memset (&response_config, 0, sizeof(coap_message_conf_t));

    if (p_request->header.type == COAP_TYPE_NON)
    {
        response_config.type = COAP_TYPE_NON;
    }
    else if (p_request->header.type == COAP_TYPE_CON)
    {
        response_config.type = COAP_TYPE_ACK;
    }

    // PIGGY BACKED RESPONSE
    response_config.code              = COAP_CODE_205_CONTENT;
    response_config.id                = p_request->header.id;
    response_config.port.port_number  = p_request->port.port_number;

    // Copy token.
    memcpy(&response_config.token[0], &p_request->token[0], p_request->header.token_len);
    // Copy token length.
    response_config.token_len = p_request->header.token_len;

    coap_message_t * p_response;
    uint32_t err_code = coap_message_new(&p_response, &response_config);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = coap_message_payload_set(p_response, p_payload, payload_len);
    if (err_code != NRF_SUCCESS)
    {
        (void)coap_message_delete(p_response);
        return err_code;
    }

    err_code = coap_message_remote_addr_set(p_response, &p_request->remote);
    if (err_code != NRF_SUCCESS)
    {
        (void)coap_message_delete(p_response);
        return err_code;
    }

    memcpy(&p_response->remote, &p_request->remote, sizeof(coap_remote_t));

    uint32_t msg_handle;
    err_code = coap_message_send(&msg_handle, p_response);
    if (err_code != NRF_SUCCESS)
    {
        (void)coap_message_delete(p_response);
        return err_code;
    }

    err_code = coap_message_delete(p_response);

    return err_code;
}
