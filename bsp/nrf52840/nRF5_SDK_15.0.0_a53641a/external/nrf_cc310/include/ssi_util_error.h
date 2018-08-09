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


#ifndef  _SSI_UTIL_ERROR_H
#define  _SSI_UTIL_ERROR_H

#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief This module contains the definitions of the UTIL module errors.
@defgroup ssi_utils_errors CryptoCell utils error definitions
@{
@ingroup ssi_utils

*/

/***********************/
/* Util return codes   */
/***********************/

/*! Success definition. */
#define SASI_UTIL_OK        0x00UL
/*! Error base number definition. */
#define SASI_UTIL_MODULE_ERROR_BASE 0x80000000

/*! Illegal key type. */
#define SASI_UTIL_INVALID_KEY_TYPE                  (SASI_UTIL_MODULE_ERROR_BASE + 0x00UL)
/*! Illegal data in pointer. */
#define SASI_UTIL_DATA_IN_POINTER_INVALID_ERROR     (SASI_UTIL_MODULE_ERROR_BASE + 0x01UL)
/*! Illegal data in size. */
#define SASI_UTIL_DATA_IN_SIZE_INVALID_ERROR        (SASI_UTIL_MODULE_ERROR_BASE + 0x02UL)
/*! Illegal data out pointer. */
#define SASI_UTIL_DATA_OUT_POINTER_INVALID_ERROR    (SASI_UTIL_MODULE_ERROR_BASE + 0x03UL)
/*! Illegal data out size. */
#define SASI_UTIL_DATA_OUT_SIZE_INVALID_ERROR       (SASI_UTIL_MODULE_ERROR_BASE + 0x04UL)
/*! Fatal error. */
#define SASI_UTIL_FATAL_ERROR               (SASI_UTIL_MODULE_ERROR_BASE + 0x05UL)
/*! Illegal parameters. */
#define SASI_UTIL_ILLEGAL_PARAMS_ERROR          (SASI_UTIL_MODULE_ERROR_BASE + 0x06UL)
/*! Invalid address given. */
#define SASI_UTIL_BAD_ADDR_ERROR            (SASI_UTIL_MODULE_ERROR_BASE + 0x07UL)
/*! Illegal domain for endorsement key. */
#define SASI_UTIL_EK_DOMAIN_INVALID_ERROR       (SASI_UTIL_MODULE_ERROR_BASE + 0x08UL)
/*! Kdr is not valid. */
#define SASI_UTIL_KDR_INVALID_ERROR                 (SASI_UTIL_MODULE_ERROR_BASE + 0x09UL)
/*! LCS is not valid. */
#define SASI_UTIL_LCS_INVALID_ERROR                 (SASI_UTIL_MODULE_ERROR_BASE + 0x0AUL)
/*! session key is not valid. */
#define SASI_UTIL_SESSION_KEY_ERROR                 (SASI_UTIL_MODULE_ERROR_BASE + 0x0BUL)
/*! Illegal user key size. */
#define SASI_UTIL_INVALID_USER_KEY_SIZE         (SASI_UTIL_MODULE_ERROR_BASE + 0x0DUL)
/*! Illegal LCS for the required operation. */
#define SASI_UTIL_ILLEGAL_LCS_FOR_OPERATION_ERR     (SASI_UTIL_MODULE_ERROR_BASE + 0x0EUL)

#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif /*_SSI_UTIL_ERROR_H*/
