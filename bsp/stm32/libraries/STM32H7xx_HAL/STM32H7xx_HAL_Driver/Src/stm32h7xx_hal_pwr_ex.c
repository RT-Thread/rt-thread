/**
  ******************************************************************************
  * @file    stm32h7xx_hal_pwr_ex.c
  * @author  MCD Application Team
  * @brief   Extended PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of PWR extension peripheral:
  *           + Peripheral Extended features functions
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @defgroup PWREx PWREx
  * @brief PWR Extended HAL module driver
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup PWREx_Private_Constants
  * @{
  */

/** @defgroup PWREx_AVD_Mode_Mask PWR Extended AVD Mode Mask
  * @{
  */
#define AVD_MODE_IT              ((uint32_t)0x00010000U)
#define AVD_MODE_EVT             ((uint32_t)0x00020000U)
#define AVD_RISING_EDGE          ((uint32_t)0x00000001U)
#define AVD_FALLING_EDGE         ((uint32_t)0x00000002U)
#define AVD_RISING_FALLING_EDGE  ((uint32_t)0x00000003U)
/**
  * @}
  */

/** @defgroup PWREx_REG_SET_TIMEOUT PWR Extended Flag Setting Time Out Value
  * @{
  */
#define PWR_FLAG_SETTING_DELAY_US  ((uint32_t)1000U)
/**
  * @}
  */

/** @defgroup PWREx_WakeUp_Pins_Offsets PWREx Wake-Up Pins masks and offsets
  * @{
  */
/* Wake-Up Pins EXTI register mask */
#define PWR_EXTI_WAKEUP_PINS_MASK  (uint32_t)(EXTI_IMR2_IM55 | EXTI_IMR2_IM56 | \
                                              EXTI_IMR2_IM57 | EXTI_IMR2_IM58 | \
                                              EXTI_IMR2_IM59 | EXTI_IMR2_IM60)

/* Wake-Up Pins PWR Pin Pull shift offsets */
#define PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET      2U
/**
  * @}
  */


