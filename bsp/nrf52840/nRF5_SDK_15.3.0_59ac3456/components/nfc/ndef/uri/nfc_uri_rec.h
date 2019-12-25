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
#ifndef NFC_URI_REC_H__
#define NFC_URI_REC_H__

/**@file
 *
 * @defgroup nfc_uri_rec URI records
 * @{
 * @ingroup  nfc_uri_msg
 *
 * @brief    Generation of NFC NDEF URI record descriptions.
 *
 */

#include "nfc_ndef_record.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @enum nfc_uri_id_t
 * @brief URI identifier codes according to "URI Record Type Definition"
 * (denotation "NFCForum-TS-RTD_URI_1.0" published on 2006-07-24) chapter 3.2.2.
 */
typedef enum
{
    NFC_URI_NONE          = 0x00,  /**< No prepending is done. */
    NFC_URI_HTTP_WWW      = 0x01,  /**< "http://www." */
    NFC_URI_HTTPS_WWW     = 0x02,  /**< "https://www." */
    NFC_URI_HTTP          = 0x03,  /**< "http:" */
    NFC_URI_HTTPS         = 0x04,  /**< "https:" */
    NFC_URI_TEL           = 0x05,  /**< "tel:" */
    NFC_URI_MAILTO        = 0x06,  /**< "mailto:" */
    NFC_URI_FTP_ANONYMOUS = 0x07,  /**< "ftp://anonymous:anonymous@" */
    NFC_URI_FTP_FTP       = 0x08,  /**< "ftp://ftp." */
    NFC_URI_FTPS          = 0x09,  /**< "ftps://" */
    NFC_URI_SFTP          = 0x0A,  /**< "sftp://" */
    NFC_URI_SMB           = 0x0B,  /**< "smb://" */
    NFC_URI_NFS           = 0x0C,  /**< "nfs://" */
    NFC_URI_FTP           = 0x0D,  /**< "ftp://" */
    NFC_URI_DAV           = 0x0E,  /**< "dav://" */
    NFC_URI_NEWS          = 0x0F,  /**< "news:" */
    NFC_URI_TELNET        = 0x10,  /**< "telnet://" */
    NFC_URI_IMAP          = 0x11,  /**< "imap:" */
    NFC_URI_RTSP          = 0x12,  /**< "rtsp://" */
    NFC_URI_URN           = 0x13,  /**< "urn:" */
    NFC_URI_POP           = 0x14,  /**< "pop:" */
    NFC_URI_SIP           = 0x15,  /**< "sip:" */
    NFC_URI_SIPS          = 0x16,  /**< "sips:" */
    NFC_URI_TFTP          = 0x17,  /**< "tftp:" */
    NFC_URI_BTSPP         = 0x18,  /**< "btspp://" */
    NFC_URI_BTL2CAP       = 0x19,  /**< "btl2cap://" */
    NFC_URI_BTGOEP        = 0x1A,  /**< "btgoep://" */
    NFC_URI_TCPOBEX       = 0x1B,  /**< "tcpobex://" */
    NFC_URI_IRDAOBEX      = 0x1C,  /**< "irdaobex://" */
    NFC_URI_FILE          = 0x1D,  /**< "file://" */
    NFC_URI_URN_EPC_ID    = 0x1E,  /**< "urn:epc:id:" */
    NFC_URI_URN_EPC_TAG   = 0x1F,  /**< "urn:epc:tag:" */
    NFC_URI_URN_EPC_PAT   = 0x20,  /**< "urn:epc:pat:" */
    NFC_URI_URN_EPC_RAW   = 0x21,  /**< "urn:epc:raw:" */
    NFC_URI_URN_EPC       = 0x22,  /**< "urn:epc:" */
    NFC_URI_URN_NFC       = 0x23,  /**< "urn:nfc:" */
    NFC_URI_RFU           = 0xFF   /**< No prepending is done. Reserved for future use. */
} nfc_uri_id_t;


/**
 * @brief Type of description of the payload of a URI record.
 */
typedef struct
{
    nfc_uri_id_t    uri_id_code;  /**< URI identifier code. */
    uint8_t const * p_uri_data;   /**< Pointer to a URI string. */
    uint8_t         uri_data_len; /**< Length of the URI string. */
} uri_payload_desc_t;

/**
 * @brief External reference to the type field of the URI record, defined in the
 * file @c nfc_uri_rec.c. It is used in the @ref NFC_NDEF_URI_RECORD_DESC_DEF macro.
 */
extern const uint8_t ndef_uri_record_type;

/**
 * @brief Function for constructing the payload for a URI record.
 *
 * This function encodes the payload according to the URI record definition. It implements an API
 * compatible with @ref p_payload_constructor_t.
 *
 * @param[in] p_input           Pointer to the description of the payload.
 * @param[out] p_buff           Pointer to payload destination. If NULL, function will
 *                              calculate the expected size of the URI record payload.
 *
 * @param[in,out] p_len         Size of available memory to write as input. Size of generated
 *                              payload as output.
 *
 * @retval NRF_SUCCESS          If the payload was encoded successfully.
 * @retval NRF_ERROR_NO_MEM     If the predicted payload size is bigger than the provided buffer space.
 */
ret_code_t nfc_uri_payload_constructor( uri_payload_desc_t * p_input,
                                        uint8_t            * p_buff,
                                        uint32_t           * p_len);

/** @brief Macro for generating a description of a URI record.
 *
 * This macro initializes an instance of an NFC NDEF record description of a URI record.
 *
 * @note The record descriptor is declared as automatic variable, which implies that
 *       the NDEF message encoding (see @ref nfc_uri_msg_encode) must be done
 *       in the same variable scope.
 *
 * @param[in]  NAME          Name for accessing record descriptor.
 * @param[in]  URI_ID_CODE   URI identifier code that defines the protocol field of the URI.
 * @param[in]  P_URI_DATA    Pointer to the URI string.
 *                           The string should not contain the protocol field if the protocol
 *                           was specified in @p uri_id_code.
 * @param[in]  URI_DATA_LEN  Length of the URI string.
 */
#define NFC_NDEF_URI_RECORD_DESC_DEF(NAME,                                   \
                                     URI_ID_CODE,                            \
                                     P_URI_DATA,                             \
                                     URI_DATA_LEN)                           \
    uri_payload_desc_t NAME##_ndef_uri_record_payload_desc =                 \
    {                                                                        \
        .uri_id_code  = (URI_ID_CODE),                                       \
        .p_uri_data   = (P_URI_DATA),                                        \
        .uri_data_len = (URI_DATA_LEN)                                       \
    };                                                                       \
                                                                             \
    NFC_NDEF_GENERIC_RECORD_DESC_DEF( NAME,                                  \
                                      TNF_WELL_KNOWN,                        \
                                      NULL,                                  \
                                      0,                                     \
                                      &ndef_uri_record_type,                 \
                                      sizeof(ndef_uri_record_type),          \
                                      nfc_uri_payload_constructor,           \
                                      &NAME##_ndef_uri_record_payload_desc)  \

/**
 * @brief Macro for accessing the NFC NDEF URI record descriptor instance that
 * was created with @ref NFC_NDEF_URI_RECORD_DESC_DEF.
 */
#define NFC_NDEF_URI_RECORD_DESC(NAME) NFC_NDEF_GENERIC_RECORD_DESC(NAME)

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NFC_URI_REC_H__
