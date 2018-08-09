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
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "lwm2m_api.h"
#include "lwm2m_register.h"
#include "lwm2m_bootstrap.h"
#include "sdk_os.h"
#include "lwm2m.h"
#include "sdk_config.h"

#if LWM2M_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME lwm2m

#define NRF_LOG_LEVEL       LWM2M_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  LWM2M_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR LWM2M_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define LWM2M_TRC     NRF_LOG_DEBUG                                                                 /**< Used for getting trace of execution in the module. */
#define LWM2M_ERR     NRF_LOG_ERROR                                                                 /**< Used for logging errors in the module. */
#define LWM2M_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                         /**< Used for dumping octet information to get details of bond information etc. */

#define LWM2M_ENTRY() LWM2M_TRC(">> %s", __func__)
#define LWM2M_EXIT()  LWM2M_TRC("<< %s", __func__)

#else // LWM2M_CONFIG_LOG_ENABLED

#define LWM2M_TRC(...)                                                                              /**< Disables traces. */
#define LWM2M_DUMP(...)                                                                             /**< Disables dumping of octet streams. */
#define LWM2M_ERR(...)                                                                              /**< Disables error logs. */

#define LWM2M_ENTRY(...)
#define LWM2M_EXIT(...)

#endif // LWM2M_CONFIG_LOG_ENABLED

#if (LWM2M_CONFIG_LOG_ENABLED != 0)

static uint8_t op_desc_idx_lookup(uint8_t bitmask)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if ((bitmask > i) == 0x1)
        {
            return i;
        }
    }

    // If no bits where set in the bitmask.
    return 0;
}

static const char m_operation_desc[8][9] = {
    "NONE",
    "READ",
    "WRITE",
    "EXECUTE",
    "DELETE",
    "CREATE",
    "DISCOVER",
    "OBSERVE"
};

#endif

SDK_MUTEX_DEFINE(m_lwm2m_mutex)                                                           /**< Mutex variable. Currently unused, this declaration does not occupy any space in RAM. */

static lwm2m_object_prototype_t *   m_objects[LWM2M_COAP_HANDLER_MAX_OBJECTS];
static lwm2m_instance_prototype_t * m_instances[LWM2M_COAP_HANDLER_MAX_INSTANCES];
static uint16_t m_num_objects;
static uint16_t m_num_instances;

static void coap_error_handler(uint32_t error_code, coap_message_t * p_message)
{
    LWM2M_ERR("[CoAP]: Unhandled coap message recieved. Error code: %lu", error_code);
}

static void internal_coap_handler_init(void)
{
    memset(m_objects, 0, sizeof(m_objects));
    memset(m_instances, 0, sizeof(m_instances));

    m_num_objects   = 0;
    m_num_instances = 0;
}


static bool numbers_only(const char * p_str, uint16_t str_len)
{
    for (uint16_t i = 0; i < str_len; i++)
    {
        if (isdigit(p_str[i]) == 0)
        {
            return false;
        }
    }
    return true;
}


static uint32_t instance_resolve(lwm2m_instance_prototype_t ** p_instance,
                                          uint16_t             object_id,
                                          uint16_t             instance_id)
{
    for (int i = 0; i < m_num_instances; ++i)
    {
        if (m_instances[i]->object_id == object_id &&
            m_instances[i]->instance_id == instance_id)
        {
            if (m_instances[i]->callback == NULL)
            {
                return NRF_ERROR_NULL;
            }

            *p_instance = m_instances[i];

            return NRF_SUCCESS;
        }
    }

    return NRF_ERROR_NOT_FOUND;
}


static uint32_t object_resolve(lwm2m_object_prototype_t ** p_instance,
                               uint16_t                    object_id)
{
    for (int i = 0; i < m_num_objects; ++i)
    {
        if (m_objects[i]->object_id == object_id)
        {
            if (m_objects[i]->callback == NULL)
            {
                return NRF_ERROR_NULL;
            }

            *p_instance = m_objects[i];

            return NRF_SUCCESS;
        }
    }

    return NRF_ERROR_NOT_FOUND;
}

