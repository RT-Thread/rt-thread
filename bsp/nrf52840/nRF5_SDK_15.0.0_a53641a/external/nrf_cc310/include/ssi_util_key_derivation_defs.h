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


#ifndef  _SSI_UTIL_KEY_DERIVATION_DEFS_H
#define  _SSI_UTIL_KEY_DERIVATION_DEFS_H

/*!
@file
@brief This file contains the definitions for the key derivation API.
@defgroup ssi_utils_key_defs CryptoCell utils general key definitions
@{
@ingroup ssi_utils

*/

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
*                           DEFINITIONS
******************************************************************************/

/*! Maximal label length in bytes. */
#define SASI_UTIL_MAX_LABEL_LENGTH_IN_BYTES     64
/*! Maximal context length in bytes. */
#define SASI_UTIL_MAX_CONTEXT_LENGTH_IN_BYTES   64

/*! Minimal fixed data size in bytes. */
#define SASI_UTIL_FIX_DATA_MIN_SIZE_IN_BYTES    3 /*!< \internal counter, 0x00, lengt(-0xff) */
/*! Maximal fixed data size in bytes. */
#define SASI_UTIL_FIX_DATA_MAX_SIZE_IN_BYTES    4 /*!< \internal counter, 0x00, lengt(0x100-0xff0) */

/*! Maximal derived key material size in bytes. */
#define SASI_UTIL_MAX_KDF_SIZE_IN_BYTES (SASI_UTIL_MAX_LABEL_LENGTH_IN_BYTES+ \
                     SASI_UTIL_MAX_CONTEXT_LENGTH_IN_BYTES+SASI_UTIL_FIX_DATA_MAX_SIZE_IN_BYTES)

/*! Maximal derived key size in bytes. */
#define SASI_UTIL_MAX_DERIVED_KEY_SIZE_IN_BYTES 4080

#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif /*_SSI_UTIL_KEY_DERIVATION_DEFS_H*/

