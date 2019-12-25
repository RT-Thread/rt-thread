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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_REQUEST_CONTROLLER)
#include "ant_request_controller.h"
#include "ant_interface.h"
#include "ant_parameters.h"
#include "app_error.h"
#include "nrf_assert.h"
#include "nrf.h"

/**@brief Common message data layout structure. */
typedef struct
{
    uint8_t page_number;     ///< Page number.
    uint8_t page_payload[7]; ///< Page payload.
}ant_common_message_layout_t;


void ant_request_controller_init(ant_request_controller_t * p_controller)
{
    ASSERT(p_controller != NULL);

    p_controller->state   = ANT_REQUEST_CONTROLLER_IDLE;
    p_controller->page_70 = DEFAULT_ANT_COMMON_PAGE70();
}


uint32_t ant_request_controller_request(ant_request_controller_t * p_controller,
                                        uint8_t                    channel_number,
                                        ant_common_page70_data_t * p_page_70)
{
    ASSERT(p_controller != NULL);
    ASSERT(p_page_70 != NULL);

    ant_common_message_layout_t message;
    message.page_number = ANT_COMMON_PAGE_70;

    ant_common_page_70_encode(message.page_payload, p_page_70);

    p_controller->state = ANT_REQUEST_CONTROLLER_SENDED;

    return sd_ant_acknowledge_message_tx(channel_number, sizeof (message), (uint8_t *)&message);
}


bool ant_request_controller_pending_get(ant_request_controller_t * p_controller,
                                        uint8_t                  * p_page_number)
{
    ASSERT(p_controller != NULL);
    ASSERT(p_page_number != NULL);

    if ((p_controller->state == ANT_REQUEST_CONTROLLER_ACK_UNTIL_SUCCESS_REQUESTED)
        || (p_controller->state == ANT_REQUEST_CONTROLLER_ACK_REQUESTED)
        || (p_controller->state == ANT_REQUEST_CONTROLLER_BROADCAST_REQUESTED))
    {
        *p_page_number = p_controller->page_70.page_number;
        return true;
    }
    return false;
}


bool ant_request_controller_ack_needed(ant_request_controller_t * p_controller)
{
    ASSERT(p_controller != NULL);
    return ((p_controller->state == ANT_REQUEST_CONTROLLER_ACK_UNTIL_SUCCESS_REQUESTED)
            || (p_controller->state == ANT_REQUEST_CONTROLLER_ACK_REQUESTED));
}


ant_request_controller_evt_t ant_request_controller_disp_evt_handler(
    ant_request_controller_t * p_controller,
    ant_evt_t                * p_ant_evt)
{
    ASSERT(p_controller != NULL);
    ASSERT(p_ant_evt != NULL);

    if ( p_controller->state == ANT_REQUEST_CONTROLLER_SENDED)
    {
        switch (p_ant_evt->event)
        {
            case EVENT_TRANSFER_TX_FAILED:
                p_controller->state = ANT_REQUEST_CONTROLLER_IDLE;
                return ANT_REQUEST_CONTROLLER_FAILED;

            case EVENT_TRANSFER_TX_COMPLETED:
                p_controller->state = ANT_REQUEST_CONTROLLER_IDLE;
                return ANT_REQUEST_CONTROLLER_SUCCESS;

            default:
                break;
        }
    }

    return ANT_REQUEST_CONTROLLER_NONE;
}


/**@brief Function for confirmation of page sending.
 *
 * @param[in]  p_controller     Pointer to the controller instance.
 */
__STATIC_INLINE void page_sended(ant_request_controller_t * p_controller)
{
    if (!((p_controller->page_70.transmission_response.items.transmit_count)--))
    {
        p_controller->state = ANT_REQUEST_CONTROLLER_IDLE;
    }
}


/**@brief Function for handling page request.
 *
 * @param[in]  p_controller      Pointer to the controller instance.
 * @param[in]  p_message_payload Pointer to the message payload.
 */
__STATIC_INLINE void page_requested(ant_request_controller_t    * p_controller,
                                    ant_common_message_layout_t * p_message_payload)
{
    ant_common_page_70_decode(p_message_payload->page_payload, &(p_controller->page_70));

    if ((p_controller->page_70.command_type == ANT_PAGE70_COMMAND_PAGE_DATA_REQUEST)
        && (p_controller->page_70.transmission_response.specyfic != ANT_PAGE70_RESPONSE_INVALID))
    {
        if (p_controller->page_70.transmission_response.items.ack_resposne)
        {
            if (p_controller->page_70.transmission_response.specyfic ==
                ANT_PAGE70_RESPONSE_TRANSMIT_UNTIL_SUCCESS)
            {
                p_controller->state = ANT_REQUEST_CONTROLLER_ACK_UNTIL_SUCCESS_REQUESTED;
            }
            else
            {
                p_controller->state = ANT_REQUEST_CONTROLLER_ACK_REQUESTED;
            }
        }
        else
        {
            p_controller->state = ANT_REQUEST_CONTROLLER_BROADCAST_REQUESTED;
        }
    }
}


void ant_request_controller_sens_evt_handler(ant_request_controller_t * p_controller,
                                             ant_evt_t                * p_ant_evt)
{
    ASSERT(p_controller != NULL);
    ASSERT(p_ant_evt != NULL);

    ant_common_message_layout_t * p_message_payload =
        (ant_common_message_layout_t *)p_ant_evt->message.ANT_MESSAGE_aucPayload;

    switch (p_ant_evt->event)
    {
        case EVENT_RX:

            if (p_message_payload->page_number == ANT_COMMON_PAGE_70)
            {
                page_requested(p_controller, p_message_payload);
            }
            break;

        case EVENT_TRANSFER_TX_COMPLETED:

            if (p_controller->state == ANT_REQUEST_CONTROLLER_ACK_UNTIL_SUCCESS_REQUESTED)
            {
                p_controller->state = ANT_REQUEST_CONTROLLER_IDLE;
            }
            /* fall through */

        case EVENT_TX:

            if (p_controller->state == ANT_REQUEST_CONTROLLER_BROADCAST_REQUESTED
                || p_controller->state == ANT_REQUEST_CONTROLLER_ACK_REQUESTED)
            {
                page_sended(p_controller);
            }
            break;

        default:
            break;
    }
}

#endif // NRF_MODULE_ENABLED(ANT_REQUEST_CONTROLLER)
