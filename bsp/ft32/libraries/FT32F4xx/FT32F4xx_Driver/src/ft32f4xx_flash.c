/**
  ******************************************************************************
  * @file               ft32f4xx_flash.c
  * @author             FMD xzhang
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the FLASH peripheral:
  *                 - FLASH Interface configuration
  *                 - FLASH Memory Programming
  *                 - Option Bytes Programming
  *                 - Interrupts and flags management
  * @version            V1.0.0
  * @data                   2025-03-13
    ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_flash.h"

/**
  * @brief  Sets the code latency value.
  * @param  FLASH_Latency: specifies the FLASH Latency value.
  *          This parameter can be one of the following values:
  *             @arg FLASH_Latency_0: FLASH 0 Latency cycle
  *             @arg FLASH_Latency_1: FLASH 1 Latency cycle
  *             @arg FLASH_Latency_2: FLASH 2 Latency cycle
  *             @arg FLASH_Latency_3: FLASH 3 Latency cycle
  *             @arg FLASH_Latency_4: FLASH 4 Latency cycle
  *             @arg FLASH_Latency_5: FLASH 5 Latency cycle
  *             @arg FLASH_Latency_6: FLASH 6 Latency cycle
  *             @arg FLASH_Latency_7: FLASH 7 Latency cycle
  * @retval None
  */
void FLASH_SetLatency(uint32_t FLASH_Latency)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_FLASH_LATENCY(FLASH_Latency));

    /* Read the RDC register */
    tmpreg = FLASH->RDC;

    /* Sets the Latency value */
    tmpreg &= (uint32_t)(~((uint32_t)FLASH_RDC_LATENCY));
    tmpreg |= FLASH_Latency;

    /* Write the  RDC register */
    FLASH->RDC = tmpreg;
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

    if (NewState != DISABLE)
    {
        FLASH->RDC |= FLASH_RDC_PRFTBE ;
    }
    else
    {
        FLASH->RDC &= ~FLASH_RDC_PRFTBE;
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

    if ((FLASH->RDC & FLASH_RDC_PRFTBS) != (uint32_t)RESET)
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
  * @brief  UnLocks the Program memory access.
  * @param  None
  * @retval None
  */
void FLASH_Unlock(void)
{
    unsigned int read_data;
    do
    {
        read_data = FLASH->FR ;
    }
    while ((read_data & FLASH_FR_BSY) != 0);
    /*KEYR write key1 0x45670123 key2 0xCDEF89AB*/
    if ((FLASH->WRC & FLASH_WRC_LOCK) != 0)
    {
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
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
    FLASH->WRC |= FLASH_WRC_LOCK;
}


/**
  * @brief  Erases a specified page in program memory.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  page_num: The page number in program memory to be erased.
  * @param  erase_size: The size of erase :
  *          This parameter can be:
  *             @arg ERASE_SIZE_0:Erase size is 512B  (default value)
  *             @arg ERASE_SIZE_1: Erase size is 2KB
  *             @arg ERASE_SIZE_2: Erase size is 16KB
  * @note   A Page is erased in the Program memory only if the address to load
  *         is the start address of a page (multiple of 512 bytes).
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ErasePage(uint32_t page_num, uint32_t erase_size)
{
    FLASH_Status status = FLASH_COMPLETE;
    uint32_t    erase_page_num;

    /* Check the parameters */
    assert_param(IS_FLASH_ERASE_PAGE_NUM(page_num));
    assert_param(IS_ERASE_SIZE(erase_size));

    FLASH_PrefetchBufferCmd(DISABLE);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
        /* If the previous operation is completed, proceed to erase the page */
        /*PNB in bit6-15 of WRC reg*/
        erase_page_num = (page_num << 6);
        /*clear status flag*/
        FLASH->FR |= FLASH_FR_CLEAR;
        /*clear page number*/
        FLASH->WRC &= (~FLASH_WRC_PNB);
        /*Active page Erase function*/
        FLASH->WRC |= FLASH_WRC_PER;
        /*select erase size*/
        FLASH->WRC |= erase_size;
        /*Page ERASE ERASE start*/
        FLASH->WRC |= (erase_page_num) |  FLASH_WRC_STRT;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
        /*clear FLASH_WRC_PER & FLASH_WRC_STRT*/
        FLASH->WRC &= (~FLASH_WRC_STRT) & (~FLASH_WRC_PER);

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

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {

        /* If the previous operation is completed, proceed to erase the page */
        /*clear status flag; clear page numbe; ERASE start*/
        FLASH->FR |= FLASH_FR_CLEAR;
        FLASH->WRC |= FLASH_WRC_MER | FLASH_WRC_STRT;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
        /*clear FLASH_WRC_MER & FLASH_WRC_STRT*/
        FLASH->WRC &= (~FLASH_WRC_MER) & (~FLASH_WRC_STRT);

    }

    FLASH_PrefetchBufferCmd(ENABLE);

    return status;
}

/**
  * @brief  Programs 4 word continued at a specified address.
  * @note   To correctly run this function, the FLASH_Unlock() FLASH_ErasePage() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  Address: specifies the address to be programmed,address is the first address of Data0
  * @param  Datax: specifies the 4 data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data3, uint32_t Data2, uint32_t Data1, uint32_t Data0)
{
    /*clear status flag*/
    FLASH->FR |= FLASH_FR_CLEAR;
    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

    FLASH_PrefetchBufferCmd(DISABLE);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
        //enable function of program firstly
        FLASH->WRC |= FLASH_WRC_PG;

        /*  proceed to program the data3 */
        *(__IO uint32_t*)Address = (uint32_t)Data0;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        if (status == FLASH_COMPLETE)
        {
            /* If the previous operation is completed, proceed to program the new  word */
            *(__IO uint32_t*)(Address + 0x4)  = (uint32_t) Data1;

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
            if (status == FLASH_COMPLETE)
            {
                /* If the previous operation is completed, proceed to program the new  word */
                *(__IO uint32_t*)(Address + 0x8)  = (uint32_t) Data2;

                /* Wait for last operation to be completed */
                status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

                if (status == FLASH_COMPLETE)
                {
                    /* If the previous operation is completed, proceed to program the new word */
                    *(__IO uint32_t*)(Address + 0xc)  = (uint32_t) Data3;

                    /* Wait for last operation to be completed */
                    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

                    /* Disable the PG Bit */
                    FLASH->WRC &= ~FLASH_WRC_PG;
                }
            }
        }

    }
    else
    {
        /* Disable the PG Bit */
        FLASH->WRC &= ~FLASH_WRC_PG;
    }
    FLASH_PrefetchBufferCmd(ENABLE);

    return status;
}


/**
  * @brief  Programs a word at a specified address.
  * @note   To correctly run this function, the FLASH_Unlock() FLASH_ErasePage() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  Address: specifies the address to be programmed
  * @param  Data0: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_Program_oneWord(uint32_t Address, uint32_t Data0)
{
    /*clear status flag*/
    FLASH->FR |= FLASH_FR_CLEAR;
    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

    FLASH_PrefetchBufferCmd(DISABLE);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
        //enable function of program firstly
        FLASH->WRC |= FLASH_WRC_PG;

        /*  proceed to program the data3 */
        *(__IO uint32_t*)Address = (uint32_t)Data0;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        /* Disable the PG Bit */
        FLASH->WRC &= ~FLASH_WRC_PG;
    }
    else
    {
        /* Disable the PG Bit */
        FLASH->WRC &= ~FLASH_WRC_PG;
    }

    FLASH_PrefetchBufferCmd(ENABLE);
    return status;
}
/**
  * @brief  Programs a half word at a specified address.
  * @note   To correctly run this function, the FLASH_Unlock() FLASH_ErasePage() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  Address: specifies the address to be programmed,address is the first address of Datax.
  * @param  Datax: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_Program_HalfWord(uint32_t Address, uint16_t Data0)
{
    /*clear status flag*/
    FLASH->FR |= FLASH_FR_CLEAR;
    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

    FLASH_PrefetchBufferCmd(DISABLE);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
        //enable function of program
        FLASH->WRC |= FLASH_WRC_PG;
        /*  proceed to program the data0 */
        *(__IO uint16_t*)Address = (uint16_t)Data0;

        while ((FLASH->FR & FLASH_FR_BSY) != 0);

        /* Disable the PG Bit */
        FLASH->WRC &= ~FLASH_WRC_PG;
    }
    else
    {
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }

    FLASH_PrefetchBufferCmd(ENABLE);
    return status;
}


