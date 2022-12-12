/**
  ******************************************************************************
  * @file    tae32f53xx_ll_flash.h
  * @author  MCD Application Team
  * @brief   Head file for FLASH module LL driver.
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
#ifndef _TAE32F53XX_LL_FLASH_H_
#define _TAE32F53XX_LL_FLASH_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup FLASH_LL
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Types FLASH LL Exported Types
  * @brief    Set the read protection level
  * @{
  */

/**
    @brief    Set the read protection level
*/
typedef enum {
    FLASH_RDP_LEVEL_0 = 0xAAU,        /*!< FLASH Read Protection Level 0 */
    FLASH_RDP_LEVEL_1 = 0xFFU,        /*!< FLASH Read Protection Level 1 */
    FLASH_RDP_LEVEL_2 = 0xCCU,        /*!< FLASH Read Protection Level 2, Warning: When enabling read protection
                                           level 2,it's no more possible to go back to level 1 or 0 */
} FLASH_RDPLVETypeDef;


/**
    @brief  Write Protection State
  */
typedef enum {
    FLASH_WRPSTATE_DISABLE  = 0x00U,  /*!< Disable the write protection of the desired sections   */
    FLASH_WRPSTATE_ENABLE   = 0x01U,  /*!< Enable the write protection of the desired sections    */
} FLASH_WRPSTETypeDef;

/**
  * @brief  Write Permission Area Control. Each AREA control 8 sections (refer to one area) in Main Memory Array
  */
typedef enum {
    FLASH_WRP_AREA_1          =      0x00000001,          /*!< FLASH Write Protection Area 1      */
    FLASH_WRP_AREA_2          =      0x00000002,          /*!< FLASH Write Protection Area 2      */
    FLASH_WRP_AREA_3          =      0x00000004,          /*!< FLASH Write Protection Area 3      */
    FLASH_WRP_AREA_4          =      0x00000008,          /*!< FLASH Write Protection Area 4      */
    FLASH_WRP_AREA_5          =      0x00000010,          /*!< FLASH Write Protection Area 5      */
    FLASH_WRP_AREA_6          =      0x00000020,          /*!< FLASH Write Protection Area 6      */
    FLASH_WRP_AREA_7          =      0x00000040,          /*!< FLASH Write Protection Area 7      */
    FLASH_WRP_AREA_8          =      0x00000080,          /*!< FLASH Write Protection Area 8      */
    FLASH_WRP_AREA_9          =      0x00000100,          /*!< FLASH Write Protection Area 9      */
    FLASH_WRP_AREA_10         =      0x00000200,          /*!< FLASH Write Protection Area 10     */
    FLASH_WRP_AREA_11         =      0x00000400,          /*!< FLASH Write Protection Area 11     */
    FLASH_WRP_AREA_12         =      0x00000800,          /*!< FLASH Write Protection Area 12     */
    FLASH_WRP_AREA_13         =      0x00001000,          /*!< FLASH Write Protection Area 13     */
    FLASH_WRP_AREA_14         =      0x00002000,          /*!< FLASH Write Protection Area 14     */
    FLASH_WRP_AREA_15         =      0x00004000,          /*!< FLASH Write Protection Area 15     */
    FLASH_WRP_AREA_16         =      0x00008000,          /*!< FLASH Write Protection Area 16     */
    FLASH_WRP_AREA_17         =      0x00010000,          /*!< FLASH Write Protection Area 17     */
    FLASH_WRP_AREA_18         =      0x00020000,          /*!< FLASH Write Protection Area 18     */
    FLASH_WRP_AREA_19         =      0x00040000,          /*!< FLASH Write Protection Area 19     */
    FLASH_WRP_AREA_20         =      0x00080000,          /*!< FLASH Write Protection Area 20     */
    FLASH_WRP_AREA_ALL        =      0x000FFFFF,          /*!< FLASH Write Protection Area ALL    */
    FLASH_WRP_AREA_Msk        =      FLASH_WRP_AREA_ALL,  /*!< FLASH Write Protection Area Mask   */
} FLASH_WRPAREAETypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Constants FLASH LL Exported Constants
  * @brief    FLASH LL Exported Constants
  * @{
  */

/** @defgroup FLASH_Error_Codes FLASH Error Codes
  * @{
  */
#define FLASH_ERROR_NONE                0x00U       /*!< No error               */
#define FLASH_ERROR_OPT                 0x01U       /*!< Operation error        */
#define FLASH_ERROR_WRP                 0x02U       /*!< Write protection error */
#define FLASH_ERROR_RDP                 0x04U       /*!< Read protection error  */
#define FLASH_ERROR_ECC                 0x08U       /*!< ECC validity error     */
/**
  * @}
  */


/** @defgroup FLASH_Program_Width FLASH Program Width
  * @{
  */
#define FLASH_PROG_DATA_WIDTH           16U         /*!< Data width in a single programming operation.Number in bytes   */
/**
  * @}
  */


/** @defgroup FLASH_Keys FLASH Keys
  * @{
  */
#define FLASH_KEY1                      0x32107654U /*!< FLASH key1                                                   */
#define FLASH_KEY2                      0xFEDCBA98U /*!< FLASH key2: used with FLASH_KEY1 
                                                         to unlock the FLASH Program/Erase features                   */

#define FLASH_OP_KEY                    0x50035003U /*!< FLASH Operation Protection Key : 
                                                         Unlock the operation of FLASH Read/Write Protection Register */

#define FLASH_PWR_KEY                   0x50030000U /*!< FLASH pwr key: unlock the FLASH Standby/Wakeup features      */
/**
  * @}
  */

/** @defgroup FLASH_Flag_definition FLASH Flag Definition
  * @{
  */
#define FLASH_FLAG_BSY                  FLASH_SR_BSY        /*!< FLASH Flag BSY     */
#define FLASH_FLAG_DIF                  FLASH_ISR_DIF       /*!< FLASH Flag DIF     */
#define FLASH_FLAG_ECCEIF               FLASH_ISR_ECCEIF    /*!< FLASH Flag ECCEIF  */
#define FLASH_FLAG_RPEIF                FLASH_ISR_RPEIF     /*!< FLASH Flag RPEIF   */
#define FLASH_FLAG_WPEIF                FLASH_ISR_WPEIF     /*!< FLASH Flag WPEIF   */
#define FLASH_FLAG_OPTEIF               FLASH_ISR_OPTEIF    /*!< FLASH Flag OPEIF   */
/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Macros FLASH LL Exported Macros
  * @brief    FLASH LL Exported Macros
  * @{
  */

/**
  * @brief  Enable FLASH I BUS Prefetch feature.
  * @note   Prefetch feature <b>should not be enabled</b> when CPU frequency is lower than <b>40MHz</b>.
  * @param  None
  * @return None
  */
#define __LL_FLASH_I_BUS_PREFETCH_ENABLE()          SET_BIT(FLASH->CR, FLASH_CR_IBPE)

/**
  * @brief  Disable FLASH I BUS Prefetch feature.
  * @param  None
  * @return None
  */
#define __LL_FLASH_I_BUS_PREFETCH_DISABLE()         CLEAR_BIT(FLASH->CR, FLASH_CR_IBPE)

/**
  * @brief  Enable FLASH D BUS Prefetch feature.
  * @note   Prefetch feature <b>should not be enabled</b> when CPU frequency is lower than <b>40MHz</b>.
  * @param  None
  * @return None
  */
#define __LL_FLASH_D_BUS_PREFETCH_ENABLE()          SET_BIT(FLASH->CR, FLASH_CR_DBPE)

/**
  * @brief  Disable FLASH D BUS Prefetch feature.
  * @param  None
  * @return None
  */
#define __LL_FLASH_D_BUS_PREFETCH_DISABLE()         CLEAR_BIT(FLASH->CR, FLASH_CR_DBPE)

/**
  * @brief  FLASH Standby.
  *         Flash will enter standby mode aim for low power mode.
  * @param  None
  * @return None
  */
#define __LL_FLASH_STANDBY_ENABLE()                 do{ WRITE_REG(FLASH->LPR, FLASH_PWR_KEY);   \
                                                        SET_BIT(FLASH->LPR, FLASH_LPR_STDBY);   \
                                                      } while (0);

/**
  * @brief  FLASH Wakeup.
  *         Flash will exit from standby mode.
  * @param  None
  * @return None
  */
#define __LL_FLASH_WAKEUP_ENABLE()                  do{ WRITE_REG(FLASH->LPR, FLASH_PWR_KEY);   \
                                                        SET_BIT(FLASH->LPR, FLASH_LPR_WKUP);    \
                                                      } while (0);

/**
  * @brief  Check whether the specified status flag in FLASH_SR Register is SET or not.
  * @param  __FLAG__ specifies the FLASH status flag to check.
  *         This parameter can be ONE of the following values:
  *             @arg FLASH_FLAG_BSY      : FLASH BUSY Status
  * @return The new state of __FLAG__ (SET or RESET).
  */
#define __LL_FLASH_GET_STATUS_FLAG(__FLAG__)        ((READ_BIT(FLASH->SR, (__FLAG__)) == (__FLAG__)) ? SET : RESET)

/**
  * @brief  Check whether the specified interrupt pending flag in FLASH_ISR Register is SET or not.
  * @param  __FLAG__ specifies the FLASH interrupt pending flag to check.
  *         This parameter can be ONE of the following values:
  *             @arg FLASH_FLAG_DIF     : Done
  *             @arg FLASH_FLAG_ECCEIF  : ECC Error
  *             @arg FLASH_FLAG_RPEIF   : Read Protection Error
  *             @arg FLASH_FLAG_WPEIF   : Write Protection Error
  *             @arg FLASH_FLAG_OPTEIF  : Operation Error
  * @return The new state of __FLAG__ (SET or RESET).
  */
#define __LL_FLASH_GET_PENDING_FLAG(__FLAG__)      ((READ_BIT(FLASH->ISR, (__FLAG__)) == (__FLAG__)) ? SET : RESET)

/**
  * @brief  Clear the FLASH's Pending Register flag.
  * @param  __FLAG__ specifies the FLASH pending flags to clear.
  *         This parameter can be any combination of the following values:
  *             @arg FLASH_FLAG_DIF     : Done
  *             @arg FLASH_FLAG_ECCEIF  : ECC Error
  *             @arg FLASH_FLAG_RPEIF   : Read Protection Error
  *             @arg FLASH_FLAG_WPEIF   : Write Protection Error
  *             @arg FLASH_FLAG_OPTEIF  : Operation Error
  * @return The new state of __FLAG__ (SET or RESET).
  */
#define __LL_FLASH_CLEAR_PENDING_FLAG(__FLAG__)     WRITE_REG(FLASH->ISR, (__FLAG__))

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASH_LL_Exported_Functions
  * @{
  */

/** @addtogroup FLASH_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_FLASH_ReadProtectLevelConfig(FLASH_RDPLVETypeDef RDPLevel);
LL_StatusETypeDef LL_FLASH_WriteProtectConfig(FLASH_WRPAREAETypeDef WRPAreas, FLASH_WRPSTETypeDef WRPState);
/**
  * @}
  */


/** @addtogroup FLASH_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_FLASH_WaitForLastOperation(uint32_t Timeout);
uint32_t LL_FLASH_GetError(void);
/**
  * @}
  */


/** @addtogroup FLASH_LL_Exported_Functions_Group3
  * @{
  */

/**
  * @brief  Unlock the FLASH Program/Erase access.
  * @param  None
  * @return LL Status
  */
__STATIC_INLINE LL_StatusETypeDef LL_FLASH_Unlock(void)
{
    if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET) {
        /* Authorize the FLASH Program/Erase access */
        WRITE_REG(FLASH->KEYR, FLASH_KEY1);
        WRITE_REG(FLASH->KEYR, FLASH_KEY2);

        /* Verify FLASH is unlocked */
        if (READ_BIT(FLASH->CR, FLASH_CR_LOCK_Msk) != RESET) {
            return LL_ERROR;
        }
    }

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Lock the FLASH Program/Erase access.
  * @param  None
  * @return LL Status
  */
__STATIC_INLINE LL_StatusETypeDef LL_FLASH_Lock(void)
{
    /* Set the LOCK Bit to lock the FLASH Program/Erase access */
    SET_BIT(FLASH->CR, FLASH_CR_LOCK);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Unlock the FLASH write/read Protection Feature access.
  * @param  None
  * @return LL Status
  */
__STATIC_INLINE LL_StatusETypeDef LL_FLASH_PF_Unlock(void)
{
    /* Unlock the FLASH Read/Write Operation Protection access */
    WRITE_REG(FLASH->KEYR, FLASH_OP_KEY);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Lock the FLASH write/read Protection Feature access.
  * @param  None
  * @return LL Status
  */
__STATIC_INLINE LL_StatusETypeDef LL_FLASH_PF_Lock(void)
{
    /* Lock the Read/Write Operation Protection access */
    WRITE_REG(FLASH->KEYR, 0x00000000UL);

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Launch the write/read Protection Feature reloading.
  * @param  None
  * @retval None
  */
__STATIC_INLINE LL_StatusETypeDef LL_FLASH_PF_Launch(void)
{
    /* Set the LAU bit in FLASH_CR register to reload */
    SET_BIT(FLASH->CR, FLASH_CR_LAU);

    /* Return function status */
    return LL_OK;
}


LL_StatusETypeDef LL_FLASH_Program(uint32_t Address, uint8_t Data[FLASH_PROG_DATA_WIDTH]);

LL_StatusETypeDef LL_FLASH_MultiSectorsErase(uint16_t Sector, uint16_t Num, uint16_t *SectorError);
LL_StatusETypeDef LL_FLASH_SectorErase(uint16_t Sector);

LL_StatusETypeDef LL_FLASH_ChipErase(void);

/**
  * @}
  */

/**
  * @}
  */


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup FLASH_LL_Private_Constants FLASH LL Private Constants
  * @brief    FLASH LL Private Constants
  * @{
  */

#define FLASH_PROGRAM_ADDRESS_MASK      0x00FFFFFFU /*!< Program address mask                                   */
#define FLASH_TIMEOUT_MAX_VALUE         300U        /*!< Max timeout for flash operations. Default 300 ticks    */

/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASH_LL_Private_Macros FLASH LL Private Macros
  * @brief    FLASH LL Private Macros
  * @{
  */

/**
  * @brief  Judge is write protect state or not
  * @param  STATE state to judge
  * @retval 0 isn't write protect state
  * @retval 1 is write protect state
  */
#define IS_WRITE_PROTECT_STATE(STATE)                  (((STATE) == FLASH_WRPSTATE_DISABLE)     || \

/**
  * @brief  Judge is flash program address align 128bit or not
  * @param  ADDRESS address to judge
  * @retval 0 isn't flash program address align 128bit
  * @retval 1 is flash program address align 128bit
  */
#define IS_FLASH_PROGRAM_ADDRESS_ALIGN_128BIT(ADDRESS) (((ADDRESS) & 0xF) == 0x00U)

/**
  * @brief  Judge is flash sector or not
  * @param  SECTOR sector to judge
  * @retval 0 isn't flash sector
  * @retval 1 is flash sector
  */
#define IS_FLASH_NB_SECTORS(SECTOR)                     ((SECTOR) < 160U)

/**
  * @}
  */


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


#endif /* _TAE32F53XX_LL_FLASH_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

