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
@brief This file contains the definitions of the CryptoCell AES errors.
@defgroup ssi_aes_error CryptoCell AES specific errors
@{
@ingroup ssi_aes
*/

#ifndef SSI_AES_ERROR_H
#define SSI_AES_ERROR_H

#include "crys_error.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************ Defines ******************************/

/* generic errors */
/*! General fatal error. */
#define SASI_FATAL_ERROR                 CRYS_FATAL_ERROR
/*! General out of resources error. */
#define SASI_OUT_OF_RESOURCE_ERROR       CRYS_OUT_OF_RESOURCE_ERROR
/*! General Illegal resource value error. */
#define SASI_ILLEGAL_RESOURCE_VAL_ERROR  CRYS_ILLEGAL_RESOURCE_VAL_ERROR

/*! CRYS_AES_MODULE_ERROR_BASE - 0x00F00000. */
/*! Illegal user context. */
#define SASI_AES_INVALID_USER_CONTEXT_POINTER_ERROR     (CRYS_AES_MODULE_ERROR_BASE + 0x00UL)
/*! Illegal IV or tweak pointer. */
#define SASI_AES_INVALID_IV_OR_TWEAK_PTR_ERROR          (CRYS_AES_MODULE_ERROR_BASE + 0x01UL)
/*! Illegal operation. */
#define SASI_AES_ILLEGAL_OPERATION_MODE_ERROR           (CRYS_AES_MODULE_ERROR_BASE + 0x02UL)
/*! Illegal key size. */
#define SASI_AES_ILLEGAL_KEY_SIZE_ERROR                 (CRYS_AES_MODULE_ERROR_BASE + 0x03UL)
/*! Illegal key pointer. */
#define SASI_AES_INVALID_KEY_POINTER_ERROR              (CRYS_AES_MODULE_ERROR_BASE + 0x04UL)
/*! Unsupported key type. */
#define SASI_AES_KEY_TYPE_NOT_SUPPORTED_ERROR           (CRYS_AES_MODULE_ERROR_BASE + 0x05UL)
/*! Illegal operation. */
#define SASI_AES_INVALID_ENCRYPT_MODE_ERROR             (CRYS_AES_MODULE_ERROR_BASE + 0x06UL)
/*! User context corrupted. */
#define SASI_AES_USER_CONTEXT_CORRUPTED_ERROR           (CRYS_AES_MODULE_ERROR_BASE + 0x07UL)
/*! Illegal data in pointer. */
#define SASI_AES_DATA_IN_POINTER_INVALID_ERROR          (CRYS_AES_MODULE_ERROR_BASE + 0x08UL)
/*! Illegal data out pointer. */
#define SASI_AES_DATA_OUT_POINTER_INVALID_ERROR         (CRYS_AES_MODULE_ERROR_BASE + 0x09UL)
/*! Illegal data in size. */
#define SASI_AES_DATA_IN_SIZE_ILLEGAL                   (CRYS_AES_MODULE_ERROR_BASE + 0x0AUL)
/*! Illegal data out address. */
#define SASI_AES_DATA_OUT_DATA_IN_OVERLAP_ERROR         (CRYS_AES_MODULE_ERROR_BASE + 0x0BUL)
/*! Illegal data in buffer size. */
#define SASI_AES_DATA_IN_BUFFER_SIZE_ERROR              (CRYS_AES_MODULE_ERROR_BASE + 0x0CUL)
/*! Illegal data out buffer size. */
#define SASI_AES_DATA_OUT_BUFFER_SIZE_ERROR             (CRYS_AES_MODULE_ERROR_BASE + 0x0DUL)
/*! Illegal padding type. */
#define SASI_AES_ILLEGAL_PADDING_TYPE_ERROR             (CRYS_AES_MODULE_ERROR_BASE + 0x0EUL)
/*! Incorrect padding. */
#define SASI_AES_INCORRECT_PADDING_ERROR                (CRYS_AES_MODULE_ERROR_BASE + 0x0FUL)
/*! Output is corrupted. */
#define SASI_AES_CORRUPTED_OUTPUT_ERROR                 (CRYS_AES_MODULE_ERROR_BASE + 0x10UL)
/*! Illegal output size. */
#define SASI_AES_DATA_OUT_SIZE_POINTER_INVALID_ERROR    (CRYS_AES_MODULE_ERROR_BASE + 0x11UL)
/*! Decryption operation is not permitted in this mode. */
#define SASI_AES_DECRYPTION_NOT_ALLOWED_ON_THIS_MODE    (CRYS_AES_MODULE_ERROR_BASE + 0x12UL)
/*! Additional block operation is not permitted. */
#define SASI_AES_ADDITIONAL_BLOCK_NOT_PERMITTED_ERROR   (CRYS_AES_MODULE_ERROR_BASE + 0x15UL)
/*! Illegal context size. */
#define SASI_AES_CTX_SIZES_ERROR                    (CRYS_AES_MODULE_ERROR_BASE + 0x16UL)

/*! Illegal parameters. */
#define SASI_AES_ILLEGAL_PARAMS_ERROR               (CRYS_AES_MODULE_ERROR_BASE + 0x60UL)
/*! Illegal CTR block offset. */
#define SASI_AES_CTR_ILLEGAL_BLOCK_OFFSET_ERROR     (CRYS_AES_MODULE_ERROR_BASE + 0x70UL)
/*! Illegal counter (in CTR mode). */
#define SASI_AES_CTR_ILLEGAL_COUNTER_ERROR          (CRYS_AES_MODULE_ERROR_BASE + 0x71UL)
/*! AES is not supported. */
#define SASI_AES_IS_NOT_SUPPORTED                   (CRYS_AES_MODULE_ERROR_BASE + 0xFFUL)

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
#endif /* #ifndef SSI_AES_ERROR_H */
