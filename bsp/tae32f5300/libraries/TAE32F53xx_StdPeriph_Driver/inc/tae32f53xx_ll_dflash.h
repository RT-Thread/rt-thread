/**
  ******************************************************************************
  * @file    tae32f53xx_ll_dflash.h
  * @author  MCD Application Team
  * @brief   Header file for DataFlash module
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32F53XX_LL_DFLASH_H_
#define _TAE32F53XX_LL_DFLASH_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup DFLASH_LL
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup DFLASH_LL_Exported_Constants DFLASH LL Exported Constants
  * @brief    DFLASH LL Exported Constants
  * @{
  */

/** @defgroup DFLASH_Keys DFLASH Keys
  * @brief    DFLASH Keys
  * @{
  */
#define DFLASH_KEY1         0x32107654U /*!< DFLASH key1                                                                        */
#define DFLASH_KEY2         0xFEDCBA98U /*!< DFLASH key2: used with DFLASH_KEY1 to unlock the DFLASH Program/Read/Erase features*/
/**
  * @}
  */

/** @defgroup DFLASH_Flag_definition DFLASH Flag Definition
  * @brief    DFLASH Flag Definition
  * @{
  */
#define DFLASH_FLAG_BSY     DFLASH_SR_BSY   /*!< DFLASH flag BSY    */
#define DFLASH_FLAG_DIF     DFLASH_ISR_DIF  /*!< DFLASH flag DIF    */
#define DFLASH_FLAG_EIF     DFLASH_ISR_EIF  /*!< DFLASH flag EIF    */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup DFLASH_LL_Exported_Macros DFLASH LL Exported Macros
  * @brief    DFLASH LL Exported Macros
  * @{
  */

/**
  * @brief  Set the DFLASH_DR Register value.
  * @param  __DATA__ specifies the Data value.
  * @return None
  */
#define __LL_DFLASH_DATA_SET(__DATA__)              WRITE_REG(DFLASH->DR, (__DATA__))

/**
  * @brief  Get the TMR Counter Register value on runtime.
  * @return Value in the DFLASH_DR Register
  */
#define __LL_DFLASH_DATA_GET()                      READ_REG(DFLASH->DR)

/**
  * @brief  Check whether the specified status flag in DFLASH_SR Register is SET or not.
  * @param  __FLAG__ specifies the DFLASH status flag to check.
  *         This parameter can be ONE of the following values:
  *             @arg DFLASH_FLAG_BSY      : DFLASH BUSY Status
  * @return The new state of __FLAG__ (SET or RESET).
  */
#define __LL_DFLASH_STATUS_FLAG_GET(__FLAG__)       ((READ_BIT(DFLASH->SR, (__FLAG__)) == (__FLAG__)) ? SET : RESET)

/**
  * @brief  Check whether the specified interrupt pending flag in DFLASH_ISR Register is SET or not.
  * @param  __FLAG__ specifies the DFLASH interrupt pending flag to check.
  *         This parameter can be ONE of the following values:
  *             @arg DFLASH_FLAG_DIF    : Done
  *             @arg DFLASH_FLAG_EIF    : Operation Error
  * @return The new state of __FLAG__ (SET or RESET).
  */
#define __LL_DFLASH_PENDING_FLAG_GET(__FLAG__)      ((READ_BIT(DFLASH->ISR, (__FLAG__)) == (__FLAG__)) ? SET : RESET)

/**
  * @brief  Clear the DFLASH's Pending Register flag.
  * @param  __FLAG__ specifies the DFLASH pending flags to clear.
  *         This parameter can be any combination of the following values:
  *             @arg DFLASH_FLAG_DIF    : Done
  *             @arg DFLASH_FLAG_EIF    : Operation Error
  * @return None
  */
#define __LL_DFLASH_PENDING_FLAG_CLEAR(__FLAG__)    WRITE_REG(DFLASH->ISR, (__FLAG__))

/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup DFLASH_LL_Exported_Functions
  * @{
  */

/** @addtogroup DFLASH_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_DFLASH_WaitForLastOperation(uint32_t Timeout);
/**
  * @}
  */


/** @addtogroup DFLASH_LL_Exported_Functions_Group2
  * @{
  */

/**
  * @brief  Unlock the DFLASH Program/Read/Erase access.
  * @param  None
  * @return LL Status
  */
__STATIC_INLINE LL_StatusETypeDef LL_DFLASH_Unlock(void)
{
    if (READ_BIT(DFLASH->CR, DFLASH_CR_LOCK) != RESET) {
        /* Authorize the DFLASH Program/Read/Erase access */
        WRITE_REG(DFLASH->KEYR, DFLASH_KEY1);
        WRITE_REG(DFLASH->KEYR, DFLASH_KEY2);

        /* Verify DFLASH is unlocked */
        if (READ_BIT(DFLASH->CR, DFLASH_CR_LOCK_Msk) != RESET) {
            return LL_ERROR;
        }
    }

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Lock the DFLASH Program/Read/Erase access.
  * @param  None
  * @return LL Status
  */
__STATIC_INLINE LL_StatusETypeDef LL_DFLASH_Lock(void)
{
    /* Set the LOCK Bit to lock the DFLASH Program/Read/Erase access */
    SET_BIT(DFLASH->CR, DFLASH_CR_LOCK);

    /* Verify DFLASH is locked */
    if (READ_BIT(DFLASH->CR, DFLASH_CR_LOCK_Msk) == RESET) {
        return LL_ERROR;
    }

    /* Return function status */
    return LL_OK;
}

LL_StatusETypeDef LL_DFLASH_Program_Byte(uint32_t Address, uint8_t Data);
LL_StatusETypeDef LL_DFLASH_Program_Word(uint32_t Address, uint32_t Data);

LL_StatusETypeDef LL_DFLASH_Read_Byte(uint32_t Address, uint8_t *Data);
LL_StatusETypeDef LL_DFLASH_Read_Word(uint32_t Address, uint32_t *Data);

LL_StatusETypeDef LL_DFLASH_MassErase(void);
LL_StatusETypeDef LL_DFLASH_SectorErase(uint16_t Sector);
LL_StatusETypeDef LL_DFLASH_MultiSectorsErase(uint16_t Sector, uint16_t Num, uint16_t *SectorError);
/**
  * @}
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup DFLASH_LL_Private_Constants DFLASH LL Private Constants
  * @brief    DFLASH LL Private Constants
  * @{
  */

#define DFLASH_PROGRAM_ADDRESS_MASK      0x0000FFFFU    /*!< Program address mask                                       */
#define DFLASH_TIMEOUT_MAX_VALUE         300U           /*!< Max timeout for data flash operations. Default 300 ticks   */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup DFLASH_LL_Private_Macros DFLASH LL Private Macros
  * @brief    DFLASH LL Private Macros
  * @{
  */

/**
  * @brief  Judge is DFLASH address mask or not
  * @param  ADDRESS address to judge
  * @retval 0 isn't DFLASH address mask
  * @retval 1 is DFLASH address mask
  */
#define IS_DFLASH_ADDRESS_MASK(ADDRESS)             ((ADDRESS) < (0x4800U))

/**
  * @brief  Judge is DFLASH address check align or not
  * @param  ADDRESS address to judge
  * @retval 0 isn't DFLASH address check align
  * @retval 1 is DFLASH address check align
  */
#define IS_DFLASH_ADDRESS_CHECK_ALIGN(ADDRESS)      (((ADDRESS) & 0x3) == 0x00U)

/**
  * @brief  Judge is DFLASH sector or not
  * @param  SECTOR sector to judge
  * @retval 0 isn't DFLASH sector
  * @retval 1 is DFLASH sector
  */
#define IS_DFLASH_NB_SECTORS(SECTOR)                ((SECTOR) < 36U)

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F53XX_LL_DFLASH_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

