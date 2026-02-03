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
 * @file n32g43x_pwr.c
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32g43x_pwr.h"

/** @addtogroup N32G43x_StdPeriph_Driver
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


void SetSysClock_MSI(void);
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
 * @brief  MR voltage selection.
 * @param voltage value: 1.0V and 1.1V.
 *   This parameter can be: MR_1V0 or MR_1V1.
 */
void PWR_MRconfig(uint8_t voltage)
{
  uint32_t tmpreg = 0;

  tmpreg = PWR->CTRL1;
  /* Clear MRSEL bits */
  tmpreg &= (~PWR_CTRL1_MRSELMASK);
  /* Set voltage*/
  tmpreg |= (uint32_t)(voltage << 9);
  PWR->CTRL1 = tmpreg;
}
/**
 * @brief  Get MR voltage value.
 * @param voltage value: 1.0V and 1.1V.
 * @return The value of voltage.
 */
uint8_t GetMrVoltage(void)
{
  uint8_t tmp = 0;

  tmp = (uint8_t)((PWR->CTRL1 >> 9) & 0x03);//2bits
  return tmp ;
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
    //*(__IO uint32_t*)CTRL_PVDEN_BB = (uint32_t)Cmd; //Can not enable the PVD bit
    PWR->CTRL2 |= Cmd;

}

/**
  * @brief  Configures the voltage threshold detected by the Power Voltage Detector(PVD).
  * @param  PWR_PVDLevel: specifies the PVD detection level
  *   This parameter can be one of the following values:
  *     @arg PWR_CTRL2_PLS1: PVD detection level set to 2.1V
  *     @arg PWR_CTRL2_PLS2: PVD detection level set to 2.25V
  *     @arg PWR_CTRL2_PLS3: PVD detection level set to 2.4V
  *     @arg PWR_CTRL2_PLS4: PVD detection level set to 2.55V
  *     @arg PWR_CTRL2_PLS5: PVD detection level set to 2.7V
  *     @arg PWR_CTRL2_PLS6: PVD detection level set to 2.85V
  *     @arg PWR_CTRL2_PLS7: PVD detection level set to 2.95V
  *     @arg PWR_CTRL2_PLS8: external input analog voltage PVD_IN (compared internally to VREFINT)
  * @retval None
  */
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));
    tmpregister = PWR->CTRL2;
    /* Clear PLS[7:5] bits */
    tmpregister &= (~PWR_CTRL2_PLSMASK);
    /* Set PRS[7:5] bits according to PWR_PVDLevel value */
    tmpregister |= PWR_PVDLevel;
    /* Store the new value */
    PWR->CTRL2 = tmpregister;
}

/**
 * @brief  Enables or disables the WakeUp Pin functionality.
 * @param Pin: which PIN  select to wakeup.
 *   This parameter can be one of the following values:
 *     @arg WAKEUP_PIN0
 *     @arg WAKEUP_PIN1
 *     @arg WAKEUP_PIN2
 * @param Cmd new state of the WakeUp Pin functionality.
 *   This parameter can be: ENABLE or DISABLE.
 */
void PWR_WakeUpPinEnable(WAKEUP_PINX WKUP_Pin,FunctionalState Cmd)
{
    uint32_t Temp = 0;
    Temp = PWR->CTRL3;
    if (ENABLE==Cmd)
    {
       Temp &= (~(PWR_CTRL3_WKUP0EN|PWR_CTRL3_WKUP1EN|PWR_CTRL3_WKUP2EN));
       Temp |= (WKUP_Pin);
       PWR->CTRL3 = Temp;
    }
    else
    {
       Temp &= (~(WKUP_Pin));
       PWR->CTRL3 = Temp;
    }
}




/**
  * @brief  Enters SLEEP mode.
  * @param  SLEEPONEXIT: specifies the SLEEPONEXIT state in SLEEP mode.
  *   This parameter can be one of the following values:
  *     @arg 0: SLEEP mode with SLEEPONEXIT disable
  *     @arg 1: SLEEP mode with SLEEPONEXIT enable
  * @param  PWR_STOPEntry: specifies if SLEEP mode in entered with WFI or WFE instruction.
  *   This parameter can be one of the following values:
  *     @arg PWR_SLEEPEntry_WFI: enter SLEEP mode with WFI instruction
  *     @arg PWR_SLEEPEntry_WFE: enter SLEEP mode with WFE instruction
  * @retval None
  */
