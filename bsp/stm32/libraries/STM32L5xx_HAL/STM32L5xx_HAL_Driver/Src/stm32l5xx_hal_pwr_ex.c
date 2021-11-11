/**
  ******************************************************************************
  * @file    stm32l5xx_hal_pwr_ex.c
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
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "stm32l5xx_hal.h"

/** @addtogroup STM32L5xx_HAL_Driver
  * @{
  */

/** @defgroup PWREx PWREx
  * @brief PWR Extended HAL module driver
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup PWR_Extended_Private_Defines PWR Extended Private Defines
  * @{
  */

#define PWR_PORTH_AVAILABLE_PINS  ((uint32_t)0x0000000B)  /* PH0/PH1/PH3 */

/** @defgroup PWREx_PVM_Mode_Mask PWR PVM Mode Mask
  * @{
  */
#define PVM_MODE_IT               ((uint32_t)0x00010000)  /*!< Mask for interruption yielded by PVM threshold crossing */
#define PVM_MODE_EVT              ((uint32_t)0x00020000)  /*!< Mask for event yielded by PVM threshold crossing        */
#define PVM_RISING_EDGE           ((uint32_t)0x00000001)  /*!< Mask for rising edge set as PVM trigger                 */
#define PVM_FALLING_EDGE          ((uint32_t)0x00000002)  /*!< Mask for falling edge set as PVM trigger                */
/**
  * @}
  */

/** @defgroup PWREx_TimeOut_Value PWR Extended Flag Setting Time Out Value
  * @{
  */
#define PWR_REGLP_SETTING_DELAY_VALUE            300UL   /*!< Time out value for REGLPF flag setting */

#define PWR_VOSF_SETTING_DELAY_VALUE              50UL   /*!< Time out value for VOSF flag setting */

#define PWR_MODE_CHANGE_DELAY_VALUE             1000UL   /*!< Time out for step down converter operating mode */

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

/** @defgroup PWREx_Exported_Functions_Group1 Extended Peripheral Control functions
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
  * @retval VOS bit field (PWR_REGULATOR_VOLTAGE_SCALE0, PWR_REGULATOR_VOLTAGE_SCALE1 or PWR_REGULATOR_VOLTAGE_SCALE2)
  */
uint32_t HAL_PWREx_GetVoltageRange(void)
{
  return (PWR->CR1 & PWR_CR1_VOS);
}

/**
  * @brief Configure the main internal regulator output voltage.
  * @param  VoltageScaling specifies the regulator output voltage to achieve
  *         a tradeoff between performance and power consumption.
  *          This parameter can be one of the following values:
  *            @arg @ref PWR_REGULATOR_VOLTAGE_SCALE0 Regulator voltage output range 0 mode,
  *                                                typical output voltage at 1.28 V,
  *                                                system frequency up to 100 MHz.
  *            @arg @ref PWR_REGULATOR_VOLTAGE_SCALE1 Regulator voltage output range 1 mode,
  *                                                typical output voltage at 1.2 V,
  *                                                system frequency up to 80 MHz.
  *            @arg @ref PWR_REGULATOR_VOLTAGE_SCALE2 Regulator voltage output range 2 mode,
  *                                                typical output voltage at 1.0 V,
  *                                                system frequency up to 26 MHz.
  * @note  When moving from Range 1 to Range 2, the system frequency must be decreased to
  *        a value below 26 MHz before calling HAL_PWREx_ControlVoltageScaling() API.
  *        When moving from Range 2 to Range 1, the system frequency can be increased to
  *        a value up to 80 MHz after calling HAL_PWREx_ControlVoltageScaling() API.
  * @note  When moving from one Range to another , the API waits for VOSF flag to be
  *        cleared before returning the status. If the flag is not cleared within limited time duration,
  *        HAL_TIMEOUT status is reported.
  * @note  The VOS shall NOT be changed in LP Mode of if LP mode is asked.
  * @note  The function shall not be called in Low-power run mode (meaningless and misleading).
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling)
{
  uint32_t wait_loop_index;

  assert_param(IS_PWR_VOLTAGE_SCALING_RANGE(VoltageScaling));

  uint32_t vos_old = READ_BIT(PWR->CR1, PWR_CR1_VOS);

  /* VOS shall not be changed in LP Mode            */
  /* or if LP Mode is asked but not yet established */
  if (HAL_PWREx_SMPS_GetEffectiveMode() == PWR_SMPS_LOW_POWER)
  {
    return HAL_ERROR;
  }
  if (READ_BIT(PWR->CR4, PWR_CR4_SMPSLPEN) == PWR_CR4_SMPSLPEN)
  {
    return HAL_ERROR;
  }

  /* No change, nothing to do */
  if (vos_old == VoltageScaling)
  {
    return HAL_OK;
  }

  MODIFY_REG(PWR->CR1, PWR_CR1_VOS, VoltageScaling);

  /* Wait until VOSF is cleared */
  /* and at least one iteration loop */
  wait_loop_index = ((PWR_VOSF_SETTING_DELAY_VALUE * (SystemCoreClock / 100000U)) / 10U) + 1U;

  while ((HAL_IS_BIT_SET(PWR->SR2, PWR_SR2_VOSF)) && (wait_loop_index != 0U))
  {
    wait_loop_index--;
  }

  if (HAL_IS_BIT_SET(PWR->SR2, PWR_SR2_VOSF))
  {
    return HAL_TIMEOUT;
  }

  return HAL_OK;
}

/**
  * @brief Enable battery charging.
  *        When VDD is present, charge the external battery on VBAT through an internal resistor.
  * @param  ResistorSelection specifies the resistor impedance.
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


#if defined(PWR_CR2_USV)
/**
  * @brief Enable VDDUSB supply.
  * @note  Remove VDDUSB electrical and logical isolation, once VDDUSB supply is present.
  * @retval None
  */
void HAL_PWREx_EnableVddUSB(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_USV);
}


/**
  * @brief Disable VDDUSB supply.
  * @retval None
  */
void HAL_PWREx_DisableVddUSB(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_USV);
}
#endif /* PWR_CR2_USV */

/**
  * @brief Enable VDDIO2 supply.
  * @note  Remove VDDIO2 electrical and logical isolation, once VDDIO2 supply is present.
  * @retval None
  */
void HAL_PWREx_EnableVddIO2(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_IOSV);
}

/**
  * @brief Disable VDDIO2 supply.
  * @retval None
  */
void HAL_PWREx_DisableVddIO2(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_IOSV);
}

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
  * @param  GPIO specifies the IO port. This parameter can be PWR_GPIO_A, ..., PWR_GPIO_H
  *         (or PWR_GPIO_I depending on the devices) to select the GPIO peripheral.
  * @param  GPIONumber specifies the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for the port where less
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
      SET_BIT(PWR->PUCRA, (GPIONumber & (~(PWR_GPIO_BIT_14))));
      CLEAR_BIT(PWR->PDCRA, (GPIONumber & (~(PWR_GPIO_BIT_13 | PWR_GPIO_BIT_15))));
      break;
    case PWR_GPIO_B:
      SET_BIT(PWR->PUCRB, GPIONumber);
      CLEAR_BIT(PWR->PDCRB, (GPIONumber & (~(PWR_GPIO_BIT_4))));
      break;
    case PWR_GPIO_C:
      SET_BIT(PWR->PUCRC, GPIONumber);
      CLEAR_BIT(PWR->PDCRC, GPIONumber);
      break;
    case PWR_GPIO_D:
      SET_BIT(PWR->PUCRD, GPIONumber);
      CLEAR_BIT(PWR->PDCRD, GPIONumber);
      break;
    case PWR_GPIO_E:
      SET_BIT(PWR->PUCRE, GPIONumber);
      CLEAR_BIT(PWR->PDCRE, GPIONumber);
      break;
    case PWR_GPIO_F:
      SET_BIT(PWR->PUCRF, GPIONumber);
      CLEAR_BIT(PWR->PDCRF, GPIONumber);
      break;
    case PWR_GPIO_G:
      SET_BIT(PWR->PUCRG, GPIONumber);
      CLEAR_BIT(PWR->PDCRG, GPIONumber);
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
  * @param  GPIO specifies the IO port. This parameter can be PWR_GPIO_A, ..., PWR_GPIO_H
  *          (or PWR_GPIO_I depending on the devices) to select the GPIO peripheral.
  * @param  GPIONumber specifies the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for the port where less
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
      CLEAR_BIT(PWR->PUCRA, (GPIONumber & (~(PWR_GPIO_BIT_14))));
      break;
    case PWR_GPIO_B:
      CLEAR_BIT(PWR->PUCRB, GPIONumber);
      break;
    case PWR_GPIO_C:
      CLEAR_BIT(PWR->PUCRC, GPIONumber);
      break;
    case PWR_GPIO_D:
      CLEAR_BIT(PWR->PUCRD, GPIONumber);
      break;
    case PWR_GPIO_E:
      CLEAR_BIT(PWR->PUCRE, GPIONumber);
      break;
    case PWR_GPIO_F:
      CLEAR_BIT(PWR->PUCRF, GPIONumber);
      break;
    case PWR_GPIO_G:
      CLEAR_BIT(PWR->PUCRG, GPIONumber);
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
  * @param  GPIO specifies the IO port. This parameter can be PWR_GPIO_A..PWR_GPIO_H
  *         (or PWR_GPIO_I depending on the devices) to select the GPIO peripheral.
  * @param  GPIONumber specifies the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for the port where less
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
      SET_BIT(PWR->PDCRA, (GPIONumber & (~(PWR_GPIO_BIT_13 | PWR_GPIO_BIT_15))));
      CLEAR_BIT(PWR->PUCRA, (GPIONumber & (~(PWR_GPIO_BIT_14))));
      break;
    case PWR_GPIO_B:
      SET_BIT(PWR->PDCRB, (GPIONumber & (~(PWR_GPIO_BIT_4))));
      CLEAR_BIT(PWR->PUCRB, GPIONumber);
      break;
    case PWR_GPIO_C:
      SET_BIT(PWR->PDCRC, GPIONumber);
      CLEAR_BIT(PWR->PUCRC, GPIONumber);
      break;
    case PWR_GPIO_D:
      SET_BIT(PWR->PDCRD, GPIONumber);
      CLEAR_BIT(PWR->PUCRD, GPIONumber);
      break;
    case PWR_GPIO_E:
      SET_BIT(PWR->PDCRE, GPIONumber);
      CLEAR_BIT(PWR->PUCRE, GPIONumber);
      break;
    case PWR_GPIO_F:
      SET_BIT(PWR->PDCRF, GPIONumber);
      CLEAR_BIT(PWR->PUCRF, GPIONumber);
      break;
    case PWR_GPIO_G:
      SET_BIT(PWR->PDCRG, GPIONumber);
      CLEAR_BIT(PWR->PUCRG, GPIONumber);
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
  * @param  GPIO specifies the IO port. This parameter can be PWR_GPIO_A..PWR_GPIO_H
  *         (or PWR_GPIO_I depending on the devices) to select the GPIO peripheral.
  * @param  GPIONumber specifies the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for the port where less
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
      CLEAR_BIT(PWR->PDCRA, (GPIONumber & (~(PWR_GPIO_BIT_13 | PWR_GPIO_BIT_15))));
      break;
    case PWR_GPIO_B:
      CLEAR_BIT(PWR->PDCRB, (GPIONumber & (~(PWR_GPIO_BIT_4))));
      break;
    case PWR_GPIO_C:
      CLEAR_BIT(PWR->PDCRC, GPIONumber);
      break;
    case PWR_GPIO_D:
      CLEAR_BIT(PWR->PDCRD, GPIONumber);
      break;
    case PWR_GPIO_E:
      CLEAR_BIT(PWR->PDCRE, GPIONumber);
      break;
    case PWR_GPIO_F:
      CLEAR_BIT(PWR->PDCRF, GPIONumber);
      break;
    case PWR_GPIO_G:
      CLEAR_BIT(PWR->PDCRG, GPIONumber);
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
  SET_BIT(PWR->CR3, PWR_CR3_APC);
}


