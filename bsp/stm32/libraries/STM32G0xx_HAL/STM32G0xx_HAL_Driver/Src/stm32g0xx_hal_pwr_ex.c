/**
  ******************************************************************************
  * @file    stm32g0xx_hal_pwr_ex.c
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
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
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
#include "stm32g0xx_hal.h"

/** @addtogroup STM32G0xx_HAL_Driver
  * @{
  */

/** @addtogroup PWREx
  * @{
  */

#ifdef HAL_PWR_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup PWR_Extended_Private_Defines PWR Extended Private Defines
  * @{
  */

#if defined(PWR_PVD_SUPPORT)
/** @defgroup PWR_PVD_Mode_Mask PWR PVD Mode Mask
  * @{
  */
#define PVD_MODE_IT           0x00010000U  /*!< Mask for interruption yielded
                                                by PVD threshold crossing     */
#define PVD_MODE_EVT          0x00020000U  /*!< Mask for event yielded
                                                by PVD threshold crossing     */
#define PVD_RISING_EDGE       0x00000001U  /*!< Mask for rising edge set as
                                                PVD trigger                   */
#define PVD_FALLING_EDGE      0x00000002U  /*!< Mask for falling edge set as
                                                PVD trigger                   */
/**
  * @}
  */
#endif /* PWR_PVD_SUPPORT */

/** @defgroup PWREx_TimeOut_Value  PWREx Flag Setting Time Out Value
  * @{
  */
#define PWR_REGLPF_SETTING_DELAY_6_US       6u  /*!< REGLPF should rise in about 5 us plus
                                                     2 APB clock. Taking in account max Sysclk at
                                                     2 MHz, and rounded to upper value */

#define PWR_VOSF_SETTING_DELAY_6_US         6u  /*!< VOSF should rise in about 5 us plus
                                                     2 APB clock. Taking in account max Sysclk at
                                                     16 MHz, and rounded to upper value */
/**
  * @}
  */

/** @defgroup PWREx_Gpio_Pin_Number  PWREx Gpio Pin Number
  * @{
  */
#define PWR_GPIO_PIN_NB                     16u  /*!< Number of gpio pin in bank */
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
     *** PVD configuration ***
    =========================
    [..]
      (+) The PVD is used to monitor the VDD power supply by comparing it to a
          threshold selected by the PVD Level (PVDRT[2:0] & PVDFT[2:0] bits in
          PWR CR2 register).
      (+) PVDO flag is available to indicate if VDD/VDDA is higher or lower
          than the PVD threshold. This event is internally connected to the EXTI
          line 16 and can generate an interrupt if enabled.
      (+) The PVD is stopped in Standby & Shutdown mode.

     *** PVM configuration ***
    =========================
    [..]

@endverbatim
  * @{
  */

/**
  * @brief  Enable battery charging.
  * @note   When VDD is present, charge the external battery on VBAT through an
  *         internal resistor.
  * @param  ResistorSelection specifies the resistor impedance.
  *         This parameter can be one of the following values:
  *           @arg @ref PWR_BATTERY_CHARGING_RESISTOR_5     5 kOhms resistor
  *           @arg @ref PWR_BATTERY_CHARGING_RESISTOR_1_5 1.5 kOhms resistor
  * @retval None
  */
void HAL_PWREx_EnableBatteryCharging(uint32_t ResistorSelection)
{
  uint32_t tmpreg;
  assert_param(IS_PWR_BATTERY_RESISTOR_SELECT(ResistorSelection));

  /* Specify resistor selection and enable battery charging */
  tmpreg = (PWR->CR4 & ~PWR_CR4_VBRS);
  PWR->CR4 = (tmpreg | ResistorSelection | PWR_CR4_VBE);
}


/**
  * @brief Disable battery charging.
  * @retval None
  */
void HAL_PWREx_DisableBatteryCharging(void)
{
  CLEAR_BIT(PWR->CR4, PWR_CR4_VBE);
}

#if defined(PWR_CR3_ENB_ULP)
/**
  * @brief  Enable POR Monitor sampling mode.
  * @note   When entering ultra low power modes (standby, shutdown) this feature
  *         can be enabled to reduce further consumption: Power On Reset monitor
  *         is then set in sampling mode, and no more in always on mode.
  * @retval None
  */
void HAL_PWREx_EnablePORMonitorSampling(void)
{
  PWR->CR3 |= PWR_CR3_ENB_ULP;
}


/**
  * @brief  Disable POR Monitor sampling mode.
  * @retval None
  */
void HAL_PWREx_DisablePORMonitorSampling(void)
{
  PWR->CR3 &= ~PWR_CR3_ENB_ULP;
}
#endif /* PWR_CR3_ENB_ULP */

#if defined(PWR_PVD_SUPPORT)
/**
  * @brief  Configure the Power Voltage Detector (PVD).
  * @param  sConfigPVD pointer to a PWR_PVDTypeDef structure that contains the
            PVD configuration information: threshold levels, operating mode.
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage thresholds corresponding to each
  *         detection level.
  * @note   User should take care that rising threshold is higher than falling
  *         one in order to avoid having always PVDO output set.
  * @retval HAL_OK
  */
HAL_StatusTypeDef HAL_PWREx_ConfigPVD(PWR_PVDTypeDef *sConfigPVD)
{
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(sConfigPVD->PVDLevel));
  assert_param(IS_PWR_PVD_MODE(sConfigPVD->Mode));

  /* Set PVD level bits only according to PVDLevel value */
  MODIFY_REG(PWR->CR2, (PWR_CR2_PVDFT | PWR_CR2_PVDRT), sConfigPVD->PVDLevel);

  /* Clear any previous config, in case no event or IT mode is selected */
  __HAL_PWR_PVD_EXTI_DISABLE_EVENT();
  __HAL_PWR_PVD_EXTI_DISABLE_IT();
  __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE();
  __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();

  /* Configure interrupt mode */
  if ((sConfigPVD->Mode & PVD_MODE_IT) == PVD_MODE_IT)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_IT();
  }

  /* Configure event mode */
  if ((sConfigPVD->Mode & PVD_MODE_EVT) == PVD_MODE_EVT)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_EVENT();
  }

  /* Configure the edge */
  if ((sConfigPVD->Mode & PVD_RISING_EDGE) == PVD_RISING_EDGE)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();
  }

  if ((sConfigPVD->Mode & PVD_FALLING_EDGE) == PVD_FALLING_EDGE)
  {
    __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();
  }

  return HAL_OK;
}


/**
  * @brief  Enable the Power Voltage Detector (PVD).
  * @retval None
  */
void HAL_PWREx_EnablePVD(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_PVDE);
}


/**
  * @brief  Disable the Power Voltage Detector (PVD).
  * @retval None
  */
void HAL_PWREx_DisablePVD(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_PVDE);
}
#endif /* PWR_PVD_SUPPORT */

#if defined(PWR_PVM_SUPPORT)
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
#endif /* PWR_PVM_SUPPORT */

#if defined(PWR_CR2_IOSV)
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
#endif /* PWR_CR2_IOSV */

#if defined (PWR_PVM_SUPPORT)
/**
  * @brief Enable the Power Voltage Monitoring for USB peripheral (power domain Vddio2)
  * @retval None
  */
void HAL_PWREx_EnablePVMUSB(void)
{
  SET_BIT(PWR->CR2, PWR_PVM_USB);
}

/**
  * @brief Disable the Power Voltage Monitoring for USB peripheral (power domain Vddio2)
  * @retval None
  */
void HAL_PWREx_DisablePVMUSB(void)
{
  CLEAR_BIT(PWR->CR2, PWR_PVM_USB);
}
#endif /* PWR_PVM_SUPPORT */

#if defined(PWR_PVM_SUPPORT)
/**
  * @brief Configure the Peripheral Voltage Monitoring (PVM).
  * @param sConfigPVM: pointer to a PWR_PVMTypeDef structure that contains the
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

  /* Configure EXTI 34 interrupts if so required:
     scan through PVMType to detect which PVMx is set and
     configure the corresponding EXTI line accordingly. */
  switch (sConfigPVM->PVMType)
  {
    case PWR_PVM_USB:
      /* Clear any previous config. Keep it clear if no event or IT mode is selected */
      __HAL_PWR_PVM_EXTI_DISABLE_EVENT();
      __HAL_PWR_PVM_EXTI_DISABLE_IT();
      __HAL_PWR_PVM_EXTI_DISABLE_FALLING_EDGE();
      __HAL_PWR_PVM_EXTI_DISABLE_RISING_EDGE();

      /* Configure interrupt mode */
      if ((sConfigPVM->Mode & PVM_MODE_IT) == PVM_MODE_IT)
      {
        __HAL_PWR_PVM_EXTI_ENABLE_IT();
      }

      /* Configure event mode */
      if ((sConfigPVM->Mode & PVM_MODE_EVT) == PVM_MODE_EVT)
      {
        __HAL_PWR_PVM_EXTI_ENABLE_EVENT();
      }

      /* Configure the edge */
      if ((sConfigPVM->Mode & PVM_RISING_EDGE) == PVM_RISING_EDGE)
      {
        __HAL_PWR_PVM_EXTI_ENABLE_RISING_EDGE();
      }

      if ((sConfigPVM->Mode & PVM_FALLING_EDGE) == PVM_FALLING_EDGE)
      {
        __HAL_PWR_PVM_EXTI_ENABLE_FALLING_EDGE();
      }
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}
#endif /* PWR_PVM_SUPPORT */
/**
  * @brief  Enable Internal Wake-up Line.
  * @retval None
  */
void HAL_PWREx_EnableInternalWakeUpLine(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_EIWUL);
}

/**
  * @brief  Disable Internal Wake-up Line.
  * @retval None
  */
void HAL_PWREx_DisableInternalWakeUpLine(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_EIWUL);
}

/**
  * @brief  Enable GPIO pull-up state in Standby and Shutdown modes.
  * @note   Set the relevant PUy bit of PWR_PUCRx register to configure the I/O in
  *         pull-up state in Standby and Shutdown modes.
  * @note   This state is effective in Standby and Shutdown modes only if APC bit
  *         is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note   The configuration is lost when exiting the Shutdown mode due to the
  *         power-on reset, maintained when exiting the Standby mode.
  * @note   To avoid any conflict at Standby and Shutdown modes exits, the corresponding
  *         PDy bit of PWR_PDCRx register is cleared unless it is reserved.
  * @param  GPIO Specify the IO port. This parameter can be PWR_GPIO_A, ..., PWR_GPIO_F
  *         to select the GPIO peripheral.
  * @param  GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for ports where less
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
      SET_BIT(PWR->PUCRA, (GPIONumber & ~PWR_GPIO_BIT_14));
      CLEAR_BIT(PWR->PDCRA, (GPIONumber & ~PWR_GPIO_BIT_13));
      break;

    case PWR_GPIO_B:
      SET_BIT(PWR->PUCRB, GPIONumber);
      CLEAR_BIT(PWR->PDCRB, GPIONumber);
      break;

    case PWR_GPIO_C:
      SET_BIT(PWR->PUCRC, GPIONumber);
      CLEAR_BIT(PWR->PDCRC, GPIONumber);
      break;

    case PWR_GPIO_D:
      SET_BIT(PWR->PUCRD, GPIONumber);
      CLEAR_BIT(PWR->PDCRD, GPIONumber);
      break;

#if defined(GPI0E)
    case PWR_GPIO_E:
      SET_BIT(PWR->PUCRE, GPIONumber);
      CLEAR_BIT(PWR->PDCRE, GPIONumber);
      break;
#endif /* GPI0E */
    case PWR_GPIO_F:
      SET_BIT(PWR->PUCRF, GPIONumber);
      CLEAR_BIT(PWR->PDCRF, GPIONumber);
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}


/**
  * @brief  Disable GPIO pull-up state in Standby mode and Shutdown modes.
  * @note   Reset the relevant PUy bit of PWR_PUCRx register used to configure the I/O
  *         in pull-up state in Standby and Shutdown modes.
  * @param  GPIO Specifies the IO port. This parameter can be PWR_GPIO_A, ..., PWR_GPIO_F
  *         to select the GPIO peripheral.
  * @param  GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for ports where less
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
      CLEAR_BIT(PWR->PUCRA, (GPIONumber & ~PWR_GPIO_BIT_14));
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

#if defined(GPI0E)
    case PWR_GPIO_E:
      CLEAR_BIT(PWR->PUCRE, GPIONumber);
      break;
#endif /* GPI0E */
    case PWR_GPIO_F:
      CLEAR_BIT(PWR->PUCRF, GPIONumber);
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}


/**
  * @brief  Enable GPIO pull-down state in Standby and Shutdown modes.
  * @note   Set the relevant PDy bit of PWR_PDCRx register to configure the I/O in
  *         pull-down state in Standby and Shutdown modes.
  * @note   This state is effective in Standby and Shutdown modes only if APC bit
  *         is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @note   The configuration is lost when exiting the Shutdown mode due to the
  *         power-on reset, maintained when exiting the Standby mode.
  * @note   To avoid any conflict at Standby and Shutdown modes exits, the corresponding
  *         PUy bit of PWR_PUCRx register is cleared unless it is reserved.
  * @param  GPIO Specify the IO port. This parameter can be PWR_GPIO_A..PWR_GPIO_F
  *         to select the GPIO peripheral.
  * @param  GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for ports where less
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
      SET_BIT(PWR->PDCRA, (GPIONumber & ~PWR_GPIO_BIT_13));
      CLEAR_BIT(PWR->PUCRA, (GPIONumber & ~PWR_GPIO_BIT_14));
      break;

    case PWR_GPIO_B:
      SET_BIT(PWR->PDCRB, GPIONumber);
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

#if defined(GPIOE)
    case PWR_GPIO_E:
      SET_BIT(PWR->PDCRE, GPIONumber);
      CLEAR_BIT(PWR->PUCRE, GPIONumber);
      break;
#endif /* GPI0E */
    case PWR_GPIO_F:
      SET_BIT(PWR->PDCRF, GPIONumber);
      CLEAR_BIT(PWR->PUCRF, GPIONumber);
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}


/**
  * @brief  Disable GPIO pull-down state in Standby and Shutdown modes.
  * @note   Reset the relevant PDy bit of PWR_PDCRx register used to configure the I/O
  *         in pull-down state in Standby and Shutdown modes.
  * @param  GPIO Specifies the IO port. This parameter can be PWR_GPIO_A..PWR_GPIO_F
  *         to select the GPIO peripheral.
  * @param  GPIONumber Specify the I/O pins numbers.
  *         This parameter can be one of the following values:
  *         PWR_GPIO_BIT_0, ..., PWR_GPIO_BIT_15 (except for ports where less
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
      CLEAR_BIT(PWR->PDCRA, (GPIONumber & ~PWR_GPIO_BIT_13));
      break;

    case PWR_GPIO_B:
      CLEAR_BIT(PWR->PDCRB, GPIONumber);
      break;

    case PWR_GPIO_C:
      CLEAR_BIT(PWR->PDCRC, GPIONumber);
      break;

    case PWR_GPIO_D:
      CLEAR_BIT(PWR->PDCRD, GPIONumber);
      break;

#if defined(GPIOE)
    case PWR_GPIO_E:
      CLEAR_BIT(PWR->PDCRE, GPIONumber);
      break;
#endif /* GPI0E */
    case PWR_GPIO_F:
      CLEAR_BIT(PWR->PDCRF, GPIONumber);
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}


/**
  * @brief  Enable pull-up and pull-down configuration.
  * @note   When APC bit is set, the I/O pull-up and pull-down configurations defined in
  *         PWR_PUCRx and PWR_PDCRx registers are applied in Standby and Shutdown modes.
  * @note   Pull-up set by PUy bit of PWR_PUCRx register is not activated if the corresponding
  *         PDy bit of PWR_PDCRx register is also set (pull-down configuration priority is higher).
  *         HAL_PWREx_EnableGPIOPullUp() and HAL_PWREx_EnableGPIOPullDown() APIs ensure there
  *         is no conflict when setting PUy or PDy bit.
  * @retval None
  */
void HAL_PWREx_EnablePullUpPullDownConfig(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_APC);
}

/**
  * @brief  Disable pull-up and pull-down configuration.
  * @note   When APC bit is cleared, the I/O pull-up and pull-down configurations defined in
  *         PWR_PUCRx and PWR_PDCRx registers are not applied in Standby and Shutdown modes.
  * @retval None
  */
void HAL_PWREx_DisablePullUpPullDownConfig(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_APC);
}

#if defined(PWR_CR3_RRS)
/**
  * @brief Enable SRAM content retention in Standby mode.
  * @note  When RRS bit is set, SRAM is powered by the low-power regulator in
  *         Standby mode and its content is kept.
  * @retval None
  */
void HAL_PWREx_EnableSRAMRetention(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_RRS);
}


/**
  * @brief Disable SRAM content retention in Standby mode.
  * @note  When RRS bit is reset, SRAM is powered off in Standby mode
  *        and its content is lost.
  * @retval None
  */
void HAL_PWREx_DisableSRAMRetention(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_RRS);
}
#endif /* PWR_CR3_RRS */

/**
  * @brief  Enable Flash Power Down.
  * @note   This API allows to enable flash power down capabilities in low power
  *         run, low power sleep and stop modes.
  * @param  PowerMode this can be a combination of following values:
  *           @arg @ref PWR_FLASHPD_LPRUN
  *           @arg @ref PWR_FLASHPD_LPSLEEP
  *           @arg @ref PWR_FLASHPD_STOP
  * @retval None
  */
void HAL_PWREx_EnableFlashPowerDown(uint32_t PowerMode)
{
  assert_param(IS_PWR_FLASH_POWERDOWN(PowerMode));

  PWR->CR1 |= PowerMode;
}


/**
  * @brief  Disable Flash Power Down.
  * @note   This API allows to disable flash power down capabilities in low power
  *         run, low power sleep and stop modes.
  * @param  PowerMode this can be a combination of following values:
  *           @arg @ref PWR_FLASHPD_LPRUN
  *           @arg @ref PWR_FLASHPD_LPSLEEP
  *           @arg @ref PWR_FLASHPD_STOP
  * @retval None
  */
void HAL_PWREx_DisableFlashPowerDown(uint32_t PowerMode)
{
  assert_param(IS_PWR_FLASH_POWERDOWN(PowerMode));

  PWR->CR1 &= ~PowerMode;
}


/**
  * @brief   Return Voltage Scaling Range.
  * @retval  VOS bit field:
  *         @arg @ref PWR_REGULATOR_VOLTAGE_SCALE1
  *         @arg @ref PWR_REGULATOR_VOLTAGE_SCALE2
  */
uint32_t HAL_PWREx_GetVoltageRange(void)
{
  return (PWR->CR1 & PWR_CR1_VOS);
}


/**
  * @brief Configure the main regulator output voltage.
  * @param  VoltageScaling specifies the regulator output voltage to achieve
  *         a tradeoff between performance and power consumption.
  *         This parameter can be one of the following values:
  *          @arg @ref PWR_REGULATOR_VOLTAGE_SCALE1 Regulator voltage output range 1 mode,
  *                                                typical output voltage at 1.2 V,
  *                                                system frequency up to 64 MHz.
  *          @arg @ref PWR_REGULATOR_VOLTAGE_SCALE2 Regulator voltage output range 2 mode,
  *                                                typical output voltage at 1.0 V,
  *                                                system frequency up to 16 MHz.
  * @note  When moving from Range 1 to Range 2, the system frequency must be decreased to
  *        a value below 16 MHz before calling HAL_PWREx_ControlVoltageScaling() API.
  *        When moving from Range 2 to Range 1, the system frequency can be increased to
  *        a value up to 64 MHz after calling HAL_PWREx_ControlVoltageScaling() API.
  * @note  When moving from Range 2 to Range 1, the API waits for VOSF flag to be
  *        cleared before returning the status. If the flag is not cleared within
  *        6 microseconds, HAL_TIMEOUT status is reported.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling)
{
  uint32_t wait_loop_index;

  assert_param(IS_PWR_VOLTAGE_SCALING_RANGE(VoltageScaling));

  /* Modify voltage scaling range */
  MODIFY_REG(PWR->CR1, PWR_CR1_VOS, VoltageScaling);

  /* In case of Range 1 selected, we need to ensure that main regulator reaches new value */
  if (VoltageScaling == PWR_REGULATOR_VOLTAGE_SCALE1)
  {
    /* Set timeout value */
    wait_loop_index = ((PWR_VOSF_SETTING_DELAY_6_US * SystemCoreClock) / 1000000U) + 1U;

    /* Wait until VOSF is reset */
    while (HAL_IS_BIT_SET(PWR->SR2, PWR_SR2_VOSF))
    {
      if (wait_loop_index != 0U)
      {
        wait_loop_index--;
      }
      else
      {
        return HAL_TIMEOUT;
      }
    }
  }

  return HAL_OK;
}



/**
  * @brief Enter Low-power Run mode
  * @note  System clock frequency has to be decreased below 2 MHz before entering
  *        low power run mode
  * @note  In Low-power Run mode, all I/O pins keep the same state as in Run mode.
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
  uint32_t wait_loop_index = ((PWR_REGLPF_SETTING_DELAY_6_US * SystemCoreClock) / 1000000U) + 1U;

  /* Clear LPR bit */
  CLEAR_BIT(PWR->CR1, PWR_CR1_LPR);

  /* Wait until REGLPF is reset */
  while (HAL_IS_BIT_SET(PWR->SR2, PWR_SR2_REGLPF))
  {
    if (wait_loop_index != 0U)
    {
      wait_loop_index--;
    }
    else
    {
      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}


#if defined(PWR_SHDW_SUPPORT)
/**
  * @brief  Enter Shutdown mode.
  * @note   In Shutdown mode, the PLL, the HSI, the LSI and the HSE oscillators are switched
  *         off. The voltage regulator is disabled and Vcore domain is powered off.
  *         SRAM and registers contents are lost except for registers in the Backup domain.
  *         The BOR is not available.
  * @note   The I/Os can be configured either with a pull-up or pull-down or can
  *         be kept in analog state.
  *         HAL_PWREx_EnableGPIOPullUp() and HAL_PWREx_EnableGPIOPullDown()
  *         respectively enable Pull Up and PullDown state.
  *         HAL_PWREx_DisableGPIOPullUp() & HAL_PWREx_DisableGPIOPullDown()
  *         disable the same. These states are effective in Standby mode only if
  *         APC bit is set through HAL_PWREx_EnablePullUpPullDownConfig() API.
  * @retval None

  * @retval None
  */
void HAL_PWREx_EnterSHUTDOWNMode(void)
{
  /* Set Shutdown mode */
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, PWR_LOWPOWERMODE_SHUTDOWN);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM)
  __force_stores();
#endif /* __CC_ARM */

  /* Request Wait For Interrupt */
  __WFI();
}
#endif /* PWR_SHDW_SUPPORT */

#if defined(PWR_PVD_SUPPORT) && defined(PWR_PVM_SUPPORT)
/**
  * @brief  This function handles the PWR PVD interrupt request.
  * @note   This API should be called under the PVD_IRQHandler().
  * @retval None
  */
void HAL_PWREx_PVD_PVM_IRQHandler(void)
{
  /* Check PWR PVD exti Rising flag */
  if (__HAL_PWR_PVD_EXTI_GET_RISING_FLAG() != 0x0U)
  {
    /* Clear PVD exti pending bit */
    __HAL_PWR_PVD_EXTI_CLEAR_RISING_FLAG();

    /* PWR PVD interrupt rising user callback */
    HAL_PWREx_PVD_PVM_Rising_Callback();
  }

  /* Check PWR exti fallling flag */
  if (__HAL_PWR_PVD_EXTI_GET_FALLING_FLAG() != 0x0U)
  {
    /* Clear PVD exti pending bit */
    __HAL_PWR_PVD_EXTI_CLEAR_FALLING_FLAG();

    /* PWR PVD interrupt falling user callback */
    HAL_PWREx_PVD_PVM_Falling_Callback();
  }

  /* Check PWR PVM exti Rising flag */
  if (__HAL_PWR_PVM_EXTI_GET_RISING_FLAG() != 0x0U)
  {
    /* Clear PVM exti pending bit */
    __HAL_PWR_PVM_EXTI_CLEAR_RISING_FLAG();

    /* PWR PVD PVM interrupt rising user callback */
    HAL_PWREx_PVD_PVM_Rising_Callback();
  }

  /* Check PWR PVM exti fallling flag */
  if (__HAL_PWR_PVM_EXTI_GET_FALLING_FLAG() != 0x0U)
  {
    /* Clear PVM exti pending bit */
    __HAL_PWR_PVM_EXTI_CLEAR_FALLING_FLAG();

    /* PWR PVM interrupt falling user callback */
    HAL_PWREx_PVD_PVM_Falling_Callback();
  }
}

/**
  * @brief  PWR PVD interrupt rising callback
  * @retval None
  */
__weak void HAL_PWREx_PVD_PVM_Rising_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_PWR_PVD_Rising_Callback can be implemented in the user file
  */
}

/**
  * @brief  PWR PVD interrupt Falling callback
  * @retval None
  */
__weak void HAL_PWREx_PVD_PVM_Falling_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_PWR_PVD_Falling_Callback can be implemented in the user file
  */
}
#elif defined(PWR_PVD_SUPPORT)
/**
  * @brief  This function handles the PWR PVD interrupt request.
  * @note   This API should be called under the PVD_IRQHandler().
  * @retval None
  */
void HAL_PWREx_PVD_IRQHandler(void)
{
  /* Check PWR exti Rising flag */
  if (__HAL_PWR_PVD_EXTI_GET_RISING_FLAG() != 0x0U)
  {
    /* Clear PVD exti pending bit */
    __HAL_PWR_PVD_EXTI_CLEAR_RISING_FLAG();

    /* PWR PVD interrupt rising user callback */
    HAL_PWREx_PVD_Rising_Callback();
  }

  /* Check PWR exti fallling flag */
  if (__HAL_PWR_PVD_EXTI_GET_FALLING_FLAG() != 0x0U)
  {
    /* Clear PVD exti pending bit */
    __HAL_PWR_PVD_EXTI_CLEAR_FALLING_FLAG();

    /* PWR PVD interrupt falling user callback */
    HAL_PWREx_PVD_Falling_Callback();
  }
}

/**
  * @brief  PWR PVD interrupt rising callback
  * @retval None
  */
__weak void HAL_PWREx_PVD_Rising_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_PWR_PVD_Rising_Callback can be implemented in the user file
  */
}

/**
  * @brief  PWR PVD interrupt Falling callback
  * @retval None
  */
__weak void HAL_PWREx_PVD_Falling_Callback(void)
{
  /* NOTE : This function should not be modified; when the callback is needed,
            the HAL_PWR_PVD_Falling_Callback can be implemented in the user file
  */
}

#endif /* PWR_PVD_SUPPORT && PWR_PVM_SUPPORT */

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
