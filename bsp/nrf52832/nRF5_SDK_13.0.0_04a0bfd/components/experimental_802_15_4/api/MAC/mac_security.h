/**
 * Copyright (c) 2016 - 2017 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 * 
 * All Rights Reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
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
#ifndef MAC_SECURITY_H_INCLUDED
#define MAC_SECURITY_H_INCLUDED

#include "sys_queue.h"
#include "sec_aes_ccm.h"

/** @file
 * The MAC MLME Security module declares the MAC Security types
 * according to the MAC specification.
 *
 * @defgroup mac_security MAC MLME Security API
 * @ingroup mac_15_4
 * @{
 * @brief Module to declare MAC MLME Security API.
 * @details The MAC Security module declares types/macros needed to implement and use the MAC security
 * engine according to the MAC specification. No routines or callbacks are declared here.
 */

/**
 * @brief  MAC sublayer security levels.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.6.2.2.1
 */
typedef enum
{
    MAC_SEC_OFF        = 0,            /**< Security is OFF. */
    MAC_SEC_MIC32,                     /**< MIC32 security. */
    MAC_SEC_MIC64,                     /**< MIC64 security. */
    MAC_SEC_MIC128,                    /**< MIC128 security. */
    MAC_SEC_ENC,                       /**< ENC security. */
    MAC_SEC_ENC_MIC32,                 /**< ENC/MIC32 security. */
    MAC_SEC_ENC_MIC64,                 /**< ENC/MIC64 security. */
    MAC_SEC_ENC_MIC128                 /**< ENC/MIC128 security. */
} mac_security_level_t;


/**
 * @brief  MAC key identifier mode.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.6.2.2.2
 */
typedef enum
{
    MAC_KEY_ID_IMPL        = 0,        /**< Impl. */
    MAC_KEY_ID_ONE_OCTET,              /**< One octet. */
    MAC_KEY_ID_FOUR_OCTET,             /**< 4 octets. */
    MAC_KEY_ID_EIGHT_OCTET             /**< 8 octets. */
} mac_key_id_mode_t;

/**@brief Size (in bytes) of short security look up item. This size is
 * set when lookup size equals to 0.
 */
#define MAC_LOOKUP_DATA_SIZE_SHORT           5

/**@brief Size (in bytes) of long security Key look up item. This size is
 * set when lookup size equals to 1.
 */
#define MAC_KEY_LOOKUP_DATA_SIZE_LONG        9

/**@brief Size (in bytes) of long security Data look up item. This size is
 * set when lookup size equals to 1.
 */
#define MAC_DATA_LOOKUP_DATA_SIZE_LONG       8

/**@brief Length of \a mac_key_source_t. Equals to extended address length. */
#define MAC_KEY_SOURCE_SIZE                  8

/**@brief This bit-mask is used to get UniqueDevice field value of
 * \a mac_key_device_descr_t.
 */
#define MAC_KEY_DEVICE_FLAG_UNIQUE           0x01

/**@brief This bit-mask is used to get BlackListed field value of
 * \a mac_key_device_descr_t.
 */
#define MAC_KEY_DEVICE_FLAG_BLACKLISTED      0x02

/**@brief Length of key. */
#define MAC_SECURITY_KEY_SIZE                16

/**@brief Length of nonce for aes-ccm algorithm .*/
#define MAC_SECURITY_NONCE_SIZE              13

/**@brief Maximum MIC size .*/
#define MAX_MIC_SIZE                         16

/**@brief This type is used to store security key .*/
typedef uint8_t mac_key_t[MAC_SECURITY_KEY_SIZE];

/**@brief This type is used to store security key lookup data .*/
typedef uint8_t mac_key_lookup_data_t[MAC_KEY_LOOKUP_DATA_SIZE_LONG];

/**@brief This type is used to store security data lookup data .*/
typedef uint8_t mac_data_lookup_data_t[MAC_DATA_LOOKUP_DATA_SIZE_LONG];

/**@brief This type is used to store security key source address .*/
typedef uint64_t mac_key_source_t;

/**@brief This type represents key LookupDataSize according to Table 94 .*/
typedef enum
{
    KEY_LOOKUP_SIZE_FIVE  = 0,         /**< Size is 5. */
    KEY_LOOKUP_SIZE_NINE  = 1          /**< Size is 9. */
} mac_key_lookup_size_t;

/**@brief This type represents real size of key LookupData .*/
typedef enum
{
    KEY_LOOKUP_SIZE_FIVE_VAL  = 5,     /**< Size is 5. */
    KEY_LOOKUP_SIZE_NINE_VAL  = 9      /**< Size is 9. */
} mac_key_lookup_size_val_t;

/**@brief This type represents data LookupDataSize .*/
typedef enum
{
    DATA_LOOKUP_SIZE_FOUR_VAL  = 4,    /**< Size is 4. */
    DATA_LOOKUP_SIZE_EIGHT_VAL = 8     /**< Size is 8. */
} mac_data_lookup_size_val_t;

/**@brief Abstract type to work with growing tables such as some of MAC
 * security attributes.
 */
typedef struct
{
    sys_queue_t                   queue;             /**< Service field .*/
    uint8_t                       size;              /**< Number of currently allocated
                                                          items inside the table .*/
} mac_table_t;

/**@brief Due to processing algorithm this field MUST be the first inside a
 * table or list.
 */
typedef struct
{
    sys_queue_item_t              item;              /**< Service field .*/
    uint8_t                       idx;               /**< Index inside table .*/
} mac_table_item_t;

/**@brief KeyIdLookupDescriptor as described in Table 94 .*/
typedef struct
{
    mac_table_item_t              table_service;     /**< Service field .*/
    mac_key_lookup_data_t         data;              /**< Set of 5 or 9 bytes.
                                                          Data used to identify the key .*/
    mac_key_lookup_size_t         size;              /**< A value of LOOKUP_SIZE_FIVE indicates a set
                                                          of 5 bytes; a value of LOOKUP_SIZE_NINE
                                                          indicates a set of 9 bytes .*/
} mac_key_id_lookup_descr_t;


/**@brief KeyIdLookupLis as described in Table 89 .*/
typedef mac_table_t mac_key_id_lookup_list_t;


/**@brief DeviceDescriptor as described in Table 93 .*/
typedef struct
{
    mac_table_item_t              table_service;     /**< Service field .*/
    uint16_t                      pan_id;            /**< The 16-bit PAN identifier of the device in
                                                          this DeviceDescriptor .*/
    uint16_t                      short_address;     /**< The 16-bit short address of the device in
                                                          this DeviceDescriptor. A value of
                                                          #MAC_EXTENDED_ADDRESS_ONLY
                                                          indicates that this device is using only its
                                                          extended address. A value of
                                                          #MAC_BROADCAST_SHORT_ADDRESS
                                                          indicates that this value is unknown .*/
    uint64_t                      extended_address;  /**< The 64-bit IEEE extended address of the
                                                          device in this DeviceDescriptor. This
                                                          element is also used in unsecuring
                                                          operations on incoming frames .*/
    uint32_t                      frame_counter;     /**< The incoming frame counter of the device
                                                          in this DeviceDescriptor. This value is used
                                                          to ensure sequential freshness of frames .*/
    bool                          exempt;            /**< Indication of whether the device may
                                                          override the minimum security level
                                                          settings defined in \a mac_security_level_table_t .*/
} mac_device_descr_t;


/**@brief DeviceTable as described in Table 93 .*/
typedef mac_table_t mac_device_table_t;


/**@brief KeyDeviceDescriptor as described in Table 91 .*/
typedef struct
{
    mac_table_item_t              table_service;     /**< Service field .*/
    uint8_t                       device_handle;     /**< Handle to the DeviceDescriptor
                                                          corresponding to the device (see
                                                          \a mac_device_descr_t).
                                                          The value is an index of the device descriptor
                                                          instance from device table .*/
    uint8_t                       unique_device : 1; /**< Indication of whether the device indicated
                                                          by DeviceDescriptorHandle is uniquely
                                                          associated with the KeyDescriptor, i.e., it
                                                          is a link key as opposed to a group key .*/
    uint8_t                       blacklisted : 1;   /**< Indication of whether the device indicated
                                                          by DeviceDescriptorHandle previously
                                                          communicated with this key prior to the
                                                          exhaustion of the frame counter. If TRUE,
                                                          this indicates that the device shall not use
                                                          this key further because it exhausted its
                                                          use of the frame counter used with this
                                                          key .*/
} mac_key_device_descr_t;


/**@brief KeyDeviceList as described in Table 89 .*/
typedef mac_table_t mac_key_device_list_t;


/**@brief KeyUsageDescriptor as described in Table 90 .*/
typedef struct
{
    mac_table_item_t          table_service;         /**< Service field .*/

    uint8_t                   frame_type : 3;        /**< See \a mac_frame_type_t .*/
    uint8_t                   cmd_frame_id : 4;      /**< See \a mac_command_id_t .*/
} mac_key_usage_descr_t;


/**@brief KeyUsageList as described in Table 89 .*/
typedef mac_table_t mac_key_usage_list_t;


/**@brief KeyDescriptor as described in Table 89 .*/
typedef struct
{
    mac_table_item_t              table_service;     /**< Service field .*/
    mac_key_id_lookup_list_t      id_lookup_list;    /**< A list of KeyIdLookupDescriptor entries
                                                          used to identify this KeyDescriptor .*/
    mac_key_device_list_t         key_device_list;   /**< A list of KeyDeviceDescriptor entries
                                                          indicating which devices are currently
                                                          using this key, including their blacklist
                                                          status .*/
    mac_key_usage_list_t          key_usage_list;    /**< A list of KeyUsageDescriptor entries
                                                          indicating which frame types this key may
                                                          be used with .*/
    mac_key_t                     key;               /**< The actual value of the key .*/
} mac_key_descr_t;


/**@brief KeyTable as described in Table 88 .*/
typedef mac_table_t mac_key_table_t;


/**@brief SecurityLevelDescriptor as described in Table 93 .*/
typedef struct
{
    mac_table_item_t          table_service;         /**< Service field. */

    uint16_t                  frame_type : 3;        /**< See \a mac_frame_type_t .*/
    uint16_t                  cmd_frame_id : 4;      /**< See \a mac_command_id_t .*/
    uint16_t                  security_min : 3;      /**< The minimal required/expected security
                                                          level for incoming MAC frames with the
                                                          indicated frame type and, if present,
                                                          command frame type (see
                                                          \a mac_security_level_t) .*/
    uint16_t                  override_min : 1;      /**< Indication of whether originating devices
                                                          for which the Exempt flag is set may
                                                          override the minimum security level
                                                          indicated by the SecurityMinimum
                                                          element. If TRUE, this indicates that for
                                                          originating devices with Exempt status,
                                                          the incoming security level zero is
                                                          acceptable, in addition to the incoming
                                                          security levels meeting the minimum
                                                          expected security level indicated by the
                                                          SecurityMinimum element .*/
} mac_security_level_descr_t;

typedef mac_table_t mac_security_level_table_t;

/** @} */

#endif // MAC_SECURITY_H_INCLUDED
