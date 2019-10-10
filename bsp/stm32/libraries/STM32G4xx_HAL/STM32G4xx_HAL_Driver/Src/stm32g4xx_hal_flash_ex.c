/**
  ******************************************************************************
  * @file    stm32g4xx_hal_flash_ex.c
  * @author  MCD Application Team
  * @brief   Extended FLASH HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the FLASH extended peripheral:
  *           + Extended programming operations functions
  *
  @verbatim
  ==============================================================================
                   ##### Flash Extended features #####
  ==============================================================================

  [..] Comparing to other previous devices, the FLASH interface for STM32G4xx
       devices contains the following additional features

       (+) Capacity up to 512 Kbytes with dual bank architecture supporting read-while-write
           capability (RWW)
       (+) Dual bank 64-bits memory organization with possibility of single bank 128-bits
       (+) Protected areas including WRP, PCROP and Securable memory

                        ##### How to use this driver #####
  ==============================================================================
  [..] This driver provides functions to configure and program the FLASH memory
       of all STM32G4xx devices. It includes
      (#) Flash Memory Erase functions:
           (++) Lock and Unlock the FLASH interface using HAL_FLASH_Unlock() and
                HAL_FLASH_Lock() functions
           (++) Erase function: Erase pages, or mass erase banks
           (++) There are two modes of erase :
             (+++) Polling Mode using HAL_FLASHEx_Erase()
             (+++) Interrupt Mode using HAL_FLASHEx_Erase_IT()

      (#) Option Bytes Programming function: Use HAL_FLASHEx_OBProgram() to:
        (++) Configure the write protection areas (WRP)
        (++) Set the Read protection Level (RDP)
        (++) Program the user Option Bytes
        (++) Configure the Proprietary Code ReadOut protection areas (PCROP)
        (++) Configure the Securable memory areas
        (++) Configure the Boot Lock

      (#) Get Option Bytes Configuration function: Use HAL_FLASHEx_OBGetConfig() to:
        (++) Get the configuration of write protection areas (WRP)
        (++) Get the level of read protection (RDP)
        (++) Get the value of the user Option Bytes
        (++) Get the configuration of Proprietary Code ReadOut Protection areas (PCROP)
        (++) Get the configuration of Securable memory areas
        (++) Get the status of Boot Lock

      (#) Activation of Securable memory area: Use HAL_FLASHEx_EnableSecMemProtection()
        (++) Deny the access to securable memory area

      (#) Enable or disable debugger: Use HAL_FLASHEx_EnableDebugger() or
          HAL_FLASHEx_DisableDebugger()

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 STMicroelectronics</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/** @addtogroup STM32G4xx_HAL_Driver
  * @{
  */

/** @defgroup FLASHEx FLASHEx
  * @brief FLASH Extended HAL module driver
  * @{
  */

#ifdef HAL_FLASH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup FLASHEx_Private_Functions FLASHEx Private Functions
  * @{
  */
static void              FLASH_MassErase(uint32_t Banks);
static HAL_StatusTypeDef FLASH_OB_WRPConfig(uint32_t WRPArea, uint32_t WRPStartOffset, uint32_t WRDPEndOffset);
static HAL_StatusTypeDef FLASH_OB_RDPConfig(uint32_t RDPLevel);
static HAL_StatusTypeDef FLASH_OB_UserConfig(uint32_t UserType, uint32_t UserConfig);
static HAL_StatusTypeDef FLASH_OB_PCROPConfig(uint32_t PCROPConfig, uint32_t PCROPStartAddr, uint32_t PCROPEndAddr);
static void              FLASH_OB_GetWRP(uint32_t WRPArea, uint32_t *WRPStartOffset, uint32_t *WRDPEndOffset);
static uint32_t          FLASH_OB_GetRDP(void);
static uint32_t          FLASH_OB_GetUser(void);
static void              FLASH_OB_GetPCROP(uint32_t *PCROPConfig, uint32_t *PCROPStartAddr, uint32_t *PCROPEndAddr);
static HAL_StatusTypeDef FLASH_OB_SecMemConfig(uint32_t SecMemBank, uint32_t SecMemSize);
static void              FLASH_OB_GetSecMem(uint32_t SecMemBank, uint32_t *SecMemSize);
static HAL_StatusTypeDef FLASH_OB_BootLockConfig(uint32_t BootLockConfig);
static uint32_t          FLASH_OB_GetBootLock(void);

/**
  * @}
  */

/* Exported functions -------------------------------------------------------*/
/** @defgroup FLASHEx_Exported_Functions FLASHEx Exported Functions
  * @{
  */

/** @defgroup FLASHEx_Exported_Functions_Group1 Extended IO operation functions
  * @brief   Extended IO operation functions
  *
@verbatim
 ===============================================================================
                ##### Extended programming operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the Extended FLASH
    programming operations Operations.

@endverbatim
  * @{
  */
/**
  * @brief  Perform a mass erase or erase the specified FLASH memory pages.
  * @param[in]  pEraseInit pointer to an FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  * @param[out]  PageError pointer to variable that contains the configuration
  *         information on faulty page in case of error (0xFFFFFFFF means that all
  *         the pages have been correctly erased).
  * @retval HAL_Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError)
{
  HAL_StatusTypeDef status;
  uint32_t page_index;

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

    /* Deactivate the cache if they are activated to avoid data misbehavior */
    if (READ_BIT(FLASH->ACR, FLASH_ACR_ICEN) != 0U)
    {
      /* Disable instruction cache  */
      __HAL_FLASH_INSTRUCTION_CACHE_DISABLE();

      if (READ_BIT(FLASH->ACR, FLASH_ACR_DCEN) != 0U)
      {
        /* Disable data cache  */
        __HAL_FLASH_DATA_CACHE_DISABLE();
        pFlash.CacheToReactivate = FLASH_CACHE_ICACHE_DCACHE_ENABLED;
      }
      else
      {
        pFlash.CacheToReactivate = FLASH_CACHE_ICACHE_ENABLED;
      }
    }
    else if (READ_BIT(FLASH->ACR, FLASH_ACR_DCEN) != 0U)
    {
      /* Disable data cache  */
      __HAL_FLASH_DATA_CACHE_DISABLE();
      pFlash.CacheToReactivate = FLASH_CACHE_DCACHE_ENABLED;
    }
    else
    {
      pFlash.CacheToReactivate = FLASH_CACHE_DISABLED;
    }

    if (pEraseInit->TypeErase == FLASH_TYPEERASE_MASSERASE)
    {
      /* Mass erase to be done */
      FLASH_MassErase(pEraseInit->Banks);

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

#if defined (FLASH_OPTR_DBANK)
      /* If the erase operation is completed, disable the MER1 and MER2 Bits */
      CLEAR_BIT(FLASH->CR, (FLASH_CR_MER1 | FLASH_CR_MER2));
#else
      /* If the erase operation is completed, disable the MER1 Bit */
      CLEAR_BIT(FLASH->CR, (FLASH_CR_MER1));
#endif
    }
    else
    {
      /*Initialization of PageError variable*/
      *PageError = 0xFFFFFFFFU;

      for (page_index = pEraseInit->Page; page_index < (pEraseInit->Page + pEraseInit->NbPages); page_index++)
      {
        FLASH_PageErase(page_index, pEraseInit->Banks);

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

        /* If the erase operation is completed, disable the PER Bit */
        CLEAR_BIT(FLASH->CR, (FLASH_CR_PER | FLASH_CR_PNB));

        if (status != HAL_OK)
        {
          /* In case of error, stop erase procedure and return the faulty page */
          *PageError = page_index;
          break;
        }
      }
    }

    /* Flush the caches to be sure of the data consistency */
    FLASH_FlushCaches();
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Perform a mass erase or erase the specified FLASH memory pages with interrupt enabled.
  * @param  pEraseInit pointer to an FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  * @retval HAL_Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));

  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Deactivate the cache if they are activated to avoid data misbehavior */
  if (READ_BIT(FLASH->ACR, FLASH_ACR_ICEN) != 0U)
  {
    /* Disable instruction cache  */
    __HAL_FLASH_INSTRUCTION_CACHE_DISABLE();

    if (READ_BIT(FLASH->ACR, FLASH_ACR_DCEN) != 0U)
    {
      /* Disable data cache  */
      __HAL_FLASH_DATA_CACHE_DISABLE();
      pFlash.CacheToReactivate = FLASH_CACHE_ICACHE_DCACHE_ENABLED;
    }
    else
    {
      pFlash.CacheToReactivate = FLASH_CACHE_ICACHE_ENABLED;
    }
  }
  else if (READ_BIT(FLASH->ACR, FLASH_ACR_DCEN) != 0U)
  {
    /* Disable data cache  */
    __HAL_FLASH_DATA_CACHE_DISABLE();
    pFlash.CacheToReactivate = FLASH_CACHE_DCACHE_ENABLED;
  }
  else
  {
    pFlash.CacheToReactivate = FLASH_CACHE_DISABLED;
  }

  /* Enable End of Operation and Error interrupts */
  __HAL_FLASH_ENABLE_IT(FLASH_IT_EOP | FLASH_IT_OPERR);

  pFlash.Bank = pEraseInit->Banks;

  if (pEraseInit->TypeErase == FLASH_TYPEERASE_MASSERASE)
  {
    /* Mass erase to be done */
    pFlash.ProcedureOnGoing = FLASH_PROC_MASS_ERASE;
    FLASH_MassErase(pEraseInit->Banks);
  }
  else
  {
    /* Erase by page to be done */
    pFlash.ProcedureOnGoing = FLASH_PROC_PAGE_ERASE;
    pFlash.NbPagesToErase = pEraseInit->NbPages;
    pFlash.Page = pEraseInit->Page;

    /*Erase 1st page and wait for IT */
    FLASH_PageErase(pEraseInit->Page, pEraseInit->Banks);
  }

  return status;
}

/**
  * @brief  Program Option bytes.
  * @param  pOBInit pointer to an FLASH_OBInitStruct structure that
  *         contains the configuration information for the programming.
  * @note   To configure any option bytes, the option lock bit OPTLOCK must be
  *         cleared with the call of HAL_FLASH_OB_Unlock() function.
  * @note   New option bytes configuration will be taken into account in two cases:
  *         - after an option bytes launch through the call of HAL_FLASH_OB_Launch()
  *         - after a power reset (BOR reset or exit from Standby/Shutdown modes)
  * @retval HAL_Status
  */
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_OPTIONBYTE(pOBInit->OptionType));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Write protection configuration */
  if ((pOBInit->OptionType & OPTIONBYTE_WRP) != 0U)
  {
    /* Configure of Write protection on the selected area */
    if (FLASH_OB_WRPConfig(pOBInit->WRPArea, pOBInit->WRPStartOffset, pOBInit->WRPEndOffset) != HAL_OK)
    {
      status = HAL_ERROR;
    }
  }

  /* Read protection configuration */
  if ((pOBInit->OptionType & OPTIONBYTE_RDP) != 0U)
  {
    /* Configure the Read protection level */
    if (FLASH_OB_RDPConfig(pOBInit->RDPLevel) != HAL_OK)
    {
      status = HAL_ERROR;
    }
  }

  /* User Configuration */
  if ((pOBInit->OptionType & OPTIONBYTE_USER) != 0U)
  {
    /* Configure the user option bytes */
    if (FLASH_OB_UserConfig(pOBInit->USERType, pOBInit->USERConfig) != HAL_OK)
    {
      status = HAL_ERROR;
    }
  }

  /* PCROP Configuration */
  if ((pOBInit->OptionType & OPTIONBYTE_PCROP) != 0U)
  {
    if (pOBInit->PCROPStartAddr != pOBInit->PCROPEndAddr)
    {
      /* Configure the Proprietary code readout protection */
      if (FLASH_OB_PCROPConfig(pOBInit->PCROPConfig, pOBInit->PCROPStartAddr, pOBInit->PCROPEndAddr) != HAL_OK)
      {
        status = HAL_ERROR;
      }
    }
  }

  /* Securable memory Configuration */
  if ((pOBInit->OptionType & OPTIONBYTE_SEC) != 0U)
  {
    /* Configure the securable memory area */
    if (FLASH_OB_SecMemConfig(pOBInit->SecBank, pOBInit->SecSize) != HAL_OK)
    {
      status = HAL_ERROR;
    }
  }

  /* Boot Entry Point Configuration */
  if ((pOBInit->OptionType & OPTIONBYTE_BOOT_LOCK) != 0U)
  {
    /* Configure the boot unique entry point option */
    if (FLASH_OB_BootLockConfig(pOBInit->BootEntryPoint) != HAL_OK)
    {
      status = HAL_ERROR;
    }
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Get the Option bytes configuration.
  * @param  pOBInit pointer to an FLASH_OBInitStruct structure that contains the
  *         configuration information.
  * @note   The fields pOBInit->WRPArea and pOBInit->PCROPConfig should indicate
  *         which area is requested for the WRP and PCROP, else no information will be returned.
  * @retval None
  */
void HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit)
{
  pOBInit->OptionType = (OPTIONBYTE_RDP | OPTIONBYTE_USER);

#if defined (FLASH_OPTR_DBANK)
  if ((pOBInit->WRPArea == OB_WRPAREA_BANK1_AREAA) || (pOBInit->WRPArea == OB_WRPAREA_BANK1_AREAB) ||
      (pOBInit->WRPArea == OB_WRPAREA_BANK2_AREAA) || (pOBInit->WRPArea == OB_WRPAREA_BANK2_AREAB))
#else
  if ((pOBInit->WRPArea == OB_WRPAREA_BANK1_AREAA) || (pOBInit->WRPArea == OB_WRPAREA_BANK1_AREAB))
#endif
  {
    pOBInit->OptionType |= OPTIONBYTE_WRP;
    /* Get write protection on the selected area */
    FLASH_OB_GetWRP(pOBInit->WRPArea, &(pOBInit->WRPStartOffset), &(pOBInit->WRPEndOffset));
  }

  /* Get Read protection level */
  pOBInit->RDPLevel = FLASH_OB_GetRDP();

  /* Get the user option bytes */
  pOBInit->USERConfig = FLASH_OB_GetUser();

#if defined (FLASH_OPTR_DBANK)
  if ((pOBInit->PCROPConfig == FLASH_BANK_1) || (pOBInit->PCROPConfig == FLASH_BANK_2))
#else
  if (pOBInit->PCROPConfig == FLASH_BANK_1)
#endif
  {
    pOBInit->OptionType |= OPTIONBYTE_PCROP;
    /* Get the Proprietary code readout protection */
    FLASH_OB_GetPCROP(&(pOBInit->PCROPConfig), &(pOBInit->PCROPStartAddr), &(pOBInit->PCROPEndAddr));
  }

  pOBInit->OptionType |= OPTIONBYTE_BOOT_LOCK;

  /* Get the boot entry point */
  pOBInit->BootEntryPoint = FLASH_OB_GetBootLock();

  /* Get the securable memory area configuration */
#if defined (FLASH_OPTR_DBANK)
  if ((pOBInit->SecBank == FLASH_BANK_1) || (pOBInit->SecBank == FLASH_BANK_2))
#else
  if (pOBInit->SecBank == FLASH_BANK_1)
#endif
  {
    pOBInit->OptionType |= OPTIONBYTE_SEC;
    FLASH_OB_GetSecMem(pOBInit->SecBank, &(pOBInit->SecSize));
  }
}

/**
  * @brief  Enable the FLASH Securable Memory protection.
  * @param  Bank: Bank to be protected
  *          This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: Bank1 to be protected
  *            @arg FLASH_BANK_2: Bank2 to be protected (*)
  *            @arg FLASH_BANK_BOTH: Bank1 and Bank2 to be protected (*)
  * @note   (*) availability depends on devices
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_EnableSecMemProtection(uint32_t Bank)
{
#if defined (FLASH_OPTR_DBANK)
  if (READ_BIT(FLASH->OPTR, FLASH_OPTR_DBANK) != 0U)
  {
    /* Check the parameters */
    assert_param(IS_FLASH_BANK(Bank));

    /* Enable the Securable Memory Protection Bit for the bank 1 if requested */
    if ((Bank & FLASH_BANK_1) != 0U)
    {
      SET_BIT(FLASH->CR, FLASH_CR_SEC_PROT1);
    }

    /* Enable the Securable Memory Protection Bit for the bank 2 if requested */
    if ((Bank & FLASH_BANK_2) != 0U)
    {
      SET_BIT(FLASH->CR, FLASH_CR_SEC_PROT2);
    }
  }
  else
#endif
  {
    SET_BIT(FLASH->CR, FLASH_CR_SEC_PROT1);
  }

  return HAL_OK;
}

/**
  * @brief  Enable Debugger.
  * @note   After calling this API, flash interface allow debugger intrusion.
  * @retval None
  */
void HAL_FLASHEx_EnableDebugger(void)
{
  FLASH->ACR |= FLASH_ACR_DBG_SWEN;
}


/**
  * @brief  Disable Debugger.
  * @note   After calling this API, Debugger is disabled: it's no more possible to
  *         break, see CPU register, etc...
  * @retval None
  */
void HAL_FLASHEx_DisableDebugger(void)
{
  FLASH->ACR &= ~FLASH_ACR_DBG_SWEN;
}

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/** @addtogroup FLASHEx_Private_Functions
  * @{
  */
/**
  * @brief  Mass erase of FLASH memory.
  * @param  Banks Banks to be erased.
  *         This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: Bank1 to be erased
  *            @arg FLASH_BANK_2: Bank2 to be erased (*)
  *            @arg FLASH_BANK_BOTH: Bank1 and Bank2 to be erased (*)
  * @note   (*) availability depends on devices
  * @retval None
  */
static void FLASH_MassErase(uint32_t Banks)
{
#if defined (FLASH_OPTR_DBANK)
  if (READ_BIT(FLASH->OPTR, FLASH_OPTR_DBANK) != 0U)
#endif
  {
    /* Check the parameters */
    assert_param(IS_FLASH_BANK(Banks));

    /* Set the Mass Erase Bit for the bank 1 if requested */
    if ((Banks & FLASH_BANK_1) != 0U)
    {
      SET_BIT(FLASH->CR, FLASH_CR_MER1);
    }

#if defined (FLASH_OPTR_DBANK)
    /* Set the Mass Erase Bit for the bank 2 if requested */
    if ((Banks & FLASH_BANK_2) != 0U)
    {
      SET_BIT(FLASH->CR, FLASH_CR_MER2);
    }
#endif
  }
#if defined (FLASH_OPTR_DBANK)
  else
  {
    SET_BIT(FLASH->CR, (FLASH_CR_MER1 | FLASH_CR_MER2));
  }
#endif

  /* Proceed to erase all sectors */
  SET_BIT(FLASH->CR, FLASH_CR_STRT);
}

/**
  * @brief  Erase the specified FLASH memory page.
  * @param  Page FLASH page to erase.
  *         This parameter must be a value between 0 and (max number of pages in the bank - 1).
  * @param  Banks Bank where the page will be erased.
  *         This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: Page in bank 1 to be erased
  *            @arg FLASH_BANK_2: Page in bank 2 to be erased (*)
  * @note   (*) availability depends on devices
  * @retval None
  */
void FLASH_PageErase(uint32_t Page, uint32_t Banks)
{
  /* Check the parameters */
  assert_param(IS_FLASH_PAGE(Page));

#if defined (FLASH_OPTR_DBANK)
  if (READ_BIT(FLASH->OPTR, FLASH_OPTR_DBANK) == 0U)
  {
    CLEAR_BIT(FLASH->CR, FLASH_CR_BKER);
  }
  else
  {
    assert_param(IS_FLASH_BANK_EXCLUSIVE(Banks));

    if ((Banks & FLASH_BANK_1) != 0U)
    {
      CLEAR_BIT(FLASH->CR, FLASH_CR_BKER);
    }
    else
    {
      SET_BIT(FLASH->CR, FLASH_CR_BKER);
    }
  }
#endif

  /* Proceed to erase the page */
  MODIFY_REG(FLASH->CR, FLASH_CR_PNB, ((Page & 0xFFU) << FLASH_CR_PNB_Pos));
  SET_BIT(FLASH->CR, FLASH_CR_PER);
  SET_BIT(FLASH->CR, FLASH_CR_STRT);
}

/**
  * @brief  Flush the instruction and data caches.
  * @retval None
  */
void FLASH_FlushCaches(void)
{
  FLASH_CacheTypeDef cache = pFlash.CacheToReactivate;

  /* Flush instruction cache  */
  if ((cache == FLASH_CACHE_ICACHE_ENABLED) ||
      (cache == FLASH_CACHE_ICACHE_DCACHE_ENABLED))
  {
    /* Reset instruction cache */
    __HAL_FLASH_INSTRUCTION_CACHE_RESET();
    /* Enable instruction cache */
    __HAL_FLASH_INSTRUCTION_CACHE_ENABLE();
  }

  /* Flush data cache */
  if ((cache == FLASH_CACHE_DCACHE_ENABLED) ||
      (cache == FLASH_CACHE_ICACHE_DCACHE_ENABLED))
  {
    /* Reset data cache */
    __HAL_FLASH_DATA_CACHE_RESET();
    /* Enable data cache */
    __HAL_FLASH_DATA_CACHE_ENABLE();
  }

  /* Reset internal variable */
  pFlash.CacheToReactivate = FLASH_CACHE_DISABLED;
}

/**
  * @brief  Configure the write protection area into Option Bytes.
  * @note   When the memory read protection level is selected (RDP level = 1),
  *         it is not possible to program or erase Flash memory if the CPU debug
  *         features are connected (JTAG or single wire) or boot code is being
  *         executed from RAM or System flash, even if WRP is not activated.
  * @note   To configure any option bytes, the option lock bit OPTLOCK must be
  *         cleared with the call of HAL_FLASH_OB_Unlock() function.
  * @note   New option bytes configuration will be taken into account in two cases:
  *         - after an option bytes launch through the call of HAL_FLASH_OB_Launch()
  *         - after a power reset (BOR reset or exit from Standby/Shutdown modes)
  * @param  WRPArea specifies the area to be configured.
  *         This parameter can be one of the following values:
  *            @arg OB_WRPAREA_BANK1_AREAA: Flash Bank 1 Area A
  *            @arg OB_WRPAREA_BANK1_AREAB: Flash Bank 1 Area B
  *            @arg OB_WRPAREA_BANK2_AREAA: Flash Bank 2 Area A (*)
  *            @arg OB_WRPAREA_BANK2_AREAB: Flash Bank 2 Area B (*)
  * @note   (*) availability depends on devices
  * @param  WRPStartOffset specifies the start page of the write protected area.
  *         This parameter can be page number between 0 and (max number of pages in the bank - 1).
  * @param  WRDPEndOffset specifies the end page of the write protected area.
  *         This parameter can be page number between WRPStartOffset and (max number of pages in the bank - 1).
  * @retval HAL_Status
  */
static HAL_StatusTypeDef FLASH_OB_WRPConfig(uint32_t WRPArea, uint32_t WRPStartOffset, uint32_t WRDPEndOffset)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_OB_WRPAREA(WRPArea));
  assert_param(IS_FLASH_PAGE(WRPStartOffset));
  assert_param(IS_FLASH_PAGE(WRDPEndOffset));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /* Configure the write protected area */
    if (WRPArea == OB_WRPAREA_BANK1_AREAA)
    {
      FLASH->WRP1AR = ((WRDPEndOffset << FLASH_WRP1AR_WRP1A_END_Pos) | WRPStartOffset);
    }
    else if (WRPArea == OB_WRPAREA_BANK1_AREAB)
    {
      FLASH->WRP1BR = ((WRDPEndOffset << FLASH_WRP1BR_WRP1B_END_Pos) | WRPStartOffset);
    }
#if defined (FLASH_OPTR_DBANK)
    else if (WRPArea == OB_WRPAREA_BANK2_AREAA)
    {
      FLASH->WRP2AR = ((WRDPEndOffset << FLASH_WRP2AR_WRP2A_END_Pos) | WRPStartOffset);
    }
    else if (WRPArea == OB_WRPAREA_BANK2_AREAB)
    {
      FLASH->WRP2BR = ((WRDPEndOffset << FLASH_WRP2BR_WRP2B_END_Pos) | WRPStartOffset);
    }
#endif
    else
    {
      /* Nothing to do */
    }

    /* Set OPTSTRT Bit */
    SET_BIT(FLASH->CR, FLASH_CR_OPTSTRT);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
  }

  return status;
}

/**
  * @brief  Set the read protection level into Option Bytes.
  * @note   To configure any option bytes, the option lock bit OPTLOCK must be
  *         cleared with the call of HAL_FLASH_OB_Unlock() function.
  * @note   New option bytes configuration will be taken into account in two cases:
  *         - after an option bytes launch through the call of HAL_FLASH_OB_Launch()
  *         - after a power reset (BOR reset or exit from Standby/Shutdown modes)
  * @note   !!! Warning : When enabling OB_RDP level 2 it's no more possible
  *         to go back to level 1 or 0 !!!
  * @param  RDPLevel specifies the read protection level.
  *         This parameter can be one of the following values:
  *            @arg OB_RDP_LEVEL_0: No protection
  *            @arg OB_RDP_LEVEL_1: Memory Read protection
  *            @arg OB_RDP_LEVEL_2: Full chip protection
  *
  * @retval HAL_Status
  */
static HAL_StatusTypeDef FLASH_OB_RDPConfig(uint32_t RDPLevel)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_OB_RDP_LEVEL(RDPLevel));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /* Configure the RDP level in the option bytes register */
    MODIFY_REG(FLASH->OPTR, FLASH_OPTR_RDP, RDPLevel);

    /* Set OPTSTRT Bit */
    SET_BIT(FLASH->CR, FLASH_CR_OPTSTRT);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
  }

  return status;
}

/**
  * @brief  Program the FLASH User Option Bytes.
  * @note   To configure any option bytes, the option lock bit OPTLOCK must be
  *         cleared with the call of HAL_FLASH_OB_Unlock() function.
  * @note   New option bytes configuration will be taken into account in two cases:
  *         - after an option bytes launch through the call of HAL_FLASH_OB_Launch()
  *         - after a power reset (BOR reset or exit from Standby/Shutdown modes)
  * @param  UserType The FLASH User Option Bytes to be modified.
  *         This parameter can be a combination of @ref FLASH_OB_USER_Type.
  * @param  UserConfig The selected User Option Bytes values:
  *         This parameter can be a combination of @ref FLASH_OB_USER_BOR_LEVEL,
  *         @ref FLASH_OB_USER_nRST_STOP, @ref FLASH_OB_USER_nRST_STANDBY ,
  *         @ref FLASH_OB_USER_nRST_SHUTDOWN, @ref FLASH_OB_USER_IWDG_SW,
  *         @ref FLASH_OB_USER_IWDG_STOP, @ref FLASH_OB_USER_IWDG_STANDBY,
  *         @ref FLASH_OB_USER_WWDG_SW, @ref FLASH_OB_USER_WWDG_SW,
  *         @ref FLASH_OB_USER_BFB2 (*), @ref FLASH_OB_USER_nBOOT1,
  *         @ref FLASH_OB_USER_SRAM_PE, @ref FLASH_OB_USER_CCMSRAM_RST,
  *         @ref FLASH_OB_USER_nSWBOOT0, @ref FLASH_OB_USER_nBOOT0,
  *         @ref FLASH_OB_USER_NRST_MODE, @ref FLASH_OB_USER_INTERNAL_RESET_HOLDER
  * @note   (*) availability depends on devices
  * @retval HAL_Status
  */
static HAL_StatusTypeDef FLASH_OB_UserConfig(uint32_t UserType, uint32_t UserConfig)
{
  uint32_t optr_reg_val = 0;
  uint32_t optr_reg_mask = 0;
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_OB_USER_TYPE(UserType));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    if ((UserType & OB_USER_BOR_LEV) != 0U)
    {
      /* BOR level option byte should be modified */
      assert_param(IS_OB_USER_BOR_LEVEL(UserConfig & FLASH_OPTR_BOR_LEV));

      /* Set value and mask for BOR level option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_BOR_LEV);
      optr_reg_mask |= FLASH_OPTR_BOR_LEV;
    }

    if ((UserType & OB_USER_nRST_STOP) != 0U)
    {
      /* nRST_STOP option byte should be modified */
      assert_param(IS_OB_USER_STOP(UserConfig & FLASH_OPTR_nRST_STOP));

      /* Set value and mask for nRST_STOP option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_nRST_STOP);
      optr_reg_mask |= FLASH_OPTR_nRST_STOP;
    }

    if ((UserType & OB_USER_nRST_STDBY) != 0U)
    {
      /* nRST_STDBY option byte should be modified */
      assert_param(IS_OB_USER_STANDBY(UserConfig & FLASH_OPTR_nRST_STDBY));

      /* Set value and mask for nRST_STDBY option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_nRST_STDBY);
      optr_reg_mask |= FLASH_OPTR_nRST_STDBY;
    }

    if ((UserType & OB_USER_nRST_SHDW) != 0U)
    {
      /* nRST_SHDW option byte should be modified */
      assert_param(IS_OB_USER_SHUTDOWN(UserConfig & FLASH_OPTR_nRST_SHDW));

      /* Set value and mask for nRST_SHDW option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_nRST_SHDW);
      optr_reg_mask |= FLASH_OPTR_nRST_SHDW;
    }

    if ((UserType & OB_USER_IWDG_SW) != 0U)
    {
      /* IWDG_SW option byte should be modified */
      assert_param(IS_OB_USER_IWDG(UserConfig & FLASH_OPTR_IWDG_SW));

      /* Set value and mask for IWDG_SW option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_IWDG_SW);
      optr_reg_mask |= FLASH_OPTR_IWDG_SW;
    }

    if ((UserType & OB_USER_IWDG_STOP) != 0U)
    {
      /* IWDG_STOP option byte should be modified */
      assert_param(IS_OB_USER_IWDG_STOP(UserConfig & FLASH_OPTR_IWDG_STOP));

      /* Set value and mask for IWDG_STOP option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_IWDG_STOP);
      optr_reg_mask |= FLASH_OPTR_IWDG_STOP;
    }

    if ((UserType & OB_USER_IWDG_STDBY) != 0U)
    {
      /* IWDG_STDBY option byte should be modified */
      assert_param(IS_OB_USER_IWDG_STDBY(UserConfig & FLASH_OPTR_IWDG_STDBY));

      /* Set value and mask for IWDG_STDBY option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_IWDG_STDBY);
      optr_reg_mask |= FLASH_OPTR_IWDG_STDBY;
    }

    if ((UserType & OB_USER_WWDG_SW) != 0U)
    {
      /* WWDG_SW option byte should be modified */
      assert_param(IS_OB_USER_WWDG(UserConfig & FLASH_OPTR_WWDG_SW));

      /* Set value and mask for WWDG_SW option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_WWDG_SW);
      optr_reg_mask |= FLASH_OPTR_WWDG_SW;
    }

#if defined (FLASH_OPTR_BFB2)
    if ((UserType & OB_USER_BFB2) != 0U)
    {
      /* BFB2 option byte should be modified */
      assert_param(IS_OB_USER_BFB2(UserConfig & FLASH_OPTR_BFB2));

      /* Set value and mask for BFB2 option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_BFB2);
      optr_reg_mask |= FLASH_OPTR_BFB2;
    }
#endif

    if ((UserType & OB_USER_nBOOT1) != 0U)
    {
      /* nBOOT1 option byte should be modified */
      assert_param(IS_OB_USER_BOOT1(UserConfig & FLASH_OPTR_nBOOT1));

      /* Set value and mask for nBOOT1 option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_nBOOT1);
      optr_reg_mask |= FLASH_OPTR_nBOOT1;
    }

    if ((UserType & OB_USER_SRAM_PE) != 0U)
    {
      /* SRAM_PE option byte should be modified */
      assert_param(IS_OB_USER_SRAM_PARITY(UserConfig & FLASH_OPTR_SRAM_PE));

      /* Set value and mask for SRAM_PE option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_SRAM_PE);
      optr_reg_mask |= FLASH_OPTR_SRAM_PE;
    }

    if ((UserType & OB_USER_CCMSRAM_RST) != 0U)
    {
      /* CCMSRAM_RST option byte should be modified */
      assert_param(IS_OB_USER_CCMSRAM_RST(UserConfig & FLASH_OPTR_CCMSRAM_RST));

      /* Set value and mask for CCMSRAM_RST option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_CCMSRAM_RST);
      optr_reg_mask |= FLASH_OPTR_CCMSRAM_RST;
    }

    if ((UserType & OB_USER_nSWBOOT0) != 0U)
    {
      /* nSWBOOT0 option byte should be modified */
      assert_param(IS_OB_USER_SWBOOT0(UserConfig & FLASH_OPTR_nSWBOOT0));

      /* Set value and mask for nSWBOOT0 option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_nSWBOOT0);
      optr_reg_mask |= FLASH_OPTR_nSWBOOT0;
    }

    if ((UserType & OB_USER_nBOOT0) != 0U)
    {
      /* nBOOT0 option byte should be modified */
      assert_param(IS_OB_USER_BOOT0(UserConfig & FLASH_OPTR_nBOOT0));

      /* Set value and mask for nBOOT0 option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_nBOOT0);
      optr_reg_mask |= FLASH_OPTR_nBOOT0;
    }

    if ((UserType & OB_USER_NRST_MODE) != 0U)
    {
      /* Reset Configuration option byte should be modified */
      assert_param(IS_OB_USER_NRST_MODE(UserConfig & FLASH_OPTR_NRST_MODE));

      /* Set value and mask for Reset Configuration option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_NRST_MODE);
      optr_reg_mask |= FLASH_OPTR_NRST_MODE;
    }

    if ((UserType & OB_USER_IRHEN) != 0U)
    {
      /* IRH option byte should be modified */
      assert_param(IS_OB_USER_IRHEN(UserConfig & FLASH_OPTR_IRHEN));

      /* Set value and mask for IRH option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTR_IRHEN);
      optr_reg_mask |= FLASH_OPTR_IRHEN;
    }

    /* Configure the option bytes register */
    MODIFY_REG(FLASH->OPTR, optr_reg_mask, optr_reg_val);

    /* Set OPTSTRT Bit */
    SET_BIT(FLASH->CR, FLASH_CR_OPTSTRT);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
  }

  return status;
}

/**
  * @brief  Configure the Proprietary code readout protection area into Option Bytes.
  * @note   To configure any option bytes, the option lock bit OPTLOCK must be
  *         cleared with the call of HAL_FLASH_OB_Unlock() function.
  * @note   New option bytes configuration will be taken into account in two cases:
  *         - after an option bytes launch through the call of HAL_FLASH_OB_Launch()
  *         - after a power reset (BOR reset or exit from Standby/Shutdown modes)
  * @param  PCROPConfig specifies the configuration (Bank to be configured and PCROP_RDP option).
  *         This parameter must be a combination of FLASH_BANK_1 or FLASH_BANK_2 (*)
  *         with OB_PCROP_RDP_NOT_ERASE or OB_PCROP_RDP_ERASE.
  * @note   (*) availability depends on devices
  * @param  PCROPStartAddr specifies the start address of the Proprietary code readout protection.
  *         This parameter can be an address between begin and end of the bank.
  * @param  PCROPEndAddr specifies the end address of the Proprietary code readout protection.
  *         This parameter can be an address between PCROPStartAddr and end of the bank.
  * @retval HAL_Status
  */
static HAL_StatusTypeDef FLASH_OB_PCROPConfig(uint32_t PCROPConfig, uint32_t PCROPStartAddr, uint32_t PCROPEndAddr)
{
  HAL_StatusTypeDef status;
  uint32_t reg_value;
  uint32_t bank1_addr;
#if defined (FLASH_OPTR_DBANK)
  uint32_t bank2_addr;
#endif

  /* Check the parameters */
  assert_param(IS_FLASH_BANK_EXCLUSIVE(PCROPConfig & FLASH_BANK_BOTH));
  assert_param(IS_OB_PCROP_RDP(PCROPConfig & FLASH_PCROP1ER_PCROP_RDP));
  assert_param(IS_FLASH_MAIN_MEM_ADDRESS(PCROPStartAddr));
  assert_param(IS_FLASH_MAIN_MEM_ADDRESS(PCROPEndAddr));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
#if defined (FLASH_OPTR_DBANK)
    /* Get the information about the bank swapping */
    if (READ_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_FB_MODE) == 0U)
    {
      bank1_addr = FLASH_BASE;
      bank2_addr = FLASH_BASE + FLASH_BANK_SIZE;
    }
    else
    {
      bank1_addr = FLASH_BASE + FLASH_BANK_SIZE;
      bank2_addr = FLASH_BASE;
    }
#else
    bank1_addr = FLASH_BASE;
#endif

#if defined (FLASH_OPTR_DBANK)
    if (READ_BIT(FLASH->OPTR, FLASH_OPTR_DBANK) == 0U)
    {
      /* Configure the Proprietary code readout protection */
      if ((PCROPConfig & FLASH_BANK_BOTH) == FLASH_BANK_1)
      {
        reg_value = ((PCROPStartAddr - FLASH_BASE) >> 4);
        MODIFY_REG(FLASH->PCROP1SR, FLASH_PCROP1SR_PCROP1_STRT, reg_value);

        reg_value = ((PCROPEndAddr - FLASH_BASE) >> 4);
        MODIFY_REG(FLASH->PCROP1ER, FLASH_PCROP1ER_PCROP1_END, reg_value);
      }
      else if ((PCROPConfig & FLASH_BANK_BOTH) == FLASH_BANK_2)
      {
        reg_value = ((PCROPStartAddr - FLASH_BASE) >> 4);
        MODIFY_REG(FLASH->PCROP2SR, FLASH_PCROP2SR_PCROP2_STRT, reg_value);

        reg_value = ((PCROPEndAddr - FLASH_BASE) >> 4);
        MODIFY_REG(FLASH->PCROP2ER, FLASH_PCROP2ER_PCROP2_END, reg_value);
      }
      else
      {
        /* Nothing to do */
      }
    }
    else
#endif
    {
      /* Configure the Proprietary code readout protection */
      if ((PCROPConfig & FLASH_BANK_BOTH) == FLASH_BANK_1)
      {
        reg_value = ((PCROPStartAddr - bank1_addr) >> 3);
        MODIFY_REG(FLASH->PCROP1SR, FLASH_PCROP1SR_PCROP1_STRT, reg_value);

        reg_value = ((PCROPEndAddr - bank1_addr) >> 3);
        MODIFY_REG(FLASH->PCROP1ER, FLASH_PCROP1ER_PCROP1_END, reg_value);
      }
#if defined (FLASH_OPTR_DBANK)
      else if ((PCROPConfig & FLASH_BANK_BOTH) == FLASH_BANK_2)
      {
        reg_value = ((PCROPStartAddr - bank2_addr) >> 3);
        MODIFY_REG(FLASH->PCROP2SR, FLASH_PCROP2SR_PCROP2_STRT, reg_value);

        reg_value = ((PCROPEndAddr - bank2_addr) >> 3);
        MODIFY_REG(FLASH->PCROP2ER, FLASH_PCROP2ER_PCROP2_END, reg_value);
      }
#endif
      else
      {
        /* Nothing to do */
      }
    }

    MODIFY_REG(FLASH->PCROP1ER, FLASH_PCROP1ER_PCROP_RDP, (PCROPConfig & FLASH_PCROP1ER_PCROP_RDP));

    /* Set OPTSTRT Bit */
    SET_BIT(FLASH->CR, FLASH_CR_OPTSTRT);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
  }

  return status;
}

/**
  * @brief  Configure the Securable memory area into Option Bytes.
  * @note   To configure any option bytes, the option lock bit OPTLOCK must be
  *         cleared with the call of HAL_FLASH_OB_Unlock() function.
  * @note   New option bytes configuration will be taken into account in two cases:
  *         - after an option bytes launch through the call of HAL_FLASH_OB_Launch()
  *         - after a power reset (BOR reset or exit from Standby/Shutdown modes)
  * @param  SecBank specifies bank of securable memory area to be configured.
  *          This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: Securable memory in Bank1 to be configured
  *            @arg FLASH_BANK_2: Securable memory in Bank2 to be configured (*)
  * @note   (*) availability depends on devices
  * @param  SecSize specifies the number of pages of the Securable memory area,
  *         starting from first page of the bank.
  *         This parameter can be page number between 0 and (max number of pages in the bank - 1)
  * @retval HAL Status
  */
static HAL_StatusTypeDef FLASH_OB_SecMemConfig(uint32_t SecBank, uint32_t SecSize)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_FLASH_BANK_EXCLUSIVE(SecBank));
  assert_param(IS_OB_SECMEM_SIZE(SecSize));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /* Configure the write protected area */
    if (SecBank == FLASH_BANK_1)
    {
      MODIFY_REG(FLASH->SEC1R, FLASH_SEC1R_SEC_SIZE1, SecSize);
    }
#if defined (FLASH_OPTR_DBANK)
    else if (SecBank == FLASH_BANK_2)
    {
      MODIFY_REG(FLASH->SEC2R, FLASH_SEC2R_SEC_SIZE2, SecSize);
    }
    else
    {
      /* Nothing to do */
    }
#endif

    /* Set OPTSTRT Bit */
    SET_BIT(FLASH->CR, FLASH_CR_OPTSTRT);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
  }

  return status;
}

/**
  * @brief  Configure the Boot Lock into Option Bytes.
  * @note   To configure any option bytes, the option lock bit OPTLOCK must be
  *         cleared with the call of HAL_FLASH_OB_Unlock() function.
  * @note   New option bytes configuration will be taken into account in two cases:
  *         - after an option bytes launch through the call of HAL_FLASH_OB_Launch()
  *         - after a power reset (BOR reset or exit from Standby/Shutdown modes)
  * @param  BootLockConfig specifies the boot lock configuration.
  *          This parameter can be one of the following values:
  *            @arg OB_BOOT_LOCK_ENABLE: Enable Boot Lock
  *            @arg OB_BOOT_LOCK_DISABLE: Disable Boot Lock
  *
  * @retval HAL_Status
  */
static HAL_StatusTypeDef FLASH_OB_BootLockConfig(uint32_t BootLockConfig)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_OB_BOOT_LOCK(BootLockConfig));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    MODIFY_REG(FLASH->SEC1R, FLASH_SEC1R_BOOT_LOCK, BootLockConfig);

    /* Set OPTSTRT Bit */
    SET_BIT(FLASH->CR, FLASH_CR_OPTSTRT);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
  }

  return status;
}

/**
  * @brief  Return the Securable memory area configuration into Option Bytes.
  * @param[in]  SecBank specifies the bank where securable memory area is located.
  *          This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: Securable memory in Bank1
  *            @arg FLASH_BANK_2: Securable memory in Bank2 (*)
  * @note   (*) availability depends on devices
  * @param[out]  SecSize specifies the number of pages used in the securable
                 memory area of the bank.
  * @retval None
  */
static void FLASH_OB_GetSecMem(uint32_t SecBank, uint32_t *SecSize)
{
  /* Get the configuration of the securable memory area */
  if (SecBank == FLASH_BANK_1)
  {
    *SecSize = READ_BIT(FLASH->SEC1R, FLASH_SEC1R_SEC_SIZE1);
  }
#if defined (FLASH_OPTR_DBANK)
  else if (SecBank == FLASH_BANK_2)
  {
    *SecSize = READ_BIT(FLASH->SEC2R, FLASH_SEC2R_SEC_SIZE2);
  }
  else
  {
    /* Nothing to do */
  }
#endif
}

/**
  * @brief  Return the Boot Lock configuration into Option Byte.
  * @retval BootLockConfig.
  *         This return value can be one of the following values:
  *            @arg OB_BOOT_LOCK_ENABLE: Boot lock enabled
  *            @arg OB_BOOT_LOCK_DISABLE: Boot lock disabled
  */
static uint32_t FLASH_OB_GetBootLock(void)
{
  return (READ_REG(FLASH->SEC1R) & FLASH_SEC1R_BOOT_LOCK);
}

/**
  * @brief  Return the Write Protection configuration into Option Bytes.
  * @param[in]  WRPArea specifies the area to be returned.
  *          This parameter can be one of the following values:
  *            @arg OB_WRPAREA_BANK1_AREAA: Flash Bank 1 Area A
  *            @arg OB_WRPAREA_BANK1_AREAB: Flash Bank 1 Area B
  *            @arg OB_WRPAREA_BANK2_AREAA: Flash Bank 2 Area A (don't apply to STM32G43x/STM32G44x devices)
  *            @arg OB_WRPAREA_BANK2_AREAB: Flash Bank 2 Area B (don't apply to STM32G43x/STM32G44x devices)
  * @param[out]  WRPStartOffset specifies the address where to copied the start page
  *              of the write protected area.
  * @param[out]  WRDPEndOffset specifies the address where to copied the end page of
  *              the write protected area.
  * @retval None
  */
static void FLASH_OB_GetWRP(uint32_t WRPArea, uint32_t *WRPStartOffset, uint32_t *WRDPEndOffset)
{
  /* Get the configuration of the write protected area */
  if (WRPArea == OB_WRPAREA_BANK1_AREAA)
  {
    *WRPStartOffset = READ_BIT(FLASH->WRP1AR, FLASH_WRP1AR_WRP1A_STRT);
    *WRDPEndOffset = (READ_BIT(FLASH->WRP1AR, FLASH_WRP1AR_WRP1A_END) >> FLASH_WRP1AR_WRP1A_END_Pos);
  }
  else if (WRPArea == OB_WRPAREA_BANK1_AREAB)
  {
    *WRPStartOffset = READ_BIT(FLASH->WRP1BR, FLASH_WRP1BR_WRP1B_STRT);
    *WRDPEndOffset = (READ_BIT(FLASH->WRP1BR, FLASH_WRP1BR_WRP1B_END) >> FLASH_WRP1BR_WRP1B_END_Pos);
  }
#if defined (FLASH_OPTR_DBANK)
  else if (WRPArea == OB_WRPAREA_BANK2_AREAA)
  {
    *WRPStartOffset = READ_BIT(FLASH->WRP2AR, FLASH_WRP2AR_WRP2A_STRT);
    *WRDPEndOffset = (READ_BIT(FLASH->WRP2AR, FLASH_WRP2AR_WRP2A_END) >> FLASH_WRP2AR_WRP2A_END_Pos);
  }
  else if (WRPArea == OB_WRPAREA_BANK2_AREAB)
  {
    *WRPStartOffset = READ_BIT(FLASH->WRP2BR, FLASH_WRP2BR_WRP2B_STRT);
    *WRDPEndOffset = (READ_BIT(FLASH->WRP2BR, FLASH_WRP2BR_WRP2B_END) >> FLASH_WRP2BR_WRP2B_END_Pos);
  }
#endif
  else
  {
    /* Nothing to do */
  }
}

/**
  * @brief  Return the FLASH Read Protection level into Option Bytes.
  * @retval RDP_Level
  *         This return value can be one of the following values:
  *            @arg OB_RDP_LEVEL_0: No protection
  *            @arg OB_RDP_LEVEL_1: Read protection of the memory
  *            @arg OB_RDP_LEVEL_2: Full chip protection
  */
static uint32_t FLASH_OB_GetRDP(void)
{
  uint32_t rdp_level = READ_BIT(FLASH->OPTR, FLASH_OPTR_RDP);

  if ((rdp_level != OB_RDP_LEVEL_0) && (rdp_level != OB_RDP_LEVEL_2))
  {
    return (OB_RDP_LEVEL_1);
  }
  else
  {
    return rdp_level;
  }
}

/**
  * @brief  Return the FLASH User Option Byte value.
  * @retval OB_user_config
  *         This return value is a combination of @ref FLASH_OB_USER_BOR_LEVEL,
  *         @ref FLASH_OB_USER_nRST_STOP, @ref FLASH_OB_USER_nRST_STANDBY,
  *         @ref FLASH_OB_USER_nRST_SHUTDOWN, @ref FLASH_OB_USER_IWDG_SW,
  *         @ref FLASH_OB_USER_IWDG_STOP, @ref FLASH_OB_USER_IWDG_STANDBY,
  *         @ref FLASH_OB_USER_WWDG_SW, @ref FLASH_OB_USER_WWDG_SW,
  *         @ref FLASH_OB_USER_BFB2 (*), @ref FLASH_OB_USER_DBANK (*),
  *         @ref FLASH_OB_USER_nBOOT1, @ref FLASH_OB_USER_SRAM_PE,
  *         @ref FLASH_OB_USER_CCMSRAM_RST, @ref OB_USER_nSWBOOT0,@ref FLASH_OB_USER_nBOOT0,
  *         @ref FLASH_OB_USER_NRST_MODE, @ref FLASH_OB_USER_INTERNAL_RESET_HOLDER
  * @note  (*) availability depends on devices
  */
static uint32_t FLASH_OB_GetUser(void)
{
  uint32_t user_config = READ_REG(FLASH->OPTR);
  CLEAR_BIT(user_config, FLASH_OPTR_RDP);

  return user_config;
}

/**
  * @brief  Return the FLASH PCROP configuration into Option Bytes.
  * @param[in,out] PCROPConfig specifies the configuration (Bank to be configured and PCROP_RDP option).
  *        This parameter must be a combination of FLASH_BANK_1 or FLASH_BANK_2
  *        with OB_PCROP_RDP_NOT_ERASE or OB_PCROP_RDP_ERASE.
  * @param[out] PCROPStartAddr specifies the address where to copied the start address
  *        of the Proprietary code readout protection.
  * @param[out] PCROPEndAddr specifies the address where to copied the end address of
  *        the Proprietary code readout protection.
  * @retval None
  */
static void FLASH_OB_GetPCROP(uint32_t *PCROPConfig, uint32_t *PCROPStartAddr, uint32_t *PCROPEndAddr)
{
  uint32_t reg_value;
  uint32_t bank1_addr;
#if defined (FLASH_OPTR_DBANK)
  uint32_t bank2_addr;

  /* Get the information about the bank swapping */
  if (READ_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_FB_MODE) == 0U)
  {
    bank1_addr = FLASH_BASE;
    bank2_addr = FLASH_BASE + FLASH_BANK_SIZE;
  }
  else
  {
    bank1_addr = FLASH_BASE + FLASH_BANK_SIZE;
    bank2_addr = FLASH_BASE;
  }
#else
  bank1_addr = FLASH_BASE;
#endif

#if defined (FLASH_OPTR_DBANK)
  if (READ_BIT(FLASH->OPTR, FLASH_OPTR_DBANK) == 0U)
  {
    if (((*PCROPConfig) & FLASH_BANK_BOTH) == FLASH_BANK_1)
    {
      reg_value       = (READ_REG(FLASH->PCROP1SR) & FLASH_PCROP1SR_PCROP1_STRT);
      *PCROPStartAddr = (reg_value << 4) + FLASH_BASE;

      reg_value     = (READ_REG(FLASH->PCROP1ER) & FLASH_PCROP1ER_PCROP1_END);
      *PCROPEndAddr = (reg_value << 4) + FLASH_BASE;
    }
    else if (((*PCROPConfig) & FLASH_BANK_BOTH) == FLASH_BANK_2)
    {
      reg_value       = (READ_REG(FLASH->PCROP2SR) & FLASH_PCROP2SR_PCROP2_STRT);
      *PCROPStartAddr = (reg_value << 4) + FLASH_BASE;

      reg_value     = (READ_REG(FLASH->PCROP2ER) & FLASH_PCROP2ER_PCROP2_END);
      *PCROPEndAddr = (reg_value << 4) + FLASH_BASE;
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
#endif
  {
    if (((*PCROPConfig) & FLASH_BANK_BOTH) == FLASH_BANK_1)
    {
      reg_value       = (READ_REG(FLASH->PCROP1SR) & FLASH_PCROP1SR_PCROP1_STRT);
      *PCROPStartAddr = (reg_value << 3) + bank1_addr;

      reg_value     = (READ_REG(FLASH->PCROP1ER) & FLASH_PCROP1ER_PCROP1_END);
      *PCROPEndAddr = (reg_value << 3) + bank1_addr;
    }
#if defined (FLASH_OPTR_DBANK)
    else if (((*PCROPConfig) & FLASH_BANK_BOTH) == FLASH_BANK_2)
    {
      reg_value       = (READ_REG(FLASH->PCROP2SR) & FLASH_PCROP2SR_PCROP2_STRT);
      *PCROPStartAddr = (reg_value << 3) + bank2_addr;

      reg_value     = (READ_REG(FLASH->PCROP2ER) & FLASH_PCROP2ER_PCROP2_END);
      *PCROPEndAddr = (reg_value << 3) + bank2_addr;
    }
#endif
    else
    {
      /* Nothing to do */
    }
  }

  *PCROPConfig |= (READ_REG(FLASH->PCROP1ER) & FLASH_PCROP1ER_PCROP_RDP);
}
/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_FLASH_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
