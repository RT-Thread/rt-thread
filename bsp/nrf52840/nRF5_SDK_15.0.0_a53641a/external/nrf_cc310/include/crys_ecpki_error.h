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



#ifndef CRYS_ECPKI_ERROR_H
#define CRYS_ECPKI_ERROR_H


/*!
@file
@brief This module contains the definitions of the CRYS ECPKI errors.
@defgroup crys_ecpki_error CryptoCell ECC specific errors
@{
@ingroup cryptocell_ecpki
*/

#include "crys_error.h"

#ifdef __cplusplus
extern "C"
{
#endif


/************************ Defines ******************************/

/* CRYS_ECPKI_MODULE_ERROR_BASE = 0x00F00800  */

/*********************************************************************************************
 * CRYS ECPKI MODULE ERRORS                                                                  *
 *********************************************************************************************/
/*! Illegal domain ID. */
#define CRYS_ECPKI_ILLEGAL_DOMAIN_ID_ERROR                  (CRYS_ECPKI_MODULE_ERROR_BASE + 0x1UL)
/*! Illegal domain pointer. */
#define CRYS_ECPKI_DOMAIN_PTR_ERROR             (CRYS_ECPKI_MODULE_ERROR_BASE + 0x2UL)
/* The CRYS ECPKI GEN KEY PAIR module errors */
/*! Illegal private key pointer. */
#define CRYS_ECPKI_GEN_KEY_INVALID_PRIVATE_KEY_PTR_ERROR        (CRYS_ECPKI_MODULE_ERROR_BASE + 0x3UL)
/*! Illegal public key pointer. */
#define CRYS_ECPKI_GEN_KEY_INVALID_PUBLIC_KEY_PTR_ERROR         (CRYS_ECPKI_MODULE_ERROR_BASE + 0x4UL)
/*! Illegal temporary buffer pointer. */
#define CRYS_ECPKI_GEN_KEY_INVALID_TEMP_DATA_PTR_ERROR          (CRYS_ECPKI_MODULE_ERROR_BASE + 0x5UL)
/*! Illegal RND context pointer. */
#define CRYS_ECPKI_RND_CONTEXT_PTR_ERROR            (CRYS_ECPKI_MODULE_ERROR_BASE + 0x6UL)

/************************************************************************************************************
* The CRYS ECPKI BUILD KEYS MODULE ERRORS                                                                   *
*************************************************************************************************************/
/*! Illegal compression mode. */
#define CRYS_ECPKI_BUILD_KEY_INVALID_COMPRESSION_MODE_ERROR     (CRYS_ECPKI_MODULE_ERROR_BASE + 0x07UL)
/*! Illegal domain ID. */
#define CRYS_ECPKI_BUILD_KEY_ILLEGAL_DOMAIN_ID_ERROR            (CRYS_ECPKI_MODULE_ERROR_BASE + 0x08UL)
/*! Illegal private key pointer. */
#define CRYS_ECPKI_BUILD_KEY_INVALID_PRIV_KEY_IN_PTR_ERROR      (CRYS_ECPKI_MODULE_ERROR_BASE + 0x09UL)
/*! Illegal private key structure pointer. */
#define CRYS_ECPKI_BUILD_KEY_INVALID_USER_PRIV_KEY_PTR_ERROR    (CRYS_ECPKI_MODULE_ERROR_BASE + 0x0AUL)
/*! Illegal private key size. */
#define CRYS_ECPKI_BUILD_KEY_INVALID_PRIV_KEY_SIZE_ERROR        (CRYS_ECPKI_MODULE_ERROR_BASE + 0x0BUL)
/*! Illegal private key data. */
#define CRYS_ECPKI_BUILD_KEY_INVALID_PRIV_KEY_DATA_ERROR        (CRYS_ECPKI_MODULE_ERROR_BASE + 0x0CUL)
/*! Illegal public key pointer. */
#define CRYS_ECPKI_BUILD_KEY_INVALID_PUBL_KEY_IN_PTR_ERROR      (CRYS_ECPKI_MODULE_ERROR_BASE + 0x0DUL)
/*! Illegal public key structure pointer. */
#define CRYS_ECPKI_BUILD_KEY_INVALID_USER_PUBL_KEY_PTR_ERROR    (CRYS_ECPKI_MODULE_ERROR_BASE + 0x0EUL)
/*! Illegal public key size. */
#define CRYS_ECPKI_BUILD_KEY_INVALID_PUBL_KEY_SIZE_ERROR        (CRYS_ECPKI_MODULE_ERROR_BASE + 0x0FUL)
/*! Illegal public key data. */
#define CRYS_ECPKI_BUILD_KEY_INVALID_PUBL_KEY_DATA_ERROR        (CRYS_ECPKI_MODULE_ERROR_BASE + 0x10UL)
/*! Illegal EC build check mode option. */
#define CRYS_ECPKI_BUILD_KEY_INVALID_CHECK_MODE_ERROR           (CRYS_ECPKI_MODULE_ERROR_BASE + 0x11UL)
/*! Illegal temporary buffer pointer. */
#define CRYS_ECPKI_BUILD_KEY_INVALID_TEMP_BUFF_PTR_ERROR        (CRYS_ECPKI_MODULE_ERROR_BASE + 0x12UL)

/* The CRYS ECPKI EXPORT PUBLIC KEY MODULE ERRORS */
/*! Illegal public key structure pointer. */
#define CRYS_ECPKI_EXPORT_PUBL_KEY_INVALID_USER_PUBL_KEY_PTR_ERROR      (CRYS_ECPKI_MODULE_ERROR_BASE + 0x14UL)
/*! Illegal public key compression mode. */
#define CRYS_ECPKI_EXPORT_PUBL_KEY_ILLEGAL_COMPRESSION_MODE_ERROR       (CRYS_ECPKI_MODULE_ERROR_BASE + 0x15UL)
/*! Illegal output public key pointer. */
#define CRYS_ECPKI_EXPORT_PUBL_KEY_INVALID_EXTERN_PUBL_KEY_PTR_ERROR    (CRYS_ECPKI_MODULE_ERROR_BASE + 0x16UL)
/*! Illegal output public key size pointer. */
#define CRYS_ECPKI_EXPORT_PUBL_KEY_INVALID_PUBL_KEY_SIZE_PTR_ERROR      (CRYS_ECPKI_MODULE_ERROR_BASE + 0x17UL)
/*! Illegal output public key size. */
#define CRYS_ECPKI_EXPORT_PUBL_KEY_INVALID_PUBL_KEY_SIZE_ERROR          (CRYS_ECPKI_MODULE_ERROR_BASE + 0x18UL)
/*! Illegal domain ID. */
#define CRYS_ECPKI_EXPORT_PUBL_KEY_ILLEGAL_DOMAIN_ID_ERROR              (CRYS_ECPKI_MODULE_ERROR_BASE + 0x19UL)
/*! Validation of public key failed. */
#define CRYS_ECPKI_EXPORT_PUBL_KEY_ILLEGAL_VALIDATION_TAG_ERROR         (CRYS_ECPKI_MODULE_ERROR_BASE + 0x1AUL)
/*! Validation of public key failed. */
#define CRYS_ECPKI_EXPORT_PUBL_KEY_INVALID_PUBL_KEY_DATA_ERROR          (CRYS_ECPKI_MODULE_ERROR_BASE + 0x1BUL)

/* The CRYS ECPKI EXPORT PRIVATE KEY MODULE ERRORS */
/*! Illegal private key structure pointer. */
#define CRYS_ECPKI_EXPORT_PRIV_KEY_INVALID_USER_PRIV_KEY_PTR_ERROR      (CRYS_ECPKI_MODULE_ERROR_BASE + 0xC0UL)
/*! Illegal output private key pointer. */
#define CRYS_ECPKI_EXPORT_PRIV_KEY_INVALID_EXTERN_PRIV_KEY_PTR_ERROR    (CRYS_ECPKI_MODULE_ERROR_BASE + 0xC1UL)
/*! Validation of private key failed. */
#define CRYS_ECPKI_EXPORT_PRIV_KEY_ILLEGAL_VALIDATION_TAG_ERROR         (CRYS_ECPKI_MODULE_ERROR_BASE + 0xC2UL)
/*! Illegal output private key size pointer. */
#define CRYS_ECPKI_EXPORT_PRIV_KEY_INVALID_PRIV_KEY_SIZE_PTR_ERROR      (CRYS_ECPKI_MODULE_ERROR_BASE + 0xC3UL)
/*! Illegal output private key size. */
#define CRYS_ECPKI_EXPORT_PRIV_KEY_INVALID_PRIV_KEY_SIZE_ERROR          (CRYS_ECPKI_MODULE_ERROR_BASE + 0xC4UL)
/*! Validation of private key failed. */
#define CRYS_ECPKI_EXPORT_PRIV_KEY_INVALID_PRIV_KEY_DATA_ERROR          (CRYS_ECPKI_MODULE_ERROR_BASE + 0xC5UL)

/* The CRYS ECPKI BUILD ECC DOMAIN ERRORS */
/*! Illegal domain ID. */
#define CRYS_ECPKI_BUILD_DOMAIN_ID_IS_NOT_VALID_ERROR            (CRYS_ECPKI_MODULE_ERROR_BASE + 0x20UL)
/*! Illegal domain ID pointer. */
#define CRYS_ECPKI_BUILD_DOMAIN_DOMAIN_PTR_ERROR                 (CRYS_ECPKI_MODULE_ERROR_BASE + 0x21UL)
/*! Illegal domain parameter pointer. */
#define CRYS_ECPKI_BUILD_DOMAIN_EC_PARAMETR_PTR_ERROR            (CRYS_ECPKI_MODULE_ERROR_BASE + 0x22UL)
/*! Illegal domain parameter size. */
#define CRYS_ECPKI_BUILD_DOMAIN_EC_PARAMETR_SIZE_ERROR           (CRYS_ECPKI_MODULE_ERROR_BASE + 0x23UL)
/*! Illegal domain cofactor parameters. */
#define CRYS_ECPKI_BUILD_DOMAIN_COFACTOR_PARAMS_ERROR            (CRYS_ECPKI_MODULE_ERROR_BASE + 0x24UL)
/*! Insufficient strength. */
#define CRYS_ECPKI_BUILD_DOMAIN_SECURITY_STRENGTH_ERROR          (CRYS_ECPKI_MODULE_ERROR_BASE + 0x25UL)
/*! SCA resistance error. */
#define CRYS_ECPKI_BUILD_SCA_RESIST_ILLEGAL_MODE_ERROR           (CRYS_ECPKI_MODULE_ERROR_BASE + 0x26UL)


/*! Internal PKI error */
#define CRYS_ECPKI_PKI_INTERNAL_ERROR                            (CRYS_ECPKI_MODULE_ERROR_BASE + 0x30UL)

/************************************************************************************************************
 * CRYS EC DIFFIE-HELLMAN MODULE ERRORS
*************************************************************************************************************/
/* The CRYS EC SVDP_DH Function errors */
/*! Illegal partner's public key pointer. */
#define CRYS_ECDH_SVDP_DH_INVALID_PARTNER_PUBL_KEY_PTR_ERROR                  (CRYS_ECPKI_MODULE_ERROR_BASE + 0x31UL)
/*! Partner's public key validation failed. */
#define CRYS_ECDH_SVDP_DH_PARTNER_PUBL_KEY_VALID_TAG_ERROR                (CRYS_ECPKI_MODULE_ERROR_BASE + 0x32UL)
/*! Illegal user private key pointer. */
#define CRYS_ECDH_SVDP_DH_INVALID_USER_PRIV_KEY_PTR_ERROR             (CRYS_ECPKI_MODULE_ERROR_BASE + 0x33UL)
/*! Private key validation failed. */
#define CRYS_ECDH_SVDP_DH_USER_PRIV_KEY_VALID_TAG_ERROR                   (CRYS_ECPKI_MODULE_ERROR_BASE + 0x34UL)
/*! Illegal shared secret pointer. */
#define CRYS_ECDH_SVDP_DH_INVALID_SHARED_SECRET_VALUE_PTR_ERROR               (CRYS_ECPKI_MODULE_ERROR_BASE + 0x35UL)
/*! Illegal temporary buffer pointer. */
#define CRYS_ECDH_SVDP_DH_INVALID_TEMP_DATA_PTR_ERROR                         (CRYS_ECPKI_MODULE_ERROR_BASE + 0x36UL)
/*! Illegal shared secret size pointer. */
#define CRYS_ECDH_SVDP_DH_INVALID_SHARED_SECRET_VALUE_SIZE_PTR_ERROR          (CRYS_ECPKI_MODULE_ERROR_BASE + 0x37UL)
/*! Illegal shared secret size. */
#define CRYS_ECDH_SVDP_DH_INVALID_SHARED_SECRET_VALUE_SIZE_ERROR              (CRYS_ECPKI_MODULE_ERROR_BASE + 0x38UL)
/*! Illegal domain ID. */
#define CRYS_ECDH_SVDP_DH_ILLEGAL_DOMAIN_ID_ERROR                             (CRYS_ECPKI_MODULE_ERROR_BASE + 0x39UL)
/*! Illegal private and public domain ID are different. */
#define CRYS_ECDH_SVDP_DH_NOT_CONCENT_PUBL_AND_PRIV_DOMAIN_ID_ERROR           (CRYS_ECPKI_MODULE_ERROR_BASE + 0x3AUL)


/************************************************************************************************************
 * CRYS ECDSA  MODULE ERRORS
 ************************************************************************************************************/
/* The CRYS ECDSA Signing  errors */
/*! Illegal domain ID. */
#define CRYS_ECDSA_SIGN_INVALID_DOMAIN_ID_ERROR         (CRYS_ECPKI_MODULE_ERROR_BASE + 0x50UL)
/*! Illegal context pointer. */
#define CRYS_ECDSA_SIGN_INVALID_USER_CONTEXT_PTR_ERROR          (CRYS_ECPKI_MODULE_ERROR_BASE + 0x51UL)
/*! Illegal private key pointer. */
#define CRYS_ECDSA_SIGN_INVALID_USER_PRIV_KEY_PTR_ERROR         (CRYS_ECPKI_MODULE_ERROR_BASE + 0x52UL)
/*! Illegal hash operation mode. */
#define CRYS_ECDSA_SIGN_ILLEGAL_HASH_OP_MODE_ERROR              (CRYS_ECPKI_MODULE_ERROR_BASE + 0x53UL)
/*! Illegal data in pointer. */
#define CRYS_ECDSA_SIGN_INVALID_MESSAGE_DATA_IN_PTR_ERROR       (CRYS_ECPKI_MODULE_ERROR_BASE + 0x54UL)
/*! Illegal data in size. */
#define CRYS_ECDSA_SIGN_INVALID_MESSAGE_DATA_IN_SIZE_ERROR      (CRYS_ECPKI_MODULE_ERROR_BASE + 0x55UL)
/*! Context validation failed. */
#define CRYS_ECDSA_SIGN_USER_CONTEXT_VALIDATION_TAG_ERROR       (CRYS_ECPKI_MODULE_ERROR_BASE + 0x57UL)
/*! User's private key validation failed. */
#define CRYS_ECDSA_SIGN_USER_PRIV_KEY_VALIDATION_TAG_ERROR      (CRYS_ECPKI_MODULE_ERROR_BASE + 0x58UL)
/*! Illegal signature pointer. */
#define CRYS_ECDSA_SIGN_INVALID_SIGNATURE_OUT_PTR_ERROR         (CRYS_ECPKI_MODULE_ERROR_BASE + 0x60UL)
/*! Illegal signature size pointer. */
#define CRYS_ECDSA_SIGN_INVALID_SIGNATURE_OUT_SIZE_PTR_ERROR    (CRYS_ECPKI_MODULE_ERROR_BASE + 0x61UL)
/*! Illegal signature size. */
#define CRYS_ECDSA_SIGN_INVALID_SIGNATURE_OUT_SIZE_ERROR        (CRYS_ECPKI_MODULE_ERROR_BASE + 0x62UL)
/*! Ephemeral key error. */
#define CRYS_ECDSA_SIGN_INVALID_IS_EPHEMER_KEY_INTERNAL_ERROR   (CRYS_ECPKI_MODULE_ERROR_BASE + 0x63UL)
/*! Illegal ephemeral key pointer. */
#define CRYS_ECDSA_SIGN_INVALID_EPHEMERAL_KEY_PTR_ERROR         (CRYS_ECPKI_MODULE_ERROR_BASE + 0x64UL)
/*! Illegal RND context pointer. */
#define CRYS_ECDSA_SIGN_INVALID_RND_CONTEXT_PTR_ERROR           (CRYS_ECPKI_MODULE_ERROR_BASE + 0x65UL)
/*! Illegal RND function pointer. */
#define CRYS_ECDSA_SIGN_INVALID_RND_FUNCTION_PTR_ERROR          (CRYS_ECPKI_MODULE_ERROR_BASE + 0x66UL)
/*! Signature calculation failed. */
#define CRYS_ECDSA_SIGN_SIGNING_ERROR                           (CRYS_ECPKI_MODULE_ERROR_BASE + 0x67UL)

/* The CRYS ECDSA Verifying  errors */
/*! Illegal domain ID. */
#define CRYS_ECDSA_VERIFY_INVALID_DOMAIN_ID_ERROR       (CRYS_ECPKI_MODULE_ERROR_BASE + 0x70UL)
/*! Illegal user's context pointer. */
#define CRYS_ECDSA_VERIFY_INVALID_USER_CONTEXT_PTR_ERROR    (CRYS_ECPKI_MODULE_ERROR_BASE + 0x71UL)
/*! Illegal public key pointer. */
#define CRYS_ECDSA_VERIFY_INVALID_SIGNER_PUBL_KEY_PTR_ERROR     (CRYS_ECPKI_MODULE_ERROR_BASE + 0x72UL)
/*! Illegal hash operation mode. */
#define CRYS_ECDSA_VERIFY_ILLEGAL_HASH_OP_MODE_ERROR            (CRYS_ECPKI_MODULE_ERROR_BASE + 0x73UL)
/*! Illegal signature pointer. */
#define CRYS_ECDSA_VERIFY_INVALID_SIGNATURE_IN_PTR_ERROR        (CRYS_ECPKI_MODULE_ERROR_BASE + 0x76UL)
/*! Illegal signature size. */
#define CRYS_ECDSA_VERIFY_INVALID_SIGNATURE_SIZE_ERROR      (CRYS_ECPKI_MODULE_ERROR_BASE + 0x77UL)
/*! Illegal data in pointer. */
#define CRYS_ECDSA_VERIFY_INVALID_MESSAGE_DATA_IN_PTR_ERROR     (CRYS_ECPKI_MODULE_ERROR_BASE + 0x80UL)
/*! Illegal data in size. */
#define CRYS_ECDSA_VERIFY_INVALID_MESSAGE_DATA_IN_SIZE_ERROR    (CRYS_ECPKI_MODULE_ERROR_BASE + 0x81UL)
/*! Context validation failed. */
#define CRYS_ECDSA_VERIFY_USER_CONTEXT_VALIDATION_TAG_ERROR     (CRYS_ECPKI_MODULE_ERROR_BASE + 0x82UL)
/*! public key validation failed. */
#define CRYS_ECDSA_VERIFY_SIGNER_PUBL_KEY_VALIDATION_TAG_ERROR  (CRYS_ECPKI_MODULE_ERROR_BASE + 0x83UL)
/*! Verification failed. */
#define CRYS_ECDSA_VERIFY_INCONSISTENT_VERIFY_ERROR             (CRYS_ECPKI_MODULE_ERROR_BASE + 0x84UL)

/*! Illegal parameters. */
#define CRYS_ECC_ILLEGAL_PARAMS_ACCORDING_TO_PRIV_ERROR              (CRYS_ECPKI_MODULE_ERROR_BASE + 0xD3UL)
/*! Illegal hash mode. */
#define CRYS_ECC_ILLEGAL_HASH_MODE_ERROR                         (CRYS_ECPKI_MODULE_ERROR_BASE + 0xE0UL)


/************************************************************************************************************
 * CRYS ECPKI MODULE  COMMON ERRORS
*************************************************************************************************************/
/*! Illegal RND function pointer. */
#define CRYS_ECPKI_INVALID_RND_FUNC_PTR_ERROR                   (CRYS_ECPKI_MODULE_ERROR_BASE + 0x90UL)
/*! Illegal RND context pointer. */
#define CRYS_ECPKI_INVALID_RND_CTX_PTR_ERROR                    (CRYS_ECPKI_MODULE_ERROR_BASE + 0x91UL)
/*! Illegal domain ID. */
#define CRYS_ECPKI_INVALID_DOMAIN_ID_ERROR                      (CRYS_ECPKI_MODULE_ERROR_BASE + 0x92UL)
/*! Private key validation failed. */
#define CRYS_ECPKI_INVALID_PRIV_KEY_TAG_ERROR                   (CRYS_ECPKI_MODULE_ERROR_BASE + 0x93UL)
/*! Public key validation failed. */
#define CRYS_ECPKI_INVALID_PUBL_KEY_TAG_ERROR                   (CRYS_ECPKI_MODULE_ERROR_BASE + 0x94UL)
/*! Illegal data in. */
#define CRYS_ECPKI_INVALID_DATA_IN_PASSED_STRUCT_ERROR          (CRYS_ECPKI_MODULE_ERROR_BASE + 0x95UL)

/************************************************************************************************************
 * CRYS ECIES MODULE ERRORS
*************************************************************************************************************/
/*! Illegal public key pointer. */
#define CRYS_ECIES_INVALID_PUBL_KEY_PTR_ERROR                   (CRYS_ECPKI_MODULE_ERROR_BASE + 0xE0UL)
/*! Public key validation failed. */
#define CRYS_ECIES_INVALID_PUBL_KEY_TAG_ERROR           (CRYS_ECPKI_MODULE_ERROR_BASE + 0xE1UL)
/*! Illegal private key pointer. */
#define CRYS_ECIES_INVALID_PRIV_KEY_PTR_ERROR                   (CRYS_ECPKI_MODULE_ERROR_BASE + 0xE2UL)
/*! Private key validation failed. */
#define CRYS_ECIES_INVALID_PRIV_KEY_TAG_ERROR           (CRYS_ECPKI_MODULE_ERROR_BASE + 0xE3UL)
/*! Illegal private key value. */
#define CRYS_ECIES_INVALID_PRIV_KEY_VALUE_ERROR         (CRYS_ECPKI_MODULE_ERROR_BASE + 0xE4UL)
/*! Illegal KDF derivation mode. */
#define CRYS_ECIES_INVALID_KDF_DERIV_MODE_ERROR             (CRYS_ECPKI_MODULE_ERROR_BASE + 0xE5UL)
/*! Illegal KDF hash mode. */
#define CRYS_ECIES_INVALID_KDF_HASH_MODE_ERROR          (CRYS_ECPKI_MODULE_ERROR_BASE + 0xE6UL)
/*! Illegal secret key pointer. */
#define CRYS_ECIES_INVALID_SECRET_KEY_PTR_ERROR         (CRYS_ECPKI_MODULE_ERROR_BASE + 0xE7UL)
/*! Illegal secret key size. */
#define CRYS_ECIES_INVALID_SECRET_KEY_SIZE_ERROR        (CRYS_ECPKI_MODULE_ERROR_BASE + 0xE8UL)
/*! Illegal cipher data pointer. */
#define CRYS_ECIES_INVALID_CIPHER_DATA_PTR_ERROR        (CRYS_ECPKI_MODULE_ERROR_BASE + 0xE9UL)
/*! Illegal cipher data size pointer. */
#define CRYS_ECIES_INVALID_CIPHER_DATA_SIZE_PTR_ERROR       (CRYS_ECPKI_MODULE_ERROR_BASE + 0xEAUL)
/*! Illegal cipher data size. */
#define CRYS_ECIES_INVALID_CIPHER_DATA_SIZE_ERROR       (CRYS_ECPKI_MODULE_ERROR_BASE + 0xEBUL)
/*! Illegal temporary buffer pointer. */
#define CRYS_ECIES_INVALID_TEMP_DATA_PTR_ERROR          (CRYS_ECPKI_MODULE_ERROR_BASE + 0xECUL)
/*! Illegal ephemeral key pointer */
#define CRYS_ECIES_INVALID_EPHEM_KEY_PAIR_PTR_ERROR             (CRYS_ECPKI_MODULE_ERROR_BASE + 0xEDUL)

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


