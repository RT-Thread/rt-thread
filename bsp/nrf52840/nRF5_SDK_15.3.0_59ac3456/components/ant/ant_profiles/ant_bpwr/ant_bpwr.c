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
#if NRF_MODULE_ENABLED(ANT_BPWR)

#include "nrf_assert.h"
#include "app_error.h"
#include "ant_interface.h"
#include "ant_bpwr.h"

#define NRF_LOG_MODULE_NAME ant_bpwr
#if ANT_BPWR_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_BPWR_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_BPWR_INFO_COLOR
#else // ANT_BPWR_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_BPWR_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define BPWR_CALIB_INT_TIMEOUT ((ANT_CLOCK_FREQUENCY * BPWR_CALIBRATION_TIMOUT_S) / BPWR_MSG_PERIOD) // calibration timeout in ant message period's unit

// for torque sensor Minimum: Interleave every 9th message
#define BPWR_PAGE_16_INTERVAL      5   // Preferred: Interleave every 5th message
#define BPWR_PAGE_16_INTERVAL_OFS  2   // Permissible offset
#define COMMON_PAGE_80_INTERVAL    119 // Minimum: Interleave every 121 messages
#define COMMON_PAGE_81_INTERVAL    120 // Minimum: Interleave every 121 messages
#define AUTO_ZERO_SUPPORT_INTERVAL 120 // Minimum: Interleave every 121 messages

/**@brief Bicycle power message data layout structure. */
typedef struct
{
    uint8_t page_number;
    uint8_t page_payload[7];
} ant_bpwr_message_layout_t;


/**@brief Function for initializing the ANT Bicycle Power Profile instance.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 * @param[in]  p_channel_config Pointer to the ANT channel configuration structure.
 *
 * @retval     NRF_SUCCESS      If initialization was successful. Otherwise, an error code is returned.
 */
static ret_code_t ant_bpwr_init(ant_bpwr_profile_t         * p_profile,
                                ant_channel_config_t const * p_channel_config)
{
    p_profile->channel_number = p_channel_config->channel_number;

    p_profile->page_1  = DEFAULT_ANT_BPWR_PAGE1();
    p_profile->page_16 = DEFAULT_ANT_BPWR_PAGE16();
    p_profile->page_17 = DEFAULT_ANT_BPWR_PAGE17();
    p_profile->page_18 = DEFAULT_ANT_BPWR_PAGE18();
    p_profile->page_80 = DEFAULT_ANT_COMMON_page80();
    p_profile->page_81 = DEFAULT_ANT_COMMON_page81();

    NRF_LOG_INFO("ANT B-PWR channel %u init", p_profile->channel_number);
    return ant_channel_init(p_channel_config);
}


ret_code_t ant_bpwr_disp_init(ant_bpwr_profile_t           * p_profile,
                              ant_channel_config_t const   * p_channel_config,
                              ant_bpwr_disp_config_t const * p_disp_config)
{
    ASSERT(p_profile != NULL);
    ASSERT(p_channel_config != NULL);
    ASSERT(p_disp_config != NULL);
    ASSERT(p_disp_config->evt_handler != NULL);
    ASSERT(p_disp_config->p_cb != NULL);

    p_profile->evt_handler   = p_disp_config->evt_handler;
    p_profile->_cb.p_disp_cb = p_disp_config->p_cb;

    p_profile->_cb.p_disp_cb ->calib_timeout = 0;
    p_profile->_cb.p_disp_cb ->calib_stat    = BPWR_DISP_CALIB_NONE;

    return ant_bpwr_init(p_profile, p_channel_config);
}


ret_code_t ant_bpwr_sens_init(ant_bpwr_profile_t           * p_profile,
                              ant_channel_config_t const   * p_channel_config,
                              ant_bpwr_sens_config_t const * p_sens_config)
{
    ASSERT(p_profile != NULL);
    ASSERT(p_channel_config != NULL);
    ASSERT(p_sens_config != NULL);
    ASSERT(p_sens_config->p_cb != NULL);
    ASSERT(p_sens_config->evt_handler != NULL);
    ASSERT(p_sens_config->calib_handler != NULL);

    p_profile->evt_handler   = p_sens_config->evt_handler;
    p_profile->_cb.p_sens_cb = p_sens_config->p_cb;

    p_profile->_cb.p_sens_cb->torque_use      = p_sens_config->torque_use;
    p_profile->_cb.p_sens_cb->calib_handler   = p_sens_config->calib_handler;
    p_profile->_cb.p_sens_cb->calib_stat      = BPWR_SENS_CALIB_NONE;
    p_profile->_cb.p_sens_cb->message_counter = 0;

    return ant_bpwr_init(p_profile, p_channel_config);
}



/**@brief Function for getting next page number to send.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 *
 * @return     Next page number.
 */
static ant_bpwr_page_t next_page_number_get(ant_bpwr_profile_t * p_profile)
{
    ant_bpwr_sens_cb_t * p_bpwr_cb = p_profile->_cb.p_sens_cb;
    ant_bpwr_page_t      page_number;

    if (p_bpwr_cb->calib_stat == BPWR_SENS_CALIB_READY)
    {
        page_number           = ANT_BPWR_PAGE_1;
        p_bpwr_cb->calib_stat = BPWR_SENS_CALIB_NONE; // mark event as processed
    }
    else if ((p_profile->BPWR_PROFILE_auto_zero_status != ANT_BPWR_AUTO_ZERO_NOT_SUPPORTED)
             && (p_bpwr_cb->message_counter == AUTO_ZERO_SUPPORT_INTERVAL))
    {
        page_number                            = ANT_BPWR_PAGE_1;
        p_profile->BPWR_PROFILE_calibration_id = ANT_BPWR_CALIB_ID_AUTO_SUPPORT;
        p_bpwr_cb->message_counter++;
    }
    else if (p_bpwr_cb->message_counter >= COMMON_PAGE_81_INTERVAL)
    {
        page_number                = ANT_BPWR_PAGE_81;
        p_bpwr_cb->message_counter = 0;
    }
    else
    {
        if (p_bpwr_cb->message_counter == COMMON_PAGE_80_INTERVAL)
        {
            page_number = ANT_BPWR_PAGE_80;
        }
        else
        {
            if ( p_bpwr_cb->torque_use == TORQUE_NONE)
            {
                page_number = ANT_BPWR_PAGE_16;
            }
            else if ((p_bpwr_cb->message_counter % BPWR_PAGE_16_INTERVAL)
                     == BPWR_PAGE_16_INTERVAL_OFS)
            {
                page_number = ANT_BPWR_PAGE_16;
            }
            else if ( p_bpwr_cb->torque_use == TORQUE_WHEEL)
            {
                page_number = ANT_BPWR_PAGE_17;
            }
            else // assumed TORQUE_CRANK
            {
                page_number = ANT_BPWR_PAGE_18;
            }
        }
        p_bpwr_cb->message_counter++;
    }

    return page_number;
}


/**@brief Function for encoding Bicycle Power Sensor message.
 *
 * @note Assume to be call each time when Tx window will occur.
 */
static void sens_message_encode(ant_bpwr_profile_t * p_profile, uint8_t * p_message_payload)
{
    ant_bpwr_message_layout_t * p_bpwr_message_payload =
        (ant_bpwr_message_layout_t *)p_message_payload;

    p_bpwr_message_payload->page_number = next_page_number_get(p_profile);

    NRF_LOG_INFO("B-PWR tx page: %u", p_bpwr_message_payload->page_number);

    switch (p_bpwr_message_payload->page_number)
    {
        case ANT_BPWR_PAGE_1:
            ant_bpwr_page_1_encode(p_bpwr_message_payload->page_payload, &(p_profile->page_1));
            break;

        case ANT_BPWR_PAGE_16:
            ant_bpwr_page_16_encode(p_bpwr_message_payload->page_payload, &(p_profile->page_16));
            ant_bpwr_cadence_encode(p_bpwr_message_payload->page_payload, &(p_profile->common));
            break;

        case ANT_BPWR_PAGE_17:
            ant_bpwr_page_17_encode(p_bpwr_message_payload->page_payload, &(p_profile->page_17));
            ant_bpwr_cadence_encode(p_bpwr_message_payload->page_payload, &(p_profile->common));
            break;

        case ANT_BPWR_PAGE_18:
            ant_bpwr_page_18_encode(p_bpwr_message_payload->page_payload, &(p_profile->page_18));
            ant_bpwr_cadence_encode(p_bpwr_message_payload->page_payload, &(p_profile->common));
            break;

        case ANT_COMMON_PAGE_80:
            ant_common_page_80_encode(p_bpwr_message_payload->page_payload, &(p_profile->page_80));
            break;

        case ANT_COMMON_PAGE_81:
            ant_common_page_81_encode(p_bpwr_message_payload->page_payload, &(p_profile->page_81));
            break;

        default:
            return;
    }

    p_profile->evt_handler(p_profile, (ant_bpwr_evt_t)p_bpwr_message_payload->page_number);

}


