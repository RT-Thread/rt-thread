/**
  ******************************************************************************
  * @file    tae32f53xx_ll_dflash.c
  * @author  MCD Application Team
  * @brief   Source file for DFLASH module.
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


#define DBG_TAG             "DFLASH LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup DFLASH_LL DFLASH LL
  * @brief    DFLASH LL module driver
  * @{
  */

#ifdef LL_DFLASH_MODULE_ENABLED

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup DFLASH_LL_Exported_Functions DFLASH LL Exported Functions
  * @brief    DFLASH LL Exported Functions
  * @{
  */

/** @defgroup DFLASH_LL_Exported_Functions_Group1 DFLASH Peripheral State functions
  * @brief    DFLASH Peripheral State functions
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
  * @brief  Wait for a DFLASH operation to complete.
  * @param  Timeout Maximum DataFlash operation timeout
  * @return LL Status
  */
LL_StatusETypeDef LL_DFLASH_WaitForLastOperation(uint32_t Timeout)
{
    uint32_t tickstart = LL_GetTick();

    /* Wait for the DFLASH operation to complete by polling on BUSY flag to be reset.
       Even if the DFLASH operation fails, the BUSY flag will be reset and an error
       flag will be set */
    while (__LL_DFLASH_STATUS_FLAG_GET(DFLASH_FLAG_BSY) != RESET) {
        if (Timeout != LL_WAIT_FOREVER) {
            if ((Timeout == 0U) || ((LL_GetTick() - tickstart) > Timeout)) {
                return LL_TIMEOUT;
            }
        }
    }

    /* Check and clear DIF flag */
    if (__LL_DFLASH_PENDING_FLAG_GET(DFLASH_FLAG_DIF) != RESET) {
        __LL_DFLASH_PENDING_FLAG_CLEAR(DFLASH_FLAG_DIF);
    }

    /* Check if any errors occurred */
    if (__LL_DFLASH_PENDING_FLAG_GET(DFLASH_FLAG_EIF) != RESET) {
        return LL_ERROR;
    }

    /* Return function status */
    return LL_OK;
}

/**
  * @}
  */


/** @defgroup DFLASH_LL_Exported_Functions_Group2 DFLASH Input and Output operation functions
  * @brief    DFLASH Input and Output operation functions
@verbatim
  ===============================================================================
                  ##### Input and Output operation functions #####
  ===============================================================================
  [..]
    This section provides functions allowing to:
    (+) Byte/Word Program operations functions
    (+) Byte/Word Read operations functions
    (+) Erase operations functions

@endverbatim
  * @{
  */

/**
  * @brief  Program one byte at a specified address.
  * @param  Address specifies the address to be programmed.
  * @param  Data specifies the data to be programmed.
  * @note   LL_DFLASH_Unlock() should be called before to unlock the DFLASH interface
  *         LL_DFLASH_Lock() should be called after to lock the DFLASH interface
  * @return LL Status
  */
LL_StatusETypeDef LL_DFLASH_Program_Byte(uint32_t Address, uint8_t Data)
{
    LL_StatusETypeDef status = LL_OK;

    /* Check the parameters */
    assert_param(IS_DFLASH_ADDRESS_MASK(Address));

    /* Address mask */
    Address &= DFLASH_PROGRAM_ADDRESS_MASK;

    if ((status = LL_DFLASH_WaitForLastOperation(DFLASH_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Byte Program mode */
        CLEAR_BIT(DFLASH->CR, DFLASH_CR_DS);

        /* Fill the data into DFLASH_DR register */
        WRITE_REG(DFLASH->DR, Data);

        /* Set Address */
        WRITE_REG(DFLASH->ADDR, Address);

        /* Ignore full 0xFF data programming */
        if ((DFLASH->DR & 0xFF) != 0xFFU) {
            /* Pragram Start */
            SET_BIT(DFLASH->CR, DFLASH_CR_PS);

            /* Wait until operation complete */
            status = LL_DFLASH_WaitForLastOperation(DFLASH_TIMEOUT_MAX_VALUE);
        }
    }

    /* Return function status */
    return status;
}

/**
  * @brief  Program one word at a specified address.
  * @param  Address specifies the address to be programmed.
  *         Notice that address must align to a word
  * @param  Data specifies the data to be programmed.
  * @note   LL_DFLASH_Unlock() should be called before to unlock the DFLASH interface
  *         LL_DFLASH_Lock() should be called after to lock the DFLASH interface
  * @return LL Status
  */
LL_StatusETypeDef LL_DFLASH_Program_Word(uint32_t Address, uint32_t Data)
{
    LL_StatusETypeDef status = LL_OK;

    /* Check the parameters */
    assert_param(IS_DFLASH_ADDRESS_MASK(Address));
    assert_param(IS_DFLASH_ADDRESS_CHECK_ALIGN(Address));

    /* Address mask */
    Address &= DFLASH_PROGRAM_ADDRESS_MASK;

    if ((status = LL_DFLASH_WaitForLastOperation(DFLASH_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Byte Program mode */
        SET_BIT(DFLASH->CR, DFLASH_CR_DS);

        /* Fill the data into DFLASH_DR register */
        WRITE_REG(DFLASH->DR, Data);

        /* Set Address */
        WRITE_REG(DFLASH->ADDR, Address);

        /* Ignore full 0xFF data programming */
        if (DFLASH->DR != 0xFFFFFFFFU) {
            /* Pragram Start */
            SET_BIT(DFLASH->CR, DFLASH_CR_PS);

            /* Wait until operation complete */
            status = LL_DFLASH_WaitForLastOperation(DFLASH_TIMEOUT_MAX_VALUE);
        }
    }

    /* Return function status */
    return status;
}

/**
  * @brief  Read one byte from a specified address.
  * @param  Address specifies the address to read.
  * @param  Data specifies the data pointer to read in.
  * @note   LL_DFLASH_Unlock() should be called before to unlock the DFLASH interface
  *         LL_DFLASH_Lock() should be called after to lock the DFLASH interface
  * @return LL Status
  */
LL_StatusETypeDef LL_DFLASH_Read_Byte(uint32_t Address, uint8_t *Data)
{
    LL_StatusETypeDef status = LL_OK;

    /* Check the parameters */
    assert_param(IS_DFLASH_ADDRESS_MASK(Address));

    /* Address mask */
    Address &= DFLASH_PROGRAM_ADDRESS_MASK;
    /* Initialize the value of Data */
    *Data    = 0;

    if ((status = LL_DFLASH_WaitForLastOperation(DFLASH_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Byte Read mode */
        CLEAR_BIT(DFLASH->CR, DFLASH_CR_DS);

        /* Set Address */
        WRITE_REG(DFLASH->ADDR, Address);

        /* Read Start */
        SET_BIT(DFLASH->CR, DFLASH_CR_RS);

        /* Wait until operation complete */
        if ((status = LL_DFLASH_WaitForLastOperation(DFLASH_TIMEOUT_MAX_VALUE)) == LL_OK) {
            /* Read the data from DFLASH->DR Registers */
            *Data = READ_REG(DFLASH->DR) & 0xFFU;
        }
    }

    /* Return function status */
    return status;
}

/**
  * @brief  Read one wrod from a specified address.
  * @param  Address specifies the address to read.
  *         Notice that address must align to a word
  * @param  Data specifies the data pointer to read in.
  * @note   LL_DFLASH_Unlock() should be called before to unlock the DFLASH interface
  *         LL_DFLASH_Lock() should be called after to lock the DFLASH interface
  * @return LL Status
  */
LL_StatusETypeDef LL_DFLASH_Read_Word(uint32_t Address, uint32_t *Data)
{
    LL_StatusETypeDef status = LL_OK;

    /* Check the parameters */
    assert_param(IS_DFLASH_ADDRESS_MASK(Address));
    assert_param(IS_DFLASH_ADDRESS_CHECK_ALIGN(Address));

    /* Address mask */
    Address &= DFLASH_PROGRAM_ADDRESS_MASK;
    /* Initialize the value of Data */
    *Data    = 0;

    if ((status = LL_DFLASH_WaitForLastOperation(DFLASH_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Byte Read mode */
        CLEAR_BIT(DFLASH->CR, DFLASH_CR_DS);

        /* Set Address */
        WRITE_REG(DFLASH->ADDR, Address);

        /* Read Start */
        SET_BIT(DFLASH->CR, DFLASH_CR_RS);

        /* Wait until operation complete */
        if ((status = LL_DFLASH_WaitForLastOperation(DFLASH_TIMEOUT_MAX_VALUE)) == LL_OK) {
            /* Read the data from DFLASH->DR Registers */
            *Data = READ_REG(DFLASH->DR);
        }
    }

    /* Return function status */
    return status;
}

/**
  * @brief  DFLASH mass erase. This will mass erase the Main-Memory area.
  * @note   Please Notice this function has no effect to the Secondary-Memory.
  * @note   LL_DFLASH_Unlock() should be called before to unlock the DFLASH interface
  *         LL_DFLASH_Lock() should be called after to lock the DFLASH interface
  * @return LL Status
  */
LL_StatusETypeDef LL_DFLASH_MassErase(void)
{
    LL_StatusETypeDef status = LL_OK;

    if ((status = LL_DFLASH_WaitForLastOperation(DFLASH_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Set to Mass Erase mode */
        SET_BIT(DFLASH->ECR, DFLASH_ECR_EMODE);

        /* Erase Start */
        SET_BIT(DFLASH->CR, DFLASH_CR_ES);

        /* Wait until operation complete */
        status = LL_DFLASH_WaitForLastOperation(DFLASH_TIMEOUT_MAX_VALUE);
    }

    /* Return function status */
    return status;
}

/**
  * @brief  Erase one specified DFLASH memory sector. This function is effective for both
  *         Main-Memory and Secondary-Memory areas.
  * @param  sector The start sector number of the specified sectors to erase.
  *         This parameter must be a value between 0 and (NB of sectors - 1)
  * @note   LL_DFLASH_Unlock() should be called before to unlock the DFLASH interface
  *         LL_DFLASH_Lock() should be called after to lock the DFLASH interface
  * @return Status
  */
LL_StatusETypeDef LL_DFLASH_SectorErase(uint16_t Sector)
{
    LL_StatusETypeDef status = LL_OK;

    /* Check the parameters */
    assert_param(IS_DFLASH_NB_SECTORS(Sector));

    if ((status = LL_DFLASH_WaitForLastOperation(DFLASH_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /* Set to Sector Erase mode */
        CLEAR_BIT(DFLASH->ECR, DFLASH_ECR_EMODE);

        /* Set Sector to erase */
        MODIFY_REG(DFLASH->ECR, DFLASH_ECR_ESNB_Msk, Sector);

        /* Erase Start */
        SET_BIT(DFLASH->CR, DFLASH_CR_ES);

        /* Wait until operation complete */
        status = LL_DFLASH_WaitForLastOperation(DFLASH_TIMEOUT_MAX_VALUE);
    }

    /* Return function status */
    return status;
}

/**
  * @brief  Erase the specified DFLASH memory multiple sectors.
  * @param  sector The start sector number of the specified sectors to erase.
  *         This parameter must be a value between 0 and (NB of sectors - 1)
  * @param  num Number of sectors to be erased.
  *         This parameter must be a value between 1 and NB of sectors
  * @note   Please notice that all specified sectors number must between 0 and (NB of sectors - 1)
  * @param  *SectorError Pointer to variable that contains the configuration information on faulty
  *         sector in case of error (0xFFFF means that all the sectors have been correctly erased).
  *         Set this pointer to NULL if you do not need it.
  * @note   LL_DFLASH_Unlock() should be called before to unlock the DFLASH interface
  *         LL_DFLASH_Lock() should be called after to lock the DFLASH interface
  * @return LL Status
  */
LL_StatusETypeDef LL_DFLASH_MultiSectorsErase(uint16_t Sector, uint16_t Num, uint16_t *SectorError)
{
    LL_StatusETypeDef status = LL_OK;

    assert_param(Num != 0);
    assert_param(IS_DFLASH_NB_SECTORS(Sector));
    assert_param(IS_DFLASH_NB_SECTORS(Sector + Num - 1));

    if ((status = LL_DFLASH_WaitForLastOperation(DFLASH_TIMEOUT_MAX_VALUE)) == LL_OK) {
        /*Initialization of SectorError variable*/
        if (SectorError != NULL) {
            *SectorError = 0xFFFF;
        }

        /* Set to Sector Erase mode */
        CLEAR_BIT(DFLASH->ECR, DFLASH_ECR_EMODE);

        /* Erase the specified sectors */
        for (uint16_t index = Sector; index < (Sector + Num); index++) {
            /* Set current Sector to erase */
            MODIFY_REG(DFLASH->ECR, DFLASH_ECR_ESNB_Msk, index);

            /* Erase Start */
            SET_BIT(DFLASH->CR, DFLASH_CR_ES);

            /* Wait until operation complete */
            if ((status = LL_DFLASH_WaitForLastOperation(DFLASH_TIMEOUT_MAX_VALUE)) != LL_OK) {
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
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


#endif /* LL_DFLASH_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

