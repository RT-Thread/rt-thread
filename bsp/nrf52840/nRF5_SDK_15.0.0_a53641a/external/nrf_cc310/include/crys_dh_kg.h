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




#ifndef _CRYS_DH_KG_H
#define _CRYS_DH_KG_H


#include "crys_dh.h"


#ifdef __cplusplus
extern "C"
{
#endif

/*! @file
@brief This module defines the API that supports Diffie-Hellman domain.
@defgroup crys_dh_kg CryptoCell DH Key Generation APIs
@{
@ingroup crys_dh
*/

/************************ Defines ******************************/
/*! Minimal size of DH seed in bytes. */
#define CRYS_DH_SEED_MIN_SIZE_IN_BYTES    CRYS_HASH_SHA1_DIGEST_SIZE_IN_BYTES
/*! Minimal size of DH seed in bits. */
#define CRYS_DH_SEED_MIN_SIZE_IN_BITS     (CRYS_DH_SEED_MIN_SIZE_IN_BYTES * 8)

/************************ Enums ********************************/


/************************ Typedefs  ****************************/

/* temp buffers, used in different DH KG functions */

/*! Temporary data buffer structure for domain parameters generation in DH. */
typedef struct CRYS_DHKGData_t
{
    /* The aligned input and output temp buffers */
    /*! Temporary buffer. */
    uint32_t TempBuff1[CRYS_DH_MAX_MOD_BUFFER_SIZE_IN_WORDS];
    /*! Temporary buffer. */
    uint32_t TempBuff2[CRYS_DH_MAX_MOD_BUFFER_SIZE_IN_WORDS];
    /*! Temporary buffer. */
    uint32_t TempBuff3[CRYS_DH_MAX_MOD_BUFFER_SIZE_IN_WORDS];
    /*! Temporary buffer. */
    uint32_t TempBuff4[CRYS_DH_MAX_MOD_BUFFER_SIZE_IN_WORDS];
    /*! Temporary buffer. */
    uint32_t TempBuff5[CRYS_DH_MAX_MOD_BUFFER_SIZE_IN_WORDS];
    /*! Temporary buffer. */
    uint32_t TempBuff6[CRYS_DH_MAX_MOD_BUFFER_SIZE_IN_WORDS];
    /*! Temporary buffer. */
    CRYS_DH_Temp_t  ExpTemps;
}CRYS_DHKGData_t;

/*! Temporary buffer structure . */
typedef struct CRYS_DHKG_CheckTemp_t
{
    /*! Temporary buffer. */
    uint32_t         CheckTempBuff[3*CRYS_DH_MAX_MOD_BUFFER_SIZE_IN_WORDS];
    /*! Temporary buffer. */
    CRYS_DHKGData_t    DhKgBuff;
}CRYS_DHKG_CheckTemp_t;

/*! DH Domain generation values definitions */
/*! Minimal modulus size for X942 - 1024.*/
#define DH_X942_PRIME_MOD_MIN_VAL    1024
/*! Maximal modulus size for X942 - 2048.*/
#define DH_X942_PRIME_MOD_MAX_VAL    2048
/*! PGeneration counter for X942 - 4096.*/
#define DH_X942_PGEN_COUNTER_CONST   4096
/*! HASH size in bits for X942 - 160.*/
#define DH_X942_HASH_SIZE_BITS        160
/*! Maximal allowed ratio between modulus and generator order sizes (by implementation) */
#define DH_MAX_RATIO_MODULO_TO_ORDER    4

/************************ Structs  ******************************/

/************************ Public Variables **********************/

/************************ Public Functions **********************/


/******************************************************************************************/
/*!
@brief This function generates DH domain parameters in Galois prime field according to standard [ANS X9.42].
It receives the required sizes (in bits) of the modulus, the generator's order, and the seed, and then generates
the prime modulus and the generator according to given sizes.
If generateSeed argument is set to 1, the function generates and outputs the random seed. Otherwise (if set to 0),
the seed has to be passed as an input argument. According to implementation the seed should be not greate, than (2^seedSizeBits - 2^32).
The seed and some additional parameters, generated by the function (factorJ, pgenCounter), are used for checking
that all domain parameters are generated according to the standard and not forged.
\note All buffer parameters should be in Big-Endian form.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_dh_error.h, crys_rnd_error.h or crys_hash_error.h.
*/
CIMPORT_C CRYSError_t CRYS_DH_CreateDomainParams(
                void   *rndState_ptr,                 /*!< [in/out] Pointer to the RND state structure. */
                SaSiRndGenerateVectWorkFunc_t rndGenerateVectFunc,   /*!< [in] Pointer to a random vector generation function. */
                uint32_t          modPsizeBits,                 /*!< [in]  Size of the modulus (Prime) in bits equal 256*n, where n >= 4. FIPS 186-4
                                                                     defines sizes 1024 and 2048 bit. */
                uint32_t          orderQsizeBits,               /*!< [in]  Size of the Generator's order in bits. FIPS 186-4 defines orderQSizeBits = 160
                                                                     for modulus 1024 bit and 224 or 256 bit for modPSizeBits = 2048. We not recommend
                                                                     sizes > 256 and returns an error if orderQSizeBits > modPSizeBits/4 */
                uint32_t          seedSizeBits,                 /*!< [in]  Seed size in bits. Requirements: modPSizeBits >= seedSizeBits >= orderQSizeBits
                                     (the first is required by our implementation). */
                uint8_t          *modP_ptr,                     /*!< [out] Pointer to the modulus (prime) buffer. The size of the buffer for output
                                     generated value must be no less than given modulus size. */
                uint8_t          *orderQ_ptr,                   /*!< [out] Pointer to the order Q of generator. The size of the buffer for output generated
                                     value must be no less than the given order size. */
                uint8_t          *generatorG_ptr,               /*!< [out] Pointer to the generator of multiplicative subgroup in GF(P).
                                     If the user does not need this output, then both the pointer and the buffer size
                                     must be set to 0. */
                uint32_t         *generGsizeBytes_ptr,          /*!< [in/out] Pointer to the one word buffer for outputting the generator's size.
                                     The passed size (if needed) must be not less than modulus size and the function
                                     returns the actual size of the generator. */
                uint8_t          *factorJ_ptr,                  /*!< [out] Pointer to the buffer for integer factor J. If NULL, the function does not output
                                     this parameter (in this case JsizeBytes_ptr also must be set to NULL, else the function
                                                                     returns an error). */
                uint32_t         *JsizeBytes_ptr,               /*!< [in/out] Pointer to the size of integer factor J. If NULL, the function does not output
                                     this parameter. */
                uint8_t          *seedS_ptr,                    /*!< [in/out] Random seed used for prime generation. The size of the buffer must be
                                                                     at least the seed size. */
                int8_t            generateSeed,                 /*!< [in]  Flag, defining whether the seed should be generated randomly by the function
                                     (1) or is passed by the user (0). */
                uint32_t         *pgenCounter_ptr,              /*!< [out] Pointer to counter of tries to generate the primes. If NULL, the function does not
                                         output this parameter. */
                CRYS_DHKGData_t    *DHKGbuff_ptr                /*!< [out] The temp buffer of defined structure for internal calculations. */
);


/******************************************************************************************/
/*!
@brief This function receives DH domain parameters, seed and prime generation counter and then verifies
that the domain was created according to the standard [ANS X9.42].
According to implementation, the value of the user passed seed should be not
greate, than (2^seedSizeBits - 2^32), otherwise an error is returned.
\note All buffer parameters should be in Big-Endian form. For more detailed
description of the parameters see ::CRYS_DH_CreateDomainParams.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_dh_error.h, crys_rnd_error.h or crys_hash_error.h.
*/
CIMPORT_C CRYSError_t CRYS_DH_CheckDomainParams(
                void   *rndState_ptr,                /*!< [in/out] Pointer to the RND state. */
                SaSiRndGenerateVectWorkFunc_t rndGenerateVectFunc,   /*!< [in/out] Pointer to the RND Generate vector function pointer. */
                uint8_t               *modP_ptr,                /*!< [in] Pointer to the modulus (Prime). */
                uint32_t               modPsizeBytes,           /*!< [in] Size of the modulus (Prime) in bytes. */
                uint8_t               *orderQ_ptr,              /*!< [in] Pointer to the order Q of generator. The size of the buffer for output
                                          generated value must be no less than the order size. */
                uint32_t               orderQsizeBytes,         /*!< [in] Size of the Generator's order in bytes. */
                uint8_t               *generatorG_ptr,          /*!< [in] Pointer to the generator of the multiplicative subgroup in GF(P). */
                uint32_t               generatorSizeBytes,      /*!< [in] Size of the generator in bytes. */
                uint8_t               *seedS_ptr,               /*!< [in] Random seed used for prime generation.  */
                uint32_t               seedSizeBits,            /*!< [in] Seed size in bits.  */
                uint32_t               pgenCounter,             /*!< [in] Counter of prime generation attempts. */
                CRYS_DHKG_CheckTemp_t *checkTempBuff_ptr        /*!< [in] Temporary buffer for internal calculations. */

);


#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif
