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
/** @file coap.h
 *
 * @defgroup iot_sdk_coap_api CoAP interface
 * @ingroup iot_sdk_coap
 * @{
 * @brief Interface for the CoAP protocol.
 */

#ifndef COAP_H__
#define COAP_H__

#include "iot_errors.h"
#include "coap_api.h"
#include "sdk_os.h"

/**
 * @defgroup iot_coap_log Module's Log Macros
 * @details Macros used for creating module logs which can be useful in understanding handling
 *          of events or actions on API requests. These are intended for debugging purposes and
 *          can be enabled by defining the COAP_ENABLE_LOGS to 1.
 * @note If NRF_LOG_ENABLED is disabled, having COAP_ENABLE_LOGS has no effect.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#if (COAP_DISABLE_API_PARAM_CHECK == 0)

/**@brief Verify NULL parameters are not passed to API by application. */
#define NULL_PARAM_CHECK(PARAM)                                                                    \
    if ((PARAM) == NULL)                                                                           \
    {                                                                                              \
        return (NRF_ERROR_NULL | IOT_COAP_ERR_BASE);                                               \
    }

/**@brief Verify that parameter members has been set by the application. */
#define NULL_PARAM_MEMBER_CHECK(PARAM)                                                             \
    if ((PARAM) == NULL)                                                                           \
    {                                                                                              \
        return (NRF_ERROR_INVALID_PARAM | IOT_COAP_ERR_BASE);                                      \
    }
#else

#define NULL_PARAM_CHECK(PARAM)
#define NULL_PARAM_MEMBER_CHECK(PARAM)

#endif // COAP_DISABLE_API_PARAM_CHECK

/**
 * @defgroup iot_coap_mutex_lock_unlock Module's Mutex Lock/Unlock Macros.
 *
 * @details Macros used to lock and unlock modules. Currently, SDK does not use mutexes but
 *          framework is provided in case the need to use an alternative architecture arises.
 * @{
 */
#define COAP_MUTEX_LOCK()   SDK_MUTEX_LOCK(m_coap_mutex)                                 /**< Lock module using mutex */
#define COAP_MUTEX_UNLOCK() SDK_MUTEX_UNLOCK(m_coap_mutex)                               /**< Unlock module using mutex */

SDK_MUTEX_DEFINE(m_coap_mutex)

/** @} */

/**@brief Sends a CoAP message.
 *
 * @details Sends out a request using the underlying transport layer. Before sending, the
 *          \ref coap_message_t structure is serialized and added to an internal message queue
 *          in the library.  The handle returned can be used to abort the message from being
 *          retransmitted at any time.
 *
 * @param[out] p_handle  Handle to the message if CoAP CON/ACK messages has been used. Returned
 *                       by reference.
 * @param[in]  p_message Message to be sent.
 *
 * @retval NRF_SUCCESS If the message was successfully encoded and scheduled for transmission.
 */
uint32_t internal_coap_message_send(uint32_t * p_handle, coap_message_t * p_message);

#ifdef __cplusplus
}
#endif

#endif // COAP_H__

/** @} */
