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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_COMMON_PAGE_70)

#include <string.h>
#include "ant_common_page_70.h"

#define NRF_LOG_MODULE_NAME ant_common_page_70
#if ANT_COMMON_PAGE_70_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_COMMON_PAGE_70_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_COMMON_PAGE_70_INFO_COLOR
#else // ANT_COMMON_PAGE_70_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_COMMON_PAGE_70_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief ANT+ common page 70 data layout structure. */
typedef struct
{
    uint8_t reserved[2];
    uint8_t descriptor[2];
    uint8_t req_trans_response;
    uint8_t req_page_number;
    uint8_t command_type;
}ant_common_page70_data_layout_t;

/**@brief Function for tracing page 70 data.
 *
 * @param[in]  p_page_data      Pointer to the page 70 data.
 */
static void page70_data_log(volatile ant_common_page70_data_t const * p_page_data)
{
    NRF_LOG_INFO("Page %d request", p_page_data->page_number);

    switch (p_page_data->transmission_response.specyfic)
    {
        case ANT_PAGE70_RESPONSE_TRANSMIT_UNTIL_SUCCESS:
            NRF_LOG_INFO("Try to send until ACK");
            break;

        case ANT_PAGE70_RESPONSE_INVALID:
            NRF_LOG_INFO("Invalid requested transmission response");
            break;

        default:

            if (p_page_data->transmission_response.items.ack_resposne)
            {
                NRF_LOG_INFO("Answer with acknowledged messages");
            }
            NRF_LOG_INFO("Requested number of transmissions: %d",
                       p_page_data->transmission_response.items.transmit_count);
    }

    switch (p_page_data->command_type)
    {
        case ANT_PAGE70_COMMAND_PAGE_DATA_REQUEST:
            NRF_LOG_INFO("Request Data Page");
            break;

        case ANT_PAGE70_COMMAND_ANT_FS_SESSION_REQUEST:
            NRF_LOG_INFO("Request ANT-FS Session");
            break;

        default:
            NRF_LOG_INFO("Invalid request");
    }
    NRF_LOG_INFO("Descriptor %x\r\n\n", p_page_data->descriptor);
}


void ant_common_page_70_encode(uint8_t                                 * p_page_buffer,
                               volatile ant_common_page70_data_t const * p_page_data)
{
    ant_common_page70_data_layout_t * p_outcoming_data =
        (ant_common_page70_data_layout_t *)p_page_buffer;

    memset(p_outcoming_data->reserved, UINT8_MAX, sizeof (p_outcoming_data->reserved));
    UNUSED_PARAMETER(uint16_encode(p_page_data->descriptor, p_outcoming_data->descriptor));
    p_outcoming_data->req_trans_response = p_page_data->transmission_response.byte;
    p_outcoming_data->req_page_number    = p_page_data->page_number;
    p_outcoming_data->command_type       = p_page_data->command_type;

    page70_data_log(p_page_data);
}


void ant_common_page_70_decode(uint8_t const                     * p_page_buffer,
                               volatile ant_common_page70_data_t * p_page_data)
{
    ant_common_page70_data_layout_t const * p_incoming_data =
        (ant_common_page70_data_layout_t *)p_page_buffer;

    p_page_data->descriptor                 = uint16_decode(p_incoming_data->descriptor);
    p_page_data->transmission_response.byte = p_incoming_data->req_trans_response;
    p_page_data->page_number                = p_incoming_data->req_page_number;
    p_page_data->command_type               = (ant_page70_command_t)p_incoming_data->command_type;

    page70_data_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_COMMON_PAGE_70)
