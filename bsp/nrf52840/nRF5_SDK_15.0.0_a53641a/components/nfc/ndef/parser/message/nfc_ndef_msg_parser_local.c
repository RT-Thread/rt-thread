/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NFC_NDEF_MSG_PARSER)

#include "nfc_ndef_msg_parser_local.h"

ret_code_t internal_ndef_msg_parser(nfc_ndef_parser_memo_desc_t * const p_parser_memo_desc,
                                    uint8_t                     const * p_nfc_data,
                                    uint32_t                    * const p_nfc_data_len)
{
    nfc_ndef_record_location_t record_location;

    ret_code_t ret_code;

    uint32_t nfc_data_left     = *p_nfc_data_len;
    uint32_t temp_nfc_data_len = 0;

    // want to modify -> use local copy
    nfc_ndef_bin_payload_desc_t * p_bin_pay_desc = p_parser_memo_desc->p_bin_pay_desc;
    nfc_ndef_record_desc_t      * p_rec_desc     = p_parser_memo_desc->p_rec_desc;


    while (nfc_data_left > 0)
    {
        temp_nfc_data_len = nfc_data_left;

        ret_code = ndef_record_parser(p_bin_pay_desc,
                                      p_rec_desc,
                                      &record_location,
                                      p_nfc_data,
                                      &temp_nfc_data_len);

        if (ret_code != NRF_SUCCESS)
        {
            return ret_code;
        }

        // verify the records location flags
        if (p_parser_memo_desc->p_msg_desc->record_count == 0)
        {
            if ((record_location != NDEF_FIRST_RECORD) && (record_location != NDEF_LONE_RECORD))
            {
                return NRF_ERROR_INVALID_DATA;
            }
        }
        else
        {
            if ((record_location != NDEF_MIDDLE_RECORD) && (record_location != NDEF_LAST_RECORD))
            {
                return NRF_ERROR_INVALID_DATA;
            }
        }

        ret_code = nfc_ndef_msg_record_add(p_parser_memo_desc->p_msg_desc, p_rec_desc);

        if (ret_code != NRF_SUCCESS)
        {
            return ret_code;
        }

        nfc_data_left -= temp_nfc_data_len;

        if ((record_location == NDEF_LAST_RECORD) || (record_location == NDEF_LONE_RECORD))
        {
            *p_nfc_data_len = *p_nfc_data_len - nfc_data_left;
            return NRF_SUCCESS;
        }
        else
        {
            if (p_parser_memo_desc->p_msg_desc->record_count ==
                p_parser_memo_desc->p_msg_desc->max_record_count)
            {
                return NRF_ERROR_NO_MEM;
            }

            p_nfc_data += temp_nfc_data_len;
            p_bin_pay_desc++;
            p_rec_desc++;
        }
    }

    return NRF_ERROR_INVALID_DATA;

}


ret_code_t ndef_parser_memo_resolve(uint8_t                     * const p_result_buf,
                                    uint32_t                    * const p_result_buf_len,
                                    nfc_ndef_parser_memo_desc_t * const p_parser_memo_desc)
{

    uint32_t                   max_rec_num;
    uint32_t                   memory_last;
    uint8_t                  * p_end;
    nfc_ndef_record_desc_t * * pp_record_desc_array;

    if (*p_result_buf_len < sizeof(parsed_ndef_msg_1_t))
    {
        return NRF_ERROR_NO_MEM;
    }

    memory_last = (*p_result_buf_len) - sizeof(parsed_ndef_msg_1_t);
    max_rec_num = (memory_last / (NFC_PARSER_M_DELTA)) + 1;

    p_parser_memo_desc->p_msg_desc = (nfc_ndef_msg_desc_t *) p_result_buf;
    pp_record_desc_array           =
        (nfc_ndef_record_desc_t * *) &p_parser_memo_desc->p_msg_desc[1];
    p_parser_memo_desc->p_bin_pay_desc =
        (nfc_ndef_bin_payload_desc_t *) &pp_record_desc_array[max_rec_num];
    p_parser_memo_desc->p_rec_desc =
        (nfc_ndef_record_desc_t *) &p_parser_memo_desc->p_bin_pay_desc[max_rec_num];

    // initialize message description
    p_parser_memo_desc->p_msg_desc->pp_record        = pp_record_desc_array;
    p_parser_memo_desc->p_msg_desc->max_record_count = max_rec_num;
    p_parser_memo_desc->p_msg_desc->record_count     = 0;

    p_end = (uint8_t *) &p_parser_memo_desc->p_rec_desc[max_rec_num];

    *p_result_buf_len = p_end - p_result_buf;

    return NRF_SUCCESS;
}

#endif // NRF_MODULE_ENABLED(NFC_NDEF_MSG_PARSER)
