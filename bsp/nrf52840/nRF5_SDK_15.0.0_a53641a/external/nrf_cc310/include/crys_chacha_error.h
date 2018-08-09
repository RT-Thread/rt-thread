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


#ifndef CRYS_CHACHA_ERROR_H
#define CRYS_CHACHA_ERROR_H


#include "crys_error.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief This module contains the definitions of the CRYS CHACHA errors.
@defgroup crys_chacha_error CryptoCell CHACHA specific errors
@{
@ingroup crys_chacha
*/



/************************ Defines ******************************/

/*! The CRYS CHACHA module errors base address - 0x00F02200. */
/*! Illegal Nonce. */
#define CRYS_CHACHA_INVALID_NONCE_ERROR                         (CRYS_CHACHA_MODULE_ERROR_BASE + 0x01UL)
/*! Illegal key size. */
#define CRYS_CHACHA_ILLEGAL_KEY_SIZE_ERROR                  (CRYS_CHACHA_MODULE_ERROR_BASE + 0x02UL)
/*! Illegal key pointer. */
#define CRYS_CHACHA_INVALID_KEY_POINTER_ERROR               (CRYS_CHACHA_MODULE_ERROR_BASE + 0x03UL)
/*! Illegal operation mode. */
#define CRYS_CHACHA_INVALID_ENCRYPT_MODE_ERROR              (CRYS_CHACHA_MODULE_ERROR_BASE + 0x04UL)
/*! Illegal data in pointer. */
#define CRYS_CHACHA_DATA_IN_POINTER_INVALID_ERROR           (CRYS_CHACHA_MODULE_ERROR_BASE + 0x05UL)
/*! Illegal data out pointer. */
#define CRYS_CHACHA_DATA_OUT_POINTER_INVALID_ERROR          (CRYS_CHACHA_MODULE_ERROR_BASE + 0x06UL)
/*! Illegal user context. */
#define CRYS_CHACHA_INVALID_USER_CONTEXT_POINTER_ERROR          (CRYS_CHACHA_MODULE_ERROR_BASE + 0x07UL)
/*! Illegal user context size. */
#define CRYS_CHACHA_CTX_SIZES_ERROR                             (CRYS_CHACHA_MODULE_ERROR_BASE + 0x08UL)
/*! Illegal Nonce pointer. */
#define CRYS_CHACHA_INVALID_NONCE_PTR_ERROR                        (CRYS_CHACHA_MODULE_ERROR_BASE + 0x09UL)
/*! Illegal data in size. */
#define CRYS_CHACHA_DATA_IN_SIZE_ILLEGAL                        (CRYS_CHACHA_MODULE_ERROR_BASE + 0x0AUL)
/*! General error. */
#define CRYS_CHACHA_GENERAL_ERROR                           (CRYS_CHACHA_MODULE_ERROR_BASE + 0x0BUL)
/*! CHACHA is not supported. */
#define CRYS_CHACHA_IS_NOT_SUPPORTED                        (CRYS_CHACHA_MODULE_ERROR_BASE + 0xFFUL)

/************************ Enums ********************************/

/************************ Typedefs  ****************************/

/************************ Structs  *****************************/

/************************ Public Variables *********************/

/************************ Public Functions *********************/

#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif


