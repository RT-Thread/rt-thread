/**************************************************************************//**
 * @file     nu_crypto.h
 * @version  V1.10
 * @brief    Cryptographic Accelerator driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
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

#define PRNG_KEY_SIZE_64        0UL     /*!< Select to generate 64-bit random key    \hideinitializer */
#define PRNG_KEY_SIZE_128       1UL     /*!< Select to generate 128-bit random key   \hideinitializer */
#define PRNG_KEY_SIZE_192       2UL     /*!< Select to generate 192-bit random key   \hideinitializer */
#define PRNG_KEY_SIZE_256       3UL     /*!< Select to generate 256-bit random key   \hideinitializer */

#define PRNG_SEED_CONT          0UL     /*!< PRNG using current seed                 \hideinitializer */
#define PRNG_SEED_RELOAD        1UL     /*!< PRNG reload new seed                    \hideinitializer */

#define AES_KEY_SIZE_128        0UL     /*!< AES select 128-bit key length           \hideinitializer */
#define AES_KEY_SIZE_192        1UL     /*!< AES select 192-bit key length           \hideinitializer */
#define AES_KEY_SIZE_256        2UL     /*!< AES select 256-bit key length           \hideinitializer */

#define AES_MODE_ECB            0UL     /*!< AES select ECB mode                     \hideinitializer */
#define AES_MODE_CBC            1UL     /*!< AES select CBC mode                     \hideinitializer */
#define AES_MODE_CFB            2UL     /*!< AES select CFB mode                     \hideinitializer */
#define AES_MODE_OFB            3UL     /*!< AES select OFB mode                     \hideinitializer */
#define AES_MODE_CTR            4UL     /*!< AES select CTR mode                     \hideinitializer */
#define AES_MODE_CBC_CS1        0x10UL  /*!< AES select CBC CS1 mode                 \hideinitializer */
#define AES_MODE_CBC_CS2        0x11UL  /*!< AES select CBC CS2 mode                 \hideinitializer */
#define AES_MODE_CBC_CS3        0x12UL  /*!< AES select CBC CS3 mode                 \hideinitializer */

#define AES_NO_SWAP             0UL     /*!< AES do not swap input and output data   \hideinitializer */
#define AES_OUT_SWAP            1UL     /*!< AES swap output data                    \hideinitializer */
#define AES_IN_SWAP             2UL     /*!< AES swap input data                     \hideinitializer */
#define AES_IN_OUT_SWAP         3UL     /*!< AES swap both input and output data     \hideinitializer */

#define DES_MODE_ECB            0x000UL /*!< DES select ECB mode                     \hideinitializer */
#define DES_MODE_CBC            0x100UL /*!< DES select CBC mode                     \hideinitializer */
#define DES_MODE_CFB            0x200UL /*!< DES select CFB mode                     \hideinitializer */
#define DES_MODE_OFB            0x300UL /*!< DES select OFB mode                     \hideinitializer */
#define DES_MODE_CTR            0x400UL /*!< DES select CTR mode                     \hideinitializer */
#define TDES_MODE_ECB           0x004UL /*!< TDES select ECB mode                    \hideinitializer */
#define TDES_MODE_CBC           0x104UL /*!< TDES select CBC mode                    \hideinitializer */
#define TDES_MODE_CFB           0x204UL /*!< TDES select CFB mode                    \hideinitializer */
#define TDES_MODE_OFB           0x304UL /*!< TDES select OFB mode                    \hideinitializer */
#define TDES_MODE_CTR           0x404UL /*!< TDES select CTR mode                    \hideinitializer */

#define TDES_NO_SWAP            0UL     /*!< TDES do not swap data                       \hideinitializer */
#define TDES_WHL_SWAP           1UL     /*!< TDES swap high-low word                     \hideinitializer */
#define TDES_OUT_SWAP           2UL     /*!< TDES swap output data                       \hideinitializer */
#define TDES_OUT_WHL_SWAP       3UL     /*!< TDES swap output data and high-low word     \hideinitializer */
#define TDES_IN_SWAP            4UL     /*!< TDES swap input data                        \hideinitializer */
#define TDES_IN_WHL_SWAP        5UL     /*!< TDES swap input data and high-low word      \hideinitializer */
#define TDES_IN_OUT_SWAP        6UL     /*!< TDES swap both input and output data        \hideinitializer */
#define TDES_IN_OUT_WHL_SWAP    7UL     /*!< TDES swap input, output and high-low word   \hideinitializer */

#define SHA_MODE_SHA1           0UL     /*!< SHA select SHA-1 160-bit                \hideinitializer */
#define SHA_MODE_SHA224         5UL     /*!< SHA select SHA-224 224-bit              \hideinitializer */
#define SHA_MODE_SHA256         4UL     /*!< SHA select SHA-256 256-bit              \hideinitializer */
#define SHA_MODE_SHA384         7UL     /*!< SHA select SHA-384 384-bit              \hideinitializer */
#define SHA_MODE_SHA512         6UL     /*!< SHA select SHA-512 512-bit              \hideinitializer */

#define SHA_NO_SWAP             0UL     /*!< SHA do not swap input and output data   \hideinitializer */
#define SHA_OUT_SWAP            1UL     /*!< SHA swap output data                    \hideinitializer */
#define SHA_IN_SWAP             2UL     /*!< SHA swap input data                     \hideinitializer */
#define SHA_IN_OUT_SWAP         3UL     /*!< SHA swap both input and output data     \hideinitializer */

#define CRYPTO_DMA_FIRST        0x4UL   /*!< Do first encrypt/decrypt in DMA cascade \hideinitializer */
#define CRYPTO_DMA_ONE_SHOT     0x5UL   /*!< Do one shot encrypt/decrypt with DMA      \hideinitializer */
#define CRYPTO_DMA_CONTINUE     0x6UL   /*!< Do continuous encrypt/decrypt in DMA cascade \hideinitializer */
#define CRYPTO_DMA_LAST         0x7UL   /*!< Do last encrypt/decrypt in DMA cascade          \hideinitializer */

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
    CURVE_UNDEF,                        /*!< Invalid curve            \hideinitializer */
}
E_ECC_CURVE;                            /*!< ECC curve                \hideinitializer */


/*@}*/ /* end of group CRYPTO_EXPORTED_CONSTANTS */


/** @addtogroup M480_CRYPTO_EXPORTED_MACROS CRYPTO Exported Macros
  @{
*/

/*----------------------------------------------------------------------------------------------*/
/*  Macros                                                                                      */
/*----------------------------------------------------------------------------------------------*/

/**
  * @brief This macro enables PRNG interrupt.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define PRNG_ENABLE_INT(crpt)       ((crpt)->INTEN |= CRPT_INTEN_PRNGIEN_Msk)

/**
  * @brief This macro disables PRNG interrupt.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define PRNG_DISABLE_INT(crpt)      ((crpt)->INTEN &= ~CRPT_INTEN_PRNGIEN_Msk)

/**
  * @brief This macro gets PRNG interrupt flag.
  * @param crpt     Specified cripto module
  * @return PRNG interrupt flag.
  * \hideinitializer
  */
#define PRNG_GET_INT_FLAG(crpt)     ((crpt)->INTSTS & CRPT_INTSTS_PRNGIF_Msk)

/**
  * @brief This macro clears PRNG interrupt flag.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define PRNG_CLR_INT_FLAG(crpt)     ((crpt)->INTSTS = CRPT_INTSTS_PRNGIF_Msk)

/**
  * @brief This macro enables AES interrupt.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define AES_ENABLE_INT(crpt)        ((crpt)->INTEN |= (CRPT_INTEN_AESIEN_Msk|CRPT_INTEN_AESEIEN_Msk))

/**
  * @brief This macro disables AES interrupt.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define AES_DISABLE_INT(crpt)       ((crpt)->INTEN &= ~(CRPT_INTEN_AESIEN_Msk|CRPT_INTEN_AESEIEN_Msk))

/**
  * @brief This macro gets AES interrupt flag.
  * @param crpt     Specified cripto module
  * @return AES interrupt flag.
  * \hideinitializer
  */
#define AES_GET_INT_FLAG(crpt)      ((crpt)->INTSTS & (CRPT_INTSTS_AESIF_Msk|CRPT_INTSTS_AESEIF_Msk))

/**
  * @brief This macro clears AES interrupt flag.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define AES_CLR_INT_FLAG(crpt)      ((crpt)->INTSTS = (CRPT_INTSTS_AESIF_Msk|CRPT_INTSTS_AESEIF_Msk))

/**
  * @brief This macro enables AES key protection.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define AES_ENABLE_KEY_PROTECT(crpt)  ((crpt)->AES_CTL |= CRPT_AES_CTL_KEYPRT_Msk)

/**
  * @brief This macro disables AES key protection.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define AES_DISABLE_KEY_PROTECT(crpt) ((crpt)->AES_CTL = ((crpt)->AES_CTL & ~CRPT_AES_CTL_KEYPRT_Msk) | (0x16UL<<CRPT_AES_CTL_KEYUNPRT_Pos)); \
                                      ((crpt)->AES_CTL &= ~CRPT_AES_CTL_KEYPRT_Msk)

/**
  * @brief This macro enables TDES interrupt.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define TDES_ENABLE_INT(crpt)       ((crpt)->INTEN |= (CRPT_INTEN_TDESIEN_Msk|CRPT_INTEN_TDESEIEN_Msk))

/**
  * @brief This macro disables TDES interrupt.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define TDES_DISABLE_INT(crpt)      ((crpt)->INTEN &= ~(CRPT_INTEN_TDESIEN_Msk|CRPT_INTEN_TDESEIEN_Msk))

/**
  * @brief This macro gets TDES interrupt flag.
  * @param crpt     Specified cripto module
  * @return TDES interrupt flag.
  * \hideinitializer
  */
#define TDES_GET_INT_FLAG(crpt)     ((crpt)->INTSTS & (CRPT_INTSTS_TDESIF_Msk|CRPT_INTSTS_TDESEIF_Msk))

/**
  * @brief This macro clears TDES interrupt flag.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define TDES_CLR_INT_FLAG(crpt)     ((crpt)->INTSTS = (CRPT_INTSTS_TDESIF_Msk|CRPT_INTSTS_TDESEIF_Msk))

/**
  * @brief This macro enables TDES key protection.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define TDES_ENABLE_KEY_PROTECT(crpt)  ((crpt)->TDES_CTL |= CRPT_TDES_CTL_KEYPRT_Msk)

/**
  * @brief This macro disables TDES key protection.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define TDES_DISABLE_KEY_PROTECT(crpt) ((crpt)->TDES_CTL = ((crpt)->TDES_CTL & ~CRPT_TDES_CTL_KEYPRT_Msk) | (0x16UL<<CRPT_TDES_CTL_KEYUNPRT_Pos)); \
                                       ((crpt)->TDES_CTL &= ~CRPT_TDES_CTL_KEYPRT_Msk)

/**
  * @brief This macro enables SHA interrupt.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define SHA_ENABLE_INT(crpt)        ((crpt)->INTEN |= (CRPT_INTEN_HMACIEN_Msk|CRPT_INTEN_HMACEIEN_Msk))

/**
  * @brief This macro disables SHA interrupt.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define SHA_DISABLE_INT(crpt)       ((crpt)->INTEN &= ~(CRPT_INTEN_HMACIEN_Msk|CRPT_INTEN_HMACEIEN_Msk))

/**
  * @brief This macro gets SHA interrupt flag.
  * @param crpt     Specified cripto module
  * @return SHA interrupt flag.
  * \hideinitializer
  */
#define SHA_GET_INT_FLAG(crpt)      ((crpt)->INTSTS & (CRPT_INTSTS_HMACIF_Msk|CRPT_INTSTS_HMACEIF_Msk))

/**
  * @brief This macro clears SHA interrupt flag.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define SHA_CLR_INT_FLAG(crpt)      ((crpt)->INTSTS = (CRPT_INTSTS_HMACIF_Msk|CRPT_INTSTS_HMACEIF_Msk))

/**
  * @brief This macro enables ECC interrupt.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define ECC_ENABLE_INT(crpt)        ((crpt)->INTEN |= (CRPT_INTEN_ECCIEN_Msk|CRPT_INTEN_ECCEIEN_Msk))

/**
  * @brief This macro disables ECC interrupt.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define ECC_DISABLE_INT(crpt)       ((crpt)->INTEN &= ~(CRPT_INTEN_ECCIEN_Msk|CRPT_INTEN_ECCEIEN_Msk))

/**
  * @brief This macro gets ECC interrupt flag.
  * @param crpt     Specified cripto module
  * @return ECC interrupt flag.
  * \hideinitializer
  */
#define ECC_GET_INT_FLAG(crpt)      ((crpt)->INTSTS & (CRPT_INTSTS_ECCIF_Msk|CRPT_INTSTS_ECCEIF_Msk))

/**
  * @brief This macro clears ECC interrupt flag.
  * @param crpt     Specified cripto module
  * @return None
  * \hideinitializer
  */
#define ECC_CLR_INT_FLAG(crpt)      ((crpt)->INTSTS = (CRPT_INTSTS_ECCIF_Msk|CRPT_INTSTS_ECCEIF_Msk))


/*@}*/ /* end of group M480_CRYPTO_EXPORTED_MACROS */


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
void AES_Start(CRPT_T *crpt, uint32_t u32Channel, uint32_t u32DMAMode);
void AES_SetKey(CRPT_T *crpt, uint32_t u32Channel, uint32_t au32Keys[], uint32_t u32KeySize);
void AES_SetInitVect(CRPT_T *crpt, uint32_t u32Channel, uint32_t au32IV[]);
void AES_SetDMATransfer(CRPT_T *crpt, uint32_t u32Channel, uint32_t u32SrcAddr, uint32_t u32DstAddr, uint32_t u32TransCnt);
void TDES_Open(CRPT_T *crpt, uint32_t u32Channel, uint32_t u32EncDec, int32_t Is3DES, int32_t Is3Key, uint32_t u32OpMode, uint32_t u32SwapType);
void TDES_Start(CRPT_T *crpt, int32_t u32Channel, uint32_t u32DMAMode);
void TDES_SetKey(CRPT_T *crpt, uint32_t u32Channel, uint32_t au32Keys[3][2]);
void TDES_SetInitVect(CRPT_T *crpt, uint32_t u32Channel, uint32_t u32IVH, uint32_t u32IVL);
void TDES_SetDMATransfer(CRPT_T *crpt, uint32_t u32Channel, uint32_t u32SrcAddr, uint32_t u32DstAddr, uint32_t u32TransCnt);
void SHA_Open(CRPT_T *crpt, uint32_t u32OpMode, uint32_t u32SwapType, uint32_t hmac_key_len);
void SHA_Start(CRPT_T *crpt, uint32_t u32DMAMode);
void SHA_SetDMATransfer(CRPT_T *crpt, uint32_t u32SrcAddr, uint32_t u32TransCnt);
void SHA_Read(CRPT_T *crpt, uint32_t u32Digest[]);
void ECC_Complete(CRPT_T *crpt);
int  ECC_IsPrivateKeyValid(CRPT_T *crpt, E_ECC_CURVE ecc_curve,  char private_k[]);
int32_t  ECC_GeneratePublicKey(CRPT_T *crpt, E_ECC_CURVE ecc_curve, char *private_k, char public_k1[], char public_k2[]);
int32_t  ECC_Mutiply(CRPT_T *crpt, E_ECC_CURVE ecc_curve, char x1[], char y1[], char *k, char x2[], char y2[]);
int32_t  ECC_GenerateSecretZ(CRPT_T *crpt, E_ECC_CURVE ecc_curve, char *private_k, char public_k1[], char public_k2[], char secret_z[]);
int32_t  ECC_GenerateSignature(CRPT_T *crpt, E_ECC_CURVE ecc_curve, char *message, char *d, char *k, char *R, char *S);
int32_t  ECC_VerifySignature(CRPT_T *crpt, E_ECC_CURVE ecc_curve, char *message, char *public_k1, char *public_k2, char *R, char *S);


/*@}*/ /* end of group CRYPTO_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CRYPTO_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif  /* __NU_CRYPTO_H__ */

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/

