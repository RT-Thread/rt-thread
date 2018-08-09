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


#ifndef CRYS_HKDF_H
#define CRYS_HKDF_H

#include "crys_hash.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief This module defines the API that supports HMAC Key derivation function as defined by RFC5869.
@defgroup crys_hkdf CryptoCell HMAC Key Derivation APIs
@{
@ingroup cryptocell_api
*/

/*! HKDF maximal key size in words. */
#define CRYS_HKDF_MAX_HASH_KEY_SIZE_IN_BYTES        512

/*! HKDF maximal HASH digest size in bytes. */
#define CRYS_HKDF_MAX_HASH_DIGEST_SIZE_IN_BYTES     CRYS_HASH_SHA512_DIGEST_SIZE_IN_BYTES

/************************ Defines ******************************/

/************************ Enums ********************************/

/*! Enum defining HKDF HASH available modes. */
typedef enum
{
        /*! SHA1 mode. */
    CRYS_HKDF_HASH_SHA1_mode      = 0,
    /*! SHA224 mode. */
    CRYS_HKDF_HASH_SHA224_mode  = 1,
    /*! SHA256 mode. */
    CRYS_HKDF_HASH_SHA256_mode  = 2,
    /*! SHA384 mode. */
    CRYS_HKDF_HASH_SHA384_mode  = 3,
    /*! SHA512 mode. */
    CRYS_HKDF_HASH_SHA512_mode  = 4,

    /*! Maximal number of HASH modes. */
    CRYS_HKDF_HASH_NumOfModes,

    /*! Reserved */
    CRYS_HKDF_HASH_OpModeLast    = 0x7FFFFFFF,

}CRYS_HKDF_HASH_OpMode_t;

/************************ Typedefs  ****************************/

/************************ Structs  ******************************/

/************************ Public Variables **********************/

/************************ Public Functions **********************/

/****************************************************************/


/*********************************************************************************************************/
/*!
@brief CRYS_HKDF_KeyDerivFunc performs the HMAC-based key derivation, according to RFC5869

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_kdf_error.h, crys_hash_error or crys_hmac_error.h
*/
CEXPORT_C CRYSError_t  CRYS_HKDF_KeyDerivFunc(
                        CRYS_HKDF_HASH_OpMode_t HKDFhashMode,   /*!< [in]   The HKDF identifier of hash function to be used. */
                        uint8_t*                Salt_ptr,       /*!< [in]   A pointer to a non secret random value. can be NULL. */
                        size_t                  SaltLen,        /*!< [in]   The size of the salt_ptr. */
                        uint8_t*                Ikm_ptr,        /*!< [in]    A pointer to a input key message. */
                        uint32_t                IkmLen,         /*!< [in]   The size of the input key message */
                        uint8_t*                Info,           /*!< [in]   A pointer to an optional context and application specific information. can be NULL */
                        uint32_t                InfoLen,        /*!< [in]   The size of the info. */
                        uint8_t*                Okm,            /*!< [in]   A pointer to a output key material. */
                        uint32_t                OkmLen,         /*!< [in]   The size of the output key material. */
                        SaSiBool                IsStrongKey    /*!< [in]    if TRUE , then no need to perform the extraction phase. */
                        );

#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif

