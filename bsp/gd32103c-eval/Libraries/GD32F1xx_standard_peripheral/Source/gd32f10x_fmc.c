/**
  ******************************************************************************
  * @brief   FMC functions of the firmware library.
  ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_fmc.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup FMC
  * @brief FMC driver modules
  * @{
  */

/** @defgroup FMC_Private_Functions
  * @{
  */

/** @defgroup FMC_Group1 FMC Memory Programming functions
 *  @brief    FMC Memory Programming functions
 *
@verbatim
 ===============================================================================
                ##### FMC Memory Programming functions #####
 ===============================================================================

    [..] The FMC Memory Programming functions, includes the following functions:
       (+) void FMC_Unlock(void);
       (+) void FMC_UnlockBank1(void);
       (+) void FMC_UnlockBank2(void);
       (+) void FMC_Lock(void);
       (+) void FMC_LockBank1(void)
       (+) void FMC_LockBank2(void)
       (+) FMC_State FMC_ErasePage(uint32_t Page_Address);
       (+) FMC_State FMC_MassErase(void);
       (+) FMC_State FMC_MassBank1Erase(void)
       (+) FMC_State FMC_MassBank2Erase(void)
       (+) FMC_State FMC_ProgramWord(uint32_t Address, uint32_t Data);
    [..] Any operation of erase or program should follow these steps:

       (#) Call the FMC_Unlock() function to unlock the FMC operation
       (#) Call erase or program data
       (#) Call the FMC_Lock() to lock the FMC operation

@endverbatim
  * @{
  */
/**
  * @brief  Unlock the main FMC operation.
  * @param  None
  * @retval None
  */
void FMC_Unlock(void)
{
    if ((FMC->CMR & FMC_CMR_LK) != RESET) {
        /* Write the FMC key */
        FMC->UKEYR = FMC_KEY1;
        FMC->UKEYR = FMC_KEY2;
    }
    if (FMC_SIZE > FMC_BANK1_SIZE) {
        /* Authorize the FPEC of Bank2 Access */
        if ((FMC->CMR2 & FMC_CMR_LK) != RESET) {
            FMC->UKEYR2 = FMC_KEY1;
            FMC->UKEYR2 = FMC_KEY2;
        }
    }
}

/**
  * @brief  Unlocks the FMC Bank1 Program Erase Controller.
  * @note   This function can be used for all GD32F10x devices.
  *         - For GD32F10X_XD and GD32F10X_CL devices this function unlocks Bank1.
  *         - For all other devices it unlocks Bank1 and it is
  *           equivalent to FLASH_Unlock function.
  * @param  None
  * @retval None
  */
void FMC_UnlockB1(void)
{
    /* Authorize the FPEC of Bank1 Access */
    if ((FMC->CMR & FMC_CMR_LK) != RESET) {
        FMC->UKEYR = FMC_KEY1;
        FMC->UKEYR = FMC_KEY2;
    }
}

/**
  * @brief  Unlocks the FMC Bank2 Program Erase Controller.
  * @note   This function can be used  for GD32F10X_XD and GD32F10X_CL density devices.
  * @param  None
  * @retval None
  */
#if defined GD32F10X_XD || defined GD32F10X_CL
void FMC_UnlockB2(void)
{
    /* Authorize the FPEC of Bank2 Access */
    if ((FMC->CMR2 & FMC_CMR_LK) != RESET) {
        FMC->UKEYR2 = FMC_KEY1;
        FMC->UKEYR2 = FMC_KEY2;
    }
}
#endif /* GD32F10X_XD and GD32F10X_CL */

/**
  * @brief  Lock the main FMC operation.
  * @param  None
  * @retval None
  */
void FMC_Lock(void)
{
    /* Set the LOCK bit*/
    FMC->CMR |= FMC_CMR_LK;

    if (FMC_SIZE > FMC_BANK1_SIZE) {
        /* Set the Lock Bit to lock the FPEC and the CR of  Bank2 */
        FMC->CMR2 |= FMC_CMR_LK;
    }
}

/**
  * @brief  Locks the FMC Bank1 Program Erase Controller.
  * @note   this function can be used for all GD32F10X devices.
  *         - For GD32F10X_XD and GD32F10X_CL devices this function Locks Bank1.
  *         - For all other devices it Locks Bank1 and it is equivalent
  *           to FMC_Lock function.
  * @param  None
  * @retval None
  */
void FMC_LockB1(void)
{
    /* Set the Lock Bit to lock the FPEC and the CMR of  Bank1 */
    FMC->CMR |= FMC_CMR_LK;
}

/**
  * @brief  Locks the FMC Bank2 Program Erase Controller.
  * @note   This function can be used for GD32F10X_XD and GD32F10X_CL density devices.
  * @param  None
  * @retval None
  */
#if defined GD32F10X_XD || defined GD32F10X_CL
void FMC_LockB2(void)
{
    /* Set the Lock Bit to lock the FPEC and the CMR of  Bank2 */
    FMC->CMR2 |= FMC_CMR_LK;
}
#endif

/**
  * @brief  Erase a page.
  * @param  Page_Address: The page address to be erased.
  * @retval FMC state: FMC_READY, FMC_BSY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */
FMC_State FMC_ErasePage(uint32_t Page_Address)
{
    if (FMC_SIZE > FMC_BANK1_SIZE) {
        FMC_State temp_state = FMC_B1_WaitReady(FMC_TIMEOUT_COUNT);
        if (Page_Address < FMC_B1_END_ADDRESS) {
            /* Wait for last operation to be completed */
            FMC_State temp_state = FMC_B1_WaitReady(FMC_TIMEOUT_COUNT);

            if (temp_state == FMC_READY) {
                FMC->CMR |= FMC_CMR_PE;
                FMC->AR  = Page_Address;
                FMC->CMR |= FMC_CMR_START;

                /* Wait for the FMC ready */
                temp_state = FMC_B1_WaitReady(FMC_TIMEOUT_COUNT);

                /* Reset the PE bit */
                FMC->CMR &= ~FMC_CMR_PE;
            }
        } else {
            /* Wait for last operation to be completed */
            FMC_State temp_state = FMC_B2_WaitReady(FMC_TIMEOUT_COUNT);

            if (temp_state == FMC_READY) {
                FMC->CMR2 |= FMC_CMR_PE;
                FMC->AR2  = Page_Address;
                if (FMC->OPTR & FMC_OPTR_PLEVEL1) {
                    FMC->AR  = Page_Address;
                }
                FMC->CMR2 |= FMC_CMR_START;

                /* Wait for the FMC ready */
                temp_state = FMC_B2_WaitReady(FMC_TIMEOUT_COUNT);

                /* Reset the PE bit */
                FMC->CMR2 &= ~FMC_CMR_PE;
            }
        }
        /* Return the FMC state  */
        return temp_state;
    }

    else {
        FMC_State temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

        if (temp_state == FMC_READY) {
            /* Start page erase */
            FMC->CMR |= FMC_CMR_PE;
            FMC->AR  = Page_Address;
            FMC->CMR |= FMC_CMR_START;

            /* Wait for the FMC ready */
            temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

            /* Reset the PE bit */
            FMC->CMR &= ~FMC_CMR_PE;
        }
        /* Return the FMC state  */
        return temp_state;
    }
}

/**
  * @brief  Erase all main FMC.
  * @param  None
  * @retval FMC state: FMC_READY, FMC_BSY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */
FMC_State FMC_MassErase(void)
{
    if (FMC_SIZE > FMC_BANK1_SIZE) {
        /* Wait for last operation to be completed */
        FMC_State temp_state = FMC_B1_WaitReady(FMC_TIMEOUT_COUNT);
        if (temp_state == FMC_READY) {
            /* Start chip erase */
            FMC->CMR |= FMC_CMR_ME;
            FMC->CMR |= FMC_CMR_START;

            /* Wait for the FMC ready */
            temp_state = FMC_B1_WaitReady(FMC_TIMEOUT_COUNT);

            /* Reset the MER bit */
            FMC->CMR &= ~FMC_CMR_ME;
        }
        temp_state = FMC_B2_WaitReady(FMC_TIMEOUT_COUNT);
        if (temp_state == FMC_READY) {
            /* Start chip erase */
            FMC->CMR2 |= FMC_CMR_ME;
            FMC->CMR2 |= FMC_CMR_START;

            /* Wait for the FMC ready */
            temp_state = FMC_B2_WaitReady(FMC_TIMEOUT_COUNT);

            /* Reset the MER bit */
            FMC->CMR2 &= ~FMC_CMR_ME;
        }
        /* Return the FMC state  */
        return temp_state;
    } else {
        FMC_State temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

        if (temp_state == FMC_READY) {
            /* Start chip erase */
            FMC->CMR |= FMC_CMR_ME;
            FMC->CMR |= FMC_CMR_START;

            /* Wait for the FMC ready */
            temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

            /* Reset the MER bit */
            FMC->CMR &= ~FMC_CMR_ME;
        }
        /* Return the FMC state  */
        return temp_state;
    }
}

/**
  * @brief  Erases all Bank1 FMC pages.
  * @note   This function can be used for all GD32F10x devices.
  *         - For GD32F10X_XD and GD32F10X_CL devices this function erases all Bank1 pages.
  *         - For all other devices it erases all Bank1 pages and it is equivalent
  *           to FLASH_EraseAllPages function.
  * @param  None
  * @retval FLASH Status: FMC state: FMC_READY, FMC_BSY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */
FMC_State FMC_MassB1Erase(void)
{
    FMC_State temp_state = FMC_B1_WaitReady(FMC_TIMEOUT_COUNT);

    if (temp_state == FMC_READY) {
        /* Start chip erase */
        FMC->CMR |= FMC_CMR_ME;
        FMC->CMR |= FMC_CMR_START;

        /* Wait for the FMC ready */
        temp_state = FMC_B1_WaitReady(FMC_TIMEOUT_COUNT);

        /* Reset the MER bit */
        FMC->CMR &= ~FMC_CMR_ME;
    }
    /* Return the Erase Status */
    return temp_state;
}

/**
  * @brief  Erases all Bank2 FMC pages.
  * @note   This function can be used for GD32F10X_XD and GD32F10X_CL density devices.
  * @param  None
  * @retval FMC Status: FMC state: FMC_READY, FMC_BSY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */

FMC_State FMC_MassB2Erase(void)
{
    FMC_State temp_state = FMC_B2_WaitReady(FMC_TIMEOUT_COUNT);

    if (temp_state == FMC_READY) {
        /* Start chip erase */
        FMC->CMR2 |= FMC_CMR_ME;
        FMC->CMR2 |= FMC_CMR_START;

        /* Wait for the FMC ready */
        temp_state = FMC_B2_WaitReady(FMC_TIMEOUT_COUNT);

        /* Reset the MER bit */
        FMC->CMR2 &= ~FMC_CMR_ME;
    }
    /* Return the Erase Status */
    return temp_state;
}


/**
  * @brief  Program a word at the corresponding address.
  * @param  Address: The address to be programmed.
  * @param  Data: The data to be programmed.
  * @retval FMC state: FMC_READY, FMC_BSY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */
FMC_State FMC_ProgramWord(uint32_t Address, uint32_t Data)
{
    if (FMC_SIZE > FMC_BANK1_SIZE) {
        FMC_State temp_state = FMC_B1_WaitReady(FMC_TIMEOUT_COUNT);
        if (Address < FMC_B1_END_ADDRESS) {
            FMC_State temp_state = FMC_B1_WaitReady(FMC_TIMEOUT_COUNT);

            if (temp_state == FMC_READY) {
                /* Set the PG bit to start program */
                FMC->CMR |= FMC_CMR_PG;

                *(__IO uint32_t *)Address = Data;

                /* Wait for the FMC ready */
                temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

                /* Reset the PG bit */
                FMC->CMR &= ~FMC_CMR_PG;
            }
        } else {
            FMC_State temp_state = FMC_B2_WaitReady(FMC_TIMEOUT_COUNT);

            if (temp_state == FMC_READY) {
                /* Set the PG bit to start program */
                FMC->CMR2 |= FMC_CMR_PG;

                *(__IO uint32_t *)Address = Data;

                /* Wait for the FMC ready */
                temp_state = FMC_B2_WaitReady(FMC_TIMEOUT_COUNT);

                /* Reset the PG bit */
                FMC->CMR2 &= ~FMC_CMR_PG;
            }
        }

        /* Return the FMC state */
        return temp_state;
    } else {

        FMC_State temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

        if (temp_state == FMC_READY) {
            /* Set the PG bit to start program */
            FMC->CMR |= FMC_CMR_PG;

            *(__IO uint32_t *)Address = Data;

            /* Wait for the FMC ready */
            temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

            /* Reset the PG bit */
            FMC->CMR &= ~FMC_CMR_PG;
        }

        /* Return the FMC state */
        return temp_state;

    }

}

/**
  * @}
  */

/** @defgroup FMC_Group2 Option Bytes Programming functions
 *  @brief    Option Bytes Programming functions
 *
@verbatim
 ===============================================================================
                ##### Option Bytes Programming functions #####
 ===============================================================================

    [..] The FMC_Option Bytes Programming_functions, includes the following functions:
       (+) void FMC_OB_Unlock(void);
       (+) void FMC_OB_Lock(void);
       (+) void FMC_OB_Reset(void);
       (+) FMC_State FMC_OB_Erase(void);
       (+) FMC_State FMC_OB_WRPConfig(uint32_t OB_WRP);
       (+) FMC_State FMC_OB_RDPConfig(uint8_t OB_RDP);
       (+) FMC_State FMC_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_DEEPSLEEP, uint8_t OB_STDBY);
       (+) FMC_State FMC_OB_BOOTConfig(uint8_t OB_BOOT);
       (+) FMC_State FMC_OB_WriteUser(uint8_t OB_USER);
       (+) FMC_ProgramOptionByteData(uint32_t Address, uint8_t Data);
       (+) uint8_t FMC_OB_GetUser(void);
       (+) uint32_t FMC_OB_GetWRP(void);
       (+) FlagStatus FMC_OB_GetRDP(void);
    [..] Any operation of erase or program should follow these steps:

   (#) Call the FMC_OB_Unlock() function to enable the Option Bytes registers access

   (#) Call one or several functions to program the desired option bytes
      (++) FMC_State FMC_OB_RDPConfig(uint8_t OB_RDP) => to set the desired read Protection Level
      (++) FMC_State FMC_OB_WRPConfig(uint32_t OB_WRP, FunctionalState NewState)
           => to Enable/Disable the desired sector write protection
      (++) FMC_State FMC_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_DEEPSLEEP, uint8_t OB_STDBY)
           => to configure the user option Bytes: IWDG, DEEPSLEEP and the Standby.
      (++) FMC_State FMC_OB_BOOTConfig(uint8_t OB_BOOT1)
           => to set or reset BOOT1
      (++) FMC_State FMC_OB_VDDAConfig(uint8_t OB_VDDA_ANALOG)
           => to enable or disable the VDDA Analog Monitoring
      (++) You can write all User Options bytes at once using a single function
           by calling FMC_State FMC_OB_WriteUser(uint8_t OB_USER)
      (++) FMC_ProgramOptionByteData(uint32_t Address, uint8_t Data) to program the
           two half word in the option bytes

   (#) Once all needed option bytes to be programmed are correctly written, call the
      FMC_OB_Launch(void) function to launch the Option Bytes programming process.

   (#) Call the FMC_OB_Lock() to disable the Option Bytes registers access (recommended
      to protect the option Bytes against possible unwanted operations)

@endverbatim
  * @{
  */

/**
  * @brief  Unlock the option byte operation
  * @param  None
  * @retval None
  */
void FMC_OB_Unlock(void)
{
    if ((FMC->CMR & FMC_CMR_OBWE) == RESET) {
        /* Write the FMC key */
        FMC->OBKEYR = FMC_KEY1;
        FMC->OBKEYR = FMC_KEY2;
    }
}

/**
  * @brief  Lock the option byte operation.
  * @param  None
  * @retval None
  */
void FMC_OB_Lock(void)
{
    /* Reset the OBWE bit */
    FMC->CMR &= ~FMC_CMR_OBWE;
}

/**
  * @brief  Generate a system reset to reload the option byte.
  * @param  None
  * @retval None
  */
void FMC_OB_Reset(void)
{
    /* Set the OPTR bit */
    FMC->CMR |= FMC_CMR_OPTR;
}

/**
  * @brief  Erase the FMC option byte.
  * @param  None
  * @retval FMC state: FMC_READY, FMC_BSY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */
FMC_State FMC_OB_Erase(void)
{
    uint16_t temp_rdp = RDP_LEVEL_0;

    FMC_State temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

    /* Check the ReadOut Protection Option Byte */
    if (FMC_OB_GetRDP() != RESET) {
        temp_rdp = 0x00;
    }

    if (temp_state == FMC_READY) {
        /* Start erase the option byte */
        FMC->CMR |= FMC_CMR_OBER;
        FMC->CMR |= FMC_CMR_START;

        /* Wait for the FMC ready */
        temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

        if (temp_state == FMC_READY) {
            /* Reset the OPER bit */
            FMC->CMR &= ~FMC_CMR_OBER;

            /* Set the OBPG bit */
            FMC->CMR |= FMC_CMR_OBPG;

            /* Set default RDP level */
            OB->RDP = (uint16_t)temp_rdp;

            /* Wait for the FMC ready */
            temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

            if (temp_state != FMC_TIMEOUT_ERR) {
                /* Reset the OBPG bit */
                FMC->CMR &= ~FMC_CMR_OBPG;
            }
        } else {
            if (temp_state != FMC_TIMEOUT_ERR) {
                /* Reset the OBPG bit */
                FMC->CMR &= ~FMC_CMR_OBPG;
            }
        }
    }
    /* Return the FMC state */
    return temp_state;
}

/**
  * @brief  Program Write protect Byte
  * @param  OB_WRP: specify the address of the pages to be write protected.
  *   The legal parameter can be:
  *     @arg WRP_SECTOR0 ... WRP_SECTOR31
  *     @arg WRP_ALLSECTORS
  * @retval FMC state: FMC_READY, FMC_BSY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */
FMC_State FMC_OB_EnableWRP(uint32_t OB_WRP)
{
    uint16_t temp_WRP0, temp_WRP1, temp_WRP2, temp_WRP3;

    FMC_State temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

    OB_WRP = (uint32_t)(~OB_WRP);
    temp_WRP0 = (uint16_t)(OB_WRP & OB_WRP0_WRP0);
    temp_WRP1 = (uint16_t)((OB_WRP & OB_WRP0_nWRP0) >> 8);
    temp_WRP2 = (uint16_t)((OB_WRP & OB_WRP1_WRP1) >> 16);
    temp_WRP3 = (uint16_t)((OB_WRP & OB_WRP1_nWRP1) >> 24);

    if (temp_state == FMC_READY) {
        FMC->OBKEYR = FMC_KEY1;
        FMC->OBKEYR = FMC_KEY2;
        /* Set the OBPG bit*/
        FMC->CMR |= FMC_CMR_OBPG;

        if (temp_WRP0 != 0xFF) {
            OB->WRP0 = temp_WRP0;

            /* Wait for the FMC ready */
            temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);
        }
        if ((temp_state == FMC_READY) && (temp_WRP1 != 0xFF)) {
            OB->WRP1 = temp_WRP1;

            /* Wait for the FMC ready */
            temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);
        }
        if ((temp_state == FMC_READY) && (temp_WRP2 != 0xFF)) {
            OB->WRP2 = temp_WRP2;

            /* Wait for the FMC ready */
            temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);
        }
        if ((temp_state == FMC_READY) && (temp_WRP3 != 0xFF)) {
            OB->WRP3 = temp_WRP3;

            /* Wait for the FMC ready */
            temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);
        }
        if (temp_state != FMC_TIMEOUT_ERR) {
            /* Reset the OBPG bit */
            FMC->CMR &= ~FMC_CMR_OBPG;
        }
    }
    /* Return the FMC state */
    return temp_state;
}

/**
  * @brief  Enable or disable the read out protection,this function erases all option bytes.
  * @param  NewValue: ENABLE or DISABLE.
  * @retval FMC state: FMC_READY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */
FMC_State FMC_ReadOutProtection(TypeState NewValue)
{
    FMC_State temp_state = FMC_READY;
    /* Wait for the FMC ready */
    temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);
    if (temp_state == FMC_READY) {
        /* Unlock option bytes */
        FMC->OBKEYR = FMC_KEY1;
        FMC->OBKEYR = FMC_KEY2;
        while ((FMC->CMR & FMC_CMR_OBWE) != FMC_CMR_OBWE)
        {}
        FMC->CMR |= FMC_CMR_OBER;
        FMC->CMR |= FMC_CMR_START;
        /* Wait for the FMC ready */
        temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);
        if (temp_state == FMC_READY) {
            /* Disable the OBER Bit */
            FMC->CMR &= ~FMC_CMR_OBER ;
            /* Enable the OBPG Bit */
            FMC->CMR |= FMC_CMR_OBPG;
            if (NewValue != DISABLE) {
                OB->RDP = 0x00;
            } else {
                OB->RDP = RDP_LEVEL_0;
            }
            /* Wait for the FMC ready */
            temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

            if (temp_state != FMC_TIMEOUT_ERR) {
                /* Enable the OBPG Bit */
                FMC->CMR &= ~FMC_CMR_OBPG ;
            }
        } else {
            if (temp_state != FMC_TIMEOUT_ERR) {
                /* Disable the OBER Bit */
                FMC->CMR &= ~FMC_CMR_OBER ;
            }
        }
    }
    /* Return the FMC state */
    return temp_state;
}

/**
  * @brief  Config the Read Out Protection bit.
  * @param  FMC_ReadProtection_Level: The Read Out Protection level.
  *   This parameter can be:
  *     @arg RDP_LEVEL_0: No protection
  *     @arg RDP_LEVEL_1: Read Outprotection of the memory
  * @retval FMC state: FMC_READY, FMC_BSY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */
FMC_State FMC_OB_RDPConfig(uint8_t OB_RDP)
{
    FMC_State temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

    if (temp_state == FMC_READY) {
        FMC->CMR |= FMC_CMR_OBER;
        FMC->CMR |= FMC_CMR_START;

        /* Wait for the FMC ready */
        temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

        if (temp_state == FMC_READY) {
            /* Reset the OBER bit */
            FMC->CMR &= ~FMC_CMR_OBER;

            /* Start the Option Bytes Programming */
            FMC->CMR |= FMC_CMR_OBPG;

            OB->RDP = OB_RDP;

            /* Wait for the FMC ready */
            temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

            if (temp_state != FMC_TIMEOUT_ERR) {
                /* Reset the OBPG bit */
                FMC->CMR &= ~FMC_CMR_OBPG;
            }
        } else {
            if (temp_state != FMC_TIMEOUT_ERR) {
                /* Reset the OBER Bit */
                FMC->CMR &= ~FMC_CMR_OBER;
            }
        }
    }
    /* Return the FMC state */
    return temp_state;
}

/**
  * @brief  Program the FMC User Option Byte: IWDG_SW / RST_DEEPSLEEP / RST_STDBY.
  * @param  OB_IWDG: Config the WDG mode
  *     @arg OB_IWDG_SW: Software WDG selected
  *     @arg OB_IWDG_HW: Hardware WDG selected
  * @param  OB_DEEPSLEEP: Config Reset event when entering DEEPSLEEP mode.
  *     @arg OB_DEEPSLEEP_NORST: No reset generated when entering in DEEPSLEEP
  *     @arg OB_DEEPSLEEP_RST: Reset generated when entering in DEEPSLEEP
  * @param  OB_STDBY: Config Reset event when entering Standby mode.
  *     @arg OB_STDBY_NORST: No reset generated when entering in STANDBY
  *     @arg OB_STDBY_RST: Reset generated when entering in STANDBY
  * @retval FMC state: FMC_READY, FMC_BSY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */
FMC_State  FMC_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_DEEPSLEEP, uint8_t OB_STDBY)
{
    FMC_State temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

    if (temp_state == FMC_READY) {
        /* Set the OBPG bit*/
        FMC->CMR |= FMC_CMR_OBPG;

        OB->USER = (uint16_t)((uint16_t)(OB_IWDG | OB_DEEPSLEEP) | (uint16_t)(OB_STDBY | 0xF8));

        /* Wait for the FMC ready */
        temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

        if (temp_state != FMC_TIMEOUT_ERR) {
            /* Reset the OBPG bit */
            FMC->CMR &= ~FMC_CMR_OBPG;
        }
    }
    /* Return the FMC state */
    return temp_state;
}

/**
  * @brief  Program the BOOT option bit.
  * @param  OB_BOOT: The legal parameter can be one of the following value:
  *     @arg OB_BOOT_B1:Start up from Bank1
  *     @arg OB_BOOT_B2:Start up from Bank2
  * @retval FMC state: FMC_READY, FMC_BSY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */
FMC_State FMC_OB_BOOTConfig(uint8_t OB_BOOT)
{
    FMC_State temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);
    FMC->OBKEYR = FMC_KEY1;
    FMC->OBKEYR = FMC_KEY2;

    if (temp_state == FMC_READY) {
        /* Set the OBPG bit*/
        FMC->CMR |= FMC_CMR_OBPG;

        if (OB_BOOT == OB_BOOT_B1) {
            OB->USER |= OB_USER_BFB2;
        } else {
            OB->USER &= (uint16_t)(~(uint16_t)(OB_USER_BFB2));
        }

        /* Wait for the FMC ready */
        temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

        if (temp_state != FMC_TIMEOUT_ERR) {
            /* Reset the OBPG bit */
            FMC->CMR &= ~FMC_CMR_OBPG;
        }
    }
    /* Return the FMC state */
    return temp_state;
}

/**
  * @brief  Program the FMC User Option Byte.
  * @param  OB_USER: Select all user option byte
  *   The legal parameter is one of the following values:
  *     @arg OB_IWDG_SW
  *     @arg OB_IWDG_HW
  *     @arg OB_DEEPSLEEP_NORST
  *     @arg OB_DEEPSLEEP_RST
  *     @arg OB_STDBY_NORST
  *     @arg OB_STDBY_RST
  *     @arg OB_BOOT_B1
  *     @arg OB_BOOT_B2
  * @retval FMC state: FMC_READY, FMC_BSY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */
FMC_State FMC_OB_WriteUser(uint8_t OB_USER)
{
    FMC_State temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

    if (temp_state == FMC_READY) {
        /* Set the OBPG bit */
        FMC->CMR |= FMC_CMR_OBPG;

        OB->USER = OB_USER | 0xf0;

        /* Wait for the FMC ready */
        temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

        if (temp_state != FMC_TIMEOUT_ERR) {
            /* Reset the OBPG bit */
            FMC->CMR &= ~FMC_CMR_OBPG;
        }
    }
    /* Return the FMC state */
    return temp_state;
}

/**
  * @brief  Program Option Byte Data.
  * @param  Address: The Option Byte address to be programmed.
  *   The legal parameter can be 0x1FFFF804 or 0x1FFFF806.
  * @param  Data: The Byte to be programmed.
  * @retval FMC state: FMC_READY, FMC_BSY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */
FMC_State FMC_ProgramOptionByteData(uint32_t Address, uint8_t Data)
{
    FMC_State temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

    if (temp_state == FMC_READY) {
        /* SET the OPTPG bit */
        FMC->CMR |= FMC_CMR_OBPG;
        *(__IO uint16_t *)Address = Data;

        /* Wait for the FMC ready */
        temp_state = FMC_WaitReady(FMC_TIMEOUT_COUNT);

        if (temp_state != FMC_TIMEOUT_ERR) {
            /* Reset the OPTPG bit */
            FMC->CMR &= ~FMC_CMR_OBPG;
        }
    }
    /* Return the FMC state */
    return temp_state;
}

/**
  * @brief  Get the FMC User Option Byte.
  * @param  None
  * @retval The FMC User Option Byte.
  */
uint8_t FMC_OB_GetUser(void)
{
    return (uint8_t)(FMC->OPTR >> 8);
}

/**
  * @brief  Get the FMC Write Protection Option Byte.
  * @param  None
  * @retval The FMC Write Protection Option Byte
  */
uint32_t FMC_OB_GetWRP(void)
{
    return (uint32_t)(FMC->WPR);
}

/**
  * @brief  Check whether the FMC Read out Protection Status is SET or RESET.
  * @param  None
  * @retval FMC ReadOut Protection state
  */
TypeState FMC_OB_GetRDP(void)
{
    TypeState RDPState = RESET;

    if ((uint8_t)(FMC->OPTR & (FMC_OPTR_PLEVEL1)) != RESET) {
        RDPState = SET;
    } else {
        RDPState = RESET;
    }
    return RDPState;
}

/**
  * @}
  */

/** @defgroup FMC_Group3 Interrupts and flags management functions
 *  @brief    Interrupts and flags management functions
 *
@verbatim
 ===============================================================================
             ##### Interrupts and flags management functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Enable or disable the corresponding FMC interrupt source.
  * @param  FMC_INT: The FMC interrupt source to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg FMC_INT_EOP: FMC end of programming Interrupt
  *     @arg FMC_INT_ERR: FMC Error Interrupt
  *     @arg FMC_INT_B2_EOP: FMC end of programming Interrupt
  *     @arg FMC_INT_B2_ERR: FMC Error Interrupt
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void FMC_INTConfig(uint32_t FMC_INT, TypeState NewValue)
{

    if (FMC_SIZE > FMC_BANK1_SIZE) {
        if ((FMC_INT & 0x80000000) != 0x0) {
            if (NewValue != DISABLE) {
                /* Enable the interrupt sources */
                FMC->CMR2 |= (FMC_INT & 0x7fffffff);
            } else {
                /* Disable the interrupt sources */
                FMC->CMR2 &= ~(uint32_t)(FMC_INT & 0x7fffffff);
            }
        } else {
            if (NewValue != DISABLE) {
                /* Enable the interrupt sources */
                FMC->CMR |= FMC_INT;
            } else {
                /* Disable the interrupt sources */
                FMC->CMR &= ~(uint32_t)FMC_INT;
            }
        }
    } else {
        if (NewValue != DISABLE) {
            /* Enable the interrupt sources */
            FMC->CMR |= FMC_INT;
        } else {
            /* Disable the interrupt sources */
            FMC->CMR &= ~(uint32_t)FMC_INT;
        }
    }
}

/**
  * @brief  Checks whether the FMC flag is SET or RESET.
  * @param  FMC_FLAG: the corresponding FMC flag.
  *   the legal parameter can be:
  *     @arg FMC_FLAG_BSY:  FMC BUSY flag
  *     @arg FMC_FLAG_PERR: FMC Programming error flag flag
  *     @arg FMC_FLAG_WERR: FMC Write protection error flag
  *     @arg FMC_FLAG_EOP:  FMC End of Programming flag
  *     @arg FMC_FLAG_OPTER: FMC option byte error flag
  * @retval The state of the FMC flag.
  */
TypeState FMC_GetBitState(uint32_t FMC_FLAG)
{
    if (FMC_SIZE > FMC_BANK1_SIZE) {
        /* Check the parameters */
        if (FMC_FLAG == FMC_FLAG_OPTERR) {
            if ((FMC->OPTR & FMC_FLAG_OPTERR) != (uint32_t)RESET) {
                return SET;
            } else {
                return RESET;
            }
        } else {
            if ((FMC_FLAG & 0x80000000) != 0x0) {
                if ((FMC->CSR2 & FMC_FLAG) != (uint32_t)RESET) {
                    return SET;
                } else {
                    return RESET;
                }
            } else {
                if ((FMC->CSR & FMC_FLAG) != (uint32_t)RESET) {
                    return SET;
                } else {
                    return RESET;
                }
            }
        }
    } else {
        if (FMC_FLAG == FMC_FLAG_OPTERR) {
            if ((FMC->OPTR & FMC_FLAG_OPTERR) != (uint32_t)RESET) {
                return SET;
            } else {
                return RESET;
            }
        } else {
            if ((FMC->CSR & FMC_FLAG) != (uint32_t)RESET) {
                return  SET;
            }
            /* Return the state of corresponding FMC flag */
            else {
                return RESET;
            }
        }
    }
}

/**
  * @brief  Clear the FMC pending flag.
  * @param  FMC_FLAG: clear the corresponding FMC flag.
  *     @arg FMC_FLAG_PERR: Programming error flag flag
  *     @arg FMC_FLAG_WERR: Write protection error flag
  *     @arg FMC_FLAG_EOP:  End of Programming flag
  * @retval None
  */
void FMC_ClearBitState(uint32_t FMC_FLAG)
{
    if (FMC_SIZE > FMC_BANK1_SIZE) {
        if ((FMC_FLAG & 0x80000000) != 0x0) {
            /* Clear the flags */
            FMC->CSR2 = FMC_FLAG;
        } else {
            /* Clear the flags */
            FMC->CSR = FMC_FLAG;
        }
    } else {
        FMC->CSR = FMC_FLAG;
    }
}

/**
  * @brief  Return the FMC state.
  * @param  None
  * @retval FMC state: FMC_READY,  FMC_BSY,  FMC_WRPERR, or FMC_PGERR
  */
FMC_State FMC_GetState(void)
{
    FMC_State temp_state = FMC_READY;

    if ((FMC->CSR & FMC_CSR_BUSY) == FMC_CSR_BUSY) {
        temp_state = FMC_BSY;
    } else {
        if ((FMC->CSR & (uint32_t)FMC_CSR_WPEF) != (uint32_t)0x00) {
            temp_state = FMC_WRPERR;
        } else {
            if ((FMC->CSR & (uint32_t)(FMC_CSR_PGEF)) != (uint32_t)0x00) {
                temp_state = FMC_PGERR;
            } else {
                temp_state = FMC_READY;
            }
        }
    }

    /* Return the FMC state */
    return temp_state;
}

/**
  * @brief  Return the FMC bak1 state.
  * @param  None
  * @retval FMC state: FMC_READY,  FMC_BSY,  FMC_WRPERR, or FMC_PGERR
  */
FMC_State FMC_GetB1State(void)
{
    FMC_State temp_state = FMC_READY;

    if ((FMC->CSR & FMC_CSR_BUSY) == FMC_CSR_BUSY) {
        temp_state = FMC_BSY;
    } else {
        if ((FMC->CSR & (uint32_t)FMC_CSR_WPEF) != (uint32_t)0x00) {
            temp_state = FMC_WRPERR;
        } else {
            if ((FMC->CSR & (uint32_t)(FMC_CSR_PGEF)) != (uint32_t)0x00) {
                temp_state = FMC_PGERR;
            } else {
                temp_state = FMC_READY;
            }
        }
    }
    return temp_state;
}

/**
  * @brief  Return the FMC bak2 state.
  * @param  None
  * @retval FMC state: FMC_READY,  FMC_BSY,  FMC_WRPERR, or FMC_PGERR
  */

FMC_State FMC_GetB2State(void)
{

    FMC_State temp_state = FMC_READY;

    if ((FMC->CSR2 & FMC_CSR2_BUSY & 0x7fffffff) == (FMC_CSR2_BUSY & 0x7fffffff)) {
        temp_state = FMC_BSY;
    } else {
        if ((FMC->CSR2 & FMC_CSR2_WPEF & 0x7fffffff) != (uint32_t)0x00) {
            temp_state = FMC_WRPERR;
        } else {
            if ((FMC->CSR2 & FMC_CSR2_PGEF & 0x7fffffff) != (uint32_t)0x00) {
                temp_state = FMC_PGERR;
            } else {
                temp_state = FMC_READY;
            }
        }
    }

    /* Return the FMC state */
    return temp_state;
}


/**
  * @brief  Check whether FMC is ready or not.
  * @param  Timeout: Count of loop
  * @retval FMC state: FMC_READY, FMC_BSY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */
FMC_State FMC_WaitReady(uint32_t uCount)
{
    FMC_State temp_state = FMC_BSY;

    /* Wait for FMC ready */
    do {
        /* Get FMC state */
        temp_state = FMC_GetState();
        uCount--;
    } while ((temp_state == FMC_BSY) && (uCount != 0x00));

    if (temp_state == FMC_BSY) {
        temp_state = FMC_TIMEOUT_ERR;
    }
    /* Return the FMC state */
    return temp_state;
}

/**
  * @brief  Check whether FMC Bank1 is ready or not.
  * @param  Timeout: Count of loop
  * @retval FMC state: FMC_READY, FMC_BSY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */
FMC_State FMC_B1_WaitReady(uint32_t uCount)
{
    FMC_State temp_state = FMC_BSY;

    /* Wait for FMC ready */
    do {
        /* Get FMC state */
        temp_state = FMC_GetB1State();
        uCount--;
    } while ((temp_state == FMC_BSY) && (uCount != 0x00));

    if (temp_state == FMC_BSY) {
        temp_state = FMC_TIMEOUT_ERR;
    }
    /* Return the FMC state */
    return temp_state;
}

/**
  * @brief  Check whether FMC Bank2 is ready or not.
  * @param  Timeout: Count of loop
  * @retval FMC state: FMC_READY, FMC_BSY, FMC_WRPERR, FMC_PGERR or FMC_TIMEOUT_ERR.
  */

FMC_State FMC_B2_WaitReady(uint32_t uCount)
{
    FMC_State temp_state = FMC_BSY;

    /* Wait for FMC ready */
    do {
        /* Get FMC state */
        temp_state = FMC_GetB2State();
        uCount--;
    } while ((temp_state == (FMC_BSY && 0x7FFFFFFF)) && (uCount != 0x00));

    if (temp_state == FMC_BSY) {
        temp_state = FMC_TIMEOUT_ERR;
    }
    /* Return the FMC state */
    return temp_state;
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
