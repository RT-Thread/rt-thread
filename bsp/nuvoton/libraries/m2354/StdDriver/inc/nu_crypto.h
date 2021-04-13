/**************************************************************************//**
 * @file     nu_crypto.h
 * @version  V3.00
 * @brief    Cryptographic Accelerator driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __NU_CRYPTO_H__
#define __NU_CRYPTO_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CRYPTO_Driver CRYPTO Driver
  @{
*/


/** @addtogroup CRYPTO_EXPORTED_CONSTANTS CRYPTO Exported Constants
  @{
*/


#define PRNG_KEY_SIZE_128       ( 0UL)     /*!< Select to generate 128-bit random key   \hideinitializer */
#define PRNG_KEY_SIZE_163       ( 1UL)     /*!< Select to generate 163-bit random key   \hideinitializer */
#define PRNG_KEY_SIZE_192       ( 2UL)     /*!< Select to generate 192-bit random key   \hideinitializer */
#define PRNG_KEY_SIZE_224       ( 3UL)     /*!< Select to generate 224-bit random key   \hideinitializer */
#define PRNG_KEY_SIZE_255       ( 4UL)     /*!< Select to generate 255-bit random key   \hideinitializer */
#define PRNG_KEY_SIZE_256       ( 6UL)     /*!< Select to generate 256-bit random key   \hideinitializer */
#define PRNG_KEY_SIZE_283       ( 7UL)     /*!< Select to generate 283-bit random key (Key Store Only)  \hideinitializer */
#define PRNG_KEY_SIZE_384       ( 8UL)     /*!< Select to generate 384-bit random key (Key Store Only)  \hideinitializer */
#define PRNG_KEY_SIZE_409       ( 9UL)     /*!< Select to generate 409-bit random key (Key Store Only)  \hideinitializer */
#define PRNG_KEY_SIZE_512       (10UL)     /*!< Select to generate 512-bit random key (Key Store Only)  \hideinitializer */
#define PRNG_KEY_SIZE_521       (11UL)     /*!< Select to generate 521-bit random key (Key Store Only)  \hideinitializer */
#define PRNG_KEY_SIZE_571       (12UL)     /*!< Select to generate 571-bit random key (Key Store Only)  \hideinitializer */

#define PRNG_SEED_CONT          (0UL)     /*!< PRNG using current seed                 \hideinitializer */
#define PRNG_SEED_RELOAD        (1UL)     /*!< PRNG reload new seed                    \hideinitializer */

#define AES_KEY_SIZE_128        (0UL)     /*!< AES select 128-bit key length           \hideinitializer */
#define AES_KEY_SIZE_192        (1UL)     /*!< AES select 192-bit key length           \hideinitializer */
#define AES_KEY_SIZE_256        (2UL)     /*!< AES select 256-bit key length           \hideinitializer */

#define AES_MODE_ECB            (0UL)     /*!< AES select ECB mode                     \hideinitializer */
#define AES_MODE_CBC            (1UL)     /*!< AES select CBC mode                     \hideinitializer */
#define AES_MODE_CFB            (2UL)     /*!< AES select CFB mode                     \hideinitializer */
#define AES_MODE_OFB            (3UL)     /*!< AES select OFB mode                     \hideinitializer */
#define AES_MODE_CTR            (4UL)     /*!< AES select CTR mode                     \hideinitializer */
#define AES_MODE_CBC_CS1        (0x10UL)  /*!< AES select CBC CS1 mode                 \hideinitializer */
#define AES_MODE_CBC_CS2        (0x11UL)  /*!< AES select CBC CS2 mode                 \hideinitializer */
#define AES_MODE_CBC_CS3        (0x12UL)  /*!< AES select CBC CS3 mode                 \hideinitializer */
#define AES_MODE_GCM            (0x20UL)
#define AES_MODE_GHASH          (0x21UL)
#define AES_MODE_CCM            (0x22UL)

#define SM4_MODE_ECB            (0x200UL)     /*!< SM4 select ECB mode                     \hideinitializer */
#define SM4_MODE_CBC            (0x201UL)     /*!< SM4 select CBC mode                     \hideinitializer */
#define SM4_MODE_CFB            (0x202UL)     /*!< SM4 select CFB mode                     \hideinitializer */
#define SM4_MODE_OFB            (0x203UL)     /*!< SM4 select OFB mode                     \hideinitializer */
#define SM4_MODE_CTR            (0x204UL)     /*!< SM4 select CTR mode                     \hideinitializer */
#define SM4_MODE_CBC_CS1        (0x210UL)     /*!< SM4 select CBC CS1 mode                 \hideinitializer */
#define SM4_MODE_CBC_CS2        (0x211UL)     /*!< SM4 select CBC CS2 mode                 \hideinitializer */
#define SM4_MODE_CBC_CS3        (0x212UL)     /*!< SM4 select CBC CS3 mode                 \hideinitializer */
#define SM4_MODE_GCM            (0x220UL)
#define SM4_MODE_GHASH          (0x221UL)
#define SM4_MODE_CCM            (0x222UL)


#define AES_NO_SWAP             (0UL)     /*!< AES do not swap input and output data   \hideinitializer */
#define AES_OUT_SWAP            (1UL)     /*!< AES swap output data                    \hideinitializer */
#define AES_IN_SWAP             (2UL)     /*!< AES swap input data                     \hideinitializer */
#define AES_IN_OUT_SWAP         (3UL)     /*!< AES swap both input and output data     \hideinitializer */

#define DES_MODE_ECB            (0x000UL) /*!< DES select ECB mode                     \hideinitializer */
#define DES_MODE_CBC            (0x100UL) /*!< DES select CBC mode                     \hideinitializer */
#define DES_MODE_CFB            (0x200UL) /*!< DES select CFB mode                     \hideinitializer */
#define DES_MODE_OFB            (0x300UL) /*!< DES select OFB mode                     \hideinitializer */
#define DES_MODE_CTR            (0x400UL) /*!< DES select CTR mode                     \hideinitializer */
#define TDES_MODE_ECB           (0x004UL) /*!< TDES select ECB mode                    \hideinitializer */
#define TDES_MODE_CBC           (0x104UL) /*!< TDES select CBC mode                    \hideinitializer */
#define TDES_MODE_CFB           (0x204UL) /*!< TDES select CFB mode                    \hideinitializer */
#define TDES_MODE_OFB           (0x304UL) /*!< TDES select OFB mode                    \hideinitializer */
#define TDES_MODE_CTR           (0x404UL) /*!< TDES select CTR mode                    \hideinitializer */

#define TDES_NO_SWAP            (0UL)     /*!< TDES do not swap data                       \hideinitializer */
#define TDES_WHL_SWAP           (1UL)     /*!< TDES swap high-low word                     \hideinitializer */
#define TDES_OUT_SWAP           (2UL)     /*!< TDES swap output data                       \hideinitializer */
#define TDES_OUT_WHL_SWAP       (3UL)     /*!< TDES swap output data and high-low word     \hideinitializer */
#define TDES_IN_SWAP            (4UL)     /*!< TDES swap input data                        \hideinitializer */
#define TDES_IN_WHL_SWAP        (5UL)     /*!< TDES swap input data and high-low word      \hideinitializer */
#define TDES_IN_OUT_SWAP        (6UL)     /*!< TDES swap both input and output data        \hideinitializer */
#define TDES_IN_OUT_WHL_SWAP    (7UL)     /*!< TDES swap input, output and high-low word   \hideinitializer */

#define SHA_MODE_SHA1           (0UL)     /*!< SHA select SHA-1 160-bit                \hideinitializer */
#define SHA_MODE_SHA224         (5UL)     /*!< SHA select SHA-224 224-bit              \hideinitializer */
#define SHA_MODE_SHA256         (4UL)     /*!< SHA select SHA-256 256-bit              \hideinitializer */
#define SHA_MODE_SHA384         (7UL)     /*!< SHA select SHA-384 384-bit              \hideinitializer */
#define SHA_MODE_SHA512         (6UL)     /*!< SHA select SHA-512 512-bit              \hideinitializer */

#define HMAC_MODE_SHA1          (8UL)     /*!< HMAC select SHA-1 160-bit                \hideinitializer */
#define HMAC_MODE_SHA224        (13UL)    /*!< HMAC select SHA-224 224-bit              \hideinitializer */
#define HMAC_MODE_SHA256        (12UL)    /*!< HMAC select SHA-256 256-bit              \hideinitializer */
#define HMAC_MODE_SHA384        (15UL)    /*!< HMAC select SHA-384 384-bit              \hideinitializer */
#define HMAC_MODE_SHA512        (14UL)    /*!< HMAC select SHA-512 512-bit              \hideinitializer */


#define SHA_NO_SWAP             (0UL)     /*!< SHA do not swap input and output data   \hideinitializer */
#define SHA_OUT_SWAP            (1UL)     /*!< SHA swap output data                    \hideinitializer */
#define SHA_IN_SWAP             (2UL)     /*!< SHA swap input data                     \hideinitializer */
#define SHA_IN_OUT_SWAP         (3UL)     /*!< SHA swap both input and output data     \hideinitializer */

#define CRYPTO_DMA_FIRST        (0x4UL)   /*!< Do first encrypt/decrypt in DMA cascade \hideinitializer */
#define CRYPTO_DMA_ONE_SHOT     (0x5UL)   /*!< Do one shot encrypt/decrypt with DMA      \hideinitializer */
#define CRYPTO_DMA_CONTINUE     (0x6UL)   /*!< Do continuous encrypt/decrypt in DMA cascade \hideinitializer */
#define CRYPTO_DMA_LAST         (0x7UL)   /*!< Do last encrypt/decrypt in DMA cascade          \hideinitializer */

//---------------------------------------------------

#define RSA_MAX_KLEN            (4096)
#define RSA_KBUF_HLEN           (RSA_MAX_KLEN/4 + 8)
#define RSA_KBUF_BLEN           (RSA_MAX_KLEN + 32)

#define RSA_KEY_SIZE_1024       (0UL)     /*!< RSA select 1024-bit key length           \hideinitializer */
#define RSA_KEY_SIZE_2048       (1UL)     /*!< RSA select 2048-bit key length           \hideinitializer */
#define RSA_KEY_SIZE_3072       (2UL)     /*!< RSA select 3072-bit key length           \hideinitializer */
#define RSA_KEY_SIZE_4096       (3UL)     /*!< RSA select 4096-bit key length           \hideinitializer */

#define RSA_MODE_NORMAL         (0x000UL)     /*!< RSA select normal mode                \hideinitializer */
#define RSA_MODE_CRT            (0x004UL)     /*!< RSA select CRT mode                   \hideinitializer */
#define RSA_MODE_CRTBYPASS      (0x00CUL)     /*!< RSA select CRT bypass mode            \hideinitializer */
#define RSA_MODE_SCAP           (0x100UL)     /*!< RSA select SCAP mode                  \hideinitializer */
#define RSA_MODE_CRT_SCAP       (0x104UL)     /*!< RSA select CRT SCAP mode              \hideinitializer */
#define RSA_MODE_CRTBYPASS_SCAP (0x10CUL)     /*!< RSA select CRT bypass SCAP mode       \hideinitializer */


typedef enum
{
    /*!< ECC curve                \hideinitializer */
    CURVE_P_192,                        /*!< ECC curve P-192          \hideinitializer */
    CURVE_P_224,                        /*!< ECC curve P-224          \hideinitializer */
    CURVE_P_256,                        /*!< ECC curve P-256          \hideinitializer */
    CURVE_P_384,                        /*!< ECC curve P-384          \hideinitializer */
    CURVE_P_521,                        /*!< ECC curve P-521          \hideinitializer */
    CURVE_K_163,                        /*!< ECC curve K-163          \hideinitializer */
    CURVE_K_233,                        /*!< ECC curve K-233          \hideinitializer */
    CURVE_K_283,                        /*!< ECC curve K-283          \hideinitializer */
    CURVE_K_409,                        /*!< ECC curve K-409          \hideinitializer */
    CURVE_K_571,                        /*!< ECC curve K-571          \hideinitializer */
    CURVE_B_163,                        /*!< ECC curve B-163          \hideinitializer */
    CURVE_B_233,                        /*!< ECC curve B-233          \hideinitializer */
    CURVE_B_283,                        /*!< ECC curve B-283          \hideinitializer */
    CURVE_B_409,                        /*!< ECC curve B-409          \hideinitializer */
    CURVE_B_571,                        /*!< ECC curve K-571          \hideinitializer */
    CURVE_KO_192,                       /*!< ECC 192-bits "Koblitz" curve   \hideinitializer */
    CURVE_KO_224,                       /*!< ECC 224-bits "Koblitz" curve   \hideinitializer */
    CURVE_KO_256,                       /*!< ECC 256-bits "Koblitz" curve   \hideinitializer */
    CURVE_BP_256,                       /*!< ECC Brainpool 256-bits curve   \hideinitializer */
    CURVE_BP_384,                       /*!< ECC Brainpool 256-bits curve   \hideinitializer */
    CURVE_BP_512,                       /*!< ECC Brainpool 256-bits curve   \hideinitializer */
    CURVE_25519,                        /*!< ECC curve-25519          \hideinitializer */
    CURVE_SM2_256,                      /*!< SM2                      \hideinitializer */
    CURVE_UNDEF = -0x7fffffff,                        /*!< Invalid curve            \hideinitializer */
}
E_ECC_CURVE;



typedef struct e_curve_t
{
    E_ECC_CURVE curve_id;
    int32_t     Echar;
    char        Ea[144];
    char        Eb[144];
    char        Px[144];
    char        Py[144];
    int32_t     Epl;
    char        Pp[176];
    int32_t     Eol;
    char        Eorder[176];
    int32_t     key_len;
    int32_t     irreducible_k1;
    int32_t     irreducible_k2;
    int32_t     irreducible_k3;
    int32_t     GF;
}  ECC_CURVE;


/* RSA working buffer for normal mode */
typedef struct
{
    uint32_t au32RsaOutput[128]; /* The RSA answer. */
    uint32_t au32RsaN[128]; /* The base of modulus operation word. */
    uint32_t au32RsaM[128]; /* The base of exponentiation words. */
    uint32_t au32RsaE[128]; /* The exponent of exponentiation words. */
} RSA_BUF_NORMAL_T;

/* RSA working buffer for CRT ( + CRT bypass) mode */
typedef struct
{
    uint32_t au32RsaOutput[128]; /* The RSA answer. */
    uint32_t au32RsaN[128]; /* The base of modulus operation word. */
    uint32_t au32RsaM[128]; /* The base of exponentiation words. */
    uint32_t au32RsaE[128]; /* The exponent of exponentiation words. */
    uint32_t au32RsaP[128]; /* The Factor of Modulus Operation. */
    uint32_t au32RsaQ[128]; /* The Factor of Modulus Operation. */
    uint32_t au32RsaTmpCp[128]; /* The Temporary Value(Cp) of RSA CRT. */
    uint32_t au32RsaTmpCq[128]; /* The Temporary Value(Cq) of RSA CRT. */
    uint32_t au32RsaTmpDp[128]; /* The Temporary Value(Dp) of RSA CRT. */
    uint32_t au32RsaTmpDq[128]; /* The Temporary Value(Dq) of RSA CRT. */
    uint32_t au32RsaTmpRp[128]; /* The Temporary Value(Rp) of RSA CRT. */
    uint32_t au32RsaTmpRq[128]; /* The Temporary Value(Rq) of RSA CRT. */
} RSA_BUF_CRT_T;

