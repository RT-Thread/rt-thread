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




#ifndef CRYS_RSA_KG_H
#define CRYS_RSA_KG_H

#include "crys_rsa_types.h"
#include "crys_rnd.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief Generates a RSA pair of public and private keys.
@defgroup crys_rsa_kg CryptoCell RSA key generation APIs
@{
@ingroup crys_rsa
*/

/************************ Defines ******************************/

/* Max allowed size and values of public exponent for key generation in CRYS */
/*! Maximal public exponent size in bits. */
#define CRYS_RSA_KG_PUB_EXP_MAX_SIZE_BITS    17
/*! Definition of public exponent value. */
#define CRYS_RSA_KG_PUB_EXP_ALLOW_VAL_1      0x000003
/*! Definition of public exponent value. */
#define CRYS_RSA_KG_PUB_EXP_ALLOW_VAL_2      0x000011
/*! Definition of public exponent value. */
#define CRYS_RSA_KG_PUB_EXP_ALLOW_VAL_3      0x010001




/***********************************************************************************************/

/*!
@brief CRYS_RSA_KG_GenerateKeyPair generates a Pair of public and private keys on non CRT mode according to [ANS X9.31].

\note    To be FIPS 186-4 [5.1] compliant use only the following key sizes (in bits): 1024, 2048 and 3072.

@return CRYS_OK on success.
@return A non-zero value from crys_rsa_error.h or crys_rnd_error.h on failure.

*/

CIMPORT_C CRYSError_t CRYS_RSA_KG_GenerateKeyPair(
                                        void   *rndState_ptr,                 /*!< [in/out] Pointer to the RND state structure. */
                                        SaSiRndGenerateVectWorkFunc_t rndGenerateVectFunc,   /*!< [in] Pointer to the random vector generation function. */
                                        uint8_t             *pubExp_ptr,            /*!< [in]  The pointer to the public exponent (public key). */
                                        uint16_t             pubExpSizeInBytes,     /*!< [in]  The public exponent size in bytes. */
                                        uint32_t             keySize,               /*!< [in]  The size of the key, in bits. Supported sizes are
                                                   512, 1024, 2048, 3072 and 4096 bit. */
                                        CRYS_RSAUserPrivKey_t *userPrivKey_ptr,     /*!< [out] Pointer to the private key structure. */
                                        CRYS_RSAUserPubKey_t  *userPubKey_ptr,      /*!< [out] Pointer to the public key structure. */
                    CRYS_RSAKGData_t      *keyGenData_ptr,      /*!< [in]  Pointer to a temporary structure required for the KeyGen operation. */
                                        CRYS_RSAKGFipsContext_t    *pFipsCtx        /*!< [in]  Pointer to temporary buffer used in case FIPS certification if required. */
);

/***********************************************************************************************/
/*!
@brief Generates a pair of public and private keys on CRT mode according to [ANS X9.31].

\note    To be FIPS 186-4 [5.1] compliant use only the following key sizes (in bits): 1024, 2048 and 3072.

@return CRYS_OK on success.
@return A non-zero value from crys_rsa_error.h or crys_rnd_error.h on failure.
*/

CIMPORT_C CRYSError_t CRYS_RSA_KG_GenerateKeyPairCRT(
                                        void   *rndState_ptr,                 /*!< [in/out] Pointer to the RND state structure. */
                                        SaSiRndGenerateVectWorkFunc_t rndGenerateVectFunc,   /*!< [in] Pointer to the random vector generation function. */
                                        uint8_t             *pubExp_ptr,           /*!< [in]  The pointer to the public exponent (public key). */
                                        uint16_t             pubExpSizeInBytes,    /*!< [in]  The public exponent size in bytes. */
                                        uint32_t             keySize,              /*!< [in]  The size of the key, in bits. Supported sizes are
                                                                                              512, 1024, 2048, 3072 and 4096 bit. */
                                        CRYS_RSAUserPrivKey_t *userPrivKey_ptr,    /*!< [out] Pointer to the private key structure. */
                                        CRYS_RSAUserPubKey_t  *userPubKey_ptr,     /*!< [out] Pointer to the public key structure. */
                                        CRYS_RSAKGData_t      *keyGenData_ptr,     /*!< [in] Pointer to a temporary structure required for the KeyGen operation. */
                                        CRYS_RSAKGFipsContext_t    *pFipsCtx       /*!< [in] Pointer to temporary buffer used in case FIPS certification if required. */
);


#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif


