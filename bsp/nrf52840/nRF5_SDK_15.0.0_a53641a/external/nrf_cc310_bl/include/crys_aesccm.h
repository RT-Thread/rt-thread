/**************************************************************************************
* Copyright (c) 2016-2017, ARM Limited or its affiliates. All rights reserved         *
*                                                                                     *
* This file and the related binary are licensed under the following license:          *
*                                                                                     *
* ARM Object Code and Header Files License, v1.0 Redistribution.                      *
*                                                                                     *
* Redistribution and use of object code, header files, and documentation, without     *
* modification, are permitted provided that the following conditions are met:         *
*                                                                                     *
* 1) Redistributions must reproduce the above copyright notice and the                *
*    following disclaimer in the documentation and/or other materials                 *
*    provided with the distribution.                                                  *
*                                                                                     *
* 2) Unless to the extent explicitly permitted by law, no reverse                     *
*    engineering, decompilation, or disassembly of is permitted.                      *
*                                                                                     *
* 3) Redistribution and use is permitted solely for the purpose of                    *
*    developing or executing applications that are targeted for use                   *
*    on an ARM-based product.                                                         *
*                                                                                     *
* DISCLAIMER. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND                  *
* CONTRIBUTORS "AS IS." ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT             *
* NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT,        *
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          *
* COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED            *
* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR              *
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF              *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING                *
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS                  *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                        *
**************************************************************************************/



#ifndef CRYS_AESCCM_H
#define CRYS_AESCCM_H

#include "ssi_pal_types.h"
#include "crys_error.h"

#include "ssi_aes.h"


#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief This file contains all of the enums and definitions that are used for the CRYS AESCCM APIs, as well as the APIs themselves.
The API supports AES-CCM and AES-CCM* as defined in ieee-802.15.4.
@defgroup crys_aesccm CryptoCell AES-CCM APIs
@{
@ingroup cryptocell_api


@note
Regarding the AES-CCM*, the API supports only AES-CCM* as defined in ieee-802.15.4-2011; With the instantiations as defined in B.3.2 and the nonce as defined in 7.3.2.
in case of AES-CCM* the flow should be as follows:
<ul><li>AES-CCM* integrated</li>
        <ul><li>CRYS_AESCCMStar_NonceGenerate</li>
        <li>CRYS_AESCCMStar</li></ul></ul>
<ul><li>AES-CCM* non-integrated</li>
        <ul><li>CRYS_AESCCMStar_NonceGenerate</li>
        <li>CRYS_AESCCMStar_Init</li>
        <li>CRYS_AESCCM_BlockAdata</li>
        <li>CRYS_AESCCM_BlockTextData</li>
        <li>CRYS_AESCCM_Finish</li></ul></ul>
*/

/************************ Defines ******************************/

/*! AES CCM context size in words.*/
#define CRYS_AESCCM_USER_CTX_SIZE_IN_WORDS (152/4)

/*! AES CCM maximal key size in words. */
#define CRYS_AESCCM_KEY_SIZE_WORDS           8

/* nonce and AESCCM-MAC sizes definitions */
/*! AES CCM NONCE minimal size in bytes. */
#define CRYS_AESCCM_NONCE_MIN_SIZE_BYTES     7
/*! AES CCM NONCE maximal size in bytes. */
#define CRYS_AESCCM_NONCE_MAX_SIZE_BYTES    13
/*! AES CCM MAC minimal size in bytes..*/
#define CRYS_AESCCM_MAC_MIN_SIZE_BYTES       4
/*! AES CCM MAC maximal size in bytes. */
#define CRYS_AESCCM_MAC_MAX_SIZE_BYTES      16

/*! AES CCM star NONCE size in bytes. */
#define CRYS_AESCCM_STAR_NONCE_SIZE_BYTES               13
/*! AES CCM star source address size in bytes. */
#define CRYS_AESCCM_STAR_SOURCE_ADDRESS_SIZE_BYTES      8

/*! AES CCM mode - CCM. */
#define CRYS_AESCCM_MODE_CCM      0
/*! AES CCM mode - CCM STAR. */
#define CRYS_AESCCM_MODE_STAR     1


/************************ Typedefs  ****************************/
/*! AES CCM key sizes. */
typedef enum {
    /*! Key size 128 bits. */
    CRYS_AES_Key128BitSize   = 0,
    /*! Key size 192 bits. */
    CRYS_AES_Key192BitSize   = 1,
    /*! Key size 256 bits. */
    CRYS_AES_Key256BitSize   = 2,
    /*! Key size 512 bits. */
    CRYS_AES_Key512BitSize   = 3,
    /*! Number of optional key sizes. */
    CRYS_AES_KeySizeNumOfOptions,
    /*! Reserved. */
    CRYS_AES_KeySizeLast    = 0x7FFFFFFF,

}CRYS_AESCCM_KeySize_t;

/*! AES_CCM key buffer definition.*/
typedef uint8_t CRYS_AESCCM_Key_t[CRYS_AESCCM_KEY_SIZE_WORDS * sizeof(uint32_t)];
/*! AES_CCM MAC buffer definition.*/
typedef uint8_t CRYS_AESCCM_Mac_Res_t[SASI_AES_BLOCK_SIZE_IN_BYTES];

/*! AES_CCM_STAR source address buffer defintion. */
typedef uint8_t CRYS_AESCCMStar_SourceAddress_t[CRYS_AESCCM_STAR_SOURCE_ADDRESS_SIZE_BYTES];
/*! AES_CCM_STAR Nonce buffer defintion. */
typedef uint8_t CRYS_AESCCMStar_Nonce_t[CRYS_AESCCM_STAR_NONCE_SIZE_BYTES];

/******************* Context Structure  ***********************/
/*! The user's context structure - the argument type that is passed by the user to the AES CCM APIs */
typedef struct CRYS_AESCCM_UserContext_t
{
    /*! AES CCM context buffer for internal usage. */
    uint32_t  buff[CRYS_AESCCM_USER_CTX_SIZE_IN_WORDS];
}CRYS_AESCCM_UserContext_t;


/************************ Public Functions **********************/

/*!
@brief This function initializes the AES CCM context.

It formats of the input data, calculates AES-MAC value for the formatted B0 block containing control information and
CCM unique value (Nonce), and initializes the AES context structure including the initial CTR0 value.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_aesccm_error.h.
*/
CRYSError_t CC_AESCCM_Init(
        CRYS_AESCCM_UserContext_t *ContextID_ptr,   /*!< [in] Pointer to the AES context buffer that is allocated by the user and is used for
                                      the AES operation. */
        SaSiAesEncryptMode_t EncrDecrMode,          /*!< [in] Flag specifying whether Encrypt (::SASI_AES_ENCRYPT) or Decrypt
                                      (::SASI_AES_DECRYPT) operation should be performed. */
        CRYS_AESCCM_Key_t CCM_Key,                  /*!< [in] Pointer to the AES-CCM key. */
        CRYS_AESCCM_KeySize_t KeySizeId,            /*!< [in] Enumerator defining the key size (only 128 bit is valid). */
        uint32_t AdataSize,                         /*!< [in] Full byte length of additional (associated) data. If set to zero,
                                      calling ::CRYS_AESCCM_BlockAdata on the same context would return an error. */
        uint32_t TextSizeQ,                         /*!< [in] Full length of plain text data. */
        uint8_t *N_ptr,                             /*!< [in] Pointer to the Nonce. */
        uint8_t SizeOfN,                            /*!< [in] Nonce byte size. The valid values depend on the ccm mode:
                                                                        <ul><li>CCM:  valid values = [7 .. 13].</li>
                                                                        <li>CCM*: valid values = [13].</li></ul> */
        uint8_t SizeOfT,                            /*!< [in] AES-CCM MAC (tag) byte size. The valid values depend on the ccm mode:
                                                                        <ul><li>CCM:  valid values = [4, 6, 8, 10, 12, 14, 16].</li>
                                                                        <li>CCM*: valid values = [0, 4, 8, 16].</li></ul>*/
                uint32_t ccmMode                            /*!< [in] Flag specifying whether AES-CCM or AES-CCM* should be performed. */
);

/*! Macro defintion for CRYS_AESCCM_Init (AES CCM non-star implementation). */
#define CRYS_AESCCM_Init(ContextID_ptr, EncrDecrMode, CCM_Key, KeySizeId, AdataSize, TextSizeQ, N_ptr, SizeOfN, SizeOfT) \
        CC_AESCCM_Init(ContextID_ptr, EncrDecrMode, CCM_Key, KeySizeId, AdataSize, TextSizeQ, N_ptr, SizeOfN, SizeOfT, CRYS_AESCCM_MODE_CCM)

/*! Macro defintion CRYS_AESCCMStar_Init (AES CCM star implementation). */
#define CRYS_AESCCMStar_Init(ContextID_ptr, EncrDecrMode, CCM_Key, KeySizeId, AdataSize, TextSizeQ, N_ptr, SizeOfN, SizeOfT) \
        CC_AESCCM_Init(ContextID_ptr, EncrDecrMode, CCM_Key, KeySizeId, AdataSize, TextSizeQ, N_ptr, SizeOfN, SizeOfT, CRYS_AESCCM_MODE_STAR)

/*!
@brief This function receives a CCM context and a block of additional data, and adds it to the AES MAC
calculation.
This API can be called only once per operation context. It should not be called in case AdataSize was set to
zero in ::CC_AESCCM_Init.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_aesccm_error.h.
*/
CRYSError_t CRYS_AESCCM_BlockAdata(
        CRYS_AESCCM_UserContext_t *ContextID_ptr,   /*!< [in] Pointer to the context buffer. */
                uint8_t *DataIn_ptr,                        /*!< [in] Pointer to the additional input data. The buffer must be contiguous. */
                uint32_t DataInSize                         /*!< [in] Byte size of the additional data. Must match AdataSize parameter provided to
                                      ::CRYS_AESCCM_Init. */
);

/*!
@brief This function can be invoked for any block of Text data whose size is a multiple of 16 bytes,
excluding the last block that must be processed by ::CRYS_AESCCM_Finish.
<ul><li> If encrypting:
    Continues calculation of the intermediate AES_MAC value of the text data, while simultaneously encrypting the text data using AES_CTR,
    starting from CTR value = CTR0+1.</li>
<li>If decrypting:
    Continues decryption of the text data, while calculating the intermediate AES_MAC value of decrypted data.</li></ul>

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_aesccm_error.h.
*/
CRYSError_t CRYS_AESCCM_BlockTextData(
                CRYS_AESCCM_UserContext_t *ContextID_ptr,   /*!< [in] Pointer to the context buffer. */
                uint8_t *DataIn_ptr,                        /*!< [in] Pointer to the additional input data. The buffer must be contiguous. */
                uint32_t DataInSize,                        /*!< [in] Byte size of the text data block. Must be a multiple of 16 bytes. */
                uint8_t *DataOut_ptr                        /*!< [out] Pointer to the output data. The size of the output buffer must be at least DataInSize.
                                                                       The buffer must be contiguous. */
);

/*!
@brief This function must be the last to be called on the text data.
It can either be called on the entire text data (if transferred as one block), or on the last block of the text data,
even if total size of text data is equal to 0.
It performs the same operations as ::CRYS_AESCCM_BlockTextData, but additionally:
<ul><li> If encrypting: </li>
     <ul><li>If the size of text data is not in multiples of 16 bytes, it pads the remaining bytes with zeros to a full 16-bytes block and
     processes the data using AES_MAC and AES_CTR algorithms.</li>
    <li> Encrypts the AES_MAC result with AES_CTR using the CTR0 value saved in the context and places the SizeOfT bytes of MAC (tag)
    at the end.</li></ul></ul>
<ul><li> If decrypting: </li>
    <ul><li>Processes the text data, except for the last SizeOfT bytes (tag), using AES_CTR and then AES_MAC algorithms.</li>
    <li>Encrypts the calculated MAC using AES_CTR based on the saved CTR0 value, and compares it with SizeOfT last bytes of input data (i.e.
        tag value).</li>
    <li>The function saves the validation result (Valid/Invalid) in the context.</li>
    <li>Returns (as the error code) the final CCM-MAC verification result.</li></ul></ul>

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_aesccm_error.h.
*/
CEXPORT_C CRYSError_t CRYS_AESCCM_Finish(
                CRYS_AESCCM_UserContext_t *ContextID_ptr,   /*!< [in] Pointer to the context buffer. */
                uint8_t *DataIn_ptr,                        /*!< [in] Pointer to the last input data. The buffer must be contiguous. */
                uint32_t DataInSize,                        /*!< [in] Byte size of the last text data block. Can be zero. */
                uint8_t *DataOut_ptr,                       /*!< [in] Pointer to the output (cipher or plain text data) data. The buffer must
                                              be contiguous. If DataInSize = 0, output buffer is not required. */
                CRYS_AESCCM_Mac_Res_t MacRes,               /*!< [in]  MAC result buffer pointer. */
                uint8_t *SizeOfT                            /*!< [out] AES-CCM MAC byte size as defined in CRYS_AESCCM_Init. */
);

/****************************************************************************************************/
/********                       AESCCM  FUNCTION                                              ******/
/****************************************************************************************************/
/*!
@brief AES CCM combines Counter mode encryption with CBC-MAC authentication.
Input to CCM includes the following elements:
<ul><li> Payload - text data that is both authenticated and encrypted.</li>
<li> Associated data (Adata) - data that is authenticated but not encrypted, e.g., a header.</li>
<li> Nonce - A unique value that is assigned to the payload and the associated data.</li></ul>

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_aesccm_error.h.
*/
CIMPORT_C CRYSError_t  CC_AESCCM(
               SaSiAesEncryptMode_t       EncrDecrMode,     /*!< [in] A flag specifying whether an AES Encrypt (::SASI_AES_ENCRYPT) or Decrypt
                                          (::SASI_AES_DECRYPT) operation should be performed. */
               CRYS_AESCCM_Key_t          CCM_Key,          /*!< [in] Pointer to AES-CCM key. */
               CRYS_AESCCM_KeySize_t      KeySizeId,        /*!< [in] Enumerator defining the key size (only 128 bit is valid). */
               uint8_t                   *N_ptr,            /*!< [in] Pointer to the Nonce. */
               uint8_t                    SizeOfN,          /*!< [in] Nonce byte size. The valid values depend on the ccm mode:
                                                                                        <ul><li>CCM:  valid values = [7 .. 13].</li>
                                                                                        <li>CCM*: valid values = [13].</li></ul> */
               uint8_t                   *ADataIn_ptr,      /*!< [in] Pointer to the additional input data. The buffer must be contiguous. */
               uint32_t                   ADataInSize,      /*!< [in] Byte size of the additional data. */
               uint8_t                   *TextDataIn_ptr,   /*!< [in] Pointer to the plain-text data for encryption or cipher-text data for decryption.
                                          The buffer must be contiguous. */
               uint32_t                   TextDataInSize,   /*!< [in] Byte size of the full text data. */
               uint8_t                   *TextDataOut_ptr,  /*!< [out] Pointer to the output (cipher or plain text data according to encrypt-decrypt mode)
                                           data. The buffer must be contiguous. */
               uint8_t                    SizeOfT,          /*!< [in] AES-CCM MAC (tag) byte size. The valid values depend on the ccm mode:
                                                                                        <ul><li>CCM:  valid values = [4, 6, 8, 10, 12, 14, 16].</li>
                                                                                        <li>CCM*: valid values = [0, 4, 8, 16].</li></ul>*/
               CRYS_AESCCM_Mac_Res_t      Mac_Res,          /*!< [in/out] Pointer to the MAC result buffer. */
                           uint32_t ccmMode                             /*!< [in] Flag specifying whether AES-CCM or AES-CCM* should be performed. */
);

/*! Macro defintion for CRYS_AESCCM (AES CCM non-star implementation). */
#define CRYS_AESCCM(EncrDecrMode, CCM_Key, KeySizeId, N_ptr, SizeOfN, ADataIn_ptr, ADataInSize, TextDataIn_ptr, TextDataInSize, TextDataOut_ptr, SizeOfT, Mac_Res) \
        CC_AESCCM(EncrDecrMode, CCM_Key, KeySizeId, N_ptr, SizeOfN, ADataIn_ptr, ADataInSize, TextDataIn_ptr, TextDataInSize, TextDataOut_ptr, SizeOfT, Mac_Res, CRYS_AESCCM_MODE_CCM)

/*! Macro defintion for CRYS_AESCCMStar (AES CCM star implementation). */
#define CRYS_AESCCMStar(EncrDecrMode, CCM_Key, KeySizeId, N_ptr, SizeOfN, ADataIn_ptr, ADataInSize, TextDataIn_ptr, TextDataInSize, TextDataOut_ptr, SizeOfT, Mac_Res) \
        CC_AESCCM(EncrDecrMode, CCM_Key, KeySizeId, N_ptr, SizeOfN, ADataIn_ptr, ADataInSize, TextDataIn_ptr, TextDataInSize, TextDataOut_ptr, SizeOfT, Mac_Res, CRYS_AESCCM_MODE_STAR)


/*!
@brief This function receives the MAC source address, the frame counter and the MAC size
and returns the required nonce for AES-CCM* as defined in ieee-802.15.4.
This API should be called before CRYS_AESCCMStar and CRYS_AESCCMStar_Init,
and the generated nonce should be provided to these functions.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_aesccm_error.h.
*/
CRYSError_t CRYS_AESCCMStar_NonceGenerate(
        CRYS_AESCCMStar_SourceAddress_t srcAddr,        /*!< [in]  The MAC address in EUI-64 format. */
        uint32_t FrameCounter,                          /*!< [in]  The MAC frame counter. */
        uint8_t SizeOfT,                                /*!< [in]  AES-CCM* MAC (tag) byte size. Valid values = [0,4,8,16]. */
        CRYS_AESCCMStar_Nonce_t nonce                   /*!< [out] The required nonce for AES-CCM*. */
);

#ifdef __cplusplus
}
#endif

/**
@}
 */

#endif /*#ifndef CRYS_AESCCM_H*/

