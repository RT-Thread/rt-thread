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
#include "nordic_common.h"
#include "sdk_common.h"
#include "sdk_config.h"
#include "iot_common.h"
#include "iot_context_manager.h"

#if IOT_CONTEXT_MANAGER_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME context_manager

#define NRF_LOG_LEVEL       IOT_CONTEXT_MANAGER_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  IOT_CONTEXT_MANAGER_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR IOT_CONTEXT_MANAGER_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define CM_TRC     NRF_LOG_DEBUG                                                              /**< Used for getting trace of execution in the module. */
#define CM_ERR     NRF_LOG_ERROR                                                              /**< Used for logging errors in the module. */
#define CM_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                      /**< Used for dumping octet information to get details of bond information etc. */

#define CM_ENTRY()                       CM_TRC(">> %s", __func__)
#define CM_EXIT()                        CM_TRC("<< %s", __func__)

#else // IOT_CONTEXT_MANAGER_CONFIG_LOG_ENABLED

#define CM_TRC(...)                                                                           /**< Disables traces. */
#define CM_DUMP(...)                                                                          /**< Disables dumping of octet streams. */
#define CM_ERR(...)                                                                           /**< Disables error logs. */

#define CM_ENTRY(...)
#define CM_EXIT(...)

#endif // IOT_CONTEXT_MANAGER_CONFIG_LOG_ENABLED

/**@brief Parameter maximum values. */
#define CID_VALUE_MAX                15
#define PREFIX_LENGTH_VALUE_MAX      128

/**
 * @defgroup api_param_check API Parameters check macros.
 *
 * @details Macros that verify parameters passed to the module in the APIs. These macros
 *          could be mapped to nothing in final versions of code to save execution and size.
 *          IOT_CONTEXT_MANAGER_DISABLE_API_PARAM_CHECK should be defined to disable these checks.
 *
 * @{
 */
#if (IOT_CONTEXT_MANAGER_DISABLE_API_PARAM_CHECK == 0)

/**@brief Macro to check is module is initialized before requesting one of the module procedures. */
#define VERIFY_MODULE_IS_INITIALIZED()                                                             \
        if (m_initialization_state == false)                                                       \
        {                                                                                          \
            return (SDK_ERR_MODULE_NOT_INITIALIZED | IOT_CONTEXT_MANAGER_ERR_BASE);                \
        }

/**@brief Macro to check is module is initialized before requesting one of the module procedures. */
#define VERIFY_MODULE_IS_INITIALIZED_NULL()                                                        \
        if (m_initialization_state == false)                                                       \
        {                                                                                          \
            return NULL;                                                                           \
        }

/**
 * @brief Verify NULL parameters are not passed to API by application.
 */
#define NULL_PARAM_CHECK(PARAM)                                                                    \
        if ((PARAM) == NULL)                                                                       \
        {                                                                                          \
            return (NRF_ERROR_NULL | IOT_CONTEXT_MANAGER_ERR_BASE);                                \
        }

/**
 * @brief Verify CID has valid value.
 */
#define VERIFY_CID_VALUE(CID)                                                                      \
        if (!((CID) <= CID_VALUE_MAX))                                                             \
        {                                                                                          \
           return (NRF_ERROR_INVALID_PARAM | IOT_CONTEXT_MANAGER_ERR_BASE);                        \
        }

/**
 * @brief Verify prefix length value.
 */
#define VERIFY_PREFIX_LEN_VALUE(PREFIX_LEN)                                                        \
        if (!(PREFIX_LEN <= PREFIX_LENGTH_VALUE_MAX))                                              \
        {                                                                                          \
           return (NRF_ERROR_INVALID_PARAM | IOT_CONTEXT_MANAGER_ERR_BASE);                        \
        }

#else // IOT_IOT_CONTEXT_MANAGER_DISABLE_API_PARAM_CHECK

#define VERIFY_MODULE_IS_INITIALIZED()
#define VERIFY_MODULE_IS_INITIALIZED_NULL()
#define NULL_PARAM_CHECK(PARAM)
#define VERIFY_CID_VALUE(CID)
#define VERIFY_PREFIX_LEN_VALUE(PREFIX_LEN)

#endif //IOT_CONTEXT_MANAGER_DISABLE_API_PARAM_CHECK
/** @} */

/**
 * @defgroup iot_context_manager_mutex_lock_unlock Module's Mutex Lock/Unlock Macros.
 *
 * @details Macros used to lock and unlock modules. Currently, SDK does not use mutexes but
 *          framework is provided in case need arises to use an alternative architecture.
 * @{
 */
#define CM_MUTEX_LOCK()   SDK_MUTEX_LOCK(m_iot_context_manager_mutex)                               /**< Lock module using mutex */
#define CM_MUTEX_UNLOCK() SDK_MUTEX_UNLOCK(m_iot_context_manager_mutex)                             /**< Unlock module using mutex */
/** @} */

/**@brief Context table, managing by IPv6 stack. */
typedef struct
{
    iot_interface_t * p_interface;                                                                  /**< IoT interface pointer. */
    uint8_t           context_count;                                                                /**< Number of valid contexts in the table. */
    iot_context_t     contexts[IOT_CONTEXT_MANAGER_MAX_CONTEXTS];                                   /**< Array of valid contexts. */
}iot_context_table_t;


SDK_MUTEX_DEFINE(m_iot_context_manager_mutex)                                                       /**< Mutex variable. Currently unused, this declaration does not occupy any space in RAM. */
static bool                m_initialization_state = false;                                          /**< Variable to maintain module initialization state. */
static iot_context_table_t m_context_table[IOT_CONTEXT_MANAGER_MAX_TABLES];                         /**< Array of contexts table managed by the module. */

/**@brief Initializes context entry. */
static void context_init(iot_context_t * p_context)
{
    p_context->context_id       = IPV6_CONTEXT_IDENTIFIER_NONE;
    p_context->prefix_len       = 0;
    p_context->compression_flag = false;

    memset(p_context->prefix.u8, 0, IPV6_ADDR_SIZE);
}


/**@brief Initializes context table. */
static void context_table_init(uint32_t table_id)
{
    uint32_t index;

    for (index = 0; index < IOT_CONTEXT_MANAGER_MAX_CONTEXTS; index++)
    {
        context_init(&m_context_table[table_id].contexts[index]);
        m_context_table[table_id].context_count = 0;
        m_context_table[table_id].p_interface   = NULL;
    }
}


/**@brief Initializes context table. */
static uint32_t context_table_find(const iot_interface_t * p_interface)
{
    uint32_t index;

    for (index = 0; index < IOT_CONTEXT_MANAGER_MAX_TABLES; index++)
    {
        if (m_context_table[index].p_interface == p_interface)
        {
            break;
        }
    }

    return index;
}


/**@brief Looks up context table for specific context identifier. */
static uint32_t context_find_by_cid(uint32_t         table_id,
                                    uint8_t          context_id,
                                    iot_context_t ** pp_context)
{
    uint32_t index;

    for (index = 0; index < IOT_CONTEXT_MANAGER_MAX_CONTEXTS; index++)
    {
        if (m_context_table[table_id].contexts[index].context_id == context_id)
        {
              *pp_context = &m_context_table[table_id].contexts[index];
              return NRF_SUCCESS;
        }
    }

    return (NRF_ERROR_NOT_FOUND | IOT_CONTEXT_MANAGER_ERR_BASE);
}


static uint32_t context_find_by_prefix(uint32_t               table_id,
                                       const ipv6_addr_t    * p_prefix,
                                       iot_context_t       ** pp_context)
{
    uint32_t index;
    uint32_t context_left;
    uint16_t context_cmp_len;
    iot_context_t * p_best_match = NULL;

    context_left = m_context_table[table_id].context_count;

    for (index = 0; index < IOT_CONTEXT_MANAGER_MAX_CONTEXTS && context_left; index++)
    {
        if (m_context_table[table_id].contexts[index].context_id != IPV6_CONTEXT_IDENTIFIER_NONE &&
            m_context_table[table_id].contexts[index].compression_flag == true)
        {
              if ((context_cmp_len = m_context_table[table_id].contexts[index].prefix_len) < 64)
              {
                  context_cmp_len = 64;
              }

              // Check if address have matched in CID table.
              if (IPV6_ADDRESS_PREFIX_CMP(m_context_table[table_id].contexts[index].prefix.u8,
                                          p_prefix->u8,
                                          context_cmp_len))
              {
                  if (p_best_match == NULL || p_best_match->prefix_len <
                    m_context_table[table_id].contexts[index].prefix_len)
                  {
                      p_best_match = &m_context_table[table_id].contexts[index];
                  }
              }

            // Decrease left context in table, to avoid too many checking.
            context_left--;
        }
    }

    if (p_best_match)
    {
        *pp_context = p_best_match;
        return NRF_SUCCESS;
    }

    return (NRF_ERROR_NOT_FOUND | IOT_CONTEXT_MANAGER_ERR_BASE);
}


/**@brief Looks up for first empty entry in the table. */
static uint32_t context_find_free(uint32_t table_id, iot_context_t ** pp_context)
{
    uint32_t index;

    for (index = 0; index < IOT_CONTEXT_MANAGER_MAX_CONTEXTS; index++)
    {
        if (m_context_table[table_id].contexts[index].context_id == IPV6_CONTEXT_IDENTIFIER_NONE)
        {
            *pp_context = &m_context_table[table_id].contexts[index];
            return NRF_SUCCESS;
        }
    }

    return (NRF_ERROR_NO_MEM | IOT_CONTEXT_MANAGER_ERR_BASE);
}


uint32_t iot_context_manager_init(void)
{
    uint32_t index;

    CM_ENTRY();

    SDK_MUTEX_INIT(m_iot_context_manager_mutex);

    CM_MUTEX_LOCK();

    for (index = 0; index < IOT_CONTEXT_MANAGER_MAX_TABLES; index++)
    {
        context_table_init(index);
    }

    m_initialization_state = true;

    CM_MUTEX_UNLOCK();

    CM_EXIT();

    return NRF_SUCCESS;
}


uint32_t iot_context_manager_table_alloc(const iot_interface_t * p_interface)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_interface);

    uint32_t err_code = NRF_SUCCESS;

    CM_ENTRY();

    CM_MUTEX_LOCK();

    const uint32_t table_id = context_table_find(NULL);

    if (table_id != IOT_CONTEXT_MANAGER_MAX_TABLES)
    {
        // Found a free context table and assign to it.
        CM_TRC("Assigned new context table.");
        m_context_table[table_id].p_interface = (iot_interface_t *)p_interface;
    }
    else
    {
        // No free context table found.
        CM_ERR("No context table found.");
        err_code = (NRF_ERROR_NO_MEM | IOT_CONTEXT_MANAGER_ERR_BASE);
    }

    CM_MUTEX_UNLOCK();

    CM_EXIT();

    return err_code;
}


uint32_t iot_context_manager_table_free(const iot_interface_t * p_interface)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_interface);

    uint32_t err_code = NRF_SUCCESS;

    CM_ENTRY();

    SDK_MUTEX_INIT(m_iot_context_manager_mutex);

    CM_MUTEX_LOCK();

    const uint32_t table_id = context_table_find(p_interface);

    if (table_id != IOT_CONTEXT_MANAGER_MAX_TABLES)
    {
        // Clear context table.
        CM_TRC("Found context table assigned to interface.");
        context_table_init(table_id);
    }
    else
    {
        // No free context table found.
        CM_ERR("No context table found.");
        err_code = (NRF_ERROR_NOT_FOUND | IOT_CONTEXT_MANAGER_ERR_BASE);
    }

    CM_MUTEX_UNLOCK();

    CM_EXIT();

    return err_code;
}


uint32_t iot_context_manager_update(const iot_interface_t * p_interface,
                                    iot_context_t         * p_context)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_context);
    VERIFY_CID_VALUE(p_context->context_id);
    VERIFY_PREFIX_LEN_VALUE(p_context->prefix_len);

    uint32_t        retval   = NRF_SUCCESS;
    uint32_t        err_code = NRF_SUCCESS;
    iot_context_t * p_internal_context;

    CM_ENTRY();

    CM_MUTEX_LOCK();

    const uint32_t table_id = context_table_find(p_interface);

    if (table_id != IOT_CONTEXT_MANAGER_MAX_TABLES)
    {
          // Try to find context in context table.
          retval = context_find_by_cid(table_id, p_context->context_id, &p_internal_context);

          if (retval != NRF_SUCCESS)
          {
              err_code = context_find_free(table_id, &p_internal_context);

              // Increase context count.
              if (err_code == NRF_SUCCESS)
              {
                  m_context_table[table_id].context_count++;
              }
          }

          if (err_code == NRF_SUCCESS)
          {
               // Update context table, with parameters from application.
               p_internal_context->context_id       = p_context->context_id;
               p_internal_context->prefix_len       = p_context->prefix_len;
               p_internal_context->compression_flag = p_context->compression_flag;
               memset(p_internal_context->prefix.u8, 0, IPV6_ADDR_SIZE);
               IPV6_ADDRESS_PREFIX_SET(p_internal_context->prefix.u8, p_context->prefix.u8, p_context->prefix_len);
           }
           else
           {
               CM_ERR("No place in context table.");
           }
    }
    else
    {
        // No free context table found.
        CM_ERR("No context table found.");
        err_code = (NRF_ERROR_NOT_FOUND | IOT_CONTEXT_MANAGER_ERR_BASE);
    }

    CM_MUTEX_UNLOCK();

    CM_EXIT();

    return err_code;
}


uint32_t iot_context_manager_remove(const iot_interface_t * p_interface,
                                    iot_context_t         * p_context)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_interface);
    NULL_PARAM_CHECK(p_context);

    uint32_t err_code  = NRF_SUCCESS;

    CM_ENTRY();

    CM_MUTEX_LOCK();

    const uint32_t table_id = context_table_find(p_interface);

    if (table_id != IOT_CONTEXT_MANAGER_MAX_TABLES)
    {
        if (p_context->context_id != IPV6_CONTEXT_IDENTIFIER_NONE)
        {
            m_context_table[table_id].context_count--;
        }

        // Reinit context entry.
        context_init(p_context);
    }
    else
    {
        // No free context table found.
        CM_ERR("No context table found.");
        err_code = (NRF_ERROR_NOT_FOUND | IOT_CONTEXT_MANAGER_ERR_BASE);
    }

    CM_MUTEX_UNLOCK();

    CM_EXIT();

    return err_code;
}


uint32_t iot_context_manager_get_by_addr(const iot_interface_t * p_interface,
                                         const ipv6_addr_t     * p_addr,
                                         iot_context_t        ** pp_context)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_interface);
    NULL_PARAM_CHECK(p_addr);
    NULL_PARAM_CHECK(pp_context);

    uint32_t err_code;

    CM_ENTRY();

    CM_MUTEX_LOCK();

    const uint32_t table_id = context_table_find(p_interface);

    if (table_id != IOT_CONTEXT_MANAGER_MAX_TABLES)
    {
        err_code = context_find_by_prefix(table_id, p_addr, pp_context);
    }
    else
    {
        // No free context table found.
        CM_ERR("No context table found.");
        err_code = (NRF_ERROR_NOT_FOUND | IOT_CONTEXT_MANAGER_ERR_BASE);
    }

    CM_MUTEX_UNLOCK();

    CM_EXIT();

    return err_code;
}


uint32_t iot_context_manager_get_by_cid(const iot_interface_t * p_interface,
                                        uint8_t           context_id,
                                        iot_context_t  ** pp_context)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_interface);
    NULL_PARAM_CHECK(pp_context);
    VERIFY_CID_VALUE(context_id);

    uint32_t err_code;

    CM_ENTRY();

    CM_MUTEX_LOCK();

    const uint32_t table_id = context_table_find(p_interface);

    if (table_id != IOT_CONTEXT_MANAGER_MAX_TABLES)
    {
        err_code = context_find_by_cid(table_id, context_id, pp_context);
    }
    else
    {
        // No free context table found.
        CM_TRC("No context table found.");
        err_code = (NRF_ERROR_NOT_FOUND | IOT_CONTEXT_MANAGER_ERR_BASE);
    }

    CM_MUTEX_UNLOCK();

    CM_EXIT();

    return err_code;
}
