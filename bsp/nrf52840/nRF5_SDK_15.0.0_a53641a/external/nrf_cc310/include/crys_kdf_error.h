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


#ifndef CRYS_KDF_ERROR_H
#define CRYS_KDF_ERROR_H

#include "crys_error.h"


#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief This module contains the definitions of the CRYS KDF errors.
@defgroup crys_kdf_error CryptoCell Key Derivation specific errors
@{
@ingroup crys_kdf
 */


/************************ Defines *******************************/

/*! The CRYS KDF module errors / base address - 0x00F01100*/
/*! Illegal input pointer. */
#define CRYS_KDF_INVALID_ARGUMENT_POINTER_ERROR         (CRYS_KDF_MODULE_ERROR_BASE + 0x0UL)
/*! Illegal input size. */
#define CRYS_KDF_INVALID_ARGUMENT_SIZE_ERROR            (CRYS_KDF_MODULE_ERROR_BASE + 0x1UL)
/*! Illegal operation mode. */
#define CRYS_KDF_INVALID_ARGUMENT_OPERATION_MODE_ERROR      (CRYS_KDF_MODULE_ERROR_BASE + 0x2UL)
/*! Illegal hash mode. */
#define CRYS_KDF_INVALID_ARGUMENT_HASH_MODE_ERROR       (CRYS_KDF_MODULE_ERROR_BASE + 0x3UL)
/*! Illegal key derivation mode. */
#define CRYS_KDF_INVALID_KEY_DERIVATION_MODE_ERROR              (CRYS_KDF_MODULE_ERROR_BASE + 0x4UL)
/*! Illegal shared secret value size. */
#define CRYS_KDF_INVALID_SHARED_SECRET_VALUE_SIZE_ERROR         (CRYS_KDF_MODULE_ERROR_BASE + 0x5UL)
/*! Illegal otherInfo size. */
#define CRYS_KDF_INVALID_OTHER_INFO_SIZE_ERROR                  (CRYS_KDF_MODULE_ERROR_BASE + 0x6UL)
/*! Illegal key data size. */
#define CRYS_KDF_INVALID_KEYING_DATA_SIZE_ERROR                 (CRYS_KDF_MODULE_ERROR_BASE + 0x7UL)
/*! Illegal algorithm ID pointer. */
#define CRYS_KDF_INVALID_ALGORITHM_ID_POINTER_ERROR             (CRYS_KDF_MODULE_ERROR_BASE + 0x8UL)
/*! Illegal algorithm ID size. */
#define CRYS_KDF_INVALID_ALGORITHM_ID_SIZE_ERROR                (CRYS_KDF_MODULE_ERROR_BASE + 0x9UL)
/*! KDF is not supproted. */
#define CRYS_KDF_IS_NOT_SUPPORTED                               (CRYS_KDF_MODULE_ERROR_BASE + 0xFFUL)

/************************ Enums *********************************/

/************************ Typedefs  *****************************/

/************************ Structs  ******************************/

/************************ Public Variables **********************/

/************************ Public Functions **********************/




#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif




