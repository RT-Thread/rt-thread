/**
  ******************************************************************************
  * @file    stm32l5xx_ll_rcc.c
  * @author  MCD Application Team
  * @brief   RCC LL module driver.
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
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_ll_rcc.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32L5xx_LL_Driver
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
/** @defgroup RCC_LL_Private_Macros RCC Private Macros
  * @{
  */
#define IS_LL_RCC_USART_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_USART1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_USART2_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_USART3_CLKSOURCE))

#define IS_LL_RCC_UART_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_UART4_CLKSOURCE) \
                                                || ((__VALUE__) == LL_RCC_UART5_CLKSOURCE))

#define IS_LL_RCC_LPUART_CLKSOURCE(__VALUE__) (((__VALUE__) == LL_RCC_LPUART1_CLKSOURCE))

#define IS_LL_RCC_I2C_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_I2C1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_I2C2_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_I2C3_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_I2C4_CLKSOURCE))

#define IS_LL_RCC_LPTIM_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_LPTIM1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPTIM2_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPTIM3_CLKSOURCE))

#define IS_LL_RCC_SAI_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_SAI1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_SAI2_CLKSOURCE))

#define IS_LL_RCC_SDMMC_KERNELCLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_SDMMC1_KERNELCLKSOURCE))

#define IS_LL_RCC_SDMMC_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_SDMMC1_CLKSOURCE))

#define IS_LL_RCC_RNG_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_RNG_CLKSOURCE))

#define IS_LL_RCC_USB_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_USB_CLKSOURCE))

#define IS_LL_RCC_ADC_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_ADC_CLKSOURCE))

#define IS_LL_RCC_DFSDM_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_DFSDM1_CLKSOURCE))

#define IS_LL_RCC_DFSDM_AUDIO_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_DFSDM1_AUDIO_CLKSOURCE))

#define IS_LL_RCC_OCTOSPI_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_OCTOSPI_CLKSOURCE))

#define IS_LL_RCC_FDCAN_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_FDCAN_CLKSOURCE))

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_LL_Private_Functions RCC Private Functions
  * @{
  */
static uint32_t RCC_GetSystemClockFreq(void);
static uint32_t RCC_GetHCLKClockFreq(uint32_t SYSCLK_Frequency);
static uint32_t RCC_GetPCLK1ClockFreq(uint32_t HCLK_Frequency);
static uint32_t RCC_GetPCLK2ClockFreq(uint32_t HCLK_Frequency);
static uint32_t RCC_PLL_GetFreqDomain_SYS(void);
static uint32_t RCC_PLL_GetFreqDomain_SAI(void);
static uint32_t RCC_PLL_GetFreqDomain_48M(void);
static uint32_t RCC_PLLSAI1_GetFreqDomain_SAI(void);
static uint32_t RCC_PLLSAI1_GetFreqDomain_48M(void);
static uint32_t RCC_PLLSAI1_GetFreqDomain_ADC(void);
static uint32_t RCC_PLLSAI2_GetFreqDomain_SAI(void);
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
  * @brief  Reset the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *         - MSI  ON and used as system clock source
  *         - HSE, HSI, PLL, PLLSAI1 and PLLSAI2 OFF
  *         - AHB, APB1 and APB2 prescaler set to 1.
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
  {
  }

  /* Set MSIRANGE default value */
  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_6);

  /* Set MSITRIM bits to the reset value*/
  LL_RCC_MSI_SetCalibTrimming(0);

  /* Set HSITRIM bits to the reset value*/
  LL_RCC_HSI_SetCalibTrimming(0x40U);

  /* Reset CFGR register */
  LL_RCC_WriteReg(CFGR, 0x00000000U);

  /* Read CR register */
  vl_mask = LL_RCC_ReadReg(CR);

  /* Reset HSION, HSIKERON, HSIASFS, HSEON, PLLON, PLLSAI1ON and PLLSAI2ON bits */
  CLEAR_BIT(vl_mask, (RCC_CR_HSION | RCC_CR_HSIASFS | RCC_CR_HSIKERON  | RCC_CR_HSEON |
                      RCC_CR_PLLON | RCC_CR_PLLSAI1ON | RCC_CR_PLLSAI2ON));

  /* Write new mask in CR register */
  LL_RCC_WriteReg(CR, vl_mask);

  /* Wait for PLLRDY, PLLSAI1RDY and PLLSAI2RDY bits to be reset */
  while (READ_BIT(RCC->CR, RCC_CR_PLLRDY | RCC_CR_PLLSAI1RDY | RCC_CR_PLLSAI2RDY) != 0U)
  {
  }

  /* Reset PLLCFGR register */
  LL_RCC_WriteReg(PLLCFGR, 16U << RCC_PLLCFGR_PLLN_Pos);

  /* Reset PLLSAI1CFGR register */
  LL_RCC_WriteReg(PLLSAI1CFGR, 16U << RCC_PLLSAI1CFGR_PLLSAI1N_Pos);

  /* Reset PLLSAI2CFGR register */
  LL_RCC_WriteReg(PLLSAI2CFGR, 16U << RCC_PLLSAI2CFGR_PLLSAI2N_Pos);

  /* Reset HSEBYP bit */
  LL_RCC_HSE_DisableBypass();

  /* Disable all interrupts */
  LL_RCC_WriteReg(CIER, 0x00000000U);

  /* Clear all interrupt flags */
  vl_mask = RCC_CICR_LSIRDYC | RCC_CICR_LSERDYC | RCC_CICR_MSIRDYC | RCC_CICR_HSIRDYC | RCC_CICR_HSERDYC | RCC_CICR_PLLRDYC | \
            RCC_CICR_HSI48RDYC | RCC_CICR_PLLSAI1RDYC | RCC_CICR_PLLSAI2RDYC | RCC_CICR_CSSC;
  LL_RCC_WriteReg(CICR, vl_mask);

  /* Clear reset flags */
  LL_RCC_ClearResetFlags();

  /* Reset privilege mode */
  LL_RCC_DisablePrivilege();

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  /* Reset secure configuration */
  LL_RCC_ConfigSecure(LL_RCC_ALL_NSEC);
#endif /* __ARM_FEATURE_CMSE && (__ARM_FEATURE_CMSE == 3U) */

  return SUCCESS;
}

/**
  * @}
  */

/** @addtogroup RCC_LL_EF_Get_Freq
  * @brief  Return the frequencies of different on chip clocks;  System, AHB, APB1 and APB2 buses clocks
  *         and different peripheral clocks available on the device.
  * @note   If SYSCLK source is MSI, function returns values based on MSI_VALUE(*)
  * @note   If SYSCLK source is HSI, function returns values based on HSI_VALUE(**)
  * @note   If SYSCLK source is HSE, function returns values based on HSE_VALUE(***)
  * @note   If SYSCLK source is PLL, function returns values based on HSE_VALUE(***)
  *         or HSI_VALUE(**) or MSI_VALUE(*) multiplied/divided by the PLL factors.
  * @note   (*) MSI_VALUE is a constant defined in this file (default value
  *             4 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.
  * @note   (**) HSI_VALUE is a constant defined in this file (default value
  *              16 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  * @note   (***) HSE_VALUE is a constant defined in this file (default value
  *               8 MHz), user has to ensure that HSE_VALUE is same as the real
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

  /* HCLK clock frequency */
  RCC_Clocks->HCLK_Frequency   = RCC_GetHCLKClockFreq(RCC_Clocks->SYSCLK_Frequency);

  /* PCLK1 clock frequency */
  RCC_Clocks->PCLK1_Frequency  = RCC_GetPCLK1ClockFreq(RCC_Clocks->HCLK_Frequency);

  /* PCLK2 clock frequency */
  RCC_Clocks->PCLK2_Frequency  = RCC_GetPCLK2ClockFreq(RCC_Clocks->HCLK_Frequency);
}

/**
  * @brief  Return USARTx clock frequency
  * @param  USARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE
  *         @arg @ref LL_RCC_USART3_CLKSOURCE
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
        usart_frequency = RCC_GetPCLK2ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else if (USARTxSource == LL_RCC_USART2_CLKSOURCE)
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

      case LL_RCC_USART2_CLKSOURCE_PCLK1:  /* USART2 Clock is PCLK1 */
        usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else if (USARTxSource == LL_RCC_USART3_CLKSOURCE)
  {
    /* USART3CLK clock frequency */
    switch (LL_RCC_GetUSARTClockSource(USARTxSource))
    {
      case LL_RCC_USART3_CLKSOURCE_SYSCLK: /* USART3 Clock is System Clock */
        usart_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_USART3_CLKSOURCE_HSI:    /* USART3 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          usart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_USART3_CLKSOURCE_LSE:    /* USART3 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          usart_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_USART3_CLKSOURCE_PCLK1:  /* USART3 Clock is PCLK1 */
        usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else
  {
    /* nothing to do */
  }

  return usart_frequency;
}

/**
  * @brief  Return UARTx clock frequency
  * @param  UARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_UART4_CLKSOURCE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE
  * @retval UART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI or LSE) is not ready
  */
uint32_t LL_RCC_GetUARTClockFreq(uint32_t UARTxSource)
{
  uint32_t uart_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_UART_CLKSOURCE(UARTxSource));

  if (UARTxSource == LL_RCC_UART4_CLKSOURCE)
  {
    /* UART4CLK clock frequency */
    switch (LL_RCC_GetUARTClockSource(UARTxSource))
    {
      case LL_RCC_UART4_CLKSOURCE_SYSCLK: /* UART4 Clock is System Clock */
        uart_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_UART4_CLKSOURCE_HSI:    /* UART4 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          uart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_UART4_CLKSOURCE_LSE:    /* UART4 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          uart_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_UART4_CLKSOURCE_PCLK1:  /* UART4 Clock is PCLK1 */
        uart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else if (UARTxSource == LL_RCC_UART5_CLKSOURCE)
  {
    /* UART5CLK clock frequency */
    switch (LL_RCC_GetUARTClockSource(UARTxSource))
    {
      case LL_RCC_UART5_CLKSOURCE_SYSCLK: /* UART5 Clock is System Clock */
        uart_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_UART5_CLKSOURCE_HSI:    /* UART5 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          uart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_UART5_CLKSOURCE_LSE:    /* UART5 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          uart_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_UART5_CLKSOURCE_PCLK1:  /* UART5 Clock is PCLK1 */
        uart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else
  {
    /* nothing to do */
  }

  return uart_frequency;
}

/**
  * @brief  Return I2Cx clock frequency
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE
  * @retval I2C clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI) is not ready
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
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
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
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else if (I2CxSource == LL_RCC_I2C3_CLKSOURCE)
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
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else if (I2CxSource == LL_RCC_I2C4_CLKSOURCE)
  {
    /* I2C4 CLK clock frequency */
    switch (LL_RCC_GetI2CClockSource(I2CxSource))
    {
      case LL_RCC_I2C4_CLKSOURCE_SYSCLK: /* I2C4 Clock is System Clock */
        i2c_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_I2C4_CLKSOURCE_HSI:    /* I2C4 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          i2c_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_I2C4_CLKSOURCE_PCLK1:  /* I2C4 Clock is PCLK1 */
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else
  {
    /* nothing to do */
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
      lpuart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
      break;

    default:
      /* unreachable code */
      break;
  }

  return lpuart_frequency;
}

/**
  * @brief  Return LPTIMx clock frequency
  * @param  LPTIMxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM2_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE
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
          lptim_frequency = LSI_VALUE;
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
        lptim_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
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
          lptim_frequency = LSI_VALUE;
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
        lptim_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else if (LPTIMxSource == LL_RCC_LPTIM3_CLKSOURCE)
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
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          lptim_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPTIM3_CLKSOURCE_PCLK1:  /* LPTIM3 Clock is PCLK1 */
        lptim_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else
  {
    /* nothing to do */
  }

  return lptim_frequency;
}

/**
  * @brief  Return SAIx clock frequency
  * @param  SAIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE
  * @retval SAI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that PLL is not ready
  */
uint32_t LL_RCC_GetSAIClockFreq(uint32_t SAIxSource)
{
  uint32_t sai_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_SAI_CLKSOURCE(SAIxSource));

  if (SAIxSource == LL_RCC_SAI1_CLKSOURCE)
  {
    /* SAI1CLK clock frequency */
    switch (LL_RCC_GetSAIClockSource(SAIxSource))
    {
      case LL_RCC_SAI1_CLKSOURCE_PLLSAI1:    /* PLLSAI1 clock used as SAI1 clock source */
        if (LL_RCC_PLLSAI1_IsReady() == 1U)
        {
          sai_frequency = RCC_PLLSAI1_GetFreqDomain_SAI();
        }
        break;

      case LL_RCC_SAI1_CLKSOURCE_PLLSAI2:    /* PLLSAI2 clock used as SAI1 clock source */
        if (LL_RCC_PLLSAI2_IsReady() == 1U)
        {
          sai_frequency = RCC_PLLSAI2_GetFreqDomain_SAI();
        }
        break;

      case LL_RCC_SAI1_CLKSOURCE_PLL:        /* PLL clock used as SAI1 clock source */
        if (LL_RCC_PLL_IsReady() == 1U)
        {
          sai_frequency = RCC_PLL_GetFreqDomain_SAI();
        }
        break;

      case LL_RCC_SAI1_CLKSOURCE_PIN:        /* External input clock used as SAI1 clock source */
        sai_frequency = EXTERNAL_SAI1_CLOCK_VALUE;
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else if (SAIxSource == LL_RCC_SAI2_CLKSOURCE)
  {
    /* SAI2CLK clock frequency */
    switch (LL_RCC_GetSAIClockSource(SAIxSource))
    {
      case LL_RCC_SAI2_CLKSOURCE_PLLSAI1:    /* PLLSAI1 clock used as SAI2 clock source */
        if (LL_RCC_PLLSAI1_IsReady() == 1U)
        {
          sai_frequency = RCC_PLLSAI1_GetFreqDomain_SAI();
        }
        break;

      case LL_RCC_SAI2_CLKSOURCE_PLLSAI2:    /* PLLSAI2 clock used as SAI2 clock source */
        if (LL_RCC_PLLSAI2_IsReady() == 1U)
        {
          sai_frequency = RCC_PLLSAI2_GetFreqDomain_SAI();
        }
        break;

      case LL_RCC_SAI2_CLKSOURCE_PLL:        /* PLL clock used as SAI2 clock source */
        if (LL_RCC_PLL_IsReady() == 1U)
        {
          sai_frequency = RCC_PLL_GetFreqDomain_SAI();
        }
        break;

      case LL_RCC_SAI2_CLKSOURCE_PIN:        /* External input clock used as SAI2 clock source */
        sai_frequency = EXTERNAL_SAI2_CLOCK_VALUE;
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else
  {
    /* nothing to do */
  }

  return sai_frequency;
}

/**
  * @brief  Return SDMMCx kernel clock frequency
  * @param  SDMMCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC1_KERNELCLKSOURCE
  * @retval SDMMC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready
  */
uint32_t LL_RCC_GetSDMMCKernelClockFreq(uint32_t SDMMCxSource)
{
  uint32_t sdmmc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_SDMMC_KERNELCLKSOURCE(SDMMCxSource));

  /* SDMMC1CLK kernel clock frequency */
  switch (LL_RCC_GetSDMMCKernelClockSource(SDMMCxSource))
  {
    case LL_RCC_SDMMC1_KERNELCLKSOURCE_48CLK:      /* 48MHz clock from internal multiplexor used as SDMMC1 clock source */
      sdmmc_frequency = LL_RCC_GetSDMMCClockFreq(LL_RCC_SDMMC1_CLKSOURCE);
      break;

    case LL_RCC_SDMMC1_KERNELCLKSOURCE_PLLP:       /* PLL "P" output (PLLSAI3CLK) clock used as SDMMC1 clock source */
      if (LL_RCC_PLL_IsReady() == 1U)
      {
        sdmmc_frequency = RCC_PLL_GetFreqDomain_SAI();
      }
      break;

    default:
      /* unreachable code */
      break;
  }

  return sdmmc_frequency;
}

/**
  * @brief  Return SDMMCx clock frequency
  * @param  SDMMCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC1_CLKSOURCE
  * @retval SDMMC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSI or HSI48) or PLL is not ready
  */
uint32_t LL_RCC_GetSDMMCClockFreq(uint32_t SDMMCxSource)
{
  uint32_t sdmmc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_SDMMC_CLKSOURCE(SDMMCxSource));

  /* SDMMC1CLK clock frequency */
  switch (LL_RCC_GetSDMMCClockSource(SDMMCxSource))
  {
    case LL_RCC_SDMMC1_CLKSOURCE_PLLSAI1:    /* PLLSAI1 clock used as SDMMC1 clock source */
      if (LL_RCC_PLLSAI1_IsReady() == 1U)
      {
        sdmmc_frequency = RCC_PLLSAI1_GetFreqDomain_48M();
      }
      break;

    case LL_RCC_SDMMC1_CLKSOURCE_PLL:        /* PLL clock used as SDMMC1 clock source */
      if (LL_RCC_PLL_IsReady() == 1U)
      {
        sdmmc_frequency = RCC_PLL_GetFreqDomain_48M();
      }
      break;

    case LL_RCC_SDMMC1_CLKSOURCE_MSI:        /* MSI clock used as SDMMC1 clock source */
      if (LL_RCC_MSI_IsReady() == 1U)
      {
        sdmmc_frequency = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                 ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                  LL_RCC_MSI_GetRange() :
                                                  LL_RCC_MSI_GetRangeAfterStandby()));
      }
      break;

    case LL_RCC_SDMMC1_CLKSOURCE_HSI48:      /* HSI48 used as SDMMC1 clock source */
      if (LL_RCC_HSI48_IsReady() == 1U)
      {
        sdmmc_frequency = HSI48_VALUE;
      }
      break;


    default:
      /* unreachable code */
      break;
  }

  return sdmmc_frequency;
}

/**
  * @brief  Return RNGx clock frequency
  * @param  RNGxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE
  * @retval RNG clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSI or HSI48) or PLL is not ready
  */
uint32_t LL_RCC_GetRNGClockFreq(uint32_t RNGxSource)
{
  uint32_t rng_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_RNG_CLKSOURCE(RNGxSource));

  /* RNGCLK clock frequency */
  switch (LL_RCC_GetRNGClockSource(RNGxSource))
  {
    case LL_RCC_RNG_CLKSOURCE_PLLSAI1:       /* PLLSAI1 clock used as RNG clock source */
      if (LL_RCC_PLLSAI1_IsReady() == 1U)
      {
        rng_frequency = RCC_PLLSAI1_GetFreqDomain_48M();
      }
      break;

    case LL_RCC_RNG_CLKSOURCE_PLL:           /* PLL clock used as RNG clock source */
      if (LL_RCC_PLL_IsReady() == 1U)
      {
        rng_frequency = RCC_PLL_GetFreqDomain_48M();
      }
      break;

    case LL_RCC_RNG_CLKSOURCE_MSI:           /* MSI clock used as RNG clock source */
      if (LL_RCC_MSI_IsReady() == 1U)
      {
        rng_frequency = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                               ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                LL_RCC_MSI_GetRange() :
                                                LL_RCC_MSI_GetRangeAfterStandby()));
      }
      break;

    case LL_RCC_RNG_CLKSOURCE_HSI48:         /* HSI48 clock used as RNG clock source */
      if (LL_RCC_HSI48_IsReady() == 1U)
      {
        rng_frequency = HSI48_VALUE;
      }
      break;

    default:
      /* unreachable code */
      break;
  }

  return rng_frequency;
}

/**
  * @brief  Return USBx clock frequency
  * @param  USBxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USB_CLKSOURCE
  * @retval USB clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSI or HSI48) or PLL is not ready
  */
uint32_t LL_RCC_GetUSBClockFreq(uint32_t USBxSource)
{
  uint32_t usb_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_USB_CLKSOURCE(USBxSource));

  /* USBCLK clock frequency */
  switch (LL_RCC_GetUSBClockSource(USBxSource))
  {
    case LL_RCC_USB_CLKSOURCE_PLLSAI1:       /* PLLSAI1 clock used as USB clock source */
      if (LL_RCC_PLLSAI1_IsReady() == 1U)
      {
        usb_frequency = RCC_PLLSAI1_GetFreqDomain_48M();
      }
      break;

    case LL_RCC_USB_CLKSOURCE_PLL:           /* PLL clock used as USB clock source */
      if (LL_RCC_PLL_IsReady() == 1U)
      {
        usb_frequency = RCC_PLL_GetFreqDomain_48M();
      }
      break;

    case LL_RCC_USB_CLKSOURCE_MSI:           /* MSI clock used as USB clock source */
      if (LL_RCC_MSI_IsReady() == 1U)
      {
        usb_frequency = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                               ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                LL_RCC_MSI_GetRange() :
                                                LL_RCC_MSI_GetRangeAfterStandby()));
      }
      break;

    case LL_RCC_USB_CLKSOURCE_HSI48:         /* HSI48 clock used as USB clock source */
      if (LL_RCC_HSI48_IsReady() == 1U)
      {
        usb_frequency = HSI48_VALUE;
      }
      break;

    default:
      /* unreachable code */
      break;
  }

  return usb_frequency;
}

/**
  * @brief  Return ADCx clock frequency
  * @param  ADCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE
  * @retval ADC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready
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
    case LL_RCC_ADC_CLKSOURCE_PLLSAI1:       /* PLLSAI1 clock used as ADC clock source */
      if (LL_RCC_PLLSAI1_IsReady() == 1U)
      {
        adc_frequency = RCC_PLLSAI1_GetFreqDomain_ADC();
      }
      break;

    case LL_RCC_ADC_CLKSOURCE_SYSCLK:        /* SYSCLK clock used as ADC clock source */
      adc_frequency = RCC_GetSystemClockFreq();
      break;

    case LL_RCC_ADC_CLKSOURCE_NONE:          /* No clock used as ADC clock source */
      adc_frequency = LL_RCC_PERIPH_FREQUENCY_NA;
      break;

    default:
      /* unreachable code */
      break;
  }

  return adc_frequency;
}

/**
  * @brief  Return DFSDMx clock frequency
  * @param  DFSDMxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DFSDM1_CLKSOURCE
  * @retval DFSDM clock frequency (in Hz)
  */
uint32_t LL_RCC_GetDFSDMClockFreq(uint32_t DFSDMxSource)
{
  uint32_t dfsdm_frequency;

  /* Check parameter */
  assert_param(IS_LL_RCC_DFSDM_CLKSOURCE(DFSDMxSource));

  /* DFSDM1CLK clock frequency */
  if (LL_RCC_GetDFSDMClockSource(DFSDMxSource) == LL_RCC_DFSDM1_CLKSOURCE_PCLK2)
  {
    /* DFSDM1 Clock is PCLK2 */
    dfsdm_frequency = RCC_GetPCLK2ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
  }
  else
  {
    /* DFSDM1 Clock is SYSCLK */
    dfsdm_frequency = RCC_GetSystemClockFreq();
  }

  return dfsdm_frequency;
}

/**
  * @brief  Return DFSDMx Audio clock frequency
  * @param  DFSDMxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DFSDM1_AUDIO_CLKSOURCE
  * @retval DFSDM clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSI or HSI) is not ready
  */
uint32_t LL_RCC_GetDFSDMAudioClockFreq(uint32_t DFSDMxSource)
{
  uint32_t dfsdm_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_DFSDM_AUDIO_CLKSOURCE(DFSDMxSource));

  /* DFSDM1CLK clock frequency */
  switch (LL_RCC_GetDFSDMAudioClockSource(DFSDMxSource))
  {
    case LL_RCC_DFSDM1_AUDIO_CLKSOURCE_SAI1:     /* SAI1 clock used as DFSDM1 audio clock */
      dfsdm_frequency = LL_RCC_GetSAIClockFreq(LL_RCC_SAI1_CLKSOURCE);
      break;

    case LL_RCC_DFSDM1_AUDIO_CLKSOURCE_MSI:      /* MSI clock used as DFSDM1 audio clock */
      if (LL_RCC_MSI_IsReady() == 1U)
      {
        dfsdm_frequency = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                 ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                  LL_RCC_MSI_GetRange() :
                                                  LL_RCC_MSI_GetRangeAfterStandby()));
      }
      break;

    case LL_RCC_DFSDM1_AUDIO_CLKSOURCE_HSI:      /* HSI clock used as DFSDM1 audio clock */
      if (LL_RCC_HSI_IsReady() == 1U)
      {
        dfsdm_frequency = HSI_VALUE;
      }
      break;

    default:
      /* unreachable code */
      break;
  }

  return dfsdm_frequency;
}

/**
  * @brief  Return OCTOSPI clock frequency
  * @param  OCTOSPIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE
  * @retval OCTOSPI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSI) or PLL is not ready
  */
uint32_t LL_RCC_GetOCTOSPIClockFreq(uint32_t OCTOSPIxSource)
{
  uint32_t octospi_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_OCTOSPI_CLKSOURCE(OCTOSPIxSource));

  /* OCTOSPI clock frequency */
  switch (LL_RCC_GetOCTOSPIClockSource(OCTOSPIxSource))
  {
    case LL_RCC_OCTOSPI_CLKSOURCE_SYSCLK:   /* OCTOSPI clock is SYSCLK */
      octospi_frequency = RCC_GetSystemClockFreq();
      break;

    case LL_RCC_OCTOSPI_CLKSOURCE_MSI:      /* MSI clock used as OCTOSPI clock */
      if (LL_RCC_MSI_IsReady() == 1U)
      {
        octospi_frequency = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                   ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                    LL_RCC_MSI_GetRange() :
                                                    LL_RCC_MSI_GetRangeAfterStandby()));
      }
      break;

    case LL_RCC_OCTOSPI_CLKSOURCE_PLL:      /* PLL clock used as OCTOSPI source */
      if (LL_RCC_PLL_IsReady() == 1U)
      {
        octospi_frequency = RCC_PLL_GetFreqDomain_48M();
      }
      break;

    default:
      /* unreachable code */
      break;
  }

  return octospi_frequency;
}

/**
  * @brief  Return FDCAN kernel clock frequency
  * @param  FDCANxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE
  * @retval FDCAN kernel clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSE) or PLL is not ready
  */
uint32_t LL_RCC_GetFDCANClockFreq(uint32_t FDCANxSource)
{
  uint32_t fdcan_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_FDCAN_CLKSOURCE(FDCANxSource));

  /* FDCAN kernel clock frequency */
  switch (LL_RCC_GetFDCANClockSource(FDCANxSource))
  {
    case LL_RCC_FDCAN_CLKSOURCE_HSE:   /* HSE clock used as FDCAN kernel clock */
      if (LL_RCC_HSE_IsReady() == 1U)
      {
        fdcan_frequency = HSE_VALUE;
      }
      break;

    case LL_RCC_FDCAN_CLKSOURCE_PLL:   /* PLL clock used as FDCAN kernel clock */
      if (LL_RCC_PLL_IsReady() == 1U)
      {
        fdcan_frequency = RCC_PLL_GetFreqDomain_48M();
      }
      break;

    case LL_RCC_FDCAN_CLKSOURCE_PLLSAI1:      /* MSI clock used as FDCAN kernel clock */
      if (LL_RCC_PLLSAI1_IsReady() == 1U)
      {
        fdcan_frequency = RCC_PLLSAI1_GetFreqDomain_SAI();
      }
      break;

    default:
      /* unreachable code */
      break;
  }

  return fdcan_frequency;
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
  * @brief  Return SYSTEM clock frequency
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
                                         ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                          LL_RCC_MSI_GetRange() :
                                          LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_HSI:  /* HSI used as system clock  source */
      frequency = HSI_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_HSE:  /* HSE used as system clock  source */
      frequency = HSE_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_PLL:  /* PLL used as system clock  source */
      frequency = RCC_PLL_GetFreqDomain_SYS();
      break;

    default:
      frequency = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                         ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                          LL_RCC_MSI_GetRange() :
                                          LL_RCC_MSI_GetRangeAfterStandby()));
      break;
  }

  return frequency;
}

/**
  * @brief  Return HCLK clock frequency
  * @param  SYSCLK_Frequency SYSCLK clock frequency
  * @retval HCLK clock frequency (in Hz)
  */
static uint32_t RCC_GetHCLKClockFreq(uint32_t SYSCLK_Frequency)
{
  /* HCLK clock frequency */
  return __LL_RCC_CALC_HCLK_FREQ(SYSCLK_Frequency, LL_RCC_GetAHBPrescaler());
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
  * @brief  Return PLL clock frequency used for system domain
  * @retval PLL clock frequency (in Hz)
  */
static uint32_t RCC_PLL_GetFreqDomain_SYS(void)
{
  uint32_t pllinputfreq, pllsource;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLLM) * PLLN
     SYSCLK = PLL_VCO / PLLR
  */
  pllsource = LL_RCC_PLL_GetMainSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_MSI:  /* MSI used as PLL clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
      pllinputfreq = HSE_VALUE;
      break;

    default:
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;
  }
  return __LL_RCC_CALC_PLLCLK_FREQ(pllinputfreq, LL_RCC_PLL_GetDivider(),
                                   LL_RCC_PLL_GetN(), LL_RCC_PLL_GetR());
}
/**
  * @brief  Return PLL clock frequency used for SAI domain
  * @retval PLL clock frequency (in Hz)
  */
static uint32_t RCC_PLL_GetFreqDomain_SAI(void)
{
  uint32_t pllinputfreq, plloutputfreq, pllsource;
  uint32_t plln, pllpdiv;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE / PLLM) * PLLN
     SAI Domain clock = PLL_VCO / PLLP
  */
  pllsource = LL_RCC_PLL_GetMainSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_MSI:  /* MSI used as PLL clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
      pllinputfreq = HSE_VALUE;
      break;

    default:
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;
  }

  plln = LL_RCC_PLL_GetN();
  pllpdiv = LL_RCC_PLL_GetP();
  if ((plln >= 8U) && (pllpdiv >= LL_RCC_PLLP_DIV_2))
  {
    plloutputfreq = __LL_RCC_CALC_PLLCLK_SAI_FREQ(pllinputfreq, LL_RCC_PLL_GetDivider(),
                                                  plln, pllpdiv);
  }
  else
  {
    plloutputfreq = 0;  /* Invalid PLLN or PLLPDIV value */
  }
  return plloutputfreq;
}

/**
  * @brief  Return PLL clock frequency used for 48 MHz domain
  * @retval PLL clock frequency (in Hz)
  */
static uint32_t RCC_PLL_GetFreqDomain_48M(void)
{
  uint32_t pllinputfreq, pllsource;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLLM) * PLLN
     48M Domain clock = PLL_VCO / PLLQ
  */
  pllsource = LL_RCC_PLL_GetMainSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_MSI:  /* MSI used as PLL clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
      pllinputfreq = HSE_VALUE;
      break;

    default:
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;
  }
  return __LL_RCC_CALC_PLLCLK_48M_FREQ(pllinputfreq, LL_RCC_PLL_GetDivider(),
                                       LL_RCC_PLL_GetN(), LL_RCC_PLL_GetQ());
}

/**
  * @brief  Return PLLSAI1 clock frequency used for SAI domain
  * @retval PLLSAI1 clock frequency (in Hz)
  */
static uint32_t RCC_PLLSAI1_GetFreqDomain_SAI(void)
{
  uint32_t pllinputfreq, plloutputfreq, pllsource;
  uint32_t plln, pllpdiv;

  /* PLLSAI1_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLLSAI1M) * PLLSAI1N */
  /* SAI Domain clock  = PLLSAI1_VCO / PLLSAI1P */
  pllsource = LL_RCC_PLLSAI1_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_MSI:  /* MSI used as PLLSAI1 clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:  /* HSI used as PLLSAI1 clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLLSOURCE_HSE:  /* HSE used as PLLSAI1 clock source */
      pllinputfreq = HSE_VALUE;
      break;

    default:
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;
  }

  plln = LL_RCC_PLLSAI1_GetN();
  pllpdiv = LL_RCC_PLLSAI1_GetP();
  if ((plln >= 8U) && (pllpdiv >= LL_RCC_PLLSAI1P_DIV_2))
  {
    plloutputfreq = __LL_RCC_CALC_PLLSAI1_SAI_FREQ(pllinputfreq, LL_RCC_PLLSAI1_GetDivider(),
                                                   plln, pllpdiv);
  }
  else
  {
    plloutputfreq = 0;  /* Invalid PLLSAI1N or PLLSAI1PDIV value */
  }
  return plloutputfreq;
}

/**
  * @brief  Return PLLSAI1 clock frequency used for 48Mhz domain
  * @retval PLLSAI1 clock frequency (in Hz)
  */
static uint32_t RCC_PLLSAI1_GetFreqDomain_48M(void)
{
  uint32_t pllinputfreq, pllsource;

  /* PLLSAI1_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLLSAI1M) * PLLSAI1N */
  /* 48M Domain clock  = PLLSAI1_VCO / PLLSAI1Q */
  pllsource = LL_RCC_PLLSAI1_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_MSI:  /* MSI used as PLLSAI1 clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:  /* HSI used as PLLSAI1 clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLLSOURCE_HSE:  /* HSE used as PLLSAI1 clock source */
      pllinputfreq = HSE_VALUE;
      break;

    default:
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;
  }
  return __LL_RCC_CALC_PLLSAI1_48M_FREQ(pllinputfreq, LL_RCC_PLLSAI1_GetDivider(),
                                        LL_RCC_PLLSAI1_GetN(), LL_RCC_PLLSAI1_GetQ());
}

/**
  * @brief  Return PLLSAI1 clock frequency used for ADC domain
  * @retval PLLSAI1 clock frequency (in Hz)
  */
static uint32_t RCC_PLLSAI1_GetFreqDomain_ADC(void)
{
  uint32_t pllinputfreq, pllsource;

  /* PLLSAI1_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLLSAI1M) * PLLSAI1N */
  /* 48M Domain clock  = PLLSAI1_VCO / PLLSAI1R */
  pllsource = LL_RCC_PLLSAI1_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_MSI:  /* MSI used as PLLSAI1 clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:  /* HSI used as PLLSAI1 clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLLSOURCE_HSE:  /* HSE used as PLLSAI1 clock source */
      pllinputfreq = HSE_VALUE;
      break;

    default:
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;
  }
  return __LL_RCC_CALC_PLLSAI1_ADC_FREQ(pllinputfreq, LL_RCC_PLLSAI1_GetDivider(),
                                        LL_RCC_PLLSAI1_GetN(), LL_RCC_PLLSAI1_GetR());
}

/**
  * @brief  Return PLLSAI2 clock frequency used for SAI domain
  * @retval PLLSAI2 clock frequency (in Hz)
  */
static uint32_t RCC_PLLSAI2_GetFreqDomain_SAI(void)
{
  uint32_t pllinputfreq, plloutputfreq, pllsource;
  uint32_t plln, pllpdiv;

  /* PLLSAI2_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLLSAI2M) * PLLSAI2N */
  /* SAI Domain clock  = PLLSAI2_VCO / PLLSAI2P */
  pllsource = LL_RCC_PLLSAI2_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_MSI:  /* MSI used as PLLSAI2 clock source */
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLLSOURCE_HSI:  /* HSI used as PLLSAI2 clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLLSOURCE_HSE:  /* HSE used as PLLSAI2 clock source */
      pllinputfreq = HSE_VALUE;
      break;

    default:
      pllinputfreq = __LL_RCC_CALC_MSI_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                            ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                             LL_RCC_MSI_GetRange() :
                                             LL_RCC_MSI_GetRangeAfterStandby()));
      break;
  }

  plln = LL_RCC_PLLSAI2_GetN();
  pllpdiv = LL_RCC_PLLSAI2_GetP();
  if ((plln >= 8U) && (pllpdiv >= LL_RCC_PLLSAI2P_DIV_2))
  {
    plloutputfreq = __LL_RCC_CALC_PLLSAI2_SAI_FREQ(pllinputfreq, LL_RCC_PLLSAI2_GetDivider(),
                                                   plln, pllpdiv);
  }
  else
  {
    plloutputfreq = 0;  /* Invalid PLLSAI2N or PLLSAI2PDIV value */
  }
  return plloutputfreq;
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
