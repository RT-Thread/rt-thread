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




#ifndef CRYS_RND_ERROR_H
#define CRYS_RND_ERROR_H

#include "crys_error.h"

#ifdef __cplusplus
extern "C"
{
#endif


/*!
@file
@brief This module contains the definitions of the CRYS RND errors.
@defgroup crys_rnd_error CryptoCell RND specific errors
@{
@ingroup crys_rnd
*/



/************************ Defines ******************************/
/*! RND module on the CRYS layer base address - 0x00F00C00 */

/*! Illegal output pointer.*/
#define CRYS_RND_DATA_OUT_POINTER_INVALID_ERROR        (CRYS_RND_MODULE_ERROR_BASE + 0x0UL)
/*! Random generation in range failed .*/
#define CRYS_RND_CAN_NOT_GENERATE_RAND_IN_RANGE        (CRYS_RND_MODULE_ERROR_BASE + 0x1UL)
/*! CPRNGT test failed.*/
#define CRYS_RND_CPRNG_TEST_FAIL_ERROR             (CRYS_RND_MODULE_ERROR_BASE + 0x2UL)
/*! Illegal additional data buffer. */
#define CRYS_RND_ADDITIONAL_INPUT_BUFFER_NULL          (CRYS_RND_MODULE_ERROR_BASE + 0x3UL)
/*! Illegal additional data size. */
#define CRYS_RND_ADDITIONAL_INPUT_SIZE_ERROR           (CRYS_RND_MODULE_ERROR_BASE + 0x4UL)
/*! Data size overflow. */
#define CRYS_RND_DATA_SIZE_OVERFLOW_ERROR          (CRYS_RND_MODULE_ERROR_BASE + 0x5UL)
/*! Illegal vector size. */
#define CRYS_RND_VECTOR_SIZE_ERROR          (CRYS_RND_MODULE_ERROR_BASE + 0x6UL)
/*! Reseed counter overflow - in case this error was returned instantiation or reseeding operation must be called. */
#define CRYS_RND_RESEED_COUNTER_OVERFLOW_ERROR      (CRYS_RND_MODULE_ERROR_BASE + 0x7UL)
/*! Instantiation was not yet called. */
#define CRYS_RND_INSTANTIATION_NOT_DONE_ERROR       (CRYS_RND_MODULE_ERROR_BASE + 0x8UL)
/*! TRNG loss of samples. */
#define CRYS_RND_TRNG_LOSS_SAMPLES_ERROR               (CRYS_RND_MODULE_ERROR_BASE + 0x9UL)
/*! TRNG Time exceeded limitations. */
#define CRYS_RND_TRNG_TIME_EXCEED_ERROR             (CRYS_RND_MODULE_ERROR_BASE + 0xAUL)
/*! TRNG loss of samples and time exceeded limitations. */
#define CRYS_RND_TRNG_LOSS_SAMPLES_AND_TIME_EXCEED_ERROR (CRYS_RND_MODULE_ERROR_BASE + 0xBUL)
/*! RND is in Known Answer Test mode. */
#define CRYS_RND_IS_KAT_MODE_ERROR                     (CRYS_RND_MODULE_ERROR_BASE + 0xCUL)
/*! RND operation not supported. */
#define CRYS_RND_OPERATION_IS_NOT_SUPPORTED_ERROR      (CRYS_RND_MODULE_ERROR_BASE + 0xDUL)
/*! RND validity check failed. */
#define CRYS_RND_STATE_VALIDATION_TAG_ERROR            (CRYS_RND_MODULE_ERROR_BASE + 0xEUL)
/*! RND is not supported. */
#define CRYS_RND_IS_NOT_SUPPORTED                      (CRYS_RND_MODULE_ERROR_BASE + 0xFUL)
/*! RND Init failed. */
#define CRYS_RND_INIT_FAILED                            (CRYS_RND_MODULE_ERROR_BASE + 0x10UL)
/*! RND Init failed. */
#define CRYS_RND_STARTUP_FAILED                         (CRYS_RND_MODULE_ERROR_BASE + 0x11UL)
/*! Instantiation Failed. */
#define CRYS_RND_INSTANTIATION_ERROR                    (CRYS_RND_MODULE_ERROR_BASE + 0x12L)


/*! Illegal generate vector function pointer. */
#define CRYS_RND_GEN_VECTOR_FUNC_ERROR                  (CRYS_RND_MODULE_ERROR_BASE + 0x14UL)

/*! Illegal work buffer pointer. */
#define CRYS_RND_WORK_BUFFER_PTR_INVALID_ERROR          (CRYS_RND_MODULE_ERROR_BASE + 0x20UL)
/*! Illegal AES key size. */
#define CRYS_RND_ILLEGAL_AES_KEY_SIZE_ERROR             (CRYS_RND_MODULE_ERROR_BASE + 0x21UL)
/*! Illegal data pointer. */
#define CRYS_RND_ILLEGAL_DATA_PTR_ERROR                 (CRYS_RND_MODULE_ERROR_BASE + 0x22UL)
/*! Illegal data size. */
#define CRYS_RND_ILLEGAL_DATA_SIZE_ERROR                (CRYS_RND_MODULE_ERROR_BASE + 0x23UL)
/*! Illegal parameter. */
#define CRYS_RND_ILLEGAL_PARAMETER_ERROR                (CRYS_RND_MODULE_ERROR_BASE + 0x24UL)
/*! Illegal RND state pointer. */
#define CRYS_RND_STATE_PTR_INVALID_ERROR                (CRYS_RND_MODULE_ERROR_BASE + 0x25UL)
/*! TRNG errors. */
#define CRYS_RND_TRNG_ERRORS_ERROR                      (CRYS_RND_MODULE_ERROR_BASE + 0x26UL)
/*! Illegal context pointer. */
#define CRYS_RND_CONTEXT_PTR_INVALID_ERROR              (CRYS_RND_MODULE_ERROR_BASE + 0x27UL)

/*! Illegal output vector pointer. */
#define CRYS_RND_VECTOR_OUT_PTR_ERROR                   (CRYS_RND_MODULE_ERROR_BASE + 0x30UL)
/*! Illegal output vector size. */
#define CRYS_RND_VECTOR_OUT_SIZE_ERROR          (CRYS_RND_MODULE_ERROR_BASE + 0x31UL)
/*! Maximal vector size is too small. */
#define CRYS_RND_MAX_VECTOR_IS_TOO_SMALL_ERROR      (CRYS_RND_MODULE_ERROR_BASE + 0x32UL)
/*! Illegal Known Answer Tests parameters. */
#define CRYS_RND_KAT_DATA_PARAMS_ERROR                  (CRYS_RND_MODULE_ERROR_BASE + 0x33UL)
/*! TRNG Known Answer Test not supported. */
#define CRYS_RND_TRNG_KAT_NOT_SUPPORTED_ERROR           (CRYS_RND_MODULE_ERROR_BASE + 0x34UL)
/*! SRAM memory is not defined. */
#define CRYS_RND_SRAM_NOT_SUPPORTED_ERROR               (CRYS_RND_MODULE_ERROR_BASE + 0x35UL)
/*! AES operation failure. */
#define CRYS_RND_AES_ERROR                              (CRYS_RND_MODULE_ERROR_BASE + 0x36UL)


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


