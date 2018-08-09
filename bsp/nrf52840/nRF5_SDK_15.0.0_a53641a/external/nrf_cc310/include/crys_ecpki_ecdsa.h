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



#ifndef CRYS_ECPKI_ECDSA_H
#define CRYS_ECPKI_ECDSA_H

/*!
@file
@brief Defines the APIs that support the ECDSA functions.
@defgroup crys_ecpki_ecdsa CryptoCell ECDSA APIs
@{
@ingroup cryptocell_ecpki
*/

#include "crys_error.h"
#include "crys_ecpki_types.h"
#include "crys_hash.h"
#include "crys_rnd.h"

#ifdef __cplusplus
extern "C"
{
#endif



/**************************************************************************
 *                CRYS_ECDSA_Sign - integrated function
 **************************************************************************/
/*!
@brief This function performs an ECDSA sign operation in integrated form.

\note
Using of HASH functions with HASH size greater than EC modulus size, is not recommended!.
Algorithm according [ANS X9.62] standard.

The message data may be either a non-hashed data or a digest of a hash function.
For a non-hashed data, the message data will be hashed using the hash function indicated by ::CRYS_ECPKI_HASH_OpMode_t.
For a digest, ::CRYS_ECPKI_HASH_OpMode_t should indicate the hash function that the message data was created by, and it will not be hashed.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_ecpki_error.h, crys_hash_error.h or crys_rnd_error.h.
**/
CIMPORT_C CRYSError_t CRYS_ECDSA_Sign(
                     void           *rndState_ptr,        /*!< [in/out] Pointer to the RND state structure. */
                     SaSiRndGenerateVectWorkFunc_t   rndGenerateVectFunc, /*!< [in] Pointer to the random vector generation function. */
                     CRYS_ECDSA_SignUserContext_t   *pSignUserContext,   /*!< [in/out] Pointer to the user buffer for signing the database. */
                     CRYS_ECPKI_UserPrivKey_t       *pSignerPrivKey,     /*!< [in]  A pointer to a user private key structure. */
                     CRYS_ECPKI_HASH_OpMode_t        hashMode,           /*!< [in]  One of the supported SHA-x HASH modes, as defined in
                                                    ::CRYS_ECPKI_HASH_OpMode_t.
                                                    \note MD5 is not supported. */
                     uint8_t                         *pMessageDataIn,    /*!< [in] Pointer to the input data to be signed.
                                                   The size of the scatter/gather list representing the data buffer
                                                   is limited to 128 entries, and the size of each entry is limited
                                                   to 64KB (fragments larger than 64KB are broken into
                                                   fragments <= 64KB). */
                     uint32_t                        messageSizeInBytes, /*!< [in]  Size of message data in bytes. */
                     uint8_t                        *pSignatureOut,      /*!< [in]  Pointer to a buffer for output of signature. */
                     uint32_t                       *pSignatureOutSize   /*!< [in/out] Pointer to the signature size. Used to pass the size of
                                                       the SignatureOut buffer (in), which must be >= 2
                                                       * OrderSizeInBytes. When the API returns,
                                                       it is replaced with the size of the actual signature (out). */
                     );



/**************************************************************************
 *                CRYS_ECDSA_Verify integrated function
 **************************************************************************/
/*!
@brief This function performs an ECDSA verify operation in integrated form.
Algorithm according [ANS X9.62] standard.

The message data may be either a non-hashed data or a digest of a hash function.
For a non-hashed data, the message data will be hashed using the hash function indicated by ::CRYS_ECPKI_HASH_OpMode_t.
For a digest, ::CRYS_ECPKI_HASH_OpMode_t should indicate the hash function that the message data was created by, and it will not be hashed.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_ecpki_error.h or crys_hash_error.h.
*/
CIMPORT_C CRYSError_t CRYS_ECDSA_Verify (
                    CRYS_ECDSA_VerifyUserContext_t *pVerifyUserContext, /*!< [in] Pointer to the user buffer for signing the database. */
                    CRYS_ECPKI_UserPublKey_t       *pUserPublKey,       /*!< [in] Pointer to a user public key structure. */
                    CRYS_ECPKI_HASH_OpMode_t        hashMode,           /*!< [in] One of the supported SHA-x HASH modes, as defined in
                                                      ::CRYS_ECPKI_HASH_OpMode_t.
                                                      \note MD5 is not supported. */
                    uint8_t                        *pSignatureIn,       /*!< [in] Pointer to the signature to be verified. */
                    uint32_t                        SignatureSizeBytes, /*!< [in] Size of the signature (in bytes).  */
                    uint8_t                        *pMessageDataIn,     /*!< [in] Pointer to the input data that was signed (same as given to
                                                      the signing function). The size of the scatter/gather list representing
                                                      the data buffer is limited to 128 entries, and the size of each entry is
                                                      limited to 64KB (fragments larger than 64KB are broken into fragments <= 64KB). */
                    uint32_t                        messageSizeInBytes  /*!< [in] Size of the input data (in bytes). */
                    );


/**********************************************************************************************************/


#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif
