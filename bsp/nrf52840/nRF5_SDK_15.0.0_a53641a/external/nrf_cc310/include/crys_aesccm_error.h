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




#ifndef CRYS_AESCCM_ERROR_H
#define CRYS_AESCCM_ERROR_H


#include "crys_error.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief This module contains the definitions of the CRYS AESCCM errors.
@defgroup crys_aesccm_error CryptoCell AES-CCM specific errors
@{
@ingroup crys_aesccm
*/

/************************ Defines ******************************/

/*! CRYS AESCCM module errors. CRYS_AESCCM_MODULE_ERROR_BASE = 0x00F01500. */
/*! Invalid context pointer. */
#define CRYS_AESCCM_INVALID_USER_CONTEXT_POINTER_ERROR     (CRYS_AESCCM_MODULE_ERROR_BASE + 0x00UL)
/*! Illegal key size. */
#define CRYS_AESCCM_ILLEGAL_KEY_SIZE_ERROR                 (CRYS_AESCCM_MODULE_ERROR_BASE + 0x01UL)
/*! Invalid key pointer. */
#define CRYS_AESCCM_INVALID_KEY_POINTER_ERROR              (CRYS_AESCCM_MODULE_ERROR_BASE + 0x02UL)
/*! Invalid encryption mode. */
#define CRYS_AESCCM_INVALID_ENCRYPT_MODE_ERROR             (CRYS_AESCCM_MODULE_ERROR_BASE + 0x03UL)
/*! Context is corrupted. */
#define CRYS_AESCCM_USER_CONTEXT_CORRUPTED_ERROR           (CRYS_AESCCM_MODULE_ERROR_BASE + 0x04UL)
/*! Invalid data in pointer. */
#define CRYS_AESCCM_DATA_IN_POINTER_INVALID_ERROR          (CRYS_AESCCM_MODULE_ERROR_BASE + 0x05UL)
/*! Invalid data out pointer. */
#define CRYS_AESCCM_DATA_OUT_POINTER_INVALID_ERROR         (CRYS_AESCCM_MODULE_ERROR_BASE + 0x06UL)
/*! Illegal data in size. */
#define CRYS_AESCCM_DATA_IN_SIZE_ILLEGAL                   (CRYS_AESCCM_MODULE_ERROR_BASE + 0x07UL)
/*! Illegal data in or data out address. */
#define CRYS_AESCCM_DATA_OUT_DATA_IN_OVERLAP_ERROR         (CRYS_AESCCM_MODULE_ERROR_BASE + 0x08UL)
/*! Illegal data out size. */
#define CRYS_AESCCM_DATA_OUT_SIZE_INVALID_ERROR            (CRYS_AESCCM_MODULE_ERROR_BASE + 0x09UL)
/*! Illegal call to process additional data. */
#define CRYS_AESCCM_ADDITIONAL_BLOCK_NOT_PERMITTED_ERROR   (CRYS_AESCCM_MODULE_ERROR_BASE + 0x0AUL)
/*! Illegal dma buffer type. */
#define CRYS_AESCCM_ILLEGAL_DMA_BUFF_TYPE_ERROR            (CRYS_AESCCM_MODULE_ERROR_BASE + 0x0BUL)
/*! Illegal parameter size. */
#define CRYS_AESCCM_ILLEGAL_PARAMETER_SIZE_ERROR           (CRYS_AESCCM_MODULE_ERROR_BASE + 0x0CUL)
/*! Invalid parameter pointer. */
#define CRYS_AESCCM_ILLEGAL_PARAMETER_PTR_ERROR            (CRYS_AESCCM_MODULE_ERROR_BASE + 0x0DUL)
/*! Invalid data type. */
#define CRYS_AESCCM_ILLEGAL_DATA_TYPE_ERROR                (CRYS_AESCCM_MODULE_ERROR_BASE + 0x0EUL)
/*! CCM MAC compare failure. */
#define CRYS_AESCCM_CCM_MAC_INVALID_ERROR                  (CRYS_AESCCM_MODULE_ERROR_BASE + 0x0FUL)
/*! Illegal operation. */
#define CRYS_AESCCM_LAST_BLOCK_NOT_PERMITTED_ERROR         (CRYS_AESCCM_MODULE_ERROR_BASE + 0x10UL)
/*! Illegal parameter. */
#define CRYS_AESCCM_ILLEGAL_PARAMETER_ERROR                (CRYS_AESCCM_MODULE_ERROR_BASE + 0x11UL)
/*! Additional data input size is incorrect. */
#define CRYS_AESCCM_NOT_ALL_ADATA_WAS_PROCESSED_ERROR      (CRYS_AESCCM_MODULE_ERROR_BASE + 0x13UL)
/*! Text data input size is incorrect. */
#define CRYS_AESCCM_NOT_ALL_DATA_WAS_PROCESSED_ERROR       (CRYS_AESCCM_MODULE_ERROR_BASE + 0x14UL)
/*! Additional data was already processed (must be processed only once). */
#define CRYS_AESCCM_ADATA_WAS_PROCESSED_ERROR          (CRYS_AESCCM_MODULE_ERROR_BASE + 0x15UL)
/*! Illegal Nonce size. */
#define CRYS_AESCCM_ILLEGAL_NONCE_SIZE_ERROR           (CRYS_AESCCM_MODULE_ERROR_BASE + 0x16UL)
/*! Illegal tag (MAC) size. */
#define CRYS_AESCCM_ILLEGAL_TAG_SIZE_ERROR         (CRYS_AESCCM_MODULE_ERROR_BASE + 0x17UL)

/*! Illegal context size. */
#define CRYS_AESCCM_CTX_SIZES_ERROR            (CRYS_AESCCM_MODULE_ERROR_BASE + 0x28UL)
/*! Illegal parameters. */
#define CRYS_AESCCM_ILLEGAL_PARAMS_ERROR           (CRYS_AESCCM_MODULE_ERROR_BASE + 0x29UL)
/*! AESCCM is not supported. */
#define CRYS_AESCCM_IS_NOT_SUPPORTED                       (CRYS_AESCCM_MODULE_ERROR_BASE + 0xFFUL)

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


