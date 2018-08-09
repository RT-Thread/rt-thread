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
#include "iot_timer.h"
#include "sdk_common.h"
#include "sdk_config.h"
#include "iot_errors.h"

/**
 * @defgroup api_param_check API Parameters check macros.
 *
 * @details Macros that verify parameters passed to the module in the APIs. These macros
 *          could be mapped to nothing in final versions of code to save execution and size.
 *          IOT_TIMER_DISABLE_API_PARAM_CHECK should be defined to disable these checks.
 *
 * @{
 */
#if (IOT_TIMER_DISABLE_API_PARAM_CHECK == 0)

/**
 * @brief Verify NULL parameters are not passed to API by application.
 */
#define NULL_PARAM_CHECK(PARAM)                                                                    \
        if ((PARAM) == NULL)                                                                       \
        {                                                                                          \
            return (NRF_ERROR_NULL | IOT_TIMER_ERR_BASE);                                          \
        }

#define VERIFY_CLIENT_LIST_IS_VALID(PARAM)                                                         \
        if ((PARAM) != NULL)                                                                       \
        {                                                                                          \
            uint8_t i;                                                                             \
            for (i = 0; i < (PARAM)->client_list_length; i++)                                      \
            {                                                                                      \
                if (((PARAM)->p_client_list[i].iot_timer_callback) == NULL)                        \
                {                                                                                  \
                    return (NRF_ERROR_INVALID_PARAM | IOT_TIMER_ERR_BASE);                         \
                }                                                                                  \
                if (((PARAM)->p_client_list[i].cb_interval == 0)                          ||       \
                    ((PARAM)->p_client_list[i].cb_interval < IOT_TIMER_RESOLUTION_IN_MS)  ||       \
                    (((PARAM)->p_client_list[i].cb_interval % IOT_TIMER_RESOLUTION_IN_MS) != 0))   \
                {                                                                                  \
                    return (NRF_ERROR_INVALID_PARAM | IOT_TIMER_ERR_BASE);                         \
                }                                                                                  \
            }                                                                                      \
        }

#define VERIFY_WALL_CLOCK_VALUE_IS_VALID(PARAM)                                                    \
        if ((PARAM) != NULL)                                                                       \
        {                                                                                          \
            if ((*PARAM % IOT_TIMER_RESOLUTION_IN_MS) != 0)                                        \
            {                                                                                      \
                return (NRF_ERROR_INVALID_PARAM | IOT_TIMER_ERR_BASE);                             \
            }                                                                                      \
        }

/**
 * @brief Verify NULL parameters are not passed to API by application.
 */
#define NULL_PARAM_CHECK(PARAM)                                                                    \
        if ((PARAM) == NULL)                                                                       \
        {                                                                                          \
            return (NRF_ERROR_NULL | IOT_TIMER_ERR_BASE);                                          \
        }

#else // IOT_TIMER_DISABLE_API_PARAM_CHECK

#define NULL_PARAM_CHECK(PARAM)
#define VERIFY_CLIENT_LIST_IS_VALID(PARAM)
#define VERIFY_WALL_CLOCK_VALUE_IS_VALID(PARAM)

#endif //IOT_TIMER_DISABLE_API_PARAM_CHECK
/** @} */

static iot_timer_time_in_ms_t           m_wall_clock = 0;
static const iot_timer_clients_list_t * m_clients    = NULL;


uint32_t iot_timer_client_list_set(const iot_timer_clients_list_t * p_list_of_clients)
{
    VERIFY_CLIENT_LIST_IS_VALID(p_list_of_clients);

    m_clients = p_list_of_clients;
    return NRF_SUCCESS;
}


uint32_t iot_timer_update(void)
{
    m_wall_clock += IOT_TIMER_RESOLUTION_IN_MS;
    if ((0xFFFFFFFFUL - m_wall_clock) < IOT_TIMER_RESOLUTION_IN_MS)
    {
        m_wall_clock = IOT_TIMER_RESOLUTION_IN_MS;
    }
    if (m_clients != NULL)
    {
        uint8_t index;
        for (index = 0; index < m_clients->client_list_length; index++)
        {
            if ((m_wall_clock % m_clients->p_client_list[index].cb_interval) == 0)
            {
                m_clients->p_client_list[index].iot_timer_callback(m_wall_clock);
            }
        }
    }
    return NRF_SUCCESS;
}


uint32_t iot_timer_wall_clock_get(iot_timer_time_in_ms_t * p_elapsed_time)
{
    NULL_PARAM_CHECK(p_elapsed_time);

    *p_elapsed_time = m_wall_clock;
    return NRF_SUCCESS;
}


uint32_t iot_timer_wall_clock_delta_get(iot_timer_time_in_ms_t * p_past_time, \
                                        iot_timer_time_in_ms_t * p_delta_time)
{
    NULL_PARAM_CHECK(p_past_time);
    NULL_PARAM_CHECK(p_delta_time);
    VERIFY_WALL_CLOCK_VALUE_IS_VALID(p_past_time);

    if (*p_past_time == m_wall_clock)
    {
        *p_delta_time = 0;
    }
    else if (*p_past_time < m_wall_clock)
    {
        *p_delta_time = m_wall_clock - *p_past_time;
    }
    else
    {
        // An integer overflow of the wall clock occured since *p_past_time.

        iot_timer_time_in_ms_t max_wall_clock = (0xFFFFFFFFUL / IOT_TIMER_RESOLUTION_IN_MS) \
                                                    * IOT_TIMER_RESOLUTION_IN_MS;
        *p_delta_time = max_wall_clock - *p_past_time; // Before overflow.
        *p_delta_time += m_wall_clock;                 // After overflow.
        *p_delta_time -= IOT_TIMER_RESOLUTION_IN_MS;   // Because of handling of wall clock integer overflow, see above.
    }

    return NRF_SUCCESS;
}
