/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(ANT_SDM)

#include "nrf_assert.h"
#include "app_error.h"
#include "ant_interface.h"
#include "ant_sdm.h"
#include "app_error.h"
#include "ant_sdm_utils.h"

#define NRF_LOG_MODULE_NAME "ANT_SDM"
#if ANT_SDM_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_SDM_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_SDM_INFO_COLOR
#else // ANT_SDM_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_SDM_LOG_ENABLED
#include "nrf_log.h"

#define COMMON_DATA_INTERVAL 64          /**< Common data page is sent every 65th message. */

/**@brief SDM message data layout structure. */
typedef struct
{
    ant_sdm_page_t  page_number;
    uint8_t         page_payload[7];
}ant_sdm_message_layout_t;

/**@brief Function for initializing the ANT SDM profile instance.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 * @param[in]  p_channel_config Pointer to the ANT channel configuration structure.
 *
 * @retval     NRF_SUCCESS      Successful initialization.
 *             Error code when initialization failed.
 */
static ret_code_t ant_sdm_init(ant_sdm_profile_t          * p_profile,
                               ant_channel_config_t const * p_channel_config)
{
    p_profile->channel_number = p_channel_config->channel_number;

    p_profile->page_1  = DEFAULT_ANT_SDM_PAGE1();
    p_profile->page_2  = DEFAULT_ANT_SDM_PAGE2();
    p_profile->page_3  = DEFAULT_ANT_SDM_PAGE3();
    p_profile->page_22 = DEFAULT_ANT_SDM_PAGE22();
    p_profile->common  = DEFAULT_ANT_SDM_COMMON_DATA();
    p_profile->page_80 = DEFAULT_ANT_COMMON_page80();
    p_profile->page_81 = DEFAULT_ANT_COMMON_page81();

    NRF_LOG_INFO("ANT SDM channel %u init\r\n", p_profile->channel_number);
    return ant_channel_init(p_channel_config);
}

ret_code_t ant_sdm_disp_init(ant_sdm_profile_t           * p_profile,
                             ant_channel_config_t const  * p_channel_config,
                             ant_sdm_disp_config_t const * p_disp_config)
{
    ASSERT(p_profile != NULL);
    ASSERT(p_channel_config != NULL);
    ASSERT(p_disp_config != NULL);
    ASSERT(p_disp_config->p_cb != NULL);
    ASSERT(p_disp_config->evt_handler != NULL);

    p_profile->evt_handler    = p_disp_config->evt_handler;
    p_profile->_cb.p_disp_cb = p_disp_config->p_cb;
    ant_request_controller_init(&(p_profile->_cb.p_disp_cb->req_controller));

    return ant_sdm_init(p_profile, p_channel_config);
}

ret_code_t ant_sdm_sens_init(ant_sdm_profile_t           * p_profile,
                             ant_channel_config_t const  * p_channel_config,
                             ant_sdm_sens_config_t const * p_sens_config)
{
    ASSERT(p_profile != NULL);
    ASSERT(p_channel_config != NULL);
    ASSERT(p_sens_config != NULL);
    ASSERT(p_sens_config->p_cb != NULL);
    ASSERT(p_sens_config->evt_handler != NULL);
    ASSERT(p_sens_config->supplementary_page_number == ANT_SDM_PAGE_1
        || p_sens_config->supplementary_page_number == ANT_SDM_PAGE_2
        || p_sens_config->supplementary_page_number == ANT_SDM_PAGE_3);

    p_profile->evt_handler    = p_sens_config->evt_handler;
    p_profile->_cb.p_sens_cb = p_sens_config->p_cb;
    ant_request_controller_init(&(p_profile->_cb.p_sens_cb->req_controller));

    p_profile->_cb.p_sens_cb->message_counter    = 0;
    p_profile->_cb.p_sens_cb->supp_page_control  = 0;
    p_profile->_cb.p_sens_cb->supp_page_number   = p_sens_config->supplementary_page_number;
    p_profile->_cb.p_sens_cb->common_page_number = ANT_SDM_PAGE_80;

    return ant_sdm_init(p_profile, p_channel_config);
}

ret_code_t ant_sdm_page_request(ant_sdm_profile_t * p_profile, ant_common_page70_data_t * p_page_70)
{
    ASSERT(p_profile != NULL);
    ASSERT(p_page_70 != NULL);

    uint32_t err_code = ant_request_controller_request(&(p_profile->_cb.p_disp_cb->req_controller),
                                                         p_profile->channel_number, p_page_70);
    NRF_LOG_INFO("\r\n");

    return err_code;
}

/**@brief Function for getting next page number to send.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 *
 * @return     Next page number.
 */
static ant_sdm_page_t next_page_number_get(ant_sdm_profile_t * p_profile)
{
    ant_sdm_sens_cb_t * p_sdm_cb = p_profile->_cb.p_sens_cb;
    ant_sdm_page_t page_number;

    if (ant_request_controller_pending_get(&(p_sdm_cb->req_controller), (uint8_t *)&page_number))
    {
        // No implementation needed
    }
    else if (p_sdm_cb->message_counter == (COMMON_DATA_INTERVAL))
    {
        page_number  = p_sdm_cb->common_page_number;
        p_sdm_cb->message_counter++;
    }
    else if (p_sdm_cb->message_counter == (COMMON_DATA_INTERVAL + 1))
    {
        page_number  = p_sdm_cb->common_page_number;
        p_sdm_cb->common_page_number = (p_sdm_cb->common_page_number == ANT_SDM_PAGE_80)
                                     ? ANT_SDM_PAGE_81 : ANT_SDM_PAGE_80;
        p_sdm_cb->message_counter = 0;
    }
    else
    {
        if (p_sdm_cb->supp_page_control)
        {
            page_number = p_sdm_cb->supp_page_number;
        }
        else
        {
            page_number = ANT_SDM_PAGE_1;
        }

        if ((p_sdm_cb->message_counter % 2) == 1)
        {
            p_sdm_cb->supp_page_control = !p_sdm_cb->supp_page_control;
        }
        p_sdm_cb->message_counter++;
    }
    return page_number;
}

/**@brief Function for encoding SDM message.
 *
 * @param[in]  p_profile         Pointer to the profile instance.
 * @param[in]  p_message_payload Pointer to the message payload.
 *
 * @note Assume to be call each time when Tx window will occur.
 */
static void sens_message_encode(ant_sdm_profile_t * p_profile, uint8_t * p_message_payload)
{
    ant_sdm_message_layout_t * p_sdm_message_payload = (ant_sdm_message_layout_t *)p_message_payload;

    p_sdm_message_payload->page_number = next_page_number_get(p_profile);

    NRF_LOG_INFO("SDM Page number: %u\r\n", p_sdm_message_payload->page_number);

    switch (p_sdm_message_payload->page_number)
    {
        case ANT_SDM_PAGE_1:
            ant_sdm_page_1_encode(p_sdm_message_payload->page_payload, &(p_profile->page_1),
                                  &(p_profile->common));
            ant_sdm_speed_encode(p_sdm_message_payload->page_payload, &(p_profile->common));
            break;

        case ANT_SDM_PAGE_2:
            ant_sdm_page_2_encode(p_sdm_message_payload->page_payload, &(p_profile->page_2));
            ant_sdm_speed_encode(p_sdm_message_payload->page_payload, &(p_profile->common));
            break;

        case ANT_SDM_PAGE_3:
            ant_sdm_page_2_encode(p_sdm_message_payload->page_payload, &(p_profile->page_2));
            ant_sdm_page_3_encode(p_sdm_message_payload->page_payload, &(p_profile->page_3));
            ant_sdm_speed_encode(p_sdm_message_payload->page_payload, &(p_profile->common));
            break;

        case ANT_SDM_PAGE_16:
            ant_sdm_page_16_encode(p_sdm_message_payload->page_payload, &(p_profile->common));
            break;

        case ANT_SDM_PAGE_22:
            ant_sdm_page_22_encode(p_sdm_message_payload->page_payload, &(p_profile->page_22));
            break;

        case ANT_SDM_PAGE_80:
            ant_common_page_80_encode(p_sdm_message_payload->page_payload, &(p_profile->page_80));
            break;

        case ANT_SDM_PAGE_81:
            ant_common_page_81_encode(p_sdm_message_payload->page_payload, &(p_profile->page_81));
            break;

        default:
            return;
    }

    p_profile->evt_handler(p_profile, (ant_sdm_evt_t)p_sdm_message_payload->page_number);
}

void ant_sdm_sens_evt_handler(ant_sdm_profile_t * p_profile, ant_evt_t * p_ant_event)
{
    ASSERT(p_profile != NULL);
    ASSERT(p_ant_event != NULL);

    if (p_ant_event->channel == p_profile->channel_number)
    {
        uint32_t err_code;
        uint8_t p_message_payload[ANT_STANDARD_DATA_PAYLOAD_SIZE];
        ant_sdm_sens_cb_t * p_sdm_cb   = p_profile->_cb.p_sens_cb;
        ant_request_controller_sens_evt_handler(&(p_sdm_cb->req_controller), p_ant_event);

        switch (p_ant_event->event)
        {
            case EVENT_TX:
            case EVENT_TRANSFER_TX_FAILED:
            case EVENT_TRANSFER_TX_COMPLETED:
                sens_message_encode(p_profile, p_message_payload);
                if (ant_request_controller_ack_needed(&(p_sdm_cb->req_controller)))
                {
                    err_code = sd_ant_acknowledge_message_tx(p_profile->channel_number, sizeof(p_message_payload), p_message_payload);
                }
                else
                {
                    err_code = sd_ant_broadcast_message_tx(p_profile->channel_number, sizeof(p_message_payload), p_message_payload);
                }
                APP_ERROR_CHECK(err_code);
                break;
            default:
                break;
        }
    }
}

