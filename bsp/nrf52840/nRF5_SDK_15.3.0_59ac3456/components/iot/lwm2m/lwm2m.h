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
/** @file lwm2m.h
 *
 * @defgroup iot_sdk_lwm2m_api LWM2M library private definitions.
 * @ingroup iot_sdk_lwm2m
 * @{
 * @brief LWM2M library private definitions.
 */

#ifndef LWM2M_H__
#define LWM2M_H__

#include "stdint.h"
#include "stdbool.h"
#include "coap_message.h"
#include "coap_codes.h"
#include "sdk_config.h"
#include "sdk_os.h"
#include "iot_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup iot_coap_mutex_lock_unlock Module's Mutex Lock/Unlock Macros.
 *
 * @details Macros used to lock and unlock modules. Currently, SDK does not use mutexes but
 *          framework is provided in case the need to use an alternative architecture arises.
 * @{
 */
#define LWM2M_MUTEX_LOCK()   SDK_MUTEX_LOCK(m_lwm2m_mutex)                                 /**< Lock module using mutex */
#define LWM2M_MUTEX_UNLOCK() SDK_MUTEX_UNLOCK(m_lwm2m_mutex)                               /**< Unlock module using mutex */

/** @} */

/**
 * @defgroup api_param_check API Parameters check macros.
 *
 * @details Macros that verify parameters passed to the module in the APIs. These macros
 *          could be mapped to nothing in final versions of code to save execution and size.
 *          LWM2M_DISABLE_API_PARAM_CHECK should be set to 0 to enable these checks.
 *
 * @{
 */
#if (LWM2M_DISABLE_API_PARAM_CHECK == 0)

/**@brief Verify NULL parameters are not passed to API by application. */
#define NULL_PARAM_CHECK(PARAM)                                                                    \
    if ((PARAM) == NULL)                                                                           \
    {                                                                                              \
        return (NRF_ERROR_NULL | IOT_LWM2M_ERR_BASE);                                              \
    }
#else

#define NULL_PARAM_CHECK(PARAM)

#endif // LWM2M_DISABLE_API_PARAM_CHECK

#define LWM2M_REQUEST_TYPE_BOOTSTRAP        1
#define LWM2M_REQUEST_TYPE_REGISTER         2
#define LWM2M_REQUEST_TYPE_UPDATE           3
#define LWM2M_REQUEST_TYPE_DEREGISTER       4

#ifdef __cplusplus
}
#endif

#endif // LWM2M_H__

/** @} */
