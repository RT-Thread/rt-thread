/**
 * This software is subject to the ANT+ Shared Source License
 * www.thisisant.com/swlicenses
 * Copyright (c) Garmin Canada Inc. 2012
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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANTFS)

#include "antfs.h"
#include <string.h>
#include "defines.h"
#include "app_error.h"
#include "app_timer.h"
#include "ant_error.h"
#include "ant_parameters.h"
#include "ant_interface.h"
#include "ant_key_manager.h"
#include "crc.h"

#if ANTFS_CONFIG_DEBUG_LED_ENABLED
    #include "bsp.h"
#endif // ANTFS_CONFIG_DEBUG_LED_ENABLED

#define BURST_PACKET_SIZE                  8u                            /**< The burst packet size. */

#define ANTFS_CONNECTION_TYPE_OFFSET       0x00u                         /**< The connection type offset within ANT-FS message. */
#define ANTFS_COMMAND_OFFSET               0x01u                         /**< The command offset within ANT-FS message. */
#define ANTFS_RESPONSE_OFFSET              0x01u                         /**< The response offset within ANT-FS message. */

#define ANTFS_CONTROL_OFFSET               0x02u                         /**< The control offset within ANT-FS message. */
#define ANTFS_DATA_OFFSET                  0x03u                         /**< The data offset within ANT-FS message. */

#define ANTFS_BEACON_ID                    0x43u                         /**< The ANT-FS beacon ID. */
#define ANTFS_COMMAND_ID                   0x44u                         /**< The ANT-FS command ID. */

// Beacon definitions.
#define STATUS1_OFFSET                     0x01u                         /**< The beacon status1 field offset. */
#define STATUS2_OFFSET                     0x02u                         /**< The beacon status2 field offset. */
   #define DEVICE_STATE_SHIFT              0x00u                         /**< Shift value for device state bitfield. */
   #define DEVICE_STATE_MASK               (0x0Fu << DEVICE_STATE_SHIFT) /**< Device state bitmask. */
   #define DEVICE_STATE_LINK               (0x00u << DEVICE_STATE_SHIFT) /**< Device is in link state. */
   #define DEVICE_STATE_AUTHENTICATE       (0x01u << DEVICE_STATE_SHIFT) /**< Device is in authenticate state. */
   #define DEVICE_STATE_TRANSPORT          (0x02u << DEVICE_STATE_SHIFT) /**< Device is in transport state. */
   #define DEVICE_STATE_BUSY               (0x03u << DEVICE_STATE_SHIFT) /**< Device is in busy state. */

#define DEVICE_DESCRIPTOR_OFFSET_0         0x04u                         /**< Beacon ANT-FS device descriptor LSB position. */
#define DEVICE_DESCRIPTOR_OFFSET_1         0x05u                         /**< Beacon ANT-FS device descriptor LSB + 1 position. */
#define DEVICE_DESCRIPTOR_OFFSET_2         0x06u                         /**< Beacon ANT-FS device descriptor LSB + 2 position. */
#define DEVICE_DESCRIPTOR_OFFSET_3         0x07u                         /**< Beacon ANT-FS device descriptor MSB position. */

// Commands.
#define ANTFS_CMD_NONE                     0x00u                         /**< Used to identify that no ANT-FS command is in progress. */
#define ANTFS_CMD_LINK_ID                  0x02u                         /**< ANT-FS link command ID. */
#define ANTFS_CMD_DISCONNECT_ID            0x03u                         /**< ANT-FS disconnect command ID. */
#define ANTFS_CMD_AUTHENTICATE_ID          0x04u                         /**< ANT-FS authenticate command ID. */
#define ANTFS_CMD_PING_ID                  0x05u                         /**< ANT-FS ping command ID. */
#define ANTFS_CMD_DOWNLOAD_ID              0x09u                         /**< ANT-FS download request command ID. */
#define ANTFS_CMD_UPLOAD_REQUEST_ID        0x0Au                         /**< ANT-FS upload request command ID. */
#define ANTFS_CMD_ERASE_ID                 0x0Bu                         /**< ANT-FS erase request command ID. */
#define ANTFS_CMD_UPLOAD_DATA_ID           0x0Cu                         /**< ANT-FS upload command ID. */

// Responses.
#define ANTFS_RSP_AUTHENTICATE_ID          0x84u                         /**< ANT-FS authenticate response command ID. */
#define ANTFS_RSP_DOWNLOAD_ID              0x89u                         /**< ANT-FS download request response command ID. */
#define ANTFS_RSP_UPLOAD_REQ_ID            0x8Au                         /**< ANT-FS upload request response command ID. */
#define ANTFS_RSP_ERASE_ID                 0x8Bu                         /**< ANT-FS erase response command ID. */
#define ANTFS_RSP_UPLOAD_DATA_ID           0x8Cu                         /**< ANT-FS upload data response command ID. */

// Link command.
#define TRANSPORT_CHANNEL_FREQUENCY_OFFSET 0x02u                         /**< Channel frequency field offset within link command. */
#define TRANSPORT_MESSAGE_PERIOD_OFFSET    0x03u                         /**< Channel period field offset within link command. */
#define HOST_ID_OFFSET_0                   0x04u                         /**< Host serial number period field LSB offset within link command. */
#define HOST_ID_OFFSET_1                   0x05u                         /**< Host serial number period field LSB + 1 offset within link command. */
#define HOST_ID_OFFSET_2                   0x06u                         /**< Host serial number period field LSB + 2 offset within link command. */
#define HOST_ID_OFFSET_3                   0x07u                         /**< Host serial number period field MSB offset within link command. */

// Authenticate command.
#define COMMAND_TYPE_OFFSET                0x02u                         /**< Command type field offset within authenticate command. */
   #define COMMAND_TYPE_PROCEED            0x00u                         /**< Command type proceed to transport in the authenticate command. */
   #define COMMAND_TYPE_REQUEST_SERIAL     0x01u                         /**< Command type request client device serial number in the authenticate command. */
   #define COMMAND_TYPE_REQUEST_PAIR       0x02u                         /**< Command type request pairing in the authenticate command. */
   #define COMMAND_TYPE_REQUEST_PASSKEY    0x03u                         /**< Command type request passkey exchange in the authenticate command. */

// Authenticate response.
#define RESPONSE_TYPE_OFFSET               0x02u                         /**< Command type field offset within authenticate response command. */
   #define AUTH_RESPONSE_N_A               0x00u                         /**< Command response type N/A (response for client serial number request). */
   #define AUTH_RESPONSE_ACCEPT            0x01u                         /**< Command response type accept. */
   #define AUTH_RESPONSE_REJECT            0x02u                         /**< Command response type reject. */

// Authenticate command/response.
#define AUTH_STRING_LENGTH_OFFSET          0x03u                         /**< Authenticate Command/Response authentication string length offset. */
#define SERIAL_NUMBER_OFFSET_0             0x04u                         /**< Authenticate Command/Response client/host serial number LSB offset. */
#define SERIAL_NUMBER_OFFSET_1             0x05u                         /**< Authenticate Command/Response client/host serial number LSB + 1 offset. */
#define SERIAL_NUMBER_OFFSET_2             0x06u                         /**< Authenticate Command/Response client/host serial number LSB + 2 offset. */
#define SERIAL_NUMBER_OFFSET_3             0x07u                         /**< Authenticate Command/Response client/host serial number MSB offset. */

// Download/Upload/Erase commands.
#define INITIAL_REQUEST_OFFSET             0x01u                         /**< Download/Upload/Erase command initial request command offset. */
#define DATA_INDEX_OFFSET_LOW              0x02u                         /**< Download/Upload/Erase command offset index low. */
#define DATA_INDEX_OFFSET_HIGH             0x03u                         /**< Download/Upload/Erase command offset index high. */

#define ADDRESS_PARAMETER_OFFSET_0         0x04u                         /**< Download/Upload command parameter LSB offset. */
#define ADDRESS_PARAMETER_OFFSET_1         0x05u                         /**< Download/Upload command parameter LSB + 1 offset. */
#define ADDRESS_PARAMETER_OFFSET_2         0x06u                         /**< Download/Upload command parameter LSB + 2 offset. */
#define ADDRESS_PARAMETER_OFFSET_3         0x07u                         /**< Download/Upload command parameter MSB offset. */
#define UPLOAD_CRC_OFFSET_LOW              0x06u                         /**< Upload data CRC offset low. */
#define UPLOAD_CRC_OFFSET_HIGH             0x07u                         /**< Upload data CRC offset high. */

// Authentication type. The highest level of authentication available is included in the beacon.
#if ANTFS_CONFIG_AUTH_TYPE_PASSKEY_ENABLED
   #define AUTHENTICATION_TYPE             COMMAND_TYPE_REQUEST_PASSKEY  /**< Passkey and pairing only mode set as authentication type in beacon. */
#elif ANTFS_CONFIG_AUTH_TYPE_PAIRING_ENABLED
   #define AUTHENTICATION_TYPE             COMMAND_TYPE_REQUEST_PAIR     /**< Pairing only mode set as authentication type in beacon. */
#elif ANTFS_CONFIG_AUTH_TYPE_PASSTHROUGH_ENABLED
   #define AUTHENTICATION_TYPE             COMMAND_TYPE_PROCEED          /**< Pass-through mode set as authentication type in beacon. */
#else
   #error "No valid auth type defined"
#endif

#define AUTHENTICATION_RETRIES             0x05u                         /**< Max number of retries for authentication responses */

#define ANTFS_EVENT_QUEUE_SIZE             0x04u                         /**< ANT-FS event queue size. */
#define SAVE_DISTANCE                       256u                         /**< Save distance required because of nRF buffer to line up data offset on retry. */

// Buffer Indices.
#define BUFFER_INDEX_MESG_SIZE             0x00u                         /**< ANT message buffer index length offset. */
#define BUFFER_INDEX_MESG_ID               0x01u                         /**< ANT message buffer index ID offset. */
#define BUFFER_INDEX_CHANNEL_NUM           0x02u                         /**< ANT message buffer index channel number offset. */
#define BUFFER_INDEX_MESG_DATA             0x03u                         /**< ANT message buffer index begin of data offset. */
#define BUFFER_INDEX_RESPONSE_CODE         0x04u                         /**< ANT message buffer index response code offset. */

typedef struct
{
    char     friendly_name[ANTFS_FRIENDLY_NAME_MAX];                      /**< Friendly Name. */
    bool     is_name_set;                                                 /**< Is the name set. */
    uint32_t index;                                                       /**< Current index (for reading the friendly name). */
    uint32_t friendly_name_size;                                          /**< Friendly name size. */
} friendly_name_t;

typedef union
{
    antfs_link_substate_t         link_sub_state;                         /**< Sub-state (Link layer). */
    antfs_authenticate_substate_t auth_sub_state;                         /**< Sub-state (Authentication layer). */
    antfs_transport_substate_t    trans_sub_state;                        /**< Sub-state (Transport layer). */
} antfs_substate_t;

typedef struct
{
    antfs_state_t    state;                                               /**< ANT-FS state. */
    antfs_substate_t sub_state;                                           /**< ANT-FS sub-state. */
} antfs_states_t;

typedef struct
{
    antfs_event_return_t * p_queue;                                       /**< ANT-FS event queue. */
    uint32_t head;                                                        /**< ANT-FS event queue head index. */
    uint32_t tail;                                                        /**< ANT-FS event queue tail index. */
} antfs_event_queue_t;

static antfs_params_t              m_initial_parameters;                  /**< Initial parameters. */
static antfs_beacon_status_byte1_t m_active_beacon_status1_field;         /**< Status 1 field in beacon. */
static uint32_t                    m_active_beacon_frequency;             /**< Active beacon frequency. */
static antfs_states_t              m_current_state;                       /**< Current state. */
static friendly_name_t             m_friendly_name;                       /**< Host's friendly name. */
static ulong_union_t               m_link_host_serial_number;             /**< Host's serial number. */
static uint32_t                    m_link_command_in_progress;            /**< ANT-FS command in progress. */
static uint32_t                    m_authenticate_command_type;           /**< Authenticate command type in progress. */
static volatile uint8_t            m_burst_wait;                          /**< Polling status flag for data unlock on burst handler input. */
static uint8_t                     m_retry;                               /**< Retry counter */
APP_TIMER_DEF(m_timer_id);                                                /**< Timer ID used with the timer module. */

#if ANTFS_CONFIG_AUTH_TYPE_PASSKEY_ENABLED
   static uint32_t m_passkey_index;                                       /**< Current location of Tx block (auth string). */
#endif // ANTFS_CONFIG_AUTH_TYPE_PASSKEY_ENABLED

// Download/upload.
static bool            m_is_data_request_pending;                         /**< Requested data pending. */
static bool            m_is_crc_pending;                                  /**< CRC for data packets pending. */
static ushort_union_t  m_file_index;                                      /**< File index of current upload/download. */
static ulong_union_t   m_file_size;                                       /**< File size of current upload/download (bytes). */
static ulong_union_t   m_max_block_size;                                  /**< Maximum number of bytes expected to be downloaded in a single burst block of data (set by host). */
static ulong_union_t   m_link_burst_index;                                /**< Current location of Tx block (bytes). */
static ulong_union_t   m_bytes_remaining;                                 /**< Total remaining data length (bytes). */
static ulong_union_t   m_max_transfer_index;                              /**< Upper limit of the current Tx burst block (bytes). */
static uint32_t        m_bytes_to_write;                                  /**< Number of bytes to write to file (upload). */
static const uint8_t * mp_upload_data;                                    /**< Address of begin of the buffer that holds data received from upload. */
#if ANTFS_CONFIG_UPLOAD_ENABLED
    static ulong_union_t m_block_size;                                    /**< Number of bytes the client can receive in a single burst. */
#endif // ANTFS_CONFIG_UPLOAD_ENABLED

// CRC verification.
static uint32_t m_saved_crc_offset;                                       /**< CRC data offset (bytes) saved at last CRC update (save point). */
static uint32_t m_saved_buffer_crc_offset;                                /**< Data offset to track how much data has been buffered into nRF */
static uint32_t m_temp_crc_offset;                                        /**< Temporary CRC data offset used in CRC calculation. */
static uint16_t m_compared_crc;                                           /**< 16-bit CRC for all data packets in the block (provided by download request). */
static uint16_t m_transfer_crc;                                           /**< 16-bit CRC for all data packets in the block (calculated by client). */
static uint16_t m_saved_transfer_crc;                                     /**< 16-bit CRC saved at last CRC update (save point). */
static uint16_t m_saved_buffer_crc;                                       /**< 16-bit CRC saved at last CRC update (save point) for buffering the nRF */

// ANT-FS event handling.
static antfs_event_return_t m_event_queue_buffer[ANTFS_EVENT_QUEUE_SIZE]; /**< Event queue storage. */
static antfs_event_queue_t m_event_queue;                                 /**< Event queue. */

static antfs_burst_wait_handler_t m_burst_wait_handler = NULL;            /**< Burst wait handler */


const char * antfs_hostname_get(void)
{
    if (m_friendly_name.is_name_set)
    {
        return (m_friendly_name.friendly_name);
    }

    return NULL;
}


/**@brief Function for waiting for the burst transmission request to complete.
 */
static void wait_burst_request_to_complete(void)
{
    while (m_burst_wait != 0)
    {
        if (m_burst_wait_handler != NULL)
        {
            m_burst_wait_handler();
        }
    };
}


/**@brief Function for stopping ANT-FS timeout, which is possibly currently running.
 */
static void timeout_disable(void)
{
    m_link_command_in_progress = ANTFS_CMD_NONE;

    const uint32_t err_code = app_timer_stop(m_timer_id);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for transmitting a beacon.
 *
 * Transmits a beacon either using a broadcast or burst transmission mode.
 *
 * @param[in] message_type     Defines the used transmission mode.
 */
static void beacon_transmit(uint32_t message_type)
{
    uint8_t beacon_status_byte2;

    // Set beacon status byte 2.

    if (m_link_command_in_progress == ANTFS_CMD_NONE)
    {
        switch (m_current_state.state)
        {
            case ANTFS_STATE_AUTH:
                beacon_status_byte2 = DEVICE_STATE_AUTHENTICATE;
                break;

            case ANTFS_STATE_TRANS:
                beacon_status_byte2 = DEVICE_STATE_TRANSPORT;
                break;

            default:
                beacon_status_byte2 = DEVICE_STATE_LINK;
                break;
        }
    }
    else
    {
        beacon_status_byte2 = DEVICE_STATE_BUSY;
    }

    // Set remaining beacon fields.

    uint8_t tx_buffer[BURST_PACKET_SIZE];

    tx_buffer[0] = ANTFS_BEACON_ID;
    tx_buffer[1] = m_active_beacon_status1_field.status;
    tx_buffer[2] = beacon_status_byte2;
    tx_buffer[3] = AUTHENTICATION_TYPE;

    if ((m_current_state.state == ANTFS_STATE_AUTH) ||
        (m_current_state.state == ANTFS_STATE_TRANS))
    {
        tx_buffer[4] = m_link_host_serial_number.bytes.byte0;
        tx_buffer[5] = m_link_host_serial_number.bytes.byte1;
        tx_buffer[6] = m_link_host_serial_number.bytes.byte2;
        tx_buffer[7] = m_link_host_serial_number.bytes.byte3;
    }
    else
    {
        tx_buffer[4] = m_initial_parameters.beacon_device_type;
        tx_buffer[5] = (m_initial_parameters.beacon_device_type >> 8u);
        tx_buffer[6] = m_initial_parameters.beacon_device_manufacturing_id;
        tx_buffer[7] = (m_initial_parameters.beacon_device_manufacturing_id >> 8u);
    }

    if (message_type == MESG_BROADCAST_DATA_ID)
    {
        if (sd_ant_broadcast_message_tx(ANTFS_CONFIG_CHANNEL_NUMBER, sizeof(tx_buffer), tx_buffer) != NRF_SUCCESS)
        {
            // @note: No implementation needed, as it is a valid and accepted use case for this call
            // to fail. This call can fail if we are in middle of bursting.
        }
    }
    else if (message_type == MESG_BURST_DATA_ID)
    {
        // Send as the first packet of a burst.
        const uint32_t err_code = sd_ant_burst_handler_request(ANTFS_CONFIG_CHANNEL_NUMBER,
                                                               sizeof(tx_buffer),
                                                               tx_buffer,
                                                               BURST_SEGMENT_START);
        APP_ERROR_CHECK(err_code);

        wait_burst_request_to_complete();

        // This is the first packet of a burst response, disable command timeout while bursting.
        timeout_disable();
    }
    else
    {
        // This should not happen.
        APP_ERROR_HANDLER(message_type);
    }
}


/**@brief Function for transmitting a authenticate response message.
 *
 * @param[in] response_type    Authenticate response code.
 * @param[in] password_length  Length of authentication string.
 * @param[in] p_password       Authentication string transmitted.
 */
static void authenticate_response_transmit(uint8_t response_type,
                                           uint32_t password_length,
                                           const uint8_t * p_password)
{
    ulong_union_t serial_number;

    serial_number.data = m_initial_parameters.client_serial_number;

    // First packet is beacon.
    beacon_transmit(MESG_BURST_DATA_ID);

    uint8_t tx_buffer[BURST_PACKET_SIZE];

    tx_buffer[ANTFS_CONNECTION_TYPE_OFFSET] = ANTFS_COMMAND_ID;
    tx_buffer[ANTFS_RESPONSE_OFFSET]        = ANTFS_RSP_AUTHENTICATE_ID;
    tx_buffer[RESPONSE_TYPE_OFFSET]         = response_type;
    tx_buffer[AUTH_STRING_LENGTH_OFFSET]    = password_length;
    tx_buffer[SERIAL_NUMBER_OFFSET_0]       = serial_number.bytes.byte0;
    tx_buffer[SERIAL_NUMBER_OFFSET_1]       = serial_number.bytes.byte1;
    tx_buffer[SERIAL_NUMBER_OFFSET_2]       = serial_number.bytes.byte2;
    tx_buffer[SERIAL_NUMBER_OFFSET_3]       = serial_number.bytes.byte3;

    uint32_t err_code;
    if ((m_current_state.state == ANTFS_STATE_AUTH) &&
        (
            (response_type != AUTH_RESPONSE_REJECT) &&
            password_length &&
            (password_length <= ANTFS_AUTH_STRING_MAX)
        )
       )
    {
        // Send second packet (auth response).
        err_code = sd_ant_burst_handler_request(ANTFS_CONFIG_CHANNEL_NUMBER,
                                                sizeof(tx_buffer),
                                                tx_buffer,
                                                BURST_SEGMENT_CONTINUE);
        APP_ERROR_CHECK(err_code);

        wait_burst_request_to_complete();

        // Round size to a multiple of 8 bytes.
        uint8_t tx_buffer_authenticate[ANTFS_AUTH_STRING_MAX + 1u];

        memset(tx_buffer_authenticate, 0, ANTFS_AUTH_STRING_MAX + 1u);
        memcpy(tx_buffer_authenticate, p_password, password_length);

        // Round up total number bytes to a multiple of 8 to be sent to burst handler.
        if (password_length & (BURST_PACKET_SIZE - 1u))
        {
            password_length &= ~(BURST_PACKET_SIZE - 1u);
            password_length += BURST_PACKET_SIZE;
        }

        // Send auth string (last packets of the burst).
        err_code = sd_ant_burst_handler_request(ANTFS_CONFIG_CHANNEL_NUMBER,
                                                password_length,
                                                tx_buffer_authenticate,
                                                BURST_SEGMENT_END);
        APP_ERROR_CHECK(err_code);

        wait_burst_request_to_complete();

        m_link_command_in_progress = ANTFS_RSP_AUTHENTICATE_ID;
    }
    else
    {
        // If the authorization is rejected or there is no valid password, the auth response is the
        // last packet.

        err_code = sd_ant_burst_handler_request(ANTFS_CONFIG_CHANNEL_NUMBER,
                                                sizeof(tx_buffer),
                                                tx_buffer,
                                                BURST_SEGMENT_END);
        APP_ERROR_CHECK(err_code);

        wait_burst_request_to_complete();
    }

    // Switch to appropiate state.
    if (response_type == AUTH_RESPONSE_REJECT)
    {
        m_current_state.sub_state.auth_sub_state = ANTFS_AUTH_SUBSTATE_REJECT;
    }
    else if (response_type == AUTH_RESPONSE_ACCEPT)
    {
        m_current_state.sub_state.auth_sub_state = ANTFS_AUTH_SUBSTATE_ACCEPT;
    }
    else
    {
        // No implementation needed.
    }
}


bool antfs_pairing_resp_transmit(bool accept)
{
#if ANTFS_CONFIG_AUTH_TYPE_PAIRING_ENABLED
    // This function should only be called when ANT-FS is in PAIRING mode.
    if ((m_current_state.state != ANTFS_STATE_AUTH) ||
        (m_current_state.sub_state.auth_sub_state != ANTFS_AUTH_SUBSTATE_PAIR))
    {
        return false;
    }

    m_link_command_in_progress = ANTFS_CMD_AUTHENTICATE_ID;

    if (accept)
    {
        // Accept request and send passkey if authentication passed.
        authenticate_response_transmit(AUTH_RESPONSE_ACCEPT,
                                       ANTFS_PASSKEY_SIZE,
                                       m_initial_parameters.p_pass_key);
    }
    else
    {
        // Reject authentication request.
        authenticate_response_transmit(AUTH_RESPONSE_REJECT, 0, NULL);
    }

    return true;
#else
    return false;
#endif // ANTFS_CONFIG_AUTH_TYPE_PAIRING_ENABLED
}


/**@brief Function for adding an ANT-FS event to the event queue.
 *
 * @param[in] event_code       The event to be added.
 */
static void event_queue_write(antfs_event_t event_code)
{
    antfs_event_return_t * p_event = NULL;
#if ANTFS_CONFIG_DEBUG_LED_ENABLED
    uint32_t err_code;
#endif // ANTFS_CONFIG_DEBUG_LED_ENABLED

    // Check if there is room in the queue for a new event.
    if (((m_event_queue.head + 1u) & (ANTFS_EVENT_QUEUE_SIZE - 1u)) != m_event_queue.tail)
    {
        p_event = &(m_event_queue.p_queue[m_event_queue.head]);
    }

    if (p_event != NULL)
    {
        // Initialize event parameters.
        p_event->event = event_code;

        // Set parameters depending on event type.
        switch (event_code)
        {
            case ANTFS_EVENT_ERASE_REQUEST:
                p_event->file_index = m_file_index.data;
                p_event->offset     = 0;
                p_event->bytes      = 0;
                p_event->crc        = 0;
                break;

            case ANTFS_EVENT_DOWNLOAD_REQUEST:
                p_event->file_index = m_file_index.data;
                // Requested offset for the download.
                p_event->offset     = m_link_burst_index.data;
                p_event->bytes      = 0;
                p_event->crc        = 0;
                break;

            case ANTFS_EVENT_DOWNLOAD_REQUEST_DATA:
                p_event->file_index = m_file_index.data;
                // Current offset.
                p_event->offset     = m_link_burst_index.data;

                if (m_bytes_remaining.data > (ANTFS_BURST_BLOCK_SIZE * BURST_PACKET_SIZE))
                {
                    // If remaining bytes > burst block size then grab one block at a time.
                    p_event->bytes = ANTFS_BURST_BLOCK_SIZE * BURST_PACKET_SIZE;
                }
                else
                {
                    p_event->bytes = m_bytes_remaining.data;
                }

                p_event->crc = 0;
                break;

            case ANTFS_EVENT_UPLOAD_REQUEST:
                p_event->file_index = m_file_index.data;
                // Requested offset for the upload.
                p_event->offset     = m_link_burst_index.data;
                // Upper limit of the download (offset + remaining bytes).
                p_event->bytes      = m_max_transfer_index.data;
                // CRC Seed (from last save point if resuming).
                p_event->crc        = m_transfer_crc;
                break;

            case ANTFS_EVENT_UPLOAD_DATA:
                p_event->file_index = m_file_index.data;
                // Current offset.
                p_event->offset     = m_link_burst_index.data;
                // Current CRC.
                p_event->crc        = m_transfer_crc;
                // Number of bytes to write.
                p_event->bytes      = m_bytes_to_write;
                // Upload to appication data buffer.
                memcpy(p_event->data, mp_upload_data, m_bytes_to_write);
                break;

            case ANTFS_EVENT_PAIRING_REQUEST:
#if ANTFS_CONFIG_DEBUG_LED_ENABLED
                err_code = bsp_indication_set(BSP_INDICATE_BONDING);
                APP_ERROR_CHECK(err_code);
#endif // ANTFS_CONFIG_DEBUG_LED_ENABLED
                break;

            default:
                // No parameters need to be set.

                p_event->file_index = 0;
                p_event->offset     = 0;
                p_event->bytes      = 0;
                p_event->crc        = 0;
                break;
        }

        // Put the event in the queue.
        m_event_queue.head = ((m_event_queue.head + 1u) & (ANTFS_EVENT_QUEUE_SIZE - 1u));
    }
    else
    {
        // No free space left in the queue.
        APP_ERROR_HANDLER(0);
    }
}


/**@brief Function for transmitting download request response message.
 *
 * @param[in] response         Download response code.
 */
static void download_request_response_transmit(uint8_t response)
{
    // First burst packet is beacon.
    beacon_transmit(MESG_BURST_DATA_ID);

    uint8_t tx_buffer[BURST_PACKET_SIZE];

    // Next send the first part of the download response.
    tx_buffer[0] = ANTFS_COMMAND_ID;
    tx_buffer[1] = ANTFS_RSP_DOWNLOAD_ID;
    tx_buffer[2] = response;
    tx_buffer[3] = 0;
    // Total number of bytes remaining in the data block.
    tx_buffer[4] = m_bytes_remaining.bytes.byte0;
    tx_buffer[5] = m_bytes_remaining.bytes.byte1;
    tx_buffer[6] = m_bytes_remaining.bytes.byte2;
    tx_buffer[7] = m_bytes_remaining.bytes.byte3;

    uint32_t err_code = sd_ant_burst_handler_request(ANTFS_CONFIG_CHANNEL_NUMBER,
                                                     sizeof(tx_buffer),
                                                     tx_buffer,
                                                     BURST_SEGMENT_CONTINUE);
    APP_ERROR_CHECK(err_code);

    wait_burst_request_to_complete();

    // Second part of the download response.

    // The offset the data will start from in this block.
    tx_buffer[0] = m_link_burst_index.bytes.byte0;
    tx_buffer[1] = m_link_burst_index.bytes.byte1;
    tx_buffer[2] = m_link_burst_index.bytes.byte2;
    tx_buffer[3] = m_link_burst_index.bytes.byte3;
    // The file size in the client device.
    tx_buffer[4] = m_file_size.bytes.byte0;
    tx_buffer[5] = m_file_size.bytes.byte1;
    tx_buffer[6] = m_file_size.bytes.byte2;
    tx_buffer[7] = m_file_size.bytes.byte3;

    if (response || (m_bytes_remaining.data == 0))
    {
        // If the download was rejected or there is no data to send.

        // Set response to end since we're not downloading any data.
        err_code = sd_ant_burst_handler_request(ANTFS_CONFIG_CHANNEL_NUMBER,
                                                sizeof(tx_buffer),
                                                tx_buffer,
                                                BURST_SEGMENT_END);
        APP_ERROR_CHECK(err_code);

        wait_burst_request_to_complete();
    }
    else
    {
        // Response will continue (data packets + CRC footer to follow).
        err_code = sd_ant_burst_handler_request(ANTFS_CONFIG_CHANNEL_NUMBER,
                                                sizeof(tx_buffer),
                                                tx_buffer,
                                                BURST_SEGMENT_CONTINUE);
        APP_ERROR_CHECK(err_code);

        wait_burst_request_to_complete();
    }

    m_link_command_in_progress = ANTFS_CMD_DOWNLOAD_ID;

    if (response == 0)
    {
        // If we are going to download (response OK), enter the downloading substate.
        m_current_state.sub_state.trans_sub_state = ANTFS_TRANS_SUBSTATE_DOWNLOADING;
        event_queue_write(ANTFS_EVENT_DOWNLOAD_START);
    }
    else
    {
        // Download rejected.
        event_queue_write(ANTFS_EVENT_DOWNLOAD_FAIL);
    }
}


void antfs_download_req_resp_prepare(uint8_t response,
                                     const antfs_request_info_t * const p_request_info)
{
    // This function should only be called after receiving a download request.
    APP_ERROR_CHECK_BOOL((m_current_state.state == ANTFS_STATE_TRANS) &&
                         (m_link_command_in_progress == ANTFS_CMD_DOWNLOAD_ID));

    if (response == 0)
    {
        // Download request OK.

        // File size of the requested download.
        m_file_size.data = p_request_info->file_size.data;

        if (m_link_burst_index.data > m_file_size.data)
        {
            // Offset should not exceed file size.
            m_link_burst_index.data = m_file_size.data;
        }

        // If the host is not limiting download size or the file size does not exceed the host's
        // download size limit.
        if ((m_max_block_size.data == 0) || (m_file_size.data < m_max_block_size.data))
        {
            //  Number of bytes remaining to be downloaded in this block is the file size.
            m_bytes_remaining.data = m_file_size.data;
        }

        if ((m_file_size.data - m_link_burst_index.data) < m_bytes_remaining.data)
        {
            // Calculate number of remaining bytes in this block based on the offset.
            m_bytes_remaining.data = m_file_size.data - m_link_burst_index.data;
        }

        // If the application is limiting the Tx block size.
        if (m_bytes_remaining.data > p_request_info->max_burst_block_size.data)
        {
            // Number of remaining bytes in this block is the application defined block size.
            m_bytes_remaining.data = p_request_info->max_burst_block_size.data;
        }

        // Find upper limit of the burst Tx.
        m_max_transfer_index.data = m_link_burst_index.data + m_bytes_remaining.data;

        if (m_saved_crc_offset == ANTFS_MAX_FILE_SIZE)
        {
            // CRC checking was set as invalid. An invalid download was requested, so reject it.
            response = RESPONSE_INVALID_OPERATION;
        }
    }

    if ((response != 0) || (m_file_size.data == 0))
    {
        // Send the response right away if the download request was rejected or there is no data to
        // send.
        download_request_response_transmit(response);
    }
    else
    {
        // Proceed to download data.
        if (m_link_burst_index.data != m_saved_crc_offset)
        {
            uint32_t temp;

            // If requesting to resume exactly where we left off, we can start from the same block.
            if (m_link_burst_index.data == m_temp_crc_offset)
            {
                // Move last save point to end of last block sent.
                m_saved_crc_offset   = m_link_burst_index.data;
                m_saved_transfer_crc = m_transfer_crc;
            }

            // To resume the download, request a block of data starting from the last save point.
            // Update the remaining number of bytes per the last save point.
            m_bytes_remaining.data += (m_link_burst_index.data - m_saved_crc_offset);

            // Swap the current burst Tx index with the saved CRC index, to make sure we do not
            // start updating the CRC until we get to the requested index.
            temp                    = m_link_burst_index.data;
            m_link_burst_index.data = m_saved_crc_offset;
            m_saved_crc_offset      = temp;

            // Set CRC to previous save point, to check the CRC provided by the host.
            m_transfer_crc = m_saved_transfer_crc;
        }

        m_temp_crc_offset = m_saved_crc_offset;

        m_is_data_request_pending = true;

        // Request data from application.
        event_queue_write(ANTFS_EVENT_DOWNLOAD_REQUEST_DATA);

        m_current_state.sub_state.trans_sub_state = ANTFS_TRANS_SUBSTATE_VERIFY_CRC;
    }
}


uint32_t antfs_input_data_download(uint16_t index,
                                   uint32_t offset,
                                   uint32_t num_bytes,
                                   const uint8_t * const p_message)
{
    // Verify that this is the requested data.
    APP_ERROR_CHECK_BOOL((offset == m_link_burst_index.data) && (index == m_file_index.data));

    // If file offset is greater than the upper limit, this is not data we need.
    APP_ERROR_CHECK_BOOL(offset <= m_max_transfer_index.data);

    if ((m_current_state.state == ANTFS_STATE_TRANS) &&
        (
            (m_current_state.sub_state.trans_sub_state == ANTFS_TRANS_SUBSTATE_VERIFY_CRC) ||
            // Only send data if we were processing a download request.
            (m_current_state.sub_state.trans_sub_state == ANTFS_TRANS_SUBSTATE_DOWNLOADING)
        )
       )
    {
        uint32_t block_offset = 0;

        if (m_current_state.sub_state.trans_sub_state == ANTFS_TRANS_SUBSTATE_VERIFY_CRC)
        {
            // Make sure download_request_response_transmit defaults to RESPONSE_INVALID_CRC.
            uint32_t response = RESPONSE_MESSAGE_OK;

            // Check CRC.
            if (m_link_burst_index.data == m_saved_crc_offset)
            {
                // If indexes match, we can compare CRC directly.
                if (m_transfer_crc != m_compared_crc)
                {
                    response = RESPONSE_INVALID_CRC;
                }
                else
                {
                    // Set up the save point
                    m_temp_crc_offset = m_link_burst_index.data; // Reset save point counter
                    m_saved_crc_offset = m_link_burst_index.data;
                    m_saved_buffer_crc_offset = m_link_burst_index.data;

                    // Set up the CRC save points
                    m_saved_transfer_crc = m_compared_crc;
                    m_saved_buffer_crc = m_compared_crc;
                    m_is_crc_pending     = true;
                }
                // Start bursting beacon and the download response (3 burst packets).
                download_request_response_transmit(response);
            }
            // If the data is in this block, advance to the requested offset
            else if ((m_link_burst_index.data < m_saved_crc_offset) &&
                     ((m_saved_crc_offset - m_link_burst_index.data) < num_bytes))
            {
                // Update the offset within this block for the requested transmission.
                block_offset = m_saved_crc_offset - m_link_burst_index.data;
                // Update the number of bytes that will actually be transmitted.
                num_bytes   -= block_offset;

                // Update CRC calculation up to requested index.
                m_transfer_crc          = crc_crc16_update(m_transfer_crc, p_message, block_offset);
                // Update the remaining number of bytes.
                m_bytes_remaining.data -= block_offset;

                // Check CRC
                if (m_transfer_crc != m_compared_crc)
                {
                    response = RESPONSE_INVALID_CRC;
                }
                else
                {
                    // Move index back to point where transmission will resume.
                    m_link_burst_index.data = m_saved_crc_offset;

                    // Set up the save point
                    m_temp_crc_offset = m_link_burst_index.data; // Reset save point counter
                    m_saved_buffer_crc_offset = m_link_burst_index.data;

                    // Set up the CRC save points
                    m_saved_transfer_crc = m_compared_crc;
                    m_saved_buffer_crc = m_compared_crc;

                    m_is_crc_pending = true;
                }
                download_request_response_transmit(response);
            }
            // Data index has gone too far and it is not possible to check CRC, fail and let host retry
            else if (m_link_burst_index.data > m_saved_crc_offset)
            {
                response = RESPONSE_INVALID_CRC;
                download_request_response_transmit(response);
            }
            // Keep getting data and recalculate the CRC until the indexes match
            else
            {
                m_is_data_request_pending = false;

                // Update the current burst index and bytes remaining
                m_link_burst_index.data += num_bytes;
                m_bytes_remaining.data -= num_bytes;

                // Update CRC
                m_transfer_crc = crc_crc16_update(m_transfer_crc, p_message, num_bytes);

                // Request more data.
                event_queue_write(ANTFS_EVENT_DOWNLOAD_REQUEST_DATA);
            }
        }

        // Append data.
        if (m_current_state.sub_state.trans_sub_state == ANTFS_TRANS_SUBSTATE_DOWNLOADING)
        {
            uint32_t num_of_bytes_to_burst = num_bytes;

            if (num_of_bytes_to_burst & (BURST_PACKET_SIZE - 1u))
            {
                // Round up total number bytes to a multiple of BURST_PACKET_SIZE to be sent to
                // burst handler.
                num_of_bytes_to_burst &= ~(BURST_PACKET_SIZE - 1u);
                num_of_bytes_to_burst += BURST_PACKET_SIZE;
            }

            uint32_t err_code = sd_ant_burst_handler_request(ANTFS_CONFIG_CHANNEL_NUMBER,
                                                             num_of_bytes_to_burst,
                                                             (uint8_t*)&(p_message[block_offset]),
                                                             BURST_SEGMENT_CONTINUE);
            if (err_code != NRF_ANT_ERROR_TRANSFER_SEQUENCE_NUMBER_ERROR)
            {
                // If burst failed before we are able to catch it, we will get a TRANSFER_SEQUENCE_NUMBER_ERROR
                // The message processing will send client back to correct state
                APP_ERROR_CHECK(err_code);
            }

            wait_burst_request_to_complete();

            // Update current burst index.
            m_link_burst_index.data += num_bytes;
            // Update remaining bytes.
            m_bytes_remaining.data  -= num_bytes;

            m_is_data_request_pending = false;

            m_transfer_crc = crc_crc16_update(m_transfer_crc,
                                              &(p_message[block_offset]),
                                              num_bytes);

            if ((m_link_burst_index.data - m_temp_crc_offset) > SAVE_DISTANCE)
            {
                // Set CRC save point
                m_saved_transfer_crc = m_saved_buffer_crc;  // Set CRC at buffer save point (will always be one behind to account for buffering)
                m_saved_buffer_crc = m_transfer_crc;        // Set CRC at save point

                // Set offset save point
                m_saved_crc_offset = m_saved_buffer_crc_offset;     // Set offset at buffer save point (will always be one behind to account for buffering)
                m_saved_buffer_crc_offset = m_link_burst_index.data;    // Set buffer offset to current data offset

                // Reset save counter offset
                m_temp_crc_offset = m_link_burst_index.data;    // Set to current location; next save point will take place after SAVE_DISTANCE bytes
            }

            if (!m_is_data_request_pending && (m_link_burst_index.data < m_max_transfer_index.data))
            {
                // If we have not finished the download.

                // Request more data.
                event_queue_write(ANTFS_EVENT_DOWNLOAD_REQUEST_DATA);

                m_is_data_request_pending = true;
            }
            else if (m_link_burst_index.data >= m_max_transfer_index.data && m_is_crc_pending)
            {
                // We are done, send CRC footer.

                uint8_t tx_buffer[BURST_PACKET_SIZE];

                tx_buffer[0] = 0;
                tx_buffer[1] = 0;
                tx_buffer[2] = 0;
                tx_buffer[3] = 0;
                tx_buffer[4] = 0;
                tx_buffer[5] = 0;
                tx_buffer[6] = (uint8_t)m_transfer_crc;
                tx_buffer[7] = (uint8_t)(m_transfer_crc >> 8u);

                err_code = sd_ant_burst_handler_request(ANTFS_CONFIG_CHANNEL_NUMBER,
                                                        sizeof(tx_buffer),
                                                        tx_buffer,
                                                        BURST_SEGMENT_END);
                if (err_code != NRF_ANT_ERROR_TRANSFER_SEQUENCE_NUMBER_ERROR)
                {
                    // If burst failed before we are able to catch it, we will get a TRANSFER_SEQUENCE_NUMBER_ERROR
                    // The message processing will send client back to correct state
                    APP_ERROR_CHECK(err_code);
                }

                wait_burst_request_to_complete();

                m_is_crc_pending          = false;
                m_max_transfer_index.data = 0;
            }

            // Return the number of bytes we accepted.
            return num_bytes;
        }
    }

    // No bytes were accepted.
    return 0;
}


bool antfs_upload_req_resp_transmit(uint8_t response,
                                    const antfs_request_info_t * const p_request_info)
{
#if ANTFS_CONFIG_UPLOAD_ENABLED
    if (m_current_state.state != ANTFS_STATE_TRANS ||
        // Only send the response if we were processing an upload request.
        (m_link_command_in_progress != ANTFS_CMD_UPLOAD_REQUEST_ID))
    {
        return false;
    }

    // If the application is sending a response for a different file than requested, the upload
    // will fail.
    if (p_request_info->file_index.data != m_file_index.data)
    {
        event_queue_write(ANTFS_EVENT_UPLOAD_FAIL);

        return false;
    }

    ulong_union_t max_mem_size;
    // Set maximum number of bytes that can be written to the file.
    max_mem_size.data = p_request_info->max_file_size;

    if (p_request_info->max_burst_block_size.data != 0)
    {
        // If the client is limiting the block size set the block size requested by the client.
        m_block_size.data = p_request_info->max_burst_block_size.data;
    }
    else
    {
        // Try to get the entire file in a single block.
        m_block_size.data = max_mem_size.data;
    }

    if (response == 0)
    {
        if (m_max_transfer_index.data > max_mem_size.data)
        {
            // Not enough space to write file, reject download.
            response = RESPONSE_MESSAGE_NOT_ENOUGH_SPACE;
        }
    }

    // Get last valid CRC and last valid offset.
    m_transfer_crc          = p_request_info->file_crc;
    m_link_burst_index.data = p_request_info->file_size.data;

    // First packet to transmit is the beacon.
    beacon_transmit(MESG_BURST_DATA_ID);

    // Second packet.

    uint8_t tx_buffer[BURST_PACKET_SIZE];

    tx_buffer[0] = ANTFS_COMMAND_ID;
    tx_buffer[1] = ANTFS_RSP_UPLOAD_REQ_ID;
    tx_buffer[2] = response;
    tx_buffer[3] = 0;
    // Last valid data offset written to the file.
    tx_buffer[4] = m_link_burst_index.bytes.byte0;
    tx_buffer[5] = m_link_burst_index.bytes.byte1;
    tx_buffer[6] = m_link_burst_index.bytes.byte2;
    tx_buffer[7] = m_link_burst_index.bytes.byte3;


    uint32_t err_code = sd_ant_burst_handler_request(ANTFS_CONFIG_CHANNEL_NUMBER,
                                                     sizeof(tx_buffer),
                                                     tx_buffer,
                                                     BURST_SEGMENT_CONTINUE);
    APP_ERROR_CHECK(err_code);

    wait_burst_request_to_complete();

    // Third packet.

    // Maximum number of bytes that can be written to the file.
    tx_buffer[0] = max_mem_size.bytes.byte0;
    tx_buffer[1] = max_mem_size.bytes.byte1;
    tx_buffer[2] = max_mem_size.bytes.byte2;
    tx_buffer[3] = max_mem_size.bytes.byte3;
    // Maximum upload block size.
    tx_buffer[4] = m_block_size.bytes.byte0;
    tx_buffer[5] = m_block_size.bytes.byte1;
    tx_buffer[6] = m_block_size.bytes.byte2;
    tx_buffer[7] = m_block_size.bytes.byte3;

    err_code = sd_ant_burst_handler_request(ANTFS_CONFIG_CHANNEL_NUMBER,
                                            sizeof(tx_buffer),
                                            tx_buffer,
                                            BURST_SEGMENT_CONTINUE);
    APP_ERROR_CHECK(err_code);

    wait_burst_request_to_complete();

    // Fourth packet.

    tx_buffer[0] = 0;
    tx_buffer[1] = 0;
    tx_buffer[2] = 0;
    tx_buffer[3] = 0;
    tx_buffer[4] = 0;
    tx_buffer[5] = 0;
    // Value of CRC at last data offset.
    tx_buffer[6] = (uint8_t) m_transfer_crc;
    tx_buffer[7] = (uint8_t)(m_transfer_crc >> 8);

    err_code = sd_ant_burst_handler_request(ANTFS_CONFIG_CHANNEL_NUMBER,
                                            sizeof(tx_buffer),
                                            tx_buffer,
                                            BURST_SEGMENT_END);
    APP_ERROR_CHECK(err_code);

    wait_burst_request_to_complete();

    m_link_command_in_progress = ANTFS_CMD_UPLOAD_REQUEST_ID;

    if (response != 0)
    {
        // Failed upload request. Reset max transfer index to 0 (do not accept any data if the host
        // sends it anyway).
        m_max_transfer_index.data = 0;
    }
    else
    {
        // Wait for upload data request.
        m_current_state.sub_state.trans_sub_state = ANTFS_TRANS_SUBSTATE_UPLOAD_WAIT_FOR_DATA;
    }

    return true;
#else
    return false;
#endif  // ANTFS_CONFIG_UPLOAD_ENABLED
}


bool antfs_upload_data_resp_transmit(bool data_upload_success)
{
#if ANTFS_CONFIG_UPLOAD_ENABLED
    // Should be in TRANSPORT layer to send this response.
    if (m_current_state.state != ANTFS_STATE_TRANS)
    {
        return false;
    }

    uint8_t tx_buffer[BURST_PACKET_SIZE];

    // Response.
    tx_buffer[0] = ANTFS_COMMAND_ID;
    tx_buffer[1] = ANTFS_RSP_UPLOAD_DATA_ID;
    tx_buffer[2] = (data_upload_success) ? RESPONSE_MESSAGE_OK : RESPONSE_MESSAGE_FAIL;
    tx_buffer[3] = 0;
    tx_buffer[4] = 0;
    tx_buffer[5] = 0;
    tx_buffer[6] = 0;
    tx_buffer[7] = 0;

    // First packet is beacon.
    beacon_transmit(MESG_BURST_DATA_ID);

    // Send last packet.
    uint32_t err_code = sd_ant_burst_handler_request(ANTFS_CONFIG_CHANNEL_NUMBER,
                                                     sizeof(tx_buffer),
                                                     tx_buffer,
                                                     BURST_SEGMENT_END);
    APP_ERROR_CHECK(err_code);

    wait_burst_request_to_complete();

    m_link_command_in_progress = ANTFS_CMD_UPLOAD_REQUEST_ID;

    // Reset maximum index.
    m_max_transfer_index.data = 0;

    return true;
#else
    return false;
#endif  // ANTFS_CONFIG_UPLOAD_ENABLED
}


void antfs_erase_req_resp_transmit(uint8_t response)
{
    // This function should only be called after receiving an erase request.
    APP_ERROR_CHECK_BOOL((m_current_state.state == ANTFS_STATE_TRANS) &&
                         (m_link_command_in_progress == ANTFS_CMD_ERASE_ID));

    beacon_transmit(MESG_BURST_DATA_ID);

    uint8_t tx_buffer[BURST_PACKET_SIZE];

    // Erase response.
    tx_buffer[0] = ANTFS_COMMAND_ID;
    tx_buffer[1] = ANTFS_RSP_ERASE_ID;
    tx_buffer[2] = response;
    tx_buffer[3] = 0;
    tx_buffer[4] = 0;
    tx_buffer[5] = 0;
    tx_buffer[6] = 0;
    tx_buffer[7] = 0;

    uint32_t err_code = sd_ant_burst_handler_request(ANTFS_CONFIG_CHANNEL_NUMBER,
                                                     sizeof(tx_buffer),
                                                     tx_buffer,
                                                     BURST_SEGMENT_END);
    APP_ERROR_CHECK(err_code);

    wait_burst_request_to_complete();
}


bool antfs_event_extract(antfs_event_return_t * const p_event)
{
    bool return_value = false;

    if (m_event_queue.head != m_event_queue.tail)
    {
        // Pending events exist. Copy event parameters into return event.
        p_event->event      = m_event_queue.p_queue[m_event_queue.tail].event;
        p_event->file_index = m_event_queue.p_queue[m_event_queue.tail].file_index;
        p_event->offset     = m_event_queue.p_queue[m_event_queue.tail].offset;
        p_event->bytes      = m_event_queue.p_queue[m_event_queue.tail].bytes;
        p_event->crc        = m_event_queue.p_queue[m_event_queue.tail].crc;
        memcpy(p_event->data,
               m_event_queue.p_queue[m_event_queue.tail].data,
               sizeof(p_event->data));

        // Release the event queue.
        m_event_queue.tail = ((m_event_queue.tail + 1u) & (ANTFS_EVENT_QUEUE_SIZE - 1u));

        return_value = true;
    }

    return return_value;
}


/**@brief Function for setting the channel period.
 *
 * Sets the channel period. The only allowed frequencies are 0.5, 1, 2, 4 and 8 Hz.
 *
 * @param[in] link_period      Link period for the beacon transmission.
 */
static void channel_period_set(uint32_t link_period)
{
    uint32_t period;

    switch (link_period)
    {
        default:
            // Shouldn't happen, but just in case default to 0,5Hz.
        case BEACON_PERIOD_0_5_HZ:
            period = 65535u;
            break;

        case BEACON_PERIOD_1_HZ:
            period = 32768u;
            break;

        case BEACON_PERIOD_2_HZ:
            period = 16384u;
            break;

        case BEACON_PERIOD_4_HZ:
            period = 8192u;
            break;

        case BEACON_PERIOD_8_HZ:
            period = 4096u;
            break;
    }

    const uint32_t err_code = sd_ant_channel_period_set(ANTFS_CONFIG_CHANNEL_NUMBER, period);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for starting ANT-FS timeout.
 *
 * @param[in] timeout_in_secs  Timeout requested in unit of seconds.
 */
static void timeout_start(uint32_t timeout_in_secs)
{
    uint32_t err_code = app_timer_stop(m_timer_id);
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_start(m_timer_id,
                               APP_TIMER_TICKS((uint32_t)(timeout_in_secs * 1000u)),
                               NULL);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for switching to authentication layer.
 */
static void authenticate_layer_transit(void)
{
    if (m_current_state.state != ANTFS_STATE_OFF)
    {
        m_current_state.state                    = ANTFS_STATE_AUTH;
        m_current_state.sub_state.auth_sub_state = ANTFS_AUTH_SUBSTATE_NONE;
        m_link_command_in_progress               = ANTFS_CMD_NONE;

        timeout_start(ANTFS_CONFIG_LINK_COMMAND_TIMEOUT);

        uint32_t err_code = sd_ant_channel_radio_freq_set(ANTFS_CONFIG_CHANNEL_NUMBER, m_active_beacon_frequency);
        APP_ERROR_CHECK(err_code);

        event_queue_write(ANTFS_EVENT_AUTH);
    }
}


/**@brief Function for decoding an ANT-FS command received at the link layer.
 *
 * @param[in] p_command_buffer The ANT-FS command buffer.
 */
static void link_layer_cmd_decode(const uint8_t * p_command_buffer)
{
    if (p_command_buffer[ANTFS_CONNECTION_TYPE_OFFSET] != ANTFS_COMMAND_ID)
    {
        return;
    }

    switch (p_command_buffer[ANTFS_COMMAND_OFFSET])
    {
        case ANTFS_CMD_LINK_ID:
            // Channel frequency.
            m_active_beacon_frequency                            =
                p_command_buffer[TRANSPORT_CHANNEL_FREQUENCY_OFFSET];
            // Channel message period.
            m_active_beacon_status1_field.parameters.link_period =
                p_command_buffer[TRANSPORT_MESSAGE_PERIOD_OFFSET];
            // Host serial Number.
            m_link_host_serial_number.bytes.byte0                =
                p_command_buffer[HOST_ID_OFFSET_0];
            m_link_host_serial_number.bytes.byte1                =
                p_command_buffer[HOST_ID_OFFSET_1];
            m_link_host_serial_number.bytes.byte2                =
                p_command_buffer[HOST_ID_OFFSET_2];
            m_link_host_serial_number.bytes.byte3                =
                p_command_buffer[HOST_ID_OFFSET_3];

            // Move to the channel period issued by the host.
            channel_period_set(m_active_beacon_status1_field.parameters.link_period);

            authenticate_layer_transit();
            break;

        default:
            break;
    }
}


/**@brief Function for switching to link layer.
 */
static void link_layer_transit(void)
{
    if (m_current_state.state != ANTFS_STATE_OFF)
    {
        uint32_t err_code;
#if ANTFS_CONFIG_DEBUG_LED_ENABLED
        err_code = bsp_indication_set(BSP_INDICATE_IDLE);
        APP_ERROR_CHECK(err_code);
#endif // ANTFS_CONFIG_DEBUG_LED_ENABLED

        m_current_state.state                    = ANTFS_STATE_LINK;
        m_current_state.sub_state.link_sub_state = ANTFS_LINK_SUBSTATE_NONE;
        m_link_command_in_progress               = ANTFS_CMD_NONE;
        m_active_beacon_status1_field            = m_initial_parameters.beacon_status_byte1;
        m_active_beacon_frequency                = m_initial_parameters.beacon_frequency;

        timeout_disable();

        err_code = sd_ant_channel_radio_freq_set(ANTFS_CONFIG_CHANNEL_NUMBER, m_active_beacon_frequency);
        APP_ERROR_CHECK(err_code);

        event_queue_write(ANTFS_EVENT_LINK);
    }
}


/**@brief Function for decoding an ANT-FS command received at the authenticate layer.
 *
 * @param[in] control_byte     The command control byte.
 * @param[in] p_command_buffer The ANT-FS command buffer.
 */
static void authenticate_layer_cmd_decode(uint8_t control_byte,
                                          const uint8_t * p_command_buffer)
{
    // @note: Response variable must have a static storage allocation as it keeps track of the
    // passkey authentication progress between multiple burst packets.
#if ANTFS_CONFIG_AUTH_TYPE_PASSKEY_ENABLED
    static uint32_t response;
#endif // ANTFS_CONFIG_AUTH_TYPE_PASSKEY_ENABLED

    if ((control_byte & ~SEQUENCE_LAST_MESSAGE) == 0 && m_link_command_in_progress != ANTFS_CMD_NONE)
    {
        // This is something new, and we're busy processing something already, so don't respond
        return;
    }

    if (p_command_buffer[ANTFS_CONNECTION_TYPE_OFFSET] == ANTFS_COMMAND_ID &&
        m_link_command_in_progress == ANTFS_CMD_NONE)
    {
        if (p_command_buffer[ANTFS_COMMAND_OFFSET] == ANTFS_CMD_AUTHENTICATE_ID)
        {
            // Make sure it is the correct host
            if (m_link_host_serial_number.bytes.byte0 != p_command_buffer[HOST_ID_OFFSET_0] ||
               m_link_host_serial_number.bytes.byte1 != p_command_buffer[HOST_ID_OFFSET_1] ||
               m_link_host_serial_number.bytes.byte2 != p_command_buffer[HOST_ID_OFFSET_2] ||
               m_link_host_serial_number.bytes.byte3 != p_command_buffer[HOST_ID_OFFSET_3])
                return;

            m_link_command_in_progress  = ANTFS_CMD_AUTHENTICATE_ID;
            m_authenticate_command_type = p_command_buffer[COMMAND_TYPE_OFFSET];
            m_retry = AUTHENTICATION_RETRIES;
        }
    }

    if (m_link_command_in_progress == ANTFS_CMD_AUTHENTICATE_ID)
    {
        switch (m_authenticate_command_type)
        {
            case COMMAND_TYPE_REQUEST_SERIAL:
                if (control_byte & SEQUENCE_LAST_MESSAGE)
                {
                    // Don't do anything before the burst completes (last burst message received).
                    timeout_start(ANTFS_CONFIG_LINK_COMMAND_TIMEOUT);
                    authenticate_response_transmit(AUTH_RESPONSE_N_A,
                                                   ANTFS_REMOTE_FRIENDLY_NAME_MAX,
                                                   // Send device friendly name if it exists.
                                                   m_initial_parameters.p_remote_friendly_name);
                }
                break;

#if ANTFS_CONFIG_AUTH_TYPE_PASSTHROUGH_ENABLED
            case COMMAND_TYPE_PROCEED:
                if (control_byte & SEQUENCE_LAST_MESSAGE)
                {
                    // Don't do anything before the burst completes (last burst message received).
                    timeout_start(ANTFS_CONFIG_LINK_COMMAND_TIMEOUT);
                    // Proceed directly to transport layer (no authentication required).
                    authenticate_response_transmit(AUTH_RESPONSE_ACCEPT, 0, NULL);
                }
                break;

#endif // ANTFS_CONFIG_AUTH_TYPE_PASSTHROUGH_ENABLED
#if ANTFS_CONFIG_AUTH_TYPE_PAIRING_ENABLED
            case COMMAND_TYPE_REQUEST_PAIR:
                if ((control_byte & SEQUENCE_NUMBER_ROLLOVER) == 0)
                {
                    // First burst packet.

                    // Friendly name length.
                    m_friendly_name.friendly_name_size =
                        p_command_buffer[AUTH_STRING_LENGTH_OFFSET];

                    if (m_friendly_name.friendly_name_size > 0)
                    {
                        if (m_friendly_name.friendly_name_size > ANTFS_FRIENDLY_NAME_MAX)
                        {
                            m_friendly_name.friendly_name_size = ANTFS_FRIENDLY_NAME_MAX;
                        }

                        m_friendly_name.index = 0;
                    }
                }
                else
                {
                    // Next burst packets: read host friendly name.

                    if (m_friendly_name.index < ANTFS_FRIENDLY_NAME_MAX)
                    {
                        uint32_t num_of_bytes = ANTFS_FRIENDLY_NAME_MAX - m_friendly_name.index;
                        if (num_of_bytes > 8u)
                        {
                            num_of_bytes = 8u;
                        }
                        memcpy((uint8_t*)&m_friendly_name.friendly_name[m_friendly_name.index],
                               p_command_buffer,
                               num_of_bytes);
                        m_friendly_name.index += num_of_bytes;
                    }
                }

                if (control_byte & SEQUENCE_LAST_MESSAGE)
                {
                    // Last burst packet.

                    timeout_start(ANTFS_CONFIG_PAIRING_TIMEOUT);
                    if (m_friendly_name.friendly_name_size > 0)
                    {
                        m_friendly_name.is_name_set = true;
                    }

                    m_current_state.sub_state.auth_sub_state = ANTFS_AUTH_SUBSTATE_PAIR;
                    // If pairing is supported, send request to UI.
                    event_queue_write(ANTFS_EVENT_PAIRING_REQUEST);
                }
                break;

#endif // ANTFS_CONFIG_AUTH_TYPE_PAIRING_ENABLED
#if ANTFS_CONFIG_AUTH_TYPE_PASSKEY_ENABLED
            case COMMAND_TYPE_REQUEST_PASSKEY:
                if ((control_byte & SEQUENCE_NUMBER_ROLLOVER) == 0)
                {
                    // First burst packet.

                    // Passkey length.
                    const uint32_t passkey_size = p_command_buffer[AUTH_STRING_LENGTH_OFFSET];

                    // Default the algorithm to accept.
                    response = AUTH_RESPONSE_ACCEPT;

                    // Check if the passkey length is valid.
                    if (passkey_size == ANTFS_PASSKEY_SIZE)
                    {
                        m_passkey_index = 0;
                    }
                    else
                    {
                        // Invalid lenght supplied - the authentication will be rejected.
                        response = AUTH_RESPONSE_REJECT;
                    }
                }
                else
                {
                    // Next burst packets: read host friendly name.

                    if ((response == AUTH_RESPONSE_ACCEPT) &&
                        // Prevent buffer overrun.
                        (m_passkey_index != ANTFS_PASSKEY_SIZE))
                    {
                        // Passkey length was valid and the host supplied key matches so far.
                        uint32_t idx = 0;

                        // Check the current received burst packet for passkey match.
                        do
                        {
                            if (m_initial_parameters.p_pass_key[m_passkey_index++] !=
                                p_command_buffer[idx])
                            {
                                // Reject the authentication request and further processing of
                                // passkey matching if a mismatch is found.
                                response = AUTH_RESPONSE_REJECT;
                                break;
                            }

                            ++idx;
                        }
                        while (idx < BURST_PACKET_SIZE);
                    }
                }

                if (control_byte & SEQUENCE_LAST_MESSAGE)
                {
                    // Last burst packet.

                    if (m_passkey_index < ANTFS_PASSKEY_SIZE)
                    {
                        // We did not get the complete passkey, reject authentication request.
                        response = AUTH_RESPONSE_REJECT;
                    }

                    timeout_start(ANTFS_CONFIG_LINK_COMMAND_TIMEOUT);
                    m_current_state.sub_state.auth_sub_state = ANTFS_AUTH_SUBSTATE_PASSKEY;
                    authenticate_response_transmit(response, 0, NULL);
                }
                break;

#endif // ANTFS_CONFIG_AUTH_TYPE_PASSKEY_ENABLED
            default:
                break;
        }
    }
    else if (p_command_buffer[ANTFS_COMMAND_OFFSET] == ANTFS_CMD_DISCONNECT_ID)
    {
        if (control_byte & SEQUENCE_LAST_MESSAGE)
        {
            // Don't do anything before the burst completes (last burst message received).
            link_layer_transit();
        }
    }
    else if (p_command_buffer[ANTFS_COMMAND_OFFSET] == ANTFS_CMD_PING_ID)
    {
        // Reset timeout.
        timeout_start(ANTFS_CONFIG_LINK_COMMAND_TIMEOUT);
        m_link_command_in_progress = ANTFS_CMD_NONE;
    }
    else
    {
        // No implementation needed.
    }
}


/**@brief Function for decoding an ANT-FS command received at the transport layer.
 *
 * @param[in] control_byte     The command control byte.
 * @param[in] p_command_buffer The ANT-FS command buffer.
 */
static void transport_layer_cmd_decode(uint8_t control_byte, const uint8_t * p_command_buffer)
{
    ulong_union_t host_serial_number = {0};

    if (p_command_buffer[ANTFS_CONNECTION_TYPE_OFFSET] == ANTFS_COMMAND_ID)
    {
        m_link_command_in_progress = p_command_buffer[ANTFS_COMMAND_OFFSET];
    }

    switch (m_link_command_in_progress)
    {
        case ANTFS_CMD_PING_ID:
            // Reset timeout.
            timeout_start(ANTFS_CONFIG_LINK_COMMAND_TIMEOUT);
            m_link_command_in_progress = ANTFS_CMD_NONE;
            break;

        case ANTFS_CMD_DISCONNECT_ID:
            if (control_byte & SEQUENCE_LAST_MESSAGE)
            {
                // Don't do anything before the burst completes (last burst message received).
                link_layer_transit();
            }
            break;

        case ANTFS_CMD_ERASE_ID:
            if (control_byte & SEQUENCE_LAST_MESSAGE)
            {
                // Don't do anything before the burst completes (last burst message received).

                // Requested index.
                m_file_index.bytes.low  = p_command_buffer[DATA_INDEX_OFFSET_LOW];
                m_file_index.bytes.high = p_command_buffer[DATA_INDEX_OFFSET_HIGH];

                // Send erase request to the application.
                event_queue_write(ANTFS_EVENT_ERASE_REQUEST);
                timeout_start(ANTFS_CONFIG_LINK_COMMAND_TIMEOUT);
                m_link_command_in_progress = ANTFS_CMD_ERASE_ID;
            }
            break;

        case ANTFS_CMD_DOWNLOAD_ID:
            if (m_current_state.sub_state.trans_sub_state != ANTFS_TRANS_SUBSTATE_NONE)
            {
                // Ignore the command if we are busy.
                break;
            }

            if ((control_byte & ~SEQUENCE_LAST_MESSAGE) == 0x00)
            {
                // First burst packet.

                if ((m_file_index.bytes.low != p_command_buffer[DATA_INDEX_OFFSET_LOW]) ||
                    (m_file_index.bytes.high != p_command_buffer[DATA_INDEX_OFFSET_HIGH]))
                {
                    // This is a new index, so we can not check the CRC against the previous saved
                    // CRC.

                    // CRC seed checking is made invalid by setting the last saved offset to the
                    // maximum file size.
                    m_saved_crc_offset = ANTFS_MAX_FILE_SIZE;
                }

                // Requested data file index.
                m_file_index.bytes.low  = p_command_buffer[DATA_INDEX_OFFSET_LOW];
                m_file_index.bytes.high = p_command_buffer[DATA_INDEX_OFFSET_HIGH];

                // Initialize current position in the TX burst to the requested offset.
                m_link_burst_index.bytes.byte0 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_0];
                m_link_burst_index.bytes.byte1 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_1];
                m_link_burst_index.bytes.byte2 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_2];
                m_link_burst_index.bytes.byte3 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_3];
            }
            else if (control_byte & SEQUENCE_LAST_MESSAGE)
            {
                // Last burst packet (download command should be two packets long).

                // Get CRC seed from host.
                m_compared_crc  = (uint16_t)p_command_buffer[DATA_INDEX_OFFSET_LOW];
                m_compared_crc |= ((uint16_t)p_command_buffer[DATA_INDEX_OFFSET_HIGH] << 8u);

                // Maximum block size allowed by host.
                m_max_block_size.bytes.byte0 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_0];
                m_max_block_size.bytes.byte1 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_1];
                m_max_block_size.bytes.byte2 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_2];
                m_max_block_size.bytes.byte3 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_3];

                // Initialize number of remaining bytes for this block to the maximum block size.
                m_bytes_remaining.data = m_max_block_size.data;

                if (p_command_buffer[INITIAL_REQUEST_OFFSET])
                {
                    // This request is the start of a new transfer.

                    // Initialize data offset for CRC calculation to the requested data offset.
                    m_saved_crc_offset = m_link_burst_index.data;
                    m_saved_buffer_crc_offset = m_link_burst_index.data;

                    // Use CRC seed provided by host for CRC checking of the data.
                    m_transfer_crc                            = m_compared_crc;
                    m_saved_transfer_crc                      = m_compared_crc;
                    m_saved_buffer_crc                        = m_compared_crc;
                    m_current_state.sub_state.trans_sub_state = ANTFS_TRANS_SUBSTATE_VERIFY_CRC;
                }
                else
                {
                    // This is a request to resume a partially completed transfer.

                    if (m_saved_crc_offset > m_link_burst_index.data)
                    {
                        // We can not check the received CRC seed as the requested offset is before
                        // our last save point.

                        // Set CRC checking as invalid.
                        m_saved_crc_offset = ANTFS_MAX_FILE_SIZE;
                    }
                    else
                    {
                        m_current_state.sub_state.trans_sub_state = ANTFS_TRANS_SUBSTATE_VERIFY_CRC;
                    }
                }

                m_is_data_request_pending = false;

                // Send download request to the application for further handling.
                event_queue_write(ANTFS_EVENT_DOWNLOAD_REQUEST);

                timeout_start(ANTFS_CONFIG_LINK_COMMAND_TIMEOUT);
                m_link_command_in_progress = ANTFS_CMD_DOWNLOAD_ID;
            }
            break;

        case ANTFS_CMD_UPLOAD_REQUEST_ID:
#if ANTFS_CONFIG_UPLOAD_ENABLED
            if ((control_byte & ~SEQUENCE_LAST_MESSAGE) == 0x00)
            {
                // First burst packet.

                if ((m_file_index.bytes.low != p_command_buffer[DATA_INDEX_OFFSET_LOW]) ||
                    (
                        (m_file_index.bytes.high != p_command_buffer[DATA_INDEX_OFFSET_HIGH]) ||
                        (m_current_state.sub_state.trans_sub_state == ANTFS_TRANS_SUBSTATE_NONE)
                    )
                   )
                {
                    // If it is a new index or we completed the last upload.

                    // Get the file index.
                    m_file_index.bytes.low  = p_command_buffer[DATA_INDEX_OFFSET_LOW];
                    m_file_index.bytes.high = p_command_buffer[DATA_INDEX_OFFSET_HIGH];

                    // As this is a new upload, reset save point to the beginning of the file.

                    // Set CRC to zero.
                    m_saved_crc_offset   = 0;
                    m_saved_transfer_crc = 0;
                }

                // Get the upper limit of upload from request message.
                m_max_transfer_index.bytes.byte0 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_0];
                m_max_transfer_index.bytes.byte1 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_1];
                m_max_transfer_index.bytes.byte2 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_2];
                m_max_transfer_index.bytes.byte3 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_3];
            }
            else if (control_byte & SEQUENCE_LAST_MESSAGE)
            {
                // Last burst (second) packet.

                // Get data offset the requested upload will start at.
                m_link_burst_index.bytes.byte0 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_0];
                m_link_burst_index.bytes.byte1 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_1];
                m_link_burst_index.bytes.byte2 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_2];
                m_link_burst_index.bytes.byte3 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_3];

                if (m_link_burst_index.data != ANTFS_MAX_FILE_SIZE)
                {
                    // If this is a new upload.

                    // The data offset specified in the upload request will be used.
                    m_saved_crc_offset = m_link_burst_index.data;

                    m_saved_transfer_crc = 0;
                }

                m_transfer_crc = m_saved_transfer_crc;

                // Send upload request to the application for further handling.
                event_queue_write(ANTFS_EVENT_UPLOAD_REQUEST);

                timeout_start(ANTFS_CONFIG_LINK_COMMAND_TIMEOUT);
                m_link_command_in_progress = ANTFS_CMD_UPLOAD_REQUEST_ID;
            }
#endif  // ANTFS_CONFIG_UPLOAD_ENABLED
            break;

        case ANTFS_CMD_UPLOAD_DATA_ID:
#if ANTFS_CONFIG_UPLOAD_ENABLED
            if ((control_byte & ~SEQUENCE_LAST_MESSAGE) == 0x00)
            {
                // First burst packet.

                if (m_current_state.sub_state.trans_sub_state ==
                    ANTFS_TRANS_SUBSTATE_UPLOAD_WAIT_FOR_DATA)
                {
                    antfs_event_t event;

                    // Get CRC Seed from host.
                    m_compared_crc  = (uint16_t)p_command_buffer[DATA_INDEX_OFFSET_LOW];
                    m_compared_crc |= ((uint16_t)p_command_buffer[DATA_INDEX_OFFSET_HIGH] << 8u);

                    // Set download offset.
                    m_link_burst_index.bytes.byte0 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_0];
                    m_link_burst_index.bytes.byte1 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_1];
                    m_link_burst_index.bytes.byte2 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_2];
                    m_link_burst_index.bytes.byte3 = p_command_buffer[ADDRESS_PARAMETER_OFFSET_3];

                    if ((m_link_burst_index.data + m_block_size.data) < m_max_transfer_index.data)
                    {
                        // Adjust block size as set by client.
                        m_max_transfer_index.data = m_link_burst_index.data + m_block_size.data;
                    }

                    if (m_compared_crc != m_transfer_crc)
                    {
                        // Check that the request matches the CRC sent on the upload response.

                        // Do not accept any data.
                        m_max_transfer_index.data = 0;

                        // Failure will be reported when upload is done.
                        event = (antfs_event_t)0;
                    }

                    // Set ready to receive a file.
                    m_current_state.sub_state.trans_sub_state = ANTFS_TRANS_SUBSTATE_UPLOADING;

                    event          = ANTFS_EVENT_UPLOAD_START;
                    m_transfer_crc = m_compared_crc;

                    if (m_link_burst_index.data > m_max_transfer_index.data)
                    {
                        // If the requested offset is too high.

                        // Clear the max transfer index, so we'll report fail when the transfer
                        // finishes.
                        m_max_transfer_index.data = 0;
                        // Clear the event because we normally would not send an event at this point
                        // in this case.
                        event = (antfs_event_t)0;
                    }

                    if (control_byte & SEQUENCE_LAST_MESSAGE)
                    {
                        // If this upload contains no data.

                        // Leave the upload state.
                        m_current_state.sub_state.trans_sub_state = ANTFS_TRANS_SUBSTATE_NONE;

                        // if it was a valid index, report it as a successful upload, otherwise
                        // report it as a failure.
                        if (event == 0)
                        {
                            event = ANTFS_EVENT_UPLOAD_FAIL;
                        }
                        else
                        {
                            event = ANTFS_EVENT_UPLOAD_COMPLETE;
                        }
                    }

                    if (event != 0)
                    {
                        event_queue_write(event);
                    }
                }
            }
#endif // ANTFS_CONFIG_UPLOAD_ENABLED
            break;

        case ANTFS_CMD_LINK_ID:
            host_serial_number.bytes.byte0 = p_command_buffer[HOST_ID_OFFSET_0];
            host_serial_number.bytes.byte1 = p_command_buffer[HOST_ID_OFFSET_1];
            host_serial_number.bytes.byte2 = p_command_buffer[HOST_ID_OFFSET_2];
            host_serial_number.bytes.byte3 = p_command_buffer[HOST_ID_OFFSET_3];

            if (m_link_host_serial_number.data == host_serial_number.data)
            {
                m_active_beacon_frequency = p_command_buffer[TRANSPORT_CHANNEL_FREQUENCY_OFFSET];
                m_active_beacon_status1_field.parameters.link_period =
                    p_command_buffer[TRANSPORT_MESSAGE_PERIOD_OFFSET];

                const uint32_t err_code = sd_ant_channel_radio_freq_set(ANTFS_CONFIG_CHANNEL_NUMBER,
                                                                        m_active_beacon_frequency);
                APP_ERROR_CHECK(err_code);

                channel_period_set(m_active_beacon_status1_field.parameters.link_period);
            }

            m_link_command_in_progress = 0;
            break;

        default:
            // Don't do anything, this is an invalid message.
            m_link_command_in_progress = 0;
            break;
    }
}


/**@brief Function for handling data upload.
 *
 * @param[in] control_byte     The command control byte.
 * @param[in] p_buffer         The data buffer.
 */
static void upload_data_process(uint8_t control_byte, const uint8_t * p_buffer)
{
#if ANTFS_CONFIG_UPLOAD_ENABLED
    if (control_byte & SEQUENCE_LAST_MESSAGE)
    {
        // Last burst packet: upload complete.

        m_current_state.sub_state.trans_sub_state = ANTFS_TRANS_SUBSTATE_NONE;

        // CRC for data packets contained in this upload block.
        m_compared_crc  = p_buffer[UPLOAD_CRC_OFFSET_LOW ];
        m_compared_crc |= (p_buffer[UPLOAD_CRC_OFFSET_HIGH] << 8u);

        if (m_max_transfer_index.data && (m_compared_crc == m_transfer_crc))
        {
            // CRC OK, upload was completed successfully.
            event_queue_write(ANTFS_EVENT_UPLOAD_COMPLETE);
        }
        else
        {
            // CRC mismatch, upload failed.
            event_queue_write(ANTFS_EVENT_UPLOAD_FAIL);
        }

        m_max_transfer_index.data = 0;
    }
    else
    {
        // Not the last burst packet: upload not complete.

        // Set initial number of bytes to 8 (size of burst packet).
        m_bytes_to_write = BURST_PACKET_SIZE;
        timeout_start(ANTFS_CONFIG_LINK_COMMAND_TIMEOUT);

        if (m_link_burst_index.data > m_max_transfer_index.data)
        {
            // We are past the main index, we do not need to write any more data.
            m_bytes_to_write = 0;
        }
        else
        {
            if ((m_bytes_to_write + m_link_burst_index.data) > m_max_transfer_index.data)
            {
                // if we're less than 8 bytes away from the end, adjust the number of bytes to write
                // in this block.
                m_bytes_to_write = m_max_transfer_index.data - m_link_burst_index.data;
            }
        }

        if (m_bytes_to_write != 0)
        {
            APP_ERROR_CHECK_BOOL(m_bytes_to_write <= BURST_PACKET_SIZE);

            // Store begin of upload data.
            mp_upload_data = p_buffer;

            m_transfer_crc = crc_crc16_update(m_transfer_crc, p_buffer, m_bytes_to_write);

            // Send data to application.
            event_queue_write(ANTFS_EVENT_UPLOAD_DATA);

            // Update current offset.
            m_link_burst_index.data += m_bytes_to_write;

            // Store save point.
            m_saved_crc_offset       = m_link_burst_index.data;
            m_saved_transfer_crc     = m_transfer_crc;
        }
    }
#endif // ANTFS_CONFIG_UPLOAD_ENABLED
}


/**@brief Function for switching to transport layer.
 */
static void transport_layer_transit(void)
{
    if (m_current_state.state != ANTFS_STATE_OFF)
    {
#if ANTFS_CONFIG_DEBUG_LED_ENABLED
        uint32_t err_code = bsp_indication_set(BSP_INDICATE_IDLE);
        APP_ERROR_CHECK(err_code);
#endif // ANTFS_CONFIG_DEBUG_LED_ENABLED
        m_current_state.state                     = ANTFS_STATE_TRANS;
        m_current_state.sub_state.trans_sub_state = ANTFS_TRANS_SUBSTATE_NONE;

        timeout_start(ANTFS_CONFIG_LINK_COMMAND_TIMEOUT);

        beacon_transmit(MESG_BROADCAST_DATA_ID);

        event_queue_write(ANTFS_EVENT_TRANS);
    }
}


void antfs_message_process(uint8_t * p_message)
{
#if ANTFS_CONFIG_DEBUG_LED_ENABLED
    uint32_t err_code;
#endif // ANTFS_CONFIG_DEBUG_LED_ENABLED

    if (p_message != NULL)
    {
        if ((p_message[BUFFER_INDEX_CHANNEL_NUM] & CHANNEL_NUMBER_MASK) != ANTFS_CONFIG_CHANNEL_NUMBER)
        {
            // Only process messages corresponding to the ANT-FS channel here.
            return;
        }

        if ((m_current_state.state == ANTFS_STATE_OFF) &&
            (
                !(
                    (p_message[BUFFER_INDEX_MESG_ID] == MESG_RESPONSE_EVENT_ID) &&
                    (p_message[BUFFER_INDEX_RESPONSE_CODE] == NO_EVENT)
                  )
            )
           )
        {
            return;
        }

        switch (p_message[BUFFER_INDEX_MESG_ID])
        {
            case MESG_BROADCAST_DATA_ID:
                // We are not going to process broadcast messages or pass them to the app to handle.
                break;

            case MESG_ACKNOWLEDGED_DATA_ID:
                // Mark it as being the last message if it's an ack message.
                p_message[ANTFS_CONTROL_OFFSET] |= SEQUENCE_LAST_MESSAGE;

            /* fall-through */
            case MESG_BURST_DATA_ID:
                switch (m_current_state.state)
                {
                    case ANTFS_STATE_LINK:
                        link_layer_cmd_decode(&p_message[ANTFS_DATA_OFFSET]);
                        break;

                    case ANTFS_STATE_AUTH:
                        authenticate_layer_cmd_decode(p_message[ANTFS_CONTROL_OFFSET],
                                                      &p_message[ANTFS_DATA_OFFSET]);
                        break;

                    case ANTFS_STATE_TRANS:
                        if (m_current_state.sub_state.trans_sub_state !=
                            ANTFS_TRANS_SUBSTATE_UPLOADING)
                        {
                            transport_layer_cmd_decode(p_message[ANTFS_CONTROL_OFFSET],
                                                       &p_message[ANTFS_DATA_OFFSET]);
                        }
                        else
                        {
                            upload_data_process(p_message[ANTFS_CONTROL_OFFSET],
                                                &p_message[ANTFS_DATA_OFFSET]);
                        }
                        break;

                    default:
                        // If in any other state or sub-state, do nothing.
                        break;
                }
                break;

            case MESG_RESPONSE_EVENT_ID:
                // Branch on event ID.
                switch (p_message[BUFFER_INDEX_RESPONSE_CODE])
                {
                    case EVENT_TRANSFER_TX_FAILED:
                        m_link_command_in_progress = ANTFS_CMD_NONE;
                        // Switch into the appropriate state after the failure. Must be ready for
                        // the host to do a retry.
                        switch (m_current_state.state)
                        {
                            case ANTFS_STATE_LINK:
                                link_layer_transit();
                                break;

                            case ANTFS_STATE_AUTH:
                                // Burst failed, retry sending the response
                                if (!m_retry)
                                {
                                    authenticate_layer_transit(); // Reload beacon
                                }
                                else
                                {
                                    if (m_current_state.sub_state.auth_sub_state == ANTFS_AUTH_SUBSTATE_ACCEPT)
                                    {
                                        if (m_authenticate_command_type == COMMAND_TYPE_REQUEST_PAIR)
                                        {
                                            authenticate_response_transmit(AUTH_RESPONSE_ACCEPT, ANTFS_PASSKEY_SIZE,
                                               m_initial_parameters.p_pass_key);
                                        }
                                        else
                                        {
                                            authenticate_response_transmit(AUTH_RESPONSE_ACCEPT, 0, NULL);
                                        }
                                    }
                                    else if (m_current_state.sub_state.auth_sub_state == ANTFS_AUTH_SUBSTATE_REJECT)
                                    {
                                        authenticate_response_transmit(AUTH_RESPONSE_REJECT, 0, NULL);
                                    }
                                    else if (m_authenticate_command_type == COMMAND_TYPE_REQUEST_SERIAL)
                                    {
                                        authenticate_response_transmit(AUTH_RESPONSE_N_A,
                                                           ANTFS_REMOTE_FRIENDLY_NAME_MAX,
                                                           // Send device friendly name if it exists.
                                                           m_initial_parameters.p_remote_friendly_name);
                                    }
                                    else
                                    {
                                        // No implementation needed
                                    }

                                    m_retry--;
                                }

                                break;

                            case ANTFS_STATE_TRANS:
                                if (m_current_state.sub_state.trans_sub_state ==
                                    ANTFS_TRANS_SUBSTATE_DOWNLOADING)
                                {
                                    event_queue_write(ANTFS_EVENT_DOWNLOAD_FAIL);
                                }
                                transport_layer_transit();
                                break;

                            default:
                                // No implementation needed.
                                break;
                        }
                        break;

                    case EVENT_TRANSFER_RX_FAILED:
                        m_link_command_in_progress = ANTFS_CMD_NONE;

                        if (m_current_state.sub_state.trans_sub_state ==
                            ANTFS_TRANS_SUBSTATE_UPLOADING)
                        {
                            event_queue_write(ANTFS_EVENT_UPLOAD_FAIL);

                            m_current_state.sub_state.trans_sub_state =
                                ANTFS_TRANS_SUBSTATE_UPLOAD_RESUME;
                        }
                        else
                        {
                            // No implementation needed
                        }

                        break;

                    case EVENT_TRANSFER_TX_COMPLETED:
                        m_link_command_in_progress = ANTFS_CMD_NONE;

                        // Switch into appropiate state after successful command.
                        switch (m_current_state.state)
                        {
                            case ANTFS_STATE_AUTH:
                                if (m_current_state.sub_state.auth_sub_state ==
                                    ANTFS_AUTH_SUBSTATE_ACCEPT)
                                {
                                    // We passed authentication, so go to transport state.
                                    transport_layer_transit();
                                }
                                else if (m_current_state.sub_state.auth_sub_state ==
                                         ANTFS_AUTH_SUBSTATE_REJECT)
                                {
                                    // We failed authentication, so go to link state.
                                    link_layer_transit();
                                }
                                else
                                {
                                    // Reload beacon.
                                    authenticate_layer_transit();
                                }
                                break;

                            case ANTFS_STATE_TRANS:
                                if (m_current_state.sub_state.trans_sub_state ==
                                    ANTFS_TRANS_SUBSTATE_DOWNLOADING)
                                {
                                    event_queue_write(ANTFS_EVENT_DOWNLOAD_COMPLETE);
                                }
                                if (m_current_state.sub_state.trans_sub_state !=
                                    ANTFS_TRANS_SUBSTATE_UPLOAD_WAIT_FOR_DATA)
                                {
                                    transport_layer_transit();  // Reload beacon.
                                }
                                break;

                            default:
                                link_layer_transit();       // Reload beacon.
                                break;
                        }
                        break;

                    case EVENT_TX:
#if ANTFS_CONFIG_DEBUG_LED_ENABLED
                        err_code = bsp_indication_set(BSP_INDICATE_SENT_OK);
                        APP_ERROR_CHECK(err_code);
#endif // ANTFS_CONFIG_DEBUG_LED_ENABLED
                        // Load beacon.
                        beacon_transmit(MESG_BROADCAST_DATA_ID);
                        break;

                    case EVENT_CHANNEL_CLOSED:
                        event_queue_write(ANTFS_EVENT_CLOSE_COMPLETE);
                        break;

                    case NO_EVENT:
                        // This shouldn't happen... command responses should not occur.
                        APP_ERROR_HANDLER(p_message[BUFFER_INDEX_RESPONSE_CODE]);
                        break;

                    default:
                        // No implementation needed.
                        return;
                }
                break;

            default:
                // No implementation needed.
                return;
        }
    }
}


void antfs_channel_setup(void)
{
    // Start channel configuration.
    uint32_t err_code = ant_fs_key_set(ANTFS_CONFIG_NETWORK_NUMBER);
    APP_ERROR_CHECK(err_code);

    err_code = sd_ant_channel_assign(ANTFS_CONFIG_CHANNEL_NUMBER,
                                     ANTFS_CHANNEL_TYPE,
                                     ANTFS_CONFIG_NETWORK_NUMBER,
                                     0);
    APP_ERROR_CHECK(err_code);

    // Use the lower 2 bytes of the ESN for device number.
    uint16_t device_number = (uint16_t)(m_initial_parameters.client_serial_number & 0x0000FFFFu);
    if (device_number == 0)
    {
        // Device number of 0 is not allowed.
        device_number = 2;
    }

    err_code = sd_ant_channel_id_set(ANTFS_CONFIG_CHANNEL_NUMBER,
                                     device_number,
                                     ANTFS_CONFIG_DEVICE_TYPE,
                                     ANTFS_CONFIG_TRANS_TYPE);
    APP_ERROR_CHECK(err_code);

    // Remain in initialization state until channel is open.
    m_current_state.state = ANTFS_STATE_INIT;
    // @note: Channel frequency is set by function below.
    link_layer_transit();
    m_current_state.state = ANTFS_STATE_INIT;

    channel_period_set(m_active_beacon_status1_field.parameters.link_period);

    err_code = sd_ant_channel_open(ANTFS_CONFIG_CHANNEL_NUMBER);
    APP_ERROR_CHECK(err_code);

    err_code = sd_ant_channel_radio_tx_power_set(ANTFS_CONFIG_CHANNEL_NUMBER,
                                                 ANTFS_CONFIG_TRANSMIT_POWER,
                                                 ANTFS_CONFIG_CUSTOM_TRANSMIT_POWER);
    APP_ERROR_CHECK(err_code);

    m_current_state.state                    = ANTFS_STATE_LINK;
    m_current_state.sub_state.link_sub_state = ANTFS_LINK_SUBSTATE_NONE;

    event_queue_write(ANTFS_EVENT_OPEN_COMPLETE);

    // Start beacon broadcast.
    beacon_transmit(MESG_BROADCAST_DATA_ID);
}


/**@brief Function for resetting the ANT-FS state machine.
 */
static void state_machine_reset(void)
{
    m_current_state.state      = ANTFS_STATE_OFF;
    m_link_command_in_progress = ANTFS_CMD_NONE;

    timeout_disable();

    // Reset the ANT-FS event queue.
    m_event_queue.p_queue = m_event_queue_buffer;
    m_event_queue.head    = 0;
    m_event_queue.tail    = 0;

    // Set as invalid.
    m_authenticate_command_type = 0xFFu;
    m_retry = 0;

    m_saved_crc_offset        = 0xFFFFFFFFu;
    m_max_transfer_index.data = 0;
    m_is_crc_pending          = false;
    m_is_data_request_pending = false;

    m_friendly_name.is_name_set = false;
    m_friendly_name.index       = 0;

    memset(m_friendly_name.friendly_name, 0, ANTFS_FRIENDLY_NAME_MAX);
}


/**@brief Function for ANT-FS timer event.
 *
 * Handles pairing and command timeouts.
 *
 * @param[in] p_context        The callback context.
 */
static void timeout_handle(void * p_context)
{
    if (m_current_state.state == ANTFS_STATE_OFF)
    {
        return;
    }

    if ((m_current_state.state == ANTFS_STATE_AUTH) &&
        // Pairing timeout.
        (m_current_state.sub_state.auth_sub_state == ANTFS_AUTH_SUBSTATE_PAIR))
    {
        // Reject authentication request and send pairing timeout event.
        authenticate_response_transmit(AUTH_RESPONSE_REJECT, 0, NULL);
        event_queue_write(ANTFS_EVENT_PAIRING_TIMEOUT);
    }

    // Fall back to link layer when an ANT-FS event times out.
    link_layer_transit();
}


void antfs_init(const antfs_params_t * const p_params,
                antfs_burst_wait_handler_t burst_wait_handler)
{
    m_initial_parameters          = *p_params;
    m_burst_wait_handler          = burst_wait_handler;
    m_active_beacon_status1_field = m_initial_parameters.beacon_status_byte1;

    uint32_t err_code = app_timer_create(&m_timer_id, APP_TIMER_MODE_SINGLE_SHOT, timeout_handle);
    APP_ERROR_CHECK(err_code);

    state_machine_reset();

    err_code = sd_ant_burst_handler_wait_flag_enable((uint8_t *)(&m_burst_wait));
    APP_ERROR_CHECK(err_code);
}
#endif // NRF_MODULE_ENABLED(ANTFS)
