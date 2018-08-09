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
@brief This file contains all of the enums and definitions that are used for the
         CRYS CHACHA APIs, as well as the APIs themselves.
@defgroup crys_chacha CryptoCell CHACHA APIs
@{
@ingroup cryptocell_api
*/
#ifndef CRYS_CHACHA_H
#define CRYS_CHACHA_H


#include "ssi_pal_types.h"
#include "crys_error.h"


#ifdef __cplusplus
extern "C"
{
#endif

/************************ Defines ******************************/
/*! CHACHA user's context size in words. */
#define CRYS_CHACHA_USER_CTX_SIZE_IN_WORDS 17

/*! CHACHA block size in words. */
#define CRYS_CHACHA_BLOCK_SIZE_IN_WORDS 16
/*! CHACHA block size in bytes. */
#define CRYS_CHACHA_BLOCK_SIZE_IN_BYTES  (CRYS_CHACHA_BLOCK_SIZE_IN_WORDS * sizeof(uint32_t))

/*! Nonce buffer max size in words. */
#define CRYS_CHACHA_NONCE_MAX_SIZE_IN_WORDS   3
/*! Nonce buffer max size in bytes. */
#define CRYS_CHACHA_NONCE_MAX_SIZE_IN_BYTES  (CRYS_CHACHA_NONCE_MAX_SIZE_IN_WORDS * sizeof(uint32_t))

/*! CHACHA KEY maximal size in words. */
#define CRYS_CHACHA_KEY_MAX_SIZE_IN_WORDS 8
/*! CHACHA KEY maximal size in bytes. */
#define CRYS_CHACHA_KEY_MAX_SIZE_IN_BYTES (CRYS_CHACHA_KEY_MAX_SIZE_IN_WORDS * sizeof(uint32_t))

/************************ Enums ********************************/

/*! Enum defining the CHACHA Encrypt or Decrypt operation mode. */
typedef enum {
    /*! CHACHA encrypt mode. */
    CRYS_CHACHA_Encrypt = 0,
    /*! CHACHA decrypt mode. */
    CRYS_CHACHA_Decrypt = 1,
    /*! CHACHA maximal number of operations (encrypt/decrypt). */
    CRYS_CHACHA_EncryptNumOfOptions,

    /*! Reserved. */
    CRYS_CHACHA_EncryptModeLast = 0x7FFFFFFF,

}CRYS_CHACHA_EncryptMode_t;

/*! Enum defining the CHACHA Nonce size in bits. */
typedef enum {
    /*! 64 bit Nonce size. */
        CRYS_CHACHA_Nonce64BitSize = 0,
    /*! 96 bit Nonce size. */
        CRYS_CHACHA_Nonce96BitSize = 1,
    /*! CHACHA maximal number of nonce sizes. */
        CRYS_CHACHA_NonceSizeNumOfOptions,
    /*! Reserved. */
        CRYS_CHACHA_NonceSizeLast = 0x7FFFFFFF,

}CRYS_CHACHA_NonceSize_t;

/************************ Typedefs  ****************************/

/*! Defines the Nonce buffer 12 bytes array. */
typedef uint8_t CRYS_CHACHA_Nonce_t[CRYS_CHACHA_NONCE_MAX_SIZE_IN_BYTES];

/*! Defines the CHACHA key buffer. */
typedef uint8_t CRYS_CHACHA_Key_t[CRYS_CHACHA_KEY_MAX_SIZE_IN_BYTES];


/************************ context Structs  ******************************/

/*! The user's context prototype - the argument type that is passed by the user
   to the CHACHA API. The context saves the state of the operation and must be saved by the user
   till the end of the APIs flow (for example till ::CRYS_CHACHA_Free is called). */
typedef struct CRYS_CHACHAUserContext_t {
    /* Allocated buffer must be double the size of actual context
     * + 1 word for offset management */
    /*! Context buffer for internal use */
    uint32_t buff[CRYS_CHACHA_USER_CTX_SIZE_IN_WORDS];
}CRYS_CHACHAUserContext_t;

/************************ Public Variables **********************/


/************************ Public Functions **********************/

/****************************************************************************************************/

/*!
@brief This function is used to initialize the context for CHACHA operations.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_chacha_error.h.
*/
CIMPORT_C CRYSError_t  CRYS_CHACHA_Init(
                        CRYS_CHACHAUserContext_t    *pContextID,        /*!< [in]  Pointer to the CHACHA context buffer that is allocated by the user
                                                                                   and is used for the CHACHA operation. */
                        CRYS_CHACHA_Nonce_t          pNonce,            /*!< [in]  A buffer containing an nonce. */
                        CRYS_CHACHA_NonceSize_t      nonceSize,         /*!< [in]  Enumerator defining the nonce size (only 64 and 96 bit are valid). */
                        CRYS_CHACHA_Key_t            pKey,               /*!< [in]  A pointer to the user's key buffer. */
                        uint32_t                     initialCounter,     /*!< [in]  An initial counter. */
                        CRYS_CHACHA_EncryptMode_t    EncryptDecryptFlag  /*!< [in]  A flag specifying whether the CHACHA should perform an Encrypt operation
                                                                                   or a Decrypt operation. */
);


/*!
@brief This function is used to process aligned blocks of CHACHA.
The data in size should be a multiple of chacha block size.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_chacha_error.h.
*/
CIMPORT_C CRYSError_t  CRYS_CHACHA_Block(
                        CRYS_CHACHAUserContext_t    *pContextID,        /*!< [in] Pointer to the context buffer. */
                        uint8_t                     *pDataIn,           /*!< [in]  A pointer to the buffer of the input data to the CHACHA.
                                                                                   The pointer does not need to be aligned. must not be null. */
                        uint32_t                    dataInSize,         /*!< [in]  The size of the input data.
                                                                                   Must be a multiple of ::CRYS_CHACHA_BLOCK_SIZE_IN_BYTES bytes and must not be 0. */
                        uint8_t                     *pDataOut           /*!< [out] A pointer to the buffer of the output data from the CHACHA.
                                                                                   The pointer does not need to be aligned. must not be null. */
);


/*!
@brief This function is used to process the remaining data of CHACHA.
The data in size should be smaller than chacha block size.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_chacha_error.h.
*/
CIMPORT_C CRYSError_t  CRYS_CHACHA_Finish(
                        CRYS_CHACHAUserContext_t    *pContextID,        /*!< [in]  Pointer to the context buffer. */
                        uint8_t                     *pDataIn,           /*!< [in]  A pointer to the buffer of the input data to the CHACHA.
                                                                                   The pointer does not need to be aligned. If dataInSize = 0, input buffer is not required. */
                        uint32_t                    dataInSize,         /*!< [in]  The size of the input data.
                                                                                   zero and non multiple of ::CRYS_CHACHA_BLOCK_SIZE_IN_BYTES are valid. */
                        uint8_t                     *pDataOut           /*!< [out] A pointer to the buffer of the output data from the CHACHA.
                                                                                   The pointer does not need to be aligned. If dataInSize = 0, output buffer is not required. */
);


/*!
@brief This function is used to free the context of CHACHA operations.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_chacha_error.h.
*/
CIMPORT_C CRYSError_t  CRYS_CHACHA_Free(
                        CRYS_CHACHAUserContext_t *pContextID    /*!< [in] Pointer to the context buffer. */
);


/*!
@brief This function is used to perform the CHACHA operation in one integrated process.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_chacha_error.h.
*/
CIMPORT_C CRYSError_t  CRYS_CHACHA(
                            CRYS_CHACHA_Nonce_t           pNonce,           /*!< [in]  A buffer containing an nonce. */
                            CRYS_CHACHA_NonceSize_t       nonceSize,               /*!< [in]  Enumerator defining the nonce size (only 64 and 96 bit are valid). */
                            CRYS_CHACHA_Key_t             pKey,                 /*!< [in]  A pointer to the user's key buffer. */
                            uint32_t                      initialCounter,       /*!< [in]  An initial counter. */
                            CRYS_CHACHA_EncryptMode_t     encryptDecryptFlag,   /*!< [in]  A flag specifying whether the CHACHA should perform an Encrypt operation
                                                                                                or a Decrypt operation. */
                            uint8_t                      *pDataIn,              /*!< [in]  A pointer to the buffer of the input data to the CHACHA.
                                                                                           The pointer does not need to be aligned. must not be null. */
                            uint32_t                      dataInSize,           /*!< [in]  The size of the input data. must not be 0. */
                            uint8_t                      *pDataOut              /*!< [out] A pointer to the buffer of the output data from the CHACHA.
                                                                                           The pointer does not need to be aligned. must not be null. */
);


/***********************************************************************************/

#ifdef __cplusplus
}
#endif

/**
@}
 */

#endif /* #ifndef CRYS_CHACHA_H */





