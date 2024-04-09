/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_pwr_ex.c
  * @author  MCD Application Team
  * @brief   Extended PWR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of PWR extension peripheral:
  *           + Peripheral Extended features functions
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
                        ##### How to use this driver #####
  ==============================================================================
  [..]
   (#) Call HAL_PWREx_ConfigSupply() function to configure the regulator supply
       with the following different setups according to hardware (support SMPS):
       (+) PWR_DIRECT_SMPS_SUPPLY
       (+) PWR_SMPS_1V8_SUPPLIES_LDO
       (+) PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO
       (+) PWR_SMPS_1V8_SUPPLIES_EXT
       (+) PWR_LDO_SUPPLY
       (+) PWR_EXTERNAL_SOURCE_SUPPLY

   (#) Call HAL_PWREx_GetSupplyConfig() function to get the current supply setup.

   (#) Call HAL_PWREx_ControlVoltageScaling() function to configure the main
       internal regulator output voltage. The voltage scaling could be one of
       the following scales :
       (+) PWR_REGULATOR_VOLTAGE_SCALE0
       (+) PWR_REGULATOR_VOLTAGE_SCALE1

   (#) Call HAL_PWREx_GetVoltageRange() function to get the current output
       voltage applied to the main regulator.

   (#) Call HAL_PWREx_ControlStopModeVoltageScaling() function to configure the main
       internal regulator output voltage in STOP mode. The voltage scaling could be one of
       the following scales :
       (+) PWR_REGULATOR_STOP_VOLTAGE_SCALE3
       (+) PWR_REGULATOR_STOP_VOLTAGE_SCALE5

   (#) Call HAL_PWREx_GetStopModeVoltageRange() function to get the current output
       voltage applied to the main regulator in STOP mode.

   (#) Call HAL_PWREx_EnableFlashPowerDown() and
       HAL_PWREx_DisableFlashPowerDown() functions to enable and disable the
       Flash Power Down in STOP mode.

   (#) Call HAL_PWREx_EnableWakeUpPin() and HAL_PWREx_DisableWakeUpPin()
       functions to enable and disable the Wake-up pin functionality for
       the selected pin.

   (#) Call HAL_PWREx_GetWakeupFlag() and HAL_PWREx_ClearWakeupFlag()
       functions to manage wake-up flag for the selected pin.

   (#) Call HAL_PWREx_WAKEUP_PIN_IRQHandler() function to handle all wake-up
       pins interrupts.

   (#) Call HAL_PWREx_EnableBkUpReg() and HAL_PWREx_DisableBkUpReg() functions
       to enable and disable the backup domain regulator.

   (#) Call HAL_PWREx_EnableUSBReg(), HAL_PWREx_DisableUSBReg(),
       HAL_PWREx_EnableUSBVoltageDetector() and
       HAL_PWREx_DisableUSBVoltageDetector() functions to manage USB power
       regulation functionalities.

   (#) Call HAL_PWREx_EnableUCPDStandbyMode() and HAL_PWREx_DisableUCPDStandbyMode() functions
       to enable and disable UCPD Standby mode.

   (#) Call HAL_PWREx_EnableUCPDDeadBattery() and HAL_PWREx_DisableUCPDDeadBattery() functions
       to enable and disable UCPD dead battery.

   (#) Call HAL_PWREx_EnableBatteryCharging() and
       HAL_PWREx_DisableBatteryCharging() functions to enable and disable the
       battery charging feature with the selected resistor.

   (#) Call HAL_PWREx_EnableAnalogBooster() and HAL_PWREx_DisableAnalogBooster() functions
       to enable and disable the AVD boost feature when the VDD supply voltage is below 2V7.

   (#) Call HAL_PWREx_EnableXSPIM1() and HAL_PWREx_DisableXSPIM1() functions
       to enable and disable the XSPIM1.

   (#) Call HAL_PWREx_EnableXSPIM2() and HAL_PWREx_DisableXSPIM2() functions
       to enable and disable the XSPIM2.

   (#) Call HAL_PWREx_ConfigXSPIPortCap() functions to configure the XSPI capacitor port 1 and 2.
      The capacitor setting could be one of the following values :
       (+) PWR_CAPACITOR_OFF
       (+) PWR_CAPACITOR_ONE_THIRD_CAPACITANCE
       (+) PWR_CAPACITOR_TWO_THIRD_CAPACITANCE
       (+) PWR_CAPACITOR_FULL_CAPACITANCE

   (#) Call HAL_PWREx_GetConfigXSPIPortCap() function to get the current
       capacitor port setting.

   (#) Call HAL_PWREx_EnableMonitoring() and HAL_PWREx_DisableMonitoring()
       functions to enable and disable the VBAT and Temperature monitoring.
       When VBAT and Temperature monitoring feature is enables, use
       HAL_PWREx_GetTemperatureLevel() and HAL_PWREx_GetVBATLevel() to get
       respectively the Temperature level and VBAT level.

   (#) Call HAL_PWREx_ConfigAVD() after setting parameter to be configured
       (event mode and voltage threshold) in order to set up the Analog Voltage
       Detector then use HAL_PWREx_EnableAVD() and  HAL_PWREx_DisableAVD()
       functions to start and stop the AVD detection.
       (+) AVD level could be one of the following values :
             (++) 1V7
             (++) 2V1
             (++) 2V5
             (++) 2V8

   (#) Call HAL_PWREx_PVD_AVD_IRQHandler() function to handle the PWR PVD and
       AVD interrupt request.

   (#) Call HAL_PWREx_EnablePullUpPullDownConfig() and
       HAL_PWREx_DisablePullUpPullDownConfig() to I/O enable / disable pull-up
       and pull-down configuration.

   (#) Call HAL_PWREx_EnableGPIOPullUp() and HAL_PWREx_EnableGPIOPullDown() to
       apply respectively pull-up and pull-down to selected I/O.
       Call HAL_PWREx_DisableGPIOPullUp() and HAL_PWREx_DisableGPIOPullDown() to
       disable applied respectively pull-up and pull-down to selected I/O.

  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
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
#define AVD_MODE_IT                    (0x00010000U)
#define AVD_MODE_EVT                   (0x00020000U)
#define AVD_RISING_EDGE                (0x00000001U)
#define AVD_FALLING_EDGE               (0x00000002U)
#define AVD_RISING_FALLING_EDGE        (0x00000003U)
/**
  * @}
  */

/** @defgroup PWREx_REG_SET_TIMEOUT PWR Extended Flag Setting Time Out Value
  * @{
  */
#define PWR_FLAG_SETTING_DELAY         (1000U)
/**
  * @}
  */

/** @defgroup PWREx_WakeUp_Pins_Offsets PWREx Wake-Up Pins masks and offsets
  * @{
  */
/* Wake-Up Pins EXTI register mask */
#define PWR_EXTI_WAKEUP_PINS_MASK  (EXTI_IMR2_IM55 | EXTI_IMR2_IM56 |\
                                    EXTI_IMR2_IM57 | EXTI_IMR2_IM58 )

/* Wake-Up Pins PWR Pin Pull shift offsets */
#define PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET (2U)
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

/** @defgroup PWREx_Exported_Functions_Group1 Power Supply Control Functions
  * @brief    Power supply control functions
  *
@verbatim
 ===============================================================================
                  ##### Power supply control functions #####
 ===============================================================================
    [..]
   (#) When the system is powered on, the POR monitors VDD supply. Once VDD is
       above the POR threshold level, the SMPS step-down converter and voltage
      regulator are enabled in the default supply configuration:

      (+) The SMPS step-down converter output level is set at 1.35 V.
          The voltage regulator LDO output level is set at 1.11 V.
          Depending on the package and configuration the SMPS provides the
          voltage to internal power domain and/or LDO or external supply.

      (+) The system is kept in reset mode as long as VCORE is not stable.

      (+) Once VCORE is stable, the system is taken out of reset and the HSI
          oscillator is enabled.

      (+) Once the oscillator is stable, the system is initialized: Flash memory
          is ready, option bytes are loaded and the CPU starts in limited run mode.

      (+) The software must then initialize the system including supply
          configuration programming in PWR control register 2 (PWR_CSR2).
          Once the supply configuration has been configured, the ACTVOSRDY bit in
          the PWR control status register 1 (PWR_SR1) must be checked to guarantee
          valid voltage levels:
          a) As long as ACTVOSRDY indicates that voltage levels are invalid, the
             system is in Run mode, write accesses to the RAMs are not permitted and
             VOS must not be changed.
          b) Once ACTVOSRDY indicates that voltage levels are valid, the system is
             in normal Run mode, write accesses to RAMs are allowed and VOS can be
             changed.

@endverbatim
  * @{
  */

/**
  * @brief Configure the system Power Supply.
  * @param  SupplySource : Specifies the Power Supply source to set after a
  *                        system startup.
  *         This parameter can be one of the following values :
  *            @arg PWR_DIRECT_SMPS_SUPPLY : The SMPS supplies the Vcore Power
  *                                          Domains. The LDO is Bypassed.
  *            @arg PWR_SMPS_1V8_SUPPLIES_LDO : The SMPS 1.8V output supplies
  *                                             the LDO. The Vcore Power Domains
  *                                             are supplied from the LDO.
  *            @arg PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO : The SMPS 1.8V output
  *                                                     supplies external
  *                                                     circuits and the LDO.
  *                                                     The Vcore Power Domains
  *                                                     are supplied from the
  *                                                     LDO.
  *            @arg PWR_SMPS_1V8_SUPPLIES_EXT : The SMPS 1.8V output supplies
  *                                             external circuits. The LDO is
  *                                             Bypassed. The Vcore Power
  *                                             Domains are supplied from
  *                                             external source.
  *            @arg PWR_LDO_SUPPLY : The LDO regulator supplies the Vcore Power
  *                                  Domains. The SMPS regulator is Bypassed.
  *            @arg PWR_EXTERNAL_SOURCE_SUPPLY : The SMPS is disabled and the LDO are
  *                                              Bypassed. The Vcore Power
  *                                              Domains are supplied from
  *                                              external source.
  * @note The SMPS step-down converter is not available on all packages,
  *       and the Bypass mode is available only when the SMPS is available.
  * @note  The PWR_DIRECT_SMPS_SUPPLY, PWR_SMPS_1V8_SUPPLIES_LDO,
  *        PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO and PWR_SMPS_1V8_SUPPLIES_EXT are used
  *        only for lines that supports SMPS regulator.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_PWREx_ConfigSupply(uint32_t SupplySource)
{
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_PWR_SUPPLY(SupplySource));

  /* Check if supply source was configured */
  if ((PWR->CSR2 & (PWR_CSR2_SDEN | PWR_CSR2_LDOEN | PWR_CSR2_BYPASS)) != (PWR_CSR2_SDEN | PWR_CSR2_LDOEN))
  {
    /* Check supply configuration */
    if ((PWR->CSR2 & PWR_SUPPLY_CONFIG_MASK) != SupplySource)
    {
      /* Supply configuration update locked, can't apply a new supply config */
      return HAL_ERROR;
    }
    else
    {
      /* Supply configuration update locked, but new supply configuration
         matches with old supply configuration : nothing to do
      */
      return HAL_OK;
    }
  }

  /* Set the power supply configuration */
  MODIFY_REG(PWR->CSR2, PWR_SUPPLY_CONFIG_MASK, SupplySource);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait till voltage level flag is set */
  while ((PWR->SR1 & PWR_SR1_ACTVOSRDY) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > PWR_FLAG_SETTING_DELAY)
    {
      return HAL_ERROR;
    }
  }

  /* When the SMPS supplies external circuits verify that SDEXTRDY flag is set */
  if ((SupplySource == PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO) ||
      (SupplySource == PWR_SMPS_1V8_SUPPLIES_EXT))
  {
    /* Get the current tick number */
    tickstart = HAL_GetTick();

    /* Wait till SMPS external supply ready flag is set */
    while ((PWR->CSR2 & PWR_CSR2_SDEXTRDY) == 0U)
    {
      if ((HAL_GetTick() - tickstart) > PWR_FLAG_SETTING_DELAY)
      {
        return HAL_ERROR;
      }
    }
  }
  return HAL_OK;
}

/**
  * @brief Get the power supply configuration.
  * @retval The supply configuration.
  */
uint32_t HAL_PWREx_GetSupplyConfig(void)
{
  return (PWR->CSR2 & PWR_SUPPLY_CONFIG_MASK);
}

/**
  * @brief Configure the main internal regulator output voltage.
  * @param  VoltageScaling : Specifies the regulator output voltage to achieve
  *                          a tradeoff between performance and power
  *                          consumption.
  *          This parameter can be one of the following values :
  *            @arg PWR_REGULATOR_VOLTAGE_SCALE0 : Regulator voltage scaling range 0 (highest frequency).
  *            @arg PWR_REGULATOR_VOLTAGE_SCALE1 : Regulator voltage scaling range 1 (lowest power).
  * @note When increasing the performance, the voltage scaling must be changed
  *       before increasing the system frequency.
  *       When decreasing performance, the system frequency must first be decreased
  *       before changing the voltage scaling.
  * @note When exiting from Stop mode or Standby mode, the Run mode voltage
  *       scaling is reset to the default VOS low value.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling)
{
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_PWR_REGULATOR_VOLTAGE(VoltageScaling));

  /* Set the voltage range */
  MODIFY_REG(PWR->CSR4, PWR_CSR4_VOS, VoltageScaling);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait till voltage level flag is set */
  while ((PWR->CSR4 & PWR_CSR4_VOSRDY) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > PWR_FLAG_SETTING_DELAY)
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief Get the main internal regulator output voltage. Reflecting the last
  *        VOS value applied to the PMU.
  * @retval The current applied VOS selection.
  */
uint32_t HAL_PWREx_GetVoltageRange(void)
{
  /* Get the active voltage scaling */
  return (PWR->SR1 & PWR_SR1_ACTVOS);
}

/**
  * @brief Configure the main internal regulator output voltage in STOP mode.
  * @param  VoltageScaling : Specifies the regulator output voltage when the
  *         system enters Stop mode to achieve a tradeoff between performance
  *         and power consumption.
  *          This parameter can be one of the following values:
  *            @arg PWR_REGULATOR_STOP_VOLTAGE_SCALE3 : System Stop mode voltage scaling range 3 (highest frequency).
  *            @arg PWR_REGULATOR_STOP_VOLTAGE_SCALE5 : System Stop mode voltage scaling range 5 (lowest power).
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_PWREx_ControlStopModeVoltageScaling(uint32_t VoltageScaling)
{
  /* Check the parameters */
  assert_param(IS_PWR_STOP_MODE_REGULATOR_VOLTAGE(VoltageScaling));

  /* Return the stop mode voltage range */
  MODIFY_REG(PWR->CR1, PWR_CR1_SVOS, VoltageScaling);

  return HAL_OK;
}

/**
  * @brief Get the main internal regulator output voltage in STOP mode.
  * @retval The actual applied SVOS selection.
  */
uint32_t HAL_PWREx_GetStopModeVoltageRange(void)
{
  /* Return the stop voltage scaling */
  return (PWR->CR1 & PWR_CR1_SVOS);
}
/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group2 Low Power Control Functions
  * @brief    Low Power Control Functions
  *
@verbatim
 ===============================================================================
                     ##### Low Power Control Functions #####
 ===============================================================================

    *** FLASH Power Down configuration ****
    =======================================
    [..]
      By setting the FLPS bit in the PWR_CR1 register using the
      HAL_PWREx_EnableFlashPowerDown() function, the Flash memory also enters
      power down mode when the device enters STOP mode. When the Flash memory is
      in power down mode, an additional startup delay is incurred when waking up
      from STOP mode.

    *** Wakeup Pins configuration ****
    ===================================
    [..]
      Wakeup pins allow the system to exit from Standby mode. The configuration
      of wakeup pins is done with the HAL_PWREx_EnableWakeUpPin(sPinParams)
      function with:
       (+) sPinParams: structure to enable and configure a wakeup pin:
        (++) WakeUpPin: Wakeup pin to be enabled.
        (++) PinPolarity: Wakeup pin polarity (rising or falling edge).
        (++) PinPull: Wakeup pin pull (no pull, pull-up or pull-down).
    [..]
      The wakeup pins are internally connected to the EXTI lines [55-58] to
      generate an interrupt if enabled. The EXTI lines configuration is done by
      the HAL_EXTI_Dx_EventInputConfig() functions defined in the stm32h7rsxxhal.c
      file.
    [..]
      When a wakeup pin event is received the HAL_PWREx_WAKEUP_PIN_IRQHandler is
      called and the appropriate flag is set in the PWR_WKUPFR register. Then in
      the HAL_PWREx_WAKEUP_PIN_IRQHandler function the wakeup pin flag will be
      cleared and the appropriate user callback will be called. The user can add
      his own code by customization of function pointer HAL_PWREx_WKUPx_Callback.

@endverbatim
  * @{
  */

/**
  * @brief Enable the Flash Power Down in Stop mode.
  * @note   When Flash Power Down is enabled the Flash memory enters low-power
  *         mode when device is in Stop mode. This feature allows to
  *         obtain the best trade-off between low-power consumption and restart
  *         time when exiting from Stop mode.
  * @retval None.
  */
void HAL_PWREx_EnableFlashPowerDown(void)
{
  /* Enable the Flash Power Down */
  SET_BIT(PWR->CR1, PWR_CR1_FLPS);
}

/**
  * @brief Disable the Flash Power Down in Stop mode.
  * @note   When Flash Power Down is disabled  the Flash memory is kept on
  *         normal mode when device is in Stop mode. This feature allows
  *         to obtain the best trade-off between low-power consumption and
  *         restart time when exiting from Stop mode.
  * @retval None.
  */
void HAL_PWREx_DisableFlashPowerDown(void)
{
  /* Disable the Flash Power Down */
  CLEAR_BIT(PWR->CR1, PWR_CR1_FLPS);
}

/**
  * @brief Enable the Wake-up PINx functionality.
  * @param  sPinParams : Pointer to a PWREx_WakeupPinTypeDef structure that
  *                      contains the configuration information for the wake-up
  *                      Pin.
  * @retval None.
  */
void HAL_PWREx_EnableWakeUpPin(const PWREx_WakeupPinTypeDef *sPinParams)
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

  /* Configure the Wakeup Pin EXTI Line */
  MODIFY_REG(EXTI->IMR2, PWR_EXTI_WAKEUP_PINS_MASK, (sPinParams->WakeUpPin << EXTI_IMR2_IM55_Pos));
}

/**
  * @brief Disable the Wake-up PINx functionality.
  * @param  WakeUpPin : Specifies the Wake-Up pin to be disabled.
  *          This parameter can be one of the following values:
  *           @arg PWR_WAKEUP_PIN1 : Disable PA0  wake-up PIN.
  *           @arg PWR_WAKEUP_PIN2 : Disable PA2  wake-up PIN.
  *           @arg PWR_WAKEUP_PIN3 : Disable PC13 wake-up PIN.
  *           @arg PWR_WAKEUP_PIN4 : Disable PC1  wake-up PIN.
  * @retval None
  */
void HAL_PWREx_DisableWakeUpPin(uint32_t WakeUpPin)
{
  /* Check the parameter */
  assert_param(IS_PWR_WAKEUP_PIN(WakeUpPin));

  /* Disable the WakeUpPin */
  CLEAR_BIT(PWR->WKUPEPR, WakeUpPin);
}

/**
  * @brief Get the Wake-Up Pin pending flags.
  * @param  WakeUpFlag : Specifies the Wake-Up PIN flag to be checked.
  *          This parameter can be one of the following values:
  *            @arg PWR_WAKEUP_FLAG1    : Get wakeup event received from PA0.
  *            @arg PWR_WAKEUP_FLAG2    : Get wakeup event received from PA2.
  *            @arg PWR_WAKEUP_FLAG3    : Get wakeup event received from PC13.
  *            @arg PWR_WAKEUP_FLAG4    : Get wakeup event received from PC1.
  *            @arg PWR_WAKEUP_FLAG_ALL : Get Wakeup event received from all
  *                                      wake up pins.
  * @retval The Wake-Up pin flag.
  */
uint32_t HAL_PWREx_GetWakeupFlag(uint32_t WakeUpFlag)
{
  /* Check the parameters */
  assert_param(IS_PWR_WAKEUP_FLAG(WakeUpFlag));

  /* Return the wake up pin flag */
  return (PWR->WKUPFR & WakeUpFlag);
}

/**
  * @brief Clear the Wake-Up pin pending flag.
  * @param  WakeUpFlag: Specifies the Wake-Up PIN flag to clear.
  *          This parameter can be one of the following values:
  *            @arg PWR_WAKEUP_FLAG1    : Clear the wakeup event received from PA0.
  *            @arg PWR_WAKEUP_FLAG2    : Clear the wakeup event received from PA2.
  *            @arg PWR_WAKEUP_FLAG3    : Clear the wakeup event received from PC13.
  *            @arg PWR_WAKEUP_FLAG4    : Clear the wakeup event received from PC1.
  *            @arg PWR_WAKEUP_FLAG_ALL : Clear the wakeup events received from all
  *                                       wake up pins.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_PWREx_ClearWakeupFlag(uint32_t WakeUpFlag)
{
  /* Check the parameter */
  assert_param(IS_PWR_WAKEUP_FLAG(WakeUpFlag));

  /* Clear the wake up event received from wake up pin x */
  WRITE_REG(PWR->WKUPCR, WakeUpFlag);

  /* Check if the wake up event is well cleared */
  if ((PWR->WKUPFR & WakeUpFlag) != 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief This function handles the PWR WAKEUP PIN interrupt request.
  * @note   This API should be called under the WAKEUP_PIN_IRQHandler().
  * @retval None.
  */
void HAL_PWREx_WAKEUP_PIN_IRQHandler(void)
{
  /* Wakeup pin EXTI line interrupt detected */
  if (READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF1) != 0U)
  {
    /* Clear PWR WKUPF1 flag */
    __HAL_PWR_CLEAR_WAKEUPFLAG(PWR_FLAG_WKUP1);

    /* PWR WKUP1 interrupt user callback */
    HAL_PWREx_WKUP1_Callback();
  }

  if (READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF2) != 0U)
  {
    /* Clear PWR WKUPF2 flag */
    __HAL_PWR_CLEAR_WAKEUPFLAG(PWR_FLAG_WKUP2);

    /* PWR WKUP2 interrupt user callback */
    HAL_PWREx_WKUP2_Callback();
  }

  if (READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF3) != 0U)
  {
    /* Clear PWR WKUPF3 flag */
    __HAL_PWR_CLEAR_WAKEUPFLAG(PWR_FLAG_WKUP3);

    /* PWR WKUP3 interrupt user callback */
    HAL_PWREx_WKUP3_Callback();
  }

  if (READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF4) != 0U)
  {
    /* Clear PWR WKUPF4 flag */
    __HAL_PWR_CLEAR_WAKEUPFLAG(PWR_FLAG_WKUP4);

    /* PWR WKUP4 interrupt user callback */
    HAL_PWREx_WKUP4_Callback();
  }
}

/**
  * @brief PWR WKUP1 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWREx_WKUP1_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWREx_WKUP1Callback can be implemented in the user file
  */
}

/**
  * @brief PWR WKUP2 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWREx_WKUP2_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWREx_WKUP2Callback can be implemented in the user file
  */
}

/**
  * @brief PWR WKUP3 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWREx_WKUP3_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWREx_WKUP3Callback can be implemented in the user file
  */
}

/**
  * @brief PWR WKUP4 interrupt callback.
  * @retval None.
  */
__weak void HAL_PWREx_WKUP4_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWREx_WKUP4Callback can be implemented in the user file
  */
}
/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group3 Peripherals Control Functions
  * @brief    Peripherals Control Functions
  *
@verbatim
 ===============================================================================
                 ##### Peripherals Control Functions #####
 ===============================================================================

    *** Main and Backup Regulators configuration ***
    ================================================
    [..]
      (+) The backup domain includes 4 Kbytes of backup SRAM accessible only
          from the CPU, and addressed in 32-bit, 16-bit or 8-bit mode. Its
          content is retained even in Standby or VBAT mode when the low power
          backup regulator is enabled. It can be considered as an internal
          EEPROM when VBAT is always present. You can use the
          HAL_PWREx_EnableBkUpReg() function to enable the low power backup
          regulator.
      (+) When the backup domain is supplied by VDD (analog switch connected to
          VDD) the backup SRAM is powered from VDD which replaces the VBAT power
          supply to save battery life.
      (+) The backup SRAM is not mass erased by a tamper event. It is read
          protected to prevent confidential data, such as cryptographic private
          key, from being accessed. The backup SRAM can be erased only through
          the Flash interface when a protection level change from level 1 to
          level 0 is requested.
      -@- Refer to the description of Read protection (RDP) in the Flash
          programming manual.
      (+) The main internal regulator can be configured to have a tradeoff
          between performance and power consumption when the device does not
          operate at the maximum frequency. This is done through
          HAL_PWREx_ControlVoltageScaling(VOS) function which configure the VOS
          bit in PWR_CSR4 register.
      (+) The main internal regulator can be configured to operate in Low Power
          mode when the system enters STOP mode to further reduce power
          consumption.
          This is done through HAL_PWREx_ControlStopModeVoltageScaling(SVOS)
          function which configure the SVOS bit in PWR_CR1 register.
    -@- Refer to the product datasheets for more details.

    *** USB Regulator configuration ***
    ===================================
    [..]
      (+) The USB transceivers are supplied from a dedicated VDD33USB supply
          that can be provided either by the integrated USB regulator, or by an
          external USB supply.
      (+) The USB regulator is enabled by HAL_PWREx_EnableUSBReg() function, the
          VDD33USB is then provided from the USB regulator.
      (+) When the USB regulator is enabled, the VDD33USB supply level detector
          shall be enabled through  HAL_PWREx_EnableUSBVoltageDetector()
          function.
      (+) The USB regulator is disabled through HAL_PWREx_DisableUSBReg()
          function and VDD33USB can be provided from an external supply. In this
          case VDD33USB and VDD50USB shall be connected together.

    *** VBAT battery charging ***
    =============================
    [..]
      (+) When VDD is present, the external battery connected to VBAT can be
          charged through an internal resistance. VBAT charging can be performed
          either through a 5 KOhm resistor or through a 1.5 KOhm resistor.
      (+) VBAT charging is enabled by HAL_PWREx_EnableBatteryCharging
          (ResistorValue) function with:
       (++) ResistorValue:
        (+++) PWR_BATTERY_CHARGING_RESISTOR_5: 5 KOhm resistor.
        (+++) PWR_BATTERY_CHARGING_RESISTOR_1_5: 1.5 KOhm resistor.
      (+) VBAT charging is disabled by HAL_PWREx_DisableBatteryCharging()
          function.

@endverbatim
  * @{
  */

/**
  * @brief Enable the Backup Regulator.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_PWREx_EnableBkUpReg(void)
{
  uint32_t tickstart;

  /* Enable the Backup regulator */
  SET_BIT(PWR->CSR1, PWR_CSR1_BREN);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait till Backup regulator ready flag is set */
  while ((PWR->CSR1 & PWR_CSR1_BRRDY) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > PWR_FLAG_SETTING_DELAY)
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief Disable the Backup Regulator.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_PWREx_DisableBkUpReg(void)
{
  uint32_t tickstart;

  /* Disable the Backup regulator */
  CLEAR_BIT(PWR->CSR1, PWR_CSR1_BREN);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait till Backup regulator ready flag is reset */
  while ((PWR->CSR1 & PWR_CSR1_BRRDY)  != 0U)
  {
    if ((HAL_GetTick() - tickstart) > PWR_FLAG_SETTING_DELAY)
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief Enable the USB Regulator.
  * @retval None.
  */
void HAL_PWREx_EnableUSBReg(void)
{
  /* Enable the USB regulator */
  SET_BIT(PWR->CSR2, PWR_CSR2_USBREGEN);
}

/**
  * @brief Disable the USB Regulator.
  * @retval None.
  */
void HAL_PWREx_DisableUSBReg(void)
{
  /* Disable the USB regulator */
  CLEAR_BIT(PWR->CSR2, PWR_CSR2_USBREGEN);
}

/**
  * @brief Enable the USB voltage level detector.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_PWREx_EnableUSBVoltageDetector(void)
{
  uint32_t tickstart;

  /* Enable the USB voltage detector */
  SET_BIT(PWR->CSR2, PWR_CSR2_USB33DEN);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait till the USB regulator ready flag is set */
  while ((PWR->CSR2 & PWR_CSR2_USB33RDY) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > PWR_FLAG_SETTING_DELAY)
    {
      return HAL_ERROR;
    }
  }
  return HAL_OK;
}

/**
  * @brief Disable the USB voltage level detector.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_PWREx_DisableUSBVoltageDetector(void)
{
  uint32_t tickstart;

  /* Disable the USB voltage detector */
  CLEAR_BIT(PWR->CSR2, PWR_CSR2_USB33DEN);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait till the USB regulator ready flag is reset */
  while ((PWR->CSR2 & PWR_CSR2_USB33RDY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > PWR_FLAG_SETTING_DELAY)
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief Enable the USB HS regulator.
  * @retval None.
  */
void HAL_PWREx_EnableUSBHSregulator(void)
{
  /* Enable the USB HS regulator */
  SET_BIT(PWR->CSR2, PWR_CSR2_USBHSREGEN);
}

/**
  * @brief Disable the USB HS regulator.
  * @retval None.
  */
void HAL_PWREx_DisableUSBHSregulator(void)
{
  /* Disable the USB HS regulator */
  CLEAR_BIT(PWR->CSR2, PWR_CSR2_USBHSREGEN);
}

/**
  * @brief Enable UCPD configuration memorization in Standby.
  * @retval None
  * @note  This function must be called just before entering Standby mode when using UCPD.
  */
void HAL_PWREx_EnableUCPDStandbyMode(void)
{
  /* Memorize UCPD configuration when entering standby mode */
  SET_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STBY);
}

/**
  * @brief Disable UCPD configuration memorization in Standby.
  * @note  This function must be called on exiting the Standby mode and before any UCPD
  *        configuration update.
  * @retval None
  */
void HAL_PWREx_DisableUCPDStandbyMode(void)
{
  CLEAR_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STBY);
}

/**
  * @brief Enable dead battery behavior.
  * @retval None
  */
void HAL_PWREx_EnableUCPDDeadBattery(void)
{
  /* Enable dead battery behavior */
  CLEAR_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS);
}

/**
  * @brief Disable dead battery behavior.
  * @retval None
  */
void HAL_PWREx_DisableUCPDDeadBattery(void)
{
  /* Disable dead battery behavior */
  SET_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS);
}

/**
  * @brief Enable the Battery charging.
  * @note   When VDD is present, charge the external battery through an internal
  *         resistor.
  *         It is automatically disabled in VBAT mode.
  * @param  ResistorValue : Specifies the charging resistor.
  *          This parameter can be one of the following values :
  *            @arg PWR_BATTERY_CHARGING_RESISTOR_5   : 5 KOhm resistor.
  *            @arg PWR_BATTERY_CHARGING_RESISTOR_1_5 : 1.5 KOhm resistor.
  * @retval None.
  */
void HAL_PWREx_EnableBatteryCharging(uint32_t ResistorValue)
{
  /* Check the parameter */
  assert_param(IS_PWR_BATTERY_RESISTOR_SELECT(ResistorValue));

  /* Specify the charging resistor and enable the Battery charging */
  MODIFY_REG(PWR->CSR2, (PWR_CSR2_VBRS | PWR_CSR2_VBE), (ResistorValue | PWR_CSR2_VBE));

}

/**
  * @brief Disable the Battery charging.
  * @retval None.
  */
void HAL_PWREx_DisableBatteryCharging(void)
{
  /* Disable the Battery charging and restore default charging resistor value */
  CLEAR_BIT(PWR->CSR2, (PWR_CSR2_VBE | PWR_CSR2_VBRS));
}

/**
  * @brief Enable the booster to guarantee the analog switch AC performance when
  *        the VDD supply voltage is below 2V7.
  * @note   The VDD supply voltage can be monitored through the PVD and the PLS
  *         field bits.
  * @retval None.
  */
void HAL_PWREx_EnableAnalogBooster(void)
{
  /* Enable the Analog voltage */
  SET_BIT(PWR->CR1, PWR_CR1_AVDREADY);

  /* Enable VDDA booster */
  SET_BIT(PWR->CR1, PWR_CR1_BOOSTE);
}

/**
  * @brief Disable the analog booster.
  * @retval None.
  */
void HAL_PWREx_DisableAnalogBooster(void)
{
  /* Disable VDDA booster */
  CLEAR_BIT(PWR->CR1, PWR_CR1_BOOSTE);

  /* Disable the Analog voltage */
  CLEAR_BIT(PWR->CR1, PWR_CR1_AVDREADY);
}

/**
  * @brief  Enable the XSPIM_P1 interface.
  * @note   The XSPIM_P1 supply must be stable prior to setting
            this bit.
  * @retval None.
  */
void HAL_PWREx_EnableXSPIM1(void)
{
  SET_BIT(PWR->CSR2, PWR_CSR2_EN_XSPIM1);
}

/**
  * @brief Disable the XSPIM_P1 interface.
  * @retval None.
  */
void HAL_PWREx_DisableXSPIM1(void)
{
  CLEAR_BIT(PWR->CSR2, PWR_CSR2_EN_XSPIM1);
}

/**
  * @brief  Enable the XSPIM_P2 interface.
  * @note   The XSPIM_P2 supply must be stable prior to setting
            this bit.
  * @retval None.
  */
void HAL_PWREx_EnableXSPIM2(void)
{
  SET_BIT(PWR->CSR2, PWR_CSR2_EN_XSPIM2);
}

/**
  * @brief Disable the XSPIM_P2 interface.
  * @retval None.
  */
void HAL_PWREx_DisableXSPIM2(void)
{
  CLEAR_BIT(PWR->CSR2, PWR_CSR2_EN_XSPIM2);
}

/**
  * @brief  Configure the capacitor port
  * @param  PortCapacitor Select the Port
  *         This parameter can be one of the following values:
  *           @arg @ref PWR_CAPACITOR_PORT1    XSPI port 1 capacitor
  *           @arg @ref PWR_CAPACITOR_PORT2    XSPI port 2 capacitor
  * @param  PortCapacitorSetting Select the capacitor setting
  *         This parameter can be one of the following values:
  *           @arg @ref PWR_CAPACITOR_OFF                     XSPI Capacitor OFF
  *           @arg @ref PWR_CAPACITOR_ONE_THIRD_CAPACITANCE   XSPI Capacitor set to 1/3
  *           @arg @ref PWR_CAPACITOR_TWO_THIRD_CAPACITANCE   XSPI Capacitor set to 2/3
  *           @arg @ref PWR_CAPACITOR_FULL_CAPACITANCE        XSPI Capacitor set to full capacitance
  * @retval None.
  */
void HAL_PWREx_ConfigXSPIPortCap(uint32_t PortCapacitor, uint32_t PortCapacitorSetting)
{
  /* Check the parameters */
  assert_param(IS_PWR_CAPACITOR(PortCapacitor));
  assert_param(IS_PWR_CAPACITOR_SETTING(PortCapacitorSetting));

  if (PortCapacitor == PWR_CAPACITOR_PORT1)
  {
    /* Set Port1 Capacitor setting */
    MODIFY_REG(PWR->CSR2, PWR_CSR2_XSPICAP1, PortCapacitorSetting);
  }
  else
  {
    /* Set Port2 Capacitor setting */
    MODIFY_REG(PWR->CSR2, PWR_CSR2_XSPICAP2, PortCapacitorSetting << (PWR_CSR2_XSPICAP2_Pos - PWR_CSR2_XSPICAP1_Pos));
  }
}

/**
  * @brief  Get the capacitor port setting
  * @param  PortCapacitor Select the Port
  *         This parameter can be one of the following values:
  *           @arg @ref PWR_CAPACITOR_PORT1    XSPI port 1 capacitor
  *           @arg @ref PWR_CAPACITOR_PORT2    XSPI port 2 capacitor
  * @retval The capacitor setting:
  *           @arg @ref PWR_CAPACITOR_OFF                     XSPI Capacitor OFF
  *           @arg @ref PWR_CAPACITOR_ONE_THIRD_CAPACITANCE   XSPI Capacitor set to 1/3
  *           @arg @ref PWR_CAPACITOR_TWO_THIRD_CAPACITANCE   XSPI Capacitor set to 2/3
  *           @arg @ref PWR_CAPACITOR_FULL_CAPACITANCE        XSPI Capacitor set to full capacitance
  */
uint32_t HAL_PWREx_GetConfigXSPIPortCap(uint32_t PortCapacitor)
{
  uint32_t PortCapacitorSetting;

  /* Check the parameter */
  assert_param(IS_PWR_CAPACITOR(PortCapacitor));

  if (PortCapacitor == PWR_CAPACITOR_PORT1)
  {
    /* Get Port1 Capacitor setting */
    PortCapacitorSetting = READ_BIT(PWR->CSR2, PWR_CSR2_XSPICAP1);
  }
  else
  {
    /* Get Port2 Capacitor setting */
    PortCapacitorSetting = (READ_BIT(PWR->CSR2, PWR_CSR2_XSPICAP2) >> (PWR_CSR2_XSPICAP2_Pos - PWR_CSR2_XSPICAP1_Pos));
  }

  return PortCapacitorSetting;
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
      (+) The VBAT battery voltage supply can be monitored by comparing it with
          two threshold levels: VBAThigh and VBATlow. VBATH flag and VBATL flags
          in the PWR control register 2 (PWR_CR2), indicate if VBAT is higher or
          lower than the threshold.
      (+) The temperature can be monitored by comparing it with two threshold
          levels, TEMPhigh and TEMPlow. TEMPH and TEMPL flags, in the PWR
          control register 2 (PWR_CR2), indicate whether the device temperature
          is higher or lower than the threshold.
      (+) The VBAT and the temperature monitoring is enabled by
          HAL_PWREx_EnableMonitoring() function and disabled by
          HAL_PWREx_DisableMonitoring() function.
      (+) The HAL_PWREx_GetVBATLevel() function returns the VBAT level which can
          be : PWR_VBAT_BELOW_LOW_THRESHOLD or PWR_VBAT_ABOVE_HIGH_THRESHOLD or
          PWR_VBAT_BETWEEN_HIGH_LOW_THRESHOLD.
      (+) The HAL_PWREx_GetTemperatureLevel() function returns the Temperature
          level which can be :
          PWR_TEMP_BELOW_LOW_THRESHOLD or PWR_TEMP_ABOVE_HIGH_THRESHOLD or
          PWR_TEMP_BETWEEN_HIGH_LOW_THRESHOLD.

    *** AVD configuration ***
    =========================
    [..]
      (+) The AVD is used to monitor the VDDA power supply by comparing it to a
          threshold selected by the AVD Level (ALS[3:0] bits in the PWR_CR1
          register).
      (+) A AVDO flag is available to indicate if VDDA is higher or lower
          than the AVD threshold. This event is internally connected to the EXTI
          line 16 to generate an interrupt if enabled.
          It is configurable through __HAL_PWR_AVD_EXTI_ENABLE_IT() macro.
      (+) The AVD is stopped in System Standby mode.

@endverbatim
  * @{
  */

/**
  * @brief Enable the VBAT and temperature monitoring.
  * @retval HAL status.
  */
void HAL_PWREx_EnableMonitoring(void)
{
  /* Enable the VBAT and Temperature monitoring */
  SET_BIT(PWR->CSR1, PWR_CSR1_MONEN);
}

/**
  * @brief Disable the VBAT and temperature monitoring.
  * @retval HAL status.
  */
void HAL_PWREx_DisableMonitoring(void)
{
  /* Disable the VBAT and Temperature monitoring */
  CLEAR_BIT(PWR->CSR1, PWR_CSR1_MONEN);
}

/**
  * @brief Indicate whether the junction temperature is between, above or below
  *        the thresholds.
  * @retval Temperature level.
  */
uint32_t HAL_PWREx_GetTemperatureLevel(void)
{
  uint32_t tempLevel;
  uint32_t regValue;

  /* Read the temperature flags */
  regValue = READ_BIT(PWR->CSR1, (PWR_CSR1_TEMPH | PWR_CSR1_TEMPL));

  /* Check if the temperature is below the threshold */
  if (regValue == PWR_CSR1_TEMPL)
  {
    tempLevel = PWR_TEMP_BELOW_LOW_THRESHOLD;
  }
  /* Check if the temperature is above the threshold */
  else if (regValue == PWR_CSR1_TEMPH)
  {
    tempLevel = PWR_TEMP_ABOVE_HIGH_THRESHOLD;
  }
  /* The temperature is between the thresholds */
  else
  {
    tempLevel = PWR_TEMP_BETWEEN_HIGH_LOW_THRESHOLD;
  }

  return tempLevel;
}

/**
  * @brief Indicate whether the Battery voltage level is between, above or below
  *        the thresholds.
  * @retval VBAT level.
  */
uint32_t HAL_PWREx_GetVBATLevel(void)
{
  uint32_t vbatLevel;
  uint32_t regValue;

  /* Read the VBAT flags */
  regValue = READ_BIT(PWR->CSR1, (PWR_CSR1_VBATH | PWR_CSR1_VBATL));

  /* Check if the VBAT is below the threshold */
  if (regValue == PWR_CSR1_VBATL)
  {
    vbatLevel = PWR_VBAT_BELOW_LOW_THRESHOLD;
  }
  /* Check if the VBAT is above the threshold */
  else if (regValue == PWR_CSR1_VBATH)
  {
    vbatLevel = PWR_VBAT_ABOVE_HIGH_THRESHOLD;
  }
  /* The VBAT is between the thresholds */
  else
  {
    vbatLevel = PWR_VBAT_BETWEEN_HIGH_LOW_THRESHOLD;
  }

  return vbatLevel;
}

/**
  * @brief  Configure the event mode and the voltage threshold detected by the
  *         Analog Voltage Detector (AVD).
  * @param  sConfigAVD : Pointer to an PWREx_AVDTypeDef structure that contains
  *                      the configuration information for the AVD.
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each
  *         detection level.
  * @note   As PVD and AVD share the same EXTI line, the EXTI operating mode to
  *         configure will replace a possible previous configuration done through
  *         HAL_PWR_ConfigPVD.
  * @retval None.
  */
void HAL_PWREx_ConfigAVD(const PWREx_AVDTypeDef *sConfigAVD)
{
  /* Check the parameters */
  assert_param(IS_PWR_AVD_LEVEL(sConfigAVD->AVDLevel));
  assert_param(IS_PWR_AVD_MODE(sConfigAVD->Mode));

  /* Set the ALS[18:17] bits according to AVDLevel value */
  MODIFY_REG(PWR->CR1, PWR_CR1_ALS, sConfigAVD->AVDLevel);

  /* Clear any previous config */
  __HAL_PWR_AVD_EXTI_DISABLE_EVENT();
  __HAL_PWR_AVD_EXTI_DISABLE_IT();

  __HAL_PWR_AVD_EXTI_DISABLE_RISING_EDGE();
  __HAL_PWR_AVD_EXTI_DISABLE_FALLING_EDGE();

  /* Configure the interrupt mode */
  if ((sConfigAVD->Mode & AVD_MODE_IT) == AVD_MODE_IT)
  {
    __HAL_PWR_AVD_EXTI_ENABLE_IT();
  }

  /* Configure the event mode */
  if ((sConfigAVD->Mode & AVD_MODE_EVT) == AVD_MODE_EVT)
  {
    __HAL_PWR_AVD_EXTI_ENABLE_EVENT();
  }

  /* Rising edge configuration */
  if ((sConfigAVD->Mode & AVD_RISING_EDGE) == AVD_RISING_EDGE)
  {
    __HAL_PWR_AVD_EXTI_ENABLE_RISING_EDGE();
  }

  /* Falling edge configuration */
  if ((sConfigAVD->Mode & AVD_FALLING_EDGE) == AVD_FALLING_EDGE)
  {
    __HAL_PWR_AVD_EXTI_ENABLE_FALLING_EDGE();
  }
}

/**
  * @brief Enable the Analog Voltage Detector (AVD).
  * @retval None.
  */
void HAL_PWREx_EnableAVD(void)
{
  /* Enable the Analog Voltage Detector */
  SET_BIT(PWR->CR1, PWR_CR1_AVDEN);
}

/**
  * @brief Disable the Analog Voltage Detector(AVD).
  * @retval None.
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
  /* Check PWR EXTI flags for PVD/AVD */
  if (((EXTI->PR1) & EXTI_PR1_PR16) != 0U)
  {
    /* Clear PVD/AVD exti pending bit */
    WRITE_REG(EXTI->PR1, EXTI_PR1_PR16);

    /* PWR PVD/AVD interrupt user callback */
    HAL_PWREx_PVD_AVD_Callback();
  }
}

/**
  * @brief  PWR PVD/AVD interrupt callback.
  * @retval None.
  */
__weak void HAL_PWREx_PVD_AVD_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_PWREx_PVD_AVD_Callback can be implemented in the user file
  */
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
      In Standby mode, pull up and pull down can be configured to
      maintain an I/O in the selected state. If the APC bit in the PWR_APCR
      register is set, the I/Os can be configured either with a pull-up through
      PWR_PUCRx registers (x=N,O), or with a pull-down through
      PWR_PDCRx registers (x=N,O,P), or can be kept in analog state
      if none of the PWR_PUCRx or PWR_PDCRx register is set.

    [..]
      The pull-down configuration has highest priority over pull-up
      configuration in case both PWR_PUCRx and PWR_PDCRx are set for the same
      I/O.

@endverbatim
  * @{
  */

/**
  * @brief  Enable pull-up and pull-down configuration.
  * @note   When APC bit is set, the I/O pull-up and pull-down configurations
  *         defined in PWR_PUCRx and PWR_PDCRx registers are applied in Standby
  *         mode.
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
  *         Standby mode.
  * @retval None.
  */
void HAL_PWREx_DisablePullUpPullDownConfig(void)
{
  CLEAR_BIT(PWR->APCR, PWR_APCR_APC);
}

/**
  * @brief  Enable GPIO pull-up state in Standby mode.
  * @note   Set the relevant PUy bits of PWR_PUCRx register to configure the I/O in
  *         pull-up state in Standby mode.
  * @note   This state is effective in Standby mode only if APC bit
  *         is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note   The configuration is maintained when exiting the Standby mode.
  * @note   Even if a PUy bit to set is reserved, the other PUy bits entered as
  *         input parameter at the same time are set.
  * @note   The pullup is not activated if the corresponding PDy bit is also set.
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of @ref PWREx_GPIO_PullUp_Port.
  * @param  GPIO_Pin  : Specify the I/O pins numbers.
  *                     This parameter can be a combination of @ref PWREx_GPIO_PullUp_Pin_Mask.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PULLPUP_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  switch (GPIO_Port)
  {
    case PWR_GPIO_PULLUP_PORT_N:
      SET_BIT(PWR->PUCRN, GPIO_Pin);
      break;

    case PWR_GPIO_PULLUP_PORT_O:
      SET_BIT(PWR->PUCRO, GPIO_Pin);
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief  Disable GPIO pull-up state in Standby mode.
  * @note   Reset the relevant PUy bits of PWR_PUCRx register used to configure the I/O
  *         in pull-up state in Standby mode.
  * @note  Even if a PUy bit to reset is reserved, the other PUy bits entered as input
  *        parameter at the same time are reset.
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of @ref PWREx_GPIO_PullUp_Port.
  * @param  GPIO_Pin  : Specify the I/O pins numbers.
  *                     This parameter can be a combination of @ref PWREx_GPIO_PullUp_Pin_Mask.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PULLPUP_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  switch (GPIO_Port)
  {
    case PWR_GPIO_PULLUP_PORT_N:
      CLEAR_BIT(PWR->PUCRN, GPIO_Pin);
      break;

    case PWR_GPIO_PULLUP_PORT_O:
      CLEAR_BIT(PWR->PUCRO, GPIO_Pin);
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief Enable GPIO pull-down state in Standby mode.
  * @note  Set the relevant PDy bits of PWR_PDCRx register to configure the I/O in
  *        pull-down state in Standby mode.
  * @note  This state is effective in Standby mode only if APC bit
  *        is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note  The configuration is maintained when exiting the Standby mode.
  * @note  Even if a PDy bit to set is reserved, the other PDy bits entered as input
  *        parameter at the same time are set.
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of @ref PWREx_GPIO_PullDown_Port.
  * @param  GPIO_Pin  : Specify the I/O pins numbers.
  *                     This parameter can be a combination of @ref PWREx_GPIO_PullDown_Pin_Mask.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PULLDOWN_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  switch (GPIO_Port)
  {
    case PWR_GPIO_PULLDOWN_PORT_N:
      SET_BIT(PWR->PDCRN, GPIO_Pin);
      break;

    case PWR_GPIO_PULLDOWN_PORT_O:
      SET_BIT(PWR->PDCRO, GPIO_Pin);
      break;

    case PWR_GPIO_PULLDOWN_PORT_P:
      SET_BIT(PWR->PDCRP, GPIO_Pin);
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief Disable GPIO pull-down state in Standby mode.
  * @note  Reset the relevant PDy bits of PWR_PDCRx register used to configure the I/O
  *        in pull-down state in Standby mode.
  * @note  Even if a PDy bit to reset is reserved, the other PDy bits entered as input
  *        parameter at the same time are reset.
  * @param  GPIO_Port : Specify the IO port.
  *                     This parameter can be a value of @ref PWREx_GPIO_PullDown_Port.
  * @param  GPIO_Pin  : Specify the I/O pins numbers.
  *                     This parameter can be a value of @ref PWREx_GPIO_PullDown_Pin_Mask.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO_Port, uint32_t GPIO_Pin)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_PWR_GPIO_PULLDOWN_PORT(GPIO_Port));
  assert_param(IS_PWR_GPIO_PIN_MASK(GPIO_Pin));

  switch (GPIO_Port)
  {
    case PWR_GPIO_PULLDOWN_PORT_N:
      CLEAR_BIT(PWR->PDCRN, GPIO_Pin);
      break;

    case PWR_GPIO_PULLDOWN_PORT_O:
      CLEAR_BIT(PWR->PDCRO, GPIO_Pin);
      break;

    case PWR_GPIO_PULLDOWN_PORT_P:
      CLEAR_BIT(PWR->PDCRP, GPIO_Pin);
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
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

