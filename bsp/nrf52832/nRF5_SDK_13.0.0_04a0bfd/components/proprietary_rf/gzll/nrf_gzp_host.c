/**
 * Copyright (c) 2009 - 2017, Nordic Semiconductor ASA
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
/**
 * @file
 * @brief Implementation of Gazell Pairing Library (gzp), Host functions.
 * @defgroup gzp_source_host Gazell Pairing Host implementation
 * @{
 * @ingroup gzp_04_source
 */


#include "nrf_gzp.h"
#include "nrf_gzll.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "nrf_assert.h"
#include "nrf_ecb.h"
#include "nrf_nvmc.h"


//lint -esym(40, GZP_PARAMS_STORAGE_ADR) "Undeclared identifier"


/******************************************************************************/
/** @name Typedefs
 *  @{ */
/******************************************************************************/

/**
 * Definition of internal states.
 */
typedef enum
{
  GZP_ID_REQ_IDLE,                 ///< No Host ID request received from Device.
  GZP_ID_REQ_PENDING,              ///< Host ID request received and waiting on application to grant/reject.
  GZP_ID_REQ_PENDING_AND_GRANTED,  ///< Host ID request received and granted by application.
  GZP_ID_REQ_PENDING_AND_REJECTED, ///< Host ID request received and rejected by application.
} gzp_id_req_stat_t;

/** @} */


/******************************************************************************/
/** @name Internal (static) function prototypes
 *  @{ */
/******************************************************************************/


/**
 * Function for incrementing internal session counter.
 */
static void gzp_session_counter_inc(void);


/**
 * Function for reading value of internal session counter.
 * @param dst   Current session counter.
 */
static void gzp_get_session_counter(uint8_t* dst);


/**
 * Function processing received "system address request" from Device.
 *
 * @param gzp_req  Pointer to RX payload containing system address request.
 */
static void gzp_process_address_req(uint8_t* gzp_req);


/**
 * Function to process Host ID request from device.
 *
 * The Host shall retrieve the Host ID from NVM, or shall generate if
 * it does not yet exist.
 *
 * @param rx_payload Pointer to rx_payload contaning Host ID request.
 */
static void gzp_process_id_req(uint8_t* rx_payload);

/**
 * Function to process Host ID fetch request from Device.
 *
 * The Device fetches the Host ID after the Host has generated/retrieved
 * the Host ID.
 *
 * @param rx_payload Pointer to rx_payload contaning Host ID fetch request.
 */
static void gzp_process_id_fetch(uint8_t* rx_payload);


/**
 * Function to process Key Update Prepare packet.
 *
 * Device requests the Session Token to be used for the Key Update request.
 */
static void gzp_process_key_update_prepare(void);


/**
 * Function to process Key Update packet.
 *
 * Device requests a Key Update and sends a new Dynamic Key. The Dynamic Key is
 * updated on the Host.
 *
 * @param rx_payload Pointer to rx_payload containing Key Update request.
 */
static void gzp_process_key_update(uint8_t* rx_payload);


/**
 * Function to process received Encrypted User packet.
 *
 * @param rx_payload Pointer to rx_payload containing the encrypted user data.
 * @param length     Length of encrypted user data.
 */
static void gzp_process_encrypted_user_data(uint8_t* rx_payload, uint8_t length);


/**
 * Function to preload the payload for the next ACK.
 *
 * @param src       Pointer to source payload.
 * @param length    Length of source payload.
 * @param pipe      Pipe for the ACK payload.
 */
static void gzp_preload_ack(uint8_t* src, uint8_t length, uint8_t pipe);


/**
 * Function for reading the Chip ID from non-volatile memory.
 *
 * The chip ID is used for the system address.
 *
 * If the Chip ID is not yet created a random Chip ID is created and
 * written to non-volatile memory. Note that the term chip ID is used as
 * the factory programmed chip sequence number was used for the system
 * address in nRF24LU ICs.
 *
 * @param     dst  Address to copy Host ID to.
 * @param[in] n    Number of bytes in the Host ID.
 */
void gzp_host_chip_id_read(uint8_t *dst, uint8_t n);


/**
 * Function to set the Host ID.
 *
 * Writes the Host ID to non-volatile memory.
 * @param src   Address of the Host ID to copy from.
 */
static void gzp_set_host_id(const uint8_t* src);


/**
 * Function to request disabling of Gazell and wait for it to be disabled.
 *
 * Emulates legacy gzll_goto_idle().
 */
static void gzll_goto_idle(void);


/**
 * Flush all TX FIFOs.
 *
 * Emulates legacy gzll_tx_fifo_flush().
 */
static void gzll_tx_fifo_flush(void);


/**
 * Flush all RX FIFOs.
 *
 * Emulates legacy gzll_rx_fifo_flush().
 */
static void gzll_rx_fifo_flush(void);


/**
 * Set a timeout for the reception of packets on the Gazell Host.
 *
 * Emulates legacy Gazell function: gzll_set_param(GZLL_PARAM_RX_TIMEOUT, x).
 *
 * @param timeout   Timeout in number of legacy "RX periods"
 *                 (1 RX period = 2 timeslot periods).
 */
static void gzll_set_rx_timeout(uint32_t timeout);

/** @} */


/******************************************************************************/
/** @name Internal (static) variabls
 *  @{ */
/******************************************************************************/

static gzp_id_req_stat_t gzp_id_req_stat; ///< Current state of Host ID request.
static bool gzp_pairing_enabled_f;        ///< True if Host is paired with a device.
static bool gzp_address_exchanged_f;      ///< True if Host has exchanged a system address with a device and thus pairing has begun.

static uint8_t gzp_session_counter[GZP_SESSION_TOKEN_LENGTH]; ///< Session counter used for key generation and update.

static bool gzp_encrypted_user_data[GZP_ENCRYPTED_USER_DATA_MAX_LENGTH]; ///< Placeholder for encrypted data from Device.
static uint8_t gzp_encrypted_user_data_length;                           ///< Length of gzp_encrypted_user_data. Zero implies no data received.

static nrf_gzll_host_rx_info_t prev_gzp_rx_info = {0, 0};                ///< RSSI and status of ACK payload transmission of previous Gazell packet.

/** @} */


/******************************************************************************/
// Implementation: Host-specific API functions
/******************************************************************************/

void gzp_init()
{
  uint8_t system_address[GZP_SYSTEM_ADDRESS_WIDTH];

  // Read "chip id", of which 4 bytes (GZP_SYSTEM_ADDRESS_WIDTH)
  // are used as system address
  gzp_host_chip_id_read(system_address, GZP_SYSTEM_ADDRESS_WIDTH);

  // Set up radio parameters (addresses and channel subset) from system_address
  (void)gzp_update_radio_params(system_address);

  // Only "data pipe" enabled by default

  (void)nrf_gzll_set_rx_pipes_enabled(nrf_gzll_get_rx_pipes_enabled() | (1 << GZP_DATA_PIPE));

  gzp_pairing_enabled_f = false;
  gzp_address_exchanged_f = false;
  gzp_id_req_stat = GZP_ID_REQ_IDLE;
  gzp_encrypted_user_data_length = 0;

  // Infinite RX timeout
  gzll_set_rx_timeout(0);
}

void gzp_pairing_enable(bool enable)
{
  if (gzp_pairing_enabled_f != enable)
  {
    gzll_goto_idle();

    if (enable)
    {
        (void)nrf_gzll_set_rx_pipes_enabled(nrf_gzll_get_rx_pipes_enabled() | (1 << GZP_PAIRING_PIPE));
    }
    else
    {
        (void)nrf_gzll_set_rx_pipes_enabled(nrf_gzll_get_rx_pipes_enabled() & ~(1 << GZP_PAIRING_PIPE));

        gzp_id_req_stat = GZP_ID_REQ_IDLE;
    }

    gzp_pairing_enabled_f = enable;

    gzll_rx_start();
  }
}

void gzp_host_execute()
{
  bool gzp_packet_received = false;
  uint32_t payload_length = NRF_GZLL_CONST_MAX_PAYLOAD_LENGTH;
  uint8_t rx_payload[NRF_GZLL_CONST_MAX_PAYLOAD_LENGTH];

  gzp_address_exchanged_f = false;

  if (nrf_gzll_get_rx_fifo_packet_count(GZP_PAIRING_PIPE) > 0)
  {
    gzp_packet_received = nrf_gzll_fetch_packet_from_rx_fifo(GZP_PAIRING_PIPE, rx_payload, &payload_length);
  }

  if (!gzp_packet_received && (gzp_encrypted_user_data_length == 0))
  {
    if (nrf_gzll_get_rx_fifo_packet_count(GZP_DATA_PIPE) > 0)
    {
      gzp_packet_received = nrf_gzll_fetch_packet_from_rx_fifo(GZP_DATA_PIPE, rx_payload, &payload_length);
    }
  }

  if (gzp_packet_received)
  {
    //lint -save -esym(644,rx_payload) //may not have been initialized
    switch (rx_payload[0])
    {
      case GZP_CMD_HOST_ADDRESS_REQ:
        gzp_process_address_req(rx_payload);
        break;

      #ifndef GZP_CRYPT_DISABLE

      case GZP_CMD_HOST_ID_REQ:
        gzp_process_id_req(rx_payload);
        break;
      case GZP_CMD_HOST_ID_FETCH:
        gzp_process_id_fetch(rx_payload);
        break;
      case GZP_CMD_KEY_UPDATE_PREPARE:
        gzp_process_key_update_prepare();
        break;
      case GZP_CMD_KEY_UPDATE:
        gzp_process_key_update(rx_payload);
        break;
      case GZP_CMD_ENCRYPTED_USER_DATA:
        gzp_process_encrypted_user_data(rx_payload, payload_length);
        break;

      #endif

      case GZP_CMD_FETCH_RESP:
      default:
        break;
    }
  }

  // Restart reception if "not proximity backoff" period has elapsed
  if (!nrf_gzll_is_enabled())
  {
    gzll_set_rx_timeout(0);

    if (gzp_pairing_enabled_f)
    {
      (void)nrf_gzll_set_rx_pipes_enabled(nrf_gzll_get_rx_pipes_enabled() | (1 << GZP_PAIRING_PIPE));
    }

    gzll_rx_start();
  }

  #ifndef GZP_CRYPT_DISABLE
  gzp_session_counter_inc();
  #endif
}

void gzll_rx_start(void)
{
  if (nrf_gzll_get_mode() != NRF_GZLL_MODE_HOST)
  {
    gzll_goto_idle();
    (void)nrf_gzll_set_mode(NRF_GZLL_MODE_HOST);
  }

  if (!nrf_gzll_is_enabled())
  {
    (void)nrf_gzll_enable();
  }
}

bool gzp_id_req_received()
{
  return (gzp_id_req_stat != GZP_ID_REQ_IDLE);
}

void gzp_id_req_reject()
{
  if (gzp_id_req_received())
  {
    gzp_id_req_stat = GZP_ID_REQ_PENDING_AND_REJECTED;
  }
}

void gzp_id_req_grant()
{
  if (gzp_id_req_received())
  {
    gzp_id_req_stat = GZP_ID_REQ_PENDING_AND_GRANTED;
  }
}

void gzp_id_req_cancel()
{
  if (gzp_id_req_received())
  {
    gzp_id_req_stat = GZP_ID_REQ_IDLE;
  }
}

//-----------------------------------------------------------------------------
// Implementation: Static functions
//-----------------------------------------------------------------------------

static void gzp_process_address_req(uint8_t* gzp_req)
{
  uint8_t temp_rx_pipes;
  uint8_t pairing_resp[GZP_CMD_HOST_ADDRESS_RESP_PAYLOAD_LENGTH];
  uint32_t rx_payload_length = NRF_GZLL_CONST_MAX_PAYLOAD_LENGTH;

  gzp_address_exchanged_f = false;

  gzll_goto_idle();
  ASSERT(nrf_gzll_get_error_code() == NRF_GZLL_ERROR_CODE_NO_ERROR);

  temp_rx_pipes = nrf_gzll_get_rx_pipes_enabled();
  ASSERT(nrf_gzll_get_error_code() == NRF_GZLL_ERROR_CODE_NO_ERROR);

  // If requesting Device within close proximity
  if (prev_gzp_rx_info.rssi >= GZP_HOST_RX_POWER_THRESHOLD)
  {
    (void)nrf_gzll_set_rx_pipes_enabled(0);
    ASSERT(nrf_gzll_get_error_code() == NRF_GZLL_ERROR_CODE_NO_ERROR);

      gzll_set_rx_timeout(GZP_CLOSE_PROXIMITY_BACKOFF_RX_TIMEOUT);
    ASSERT(nrf_gzll_get_error_code() == NRF_GZLL_ERROR_CODE_NO_ERROR);

    gzll_rx_fifo_flush();
    ASSERT(nrf_gzll_get_error_code() == NRF_GZLL_ERROR_CODE_NO_ERROR);

    // Start "proximity" back off period
    gzll_rx_start();
    ASSERT(nrf_gzll_get_error_code() == NRF_GZLL_ERROR_CODE_NO_ERROR);

    while (nrf_gzll_is_enabled())
    {}

    // Build pairing response packet
    pairing_resp[0] = (uint8_t)GZP_CMD_HOST_ADDRESS_RESP;
    gzp_host_chip_id_read(&pairing_resp[GZP_CMD_HOST_ADDRESS_RESP_ADDRESS], GZP_SYSTEM_ADDRESS_WIDTH);

    (void)nrf_gzll_add_packet_to_tx_fifo(0, &pairing_resp[0], GZP_CMD_HOST_ADDRESS_RESP_PAYLOAD_LENGTH);
    ASSERT(nrf_gzll_get_error_code() == NRF_GZLL_ERROR_CODE_NO_ERROR);
    gzll_set_rx_timeout(GZP_STEP1_RX_TIMEOUT);

    // Enable only pairing pipe when waiting for pairing request step 1
    (void)nrf_gzll_set_rx_pipes_enabled((1 << GZP_PAIRING_PIPE));

    gzll_rx_start();

    while (nrf_gzll_is_enabled())
    {
      if (nrf_gzll_get_rx_fifo_packet_count(GZP_PAIRING_PIPE))
      {
        (void)nrf_gzll_fetch_packet_from_rx_fifo(GZP_PAIRING_PIPE, &gzp_req[0], &rx_payload_length);

        // Validate step 1 of pairing request
        if (gzp_req[0] == (uint8_t)GZP_CMD_HOST_ADDRESS_FETCH)
        {
          gzp_address_exchanged_f = true;
        }
      }
    }

    gzll_tx_fifo_flush();
    gzll_rx_fifo_flush();

    gzll_set_rx_timeout(0);

    (void)nrf_gzll_set_rx_pipes_enabled(temp_rx_pipes);

    // Return to normal operation
    gzll_rx_start();
  }
  else
  {
    (void)nrf_gzll_set_rx_pipes_enabled(temp_rx_pipes & ~(1 << GZP_PAIRING_PIPE));

    gzll_set_rx_timeout(GZP_NOT_PROXIMITY_BACKOFF_RX_TIMEOUT);

    // Start "not proximity" backoff period
    gzll_rx_start();
  }
}

static void gzp_preload_ack(uint8_t* src, uint8_t length, uint8_t pipe)
{
  gzll_goto_idle();

  gzll_tx_fifo_flush();

  (void)nrf_gzll_add_packet_to_tx_fifo(pipe, src, length);

  gzll_rx_start();
}

static void gzll_set_rx_timeout(uint32_t timeout)
{
    timeout *= 2; // * 2 as gzll_set_rx_timeout() takes RX_PERIODS as input, which equals 2 timeslots.
    nrf_gzll_set_auto_disable(timeout);
}

bool gzp_address_exchanged()
{
  return gzp_address_exchanged_f;
}

#ifndef GZP_CRYPT_DISABLE

bool gzp_crypt_user_data_received()
{
  return (gzp_encrypted_user_data_length > 0);
}

bool gzp_crypt_user_data_read(uint8_t* dst, uint8_t* length)
{
  if (gzp_encrypted_user_data_length > 0)
  {
    memcpy(dst, (void*)gzp_encrypted_user_data, gzp_encrypted_user_data_length);

    if (length != NULL)
    {
      *length = gzp_encrypted_user_data_length;
    }
    gzp_encrypted_user_data_length = 0;

    return true;
  }
  else
  {
    return false;
  }
}

static void gzp_session_counter_inc()
{
  uint8_t i;

  for (i = 0; i < GZP_SESSION_TOKEN_LENGTH; i++)
  {
    gzp_session_counter[i]++;
    if (gzp_session_counter[i] != 0)
    {
      break;
    }
  }
}

static void gzp_get_session_counter(uint8_t* dst)
{
  memcpy(dst, (void*)gzp_session_counter, GZP_SESSION_TOKEN_LENGTH);
}

static void gzp_set_host_id(const uint8_t* src)
{
  if (*((uint8_t*)GZP_PARAMS_STORAGE_ADR) == 0xff)
  {
    nrf_nvmc_write_bytes(GZP_PARAMS_STORAGE_ADR + 1, src, GZP_HOST_ID_LENGTH);
    nrf_nvmc_write_byte(GZP_PARAMS_STORAGE_ADR, 0x00);
  }
}

void gzp_get_host_id(uint8_t *dst)
{
  memcpy(dst, (uint8_t*)GZP_PARAMS_STORAGE_ADR + 1, GZP_HOST_ID_LENGTH);
}

static void gzp_process_id_req(uint8_t* rx_payload)
{
  int i;
  uint8_t temp_host_id[GZP_HOST_ID_LENGTH];

  if (gzp_pairing_enabled_f)
  {
    if (!gzp_id_req_received())
    {
      gzp_crypt_set_session_token(&rx_payload[GZP_CMD_HOST_ID_REQ_SESSION_TOKEN]);
      gzp_id_req_stat = GZP_ID_REQ_PENDING;
    }

    gzp_get_host_id(temp_host_id);

    // Added:
    for (i = 0; i < GZP_HOST_ID_LENGTH; i++)
    {
      if (temp_host_id[i] != 0xFF)
      {
        break;
      }
    }

    if (i == GZP_HOST_ID_LENGTH) // If host not generated yet
    {
      gzp_get_session_counter(temp_host_id);

#if (GZP_HOST_ID_LENGTH > GZP_SESSION_TOKEN_LENGTH)
      gzp_xor_cipher(temp_host_id, temp_host_id, &rx_payload[GZP_CMD_HOST_ID_REQ_SESSION_TOKEN], GZP_SESSION_TOKEN_LENGTH);
#else //(GZP_HOST_ID_LENGTH > GZP_SESSION_TOKEN_LENGTH)
      gzp_xor_cipher(temp_host_id, temp_host_id, &rx_payload[GZP_CMD_HOST_ID_REQ_SESSION_TOKEN], GZP_HOST_ID_LENGTH);
#endif //(GZP_HOST_ID_LENGTH > GZP_SESSION_TOKEN_LENGTH)

      gzp_set_host_id(temp_host_id);
    }
  }
}

static void gzp_process_id_fetch(uint8_t* rx_payload)
{
  uint8_t tx_payload[GZP_CMD_HOST_ID_FETCH_RESP_PAYLOAD_LENGTH];

  if (gzp_id_req_received())
  {
    gzp_crypt_select_key(GZP_ID_EXCHANGE);
    gzp_crypt(&rx_payload[1], &rx_payload[1], GZP_CMD_HOST_ID_FETCH_PAYLOAD_LENGTH - 1);
    if (gzp_validate_id(&rx_payload[GZP_CMD_HOST_ID_FETCH_VALIDATION_ID]))
    {
      switch (gzp_id_req_stat)
      {
        case GZP_ID_REQ_PENDING_AND_GRANTED:
          tx_payload[GZP_CMD_HOST_ID_FETCH_RESP_STATUS] = (uint8_t)GZP_ID_RESP_GRANTED;
          gzp_get_host_id(&tx_payload[GZP_CMD_HOST_ID_FETCH_RESP_HOST_ID]);
          gzp_id_req_stat = GZP_ID_REQ_IDLE;
          break;
        case GZP_ID_REQ_PENDING_AND_REJECTED:
          tx_payload[GZP_CMD_HOST_ID_FETCH_RESP_STATUS] = (uint8_t)GZP_ID_RESP_REJECTED;
          gzp_id_req_stat = GZP_ID_REQ_IDLE;
          break;
        case GZP_ID_REQ_PENDING:
        default:
          tx_payload[GZP_CMD_HOST_ID_FETCH_RESP_STATUS] = (uint8_t)GZP_ID_RESP_PENDING;
          break;
      }

      tx_payload[0] = (uint8_t)GZP_CMD_HOST_ID_FETCH_RESP;
      gzp_add_validation_id(&tx_payload[GZP_CMD_HOST_ID_FETCH_RESP_VALIDATION_ID]);
      gzp_crypt(&tx_payload[1], &tx_payload[1], GZP_CMD_HOST_ID_FETCH_RESP_PAYLOAD_LENGTH - 1);

      ASSERT(nrf_gzll_get_error_code() == NRF_GZLL_ERROR_CODE_NO_ERROR);
      gzp_preload_ack(tx_payload, GZP_CMD_HOST_ID_FETCH_RESP_PAYLOAD_LENGTH, GZP_DATA_PIPE);
      ASSERT(nrf_gzll_get_error_code() == NRF_GZLL_ERROR_CODE_NO_ERROR);
    }
  }
}

static void gzp_process_key_update_prepare()
{
  uint8_t tx_payload[GZP_CMD_KEY_UPDATE_PREPARE_RESP_PAYLOAD_LENGTH];

  tx_payload[0] = (uint8_t)GZP_CMD_KEY_UPDATE_PREPARE_RESP;

  gzp_get_session_counter(&tx_payload[GZP_CMD_KEY_UPDATE_PREPARE_RESP_SESSION_TOKEN]);

  // Update session token if no ID request is pending
  if (!gzp_id_req_received())
  {
    gzp_crypt_set_session_token(&tx_payload[GZP_CMD_KEY_UPDATE_PREPARE_RESP_SESSION_TOKEN]);
  }

  gzp_preload_ack(tx_payload, GZP_CMD_KEY_UPDATE_PREPARE_RESP_PAYLOAD_LENGTH, GZP_DATA_PIPE);
  ASSERT(nrf_gzll_get_error_code() == NRF_GZLL_ERROR_CODE_NO_ERROR);
}

static void gzp_process_key_update(uint8_t* rx_payload)
{
  gzp_crypt_select_key(GZP_KEY_EXCHANGE);
  gzp_crypt(&rx_payload[1], &rx_payload[1], GZP_CMD_KEY_UPDATE_PAYLOAD_LENGTH - 1);
  if (gzp_validate_id(&rx_payload[GZP_CMD_KEY_UPDATE_VALIDATION_ID]))
  {
    gzp_crypt_set_dyn_key(&rx_payload[GZP_CMD_KEY_UPDATE_NEW_KEY]);
  }
}

static void gzp_process_encrypted_user_data(uint8_t* rx_payload, uint8_t length)
{
  uint8_t tx_payload[GZP_CMD_ENCRYPTED_USER_DATA_RESP_PAYLOAD_LENGTH];

  if (gzp_id_req_received())
  {
    gzp_crypt_select_key(GZP_ID_EXCHANGE);
  }
  else
  {
    gzp_crypt_select_key(GZP_DATA_EXCHANGE);
  }

  gzp_crypt(&rx_payload[1], &rx_payload[1], length - 1);
  if (gzp_validate_id(&rx_payload[GZP_CMD_ENCRYPTED_USER_DATA_VALIDATION_ID]))
  {
    gzp_encrypted_user_data_length = length - GZP_ENCRYPTED_USER_DATA_PACKET_OVERHEAD;
    memcpy((void*)gzp_encrypted_user_data, &rx_payload[GZP_CMD_ENCRYPTED_USER_DATA_PAYLOAD], gzp_encrypted_user_data_length);
  }

  // Build response packet
  tx_payload[0] = (uint8_t)GZP_CMD_ENCRYPTED_USER_DATA_RESP;
  gzp_add_validation_id(&tx_payload[GZP_CMD_ENCRYPTED_USER_DATA_RESP_VALIDATION_ID]);
  gzp_crypt(&tx_payload[GZP_CMD_ENCRYPTED_USER_DATA_RESP_VALIDATION_ID], &tx_payload[GZP_CMD_ENCRYPTED_USER_DATA_RESP_VALIDATION_ID], GZP_VALIDATION_ID_LENGTH);
  gzp_get_session_counter(&tx_payload[GZP_CMD_ENCRYPTED_USER_DATA_RESP_SESSION_TOKEN]);

  // Update "session token" only if no ID request is pending
  if (!gzp_id_req_received())
  {
    gzp_crypt_set_session_token(&tx_payload[GZP_CMD_ENCRYPTED_USER_DATA_RESP_SESSION_TOKEN]);
  }

  ASSERT(nrf_gzll_get_error_code() == NRF_GZLL_ERROR_CODE_NO_ERROR);
  gzp_preload_ack(tx_payload, GZP_CMD_ENCRYPTED_USER_DATA_RESP_PAYLOAD_LENGTH, GZP_DATA_PIPE);
  ASSERT(nrf_gzll_get_error_code() == NRF_GZLL_ERROR_CODE_NO_ERROR);
}

//-----------------------------------------------------------------------------
// Function added during LE1 -> nRF51 port
//-----------------------------------------------------------------------------

static void gzll_goto_idle()
{
  nrf_gzll_disable();
  while (nrf_gzll_is_enabled())
  {}
}

static void gzll_tx_fifo_flush(void)
{
  int i;

  for (i = 0; i < NRF_GZLL_CONST_PIPE_COUNT; i++)
  {
    (void)nrf_gzll_flush_tx_fifo(i);
  }
}

static void gzll_rx_fifo_flush(void)
{
  int i;

  for (i = 0; i < NRF_GZLL_CONST_PIPE_COUNT; i++)
  {
    (void)nrf_gzll_flush_rx_fifo(i);
  }
}


/******************************************************************************/
// Implementation: Gazell callback functions
/******************************************************************************/

void nrf_gzll_device_tx_failed(uint32_t pipe, nrf_gzll_device_tx_info_t tx_info)
{
}


void nrf_gzll_device_tx_success(uint32_t pipe, nrf_gzll_device_tx_info_t tx_info)
{
}


void nrf_gzll_disabled(void)
{
}


void nrf_gzll_host_rx_data_ready(uint32_t pipe, nrf_gzll_host_rx_info_t rx_info)
{
    if (pipe == GZP_PAIRING_PIPE)
    {
        prev_gzp_rx_info = rx_info;
    }
}

/** @} */
/** @} */

#endif