ret_code_t ant_sdm_disp_open(ant_sdm_profile_t * p_profile)
{
    ASSERT(p_profile != NULL);

    NRF_LOG_INFO("ANT SDM channel %u open\r\n", p_profile->channel_number);
    return sd_ant_channel_open(p_profile->channel_number);
}

ret_code_t ant_sdm_sens_open(ant_sdm_profile_t * p_profile)
{
    ASSERT(p_profile != NULL);

    // Fill tx buffer for the first frame
    uint32_t err_code;
    uint8_t  p_message_payload[ANT_STANDARD_DATA_PAYLOAD_SIZE];

    sens_message_encode(p_profile, p_message_payload);
    err_code =
        sd_ant_broadcast_message_tx(p_profile->channel_number,
                                    sizeof (p_message_payload),
                                    p_message_payload);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_INFO("ANT SDM channel %u open\r\n", p_profile->channel_number);
    return sd_ant_channel_open(p_profile->channel_number);
}


/**@brief Function for decoding SDM message.
 *
 * @note Assume to be call each time when Rx window will occur.
 */
static void disp_message_decode(ant_sdm_profile_t * p_profile, uint8_t * p_message_payload)
{
    const ant_sdm_message_layout_t * p_sdm_message_payload  = (ant_sdm_message_layout_t *)p_message_payload;

    NRF_LOG_INFO("SDM Page number: %u\r\n", p_sdm_message_payload->page_number);

    switch (p_sdm_message_payload->page_number)
    {
        case ANT_SDM_PAGE_1:
            ant_sdm_page_1_decode(p_sdm_message_payload->page_payload, &(p_profile->page_1), &(p_profile->common));
            ant_sdm_speed_decode(p_sdm_message_payload->page_payload, &(p_profile->common));
            break;

        case ANT_SDM_PAGE_3:
            ant_sdm_page_3_decode(p_sdm_message_payload->page_payload, &(p_profile->page_3));
            /* fall through */
        case ANT_SDM_PAGE_2:
            ant_sdm_page_2_decode(p_sdm_message_payload->page_payload, &(p_profile->page_2));
            ant_sdm_speed_decode(p_sdm_message_payload->page_payload, &(p_profile->common));
            break;

        case ANT_SDM_PAGE_16:
            ant_sdm_page_16_decode(p_sdm_message_payload->page_payload, &(p_profile->common));
            break;

        case ANT_SDM_PAGE_22:
            ant_sdm_page_22_decode(p_sdm_message_payload->page_payload, &(p_profile->page_22));
            break;

        case ANT_SDM_PAGE_80:
            ant_common_page_80_decode(p_sdm_message_payload->page_payload, &(p_profile->page_80));
            break;

        case ANT_SDM_PAGE_81:
            ant_common_page_81_decode(p_sdm_message_payload->page_payload, &(p_profile->page_81));
            break;

        default:
            return;
    }

    p_profile->evt_handler(p_profile, (ant_sdm_evt_t)p_sdm_message_payload->page_number);
}

void ant_sdm_disp_evt_handler(ant_sdm_profile_t * p_profile, ant_evt_t * p_ant_event)
{
    ASSERT(p_profile != NULL);
    ASSERT(p_ant_event != NULL);

    if (p_ant_event->channel == p_profile->channel_number)
    {
        ANT_MESSAGE       * p_message = (ANT_MESSAGE *)p_ant_event->msg.evt_buffer;
        ant_sdm_disp_cb_t * p_sdm_cb  = p_profile->_cb.p_disp_cb;

        switch (ant_request_controller_disp_evt_handler(&(p_sdm_cb->req_controller), p_ant_event))
        {
            case ANT_REQUEST_CONTROLLER_SUCCESS:
                p_profile->evt_handler(p_profile, ANT_SDM_PAGE_REQUEST_SUCCESS);
                break;
            case ANT_REQUEST_CONTROLLER_FAILED:
                p_profile->evt_handler(p_profile, ANT_SDM_PAGE_REQUEST_FAILED);
                break;
            default:
                break;
        }

        switch (p_ant_event->event)
        {
            case EVENT_RX:
                if (p_message->ANT_MESSAGE_ucMesgID == MESG_BROADCAST_DATA_ID
                 || p_message->ANT_MESSAGE_ucMesgID == MESG_ACKNOWLEDGED_DATA_ID
                 || p_message->ANT_MESSAGE_ucMesgID == MESG_BURST_DATA_ID)
                {
                    disp_message_decode(p_profile, p_message->ANT_MESSAGE_aucPayload);
                }
                break;
            default:
                break;
        }
    }
}

#endif // NRF_MODULE_ENABLED(ANT_SDM)
