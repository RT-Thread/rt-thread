/**
  ******************************************************************************
  * @file               ft32f0xx_flash.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the FLASH peripheral:
  *                 - FLASH Interface configuration
  *                 - FLASH Memory Programming
  *                 - Option Bytes Programming
  *                 - Interrupts and flags management
  * @version            V1.0.0
  * @data                   2021-07-01
    ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx_flash.h"

/**
  * @brief  Sets the code latency value.
  * @param  FLASH_Latency: specifies the FLASH Latency value.
  *          This parameter can be one of the following values:
  *             @arg FLASH_Latency_0: FLASH Zero Latency cycle
  *             @arg FLASH_Latency_1: FLASH One Latency cycle
  * @retval None
  */
void FLASH_SetLatency(uint32_t FLASH_Latency)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_FLASH_LATENCY(FLASH_Latency));

    /* Read the ACR register */
    tmpreg = FLASH->ACR;

    /* Sets the Latency value */
    tmpreg &= (uint32_t) (~((uint32_t)FLASH_ACR_LATENCY));
    tmpreg |= FLASH_Latency;

    /* Write the ACR register */
    FLASH->ACR = tmpreg;
}

/**
  * @brief  Enables or disables the Prefetch Buffer.
  * @param  NewState: new state of the FLASH prefetch buffer.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FLASH_PrefetchBufferCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(NewState != DISABLE)
    {
        FLASH->ACR |= FLASH_ACR_PRFTBE;
    }
    else
    {
        FLASH->ACR &= (uint32_t)(~((uint32_t)FLASH_ACR_PRFTBE));
    }
}

/**
  * @brief  Checks whether the FLASH Prefetch Buffer status is set or not.
  * @param  None
  * @retval FLASH Prefetch Buffer Status (SET or RESET).
  */
FlagStatus FLASH_GetPrefetchBufferStatus(void)
{
    FlagStatus bitstatus = RESET;

    if ((FLASH->ACR & FLASH_ACR_PRFTBS) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the new state of FLASH Prefetch Buffer Status (SET or RESET) */
    return bitstatus;
}


/**
  * @brief  Unlocks the FLASH control register and program memory access.
  * @param  None
  * @retval None
  */
void FLASH_Unlock(void)
{
    if((FLASH->CR & FLASH_CR_LOCK) != RESET)
    {
        /* Unlocking the program memory access */
        FLASH->KEYR = FLASH_FKEY1;
        FLASH->KEYR = FLASH_FKEY2;
    }
}

/**
  * @brief  Locks the Program memory access.
  * @param  None
  * @retval None
  */
void FLASH_Lock(void)
{
    /* Set the LOCK Bit to lock the FLASH control register and program memory access */
    FLASH->CR |= FLASH_CR_LOCK;
}

/**
  * @brief  Erases a specified page in program memory.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  Page_Address: The page address in program memory to be erased.
  * @note   A Page is erased in the Program memory only if the address to load
  *         is the start address of a page (multiple of 512 bytes,in FT32F072XB is 1024 bytes).
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ErasePage(uint32_t Page_Address)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Page_Address));

    FLASH_PrefetchBufferCmd(DISABLE);
  __ASM("ISB");

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if(status == FLASH_COMPLETE)
  {
    /* If the previous operation is completed, proceed to erase the page */
    FLASH->CR |= FLASH_CR_PER;
    FLASH->AR  = Page_Address;
    FLASH->CR |= FLASH_CR_STRT;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    /* Disable the PER Bit */
    FLASH->CR &= ~FLASH_CR_PER;
  }

  FLASH_PrefetchBufferCmd(ENABLE);

  /* Return the Erase Status */
  return status;
}

/**
  * @brief  Erases all FLASH pages.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseAllPages(void)
{
    FLASH_Status status = FLASH_COMPLETE;

    FLASH_PrefetchBufferCmd(DISABLE);
    __ASM("ISB");

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
        /* if the previous operation is completed, proceed to erase all pages */
         FLASH->CR |= FLASH_CR_MER;
         FLASH->CR |= FLASH_CR_STRT;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        /* Disable the MER Bit */
        FLASH->CR &= ~FLASH_CR_MER;
    }

    FLASH_PrefetchBufferCmd(ENABLE);

    /* Return the Erase Status */
    return status;
}

#if defined(FT32F072xB)
/**
  * @brief  Programs a word at a specified address.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  FLASH_PrefetchBufferCmd(DISABLE);
  __ASM("ISB");

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if(status == FLASH_COMPLETE)
  {
    /* If the previous operation is completed, proceed to program the new first
    half word */
    FLASH->CR |= FLASH_CR_PG;

    *(__IO uint16_t*)Address = (uint16_t)Data;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
      /* If the previous operation is completed, proceed to program the new second
      half word */
      tmp = Address + 2;

      *(__IO uint16_t*) tmp = Data >> 16;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

      /* Disable the PG Bit */
      FLASH->CR &= ~FLASH_CR_PG;
    }
    else
    {
      /* Disable the PG Bit */
      FLASH->CR &= ~FLASH_CR_PG;
    }
  }

  FLASH_PrefetchBufferCmd(ENABLE);
  /* Return the Program Status */
  return status;
}

/**
  * @brief  Programs a half word at a specified address.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  FLASH_PrefetchBufferCmd(DISABLE);
  __ASM("ISB");

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if(status == FLASH_COMPLETE)
  {
    /* If the previous operation is completed, proceed to program the new data */
    FLASH->CR |= FLASH_CR_PG;

    *(__IO uint16_t*)Address = Data;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    /* Disable the PG Bit */
    FLASH->CR &= ~FLASH_CR_PG;
  }

  FLASH_PrefetchBufferCmd(ENABLE);

  /* Return the Program Status */
  return status;
}
#else
/**
  * @brief  Programs a word at a specified address.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  FLASH_PrefetchBufferCmd(DISABLE);
  __ASM("ISB");

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if(status == FLASH_COMPLETE)
  {
    /* If the previous operation is completed, proceed to program the new first word */
    FLASH->CR |= FLASH_CR_PG;

    *(__IO uint32_t*)Address = Data;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    /* Disable the PG Bit */
    FLASH->CR &= ~FLASH_CR_PG;
  }

  FLASH_PrefetchBufferCmd(ENABLE);

  /* Return the Program Status */
  return status;
}
#endif

/**
  * @}
  */

/**
  * @brief  Unlocks the option bytes block access.
  * @param  None
  * @retval None
  */
void FLASH_OB_Unlock(void)
{
  if((FLASH->CR & FLASH_CR_OPTWRE) == RESET)
  {
    /* Unlocking the option bytes block access */
    FLASH->OPTKEYR = FLASH_OPTKEY1;
    FLASH->OPTKEYR = FLASH_OPTKEY2;
  }
}

/**
  * @brief  Locks the option bytes block access.
  * @param  None
  * @retval None
  */
void FLASH_OB_Lock(void)
{
    /* Set the OPTWREN Bit to lock the option bytes block access */
    FLASH->CR &= ~FLASH_CR_OPTWRE;
}

/**
  * @brief  Launch the option byte loading.
  * @param  None
  * @retval None
  */
void FLASH_OB_Launch(void)
{
    /* Set the OBL_Launch bit to launch the option byte loading */
    FLASH->CR |= FLASH_CR_OBL_LAUNCH;
}

#if defined(FT32F072xB)
/**
  * @brief  Erases the FLASH option bytes.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @note   This functions erases all option bytes except the Read protection (RDP).
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_Erase(void)
{
    uint16_t rdptmp = OB_RDP_Level_0;

    FLASH_Status status = FLASH_COMPLETE;

    /* Get the actual read protection Option Byte value */
    if(FLASH_OB_GetRDP() != RESET)
    {
        rdptmp = 0x0;
    }

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
        /* If the previous operation is completed, proceed to erase the option bytes */
        FLASH->CR |= FLASH_CR_OPTER;
        FLASH->CR |= FLASH_CR_STRT;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        if(status == FLASH_COMPLETE)
        {
            /* If the erase operation is completed, disable the OPTER Bit */
            FLASH->CR &= ~FLASH_CR_OPTER;

            /* Enable the Option Bytes Programming operation */
            FLASH->CR |= FLASH_CR_OPTPG;

            /* Restore the last read protection Option Byte value */
            OB->RDP = (uint16_t)rdptmp;

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

            if(status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CR &= ~FLASH_CR_OPTPG;
            }

        }
        else
        {
            if (status != FLASH_TIMEOUT)
            {
                FLASH->CR &= ~FLASH_CR_OPTER;
            }
        }
    }
    /* Return the erase status */
    return status;
}

