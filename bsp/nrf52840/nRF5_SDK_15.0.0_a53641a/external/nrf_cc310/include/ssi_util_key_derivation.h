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


#ifndef  _SSI_UTIL_KEY_DERIVATION_H
#define  _SSI_UTIL_KEY_DERIVATION_H

/*!
@file
@brief This module defines the API that supports Key derivation function as specified
       in [SP800-108] in section "KDF in Counter Mode".
@defgroup ssi_utils_key_derivation CryptoCell utility key derivation APIs
@{
@ingroup ssi_utils

*/

#ifdef __cplusplus
extern "C"
{
#endif

#include "ssi_util_defs.h"
#include "ssi_util_key_derivation_defs.h"
#include "ssi_aes.h"

/******************************************************************************
*                           DEFINITIONS
******************************************************************************/

/*! Input key derivation type. */
typedef enum  {
    /*! User's key.*/
    SASI_UTIL_USER_KEY = 0,
    /*! Root key (Kdr).*/
    SASI_UTIL_ROOT_KEY = 1,
    /*! Reserved.*/
    SASI_UTIL_END_OF_KEY_TYPE = 0x7FFFFFFF
}SaSiUtilKeyType_t;


/*!
@brief  The key derivation function is as specified in [SP800-108] in section "KDF in Counter Mode".
    The derivation is based on length l, label L, context C and derivation key Ki.
    AES-CMAC is used as the pseudorandom function (PRF).

@return SASI_UTIL_OK on success.
@return A non-zero value from ssi_util_error.h on failure.
*/

/*  A key derivation functions can iterates n times until l bits of keying material are generated.
        For each of the iteration of the PRF, i=1 to n, do:
        result(0) = 0;
        K(i) = PRF (Ki, [i] || Label || 0x00 || Context || length);
        results(i) = result(i-1) || K(i);

        concisely, result(i) = K(i) || k(i-1) || .... || k(0)*/
SaSiUtilError_t SaSi_UtilKeyDerivation(
    SaSiUtilKeyType_t       keyType,    /*!< [in] The key type that is used as an input to a key derivation function.
                              Can be one of: SASI_UTIL_USER_KEY or SASI_UTIL_ROOT_KEY. */
    SaSiAesUserKeyData_t    *pUserKey,  /*!< [in] A pointer to the user's key buffer (in case of SASI_UTIL_USER_KEY). */
    const uint8_t       *pLabel,    /*!< [in] A string that identifies the purpose for the derived keying material.*/
    size_t              labelSize,  /*!< [in] The label size should be in range of 1 to 64 bytes length. */
    const uint8_t       *pContextData,  /*!< [in] A binary string containing the information related to the derived keying material. */
    size_t              contextSize,    /*!< [in] The context size should be in range of 1 to 64 bytes length. */
    uint8_t         *pDerivedKey,   /*!< [out] Keying material output (MUST be atleast the size of derivedKeySize). */
    size_t          derivedKeySize  /*!< [in] Size of the derived keying material in bytes (limited to 4080 bytes). */
    );

#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif /*_SSI_UTIL_KEY_DERIVATION_H*/
