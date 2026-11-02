/**
  ******************************************************************************
  * @file    tae32f53xx_ll_flash.c
  * @author  MCD Application Team
  * @brief   FLASH LL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the internal FLASH memory:
  *           + Program operations functions
  *           + Erase operations functions
  *           + Peripheral State functions
  *           + Write Protection Area configure functions
  *           + Read Protection Level configure functions
  *           + Interrupt and Callback functions
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

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll.h"


#define DBG_TAG             "FLASH LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup FLASH_LL FLASH LL
  * @brief    Flash LL module driver.
  * @{
  */

#ifdef LL_FLASH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup FLASH_LL_Private_Variables FLASH LL Private Variables
  * @brief    FLASH LL Private Variables
  * @{
  */

/** @brief Variable whitch recorded the error codes.
  *        This parameter can be any combination of @ref FLASH_Error_Codes
  */
static uint32_t FlashErrorCode = FLASH_ERROR_NONE;

/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/
/** @defgroup FLASH_LL_Private_Functions FLASH LL Private Functions
  * @brief    FLASH LL Private Functions
  * @{
  */
static void FLASH_SetErrorCode(void);

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Functions FLASH LL Exported Functions
  * @brief    FLASH LL Exported Functions
  * @{
  */

/** @defgroup FLASH_LL_Exported_Functions_Group1 FLASH Peripheral Control functions
  * @brief    FLASH Peripheral Control functions
@verbatim
  ===============================================================================
                       ##### Peripheral Control functions #####
  ===============================================================================
  [..]
    This section provides functions allowing to:
    (+) Read Protection Level configure
    (+) Write Protection Area configure

@endverbatim
  * @{
  */

/**
  * @brief  Read Protection Level configuration.
  * @param  RDPLevel specifies the read protection level
  *         This parameter can be a value of @ref FLASH_Read_Protection_Level:
  *             @arg FLASH_RDP_LEVEL_0 : No protection
  *             @arg FLASH_RDP_LEVEL_1 : Memory Read protection
  *             @arg FLASH_RDP_LEVEL_2 : Full chip protection
  * @note   When enabling read protection level 2, it's no more possible to
  *         go back to level 1 or level 0.
  * @note   The function @ref LL_FLASH_Unlock() should be called before to unlock the FLASH interface
  *         The function @ref LL_FLASH_PF_Unlock() should be called before to unlock the protection feature
  *         The function @ref LL_FLASH_PF_Launch() should be called after to force the reload of the new configuration
  * @return LL Status
  */
LL_StatusETypeDef LL_FLASH_ReadProtectLevelConfig(FLASH_RDPLVETypeDef RDPLevel)
{
    LL_StatusETypeDef status = LL_OK;

    if ((status = LL_FLASH_WaitForLastOperation(FLASH_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Clear error code before operation */
        FlashErrorCode = FLASH_ERROR_NONE;

        /* Configure the RDP level in the userdata register */
        MODIFY_REG(FLASH->RDPR, FLASH_RDPR_RDP_Msk, RDPLevel);

        /* Wait until operation complete */
        status = LL_FLASH_WaitForLastOperation(FLASH_TIMEOUT_MAX_VALUE);
    }

    return status;
}

/**
  * @brief  Write Protection configuration.
  * @param  WRPAreas specifies the area to configure Write Protection.
  *         This parameter can be any combination value of @ref FLASH_Write_Protection_Area.
  * @param  WRPState Enable/Disable WRP state for the specifies WPRAreas.
  *         This parameter can be a value of @ref FLASH_WRP_State:
  *             @arg FLASH_WRPSTATE_DISABLE: Disable specifies areas WRP
  *             @arg FLASH_WRPSTATE_ENABLE: Enable specifies areas WRP
  * @note   Once memory area Write Protection is enabled, user must not program the memory area
  *         until the protection is disabled.
  * @note   The function @ref LL_FLASH_Unlock() should be called before to unlock the FLASH interface
  *         The function @ref LL_FLASH_PF_Unlock() should be called before to unlock the protection feature
  *         The function @ref LL_FLASH_PF_Launch() should be called after to force the reload of the new configuration
  * @return Status
  */
LL_StatusETypeDef LL_FLASH_WriteProtectConfig(FLASH_WRPAREAETypeDef WRPAreas, FLASH_WRPSTETypeDef WRPState)
{
    LL_StatusETypeDef status = LL_OK;

    if ((status = LL_FLASH_WaitForLastOperation(FLASH_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Clear error code before operation */
        FlashErrorCode = FLASH_ERROR_NONE;

        if (WRPState == FLASH_WRPSTATE_ENABLE) {
            /* Enable the Write Protection */
            CLEAR_BIT(FLASH->WRPR, WRPAreas);
        } else {
            /* Disable the Write Protection */
            SET_BIT(FLASH->WRPR, WRPAreas);
        }

        /* Wait until operation complete */
        status = LL_FLASH_WaitForLastOperation(FLASH_TIMEOUT_MAX_VALUE);
    }

    return status;
}

/**
  * @}
  */


/** @defgroup FLASH_LL_Exported_Functions_Group2 FLASH Peripheral State functions
  * @brief    FLASH Peripheral State functions
@verbatim
  ===============================================================================
                       ##### Peripheral State functions #####
  ===============================================================================
  [..]
    This section provides functions allowing to:
    (+) Peripheral State functions

@endverbatim
  * @{
  */

/**
  * @brief  Wait for a FLASH operation to complete.
  * @param  Timeout Maximum flash operation timeout
  * @return LL Status
  */
LL_StatusETypeDef LL_FLASH_WaitForLastOperation(uint32_t Timeout)
{
    uint32_t tickstart = LL_GetTick();

    /* Wait for the FLASH operation to complete by polling on BUSY flag to be reset.
       Even if the FLASH operation fails, the BUSY flag will be reset and an error
       flag will be set */
    while (__LL_FLASH_GET_STATUS_FLAG(FLASH_FLAG_BSY) != RESET) {
        if (Timeout != LL_WAIT_FOREVER) {
            if ((Timeout == 0U) || ((LL_GetTick() - tickstart) > Timeout)) {
                return LL_TIMEOUT;
            }
        }
    }

    /* Check and clear DIF flag */
    if (__LL_FLASH_GET_PENDING_FLAG(FLASH_FLAG_DIF) != RESET) {
        __LL_FLASH_CLEAR_PENDING_FLAG(FLASH_FLAG_DIF);
    }

    /* Check if any errors occurred */
    if ((__LL_FLASH_GET_PENDING_FLAG(FLASH_FLAG_RPEIF) != RESET)    ||
        (__LL_FLASH_GET_PENDING_FLAG(FLASH_FLAG_WPEIF) != RESET)    ||
        (__LL_FLASH_GET_PENDING_FLAG(FLASH_FLAG_OPTEIF) != RESET)   ||
        (__LL_FLASH_GET_PENDING_FLAG(FLASH_FLAG_ECCEIF) != RESET)) {
        /* Save the error code */
        FLASH_SetErrorCode();
        return LL_ERROR;
    }

    /* Return function status */
    return LL_OK;
}

/**
  * @brief  Get the specific FLASH error flags.
  * @return The returned value can be any combination of @ref FLASH_Error_Codes
  */
uint32_t LL_FLASH_GetError(void)
{
    return FlashErrorCode;
}

/**
  * @}
  */


/** @defgroup FLASH_LL_Exported_Functions_Group3 FLASH Input and Output operation functions
  * @brief    FLASH Input and Output operation functions
@verbatim
  ===============================================================================
                  ##### Input and Output operation functions #####
  ===============================================================================
  [..]
    This section provides functions allowing to:
    (+) Program operations functions
    (+) Erase operations functions

@endverbatim
  * @{
  */

/**
  * @brief  Program 16 bytes (128 bit) at a specified address.
  * @param  Address specifies the address to be programmed.
  *         Notice that address must align to 128 bit
  * @param  Data[] specifies the data to be programmed.
  *         FLASH_PROG_DATA_WIDTH bytes will be programmed in a single operation.
  * @note   LL_FLASH_Unlock() should be called before to unlock the FLASH interface
  *         LL_FLASH_Lock() should be called after to lock the FLASH interface
  * @return LL Status
  */
LL_StatusETypeDef LL_FLASH_Program(uint32_t Address, uint8_t Data[FLASH_PROG_DATA_WIDTH])
{
    LL_StatusETypeDef status = LL_OK;

    /* Check the parameters */
    assert_param(Data != NULL);
    assert_param(IS_FLASH_PROGRAM_ADDRESS_ALIGN_128BIT(Address));

    /* Address mask */
    Address &= FLASH_PROGRAM_ADDRESS_MASK;

    if ((status = LL_FLASH_WaitForLastOperation(FLASH_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Clear error code before operation */
        FlashErrorCode = FLASH_ERROR_NONE;

        /* Fill the data into FLASH Program Control Registers */
        FLASH->DR0 = *((__IO uint32_t *)(Data +  0));
        FLASH->DR1 = *((__IO uint32_t *)(Data +  4));
        FLASH->DR2 = *((__IO uint32_t *)(Data +  8));
        FLASH->DR3 = *((__IO uint32_t *)(Data + 12));

        /* Set Address */
        FLASH->ADDR = Address;

        /* Ignore full 0xFF data programming */
        if ((FLASH->DR0 != 0xFFFFFFFFU) &&
            (FLASH->DR1 != 0xFFFFFFFFU) &&
            (FLASH->DR2 != 0xFFFFFFFFU) &&
            (FLASH->DR3 != 0xFFFFFFFFU)) {

            /* Pragram Start */
            SET_BIT(FLASH->CR, FLASH_CR_PS);

            /* Wait until operation complete */
            status = LL_FLASH_WaitForLastOperation(FLASH_TIMEOUT_MAX_VALUE);
        }
    }

    /* Return function status */
    return status;
}

/**
  * @brief  Erase one specified FLASH memory sector.
  * @param  sector The start sector number of the specified sectors to erase.
  *         This parameter must be a value between 0 and (NB of sectors - 1)
  * @note   LL_FLASH_Unlock() should be called before to unlock the FLASH interface
  *         LL_FLASH_Lock() should be called after to lock the FLASH interface
  * @return Status
  */
LL_StatusETypeDef LL_FLASH_SectorErase(uint16_t Sector)
{
    LL_StatusETypeDef status = LL_OK;

    /* Check the parameters */
    assert_param(IS_FLASH_NB_SECTORS(Sector));

    if ((status = LL_FLASH_WaitForLastOperation(FLASH_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Clear error code before operation */
        FlashErrorCode = FLASH_ERROR_NONE;

        /* Set to Sector Erase mode */
        CLEAR_BIT(FLASH->ECR, FLASH_ECR_EMODE);

        /* Set Sector to erase */
        MODIFY_REG(FLASH->ECR, FLASH_ECR_ESNB_Msk, Sector);

        /* Erase Start */
        SET_BIT(FLASH->CR, FLASH_CR_ES);

        /* Wait until operation complete */
        status = LL_FLASH_WaitForLastOperation(FLASH_TIMEOUT_MAX_VALUE);
    }

    /* Return function status */
    return status;
}

/**
  * @brief  Erase the specified FLASH memory multiple sectors.
  * @param  sector The start sector number of the specified sectors to erase.
  *         This parameter must be a value between 0 and (NB of sectors - 1)
  * @param  num Number of sectors to be erased.
  *         This parameter must be a value between 1 and NB of sectors
  * @note   Please notice that all specified sectors number must between 0 and (NB of sectors - 1)
  * @param  *SectorError Pointer to variable that contains the configuration information on faulty
  *         sector in case of error (0xFFFF means that all the sectors have been correctly erased).
  *         Set this pointer to NULL if you do not need it.
  * @note   LL_FLASH_Unlock() should be called before to unlock the FLASH interface
  *         LL_FLASH_Lock() should be called after to lock the FLASH interface
  * @return LL Status
  */
LL_StatusETypeDef LL_FLASH_MultiSectorsErase(uint16_t Sector, uint16_t Num, uint16_t *SectorError)
{
    LL_StatusETypeDef status = LL_OK;

    assert_param(Num != 0);
    assert_param(IS_FLASH_NB_SECTORS(Sector));
    assert_param(IS_FLASH_NB_SECTORS(Sector + Num - 1));

    if ((status = LL_FLASH_WaitForLastOperation(FLASH_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Clear error code before operation */
        FlashErrorCode = FLASH_ERROR_NONE;

        /*Initialization of SectorError variable*/
        if (SectorError != NULL) {
            *SectorError = 0xFFFF;
        }

        /* Set to Sector Erase mode */
        CLEAR_BIT(FLASH->ECR, FLASH_ECR_EMODE);

        /* Erase the specified sectors */
        for (uint16_t index = Sector; index < (Sector + Num); index++) {
            /* Set current Sector to erase */
            MODIFY_REG(FLASH->ECR, FLASH_ECR_ESNB_Msk, index);

            /* Erase Start */
            SET_BIT(FLASH->CR, FLASH_CR_ES);

            /* Wait until operation complete */
            if ((status = LL_FLASH_WaitForLastOperation(FLASH_TIMEOUT_MAX_VALUE)) != LL_OK) {
                /* In case of error, stop erase procedure and return the faulty Sector */
                if (SectorError != NULL) {
                    *SectorError = index;
                }

                break;
            }
        }
    }

    /* Return function status */
    return status;
}

/**
  * @brief  FLASH memory mass erase. This will erase the entire FLASH memory.
  * @note   LL_FLASH_Unlock() should be called before to unlock the FLASH interface
  *         LL_FLASH_Lock() should be called after to lock the FLASH interface
  * @return LL Status
  */
LL_StatusETypeDef LL_FLASH_ChipErase(void)
{
    LL_StatusETypeDef status = LL_OK;

    if ((status = LL_FLASH_WaitForLastOperation(FLASH_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Clear error code before operation */
        FlashErrorCode = FLASH_ERROR_NONE;

        /* Set to Chip Erase mode */
        SET_BIT(FLASH->ECR, FLASH_ECR_EMODE);

        /* Erase Start */
        SET_BIT(FLASH->CR, FLASH_CR_ES);

        /* Wait until operation complete */
        status = LL_FLASH_WaitForLastOperation(FLASH_TIMEOUT_MAX_VALUE);
    }

    /* Return function status */
    return status;
}

/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/
/** @addtogroup FLASH_LL_Private_Functions
  * @{
  */

/**
  * @brief  Set the specific FLASH error flag.
  * @return None
  */
static void FLASH_SetErrorCode(void)
{
    if (__LL_FLASH_GET_PENDING_FLAG(FLASH_FLAG_RPEIF) != RESET) {
        FlashErrorCode |= FLASH_ERROR_RDP;
        __LL_FLASH_CLEAR_PENDING_FLAG(FLASH_FLAG_RPEIF);
    }

    if (__LL_FLASH_GET_PENDING_FLAG(FLASH_FLAG_WPEIF) != RESET) {
        FlashErrorCode |= FLASH_ERROR_WRP;
        __LL_FLASH_CLEAR_PENDING_FLAG(FLASH_FLAG_WPEIF);
    }

    if (__LL_FLASH_GET_PENDING_FLAG(FLASH_FLAG_OPTEIF) != RESET) {
        FlashErrorCode |= FLASH_ERROR_OPT;
        __LL_FLASH_CLEAR_PENDING_FLAG(FLASH_FLAG_OPTEIF);
    }

    if (__LL_FLASH_GET_PENDING_FLAG(FLASH_FLAG_ECCEIF) != RESET) {
        FlashErrorCode |= FLASH_ERROR_ECC;
        __LL_FLASH_CLEAR_PENDING_FLAG(FLASH_FLAG_ECCEIF);
    }
}

/**
  * @}
  */


#endif /* LL_FLASH_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

