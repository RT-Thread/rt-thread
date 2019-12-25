/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#ifndef NFC_AC_REC_H__
#define NFC_AC_REC_H__

/**@file
 *
 * @defgroup nfc_ac_rec ac (Alternative carrier) records
 * @{
 * @ingroup  nfc_ble_pair_msg
 *
 * @brief Generation of NFC NDEF Alternative Carrier records for NDEF messages.
 *
 */

#include <stdint.h>
#include "nfc_ndef_record.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AC_REC_CPS_BYTE_SIZE            1 ///< Size of the field with CPS data.
#define AC_REC_DATA_REF_LEN_SIZE        1 ///< Size of the Data Reference Length field.
#define AC_REC_AUX_DATA_REF_COUNT_SIZE  1 ///< Size of the Data Reference Length field.

/**
 * @brief Carrier Power State.
 *
 * Possible Carrier Power State field values in an Alternative Carrier record.
 */
typedef enum
{
    NFC_AC_CPS_INACTIVE     = 0x00, ///< Alternative Carrier inactive.
    NFC_AC_CPS_ACTIVE       = 0x01, ///< Alternative Carrier active.
    NFC_AC_CPS_ACTIVATING   = 0x02, ///< Alternative Carrier activating.
    NFC_AC_CPS_UNKNOWN      = 0x03  ///< Alternative Carrier power status unknown.
} nfc_ac_rec_cps_t;

#define NFC_AC_CPS_MASK (NFC_AC_CPS_UNKNOWN) ///< Mask of Carrier Power State bits in a first ac record byte.

/**
 * @brief Carrier Data Reference and Auxiliary Data Reference descriptor.
 */
typedef struct
{
    uint8_t     length; ///< Length of the data field.
    uint8_t   * p_data; ///< Pointer to the Data Reference characters. Not relevant if length is 0.
} nfc_ac_rec_data_ref_t;

/**
 * @brief Alternative Carrier record payload descriptor.
 */
typedef struct
{
    nfc_ac_rec_cps_t            cps;                ///< Carrier Power State value.
    nfc_ac_rec_data_ref_t       carrier_data_ref;   ///< Carrier Data Reference.
    uint8_t               const max_aux_data_ref;   ///< Maximum number of Auxiliary Data Reference fields.
    uint8_t                     aux_data_ref_count; ///< Number of Auxiliary Data Reference fields.
    nfc_ac_rec_data_ref_t     * p_aux_data_ref;     ///< Pointer to the Auxiliary Data Reference fields.
} nfc_ac_rec_payload_desc_t;


/**
 * @brief Constructor for an NFC NDEF Alternative Carrier record payload.
 *
 * This function encodes the payload of an Alternative Carrier record as specified in the Connection
 * Handover standard. It implements an API compatible with @ref p_payload_constructor_t.
 */
ret_code_t nfc_ac_rec_payload_constructor(nfc_ac_rec_payload_desc_t * p_nfc_rec_ac_payload_desc,
                                          uint8_t                   * p_buff,
                                          uint32_t                  * p_len);

/**
 * @brief External reference to the type field of the Alternative Carrier record, defined in the
 * file @c nfc_ac_rec.c. It is used in the @ref NFC_NDEF_AC_RECORD_DESC_DEF macro.
 */
extern const uint8_t nfc_ac_rec_type_field[2];

/**
 * @brief Size of the type field of the Alternative Carrier record, defined in the
 * file @c nfc_ac_rec.c. It is used in the @ref NFC_NDEF_AC_RECORD_DESC_DEF macro.
 */
#define NFC_AC_REC_TYPE_LENGTH 2

/**
 *@brief Macro for creating and initializing an NFC NDEF record descriptor for an Alternative Carrier record.
 *
 * This macro creates and initializes an instance of type @ref nfc_ndef_record_desc_t and
 * an instance of type @ref nfc_ac_rec_payload_desc_t, which together constitute an instance of an Alternative Carrier record.
 *
 * Use the macro @ref NFC_NDEF_AC_RECORD_DESC to access the NDEF Alternative Carrier record descriptor instance.
 *
 * @note The record descriptor is declared as automatic variable, which implies that
 *       the NDEF message encoding (see @ref nfc_ble_full_handover_select_msg_encode)
 *       must be done in the same variable scope.
 *
 * @param[in] NAME              Name of the created record descriptor instance.
 * @param[in] CPS               Carrier Power State value.
 * @param[in] CARR_DATA_REF_LEN Length of the Carrier Data Reference field.
 * @param[in] P_CARR_DATA_REF   Pointer to the Carrier Data Reference field.
 * @param[in] MAX_AUX_DATA_REF  Maximum number of Auxiliary Data Reference fields.
 */
#define NFC_NDEF_AC_RECORD_DESC_DEF(NAME,                                                       \
                                    CPS,                                                        \
                                    CARR_DATA_REF_LEN,                                          \
                                    P_CARR_DATA_REF,                                            \
                                    MAX_AUX_DATA_REF)                                           \
    nfc_ac_rec_data_ref_t     NAME##_nfc_ac_rec_aux_data_ref_array[MAX_AUX_DATA_REF];           \
    nfc_ac_rec_payload_desc_t NAME##_nfc_ac_rec_payload_desc =                                  \
    {                                                                                           \
        .cps = CPS,                                                                             \
        .carrier_data_ref = {CARR_DATA_REF_LEN, P_CARR_DATA_REF},                               \
        .max_aux_data_ref = MAX_AUX_DATA_REF,                                                   \
        .aux_data_ref_count = 0,                                                                \
        .p_aux_data_ref = NAME##_nfc_ac_rec_aux_data_ref_array                                  \
    };                                                                                          \
    NFC_NDEF_GENERIC_RECORD_DESC_DEF(NAME,                                                      \
                                     TNF_WELL_KNOWN,                                            \
                                     0,                                                         \
                                     0,                                                         \
                                     nfc_ac_rec_type_field,                                     \
                                     NFC_AC_REC_TYPE_LENGTH,                                    \
                                     nfc_ac_rec_payload_constructor,                            \
                                     &(NAME##_nfc_ac_rec_payload_desc))

/**
 * @brief Macro for accessing the NFC NDEF Alternative Carrier record descriptor
 * instance that was created with @ref NFC_NDEF_AC_RECORD_DESC_DEF.
 */
#define NFC_NDEF_AC_RECORD_DESC(NAME) NFC_NDEF_GENERIC_RECORD_DESC(NAME)

/**
 * @brief Function for clearing an Auxiliary Data Reference in an NFC NDEF Alternative Carrier record.
 *
 * This function clears the Auxiliary Data References from the Alternative Carrier record.
 *
 * @param[in, out] p_ac_rec  Pointer to the Alternative Carrier record descriptor.
 */
void nfc_ac_rec_auxiliary_data_ref_clear(nfc_ndef_record_desc_t * p_ac_rec);

/**
 * @brief Function for adding an Auxiliary Data Reference to an NFC NDEF Alternative Carrier record.
 *
 * @param[in, out] p_ac_rec    Pointer to an ac record.
 * @param[in]      p_aux_data  Pointer to the Auxiliary Data Reference data buffer.
 * @param[in]      aux_length  Length of the Auxiliary Data Reference data.
 *
 * @retval NRF_SUCCESS      If the Auxiliary Data Reference was added successfully.
 * @retval NRF_ERROR_NO_MEM If the record already contains the maximum number of Auxiliary Data References.
 */
ret_code_t nfc_ac_rec_auxiliary_data_ref_add(nfc_ndef_record_desc_t * p_ac_rec,
                                             uint8_t                * p_aux_data,
                                             uint8_t                  aux_length);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NFC_AC_REC_H__
