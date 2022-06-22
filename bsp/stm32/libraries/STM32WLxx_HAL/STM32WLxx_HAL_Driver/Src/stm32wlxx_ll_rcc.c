/**
  ******************************************************************************
  * @file    stm32wlxx_ll_rcc.c
  * @author  MCD Application Team
  * @brief   RCC LL module driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_ll_rcc.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */
/** @addtogroup STM32WLxx_LL_Driver
  * @{
  */

#if defined(RCC)

/** @addtogroup RCC_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_LL_Private_Macros
  * @{
  */
#define IS_LL_RCC_USART_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_USART1_CLKSOURCE) || \
                                               ((__VALUE__) == LL_RCC_USART2_CLKSOURCE))

#define IS_LL_RCC_LPUART_CLKSOURCE(__VALUE__) (((__VALUE__) == LL_RCC_LPUART1_CLKSOURCE))

#define IS_LL_RCC_I2C_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_I2C1_CLKSOURCE) || \
                                               ((__VALUE__) == LL_RCC_I2C2_CLKSOURCE) || \
                                               ((__VALUE__) == LL_RCC_I2C3_CLKSOURCE))

#define IS_LL_RCC_LPTIM_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_LPTIM1_CLKSOURCE) || \
                                               ((__VALUE__) == LL_RCC_LPTIM2_CLKSOURCE) || \
                                               ((__VALUE__) == LL_RCC_LPTIM3_CLKSOURCE))

#define IS_LL_RCC_RNG_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_RNG_CLKSOURCE))

#define IS_LL_RCC_I2S_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_I2S2_CLKSOURCE))

#define IS_LL_RCC_ADC_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_ADC_CLKSOURCE))

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_LL_Private_Functions RCC Private functions
  * @{
  */
static uint32_t RCC_PLL_GetFreqDomain_SYS(void);
static uint32_t RCC_PLL_GetFreqDomain_ADC(void);
static uint32_t RCC_PLL_GetFreqDomain_RNG(void);
static uint32_t RCC_PLL_GetFreqDomain_I2S(void);

static uint32_t RCC_GetSystemClockFreq(void);

static uint32_t RCC_GetHCLK1ClockFreq(uint32_t SYSCLK_Frequency);
#if defined(DUAL_CORE)
static uint32_t RCC_GetHCLK2ClockFreq(uint32_t SYSCLK_Frequency);
#endif /* DUAL_CORE */
static uint32_t RCC_GetHCLK3ClockFreq(uint32_t SYSCLK_Frequency);


static uint32_t RCC_GetPCLK1ClockFreq(uint32_t HCLK_Frequency);
static uint32_t RCC_GetPCLK2ClockFreq(uint32_t HCLK_Frequency);
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCC_LL_Exported_Functions
  * @{
  */

/** @addtogroup RCC_LL_EF_Init
  * @{
  */

/**
  * @brief  Reset the RCC clock  to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *         - MSI ON and used as system clock source
  *         - HSE, HSI, PLL Source OFF
  *         - CPU1, CPU2, AHB3, APB1 and APB2 prescaler set to 1.
  *         - CSS, MCO OFF
  *         - All interrupts disabled
  * @note   This function doesn't modify the configuration of the
  *         - Peripheral clocks
  *         - LSI, LSE and RTC clocks
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RCC registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_RCC_DeInit(void)
{
  __IO uint32_t vl_mask;

  /* Set MSION bit */
  LL_RCC_MSI_Enable();

  /* Insure MSIRDY bit is set before writing default MSIRANGE value */
  while (LL_RCC_MSI_IsReady() == 0U)
  {}

  /* Set MSIRANGE default value */
  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_6);

  /* Set MSITRIM bits to the reset value*/
  LL_RCC_MSI_SetCalibTrimming(0);

  /* Set HSITRIM bits to the reset value*/
  LL_RCC_HSI_SetCalibTrimming(0x40U);

  /* Reset CFGR register */
  LL_RCC_WriteReg(CFGR, 0x00070000U); /* MSI selected as System Clock and all prescaler to not divided */

  /* Read CR register */
  vl_mask = LL_RCC_ReadReg(CR);

  /* Reset HSION, HSIKERON, HSIASFS, HSEON, HSEBYP, HSEPRE, HSEBYPPWR and PLLSYSON bits */
  CLEAR_BIT(vl_mask, (RCC_CR_HSION | RCC_CR_HSIKERON | RCC_CR_HSIASFS | RCC_CR_HSEON | \
                      RCC_CR_HSEPRE | RCC_CR_HSEBYPPWR | RCC_CR_PLLON));

  /* Write new value in CR register */
  LL_RCC_WriteReg(CR, vl_mask);

  /* Wait for PLL READY bit to be reset */
  while (LL_RCC_PLL_IsReady() != 0U)
  {}

  /* Reset PLLCFGR register */
  LL_RCC_WriteReg(PLLCFGR, 0x22041000U);

  /* Disable all interrupts */
  LL_RCC_WriteReg(CIER, 0x00000000U);

  /* Clear all interrupt flags */
  vl_mask = RCC_CICR_LSIRDYC | RCC_CICR_LSERDYC | RCC_CICR_MSIRDYC | RCC_CICR_HSIRDYC | \
            RCC_CICR_HSERDYC | RCC_CICR_PLLRDYC | RCC_CICR_CSSC | RCC_CICR_LSECSSC;

  LL_RCC_WriteReg(CICR, vl_mask);

  /* Clear reset flags */
  LL_RCC_ClearResetFlags();

  /* EXTCFGR reset*/
  LL_RCC_WriteReg(EXTCFGR, 0x00030000U);

  return SUCCESS;
}

/**
  * @}
  */

/** @addtogroup RCC_LL_EF_Get_Freq
  * @brief  Return the frequencies of different on chip clocks;  System, AHB, APB1 and APB2 buses clocks
  *         and different peripheral clocks available on the device.
  * @note   If SYSCLK source is MSI, function returns values based on MSI values(*)
  * @note   If SYSCLK source is HSI, function returns values based on HSI_VALUE(**)
  * @note   If SYSCLK source is HSE, function returns values based on HSE_VALUE(***)
  * @note   If SYSCLK source is PLL, function returns values based on HSE_VALUE(***)
  *         or HSI_VALUE(**) or MSI values(*) multiplied/divided by the PLL factors.
  * @note   (*)  MSI values are retrieved thanks to __LL_RCC_CALC_MSI_FREQ macro
  * @note   (**) HSI_VALUE is a constant defined in this file (default value
  *              16 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  * @note   (***) HSE_VALUE is a constant defined in this file (default value
  *               32 MHz), user has to ensure that HSE_VALUE is same as the real
  *               frequency of the crystal used. Otherwise, this function may
  *               have wrong result.
  * @note   The result of this function could be incorrect when using fractional
  *         value for HSE crystal.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @{
  */

/**
  * @brief  Return the frequencies of different on chip clocks;  System, AHB, APB1 and APB2 buses clocks
  * @note   Each time SYSCLK, HCLK, PCLK1 and/or PCLK2 clock changes, this function
  *         must be called to update structure fields. Otherwise, any
  *         configuration based on this function will be incorrect.
  * @param  RCC_Clocks pointer to a @ref LL_RCC_ClocksTypeDef structure which will hold the clocks frequencies
  * @retval None
  */
void LL_RCC_GetSystemClocksFreq(LL_RCC_ClocksTypeDef *RCC_Clocks)
{
  /* Get SYSCLK frequency */
  RCC_Clocks->SYSCLK_Frequency = RCC_GetSystemClockFreq();

  /* HCLK1 clock frequency */
  RCC_Clocks->HCLK1_Frequency   = RCC_GetHCLK1ClockFreq(RCC_Clocks->SYSCLK_Frequency);

#if defined(DUAL_CORE)
  /* HCLK2 clock frequency */
  RCC_Clocks->HCLK2_Frequency   = RCC_GetHCLK2ClockFreq(RCC_Clocks->SYSCLK_Frequency);
#endif /* DUAL_CORE */

  /* HCLK3 clock frequency */
  RCC_Clocks->HCLK3_Frequency   = RCC_GetHCLK3ClockFreq(RCC_Clocks->SYSCLK_Frequency);

  /* PCLK1 clock frequency */
  RCC_Clocks->PCLK1_Frequency  = RCC_GetPCLK1ClockFreq(RCC_Clocks->HCLK1_Frequency);

  /* PCLK2 clock frequency */
  RCC_Clocks->PCLK2_Frequency  = RCC_GetPCLK2ClockFreq(RCC_Clocks->HCLK1_Frequency);
}

/**
  * @brief  Return USARTx clock frequency
  * @param  USARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  * @retval USART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI or LSE) is not ready
  */
uint32_t LL_RCC_GetUSARTClockFreq(uint32_t USARTxSource)
{
  uint32_t usart_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_USART_CLKSOURCE(USARTxSource));

  if (USARTxSource == LL_RCC_USART1_CLKSOURCE)
  {
    /* USART1CLK clock frequency */
    switch (LL_RCC_GetUSARTClockSource(USARTxSource))
    {
      case LL_RCC_USART1_CLKSOURCE_SYSCLK: /* USART1 Clock is System Clock */
        usart_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_USART1_CLKSOURCE_HSI:    /* USART1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          usart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_USART1_CLKSOURCE_LSE:    /* USART1 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          usart_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_USART1_CLKSOURCE_PCLK2:  /* USART1 Clock is PCLK2 */
      default:
        usart_frequency = RCC_GetPCLK2ClockFreq(RCC_GetHCLK1ClockFreq(RCC_GetSystemClockFreq()));
        break;
    }
  }
  else
  {
    /* USART2CLK clock frequency */
    switch (LL_RCC_GetUSARTClockSource(USARTxSource))
    {
      case LL_RCC_USART2_CLKSOURCE_SYSCLK: /* USART2 Clock is System Clock */
        usart_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_USART2_CLKSOURCE_HSI:    /* USART2 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          usart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_USART2_CLKSOURCE_LSE:    /* USART2 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          usart_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_USART2_CLKSOURCE_PCLK1:  /* USART2 Clock is PCLK2 */
      default:
        usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLK1ClockFreq(RCC_GetSystemClockFreq()));
        break;
    }
  }
  return usart_frequency;
}

/**
  * @brief  Return I2Cx clock frequency
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE
  * @retval I2C clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that HSI oscillator is not ready
  */
uint32_t LL_RCC_GetI2CClockFreq(uint32_t I2CxSource)
{
  uint32_t i2c_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_I2C_CLKSOURCE(I2CxSource));

  if (I2CxSource == LL_RCC_I2C1_CLKSOURCE)
  {
    /* I2C1 CLK clock frequency */
    switch (LL_RCC_GetI2CClockSource(I2CxSource))
    {
      case LL_RCC_I2C1_CLKSOURCE_SYSCLK: /* I2C1 Clock is System Clock */
        i2c_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_I2C1_CLKSOURCE_HSI:    /* I2C1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          i2c_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_I2C1_CLKSOURCE_PCLK1:  /* I2C1 Clock is PCLK1 */
      default:
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLK1ClockFreq(RCC_GetSystemClockFreq()));
        break;
    }
  }
  else if (I2CxSource == LL_RCC_I2C2_CLKSOURCE)
  {
    /* I2C2 CLK clock frequency */
    switch (LL_RCC_GetI2CClockSource(I2CxSource))
    {
      case LL_RCC_I2C2_CLKSOURCE_SYSCLK: /* I2C2 Clock is System Clock */
        i2c_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_I2C2_CLKSOURCE_HSI:    /* I2C2 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          i2c_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_I2C2_CLKSOURCE_PCLK1:  /* I2C2 Clock is PCLK1 */
      default:
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLK1ClockFreq(RCC_GetSystemClockFreq()));
        break;
    }
  }
  else
  {
    /* I2C3 CLK clock frequency */
    switch (LL_RCC_GetI2CClockSource(I2CxSource))
    {
      case LL_RCC_I2C3_CLKSOURCE_SYSCLK: /* I2C3 Clock is System Clock */
        i2c_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_I2C3_CLKSOURCE_HSI:    /* I2C3 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          i2c_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_I2C3_CLKSOURCE_PCLK1:  /* I2C3 Clock is PCLK1 */
      default:
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLK1ClockFreq(RCC_GetSystemClockFreq()));
        break;
    }
  }

  return i2c_frequency;
}


/**
  * @brief  Return LPUARTx clock frequency
  * @param  LPUARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE
  * @retval LPUART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI or LSE) is not ready
  */
uint32_t LL_RCC_GetLPUARTClockFreq(uint32_t LPUARTxSource)
{
  uint32_t lpuart_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_LPUART_CLKSOURCE(LPUARTxSource));

  /* LPUART1CLK clock frequency */
  switch (LL_RCC_GetLPUARTClockSource(LPUARTxSource))
  {
    case LL_RCC_LPUART1_CLKSOURCE_SYSCLK: /* LPUART1 Clock is System Clock */
      lpuart_frequency = RCC_GetSystemClockFreq();
      break;

    case LL_RCC_LPUART1_CLKSOURCE_HSI:    /* LPUART1 Clock is HSI Osc. */
      if (LL_RCC_HSI_IsReady() == 1U)
      {
        lpuart_frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_LPUART1_CLKSOURCE_LSE:    /* LPUART1 Clock is LSE Osc. */
      if (LL_RCC_LSE_IsReady() == 1U)
      {
        lpuart_frequency = LSE_VALUE;
      }
      break;

    case LL_RCC_LPUART1_CLKSOURCE_PCLK1:  /* LPUART1 Clock is PCLK1 */
    default:
      lpuart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLK1ClockFreq(RCC_GetSystemClockFreq()));
      break;
  }

  return lpuart_frequency;
}

/**
  * @brief  Return LPTIMx clock frequency
  * @param  LPTIMxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE
  * @retval LPTIM clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI, LSI or LSE) is not ready
  */
uint32_t LL_RCC_GetLPTIMClockFreq(uint32_t LPTIMxSource)
{
  uint32_t lptim_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_LPTIM_CLKSOURCE(LPTIMxSource));

  if (LPTIMxSource == LL_RCC_LPTIM1_CLKSOURCE)
  {
    /* LPTIM1CLK clock frequency */
    switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
    {
      case LL_RCC_LPTIM1_CLKSOURCE_LSI:    /* LPTIM1 Clock is LSI Osc. */
        if (LL_RCC_LSI_IsReady() == 1U)
        {
          if (LL_RCC_LSI_GetPrediv() == LL_RCC_LSI_PREDIV_128)
          {
            lptim_frequency = LSI_VALUE / 128U;
          }
          else
          {
            lptim_frequency = LSI_VALUE;
          }
        }
        break;

      case LL_RCC_LPTIM1_CLKSOURCE_HSI:    /* LPTIM1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          lptim_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM1_CLKSOURCE_LSE:    /* LPTIM1 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          lptim_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPTIM1_CLKSOURCE_PCLK1:  /* LPTIM1 Clock is PCLK1 */
      default:
        lptim_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLK1ClockFreq(RCC_GetSystemClockFreq()));
        break;
    }
  }
  else if (LPTIMxSource == LL_RCC_LPTIM2_CLKSOURCE)
  {
    /* LPTIM2CLK clock frequency */
    switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
    {
      case LL_RCC_LPTIM2_CLKSOURCE_LSI:    /* LPTIM2 Clock is LSI Osc. */
        if (LL_RCC_LSI_IsReady() == 1U)
        {
          if (LL_RCC_LSI_GetPrediv() == LL_RCC_LSI_PREDIV_128)
          {
            lptim_frequency = LSI_VALUE / 128U;
          }
          else
          {
            lptim_frequency = LSI_VALUE;
          }
        }
        break;

      case LL_RCC_LPTIM2_CLKSOURCE_HSI:    /* LPTIM2 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          lptim_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM2_CLKSOURCE_LSE:    /* LPTIM2 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          lptim_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPTIM2_CLKSOURCE_PCLK1:  /* LPTIM2 Clock is PCLK1 */
      default:
        lptim_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLK1ClockFreq(RCC_GetSystemClockFreq()));
        break;
    }
  }
  else
  {
    /* LPTIM3CLK clock frequency */
    switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
    {
      case LL_RCC_LPTIM3_CLKSOURCE_LSI:    /* LPTIM3 Clock is LSI Osc. */
        if (LL_RCC_LSI_IsReady() == 1U)
        {
          lptim_frequency = LSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM3_CLKSOURCE_HSI:    /* LPTIM3 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          lptim_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM3_CLKSOURCE_LSE:    /* LPTIM3 Clock is LSE Osc. */
        if (LL_RCC_LSI_IsReady() == 1U)
        {
          if (LL_RCC_LSI_GetPrediv() == LL_RCC_LSI_PREDIV_128)
          {
            lptim_frequency = LSI_VALUE / 128U;
          }
          else
          {
            lptim_frequency = LSI_VALUE;
          }
        }
        break;


      case LL_RCC_LPTIM3_CLKSOURCE_PCLK1:  /* LPTIM3 Clock is PCLK1 */
      default:
        lptim_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLK1ClockFreq(RCC_GetSystemClockFreq()));
        break;
    }
  }

  return lptim_frequency;
}

/**
  * @brief  Return RNGx clock frequency
  * @param  RNGxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE
  * @retval RNG clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSI) or PLLs (PLL) is not ready
  */
uint32_t LL_RCC_GetRNGClockFreq(uint32_t RNGxSource)
{
  uint32_t rng_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_RNG_CLKSOURCE(RNGxSource));

  /* RNGCLK clock frequency */
  switch (LL_RCC_GetRNGClockSource(RNGxSource))
  {
    case LL_RCC_RNG_CLKSOURCE_MSI:           /* MSI used as RNG clock source */
      if (LL_RCC_MSI_IsReady() == 1U)
      {
        rng_frequency = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                               ((LL_RCC_MSI_IsEnabledRangeSelect()  == 1U) ?
                                                LL_RCC_MSI_GetRange() :
                                                LL_RCC_MSI_GetRangeAfterStandby()));
      }
      break;
    case LL_RCC_RNG_CLKSOURCE_LSI:           /* LSI clock used as RNG clock source */

      if (LL_RCC_LSI_IsReady() == 1U)
      {
        if (LL_RCC_LSI_GetPrediv() == LL_RCC_LSI_PREDIV_128)
        {
          rng_frequency = LSI_VALUE / 128U;
        }
        else
        {
          rng_frequency = LSI_VALUE;
        }
        break;
      }
      break;
    case LL_RCC_RNG_CLKSOURCE_LSE:           /* LSE clock used as RNG clock source */

      if (LL_RCC_LSE_IsReady() == 1U)
      {
        rng_frequency = LSE_VALUE;
      }
      break;
    case LL_RCC_RNG_CLKSOURCE_PLL:           /* PLL clock used as RNG clock source */
    default:
      if (LL_RCC_PLL_IsReady() == 1U)
      {
        rng_frequency = RCC_PLL_GetFreqDomain_RNG();
      }
      break;
  }
  return rng_frequency;
}

/**
  * @brief  Return I2Sx clock frequency
  * @param  I2SxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2S2_CLKSOURCE
  * @retval I2S clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI) or PLLs (PLL) is not ready
  */
uint32_t LL_RCC_GetI2SClockFreq(uint32_t I2SxSource)
{
  uint32_t i2s_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_I2S_CLKSOURCE(I2SxSource));

  /* I2SCLK clock frequency */
  switch (LL_RCC_GetI2SClockSource(I2SxSource))
  {
    case LL_RCC_I2S2_CLKSOURCE_PLL:    /* I2S2 Clock is PLL"P" */
      if (LL_RCC_PLL_IsReady() == 1U)
      {
        i2s_frequency = RCC_PLL_GetFreqDomain_I2S();
      }
      break;

    case LL_RCC_I2S2_CLKSOURCE_PIN:          /* I2S2 Clock is External clock */
      i2s_frequency = EXTERNAL_CLOCK_VALUE;
      break;

    case LL_RCC_I2S2_CLKSOURCE_HSI:           /* HSI clock used as I2S clock source */
    default:
      if (LL_RCC_HSI_IsReady() == 1U)
      {
        i2s_frequency = HSI_VALUE;
      }
      break;
  }
  return i2s_frequency;
}

/**
  * @brief  Return ADCx clock frequency
  * @param  ADCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE
  * @retval ADC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSI) or PLL is not ready
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NA indicates that no clock source selected
  */
uint32_t LL_RCC_GetADCClockFreq(uint32_t ADCxSource)
{
  uint32_t adc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_ADC_CLKSOURCE(ADCxSource));

  /* ADCCLK clock frequency */
  switch (LL_RCC_GetADCClockSource(ADCxSource))
  {
    case LL_RCC_ADC_CLKSOURCE_HSI:    /* ADC Clock is HSI Osc. */
      if (LL_RCC_HSI_IsReady() == 1U)
      {
        adc_frequency = HSI_VALUE;
      }
      break;
    case LL_RCC_ADC_CLKSOURCE_SYSCLK:        /* SYSCLK clock used as ADC clock source */
      adc_frequency = RCC_GetSystemClockFreq();
      break;
    case LL_RCC_ADC_CLKSOURCE_PLL:           /* PLL clock used as ADC clock source */
      if (LL_RCC_PLL_IsReady() == 1U)
      {
        adc_frequency = RCC_PLL_GetFreqDomain_ADC();
      }
      break;
    case LL_RCC_ADC_CLKSOURCE_NONE:          /* No clock used as ADC clock source */
    default:
      adc_frequency = LL_RCC_PERIPH_FREQUENCY_NA;
      break;
  }

  return adc_frequency;
}

/**
  * @brief  Return RTC clock frequency
  * @retval RTC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillators (LSI, LSE or HSE) are not ready
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NA indicates that no clock source selected
  */
uint32_t LL_RCC_GetRTCClockFreq(void)
{
  uint32_t rtc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* RTCCLK clock frequency */
  switch (LL_RCC_GetRTCClockSource())
  {
    case LL_RCC_RTC_CLKSOURCE_LSE:       /* LSE clock used as RTC clock source */
      if (LL_RCC_LSE_IsReady() == 1U)
      {
        rtc_frequency = LSE_VALUE;
      }
      break;

    case LL_RCC_RTC_CLKSOURCE_LSI:       /* LSI clock used as RTC clock source */
      if (LL_RCC_LSI_IsReady() == 1U)
      {
        if (LL_RCC_LSI_GetPrediv() == LL_RCC_LSI_PREDIV_128)
        {
          rtc_frequency = LSI_VALUE / 128U;
        }
        else
        {
          rtc_frequency = LSI_VALUE;
        }
      }
      break;

    case LL_RCC_RTC_CLKSOURCE_HSE_DIV32:        /* HSE clock used as ADC clock source */
      rtc_frequency = HSE_VALUE / 32U;
      break;

    case LL_RCC_RTC_CLKSOURCE_NONE:          /* No clock used as RTC clock source */
    default:
      rtc_frequency = LL_RCC_PERIPH_FREQUENCY_NA;
      break;
  }

  return rtc_frequency;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup RCC_LL_Private_Functions
  * @{
  */

/**
  * @brief  Return SYSTEM clock (SYSCLK) frequency
  * @retval SYSTEM clock frequency (in Hz)
  */
static uint32_t RCC_GetSystemClockFreq(void)
{
  uint32_t frequency;

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (LL_RCC_GetSysClkSource())
  {
    case LL_RCC_SYS_CLKSOURCE_STATUS_MSI:  /* MSI used as system clock source */
      frequency = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                         ((LL_RCC_MSI_IsEnabledRangeSelect()  == 1U) ?
                                          LL_RCC_MSI_GetRange() :
                                          LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_HSI:  /* HSI used as system clock  source */
      frequency = HSI_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_HSE:  /* HSE used as system clock  source */
      if (LL_RCC_HSE_IsEnabledDiv2() == 1U)
      {
        frequency = HSE_VALUE / 2U;
      }
      else
      {
        frequency = HSE_VALUE;
      }
      break;


    case LL_RCC_SYS_CLKSOURCE_STATUS_PLL:  /* PLL used as system clock  source */
      frequency = RCC_PLL_GetFreqDomain_SYS();
      break;

    default:
      frequency = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                         ((LL_RCC_MSI_IsEnabledRangeSelect()  == 1U) ?
                                          LL_RCC_MSI_GetRange() :
                                          LL_RCC_MSI_GetRangeAfterStandby()));
      break;
  }

  return frequency;
}

/**
  * @brief  Return HCLK1 clock frequency
  * @param  SYSCLK_Frequency SYSCLK clock frequency
  * @retval HCLK1 clock frequency (in Hz)
  */
static uint32_t RCC_GetHCLK1ClockFreq(uint32_t SYSCLK_Frequency)
{
  /* HCLK clock frequency */
  return __LL_RCC_CALC_HCLK1_FREQ(SYSCLK_Frequency, LL_RCC_GetAHBPrescaler());
}

#if defined(DUAL_CORE)
/**
  * @brief  Return HCLK2 clock frequency
  * @param  SYSCLK_Frequency SYSCLK clock frequency
  * @retval HCLK2 clock frequency (in Hz)
  */
static uint32_t RCC_GetHCLK2ClockFreq(uint32_t SYSCLK_Frequency)
{
  /* HCLK clock frequency */
  return __LL_RCC_CALC_HCLK2_FREQ(SYSCLK_Frequency, LL_C2_RCC_GetAHBPrescaler());
}
#endif /* DUAL_CORE */

/**
  * @brief  Return HCLK clock frequency
  * @param  SYSCLK_Frequency SYSCLK clock frequency
  * @retval HCLK3 clock frequency (in Hz)
  */
static uint32_t RCC_GetHCLK3ClockFreq(uint32_t SYSCLK_Frequency)
{
  /* HCLK clock frequency */
  return __LL_RCC_CALC_HCLK3_FREQ(SYSCLK_Frequency, LL_RCC_GetAHB3Prescaler());
}

/**
  * @brief  Return PCLK1 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK1 clock frequency (in Hz)
  */
static uint32_t RCC_GetPCLK1ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK1 clock frequency */
  return __LL_RCC_CALC_PCLK1_FREQ(HCLK_Frequency, LL_RCC_GetAPB1Prescaler());
}

/**
  * @brief  Return PCLK2 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK2 clock frequency (in Hz)
  */
static uint32_t RCC_GetPCLK2ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK2 clock frequency */
  return __LL_RCC_CALC_PCLK2_FREQ(HCLK_Frequency, LL_RCC_GetAPB2Prescaler());
}

/**
  * @brief  Return PLL clock (PLLRCLK) frequency used for system domain
  * @retval PLLRCLK clock frequency (in Hz)
  */
static uint32_t RCC_PLL_GetFreqDomain_SYS(void)
{
  uint32_t pllinputfreq;
  uint32_t pllsource;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI Value/ PLLM) * PLLN
     SYSCLK = PLL_VCO / PLLR
  */
  pllsource = LL_RCC_PLL_GetMainSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_MSI:  /* MSI used as PLL clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect()  == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
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
                                            ((LL_RCC_MSI_IsEnabledRangeSelect()  == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;
  }
  return __LL_RCC_CALC_PLLCLK_FREQ(pllinputfreq, LL_RCC_PLL_GetDivider(),
                                   LL_RCC_PLL_GetN(), LL_RCC_PLL_GetR());
}

/**
  * @brief  Return PLL clock (PLLPCLK) frequency used for ADC domain
  * @retval PLLPCLK clock frequency (in Hz)
  */
static uint32_t RCC_PLL_GetFreqDomain_ADC(void)
{
  uint32_t pllinputfreq;
  uint32_t pllsource;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI Value / PLLM) * PLLN
  */
  pllsource = LL_RCC_PLL_GetMainSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_MSI:  /* MSI used as PLL clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect()  == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
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
                                            ((LL_RCC_MSI_IsEnabledRangeSelect()  == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;
  }
  return __LL_RCC_CALC_PLLCLK_ADC_FREQ(pllinputfreq, LL_RCC_PLL_GetDivider(),
                                       LL_RCC_PLL_GetN(), LL_RCC_PLL_GetP());
}

/**
  * @brief  Return PLL clock (PLLQCLK) frequency used for RNG domain
  * @retval PLLQCLK clock frequency (in Hz)
  */
static uint32_t RCC_PLL_GetFreqDomain_RNG(void)
{
  uint32_t pllinputfreq;
  uint32_t pllsource;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI Value / PLLM) * PLLN
  */
  pllsource = LL_RCC_PLL_GetMainSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_MSI:  /* MSI used as PLL clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect()  == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
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
                                            ((LL_RCC_MSI_IsEnabledRangeSelect()  == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;
  }
  return __LL_RCC_CALC_PLLCLK_RNG_FREQ(pllinputfreq, LL_RCC_PLL_GetDivider(),
                                       LL_RCC_PLL_GetN(), LL_RCC_PLL_GetQ());
}

/**
  * @brief  Return PLL clock (PLLQCLK) frequency used for I2S domain
  * @retval PLLQCLK clock frequency (in Hz)
  */
static uint32_t RCC_PLL_GetFreqDomain_I2S(void)
{
  uint32_t pllinputfreq;
  uint32_t pllsource;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI Value / PLLM) * PLLN
  */
  pllsource = LL_RCC_PLL_GetMainSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_MSI:  /* MSI used as PLL clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect()  == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
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
                                            ((LL_RCC_MSI_IsEnabledRangeSelect()  == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;
  }
  return __LL_RCC_CALC_PLLCLK_I2S2_FREQ(pllinputfreq, LL_RCC_PLL_GetDivider(),
                                        LL_RCC_PLL_GetN(), LL_RCC_PLL_GetQ());
}


/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(RCC) */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
