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
/**
 * @addtogroup ser_conn Connectivity application code
 * @ingroup ble_sdk_lib_serialization
 */


/** @file
 *
 * @defgroup ser_conn_handlers Events handlers in the Connectivity Chip
 * @{
 * @ingroup ser_conn
 *
 * @brief   Events handlers used to process high level events in the connectivity application.
 *
 * @details This file contains functions: processing the HAL Transport layer events, processing BLE
 *          SoftDevice events, starting processing received packets.
 */

#ifndef SER_CONN_HANDLERS_H__
#define SER_CONN_HANDLERS_H__

#include <stdint.h>
#include "nordic_common.h"
#include "app_util.h"
#include "ser_hal_transport.h"

#ifdef BLE_STACK_SUPPORT_REQD
#include "ble.h"
#include "nrf_sdh_ble.h"
#endif // BLE_STACK_SUPPORT_REQD

#ifdef ANT_STACK_SUPPORT_REQD
#include "nrf_sdh_ant.h"
#endif // ANT_STACK_SUPPORT_REQD

#ifdef __cplusplus
extern "C" {
#endif

/** Maximum number of events in the application scheduler queue. */
#ifdef S112
#define SER_CONN_SCHED_QUEUE_SIZE             8u
#else
#define SER_CONN_SCHED_QUEUE_SIZE             16u
#endif

/** Maximum size of events data in the application scheduler queue aligned to 32 bits - this is
 *  size of the buffers of the SoftDevice handler, which stores events pulled from the SoftDevice.
 */

#if defined(BLE_STACK_SUPPORT_REQD) && defined(ANT_STACK_SUPPORT_REQD)
#define STACK_EVENT_MAX_SIZE    MAX(NRF_SDH_BLE_EVT_BUF_SIZE, NRF_SDH_ANT_EVT_BUF_SIZE)
#elif defined(BLE_STACK_SUPPORT_REQD)
#define STACK_EVENT_MAX_SIZE    NRF_SDH_BLE_EVT_BUF_SIZE
#elif defined(ANT_STACK_SUPPORT_REQD)
#define STACK_EVENT_MAX_SIZE    NRF_SDH_ANT_EVT_BUF_SIZE
#endif


#define SER_CONN_SCHED_MAX_EVENT_DATA_SIZE    ((CEIL_DIV(MAX(STACK_EVENT_MAX_SIZE,              \
                                                             sizeof(uint32_t)),                 \
                                                             sizeof(uint32_t))) *               \
                                                             sizeof(uint32_t))

/** @brief Prototype for function called when there is no free TX buffer and system is blocked */
typedef void (*ser_conn_on_no_mem_t)(void);

/**
 * @brief A function for setting handler which should be called when serialization
 * is blocked waiting for TX buffer.
 *
 * @param handler Handler to be called whenever serialization failed to allocate TX buffer
 *
 */
void ser_conn_on_no_mem_handler_set(ser_conn_on_no_mem_t handler);

/**
 * @brief A function called when TX buffer allocation failed. Serialization is always allocating TX
 * buffer in main context expecting that it will be freed from interrupt context.
 */
void ser_conn_on_no_mem_handler(void);


/**@brief A function for processing the HAL Transport layer events.
 *
 * @param[in] event    HAL Transport layer event.
 */
void ser_conn_hal_transport_event_handle(ser_hal_transport_evt_t event);


/**@brief A function to call the function to process a packet when it is fully received.
 *
 * @retval    NRF_SUCCESS           Operation success.
 * @retval    NRF_ERROR_NULL        Operation failure. NULL pointer supplied.
 * @retval    NRF_ERROR_INTERNAL    Operation failure. Internal error ocurred.
 */
uint32_t ser_conn_rx_process(void);


#ifdef BLE_STACK_SUPPORT_REQD
/**@brief Reset serialization state */
void ser_conn_reset(void);

/**@brief A function for processing BLE SoftDevice events.
 *
 * @details BLE events are put into application scheduler queue to be processed at a later time.
 *
 * @param[in] p_ble_evt    A pointer to a BLE event.
 * @param[in] p_context    A parameter to the handler. Not used.
 */
void ser_conn_ble_event_handle(ble_evt_t const * p_ble_evt, void * p_context);
#endif // BLE_STACK_SUPPORT_REQD

#ifdef ANT_STACK_SUPPORT_REQD
/**@brief A function for processing ANT SoftDevice events.
 *
 * @details ANT events are put into application scheduler queue to be processed at a later time.
 *
 * @param[in] p_ant_evt    A pointer to a BLE event.
 * @param[in] p_context    A parameter to the handler. Not used.
 */
void ser_conn_ant_event_handle(ant_evt_t * p_ant_evt, void * p_context);
#endif // ANT_STACK_SUPPORT_REQD

#ifdef __cplusplus
}
#endif

#endif /* SER_CONN_HANDLERS_H__ */
/** @} */
