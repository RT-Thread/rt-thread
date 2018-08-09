/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
#include "nrf_soc.h"
#include "nordic_common.h"
#include "sdk_common.h"
#include "sdk_config.h"
#include "iot_common.h"
#include "iot_pbuffer.h"
#include "mem_manager.h"

#if IOT_PBUFFER_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME pbuffer

#define NRF_LOG_LEVEL       IOT_PBUFFER_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  IOT_PBUFFER_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR IOT_PBUFFER_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define PBUFFER_TRC     NRF_LOG_DEBUG                                                               /**< Used for getting trace of execution in the module. */
#define PBUFFER_ERR     NRF_LOG_ERROR                                                               /**< Used for logging errors in the module. */
#define PBUFFER_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                       /**< Used for dumping octet information to get details of bond information etc. */

#define PBUFFER_ENTRY() PBUFFER_TRC(">> %s", __func__)
#define PBUFFER_EXIT()  PBUFFER_TRC("<< %s", __func__)

#else // IOT_PBUFFER_CONFIG_LOG_ENABLED

#define PBUFFER_TRC(...)                                                                            /**< Disables traces. */
#define PBUFFER_DUMP(...)                                                                           /**< Disables dumping of octet streams. */
#define PBUFFER_ERR(...)                                                                            /**< Disables error logs. */

#define PBUFFER_ENTRY(...)
#define PBUFFER_EXIT(...)

#endif // IOT_PBUFFER_CONFIG_LOG_ENABLED

/**
 * @defgroup api_param_check API Parameters check macros.
 *
 * @details Macros that verify parameters passed to the module in the APIs. These macros
 *          could be mapped to nothing in final versions of code to save execution and size.
 *          BLE_HPS_DISABLE_API_PARAM_CHECK should be defined to disable these checks.
 *
 * @{
 */
#if (IOT_PBUFFER_DISABLE_API_PARAM_CHECK == 0)

/**@brief Macro to check is module is initialized before requesting one of the module procedures. */
#define VERIFY_MODULE_IS_INITIALIZED()                                                             \
        if (m_initialization_state == false)                                                       \
        {                                                                                          \
            return (SDK_ERR_MODULE_NOT_INITIALIZED | IOT_PBUFFER_ERR_BASE);                        \
        }

/**@brief Macro to check is module is initialized before requesting one of the module
         procedures but does not use any return code. */
#define VERIFY_MODULE_IS_INITIALIZED_VOID()                                                        \
        if (m_initialization_state == false)                                                       \
        {                                                                                          \
            return;                                                                                \
        }

/**
 * @brief Verify NULL parameters are not passed to API by application.
 */
#define NULL_PARAM_CHECK(PARAM)                                                                    \
        if ((PARAM) == NULL)                                                                       \
        {                                                                                          \
            return (NRF_ERROR_NULL | IOT_PBUFFER_ERR_BASE);                                        \
        }

/**
 * @brief Verify Type field has valid value.
 */
#define VERIFY_PBUFFER_TYPE(TYPE)                                                                  \
        if (((TYPE) == 0) || ((TYPE) > COAP_PACKET_TYPE))                                          \
        {                                                                                          \
           return (NRF_ERROR_INVALID_PARAM | IOT_PBUFFER_ERR_BASE);                                \
        }


/**
 * @brief Verify flags field has valid value.
 */
#define VERIFY_PBUFFER_FLAGS(FLAG)                                                                 \
        if ((uint32_t)(FLAG) > PBUFFER_FLAG_NO_MEM_ALLOCATION)                                     \
        {                                                                                          \
           return (NRF_ERROR_INVALID_PARAM | IOT_PBUFFER_ERR_BASE);                                \
        }

/**
 * @brief Verify flags field has valid value.
 */
#define VERIFY_NON_ZERO_LENGTH(LEN)                                                                \
        if ((LEN) ==0)                                                                             \
        {                                                                                          \
           return (NRF_ERROR_INVALID_LENGTH | IOT_PBUFFER_ERR_BASE);                               \
        }

#else //IOT_PBUFFER_DISABLE_API_PARAM_CHECK

#define VERIFY_MODULE_IS_INITIALIZED()
#define VERIFY_MODULE_IS_INITIALIZED_VOID()
#define NULL_PARAM_CHECK(PARAM)
#define VERIFY_PBUFFER_TYPE(TYPE)
#define VERIFY_PBUFFER_FLAGS(FLAG)
#define VERIFY_NON_ZERO_LENGTH(LEN)

#endif //IOT_PBUFFER_DISABLE_API_PARAM_CHECK

/**
 * @defgroup ble_ipsp_mutex_lock_unlock Module's Mutex Lock/Unlock Macros.
 *
 * @details Macros used to lock and unlock modules. Currently, SDK does not use mutexes but
 *          framework is provided in case need arises to use an alternative architecture.
 * @{
 */
#define PBUFFER_MUTEX_LOCK()   SDK_MUTEX_LOCK(m_pbuffer_mutex)                                /**< Lock module using mutex */
#define PBUFFER_MUTEX_UNLOCK() SDK_MUTEX_UNLOCK(m_pbuffer_mutex)                              /**< Unlock module using mutex */
/** @} */

/** @brief Packet buffer type managed by the module. */
typedef struct
{
   iot_pbuffer_t  buffer;                                                                     /**< Packet buffer being managed. */
   uint32_t       allocated_length;                                                           /**< Length allocated for the buffer. */
}pbuffer_t;

SDK_MUTEX_DEFINE(m_pbuffer_mutex)                                                             /**< Mutex variable. Currently unused, this declaration does not occupy any space in RAM. */
static bool      m_initialization_state  = false;                                             /**< Variable to maintain module initialization state. */
static pbuffer_t m_pbuffer[IOT_PBUFFER_MAX_COUNT];                                            /**< Table of packet buffers managed by the module. */


/**@brief Initializes packet buffer. */
static void pbuffer_init(pbuffer_t * p_buffer)
{
    p_buffer->buffer.p_memory  = NULL;
    p_buffer->buffer.p_payload = NULL;
    p_buffer->buffer.length    = 0;
    p_buffer->buffer.type      = UNASSIGNED_TYPE;
    p_buffer->allocated_length = 0;
}


/**@brief Get size of offset to be used based on the requested type. */
static uint32_t type_offset_get(iot_pbuffer_type_t type)
{
    uint32_t offset = 0;

    switch (type)
    {
        case RAW_PACKET_TYPE:
        {
            offset = 0;
            break;
        }
        case IPV6_PACKET_TYPE:
        {
           offset = IPV6_IP_HEADER_SIZE;
           break;
        }
        case ICMP6_PACKET_TYPE:
        {
            offset = IPV6_IP_HEADER_SIZE + ICMP6_HEADER_SIZE;
            break;
        }
        case UDP6_PACKET_TYPE:   // Fall through.
        {
            offset = IPV6_IP_HEADER_SIZE + UDP_HEADER_SIZE;
            break;
        }
        case COAP_PACKET_TYPE:
        {
            offset = IPV6_IP_HEADER_SIZE + UDP_HEADER_SIZE + COAP_HEADER_SIZE;
            break;
        }
        default:
        {
            // Should never happen.
            break;
        }
    }

    return offset;
}


/**@brief Allocates 'length' sized packet buffer. */
static uint32_t pbuffer_allocate(pbuffer_t ** pp_buffer, uint32_t length, iot_pbuffer_flags_t flags)
{
    uint32_t index;
    uint32_t err_code = (NRF_ERROR_NO_MEM | IOT_PBUFFER_ERR_BASE);


    for (index = 0; index < IOT_PBUFFER_MAX_COUNT; index ++)
    {
        if (m_pbuffer[index].allocated_length == 0)
        {
            // Found a free buffer, allocate.
            PBUFFER_TRC("Found free buffer. Requesting memory allocation.");

            m_pbuffer[index].allocated_length = length;

            if (flags == PBUFFER_FLAG_DEFAULT)
            {
                err_code = nrf_mem_reserve(&m_pbuffer[index].buffer.p_memory, &m_pbuffer[index].allocated_length);
                if (err_code == NRF_SUCCESS)
                {
                    PBUFFER_TRC("Allocated pbuffer at index 0x%08lX", index);
                    (*pp_buffer)  = &m_pbuffer[index];
                }
                else
                {
                    PBUFFER_ERR("Failed to allocate memory for packet buffer of size %ld", length);
                    m_pbuffer[index].allocated_length  = 0;
                }
            }
            else
            {
                PBUFFER_TRC("Allocated pbuffer at index 0x%08lX without any memory allocation.", index);
                (*pp_buffer)  = &m_pbuffer[index];
                err_code = NRF_SUCCESS;
            }
            break;
        }
    }

    return err_code;
}


/**@brief Finds the internal buffer based on the external iot_pbuffer_t. */
static uint32_t pbuffer_find(pbuffer_t ** p_internal_buffer, iot_pbuffer_t * p_buffer)
{
    const uint32_t size  = sizeof (pbuffer_t);
    const uint32_t diff  = (((uint32_t)p_buffer) - ((uint32_t)m_pbuffer));

    if ((diff > (size * IOT_PBUFFER_MAX_COUNT)) ||
        ((diff % size) != 0))
    {
        return (NRF_ERROR_INVALID_ADDR | IOT_PBUFFER_ERR_BASE);
    }

    (*p_internal_buffer) = (pbuffer_t *) p_buffer;

    return NRF_SUCCESS;
}


uint32_t iot_pbuffer_init(void)
{
    uint32_t index;

    PBUFFER_ENTRY();

    SDK_MUTEX_INIT(m_pbuffer_mutex);

    PBUFFER_MUTEX_LOCK();

    for (index = 0; index < IOT_PBUFFER_MAX_COUNT; index++)
    {
        pbuffer_init(&m_pbuffer[index]);
    }

    m_initialization_state = true;

    PBUFFER_EXIT();

    PBUFFER_MUTEX_UNLOCK();

    return NRF_SUCCESS;
}


uint32_t iot_pbuffer_allocate(iot_pbuffer_alloc_param_t    *  p_param,
                              iot_pbuffer_t                ** pp_pbuffer)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_param);
    NULL_PARAM_CHECK(pp_pbuffer);
    VERIFY_PBUFFER_TYPE(p_param->type);
    VERIFY_PBUFFER_FLAGS(p_param->flags);
    VERIFY_NON_ZERO_LENGTH(p_param->length);

    PBUFFER_ENTRY();

    PBUFFER_MUTEX_LOCK();

    uint32_t  err_code;
    uint32_t  offset;
    pbuffer_t * p_alloc_buffer;

    // Get offset to be added to length.
    offset = type_offset_get(p_param->type);

    err_code = pbuffer_allocate(&p_alloc_buffer, ((p_param->length) + offset), p_param->flags);
    if (err_code == NRF_SUCCESS)
    {
        p_alloc_buffer->buffer.length = p_param->length;
        p_alloc_buffer->buffer.type   = p_param->type;

        if (p_param->flags != PBUFFER_FLAG_NO_MEM_ALLOCATION)
        {
            p_alloc_buffer->buffer.p_payload = ((p_alloc_buffer->buffer.p_memory) + offset);
        }

        (*pp_pbuffer) = &p_alloc_buffer->buffer;
    }

    PBUFFER_MUTEX_UNLOCK();

    PBUFFER_EXIT();

    return err_code;
}


uint32_t iot_pbuffer_reallocate(iot_pbuffer_alloc_param_t  * p_param,
                                iot_pbuffer_t              * p_pbuffer)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_param);
    NULL_PARAM_CHECK(p_pbuffer);
    VERIFY_PBUFFER_TYPE(p_param->type);
    VERIFY_PBUFFER_FLAGS(p_param->flags);
    VERIFY_NON_ZERO_LENGTH(p_param->length);

    PBUFFER_ENTRY();

    PBUFFER_MUTEX_LOCK();

    uint32_t    err_code;
    uint32_t    realloc_len;
    pbuffer_t * p_alloc_buffer;

    // Ensure pointer provided is in the ranged managed by the module.
    err_code = pbuffer_find(&p_alloc_buffer, p_pbuffer);

    if (err_code == NRF_SUCCESS)
    {
        // Get realloc_len to be added to length.
        const uint32_t offset = type_offset_get(p_param->type);
        realloc_len = p_param->length + offset;

        // Check if requested length cannot be accommodated in the allocated buffer.
        if (realloc_len > p_alloc_buffer->allocated_length)
        {
            // No, it cannot be, request a new buffer.
            uint8_t * p_new_mem;

            if (p_param->flags != PBUFFER_FLAG_NO_MEM_ALLOCATION)
            {
                err_code = nrf_mem_reserve(&p_new_mem, &realloc_len);
                if (err_code == NRF_SUCCESS)
                {
                    // Copy data into the new buffer.
                    memcpy (p_new_mem,
                            p_pbuffer->p_memory,
                            p_alloc_buffer->allocated_length);

                    // Now free the old buffer. Perform the free
                    nrf_free(p_alloc_buffer->buffer.p_memory);

                    p_alloc_buffer->allocated_length = realloc_len;
                    p_alloc_buffer->buffer.p_memory  = p_new_mem;
                    p_alloc_buffer->buffer.length    = p_param->length;
                }
            }
        }

        if (err_code == NRF_SUCCESS)
        {
            p_alloc_buffer->buffer.length    = p_param->length;
            p_alloc_buffer->buffer.type      = p_param->type;

            if (p_param->flags == PBUFFER_FLAG_DEFAULT)
            {
                p_alloc_buffer->buffer.p_payload = (p_alloc_buffer->buffer.p_memory + offset);
            }
        }
    }
    else
    {
        PBUFFER_ERR("Cannot find buffer to be freed.");
    }

    PBUFFER_MUTEX_UNLOCK();

    PBUFFER_EXIT();

    return err_code;
}


uint32_t iot_pbuffer_free(iot_pbuffer_t  * p_pbuffer, bool free_flag)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_pbuffer);

    PBUFFER_ENTRY();

    PBUFFER_MUTEX_LOCK();

    uint32_t   err_code;
    pbuffer_t * p_alloc_buffer;

    // Ensure pointer provided is in the ranged managed by the module.
    err_code = pbuffer_find(&p_alloc_buffer, p_pbuffer);
    if (err_code == NRF_SUCCESS)
    {
        if (free_flag == true)
        {
            nrf_free(p_alloc_buffer->buffer.p_memory);
        }
        pbuffer_init(p_alloc_buffer);
    }
    else
    {
        PBUFFER_ERR("Cannot find buffer to be freed.");
    }

    PBUFFER_MUTEX_UNLOCK();

    PBUFFER_EXIT();

    return err_code;
}
