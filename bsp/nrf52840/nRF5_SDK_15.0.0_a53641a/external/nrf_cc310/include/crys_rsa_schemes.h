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



#ifndef CRYS_RSA_SCHEMES_H
#define CRYS_RSA_SCHEMES_H


#include "crys_error.h"
#include "crys_rsa_types.h"
#include "crys_rnd.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief This module defines APIs that support [PKCS1_1.5] and [PKCS1_2.1] encryption and signature schemes.
@defgroup crys_rsa_schemes CryptoCell RSA encryption and signature schemes
@{
@ingroup crys_rsa
*/

/**********************************************************************************************************/
/*!
@brief This function implements the Encrypt algorithm, as defined in [PKCS1_2.1] and [PKCS1_1.5].

It should not be called directly. Instead, use macros ::CRYS_RSA_OAEP_Encrypt or ::CRYS_RSA_PKCS1v15_Encrypt.

@return CRYS_OK on success.
@return A non-zero value from crys_rsa_error.h, crys_rnd_error.h or crys_hash_error.h on failure.
*/
CIMPORT_C CRYSError_t SaSi_RsaSchemesEncrypt(
                        void   *rndState_ptr,           /*!< [in/out] Pointer to the RND state structure. */
                        SaSiRndGenerateVectWorkFunc_t rndGenerateVectFunc,   /*!< [in] Pointer to the random vector generation function. */
                        CRYS_RSAUserPubKey_t  *UserPubKey_ptr,      /*!< [in]  Pointer to the public key data structure. */
                        CRYS_RSAPrimeData_t   *PrimeData_ptr,       /*!< [in]  Pointer to a temporary structure that is internally used as workspace for the
                                           Encryption operation. */
                        CRYS_RSA_HASH_OpMode_t hashFunc,            /*!< [in]  The HASH function to be used. One of the supported SHA-x HASH modes, as defined
                                           in ::CRYS_RSA_HASH_OpMode_t (MD5 is not supported).*/
                        uint8_t  *L,                                /*!< [in]  The label input pointer. Relevant for [PKCS1_2.1] only. NULL by default.
                                           NULL for [PKCS1_1.5]. */
                        uint16_t  Llen,                             /*!< [in]  The label length. Relevant for [PKCS1_2.1] only. Zero by default.
                                           Must be <=2048. Zero for [PKCS1_1.5]. */
                        CRYS_PKCS1_MGF_t MGF,                       /*!< [in]  The mask generation function. [PKCS1_2.1] defines MGF1, so the only value
                                           allowed here is CRYS_PKCS1_MGF1. */
                        uint8_t   *DataIn_ptr,                      /*!< [in]  Pointer to the data to encrypt. */
                        uint16_t   DataInSize,                      /*!< [in]  The size (in bytes) of the data to encrypt. The data size must be:
                                                                                - For [PKCS1_2.1], DataSize <= modulus size - 2*HashLen - 2.
                                                                                - For [PKCS1_1.5], DataSize <= modulus size - 11. */
                        uint8_t   *Output_ptr,                      /*!< [out] Pointer to the encrypted data. The buffer must be at least modulus size bytes long. */
                        CRYS_PKCS1_version  PKCS1_ver               /*!< [in]  [PKCS1_1.5] or [PKCS1_2.1], according to the functionality required. */
);

/*!
   @brief
   CRYS_RSA_OAEP_PSS21_Encrypt implements the RSAES-OAEP algorithm
   as defined in PKCS#1 v2.1 8.1.

   \note It is not recommended to use hash MD5 in OAEP PKCS1 ver 2.1, therefore
    it is not supported.

   This function combines the RSA encryption primitive and the
   EME-OAEP encoding method, to provide an RSA-based encryption
   method that is semantically secure against adaptive
   chosen-ciphertext attacks. For additional details, please refer to
   the PKCS#1 standard.
*/
#define CRYS_RSA_OAEP_Encrypt(rndState_ptr, rndGenerateVectFunc, UserPubKey_ptr,PrimeData_ptr,HashMode,L,Llen,MGF,Data_ptr,DataSize,Output_ptr)\
        SaSi_RsaSchemesEncrypt(rndState_ptr, rndGenerateVectFunc, UserPubKey_ptr,PrimeData_ptr,HashMode,L,Llen,MGF,Data_ptr,DataSize,Output_ptr,CRYS_PKCS1_VER21)

/*!
   @brief
   CRYS_RSA_PKCS1v15_Encrypt implements the RSAES-PKCS1v15 algorithm
   as defined in PKCS#1 v2.1 8.2.
*/
#define CRYS_RSA_PKCS1v15_Encrypt(rndState_ptr, rndGenerateVectFunc, UserPubKey_ptr,PrimeData_ptr,DataIn_ptr,DataInSize,Output_ptr)\
        SaSi_RsaSchemesEncrypt(rndState_ptr, rndGenerateVectFunc, UserPubKey_ptr,PrimeData_ptr,CRYS_RSA_HASH_NO_HASH_mode,NULL,0,CRYS_PKCS1_NO_MGF,DataIn_ptr, \
        DataInSize, Output_ptr,CRYS_PKCS1_VER15)


/**********************************************************************************************************/
/*!
@brief This function implements the Decrypt algorithm, as defined in [PKCS1_2.1] and [PKCS1_1.5].

It should not be called directly. Instead, use macros ::CRYS_RSA_OAEP_Decrypt or ::CRYS_RSA_PKCS1v15_Decrypt.

@return CRYS_OK on success.
@return A non-zero value from crys_rsa_error.h or crys_hash_error.h on failure.
*/
CIMPORT_C CRYSError_t SaSi_RsaSchemesDecrypt(
                                CRYS_RSAUserPrivKey_t  *UserPrivKey_ptr,    /*!< [in]  Pointer to the private key data structure of the user. */
                                CRYS_RSAPrimeData_t    *PrimeData_ptr,      /*!< [in]  Pointer to a temporary structure that is internally used as workspace
                                               for the decryption operation. */
                                CRYS_RSA_HASH_OpMode_t  hashFunc,           /*!< [in]  The HASH function to be used. One of the supported SHA-x HASH modes,
                                               as defined in ::CRYS_RSA_HASH_OpMode_t (MD5 is not supported). */
                                uint8_t                 *L,                 /*!< [in]  The label input pointer. Relevant for [PKCS1_2.1] only. NULL by default.
                                               NULL for [PKCS1_1.5]. */
                                uint16_t              Llen,                 /*!< [in]  The label length. Relevant for [PKCS1_2.1] only. Zero by default.
                                               Zero for [PKCS1_1.5]. */
                                CRYS_PKCS1_MGF_t        MGF,                /*!< [in]  The mask generation function. [PKCS1_2.1] defines MGF1, so the only
                                               value allowed here is CRYS_PKCS1_MGF1. */
                                uint8_t              *DataIn_ptr,           /*!< [in]  Pointer to the data to decrypt. */
                                uint16_t              DataInSize,           /*!< [in]  The size (in bytes) of the data to decrypt. DataSize must be &le;
                                               the modulus size. */
                                uint8_t              *Output_ptr,           /*!< [in]  Pointer to the decrypted data. The buffer must be at least
                                               PrivKey_ptr->N.len bytes long (i.e. the modulus size in bytes). */
                                uint16_t             *OutputSize_ptr,       /*!< [in]  Pointer to the byte size of the buffer pointed to by Output_buffer.
                                               The size must be:
                                                                                       <ul><li> For PKCS #1 v2.1: Modulus size > OutputSize >=
                                                (modulus size - 2*HashLen - 2).</li>
                                                                                       <li> For PKCS #1 v1.5: Modulus size > OutputSize >= (modulus size - 11).
                                                                                        The value pointed by OutputSize_ptr is updated after decryption with
                                            the actual number of bytes that are loaded to Output_ptr.</li></ul> */
                                CRYS_PKCS1_version      PKCS1_ver           /*!< [in]  [PKCS1_1.5] or [PKCS1_2.1], according to the functionality required. */
);

/**********************************************************************************************************/
/**
   @brief
   CRYS_RSA_OAEP_Decrypt implements the RSAES-OAEP algorithm
   as defined in PKCS#1 v2.1 8.1.

   \note It is not recommended to use hash MD5 in OAEP PKCS1 ver 2.1, therefore
   it is not supported.

   This function combines the RSA decryption primitive and the
   EME-OAEP encoding method, to provide an RSA-based decryption
   method that is semantically secure against adaptive
   chosen-ciphertext attacks. For more details, please refer to
   the PKCS#1 standard.

*/
#define CRYS_RSA_OAEP_Decrypt(UserPrivKey_ptr,PrimeData_ptr,HashMode,L,Llen,MGF,Data_ptr,DataSize,Output_ptr,OutputSize_ptr)\
        SaSi_RsaSchemesDecrypt(UserPrivKey_ptr,PrimeData_ptr,HashMode,L,Llen,MGF,Data_ptr,DataSize,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER21)


/**
   @brief
   CRYS_RSA_PKCS1v15_Decrypt implements the RSAES-PKCS1v15 algorithm as defined
   in PKCS#1 v2.1 8.2.
*/
#define CRYS_RSA_PKCS1v15_Decrypt(UserPrivKey_ptr,PrimeData_ptr,DataIn_ptr,DataInSize,Output_ptr,OutputSize_ptr)\
        SaSi_RsaSchemesDecrypt(UserPrivKey_ptr,PrimeData_ptr,CRYS_RSA_HASH_NO_HASH_mode,NULL,0,CRYS_PKCS1_NO_MGF,DataIn_ptr,DataInSize,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER15)


/**********************************************************************************************************/
/*!
@brief Implements the Signing algorithm, as defined in [PKCS1_1.5] or [PKCS1_2.1], using a single function.

The input data may be either a non-hashed data or a digest of a hash function.
For a non-hashed data, the input data will be hashed using the hash function indicated by ::CRYS_RSA_HASH_OpMode_t.
For a digest, ::CRYS_RSA_HASH_OpMode_t should indicate the hash function that the input data was created by, and it will not be hashed.

@return CRYS_OK on success.
@return A non-zero value from crys_rsa_error.h, crys_rnd_error.h or crys_hash_error.h on failure.
*/
CIMPORT_C CRYSError_t SaSi_RsaSign(
                   void   *rndState_ptr,                /*!< [in/out] Pointer to the RND state. */
                   SaSiRndGenerateVectWorkFunc_t rndGenerateVectFunc,   /*!< [in/out] Pointer to the RND Generate vector function pointer. */
                   CRYS_RSAPrivUserContext_t *UserContext_ptr,      /*!< [in]  Pointer to a temporary context for internal use. */
                   CRYS_RSAUserPrivKey_t *UserPrivKey_ptr,          /*!< [in]  Pointer to the private key data structure of the user.
                                                                               The representation (pair or quintuple) and hence the algorithm (CRT or not CRT)
                                           is determined by the Private Key build function -
                                                                               ::CRYS_RSA_Build_PrivKey or ::CRYS_RSA_Build_PrivKeyCRT. */
                   CRYS_RSA_HASH_OpMode_t rsaHashMode,              /*!< [in]  One of the supported SHA-x HASH modes, as defined in ::CRYS_RSA_HASH_OpMode_t.
                                           (MD5 is not supported). */
                   CRYS_PKCS1_MGF_t MGF,                            /*!< [in]  The mask generation function. [PKCS1_2.1] defines only MGF1, so the only value
                                           allowed for [PKCS1_2.1] is CRYS_PKCS1_MGF1. */
                   uint16_t     SaltLen,                            /*!< [in]  The Length of the Salt buffer (relevant for PKCS#1 Ver 2.1 only, typically lengths is 0 or hash Len).
                                                                               FIPS 186-4 requires, that SaltLen <= hash len. If SaltLen > KeySize - hash Len - 2, the function
                                                                               returns an error.  */
                   uint8_t     *DataIn_ptr,                         /*!< [in]  Pointer to the input data to be signed.
                                                                               The size of the scatter/gather list representing the data buffer is limited to 128
                                           entries, and the size of each entry is limited to 64KB (fragments larger than
                                           64KB are broken into fragments <= 64KB). */
                   uint32_t     DataInSize,                         /*!< [in]  The size (in bytes) of the data to sign. */
                   uint8_t     *Output_ptr,                         /*!< [out] Pointer to the signature. The buffer must be at least PrivKey_ptr->N.len bytes
                                           long (i.e. the modulus size in bytes). */
                   uint16_t    *OutputSize_ptr,                     /*!< [in/out] Pointer to the signature size value - the input value is the signature
                                          buffer size allocated, the output value is the signature size used.
                                                                                  he buffer must be equal to PrivKey_ptr->N.len bytes long
                                          (i.e. the modulus size in bytes). */
                   CRYS_PKCS1_version PKCS1_ver                     /*!< [in]  [PKCS1_1.5] or [PKCS1_2.1], according to the functionality required. */
);


/*!
@brief CRYS_RSA_PKCS1v15_Sign implements the RSASSA-PKCS1v15 algorithm as defined in PKCS#1 v1.5.

This function combines the RSASP1 signature primitive and the EMSA-PKCS1v15 encoding method, to provide an RSA-based signature scheme.
For more details, please refer to the PKCS#1 standard.
 */

#define CRYS_RSA_PKCS1v15_Sign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,hashFunc,DataIn_ptr,DataInSize,Output_ptr,OutputSize_ptr)\
        SaSi_RsaSign(rndState_ptr, rndGenerateVectFunc, (UserContext_ptr),(UserPrivKey_ptr),(hashFunc),(CRYS_PKCS1_NO_MGF),0,(DataIn_ptr),(DataInSize),(Output_ptr),(OutputSize_ptr),CRYS_PKCS1_VER15)


/*!
@brief CRYS_RSA_PKCS1v15_SHA1_Sign implements the RSASSA-PKCS1v15 algorithm as defined in PKCS#1 v1.5, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-1.

\note The data_in size is already known after the Hash.
*/
#define CRYS_RSA_PKCS1v15_SHA1_Sign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,DataIn_ptr,Output_ptr,OutputSize_ptr)\
        SaSi_RsaSign(rndState_ptr, rndGenerateVectFunc, (UserContext_ptr),(UserPrivKey_ptr),(CRYS_RSA_After_SHA1_mode),(CRYS_PKCS1_NO_MGF),0,(DataIn_ptr),CRYS_HASH_SHA1_DIGEST_SIZE_IN_BYTES,(Output_ptr),(OutputSize_ptr),CRYS_PKCS1_VER15)

/*!
@brief CRYS_RSA_PKCS1v15_MD5_Sign implements the RSASSA-PKCS1v15 algorithm as defined in PKCS#1 v1.5, but without performing a HASH function -
it assumes that the data in has already been hashed using MD5.

\note The data_in size is already known after the Hash.
*/

#define CRYS_RSA_PKCS1v15_MD5_Sign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,DataIn_ptr,Output_ptr,OutputSize_ptr)\
        SaSi_RsaSign(rndState_ptr, rndGenerateVectFunc, (UserContext_ptr),(UserPrivKey_ptr),CRYS_RSA_After_MD5_mode,CRYS_PKCS1_NO_MGF,0,(DataIn_ptr),CRYS_HASH_MD5_DIGEST_SIZE_IN_BYTES,(Output_ptr),(OutputSize_ptr),CRYS_PKCS1_VER15)


/*!
@brief CRYS_RSA_PKCS1v15_SHA224_Sign implements the RSASSA-PKCS1v15 algorithm as defined in PKCS#1 v1.5, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-224.

\note The data_in size is already known after the Hash.
*/
#define CRYS_RSA_PKCS1v15_SHA224_Sign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,DataIn_ptr,Output_ptr,OutputSize_ptr)\
        SaSi_RsaSign(rndState_ptr, rndGenerateVectFunc, (UserContext_ptr),(UserPrivKey_ptr),(CRYS_RSA_After_SHA224_mode),(CRYS_PKCS1_NO_MGF),0,(DataIn_ptr),CRYS_HASH_SHA224_DIGEST_SIZE_IN_BYTES,(Output_ptr),(OutputSize_ptr),CRYS_PKCS1_VER15)


/*!
@brief CRYS_RSA_PKCS1v15_SHA256_Sign implements the RSASSA-PKCS1v15 algorithm as defined in PKCS#1 v1.5, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-256.

\note The data_in size is already known after the Hash.
*/
#define CRYS_RSA_PKCS1v15_SHA256_Sign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,DataIn_ptr,Output_ptr,OutputSize_ptr)\
        SaSi_RsaSign(rndState_ptr, rndGenerateVectFunc, (UserContext_ptr),(UserPrivKey_ptr),(CRYS_RSA_After_SHA256_mode),(CRYS_PKCS1_NO_MGF),0,(DataIn_ptr),CRYS_HASH_SHA256_DIGEST_SIZE_IN_BYTES,(Output_ptr),(OutputSize_ptr),CRYS_PKCS1_VER15)

/*!
@brief CRYS_RSA_PKCS1v15_SHA1_Sign implements the RSASSA-PKCS1v15 algorithm as defined in PKCS#1 v1.5, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-384.

\note The data_in size is already known after the Hash.
*/
#define CRYS_RSA_PKCS1v15_SHA384_Sign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,DataIn_ptr,Output_ptr,OutputSize_ptr)\
        SaSi_RsaSign(rndState_ptr, rndGenerateVectFunc, (UserContext_ptr),(UserPrivKey_ptr),(CRYS_RSA_After_SHA384_mode),(CRYS_PKCS1_NO_MGF),0,(DataIn_ptr),CRYS_HASH_SHA384_DIGEST_SIZE_IN_BYTES,(Output_ptr),(OutputSize_ptr),CRYS_PKCS1_VER15)


/*!
@brief CRYS_RSA_PKCS1v15_SHA512_Sign implements the RSASSA-PKCS1v15 algorithm  as defined in PKCS#1 v1.5, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-512.

\note The data_in size is already known after the Hash.
*/
#define CRYS_RSA_PKCS1v15_SHA512_Sign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,DataIn_ptr,Output_ptr,OutputSize_ptr)\
        SaSi_RsaSign(rndState_ptr, rndGenerateVectFunc, (UserContext_ptr),(UserPrivKey_ptr),(CRYS_RSA_After_SHA512_mode),(CRYS_PKCS1_NO_MGF),0,(DataIn_ptr),CRYS_HASH_SHA512_DIGEST_SIZE_IN_BYTES,(Output_ptr),(OutputSize_ptr),CRYS_PKCS1_VER15)



/*!
@brief CRYS_RSA_PSS_Sign implements the RSASSA-PSS algorithm as defined in PKCS#1 v2.1 9.1, in a single function call.

\note According to the PKCS#1 ver2.1 it is not recommended to use MD5 Hash, therefore it is not supported.

The actual macro that is used by the user is ::CRYS_RSA_PSS_Sign.
*/

#define CRYS_RSA_PSS_Sign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,hashFunc,MGF,SaltLen,DataIn_ptr,DataInSize,Output_ptr,OutputSize_ptr)\
        SaSi_RsaSign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,hashFunc,MGF,SaltLen,DataIn_ptr,DataInSize,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA1_Sign implements the RSASSA-PSS algorithm as defined in PKCS#1 v2.1 9.1 in a single function call, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-1.

\note The data_in size is already known after the Hash.

The actual macro that is used by the users is ::CRYS_RSA_PSS_SHA1_Sign.
*/

#define CRYS_RSA_PSS_SHA1_Sign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,MGF,SaltLen,DataIn_ptr,Output_ptr,OutputSize_ptr)\
        SaSi_RsaSign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,CRYS_RSA_After_SHA1_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA1_DIGEST_SIZE_IN_BYTES,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA224_Sign implements the RSASSA-PSS algorithm as defined in PKCS#1 v2.1 9.1 in a single function call, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-224.

\note The data_in size is already known after the Hash.

The actual macro that is used by the users is ::CRYS_RSA_PSS_SHA224_Sign.
*/

#define CRYS_RSA_PSS_SHA224_Sign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,MGF,SaltLen,DataIn_ptr,Output_ptr,OutputSize_ptr)\
        SaSi_RsaSign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,CRYS_RSA_After_SHA224_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA224_DIGEST_SIZE_IN_BYTES,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA256_Sign implements the RSASSA-PSS algorithm as defined in PKCS#1 v2.1 9.1 in a single function call, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-256.

\note The data_in size is already known after the Hash.

The actual macro that is used by the users is ::CRYS_RSA_PSS_SHA256_Sign.
*/

#define CRYS_RSA_PSS_SHA256_Sign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,MGF,SaltLen,DataIn_ptr,Output_ptr,OutputSize_ptr)\
        SaSi_RsaSign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,CRYS_RSA_After_SHA256_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA256_DIGEST_SIZE_IN_BYTES,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA384_Sign implements the RSASSA-PSS algorithm as defined in PKCS#1 v2.1 9.1 in a single function call, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-384.

\note The data_in size is already known after the Hash.

The actual macro that is used by the users is ::CRYS_RSA_PSS_SHA384_Sign.
*/

#define CRYS_RSA_PSS_SHA384_Sign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,MGF,SaltLen,DataIn_ptr,Output_ptr,OutputSize_ptr)\
        SaSi_RsaSign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,CRYS_RSA_After_SHA384_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA384_DIGEST_SIZE_IN_BYTES,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA512_Sign implements the RSASSA-PSS algorithm as defined in PKCS#1 v2.1 9.1 in a single function call, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-512.

\note The data_in size is already known after the Hash.

The actual macro that is used by the users is ::CRYS_RSA_PSS_SHA512_Sign.
*/

#define CRYS_RSA_PSS_SHA512_Sign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,MGF,SaltLen,DataIn_ptr,Output_ptr,OutputSize_ptr)\
        SaSi_RsaSign(rndState_ptr, rndGenerateVectFunc, UserContext_ptr,UserPrivKey_ptr,CRYS_RSA_After_SHA512_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA512_DIGEST_SIZE_IN_BYTES,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER21)


/**********************************************************************************************************/
/*!
@brief Implements the RSA signature verification algorithms, in a single function call, as defined in referenced standards [PKCS1_1.5]
and [PKCS1_2.1].

The input data may be either a non-hashed data or a digest of a hash function.
For a non-hashed data, the input data will be hashed using the hash function indicated by ::CRYS_RSA_HASH_OpMode_t.
For a digest, ::CRYS_RSA_HASH_OpMode_t should indicate the hash function that the input data was created by, and it will not be hashed.

@return CRYS_OK on success.
@return A non-zero value from crys_rsa_error.h or crys_hash_error.h on failure.
*/

CIMPORT_C CRYSError_t SaSi_RsaVerify(
                            CRYS_RSAPubUserContext_t *UserContext_ptr,      /*!< [in]  Pointer to a temporary context for internal use. */
                            CRYS_RSAUserPubKey_t *UserPubKey_ptr,           /*!< [in]  Pointer to the public key data structure of the user. */
                            CRYS_RSA_HASH_OpMode_t rsaHashMode,             /*!< [in]  One of the supported SHA-x HASH modes, as defined in ::CRYS_RSA_HASH_OpMode_t.
                                               (MD5 is not supported). */
                            CRYS_PKCS1_MGF_t MGF,                           /*!< [in]  The mask generation function. [PKCS1_2.1] defines only MGF1, so the only
                                               value allowed for [PKCS_2.1] is CRYS_PKCS1_MGF1. */
                            uint16_t SaltLen,                               /*!< [in]  The Length of the Salt buffer. Relevant only for [PKCS1_2.1].
                                               Typical lengths are 0 or hash Len (20 for SHA-1).
                                                                                       The maximum length allowed is [modulus size - hash Len - 2]. */
                            uint8_t     *DataIn_ptr,                        /*!< [in]  Pointer to the input data to be verified.
                                                                                        The size of the scatter/gather list representing the data buffer is
                                            limited to 128 entries, and the size of each entry is limited to 64KB
                                            (fragments larger than 64KB are broken into fragments <= 64KB). */
                            uint32_t     DataInSize,                        /*!< [in]  The size (in bytes) of the data whose signature is to be verified. */
                            uint8_t     *Sig_ptr,                           /*!< [in]  Pointer to the signature to be verified.
                                                                                       The length of the signature is PubKey_ptr->N.len bytes
                                               (i.e. the modulus size in bytes). */
                            CRYS_PKCS1_version PKCS1_ver                    /*!< [in]  [PKCS1_1.5] or [PKCS1_2.1], according to the functionality required. */
);

/*!
@brief CRYS_RSA_PKCS1v15_Verify implements the RSASSA-PKCS1v15 Verify algorithm as defined in PKCS#1 v1.5.
*/
#define CRYS_RSA_PKCS1v15_Verify(UserContext_ptr,UserPubKey_ptr,hashFunc,DataIn_ptr,DataInSize,Sig_ptr)\
        SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,hashFunc,CRYS_PKCS1_NO_MGF,0,DataIn_ptr,DataInSize,Sig_ptr,CRYS_PKCS1_VER15)


/*!
@brief CRYS_RSA_PKCS1v15_MD5_Verify implements the RSASSA-PKCS1v15 Verify algorithm as defined in PKCS#1 v1.5, but without operating the HASH function -
it assumes the DataIn_ptr data has already been hashed using MD5.
*/
#define CRYS_RSA_PKCS1v15_MD5_Verify(UserContext_ptr,UserPubKey_ptr,DataIn_ptr,Sig_ptr)\
        SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_MD5_mode,CRYS_PKCS1_NO_MGF,0,DataIn_ptr,CRYS_HASH_MD5_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER15)


/*!
@brief CRYS_RSA_PKCS1v15_SHA1_Verify implements the RSASSA-PKCS1v15 Verify algorithm as defined in PKCS#1 v1.5, but without operating the HASH function -
it assumes that the DataIn_ptr data has already been hashed using SHA1.

*/
#define CRYS_RSA_PKCS1v15_SHA1_Verify(UserContext_ptr,UserPubKey_ptr,DataIn_ptr,Sig_ptr)\
        SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA1_mode,CRYS_PKCS1_NO_MGF,0,DataIn_ptr,CRYS_HASH_SHA1_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER15)

/*!
@brief CRYS_RSA_PKCS1v15_SHA224_Verify implements the RSASSA-PKCS1v15 Verify algorithm as defined in PKCS#1 v1.5, but without operating the HASH function -
it assumes that the DataIn_ptr data has already been hashed using SHA224.

*/
#define CRYS_RSA_PKCS1v15_SHA224_Verify(UserContext_ptr,UserPubKey_ptr,DataIn_ptr,Sig_ptr)\
        SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA224_mode,CRYS_PKCS1_NO_MGF,0,DataIn_ptr,CRYS_HASH_SHA224_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER15)

/*!
@brief CRYS_RSA_PKCS1v15_SHA256_Verify implements the RSASSA-PKCS1v15 Verify algorithm as defined in PKCS#1 v1.5, but without operating the HASH function -
it assumes that the DataIn_ptr data has already been hashed using SHA256.

*/
#define CRYS_RSA_PKCS1v15_SHA256_Verify(UserContext_ptr,UserPubKey_ptr,DataIn_ptr,Sig_ptr)\
        SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA256_mode,CRYS_PKCS1_NO_MGF,0,DataIn_ptr,CRYS_HASH_SHA256_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER15)

/*!
@brief CRYS_RSA_PKCS1v15_SHA384_Verify implements the RSASSA-PKCS1v15 Verify algorithm as defined in PKCS#1 v1.5, but without operating the HASH function -
it assumes that the DataIn_ptr data has already been hashed using SHA384.

*/
#define CRYS_RSA_PKCS1v15_SHA384_Verify(UserContext_ptr,UserPubKey_ptr,DataIn_ptr,Sig_ptr)\
        SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA384_mode,CRYS_PKCS1_NO_MGF,0,DataIn_ptr,CRYS_HASH_SHA384_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER15)

/*!
@brief CRYS_RSA_PKCS1v15_SHA512_Verify implements the RSASSA-PKCS1v15 Verify algorithm as defined in PKCS#1 v1.5, but without operating the HASH function -
it assumes that the DataIn_ptr data has already been hashed using SHA512.

*/
#define CRYS_RSA_PKCS1v15_SHA512_Verify(UserContext_ptr,UserPubKey_ptr,DataIn_ptr,Sig_ptr)\
        SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA512_mode,CRYS_PKCS1_NO_MGF,0,DataIn_ptr,CRYS_HASH_SHA512_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER15)

/*!
@brief CRYS_RSA_PSS_Verify implements the RSASSA-PKCS1v21 Verify algorithm as defined in PKCS#1 v2.1.
*/

#define CRYS_RSA_PSS_Verify(UserContext_ptr,UserPubKey_ptr,hashFunc,MGF,SaltLen,DataIn_ptr,DataInSize,Sig_ptr)\
        SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,hashFunc,MGF,SaltLen,DataIn_ptr,DataInSize,Sig_ptr,CRYS_PKCS1_VER21)

                  /*!
@brief CRYS_RSA_PSS_SHA1_Verify implements the PKCS1v21 Verify algorithm as defined in PKCS#1 v2.1, but without operating the HASH function -
it assumes the DataIn_ptr has already been hashed using SHA1.

*/

#define CRYS_RSA_PSS_SHA1_Verify(UserContext_ptr,UserPubKey_ptr,MGF,SaltLen,DataIn_ptr,Sig_ptr)\
        SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA1_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA1_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA224_Verify implements the PKCS1v21 Verify algorithm as defined in PKCS#1 v2.1, but without operating the HASH function -
it assumes the DataIn_ptr has already been hashed using SHA224.
*/

#define CRYS_RSA_PSS_SHA224_Verify(UserContext_ptr,UserPubKey_ptr,MGF,SaltLen,DataIn_ptr,Sig_ptr)\
        SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA224_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA224_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER21)

/*!
@brief CRYS_RSA_PSS_SHA256_Verify implements the PKCS1v21 Verify algorithm as defined in PKCS#1 v2.1, but without operating the HASH function -
it assumes the DataIn_ptr has already been hashed using SHA256.

*/

#define CRYS_RSA_PSS_SHA256_Verify(UserContext_ptr,UserPubKey_ptr,MGF,SaltLen,DataIn_ptr,Sig_ptr)\
        SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA256_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA256_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA384_Verify implements the PKCS1v21 Verify algorithm as defined in PKCS#1 v2.1, but without operating the HASH function -
it assumes the DataIn_ptr has already been hashed using SHA384.

*/

#define CRYS_RSA_PSS_SHA384_Verify(UserContext_ptr,UserPubKey_ptr,MGF,SaltLen,DataIn_ptr,Sig_ptr)\
        SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA384_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA384_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA512_Verify implements the PKCS1v21 Verify algorithm as defined in PKCS#1 v2.1, but without operating the HASH function -
it assumes the DataIn_ptr has already been hashed using SHA512.
*/

#define CRYS_RSA_PSS_SHA512_Verify(UserContext_ptr,UserPubKey_ptr,MGF,SaltLen,DataIn_ptr,Sig_ptr)\
        SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA512_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA512_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER21)

/**********************************************************************************************************/


#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif
