/**
  ******************************************************************************
  * @file    stm32u5xx_hal_pwr_ex.c
  * @author  MCD Application Team
  * @brief   Extended PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller extension peripheral :
  *           + Power Supply Control Functions
  *           + Low Power Control Functions
  *           + Voltage Monitoring Functions
  *           + Memories Retention Functions
  *           + I/O Pull-Up Pull-Down Configuration Functions
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
   (#) Call HAL_PWREx_ControlVoltageScaling() and HAL_PWREx_GetVoltageRange() to
       set / get the voltage scaling range.
      (+) Voltage scaling can be one of the following values :
             (++) voltage output scale 1 : 1V2
                  => Used when system clock frequency is up to 160 MHz
             (++) voltage output scale 2 : 1V1
                  => Used when system clock frequency is up to 100 MHz
             (++) voltage output scale 3 : 1V0
                  => Used when system clock frequency is up to 50 MHz
             (++) voltage output scale 4 : 0V9
                  => Used when system clock frequency is up to 24 MHz

   (#) Call HAL_PWREx_EnableFastSoftStart() and HAL_PWREx_DisableFastSoftStart()
       to enable / disable the fast software startup for the current regulator.

   (#) Call HAL_PWREx_EnterSTOP1Mode() function to enter the whole system to
       Stop 1 mode. Wake-up from Stop 1 mode could be following to an event or
       an interrupt according to low power mode intrinsic request called
       (__WFI() or __WFE()). (Regulator state on U5 devices is managed
       internally but regulator parameter is kept for product compatibility).

   (#) Call HAL_PWREx_EnterSTOP2Mode() function to enter the whole system to
       Stop 2 mode. Wake-up from Stop 2 mode could be following to an event or
       an interrupt according to low power mode intrinsic request called
       (__WFI() or __WFE()). (Regulator state on U5 devices is managed
       internally but regulator parameter is kept for product compatibility).

   (#) Call HAL_PWREx_EnterSTOP3Mode() function to enter the whole system to
       Stop 3 mode. Wake-up from Stop 3 mode could be following to an event or
       an interrupt according to low power mode intrinsic request called
       (__WFI() or __WFE()). (Regulator state on U5 devices is managed
       internally but regulator parameter is kept for product compatibility).

   (#) Call HAL_PWREx_EnterSHUTDOWNMode() function to enter the whole system in
       Shutdown mode. Wake-up from Shutdown mode can be following to an external
       reset (NRST pin), a WKUP pin event (configurable rising or falling edge),
       or an RTC event occurs (alarm, periodic wakeup, timestamp), or a tamper
       detection.

   (#) Call HAL_PWREx_ConfigSRDDomain() to force in Run mode or to enter in Stop
       mode Smart Run Domain when the system enters Stop mode (Stop 0/1/2).

   (#) Call HAL_PWREx_EnableUltraLowPowerMode() and
       HAL_PWREx_DisableUltraLowPowerMode() to enable / disable the BOR ultra
       low power mode.

   (#) Call HAL_PWREx_S3WU_IRQHandler() function to handle the PWR Stop 3 wake
       up interrupt request.

   (#) Call HAL_PWREx_EnableBatteryCharging() and
       HAL_PWREx_DisableBatteryCharging() to enable / disable the battery
       charging capability when VDD alimentation is available.

   (#) Call HAL_PWREx_EnableVddUSB(), HAL_PWREx_EnableVddIO2() and
       HAL_PWREx_EnableVddA() to enable respectively VDDUSB, VDDIO2 and VDDA
       electrical and logical isolation.
       It is recommanded to disable VDDUSB, VDDIO2 and VDDA electrical and
       logical isolation through HAL_PWREx_DisableVddUSB(),
       HAL_PWREx_DisableVddIO2() and HAL_PWREx_DisableVddA().

   (#) Call HAL_PWREx_ConfigPVM() after setting parameters to be configured
       (event mode and PVD type) in order to set up the Peripheral Voltage
       Monitor, then use HAL_PWREx_EnableUVM(), HAL_PWREx_EnableIO2VM(),
       HAL_PWREx_EnableAVM1() and HAL_PWREx_EnableAVM2() functions to start the
       PVM VDDx monitoring and use HAL_PWREx_DisableUVM(),
       HAL_PWREx_DisableIO2VM(), HAL_PWREx_DisableAVM1() and
       HAL_PWREx_DisableAVM2() to stop the PVM VDDx monitoring.
       (+) PVM monitored voltages are :
             (++) VDDUSB versus 1V2
             (++) VDDIO2 versus 0V9
             (++) VDDA versus 1V6
             (++) VDDA versus 1V8

   (#) Call HAL_PWREx_EnableMonitoring() and HAL_PWREx_DisableMonitoring() to
       enable / disable the VBAT and temperature monitoring.

   (#) Call HAL_PWREx_EnableUCPDStandbyMode() and
       HAL_PWREx_DisableUCPDStandbyMode() to enable / disable the UCPD
       configuration memorization in Standby mode.

   (#) Call HAL_PWREx_EnableUCPDDeadBattery() and
       HAL_PWREx_DisableUCPDDeadBattery() to enable / disable the dead battery
       behavior.

   (#) Call HAL_PWREx_PVD_PVM_IRQHandler() function to handle the PWR PVD and
       PVM interrupt request.

   (#) Call HAL_PWREx_EnableSRAM2ContentStandbyRetention() and
       HAL_PWREx_DisableSRAM2ContentStandbyRetention() to
       enable / disable the SRAM2 content retention in Stop 3 and Standby low
       power modes.

   (#) Call HAL_PWREx_EnableRAMsContentStopRetention() and
       HAL_PWREx_DisableRAMsContentStopRetention() to
       enable / disable the RAMs content retention in Stop mode (Stop 0/1/2/3).
       (+) Retained RAM can be one of the following RAMs :
             (++) SRAM1
             (++) SRAM2
             (++) SRAM3
             (++) SRAM4
             (++) ICACHE
             (++) DMA2DRAM
             (++) PKA32RAM
             (++) DCACHE1
             (++) FMAC
             (++) FDCAN
             (++) USB

   (#) Call HAL_PWREx_EnableRAMsContentRunRetention() and
       HAL_PWREx_DisableRAMsContentRunRetention() to
       enable / disable the RAMs content retention in Run mode.
       (+) Retained RAM can be one of the following RAMs :
             (++) SRAM1
             (++) SRAM2
             (++) SRAM3
             (++) SRAM4

   (#) Call HAL_PWREx_EnableFlashFastWakeUp() and
       HAL_PWREx_DisableFlashFastWakeUp() to enable / disable the flash memory
       fast wakeup from Stop mode (Stop 0/1).

   (#) Call HAL_PWREx_EnableSRAM4FastWakeUp() and
       HAL_PWREx_DisableSRAM4FastWakeUp() to enable / disable the SRAM4 memory
       fast wakeup from Stop mode (Stop 0/1/2).

   (#) Call HAL_PWREx_EnableBkupRAMRetention() and
       HAL_PWREx_DisableBkupRAMRetention() to enable / disable the Backup RAM
       content retention in Standby, Shutdown and VBAT modes.

   (#) Call HAL_PWREx_EnablePullUpPullDownConfig() and
       HAL_PWREx_DisablePullUpPullDownConfig() to I/O enable / disable pull-up
       and pull-down configuration.

   (#) Call HAL_PWREx_EnableGPIOPullUp() and HAL_PWREx_EnableGPIOPullDown() to
       apply repectively pull-up and pull-down to selected I/O.
       Call HAL_PWREx_DisableGPIOPullUp() and HAL_PWREx_DisableGPIOPullDown() to
       disable applied repectively pull-up and pull-down to selected I/O.

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup PWREx PWREx
  * @brief    PWR Extended HAL module driver
  * @{
  */

#if defined (HAL_PWR_MODULE_ENABLED)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup PWR_Extended_Private_Defines PWR Extended Private Defines
  * @{
  */
/*!< PORTI pins mask */
#define PWR_PORTI_AVAILABLE_PINS  (0xFFU)
/*!< Time out value of flags setting */
#define PWR_FLAG_SETTING_DELAY    (0x32U)

/** @defgroup PWR_PVM_Mode_Mask PWR PVM Mode Mask
  * @{
  */
#define PVM_RISING_EDGE  (0x01U)  /*!< Mask for rising edge set as PVM trigger                 */
#define PVM_FALLING_EDGE (0x02U)  /*!< Mask for falling edge set as PVM trigger                */
#define PVM_MODE_IT      (0x04U)  /*!< Mask for interruption yielded by PVM threshold crossing */
#define PVM_MODE_EVT     (0x08U)  /*!< Mask for event yielded by PVM threshold crossing        */
/**
  * @}
  */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup PWREx_Exported_Functions PWR Extended Exported Functions
  * @{
  */

/** @defgroup PWREx_Exported_Functions_Group1 Power Supply Control Functions
  * @brief    Power supply control functions
  *
@verbatim
 ===============================================================================
                  ##### Power supply control functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to control power supply.

    [..]
      (+) The STM32U5 Series devices embed two regulators : one LDO (linear
          voltage regulator) and one SMPS (step down converter) in parallel to
          provide the VCORE supply for digital peripherals, SRAM1, SRAM2, SRAM3
          and SRAM4 and embedded Flash memory.

      (+) The SMPS allows the power consumption to be reduced but some
          peripherals can be perturbed by the noise generated by the SMPS,
          requiring the application to switch to LDO when running this
          peripheral in order to reach the best performances.

      (+) The LDO and the SMPS regulators have two modes: Main regulator mode
          (used when performance is needed), and Low-power regulator mode. LDO
          or SMPS can be used in all voltage scaling ranges, and in all Stop
          modes.

      (+) After reset, the regulator is the LDO, in Range 4. Switching to SMPS
          provides lower consumption in particular at high VDD voltage. It is
          possible to switch from LDO to SMPS, or from SMPS to LDO on the fly in
          any range, by configuring the REGSEL bit. It is recommended to switch
          first to SMPS before changing the voltage range.

      (+) When exiting the Stop or Standby modes, the regulator is the same than
          when entering low power modes. The voltage range is the Range 4.

      (+) Both regulators can provide four different voltages (voltage scaling)
          and can operate in Stop modes.
          Voltage scaling ranges can be one of the following values :
             (++) voltage output scale 1 : 1V2
                  => Used when system clock frequency is up to 160 MHz
             (++) voltage output scale 2 : 1V1
                  => Used when system clock frequency is up to 100 MHz
             (++) voltage output scale 3 : 1V0
                  => Used when system clock frequency is up to 50 MHz
             (++) voltage output scale 4 : 0V9
                  => Used when system clock frequency is up to 24 MHz

@endverbatim
  * @{
  */

/**
  * @brief  Configure the main internal regulator output voltage to achieve
  *         a tradeoff between performance and power consumption.
  * @param  VoltageScaling : Specifies the regulator output voltage scale.
  *                          This parameter can be one of the following values :
  *                          @arg @ref PWR_REGULATOR_VOLTAGE_SCALE1 : Regulator voltage output scale 1.
  *                                                                   Provides a typical output voltage at 1.2 V.
  *                                                                   Used when system clock frequency is up to 160 MHz.
  *                          @arg @ref PWR_REGULATOR_VOLTAGE_SCALE2 : Regulator voltage output scale 2.
  *                                                                   Provides a typical output voltage at 1.1 V.
  *                                                                   Used when system clock frequency is up to 100 MHz.
  *                          @arg @ref PWR_REGULATOR_VOLTAGE_SCALE3 : Regulator voltage output scale 3.
  *                                                                   Provides a typical output voltage at 1.0 V.
  *                                                                   Used when system clock frequency is up to 50 MHz.
  *                          @arg @ref PWR_REGULATOR_VOLTAGE_SCALE4 : Regulator voltage output scale 4.
  *                                                                   Provides a typical output voltage at 0.9 V.
  *                                                                   Used when system clock frequency is up to 24 MHz.
  * @note  Before moving to voltage scaling 2, it is mandatory to ensure that
  *        the system frequency is between 50 MHz and 100 MHz.
  * @note  Before moving to voltage scaling 3, it is mandatory to ensure that
  *        the system frequency is between 24 MHz and 50 MHz.
  * @note  Before moving to voltage scaling 4, it is mandatory to ensure that
  *        the system frequency is below 24 MHz.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling)
{
  uint32_t timeout;
  uint32_t vos_old;

  /* Check the parameter */
  assert_param(IS_PWR_VOLTAGE_SCALING_RANGE(VoltageScaling));

  /* Get the current voltage scale applied */
  vos_old = READ_BIT(PWR->SVMSR, PWR_SVMSR_ACTVOS);

  /* No change, nothing to do */
  if (vos_old == VoltageScaling)
  {
    return HAL_OK;
  }

  /* Check voltage scaling level */
  /*
   *  The Embedded power distribution (EPOD) must be enabled before switching to
   *  voltage scale 1 / 2 from voltage scale lower.
   */
  if (VoltageScaling > PWR_REGULATOR_VOLTAGE_SCALE3)
  {
    MODIFY_REG(PWR->VOSR, (PWR_VOSR_VOS | PWR_VOSR_BOOSTEN), (VoltageScaling | PWR_VOSR_BOOSTEN));
  }
  else
  {
    MODIFY_REG(PWR->VOSR, (PWR_VOSR_VOS | PWR_VOSR_BOOSTEN), VoltageScaling);
  }

  /* Wait until VOSRDY is rised */
  timeout = ((PWR_FLAG_SETTING_DELAY * (SystemCoreClock / 1000U)) / 1000U) + 1U;
  while (HAL_IS_BIT_CLR(PWR->VOSR, PWR_VOSR_VOSRDY) && (timeout != 0U))
  {
    timeout--;
  }

  /* Check time out */
  if (timeout != 0U)
  {
    /* Wait until ACTVOSRDY is rised */
    timeout = ((PWR_FLAG_SETTING_DELAY * (SystemCoreClock / 1000U)) / 1000U) + 1U;
    while ((HAL_IS_BIT_CLR(PWR->SVMSR, PWR_SVMSR_ACTVOSRDY)) && (timeout != 0U))
    {
      timeout--;
    }
  }

  /* Check time out */
  if (timeout == 0U)
  {
    return HAL_TIMEOUT;
  }

  return HAL_OK;
}

/**
  * @brief  Return Voltage Scaling Range.
  * @retval Applied voltage scaling value.
  */
uint32_t HAL_PWREx_GetVoltageRange(void)
{
  return (PWR->SVMSR & PWR_SVMSR_ACTVOS);
}

/**
  * @brief  Configure the system Power Supply.
  * @param  SupplySource : Specifies the Power Supply source to set after a
  *                        system startup.
  *                        This parameter can be one of the following values :
  *                        @arg PWR_LDO_SUPPLY  : The LDO regulator supplies the Vcore Power Domains.
  *                        @arg PWR_SMPS_SUPPLY : The SMPS regulator supplies the Vcore Power Domains.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_ConfigSupply(uint32_t SupplySource)
{
  uint32_t timeout;

  /* Check the parameter */
  assert_param(IS_PWR_SUPPLY(SupplySource));

  /* Set maximum time out */
  timeout = ((PWR_FLAG_SETTING_DELAY * (SystemCoreClock / 1000U)) / 1000U) + 1U;

  /* Configure the LDO as system regulator supply */
  if (SupplySource == PWR_LDO_SUPPLY)
  {
    /* Set the power supply configuration */
    CLEAR_BIT(PWR->CR3, PWR_CR3_REGSEL);

    /* Wait until system switch on new regulator */
    while (HAL_IS_BIT_SET(PWR->SVMSR, PWR_SVMSR_REGS) && (timeout != 0U))
    {
      timeout--;
    }
  }
  /* Configure the SMPS as system regulator supply */
  else
  {
    /* Set the power supply configuration */
    SET_BIT(PWR->CR3, PWR_CR3_REGSEL);

    /* Wait until system switch on new regulator */
    while (HAL_IS_BIT_CLR(PWR->SVMSR, PWR_SVMSR_REGS) && (timeout != 0U))
    {
      timeout--;
    }
  }

  /* Check time out */
  if (timeout == 0U)
  {
    return HAL_TIMEOUT;
  }

  return HAL_OK;
}

/**
  * @brief  Get the power supply configuration.
  * @retval The supply configured.
  */
uint32_t  HAL_PWREx_GetSupplyConfig(void)
{
  return (PWR->SVMSR & PWR_SVMSR_REGS);
}

/**
  * @brief  Enable fast soft start for the current regulator.
  * @retval None.
  */
void HAL_PWREx_EnableFastSoftStart(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_FSTEN);
}

/**
  * @brief  Disable fast soft start for the current regulator.
  * @retval None.
  */
void HAL_PWREx_DisableFastSoftStart(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_FSTEN);
}
/**
  * @}
  */


/** @defgroup PWREx_Exported_Functions_Group2 Low Power Control Functions
  * @brief    Low power control functions
  *
@verbatim
 ===============================================================================
                     ##### Low power control functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to control low power modes.

    *** Low Power modes configuration ***
    =====================================
    [..]
      This section presents 4 principles low power modes :
      (+) Stop 1 mode   : Cortex-M33 is stopped, clocks are stopped and the
                          regulator is in low power mode. Several peripheral can
                          operate in this mode.

      (+) Stop 2 mode   : Cortex-M33 is stopped, clocks are stopped and the
                          regulator is in low power mode. Only autonomous
                          peripherals can operate in this mode.

      (+) Stop 3 mode   : Cortex-M33 is stopped, clocks are stopped and the
                          regulator is in low power mode. No peripheral can
                          operate in this mode. Only RAMs content is preserved.

      (+) Shutdown mode : All PWR domains enter Shutdown mode and the VCORE
                          supply regulator is powered off. The SRAMs and
                          register contents are lost except for registers in the
                          Backup domain.

   *** Stop 1 mode ***
   ===================
    [..]
      The Stop 1 mode is based on the Cortex-M33 Deepsleep mode combined with
      the peripheral clock gating. The voltage regulator is configured in low
      power mode. In Stop 1 mode, all clocks in the VCORE domain are stopped.
      The PLL, MSIS, MSIK, HSI16 and HSE oscillators are disabled.
      Some peripherals with the LPBAM capability can switch on HSI16 or MSIS or
      MSIK for transferring data. All SRAMs and register contents are preserved,
      but the SRAMs can be totally or partially switched off to further reduced
      consumption.
      The BOR is always available in Stop 1 mode.

      (+) Entry:
          The Stop 1 mode is entered by using the HAL_PWREx_EnterSTOP1Mode()
          function.

          (++) PWR_STOPENTRY_WFI: enter Stop 1 mode with WFI instruction.
          (++) PWR_STOPENTRY_WFE: enter Stop 1 mode with WFE instruction.

      (+) Exit:
          Any EXTI line configured in interrupt mode (the corresponding EXTI
          interrupt vector must be enabled in the NVIC). The interrupt source
          can be external interrupts or peripherals with wakeup capability.
          Any peripheral interrupt occurring when the AHB/APB clocks are present
          due to an autonomous peripheral clock request (the peripheral vector
          must be enabled in the NVIC)
          Any EXTI line configured in event mode.

   *** Stop 2 mode ***
   ===================
    [..]
      The Stop 2 mode is based on the Cortex-M33 Deepsleep mode combined with
      peripheral clock gating. In Stop 2 mode, all clocks in the VCORE domain
      are stopped.
      The PLL, MSIS, MSIK, HSI16 and HSE oscillators are disabled.
      Some peripherals with the LPBAM capability can switch on HSI16 or MSIS or
      MSIK for transferring data. All SRAMs and register contents are preserved,
      but the SRAMs can be totally or partially switched off to further reduce
      consumption.
      The BOR is always available in Stop 2 mode.

      (+) Entry:
          The Stop 2 mode is entered by using the HAL_PWREx_EnterSTOP2Mode()
          function.

          (++) PWR_STOPENTRY_WFI: enter Stop 2 mode with WFI instruction.
          (++) PWR_STOPENTRY_WFE: enter Stop 2 mode with WFE instruction.

      (+) Exit:
          Any EXTI line configured in interrupt mode (the corresponding EXTI
          interrupt vector must be enabled in the NVIC). The interrupt source
          can be external interrupts or peripherals with wakeup capability.
          Any peripheral interrupt occurring when the AHB/APB clocks are present
          due to an autonomous peripheral clock request (the peripheral vector
          must be enabled in the NVIC)
          Any EXTI line configured in event mode.

   *** Stop 3 mode ***
   ===================
    [..]
      The Stop 3 mode is based on the Cortex®-M33 Deepsleep mode combined with
      peripheral clock gating. In Stop 3 mode, all clocks in the VCORE domain
      are stopped.
      The PLL, MSIS, MSIK, HSI16 and HSE oscillators are disabled.
      All SRAMs and register contents are preserved, but the SRAMs can be
      totally or partially switched off to further reduce consumption.
      The BOR is always available in Stop 3 mode.

      (+) Entry:
          The Stop 3 mode is entered by using the HAL_PWREx_EnterSTOP3Mode()
          function.

          (++) PWR_STOPENTRY_WFI: enter Stop 3 mode with WFI instruction.
          (++) PWR_STOPENTRY_WFE: enter Stop 3 mode with WFE instruction.

      (+) Exit:
          WKUPx pin edge, RTC or TAMP event, external Reset in NRST pin, IWDG
          Reset, BOR reset.

  *** Shutdown mode ***
   ====================
    [..]
      The lowest power consumption is reached in Shutdown mode. It is based on
      the Deepsleep mode with the voltage regulator disabled. The VCORE domain
      is consequently powered off.
      The PLL, HSI16, MSIS, MSIK and HSE oscillators are also switched off.
      The SRAMs and register contents are lost except for registers in the
      Backup domain.
      The BOR is not available in Shutdown mode.
      No power voltage monitoring is possible in this mode, therefore the switch
      to Backup domain is not supported.

      (+) Entry:
          The Shutdown mode is entered by using the HAL_PWREx_EnterSHUTDOWNMode()
          function.

      (+) Exit:
          WKUPx pin edge, RTC/TAMP event, external Reset in NRST pin.

@endverbatim
  * @{
  */

/**
  * @brief  Enter the whole system to Stop 1 mode.
  * @note   Stop 1 offers the largest number of active peripherals and wakeup
  *         sources, a smaller wakeup time but a higher consumption.
  * @note   Stop mode achieves the lowest power consumption while retaining
  *         the content of SRAM and registers. All clocks in the VCORE domain
  *         are stopped. The PLL, the MSI (MSIS and MSIK) RC, the HSI16 RC and
  *         the HSE crystal oscillators are disabled. The LSE or LSI is still
  *         running.
  * @note   The system clock when exiting from Stop mode can be either MSIS up
  *         to 24 MHz or HSI16, depending on software configuration.
  * @param  STOPEntry : Specifies if Stop mode is entered with WFI or WFE
  *                     instruction.
  *                     This parameter can be one of the following values :
  *                     @arg @ref PWR_STOPENTRY_WFI enter Stop mode with Wait
  *                               For Interrupt request.
  *                     @arg @ref PWR_STOPENTRY_WFE enter Stop mode with Wait
  *                               For Event request.
  * @retval None.
  */
void HAL_PWREx_EnterSTOP1Mode(uint8_t STOPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));

  /* Stop 1 mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_CR1_LPMS_0);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select Stop mode entry */
  if (STOPEntry == PWR_STOPENTRY_WFI)
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
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief  Enter the whole system to Stop 2 mode.
  * @note   In Stop 2 mode, all clocks in the VCORE domain are stopped. The PLL,
  *         MSIS, MSIK, HSI16 and HSE oscillators are disabled.
  * @note   Stop mode achieves the lowest power consumption while retaining
  *         the content of SRAM and registers. All clocks in the VCORE domain
  *         are stopped. The PLL, the MSI (MSIS and MSIK) RC, the HSI16 RC and
  *         the HSE crystal oscillators are disabled. The LSE or LSI is still
  *         running.
  * @note   The system clock when exiting from Stop mode can be either MSIS up
  *         to 24 MHz or HSI16, depending on software configuration.
  * @param  STOPEntry : Specifies if Stop mode is entered with WFI or WFE
  *                     instruction.
  *                     This parameter can be one of the following values :
  *                     @arg @ref PWR_STOPENTRY_WFI enter Stop mode with Wait
  *                               For Interrupt request.
  *                     @arg @ref PWR_STOPENTRY_WFE enter Stop mode with Wait
  *                               For Event request.
  * @retval None.
  */
void HAL_PWREx_EnterSTOP2Mode(uint8_t STOPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));

  /* Stop 2 mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_CR1_LPMS_1);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select Stop mode entry */
  if (STOPEntry == PWR_STOPENTRY_WFI)
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
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief  Enter the whole system to Stop 3 mode.
  * @note   Stop 3 is the lowest power mode with full retention, but the
  *         functional peripherals and sources of wakeup are reduced to the same
  *         ones than in Standby mode.
  * @note   Stop mode achieves the lowest power consumption while retaining
  *         the content of SRAM and registers. All clocks in the VCORE domain
  *         are stopped. The PLL, the MSI (MSIS and MSIK) RC, the HSI16 RC and
  *         the HSE crystal oscillators are disabled. The LSE or LSI is still
  *         running.
  * @note   The system clock when exiting from Stop mode can be either MSIS up
  *         to 24 MHz or HSI16, depending on software configuration.
  * @param  STOPEntry : Specifies if Stop mode is entered with WFI or WFE
  *                     instruction.
  *                     This parameter can be one of the following values :
  *                     @arg @ref PWR_STOPENTRY_WFI enter Stop mode with Wait
  *                               For Interrupt request.
  *                     @arg @ref PWR_STOPENTRY_WFE enter Stop mode with Wait
  *                               For Event request.
  * @retval None.
  */
void HAL_PWREx_EnterSTOP3Mode(uint8_t STOPEntry)
{
  /* Check the parameter */
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));

  /* Set Stop mode 3 */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, (PWR_CR1_LPMS_0 | PWR_CR1_LPMS_1));

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select Stop mode entry */
  if (STOPEntry == PWR_STOPENTRY_WFI)
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
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief  Enter the whole system to Shutdown mode.
  * @note   Shutdown mode allows the lowest power consumption. The internal
  *         regulator is switched off so that the VCORE domain is powered off.
  *         The PLL, the HSI16, the MSI (MSIS and MSIK), the LSI and the HSE
  *         oscillators are also switched off.
  * @note   The SRAMs and register contents are lost except for registers in the
  *         Backup domain. The BOR is not available in Shutdown mode. No power
  *         voltage monitoring is possible in this mode, therefore the switch to
  *         Backup domain is not supported.
  * @retval None.
  */
void HAL_PWREx_EnterSHUTDOWNMode(void)
{
  /* Set Shutdown mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, (PWR_CR1_LPMS_1 | PWR_CR1_LPMS_2));

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* This option is used to ensure that store operations are completed */
#if defined (__CC_ARM)
  __force_stores();
#endif /* (__CC_ARM)*/
  /* Request Wait For Interrupt */
  __WFI();
}

/**
  * @brief  Configure the SRD domain when the System in Stop 0/1/2 mode.
  * @param  SRDState : Specifies the SRD state.
  *                    This parameter can be one of the following values :
  *                    @arg PWR_SRD_DOMAIN_STOP : SRD in Stop mode when system
  *                                               goes to Stop 0/1/2 mode
  *                    @arg PWR_SRD_DOMAIN_RUN  : SRD in Run mode when system
  *                                               goes to Stop 0/1/2 mode
  * @retval None.
  */
void HAL_PWREx_ConfigSRDDomain(uint32_t SRDState)
{
  /* Check the parameter */
  assert_param(IS_PWR_SRD_STATE(SRDState));

  /* Config the SRD domain */
  MODIFY_REG(PWR->CR2, PWR_CR2_SRDRUN, SRDState);
}

/**
  * @brief  Enable BOR ultra-low power mode.
  * @note   BOR operating can be in discontinuous (ultra-low power) mode in
  *         Stop 1, Stop 2, Stop 3 and Standby modes and when the regulator is
  *         in Range 4 (Run, Sleep or Stop 0 mode).
  * @retval None.
  */
void HAL_PWREx_EnableUltraLowPowerMode(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_ULPMEN);
}

/**
  * @brief  Disable BOR ultra-low power mode.
  * @retval None.
  */
void HAL_PWREx_DisableUltraLowPowerMode(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_ULPMEN);
}

/**
  * @brief  This function handles the PWR Wake up from Stop 3 interrupt request.
  * @note   This API should be called under the PWR_S3WU_IRQHandler().
  * @param  WakeUpPin : Specifies the wakeup pin interrupt to be handled.
  *                     This parameter can be a combination of @ref PWR_WakeUp_Pins.
  * @retval None.
  */
void HAL_PWREx_S3WU_IRQHandler(uint32_t WakeUpPin)
{
  /* Check PWR wake up line 1 */
  if ((WakeUpPin & PWR_WAKEUP_PIN1) != 0U)
  {
    if (READ_BIT(PWR->WUSR, PWR_WUSR_WUF1) != 0U)
    {
      /* Clear PWR wake up flag line 1 */
      SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF1);

      /* PWR S3WU interrupt user callback */
      HAL_PWREx_S3WUCallback(WakeUpPin);
    }
  }

  /* Check PWR wake up line 2 */
  if ((WakeUpPin & PWR_WAKEUP_PIN2) != 0U)
  {
    if (READ_BIT(PWR->WUSR, PWR_WUSR_WUF2) != 0U)
    {
      /* Clear PWR wake up flag line 2 */
      SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF2);

      /* PWR S3WU interrupt user callback */
      HAL_PWREx_S3WUCallback(WakeUpPin);
    }
  }

  /* Check PWR wake up line 3 */
  if ((WakeUpPin & PWR_WAKEUP_PIN3) != 0U)
  {
    if (READ_BIT(PWR->WUSR, PWR_WUSR_WUF3) != 0U)
    {
      /* Clear PWR wake up flag line 3 */
      SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF3);

      /* PWR S3WU interrupt user callback */
      HAL_PWREx_S3WUCallback(WakeUpPin);
    }
  }

  /* Check PWR wake up line 4 */
  if ((WakeUpPin & PWR_WAKEUP_PIN4) != 0U)
  {
    if (READ_BIT(PWR->WUSR, PWR_WUSR_WUF4) != 0U)
    {
      /* Clear PWR wake up flag line 4 */
      SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF4);

      /* PWR S3WU interrupt user callback */
      HAL_PWREx_S3WUCallback(WakeUpPin);
    }
  }

  /* Check PWR wake up line 5 */
  if ((WakeUpPin & PWR_WAKEUP_PIN5) != 0U)
  {
    if (READ_BIT(PWR->WUSR, PWR_WUSR_WUF5) != 0U)
    {
      /* Clear PWR wake up flag line 5 */
      SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF5);

      /* PWR S3WU interrupt user callback */
      HAL_PWREx_S3WUCallback(WakeUpPin);
    }
  }

  /* Check PWR wake up line 6 */
  if ((WakeUpPin & PWR_WAKEUP_PIN6) != 0U)
  {
    if (READ_BIT(PWR->WUSR, PWR_WUSR_WUF6) != 0U)
    {
      /* Clear PWR wake up flag line 6 */
      SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF6);

      /* PWR S3WU interrupt user callback */
      HAL_PWREx_S3WUCallback(WakeUpPin);
    }
  }

  /* Check PWR wake up line 7 */
  if ((WakeUpPin & PWR_WAKEUP_PIN7) != 0U)
  {
    if (READ_BIT(PWR->WUSR, PWR_WUSR_WUF7) != 0U)
    {
      /* Clear PWR wake up flag line 7 */
      SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF7);

      /* PWR S3WU interrupt user callback */
      HAL_PWREx_S3WUCallback(WakeUpPin);
    }
  }

  /* Check PWR wake up line 8 */
  if ((WakeUpPin & PWR_WAKEUP_PIN8) != 0U)
  {
    if (READ_BIT(PWR->WUSR, PWR_WUSR_WUF8) != 0U)
    {
      /* Clear PWR wake up flag line 8 */
      SET_BIT(PWR->WUSCR, PWR_WUSCR_CWUF8);

      /* PWR S3WU interrupt user callback */
      HAL_PWREx_S3WUCallback(WakeUpPin);
    }
  }
}

/**
  * @brief  PWR S3WU interrupt callback.
  * @param  WakeUpPin : Specifies the wakeup pin interrupt to be handled.
  *                     This parameter can be a combination of @ref PWR_WakeUp_Pins.
  * @retval None.
  */
__weak void HAL_PWREx_S3WUCallback(uint32_t WakeUpPin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(WakeUpPin);

  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWREx_S3WU_IRQHandler() API can be implemented in the user file
   */
}
/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group3 Voltage Monitoring Functions
  * @brief    Voltage monitoring functions
  *
@verbatim
 ===============================================================================
                     ##### Voltage Monitoring Functions #####
 ===============================================================================
    [..]
      This section provides functions allowing voltage monitoring.

    *** PVM configuration ***
    =========================
    [..]
      (+) The supplies (VDDA, VDDIO2 and VDDUSB) can be independent from VDD and
          can be monitored with four peripheral voltage monitoring (PVM):

          (++) The UVM monitors the USB supply VDDUSB. VDDUSBRDY indicates if
               the VDDUSB independent power supply is higher or lower than the
               VUVM threshold.
          (++) The IO2VM monitors the PG[15:2] supply VDDIO2. VDDIO2RDY
               indicates if the VDDIO2 independent power supply is higher or
               lower than the VIO2VM threshold.
          (++) The AVM1 monitors the analog supply VDDA. VDDA1RDY indicates if
               the VDDA independent power supply is higher or lower than the
               VAVM1 threshold.
          (++) The AVM2 monitors the analog supply VDDA. VDDA2RDY indicates if
               the VDDA independent power supply is higher or lower than the
               VAVM2 threshold.

      (+) Each PVM output is connected to an EXTI line and can generate an
          interrupt if enabled through the EXTI registers. The PVMx output
          interrupt is generated when the independent power supply drops below
          the PVM threshold and/or when it rises above the PVM threshold,
          depending on EXTI line rising/falling edge configuration.

      (+) Each PVM can remain active in Stop 0, Stop 1, Stop 2 modes, and the
          PVM interrupt can wake up from the Stop mode. The PVM is not
          functional in Stop 3 mode.

    *** VBAT charging ***
    =====================
    [..]
      When VDD is present, it is possible to charge the external battery on VBAT
      through an internal resistance.
      The VBAT charging is done either through a 5 kOhm resistor or through a 1.5
      kOhm resistor depending on the VBRS bit value in the PWR_BDCR2 register.
      The battery charging is enabled by setting VBE bit in the PWR_BDCR2
      register. It is automatically disabled in VBAT mode.

    *** Backup domain monitoring ***
    ================================
    [..]
      When the Backup domain voltage and temperature monitoring is enabled
      (MONEN = 1 in the PWR_BDCR1 register), the Backup domain voltage and the
      temperature are monitored.
      If the Backup domain voltage monitoring internal tamper is enabled in the
      TAMP peripheral (ITAMP1E = 1 in the TAMP_CR1 register), a tamper event is
      generated when the Backup domain voltage is above the functional range.
      In case the Backup domain voltage is below the functional range,
      a Brownout reset is generated, erasing all device including Backup domain.

    *** Backup domain battery ***
    =============================
    [..]
      (+) To retain the content of the backup registers and supply the RTC
          function when VDD is turned off, the VBAT pin can be connected to an
          optional backup voltage supplied by a battery or by another source.
          The VBAT pin powers the RTC unit, the LSE oscillator and the PC13 to
          PC15 I/Os, allowing the RTC to operate even when the main power supply
          is turned off. The backup SRAM is optionally powered by VBAT pin when
          the BREN bit is set in the PWR Backup domain control register 1
          (PWR_BDCR1).
          The switch to the VBAT supply is controlled by the power down reset
          embedded in the Reset block.

      (+) After exiting reset, the USB Type-C “dead battery” behavior is enabled,
          which may have a pull-down effect on CC1 and CC2 pins. It is
          recommended to disable it in all cases, either to stop this pull-down
          or to handover control to the UCPD (the UCPD must be initialized
          before doing the disable).

@endverbatim
  * @{
  */

/**
  * @brief  Configure the voltage monitor threshold detected by the Peripheral
  *         voltage monitoring (PVM).
  * @param  pConfigPVM : Pointer to a PWR_PVMTypeDef structure that contains the
  *                      PVM configuration information (PVMType and EventMode).
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_ConfigPVM(PWR_PVMTypeDef *pConfigPVM)
{
  /* Check the PVM parameter */
  if (pConfigPVM == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_PWR_PVM_TYPE(pConfigPVM->PVMType));
  assert_param(IS_PWR_PVM_MODE(pConfigPVM->Mode));

  /* Check the peripheral voltage monitor type */
  switch (pConfigPVM->PVMType)
  {
    case PWR_UVM: /* Independent USB voltage monitor */

      /* Disable EXTI UVM event and interrupt */
      __HAL_PWR_UVM_EXTI_DISABLE_EVENT();
      __HAL_PWR_UVM_EXTI_DISABLE_IT();
      __HAL_PWR_UVM_EXTI_DISABLE_RISING_EDGE();
      __HAL_PWR_UVM_EXTI_DISABLE_FALLING_EDGE();

      /* Configure the UVM in interrupt mode */
      if ((pConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_UVM_EXTI_ENABLE_IT();
      }

      /* Configure the UVM in event mode */
      if ((pConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_UVM_EXTI_ENABLE_EVENT();
      }

      /* Configure the UVM in rising edge */
      if ((pConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_UVM_EXTI_ENABLE_RISING_EDGE();
      }

      /* Configure the UVM in falling edge */
      if ((pConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_UVM_EXTI_ENABLE_FALLING_EDGE();
      }

      break;

    case PWR_IO2VM: /* Independent I/Os voltage monitor */

      /* Disable EXTI IO2VM event and interrupt */
      __HAL_PWR_IO2VM_EXTI_DISABLE_EVENT();
      __HAL_PWR_IO2VM_EXTI_DISABLE_IT();
      __HAL_PWR_IO2VM_EXTI_DISABLE_RISING_EDGE();
      __HAL_PWR_IO2VM_EXTI_DISABLE_FALLING_EDGE();

      /* Configure the IO2VM in interrupt mode */
      if ((pConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_IO2VM_EXTI_ENABLE_IT();
      }

      /* Configure the IO2VM in event mode */
      if ((pConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_IO2VM_EXTI_ENABLE_EVENT();
      }

      /* Configure the IO2VM in rising edge */
      if ((pConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_IO2VM_EXTI_ENABLE_RISING_EDGE();
      }

      /* Configure the IO2VM in falling edge */
      if ((pConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_IO2VM_EXTI_ENABLE_FALLING_EDGE();
      }

      break;

    case PWR_AVM1: /* VDDA Independent analog supply voltage monitor 1 (1.6V threshold) */

      /* Disable EXTI AVM1 event and interrupt */
      __HAL_PWR_AVM1_EXTI_DISABLE_EVENT();
      __HAL_PWR_AVM1_EXTI_DISABLE_IT();
      __HAL_PWR_AVM1_EXTI_DISABLE_RISING_EDGE();
      __HAL_PWR_AVM1_EXTI_DISABLE_FALLING_EDGE();

      /* Configure the AVM1 in interrupt mode */
      if ((pConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_AVM1_EXTI_ENABLE_IT();
      }

      /* Configure the AVM1 in event mode */
      if ((pConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_AVM1_EXTI_ENABLE_EVENT();
      }

      /* Configure the AVM1 in rising edge */
      if ((pConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_AVM1_EXTI_ENABLE_RISING_EDGE();
      }

      /* Configure the AVM1 in falling edge */
      if ((pConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_AVM1_EXTI_ENABLE_FALLING_EDGE();
      }

      break;

    case PWR_AVM2: /* VDDA Independent analog supply voltage monitor 2 (1.8V threshold) */

      /* Disable EXTI AVM2 event and interrupt */
      __HAL_PWR_AVM2_EXTI_DISABLE_EVENT();
      __HAL_PWR_AVM2_EXTI_DISABLE_IT();
      __HAL_PWR_AVM2_EXTI_DISABLE_RISING_EDGE();
      __HAL_PWR_AVM2_EXTI_DISABLE_FALLING_EDGE();

      /* Configure the AVM2 in interrupt mode */
      if ((pConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_AVM2_EXTI_ENABLE_IT();
      }

      /* Configure the AVM2 in event mode */
      if ((pConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_AVM2_EXTI_ENABLE_EVENT();
      }

      /* Configure the AVM2 in rising edge */
      if ((pConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_AVM2_EXTI_ENABLE_RISING_EDGE();
      }

      /* Configure the AVM2 in falling edge */
      if ((pConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_AVM2_EXTI_ENABLE_FALLING_EDGE();
      }

      break;

    default: /* No valid voltage monitor selected */
      return HAL_ERROR;
      break;
  }

  return HAL_OK;
}

/**
  * @brief  Enable VDDUSB supply.
  * @note   Remove VDDUSB electrical and logical isolation, once VDDUSB supply
  *         is present for consumption saving.
  * @retval None.
  */
void HAL_PWREx_EnableVddUSB(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_USV);
}

/**
  * @brief  Disable VDDUSB supply.
  * @retval None.
  */
void HAL_PWREx_DisableVddUSB(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_USV);
}

/**
  * @brief  Enable VDDIO2 supply.
  * @note   Remove VDDIO2 electrical and logical isolation, once VDDIO2 supply
  *         is present for consumption saving.
  * @retval None.
  */
void HAL_PWREx_EnableVddIO2(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_IO2SV);
}

/**
  * @brief  Disable VDDIO2 supply.
  * @retval None.
  */
void HAL_PWREx_DisableVddIO2(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_IO2SV);
}

/**
  * @brief  Enable VDDA supply.
  * @note   Remove VDDA electrical and logical isolation, once VDDA supply is
  *         present for consumption saving.
  * @retval None.
  */
void HAL_PWREx_EnableVddA(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_ASV);
}

/**
  * @brief  Disable VDDA supply.
  * @retval None.
  */
void HAL_PWREx_DisableVddA(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_ASV);
}

/**
  * @brief  Enable the UVM Voltage Monitoring : VDDUSB versus 1.2 V.
  * @retval None.
  */
void HAL_PWREx_EnableUVM(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_UVMEN);
}

/**
  * @brief  Disable the UVM Voltage Monitoring : VDDUSB versus 1.2 V.
  * @retval None.
  */
void HAL_PWREx_DisableUVM(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_UVMEN);
}

/**
  * @brief  Enable the IO2VM Voltage Monitoring : VDDIO2 versus 0.9 V.
  * @retval None.
  */
void HAL_PWREx_EnableIO2VM(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_IO2VMEN);
}

/**
  * @brief  Disable the IO2VM Voltage Monitoring : VDDIO2 versus 0.9 V.
  * @retval None.
  */
void HAL_PWREx_DisableIO2VM(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_IO2VMEN);
}

/**
  * @brief  Enable the AVM1 Voltage Monitoring : VDDA versus 1.6 V.
  * @retval None.
  */
void HAL_PWREx_EnableAVM1(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_AVM1EN);
}

/**
  * @brief  Disable the AVM1 Voltage Monitoring : VDDA versus 1.6 V.
  * @retval None.
  */
void HAL_PWREx_DisableAVM1(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_AVM1EN);
}

/**
  * @brief  Enable the AVM2 Voltage Monitoring : VDDA versus 1.8 V.
  * @retval None.
  */
void HAL_PWREx_EnableAVM2(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_AVM2EN);
}

/**
  * @brief  Disable the AVM2 Voltage Monitoring : VDDA versus 1.8 V.
  * @retval None.
  */
void HAL_PWREx_DisableAVM2(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_AVM2EN);
}

/**
  * @brief  Enable the VBAT and temperature monitoring.
  * @retval None.
  */
void HAL_PWREx_EnableMonitoring(void)
{
  SET_BIT(PWR->BDCR1, PWR_BDCR1_MONEN);
}

/**
  * @brief  Disable the VBAT and temperature monitoring.
  * @retval None.
  */
void HAL_PWREx_DisableMonitoring(void)
{
  CLEAR_BIT(PWR->BDCR1, PWR_BDCR1_MONEN);
}

/**
  * @brief  Enable UCPD configuration memorization in Standby mode.
  * @retval None.
  */
void HAL_PWREx_EnableUCPDStandbyMode(void)
{
  SET_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STDBY);
}

/**
  * @brief  Disable UCPD configuration memorization in Standby mode.
  * @note   This function must be called on exiting the Standby mode and before
  *         any UCPD configuration update.
  * @retval None.
  */
void HAL_PWREx_DisableUCPDStandbyMode(void)
{
  CLEAR_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STDBY);
}

/**
  * @brief  Enable dead battery behavior.
  * @note   After exiting reset, the USB Type-C “dead battery” behavior is
  *         enabled, which may have a pull-down effect on CC1 and CC2 pins.
  *         It is recommended to disable it in all cases, either to stop this
  *         pull-down or to handover control to the UCPD (the UCPD must be
  *         initialized before doing the disable).
  * @retval None.
  */
void HAL_PWREx_EnableUCPDDeadBattery(void)
{
  CLEAR_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS);
}

/**
  * @brief  Disable dead battery behavior.
  * @note   After exiting reset, the USB Type-C “dead battery” behavior is
  *         enabled, which may have a pull-down effect on CC1 and CC2 pins.
  *         It is recommended to disable it in all cases, either to stop this
  *         pull-down or to handover control to the UCPD (the UCPD must be
  *         initialized before doing the disable).
  * @retval None.
  */
void HAL_PWREx_DisableUCPDDeadBattery(void)
{
  SET_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS);
}

/**
  * @brief  Enable the Battery charging.
  * @note   When VDD is present, charge the external battery through an internal
  *         resistor.
  * @param  ResistorValue : Specifies the charging resistor.
  *                         This parameter can be one of the following values :
  *                         @arg PWR_BATTERY_CHARGING_RESISTOR_5   : 5 KOhm resistor.
  *                         @arg PWR_BATTERY_CHARGING_RESISTOR_1_5 : 1.5 KOhm resistor.
  * @retval None.
  */
void HAL_PWREx_EnableBatteryCharging(uint32_t ResistorValue)
{
  /* Check the parameter */
  assert_param(IS_PWR_BATTERY_RESISTOR_SELECT(ResistorValue));

  /* Specify the charging resistor */
  MODIFY_REG(PWR->BDCR2, PWR_BDCR2_VBRS, ResistorValue);

  /* Enable the Battery charging */
  SET_BIT(PWR->BDCR2, PWR_BDCR2_VBE);
}

/**
  * @brief  Disable the Battery charging.
  * @retval None.
  */
void HAL_PWREx_DisableBatteryCharging(void)
{
  CLEAR_BIT(PWR->BDCR2, PWR_BDCR2_VBE);
}

/**
  * @brief  This function handles the PWR PVD/PVM interrupt request.
  * @note   This API should be called under the PVD_PVM_IRQHandler().
  * @retval None.
  */
void HAL_PWREx_PVD_PVM_IRQHandler(void)
{
  uint32_t  rising_flag;
  uint32_t  falling_flag;

  /* Get pending flags */
  rising_flag = READ_REG(EXTI->RPR1);
  falling_flag = READ_REG(EXTI->FPR1);

  /* Check PWR exti flags for PVD */
  if (((rising_flag | falling_flag) & PWR_EXTI_LINE_PVD) != 0U)
  {
    /* PWR PVD interrupt user callback */
    HAL_PWR_PVDCallback();

    /* Clear PVD exti pending bit */
    WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_PVD);
    WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_PVD);
  }

  /* Check PWR exti flags for UVM */
  if (((rising_flag | falling_flag) & PWR_EXTI_LINE_UVM) != 0U)
  {
    /* PWR UVM interrupt user callback */
    HAL_PWREx_UVMCallback();

    /* Clear UVM exti pending bit */
    WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_UVM);
    WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_UVM);
  }

  /* Check PWR exti flags for IO2VM */
  if (((rising_flag | falling_flag) & PWR_EXTI_LINE_IO2VM) != 0U)
  {
    /* PWR IO2VM interrupt user callback */
    HAL_PWREx_IO2VMCallback();

    /* Clear IO2VM exti pending bit */
    WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_IO2VM);
    WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_IO2VM);
  }

  /* Check PWR exti flags for AVM1 */
  if (((rising_flag | falling_flag) & PWR_EXTI_LINE_AVM1) != 0U)
  {
    /* PWR AVM1 interrupt user callback */
    HAL_PWREx_AVM1Callback();

    /* Clear AVM1 exti pending bit */
    WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_AVM1);
    WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_AVM1);
  }

  /* Check PWR exti flags for AVM2 */
  if (((rising_flag | falling_flag) & PWR_EXTI_LINE_AVM2) != 0U)
  {
    /* PWR AVM2 interrupt user callback */
    HAL_PWREx_AVM2Callback();

    /* Clear AVM2 exti pending bit */
    WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_AVM2);
    WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_AVM2);
  }
}

/**
  * @brief  PWR UVM interrupt callback.
  * @retval None.
  */
__weak void HAL_PWREx_UVMCallback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWREx_UVMCallback() API can be implemented in the user file
   */
}

/**
  * @brief  PWR IO2VM interrupt callback.
  * @retval None.
  */
__weak void HAL_PWREx_IO2VMCallback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWREx_IO2VMCallback() API can be implemented in the user file
   */
}

/**
  * @brief  PWR AVM1 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWREx_AVM1Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWREx_AVM1Callback() API can be implemented in the user file
   */
}

/**
  * @brief  PWR AVM2 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWREx_AVM2Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWREx_AVM2Callback() API can be implemented in the user file
   */
}
/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group4 Memories Retention Functions
  * @brief    Memories retention functions
  *
@verbatim
 ===============================================================================
                     ##### Memories Retention Functions #####
 ===============================================================================
    [..]
      Several STM32U5 devices RAMs are configurable to keep / lose RAMs content
      during Stop mode (Stop 0/1/2/3).
       (+) Retained content RAMs in Stop modes are :
             (++) SRAM1
             (++) SRAM2
             (++) SRAM3
             (++) SRAM4
             (++) ICACHE
             (++) DMA2DRAM
             (++) PKA32RAM
             (++) DCACHE
             (++) FMAC
             (++) FDCAN
             (++) USB

    [..]
      Several STM32U5 devices RAMs are configurable to keep / lose RAMs content
      during Run mode.
       (+) Retained content RAMs in Run modes are :
             (++) SRAM1
             (++) SRAM2
             (++) SRAM3
             (++) SRAM4

    [..]
      SRAM2 is configurable to keep / lose its content in Stop 3 and Standby
      modes. The SRAM2 retention feature granularity is at pages level.

    [..]
      BKPRAM is configurable to keep / lose its content in Standby, Shutdown and
      VBAT modes.

@endverbatim
  * @{
  */

/**
  * @brief  Enable SRAM2 page(s) content retention in Stop 3 and Standby mode.
  * @note   When RRSx bit is set, SRAM2 is powered by the low-power regulator in
  *         Stop 3 and Standby mode and its content is kept.
  * @param  SRAM2Pages : Specifies the SRAM2 pages.
  *                      This parameter can be one of the following values :
  *                      @arg PWR_SRAM2_PAGE1_STANDBY_RETENTION : SRAM2 page 1 retention.
  *                      @arg PWR_SRAM2_PAGE2_STANDBY_RETENTION : SRAM2 page 2 retention.
  *                      @arg PWR_SRAM2_FULL_STANDBY_RETENTION  : SRAM2 page 1 and page 2 retention.
  * @retval None.
  */
void HAL_PWREx_EnableSRAM2ContentStandbyRetention(uint32_t SRAM2Pages)
{
  /* Check the parameters */
  assert_param(IS_PWR_SRAM2_STANDBY_RETENTION(SRAM2Pages));

  /* Set RRSx bit(s) */
  SET_BIT(PWR->CR1, SRAM2Pages);
}

/**
  * @brief  Disable SRAM2 page(s) content retention in Stop 3 and Standby mode.
  * @note   When RRSx bit is reset, SRAM2 is powered off in Stop 3 and Standby
  *         mode and its content is lost.
  * @param  SRAM2Pages : Specifies the SRAM2 pages.
  *                      This parameter can be one of the following values :
  *                      @arg PWR_SRAM2_PAGE1_STANDBY_RETENTION : SRAM2 page 1 retention.
  *                      @arg PWR_SRAM2_PAGE2_STANDBY_RETENTION : SRAM2 page 2 retention.
  *                      @arg PWR_SRAM2_FULL_STANDBY_RETENTION  : SRAM2 page 1 and page 2 retention.
  * @retval None.
  */
void HAL_PWREx_DisableSRAM2ContentStandbyRetention(uint32_t SRAM2Pages)
{
  /* Check the parameters */
  assert_param(IS_PWR_SRAM2_STANDBY_RETENTION(SRAM2Pages));

  /* Clear RRSx bit(s) */
  CLEAR_BIT(PWR->CR1, SRAM2Pages);
}

/**
  * @brief  Enable RAM page(s) content retention in Stop mode (Stop 0, 1, 2, 3).
  * @note   When enabling content retention for a given RAM, memory kept powered
  *         in Stop mode. (Not optimized power consumption)
  * @param RAMSelection: Specifies RAM page(s) to be retained in Stop mode.
  *                      This parameter can be one or a combination of the same
  *                      memory @ref PWREx_RAM_Contents_Stop_Retention.
  * @retval None.
  */
void HAL_PWREx_EnableRAMsContentStopRetention(uint32_t RAMSelection)
{
  uint32_t dummy;

  /* Check RAM ID */
  switch (RAMSelection & SRAM_ID_MASK)
  {
    /* SRAM 1 Stop retention */
    case SRAM1_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_SRAM1_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & ~SRAM_ID_MASK) & (PAGE01_ID | PAGE02_ID | PAGE03_ID);
      CLEAR_BIT(PWR->CR2, dummy);

      break;
    }

    /* SRAM 2 Stop retention */
    case SRAM2_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_SRAM2_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & PWR_SRAM2_FULL_STOP_RETENTION) & ~SRAM_ID_MASK;
      CLEAR_BIT(PWR->CR2, (dummy << PWR_CR2_SRAM2PDS1_Pos));

      break;
    }

    /* SRAM 3 Stop retention */
    case SRAM3_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_SRAM3_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & ~SRAM_ID_MASK) & (PAGE01_ID | PAGE02_ID | PAGE03_ID | PAGE04_ID |
                                                PAGE05_ID | PAGE06_ID | PAGE07_ID | PAGE08_ID);
      CLEAR_BIT(PWR->CR2, (dummy << PWR_CR2_SRAM3PDS1_Pos));

      break;
    }

    /* SRAM 4 Stop retention */
    case SRAM4_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_SRAM4_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & PWR_SRAM4_FULL_STOP_RETENTION) & ~SRAM_ID_MASK;
      CLEAR_BIT(PWR->CR2, (dummy << PWR_CR2_SRAM4PDS_Pos));

      break;
    }

    /* ICACHE RAM Stop retention */
    case ICACHERAM_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_ICACHE_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & PWR_ICACHE_FULL_STOP_RETENTION) & ~SRAM_ID_MASK;
      CLEAR_BIT(PWR->CR2, dummy << PWR_CR2_ICRAMPDS_Pos);

      break;
    }

    /* DCACHE1 RAM Stop retention */
    case DCACHE1RAM_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_DCACHE1_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & PWR_DCACHE1_FULL_STOP_RETENTION) & ~SRAM_ID_MASK;
      CLEAR_BIT(PWR->CR2, dummy << PWR_CR2_DC1RAMPDS_Pos);

      break;
    }

    /* DMA2D RAM Stop retention */
    case DMA2DRAM_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_DMA2DRAM_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & PWR_DMA2DRAM_FULL_STOP_RETENTION) & ~SRAM_ID_MASK;
      CLEAR_BIT(PWR->CR2, (dummy << PWR_CR2_DMA2DRAMPDS_Pos));

      break;
    }

    /* FMAC, FDCAN and USB RAM Stop retention */
    case PERIPHRAM_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_PERIPHRAM_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & PWR_PERIPHRAM_FULL_STOP_RETENTION) & ~SRAM_ID_MASK;
      CLEAR_BIT(PWR->CR2, (dummy << PWR_CR2_PRAMPDS_Pos));

      break;
    }

    /* PKA32 RAM Stop retention */
    case PKARAM_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_PKA32RAM_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & PWR_PKA32RAM_FULL_STOP_RETENTION) & ~SRAM_ID_MASK;
      CLEAR_BIT(PWR->CR2, (dummy << PWR_CR2_PKARAMPDS_Pos));

      break;
    }

    default:
    {
      return;
      break;
    }
  }
}

/**
  * @brief Disable RAM page(s) content lost in Stop mode (Stop 0, 1, 2, 3).
  * @note  When disabling content lost for a given RAM, memory powered down
  *        in Stop mode. (Optimized power consumption)
  * @param RAMSelection: Specifies RAM page(s) to be lost in Stop mode.
  *                      This parameter can be one or a combination of the same
  *                      memory @ref PWREx_RAM_Contents_Stop_Retention.
  * @retval None.
  */
void HAL_PWREx_DisableRAMsContentStopRetention(uint32_t RAMSelection)
{
  uint32_t dummy;

  /* Check RAM ID */
  switch (RAMSelection & SRAM_ID_MASK)
  {
    /* SRAM 1 Stop retention */
    case SRAM1_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_SRAM1_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy   = (RAMSelection & ~SRAM_ID_MASK) & (PAGE01_ID | PAGE02_ID | PAGE03_ID);
      SET_BIT(PWR->CR2, dummy);

      break;
    }

    /* SRAM 2 Stop retention */
    case SRAM2_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_SRAM2_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & PWR_SRAM2_FULL_STOP_RETENTION) & ~SRAM_ID_MASK;
      SET_BIT(PWR->CR2, (dummy << PWR_CR2_SRAM2PDS1_Pos));

      break;
    }

    /* SRAM 3 Stop retention */
    case SRAM3_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_SRAM3_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & ~SRAM_ID_MASK) & (PAGE01_ID | PAGE02_ID | PAGE03_ID | PAGE04_ID |
                                                PAGE05_ID | PAGE06_ID | PAGE07_ID | PAGE08_ID);
      SET_BIT(PWR->CR2, (dummy << PWR_CR2_SRAM3PDS1_Pos));

      break;
    }

    /* SRAM 4 Stop retention */
    case SRAM4_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_SRAM4_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & PWR_SRAM4_FULL_STOP_RETENTION) & ~SRAM_ID_MASK;
      SET_BIT(PWR->CR2, (dummy << PWR_CR2_SRAM4PDS_Pos));

      break;
    }

    /* ICACHE RAM Stop retention */
    case ICACHERAM_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_ICACHE_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & PWR_ICACHE_FULL_STOP_RETENTION) & ~SRAM_ID_MASK;
      SET_BIT(PWR->CR2, (dummy << PWR_CR2_ICRAMPDS_Pos));

      break;
    }

    /* DCACHE1 RAM Stop retention */
    case DCACHE1RAM_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_DCACHE1_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & PWR_DCACHE1_FULL_STOP_RETENTION) & ~SRAM_ID_MASK;
      SET_BIT(PWR->CR2, (dummy << PWR_CR2_DC1RAMPDS_Pos));

      break;
    }

    /* DMA2D RAM Stop retention */
    case DMA2DRAM_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_DMA2DRAM_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & PWR_DMA2DRAM_FULL_STOP_RETENTION) & ~SRAM_ID_MASK;
      SET_BIT(PWR->CR2, (dummy << PWR_CR2_DMA2DRAMPDS_Pos));

      break;
    }

    /* FMAC, FDCAN and USB RAM Stop retention */
    case PERIPHRAM_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_PERIPHRAM_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & PWR_PERIPHRAM_FULL_STOP_RETENTION) & ~SRAM_ID_MASK;
      SET_BIT(PWR->CR2, (dummy << PWR_CR2_PRAMPDS_Pos));

      break;
    }

    /* PKA32 RAM Stop retention */
    case PKARAM_ID:
    {
      /* Check the parameters */
      assert_param(IS_PWR_PKA32RAM_STOP_RETENTION(RAMSelection));

      /* Calculate pages mask */
      dummy = (RAMSelection & PWR_PKA32RAM_FULL_STOP_RETENTION) & ~SRAM_ID_MASK;
      SET_BIT(PWR->CR2, (dummy << PWR_CR2_PKARAMPDS_Pos));

      break;
    }

    default:
    {
      return;
      break;
    }
  }
}

/**
  * @brief  Enable RAMs full content retention in Run mode.
  * @param  RAMSelection : Specifies the SRAM content to be retained in Run mode.
  *                        This parameter can be one or a combination of the following values :
  *                        @arg PWR_SRAM1_FULL_RUN_RETENTION : SRAM1 full content retention.
  *                        @arg PWR_SRAM2_FULL_RUN_RETENTION : SRAM2 full content retention.
  *                        @arg PWR_SRAM3_FULL_RUN_RETENTION : SRAM3 full content retention.
  *                        @arg PWR_SRAM4_FULL_RUN_RETENTION : SRAM4 full content retention.
  * @retval None.
  */
void HAL_PWREx_EnableRAMsContentRunRetention(uint32_t RAMSelection)
{
  /* Check the parameters */
  assert_param(IS_PWR_RAM_RUN_RETENTION(RAMSelection));

  /* Enable RAM retention in Run mode */
  CLEAR_BIT(PWR->CR1, RAMSelection);
}

/**
  * @brief  Disable RAMs full content retention in Run mode.
  * @param  RAMSelection : Specifies the SRAM content to be lost in Run mode.
  *                        This parameter can be one or a combination of the following values :
  *                        @arg PWR_SRAM1_FULL_RUN_RETENTION : SRAM1 full content lost.
  *                        @arg PWR_SRAM2_FULL_RUN_RETENTION : SRAM2 full content lost.
  *                        @arg PWR_SRAM3_FULL_RUN_RETENTION : SRAM3 full content lost.
  *                        @arg PWR_SRAM4_FULL_RUN_RETENTION : SRAM4 full content lost.
  * @retval None.
  */
void HAL_PWREx_DisableRAMsContentRunRetention(uint32_t RAMSelection)
{
  /* Check the parameters */
  assert_param(IS_PWR_RAM_RUN_RETENTION(RAMSelection));

  /* Disable RAM retention in Run mode */
  SET_BIT(PWR->CR1, RAMSelection);
}

/**
  * @brief  Enable the Backup RAM retention in Standby, Shutdown and VBAT modes.
  * @note   If BREN is reset, the backup RAM can still be used in Run, Sleep and
  *         Stop modes. However, its content is lost in Standby, Shutdown and
  *         VBAT modes.
  * @note   This bit can be enabled only when LDO regulator is selected as
  *         source supply.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_EnableBkupRAMRetention(void)
{
  /*
    Backup RAM retention in Standby, Shutdown and VBAT should be enabled
    when the Vcore is alimented by the LDO regulator
  */
  if (HAL_PWREx_GetSupplyConfig() == PWR_LDO_SUPPLY)
  {
    SET_BIT(PWR->BDCR1, PWR_BDCR1_BREN);
  }
  /* SMPS regulator selected */
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the Backup RAM retention in Standby, Shutdown and VBAT modes.
  * @note   If BREN is reset, the backup RAM can still be used in Run, Sleep and
  *         Stop modes. However, its content is lost in Standby, Shutdown and
  *         VBAT modes. This bit can be writte
  * @retval None.
  */
void HAL_PWREx_DisableBkupRAMRetention(void)
{
  CLEAR_BIT(PWR->BDCR1, PWR_BDCR1_BREN);
}

/**
  * @brief  Enable the flash memory fast wakeup from Stop 0 and Stop 1 modes.
  * @note   This feature is used to obtain the best trade-off between low-power
  *         consumption and wakeup time when exiting the Stop 0 or Stop 1 modes.
  *         When this feature is enabled, the Flash memory remains in normal
  *         mode in Stop 0 and Stop 1 modes, which offers a faster startup time
  *         with higher consumption.
  * @retval None.
  */
void HAL_PWREx_EnableFlashFastWakeUp(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_FLASHFWU);
}

/**
  * @brief  Disable the Flash Power Down in Stop mode.
  * @note   This feature is used to obtain the best trade-off between low-power
  *         consumption and wakeup time when exiting the Stop 0 or Stop 1 modes.
  *         When this feature is disabled, the Flash memory enters low-power
  *         mode in Stop 0 and Stop 1 modes, which causes a slower startup time
  *         with lower consumption.
  * @retval None.
  */
void HAL_PWREx_DisableFlashFastWakeUp(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_FLASHFWU);
}

/**
  * @brief  Enable the SRAM4 memory fast wakeup from Stop 0, Stop 1 and Stop 2 modes.
  * @note   This bit is used to obtain the best trade-off between low-power consumption
  *         and wakeup time. SRAM4 wakeup time increases the wakeup time when exiting
  *         Stop 0, Stop 1 and Stop 2 modes, and also increases the LPDMA access time
  *         to SRAM4 during Stop modes.
  * @retval None.
  */
void HAL_PWREx_EnableSRAM4FastWakeUp(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_SRAM4FWU);
}

/**
  * @brief  Disable the SRAM4 memory fast wakeup from Stop 0, Stop 1 and Stop 2 modes.
  * @note   This bit is used to obtain the best trade-off between low-power consumption
  *         and wakeup time. SRAM4 wakeup time increases the wakeup time when exiting
  *         Stop 0, Stop 1 and Stop 2 modes, and also increases the LPDMA access time
  *         to SRAM4 during Stop modes.
  * @retval None.
  */
void HAL_PWREx_DisableSRAM4FastWakeUp(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_SRAM4FWU);
}
/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group5 I/O Pull-Up Pull-Down Configuration Functions
  * @brief    I/O pull-up / pull-down configuration functions
  *
@verbatim
 ===============================================================================
                     ##### Voltage monitoring Functions #####
 ===============================================================================
    [..]
      In Standby and Shutdown mode, pull up and pull down can be configured to
      maintain an I/O in the selected state. If the APC bit in the PWR_APCR
      register is set, the I/Os can be configured either with a pull-up through
      PWR_PUCRx registers (x=A,B,C,D,E,F,G,H,I), or with a pull-down through
      PWR_PDCRx registers (x=A,B,C,D,E,F,G,H,I)), or can be kept in analog state
      if none of the PWR_PUCRx or PWR_PDCRx register is set.

    [..]
      The pull-down configuration has highest priority over pull-up
      configuration in case both PWR_PUCRx and PWR_PDCRx are set for the same
      I/O.
      This configuration is lost when exiting the Shutdown but not from Standby
      mode.

@endverbatim
  * @{
  */

/**
  * @brief  Enable pull-up and pull-down configuration.
  * @note   When APC bit is set, the I/O pull-up and pull-down configurations
  *         defined in PWR_PUCRx and PWR_PDCRx registers are applied in Standby
  *         and Shutdown modes.
  * @note   Pull-up set by PUy bit of PWR_PUCRx register is not activated if the
  *         corresponding PDy bit of PWR_PDCRx register is also set (pull-down
  *         configuration priority is higher). HAL_PWREx_EnableGPIOPullUp() and
  *         HAL_PWREx_EnableGPIOPullDown() API's ensure there is no conflict
  *         when setting PUy or PDy bit.
  * @retval None.
  */
void HAL_PWREx_EnablePullUpPullDownConfig(void)
{
  SET_BIT(PWR->APCR, PWR_APCR_APC);
}

/**
  * @brief  Disable pull-up and pull-down configuration.
  * @note   When APC bit is cleared, the I/O pull-up and pull-down configurations
  *         defined in PWR_PUCRx and PWR_PDCRx registers are not applied in
  *         Standby and Shutdown modes.
  * @retval None.
  */
void HAL_PWREx_DisablePullUpPullDownConfig(void)
{
  CLEAR_BIT(PWR->APCR, PWR_APCR_APC);
}

/**
  * @brief  Enable GPIO pull-up state in Standby and Shutdown modes.
  * @note   Set the relevant PUy bits of PWR_PUCRx register to configure the I/O
  *         in pull-up state in Standby and Shutdown modes.
  * @note   This state is effective in Standby and Shutdown modes only if APC
  *         bit is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note   The configuration is lost when exiting the Shutdown mode due to the
  *         power-on reset, maintained when exiting the Standby mode.
  * @note   To avoid any conflict at Standby and Shutdown modes exits, the
  *         corresponding PDy bit of PWR_PDCRx register is cleared unless it is
  *         reserved.
  * @note   Even if a PUy bit to set is reserved, the other PUy bits entered as
  *         input parameter at the same time are set.
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Port.
  * @param  GPIO_Pin  : Specify the I/O pins numbers.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Pin_Mask.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  /* Check GPIO port */
  switch (GPIO_Port)
  {
    case PWR_GPIO_A: /* Apply Pull Up to GPIO port A */
      SET_BIT(PWR->PUCRA, (GPIO_Pin & (~(PWR_GPIO_BIT_14))));
      CLEAR_BIT(PWR->PDCRA, (GPIO_Pin & (~(PWR_GPIO_BIT_13 | PWR_GPIO_BIT_15))));
      break;

    case PWR_GPIO_B: /* Apply Pull Up to GPIO port B */
      SET_BIT(PWR->PUCRB, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRB, (GPIO_Pin & (~(PWR_GPIO_BIT_4))));
      break;

    case PWR_GPIO_C: /* Apply Pull Up to GPIO port C */
      SET_BIT(PWR->PUCRC, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRC, GPIO_Pin);
      break;

    case PWR_GPIO_D: /* Apply Pull Up to GPIO port D */
      SET_BIT(PWR->PUCRD, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRD, GPIO_Pin);
      break;

    case PWR_GPIO_E: /* Apply Pull Up to GPIO port E */
      SET_BIT(PWR->PUCRE, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRE, GPIO_Pin);
      break;

    case PWR_GPIO_F: /* Apply Pull Up to GPIO port F */
      SET_BIT(PWR->PUCRF, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRF, GPIO_Pin);
      break;

    case PWR_GPIO_G: /* Apply Pull Up to GPIO port G */
      SET_BIT(PWR->PUCRG, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRG, GPIO_Pin);
      break;

    case PWR_GPIO_H: /* Apply Pull Up to GPIO port H */
      SET_BIT(PWR->PUCRH, GPIO_Pin);
      CLEAR_BIT(PWR->PDCRH, GPIO_Pin);
      break;

    case PWR_GPIO_I: /* Apply Pull Up to GPIO port I */
      SET_BIT(PWR->PUCRI, (GPIO_Pin & PWR_PORTI_AVAILABLE_PINS));
      CLEAR_BIT(PWR->PDCRI, (GPIO_Pin & PWR_PORTI_AVAILABLE_PINS));
      break;

    default:
      return HAL_ERROR;
      break;
  }

  return HAL_OK;
}

/**
  * @brief Disable GPIO pull-up state in Standby mode and Shutdown modes.
  * @note  Reset the relevant PUy bits of PWR_PUCRx register used to configure
  *        the I/O in pull-up state in Standby and Shutdown modes.
  * @note  Even if a PUy bit to reset is reserved, the other PUy bits entered as
  *        input parameter at the same time are reset.
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Port.
  * @param  GPIO_Pin  : Specify the I/O pins numbers.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Pin_Mask.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  /* Check GPIO port */
  switch (GPIO_Port)
  {
    case PWR_GPIO_A: /* Disable Pull Up for GPIO port A */
      CLEAR_BIT(PWR->PUCRA, (GPIO_Pin & (~(PWR_GPIO_BIT_14))));
      break;

    case PWR_GPIO_B: /* Disable Pull Up for GPIO port B */
      CLEAR_BIT(PWR->PUCRB, GPIO_Pin);
      break;

    case PWR_GPIO_C: /* Disable Pull Up for GPIO port C */
      CLEAR_BIT(PWR->PUCRC, GPIO_Pin);
      break;

    case PWR_GPIO_D: /* Disable Pull Up for GPIO port D */
      CLEAR_BIT(PWR->PUCRD, GPIO_Pin);
      break;

    case PWR_GPIO_E: /* Disable Pull Up for GPIO port E */
      CLEAR_BIT(PWR->PUCRE, GPIO_Pin);
      break;

    case PWR_GPIO_F: /* Disable Pull Up for GPIO port F */
      CLEAR_BIT(PWR->PUCRF, GPIO_Pin);
      break;

    case PWR_GPIO_G: /* Disable Pull Up for GPIO port G */
      CLEAR_BIT(PWR->PUCRG, GPIO_Pin);
      break;

    case PWR_GPIO_H: /* Disable Pull Up for GPIO port H */
      CLEAR_BIT(PWR->PUCRH, GPIO_Pin);
      break;

    case PWR_GPIO_I: /* Disable Pull Up for GPIO port I */
      CLEAR_BIT(PWR->PUCRI, (GPIO_Pin & PWR_PORTI_AVAILABLE_PINS));
      break;

    default:
      return HAL_ERROR;
      break;
  }

  return HAL_OK;
}

/**
  * @brief Enable GPIO pull-down state in Standby and Shutdown modes.
  * @note  Set the relevant PDy bits of PWR_PDCRx register to configure the I/O
  *        in pull-down state in Standby and Shutdown modes.
  * @note  This state is effective in Standby and Shutdown modes only if APC bit
  *        is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note  The configuration is lost when exiting the Shutdown mode due to the
  *        power-on reset, maintained when exiting the Standby mode.
  * @note  To avoid any conflict at Standby and Shutdown modes exits, the
  *        corresponding PUy bit of PWR_PUCRx register is cleared unless it is
  *        reserved.
  * @note  Even if a PDy bit to set is reserved, the other PDy bits entered as
  *        input parameter at the same time are set.
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Port.
  * @param  GPIO_Pin  : Specify the I/O pins numbers.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Pin_Mask.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  /* Check GPIO port */
  switch (GPIO_Port)
  {
    case PWR_GPIO_A: /* Apply Pull Down to GPIO port A */
      SET_BIT(PWR->PDCRA, (GPIO_Pin & (~(PWR_GPIO_BIT_13 | PWR_GPIO_BIT_15))));
      CLEAR_BIT(PWR->PUCRA, (GPIO_Pin & (~(PWR_GPIO_BIT_14))));
      break;

    case PWR_GPIO_B: /* Apply Pull Down to GPIO port B */
      SET_BIT(PWR->PDCRB, (GPIO_Pin & (~(PWR_GPIO_BIT_4))));
      CLEAR_BIT(PWR->PUCRB, GPIO_Pin);
      break;

    case PWR_GPIO_C: /* Apply Pull Down to GPIO port C */
      SET_BIT(PWR->PDCRC, GPIO_Pin);
      CLEAR_BIT(PWR->PUCRC, GPIO_Pin);
      break;

    case PWR_GPIO_D: /* Apply Pull Down to GPIO port D */
      SET_BIT(PWR->PDCRD, GPIO_Pin);
      CLEAR_BIT(PWR->PUCRD, GPIO_Pin);
      break;

    case PWR_GPIO_E: /* Apply Pull Down to GPIO port E */
      SET_BIT(PWR->PDCRE, GPIO_Pin);
      CLEAR_BIT(PWR->PUCRE, GPIO_Pin);
      break;

    case PWR_GPIO_F: /* Apply Pull Down to GPIO port F */
      SET_BIT(PWR->PDCRF, GPIO_Pin);
      CLEAR_BIT(PWR->PUCRF, GPIO_Pin);
      break;

    case PWR_GPIO_G: /* Apply Pull Down to GPIO port G */
      SET_BIT(PWR->PDCRG, GPIO_Pin);
      CLEAR_BIT(PWR->PUCRG, GPIO_Pin);
      break;

    case PWR_GPIO_H: /* Apply Pull Down to GPIO port H */
      SET_BIT(PWR->PDCRH, GPIO_Pin);
      CLEAR_BIT(PWR->PUCRH, GPIO_Pin);
      break;

    case PWR_GPIO_I: /* Apply Pull Down to GPIO port I */
      SET_BIT(PWR->PDCRI, (GPIO_Pin & PWR_PORTI_AVAILABLE_PINS));
      CLEAR_BIT(PWR->PUCRI, (GPIO_Pin & PWR_PORTI_AVAILABLE_PINS));
      break;

    default:
      return HAL_ERROR;
      break;
  }

  return HAL_OK;
}

/**
  * @brief Disable GPIO pull-down state in Standby and Shutdown modes.
  * @note  Reset the relevant PDy bits of PWR_PDCRx register used to configure the I/O
  *        in pull-down state in Standby and Shutdown modes.
  * @note  Even if a PDy bit to reset is reserved, the other PDy bits entered as input
  *        parameter at the same time are reset.
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Port.
  * @param  GPIO_Pin  : Specify the I/O pins numbers.
  *                     This parameter can be a value of
  *                     @ref PWREx_GPIO_Pin_Mask.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  /* Check GPIO port */
  switch (GPIO_Port)
  {
    case PWR_GPIO_A: /* Disable Pull Down for GPIO port A */
      CLEAR_BIT(PWR->PDCRA, (GPIO_Pin & (~(PWR_GPIO_BIT_13 | PWR_GPIO_BIT_15))));
      break;

    case PWR_GPIO_B: /* Disable Pull Down for GPIO port B */
      CLEAR_BIT(PWR->PDCRB, (GPIO_Pin & (~(PWR_GPIO_BIT_4))));
      break;

    case PWR_GPIO_C: /* Disable Pull Down for GPIO port C */
      CLEAR_BIT(PWR->PDCRC, GPIO_Pin);
      break;

    case PWR_GPIO_D: /* Disable Pull Down for GPIO port D */
      CLEAR_BIT(PWR->PDCRD, GPIO_Pin);
      break;

    case PWR_GPIO_E: /* Disable Pull Down for GPIO port E */
      CLEAR_BIT(PWR->PDCRE, GPIO_Pin);
      break;

    case PWR_GPIO_F: /* Disable Pull Down for GPIO port F */
      CLEAR_BIT(PWR->PDCRF, GPIO_Pin);
      break;

    case PWR_GPIO_G: /* Disable Pull Down for GPIO port G */
      CLEAR_BIT(PWR->PDCRG, GPIO_Pin);
      break;

    case PWR_GPIO_H: /* Disable Pull Down for GPIO port H */
      CLEAR_BIT(PWR->PDCRH, GPIO_Pin);
      break;

    case PWR_GPIO_I: /* Disable Pull Down for GPIO port I */
      CLEAR_BIT(PWR->PDCRI, (GPIO_Pin & PWR_PORTI_AVAILABLE_PINS));
      break;

    default:
      return HAL_ERROR;
      break;
  }

  return HAL_OK;
}
/**
  * @}
  */

#endif /* defined (HAL_PWR_MODULE_ENABLED) */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
