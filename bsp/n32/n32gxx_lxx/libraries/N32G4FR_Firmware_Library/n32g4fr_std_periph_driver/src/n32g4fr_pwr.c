/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
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
 * @file n32g4fr_pwr.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g4fr_pwr.h"

/** @addtogroup N32G4FR_StdPeriph_Driver
 * @{
 */

/** @addtogroup PWR
 * @brief PWR driver modules
 * @{
 */

/** @addtogroup PWR_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup PWR_Private_Defines
 * @{
 */

/* --------- PWR registers bit address in the alias region ---------- */
#define PWR_OFFSET (PWR_BASE - PERIPH_BASE)

/* --- CTRL Register ---*/

/* Alias word address of DBKP bit */
#define CTRL_OFFSET  (PWR_OFFSET + 0x00)
#define DBKP_BITN    0x08
#define CTRL_DBKP_BB (PERIPH_BB_BASE + (CTRL_OFFSET * 32) + (DBKP_BITN * 4))

/* Alias word address of PVDEN bit */
#define PVDEN_BITN    0x04
#define CTRL_PVDEN_BB (PERIPH_BB_BASE + (CTRL_OFFSET * 32) + (PVDEN_BITN * 4))

/* --- CTRLSTS Register ---*/

/* Alias word address of WKUPEN bit */
#define CTRLSTS_OFFSET    (PWR_OFFSET + 0x04)
#define WKUPEN_BITN       0x08
#define CTRLSTS_WKUPEN_BB (PERIPH_BB_BASE + (CTRLSTS_OFFSET * 32) + (WKUPEN_BITN * 4))

/* ------------------ PWR registers bit mask ------------------------ */

/* CTRL register bit mask */
#define CTRL_DS_MASK  ((uint32_t)0xFFFFFFFC)
#define CTRL_PRS_MASK ((uint32_t)0xFFFFFD1F)

/**
 * @}
 */

/** @addtogroup PWR_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup PWR_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup PWR_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup PWR_Private_Functions
 * @{
 */

/**
 * @brief  Deinitializes the PWR peripheral registers to their default reset values.
 */
void PWR_DeInit(void)
{
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_PWR, ENABLE);
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_PWR, DISABLE);
}

/**
 * @brief  Enables or disables access to the RTC and backup registers.
 * @param Cmd new state of the access to the RTC and backup registers.
 *   This parameter can be: ENABLE or DISABLE.
 */
void PWR_BackupAccessEnable(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    *(__IO uint32_t*)CTRL_DBKP_BB = (uint32_t)Cmd;
}

/**
 * @brief  Enables or disables the Power Voltage Detector(PVD).
 * @param Cmd new state of the PVD.
 *   This parameter can be: ENABLE or DISABLE.
 */
void PWR_PvdEnable(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    *(__IO uint32_t*)CTRL_PVDEN_BB = (uint32_t)Cmd;
}

/**
 * @brief  Configures the voltage threshold detected by the Power Voltage Detector(PVD).
 * @param PWR_PVDLevel specifies the PVD detection level
 *   This parameter can be one of the following values:
 *     @arg PWR_PVDRANGRE_2V2 PVD detection level set to 2.2V
 *     @arg PWR_PVDRANGRE_2V3 PVD detection level set to 2.3V
 *     @arg PWR_PVDRANGRE_2V4 PVD detection level set to 2.4V
 *     @arg PWR_PVDRANGRE_2V5 PVD detection level set to 2.5V
 *     @arg PWR_PVDRANGRE_2V6 PVD detection level set to 2.6V
 *     @arg PWR_PVDRANGRE_2V7 PVD detection level set to 2.7V
 *     @arg PWR_PVDRANGRE_2V8 PVD detection level set to 2.8V
 *     @arg PWR_PVDRANGRE_2V9 PVD detection level set to 2.9V
 */
void PWR_PvdRangeConfig(uint32_t PWR_PVDLevel)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));
    tmpregister = PWR->CTRL;
    /* Clear PRS[7:5] bits */
    tmpregister &= CTRL_PRS_MASK;
    /* Set PRS[7:5] bits according to PWR_PVDLevel value */
    tmpregister |= PWR_PVDLevel;
    /* Store the new value */
    PWR->CTRL = tmpregister;
}

/**
 * @brief  Enables or disables the WakeUp Pin functionality.
 * @param Cmd new state of the WakeUp Pin functionality.
 *   This parameter can be: ENABLE or DISABLE.
 */
void PWR_WakeUpPinEnable(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    *(__IO uint32_t*)CTRLSTS_WKUPEN_BB = (uint32_t)Cmd;
}

/**
 * @brief  Enters SLEEP mode.
 * @param SLEEPONEXIT specifies the SLEEPONEXIT state in SLEEP mode.
 *   This parameter can be one of the following values:
 *     @arg 0 SLEEP mode with SLEEPONEXIT disable
 *     @arg 1 SLEEP mode with SLEEPONEXIT enable
 * @param PWR_STOPEntry specifies if SLEEP mode in entered with WFI or WFE instruction.
 *   This parameter can be one of the following values:
 *     @arg PWR_STOPENTRY_WFI enter SLEEP mode with WFI instruction
 *     @arg PWR_STOPENTRY_WFE enter SLEEP mode with WFE instruction
 */