void PWR_EnterSLEEPMode(uint8_t SLEEPONEXIT, uint8_t PWR_SLEEPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_SLEEP_ENTRY(PWR_SLEEPEntry));

  /* CLEAR SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP);

    /* Select SLEEPONEXIT mode entry --------------------------------------------------*/
  if (SLEEPONEXIT == 1)
  {
    /* the MCU enters Sleep mode as soon as it exits the lowest priority ISR */
    SCB->SCR |= SCB_SCR_SLEEPONEXIT;
  }
  else if (SLEEPONEXIT == 0)
  {
    /* Sleep-now */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPONEXIT);
  }

  /* Select SLEEP mode entry --------------------------------------------------*/
  if (PWR_SLEEPEntry == PWR_SLEEPENTRY_WFI)
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
 * @brief  Enters STOP2 mode.
 * @param PWR_STOPEntry specifies if STOP2 mode in entered with WFI or WFE instruction.
 *   This parameter can be one of the following values:
 *     @arg PWR_STOPENTRY_WFI enter STOP2 mode with WFI instruction
 *     @arg PWR_STOPENTRY_WFE enter STOP2 mode with WFE instruction
 * @param RetentionMode: PWR_CTRL3_RAM1RET or PWR_CTRL3_RAM2RET
 */
void PWR_EnterSTOP2Mode(uint8_t PWR_STOPEntry,uint32_t RetentionMode)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));
  /* Wait MR Voltage Adjust Complete */
  while ((PWR->STS2 &0X2) != 2);
  tmpreg = PWR->CTRL3;
  /* Clear SRAMRET bits */
  tmpreg &= (~PWR_CTRL3_RAMRETMASK);
  /* Set SRAM1/2 select */
  tmpreg |= RetentionMode;
  PWR->CTRL3 = tmpreg;
  /* Select the regulator state in STOP2 mode ---------------------------------*/
  tmpreg = PWR->CTRL1;
  /* Clear LPMS bits */
  tmpreg &= (~PWR_CTRL1_LPMSELMASK);
  /* Set stop2 mode select */
  tmpreg |= PWR_CTRL1_STOP2;
  /* Store the new value */
  PWR->CTRL1 = tmpreg;
  /*Clear PWR_CTRL3_PBDTSTP2 for BOR always on*/
  tmpreg = PWR->CTRL3;
  tmpreg &= (~PWR_CTRL3_PBDTSTP2);
  PWR->CTRL3 = tmpreg;
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP;

  /* Select STOP mode entry --------------------------------------------------*/
  if (PWR_STOPEntry ==  PWR_STOPENTRY_WFI)
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
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP);
}


/**
  * @brief  Enters Low power run mode.
  * @param
  *     @arg
  *     @arg
  * @retval None
  */
void PWR_EnterLowPowerRunMode(void)
{
    uint32_t tmpreg = 0;

    SetSysClock_MSI();
    FLASH_SetLatency(FLASH_LATENCY_2);    //Configure the Flash read latency to be grater than 2, so LVE/SE timing requirement is guaranteed
    //config FLASH enter the low power voltage mode
    FLASH->AC |= FLASH_AC_LVMEN;
    while ((FLASH->AC & FLASH_AC_LVMF) != FLASH_AC_LVMF);
    FLASH_SetLatency(FLASH_LATENCY_0);    //Configure the latency of Flash read cycle to proper value which depends on the Flash read access time.

    _SetLprunSramVoltage(0);
    _SetBandGapMode(0);
    _SetPvdBorMode(0);
    /* Select the regulator state in LPRUN mode ---------------------------------*/
    tmpreg = PWR->CTRL1;
    /* Clear LPMS bits */
    tmpreg &= (~PWR_CTRL1_LPMSELMASK);
    /* Set lpr to run the main power domain*/
    tmpreg |= PWR_CTRL1_LPREN;
    /* Store the new value */
    PWR->CTRL1 = tmpreg;
    /*Clear PWR_CTRL3_PBDTLPR for BOR always on*/
    tmpreg = PWR->CTRL3;
    tmpreg &= (~PWR_CTRL3_PBDTLPR);
    PWR->CTRL3 = tmpreg;
    while ((PWR->STS2 &PWR_STS2_LPRUNF) != 0);//LPRCNT flag ready
}

/**
  * @brief  Enters Low power run mode.
  * @param
  *     @arg
  *     @arg
  * @retval None
  */
void PWR_ExitLowPowerRunMode(void)
{
    PWR->CTRL1 &= ~PWR_CTRL1_LPREN;
    while ((PWR->STS2 &PWR_STS2_LPRUNF) != PWR_STS2_LPRUNF);
    FLASH_SetLatency(FLASH_LATENCY_2);    //Configure the Flash read latency to be grater than 2, so LVE/SE timing requirement is guaranteed
    FLASH->AC &= ~FLASH_AC_LVMEN;                  //clear LVMREQ
    while ((FLASH->AC &FLASH_AC_LVMF) != 0);   //wait LVE is deasserted by polling the LVMVLD bit

    FLASH_SetLatency(FLASH_LATENCY_0);    //Configure the latency of Flash read cycle to proper value which depends on the Flash read access time.
}

/**
  * @brief  Enters LP_SLEEP mode.
  * @param  SLEEPONEXIT: specifies the SLEEPONEXIT state in SLEEP mode.
  *   This parameter can be one of the following values:
  *     @arg 0: SLEEP mode with SLEEPONEXIT disable
  *     @arg 1: SLEEP mode with SLEEPONEXIT enable
  * @param  PWR_STOPEntry: specifies if SLEEP mode in entered with WFI or WFE instruction.
  *   This parameter can be one of the following values:
  *     @arg PWR_SLEEPEntry_WFI: enter SLEEP mode with WFI instruction
  *     @arg PWR_SLEEPEntry_WFE: enter SLEEP mode with WFE instruction
  * @retval None
  */
void PWR_EnterLowPowerSleepMode(uint8_t SLEEPONEXIT, uint8_t PWR_SLEEPEntry)
{
  PWR_EnterLowPowerRunMode();
  PWR_EnterSLEEPMode(SLEEPONEXIT, PWR_SLEEPEntry);
}

 /**
  * @brief  Enters STANDBY mode.
  * @param  PWR_STANDBYEntry: specifies if STANDBY mode in entered with WFI or WFE instruction.
  *   This parameter can be one of the following values:
  *     @arg PWR_STANDBYEntry_WFI: enter STANDBY mode with WFI instruction
  *     @arg PWR_CTRL3_RAM2RET: SRAM2 whether to retention
  * @retval None
  */
void PWR_EnterSTANDBYMode(uint8_t PWR_STANDBYEntry,uint32_t Sam2Ret)
{
    uint32_t tmpreg;
    /* Clear Wake-up flag */
    PWR->STSCLR |= PWR_STSCLR_CLRWKUP0;
    PWR->STSCLR |= PWR_STSCLR_CLRWKUP1;
    PWR->STSCLR |= PWR_STSCLR_CLRWKUP2;
    tmpreg = PWR->CTRL3;
    /* Clear SRAMRET bits */
    tmpreg &= (~PWR_CTRL3_RAMRETMASK);
    /* Set SRAM1/2 select */
    tmpreg |= Sam2Ret;
    PWR->CTRL3 = tmpreg;

    tmpreg = PWR->CTRL1;
    /* Clear LPMS bits */
    tmpreg &= (~PWR_CTRL1_LPMSELMASK);
    /* Select STANDBY mode */
    tmpreg |= PWR_CTRL1_STANDBY;
    PWR->CTRL1 = tmpreg;
    /*Clear PWR_CTRL3_PBDTSTBY for BOR always on*/
    tmpreg = PWR->CTRL3;
    tmpreg &= (~PWR_CTRL3_PBDTSTBY);
    PWR->CTRL3 = tmpreg;
    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP;
/* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM   )
  __force_stores();
#endif
 /* Select STANDBY mode entry --------------------------------------------------*/
  if (PWR_STANDBYEntry == PWR_STOPENTRY_WFI)
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
  * @brief  Checks whether the specified PWR flag is set or not.
  * @param  PWR_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg PWR_WKUP0_FLAG/PWR_WKUP1_FLAG/PWR_WKUP2_FLAG: Wake Up flag
  *     @arg PWR_STBY_FLAG: StandBy flag
  *     @arg PWR_LPRUN_FLAG: low power work flag
  *     @arg PWR_MR_FLAG: MR work statue flag
  *     @arg PWR_PVDO_FLAG: PVD output flag
  * @retval The new state of PWR_FLAG (SET or RESET).
  */
FlagStatus PWR_GetFlagStatus(uint8_t STS,uint32_t PWR_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_PWR_GET_FLAG(PWR_FLAG));
  if (STS == 1)
    {
        if ((PWR->STS1 & PWR_FLAG) != (uint32_t)RESET)
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
        if ((PWR->STS2 & PWR_FLAG) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }

    }

  /* Return the flag status */
  return bitstatus;
}

/**
 * @brief  Clears the PWR's pending flags.
 * @param PWR_FLAG specifies the flag to clear.
 *   This parameter can be one of the following values:
  *     @arg PWR_WKUP1_FLAG/PWR_WKUP2_FLAG/PWR_WKUP3_FLAG: Wake Up flag
  *     @arg PWR_STBY_FLAG: StandBy flag
 */
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
    /* Check the parameters */
    assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));

    PWR->STSCLR |=  PWR_FLAG ;
}


/**
 * @brief  set system clock with MSI.
 * @param void.
 */
void SetSysClock_MSI(void)
{
     RCC_DeInit();

    if (RESET == RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_MSIRD))
    {
        /* Enable MSI and Config Clock */
        RCC_ConfigMsi(RCC_MSI_ENABLE, RCC_MSI_RANGE_4M);
        /* Waits for MSI start-up */
        while (SUCCESS != RCC_WaitMsiStable());
    }

    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufSet(FLASH_PrefetchBuf_EN);

    /* Select MSI as system clock source */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_MSI);

    /* Wait till MSI is used as system clock source */
    while (RCC_GetSysclkSrc() != 0x00)
    {
    }

    /* Flash 0 wait state */
    //FLASH_SetLatency(FLASH_LATENCY_0);

    /* HCLK = SYSCLK */
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);

    /* PCLK2 = HCLK */
    RCC_ConfigPclk2(RCC_HCLK_DIV1);

    /* PCLK1 = HCLK */
    RCC_ConfigPclk1(RCC_HCLK_DIV1);
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
