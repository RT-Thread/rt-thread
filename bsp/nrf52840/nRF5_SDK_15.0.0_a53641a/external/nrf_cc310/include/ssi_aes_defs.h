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
@brief This file contains definitions that are used for the ARM CryptoCell 3xx version of the CryptoCell AES APIs.
@defgroup ssi_aes_defs CryptoCell AES definitions
@{
@ingroup ssi_aes

*/

#ifndef SSI_AES_DEFS_H
#define SSI_AES_DEFS_H

#include "ssi_pal_types.h"


#ifdef __cplusplus
extern "C"
{
#endif

/************************ Defines ******************************/

/*! The size of the user's context prototype (see ::SaSiAesUserContext_t) in words. */
#define SASI_AES_USER_CTX_SIZE_IN_WORDS (4+4+7+4)

/*! The AES block size in words. */
#define SASI_AES_BLOCK_SIZE_IN_WORDS 4
/*! The AES block size in bytes. */
#define SASI_AES_BLOCK_SIZE_IN_BYTES  (SASI_AES_BLOCK_SIZE_IN_WORDS * sizeof(uint32_t))

/*! The size of the IV buffer in words. */
#define SASI_AES_IV_SIZE_IN_WORDS   SASI_AES_BLOCK_SIZE_IN_WORDS
/*! The size of the IV buffer in bytes. */
#define SASI_AES_IV_SIZE_IN_BYTES  (SASI_AES_IV_SIZE_IN_WORDS * sizeof(uint32_t))

/*! The maximum size of the AES KEY in words. */
#define SASI_AES_KEY_MAX_SIZE_IN_WORDS 4
/*! The maximum size of the AES KEY in bytes. */
#define SASI_AES_KEY_MAX_SIZE_IN_BYTES (SASI_AES_KEY_MAX_SIZE_IN_WORDS * sizeof(uint32_t))


#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif /* #ifndef SSI_AES_DEFS_H */
