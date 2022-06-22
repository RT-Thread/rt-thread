/**
  ******************************************************************************
  * @file    stm32wlxx_hal_pwr_ex.c
  * @author  MCD Application Team
  * @brief   Extended PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Extended Initialization and de-initialization functions
  *           + Extended Peripheral Control functions
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32wlxx_hal.h"

/** @addtogroup STM32WLxx_HAL_Driver
  * @{
  */

/** @addtogroup PWREx
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup PWREx_Private_Constants PWR Extended Private Constants
  * @{
  */
#define PWR_PORTC_AVAILABLE_PINS   (PWR_GPIO_BIT_15 | PWR_GPIO_BIT_14 | PWR_GPIO_BIT_13 | PWR_GPIO_BIT_6 | PWR_GPIO_BIT_5 | PWR_GPIO_BIT_4 | PWR_GPIO_BIT_3 | PWR_GPIO_BIT_2 | PWR_GPIO_BIT_1 | PWR_GPIO_BIT_0)
#define PWR_PORTH_AVAILABLE_PINS   (PWR_GPIO_BIT_3)

/** @defgroup PWREx_TimeOut_Value PWR Extended Flag Setting Time Out Value
  * @{
  */
#define PWR_FLAG_SETTING_DELAY_US                      50UL   /*!< Time out value for REGLPF and VOSF flags setting */
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
/** @addtogroup PWREx_Exported_Functions PWR Extended Exported Functions
  * @{
  */

/** @addtogroup PWREx_Exported_Functions_Group1 Extended Peripheral Control functions
  *  @brief   Extended Peripheral Control functions
  *
@verbatim
 ===============================================================================
              ##### Extended Peripheral Initialization and de-initialization functions #####
 ===============================================================================
    [..]

@endverbatim
  * @{
  */


/**
  * @brief Return Voltage Scaling Range.
  * @retval VOS bit field (PWR_REGULATOR_VOLTAGE_SCALE1 or PWPWR_REGULATOR_VOLTAGE_SCALE2)
  */
uint32_t HAL_PWREx_GetVoltageRange(void)
{
  return (PWR->CR1 & PWR_CR1_VOS);
}

/**
  * @brief Configure the main internal regulator output voltage.
  * @param VoltageScaling specifies the regulator output voltage to achieve
  *         a trade-off between performance and power consumption.
  *          This parameter can be one of the following values:
  *            @arg @ref PWR_REGULATOR_VOLTAGE_SCALE1 Regulator voltage output range 1 mode,
  *                                                typical output voltage at 1.2 V,
  *                                                system frequency up to 48 MHz.
  *            @arg @ref PWR_REGULATOR_VOLTAGE_SCALE2 Regulator voltage output range 2 mode,
  *                                                typical output voltage at 1.0 V,
  *                                                system frequency up to 16 MHz.
  * @note  When moving from Range 1 to Range 2, the system frequency must be decreased to
  *        a value below 16 MHz before calling HAL_PWREx_ControlVoltageScaling() API.
  *        When moving from Range 2 to Range 1, the system frequency can be increased to
  *        a value up to 48 MHz after calling HAL_PWREx_ControlVoltageScaling() API.
  * @note  When moving from Range 2 to Range 1, the API waits for VOSF flag to be
  *        cleared before returning the status. If the flag is not cleared within
  *        50 microseconds, HAL_TIMEOUT status is reported.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling)
{
  uint32_t wait_loop_index;

  assert_param(IS_PWR_VOLTAGE_SCALING_RANGE(VoltageScaling));

  /* If Set Range 1 */
  if (VoltageScaling == PWR_REGULATOR_VOLTAGE_SCALE1)
  {
    if (READ_BIT(PWR->CR1, PWR_CR1_VOS) != PWR_REGULATOR_VOLTAGE_SCALE1)
    {
      /* Set Range 1 */
      MODIFY_REG(PWR->CR1, PWR_CR1_VOS, PWR_REGULATOR_VOLTAGE_SCALE1);

      /* Wait until VOSF is cleared */
      wait_loop_index = ((PWR_FLAG_SETTING_DELAY_US * SystemCoreClock) / 1000000UL);
      while ((HAL_IS_BIT_SET(PWR->SR2, PWR_SR2_VOSF)) && (wait_loop_index != 0U))
      {
        wait_loop_index--;
      }
      if (HAL_IS_BIT_SET(PWR->SR2, PWR_SR2_VOSF))
      {
        return HAL_TIMEOUT;
      }
    }
  }
  else
  {
    if (READ_BIT(PWR->CR1, PWR_CR1_VOS) != PWR_REGULATOR_VOLTAGE_SCALE2)
    {
      /* Set Range 2 */
      MODIFY_REG(PWR->CR1, PWR_CR1_VOS, PWR_REGULATOR_VOLTAGE_SCALE2);
      /* No need to wait for VOSF to be cleared for this transition */
    }
  }

  return HAL_OK;
}

/****************************************************************************/

/**
  * @brief Enable battery charging.
  *        When VDD is present, charge the external battery on VBAT through an internal resistor.
  * @param ResistorSelection specifies the resistor impedance.
  *          This parameter can be one of the following values:
  *            @arg @ref PWR_BATTERY_CHARGING_RESISTOR_5     5 kOhms resistor
  *            @arg @ref PWR_BATTERY_CHARGING_RESISTOR_1_5 1.5 kOhms resistor
  * @retval None
  */
void HAL_PWREx_EnableBatteryCharging(uint32_t ResistorSelection)
{
  assert_param(IS_PWR_BATTERY_RESISTOR_SELECT(ResistorSelection));

  /* Specify resistor selection */
  MODIFY_REG(PWR->CR4, PWR_CR4_VBRS, ResistorSelection);

  /* Enable battery charging */
  SET_BIT(PWR->CR4, PWR_CR4_VBE);
}

/**
  * @brief Disable battery charging.
  * @retval None
  */
void HAL_PWREx_DisableBatteryCharging(void)
{
  CLEAR_BIT(PWR->CR4, PWR_CR4_VBE);
}

/****************************************************************************/

/**
  * @brief Enable Internal Wake-up Line.
  * @retval None
  */
void HAL_PWREx_EnableInternalWakeUpLine(void)
{
#ifdef CORE_CM0PLUS
  SET_BIT(PWR->C2CR3, PWR_C2CR3_EIWUL);
#else
  SET_BIT(PWR->CR3, PWR_CR3_EIWUL);
#endif
}

/**
  * @brief Disable Internal Wake-up Line.
  * @retval None
  */
void HAL_PWREx_DisableInternalWakeUpLine(void)
{
#ifdef CORE_CM0PLUS
  CLEAR_BIT(PWR->C2CR3, PWR_C2CR3_EIWUL);
#else
  CLEAR_BIT(PWR->CR3, PWR_CR3_EIWUL);
#endif
}

/**
  * @brief  Set radio busy trigger polarity.
  * @param  RadioBusyPolarity This parameter can be one of the following values:
  *         @arg @ref PWR_RADIO_BUSY_POLARITY_RISING
  *         @arg @ref PWR_RADIO_BUSY_POLARITY_FALLING
  * @retval HAL Status
  */
void HAL_PWREx_SetRadioBusyPolarity(uint32_t RadioBusyPolarity)
{
  /* Check the parameters */
  assert_param(IS_RADIO_BUSY_POLARITY(RadioBusyPolarity));

  LL_PWR_SetRadioBusyPolarity(RadioBusyPolarity);
}

/**
  * @brief  Set radio busy trigger action: wake-up from low-power mode Standby,
  *         interruption.
  * @note   Signal polarity can be configured using function
  *         @ref HAL_PWREx_SetRadioBusyPolarity().
  * @param  RadioBusyTrigger This parameter can be one of the following values:
  *         @arg @ref PWR_RADIO_BUSY_TRIGGER_NONE
  *         @arg @ref PWR_RADIO_BUSY_TRIGGER_WU_IT
  * @retval None
  */
void HAL_PWREx_SetRadioBusyTrigger(uint32_t RadioBusyTrigger)
{
  /* Check the parameters */
  assert_param(IS_PWR_RADIO_BUSY_TRIGGER(RadioBusyTrigger));

#ifdef CORE_CM0PLUS
  LL_C2_PWR_SetRadioBusyTrigger(RadioBusyTrigger);
#else
  LL_PWR_SetRadioBusyTrigger(RadioBusyTrigger);
#endif
}

/**
  * @brief  Set radio IRQ trigger action: wake-up from low-power mode Standby,
  *         interruption.
  * @param  RadioIRQTrigger This parameter can be one of the following values:
  *         @arg @ref PWR_RADIO_IRQ_TRIGGER_NONE
  *         @arg @ref PWR_RADIO_IRQ_TRIGGER_WU_IT
  * @retval None
  */
void HAL_PWREx_SetRadioIRQTrigger(uint32_t RadioIRQTrigger)
{
  /* Check the parameters */
  assert_param(IS_RADIO_IRQ_TRIGGER(RadioIRQTrigger));

#ifdef CORE_CM0PLUS
  LL_C2_PWR_SetRadioIRQTrigger(RadioIRQTrigger);
#else
  LL_PWR_SetRadioIRQTrigger(RadioIRQTrigger);
#endif
}

#if defined(DUAL_CORE)
/**
  * @brief Enable CPU2 on-Hold interrupt.
  * @retval None
  */
void HAL_PWREx_EnableHOLDC2IT(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_EC2H);
}

/**
  * @brief Disable CPU2 on-Hold interrupt.
  * @retval None
  */
void HAL_PWREx_DisableHOLDC2IT(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_EC2H);
}
#endif

/****************************************************************************/

/**
  * @brief Enable GPIO pull-up state in Standby and Shutdown modes.
  * @note  Set the relevant PUy bits of PWR_PUCRx register to configure the I/O in
  *        pull-up state in Standby and Shutdown modes.
  * @note  This state is effective in Standby and Shutdown modes only if APC bit
  *        is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note  The configuration is lost when exiting the Shutdown mode due to the
  *        power-on reset, maintained when exiting the Standby mode.
  * @note  To avoid any conflict at Standby and Shutdown modes exits, the corresponding
  *        PDy bit of PWR_PDCRx register is cleared unless it is reserved.
  * @note  Even if a PUy bit to set is reserved, the other PUy bits entered as input
  *        parameter at the same time are set.
  * @param GPIO Specify the IO port. This parameter can be PWR_GPIO_A, ..., PWR_GPIO_H
  *         to select the GPIO peripheral.
  * @param GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for PORTH where less
  *         I/O pins are available) or the logical OR of several of them to set
  *         several bits for a given port in a single API call.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_PWR_GPIO(GPIO));
  assert_param(IS_PWR_GPIO_BIT_NUMBER(GPIONumber));

  switch (GPIO)
  {
    case PWR_GPIO_A:
      SET_BIT(PWR->PUCRA, GPIONumber);
      CLEAR_BIT(PWR->PDCRA, GPIONumber);
      break;
    case PWR_GPIO_B:
      SET_BIT(PWR->PUCRB, GPIONumber);
      CLEAR_BIT(PWR->PDCRB, GPIONumber);
      break;
    case PWR_GPIO_C:
      SET_BIT(PWR->PUCRC, (GPIONumber & PWR_PORTC_AVAILABLE_PINS));
      CLEAR_BIT(PWR->PDCRC, (GPIONumber & PWR_PORTC_AVAILABLE_PINS));
      break;
    case PWR_GPIO_H:
      SET_BIT(PWR->PUCRH, (GPIONumber & PWR_PORTH_AVAILABLE_PINS));
      CLEAR_BIT(PWR->PDCRH, (GPIONumber & PWR_PORTH_AVAILABLE_PINS));
      break;
    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief Disable GPIO pull-up state in Standby mode and Shutdown modes.
  * @note  Reset the relevant PUy bits of PWR_PUCRx register used to configure the I/O
  *        in pull-up state in Standby and Shutdown modes.
  * @note  Even if a PUy bit to reset is reserved, the other PUy bits entered as input
  *        parameter at the same time are reset.
  * @param GPIO Specifies the IO port. This parameter can be PWR_GPIO_A, ..., PWR_GPIO_H
  *         to select the GPIO peripheral.
  * @param GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for PORTH where less
  *         I/O pins are available) or the logical OR of several of them to reset
  *         several bits for a given port in a single API call.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_PWR_GPIO(GPIO));
  assert_param(IS_PWR_GPIO_BIT_NUMBER(GPIONumber));

  switch (GPIO)
  {
    case PWR_GPIO_A:
      CLEAR_BIT(PWR->PUCRA, GPIONumber);
      break;
    case PWR_GPIO_B:
      CLEAR_BIT(PWR->PUCRB, GPIONumber);
      break;
    case PWR_GPIO_C:
      CLEAR_BIT(PWR->PUCRC, (GPIONumber & PWR_PORTC_AVAILABLE_PINS));
      break;
    case PWR_GPIO_H:
      CLEAR_BIT(PWR->PUCRH, (GPIONumber & PWR_PORTH_AVAILABLE_PINS));
      break;
    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief Enable GPIO pull-down state in Standby and Shutdown modes.
  * @note  Set the relevant PDy bits of PWR_PDCRx register to configure the I/O in
  *        pull-down state in Standby and Shutdown modes.
  * @note  This state is effective in Standby and Shutdown modes only if APC bit
  *        is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note  The configuration is lost when exiting the Shutdown mode due to the
  *        power-on reset, maintained when exiting the Standby mode.
  * @note  To avoid any conflict at Standby and Shutdown modes exits, the corresponding
  *        PUy bit of PWR_PUCRx register is cleared unless it is reserved.
  * @note  Even if a PDy bit to set is reserved, the other PDy bits entered as input
  *        parameter at the same time are set.
  * @param GPIO Specify the IO port. This parameter can be PWR_GPIO_A..PWR_GPIO_H
  *         to select the GPIO peripheral.
  * @param GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for PORTH where less
  *         I/O pins are available) or the logical OR of several of them to set
  *         several bits for a given port in a single API call.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_PWR_GPIO(GPIO));
  assert_param(IS_PWR_GPIO_BIT_NUMBER(GPIONumber));

  switch (GPIO)
  {
    case PWR_GPIO_A:
      SET_BIT(PWR->PDCRA, GPIONumber);
      CLEAR_BIT(PWR->PUCRA, GPIONumber);
      break;
    case PWR_GPIO_B:
      SET_BIT(PWR->PDCRB, GPIONumber);
      CLEAR_BIT(PWR->PUCRB, GPIONumber);
      break;
    case PWR_GPIO_C:
      SET_BIT(PWR->PDCRC, (GPIONumber & PWR_PORTC_AVAILABLE_PINS));
      CLEAR_BIT(PWR->PUCRC, (GPIONumber & PWR_PORTC_AVAILABLE_PINS));
      break;
    case PWR_GPIO_H:
      SET_BIT(PWR->PDCRH, (GPIONumber & PWR_PORTH_AVAILABLE_PINS));
      CLEAR_BIT(PWR->PUCRH, (GPIONumber & PWR_PORTH_AVAILABLE_PINS));
      break;
    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief Disable GPIO pull-down state in Standby and Shutdown modes.
  * @note  Reset the relevant PDy bits of PWR_PDCRx register used to configure the I/O
  *        in pull-down state in Standby and Shutdown modes.
  * @note  Even if a PDy bit to reset is reserved, the other PDy bits entered as input
  *        parameter at the same time are reset.
  * @param GPIO Specifies the IO port. This parameter can be PWR_GPIO_A..PWR_GPIO_H
  *         to select the GPIO peripheral.
  * @param GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for PORTH where less
  *         I/O pins are available) or the logical OR of several of them to reset
  *         several bits for a given port in a single API call.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_PWR_GPIO(GPIO));
  assert_param(IS_PWR_GPIO_BIT_NUMBER(GPIONumber));

  switch (GPIO)
  {
    case PWR_GPIO_A:
      CLEAR_BIT(PWR->PDCRA, GPIONumber);
      break;
    case PWR_GPIO_B:
      CLEAR_BIT(PWR->PDCRB, GPIONumber);
      break;
    case PWR_GPIO_C:
      CLEAR_BIT(PWR->PDCRC, (GPIONumber & PWR_PORTC_AVAILABLE_PINS));
      break;
    case PWR_GPIO_H:
      CLEAR_BIT(PWR->PDCRH, (GPIONumber & PWR_PORTH_AVAILABLE_PINS));
      break;
    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief Enable pull-up and pull-down configuration.
  * @note  When APC bit is set, the I/O pull-up and pull-down configurations defined in
  *        PWR_PUCRx and PWR_PDCRx registers are applied in Standby and Shutdown modes.
  * @note  Pull-up set by PUy bit of PWR_PUCRx register is not activated if the corresponding
  *        PDy bit of PWR_PDCRx register is also set (pull-down configuration priority is higher).
  *        HAL_PWREx_EnableGPIOPullUp() and HAL_PWREx_EnableGPIOPullDown() API's ensure there
  *        is no conflict when setting PUy or PDy bit.
  * @retval None
  */
void HAL_PWREx_EnablePullUpPullDownConfig(void)
{
#ifdef CORE_CM0PLUS
  SET_BIT(PWR->C2CR3, PWR_C2CR3_APC);
#else
  SET_BIT(PWR->CR3, PWR_CR3_APC);
#endif
}

/**
  * @brief Disable pull-up and pull-down configuration.
  * @note  When APC bit is cleared, the I/O pull-up and pull-down configurations defined in
  *        PWR_PUCRx and PWR_PDCRx registers are not applied in Standby and Shutdown modes.
  * @retval None
  */
void HAL_PWREx_DisablePullUpPullDownConfig(void)
{
#ifdef CORE_CM0PLUS
  CLEAR_BIT(PWR->C2CR3, PWR_C2CR3_APC);
#else
  CLEAR_BIT(PWR->CR3, PWR_CR3_APC);
#endif
}

/****************************************************************************/

#if defined(DUAL_CORE)
/**
  * @brief  Hold CPU and allocated peripherals after reset or wakeup from Stop or Standby.
  * @param  CPU Specifies the core to be held.
  *             This parameter can be one of the following values:
  *             @arg PWR_CORE_CPU2: Hold CPU2.
  * @note   Hold CPU2 with CPU1 as master by default.
  * @retval None
  */
void HAL_PWREx_HoldCore(uint32_t CPU)
{
  /* Check the parameters */
  assert_param(IS_PWR_CORE_HOLD_RELEASE(CPU));

  LL_PWR_DisableBootC2();
}

/**
  * @brief  Release CPU and allocated peripherals after reset or wakeup from Stop or Standby.
  * @param  CPU Specifies the core to be released.
  *             This parameter can be one of the following values:
  *             @arg PWR_CORE_CPU2: Release the CPU2 from holding.
  * @retval None
  */
void HAL_PWREx_ReleaseCore(uint32_t CPU)
{
  /* Check the parameters */
  assert_param(IS_PWR_CORE_HOLD_RELEASE(CPU));

  LL_PWR_EnableBootC2();
}

/****************************************************************************/
#ifdef CORE_CM0PLUS
/**
  * @brief  Enable CPU2 wake-up from low-power mode on illegal access occurrence
  * @note   Can be configured from CPU2 only
  * @retval None
  */
void HAL_PWREx_EnableWakeUp_ILAC(void)
{
  LL_PWR_C2_EnableWakeUp_ILAC();
}

/**
  * @brief  Disable CPU2 wake-up from low-power mode on illegal access occurrence
  * @note   Can be configured from CPU2 only
  * @retval None
  */
void HAL_PWREx_DisableWakeUp_ILAC(void)
{
  LL_PWR_C2_DisableWakeUp_ILAC();
}

/**
  * @brief  Check if bit to wake-up CPU2 from low-power mode on illegal access
  *         occurrence is set
  * @note   Can be used from CPU2 only
  * @retval State of bit (1 or 0)
  */
uint32_t HAL_PWREx_IsEnabledWakeUp_ILAC(void)
{
  return LL_PWR_C2_IsEnabledWakeUp_ILAC();
}
#endif
#endif

/****************************************************************************/
/**
  * @brief Enable SRAM2 content retention in Standby mode.
  * @note  When RRS bit is set, SRAM is powered by the low-power regulator in
  *         Standby mode and its content is kept.
  * @retval None
  */
void HAL_PWREx_EnableSRAMRetention(void)
{
  LL_PWR_EnableSRAM2Retention();
}

/**
  * @brief Disable SRAM2 content retention in Standby mode.
  * @note  When RRS bit is reset, SRAM is powered off in Standby mode
  *        and its content is lost.
  * @retval None
  */
void HAL_PWREx_DisableSRAMRetention(void)
{
  LL_PWR_DisableSRAM2Retention();
}

/****************************************************************************/
/**
  * @brief  Enable Flash Power Down.
  * @note   This API allows to enable flash power down capabilities in low power
  *         run and low power sleep modes.
  * @note   This configuration is effective when both CPU have selected it.
  * @param  PowerMode this can be a combination of following values:
  *           @arg @ref PWR_FLASHPD_LPRUN
  *           @arg @ref PWR_FLASHPD_LPSLEEP
  * @retval None
  */
void HAL_PWREx_EnableFlashPowerDown(uint32_t PowerMode)
{
  assert_param(IS_PWR_FLASH_POWERDOWN(PowerMode));

#ifdef CORE_CM0PLUS
  if ((PowerMode & PWR_FLASHPD_LPRUN) != 0U)
  {
    /* Unlock bit FPDR */
    WRITE_REG(PWR->C2CR1, PWR_FLASH_POWER_MODE_UNLOCK_CODE);
  }

  /* Set flash power down mode */
  SET_BIT(PWR->C2CR1, PowerMode);
#else
  if ((PowerMode & PWR_FLASHPD_LPRUN) != 0U)
  {
    /* Unlock bit FPDR */
    WRITE_REG(PWR->CR1, PWR_FLASH_POWER_MODE_UNLOCK_CODE);
  }

  /* Set flash power down mode */
  SET_BIT(PWR->CR1, PowerMode);
#endif
}

/**
  * @brief  Disable Flash Power Down.
  * @note   This API allows to disable flash power down capabilities in low power
  *         run and low power sleep modes.
  * @note   This configuration is effective when both CPU have selected it.
  * @param  PowerMode this can be a combination of following values:
  *           @arg @ref PWR_FLASHPD_LPRUN
  *           @arg @ref PWR_FLASHPD_LPSLEEP
  * @retval None
  */
void HAL_PWREx_DisableFlashPowerDown(uint32_t PowerMode)
{
  assert_param(IS_PWR_FLASH_POWERDOWN(PowerMode));

#ifdef CORE_CM0PLUS
  /* Set flash power down mode */
  CLEAR_BIT(PWR->C2CR1, PowerMode);
#else
  /* Set flash power down mode */
  CLEAR_BIT(PWR->CR1, PowerMode);
#endif
}

/****************************************************************************/
/**
  * @brief  Enable wake-up power voltage detection
  * @note   Wake-up power voltage detection status can be checked
  *         using flag @ref PWR_FLAG_WPVD.
  * @retval None
  */
void HAL_PWREx_EnableWPVD(void)
{
#ifdef CORE_CM0PLUS
  LL_C2_PWR_EnableWPVD();
#else
  LL_PWR_EnableWPVD();
#endif
}

/**
  * @brief  Disable wake-up power voltage detection
  * @retval None
  */
void HAL_PWREx_DisableWPVD(void)
{
#ifdef CORE_CM0PLUS
  LL_C2_PWR_DisableWPVD();
#else
  LL_PWR_DisableWPVD();
#endif
}

/**
  * @brief  Enable periodical sampling of supply voltage in Stop and Standby
  *         modes for detecting condition of PDR and BOR reset.
  * @note   Caution: When enabled, and if the supply voltage drops below
  *         the minimum operating condition between two supply voltage samples,
  *         the reset condition is missed and no reset is generated.
  * @retval None
  */
void HAL_PWREx_EnableBORPVD_ULP(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_ULPEN);
}


/**
  * @brief  Disable periodical sampling of supply voltage in Stop and Standby
  *         modes for detecting condition of PDR and BOR reset.
  * @note  All the other modes are not affected by this bit
  * @retval None
  */
void HAL_PWREx_DisableBORPVD_ULP(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_ULPEN);
}

/****************************************************************************/

/**
  * @brief Enable the Power Voltage Monitoring 3: VDDA versus 1.62V.
  * @retval None
  */
void HAL_PWREx_EnablePVM3(void)
{
  SET_BIT(PWR->CR2, PWR_PVM_3);
}

/**
  * @brief Disable the Power Voltage Monitoring 3: VDDA versus 1.62V.
  * @retval None
  */
void HAL_PWREx_DisablePVM3(void)
{
  CLEAR_BIT(PWR->CR2, PWR_PVM_3);
}

/**
  * @brief Configure the Peripheral Voltage Monitoring (PVM).
  * @param sConfigPVM pointer to a PWR_PVMTypeDef structure that contains the
  *        PVM configuration information.
  * @note The API configures a single PVM according to the information contained
  *       in the input structure. To configure several PVMs, the API must be singly
  *       called for each PVM used.
  * @note Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage thresholds corresponding to each
  *         detection level and to each monitored supply.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PWREx_ConfigPVM(PWR_PVMTypeDef *sConfigPVM)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_PWR_PVM_TYPE(sConfigPVM->PVMType));
  assert_param(IS_PWR_PVM_MODE(sConfigPVM->Mode));

  /* Configure EXTI lines if so required:
     scan through PVMType to detect which PVMx is set and
     configure the corresponding EXTI line accordingly. */
  switch (sConfigPVM->PVMType)
  {
    case PWR_PVM_3:
      /* Clear any previous config. Keep it clear if no event or IT mode is selected */
      __HAL_PWR_PVM3_EXTI_DISABLE_EVENT();
      __HAL_PWR_PVM3_EXTI_DISABLE_IT();
      
      __HAL_PWR_PVM3_EXTI_DISABLE_FALLING_EDGE();
      __HAL_PWR_PVM3_EXTI_DISABLE_RISING_EDGE();

      /* Configure interrupt mode */
      if ((sConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_PVM3_EXTI_ENABLE_IT();
      }

      /* Configure the edge */
      if ((sConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_PVM3_EXTI_ENABLE_RISING_EDGE();
      }

      if ((sConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_PVM3_EXTI_ENABLE_FALLING_EDGE();
      }
      break;

    default:
      status = HAL_ERROR;
      break;

  }

  return status;
}

/**
  * @brief  Set monitoring of supply voltage for radio operating level
  *         (radio End Of Life), radio must be in active mode.
  * @param  RadioEOL This parameter can be one of the following values:
  *         @arg @ref PWR_RADIO_EOL_ENABLE
  *         @arg @ref PWR_RADIO_EOL_DISABLE
  * @retval None
  */
void HAL_PWREx_SetRadioEOL(uint32_t RadioEOL)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_RFEOLEN, RadioEOL);
}

/****************************************************************************/

/**
  * @brief Set SMPS operating mode.
  * @note   In case of a board without SMPS coil mounted, SMPS should not be activated.
  * @param  OperatingMode This parameter can be one of the following values:
  *         @arg @ref PWR_SMPS_BYPASS
  *         @arg @ref PWR_SMPS_STEP_DOWN
  * @retval None
  */
void HAL_PWREx_SMPS_SetMode(uint32_t OperatingMode)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSEN, OperatingMode);
}

/**
  * @brief  Get SMPS effective operating mode
  * @note   SMPS operating mode can be changed by hardware, therefore
  *         requested operating mode can differ from effective low power mode.
  *         - dependency SubGhz Radio IP: can switch SMPS on for radio activity.
  * @note   In case of a board without SMPS coil mounted, SMPS should not be activated
  *         and this function is not relevant.
  * @retval Returned value can be one of the following values:
  *         @arg @ref PWR_SMPS_BYPASS
  *         @arg @ref PWR_SMPS_STEP_DOWN
  */
uint32_t HAL_PWREx_SMPS_GetEffectiveMode(void)
{
  /* Return a value corresponding to definition of literals                   */
  /* PWR_SMPS_BYPASS or PWR_SMPS_STEP_DOWN.                                   */
  return (uint32_t)(READ_BIT(PWR->SR2, PWR_SR2_SMPSRDY) << (PWR_CR5_SMPSEN_Pos - PWR_SR2_SMPSRDY_Pos));
}

/****************************************************************************/

/**
  * @brief Enter Low-power Run mode
  * @note  In Low-power Run mode, all I/O pins keep the same state as in Run mode.
  * @note  Clock frequency must be reduced below 2 MHz.
  * @retval None
  */
void HAL_PWREx_EnableLowPowerRunMode(void)
{
  /* Set Regulator parameter */
  SET_BIT(PWR->CR1, PWR_CR1_LPR);
}

/**
  * @brief Exit Low-power Run mode.
  * @note  Before HAL_PWREx_DisableLowPowerRunMode() completion, the function checks that
  *        REGLPF has been properly reset (otherwise, HAL_PWREx_DisableLowPowerRunMode
  *        returns HAL_TIMEOUT status). The system clock frequency can then be
  *        increased above 2 MHz.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_DisableLowPowerRunMode(void)
{
  uint32_t wait_loop_index;

  /* Clear LPR bit */
  CLEAR_BIT(PWR->CR1, PWR_CR1_LPR);

  /* Wait until REGLPF is reset */
  wait_loop_index = ((PWR_FLAG_SETTING_DELAY_US * SystemCoreClock) / 1000000UL);
  while ((HAL_IS_BIT_SET(PWR->SR2, PWR_SR2_REGLPF)) && (wait_loop_index != 0U))
  {
    wait_loop_index--;
  }
  if (HAL_IS_BIT_SET(PWR->SR2, (PWR_SR2_REGLPF)))
  {
    return HAL_TIMEOUT;
  }

  return HAL_OK;
}

/****************************************************************************/

/**
  * @brief Enter Stop 0 mode.
  * @note  In Stop 0 mode, main and low voltage regulators are ON.
  * @note  In Stop 0 mode, all I/O pins keep the same state as in Run mode.
  * @note  All clocks in the VCORE domain are stopped; the PLL, the MSI,
  *        the HSI and the HSE oscillators are disabled. Some peripherals with the wakeup capability
  *        (I2Cx, USARTx and LPUART) can switch on the HSI to receive a frame, and switch off the HSI
  *        after receiving the frame if it is not a wakeup frame. In this case, the HSI clock is propagated
  *        only to the peripheral requesting it.
  *        SRAM1, SRAM2 and register contents are preserved.
  *        The BOR is available.
  * @note  When exiting Stop 0 mode by issuing an interrupt or a wakeup event,
  *         the HSI RC oscillator is selected as system clock if STOPWUCK bit in RCC_CFGR register
  *         is set; the MSI oscillator is selected if STOPWUCK is cleared.
  * @note  By keeping the internal regulator ON during Stop 0 mode, the consumption
  *         is higher although the startup time is reduced.
  * @note  According to system power policy, system entering in Stop mode
  *        is depending on other CPU power mode.
  * @param STOPEntry  specifies if Stop mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *            @arg @ref PWR_STOPENTRY_WFI  Enter Stop mode with WFI instruction
  *            @arg @ref PWR_STOPENTRY_WFE  Enter Stop mode with WFE instruction
  * @retval None
  */
void HAL_PWREx_EnterSTOP0Mode(uint8_t STOPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));

#ifdef CORE_CM0PLUS
  /* Stop 0 mode with Main Regulator */
  MODIFY_REG(PWR->C2CR1, PWR_C2CR1_LPMS, PWR_LOWPOWERMODE_STOP0);

#else
  /* Stop 0 mode with Main Regulator */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_LOWPOWERMODE_STOP0);

#endif

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select Stop mode entry --------------------------------------------------*/
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
  * @brief Enter Stop 1 mode.
  * @note  In Stop 1 mode, only low power voltage regulator is ON.
  * @note  In Stop 1 mode, all I/O pins keep the same state as in Run mode.
  * @note  All clocks in the VCORE domain are stopped; the PLL, the MSI,
  *        the HSI and the HSE oscillators are disabled. Some peripherals with the wakeup capability
  *        (I2Cx, USARTx and LPUART) can switch on the HSI to receive a frame, and switch off the HSI
  *        after receiving the frame if it is not a wakeup frame. In this case, the HSI clock is propagated
  *        only to the peripheral requesting it.
  *        SRAM1, SRAM2 and register contents are preserved.
  *        The BOR is available.
  * @note  When exiting Stop 1 mode by issuing an interrupt or a wakeup event,
  *         the HSI RC oscillator is selected as system clock if STOPWUCK bit in RCC_CFGR register
  *         is set; the MSI oscillator is selected if STOPWUCK is cleared.
  * @note  Due to low power mode, an additional startup delay is incurred when waking up from Stop 1 mode.
  * @note  According to system power policy, system entering in Stop mode
  *        is depending on other CPU power mode.
  * @param STOPEntry  specifies if Stop mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *            @arg @ref PWR_STOPENTRY_WFI  Enter Stop mode with WFI instruction
  *            @arg @ref PWR_STOPENTRY_WFE  Enter Stop mode with WFE instruction
  * @retval None
  */
void HAL_PWREx_EnterSTOP1Mode(uint8_t STOPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));

#ifdef CORE_CM0PLUS
  /* Stop 1 mode with Low-Power Regulator */
  MODIFY_REG(PWR->C2CR1, PWR_C2CR1_LPMS, PWR_LOWPOWERMODE_STOP1);
#else
  /* Stop 1 mode with Low-Power Regulator */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_LOWPOWERMODE_STOP1);
#endif

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select Stop mode entry --------------------------------------------------*/
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
  * @brief Enter Stop 2 mode.
  * @note  In Stop 2 mode, only low power voltage regulator is ON.
  * @note  In Stop 2 mode, all I/O pins keep the same state as in Run mode.
  * @note  All clocks in the VCORE domain are stopped, the PLL, the MSI,
  *        the HSI and the HSE oscillators are disabled. Some peripherals with wakeup capability
  *        (LCD, LPTIM1, I2C3 and LPUART) can switch on the HSI to receive a frame, and switch off the HSI after
  *        receiving the frame if it is not a wakeup frame. In this case the HSI clock is propagated only
  *        to the peripheral requesting it.
  *        SRAM1, SRAM2 and register contents are preserved.
  *        The BOR is available.
  *        The voltage regulator is set in low-power mode but LPR bit must be cleared to enter stop 2 mode.
  *        Otherwise, Stop 1 mode is entered.
  * @note  When exiting Stop 2 mode by issuing an interrupt or a wakeup event,
  *         the HSI RC oscillator is selected as system clock if STOPWUCK bit in RCC_CFGR register
  *         is set; the MSI oscillator is selected if STOPWUCK is cleared.
  * @note  According to system power policy, system entering in Stop mode
  *        is depending on other CPU power mode.
  * @param STOPEntry  specifies if Stop mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *            @arg @ref PWR_STOPENTRY_WFI  Enter Stop mode with WFI instruction
  *            @arg @ref PWR_STOPENTRY_WFE  Enter Stop mode with WFE instruction
  * @retval None
  */
void HAL_PWREx_EnterSTOP2Mode(uint8_t STOPEntry)
{
  /* Check the parameter */
  assert_param(IS_PWR_STOP_ENTRY(STOPEntry));

#ifdef CORE_CM0PLUS
  /* Set Stop mode 2 */
  MODIFY_REG(PWR->C2CR1, PWR_C2CR1_LPMS, PWR_LOWPOWERMODE_STOP2);
#else
  /* Set Stop mode 2 */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_LOWPOWERMODE_STOP2);
#endif

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select Stop mode entry --------------------------------------------------*/
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
  * @brief Enter Shutdown mode.
  * @note  In Shutdown mode, the PLL, the HSI, the MSI, the LSI and the HSE oscillators are switched
  *        off. The voltage regulator is disabled and Vcore domain is powered off.
  *        SRAM1, SRAM2 and registers contents are lost except for registers in the Backup domain.
  *        The BOR is not available.
  * @note  The I/Os can be configured either with a pull-up or pull-down or can be kept in analog state.
  * @note  According to system power policy, system entering in Shutdown mode
  *        is depending on other CPU power mode.
  * @retval None
  */
void HAL_PWREx_EnterSHUTDOWNMode(void)
{
#ifdef CORE_CM0PLUS
  /* Set Shutdown mode */
  MODIFY_REG(PWR->C2CR1, PWR_C2CR1_LPMS, PWR_LOWPOWERMODE_SHUTDOWN);
#else
  /* Set Shutdown mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_LOWPOWERMODE_SHUTDOWN);
#endif

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM)
  __force_stores();
#endif

  /* Request Wait For Interrupt */
  __WFI();

  /* Note: After this request to enter in Shutdown mode, at wake-up, program
           execution depends on system low-power mode:
           - If system was in Shutdown mode (other CPU in Shutdown),
             then at wake-up program restarts at reset state
           - If system was in Run or Stop mode (other CPU in Run, Sleep, Stop),
             then at wake-up program continues from this point
  */
}

/**
  * @brief This function handles the PWR PVD/PVMx interrupt request.
  * @note This API should be called under the PVD_PVM_IRQHandler().
  * @retval None
  */
void HAL_PWREx_PVD_PVM_IRQHandler(void)
{
  /* Check PWR exti flag */
  if (__HAL_PWR_PVD_EXTI_GET_FLAG() != 0UL)
  {
    /* Clear PVD exti pending bit */
    __HAL_PWR_PVD_EXTI_CLEAR_FLAG();

    /* PWR PVD interrupt user callback */
    HAL_PWR_PVDCallback();
  }

  if (__HAL_PWR_PVM3_EXTI_GET_FLAG() != 0UL)
  {
    /* Clear PVM3 exti pending bit */
    __HAL_PWR_PVM3_EXTI_CLEAR_FLAG();

    /* PWR PVM3 interrupt user callback */
    HAL_PWREx_PVM3Callback();
  }
}

/**
  * @brief PWR PVM3 interrupt callback
  * @retval None
  */
__weak void HAL_PWREx_PVM3Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWREx_PVM3Callback() API can be implemented in the user file
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
