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




#ifndef CRYS_RND_H
#define CRYS_RND_H

#include "crys_error.h"
#include "ssi_aes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief This file contains the CRYS APIs used for random number generation.
The random-number generation module implements referenced standard [SP800-90].
@defgroup crys_rnd CryptoCell Random Generator APIs
@{
@ingroup cryptocell_api
*/

/************************ Defines ******************************/

/*!  Maximal reseed counter - indicates maximal number of
requests allowed between reseeds; according to NIST 800-90
it is (2^48 - 1), our restriction is :  (0xFFFFFFFF - 0xF).*/
#define CRYS_RND_MAX_RESEED_COUNTER     (0xFFFFFFFF - 0xF)

/* Max size for one RNG generation (in bits) =
  max_num_of_bits_per_request = 2^19 (FIPS 800-90 Tab.3) */
/*! Maximal size of generated vector in bits. */
#define CRYS_RND_MAX_GEN_VECTOR_SIZE_BITS       0x7FFFF
/*! Maximal size of generated vector in bytes. */
#define CRYS_RND_MAX_GEN_VECTOR_SIZE_BYTES      0xFFFF

/*! AES output block size in words. */
#define CRYS_RND_AES_BLOCK_SIZE_IN_WORDS  SASI_AES_BLOCK_SIZE_IN_WORDS


/* RND seed and additional input sizes */
/*! Maximal size of random seed in words. */
#define CRYS_RND_SEED_MAX_SIZE_WORDS                  12

#ifndef CRYS_RND_ADDITINAL_INPUT_MAX_SIZE_WORDS
/*! Maximal size of additional input data in words. */
#define CRYS_RND_ADDITINAL_INPUT_MAX_SIZE_WORDS CRYS_RND_SEED_MAX_SIZE_WORDS
#endif

/* allowed sizes of AES Key, in words */
/*! AES key size (128 bits) in words. */
#define CRYS_RND_AES_KEY_128_SIZE_WORDS  4
/*! AES key size (192 bits) in words. */
#define CRYS_RND_AES_KEY_192_SIZE_WORDS  6
/*! AES key size (256 bits) in words. */
#define CRYS_RND_AES_KEY_256_SIZE_WORDS  8

/*   Definitions of temp buffer for RND_DMA version of CRYS_RND   */
/*******************************************************************/
/*   Definitions of temp buffer for DMA version of CRYS_RND   */

/*! Temporary buffer size in words. */
#define CRYS_RND_WORK_BUFFER_SIZE_WORDS 1528

/*! A definition for RAM buffer to be internally used in instantiation (or reseeding) operation. */
typedef struct
{
    /*! Internal buffer*/
    uint32_t crysRndWorkBuff[CRYS_RND_WORK_BUFFER_SIZE_WORDS];
}CRYS_RND_WorkBuff_t;

/*! A definition for entropy estimation data type. */
#define CRYS_RND_EntropyEstimatData_t  CRYS_RND_WorkBuff_t
/*! A definition for entropy estimation buffer. */
#define crysRndEntrIntBuff  crysRndWorkBuff


/* RND source buffer inner (entrpopy) offset       */
/*! An internal offset definition. */
#define CRYS_RND_TRNG_SRC_INNER_OFFSET_WORDS    2
/*! An internal offset definition. */
#define CRYS_RND_TRNG_SRC_INNER_OFFSET_BYTES    (CRYS_RND_TRNG_SRC_INNER_OFFSET_WORDS*sizeof(uint32_t))




/* Size of the expected output buffer used by FIPS KAT */
/*! FIPS Known answer test output size. */
#define CRYS_PRNG_FIPS_KAT_OUT_DATA_SIZE      64

/************************ Enumerators  ****************************/

/*! Definition of random operation modes. */
typedef  enum
{
    /*! SW entropy estimation mode. */
    CRYS_RND_Fast  = 0,
    /*! Full entropy mode. */
    CRYS_RND_Slow  = 1,
    /*! Reserved. */
    CRYS_RND_ModeLast = 0x7FFFFFFF,
} CRYS_RND_mode_t;



/************************ Structs  *****************************/


/* The internal state of DRBG mechanism based on AES CTR and CBC-MAC
   algorithms. It is set as global data defined by the following
   structure  */
/*! RND state structure. Includes internal data that needs to be saved between boots by the user.*/
typedef  struct
{
    /* Seed buffer, consists from concatenated Key||V: max size 12 words */
    /*! Random Seed buffer */
    uint32_t  Seed[CRYS_RND_SEED_MAX_SIZE_WORDS];
    /* Previous value for continuous test */
    /*! Previous random data (used for continuous test). */
    uint32_t  PreviousRandValue[SASI_AES_BLOCK_SIZE_IN_WORDS];

    /* AdditionalInput buffer max size = seed max size words + 4w for padding*/
    /*! Previous additional input buffer. */
    uint32_t  PreviousAdditionalInput[CRYS_RND_ADDITINAL_INPUT_MAX_SIZE_WORDS+5];
    /*! Additional input buffer. */
    uint32_t  AdditionalInput[CRYS_RND_ADDITINAL_INPUT_MAX_SIZE_WORDS+4];
    /*! Additional input size in words. */
    uint32_t  AddInputSizeWords; /* size of additional data set by user, words   */

    /*! Entropy source size in words */
    uint32_t  EntropySourceSizeWords;

    /*! Reseed counter (32 bits active) - indicates number of requests for entropy
    since instantiation or reseeding */
    uint32_t  ReseedCounter;

    /*! Key size: 4 or 8 words according to security strength 128 bits or 256 bits*/
    uint32_t KeySizeWords;

    /* State flag (see definition of StateFlag above), containing bit-fields, defining:
    - b'0: instantiation steps:   0 - not done, 1 - done;
    - 2b'9,8: working or testing mode: 0 - working, 1 - KAT DRBG test, 2 -
      KAT TRNG test;
    b'16: flag defining is Previous random valid or not:
            0 - not valid, 1 - valid */
    /*! State flag used internally in the code.*/
    uint32_t StateFlag;

    /* Trng processing flag - indicates which ROSC lengths are:
    -  allowed (bits 0-3);
    -  total started (bits 8-11);
    -  processed (bits 16-19);
    -  started, but not processed (bits24-27)              */
    /*! TRNG process state used internally in the code */
    uint32_t TrngProcesState;

    /* validation tag */
    /*! Validation tag used internally in the code */
    uint32_t ValidTag;

    /*! Rnd source entropy size in bits */
    uint32_t  EntropySizeBits;

} CRYS_RND_State_t;


/*! The RND Generate vector function pointer type definition.
   The prototype intendent for External and CRYS internal RND functions
   pointers definitions.
   Full description can be found in ::CRYS_RND_GenerateVector function API. */
typedef uint32_t (*SaSiRndGenerateVectWorkFunc_t)(        \
                void  *rndState_ptr, /*context*/   \
                uint16_t          outSizeBytes,   /*in*/      \
                uint8_t          *out_ptr         /*out*/);



/*! Data structure required for internal FIPS verification for PRNG KAT. */
typedef  struct
{
       /*! Internal working buffer. */
       CRYS_RND_WorkBuff_t      rndWorkBuff;
       /*! Output buffer. */
       uint8_t                  rndOutputBuff[CRYS_PRNG_FIPS_KAT_OUT_DATA_SIZE];
} CRYS_PrngFipsKatCtx_t;


/*****************************************************************************/
/**********************        Public Functions      *************************/
/*****************************************************************************/

/*!
@brief This function needs to be called once.
It calls CRYS_RND_Instantiation to initialize the TRNG and the primary RND context.
An initialized RND context is required for calling RND APIs and asymmetric cryptography key generation and signatures.
The primary context returned by this function can be used as a single global context for all RND needs.
Alternatively, other contexts may be initialized and used with a more limited scope (for specific applications or specific threads).

\note The Mutexes, if used, are initialized by this API. Therefore, unlike the other APIs in the library,
this API is not thread-safe.

@param[in/out] rnd_ctx - Pointer to the RND state structure.
@param[in/out] rndWorkBuff_ptr  - Pointer to the RND scratch buffer.
*/
CEXPORT_C CRYSError_t CRYS_RndInit(void* rnd_ctx, /*!< [in/out] Pointer to the RND state buffer,
                                                                allocated by the user. This state must be saved and provided
                                                                as parameter to any API that uses the RND module.*/
                                             CRYS_RND_WorkBuff_t  *rndWorkBuff_ptr /*!< [in] Scratchpad for the RND module's work. */);

/*!
@brief This function initializes the RND context.
It must be called at least once prior to using this context with any API that requires it as a parameter (e.g., other RND APIs, asymmetric
cryptography key generation and signatures).
It is called as part of ARM TrustZone CryptoCell library initialization, which initializes and returns the primary RND context.
This primary context can be used as a single global context for all RND needs.
Alternatively, other contexts may be initialized and used with a more limited scope (for specific applications or specific threads).
The call to this function must be followed by a call to ::CRYS_RND_SetGenerateVectorFunc API to set the generate vector function.
It implements referenced standard [SP800-90] - 10.2.1.3.2 - CTR-DRBG Instantiate algorithm using AES (FIPS-PUB 197) and Derivation Function (DF).
\note Additional data can be mixed with the random seed (personalization data or nonce). If required, this data should be provided by calling ::CRYS_RND_AddAdditionalInput prior to using this API.

@return CRYS_OK on success.
@return A non-zero value from crys_rnd_error.h on failure.
*/
CIMPORT_C CRYSError_t CRYS_RND_Instantiation(
                        void   *rndState_ptr,       /*!< [in/out]  Pointer to the RND state buffer allocated by the user, which is used to
                                           maintain the RND state. This context state must be saved and provided as a
                                           parameter to any API that uses the RND module.
                                           \note the context must be cleared before sent to the function. */
                        CRYS_RND_WorkBuff_t  *rndWorkBuff_ptr       /*!< [in/out] Scratchpad for the RND module's work. */
);


/*!
@brief Clears existing RNG instantiation state.

@return CRYS_OK on success.
@return A non-zero value from crys_rnd_error.h on failure.
*/
CIMPORT_C CRYSError_t CRYS_RND_UnInstantiation(
                        void *rndState_ptr       /*!< [in/out] Pointer to the RND context state buffer. */
);


/*!
@brief This function is used for reseeding the RNG with additional entropy and additional user-provided input.
(additional data should be provided by calling ::CRYS_RND_AddAdditionalInput prior to using this API).
It implements referenced standard [SP800-90] - 10.2.1.4.2 - CTR-DRBG Reseeding algorithm, using AES (FIPS-PUB 197) and Derivation Function (DF).

@return CRYS_OK on success.
@return A non-zero value from crys_rnd_error.h on failure.
*/
CIMPORT_C CRYSError_t CRYS_RND_Reseeding(
                        void   *rndState_ptr,          /*!< [in/out] Pointer to the RND context buffer. */
                        CRYS_RND_WorkBuff_t  *rndWorkBuff_ptr      /*!< [in/out] Scratchpad for the RND module's work. */
);


/****************************************************************************************/
/*!
@brief Generates a random vector according to the algorithm defined in referenced standard [SP800-90] - 10.2.1.5.2 - CTR-DRBG.
The generation algorithm uses AES (FIPS-PUB 197) and Derivation Function (DF).

\note
<ul id="noteb"><li> The RND module must be instantiated prior to invocation of this API.</li>
<li> In the following cases, Reseeding operation must be performed prior to vector generation:</li>
    <ul><li> Prediction resistance is required.</li>
    <li> The function returns CRYS_RND_RESEED_COUNTER_OVERFLOW_ERROR, stating that the Reseed Counter has passed its upper-limit (2^32-2).</li></ul></ul>

@return CRYS_OK on success.
@return A non-zero value from crys_rnd_error.h on failure.
*/
CIMPORT_C CRYSError_t CRYS_RND_GenerateVector(
                            void *rndState_ptr,     /*!< [in/out] Pointer to the RND state structure, which is part of the RND context structure.
                                     Use rndContext->rndState field of the context for this parameter. */
                            uint16_t   outSizeBytes,            /*!< [in]  The size in bytes of the random vector required. The maximal size is 2^16 -1 bytes. */
                            uint8_t   *out_ptr                  /*!< [out] The pointer to output buffer. */
);



/**********************************************************************************************************/
/*!
@brief Generates a random vector with specific limitations by testing candidates (described and used in FIPS 186-4: B.1.2, B.4.2 etc.).

This function draws a random vector, compare it to the range limits, and if within range - return it in rndVect_ptr.
If outside the range, the function continues retrying until a conforming vector is found, or the maximal retries limit is exceeded.
If maxVect_ptr is provided, rndSizeInBits specifies its size, and the output vector must conform to the range [1 < rndVect < maxVect].
If maxVect_ptr is NULL, rndSizeInBits specifies the exact required vector size, and the output vector must be the exact same
bit size (with its most significant bit = 1).
\note
The RND module must be instantiated prior to invocation of this API.

@return CRYS_OK on success.
@return A non-zero value from crys_rnd_error.h on failure.
*/
CIMPORT_C CRYSError_t CRYS_RND_GenerateVectorInRange(
                    void   *rndState_ptr,                 /*!< [in/out] Pointer to the RND state structure. */
                    SaSiRndGenerateVectWorkFunc_t rndGenerateVectFunc,   /*!< [in] Pointer to the random vector generation function. */
                    uint32_t  rndSizeInBits,                /*!< [in]  The size in bits of the random vector required. The allowed size in range  2 <= rndSizeInBits < 2^19-1, bits. */
                    uint8_t  *maxVect_ptr,                  /*!< [in]  Pointer to the vector defining the upper limit for the random vector output, Given as little-endian byte array.
                                                                       If not NULL, its actual size is treated as [(rndSizeInBits+7)/8] bytes and its value must be in range (3, 2^19) */
                    uint8_t  *rndVect_ptr                   /*!< [in/out] Pointer to the output buffer for the random vector. Must be at least [(rndSizeInBits+7)/8] bytes.
                                                                 Treated as little-endian byte array. */
);


/*************************************************************************************/
/*!
@brief Used for adding additional input/personalization data provided by the user,
to be later used by the ::CRYS_RND_Instantiation/::CRYS_RND_Reseeding/::CRYS_RND_GenerateVector functions.

@return CRYS_OK on success.
@return A non-zero value from crys_rnd_error.h on failure.
*/
CIMPORT_C CRYSError_t CRYS_RND_AddAdditionalInput(
                            void *rndState_ptr,         /*!< [in/out] Pointer to the RND context state buffer. */
                            uint8_t *additonalInput_ptr,            /*!< [in]  The Additional Input buffer. */
                            uint16_t additonalInputSize             /*!< [in]  The size of the Additional Input buffer. It must
                                                                               be <= CRYS_RND_ADDITINAL_INPUT_MAX_SIZE_WORDS and a multiple of 4. */
);

/*!
@brief The CRYS_RND_EnterKatMode function sets KAT mode bit into StateFlag of global CRYS_RND_WorkingState structure.

The user must call this function before calling functions performing KAT tests.

\note Total size of entropy and nonce must be not great than 126 words (maximal size of entropy and nonce).

@return CRYS_OK on success.
@return A non-zero value from crys_rnd_error.h on failure.
*/
CIMPORT_C CRYSError_t CRYS_RND_EnterKatMode(
            void   *rndState_ptr,       /*!< [in/out] Pointer to the RND context state buffer. */
            uint8_t            *entrData_ptr,       /*!< [in] Entropy data. */
            uint32_t            entrSize,           /*!< [in] Entropy size in bytes. */
            uint8_t            *nonce_ptr,          /*!< [in] Nonce. */
            uint32_t            nonceSize,          /*!< [in] Entropy size in bytes. */
            CRYS_RND_WorkBuff_t  *workBuff_ptr      /*!< [out] RND working buffer, must be the same buffer, which should be passed into
                            Instantiation/Reseeding functions. */
);

/**********************************************************************************************************/
/*!
@brief The CRYS_RND_DisableKatMode function disables KAT mode bit into StateFlag of global CRYS_RND_State_t structure.

The user must call this function after KAT tests before actual using RND module (Instantiation etc.).

@return CRYS_OK on success.
@return A non-zero value from crys_rnd_error.h on failure.
*/
CIMPORT_C void CRYS_RND_DisableKatMode(
                    void   *rndState_ptr     /*!< [in/out] Pointer to the RND state buffer. */
);


#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif /* #ifndef CRYS_RND_H */

