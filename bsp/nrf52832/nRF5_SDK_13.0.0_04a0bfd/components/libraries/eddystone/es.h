/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#ifndef ES_H__
#define ES_H__

#include <stdint.h>
#include "app_util_platform.h"

/**
 * @file
 *
 * @defgroup eddystone_types Frame types and data formats
 * @brief Definitions specific to Eddystone frame types and data formats.
 * @ingroup eddystone
 * @{
 */

/** @brief Swap 2 bytes.
 */
#define BYTES_SWAP_16BIT(x) (x << 8 | x >> 8)

/** @brief Reverse 4 bytes.
 */
#define BYTES_REVERSE_32BIT(x)                                                                     \
    ((x << 24 | ((x << 8) & 0x00FF0000)) | (((x >> 8) & 0x0000FF00) | x >> 24))

/** @brief Check if the error code is equal to NRF_SUCCESS. If it is not, return the error code.
 */
#define RETURN_IF_ERROR(PARAM)                                                                     \
    if ((PARAM) != NRF_SUCCESS)                                                                    \
    {                                                                                              \
        return (PARAM);                                                                            \
    }

#define ES_UUID                          0xFEAA     //!< UUID for Eddystone beacons according to specification.

#define ES_UID_FRAME_TYPE                0x00       //!< UID frame type (fixed at 0x00).
#define ES_UID_RFU                       0x00, 0x00 //!< Reserved for future use according to specification.

#define ES_URL_FRAME_TYPE                0x10       //!< URL frame type (fixed at 0x10).
#define ES_URL_SCHEME                    0x00       //!< URL prefix scheme according to specification (0x00 = "http://www").

#define ES_TLM_FRAME_TYPE                0x20       //!< TLM frame type (fixed at 0x20).
#define ES_EID_FRAME_TYPE                0x30       //!< EID frame type (fixed at 0x30).

#define ES_FRAME_TYPE_LENGTH             (1)         //!< Length of a frame type field.

#define ES_UID_LENGTH                    (20)        //!< Length of a UID frame.
#define ES_UID_NAMESPACE_LENGTH          (10)        //!< Length of a UID frame namespace field.
#define ES_UID_INSTANCE_LENGTH           (6)         //!< Length of a UID frame instance field.
#define ES_UID_RFU_LENGTH                (2)         //!< Length of a UID frame RFU field.

#define ES_URL_LENGTH                    (20)        //!< Length of a URL frame.
#define ES_URL_URL_SCHEME_LENGTH         (1)         //!< Length of a URL frame URL scheme field.
#define ES_URL_ENCODED_URL_LENGTH        (17)        //!< Maximum length of a URL frame encoded URL field.

#define ES_TLM_LENGTH                    (14)        //!< Length of a TLM frame.
#define ES_TLM_VBATT_LENGTH              (2)         //!< Length of a TLM frame VBATT field.
#define ES_TLM_TEMP_LENGTH               (2)         //!< Length of a TLM frame TEMP field.
#define ES_TLM_ADV_CNT_LENGTH            (4)         //!< Length of a TLM frame ADV count field.
#define ES_TLM_SEC_CNT_LENGTH            (4)         //!< Length of a TLM frame seconds field.

#define ES_EID_LENGTH                    (10)        //!< Length of an EID frame.
#define ES_EID_ID_LENGTH                 (8)         //!< Length of an EID frame ephemeral ID field.
#define ES_EID_GATTS_READ_LENGTH         (14)
#define ES_EID_GATTS_READ_FRAME_TYPE_IDX (0)
#define ES_EID_GATTS_READ_EXPONENT_IDX   (1)
#define ES_EID_GATTS_READ_CLCK_VALUE_IDX (2)
#define ES_EID_GATTS_READ_EID_IDX        (6)

#define ES_ETLM_LENGTH                   (18)        //!< Length of an eTLM frame.
#define ES_ETLM_ECRYPTED_LENGTH          (ES_TLM_VBATT_LENGTH +   \
                                          ES_TLM_TEMP_LENGTH +    \
                                          ES_TLM_ADV_CNT_LENGTH + \
                                          ES_TLM_SEC_CNT_LENGTH)  //!< Length of an eTLM frame encrypted TLM field.

#define ES_ETLM_RFU                      (0x00)      //!< eTLM frame RFU field value.
#define ES_SPEC_VERSION_BYTE             (0x00)      //!< eTLM frame specification version field value.

/** @brief Eddystone frame type values. These values are advertised as frame types. */
typedef enum
{
  ES_FRAME_TYPE_UID = ES_UID_FRAME_TYPE, /**< UID frame type. */
  ES_FRAME_TYPE_URL = ES_URL_FRAME_TYPE, /**< URL frame type. */
  ES_FRAME_TYPE_TLM = ES_TLM_FRAME_TYPE, /**< TLM frame type. */
  ES_FRAME_TYPE_EID = ES_EID_FRAME_TYPE  /**< EID frame type. */
} es_frame_type_t;

/** @brief TLM version values. */
typedef enum
{
    ES_TLM_VERSION_TLM = 0x00, /**< TLM. */
    ES_TLM_VERSION_ETLM = 0x01 /**< Encrypted TLM (eTLM). */
} es_tlm_version_t;

/** @brief UID frame data representation.
 * @note This is a packed structure. Therefore, you should not change it.
 */
typedef PACKED_STRUCT
{
    es_frame_type_t frame_type;                             //!< Frame type (see @ref es_frame_type_t).
    int8_t          ranging_data;                           //!< Calibrated TX power at 0 m.
    int8_t          namespace[ES_UID_NAMESPACE_LENGTH];     //!< UID namespace.
    int8_t          instance[ES_UID_INSTANCE_LENGTH];       //!< UID instance.
    int8_t          rfu[ES_UID_RFU_LENGTH];                 //!< RFU.
} es_uid_frame_t;


/** @brief URL frame data representation.
 * @note This is a packed structure. Therefore, you should not change it.
*/
typedef PACKED_STRUCT
{
    es_frame_type_t frame_type;                             //!< Frame type (see @ref es_frame_type_t).
    int8_t          ranging_data;                           //!< Calibrated TX power at 0 m.
    uint8_t         url_scheme;                             //!< URL scheme.
    uint8_t         encoded_url[ES_URL_ENCODED_URL_LENGTH]; //!< Encoded URL (variable length).
} es_url_frame_t;


/** @brief TLM frame data representation.
 * @note This is a packed structure. Therefore, you should not change it.
*/
typedef PACKED_STRUCT
{
    es_frame_type_t  frame_type;                            //!< Frame type (see @ref es_frame_type_t).
    es_tlm_version_t version;                               //!< TLM version (see @ref es_tlm_version_t).
    int8_t           vbatt[ES_TLM_VBATT_LENGTH];            //!< Battery voltage (in 1 mV units).
    int8_t           temp[ES_TLM_TEMP_LENGTH];              //!< Beacon temperature.
    int8_t           adv_cnt[ES_TLM_ADV_CNT_LENGTH];        //!< Advertising PDU count.
    int8_t           sec_cnt[ES_TLM_SEC_CNT_LENGTH];        //!< Time since power-on or reboot.
} es_tlm_frame_t;

/** @brief EID frame data representation.
 * @note This is a packed structure. Therefore, you should not change it.
*/
typedef PACKED_STRUCT
{
    es_frame_type_t frame_type;                             //!< Frame type (see @ref es_frame_type_t).
    int8_t          ranging_data;                           //!< Calibrated TX power at 0 m.
    int8_t          eid[ES_EID_ID_LENGTH];                  //!< 8-byte ephemeral identifier.
} es_eid_frame_t;


/** @brief eTLM frame data representation.
 * @note This is a packed structure. Therefore, you should not change it.
*/
typedef PACKED_STRUCT
{
    es_frame_type_t  frame_type;                             //!< Frame type (see @ref es_frame_type_t).
    es_tlm_version_t version;                                //!< TLM version (see @ref es_tlm_version_t).
    int8_t           encrypted_tlm[ES_ETLM_ECRYPTED_LENGTH]; //!< Encrypted TLM data.
    int16_t          random_salt;                            //!< Salt
    int16_t          msg_integrity_check;                    //!< Message integrity check.
} es_etlm_frame_t;

/**
 * @}
 */

#endif // ES_H__
