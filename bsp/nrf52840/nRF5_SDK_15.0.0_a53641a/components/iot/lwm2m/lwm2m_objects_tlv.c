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
#include "lwm2m_objects_tlv.h"
#include "lwm2m_tlv.h"

static void index_buffer_len_update(uint32_t * index, uint32_t * buffer_len, uint32_t max_buffer)
{
    *index      += *buffer_len;
    *buffer_len  = max_buffer - *index;
}

uint32_t lwm2m_tlv_server_decode(lwm2m_server_t * server, uint8_t * buffer, uint32_t buffer_len)
{
    uint32_t    err_code;
    lwm2m_tlv_t tlv;

    uint32_t index = 0;

    while (index < buffer_len)
    {
        err_code = lwm2m_tlv_decode(&tlv, &index, buffer, buffer_len);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }

        switch (tlv.id)
        {
            case LWM2M_SERVER_SHORT_SERVER_ID:
            {
                if (lwm2m_tlv_bytebuffer_to_uint16(tlv.value, tlv.length, &server->short_server_id) != NRF_SUCCESS)
                {
                    return NRF_ERROR_INVALID_DATA;
                }

                break;
            }

            case LWM2M_SERVER_LIFETIME:
            {
                if (lwm2m_tlv_bytebuffer_to_uint32(tlv.value, tlv.length, &server->lifetime))
                {
                    return NRF_ERROR_INVALID_DATA;
                }
                break;
            }

            case LWM2M_SERVER_DEFAULT_MIN_PERIOD:
            {
                if (lwm2m_tlv_bytebuffer_to_uint32(tlv.value, tlv.length, &server->default_minimum_period))
                {
                    return NRF_ERROR_INVALID_DATA;
                }
                break;
            }

            case LWM2M_SERVER_DEFAULT_MAX_PERIOD:
            {
                if (lwm2m_tlv_bytebuffer_to_uint32(tlv.value, tlv.length, &server->default_maximum_period))
                {
                    return NRF_ERROR_INVALID_DATA;
                }
                break;
            }

            case LWM2M_SERVER_DISABLE:
            {
                // Execute do nothing
                break;
            }

            case LWM2M_SERVER_DISABLE_TIMEOUT:
            {
                if (lwm2m_tlv_bytebuffer_to_uint32(tlv.value, tlv.length, &server->disable_timeout))
                {
                    return NRF_ERROR_INVALID_DATA;
                }
                break;
            }

            case LWM2M_SERVER_NOTIFY_WHEN_DISABLED:
            {
                server->notification_storing_on_disabled = tlv.value[0];
                break;
            }
            case LWM2M_SERVER_BINDING:
            {
                // If original buffer is gone this will also be gone
                server->binding.len = tlv.length;
                server->binding.p_val = (char *) tlv.value;
                break;
            }

            case LWM2M_SERVER_REGISTRATION_UPDATE_TRIGGER:
            {
                // Execute do nothing
                break;
            }

            default:
                break;
        }
    }

    return NRF_SUCCESS;
}


uint32_t lwm2m_tlv_security_decode(lwm2m_security_t * p_security,
                                   uint8_t *          p_buffer,
                                   uint32_t           buffer_len)
{
    uint32_t    err_code;
    lwm2m_tlv_t tlv;

    uint32_t index = 0;

    while (index < buffer_len)
    {
        err_code = lwm2m_tlv_decode(&tlv, &index, p_buffer, buffer_len);

        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }

        switch (tlv.id)
        {
            case LWM2M_SECURITY_SERVER_URI:
            {
                p_security->server_uri.p_val = (char *)tlv.value;
                p_security->server_uri.len   = tlv.length;
                break;
            }

            case LWM2M_SECURITY_BOOTSTRAP_SERVER:
            {
                p_security->bootstrap_server = tlv.value[0];
                break;
            }

            case LWM2M_SECURITY_SECURITY_MODE:
            {
                p_security->security_mode = tlv.value[0];
                break;
            }

            case LWM2M_SECURITY_PUBLIC_KEY:
            {
                p_security->public_key.p_val = tlv.value;
                p_security->public_key.len   = tlv.length;
                break;
            }

            case LWM2M_SECURITY_SERVER_PUBLIC_KEY:
            {
                p_security->server_public_key.p_val = tlv.value;
                p_security->server_public_key.len   = tlv.length;
                break;
            }

            case LWM2M_SECURITY_SECRET_KEY:
            {
                p_security->secret_key.p_val = tlv.value;
                p_security->secret_key.len   = tlv.length;
                break;
            }

            case LWM2M_SECURITY_SMS_SECURITY_MODE:
            {
                p_security->sms_security_mode = tlv.value[0];
                break;
            }

            case LWM2M_SECURITY_SMS_BINDING_KEY_PARAM:
            {
                p_security->sms_binding_key_param.p_val = tlv.value;
                p_security->sms_binding_key_param.len   = tlv.length;
                break;
            }

            case LWM2M_SECURITY_SMS_BINDING_SECRET_KEY:
            {
                p_security->sms_binding_secret_keys.p_val = tlv.value;
                p_security->sms_binding_secret_keys.len   = tlv.length;
                break;
            }

            case LWM2M_SECURITY_SERVER_SMS_NUMBER:
            {
                uint32_t result = lwm2m_tlv_bytebuffer_to_uint32(tlv.value,
                                                                 tlv.length,
                                                                 &p_security->sms_number);
                if (result != NRF_SUCCESS)
                {
                    return NRF_ERROR_INVALID_DATA;
                }
                break;
            }

            case LWM2M_SECURITY_SHORT_SERVER_ID:
            {
                uint32_t result = lwm2m_tlv_bytebuffer_to_uint16(tlv.value,
                                                                 tlv.length,
                                                                 &p_security->short_server_id);
                if (result != NRF_SUCCESS)
                {
                    return NRF_ERROR_INVALID_DATA;
                }
                break;
            }

            case LWM2M_SECURITY_CLIENT_HOLD_OFF_TIME:
            {
                uint32_t result = lwm2m_tlv_bytebuffer_to_uint32(tlv.value,
                                                                 tlv.length,
                                                                 &p_security->client_hold_off_time);
                if (result != NRF_SUCCESS)
                {
                    return NRF_ERROR_INVALID_DATA;
                }
                break;
            }

            default:
                break;
        }
    }

    return NRF_SUCCESS;
}


uint32_t lwm2m_tlv_server_encode(uint8_t *        p_buffer,
                                 uint32_t *       p_buffer_len,
                                 lwm2m_server_t * p_server)
{
    uint32_t err_code;
    uint32_t max_buffer = *p_buffer_len;
    uint32_t index      = 0;

    lwm2m_tlv_t tlv;
    tlv.id_type = TLV_TYPE_RESOURCE_VAL; // Type is the same for all.

    // Encode short server id.
    lwm2m_tlv_uint16_set(&tlv, p_server->short_server_id, LWM2M_SERVER_SHORT_SERVER_ID);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    // Encode lifetime.
    lwm2m_tlv_uint32_set(&tlv, p_server->lifetime, LWM2M_SERVER_LIFETIME);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    // Encode default minimum period.
    lwm2m_tlv_uint32_set(&tlv, p_server->default_minimum_period, LWM2M_SERVER_DEFAULT_MIN_PERIOD);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    // Encode default maximum period.
    lwm2m_tlv_uint32_set(&tlv, p_server->default_maximum_period, LWM2M_SERVER_DEFAULT_MAX_PERIOD);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    // Encode disable timeout.
    lwm2m_tlv_uint32_set(&tlv, p_server->disable_timeout, LWM2M_SERVER_DISABLE_TIMEOUT);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    // Encode Notify when disabled.
    lwm2m_tlv_bool_set(&tlv, p_server->notification_storing_on_disabled, LWM2M_SERVER_NOTIFY_WHEN_DISABLED);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    // Encode binding.
    lwm2m_tlv_string_set(&tlv, p_server->binding, LWM2M_SERVER_BINDING);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    *p_buffer_len = index;

    return NRF_SUCCESS;
}


uint32_t lwm2m_tlv_security_encode(uint8_t *          p_buffer,
                                   uint32_t *         p_buffer_len,
                                   lwm2m_security_t * p_security)
{
    uint32_t err_code;
    uint32_t max_buffer = *p_buffer_len;
    uint32_t index = 0;

    lwm2m_tlv_t tlv;
    tlv.id_type = TLV_TYPE_RESOURCE_VAL; // type is the same for all.


    lwm2m_tlv_string_set(&tlv, p_security->server_uri, LWM2M_SECURITY_SERVER_URI);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    lwm2m_tlv_bool_set(&tlv, p_security->bootstrap_server, LWM2M_SECURITY_BOOTSTRAP_SERVER);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    lwm2m_tlv_uint16_set(&tlv, p_security->security_mode, LWM2M_SECURITY_SECURITY_MODE);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    lwm2m_tlv_opaque_set(&tlv, p_security->public_key, LWM2M_SECURITY_PUBLIC_KEY);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    lwm2m_tlv_opaque_set(&tlv, p_security->server_public_key, LWM2M_SECURITY_SERVER_PUBLIC_KEY);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    lwm2m_tlv_opaque_set(&tlv, p_security->secret_key, LWM2M_SECURITY_SECRET_KEY);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    lwm2m_tlv_uint16_set(&tlv, p_security->sms_security_mode, LWM2M_SECURITY_SMS_SECURITY_MODE);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    lwm2m_tlv_opaque_set(&tlv, p_security->sms_binding_key_param, LWM2M_SECURITY_SMS_BINDING_KEY_PARAM);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    lwm2m_tlv_opaque_set(&tlv, p_security->sms_binding_secret_keys, LWM2M_SECURITY_SMS_BINDING_SECRET_KEY);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    lwm2m_tlv_uint32_set(&tlv, p_security->sms_number, LWM2M_SECURITY_SERVER_SMS_NUMBER);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    lwm2m_tlv_uint16_set(&tlv, p_security->short_server_id, LWM2M_SECURITY_SHORT_SERVER_ID);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    lwm2m_tlv_uint32_set(&tlv, p_security->client_hold_off_time, LWM2M_SECURITY_CLIENT_HOLD_OFF_TIME);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    return NRF_SUCCESS;
}