/**
  * @brief  Write protects the desired pages
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  OB_WRP: specifies the address of the pages to be write protected.
  *          This parameter can be:
  *             @arg OB_WRP_Pages0to7..OB_WRP_Pages120to127
  *             @arg OB_WRP_AllPages
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_EnableWRP(uint32_t OB_WRP)
{
 uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;

  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_OB_WRP(OB_WRP));

  OB_WRP = (uint32_t)(~OB_WRP);
  WRP0_Data = (uint16_t)(OB_WRP & OB_WRP0_WRP0);
  WRP1_Data = (uint16_t)((OB_WRP >> 8) & OB_WRP0_WRP0);
  WRP2_Data = (uint16_t)((OB_WRP >> 16) & OB_WRP0_WRP0) ;
  WRP3_Data = (uint16_t)((OB_WRP >> 24) & OB_WRP0_WRP0) ;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if(status == FLASH_COMPLETE)
  {
    FLASH->CR |= FLASH_CR_OPTPG;

    if(WRP0_Data != 0xFF)
    {
      OB->WRP0 = WRP0_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }
    if((status == FLASH_COMPLETE) && (WRP1_Data != 0xFF))
    {
      OB->WRP1 = WRP1_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }
    if((status == FLASH_COMPLETE) && (WRP2_Data != 0xFF))
    {
      OB->WRP2 = WRP2_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }
    if((status == FLASH_COMPLETE) && (WRP3_Data != 0xFF))
    {
      OB->WRP3 = WRP3_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }
    if(status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }
  /* Return the write protection operation Status */
  return status;
}
/**
  * @brief  Enables or disables the read out protection.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  FLASH_ReadProtection_Level: specifies the read protection level.
  *          This parameter can be:
  *             @arg OB_RDP_Level_0: No protection
  *             @arg OB_RDP_Level_1: Read protection of the memory
  *             @arg
  * @note   When enabling OB_RDP level 2 it's no more possible to go back to level 1 or 0
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_RDPConfig(uint8_t OB_RDP)
{
    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_OB_RDP(OB_RDP));
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
        FLASH->CR |= FLASH_CR_OPTER;
        FLASH->CR |= FLASH_CR_STRT;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        if(status == FLASH_COMPLETE)
        {
            /* If the erase operation is completed, disable the OPTER Bit */
            FLASH->CR &= ~FLASH_CR_OPTER;

            /* Enable the Option Bytes Programming operation */
            FLASH->CR |= FLASH_CR_OPTPG;

            OB->RDP = OB_RDP;

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

            if(status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CR &= ~FLASH_CR_OPTPG;
            }
        }
        else
        {
            if(status != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CR &= ~FLASH_CR_OPTER;
            }
        }
    }
    /* Return the protection operation Status */
    return status;
}

/**
  * @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  OB_IWDG: Selects the WDG mode
  *          This parameter can be one of the following values:
  *             @arg OB_IWDG_SW: Software WDG selected
  *             @arg OB_IWDG_HW: Hardware WDG selected
  * @param  OB_STOP: Reset event when entering STOP mode.
  *          This parameter can be one of the following values:
  *             @arg OB_STOP_NoRST: No reset generated when entering in STOP
  *             @arg OB_STOP_RST: Reset generated when entering in STOP
  * @param  OB_STDBY: Reset event when entering Standby mode.
  *          This parameter can be one of the following values:
  *             @arg OB_STDBY_NoRST: No reset generated when entering in STANDBY
  *             @arg OB_STDBY_RST: Reset generated when entering in STANDBY
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY)
{
    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
    assert_param(IS_OB_STOP_SOURCE(OB_STOP));
    assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CR |= FLASH_CR_OPTPG;

        OB->USER = (uint16_t)((uint16_t)(OB_IWDG | OB_STOP) | (uint16_t)(OB_STDBY | 0xF8));

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        if(status != FLASH_TIMEOUT)
        {
            /* If the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= ~FLASH_CR_OPTPG;
        }
    }
    /* Return the Option Byte program Status */
    return status;
}

/**
  * @brief  Sets or resets the BOOT1 option bit.
  * @param  OB_BOOT1: Set or Reset the BOOT1 option bit.
  *          This parameter can be one of the following values:
  *             @arg OB_BOOT1_RESET: BOOT1 option bit reset
  *             @arg OB_BOOT1_SET: BOOT1 option bit set
  * @retval None
  */
FLASH_Status FLASH_OB_BOOTConfig(uint8_t OB_BOOT1)
{
    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_OB_BOOT1(OB_BOOT1));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CR |= FLASH_CR_OPTPG;

        OB->USER = OB_BOOT1 | 0xEF;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        if(status != FLASH_TIMEOUT)
        {
            /* If the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= ~FLASH_CR_OPTPG;
        }
    }
    /* Return the Option Byte program Status */
    return status;
}

/**
  * @brief  Sets or resets the analogue monitoring on VDDA Power source.
  * @param  OB_VDDA_ANALOG: Selects the analog monitoring on VDDA Power source.
  *          This parameter can be one of the following values:
  *             @arg OB_VDDA_ANALOG_ON: Analog monitoring on VDDA Power source ON
  *             @arg OB_VDDA_ANALOG_OFF: Analog monitoring on VDDA Power source OFF
  * @retval None
  */
FLASH_Status FLASH_OB_VDDAConfig(uint8_t OB_VDDA_ANALOG)
{
    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_OB_VDDA_ANALOG(OB_VDDA_ANALOG));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CR |= FLASH_CR_OPTPG;

        OB->USER =  OB_VDDA_ANALOG | 0xDF;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        if(status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= ~FLASH_CR_OPTPG;
        }
    }
    /* Return the Option Byte program Status */
    return status;
}

/**
  * @brief  Sets or resets the SRAM parity.
  * @param  OB_SRAM_Parity: Set or Reset the SRAM parity enable bit.
  *          This parameter can be one of the following values:
  *             @arg OB_SRAM_PARITY_SET: Set SRAM parity.
  *             @arg OB_SRAM_PARITY_RESET: Reset SRAM parity.
  * @retval None
  */
FLASH_Status FLASH_OB_SRAMParityConfig(uint8_t OB_SRAM_Parity)
{
    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_OB_SRAM_PARITY(OB_SRAM_Parity));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {

        /* Enable the Option Bytes Programming operation */
        FLASH->CR |= FLASH_CR_OPTPG;

        OB->USER =  OB_SRAM_Parity | 0xBF;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        if(status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= ~FLASH_CR_OPTPG;
        }
    }
    /* Return the Option Byte program Status */
    return status;
}

/**
  * @brief  Programs the FLASH User Option Byte: IWDG_SW, RST_STOP, RST_STDBY,
  *         BOOT1 and VDDA ANALOG monitoring.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  OB_USER: Selects all user option bytes
  *          This parameter is a combination of the following values:
  *             @arg OB_IWDG_SW / OB_IWDG_HW: Software / Hardware WDG selected
  *             @arg OB_STOP_NoRST / OB_STOP_RST: No reset / Reset generated when entering in STOP
  *             @arg OB_STDBY_NoRST / OB_STDBY_RST: No reset / Reset generated when entering in STANDBY
  *             @arg OB_BOOT1_RESET / OB_BOOT1_SET: BOOT1 Reset / Set
  *             @arg OB_VDDA_ANALOG_ON / OB_VDDA_ANALOG_OFF: Analog monitoring on VDDA Power source ON / OFF
  *             @arg OB_SRAM_PARITY_SET / OB_SRAM_PARITY_RESET: SRAM Parity SET / RESET
  *             @arg OB_BOOT0_RESET / OB_BOOT0_SET: BOOT0 Reset / Set
  *             @arg OB_BOOT0_SW / OB_BOOT0_SW: BOOT0 pin disabled / BOOT0 pin bonded with GPIO
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_WriteUser(uint8_t OB_USER)
{
    FLASH_Status status = FLASH_COMPLETE;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
        /* If the erase operation is completed, disable the OPTER Bit */
        FLASH->CR &= ~FLASH_CR_OPTER;
        /* Enable the Option Bytes Programming operation */
        FLASH->CR |= FLASH_CR_OPTPG;

        OB->USER = OB_USER;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        if(status != FLASH_TIMEOUT)
        {
            /* If the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= ~FLASH_CR_OPTPG;
        }
    }
    /* Return the Option Byte program Status */
    return status;

}

/**
  * @brief  Programs a half word at a specified Option Byte Data address.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  Address: specifies the address to be programmed.
  *          This parameter can be 0x1FFFF804.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_ProgramData(uint32_t Address, uint8_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* Check the parameters */
  assert_param(IS_OB_DATA_ADDRESS(Address));
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if(status == FLASH_COMPLETE)
  {
    /* Enables the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG;
    *(__IO uint16_t*)Address = Data;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* If the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }
  /* Return the Option Byte Data Program Status */
  return status;
}
#else
/**
  * @brief  Erases the FLASH option bytes.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @note   This functions erases all option bytes except the Read protection (RDP).
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_Erase(void)
{
  uint32_t rdptmp = 0;

  FLASH_Status status = FLASH_COMPLETE;

  /* Get the actual read protection Option Byte value */
  if(FLASH_OB_GetRDP() != RESET)
  {
    rdptmp = 0x0000 | 0xff00;               //读保护级别1
  }
    else
    {
        rdptmp = OB_RDP_Level_0 | 0x5500;   //读保护级别0
    }

    /*Get iwdg value */
//  if ((uint8_t)(FLASH->OBR & (FLASH_OBR_IWDG_SW)) != RESET)
//  {
//      rdptmp |= 0x0f0000 | 0xf0000000;//HW iwdg
//  }
//  else
    {
        rdptmp |= 0x0e0000 | 0xf1000000;//sw iwdg
    }

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if(status == FLASH_COMPLETE)
  {
    /* If the previous operation is completed, proceed to erase the option bytes */
    FLASH->CR |= FLASH_CR_OPTER;
    FLASH->CR |= FLASH_CR_STRT;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
      /* If the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= ~FLASH_CR_OPTER;

      /* Enable the Option Bytes Programming operation */
      FLASH->CR |= FLASH_CR_OPTPG;

      /* Restore the last read protection Option Byte value */
      OB->USER_RDP = rdptmp;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

      if(status != FLASH_TIMEOUT)
      {
        /* if the program operation is completed, disable the OPTPG Bit */
        FLASH->CR &= ~FLASH_CR_OPTPG;
      }
    }
    else
    {
      if (status != FLASH_TIMEOUT)
      {
        /* Disable the OPTPG Bit */
        FLASH->CR &= ~FLASH_CR_OPTPG;
      }
    }
  }
  /* Return the erase status */
  return status;
}

/**
  * @brief  Write protects the desired pages
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  OB_WRP: specifies the address of the pages to be write protected.
  *          This parameter can be:
  *             @arg OB_WRP_Pages0to3..OB_WRP_Pages60to63
  *             @arg OB_WRP_AllPages
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_EnableWRP(uint32_t OB_WRP)
{
    uint8_t WRP0_Data = 0xFF,WRP1_Data = 0xFF,WRP2_Data = 0xFF,WRP3_Data = 0xFF;
    uint8_t nWRP0_Data = 0,nWRP1_Data = 0,nWRP2_Data = 0,nWRP3_Data = 0;
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_OB_WRP(OB_WRP));

  OB_WRP = (uint32_t)(~OB_WRP);
  WRP0_Data = (uint8_t)(OB_WRP & OB_WRP0_WRP0);
    nWRP0_Data = ~WRP0_Data;

  WRP1_Data = (uint8_t)((OB_WRP >> 8) & OB_WRP0_WRP0);
    nWRP1_Data = ~WRP1_Data;

  WRP2_Data = (uint8_t)((OB_WRP >> 16) & OB_WRP0_WRP0);
    nWRP2_Data = ~WRP2_Data;

  WRP3_Data = (uint8_t)((OB_WRP >> 24) & OB_WRP0_WRP0);
  nWRP3_Data = ~WRP3_Data;
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if(status == FLASH_COMPLETE)
  {
    FLASH->CR |= FLASH_CR_OPTPG;

   if((WRP0_Data != 0xFF) ||(WRP1_Data != 0xFF))
    {
      OB->WRP1_WRP0 = (WRP0_Data) | (nWRP0_Data<<8) | (WRP1_Data<<16) | (nWRP1_Data<<24);

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }
   if((status == FLASH_COMPLETE) && (WRP2_Data != 0xFF))
    {
      OB->WRP3_WRP2  = (WRP2_Data) | (nWRP2_Data<<8) | (WRP3_Data<<16) | (nWRP3_Data<<24);

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }
    if(status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }
  /* Return the write protection operation Status */
  return status;
}

/**
  * @brief  Enables or disables the read out protection.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  FLASH_ReadProtection_Level: specifies the read protection level.
  *          This parameter can be:
  *             @arg OB_RDP_Level_0: No protection
  *             @arg OB_RDP_Level_1: Read protection of the memory
  *             @arg
  * @note   When enabling OB_RDP level 2 it's no more possible to go back to level 1 or 0
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_RDPConfig(uint8_t OB_RDP)
{
  FLASH_Status status = FLASH_COMPLETE;
  uint32_t ob_user_rdp = 0;
    uint16_t ob_rdp_nrdp = 0;

  /* Check the parameters */
  assert_param(IS_OB_RDP(OB_RDP));
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    ob_user_rdp = OB->USER_RDP & 0xffff0000;
    ob_rdp_nrdp = OB_RDP;
    OB_RDP = ~OB_RDP;
    ob_rdp_nrdp |= OB_RDP<<8;
  ob_user_rdp |= ob_rdp_nrdp;

  if(status == FLASH_COMPLETE)
  {
    FLASH->CR |= FLASH_CR_OPTER;
    FLASH->CR |= FLASH_CR_STRT;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
      /* If the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= ~FLASH_CR_OPTER;

      /* Enable the Option Bytes Programming operation */
      FLASH->CR |= FLASH_CR_OPTPG;

      OB->USER_RDP = ob_user_rdp;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

      if(status != FLASH_TIMEOUT)
      {
        /* if the program operation is completed, disable the OPTPG Bit */
        FLASH->CR &= ~FLASH_CR_OPTPG;
      }
    }
    else
    {
      if(status != FLASH_TIMEOUT)
      {
        /* Disable the OPTER Bit */
        FLASH->CR &= ~FLASH_CR_OPTER;
      }
    }
  }
  /* Return the protection operation Status */
  return status;
}

