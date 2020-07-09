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
#include "sdk_config.h"
#if NFC_T4T_HL_DETECTION_PROCEDURES_ENABLED

#include "nfc_t4t_hl_detection_procedures.h"
#include "nfc_t4t_apdu.h"
#include "adafruit_pn532.h"
#include "sdk_macros.h"
#include "nordic_common.h"

#define NRF_LOG_MODULE_NAME "NFC_T4T_HL_DETECTION_PROCEDURES"
#if NFC_T4T_HL_DETECTION_PROCEDURES_LOG_ENABLED
#define NRF_LOG_LEVEL       NFC_T4T_HL_DETECTION_PROCEDURES_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NFC_T4T_HL_DETECTION_PROCEDURES_INFO_COLOR
#else // NFC_T4T_HL_DETECTION_PROCEDURES_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // NFC_T4T_HL_DETECTION_PROCEDURES_LOG_ENABLED
#include "nrf_log.h"

#define CC_FILE_ID                0xE103 ///< File Identifier of Capability Container.
#define FILE_ID_SIZE              2      ///< Size of File Identifier field in CC file.
#define MIN_MAX_RAPDU_SIZE        0x0F   ///< Minimal value of maximal RAPDU data field size.
#define NDEF_FILE_NLEN_FIELD_SIZE 2      ///< Size of NLEN field in NDEF file.
#define NDEF_APP_PROC_RESP_LEN    256    ///< Maximal size of RAPDU data in the NDEF Tag Application Select Procedure.

// Adafruit library limitations.
#define MAX_ADAFRUIT_RAPDU_SIZE   242    ///< Maximal value of RAPDU data field size
#define MAX_ADAFRUIT_CAPDU_SIZE   56     ///< Maximal value of CAPDU data field size

static uint8_t       m_file_id[FILE_ID_SIZE];                                                       ///< Buffer for selected EF ID storage.
static const uint8_t m_nfc_t4t_select_ndef_app_data[] = {0xD2, 0x76, 0x00, 0x00, 0x85, 0x01, 0x01}; ///< NDEF Tag Application name.
static const uint8_t m_nlen_update_value[]            = {0x00, 0x00};                               ///< NLEN value used in NDEF Update Procedure.

/**
 * @brief Function for performing APDU exchanges with Adafruit library.
 */
static ret_code_t nfc_t4t_apdu_exchange(nfc_t4t_comm_apdu_t * const p_capdu,
                                        nfc_t4t_resp_apdu_t * const p_rapdu,
                                        uint8_t             * const p_apdu_buff,
                                        uint8_t                     resp_len)
{
    if (resp_len > APDU_BUFF_SIZE)
    {
        return NRF_ERROR_NO_MEM;
    }

    uint16_t   apdu_buff_len = APDU_BUFF_SIZE;
    ret_code_t err_code      = nfc_t4t_comm_apdu_encode(p_capdu,
                                                        p_apdu_buff,
                                                        &apdu_buff_len);
    VERIFY_SUCCESS(err_code);

    err_code = adafruit_pn532_in_data_exchange(p_apdu_buff, apdu_buff_len, p_apdu_buff, &resp_len);
    VERIFY_SUCCESS(err_code);

    err_code = nfc_t4t_resp_apdu_decode(p_rapdu, p_apdu_buff, resp_len);
    VERIFY_SUCCESS(err_code);

    nfc_t4t_resp_apdu_printout(p_rapdu);
    VERIFY_RAPDU_SUCCESS(p_rapdu);

    return err_code;
}

/**
 * @brief Function for performing APDU exchanges with Adafruit library with default response length.
 */
static ret_code_t nfc_t4t_apdu_default_exchange(nfc_t4t_comm_apdu_t * const p_capdu,
                                                nfc_t4t_resp_apdu_t * const p_rapdu,
                                                uint8_t             * const p_apdu_buff)
{
    if (p_capdu->resp_len + sizeof(p_rapdu->status) > UINT8_MAX)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    uint8_t    resp_len = (uint8_t) (p_capdu->resp_len + sizeof(p_rapdu->status));
    ret_code_t err_code = nfc_t4t_apdu_exchange(p_capdu, p_rapdu, p_apdu_buff, resp_len);

    return err_code;
}


/**
 * @brief Function for saving part of EF (contained in RAPDU) in storage buffer.
 */
static ret_code_t nfc_t4t_file_chunk_save(nfc_t4t_resp_apdu_t const * const p_rapdu,
                                          uint8_t                   * const p_storage_buff,
                                          uint16_t                          storage_buff_len,
                                          uint16_t                  * const p_file_offset)
{
    if (p_rapdu->data.p_buff == NULL)
    {
        return NRF_ERROR_NULL;
    }
    if ((*p_file_offset) + p_rapdu->data.len > storage_buff_len)
    {
        return NRF_ERROR_NO_MEM;
    }

    memcpy(p_storage_buff + (*p_file_offset), p_rapdu->data.p_buff, p_rapdu->data.len);
    *p_file_offset += p_rapdu->data.len;

    return NRF_SUCCESS;
}


/**
 * @brief Function for updating the remaining length of the read file.
 */
static ret_code_t nfc_t4t_file_len_update(nfc_t4t_resp_apdu_t const * const p_rapdu,
                                          uint16_t                  * const p_len)
{
    if (*p_len < p_rapdu->data.len)
    {
        return NRF_ERROR_INVALID_DATA;
    }
    *p_len -= p_rapdu->data.len;

    return NRF_SUCCESS;
}


ret_code_t nfc_t4t_ndef_tag_app_select(void)
{
    ret_code_t          err_code;
    nfc_t4t_comm_apdu_t capdu;
    nfc_t4t_resp_apdu_t rapdu;
    uint8_t             apdu_buff[APDU_BUFF_SIZE];

    NRF_LOG_INFO("NDEF Tag Application Select Procedure \r\n");

    nfc_t4t_comm_apdu_clear(&capdu);
    capdu.instruction = NFC_T4T_CAPDU_SELECT_INS;
    capdu.parameter   = SELECT_BY_NAME;
    capdu.data.p_buff = (uint8_t *) m_nfc_t4t_select_ndef_app_data;
    capdu.data.len    = sizeof(m_nfc_t4t_select_ndef_app_data);
    capdu.resp_len    = NDEF_APP_PROC_RESP_LEN;

    err_code = nfc_t4t_apdu_exchange(&capdu, &rapdu, apdu_buff, sizeof(rapdu.status));
    NRF_LOG_RAW_INFO("\r\n");
    return err_code;
}


ret_code_t nfc_t4t_file_select(uint16_t file_id)
{
    ret_code_t          err_code;
    nfc_t4t_comm_apdu_t capdu;
    nfc_t4t_resp_apdu_t rapdu;
    uint8_t             apdu_buff[APDU_BUFF_SIZE];

    if (file_id != CC_FILE_ID)
    {
        NRF_LOG_INFO("File (ID = %4X) Select Procedure \r\n", file_id);
    }
    UNUSED_RETURN_VALUE(uint16_big_encode(file_id, m_file_id));

    nfc_t4t_comm_apdu_clear(&capdu);
    capdu.instruction = NFC_T4T_CAPDU_SELECT_INS;
    capdu.parameter   = SELECT_BY_FILE_ID;
    capdu.data.p_buff = m_file_id;
    capdu.data.len    = sizeof(m_file_id);

    err_code = nfc_t4t_apdu_default_exchange(&capdu, &rapdu, apdu_buff);
    NRF_LOG_RAW_INFO("\r\n");
    return err_code;
}


ret_code_t nfc_t4t_cc_select(void)
{
    NRF_LOG_INFO("Capability Container Select Procedure \r\n");

    return nfc_t4t_file_select(CC_FILE_ID);
}


ret_code_t nfc_t4t_cc_read(nfc_t4t_capability_container_t * const p_cc_file)
{
    ret_code_t          err_code;
    nfc_t4t_comm_apdu_t capdu;
    nfc_t4t_resp_apdu_t rapdu;
    uint16_t            clen;
    uint16_t            file_offset = 0;
    uint8_t             storage_buff[CC_STORAGE_BUFF_SIZE];
    uint8_t             apdu_buff[APDU_BUFF_SIZE];

    NRF_LOG_INFO("Capability Container Read Procedure \r\n");

    nfc_t4t_comm_apdu_clear(&capdu);
    capdu.instruction = NFC_T4T_CAPDU_READ_INS;
    capdu.parameter   = file_offset;
    capdu.resp_len    = MIN_MAX_RAPDU_SIZE;

    err_code = nfc_t4t_apdu_default_exchange(&capdu, &rapdu, apdu_buff);
    VERIFY_SUCCESS(err_code);

    err_code = nfc_t4t_file_chunk_save(&rapdu, storage_buff, CC_STORAGE_BUFF_SIZE, &file_offset);
    VERIFY_SUCCESS(err_code);

    clen     = uint16_big_decode(storage_buff);
    err_code = nfc_t4t_file_len_update(&rapdu, &clen);
    VERIFY_SUCCESS(err_code);

    while (clen > 0)
    {
        capdu.parameter = file_offset;
        capdu.resp_len  = MIN(MIN_MAX_RAPDU_SIZE, MIN(clen, MAX_ADAFRUIT_RAPDU_SIZE));

        err_code = nfc_t4t_apdu_default_exchange(&capdu, &rapdu, apdu_buff);
        VERIFY_SUCCESS(err_code);

        err_code = nfc_t4t_file_chunk_save(&rapdu, storage_buff, CC_STORAGE_BUFF_SIZE, &file_offset);
        VERIFY_SUCCESS(err_code);

        err_code = nfc_t4t_file_len_update(&rapdu, &clen);
        VERIFY_SUCCESS(err_code);
    }

    err_code = nfc_t4t_cc_file_parse(p_cc_file, storage_buff, file_offset);

    NRF_LOG_RAW_INFO("\r\n");
    return err_code;
}


ret_code_t nfc_t4t_ndef_read(nfc_t4t_capability_container_t * const p_cc_file,
                             uint8_t                        *       p_ndef_file_buff,
                             uint8_t                                ndef_file_buff_len)
{
    ret_code_t          err_code;
    nfc_t4t_comm_apdu_t capdu;
    nfc_t4t_resp_apdu_t rapdu;
    uint16_t            len;
    uint16_t            file_offset = 0;
    uint8_t             apdu_buff[APDU_BUFF_SIZE];

    NRF_LOG_INFO("NDEF Read Procedure \r\n");

    // Read the NLEN (NDEF length) field of NDEF file.
    nfc_t4t_comm_apdu_clear(&capdu);
    capdu.instruction = NFC_T4T_CAPDU_READ_INS;
    capdu.parameter   = file_offset;
    capdu.resp_len    = NDEF_FILE_NLEN_FIELD_SIZE;

    err_code = nfc_t4t_apdu_default_exchange(&capdu, &rapdu, apdu_buff);
    VERIFY_SUCCESS(err_code);

    err_code = nfc_t4t_file_chunk_save(&rapdu, p_ndef_file_buff, ndef_file_buff_len, &file_offset);
    VERIFY_SUCCESS(err_code);

    len      = uint16_big_decode(p_ndef_file_buff) + NDEF_FILE_NLEN_FIELD_SIZE;
    err_code = nfc_t4t_file_len_update(&rapdu, &len);
    VERIFY_SUCCESS(err_code);

    // Read the NDEF message.
    while (len > 0)
    {
        capdu.parameter = file_offset;
        capdu.resp_len  = MIN(len, MIN(p_cc_file->max_rapdu_size, MAX_ADAFRUIT_RAPDU_SIZE));

        err_code = nfc_t4t_apdu_default_exchange(&capdu, &rapdu, apdu_buff);
        VERIFY_SUCCESS(err_code);

        err_code = nfc_t4t_file_chunk_save(&rapdu, p_ndef_file_buff, ndef_file_buff_len, &file_offset);
        VERIFY_SUCCESS(err_code);

        err_code = nfc_t4t_file_len_update(&rapdu, &len);
        VERIFY_SUCCESS(err_code);
    }

    // Bind NDEF File Control TLV with NDEF file.
    nfc_t4t_file_t file =
    {
        .p_content = p_ndef_file_buff,
        .len       = file_offset
    };
    uint16_t file_id = uint16_big_decode(m_file_id);
    err_code = nfc_t4t_file_content_set(p_cc_file, file, file_id);

    NRF_LOG_RAW_INFO("\r\n");
    return err_code;
}


ret_code_t nfc_t4t_ndef_update(nfc_t4t_capability_container_t * const p_cc_file,
                               uint8_t                        *       p_ndef_file_buff,
                               uint8_t                                ndef_file_buff_len)
{
    ret_code_t            err_code;
    nfc_t4t_comm_apdu_t   capdu;
    nfc_t4t_resp_apdu_t   rapdu;
    uint16_t              len;
    uint16_t              file_offset = 0;
    uint16_t              file_id     = uint16_big_decode(m_file_id);
    uint8_t               apdu_buff[APDU_BUFF_SIZE];
    nfc_t4t_tlv_block_t * p_tlv_block;

    NRF_LOG_INFO("NDEF Update Procedure \r\n");

    if (ndef_file_buff_len < NDEF_FILE_NLEN_FIELD_SIZE)
    {
        return NRF_ERROR_INVALID_DATA;
    }

    // Check if selected NDEF file is registered in CC file descriptor.
    p_tlv_block = nfc_t4t_file_content_get(p_cc_file, file_id);
    if (p_tlv_block == NULL)
    {
        return NRF_ERROR_NULL;
    }

    // Check NDEF file capacity before writing anything to it.
    len = uint16_big_decode(p_ndef_file_buff);
    if ((len + NDEF_FILE_NLEN_FIELD_SIZE != ndef_file_buff_len) ||
        (ndef_file_buff_len > p_tlv_block->value.max_file_size))
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Write the value 0000h in the NLEN field.
    nfc_t4t_comm_apdu_clear(&capdu);
    capdu.instruction = NFC_T4T_CAPDU_UPDATE_INS;
    capdu.parameter   = file_offset;
    capdu.data.p_buff = (uint8_t *) m_nlen_update_value;
    capdu.data.len    = NDEF_FILE_NLEN_FIELD_SIZE;

    err_code = nfc_t4t_apdu_default_exchange(&capdu, &rapdu, apdu_buff);
    VERIFY_SUCCESS(err_code);
    file_offset += NDEF_FILE_NLEN_FIELD_SIZE;

    // Write the NDEF message in the NDEF message field.
    while (len > 0)
    {
        capdu.parameter   = file_offset;
        capdu.data.p_buff = p_ndef_file_buff + file_offset;
        capdu.data.len    = MIN(len, MIN(p_cc_file->max_capdu_size, MAX_ADAFRUIT_CAPDU_SIZE));

        err_code = nfc_t4t_apdu_default_exchange(&capdu, &rapdu, apdu_buff);
        VERIFY_SUCCESS(err_code);

        file_offset += capdu.data.len;
        len         -= capdu.data.len;
    }

    // Write the length of the NDEF message in the NLEN field.
    capdu.parameter   = 0;
    capdu.data.p_buff = p_ndef_file_buff;
    capdu.data.len    = NDEF_FILE_NLEN_FIELD_SIZE;

    err_code = nfc_t4t_apdu_default_exchange(&capdu, &rapdu, apdu_buff);
    VERIFY_SUCCESS(err_code);

    NRF_LOG_RAW_INFO("\r\n");
    return NRF_SUCCESS;
}


#endif // NFC_T4T_HL_DETECTION_PROCEDURES_ENABLED

