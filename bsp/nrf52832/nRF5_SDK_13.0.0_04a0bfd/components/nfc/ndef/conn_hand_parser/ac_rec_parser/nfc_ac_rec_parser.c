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
#include "nfc_ac_rec_parser.h"
#include "sdk_macros.h"

/**
 * @brief Function for parsing Data Reference field inside Alternative Carrier record payload.
 *
 * This function parses Data Reference field inside Alternative Carrier record payload and extracts
 * its descriptor.
 *
 * @param[in,out]     pp_buff      Pointer to pointer to the remaining payload data.
 * @param[in,out]     p_len        Pointer to the length of remaining payload data.
 * @param[in,out]     p_ref_field  Pointer to the structure that will be used to hold
 *                                 parsed data.
 *
 * @retval NRF_SUCCESS                 If the function completed successfully.
 * @retval NRF_ERROR_NULL              If provided buffer for Data Reference in  \p p_ref_field is
 *                                     null.
 * @retval NRF_ERROR_NO_MEM            If the buffer provided for Data Reference in \p p_ref_field
 *                                     does not have enough space to store it.
 * @retval NRF_ERROR_INVALID_LENGTH    If Data Reference length exceeds record payload.
 */
static ret_code_t ac_rec_reference_field_parse(uint8_t                    ** const pp_buff,
                                               uint32_t                   *  const p_len,
                                               nfc_ac_rec_data_ref_t      *  const p_ref_field)
{
    if (p_ref_field->length < **pp_buff)
    {
        return NRF_ERROR_NO_MEM;
    }
    p_ref_field->length = **pp_buff;
    *pp_buff  += AC_REC_DATA_REF_LEN_SIZE;
    (*p_len)  -= AC_REC_DATA_REF_LEN_SIZE;

    if (*p_len < p_ref_field->length)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    VERIFY_PARAM_NOT_NULL(p_ref_field->p_data);
    memcpy( p_ref_field->p_data,
            *pp_buff,
            p_ref_field->length );
    *pp_buff  += p_ref_field->length;
    (*p_len)  -= p_ref_field->length;

    return NRF_SUCCESS;
}

/**
 * @brief Function for parsing Alternative Carrier record payload.
 *
 * This function parses Alternative Carrier record payload and extracts its payload descriptor.
 *
 * @param[in]     p_buff                  Pointer to the record payload.
 * @param[in]     p_len                   Pointer to the record payload length.
 * @param[in,out] p_ac_rec_payload_data   Pointer to the structure that will be used to hold
 *                                        parsed data.
 *
 * @retval NRF_SUCCESS                 If the function completed successfully.
 * @retval NRF_ERROR_NULL              If any provided arguments or any needed buffers stored in
 *                                     \p p_ac_rec_payload_data are nulls.
 * @retval NRF_ERROR_NO_MEM            If any from provided buffers does not have enough space
 *                                     to store its data.
 * @retval NRF_ERROR_INVALID_LENGTH    If any length field exceeds record payload.
 * @retval NRF_ERROR_INVALID_PARAM     If Carrier Power State field has incorrect value.
 */
static ret_code_t nfc_ac_payload_parse(uint8_t                    * p_buff,
                                       uint32_t                   * const p_len,
                                       nfc_ac_rec_payload_desc_t  * const p_ac_rec_payload_data)
{
    if ( (p_buff == NULL) || (p_len == NULL) || (p_ac_rec_payload_data == NULL) )
    {
        return NRF_ERROR_NULL;
    }

    if (*p_len < AC_REC_CPS_BYTE_SIZE + AC_REC_DATA_REF_LEN_SIZE + AC_REC_AUX_DATA_REF_COUNT_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Copy CPS to ac record payload descriptor.
    if (*p_buff & ~NFC_AC_CPS_MASK)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    p_ac_rec_payload_data->cps  = (nfc_ac_rec_cps_t) *p_buff;
    p_buff   += AC_REC_CPS_BYTE_SIZE;
    (*p_len) -= AC_REC_CPS_BYTE_SIZE;

    // Copy Carrier Data Reference to ac record payload descriptor.
    ret_code_t err_code = ac_rec_reference_field_parse(&p_buff,
                                                       p_len,
                                                       &p_ac_rec_payload_data->carrier_data_ref);
    VERIFY_SUCCESS(err_code);

    // Copy Auxiliary Data Reference to ac record payload descriptor.
    if ( p_ac_rec_payload_data->aux_data_ref_count < *p_buff)
    {
        return NRF_ERROR_NO_MEM;
    }
    p_ac_rec_payload_data->aux_data_ref_count = *p_buff;
    p_buff   += AC_REC_AUX_DATA_REF_COUNT_SIZE;
    (*p_len) -= AC_REC_AUX_DATA_REF_COUNT_SIZE;

    if (p_ac_rec_payload_data->aux_data_ref_count != 0)
    {
        VERIFY_PARAM_NOT_NULL(p_ac_rec_payload_data->p_aux_data_ref);
    }

    for (uint8_t i = 0; i < p_ac_rec_payload_data->aux_data_ref_count; i++)
    {
        err_code = ac_rec_reference_field_parse(&p_buff,
                                                 p_len,
                                                &(p_ac_rec_payload_data->p_aux_data_ref[i]));
        VERIFY_SUCCESS(err_code);
    }

    // Check if all payload data were parsed.
    if (*p_len != 0)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    return NRF_SUCCESS;
}

ret_code_t nfc_ac_rec_parse(nfc_ndef_record_desc_t    const * const p_rec_desc,
                            nfc_ac_rec_payload_desc_t       * const p_ac_rec_payload_data)
{
    ret_code_t err_code;

    if (p_rec_desc->tnf != TNF_WELL_KNOWN)
    {
        return NRF_ERROR_INVALID_DATA;
    }

    if (p_rec_desc->type_length != sizeof(nfc_ac_rec_type_field))
    {
        return NRF_ERROR_INVALID_DATA;
    }

    if (memcmp(p_rec_desc->p_type, nfc_ac_rec_type_field, sizeof(nfc_ac_rec_type_field)) != 0)
    {
        return NRF_ERROR_INVALID_DATA;
    }

    if (p_rec_desc->payload_constructor != (p_payload_constructor_t) nfc_ndef_bin_payload_memcopy)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    uint8_t const * p_payload =
        ((nfc_ndef_bin_payload_desc_t *)(p_rec_desc->p_payload_descriptor))->p_payload;
    uint32_t payload_length   =
        ((nfc_ndef_bin_payload_desc_t *)(p_rec_desc->p_payload_descriptor))->payload_length;

    err_code = nfc_ac_payload_parse((uint8_t *) p_payload,
                                    &payload_length,
                                    p_ac_rec_payload_data);

    return err_code;
}
