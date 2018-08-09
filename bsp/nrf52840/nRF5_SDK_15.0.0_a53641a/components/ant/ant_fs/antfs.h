/**
 * This software is subject to the ANT+ Shared Source License
 * www.thisisant.com/swlicenses
 * Copyright (c) Dynastream Innovations, Inc. 2012
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 * 1) Redistributions of source code must retain the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer.
 * 
 * 2) Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 * 
 * 3) Neither the name of Dynastream nor the names of its
 *    contributors may be used to endorse or promote products
 *    derived from this software without specific prior
 *    written permission.
 * 
 * The following actions are prohibited:
 * 1) Redistribution of source code containing the ANT+ Network
 *    Key. The ANT+ Network Key is available to ANT+ Adopters.
 *    Please refer to http://thisisant.com to become an ANT+
 *    Adopter and access the key.
 * 
 * 2) Reverse engineering, decompilation, and/or disassembly of
 *    software provided in binary form under this license.
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
/**@file
 * @brief The ANT-FS client protocol interface.
 * This file is based on implementation originally made by Dynastream Innovations Inc. - August 2012
 * @defgroup ant_fs ANT-FS client device simulator
 * @{
 * @ingroup ant_sdk_utils
 *
 * @brief The ANT-FS client device simulator.
 *
 * @note The ANT-FS Network Key is available for ANT+ Adopters. Please refer to http://thisisant.com to become an ANT+ Adopter and access the key.
 */

#ifndef ANTFS_H__
#define ANTFS_H__

#include <stdint.h>
#include <stdbool.h>
#include "defines.h"
#include "sdk_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ANTFS_VERSION_MAJOR               1u                                                                                             /**< Version major number. */
#define ANTFS_VERSION_MINOR               0                                                                                              /**< Version minor number. */
#define ANTFS_VERSION_ITERATION           0                                                                                              /**< Version iteration. */
#define ANTFS_VERSION_TYPE                'R'                                                                                            /**< Version type is release. */
#define ANTFS_VERSION_SPEC                '0.AK'                                                                                         /**< Version of the ANT-FS Technology Specification. */
#define ANTFS_DIR_STRUCT_VERSION          1u                                                                                             /**< Version of the directory file structure. */
#define ANTFS_VERSION_DATE                20090522u                                                                                      /**< Version date. */

// ANT-FS options.
#define ANTFS_LINK_FREQ                   50u                                                                                            /**< RF Frequency (+2400MHz). */
#define ANTFS_CHANNEL_TYPE                CHANNEL_TYPE_MASTER                                                                            /**< ANT-FS Client Channel Type. */
#define ANTFS_AUTH_STRING_MAX             255u                                                                                           /**< Maximum size of authentication strings (passkey/friendly name). */
#define ANTFS_PASSKEY_SIZE                16u                                                                                            /**< Passkey size. */
#define ANTFS_FRIENDLY_NAME_MAX           16u                                                                                            /**< Maximum size of friendly name received from host. */
#define ANTFS_REMOTE_FRIENDLY_NAME_MAX    16u                                                                                            /**< Maximum size of client's friendly name. */

// Beacon definitions.
#define BEACON_PERIOD_SHIFT               0x00                                                                                           /**< Shift value for masking out beacon period. */
#define BEACON_PERIOD_MASK                (0x07u << BEACON_PERIOD_SHIFT)                                                                 /**< Beacon period bitmask. */
#define BEACON_PERIOD_0_5_HZ              (0x00  << BEACON_PERIOD_SHIFT)                                                                 /**< Value for 0,5Hz beacon period. */
#define BEACON_PERIOD_1_HZ                (0x01u << BEACON_PERIOD_SHIFT)                                                                 /**< Value for 1Hz beacon period. */
#define BEACON_PERIOD_2_HZ                (0x02u << BEACON_PERIOD_SHIFT)                                                                 /**< Value for 2Hz beacon period. */
#define BEACON_PERIOD_4_HZ                (0x03u << BEACON_PERIOD_SHIFT)                                                                 /**< Value for 4Hz beacon period. */
#define BEACON_PERIOD_8_HZ                (0x04u << BEACON_PERIOD_SHIFT)                                                                 /**< Value for 8Hz beacon period. */
#define PAIRING_AVAILABLE_FLAG_SHIFT      0x03u                                                                                          /**< Shift value for masking out pairing enabled bit. */
#define PAIRING_AVAILABLE_FLAG_MASK       (0x01u << PAIRING_AVAILABLE_FLAG_SHIFT)                                                        /**< Pairing enabled bitmask. */
#define UPLOAD_ENABLED_FLAG_SHIFT         0x04u                                                                                          /**< Shift value for masking out upload enabled bit. */
#define UPLOAD_ENABLED_FLAG_MASK          (0x01u << UPLOAD_ENABLED_FLAG_SHIFT)                                                           /**< Upload enabled bitmask. */
#define DATA_AVAILABLE_FLAG_SHIFT         0x05u                                                                                          /**< Shift value for masking out data available bit. */
#define DATA_AVAILABLE_FLAG_MASK          (0x01u << DATA_AVAILABLE_FLAG_SHIFT)                                                           /**< Data available bitmask. */

#if ANTFS_ENABLED
// Build the default beacon settings.
#if ANTFS_CONFIG_AUTH_TYPE_PAIRING_ENABLED
   #define ANTFS_PAIRING_BIT              PAIRING_AVAILABLE_FLAG_MASK                                                                    /**< Build pairing enabled default beacon setting. */
#else
   #define ANTFS_PAIRING_BIT              0x00u                                                                                          /**< Build pairing disabled default beacon setting. */
#endif // ANTFS_CONFIG_AUTH_TYPE_PAIRING_ENABLED
#if ANTFS_CONFIG_UPLOAD_ENABLED
   #define ANTFS_UPLOAD_BIT               UPLOAD_ENABLED_FLAG_MASK                                                                       /**< Build upload enabled default beacon setting. */
#else
   #define ANTFS_UPLOAD_BIT               0x00u                                                                                          /**< Build upload disabled default beacon setting. */
#endif // ANTFS_CONFIG_UPLOAD_ENABLED

#define ANTFS_DEFAULT_BEACON              (ANTFS_CONFIG_BEACON_STATUS_PERIOD | ANTFS_UPLOAD_BIT | ANTFS_PAIRING_BIT | DATA_AVAILABLE_FLAG_MASK) /**< Define the default beacon setting. */
#endif // ANTFS_ENABLED

// Download/Upload responses.
#define RESPONSE_MESSAGE_OK               0x00u                                                                                          /**< Download request ok. */
#define RESPONSE_MESSAGE_NOT_EXIST        0x01u                                                                                          /**< File does not exist. */
#define RESPONSE_MESSAGE_NOT_AVAILABLE    0x02u                                                                                          /**< File can not be read/written to (download/upload respectively). */
#define RESPONSE_INVALID_OPERATION        0x04u                                                                                          /**< Request invalid. */
// Download responses.
#define RESPONSE_MESSAGE_NOT_READY        0x03u                                                                                          /**< Not ready to download. */
#define RESPONSE_INVALID_CRC              0x05u                                                                                          /**< CRC incorrect. */
// Upload responses.
#define RESPONSE_MESSAGE_NOT_ENOUGH_SPACE 0x03u                                                                                          /**< Not enough space to to complete write. */
#define RESPONSE_MESSAGE_UPLOAD_NOT_READY 0x05u                                                                                          /**< Not ready to upload */
// Upload/Erase responses.
#define RESPONSE_MESSAGE_FAIL             0x01u                                                                                          /**< Data File Index does not exist / Erase failed. */

// Directory general file flags.
#define ANTFS_DIR_READ_MASK               0x80u                                                                                          /**< Read (can download). */
#define ANTFS_DIR_WRITE_MASK              0x40u                                                                                          /**< Write (can upload). */
#define ANTFS_DIR_ERASE_MASK              0x20u                                                                                          /**< Erase (can erase). */
#define ANTFS_DIR_ARCHIVE_MASK            0x10u                                                                                          /**< Archive (has been downloaded). */
#define ANTFS_DIR_APPEND_MASK             0x08u                                                                                          /**< Append (can append to file only). */

#define ANTFS_MAX_FILE_SIZE               0xFFFFFFFFu                                                                                    /**< Maximum file size, as specified by directory structure. */
#define ANTFS_BURST_BLOCK_SIZE            16u                                                                                            /**< Size of each block of burst data that the client attempts to send when it processes a data request event. */

/**@brief ANT-FS beacon status. */
typedef union
{
    uint32_t        status;                                     /**< Beacon status byte 1. */

    struct
    {
        uint8_t     link_period         : 3;                    /**< Beacon period (0.5 - 8 Hz). */
        bool        is_pairing_enabled  : 1;                    /**< Pairing is enabled/disabled. */
        bool        is_upload_enabled   : 1;                    /**< Upload is enabled/disabled. */
        bool        is_data_available   : 1;                    /**< Data is available for download / no data available. */
        uint8_t     reserved            : 2;                    /**< Reserved. */
    } parameters;
} antfs_beacon_status_byte1_t;

// ANT-FS states.
typedef enum
{
    ANTFS_STATE_OFF,                                            /**< Off state. */
    ANTFS_STATE_INIT,                                           /**< Init state. */
    ANTFS_STATE_LINK,                                           /**< Link state. */
    ANTFS_STATE_AUTH,                                           /**< Authenticate state. */
    ANTFS_STATE_TRANS                                           /**< Transport state. */
} antfs_state_t;

// ANT-FS link layer substates.
typedef enum
{
    ANTFS_LINK_SUBSTATE_NONE                                    /**< None state. */
} antfs_link_substate_t;

// ANT-FS authenticate layer substates. */
typedef enum
{
    ANTFS_AUTH_SUBSTATE_NONE,                                   /**< None state. */
    ANTFS_AUTH_SUBSTATE_PAIR,                                   /**< Pairing state. */
    ANTFS_AUTH_SUBSTATE_PASSKEY,                                /**< Passkey state. */
    ANTFS_AUTH_SUBSTATE_ACCEPT,                                 /**< Authenticate accept state. */
    ANTFS_AUTH_SUBSTATE_REJECT                                  /**< Authenticate reject state. */
} antfs_authenticate_substate_t;

// ANT-FS transport layer substates. */
typedef enum
{
    ANTFS_TRANS_SUBSTATE_NONE,                                  /**< None state. */
    ANTFS_TRANS_SUBSTATE_VERIFY_CRC,                            /**< Verify CRC state. */
    ANTFS_TRANS_SUBSTATE_DOWNLOADING,                           /**< Downloading state. */
    ANTFS_TRANS_SUBSTATE_UPLOAD_WAIT_FOR_DATA,                  /**< Wait for upload data request state. */
    ANTFS_TRANS_SUBSTATE_UPLOADING,                             /**< Ready / receiving upload data state. */
    ANTFS_TRANS_SUBSTATE_UPLOAD_RESUME                          /**< RX failure upon receiving upload data state. */
} antfs_transport_substate_t;

// ANT-FS Events.
typedef enum
{
    ANTFS_EVENT_PAIRING_REQUEST =       0xB0,                   /**< Pairing request event. */
    ANTFS_EVENT_PAIRING_TIMEOUT =       0xB1,                   /**< Pairing timeout event. */
    ANTFS_EVENT_OPEN_COMPLETE =         0xB2,                   /**< Channel setup complete event. */
    ANTFS_EVENT_CLOSE_COMPLETE =        0xB4,                   /**< Channel closed event. */
    ANTFS_EVENT_LINK =                  0xB6,                   /**< Enter link layer event. */
    ANTFS_EVENT_AUTH =                  0xB7,                   /**< Enter authenticate layer event. */
    ANTFS_EVENT_TRANS =                 0xB8,                   /**< Enter transport layer event. */
    ANTFS_EVENT_DOWNLOAD_REQUEST =      0xB9,                   /**< Download request event. */
    ANTFS_EVENT_DOWNLOAD_REQUEST_DATA = 0xBA,                   /**< Download request data event. */
    ANTFS_EVENT_DOWNLOAD_START  =       0xBB,                   /**< Download started event. */
    ANTFS_EVENT_DOWNLOAD_COMPLETE =     0xBC,                   /**< Download completed event. */
    ANTFS_EVENT_DOWNLOAD_FAIL =         0xBD,                   /**< Download failed event. */
    ANTFS_EVENT_UPLOAD_REQUEST =        0xBE,                   /**< Upload request event. */
    ANTFS_EVENT_UPLOAD_DATA =           0xBF,                   /**< Upload data available for read event. */
    ANTFS_EVENT_UPLOAD_START  =         0xC0,                   /**< Upload begin event. */
    ANTFS_EVENT_UPLOAD_COMPLETE =       0xC1,                   /**< Upload completed event. */
    ANTFS_EVENT_UPLOAD_FAIL =           0xC2,                   /**< Upload process failed event. */
    ANTFS_EVENT_ERASE_REQUEST =         0xC3                    /**< Erase request event. */
} antfs_event_t;

/**@brief ANT-FS <-> application event communication object. */
typedef struct
{
    antfs_event_t event;                                        /**< ANT-FS event. */
    uint16_t      file_index;                                   /**< File index (download/upload/erase). */
    uint32_t      offset;                                       /**< Current offset (download/upload). */
    uint32_t      bytes;                                        /**< Number of bytes in block (download/upload). */
    uint16_t      crc;                                          /**< Current CRC (upload). */
    uint8_t       data[8];                                      /**< Block of data (upload). */
} antfs_event_return_t;

/**@brief ANT-FS parameters. */
typedef struct
{
    uint32_t                    client_serial_number;           /**< Client serial number. */
    uint16_t                    beacon_device_type;             /**< Client device type. */
    uint16_t                    beacon_device_manufacturing_id; /**< Client manufacturing ID. */
    uint8_t                     beacon_frequency;               /**< Beacon RF Frequency. */
    antfs_beacon_status_byte1_t beacon_status_byte1;            /**< Beacon status byte 1. */
    const uint8_t *             p_pass_key;                     /**< Pass Key. */
    const uint8_t *             p_remote_friendly_name;         /**< Friendly Name. */
} antfs_params_t;

/**@brief ANT-FS directory header. */
typedef struct
{
    uint8_t  version;                                           /**< Version of the directory file structure. */
    uint8_t  length;                                            /**< Length of each structure, in bytes. */
    uint8_t  time_format;                                       /**< Defines how system keeps track of date/time stamps. */
    uint8_t  reserved01;
    uint8_t  reserved02;
    uint8_t  reserved03;
    uint8_t  reserved04;
    uint8_t  reserved05;
    uint32_t system_time;                                       /**< Number of seconds elapsed since system power up. */
    uint32_t date;                                              /**< Number of seconds elapsed since 00:00 hrs Dec 31, 1989. If system time is unknown, used as counter. */
} antfs_dir_header_t;

/**@brief ANT-FS directory entry. */
typedef struct
{
    uint16_t data_file_index;                                   /**< Data file index. */
    uint8_t  file_data_type;                                    /**< File data type. */
    uint8_t  user_defined1;                                     /**< Identifier, first byte (structure defined by data type). */
    uint16_t user_defined2;                                     /**< Identifier, last two bytes (structure defined by data type). */
    uint8_t  user_flags;                                        /**< File data type specific flags (bits defined by data type). */
    uint8_t  general_flags;                                     /**< Bit mapped flags of flag permissions. */
    uint32_t file_size_in_bytes;                                /**< File size, in bytes. */
    uint32_t date;                                              /**< Number of seconds elapsed since 00:00 hrs Dec 31, 1980, if supported. */
} antfs_dir_struct_t;

/**@brief ANT-FS download/upload request context. */
typedef struct
{
    ulong_union_t  file_size;                                   /**< Size of a file to download when reading, or the size of a partially completed upload when writing. */
    uint32_t       max_file_size;                               /**< The maximum size of the file specified, this is the file size when reading, and the maximum allowed file size when writing. */
    ulong_union_t  max_burst_block_size;                        /**< Maximum burst block size. */
    ushort_union_t file_index;                                  /**< File index. */
    uint16_t       file_crc;                                    /**< CRC (uploads). */
} antfs_request_info_t;

