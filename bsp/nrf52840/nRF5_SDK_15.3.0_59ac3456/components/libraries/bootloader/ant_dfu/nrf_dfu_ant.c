/**
 * This software is subject to the ANT+ Shared Source License
 * www.thisisant.com/swlicenses
 * Copyright (c) Garmin Canada Inc. 2018
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 *    1) Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *
 *    2) Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *
 *    3) Neither the name of Garmin nor the names of its
 *       contributors may be used to endorse or promote products
 *       derived from this software without specific prior
 *       written permission.
 *
 * The following actions are prohibited:
 *
 *    1) Redistribution of source code containing the ANT+ Network
 *       Key. The ANT+ Network Key is available to ANT+ Adopters.
 *       Please refer to http://thisisant.com to become an ANT+
 *       Adopter and access the key. 
 *
 *    2) Reverse engineering, decompilation, and/or disassembly of
 *       software provided in binary form under this license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE HEREBY
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; DAMAGE TO ANY DEVICE, LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE. SOME STATES DO NOT ALLOW 
 * THE EXCLUSION OF INCIDENTAL OR CONSEQUENTIAL DAMAGES, SO THE
 * ABOVE LIMITATIONS MAY NOT APPLY TO YOU.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "sdk_common.h"

#include "ant_channel_config.h"
#include "ant_interface.h"
#include "ant_parameters.h"
#include "nrf_assert.h"
#include "nrf_balloc.h"
#include "nrf_bootloader_info.h"
#include "nrf_dfu_handling_error.h"
#include "nrf_dfu_req_handler.h"
#include "nrf_dfu_transport.h"
#include "nrf_dfu_mbr.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ant.h"
#include "nrf_soc.h"

#define NRF_LOG_MODULE_NAME nrf_dfu_ant
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@file
 *
 * @defgroup nrf_dfu_ant ANT transport for reference DFU.
 * @ingroup  nrf_dfu
 * @brief    Device Firmware Update (DFU) transport layer using ANT.
 *
 * Transport documentation:
 *
 * The ANT transport uses all of the same opcodes and payload formats as the
 * UART serial transport. The only differences are the packet header format and
 * some extra details to deal with retransmissions.
 *
 * The device receiving the update is the ANT master. The format of the
 * broadcast buffer is as follows;
 *      Byte 0: Current Slave -> Master sequence number.
 *      Byte 1: Current Master -> Slave sequence number.
 *      Bytes 2-7: Reserved, set to 0.
 *
 * The sequence numbers are used to detect retransmissions, any messages sent
 * with a sequence number equivalent to the current sequence will be ignored.
 *
 * When the slave first connects to the master it should inspect the broadcast
 * data in order to synchronize its sequence counters.
 *
 * All commands/responses are padded out to the nearest 8-byte boundary after
 * framing, and then sent using either a burst or acknowledged data depending on
 * length (ack data is used for 8-byte messages). The message transmission is
 * retried until an EVENT_TRANSFER_TX_COMPLETE event is received.
 * All messages are framed using the following format:
 *      Bytes 0-1: Message length before padding, little endian, includes header.
 *      Byte 2: Sequence number. Increment for every new message.
 *      Byte 3: Op code. Always 0x60 for responses.
 *      Bytes 4-N: Command/Response payload. This follows the same format as the
 *                 UART serial transport, without any SLIP encoding.
 *
 * As a final note, the MTU for this protocol is the maximum size of a burst
 * that can be received.
 */

/** Packet header is always 2 byte length + seq num + op code */
#define PKT_HEADER_SIZE 4

/** Maximum size of the payload in a write command. */
#define MAX_WRITE_PAYLOAD (NRF_DFU_ANT_MTU - PKT_HEADER_SIZE)

/** Bursts are always a multiple of the standard data size. */
STATIC_ASSERT_MSG(
    ALIGN_NUM(ANT_STANDARD_DATA_PAYLOAD_SIZE, NRF_DFU_ANT_MTU) == NRF_DFU_ANT_MTU,
    "ANT MTU must be a multiple of " STRINGIFY(ANT_STANDARD_DATA_PAYLOAD_SIZE));

