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



#ifndef CRYS_ECPKI_KG_H
#define CRYS_ECPKI_KG_H

/*! @file
@brief Defines the API for generation of ECC private and public keys.
@defgroup crys_ecpki_kg CryptoCell ECC Key Generation APIs
@{
@ingroup cryptocell_ecpki
*/


#include "crys_error.h"
#include "crys_rnd.h"
#include "crys_ecpki_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*****************  CRYS_ECPKI_GenKeyPair function   **********************/
/*!
@brief Generates a pair of private and public keys in internal representation according to [ANS X9.62].

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_ecpki_error.h or crys_rnd_error.h
*/
CIMPORT_C CRYSError_t CRYS_ECPKI_GenKeyPair(
            void       *rndState_ptr,     /*!< [in/out] Pointer to the RND state structure. */
            SaSiRndGenerateVectWorkFunc_t rndGenerateVectFunc,   /*!< [in] Pointer to the random vector generation function.  */
                        const CRYS_ECPKI_Domain_t  *pDomain,          /*!< [in]  Pointer to EC domain (curve). */
                        CRYS_ECPKI_UserPrivKey_t   *pUserPrivKey,     /*!< [out] Pointer to the private key structure. This structure is used as input to the
                                         ECPKI cryptographic primitives. */
                        CRYS_ECPKI_UserPublKey_t   *pUserPublKey,     /*!< [out] Pointer to the public key structure. This structure is used as input to the
                                         ECPKI cryptographic primitives. */
            CRYS_ECPKI_KG_TempData_t   *pTempData,        /*!< [in] Temporary buffers for internal use, defined in ::CRYS_ECPKI_KG_TempData_t. */
                        CRYS_ECPKI_KG_FipsContext_t   *pFipsCtx       /*!< [in] Pointer to temporary buffer used in case FIPS certification if required. */
);



#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif




