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



 #ifndef CRYS_RSA_ERROR_H
#define CRYS_RSA_ERROR_H


#include "crys_error.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*! @file
@brief This module contains the definitions of the CRYS RSA errors.
@defgroup crys_rsa_error CryptoCell RSA specific errors
@{
@ingroup crys_rsa
*/

/************************ Defines ******************************/

/*! CRYS RSA module on the CRYS layer base address - 0x00F00400 */

/*! The CRYS RSA module errors */
/*! Illegal modulus size. */
#define CRYS_RSA_INVALID_MODULUS_SIZE                        (CRYS_RSA_MODULE_ERROR_BASE + 0x0UL)
/*! Illegal modulus pointer. */
#define CRYS_RSA_INVALID_MODULUS_POINTER_ERROR               (CRYS_RSA_MODULE_ERROR_BASE + 0x1UL)
/*! Illegal exponent pointer. */
#define CRYS_RSA_INVALID_EXPONENT_POINTER_ERROR              (CRYS_RSA_MODULE_ERROR_BASE + 0x2UL)
/*! Illegal public key structure pointer. */
#define CRYS_RSA_INVALID_PUB_KEY_STRUCT_POINTER_ERROR        (CRYS_RSA_MODULE_ERROR_BASE + 0x3UL)
/*! Illegal private key structure pointer. */
#define CRYS_RSA_INVALID_PRIV_KEY_STRUCT_POINTER_ERROR       (CRYS_RSA_MODULE_ERROR_BASE + 0x4UL)
/*! Illegal exponent value. */
#define CRYS_RSA_INVALID_EXPONENT_VAL                        (CRYS_RSA_MODULE_ERROR_BASE + 0x5UL)
/*! Illegal exponent size. */
#define CRYS_RSA_INVALID_EXPONENT_SIZE                       (CRYS_RSA_MODULE_ERROR_BASE + 0x6UL)
/*! Illegal CRT first factor pointer (P_ptr) . */
#define CRYS_RSA_INVALID_CRT_FIRST_FACTOR_POINTER_ERROR      (CRYS_RSA_MODULE_ERROR_BASE + 0x7UL)
/*! Illegal CRT second factor pointer (Q_ptr) . */
#define CRYS_RSA_INVALID_CRT_SECOND_FACTOR_POINTER_ERROR     (CRYS_RSA_MODULE_ERROR_BASE + 0x8UL)
/*! Illegal CRT first exponent factor pointer (dP_ptr) . */
#define CRYS_RSA_INVALID_CRT_FIRST_FACTOR_EXP_PTR_ERROR      (CRYS_RSA_MODULE_ERROR_BASE + 0x9UL)
/*! Illegal CRT second exponent factor pointer (dQ_ptr) . */
#define CRYS_RSA_INVALID_CRT_SECOND_FACTOR_EXP_PTR_ERROR     (CRYS_RSA_MODULE_ERROR_BASE + 0xAUL)
/*! Illegal CRT coefficient pointer (qInv_ptr) . */
#define CRYS_RSA_INVALID_CRT_COEFFICIENT_PTR_ERROR           (CRYS_RSA_MODULE_ERROR_BASE + 0xBUL)
/*! Illegal CRT first factor size (Psize). */
#define CRYS_RSA_INVALID_CRT_FIRST_FACTOR_SIZE               (CRYS_RSA_MODULE_ERROR_BASE + 0xCUL)
/*! Illegal CRT second factor size (Qsize). */
#define CRYS_RSA_INVALID_CRT_SECOND_FACTOR_SIZE              (CRYS_RSA_MODULE_ERROR_BASE + 0xDUL)
/*! Illegal CRT first and second factor size (Psize + Qsize). */
#define CRYS_RSA_INVALID_CRT_FIRST_AND_SECOND_FACTOR_SIZE    (CRYS_RSA_MODULE_ERROR_BASE + 0xEUL)
/*! Illegal CRT first factor exponent value (dP). */
#define CRYS_RSA_INVALID_CRT_FIRST_FACTOR_EXPONENT_VAL       (CRYS_RSA_MODULE_ERROR_BASE + 0xFUL)
/*! Illegal CRT first factor exponent value (dQ). */
#define CRYS_RSA_INVALID_CRT_SECOND_FACTOR_EXPONENT_VAL      (CRYS_RSA_MODULE_ERROR_BASE + 0x10UL)
/*! Illegal CRT coefficient value (qInv). */
#define CRYS_RSA_INVALID_CRT_COEFF_VAL                       (CRYS_RSA_MODULE_ERROR_BASE + 0x11UL)
/*! Illegal data in. */
#define CRYS_RSA_DATA_POINTER_INVALID_ERROR                  (CRYS_RSA_MODULE_ERROR_BASE + 0x12UL)
/*! Illegal message data size. */
#define CRYS_RSA_INVALID_MESSAGE_DATA_SIZE                   (CRYS_RSA_MODULE_ERROR_BASE + 0x13UL)
/*! Illegal message value. */
#define CRYS_RSA_INVALID_MESSAGE_VAL                         (CRYS_RSA_MODULE_ERROR_BASE + 0x14UL)

/*! Modulus even error. */
#define CRYS_RSA_MODULUS_EVEN_ERROR                          (CRYS_RSA_MODULE_ERROR_BASE + 0x15UL)
/*! Illegal context pointer. */
#define CRYS_RSA_INVALID_USER_CONTEXT_POINTER_ERROR          (CRYS_RSA_MODULE_ERROR_BASE + 0x16UL)
/*! Illegal hash operation mode. */
#define CRYS_RSA_HASH_ILLEGAL_OPERATION_MODE_ERROR           (CRYS_RSA_MODULE_ERROR_BASE + 0x17UL)
/*! Illegal MGF value. */
#define CRYS_RSA_MGF_ILLEGAL_ARG_ERROR                       (CRYS_RSA_MODULE_ERROR_BASE + 0x18UL)
/*! Illegal PKCS1 version. */
#define CRYS_RSA_PKCS1_VER_ARG_ERROR                         (CRYS_RSA_MODULE_ERROR_BASE + 0x19UL)

/*! Invalid private key. */
#define CRYS_RSA_PRIV_KEY_VALIDATION_TAG_ERROR               (CRYS_RSA_MODULE_ERROR_BASE + 0x1AUL)
/*! Invalid public key. */
#define CRYS_RSA_PUB_KEY_VALIDATION_TAG_ERROR                (CRYS_RSA_MODULE_ERROR_BASE + 0x1BUL)
/*! Invalid context. */
#define CRYS_RSA_USER_CONTEXT_VALIDATION_TAG_ERROR           (CRYS_RSA_MODULE_ERROR_BASE + 0x1CUL)
/*! Illegal output pointer. */
#define CRYS_RSA_INVALID_OUTPUT_POINTER_ERROR                (CRYS_RSA_MODULE_ERROR_BASE + 0x1DUL)
/*! Illegal output size pointer. */
#define CRYS_RSA_INVALID_OUTPUT_SIZE_POINTER_ERROR           (CRYS_RSA_MODULE_ERROR_BASE + 0x1FUL)
/*! Illegal temporary buffer pointer. */
#define CRYS_RSA_CONV_TO_CRT_INVALID_TEMP_BUFF_POINTER_ERROR (CRYS_RSA_MODULE_ERROR_BASE + 0x20UL)

/*! OAEP encode parameter string is too long. */
#define CRYS_RSA_BASE_OAEP_ENCODE_PARAMETER_STRING_TOO_LONG  (CRYS_RSA_MODULE_ERROR_BASE + 0x22UL)
/*! OAEP decode parameter string is too long. */
#define CRYS_RSA_BASE_OAEP_DECODE_PARAMETER_STRING_TOO_LONG  (CRYS_RSA_MODULE_ERROR_BASE + 0x23UL)
/*! OAEP encode message is too long. */
#define CRYS_RSA_BASE_OAEP_ENCODE_MESSAGE_TOO_LONG           (CRYS_RSA_MODULE_ERROR_BASE + 0x24UL)
/*! OAEP decode message is too long. */
#define CRYS_RSA_BASE_OAEP_DECODE_MESSAGE_TOO_LONG           (CRYS_RSA_MODULE_ERROR_BASE + 0x25UL)
/*! Illegal key generation data struct pointer. */
#define CRYS_RSA_KEY_GEN_DATA_STRUCT_POINTER_INVALID         (CRYS_RSA_MODULE_ERROR_BASE + 0x26UL)
/*! Illegal PRIM data struct pointer. */
#define CRYS_RSA_PRIM_DATA_STRUCT_POINTER_INVALID            (CRYS_RSA_MODULE_ERROR_BASE + 0x27UL)
/*! Illegal message buffer size. */
#define CRYS_RSA_INVALID_MESSAGE_BUFFER_SIZE                 (CRYS_RSA_MODULE_ERROR_BASE + 0x28UL)
/*! Illegal signature buffer size. */
#define CRYS_RSA_INVALID_SIGNATURE_BUFFER_SIZE               (CRYS_RSA_MODULE_ERROR_BASE + 0x29UL)
/*! Illegal modulus size pointer. */
#define CRYS_RSA_INVALID_MOD_BUFFER_SIZE_POINTER             (CRYS_RSA_MODULE_ERROR_BASE + 0x2AUL)
/*! Illegal exponent size pointer. */
#define CRYS_RSA_INVALID_EXP_BUFFER_SIZE_POINTER             (CRYS_RSA_MODULE_ERROR_BASE + 0x2BUL)
/*! Illegal signature pointer. */
#define CRYS_RSA_INVALID_SIGNATURE_BUFFER_POINTER            (CRYS_RSA_MODULE_ERROR_BASE + 0x2CUL)
/*! Wrong private key type. */
#define CRYS_RSA_WRONG_PRIVATE_KEY_TYPE                      (CRYS_RSA_MODULE_ERROR_BASE + 0x2DUL)

/*! Illegal CRT first factor size pointer (Psize) . */
#define CRYS_RSA_INVALID_CRT_FIRST_FACTOR_SIZE_POINTER_ERROR (CRYS_RSA_MODULE_ERROR_BASE + 0x2EUL)
/*! Illegal CRT second factor size pointer (Qsize) . */
#define CRYS_RSA_INVALID_CRT_SECOND_FACTOR_SIZE_POINTER_ERROR (CRYS_RSA_MODULE_ERROR_BASE + 0x2FUL)
/*! Illegal CRT first factor exponent size pointer (dPsize) . */
#define CRYS_RSA_INVALID_CRT_FIRST_FACTOR_EXP_SIZE_PTR_ERROR (CRYS_RSA_MODULE_ERROR_BASE + 0x30UL)
/*! Illegal CRT second factor exponent size pointer (dQsize) . */
#define CRYS_RSA_INVALID_CRT_SECOND_FACTOR_EXP_SIZE_PTR_ERROR (CRYS_RSA_MODULE_ERROR_BASE + 0x31UL)
/*! Illegal CRT coefficient size pointer (qInvsize) . */
#define CRYS_RSA_INVALID_CRT_COEFFICIENT_SIZE_PTR_ERROR      (CRYS_RSA_MODULE_ERROR_BASE + 0x32UL)

/*! Illegal CRT first factor size (Psize) . */
#define CRYS_RSA_INVALID_CRT_FIRST_FACTOR_SIZE_ERROR         (CRYS_RSA_MODULE_ERROR_BASE + 0x33UL)
/*! Illegal CRT second factor size (Qsize) . */
#define CRYS_RSA_INVALID_CRT_SECOND_FACTOR_SIZE_ERROR        (CRYS_RSA_MODULE_ERROR_BASE + 0x34UL)
/*! Illegal CRT first factor exponent size (dPsize) . */
#define CRYS_RSA_INVALID_CRT_FIRST_FACTOR_EXP_SIZE_ERROR     (CRYS_RSA_MODULE_ERROR_BASE + 0x35UL)
/*! Illegal CRT second factor exponent size (dQsize) . */
#define CRYS_RSA_INVALID_CRT_SECOND_FACTOR_EXP_SIZE_ERROR    (CRYS_RSA_MODULE_ERROR_BASE + 0x36UL)
/*! Illegal CRT coefficient size (qInvsize) . */
#define CRYS_RSA_INVALID_CRT_COEFFICIENT_SIZE_ERROR          (CRYS_RSA_MODULE_ERROR_BASE + 0x37UL)
/*! Key generation conditional test failed. */
#define CRYS_RSA_KEY_GEN_CONDITIONAL_TEST_FAIL_ERROR         (CRYS_RSA_MODULE_ERROR_BASE + 0x38UL)

/*! Random generation in range failed. */
#define CRYS_RSA_CAN_NOT_GENERATE_RAND_IN_RANGE              (CRYS_RSA_MODULE_ERROR_BASE + 0x39UL)
/*! Illegal CRT parameter size. */
#define CRYS_RSA_INVALID_CRT_PARAMETR_SIZE_ERROR             (CRYS_RSA_MODULE_ERROR_BASE + 0x3AUL)

/*! Illegal modulus. */
#define CRYS_RSA_INVALID_MODULUS_ERROR                       (CRYS_RSA_MODULE_ERROR_BASE + 0x40UL)
/*! Illegal pointer. */
#define CRYS_RSA_INVALID_PTR_ERROR                           (CRYS_RSA_MODULE_ERROR_BASE + 0x41UL)
/*! Illegal decryption mode. */
#define CRYS_RSA_INVALID_DECRYPRION_MODE_ERROR               (CRYS_RSA_MODULE_ERROR_BASE + 0x42UL)

/*! Illegal generated private key. */
#define CRYS_RSA_GENERATED_PRIV_KEY_IS_TOO_LOW               (CRYS_RSA_MODULE_ERROR_BASE + 0x43UL)
/*! Key generation error. */
#define CRYS_RSA_KEY_GENERATION_FAILURE_ERROR                (CRYS_RSA_MODULE_ERROR_BASE + 0x44UL)
/*! Internal error. */
#define CRYS_RSA_INTERNAL_ERROR                              (CRYS_RSA_MODULE_ERROR_BASE + 0x45UL)


/****************************************************************************************
 * PKCS#1 VERSION 1.5 ERRORS
 ****************************************************************************************/
/*! BER encoding passed. */
#define CRYS_RSA_BER_ENCODING_OK                            CRYS_OK
/*! Error in BER parsing. */
#define CRYS_RSA_ERROR_BER_PARSING                         (CRYS_RSA_MODULE_ERROR_BASE+0x51UL)
/*! Error in PKCS15 message. */
#define CRYS_RSA_ENCODE_15_MSG_OUT_OF_RANGE                (CRYS_RSA_MODULE_ERROR_BASE+0x52UL)
/*! Error in PKCS15 PS. */
#define CRYS_RSA_ENCODE_15_PS_TOO_SHORT                    (CRYS_RSA_MODULE_ERROR_BASE+0x53UL)
/*! PKCS15 block type is not supported. */
#define CRYS_RSA_PKCS1_15_BLOCK_TYPE_NOT_SUPPORTED         (CRYS_RSA_MODULE_ERROR_BASE+0x54UL)
/*! Error in PKCS15 decrypted block parsing. */
#define CRYS_RSA_15_ERROR_IN_DECRYPTED_BLOCK_PARSING       (CRYS_RSA_MODULE_ERROR_BASE+0x55UL)
/*! Error in random operation. */
#define CRYS_RSA_ERROR_IN_RANDOM_OPERATION_FOR_ENCODE      (CRYS_RSA_MODULE_ERROR_BASE+0x56UL)
/*! PKCS15 verification failed. */
#define CRYS_RSA_ERROR_VER15_INCONSISTENT_VERIFY           (CRYS_RSA_MODULE_ERROR_BASE+0x57UL)
/*! Illegal message size (in no hash operation case). */
#define CRYS_RSA_INVALID_MESSAGE_DATA_SIZE_IN_NO_HASH_CASE (CRYS_RSA_MODULE_ERROR_BASE+0x58UL)
/*! Illegal message size. */
#define CRYS_RSA_INVALID_MESSAGE_DATA_SIZE_IN_SSL_CASE     (CRYS_RSA_MODULE_ERROR_BASE+0x59UL)
/*! PKCS#1 Ver 1.5 verify hash input inconsistent with hash mode derived from signature. */
#define CRYS_RSA_PKCS15_VERIFY_BER_ENCODING_HASH_TYPE      (CRYS_RSA_MODULE_ERROR_BASE+0x60UL)
/*! Illegal DER hash mode */
#define CRYS_RSA_GET_DER_HASH_MODE_ILLEGAL                 (CRYS_RSA_MODULE_ERROR_BASE+0x61UL)

/****************************************************************************************
 * PKCS#1 VERSION 2.1 ERRORS
 ****************************************************************************************/
/*! Illegal salt length. */
#define CRYS_RSA_PSS_ENCODING_MODULUS_HASH_SALT_LENGTHS_ERROR  (CRYS_RSA_MODULE_ERROR_BASE+0x80UL)
/*! Illegal MGF mask. */
#define CRYS_RSA_BASE_MGF_MASK_TOO_LONG                   (CRYS_RSA_MODULE_ERROR_BASE+0x81UL)
/*! PSS verification failed. */
#define CRYS_RSA_ERROR_PSS_INCONSISTENT_VERIFY            (CRYS_RSA_MODULE_ERROR_BASE+0x82UL)
/*! OAEP message too long. */
#define CRYS_RSA_OAEP_VER21_MESSAGE_TOO_LONG              (CRYS_RSA_MODULE_ERROR_BASE+0x83UL)
/*! OAEP error in decrypted block parsing. */
#define CRYS_RSA_ERROR_IN_DECRYPTED_BLOCK_PARSING         (CRYS_RSA_MODULE_ERROR_BASE+0x84UL)
/*! OAEP decoding error. */
#define CRYS_RSA_OAEP_DECODE_ERROR                        (CRYS_RSA_MODULE_ERROR_BASE+0x85UL)
/*! Error in decrypted data size. */
#define CRYS_RSA_15_ERROR_IN_DECRYPTED_DATA_SIZE          (CRYS_RSA_MODULE_ERROR_BASE+0x86UL)
/*! Error in decrypted data. */
#define CRYS_RSA_15_ERROR_IN_DECRYPTED_DATA               (CRYS_RSA_MODULE_ERROR_BASE+0x87UL)
/*! Illegal L pointer. */
#define CRYS_RSA_OAEP_L_POINTER_ERROR                     (CRYS_RSA_MODULE_ERROR_BASE+0x88UL)
/*! Illegal output size. */
#define CRYS_RSA_DECRYPT_INVALID_OUTPUT_SIZE              (CRYS_RSA_MODULE_ERROR_BASE+0x89UL)
/*! Illegal output size pointer. */
#define CRYS_RSA_DECRYPT_OUTPUT_SIZE_POINTER_ERROR        (CRYS_RSA_MODULE_ERROR_BASE+0x8AUL)
/*! Illegal parameters. */
#define CRYS_RSA_ILLEGAL_PARAMS_ACCORDING_TO_PRIV_ERROR   (CRYS_RSA_MODULE_ERROR_BASE + 0x93UL)
/*! RSA is not supported. */
#define CRYS_RSA_IS_NOT_SUPPORTED                         (CRYS_RSA_MODULE_ERROR_BASE+0xFFUL)


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


