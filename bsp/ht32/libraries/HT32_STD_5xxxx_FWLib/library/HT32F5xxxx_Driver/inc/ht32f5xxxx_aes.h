/*********************************************************************************************************//**
 * @file    ht32f5xxxx_aes.h
 * @version $Rev:: 7390         $
 * @date    $Date:: 2023-12-12 #$
 * @brief   The header file of the ADC library.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F5XXXX_AES_H
#define __HT32F5XXXX_AES_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup AES
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup AES_Exported_Types AES exported types
  * @{
  */

/**
 * @brief  Definition of AES Init Structure
 */
typedef struct
{
  u16 AES_KeySize;
  u16 AES_Dir;
  u16 AES_Mode;
  u16 AES_Swap;
} AES_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup AES_Exported_Constants AES exported constants
  * @{
  */

#define IS_AES(AES)                        (AES == HT_AES)

/* Definitions of AES key size                                                                              */
#define AES_KEYSIZE_128B                   ((u32)0x00000000)
#define IS_AES_KEY_SIZE1(SIZE)             (SIZE == AES_KEYSIZE_128B)

#if (LIBCFG_AES_KEYSIZE_256B)
#define AES_KEYSIZE_192B                   ((u32)0x00000020)
#define AES_KEYSIZE_256B                   ((u32)0x00000040)
#define IS_AES_KEY_SIZE2(SIZE)             ((SIZE == AES_KEYSIZE_192B) || (SIZE == AES_KEYSIZE_256B))
#else
#define IS_AES_KEY_SIZE2(SIZE)             (0)
#endif

#define IS_AES_KEY_SIZE(SIZE)              (IS_AES_KEY_SIZE1(SIZE) || IS_AES_KEY_SIZE2(SIZE))

/* Definitions of AES direction                                                                             */
typedef enum
{
  AES_DIR_ENCRYPT                    =0,
  AES_DIR_DECRYPT                    =2
} AES_DIR_Enum;

#define IS_AES_DIR(DIR) ((DIR == AES_DIR_ENCRYPT) || (DIR == AES_DIR_DECRYPT))

/* Definitions of AES mode                                                                                  */
#define AES_MODE_ECB                       ((u32)0x00000000)
#define AES_MODE_CBC                       ((u32)0x00000004)
#define AES_MODE_CTR                       ((u32)0x00000008)

#define IS_AES_MODE(MODE) ((MODE == AES_MODE_ECB) || (MODE == AES_MODE_CBC) || (MODE == AES_MODE_CTR))

/* Definitions of AES key start                                                                             */
#define AES_KEYSTART_DISABLE               ((u32)0x00000000)
#define AES_KEYSTART_ENABLE                ((u32)0x00000010)

#define IS_AES_KEYSTART(KEYSTART) ((KEYSTART == AES_KEYSTART_DISABLE) || (KEYSTART == AES_KEYSTART_ENABLE))

/* Definitions of AES swap                                                                                  */
#define AES_SWAP_DISABLE                   ((u32)0x00000000)
#define AES_SWAP_ENABLE                    ((u32)0x00000100)

#define IS_AES_SWAP(SWAP) ((SWAP == AES_SWAP_DISABLE) || (SWAP == AES_SWAP_ENABLE))

/* Definitions of AES flush                                                                                 */
#define AES_FLUSH_DISABLE                  ((u32)0x00000000)
#define AES_FLUSH_ENABLE                   ((u32)0x00000400)

#define IS_AES_FLUSH(FLUSH) ((FLUSH == AES_FLUSH_DISABLE) || (FLUSH == AES_FLUSH_ENABLE))

/* Definitions of AES Enable                                                                                */
#define AES_DISABLE                        ((u32)0x00000000)
#define AES_ENABLE                         ((u32)0x00000001)

#define IS_AES_CMD(CMD) ((CMD == AES_DISABLE) || (CMD == AES_ENABLE))

/* Definitions of AES status                                                                                */
#define AES_SR_IFEMPTY                     ((u32)0x00000001)
#define AES_SR_IFNFULL                     ((u32)0x00000002)
#define AES_SR_OFNEMPTY                    ((u32)0x00000004)
#define AES_SR_OFFULL                      ((u32)0x00000008)
#define AES_SR_BUSY                        ((u32)0x00000010)

#define IS_AES_STATUS(STATUS)              ((STATUS == AES_SR_IFEMPTY)  || \
                                            (STATUS == AES_SR_IFNFULL)  || \
                                            (STATUS == AES_SR_OFNEMPTY) || \
                                            (STATUS == AES_SR_OFFULL)   || \
                                            (STATUS == AES_SR_BUSY))

/* Definitions of AES PDMA                                                                                  */
#define AES_PDMA_IFDMAEN                   ((u32)0x00000001)
#define AES_PDMA_OFDMAEN                   ((u32)0x00000002)

#define IS_AES_PDMA(AES_PDMA)              ((AES_PDMA == AES_PDMA_IFDMAEN) || (AES_PDMA == AES_PDMA_OFDMAEN))

/* Definitions of AES Interrupt Status                                                                      */
#define AES_INTSR_IFINT                    ((u32)0x00000001)
#define AES_INTSR_OFINT                    ((u32)0x00000002)

#define IS_AES_INTSR(AES_INSR)             ((AES_INSR == AES_INTSR_IFINT) || (AES_INSR == AES_INTSR_OFINT))

/* Definitions of AES interrupt enable                                                                      */
#define AES_IER_IFINTEN                    ((u32)0x00000001)
#define AES_IER_OFINTEN                    ((u32)0x00000002)

#define IS_AES_IER(ARS_IER)                ((ARS_IER == AES_IER_IFINTEN) || (ARS_IER == AES_IER_OFINTEN))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup AES_Exported_Functions AES exported functions
  * @{
  */
void AES_ECB_Init(HT_AES_TypeDef* HT_AESn, AES_InitTypeDef* AES_InitStruct);
void AES_CBC_Init(HT_AES_TypeDef* HT_AESn, AES_InitTypeDef* AES_InitStruct);
void AES_CTR_Init(HT_AES_TypeDef* HT_AESn, AES_InitTypeDef* AES_InitStruct);
void AES_SetKeyTable(HT_AES_TypeDef* HT_AESn, u32 *Key, u32 keySize);
ErrStatus _AES_CryptData(HT_AES_TypeDef* HT_AESn, AES_DIR_Enum dir, u32 *iv, u32 length, u32 *inputData, u32 *outputData);
#define AES_ECB_CryptData(a, b, c, d, e)     _AES_CryptData(a, b, NULL, c, d, e)
#define AES_CBC_CryptData                    _AES_CryptData
#define AES_CTR_CryptData(a, b, c, d, e)     _AES_CryptData(a, AES_DIR_ENCRYPT, b, c, d, e)
#if 0
ErrStatus AES_ECB_CryptData(HT_AES_TypeDef* HT_AESn, AES_DIR_Enum mode, u32 length, u32 *inputData, u32 *outputData);
ErrStatus AES_CBC_CryptData(HT_AES_TypeDef* HT_AESn, AES_DIR_Enum mode, u32 *iv, u32 length, u32 *inputData, u32 *outputData);
ErrStatus AES_CTR_CryptData(HT_AES_TypeDef* HT_AESn, u32 *iv, u32 length, u32 *inputData, u32 *outputData);
#endif

void AES_StartKey(HT_AES_TypeDef* HT_AESn);
void AES_DeInit(HT_AES_TypeDef* HT_AESn);
void AES_FIFOFlush(HT_AES_TypeDef* HT_AESn);
void AES_Cmd(HT_AES_TypeDef* HT_AESn, ControlStatus NewState);
FlagStatus AES_GetStatus(HT_AES_TypeDef* HT_AESn, u32 AES_Status);
void AES_PDMACmd(HT_AES_TypeDef* HT_AESn, u32 AES_PDMA_xFDMAEN, ControlStatus NewState);
FlagStatus AES_GetIntStatus(HT_AES_TypeDef* HT_AESn, u32 AES_INTSR_x);
void AES_IntConfig(HT_AES_TypeDef* HT_AESn, u32 AES_IER_x, ControlStatus NewState);
void AES_SetInputData(HT_AES_TypeDef* HT_AESn, uc32 AES_Data);
u32 AES_GetOutputData(HT_AES_TypeDef* HT_AESn);
void AES_SetVectorTable(HT_AES_TypeDef* HT_AESn, u32 *Vector);
void AESCore_IRQHandler(HT_AES_TypeDef* HT_AESn);
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
