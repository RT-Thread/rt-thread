/**
  ******************************************************************************
  * @file    stm32h7xx_hal_flash_ex.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date   29-December-2017
  * @brief   Extended FLASH HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the FLASH extension peripheral:
  *           + Extended programming operations functions
  *  
 @verbatim    
 ==============================================================================
                   ##### Flash Extension features #####
  ==============================================================================
           
  [..] Comparing to other previous devices, the FLASH interface for STM32H7xx 
       devices contains the following additional features 
       
       (+) Capacity up to 2 Mbyte with dual bank architecture supporting read-while-write
           capability (RWW)
       (+) Dual bank memory organization       
       (+) PCROP protection for all banks
   
                        ##### How to use this driver #####
 ==============================================================================
  [..] This driver provides functions to configure and program the FLASH memory 
       of all STM32H7xx devices. It includes
      (#) FLASH Memory Erase functions: 
           (++) Lock and Unlock the FLASH interface using HAL_FLASH_Unlock() and 
                HAL_FLASH_Lock() functions
           (++) Erase function: Erase sector, erase all sectors
           (++) There are two modes of erase :
             (+++) Polling Mode using HAL_FLASHEx_Erase()
             (+++) Interrupt Mode using HAL_FLASHEx_Erase_IT()
                         
      (#) Option Bytes Programming functions: Use HAL_FLASHEx_OBProgram() to :
        (++) Set/Reset the write protection per bank
        (++) Set the Read protection Level
        (++) Set the BOR level
        (++) Program the user Option Bytes 
        (++) PCROP protection configuration and control per bank
    (++) Secure area configuration and control per bank
    (++) Core Boot address configuration 
    
   (#) FLASH Memory Lock and unlock per Bank: HAL_FLASHEx_Lock_Bank1 and HAL_FLASHEx_Unlock_Bank1 functions
    
    
 @endverbatim                      
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @defgroup FLASHEx  FLASHEx
  * @brief FLASH HAL Extension module driver
  * @{
  */

#ifdef HAL_FLASH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/ 
/** @addtogroup FLASHEx_Private_Constants
  * @{
  */    
#define FLASH_TIMEOUT_VALUE       50000U/* 50 s */
/**
  * @}
  */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern FLASH_ProcessTypeDef pFlash;

/* Private function prototypes -----------------------------------------------*/

static void FLASH_MassErase(uint32_t VoltageRange, uint32_t Banks);
void FLASH_Erase_Sector(uint32_t Sector, uint32_t Bank, uint32_t VoltageRange);
static HAL_StatusTypeDef FLASH_OB_EnableWRP(uint32_t WRPSector, uint32_t Banks);
static HAL_StatusTypeDef FLASH_OB_DisableWRP(uint32_t WRPSector, uint32_t Bank);
static void FLASH_OB_GetWRP(uint32_t *WRPState, uint32_t *WRPSector, uint32_t Bank);
static HAL_StatusTypeDef FLASH_OB_RDPConfig(uint32_t RDPLevel);
static uint32_t FLASH_OB_GetRDP(void);
static HAL_StatusTypeDef FLASH_OB_PCROPConfig(uint32_t PCROConfigRDP, uint32_t PCROPStartAddr, uint32_t PCROPEndAddr, uint32_t Banks);
static void FLASH_OB_GetPCROP(uint32_t *PCROPConfig, uint32_t *PCROPStartAddr,uint32_t *PCROPEndAddr, uint32_t Bank);
static HAL_StatusTypeDef FLASH_OB_BOR_LevelConfig(uint8_t Level);
static uint32_t FLASH_OB_GetBOR(void);
static HAL_StatusTypeDef FLASH_OB_UserConfig(uint32_t UserType, uint32_t UserConfig);
static uint32_t FLASH_OB_GetUser(void);
static HAL_StatusTypeDef FLASH_OB_BootAddConfig(uint32_t BootOption, uint32_t BootAddress0, uint32_t BootAddress1);
static void FLASH_OB_GetBootAdd(uint32_t *BootAddress0, uint32_t *BootAddress1);
static HAL_StatusTypeDef FLASH_OB_SecureAreaConfig(uint32_t SecureAreaConfig, uint32_t SecureAreaStartAddr, uint32_t SecureAreaEndAddr, uint32_t Banks);
static void FLASH_OB_GetSecureArea(uint32_t *SecureAreaConfig, uint32_t *SecureAreaStartAddr, uint32_t *SecureAreaEndAddr, uint32_t Bank);





/* Private functions ---------------------------------------------------------*/

/** @defgroup FLASHEx_Private_Functions Extended FLASH Private functions
  * @{
  */ 

/** @defgroup FLASHEx_Group1 Extended IO operation functions
 *  @brief   Extended IO operation functions 
 *
@verbatim   
 ===============================================================================
                ##### Extended programming operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the Extension FLASH 
    programming operations Operations.
 
@endverbatim
  * @{
  */
/**
  * @brief  Perform a mass erase or erase the specified FLASH memory sectors 
  * @param[in]  pEraseInit pointer to an FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  * 
  * @param[out]  SectorError pointer to variable  that
  *         contains the configuration information on faulty sector in case of error 
  *         (0xFFFFFFFF means that all the sectors have been correctly erased)
  * 
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *SectorError)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t index = 0;
  
  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));
  assert_param(IS_VOLTAGERANGE(pEraseInit->VoltageRange));
  assert_param(IS_FLASH_BANK(pEraseInit->Banks));
  
  
  /* Wait for last operation to be completed */
  if((pEraseInit->Banks & FLASH_BANK_1) == FLASH_BANK_1) 
  {
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);
  }

  if((pEraseInit->Banks & FLASH_BANK_2) == FLASH_BANK_2) 
  {
    status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);
  }
  
  if(status == HAL_OK)
  {
    /*Initialization of SectorError variable*/
    *SectorError = 0xFFFFFFFF;
    
    if(pEraseInit->TypeErase == FLASH_TYPEERASE_MASSERASE)
    {
      /*Mass erase to be done*/
      FLASH_MassErase(pEraseInit->VoltageRange, pEraseInit->Banks);

      /* Wait for last operation to be completed */
      if((pEraseInit->Banks & FLASH_BANK_1) == FLASH_BANK_1)
      {
        status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);
        /* if the erase operation is completed, disable the Bank1 BER Bit */
        FLASH->CR1 &= (~FLASH_CR_BER);
      }
      if((pEraseInit->Banks & FLASH_BANK_2) == FLASH_BANK_2)
      {
        status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);
        /* if the erase operation is completed, disable the Bank2 BER Bit */
        FLASH->CR2 &= (~FLASH_CR_BER);    
      }
    }
    else
    {
      /* Check the parameters */
      assert_param(IS_FLASH_BANK_EXCLUSIVE(pEraseInit->Banks));
      assert_param(IS_FLASH_NBSECTORS(pEraseInit->NbSectors + pEraseInit->Sector));

      /* Erase by sector by sector to be done*/
      for(index = pEraseInit->Sector; index < (pEraseInit->NbSectors + pEraseInit->Sector); index++)
      {
        FLASH_Erase_Sector(index, pEraseInit->Banks, pEraseInit->VoltageRange);

        if((pEraseInit->Banks & FLASH_BANK_1) == FLASH_BANK_1)
        {
          /* Wait for last operation to be completed */
          status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);
        
          /* If the erase operation is completed, disable the SER Bit */
          FLASH->CR1 &= (~(FLASH_CR_SER | FLASH_CR_SNB));
        }
        if((pEraseInit->Banks & FLASH_BANK_2) == FLASH_BANK_2)
        {
          /* Wait for last operation to be completed */
          status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);
        
          /* If the erase operation is completed, disable the SER Bit */
          FLASH->CR2 &= (~(FLASH_CR_SER | FLASH_CR_SNB));
        }

        if(status != HAL_OK)
        {
          /* In case of error, stop erase procedure and return the faulty sector*/
          *SectorError = index;
          break;
        }
      }
    }
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Perform a mass erase or erase the specified FLASH memory sectors with interrupt enabled
  * @param  pEraseInit pointer to an FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  * 
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));
  assert_param(IS_VOLTAGERANGE(pEraseInit->VoltageRange));
  assert_param(IS_FLASH_BANK(pEraseInit->Banks));

  if((pEraseInit->Banks & FLASH_BANK_1) == FLASH_BANK_1) 
  {  
    /* Clear bank 1 pending flags (if any) */ 
    __HAL_FLASH_CLEAR_FLAG_BANK1(FLASH_FLAG_EOP_BANK1 | FLASH_FLAG_ALL_ERRORS_BANK1); 
  
    /* Enable End of Operation and Error interrupts for Bank 1 */
    __HAL_FLASH_ENABLE_IT_BANK1(FLASH_IT_EOP_BANK1    | FLASH_IT_WRPERR_BANK1 | FLASH_IT_PGSERR_BANK1 | \
                                FLASH_IT_STRBERR_BANK1 | FLASH_IT_INCERR_BANK1 | FLASH_IT_OPERR_BANK1); 
  }
  if((pEraseInit->Banks & FLASH_BANK_2) == FLASH_BANK_2) 
  {  
    /* Clear bank 2 pending flags (if any) */ 
    __HAL_FLASH_CLEAR_FLAG_BANK2(FLASH_FLAG_EOP_BANK2 | FLASH_FLAG_ALL_ERRORS_BANK2); 
  
    /* Enable End of Operation and Error interrupts for Bank 2 */
    __HAL_FLASH_ENABLE_IT_BANK2(FLASH_IT_EOP_BANK2    | FLASH_IT_WRPERR_BANK2 | FLASH_IT_PGSERR_BANK2 | \
                                FLASH_IT_STRBERR_BANK2 | FLASH_IT_INCERR_BANK2 | FLASH_IT_OPERR_BANK2); 
  }
  
  if(pEraseInit->TypeErase == FLASH_TYPEERASE_MASSERASE)
  {
    /*Mass erase to be done*/
    if(pEraseInit->Banks == FLASH_BANK_1)
    {
      pFlash.ProcedureOnGoing = FLASH_PROC_MASSERASE_BANK1;
    }
    else if(pEraseInit->Banks == FLASH_BANK_2)
    {
      pFlash.ProcedureOnGoing = FLASH_PROC_MASSERASE_BANK2;
    }
    else
    {
      pFlash.ProcedureOnGoing = FLASH_PROC_ALLBANK_MASSERASE;  
    }

    FLASH_MassErase(pEraseInit->VoltageRange, pEraseInit->Banks);
  }
  else
  {
    /* Erase by sector to be done*/

    /* Check the parameters */
    assert_param(IS_FLASH_BANK_EXCLUSIVE(pEraseInit->Banks));
    assert_param(IS_FLASH_NBSECTORS(pEraseInit->NbSectors + pEraseInit->Sector));

    if(pEraseInit->Banks == FLASH_BANK_1)
    {
      pFlash.ProcedureOnGoing = FLASH_PROC_SECTERASE_BANK1;  
    }
    else
    {
      pFlash.ProcedureOnGoing = FLASH_PROC_SECTERASE_BANK2;    
    }

    pFlash.NbSectorsToErase = pEraseInit->NbSectors;
    pFlash.Sector = pEraseInit->Sector;
    pFlash.VoltageForErase = pEraseInit->VoltageRange;

    /*Erase 1st sector and wait for IT*/
    FLASH_Erase_Sector(pEraseInit->Sector, pEraseInit->Banks, pEraseInit->VoltageRange);
  }

  return status;
}

/**
  * @brief  Program option bytes
  * @param  pOBInit pointer to an FLASH_OBInitStruct structure that
  *         contains the configuration information for the programming.
  * 
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Check the parameters */
  assert_param(IS_OPTIONBYTE(pOBInit->OptionType));
  
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /*Write protection configuration*/
  if((pOBInit->OptionType & OPTIONBYTE_WRP) == OPTIONBYTE_WRP)
  {
    assert_param(IS_WRPSTATE(pOBInit->WRPState));
    assert_param(IS_FLASH_BANK(pOBInit->Banks));
  
    if(pOBInit->WRPState == OB_WRPSTATE_ENABLE)
    {
      /*Enable of Write protection on the selected Sector*/
      status = FLASH_OB_EnableWRP(pOBInit->WRPSector,pOBInit->Banks);
    }
    else
    {
      /*Disable of Write protection on the selected Sector*/
      status = FLASH_OB_DisableWRP(pOBInit->WRPSector, pOBInit->Banks);
    }
    if(status != HAL_OK)
    {
      /* Process Unlocked */
      __HAL_UNLOCK(&pFlash);
      return status;
    }
  }
  
  /* Read protection configuration */
  if((pOBInit->OptionType & OPTIONBYTE_RDP) != RESET)
  {
    /* Configure the Read protection level */
    status = FLASH_OB_RDPConfig(pOBInit->RDPLevel);
    if(status != HAL_OK)
    {
      /* Process Unlocked */
      __HAL_UNLOCK(&pFlash);
      return status;
    }
  }
  
  /* User Configuration */
  if((pOBInit->OptionType & OPTIONBYTE_USER) != RESET)
  {
    /* Configure the user option bytes */
    status = FLASH_OB_UserConfig(pOBInit->USERType, pOBInit->USERConfig);
    if(status != HAL_OK)
    {
      /* Process Unlocked */
      __HAL_UNLOCK(&pFlash);
      return status;
    }
  }
  
  /* PCROP Configuration */
  if((pOBInit->OptionType & OPTIONBYTE_PCROP) != RESET)
  {
    assert_param(IS_FLASH_BANK(pOBInit->Banks));
  
    /*Configure the Proprietary code readout protection */
    status = FLASH_OB_PCROPConfig(pOBInit->PCROPConfig, pOBInit->PCROPStartAddr, pOBInit->PCROPEndAddr, pOBInit->Banks);
    if(status != HAL_OK)
    {
      /* Process Unlocked */
      __HAL_UNLOCK(&pFlash);
      return status;
    }
    
  }
  
  /*BOR Level  configuration*/
  if((pOBInit->OptionType & OPTIONBYTE_BOR) == OPTIONBYTE_BOR)
  {
    status = FLASH_OB_BOR_LevelConfig(pOBInit->BORLevel);
    if(status != HAL_OK)
    {
      /* Process Unlocked */
      __HAL_UNLOCK(&pFlash);
      return status;
    }
  }
  
  /*Boot Address  configuration*/
  if((pOBInit->OptionType & OPTIONBYTE_BOOTADD) == OPTIONBYTE_BOOTADD)
  {
    status = FLASH_OB_BootAddConfig(pOBInit->BootConfig, pOBInit->BootAddr0, pOBInit->BootAddr1);
    if(status != HAL_OK)
    {
      /* Process Unlocked */
      __HAL_UNLOCK(&pFlash);
      return status;
    }
  }  
  /*Bank1 secure area  configuration*/
  if((pOBInit->OptionType & OPTIONBYTE_SECURE_AREA) == OPTIONBYTE_SECURE_AREA)
  {
    status = FLASH_OB_SecureAreaConfig(pOBInit->SecureAreaConfig, pOBInit->SecureAreaStartAddr, pOBInit->SecureAreaEndAddr,pOBInit->Banks);
    if(status != HAL_OK)
    {
      /* Process Unlocked */
      __HAL_UNLOCK(&pFlash);
      return status;
    }
  }  

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief Get the Option byte configuration
  * @note  The parameter Banks of the pOBInit structure must be exclusively FLASH_BANK_1 or FLASH_BANK_2
           as this parameter is use to get the given Bank WRP, PCROP and secured area.   
  * @param  pOBInit pointer to an FLASH_OBInitStruct structure that
  *         contains the configuration information for the programming.
  * 
  * @retval None
  */
void HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit)
{
  /* Check the parameters */
  assert_param(IS_FLASH_BANK_EXCLUSIVE(pOBInit->Banks));  
  pOBInit->OptionType = (OPTIONBYTE_WRP  | OPTIONBYTE_RDP         | \
                         OPTIONBYTE_USER | OPTIONBYTE_PCROP       | \
                         OPTIONBYTE_BOR  | OPTIONBYTE_BOOTADD | \
                         OPTIONBYTE_SECURE_AREA);

  /* Get write protection on the selected area */
  FLASH_OB_GetWRP(&(pOBInit->WRPState), &(pOBInit->WRPSector), pOBInit->Banks);
  
  /* Get Read protection level */
  pOBInit->RDPLevel = FLASH_OB_GetRDP();
  
  /* Get the user option bytes */
  pOBInit->USERConfig = FLASH_OB_GetUser();
  
  /* Get the Proprietary code readout protection */
  FLASH_OB_GetPCROP(&(pOBInit->PCROPConfig), &(pOBInit->PCROPStartAddr), &(pOBInit->PCROPEndAddr), pOBInit->Banks);
  
  /*Get BOR Level*/
  pOBInit->BORLevel = FLASH_OB_GetBOR();
  
  /*Get Boot Address*/
  FLASH_OB_GetBootAdd(&(pOBInit->BootAddr0), &(pOBInit->BootAddr1));
  /*Get Bank Secure area*/
  FLASH_OB_GetSecureArea(&(pOBInit->SecureAreaConfig), &(pOBInit->SecureAreaStartAddr), &(pOBInit->SecureAreaEndAddr), pOBInit->Banks);
}

/**
  * @brief  Unlock the FLASH Bank1 control registers access
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Unlock_Bank1(void)
{
  if(READ_BIT(FLASH->CR1, FLASH_CR_LOCK) != RESET)
  {
    /* Authorize the FLASH A Registers access */
    WRITE_REG(FLASH->KEYR1, FLASH_KEY1);
    WRITE_REG(FLASH->KEYR1, FLASH_KEY2);
  }
  else
  {
    return HAL_ERROR;
  }
  
  return HAL_OK;
}

/**
  * @brief  Locks the FLASH Bank1 control registers access
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Lock_Bank1(void)
{
  /* Set the LOCK Bit to lock the FLASH A Registers access */
  SET_BIT(FLASH->CR1, FLASH_CR_LOCK);
  return HAL_OK;  
}

/**
  * @brief  Unlock the FLASH Bank2 control registers access
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Unlock_Bank2(void)
{
  if(READ_BIT(FLASH->CR2, FLASH_CR_LOCK) != RESET)
  {
    /* Authorize the FLASH A Registers access */
    WRITE_REG(FLASH->KEYR2, FLASH_KEY1);
    WRITE_REG(FLASH->KEYR2, FLASH_KEY2);
  }
  else
  {
    return HAL_ERROR;
  }
  
  return HAL_OK;
}

/**
  * @brief  Locks the FLASH Bank2 control registers access
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Lock_Bank2(void)
{
  /* Set the LOCK Bit to lock the FLASH A Registers access */
  SET_BIT(FLASH->CR2, FLASH_CR_LOCK);
  return HAL_OK;  
}

/**
  * @brief  Full erase of FLASH memory sectors 
  * @param  VoltageRange The device program/erase parallelism.  
  *          This parameter can be one of the following values:
  *            @arg FLASH_VOLTAGE_RANGE_1 : Flash program/erase by 8 bits   
  *            @arg FLASH_VOLTAGE_RANGE_2 : Flash program/erase by 16 bits  
  *            @arg FLASH_VOLTAGE_RANGE_3 : Flash program/erase by 32 bits
  *            @arg FLASH_VOLTAGE_RANGE_4 : Flash program/erase by 64 bits   
  * 
  * @param  Banks Banks to be erased
  *          This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: Bank1 to be erased
  *            @arg FLASH_BANK_2: Bank2 to be erased
  *            @arg FLASH_BANK_BOTH: Bank1 and Bank2 to be erased
  *
  * @retval HAL Status
  */
static void FLASH_MassErase(uint32_t VoltageRange, uint32_t Banks)
{
  /* Check the parameters */
  assert_param(IS_FLASH_BANK(Banks));
  assert_param(IS_VOLTAGERANGE(VoltageRange));  
  
  /* Flash Mass Erase */
  if((Banks & FLASH_BANK_BOTH) == FLASH_BANK_BOTH)
  {
    /* reset Program/erase VoltageRange for Bank1 */
    FLASH->CR1 &= (~FLASH_CR_PSIZE);    
    /* Bank1 will be erased, and set voltage range*/
    FLASH->CR1 |= FLASH_CR_BER | VoltageRange;
    
    FLASH->OPTCR |= FLASH_OPTCR_MER;
    
  }
  else
  {
    /* Proceed to erase Flash Bank  */
    if((Banks & FLASH_BANK_1) == FLASH_BANK_1)
    {
      /* reset Program/erase VoltageRange for Bank1 */
      FLASH->CR1 &= (~FLASH_CR_PSIZE);
    
      /* Bank1 will be erased, and set voltage range*/
      FLASH->CR1 |= FLASH_CR_BER | VoltageRange;
      FLASH->CR1 |= FLASH_CR_START;
    }
    if((Banks & FLASH_BANK_2) == FLASH_BANK_2)
    {
      /* reset Program/erase VoltageRange for Bank2 */
      FLASH->CR2 &= (~FLASH_CR_PSIZE);
    
      /* Bank2 will be erased, and set voltage range*/
      FLASH->CR2 |= FLASH_CR_BER | VoltageRange;
      FLASH->CR2 |= FLASH_CR_START;
    }
  }
}

/**
  * @brief  Erase the specified FLASH memory sector
  * @param  Sector FLASH sector to erase
  * @param  Banks Banks to be erased
  *          This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: Bank1 to be erased
  *            @arg FLASH_BANK_2: Bank2 to be erased
  *            @arg FLASH_BANK_BOTH: Bank1 and Bank2 to be erased  
  * @param  VoltageRange The device program/erase parallelism.  
  *          This parameter can be one of the following values:
  *            @arg FLASH_VOLTAGE_RANGE_1 : Flash program/erase by 8 bits   
  *            @arg FLASH_VOLTAGE_RANGE_2 : Flash program/erase by 16 bits  
  *            @arg FLASH_VOLTAGE_RANGE_3 : Flash program/erase by 32 bits
  *            @arg FLASH_VOLTAGE_RANGE_4 : Flash program/erase by 62 bits 
  * 
  * @retval None
  */
void FLASH_Erase_Sector(uint32_t Sector, uint32_t Banks, uint32_t VoltageRange)
{
  assert_param(IS_FLASH_BANK_EXCLUSIVE(Banks));
  assert_param(IS_VOLTAGERANGE(VoltageRange));  
  assert_param(IS_FLASH_SECTOR(Sector));
  
  if((Banks & FLASH_BANK_1) == FLASH_BANK_1)
  {
    /* reset Program/erase VoltageRange for Bank1 */
    FLASH->CR1 &= ~(FLASH_CR_PSIZE | FLASH_CR_SNB);
  
    FLASH->CR1 |= (FLASH_CR_SER | VoltageRange | (Sector << POSITION_VAL(FLASH_CR_SNB)));
  
    FLASH->CR1 |= FLASH_CR_START;  
  }

  if((Banks & FLASH_BANK_2) == FLASH_BANK_2)
  {
    /* reset Program/erase VoltageRange for Bank2 */
    FLASH->CR2 &= ~(FLASH_CR_PSIZE | FLASH_CR_SNB);

    FLASH->CR2 |= (FLASH_CR_SER | VoltageRange  | (Sector << POSITION_VAL(FLASH_CR_SNB)));

    FLASH->CR2 |= FLASH_CR_START;  
  }
}

/**
  * @brief  Enable the write protection of the desired bank1 or bank 2 sectors
  * @param  WRPSector specifies the sector(s) to be write protected.
  *          This parameter can be one of the following values:
  *            @arg WRPSector:  A combination of OB_WRP_SECTOR_0 to OB_WRP_SECTOR_0 or OB_WRP_SECTOR_All
  *
  * @param  Banks the specific bank to apply WRP sectors 
  *          This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: WRP enable on specified bank1 sectors
  *            @arg FLASH_BANK_2: WRP enable on specified bank2 sectors
  *            @arg FLASH_BANK_BOTH: WRP enable bank1 and bank2 specified sectors
  *
  * @retval HAL FLASH State   
  */
static HAL_StatusTypeDef FLASH_OB_EnableWRP(uint32_t WRPSector, uint32_t Banks)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_FLASH_BANK(Banks));
  
  if((Banks & FLASH_BANK_1) == FLASH_BANK_1)
  {
    assert_param(IS_OB_WRP_SECTOR(WRPSector));
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);
  
    if(status == HAL_OK)
    {
      FLASH->WPSN_PRG1 &= (~(WRPSector & FLASH_WPSN_WRPSN));
    }
  }
  
  if((Banks & FLASH_BANK_2) == FLASH_BANK_2)
  {
    assert_param(IS_OB_WRP_SECTOR(WRPSector));

    /* Wait for last operation to be completed */
    status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);
  
    if(status == HAL_OK)
    {
      FLASH->WPSN_PRG2 &= (~(WRPSector & FLASH_WPSN_WRPSN));
    }
  }

  if((Banks & FLASH_BANK_1) == FLASH_BANK_1)
  { 
    /* Wait for last operation to be completed */
    status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);
  }
  
  if((Banks & FLASH_BANK_2) == FLASH_BANK_2)
  { 
    /* Wait for last operation to be completed */
    status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);
  }
  
  return status;
}

/**
  * @brief  Disable the write protection of the desired bank1 or bank 2 sectors
  * @param  WRPSector specifies the sector(s) to disable write protection.
  *          This parameter can be one of the following values:
  *            @arg WRPSector:  A combination of FLASH_OB_WRP_SECTOR_0 to FLASH_OB_WRP_SECTOR_7 or FLASH_OB_WRP_SECTOR_All
  *
  * @param  Banks the specific bank to apply WRP sectors 
  *          This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: WRP disable on specified bank1 sectors
  *            @arg FLASH_BANK_2: WRP disable on specified bank2 sectors
  *            @arg FLASH_BANK_BOTH: WRP disable bank1 and bank2 specified sectors
  *
  * @retval HAL FLASH State   
  */
static HAL_StatusTypeDef FLASH_OB_DisableWRP(uint32_t WRPSector, uint32_t Banks)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_FLASH_BANK(Banks));
  assert_param(IS_OB_WRP_SECTOR(WRPSector));
  
  if((Banks & FLASH_BANK_1) == FLASH_BANK_1)
  {    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);
  
    if(status == HAL_OK)
    {
      FLASH->WPSN_PRG1 |= (WRPSector & FLASH_WPSN_WRPSN);
    }  
  }
  
  if((Banks & FLASH_BANK_2) == FLASH_BANK_2)
  {    
    /* Wait for last operation to be completed */
    status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);
  
    if(status == HAL_OK)
    {
      FLASH->WPSN_PRG2 |= (WRPSector & FLASH_WPSN_WRPSN);
    }  
  }

  if((Banks & FLASH_BANK_1) == FLASH_BANK_1)
  { 
    /* Wait for last operation to be completed */
    status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);
  }
  
  if((Banks & FLASH_BANK_2) == FLASH_BANK_2)
  { 
    /* Wait for last operation to be completed */
    status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);
  }
  
  return status;
}

/**
  * @brief  Get the write protection of the given bank1 or bank 2 sectors
  * @param  WRPState gives the write protection state on the given bank .
  *          This parameter can be one of the following values:
  *          @arg WRPState: OB_WRPSTATE_DISABLE or OB_WRPSTATE_ENABLE 

  * @param  WRPSector gives the write protected sector(s) on the given bank .
  *          This parameter can be one of the following values:
  *          @arg WRPSector:  A combination of FLASH_OB_WRP_SECTOR_0 to FLASH_OB_WRP_SECTOR_7 or FLASH_OB_WRP_SECTOR_All
  *
  * @param  Bank the specific bank to apply WRP sectors 
  *          This parameter can be exclusively one of the following values:
  *            @arg FLASH_BANK_1: Get bank1 WRP sectors
  *            @arg FLASH_BANK_2: Get bank2 WRP sectors
  *            @arg FLASH_BANK_BOTH: note allowed in this functions
  *
  * @retval HAL FLASH State   
  */
static void FLASH_OB_GetWRP(uint32_t *WRPState, uint32_t *WRPSector, uint32_t Bank)
{
  uint32_t regvalue = 0;
  /* Check the parameters */
  assert_param(IS_FLASH_BANK_EXCLUSIVE(Bank));
  
  if((Bank & FLASH_BANK_BOTH) == FLASH_BANK_1)
  {
    regvalue = FLASH->WPSN_CUR1;
  }
  
  if((Bank & FLASH_BANK_BOTH) == FLASH_BANK_2)
  {
    regvalue = FLASH->WPSN_CUR2;
  }
  
  (*WRPSector) = (~(regvalue & FLASH_WPSN_WRPSN)) & FLASH_WPSN_WRPSN;
  if(*WRPSector == 0)
  {
    (*WRPState) = OB_WRPSTATE_DISABLE;
  }
  else
  {
    (*WRPState) = OB_WRPSTATE_ENABLE;
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
  *         to go back to level 1 or 0 !!!
  *    
  * @param  RDPLevel specifies the read protection level.
  *         This parameter can be one of the following values:
  *            @arg OB_RDP_LEVEL_0: No protection
  *            @arg OB_RDP_LEVEL_1: Read protection of the memory
  *            @arg OB_RDP_LEVEL_2: Full chip protection
  *   
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_OB_RDPConfig(uint32_t RDPLevel)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_OB_RDP_LEVEL(RDPLevel));
    
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);
  status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);
  
  if(status == HAL_OK)
  { 
    /* Configure the RDP level in the option bytes register */
    MODIFY_REG(FLASH->OPTSR_PRG, FLASH_OPTSR_RDP, RDPLevel);
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);
    status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);
  }

  return status;
}

/**
  * @brief  Get the read protection level. 
  * @retval RDPLevel specifies the read protection level.
  *         This parameter can be one of the following values:
  *            @arg OB_RDP_LEVEL_0: No protection
  *            @arg OB_RDP_LEVEL_1: Read protection of the memory
  *            @arg OB_RDP_LEVEL_2: Full chip protection
  */
static uint32_t FLASH_OB_GetRDP(void)
{
  return (FLASH->OPTSR_CUR & FLASH_OPTSR_RDP);
}

/**
  * @brief  Program the FLASH User Option Byte.
  * 
  * @note   To configure the user option bytes, the option lock bit OPTLOCK must
  *         be cleared with the call of the HAL_FLASH_OB_Unlock() function.
  *
  * @note   To validate the user option bytes, the option bytes must be reloaded 
  *         through the call of the HAL_FLASH_OB_Launch() function.
  *   
  * @param  UserType The FLASH User Option Bytes to be modified :
  *                   a combination of @arg FLASH_OB_USER_Type 
  *
  * @param  UserConfig The FLASH User Option Bytes values: 
  *         IWDG_SW(Bit4), WWDG_SW(Bit 5), nRST_STOP(Bit 6), nRST_STDY(Bit 7),
  *         FZ_IWDG_STOP(Bit 17), FZ_IWDG_SDBY(Bit 18), ST_RAM_SIZE(Bit[19:20]),
  *         ePcROP_EN(Bit 21), SWAP_BANK_OPT(Bit 31) . 
  *   
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_OB_UserConfig(uint32_t UserType, uint32_t UserConfig)
{
  uint32_t optr_reg_val = 0;
  uint32_t optr_reg_mask = 0;
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_OB_USER_TYPE(UserType));
  
  /* Wait for OB change operation to be completed */
  status = FLASH_OB_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  { 
    if((UserType & OB_USER_IWDG1_SW) != RESET)
    {
      /* IWDG_HW option byte should be modified */
      assert_param(IS_OB_IWDG1_SOURCE(UserConfig & FLASH_OPTSR_IWDG1_SW));
    
      /* Set value and mask for IWDG_HW option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTSR_IWDG1_SW);
      optr_reg_mask |= FLASH_OPTSR_IWDG1_SW;
    }
    if((UserType & OB_USER_NRST_STOP_D1) != RESET)
    {
      /* NRST_STOP option byte should be modified */
      assert_param(IS_OB_STOP_D1_RESET(UserConfig & FLASH_OPTSR_NRST_STOP_D1));
    
      /* Set value and mask for NRST_STOP option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTSR_NRST_STOP_D1);
      optr_reg_mask |= FLASH_OPTSR_NRST_STOP_D1;
    }

    if((UserType & OB_USER_NRST_STDBY_D1) != RESET)
    {
      /* NRST_STDBY option byte should be modified */
      assert_param(IS_OB_STDBY_D1_RESET(UserConfig & FLASH_OPTSR_NRST_STBY_D1));
    
      /* Set value and mask for NRST_STDBY option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTSR_NRST_STBY_D1);
      optr_reg_mask |= FLASH_OPTSR_NRST_STBY_D1;
    }

    if((UserType & OB_USER_IWDG_STOP) != RESET)
    {
      /* IWDG_STOP option byte should be modified */
      assert_param(IS_OB_USER_IWDG_STOP(UserConfig & FLASH_OPTSR_FZ_IWDG_STOP));
    
      /* Set value and mask for IWDG_STOP option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTSR_FZ_IWDG_STOP);
      optr_reg_mask |= FLASH_OPTSR_FZ_IWDG_STOP;
    }

    if((UserType & OB_USER_IWDG_STDBY) != RESET)
    {
      /* IWDG_STDBY option byte should be modified */
      assert_param(IS_OB_USER_IWDG_STDBY(UserConfig & FLASH_OPTSR_FZ_IWDG_SDBY));
    
      /* Set value and mask for IWDG_STDBY option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTSR_FZ_IWDG_SDBY);
      optr_reg_mask |= FLASH_OPTSR_FZ_IWDG_SDBY;
    }

    if((UserType & OB_USER_SECURITY) != RESET)
    {
      /* SECURITY option byte should be modified */
      assert_param(IS_OB_USER_SECURITY(UserConfig & FLASH_OPTSR_SECURITY));
    
      /* Set value and mask for ePcROP_EN option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTSR_SECURITY);
      optr_reg_mask |= FLASH_OPTSR_SECURITY;
    }
    if((UserType & OB_USER_SWAP_BANK) != RESET)
    {
      /* SWAP_BANK_OPT option byte should be modified */
      assert_param(IS_OB_USER_SWAP_BANK(UserConfig & FLASH_OPTSR_SWAP_BANK_OPT));
    
      /* Set value and mask for SWAP_BANK_OPT option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTSR_SWAP_BANK_OPT);
      optr_reg_mask |= FLASH_OPTSR_SWAP_BANK_OPT;
    }  
    
    if((UserType & OB_USER_IOHSLV) != RESET)
    {
      /* IOHSLV_OPT option byte should be modified */
      assert_param(IS_OB_USER_IOHSLV(UserConfig & FLASH_OPTSR_IO_HSLV));
    
      /* Set value and mask for IOHSLV_OPT option byte */
      optr_reg_val |= (UserConfig & FLASH_OPTSR_IO_HSLV);
      optr_reg_mask |= FLASH_OPTSR_IO_HSLV;
    }

    /* Configure the option bytes register */
    MODIFY_REG(FLASH->OPTSR_PRG, optr_reg_mask, optr_reg_val);
  }

  return status;            
}
/**
  * @brief  Return the FLASH User Option Byte value.
  * @retval The FLASH User Option Bytes values
  *         IWDG_SW(Bit4), WWDG_SW(Bit 5), nRST_STOP(Bit 6), nRST_STDY(Bit 7),
  *         FZ_IWDG_STOP(Bit 17), FZ_IWDG_SDBY(Bit 18), ST_RAM_SIZE(Bit[19:20]),
  *         ePcROP_EN(Bit 21), SWAP_BANK_OPT(Bit 31) .
  */
static uint32_t FLASH_OB_GetUser(void)
{
  uint32_t userConfig = READ_REG(FLASH->OPTSR_CUR);
  userConfig &= (~(FLASH_OPTSR_BOR_LEV | FLASH_OPTSR_RDP));
  
  return userConfig;
}

/**
  * @brief  Configure the Proprietary code readout protection of the desired addresses
  *
  * @note   To configure the PCROP options, the option lock bit OPTLOCK must be 
  *         cleared with the call of the HAL_FLASH_OB_Unlock() function.
  * @note   To validate the PCROP options, the option bytes must be reloaded 
  *         through the call of the HAL_FLASH_OB_Launch() function.
  *
  * @param  PCROPConfig specifies if the PCROP area for the given Bank shall be erased or not 
  *                        when RDP level  decreased from Level 1 to Level 0.
  *                        This parameter must be a value of @arg FLASH_OB_PCROP_RDP enumeration
  *
  * @param  PCROPStartAddr specifies the start address of the Proprietary code readout protection
  *          This parameter can be an address between begin and end of the bank 
  *
  * @param  PCROPEndAddr specifies the end address of the Proprietary code readout protection
  *          This parameter can be an address between PCROPStartAddr and end of the bank 
  *
  * @param  Banks the specific bank to apply PCROP sectors 
  *          This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: PCROP on specified bank1 area
  *            @arg FLASH_BANK_2: PCROP on specified bank2 area
  *            @arg FLASH_BANK_BOTH: PCROP on specified bank1 and bank2 area (same config will be applied on both banks)
  *              
  * @retval HAL Status
  */
static HAL_StatusTypeDef FLASH_OB_PCROPConfig(uint32_t PCROPConfig, uint32_t PCROPStartAddr, uint32_t PCROPEndAddr, uint32_t Banks)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_FLASH_BANK(Banks));
  assert_param(IS_OB_PCROP_RDP(PCROPConfig));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(PCROPStartAddr));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(PCROPEndAddr));
   
  if((Banks & FLASH_BANK_1) == FLASH_BANK_1)  
  {
    assert_param(IS_FLASH_PROGRAM_ADDRESS_BANK1(PCROPStartAddr));
    assert_param(IS_FLASH_PROGRAM_ADDRESS_BANK1(PCROPEndAddr));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE,FLASH_BANK_1);

    if(status == HAL_OK)
    {
      /* Configure the Proprietary code readout protection */
      FLASH->PRAR_PRG1 = ((PCROPStartAddr - FLASH_BANK1_BASE) >> 8);
    
      FLASH->PRAR_PRG1 |= (((PCROPEndAddr - FLASH_BANK1_BASE) >> 8) << POSITION_VAL(FLASH_PRAR_PROT_AREA_END)) ;
    
      FLASH->PRAR_PRG1 |= PCROPConfig;
    
      /* Wait for last operation to be completed */
      status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);
    }
  }  
  if((Banks & FLASH_BANK_2) == FLASH_BANK_2)  
  {
    assert_param(IS_FLASH_PROGRAM_ADDRESS_BANK2(PCROPStartAddr));
    assert_param(IS_FLASH_PROGRAM_ADDRESS_BANK2(PCROPEndAddr));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE,FLASH_BANK_2);

    if(status == HAL_OK)
    {
      FLASH->PRAR_PRG2 = ((PCROPStartAddr - FLASH_BANK2_BASE) >> 8);
    
      FLASH->PRAR_PRG2 |= (((PCROPEndAddr - FLASH_BANK2_BASE) >> 8) << POSITION_VAL(FLASH_PRAR_PROT_AREA_END)) ;
    
      FLASH->PRAR_PRG2 |= PCROPConfig;
    
      /* Wait for last operation to be completed */
      status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);
    }  
  }
  
  return status;
}

/**
  * @brief  Get the Proprietary code readout protection configuration on a given Bank
  *
  * @param  PCROPConfig gives if the PCROP area for the given Bank shall be erased or not 
  *                        when RDP level decreased from Level 1 to Level 0 or during a mass erase.
  *
  * @param  PCROPStartAddr gives the start address of the Proprietary code readout protection of the bank 
  *
  * @param  PCROPEndAddr gives the end address of the Proprietary code readout protection of the bank 
  *
  * @param  Bank the specific bank to apply PCROP sectors 
  *          This parameter can be exclusively one of the following values:
  *            @arg FLASH_BANK_1: PCROP on specified bank1 area
  *            @arg FLASH_BANK_2: PCROP on specified bank2 area
  *            @arg FLASH_BANK_BOTH: is  not allowed here
  *              
  * @retval HAL Status
  */
static void FLASH_OB_GetPCROP(uint32_t *PCROPConfig, uint32_t *PCROPStartAddr,uint32_t *PCROPEndAddr, uint32_t Bank)
{
  uint32_t regvalue = 0;
  uint32_t bankBase = 0;
  
  /* Check the parameters */
  assert_param(IS_FLASH_BANK_EXCLUSIVE(Bank));
  
  if((Bank & FLASH_BANK_BOTH) == FLASH_BANK_1)
  {
    regvalue = FLASH->PRAR_CUR1;
    bankBase = FLASH_BANK1_BASE;
  }
  
  if((Bank & FLASH_BANK_BOTH) == FLASH_BANK_2)
  {
    regvalue = FLASH->PRAR_CUR2;
    bankBase = FLASH_BANK2_BASE;    
  }

  
  (*PCROPConfig) =  (regvalue & FLASH_PRAR_DMEP);
  
  (*PCROPStartAddr) = ((regvalue & FLASH_PRAR_PROT_AREA_START) << 8) + bankBase;
  (*PCROPEndAddr) = (regvalue & FLASH_PRAR_PROT_AREA_END) >> POSITION_VAL(FLASH_PRAR_PROT_AREA_END) ;
  (*PCROPEndAddr) = ((*PCROPEndAddr) << 8) + bankBase;    
}

/**
  * @brief  Set the BOR Level. 
  * @param  Level specifies the Option Bytes BOR Reset Level.
  *          This parameter can be one of the following values:
  *            @arg OB_BOR_LEVEL1: Supply voltage ranges from 1.69V - 1.8V
  *            @arg OB_BOR_LEVEL2: Supply voltage ranges from 1.94V - 2.1V
  *            @arg OB_BOR_LEVEL3: Supply voltage ranges from 2.30V - 2.49V
  * @retval HAL Status
  */
static HAL_StatusTypeDef FLASH_OB_BOR_LevelConfig(uint8_t Level)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  assert_param(IS_OB_BOR_LEVEL(Level));
   
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);
  status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);

  if(status == HAL_OK)
  {
    /* Configure BOR_LEV option byte */
    MODIFY_REG(FLASH->OPTSR_PRG, FLASH_OPTSR_BOR_LEV, Level );
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);
    status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);
  }

  return status;
}

/**
  * @brief  Get the BOR Level. 
  * @retval The Option Bytes BOR Reset Level.
  *            This parameter can be one of the following values:
  *            @arg OB_BOR_LEVEL1: Supply voltage ranges from 1.69V - 1.8V
  *            @arg OB_BOR_LEVEL2: Supply voltage ranges from 1.94V - 2.1V
  *            @arg OB_BOR_LEVEL3: Supply voltage ranges from 2.30V - 2.49V
  */
static uint32_t FLASH_OB_GetBOR(void)
{
  return (FLASH->OPTSR_CUR & FLASH_OPTSR_BOR_LEV);
}

/**
  * @brief  Set Boot address
  * @param  BootOption Boot address option byte to be programmed,
  *                     This parameter must be a value of @ref FLASHEx_OB_BOOT_OPTION 
                        (OB_BOOT_ADD0, OB_BOOT_ADD1 or OB_BOOT_ADD_BOTH)
  *
  * @param  BootAddress0 Specifies the Boot Address 0
  * @param  BootAddress1 Specifies the Boot Address 1
  * @retval HAL Status
  */
static HAL_StatusTypeDef FLASH_OB_BootAddConfig(uint32_t BootOption, uint32_t BootAddress0, uint32_t BootAddress1)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_OB_BOOT_ADD_OPTION(BootOption));
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);
  status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);
  
  if(status == HAL_OK)
  {
    if((BootOption & OB_BOOT_ADD0) == OB_BOOT_ADD0)
    {
      /* Check the parameters */
      assert_param(IS_BOOT_ADDRESS(BootAddress0));
    
      /* Configure BOOT ADD0 */
      MODIFY_REG(FLASH->BOOT_PRG, FLASH_BOOT_ADD0, (BootAddress0 >> 16));
    }

    if((BootOption & OB_BOOT_ADD1) == OB_BOOT_ADD1)
    {
      /* Check the parameters */
      assert_param(IS_BOOT_ADDRESS(BootAddress1));
    
      /* Configure BOOT ADD1 */
      MODIFY_REG(FLASH->BOOT_PRG, FLASH_BOOT_ADD1, BootAddress1 );
    }

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);
    status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);
  }  
  
  return status;  
}

/**
  * @brief  Get Boot address
  * @param  BootAddress0 Specifies the Boot Address 0.
  * @param  BootAddress1 Specifies the Boot Address 1.
  * @retval HAL Status
  */
static void FLASH_OB_GetBootAdd(uint32_t *BootAddress0, uint32_t *BootAddress1)
{
  uint32_t regvalue = 0;

  regvalue = FLASH->BOOT_CUR;  

  (*BootAddress0) = (regvalue & FLASH_BOOT_ADD0) << 16;

  (*BootAddress1) = (regvalue & FLASH_BOOT_ADD1);

}

/**
  * @brief  Set secure area configuration
  * @param  SecureAreaConfig specify if the secure area will be deleted or not during next mass-erase,
  *
  * @param  SecureAreaStartAddr Specifies the secure area start address
  * @param  SecureAreaEndAddr Specifies the secure area end address
  * @param  Banks Specifies the Bank  
  * @retval HAL Status
  */
static HAL_StatusTypeDef FLASH_OB_SecureAreaConfig(uint32_t SecureAreaConfig, uint32_t SecureAreaStartAddr, uint32_t SecureAreaEndAddr, uint32_t Banks)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_FLASH_BANK_EXCLUSIVE(Banks));
  assert_param(IS_OB_SECURE_RDP(SecureAreaConfig));
  
  if((Banks & FLASH_BANK_1) == FLASH_BANK_1)
  {
    /* Check the parameters */
    assert_param(IS_FLASH_PROGRAM_ADDRESS_BANK1(SecureAreaStartAddr));
    assert_param(IS_FLASH_PROGRAM_ADDRESS_BANK1(SecureAreaEndAddr));
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);
  
    if(status == HAL_OK)
    {
      /* Configure the secure area */
      FLASH->SCAR_PRG1 = ((SecureAreaStartAddr - FLASH_BANK1_BASE) >> 8);
    
      FLASH->SCAR_PRG1 |= (((SecureAreaEndAddr - FLASH_BANK1_BASE) >> 8) << POSITION_VAL(FLASH_SCAR_SEC_AREA_END)) ;
    
      FLASH->SCAR_PRG1 |= (SecureAreaConfig & FLASH_SCAR_DMES);

      status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_1);    
    
    }  
  }
  if((Banks & FLASH_BANK_2) == FLASH_BANK_2)
  {
    /* Check the parameters */
    assert_param(IS_FLASH_PROGRAM_ADDRESS_BANK2(SecureAreaStartAddr));
    assert_param(IS_FLASH_PROGRAM_ADDRESS_BANK2(SecureAreaEndAddr));
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);

    if(status == HAL_OK)
    {
      /* Configure the secure area */
      FLASH->SCAR_PRG2 = ((SecureAreaStartAddr - FLASH_BANK2_BASE) >> 8);
    
      FLASH->SCAR_PRG2 |= (((SecureAreaEndAddr - FLASH_BANK2_BASE) >> 8) << POSITION_VAL(FLASH_SCAR_SEC_AREA_END)) ;
    
      FLASH->SCAR_PRG2 |= (SecureAreaConfig & FLASH_SCAR_DMES);

      status |= FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE, FLASH_BANK_2);    
    }   
  }
    
  return status; 
}

/**
  * @brief  Set secure area configuration
  * @param  SecureAreaConfig specify if the secure area will be deleted or not during next mass-erase,
  *
  * @param  SecureAreaStartAddr Specifies the secure area start address
  * @param  SecureAreaEndAddr Specifies the secure area end address
  * @param  Bank Specifies the Bank  
  * @retval HAL Status
  */
static void FLASH_OB_GetSecureArea(uint32_t *SecureAreaConfig, uint32_t *SecureAreaStartAddr, uint32_t *SecureAreaEndAddr, uint32_t Bank)
{
  uint32_t regvalue = 0;
  uint32_t bankBase = 0;  
  
  /* Check the parameters */
  assert_param(IS_FLASH_BANK_EXCLUSIVE(Bank));
  
  if((Bank & FLASH_BANK_BOTH) == FLASH_BANK_1)
  {
    regvalue = FLASH->SCAR_CUR1;
    bankBase = FLASH_BANK1_BASE;    
  }
  
  if((Bank & FLASH_BANK_BOTH) == FLASH_BANK_2)
  {
    regvalue = FLASH->SCAR_CUR2;
    bankBase = FLASH_BANK2_BASE;    
  }
  
  (*SecureAreaConfig) = (regvalue & FLASH_SCAR_DMES);
  (*SecureAreaStartAddr) = ((regvalue & FLASH_SCAR_SEC_AREA_START) << 8) + bankBase;
  (*SecureAreaEndAddr) = (regvalue & FLASH_SCAR_SEC_AREA_END) >> POSITION_VAL(FLASH_SCAR_SEC_AREA_END) ;
  (*SecureAreaEndAddr) = ((*SecureAreaEndAddr) << 8) + bankBase;
  
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
