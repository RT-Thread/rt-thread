/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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

#include "nrf_dfu_serial.h"
#include "nrf_dfu_req_handler.h"
#include "nrf_dfu_handling_error.h"

#define NRF_LOG_MODULE_NAME nrf_dfu_serial
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define NRF_SERIAL_OPCODE_SIZE (sizeof(uint8_t))



static uint32_t response_ext_err_payload_add(uint8_t * p_buffer, uint32_t buf_offset)
{
    p_buffer[buf_offset] = ext_error_get();
    (void) ext_error_set(NRF_DFU_EXT_ERROR_NO_ERROR);

    return 1;
}


static void response_send(nrf_dfu_serial_t         * p_transport,
                          nrf_dfu_response_t const * p_response)
{
    uint8_t   index            = 0;
    uint8_t * p_serialized_rsp = p_transport->p_rsp_buf;

    NRF_LOG_DEBUG("Sending Response: [0x%01x, 0x%01x]", p_response->request, p_response->result);

    p_serialized_rsp[index++] = NRF_DFU_OP_RESPONSE;
    p_serialized_rsp[index++] = p_response->request;
    p_serialized_rsp[index++] = (uint8_t)(p_response->result);

    if (p_response->result == NRF_DFU_RES_CODE_SUCCESS)
    {
        switch (p_response->request)
        {
            case NRF_DFU_OP_PROTOCOL_VERSION:
            {
                p_serialized_rsp[index] = p_response->protocol.version;
                index += sizeof(uint8_t);
            } break;

            case NRF_DFU_OP_HARDWARE_VERSION:
            {
                index += uint32_encode(p_response->hardware.part,                 &p_serialized_rsp[index]);
                index += uint32_encode(p_response->hardware.variant,              &p_serialized_rsp[index]);
                index += uint32_encode(p_response->hardware.memory.rom_size,      &p_serialized_rsp[index]);
                index += uint32_encode(p_response->hardware.memory.ram_size,      &p_serialized_rsp[index]);
                index += uint32_encode(p_response->hardware.memory.rom_page_size, &p_serialized_rsp[index]);
            } break;

            case NRF_DFU_OP_FIRMWARE_VERSION:
            {
                p_serialized_rsp[index++] = p_response->firmware.type;
                index += uint32_encode(p_response->firmware.version, &p_serialized_rsp[index]);
                index += uint32_encode(p_response->firmware.addr,    &p_serialized_rsp[index]);
                index += uint32_encode(p_response->firmware.len,     &p_serialized_rsp[index]);
            } break;

            case NRF_DFU_OP_CRC_GET:
                index += uint32_encode(p_response->crc.offset, &p_serialized_rsp[index]);
                index += uint32_encode(p_response->crc.crc,    &p_serialized_rsp[index]);
                break;

            case NRF_DFU_OP_OBJECT_SELECT:
                index += uint32_encode(p_response->select.max_size, &p_serialized_rsp[index]);
                index += uint32_encode(p_response->select.offset,   &p_serialized_rsp[index]);
                index += uint32_encode(p_response->select.crc,      &p_serialized_rsp[index]);
                break;

            case NRF_DFU_OP_MTU_GET:
                index += uint16_encode(p_response->mtu.size, &p_serialized_rsp[index]);
                break;

            case NRF_DFU_OP_PING:
                p_serialized_rsp[index] = p_response->ping.id;
                index += sizeof(uint8_t);
                break;

            default:
                // no implementation
                break;
        }
    }
    else if (p_response->result == NRF_DFU_RES_CODE_EXT_ERROR)
    {
        index += response_ext_err_payload_add(p_serialized_rsp, index);
    }

    if (index > NRF_SERIAL_MAX_RESPONSE_SIZE)
    {
        NRF_LOG_ERROR("Message is larger than expected.");
    }

    // Send response.
    if (p_transport->rsp_func((uint8_t const *)(p_serialized_rsp), index) != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Failed to send data over serial interface!");
    }
}


void dfu_req_handler_rsp_clbk(nrf_dfu_response_t * p_res, void * p_context)
{
    nrf_dfu_serial_t * p_transport = (nrf_dfu_serial_t *)(p_context);

    if (p_res->result != NRF_DFU_RES_CODE_SUCCESS)
    {
        NRF_LOG_WARNING("DFU request completed with result: 0x%x", p_res->result);
    }

    switch (p_res->request)
    {
        default:
            /* Reply normally.
             * Make sure to reply to NRF_DFU_OP_OBJECT_CREATE when running DFU over serial,
             * otherwise the transfer might run very slow, without an apparent reason.
             */
            break;

        case NRF_DFU_OP_OBJECT_WRITE:
        {
            p_transport->pkt_notif_target_count--;

            if (   (p_transport->pkt_notif_target       == 0)
                || (p_transport->pkt_notif_target_count != 0))
            {
                /* Do not reply to _OBJECT_WRITE messages. */
                return;
            }

            /* Reply with a CRC message and reset the packet counter. */
            p_transport->pkt_notif_target_count = p_transport->pkt_notif_target;

            p_res->request    = NRF_DFU_OP_CRC_GET;
            p_res->crc.offset = p_res->write.offset;
            p_res->crc.crc    = p_res->write.crc;
        } break;
    }

    response_send(p_transport, p_res);
}


void nrf_dfu_serial_on_packet_received(nrf_dfu_serial_t       * p_transport,
                                       uint8_t          const * p_data,
                                       uint32_t                 length)
{
    uint8_t  const * p_payload   = &p_data[NRF_SERIAL_OPCODE_SIZE];
    uint16_t const   payload_len = (length - NRF_SERIAL_OPCODE_SIZE);

    nrf_dfu_request_t request =
    {
        .request           = (nrf_dfu_op_t)(p_data[0]),
        .callback.response = dfu_req_handler_rsp_clbk,
        .p_context         = p_transport
    };

    bool buf_free = true;

    switch (request.request)
    {
        case NRF_DFU_OP_FIRMWARE_VERSION:
        {
            request.firmware.image_number = p_payload[0];
        } break;

        case NRF_DFU_OP_RECEIPT_NOTIF_SET:
        {
            NRF_LOG_DEBUG("Set receipt notif target: %d", p_transport->pkt_notif_target);

            p_transport->pkt_notif_target       = uint16_decode(&p_payload[0]);
            p_transport->pkt_notif_target_count = p_transport->pkt_notif_target;
        } break;

        case NRF_DFU_OP_OBJECT_SELECT:
        {
            request.select.object_type = p_payload[0];
        } break;

        case NRF_DFU_OP_OBJECT_CREATE:
        {
            // Reset the packet receipt notification on create object
            p_transport->pkt_notif_target_count = p_transport->pkt_notif_target;

            request.create.object_type = p_payload[0];
            request.create.object_size = uint32_decode(&p_payload[1]);
        } break;

        case NRF_DFU_OP_OBJECT_WRITE:
        {
            // Buffer will be freed asynchronously
            buf_free = false;

            request.write.p_data   = p_payload;
            request.write.len      = payload_len;
            request.callback.write = p_transport->payload_free_func;
        } break;

        case NRF_DFU_OP_MTU_GET:
        {
            NRF_LOG_DEBUG("Received serial mtu");
            request.mtu.size = p_transport->mtu;
        } break;

        case NRF_DFU_OP_PING:
        {
            NRF_LOG_DEBUG("Received ping %d", p_payload[0]);
            request.ping.id = p_payload[0];
        } break;

        default:
            /* Do nothing. */
            break;
    }

    if (buf_free)
    {
        p_transport->payload_free_func((void *)(p_payload));
    }

    ret_code_t ret_code = nrf_dfu_req_handler_on_req(&request);
    ASSERT(ret_code == NRF_SUCCESS);
}
