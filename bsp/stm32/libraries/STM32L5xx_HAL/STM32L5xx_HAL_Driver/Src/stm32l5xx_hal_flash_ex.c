/**
  ******************************************************************************
  * @file    stm32l5xx_hal_flash_ex.c
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

  [..] Comparing to other previous devices, the FLASH interface for STM32L5xx
       devices contains the following additional features

       (+) Capacity up to 512 Kbytes with dual bank architecture supporting read-while-write
           capability (RWW)
       (+) Dual bank memory organization with possibility of 128-bits single bank
       (+) Watermark-based secure area including secure hide areas
       (+) Block-based secure pages

                        ##### How to use this driver #####
 ==============================================================================
  [..] This driver provides functions to configure and program the FLASH memory
       of all STM32L5xx devices. It includes
      (#) Flash Memory Erase functions:
           (++) Lock and Unlock the FLASH interface using HAL_FLASH_Unlock() and
                HAL_FLASH_Lock() functions
           (++) Erase function: Erase page, mass erase of one or two banks
           (++) There are two modes of erase :
             (+++) Polling Mode using HAL_FLASHEx_Erase()
             (+++) Interrupt Mode using HAL_FLASHEx_Erase_IT()

      (#) Option Bytes Programming function: Use HAL_FLASHEx_OBProgram() to :
        (++) Configure the write protection for each area
        (++) Set the Read protection Level
        (++) Program the user Option Bytes
        (++) Configure the watermark security for each area including secure hide areas
        (++) Configure the boot lock (BOOT_LOCK)
        (++) Configure the Boot addresses

      (#) Get Option Bytes Configuration function: Use HAL_FLASHEx_OBGetConfig() to :
        (++) Get the value of a write protection area
        (++) Know if the read protection is activated
        (++) Get the value of the user Option Bytes
        (++) Get the configuration of a watermark security area including secure hide areas
        (++) Get the boot lock (BOOT_LOCK) configuration
        (++) Get the value of a boot address

      (#) Block-based secure area configuration function: Use HAL_FLASHEx_ConfigBBAttributes()
        (++) Bit-field allowing to secure or un-secure each page

      (#) Get the block-based secure area configuration function: Use HAL_FLASHEx_GetConfigBBAttributes()
        (++) Returns the configuration of the block-based security for all the pages

      (#) Activation of the secure hide area function: Use HAL_FLASHEx_EnableSecHideProtection()
        (++) Deny the access to the secure hide area

      (#) Privilege mode configuration function: Use HAL_FLASHEx_ConfigPrivMode()
        (++) FLASH register can be protected against non-privilege accesses

      (#) Get the privilege mode configuration function: Use HAL_FLASHEx_GetPrivMode()
        (++) Returns if the FLASH registers are protected against non-privilege accesses

      (#) Security inversion configuration function: Use HAL_FLASHEx_ConfigSecInversion()
        (++) FLASH secure state can be override

      (#) Get the security inversion configuration function: Use HAL_FLASHEx_GetSecInversion()
        (++) Returns if FLASH secure state is override

      (#) LVE pin management configuration function: Use HAL_FLASHEx_ConfigLVEPin()
        (++) LVE FLASH pin can be controlled either by power controller or enforced
             to low in order to use external SMPS

      (#) Get LVE pin management configuration function: Use HAL_FLASHEx_GetLVEPin()
        (++) Returns if LVE FLASH pin is controlled by power controller or enforced to low

 @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_hal.h"

/** @addtogroup STM32L5xx_HAL_Driver
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
static void     FLASH_MassErase(uint32_t Banks);
static void     FLASH_OB_WRPConfig(uint32_t WRPArea, uint32_t WRPStartOffset, uint32_t WRPEndOffset);
static void     FLASH_OB_RDPConfig(uint32_t RDPLevel);
static void     FLASH_OB_UserConfig(uint32_t UserType, uint32_t UserConfig);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
static void     FLASH_OB_WMSECConfig(uint32_t WMSecConfig, uint32_t WMSecStartPage, uint32_t WMSecEndPage, uint32_t WMHDPEndPage);
static void     FLASH_OB_BootLockConfig(uint32_t BootLockConfig);
#endif
static void     FLASH_OB_BootAddrConfig(uint32_t BootAddrConfig, uint32_t BootAddr);
static void     FLASH_OB_GetWRP(uint32_t WRPArea, uint32_t * WRPStartOffset, uint32_t * WRPEndOffset);
static uint32_t FLASH_OB_GetRDP(void);
static uint32_t FLASH_OB_GetUser(void);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
static void     FLASH_OB_GetWMSEC(uint32_t * WMSecConfig, uint32_t * WMSecStartPage, uint32_t * WMSecEndPage, uint32_t * WMHDPEndPage);
static uint32_t FLASH_OB_GetBootLock(void);
#endif
static void     FLASH_OB_GetBootAddr(uint32_t BootAddrConfig, uint32_t * BootAddr);
/**
  * @}
  */

/* Exported functions -------------------------------------------------------*/
/** @defgroup FLASHEx_Exported_Functions FLASH Extended Exported Functions
  * @{
  */

/** @defgroup FLASHEx_Exported_Functions_Group1 Extended Programming Operation functions
 *  @brief   Extended Programming Operation functions
 *
@verbatim
 ===============================================================================
                ##### Extended Programming Operation functions #####
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
  *
  * @param[out]  PageError   pointer to variable that contains the configuration
  *         information on faulty page in case of error (0xFFFFFFFF means that all
  *         the pages have been correctly erased)
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError)
{
  HAL_StatusTypeDef status;
  uint32_t page_index;
  __IO uint32_t *reg;

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    pFlash.ProcedureOnGoing = pEraseInit->TypeErase;

    reg = IS_FLASH_SECURE_OPERATION() ? &(FLASH->SECCR) : &(FLASH_NS->NSCR);

    if ((pFlash.ProcedureOnGoing & ~(FLASH_NON_SECURE_MASK)) == FLASH_TYPEERASE_MASSERASE)
    {
      /* Mass erase to be done */
      FLASH_MassErase(pEraseInit->Banks);

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
    }
    else
    {
      /*Initialization of PageError variable*/
      *PageError = 0xFFFFFFFFU;

      for(page_index = pEraseInit->Page; page_index < (pEraseInit->Page + pEraseInit->NbPages); page_index++)
      {
        FLASH_PageErase(page_index, pEraseInit->Banks);

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

        if (status != HAL_OK)
        {
          /* In case of error, stop erase procedure and return the faulty page */
          *PageError = page_index;
          break;
        }
      }
    }

    /* If the erase operation is completed, disable the associated bits */
    CLEAR_BIT((*reg), (pFlash.ProcedureOnGoing & ~(FLASH_NON_SECURE_MASK)));
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Perform a mass erase or erase the specified FLASH memory pages with interrupt enabled.
  * @param  pEraseInit pointer to an FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit)
{
  HAL_StatusTypeDef status;
  __IO uint32_t *reg_cr;

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status != HAL_OK)
  {
    /* Process Unlocked */
    __HAL_UNLOCK(&pFlash);
  }
  else
  {
    /* Set internal variables used by the IRQ handler */
    pFlash.ProcedureOnGoing = pEraseInit->TypeErase;
    pFlash.Bank = pEraseInit->Banks;
    
    /* Access to SECCR or NSCR depends on operation type */
    reg_cr = IS_FLASH_SECURE_OPERATION() ? &(FLASH->SECCR) : &(FLASH->NSCR);

    /* Enable End of Operation and Error interrupts */
    (*reg_cr) |= (FLASH_IT_EOP | FLASH_IT_OPERR);

    if ((pFlash.ProcedureOnGoing & ~(FLASH_NON_SECURE_MASK)) == FLASH_TYPEERASE_MASSERASE)
    {
      /* Mass erase to be done */
      FLASH_MassErase(pEraseInit->Banks);
    }
    else
    {
      /* Erase by page to be done */
      pFlash.NbPagesToErase = pEraseInit->NbPages;
      pFlash.Page = pEraseInit->Page;

      /*Erase 1st page and wait for IT */
      FLASH_PageErase(pEraseInit->Page, pEraseInit->Banks);
    }
  }

  return status;
}

/**
  * @brief  Program Option bytes.
  * @param  pOBInit pointer to an FLASH_OBInitStruct structure that
  *         contains the configuration information for the programming.
  *
  * @note   To configure any option bytes, the option lock bit OPTLOCK must be
  *         cleared with the call of HAL_FLASH_OB_Unlock() function.
  * @note   New option bytes configuration will be taken into account in two cases:
  *         - after an option bytes launch through the call of HAL_FLASH_OB_Launch()
  *         - after a power reset (BOR reset or exit from Standby/Shutdown modes)
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_OPTIONBYTE(pOBInit->OptionType));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Reset error code */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  {
    /* Write protection configuration */
    if((pOBInit->OptionType & OPTIONBYTE_WRP) != 0U)
    {
      /* Configure of Write protection on the selected area */
      FLASH_OB_WRPConfig(pOBInit->WRPArea, pOBInit->WRPStartOffset, pOBInit->WRPEndOffset);
    }

    /* Read protection configuration */
    if((pOBInit->OptionType & OPTIONBYTE_RDP) != 0U)
    {
      /* Configure the Read protection level */
      FLASH_OB_RDPConfig(pOBInit->RDPLevel);
    }

    /* User Configuration */
    if((pOBInit->OptionType & OPTIONBYTE_USER) != 0U)
    {
      /* Configure the user option bytes */
      FLASH_OB_UserConfig(pOBInit->USERType, pOBInit->USERConfig);
    }

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    /* Watermark secure configuration */
    if((pOBInit->OptionType & OPTIONBYTE_WMSEC) != 0U)
    {
      /* Configure the watermark-based secure area */
      FLASH_OB_WMSECConfig(pOBInit->WMSecConfig, pOBInit->WMSecStartPage, pOBInit->WMSecEndPage, pOBInit->WMHDPEndPage);
    }

    /* Unique boot entry point configuration */
    if((pOBInit->OptionType & OPTIONBYTE_BOOT_LOCK) != 0U)
    {
      /* Configure the unique boot entry point */
      FLASH_OB_BootLockConfig(pOBInit->BootLock);
    }
#endif

    /* Boot address configuration */
    if((pOBInit->OptionType & OPTIONBYTE_BOOTADDR) != 0U)
    {
      /* Configure the boot address */
      FLASH_OB_BootAddrConfig(pOBInit->BootAddrConfig, pOBInit->BootAddr);
    }

    /* Set OPTSTRT Bit */
    SET_BIT(FLASH->NSCR, FLASH_NSCR_OPTSTRT);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Get the Option bytes configuration.
  * @param  pOBInit pointer to an FLASH_OBInitStruct structure that contains the
  *                  configuration information.
  * @note   The fields pOBInit->WRPArea, pOBInit->WMSecConfig and pOBInit->BootAddrConfig
  *         should indicate which area/address is requested for the WRP, WM Security or
  *         Boot Address, else no information will be returned
  *
  * @retval None
  */
void HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit)
{
  pOBInit->OptionType = (OPTIONBYTE_RDP | OPTIONBYTE_USER);

  if((pOBInit->WRPArea == OB_WRPAREA_BANK1_AREAA) || (pOBInit->WRPArea == OB_WRPAREA_BANK1_AREAB) ||
     (pOBInit->WRPArea == OB_WRPAREA_BANK2_AREAA) || (pOBInit->WRPArea == OB_WRPAREA_BANK2_AREAB))
  {
    pOBInit->OptionType |= OPTIONBYTE_WRP;
    /* Get write protection on the selected area */
    FLASH_OB_GetWRP(pOBInit->WRPArea, &(pOBInit->WRPStartOffset), &(pOBInit->WRPEndOffset));
  }

  /* Get Read protection level */
  pOBInit->RDPLevel = FLASH_OB_GetRDP();

  /* Get the user option bytes */
  pOBInit->USERConfig = FLASH_OB_GetUser();

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  /* Get the configuration of the watermark secure area for the selected area */
  if ((pOBInit->WMSecConfig == OB_WMSEC_AREA1) || (pOBInit->WMSecConfig == OB_WMSEC_AREA2))
  {
    pOBInit->OptionType |= OPTIONBYTE_WMSEC;
    FLASH_OB_GetWMSEC(&(pOBInit->WMSecConfig), &(pOBInit->WMSecStartPage), &(pOBInit->WMSecEndPage), &(pOBInit->WMHDPEndPage));
  }

  pOBInit->OptionType |= OPTIONBYTE_BOOT_LOCK;

  /* Get the configuration of the unique boot entry point */
  pOBInit->BootLock = FLASH_OB_GetBootLock();
#endif

  /* Get the value of the selected boot address */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  if ((pOBInit->BootAddrConfig == OB_BOOTADDR_NS0) || (pOBInit->BootAddrConfig == OB_BOOTADDR_NS1) ||
      (pOBInit->BootAddrConfig == OB_BOOTADDR_SEC0))
#else
  if ((pOBInit->BootAddrConfig == OB_BOOTADDR_NS0) || (pOBInit->BootAddrConfig == OB_BOOTADDR_NS1))
#endif
  {
    pOBInit->OptionType |= OPTIONBYTE_BOOTADDR;
    FLASH_OB_GetBootAddr(pOBInit->BootAddrConfig, &(pOBInit->BootAddr));
  }
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Configure the block-based secure area.
  *
  * @param  pBBAttributes pointer to an FLASH_BBAttributesTypeDef structure that
  *         contains the configuration information for the programming.
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_ConfigBBAttributes(FLASH_BBAttributesTypeDef *pBBAttributes)
{
  HAL_StatusTypeDef status;
  uint8_t index;
  __IO uint32_t *reg;

  /* Check the parameters */
  assert_param(IS_FLASH_BANK_EXCLUSIVE(pBBAttributes->Bank));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    if (pBBAttributes->BBAttributesType == FLASH_BB_SEC)
    {
      if (pBBAttributes->Bank == FLASH_BANK_1)
      {
        reg = &(FLASH->SECBB1R1);
      }
      else
      {
        reg = &(FLASH->SECBB2R1);
      }

      /* Modify the register values and check that new attributes are taken in account */
      for (index = 0; index < FLASH_BLOCKBASED_NB_REG; index++)
      {
        *reg = pBBAttributes->BBAttributes_array[index];
        if (*reg != pBBAttributes->BBAttributes_array[index])
        {
          status = HAL_ERROR;
        }
        reg++;
      }
    }

    /* ISB instruction is called to be sure next instructions are performed with correct attributes */
    __ISB();
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Return the block-based secure area.
  *
  * @param  pBBAttributes [in/out] pointer to an FLASH_BBAttributesTypeDef structure
  *                  that contains theconfiguration information.
  * @note   The fields pBBAttributes->BBSecConfig should indicate which area is requested
  *          for the block-based security, else no information will be returned
  *
  * @retval None
  */
void HAL_FLASHEx_GetConfigBBAttributes(FLASH_BBAttributesTypeDef *pBBAttributes)
{
  uint8_t index;
  __IO uint32_t *reg;

  /* Check the parameters */
  assert_param(IS_FLASH_BANK_EXCLUSIVE(pBBAttributes->Bank));

  if (pBBAttributes->BBAttributesType == FLASH_BB_SEC)
  {
    if (pBBAttributes->Bank == FLASH_BANK_1)
    {
      reg = &(FLASH->SECBB1R1);
    }
    else
    {
      reg = &(FLASH->SECBB2R1);
    }

    for (index = 0; index < FLASH_BLOCKBASED_NB_REG; index++)
    {
      pBBAttributes->BBAttributes_array[index] = *reg;
      reg++;
    }
  }
}

/**
  * @brief  Activation of the protection of the secure hide area.
  *
  * @param  Banks indicate the bank concerned by the activation
  *          This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: Bank1
  *            @arg FLASH_BANK_2: Bank2
  *            @arg FLASH_BANK_BOTH: Bank1 & Bank2
  *
  * @retval None
  */
void HAL_FLASHEx_EnableSecHideProtection(uint32_t Banks)
{
  /* Check the parameters */
  assert_param(IS_FLASH_BANK(Banks));

  if ((Banks & FLASH_BANK_1) != 0U)
  {
    SET_BIT(FLASH->SECHDPCR, FLASH_SECHDPCR_HDP1_ACCDIS);
  }
  if((Banks & FLASH_BANK_2) != 0U)
  {
    SET_BIT(FLASH->SECHDPCR, FLASH_SECHDPCR_HDP2_ACCDIS);
  }
}
#endif

/**
  * @}
  */

/** @defgroup FLASHEx_Exported_Functions_Group2 Extended Peripheral Control functions
 *  @brief   Extended Peripheral Control functions
 *
@verbatim
 ===============================================================================
                      ##### Extended Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the FLASH
    memory operations.

@endverbatim
  * @{
  */

/**
  * @brief  Configuration of the privilege attribute.
  *
  * @param  PrivMode indicate privilege mode configuration
  *          This parameter can be one of the following values:
  *            @arg FLASH_PRIV_GRANTED: access to Flash registers is granted
  *            @arg FLASH_PRIV_DENIED: access to Flash registers is denied to non-privilege access
  *
  * @retval None
  */
void HAL_FLASHEx_ConfigPrivMode(uint32_t PrivMode)
{
  /* Check the parameters */
  assert_param(IS_FLASH_CFGPRIVMODE(PrivMode));

  MODIFY_REG(FLASH->PRIVCFGR, FLASH_PRIVCFGR_PRIV, PrivMode);
}

/**
  * @brief  Return the value of the privilege attribute.
  *
  * @retval  It indicates privilege mode configuration.
  *          This return value can be one of the following values:
  *            @arg FLASH_PRIV_GRANTED: access to Flash registers is granted
  *            @arg FLASH_PRIV_DENIED: access to Flash registers is denied to non-privilege access
  */
uint32_t HAL_FLASHEx_GetPrivMode(void)
{
  return (FLASH->PRIVCFGR & FLASH_PRIVCFGR_PRIV);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Configuration of the security inversion.
  *
  * @param  SecInvState indicate the flash security state configuration
  *          This parameter can be one of the following values:
  *            @arg FLASH_SEC_INV_DISABLE: Security state of Flash is not inverted
  *            @arg FLASH_SEC_INV_ENABLE: Security state of Flash is inverted
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_ConfigSecInversion(uint32_t SecInvState)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_FLASH_CFGSECINV(SecInvState));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    MODIFY_REG(FLASH->SECCR, FLASH_SECCR_SECINV, SecInvState);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Return the value of the security inversion.
  *
  * @retval  It indicates the flash security state configuration
  *          This return value can be one of the following values:
  *            @arg FLASH_SEC_INV_DISABLE: Security state of Flash is not inverted
  *            @arg FLASH_SEC_INV_ENABLE: Security state of Flash is inverted
  */
uint32_t HAL_FLASHEx_GetSecInversion(void)
{
  return (FLASH->SECCR & FLASH_SECCR_SECINV);
}
#endif

/**
  * @brief  Configuration of the LVE pin management.
  *
  * @param  ConfigLVE indicate the LVE pin management configuration
  *          This parameter can be one of the following values:
  *            @arg FLASH_LVE_PIN_CTRL: LVEA/B FLASH pin controlled by power controller
  *            @arg FLASH_LVE_PIN_FORCED: LVEA/B FLASH pin enforced to low
  *
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_ConfigLVEPin(uint32_t ConfigLVE)
{
  HAL_StatusTypeDef status;

  /* Check the parameters */
  assert_param(IS_FLASH_CFGLVEPIN(ConfigLVE));

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /* Check that the voltage scaling is range 2 */
    if (HAL_PWREx_GetVoltageRange() == PWR_REGULATOR_VOLTAGE_SCALE2)
    {
      /* Unlock the bit LVEN */
      FLASH->LVEKEYR = FLASH_LVEKEY1;
      FLASH->LVEKEYR = FLASH_LVEKEY2;

      /* Modify the value of LVEN bit */
      MODIFY_REG(FLASH->ACR, FLASH_ACR_LVEN, ConfigLVE);

      /* Check that the bit has been correctly configured */
      if (READ_BIT(FLASH->ACR, FLASH_ACR_LVEN) != ConfigLVE)
      {
        status = HAL_ERROR;
      }
    }
    else
    {
      /* Not allow to force Flash LVE pin if not in voltage range 2 */
      status = HAL_ERROR;
    }
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Return the value of the LVE pin management.
  *
  * @retval  It indicates the LVE pin management configuration
  *          This return value can be one of the following values:
  *            @arg FLASH_LVE_PIN_CTRL: LVEA/B FLASH pin controlled by power controller
  *            @arg FLASH_LVE_PIN_FORCED: LVEA/B FLASH pin enforces to low
  */
uint32_t HAL_FLASHEx_GetLVEPin(void)
{
  return (FLASH->ACR & FLASH_ACR_LVEN);
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
  * @param  Banks Banks to be erased
  *          This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: Bank1 to be erased
  *            @arg FLASH_BANK_2: Bank2 to be erased
  *            @arg FLASH_BANK_BOTH: Bank1 and Bank2 to be erased
  * @retval None
  */
static void FLASH_MassErase(uint32_t Banks)
{
  __IO uint32_t *reg;
  
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  uint32_t primask_bit;

  /* Disable interrupts to avoid any interruption */
  primask_bit = __get_PRIMASK();
  __disable_irq();
#endif
  
  /* Access to SECCR or NSCR registers depends on operation type */
  reg = IS_FLASH_SECURE_OPERATION() ? &(FLASH->SECCR) : &(FLASH_NS->NSCR);

  if (READ_BIT(FLASH->OPTR, FLASH_OPTR_DBANK) != 0U)
  {
    /* Check the parameters */
    assert_param(IS_FLASH_BANK(Banks));

    /* Set the Mass Erase Bit for the bank 1 if requested */
    if((Banks & FLASH_BANK_1) != 0U)
    {
      SET_BIT((*reg), FLASH_NSCR_NSMER1);
    }

    /* Set the Mass Erase Bit for the bank 2 if requested */
    if((Banks & FLASH_BANK_2) != 0U)
    {
      SET_BIT((*reg), FLASH_NSCR_NSMER2);
    }
  }
  else
  {
    SET_BIT((*reg), (FLASH_NSCR_NSMER1 | FLASH_NSCR_NSMER2));
  }

  /* Proceed to erase all sectors */
  SET_BIT((*reg), FLASH_NSCR_NSSTRT);

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  /* Re-enable the interrupts */
  __set_PRIMASK(primask_bit);
#endif
}

/**
  * @brief  Erase the specified FLASH memory page.
  * @param  Page FLASH page to erase
  *         This parameter must be a value between 0 and (max number of pages in the bank - 1)
  * @param  Banks Bank(s) where the page will be erased
  *          This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: Page in bank 1 to be erased
  *            @arg FLASH_BANK_2: Page in bank 2 to be erased
  * @retval None
  */
void FLASH_PageErase(uint32_t Page, uint32_t Banks)
{
  __IO uint32_t *reg;
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  uint32_t primask_bit;
#endif
  /* Check the parameters */
  assert_param(IS_FLASH_PAGE(Page));

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  /* Disable interrupts to avoid any interruption */
  primask_bit = __get_PRIMASK();
  __disable_irq();
#endif

  /* Access to SECCR or NSCR registers depends on operation type */
  reg = IS_FLASH_SECURE_OPERATION() ? &(FLASH->SECCR) : &(FLASH_NS->NSCR);

  if(READ_BIT(FLASH->OPTR, FLASH_OPTR_DBANK) == 0U)
  {
    CLEAR_BIT((*reg), FLASH_NSCR_NSBKER);
  }
  else
  {
    assert_param(IS_FLASH_BANK_EXCLUSIVE(Banks));

    if((Banks & FLASH_BANK_1) != 0U)
    {
      CLEAR_BIT((*reg), FLASH_NSCR_NSBKER);
    }
    else
    {
      SET_BIT((*reg), FLASH_NSCR_NSBKER);
    }
  }

  /* Proceed to erase the page */
  MODIFY_REG((*reg), (FLASH_NSCR_NSPNB | FLASH_NSCR_NSPER), ((Page << FLASH_NSCR_NSPNB_Pos) | FLASH_NSCR_NSPER));
  SET_BIT((*reg), FLASH_NSCR_NSSTRT);

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  /* Re-enable the interrupts */
  __set_PRIMASK(primask_bit);
#endif
}

/**
  * @brief  Configure the write protection of the desired pages.
  *
  * @note   When the memory read protection level is selected (RDP level = 1),
  *         it is not possible to program or erase Flash memory if the CPU debug
  *         features are connected (JTAG or single wire) or boot code is being
  *         executed from RAM or System flash, even if WRP is not activated.
  * @note   To configure the WRP options, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_OB_Unlock() function.
  * @note   To validate the WRP options, the option bytes must be reloaded
  *         through the call of the HAL_FLASH_OB_Launch() function.
  *
  * @param  WRPArea specifies the area to be configured.
  *          This parameter can be one of the following values:
  *            @arg OB_WRPAREA_BANK1_AREAA: Flash Bank 1 Area A
  *            @arg OB_WRPAREA_BANK1_AREAB: Flash Bank 1 Area B
  *            @arg OB_WRPAREA_BANK2_AREAA: Flash Bank 2 Area A
  *            @arg OB_WRPAREA_BANK2_AREAB: Flash Bank 2 Area B
  *
  * @param  WRPStartOffset specifies the start page of the write protected area
  *          This parameter can be page number between 0 and (max number of pages in the bank - 1)
  *
  * @param  WRPEndOffset specifies the end page of the write protected area
  *          This parameter can be page number between WRPStartOffset and (max number of pages in the bank - 1)
  *
  * @retval None
  */
static void FLASH_OB_WRPConfig(uint32_t WRPArea, uint32_t WRPStartOffset, uint32_t WRPEndOffset)
{
  /* Check the parameters */
  assert_param(IS_OB_WRPAREA(WRPArea));
  assert_param(IS_FLASH_PAGE(WRPStartOffset));
  assert_param(IS_FLASH_PAGE(WRPEndOffset));

  /* Configure the write protected area */
  if(WRPArea == OB_WRPAREA_BANK1_AREAA)
  {
    MODIFY_REG(FLASH->WRP1AR, (FLASH_WRP1AR_WRP1A_PSTRT | FLASH_WRP1AR_WRP1A_PEND),
               (WRPStartOffset | (WRPEndOffset << FLASH_WRP1AR_WRP1A_PEND_Pos)));
  }
  else if(WRPArea == OB_WRPAREA_BANK1_AREAB)
  {
    MODIFY_REG(FLASH->WRP1BR, (FLASH_WRP1BR_WRP1B_PSTRT | FLASH_WRP1BR_WRP1B_PEND),
               (WRPStartOffset | (WRPEndOffset << FLASH_WRP1BR_WRP1B_PEND_Pos)));
  }
  else if(WRPArea == OB_WRPAREA_BANK2_AREAA)
  {
    MODIFY_REG(FLASH->WRP2AR, (FLASH_WRP2AR_WRP2A_PSTRT | FLASH_WRP2AR_WRP2A_PEND),
               (WRPStartOffset | (WRPEndOffset << FLASH_WRP2AR_WRP2A_PEND_Pos)));
  }
  else if(WRPArea == OB_WRPAREA_BANK2_AREAB)
  {
    MODIFY_REG(FLASH->WRP2BR, (FLASH_WRP2BR_WRP2B_PSTRT | FLASH_WRP2BR_WRP2B_PEND),
               (WRPStartOffset | (WRPEndOffset << FLASH_WRP2BR_WRP2B_PEND_Pos)));
  }
  else
  {
    /* Empty statement (to be compliant MISRA 15.7) */
  }
}

/**
  * @brief  Set the read protection level.
  *
  * @note   To configure the RDP level, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_OB_Unlock() function.
  * @note   To validate the RDP level, the option bytes must be reloaded
  *         through the call of the HAL_FLASH_OB_Launch() function.
  * @note   !!! Warning : When enabling OB_RDP level 2 it's no more possible
  *         to go back to other levels !!!
  *
  * @param  RDPLevel specifies the read protection level.
  *         This parameter can be one of the following values:
  *            @arg OB_RDP_LEVEL_0: No protection
  *            @arg OB_RDP_LEVEL_0_5: No debug access to secure area
  *            @arg OB_RDP_LEVEL_1: Read protection of the memory
  *            @arg OB_RDP_LEVEL_2: Full chip protection
  *
  * @retval None
  */
static void FLASH_OB_RDPConfig(uint32_t RDPLevel)
{
  /* Check the parameters */
  assert_param(IS_OB_RDP_LEVEL(RDPLevel));

  /* Configure the RDP level in the option bytes register */
  MODIFY_REG(FLASH->OPTR, FLASH_OPTR_RDP, RDPLevel);
}

/**
  * @brief  Program the FLASH User Option Byte.
  *
  * @note   To configure the user option bytes, the option lock bit OPTLOCK must
  *         be cleared with the call of the HAL_FLASH_OB_Unlock() function.
  * @note   To validate the user option bytes, the option bytes must be reloaded
  *         through the call of the HAL_FLASH_OB_Launch() function.
  *
  * @param  UserType The FLASH User Option Bytes to be modified
  *         This parameter can be a combination of @ref FLASH_OB_USER_Type
  * @param  UserConfig The FLASH User Option Bytes values.
  *         It can be a combination of @ref FLASH_OB_USER_BOR_LEVEL,
  *         @ref FLASH_OB_USER_nRST_STOP, @ref FLASH_OB_USER_nRST_STANDBY,
  *         @ref FLASH_OB_USER_nRST_SHUTDOWN, @ref FLASH_OB_USER_IWDG_SW,
  *         @ref FLASH_OB_USER_IWDG_STOP, @ref FLASH_OB_USER_IWDG_STANDBY,
  *         @ref FLASH_OB_USER_WWDG_SW, @ref OB_USER_SWAP_BANK,
  *         @ref FLASH_OB_USER_DUALBANK, @ref FLASH_OB_USER_DBANK,
  *         @ref FLASH_OB_USER_SRAM2_PAR, @ref FLASH_OB_USER_SRAM2_RST,
  *         @ref OB_USER_nSWBOOT0, @ref OB_USER_nBOOT0, @ref FLASH_OB_USER_PA15_PUPEN
  *         and @ref OB_USER_TZEN
  *
  * @retval None
  */
static void FLASH_OB_UserConfig(uint32_t UserType, uint32_t UserConfig)
{
  uint32_t optr_reg_val = 0;
  uint32_t optr_reg_mask = 0;

  /* Check the parameters */
  assert_param(IS_OB_USER_TYPE(UserType));

  if((UserType & OB_USER_BOR_LEV) != 0U)
  {
    /* BOR level option byte should be modified */
    assert_param(IS_OB_USER_BOR_LEVEL(UserConfig & FLASH_OPTR_BOR_LEV));

    /* Set value and mask for BOR level option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_BOR_LEV);
    optr_reg_mask |= FLASH_OPTR_BOR_LEV;
  }

  if((UserType & OB_USER_nRST_STOP) != 0U)
  {
    /* nRST_STOP option byte should be modified */
    assert_param(IS_OB_USER_STOP(UserConfig & FLASH_OPTR_nRST_STOP));

    /* Set value and mask for nRST_STOP option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_nRST_STOP);
    optr_reg_mask |= FLASH_OPTR_nRST_STOP;
  }

  if((UserType & OB_USER_nRST_STDBY) != 0U)
  {
    /* nRST_STDBY option byte should be modified */
    assert_param(IS_OB_USER_STANDBY(UserConfig & FLASH_OPTR_nRST_STDBY));

    /* Set value and mask for nRST_STDBY option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_nRST_STDBY);
    optr_reg_mask |= FLASH_OPTR_nRST_STDBY;
  }

  if((UserType & OB_USER_nRST_SHDW) != 0U)
  {
    /* nRST_SHDW option byte should be modified */
    assert_param(IS_OB_USER_SHUTDOWN(UserConfig & FLASH_OPTR_nRST_SHDW));

    /* Set value and mask for nRST_SHDW option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_nRST_SHDW);
    optr_reg_mask |= FLASH_OPTR_nRST_SHDW;
  }

  if((UserType & OB_USER_IWDG_SW) != 0U)
  {
    /* IWDG_SW option byte should be modified */
    assert_param(IS_OB_USER_IWDG(UserConfig & FLASH_OPTR_IWDG_SW));

    /* Set value and mask for IWDG_SW option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_IWDG_SW);
    optr_reg_mask |= FLASH_OPTR_IWDG_SW;
  }

  if((UserType & OB_USER_IWDG_STOP) != 0U)
  {
    /* IWDG_STOP option byte should be modified */
    assert_param(IS_OB_USER_IWDG_STOP(UserConfig & FLASH_OPTR_IWDG_STOP));

    /* Set value and mask for IWDG_STOP option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_IWDG_STOP);
    optr_reg_mask |= FLASH_OPTR_IWDG_STOP;
  }

  if((UserType & OB_USER_IWDG_STDBY) != 0U)
  {
    /* IWDG_STDBY option byte should be modified */
    assert_param(IS_OB_USER_IWDG_STDBY(UserConfig & FLASH_OPTR_IWDG_STDBY));

    /* Set value and mask for IWDG_STDBY option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_IWDG_STDBY);
    optr_reg_mask |= FLASH_OPTR_IWDG_STDBY;
  }

  if((UserType & OB_USER_WWDG_SW) != 0U)
  {
    /* WWDG_SW option byte should be modified */
    assert_param(IS_OB_USER_WWDG(UserConfig & FLASH_OPTR_WWDG_SW));

    /* Set value and mask for WWDG_SW option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_WWDG_SW);
    optr_reg_mask |= FLASH_OPTR_WWDG_SW;
  }

  if((UserType & OB_USER_SWAP_BANK) != 0U)
  {
    /* SWAP_BANK option byte should be modified */
    assert_param(IS_OB_USER_SWAP_BANK(UserConfig & FLASH_OPTR_SWAP_BANK));

    /* Set value and mask for SWAP_BANK option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_SWAP_BANK);
    optr_reg_mask |= FLASH_OPTR_SWAP_BANK;
  }

  if((UserType & OB_USER_DUALBANK) != 0U)
  {
    /* DUALBANK option byte should be modified */
    assert_param(IS_OB_USER_DUALBANK(UserConfig & FLASH_OPTR_DB256K));

    /* Set value and mask for DB256K option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_DB256K);
    optr_reg_mask |= FLASH_OPTR_DB256K;
  }

  if((UserType & OB_USER_SRAM2_PE) != 0U)
  {
    /* SRAM2_PAR option byte should be modified */
    assert_param(IS_OB_USER_SRAM2_PARITY(UserConfig & FLASH_OPTR_SRAM2_PE));

    /* Set value and mask for SRAM2_PAR option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_SRAM2_PE);
    optr_reg_mask |= FLASH_OPTR_SRAM2_PE;
  }

  if((UserType & OB_USER_SRAM2_RST) != 0U)
  {
    /* SRAM2_RST option byte should be modified */
    assert_param(IS_OB_USER_SRAM2_RST(UserConfig & FLASH_OPTR_SRAM2_RST));

    /* Set value and mask for SRAM2_RST option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_SRAM2_RST);
    optr_reg_mask |= FLASH_OPTR_SRAM2_RST;
  }

  if((UserType & OB_USER_nSWBOOT0) != 0U)
  {
    /* nSWBOOT0 option byte should be modified */
    assert_param(IS_OB_USER_SWBOOT0(UserConfig & FLASH_OPTR_nSWBOOT0));

    /* Set value and mask for nSWBOOT0 option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_nSWBOOT0);
    optr_reg_mask |= FLASH_OPTR_nSWBOOT0;
  }

  if((UserType & OB_USER_nBOOT0) != 0U)
  {
    /* nBOOT0 option byte should be modified */
    assert_param(IS_OB_USER_BOOT0(UserConfig & FLASH_OPTR_nBOOT0));

    /* Set value and mask for nBOOT0 option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_nBOOT0);
    optr_reg_mask |= FLASH_OPTR_nBOOT0;
  }

  if((UserType & OB_USER_PA15_PUPEN) != 0U)
  {
    /* nBOOT0 option byte should be modified */
    assert_param(IS_OB_USER_PA15_PUPEN(UserConfig & FLASH_OPTR_PA15_PUPEN));

    /* Set value and mask for nBOOT0 option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_PA15_PUPEN);
    optr_reg_mask |= FLASH_OPTR_PA15_PUPEN;
  }

  if((UserType & OB_USER_TZEN) != 0U)
  {
    /* TZEN option byte should be modified */
    assert_param(IS_OB_USER_TZEN(UserConfig & FLASH_OPTR_TZEN));

    /* Set value and mask for TZEN option byte */
    optr_reg_val |= (UserConfig & FLASH_OPTR_TZEN);
    optr_reg_mask |= FLASH_OPTR_TZEN;
  }

  /* Configure the option bytes register */
  MODIFY_REG(FLASH->OPTR, optr_reg_mask, optr_reg_val);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Configure the watermarked-based secure area.
  *
  * @param  WMSecConfig specifies the area to be configured.
  *          This parameter can be a combination of the following values:
  *            @arg OB_WMSEC_AREA1 or @arg OB_WMSEC_AREA2: Select Flash Secure Area 1 or Area 2
  *            @arg OB_WMSEC_SECURE_AREA_CONFIG: configure Flash Secure Area
  *            @arg OB_WMSEC_HDP_AREA_CONFIG: configure Flash secure hide Area
  *            @arg OB_WMSEC_HDP_AREA_ENABLE: enable secure hide Area in Secure Area
  *            @arg OB_WMSEC_HDP_AREA_DISABLE: disable secure hide Area in Secure Area
  *
  * @param  WMSecStartPage specifies the start page of the secure area
  *          This parameter can be page number between 0 and (max number of pages in the bank - 1)
  *
  * @param  WMSecEndPage specifies the end page of the secure area
  *          This parameter can be page number between WMSecStartPage and (max number of pages in the bank - 1)
  *
  * @param  WMHDPEndPage specifies the end page of the secure hide area
  *          This parameter can be page number between WMSecStartPage and WMPCROPStartPage
  *
  * @retval None
  */
static void FLASH_OB_WMSECConfig(uint32_t WMSecConfig, uint32_t WMSecStartPage, uint32_t WMSecEndPage, uint32_t WMHDPEndPage)
{
  uint32_t tmp_secwm1 = 0U, tmp_secwm2 = 0U;

  /* Check the parameters */
  assert_param(IS_OB_WMSEC_CONFIG(WMSecConfig));
  assert_param(IS_OB_WMSEC_AREA_EXCLUSIVE(WMSecConfig & 0x3U));
  assert_param(IS_FLASH_PAGE(WMSecStartPage));
  assert_param(IS_FLASH_PAGE(WMSecEndPage));
  assert_param(IS_FLASH_PAGE(WMHDPEndPage));

  /* Read SECWM registers */
  if ((WMSecConfig & OB_WMSEC_AREA1) != 0U)
  {
    tmp_secwm1 = FLASH->SECWM1R1;
    tmp_secwm2 = FLASH->SECWM1R2;
  }
  else if ((WMSecConfig & OB_WMSEC_AREA2) != 0U)
  {
    tmp_secwm1 = FLASH->SECWM2R1;
    tmp_secwm2 = FLASH->SECWM2R2;
  }
  else
  {
    /* Nothing to do */
  }

  /* Configure Secure Area */
  if ((WMSecConfig & OB_WMSEC_SECURE_AREA_CONFIG) != 0U)
  {
    MODIFY_REG(tmp_secwm1, (FLASH_SECWM1R1_SECWM1_PSTRT | FLASH_SECWM1R1_SECWM1_PEND),
               ((WMSecEndPage << FLASH_SECWM1R1_SECWM1_PEND_Pos) | WMSecStartPage));
  }

  /* Configure Secure Hide Area */
  if ((WMSecConfig & OB_WMSEC_HDP_AREA_CONFIG) != 0U)
  {
    tmp_secwm2 &= (~(FLASH_SECWM1R2_HDP1_PEND));
    tmp_secwm2 |= (WMHDPEndPage << FLASH_SECWM1R2_HDP1_PEND_Pos);
  }

  /* Enable Secure Hide Area */
  if ((WMSecConfig & OB_WMSEC_HDP_AREA_ENABLE) != 0U)
  {
    tmp_secwm2 |= FLASH_SECWM1R2_HDP1EN;
  }

  /* Disable Secure Hide Area */
  if ((WMSecConfig & OB_WMSEC_HDP_AREA_DISABLE) != 0U)
  {
    tmp_secwm2 &= (~FLASH_SECWM1R2_HDP1EN);
  }

  /* Write SECWM registers */
  if ((WMSecConfig & OB_WMSEC_AREA1) != 0U)
  {
    FLASH->SECWM1R1 = tmp_secwm1;
    FLASH->SECWM1R2 = tmp_secwm2;
  }
  else if ((WMSecConfig & OB_WMSEC_AREA2) != 0U)
  {
    FLASH->SECWM2R1 = tmp_secwm1;
    FLASH->SECWM2R2 = tmp_secwm2;
  }
  else
  {
    /* Nothing to do */
  }
}

/**
  * @brief  Configure the boot lock.
  *
  * @param  BootLockConfig specifies the activation of the BOOT_LOCK.
  *          This parameter can be one of the following values:
  *            @arg OB_BOOT_LOCK_DISABLE: Boot Lock mode deactivated
  *            @arg OB_BOOT_LOCK_ENABLE: Boot Lock mode activated
  *
  * @retval None
  */
static void FLASH_OB_BootLockConfig(uint32_t BootLockConfig)
{
  /* Check the parameters */
  assert_param(IS_OB_BOOT_LOCK(BootLockConfig));

  /* Configure the option bytes register */
  MODIFY_REG(FLASH->SECBOOTADD0R, FLASH_SECBOOTADD0R_BOOT_LOCK, BootLockConfig);
}
#endif

/**
  * @brief  Configure the boot address.
  *
  * @param  BootAddrConfig specifies the area to be configured.
  *          This parameter can be one of the following values:
  *            @arg OB_BOOTADDR_NS0: Non-secure boot address 0
  *            @arg OB_BOOTADDR_NS1: Non-secure boot address 1
  *            @arg OB_BOOTADDR_SEC0: Secure boot address 0
  *
  * @param  BootAddr: specifies the address used for the boot
  *          This parameter can be page number between 0 and 0xFFFFFF00
  *
  * @retval None
  */
static void FLASH_OB_BootAddrConfig(uint32_t BootAddrConfig, uint32_t BootAddr)
{
  /* Check the parameters */
  assert_param(IS_OB_BOOTADDR_CONFIG(BootAddrConfig));

  if (BootAddrConfig == OB_BOOTADDR_NS0)
  {
    MODIFY_REG(FLASH->NSBOOTADD0R, FLASH_NSBOOTADD0R_NSBOOTADD0, BootAddr);
  }
  else if (BootAddrConfig == OB_BOOTADDR_NS1)
  {
    MODIFY_REG(FLASH->NSBOOTADD1R, FLASH_NSBOOTADD1R_NSBOOTADD1, BootAddr);
  }
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  else if (BootAddrConfig == OB_BOOTADDR_SEC0)
  {
    MODIFY_REG(FLASH->SECBOOTADD0R, FLASH_SECBOOTADD0R_SECBOOTADD0, BootAddr);
  }
#endif
  else
  {
    /* Empty statement (to be compliant MISRA 15.7) */
  }
}

/**
  * @brief  Return the FLASH Write Protection Option Bytes value.
  *
  * @param[in]  WRPArea specifies the area to be returned.
  *          This parameter can be one of the following values:
  *            @arg OB_WRPAREA_BANK1_AREAA: Flash Bank 1 Area A
  *            @arg OB_WRPAREA_BANK1_AREAB: Flash Bank 1 Area B
  *            @arg OB_WRPAREA_BANK2_AREAA: Flash Bank 2 Area A
  *            @arg OB_WRPAREA_BANK2_AREAB: Flash Bank 2 Area B
  *
  * @param[out]  WRPStartOffset specifies the address where to copied the start page
  *                         of the write protected area
  *
  * @param[out]  WRPEndOffset specifies the address where to copied the end page of
  *                        the write protected area
  *
  * @retval None
  */
static void FLASH_OB_GetWRP(uint32_t WRPArea, uint32_t * WRPStartOffset, uint32_t * WRPEndOffset)
{
  /* Get the configuration of the write protected area */
  if(WRPArea == OB_WRPAREA_BANK1_AREAA)
  {
    *WRPStartOffset = READ_BIT(FLASH->WRP1AR, FLASH_WRP1AR_WRP1A_PSTRT);
    *WRPEndOffset = (READ_BIT(FLASH->WRP1AR, FLASH_WRP1AR_WRP1A_PEND) >> FLASH_WRP1AR_WRP1A_PEND_Pos);
  }
  else if(WRPArea == OB_WRPAREA_BANK1_AREAB)
  {
    *WRPStartOffset = READ_BIT(FLASH->WRP1BR, FLASH_WRP1BR_WRP1B_PSTRT);
    *WRPEndOffset = (READ_BIT(FLASH->WRP1BR, FLASH_WRP1BR_WRP1B_PEND) >> FLASH_WRP1BR_WRP1B_PEND_Pos);
  }
  else if(WRPArea == OB_WRPAREA_BANK2_AREAA)
  {
    *WRPStartOffset = READ_BIT(FLASH->WRP2AR, FLASH_WRP2AR_WRP2A_PSTRT);
    *WRPEndOffset = (READ_BIT(FLASH->WRP2AR, FLASH_WRP2AR_WRP2A_PEND) >> FLASH_WRP2AR_WRP2A_PEND_Pos);
  }
  else if(WRPArea == OB_WRPAREA_BANK2_AREAB)
  {
    *WRPStartOffset = READ_BIT(FLASH->WRP2BR, FLASH_WRP2BR_WRP2B_PSTRT);
    *WRPEndOffset = (READ_BIT(FLASH->WRP2BR, FLASH_WRP2BR_WRP2B_PEND) >> FLASH_WRP2BR_WRP2B_PEND_Pos);
  }
  else
  {
    /* Empty statement (to be compliant MISRA 15.7) */
  }
}

/**
  * @brief  Return the FLASH Read Protection level.
  * @retval FLASH ReadOut Protection Status:
  *         This return value can be one of the following values:
  *            @arg OB_RDP_LEVEL_0: No protection
  *            @arg OB_RDP_LEVEL_0_5: No debug access to secure area
  *            @arg OB_RDP_LEVEL_1: Read protection of the memory
  *            @arg OB_RDP_LEVEL_2: Full chip protection
  */
static uint32_t FLASH_OB_GetRDP(void)
{
  uint32_t rdp_level = READ_BIT(FLASH->OPTR, FLASH_OPTR_RDP);

  if ((rdp_level != OB_RDP_LEVEL_0) && (rdp_level != OB_RDP_LEVEL_0_5) && (rdp_level != OB_RDP_LEVEL_2))
  {
    return (OB_RDP_LEVEL_1);
  }
  else
  {
    return (rdp_level);
  }
}

/**
  * @brief  Return the FLASH User Option Byte value.
  * @retval The FLASH User Option Bytes values,
  *         it can be a combination of @ref FLASH_OB_USER_BOR_LEVEL,
  *         @ref FLASH_OB_USER_nRST_STOP, @ref FLASH_OB_USER_nRST_STANDBY,
  *         @ref FLASH_OB_USER_nRST_SHUTDOWN, @ref FLASH_OB_USER_IWDG_SW,
  *         @ref FLASH_OB_USER_IWDG_STOP, @ref FLASH_OB_USER_IWDG_STANDBY,
  *         @ref FLASH_OB_USER_WWDG_SW, @ref OB_USER_SWAP_BANK,
  *         @ref FLASH_OB_USER_DUALBANK, @ref FLASH_OB_USER_DBANK,
  *         @ref FLASH_OB_USER_SRAM2_PAR, @ref FLASH_OB_USER_SRAM2_RST,
  *         @ref OB_USER_nSWBOOT0, @ref OB_USER_nBOOT0, @ref FLASH_OB_USER_PA15_PUPEN
  *         and @ref OB_USER_TZEN
  */
static uint32_t FLASH_OB_GetUser(void)
{
  uint32_t user_config = READ_REG(FLASH->OPTR);
  CLEAR_BIT(user_config, FLASH_OPTR_RDP);

  return user_config;
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Return the watermarked-based secure area.
  *
  * @param  WMSecConfig [in/out] specifies the area to be returned.
  *                  This parameter can be one of the following values:
  *                   @arg OB_WMSEC_AREA1: Flash Secure Area 1
  *                   @arg OB_WMSEC_AREA2: Flash Secure Area 2
  *                  When return from the function, this parameter will have a combination of the following values:
  *                   @arg OB_WMSEC_AREA1 or @arg OB_WMSEC_AREA2: selected Flash Secure Area 1 or Area 2
  *                   @arg OB_WMSEC_HDP_AREA_ENABLE: Secure Hide Area in Secure Area enabled
  *                   @arg OB_WMSEC_HDP_AREA_DISABLE: Secure Hide Area in Secure Area disabled
  *
  * @param  WMSecStartPage [out] specifies the address where to copied the start page of the secure area
  *
  * @param  WMSecEndPage [out] specifies the address where to copied the end page of the secure area
  *
  * @param  WMHDPEndPage [out] specifies the address where to copied the end page of the secure hide area
  *
  * @retval None
  */
static void FLASH_OB_GetWMSEC(uint32_t * WMSecConfig, uint32_t * WMSecStartPage, uint32_t * WMSecEndPage, uint32_t * WMHDPEndPage)
{
  uint32_t tmp_secwm1 = 0U, tmp_secwm2 = 0U;

  /* Check the parameters */
  assert_param(IS_OB_WMSEC_CONFIG(*WMSecConfig));
  assert_param(IS_FLASH_BANK_EXCLUSIVE((*WMSecConfig) & 0x3U));

  /* Read SECWM registers */
  if (((*WMSecConfig) & OB_WMSEC_AREA1) != 0U)
  {
    tmp_secwm1 = FLASH->SECWM1R1;
    tmp_secwm2 = FLASH->SECWM1R2;
  }
  else if (((*WMSecConfig) & OB_WMSEC_AREA2) != 0U)
  {
    tmp_secwm1 = FLASH->SECWM2R1;
    tmp_secwm2 = FLASH->SECWM2R2;
  }
  else
  {
    /* Nothing to do */
  }

  /* Configuration of secure area */
  *WMSecStartPage = (tmp_secwm1 & FLASH_SECWM1R1_SECWM1_PSTRT);
  *WMSecEndPage = ((tmp_secwm1 & FLASH_SECWM1R1_SECWM1_PEND) >> FLASH_SECWM1R1_SECWM1_PEND_Pos);

  /* Configuration of secure hide area */
  *WMHDPEndPage = ((tmp_secwm2 & FLASH_SECWM1R2_HDP1_PEND) >> FLASH_SECWM1R2_HDP1_PEND_Pos);

  if ((tmp_secwm2 & FLASH_SECWM1R2_HDP1EN) == 0U)
  {
    *WMSecConfig = ((*WMSecConfig) | OB_WMSEC_HDP_AREA_DISABLE);
  }
  else
  {
    *WMSecConfig = ((*WMSecConfig) | OB_WMSEC_HDP_AREA_ENABLE);
  }
}

/**
  * @brief  Return the boot lock configuration.
  *
  * @retval  Value of Boot Lock configuration.
  *          It can be one of the following values:
  *            @arg OB_BOOT_LOCK_DISABLE: Boot Lock mode deactivated
  *            @arg OB_BOOT_LOCK_ENABLE: Boot Lock mode activated
  */
static uint32_t FLASH_OB_GetBootLock(void)
{
  return (FLASH->SECBOOTADD0R & FLASH_SECBOOTADD0R_BOOT_LOCK);
}
#endif

/**
  * @brief  Return the boot address.
  *
  * @param[in]  BootAddrConfig specifies the area to be returned.
  *              This parameter can be one of the following values:
  *                @arg OB_BOOTADDR_NS0: Non-secure boot address 0
  *                @arg OB_BOOTADDR_NS1: Non-secure boot address 1
  *                @arg OB_BOOTADDR_SEC0: Secure boot address 0
  *
  * @param[out]  BootAddr specifies the boot address value
  *
  * @retval None
  */
static void FLASH_OB_GetBootAddr(uint32_t BootAddrConfig, uint32_t * BootAddr)
{
  if (BootAddrConfig == OB_BOOTADDR_NS0)
  {
    *BootAddr = (FLASH->NSBOOTADD0R & FLASH_NSBOOTADD0R_NSBOOTADD0);
  }
  else if (BootAddrConfig == OB_BOOTADDR_NS1)
  {
    *BootAddr = (FLASH->NSBOOTADD1R & FLASH_NSBOOTADD1R_NSBOOTADD1);
  }
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  else if (BootAddrConfig == OB_BOOTADDR_SEC0)
  {
    *BootAddr = (FLASH->SECBOOTADD0R & FLASH_SECBOOTADD0R_SECBOOTADD0);
  }
#endif
  else
  {
    /* Empty statement (to be compliant MISRA 15.7) */
  }
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
