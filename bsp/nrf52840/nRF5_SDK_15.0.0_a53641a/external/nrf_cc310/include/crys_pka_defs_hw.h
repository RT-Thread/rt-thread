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




#ifndef _CRYS_PKA_DEFS_HW_H_
#define _CRYS_PKA_DEFS_HW_H_

#include "ssi_pal_types.h"
#include "ssi_pka_hw_plat_defs.h"

/*!
@defgroup cryptocell_pka CryptoCell PKA group
@{
@ingroup cryptocell_api
@brief This group is the cryptocell PKA root group
@}

@file
@brief The file contains all of the enums and definitions that are used in the PKA related code.
@defgroup crys_pka_defs_hw CryptoCell PKA specific definitions
@{
@ingroup cryptocell_pka
*/


/* The valid key sizes in bits for RSA primitives (exponentiation) */
/*! Maximal RSA modulus size */
#define CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS ((CRYS_RSA_MAX_VALID_KEY_SIZE_VALUE_IN_BITS + SASI_PKA_WORD_SIZE_IN_BITS) / SASI_BITS_IN_32BIT_WORD )
/*! Maximal EC modulus size */
#define CRYS_ECPKI_MODUL_MAX_LENGTH_IN_BITS   521

/*! size of buffers for Barrett modulus tag NP, used in PKI algorithms. */
#define CRYS_PKA_BARRETT_MOD_TAG_BUFF_SIZE_IN_WORDS 5
/*! size of buffers for Barrett modulus tag NP, used in ECC. */
#define CRYS_PKA_ECPKI_BARRETT_MOD_TAG_BUFF_SIZE_IN_WORDS  CRYS_PKA_BARRETT_MOD_TAG_BUFF_SIZE_IN_WORDS
/*! Maximal PKA modulus size */
#define CRYS_PKA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS
/*! Maximal PKA public key size in words */
#define CRYS_PKA_PUB_KEY_BUFF_SIZE_IN_WORDS (2*CRYS_PKA_BARRETT_MOD_TAG_BUFF_SIZE_IN_WORDS)
/*! Maximal PKA private key size in words */
#define CRYS_PKA_PRIV_KEY_BUFF_SIZE_IN_WORDS (2*CRYS_PKA_BARRETT_MOD_TAG_BUFF_SIZE_IN_WORDS)
/*! Maximal PKA KG buffer size in words */
#define CRYS_PKA_KGDATA_BUFF_SIZE_IN_WORDS   (3*CRYS_PKA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS)


/*! Maximal EC modulus size in words. */
#define CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS  18 /*!< \internal [(CRYS_ECPKI_MODUL_MAX_LENGTH_IN_BITS + 31)/(sizeof(uint32_t)) + 1] */
/*! Maximal EC order size in words. */
#define CRYS_ECPKI_ORDER_MAX_LENGTH_IN_WORDS  (CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS + 1)
/*! Maximal EC domain size in words. */
#define CRYS_PKA_DOMAIN_BUFF_SIZE_IN_WORDS (2*CRYS_PKA_BARRETT_MOD_TAG_BUFF_SIZE_IN_WORDS)


/*! ECC NAF buffer definitions */
#define COUNT_NAF_WORDS_PER_KEY_WORD  8  /*!< \internal Change according to NAF representation (? 2)*/
/*! Maximal ECC NAF length */
#define CRYS_PKA_ECDSA_NAF_BUFF_MAX_LENGTH_IN_WORDS (COUNT_NAF_WORDS_PER_KEY_WORD*CRYS_ECPKI_ORDER_MAX_LENGTH_IN_WORDS + 1)

#ifndef SSI_SUPPORT_ECC_SCA_SW_PROTECT
/* on fast SCA non protected mode required additional buffers for NAF key */
/*! Scalar Buffer size in words */
#define CRYS_PKA_ECPKI_SCALAR_MUL_BUFF_MAX_LENGTH_IN_WORDS (CRYS_PKA_ECDSA_NAF_BUFF_MAX_LENGTH_IN_WORDS+CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS+2)
#else
/*! Scalar Buffer size in words */
#define CRYS_PKA_ECPKI_SCALAR_MUL_BUFF_MAX_LENGTH_IN_WORDS  1 /*(4*CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS)*/
#endif
/*! ECC temp buffer size in words */
#define CRYS_PKA_ECPKI_BUILD_TMP_BUFF_MAX_LENGTH_IN_WORDS (3*CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS+CRYS_PKA_ECPKI_SCALAR_MUL_BUFF_MAX_LENGTH_IN_WORDS)
/*! ECC sign temp buffer size in words */
#define CRYS_PKA_ECDSA_SIGN_BUFF_MAX_LENGTH_IN_WORDS (6*CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS+CRYS_PKA_ECPKI_SCALAR_MUL_BUFF_MAX_LENGTH_IN_WORDS)
/*! ECC ecdh temp buffer size in words */
#define CRYS_PKA_ECDH_BUFF_MAX_LENGTH_IN_WORDS (2*CRYS_ECPKI_ORDER_MAX_LENGTH_IN_WORDS + CRYS_PKA_ECPKI_SCALAR_MUL_BUFF_MAX_LENGTH_IN_WORDS)
/*! PKA KG temp buffer size in words */
#define CRYS_PKA_KG_BUFF_MAX_LENGTH_IN_WORDS (2*CRYS_ECPKI_ORDER_MAX_LENGTH_IN_WORDS + CRYS_PKA_ECPKI_SCALAR_MUL_BUFF_MAX_LENGTH_IN_WORDS)
/*! ECC verify temp buffer size in words */
#define CRYS_PKA_ECDSA_VERIFY_BUFF_MAX_LENGTH_IN_WORDS (3*CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS)

/* *************************************************************************** */
/*! Definitions of maximal size of modulus buffers for CRYS_EC_MONT and EC_EDW in bytes */
#define CRYS_EC_MONT_EDW_MODULUS_MAX_SIZE_IN_BYTES  32U  /*!< \internal for Curve25519 */
/*! Definitions of maximal size of modulus buffers for CRYS_EC_MONT and EC_EDW in words */
#define CRYS_EC_MONT_EDW_MODULUS_MAX_SIZE_IN_WORDS   8U  /*!< \internal for Curve25519 */
/*! ECC montgomery temp buffer size in words */
#define CRYS_EC_MONT_TEMP_BUFF_SIZE_IN_32BIT_WORDS  (8 * CRYS_EC_MONT_EDW_MODULUS_MAX_SIZE_IN_WORDS)
/*! ECC edwards temp buffer size in words */
#define CRYS_EC_EDW_TEMP_BUFF_SIZE_IN_32BIT_WORD (8*CRYS_EC_MONT_EDW_MODULUS_MAX_SIZE_IN_WORDS + (sizeof(CRYS_HASHUserContext_t)+SASI_32BIT_WORD_SIZE-1)/SASI_32BIT_WORD_SIZE)

/**
@}
 */
/**
@}
 */
#endif /*_CRYS_PKA_DEFS_HW_H_*/

