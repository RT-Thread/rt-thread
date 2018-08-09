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



#ifndef CRYS_DH_ERROR_H
#define CRYS_DH_ERROR_H


#include "crys_error.h"


#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief This file contains error codes definitions for CRYS DH module.
@defgroup crys_dh_error CryptoCell DH specific errors
@{
@ingroup crys_dh
*/
/************************ Defines ******************************/
/* DH module on the CRYS layer base address - 0x00F00500 */
/*! The CRYS DH module errors */
/*! Illegal input pointer.*/
#define CRYS_DH_INVALID_ARGUMENT_POINTER_ERROR          (CRYS_DH_MODULE_ERROR_BASE + 0x0UL)
/*! Illegal input size.*/
#define CRYS_DH_INVALID_ARGUMENT_SIZE_ERROR         (CRYS_DH_MODULE_ERROR_BASE + 0x1UL)
/*! Illegal operation mode.*/
#define CRYS_DH_INVALID_ARGUMENT_OPERATION_MODE_ERROR       (CRYS_DH_MODULE_ERROR_BASE + 0x2UL)
/*! Illegal hash mode.*/
#define CRYS_DH_INVALID_ARGUMENT_HASH_MODE_ERROR        (CRYS_DH_MODULE_ERROR_BASE + 0x3UL)

/*! Illegal secret key data size. */
#define CRYS_DH_SECRET_KEYING_DATA_SIZE_ILLEGAL_ERROR       (CRYS_DH_MODULE_ERROR_BASE + 0x4UL)
/*! Illegal L input. */
#define CRYS_DH_INVALID_L_ARGUMENT_ERROR            (CRYS_DH_MODULE_ERROR_BASE + 0x5UL)
/*! Prime is smaller than generator. */
#define CRYS_DH_ARGUMENT_PRIME_SMALLER_THAN_GENERATOR_ERROR (CRYS_DH_MODULE_ERROR_BASE + 0x6UL)
/*! Generator is smaller than zero. */
#define CRYS_DH_ARGUMENT_GENERATOR_SMALLER_THAN_ZERO_ERROR      (CRYS_DH_MODULE_ERROR_BASE + 0x7UL)
/*! Illegal private key size. */
#define CRYS_DH_ARGUMENT_PRV_SIZE_ERROR             (CRYS_DH_MODULE_ERROR_BASE + 0x8UL)
/*! Illegal buffer size. */
#define CRYS_DH_ARGUMENT_BUFFER_SIZE_ERROR          (CRYS_DH_MODULE_ERROR_BASE + 0x9UL)
/*! Invalid shared secret value. */
#define CRYS_DH_INVALID_SHARED_SECRET_VALUE_ERROR       (CRYS_DH_MODULE_ERROR_BASE + 0xAUL)
/*! DH is not supported. */
#define CRYS_DH_IS_NOT_SUPPORTED                (CRYS_DH_MODULE_ERROR_BASE + 0xFUL)
/*! Illegal X942 hybrid buffer size.*/
#define CRYS_DH_X942_HYBRID_SIZE1_BUFFER_ERROR          (CRYS_DH_MODULE_ERROR_BASE + 0x15UL)

/*The requested derived secret key size is invalid*/
/*! Illegal secret key size .*/
#define CRYS_DH_SECRET_KEY_SIZE_NEEDED_ERROR            (CRYS_DH_MODULE_ERROR_BASE + 0x16UL)
/*! Illegal output secret key size .*/
#define CRYS_DH_SECRET_KEY_SIZE_OUTPUT_ERROR            (CRYS_DH_MODULE_ERROR_BASE + 0x17UL)
/*! Illegal otherInfo size .*/
#define CRYS_DH_OTHERINFO_SIZE_ERROR                            (CRYS_DH_MODULE_ERROR_BASE + 0x18UL)

/* DH domain and key generation and checking errors */
/*! Illegal modulus size. */
#define CRYS_DH_INVALID_MODULUS_SIZE_ERROR          (CRYS_DH_MODULE_ERROR_BASE + 0x20UL)
/*! Illegal order size. */
#define CRYS_DH_INVALID_ORDER_SIZE_ERROR            (CRYS_DH_MODULE_ERROR_BASE + 0x21UL)
/*! Illegal seed size. */
#define CRYS_DH_INVALID_SEED_SIZE_ERROR             (CRYS_DH_MODULE_ERROR_BASE + 0x22UL)
/*! Illegal J factor pointer size. */
#define CRYS_DH_INVALID_J_FACTOR_PTR_OR_SIZE_ERROR      (CRYS_DH_MODULE_ERROR_BASE + 0x23UL)
/*! Illegal generator pointer or size. */
#define CRYS_DH_INVALID_GENERATOR_PTR_OR_SIZE_ERROR         (CRYS_DH_MODULE_ERROR_BASE + 0x24UL)

/*! Illegal domain primes. */
#define CRYS_DH_CHECK_DOMAIN_PRIMES_NOT_VALID_ERROR             (CRYS_DH_MODULE_ERROR_BASE + 0x25UL)
/*! Illegal domain generator. */
#define CRYS_DH_CHECK_DOMAIN_GENERATOR_NOT_VALID_ERROR          (CRYS_DH_MODULE_ERROR_BASE + 0x26UL)
/*! Illegal public key size. */
#define CRYS_DH_INVALID_PUBLIC_KEY_SIZE_ERROR                   (CRYS_DH_MODULE_ERROR_BASE + 0x27UL)
/*! Illegal public key. */
#define CRYS_DH_CHECK_PUB_KEY_NOT_VALID_ERROR                   (CRYS_DH_MODULE_ERROR_BASE + 0x28UL)
/*! Illegal generator size or pointer. */
#define CRYS_DH_CHECK_GENERATOR_SIZE_OR_PTR_NOT_VALID_ERROR     (CRYS_DH_MODULE_ERROR_BASE + 0x29UL)
/*! Illegal seed size or pointer. */
#define CRYS_DH_CHECK_SEED_SIZE_OR_PTR_NOT_VALID_ERROR          (CRYS_DH_MODULE_ERROR_BASE + 0x2AUL)
/*! Illegal generator. */
#define CRYS_DH_CHECK_GENERATOR_NOT_VALID_ERROR                 (CRYS_DH_MODULE_ERROR_BASE + 0x2BUL)
/*! Prime generation failed. */
#define CRYS_DH_PRIME_P_GENERATION_FAILURE_ERROR                (CRYS_DH_MODULE_ERROR_BASE + 0x2CUL)
/*! Illegal public key. */
#define CRYS_DH_INVALID_PUBLIC_KEY_ERROR                        (CRYS_DH_MODULE_ERROR_BASE + 0x2DUL)
/*! Illegal seed. */
#define CRYS_DH_PASSED_INVALID_SEED_ERROR                   (CRYS_DH_MODULE_ERROR_BASE + 0x2EUL)
/*! Prime generation failed. */
#define CRYS_DH_PRIME_Q_GENERATION_FAILURE_ERROR            (CRYS_DH_MODULE_ERROR_BASE + 0x2FUL)
/*! Internal PKI error */
#define CRYS_DH_PKI_INTERNAL_ERROR                              (CRYS_DH_MODULE_ERROR_BASE + 0x30UL)



/************************ Enums ********************************/


/************************ Typedefs  ****************************/


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

