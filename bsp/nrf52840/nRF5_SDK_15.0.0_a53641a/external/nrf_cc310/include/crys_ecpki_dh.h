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



#ifndef CRYS_ECPKI_DH_H
#define CRYS_ECPKI_DH_H

/*! @file
@brief Defines the API that supports EC Diffie-Hellman shared secret value derivation primitives.
@defgroup crys_ecpki_dh CryptoCell ECC Diffie-Hellman APIs
@{
@ingroup cryptocell_ecpki
*/


#include "crys_ecpki_types.h"
#include "crys_ecpki_error.h"

#ifdef __cplusplus
extern "C"
{
#endif

/***********************************************************************
 *               CRYS_ECDH_SVDP_DH function                    *
 ***********************************************************************/
/*!
@brief Creates the shared secret value according to [IEEE1363, ANS X9.63]:

<ol><li> Checks input-parameter pointers and EC Domain in public and private
keys.</li>
<li> Derives the partner public key and calls the EcWrstDhDeriveSharedSecret
function, which performs EC SVDP operations.</li></ol>
\note The term "User"
refers to any party that calculates a shared secret value using this primitive.
The term "Partner" refers to any other party of shared secret value calculation.
Partner's public key shall be validated before using in this primitive.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_ecpki_error.h.
*/
CIMPORT_C CRYSError_t CRYS_ECDH_SVDP_DH(
                        CRYS_ECPKI_UserPublKey_t *PartnerPublKey_ptr,       /*!< [in]  Pointer to a partner public key. */
                        CRYS_ECPKI_UserPrivKey_t *UserPrivKey_ptr,          /*!< [in]  Pointer to a user private key. */
                        uint8_t              *SharedSecretValue_ptr,    /*!< [out] Pointer to an output buffer that will contain the shared
                                               secret value. */
                        uint32_t                 *SharedSecrValSize_ptr,    /*!< [in/out] Pointer to the size of user-passed buffer (in) and
                                                                                          actual size of output of calculated shared secret value
                                              (out). */
                        CRYS_ECDH_TempData_t     *TempBuff_ptr              /*!< [in]  Pointer to a temporary buffer. */);

#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif
