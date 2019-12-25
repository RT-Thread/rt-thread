/**
 * Copyright (c) 2012 - 2019, Nordic Semiconductor ASA
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
/** @file
 *
 * @defgroup ble_sdk_lib_advdata Advertising and Scan Response Data Encoder
 * @{
 * @ingroup ble_sdk_lib
 * @brief Functions for encoding data in the Advertising and Scan Response Data format,
 *        and for passing the data to the stack.
 */

#ifndef BLE_ADVDATA_H__
#define BLE_ADVDATA_H__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "ble.h"
#include "sdk_common.h"

#ifdef __cplusplus
extern "C" {
#endif


#define AD_LENGTH_FIELD_SIZE               1UL                                         /**< Advertising Data and Scan Response format contains 1 octet for the length. */
#define AD_TYPE_FIELD_SIZE                 1UL                                         /**< Advertising Data and Scan Response format contains 1 octet for the AD type. */
#define AD_DATA_OFFSET                     (AD_LENGTH_FIELD_SIZE + AD_TYPE_FIELD_SIZE) /**< Offset for the AD data field of the Advertising Data and Scan Response format. */

#define AD_TYPE_BLE_DEVICE_ADDR_TYPE_SIZE  1UL                                 /**< Data size (in octets) of the Address type of the LE Bluetooth Device Address AD type. */
#define AD_TYPE_BLE_DEVICE_ADDR_DATA_SIZE  (BLE_GAP_ADDR_LEN + \
                                            AD_TYPE_BLE_DEVICE_ADDR_TYPE_SIZE) /**< Data size (in octets) of the LE Bluetooth Device Address AD type. */
#define AD_TYPE_BLE_DEVICE_ADDR_SIZE       (AD_DATA_OFFSET + \
                                            AD_TYPE_BLE_DEVICE_ADDR_DATA_SIZE) /**< Size (in octets) of the LE Bluetooth Device Address AD type. */
#define AD_TYPE_APPEARANCE_DATA_SIZE       2UL                                 /**< Data size (in octets) of the Appearance AD type. */
#define AD_TYPE_APPEARANCE_SIZE            (AD_DATA_OFFSET + \
                                            AD_TYPE_APPEARANCE_DATA_SIZE)      /**< Size (in octets) of the Appearance AD type. */
#define AD_TYPE_FLAGS_DATA_SIZE            1UL                                 /**< Data size (in octets) of the Flags AD type. */
#define AD_TYPE_FLAGS_SIZE                 (AD_DATA_OFFSET + \
                                            AD_TYPE_FLAGS_DATA_SIZE)           /**< Size (in octets) of the Flags AD type. */
#define AD_TYPE_TX_POWER_LEVEL_DATA_SIZE   1UL                                 /**< Data size (in octets) of the TX Power Level AD type. */
#define AD_TYPE_TX_POWER_LEVEL_SIZE        (AD_DATA_OFFSET + \
                                            AD_TYPE_TX_POWER_LEVEL_DATA_SIZE)  /**< Size (in octets) of the TX Power Level AD type. */
#define AD_TYPE_CONN_INT_DATA_SIZE         4UL                                 /**< Data size (in octets) of the Slave Connection Interval Range AD type. */
#define AD_TYPE_CONN_INT_SIZE              (AD_DATA_OFFSET + \
                                            AD_TYPE_CONN_INT_DATA_SIZE)        /**< Data size (in octets) of the Slave Connection Interval Range AD type. */
#define AD_TYPE_MANUF_SPEC_DATA_ID_SIZE    2UL                                 /**< Size (in octets) of the Company Identifier Code, which is a part of the Manufacturer Specific Data AD type. */
#define AD_TYPE_SERV_DATA_16BIT_UUID_SIZE  2UL                                 /**< Size (in octets) of the 16-bit UUID, which is a part of the Service Data AD type. */

#define BLE_ADV_DATA_MATCH_FULL_NAME       0xff


/**@brief Security Manager TK value. */
typedef struct
{
  uint8_t tk[BLE_GAP_SEC_KEY_LEN];      /**< Array containing TK value in little-endian format. */
} ble_advdata_tk_value_t;

/**@brief Advertising data LE Role types. This enumeration contains the options available for the LE role inside
 *        the advertising data. */
typedef enum
{
    BLE_ADVDATA_ROLE_NOT_PRESENT = 0,                                 /**< LE Role AD structure not present. */
    BLE_ADVDATA_ROLE_ONLY_PERIPH,                                     /**< Only Peripheral Role supported. */
    BLE_ADVDATA_ROLE_ONLY_CENTRAL,                                    /**< Only Central Role supported. */
    BLE_ADVDATA_ROLE_BOTH_PERIPH_PREFERRED,                           /**< Peripheral and Central Role supported. Peripheral Role preferred for connection establishment. */
    BLE_ADVDATA_ROLE_BOTH_CENTRAL_PREFERRED                           /**< Peripheral and Central Role supported. Central Role preferred for connection establishment */
} ble_advdata_le_role_t;

/**@brief Advertising data name type. This enumeration contains the options available for the device name inside
 *        the advertising data. */
typedef enum
{
    BLE_ADVDATA_NO_NAME,                                              /**< Include no device name in advertising data. */
    BLE_ADVDATA_SHORT_NAME,                                           /**< Include short device name in advertising data. */
    BLE_ADVDATA_FULL_NAME                                             /**< Include full device name in advertising data. */
} ble_advdata_name_type_t;

/**@brief UUID list type. */
typedef struct
{
    uint16_t                     uuid_cnt;                            /**< Number of UUID entries. */
    ble_uuid_t *                 p_uuids;                             /**< Pointer to UUID array entries. */
} ble_advdata_uuid_list_t;

/**@brief Connection interval range structure. */
typedef struct
{
    uint16_t                     min_conn_interval;                   /**< Minimum connection interval, in units of 1.25 ms, range 6 to 3200 (7.5 ms to 4 s). */
    uint16_t                     max_conn_interval;                   /**< Maximum connection interval, in units of 1.25 ms, range 6 to 3200 (7.5 ms to 4 s). The value 0xFFFF indicates no specific maximum. */
} ble_advdata_conn_int_t;

/**@brief Manufacturer specific data structure. */
typedef struct
{
    uint16_t                     company_identifier;                  /**< Company identifier code. */
    uint8_array_t                data;                                /**< Additional manufacturer specific data. */
} ble_advdata_manuf_data_t;

/**@brief Service data structure. */
typedef struct
{
    uint16_t                     service_uuid;                        /**< Service UUID. */
    uint8_array_t                data;                                /**< Additional service data. */
} ble_advdata_service_data_t;

/**@brief Advertising data structure. This structure contains all options and data needed for encoding and
 *        setting the advertising data. */
typedef struct
{
    ble_advdata_name_type_t      name_type;                           /**< Type of device name. */
    uint8_t                      short_name_len;                      /**< Length of short device name (if short type is specified). */
    bool                         include_appearance;                  /**< Determines if Appearance shall be included. */
    uint8_t                      flags;                               /**< Advertising data Flags field. */
    int8_t *                     p_tx_power_level;                    /**< TX Power Level field. */
    ble_advdata_uuid_list_t      uuids_more_available;                /**< List of UUIDs in the 'More Available' list. */
    ble_advdata_uuid_list_t      uuids_complete;                      /**< List of UUIDs in the 'Complete' list. */
    ble_advdata_uuid_list_t      uuids_solicited;                     /**< List of solicited UUIDs. */
    ble_advdata_conn_int_t *     p_slave_conn_int;                    /**< Slave Connection Interval Range. */
    ble_advdata_manuf_data_t *   p_manuf_specific_data;               /**< Manufacturer specific data. */
    ble_advdata_service_data_t * p_service_data_array;                /**< Array of Service data structures. */
    uint8_t                      service_data_count;                  /**< Number of Service data structures. */
    bool                         include_ble_device_addr;             /**< Determines if LE Bluetooth Device Address shall be included. */
    ble_advdata_le_role_t        le_role;                             /**< LE Role field. Included when different from @ref BLE_ADVDATA_ROLE_NOT_PRESENT. @warning This field can be used only for NFC. For BLE advertising, set it to NULL. */
    ble_advdata_tk_value_t *     p_tk_value;                          /**< Security Manager TK value field. Included when different from NULL. @warning This field can be used only for NFC. For BLE advertising, set it to NULL.*/
    uint8_t *                    p_sec_mgr_oob_flags;                 /**< Security Manager Out Of Band Flags field. Included when different from NULL. @warning This field can be used only for NFC. For BLE advertising, set it to NULL.*/
    ble_gap_lesc_oob_data_t *    p_lesc_data;                         /**< LE Secure Connections OOB data. Included when different from NULL. @warning This field can be used only for NFC. For BLE advertising, set it to NULL.*/
} ble_advdata_t;

/**@brief Function for encoding data in the Advertising and Scan Response data format (AD structures).
 *
 * @details This function encodes data into the Advertising and Scan Response data format
 *          (AD structures) based on the fields in the supplied structures. This function can be
 *          used to create a payload of Advertising packet or Scan Response packet, or a payload of
 *          NFC message intended for initiating the Out-of-Band pairing.
 *
 * @param[in]      p_advdata       Pointer to the structure for specifying the content of encoded data.
 * @param[out]     p_encoded_data  Pointer to the buffer where encoded data will be returned.
 * @param[in,out]  p_len           \c in: Size of \p p_encoded_data buffer.
 *                                 \c out: Length of encoded data.
 *
 * @retval NRF_SUCCESS             If the operation was successful.
 * @retval NRF_ERROR_INVALID_PARAM If the operation failed because a wrong parameter was provided in
 *                                 \p p_advdata.
 * @retval NRF_ERROR_DATA_SIZE     If the operation failed because not all the requested data could
 *                                 fit into the provided buffer or some encoded AD structure is too
 *                                 long and its length cannot be encoded with one octet.
 *
 * @warning This API may override the application's request to use the long name and use a short name
 * instead. This truncation will occur in case the long name does not fit the provided buffer size.
 * The application can specify a preferred short name length if truncation is required.
 * For example, if the complete device name is ABCD_HRMonitor, the application can specify the short name
 * length to be 8, so that the short device name appears as ABCD_HRM instead of ABCD_HRMo or ABCD_HRMoni
 * if the available size for the short name is 9 or 12 respectively, to have a more appropriate short name.
 * However, it should be noted that this is just a preference that the application can specify, and
 * if the preference is too large to fit in the provided buffer, the name can be truncated further.
 */
ret_code_t ble_advdata_encode(ble_advdata_t const * const p_advdata,
                              uint8_t             * const p_encoded_data,
                              uint16_t            * const p_len);


/**@brief Function for searching encoded Advertising or Scan Response data for specific data types.
 *
 * @details This function searches through encoded data e.g. the data produced by
 *          @ref ble_advdata_encode, or the data found in Advertising reports
 *          (@ref BLE_GAP_EVT_ADV_REPORT), and gives the offset of the data within the data buffer.
 *          The data with type \p ad_type can be found at p_encoded_data[*p_offset] after calling
 *          the function. This function can iterate through multiple instances of data of one
 *          type by calling it again with the offset provided by the previous call.
 *
 *          Example code for finding multiple instances of one type of data:
 *              offset = 0;
 *              ble_advdata_search(&data, len, &offset, AD_TYPE);
 *              first_instance_of_data = data[offset];
 *              ble_advdata_search(&data, len, &offset, AD_TYPE);
 *              second_instance_of_data = data[offset];
 *
 * @param[in]    p_encoded_data  The data buffer containing the encoded Advertising data.
 * @param[in]    data_len        The length of the data buffer \p p_encoded_data.
 * @param[inout] p_offset        \c in: The offset to start searching from.
 *                               \c out: The offset the data type can be found at.
 *                                       This value is not changed if the call returns 0.
 * @param[in]    ad_type         The type of data to search for.
 *
 * @return The length of the found data, or 0 if no data was found with the the type \p ad_type,
 *         or if \p p_encoded_data or \p p_offset were NULL.
 */
uint16_t ble_advdata_search(uint8_t const * p_encoded_data,
                            uint16_t        data_len,
                            uint16_t      * p_offset,
                            uint8_t         ad_type);

/**@brief Function for getting specific data from encoded Advertising or Scan Response data.
 *
 * @details This function searches through encoded data e.g. the data produced by
 *          @ref ble_advdata_encode, or the data found in Advertising reports
 *          (@ref BLE_GAP_EVT_ADV_REPORT), and returns a pointer directly to the data within the
 *          data buffer.
 *
 *          Example code:
 *              ad_type_data = ble_advdata_parse(&data, len, AD_TYPE);
 *
 * @param[in]    p_encoded_data  Data buffer containing the encoded Advertising data.
 * @param[in]    data_len        Length of the data buffer \p p_encoded_data.
 * @param[in]    ad_type         Type of data to search for.
 *
 * @return Pointer to the found data, or NULL if no data was found with the type \p ad_type,
 *         or if \p p_encoded_data or \p p_data_len were NULL.
 */
uint8_t * ble_advdata_parse(uint8_t  * p_encoded_data,
                            uint16_t   data_len,
                            uint8_t    ad_type);


/**@brief Function for searching through encoded Advertising data for a complete local name.
 *
 * @param[in]    p_encoded_data Data buffer containing the encoded Advertising data.
 * @param[in]    data_len       Length of the data buffer \p p_encoded_data.
 * @param[in]    p_target_name  Name to search for.
 *
 * @retval true   If \p p_target_name was found among \p p_encoded_data, as a complete local name.
 * @retval false  If \p p_target_name was not found among \p p_encoded_data, or if \p p_encoded_data
 *                or \p p_target_name was NULL.
 */
bool ble_advdata_name_find(uint8_t const * p_encoded_data,
                           uint16_t        data_len,
                           char    const * p_target_name);


/**@brief Function for searching through encoded Advertising data for a device shortened name.
 *
 * @param[in]    p_encoded_data     Data buffer containing the encoded Advertising data.
 * @param[in]    data_len           Length of the data buffer \p p_encoded_data.
 * @param[in]    p_target_name      Name to search for.
 * @param[in]    short_name_min_len Minimum length of the shortened name.
 *               For example, if the advertising data has a shortened name 'No' and this parameter is
 *               set to 4 with a target_name set to Nordic_XXX it will return false, but if
 *               the shortened name in the advertising data is 'Nord', it will return true.
 * @note: If the shortened name in the Advertising data has the same length as the target name,
 *        this function will return false, since this means that the complete name is actually
 *        longer, thus different than the target name.
 *
 * @retval true   If \p p_target_name was found among \p p_encoded_data, as short local name.
 * @retval false  If \p p_target_name was not found among \p p_encoded_data, or if \p p_encoded_data
 *                or \p p_target_name was NULL.
 */
bool ble_advdata_short_name_find(uint8_t const * p_encoded_data,
                                 uint16_t        data_len,
                                 char    const * p_target_name,
                                 uint8_t const   short_name_min_len);

/**@brief Function for searching through encoded Advertising data for a UUID (16-bit or 128-bit).
 *
 * @param[in]    p_encoded_data  Data buffer containing the encoded Advertising data.
 * @param[in]    data_len        Length of the data buffer \p p_encoded_data.
 * @param[in]    p_target_uuid   UUID to search for.
 *
 * @retval true   If \p p_target_uuid was found among \p p_encoded_data.
 * @retval false  If \p p_target_uuid was not found among \p p_encoded_data, or if \p p_encoded_data
 *                or \p p_target_uuid was NULL.
 */
bool ble_advdata_uuid_find(uint8_t    const * p_encoded_data,
                           uint16_t           data_len,
                           ble_uuid_t const * p_target_uuid);


/**@brief Function for searching through encoded Advertising data for an appearance.
 *
 * @param[in]    p_encoded_data        Data buffer containing the encoded Advertising data.
 * @param[in]    data_len              Length of the data buffer \p p_encoded_data.
 * @param[in]    p_target_appearance   Appearance to search for.
 *
 * @retval true   If \p p_target_appearance was found among \p p_encoded_data.
 * @retval false  If \p p_target_appearance was not found among \p p_encoded_data, or if \p p_encoded_data
 *                or \p p_target_appearance was NULL.
 */
bool ble_advdata_appearance_find(uint8_t   const * p_encoded_data,
                                 uint16_t          data_len,
                                 uint16_t  const * p_target_appearance);


#ifdef __cplusplus
}
#endif

#endif // BLE_ADVDATA_H__

/** @} */
