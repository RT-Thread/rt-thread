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


#ifndef CRYS_ERROR_H
#define CRYS_ERROR_H

#include "ssi_pal_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*! @file
@brief This module defines the error return code types and the numbering spaces of the error codes
for each module of the layers listed below.
@defgroup crys_error CryptoCell general base error codes
@{
@ingroup cryptocell_api
*/

/*! The definitions of the error number space used for the different modules */

/* ........... Error base numeric mapping definitions ................... */
/* ----------------------------------------------------------------------- */

 /*! CRYS error base number. */
#define CRYS_ERROR_BASE          0x00F00000UL

/*! Error range number assigned for each layer. */
#define CRYS_ERROR_LAYER_RANGE   0x00010000UL

/*! Error range number assigned to each module on its specified layer. */
#define CRYS_ERROR_MODULE_RANGE  0x00000100UL

/* Defines the layer index for the error mapping. */
/*! CRYS error layer index. */
#define CRYS_LAYER_ERROR_IDX     0x00UL
/*! Low level functions error layer index. */
#define LLF_LAYER_ERROR_IDX      0x01UL
/*! Generic error layer index. */
#define GENERIC_ERROR_IDX        0x05UL

/* Defines the module index for error mapping */
/*! AES error index.*/
#define AES_ERROR_IDX            0x00UL
/*! DES error index.*/
#define DES_ERROR_IDX            0x01UL
/*! HASH error index.*/
#define HASH_ERROR_IDX           0x02UL
/*! HMAC error index.*/
#define HMAC_ERROR_IDX           0x03UL
/*! RSA error index.*/
#define RSA_ERROR_IDX            0x04UL
/*! DH error index.*/
#define DH_ERROR_IDX             0x05UL

/*! ECPKI error index.*/
#define ECPKI_ERROR_IDX          0x08UL
/*! RND error index.*/
#define RND_ERROR_IDX            0x0CUL
/*! Common error index.*/
#define COMMON_ERROR_IDX         0x0DUL
/*! KDF error index.*/
#define KDF_ERROR_IDX            0x11UL
/*! HKDF error index.*/
#define HKDF_ERROR_IDX           0x12UL
/*! AESCCM error index.*/
#define AESCCM_ERROR_IDX         0x15UL
/*! FIPS error index.*/
#define FIPS_ERROR_IDX           0x17UL

/*! PKA error index.*/
#define PKA_MODULE_ERROR_IDX     0x21UL
/*! CHACHA error index.*/
#define CHACHA_ERROR_IDX         0x22UL
/*! EC montgomery and edwards error index.*/
#define EC_MONT_EDW_ERROR_IDX    0x23UL
/*! CHACHA POLY error index.*/
#define CHACHA_POLY_ERROR_IDX    0x24UL
/*! POLY error index.*/
#define POLY_ERROR_IDX           0x25UL
/*! SRP error index.*/
#define SRP_ERROR_IDX            0x26UL



/* .......... defining the error spaces for each module on each layer ........... */
/* ------------------------------------------------------------------------------ */

/*! AES module error base address - 0x00F00000. */
#define CRYS_AES_MODULE_ERROR_BASE  (CRYS_ERROR_BASE + \
                                     (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                     (CRYS_ERROR_MODULE_RANGE * AES_ERROR_IDX ) )

/*! DES module error base address - 0x00F00100. */
#define CRYS_DES_MODULE_ERROR_BASE  (CRYS_ERROR_BASE + \
                                     (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                     (CRYS_ERROR_MODULE_RANGE * DES_ERROR_IDX ) )

/*! HASH module error base address - 0x00F00200. */
#define CRYS_HASH_MODULE_ERROR_BASE (CRYS_ERROR_BASE + \
                                     (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                     (CRYS_ERROR_MODULE_RANGE * HASH_ERROR_IDX ) )

/*! HMAC module error base address - 0x00F00300. */
#define CRYS_HMAC_MODULE_ERROR_BASE (CRYS_ERROR_BASE + \
                                     (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                     (CRYS_ERROR_MODULE_RANGE * HMAC_ERROR_IDX ) )

/*! RSA module error base address - 0x00F00400. */
#define CRYS_RSA_MODULE_ERROR_BASE (CRYS_ERROR_BASE + \
                                   (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                   (CRYS_ERROR_MODULE_RANGE * RSA_ERROR_IDX ) )

/*! DH module error base address - 0x00F00500. */
#define CRYS_DH_MODULE_ERROR_BASE  (CRYS_ERROR_BASE + \
                                   (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                   (CRYS_ERROR_MODULE_RANGE * DH_ERROR_IDX ) )

/*! ECPKI module error base address - 0x00F00800. */
#define CRYS_ECPKI_MODULE_ERROR_BASE (CRYS_ERROR_BASE + \
                                     (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                     (CRYS_ERROR_MODULE_RANGE * ECPKI_ERROR_IDX ) )

/*! Low level ECPKI module error base address -  0x00F10800. */
#define LLF_ECPKI_MODULE_ERROR_BASE  (CRYS_ERROR_BASE + \
                                     (CRYS_ERROR_LAYER_RANGE * LLF_LAYER_ERROR_IDX) + \
                                     (CRYS_ERROR_MODULE_RANGE * ECPKI_ERROR_IDX ) )

/*! RND module error base address - 0x00F00C00. */
#define CRYS_RND_MODULE_ERROR_BASE   (CRYS_ERROR_BASE + \
                                     (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                     (CRYS_ERROR_MODULE_RANGE * RND_ERROR_IDX ) )

/*! Low level RND module error base address -  0x00F10C00. */
#define LLF_RND_MODULE_ERROR_BASE    (CRYS_ERROR_BASE + \
                                     (CRYS_ERROR_LAYER_RANGE * LLF_LAYER_ERROR_IDX) + \
                                     (CRYS_ERROR_MODULE_RANGE * RND_ERROR_IDX ) )

/*! COMMMON module error base address - 0x00F00D00. */
#define CRYS_COMMON_MODULE_ERROR_BASE (CRYS_ERROR_BASE + \
                                     (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                     (CRYS_ERROR_MODULE_RANGE * COMMON_ERROR_IDX ) )

/*! KDF module error base address - 0x00F01100. */
#define CRYS_KDF_MODULE_ERROR_BASE (CRYS_ERROR_BASE + \
                                  (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                  (CRYS_ERROR_MODULE_RANGE * KDF_ERROR_IDX ) )

/*! HKDF module error base address - 0x00F01100. */
#define CRYS_HKDF_MODULE_ERROR_BASE (CRYS_ERROR_BASE + \
                                  (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                  (CRYS_ERROR_MODULE_RANGE * HKDF_ERROR_IDX ) )

/*! AESCCM module error base address - 0x00F01500. */
#define CRYS_AESCCM_MODULE_ERROR_BASE  (CRYS_ERROR_BASE + \
                                       (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                       (CRYS_ERROR_MODULE_RANGE * AESCCM_ERROR_IDX ) )

/*! FIPS module error base address - 0x00F01700. */
#define CRYS_FIPS_MODULE_ERROR_BASE  (CRYS_ERROR_BASE + \
                                       (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                       (CRYS_ERROR_MODULE_RANGE * FIPS_ERROR_IDX ) )

/*! PKA module error base address - 0x00F02100. */
#define PKA_MODULE_ERROR_BASE             (CRYS_ERROR_BASE + \
                                           (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                           (CRYS_ERROR_MODULE_RANGE * PKA_MODULE_ERROR_IDX ) )

/*! CHACHA module error base address - 0x00F02200. */
#define CRYS_CHACHA_MODULE_ERROR_BASE  (CRYS_ERROR_BASE + \
                                           (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                           (CRYS_ERROR_MODULE_RANGE * CHACHA_ERROR_IDX ) )
/*! CHACHA POLY module error base address - 0x00F02400. */
#define CRYS_CHACHA_POLY_MODULE_ERROR_BASE  (CRYS_ERROR_BASE + \
                                           (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                           (CRYS_ERROR_MODULE_RANGE * CHACHA_POLY_ERROR_IDX ) )
/*! POLY module error base address - 0x00F02500. */
#define CRYS_POLY_MODULE_ERROR_BASE  (CRYS_ERROR_BASE + \
                                           (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                           (CRYS_ERROR_MODULE_RANGE * POLY_ERROR_IDX ) )

/*! SRP module error base address - 0x00F02600. */
#define CRYS_SRP_MODULE_ERROR_BASE (CRYS_ERROR_BASE + \
                                           (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                           (CRYS_ERROR_MODULE_RANGE * SRP_ERROR_IDX ) )


/*! EC MONT_EDW module error base address - 0x00F02300.  */
#define CRYS_EC_MONT_EDW_MODULE_ERROR_BASE (CRYS_ERROR_BASE + \
                                           (CRYS_ERROR_LAYER_RANGE * CRYS_LAYER_ERROR_IDX) + \
                                           (CRYS_ERROR_MODULE_RANGE * EC_MONT_EDW_ERROR_IDX ) )


/*! User generic error base address - 0x00F50000 */
#define GENERIC_ERROR_BASE ( CRYS_ERROR_BASE + (CRYS_ERROR_LAYER_RANGE * GENERIC_ERROR_IDX) )
/*! CRYS fatal error. */
#define CRYS_FATAL_ERROR            (GENERIC_ERROR_BASE + 0x00UL)
/*! CRYS out of resources error. */
#define CRYS_OUT_OF_RESOURCE_ERROR      (GENERIC_ERROR_BASE + 0x01UL)
/*! CRYS illegal resource value error. */
#define CRYS_ILLEGAL_RESOURCE_VAL_ERROR     (GENERIC_ERROR_BASE + 0x02UL)



/* ............ The OK (success) definition ....................... */
/*! Success defintion. */
#define CRYS_OK 0

/*! MACRO that defines crys return value. */
#define SASI_CRYS_RETURN_ERROR(retCode, retcodeInfo, funcHandler) \
    ((retCode) == 0 ? CRYS_OK : funcHandler(retCode, retcodeInfo))

/************************ Enums ********************************/


/************************ Typedefs  ****************************/

/*! The typedef definition of all of the error codes that are returned from the CRYS functions */
typedef uint32_t CRYSError_t;

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