static uint32_t op_code_resolve(lwm2m_instance_prototype_t * p_instance,
                                uint16_t                     resource_id,
                                uint8_t *                    operation)
{
    uint8_t *  operations     = (uint8_t *) p_instance + p_instance->operations_offset;
    uint16_t * operations_ids = (uint16_t *)((uint8_t *) p_instance +
                                p_instance->resource_ids_offset);

    for (int j = 0; j < p_instance->num_resources; ++j)
    {
        if (operations_ids[j] == resource_id)
        {
            *operation = operations[j];
            return NRF_SUCCESS;
        }
    }

    return NRF_ERROR_NOT_FOUND;
}

static uint32_t internal_request_handle(coap_message_t * p_request,
                                        uint16_t *       p_path,
                                        uint8_t          path_len)
{
    uint32_t err_code;
    uint8_t  operation    = LWM2M_OPERATION_CODE_NONE;
    uint32_t content_type = 0;

    err_code = coap_message_ct_mask_get(p_request, &content_type);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    /**
     * TODO: the methods should check if we have read / write / execute rights
     *       through ACL and resource operations
     */

    switch (p_request->header.code)
    {
        case COAP_CODE_GET:
        {
            LWM2M_TRC("[CoAP]: CoAP GET request");
            if (content_type == COAP_CT_APP_LINK_FORMAT) // Discover
            {
                operation = LWM2M_OPERATION_CODE_DISCOVER;
            }
            else // Read
            {
                operation = LWM2M_OPERATION_CODE_READ;
            }
            break;
        }

        case COAP_CODE_PUT:
        {
            operation = LWM2M_OPERATION_CODE_WRITE;
            break;
        }

        case COAP_CODE_POST:
        {
            operation = LWM2M_OPERATION_CODE_WRITE;
            break;
        }

        case COAP_CODE_DELETE:
        {
            operation = LWM2M_OPERATION_CODE_DELETE;
            break;
        }

        default:
            break; // Maybe send response with unsupported method not allowed?
    }

    err_code = NRF_ERROR_NOT_FOUND;

    switch (path_len)
    {
        case 0:
        {
            if (operation == LWM2M_OPERATION_CODE_DELETE)
            {
                LWM2M_TRC("[CoAP]: >> %s root /",
                          m_operation_desc[op_desc_idx_lookup(operation)]);

                LWM2M_MUTEX_UNLOCK();

                err_code = lwm2m_coap_handler_root(LWM2M_OPERATION_CODE_DELETE, p_request);

                LWM2M_MUTEX_LOCK();

                LWM2M_TRC("[CoAP]: << %s root /",
                          m_operation_desc[op_desc_idx_lookup(operation)]);
            }
            break;
        }

        case 1:
        {
            LWM2M_TRC("[CoAP]: >> %s object /%u/",
                      m_operation_desc[op_desc_idx_lookup(operation)],
                      p_path[0]);

            lwm2m_object_prototype_t * p_object;

            err_code = object_resolve(&p_object, p_path[0]);

            if (err_code != NRF_SUCCESS)
            {
                break;
            }

            LWM2M_MUTEX_UNLOCK();

            err_code = p_object->callback(p_object, LWM2M_INVALID_INSTANCE, operation, p_request);

            LWM2M_MUTEX_LOCK();

            LWM2M_TRC("[CoAP]: << %s object /%u/, result: %s",
                      m_operation_desc[op_desc_idx_lookup(operation)],
                      p_path[0],
                      (err_code == NRF_SUCCESS) ? "SUCCESS" : "NOT_FOUND");

            break;
        }

        case 2:
        {
            LWM2M_TRC("[CoAP]: >> %s instance /%u/%u/",
                      m_operation_desc[op_desc_idx_lookup(operation)],
                      p_path[0],
                      p_path[1]);

            lwm2m_instance_prototype_t * p_instance;

            err_code = instance_resolve(&p_instance, p_path[0], p_path[1]);
            if (err_code == NRF_SUCCESS)
            {
                LWM2M_MUTEX_UNLOCK();

                err_code = p_instance->callback(p_instance, LWM2M_INVALID_RESOURCE, operation, p_request);

                LWM2M_MUTEX_LOCK();

                LWM2M_TRC("[CoAP]: << %s instance /%u/%u/, result: %s",
                          m_operation_desc[op_desc_idx_lookup(operation)],
                          p_path[0],
                          p_path[1],
                          (err_code == NRF_SUCCESS) ? "SUCCESS" : "NOT_FOUND");
                break;
            }

            // Bootstrap can write to non-existing instances
            if (err_code == NRF_ERROR_NOT_FOUND         &&
                operation == LWM2M_OPERATION_CODE_WRITE &&
                p_request->header.code == COAP_CODE_PUT)
            {
                LWM2M_TRC("[CoAP]: >> %s object /%u/%u/",
                          m_operation_desc[op_desc_idx_lookup(operation)],
                          p_path[0],
                          p_path[1]);

                lwm2m_object_prototype_t * p_object;

                err_code = object_resolve(&p_object, p_path[0]);

                if (err_code != NRF_SUCCESS)
                {
                    break;
                }

                LWM2M_MUTEX_UNLOCK();

                err_code = p_object->callback(p_object, p_path[1], operation, p_request);

                LWM2M_MUTEX_LOCK();

                LWM2M_TRC("[CoAP]: << %s object /%u/%u/, result: %s",
                          m_operation_desc[op_desc_idx_lookup(operation)],
                          p_path[0],
                          p_path[1],
                          (err_code == NRF_SUCCESS) ? "SUCCESS" : "NOT_FOUND");
            }

            if (err_code == NRF_ERROR_NOT_FOUND         &&
                operation == LWM2M_OPERATION_CODE_WRITE &&
                p_request->header.code == COAP_CODE_POST)
            {
                LWM2M_TRC("[CoAP]: >> CREATE object /%u/%u/",
                          p_path[0],
                          p_path[1]);

                lwm2m_object_prototype_t * p_object;

                err_code = object_resolve(&p_object, p_path[0]);

                if (err_code != NRF_SUCCESS)
                {
                    break;
                }

                LWM2M_MUTEX_UNLOCK();

                err_code = p_object->callback(p_object, p_path[1], LWM2M_OPERATION_CODE_CREATE, p_request);

                LWM2M_MUTEX_LOCK();

                LWM2M_TRC("[CoAP]: << CREATE object /%u/%u/, result: %s",
                          p_path[0],
                          p_path[1],
                          (err_code == NRF_SUCCESS) ? "SUCCESS" : "NOT_FOUND");
                break;
            }

            break;
        }

        case 3:
        {
            if (operation == LWM2M_OPERATION_CODE_DELETE)
            {
                // Deleting resources within an instance not allowed.
                break;
            }

            if (p_request->header.code == COAP_CODE_POST)
            {
                for (int i = 0; i < m_num_instances; ++i)
                {
                    if ((m_instances[i]->object_id == p_path[0]) &&
                        (m_instances[i]->instance_id == p_path[1]))
                    {
                        if (m_instances[i]->callback == NULL)
                        {
                            err_code = NRF_ERROR_NULL;
                            break;
                        }

                        uint8_t resource_operation = 0;
                        err_code = op_code_resolve(m_instances[i], p_path[2], &resource_operation);

                        if (err_code != NRF_SUCCESS)
                            break;

                        if ((resource_operation & LWM2M_OPERATION_CODE_EXECUTE) > 0)
                        {
                            operation = LWM2M_OPERATION_CODE_EXECUTE;
                        }

                        if ((resource_operation & LWM2M_OPERATION_CODE_WRITE) > 0)
                        {
                            operation = LWM2M_OPERATION_CODE_WRITE;
                        }

                        LWM2M_TRC("[CoAP]: >> %s instance /%u/%u/%u/",
                                  m_operation_desc[op_desc_idx_lookup(operation)],
                                  m_instances[i]->object_id,
                                  m_instances[i]->instance_id,
                                  p_path[2]);

                        LWM2M_MUTEX_UNLOCK();

                        (void)m_instances[i]->callback(m_instances[i],
                                                       p_path[2],
                                                       operation,
                                                       p_request);

                        LWM2M_MUTEX_LOCK();

                        err_code = NRF_SUCCESS;

                        LWM2M_TRC("[CoAP]: << %s instance /%u/%u/%u/",
                                  m_operation_desc[op_desc_idx_lookup(operation)],
                                  m_instances[i]->object_id,
                                  m_instances[i]->instance_id,
                                  p_path[2]);

                        break;
                    }
                }
            }
            else
            {
                LWM2M_TRC("[CoAP]: >> %s instance /%u/%u/%u/",
                          m_operation_desc[op_desc_idx_lookup(operation)],
                          p_path[0],
                          p_path[1],
                          p_path[2]);

                lwm2m_instance_prototype_t * p_instance;

                err_code = instance_resolve(&p_instance, p_path[0], p_path[1]);
                if (err_code != NRF_SUCCESS)
                {
                    break;
                }

                LWM2M_MUTEX_UNLOCK();

                err_code = p_instance->callback(p_instance, p_path[2], operation, p_request);

                LWM2M_MUTEX_LOCK();

                LWM2M_TRC("[CoAP]: << %s instance /%u/%u/%u/, result: %s",
                          m_operation_desc[op_desc_idx_lookup(operation)],
                          p_path[0],
                          p_path[1],
                          p_path[2],
                          (err_code == NRF_SUCCESS) ? "SUCCESS" : "NOT_FOUND");
            }
            break;
        }

        default:
            break;
    }

    return err_code;
}


static uint32_t lwm2m_coap_handler_handle_request(coap_message_t * p_request)
{
    LWM2M_ENTRY();

    uint16_t index;
    uint16_t path[3];
    char *   endptr;

    bool     is_numbers_only = true;
    uint16_t path_index      = 0;
    uint32_t err_code        = NRF_SUCCESS;

    LWM2M_MUTEX_LOCK();

    for (index = 0; index < p_request->options_count; index++)
    {
        if (p_request->options[index].number == COAP_OPT_URI_PATH)
        {
            uint16_t option_len = p_request->options[index].length;
            bool     numbers    = numbers_only((char *)p_request->options[index].p_data,
                                               option_len);

            if (numbers)
            {
                // Declare a temporary array that is 1 byte longer than the
                // option data in order to leave space for a terminating character.
                uint8_t option_data[option_len + 1];
                // Set the temporary array to zero.
                memset(option_data, 0, sizeof(option_data));
                // Copy the option data string to the temporary array.
                memcpy(option_data, p_request->options[index].p_data, option_len);

                // Convert the zero-terminated string to a long int value.
                path[path_index] = strtol((char *)option_data, &endptr, 10);

                ++path_index;

                if (endptr == ((char *)option_data))
                {
                    err_code = NRF_ERROR_NOT_FOUND;
                    break;
                }

                if (endptr != ((char *)option_data + option_len))
                {
                    err_code = NRF_ERROR_NOT_FOUND;
                    break;
                }
            }
            else
            {
                is_numbers_only = false;
                break;
            }
        }
    }

    if (err_code == NRF_SUCCESS)
    {
        if (is_numbers_only == true)
        {
            err_code = internal_request_handle(p_request, path, path_index);
        }
        else
        {
            // If uri path did not consist of numbers only.
            char * requested_uri = NULL;
            for (index = 0; index < p_request->options_count; index++)
            {
                if (p_request->options[index].number == COAP_OPT_URI_PATH)
                {
                    requested_uri = (char *)p_request->options[index].p_data;

                    // Stop on first URI hit.
                    break;
                }
            }

            if (requested_uri == NULL)
            {
                err_code = NRF_ERROR_NOT_FOUND;
            }
            else
            {
                // Try to look up if there is a match with object with an alias name.
                for (int i = 0; i < m_num_objects; ++i)
                {
                    if (m_objects[i]->object_id == LWM2M_NAMED_OBJECT)
                    {
                        size_t size = strlen(m_objects[i]->p_alias_name);
                        if ((strncmp(m_objects[i]->p_alias_name, requested_uri, size) == 0))
                        {
                            if (m_objects[i]->callback == NULL)
                            {
                                err_code = NRF_ERROR_NULL;
                                break;
                            }

                            LWM2M_MUTEX_UNLOCK();

                            err_code = m_objects[i]->callback(m_objects[i],
                                                              LWM2M_INVALID_INSTANCE,
                                                              LWM2M_OPERATION_CODE_NONE,
                                                              p_request);

                            LWM2M_MUTEX_LOCK();

                            break;
                        }
                    }
                    else
                    {
                        // This is not a name object, return error code.
                        err_code = NRF_ERROR_NOT_FOUND;
                        break;
                    }
                }
            }
        }
    }

    LWM2M_MUTEX_UNLOCK();

    LWM2M_EXIT();

    return err_code;
}


uint32_t lwm2m_coap_handler_instance_add(lwm2m_instance_prototype_t * p_instance)
{
    LWM2M_ENTRY();

    NULL_PARAM_CHECK(p_instance);

    LWM2M_MUTEX_LOCK();

    if (m_num_instances == LWM2M_COAP_HANDLER_MAX_INSTANCES)
    {
        LWM2M_MUTEX_UNLOCK();

        return NRF_ERROR_NO_MEM;
    }

    m_instances[m_num_instances] = p_instance;
    ++m_num_instances;

    LWM2M_MUTEX_UNLOCK();

    return NRF_SUCCESS;
}


uint32_t lwm2m_coap_handler_instance_delete(lwm2m_instance_prototype_t * p_instance)
{
    LWM2M_ENTRY();

    NULL_PARAM_CHECK(p_instance);

    LWM2M_MUTEX_LOCK();

    for (int i = 0; i < m_num_instances; ++i)
    {
        if ((m_instances[i]->object_id == p_instance->object_id) &&
            (m_instances[i]->instance_id == p_instance->instance_id))
        {
            // Move current last entry into this index position, and trim down the length.
            // If this is the last element, it cannot be accessed because the m_num_instances
            // count is 0.
            m_instances[i] = m_instances[m_num_instances - 1];
            --m_num_instances;

            LWM2M_MUTEX_UNLOCK();

            return NRF_SUCCESS;
        }
    }

    LWM2M_MUTEX_UNLOCK();

    return NRF_ERROR_NOT_FOUND;
}


uint32_t lwm2m_coap_handler_object_add(lwm2m_object_prototype_t * p_object)
{
    LWM2M_ENTRY();

    NULL_PARAM_CHECK(p_object);

    LWM2M_MUTEX_LOCK();

    if (m_num_objects == LWM2M_COAP_HANDLER_MAX_INSTANCES)
    {
        LWM2M_MUTEX_UNLOCK();

        return NRF_ERROR_NO_MEM;
    }

    m_objects[m_num_objects] = p_object;
    ++m_num_objects;

    LWM2M_MUTEX_UNLOCK();

    return NRF_SUCCESS;
}


uint32_t lwm2m_coap_handler_object_delete(lwm2m_object_prototype_t * p_object)
{
    LWM2M_ENTRY();

    NULL_PARAM_CHECK(p_object);

    LWM2M_MUTEX_LOCK();

    for (int i = 0; i < m_num_objects; ++i)
    {
        if ( m_objects[i]->object_id == p_object->object_id)
        {
            // Move current last entry into this index position, and trim down the length.
            // If this is the last element, it cannot be accessed because the m_num_objects
            // count is 0.
            m_objects[i] = m_objects[m_num_objects - 1];
            --m_num_objects;

            LWM2M_MUTEX_UNLOCK();

            return NRF_SUCCESS;
        }
    }

    LWM2M_MUTEX_UNLOCK();

    return NRF_ERROR_NOT_FOUND;
}


uint32_t lwm2m_coap_handler_gen_link_format(uint8_t * p_buffer, uint16_t * p_buffer_len)
{

    LWM2M_ENTRY();

    NULL_PARAM_CHECK(p_buffer_len);

    LWM2M_MUTEX_LOCK();

    uint16_t  buffer_index = 0;
    uint8_t * p_string_buffer;
    uint16_t  buffer_max_size;

    uint8_t   dry_run_buffer[16];
    bool      dry_run      = false;
    uint16_t  dry_run_size = 0;

    if (p_buffer == NULL)
    {
        // Dry-run only, in order to calculate the size of the needed buffer.
        dry_run = true;
        p_string_buffer = dry_run_buffer;
        buffer_max_size = sizeof(dry_run_buffer);
    }
    else
    {
        p_string_buffer = p_buffer;
        buffer_max_size = *p_buffer_len;
    }

    for (int i = 0; i < m_num_objects; ++i)
    {
        // We need more than 3 chars to write a new link
        if (buffer_max_size - buffer_index <= 3)
        {
            LWM2M_MUTEX_UNLOCK();

            return NRF_ERROR_NO_MEM;
        }

        uint16_t curr_object = m_objects[i]->object_id;

        if (curr_object == LWM2M_NAMED_OBJECT)
        {
            // Skip this object as it is a named object.
            continue;
        }

        bool instance_present = false;
        for (int j = 0; j < m_num_instances; ++j)
        {
            if (m_instances[j]->object_id == curr_object)
            {
                instance_present = true;

                buffer_index += snprintf((char *)&p_string_buffer[buffer_index],
                                         buffer_max_size - buffer_index,
                                         "</%u/%u>,",
                                         m_instances[j]->object_id,
                                         m_instances[j]->instance_id);
                if (dry_run == true)
                {
                    dry_run_size += buffer_index;
                    buffer_index = 0;
                }
            }
        }

        if (!instance_present)
        {
            buffer_index += snprintf((char *)&p_string_buffer[buffer_index],
                                     buffer_max_size - buffer_index,
                                     "</%u>,",
                                     curr_object);
            if (dry_run == true)
            {
                dry_run_size += buffer_index;
                buffer_index = 0;
            }
        }
    }

    if (dry_run == true)
    {
        *p_buffer_len = dry_run_size - 1;
    }
    else
    {
        *p_buffer_len = buffer_index - 1; // Remove the last comma
    }

    LWM2M_MUTEX_UNLOCK();

    return NRF_SUCCESS;
}


uint32_t lwm2m_init(void)
{
    SDK_MUTEX_INIT(m_lwm2m_mutex);

    LWM2M_MUTEX_LOCK();

    uint32_t err_code;

    err_code = internal_lwm2m_register_init();
    if (err_code != NRF_SUCCESS)
    {
        LWM2M_MUTEX_UNLOCK();
        return err_code;
    }

    err_code = internal_lwm2m_bootstrap_init();
    if (err_code != NRF_SUCCESS)
    {
        LWM2M_MUTEX_UNLOCK();
        return err_code;
    }

    err_code = coap_error_handler_register(coap_error_handler);
    if (err_code != NRF_SUCCESS)
    {
        LWM2M_MUTEX_UNLOCK();
        return err_code;
    }

    internal_coap_handler_init();

    err_code = coap_request_handler_register(lwm2m_coap_handler_handle_request);

    LWM2M_MUTEX_UNLOCK();

    return err_code;
}