/**
  * @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  OB_IWDG: Selects the WDG mode
  *          This parameter can be one of the following values:
  *             @arg OB_IWDG_SW: Software WDG selected
  *             @arg OB_IWDG_HW: Hardware WDG selected
  * @param  OB_STOP: Reset event when entering STOP mode.
  *          This parameter can be one of the following values:
  *             @arg OB_STOP_NoRST: No reset generated when entering in STOP
  *             @arg OB_STOP_RST: Reset generated when entering in STOP
  * @param  OB_STDBY: Reset event when entering Standby mode.
  *          This parameter can be one of the following values:
  *             @arg OB_STDBY_NoRST: No reset generated when entering in STANDBY
  *             @arg OB_STDBY_RST: Reset generated when entering in STANDBY
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY)
{
  FLASH_Status status = FLASH_COMPLETE;
    uint32_t ob_user_rdp = 0;
    uint8_t ob_user = 0,ob_nuser = 0;

  /* Check the parameters */
  assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
  assert_param(IS_OB_STOP_SOURCE(OB_STOP));
  assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    ob_user = OB->USER_RDP >>16 & 0xF8;//Clear
    ob_user |= OB_IWDG | OB_STOP | OB_STDBY;
    ob_nuser = ~ob_user;

    ob_user_rdp = (OB->USER_RDP &0x0000ffff) |  ob_user<<16 | ob_nuser<<24;

  if(status == FLASH_COMPLETE)
  {
    FLASH->CR |= FLASH_CR_OPTER;
    FLASH->CR |= FLASH_CR_STRT;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
      /* If the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= ~FLASH_CR_OPTER;
            /* Enable the Option Bytes Programming operation */
            FLASH->CR |= FLASH_CR_OPTPG;

            OB->USER_RDP = ob_user_rdp;

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

            if(status != FLASH_TIMEOUT)
            {
                /* If the program operation is completed, disable the OPTPG Bit */
                FLASH->CR &= ~FLASH_CR_OPTPG;
            }
        }
    }
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Sets or resets the BOOT1 option bit.
  * @param  OB_BOOT1: Set or Reset the BOOT1 option bit.
  *          This parameter can be one of the following values:
  *             @arg OB_BOOT1_RESET: BOOT1 option bit reset
  *             @arg OB_BOOT1_SET: BOOT1 option bit set
  * @retval None
  */
FLASH_Status FLASH_OB_BOOTConfig(uint8_t OB_BOOT1)
{
  FLASH_Status status = FLASH_COMPLETE;
    uint32_t ob_user_rdp = 0;
    uint8_t ob_user =0,ob_nuser = 0;

  /* Check the parameters */
  assert_param(IS_OB_BOOT1(OB_BOOT1));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    ob_user = OB->USER_RDP >>16 & 0xef;//Clear
    ob_user |= OB_BOOT1;
    ob_nuser = ~ob_user;
  ob_user_rdp = (OB->USER_RDP &0x0000ffff) |  ob_user<<16 | ob_nuser<<24;

  if(status == FLASH_COMPLETE)
  {
    FLASH->CR |= FLASH_CR_OPTER;
    FLASH->CR |= FLASH_CR_STRT;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
      /* If the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= ~FLASH_CR_OPTER;
            /* Enable the Option Bytes Programming operation */
            FLASH->CR |= FLASH_CR_OPTPG;

            OB->USER_RDP = ob_user_rdp;

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

            if(status != FLASH_TIMEOUT)
            {
                /* If the program operation is completed, disable the OPTPG Bit */
                FLASH->CR &= ~FLASH_CR_OPTPG;
            }
        }
    }
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Sets or resets the analogue monitoring on VDDA Power source.
  * @param  OB_VDDA_ANALOG: Selects the analog monitoring on VDDA Power source.
  *          This parameter can be one of the following values:
  *             @arg OB_VDDA_ANALOG_ON: Analog monitoring on VDDA Power source ON
  *             @arg OB_VDDA_ANALOG_OFF: Analog monitoring on VDDA Power source OFF
  * @retval None
  */
FLASH_Status FLASH_OB_VDDAConfig(uint8_t OB_VDDA_ANALOG)
{
  FLASH_Status status = FLASH_COMPLETE;
    uint32_t ob_user_rdp = 0;
    uint8_t ob_user = 0,ob_nuser = 0;

  /* Check the parameters */
  assert_param(IS_OB_VDDA_ANALOG(OB_VDDA_ANALOG));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    ob_user = OB->USER_RDP >>16 & 0xdf;//Clear
    ob_user |= OB_VDDA_ANALOG;
    ob_nuser = ~ob_user;
  ob_user_rdp = (OB->USER_RDP &0x0000ffff) |  ob_user<<16 | ob_nuser<<24;

  if(status == FLASH_COMPLETE)
  {
    FLASH->CR |= FLASH_CR_OPTER;
    FLASH->CR |= FLASH_CR_STRT;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
      /* If the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= ~FLASH_CR_OPTER;
            /* Enable the Option Bytes Programming operation */
            FLASH->CR |= FLASH_CR_OPTPG;

            OB->USER_RDP = ob_user_rdp;

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

            if(status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CR &= ~FLASH_CR_OPTPG;
            }
        }
    }
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Sets or resets the SRAM parity.
  * @param  OB_SRAM_Parity: Set or Reset the SRAM parity enable bit.
  *          This parameter can be one of the following values:
  *             @arg OB_SRAM_PARITY_SET: Set SRAM parity.
  *             @arg OB_SRAM_PARITY_RESET: Reset SRAM parity.
  * @retval None
  */
FLASH_Status FLASH_OB_SRAMParityConfig(uint8_t OB_SRAM_Parity)
{
  FLASH_Status status = FLASH_COMPLETE;
    uint32_t ob_user_rdp = 0;
    uint8_t ob_user = 0,ob_nuser = 0;

  /* Check the parameters */
  assert_param(IS_OB_SRAM_PARITY(OB_SRAM_Parity));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    ob_user = OB->USER_RDP >>16 & 0xbf;//Clear
    ob_user |= OB_SRAM_Parity;
    ob_nuser = ~ob_user;
  ob_user_rdp = (OB->USER_RDP &0x0000ffff) |  ob_user<<16 | ob_nuser<<24;

  if(status == FLASH_COMPLETE)
  {
    FLASH->CR |= FLASH_CR_OPTER;
    FLASH->CR |= FLASH_CR_STRT;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
      /* If the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= ~FLASH_CR_OPTER;
            /* Enable the Option Bytes Programming operation */
            FLASH->CR |= FLASH_CR_OPTPG;

            OB->USER_RDP = ob_user_rdp;

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

            if(status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CR &= ~FLASH_CR_OPTPG;
            }
        }
    }
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Programs the FLASH User Option Byte: IWDG_SW, RST_STOP, RST_STDBY,
  *         BOOT1 and VDDA ANALOG monitoring.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  OB_USER: Selects all user option bytes
  *          This parameter is a combination of the following values:
  *             @arg OB_IWDG_SW / OB_IWDG_HW: Software / Hardware WDG selected
  *             @arg OB_STOP_NoRST / OB_STOP_RST: No reset / Reset generated when entering in STOP
  *             @arg OB_STDBY_NoRST / OB_STDBY_RST: No reset / Reset generated when entering in STANDBY
  *             @arg OB_BOOT1_RESET / OB_BOOT1_SET: BOOT1 Reset / Set
  *             @arg OB_VDDA_ANALOG_ON / OB_VDDA_ANALOG_OFF: Analog monitoring on VDDA Power source ON / OFF
  *             @arg OB_SRAM_PARITY_SET / OB_SRAM_PARITY_RESET: SRAM Parity SET / RESET
  *             @arg OB_BOOT0_RESET / OB_BOOT0_SET: BOOT0 Reset / Set
  *             @arg OB_BOOT0_SW / OB_BOOT0_SW: BOOT0 pin disabled / BOOT0 pin bonded with GPIO
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_WriteUser(uint8_t OB_USER)
{
  FLASH_Status status = FLASH_COMPLETE;
    uint32_t ob_user_rdp = 0;
    uint8_t ob_user = 0,ob_nuser = 0;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    ob_user = OB->USER_RDP >>16 & 0x00;//Clear
    ob_user |= OB_USER;
    ob_nuser = ~ob_user;
  ob_user_rdp = (OB->USER_RDP &0x0000ffff) |  ob_user<<16 | ob_nuser<<24;

  if(status == FLASH_COMPLETE)
  {
    FLASH->CR |= FLASH_CR_OPTER;
    FLASH->CR |= FLASH_CR_STRT;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
      /* If the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= ~FLASH_CR_OPTER;
            /* Enable the Option Bytes Programming operation */
            FLASH->CR |= FLASH_CR_OPTPG;

            OB->USER_RDP = ob_user_rdp;

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

            if(status != FLASH_TIMEOUT)
            {
                /* If the program operation is completed, disable the OPTPG Bit */
                FLASH->CR &= ~FLASH_CR_OPTPG;
            }
        }
    }
  /* Return the Option Byte program Status */
  return status;

}

/**
  * @brief  Programs a half word at a specified Option Byte Data address.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  Address: specifies the address to be programmed.
  *          This parameter can be 0x1FFFF804.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_ProgramData(uint32_t Address, uint32_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_OB_DATA_ADDRESS(Address));
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status == FLASH_COMPLETE)
    {
        /* Enables the Option Bytes Programming operation */
        FLASH->CR |= FLASH_CR_OPTPG;
        *(__IO uint32_t*)Address = Data;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        if(status != FLASH_TIMEOUT)
        {
            /* If the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= ~FLASH_CR_OPTPG;
        }
    }
  /* Return the Option Byte Data Program Status */
  return status;
}
#endif

/**
  * @brief  Returns the FLASH User Option Bytes values.
  * @param  None
  * @retval The FLASH User Option Bytes .
  */
uint8_t FLASH_OB_GetUser(void)
{
  /* Return the User Option Byte */
  return (uint8_t)(FLASH->OBR >> 8);
}

/**
  * @brief  Returns the FLASH Write Protection Option Bytes value.
  * @param  None
  * @retval The FLASH Write Protection Option Bytes value
  */
uint32_t FLASH_OB_GetWRP(void)
{
  /* Return the FLASH write protection Register value */
  return (uint32_t)(FLASH->WRPR);
}

/**
  * @brief  Checks whether the FLASH Read out Protection Status is set or not.
  * @param  None
  * @retval FLASH ReadOut Protection Status(SET or RESET)
  */
FlagStatus FLASH_OB_GetRDP(void)
{
  FlagStatus readstatus = RESET;

  if ((uint8_t)(FLASH->OBR & (FLASH_OBR_RDPRT1 | FLASH_OBR_RDPRT2)) != RESET)
  {
    readstatus = SET;
  }
  else
  {
    readstatus = RESET;
  }
  return readstatus;
}

/**
  * @}
  */

/**
  * @brief  Enables or disables the specified FLASH interrupts.
  * @param  FLASH_IT: specifies the FLASH interrupt sources to be enabled or
  *         disabled.
  *          This parameter can be any combination of the following values:
  *             @arg FLASH_IT_EOP: FLASH end of programming Interrupt
  *             @arg FLASH_IT_ERR: FLASH Error Interrupt
  * @retval None
  */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FLASH_IT(FLASH_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if(NewState != DISABLE)
  {
    /* Enable the interrupt sources */
    FLASH->CR |= FLASH_IT;
  }
  else
  {
    /* Disable the interrupt sources */
    FLASH->CR &= ~(uint32_t)FLASH_IT;
  }
}

/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @param  FLASH_FLAG: specifies the FLASH flag to check.
  *          This parameter can be one of the following values:
  *             @arg FLASH_FLAG_BSY: FLASH write/erase operations in progress flag
  *             @arg FLASH_FLAG_PGERR: FLASH Programming error flag flag
  *             @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
  *             @arg FLASH_FLAG_EOP: FLASH End of Programming flag
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG));

  if((FLASH->SR & FLASH_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the new state of FLASH_FLAG (SET or RESET) */
  return bitstatus;
}

/**
  * @brief  Clears the FLASH's pending flags.
  * @param  FLASH_FLAG: specifies the FLASH flags to clear.
  *          This parameter can be any combination of the following values:
  *             @arg FLASH_FLAG_PGERR: FLASH Programming error flag flag
  *             @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
  *             @arg FLASH_FLAG_EOP: FLASH End of Programming flag
  * @retval None
  */
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
  /* Check the parameters */
  assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG));

  /* Clear the flags */
  FLASH->SR = FLASH_FLAG;
}

/**
  * @brief  Returns the FLASH Status.
  * @param  None
  * @retval FLASH Status: The returned value can be:
  *         FLASH_BUSY, FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP or FLASH_COMPLETE.
  */
FLASH_Status FLASH_GetStatus(void)
{
  FLASH_Status FLASHstatus = FLASH_COMPLETE;

  if((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY)
  {
    FLASHstatus = FLASH_BUSY;
  }
  else
  {
    if((FLASH->SR & (uint32_t)FLASH_FLAG_WRPERR)!= (uint32_t)0x00)
    {
      FLASHstatus = FLASH_ERROR_WRP;
    }
    else
    {
      if((FLASH->SR & (uint32_t)(FLASH_SR_PGERR)) != (uint32_t)0x00)
      {
        FLASHstatus = FLASH_ERROR_PROGRAM;
      }
      else
      {
        FLASHstatus = FLASH_COMPLETE;
      }
    }
  }
  /* Return the FLASH Status */
  return FLASHstatus;
}


/**
  * @brief  Waits for a FLASH operation to complete or a TIMEOUT to occur.
  * @param  Timeout: FLASH programming Timeout
  * @retval FLASH Status: The returned value can be: FLASH_BUSY,
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check for the FLASH Status */
  status = FLASH_GetStatus();

  /* Wait for a FLASH operation to complete or a TIMEOUT to occur */
  while((status == FLASH_BUSY) && (Timeout != 0x00))
  {
    status = FLASH_GetStatus();
    Timeout--;
  }

  if(Timeout == 0x00 )
  {
    status = FLASH_TIMEOUT;
  }
  /* Return the operation status */
  return status;
}

/**
  * @}
  */

/**
  * @}
  */

  /**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
