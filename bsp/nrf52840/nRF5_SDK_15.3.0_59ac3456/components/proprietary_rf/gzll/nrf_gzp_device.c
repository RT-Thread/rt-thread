/**
 * Copyright (c) 2009 - 2019, Nordic Semiconductor ASA
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
 * @brief Implementation of Gazell Pairing Library (gzp), Device functions.
 * @defgroup gzp_source_device Gazell Pairing Device implementation.
 * @{
 * @ingroup gzp_04_source
 */


#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "nrf_gzll.h"
#include "nrf_gzp.h"
#include "nrf_delay.h"
#include "nrf_nvmc.h"

#define SOURCE_FILE NRF_SOURCE_FILE_GZP_DEVICE    ///< File identifer for asserts.

/******************************************************************************/
/** @name Misc. defines
 *  @{ */
/******************************************************************************/

#define GZP_PARAMS_DB_ELEMENT_SYSTEM_ADDRESS 0 ///< System address position.
#define GZP_PARAMS_DB_ELEMENT_HOST_ID (GZP_PARAMS_DB_ELEMENT_SYSTEM_ADDRESS + GZP_SYSTEM_ADDRESS_WIDTH) ///< Host ID position
#define GZP_PARAMS_DB_ELEMENT_SIZE (GZP_SYSTEM_ADDRESS_WIDTH + GZP_HOST_ID_LENGTH)///< Total size
#define GZP_PARAMS_DB_MAX_ENTRIES 14            ///<  Maximum allowed entries in the database.

/** @} */

/******************************************************************************/
/** @name Derived parameters
 *  @{ */
/******************************************************************************/

//lint -esym(40, GZP_PARAMS_STORAGE_ADR) "Undeclare identifier"
#define GZP_PARAMS_DB_ADR GZP_PARAMS_STORAGE_ADR                                    ///<
#define GZP_PARAMS_DB_SIZE (GZP_PARAMS_DB_MAX_ENTRIES * GZP_PARAMS_DB_ELEMENT_SIZE) ///<

#define GZP_INDEX_DB_ADR (GZP_PARAMS_STORAGE_ADR + GZP_PARAMS_DB_SIZE)             ///<
#define GZP_INDEX_DB_SIZE (GZP_DEVICE_PARAMS_STORAGE_SIZE - GZP_PARAMS_DB_SIZE)    ///<

#if (GZP_DEVICE_PARAMS_STORAGE_SIZE < GZP_PARAMS_DB_SIZE)
  #error GZP_DEVICE_PARAMS_STORAGE_SIZE must be greater or equal to GZP_PAIRING_PARAMS_DB_SIZE
#elif (GZP_DEVICE_PARAMS_STORAGE_SIZE == GZP_PARAMS_DB_SIZE )
  #warning GZP_DEVICE_PARAMS_STORAGE_SIZE to low to be able store any pairing parameters NV memory
#endif
/** @} */


/******************************************************************************/
/** @name Typedefs
 *  @{ */
/******************************************************************************/


/**
 * Possible return values for the function gzp_tx_rx_transaction()
 */
typedef enum
{
    GZP_TX_RX_SUCCESS,         ///< ACK received. Transaction successful.
    GZP_TX_RX_FAILED_TO_SEND,  ///<
    GZP_TX_RX_NO_RESPONSE      ///<
} gzp_tx_rx_trans_result_t;
/** @} */


/******************************************************************************/
/** @name Internal variables
 *  @{ */
/******************************************************************************/

static uint8_t gzp_system_address[GZP_SYSTEM_ADDRESS_WIDTH]; ///<
static uint8_t gzp_host_id[GZP_HOST_ID_LENGTH];              ///<
static uint8_t dyn_key[GZP_DYN_KEY_LENGTH];
static bool gzp_id_req_pending = false;

/** @} */


/******************************************************************************/
/** @name Internal (static) function prototypes
 *  @{ */
/******************************************************************************/

/**
 * Function for sending an encrypted packet.
 *
 * The function waits for the transmission to complete.
 *
 * @param tx_packet Pointer to the packet to be sent.
 * @param length    Length of the packet to be sent.
 * @param pipe      Pipe on which the packet should be sent.
 *
 * @retval true  If the transmission succeeded.
 * @retval false If the transmission failed (timed out).
 */
static bool gzp_tx_packet(const uint8_t* tx_packet, uint8_t length, uint8_t pipe);

/**
 * Function sending the packet *tx_packet and a subsequent packet fetching the response
 * to *tx_packet.
 *
 * @param tx_packet is a pointer to the packet to be sent.
 * @param tx_length is the length of the packet to be sent.
 * @param rx_dst is a pointer to where the received response packet should be stored.
 * @param rx_length is a pointer to where the length of the received packet should be stored.
 * @param pipe is the pipe on which the packet should be sent.
 *
 * @return result of the transaction.
 */
 static gzp_tx_rx_trans_result_t gzp_tx_rx_transaction(const uint8_t *tx_packet, uint8_t tx_length, uint8_t *rx_dst, uint32_t *rx_length, uint8_t pipe);

/**
 * Function for sending an encrypted packet. The function detects whether the correct
 * key was used, and attempts to send a "key update" to the host if the wrong key was being
 * used.

 * @param tx_packet is a pointer to the packet to be sent.
 * @param length is the length of the packet to be sent.

 * @retval true if transmission succeeded and packet was decrypted correctly by host.
 * @retval false if transmission failed or packet was not decrypted correctly by host.
 */
static bool gzp_crypt_tx_transaction(const uint8_t *tx_packet, uint8_t length);

/**
 * Function updateing the "dynamic key" and sending a "key update" to the host.
 *
 *  @retval true if key update succeeded.
 * @retval false if if key update failed.
 */
static bool gzp_key_update(void);

/**
 * Function for adding an element to "parameters data base" in non volatile (NV) memory. An element is
 * GZP_PARAMS_ELEMENT_SYSTEM_ADDRESS bytes long, holding the "system address" and  "host ID".
 *
 * The "parameters data base" can store up to GZP_DEVICE_PAIRING_PARAMS_DB_MAX_ENTRIES
 * elements.
 *
 * @param src_element is a pointer to the element.
 * @param index is a number between 0 and (GZP_PARAMS_DB_MAX_ENTRIES - 1)
 * selecting the location in which the element will be stored.
 */
static void gzp_params_db_add(const uint8_t *src_element, uint8_t index);

/**
 * Function for reading an element from "parameters data base" in non volatile (NV) memory. An element is
 * GZP_PARAMS_ELEMENT_SYSTEM_ADDRESS bytes long, holding the "system address" and  "host ID".
 *
 * @param dst_element is a pointer where the read element should be stored.
 * @param index is a number between 0 and (GZP_PARAMS_DB_MAX_ENTRIES - 1).
 * selecting the location that should be read.
 */
static void gzp_params_db_read(uint8_t* dst_element, uint8_t index);

/**
 * Function for writing an index to the "index data base" in non volatile (NV) memory.
 *
 * @param index is the index to be written to the data base.
 */
static void gzp_index_db_add(uint8_t index);

/**
 * Function for reading the index previously written to the "index data base" in NV memory.
 *
 * @return
 */
static uint8_t gzp_index_db_read(void);

/**
 * Check "index data base" is full.
 *
 * @retval true
 * @retval false
 */
static bool gzp_index_db_full(void);

/**
 * Function returning @b true if the "index data base" is empty.
 *
 * @retval true
 * @retval false
 */
static bool gzp_index_db_empty(void);

/**
 * Function returning @b true if array contains only 1s (0xff).
 *
 * @param *src is a pointer to the array to be evaluated.
 * @param length is the length of the array to be evaluated.
 *
 * @retval true
 * @retval false
 */
static bool gzp_array_is_set(const uint8_t* src, uint8_t length);

/**
 * Function for storing the current "system address" and "host ID" in NV memory.
 *
 * @param store_all selects whether only "system address" or both "system address" and
 *                  "host ID" should be stored.
 * @arg true selects that both should be stored.
 * @arg false selects that only "system address" should be stored.
 *
 * @retval true
 * @retval false
 */
static bool gzp_params_store(bool store_all);

/**
 * Restore the "system address" and "host ID" from NV memory.
 * @retval true
 * @retval false
 */
static bool gzp_params_restore(void);

/**
 * Delay function. Will add a delay equal to GZLL_RX_PERIOD * rx_periods [us].
 *
 * @param rx_periods
 */
void gzp_delay_rx_periods(uint32_t rx_periods);

/**
 * Delay function. Will add a delay equal to GZLL_RX_PERIOD * rx_periods [us] using the
 * gazell timer and not a delay loop.
 *
 * @param rx_periods
 */
void gzp_tick_sleep_rx_periods(uint32_t rx_periods);

/*
 * Print debug string. By default does nothing.
 *
 * If GZP_DEBUG is defined then the print string function is required to
 * be implemented.
 */
void print_string(char* p_expr);

/** @} */

/******************************************************************************/
/** @name Internal (static) variables
 *  @{ */
/******************************************************************************/

static nrf_gzll_device_tx_info_t latest_tx_info;  ///< Information about the last TX attempt, e.g. RSSI of ACK.

static volatile bool tx_complete; ///< Flag to indicate whether a GZLL TX attempt has completed.
static bool tx_success;  ///< Flag to indicate whether a GZLL TX attempt was successful.

// Define Macro to make array initialization nicer
#define REP4(X) X X X X

#if defined(__ICCARM__)
  #if GZP_PARAMS_DB_ADR == 0x1000
    static const uint32_t database[GZP_DEVICE_PARAMS_STORAGE_SIZE/4] @ "gzp_dev_data"
  #elif GZP_PARAMS_DB_ADR == 0x15000
    static const uint32_t database[GZP_DEVICE_PARAMS_STORAGE_SIZE/4] @ "gzp_dev_data_sd"
  #else
    #error
  #endif
#else
static const uint32_t database[GZP_DEVICE_PARAMS_STORAGE_SIZE / 4] __attribute__((at(GZP_PARAMS_DB_ADR)))
#endif
= {
    #define STATIC_INIT_VALUE    0xFFFFFFFF
    #define STATIC_INIT_COUNT    (GZP_DEVICE_PARAMS_STORAGE_SIZE / 4)
    #define INIT_1 STATIC_INIT_VALUE,
    #define INIT_4 REP4(INIT_1)
    #define INIT_16 REP4(INIT_4)
    #define INIT_64 REP4(INIT_16)
    #define INIT_256 REP4(INIT_64)
    #define INIT_1024 REP4(INIT_256)

    #if (STATIC_INIT_COUNT == 256)
        INIT_256
    #elif (STATIC_INIT_COUNT == 1024)
        INIT_1024
    #else
        #error Gazell Pairing Library database not initialized properly!
    #endif
}; ///< Database for storing keys.


/** @} */


/******************************************************************************/
// Implementation: Device-specific API functions
/******************************************************************************/


void gzp_init()
{
    gzp_id_req_pending = false;

#ifndef GZP_NV_STORAGE_DISABLE
    (void)gzp_params_restore();
#endif

    // Update radio parameters from gzp_system_address
    (void)gzp_update_radio_params(gzp_system_address);
}


void gzp_erase_pairing_data(void)
{
    // Erase database flash page so that it can be later written to.
    nrf_nvmc_page_erase((uint32_t)database);
}

bool gzp_address_req_send()
{
    //lint -save -e514 Unusual use of a Boolean expression (gzll_update_ok &= ...)
    uint8_t i;
    bool retval = false;
    bool success;
    uint8_t address_req[GZP_CMD_HOST_ADDRESS_REQ_PAYLOAD_LENGTH];
    uint8_t rx_payload[NRF_GZLL_CONST_MAX_PAYLOAD_LENGTH];
    uint32_t rx_payload_length =  NRF_GZLL_CONST_MAX_PAYLOAD_LENGTH;
    nrf_gzll_tx_power_t temp_power;
    uint32_t temp_max_tx_attempts;
    bool gzll_update_ok = true;


    // Store parameters that are temporarily changed
    temp_max_tx_attempts = nrf_gzll_get_max_tx_attempts();
    temp_power = nrf_gzll_get_tx_power();

    // Modify parameters
    nrf_gzp_disable_gzll();
    nrf_gzll_set_max_tx_attempts(GZP_REQ_TX_TIMEOUT);
    gzll_update_ok &= nrf_gzll_set_tx_power(GZP_POWER);

    // Flush RX FIFO
    gzll_update_ok &= nrf_gzll_flush_rx_fifo(GZP_PAIRING_PIPE);
    gzll_update_ok &= nrf_gzll_enable();
    // Build "request" packet
    address_req[0] = (uint8_t)GZP_CMD_HOST_ADDRESS_REQ;

    // Send a number of packets in order to broadcast that devices not within
    // close proximity must back off.
    for (i = 0; i < GZP_MAX_BACKOFF_PACKETS; i++)
    {
        success = gzp_tx_packet(address_req, GZP_CMD_HOST_ADDRESS_REQ_PAYLOAD_LENGTH, GZP_PAIRING_PIPE);
        if (success)
        {
            nrf_gzp_flush_rx_fifo(GZP_PAIRING_PIPE);
        }
        else
        {
            break;
        }
    }

    gzp_delay_rx_periods(GZP_TX_ACK_WAIT_TIMEOUT);
    // Send message for fetching pairing response from host.
    address_req[0] = (uint8_t)GZP_CMD_HOST_ADDRESS_FETCH;

    success =  gzp_tx_packet(address_req, GZP_CMD_HOST_ADDRESS_REQ_PAYLOAD_LENGTH, GZP_PAIRING_PIPE);
    if (success  && latest_tx_info.payload_received_in_ack)
    {
        // If pairing response received
        if (nrf_gzll_get_rx_fifo_packet_count(GZP_PAIRING_PIPE) > 0)
        {
            rx_payload_length = NRF_GZLL_CONST_MAX_PAYLOAD_LENGTH;  //dummy placeholder
            if (nrf_gzll_fetch_packet_from_rx_fifo(GZP_PAIRING_PIPE, rx_payload, &rx_payload_length))
            {
                if (rx_payload[0] == (uint8_t)GZP_CMD_HOST_ADDRESS_RESP)
                {
                    memcpy(gzp_system_address, &rx_payload[GZP_CMD_HOST_ADDRESS_RESP_ADDRESS], GZP_SYSTEM_ADDRESS_WIDTH);
                    gzll_update_ok &= gzp_update_radio_params(&rx_payload[GZP_CMD_HOST_ADDRESS_RESP_ADDRESS]);
                    #ifndef GZP_NV_STORAGE_DISABLE
                    (void)gzp_params_store(false); // "False" indicates that only "system address" part of DB element will be stored
                    #endif
                    retval = true;
                }
            }
        }
    }
    else
    {
        gzp_delay_rx_periods(GZP_NOT_PROXIMITY_BACKOFF_RX_TIMEOUT - GZP_TX_ACK_WAIT_TIMEOUT);
    }
    gzp_delay_rx_periods(GZP_STEP1_RX_TIMEOUT);

    // Clean-up and restore parameters temporarily  modified
    nrf_gzp_disable_gzll();
    gzll_update_ok &= nrf_gzll_flush_rx_fifo(GZP_PAIRING_PIPE);
    gzll_update_ok &= nrf_gzll_flush_tx_fifo(GZP_PAIRING_PIPE);
    nrf_gzll_set_max_tx_attempts(temp_max_tx_attempts);
    gzll_update_ok &= nrf_gzll_set_tx_power(temp_power);
    gzll_update_ok &= nrf_gzll_enable();

    if (!gzll_update_ok)
    {
    /*
    The update of the Gazell parameters failed. Use nrf_gzll_get_error_code()
    to investigate the cause.
    */
    }

    return retval;
    //lint -restore
}

#ifndef GZP_CRYPT_DISABLE

gzp_id_req_res_t gzp_id_req_send()
{
    uint8_t tx_packet[GZP_CMD_HOST_ID_REQ_PAYLOAD_LENGTH];
    uint8_t rx_packet[GZP_MAX_ACK_PAYLOAD_LENGTH];
    gzp_tx_rx_trans_result_t trans_result;

    // If no ID request is pending, send new "ID request"
    if (!gzp_id_req_pending)
    {
        // Build "Host ID request packet"
        tx_packet[0] = (uint8_t)GZP_CMD_HOST_ID_REQ;

        // Generate new session token
        gzp_random_numbers_generate(&tx_packet[GZP_CMD_HOST_ID_REQ_SESSION_TOKEN], GZP_SESSION_TOKEN_LENGTH);

        // Send "Host ID request"
        if (gzp_tx_packet(tx_packet, GZP_CMD_HOST_ID_REQ_PAYLOAD_LENGTH, GZP_DATA_PIPE))
        {
            // Update session token if "Host ID request" was successfully transmitted
            gzp_crypt_set_session_token(&tx_packet[GZP_CMD_HOST_ID_REQ_SESSION_TOKEN]);
            gzp_id_req_pending = true;

            return GZP_ID_RESP_PENDING;
        }
    }
    else // If "ID request is pending" send "fetch ID" packet
    {
        // Build "host ID fetch" packet
        tx_packet[0] = (uint8_t)GZP_CMD_HOST_ID_FETCH;
        gzp_add_validation_id(&tx_packet[GZP_CMD_HOST_ID_FETCH_VALIDATION_ID]);

        // Encrypt "host ID fetch" packet
        gzp_crypt_select_key(GZP_ID_EXCHANGE);
        gzp_crypt(&tx_packet[1], &tx_packet[1], GZP_CMD_HOST_ID_FETCH_PAYLOAD_LENGTH - 1);

        trans_result = gzp_tx_rx_transaction(tx_packet, GZP_CMD_HOST_ID_FETCH_PAYLOAD_LENGTH, rx_packet, NULL, GZP_DATA_PIPE);
        // If packet was successfully sent AND a response packet was received
        if (trans_result == GZP_TX_RX_SUCCESS)
        {
            // Validate response packet
            if (rx_packet[0] == (uint8_t)GZP_CMD_HOST_ID_FETCH_RESP)
            {
                gzp_crypt(&rx_packet[1], &rx_packet[1], GZP_CMD_HOST_ID_FETCH_RESP_PAYLOAD_LENGTH - 1);
                if (gzp_validate_id(&rx_packet[GZP_CMD_HOST_ID_FETCH_RESP_VALIDATION_ID]))
                {
                    switch (rx_packet[GZP_CMD_HOST_ID_FETCH_RESP_STATUS])
                    {
                    case GZP_ID_RESP_PENDING:
                        break;
                    case GZP_ID_RESP_REJECTED:
                        gzp_id_req_pending = false;
                        break;
                    case GZP_ID_RESP_GRANTED:
                        gzp_set_host_id(&rx_packet[GZP_CMD_HOST_ID_FETCH_RESP_HOST_ID]);
                        gzp_random_numbers_generate(dyn_key, GZP_DYN_KEY_LENGTH);
                        gzp_crypt_set_dyn_key(dyn_key);
                        #ifndef GZP_NV_STORAGE_DISABLE
                        (void)gzp_params_store(true);
                        #endif
                        gzp_id_req_pending = false;
                        break;
                    default:
                        break;
                    }

                    return (gzp_id_req_res_t)rx_packet[GZP_CMD_HOST_ID_FETCH_RESP_STATUS];
                }
                else
                {
                    gzp_id_req_pending = false;
                    return GZP_ID_RESP_REJECTED;
                }
            }
        }
    }

    gzp_id_req_pending = false;
    return GZP_ID_RESP_FAILED;
}

void gzp_id_req_cancel()
{
    gzp_id_req_pending = false;
}

bool gzp_crypt_data_send(const uint8_t *src, uint8_t length)
{
    if (length <= GZP_ENCRYPTED_USER_DATA_MAX_LENGTH)
    {
        if (gzp_crypt_tx_transaction(src, length))
        {
            return true;
        }
        else
        {
            //print_string("GZP_CRYPT_TX failed\r\n");
            // Attempt key update if user data transmission failed
            // during normal operation (!gzp_id_req_pending)
            if (!gzp_id_req_pending)
            {
                //print_string("KEY UPDATE\r\n");
                if (gzp_key_update())
                {
                  return gzp_crypt_tx_transaction(src, length);
                }
            }
            return false;
        }
    }
    else
    {
        return false;
    }
}

#endif
/** @} */


/******************************************************************************/
// Implementation: Internal (static) functions
/******************************************************************************/

static bool gzp_tx_packet(const uint8_t* tx_packet, uint8_t length, uint8_t pipe)
{
    tx_complete = false;
    tx_success = false;

    if (nrf_gzll_add_packet_to_tx_fifo(pipe,(uint8_t *)tx_packet, length))
    {
        while (tx_complete == false)
        {
            __WFI();
        }
        return tx_success;
    }
    else
    {
        return false;
    }
}

static gzp_tx_rx_trans_result_t gzp_tx_rx_transaction(const uint8_t *tx_packet, uint8_t tx_length, uint8_t *rx_dst, uint32_t *rx_length, uint8_t pipe)
{

    gzp_tx_rx_trans_result_t retval;
    uint8_t fetch_packet[GZP_CMD_FETCH_RESP_PAYLOAD_LENGTH];
    bool tx_packet_success;
    bool fetch_success;
    uint32_t local_rx_length = GZP_MAX_ACK_PAYLOAD_LENGTH;
    uint32_t temp_lifetime;

    nrf_gzp_flush_rx_fifo(pipe);

    retval = GZP_TX_RX_FAILED_TO_SEND;

    (void)nrf_gzll_disable();
    while (nrf_gzll_is_enabled())
    {}
    temp_lifetime = nrf_gzll_get_sync_lifetime();
    (void)nrf_gzll_set_sync_lifetime(GZP_TX_RX_TRANS_DELAY * 3); // 3 = RXPERIOD * 2 + margin
    (void)nrf_gzll_enable();

    tx_packet_success = gzp_tx_packet(tx_packet, tx_length, pipe);

    if (tx_packet_success)
    {
        retval = GZP_TX_RX_NO_RESPONSE;

        nrf_gzp_flush_rx_fifo(pipe);

        fetch_packet[0] = (uint8_t)GZP_CMD_FETCH_RESP;

        gzp_tick_sleep_rx_periods(GZP_TX_RX_TRANS_DELAY);

        tx_packet_success = gzp_tx_packet(fetch_packet, GZP_CMD_FETCH_RESP_PAYLOAD_LENGTH, pipe);

        if (tx_packet_success)
        {
            if (nrf_gzll_get_rx_fifo_packet_count(pipe))
            {
                local_rx_length = NRF_GZLL_CONST_MAX_PAYLOAD_LENGTH;
                fetch_success = nrf_gzll_fetch_packet_from_rx_fifo(pipe, rx_dst, &local_rx_length);
            }
            else
            {
                fetch_success = false;
            }

            if (fetch_success)
            {
                retval = GZP_TX_RX_SUCCESS;
            }
            else
            {
                //print_string("GZP_TX_FETCH_FAILED\r\n");
            }
        }
        else
        {
            //print_string("GZP_TX_FETCH_NO_ACK\r\n");
        }
    }

    (void)nrf_gzll_disable();
    while (nrf_gzll_is_enabled())
    {}
    (void)nrf_gzll_set_sync_lifetime(temp_lifetime);
    (void)nrf_gzll_enable();

    return retval;
}

#ifndef GZP_CRYPT_DISABLE

static bool gzp_crypt_tx_transaction(const uint8_t *src, uint8_t length)
{
    uint8_t tx_packet[GZP_MAX_FW_PAYLOAD_LENGTH];
    uint8_t rx_packet[GZP_MAX_ACK_PAYLOAD_LENGTH];
    uint8_t tx_packet_length;

    gzp_tx_rx_trans_result_t result;

    tx_packet_length = length + (uint8_t)GZP_ENCRYPTED_USER_DATA_PACKET_OVERHEAD;

    // Assemble tx packet
    tx_packet[0] = (uint8_t)GZP_CMD_ENCRYPTED_USER_DATA;
    gzp_add_validation_id(&tx_packet[GZP_CMD_ENCRYPTED_USER_DATA_VALIDATION_ID]);
    memcpy(&tx_packet[GZP_CMD_ENCRYPTED_USER_DATA_PAYLOAD], (uint8_t*)src, length);

    // Encrypt tx packet
    if (gzp_id_req_pending)
    {
        gzp_crypt_select_key(GZP_ID_EXCHANGE);
    }
    else
    {
        gzp_crypt_select_key(GZP_DATA_EXCHANGE);
    }
    gzp_crypt(&tx_packet[1], &tx_packet[1], tx_packet_length - 1);

    // If packet was successfully sent AND a response packet was received
    result = gzp_tx_rx_transaction(tx_packet, tx_packet_length, rx_packet, NULL, GZP_DATA_PIPE);
    if (result == GZP_TX_RX_SUCCESS)
    {
        if (rx_packet[0] == (uint8_t)GZP_CMD_ENCRYPTED_USER_DATA_RESP)
        {
            gzp_crypt(&rx_packet[GZP_CMD_ENCRYPTED_USER_DATA_RESP_VALIDATION_ID], &rx_packet[GZP_CMD_ENCRYPTED_USER_DATA_RESP_VALIDATION_ID], GZP_VALIDATION_ID_LENGTH);

            // Validate response in order to know whether packet was correctly decrypted by host
            if (gzp_validate_id(&rx_packet[GZP_CMD_ENCRYPTED_USER_DATA_RESP_VALIDATION_ID]))
            {
                // Update session token if normal operation (!gzp_id_req_pending)
                if (!gzp_id_req_pending)
                {
                    gzp_crypt_set_session_token(&rx_packet[GZP_CMD_ENCRYPTED_USER_DATA_RESP_SESSION_TOKEN]);
                }
                return true;
            }
            else
            {
                //print_string("GZP_CRYPT_TX_TRANS: Validation ID bad\r\n");
                return false;
            }
        }
        else
        {
            //print_string("GZP_CRYPT_TX_TRANS: Bad CMD. \r\n");
            return false;
        }
    }
    else
    {
        //print_string("GZP_CRYPT_TX_TRANS: gzp_tx_rx_trans not SUCCESS\r\n");
        return false;
    }
}

static bool gzp_key_update(void)
{
    uint8_t tx_packet[GZP_CMD_KEY_UPDATE_PAYLOAD_LENGTH], rx_packet[GZP_MAX_ACK_PAYLOAD_LENGTH];

    // Send "prepare packet" to get session token to be used for key update
    tx_packet[0] = (uint8_t)GZP_CMD_KEY_UPDATE_PREPARE;

    // If packet was successfully sent AND a response packet was received
    if (gzp_tx_rx_transaction(tx_packet, GZP_CMD_KEY_UPDATE_PREPARE_PAYLOAD_LENGTH, rx_packet, NULL, GZP_DATA_PIPE) == GZP_TX_RX_SUCCESS)
    {
        if (rx_packet[0] == (uint8_t)GZP_CMD_KEY_UPDATE_PREPARE_RESP)
        {
            gzp_crypt_set_session_token(&rx_packet[GZP_CMD_KEY_UPDATE_PREPARE_RESP_SESSION_TOKEN]);

            // Build "key update" packet
            tx_packet[0] = (uint8_t)GZP_CMD_KEY_UPDATE;
            gzp_add_validation_id(&tx_packet[GZP_CMD_KEY_UPDATE_VALIDATION_ID]);
            gzp_random_numbers_generate(&tx_packet[GZP_CMD_KEY_UPDATE_NEW_KEY], GZP_DYN_KEY_LENGTH);
            gzp_crypt_set_dyn_key(&tx_packet[GZP_CMD_KEY_UPDATE_NEW_KEY]);

            // Encrypt "key update packet"
            gzp_crypt_select_key(GZP_KEY_EXCHANGE);
            gzp_crypt(&tx_packet[1], &tx_packet[1], GZP_CMD_KEY_UPDATE_PAYLOAD_LENGTH - 1);

            // Send "key update" packet
            if (gzp_tx_packet(tx_packet, GZP_CMD_KEY_UPDATE_PAYLOAD_LENGTH, GZP_DATA_PIPE))
            {
                return true;
            }
        }
    }

    return false;
}

#endif

void gzp_set_host_id(const uint8_t * id)
{
    memcpy(gzp_host_id, id, GZP_HOST_ID_LENGTH);
}

void gzp_get_host_id(uint8_t * dst_id)
{
    memcpy(dst_id, gzp_host_id, GZP_HOST_ID_LENGTH);
}

static void gzp_params_db_add(const uint8_t* src_element, uint8_t index)
{
    nrf_nvmc_write_bytes((GZP_PARAMS_DB_ADR + (index * GZP_PARAMS_DB_ELEMENT_SIZE)), src_element, (uint32_t)GZP_PARAMS_DB_ELEMENT_SIZE);
}


static void gzp_params_db_read(uint8_t* dst_element, uint8_t index)
{
    memcpy(dst_element,(uint8_t*)(GZP_PARAMS_DB_ADR + (index * GZP_PARAMS_DB_ELEMENT_SIZE)), GZP_PARAMS_DB_ELEMENT_SIZE);
}


static void gzp_index_db_add(uint8_t val)
{
    int16_t i;
    uint8_t temp_val;
    uint32_t  addr;

    // Search for unwritten loacation in index DB
    for (i = 0; i < GZP_INDEX_DB_SIZE; i++)
    {
        temp_val = *(uint8_t*)(GZP_INDEX_DB_ADR + i);

        // Lower nibble
        if (i != (GZP_INDEX_DB_SIZE - 1))
        {
            if ((temp_val & 0x0f) == 0x0f)
            {
                temp_val = (temp_val & 0xf0) | val;
                break;
            }
            // Upper nibble
            else if ((temp_val & 0xf0) == 0xf0)
            {
                temp_val = (temp_val & 0x0f) | (val << 4);
                break;
            }
        }
        else
        {
            temp_val = (GZP_PARAMS_DB_MAX_ENTRIES << 4) | val;
            break;
        }
    }

    // Write index DB
    addr = (GZP_INDEX_DB_ADR + i);
    nrf_nvmc_write_byte(addr, temp_val);
}

static uint8_t gzp_index_db_read()
{
    uint8_t retval;
    int16_t i;

    // Search for previously written location
    for (i = (GZP_INDEX_DB_SIZE - 1); i >= 0; i--)
    {
        retval = *(uint8_t*)(GZP_INDEX_DB_ADR + i);

        if (retval != 0xff)
        {
          break;
        }
    }

    if (retval == 0xff)
    {
        retval = GZP_PARAMS_DB_MAX_ENTRIES;  // index db empty
    }
    else if ((retval & 0xf0) != 0xf0)
    {
        retval >>= 4;
    }
    else
    {
        retval &= 0x0f;
    }

    return retval;
}

int8_t gzp_get_pairing_status(void)
{
    uint8_t db_byte;
    int8_t db_index;
    int16_t i;
    uint8_t temp_element[GZP_PARAMS_DB_ELEMENT_SIZE];
    uint8_t default_host_id[GZP_HOST_ID_LENGTH];

    db_index = -2;

    // Populate default Host ID with F's.
    for (i=0; i< GZP_HOST_ID_LENGTH; i++)
    {
       default_host_id[i] = 0xFF;
    }

    // Search for previously written location
    for (i = (GZP_INDEX_DB_SIZE - 1); i >= 0; i--)
    {
        db_byte = *(uint8_t*)(GZP_INDEX_DB_ADR + i);

        // Check if idx has been written to
        if (db_byte != 0xff)
        {
          // Convert 4-bit nibble to index
          if ((db_byte & 0xf0) != 0xf0)
          {
              db_byte = (db_byte >> 4) & 0x0f;
          }
          else
          {
              db_byte = db_byte & 0x0f;
          }

          // Retrieve database entry
          gzp_params_db_read(temp_element, db_byte);

          // Check if database entry is all F's
          if ( memcmp(&temp_element[GZP_PARAMS_DB_ELEMENT_HOST_ID], default_host_id, GZP_HOST_ID_LENGTH) != 0)
          {

            db_index = db_byte;
          }
          else
          {
            db_index = -1;
          }
          break;
        }
    }

    return db_index;
}


static bool gzp_index_db_full()
{
#if (GZP_INDEX_DB_SIZE != 0)
    return ((*(uint8_t*)(GZP_INDEX_DB_ADR + (GZP_INDEX_DB_SIZE - 1)) != 0xff));
#else
    return true;
#endif
}

//lint -save -e506 Constant value boolean
static bool gzp_index_db_empty()
{
#if (GZP_INDEX_DB_SIZE != 0)
    return ((GZP_INDEX_DB_SIZE == 0) || ((*(uint8_t*)(GZP_INDEX_DB_ADR)) == 0xff));
#else
    return true;
#endif
}
//lint -restore

static bool gzp_array_is_set(const uint8_t* src, uint8_t length)
{
    uint8_t i;

    for (i = 0; i < length; i++)
    {
        if (*(src++) != 0xff)
        {
            return false;
        }
    }
    return true;
}

static bool gzp_params_store(bool store_all)
{
    uint8_t i;
    bool write_index_db = false;
    bool write_param_db = false;
    uint8_t new_db_index = 0;
    uint8_t temp_element[GZP_PARAMS_DB_ELEMENT_SIZE];

    // Search param DB to see if current setup exists
    if (store_all)
    {
        // Search for: Current system address and host ID exists
        for (i = 0; i < GZP_PARAMS_DB_MAX_ENTRIES; i++)
        {
            gzp_params_db_read(temp_element, i);

            if (((memcmp(&temp_element[GZP_PARAMS_DB_ELEMENT_SYSTEM_ADDRESS], gzp_system_address, GZP_SYSTEM_ADDRESS_WIDTH)) == 0) && ((memcmp(&temp_element[GZP_PARAMS_DB_ELEMENT_HOST_ID], gzp_host_id, GZP_HOST_ID_LENGTH)) == 0))
            {
                write_index_db = true;
                new_db_index = i;
                break; // System address + host_id allready exists in database
            }
        }

        // Search for: Current system address and cleared host ID
        if (!write_index_db)
        {
            for (i = 0; i < GZP_PARAMS_DB_MAX_ENTRIES; i++)
            {
                gzp_params_db_read(temp_element, i);

                if (((memcmp(&temp_element[GZP_PARAMS_DB_ELEMENT_SYSTEM_ADDRESS], gzp_system_address, GZP_SYSTEM_ADDRESS_WIDTH)) == 0) && \
                        (gzp_array_is_set(&temp_element[GZP_PARAMS_DB_ELEMENT_HOST_ID], GZP_HOST_ID_LENGTH)))
                {
                    memcpy(&temp_element[GZP_PARAMS_DB_ELEMENT_HOST_ID], gzp_host_id, GZP_HOST_ID_LENGTH);
                    new_db_index = i;
                    write_index_db = true;
                    write_param_db = true;
                    break;
                }
            }
        }

        // Search for: Cleared system address and cleared host ID
        if (!write_index_db)
        {
            for (i = 0; i < GZP_PARAMS_DB_MAX_ENTRIES; i++)
            {
                gzp_params_db_read(temp_element, i);

                if (gzp_array_is_set(temp_element, GZP_PARAMS_DB_ELEMENT_SIZE))
                {
                    memcpy(&temp_element[GZP_PARAMS_DB_ELEMENT_SYSTEM_ADDRESS], gzp_system_address, GZP_SYSTEM_ADDRESS_WIDTH);
                    memcpy(&temp_element[GZP_PARAMS_DB_ELEMENT_HOST_ID], gzp_host_id, GZP_HOST_ID_LENGTH);
                    new_db_index = i;
                    write_index_db = true;
                    write_param_db = true;
                    break;
                }
            }
        }
    }
    else
    {
        // Search for: System address + any host ID
        for (i = 0; i < GZP_PARAMS_DB_MAX_ENTRIES; i++)
        {
            gzp_params_db_read(temp_element, i);

            if ((memcmp(&temp_element[GZP_PARAMS_DB_ELEMENT_SYSTEM_ADDRESS], gzp_system_address, GZP_SYSTEM_ADDRESS_WIDTH)) == 0)
            {
                //memcpy(&temp_element[GZP_PARAMS_DB_ELEMENT_HOST_ID], gzp_host_id, GZP_HOST_ID_LENGTH);
                write_index_db = true;
                new_db_index = i;
                break;
            }
        }

        // Search for: System address cleared
        if (!write_index_db)
        {
            for (i = 0; i < GZP_PARAMS_DB_MAX_ENTRIES; i++)
            {
                gzp_params_db_read(temp_element, i);

                if (gzp_array_is_set(&temp_element[GZP_PARAMS_DB_ELEMENT_SYSTEM_ADDRESS], GZP_SYSTEM_ADDRESS_WIDTH))
                {
                    memcpy(&temp_element[GZP_PARAMS_DB_ELEMENT_SYSTEM_ADDRESS], gzp_system_address, GZP_SYSTEM_ADDRESS_WIDTH);
                    write_index_db = true;
                    write_param_db = true;
                    new_db_index = i;
                    break;
                }
            }
        }
    }

    if (write_param_db)
    {
        gzp_params_db_add(temp_element, new_db_index);
    }

    if (write_index_db)
    {
        if (!gzp_index_db_full() && (new_db_index != gzp_index_db_read()) && (new_db_index != GZP_PARAMS_DB_MAX_ENTRIES))
        {
            gzp_index_db_add(new_db_index);
            return true;
        }
    }

    return false;
}

static bool gzp_params_restore(void)
{
    uint8_t i;
    uint8_t temp_element[GZP_PARAMS_DB_ELEMENT_SIZE];

    if (!gzp_index_db_full() && !gzp_index_db_empty())
    {
        i = gzp_index_db_read();

        if (i < GZP_PARAMS_DB_MAX_ENTRIES)
        {
            gzp_params_db_read(temp_element, i);
            memcpy(gzp_system_address, &temp_element[GZP_PARAMS_DB_ELEMENT_SYSTEM_ADDRESS], GZP_SYSTEM_ADDRESS_WIDTH);
            gzp_set_host_id(&temp_element[GZP_PARAMS_DB_ELEMENT_HOST_ID]);
            return true;
        }
    }

    return false;
}

void gzp_delay_rx_periods(uint32_t rx_periods)
{
    nrf_delay_us(rx_periods * 2 * nrf_gzll_get_timeslot_period());
}

void gzp_tick_sleep_rx_periods(uint32_t rx_periods)
{
    nrf_gzll_clear_tick_count();

    while (nrf_gzll_get_tick_count() < 2 * rx_periods)
    {
        __WFI();
    }
}


void nrf_gzll_device_tx_success(uint32_t pipe, nrf_gzll_device_tx_info_t tx_info)
{
    latest_tx_info = tx_info;

    tx_complete = true;
    tx_success = true;
}

void nrf_gzll_device_tx_failed(uint32_t pipe, nrf_gzll_device_tx_info_t tx_info)
{
    latest_tx_info = tx_info;

    tx_complete = true;
    tx_success = false;
}

bool nrf_gzp_tx_complete(void)
{
    return tx_complete;
}

bool nrf_gzp_tx_success(void)
{
    return tx_success;
}

void nrf_gzp_reset_tx_complete()
{
    tx_complete = false;
}

void nrf_gzp_reset_tx_success()
{
    tx_success = false;
}

void nrf_gzll_disabled(void)
{
}

void nrf_gzll_host_rx_data_ready(uint32_t pipe, nrf_gzll_host_rx_info_t rx_info)
{
}

/** @} */
/** @} */
