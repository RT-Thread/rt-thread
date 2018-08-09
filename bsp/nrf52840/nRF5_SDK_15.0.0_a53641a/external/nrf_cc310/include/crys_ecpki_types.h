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



#ifndef CRYS_ECPKI_TYPES_H
#define CRYS_ECPKI_TYPES_H

/*!
@file
@brief Contains all of the enums and definitions that are used for the CRYS ECPKI APIs.
@defgroup crys_ecpki_types CryptoCell ECC specific types
@{
@ingroup cryptocell_ecpki
*/

#include "ssi_pal_types_plat.h"
#include "crys_hash.h"
#include "crys_pka_defs_hw.h"
#include "ssi_pal_compiler.h"

#ifdef __cplusplus
extern "C"
{
#endif


/************************ Defines ******************************/
/*! Internal buffer size in words. */
#define CRYS_PKA_DOMAIN_LLF_BUFF_SIZE_IN_WORDS (10 + 3*CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS)

/**************************************************************************************
 *                Enumerators
 ***************************************************************************************/

/*------------------------------------------------------------------*/
/*! Enumerator for the EC Domain idetifier
   References: [13] - SEC 2: Recommended elliptic curve domain parameters.
                      Version 1.0. Certicom 2000.
               [8]  - WAP-261-WTLS-20010406-a, Version 06-April-2001.     */

typedef enum
{
    /* For prime field */
    CRYS_ECPKI_DomainID_secp160k1,   /*!< EC secp160r1 */
    CRYS_ECPKI_DomainID_secp160r1,   /*!< EC secp160k1 */
    CRYS_ECPKI_DomainID_secp160r2,   /*!< EC secp160r2 */
    CRYS_ECPKI_DomainID_secp192k1,   /*!< EC secp192k1 */
    CRYS_ECPKI_DomainID_secp192r1,   /*!< EC secp192r1 */
    CRYS_ECPKI_DomainID_secp224k1,   /*!< EC secp224k1 */
    CRYS_ECPKI_DomainID_secp224r1,   /*!< EC secp224r1 */
    CRYS_ECPKI_DomainID_secp256k1,   /*!< EC secp256k1 */
    CRYS_ECPKI_DomainID_secp256r1,   /*!< EC secp256r1 */
    CRYS_ECPKI_DomainID_secp384r1,   /*!< EC secp384r1 */
    CRYS_ECPKI_DomainID_secp521r1,   /*!< EC secp521r1 */

    CRYS_ECPKI_DomainID_Builded,     /*!< User given, not identified. */
    CRYS_ECPKI_DomainID_OffMode,     /*!< Reserved.*/

    CRYS_ECPKI_DomainIDLast      = 0x7FFFFFFF, /*! Reserved.*/

}CRYS_ECPKI_DomainID_t;


/*------------------------------------------------------------------*/
/*! Defines the enum for the HASH operation mode.
 *  The enumerator defines 6 HASH modes according to IEEE 1363.
 *
 */
typedef enum
{
    CRYS_ECPKI_HASH_SHA1_mode    = 0,       /*!< The message data will be hashed with SHA1. */
    CRYS_ECPKI_HASH_SHA224_mode  = 1,       /*!< The message data will be hashed with SHA224. */
    CRYS_ECPKI_HASH_SHA256_mode  = 2,       /*!< The message data will be hashed with SHA256. */
    CRYS_ECPKI_HASH_SHA384_mode  = 3,       /*!< The message data will be hashed with SHA384. */
    CRYS_ECPKI_HASH_SHA512_mode  = 4,       /*!< The message data will be hashed with SHA512. */

    CRYS_ECPKI_AFTER_HASH_SHA1_mode    = 5, /*!< The message data is a digest of SHA1 and will not be hashed. */
    CRYS_ECPKI_AFTER_HASH_SHA224_mode  = 6, /*!< The message data is a digest of SHA224 and will not be hashed. */
    CRYS_ECPKI_AFTER_HASH_SHA256_mode  = 7, /*!< The message data is a digest of SHA256 and will not be hashed. */
    CRYS_ECPKI_AFTER_HASH_SHA384_mode  = 8, /*!< The message data is a digest of SHA384 and will not be hashed. */
    CRYS_ECPKI_AFTER_HASH_SHA512_mode  = 9, /*!< The message data is a digest of SHA512 and will not be hashed. */


    CRYS_ECPKI_HASH_NumOfModes,   /*!< Maximal number of HASH modes. */
    CRYS_ECPKI_HASH_OpModeLast        = 0x7FFFFFFF, /*!< Reserved. */

}CRYS_ECPKI_HASH_OpMode_t;


/*---------------------------------------------------*/
/*! Enumerator for the EC point compression idetifier. */
typedef enum
{
    CRYS_EC_PointCompressed     = 2,   /*!< Compressed point. */
    CRYS_EC_PointUncompressed   = 4,   /*!< Uncompressed point. */
    CRYS_EC_PointContWrong      = 5,   /*!< Wrong Point Control value. */
    CRYS_EC_PointHybrid         = 6,   /*!< Hybrid point. */

    CRYS_EC_PointCompresOffMode = 8,   /*!< Reserved. */

    CRYS_ECPKI_PointCompressionLast= 0x7FFFFFFF, /*!< Reserved. */

}CRYS_ECPKI_PointCompression_t;


/*! EC key checks defintions. */
typedef enum {
    CheckPointersAndSizesOnly = 0,   /*!< Only preliminary input parameters are checked. */
    ECpublKeyPartlyCheck      = 1,   /*!< Preliminary input parameters check and verify that EC PubKey point is on the curve. */
    ECpublKeyFullCheck        = 2,   /*!< All the above and in addition verifies that EC_GeneratorOrder*PubKey = O */

    PublKeyChecingOffMode,             /*! Reserved. */
    EC_PublKeyCheckModeLast  = 0x7FFFFFFF, /*! Reserved. */
}EC_PublKeyCheckMode_t;

/*----------------------------------------------------*/
/*! Defintion of sw SCA protection. */
typedef enum {
    SCAP_Inactive, /*! Inactive.*/
    SCAP_Active,   /*! Active.*/
    SCAP_OFF_MODE, /*! Reserved. */
    SCAP_LAST = 0x7FFFFFFF /*! Reserved. */
} CRYS_ECPKI_ScaProtection_t;


/**************************************************************************************
 *               EC  Domain structure definition
 ***************************************************************************************/

/*! The structure containing the EC domain parameters in little-endian form
    EC equation: Y^2 = X^3 + A*X + B over prime fild GFp. */
typedef  struct {

    /*! EC modulus: P. */
    uint32_t    ecP [CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS];
    /*! EC equation parameter a. */
    uint32_t    ecA [CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS];
    /*! EC equation parameter b. */
    uint32_t    ecB [CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS];
    /*! Order of generator. */
    uint32_t    ecR [CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS + 1];
    /*! EC cofactor EC_Cofactor_K
        Generator (EC base point) coordinates in projective form. */
    uint32_t    ecGx [CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS];
    /*! EC cofactor EC_Cofactor_K
        Generator (EC base point) coordinates in projective form. */
    uint32_t    ecGy [CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS];
    /*! EC cofactor EC_Cofactor_K
        Generator (EC base point) coordinates in projective form. */
    uint32_t    ecH;
    /*! Specific fields that are used by the low level.*/
    uint32_t      llfBuff[CRYS_PKA_DOMAIN_LLF_BUFF_SIZE_IN_WORDS];
    /*! Size of fields in bits. */
    uint32_t    modSizeInBits;
    /*! Order size in bits. */
    uint32_t    ordSizeInBits;
    /*! Size of each inserted Barret tag in words; 0 - if not inserted.*/
    uint32_t    barrTagSizeInWords;
    /*! EC Domain identifier.*/
    CRYS_ECPKI_DomainID_t   DomainID;

    /*! Internal buffer. */
    int8_t name[20];

} CRYS_ECPKI_Domain_t;



/**************************************************************************************
 *               EC  point structures definitions
 ***************************************************************************************/

/*! The structure containing the EC point in affine coordinates
   and little endian form. */
typedef  struct
{
    /*! Point coordinate X. */
    uint32_t x[CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS];
    /*! Point coordinate Y. */
    uint32_t y[CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS];

}CRYS_ECPKI_PointAffine_t;


/**************************************************************************************
 *                ECPKI public and private key  Structures
 ***************************************************************************************/

/* --------------------------------------------------------------------- */
/* .................. The public key structures definitions ............ */
/* --------------------------------------------------------------------- */

/*! The structure containing the Public Key in affine coordinates.*/
typedef  struct
{
    /*! Public Key coordinate X.*/
    uint32_t x[CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS];
    /*! Public Key coordinate Y.*/
    uint32_t y[CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS];
    /*! EC Domain.*/
    CRYS_ECPKI_Domain_t  domain;
    /*! Point type.*/
    uint32_t pointType;
} CRYS_ECPKI_PublKey_t;

/*! The EC public key's user structure prototype. This structure must be saved by the user, and is used as input to the ECC functions
(such as ::CRYS_ECDSA_Verify etc.). */
typedef struct   CRYS_ECPKI_UserPublKey_t
{
    /*! Validation tag.*/
    uint32_t    valid_tag;
    /*! Public key data. */
    uint32_t    PublKeyDbBuff[(sizeof(CRYS_ECPKI_PublKey_t)+3)/4];

}  CRYS_ECPKI_UserPublKey_t;


/* --------------------------------------------------------------------- */
/* .................. The private key structures definitions ........... */
/* --------------------------------------------------------------------- */

/*! Structure containing the Private key data. */
typedef  struct
{
    /*! Private Key data. */
    uint32_t  PrivKey[CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS + 1];
    /*! Domain. */
    CRYS_ECPKI_Domain_t  domain;
    /*! SCA protection mode. */
    CRYS_ECPKI_ScaProtection_t  scaProtection;

}CRYS_ECPKI_PrivKey_t;


/*! The EC private key's user structure prototype. This structure must be saved by the user, and is used as input to the ECC functions
(such as ::CRYS_ECDSA_Sign etc.). */
typedef struct   CRYS_ECPKI_UserPrivKey_t
{
    /*! Validation tag. */
    uint32_t    valid_tag;
    /*! Private key data. */
    uint32_t    PrivKeyDbBuff[(sizeof(CRYS_ECPKI_PrivKey_t)+3)/4];

}  CRYS_ECPKI_UserPrivKey_t;

/*! ECDH temporary data type  */
typedef struct CRYS_ECDH_TempData_t
{
    /*! Temporary buffers. */
    uint32_t crysEcdhIntBuff[CRYS_PKA_ECDH_BUFF_MAX_LENGTH_IN_WORDS];
}CRYS_ECDH_TempData_t;

/*! EC build temporary data. */
typedef struct CRYS_ECPKI_BUILD_TempData_t
{
    /*! Temporary buffers. */
    uint32_t  crysBuildTmpIntBuff[CRYS_PKA_ECPKI_BUILD_TMP_BUFF_MAX_LENGTH_IN_WORDS];
}CRYS_ECPKI_BUILD_TempData_t;



/**************************************************************************
 *                CRYS ECDSA context structures
 **************************************************************************/

/* --------------------------------------------------------------------- */
/*                CRYS ECDSA Signing context structure                   */
/* --------------------------------------------------------------------- */
/*! Internal buffer used in the signing process. */
typedef uint32_t CRYS_ECDSA_SignIntBuff[CRYS_PKA_ECDSA_SIGN_BUFF_MAX_LENGTH_IN_WORDS];

/*! Context definition for Signing operation. */
typedef  struct
{
    /*! Private Key data. */
    CRYS_ECPKI_UserPrivKey_t     ECDSA_SignerPrivKey;

    /*! HASH context. */
    CRYS_HASHUserContext_t hashUserCtxBuff;
    /*! HASH result buffer. */
    CRYS_HASH_Result_t        hashResult;
    /*! HASH result size in words. */
    uint32_t                     hashResultSizeWords;
    /*! HASH mode. */
    CRYS_ECPKI_HASH_OpMode_t     hashMode;
    /*! Internal buffer. */
    CRYS_ECDSA_SignIntBuff crysEcdsaSignIntBuff;
}ECDSA_SignContext_t;


/* --------------------------------------------------------------------- */
/*                CRYS ECDSA  Signing User context database              */
/* --------------------------------------------------------------------- */

/*! User's context definition for signing operation. The context saves the state of the operation and must be saved by the user
   till the end of the APIs flow  */
typedef struct  CRYS_ECDSA_SignUserContext_t
{
    /*! Signing process data. */
    uint32_t  context_buff [(sizeof(ECDSA_SignContext_t)+3)/4];
    /*! Validation tag*/
    uint32_t  valid_tag;
} CRYS_ECDSA_SignUserContext_t;



/****************************************************************************/

/* --------------------------------------------------------------------- */
/*                CRYS ECDSA Verifying context structure                 */
/* --------------------------------------------------------------------- */
/*! Internal buffer used in the verification process. */
typedef uint32_t CRYS_ECDSA_VerifyIntBuff[CRYS_PKA_ECDSA_VERIFY_BUFF_MAX_LENGTH_IN_WORDS];

/*! Context definition for verification operation. */
typedef  struct
{
    /*! Public key data. */
    CRYS_ECPKI_UserPublKey_t         ECDSA_SignerPublKey;

    /*! HASH context. */
    CRYS_HASHUserContext_t hashUserCtxBuff;
    /*! HASH result. */
    CRYS_HASH_Result_t               hashResult;
    /*! HASH result size in words. */
    uint32_t                        hashResultSizeWords;
    /*! HASH mode. */
    CRYS_ECPKI_HASH_OpMode_t            hashMode;
    /*! Internal buffer. */
    CRYS_ECDSA_VerifyIntBuff    crysEcdsaVerIntBuff;

}ECDSA_VerifyContext_t;


/* --------------------------------------------------------------------- */
/*                CRYS ECDSA Verifying User context database             */
/* --------------------------------------------------------------------- */
/*! User's context definition for verification operation. The context saves the state of the operation and must be saved by the user
   till the end of the APIs flow  */
typedef struct  CRYS_ECDSA_VerifyUserContext_t
{
    /*! Verification process data. */
    uint32_t    context_buff[(sizeof(ECDSA_VerifyContext_t)+3)/4];
    /*! Validation tag. */
    uint32_t    valid_tag;
}CRYS_ECDSA_VerifyUserContext_t;




/* --------------------------------------------------------------------- */
/* .................. key generation temp buffer   ........... */
/* --------------------------------------------------------------------- */

/*! ECPKI KG temporary data type */
typedef struct CRYS_ECPKI_KG_TempData_t
{
    /*! Internal buffer. */
    uint32_t crysKGIntBuff[CRYS_PKA_KG_BUFF_MAX_LENGTH_IN_WORDS];
}CRYS_ECPKI_KG_TempData_t;

/*! ECIES temporary data definition. */
typedef struct CRYS_ECIES_TempData_t {

    /*! Private key data. */
    CRYS_ECPKI_UserPrivKey_t   PrivKey;
    /*! Public key data. */
    CRYS_ECPKI_UserPublKey_t   PublKey;
    /*! Internal buffer. */
    uint32_t  zz[3*CRYS_ECPKI_MODUL_MAX_LENGTH_IN_WORDS + 1];
    /*! Internal buffers. */
    union {
        CRYS_ECPKI_BUILD_TempData_t buildTempbuff;
        CRYS_ECPKI_KG_TempData_t    KgTempBuff;
        CRYS_ECDH_TempData_t        DhTempBuff;
    } tmp;

}CRYS_ECIES_TempData_t;


/* --------------------------------------------------------------------- */
/* .................. defines for FIPS      ........... */
/* --------------------------------------------------------------------- */

/*! Order length for the FIPS ECC tests. */
#define CRYS_ECPKI_FIPS_ORDER_LENGTH (256/SASI_BITS_IN_BYTE)  // the order of secp256r1 in bytes

/*! Context definition required for internal FIPS verification for ECPKI key generation. */
typedef struct CRYS_ECPKI_KG_FipsContext_t
{
    /*! Signing and verification data. */
    union {
        CRYS_ECDSA_SignUserContext_t    signCtx;
        CRYS_ECDSA_VerifyUserContext_t  verifyCtx;
    }operationCtx;
    /*! Internal buffer. */
    uint32_t    signBuff[2*CRYS_ECPKI_ORDER_MAX_LENGTH_IN_WORDS];
}CRYS_ECPKI_KG_FipsContext_t;



/*! Context defintion, required for internal FIPS verification for ECDSA KAT.      *
*  The ECDSA KAT tests defined for domain 256r1.     */
typedef struct CRYS_ECDSAFipsKatContext_t{
    /*! Key data. */
    union {
        /*! Private key data. */
        struct {
            CRYS_ECPKI_UserPrivKey_t    PrivKey;
            CRYS_ECDSA_SignUserContext_t    signCtx;
        }userSignData;
        /*! Public key data. */
        struct {
            CRYS_ECPKI_UserPublKey_t    PublKey;
            union {
                CRYS_ECDSA_VerifyUserContext_t  verifyCtx;
                CRYS_ECPKI_BUILD_TempData_t tempData;
            }buildOrVerify;
        }userVerifyData;
    }keyContextData;
    /*! Internal buffer. */
    uint8_t         signBuff[2*CRYS_ECPKI_FIPS_ORDER_LENGTH];
}CRYS_ECDSAFipsKatContext_t;

/*! Context definition, required for internal FIPS verification for ECDH KAT. */
typedef struct CRYS_ECDHFipsKatContext_t{
    /*! Public key data. */
    CRYS_ECPKI_UserPublKey_t  pubKey;
    /*! Private key data. */
    CRYS_ECPKI_UserPrivKey_t  privKey;
    /*! Internal buffers. */
    union {
        CRYS_ECPKI_BUILD_TempData_t  ecpkiTempData;
        CRYS_ECDH_TempData_t      ecdhTempBuff;
    }tmpData;
    /*! Buffer for the secret key. */
    uint8_t           secretBuff[CRYS_ECPKI_FIPS_ORDER_LENGTH];
}CRYS_ECDHFipsKatContext_t;

#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif
