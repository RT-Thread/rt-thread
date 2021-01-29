/**
  ******************************************************************************
  * @file    stm32wlxx_hal_rcc.c
  * @author  MCD Application Team
  * @brief   RCC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Reset and Clock Control (RCC) peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *
  @verbatim
  ==============================================================================
                      ##### RCC specific features #####
  ==============================================================================
    [..]
      After reset the device is running from Multiple Speed Internal oscillator
      (4 MHz) with Flash 0 wait state. Flash prefetch buffer, D-Cache
      and I-Cache are disabled, and all peripherals are off except internal
      SRAM, Flash and JTAG.

      (+) There is no prescaler on High speed (AHBs) and Low speed (APBs) buses:
          all peripherals mapped on these buses are running at MSI speed.
      (+) The clock for all peripherals is switched off, except the SRAM and FLASH.
      (+) All GPIOs are in analog mode, except the JTAG pins which
          are assigned to be used for debug purpose.

    [..]
      Once the device started from reset, the user application has to:
      (+) Configure  clock source to be used to drive the System clock
          (if the application needs higher frequency/performance)
      (+) Configure the System clock frequency and Flash settings
      (+) Configure the AHB and APB buses prescalers
      (+) Enable the clock for the peripheral(s) to be used
      (+) Configure the clock source(s) for peripherals which clocks are not
          derived from the System clock (RTC, ADC, RNG, I2S2, USARTx, LPUART1, LPTIMx, I2Cx)

  @endverbatim
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

/** @defgroup RCC RCC
  * @brief RCC HAL module driver
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup RCC_Private_Constants RCC Private Constants
  * @{
  */
#define HSE_TIMEOUT_VALUE          HSE_STARTUP_TIMEOUT
#define HSI_TIMEOUT_VALUE          (2U)       /* 2 ms (minimum Tick + 1)         */
#define MSI_TIMEOUT_VALUE          (2U)       /* 2 ms (minimum Tick + 1)         */
#define LSI_TIMEOUT_VALUE          (17U)      /* 17 ms (16 ms starting time + 1) */
#define PRESCALER_TIMEOUT_VALUE    (2U)       /* 2 ms (minimum Tick + 1)         */
#define LATENCY_TIMEOUT_VALUE      (2U)       /* 2 ms (minimum Tick + 1)         */
#define CLOCKSWITCH_TIMEOUT_VALUE  (5000U)    /* 5 s                             */

#define PLLSOURCE_NONE             (0U)
#define MEGA_HZ                    (1000000U) /* Division factor to convert Hz in Mhz */

#define RCC_PLLCFR_RESET_VALUE     (RCC_PLLCFGR_PLLR_0 | RCC_PLLCFGR_PLLQ_0 | RCC_PLLCFGR_PLLP_1 | RCC_PLLCFGR_PLLN_0)
#define RCC_EXTCFGR_RESET_VALUE     (0x00030000U)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup RCC_Private_Macros RCC Private Macros
  * @{
  */
#define __MCO1_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define MCO1_GPIO_PORT        GPIOA
#define MCO1_PIN              GPIO_PIN_8

#define __COUNTOF(_A_)   (sizeof(_A_) / sizeof(*(_A_)))
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_Private_Functions RCC Private Functions
  * @{
  */
static HAL_StatusTypeDef RCC_SetFlashLatencyFromMSIRange(uint32_t MSI_Range);
static HAL_StatusTypeDef RCC_SetFlashLatency(uint32_t Flash_ClkSrcFreq, uint32_t VCORE_Voltage);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup RCC_Exported_Functions RCC Exported Functions
  * @{
  */

/** @defgroup RCC_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
  @verbatim
 ===============================================================================
           ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]
      This section provides functions allowing to configure the internal and external oscillators
      (HSE, HSI, LSE, MSI, LSI, PLL, CSS and MCO) and the System buses clocks (SYSCLK, HCLK1, HCLK2, HCLK3, PCLK1
       and PCLK2).

    [..] Internal/external clock and PLL configuration
         (+) HSI (high-speed internal): 16 MHz factory-trimmed RC used directly or through
             the PLL as System clock source.

         (+) MSI (Multiple Speed Internal): Its frequency is software trimmable from 100KHZ to 48MHZ.
             The number of flash wait states is automatically adjusted when MSI range is updated with
             @ref HAL_RCC_OscConfig() and the MSI is used as System clock source.

         (+) LSI (low-speed internal): 32 KHz low consumption RC used as IWDG and/or RTC
             clock source.

         (+) HSE (high-speed external): 32 MHz crystal oscillator used directly or
             through the PLL as System clock source. It is used also as RF clock source
             Can be used also optionally as RTC clock source.

         (+) LSE (low-speed external): 32.768 KHz oscillator used optionally to drive RTC used for
             Auto-wakeup from Stop and Standby modes, or the real-time clock (RTCCLK).

         (+) PLL (clocked by HSI, HSE or MSI) providing up to three independent output clocks:
           (++) The first output is used to generate the high speed system clock (up to 48MHz).
           (++) The second output is used to generate the clock for I2S2 and the random analog generator (<=48 MHz)
           (++) The third output is used to generate a clock on ADC interface.

         (+) CSS (Clock security system): once enabled, if a HSE clock failure occurs
             (HSE used directly or through PLL as System clock source), the System clock
             is automatically switched to MSI or the HSI oscillator (depending on the
             STOPWUCK configuration) and an interrupt is generated if enabled.
             The interrupt is linked to the CPU1 and CPU2 NMI (Non-Maskable Interrupt) exception vector.

         (+) LSECSS: once enabled, if a LSE clock failure occurs, the LSE
             clock is no longer supplied to the RTC but no hardware action is made to the registers. If the
             MSI was in PLL-mode, this mode is disabled.
             In Standby mode a wakeup is generated. In other modes an interrupt can be sent to wakeup
             the software

         (+) MCO (microcontroller clock output): used to output MSI, LSI, HSI, LSE, HSE (before and
             after stabilization), SYSCLK, or main PLL clocks (through a configurable prescaler) on PA8 pin.

    [..] System, AHB and APB buses clocks configuration
         (+) Several clock sources can be used to drive the System clock (SYSCLK): MSI, HSI,
             HSE and main PLL.
             The AHB clock (HCLK1) is derived from System clock through configurable
             prescaler and used to clock the CPU1, memory and peripherals mapped
             on AHB bus (DMA, GPIO...). APB1 (PCLK1) and APB2 (PCLK2) clocks are derived
             from AHB clock through configurable prescalers and used to clock
             the peripherals mapped on these buses. You can use
             "@ref HAL_RCC_GetSysClockFreq()" function to retrieve the frequencies of these clocks.
             The AHB3 clock (HCLK3) is derived from System clock through configurable
             prescaler and used to clock the FLASH. APB3 (PCLK3) is derived from AHB3 clock.

         -@- All the peripheral clocks are derived from the System clock (SYSCLK) except:

           (+@) RTC: the RTC clock can be derived either from the LSI, LSE or HSE clock divided by 32.
                You have to use @ref __HAL_RCC_RTC_ENABLE() and @ref HAL_RCCEx_PeriphCLKConfig() function
                to configure this clock.

           (+@) IWDG clock which is always the LSI clock.

         (+) The maximum frequency of the SYSCLK, HCLK1, HCLK2, HCLK3, PCLK1 and PCLK2 is 48 MHz.
             The clock source frequency should be adapted depending on the device voltage range
             as listed in the Reference Manual "Clock source frequency versus voltage scaling" chapter.

  @endverbatim

           Table 1. HCLK3 clock frequency.
           +--------------------------------------------------------+
           | Latency          |    HCLK3 clock frequency (MHz)      |
           |                  |-------------------------------------|
           |                  | voltage range 1  | voltage range 2  |
           |                  |      1.2 V       |     1.0 V        |
           |------------------|------------------|------------------|
           |0WS(1 HCLK cycles |   HCLK3 <= 18    |   HCLK3 <= 6     |
           |------------------|------------------|------------------|
           |1WS(2 HCLK cycles)|   HCLK3 <= 36    |   HCLK3 <= 12    |
           |------------------|------------------|------------------|
           |2WS(3 HCLK cycles)|   HCLK3 <= 48    |   HCLK3 <= 16    |
           |------------------|------------------|------------------|

  * @{
  */

/**
  * @brief  Reset the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *            - MSI ON and used as system clock source
  *            - HSE, HSI, PLL OFF
  *            - HCLK1, HCLK2, HCLK3, PCLK1 and PCLK2 prescalers set to 1.
  *            - CSS, MCO OFF
  *            - All interrupts disabled
  * @note   This function doesn't modify the configuration of the
  *            - Peripheral clocks
  *            - LSI, LSE and RTC clocks
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCC_DeInit(void)
{
  uint32_t tickstart;

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Set MSION bit */
  LL_RCC_MSI_Enable();

  /* Wait till MSI is ready */
  while (LL_RCC_MSI_IsReady() == 0U)
  {
    if ((HAL_GetTick() - tickstart) > MSI_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Set MSIRANGE default value */
  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_6);

  /* Set MSITRIM bits to the reset value*/
  LL_RCC_MSI_SetCalibTrimming(RCC_MSICALIBRATION_DEFAULT);

  /* Set HSITRIM bits to the reset value*/
  LL_RCC_HSI_SetCalibTrimming(RCC_HSICALIBRATION_DEFAULT);

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Reset CFGR register (MSI is selected as system clock source) */
  CLEAR_REG(RCC->CFGR);

  /* Wait till MSI oscillator used as system clock */
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_MSI)
  {
    if ((HAL_GetTick() - tickstart) > CLOCKSWITCH_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Reset HSION, HSIKERON, HSIASFS, HSEON, PLLON, HSEPRE bits */
  CLEAR_BIT(RCC->CR, RCC_CR_HSION | RCC_CR_HSIKERON | RCC_CR_HSIASFS | RCC_CR_HSEON | RCC_CR_HSEPRE | RCC_CR_PLLON);

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till HSE is disabled */
  while (LL_RCC_HSE_IsReady() != 0U)
  {
    if ((HAL_GetTick() - tickstart) > HSE_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Reset HSEBYPPWR bit once HSE is OFF */
  LL_RCC_HSE_DisableTcxo();

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till PLL is fully stopped */
  while (LL_RCC_PLL_IsReady() != 0U)
  {
    if ((HAL_GetTick() - tickstart) > PLL_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* once PLL is OFF, reset PLLCFGR register to default value */
  WRITE_REG(RCC->PLLCFGR, RCC_PLLCFR_RESET_VALUE);

  /* Disable all interrupts */
  CLEAR_REG(RCC->CIER);

  /* Clear all flags */
  WRITE_REG(RCC->CICR, 0xFFFFFFFFU);

  /* EXTCFGR reset*/
  WRITE_REG(RCC->EXTCFGR, RCC_EXTCFGR_RESET_VALUE);

  /* Update the SystemCoreClock global variable */
  SystemCoreClock = MSI_VALUE;

  /* Adapt Systick interrupt period */
  if (HAL_InitTick(uwTickPrio) != HAL_OK)
  {
    return HAL_ERROR;
  }
  else
  {
    return HAL_OK;
  }
}

/**
  * @brief  Initialize the RCC Oscillators according to the specified parameters in the
  *         @ref RCC_OscInitTypeDef.
  * @param  RCC_OscInitStruct  pointer to a @ref RCC_OscInitTypeDef structure that
  *         contains the configuration information for the RCC Oscillators.
  * @note   The PLL is not disabled when used as system clock.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct)
{
  uint32_t tickstart;
  uint32_t sysclk_source;
  uint32_t pll_config;
  HAL_StatusTypeDef status;

  /* Check Null pointer */
  if (RCC_OscInitStruct == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RCC_OSCILLATORTYPE(RCC_OscInitStruct->OscillatorType));

  sysclk_source = __HAL_RCC_GET_SYSCLK_SOURCE();
  pll_config = __HAL_RCC_GET_PLL_OSCSOURCE();

  /*----------------------------- MSI Configuration --------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_MSI) == RCC_OSCILLATORTYPE_MSI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_MSI(RCC_OscInitStruct->MSIState));
    assert_param(IS_RCC_MSI_CALIBRATION_VALUE(RCC_OscInitStruct->MSICalibrationValue));
    assert_param(IS_RCC_MSI_CLOCK_RANGE(RCC_OscInitStruct->MSIClockRange));

    /* When the MSI is used as system clock it will not be disabled */
    if ((sysclk_source == RCC_SYSCLKSOURCE_STATUS_MSI) ||
        ((sysclk_source == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && (pll_config == RCC_PLLSOURCE_MSI)))
    {
      if ((LL_RCC_MSI_IsReady() != 0U) && (RCC_OscInitStruct->MSIState == RCC_MSI_OFF))
      {
        return HAL_ERROR;
      }
      /* Otherwise, just the calibration and MSI range change are allowed */
      else
      {
        /* To correctly read data from FLASH memory, the number of wait states (LATENCY)
           must be correctly programmed according to the frequency of the AHB3 clock
           and the supply voltage of the device. */
        if (RCC_OscInitStruct->MSIClockRange > __HAL_RCC_GET_MSI_RANGE())
        {
          /* First increase number of wait states update if necessary */
          if (RCC_SetFlashLatencyFromMSIRange(RCC_OscInitStruct->MSIClockRange) != HAL_OK)
          {
            return HAL_ERROR;
          }

          /* Selects the Multiple Speed oscillator (MSI) clock range .*/
          __HAL_RCC_MSI_RANGE_CONFIG(RCC_OscInitStruct->MSIClockRange);
          /* Adjusts the Multiple Speed oscillator (MSI) calibration value.*/
          __HAL_RCC_MSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->MSICalibrationValue);
        }
        else
        {
          /* Else, keep current flash latency while decreasing applies */
          /* Selects the Multiple Speed oscillator (MSI) clock range .*/
          __HAL_RCC_MSI_RANGE_CONFIG(RCC_OscInitStruct->MSIClockRange);
          /* Adjusts the Multiple Speed oscillator (MSI) calibration value.*/
          __HAL_RCC_MSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->MSICalibrationValue);

          /* Decrease number of wait states update if necessary */
          if (RCC_SetFlashLatencyFromMSIRange(RCC_OscInitStruct->MSIClockRange) != HAL_OK)
          {
            return HAL_ERROR;
          }
        }

        /* Update the SystemCoreClock global variable */
        SystemCoreClock = HAL_RCC_GetHCLKFreq();

        /* Configure the source of time base considering new system clocks settings*/
        status = HAL_InitTick(uwTickPrio);
        if (status != HAL_OK)
        {
          return status;
        }
      }
    }
    else
    {
      /* Check the MSI State */
      if (RCC_OscInitStruct->MSIState != RCC_MSI_OFF)
      {
        /* Enable the Internal High Speed oscillator (MSI). */
        __HAL_RCC_MSI_ENABLE();

        /* Get timeout */
        tickstart = HAL_GetTick();

        /* Wait till MSI is ready */
        while (LL_RCC_MSI_IsReady() == 0U)
        {
          if ((HAL_GetTick() - tickstart) > MSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }

        /* Selects the Multiple Speed oscillator (MSI) clock range .*/
        __HAL_RCC_MSI_RANGE_CONFIG(RCC_OscInitStruct->MSIClockRange);
        /* Adjusts the Multiple Speed oscillator (MSI) calibration value.*/
        __HAL_RCC_MSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->MSICalibrationValue);

      }
      else
      {
        /* Disable the Internal High Speed oscillator (MSI). */
        __HAL_RCC_MSI_DISABLE();

        /* Get timeout */
        tickstart = HAL_GetTick();

        /* Wait till MSI is disabled */
        while (LL_RCC_MSI_IsReady() != 0U)
        {
          if ((HAL_GetTick() - tickstart) > MSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
  }

  /*------------------------------- HSE Configuration ------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSE(RCC_OscInitStruct->HSEState));

    /* When the HSE is used as system clock or clock source for PLL in these cases it is not allowed to be disabled */
    if ((sysclk_source == RCC_SYSCLKSOURCE_STATUS_HSE) ||
        ((sysclk_source == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && (pll_config == RCC_PLLSOURCE_HSE)))
    {
      if ((LL_RCC_HSE_IsReady() != 0U) && (RCC_OscInitStruct->HSEState == RCC_HSE_OFF))
      {
        return HAL_ERROR;
      }
    }
    else
    {
      /* Set the new HSE configuration ---------------------------------------*/
      /* Check HSE division factor */
      assert_param(IS_RCC_HSEDIV(RCC_OscInitStruct->HSEDiv));

      /* Set HSE division factor */
      MODIFY_REG(RCC->CR, RCC_CR_HSEPRE, RCC_OscInitStruct->HSEDiv);

      __HAL_RCC_HSE_CONFIG(RCC_OscInitStruct->HSEState);

      /* Check the HSE State */
      if (RCC_OscInitStruct->HSEState != RCC_HSE_OFF)
      {
        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSE is ready */
        while (LL_RCC_HSE_IsReady() == 0U)
        {
          if ((HAL_GetTick() - tickstart) > HSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSE is disabled */
        while (LL_RCC_HSE_IsReady() != 0U)
        {
          if ((HAL_GetTick() - tickstart) > HSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
  }

  /*----------------------------- HSI Configuration --------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSI(RCC_OscInitStruct->HSIState));
    assert_param(IS_RCC_HSI_CALIBRATION_VALUE(RCC_OscInitStruct->HSICalibrationValue));

    /* Check if HSI is used as system clock or as PLL source when PLL is selected as system clock */
    if ((sysclk_source == RCC_SYSCLKSOURCE_STATUS_HSI) ||
        ((sysclk_source == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && (pll_config == RCC_PLLSOURCE_HSI)))
    {
      /* When HSI is used as system clock it will not be disabled */
      if ((LL_RCC_HSI_IsReady() != 0U) && (RCC_OscInitStruct->HSIState == RCC_HSI_OFF))
      {
        return HAL_ERROR;
      }
      /* Otherwise, just the calibration is allowed */
      else
      {
        /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
        __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HSICalibrationValue);
      }
    }
    else
    {
      /* Check the HSI State */
      if (RCC_OscInitStruct->HSIState != RCC_HSI_OFF)
      {
        /* Enable the Internal High Speed oscillator (HSI). */
        __HAL_RCC_HSI_ENABLE();

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSI is ready */
        while (LL_RCC_HSI_IsReady() == 0U)
        {
          if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }

        /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
        __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HSICalibrationValue);
      }
      else
      {
        /* Disable the Internal High Speed oscillator (HSI). */
        __HAL_RCC_HSI_DISABLE();

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSI is disabled */
        while (LL_RCC_HSI_IsReady() != 0U)
        {
          if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
  }

  /*------------------------------ LSI Configuration -------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LSI(RCC_OscInitStruct->LSIState));

    /* Check the LSI State */
    if (RCC_OscInitStruct->LSIState != RCC_LSI_OFF)
    {
      uint32_t csr_temp = RCC->CSR;

      /* Check LSI division factor */
      assert_param(IS_RCC_LSIDIV(RCC_OscInitStruct->LSIDiv));

      if (RCC_OscInitStruct->LSIDiv != (csr_temp & RCC_CSR_LSIPRE))
      {
        if (((csr_temp & RCC_CSR_LSIRDY) == RCC_CSR_LSIRDY) && \
            ((csr_temp & RCC_CSR_LSION) != RCC_CSR_LSION))
        {
          /* If LSIRDY is set while LSION is not enabled,
             LSIPRE can't be updated  */
          return HAL_ERROR;
        }

        /* Turn off LSI before changing RCC_CSR_LSIPRE */
        if ((csr_temp & RCC_CSR_LSION) == RCC_CSR_LSION)
        {
          __HAL_RCC_LSI_DISABLE();

          /* Get Start Tick*/
          tickstart = HAL_GetTick();

          /* Wait till LSI is disabled */
          while (LL_RCC_LSI_IsReady() != 0U)
          {
            if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
            {
              return HAL_TIMEOUT;
            }
          }
        }

        /* Set LSI division factor */
        MODIFY_REG(RCC->CSR, RCC_CSR_LSIPRE, RCC_OscInitStruct->LSIDiv);
      }

      /* Enable the Internal Low Speed oscillator (LSI). */
      __HAL_RCC_LSI_ENABLE();

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSI is ready */
      while (LL_RCC_LSI_IsReady() == 0U)
      {
        if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      /* Disable the Internal Low Speed oscillator (LSI). */
      __HAL_RCC_LSI_DISABLE();

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSI is disabled */
      while (LL_RCC_LSI_IsReady() != 0U)
      {
        if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  /*------------------------------ LSE Configuration -------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LSE(RCC_OscInitStruct->LSEState));

    /* Update LSE configuration in Backup Domain control register    */
    /* Requires to enable write access to Backup Domain of necessary */

    if (LL_PWR_IsEnabledBkUpAccess() == 0U)
    {
      /* Enable write access to Backup domain */
      HAL_PWR_EnableBkUpAccess();

      /* Wait for Backup domain Write protection disable */
      tickstart = HAL_GetTick();

      while (LL_PWR_IsEnabledBkUpAccess() == 0U)
      {
        if ((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    /* Set the new LSE configuration -----------------------------------------*/
    if (RCC_OscInitStruct->LSEState != RCC_LSE_OFF)
    {
      /* Enable LSE bypasss (if requested) */
      if ((RCC_OscInitStruct->LSEState == RCC_LSE_BYPASS)
          || (RCC_OscInitStruct->LSEState == RCC_LSE_BYPASS_RTC_ONLY))
      {
        /* LSE oscillator bypass enable */
        SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
      }

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* LSE oscillator enable */
      SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);

      /* Wait till LSE is ready */
      while (LL_RCC_LSE_IsReady() == 0U)
      {
        if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }

      /* Enable LSE system clock (if requested) */
      if ((RCC_OscInitStruct->LSEState == RCC_LSE_ON)
          || (RCC_OscInitStruct->LSEState == RCC_LSE_BYPASS))
      {
        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        SET_BIT(RCC->BDCR, RCC_BDCR_LSESYSEN);

        /* Wait till LSESYS is ready */
        while (READ_BIT(RCC->BDCR, RCC_BDCR_LSESYSRDY) == 0U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSESYSEN);

        /* Wait till LSESYSRDY is cleared */
        while (READ_BIT(RCC->BDCR, RCC_BDCR_LSESYSRDY) != 0U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
    else
    {
      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSESYSEN);

      /* Wait till LSESYSRDY is cleared */
      while (READ_BIT(RCC->BDCR, RCC_BDCR_LSESYSRDY) != 0U)
      {
        if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* LSE oscillator disable */
      CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);

      /* Wait till LSE is disabled */
      while (LL_RCC_LSE_IsReady() != 0U)
      {
        if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  /*-------------------------------- PLL Configuration -----------------------*/
  /* Check the parameters */
  assert_param(IS_RCC_PLL(RCC_OscInitStruct->PLL.PLLState));

  if (RCC_OscInitStruct->PLL.PLLState != RCC_PLL_NONE)
  {
    /* Check if the PLL is used as system clock or not */
    if (sysclk_source != RCC_SYSCLKSOURCE_STATUS_PLLCLK)
    {
      if (RCC_OscInitStruct->PLL.PLLState == RCC_PLL_ON)
      {
        /* Check the parameters */
        assert_param(IS_RCC_PLLSOURCE(RCC_OscInitStruct->PLL.PLLSource));
        assert_param(IS_RCC_PLLM_VALUE(RCC_OscInitStruct->PLL.PLLM));
        assert_param(IS_RCC_PLLN_VALUE(RCC_OscInitStruct->PLL.PLLN));
        assert_param(IS_RCC_PLLP_VALUE(RCC_OscInitStruct->PLL.PLLP));
        assert_param(IS_RCC_PLLQ_VALUE(RCC_OscInitStruct->PLL.PLLQ));
        assert_param(IS_RCC_PLLR_VALUE(RCC_OscInitStruct->PLL.PLLR));

        /* Disable the main PLL. */
        __HAL_RCC_PLL_DISABLE();

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till PLL is ready */
        while (LL_RCC_PLL_IsReady() != 0U)
        {
          if ((HAL_GetTick() - tickstart) > PLL_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }

        /* Configure the main PLL clock source, multiplication and division factors. */
        __HAL_RCC_PLL_CONFIG(RCC_OscInitStruct->PLL.PLLSource,
                             RCC_OscInitStruct->PLL.PLLM,
                             RCC_OscInitStruct->PLL.PLLN,
                             RCC_OscInitStruct->PLL.PLLP,
                             RCC_OscInitStruct->PLL.PLLQ,
                             RCC_OscInitStruct->PLL.PLLR);

        /* Enable the main PLL. */
        __HAL_RCC_PLL_ENABLE();

        /* Enable PLL System Clock output. */
        __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_SYSCLK);

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till PLL is ready */
        while (LL_RCC_PLL_IsReady() == 0U)
        {
          if ((HAL_GetTick() - tickstart) > PLL_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        /* Disable the main PLL. */
        __HAL_RCC_PLL_DISABLE();

        /* Disable all PLL outputs to save power */
        MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC, PLLSOURCE_NONE);

        __HAL_RCC_PLLCLKOUT_DISABLE(RCC_PLL_SYSCLK | RCC_PLL_RNGCLK | RCC_PLL_ADCCLK);


        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till PLL is disabled */
        while (LL_RCC_PLL_IsReady() != 0U)
        {
          if ((HAL_GetTick() - tickstart) > PLL_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
    else
    {
      /* Check if there is a request to disable the PLL used as System clock source */
      if ((RCC_OscInitStruct->PLL.PLLState) == RCC_PLL_OFF)
      {
        return HAL_ERROR;
      }
      else
      {
        /* Do not return HAL_ERROR if request repeats the current configuration */
        pll_config = RCC->PLLCFGR;
        if ((READ_BIT(pll_config, RCC_PLLCFGR_PLLSRC) != RCC_OscInitStruct->PLL.PLLSource)
            || (READ_BIT(pll_config, RCC_PLLCFGR_PLLM)   != RCC_OscInitStruct->PLL.PLLM)
            || (READ_BIT(pll_config, RCC_PLLCFGR_PLLN)   != (RCC_OscInitStruct->PLL.PLLN << RCC_PLLCFGR_PLLN_Pos))
            || (READ_BIT(pll_config, RCC_PLLCFGR_PLLR)   != RCC_OscInitStruct->PLL.PLLR))
        {
          return HAL_ERROR;
        }
      }
    }
  }
  return HAL_OK;
}


/**
  * @brief  Initialize the CPU, AHB and APB buses clocks according to the specified
  *         parameters in the RCC_ClkInitStruct.
  * @param  RCC_ClkInitStruct  pointer to a @ref RCC_ClkInitTypeDef structure that
  *         contains the configuration information for the RCC peripheral.
  * @param  FLatency  FLASH Latency
  *          This parameter can be one of the following values:
  *            @arg FLASH_LATENCY_0   FLASH 0 Latency cycle
  *            @arg FLASH_LATENCY_1   FLASH 1 Latency cycle
  *            @arg FLASH_LATENCY_2   FLASH 2 Latency cycle
  *
  * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency
  *
  * @note   The MSI is used by default as system clock source after
  *         wake-up from Reset, wake-up from STANDBY mode. After restart from Reset,
  *         the MSI frequency is set to its default value 4 MHz.
  *
  * @note   The HSI can be selected as system clock source after
  *         from STOP modes or in case of failure of the HSE used directly or indirectly
  *         as system clock (if the Clock Security System CSS is enabled).
  *
  * @note   A switch from one clock source to another occurs only if the target
  *         clock source is ready (clock stable after startup delay or PLL locked).
  *         If a clock source which is not yet ready is selected, the switch will
  *         occur when the clock source is ready.
  *
  * @note   You can use @ref HAL_RCC_GetClockConfig() function to know which clock is
  *         currently used as system clock source.
  *
  * @note   Depending on the device voltage range, the software has to set correctly
  *         HPRE[3:0] bits to ensure that HCLK1 not exceed the maximum allowed frequency
  *         (for more details refer to section above "Initialization/de-initialization functions")
  * @retval None
  */
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t FLatency)
{
  uint32_t tickstart;

  /* Check Null pointer */
  if (RCC_ClkInitStruct == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RCC_CLOCKTYPE(RCC_ClkInitStruct->ClockType));
  assert_param(IS_FLASH_LATENCY(FLatency));

  /* To correctly read data from FLASH memory, the number of wait states (LATENCY)
    must be correctly programmed according to the frequency of the FLASH clock
    (HCLK3) and the supply voltage of the device. */

  /* Increasing the number of wait states because of higher CPU frequency */
  if (FLatency > __HAL_FLASH_GET_LATENCY())
  {
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    __HAL_FLASH_SET_LATENCY(FLatency);

    /* Get Start Tick*/
    tickstart = HAL_GetTick();

    /* Check that the new number of wait states is taken into account to access the Flash
       memory by reading the FLASH_ACR register */
    while (__HAL_FLASH_GET_LATENCY() != FLatency)
    {
      if ((HAL_GetTick() - tickstart) > LATENCY_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /*-------------------------- HCLK1 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_HCLK) == RCC_CLOCKTYPE_HCLK)
  {
    assert_param(IS_RCC_HCLKx(RCC_ClkInitStruct->AHBCLKDivider));
    LL_RCC_SetAHBPrescaler(RCC_ClkInitStruct->AHBCLKDivider);

    /* HCLK1 prescaler flag when value applied */
    tickstart = HAL_GetTick();
    while (LL_RCC_IsActiveFlag_HPRE() == 0U)
    {
      if ((HAL_GetTick() - tickstart) > PRESCALER_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

#if defined(DUAL_CORE)
  /*-------------------------- HCLK2 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_HCLK2) == RCC_CLOCKTYPE_HCLK2)
  {
    assert_param(IS_RCC_HCLKx(RCC_ClkInitStruct->AHBCLK2Divider));
    LL_C2_RCC_SetAHBPrescaler(RCC_ClkInitStruct->AHBCLK2Divider);

    /* HCLK2 prescaler flag when value applied */
    tickstart = HAL_GetTick();
    while (LL_RCC_IsActiveFlag_C2HPRE() == 0U)
    {
      if ((HAL_GetTick() - tickstart) > PRESCALER_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }
#endif /* DUAL_CORE */

  /*-------------------------- HCLK3 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_HCLK3) == RCC_CLOCKTYPE_HCLK3)
  {
    assert_param(IS_RCC_HCLKx(RCC_ClkInitStruct->AHBCLK3Divider));
    LL_RCC_SetAHB3Prescaler(RCC_ClkInitStruct->AHBCLK3Divider);

    /* AHB shared prescaler flag when value applied */
    tickstart = HAL_GetTick();
    while (LL_RCC_IsActiveFlag_SHDHPRE() == 0U)
    {
      if ((HAL_GetTick() - tickstart) > PRESCALER_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /*-------------------------- PCLK1 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK1) == RCC_CLOCKTYPE_PCLK1)
  {
    assert_param(IS_RCC_PCLKx(RCC_ClkInitStruct->APB1CLKDivider));
    LL_RCC_SetAPB1Prescaler(RCC_ClkInitStruct->APB1CLKDivider);

    /* APB1 prescaler flag when value applied */
    tickstart = HAL_GetTick();
    while (LL_RCC_IsActiveFlag_PPRE1() == 0U)
    {
      if ((HAL_GetTick() - tickstart) > PRESCALER_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /*-------------------------- PCLK2 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK2) == RCC_CLOCKTYPE_PCLK2)
  {
    assert_param(IS_RCC_PCLKx(RCC_ClkInitStruct->APB2CLKDivider));
    LL_RCC_SetAPB2Prescaler((RCC_ClkInitStruct->APB2CLKDivider) << 3U);

    /* APB2 prescaler flag when value applied */
    tickstart = HAL_GetTick();
    while (LL_RCC_IsActiveFlag_PPRE2() == 0U)
    {
      if ((HAL_GetTick() - tickstart) > PRESCALER_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /*------------------------- SYSCLK Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_SYSCLK) == RCC_CLOCKTYPE_SYSCLK)
  {
    assert_param(IS_RCC_SYSCLKSOURCE(RCC_ClkInitStruct->SYSCLKSource));

    /* HSE is selected as System Clock Source */
    if (RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HSE)
    {
      /* Check the HSE ready flag */
      if (LL_RCC_HSE_IsReady() == 0U)
      {
        return HAL_ERROR;
      }
    }
    /* PLL is selected as System Clock Source */
    else if (RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_PLLCLK)
    {
      /* Check the PLL ready flag */
      if (LL_RCC_PLL_IsReady() == 0U)
      {
        return HAL_ERROR;
      }
    }
    /* MSI is selected as System Clock Source */
    else if (RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_MSI)
    {
      /* Check the MSI ready flag */
      if (LL_RCC_MSI_IsReady() == 0U)
      {
        return HAL_ERROR;
      }
    }
    /* HSI is selected as System Clock Source */
    else
    {
      /* Check the HSI ready flag */
      if (LL_RCC_HSI_IsReady() == 0U)
      {
        return HAL_ERROR;
      }

    }

    /* apply system clock switch */
    LL_RCC_SetSysClkSource(RCC_ClkInitStruct->SYSCLKSource);

    /* Get Start Tick*/
    tickstart = HAL_GetTick();

    /* check system clock source switch status */
    while (__HAL_RCC_GET_SYSCLK_SOURCE() != (RCC_ClkInitStruct->SYSCLKSource << RCC_CFGR_SWS_Pos))
    {
      if ((HAL_GetTick() - tickstart) > CLOCKSWITCH_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* Decreasing the number of wait states because of lower CPU frequency */
  if (FLatency < __HAL_FLASH_GET_LATENCY())
  {
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    __HAL_FLASH_SET_LATENCY(FLatency);

    /* Get Start Tick*/
    tickstart = HAL_GetTick();

    /* Check that the new number of wait states is taken into account to access the Flash
    memory by reading the FLASH_ACR register */
    while (__HAL_FLASH_GET_LATENCY() != FLatency)
    {
      if ((HAL_GetTick() - tickstart) > LATENCY_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /*--------------------------------------------------------------------------*/

  /* Update the SystemCoreClock global variable */
  SystemCoreClock = HAL_RCC_GetHCLKFreq();

  /* Configure the source of time base considering new system clocks settings*/
  return HAL_InitTick(uwTickPrio);
}

/**
  * @}
  */

/** @defgroup RCC_Exported_Functions_Group2 Peripheral Control functions
  *  @brief   RCC clocks control functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to:

    (+) Output clock to MCO pin.
    (+) Retrieve current clock frequencies.
    (+) Enable the Clock Security System.
    (+) HSE CSS Interrupt handler.
    (+) Default HSE CSS callback function.

@endverbatim
  * @{
  */

/**
  * @brief  Select the clock source to output on MCO1 pin(PA8).
  * @note   PA8 should be configured in alternate function mode.
  * @param  RCC_MCOx  specifies the output direction for the clock source.
  *            @arg @ref RCC_MCO1  Clock source to output on MCO1 pin(PA8)
  * @param  RCC_MCOSource  specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCO1SOURCE_NOCLOCK  MCO output disabled, no clock on MCO
  *            @arg @ref RCC_MCO1SOURCE_SYSCLK  system  clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_MSI  MSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSI  HSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_HSE  HSE clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_PLLCLK  main PLLR clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSI  LSI clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_LSE  LSE clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_PLLPCLK  main PLLP clock selected as MCO source
  *            @arg @ref RCC_MCO1SOURCE_PLLQCLK  main PLLQ clock selected as MCO source
  * @param  RCC_MCODiv  specifies the MCO prescaler.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MCODIV_1  no division applied to MCO clock
  *            @arg @ref RCC_MCODIV_2  division by 2 applied to MCO clock
  *            @arg @ref RCC_MCODIV_4  division by 4 applied to MCO clock
  *            @arg @ref RCC_MCODIV_8  division by 8 applied to MCO clock
  *            @arg @ref RCC_MCODIV_16  division by 16 applied to MCO clock
  * @retval None
  */
void HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Check the parameters */
  assert_param(IS_RCC_MCO(RCC_MCOx));
  assert_param(IS_RCC_MCODIV(RCC_MCODiv));
  assert_param(IS_RCC_MCO1SOURCE(RCC_MCOSource));

  /* MCO1 Clock Enable */
  __MCO1_CLK_ENABLE();

  /* Configure the MCO1 pin in alternate function mode */
  GPIO_InitStruct.Pin       = MCO1_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(MCO1_GPIO_PORT, &GPIO_InitStruct);

  /* Configure the microcontroller clock output (MCO) */
  LL_RCC_ConfigMCO(RCC_MCOSource, RCC_MCODiv);
}

/**
  * @brief  Return the SYSCLK frequency.
  *
  * @note   The system  computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source:
  * @note     If SYSCLK source is MSI, function returns values based on MSI range
  * @note     If SYSCLK source is HSI, function returns values based on HSI_VALUE(*)
  * @note     If SYSCLK source is HSE, function returns values based on HSE_VALUE(**)
  * @note     If SYSCLK source is PLL, function returns values based on HSE_VALUE(**),
  *           HSI_VALUE(*) or MSI Value multiplied/divided by the PLL factors.
  * @note     (*) HSI_VALUE is a constant defined in stm32wlxx_hal_conf.h file (default value
  *               16 MHz) but the real value may vary depending on the variations
  *               in voltage and temperature.
  * @note     (**) HSE_VALUE is a constant defined in stm32wlxx_hal_conf.h file (default value
  *                32 MHz), user has to ensure that HSE_VALUE is same as the real
  *                frequency of the crystal used. Otherwise, this function may
  *                have wrong result.
  *
  * @note   The result of this function could be not correct when using fractional
  *         value for HSE crystal.
  *
  * @note   This function can be used by the user application to compute the
  *         baudrate for the communication peripherals or configure other parameters.
  *
  * @note   Each time SYSCLK changes, this function must be called to update the
  *         right SYSCLK value. Otherwise, any configuration based on this function will be incorrect.
  *
  *
  * @retval SYSCLK frequency
  */
uint32_t HAL_RCC_GetSysClockFreq(void)
{
  uint32_t sysclk_source;
  uint32_t pllsource;
  uint32_t sysclockfreq = 0U;
  uint32_t msifreq = 0U;
  uint32_t pllinputfreq;

  sysclk_source = __HAL_RCC_GET_SYSCLK_SOURCE();
  pllsource = __HAL_RCC_GET_PLL_OSCSOURCE();

  if ((sysclk_source == RCC_SYSCLKSOURCE_STATUS_MSI) ||
      ((sysclk_source == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && (pllsource == RCC_PLLSOURCE_MSI)))
  {
    /* MSI or PLL with MSI source used as system clock source */
    /*Retrieve MSI frequency range in HZ*/
    msifreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                     ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                      LL_RCC_MSI_GetRange() :
                                      LL_RCC_MSI_GetRangeAfterStandby()));

    /* Get SYSCLK source */
    if (sysclk_source == RCC_SYSCLKSOURCE_STATUS_MSI)
    {
      /* MSI used as system clock source */
      sysclockfreq = msifreq;
    }
  }
  else if (sysclk_source == RCC_SYSCLKSOURCE_STATUS_HSI)
  {
    /* HSI used as system clock source */
    sysclockfreq = HSI_VALUE;
  }
  else if (sysclk_source == RCC_SYSCLKSOURCE_STATUS_HSE)
  {
    /* HSE used as system clock source */
    if (LL_RCC_HSE_IsEnabledDiv2() == 1U)
    {
      sysclockfreq = HSE_VALUE / 2U;
    }
    else
    {
      sysclockfreq = HSE_VALUE;
    }
  }
  else
  {
    /* Nothing to do */
  }

  if (__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK)
  {
    /* PLL used as system clock  source */
    pllsource = LL_RCC_PLL_GetMainSource();

    switch (pllsource)
    {
      case RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
        pllinputfreq = HSI_VALUE;
        break;
      case RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
        if (LL_RCC_HSE_IsEnabledDiv2() == 1U)
        {
          pllinputfreq = HSE_VALUE / 2U;
        }
        else
        {
          pllinputfreq = HSE_VALUE;
        }
        break;
      case RCC_PLLSOURCE_MSI:  /* MSI used as PLL clock source */
      default:
        pllinputfreq = msifreq;
        break;
    }
    sysclockfreq = __LL_RCC_CALC_PLLCLK_FREQ(pllinputfreq, LL_RCC_PLL_GetDivider(),
                                             LL_RCC_PLL_GetN(), LL_RCC_PLL_GetR());
  }

  return sysclockfreq;
}

/**
  * @brief  Return the HCLK frequency.
  * @retval HCLK frequency in Hz
  */
uint32_t HAL_RCC_GetHCLKFreq(void)
{
  /* Get SysClock and Compute HCLK1 frequency --------------------------------*/
  return ((uint32_t)(__LL_RCC_CALC_HCLK1_FREQ(HAL_RCC_GetSysClockFreq(), LL_RCC_GetAHBPrescaler())));
}

#if defined(DUAL_CORE)
/**
  * @brief  Return the HCLK2 frequency.
  * @retval HCLK2 frequency in Hz
  */
uint32_t HAL_RCC_GetHCLK2Freq(void)
{
  /* Get SysClock and Compute HCLK2 frequency --------------------------------*/
  return ((uint32_t)(__LL_RCC_CALC_HCLK2_FREQ(HAL_RCC_GetSysClockFreq(), LL_C2_RCC_GetAHBPrescaler())));
}
#endif /* DUAL_CORE */

/**
  * @brief  Return the HCLK3 frequency.
  * @retval HCLK3 frequency in Hz
  */
uint32_t HAL_RCC_GetHCLK3Freq(void)
{
  /* Get SysClock and Compute AHB3 frequency ---------------------------------*/
  return ((uint32_t)(__LL_RCC_CALC_HCLK3_FREQ(HAL_RCC_GetSysClockFreq(), LL_RCC_GetAHB3Prescaler())));
}

/**
  * @brief  Return the PCLK1 frequency.
  * @retval PCLK1 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK1Freq(void)
{
  /* Get HCLK source and Compute PCLK1 frequency -----------------------------*/
  return ((uint32_t)(__LL_RCC_CALC_PCLK1_FREQ(HAL_RCC_GetHCLKFreq(), LL_RCC_GetAPB1Prescaler())));
}

/**
  * @brief  Return the PCLK2 frequency.
  * @retval PCLK2 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK2Freq(void)
{
  /* Get HCLK source and Compute PCLK2 frequency -----------------------------*/
  return ((uint32_t)(__LL_RCC_CALC_PCLK2_FREQ(HAL_RCC_GetHCLKFreq(), LL_RCC_GetAPB2Prescaler())));
}

/**
  * @brief  Configure the RCC_OscInitStruct according to the internal
  *         RCC configuration registers.
  * @param  RCC_OscInitStruct  pointer to an RCC_OscInitTypeDef structure that
  *         will be configured.
  * @retval None
  */
void HAL_RCC_GetOscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct)
{
  /* Check the parameters */
  if (RCC_OscInitStruct != NULL)
  {
    /* Set all possible values for the Oscillator type parameter ---------------*/
    RCC_OscInitStruct->OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_MSI | \
                                        RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_LSI;


    /* Get the HSE configuration -----------------------------------------------*/
    if ((RCC->CR & RCC_CR_HSEBYPPWR) == RCC_CR_HSEBYPPWR)
    {
      RCC_OscInitStruct->HSEState = RCC_HSE_BYPASS_PWR;
    }
    else if ((RCC->CR & RCC_CR_HSEON) == RCC_CR_HSEON)
    {
      RCC_OscInitStruct->HSEState = RCC_HSE_ON;
    }
    else
    {
      RCC_OscInitStruct->HSEState = RCC_HSE_OFF;
    }

    if ((RCC->CR & RCC_CR_HSEPRE) == RCC_CR_HSEPRE)
    {
      RCC_OscInitStruct->HSEDiv = RCC_HSE_DIV2;
    }
    else
    {
      RCC_OscInitStruct->HSEDiv = RCC_HSE_DIV1;
    }

    /* Get the MSI configuration -----------------------------------------------*/
    if ((RCC->CR & RCC_CR_MSION) == RCC_CR_MSION)
    {
      RCC_OscInitStruct->MSIState = RCC_MSI_ON;
    }
    else
    {
      RCC_OscInitStruct->MSIState = RCC_MSI_OFF;
    }
    RCC_OscInitStruct->MSICalibrationValue  = LL_RCC_MSI_GetCalibTrimming();
    RCC_OscInitStruct->MSIClockRange        = LL_RCC_MSI_GetRange();

    /* Get the HSI configuration -----------------------------------------------*/
    if ((RCC->CR & RCC_CR_HSION) == RCC_CR_HSION)
    {
      RCC_OscInitStruct->HSIState = RCC_HSI_ON;
    }
    else
    {
      RCC_OscInitStruct->HSIState = RCC_HSI_OFF;
    }

    RCC_OscInitStruct->HSICalibrationValue = LL_RCC_HSI_GetCalibTrimming();

    /* Get the LSE configuration -----------------------------------------------*/
    if ((RCC->BDCR & RCC_BDCR_LSEON) == RCC_BDCR_LSEON)
    {
      if ((RCC->BDCR & RCC_BDCR_LSEBYP) == RCC_BDCR_LSEBYP)
      {
        if ((RCC->BDCR & RCC_BDCR_LSESYSEN) == RCC_BDCR_LSESYSEN)
        {
          RCC_OscInitStruct->LSEState = RCC_LSE_BYPASS;
        }
        else
        {
          RCC_OscInitStruct->LSEState = RCC_LSE_BYPASS_RTC_ONLY;
        }
      }
      else if ((RCC->BDCR & RCC_BDCR_LSESYSEN) == RCC_BDCR_LSESYSEN)
      {
        RCC_OscInitStruct->LSEState = RCC_LSE_ON;
      }
      else
      {
        RCC_OscInitStruct->LSEState = RCC_LSE_ON_RTC_ONLY;
      }
    }
    else
    {
      RCC_OscInitStruct->LSEState = RCC_LSE_OFF;
    }

    /* Get the LSI configuration -----------------------------------------------*/
    if (((RCC->CSR & RCC_CSR_LSION) == RCC_CSR_LSION))
    {
      RCC_OscInitStruct->LSIState = RCC_LSI_ON;
    }
    else
    {
      RCC_OscInitStruct->LSIState = RCC_LSI_OFF;
    }

    if ((RCC->CSR & RCC_CSR_LSIPRE) == RCC_CSR_LSIPRE)
    {
      RCC_OscInitStruct->LSIDiv = RCC_LSI_DIV128;
    }
    else
    {
      RCC_OscInitStruct->LSIDiv = RCC_LSI_DIV1;
    }

    /* Get the PLL configuration -----------------------------------------------*/
    if ((RCC->CR & RCC_CR_PLLON) == RCC_CR_PLLON)
    {
      RCC_OscInitStruct->PLL.PLLState = RCC_PLL_ON;
    }
    else
    {
      RCC_OscInitStruct->PLL.PLLState = RCC_PLL_OFF;
    }
    RCC_OscInitStruct->PLL.PLLSource = LL_RCC_PLL_GetMainSource();
    RCC_OscInitStruct->PLL.PLLM      = LL_RCC_PLL_GetDivider();
    RCC_OscInitStruct->PLL.PLLN      = LL_RCC_PLL_GetN();
    RCC_OscInitStruct->PLL.PLLP      = LL_RCC_PLL_GetP();
    RCC_OscInitStruct->PLL.PLLQ      = LL_RCC_PLL_GetQ();
    RCC_OscInitStruct->PLL.PLLR      = LL_RCC_PLL_GetR();
  }
}

/**
  * @brief  Configure the RCC_ClkInitStruct according to the internal
  *         RCC configuration registers.
  * @param  RCC_ClkInitStruct Pointer to a @ref RCC_ClkInitTypeDef structure that
  *                           will be configured.
  * @param  pFLatency         Pointer to the Flash Latency variable.
  * @retval None
  */
void HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t *pFLatency)
{
  /* Check the parameters */
  if ((RCC_ClkInitStruct != NULL) && (pFLatency != NULL))
  {
    /* Set all possible values for the Clock type parameter --------------------*/
    RCC_ClkInitStruct->ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 \
                                    | RCC_CLOCKTYPE_PCLK2  | RCC_CLOCKTYPE_HCLK3);
#if defined(DUAL_CORE)
    RCC_ClkInitStruct->ClockType |= RCC_CLOCKTYPE_HCLK2;
#endif  /* DUAL_CORE */

    /* Get the SYSCLK configuration --------------------------------------------*/
    RCC_ClkInitStruct->SYSCLKSource = LL_RCC_GetSysClkSource();

    /* Get the HCLK configuration ----------------------------------------------*/
    RCC_ClkInitStruct->AHBCLKDivider = LL_RCC_GetAHBPrescaler();

    /* Get the APB1 configuration ----------------------------------------------*/
    RCC_ClkInitStruct->APB1CLKDivider = LL_RCC_GetAPB1Prescaler();

    /* Get the APB2 configuration ----------------------------------------------*/
    RCC_ClkInitStruct->APB2CLKDivider = LL_RCC_GetAPB2Prescaler();

#if defined(DUAL_CORE)
    /* Get the AHBCLK2Divider configuration ------------------------------------*/
    RCC_ClkInitStruct->AHBCLK2Divider = LL_C2_RCC_GetAHBPrescaler();
#endif  /* DUAL_CORE */

    /* Get the AHBCLK3Divider configuration ------------------------------------*/
    RCC_ClkInitStruct->AHBCLK3Divider = LL_RCC_GetAHB3Prescaler();

    /* Get the Flash Wait State (Latency) configuration ------------------------*/
    *pFLatency = __HAL_FLASH_GET_LATENCY();
  }
}

/**
  * @brief  Enable the Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure (Clock Security System Interrupt, CSSI),
  *         allowing the MCU to perform rescue operations. The CSSI is linked to
  *         CPU1 and CPU2 NMI (Non-Maskable Interrupt) exception vector.
  * @note   The Clock Security System can only be cleared by reset.
  * @retval None
  */
void HAL_RCC_EnableCSS(void)
{
  LL_RCC_HSE_EnableCSS();
}

/**
  * @brief Handle the RCC HSE Clock Security System interrupt request.
  * @note  This API should be called under the NMI_Handler().
  * @retval None
  */
void HAL_RCC_NMI_IRQHandler(void)
{
  /* Check RCC CSSF interrupt flag  */
  if (__HAL_RCC_GET_IT(RCC_IT_HSECSS))
  {
    /* RCC Clock Security System interrupt user callback */
    HAL_RCC_CSSCallback();

    /* Clear RCC CSS pending bit */
    __HAL_RCC_CLEAR_IT(RCC_IT_HSECSS);
  }
}

/**
  * @brief Handle the RCC HSE Clock Security System interrupt callback.
  * @retval none
  */
__weak void HAL_RCC_CSSCallback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the @ref HAL_RCC_CSSCallback should be implemented in the user file
   */
}

/**
  * @}
  */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @addtogroup RCC_Private_Functions
  * @{
  */


/**
  * @brief  Update number of Flash wait states in line with MSI range and current
            voltage range.
  * @param  MSI_Range  MSI range value from @ref RCC_MSIRANGE_0 to @ref RCC_MSIRANGE_11
  * @retval HAL status
  */
static HAL_StatusTypeDef RCC_SetFlashLatencyFromMSIRange(uint32_t MSI_Range)
{
  uint32_t flash_clksrcfreq;
  uint32_t msifreq;

  /* MSI frequency range in Hz */
  msifreq           = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSIRANGESEL_RUN, MSI_Range);
  flash_clksrcfreq  = __LL_RCC_CALC_HCLK3_FREQ(msifreq, LL_RCC_GetAHB3Prescaler());

  return RCC_SetFlashLatency((flash_clksrcfreq / MEGA_HZ), HAL_PWREx_GetVoltageRange());
}


/**
  * @brief  Update number of Flash wait states.
  * @param  Flash_ClkSrcFreq  Flash Clock Source (in MHz)
  * @param  VCORE_Voltage     Current Vcore voltage
  *          This parameter can be one of the following values:
  *            @arg PWR_REGULATOR_VOLTAGE_SCALE1   Regulator voltage output range 1 mode
  *            @arg PWR_REGULATOR_VOLTAGE_SCALE2   Regulator voltage output range 2 mode
  * @retval HAL status
  */
static HAL_StatusTypeDef RCC_SetFlashLatency(uint32_t Flash_ClkSrcFreq, uint32_t VCORE_Voltage)
{
  /* Flash Clock source (HCLK3) range in MHz for VCORE range1 */
  const uint16_t FLASH_CLK_SRC_RANGE_VOS1[] = {18, 36, 48};

  /* Flash Clock source (HCLK3) range in MHz for VCORE range2 */
  const uint16_t FLASH_CLK_SRC_RANGE_VOS2[] = {6, 12, 16};

  /* Flash Latency range */
  const uint32_t FLASH_LATENCY_RANGE[] = {FLASH_LATENCY_0, FLASH_LATENCY_1, FLASH_LATENCY_2};

  uint32_t latency   = FLASH_LATENCY_0;  /* default value 0WS */
  uint32_t tickstart;

  if (VCORE_Voltage == PWR_REGULATOR_VOLTAGE_SCALE1)
  {
    for (uint32_t index = 0; index < __COUNTOF(FLASH_CLK_SRC_RANGE_VOS1); index++)
    {
      if (Flash_ClkSrcFreq <= FLASH_CLK_SRC_RANGE_VOS1[index])
      {
        latency = FLASH_LATENCY_RANGE[index];
        break;
      }
    }
  }
  else  /* PWR_REGULATOR_VOLTAGE_SCALE2 */
  {
    for (uint32_t index = 0; index < __COUNTOF(FLASH_CLK_SRC_RANGE_VOS2); index++)
    {
      if (Flash_ClkSrcFreq <= FLASH_CLK_SRC_RANGE_VOS2[index])
      {
        latency = FLASH_LATENCY_RANGE[index];
        break;
      }
    }
  }

  __HAL_FLASH_SET_LATENCY(latency);

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Check that the new number of wait states is taken into account to access the Flash
     memory by reading the FLASH_ACR register */
  while (__HAL_FLASH_GET_LATENCY() != latency)
  {
    if ((HAL_GetTick() - tickstart) > LATENCY_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }
  return HAL_OK;
}

/**
  * @}
  */

#endif /* HAL_RCC_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
