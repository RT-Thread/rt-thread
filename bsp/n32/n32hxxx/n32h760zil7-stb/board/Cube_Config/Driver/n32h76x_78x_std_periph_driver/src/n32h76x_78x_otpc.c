/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_otpc.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_otpc.h"

/**
*\*\name    OTPC_Unlock.
*\*\fun     This function Unlock the CTRL Register.
*\*\param   none
*\*\return  none
**/
void OTPC_Unlock(void)
{
    /* Unlock the OTPC_CTRL */
    OTPC->KEY = OTPC_KEY1;
    OTPC->KEY = OTPC_KEY2;
}

/**
*\*\name    OTPC_Lock.
*\*\fun     This function Lock the CTRL Register.
*\*\param   none
*\*\return  none
**/
void OTPC_Lock(void)
{
    /* Lock the OTPC_CTRL */
    OTPC->CTRL |= OTPC_CMD_LOCK;
}

/**
*\*\name    OTPC_GetLockStatus.
*\*\fun     This function return the Unlock status.
*\*\param   none
*\*\return  FlagStatus:
*\*\        SET     OTPC_CTRL is Locked
*\*\        RESET   OTPC_CTRL is Unlock
**/
FlagStatus OTPC_GetLockStatus(void)
{
    FlagStatus bitstatus;

    /* Return the Lock status */
    if ((OTPC->CTRL & OTPC_CMD_LOCK) == OTPC_CMD_LOCK)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}
/**
*\*\name    OTPC_SetUsCount.
*\*\fun     This function Sets the us Conter.
*\*\param   us_count : 0x00000000 - 0x000001FF
*\*\return  none
**/
void OTPC_SetUsCount(uint32_t us_count)
{
    /* Set the us Counter */
    OTPC->USC = (OTPC_USC_MASK &  us_count);
}
/**
*\*\name    OTPC_GetFlagStatus.
*\*\fun     This function return the Flag status.
*\*\param   optc_flag
*\*\            - OTPC_FLAG_BE          Busy Error Flag
*\*\            - OTPC_FLAG_OORE        Read / Write out of Range Error Flag
*\*\            - OTPC_FLAG_RDPE        Read Protection Error Flag
*\*\            - OTPC_FLAG_WRPE        Write Protection Error Flag
*\*\            - OTPC_FLAG_PGE         Program Error Flag
*\*\            - OTPC_FLAG_KEYE        Key Error Flag
*\*\            - OTPC_FLAG_BUSY        Busy Flag
*\*\return  FlagStatus
*\*\          - SET
*\*\          - RESET
**/
FlagStatus OTPC_GetFlagStatus(uint32_t optc_flag)
{
    FlagStatus bitstatus;

    if ((OTPC->STS & optc_flag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name    OTPC_ClearFlag.
*\*\fun     This function Clear the Flag status.
*\*\param   optc_flag
*\*\            - OTPC_FLAG_BE          Busy Error Flag
*\*\            - OTPC_FLAG_OORE        Read / Write out of Range Error Flag
*\*\            - OTPC_FLAG_RDPE        Read Protection Error Flag
*\*\            - OTPC_FLAG_WRPE        Write Protection Error Flag
*\*\            - OTPC_FLAG_PGE         Program Error Flag
*\*\return  none
**/
void OTPC_ClearFlag(uint32_t optc_flag)
{
    /* Write 1 Clear the Flags */
    OTPC->STS = optc_flag;
}

/**
*\*\name    OTPC_ConfigInterrupt.
*\*\fun     This function Enable the OTPC Interrupt.
*\*\param   otpc_int:
*\*\            - OTPC_INT_BE          Busy Error Interrupt Enable
*\*\            - OTPC_INT_OORE        Read / Write out of Range Error Interrupt Enable
*\*\            - OTPC_INT_RDPE        Read Protection Error Interrupt Enable
*\*\            - OTPC_INT_WRPE        Write Protection Error Interrupt Enable
*\*\            - OTPC_INT_PGE         Program Error Interrupt Enable
*\*\        FunctionalState:
*\*\            - ENABLE
*\*\            - DISABLE
*\*\return  none
**/
void OTPC_ConfigInterrupt(uint32_t otpc_int, FunctionalState cmd)
{
    if(cmd == ENABLE)
    {
        OTPC->CTRL |= otpc_int;
    }
    else
    {
        OTPC->CTRL &= (~otpc_int);
    }
}

/**
*\*\name    OTPC_ClearFlag.
*\*\fun     This function Check the Error Flag.
*\*\param   none
*\*\return  FlagStatus
*\*\            - RESET               No Error Occur
*\*\            - SET                 Has Error Occur
**/
FlagStatus OTPC_CheckError(void)
{
    FlagStatus bitstatus;

    /* Check the Error Flag */
    if((OTPC->STS & OTPC_ALLERROR_STS) == RESET)
    {
        bitstatus = RESET;
    }
    else
    {
        /* Has Error Occur */
        bitstatus = SET;
    }

    return bitstatus;
}

/**
*\*\name    OTPC_WaitForLastOperation.
*\*\fun     This function Wait For the Last Operation is Complete.
*\*\param   none
*\*\return  OTPC_STS
*\*\            - OTPC_ERR_TIMEOUT              Last Operation TimeOut Error Occur
*\*\            - OTPC_COMPLETE                 Last Operation Complete without any Errors
*\*\            - OTPC_UNCOMPLETE               Last Operation has Error Occur
**/
OTPC_STS OTPC_WaitForLastOperation(void)
{
    FlagStatus flag_status = SET;
    OTPC_STS   status_temp;
    uint32_t time_out = OTPC_TIME_OUT;

    while((flag_status != RESET) && (time_out != 0))
    {
        /* Get Busy Flag */
        flag_status = OTPC_GetFlagStatus(OTPC_FLAG_BUSY);
        time_out--;
    }

    if(time_out == 0)
    {
        status_temp = OTPC_ERR_TIMEOUT;
    }
    else if(OTPC_CheckError() == SET)
    {
        status_temp = OTPC_UNCOMPLETE;
    }
    else
    {
        status_temp = OTPC_COMPLETE;
    }

    return status_temp;
}

/**
*\*\name    OTPC_WriteEnable.
*\*\fun     This function Enable the OTPC Operation as Write.
*\*\param   none
*\*\return  none
**/
void OTPC_WriteEnable(void)
{
    OTPC->CTRL |= OTPC_CMD_WRITE;
}

/**
*\*\name    OTPC_ReadEnable.
*\*\fun     This function Enable the OTPC Operation as Read.
*\*\param   none
*\*\return  none
**/
void OTPC_ReadEnable(void)
{
    OTPC->CTRL &= OTPC_CMD_READ;
}

/**
*\*\name    OTPC_ConfigAddr.
*\*\fun     This function Set the Operate Address.
*\*\param   addr : 0x00000500 - 0x000005FF
*\*\return  none
**/
void OTPC_SetAddr(uint32_t addr)
{
    OTPC->ADDR = addr;
}

/**
*\*\name    OTPC_SetWriteData.
*\*\fun     This function Set the Write data.
*\*\param   data : The data need to be Programed
*\*\return  none
**/
void OTPC_SetWriteData(uint32_t data)
{
    OTPC->WDATA = data;
}

/**
*\*\name    OTPC_ProgramWord.
*\*\fun     This function Program data at addr.
*\*\param   addr : 0x00000500 - 0x000005FF
*\*\        data : The data need to be Programed
*\*\return  OTPC_STS
*\*\            - OTPC_ERR_TIMEOUT              Last Operation TimeOut Error Occur
*\*\            - OTPC_COMPLETE                 Last Operation Complete without any Error
*\*\            - OTPC_UNCOMPLETE               Last Operation has Error Occur
*\*\note    During the write operation, NRST cannot be reset
**/
OTPC_STS OTPC_ProgramWord(uint32_t addr, uint32_t data)
{
    OTPC_STS otpc_status;
    OTPC_ClearFlag(OTPC_ERROR_STS);
    /* Get Last Operation Status */
    otpc_status = OTPC_WaitForLastOperation();

    /* Last Operation Not Complete and Errors Occur */
    if(otpc_status == OTPC_COMPLETE)
    {
        OTPC_WriteEnable();
        OTPC_SetWriteData(data);
        OTPC_SetAddr(addr);
        /* Get Last Operation Status */
        otpc_status = OTPC_WaitForLastOperation();
    }

    return otpc_status;
}

/**
*\*\name    OTPC_ReadWord.
*\*\fun     This function Read data at addr.
*\*\param   addr : 0x00000300 - 0x000003CF,0x00000500 - 0x000005FF
*\*\        *data : The Point of the data need to be Read;
*\*\return  OTPC_STS
*\*\            - OTPC_ERR_TIMEOUT              Last Operation TimeOut Error Occur
*\*\            - OTPC_COMPLETE                 Last Operation Complete without any Error
*\*\            - OTPC_UNCOMPLETE               Last Operation has Error Occur
**/
OTPC_STS OTPC_ReadWord(uint32_t addr, uint32_t *data)
{
    /* Get Last Operation Status */
    OTPC_STS otpc_status = OTPC_WaitForLastOperation();

    /* Last Operation Not Complete and Errors Occur */
    if(otpc_status != OTPC_COMPLETE)
    {
        /* no process */
    }
    else
    {
        OTPC_ReadEnable();
        OTPC_SetAddr(addr);
        otpc_status = OTPC_WaitForLastOperation();
    }

    if(otpc_status != OTPC_COMPLETE)
    {
        /* no process */
    }
    else
    {
        *data = OTPC->RDATA;
    }

    return otpc_status;
}

/**
*\*\name    OTPC_GetUserCfgVaildNum.
*\*\fun     This function Check the 16 Copies region is programble.
*\*\param   ConfigUser
*\*\            - OTPC_SEC_JTAG_REG
*\*\            - OTPC_SEC_MODE_REG
*\*\            - OTPC_RDP2_REG
*\*\            - OTPC_BTM_REG
*\*\            - OTPC_BOR_REG
*\*\            - OTPC_IWDG_REG
*\*\            - OTPC_TCM_SIZE_REG
*\*\            - OTPC_JTAG_KEY_REG
*\*\            - OTPC_REK_UNIT1_REG
*\*\            - OTPC_REK_UNIT2_REG
*\*\            - OTPC_REK_UNIT3_REG
*\*\            - OTPC_REK_UNIT4_REG
*\*\            - OTPC_IDK_UNIT1_REG
*\*\            - OTPC_IDK_UNIT2_REG
*\*\            - OTPC_IDK_UNIT3_REG
*\*\            - OTPC_IDK_UNIT4_REG
*\*\return  value_temp : The quantity containing 1 in the lower 16 bits indicates the remaining programmable quantity
**/
uint32_t OTPC_GetUserCfgVaildNum(uint32_t ConfigUser)
{
    uint32_t value_temp;
    value_temp = *(uint32_t*)(OTPC_BASE + ConfigUser);
    value_temp &= OTPC_VARIOUS_REG_MASK;
    return value_temp;
}

/**
*\*\name    OTPC_CheckUserMemoryUnused.
*\*\fun     This function Check the User Memory Unused region is programble.
*\*\param   addr : 0x0500 ~ 0x05FF
*\*\return  FlagStatus :
*\*\            - SET           The Check Address is Programble
*\*\            - RESET         The Check Address is not Programble
**/
FlagStatus OTPC_CheckUserMemoryUnused(uint32_t addr)
{
    FlagStatus value_stauts;
    uint32_t base_addr;
    uint32_t vaild_bit;

    /* Get the register address corresponding to the address FLAG */
    base_addr = OTPC_BASE + OTPC_UMUU_BASE_REG + (((addr - OTPC_UNUSE_STARTADDRESS) / OTPC_UNUSE_PAGESIZE) * 4U);
    /* Get the register bit corresponding to the address FLAG */
    vaild_bit = (addr - OTPC_UNUSE_STARTADDRESS) % OTPC_UNUSE_PAGESIZE;

    if(((*(uint32_t*)base_addr) & (0x01UL << vaild_bit)) == RESET)
    {
        value_stauts = RESET;
    }
    else
    {
        value_stauts = SET;
    }

    return value_stauts;
}


/**
*\*\name    OTPC_GetReload.
*\*\fun     This function Return the OTPC_CFG_RELOAD Values.
*\*\param   DBGReloadValue pointer to an OTPC_DBGReloadValue structure.
*\*\          - NRST_IWDG_OTPValue
*\*\               - bit13: nRST_STOP_C_M7; When entering STOP0/STOP2 mode, the system will automatically reset
*\*\                       - 0: Reset
*\*\                       - 1: No reset
*\*\               - bit12: nRST_STOP_C_M4; When entering STOP0/STOP2 mode, the system will automatically reset
*\*\                       - 0: Reset
*\*\                       - 1: No reset
*\*\               - bit11: nRST_STDBY_C_M7; When entering Standby mode, the system will automatically reset
*\*\                       - 0: Reset
*\*\                       - 1: No reset
*\*\               - bit10: nRST_STDBY_C_M4; When entering Standby mode, the system will automatically reset
*\*\                       - 0: Reset
*\*\                       - 1: No reset
*\*\               - bit9 : IWDG_SW_M7; iwdg control selection
*\*\                       - 0: hardware
*\*\                       - 1: software
*\*\               - bit8 : IWDG_SW_M4; iwdg control selection
*\*\                       - 0: hardware
*\*\                       - 1: software
*\*\               - bit7 : IWDG_STOP0_M7; IWDG's activity status in STOP0 mode
*\*\                       - 0: Freeze
*\*\                       - 1: Active
*\*\               - bit6 : IWDG_STOP0_M4; IWDG's activity status in STOP0 mode
*\*\                       - 0: Freeze
*\*\                       - 1: Active
*\*\               - bit5 : IWDG_STOP2_M7; IWDG's activity status in STOP2 mode
*\*\                       - 0: Freeze
*\*\                       - 1: Active
*\*\               - bit4 : IWDG_STOP2_M4; IWDG's activity status in STOP2 mode
*\*\                       - 0: Freeze
*\*\                       - 1: Active
*\*\               - bit3 : IWDG_STANDBY_M7; IWDG's activity status in STANDBY mode
*\*\                       - 0: Freeze
*\*\                       - 1: Active
*\*\               - bit2 : IWDG_STANDBY_M4; IWDG's activity status in STANDBY mode
*\*\                       - 0: Freeze
*\*\                       - 1: Active
*\*\               - bit1 : IWDG_SLEEP_M7; IWDG's activity status in SLEEP mode
*\*\                       - 0: Freeze
*\*\                       - 1: Active
*\*\               - bit0 : IWDG_SLEEP_M4; IWDG's activity status in SLEEP mode
*\*\                       - 0: Freeze
*\*\                       - 1: Active
*\*\          - BOR_OTPValue
*\*\               - 0x00~0x07
*\*\          - SEC_JTAG_OTPValue
*\*\               - 0x0F/0x09: JTAG/SWD Enable
*\*\               - others: JTAG/SWD Disable
*\*\          - L2MODE
*\*\               - ENABLE
*\*\               - DISABLE
*\*\          - L1MODE
*\*\               - ENABLE
*\*\               - DISABLE
*\*\          - L0MODE
*\*\               - ENABLE
*\*\               - DISABLE
*\*\          - ROOTMODE
*\*\               - ENABLE
*\*\               - DISABLE
*\*\          - INITMODE
*\*\               - ENABLE
*\*\               - DISABLE
*\*\          - TCM_SIZE_OTPValue
*\*\               - 0x00~0x3F,For detailed description, please refer to the System Security section of the User Manual, OTP Options byte
*\*\return  none
**/
void OTPC_GetReload(OTPC_DBGReloadValue* DBGReloadValue)
{
    DBGReloadValue->NRST_IWDG_OTPValue = ((OTPC->CRLD1) & OTPC_CRLD1_NRIWDG) >> OTPC_CRLD1_NRIWDG_OFFSET;
    DBGReloadValue->BOR_OTPValue = ((OTPC->CRLD1) & OTPC_CRLD1_BOR) >> OTPC_CRLD1_BOR_OFFSET;
    DBGReloadValue->SEC_JTAG_OTPValue = ((OTPC->CRLD1) & OTPC_CRLD1_SJAG);

    if((OTPC->CRLD2 & OTPC_CRLD2_L2MD) == RESET)
    {
        DBGReloadValue->L2MODE = RESET;
    }
    else
    {
        DBGReloadValue->L2MODE = SET;
    }

    if((OTPC->CRLD2 & OTPC_CRLD2_L1MD) == RESET)
    {
        DBGReloadValue->L1MODE = RESET;
    }
    else
    {
        DBGReloadValue->L1MODE = SET;
    }

    if((OTPC->CRLD2 & OTPC_CRLD2_L0MD) == RESET)
    {
        DBGReloadValue->L0MODE = RESET;
    }
    else
    {
        DBGReloadValue->L0MODE = SET;
    }

    if((OTPC->CRLD2 & OTPC_CRLD2_ROOTMD) == RESET)
    {
        DBGReloadValue->ROOTMODE = RESET;
    }
    else
    {
        DBGReloadValue->ROOTMODE = SET;
    }

    if((OTPC->CRLD2 & OTPC_CRLD2_INITMD) == RESET)
    {
        DBGReloadValue->INITMODE = RESET;
    }
    else
    {
        DBGReloadValue->INITMODE = SET;
    }

    DBGReloadValue->TCM_SIZE_OTPValue = ((OTPC->CRLD2) & OTPC_CRLD2_TCMSZ);
}