/**
  * @brief  Programs 1 Byte at a specified address.
  * @note   To correctly run this function, the FLASH_Unlock() FLASH_ErasePage() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
  *         to protect the FLASH memory against possible unwanted operation)
  * @param  Address: specifies the address to be programmed,address is the first address of Datax.
  * @param  Datax: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_Program_Byte(uint32_t Address, uint8_t Data0)
{
    /*clear status flag*/
    FLASH->FR |= FLASH_FR_CLEAR;
    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

    FLASH_PrefetchBufferCmd(DISABLE);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
        /*enable function of program*/
        FLASH->WRC |= FLASH_WRC_PG;

        /*proceed to program the data3 */
        *(__IO uint8_t*)Address = (uint8_t)Data0;

        while ((FLASH->FR & FLASH_FR_BSY) != 0);

        /* Disable the PG Bit */
        FLASH->WRC &= ~FLASH_WRC_PG;
    }
    else
    {
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }

    FLASH_PrefetchBufferCmd(ENABLE);
    return status;
}

/**
  * @brief  Unlocks the option bytes block access.
  * @param  None
  * @retval None
  */
void FLASH_OPBC_Unlock(void)
{
    unsigned int read_data;

    do
    {
        read_data = FLASH->FR ;
    }
    /*flash is not busy now*/
    while ((read_data & FLASH_FR_BSY) != 0);

    /*option byte is unlock*/
    if ((FLASH->OPBC & FLASH_OPBC_OPTLOCK) != 0)
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
void FLASH_OPBC_Lock(void)
{
    /* Set the OPTLOCK Bit to lock the option bytes block access */
    FLASH->OPBC |= FLASH_OPBC_OPTLOCK;
}


/**
  * @brief  Write protects the desired pages
  * @note   To correctly run this function, the FLASH_OPBC_Unlock() function must be called before.
  * @note   Call the FLASH_OPBC_lock() to disable the flash control register access and the option after FLASH_OPBC_Unlock
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  WRPR_WRP: specifies the address of the pages to be write protected.
  *          This parameter can be:
  *             @arg WRP_PAGE0_31 to WRP_PAGE992_1023
  *             @arg WRP_AllPAGES
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_WRPR_EnableWRP(uint32_t WRPR_WRP)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_WRPR_WRP(WRPR_WRP));

    FLASH_PrefetchBufferCmd(DISABLE);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    if (status == FLASH_COMPLETE)
    {
        FLASH->WRPR = WRPR_WRP;
        FLASH->OPBC |= FLASH_OPBC_OPTSTRT;//update OPBC reg value

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTSTART Bit */
            FLASH->OPBC &= ~FLASH_OPBC_OPTSTRT;
        }
    }

    FLASH_PrefetchBufferCmd(ENABLE);
    return status;
}


/**
  * @brief  Enables or disables the read out protection.
  * @note   To correctly run this function, the FLASH_OPBC_Unlock() function must be called before.
  * @note   Call the FLASH_OPBC_lock() to disable the flash control register access and the option after FLASH_OPBC_Unlock
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  FLASH_ReadProtection_Level: specifies the read protection level.
  *          This parameter can be:
  *             @arg OPBC_RDP_Level_0: Read protection 0 of the memory
  *             @arg OPBC_RDP_Level_1: Read protection 1 of the memory
  *             @arg OPBC_RDP_Level_2: Read protection 2 of the memory (Be CAREFUL !! to use protection 2)
  * @note   When enabling OPBC_RDP level 2 it's no more possible to go back to level 1 or 0
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OPBC_RDPConfig(uint8_t OPBC_RDP)
{
    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_OPBC_RDP(OPBC_RDP));

    uint32_t opbc_data;
    opbc_data = (FLASH->OPBC);
    opbc_data &= ~(0xff << 8);
    opbc_data |= (OPBC_RDP << 8);

    FLASH_PrefetchBufferCmd(DISABLE);

    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    if (status == FLASH_COMPLETE)
    {
        FLASH->OPBC  = opbc_data | FLASH_OPBC_OPTSTRT ;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTSTART Bit */
            FLASH->OPBC &= ~FLASH_OPBC_OPTSTRT;
        }
    }

    FLASH_PrefetchBufferCmd(ENABLE);
    return status;
}


/**
  * @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
  * @note   To correctly run this function, the FLASH_OPBC_Unlock() function must be called before.
  * @note   Call the FLASH_OPBC_lock() to disable the flash control register access and the optio after FLASH_OPBC_Unlock
  *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  OPBC_IWDG: Selects the WDG mode
  *          This parameter can be one of the following values:
  *             @arg OPBC_IWDG_SW: Software WDG selected 1
  *             @arg OPBC_IWDG_HW: Hardware WDG selected 0
  * @param  OPBC_STOP: Reset event when entering STOP mode.
  *          This parameter can be one of the following values:
  *             @arg OPBC_STOP_NoRST: No reset generated when entering in STOP
  *             @arg OPBC_STOP_RST: Reset generated when entering in STOP
  * @param  OPBC_STDBY: Reset event when entering Standby mode.
  *          This parameter can be one of the following values:
  *             @arg OPBC_STDBY_NoRST: No reset generated when entering in STANDBY
  *             @arg OPBC_STDBY_RST: Reset generated when entering in STANDBY
  * @retval FLASH Status: The returned value can be:
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OPBC_UserConfig(uint8_t OPBC_IWDG, uint8_t OPBC_STOP, uint8_t OPBC_STDBY)
{
    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_OPBC_IWDG_SOURCE(OPBC_IWDG));
    assert_param(IS_OPBC_STOP_SOURCE(OPBC_STOP));
    assert_param(IS_OPBC_STDBY_SOURCE(OPBC_STDBY));

    FLASH_PrefetchBufferCmd(DISABLE);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    uint32_t opbc_data;
    opbc_data = (FLASH->OPBC);
    opbc_data &= ~(0xff);
    opbc_data |= OPBC_IWDG | OPBC_STOP | OPBC_STDBY;


    if (status == FLASH_COMPLETE)
    {
        FLASH->OPBC = (opbc_data | FLASH_OPBC_OPTSTRT);

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

        if (status != FLASH_TIMEOUT)
        {
            /* If the program operation is completed, disable the OPTPG Bit */
            FLASH->OPBC &= ~FLASH_OPBC_OPTSTRT;
        }
    }

    FLASH_PrefetchBufferCmd(ENABLE);
    /* Return the Option Byte program Status */
    return status;
}


/**
  * @brief  Set the BOR Level.
  * @note   To correctly run this function, the FLASH_OPBC_Unlock() function must be called before.
  * @param  BORR_Level specifies the Option Bytes posedge threshold voltage Level.
  *          This parameter can be one of the following values:
  *            @arg OPBC_BORR_LEVEL0: Supply threshold voltage 2.1v
  *            @arg OPBC_BORR_LEVEL1: Supply threshold voltage 2.3v
  *            @arg OPBC_BORR_LEVEL2: Supply threshold voltage 2.6v
  *            @arg OPBC_BORR_LEVEL3: Supply threshold voltage 2.9v
  * @param  BORF_Level specifies the Option Bytes negedge threshold voltage Level.
  *          This parameter can be one of the following values:  *
  *            @arg OPBC_BORF_LEVEL0: Supply threshold voltage 2.0v
  *            @arg OPBC_BORF_LEVEL1: Supply threshold voltage 2.2v
  *            @arg OPBC_BORF_LEVEL2: Supply threshold voltage 2.5v
  *            @arg OPBC_BORF_LEVEL3: Supply threshold voltage 2.8v
  * @param  NewState: new state of the configed undervoltage reset :BOR_EN.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval HAL Status
  */
FLASH_Status FLASH_OPBC_BOR_LevelConfig(uint32_t BORR_Level, uint32_t BORF_Level, FunctionalState NewState)
{
    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_OPBC_BORR_LEVEL(BORR_Level));
    assert_param(IS_OPBC_BORF_LEVEL(BORR_Level));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    FLASH_PrefetchBufferCmd(DISABLE);

    uint32_t opbc_data;
    opbc_data = (FLASH->OPBC);
    opbc_data &= ~(0xff << 16);
    opbc_data |= BORR_Level | BORF_Level;


    if (NewState != DISABLE)
    {
        if (status == FLASH_COMPLETE)
        {
            /*enable configed undervoltage reset,config  BOR Level,Wait for last operation to be completed*/
            FLASH->OPBC = FLASH_OPBC_BOR_EN | opbc_data | FLASH_OPBC_OPTSTRT;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

            if (status != FLASH_TIMEOUT)
            {
                /* If the program operation is completed, disable the OPTSTRT Bit */
                FLASH->OPBC &= ~FLASH_OPBC_OPTSTRT;
            }
        }
    }
    else
    {
        /*disable configed undervoltage reset*/
        FLASH->OPBC &= ~FLASH_OPBC_BOR_EN;
        /*update OPBC reg value*/
        FLASH->OPBC = opbc_data | FLASH_OPBC_OPTSTRT;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
        if (status != FLASH_TIMEOUT)
        {
            /* If the program operation is completed, disable the OPTSTRT Bit */
            FLASH->OPBC &= ~FLASH_OPBC_OPTSTRT;
        }
    }

    FLASH_PrefetchBufferCmd(ENABLE);
    /* Return the Option Byte program Status */
    return status;
}



/**
  * @brief  Clears the FLASH's pending flags.
  * @param  FLASH_FLAG: specifies the FLASH flags to clear.
  *          This parameter can be any combination of the following values:
  *             @arg FLASH_FLAG_PGERR: FLASH Programming error flag flag
  *             @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
  *             @arg FLASH_FLAG_EOP: FLASH End of Programming flag
  *             @arg FLASH_FLAG_PGSERR:FLASH Programming sequence error flag
  *             @arg FLASH_FLAG_OPBERR:user option and factory are not load correctly flag
  * @note  Can not clear FLASH_FLAG_BSY flag
  * @retval None
  */
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
    /* Check the parameters */
    assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG));

    /* Clear the flags( RC_W1 )*/
    FLASH->FR |= FLASH_FLAG;
}


/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @param  FLASH_FLAG: specifies the FLASH flag to check.
  *          This parameter can be one of the following values:
  *             @arg FLASH_FLAG_BSY: FLASH write/erase operations in progress flag
  *             @arg FLASH_FLAG_PGERR: FLASH Programming error flag flag
  *             @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
  *             @arg FLASH_FLAG_EOP: FLASH End of Programming flag
  *             @arg FLASH_FLAG_PGSERR:FLASH Programming sequence error flag
  *             @arg FLASH_FLAG_OPBERR:user option and factory are not load correctly flag
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG));

    if ((FLASH->FR & FLASH_FLAG) != (uint32_t)RESET)
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
  * @brief  Returns the FLASH Write Protection Option Bytes value.
  * @param  None
  * @retval The FLASH Write Protection Option Bytes value
  */
uint32_t FLASH_OPBC_GetWRP(void)
{
    /* Return the FLASH write protection Register value */
    return (uint32_t)(FLASH->WRPR);
}


/**
  * @brief  Checks whether the FLASH Read out Protection Status is set or not.
  * @param  None
  * @retval FLASH ReadOut Protection Status(SET or RESET)
  */
FlagStatus FLASH_OPBC_GetRDP(void)
{
    FlagStatus readstatus = RESET;
    uint32_t Temp = ((FLASH -> OPBC) & FLASH_OPBC_RDP_Msk);
    if (Temp == (OPBC_RDP_Level_1 << 8) || Temp == (OPBC_RDP_Level_2 << 8))
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
  * @brief  Enables or disables the specified FLASH interrupts.
  * @param  FLASH_IT: specifies the FLASH interrupt sources to be enabled or
  *         disabled.
  *          This parameter can be any combination of the following values:
  *             @arg FLASH_IT_EOP: FLASH end of programming Interrupt
  *             @arg FLASH_IT_ERR: FLASH Error Interrupt
  * @param  NewState: new state of the flash Interrupt
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FLASH_IT(FLASH_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the interrupt sources */
        FLASH->WRC |= FLASH_IT;
    }
    else
    {
        /* Disable the interrupt sources */
        FLASH->WRC &= ~(uint32_t)FLASH_IT;
    }
}


/**
  * @brief  Returns the FLASH Status.
  * @param  None
  * @retval FLASH Status: The returned value can be:
  *         FLASH_BUSY, FLASH_ERROR_PROGRAM,FLASH_ERROR_PGSERR, FLASH_ERROR_WRP or FLASH_COMPLETE.
  */
FLASH_Status FLASH_GetStatus(void)
{
    FLASH_Status FLASHstatus = FLASH_COMPLETE;

    if ((FLASH->FR & (uint32_t)FLASH_FLAG_BSY) != (uint32_t)0x00)
    {
        FLASHstatus = FLASH_BUSY;
    }
    else
    {
        if ((FLASH->FR & (uint32_t)FLASH_FLAG_WRPERR) != (uint32_t)0x00)
        {
            FLASHstatus = FLASH_ERROR_WRP;
        }
        else
        {
            if ((FLASH->FR & (uint32_t)(FLASH_FLAG_PGERR)) != (uint32_t)0x00)
            {
                FLASHstatus = FLASH_ERROR_PROGRAM;
            }
            else
            {
                if ((FLASH->FR & (uint32_t)(FLASH_FLAG_PGSERR)) != (uint32_t)0x00)
                {
                    FLASHstatus = FLASH_ERROR_PGSERR;
                }
                else
                {
                    FLASHstatus = FLASH_COMPLETE;
                }
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
    while ((status == FLASH_BUSY) && (Timeout != 0x00))
    {
        status = FLASH_GetStatus();
        Timeout--;
    }

    if (Timeout == 0x00)
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
