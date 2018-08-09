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


#ifndef  _SSI_UTIL_DEFS_H
#define  _SSI_UTIL_DEFS_H

/*!
@defgroup ssi_utils CryptoCell utility APIs
@{
@ingroup cryptocell_api
@brief This group is the utility apis group
@}

@file
@brief This file contains CryptoCell Util general definitions.
@defgroup ssi_utils_defs CryptoCell utils general definitions
@{
@ingroup ssi_utils

*/


#ifdef __cplusplus
extern "C"
{
#endif

#include "ssi_pal_types_plat.h"
#include "ssi_util_key_derivation_defs.h"


/******************************************************************************
*                           DEFINITIONS
******************************************************************************/
/*! Supported AES key size in bits. */
#define SASI_UTIL_AES_128BIT_SIZE   16  // same as SEP_AES_128_BIT_KEY_SIZE
/*****************************************/
/* CMAC derive key definitions*/
/*****************************************/
/*! Minimal data size for CMAC derivation operation. */
#define SASI_UTIL_CMAC_DERV_MIN_DATA_IN_SIZE    SASI_UTIL_FIX_DATA_MIN_SIZE_IN_BYTES+2
/*! Maximal data size for CMAC derivation operation. */
#define SASI_UTIL_CMAC_DERV_MAX_DATA_IN_SIZE    SASI_UTIL_MAX_KDF_SIZE_IN_BYTES
/*! AES CMAC result size in bytes. */
#define SASI_UTIL_AES_CMAC_RESULT_SIZE_IN_BYTES 0x10UL
/*! AES CMAC result size in words. */
#define SASI_UTIL_AES_CMAC_RESULT_SIZE_IN_WORDS (SASI_UTIL_AES_CMAC_RESULT_SIZE_IN_BYTES/4)

/*! Util Error type. */
typedef uint32_t SaSiUtilError_t;
/*! Defines the CMAC result buffer. */
typedef uint8_t SaSiUtilAesCmacResult_t[SASI_UTIL_AES_CMAC_RESULT_SIZE_IN_BYTES];


#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif /*_SSI_UTIL_DEFS_H*/
