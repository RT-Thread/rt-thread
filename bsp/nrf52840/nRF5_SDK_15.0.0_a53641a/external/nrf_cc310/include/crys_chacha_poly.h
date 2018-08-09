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
         CRYS CHACHA-POLY APIs, as well as the APIs themselves.
@defgroup crys_chacha_poly CryptoCell CHACHA-POLY APIs
@{
@ingroup cryptocell_api
*/
#ifndef CRYS_CHACHA_POLY_H
#define CRYS_CHACHA_POLY_H


#include "ssi_pal_types.h"
#include "crys_error.h"
#include "crys_chacha.h"
#include "crys_poly.h"


#ifdef __cplusplus
extern "C"
{
#endif


/*!
@brief This function is used to perform the CHACHA-POLY encryption and authentication operation.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_chacha_poly_error.h.
*/
CIMPORT_C CRYSError_t  CRYS_CHACHA_POLY(
                CRYS_CHACHA_Nonce_t      pNonce,            /*!< [in]  A pointer to a buffer containing the nonce value. */
                            CRYS_CHACHA_Key_t            pKey,                  /*!< [in]  A pointer to the user's key buffer. */
                            CRYS_CHACHA_EncryptMode_t    encryptDecryptFlag,    /*!< [in]  A flag specifying whether the CHACHA-POLY should perform an Encrypt or
                                               Decrypt operation. */
                uint8_t          *pAddData,     /*!< [in]  A pointer to the buffer of the additional data to the POLY.
                                                                                           The pointer does not need to be aligned. must not be null. */
                size_t           addDataSize,       /*!< [in]  The size of the input data. must not be 0. */
                uint8_t                     *pDataIn,              /*!< [in]  A pointer to the buffer of the input data to the CHACHA.
                                                                                           The pointer does not need to be aligned. must not be null. */
                            size_t                       dataInSize,            /*!< [in]  The size of the input data. must not be 0. */
                            uint8_t                     *pDataOut,             /*!< [out] A pointer to the buffer of the output data from the CHACHA.
                                                                                           must not be null. */
                CRYS_POLY_Mac_t      macRes         /*!< [in/out] Pointer to the MAC result buffer.*/
);



#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif /* #ifndef CRYS_CHACHA_POLY_H */





