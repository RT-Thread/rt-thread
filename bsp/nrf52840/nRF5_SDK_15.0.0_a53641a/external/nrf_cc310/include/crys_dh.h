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




#ifndef _CRYS_DH_H
#define _CRYS_DH_H

#include "crys_rsa_types.h"
#include "crys_kdf.h"
#include "crys_rnd.h"

#ifdef __cplusplus
extern "C"
{
#endif


/*!
@file
@brief This module defines the API that supports Diffie-Hellman key exchange, as defined in [PKCS3] and in [X9.42] (key lengths 1024 and 2048 bits).
@defgroup crys_dh CryptoCell DH APIs
@{
@ingroup cryptocell_api
*/


/************************ Defines ******************************/
/*! Defintion for DH public key.*/
#define CRYS_DHPubKey_t  CRYSRSAPubKey_t

/*! Maximal valid key size in bits.*/
#define CRYS_DH_MAX_VALID_KEY_SIZE_VALUE_IN_BITS  CRYS_RSA_MAX_VALID_KEY_SIZE_VALUE_IN_BITS /*!< \internal RL restrict to 2048 */
/*! Minimal valid key size in bits.*/
#define CRYS_DH_MIN_VALID_KEY_SIZE_VALUE_IN_BITS  1024 /*!< Size limitation according to ANSI standard */
/*! Maximal modulus size in bytes.*/
#define CRYS_DH_MAX_MOD_SIZE_IN_BYTES   (CRYS_DH_MAX_VALID_KEY_SIZE_VALUE_IN_BITS / SASI_BITS_IN_BYTE)
/*! Maximal modulus size in words.*/
#define CRYS_DH_MAX_MOD_SIZE_IN_WORDS   (CRYS_DH_MAX_MOD_SIZE_IN_BYTES/sizeof(uint32_t))

/*! Modulus buffer size in words.*/
#define CRYS_DH_MAX_MOD_BUFFER_SIZE_IN_WORDS (CRYS_DH_MAX_MOD_SIZE_IN_WORDS + 2)
/*! Maximal domain generation size in bits.*/
#define CRYS_DH_DOMAIN_GENERATION_MAX_SIZE_BITS   CRYS_RSA_MAX_KEY_GENERATION_SIZE_BITS /*!< \internal RL restrict to 2048 */

/*! Defintion for DH primitives data.*/
#define CRYS_DHPrimeData_t   CRYS_RSAPrimeData_t
/*! Defintion for DH public key.*/
#define CRYS_DHUserPubKey_t  CRYS_RSAUserPubKey_t
/*! Defintion for DH other info.*/
#define CRYS_DH_OtherInfo_t  CRYS_KDF_OtherInfo_t

/*! Keying data size is in bytes*/
#define CRYS_DH_MAX_SIZE_OF_KEYING_DATA  CRYS_KDF_MAX_SIZE_OF_KEYING_DATA

/************************ Enums ********************************/

/*! DH operations mode */
typedef enum
{
    /*! PKCS3 operation mode. */
    CRYS_DH_PKCS3_mode  = 0,
    /*! ANSI X942 operation mode. */
    CRYS_DH_ANSI_X942_mode = 1,
    /*! Total number of operation modes. */
    CRYS_DH_NumOfModes,

    /*! Reserved. */
    CRYS_DH_OpModeLast    = 0x7FFFFFFF,

}CRYS_DH_OpMode_t;

/*! HASH operation modes */
typedef enum
{
    /*! SHA1 operation mode. */
    CRYS_DH_HASH_SHA1_mode      = CRYS_HASH_SHA1_mode,
    /*! SHA224 operation mode. */
    CRYS_DH_HASH_SHA224_mode    = CRYS_HASH_SHA224_mode,
    /*! SHA256 operation mode. */
    CRYS_DH_HASH_SHA256_mode    = CRYS_HASH_SHA256_mode,
    /*! SHA384 operation mode. */
    CRYS_DH_HASH_SHA384_mode    = CRYS_HASH_SHA384_mode,
    /*! SHA512 operation mode. */
    CRYS_DH_HASH_SHA512_mode    = CRYS_HASH_SHA512_mode,
    /*! MD5 operation mode (not used in DH). */
    CRYS_DH_HASH_MD5_mode           = CRYS_HASH_MD5_mode, /*!< \internal not used in DH */
    /*! Total number of HASH modes. */
    CRYS_DH_HASH_NumOfModes     = CRYS_HASH_MD5_mode,
    /*! Reserved. */
    CRYS_DH_HASH_OperationModeLast  = 0x7FFFFFFF,

}CRYS_DH_HASH_OpMode_t;

/*! Key derivation modes. */
typedef enum
{
    /*! ASN1 derivation mode.*/
    CRYS_DH_ASN1_Der_mode    = CRYS_KDF_ASN1_DerivMode,
    /*! Concatination derivation mode.*/
    CRYS_DH_Concat_Der_mode  = CRYS_KDF_ConcatDerivMode,
    /*! X963 derivation mode.*/
    CRYS_DH_X963_DerMode    = CRYS_KDF_ConcatDerivMode,
    /*! Reserved. */
    CRYS_DH_DerivationFunc_ModeLast= 0x7FFFFFFF,

}CRYS_DH_DerivationFunc_Mode;


/************************ Typedefs  *************************************/
/*! Temporary buffer structure for internal usage.*/
typedef struct
{
    /*! Temporary primitives data */
    CRYS_DHPrimeData_t PrimeData;
    /*! Public key. */
    CRYS_DHPubKey_t    PubKey;
    /*! Temporary buffer for internal usage. */
    uint32_t TempBuff[CRYS_DH_MAX_MOD_BUFFER_SIZE_IN_WORDS];
} CRYS_DH_ExpTemp_t;

/*! Temporary buffer structure for internal usage. */
typedef struct
{
    /*! Temporary primitives data */
    CRYS_DHPrimeData_t PrimeData;
    /*! User's public key. */
    CRYS_DHUserPubKey_t    UserPubKey;
    /*! Temporary buffer for internal usage. */
    uint32_t TempBuff[CRYS_DH_MAX_MOD_BUFFER_SIZE_IN_WORDS];
} CRYS_DH_Temp_t;

/*! Temporary buffer structure for internal usage. */
typedef struct
{
    /*! Temporary primitives data */
    CRYS_DHPrimeData_t PrimeData;
    /*! User's public key. */
    CRYS_DHUserPubKey_t    UserPubKey;
    /*! Temporary buffer for internal usage. */
    uint32_t TempBuff[2*CRYS_DH_MAX_MOD_BUFFER_SIZE_IN_WORDS];
} CRYS_DH_HybrTemp_t;

/*! Defintion of buffer used for FIPS Known Answer Tests. */
typedef struct
{
    /*! Public key. */
    CRYS_DHUserPubKey_t pubKey;
    /*! Temporary primitives data */
    CRYS_DHPrimeData_t  primeData;
    /*! Buffer for the secret value.*/
    uint8_t secretBuff[CRYS_DH_MIN_VALID_KEY_SIZE_VALUE_IN_BITS/SASI_BITS_IN_BYTE];  // KAT tests uses 1024 bit key
} CRYS_DH_FipsKat_t;


/************************ Structs  **************************************/

/************************ Public Variables ******************************/

/************************ Public Functions ******************************/

/*******************************************************************************************/

/*!
@brief This function has two purposes:
<ol><li> Randomly generate the client private key according to the choosen version [PKCS3] or [ANSI X9.42].</li>
<li> Computes the client public key as follows: ClientPub = Generator^Prv mod Prime, where '^' is the symbol of exponentiation.</li></ol>
This function should not be called directly. Instead, use the macros ::CRYS_DH_PKCS3_GeneratePubPrv and ::CRYS_DH_ANSI_X942_GeneratePubPrv.
\note
All buffer parameters should be in Big-Endian form.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_dh_error.h, crys_rnd_error.h or crys_rsa_error.h.
 */
CIMPORT_C CRYSError_t _DX_DH_GeneratePubPrv(
                    void   *rndState_ptr,               /*!< [in/out] Pointer to the RND state structure. */
                    SaSiRndGenerateVectWorkFunc_t rndGenerateVectFunc, /*!< [in] Pointer to the random vector generation function. */
                    uint8_t *Generator_ptr,                         /*!< [in]  Pointer to the Generator octet string. */
                    uint16_t GeneratorSize,                         /*!< [in]  The size of the Generator string (in bytes). */
                    uint8_t *Prime_ptr,                             /*!< [in]  Pointer to the Prime octet string P (used as modulus in the algorithm). */
                    uint16_t PrimeSize,                             /*!< [in]  The size of the Prime string in bytes. */
                    uint16_t L,                                     /*!< [in]  Exact size in bits of the Prime to be generated (relevant only for [PKCS3]):
                                                                               <ul><li> If L!=0, force the private key to be [2^(L-1) ? Prv < 2^L], where '^'
                                            indicates exponentiation.</li>
                                                                               <li> If L = 0 then [0 < Prv < P-1].</li></ul> */
                    uint8_t *Q_ptr,                                 /*!< [in]  Relevant only for [ANSI X9.42] - Pointer to the Q octet string in the range:
                                                                                1 <= Prv <= Q-1 or 1 < Prv < Q-1. */
                    uint16_t QSize,                                 /*!< [in]  Relevant only for [ANSI X9.42] - Size of the Q string (in bytes). */
                    CRYS_DH_OpMode_t DH_mode,                       /*!< [in]  An enumerator declaring whether this is [PKCS3] or [ANSI X9.42] mode. */
                    CRYS_DHUserPubKey_t *tmpPubKey_ptr,             /*!< [in]  Pointer to a temporary buffer for public key structure. Used for the
                                                   exponentiation function. */
                    CRYS_DHPrimeData_t  *tmpPrimeData_ptr,          /*!< [in]  Pointer to a structure holding internal temporary buffers. */
                    uint8_t *ClientPrvKey_ptr,                      /*!< [out] Pointer to the Private key Prv. This buffer should be at least the following
                                           size (in bytes):
                                                                               <ul><li> If L is provided: (L+7)/8.</li>
                                                                               <li> If L is NULL: \p PrimeSize. </li></ul> */
                    uint16_t *ClientPrvKeySize_ptr,                 /*!< [in/out] Pointer to the Private key size:
                                                                                    <ul><li> Input - size of the given buffer.</li>
                                                                                    <li> Output - actual size of the generated private key.</li></ul> */
                    uint8_t *ClientPub1_ptr,                        /*!< [out] Pointer to the Public key. This buffer should be at least \p PrimeSize bytes. */
                    uint16_t *ClientPubSize_ptr                     /*!< [in/out] Pointer to the Public key size:
                                                                                  <ul><li> Input - size of the given buffer.</li>
                                                                                  <li> Output - actual size of the generated public key.</li></ul> */
);


/* macro for calling the GeneratePubPrv function on PKCS#3 mode:  Q is irrelevant */
/*--------------------------------------------------------------------------------*/
/*!
This macro is used to generate the public and private DH keys according to [PKCS3]. For a description of the parameters see ::_DX_DH_GeneratePubPrv.
*/
#define CRYS_DH_PKCS3_GeneratePubPrv(rndState_ptr, rndGenerateVectFunc, Generator_ptr,GeneratorSize,\
                Prime_ptr,PrimeSize,\
                L,\
                tmpPubKey_ptr,tmpPrimeData_ptr,\
                ClientPrvKey_ptr,ClientPrvKeySize_ptr,\
                ClientPub_ptr,ClientPubSize_ptr)\
        _DX_DH_GeneratePubPrv(rndState_ptr, rndGenerateVectFunc, (Generator_ptr),(GeneratorSize),\
                (Prime_ptr),(PrimeSize),\
                (L),\
                (uint8_t *)NULL,(uint16_t)0,\
                CRYS_DH_PKCS3_mode,\
                (tmpPubKey_ptr),(tmpPrimeData_ptr),\
                (ClientPrvKey_ptr),(ClientPrvKeySize_ptr),\
                (ClientPub_ptr),(ClientPubSize_ptr))

/*!
This macro is used to generate the public and private DH keys according to [ANSI X9.42]. For a description of the parameters see ::_DX_DH_GeneratePubPrv.
*/
#define CRYS_DH_ANSI_X942_GeneratePubPrv(rndState_ptr, rndGenerateVectFunc, Generator_ptr,GeneratorSize,Prime_ptr,PrimeSize,\
                Q_ptr,QSize,\
                tmpPubKey_ptr,tmpPrimeData_ptr,\
                ClientPrvKey_ptr,ClientPrvKeySize_ptr,\
                ClientPub_ptr,ClientPubSize_ptr)\
        _DX_DH_GeneratePubPrv(rndState_ptr, rndGenerateVectFunc, (Generator_ptr),(GeneratorSize),\
                (Prime_ptr),(PrimeSize),\
                (uint16_t)0,\
                (Q_ptr),(QSize),\
                CRYS_DH_ANSI_X942_mode,\
                (tmpPubKey_ptr),(tmpPrimeData_ptr),\
                (ClientPrvKey_ptr),(ClientPrvKeySize_ptr),\
                (ClientPub_ptr),(ClientPubSize_ptr))


/*******************************************************************************************/
/*!
@brief This function computes the shared secret key (value) accordng to [ANSI X9.42], 7.5.1:
          SecretKey = ServerPubKey ^ ClientPrvKey mod Prime.
\note <ul id="noteb"><li> All buffer parameters should be in Big-Endian form.</li>
<li>The user must obtain assurance of validity of the public key, using one of methods,
described in [ANSI X9.42] paragraph 7.4.</li>
<li>The actual size of the private key (in bits) must be not less than 2 and not greater than the actual
size of the Prime (modulus in bits).</li></ul>

@return CRYS_OK on success.
@return A non-zero value on failure as defined in crys_dh_error.h or crys_rsa_error.h.
*/
CIMPORT_C CRYSError_t CRYS_DH_GetSecretKey(
                    uint8_t *ClientPrvKey_ptr,                  /*!< [in]  Pointer to the Private key octet string Prv < Prime. */
                    uint16_t ClientPrvKeySize,                  /*!< [in]  The Private key Size (in bytes). */
                    uint8_t *ServerPubKey_ptr,                  /*!< [in]  Pointer to the Server public key octet string. */
                    uint16_t ServerPubKeySize,                  /*!< [in]  The Server Public key Size (in bytes). */
                    uint8_t *Prime_ptr,                         /*!< [in]  Pointer to the Prime octet string. */
                    uint16_t PrimeSize,                         /*!< [in]  The size of the Prime string. */
                    CRYS_DHUserPubKey_t *tmpPubKey_ptr,         /*!< [in]  Pointer to the public key structure. Used for the exponentiation
                                             operation function. Need not be initialized. */
                    CRYS_DHPrimeData_t  *tmpPrimeData_ptr,      /*!< [in]  Pointer to a structure containing internal temp buffers. */
                    uint8_t *SecretKey_ptr,                     /*!< [out] Pointer to the secret key octet string. This buffer should be at
                                            least PrimeSize bytes. */
                    uint16_t *SecretKeySize_ptr                 /*!< [in/out] Pointer to the secret key Buffer Size. This buffer should be at
                                            least of PrimeSize bytes:
                                            <ul><li> Input  - size of the given buffer.</li>
                                            <li> Output - actual size. </li></ul>*/
);


/******************************************************************************************/
/*!
@brief This function extracts the shared secret keying data from the shared secret value. It should be called by using
macros ::CRYS_DH_X942_GetSecretDataAsn1 and ::CRYS_DH_X942_GetSecretDataConcat.

\note
<ul id="noteb"><li> The "other info" argument and its AlgorithmID entry are mandatory only for ASN1 key derivation, and optional for
the other derivation modes. </li>
<li>If used, all entries of the structure should be initialized with relevant data and size, prior to calling this function
(entry size of empty fields must be set to 0).</li>
<li>All buffers arguments are represented in Big-Endian form.</li></ul>

@return CRYS_OK on success.
@return A non-zero value on failure as defined in crys_dh_error.h, crys_rsa_error.h, crys_kdf_error.h or crys_hash_error.h.
*/
 CIMPORT_C CRYSError_t CRYS_DH_X942_GetSecretData(
                    uint8_t                  *ClientPrvKey_ptr,        /*!< [in] Pointer to the Private key octet string. */
                    uint16_t                  ClientPrvKeySize,         /*!< [in] The Private key size (in bytes). */
                    uint8_t                  *ServerPubKey_ptr,         /*!< [in] Pointer to the Server public key octet string. */
            uint16_t                  ServerPubKeySize,         /*!< [in] The Server Public key size (in bytes). */
                    uint8_t                  *Prime_ptr,                /*!< [in] Pointer to the Prime octet string. */
                    uint16_t                  PrimeSize,                /*!< [in] The size of the Prime string. */
                    CRYS_DH_OtherInfo_t        *otherInfo_ptr,          /*!< [in] Pointer to structure containing other data, shared by two entities
                                          sharing the secret keying data.
                                                                                  The Maximal size of each data entry of "other info" is limited - see crys_kdf.h
                                          for the defined value. */
                    CRYS_DH_HASH_OpMode_t       hashMode,               /*!< [in] One of the supported SHA-x HASH modes. The supported modes are according to the supported
                                              HASH modes for the product (and MD5 is not supported). */
                    CRYS_DH_DerivationFunc_Mode DerivFunc_mode,         /*!< [in] The enumerator ID of key derivation function mode. ASN1 or Concatenation
                                          modes are supported. */
                    CRYS_DH_Temp_t             *tmpBuff_ptr,            /*!< [in] A pointer to the DH temp buffer structure. Not initialized. */
                    uint8_t                  *SecretKeyingData_ptr,     /*!< [out] Pointer to the secret key octet string. This buffer should be at least
                                           PrimeSize bytes. */
                    uint16_t                  SecretKeyingDataSize      /*!< [in] The required Secret Keying data size (in bytes). Must be larger than 0,
                                          and smaller than the maximal - CRYS_DH_MAX_SIZE_OF_KEYING_DATA. */
);

/****************************************************************/
/*!
This macro implements the DH [ANSI X9.42] standard. It derives a secret key using the Derivation function based on ASN.1. For a
description of the parameters see ::CRYS_DH_X942_GetSecretData.*/
#define CRYS_DH_X942_GetSecretDataAsn1(ClientPrvKey_ptr,ClientPrvKeySize,ServerPubKey_ptr,ServerPubKeySize,Prime_ptr,PrimeSize,otherInfo_ptr,hashMode,tmpBuff_ptr,SecretKeyingData_ptr,SecretKeyingDataSize)\
    CRYS_DH_X942_GetSecretData((ClientPrvKey_ptr),(ClientPrvKeySize),(ServerPubKey_ptr),(ServerPubKeySize),(Prime_ptr),(PrimeSize),(otherInfo_ptr),(hashMode),(CRYS_DH_ASN1_Der_mode),(tmpBuff_ptr),(SecretKeyingData_ptr),(SecretKeyingDataSize))
/*!
This macro implements the DH [ANSI X9.42] standard. It derives a secret key using the Derivation function based on concatenation of HASHed data.
For a description of the parameters see ::CRYS_DH_X942_GetSecretData.*/
#define CRYS_DH_X942_GetSecretDataConcat(ClientPrvKey_ptr,ClientPrvKeySize,ServerPubKey_ptr,ServerPubKeySize,Prime_ptr,PrimeSize,otherInfo_ptr,hashMode,tmpBuff_ptr,SecretKeyingData_ptr,SecretKeyingDataSize)\
    CRYS_DH_X942_GetSecretData((ClientPrvKey_ptr),(ClientPrvKeySize),(ServerPubKey_ptr),(ServerPubKeySize),(Prime_ptr),(PrimeSize),(otherInfo_ptr),(hashMode),(CRYS_DH_Concat_Der_mode),(tmpBuff_ptr),(SecretKeyingData_ptr),(SecretKeyingDataSize))


/****************************************************************/
/*!
@brief The function computes shared secret data using two pairs of public and private keys:

<ul><li> SecretKey1 = ServerPubKey1^ClientPrvKey1 mod Prime. </li>
<li> SecretKey2 = ServerPubKey2^ClientPrvKey2 mod Prime. </li></ul>
It uses the Derivation function to derive secret keying data from the two secret keys (values).
This function may be called directly, or by using macros ::CRYS_DH_X942_HybridGetSecretDataAsn1 and ::CRYS_DH_X942_HybridGetSecretDataConcat
described above.

\note
<ul id="noteb"><li> The "other info" argument and its AlgorithmID entry are mandatory only for ASN1 key derivation, and optional for the other derivation modes.</li>
If used, all entries of the structure should be initialized with relevant data and size, prior to calling this function
(entry size of empty fields must be set to 0).
<li> All buffers arguments are represented in Big-Endian form. </li></ul>

@return CRYS_OK on success.
@return A non-zero value on failure as defined in crys_dh_error.h, crys_rsa_error.h or crys_hash_error.h.
*/
CIMPORT_C CRYSError_t CRYS_DH_X942_HybridGetSecretData(
                uint8_t            *ClientPrvKey_ptr1,          /*!< [in]  Pointer to the First Private key octet string number. */
                uint16_t            ClientPrvKeySize1,          /*!< [in]  The First Private key Size (in bytes). */
                uint8_t            *ClientPrvKey_ptr2,          /*!< [in]  Pointer to the Second Private key octet string. */
        uint16_t            ClientPrvKeySize2,          /*!< [in]  The Second Private key Size (in bytes). */
                uint8_t            *ServerPubKey_ptr1,          /*!< [in]  Pointer to the First Server public key octet string. */
                uint16_t            ServerPubKeySize1,          /*!< [in]  The First Server Public key Size (in bytes). */
                uint8_t            *ServerPubKey_ptr2,          /*!< [in]  Pointer to the Second Server public key octet string. */
                uint16_t            ServerPubKeySize2,          /*!< [in]  The Second Server Public key Size (in bytes). */
                uint8_t            *Prime_ptr,                  /*!< [in]  Pointer to the Prime octet string. */
                uint16_t            PrimeSize,                  /*!< [in]  The size of the Prime string. */
                CRYS_DH_OtherInfo_t  *otherInfo_ptr,            /*!< [in]  Pointer to structure containing optional other data, shared by two entities
                                 sharing the secret keying data. */
                CRYS_DH_HASH_OpMode_t hashMode,                 /*!< [in]  One of the supported SHA-x HASH modes. The supported modes are according to the supported
                                           HASH modes for the product (and MD5 is not supported). */
                CRYS_DH_DerivationFunc_Mode DerivFunc_mode,     /*!< [in]  The type of function to use to derive the secret key to the key data.
                                 ASN.1 or Concatenation modes are supported. */
                CRYS_DH_HybrTemp_t   *tmpDhHybr_ptr,            /*!< [in]  Pointer to a CRYS_DH_Temp_t structure that contains temp buffers for
                                 internal operations. */
                uint8_t            *SecretKeyingData_ptr,       /*!< [out] Pointer to the secret key octet string. This buffer should be at least
                                 of size PrimeSize bytes. */
                uint16_t            SecretKeyingDataSize        /*!< [in]  The required Secret Keying data size (in bytes). Must be larger than 0,
                                 and smaller than CRYS_DH_MAX_SIZE_OF_KEYING_DATA. */
);


/****************************************************************/
/*!
This macro implements the DH [X9.42] standard deriving a hybrid secret key from two public-private pair of keys using the Derivation function based on ASN.1.
For a description of the parameters see ::CRYS_DH_X942_HybridGetSecretData.*/
#define CRYS_DH_X942_HybridGetSecretDataAsn1(ClientPrvKey_ptr1,ClientPrvKeySize1,ClientPrvKey_ptr2,ClientPrvKeySize2,ServerPubKey_ptr1,ServerPubKeySize1,ServerPubKey_ptr2,ServerPubKeySize2,Prime_ptr,PrimeSize,otherInfo_ptr,hashFunc,tmpDhHybr_ptr,SecretKeyingData_ptr,SecretKeyingDataSize)\
    CRYS_DH_X942_HybridGetSecretData((ClientPrvKey_ptr1),(ClientPrvKeySize1),(ClientPrvKey_ptr2),(ClientPrvKeySize2),(ServerPubKey_ptr1),(ServerPubKeySize1),(ServerPubKey_ptr2),(ServerPubKeySize2),(Prime_ptr),(PrimeSize),(otherInfo_ptr),(hashFunc),CRYS_DH_ASN1_Der_mode,(tmpDhHybr_ptr),(SecretKeyingData_ptr),(SecretKeyingDataSize))

/*!
This macro implements the DH [X9.42] standard, deriving a hybrid secret key from two pairs of public-private keys, using the Derivation
function based on concatenation using SHA-x HASH. For a description of the parameters see ::CRYS_DH_X942_HybridGetSecretData.
*/
#define CRYS_DH_X942_HybridGetSecretDataConcat(ClientPrvKey_ptr1,ClientPrvKeySize1,ClientPrvKey_ptr2,ClientPrvKeySize2,ServerPubKey_ptr1,ServerPubKeySize1,ServerPubKey_ptr2,ServerPubKeySize2,Prime_ptr,PrimeSize,otherInfo_ptr,hashFunc,tmpDhHybr_ptr,SecretKeyingData_ptr,SecretKeyingDataSize)\
    CRYS_DH_X942_HybridGetSecretData((ClientPrvKey_ptr1),(ClientPrvKeySize1),(ClientPrvKey_ptr2),(ClientPrvKeySize2),(ServerPubKey_ptr1),(ServerPubKeySize1),(ServerPubKey_ptr2),(ServerPubKeySize2),(Prime_ptr),(PrimeSize),(otherInfo_ptr),(hashFunc),CRYS_DH_Concat_Der_mode,(tmpDhHybr_ptr),(SecretKeyingData_ptr),(SecretKeyingDataSize))


/******************************************************************************************/
/*!
@brief The function checks the obtained DH public key according to its domain parameters [ANSI X9.42-2001]

\note
Assuming: The DH domain parameters are valid.

@return CRYS_OK on success.
@return A non-zero value on failure as defined in crys_dh_error.h.
*/
CIMPORT_C CRYSError_t CRYS_DH_CheckPubKey(
                    uint8_t              *modP_ptr,            /*!< [in] The pointer to the modulus (prime) P. */
                    uint32_t              modPsizeBytes,        /*!< [in]  The modulus size in bytes. */
                    uint8_t              *orderQ_ptr,           /*!< [in]  The pointer to the prime order Q of generator. */
                    uint32_t              orderQsizeBytes,      /*!< [in]  The size of order of generator in bytes. */
                    uint8_t              *pubKey_ptr,           /*!< [in]  The pointer to the public key to be validated. */
                    uint32_t              pubKeySizeBytes,      /*!< [in]  The public key size in bytes. */
                    CRYS_DH_Temp_t       *tempBuff_ptr         /*!< [in]  The temp buffer for internal calculations. */
);


#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif
