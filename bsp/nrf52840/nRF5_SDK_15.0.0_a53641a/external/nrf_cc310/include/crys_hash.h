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


/*!
@file
@brief This file contains all of the enums and definitions
that are used for the CRYS HASH APIs, as well as the APIs themselves.
@defgroup crys_hash CryptoCell HASH APIs
@{
@ingroup cryptocell_api


This product supports the following HASH algorithms (or modes, according to product):
<ul><li> CRYS_HASH_MD5 (producing 16 byte output).</li>
<li> CRYS_HASH_SHA1 (producing 20 byte output).</li>
<li> CRYS_HASH_SHA224 (producing 28 byte output).</li>
<li> CRYS_HASH_SHA256 (producing 32 byte output).</li>
<li> CRYS_HASH_SHA384 (producing 48 byte output).</li>
<li> CRYS_HASH_SHA512 (producing 64 byte output).</li></ul>

HASH calculation can be performed in either of the following two modes of operation:
<ul><li> Integrated operation - Processes all data in a single function call. This flow is applicable when all data is available prior to the
     cryptographic operation.</li>
<li> Block operation - Processes a subset of the data buffers, and is called multiple times in a sequence. This flow is applicable when the
     next data buffer becomes available only during/after processing of the current data buffer.</li></ul>

The following is a typical HASH Block operation flow:
<ol><li> ::CRYS_HASH_Init - this function initializes the HASH machine on the CRYS level by setting the context pointer that is used on the entire
     HASH operation.</li>
<li> ::CRYS_HASH_Update - this function runs a HASH operation on a block of data allocated by the user. This function may be called as many times
     as required.</li>
<li> ::CRYS_HASH_Finish - this function ends the HASH operation. It returns the digest result and clears the context.</li></ol>
*/

#ifndef CRYS_HASH_H
#define CRYS_HASH_H


#include "ssi_pal_types.h"
#include "crys_error.h"
#include "crys_hash_defs.h"


#ifdef __cplusplus
extern "C"
{
#endif


/************************ Defines ******************************/
/* The hash result in words
#define CRYS_HASH_RESULT_SIZE_IN_WORDS 5*/
/*! The maximal hash result is 512 bits for SHA512. */
#define CRYS_HASH_RESULT_SIZE_IN_WORDS  16

/*! MD5 digest result size in bytes. */
#define CRYS_HASH_MD5_DIGEST_SIZE_IN_BYTES 16

/*! MD5 digest result size in words. */
#define CRYS_HASH_MD5_DIGEST_SIZE_IN_WORDS 4

/*! SHA-1 digest result size in bytes. */
#define CRYS_HASH_SHA1_DIGEST_SIZE_IN_BYTES 20

/*! SHA-1 digest result size in words. */
#define CRYS_HASH_SHA1_DIGEST_SIZE_IN_WORDS 5

/*! SHA-256 digest result size in words. */
#define CRYS_HASH_SHA224_DIGEST_SIZE_IN_WORDS 7

/*! SHA-256 digest result size in words. */
#define CRYS_HASH_SHA256_DIGEST_SIZE_IN_WORDS 8

/*! SHA-384 digest result size in words. */
#define CRYS_HASH_SHA384_DIGEST_SIZE_IN_WORDS 12

/*! SHA-512 digest result size in words. */
#define CRYS_HASH_SHA512_DIGEST_SIZE_IN_WORDS 16

/*! SHA-256 digest result size in bytes */
#define CRYS_HASH_SHA224_DIGEST_SIZE_IN_BYTES 28

/*! SHA-256 digest result size in bytes */
#define CRYS_HASH_SHA256_DIGEST_SIZE_IN_BYTES 32

/*! SHA-384 digest result size in bytes */
#define CRYS_HASH_SHA384_DIGEST_SIZE_IN_BYTES 48

/*! SHA-512 digest result size in bytes */
#define CRYS_HASH_SHA512_DIGEST_SIZE_IN_BYTES 64

/*! SHA1 hash block size in words */
#define CRYS_HASH_BLOCK_SIZE_IN_WORDS 16

/*! SHA1 hash block size in bytes */
#define CRYS_HASH_BLOCK_SIZE_IN_BYTES 64

/*! SHA2 hash block size in words */
#define CRYS_HASH_SHA512_BLOCK_SIZE_IN_WORDS    32

/*! SHA2 hash block size in bytes */
#define CRYS_HASH_SHA512_BLOCK_SIZE_IN_BYTES    128

/*! Maximal data size for update operation. */
#define CRYS_HASH_UPDATE_DATA_MAX_SIZE_IN_BYTES (1 << 29)


/************************ Enums ********************************/

/*!
HASH operation mode
*/
typedef enum {
    CRYS_HASH_SHA1_mode          = 0,    /*!< SHA1. */
    CRYS_HASH_SHA224_mode        = 1,    /*!< SHA224. */
    CRYS_HASH_SHA256_mode        = 2,    /*!< SHA256. */
    CRYS_HASH_SHA384_mode        = 3,    /*!< SHA384. */
    CRYS_HASH_SHA512_mode        = 4,    /*!< SHA512. */
    CRYS_HASH_MD5_mode           = 5,    /*!< MD5. */
    /*! Number of hash modes. */
    CRYS_HASH_NumOfModes,
    /*! Reserved. */
    CRYS_HASH_OperationModeLast= 0x7FFFFFFF,

}CRYS_HASH_OperationMode_t;

/************************ Typedefs  *****************************/

/*! HASH result buffer. */
typedef uint32_t CRYS_HASH_Result_t[CRYS_HASH_RESULT_SIZE_IN_WORDS];

/************************ Structs  ******************************/
/*! The user's context prototype - the argument type that is passed by the user
   to the HASH APIs. The context saves the state of the operation and must be saved by the user
   till the end of the APIs flow. */
typedef struct CRYS_HASHUserContext_t {
    /*! Internal buffer */
    uint32_t buff[CRYS_HASH_USER_CTX_SIZE_IN_WORDS];
}CRYS_HASHUserContext_t;

/************************ Public Variables **********************/

/************************ Public Functions **********************/


/************************************************************************************************/
/*!
@brief This function initializes the HASH machine and the HASH Context.

It receives as input a pointer to store the context handle to the HASH Context,
and initializes the HASH Context with the cryptographic attributes that are needed for the HASH block operation (initializes H's value for the HASH algorithm).

@return CRYS_OK on success.
@return A non-zero value from crys_hash_error.h on failure.
*/
CIMPORT_C CRYSError_t CRYS_HASH_Init(
                        CRYS_HASHUserContext_t     *ContextID_ptr,         /*!< [in]  Pointer to the HASH context buffer allocated by the user that is used
                                        for the HASH machine operation. */
                        CRYS_HASH_OperationMode_t  OperationMode           /*!< [in]  One of the supported HASH modes, as defined in CRYS_HASH_OperationMode_t. */
);

/************************************************************************************************/
/*!
@brief This function processes a block of data to be HASHed.

It updates a HASH Context that was previously initialized by CRYS_HASH_Init or updated by a previous call to CRYS_HASH_Update.

@return CRYS_OK on success.
@return A non-zero value from crys_hash_error.h on failure.
*/

CIMPORT_C CRYSError_t CRYS_HASH_Update(
                        CRYS_HASHUserContext_t  *ContextID_ptr,         /*!< [in]  Pointer to the HASH context buffer allocated by the user, which is used for the
                                           HASH machine operation. */
                        uint8_t                 *DataIn_ptr,            /*!< [in]  Pointer to the input data to be HASHed.
                                                                                   it is a one contiguous memory block. */
                        size_t                 DataInSize             /*!< [in]  Byte size of the input data. Must be > 0.
                                                                                    If not a multiple of the HASH block size (64 for MD5, SHA-1 and SHA-224/256,
                                            128 for SHA-384/512), no further calls
                                                                                    to CRYS_HASH_Update are allowed in this context, and only CRYS_HASH_Finish
                                            can be called to complete the computation. */
);

/************************************************************************************************/
/*!
@brief This function finalizes the hashing process of data block.

It receives a handle to the HASH Context, which was previously initialized by CRYS_HASH_Init or by CRYS_HASH_Update.
It "adds" a header to the data block according to the relevant HASH standard, and computes the final message digest.

@return CRYS_OK on success.
@return A non-zero value from crys_hash_error.h on failure.
*/

CIMPORT_C CRYSError_t CRYS_HASH_Finish(
                        CRYS_HASHUserContext_t  *ContextID_ptr,         /*!< [in]  Pointer to the HASH context buffer allocated by the user that is used for
                                           the HASH machine operation. */
                        CRYS_HASH_Result_t       HashResultBuff         /*!< [in]  Pointer to the word-aligned 64 byte buffer. The actual size of the HASH
                                           result depends on CRYS_HASH_OperationMode_t. */
);


/************************************************************************************************/
/*!
@brief This function is a utility function that frees the context if the operation has failed.

The function executes the following major steps:
<ol><li> Checks the validity of all of the inputs of the function. </li>
<li> Clears the user's context.</li>
<li> Exits the handler with the OK code.</li></ol>

@return CRYS_OK on success.
@return A non-zero value from crys_hash_error.h on failure.
*/

CIMPORT_C CRYSError_t  CRYS_HASH_Free(
                        CRYS_HASHUserContext_t  *ContextID_ptr         /*!< [in]  Pointer to the HASH context buffer allocated by the user that is used for
                                         the HASH machine operation. */
);


/************************************************************************************************/
/*!
@brief This function processes a single buffer of data.

The function allocates an internal HASH Context, and initializes it with the cryptographic attributes
that are needed for the HASH block operation (initialize H's value for the HASH algorithm).
Then it processes the data block, calculating the HASH. Finally, it returns the data buffer's message digest.

@return CRYS_OK on success.
@return A non-zero value from crys_hash_error.h on failure.
 */

CIMPORT_C CRYSError_t CRYS_HASH  (
                        CRYS_HASH_OperationMode_t  OperationMode,       /*!< [in]  One of the supported HASH modes, as defined in CRYS_HASH_OperationMode_t. */
                        uint8_t                   *DataIn_ptr,          /*!< [in]  Pointer to the input data to be HASHed.
                                                                                   The size of the scatter/gather list representing the data buffer is limited
                                           to 128 entries, and the size of each entry is limited to 64KB
                                           (fragments larger than 64KB are broken into fragments <= 64KB). */
                        size_t                   DataSize,            /*!< [in]  The size of the data to be hashed in bytes. */
                        CRYS_HASH_Result_t         HashResultBuff       /*!< [out] Pointer to a word-aligned 64 byte buffer. The actual size of the HASH
                                           result depends on CRYS_HASH_OperationMode_t. */
);



#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif
