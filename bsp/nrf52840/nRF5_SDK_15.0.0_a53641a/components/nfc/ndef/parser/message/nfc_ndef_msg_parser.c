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

#include "nfc_ndef_msg_parser.h"
#include "nrf_delay.h"

#define NRF_LOG_MODULE_NAME nfc_ndef_msg_parser
#if NFC_NDEF_MSG_PARSER_LOG_ENABLED
#define NRF_LOG_LEVEL       NFC_NDEF_MSG_PARSER_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NFC_NDEF_MSG_PARSER_INFO_COLOR
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();
#else // NFC_NDEF_MSG_PARSER_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#include "nrf_log.h"
#endif // NFC_NDEF_MSG_PARSER_LOG_ENABLED

ret_code_t ndef_msg_parser(uint8_t  * const p_result_buf,
                           uint32_t * const p_result_buf_len,
                           uint8_t  * const p_nfc_data,
                           uint32_t * const p_nfc_data_len)
{
    ret_code_t                  ret_code;
    nfc_ndef_parser_memo_desc_t parser_memory_helper;

    ret_code = ndef_parser_memo_resolve(p_result_buf,
                                        p_result_buf_len,
                                        &parser_memory_helper);

    if (ret_code != NRF_SUCCESS)
    {
        return ret_code;
    }

    ret_code = internal_ndef_msg_parser(&parser_memory_helper,
                                        p_nfc_data,
                                        p_nfc_data_len);

    return ret_code;
}


void ndef_msg_printout(nfc_ndef_msg_desc_t * const p_msg_desc)
{
    uint32_t i;

    NRF_LOG_INFO("NDEF message contains %d record(s)", p_msg_desc->record_count);

    for (i = 0; i < p_msg_desc->record_count; i++)
    {
        ndef_record_printout(i, p_msg_desc->pp_record[i]);
    }
}

#endif // NRF_MODULE_ENABLED(NFC_NDEF_MSG_PARSER)