/**@brief Function for decoding messages received by Bicycle Power sensor message.
 *
 * @note Assume to be call each time when Rx window will occur.
 */
static void sens_message_decode(ant_bpwr_profile_t * p_profile, uint8_t * p_message_payload)
{
    const ant_bpwr_message_layout_t * p_bpwr_message_payload =
        (ant_bpwr_message_layout_t *)p_message_payload;
    ant_bpwr_page1_data_t page1;

    switch (p_bpwr_message_payload->page_number)
    {
        case ANT_BPWR_PAGE_1:
            ant_bpwr_page_1_decode(p_bpwr_message_payload->page_payload, &page1);
            p_profile->_cb.p_sens_cb->calib_stat = BPWR_SENS_CALIB_REQUESTED;
            p_profile->_cb.p_sens_cb->calib_handler(p_profile, &page1);
            break;

        default:
            break;
    }
}


/**@brief Function for decoding messages received by Bicycle Power display message.
 *
 * @note Assume to be call each time when Rx window will occur.
 */
static void disp_message_decode(ant_bpwr_profile_t * p_profile, uint8_t * p_message_payload)
{
    const ant_bpwr_message_layout_t * p_bpwr_message_payload =
        (ant_bpwr_message_layout_t *)p_message_payload;

    NRF_LOG_INFO("B-PWR rx page: %u", p_bpwr_message_payload->page_number);

    switch (p_bpwr_message_payload->page_number)
    {
        case ANT_BPWR_PAGE_1:
            ant_bpwr_page_1_decode(p_bpwr_message_payload->page_payload, &(p_profile->page_1));
            p_profile->_cb.p_disp_cb->calib_stat = BPWR_DISP_CALIB_NONE;
            break;

        case ANT_BPWR_PAGE_16:
            ant_bpwr_page_16_decode(p_bpwr_message_payload->page_payload, &(p_profile->page_16));
            ant_bpwr_cadence_decode(p_bpwr_message_payload->page_payload, &(p_profile->common));
            break;

        case ANT_BPWR_PAGE_17:
            ant_bpwr_page_17_decode(p_bpwr_message_payload->page_payload, &(p_profile->page_17));
            ant_bpwr_cadence_decode(p_bpwr_message_payload->page_payload, &(p_profile->common));
            break;

        case ANT_BPWR_PAGE_18:
            ant_bpwr_page_18_decode(p_bpwr_message_payload->page_payload, &(p_profile->page_18));
            ant_bpwr_cadence_decode(p_bpwr_message_payload->page_payload, &(p_profile->common));
            break;

        case ANT_COMMON_PAGE_80:
            ant_common_page_80_decode(p_bpwr_message_payload->page_payload, &(p_profile->page_80));
            break;

        case ANT_COMMON_PAGE_81:
            ant_common_page_81_decode(p_bpwr_message_payload->page_payload, &(p_profile->page_81));
            break;

        default:
            return;
    }

    p_profile->evt_handler(p_profile, (ant_bpwr_evt_t)p_bpwr_message_payload->page_number);
}


ret_code_t ant_bpwr_calib_request(ant_bpwr_profile_t * p_profile, ant_bpwr_page1_data_t * p_page_1)
{
    ant_bpwr_message_layout_t bpwr_message_payload;

    if (p_profile->_cb.p_disp_cb->calib_stat == BPWR_DISP_CALIB_REQUESTED)
    {
        return NRF_SUCCESS; // calibration in progress, so omit this request
    }

    bpwr_message_payload.page_number = ANT_BPWR_PAGE_1;
    ant_bpwr_page_1_encode(bpwr_message_payload.page_payload, p_page_1);

    uint32_t err_code = sd_ant_acknowledge_message_tx(p_profile->channel_number,
                                                      sizeof (bpwr_message_payload),
                                                      (uint8_t *) &bpwr_message_payload);

    if (err_code == NRF_SUCCESS)
    {
        p_profile->_cb.p_disp_cb->calib_timeout = BPWR_CALIB_INT_TIMEOUT; // initialize watch on calibration's time-out
        p_profile->_cb.p_disp_cb->calib_stat    = BPWR_DISP_CALIB_REQUESTED;
        NRF_LOG_INFO("Start calibration process");
    }
    return err_code;
}


void ant_bpwr_calib_response(ant_bpwr_profile_t * p_profile)
{
    if (p_profile->_cb.p_sens_cb->calib_stat != BPWR_SENS_CALIB_READY) // abort if callback request is in progress
    {
        p_profile->_cb.p_sens_cb->calib_stat = BPWR_SENS_CALIB_READY; // calibration respond
    }
}


/**@brief Function for hangling calibration events.
 */
static void service_calib(ant_bpwr_profile_t * p_profile, uint8_t event)
{
    ant_bpwr_evt_t       bpwr_event;

    if (p_profile->_cb.p_disp_cb->calib_stat == BPWR_DISP_CALIB_REQUESTED)
    {
        switch (event)
        {
            case EVENT_RX:
            /* fall through */
            case EVENT_RX_FAIL:

                if (p_profile->_cb.p_disp_cb->calib_timeout-- == 0)
                {
                    bpwr_event = ANT_BPWR_CALIB_TIMEOUT;
                    break;
                }
                else
                {
                    return;
                }

            case EVENT_TRANSFER_TX_FAILED:
                bpwr_event = ANT_BPWR_CALIB_REQUEST_TX_FAILED;
                break;

            case EVENT_RX_SEARCH_TIMEOUT:
                bpwr_event = ANT_BPWR_CALIB_TIMEOUT;
                break;

            default:
                return;
        }

        NRF_LOG_INFO("End calibration process");
        p_profile->_cb.p_disp_cb->calib_stat = BPWR_DISP_CALIB_NONE;

        p_profile->evt_handler(p_profile, bpwr_event);
    }
}


static void ant_message_send(ant_bpwr_profile_t * p_profile)
{
    uint32_t err_code;
    uint8_t  p_message_payload[ANT_STANDARD_DATA_PAYLOAD_SIZE];

    sens_message_encode(p_profile, p_message_payload);
    err_code =
        sd_ant_broadcast_message_tx(p_profile->channel_number,
                                    sizeof (p_message_payload),
                                    p_message_payload);
    APP_ERROR_CHECK(err_code);
}


ret_code_t ant_bpwr_disp_open(ant_bpwr_profile_t * p_profile)
{
    NRF_LOG_INFO("ANT B-PWR %u open", p_profile->channel_number);
    return sd_ant_channel_open(p_profile->channel_number);
}


ret_code_t ant_bpwr_sens_open(ant_bpwr_profile_t * p_profile)
{
    // Fill tx buffer for the first frame
    ant_message_send(p_profile);

    NRF_LOG_INFO("ANT B-PWR %u open", p_profile->channel_number);
    return sd_ant_channel_open(p_profile->channel_number);
}


void ant_bpwr_sens_evt_handler(ant_evt_t * p_ant_event, void * p_context)
{
    ant_bpwr_profile_t * p_profile = ( ant_bpwr_profile_t *)p_context;

    if (p_ant_event->channel == p_profile->channel_number)
    {
        switch (p_ant_event->event)
        {
            case EVENT_TX:
                ant_message_send(p_profile);
                break;

            case EVENT_RX:
                if (p_ant_event->message.ANT_MESSAGE_ucMesgID == MESG_ACKNOWLEDGED_DATA_ID)
                {
                    sens_message_decode(p_profile, p_ant_event->message.ANT_MESSAGE_aucPayload);
                }
                break;

            default:
                // No implementation needed
                break;
        }
    }
}


void ant_bpwr_disp_evt_handler(ant_evt_t * p_ant_event, void * p_context)
{
    ant_bpwr_profile_t * p_profile = ( ant_bpwr_profile_t *)p_context;

    if (p_ant_event->channel == p_profile->channel_number)
    {
        switch (p_ant_event->event)
        {
            case EVENT_RX:

                if (p_ant_event->message.ANT_MESSAGE_ucMesgID == MESG_BROADCAST_DATA_ID
                 || p_ant_event->message.ANT_MESSAGE_ucMesgID == MESG_ACKNOWLEDGED_DATA_ID
                 || p_ant_event->message.ANT_MESSAGE_ucMesgID == MESG_BURST_DATA_ID)
                {
                    disp_message_decode(p_profile, p_ant_event->message.ANT_MESSAGE_aucPayload);
                }
                break;

            default:
                break;
        }
        service_calib(p_profile, p_ant_event->event);
    }
}

#endif // NRF_MODULE_ENABLED(ANT_BPWR)
