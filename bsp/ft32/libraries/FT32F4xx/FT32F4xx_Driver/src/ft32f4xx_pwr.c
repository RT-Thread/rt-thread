/**
  ******************************************************************************
  * @file               ft32f4xx_pwr.c
  * @author             Rwang
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the Power Controller (PWR) peripheral:
  *                 + Backup Domain Access
  *                 + PVD configuration
  *                 + WakeUp pins configuration
  *                 + Low Power modes configuration
  *                 + Flags management
  *                 + Vbat charge configuration
  * @version            V1.0.0
  * @data                   2025-03-24
    ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_pwr.h"
#include "ft32f4xx_rcc.h"


/* ------------------ PWR registers bit mask ------------------------ */

/* CR register bit mask */
#define CR_VBRS_MASK              ((uint32_t)0x00080000)
#define CR_VOS_MASK               ((uint32_t)0x00006000)
#define CR_PLSR_MASK              ((uint32_t)0x00000E00)
#define CR_PLSF_MASK              ((uint32_t)0x000001C0)
#define SCB_SCR_SLEEPONEXIT       ((uint32_t)0x00000002)
#define SCB_SCR_SLEEPDEEP         ((uint32_t)0x00000004)



/**
  * @brief  Deinitializes the PWR peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void PWR_DeInit(void)
{
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, DISABLE);
}
/**
  * @}
  */


/**
  * @brief  Enables or disables vbat charge
  * @note   Vbat will be charge by external resistance
  * @param  NewState: new state of the access to the Backup domain registers.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_VbatCharge(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Vbat charge */
        PWR->CR |=  PWR_CR_VBE;
    }
    else
    {
        /* Disable the Vbat Charge*/
        PWR->CR &= ~PWR_CR_VBE;
    }
}
/**
  * @}
  */


/**
  * @brief  Configures the Vbat Charge Resistance.
  * @param  PWR_VbatRes: specifies the Vbat Resistance detection
  *          This parameter can be one of the following values:
  *             @arg PWR_Vbat_Charge_5k
  *             @arg PWR_Vbat_Charge_1point5k
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each
  *         detection level.
  * @retval None
  */
void PWR_VbatResConfig(uint32_t PWR_VbatRes)
{
    /* Check the parameters */
    assert_param(IS_PWR_VBAT_RES(PWR_VbatRes));

    /* Set Vbrs and Vbrs bit according to PWR_VbatRes value */
    if (PWR_VbatRes == PWR_Vbat_Charge_5k)
    {
        PWR->CR &= ~PWR_CR_VBRS;
    }
    else
    {
        PWR->CR |=  PWR_CR_VBRS;
    }
}
/**
  * @}
  */


/**
  * @brief  Configures the Main Voltage Regulator.
  * @param  PWR_VOSLevel: specifies the Main Voltage Regulator detection
  *          This parameter can be one of the following values:
  *             @arg PWR_VosLevel_0
  *             @arg PWR_VosLevel_1
  *             @arg PWR_VosLevel_2
  *             @arg PWR_VosLevel_3
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each
  *         detection level.
  * @retval None
  */
void PWR_VosLevelConfig(uint32_t PWR_VosLevel)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_PWR_VOS_LEVEL(PWR_VosLevel));

    tmpreg =   PWR->CR;

    /* Clear vos bits */
    tmpreg &= ~CR_VOS_MASK;

    /* Set vos and vos bits according to PWR_VosLevel value */
    tmpreg |=  PWR_VosLevel;

    /* Store the new value */
    PWR->CR =  tmpreg;
}
/**
  * @}
  */


/**
  * @brief  Enables or disables access to the Backup domain registers.
  * @note   If the HSE divided by 32 is used as the RTC clock, the
  *         Backup Domain Access should be kept enabled.
  * @param  NewState: new state of the access to the Backup domain registers.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_BackupAccessCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Backup Domain Access */
        PWR->CR |=  PWR_CR_DBP;
    }
    else
    {
        /* Disable the Backup Domain Access */
        PWR->CR &= ~PWR_CR_DBP;
    }
}
/**
  * @}
  */


/**
  * @brief  Enables or disables the Power Voltage Detector(PVD).
  * @param  NewState: new state of the PVD.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_PVDEnable(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the PVD */
        PWR->CR |=  PWR_CR_PVDE;
    }
    else
    {
        /* Disable the PVD */
        PWR->CR &= ~PWR_CR_PVDE;
    }
}
/**
  * @}
  */


/**
  * @brief  Configures the rise voltage threshold detected by the Power Voltage Detector(PVD).
  * @param  PWR_PVDRLevel: specifies the PVD rise detection level
  *          This parameter can be one of the following values:
  *             @arg PWR_PVDRLevel_0
  *             @arg PWR_PVDRLevel_1
  *             @arg PWR_PVDRLevel_2
  *             @arg PWR_PVDRLevel_3
  *             @arg PWR_PVDRLevel_4
  *             @arg PWR_PVDRLevel_5
  *             @arg PWR_PVDRLevel_6
  *             @arg PWR_PVDRLevel_7
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each
  *         detection rise level.
  * @retval None
  */
void PWR_PVDRLevelConfig(uint32_t PWR_PVDRLevel)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_PWR_PVDR_LEVEL(PWR_PVDRLevel));

    tmpreg  =  PWR->CR;

    /* Clear PVDR bits */
    tmpreg &= ~CR_PLSR_MASK;

    /* Set PVDR and PVDR bits according to PWR_PVDRLevel value */
    tmpreg |=  PWR_PVDRLevel;

    /* Store the new value */
    PWR->CR =  tmpreg;
}
/**
  * @}
  */


/**
  * @brief  Configures the fall voltage threshold detected by the Power Voltage Detector(PVD).
  * @param  PWR_PVDRLevel: specifies the PVD fall detection level
  *          This parameter can be one of the following values:
  *             @arg PWR_PVDFLevel_0
  *             @arg PWR_PVDFLevel_1
  *             @arg PWR_PVDFLevel_2
  *             @arg PWR_PVDFLevel_3
  *             @arg PWR_PVDFLevel_4
  *             @arg PWR_PVDFLevel_5
  *             @arg PWR_PVDFLevel_6
  *             @arg PWR_PVDFLevel_7
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each
  *         detection fall level.
  * @retval None
  */
void PWR_PVDFLevelConfig(uint32_t PWR_PVDFLevel)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_PWR_PVDF_LEVEL(PWR_PVDFLevel));

    tmpreg  =  PWR->CR;

    /* Clear PVDF bits */
    tmpreg &= ~CR_PLSF_MASK;

    /* Set PVDF and PVDF bits according to PWR_PVDFLevel value */
    tmpreg |=  PWR_PVDFLevel;

    /* Store the new value */
    PWR->CR =  tmpreg;
}
/**
  * @}
  */


/**
  * @brief  Enables or Disable the Power Off Reset in standby(Pdroff).
  * @param  NewState: new state of the Pdroff.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_PdroffEnable(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Disable the PDR in standby*/
        PWR->CR |=  PWR_CR_PDROFF;
    }
    else
    {
        /* Enable  the PVD in standby*/
        PWR->CR &= ~PWR_CR_PDROFF;
    }
}
/**
  * @}
  */


/**
  * @brief  Enables or disables the WakeUp Pin functionality.
  * @param  PWR_WakeUpPin: specifies the WakeUpPin.
  *          This parameter can be one of the following values
  *             @arg PWR_WakeUpPin_1
  *             @arg PWR_WakeUpPin_2
  *             @arg PWR_WakeUpPin_3
  * @param  NewState: new state of the WakeUp Pin functionality.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_PWR_WAKEUP_PIN(PWR_WakeUpPin));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the EWUPx pin */
        PWR->CSR |=  PWR_WakeUpPin;
    }
    else
    {
        /* Disable the EWUPx pin */
        PWR->CSR &= ~PWR_WakeUpPin;
    }
}
/**
  * @}
  */


/**
  * @brief  Enables or Disable the Backup Regulator Enable(BRE).
  * @param  NewState: new state of the Bre.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWR_BreEnable(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Backup Regulator*/
        PWR->CSR |=  PWR_CSR_BRE;
    }
    else
    {
        /* Disable the Backup Regulator*/
        PWR->CSR &= ~PWR_CSR_BRE;
    }
}
/**
  * @}
  */


/**
  * @brief  Enters Sleep mode.
  * @note   In Sleep mode, all I/O pins keep the same state as in Run mode.
  * @param  PWR_SLEEPEntry: specifies if SLEEP mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *             @arg PWR_SleepEntry_WFI: enter SLEEP mode with WFI instruction
  *             @arg PWR_SleepEntry_WFE: enter SLEEP mode with WFE instruction
  *             @arg PWR_SleepEntry_SLEEPONEXIT: enter SLEEP mode while mcu exit the lowest priority interrupt
  * @retval None
  */
void PWR_EnterSleepMode(uint8_t PWR_SleepEntry)
{
    /* Check the parameters */
    assert_param(IS_PWR_SLEEP_ENTRY(PWR_SleepEntry));

    /* Clear SLEEPDEEP bit of Cortex-M0 System Control Register */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP;

    /* Select SLEEP mode entry */
    if (PWR_SleepEntry == PWR_SleepEntry_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else if (PWR_SleepEntry == PWR_SleepEntry_WFE)
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }
    else if (PWR_SleepEntry == PWR_SleepEntry_SLEEPONEXIT)
    {
        /* Set SLEEP on exit bit of Cortex-M0 System Control Register */
        SCB->SCR |= SCB_SCR_SLEEPONEXIT;
    }
}

/**
  * @brief  Enters STOP mode.
  * @note   In Stop mode, all I/O pins keep the same state as in Run mode.
  * @note   When exiting Stop mode by issuing an interrupt or a wakeup event,
  *         the HSI RC oscillator is selected as system clock.
  * @note   When the voltage regulator operates in low power mode, an additional
  *         startup delay is incurred when waking up from Stop mode.
  *         By keeping the internal regulator ON during Stop mode, the consumption
  *         is higher although the startup time is reduced.
  * @param  PWR_Regulator: specifies the regulator state in STOP mode.
  *         This parameter can be one of the following values:
  *             @arg PWR_Regulator_ON: STOP mode with regulator ON
  *             @arg PWR_Regulator_LowPower: STOP mode with regulator in low power mode
  * @param  PWR_STOPEntry: specifies if STOP mode in entered with WFI or WFE instruction.
  *         This parameter can be one of the following values:
  *             @arg PWR_StopEntry_WFI: enter STOP mode with WFI instruction
  *             @arg PWR_StopEntry_WFE: enter STOP mode with WFE instruction
  * @retval None
  */
void PWR_EnterStopMode(uint32_t PWR_Regulator, uint8_t PWR_StopEntry)
{
    /* Check the parameters */
    assert_param(IS_PWR_REGULATOR(PWR_Regulator));
    assert_param(IS_PWR_STOP_ENTRY(PWR_StopEntry));

    /* Select Regulator status in stop mode */
    if (PWR_Regulator == PWR_Regulator_ON)
    {
        /* Clear LPDS bit make Regulator open in stop mode */
        PWR->CR &= ~PWR_CR_LPDS;
    }
    else if (PWR_Regulator == PWR_Regulator_LowPower)
    {
        /* Set   LPDS bit make Regulator Lowerpower in stop mode */
        PWR->CR |=  PWR_CR_LPDS;
    }

    /* Select STOP mode entry */
    if (PWR_StopEntry == PWR_StopEntry_WFI)
    {
        /* Set SLEEPDEEP bit of Cortex System Control Register */
        SCB->SCR |= SCB_SCR_SLEEPDEEP;
        /* Request Wait For Interrupt */
        __WFI();
    }
    else if (PWR_StopEntry == PWR_StopEntry_WFE)
    {
        /* Set SLEEPDEEP bit of Cortex System Control Register */
        SCB->SCR |= SCB_SCR_SLEEPDEEP;
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }
}

/**
  * @brief  Enters STANDBY mode.
  * @note   In Standby mode, all I/O pins are high impedance except for:
  *          - Reset pad (still available)
  *          - RTC_AF1 pin (PC13) if configured for Wakeup pin 2 (WKUP2), tamper,
  *             time-stamp, RTC Alarm out, or RTC clock calibration out.
  *          - WKUP pin 1 (PA0) if enabled.
  * @param  PWR_StandbyEntry: specifies if STOP mode in entered with WFI or WFE instruction.
  *         This parameter can be one of the following values:
  *             @arg PWR_StandbyEntry_WFI: enter STANDBY mode with WFI instruction
  *             @arg PWR_StandbyEntry_WFE: enter STANDBY mode with WFE instruction
  * @note The Wakeup flag (WUF) need to be cleared at application level before to call this function
  * @param  None
  * @retval None
  */
void PWR_EnterStandbyMode(uint8_t PWR_StandbyEntry)
{
    assert_param(IS_PWR_STANDBY_ENTRY(PWR_StandbyEntry));

    /* Select STANDBY mode */
    PWR->CR |= PWR_CR_PDDS;

    /* Set SLEEPDEEP bit of Cortex-M0 System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP;

    /* Select Standby mode entry */
    if (PWR_StandbyEntry == PWR_StandbyEntry_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else if (PWR_StandbyEntry == PWR_StandbyEntry_WFE)
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }
}
/**
  * @}
  */

/**
  * @brief  Checks whether the specified PWR flag is set or not.
  * @param  PWR_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *             @arg PWR_FLAG_WU: Wake Up flag. This flag indicates that a wakeup
  *                  event was received from the WKUP pin or from the RTC alarm
  *                  (Alarm A or Alarm B), RTC Tamper event or RTC TimeStamp event
  *             @arg PWR_FLAG_SB: StandBy flag. This flag indicates that the
  *                  system was resumed from Standby mode
  *             @arg PWR_FLAG_PVDO: PVD Output. This flag is valid only if PVD
  *                  is enabled by the PWR_PVDEnable() function.
  *             @arg PWR_FLAG_BRR: Backup regulator ready. This flag is valid
  *                  only if BRE is enabled by the PWR_BreEnable() function.
  *             @arg PWR_FLAG_VREFINTRDY: Internal Voltage Reference Ready flag
  *                  This flag indicates the state of the internal voltage
  *                  reference, VREFINT.
  * @retval The new state of PWR_FLAG (SET or RESET).
  */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_PWR_GET_FLAG(PWR_FLAG));

    if ((PWR->CSR & PWR_FLAG) != (uint32_t)RESET)
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
  * @}
  */


/**
  * @brief  Clears the PWR's pending flags.
  * @param  PWR_FLAG: specifies the flag to clear.
  *          This parameter can be one of the following values:
  *             @arg PWR_FLAG_CWU: Wake Up flag
  *             @arg PWR_FLAG_CSB: StandBy flag
  * @retval None
  */
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
    /* Check the parameters */
    assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));

    if (PWR_FLAG == PWR_FLAG_CWU)
    {
        /*clear wkup flag*/
        PWR->CR |= PWR_FLAG_CWU;
    }
    else if (PWR_FLAG == PWR_FLAG_CWU)
    {
        /*clare standby flag*/
        PWR->CR |= PWR_FLAG_CSB;
    }
}
/**
  * @}
  */


/************************ (C) COPYRIGHT FMD *****END OF FILE****/
