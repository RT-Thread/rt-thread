/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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

#include "nrf_serial_dfu.h"

#include <string.h>
#include "boards.h"
#include "app_util_platform.h"
#include "nrf_dfu_transport.h"
#include "nrf_dfu_req_handler.h"
#include "slip.h"
#include "nrf_log.h"


#define AVAILABLE_LED_PIN_NO            BSP_LED_0                                               /**< Is on when serial DFU transport is enabled (but not connected). */
#define CONNECTED_LED_PIN_NO            BSP_LED_1                                               /**< Is on when device has connected. */


#define CREATE_OBJECT_REQUEST_LEN       (sizeof(uint8_t)+sizeof(uint32_t))
#define SET_RECEIPT_NOTIF_REQUEST_LEN   (sizeof(uint16_t))
#define CALCULATE_CRC_REQUEST_LEN       0
#define EXECUTE_OBJECT_REQUEST_LEN      0
#define SELECT_OBJECT_REQUEST_LEN       (sizeof(uint8_t))
#define GET_SERIAL_MTU_REQUEST_LEN      0

#define MAX_RESPONSE_SIZE               (1+1+3*4)

static serial_dfu_t m_dfu;


//lint -save -e545 -esym(526, dfu_trans) -esym(528, dfu_trans)
DFU_TRANSPORT_REGISTER(nrf_dfu_transport_t const dfu_trans) =
{
    .init_func =        serial_dfu_transport_init,
    .close_func =       serial_dfu_transport_close
};
//lint -restore


ANON_UNIONS_ENABLE

typedef struct
{
    uint8_t            op_code;
    nrf_dfu_res_code_t resp_val;
    union
    {
        struct
        {
            uint32_t offset;
            uint32_t crc;
        } crc_response;

        struct
        {
            uint32_t max_size;
            uint32_t offset;
            uint32_t crc;
        } select_response;

        struct
        {
            uint16_t mtu;
        } serial_mtu_response;
    };

} serial_dfu_response_t;

ANON_UNIONS_DISABLE


/**@brief       Function for the LEDs initialization.
 *
 * @details     Initializes all LEDs used by this application.
 */
static void leds_init(void)
{
    nrf_gpio_cfg_output(AVAILABLE_LED_PIN_NO);
    nrf_gpio_cfg_output(CONNECTED_LED_PIN_NO);
    nrf_gpio_pin_clear(AVAILABLE_LED_PIN_NO);
    nrf_gpio_pin_set(CONNECTED_LED_PIN_NO);
}

static void response_send(serial_dfu_t          * p_dfu,
                          serial_dfu_response_t * p_response)
{
    uint8_t response_buffer[MAX_RESPONSE_SIZE];
    uint8_t encoded_response[MAX_RESPONSE_SIZE*2 + 1];
    uint32_t encoded_response_length;

    uint16_t index = 0;

    NRF_LOG_DEBUG("Sending Response: [0x%01x, 0x%01x]\r\n", p_response->op_code, p_response->resp_val);

    response_buffer[index++] = SERIAL_DFU_OP_CODE_RESPONSE;

    // Encode the Request Op code
    response_buffer[index++] = p_response->op_code;

    // Encode the Response Value.
    response_buffer[index++] = (uint8_t)p_response->resp_val;

    if (p_response->resp_val == NRF_DFU_RES_CODE_SUCCESS)
    {
        switch (p_response->op_code)
        {
            case SERIAL_DFU_OP_CODE_CALCULATE_CRC:
                index += uint32_encode(p_response->crc_response.offset, &response_buffer[index]);
                index += uint32_encode(p_response->crc_response.crc, &response_buffer[index]);
                break;

            case SERIAL_DFU_OP_CODE_SELECT_OBJECT:
                index += uint32_encode(p_response->select_response.max_size, &response_buffer[index]);
                index += uint32_encode(p_response->select_response.offset, &response_buffer[index]);
                index += uint32_encode(p_response->select_response.crc, &response_buffer[index]);
                break;

            case SERIAL_DFU_OP_CODE_GET_SERIAL_MTU:
                index += uint16_encode(p_response->serial_mtu_response.mtu, &response_buffer[index]);
                break;

            default:
                // no implementation
                break;
        }
    }

    // encode into slip
    (void)slip_encode(encoded_response, response_buffer, index, &encoded_response_length);

    // send
    (void)nrf_drv_uart_tx(&p_dfu->uart_instance, encoded_response, encoded_response_length);
}

static void on_packet_received(serial_dfu_t * p_dfu)
{
    nrf_dfu_req_t       dfu_req;
    nrf_dfu_res_t       dfu_res = {{{0}}};

    serial_dfu_response_t serial_response;

    memset(&dfu_req, 0, sizeof(nrf_dfu_req_t));

    const serial_dfu_op_code_t op_code             = (serial_dfu_op_code_t)p_dfu->recv_buffer[0];
    const uint16_t             packet_payload_len  = p_dfu->slip.current_index - 1;
    uint8_t * p_payload                            = &p_dfu->recv_buffer[1];

    serial_response.op_code = op_code;

    nrf_gpio_pin_clear(CONNECTED_LED_PIN_NO);
    nrf_gpio_pin_set(AVAILABLE_LED_PIN_NO);

    switch (op_code)
    {
        case SERIAL_DFU_OP_CODE_CREATE_OBJECT:

            if (packet_payload_len != CREATE_OBJECT_REQUEST_LEN)
            {
                serial_response.resp_val = NRF_DFU_RES_CODE_INVALID_PARAMETER;
                break;
            }

            NRF_LOG_DEBUG("Received create object\r\n");

            // Reset the packet receipt notification on create object
            p_dfu->pkt_notif_target_count = p_dfu->pkt_notif_target;

            // Get type parameter
            dfu_req.obj_type    =  p_payload[0];

            // Get length value
            dfu_req.object_size = uint32_decode(&p_payload[1]);

            // Set req type
            dfu_req.req_type        = NRF_DFU_OBJECT_OP_CREATE;

            serial_response.resp_val = nrf_dfu_req_handler_on_req(NULL, &dfu_req, &dfu_res);
            break;

        case SERIAL_DFU_OP_CODE_SET_RECEIPT_NOTIF:
            NRF_LOG_DEBUG("Set receipt notif\r\n");
            if (packet_payload_len != SET_RECEIPT_NOTIF_REQUEST_LEN)
            {
                serial_response.resp_val = NRF_DFU_RES_CODE_INVALID_PARAMETER;
                break;
            }

            p_dfu->pkt_notif_target = uint16_decode(&p_payload[0]);
            p_dfu->pkt_notif_target_count   = p_dfu->pkt_notif_target;

            serial_response.resp_val = NRF_DFU_RES_CODE_SUCCESS;
            break;

        case SERIAL_DFU_OP_CODE_CALCULATE_CRC:
            NRF_LOG_DEBUG("Received calculate CRC\r\n");

            dfu_req.req_type     =  NRF_DFU_OBJECT_OP_CRC;

            serial_response.resp_val = nrf_dfu_req_handler_on_req(NULL, &dfu_req, &dfu_res);
            serial_response.crc_response.offset = dfu_res.offset;
            serial_response.crc_response.crc    = dfu_res.crc;
            break;

        case SERIAL_DFU_OP_CODE_EXECUTE_OBJECT:
            NRF_LOG_DEBUG("Received execute object\r\n");

            // Set req type
            dfu_req.req_type     =  NRF_DFU_OBJECT_OP_EXECUTE;

            serial_response.resp_val = nrf_dfu_req_handler_on_req(NULL, &dfu_req, &dfu_res);
            break;

        case SERIAL_DFU_OP_CODE_SELECT_OBJECT:

            NRF_LOG_DEBUG("Received select object\r\n");
            if (packet_payload_len != SELECT_OBJECT_REQUEST_LEN)
            {
                serial_response.resp_val = NRF_DFU_RES_CODE_INVALID_PARAMETER;
                break;
            }

            // Set object type to read info about
            dfu_req.obj_type = p_payload[0];

            dfu_req.req_type = NRF_DFU_OBJECT_OP_SELECT;

            serial_response.resp_val = nrf_dfu_req_handler_on_req(NULL, &dfu_req, &dfu_res);
            serial_response.select_response.max_size = dfu_res.max_size;
            serial_response.select_response.offset   = dfu_res.offset;
            serial_response.select_response.crc      = dfu_res.crc;
            break;

        case SERIAL_DFU_OP_CODE_GET_SERIAL_MTU:
            NRF_LOG_DEBUG("Received get serial mtu\r\n");

            serial_response.resp_val = NRF_DFU_RES_CODE_SUCCESS;
            serial_response.serial_mtu_response.mtu = sizeof(p_dfu->recv_buffer);
            break;

        case SERIAL_DFU_OP_CODE_WRITE_OBJECT:
             // Set req type
            dfu_req.req_type =  NRF_DFU_OBJECT_OP_WRITE;

            // Set data and length
            dfu_req.p_req    =  &p_payload[0];
            dfu_req.req_len  =  packet_payload_len;

            serial_response.resp_val = nrf_dfu_req_handler_on_req(NULL, &dfu_req, &dfu_res);
            if(serial_response.resp_val != NRF_DFU_RES_CODE_SUCCESS)
            {
                NRF_LOG_ERROR("Failure to run packet write\r\n");
            }

            // Check if a packet receipt notification is needed to be sent.
            if (p_dfu->pkt_notif_target != 0 && --p_dfu->pkt_notif_target_count == 0)
            {
                serial_response.op_code = SERIAL_DFU_OP_CODE_CALCULATE_CRC;
                serial_response.crc_response.offset = dfu_res.offset;
                serial_response.crc_response.crc    = dfu_res.crc;

                // Reset the counter for the number of firmware packets.
                p_dfu->pkt_notif_target_count = p_dfu->pkt_notif_target;
            }
            break;

        default:
            // Unsupported op code.
            NRF_LOG_WARNING("Received unsupported OP code\r\n");
            serial_response.resp_val = NRF_DFU_RES_CODE_INVALID_PARAMETER;
            break;
    }

    if (op_code != SERIAL_DFU_OP_CODE_WRITE_OBJECT)
    {
        response_send(p_dfu, &serial_response);
    }
}


static __INLINE void on_rx_complete(serial_dfu_t * p_dfu, uint8_t * p_data, uint8_t len)
{
    ret_code_t ret_code;

    ret_code = slip_decode_add_byte(&p_dfu->slip, p_data[0]);

    if (ret_code == NRF_SUCCESS)
    {
        on_packet_received(p_dfu);

        // reset the slip decoding
        p_dfu->slip.current_index = 0;
        p_dfu->slip.state = SLIP_STATE_DECODING;
    }

    (void)nrf_drv_uart_rx(&m_dfu.uart_instance, &m_dfu.uart_buffer, 1);
}

static void uart_event_handler(nrf_drv_uart_event_t * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_UART_EVT_TX_DONE:
            nrf_dfu_req_handler_reset_if_dfu_complete();
            break;

        case NRF_DRV_UART_EVT_RX_DONE:
            on_rx_complete((serial_dfu_t*)p_context, p_event->data.rxtx.p_data, p_event->data.rxtx.bytes);
            break;

        case NRF_DRV_UART_EVT_ERROR:
            APP_ERROR_HANDLER(p_event->data.error.error_mask);
            break;
    }
}


uint32_t serial_dfu_transport_init(void)
{
    uint32_t err_code;

    leds_init();

    m_dfu.slip.p_buffer         = m_dfu.recv_buffer;
    m_dfu.slip.current_index    = 0;
    m_dfu.slip.buffer_len       = sizeof(m_dfu.recv_buffer);
    m_dfu.slip.state            = SLIP_STATE_DECODING;

    nrf_drv_uart_config_t uart_config = NRF_DRV_UART_DEFAULT_CONFIG;

    uart_config.pseltxd            = TX_PIN_NUMBER;
    uart_config.pselrxd            = RX_PIN_NUMBER;
    uart_config.pselcts            = CTS_PIN_NUMBER;
    uart_config.pselrts            = RTS_PIN_NUMBER;
    uart_config.hwfc               = NRF_UART_HWFC_ENABLED;
    uart_config.p_context          = &m_dfu;


    nrf_drv_uart_t instance =  NRF_DRV_UART_INSTANCE(0);
    memcpy(&m_dfu.uart_instance, &instance, sizeof(instance));

    err_code =  nrf_drv_uart_init(&m_dfu.uart_instance,
                                  &uart_config,
                                  uart_event_handler);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Failed initializing uart\n");
        return err_code;
    }

    nrf_drv_uart_rx_enable(&m_dfu.uart_instance);

    err_code = nrf_drv_uart_rx(&m_dfu.uart_instance, &m_dfu.uart_buffer, 1);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Failed initializing rx\n");
    }

    NRF_LOG_DEBUG("UART initialized\n");

    return err_code;
}


uint32_t serial_dfu_transport_close(void)
{
    nrf_drv_uart_uninit(&m_dfu.uart_instance);
    return NRF_SUCCESS;
}
