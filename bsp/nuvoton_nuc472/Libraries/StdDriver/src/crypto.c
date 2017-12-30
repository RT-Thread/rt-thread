/**************************************************************************//**
 * @file     crypto.c
 * @version  V1.10
 * $Revision: 12 $
 * $Date: 15/11/06 2:17p $
 * @brief  Cryptographic Accelerator driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <string.h>
#include "NUC472_442.h"

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_CRYPTO_Driver CRYPTO Driver
  @{
*/


/** @addtogroup NUC472_442_CRYPTO_EXPORTED_FUNCTIONS CRYPTO Exported Functions
  @{
*/

/// @cond HIDDEN_SYMBOLS

static uint32_t g_AES_CTL[4];
static uint32_t g_TDES_CTL[4];

/// @endcond HIDDEN_SYMBOLS

/**
  * @brief  Open PRNG function
  * @param[in]  u32KeySize is PRNG key size, including:
  *         - \ref PRNG_KEY_SIZE_64
  *         - \ref PRNG_KEY_SIZE_128
  *         - \ref PRNG_KEY_SIZE_192
  *         - \ref PRNG_KEY_SIZE_256
  * @param[in]  u32SeedReload is PRNG seed reload or not, including:
  *         - \ref PRNG_SEED_CONT
  *         - \ref PRNG_SEED_RELOAD
  * @param[in]  u32Seed  The new seed. Only valid when u32SeedReload is PRNG_SEED_RELOAD.
  * @return None
  */
void PRNG_Open(uint32_t u32KeySize, uint32_t u32SeedReload, uint32_t u32Seed)
{
    if (u32SeedReload)
        CRPT->PRNG_SEED = u32Seed;

    CRPT->PRNG_CTL =  (u32KeySize << CRPT_PRNG_CTL_KEYSZ_Pos) |
                      (u32SeedReload << CRPT_PRNG_CTL_SEEDRLD_Pos);
}

/**
  * @brief  Start to generate one PRNG key.
  * @param None
  * @return None
  */
void PRNG_Start(void)
{
    CRPT->PRNG_CTL |= CRPT_PRNG_CTL_START_Msk;
}

/**
  * @brief  Read the PRNG key.
  * @param[out]  u32RandKey  The key buffer to store newly generated PRNG key.
  * @return None
  */
void PRNG_Read(uint32_t u32RandKey[])
{
    int  i, wcnt;

    wcnt = (((CRPT->PRNG_CTL & CRPT_PRNG_CTL_KEYSZ_Msk)>>CRPT_PRNG_CTL_KEYSZ_Pos)+1)*2;
    for (i = 0; i < wcnt; i++)
        u32RandKey[i] = *(uint32_t *)((uint32_t)&(CRPT->PRNG_KEY0) + (i * 4));
}


/**
  * @brief  Open AES encrypt/decrypt function.
  * @param[in]  u32Channel   AES channel. Must be 0~3.
  * @param[in]  u32EncDec    1: AES encode;  0: AES decode
  * @param[in]  u32OpMode    AES operation mode, including:
  *         - \ref AES_MODE_ECB
  *         - \ref AES_MODE_CBC
  *         - \ref AES_MODE_CFB
  *         - \ref AES_MODE_OFB
  *         - \ref AES_MODE_CTR
  *         - \ref AES_MODE_CBC_CS1
  *         - \ref AES_MODE_CBC_CS2
  *         - \ref AES_MODE_CBC_CS3
  * @param[in]  u32KeySize is AES key size, including:
  *         - \ref AES_KEY_SIZE_128
  *         - \ref AES_KEY_SIZE_192
  *         - \ref AES_KEY_SIZE_256
  * @param[in]  u32SwapType is AES input/output data swap control, including:
  *         - \ref AES_NO_SWAP
  *         - \ref AES_OUT_SWAP
  *         - \ref AES_IN_SWAP
  *         - \ref AES_IN_OUT_SWAP
  * @return None
  */
void AES_Open(uint32_t u32Channel, uint32_t u32EncDec,
              uint32_t u32OpMode, uint32_t u32KeySize, uint32_t u32SwapType)
{
    CRPT->AES_CTL = (u32Channel << CRPT_AES_CTL_CHANNEL_Pos) |
                    (u32EncDec << CRPT_AES_CTL_ENCRPT_Pos) |
                    (u32OpMode << CRPT_AES_CTL_OPMODE_Pos) |
                    (u32KeySize << CRPT_AES_CTL_KEYSZ_Pos) |
                    (u32SwapType << CRPT_AES_CTL_OUTSWAP_Pos);
    g_AES_CTL[u32Channel] = CRPT->AES_CTL;
}

/**
  * @brief  Start AES encrypt/decrypt
  * @param[in]  u32Channel  AES channel. Must be 0~3.
  * @param[in]  u32DMAMode  AES DMA control, including:
  *         - \ref CRYPTO_DMA_ONE_SHOT   One shop AES encrypt/decrypt.
  *         - \ref CRYPTO_DMA_CONTINUE   Continuous AES encrypt/decrypt.
  *         - \ref CRYPTO_DMA_LAST       Last AES encrypt/decrypt of a series of AES_Start.
  * @return None
  */
void AES_Start(int32_t u32Channel, uint32_t u32DMAMode)
{
    CRPT->AES_CTL = g_AES_CTL[u32Channel];
    CRPT->AES_CTL |= CRPT_AES_CTL_START_Msk | (u32DMAMode << CRPT_AES_CTL_DMALAST_Pos);
}

/**
  * @brief  Set AES keys
  * @param[in]  u32Channel  AES channel. Must be 0~3.
  * @param[in]  au32Keys    An word array contains AES keys.
  * @param[in]  u32KeySize is AES key size, including:
  *         - \ref AES_KEY_SIZE_128
  *         - \ref AES_KEY_SIZE_192
  *         - \ref AES_KEY_SIZE_256
  * @return None
  */
void AES_SetKey(uint32_t u32Channel, uint32_t au32Keys[], uint32_t u32KeySize)
{
    int       i, wcnt;
    uint32_t  *key_ptr;

    key_ptr = (uint32_t *)((uint32_t)&CRPT->AES0_KEY0 + (u32Channel * 0x3C));
    wcnt = 4 + u32KeySize*2;
    for (i = 0; i < wcnt; i++, key_ptr++)
        *key_ptr = au32Keys[i];
}

/**
  * @brief  Set AES initial vectors
  * @param[in]  u32Channel  AES channel. Must be 0~3.
  * @param[in]  au32IV      A four entry word array contains AES initial vectors.
  * @return None
  */
void AES_SetInitVect(uint32_t u32Channel, uint32_t au32IV[])
{
    int       i;
    uint32_t  *key_ptr;

    key_ptr = (uint32_t *)((uint32_t)&CRPT->AES0_IV0 + (u32Channel * 0x3C));
    for (i = 0; i < 4; i++, key_ptr++)
        *key_ptr = au32IV[i];
}

/**
  * @brief  Set AES DMA transfer configuration.
  * @param[in]  u32Channel   AES channel. Must be 0~3.
  * @param[in]  u32SrcAddr   AES DMA source address
  * @param[in]  u32DstAddr   AES DMA destination address
  * @param[in]  u32TransCnt  AES DMA transfer byte count
  * @return None
  */
void AES_SetDMATransfer(uint32_t u32Channel, uint32_t u32SrcAddr,
                        uint32_t u32DstAddr, uint32_t u32TransCnt)
{
    *(uint32_t *)((uint32_t)&CRPT->AES0_SADDR + (u32Channel * 0x3C)) = u32SrcAddr;
    *(uint32_t *)((uint32_t)&CRPT->AES0_DADDR + (u32Channel * 0x3C)) = u32DstAddr;
    *(uint32_t *)((uint32_t)&CRPT->AES0_CNT + (u32Channel * 0x3C)) = u32TransCnt;
}

/**
  * @brief  Open TDES encrypt/decrypt function.
  * @param[in]  u32Channel   TDES channel. Must be 0~3.
  * @param[in]  u32EncDec    1: TDES encode; 0: TDES decode
  * @param[in]  u32OpMode    TDES operation mode, including:
  *         - \ref TDES_MODE_ECB
  *         - \ref TDES_MODE_CBC
  *         - \ref TDES_MODE_CFB
  *         - \ref TDES_MODE_OFB
  *         - \ref TDES_MODE_CTR
  * @param[in]  u32SwapType is TDES input/output data swap control and word swap control, including:
  *         - \ref TDES_NO_SWAP
  *         - \ref TDES_WHL_SWAP
  *         - \ref TDES_OUT_SWAP
  *         - \ref TDES_OUT_WHL_SWAP
  *         - \ref TDES_IN_SWAP
  *         - \ref TDES_IN_WHL_SWAP
  *         - \ref TDES_IN_OUT_SWAP
  *         - \ref TDES_IN_OUT_WHL_SWAP
  * @return None
  */
void TDES_Open(uint32_t u32Channel, uint32_t u32EncDec, uint32_t u32OpMode, uint32_t u32SwapType)
{
    g_TDES_CTL[u32Channel] = (u32Channel << CRPT_TDES_CTL_CHANNEL_Pos) |
                             (u32EncDec << CRPT_TDES_CTL_ENCRPT_Pos) |
                             u32OpMode | CRPT_TDES_CTL_3KEYS_Msk |
                             (u32SwapType << CRPT_TDES_CTL_BLKSWAP_Pos);
}

/**
  * @brief  Start TDES encrypt/decrypt
  * @param[in]  u32Channel  TDES channel. Must be 0~3.
  * @param[in]  u32DMAMode  TDES DMA control, including:
  *         - \ref CRYPTO_DMA_ONE_SHOT   One shop TDES encrypt/decrypt.
  *         - \ref CRYPTO_DMA_CONTINUE   Continuous TDES encrypt/decrypt.
  *         - \ref CRYPTO_DMA_LAST       Last TDES encrypt/decrypt of a series of TDES_Start.
  * @return None
  */
void TDES_Start(int32_t u32Channel, uint32_t u32DMAMode)
{
    g_TDES_CTL[u32Channel] |= CRPT_TDES_CTL_START_Msk | (u32DMAMode << CRPT_TDES_CTL_DMALAST_Pos);
    CRPT->TDES_CTL = g_TDES_CTL[u32Channel];
}

/**
  * @brief  Set TDES keys
  * @param[in]  u32Channel  TDES channel. Must be 0~3.
  * @param[in]  au8Keys     The TDES keys.
  * @return None
  */
void TDES_SetKey(uint32_t u32Channel, uint8_t au8Keys[3][8])
{
    int         i;
    uint8_t     *pu8TKey;

    pu8TKey = (uint8_t *)((uint32_t)&CRPT->TDES0_KEY1H + (0x40 * u32Channel));
    for (i = 0; i < 3; i++, pu8TKey+=8)
        memcpy(pu8TKey, &au8Keys[i][0], 8);
}

/**
  * @brief  Set TDES initial vectors
  * @param[in]  u32Channel  TDES channel. Must be 0~3.
  * @param[in]  u32IVH      TDES initial vector high word.
  * @param[in]  u32IVL      TDES initial vector low word.
  * @return None
  */
void TDES_SetInitVect(uint32_t u32Channel, uint32_t u32IVH, uint32_t u32IVL)
{
    *(uint32_t *)((uint32_t)&CRPT->TDES0_IVH + 0x40 * u32Channel) = u32IVH;
    *(uint32_t *)((uint32_t)&CRPT->TDES0_IVL + 0x40 * u32Channel) = u32IVL;
}

/**
  * @brief  Set TDES DMA transfer configuration.
  * @param[in]  u32Channel   TDES channel. Must be 0~3.
  * @param[in]  u32SrcAddr   TDES DMA source address
  * @param[in]  u32DstAddr   TDES DMA destination address
  * @param[in]  u32TransCnt  TDES DMA transfer byte count
  * @return None
  */
void TDES_SetDMATransfer(uint32_t u32Channel, uint32_t u32SrcAddr,
                         uint32_t u32DstAddr, uint32_t u32TransCnt)
{
    *(uint32_t *)((uint32_t)&CRPT->TDES0_SADDR + (u32Channel * 0x40)) = u32SrcAddr;
    *(uint32_t *)((uint32_t)&CRPT->TDES0_DADDR + (u32Channel * 0x40)) = u32DstAddr;
    *(uint32_t *)((uint32_t)&CRPT->TDES0_CNT + (u32Channel * 0x40)) = u32TransCnt;
}

/**
  * @brief  Open SHA encrypt function.
  * @param[in]  u32OpMode   SHA operation mode, including:
  *         - \ref SHA_MODE_SHA1
  *         - \ref SHA_MODE_SHA224
  *         - \ref SHA_MODE_SHA256
  * @param[in]  u32SwapType is SHA input/output data swap control, including:
  *         - \ref SHA_NO_SWAP
  *         - \ref SHA_OUT_SWAP
  *         - \ref SHA_IN_SWAP
  *         - \ref SHA_IN_OUT_SWAP
  * @return None
  */
void SHA_Open(uint32_t u32OpMode, uint32_t u32SwapType)
{
    CRPT->SHA_CTL = (u32OpMode << CRPT_SHA_CTL_OPMODE_Pos) |
                    (u32SwapType << CRPT_SHA_CTL_OUTSWAP_Pos);
}

/**
  * @brief  Start SHA encrypt
  * @param[in]  u32DMAMode  TDES DMA control, including:
  *         - \ref CRYPTO_DMA_ONE_SHOT   One shop SHA encrypt.
  *         - \ref CRYPTO_DMA_CONTINUE   Continuous SHA encrypt.
  *         - \ref CRYPTO_DMA_LAST       Last SHA encrypt of a series of SHA_Start.
  * @return None
  */
void SHA_Start(uint32_t u32DMAMode)
{
    CRPT->SHA_CTL &= ~(0x7 << CRPT_SHA_CTL_DMALAST_Pos);
    CRPT->SHA_CTL |= CRPT_SHA_CTL_START_Msk | (u32DMAMode << CRPT_SHA_CTL_DMALAST_Pos);
}

/**
  * @brief  Set SHA DMA transfer
  * @param[in]  u32SrcAddr   SHA DMA source address
  * @param[in]  u32TransCnt  SHA DMA transfer byte count
  * @return None
  */
void SHA_SetDMATransfer(uint32_t u32SrcAddr, uint32_t u32TransCnt)
{
    CRPT->SHA_SADDR = u32SrcAddr;
    CRPT->SHA_DMACNT = u32TransCnt;
}

/**
  * @brief  Read the SHA digest.
  * @param[out]  u32Digest  The SHA encrypt output digest.
  * @return None
  */
void SHA_Read(uint32_t u32Digest[])
{
    uint32_t  i, wcnt;

    i = (CRPT->SHA_CTL & CRPT_SHA_CTL_OPMODE_Msk) >> CRPT_SHA_CTL_OPMODE_Pos;
    if (i == SHA_MODE_SHA1)
        wcnt = 5;
    else if (i == SHA_MODE_SHA224)
        wcnt = 7;
    else
        wcnt = 8;

    for (i = 0; i < wcnt; i++)
        u32Digest[i] = *(uint32_t *)((uint32_t)&(CRPT->SHA_DGST0) + (i * 4));
}


/*@}*/ /* end of group NUC472_442_CRYPTO_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_CRYPTO_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/

