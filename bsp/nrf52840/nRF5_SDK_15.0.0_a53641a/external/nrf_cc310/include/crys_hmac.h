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
that are used for the CRYS HMAC APIs, as well as the APIs themselves.
@defgroup crys_hmac CryptoCell HMAC APIs
@{
@ingroup cryptocell_api


HMAC is a wrapping algorithm that uses a HASH function (one of the supported HASH algorithms, as specified in the HASH chapter) and a key,
to generate a unique authentication code over the input data.
HMAC calculation can be performed in either of the following two modes of operation:
<ul><li> Integrated operation - Processes all data in a single function call. This flow is applicable when all data is available prior to
the cryptographic operation.</li>
<li> Block operation - Processes a subset of the data buffers, and is called multiple times in a sequence. This flow is applicable when
the next data buffer becomes available only during/after processing of the current data buffer.</li></ul>

The following is a typical HMAC Block operation flow:
<ol><li> ::CRYS_HMAC_Init: This function initializes the HMAC machine on the CRYS level by setting the context pointer that is
    used on the entire HMAC operation.</li>
<li> ::CRYS_HMAC_Update: This function runs an HMAC operation on a block of data allocated by the user. This function may be called as
     many times as required.</li>
<li> ::CRYS_HMAC_Finish: This function ends the HMAC operation. It returns the digest result and clears the context.</li></ol>
*/

#ifndef CRYS_HMAC_H
#define CRYS_HMAC_H


#include "ssi_pal_types.h"
#include "crys_error.h"

#include "crys_hash.h"
#include "crys_hmac_defs.h"

#ifdef __cplusplus
extern "C"
{
#endif


/************************ Defines ******************************/

/*! HMAC key size after padding for MD5, SHA1, SHA256. */
#define CRYS_HMAC_KEY_SIZE_IN_BYTES 64

/*! HMAC key size after padding for SHA384, SHA512 */
#define CRYS_HMAC_SHA2_1024BIT_KEY_SIZE_IN_BYTES 128

/************************ Enums ********************************/

/************************ Typedefs  ****************************/

/*********************** Structures ****************************/


/*! User's context prototype - the argument type that is passed by the user
   to the HMAC APIs. The context saves the state of the operation and must be saved by the user
   till the end of the APIs flow */
typedef struct CRYS_HMACUserContext_t {
    /*! Context buffer for internal use */
    uint32_t buff[CRYS_HMAC_USER_CTX_SIZE_IN_WORDS];

}CRYS_HMACUserContext_t;

/************************ Structs  ******************************/


/************************ Public Variables **********************/


/************************ Public Functions **********************/

/*!
@brief This function initializes the HMAC machine.

It allocates and initializes the HMAC Context. It initiates a HASH session and processes a HASH update on the Key XOR ipad,
then stores it in the context

@return CRYS_OK on success.
@return A non-zero value from crys_hmac_error.h or crys_hash_error.h on failure.
*/
CIMPORT_C CRYSError_t CRYS_HMAC_Init(
                        CRYS_HMACUserContext_t     *ContextID_ptr,         /*!< [in]  Pointer to the HMAC context buffer allocated by the user, which is used
                                              for the HMAC machine operation. */
                        CRYS_HASH_OperationMode_t  OperationMode,          /*!< [in]  One of the supported HASH modes, as defined in CRYS_HASH_OperationMode_t. */
                        uint8_t                    *key_ptr,               /*!< [in]  The pointer to the user's key buffer. */
                        uint16_t                    keySize                /*!< [in]  The key size in bytes. If the key size is bigger than the HASH block, the key will be hashed.
                                         The limitations on the key size are the same as the limitations on MAX hash size. */
);


/*!
@brief This function processes a block of data to be HASHed.

It receives a handle to the HMAC Context, and updates the HASH value with the new data.

@return CRYS_OK on success.
@return A non-zero value from crys_hmac_error.h or crys_hash_error.h on failure.
*/

CIMPORT_C CRYSError_t CRYS_HMAC_Update(
                        CRYS_HMACUserContext_t  *ContextID_ptr,         /*!< [in]  Pointer to the HMAC context buffer allocated by the user
                                           that is used for the HMAC machine operation. */
                        uint8_t                 *DataIn_ptr,            /*!< [in]  Pointer to the input data to be HASHed.
                                                                                   The size of the scatter/gather list representing the data buffer is limited to
                                           128 entries, and the size of each entry is limited to 64KB
                                           (fragments larger than 64KB are broken into fragments <= 64KB). */
                        size_t                 DataInSize             /*!< [in]  Byte size of the input data. Must be > 0.
                                                                                   If not a multiple of the HASH block size (64 for SHA-1 and SHA-224/256,
                                           128 for SHA-384/512), no further calls to ::CRYS_HMAC_Update are allowed in
                                           this context, and only ::CRYS_HMAC_Finish can be called to complete the
                                           computation. */
);


/*!
@brief This function finalizes the HMAC processing of a data block.

It receives a handle to the HMAC context that was previously initialized by ::CRYS_HMAC_Init, or by ::CRYS_HMAC_Update.
It completes the HASH calculation on the ipad and text, and then executes a new HASH operation with the key XOR opad and the previous
HASH operation result.

@return CRYS_OK on success.
@return A non-zero value from crys_hmac_error.h or crys_hash_error.h on failure.
*/

CIMPORT_C CRYSError_t CRYS_HMAC_Finish(
                        CRYS_HMACUserContext_t  *ContextID_ptr,         /*!< [in]  Pointer to the HMAC context buffer allocated by the user, which is used
                                           for the HMAC machine operation. */
                        CRYS_HASH_Result_t       HmacResultBuff         /*!< [out] Pointer to the word-aligned 64 byte buffer. The actual size of the
                                           HASH result depends on CRYS_HASH_OperationMode_t. */
);


/*!
@brief This function is a service function that frees the context if the operation has failed.

The function executes the following major steps:
<ol><li> Checks the validity of all of the inputs of the function. </li>
<li> Clears the user's context.</li>
<li> Exits the handler with the OK code.</li></ol>

@return CRYS_OK on success.
@return a non-zero value from crys_hmac_error.h on failure.
*/

CIMPORT_C CRYSError_t  CRYS_HMAC_Free(
                        CRYS_HMACUserContext_t  *ContextID_ptr         /*!< [in]  Pointer to the HMAC context buffer allocated by the user, which is used for
                                          the HMAC machine operation. */
);


/*!
@brief This function processes a single buffer of data, and returns the data buffer's message digest.

@return CRYS_OK on success.
@return A non-zero value from crys_hmac_error.h or crys_hash_error.h on failure.
*/
CIMPORT_C CRYSError_t CRYS_HMAC  (
                        CRYS_HASH_OperationMode_t  OperationMode,       /*!< [in]  One of the supported HASH modes, as defined in CRYS_HASH_OperationMode_t. */
                        uint8_t                    *key_ptr,            /*!< [in]  The pointer to the user's key buffer. */
                        uint16_t                    keySize,            /*!< [in]  The key size in bytes. If the key size is bigger than the HASH block, the key will be hashed.
                                         The limitations on the key size are the same as the limitations on MAX hash size.*/
                        uint8_t                    *DataIn_ptr,         /*!< [in]  Pointer to the input data to be HASHed.
                                                                                   The size of the scatter/gather list representing the data buffer is limited to 128
                                           entries, and the size of each entry is limited to 64KB (fragments larger than
                                           64KB are broken into fragments <= 64KB). */
                        size_t                    DataSize,           /*!< [in]  The size of the data to be hashed (in bytes). */
                        CRYS_HASH_Result_t          HmacResultBuff      /*!< [out] Pointer to the word-aligned 64 byte buffer. The actual size of the
                                           HMAC result depends on CRYS_HASH_OperationMode_t. */
);
#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif
