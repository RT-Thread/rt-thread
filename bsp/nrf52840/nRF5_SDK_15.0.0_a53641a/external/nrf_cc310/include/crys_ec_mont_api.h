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



#ifndef CRYS_ECMONT_API_H
#define CRYS_ECMONT_API_H

#include "ssi_pal_types.h"
#include "crys_rnd.h"
#include "crys_pka_defs_hw.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
@file
@brief This file contains the CRYS APIs used for EC MONT (Montgomery Curve25519) algorithms.
@defgroup crys_ec_mont CryptoCell EC Montgomery APIs
@{
@ingroup cryptocell_ec


\note  Implemented algorithms according to Montgomery elliptic curves cryptography,
       developed by Daniel J.Bernstein etc.
*/

/*! EC Montgomery curve25519 modulus size in bits, words and bytes  */
/*! EC Montgomery modulus size in bits. */
#define CRYS_ECMONT_MOD_SIZE_IN_BITS  255U
/*! EC Montgomery modulus size in words. */
#define CRYS_ECMONT_MOD_SIZE_IN_32BIT_WORDS    ((CRYS_ECMONT_MOD_SIZE_IN_BITS + SASI_BITS_IN_32BIT_WORD - 1) / SASI_BITS_IN_32BIT_WORD)
/*! EC Montgomery modulus size in bytes. */
#define CRYS_ECMONT_MOD_SIZE_IN_BYTES          ((CRYS_ECMONT_MOD_SIZE_IN_BITS + SASI_BITS_IN_32BIT_WORD - 1) / sizeof(uint32_t))

/*! Constant sizes of special EC_MONT buffers and arrays  */
/*! EC Montgomery scalar size in bytes. */
#define CRYS_ECMONT_SCALARBYTES     (CRYS_ECMONT_MOD_SIZE_IN_32BIT_WORDS * SASI_32BIT_WORD_SIZE)
/*! EC Montgomery scalar multiplication size in bytes. */
#define CRYS_ECMONT_SCALARMULTBYTES (CRYS_ECMONT_MOD_SIZE_IN_32BIT_WORDS * SASI_32BIT_WORD_SIZE)
/*! EC Montgomery scalar seed size in bytes. */
#define CRYS_ECMONT_SEEDBYTES       (CRYS_ECMONT_MOD_SIZE_IN_32BIT_WORDS * SASI_32BIT_WORD_SIZE)

/*! EC Montgomery domains ID-s enumerator. */
typedef enum {
        CRYS_ECMONT_DOMAIN_CURVE_25519,  /*!< EC Curve25519. */
    /*! EC Montgomery last domain. */
        CRYS_ECMONT_DOMAIN_OFF_MODE,
    /*! Reserved. */
        CRYS_ECMONT_DOMAIN_LAST = 0x7FFFFFFF
}CRYS_ECMONT_DomainId_t;


/*! EC_MONT scalar mult temp buffer type definition */
typedef struct {
    /*! Internal temporary buffer. */
        uint32_t ecMontScalarMultTempBuff[CRYS_EC_MONT_TEMP_BUFF_SIZE_IN_32BIT_WORDS]; // set needed
} CRYS_ECMONT_ScalrMultTempBuff_t;

/*! EC_MONT temp buffer type definition */
typedef struct {
        /* Don't change sequence order of the buffers */
    /*! Internal temporary buffer. */
        uint32_t ecMontScalar[CRYS_EC_MONT_EDW_MODULUS_MAX_SIZE_IN_WORDS];
    /*! Internal temporary buffer. */
        uint32_t ecMontResPoint[CRYS_EC_MONT_EDW_MODULUS_MAX_SIZE_IN_WORDS];
    /*! Internal temporary buffer. */
        uint32_t ecMontInPoint[CRYS_EC_MONT_EDW_MODULUS_MAX_SIZE_IN_WORDS];
    /*! Internal temporary buffer. */
        CRYS_ECMONT_ScalrMultTempBuff_t  ecMontScalrMultTempBuff; // if needed
} CRYS_ECMONT_TempBuff_t;


/*********************************************************************/
/*!
@brief The function performs EC Montgomery (Curve25519) scalar multiplication:
       resPoint = scalar * point.

@return CRYS_OK on success,
@return A non-zero value on failure as defined crys_ec_mont_edw_error.h.
*/
CIMPORT_C CRYSError_t CRYS_ECMONT_Scalarmult(
                                            uint8_t       *pResPoint,       /*!< [out] Pointer to the public (secret) key. */
                                            size_t        *pResPointSize,   /*!< [in/out] Pointer to the size of the public key in bytes.
                                                                                   In  - the size of the buffer. must be at least EC modulus
                                                                                         size (for curve25519 - 32 bytes).
                                                                                   Out - the actual size. */
                                            const uint8_t *pScalar,         /*!< [in] Pointer to the secret (private) key. */
                                            size_t         scalarSize,      /*!< [in] Pointer to the size of the secret key in bytes;
                                                                                 must be equal to EC order size (for curve25519 - 32 bytes). */
                                            const uint8_t *pInPoint,        /*!< [in] Pointer to the input point (compressed). */
                                            size_t         inPointSize,     /*!< [in] Size of the point - must be equal to CRYS_ECMONT_MOD_SIZE_IN_BYTES. */
                                            CRYS_ECMONT_TempBuff_t *pEcMontTempBuff  /*!< [in] Pointer to temp buffer, for internal use. */);


/*********************************************************************/
/*!
@brief The function performs EC Montgomery (Curve25519) scalar multiplication of base point:
       res = scalar * base_point.

       Note: all byte arrays have LE order of bytes, i.e. LS byte is on left most place.

@return CRYS_OK on success,
@return A non-zero value on failure as defined crys_ec_mont_edw_error.h.
*/
CIMPORT_C CRYSError_t CRYS_ECMONT_ScalarmultBase(
                                                uint8_t       *pResPoint,      /*!< [out] Pointer to the public (secret) key. */
                                                size_t        *pResPointSize,  /*!< [in/out] Pointer to the size of the public key in bytes.
                                                                                      In  - the size of buffer must be at least EC modulus size
                                                                                      (for curve25519 - 32 bytes);
                                                                                      Out - the actual size. */
                                                const uint8_t *pScalar,        /*!< [in] Pointer to the secret (private) key. */
                                                size_t         scalarSize,     /*!< [in] Pointer to the size of the scalar in bytes -
                                                                                    must be equal to EC order size (for curve25519 - 32 bytes). */
                                                CRYS_ECMONT_TempBuff_t *pEcMontTempBuff /*!< [in] Pointer to temp buffer, for internal use. */);


/*******************************************************************/
/*!
@brief The function randomly generates  private and public keys for Montgomery
       Curve25519.


\note <ul id="noteb"><li> All byte arrays are in LE order of bytes, i.e. LS byte is on the left most place.</li>
      <li> LS and MS bits of the Secret key are set according to EC Montgomery scalar mult. algorithm:
                secrKey[0] &= 248; secrKey[31] &= 127; secrKey[31] |= 64;</li></ul>

@return CRYS_OK on success,
@return A non-zero value on failure as defined crys_ec_mont_edw_error.h or crys_rnd_error.h.

*/
CIMPORT_C CRYSError_t CRYS_ECMONT_KeyPair (
                                          uint8_t *pPublKey,                    /*!< [out] Pointer to the public key. */
                                          size_t  *pPublKeySize,                /*!< [in/out] Pointer to the size of the public key in bytes.
                                                                                      In  - the size of the buffer must be at least EC order size
                                                                                            (for curve25519 - 32 bytes);
                                                                                      Out - the actual size. */
                                          uint8_t *pSecrKey,                    /*!< [out] Pointer to the secret key, including. */
                                          size_t  *pSecrKeySize,                /*!< [in/out] Pointer to the size of buffer for the secret key in bytes -
                                                                                     must be at least EC order size (for curve25519 - 32 bytes). */
                                         void   *pRndState,     /*!< [in/out] Pointer to the RND state structure. */
                     SaSiRndGenerateVectWorkFunc_t rndGenerateVectFunc,   /*!< [in] Pointer to the random vector generation function. */
                                          CRYS_ECMONT_TempBuff_t *pEcMontTempBuff /*!< [in] Pointer to the temp buffer, for internal use. */);


/*******************************************************************/
/*!
@brief The function generates private and public keys for Montgomery algorithms.

       The generation performed using given seed.


@return CRYS_OK on success,
@return A non-zero value on failure as defined crys_ec_mont_edw_error.h or crys_hash_error.h.
*/
CIMPORT_C CRYSError_t CRYS_ECMONT_SeedKeyPair (
                                              uint8_t       *pPublKey,       /*!< [out] Pointer to the public (secret) key. */
                                              size_t        *pPublKeySize,   /*!< [in/out] Pointer to the size of the public key in bytes.
                                                                                     In  - the size of buffer must be at least EC order size
                                                                                           (for curve25519 - 32 bytes);
                                                                                     Out - the actual size. */
                                              uint8_t       *pSecrKey,       /*!< [out] Pointer to the secret (private) key. */
                                              size_t        *pSecrKeySize,   /*!< [in/out] Pointer to the size of the secret key in bytes
                                                                                      In  - the size of buffer must be at least EC order size
                                                                                            (for curve25519 - 32 bytes);
                                                                                      Out - the actual size. */
                                              const uint8_t *pSeed,          /*!< [in] Pointer to the given seed - 32 bytes. */
                                              size_t         seedSize,       /*!< [in/] Size of the seed in bytes (must be equal to CRYS_ECMONT_SEEDBYTES). */
                                              CRYS_ECMONT_TempBuff_t *pEcMontTempBuff /*!< [in] Pointer to a temp buffer, for internal use. */);


#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif



