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



#ifndef CRYS_RSA_PRIM_H
#define CRYS_RSA_PRIM_H

#include "crys_rsa_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief This module defines the API that implements the [PKCS1_2.1] primitive functions.
@defgroup crys_rsa_prim CryptoCell RSA primitive APIs
@{
@ingroup crys_rsa


\note Direct use of primitive functions, rather than schemes to protect data, is strongly discouraged as primitive functions are
susceptible to well-known attacks.
*/



/**********************************************************************************/
/*!
@brief Implements the RSAEP algorithm, as defined in [PKCS1_2.1] - 6.1.1.

@return CRYS_OK on success.
@return A non-zero value from crys_rsa_error.h on failure.
 */
CIMPORT_C CRYSError_t CRYS_RSA_PRIM_Encrypt(
                                CRYS_RSAUserPubKey_t *UserPubKey_ptr,       /*!< [in]  Pointer to the public key data structure. */
                                CRYS_RSAPrimeData_t  *PrimeData_ptr,        /*!< [in]  Pointer to a temporary structure containing internal buffers. */
                                uint8_t              *Data_ptr,             /*!< [in]  Pointer to the data to encrypt. */
                                uint16_t              DataSize,             /*!< [in]  The size (in bytes) of input data must be &le; modulus size. If is smaller,
                                                                                       then the function padds it by zeros on left side up to the modulus size
                                                                                   and therefore, after further decrypt operation, its result will contain
                                                                                       zero-padding also. If the function is used for recovering the plain data
                                                                                       from result of inverse function (CRYS_RSA_PRIM_Decrypt), the input size
                                                                                       must be equal to modulus size exactly. */
                                uint8_t              *Output_ptr            /*!< [out] Pointer to the encrypted data. The buffer size must be &ge; the modulus size. */
);


/**********************************************************************************/
/*!
@brief Implements the RSADP algorithm, as defined in [PKCS1_2.1] - 6.1.2.

@return CRYS_OK on success.
@return A non-zero value from crys_rsa_error.h on failure.

*/
CIMPORT_C CRYSError_t CRYS_RSA_PRIM_Decrypt(
                            CRYS_RSAUserPrivKey_t *UserPrivKey_ptr,     /*!< [in]  Pointer to the private key data structure.
                                                                                   The key representation (pair or quintuple) and hence the RSA algorithm
                                                                                   (CRT or not-CRT) is determined by enum value in the structure
                                           ::CRYS_RSA_Build_PrivKey or ::CRYS_RSA_Build_PrivKeyCRT. */
                            CRYS_RSAPrimeData_t   *PrimeData_ptr,       /*!< [in]  Pointer to a temporary structure containing internal buffers required for
                                           the RSA operation. */
                            uint8_t     *Data_ptr,                      /*!< [in]  Pointer to the data to be decrypted. */
                            uint16_t     DataSize,                      /*!< [in]  The size (in bytes) of input data must be &le; modulus size.
                                                                                   If the size is smaller (not recommendet), then the data will be zero-padded
                                                                                   by the function on left side up to the modulus size and therefore, after further
                                                                                   decrypt operation,its result will contain zero-padding also. If the function is used
                                                                                   for recovering the plain data from result of inverse function (CRYS_RSA_PRIM_Encrypt),
                                                                                   the input size must be equal to modulus size exactly. */
                            uint8_t     *Output_ptr                     /*!< [out] Pointer to the decrypted data. The buffer size must be &le; the modulus size. */
);


/*!
@brief Implements the RSASP1 algorithm, as defined in [PKCS1_2.1] - 6.2.1, as a call to ::CRYS_RSA_PRIM_Decrypt,
since the signature primitive is identical to the decryption primitive.
*/
#define CRYS_RSA_PRIM_Sign CRYS_RSA_PRIM_Decrypt

/*!
@brief Implements the RSAVP1 algorithm, as defined in [PKCS1_2.1] - 6.2.2, as a call to ::CRYS_RSA_PRIM_Encrypt.
*/
#define CRYS_RSA_PRIM_Verify CRYS_RSA_PRIM_Encrypt

#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif
