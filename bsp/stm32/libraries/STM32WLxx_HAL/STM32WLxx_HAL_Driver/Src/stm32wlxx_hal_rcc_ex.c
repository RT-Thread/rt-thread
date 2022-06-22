/**
  ******************************************************************************
  * @file    stm32wlxx_hal_rcc_ex.c
  * @author  MCD Application Team
  * @brief   Extended RCC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities RCC extended peripheral:
  *           + Extended Peripheral Control functions
  *           + Extended Clock management functions
  *           + Extended Clock Recovery System Control functions
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

/** @defgroup RCCEx RCCEx
  * @brief RCC Extended HAL module driver
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/** @defgroup RCCEx_Private_Constants RCCEx Private Constants
  * @{
  */
#define __LSCO1_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define LSCO1_GPIO_PORT        GPIOA
#define LSCO1_PIN              GPIO_PIN_2
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCCEx_Private_Functions RCCEx Private Functions
  * @{
  */
static uint32_t          RCC_PLL_GetFreqDomain_P(void);
static uint32_t          RCC_PLL_GetFreqDomain_Q(void);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup RCCEx_Exported_Functions RCCEx Exported Functions
  * @{
  */

/** @defgroup RCCEx_Exported_Functions_Group1 Extended Peripheral Control functions
  *  @brief  Extended Peripheral Control functions
  *
@verbatim
 ===============================================================================
                ##### Extended Peripheral Control functions  #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the RCC Clocks
    frequencies.
    [..]
    (@) Important note: Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to
        select the RTC clock source; in this case the Backup domain will be reset in
        order to modify the RTC Clock source, as consequence RTC registers (including
        the backup registers) and RCC_BDCR register are set to their reset values.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the RCC extended peripherals clocks according to the specified
  *         parameters in the @ref RCC_PeriphCLKInitTypeDef.
  * @param  PeriphClkInit  pointer to a @ref RCC_PeriphCLKInitTypeDef structure that
  *         contains a field PeriphClockSelection which can be a combination of the following values:
  *            @arg @ref RCC_PERIPHCLK_USART1   USART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART2   USART2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPUART1  LPUART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C1     I2C1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C2     I2C2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C3     I2C3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2S2     I2S2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM1   LPTIM1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM2   LPTIM2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM3   LPTIM3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_RNG      RNG peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADC      ADC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_RTC      RTC peripheral clock
  *
  * @note   Care must be taken when @ref HAL_RCCEx_PeriphCLKConfig() is used to select
  *         the RTC clock source: in this case the access to Backup domain is enabled.
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tmpregister = 0;
  uint32_t tickstart;
  HAL_StatusTypeDef ret = HAL_OK;   /* Intermediate status */
  HAL_StatusTypeDef status  = HAL_OK;   /* Final status */

  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClkInit->PeriphClockSelection));

  /*-------------------------- RTC clock source configuration ----------------------*/
  if ((PeriphClkInit->PeriphClockSelection & RCC_PERIPHCLK_RTC) == RCC_PERIPHCLK_RTC)
  {

    /* Check for RTC Parameters used to output RTCCLK */
    assert_param(IS_RCC_RTCCLKSOURCE(PeriphClkInit->RTCClockSelection));


    /* Enable write access to Backup domain */
    HAL_PWR_EnableBkUpAccess();

    /* Wait for Backup domain Write protection disable */
    tickstart = HAL_GetTick();

    while (!(READ_BIT(PWR->CR1, PWR_CR1_DBP) == (PWR_CR1_DBP)))
    {
      if ((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
      {
        ret = HAL_TIMEOUT;
        break;
      }
    }

    if (ret == HAL_OK)
    {
      /* Reset the Backup domain only if the RTC Clock source selection is modified */
      if (LL_RCC_GetRTCClockSource() != PeriphClkInit->RTCClockSelection)
      {
        /* Store the content of BDCR register before the reset of Backup Domain */
        tmpregister = READ_BIT(RCC->BDCR, ~(RCC_BDCR_RTCSEL));

        /* RTC Clock selection can be changed only if the Backup Domain is reset */
        __HAL_RCC_BACKUPRESET_FORCE();
        __HAL_RCC_BACKUPRESET_RELEASE();

        /* Restore the Content of BDCR register */
        RCC->BDCR = tmpregister;
      }

      /* Wait for LSE reactivation if LSE was enable prior to Backup Domain reset */
      if (HAL_IS_BIT_SET(tmpregister, RCC_BDCR_LSERDY))
      {
        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till LSE is ready */
        while (LL_RCC_LSE_IsReady() != 1U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            ret = HAL_TIMEOUT;
            break;
          }
        }
      }

      if (ret == HAL_OK)
      {
        /* Apply new RTC clock source selection */
        __HAL_RCC_RTC_CONFIG(PeriphClkInit->RTCClockSelection);
      }
      else
      {
        /* set overall return value */
        status = ret;
      }
    }
    else
    {
      /* set overall return value */
      status = ret;
    }

  }

  /*-------------------- USART1 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART1) == RCC_PERIPHCLK_USART1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART1CLKSOURCE(PeriphClkInit->Usart1ClockSelection));

    /* Configure the USART1 clock source */
    __HAL_RCC_USART1_CONFIG(PeriphClkInit->Usart1ClockSelection);
  }

  /*-------------------- USART2 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART2) == RCC_PERIPHCLK_USART2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART2CLKSOURCE(PeriphClkInit->Usart2ClockSelection));

    /* Configure the USART2 clock source */
    __HAL_RCC_USART2_CONFIG(PeriphClkInit->Usart2ClockSelection);
  }

  /*-------------------- LPUART1 clock source configuration ------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPUART1CLKSOURCE(PeriphClkInit->Lpuart1ClockSelection));

    /* Configure the LPUAR1 clock source */
    __HAL_RCC_LPUART1_CONFIG(PeriphClkInit->Lpuart1ClockSelection);
  }

  /*-------------------- LPTIM1 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM1) == (RCC_PERIPHCLK_LPTIM1))
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM1CLKSOURCE(PeriphClkInit->Lptim1ClockSelection));

    /* Configure the LPTIM1 clock source */
    __HAL_RCC_LPTIM1_CONFIG(PeriphClkInit->Lptim1ClockSelection);
  }

  /*-------------------- LPTIM2 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM2) == (RCC_PERIPHCLK_LPTIM2))
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM2CLKSOURCE(PeriphClkInit->Lptim2ClockSelection));

    /* Configure the LPTIM2 clock source */
    __HAL_RCC_LPTIM2_CONFIG(PeriphClkInit->Lptim2ClockSelection);
  }

  /*-------------------- LPTIM3 clock source configuration -------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM3) == (RCC_PERIPHCLK_LPTIM3))
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM3CLKSOURCE(PeriphClkInit->Lptim3ClockSelection));

    /* Configure the LPTIM3 clock source */
    __HAL_RCC_LPTIM3_CONFIG(PeriphClkInit->Lptim3ClockSelection);
  }

  /*-------------------- I2C1 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C1) == RCC_PERIPHCLK_I2C1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C1CLKSOURCE(PeriphClkInit->I2c1ClockSelection));

    /* Configure the I2C1 clock source */
    __HAL_RCC_I2C1_CONFIG(PeriphClkInit->I2c1ClockSelection);
  }

  /*-------------------- I2C2 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C2) == RCC_PERIPHCLK_I2C2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C2CLKSOURCE(PeriphClkInit->I2c2ClockSelection));

    /* Configure the I2C2 clock source */
    __HAL_RCC_I2C2_CONFIG(PeriphClkInit->I2c2ClockSelection);
  }

  /*-------------------- I2C3 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C3) == RCC_PERIPHCLK_I2C3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C3CLKSOURCE(PeriphClkInit->I2c3ClockSelection));

    /* Configure the I2C3 clock source */
    __HAL_RCC_I2C3_CONFIG(PeriphClkInit->I2c3ClockSelection);
  }

  /*-------------------- I2S2 clock source configuration ---------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S2) == (RCC_PERIPHCLK_I2S2))
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2S2CLKSOURCE(PeriphClkInit->I2s2ClockSelection));

    /* Configure the I2S2 clock source */
    __HAL_RCC_I2S2_CONFIG(PeriphClkInit->I2s2ClockSelection);

    if (PeriphClkInit->I2s2ClockSelection == RCC_I2S2CLKSOURCE_PLL)
    {
      /* Enable RCC_PLL_I2S2CLK output */
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_I2S2CLK);
    }
  }

  /*-------------------- RNG clock source configuration ----------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RNG) == (RCC_PERIPHCLK_RNG))
  {
    assert_param(IS_RCC_RNGCLKSOURCE(PeriphClkInit->RngClockSelection));
    __HAL_RCC_RNG_CONFIG(PeriphClkInit->RngClockSelection);

    if (PeriphClkInit->RngClockSelection == RCC_RNGCLKSOURCE_PLL)
    {
      /* Enable RCC_PLL_RNGCLK output */
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_RNGCLK);
    }
  }

  /*-------------------- ADC clock source configuration ----------------------*/
  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADC) == RCC_PERIPHCLK_ADC)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADCCLKSOURCE(PeriphClkInit->AdcClockSelection));

    /* Configure the ADC interface clock source */
    __HAL_RCC_ADC_CONFIG(PeriphClkInit->AdcClockSelection);

    if (PeriphClkInit->AdcClockSelection == RCC_ADCCLKSOURCE_PLL)
    {
      /* Enable RCC_PLL_RNGCLK output */
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_ADCCLK);
    }
  }

  return status;
}


/**
  * @brief  Get the RCC_ClkInitStruct according to the internal RCC configuration registers.
  * @param  PeriphClkInit  pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         returns the configuration information for the Extended Peripherals
  *         clocks(LPTIM1, LPTIM2, LPTIM3, I2C1, I2C2, I2C3, I2S2, LPUART1,
  *         USART1, USART2, RTC, ADC, RNG).
  * @retval None
  */
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  /* Set all possible values for the extended clock type parameter------------*/
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_I2S2    | \
                                        RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | RCC_PERIPHCLK_I2C3    | \
                                        RCC_PERIPHCLK_LPTIM1 | RCC_PERIPHCLK_LPTIM2 | RCC_PERIPHCLK_LPTIM3  | \
                                        RCC_PERIPHCLK_RNG    | RCC_PERIPHCLK_ADC    | RCC_PERIPHCLK_RTC     | \
                                        RCC_PERIPHCLK_LPUART1;

  /* Get the USART1 clock source ---------------------------------------------*/
  PeriphClkInit->Usart1ClockSelection   = __HAL_RCC_GET_USART1_SOURCE();

  /* Get the USART2 clock source ---------------------------------------------*/
  PeriphClkInit->Usart2ClockSelection  = __HAL_RCC_GET_USART2_SOURCE();

  /* Get the I2S2 clock source -----------------------------------------------*/
  PeriphClkInit->I2s2ClockSelection  = __HAL_RCC_GET_I2S2_SOURCE();

  /* Get the LPUART1 clock source --------------------------------------------*/
  PeriphClkInit->Lpuart1ClockSelection  = __HAL_RCC_GET_LPUART1_SOURCE();

  /* Get the I2C1 clock source -----------------------------------------------*/
  PeriphClkInit->I2c1ClockSelection     = __HAL_RCC_GET_I2C1_SOURCE();

  /* Get the I2C2 clock source -----------------------------------------------*/
  PeriphClkInit->I2c2ClockSelection     = __HAL_RCC_GET_I2C2_SOURCE();

  /* Get the I2C3 clock source -----------------------------------------------*/
  PeriphClkInit->I2c3ClockSelection     = __HAL_RCC_GET_I2C3_SOURCE();

  /* Get the LPTIM1 clock source ---------------------------------------------*/
  PeriphClkInit->Lptim1ClockSelection   = __HAL_RCC_GET_LPTIM1_SOURCE();

  /* Get the LPTIM2 clock source ---------------------------------------------*/
  PeriphClkInit->Lptim2ClockSelection   = __HAL_RCC_GET_LPTIM2_SOURCE();

  /* Get the LPTIM3 clock source ---------------------------------------------*/
  PeriphClkInit->Lptim3ClockSelection   = __HAL_RCC_GET_LPTIM3_SOURCE();

  /* Get the RTC clock source ------------------------------------------------*/
  PeriphClkInit->RTCClockSelection      = __HAL_RCC_GET_RTC_SOURCE();

  /* Get the RNG clock source ------------------------------------------------*/
  PeriphClkInit->RngClockSelection      = __HAL_RCC_GET_RNG_SOURCE();

  /* Get the ADC clock source ------------------------------------------------*/
  PeriphClkInit->AdcClockSelection      = __HAL_RCC_GET_ADC_SOURCE();

}

/**
  * @brief  Return the peripheral clock frequency for peripherals with clock source
  * @note   Return 0 if peripheral clock identifier not managed by this API
  * @param  PeriphClk  Peripheral clock identifier
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PERIPHCLK_USART1   USART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART2   USART2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPUART1  LPUART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C1     I2C1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C2     I2C2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C3     I2C3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2S2     I2S2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM1   LPTIM1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM2   LPTIM2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM3   LPTIM3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_RNG      RNG peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADC      ADC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_RTC      RTC peripheral clock
  *
  * @retval Frequency in Hz
  */
uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;

  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClk));

  switch (PeriphClk)
  {
    case RCC_PERIPHCLK_RTC:

      /* Get the current RTC source */
      srcclk = LL_RCC_GetRTCClockSource();

      switch (srcclk)
      {
        case LL_RCC_RTC_CLKSOURCE_LSE:                /* LSE clock used as RTC clock source */
          if (LL_RCC_LSE_IsReady() == 1U)
          {
            frequency = LSE_VALUE;
          }
          break;

        case LL_RCC_RTC_CLKSOURCE_LSI:                /* LSI clock used as RTC clock source */
          if (LL_RCC_LSI_IsReady() == 1U)
          {
            if (LL_RCC_LSI_GetPrediv() == LL_RCC_LSI_PREDIV_128)
            {
              frequency = LSI_VALUE / 128U;
            }
            else
            {
              frequency = LSI_VALUE;
            }
          }
          break;

        case LL_RCC_RTC_CLKSOURCE_HSE_DIV32:          /* HSE/32 clock used as RTC clock source */
          frequency = HSE_VALUE / 32U;
          break;

        case LL_RCC_RTC_CLKSOURCE_NONE:               /* No clock used as RTC clock source */
        default:
          /* No clock source, frequency default init at 0 */
          break;
      }
      break;

    case RCC_PERIPHCLK_RNG:

      /* Get the current RTC source */
      srcclk = LL_RCC_GetRNGClockSource(LL_RCC_RNG_CLKSOURCE);

      switch (srcclk)
      {
        case LL_RCC_RNG_CLKSOURCE_PLL:                /* PLL clock used as RNG clock source */
          if (LL_RCC_PLL_IsReady() == 1U)
          {
            frequency = RCC_PLL_GetFreqDomain_Q();
          }
          break;

        case LL_RCC_RNG_CLKSOURCE_LSI:                /* LSI clock used as RNG clock source */
          if (LL_RCC_LSI_IsReady() == 1U)
          {
            if (LL_RCC_LSI_GetPrediv() == LL_RCC_LSI_PREDIV_128)
            {
              frequency = LSI_VALUE / 128U;
            }
            else
            {
              frequency = LSI_VALUE;
            }
          }
          break;

        case LL_RCC_RNG_CLKSOURCE_LSE:                /* LSE clock used as RNG clock source */
          if (LL_RCC_LSE_IsReady() == 1U)
          {
            frequency = LSE_VALUE;
          }
          break;

        case LL_RCC_RNG_CLKSOURCE_MSI:                  /* MSI clock used as RNG clock source */
        default:
          if (LL_RCC_MSI_IsReady() == 1U)
          {
            frequency = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                               ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                LL_RCC_MSI_GetRange() :
                                                LL_RCC_MSI_GetRangeAfterStandby()));
          }
          break;
      }
      break;

    case RCC_PERIPHCLK_USART1:

      /* Get the current USART1 source */
      srcclk = LL_RCC_GetUSARTClockSource(LL_RCC_USART1_CLKSOURCE);

      switch (srcclk)
      {
        case LL_RCC_USART1_CLKSOURCE_SYSCLK:          /* USART1 Clock is System Clock */
          frequency = HAL_RCC_GetSysClockFreq();
          break;

        case LL_RCC_USART1_CLKSOURCE_HSI:             /* USART1 Clock is HSI Osc. */
          if (LL_RCC_HSI_IsReady() == 1U)
          {
            frequency = HSI_VALUE;
          }
          break;

        case LL_RCC_USART1_CLKSOURCE_LSE:             /* USART1 Clock is LSE Osc. */
          if (LL_RCC_LSE_IsReady() == 1U)
          {
            frequency = LSE_VALUE;
          }
          break;

        case LL_RCC_USART1_CLKSOURCE_PCLK2:           /* USART1 Clock is PCLK2 */
        default:
          frequency = __LL_RCC_CALC_PCLK2_FREQ(__LL_RCC_CALC_HCLK1_FREQ(HAL_RCC_GetSysClockFreq(), \
                                                                        LL_RCC_GetAHBPrescaler()), \
                                               LL_RCC_GetAPB2Prescaler());
          break;
      }
      break;

    case RCC_PERIPHCLK_USART2:

      /* Get the current USART2 source */
      srcclk = LL_RCC_GetUSARTClockSource(LL_RCC_USART2_CLKSOURCE);

      switch (srcclk)
      {
        case LL_RCC_USART2_CLKSOURCE_SYSCLK:          /* USART2 Clock is System Clock */
          frequency = HAL_RCC_GetSysClockFreq();
          break;

        case LL_RCC_USART2_CLKSOURCE_HSI:             /* USART2 Clock is HSI Osc. */
          if (LL_RCC_HSI_IsReady() == 1U)
          {
            frequency = HSI_VALUE;
          }
          break;

        case LL_RCC_USART2_CLKSOURCE_LSE:             /* USART2 Clock is LSE Osc. */
          if (LL_RCC_LSE_IsReady() == 1U)
          {
            frequency = LSE_VALUE;
          }
          break;

        case LL_RCC_USART2_CLKSOURCE_PCLK1:           /* USART2 Clock is PCLK1 */
        default:
          frequency = __LL_RCC_CALC_PCLK1_FREQ(__LL_RCC_CALC_HCLK1_FREQ(HAL_RCC_GetSysClockFreq(), \
                                                                        LL_RCC_GetAHBPrescaler()), \
                                               LL_RCC_GetAPB1Prescaler());
          break;
      }
      break;

    case RCC_PERIPHCLK_LPUART1:

      /* Get the current LPUART1 source */
      srcclk = LL_RCC_GetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE);

      switch (srcclk)
      {
        case LL_RCC_LPUART1_CLKSOURCE_SYSCLK:         /* LPUART1 Clock is System Clock */
          frequency = HAL_RCC_GetSysClockFreq();
          break;

        case LL_RCC_LPUART1_CLKSOURCE_HSI:            /* LPUART1 Clock is HSI Osc. */
          if (LL_RCC_HSI_IsReady() == 1U)
          {
            frequency = HSI_VALUE;
          }
          break;

        case LL_RCC_LPUART1_CLKSOURCE_LSE:            /* LPUART1 Clock is LSE Osc. */
          if (LL_RCC_LSE_IsReady() == 1U)
          {
            frequency = LSE_VALUE;
          }
          break;

        case LL_RCC_LPUART1_CLKSOURCE_PCLK1:          /* LPUART1 Clock is PCLK1 */
        default:
          frequency = __LL_RCC_CALC_PCLK1_FREQ(__LL_RCC_CALC_HCLK1_FREQ(HAL_RCC_GetSysClockFreq(), \
                                                                        LL_RCC_GetAHBPrescaler()), \
                                               LL_RCC_GetAPB1Prescaler());
          break;
      }

      break;

    case RCC_PERIPHCLK_ADC:

      /* Get the current ADC source */
      srcclk = LL_RCC_GetADCClockSource(LL_RCC_ADC_CLKSOURCE);

      switch (srcclk)
      {
        case LL_RCC_ADC_CLKSOURCE_HSI:                /* HSI Osc. used as ADC clock source  */
          if (LL_RCC_HSI_IsReady() == 1U)
          {
            frequency = HSI_VALUE;
          }
          break;


        case LL_RCC_ADC_CLKSOURCE_SYSCLK:             /* SYSCLK clock used as ADC clock source */
          frequency = HAL_RCC_GetSysClockFreq();
          break;

        case LL_RCC_ADC_CLKSOURCE_PLL:                /* PLL clock used as ADC clock source */
          if (LL_RCC_PLL_IsReady() == 1U)
          {
            frequency = RCC_PLL_GetFreqDomain_P();
          }
          break;

        case LL_RCC_ADC_CLKSOURCE_NONE:               /* No clock used as ADC clock source */
        default:
          /* No clock source, frequency default init at 0 */
          break;
      }
      break;

    case RCC_PERIPHCLK_I2C1:

      /* Get the current I2C1 source */
      srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C1_CLKSOURCE);

      switch (srcclk)
      {
        case LL_RCC_I2C1_CLKSOURCE_SYSCLK:            /* I2C1 Clock is System Clock */
          frequency = HAL_RCC_GetSysClockFreq();
          break;

        case LL_RCC_I2C1_CLKSOURCE_HSI:               /* I2C1 Clock is HSI Osc. */
          if (LL_RCC_HSI_IsReady() == 1U)
          {
            frequency = HSI_VALUE;
          }
          break;

        case LL_RCC_I2C1_CLKSOURCE_PCLK1:             /* I2C1 Clock is PCLK1 */
        default:
          frequency = __LL_RCC_CALC_PCLK1_FREQ(__LL_RCC_CALC_HCLK1_FREQ(HAL_RCC_GetSysClockFreq(), \
                                                                        LL_RCC_GetAHBPrescaler()), \
                                               LL_RCC_GetAPB1Prescaler());
          break;
      }
      break;

    case RCC_PERIPHCLK_I2C2:

      /* Get the current I2C2 source */
      srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C2_CLKSOURCE);

      switch (srcclk)
      {
        case LL_RCC_I2C2_CLKSOURCE_SYSCLK:            /* I2C2 Clock is System Clock */
          frequency = HAL_RCC_GetSysClockFreq();
          break;

        case LL_RCC_I2C2_CLKSOURCE_HSI:               /* I2C2 Clock is HSI Osc. */
          if (LL_RCC_HSI_IsReady() == 1U)
          {
            frequency = HSI_VALUE;
          }
          break;

        case LL_RCC_I2C2_CLKSOURCE_PCLK1:             /* I2C2 Clock is PCLK1 */
        default:
          frequency = __LL_RCC_CALC_PCLK1_FREQ(__LL_RCC_CALC_HCLK1_FREQ(HAL_RCC_GetSysClockFreq(), \
                                                                        LL_RCC_GetAHBPrescaler()), \
                                               LL_RCC_GetAPB1Prescaler());
          break;
      }
      break;

    case RCC_PERIPHCLK_I2C3:

      /* Get the current I2C3 source */
      srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C3_CLKSOURCE);

      switch (srcclk)
      {
        case LL_RCC_I2C3_CLKSOURCE_SYSCLK:            /* I2C3 Clock is System Clock */
          frequency = HAL_RCC_GetSysClockFreq();
          break;

        case LL_RCC_I2C3_CLKSOURCE_HSI:               /* I2C3 Clock is HSI Osc. */
          if (LL_RCC_HSI_IsReady() == 1U)
          {
            frequency = HSI_VALUE;
          }
          break;

        case LL_RCC_I2C3_CLKSOURCE_PCLK1:             /* I2C3 Clock is PCLK1 */
        default:
          frequency = __LL_RCC_CALC_PCLK1_FREQ(__LL_RCC_CALC_HCLK1_FREQ(HAL_RCC_GetSysClockFreq(), \
                                                                        LL_RCC_GetAHBPrescaler()), \
                                               LL_RCC_GetAPB1Prescaler());
          break;
      }
      break;

    case RCC_PERIPHCLK_I2S2:

      /* Get the current I2S2 source */
      srcclk = LL_RCC_GetI2SClockSource(LL_RCC_I2S2_CLKSOURCE);

      switch (srcclk)
      {
        case LL_RCC_I2S2_CLKSOURCE_PIN:          /* I2S2 Clock is External clock */
          frequency = EXTERNAL_CLOCK_VALUE;
          break;

        case LL_RCC_I2S2_CLKSOURCE_HSI:               /* I2S2 Clock is HSI Osc. */
          if (LL_RCC_HSI_IsReady() == 1U)
          {
            frequency = HSI_VALUE;
          }
          break;

        case LL_RCC_I2S2_CLKSOURCE_PLL:               /* I2S2 Clock is PLL */
        default:
          frequency = RCC_PLL_GetFreqDomain_Q();
          break;
      }
      break;

    case RCC_PERIPHCLK_LPTIM1:

      /* Get the current LPTIM1 source */
      srcclk = LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE);

      switch (srcclk)
      {
        case LL_RCC_LPTIM1_CLKSOURCE_LSI:             /* LPTIM1 Clock is LSI Osc. */
          if (LL_RCC_LSI_IsReady() == 1U)
          {
            if (LL_RCC_LSI_GetPrediv() == LL_RCC_LSI_PREDIV_128)
            {
              frequency = LSI_VALUE / 128U;
            }
            else
            {
              frequency = LSI_VALUE;
            }
          }
          break;

        case LL_RCC_LPTIM1_CLKSOURCE_HSI:             /* LPTIM1 Clock is HSI Osc. */
          if (LL_RCC_HSI_IsReady() == 1U)
          {
            frequency = HSI_VALUE;
          }
          break;

        case LL_RCC_LPTIM1_CLKSOURCE_LSE:             /* LPTIM1 Clock is LSE Osc. */
          if (LL_RCC_LSE_IsReady() == 1U)
          {
            frequency = LSE_VALUE;
          }
          break;

        case LL_RCC_LPTIM1_CLKSOURCE_PCLK1:           /* LPTIM1 Clock is PCLK1 */
        default:
          frequency = __LL_RCC_CALC_PCLK1_FREQ(__LL_RCC_CALC_HCLK1_FREQ(HAL_RCC_GetSysClockFreq(), \
                                                                        LL_RCC_GetAHBPrescaler()), \
                                               LL_RCC_GetAPB1Prescaler());
          break;
      }
      break;

    case RCC_PERIPHCLK_LPTIM2:

      /* Get the current LPTIM2 source */
      srcclk = LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM2_CLKSOURCE);

      switch (srcclk)
      {
        case LL_RCC_LPTIM2_CLKSOURCE_LSI:             /* LPTIM2 Clock is LSI Osc. */
          if (LL_RCC_LSI_IsReady() == 1U)
          {
            if (LL_RCC_LSI_GetPrediv() == LL_RCC_LSI_PREDIV_128)
            {
              frequency = LSI_VALUE / 128U;
            }
            else
            {
              frequency = LSI_VALUE;
            }
          }
          break;

        case LL_RCC_LPTIM2_CLKSOURCE_HSI:             /* LPTIM2 Clock is HSI Osc. */
          if (LL_RCC_HSI_IsReady() == 1U)
          {
            frequency = HSI_VALUE;
          }
          break;

        case LL_RCC_LPTIM2_CLKSOURCE_LSE:             /* LPTIM2 Clock is LSE Osc. */
          if (LL_RCC_LSE_IsReady() == 1U)
          {
            frequency = LSE_VALUE;
          }
          break;

        case LL_RCC_LPTIM2_CLKSOURCE_PCLK1:           /* LPTIM2 Clock is PCLK1 */
        default:
          frequency = __LL_RCC_CALC_PCLK1_FREQ(__LL_RCC_CALC_HCLK1_FREQ(HAL_RCC_GetSysClockFreq(), \
                                                                        LL_RCC_GetAHBPrescaler()), \
                                               LL_RCC_GetAPB1Prescaler());
          break;
      }

      break;

    case RCC_PERIPHCLK_LPTIM3:

      /* Get the current LPTIM3 source */
      srcclk = LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM3_CLKSOURCE);

      switch (srcclk)
      {
        case LL_RCC_LPTIM3_CLKSOURCE_LSI:             /* LPTIM3 Clock is LSI Osc. */
          if (LL_RCC_LSI_IsReady() == 1U)
          {
            if (LL_RCC_LSI_GetPrediv() == LL_RCC_LSI_PREDIV_128)
            {
              frequency = LSI_VALUE / 128U;
            }
            else
            {
              frequency = LSI_VALUE;
            }
          }
          break;

        case LL_RCC_LPTIM3_CLKSOURCE_HSI:             /* LPTIM3 Clock is HSI Osc. */
          if (LL_RCC_HSI_IsReady() == 1U)
          {
            frequency = HSI_VALUE;
          }
          break;

        case LL_RCC_LPTIM3_CLKSOURCE_LSE:             /* LPTIM3 Clock is LSE Osc. */
          if (LL_RCC_LSE_IsReady() == 1U)
          {
            frequency = LSE_VALUE;
          }
          break;

        case LL_RCC_LPTIM3_CLKSOURCE_PCLK1:           /* LPTIM3 Clock is PCLK1 */
        default:
          frequency = __LL_RCC_CALC_PCLK1_FREQ(__LL_RCC_CALC_HCLK1_FREQ(HAL_RCC_GetSysClockFreq(), \
                                                                        LL_RCC_GetAHBPrescaler()), \
                                               LL_RCC_GetAPB1Prescaler());
          break;
      }

      break;

    default:
      /* Unknown periphclk, frequency default init at 0 */
      break;
  }

  return (frequency);
}

/**
  * @}
  */

/** @defgroup RCCEx_Exported_Functions_Group2 Extended Clock management functions
  *  @brief  Extended Clock management functions
  *
@verbatim
 ===============================================================================
                ##### Extended clock management functions  #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the
    activation or deactivation of MSI PLL-mode, LSE CSS,
    Low speed clock output and clock after wake-up from STOP mode.
@endverbatim
  * @{
  */

/******************************************************************************/

/**
  * @brief  Configure the oscillator clock source for wakeup from Stop and CSS backup clock.
  * @param  WakeUpClk  Wakeup clock
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_STOP_WAKEUPCLOCK_MSI  MSI oscillator selection
  *            @arg @ref RCC_STOP_WAKEUPCLOCK_HSI  HSI oscillator selection
  * @note   This function shall not be called after the Clock Security System on HSE has been
  *         enabled.
  * @retval None
  */
void HAL_RCCEx_WakeUpStopCLKConfig(uint32_t WakeUpClk)
{
  assert_param(IS_RCC_STOP_WAKEUPCLOCK(WakeUpClk));

  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(WakeUpClk);
}

/**
  * @brief  Enable the LSE Clock Security System.
  * @note   Prior to enable the LSE Clock Security System, LSE oscillator has to be enabled
  *         with HAL_RCC_OscConfig() and the LSE oscillator clock has to be selected as RTC
  *         clock with HAL_RCCEx_PeriphCLKConfig().
  * @retval None
  */
void HAL_RCCEx_EnableLSECSS(void)
{
  LL_RCC_LSE_EnableCSS();
}

/**
  * @brief  Disable the LSE Clock Security System.
  * @note   LSE Clock Security System can only be disabled after a LSE failure detection.
  * @retval None
  */
void HAL_RCCEx_DisableLSECSS(void)
{
  LL_RCC_LSE_DisableCSS();

  /* Disable LSE CSS IT if any */
  __HAL_RCC_DISABLE_IT(RCC_IT_LSECSS);
}

/**
  * @brief  Enable the LSE Clock Security System Interrupt & corresponding EXTI line.
  * @note   Prior to enable the LSE Clock Security System, LSE oscillator has to be enabled
  *         with HAL_RCC_OscConfig() and the LSE oscillator clock has to be selected as RTC
  *         clock with HAL_RCCEx_PeriphCLKConfig().
  * @note   LSE Clock Security System Interrupt is mapped on RTC EXTI line 19
  * @retval None
  */
void HAL_RCCEx_EnableLSECSS_IT(void)
{
  /* Enable LSE CSS */
  LL_RCC_LSE_EnableCSS();

  /* Enable LSE CSS IT */
  __HAL_RCC_ENABLE_IT(RCC_IT_LSECSS);

  /* Enable IT on EXTI Line 19 */
  __HAL_RCC_LSECSS_EXTI_ENABLE_IT();

}

/**
  * @brief Handle the RCC LSE Clock Security System interrupt request.
  * @note   Clearing the interrupt flag is under aplication's responsibility.
  *         This should be part of clock recovery strategy when waking up the
  *         system.
  * @retval None
  */
void HAL_RCCEx_LSECSS_IRQHandler(void)
{
  /* Check RCC LSE CSSF flag  */
  if (__HAL_RCC_GET_IT(RCC_IT_LSECSS))
  {

    /* RCC LSE Clock Security System interrupt user callback */
    HAL_RCCEx_LSECSS_Callback();
  }
}

/**
  * @brief  RCCEx LSE Clock Security System interrupt callback.
  * @retval none
  */
__weak void HAL_RCCEx_LSECSS_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the @ref HAL_RCCEx_LSECSS_Callback should be implemented in the user file
   */
}

/**
  * @brief  Select the Low Speed clock source to output on LSCO pin (PA2).
  * @param  LSCOSource  specifies the Low Speed clock source to output.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_LSCOSOURCE_LSI  LSI clock selected as LSCO source
  *            @arg @ref RCC_LSCOSOURCE_LSE  LSE clock selected as LSCO source
  * @retval None
  */
void HAL_RCCEx_EnableLSCO(uint32_t LSCOSource)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  FlagStatus       backupchanged = RESET;

  /* Check the parameters */
  assert_param(IS_RCC_LSCOSOURCE(LSCOSource));

  /* LSCO Pin Clock Enable */
  __LSCO1_CLK_ENABLE();

  /* Configure the LSCO pin in analog mode */
  GPIO_InitStruct.Pin   = LSCO1_PIN;
  GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Alternate = GPIO_AF0_LSCO;
  HAL_GPIO_Init(LSCO1_GPIO_PORT, &GPIO_InitStruct);

  /* Update LSCOSEL clock source in Backup Domain control register */
  if (LL_PWR_IsEnabledBkUpAccess() == 0U)
  {
    HAL_PWR_EnableBkUpAccess();
    backupchanged = SET;
  }

  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSCOSEL | RCC_BDCR_LSCOEN, LSCOSource | RCC_BDCR_LSCOEN);

  if (backupchanged == SET)
  {
    HAL_PWR_DisableBkUpAccess();
  }
}

/**
  * @brief  Disable the Low Speed clock output.
  * @retval None
  */
void HAL_RCCEx_DisableLSCO(void)
{
  FlagStatus       backupchanged = RESET;

  if (LL_PWR_IsEnabledBkUpAccess() == 0U)
  {
    /* Enable access to the backup domain */
    HAL_PWR_EnableBkUpAccess();
    backupchanged = SET;
  }

  LL_RCC_LSCO_Disable();

  /* Restore previous configuration */
  if (backupchanged == SET)
  {
    /* Disable access to the backup domain */
    HAL_PWR_DisableBkUpAccess();
  }
}

/**
  * @brief  Enable the PLL-mode of the MSI.
  * @note   Prior to enable the PLL-mode of the MSI for automatic hardware
  *         calibration LSE oscillator has to be enabled with @ref HAL_RCC_OscConfig().
  * @retval None
  */
void HAL_RCCEx_EnableMSIPLLMode(void)
{
  LL_RCC_MSI_EnablePLLMode() ;
}

/**
  * @brief  Disable the PLL-mode of the MSI.
  * @note   PLL-mode of the MSI is automatically reset when LSE oscillator is disabled.
  * @retval None
  */
void HAL_RCCEx_DisableMSIPLLMode(void)
{
  LL_RCC_MSI_DisablePLLMode() ;
}

/**
  * @}
  */


/**
  * @}
  */

/** @addtogroup RCCEx_Private_Functions
  * @{
  */

/**
  * @brief  Return PLL clock (PLLPCLK) frequency used for ADC domain
  * @retval PLLPCLK clock frequency (in Hz)
  */
static uint32_t RCC_PLL_GetFreqDomain_P(void)
{
  uint32_t pllinputfreq;
  uint32_t pllsource;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI Value / PLLM) * PLLN
   * ADC Domain clock = PLL_VCO / PLLP
   */
  pllsource = LL_RCC_PLL_GetMainSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_MSI:                        /* MSI used as PLL clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:                        /* HSI used as PLL clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLLSOURCE_HSE:                        /* HSE used as PLL clock source */
      if (LL_RCC_HSE_IsEnabledDiv2() == 1U)
      {
        pllinputfreq = HSE_VALUE / 2U;
      }
      else
      {
        pllinputfreq = HSE_VALUE;
      }
      break;

    default:
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;
  }
  return __LL_RCC_CALC_PLLCLK_ADC_FREQ(pllinputfreq, LL_RCC_PLL_GetDivider(),
                                       LL_RCC_PLL_GetN(), LL_RCC_PLL_GetP());
}


/**
  * @brief  Return PLL clock (PLLQCLK) frequency used for 48 MHz domain
  * @retval PLLQCLK clock frequency (in Hz)
  */
static uint32_t RCC_PLL_GetFreqDomain_Q(void)
{
  uint32_t pllinputfreq;
  uint32_t pllsource;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI Value/ PLLM) * PLLN
   * 48M Domain clock = PLL_VCO / PLLQ
   */
  pllsource = LL_RCC_PLL_GetMainSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_MSI:                        /* MSI used as PLL clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:                        /* HSI used as PLL clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLLSOURCE_HSE:                        /* HSE used as PLL clock source */
      if (LL_RCC_HSE_IsEnabledDiv2() == 1U)
      {
        pllinputfreq = HSE_VALUE / 2U;
      }
      else
      {
        pllinputfreq = HSE_VALUE;
      }
      break;

    default:
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;
  }
  return __LL_RCC_CALC_PLLCLK_RNG_FREQ(pllinputfreq, LL_RCC_PLL_GetDivider(),
                                       LL_RCC_PLL_GetN(), LL_RCC_PLL_GetQ());
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

