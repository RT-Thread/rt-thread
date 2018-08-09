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
@brief This file contains all of the enums and definitions that are used for the
       CRYS SRP APIs, as well as the APIs themselves.
@defgroup crys_srp CryptoCell SRP APIs
@{
@ingroup cryptocell_api

*/
#ifndef CRYS_SRP_H
#define CRYS_SRP_H


#include "ssi_pal_types.h"
#include "crys_error.h"
#include "crys_pka_defs_hw.h"
#include "crys_hash.h"
#include "crys_rnd.h"


#ifdef __cplusplus
extern "C"
{
#endif

/*!\internal The following describes the SRP APIs usage for the Device and the Accessory :*

        Device (User)                       Accessory (Host)
*      --------------                       -----------------

  1.    CRYS_SRP_HK_INIT(CRYS_SRP_USER, .......)        CRYS_SRP_HK_INIT(CRYS_SRP_HOST, .....)

  2.                                CRYS_SRP_PwdVerCreate(..)

  3.    CRYS_SRP_UserPubKeyCreate(..)               CRYS_SRP_HostPubKeyCreate(..)

  4.    CRYS_SRP_UserProofCalc(..)

  5.                                CRYS_SRP_HostProofVerifyAndCalc(..)

  6.    CRYS_SRP_UserProofVerify(..)

  7.    CRYS_SRP_Clear(..)                  CRYS_SRP_Clear(..)

 */

/************************ Defines ******************************/
/*! The SRP modulus sizes. */
/*! 1024 bits modulus size. */
#define CRYS_SRP_MODULUS_SIZE_1024_BITS   1024
/*! 1536 bits modulus size. */
#define CRYS_SRP_MODULUS_SIZE_1536_BITS   1536
/*! 2048 bits modulus size. */
#define CRYS_SRP_MODULUS_SIZE_2048_BITS   2048
/*! 3072 bits modulus size. */
#define CRYS_SRP_MODULUS_SIZE_3072_BITS   3072

/*! Maximal modulus size in bits. */
#define CRYS_SRP_MAX_MODULUS_IN_BITS        CRYS_SRP_MODULUS_SIZE_3072_BITS
/*! Maximal modulus size in bytes. */
#define CRYS_SRP_MAX_MODULUS            (CRYS_SRP_MAX_MODULUS_IN_BITS/SASI_BITS_IN_BYTE)
/*! Maximal modulus size in words. */
#define CRYS_SRP_MAX_MODULUS_IN_WORDS       (CRYS_SRP_MAX_MODULUS_IN_BITS/SASI_BITS_IN_32BIT_WORD)

/*! The SRP private number size range. */
/*! Minimal private number size in bits. */
#define CRYS_SRP_PRIV_NUM_MIN_SIZE_IN_BITS      (256)
/*! Minimal private number size in bytes. */
#define CRYS_SRP_PRIV_NUM_MIN_SIZE          (CRYS_SRP_PRIV_NUM_MIN_SIZE_IN_BITS/SASI_BITS_IN_BYTE)
/*! Minimal private number size in words. */
#define CRYS_SRP_PRIV_NUM_MIN_SIZE_IN_WORDS         (CRYS_SRP_PRIV_NUM_MIN_SIZE_IN_BITS/SASI_BITS_IN_32BIT_WORD)
/*! Maximal private number size in bits. */
#define CRYS_SRP_PRIV_NUM_MAX_SIZE_IN_BITS      (CRYS_SRP_MAX_MODULUS_IN_BITS)
/*! Maximal private number size in bytes. */
#define CRYS_SRP_PRIV_NUM_MAX_SIZE          (CRYS_SRP_PRIV_NUM_MAX_SIZE_IN_BITS/SASI_BITS_IN_BYTE)
/*! Maximal private number size in words. */
#define CRYS_SRP_PRIV_NUM_MAX_SIZE_IN_WORDS         (CRYS_SRP_PRIV_NUM_MAX_SIZE_IN_BITS/SASI_BITS_IN_32BIT_WORD)

/*! Maximal SRP HASH digest size in words. */
#define CRYS_SRP_MAX_DIGEST_IN_WORDS        CRYS_HASH_RESULT_SIZE_IN_WORDS
/*! Maximal SRP HASH digest size in bytes. */
#define CRYS_SRP_MAX_DIGEST         (CRYS_SRP_MAX_DIGEST_IN_WORDS*SASI_32BIT_WORD_SIZE)

/*! Minimal salt size in bytes. */
#define CRYS_SRP_MIN_SALT_SIZE          (8)
/*! Minimal salt size in words. */
#define CRYS_SRP_MIN_SALT_SIZE_IN_WORDS     (CRYS_SRP_MIN_SALT_SIZE/SASI_32BIT_WORD_SIZE)
/*! Maximal salt size in bytes. */
#define CRYS_SRP_MAX_SALT_SIZE          (64)
/*! Maximal salt size in words. */
#define CRYS_SRP_MAX_SALT_SIZE_IN_WORDS     (CRYS_SRP_MAX_SALT_SIZE/SASI_32BIT_WORD_SIZE)

/************************ Typedefs  ****************************/
/*! SRP modulus buffer definition. */
typedef uint8_t CRYS_SRP_Modulus_t[CRYS_SRP_MAX_MODULUS];

/*! SRP digest buffer definition. */
typedef uint8_t CRYS_SRP_Digest_t[CRYS_SRP_MAX_DIGEST];

/*! SRP secret buffer definition. */
typedef uint8_t CRYS_SRP_Secret_t[2*CRYS_SRP_MAX_DIGEST];

/************************ Enums ********************************/

/*!
SRP supported versions
*/
typedef enum {
    CRYS_SRP_VER_3  = 0,    /*!< VER 3. */
    CRYS_SRP_VER_6   = 1,    /*!< VER 6. */
    CRYS_SRP_VER_6A  = 2,    /*!< VER 6A. */
    CRYS_SRP_VER_HK  = 3,    /*!< VER 6A. */
    /*! Maximal number of supported versions.*/
    CRYS_SRP_NumOfVersions,
    /*! Reserved.*/
    CRYS_SRP_VersionLast= 0x7FFFFFFF,

}CRYS_SRP_Version_t;

/*!
SRP entity type
*/
typedef enum {
    CRYS_SRP_HOST   = 1,    /*!< Host entity, called also server, verifier, or Accessory in Home-Kit */
    CRYS_SRP_USER   = 2,    /*!< User entity, called also client, or Device in Home-Kit */
    /*! Maximal number of entities types.*/
    CRYS_SRP_NumOfEntityType,
    /*! Reserved.*/
    CRYS_SRP_EntityLast= 0x7FFFFFFF,

}CRYS_SRP_Entity_t;

/************************ Structs  ******************************/

/*! Group parameters for the SRP - defines the modulus and the generator used */
typedef struct CRYS_SRP_GroupParam_t {
    /*! SRP modulus.*/
    CRYS_SRP_Modulus_t  modulus;
    /*! SRP generator.*/
    uint8_t         gen;
    /*! SRP modulus size in bits .*/
    size_t          modSizeInBits;
    /*! SRP valid Np.*/
    uint32_t        validNp;
    /*! SRP Np buffer.*/
    uint32_t        Np[CRYS_PKA_BARRETT_MOD_TAG_BUFF_SIZE_IN_WORDS];
}CRYS_SRP_GroupParam_t;

/************************ context Structs  ******************************/
/*! The SRP context prototype */
typedef struct CRYS_SRP_Context_t {
    /*! SRP entitiy type.*/
    CRYS_SRP_Entity_t       srpType;
    /*! SRP version.*/
    CRYS_SRP_Version_t      srpVer;
    /*! Group parameter including the modulus information.*/
    CRYS_SRP_GroupParam_t       groupParam; // N, g, Np
    /*! Hash mode.*/
    CRYS_HASH_OperationMode_t   hashMode;
    /*! Hash digest size.*/
    size_t              hashDigestSize;
    /*! Pointer to RND state.*/
    CRYS_RND_State_t        *pRndState;
    /*! Pointer to random vector generation function.*/
    SaSiRndGenerateVectWorkFunc_t   rndGenerateVectFunc;
    /*! Modulus.*/
    CRYS_SRP_Modulus_t      ephemPriv;  // a or b
    /*! Modulus size.*/
    size_t              ephemPrivSize;
    /*! User name digest.*/
    CRYS_SRP_Digest_t       userNameDigest; // M
    /*! Cred digest.*/
    CRYS_SRP_Digest_t       credDigest; // p
    /*! SRP K multiplier. */                        //
    CRYS_SRP_Digest_t       kMult;      // k multiplier
}CRYS_SRP_Context_t;


/************************ SRP common Functions **********************/
/****************************************************************************************************/
/*!
@brief This function initiates the SRP context.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_srp_error.h or crys_hash_error.h.
*/
CIMPORT_C CRYSError_t  CRYS_SRP_Init(
                CRYS_SRP_Entity_t   srpType,    /*!< [in] SRP entity type. */
                CRYS_SRP_Version_t  srpVer,     /*!< [in] SRP version. */
                CRYS_SRP_Modulus_t  srpModulus, /*!< [in] A pointer to the SRP modulus, BE byte buffer. */
                uint8_t         srpGen,     /*!< [in] The SRP generator param. */
                size_t          modSizeInBits,  /*!< [in] The SRP modulus size in bits:1024, 1536, 2048 & 3072 */
                CRYS_HASH_OperationMode_t   hashMode,       /*!< [in] Enumerator defining the HASH mode. */
                uint8_t         *pUserName, /*!< [in] A Pointer to user name. */
                size_t                  userNameSize,   /*!< [in] The user name buffer size > 0. */
                uint8_t         *pPwd,      /*!< [in] A Pointer to user password. */
                size_t                  pwdSize,    /*!< [in] The user password buffer size > 0 if pPwd is valid. */
                void    *pRndState, /*!< [in] A Pointer to RND context.*/
                SaSiRndGenerateVectWorkFunc_t   rndGenerateVectFunc, /*!< [in] Pointer to random vector generation function.*/
                CRYS_SRP_Context_t  *pCtx       /*!< [out] A Pointer to the SRP host context.*/
);

/*! MACRO definition for a specific SRP initialization function.*/
#define CRYS_SRP_HK_INIT(srpType, srpModulus, srpGen, modSizeInBits, pUserName, userNameSize, pPwd, pwdSize, pRndState, rndGenerateVectFunc, pCtx) \
    CRYS_SRP_Init(srpType, CRYS_SRP_VER_HK, srpModulus, srpGen, modSizeInBits, CRYS_HASH_SHA512_mode, pUserName, userNameSize, pPwd, pwdSize, pRndState, rndGenerateVectFunc, pCtx)


/****************************************************************************************************/
/*!
@brief This function calculates pSalt &  password verifier

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_srp_error.h, crys_rnd_error.h or crys_hash_error.h.
*/
CIMPORT_C CRYSError_t  CRYS_SRP_PwdVerCreate(
                size_t                  saltSize,   /*!< [in] The size of the random salt to generate,
                                        The range is between CRYS_SRP_MIN_SALT_SIZE
                                        to CRYS_SRP_MAX_SALT_SIZE. */
                uint8_t         *pSalt,     /*!< [out] A Pointer to the pSalt number (s).*/
                CRYS_SRP_Modulus_t      pwdVerifier,    /*!< [out] A Pointer to the password verifier (v). */
                CRYS_SRP_Context_t  *pCtx       /*!< [out] A Pointer to the SRP context.*/
);


/****************************************************************************************************/
/*!
@brief Clears the SRP context.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_srp_error.h.
*/
CIMPORT_C CRYSError_t  CRYS_SRP_Clear(
                CRYS_SRP_Context_t  *pCtx       /*!< [in/out] A Pointer to the SRP context.*/
);


/************************ SRP Host Functions **********************/
/****************************************************************************************************/
/*!
@brief This function generates host public & private ephemeral key, known as B & b in RFC

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_srp_error.h or crys_rnd_error.h.
*/
CIMPORT_C CRYSError_t  CRYS_SRP_HostPubKeyCreate(
                size_t                  ephemPrivSize,  /*!< [in] The size of the generated ephemeral private key (b).
                                        The range is between CRYS_SRP_PRIV_NUM_MIN_SIZE to
                                        CRYS_SRP_PRIV_NUM_MAX_SIZE */
                CRYS_SRP_Modulus_t      pwdVerifier,    /*!< [in] A Pointer to the verifier (v). */
                CRYS_SRP_Modulus_t      hostPubKeyB,    /*!< [out] A Pointer to the host ephemeral public key (B). */
                CRYS_SRP_Context_t  *pCtx       /*!< [in/out] A Pointer to the SRP context.*/
);


/*!
@brief Verifies the user Proof and calculates the Host message proof.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_srp_error.h or crys_hash_error.h.
*/
CIMPORT_C CRYSError_t  CRYS_SRP_HostProofVerifyAndCalc(
                size_t                  saltSize,   /*!< [in] The size of the random salt,
                                        The range is between CRYS_SRP_MIN_SALT_SIZE
                                        to CRYS_SRP_MAX_SALT_SIZE. */
                uint8_t         *pSalt,     /*!< [in] A Pointer to the pSalt number.*/
                CRYS_SRP_Modulus_t      pwdVerifier,    /*!< [in] A Pointer to the password verifier (v). */
                CRYS_SRP_Modulus_t      userPubKeyA,    /*!< [in] A Pointer to the user ephemeral public key (A). */
                CRYS_SRP_Modulus_t      hostPubKeyB,    /*!< [in] A Pointer to the host ephemeral public key (B). */
                CRYS_SRP_Digest_t   userProof,      /*!< [in] A Pointer to the SRP user proof buffer (M1).*/
                CRYS_SRP_Digest_t   hostProof,      /*!< [out] A Pointer to the SRP host proof buffer (M2).*/
                CRYS_SRP_Secret_t   sharedSecret,   /*!< [out] A Pointer to the SRP shared secret (K).*/
                CRYS_SRP_Context_t  *pCtx       /*!< [in] A Pointer to the SRP context.*/
);



/************************ SRP User Functions **********************/
/****************************************************************************************************/
/*!
@brief This function generates user public & private ephemeral key, known as A & a in RFC

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_srp_error.h or crys_rnd_error.h.
*/
CIMPORT_C CRYSError_t  CRYS_SRP_UserPubKeyCreate(
                size_t                  ephemPrivSize,  /*!< [in] The size of the generated ephemeral private key (a).
                                        The range is between CRYS_SRP_PRIV_NUM_MIN_SIZE to
                                        CRYS_SRP_PRIV_NUM_MAX_SIZE */
                CRYS_SRP_Modulus_t      userPubKeyA,    /*!< [out] A Pointer to the user ephemeral public key (A). */
                CRYS_SRP_Context_t  *pCtx       /*!< [in/out] A Pointer to the SRP context.*/
);


/****************************************************************************************************/
/*!
@brief This function calculates the user proof.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_srp_error.h or crys_hash_error.h.
*/
CIMPORT_C CRYSError_t  CRYS_SRP_UserProofCalc(
                size_t                  saltSize,   /*!< [in] The size of the random salt,
                                        The range is between CRYS_SRP_MIN_SALT_SIZE
                                        to CRYS_SRP_MAX_SALT_SIZE. */
                uint8_t         *pSalt,     /*!< [in] A Pointer to the pSalt number.*/
                CRYS_SRP_Modulus_t  userPubKeyA,  /*!< [in] A Pointer to the user public ephmeral key (A).*/
                CRYS_SRP_Modulus_t  hostPubKeyB,  /*!< [in] A Pointer to the host public ephmeral key (B).*/
                CRYS_SRP_Digest_t   userProof,      /*!< [out] A Pointer to the SRP user proof buffer (M1).*/
                CRYS_SRP_Secret_t   sharedSecret,   /*!< [out] A Pointer to the SRP shared secret (K).*/
                CRYS_SRP_Context_t  *pCtx       /*!< [out] A Pointer to the SRP context.*/
);

/****************************************************************************************************/
/*!
@brief This function verifies the host proof

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_srp_error.h or crys_hash_error.h.
*/
CIMPORT_C CRYSError_t  CRYS_SRP_UserProofVerify(
                CRYS_SRP_Secret_t   sharedSecret,   /*!< [in] A Pointer to the SRP shared secret (K).*/
                CRYS_SRP_Modulus_t  userPubKeyA,  /*!< [in] A Pointer to the user public ephmeral key (A).*/
                CRYS_SRP_Digest_t   userProof,      /*!< [in] A Pointer to the SRP user proof buffer (M1).*/
                CRYS_SRP_Digest_t   hostProof,     /*!< [in] A Pointer to the SRP host proof buffer (M2).*/
                CRYS_SRP_Context_t  *pCtx       /*!< [out] A Pointer to the SRP user context.*/
);


#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif /* #ifndef CRYS_SRP_H */