/**@brief The burst wait handler can be configured by the application to customize the code that is
 * executed while waiting for the burst busy flag. */
typedef void(*antfs_burst_wait_handler_t)(void);

/**@brief Function for setting initial ANT-FS configuration parameters.
 *
 * @param[in] p_params                 The initial ANT-FS configuration parameters.
 * @param[in] burst_wait_handler       Burst wait handler.
 */
void antfs_init(const antfs_params_t * const    p_params,
                antfs_burst_wait_handler_t      burst_wait_handler);

/**@brief Function for getting host name if received.
 *
 * @return Pointer to host name buffer if a host name was recieved, NULL otherwise.
 */
const char * antfs_hostname_get(void);

/**@brief Function for transmitting a response to a pairing request issued by ANT-FS host.
 *
 * @param[in] accept              The pairing response, true if pairing accepted.
 *
 * @retval true  Operation success. Response to a pairing request was transmitted.
 * @retval false Operation failure. Not in pairing mode or pairing not supported by the
 *               implementation.
 */
bool antfs_pairing_resp_transmit(bool accept);

/**@brief Function for doing calculations prior downloading the data to the ANT-FS host.
 *
 * Function does the necessary pre processing calculations, which are required prior downloading the
 * data, and also transmits the download request response right away in case of the download request
 * was rejected or there is no data to send.
 *
 * @param[in] response            The download request response code.
 * @param[in] p_request_info      ANT-FS request info structure.
 */
void antfs_download_req_resp_prepare(uint8_t                            response,
                                     const antfs_request_info_t * const p_request_info);

/**@brief Function for downloading requested data.
 *
 * @param[in] index               Index of the current file downloaded.
 * @param[in] offset              Offset specified by client.
 * @param[in] num_bytes           Number of bytes requested to be transmitted from the buffer.
 * @param[in] p_message           Data buffer to be transmitted.
 *
 * @return Number of data bytes transmitted.
 */
uint32_t antfs_input_data_download(uint16_t index,
                                   uint32_t offset,
                                   uint32_t num_bytes,
                                   const uint8_t * const p_message);

/**@brief Function for transmitting upload request response to a upload request command by ANT-FS
 *        host.
 *
 * @param[in] response            The upload response code.
 * @param[in] p_request_info      ANT-FS request info structure.
 *
 * @retval true  Operation success. Response to upload request command was transmitted.
 * @retval false Operation failure. Upload not supported by the implementation or not in correct
 *                                  state or application is sending a response for a different file
 *                                  than requested.
 */
bool antfs_upload_req_resp_transmit(uint8_t                            response,
                                    const antfs_request_info_t * const p_request_info);

/**@brief Function for transmitting upload data response to a upload data command by ANT-FS host.
 *
 * @param[in] data_upload_success The upload response code, true for success.
 *
 * @retval true  Operation success. Response to upload data command was transmitted.
 * @retval false Operation failure. Upload not supported by the implementation or not in correct
 *                                  state.
 */
bool antfs_upload_data_resp_transmit(bool data_upload_success);

/**@brief Function for transmitting erase response to a erase request.
 *
 * @param[in] response            The erase response code.
 */
void antfs_erase_req_resp_transmit(uint8_t response);

/**@brief Function for extracting possible pending ANT-FS event.
 *
 * @param[out] p_event            The output event structure.
 *
 * @retval true  Operation success. Pending ANT-FS event available and it was copied to the output
 *                                  event structure.
 * @retval false Operation failure. No pending ANT-FS event available.
 */
bool antfs_event_extract(antfs_event_return_t * const p_event);

/**@brief Function for processing ANT events and data received from the ANT-FS channel.
 *
 * @param[in] p_message           The message buffer containing the message received from the ANT-FS
 *                                channel.
 */
void antfs_message_process(uint8_t * p_message);

/**@brief Function for setting up the ANT-FS channel.
 */
void antfs_channel_setup(void);


#ifdef __cplusplus
}
#endif

#endif // ANTFS_H__

/**
 *@}
 **/