/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup PWREx_Exported_Functions PWREx Exported Functions
  * @{
  */

/** @defgroup PWREx_Exported_Functions_Group1 Power supply control functions
  * @brief    Power supply control functions
  *
@verbatim

 ===============================================================================
                 ##### Power supply control functions #####
 ===============================================================================

    *** Power supply configuration ***
    ==================================
    [..]
      When the system is powered on, the POR monitors VDD supply. Once VDD is above the
      POR threshold level, the voltage regulator is enabled in the default supply
      configuration:
      (+) The Voltage converter output level is set at 1.0 V in accordance with the VOS3
          level configured in PWR D3 domain control register (PWR_D3CR).
      (+) The system is kept in reset mode as long as VCORE is not ok.
      (+) Once VCORE is ok, the system is taken out of reset and the HSI oscillator is enabled.
      (+) Once the oscillator is stable, the system is initialized: Flash memory and option
          bytes are loaded and the CPU starts in Run* mode.
      (+) The software shall then initialize the system including supply configuration
          programming using the HAL_PWREx_ConfigSupply(SupplySource) with:
       (++) SupplySource:
        (+++) PWR_LDO_SUPPLY: VCORE Power Domains are supplied from the LDO according to
                              VOS. LDO power mode (Main, LP, Off) will follow system low-power
                              modes.
        (+++) PWR_EXTERNAL_SOURCE_SUPPLY: VCORE supplied from external source and LDO bypassed,
                                          voltage monitoring still active.
      (+) Once the supply configuration  has been configured, the HAL_PWREx_ConfigSupply
          function checks the ACTVOSRDY bit in PWR control status register 1 (PWR_CSR1)
          to guarantee a valid voltage levels:
       (++) As long as ACTVOSRDY indicates that voltage levels are invalid, the system is in
            limited Run* mode, write accesses to the RAMs are not permitted and VOS shall
            not be changed.
       (++) Once ACTVOSRDY indicates that voltage levels are valid, the system is in normal
            Run mode, write accesses to RAMs are allowed and VOS can be changed.

@endverbatim
  * @{
  */

#if defined(SMPS)
/**
  * @brief  Configure the system Power Supply.
  * @param  SupplySource: Specifies the Power Supply source to set after a system startup.
  *         This parameter can be one of the following values:
  *            @arg PWR_LDO_SUPPLY                      The LDO regulator supplies the Vcore Power Domains.
  *                                                     The SMPS regulator is Bypassed.
  *
  *            @arg PWR_DIRECT_SMPS_SUPPLY              The SMPS supplies the Vcore Power Domains.
  *                                                     The LDO is Bypassed.
  *
  *            @arg PWR_SMPS_1V8_SUPPLIES_LDO           The SMPS 1.8V output supplies the LDO.
  *                                                     The Vcore Power Domains are supplied from the LDO.
  *
  *            @arg PWR_SMPS_2V5_SUPPLIES_LDO           The SMPS 2.5V output supplies the LDO.
  *                                                     The Vcore Power Domains are supplied from the LDO.
  *
  *            @arg PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO   The SMPS 1.8V output supplies external circuits and the LDO.
  *                                                     The Vcore Power Domains are supplied from the LDO.
  *
  *            @arg PWR_SMPS_2V5_SUPPLIES_EXT_AND_LDO   The SMPS 2.5V output supplies external circuits and the LDO.
  *                                                     The Vcore Power Domains are supplied from the LDO.
  *
  *            @arg PWR_SMPS_1V8_SUPPLIES_EXT           The SMPS 1.8V output supplies external circuits.
  *                                                     The LDO is Bypassed.
  *                                                     The Vcore Power Domains are supplied from external source.
  *
  *            @arg PWR_SMPS_2V5_SUPPLIES_EXT           The SMPS 2.5V output supplies external circuits.
  *                                                     The LDO is Bypassed.
  *                                                     The Vcore Power Domains are supplied from external source.
  *
  *            @arg PWR_EXTERNAL_SOURCE_SUPPLY          The SMPS and the LDO are Bypassed.
  *                                                     The Vcore Power Domains are supplied from external source.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_PWREx_ConfigSupply(uint32_t SupplySource)
{
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_PWR_SUPPLY(SupplySource));

  if((PWR->CR3 & (PWR_CR3_SMPSEN | PWR_CR3_LDOEN | PWR_CR3_BYPASS)) != (PWR_CR3_SMPSEN | PWR_CR3_LDOEN))
  {
    if((PWR->CR3 & PWR_SUPPLY_CONFIG_MASK) != SupplySource)
    {
      /* Supply configuration update locked, can't apply a new regulator config */
      return HAL_ERROR;
    }
  }

  /* Set the power supply configuration */
  MODIFY_REG(PWR->CR3, PWR_SUPPLY_CONFIG_MASK, SupplySource);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait till voltage level flag is set */
  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_ACTVOSRDY))
  {
    if((HAL_GetTick() - tickstart ) > PWR_FLAG_SETTING_DELAY_US)
    {
      return HAL_TIMEOUT;
    }
  }

  /* When the SMPS supplies external circuits verify that SDEXTRDY flag is set */
  if((SupplySource == PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO) ||
     (SupplySource == PWR_SMPS_2V5_SUPPLIES_EXT_AND_LDO) ||
     (SupplySource == PWR_SMPS_1V8_SUPPLIES_EXT) ||
     (SupplySource == PWR_SMPS_2V5_SUPPLIES_EXT))
  {
    /* Get tick */
    tickstart = HAL_GetTick();

    /* Wait till SMPS external supply ready flag is set */
    while(!__HAL_PWR_GET_FLAG(PWR_FLAG_SMPSEXTRDY))
    {
      if((HAL_GetTick() - tickstart ) > PWR_FLAG_SETTING_DELAY_US)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  return HAL_OK;
}
#else
/**
  * @brief  Configure the system Power Supply.
  * @param  SupplySource: Specifies the Power Supply source to set after a system startup.
  *         This parameter can be one of the following values:
  *            @arg PWR_LDO_SUPPLY                      The LDO regulator supplies the Vcore Power Domains.
  *
  *            @arg PWR_EXTERNAL_SOURCE_SUPPLY          The LDO regulator is Bypassed.
  *                                                     The Vcore Power Domains are supplied from external source.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_PWREx_ConfigSupply(uint32_t SupplySource)
{
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_PWR_SUPPLY(SupplySource));

  if(!__HAL_PWR_GET_FLAG(PWR_FLAG_SCUEN))
  {
    if((PWR->CR3 & PWR_SUPPLY_CONFIG_MASK) != SupplySource)
    {
      /* Supply configuration update locked, can't apply a new regulator config */
      return HAL_ERROR;
    }
  }

  /* Set the power supply configuration */
  MODIFY_REG(PWR->CR3, PWR_SUPPLY_CONFIG_MASK, SupplySource);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait till voltage level flag is set */
  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_ACTVOSRDY))
  {
    if((HAL_GetTick() - tickstart ) > PWR_FLAG_SETTING_DELAY_US)
    {
      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}
#endif /*SMPS*/


/**
  * @brief  Get the power supply configuration.
  * @retval The supply configuration.
  */
uint32_t  HAL_PWREx_GetSupplyConfig(void)
{
  return (PWR->CR3 & PWR_SUPPLY_CONFIG_MASK);
}

/**
  * @brief  Configure the main internal regulator output voltage.
  * @param  VoltageScaling: Specifies the regulator output voltage to achieve
  *         a tradeoff between performance and power consumption.
  *          This parameter can be one of the following values:
  *            @arg PWR_REGULATOR_VOLTAGE_SCALE1: Regulator voltage output range 1 mode.
  *            @arg PWR_REGULATOR_VOLTAGE_SCALE2: Regulator voltage output range 2 mode.
  *            @arg PWR_REGULATOR_VOLTAGE_SCALE3: Regulator voltage output range 3 mode.
  * @note   When moving from Range 1 to Range 2, the system frequency must be decreased
  *         before calling HAL_PWREx_ControlVoltageScaling() API.
  *         When moving from Range 2 to Range 1, the system frequency can be increased
  *         after calling HAL_PWREx_ControlVoltageScaling() API.
  * @note   When moving from a Range to an other one, the API waits for VOSRDY flag to be
  *         set before returning the status. If the flag is not set within 1000 microseconds,
  *         HAL_TIMEOUT status is reported.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling)
{
  uint32_t tickstart;

  assert_param(IS_PWR_REGULATOR_VOLTAGE(VoltageScaling));

  /* Set the voltage range */
  MODIFY_REG(PWR->D3CR, PWR_D3CR_VOS, VoltageScaling);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait until the VOSRDY flag is set */
  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY))
  {
    if((HAL_GetTick() - tickstart ) > PWR_FLAG_SETTING_DELAY_US)
    {
      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Get the main internal regulator output voltage.
  *         Reflecting the last VOS value applied to the PMU.
  * @retval The actual applied VOS for VDD11 Voltage Scaling selection.
  */
uint32_t  HAL_PWREx_GetVoltageRange(void)
{
  return (PWR->CSR1 & PWR_CSR1_ACTVOS);
}

/**
  * @brief  Configure the main internal regulator output voltage in STOP mode.
  * @param  VoltageScaling: Specifies the regulator output voltage when the system enters
  *         Stop mode to achieve a tradeoff between performance and power consumption.
  *          This parameter can be one of the following values:
  *            @arg PWR_REGULATOR_SVOS_SCALE3: Regulator voltage output range 3 mode.
  *            @arg PWR_REGULATOR_SVOS_SCALE4: Regulator voltage output range 4 mode.
  *            @arg PWR_REGULATOR_SVOS_SCALE5: Regulator voltage output range 5 mode.
  * @note   The Stop mode voltage scaling for SVOS4 and SVOS5 sets the voltage regulator
  *         in Low-power (LP) mode to further reduce power consumption.
  *         When preselecting SVOS3, the use of the voltage regulator low-power mode (LP)
  *         can be selected by LPDS register bit.
  * @note   The selected SVOS4 and SVOS5 levels add an additional startup delay when exiting
  *         from system Stop mode.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_ControlStopModeVoltageScaling(uint32_t VoltageScaling)
{
  assert_param(IS_PWR_STOP_MODE_REGULATOR_VOLTAGE(VoltageScaling));

  /* Set the stop mode voltage range */
  MODIFY_REG(PWR->CR1, PWR_CR1_SVOS, VoltageScaling);

  return HAL_OK;
}

/**
  * @brief  Get the main internal regulator output voltage in STOP mode.
  * @retval The actual applied VOS for VDD11 Voltage Scaling selection.
  */
uint32_t  HAL_PWREx_GetStopModeVoltageRange(void)
{
  return (PWR->CR1 & PWR_CR1_SVOS);
}

/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group2 Low power control functions
  * @brief    Low power control functions
  *
@verbatim

 ===============================================================================
                 ##### Low power control functions #####
 ===============================================================================

    *** Domains Low Power modes configuration ***
    =============================================
    [..]
      The system present 3 principles domains (D1, D2 and D3) that can be operated
      in low-power modes (DSTOP or DSTANDBY mode):

      (+) DSTOP mode to enters a domain to STOP mode:
       (++) D1 domain and/or D2 domain enters DSTOP mode only when the CPU
            subsystem is in CSTOP mode and has allocated peripheral in the domain.
            In DSTOP mode the domain bus matrix clock is stopped.
       (++) The system enters STOP mode using one of the following scenarios:
        (+++) D1 domain enters DSTANDBY mode (powered off) and D2, D3 domains enter DSTOP mode.
        (+++) D2 domain enters DSTANDBY mode (powered off) and D1, D3 domains enter DSTOP mode.
        (+++) D3 domain enters DSTANDBY mode (powered off) and D1, D2 domains enter DSTOP mode.
        (+++) D1 and D2 domains enter DSTANDBY mode (powered off) and D3 domain enters DSTOP mode.
        (+++) D1 and D3 domains enter DSTANDBY mode (powered off) and D2 domain enters DSTOP mode.
        (+++) D2 and D3 domains enter DSTANDBY mode (powered off) and D1 domain enters DSTOP mode.
        (+++) D1, D2 and D3 domains enter DSTOP mode.
       (++) When the system enters STOP mode, the clocks are stopped and the regulator is running
            in main or low power mode.
       (++) D3 domain can be kept in Run mode regardless of the CPU status when enter
            STOP mode by using HAL_PWREx_ConfigD3Domain(D3State) function.

      (+) DSTANDBY mode to enters a domain to STANDBY mode:
       (++) The DSTANDBY mode is entered when the PDDS_Dn bit in PWR CPU control register
            (PWR_CPUCR) for the Dn domain selects Standby mode.
       (++) The system enters STANDBY mode only when D1, D2 and D3 domains enter DSTANDBY mode.
            Consequently the VCORE supply regulator is powered off.

   *** DSTOP mode ***
   ==================
    [..]
      In DStop mode the domain bus matrix clock is stopped.
      The Flash memory can enter low-power Stop mode when it is enabled through FLPS in
      PWR_CR1 register. This allows a trade-off between domain DStop restart time and low
      power consumption.
    [..]
      In DStop mode domain peripherals using the LSI or LSE clock and peripherals having a
      kernel clock request are still able to operate.
    [..]
      Before entering DSTOP mode it is recommended to call SCB_CleanDCache function
      in order to clean the D-Cache and guarantee the data integrity for the SRAM memories.

      (+) Entry:
         The DSTOP mode is entered using the HAL_PWREx_EnterSTOPMode(Regulator, STOPEntry, Domain)
         function with:
         (++) Regulator:
          (+++) PWR_MAINREGULATOR_ON: Main regulator ON.
          (+++) PWR_LOWPOWERREGULATOR_ON: Low Power regulator ON.
         (++) STOPEntry:
          (+++) PWR_STOPENTRY_WFI: enter STOP mode with WFI instruction
          (+++) PWR_STOPENTRY_WFE: enter STOP mode with WFE instruction
         (++) Domain:
          (+++) PWR_D1_DOMAIN: Enters D1 domain to DSTOP mode.
          (+++) PWR_D2_DOMAIN: Enters D2 domain to DSTOP mode.
          (+++) PWR_D3_DOMAIN: Enters D3 domain to DSTOP mode.

      (+) Exit:
        Any EXTI Line (Internal or External) configured in Interrupt/Event mode.

   *** DSTANDBY mode ***
   ====================
    [..]
      In DStandby mode:
        (+) The domain bus matrix clock is stopped.
        (+) The domain is powered down and the domain RAM and register contents are lost.
    [..]
      Before entering DSTANDBY mode it is recommended to call SCB_CleanDCache function
      in order to clean the D-Cache and guarantee the data integrity for the SRAM memories.

      (+) Entry:
         The DSTANDBY mode is entered using the HAL_PWREx_EnterSTANDBYMode(Domain) function with:
       (++) Domain:
        (+++) PWR_D1_DOMAIN: Enters D1 domain to DSTANDBY mode.
        (+++) PWR_D2_DOMAIN: Enters D2 domain to DSTANDBY mode.
        (+++) PWR_D3_DOMAIN: Enters D3 domain to DSTANDBY mode.

      (+) Exit:
        WKUP pin rising or falling edge, RTC alarm (Alarm A and Alarm B), RTC
        wakeup, tamper event, time stamp event, external reset in NRST pin, IWDG reset.

   *** Keep D3 in RUN mode ***
   ===========================
    [..]
      D3 domain can be kept in Run mode regardless of the CPU status when enter
      STOP mode by using HAL_PWREx_ConfigD3Domain(D3State) function with:
       (+) D3State:
        (++) PWR_D3_DOMAIN_STOP: D3 domain will follow the CPU sub-system mode.
        (++) PWR_D3_DOMAIN_RUN: D3 domain remains in Run mode regardless of CPU subsystem mode.

    *** FLASH Power Down configuration ****
    =======================================
    [..]
      By setting the FLPS bit in the PWR_CR1 register using the HAL_PWREx_EnableFlashPowerDown()
      function, the Flash memory also enters power down mode when the device enters Stop mode.
      When the Flash memory is in power down mode, an additional startup delay is incurred when
      waking up from Stop mode.

    *** Wakeup Pins configuration ****
    ===================================
    [..]
      Wakeup pins allow the system to exit from Standby mode. The configuration of
      wakeup pins is done with the HAL_PWREx_EnableWakeUpPin(sPinParams) function with:
       (+) sPinParams: structure to enable and configure a wakeup pin:
        (++) WakeUpPin: Wakeup pin to be enabled.
        (++) PinPolarity: Wakeup pin polarity (rising or falling edge).
        (++) PinPull: Wakeup pin pull (no pull, pull-up or pull-down).
    [..]
      The wakeup pins are internally connected to the EXTI lines [55-60] to generate an interrupt
      if enabled. The EXTI lines configuration is done by the HAL_EXTI_Dx_EventInputConfig() functions
      defined in the stm32h7xxhal.c file.
    [..]
      When a wakeup pin event is received the HAL_PWREx_WAKEUP_PIN_IRQHandler is called
      and the appropriate flag is set in the PWR_WKUPFR register. Then in the HAL_PWREx_WAKEUP_PIN_IRQHandler
      function the wakeup pin flag will be cleared and the appropriate user callback will be called.
      The user can add his own code by customization of function pointer HAL_PWREx_WKUPx_Callback.

@endverbatim
  * @{
  */

/**
  * @brief  Enter a Domain to DSTOP mode.
  * @note   In DStop mode the domain bus matrix clock is stopped.
  * @note   The system D3 domain enters Stop mode only when the CPU subsystem is in CStop mode,
  *         the EXTI wakeup sources are inactive and at least one PDDS_Dn bit in PWR CPU
  *         control register (PWR_CPUCR) for any domain request Stop.
  * @note   In system D3 domain Stop mode, D1 domain and D2 domain are either in DStop and/or
  *         DStandby mode.
  * @note   Before entering DSTOP mode it is recommended to call SCB_CleanDCache function
  *         in order to clean the D-Cache and guarantee the data integrity for the SRAM memories.
  * @note   In System Stop mode, the domain peripherals that use the LSI or LSE clock, and the
  *         peripherals that have a kernel clock request to select HSI or CSI as source,
  *         are still able to operate.
  * @param  Regulator: Specifies the regulator state in Stop mode.
  *          This parameter can be one of the following values:
  *            @arg PWR_MAINREGULATOR_ON: Stop mode with regulator ON
  *            @arg PWR_LOWPOWERREGULATOR_ON: Stop mode with low power regulator ON
  * @param  STOPEntry: Specifies if Stop mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *            @arg PWR_STOPENTRY_WFI: Enter DStop mode with WFI instruction
  *            @arg PWR_STOPENTRY_WFE: Enter DStop mode with WFE instruction
  * @param  Domain: Specifies the Domain to enter STOP mode.
  *          This parameter can be one of the following values:
  *            @arg PWR_D1_DOMAIN: Enter D1 Domain to DSTOP mode.
  *            @arg PWR_D2_DOMAIN: Enter D2 Domain to DSTOP mode.
  *            @arg PWR_D3_DOMAIN: Enter D3 Domain to DSTOP mode.
  * @retval None
  */
void HAL_PWREx_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry, uint32_t Domain)
{
  /* Check the parameters */
  assert_param(IS_PWR_REGULATOR(Regulator));
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));
  assert_param(IS_PWR_DOMAIN(Domain));

  /* Select the regulator state in Stop mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPDS, Regulator);

  /* Select the domain Power Down DeepSleep */
  if (Domain == PWR_D1_DOMAIN)
  {
    /* Check Core */
    assert_param(IS_PWR_D1_CPU(HAL_GetCurrentCPUID()));

    /* Keep DSTOP mode when D1 domain enters Deepsleep */
    CLEAR_BIT(PWR->CPUCR, PWR_CPUCR_PDDS_D1);

#if defined(DUAL_CORE)
    CLEAR_BIT(PWR->CPU2CR, PWR_CPU2CR_PDDS_D1);
#endif /*DUAL_CORE*/

    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Ensure that all instructions done before entering STOP mode */
    __DSB();
    __ISB();

    /* Select Stop mode entry */
    if(STOPEntry == PWR_STOPENTRY_WFI)
    {
      /* Request Wait For Interrupt */
      __WFI();
    }
    else
    {
      /* Request Wait For Event */
      __WFE();
    }

    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
  }
  else if (Domain == PWR_D2_DOMAIN)
  {
    /* Keep DSTOP mode when D2 domain enters Deepsleep */
    CLEAR_BIT(PWR->CPUCR, PWR_CPUCR_PDDS_D2);

#if defined(DUAL_CORE)
    /* Check Core */
    assert_param(IS_PWR_D2_CPU(HAL_GetCurrentCPUID()));

    CLEAR_BIT(PWR->CPU2CR, PWR_CPU2CR_PDDS_D2);

    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Ensure that all instructions done before entering STOP mode */
    __DSB();
    __ISB();

    /* Select Stop mode entry */
    if(STOPEntry == PWR_STOPENTRY_WFI)
    {
      /* Request Wait For Interrupt */
      __WFI();
    }
    else
    {
      /* Request Wait For Event */
      __WFE();
    }

    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
#endif /*DUAL_CORE*/
  }
  else
  {
    /* Keep DSTOP mode when D3 domain enters Deepsleep */
    CLEAR_BIT(PWR->CPUCR, PWR_CPUCR_PDDS_D3);

#if defined(DUAL_CORE)
    CLEAR_BIT(PWR->CPU2CR, PWR_CPU2CR_PDDS_D3);
#endif /*DUAL_CORE*/
  }
}


/**
  * @brief  Clear pending event.
  * @note   This API clear the pending event in order to enter a given domain to DSTOP. It should
  *         be called just before enter low power mode APIs using Wait For Event request.
  * @retval None
  */
void HAL_PWREx_ClearPendingEvent(void)
{
#if defined(DUAL_CORE)
  /* Check Core */
  if(HAL_GetCurrentCPUID() == CM7_CPUID)
  {
    __WFE();
  }
  else
  {
    __SEV();
    __WFE();
  }
#else
  __WFE();
#endif /*DUAL_CORE*/

}

/**
  * @brief  Enter a Domain to DSTANDBY mode.
  * @note   The DStandby mode is entered when all PDDS_Dn bits in PWR_CPUCR for the Dn domain
  *         select Standby mode. When the system enters Standby mode, the voltage regulator
  *         is disabled.
  * @note   When D2 or D3 domain is in DStandby mode and the CPU sets the domain PDDS_Dn
  *         bit to select Stop mode, the domain remains in DStandby mode. The domain will only
  *         exit DStandby when the CPU allocates a peripheral in the domain.
  * @note   The system D3 domain enters Standby mode only when the D1 and D2 domain are in
  *         DStandby.
  * @note   Before entering DSTANDBY mode it is recommended to call SCB_CleanDCache function
  *         in order to clean the D-Cache and guarantee the data integrity for the SRAM memories.
  * @param  Domain: Specifies the Domain to enter to STANDBY mode.
  *          This parameter can be one of the following values:
  *            @arg PWR_D1_DOMAIN: Enter D1 Domain to DSTANDBY mode.
  *            @arg PWR_D2_DOMAIN: Enter D2 Domain to DSTANDBY mode.
  *            @arg PWR_D3_DOMAIN: Enter D3 Domain to DSTANDBY mode.
  * @retval None
  */
void HAL_PWREx_EnterSTANDBYMode(uint32_t Domain)
{
  /* Check the parameters */
  assert_param(IS_PWR_DOMAIN(Domain));

  /* Select the domain Power Down DeepSleep */
  if (Domain == PWR_D1_DOMAIN)
  {
    /* Check Core */
    assert_param(IS_PWR_D1_CPU(HAL_GetCurrentCPUID()));

    /* Allow DSTANDBY mode when D1 domain enters Deepsleep */
    SET_BIT(PWR-> CPUCR, PWR_CPUCR_PDDS_D1);

#if defined(DUAL_CORE)
    SET_BIT(PWR-> CPU2CR, PWR_CPU2CR_PDDS_D1);
#endif /*DUAL_CORE*/

    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM)
    __force_stores();
#endif

    /* Request Wait For Interrupt */
    __WFI();
  }
  else if (Domain == PWR_D2_DOMAIN)
  {
    /* Allow DSTANDBY mode when D2 domain enters Deepsleep */
    SET_BIT(PWR-> CPUCR, PWR_CPUCR_PDDS_D2);

#if defined(DUAL_CORE)
    /* Check Core */
    assert_param(IS_PWR_D2_CPU(HAL_GetCurrentCPUID()));

    SET_BIT(PWR-> CPU2CR, PWR_CPU2CR_PDDS_D2);

    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM)
    __force_stores();
#endif

    /* Request Wait For Interrupt */
    __WFI();
#endif /*DUAL_CORE*/
  }
  else
  {
    /* Allow DSTANDBY mode when D3 domain enters Deepsleep */
    SET_BIT(PWR-> CPUCR, PWR_CPUCR_PDDS_D3);

#if defined(DUAL_CORE)
    SET_BIT(PWR-> CPU2CR, PWR_CPU2CR_PDDS_D3);
#endif /*DUAL_CORE*/
  }
}

/**
  * @brief  Configure the D3 Domain state when the CPU is in low power mode.
  * @param  D3State: Specifies the D3 state.
  *          This parameter can be one of the following values:
  *            @arg PWR_D3_DOMAIN_STOP: D3 domain will follow the CPU sub-system mode.
  *            @arg PWR_D3_DOMAIN_RUN : D3 domain will stay in RUN mode regardless of the
  *                                     CPU sub-system mode.
  * @retval None
  */
void HAL_PWREx_ConfigD3Domain(uint32_t D3State)
{
  /* Check the parameters */
  assert_param(IS_D3_STATE(D3State));

  /* Keep D3 in run mode */
  MODIFY_REG(PWR->CPUCR, PWR_CPUCR_RUN_D3, D3State);
#if defined(DUAL_CORE)
  MODIFY_REG(PWR->CPU2CR, PWR_CPU2CR_RUN_D3, D3State);
#endif /*DUAL_CORE*/
}

#if defined(DUAL_CORE)
/**
  * @brief  Clear HOLD2F, STOPF, SBF, SBF_D1, and SBF_D2 flags for a given domain.
  * @param  DomainFlags: Specifies the Domain flags to be cleared.
  *          This parameter can be one of the following values:
  *            @arg PWR_D1_DOMAIN_FLAGS: Clear D1 Domain flags.
  *            @arg PWR_D2_DOMAIN_FLAGS: Clear D2 Domain flags.
  * @retval None.
  */
void HAL_PWREx_ClearDomainFlags(uint32_t DomainFlags)
{
  /* Check the parameters */
  assert_param(IS_PWR_DOMAIN_FLAG(DomainFlags));

  if (DomainFlags == PWR_D1_DOMAIN_FLAGS)
  {
    /* Clear D1 domain flags (HOLD2F, STOPF, SBF, SBF_D1, and SBF_D2) */
    SET_BIT(PWR->CPUCR, PWR_CPUCR_CSSF);
  }
  else
  {
    /* Clear D2 domain flags (HOLD2F, STOPF, SBF, SBF_D1, and SBF_D2) */
    SET_BIT(PWR->CPU2CR, PWR_CPU2CR_CSSF);
  }
}
#endif /*DUAL_CORE*/

#if defined(DUAL_CORE)
/**
  * @brief  Hold the CPU and their allocated peripherals when exiting from STOP mode.
  * @param  CPU: Specifies the core to be held.
  *              This parameter can be one of the following values:
  *             @arg PWR_CORE_CPU1: Hold CPU1 and set CPU2 as master.
  *             @arg PWR_CORE_CPU2: Hold CPU2 and set CPU1 as master.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PWREx_HoldCore(uint32_t CPU)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_PWR_CORE(CPU));

  if (PWR_CORE_CPU2 == CPU)
  {
    /* If CPU1 is not held */
    if(PWR_CPU2CR_HOLD1 != (PWR->CPU2CR & PWR_CPU2CR_HOLD1))
    {
      /* Set HOLD2 bit */
      SET_BIT(PWR->CPUCR, PWR_CPUCR_HOLD2);
    }
    else
    {
      status = HAL_ERROR;
    }
  }
  else if (PWR_CORE_CPU1 == CPU)
  {
    /* If CPU2 is not held */
    if(PWR_CPUCR_HOLD2 != (PWR->CPUCR & PWR_CPUCR_HOLD2))
    {
      /* Set HOLD1 bit */
      SET_BIT(PWR->CPU2CR, PWR_CPU2CR_HOLD1);
    }
    else
    {
      status = HAL_ERROR;
    }
  }
  else
  {
    status = HAL_ERROR;
  }

  return status;
}
#endif /*DUAL_CORE*/


#if defined(DUAL_CORE)
/**
  * @brief   Release the CPU and their allocated peripherals after a wake-up from STOP mode.
  * @param  CPU: Specifies the core to be released.
  *         This parameter can be one of the following values:
  *             @arg  PWR_CORE_CPU1: Release the CPU1 and their allocated peripherals from holding.
  *             @arg  PWR_CORE_CPU2: Release the CPU2 and their allocated peripherals from holding.
  * @retval None
  */
void HAL_PWREx_ReleaseCore(uint32_t CPU)
{
  /* Check the parameters */
  assert_param(IS_PWR_CORE(CPU));

  if (PWR_CORE_CPU2 == CPU)
  {
    /* Reset HOLD2 bit */
    CLEAR_BIT(PWR->CPUCR, PWR_CPUCR_HOLD2);
  }
  else
  {
    /* Reset HOLD1 bit */
    CLEAR_BIT(PWR->CPU2CR, PWR_CPU2CR_HOLD1);
  }
}
#endif /*DUAL_CORE*/

/**
  * @brief  Enable the Flash Power Down in Stop mode.
  * @retval None
  */
void HAL_PWREx_EnableFlashPowerDown(void)
{
  /* Enable the Flash Power Down */
  SET_BIT(PWR->CR1, PWR_CR1_FLPS);
}

/**
  * @brief  Disable the Flash Power Down in Stop mode.
  * @retval None
  */
void HAL_PWREx_DisableFlashPowerDown(void)
{
  /* Disable the Flash Power Down */
  CLEAR_BIT(PWR->CR1, PWR_CR1_FLPS);
}

/**
  * @brief  Enable the Wake-up PINx functionality.
  * @param  sPinParams: pointer to an PWREx_WakeupPinTypeDef structure that contains
  *                     the configuration informations for the wake-up Pin.
  * @retval None
  */
void HAL_PWREx_EnableWakeUpPin(PWREx_WakeupPinTypeDef *sPinParams)
{
  uint32_t pinConfig;
  uint32_t regMask;
  const uint32_t pullMask = PWR_WKUPEPR_WKUPPUPD1;

  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_PIN(sPinParams->WakeUpPin));
  assert_param(IS_PWR_WAKEUP_PIN_POLARITY(sPinParams->PinPolarity));
  assert_param(IS_PWR_WAKEUP_PIN_PULL(sPinParams->PinPull));

  pinConfig = sPinParams->WakeUpPin | \
              (sPinParams->PinPolarity << ((POSITION_VAL(sPinParams->WakeUpPin) + PWR_WKUPEPR_WKUPP1_Pos) & 0x1FU)) | \
              (sPinParams->PinPull << (((POSITION_VAL(sPinParams->WakeUpPin) * PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET) + PWR_WKUPEPR_WKUPPUPD1_Pos) & 0x1FU));

  regMask   = sPinParams->WakeUpPin | \
              (PWR_WKUPEPR_WKUPP1 << (POSITION_VAL(sPinParams->WakeUpPin) & 0x1FU)) | \
              (pullMask << ((POSITION_VAL(sPinParams->WakeUpPin) * PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET) & 0x1FU));

  /* Enable and Specify the Wake-Up pin polarity and the pull configuration
     for the event detection (rising or falling edge) */
  MODIFY_REG(PWR->WKUPEPR, regMask, pinConfig);
#ifndef DUAL_CORE
  /* Configure the Wakeup Pin EXTI Line */
  MODIFY_REG(EXTI->IMR2, PWR_EXTI_WAKEUP_PINS_MASK, (sPinParams->WakeUpPin << EXTI_IMR2_IM55_Pos));
#endif
}

/**
  * @brief Disable the Wake-up PINx functionality.
  * @param WakeUpPin: Specifies the Wake-Up pin to be disabled.
  *          This parameter can be one of the following values:
  *           @arg PWR_WAKEUP_PIN1: Disable PA0  wake-up PIN.
  *           @arg PWR_WAKEUP_PIN2: Disable PA2  wake-up PIN..
  *           @arg PWR_WAKEUP_PIN3: Disable PI8  wake-up PIN..
  *           @arg PWR_WAKEUP_PIN4: Disable PC13 wake-up PIN..
  *           @arg PWR_WAKEUP_PIN5: Disable PI11 wake-up PIN..
  *           @arg PWR_WAKEUP_PIN6: Disable PC1  wake-up PIN..
  * @retval None
  */
void HAL_PWREx_DisableWakeUpPin(uint32_t WakeUpPin)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPin));

  /* Disable the WakeUpPin */
  CLEAR_BIT(PWR->WKUPEPR, WakeUpPin);
}

/**
  * @brief  Get the Wake-Up Pin flag.
  * @param  WakeUpFlag: Specifies the Wake-Up PIN flag to check.
  *          This parameter can be one of the following values:
  *            @arg PWR_WAKEUP_FLAG1: A wakeup event was received from PA0.
  *            @arg PWR_WAKEUP_FLAG2: A wakeup event was received from PA2.
  *            @arg PWR_WAKEUP_FLAG3: A wakeup event was received from PC1.
  *            @arg PWR_WAKEUP_FLAG4: A wakeup event was received from PC13.
  *            @arg PWR_WAKEUP_FLAG5: A wakeup event was received from PI8.
  *            @arg PWR_WAKEUP_FLAG6: A wakeup event was received from PI11.
  * @retval The Wake-Up pin flag.
  */
uint32_t  HAL_PWREx_GetWakeupFlag(uint32_t WakeUpFlag)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_FLAG(WakeUpFlag));

  return (PWR->WKUPFR & WakeUpFlag);
}

/**
  * @brief  Clear the Wake-Up pin flag.
  * @param  WakeUpFlag: Specifies the Wake-Up PIN flag to clear.
  *          This parameter can be one of the following values:
  *            @arg PWR_WAKEUP_FLAG1: Clear the wakeup event received from PA0.
  *            @arg PWR_WAKEUP_FLAG2: Clear the wakeup event received from PA2.
  *            @arg PWR_WAKEUP_FLAG3: Clear the wakeup event received from PC1.
  *            @arg PWR_WAKEUP_FLAG4: Clear the wakeup event received from PC13.
  *            @arg PWR_WAKEUP_FLAG5: Clear the wakeup event received from PI8.
  *            @arg PWR_WAKEUP_FLAG6: Clear the wakeup event received from PI11.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_PWREx_ClearWakeupFlag(uint32_t WakeUpFlag)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_FLAG(WakeUpFlag));

  SET_BIT(PWR->WKUPCR, WakeUpFlag);

  if((PWR->WKUPFR & WakeUpFlag) != 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  This function handles the PWR WAKEUP PIN interrupt request.
  * @note   This API should be called under the WAKEUP_PIN_IRQHandler().
  * @retval None
  */
void HAL_PWREx_WAKEUP_PIN_IRQHandler(void)
{
  /* Wakeup pin EXTI line interrupt detected */
  if(READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF1) != 0U)
  {
    /* Clear PWR WKUPF1 flag */
    SET_BIT(PWR->WKUPCR, PWR_WKUPCR_WKUPC1);

    /* PWR WKUP1 interrupt user callback */
    HAL_PWREx_WKUP1_Callback();
  }
  else if(READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF2) != 0U)
  {
    /* Clear PWR WKUPF2 flag */
    SET_BIT(PWR->WKUPCR, PWR_WKUPCR_WKUPC2);

    /* PWR WKUP2 interrupt user callback */
    HAL_PWREx_WKUP2_Callback();
  }
  else if(READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF3) != 0U)
  {
    /* Clear PWR WKUPF3 flag */
    SET_BIT(PWR->WKUPCR, PWR_WKUPCR_WKUPC3);

    /* PWR WKUP3 interrupt user callback */
    HAL_PWREx_WKUP3_Callback();
  }
  else if(READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF4) != 0U)
  {
    /* Clear PWR WKUPF4 flag */
    SET_BIT(PWR->WKUPCR, PWR_WKUPCR_WKUPC4);

    /* PWR WKUP4 interrupt user callback */
    HAL_PWREx_WKUP4_Callback();
  }
  else if(READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF5) != 0U)
  {
    /* Clear PWR WKUPF5 flag */
    SET_BIT(PWR->WKUPCR, PWR_WKUPCR_WKUPC5);

    /* PWR WKUP5 interrupt user callback */
    HAL_PWREx_WKUP5_Callback();
  }
  else
  {
    /* Clear PWR WKUPF6 flag */
    SET_BIT(PWR->WKUPCR, PWR_WKUPCR_WKUPC6);

    /* PWR WKUP6 interrupt user callback */
    HAL_PWREx_WKUP6_Callback();
  }
}

/**
  * @brief  PWR WKUP1 interrupt callback
  * @retval None
  */
__weak void HAL_PWREx_WKUP1_Callback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PWREx_WKUP1Callback could be implemented in the user file
  */
}

/**
  * @brief  PWR WKUP2 interrupt callback
  * @retval None
  */
__weak void HAL_PWREx_WKUP2_Callback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PWREx_WKUP2Callback could be implemented in the user file
  */
}

/**
  * @brief  PWR WKUP3 interrupt callback
  * @retval None
  */
__weak void HAL_PWREx_WKUP3_Callback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PWREx_WKUP3Callback could be implemented in the user file
  */
}

/**
  * @brief  PWR WKUP4 interrupt callback
  * @retval None
  */
__weak void HAL_PWREx_WKUP4_Callback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PWREx_WKUP4Callback could be implemented in the user file
  */
}

/**
  * @brief  PWR WKUP5 interrupt callback
  * @retval None
  */
__weak void HAL_PWREx_WKUP5_Callback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PWREx_WKUP5Callback could be implemented in the user file
  */
}

/**
  * @brief  PWR WKUP6 interrupt callback
  * @retval None
  */
__weak void HAL_PWREx_WKUP6_Callback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PWREx_WKUP6Callback could be implemented in the user file
  */
}

/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group3 Peripherals control functions
  * @brief    Peripherals control functions
  *
@verbatim

 ===============================================================================
                 ##### Peripherals control functions #####
 ===============================================================================

    *** Main and Backup Regulators configuration ***
    ================================================
    [..]
      (+) The backup domain includes 4 Kbytes of backup SRAM accessible only from
          the CPU, and address in 32-bit, 16-bit or 8-bit mode. Its content is
          retained even in Standby or VBAT mode when the low power backup regulator
          is enabled. It can be considered as an internal EEPROM when VBAT is
          always present. You can use the HAL_PWREx_EnableBkUpReg() function to
          enable the low power backup regulator.
      (+) When the backup domain is supplied by VDD (analog switch connected to VDD)
          the backup SRAM is powered from VDD which replaces the VBAT power supply to
          save battery life.
      (+) The backup SRAM is not mass erased by a tamper event. It is read
          protected to prevent confidential data, such as cryptographic private
          key, from being accessed. The backup SRAM can be erased only through
          the Flash interface when a protection level change from level 1 to
          level 0 is requested.
      -@- Refer to the description of Read protection (RDP) in the Flash
          programming manual.
      (+) The main internal regulator can be configured to have a tradeoff between
          performance and power consumption when the device does not operate at
          the maximum frequency. This is done through HAL_PWREx_ControlVoltageScaling(VOS)
          function which configure the VOS bit in PWR_D3CR register.
      (+) The main internal regulator can be configured to operate in Low Power mode
          when the system enter STOP mode to further reduce power consumption.
          This is done through HAL_PWREx_ControlStopModeVoltageScaling(SVOS)
          function which configure the SVOS bit in PWR_CR1 register.
          The selected SVOS4 and SVOS5 levels add an additional startup delay when exiting from
          system Stop mode.
    -@- Refer to the product datasheets for more details.

    *** USB Regulator configuration ***
    ===================================
    [..]
      (+) The USB transceivers are supplied from a dedicated VDD33USB supply that can be
          provided either by the integrated USB regulator, or by an external USB supply.
      (+) The USB regulator is enabled by HAL_PWREx_EnableUSBReg() function, the VDD33USB
          is then provided from the USB regulator.
      (+) When the USB regulator is enabled, the VDD33USB supply level detector shall
          be enabled through  HAL_PWREx_EnableUSBVoltageDetector() function.
      (+) The USB regulator is disabled through HAL_PWREx_DisableUSBReg() function and VDD33USB
          can be provided from an external supply. In this case VDD33USB and VDD50USB shall
          be connected together

    *** VBAT battery charging ***
    =============================
    [..]
      (+) When VDD is present, the external battery connected to VBAT can be charged through an
          internal resistance. VBAT charging can be performed either through a 5 KOhm resistor
          or through a 1.5 KOhm resistor.
      (+) VBAT charging is enabled by HAL_PWREx_EnableBatteryCharging(ResistorValue) function
          with:
       (++) ResistorValue:
        (+++) PWR_BATTERY_CHARGING_RESISTOR_5: 5 KOhm resistor.
        (+++) PWR_BATTERY_CHARGING_RESISTOR_1_5: 1.5 KOhm resistor.
      (+) VBAT charging is disabled by HAL_PWREx_DisableBatteryCharging() function.

@endverbatim
  * @{
  */

/**
  * @brief  Enable the Backup Regulator.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PWREx_EnableBkUpReg(void)
{
  uint32_t tickstart;

  /* Enable the Backup regulator */
  SET_BIT(PWR->CR2, PWR_CR2_BREN);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait till Backup regulator ready flag is set */
  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_BRR))
  {
    if((HAL_GetTick() - tickstart ) > PWR_FLAG_SETTING_DELAY_US)
    {
      return HAL_TIMEOUT;
    }
  }
  return HAL_OK;
}

/**
  * @brief  Disable the Backup Regulator.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PWREx_DisableBkUpReg(void)
{
  uint32_t tickstart;

  /* Disable the Backup regulator */
  CLEAR_BIT(PWR->CR2, PWR_CR2_BREN);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait till Backup regulator ready flag is reset */
  while(__HAL_PWR_GET_FLAG(PWR_FLAG_BRR) != RESET)
  {
    if((HAL_GetTick() - tickstart ) > PWR_FLAG_SETTING_DELAY_US)
    {
      return HAL_TIMEOUT;
    }
  }
  return HAL_OK;
}

/**
  * @brief  Enable the USB Regulator.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PWREx_EnableUSBReg(void)
{
  uint32_t tickstart;

  /* Enable the USB regulator */
  SET_BIT(PWR->CR3, PWR_CR3_USBREGEN);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait till the USB regulator ready flag is set */
  while(READ_BIT(PWR->CR3, PWR_CR3_USB33RDY) == 0U)
  {
    if((HAL_GetTick() - tickstart ) > PWR_FLAG_SETTING_DELAY_US)
    {
      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Disable the USB Regulator.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PWREx_DisableUSBReg(void)
{
  uint32_t tickstart;

  /* Disable the USB regulator */
  CLEAR_BIT(PWR->CR3, PWR_CR3_USBREGEN);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait till the USB regulator ready flag is reset */
  while(READ_BIT(PWR->CR3, PWR_CR3_USB33RDY) != 0U)
  {
    if((HAL_GetTick() - tickstart ) > PWR_FLAG_SETTING_DELAY_US)
    {
      return HAL_TIMEOUT;
    }
  }
  return HAL_OK;
}

/**
  * @brief  Enable the USB voltage level detector.
  * @retval None
  */
void HAL_PWREx_EnableUSBVoltageDetector(void)
{
  /* Enable the USB voltage detector */
  SET_BIT(PWR->CR3, PWR_CR3_USB33DEN);
}

/**
  * @brief  Disable the USB voltage level detector.
  * @retval None
  */
void HAL_PWREx_DisableUSBVoltageDetector(void)
{
  /* Disable the USB voltage detector */
  CLEAR_BIT(PWR->CR3, PWR_CR3_USB33DEN);
}


/**
  * @brief  Enable the Battery charging.
  *         When VDD is present, charge the external battery through an internal resistor.
  * @param  ResistorValue: Specifies the charging resistor.
  *          This parameter can be one of the following values:
  *            @arg PWR_BATTERY_CHARGING_RESISTOR_5:   5 KOhm resistor.
  *            @arg PWR_BATTERY_CHARGING_RESISTOR_1_5: 1.5 KOhm resistor.
  * @retval None
  */
void HAL_PWREx_EnableBatteryCharging(uint32_t ResistorValue)
{
  assert_param(IS_PWR_BATTERY_RESISTOR_SELECT(ResistorValue));

  /* Specify the charging resistor */
  MODIFY_REG(PWR->CR3, PWR_CR3_VBRS, ResistorValue);

  /* Enable the Battery charging */
  SET_BIT(PWR->CR3, PWR_CR3_VBE);
}


/**
  * @brief  Disable the Battery charging.
  * @retval None
  */
void HAL_PWREx_DisableBatteryCharging(void)
{
  /* Disable the Battery charging */
  CLEAR_BIT(PWR->CR3, PWR_CR3_VBE);
}

/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group4 Power Monitoring functions
  * @brief    Power Monitoring functions
  *
@verbatim

 ===============================================================================
                 ##### Power Monitoring functions #####
 ===============================================================================

    *** VBAT and Temperature supervision ***
    ========================================
    [..]
      (+) The VBAT battery voltage supply can be monitored by comparing it with two threshold
          levels: VBAThigh and VBATlow. VBATH flag and VBATL flags in the PWR control register 2
          (PWR_CR2), indicate if VBAT is higher or lower than the threshold.
      (+) The temperature can be monitored by comparing it with two threshold levels, TEMPhigh
          and TEMPlow. TEMPH and TEMPL flags, in the PWR control register 2 (PWR_CR2),
          indicate whether the device temperature is higher or lower than the threshold.
      (+) The VBAT and the temperature monitoring is enabled by HAL_PWREx_EnableMonitoring()
          function and disabled by HAL_PWREx_DisableMonitoring() function.
      (+) The HAL_PWREx_GetVBATLevel() function return the VBAT level which can be:
          PWR_VBAT_BELOW_LOW_THRESHOLD or PWR_VBAT_ABOVE_HIGH_THRESHOLD or
          PWR_VBAT_BETWEEN_HIGH_LOW_THRESHOLD.
      (+) The HAL_PWREx_GetTemperatureLevel() function return the Temperature level which
          can be: PWR_TEMP_BELOW_LOW_THRESHOLD or PWR_TEMP_ABOVE_HIGH_THRESHOLD or
          PWR_TEMP_BETWEEN_HIGH_LOW_THRESHOLD.

    *** AVD configuration ***
    =========================
    [..]
      (+) The AVD is used to monitor the VDDA power supply by comparing it to a
          threshold selected by the AVD Level (ALS[3:0] bits in the PWR_CR1 register).
      (+) A AVDO flag is available to indicate if VDDA is higher or lower
          than the AVD threshold. This event is internally connected to the EXTI
          line 16 to generate an interrupt if enabled.
          It is configurable through __HAL_PWR_AVD_EXTI_ENABLE_IT() macro.
      (+) The AVD is stopped in System Standby mode.

@endverbatim
  * @{
  */

/**
  * @brief  Enable the VBAT and temperature monitoring.
  * @retval HAL status
  */
void HAL_PWREx_EnableMonitoring(void)
{
  /* Enable the VBAT and Temperature monitoring */
  SET_BIT(PWR->CR2, PWR_CR2_MONEN);
}

/**
  * @brief  Disable the VBAT and temperature monitoring.
  * @retval HAL status
  */
void HAL_PWREx_DisableMonitoring(void)
{
  /* Disable the VBAT and Temperature monitoring */
  CLEAR_BIT(PWR->CR2, PWR_CR2_MONEN);
}

/**
  * @brief  Indicate whether the junction temperature is between, above or below the threshold.
  * @retval Temperature level.
  */
uint32_t HAL_PWREx_GetTemperatureLevel(void)
{
  uint32_t tempLevel;
  uint32_t regValue;

  /* Read the temperature flags */
  regValue = PWR->CR2 & (PWR_CR2_TEMPH | PWR_CR2_TEMPL);

  /* Compare the read value to the temperature threshold */
  if(regValue == PWR_CR2_TEMPL)
  {
    tempLevel = PWR_TEMP_BELOW_LOW_THRESHOLD;
  }
  else if(regValue == PWR_CR2_TEMPH)
  {
    tempLevel = PWR_TEMP_ABOVE_HIGH_THRESHOLD;
  }
  else
  {
    tempLevel = PWR_TEMP_BETWEEN_HIGH_LOW_THRESHOLD;
  }

  return tempLevel;
}

/**
  * @brief  Indicate whether the Battery voltage level is between, above or below the threshold.
  * @retval VBAT level.
  */
uint32_t HAL_PWREx_GetVBATLevel(void)
{
  uint32_t VBATLevel;
  uint32_t regValue;

  /* Read the VBAT flags */
  regValue = PWR->CR2 & (PWR_CR2_VBATH | PWR_CR2_VBATL);

  /* Compare the read value to the VBAT threshold */
  if(regValue == PWR_CR2_VBATL)
  {
    VBATLevel = PWR_VBAT_BELOW_LOW_THRESHOLD;
  }
  else if(regValue == PWR_CR2_VBATH)
  {
    VBATLevel = PWR_VBAT_ABOVE_HIGH_THRESHOLD;
  }
  else
  {
    VBATLevel = PWR_VBAT_BETWEEN_HIGH_LOW_THRESHOLD;
  }

  return VBATLevel;
}

/**
  * @brief  Configure the analog voltage threshold detected by the Analog Voltage Detector(AVD).
  * @param  sConfigAVD: pointer to an PWR_AVDTypeDef structure that contains the configuration
  *                     information for the AVD.
  * @note   Refer to the electrical characteristics of your device datasheet for more details
  *         about the voltage threshold corresponding to each detection level.
  * @retval None
  */
void HAL_PWREx_ConfigAVD(PWREx_AVDTypeDef *sConfigAVD)
{
  /* Check the parameters */
  assert_param(IS_PWR_AVD_LEVEL(sConfigAVD->AVDLevel));
  assert_param(IS_PWR_AVD_MODE(sConfigAVD->Mode));

  /* Set the ALS[18:17] bits according to AVDLevel value */
  MODIFY_REG(PWR->CR1, PWR_CR1_ALS, sConfigAVD->AVDLevel);

  /* Clear any previous config */
#if !defined (DUAL_CORE)
  __HAL_PWR_AVD_EXTI_DISABLE_EVENT();
  __HAL_PWR_AVD_EXTI_DISABLE_IT();
#endif
  __HAL_PWR_AVD_EXTI_DISABLE_RISING_EDGE();
  __HAL_PWR_AVD_EXTI_DISABLE_FALLING_EDGE();

#if !defined (DUAL_CORE)
  /* Configure the interrupt mode */
  if(AVD_MODE_IT == (sConfigAVD->Mode & AVD_MODE_IT))
  {
    __HAL_PWR_AVD_EXTI_ENABLE_IT();
  }

  /* Configure the event mode */
  if(AVD_MODE_EVT == (sConfigAVD->Mode & AVD_MODE_EVT))
  {
    __HAL_PWR_AVD_EXTI_ENABLE_EVENT();
  }
#endif
  /* Configure the edge */
  if(AVD_RISING_EDGE == (sConfigAVD->Mode & AVD_RISING_EDGE))
  {
    __HAL_PWR_AVD_EXTI_ENABLE_RISING_EDGE();
  }

  if(AVD_FALLING_EDGE == (sConfigAVD->Mode & AVD_FALLING_EDGE))
  {
    __HAL_PWR_AVD_EXTI_ENABLE_FALLING_EDGE();
  }
}

/**
  * @brief  Enable the Analog Voltage Detector(AVD).
  * @retval None
  */
void HAL_PWREx_EnableAVD(void)
{
  /* Enable the Analog Voltage Detector */
  SET_BIT(PWR->CR1, PWR_CR1_AVDEN);
}

/**
  * @brief  Disable the Analog Voltage Detector(AVD).
  * @retval None
  */
void HAL_PWREx_DisableAVD(void)
{
  /* Disable the Analog Voltage Detector */
  CLEAR_BIT(PWR->CR1, PWR_CR1_AVDEN);
}

/**
  * @brief  This function handles the PWR PVD/AVD interrupt request.
  * @note   This API should be called under the PVD_AVD_IRQHandler().
  * @retval None
  */
void HAL_PWREx_PVD_AVD_IRQHandler(void)
{
#if defined(DUAL_CORE)
  /* PVD EXTI line interrupt detected */
  if(READ_BIT(PWR->CR1, PWR_CR1_PVDEN) != 0U)
  {
    if (HAL_GetCurrentCPUID() == CM7_CPUID)
    {
      /* Check PWR D1 EXTI flag */
      if(__HAL_PWR_PVD_EXTI_GET_FLAG() != RESET)
      {
        /* PWR PVD interrupt user callback */
        HAL_PWR_PVDCallback();

        /* Clear PWR EXTI D1 pending bit */
        __HAL_PWR_PVD_EXTI_CLEAR_FLAG();
      }
    }
    else
    {
      /* Check PWR EXTI D2 flag */
      if(__HAL_PWR_PVD_EXTID2_GET_FLAG() != RESET)
      {
        /* PWR PVD interrupt user callback */
        HAL_PWR_PVDCallback();

        /* Clear PWR EXTI D2 pending bit */
        __HAL_PWR_PVD_EXTID2_CLEAR_FLAG();
      }
    }
  }

  /* AVD EXTI line interrupt detected */
  if(READ_BIT(PWR->CR1, PWR_CR1_AVDEN) != 0U)
  {
    if (HAL_GetCurrentCPUID() == CM7_CPUID)
    {
      /* Check PWR EXTI D1 flag */
      if(__HAL_PWR_AVD_EXTI_GET_FLAG() != RESET)
      {
        /* PWR AVD interrupt user callback */
        HAL_PWREx_AVDCallback();

        /* Clear PWR EXTI D1 pending bit */
        __HAL_PWR_AVD_EXTI_CLEAR_FLAG();
      }
    }
    else
    {
      /* Check PWR EXTI D2 flag */
      if(__HAL_PWR_AVD_EXTID2_GET_FLAG() != RESET)
      {
        /* PWR AVD interrupt user callback */
        HAL_PWREx_AVDCallback();

        /* Clear PWR EXTI D2 pending bit */
        __HAL_PWR_AVD_EXTID2_CLEAR_FLAG();
      }
    }
  }
#else
  /* PVD EXTI line interrupt detected */
  if(READ_BIT(PWR->CR1, PWR_CR1_PVDEN) != 0U)
  {
    /* Check PWR EXTI flag */
    if(__HAL_PWR_PVD_EXTI_GET_FLAG() != RESET)
    {
      /* PWR PVD interrupt user callback */
      HAL_PWR_PVDCallback();

      /* Clear PWR EXTI pending bit */
      __HAL_PWR_PVD_EXTI_CLEAR_FLAG();
    }
  }

  /* AVD EXTI line interrupt detected */
  if(READ_BIT(PWR->CR1, PWR_CR1_AVDEN) != 0U)
  {
    /* Check PWR EXTI flag */
    if(__HAL_PWR_AVD_EXTI_GET_FLAG() != RESET)
    {
      /* PWR AVD interrupt user callback */
      HAL_PWREx_AVDCallback();

      /* Clear PWR EXTI pending bit */
      __HAL_PWR_AVD_EXTI_CLEAR_FLAG();
    }
  }
#endif /*DUAL_CORE*/
}

/**
  * @brief  PWR AVD interrupt callback
  * @retval None
  */
__weak void HAL_PWREx_AVDCallback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_PWR_AVDCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_PWR_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
