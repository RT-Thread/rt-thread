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
#include <string.h>
#include "ant_conn.h"
#include "conn_mw_ant.h"
#include "ble_serialization.h"
#include "nrf_log_ctrl.h"
#include "sdk_config.h"

#define ANT_BUFFER_SIZE_FOR_SD      ANT_ENABLE_GET_REQUIRED_SPACE(ANT_SER_CONFIG_TOTAL_CHANNELS_ALLOCATED, \
                                                                  ANT_SER_CONFIG_ENCRYPTED_CHANNELS,       \
                                                                  ANT_SER_CONFIG_BURST_QUEUE_SIZE,         \
                                                                  ANT_SER_CONFIG_EVENT_QUEUE_SIZE)
#define ANT_ADV_BURST_CFG_SIZE_MAX  (11u)
#define ANT_CRYPTO_INFO_SIZE        (((MESG_CONFIG_ENCRYPT_REQ_CONFIG_USER_DATA_SIZE) - \
                                      (MESG_CHANNEL_NUM_SIZE)) +                        \
                                     ((MESG_CONFIG_ENCRYPT_REQ_CONFIG_ID_SIZE) -        \
                                      (MESG_CHANNEL_NUM_SIZE)))
#define ANT_CRYPTO_INFO_MAX_SIZE    (MESG_CONFIG_ENCRYPT_REQ_CONFIG_USER_DATA_SIZE - \
                                     MESG_CHANNEL_NUM_SIZE)

#ifdef ANT_STACK_SUPPORT_REQD
static union
{
    uint8_t  u8[ANT_BUFFER_SIZE_FOR_SD];
    uint32_t u32[1]; // force allign to uint32_t
}ant_stack_buffer; /*!< Memory buffer provided in order to support channel configuration */
#endif

uint32_t conn_mw_ant_enable(uint8_t const * const p_rx_buf,
                            uint32_t              rx_buf_len,
                            uint8_t * const       p_tx_buf,
                            uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);


    ANT_ENABLE   params;
    ANT_ENABLE * p_params = &params;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_enable_req_dec(p_rx_buf, rx_buf_len, &p_params);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    SER_ASSERT(p_params -> ucTotalNumberOfChannels == ANT_SER_CONFIG_TOTAL_CHANNELS_ALLOCATED, err_code);
    SER_ASSERT(p_params -> ucNumberOfEncryptedChannels == ANT_SER_CONFIG_ENCRYPTED_CHANNELS, err_code);
    SER_ASSERT(p_params -> usNumberOfEvents == ANT_SER_CONFIG_EVENT_QUEUE_SIZE, err_code);
    SER_ASSERT(p_params -> usMemoryBlockByteSize == ANT_BUFFER_SIZE_FOR_SD, err_code);

    ANT_ENABLE m_ant_enable_cfg =
    {
        .ucTotalNumberOfChannels        = p_params -> ucTotalNumberOfChannels,
        .ucNumberOfEncryptedChannels    = p_params -> ucNumberOfEncryptedChannels,
        .usNumberOfEvents               = p_params -> usNumberOfEvents,
        .pucMemoryBlockStartLocation    = ant_stack_buffer.u8,
        .usMemoryBlockByteSize          = p_params -> usMemoryBlockByteSize
    };

    sd_err_code = sd_ant_enable(&m_ant_enable_cfg);

    err_code = ant_enable_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_channel_assign(uint8_t const * const p_rx_buf,
                                 uint32_t              rx_buf_len,
                                 uint8_t * const       p_tx_buf,
                                 uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint8_t type;
    uint8_t network;
    uint8_t ext_assign;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code =ant_channel_assign_req_dec(p_rx_buf, rx_buf_len, &channel, &type, &network, &ext_assign);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    //disabled till codec is adopted.
    sd_err_code = sd_ant_channel_assign(channel, type, network, ext_assign);


    err_code = ant_channel_assign_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;

}

uint32_t conn_ant_channel_open_with_offset(uint8_t const * const p_rx_buf,
                                           uint32_t              rx_buf_len,
                                           uint8_t * const       p_tx_buf,
                                           uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t  channel;
    uint16_t usOffset;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_channel_open_with_offset_req_dec(p_rx_buf, rx_buf_len, &channel, &usOffset);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_channel_open_with_offset(channel, usOffset);

    err_code = ant_channel_open_with_offset_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}


uint32_t conn_ant_channel_id_set(uint8_t const * const p_rx_buf,
                                 uint32_t              rx_buf_len,
                                 uint8_t * const       p_tx_buf,
                                 uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint16_t device_number;
    uint8_t device_type;
    uint8_t transmission_type;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code =ant_channel_id_set_req_dec(p_rx_buf, rx_buf_len, &channel, &device_number, &device_type, &transmission_type);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    //disabled till codec is adopted.
    sd_err_code = sd_ant_channel_id_set(channel, device_number, device_type, transmission_type);

    err_code = ant_channel_id_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_channel_period_set(uint8_t const * const p_rx_buf,
                                     uint32_t              rx_buf_len,
                                     uint8_t * const       p_tx_buf,
                                     uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint16_t period;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_channel_period_set_req_dec(p_rx_buf, rx_buf_len, &channel, &period);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_channel_period_set(channel, period);

    err_code = ant_channel_period_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_channel_radio_freq_set(uint8_t const * const p_rx_buf,
                                         uint32_t              rx_buf_len,
                                         uint8_t * const       p_tx_buf,
                                         uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint8_t freq;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_channel_radio_freq_set_req_dec(p_rx_buf, rx_buf_len, &channel, &freq);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_channel_radio_freq_set(channel, freq);

    err_code = ant_channel_radio_freq_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_broadcast_message_tx(uint8_t const * const p_rx_buf,
                                       uint32_t              rx_buf_len,
                                       uint8_t * const       p_tx_buf,
                                       uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint8_t size;
    uint8_t mesg[ANT_STANDARD_DATA_PAYLOAD_SIZE];
    uint8_t * p_mesg = mesg;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_broadcast_message_tx_req_dec(p_rx_buf, rx_buf_len, &channel, &size, &p_mesg);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_broadcast_message_tx(channel, size, p_mesg);

    err_code = ant_broadcast_message_tx_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_acknowledge_message_tx(uint8_t const * const p_rx_buf,
                                         uint32_t              rx_buf_len,
                                         uint8_t * const       p_tx_buf,
                                         uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint8_t size;
    uint8_t mesg[ANT_STANDARD_DATA_PAYLOAD_SIZE];
    uint8_t * p_mesg = mesg;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_acknowledge_message_tx_req_dec(p_rx_buf, rx_buf_len, &channel, &size, &p_mesg);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_acknowledge_message_tx(channel, size, p_mesg);

    err_code = ant_acknowledge_message_tx_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_channel_unassign(uint8_t const * const p_rx_buf,
                                   uint32_t              rx_buf_len,
                                   uint8_t * const       p_tx_buf,
                                   uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_channel_unassign_req_dec(p_rx_buf, rx_buf_len, &channel);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_channel_unassign(channel);

    err_code = ant_channel_unassign_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_channel_close(uint8_t const * const p_rx_buf,
                                uint32_t              rx_buf_len,
                                uint8_t * const       p_tx_buf,
                                uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_channel_close_req_dec(p_rx_buf, rx_buf_len, &channel);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_channel_close(channel);

    err_code = ant_channel_close_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_network_address_set(uint8_t const * const p_rx_buf,
                                      uint32_t              rx_buf_len,
                                      uint8_t * const       p_tx_buf,
                                      uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t network;
    uint8_t network_address[MESG_NETWORK_KEY_SIZE - MESG_CHANNEL_NUM_SIZE];
    uint8_t * p_network_address = network_address;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_network_address_set_req_dec(p_rx_buf, rx_buf_len, &network, &p_network_address);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_network_address_set(network, p_network_address);

    err_code = ant_network_address_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_channel_radio_tx_power_set(uint8_t const * const p_rx_buf,
                                             uint32_t              rx_buf_len,
                                             uint8_t * const       p_tx_buf,
                                             uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint8_t tx_power;
    uint8_t custom_tx_power;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_channel_radio_tx_power_set_req_dec(p_rx_buf, rx_buf_len, &channel, &tx_power, &custom_tx_power);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_channel_radio_tx_power_set(channel, tx_power, custom_tx_power);

    err_code = ant_channel_radio_tx_power_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_channel_rx_search_timeout_set(uint8_t const * const p_rx_buf,
                                                uint32_t              rx_buf_len,
                                                uint8_t * const       p_tx_buf,
                                                uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint8_t timeout;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_channel_rx_search_timeout_set_req_dec(p_rx_buf, rx_buf_len, &channel, &timeout);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_channel_rx_search_timeout_set(channel, timeout);

    err_code = ant_channel_rx_search_timeout_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_channel_low_priority_rx_search_timeout_set(uint8_t const * const p_rx_buf,
                                                             uint32_t              rx_buf_len,
                                                             uint8_t * const       p_tx_buf,
                                                             uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint8_t timeout;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_channel_low_priority_rx_search_timeout_set_req_dec(p_rx_buf, rx_buf_len, &channel, &timeout);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_channel_low_priority_rx_search_timeout_set(channel, timeout);

    err_code = ant_channel_low_priority_rx_search_timeout_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_prox_search_set(uint8_t const * const p_rx_buf,
                                  uint32_t              rx_buf_len,
                                  uint8_t * const       p_tx_buf,
                                  uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint8_t prox_threshold;
    uint8_t custom_prox_threshold;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_prox_search_set_req_dec(p_rx_buf, rx_buf_len, &channel, &prox_threshold, &custom_prox_threshold);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_prox_search_set(channel, prox_threshold, custom_prox_threshold);

    err_code = ant_prox_search_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_search_waveform_set(uint8_t const * const p_rx_buf,
                                      uint32_t              rx_buf_len,
                                      uint8_t * const       p_tx_buf,
                                      uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint16_t waveform;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_search_waveform_set_req_dec(p_rx_buf, rx_buf_len, &channel, &waveform);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_search_waveform_set(channel, waveform);

    err_code = ant_search_waveform_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_channel_id_get(uint8_t const * const p_rx_buf,
                                 uint32_t              rx_buf_len,
                                 uint8_t * const       p_tx_buf,
                                 uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t device_number;
    uint8_t device_type;
    uint8_t transmit_type;
    uint8_t channel;
    uint16_t * p_device_number = &device_number;
    uint8_t * p_device_type = &device_type;
    uint8_t * p_transmit_type = &transmit_type;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_channel_id_get_req_dec(p_rx_buf, rx_buf_len, &channel);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_channel_id_get(channel, p_device_number, p_device_type, p_transmit_type);

    err_code = ant_channel_id_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_device_number, p_device_type, p_transmit_type);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_channel_radio_freq_get(uint8_t const * const p_rx_buf,
                                         uint32_t              rx_buf_len,
                                         uint8_t * const       p_tx_buf,
                                         uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t r_freq;
    uint8_t channel;
    uint8_t * p_r_freq = &r_freq;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_channel_radio_freq_get_req_dec(p_rx_buf, rx_buf_len, &channel);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_channel_radio_freq_get(channel, p_r_freq);

    err_code = ant_channel_radio_freq_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_r_freq);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_channel_period_get(uint8_t const * const p_rx_buf,
                                     uint32_t              rx_buf_len,
                                     uint8_t * const       p_tx_buf,
                                     uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t period;
    uint8_t channel;
    uint16_t * p_period = &period;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_channel_period_get_req_dec(p_rx_buf, rx_buf_len, &channel);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_channel_period_get(channel, p_period);

    err_code = ant_channel_period_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_period);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_search_channel_priority_set(uint8_t const * const p_rx_buf,
                                              uint32_t              rx_buf_len,
                                              uint8_t * const       p_tx_buf,
                                              uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint8_t search_priority;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_search_channel_priority_set_req_dec(p_rx_buf, rx_buf_len, &channel, &search_priority);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_search_channel_priority_set(channel, search_priority);

    err_code = ant_search_channel_priority_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_active_search_sharing_cycles_set(uint8_t const * const p_rx_buf,
                                                   uint32_t              rx_buf_len,
                                                   uint8_t * const       p_tx_buf,
                                                   uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint8_t cycles;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_active_search_sharing_cycles_set_req_dec(p_rx_buf, rx_buf_len, &channel, &cycles);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_active_search_sharing_cycles_set(channel, cycles);

    err_code = ant_active_search_sharing_cycles_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_lib_config_set(uint8_t const * const p_rx_buf,
                                 uint32_t              rx_buf_len,
                                 uint8_t * const       p_tx_buf,
                                 uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t ant_lib_config;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_lib_config_set_req_dec(p_rx_buf, rx_buf_len, &ant_lib_config);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_lib_config_set(ant_lib_config);

    err_code = ant_lib_config_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_active_search_sharing_cycles_get(uint8_t const * const p_rx_buf,
                                                   uint32_t              rx_buf_len,
                                                   uint8_t * const       p_tx_buf,
                                                   uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t cycles;
    uint8_t channel;
    uint8_t * p_cycles = &cycles;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_active_search_sharing_cycles_get_req_dec(p_rx_buf, rx_buf_len, &channel);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_active_search_sharing_cycles_get(channel, p_cycles);

    err_code = ant_active_search_sharing_cycles_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_cycles);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_lib_config_get(uint8_t const * const p_rx_buf,
                                 uint32_t              rx_buf_len,
                                 uint8_t * const       p_tx_buf,
                                 uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t ant_lib_config;
    uint8_t * p_ant_lib_config = &ant_lib_config;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    sd_err_code = sd_ant_lib_config_get(p_ant_lib_config);

    err_code = ant_lib_config_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_ant_lib_config);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_lib_config_clear(uint8_t const * const p_rx_buf,
                                   uint32_t              rx_buf_len,
                                   uint8_t * const       p_tx_buf,
                                   uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t ant_lib_config;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_lib_config_clear_req_dec(p_rx_buf, rx_buf_len, &ant_lib_config);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_lib_config_clear(ant_lib_config);

    err_code = ant_lib_config_clear_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_stack_reset(uint8_t const * const p_rx_buf,
                              uint32_t              rx_buf_len,
                              uint8_t * const       p_tx_buf,
                              uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    sd_err_code = sd_ant_stack_reset();

    err_code = ant_stack_reset_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_rx_scan_mode_start(uint8_t const * const p_rx_buf,
                                     uint32_t              rx_buf_len,
                                     uint8_t * const       p_tx_buf,
                                     uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t sync_channel_packets_only;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_rx_scan_mode_start_req_dec(p_rx_buf, rx_buf_len, &sync_channel_packets_only);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_rx_scan_mode_start(sync_channel_packets_only);

    err_code = ant_rx_scan_mode_start_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_id_list_add(uint8_t const * const p_rx_buf,
                              uint32_t              rx_buf_len,
                              uint8_t * const       p_tx_buf,
                              uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint8_t dev_id[ANT_ID_SIZE];
    uint8_t * p_dev_id = dev_id;
    uint8_t list_index;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_id_list_add_req_dec(p_rx_buf, rx_buf_len, &channel, &p_dev_id, &list_index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_id_list_add(channel, p_dev_id, list_index);

    err_code = ant_id_list_add_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_id_list_config(uint8_t const * const p_rx_buf,
                                 uint32_t              rx_buf_len,
                                 uint8_t * const       p_tx_buf,
                                 uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint8_t id_list_size;
    uint8_t inc_exc_flag;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_id_list_config_req_dec(p_rx_buf, rx_buf_len, &channel, &id_list_size, &inc_exc_flag);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_id_list_config(channel, id_list_size, inc_exc_flag);

    err_code = ant_id_list_config_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_channel_status_get(uint8_t const * const p_rx_buf,
                                     uint32_t              rx_buf_len,
                                     uint8_t * const       p_tx_buf,
                                     uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t status;
    uint8_t channel;
    uint8_t * p_status = &status;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_channel_status_get_req_dec(p_rx_buf, rx_buf_len, &channel);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_channel_status_get(channel, p_status);

    err_code = ant_channel_status_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_status);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_cw_test_mode_init(uint8_t const * const p_rx_buf,
                                    uint32_t              rx_buf_len,
                                    uint8_t * const       p_tx_buf,
                                    uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    sd_err_code = sd_ant_cw_test_mode_init();

    err_code = ant_cw_test_mode_init_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_cw_test_mode(uint8_t const * const p_rx_buf,
                               uint32_t              rx_buf_len,
                               uint8_t * const       p_tx_buf,
                               uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t radio_freq;
    uint8_t tx_power;
    uint8_t custom_tx_power;
    uint8_t mode;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_cw_test_mode_req_dec(p_rx_buf, rx_buf_len, &radio_freq, &tx_power, &custom_tx_power, &mode);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_cw_test_mode(radio_freq, tx_power, custom_tx_power, mode);

    err_code = ant_cw_test_mode_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_version_get(uint8_t const * const p_rx_buf,
                              uint32_t              rx_buf_len,
                              uint8_t * const       p_tx_buf,
                              uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t version[MESG_BUFFER_SIZE];
    memset(version, 0, sizeof(version));

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    sd_err_code = sd_ant_version_get(version);

    err_code = ant_version_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, version);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_capabilities_get(uint8_t const * const p_rx_buf,
                                   uint32_t              rx_buf_len,
                                   uint8_t * const       p_tx_buf,
                                   uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t capabilities[MESG_CAPABILITIES_SIZE];
    memset(capabilities, 0, sizeof(capabilities));

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    sd_err_code = sd_ant_capabilities_get(capabilities);

    err_code = ant_capabilities_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, capabilities);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_crypto_channel_enable(uint8_t const * const p_rx_buf,
                                        uint32_t              rx_buf_len,
                                        uint8_t * const       p_tx_buf,
                                        uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint8_t enable;
    uint8_t key_num;
    uint8_t decimation_rate;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_crypto_channel_enable_req_dec(p_rx_buf, rx_buf_len, &channel, &enable, &key_num, &decimation_rate);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_crypto_channel_enable(channel, enable, key_num, decimation_rate);

    err_code = ant_crypto_channel_enable_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_adv_burst_config_set(uint8_t const * const p_rx_buf,
                                       uint32_t              rx_buf_len,
                                       uint8_t * const       p_tx_buf,
                                       uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t size;
    uint8_t config[ANT_ADV_BURST_CFG_SIZE_MAX];

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_adv_burst_config_set_req_dec(p_rx_buf, rx_buf_len, config, &size);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_adv_burst_config_set(config, size);

    err_code = ant_adv_burst_config_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_crypto_key_set(uint8_t const * const p_rx_buf,
                                 uint32_t              rx_buf_len,
                                 uint8_t * const       p_tx_buf,
                                 uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t key_num;
    uint8_t key[SIZE_OF_ENCRYPTED_KEY];
    uint8_t * p_key = key;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_crypto_key_set_req_dec(p_rx_buf, rx_buf_len, &key_num, &p_key);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_crypto_key_set(key_num, p_key);

    err_code = ant_crypto_key_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_crypto_info_set(uint8_t const * const p_rx_buf,
                                  uint32_t              rx_buf_len,
                                  uint8_t * const       p_tx_buf,
                                  uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t type;
    uint8_t info[ANT_CRYPTO_INFO_SIZE];
    uint8_t * p_info = info;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_crypto_info_set_req_dec(p_rx_buf, rx_buf_len, &type, &p_info);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_crypto_info_set(type, p_info);

    err_code = ant_crypto_info_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_crypto_info_get(uint8_t const * const p_rx_buf,
                                  uint32_t              rx_buf_len,
                                  uint8_t * const       p_tx_buf,
                                  uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t type;
    uint8_t info[ANT_CRYPTO_INFO_MAX_SIZE];
    memset(info, 0, sizeof(info));

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_crypto_info_get_req_dec(p_rx_buf, rx_buf_len, &type);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_crypto_info_get(type, info);

    err_code = ant_crypto_info_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, type, info);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_coex_config_set(uint8_t const * const p_rx_buf,
                                  uint32_t              rx_buf_len,
                                  uint8_t * const       p_tx_buf,
                                  uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint8_t coex_config_buffer[(MESG_BUFFER_SIZE / 2) - 1];
    uint8_t adv_coex_config_buffer[(MESG_BUFFER_SIZE / 2) - 1];

    ANT_BUFFER_PTR coex_config =
    {
        .ucBufferSize = 0,
        .pucBuffer = coex_config_buffer
    };

    ANT_BUFFER_PTR adv_coex_config =
    {
        .ucBufferSize = 0,
        .pucBuffer = adv_coex_config_buffer
    };

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_coex_config_set_req_dec(p_rx_buf, rx_buf_len, &channel, &coex_config, &adv_coex_config);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    if (coex_config.ucBufferSize == 0 && adv_coex_config.ucBufferSize == 0)
    {
        sd_err_code = sd_ant_coex_config_set(channel, NULL, NULL);
    }
    else if (coex_config.ucBufferSize == 0)
    {
        sd_err_code = sd_ant_coex_config_set(channel, NULL, &adv_coex_config);
    }
    else if (adv_coex_config.ucBufferSize == 0)
    {
        sd_err_code = sd_ant_coex_config_set(channel, &coex_config, NULL);
    }
    else
    {
        sd_err_code = sd_ant_coex_config_set(channel, &coex_config, &adv_coex_config);
    }

    err_code = ant_coex_config_set_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_ant_coex_config_get(uint8_t const * const p_rx_buf,
                                  uint32_t              rx_buf_len,
                                  uint8_t * const       p_tx_buf,
                                  uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint8_t channel;
    uint8_t coex_config_buffer[(MESG_BUFFER_SIZE / 2) - 1];
    uint8_t adv_coex_config_buffer[(MESG_BUFFER_SIZE / 2) - 1];

    ANT_BUFFER_PTR coex_config =
    {
        .ucBufferSize = sizeof(coex_config_buffer),
        .pucBuffer = coex_config_buffer
    };

    ANT_BUFFER_PTR adv_coex_config =
    {
        .ucBufferSize = sizeof(adv_coex_config_buffer),
        .pucBuffer = adv_coex_config_buffer
    };

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code = 0;

    err_code = ant_coex_config_get_req_dec(p_rx_buf, rx_buf_len, &channel);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ant_coex_config_get(channel, &coex_config, &adv_coex_config);

    err_code = ant_coex_config_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, &coex_config, &adv_coex_config);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}
