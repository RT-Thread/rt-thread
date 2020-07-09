/**
 * Copyright (c) 2017 - 2017, Nordic Semiconductor ASA
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

#include <stdint.h>
#include "ant_interface.h"
#include "ble_serialization.h"
#include "ant_app.h"
#include "ser_sd_transport.h"
#include "app_error.h"

static void * mp_out_params[3];

static void tx_buf_alloc(uint8_t * * p_data, uint32_t * p_len)
{
    uint32_t err_code;
    uint16_t len16;

    do
    {
        err_code = ser_sd_transport_tx_alloc(p_data, &len16);
    }
    while (err_code != NRF_SUCCESS);

    *p_data[0] = SER_PKT_TYPE_ANT_CMD;
    *p_len     = (uint32_t)len16 - 1;
}

/**@brief Command response callback function for @ref sd_ant_enable ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t enable_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ant_enable_rsp_dec(p_buffer,
                                                 length,
                                                 &result_code);

   //@note: Should never fail.

    APP_ERROR_CHECK(err_code);

    return result_code;
}

uint32_t sd_ant_enable(ANT_ENABLE * const p_ant_enable)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length;

    tx_buf_alloc(&p_buffer, &buffer_length);

    const uint32_t err_code = ant_enable_req_enc(p_ant_enable,
                                                 &(p_buffer[1]),
                                                 &buffer_length);
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      enable_rsp_dec);

}

/**@brief Command response callback function for @ref sd_ant_channel_assign ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t channel_assign_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ant_channel_assign_rsp_dec(p_buffer,
                                                         length,
                                                         &result_code);
    //@note: Should never fail.

    APP_ERROR_CHECK(err_code);

    return result_code;
}

uint32_t sd_ant_channel_assign(uint8_t channel, uint8_t channel_type, uint8_t network, uint8_t ext_assign)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length;

    tx_buf_alloc(&p_buffer, &buffer_length);

    const uint32_t err_code = ant_channel_assign_req_enc(channel,
                                                         channel_type,
                                                         network,
                                                         ext_assign,
                                                         &(p_buffer[1]),
                                                         &buffer_length);
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      channel_assign_rsp_dec);

}

/**@brief Command response callback function for @ref sd_ant_channel_open_with_offset ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t channel_open_with_offset_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ant_channel_open_with_offset_rsp_dec(p_buffer,
                                                                   length,
                                                                   &result_code);
    //@note: Should never fail.

    APP_ERROR_CHECK(err_code);

    return result_code;
}

uint32_t sd_ant_channel_open_with_offset(uint8_t channel, uint16_t usOffset)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length;

    tx_buf_alloc(&p_buffer, &buffer_length);

    const uint32_t err_code = ant_channel_open_with_offset_req_enc(channel,
                                                                   usOffset,
                                                                   &(p_buffer[1]),
                                                                   &buffer_length);
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      channel_open_with_offset_rsp_dec);

}

/**@brief Command response callback function for @ref sd_ant_channel_id_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t channel_id_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ant_channel_id_set_rsp_dec(p_buffer,
                                                         length,
                                                         &result_code);
    //@note: Should never fail.

    APP_ERROR_CHECK(err_code);

    return result_code;
}

uint32_t sd_ant_channel_id_set (uint8_t channel, uint16_t device_number, uint8_t device_type, uint8_t transmit_type)
{
    uint8_t * p_buffer;
    uint32_t  buffer_length;

    tx_buf_alloc(&p_buffer, &buffer_length);

    const uint32_t err_code = ant_channel_id_set_req_enc(channel,
                                                         device_number,
                                                         device_type,
                                                         transmit_type,
                                                         &(p_buffer[1]),
                                                         &buffer_length);
    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      channel_id_set_rsp_dec);

}

/**@brief Command response callback function for @ref sd_ant_channel_period_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t channel_period_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =  ant_channel_period_set_rsp_dec(p_buffer,
                                                              length,
                                                              &result_code);
    //@note: Should never fail.

    APP_ERROR_CHECK(err_code);

    return result_code;
}

uint32_t sd_ant_channel_period_set(uint8_t channel, uint16_t period)
{
    uint8_t * p_buffer;
    uint32_t buffer_length;

    tx_buf_alloc(&p_buffer, &buffer_length);

    const uint32_t err_code = ant_channel_period_set_req_enc(channel,
                                                             period,
                                                             &(p_buffer[1]),
                                                             &buffer_length);

    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      channel_period_set_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_channel_radio_freq_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t channel_radio_freq_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =  ant_channel_radio_freq_set_rsp_dec(p_buffer,
                                                                  length,
                                                                  &result_code);
    //@note: Should never fail.

    APP_ERROR_CHECK(err_code);

    return result_code;
}

uint32_t sd_ant_channel_radio_freq_set (uint8_t channel, uint8_t freq)
{
    uint8_t * p_buffer;
    uint32_t buffer_length;

    tx_buf_alloc(&p_buffer, &buffer_length);

    const uint32_t err_code = ant_channel_radio_freq_set_req_enc(channel,
                                                                 freq,
                                                                 &(p_buffer[1]),
                                                                 &buffer_length);

    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      channel_radio_freq_set_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_broadcast_message_tx ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t broadcast_message_tx_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =  ant_broadcast_message_tx_rsp_dec(p_buffer,
                                                                length,
                                                                &result_code);
    //@note: Should never fail.

    APP_ERROR_CHECK(err_code);

    return result_code;
}

uint32_t sd_ant_broadcast_message_tx(uint8_t channel, uint8_t size, uint8_t * p_mesg)
{
    uint8_t * p_buffer;
    uint32_t buffer_length;

    tx_buf_alloc(&p_buffer, &buffer_length);

    const uint32_t err_code = ant_broadcast_message_tx_req_enc(channel,
                                                               size,
                                                               p_mesg,
                                                               &(p_buffer[1]),
                                                               &buffer_length);

    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      broadcast_message_tx_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_acknowledge_message_tx ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t acknowledge_message_tx_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_acknowledge_message_tx_rsp_dec(p_buffer,
                                                               length,
                                                               &result_code);

  //@note: Should never fail.

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_acknowledge_message_tx(uint8_t channel, uint8_t size, uint8_t * p_mesg)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_acknowledge_message_tx_req_enc(channel,
                                                               size,
                                                               p_mesg,
                                                               &(p_buffer[1]),
                                                               &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    acknowledge_message_tx_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_channel_unassign ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t channel_unassign_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_channel_unassign_rsp_dec(p_buffer,
                                                         length,
                                                         &result_code);

  //@note: Should never fail.

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_channel_unassign(uint8_t channel)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_channel_unassign_req_enc(channel,
                                                         &(p_buffer[1]),
                                                         &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    channel_unassign_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_channel_close ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t channel_close_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_channel_close_rsp_dec(p_buffer,
                                                      length,
                                                      &result_code);

  //@note: Should never fail.

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_channel_close(uint8_t channel)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_channel_close_req_enc(channel,
                                                      &(p_buffer[1]),
                                                      &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    channel_close_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_network_address_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t network_address_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_network_address_set_rsp_dec(p_buffer,
                                                            length,
                                                            &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_network_address_set(uint8_t network, const uint8_t * p_network_key)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_network_address_set_req_enc(network,
                                                            p_network_key,
                                                            &(p_buffer[1]),
                                                            &buffer_length);

  APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    network_address_set_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_channel_radio_tx_power_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t channel_radio_tx_power_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_channel_radio_tx_power_set_rsp_dec(p_buffer,
                                                                   length,
                                                                   &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_channel_radio_tx_power_set(uint8_t channel, uint8_t tx_power, uint8_t custom_tx_power)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_channel_radio_tx_power_set_req_enc(channel,
                                                                   tx_power,
                                                                   custom_tx_power,
                                                                   &(p_buffer[1]),
                                                                   &buffer_length);

  APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    channel_radio_tx_power_set_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_channel_rx_search_timeout_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t channel_rx_search_timeout_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_channel_rx_search_timeout_set_rsp_dec(p_buffer,
                                                                      length,
                                                                      &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_channel_rx_search_timeout_set(uint8_t channel, uint8_t timeout)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_channel_rx_search_timeout_set_req_enc(channel,
                                                                      timeout,
                                                                      &(p_buffer[1]),
                                                                      &buffer_length);

  APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    channel_rx_search_timeout_set_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_channel_low_priority_rx_search_timeout_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t channel_low_priority_rx_search_timeout_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_channel_low_priority_rx_search_timeout_set_rsp_dec(p_buffer,
                                                                                   length,
                                                                                   &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_channel_low_priority_rx_search_timeout_set(uint8_t channel, uint8_t timeout)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_channel_low_priority_rx_search_timeout_set_req_enc(channel,
                                                                                   timeout,
                                                                                   &(p_buffer[1]),
                                                                                   &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    channel_low_priority_rx_search_timeout_set_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_prox_search_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t prox_search_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_prox_search_set_rsp_dec(p_buffer,
                                                        length,
                                                        &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_prox_search_set(uint8_t channel, uint8_t prox_threshold, uint8_t custom_prox_threshold)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_prox_search_set_req_enc(channel,
                                                        prox_threshold,
                                                        custom_prox_threshold,
                                                        &(p_buffer[1]),
                                                        &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    prox_search_set_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_search_waveform_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t search_waveform_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_search_waveform_set_rsp_dec(p_buffer,
                                                            length,
                                                            &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_search_waveform_set(uint8_t channel, uint16_t waveform)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_search_waveform_set_req_enc(channel,
                                                            waveform,
                                                            &(p_buffer[1]),
                                                            &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    search_waveform_set_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_channel_id_get ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t channel_id_get_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_channel_id_get_rsp_dec(p_buffer,
                                                       length,
                                                       mp_out_params[0],
                                                       mp_out_params[1],
                                                       mp_out_params[2],
                                                       &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_channel_id_get(uint8_t channel, uint16_t * p_device_number, uint8_t * p_device_type, uint8_t * p_transmit_type)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);
  mp_out_params[0] = p_device_number;
  mp_out_params[1] = p_device_type;
  mp_out_params[2] = p_transmit_type;

  const uint32_t err_code = ant_channel_id_get_req_enc(channel,
                                                       &(p_buffer[1]),
                                                       &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    channel_id_get_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_channel_radio_freq_get ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t channel_radio_freq_get_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_channel_radio_freq_get_rsp_dec(p_buffer,
                                                               length,
                                                               mp_out_params[0],
                                                               &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_channel_radio_freq_get(uint8_t channel, uint8_t * p_r_freq)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);
  mp_out_params[0] = p_r_freq;

  const uint32_t err_code = ant_channel_radio_freq_get_req_enc(channel,
                                                               &(p_buffer[1]),
                                                               &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    channel_radio_freq_get_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_channel_period_get ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t channel_period_get_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_channel_period_get_rsp_dec(p_buffer,
                                                           length,
                                                           mp_out_params[0],
                                                           &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_channel_period_get(uint8_t channel, uint16_t * p_period)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);
  mp_out_params[0] = p_period;

  const uint32_t err_code = ant_channel_period_get_req_enc(channel,
                                                           &(p_buffer[1]),
                                                           &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    channel_period_get_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_search_channel_priority_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t search_channel_priority_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_search_channel_priority_set_rsp_dec(p_buffer,
                                                                    length,
                                                                    &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_search_channel_priority_set(uint8_t channel, uint8_t search_priority)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_search_channel_priority_set_req_enc(channel,
                                                                    search_priority,
                                                                    &(p_buffer[1]),
                                                                    &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    search_channel_priority_set_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_active_search_sharing_cycles_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t active_search_sharing_cycles_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_active_search_sharing_cycles_set_rsp_dec(p_buffer,
                                                                         length,
                                                                         &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_active_search_sharing_cycles_set(uint8_t channel, uint8_t cycles)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_active_search_sharing_cycles_set_req_enc(channel,
                                                                         cycles,
                                                                         &(p_buffer[1]),
                                                                         &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    active_search_sharing_cycles_set_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_lib_config_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t lib_config_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_lib_config_set_rsp_dec(p_buffer,
                                                       length,
                                                       &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_lib_config_set(uint8_t ant_lib_config)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_lib_config_set_req_enc(ant_lib_config,
                                                       &(p_buffer[1]),
                                                       &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    lib_config_set_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_active_search_sharing_channels_get ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t active_search_sharing_cycles_get_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_active_search_sharing_cycles_get_rsp_dec(p_buffer,
                                                                         length,
                                                                         mp_out_params[0],
                                                                         &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_active_search_sharing_cycles_get(uint8_t channel, uint8_t * p_cycles)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);
  mp_out_params[0] = p_cycles;

  const uint32_t err_code = ant_active_search_sharing_cycles_get_req_enc(channel,
                                                                         &(p_buffer[1]),
                                                                         &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    active_search_sharing_cycles_get_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_lib_config_get ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t lib_config_get_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_lib_config_get_rsp_dec(p_buffer,
                                                       length,
                                                       mp_out_params[0],
                                                       &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_lib_config_get(uint8_t * p_ant_lib_config)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);
  mp_out_params[0] = p_ant_lib_config;

  const uint32_t err_code = ant_lib_config_get_req_enc(&(p_buffer[1]),
                                                       &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    lib_config_get_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_lib_config_clear ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t lib_config_clear_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_lib_config_clear_rsp_dec(p_buffer,
                                                         length,
                                                         &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_lib_config_clear(uint8_t ant_lib_config)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_lib_config_clear_req_enc(ant_lib_config,
                                                         &(p_buffer[1]),
                                                         &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    lib_config_clear_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_stack_reset ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t stack_reset_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_stack_reset_rsp_dec(p_buffer,
                                                    length,
                                                    &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_stack_reset()
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_stack_reset_req_enc(&(p_buffer[1]),
                                                    &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    stack_reset_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_rx_scan_mode_start ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t rx_scan_mode_start_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_rx_scan_mode_start_rsp_dec(p_buffer,
                                                         length,
                                                         &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_rx_scan_mode_start(uint8_t sync_channel_packets_only)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_rx_scan_mode_start_req_enc(sync_channel_packets_only,
                                                           &(p_buffer[1]),
                                                           &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    rx_scan_mode_start_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_id_list_add ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t id_list_add_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_id_list_add_rsp_dec(p_buffer,
                                                    length,
                                                    &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_id_list_add(uint8_t channel, uint8_t * p_dev_id, uint8_t list_index)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_id_list_add_req_enc(channel,
                                                    p_dev_id,
                                                    list_index,
                                                    &(p_buffer[1]),
                                                    &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    id_list_add_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_id_list_config ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t id_list_config_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_id_list_config_rsp_dec(p_buffer,
                                                       length,
                                                       &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_id_list_config(uint8_t channel, uint8_t id_list_size, uint8_t inc_exc_flag)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_id_list_config_req_enc(channel,
                                                       id_list_size,
                                                       inc_exc_flag,
                                                       &(p_buffer[1]),
                                                       &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    id_list_config_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_channel_status_get ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t channel_status_get_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_channel_status_get_rsp_dec(p_buffer,
                                                           length,
                                                           mp_out_params[0],
                                                           &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_channel_status_get(uint8_t channel, uint8_t * p_status)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);
  mp_out_params[0] = p_status;

  const uint32_t err_code = ant_channel_status_get_req_enc(channel,
                                                           &(p_buffer[1]),
                                                           &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    channel_status_get_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_cw_test_mode_init ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t cw_test_mode_init_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_cw_test_mode_init_rsp_dec(p_buffer,
                                                          length,
                                                          &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_cw_test_mode_init()
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_cw_test_mode_init_req_enc(&(p_buffer[1]),
                                                          &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    cw_test_mode_init_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_cw_test_mode ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t cw_test_mode_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_cw_test_mode_rsp_dec(p_buffer,
                                                     length,
                                                     &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_cw_test_mode(uint8_t radio_freq, uint8_t tx_power, uint8_t custom_tx_power, uint8_t mode)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);

  const uint32_t err_code = ant_cw_test_mode_req_enc(radio_freq,
                                                     tx_power,
                                                     custom_tx_power,
                                                     mode,
                                                     &(p_buffer[1]),
                                                     &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    cw_test_mode_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_version_get ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t version_get_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_version_get_rsp_dec(p_buffer,
                                                    length,
                                                    &mp_out_params[0],
                                                    &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_version_get(uint8_t * p_version)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);
  mp_out_params[0] = p_version;

  const uint32_t err_code = ant_version_get_req_enc(&(p_buffer[1]),
                                                    &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    version_get_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_capabilities_get ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t capabilities_get_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_capabilities_get_rsp_dec(p_buffer,
                                                         length,
                                                         &mp_out_params[0],
                                                         &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_capabilities_get(uint8_t * p_capabilities)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);
  mp_out_params[0] = p_capabilities;

  const uint32_t err_code = ant_capabilities_get_req_enc(&(p_buffer[1]),
                                                         &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    capabilities_get_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_crypto_channel_enable ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t crypto_channel_enable_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =  ant_crypto_channel_enable_rsp_dec(p_buffer,
                                                                 length,
                                                                 &result_code);
    //@note: Should never fail.

    APP_ERROR_CHECK(err_code);

    return result_code;
}

uint32_t sd_ant_crypto_channel_enable(uint8_t channel, uint8_t enable, uint8_t key_num, uint8_t decimation_rate)
{
    uint8_t * p_buffer;
    uint32_t buffer_length;

    tx_buf_alloc(&p_buffer, &buffer_length);

    const uint32_t err_code = ant_crypto_channel_enable_req_enc(channel,
                                                                enable,
                                                                key_num,
                                                                decimation_rate,
                                                                &(p_buffer[1]),
                                                                &buffer_length);

    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      crypto_channel_enable_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_adv_burst_config_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t adv_burst_config_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =  ant_adv_burst_config_set_rsp_dec(p_buffer,
                                                                length,
                                                                &result_code);
    //@note: Should never fail.
    APP_ERROR_CHECK(err_code);

    return result_code;
}

uint32_t sd_ant_adv_burst_config_set(uint8_t * p_config, uint8_t size)
{
    uint8_t * p_buffer;
    uint32_t buffer_length;

    tx_buf_alloc(&p_buffer, &buffer_length);

    const uint32_t err_code = ant_adv_burst_config_set_req_enc(p_config,
                                                               size,
                                                               &(p_buffer[1]),
                                                               &buffer_length);

    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      adv_burst_config_set_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_crypto_key_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t crypto_key_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =  ant_crypto_key_set_rsp_dec(p_buffer,
                                                          length,
                                                          &result_code);
    //@note: Should never fail.
    APP_ERROR_CHECK(err_code);

    return result_code;
}

uint32_t sd_ant_crypto_key_set(uint8_t key_num, uint8_t * p_key)
{
    uint8_t * p_buffer;
    uint32_t buffer_length;

    tx_buf_alloc(&p_buffer, &buffer_length);

    const uint32_t err_code = ant_crypto_key_set_req_enc(key_num,
                                                         p_key,
                                                         &(p_buffer[1]),
                                                         &buffer_length);

    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      crypto_key_set_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_crypto_info_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t crypto_info_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =  ant_crypto_info_set_rsp_dec(p_buffer,
                                                           length,
                                                           &result_code);
    //@note: Should never fail.
    APP_ERROR_CHECK(err_code);

    return result_code;
}

uint32_t sd_ant_crypto_info_set(uint8_t type, uint8_t * p_info)
{
    uint8_t * p_buffer;
    uint32_t buffer_length;

    tx_buf_alloc(&p_buffer, &buffer_length);

    const uint32_t err_code = ant_crypto_info_set_req_enc(type,
                                                          p_info,
                                                          &(p_buffer[1]),
                                                          &buffer_length);

    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      crypto_info_set_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_crypto_info_get ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t crypto_info_get_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =  ant_crypto_info_get_rsp_dec(p_buffer,
                                                           length,
                                                           mp_out_params[0],
                                                           &result_code);
    //@note: Should never fail.
    APP_ERROR_CHECK(err_code);

    return result_code;
}

uint32_t sd_ant_crypto_info_get(uint8_t type, uint8_t * p_info)
{
    uint8_t * p_buffer;
    uint32_t buffer_length;

    tx_buf_alloc(&p_buffer, &buffer_length);
    mp_out_params[0] = p_info;

    const uint32_t err_code = ant_crypto_info_get_req_enc(type,
                                                          &(p_buffer[1]),
                                                          &buffer_length);

    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      crypto_info_get_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_coex_config_set ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t coex_config_set_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code =  ant_coex_config_set_rsp_dec(p_buffer,
                                                           length,
                                                           &result_code);
    //@note: Should never fail.
    APP_ERROR_CHECK(err_code);

    return result_code;
}

uint32_t sd_ant_coex_config_set(uint8_t channel, ANT_BUFFER_PTR * p_coex_config, ANT_BUFFER_PTR * p_adv_coex_config)
{
    uint8_t * p_buffer;
    uint32_t buffer_length;

    tx_buf_alloc(&p_buffer, &buffer_length);

    const uint32_t err_code = ant_coex_config_set_req_enc(channel,
                                                          p_coex_config,
                                                          p_adv_coex_config,
                                                          &(p_buffer[1]),
                                                          &buffer_length);

    APP_ERROR_CHECK(err_code);

    //@note: Increment buffer length as internally managed packet type field must be included.
    return ser_sd_transport_cmd_write(p_buffer,
                                      (++buffer_length),
                                      coex_config_set_rsp_dec);
}

/**@brief Command response callback function for @ref sd_ant_coex_config_get ANT command.
 *
 * Callback for decoding the output parameters and the command response return code.
 *
 * @param[in] p_buffer  Pointer to begin of command response buffer.
 * @param[in] length    Length of data in bytes.
 *
 * @return Decoded command response return code.
 */
static uint32_t coex_config_get_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
  uint32_t result_code;

  const uint32_t err_code = ant_coex_config_get_rsp_dec(p_buffer,
                                                        length,
                                                        mp_out_params[0],
                                                        mp_out_params[1],
                                                        &result_code);

  //@note: Should never fail

  APP_ERROR_CHECK(err_code);

  return result_code;
}

uint32_t sd_ant_coex_config_get(uint8_t channel, ANT_BUFFER_PTR * p_coex_config, ANT_BUFFER_PTR * p_adv_coex_config)
{
  uint8_t * p_buffer;
  uint32_t buffer_length;

  tx_buf_alloc(&p_buffer, &buffer_length);
  mp_out_params[0] = p_coex_config;
  mp_out_params[1] = p_adv_coex_config;

  const uint32_t err_code = ant_coex_config_get_req_enc(channel,
                                                        &(p_buffer[1]),
                                                        &buffer_length);

  APP_ERROR_CHECK(err_code);

  //@note: Increment buffer length as internally managed packet type field must be included.
  return ser_sd_transport_cmd_write(p_buffer,
                                    (++buffer_length),
                                    coex_config_get_rsp_dec);
}
