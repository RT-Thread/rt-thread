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
/** @file
 *
 * @defgroup ant_request_controller ANT request controller
 * @{
 * @ingroup ant_sdk_utils
 *
 * @brief   Module for handling page requests related to page 70.
 */

#ifndef ANT_REQUEST_CONTROLLER_H__
#define ANT_REQUEST_CONTROLLER_H__
#include <stdbool.h>
#include "ant_common_page_70.h"
#include "nrf_sdh_ant.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Request controller events types. */
typedef enum
{
    ANT_REQUEST_CONTROLLER_NONE,    ///< No event.
    ANT_REQUEST_CONTROLLER_SUCCESS, ///< Page request successful.
    ANT_REQUEST_CONTROLLER_FAILED,  ///< Page request failed.
} ant_request_controller_evt_t;

/**@brief Request controller states. */
typedef enum
{
    ANT_REQUEST_CONTROLLER_IDLE,                        ///< Module is in idle state.
    ANT_REQUEST_CONTROLLER_SENDED,                      ///< Module waits for acknowledgment of its request.
    ANT_REQUEST_CONTROLLER_BROADCAST_REQUESTED,         ///< Module is requested to send page n times using broadcast.
    ANT_REQUEST_CONTROLLER_ACK_REQUESTED,               ///< Module is requested to send page n times using acknowledgment.
    ANT_REQUEST_CONTROLLER_ACK_UNTIL_SUCCESS_REQUESTED, ///< Module is requested to send page until success using acknowledgment.
} ant_request_controller_state_t;

/**@brief ANT request controller structure. */
typedef struct
{
    ant_request_controller_state_t state;   ///< Actual module state.
    ant_common_page70_data_t       page_70; ///< Page 70.
} ant_request_controller_t;

/**@brief Function for initializing the ANT request controller instance.
 *
 * @param[in]  p_controller     Pointer to the controller instance.
 */
void ant_request_controller_init(ant_request_controller_t * p_controller);

/**@brief Function for sending a request.
 *
 * @param[in]  p_controller     Pointer to the controller instance.
 * @param[in]  channel_number   Channel number.
 * @param[in]  p_page_70        Pointer to the prepared page 70.
 *
 * @return     Error code returned by @ref sd_ant_acknowledge_message_tx().
 */
uint32_t ant_request_controller_request(ant_request_controller_t * p_controller,
                                        uint8_t                    channel_number,
                                        ant_common_page70_data_t * p_page_70);

/**@brief Function for getting pending page number.
 *
 * @details This function checks whether a page number was requested.
 *
 * @param[in]  p_controller     Pointer to the controller instance.
 * @param[out] p_page_number    Pending page number (valid if true was returned).
 *
 * @retval     TRUE             If there was a pending page.
 * @retval     FALSE            If no page was pending.
 */
bool ant_request_controller_pending_get(ant_request_controller_t * p_controller,
                                        uint8_t                  * p_page_number);

/**@brief Function for checking whether the next page must be sent with acknowledgment.
 *
 * @param[in]  p_controller     Pointer to the controller instance.
 *
 * @retval     TRUE             If the next transmission needs acknowledgment.
 * @retval     FALSE            If the next transmission does not need acknowledgment.
 */
bool ant_request_controller_ack_needed(ant_request_controller_t * p_controller);

/**
 * @brief Function for handling ANT events on display side.
 *
 * @details All events from the ANT stack that are related to the appropriate channel number
 *          should be propagated.
 *
 * @param[in]  p_controller         Pointer to the controller instance.
 * @param[in]  p_ant_evt            Event received from the ANT stack.
 */
ant_request_controller_evt_t ant_request_controller_disp_evt_handler(
    ant_request_controller_t * p_controller,
    ant_evt_t                * p_ant_evt);

/**
 * @brief Function for handling ANT events on sensor side.
 *
 * @details All events from the ANT stack that are related to the appropriate channel number
 *          should be propagated.
 *
 * @param[in]  p_controller             Pointer to the controller instance.
 * @param[in]  p_ant_evt                Event received from the ANT stack.
 * @retval     TRUE                     If there was a pending page.
 */
void ant_request_controller_sens_evt_handler(ant_request_controller_t * p_controller,
                                             ant_evt_t                * p_ant_evt);



#ifdef __cplusplus
}
#endif

#endif // ANT_REQUEST_CONTROLLER_H__
/** @} */