/**
  * @brief Disable pull-up and pull-down configuration.
  * @note  When APC bit is cleared, the I/O pull-up and pull-down configurations defined in
  *        PWR_PUCRx and PWR_PDCRx registers are not applied in Standby and Shutdown modes.
  * @retval None
  */
void HAL_PWREx_DisablePullUpPullDownConfig(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_APC);
}


/**
  * @brief Configure SRAM2 content retention in Standby mode.
  * @param  SRAM2ContentRetention  This parameter can be one of the following values:
  *         @arg @ref PWR_NO_SRAM2_RETENTION
  *         @arg @ref PWR_FULL_SRAM2_RETENTION
  *         @arg @ref PWR_4KBYTES_SRAM2_RETENTION
  * @note  This feature is secured by SMLPM bit when system implements security (TZEN=1).
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_ConfigSRAM2ContentRetention(uint32_t SRAM2ContentRetention)
{
  /* Check the parameters */
  assert_param(IS_PWR_SRAM2CONTENT_RETENTION(SRAM2ContentRetention));

  /* Set RRS bits */
  MODIFY_REG(PWR->CR3, PWR_CR3_RRS, SRAM2ContentRetention);

  return HAL_OK;
}


/**
  * @brief Enable SRAM2 content retention in Standby mode.
  * @note  When RRS bit is set, SRAM2 is powered by the low-power regulator in
  *         Standby mode and its content is kept.
  * @retval None
  */
void HAL_PWREx_EnableSRAM2ContentRetention(void)
{
  (void) HAL_PWREx_ConfigSRAM2ContentRetention(PWR_FULL_SRAM2_RETENTION);
}


/**
  * @brief Disable SRAM2 content retention in Standby mode.
  * @note  When RRS bit is reset, SRAM2 is powered off in Standby mode
  *        and its content is lost.
  * @retval None
  */
void HAL_PWREx_DisableSRAM2ContentRetention(void)
{
  (void) HAL_PWREx_ConfigSRAM2ContentRetention(PWR_NO_SRAM2_RETENTION);
}


/**
  * @brief Enable the Power Voltage Monitoring 1: VDDUSB versus 1.2 V.
  * @retval None
  */
void HAL_PWREx_EnablePVM1(void)
{
  SET_BIT(PWR->CR2, PWR_PVM_1);
}

/**
  * @brief Disable the Power Voltage Monitoring 1: VDDUSB versus 1.2 V.
  * @retval None
  */
void HAL_PWREx_DisablePVM1(void)
{
  CLEAR_BIT(PWR->CR2, PWR_PVM_1);
}

/**
  * @brief Enable the Power Voltage Monitoring 2: VDDIO2 versus 0.9 V.
  * @retval None
  */
void HAL_PWREx_EnablePVM2(void)
{
  SET_BIT(PWR->CR2, PWR_PVM_2);
}

/**
  * @brief Disable the Power Voltage Monitoring 2: VDDIO2 versus 0.9 V.
  * @retval None
  */
void HAL_PWREx_DisablePVM2(void)
{
  CLEAR_BIT(PWR->CR2, PWR_PVM_2);
}


/**
  * @brief Enable the Power Voltage Monitoring 3: VDDA versus 1.62 V.
  * @retval None
  */
void HAL_PWREx_EnablePVM3(void)
{
  SET_BIT(PWR->CR2, PWR_PVM_3);
}

/**
  * @brief Disable the Power Voltage Monitoring 3: VDDA versus 1.62 V.
  * @retval None
  */
void HAL_PWREx_DisablePVM3(void)
{
  CLEAR_BIT(PWR->CR2, PWR_PVM_3);
}


/**
  * @brief Enable the Power Voltage Monitoring 4:  VDDA versus 1.8 V.
  * @retval None
  */
void HAL_PWREx_EnablePVM4(void)
{
  SET_BIT(PWR->CR2, PWR_PVM_4);
}

/**
  * @brief Disable the Power Voltage Monitoring 4:  VDDA versus 1.8 V.
  * @retval None
  */
void HAL_PWREx_DisablePVM4(void)
{
  CLEAR_BIT(PWR->CR2, PWR_PVM_4);
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


  /* Configure EXTI 35 to 38 interrupts if so required:
     scan through PVMType to detect which PVMx is set and
     configure the corresponding EXTI line accordingly. */
  switch (sConfigPVM->PVMType)
  {
    case PWR_PVM_1:
      /* Clear any previous config. Keep it clear if no event or IT mode is selected */
      __HAL_PWR_PVM1_EXTI_DISABLE_EVENT();
      __HAL_PWR_PVM1_EXTI_DISABLE_IT();
      __HAL_PWR_PVM1_EXTI_DISABLE_FALLING_EDGE();
      __HAL_PWR_PVM1_EXTI_DISABLE_RISING_EDGE();

      /* Configure interrupt mode */
      if ((sConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_PVM1_EXTI_ENABLE_IT();
      }

      /* Configure event mode */
      if ((sConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_PVM1_EXTI_ENABLE_EVENT();
      }

      /* Configure the edge */
      if ((sConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_PVM1_EXTI_ENABLE_RISING_EDGE();
      }

      if ((sConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_PVM1_EXTI_ENABLE_FALLING_EDGE();
      }
      break;

    case PWR_PVM_2:
      /* Clear any previous config. Keep it clear if no event or IT mode is selected */
      __HAL_PWR_PVM2_EXTI_DISABLE_EVENT();
      __HAL_PWR_PVM2_EXTI_DISABLE_IT();
      __HAL_PWR_PVM2_EXTI_DISABLE_FALLING_EDGE();
      __HAL_PWR_PVM2_EXTI_DISABLE_RISING_EDGE();

      /* Configure interrupt mode */
      if ((sConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_PVM2_EXTI_ENABLE_IT();
      }

      /* Configure event mode */
      if ((sConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_PVM2_EXTI_ENABLE_EVENT();
      }

      /* Configure the edge */
      if ((sConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_PVM2_EXTI_ENABLE_RISING_EDGE();
      }

      if ((sConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_PVM2_EXTI_ENABLE_FALLING_EDGE();
      }
      break;

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

      /* Configure event mode */
      if ((sConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_PVM3_EXTI_ENABLE_EVENT();
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

    case PWR_PVM_4:
      /* Clear any previous config. Keep it clear if no event or IT mode is selected */
      __HAL_PWR_PVM4_EXTI_DISABLE_EVENT();
      __HAL_PWR_PVM4_EXTI_DISABLE_IT();
      __HAL_PWR_PVM4_EXTI_DISABLE_FALLING_EDGE();
      __HAL_PWR_PVM4_EXTI_DISABLE_RISING_EDGE();

      /* Configure interrupt mode */
      if ((sConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_PVM4_EXTI_ENABLE_IT();
      }

      /* Configure event mode */
      if ((sConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_PVM4_EXTI_ENABLE_EVENT();
      }

      /* Configure the edge */
      if ((sConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_PVM4_EXTI_ENABLE_RISING_EDGE();
      }

      if ((sConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_PVM4_EXTI_ENABLE_FALLING_EDGE();
      }
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}



/**
  * @brief Enter Low-power Run mode
  * @note  In Low-power Run mode, all I/O pins keep the same state as in Run mode.
  * @note  When Regulator is set to PWR_LOWPOWERREGULATOR_ON, the user can optionally configure the
  *        Flash in power-down monde in setting the RUN_PD bit in FLASH_ACR register.
  *        Additionally, the clock frequency must be reduced below 2 MHz.
  *        Setting RUN_PD in FLASH_ACR then appropriately reducing the clock frequency must
  *        be done before calling HAL_PWREx_EnableLowPowerRunMode() API.
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
  /* and at least one iteration loop */
  wait_loop_index = ((PWR_REGLP_SETTING_DELAY_VALUE * (SystemCoreClock / 100000U)) / 10U) + 1U;

  while ((HAL_IS_BIT_SET(PWR->SR2, PWR_SR2_REGLPF)) && (wait_loop_index != 0U))
  {
    wait_loop_index--;
  }
  if (HAL_IS_BIT_SET(PWR->SR2, PWR_SR2_REGLPF))
  {
    return HAL_TIMEOUT;
  }

  return HAL_OK;
}


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

  /* Stop 0 mode with Main Regulator */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_CR1_LPMS_STOP0);

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

  /* Stop 1 mode with Low-Power Regulator */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_CR1_LPMS_STOP1);

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

  /* Set Stop mode 2 */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_CR1_LPMS_STOP2);

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
  * @retval None
  */
void HAL_PWREx_EnterSHUTDOWNMode(void)
{

  /* Set Shutdown mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_CR1_LPMS_SHUTDOWN);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM)
  __force_stores();
#endif
  /* Request Wait For Interrupt */
  __WFI();
}




/**
  * @brief This function handles the PWR PVD/PVMx interrupt request.
  * @note This API should be called under the PVD_PVM_IRQHandler().
  * @retval None
  */
void HAL_PWREx_PVD_PVM_IRQHandler(void)
{
  uint32_t  rising_flag;
  uint32_t  falling_flag;

  rising_flag = READ_REG(EXTI->RPR1);
  falling_flag = READ_REG(EXTI->FPR1);

  /* Check PWR exti flags for PVD */
  if (((rising_flag | falling_flag) & PWR_EXTI_LINE_PVD) != 0x0U)
  {
    /* PWR PVD interrupt user callback */
    HAL_PWR_PVDCallback();

    /* Clear PVD exti pending bit */
    WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_PVD);
    WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_PVD);
  }

  /* Next, successively check PVMx exti flags */
  rising_flag = READ_REG(EXTI->RPR2);
  falling_flag = READ_REG(EXTI->FPR2);

  if (((rising_flag | falling_flag) & PWR_EXTI_LINE_PVM1) != 0x0U)
  {
    /* PWR PVM1 interrupt user callback */
    HAL_PWREx_PVM1Callback();

    /* Clear PVM1 exti pending bit */
    WRITE_REG(EXTI->RPR2, PWR_EXTI_LINE_PVM1);
    WRITE_REG(EXTI->FPR2, PWR_EXTI_LINE_PVM1);
  }
  if (((rising_flag | falling_flag) & PWR_EXTI_LINE_PVM2) != 0x0U)
  {
    /* PWR PVM2 interrupt user callback */
    HAL_PWREx_PVM2Callback();

    /* Clear PVM2 exti pending bit */
    WRITE_REG(EXTI->RPR2, PWR_EXTI_LINE_PVM2);
    WRITE_REG(EXTI->FPR2, PWR_EXTI_LINE_PVM2);
  }
  if (((rising_flag | falling_flag) & PWR_EXTI_LINE_PVM3) != 0x0U)
  {
    /* PWR PVM3 interrupt user callback */
    HAL_PWREx_PVM3Callback();

    /* Clear PVM3 exti pending bit */
    WRITE_REG(EXTI->RPR2, PWR_EXTI_LINE_PVM3);
    WRITE_REG(EXTI->FPR2, PWR_EXTI_LINE_PVM3);
  }
  if (((rising_flag | falling_flag) & PWR_EXTI_LINE_PVM4) != 0x0U)
  {
    /* PWR PVM4 interrupt user callback */
    HAL_PWREx_PVM4Callback();

    /* Clear PVM4 exti pending bit */
    WRITE_REG(EXTI->RPR2, PWR_EXTI_LINE_PVM4);
    WRITE_REG(EXTI->FPR2, PWR_EXTI_LINE_PVM4);
  }
}


/**
  * @brief PWR PVM1 interrupt callback
  * @retval None
  */
__weak void HAL_PWREx_PVM1Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWREx_PVM1Callback() API can be implemented in the user file
   */
}

/**
  * @brief PWR PVM2 interrupt callback
  * @retval None
  */
__weak void HAL_PWREx_PVM2Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWREx_PVM2Callback() API can be implemented in the user file
   */
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
  * @brief PWR PVM4 interrupt callback
  * @retval None
  */
__weak void HAL_PWREx_PVM4Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_PWREx_PVM4Callback() API can be implemented in the user file
   */
}

/**
  * @brief Enable UCPD configuration memorization in Standby.
  * @note  This feature is secured by secured UCPD1 when system implements security (TZEN=1).
  * @retval None
  */
void HAL_PWREx_EnableUCPDStandbyMode(void)
{
  /* Memorize UCPD configuration when entering standby mode */
  SET_BIT(PWR->CR3, PWR_CR3_UCPD_STDBY);
}

/**
  * @brief Disable UCPD configuration memorization in Standby.
  * @note  This function must be called on exiting the Standby mode and before any UCPD
  *        configuration update.
  * @note  This feature is secured by secured UCPD1 when system implements security (TZEN=1).
  * @retval None
  */
void HAL_PWREx_DisableUCPDStandbyMode(void)
{
  /* Write 0 immediately after Standby exit when using UCPD,
     and before writing any UCPD registers */
  CLEAR_BIT(PWR->CR3, PWR_CR3_UCPD_STDBY);
}

/**
  * @brief Enable the USB Type-C dead battery pull-down behavior
  *        on UCPDx_CC1 and UCPDx_CC2 pins
  * @note  This feature is secured by secured UCPD1 when system implements security (TZEN=1).
  * @retval None
  */
void HAL_PWREx_EnableUCPDDeadBattery(void)
{
  /* Write 0 to enable the USB Type-C dead battery pull-down behavior */
  CLEAR_BIT(PWR->CR3, PWR_CR3_UCPD_DBDIS);
}

/**
  * @brief Disable the USB Type-C dead battery pull-down behavior
  *        on UCPDx_CC1 and UCPDx_CC2 pins
  * @note  This feature is secured by secured UCPD1 when system implements security (TZEN=1).
  * @note After exiting reset, the USB Type-C dead battery behavior will be enabled,
  *       which may have a pull-down effect on CC1 and CC2 pins.
  *       It is recommended to disable it in all cases, either to stop this pull-down
  *       or to hand over control to the UCPD (which should therefore be
  *       initialized before doing the disable).
  * @retval None
  */
void HAL_PWREx_DisableUCPDDeadBattery(void)
{
  /* Write 1 to disable the USB Type-C dead battery pull-down behavior */
  SET_BIT(PWR->CR3, PWR_CR3_UCPD_DBDIS);
}

/**
  * @brief Enable ultra low power mode.
  *        Enable ultra low power BORL, BORH and PVD in Standby/Shutdown mode.
  * @note  This feature is secured by VDMSEC bit when system implements security (TZEN=1).
  * @retval None
  */
void HAL_PWREx_EnableUltraLowPowerMode(void)
{
  /* Enable ultra low power mode */
  SET_BIT(PWR->CR3, PWR_CR3_ULPMEN);
}

/**
  * @brief Disable ultra low power mode.
  * @note  This feature is secured by VDMSEC bit when system implements security (TZEN=1).
  * @retval None
  */
void HAL_PWREx_DisableUltraLowPowerMode(void)
{
  /* Disable ultra low power mode */
  CLEAR_BIT(PWR->CR3, PWR_CR3_ULPMEN);
}

/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions_Group2 Extended Power Control SMPS functions
 *  @brief  Extended Power Control SMPS functions
 *
@verbatim
 ===============================================================================
             ##### Extended Power Control SMPS functions  #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the
    SMPS mode.

@endverbatim
 * @{
 */

/**
  * @brief Set SMPS step down converter operating mode.
  * @param OperatingMode This parameter can be one of the following values:
  *         @arg @ref PWR_SMPS_HIGH_POWER    SMPS step down converter in high-power mode (default)
  *         @arg @ref PWR_SMPS_LOW_POWER     SMPS step down converter in low-power mode
  *         @arg @ref PWR_SMPS_BYPASS        SMPS step down converter in bypass mode
  * @note The High-power mode achieves the high efficiency at high current load.
  * @note The Low-power mode achieves the high efficiency at low current load.
  * @note The Low-power mode can be enabled only when the main regulator voltage is in range 2 mode.
  *       When Low-power mode is enabled, the voltage scaling must not be modified. This mode can be
  *       only selected when power consumption does not exceed 30 mA.
  * @note When switching from one power mode to another, HAL_PWREx_SMPS_SetMode() waits for the new
  *       mode to be effective within a limited time duration before returning the status HAL_OK
  *       else it returns HAL_TIMEOUT. A request for Low power mode when the voltage regulator is not
  *       in range 2 is rejected with HAL_ERROR.
  * @note The Bypass mode can be enabled or disabled on the fly whatever the selected operation mode.
  * @note The function shall not be called in Low-power run mode (meaningless and misleading).
  * @retval HAL Status
  */

HAL_StatusTypeDef HAL_PWREx_SMPS_SetMode(uint32_t OperatingMode)
{
  HAL_StatusTypeDef status;
  uint32_t pwr_sr1;
  uint32_t wait_loop_index;

  /* Check the parameters */
  assert_param(IS_PWR_SMPS_MODE(OperatingMode));

  if (OperatingMode == PWR_SMPS_HIGH_POWER)
  {
    MODIFY_REG(PWR->CR4, (PWR_CR4_SMPSBYP | PWR_CR4_SMPSLPEN), 0U);
  }
  else if (OperatingMode == PWR_SMPS_LOW_POWER)
  {
    /* ------------------------------------------------------------------------ */
    /* SMPS Low-power mode can only be set in range 2 */
    if (HAL_PWREx_GetVoltageRange() != PWR_REGULATOR_VOLTAGE_SCALE2)
    {
      return HAL_ERROR;
    }
    else
    {
      pwr_sr1 = READ_REG(PWR->SR1);

      if (READ_BIT(pwr_sr1, PWR_SR1_SMPSHPRDY | PWR_SR1_SMPSBYPRDY) == 0U)
      {
        /* Already in SMPS Low-power mode */
        /* Nothing to configure      */   
      }
      else
      {
        /* Switch to Low-power mode */
        MODIFY_REG(PWR->CR4, (PWR_CR4_SMPSBYP | PWR_CR4_SMPSLPEN), PWR_CR4_SMPSLPEN);
      }
    }
  }
  else /* PWR_SMPS_BYPASS */
  {
    HAL_PWREx_SMPS_EnableBypassMode();
  }

  /* Wait until SMPS step down converter operating mode change */
  /* and at least one iteration loop */
  wait_loop_index = ((PWR_MODE_CHANGE_DELAY_VALUE * (SystemCoreClock / 100000U)) / 10U) + 1U;

  while ((HAL_PWREx_SMPS_GetEffectiveMode() != OperatingMode) && (wait_loop_index != 0U))
  {
    wait_loop_index--;
  }

  if (HAL_PWREx_SMPS_GetEffectiveMode() == OperatingMode)
  {
    status = HAL_OK;
  }
  else
  {
    status = HAL_TIMEOUT;
  }
  return status;
}

/**
  * @brief  Get SMPS effective step down converter operating mode
  * @retval Returned value can be one of the following values:
  *         @arg @ref PWR_SMPS_HIGH_POWER    SMPS step down converter in high-power mode (default)
  *         @arg @ref PWR_SMPS_LOW_POWER     SMPS step down converter in low-power mode
  *         @arg @ref PWR_SMPS_BYPASS        SMPS step down converter in bypass mode
  */
uint32_t HAL_PWREx_SMPS_GetEffectiveMode(void)
{
  uint32_t mode;
  uint32_t pwr_sr1;

  pwr_sr1 = READ_REG(PWR->SR1);
  if (READ_BIT(pwr_sr1, PWR_SR1_SMPSBYPRDY) != 0U)
  {
    mode = PWR_SMPS_BYPASS;
  }
  else if (READ_BIT(pwr_sr1, PWR_SR1_SMPSHPRDY) == 0U)
  {
    mode = PWR_SMPS_LOW_POWER;
  }
  else
  {
    mode = PWR_SMPS_HIGH_POWER;
  }

  return mode;
}

/**
  * @brief Enable SMPS step down converter fast start.
  * @note  This feature is secured by VDMSEC bit when system implements security (TZEN=1).
  * @retval None
  */
void HAL_PWREx_SMPS_EnableFastStart(void)
{
  SET_BIT(PWR->CR4, PWR_CR4_SMPSFSTEN);
}

/**
  * @brief Disable SMPS step down converter fast start.
  * @note  This feature is secured by VDMSEC bit when system implements security (TZEN=1).
  * @retval None
  */
void HAL_PWREx_SMPS_DisableFastStart(void)
{
  CLEAR_BIT(PWR->CR4, PWR_CR4_SMPSFSTEN);
}

/**
  * @brief Disable the SMPS Bypass.
  * @note  This feature is secured by VDMSEC bit when system implements security (TZEN=1).
  * @retval None
  */
void HAL_PWREx_SMPS_DisableBypassMode(void)
{
  CLEAR_BIT(PWR->CR4, PWR_CR4_SMPSBYP);
}

/**
  * @brief Enable the SMPS Bypass.
  * @note  This feature is secured by VDMSEC bit when system implements security (TZEN=1).
  * @retval None
  */
void HAL_PWREx_SMPS_EnableBypassMode(void)
{
  SET_BIT(PWR->CR4, PWR_CR4_SMPSBYP);
}


/**
  * @brief Enable external SMPS when external SMPS switch closed.
  * @note  This feature is secured by VDMSEC bit when system implements security (TZEN=1).
  * @retval None
  */
void HAL_PWREx_SMPS_EnableExternal(void)
{
  SET_BIT(PWR->CR4, PWR_CR4_EXTSMPSEN);
}

/**
  * @brief Disable external SMPS when external SMPS switch closed.
  * @note  This feature is secured by VDMSEC bit when system implements security (TZEN=1).
  * @retval None
  */
void HAL_PWREx_SMPS_DisableExternal(void)
{
  CLEAR_BIT(PWR->CR4, PWR_CR4_EXTSMPSEN);
}

/**
  * @brief  Get Main Regulator status for use with external SMPS
  * @retval Returned value can be one of the following values:
  *         @arg @ref PWR_MAINREG_READY_FOR_EXTSMPS     Main regulator ready for use with external SMPS
  *         @arg @ref PWR_MAINREG_NOT_READY_FOR_EXTSMPS Main regulator not ready for use with external SMPS
  */
uint32_t HAL_PWREx_SMPS_GetMainRegulatorExtSMPSReadyStatus(void)
{
  uint32_t main_regulator_status;
  uint32_t pwr_sr1;

  pwr_sr1 = READ_REG(PWR->SR1);
  if (READ_BIT(pwr_sr1, PWR_SR1_EXTSMPSRDY) != 0U)
  {
    main_regulator_status = PWR_MAINREG_READY_FOR_EXTSMPS;
  }
  else
  {
    main_regulator_status = PWR_MAINREG_NOT_READY_FOR_EXTSMPS;
  }
  return main_regulator_status;
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