void PWR_EnterSLEEPMode(uint8_t SLEEPONEXIT, uint8_t PWR_STOPEntry)
{
    //  uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));

    /* CLEAR SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t) ~((uint32_t)SCB_SCR_SLEEPDEEP);

    /* Select SLEEPONEXIT mode entry --------------------------------------------------*/
    if (SLEEPONEXIT == 1)
    {
        /* the MCU enters Sleep mode as soon as it exits the lowest priority INTSTS */
        SCB->SCR |= SCB_SCR_SLEEPONEXIT;
    }
    else if (SLEEPONEXIT == 0)
    {
        /* Sleep-now */
        SCB->SCR &= (uint32_t) ~((uint32_t)SCB_SCR_SLEEPONEXIT);
    }

    /* Select SLEEP mode entry --------------------------------------------------*/
    if (PWR_STOPEntry == PWR_STOPENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }
}

/**
 * @brief  Enters STOP mode.
 * @param PWR_Regulator specifies the regulator state in STOP mode.
 *   This parameter can be one of the following values:
 *     @arg PWR_REGULATOR_ON STOP mode with regulator ON
 *     @arg PWR_REGULATOR_LOWPOWER STOP mode with regulator in low power mode
 * @param PWR_STOPEntry specifies if STOP mode in entered with WFI or WFE instruction.
 *   This parameter can be one of the following values:
 *     @arg PWR_STOPENTRY_WFI enter STOP mode with WFI instruction
 *     @arg PWR_STOPENTRY_WFE enter STOP mode with WFE instruction
 */
void PWR_EnterStopState(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_PWR_REGULATOR(PWR_Regulator));
    assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));

    /* Select the regulator state in STOP mode ---------------------------------*/
    tmpregister = PWR->CTRL;
    /* Clear PDS and LPS bits */
    tmpregister &= CTRL_DS_MASK;
    /* Set LPS bit according to PWR_Regulator value */
    tmpregister |= PWR_Regulator;
    /* Store the new value */
    PWR->CTRL = tmpregister;
    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP;

    /* Select STOP mode entry --------------------------------------------------*/
    if (PWR_STOPEntry == PWR_STOPENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }

    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t) ~((uint32_t)SCB_SCR_SLEEPDEEP);
}

/**
 * @brief  Enters STOP2 mode.
 * @param PWR_STOPEntry specifies if STOP2 mode in entered with WFI or WFE instruction.
 *   This parameter can be one of the following values:
 *     @arg PWR_STOPENTRY_WFI enter STOP2 mode with WFI instruction
 *     @arg PWR_STOPENTRY_WFE enter STOP2 mode with WFE instruction
 */
void PWR_EnterSTOP2Mode(uint8_t PWR_STOPEntry)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));

    /* Select the regulator state in STOP2 mode ---------------------------------*/
    tmpregister = PWR->CTRL;
    /* Clear PDS and LPS bits */
    tmpregister &= CTRL_DS_MASK;
    /* Store the new value */
    PWR->CTRL = tmpregister;
    /*STOP2 sleep mode control-stop2s*/
    PWR->CTRL2 |= PWR_CTRL2_STOP2S;
    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP;
    // PWR_CTRL2.BIT0 STOP2S need?
    /* Select STOP mode entry --------------------------------------------------*/
    if (PWR_STOPEntry == PWR_STOPENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }

    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t) ~((uint32_t)SCB_SCR_SLEEPDEEP);
}

/**
 * @brief  Enters STANDBY mode.
 */
void PWR_EnterStandbyState(void)
{
    /* Clear Wake-up flag */
    PWR->CTRL |= PWR_CTRL_CWKUP;
    /* Clear PDS and LPS bits */
    PWR->CTRL &= CTRL_DS_MASK;
    /* Select STANDBY mode */
    PWR->CTRL |= PWR_CTRL_PDS;
    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP;
/* This option is used to ensure that store operations are completed */
#if defined(__CC_ARM)
    __force_stores();
#endif
    /* Request Wait For Interrupt */
    __WFI();
}

/**
 * @brief  Checks whether the specified PWR flag is set or not.
 * @param PWR_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg PWR_WU_FLAG Wake Up flag
 *     @arg PWR_SB_FLAG StandBy flag
 *     @arg PWR_PVDO_FLAG PVD Output
 *     @arg PWR_VBATF_FLAG VBAT flag
 * @return The new state of PWR_FLAG (SET or RESET).
 */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_PWR_GET_FLAG(PWR_FLAG));

    if ((PWR->CTRLSTS & PWR_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the flag status */
    return bitstatus;
}

/**
 * @brief  Clears the PWR's pending flags.
 * @param PWR_FLAG specifies the flag to clear.
 *   This parameter can be one of the following values:
 *     @arg PWR_WU_FLAG Wake Up flag
 *     @arg PWR_SB_FLAG StandBy and VBAT flag
 */
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
    /* Check the parameters */
    assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));

    PWR->CTRL |= PWR_FLAG << 2;
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
