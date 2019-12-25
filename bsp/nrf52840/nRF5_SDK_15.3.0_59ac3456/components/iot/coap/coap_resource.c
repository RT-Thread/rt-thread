/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
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

#include "coap_resource.h"
#include "coap_api.h"
#include "iot_common.h"
#include "sdk_config.h"

#define COAP_RESOURCE_MAX_AGE_INIFINITE  0xFFFFFFFF

static coap_resource_t * mp_root_resource = NULL;
static char m_scratch_buffer[(COAP_RESOURCE_MAX_NAME_LEN + 1) * COAP_RESOURCE_MAX_DEPTH + 6];

#if (COAP_DISABLE_API_PARAM_CHECK == 0)

/**@brief Verify NULL parameters are not passed to API by application. */
#define NULL_PARAM_CHECK(PARAM)                                                                    \
    if ((PARAM) == NULL)                                                                           \
    {                                                                                              \
        return (NRF_ERROR_NULL | IOT_COAP_ERR_BASE);                                               \
    }
#else

#define NULL_PARAM_CHECK(PARAM)

#endif // COAP_DISABLE_API_PARAM_CHECK

uint32_t coap_resource_init(void)
{
    mp_root_resource = NULL;
    return NRF_SUCCESS;
}

uint32_t coap_resource_create(coap_resource_t * p_resource, const char * name)
{
    NULL_PARAM_CHECK(p_resource);
    NULL_PARAM_CHECK(name);

    if (strlen(name) > COAP_RESOURCE_MAX_NAME_LEN)
    {
        return (NRF_ERROR_DATA_SIZE | IOT_COAP_ERR_BASE);
    }

    memcpy(p_resource->name, name, strlen(name));

    if (mp_root_resource == NULL)
    {
        mp_root_resource = p_resource;
    }

    p_resource->max_age = COAP_RESOURCE_MAX_AGE_INIFINITE;

    return NRF_SUCCESS;
}

uint32_t coap_resource_child_add(coap_resource_t * p_parent, coap_resource_t * p_child)
{
    NULL_PARAM_CHECK(p_parent);
    NULL_PARAM_CHECK(p_child);

    if (p_parent->child_count == 0)
    {
        p_parent->p_front = p_child;
        p_parent->p_tail = p_child;
    }
    else
    {
        coap_resource_t * p_last_sibling = p_parent->p_tail;
        p_last_sibling->p_sibling = p_child;
        p_parent->p_tail = p_child;
    }

    p_parent->child_count++;

    return NRF_SUCCESS;
}

static uint32_t generate_path(uint16_t buffer_pos, coap_resource_t * p_current_resource, char * parent_path, uint8_t * string, uint16_t * length)
{
    uint32_t err_code = NRF_SUCCESS;

    if (parent_path == NULL)
    {
        m_scratch_buffer[buffer_pos++] = '<';

        if (p_current_resource->p_front != NULL)
        {
            coap_resource_t * next_child = p_current_resource->p_front;
            do
            {
                err_code = generate_path(buffer_pos, next_child, m_scratch_buffer, string, length);
                if (err_code != NRF_SUCCESS)
                {
                    return err_code;
                }
                next_child = next_child->p_sibling;
            } while (next_child != NULL);
        }
    }
    else
    {
        uint16_t size = strlen(p_current_resource->name);
        m_scratch_buffer[buffer_pos++] = '/';

        memcpy(&m_scratch_buffer[buffer_pos], p_current_resource->name, size);
        buffer_pos += size;

        if (p_current_resource->p_front != NULL)
        {
            coap_resource_t * next_child = p_current_resource->p_front;
            do
            {
                err_code = generate_path(buffer_pos, next_child, m_scratch_buffer, string, length);
                if (err_code != NRF_SUCCESS)
                {
                    return err_code;
                }
                next_child = next_child->p_sibling;
            } while (next_child != NULL);
        }

        m_scratch_buffer[buffer_pos++] = '>';

        // If the resource is observable, append 'obs;' token.
        if ((p_current_resource->permission & COAP_PERM_OBSERVE) > 0)
        {
           memcpy(&m_scratch_buffer[buffer_pos], ";obs", 4);
           buffer_pos += 4;
        }

        m_scratch_buffer[buffer_pos++] = ',';

        if (buffer_pos <= (*length))
        {
            *length -= buffer_pos;
            memcpy(&string[strlen((char *)string)], m_scratch_buffer, buffer_pos);
        }
        else
        {
            return (NRF_ERROR_DATA_SIZE | IOT_COAP_ERR_BASE);
        }
    }

    return err_code;
}

uint32_t coap_resource_well_known_generate(uint8_t * string, uint16_t * length)
{
    NULL_PARAM_CHECK(string);
    NULL_PARAM_CHECK(length);

    if (mp_root_resource == NULL)
    {
        return (NRF_ERROR_INVALID_STATE | IOT_COAP_ERR_BASE);
    }

    memset(string, 0, *length);

    uint32_t err_code = generate_path(0, mp_root_resource, NULL, string, length);

    string[strlen((char *)string) - 1] = '\0'; // remove the last comma

    return err_code;
}

static coap_resource_t * coap_resource_child_resolve(coap_resource_t * p_parent,
                                                     char *            p_path)
{
    coap_resource_t * result = NULL;
    if (p_parent->p_front != NULL)
    {
        coap_resource_t * sibling_in_question = p_parent->p_front;

        do {
            // Check if the sibling name match.
            size_t size = strlen(sibling_in_question->name);
            if (strncmp(sibling_in_question->name, p_path, size) == 0)
            {
                return sibling_in_question;
            }
            else
            {
                sibling_in_question = sibling_in_question->p_sibling;
            }
        } while (sibling_in_question != NULL);
    }
    return result;
}

uint32_t coap_resource_get(coap_resource_t ** p_resource, uint8_t ** pp_uri_pointers, uint8_t num_of_uris)
{
    if (mp_root_resource == NULL)
    {
        // Make sure pointer is set to NULL before returning.
        *p_resource = NULL;
        return (NRF_ERROR_INVALID_STATE | IOT_COAP_ERR_BASE);
    }

    coap_resource_t * p_current_resource = mp_root_resource;

    // Every node should start at root.
    for (uint8_t i = 0; i < num_of_uris; i++)
    {
        p_current_resource = coap_resource_child_resolve(p_current_resource, (char *)pp_uri_pointers[i]);

        if (p_current_resource == NULL)
        {
            // Stop looping as this direction will not give anything more.
            break;
        }
    }

    if (p_current_resource != NULL)
    {
        *p_resource = p_current_resource;
        return NRF_SUCCESS;
    }

    // If nothing has been found.
    *p_resource = NULL;
    return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
}

uint32_t coap_resource_root_get(coap_resource_t ** pp_resource)
{
    NULL_PARAM_CHECK(pp_resource);

    if (mp_root_resource == NULL)
    {
        return (NRF_ERROR_NOT_FOUND | IOT_COAP_ERR_BASE);
    }

    *pp_resource = mp_root_resource;

    return NRF_SUCCESS;
}
