/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g43x_flash.c
 * @author Nations
 * @version V1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32g43x_flash.h"

/** @addtogroup N32G43x_StdPeriph_Driver
 * @{
 */

/** @addtogroup FLASH
 * @brief FLASH driver modules
 * @{
 */

/** @addtogroup FLASH_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup FLASH_Private_Defines
 * @{
 */

/* Flash Access Control Register bits */
#define AC_LATENCY_MSK ((uint32_t)0x000000F8)
#define AC_PRFTBE_MSK  ((uint32_t)0xFFFFFFEF)
#define AC_ICAHEN_MSK  ((uint32_t)0xFFFFFF7F)
#define AC_LVMEN_MSK   ((uint32_t)0xFFFFFDFF)
#define AC_SLMEN_MSK   ((uint32_t)0xFFFFF7FF)

/* Flash Access Control Register bits */
#define AC_PRFTBS_MSK  ((uint32_t)0x00000020)
#define AC_ICAHRST_MSK ((uint32_t)0x00000040)
#define AC_LVMF_MSK    ((uint32_t)0x00000100)
#define AC_SLMF_MSK    ((uint32_t)0x00000400)

/* Flash Control Register bits */
#define CTRL_Set_PG       ((uint32_t)0x00000001)
#define CTRL_Reset_PG     ((uint32_t)0x00003FFE)
#define CTRL_Set_PER      ((uint32_t)0x00000002)
#define CTRL_Reset_PER    ((uint32_t)0x00003FFD)
#define CTRL_Set_MER      ((uint32_t)0x00000004)
#define CTRL_Reset_MER    ((uint32_t)0x00003FFB)
#define CTRL_Set_OPTPG    ((uint32_t)0x00000010)
#define CTRL_Reset_OPTPG  ((uint32_t)0x00003FEF)
#define CTRL_Set_OPTER    ((uint32_t)0x00000020)
#define CTRL_Reset_OPTER  ((uint32_t)0x00003FDF)
#define CTRL_Set_START    ((uint32_t)0x00000040)
#define CTRL_Set_LOCK     ((uint32_t)0x00000080)
#define CTRL_Reset_SMPSEL ((uint32_t)0x00003EFF)
#define CTRL_SMPSEL_SMP1  ((uint32_t)0x00000000)
#define CTRL_SMPSEL_SMP2  ((uint32_t)0x00000100)

/* FLASH Mask */
#define RDPRTL1_MSK  ((uint32_t)0x00000002)
#define RDPRTL2_MSK  ((uint32_t)0x80000000)
#define OBR_USER_MSK ((uint32_t)0x0000001C)
#define WRP0_MSK     ((uint32_t)0x000000FF)
#define WRP1_MSK     ((uint32_t)0x0000FF00)
#define WRP2_MSK     ((uint32_t)0x00FF0000)
#define WRP3_MSK     ((uint32_t)0xFF000000)

/* FLASH Keys */
#define L1_RDP_Key   ((uint32_t)0xFFFF00A5)
#define RDP_USER_Key ((uint32_t)0xFFF000A5)
#define L2_RDP_Key   ((uint32_t)0xFFFF33CC)
#define FLASH_KEY1   ((uint32_t)0x45670123)
#define FLASH_KEY2   ((uint32_t)0xCDEF89AB)

/* Delay definition */
#define EraseTimeout   ((uint32_t)0x000B0000)
#define ProgramTimeout ((uint32_t)0x00002000)
/**
 * @}
 */

/** @addtogroup FLASH_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup FLASH_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup FLASH_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup FLASH_Private_Functions
 * @{
 */

/**
 * @brief  Sets the code latency value.
 * @note   This function can be used for N32G43x devices.
 * @param FLASH_Latency specifies the FLASH Latency value.
 *   This parameter can be one of the following values:
 *     @arg FLASH_LATENCY_0 FLASH Zero Latency cycle
 *     @arg FLASH_LATENCY_1 FLASH One Latency cycle
 *     @arg FLASH_LATENCY_2 FLASH Two Latency cycles
 *     @arg FLASH_LATENCY_3 FLASH Three Latency cycles
 */
void FLASH_SetLatency(uint32_t FLASH_Latency)
{
    uint32_t tmpregister = 0;

    /* Check the parameters */
    assert_param(IS_FLASH_LATENCY(FLASH_Latency));

    /* Read the ACR register */
    tmpregister = FLASH->AC;

    /* Sets the Latency value */
    tmpregister &= AC_LATENCY_MSK;
    tmpregister |= FLASH_Latency;

    /* Write the ACR register */
    FLASH->AC = tmpregister;
}

/**
 * @brief  Enables or disables the Prefetch Buffer.
 * @note   This function can be used for N32G43x devices.
 * @param FLASH_PrefetchBuf specifies the Prefetch buffer status.
 *   This parameter can be one of the following values:
 *     @arg FLASH_PrefetchBuf_EN FLASH Prefetch Buffer Enable
 *     @arg FLASH_PrefetchBuf_DIS FLASH Prefetch Buffer Disable
 */
void FLASH_PrefetchBufSet(uint32_t FLASH_PrefetchBuf)
{
    /* Check the parameters */
    assert_param(IS_FLASH_PREFETCHBUF_STATE(FLASH_PrefetchBuf));

    /* Enable or disable the Prefetch Buffer */
    FLASH->AC &= AC_PRFTBE_MSK;
    FLASH->AC |= FLASH_PrefetchBuf;
}

/**
 * @brief  ICache Reset.
 * @note   This function can be used for N32G43x devices.
 */
void FLASH_iCacheRST(void)
{
    /* ICache Reset */
    FLASH->AC |= FLASH_AC_ICAHRST;
}

/**
 * @brief  Enables or disables the iCache.
 * @note   This function can be used for N32G43x devices.
 * @param FLASH_iCache specifies the iCache status.
 *   This parameter can be one of the following values:
 *     @arg FLASH_iCache_EN  FLASH iCache Enable
 *     @arg FLASH_iCache_DIS FLASH iCache Disable
 */
void FLASH_iCacheCmd(uint32_t FLASH_iCache)
{
    /* Check the parameters */
    assert_param(IS_FLASH_ICACHE_STATE(FLASH_iCache));

    /* Enable or disable the iCache */
    FLASH->AC &= AC_ICAHEN_MSK;
    FLASH->AC |= FLASH_iCache;
}

/**
 * @brief  Enables or disables the Low Voltage Mode.
 * @note   This function can be used for N32G43x devices.
 * @param FLASH_LVM specifies the Low Voltage Mode status.
 *   This parameter can be one of the following values:
 *     @arg FLASH_LVM_EN  FLASH Low Voltage Mode Enable
 *     @arg FLASH_LVM_DIS FLASH Low Voltage Mode Disable
 */
void FLASH_LowVoltageModeCmd(uint32_t FLASH_LVM)
{
    /* Check the parameters */
    assert_param(IS_FLASH_LVM(FLASH_LVM));

    /* Enable or disable LVM */
    FLASH->AC &= AC_LVMEN_MSK;
    FLASH->AC |= FLASH_LVM;
}

/**
 * @brief  Checks whether the Low Voltage Mode status is SET or RESET.
 * @note   This function can be used for N32G43x devices.
 * @return Low Voltage Mode Status (SET or RESET).
 */
FlagStatus FLASH_GetLowVoltageModeSTS(void)
{
    FlagStatus bitstatus = RESET;

    if ((FLASH->AC & AC_LVMF_MSK) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the new state of FLASH Low Voltage Mode Status (SET or RESET) */
    return bitstatus;
}

/**
 * @brief  Enables or disables the FLASH Sleep Mode.
 * @note   This function can be used for N32G43x devices.
 * @param FLASH_SLM specifies the FLASH Sleep Mode status.
 *   This parameter can be one of the following values:
 *     @arg FLASH_SLM_EN  FLASH iCache Enable
 *     @arg FLASH_SLM_DIS FLASH iCache Disable
 */
void FLASH_FLASHSleepModeCmd(uint32_t FLASH_SLM)
{
    /* Check the parameters */
    assert_param(IS_FLASH_SLM(FLASH_SLM));

    /* Enable or disable SLM */
    FLASH->AC &= AC_SLMEN_MSK;
    FLASH->AC |= FLASH_SLM;
}

/**
 * @brief  Checks whether the FLASH Sleep Mode status is SET or RESET.
 * @note   This function can be used for N32G43x devices.
 * @return FLASH Sleep Mode Status (SET or RESET).
 */
FlagStatus FLASH_GetFLASHSleepModeSTS(void)
{
    FlagStatus bitstatus = RESET;

    if ((FLASH->AC & AC_SLMF_MSK) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the new state of FLASH Sleep Mode Status (SET or RESET) */
    return bitstatus;
}

/**
 * @brief  Checks whether the FLASH SMPSEL is SMP1 or SMP2.
 * @note   This function can be used for N32G43x devices.
 * @param FLASH_smpsel FLASH_SMPSEL_SMP1 or FLASH_SMPSEL_SMP2
 */
void FLASH_SetSMPSELStatus(uint32_t FLASH_smpsel)
{
    /* Check the parameters */
    assert_param(IS_FLASH_SMPSEL_STATE(FLASH_smpsel));

    /* SMP1 or SMP2 */
    FLASH->CTRL &= CTRL_Reset_SMPSEL;
    FLASH->CTRL |= FLASH_smpsel;
}

/**
 * @brief  Configures the Internal High Speed oscillator
 *         to program/erase FLASH.
 * @note   This function can be used for N32G43x devices.
 *         - For N32G43x devices this function enable HSI.
 * @return FLASH_HSICLOCK (FLASH_HSICLOCK_ENABLE or FLASH_HSICLOCK_DISABLE).
 */
FLASH_HSICLOCK FLASH_ClockInit(void)
{
    bool HSIStatus = 0;
    __IO uint32_t StartUpCounter = 0;
    FLASH_HSICLOCK hsiclock_status = FLASH_HSICLOCK_ENABLE;

    if ((RCC->CTRL & RCC_CTRL_HSIRDF) == RESET)
    {
        /* Enable HSI */
        RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

        /* Wait till HSI is ready and if Time out is reached exit */
        do
        {
            HSIStatus = RCC->CTRL & RCC_CTRL_HSIRDF;
            StartUpCounter++;
        } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

        HSIStatus = ((RCC->CTRL & RCC_CTRL_HSIRDF) != RESET);
        if (!HSIStatus)
        {
            hsiclock_status = FLASH_HSICLOCK_DISABLE;
        }
    }
    return hsiclock_status;
}

/**
 * @brief  Unlocks the FLASH Program Erase Controller.
 * @note   This function can be used for N32G43x devices.
 *         - For N32G43x devices this function unlocks Bank.
 *           to FLASH_Unlock function..
 */
void FLASH_Unlock(void)
{
    /* Unlocks the FLASH Program Erase Controller */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
}

/**
 * @brief  Locks the FLASH Program Erase Controller.
 * @note   This function can be used for N32G43x devices.
 *         - For N32G43x devices this function Locks Bank.
 *           to FLASH_Lock function.
 */
void FLASH_Lock(void)
{
    /* Set the Lock Bit to lock the FLASH Program Erase Controller */
    FLASH->CTRL |= CTRL_Set_LOCK;
}

/**
 * @brief  Erases a specified FLASH page.
 * @note   This function can be used for N32G43x devices.
 * @param Page_Address The page address to be erased.
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERR_RDKEY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_EraseOnePage(uint32_t Page_Address)
{
    FLASH_STS status = FLASH_COMPL;
    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(Page_Address));

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);

    if (status == FLASH_COMPL)
    {
        /* if the previous operation is completed, proceed to erase the page */
        FLASH->CTRL |= CTRL_Set_PER;
        FLASH->ADD = Page_Address;
        FLASH->CTRL |= CTRL_Set_START;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);

        /* Disable the PER Bit */
        FLASH->CTRL &= CTRL_Reset_PER;
    }

    /* Return the Erase Status */
    return status;
}

/**
 * @brief  Erases all FLASH pages.
 * @note   This function can be used for all N32G43x devices.
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERR_RDKEY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_MassErase(void)
{
    FLASH_STS status = FLASH_COMPL;

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);
    if (status == FLASH_COMPL)
    {
        /* if the previous operation is completed, proceed to erase all pages */
        FLASH->CTRL |= CTRL_Set_MER;
        FLASH->CTRL |= CTRL_Set_START;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);

        /* Disable the MER Bit */
        FLASH->CTRL &= CTRL_Reset_MER;
    }

    /* Return the Erase Status */
    return status;
}

/**
 * @brief  Erases the FLASH option bytes.
 * @note   This functions erases all option bytes except the Read protection (RDP).
 * @note   This function can be used for N32G43x devices.
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERR_RDKEY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_RDP2 or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_EraseOB(void)
{
    uint32_t rdptmp = L1_RDP_Key;

    FLASH_STS status = FLASH_COMPL;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status = FLASH_ERR_RDP2;
        return status;
    }

    /* Get the actual read protection Option Byte value */
    if (FLASH_GetReadOutProtectionSTS() != RESET)
    {
        rdptmp = FLASH_USER_USER;
    }

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);

    if (status == FLASH_COMPL)
    {
        /* Authorize the small information block programming */
        FLASH->OPTKEY = FLASH_KEY1;
        FLASH->OPTKEY = FLASH_KEY2;

        /* if the previous operation is completed, proceed to erase the option bytes */
        FLASH->CTRL |= CTRL_Set_OPTER;
        FLASH->CTRL |= CTRL_Set_START;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);

        if (status == FLASH_COMPL)
        {
            /* Clears the FLASH's pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);

            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= CTRL_Reset_OPTER;

            /* Enable the Option Bytes Programming operation */
            FLASH->CTRL |= CTRL_Set_OPTPG;
            /* Restore the last read protection Option Byte value */
            OBT->USER_RDP = (uint32_t)rdptmp;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOpt(ProgramTimeout);

            if (status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CTRL &= CTRL_Reset_OPTPG;
            }
        }
        else
        {
            if (status != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= CTRL_Reset_OPTER;
            }
        }
    }
    /* Return the erase status */
    return status;
}


/**
 * @brief  Programs the FLASH User Option Byte:
 *         RDP1 / IWDG_SW / RST_STOP2 / RST_STDBY / RST_PD / OB_Data0 / OB_Data1
 *         WRP_Pages / RDP2 / nBOOT0 / nBOOT1 / nSWBOOT0 / BOR_LEV[2:0].
 * @note   This function can be used for N32G43x devices.
 * @param  OB_RDP1
 *   This parameter can be one of the following values:
 *     @arg OB_RDP1_ENABLE
 *     @arg OB_RDP1_DISABLE
 * @param  OB_IWDG Selects the IWDG mode
 *   This parameter can be one of the following values:
 *     @arg OB_IWDG_SW Software IWDG selected
 *     @arg OB_IWDG_HW Hardware IWDG selected
 * @param  OB_STOP2 Reset event when entering STOP2 mode.
 *   This parameter can be one of the following values:
 *     @arg OB_STOP2_NORST No reset generated when entering in STOP2
 *     @arg OB_STOP2_RST Reset generated when entering in STOP2
 * @param  OB_STDBY Reset event when entering Standby mode.
 *   This parameter can be one of the following values:
 *     @arg OB_STDBY_NORST No reset generated when entering in STANDBY
 *     @arg OB_STDBY_RST Reset generated when entering in STANDBY
 * @param  OB_PD Reset event when entering PowerDown mode.
 *   This parameter can be one of the following values:
 *     @arg OB_PD_NORST No reset generated when entering in PowerDown
 *     @arg OB_PD_RST Reset generated when entering in PowerDown
 * @param  OB_Data0
 *   This parameter can be one of the following values:
 *     @arg 0x00 ~ 0xFF
 * @param  OB_Data1
 *   This parameter can be one of the following values:
 *     @arg 0x00 ~ 0xFF
 * @param WRP_Pages specifies the address of the pages to be write protected.
 *   This parameter can be:
 *     @arg For @b N32G43x_devices: value between FLASH_WRP_Pages0to1 and
 *       FLASH_WRP_Pages62to63 or FLASH_WRP_AllPages or (~FLASH_WRP_AllPages)
 * @param  OB_RDP2
 *   This parameter can be one of the following values:
 *     @arg OB_RDP2_ENABLE
 *     @arg OB_RDP2_DISABLE
 * @param  OB2_nBOOT0
 *   This parameter can be one of the following values:
 *     @arg OB2_NBOOT0_SET Set nBOOT0
 *     @arg OB2_NBOOT0_CLR Clear nBOOT0
 * @param OB2_nBOOT1
 *   This parameter can be one of the following values:
 *     @arg OB2_NBOOT1_SET Set nBOOT1
 *     @arg OB2_NBOOT1_CLR Clear nBOOT1
 * @param OB2_nSWBOOT0
 *   This parameter can be one of the following values:
 *     @arg OB2_NSWBOOT0_SET Set nSWBOOT0
 *     @arg OB2_NSWBOOT0_CLR Clear nSWBOOT0
* @param OB2_BOR_LEV[2:0]
 *   This parameter can be one of the following values:
 *     @arg OB2_BOR_LEV0
 *     @arg OB2_BOR_LEV1
 *     @arg OB2_BOR_LEV2
 *     @arg OB2_BOR_LEV3
 *     @arg OB2_BOR_LEV4
 *     @arg OB2_BOR_LEV5
 *     @arg OB2_BOR_LEV6
 *     @arg OB2_BOR_LEV7
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERR_RDKEY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_RDP2 or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_ConfigALLOptionByte(uint8_t OB_RDP1,    uint8_t OB_IWDG,    uint8_t OB_STOP2,
                                    uint8_t OB_STDBY,   uint8_t OB_PD,      uint8_t OB_Data0,
                                    uint8_t OB_Data1,   uint32_t WRP_Pages, uint8_t OB_RDP2,
                                    uint8_t OB2_nBOOT0, uint8_t OB2_nBOOT1, uint8_t OB2_nSWBOOT0,
                                    uint8_t OB2_BOR_LEV)
{
    uint32_t rdpuser_tmp, data0data1_tmp, wrp0wrp1_tmp, wrp2wrp3_tmp, rdp2user2_tmp;

    FLASH_STS status = FLASH_COMPL;

    /* Check the parameters */
    assert_param(IS_OB_RDP1_SOURCE(OB_RDP1));
    assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
    assert_param(IS_OB_STOP2_SOURCE(OB_STOP2));
    assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));
    assert_param(IS_OB_PD_SOURCE(OB_PD));
    assert_param(IS_FLASH_WRP_PAGE(WRP_Pages));
    assert_param(IS_OB_RDP2_SOURCE(OB_RDP2));
    assert_param(IS_OB2_NBOOT0_SOURCE(OB2_nBOOT0));
    assert_param(IS_OB2_NBOOT1_SOURCE(OB2_nBOOT1));
    assert_param(IS_OB2_NSWBOOT0_SOURCE(OB2_nSWBOOT0));
    assert_param(IS_OB2_BOR_LEV_SOURCE(OB2_BOR_LEV));

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status = FLASH_ERR_RDP2;
        return status;
    }

    WRP_Pages      = (uint32_t)(~WRP_Pages);
    rdpuser_tmp    = (((uint32_t)OB_RDP1) | (((uint32_t)(OB_IWDG | OB_STOP2 | OB_STDBY | OB_PD)) << 16));
    data0data1_tmp = (((uint32_t)OB_Data0) | (((uint32_t)OB_Data0) << 16));
    wrp0wrp1_tmp   = ((WRP_Pages & FLASH_WRP0_WRP0) | ((WRP_Pages << 8) & FLASH_WRP1_WRP1));
    wrp2wrp3_tmp   = (((WRP_Pages >> 16) & FLASH_WRP2_WRP2) | ((WRP_Pages >> 8) & FLASH_WRP3_WRP3));
    rdp2user2_tmp  = (((uint32_t)OB_RDP2) | (((uint32_t)(OB2_nBOOT0 | OB2_nBOOT1 | OB2_nSWBOOT0 | OB2_BOR_LEV)) << 16));

    /* Authorize the small information block programming */
    FLASH->OPTKEY = FLASH_KEY1;
    FLASH->OPTKEY = FLASH_KEY2;

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);
    if (status == FLASH_COMPL)
    {
        /* if the previous operation is completed, proceed to erase the option bytes */
        FLASH->CTRL |= CTRL_Set_OPTER;
        FLASH->CTRL |= CTRL_Set_START;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);

        if (status == FLASH_COMPL)
        {
            /* Clears the FLASH's pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);

            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= CTRL_Reset_OPTER;

            /* Enable the Option Bytes Programming operation */
            FLASH->CTRL |= CTRL_Set_OPTPG;

            /* Program USER_RDP Option Byte value */
            OBT->USER_RDP = (uint32_t)rdpuser_tmp;

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOpt(ProgramTimeout);

            if (status == FLASH_COMPL)
            {
                /* Clears the FLASH's pending flags */
                FLASH_ClearFlag(FLASH_STS_CLRFLAG);

                /* Program Data1_Data0 Option Byte value */
                OBT->Data1_Data0 = (uint32_t)data0data1_tmp;

                /* Wait for last operation to be completed */
                status = FLASH_WaitForLastOpt(ProgramTimeout);

                if (status == FLASH_COMPL)
                {
                    /* Clears the FLASH's pending flags */
                    FLASH_ClearFlag(FLASH_STS_CLRFLAG);

                    /* Program WRP1_WRP0 Option Byte value */
                    OBT->WRP1_WRP0 = (uint32_t)wrp0wrp1_tmp;

                    /* Wait for last operation to be completed */
                    status = FLASH_WaitForLastOpt(ProgramTimeout);

                    if (status == FLASH_COMPL)
                    {
                        /* Clears the FLASH's pending flags */
                        FLASH_ClearFlag(FLASH_STS_CLRFLAG);

                        /* Program WRP3_WRP2 Option Byte value */
                        OBT->WRP3_WRP2 = (uint32_t)wrp2wrp3_tmp;

                        /* Wait for last operation to be completed */
                        status = FLASH_WaitForLastOpt(ProgramTimeout);

                        if (status == FLASH_COMPL)
                        {
                            /* Clears the FLASH's pending flags */
                            FLASH_ClearFlag(FLASH_STS_CLRFLAG);

                            /* Program USER2_RDP2 Option Byte value */
                            OBT->USER2_RDP2 = (uint32_t)rdp2user2_tmp;

                            /* Wait for last operation to be completed */
                            status = FLASH_WaitForLastOpt(ProgramTimeout);
                        }
                    }
                }
            }

            if (status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CTRL &= CTRL_Reset_OPTPG;
            }
        }
        else
        {
            if (status != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= CTRL_Reset_OPTER;
            }
        }
    }

    /* Return the Option Byte program Status */
    return status;
}

/**
 * @brief  Programs a word at a specified address.
 * @note   This function can be used for N32G43x devices.
 * @param Address specifies the address to be programmed.
 * @param Data specifies the data to be programmed.
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERR_RDKEY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_ADD or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
    FLASH_STS status  = FLASH_COMPL;

    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(Address));

    if ((Address & (uint32_t)0x3) != 0)
    {
        /* The programming address is not a multiple of 4 */
        status = FLASH_ERR_ADD;
        return status;
    }

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(ProgramTimeout);

    if (status == FLASH_COMPL)
    {
        /* if the previous operation is completed, proceed to program the new word */
        FLASH->CTRL |= CTRL_Set_PG;

        *(__IO uint32_t*)Address = (uint32_t)Data;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(ProgramTimeout);

        /* Disable the PG Bit */
        FLASH->CTRL &= CTRL_Reset_PG;
    }

    /* Return the Program Status */
    return status;
}

/**
 * @brief  Programs a half word at a specified Option Byte Data address.
 * @note   This function can be used for N32G43x devices.
 * @param Address specifies the address to be programmed.
 *   This parameter can be 0x1FFFF804.
 * @param Data specifies the data to be programmed(Data0 and Data1).
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERR_RDKEY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_RDP2 or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_ProgramOBData(uint32_t Address, uint32_t Data)
{
    FLASH_STS status = FLASH_COMPL;
    /* Check the parameters */
    assert_param(IS_OB_DATA_ADDRESS(Address));

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status = FLASH_ERR_RDP2;
        return status;
    }

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(ProgramTimeout);

    if (status == FLASH_COMPL)
    {
        /* Authorize the small information block programming */
        FLASH->OPTKEY = FLASH_KEY1;
        FLASH->OPTKEY = FLASH_KEY2;
        /* Enables the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        *(__IO uint32_t*)Address = (uint32_t)Data;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    /* Return the Option Byte Data Program Status */
    return status;
}

/**
 * @brief  Write protects the desired pages
 * @note   This function can be used for N32G43x devices.
 * @param FLASH_Pages specifies the address of the pages to be write protected.
 *   This parameter can be:
 *     @arg For @b N32G43x_devices: value between FLASH_WRP_Pages0to1 and
 *       FLASH_WRP_Pages60to61 or FLASH_WRP_Pages62to63
 *     @arg FLASH_WRP_AllPages
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERR_RDKEY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_RDP2 or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_EnWriteProtection(uint32_t FLASH_Pages)
{
    uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;

    FLASH_STS status = FLASH_COMPL;

    /* Check the parameters */
    assert_param(IS_FLASH_WRP_PAGE(FLASH_Pages));

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status = FLASH_ERR_RDP2;
        return status;
    }

    FLASH_Pages = (uint32_t)(~FLASH_Pages);
    WRP0_Data   = (uint16_t)(FLASH_Pages & WRP0_MSK);
    WRP1_Data   = (uint16_t)((FLASH_Pages & WRP1_MSK) >> 8);
    WRP2_Data   = (uint16_t)((FLASH_Pages & WRP2_MSK) >> 16);
    WRP3_Data   = (uint16_t)((FLASH_Pages & WRP3_MSK) >> 24);

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(ProgramTimeout);

    if (status == FLASH_COMPL)
    {
        /* Authorizes the small information block programming */
        FLASH->OPTKEY = FLASH_KEY1;
        FLASH->OPTKEY = FLASH_KEY2;
        FLASH->CTRL |= CTRL_Set_OPTPG;

        if ((WRP0_Data != 0xFF) || (WRP1_Data != 0xFF))
        {
            OBT->WRP1_WRP0 = (((uint32_t)WRP0_Data) | (((uint32_t)WRP1_Data) << 16));

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOpt(ProgramTimeout);
        }

        if (((WRP2_Data != 0xFF) || (WRP3_Data != 0xFF)) && (status == FLASH_COMPL))
        {
            OBT->WRP3_WRP2 = (((uint32_t)WRP2_Data) | (((uint32_t)WRP3_Data) << 16));

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOpt(ProgramTimeout);
        }

        if (status != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    /* Return the write protection operation Status */
    return status;
}

/**
 * @brief  Enables or disables the read out protection.
 * @note   If the user has already programmed the other option bytes before calling
 *   this function, he must re-program them since this function erases all option bytes.
 * @note   This function can be used for N32G43x devices.
 * @param Cmd new state of the ReadOut Protection.
 *   This parameter can be: ENABLE or DISABLE.
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERR_RDKEY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_RDP2 or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_ReadOutProtectionL1(FunctionalState Cmd)
{
    uint32_t usertmp;
    FLASH_STS status = FLASH_COMPL;

    usertmp = ((OBR_USER_MSK & FLASH->OB) << 0x0E);
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status = FLASH_ERR_RDP2;
        return status;
    }

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);

    if (status == FLASH_COMPL)
    {
        /* Authorizes the small information block programming */
        FLASH->OPTKEY = FLASH_KEY1;
        FLASH->OPTKEY = FLASH_KEY2;
        FLASH->CTRL |= CTRL_Set_OPTER;
        FLASH->CTRL |= CTRL_Set_START;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);
        if (status == FLASH_COMPL)
        {
            /* Clears the FLASH's pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);

            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= CTRL_Reset_OPTER;
            /* Enable the Option Bytes Programming operation */
            FLASH->CTRL |= CTRL_Set_OPTPG;
            if (Cmd != DISABLE)
            {
                OBT->USER_RDP = (FLASH_USER_USER & usertmp);
            }
            else
            {
                OBT->USER_RDP = ((L1_RDP_Key & FLASH_RDP_RDP1) | usertmp);
            }
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOpt(EraseTimeout);

            if (status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CTRL &= CTRL_Reset_OPTPG;
            }
        }
        else
        {
            if (status != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= CTRL_Reset_OPTER;
            }
        }
    }
    /* Return the protection operation Status */
    return status;
}

/**
 * @brief  Enables or disables the read out protection L2.
 * @note   If the user has already programmed the other option bytes before calling
 *   this function, he must re-program them since this function erases all option bytes.
 * @note   This function can be used for N32G43x devices.
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERR_RDKEY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_RDP2 or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_ReadOutProtectionL2_ENABLE(void)
{
    uint32_t usertmp;
    FLASH_STS status = FLASH_COMPL;

    usertmp = ((OBR_USER_MSK & FLASH->OB) << 0x0E);

    /* Get the actual read protection L1 Option Byte value */
    if (FLASH_GetReadOutProtectionSTS() == RESET)
    {
        usertmp |= (L1_RDP_Key & FLASH_RDP_RDP1);
    }
    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status = FLASH_ERR_RDP2;
        return status;
    }

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);

    if (status == FLASH_COMPL)
    {
        /* Authorizes the small information block programming */
        FLASH->OPTKEY = FLASH_KEY1;
        FLASH->OPTKEY = FLASH_KEY2;
        FLASH->CTRL |= CTRL_Set_OPTER;
        FLASH->CTRL |= CTRL_Set_START;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);
        if (status == FLASH_COMPL)
        {
            /* Clears the FLASH's pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);

            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= CTRL_Reset_OPTER;
            /* Enable the Option Bytes Programming operation */
            FLASH->CTRL |= CTRL_Set_OPTPG;

            OBT->USER_RDP = usertmp;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOpt(EraseTimeout);

            if (status == FLASH_COMPL)
            {
                /* Clears the FLASH's pending flags */
                FLASH_ClearFlag(FLASH_STS_CLRFLAG);

                /* Enables the read out protection L2 */
                OBT->USER2_RDP2 = L2_RDP_Key;

                /* Wait for last operation to be completed */
                status = FLASH_WaitForLastOpt(EraseTimeout);
            }

            if (status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CTRL &= CTRL_Reset_OPTPG;
            }
        }
        else
        {
            if (status != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= CTRL_Reset_OPTER;
            }
        }
    }
    /* Return the protection operation Status */
    return status;
}

/**
 * @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
 * @note   This function can be used for N32G43x devices.
 * @param OB_IWDG Selects the IWDG mode
 *   This parameter can be one of the following values:
 *     @arg OB_IWDG_SW Software IWDG selected
 *     @arg OB_IWDG_HW Hardware IWDG selected
 * @param OB_STOP2 Reset event when entering STOP2 mode.
 *   This parameter can be one of the following values:
 *     @arg OB_STOP2_NORST No reset generated when entering in STOP2
 *     @arg OB_STOP2_RST Reset generated when entering in STOP2
 * @param OB_STDBY Reset event when entering Standby mode.
 *   This parameter can be one of the following values:
 *     @arg OB_STDBY_NORST No reset generated when entering in STANDBY
 *     @arg OB_STDBY_RST Reset generated when entering in STANDBY
 * @param OB_PD Reset event when entering PowerDown mode.
 *   This parameter can be one of the following values:
 *     @arg OB_PD_NORST No reset generated when entering in PowerDown
 *     @arg OB_PD_RST Reset generated when entering in PowerDown
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERR_RDKEY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_RDP2 or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_ConfigUserOB(uint8_t OB_IWDG, uint8_t OB_STOP2, uint8_t OB_STDBY, uint8_t OB_PD)
{
    uint32_t rdpuser_tmp = RDP_USER_Key;

    FLASH_STS status = FLASH_COMPL;

    /* Check the parameters */
    assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
    assert_param(IS_OB_STOP2_SOURCE(OB_STOP2));
    assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));
    assert_param(IS_OB_PD_SOURCE(OB_PD));

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status = FLASH_ERR_RDP2;
        return status;
    }

    /* Get the actual read protection Option Byte value */
    if (FLASH_GetReadOutProtectionSTS() != RESET)
    {
        rdpuser_tmp = 0xFFF00000;
    }

    /* Authorize the small information block programming */
    FLASH->OPTKEY = FLASH_KEY1;
    FLASH->OPTKEY = FLASH_KEY2;

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);

    if (status == FLASH_COMPL)
    {
        /* if the previous operation is completed, proceed to erase the option bytes */
        FLASH->CTRL |= CTRL_Set_OPTER;
        FLASH->CTRL |= CTRL_Set_START;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);

        if (status == FLASH_COMPL)
        {
            /* Clears the FLASH's pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);

            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= CTRL_Reset_OPTER;

            /* Enable the Option Bytes Programming operation */
            FLASH->CTRL |= CTRL_Set_OPTPG;
            /* Restore the last read protection Option Byte value */
            OBT->USER_RDP =
                (uint32_t)rdpuser_tmp
                | (((uint32_t)(OB_IWDG | OB_STOP2 | OB_STDBY | OB_PD)) << 16);
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOpt(ProgramTimeout);

            if (status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CTRL &= CTRL_Reset_OPTPG;
            }
        }
        else
        {
            if (status != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= CTRL_Reset_OPTER;
            }
        }
    }

    /* Return the Option Byte program Status */
    return status;
}

/**
 * @brief  Programs the FLASH User Option Byte: nBOOT0 / nBOOT1 / nSWBOOT0 / BOR_LEV[2:0].
 * @note   This function can be used for N32G43x devices.
 * @param OB2_nBOOT0
 *   This parameter can be one of the following values:
 *     @arg OB2_NBOOT0_SET Set nBOOT0
 *     @arg OB2_NBOOT0_CLR Clear nBOOT0
 * @param OB2_nBOOT1
 *   This parameter can be one of the following values:
 *     @arg OB2_NBOOT1_SET Set nBOOT1
 *     @arg OB2_NBOOT1_CLR Clear nBOOT1
 * @param OB2_nSWBOOT0
 *   This parameter can be one of the following values:
 *     @arg OB2_NSWBOOT0_SET Set nSWBOOT0
 *     @arg OB2_NSWBOOT0_CLR Clear nSWBOOT0
* @param OB2_BOR_LEV[2:0]
 *   This parameter can be one of the following values:
 *     @arg OB2_BOR_LEV0
 *     @arg OB2_BOR_LEV1
 *     @arg OB2_BOR_LEV2
 *     @arg OB2_BOR_LEV3
 *     @arg OB2_BOR_LEV4
 *     @arg OB2_BOR_LEV5
 *     @arg OB2_BOR_LEV6
 *     @arg OB2_BOR_LEV7
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERR_RDKEY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV, FLASH_ERR_RDP2 or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_ConfigUserOB2(uint8_t OB2_nBOOT0, uint8_t OB2_nBOOT1,
                              uint8_t OB2_nSWBOOT0, uint8_t OB2_BOR_LEV)
{
    uint32_t rdpuser_tmp = (RDP_USER_Key | FLASH_USER_USER);
    uint32_t rdp2user2_tmp = 0xFF00FFFF;

    FLASH_STS status = FLASH_COMPL;

    /* Check the parameters */
    assert_param(IS_OB2_NBOOT0_SOURCE(OB2_nBOOT0));
    assert_param(IS_OB2_NBOOT1_SOURCE(OB2_nBOOT1));
    assert_param(IS_OB2_NSWBOOT0_SOURCE(OB2_nSWBOOT0));
    assert_param(IS_OB2_BOR_LEV_SOURCE(OB2_BOR_LEV));

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status = FLASH_ERR_RDP2;
        return status;
    }

    /* Get the actual read protection Option Byte value */
    if (FLASH_GetReadOutProtectionSTS() != RESET)
    {
        rdpuser_tmp = 0xFFFF0000;
    }

    /* Authorize the small information block programming */
    FLASH->OPTKEY = FLASH_KEY1;
    FLASH->OPTKEY = FLASH_KEY2;

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);

    if (status == FLASH_COMPL)
    {
        /* if the previous operation is completed, proceed to erase the option bytes */
        FLASH->CTRL |= CTRL_Set_OPTER;
        FLASH->CTRL |= CTRL_Set_START;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);

        if (status == FLASH_COMPL)
        {
            /* Clears the FLASH's pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);

            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= CTRL_Reset_OPTER;

            /* Enable the Option Bytes Programming operation */
            FLASH->CTRL |= CTRL_Set_OPTPG;

            /* Restore the last RDP1 Option Byte value */
            OBT->USER_RDP = (uint32_t)rdpuser_tmp;

            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOpt(ProgramTimeout);

            if (status == FLASH_COMPL)
            {
                /* Clears the FLASH's pending flags */
                FLASH_ClearFlag(FLASH_STS_CLRFLAG);

                /* Restore the last RDP2 Option Byte value */
                OBT->USER2_RDP2 = (uint32_t)rdp2user2_tmp | (((uint32_t)(OB2_nBOOT0)   | (uint32_t)(OB2_nBOOT1)  \
                                                         | (uint32_t)(OB2_nSWBOOT0) | (uint32_t)(OB2_BOR_LEV)) << 16);

                /* Wait for last operation to be completed */
                status = FLASH_WaitForLastOpt(ProgramTimeout);
            }

            if (status != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CTRL &= CTRL_Reset_OPTPG;
            }
        }
        else
        {
            if (status != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= CTRL_Reset_OPTER;
            }
        }
    }

    /* Return the Option Byte program Status */
    return status;
}

/**
 * @brief  Returns the FLASH User Option Bytes values.
 * @note   This function can be used for N32G43x devices.
 * @return The FLASH User Option Bytes values:IWDG_SW(Bit0), RST_STOP(Bit1)
 *         and RST_STDBY(Bit2).
 */
uint32_t FLASH_GetUserOB(void)
{
    /* Return the User Option Byte */
    return (uint32_t)(FLASH->OB >> 2);
}

/**
 * @brief  Returns the FLASH Write Protection Option Bytes Register value.
 * @note   This function can be used for N32G43x devices.
 * @return The FLASH Write Protection  Option Bytes Register value
 */
uint32_t FLASH_GetWriteProtectionOB(void)
{
    /* Return the Flash write protection Register value */
    return (uint32_t)(FLASH->WRP);
}

/**
 * @brief  Checks whether the FLASH Read Out Protection Status is set or not.
 * @note   This function can be used for N32G43x devices.
 * @return FLASH ReadOut Protection Status(SET or RESET)
 */
FlagStatus FLASH_GetReadOutProtectionSTS(void)
{
    FlagStatus readoutstatus = RESET;
    if ((FLASH->OB & RDPRTL1_MSK) != (uint32_t)RESET)
    {
        readoutstatus = SET;
    }
    else
    {
        readoutstatus = RESET;
    }
    return readoutstatus;
}

/**
 * @brief  Checks whether the FLASH Read Out Protection L2 Status is set or not.
 * @note   This function can be used for N32G43x devices.
 * @return FLASH ReadOut Protection L2 Status(SET or RESET)
 */
FlagStatus FLASH_GetReadOutProtectionL2STS(void)
{
    FlagStatus readoutstatus = RESET;
    if ((FLASH->OB & RDPRTL2_MSK) != (uint32_t)RESET)
    {
        readoutstatus = SET;
    }
    else
    {
        readoutstatus = RESET;
    }
    return readoutstatus;
}

/**
 * @brief  Checks whether the FLASH Prefetch Buffer status is set or not.
 * @note   This function can be used for N32G43x devices.
 * @return FLASH Prefetch Buffer Status (SET or RESET).
 */
FlagStatus FLASH_GetPrefetchBufSTS(void)
{
    FlagStatus bitstatus = RESET;

    if ((FLASH->AC & AC_PRFTBS_MSK) != (uint32_t)RESET)
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
 * @brief  Checks whether the FLASH SMPSEL is SMP1 or SMP2.
 * @note   This function can be used for N32G43x devices.
 * @return FLASH SMPSEL (FLASH_SMP1 or FLASH_SMP2).
 */
FLASH_SMPSEL FLASH_GetSMPSELStatus(void)
{
    FLASH_SMPSEL bitstatus = FLASH_SMP1;

    if ((FLASH->CTRL & CTRL_Reset_SMPSEL) != (uint32_t)FLASH_SMP1)
    {
        bitstatus = FLASH_SMP2;
    }
    else
    {
        bitstatus = FLASH_SMP1;
    }
    /* Return the new state of FLASH SMPSEL (FLASH_SMP1 or FLASH_SMP2) */
    return bitstatus;
}

/**
 * @brief  Enables or disables the specified FLASH interrupts.
 * @note   This function can be used for N32G43x devices.
 * @param FLASH_INT specifies the FLASH interrupt sources to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg FLASH_IT_ERROR FLASH Error Interrupt
 *     @arg FLASH_INT_FERR EVERR PVERR Interrupt
 *     @arg FLASH_INT_EOP FLASH end of operation Interrupt
 * @param Cmd new state of the specified Flash interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 */
void FLASH_INTConfig(uint32_t FLASH_INT, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FLASH_INT(FLASH_INT));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the interrupt sources */
        FLASH->CTRL |= FLASH_INT;
    }
    else
    {
        /* Disable the interrupt sources */
        FLASH->CTRL &= ~(uint32_t)FLASH_INT;
    }
}

/**
 * @brief  Checks whether the specified FLASH flag is set or not.
 * @note   This function can be used for N32G43x devices.
 * @param FLASH_FLAG specifies the FLASH flag to check.
 *   This parameter can be one of the following values:
 *     @arg FLASH_FLAG_BUSY FLASH Busy flag
 *     @arg FLASH_FLAG_PGERR FLASH Program error flag
 *     @arg FLASH_FLAG_PVERR FLASH Program Verify ERROR flag
 *     @arg FLASH_FLAG_WRPERR FLASH Write protected error flag
 *     @arg FLASH_FLAG_EOP FLASH End of Operation flag
 *     @arg FLASH_FLAG_EVERR FLASH Erase Verify ERROR flag
 *     @arg FLASH_FLAG_OBERR FLASH Option Byte error flag
 * @return The new state of FLASH_FLAG (SET or RESET).
 */
FlagStatus FLASH_GetFlagSTS(uint32_t FLASH_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG));
    if (FLASH_FLAG == FLASH_FLAG_OBERR)
    {
        if ((FLASH->OB & FLASH_FLAG_OBERR) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else
    {
        if ((FLASH->STS & FLASH_FLAG) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }

    /* Return the new state of FLASH_FLAG (SET or RESET) */
    return bitstatus;
}

/**
 * @brief  Clears the FLASH's pending flags.
 * @note   This function can be used for N32G43x devices.
 * @param FLASH_FLAG specifies the FLASH flags to clear.
 *   This parameter can be any combination of the following values:
 *     @arg FLASH_FLAG_PGERR FLASH Program error flag
 *     @arg FLASH_FLAG_PVERR FLASH Program Verify ERROR flag
 *     @arg FLASH_FLAG_WRPERR FLASH Write protected error flag
 *     @arg FLASH_FLAG_EOP FLASH End of Operation flag
 *     @arg FLASH_FLAG_EVERR FLASH Erase Verify ERROR flag
 */
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
    /* Check the parameters */
    assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG));

    /* Clear the flags */
    FLASH->STS |= FLASH_FLAG;
}

/**
 * @brief  Returns the FLASH Status.
 * @note   This function can be used for N32G43x devices, it is equivalent
 *         to FLASH_GetBank1Status function.
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERR_RDKEY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_GetSTS(void)
{
    FLASH_STS flashstatus = FLASH_COMPL;

    if ((FLASH->STS & FLASH_FLAG_BUSY) == FLASH_FLAG_BUSY)
    {
        flashstatus = FLASH_BUSY;
    }
    else
    {
        if ((FLASH->STS & FLASH_FLAG_PGERR) != 0)
        {
            flashstatus = FLASH_ERR_PG;
        }
        else
        {
            if ((FLASH->STS & FLASH_FLAG_PVERR) != 0)
            {
                flashstatus = FLASH_ERR_PV;
            }
            else
            {
                if ((FLASH->STS & FLASH_FLAG_WRPERR) != 0)
                {
                    flashstatus = FLASH_ERR_WRP;
                }
                else
                {
                    if ((FLASH->STS & FLASH_FLAG_EVERR) != 0)
                    {
                        flashstatus = FLASH_ERR_EV;
                    }
                    else
                    {
                        flashstatus = FLASH_COMPL;
                    }
                }
            }
        }
    }

    /* Return the Flash Status */
    return flashstatus;
}

/**
 * @brief  Waits for a Flash operation to complete or a TIMEOUT to occur.
 * @note   This function can be used for N32G43x devices,
 *         it is equivalent to FLASH_WaitForLastBank1Operation..
 * @param Timeout FLASH programming Timeout
 * @return FLASH Status: The returned value can be: FLASH_BUSY, FLASH_ERR_RDKEY,
 *         FLASH_ERR_PG, FLASH_ERR_PV, FLASH_ERR_WRP, FLASH_COMPL,
 *         FLASH_ERR_EV or FLASH_TIMEOUT.
 */
FLASH_STS FLASH_WaitForLastOpt(uint32_t Timeout)
{
    FLASH_STS status = FLASH_COMPL;

    /* Check for the Flash Status */
    status = FLASH_GetSTS();
    /* Wait for a Flash operation to complete or a TIMEOUT to occur */
    while ((status == FLASH_BUSY) && (Timeout != 0x00))
    {
        status = FLASH_GetSTS();
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
