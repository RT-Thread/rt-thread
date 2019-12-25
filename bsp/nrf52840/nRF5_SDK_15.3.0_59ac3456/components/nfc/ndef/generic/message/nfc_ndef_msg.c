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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NFC_NDEF_MSG)

#include "app_util.h"
#include "nfc_ndef_msg.h"
#include "nordic_common.h"
#include "nrf.h"


/**
 * @brief Resolve the value of record location flags of the NFC NDEF record within an NFC NDEF message.
 */
__STATIC_INLINE nfc_ndef_record_location_t record_location_get(uint32_t index,
                                                               uint32_t record_count)
{
    nfc_ndef_record_location_t record_location;

    if (index == 0)
    {
        if (record_count == 1)
        {
            record_location = NDEF_LONE_RECORD;
        }
        else
        {
            record_location = NDEF_FIRST_RECORD;
        }
    }
    else if (record_count == index + 1)
    {
        record_location = NDEF_LAST_RECORD;
    }
    else
    {
        record_location = NDEF_MIDDLE_RECORD;
    }

    return record_location;
}


ret_code_t nfc_ndef_msg_encode(nfc_ndef_msg_desc_t const * p_ndef_msg_desc,
                               uint8_t                   * p_msg_buffer,
                               uint32_t * const            p_msg_len)
{
    nfc_ndef_record_location_t record_location;
    uint32_t                   temp_len;
    uint32_t                   i;
    uint32_t                   err_code;

    uint32_t sum_of_len = 0;

    if ((p_ndef_msg_desc == NULL) || p_msg_len == NULL)
    {
        return NRF_ERROR_NULL;
    }

    nfc_ndef_record_desc_t * * pp_record_rec_desc = p_ndef_msg_desc->pp_record;

    if (p_ndef_msg_desc->pp_record == NULL)
    {
        return NRF_ERROR_NULL;
    }

#if NFC_NDEF_MSG_TAG_TYPE == TYPE_4_TAG
    uint8_t * p_root_msg_buffer = p_msg_buffer;

    if (p_msg_buffer != NULL)
    {
        if (*p_msg_len < NLEN_FIELD_SIZE)
        {
            return NRF_ERROR_NO_MEM;
        }

        p_msg_buffer += NLEN_FIELD_SIZE;
    }
    sum_of_len += NLEN_FIELD_SIZE;
#endif

    for (i = 0; i < p_ndef_msg_desc->record_count; i++)
    {
        record_location = record_location_get(i, p_ndef_msg_desc->record_count);

        temp_len = *p_msg_len - sum_of_len;

        err_code = nfc_ndef_record_encode(*pp_record_rec_desc,
                                          record_location,
                                          p_msg_buffer,
                                          &temp_len);

        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }

        sum_of_len += temp_len;
        if (p_msg_buffer != NULL)
        {
            p_msg_buffer += temp_len;
        }

        /* next record */
        pp_record_rec_desc++;
    }

#if NFC_NDEF_MSG_TAG_TYPE == TYPE_4_TAG
    if (p_msg_buffer != NULL)
    {
        if (sum_of_len - NLEN_FIELD_SIZE > UINT16_MAX)
        {
            return NRF_ERROR_NOT_SUPPORTED;
        }

        UNUSED_RETURN_VALUE(uint16_big_encode(sum_of_len - NLEN_FIELD_SIZE, p_root_msg_buffer));
    }
#endif

    *p_msg_len = sum_of_len;

    return NRF_SUCCESS;
}


void nfc_ndef_msg_clear(nfc_ndef_msg_desc_t * p_msg)
{
    p_msg->record_count = 0;
}


ret_code_t nfc_ndef_msg_record_add(nfc_ndef_msg_desc_t * const    p_msg,
                                   nfc_ndef_record_desc_t * const p_record)
{
    if (p_msg->record_count >= p_msg->max_record_count)
    {
        return NRF_ERROR_NO_MEM;
    }

    p_msg->pp_record[p_msg->record_count] = p_record;
    p_msg->record_count++;

    return NRF_SUCCESS;
}

#endif // NRF_MODULE_ENABLED(NFC_NDEF_MSG)
