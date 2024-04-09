/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_flash_ex.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_HAL_FLASH_EX_H
#define STM32H7RSxx_HAL_FLASH_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal_def.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
  * @{
  */

/** @addtogroup FLASHEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @addtogroup FLASH_Exported_Types FLASH Exported Types
  * @{
  */
/**
  * @brief  FLASH Erase structure definition
  */
typedef struct
{
  uint32_t Index;     /*!< Index of the key.
                           This parameter can be a value between 0 and 31 */
  uint32_t Size;      /*!< Size of the key.
                           This parameter must be a value of @ref FLASH_Key_Size */
  uint32_t HDPLLevel; /*!< HDPL level of the key.
                           This parameter must be a value of @ref FLASH_KEY_Level */
} FLASH_KeyConfigTypeDef;

/**
  * @brief  FLASH CRC configuration structure definition
  */
typedef struct
{
  uint32_t TypeCRC;      /*!< CRC Selection Type.
                              This parameter can be a value of @ref FLASHEx_CRC_Selection_Type */

  uint32_t BurstSize;    /*!< CRC Burst Size.
                              This parameter can be a value of @ref FLASHEx_CRC_Burst_Size */

  uint32_t Sector;       /*!< Initial FLASH sector from which starts the CRC computation
                             This parameter must be a value between 0 and (max number of sector - 1)*/

  uint32_t NbSectors;    /*!< Number of sectors to be computed.
                              This parameter must be a value between 1 and
                              (max number of sectors - value of Initial sector)*/

  uint32_t CRCStartAddr; /*!< CRC Start address.
                              This parameter must be a value between begin address and end address of a bank */

  uint32_t CRCEndAddr;   /*!< CRC End address.
                              This parameter must be a value between CRC Start address and end address of a bank */

} FLASH_CRCInitTypeDef;

/**
  * @brief  FLASH ECC information structure definition
  */
typedef struct
{
  uint32_t Area;        /*!< Area from which an ECC was detected.
                             This parameter can be a value of @ref FLASHEx_ECC_Area  */
  uint32_t Address;     /*!< Flash address from which en ECC error was detected.
                             This parameter must be a value between begin address and end address of the Flash */
  uint32_t MasterID;    /*!< Master that initiated transfer on which error was detected
                             This parameter can be a value of @ref FLASHEx_ECC_Master */
} FLASH_EccInfoTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @addtogroup FLASHEx_Exported_Constants
  * @{
  */
/** @defgroup FLASH_Key_Size FLASH Option Bytes Key Size
  * @{
  */
#define FLASH_KEY_32_BITS           0x0000000U             /*!< Key size is 32 bits */
#define FLASH_KEY_64_BITS           FLASH_OBKCR_OBKSIZE_0  /*!< Key size is 64 bits */
#define FLASH_KEY_128_BITS          FLASH_OBKCR_OBKSIZE_1  /*!< Key size is 128 bits */
#define FLASH_KEY_256_BITS          FLASH_OBKCR_OBKSIZE    /*!< Key size is 256 bits */
/**
  * @}
  */

/** @defgroup FLASH_KEY_Level FLASH Option Bytes Key HDPL level
  * @{
  */
#define FLASH_KEY_LEVEL_CURRENT  0x00000000U           /*!< Key stored for the HDPL indicated in SBS_HDPLSR */
#define FLASH_KEY_LEVEL_NEXT     FLASH_OBKCR_NEXTKL_0  /*!< Key stored for the HDPL indicated in SBS_HDPLSR + 1 */
#define FLASH_KEY_LEVEL_PLUS_TWO FLASH_OBKCR_NEXTKL_1  /*!< Key stored for the HDPL indicated in SBS_HDPLSR + 2 */
/**
  * @}
  */

/** @defgroup FLASHEx_CRC_Selection_Type FLASH CRC Selection Type
  * @{
  */
#define FLASH_CRC_ADDR         0x00000000U                                      /*!< CRC selection type by address  */
#define FLASH_CRC_SECTORS      FLASH_CRCCR_CRC_BY_SECT                          /*!< CRC selection type by sectors  */
#define FLASH_CRC_BANK         (FLASH_CRCCR_ALL_SECT | FLASH_CRCCR_CRC_BY_SECT) /*!< CRC selection type all bank */
/**
  * @}
  */

/** @defgroup FLASHEx_CRC_Burst_Size FLASH CRC Burst Size
  * @{
  */
#define FLASH_CRC_BURST_SIZE_4    0x00000000U              /*!< Every burst has a size of 4 Flash words (64 Bytes) */
#define FLASH_CRC_BURST_SIZE_16   FLASH_CRCCR_CRC_BURST_0  /*!< Every burst has a size of 16 Flash words (256 Bytes) */
#define FLASH_CRC_BURST_SIZE_64   FLASH_CRCCR_CRC_BURST_1  /*!< Every burst has a size of 64 Flash words (1 kByte) */
#define FLASH_CRC_BURST_SIZE_256  FLASH_CRCCR_CRC_BURST    /*!< Every burst has a size of 256 Flash words (4 kBytes) */
/**
  * @}
  */

/** @defgroup FLASHEx_ECC_Area FLASH ECC Area
  * @{
  */
#define FLASH_ECC_AREA_USER_BANK1 0x00000000U  /*!< FLASH bank 1 area */
#define FLASH_ECC_AREA_SYSTEM     0x00000001U  /*!< System FLASH area */
#define FLASH_ECC_AREA_OTP        0x00000002U  /*!< FLASH OTP area */
#define FLASH_ECC_AREA_READ_ONLY  0x00000004U  /*!< FLASH Read-only area */
/**
  * @}
  */

/** @defgroup FLASHEx_ECC_Master FLASH ECC Master
  * @{
  */
#define FLASH_ECC_MASTER_CPU1     0x00000000U  /*!< ECC error occurs on a CPU1 transaction */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASHEx_Exported_Functions
  * @{
  */

/* Extended Program operation functions  *************************************/
/** @addtogroup FLASHEx_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase(const FLASH_EraseInitTypeDef *pEraseInit, uint32_t *SectorError);
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(const FLASH_EraseInitTypeDef *pEraseInit);
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(const FLASH_OBProgramInitTypeDef *pOBInit);
void              HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);
/**
  * @}
  */

/** @addtogroup FLASHEx_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef HAL_FLASHEx_OTPLockConfig(uint32_t OTPLBlock);
uint32_t          HAL_FLASHEx_GetOTPLock(void);
HAL_StatusTypeDef HAL_FLASHEx_KeyConfig(const FLASH_KeyConfigTypeDef *pKeyConfig, const uint32_t *pKey);
HAL_StatusTypeDef HAL_FLASHEx_GetKey(const FLASH_KeyConfigTypeDef *pKeyConfig, uint32_t *pKey);
HAL_StatusTypeDef HAL_FLASHEx_ComputeCRC(const FLASH_CRCInitTypeDef *pCRCInit, uint32_t *CRC_Result);
/**
  * @}
  */

/** @addtogroup FLASHEx_Exported_Functions_Group3
  * @{
  */
void              HAL_FLASHEx_EnableEccCorrectionInterrupt(void);
void              HAL_FLASHEx_DisableEccCorrectionInterrupt(void);
void              HAL_FLASHEx_EnableEccDetectionInterrupt(void);
void              HAL_FLASHEx_DisableEccDetectionInterrupt(void);
void              HAL_FLASHEx_GetEccInfo(FLASH_EccInfoTypeDef *pData);
void              HAL_FLASHEx_ECCD_IRQHandler(void);
void              HAL_FLASHEx_EccDetectionCallback(void);
void              HAL_FLASHEx_EccCorrectionCallback(void);
/**
  * @}
  */

/**
  * @}
  */

/* Private function ----------------------------------------------------------*/
/** @addtogroup FLASHEx_Private_Functions FLASHEx Private Functions
  * @{
  */
void FLASH_SectorErase(uint32_t Sector);
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASHEx_Private_Macros FLASH Private Macros
  *  @{
  */
#define IS_KEY_INDEX(VALUE)            ((VALUE) < 0x20U)

#define IS_KEY_SIZE(VALUE)             (((VALUE) == FLASH_KEY_32_BITS)  || ((VALUE) == FLASH_KEY_64_BITS) || \
                                        ((VALUE) == FLASH_KEY_128_BITS) || ((VALUE) == FLASH_KEY_256_BITS))

#define IS_KEY_HDPL_LEVEL(VALUE)       (((VALUE) == FLASH_KEY_LEVEL_CURRENT) || \
                                        ((VALUE) == FLASH_KEY_LEVEL_NEXT)    || \
                                        ((VALUE) == FLASH_KEY_LEVEL_PLUS_TWO))

#define IS_OB_OTP_BLOCK(VALUE)         ((VALUE) <= 0xFFFFU)

#define IS_FLASH_TYPE_CRC(VALUE)       (((VALUE) == FLASH_CRC_ADDR) || ((VALUE) == FLASH_CRC_SECTORS) ||\
                                        ((VALUE) == FLASH_CRC_BANK))

#define IS_FLASH_BURST_SIZE_CRC(VALUE) (((VALUE) == FLASH_CRC_BURST_SIZE_4) || ((VALUE) == FLASH_CRC_BURST_SIZE_16) ||\
                                        ((VALUE) == FLASH_CRC_BURST_SIZE_64) || ((VALUE) == FLASH_CRC_BURST_SIZE_256))
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

#endif /* STM32H7RSxx_HAL_FLASH_EX_H */
