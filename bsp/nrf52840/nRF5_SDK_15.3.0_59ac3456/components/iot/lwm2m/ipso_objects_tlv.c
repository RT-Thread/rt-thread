/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#include "ipso_objects_tlv.h"
#include "lwm2m_tlv.h"

static void index_buffer_len_update(uint32_t * index, uint32_t * buffer_len, uint32_t max_buffer)
{
    *index      += *buffer_len;
    *buffer_len  = max_buffer - *index;
}

uint32_t ipso_tlv_ipso_digital_output_decode(ipso_digital_output_t * p_digital_output,
                                             uint8_t *               p_buffer,
                                             uint32_t                buffer_len)
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
            case IPSO_RR_ID_DIGITAL_OUTPUT_STATE:
            {
                p_digital_output->digital_output_state = tlv.value[0];
                break;
            }

            case IPSO_RR_ID_DIGITAL_OUTPUT_POLARITY:
            {
                p_digital_output->digital_output_polarity = tlv.value[0];
                break;
            }

            case IPSO_RR_ID_APPLICATION_TYPE:
            {
                p_digital_output->application_type.p_val = (char *)tlv.value;
                p_digital_output->application_type.len   = tlv.length;
                break;
            }

            default:
                break;
        }
    }

    return NRF_SUCCESS;
}

uint32_t ipso_tlv_ipso_digital_output_encode(uint8_t *               p_buffer,
                                             uint32_t *              p_buffer_len,
                                             ipso_digital_output_t * p_digital_output)
{
    uint32_t err_code;
    uint32_t max_buffer = *p_buffer_len;
    uint32_t index = 0;

    lwm2m_tlv_t tlv;
    tlv.id_type = TLV_TYPE_RESOURCE_VAL; // type is the same for all.

    // Encode state.
    lwm2m_tlv_bool_set(&tlv, p_digital_output->digital_output_state, IPSO_RR_ID_DIGITAL_OUTPUT_STATE);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    // Encode polarity.
    lwm2m_tlv_bool_set(&tlv, p_digital_output->digital_output_polarity, IPSO_RR_ID_DIGITAL_OUTPUT_POLARITY);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    // Encode application type.
    lwm2m_tlv_string_set(&tlv, p_digital_output->application_type, IPSO_RR_ID_APPLICATION_TYPE);
    err_code = lwm2m_tlv_encode(p_buffer + index, p_buffer_len, &tlv);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    index_buffer_len_update(&index, p_buffer_len, max_buffer);

    *p_buffer_len = index;

    return NRF_SUCCESS;
}
