/**************************************************************************//**
 * @file     crypto.h
 * @version  V1.10
 * $Revision: 14 $
 * $Date: 14/10/06 1:49p $
 * @brief    Cryptographic Accelerator driver header file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __CRYPTO_H__
#define __CRYPTO_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_CRYPTO_Driver CRYPTO Driver
  @{
*/


/** @addtogroup NUC472_442_CRYPTO_EXPORTED_CONSTANTS CRYPTO Exported Constants
  @{
*/

#define PRNG_KEY_SIZE_64        0       /*!< Select to generate 64-bit random key    \hideinitializer */
#define PRNG_KEY_SIZE_128       1       /*!< Select to generate 128-bit random key   \hideinitializer */
#define PRNG_KEY_SIZE_192       2       /*!< Select to generate 192-bit random key   \hideinitializer */
#define PRNG_KEY_SIZE_256       3       /*!< Select to generate 256-bit random key   \hideinitializer */

#define PRNG_SEED_CONT          0       /*!< PRNG using current seed                 \hideinitializer */
#define PRNG_SEED_RELOAD        1       /*!< PRNG reload new seed                    \hideinitializer */

#define AES_KEY_SIZE_128        0       /*!< AES select 128-bit key length           \hideinitializer */
#define AES_KEY_SIZE_192        1       /*!< AES select 192-bit key length           \hideinitializer */
#define AES_KEY_SIZE_256        2       /*!< AES select 256-bit key length           \hideinitializer */

#define AES_MODE_ECB            0       /*!< AES select ECB mode                     \hideinitializer */
#define AES_MODE_CBC            1       /*!< AES select CBC mode                     \hideinitializer */
#define AES_MODE_CFB            2       /*!< AES select CFB mode                     \hideinitializer */
#define AES_MODE_OFB            3       /*!< AES select OFB mode                     \hideinitializer */
#define AES_MODE_CTR            4       /*!< AES select CTR mode                     \hideinitializer */
#define AES_MODE_CBC_CS1        0x10    /*!< AES select CBC CS1 mode                 \hideinitializer */
#define AES_MODE_CBC_CS2        0x11    /*!< AES select CBC CS2 mode                 \hideinitializer */
#define AES_MODE_CBC_CS3        0x12    /*!< AES select CBC CS3 mode                 \hideinitializer */

#define AES_NO_SWAP             0       /*!< AES do not swap input and output data   \hideinitializer */
#define AES_OUT_SWAP            1       /*!< AES swap output data                    \hideinitializer */
#define AES_IN_SWAP             2       /*!< AES swap input data                     \hideinitializer */
#define AES_IN_OUT_SWAP         3       /*!< AES swap both input and output data     \hideinitializer */

#define DES_MODE_ECB            0x000   /*!< DES select ECB mode                     \hideinitializer */
#define DES_MODE_CBC            0x100   /*!< DES select CBC mode                     \hideinitializer */
#define DES_MODE_CFB            0x200   /*!< DES select CFB mode                     \hideinitializer */
#define DES_MODE_OFB            0x300   /*!< DES select OFB mode                     \hideinitializer */
#define DES_MODE_CTR            0x400   /*!< DES select CTR mode                     \hideinitializer */
#define TDES_MODE_ECB           0x004   /*!< TDES select ECB mode                    \hideinitializer */
#define TDES_MODE_CBC           0x104   /*!< TDES select CBC mode                    \hideinitializer */
#define TDES_MODE_CFB           0x204   /*!< TDES select CFB mode                    \hideinitializer */
#define TDES_MODE_OFB           0x304   /*!< TDES select OFB mode                    \hideinitializer */
#define TDES_MODE_CTR           0x404   /*!< TDES select CTR mode                    \hideinitializer */

#define TDES_NO_SWAP            0       /*!< TDES do not swap data                       \hideinitializer */
#define TDES_WHL_SWAP           1       /*!< TDES swap high-low word                     \hideinitializer */
#define TDES_OUT_SWAP           2       /*!< TDES swap output data                       \hideinitializer */
#define TDES_OUT_WHL_SWAP       3       /*!< TDES swap output data and high-low word     \hideinitializer */
#define TDES_IN_SWAP            4       /*!< TDES swap input data                        \hideinitializer */
#define TDES_IN_WHL_SWAP        5       /*!< TDES swap input data and high-low word      \hideinitializer */
#define TDES_IN_OUT_SWAP        6       /*!< TDES swap both input and output data        \hideinitializer */
#define TDES_IN_OUT_WHL_SWAP    7       /*!< TDES swap input, output and high-low word   \hideinitializer */

#define SHA_MODE_SHA1           0       /*!< SHA select SHA-1 160-bit                \hideinitializer */
#define SHA_MODE_SHA224         5       /*!< SHA select SHA-224 224-bit              \hideinitializer */
#define SHA_MODE_SHA256         4       /*!< SHA select SHA-256 256-bit              \hideinitializer */

#define SHA_NO_SWAP             0       /*!< SHA do not swap input and output data   \hideinitializer */
#define SHA_OUT_SWAP            1       /*!< SHA swap output data                    \hideinitializer */
#define SHA_IN_SWAP             2       /*!< SHA swap input data                     \hideinitializer */
#define SHA_IN_OUT_SWAP         3       /*!< SHA swap both input and output data     \hideinitializer */

#define CRYPTO_DMA_ONE_SHOT     0x5     /*!< Do one shot encrypt/decrypt with DMA      \hideinitializer */
#define CRYPTO_DMA_CONTINUE     0x6     /*!< Do one continuous encrypt/decrypt with DMA \hideinitializer */
#define CRYPTO_DMA_LAST         0x6     /*!< Do last encrypt/decrypt with DMA          \hideinitializer */

/*@}*/ /* end of group NUC472_442_CRYPTO_EXPORTED_CONSTANTS */




/** @addtogroup NUC472_442_CRYPTO_EXPORTED_FUNCTIONS CRYPTO Exported Functions
  @{
*/

/*----------------------------------------------------------------------------------------------*/
/*  Macros                                                                                      */
/*----------------------------------------------------------------------------------------------*/

/**
  * @brief This macro enables PRNG interrupt.
  * @param None
  * @return None
  * \hideinitializer
  */
#define PRNG_ENABLE_INT()       (CRPT->INTEN |= CRPT_INTEN_PRNGIEN_Msk)

/**
  * @brief This macro disables PRNG interrupt.
  * @param None
  * @return None
  * \hideinitializer
  */
#define PRNG_DISABLE_INT()      (CRPT->INTEN &= ~CRPT_INTEN_PRNGIEN_Msk)

/**
  * @brief This macro gets PRNG interrupt flag.
  * @param None
  * @return PRNG interrupt flag.
  * \hideinitializer
  */
#define PRNG_GET_INT_FLAG()     (CRPT->INTSTS & CRPT_INTSTS_PRNGIF_Msk)

/**
  * @brief This macro clears PRNG interrupt flag.
  * @param None
  * @return None
  * \hideinitializer
  */
#define PRNG_CLR_INT_FLAG()     (CRPT->INTSTS = CRPT_INTSTS_PRNGIF_Msk)

/**
  * @brief This macro enables AES interrupt.
  * @param None
  * @return None
  * \hideinitializer
  */
#define AES_ENABLE_INT()        (CRPT->INTEN |= (CRPT_INTEN_AESIEN_Msk|CRPT_INTEN_AESERRIEN_Msk))

/**
  * @brief This macro disables AES interrupt.
  * @param None
  * @return None
  * \hideinitializer
  */
#define AES_DISABLE_INT()       (CRPT->INTEN &= ~(CRPT_INTEN_AESIEN_Msk|CRPT_INTEN_AESERRIEN_Msk))

/**
  * @brief This macro gets AES interrupt flag.
  * @param None
  * @return AES interrupt flag.
  * \hideinitializer
  */
#define AES_GET_INT_FLAG()      (CRPT->INTSTS & (CRPT_INTSTS_AESIF_Msk|CRPT_INTSTS_AESERRIF_Msk))

/**
  * @brief This macro clears AES interrupt flag.
  * @param None
  * @return None
  * \hideinitializer
  */
#define AES_CLR_INT_FLAG()      (CRPT->INTSTS = (CRPT_INTSTS_AESIF_Msk|CRPT_INTSTS_AESERRIF_Msk))

/**
  * @brief This macro enables AES key protection.
  * @param None
  * @return None
  * \hideinitializer
  */
#define AES_ENABLE_KEY_PROTECT()  (CRPT->AES_CTL |= CRPT_AES_CTL_KEYPRT_Msk)

/**
  * @brief This macro disables AES key protection.
  * @param None
  * @return None
  * \hideinitializer
  */
#define AES_DISABLE_KEY_PROTECT() (CRPT->AES_CTL = (CRPT->AES_CTL & ~CRPT_AES_CTL_KEYPRT_Msk) | (0x16<<CRPT_AES_CTL_KEYUNPRT_Pos))

/**
  * @brief This macro enables TDES interrupt.
  * @param None
  * @return None
  * \hideinitializer
  */
#define TDES_ENABLE_INT()       (CRPT->INTEN |= (CRPT_INTEN_TDESIEN_Msk|CRPT_INTEN_TDESERRIEN_Msk))

/**
  * @brief This macro disables TDES interrupt.
  * @param None
  * @return None
  * \hideinitializer
  */
#define TDES_DISABLE_INT()      (CRPT->INTEN &= ~(CRPT_INTEN_TDESIEN_Msk|CRPT_INTEN_TDESERRIEN_Msk))

/**
  * @brief This macro gets TDES interrupt flag.
  * @param None
  * @return TDES interrupt flag.
  * \hideinitializer
  */
#define TDES_GET_INT_FLAG()     (CRPT->INTSTS & (CRPT_INTSTS_TDESIF_Msk|CRPT_INTSTS_TDESERRIF_Msk))

/**
  * @brief This macro clears TDES interrupt flag.
  * @param None
  * @return None
  * \hideinitializer
  */
#define TDES_CLR_INT_FLAG()     (CRPT->INTSTS = (CRPT_INTSTS_TDESIF_Msk|CRPT_INTSTS_TDESERRIF_Msk))

/**
  * @brief This macro enables TDES key protection.
  * @param None
  * @return None
  * \hideinitializer
  */
#define TDES_ENABLE_KEY_PROTECT()  (CRPT->TDES_CTL |= CRPT_TDES_CTL_KEYPRT_Msk)

/**
  * @brief This macro disables TDES key protection.
  * @param None
  * @return None
  * \hideinitializer
  */
#define TDES_DISABLE_KEY_PROTECT() (CRPT->TDES_CTL = (CRPT->TDES_CTL & ~CRPT_TDES_CTL_KEYPRT_Msk) | (0x16<<CRPT_TDES_CTL_KEYUNPRT_Pos))

/**
  * @brief This macro enables SHA interrupt.
  * @param None
  * @return None
  * \hideinitializer
  */
#define SHA_ENABLE_INT()        (CRPT->INTEN |= (CRPT_INTEN_SHAIEN_Msk|CRPT_INTEN_SHAERRIEN_Msk))

/**
  * @brief This macro disables SHA interrupt.
  * @param None
  * @return None
  * \hideinitializer
  */
#define SHA_DISABLE_INT()       (CRPT->INTEN &= ~(CRPT_INTEN_SHAIEN_Msk|CRPT_INTEN_SHAERRIEN_Msk))

/**
  * @brief This macro gets SHA interrupt flag.
  * @param None
  * @return SHA interrupt flag.
  * \hideinitializer
  */
#define SHA_GET_INT_FLAG()      (CRPT->INTSTS & (CRPT_INTSTS_SHAIF_Msk|CRPT_INTSTS_SHAERRIF_Msk))

/**
  * @brief This macro clears SHA interrupt flag.
  * @param None
  * @return None
  * \hideinitializer
  */
#define SHA_CLR_INT_FLAG()      (CRPT->INTSTS = (CRPT_INTSTS_SHAIF_Msk|CRPT_INTSTS_SHAERRIF_Msk))



/*---------------------------------------------------------------------------------------------------------*/
/*  Functions                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/

void PRNG_Open(uint32_t u32KeySize, uint32_t u32SeedReload, uint32_t u32Seed);
void PRNG_Start(void);
void PRNG_Read(uint32_t u32RandKey[]);
void AES_Open(uint32_t u32Channel, uint32_t u32EncDec, uint32_t u32OpMode, uint32_t u32KeySize, uint32_t u32SwapType);
void AES_Start(int32_t u32Channel, uint32_t u32DMAMode);
void AES_SetKey(uint32_t u32Channel, uint32_t au32Keys[], uint32_t u32KeySize);
void AES_SetInitVect(uint32_t u32Channel, uint32_t au32IV[]);
void AES_SetDMATransfer(uint32_t u32Channel, uint32_t u32SrcAddr, uint32_t u32DstAddr, uint32_t u32TransCnt);
void TDES_Open(uint32_t u32Channel, uint32_t u32EncDec, uint32_t u32OpMode, uint32_t u32SwapType);
void TDES_Start(int32_t u32Channel, uint32_t u32DMAMode);
void TDES_SetKey(uint32_t u32Channel, uint8_t au8Keys[3][8]);
void TDES_SetInitVect(uint32_t u32Channel, uint32_t u32IVH, uint32_t u32IVL);
void TDES_SetDMATransfer(uint32_t u32Channel, uint32_t u32SrcAddr, uint32_t u32DstAddr, uint32_t u32TransCnt);
void SHA_Open(uint32_t u32OpMode, uint32_t u32SwapType);
void SHA_Start(uint32_t u32DMAMode);
void SHA_SetDMATransfer(uint32_t u32SrcAddr, uint32_t u32TransCnt);
void SHA_Read(uint32_t u32Digest[]);


/*@}*/ /* end of group NUC472_442_CRYPTO_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_CRYPTO_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif  // __CRYPTO_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/

