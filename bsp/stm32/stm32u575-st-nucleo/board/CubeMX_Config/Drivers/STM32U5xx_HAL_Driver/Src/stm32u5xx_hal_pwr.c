/**
  ******************************************************************************
  * @file    stm32u5xx_hal_pwr.c
  * @author  MCD Application Team
  * @brief   PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Initialization/De-Initialization Functions.
  *           + Peripheral Control Functions.
  *           + PWR Attributes Functions.
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
                        ##### PWR peripheral overview #####
  ==============================================================================
  [..]
   (#) The Power control (PWR) provides an overview of the supply architecture
       for the different power domains and of the supply configuration
       controller.

   (#) Domain architecture overview for the U5 devices:
      (+) U5 devices have 2 power domains (CD and SRD).
          The core domain (CD) contains a CPU (Cortex-M33), a Flash memory and
          some peripherals dedicated for general purpose. The SRD domain
          contains the system control and low-power peripherals.

   (#) Every entity has low power mode as described below :
   (#) The CPU low power modes are :
      (+) CPU CRun.
      (+) CPU CSleep.
      (+) CPU CStop.
   (#) The system low power modes are :
      (+) Run.
      (+) Stop 0.
      (+) Stop 1.
      (+) Stop 2.
      (+) Stop 3.
      (+) Standby.
      (+) Shutdown.

  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
   (#) After startup, power management peripheral is not active by default. Use
       __HAL_RCC_PWR_CLK_ENABLE() macro to enable power interface.

   (#) Call HAL_PWR_EnableBkUpAccess() and HAL_PWR_DisableBkUpAccess() functions
       to enable/disable access to the backup domain (RCC Backup domain control
       register RCC_BDCR, RTC registers, TAMP registers, backup registers and
       backup SRAM).

   (#) Call HAL_PWR_ConfigPVD() after setting parameters to be configured (event
       mode and voltage threshold) in order to set up the Programmed Voltage
       Detector, then use HAL_PWR_EnablePVD() and  HAL_PWR_DisablePVD()
       functions to start and stop the PVD detection.
       (+) PVD level can be one of the following values :
             (++) 2V0
             (++) 2V2
             (++) 2V4
             (++) 2V5
             (++) 2V6
             (++) 2V8
             (++) 2V9
             (++) External input analog voltage PVD_IN (compared internally to
                  VREFINT)

   (#) Call HAL_PWR_EnableWakeUpPin() and HAL_PWR_DisableWakeUpPin() functions
       with the right parameter to configure the wake up pin polarity (Low or
       High), the wake up pin selection and to enable and disable it.

   (#) Call HAL_PWR_EnterSLEEPMode() function to enter the CPU in Sleep mode.
       Wake-up from Sleep mode could be following to an event or an
       interrupt according to low power mode intrinsic request called (__WFI()
       or __WFE()).

   (#) Call HAL_PWR_EnterSTOPMode() function to enter the whole system to Stop 0
       mode. Wake-up from Stop 0 mode could be following to an event or an
       interrupt according to low power mode intrinsic request called (__WFI()
       or __WFE()). (Regulator state on U5 devices is managed internally but
       regulator parameter is kept for product compatibility).

   (#) Call HAL_PWR_EnterSTANDBYMode() function to enter the whole system in
       Standby mode. Wake-up from Standby mode can be following only by an
       interrupt.

   (#) Call HAL_PWR_EnableSleepOnExit() and HAL_PWR_DisableSleepOnExit() APIs to
       enable and disable the Cortex-M33 re-entry in Sleep mode after an
       interruption handling is over.

   (#) Call HAL_PWR_EnableSEVOnPend() and HAL_PWR_DisableSEVOnPend() functions
       to configure the Cortex-M33 to wake-up after any pending event / interrupt
       even if it's disabled or has insufficient priority to cause exception
       entry.

   (#) Call HAL_PWR_PVD_IRQHandler() under PVD_AVD_IRQHandler() function to
       handle the PWR PVD interrupt request.

   (#) Call HAL_PWR_ConfigAttributes() function to configure PWR item secure and
       privilege attributes and call HAL_PWR_GetConfigAttributes() function to
       get the attribute configuration for the selected item.

     *** PWR HAL driver macros list ***
     =============================================
     [..]
       Below the list of most used macros in PWR HAL driver.

      (+) __HAL_PWR_GET_FLAG()   : Get the PWR pending flags.
      (+) __HAL_PWR_CLEAR_FLAG() : Clear the PWR pending flags.

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup PWR PWR
  * @brief PWR HAL module driver
  * @{
  */

#if defined (HAL_PWR_MODULE_ENABLED)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup PWR_Private_Defines PWR Private Defines
  * @{
  */

/** @defgroup PWR_PVD_Mode_Mask PWR PVD Mode Mask
  * @{
  */
#define PVD_RISING_EDGE  (0x01U)  /*!< Mask for rising edge set as PVD trigger                 */
#define PVD_FALLING_EDGE (0x02U)  /*!< Mask for falling edge set as PVD trigger                */
#define PVD_MODE_IT      (0x04U)  /*!< Mask for interruption yielded by PVD threshold crossing */
#define PVD_MODE_EVT     (0x08U)  /*!< Mask for event yielded by PVD threshold crossing        */
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

/** @defgroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_Exported_Functions_Group1 Initialization and De-Initialization Functions
  *  @brief   Initialization and de-Initialization functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and De-Initialization Functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to deinitialize power peripheral
      and to manage backup domain access.

    [..]
      After system reset, the backup domain (RCC Backup domain control register
      RCC_BDCR, RTC registers, TAMP registers, backup registers and backup SRAM)
      is protected against possible unwanted write accesses.
      The HAL_PWR_EnableBkUpAccess() function enables the access to the backup
      domain.
      The HAL_PWR_DisableBkUpAccess() function disables the access to the backup
      domain.

@endverbatim
  * @{
  */

/**
  * @brief  Deinitialize the HAL PWR peripheral registers to their default reset
  *         values.
  * @note   This functionality is not available in this product.
  *         The prototype is kept just to maintain compatibility with other
  *         products.
  * @retval None.
  */
void HAL_PWR_DeInit(void)
{
}

/**
  * @brief  Enable access to the backup domain (RCC Backup domain control
  *         register RCC_BDCR, RTC registers, TAMP registers, backup registers
  *         and backup SRAM).
  * @note   After a system reset, the backup domain is protected against
  *         possible unwanted write accesses.
  * @retval None.
  */
void HAL_PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->DBPR, PWR_DBPR_DBP);
}

/**
  * @brief  Disable access to the backup domain (RCC Backup domain control
  *         register RCC_BDCR, RTC registers, TAMP registers, backup registers
  *         and backup SRAM).
  * @retval None.
  */
void HAL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->DBPR, PWR_DBPR_DBP);
}
/**
  * @}
  */


/** @defgroup PWR_Exported_Functions_Group2 Peripheral Control Functions
  *  @brief   Low power modes configuration functions
  *
@verbatim
 ===============================================================================
                 ##### Peripheral Control functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to control power peripheral.

    *** PVD configuration ***
    =========================
    [..]
      (+) The PVD can be used to monitor the VDD power supply by comparing it
          to a threshold selected by the PVDLS[2:0] bits in the PWR supply
          voltage monitoring control register (PWR_SVMCR) and can be enabled by
          setting the PVDE bit.

      (+) A PVDO flag is available in the PWR supply voltage monitoring control
          register (PWR_SVMCR) to indicate if VDD is higher or lower than the
          PVD threshold. This event is internally connected to the EXTI line 16
          and can generate an interrupt if enabled through the EXTI registers.
          It is configurable through __HAL_PWR_PVD_EXTI_ENABLE_IT() macro.

      (+) The PVD can remain active in Stop 0, Stop 1, Stop 2 modes, and the PVM
          interrupt can wake up from the Stop mode. The PVD is not functional in
          Stop 3 mode.

      (+) During Stop 1, Stop 2 and Stop 3 modes, it is possible to set the PVD
          in ultra-low-power mode to further reduce the current consumption by
          setting the ULPMEN bit in PWR_CR1 register.

    *** Wake-up pin configuration ***
    =================================
    [..]
      (+) Wake-up pin is used to wake up the system from Stop 3, Standby and
          Shutdown mode.
          The pin selection is configurable through the WUCR3 register to map
          internal signal to wake up pin line.
          The pin polarity is configurable through the WUCR2 register to be
          active on rising or falling edges.

      (+) There are up to 24 wake-up signals that can be mapped to up to 8
          wake-up lines in the STM32U5 family.

    *** Low Power modes configuration ***
    =====================================
    [..]
      This section presents 3 principles low-power modes :
      (+) Sleep mode   : Cortex-M33 is stopped and all PWR domains are remaining
                         active (powered and clocked).

      (+) Stop 0 mode  : Cortex-M33 is stopped, clocks are stopped and the
                         regulator is running.

      (+) Standby mode : All PWR domains enter DSTANDBY mode and the VCORE
                         supply regulator is powered off.

   *** Sleep mode ***
   ==================
    [..]
      (+) Entry :
          The Sleep mode is entered by using the HAL_PWR_EnterSLEEPMode()
          function.

          (++) PWR_SLEEPENTRY_WFI: enter Sleep mode with WFI instruction.
          (++) PWR_SLEEPENTRY_WFE: enter Sleep mode with WFE instruction.

      -@@- The Regulator parameter is not used for the STM32U5 family and is
           kept as parameter just to maintain compatibility with other families.

      (+) Exit :
          According to Sleep entry, any event when entry is __WFE() intrinsic
          and any interrupt when entry is __WFI() intrinsic can wake up the
          device from Sleep mode.

   *** Stop 0 mode ***
   ===================
    [..]
      The Stop 0 mode is based on the Cortex-M33 Deepsleep mode combined with
      the peripheral clock gating. The voltage regulator is configured in main
      regulator mode. In Stop 0 mode, all clocks in the VCORE domain are stopped.
      The PLL, MSIS, MSIK, HSI16 and HSE oscillators are disabled.
      Some peripherals with the LPBAM capability can switch on HSI16 or MSIS or
      MSIK for transferring data. All SRAMs and register contents are preserved,
      but the SRAMs can be totally or partially switched off to further reduced
      consumption.
      The BOR is always available in Stop 0 mode.

      (+) Entry:
          The Stop mode is entered using the HAL_PWR_EnterSTOPMode() function
          with :

         (++) StopEntry:
          (+++) PWR_STOPENTRY_WFI: enter Stop mode with WFI instruction.
          (+++) PWR_STOPENTRY_WFE: enter Stop mode with WFE instruction.

      -@@- The Regulator parameter is not used for the STM32U5 family and is
           kept as parameter just to maintain compatibility with other families.

      (+) Exit:
          Any EXTI line configured in interrupt mode (the corresponding EXTI
          interrupt vector must be enabled in the NVIC). The interrupt source
          can be external interrupts or peripherals with wakeup capability.
          Any peripheral interrupt occurring when the AHB/APB clocks are present
          due to an autonomous peripheral clock request (the peripheral vector
          must be enabled in the NVIC).

   *** Standby mode ***
   ====================
    [..]
      The Standby mode is used to achieve the lowest power consumption with BOR.
      The internal regulator is switched off so that the VCORE domain is powered
      off.
      The PLL, the MSI (MSIS and MSIK) RC, the HSI16 RC and the HSE crystal
      oscillators are also switched off.
      The RTC can remain active (Standby mode with RTC, Standby mode without
      RTC).
      The Brownout reset (BOR) always remains active in Standby mode.
      The state of each I/O during Standby mode can be selected by software:
      I/O with internal pull-up, internal pull-down or floating.
      After entering Standby mode, SRAMs and register contents are lost except
      for registers and backup SRAM in the Backup domain and Standby circuitry.
      Optionally, the full SRAM2 or 8 Kbytes or 56 Kbytes can be retained in
      Standby mode, supplied by the low-power regulator (Standby with RAM2
      retention mode).
      The BORL (Brownout reset detector low) can be configured in ultra low
      power mode to further reduce power consumption during Standby mode.
      The device exits Standby mode upon an external reset (NRST pin), an IWDG
      reset, WKUP pin event (configurable rising or falling edge), an RTC event
      occurs (alarm, periodic wakeup, timestamp), or a tamper detection.
      The system clock after wakeup is MSIS up to 4 MHz.

      (++) Entry:
           The Standby mode is entered using the HAL_PWR_EnterSTANDBYMode()
           function.

      (++) Exit:
           WKUPx pin edge, RTC event, external Reset in NRST pin, IWDG Reset,
           BOR reset.

@endverbatim
  * @{
  */

/**
  * @brief  Configure the voltage threshold detected by the Programmed Voltage
  *         Detector (PVD).
  * @param  pConfigPVD : Pointer to a PWR_PVDTypeDef structure that contains the
  *                      PVD configuration information (PVDLevel and EventMode).
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWR_ConfigPVD(PWR_PVDTypeDef *pConfigPVD)
{
  /* Check the PVD parameter */
  if (pConfigPVD == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(pConfigPVD->PVDLevel));
  assert_param(IS_PWR_PVD_MODE(pConfigPVD->Mode));

  /* Set PVDLS[2:0] bits according to PVDLevel value */
  MODIFY_REG(PWR->SVMCR, PWR_SVMCR_PVDLS, pConfigPVD->PVDLevel);

  /* Disable PVD Event/Interrupt */
  __HAL_PWR_PVD_EXTI_DISABLE_EVENT();
  __HAL_PWR_PVD_EXTI_DISABLE_IT();
  __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();
  __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE();

  /* Configure the PVD in interrupt mode */
  if ((pConfigPVD->Mode & PVD_MODE_IT) == PVD_MODE_IT)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_IT();
  }

  /* Configure the PVD in event mode */
  if ((pConfigPVD->Mode & PVD_MODE_EVT) == PVD_MODE_EVT)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_EVENT();
  }

  /* Configure the PVD in rising edge */
  if ((pConfigPVD->Mode & PVD_RISING_EDGE) == PVD_RISING_EDGE)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();
  }

  /* Configure the PVD in falling edge */
  if ((pConfigPVD->Mode & PVD_FALLING_EDGE) == PVD_FALLING_EDGE)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();
  }

  return HAL_OK;
}

/**
  * @brief  Enable the programmable voltage detector (PVD).
  * @retval None.
  */
void HAL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->SVMCR, PWR_SVMCR_PVDE);
}

/**
  * @brief  Disable the programmable voltage detector (PVD).
  * @retval None.
  */
void HAL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->SVMCR, PWR_SVMCR_PVDE);
}

/**
  * @brief  Enable the wake up line functionality.
  * @note   Wake up lines are used to wake up the system from Stop 3, Standby and
  *         Shutdown modes.
  * @param  WakeUpPin : Specifies which wake up line to enable. This parameter
  *                     can be one of PWR_WakeUp_Pins_High_Polarity define
  *                     group where every param select the wake up line, the
  *                     wake up source with high polarity detection and the wake
  *                     up selected I/O or can be one of
  *                     PWR_WakeUp_Pins_Low_Polarity define group where every
  *                     param select the wake up line, the wake up source with
  *                     low polarity and the wake up selected I/O or can be one
  *                     of PWR_WakeUp_Pins define group where every param select
  *                     the wake up line, the wake up source with
  *                     high polarity and the first wake up I/O.
  * @retval None.
  */
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPin)
{
  /* Check the parameter */
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPin));

  /* Specifies the wake up line polarity for the event detection (rising or falling edge) */
  MODIFY_REG(PWR->WUCR2, (PWR_EWUP_MASK & WakeUpPin), (WakeUpPin >> PWR_WUP_POLARITY_SHIFT));

  /* Specifies the wake up line I/O selection */
  MODIFY_REG(PWR->WUCR3, (3UL << (POSITION_VAL(PWR_EWUP_MASK & WakeUpPin) * 2U)),
             (WakeUpPin >> PWR_WUP_SELECT_SIGNAL_SHIFT));

  /* Enable wake-up line */
  SET_BIT(PWR->WUCR1, (PWR_EWUP_MASK & WakeUpPin));
}

/**
  * @brief  Disable the wake up line functionality.
  * @param  WakeUpPin : Specifies the wake up line to disable.
  *                     This parameter can be a combination of all the following
  *                     values :
  *                     @arg @ref PWR_WAKEUP_PIN1
  *                     @arg @ref PWR_WAKEUP_PIN2
  *                     @arg @ref PWR_WAKEUP_PIN3
  *                     @arg @ref PWR_WAKEUP_PIN4
  *                     @arg @ref PWR_WAKEUP_PIN6
  *                     @arg @ref PWR_WAKEUP_PIN5
  *                     @arg @ref PWR_WAKEUP_PIN7
  *                     @arg @ref PWR_WAKEUP_PIN8
  * @retval None
  */
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPin)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPin));

  /* Disable wake-up pin */
  CLEAR_BIT(PWR->WUCR1, (PWR_EWUP_MASK & WakeUpPin));
}

/**
  * @brief  Enter the CPU in Sleep mode.
  * @note   In Sleep mode, all I/O pins keep the same state as in Run mode.
  * @note   CPU clock is off and all peripherals including Cortex-M33 core such
  *         as NVIC and SysTick can run and wake up the CPU when an interrupt
  *         or an event occurs.
  * @param  Regulator : Specifies the regulator state in Sleep mode.
  *                     This parameter can be one of the following values :
  *                     @arg @ref PWR_MAINREGULATOR_ON
  *                     @arg @ref PWR_LOWPOWERREGULATOR_ON
  * @note   This parameter is not available in this product.
  *         The parameter is kept just to maintain compatibility with other
  *         products.
  * @param  SleepEntry : Specifies if Sleep mode is entered with WFI or WFE
  *                      instruction.
  *                      This parameter can be one of the following values :
  *                      @arg @ref PWR_SLEEPENTRY_WFI enter Sleep mode with Wait
  *                                For Interrupt request.
  *                      @arg @ref PWR_SLEEPENTRY_WFE enter Sleep mode with Wait
  *                                For Event request.
  * @note   When WFI entry is used, ticks interrupt must be disabled to avoid
  *         unexpected CPU wake up.
  * @retval None.
  */
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SleepEntry)
{
  UNUSED(Regulator);

  /* Check the parameter */
  assert_param(IS_PWR_SLEEP_ENTRY(SleepEntry));

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select Sleep mode entry */
  if (SleepEntry == PWR_SLEEPENTRY_WFI)
  {
    /* Wait For Interrupt Request */
    __WFI();
  }
  else
  {
    /* Wait For Event Request */
    __SEV();
    __WFE();
    __WFE();
  }
}

/**
  * @brief  Enter the whole system to Stop 0 mode.
  * @note   In Stop 0 mode, the regulator remains in main regulator mode,
  *         allowing a very fast wakeup time but with much higher consumption
  *         comparing to other Stop modes.
  * @note   Stop 0 offers the largest number of active peripherals and wakeup
  *         sources, a smaller wakeup time but a higher consumption.
  *         Stop mode achieves the lowest power consumption while retaining
  *         the content of SRAM and registers. All clocks in the VCORE domain
  *         are stopped. The PLL, the MSI (MSIS and MSIK) RC, the HSI16 RC and
  *         the HSE crystal oscillators are disabled. The LSE or LSI is still
  *         running.
  * @note   The system clock when exiting from Stop mode can be either MSIS up
  *         to 24 MHz or HSI16, depending on software configuration.
  * @param  Regulator : Specifies the regulator state in Stop mode.
  *                     This parameter can be one of the following values :
  *                     @arg @ref PWR_MAINREGULATOR_ON
  *                     @arg @ref PWR_LOWPOWERREGULATOR_ON
  * @note   This parameter is not available in this product.
  *         The parameter is kept just to maintain compatibility with other
  *         products.
  * @param  StopEntry : Specifies if Stop mode is entered with WFI or WFE
  *                     instruction.
  *                     This parameter can be one of the following values :
  *                     @arg @ref PWR_STOPENTRY_WFI enter Stop mode with Wait
  *                               For Interrupt request.
  *                     @arg @ref PWR_STOPENTRY_WFE enter Stop mode with Wait
  *                               For Event request.
  * @retval None.
  */
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t StopEntry)
{
  UNUSED(Regulator);

  /* Check the parameter */
  assert_param(IS_PWR_STOP_ENTRY(StopEntry));

  /* Select Stop 0 mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, 0U);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select Stop mode entry */
  if (StopEntry == PWR_STOPENTRY_WFI)
  {
    /* Wait For Interrupt Request */
    __WFI();
  }
  else
  {
    /* Wait For Event Request */
    __SEV();
    __WFE();
    __WFE();
  }

  /* Reset SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief  Enter the whole system to Standby mode.
  * @note   The Standby mode is used to achieve the lowest power consumption
  *         with BOR. The internal regulator is switched off so that the VCORE
  *         domain is powered off. The PLL, the MSI (MSIS and MSIK) RC, the
  *         HSI16 RC and the HSE crystal oscillators are also switched off.
  * @note   After entering Standby mode, SRAMs and register contents are lost
  *         except for registers and backup SRAM in the Backup domain and
  *         Standby circuitry. Optionally, the full SRAM2 or 8 Kbytes or 56
  *         Kbytes can be retained in Standby mode, supplied by the low-power
  *         regulator (Standby with RAM2 retention mode) through
  *         HAL_PWREx_EnableSRAM2ContentStandbyRetention().
  * @note   The state of each I/O during Standby mode can be selected by
  *         software : I/O with internal pull-up through
  *         HAL_PWREx_EnableGPIOPullUp() and internal pull-down through
  *         HAL_PWREx_EnableGPIOPullDown().
  * @retval None.
  */
void HAL_PWR_EnterSTANDBYMode(void)
{
  /* Select Standby mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_CR1_LPMS_2);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM)
  __force_stores();
#endif /*( __CC_ARM)*/

  /* Wait For Interrupt Request */
  __WFI();
}

/**
  * @brief  Indicate SLEEP-ON-EXIT feature when returning from handler mode to
  *         thread mode.
  * @note   Set SLEEPONEXIT bit of SCR register. When this bit is set, the
  *         processor re-enters Sleep mode when an interruption handling is over.
  *         Setting this bit is useful when the processor is expected to run
  *         only on interruptions handling.
  * @retval None.
  */
void HAL_PWR_EnableSleepOnExit(void)
{
  /* Set SLEEPONEXIT bit of Cortex-M33 System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
}

/**
  * @brief  Disable SLEEP-ON-EXIT feature when returning from handler mode to
  *         thread mode.
  * @note   Clears SLEEPONEXIT bit of SCR register. When this bit is set, the
  *         processor re-enters Sleep mode when an interruption handling is over.
  * @retval None.
  */
void HAL_PWR_DisableSleepOnExit(void)
{
  /* Clear SLEEPONEXIT bit of Cortex-M33 System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
}

/**
  * @brief  Enable CORTEX SEV-ON-PEND feature.
  * @note   Sets SEVONPEND bit of SCR register. When this bit is set, any
  *         pending event / interrupt even if it's disabled or has insufficient
  *         priority to cause exception entry wakes up the Cortex-M33.
  * @retval None.
  */
void HAL_PWR_EnableSEVOnPend(void)
{
  /* Set SEVONPEND bit of Cortex-M33 System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
}

/**
  * @brief  Disable CORTEX SEVONPEND feature.
  * @note   Resets SEVONPEND bit of SCR register. When this bit is reset, only enabled
  *         pending event / interrupt to cause exception entry wakes up the Cortex-M33.
  * @retval None.
  */
void HAL_PWR_DisableSEVOnPend(void)
{
  /* Clear SEVONPEND bit of Cortex-M33 System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
}

/**
  * @brief  This function handles the PWR PVD interrupt request.
  * @note   This API should be called under the PVD_AVD_IRQHandler().
  * @retval None.
  */
void HAL_PWR_PVD_IRQHandler(void)
{
  uint32_t  rising_flag;
  uint32_t  falling_flag;

  /* Get pending flags */
  rising_flag  = READ_REG(EXTI->RPR1);
  falling_flag = READ_REG(EXTI->FPR1);

  /* Check PWR EXTI flags for PVD */
  if (((rising_flag | falling_flag) & PWR_EXTI_LINE_PVD) != 0U)
  {
    /* PWR PVD interrupt user callback */
    HAL_PWR_PVDCallback();

    /* Clear PVD EXTI pending bit */
    WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_PVD);
    WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_PVD);
  }
}

/**
  * @brief  PWR PVD interrupt callback.
  * @retval None.
  */
__weak void HAL_PWR_PVDCallback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWR_PVDCallback can be implemented in the user file
  */
}
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group3 Attributes Management Functions
  *  @brief    Attributes management functions
  *
@verbatim
 ===============================================================================
                       ##### PWR Attributes Functions #####
 ===============================================================================
    [..]
      When the TrustZone security is activated by the TZEN option bit in the
      FLASH_OPTR register, some PWR register fields can be secured against
      non-secure access.
      The PWR TrustZone security allows the following features to be secured
      through the PWR_SECCFGR register :

      (++) Low-power mode.
      (++) Wake-up (WKUP) pins.
      (++) Voltage detection and monitoring.
      (++) VBAT mode.
      (++) I/Os pull-up/pull-down configuration.

      Other PWR configuration bits are secure when :
      (++) The system clock selection is secure in RCC: the voltage scaling
           (VOS) configuration and the regulator booster (BOOSTEN) are secure.
      (++) A GPIO is configured as secure: its corresponding bit for pull-up /
           pull-down configuration in Standby mode is secure.
      (++) The UCPD1 is secure in the GTZC: the PWR_UCPDR register is secure.

      A non-secure access to a secure-protected register bit is denied :
      (++) The secured bits are not written (WI) with a non-secure write access.
      (++) The secured bits are read as 0 (RAZ) with a non-secure read access.

    [..]
      When the TrustZone security is disabled (TZEN = 0), PWR_SECCFGR is RAZ/WI
      and all other registers are non-secure.

    [..]
      By default, after a reset, all PWR registers can be read or written with
      both privileged and unprivileged accesses, except PWR_PRIVCFGR that can be
      written with privileged access only. PWR_PRIVCFGR can be read by secure
      and non secure, privileged and unprivileged accesses.
      The SPRIV bit in PWR_PRIVCFGR can be written with secure privileged access
      only. This bit configures the privileged access of all PWR secure
      functions (defined by PWR_SECCFGR, GTZC, RCC or GPIO).
      When the SPRIV bit is set in PWR_PRIVCFGR:
      (++) The PWR secure bits can be written only with privileged access,
      including PWR_SECCFGR.
      (++) The PWR secure bits can be read only with privileged access except
           PWR_SECCFGR and PWR_PRIVCFGR that can be read by privileged or
           unprivileged access.
      (++) An unprivileged access to a privileged PWR bit or register is
           discarded : the bits are read as zero and the write to these bits is
           ignored (RAZ/WI).
      The NSPRIV bit of PWR_PRIVCFGR can be written with privileged access only,
      secure or non-secure. This bit configures the privileged access of all PWR
      securable functions that are configured as non-secure (defined by
      PWR_SECCFGR, GTZC, RCC or GPIO).
      When the NSPRIV bit is set in PWR_PRIVCFGR :
      (++) The PWR securable bits that are configured as non-secure, can be
           written only with privileged access.
      (++) The PWR securable bits that are configured as non-secure, can be read
           only with privileged access except PWR_PRIVCFGR that can be read by
           privileged or unprivileged accesses.
      (++) The VOSRDY and BOOSTRDY bits in PWR_VOSR, PWR_SR, PWR_SVMSR, PWR_BDSR
           and PWR_WUSR, can be read with privileged or unprivileged accesses.
      (++) An unprivileged access to a privileged PWR bit or register is
           discarded : the bits are read as zero and the write to these bits is
           ignored (RAZ/WI).

@endverbatim
  * @{
  */

/**
  * @brief  Configure the PWR item attributes.
  * @note   Available attributes are security and privilege protection.
  * @note   Security attribute can only be set only by secure access.
  * @note   Privilege attribute for secure items can be managed only by a secure
  *         privileged access.
  * @note   Privilege attribute for nsecure items can be managed  by a secure
  *         privileged access or by a nsecure privileged access.
  * @param  Item       : Specifies the item(s) to set attributes on.
  *                      This parameter can be a combination of @ref PWR_Items.
  * @param  Attributes : Specifies the available attribute(s).
  *                      This parameter can be one of @ref PWR_Attributes.
  * @retval None.
  */
void HAL_PWR_ConfigAttributes(uint32_t Item, uint32_t Attributes)
{
  /* Check the parameters */
  assert_param(IS_PWR_ITEMS_ATTRIBUTES(Item));
  assert_param(IS_PWR_ATTRIBUTES(Attributes));

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  /* Secure item management (TZEN = 1) */
  if ((Attributes & PWR_ITEM_ATTR_SEC_PRIV_MASK) == PWR_ITEM_ATTR_SEC_PRIV_MASK)
  {
    /* Privilege item management */
    if ((Attributes & PWR_SEC_PRIV) == PWR_SEC_PRIV)
    {
      SET_BIT(PWR->SECCFGR, Item);
      SET_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_SPRIV);
    }
    else
    {
      SET_BIT(PWR->SECCFGR, Item);
      CLEAR_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_SPRIV);
    }
  }
  /* NSecure item management */
  else
  {
    /* Privilege item management */
    if ((Attributes & PWR_NSEC_PRIV) == PWR_NSEC_PRIV)
    {
      CLEAR_BIT(PWR->SECCFGR, Item);
      SET_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV);
    }
    else
    {
      CLEAR_BIT(PWR->SECCFGR, Item);
      CLEAR_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV);
    }
  }
#else
  /* NSecure item management (TZEN = 0) */
  if ((Attributes & PWR_ITEM_ATTR_NSEC_PRIV_MASK) == PWR_ITEM_ATTR_NSEC_PRIV_MASK)
  {
    /* Privilege item management */
    if ((Attributes & PWR_NSEC_PRIV) == PWR_NSEC_PRIV)
    {
      SET_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV);
    }
    else
    {
      CLEAR_BIT(PWR->PRIVCFGR, PWR_PRIVCFGR_NSPRIV);
    }
  }
#endif /* __ARM_FEATURE_CMSE */
}

/**
  * @brief  Get attribute(s) of a PWR item.
  * @param  Item        : Specifies the item(s) to get attributes of.
  *                       This parameter can be one of @ref PWR_Items.
  * @param  pAttributes : Pointer to return attribute(s).
  *                       Returned value could be one of @ref PWR_Attributes.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWR_GetConfigAttributes(uint32_t Item, uint32_t *pAttributes)
{
  uint32_t attributes;

  /* Check attribute pointer */
  if (pAttributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameter */
  assert_param(IS_PWR_ITEMS_ATTRIBUTES(Item));

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  /* Check item security */
  if ((PWR->SECCFGR & Item) == Item)
  {
    /* Get Secure privileges attribute */
    attributes = ((PWR->PRIVCFGR & PWR_PRIVCFGR_SPRIV) == 0U) ? PWR_SEC_NPRIV : PWR_SEC_PRIV;
  }
  else
  {
    /* Get Non-Secure privileges attribute */
    attributes = ((PWR->PRIVCFGR & PWR_PRIVCFGR_NSPRIV) == 0U) ? PWR_NSEC_NPRIV : PWR_NSEC_PRIV;
  }
#else
  /* Get Non-Secure privileges attribute */
  attributes = ((PWR->PRIVCFGR & PWR_PRIVCFGR_NSPRIV) == 0U) ? PWR_NSEC_NPRIV : PWR_NSEC_PRIV;
#endif /* __ARM_FEATURE_CMSE */

  /* return value */
  *pAttributes = attributes;

  return HAL_OK;
}
/**
  * @}
  */

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
