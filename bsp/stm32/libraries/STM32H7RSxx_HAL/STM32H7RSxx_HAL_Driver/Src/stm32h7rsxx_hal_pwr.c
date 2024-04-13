/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_pwr.c
  * @author  MCD Application Team
  * @brief   PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Initialization/De-Initialization Functions.
  *           + Peripheral Control Functions.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

   (#) Several low-power modes are available to save power when the CPU does not need to
       execute code :
      (+) Sleep   (CPU clock stopped and still in RUN mode)
      (+) Stop    (System clock stopped)
      (+) Standby (System powered down)

  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]

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

   (#) Call HAL_PWR_EnterSTOPMode() function to enter the whole system to Stop
       mode. Wake-up from Stop mode could be following to an event or an
       interrupt according to low power mode intrinsic request called (__WFI()
       or __WFE()).

   (#) Call HAL_PWR_EnterSTANDBYMode() function to enter the whole system in
       Standby mode. Wake-up from Standby mode can be following only by an
       interrupt.

   (#) Call HAL_PWR_EnableSleepOnExit() and HAL_PWR_DisableSleepOnExit() APIs to
       enable and disable the Cortex-M7 re-entry in Sleep mode after an
       interruption handling is over.

   (#) Call HAL_PWR_EnableSEVOnPend() and HAL_PWR_DisableSEVOnPend() functions
       to configure the Cortex-M7 to wake-up after any pending event / interrupt
       even if it's disabled or has insufficient priority to cause exception
       entry.

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
#include "stm32h7rsxx_hal.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
  * @{
  */

/** @defgroup PWR PWR
  * @brief PWR HAL module driver
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup PWR_Private_Defines PWR Private Defines
  * @{
  */

/** @defgroup PWR_PVD_Mode_Mask PWR PVD Mode Mask
  * @{
  */
#define PVD_MODE_IT                     (0x00010000U)
#define PVD_MODE_EVT                    (0x00020000U)
#define PVD_RISING_EDGE                 (0x00000001U)
#define PVD_FALLING_EDGE                (0x00000002U)
#define PVD_RISING_FALLING_EDGE         (0x00000003U)
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
      This section provides functions allowing to deinitialize power peripheral.

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
  SET_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Disable access to the backup domain (RCC Backup domain control
  *         register RCC_BDCR, RTC registers, TAMP registers, backup registers
  *         and backup SRAM).
  * @retval None.
  */
void HAL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_DBP);
}
/**
  * @}
  */


/** @defgroup PWR_Exported_Functions_Group2 Peripheral Control Functions
  *  @brief   Power Control functions
  *
@verbatim
 ===============================================================================
                 ##### Peripheral Control Functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to control power peripheral.

    *** PVD configuration ***
    =========================
    [..]
      (+) The PVD is used to monitor the VDD power supply by comparing it to a
          threshold selected by the PVD Level (PLS[2:0] bits in the PWR_CR1
          register).

      (+) A PVDO flag is available to indicate if VDD is higher or lower
          than the PVD threshold. This event is internally connected to the EXTI
          line 16 to generate an interrupt if enabled.
          It is configurable through __HAL_PWR_PVD_EXTI_ENABLE_IT() macro.

      (+) The PVD is stopped in STANDBY mode.

    *** Wake-up pin configuration ***
    =================================
    [..]
      (+) Wake-up pin is used to wake up the system from STANDBY mode.
          The pin pull is configurable through the WKUPEPR register to be in
          No-pull, Pull-up and Pull-down.
          The pin polarity is configurable through the WKUPEPR register to be
          active on rising or falling edges.

      (+) There are up to four Wake-up pin in the STM32H7RS devices family.

    *** Low Power modes configuration ***
    =====================================
    [..]
     The device present 3 principles low-power modes :
      (+) SLEEP mode   : Cortex-M7 is stopped and all PWR domains are remaining
                         active (Powered and Clocked).

      (+) STOP mode    : Cortex-M7 is stopped, clocks are stopped and the
                         regulator is running. The Main regulator or the LP
                         regulator could be selected.

      (+) STANDBY mode : All PWR domains enter DSTANDBY mode and the VCORE
                         supply regulator is powered off.

   *** SLEEP mode ***
   ==================
    [..]
      (+) Entry:
        The SLEEP mode is entered by using the HAL_PWR_EnterSLEEPMode(Regulator,
        SLEEPEntry) function.

          (++) PWR_SLEEPENTRY_WFI             : Enter SLEEP mode with WFI instruction.
          (++) PWR_SLEEPENTRY_WFE             : Enter SLEEP mode with WFE instruction and
                                                clear of pending events before.
          (++) PWR_SLEEPENTRY_WFE_NO_EVT_CLEAR: Enter SLEEP mode with WFE instruction and
                                                no clear of pending event before.
      -@@- The Regulator parameter is not used for the STM32H7RS family
              and is kept as parameter just to maintain compatibility with the
              lower power families. (STM32L).

      (+) Exit:
        Any peripheral interrupt acknowledged by the nested vectored interrupt
        controller (NVIC) can wake up the device from SLEEP mode.

   *** STOP mode ***
   =================
    [..]
      In system STOP mode, the CPU clock is stopped. All CPU subsystem peripheral
      clocks are stopped too.
      The voltage regulator can be configured either in normal or low-power mode.
      To minimize the consumption in STOP mode, FLASH can be powered off before
      entering the STOP mode using the HAL_PWREx_EnableFlashPowerDown() function.
      It can be switched on again by software after exiting the STOP mode using
      the HAL_PWREx_DisableFlashPowerDown() function.
      (+) Entry:
         The STOP mode is entered using the HAL_PWR_EnterSTOPMode(Regulator,
         STOPEntry) function with:
         (++) Regulator:
          (+++) PWR_MAINREGULATOR_ON: Main regulator ON.
                This parameter is not used for the STM32H7RS family and is kept as parameter
                just to maintain compatibility with the lower power families.
         (++) STOPEntry:
          (+++) PWR_STOPENTRY_WFI             : Enter STOP mode with WFI instruction.
          (+++) PWR_STOPENTRY_WFE             : Enter STOP mode with WFE instruction and
                                                clear of pending events before.
          (+++) PWR_STOPENTRY_WFE_NO_EVT_CLEAR: Enter STOP mode with WFE instruction and
                                                no clear of pending event before.
      (+) Exit:
         Any EXTI Line (Internal or External) configured in Interrupt/Event mode.

   *** STANDBY mode ***
   ====================
    [..]
    (+)
      The system STANDBY mode allows to achieve the lowest power consumption.
      It is based on the Cortex-M7 deep SLEEP mode, with the voltage regulator
      disabled. The system is consequently powered off. The PLL, the HSI
      oscillator and the HSE oscillator are also switched off. SRAM and register
      contents are lost except for the RTC registers, RTC backup registers,
      backup SRAM and standby circuitry.

    [..]
      The voltage regulator is OFF.

      (++) Entry:
        (+++) The STANDBY mode is entered using the HAL_PWR_EnterSTANDBYMode()
              function.

      (++) Exit:
        (+++) WKUP pin rising or falling edge, RTC alarm (Alarm A and Alarm B),
              RTC wakeup, tamper event, time stamp event, external reset in NRST
              pin, IWDG reset.

   *** Auto-wakeup (AWU) from low-power mode ***
   =============================================
    [..]
     (+) The MCU can be woken up from low-power mode by an RTC Alarm event, an
         RTC Wakeup event, a tamper event or a time-stamp event, without
         depending on an external interrupt (Auto-wakeup mode).

     (+) RTC auto-wakeup (AWU) from the STOP and STANDBY modes

       (++) To wake up from the STOP mode with an RTC alarm event, it is
            necessary to configure the RTC to generate the RTC alarm using the
            HAL_RTC_SetAlarm_IT() function.

       (++) To wake up from the STOP mode with an RTC Tamper or time stamp event,
            it is necessary to configure the RTC to detect the tamper or time
            stamp event using the HAL_RTCEx_SetTimeStamp_IT() or
            HAL_RTCEx_SetTamper_IT() functions.

       (++) To wake up from the STOP mode with an RTC WakeUp event, it is
            necessary to configure the RTC to generate the RTC WakeUp event
            using the HAL_RTCEx_SetWakeUpTimer_IT() function.

@endverbatim
  * @{
  */

/**
  * @brief  Configure the voltage threshold detected by the Programmed Voltage
  *         Detector (PVD).
  * @param  sConfigPVD : Pointer to a PWR_PVDTypeDef structure that contains the
  *                      PVD configuration information (PVDLevel and EventMode).
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each
  *         detection level.
  * @note   As PVD and AVD share the same EXTI line, the EXTI operating mode to
  *         configure will replace a possible previous configuration done through
  *         HAL_PWREx_ConfigAVD.
  * @retval None.
  */
void HAL_PWR_ConfigPVD(const PWR_PVDTypeDef *sConfigPVD)
{
  /* Check the PVD configuration parameter */
  if (sConfigPVD == NULL)
  {
    return;
  }

  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(sConfigPVD->PVDLevel));
  assert_param(IS_PWR_PVD_MODE(sConfigPVD->Mode));

  /* Set PLS[7:5] bits according to PVDLevel value */
  MODIFY_REG(PWR->CR1, PWR_CR1_PLS, sConfigPVD->PVDLevel);

  /* Clear any previous config. Keep it clear if no event or IT mode is selected */
  __HAL_PWR_PVD_EXTI_DISABLE_EVENT();
  __HAL_PWR_PVD_EXTI_DISABLE_IT();
  __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();
  __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE();

  /* Configure the PVD in interrupt mode */
  if ((sConfigPVD->Mode & PVD_MODE_IT) == PVD_MODE_IT)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_IT();
  }

  /* Configure the PVD in event mode */
  if ((sConfigPVD->Mode & PVD_MODE_EVT) == PVD_MODE_EVT)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_EVENT();
  }

  /* Rising edge configuration */
  if ((sConfigPVD->Mode & PVD_RISING_EDGE) == PVD_RISING_EDGE)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();
  }

  /* Falling edge configuration */
  if ((sConfigPVD->Mode & PVD_FALLING_EDGE) == PVD_FALLING_EDGE)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();
  }
}

/**
  * @brief  Enable the programmable voltage detector (PVD).
  * @retval None.
  */
void HAL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_PVDE);
}

/**
  * @brief  Disable the programmable voltage detector (PVD).
  * @retval None.
  */
void HAL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_PVDE);
}

/**
  * @brief  Enable the WakeUp PINx functionality.
  * @param  WakeUpPinPolarity : Specifies which Wake-Up pin to enable.
  *          This parameter can be one of the following legacy values, which
  *          sets the default (rising edge):
  *            @arg PWR_WAKEUP_PIN1,
  *                 PWR_WAKEUP_PIN2,
  *                 PWR_WAKEUP_PIN3,
  *                 PWR_WAKEUP_PIN4.
  *          or one of the following values where the user can explicitly states
  *          the enabled pin and the chosen polarity:
  *            @arg PWR_WAKEUP_PIN1_HIGH, PWR_WAKEUP_PIN1_LOW,
  *                 PWR_WAKEUP_PIN2_HIGH, PWR_WAKEUP_PIN2_LOW,
  *                 PWR_WAKEUP_PIN3_HIGH, PWR_WAKEUP_PIN3_LOW,
  *                 PWR_WAKEUP_PIN4_HIGH, PWR_WAKEUP_PIN4_LOW.
  * @note   PWR_WAKEUP_PINx and PWR_WAKEUP_PINx_HIGH are equivalent.
  * @retval None.
  */
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPinPolarity)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPinPolarity));

  /*
     Enable and Specify the Wake-Up pin polarity and the pull configuration
     for the event detection (rising or falling edge).
  */
  MODIFY_REG(PWR->WKUPEPR, PWR_WKUPEPR_WKUPEN | PWR_WKUPEPR_WKUPP, WakeUpPinPolarity);
}

/**
  * @brief  Disable the WakeUp PINx functionality.
  * @param  WakeUpPinx : Specifies the Power Wake-Up pin to disable.
  *          This parameter can be one of the following values:
  *            @arg PWR_WAKEUP_PIN1,
  *                 PWR_WAKEUP_PIN2,
  *                 PWR_WAKEUP_PIN3,
  *                 PWR_WAKEUP_PIN4,
  *                 PWR_WAKEUP_PIN1_HIGH, PWR_WAKEUP_PIN1_LOW,
  *                 PWR_WAKEUP_PIN2_HIGH, PWR_WAKEUP_PIN2_LOW,
  *                 PWR_WAKEUP_PIN3_HIGH, PWR_WAKEUP_PIN3_LOW,
  *                 PWR_WAKEUP_PIN4_HIGH, PWR_WAKEUP_PIN4_LOW.
  * @retval None.
  */
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPinx));

  /* Disable the wake up pin selected */
  CLEAR_BIT(PWR->WKUPEPR, (PWR_WKUPEPR_WKUPEN & WakeUpPinx));
}

/**
  * @brief  Enter the current core in SLEEP mode (CSLEEP).
  * @param  Regulator : NA in this family project
  *         Specifies the regulator state in SLEEP mode.
  * @note   This parameter is not used for the STM32H7RS family and is kept as
  *         parameter just to maintain compatibility with the lower power
  *         families.
  * @param  SLEEPEntry : Specifies if SLEEP mode is entered with WFI or WFE
  *                      intrinsic instruction.
  *          This parameter can be one of the following values:
  *            @arg PWR_SLEEPENTRY_WFI              : Enter SLEEP mode with WFI instruction.
  *            @arg PWR_SLEEPENTRY_WFE              : Enter SLEEP mode with WFE instruction and
  *                                                   clear of pending events before.
  *            @arg PWR_SLEEPENTRY_WFE_NO_EVT_CLEAR : Enter SLEEP mode with WFE instruction and
  *                                                   no clear of pending event before.
  * @retval None.
  */
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Regulator);

  /* Check the parameters */
  assert_param(IS_PWR_SLEEP_ENTRY(SLEEPEntry));

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);

  /* Select Sleep mode entry */
  if (SLEEPEntry == PWR_SLEEPENTRY_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    if (SLEEPEntry != PWR_SLEEPENTRY_WFE_NO_EVT_CLEAR)
    {
      /* Clear all pending event */
      __SEV();
      __WFE();
    }

    /* Request Wait For Event */
    __WFE();
  }
}

/**
  * @brief  Enter the whole system to Stop mode.
  * @note   This API will enter the system in STOP mode
  * @param  Regulator : This parameter is not used for this product family.
            and is kept as parameter just to maintain compatibility with the
            lower power families.
  * @param  STOPEntry : Specifies if STOP mode in entered with WFI or WFE
  *                     intrinsic instruction.
  *          This parameter can be one of the following values:
  *            @arg PWR_STOPENTRY_WFI              : Enter STOP mode with WFI instruction.
  *            @arg PWR_STOPENTRY_WFE              : Enter STOP mode with WFE instruction and
  *                                                  clear of pending events before.
  *            @arg PWR_STOPENTRY_WFE_NO_EVT_CLEAR : Enter STOP mode with WFE instruction and
  *                                                  no clear of pending event before.
  * @note   In System STOP mode, all I/O pins keep the same state as in Run mode.
  * @note   When exiting System STOP mode by issuing an interrupt or a wakeup
  *         event, the HSI RC oscillator is selected as default system wakeup
  *         clock.
  * @note   In System STOP mode, when the voltage regulator operates in low
  *         power mode, an additional startup delay is incurred when the system
  *         is waking up. By keeping the internal regulator ON during STOP mode,
  *         the consumption is higher although the startup time is reduced.
  * @retval None.
  */
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry)
{

  /* Prevent unused argument(s) compilation warning */
  UNUSED(Regulator);

  /* Check the parameters */
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));

  /* Select Stop mode when device enters Deepsleep */
  CLEAR_BIT(PWR->CSR3, PWR_CSR3_PDDS);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);

  /* Ensure that all instructions are done before entering STOP mode */
  __DSB();
  __ISB();

  /* Select Stop mode entry */
  if (STOPEntry == PWR_STOPENTRY_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    if (STOPEntry != PWR_STOPENTRY_WFE_NO_EVT_CLEAR)
    {
      /* Clear all pending event */
      __SEV();
      __WFE();
    }
    /* Request Wait For Event */
    __WFE();
  }

  /* Clear SLEEPDEEP bit of Cortex-M7 in the System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);
}

/**
  * @brief  Enter the whole system to Standby mode.
  * @note   The Standby mode allows achieving the lowest power consumption.
  * @note   When the system enters in Standby mode, the voltage regulator is disabled.
  *         The complete VCORE domain is consequently powered off.
  *         The PLLs, HSI oscillator, CSI oscillator, HSI48 and the HSE oscillator are
  *         also switched off.
  *         SRAM and register contents are lost except for backup domain registers
  *         (RTC registers, RTC backup register and backup RAM), and Standby circuitry.
  * @note   When the System exit STANDBY mode by issuing an interrupt or a
  *         wakeup event, the HSI RC oscillator is selected as system clock.
  * @retval None.
  */
void HAL_PWR_EnterSTANDBYMode(void)
{
  /* Select Standby when device enters Deepsleep */
  SET_BIT(PWR->CSR3, PWR_CSR3_PDDS);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);

  /* Ensure that all instructions are done before entering STANDBY mode */
  __DSB();
  __ISB();

  /* Request Wait For Interrupt */
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
  /* Set SLEEPONEXIT bit of Cortex-M7 System Control Register */
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
  /* Clear SLEEPONEXIT bit of Cortex-M7 System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
}

/**
  * @brief  Enable CORTEX SEV-ON-PEND feature.
  * @note   Sets SEVONPEND bit of SCR register. When this bit is set, any
  *         pending event / interrupt even if it's disabled or has insufficient
  *         priority to cause exception entry wakes up the Cortex-M7.
  * @retval None.
  */
void HAL_PWR_EnableSEVOnPend(void)
{
  /* Set SEVONPEND bit of Cortex-M7 System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
}

/**
  * @brief  Disable CORTEX SEVONPEND feature.
  * @note   Resets SEVONPEND bit of SCR register. When this bit is reset, only
  *         enabled pending causes exception entry wakes up the Cortex-M7.
  * @retval None.
  */
void HAL_PWR_DisableSEVOnPend(void)
{
  /* Clear SEVONPEND bit of Cortex-M7 System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
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