/* RSA working buffer for SCAP mode */
typedef struct
{
    uint32_t au32RsaOutput[128]; /* The RSA answer. */
    uint32_t au32RsaN[128]; /* The base of modulus operation word. */
    uint32_t au32RsaM[128]; /* The base of exponentiation words. */
    uint32_t au32RsaE[128]; /* The exponent of exponentiation words. */
    uint32_t au32RsaP[128]; /* The Factor of Modulus Operation. */
    uint32_t au32RsaQ[128]; /* The Factor of Modulus Operation. */
    uint32_t au32RsaTmpBlindKey[128]; /* The Temporary Value(blind key) of RSA SCAP. */
} RSA_BUF_SCAP_T;

/* RSA working buffer for CRT ( + CRT bypass ) + SCAP mode */
typedef struct
{
    uint32_t au32RsaOutput[128]; /* The RSA answer. */
    uint32_t au32RsaN[128]; /* The base of modulus operation word. */
    uint32_t au32RsaM[128]; /* The base of exponentiation words. */
    uint32_t au32RsaE[128]; /* The exponent of exponentiation words. */
    uint32_t au32RsaP[128]; /* The Factor of Modulus Operation. */
    uint32_t au32RsaQ[128]; /* The Factor of Modulus Operation. */
    uint32_t au32RsaTmpCp[128]; /* The Temporary Value(Cp) of RSA CRT. */
    uint32_t au32RsaTmpCq[128]; /* The Temporary Value(Cq) of RSA CRT. */
    uint32_t au32RsaTmpDp[128]; /* The Temporary Value(Dp) of RSA CRT. */
    uint32_t au32RsaTmpDq[128]; /* The Temporary Value(Dq) of RSA CRT. */
    uint32_t au32RsaTmpRp[128]; /* The Temporary Value(Rp) of RSA CRT. */
    uint32_t au32RsaTmpRq[128]; /* The Temporary Value(Rq) of RSA CRT. */
    uint32_t au32RsaTmpBlindKey[128]; /* The Temporary Value(blind key) of RSA SCAP. */
} RSA_BUF_CRT_SCAP_T;

/* RSA working buffer for using key store */
typedef struct
{
    uint32_t au32RsaOutput[128]; /* The RSA answer. */
    uint32_t au32RsaN[128]; /* The base of modulus operation word. */
    uint32_t au32RsaM[128]; /* The base of exponentiation words. */
} RSA_BUF_KS_T;

/**@}*/ /* end of group CRYPTO_EXPORTED_CONSTANTS */


/** @addtogroup CRYPTO_EXPORTED_MACROS CRYPTO Exported Macros
  @{
*/

/*----------------------------------------------------------------------------------------------*/
/*  Macros                                                                                      */
/*----------------------------------------------------------------------------------------------*/

/**
  * @brief This macro enables PRNG interrupt.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define PRNG_ENABLE_INT(crpt)       ((crpt)->INTEN |= CRPT_INTEN_PRNGIEN_Msk)

/**
  * @brief This macro disables PRNG interrupt.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define PRNG_DISABLE_INT(crpt)      ((crpt)->INTEN &= ~CRPT_INTEN_PRNGIEN_Msk)

/**
  * @brief This macro gets PRNG interrupt flag.
  * @param crpt     Specified crypto module
  * @return PRNG interrupt flag.
  * \hideinitializer
  */
#define PRNG_GET_INT_FLAG(crpt)     ((crpt)->INTSTS & CRPT_INTSTS_PRNGIF_Msk)

/**
  * @brief This macro clears PRNG interrupt flag.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define PRNG_CLR_INT_FLAG(crpt)     ((crpt)->INTSTS = CRPT_INTSTS_PRNGIF_Msk)

/**
  * @brief This macro enables AES interrupt.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define AES_ENABLE_INT(crpt)        ((crpt)->INTEN |= (CRPT_INTEN_AESIEN_Msk|CRPT_INTEN_AESEIEN_Msk))

/**
  * @brief This macro disables AES interrupt.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define AES_DISABLE_INT(crpt)       ((crpt)->INTEN &= ~(CRPT_INTEN_AESIEN_Msk|CRPT_INTEN_AESEIEN_Msk))

/**
  * @brief This macro gets AES interrupt flag.
  * @param crpt     Specified crypto module
  * @return AES interrupt flag.
  * \hideinitializer
  */
#define AES_GET_INT_FLAG(crpt)      ((crpt)->INTSTS & (CRPT_INTSTS_AESIF_Msk|CRPT_INTSTS_AESEIF_Msk))

/**
  * @brief This macro clears AES interrupt flag.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define AES_CLR_INT_FLAG(crpt)      ((crpt)->INTSTS = (CRPT_INTSTS_AESIF_Msk|CRPT_INTSTS_AESEIF_Msk))

/**
  * @brief This macro enables AES key protection.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define AES_ENABLE_KEY_PROTECT(crpt)  ((crpt)->AES_CTL |= CRPT_AES_CTL_KEYPRT_Msk)

/**
  * @brief This macro disables AES key protection.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define AES_DISABLE_KEY_PROTECT(crpt) ((crpt)->AES_CTL = ((crpt)->AES_CTL & ~CRPT_AES_CTL_KEYPRT_Msk) | (0x16UL<<CRPT_AES_CTL_KEYUNPRT_Pos)); \
                                      ((crpt)->AES_CTL &= ~CRPT_AES_CTL_KEYPRT_Msk)

/**
  * @brief This macro enables TDES interrupt.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define TDES_ENABLE_INT(crpt)       ((crpt)->INTEN |= (CRPT_INTEN_TDESIEN_Msk|CRPT_INTEN_TDESEIEN_Msk))

/**
  * @brief This macro disables TDES interrupt.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define TDES_DISABLE_INT(crpt)      ((crpt)->INTEN &= ~(CRPT_INTEN_TDESIEN_Msk|CRPT_INTEN_TDESEIEN_Msk))

/**
  * @brief This macro gets TDES interrupt flag.
  * @param crpt     Specified crypto module
  * @return TDES interrupt flag.
  * \hideinitializer
  */
#define TDES_GET_INT_FLAG(crpt)     ((crpt)->INTSTS & (CRPT_INTSTS_TDESIF_Msk|CRPT_INTSTS_TDESEIF_Msk))

/**
  * @brief This macro clears TDES interrupt flag.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define TDES_CLR_INT_FLAG(crpt)     ((crpt)->INTSTS = (CRPT_INTSTS_TDESIF_Msk|CRPT_INTSTS_TDESEIF_Msk))

/**
  * @brief This macro enables TDES key protection.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define TDES_ENABLE_KEY_PROTECT(crpt)  ((crpt)->TDES_CTL |= CRPT_TDES_CTL_KEYPRT_Msk)

/**
  * @brief This macro disables TDES key protection.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define TDES_DISABLE_KEY_PROTECT(crpt) ((crpt)->TDES_CTL = ((crpt)->TDES_CTL & ~CRPT_TDES_CTL_KEYPRT_Msk) | (0x16UL<<CRPT_TDES_CTL_KEYUNPRT_Pos)); \
                                       ((crpt)->TDES_CTL &= ~CRPT_TDES_CTL_KEYPRT_Msk)

/**
  * @brief This macro enables SHA interrupt.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define SHA_ENABLE_INT(crpt)        ((crpt)->INTEN |= (CRPT_INTEN_HMACIEN_Msk|CRPT_INTEN_HMACEIEN_Msk))

/**
  * @brief This macro disables SHA interrupt.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define SHA_DISABLE_INT(crpt)       ((crpt)->INTEN &= ~(CRPT_INTEN_HMACIEN_Msk|CRPT_INTEN_HMACEIEN_Msk))

/**
  * @brief This macro gets SHA interrupt flag.
  * @param crpt     Specified crypto module
  * @return SHA interrupt flag.
  * \hideinitializer
  */
#define SHA_GET_INT_FLAG(crpt)      ((crpt)->INTSTS & (CRPT_INTSTS_HMACIF_Msk|CRPT_INTSTS_HMACEIF_Msk))

/**
  * @brief This macro clears SHA interrupt flag.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define SHA_CLR_INT_FLAG(crpt)      ((crpt)->INTSTS = (CRPT_INTSTS_HMACIF_Msk|CRPT_INTSTS_HMACEIF_Msk))

/**
  * @brief This macro enables ECC interrupt.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define ECC_ENABLE_INT(crpt)        ((crpt)->INTEN |= (CRPT_INTEN_ECCIEN_Msk|CRPT_INTEN_ECCEIEN_Msk))

/**
  * @brief This macro disables ECC interrupt.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define ECC_DISABLE_INT(crpt)       ((crpt)->INTEN &= ~(CRPT_INTEN_ECCIEN_Msk|CRPT_INTEN_ECCEIEN_Msk))

/**
  * @brief This macro gets ECC interrupt flag.
  * @param crpt     Specified crypto module
  * @return ECC interrupt flag.
  * \hideinitializer
  */
#define ECC_GET_INT_FLAG(crpt)      ((crpt)->INTSTS & (CRPT_INTSTS_ECCIF_Msk|CRPT_INTSTS_ECCEIF_Msk))

/**
  * @brief This macro clears ECC interrupt flag.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define ECC_CLR_INT_FLAG(crpt)      ((crpt)->INTSTS = (CRPT_INTSTS_ECCIF_Msk|CRPT_INTSTS_ECCEIF_Msk))

/**
  * @brief This macro enables RSA interrupt.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define RSA_ENABLE_INT(crpt)        ((crpt)->INTEN |= (CRPT_INTEN_RSAIEN_Msk|CRPT_INTEN_RSAEIEN_Msk))

/**
  * @brief This macro disables RSA interrupt.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define RSA_DISABLE_INT(crpt)       ((crpt)->INTEN &= ~(CRPT_INTEN_RSAIEN_Msk|CRPT_INTEN_RSAEIEN_Msk))

/**
  * @brief This macro gets RSA interrupt flag.
  * @param crpt     Specified crypto module
  * @return ECC interrupt flag.
  * \hideinitializer
  */
#define RSA_GET_INT_FLAG(crpt)      ((crpt)->INTSTS & (CRPT_INTSTS_RSAIF_Msk|CRPT_INTSTS_RSAEIF_Msk))

/**
  * @brief This macro clears RSA interrupt flag.
  * @param crpt     Specified crypto module
  * @return None
  * \hideinitializer
  */
#define RSA_CLR_INT_FLAG(crpt)      ((crpt)->INTSTS = (CRPT_INTSTS_RSAIF_Msk|CRPT_INTSTS_RSAEIF_Msk))


/**@}*/ /* end of group CRYPTO_EXPORTED_MACROS */



/** @addtogroup CRYPTO_EXPORTED_FUNCTIONS CRYPTO Exported Functions
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  Functions                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/

void PRNG_Open(CRPT_T *crpt, uint32_t u32KeySize, uint32_t u32SeedReload, uint32_t u32Seed);
void PRNG_Start(CRPT_T *crpt);
void PRNG_Read(CRPT_T *crpt, uint32_t u32RandKey[]);
void AES_Open(CRPT_T *crpt, uint32_t u32Channel, uint32_t u32EncDec, uint32_t u32OpMode, uint32_t u32KeySize, uint32_t u32SwapType);
void AES_Start(CRPT_T *crpt, int32_t u32Channel, uint32_t u32DMAMode);
void AES_SetKey(CRPT_T *crpt, uint32_t u32Channel, uint32_t au32Keys[], uint32_t u32KeySize);
void AES_SetKey_KS(CRPT_T *crpt, KS_MEM_Type mem, int32_t i32KeyIdx);
void AES_SetInitVect(CRPT_T *crpt, uint32_t u32Channel, uint32_t au32IV[]);
void AES_SetDMATransfer(CRPT_T *crpt, uint32_t u32Channel, uint32_t u32SrcAddr, uint32_t u32DstAddr, uint32_t u32TransCnt);
void SHA_Open(CRPT_T *crpt, uint32_t u32OpMode, uint32_t u32SwapType, uint32_t hmac_key_len);
void SHA_Start(CRPT_T *crpt, uint32_t u32DMAMode);
void SHA_SetDMATransfer(CRPT_T *crpt, uint32_t u32SrcAddr, uint32_t u32TransCnt);
void SHA_Read(CRPT_T *crpt, uint32_t u32Digest[]);
void ECC_DriverISR(CRPT_T *crpt);
int  ECC_IsPrivateKeyValid(CRPT_T *crpt, E_ECC_CURVE ecc_curve,  char private_k[]);
int32_t  ECC_GenerateSecretZ(CRPT_T *crpt, E_ECC_CURVE ecc_curve, char *private_k, char public_k1[], char public_k2[], char secret_z[]);
int32_t  ECC_GeneratePublicKey(CRPT_T *crpt, E_ECC_CURVE ecc_curve, char *private_k, char public_k1[], char public_k2[]);
int32_t  ECC_GenerateSignature(CRPT_T *crpt, E_ECC_CURVE ecc_curve, char *message, char *d, char *k, char *R, char *S);
int32_t  ECC_VerifySignature(CRPT_T *crpt, E_ECC_CURVE ecc_curve, char *message, char *public_k1, char *public_k2, char *R, char *S);


int32_t RSA_Open(CRPT_T *crpt, uint32_t u32OpMode, uint32_t u32KeySize, void *psRSA_Buf, uint32_t u32BufSize, uint32_t u32UseKS);
int32_t RSA_SetKey(CRPT_T *crpt, char *Key);
int32_t RSA_SetDMATransfer(CRPT_T *crpt, char *Src, char *n, char *P, char *Q);
void RSA_Start(CRPT_T *crpt);
int32_t RSA_Read(CRPT_T *crpt, char * Output);
int32_t RSA_SetKey_KS(CRPT_T *crpt, uint32_t u32KeyNum, uint32_t u32KSMemType, uint32_t u32BlindKeyNum);
int32_t RSA_SetDMATransfer_KS(CRPT_T *crpt, char *Src, char *n, uint32_t u32PNum,
                              uint32_t u32QNum, uint32_t u32CpNum, uint32_t u32CqNum, uint32_t u32DpNum,
                              uint32_t u32DqNum, uint32_t u32RpNum, uint32_t u32RqNum);
int32_t  ECC_GeneratePublicKey_KS(CRPT_T *crpt, E_ECC_CURVE ecc_curve, KS_MEM_Type mem, int32_t i32KeyIdx, char public_k1[], char public_k2[], uint32_t u32ExtraOp);
int32_t  ECC_GenerateSignature_KS(CRPT_T *crpt, E_ECC_CURVE ecc_curve, char *message, KS_MEM_Type mem_d, int32_t i32KeyIdx_d, KS_MEM_Type mem_k, int32_t i32KeyIdx_k, char *R, char *S);
int32_t  ECC_VerifySignature_KS(CRPT_T *crpt, E_ECC_CURVE ecc_curve, char *message, KS_MEM_Type mem_pk1, int32_t i32KeyIdx_pk1, KS_MEM_Type mem_pk2, int32_t i32KeyIdx_pk2, char *R, char *S);
int32_t  ECC_GenerateSecretZ_KS(CRPT_T *crpt, E_ECC_CURVE ecc_curve, KS_MEM_Type mem, int32_t i32KeyIdx, char public_k1[], char public_k2[]);

void CRPT_Reg2Hex(int32_t count, uint32_t volatile reg[], char output[]);
void CRPT_Hex2Reg(char input[], uint32_t volatile reg[]);
int32_t ECC_GetCurve(CRPT_T *crpt, E_ECC_CURVE ecc_curve, ECC_CURVE *curve);

/**@}*/ /* end of group CRYPTO_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group CRYPTO_Driver */

/**@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif  /* __NU_CRYPTO_H__ */