/** Number of buffers to reserve space for with balloc. */
#if (NRF_DFU_ANT_BUFFERS_OVERRIDE)
#define NUM_BUFFERS NRF_DFU_ANT_BUFFERS
#else
#define NUM_BUFFERS CEIL_DIV(CODE_PAGE_SIZE, MAX_WRITE_PAYLOAD)
#endif

static uint32_t ant_dfu_init(nrf_dfu_observer_t observer);
static uint32_t ant_dfu_close(nrf_dfu_transport_t const * p_exception);

static ant_channel_config_t m_channel_config = {
    .channel_number = 0,
    .channel_type = CHANNEL_TYPE_MASTER,
    .rf_freq = NRF_DFU_ANT_RF_FREQ,
    .transmission_type = 1, // Non-shared, no global pages.
    .device_type = NRF_DFU_ANT_DEV_TYPE,
    .channel_period = NRF_DFU_ANT_CHANNEL_PERIOD,
};

static nrf_dfu_observer_t m_observer;
/** Has transport been initialized by DFU core */
static bool m_initialized = false;
/** Has the channel started broadcasting */
static bool m_started = false;
/** Has some data been received on the transport. */
static bool m_active = false;

/** State tracking for rx transfers. */
static struct
{
    /** Buffer for holding the command. */
    uint8_t * buff;
    /** Amount of data written */
    size_t offset;
    /** Sequence of last processed command. */
    uint8_t seq;
} m_rx;

/** State tracking for tx transfers. */
static struct
{
    /** Raw data to send. */
    uint8_t resp[ALIGN_NUM(ANT_STANDARD_DATA_PAYLOAD_SIZE,
        PKT_HEADER_SIZE + sizeof(nrf_dfu_response_t))];
    /** Length of data to send. 0 Indicates no response queued. */
    size_t len;
    /** Sequence number of last queued response. */
    uint8_t seq;
    /**
     * Used as burst flag for softdevice, allows to busy loop until all data is
     * accepted by softdevice.
     */
    volatile bool buffering;
    /**
     * Indicate that a new response was generated before the last one was
     * confirmed.
     */
    bool response_overwritten;
    /** Data buffer used for broadcast messages. */
    uint8_t bcast_data[ANT_STANDARD_DATA_PAYLOAD_SIZE];
} m_tx;

/** State tracking for progress notifications. */
static struct
{
    /** Requested PRN */
    uint16_t limit;
    /** How many more write commands until a CRC should be sent back. */
    uint16_t remaining;
} m_pkt_notify;

DFU_TRANSPORT_REGISTER(nrf_dfu_transport_t const ant_dfu_transport) = {
    .init_func = ant_dfu_init,
    .close_func = ant_dfu_close,
};

NRF_BALLOC_DEF(m_buffer_pool, NRF_DFU_ANT_MTU, NUM_BUFFERS);

static void release_rx_buff(void)
{
    if (m_rx.buff != NULL)
    {
        nrf_balloc_free(&m_buffer_pool, m_rx.buff);
        m_rx.buff = NULL;
    }
}

static void transmit_response(void)
{
    uint32_t err_code = NRF_SUCCESS;

    size_t full_len = ALIGN_NUM(ANT_STANDARD_DATA_PAYLOAD_SIZE, m_tx.len);

    // Pad out with 0's.
    memset(&m_tx.resp[m_tx.len], 0, full_len - m_tx.len);

    if (full_len > ANT_STANDARD_DATA_PAYLOAD_SIZE)
    {
        err_code = sd_ant_burst_handler_request(
            m_channel_config.channel_number,
            full_len, m_tx.resp,
            BURST_SEGMENT_START | BURST_SEGMENT_END);
    } else
    {
        err_code = sd_ant_acknowledge_message_tx(
            m_channel_config.channel_number,
            full_len, m_tx.resp);
    }

    // Wait for buffer to be consumed.
    // TODO: wait flag management needs to be improved if this will coexist with
    // other channels.
    while (err_code == NRF_SUCCESS && m_tx.buffering)
    {
        err_code = sd_app_evt_wait();
    }

    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Sending response failed with error %d", err_code);
    }
}

static void update_bcast_data(void)
{
    memset(m_tx.bcast_data, 0, sizeof(m_tx.bcast_data));
    m_tx.bcast_data[0] = m_rx.seq;
    m_tx.bcast_data[1] = m_tx.seq;

    if (NRF_SUCCESS != sd_ant_broadcast_message_tx(
        m_channel_config.channel_number,
        sizeof(m_tx.bcast_data), m_tx.bcast_data))
    {
        NRF_LOG_WARNING("Unable to update broadcast data.");
    }
}

static void handle_write_complete(void * p_buf)
{
    nrf_balloc_free(&m_buffer_pool, p_buf);
}

static void prepare_response(nrf_dfu_response_t * p_res)
{
    if (m_tx.len)
    {
        NRF_LOG_WARNING("Overwriting previous response.");
        m_tx.response_overwritten = true;
    }

    // reserve first 2 bytes for length.
    m_tx.len = 2;

    m_tx.resp[m_tx.len++] = ++(m_tx.seq);
    m_tx.resp[m_tx.len++] = NRF_DFU_OP_RESPONSE;
    m_tx.resp[m_tx.len++] = p_res->request;
    m_tx.resp[m_tx.len++] = p_res->result;

    if (p_res->result == NRF_DFU_RES_CODE_SUCCESS)
    {
        switch(p_res->request)
        {
            case NRF_DFU_OP_PROTOCOL_VERSION:
            {
                m_tx.resp[m_tx.len++] = p_res->protocol.version;
            } break;

            case NRF_DFU_OP_CRC_GET:
            {
                m_tx.len += uint32_encode(
                    p_res->crc.offset, &m_tx.resp[m_tx.len]);
                m_tx.len += uint32_encode(
                    p_res->crc.crc, &m_tx.resp[m_tx.len]);
            } break;

            case NRF_DFU_OP_OBJECT_SELECT:
            {
                m_tx.len += uint32_encode(
                    p_res->select.max_size, &m_tx.resp[m_tx.len]);
                m_tx.len += uint32_encode(
                    p_res->select.offset, &m_tx.resp[m_tx.len]);
                m_tx.len += uint32_encode(
                    p_res->select.crc, &m_tx.resp[m_tx.len]);
            } break;

            case NRF_DFU_OP_MTU_GET:
            {
                m_tx.len += uint16_encode(
                    p_res->mtu.size, &m_tx.resp[m_tx.len]);
            } break;

            case NRF_DFU_OP_PING:
            {
                m_tx.resp[m_tx.len++] = p_res->ping.id;
            } break;

            case NRF_DFU_OP_HARDWARE_VERSION:
            {
                m_tx.len += uint32_encode(
                    p_res->hardware.part, &m_tx.resp[m_tx.len]);
                m_tx.len += uint32_encode(
                    p_res->hardware.variant, &m_tx.resp[m_tx.len]);
                m_tx.len += uint32_encode(
                    p_res->hardware.memory.rom_size, &m_tx.resp[m_tx.len]);
                m_tx.len += uint32_encode(
                    p_res->hardware.memory.rom_page_size, &m_tx.resp[m_tx.len]);
                m_tx.len += uint32_encode(
                    p_res->hardware.memory.ram_size, &m_tx.resp[m_tx.len]);
            } break;

            case NRF_DFU_OP_FIRMWARE_VERSION:
            {
                m_tx.resp[m_tx.len++] = p_res->firmware.type;
                m_tx.len += uint32_encode(
                    p_res->firmware.version, &m_tx.resp[m_tx.len]);
                m_tx.len += uint32_encode(
                    p_res->firmware.addr, &m_tx.resp[m_tx.len]);
                m_tx.len += uint32_encode(
                    p_res->firmware.len, &m_tx.resp[m_tx.len]);
            } break;

            default:
                break;
        }
    }
    else if (p_res->result == NRF_DFU_RES_CODE_EXT_ERROR)
    {
        m_tx.resp[m_tx.len++] = ext_error_get();
        UNUSED_RETURN_VALUE(ext_error_set(NRF_DFU_EXT_ERROR_NO_ERROR));
    }

    // Finally fill in the length.
    UNUSED_RETURN_VALUE(uint16_encode(m_tx.len, m_tx.resp));

    // Safety check buffer overflow.
    ASSERT(m_tx.len <= sizeof(m_tx.resp));

    if (!m_tx.response_overwritten)
    {
        // Can send out the response immediately if there wasn't a previous one
        // queued.
        transmit_response();
    }
}

static void handle_response(nrf_dfu_response_t * p_res, void * p_context)
{
    UNUSED_PARAMETER(p_context);

    if (p_res->result != NRF_DFU_RES_CODE_SUCCESS)
    {
        NRF_LOG_WARNING("Operation %d had result %d",
            p_res->request, p_res->result);
    }

    if (p_res->request == NRF_DFU_OP_OBJECT_WRITE)
    {
        if (m_pkt_notify.limit == 0 ||
            --m_pkt_notify.remaining != 0)
        {
            // No packet notification needed, filter out response.
            return;
        }

        // Packet Notification time, send a CRC response.
        m_pkt_notify.remaining = m_pkt_notify.limit;
        p_res->request = NRF_DFU_OP_CRC_GET;
        uint32_t offset = p_res->write.offset;
        uint32_t crc = p_res->write.crc;
        p_res->crc.offset = offset;
        p_res->crc.crc = crc;
    }

    prepare_response(p_res);
}

static uint32_t handle_request(void)
{
    uint16_t len = uint16_decode(m_rx.buff);
    uint16_t offset = sizeof(uint16_t);

    if (len < PKT_HEADER_SIZE || len > m_rx.offset)
    {
        NRF_LOG_WARNING("Ignoring command with invalid length.");
        return NRF_ERROR_DATA_SIZE;
    }

    uint8_t seq = m_rx.buff[offset++];
    if (!m_active)
    {
        m_active = true;
        // Close all other transports.
        UNUSED_RETURN_VALUE(nrf_dfu_transports_close(&ant_dfu_transport));
    }
    else if (seq == m_rx.seq)
    {
        NRF_LOG_DEBUG("Ignoring repeated command");
        return NRF_SUCCESS;
    }

    m_rx.seq = seq;

    nrf_dfu_request_t request = {
        .request = (nrf_dfu_op_t)m_rx.buff[offset++],
        .callback.response = handle_response,
    };

    switch(request.request)
    {
        case NRF_DFU_OP_OBJECT_CREATE:
        {
            request.create.object_type = m_rx.buff[offset++];
            request.create.object_size = uint32_decode(&m_rx.buff[offset]);
            offset += sizeof(uint32_t);
        } break;

        case NRF_DFU_OP_RECEIPT_NOTIF_SET:
        {
            request.prn.target = uint16_decode(&m_rx.buff[offset]);
            offset += sizeof(uint16_t);
        } break;

        case NRF_DFU_OP_OBJECT_SELECT:
        {
            request.select.object_type = m_rx.buff[offset++];
        } break;

        case NRF_DFU_OP_OBJECT_WRITE:
        {
            request.write.p_data = &m_rx.buff[offset];
            request.write.len = len - offset;
            offset = len;
        } break;

        case NRF_DFU_OP_PING:
        {
            request.ping.id = m_rx.buff[offset++];
        } break;

        case NRF_DFU_OP_FIRMWARE_VERSION:
        {
            request.firmware.image_number = m_rx.buff[offset++];
        } break;

        case NRF_DFU_OP_MTU_GET:
        {
            NRF_LOG_DEBUG("ANT DFU: Responding to MTU request with %d",
                NRF_DFU_ANT_MTU);
            request.mtu.size = NRF_DFU_ANT_MTU;
        } break;

        default:
            // Do nothing.
            break;
    }

    if (offset > len)
    {
        NRF_LOG_WARNING("Ignoring command with invalid length");
        return NRF_ERROR_DATA_SIZE;
    }

    // Some processing that is only safe to do if accepting the command.

    switch (request.request)
    {
        case NRF_DFU_OP_RECEIPT_NOTIF_SET:
        {
            m_pkt_notify.limit = request.prn.target;
            m_pkt_notify.remaining = m_pkt_notify.limit;
        } break;

        case NRF_DFU_OP_OBJECT_CREATE:
        case NRF_DFU_OP_OBJECT_SELECT:
        {
            m_pkt_notify.remaining = m_pkt_notify.limit;
        } break;

        case NRF_DFU_OP_OBJECT_WRITE:
        {
            // Ownership of buffer is transferred to the write command.
            request.callback.write = handle_write_complete;
            m_rx.buff = NULL;
        } break;

        default:
            break;
    }

    return nrf_dfu_req_handler_on_req(&request);
}

static void handle_tx_transfer_complete(bool success)
{
    if (m_tx.response_overwritten)
    {
        // By treating the result as a failure the retransmission will send out
        // the new response.
        success = false;
        m_tx.response_overwritten = false;
    }

    if (success)
    {
        m_tx.len = 0;
        update_bcast_data();
    }
    else
    {
        transmit_response();
    }
}

static void handle_rx_transfer_start()
{
    if (m_rx.buff == NULL)
    {
        m_rx.buff = nrf_balloc_alloc(&m_buffer_pool);
        if (m_rx.buff != NULL)
        {
            NRF_LOG_INFO("Allocated buffer %x", m_rx.buff);
        }
        else
        {
            NRF_LOG_ERROR("Unable to allocate buffer for incoming packet.");
            return;
        }
    }

    NRF_LOG_DEBUG("Resetting rx pointer.");
    m_rx.offset = 0;
}

static void handle_rx_transfer_complete(bool success)
{
    if (success)
    {
        uint32_t err_code = handle_request();
        if (err_code != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("Error %d handling request.", err_code);
        }
    }

    release_rx_buff();
}

static void handle_rx_transfer_data(uint8_t * data, size_t len)
{
    if (m_rx.buff == NULL)
    {
        NRF_LOG_DEBUG("Ignoring transfer data.");
        return;
    }

    if (m_rx.offset + len > NRF_DFU_ANT_MTU)
    {
        NRF_LOG_ERROR("Received packet overflows MTU.");
        handle_rx_transfer_complete(false);
        return;
    }

    memcpy(&m_rx.buff[m_rx.offset], data, len);
    m_rx.offset += len;
}

static void handle_data_mesg(ANT_MESSAGE * p_msg)
{
    bool is_first = false;
    bool is_last = false;
    uint8_t len = ANT_STANDARD_DATA_PAYLOAD_SIZE;

    switch(p_msg->ANT_MESSAGE_ucMesgID)
    {
        case MESG_BROADCAST_DATA_ID:
        {
            // Broadcast data is ignored.
            len = 0;
        } break;

        case MESG_ACKNOWLEDGED_DATA_ID:
        {
            is_first = true;
            is_last = true;
        } break;

        case MESG_ADV_BURST_DATA_ID:
        {
            len = p_msg->ANT_MESSAGE_ucSize - MESG_CHANNEL_NUM_SIZE;
        } // FALL-THROUGH : both burst types act the same other than len.
        case MESG_BURST_DATA_ID:
        {
            uint8_t seq = p_msg->ANT_MESSAGE_ucChannel & SEQUENCE_NUMBER_MASK;
            is_first = seq == SEQUENCE_FIRST_MESSAGE;
            is_last = !!(seq & SEQUENCE_LAST_MESSAGE);
        } break;
    }

    if (len != 0)
    {
        if (is_first)
        {
            handle_rx_transfer_start();
        }

        handle_rx_transfer_data(p_msg->ANT_MESSAGE_aucPayload, len);

        if (is_last)
        {
            handle_rx_transfer_complete(true);
        }
    }
}

static void ant_dfu_evt_handler(ant_evt_t * p_ant_evt, void * p_context)
{
    // Ignore messages meant for other channels.
    if (p_ant_evt->channel != m_channel_config.channel_number)
    {
        return;
    }

    switch(p_ant_evt->event)
    {
        case EVENT_TX:
        {
            if (!m_started)
            {
                m_started = true;
                m_observer(NRF_DFU_EVT_TRANSPORT_ACTIVATED);
            }
        } break;

        case EVENT_TRANSFER_TX_COMPLETED:
            handle_tx_transfer_complete(true);
            break;
        case EVENT_TRANSFER_TX_FAILED:
            handle_tx_transfer_complete(false);
            break;

        case EVENT_RX:
            handle_data_mesg(&p_ant_evt->message);
            break;

        case EVENT_TRANSFER_RX_FAILED:
            handle_rx_transfer_complete(false);
            break;
    }
}

static uint32_t ant_dfu_init(nrf_dfu_observer_t observer)
{
    uint32_t err_code = NRF_SUCCESS;
    if (m_initialized)
    {
        return err_code;
    }

    NRF_SDH_ANT_OBSERVER(ant_dfu_observer, NRF_DFU_ANT_EVT_HANDLER_PRIO,
        ant_dfu_evt_handler, NULL);

    m_observer = observer;
    m_tx.seq = m_rx.seq = 0;
    m_active = false;
    m_started = false;

    NRF_LOG_DEBUG("Initializing ANT DFU transport");

    err_code = nrf_balloc_init(&m_buffer_pool);
    VERIFY_SUCCESS(err_code);

    err_code = nrf_dfu_mbr_init_sd();
    VERIFY_SUCCESS(err_code);

    NRF_LOG_DEBUG("Setting up vector table: 0x%08x", BOOTLOADER_START_ADDR);
    err_code = sd_softdevice_vector_table_base_set(BOOTLOADER_START_ADDR);
    VERIFY_SUCCESS(err_code);

    NRF_LOG_DEBUG("Enabling softdevice");
    err_code = nrf_sdh_enable_request();
    VERIFY_SUCCESS(err_code);

    err_code = nrf_sdh_ant_enable();
    VERIFY_SUCCESS(err_code);

    static uint8_t adv_burst_conf[] = {
        ADV_BURST_MODE_ENABLE,
        ADV_BURST_MODES_SIZE_24_BYTES,
        0, // No required modes.
        0, 0, // Reserved
        ADV_BURST_MODES_FREQ_HOP, // Optional Modes
        0, 0, // Reserved
        // No optional configs.
    };
    err_code = sd_ant_adv_burst_config_set(adv_burst_conf, sizeof(adv_burst_conf));
    VERIFY_SUCCESS(err_code);

    m_channel_config.device_number = NRF_FICR->DEVICEID[0];
    m_channel_config.transmission_type |= (NRF_FICR->DEVICEID[1] & 0xF) << 4;

    err_code = ant_channel_init(&m_channel_config);
    VERIFY_SUCCESS(err_code);

    update_bcast_data();

    err_code = sd_ant_channel_open(m_channel_config.channel_number);
    VERIFY_SUCCESS(err_code);

    NRF_LOG_DEBUG("ANT transport intialized");

    m_initialized = true;
    return err_code;
}

static uint32_t ant_dfu_close(nrf_dfu_transport_t const * p_exception)
{
    uint32_t err_code = NRF_SUCCESS;

    if (p_exception != &ant_dfu_transport && m_initialized)
    {
        NRF_LOG_DEBUG("Shutting down ANT DFU transport");

        m_initialized = false;

        err_code = sd_ant_channel_close(m_channel_config.channel_number);
        VERIFY_SUCCESS(err_code);

        uint8_t status;
        do
        {
            // The initial wait is safe because the close command above would
            // have generated at least 1 app event.
            err_code = sd_app_evt_wait();
            VERIFY_SUCCESS(err_code);
            err_code = sd_ant_channel_status_get(
                m_channel_config.channel_number, &status);
            VERIFY_SUCCESS(err_code);
        } while ((status & STATUS_CHANNEL_STATE_MASK) != STATUS_ASSIGNED_CHANNEL);

        err_code = nrf_sdh_disable_request();
        VERIFY_SUCCESS(err_code);

        NRF_LOG_DEBUG("ANT transport disabled.");
    }

    return err_code;
}
