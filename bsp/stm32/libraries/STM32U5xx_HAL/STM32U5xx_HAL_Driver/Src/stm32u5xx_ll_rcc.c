/**
  ******************************************************************************
  * @file    stm32u5xx_ll_rcc.c
  * @author  MCD Application Team
  * @brief   RCC LL module driver.
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
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_ll_rcc.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */
/** @addtogroup STM32U5xx_LL_Driver
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

#define IS_LL_RCC_SPI_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_SPI1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_SPI2_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_SPI3_CLKSOURCE))

#define IS_LL_RCC_LPTIM_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_LPTIM1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPTIM2_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPTIM34_CLKSOURCE))

#define IS_LL_RCC_SAI_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_SAI1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_SAI2_CLKSOURCE))

#define IS_LL_RCC_SDMMC_KERNELCLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_SDMMC_KERNELCLKSOURCE))

#define IS_LL_RCC_SDMMC_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_SDMMC_CLKSOURCE))

#define IS_LL_RCC_RNG_CLKSOURCE(__VALUE__)      (((__VALUE__) == LL_RCC_RNG_CLKSOURCE))

#define IS_LL_RCC_USB_CLKSOURCE(__VALUE__)      (((__VALUE__) == LL_RCC_USB_CLKSOURCE))

#define IS_LL_RCC_ADCDAC_CLKSOURCE(__VALUE__)   (((__VALUE__) == LL_RCC_ADCDAC_CLKSOURCE))

#define IS_LL_RCC_MDF1_CLKSOURCE(__VALUE__)     (((__VALUE__) == LL_RCC_MDF1_CLKSOURCE))

#define IS_LL_RCC_DAC1_CLKSOURCE(__VALUE__)     (((__VALUE__) == LL_RCC_DAC1_CLKSOURCE))

#define IS_LL_RCC_ADF1_CLKSOURCE(__VALUE__)     (((__VALUE__) == LL_RCC_ADF1_CLKSOURCE))

#define IS_LL_RCC_OCTOSPI_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_OCTOSPI_CLKSOURCE))

#define IS_LL_RCC_SAES_CLKSOURCE(__VALUE__)     (((__VALUE__) == LL_RCC_SAES_CLKSOURCE))

#define IS_LL_RCC_FDCAN_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_FDCAN_CLKSOURCE))

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_LL_Private_Functions RCC Private functions
  * @{
  */
static uint32_t RCC_GetSystemClockFreq(void);
static uint32_t RCC_GetHCLKClockFreq(uint32_t SYSCLK_Frequency);
static uint32_t RCC_GetPCLK1ClockFreq(uint32_t HCLK_Frequency);
static uint32_t RCC_GetPCLK2ClockFreq(uint32_t HCLK_Frequency);
static uint32_t RCC_GetPCLK3ClockFreq(uint32_t HCLK_Frequency);
static uint32_t RCC_PLL1_GetFreqDomain_SYS(void);
static uint32_t RCC_PLL1_GetFreqDomain_SAI(void);
static uint32_t RCC_PLL1_GetFreqDomain_48M(void);
static uint32_t RCC_PLL2_GetFreqDomain_SAI(void);
static uint32_t RCC_PLL2_GetFreqDomain_48M(void);
static uint32_t RCC_PLL2_GetFreqDomain_ADC(void);
static uint32_t RCC_PLL3_GetFreqDomain_SAI(void);
static uint32_t RCC_PLL3_GetFreqDomain_48M(void);
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
  *         - HSE, HSI, PLL1, PLL2 and PLL3 OFF
  *         - AHB, APB1, APB2 and APB3 prescaler set to 1.
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
  uint32_t vl_mask;

  /* Set MSION bit */
  LL_RCC_MSIS_Enable();

  /* Insure MSIRDY bit is set before writing default MSIRANGE value */
  while (LL_RCC_MSIS_IsReady() == 0U)
  {
  }

  /* Set MSIRANGE default value */
  LL_RCC_MSIS_SetRange(LL_RCC_MSISRANGE_4);

  /* Set MSITRIM bits to the reset value*/
  LL_RCC_MSI_SetCalibTrimming(0, LL_RCC_MSI_OSCILLATOR_1);

  /* Set HSITRIM bits to the reset value*/
  LL_RCC_HSI_SetCalibTrimming(0x40U);

  /* Reset CFGR register */
  LL_RCC_WriteReg(CFGR1, 0x00000000U);
  LL_RCC_WriteReg(CFGR2, 0x00000000U);
  LL_RCC_WriteReg(CFGR3, 0x00000000U);

  /* Read CR register */
  vl_mask = LL_RCC_ReadReg(CR);

  /* Reset HSION, HSIKERON, HSEON, PLL1ON, PLL2ON and PLL3ON bits */
  CLEAR_BIT(vl_mask, (RCC_CR_HSION | RCC_CR_HSIKERON  | RCC_CR_HSEON |
                      RCC_CR_PLL1ON | RCC_CR_PLL2ON | RCC_CR_PLL3ON));

  /* Write new mask in CR register */
  LL_RCC_WriteReg(CR, vl_mask);

  /* Wait for PLL1RDY, PLL2RDY and PLL3RDY bits to be reset */
  while (READ_BIT(RCC->CR, RCC_CR_PLL1RDY | RCC_CR_PLL2RDY | RCC_CR_PLL3RDY) != 0U)
  {
  }

  /* Reset PLL1DIVR register */
  LL_RCC_WriteReg(PLL1DIVR, 0x01010280U);

  /* Reset PLL2DIVR register */
  LL_RCC_WriteReg(PLL2DIVR, 0x01010280U);

  /* Reset PLL3DIVR register */
  LL_RCC_WriteReg(PLL3DIVR, 0x01010280U);

  /* Reset HSEBYP bit */
  LL_RCC_HSE_DisableBypass();

  /* Disable all interrupts */
  LL_RCC_WriteReg(CIER, 0x00000000U);

  /* Clear all interrupt flags */
  vl_mask = RCC_CICR_LSIRDYC | RCC_CICR_LSERDYC | RCC_CICR_MSISRDYC | RCC_CICR_HSIRDYC | RCC_CICR_HSERDYC | \
            RCC_CICR_PLL1RDYC | RCC_CICR_PLL2RDYC | RCC_CICR_PLL3RDYC | RCC_CICR_HSI48RDYC | RCC_CICR_CSSC | \
            RCC_CICR_MSIKRDYC;
  LL_RCC_WriteReg(CICR, vl_mask);

  /* Clear reset flags */
  LL_RCC_ClearResetFlags();

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
  * @note   Each time SYSCLK, HCLK, PCLK1, PCLK2 and/or PCLK3 clock changes, this function
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

  /* PCLK3 clock frequency */
  RCC_Clocks->PCLK3_Frequency  = RCC_GetPCLK3ClockFreq(RCC_Clocks->HCLK_Frequency);
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
      case LL_RCC_UART4_CLKSOURCE_SYSCLK:  /* UART4 Clock is System Clock */
        uart_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_UART4_CLKSOURCE_HSI:     /* UART4 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          uart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_UART4_CLKSOURCE_LSE:     /* UART4 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          uart_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_UART4_CLKSOURCE_PCLK1:   /* UART4 Clock is PCLK1 */
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
  * @brief  Return SPIx clock frequency
  * @param  SPIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE
  * @retval SPI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI or MSIK) is not ready
  */
uint32_t LL_RCC_GetSPIClockFreq(uint32_t SPIxSource)
{
  uint32_t SPI_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_SPI_CLKSOURCE(SPIxSource));

  if (SPIxSource == LL_RCC_SPI1_CLKSOURCE)
  {
    /* SPI1 CLK clock frequency */
    switch (LL_RCC_GetSPIClockSource(SPIxSource))
    {
      case LL_RCC_SPI1_CLKSOURCE_SYSCLK: /* SPI1 Clock is System Clock */
        SPI_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_SPI1_CLKSOURCE_HSI:    /* SPI1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          SPI_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_SPI1_CLKSOURCE_MSIK:    /* SPI1 Clock is MSIK Osc.*/
        SPI_frequency = __LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                 LL_RCC_MSIK_GetRange() :
                                                 LL_RCC_MSIK_GetRangeAfterStandby()));
        break;

      case LL_RCC_SPI1_CLKSOURCE_PCLK2:  /* SPI1 Clock is PCLK2 */
        SPI_frequency = RCC_GetPCLK2ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else if (SPIxSource == LL_RCC_SPI2_CLKSOURCE)
  {
    /* SPI2 CLK clock frequency */
    switch (LL_RCC_GetSPIClockSource(SPIxSource))
    {
      case LL_RCC_SPI2_CLKSOURCE_SYSCLK: /* SPI2 Clock is System Clock */
        SPI_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_SPI2_CLKSOURCE_HSI:    /* SPI2 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          SPI_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_SPI2_CLKSOURCE_MSIK:  /* SPI2 Clock is MSIK Osc.*/
        SPI_frequency = __LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                 LL_RCC_MSIK_GetRange() :
                                                 LL_RCC_MSIK_GetRangeAfterStandby()));
        break;

      case LL_RCC_SPI2_CLKSOURCE_PCLK1:  /* SPI2 Clock is PCLK1 */
        SPI_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      default:
        /* unreachable code */
        break;

    }
  }
  else if (SPIxSource == LL_RCC_SPI3_CLKSOURCE)
  {
    /* SPI3 CLK clock frequency */
    switch (LL_RCC_GetSPIClockSource(SPIxSource))
    {
      case LL_RCC_SPI3_CLKSOURCE_SYSCLK: /* SPI3 Clock is System Clock */
        SPI_frequency = RCC_GetSystemClockFreq();
        break;

      case LL_RCC_SPI3_CLKSOURCE_HSI:    /* SPI3 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          SPI_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_SPI3_CLKSOURCE_MSIK:  /* SPI3 Clock is MSIK Osc. */
        SPI_frequency = __LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                 LL_RCC_MSIK_GetRange() :
                                                 LL_RCC_MSIK_GetRangeAfterStandby()));
        break;

      case LL_RCC_SPI3_CLKSOURCE_PCLK3:   /* SPI3 Clock is PCLK3 */
        SPI_frequency = RCC_GetPCLK3ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
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

  return SPI_frequency;
}

/**
  * @brief  Return I2Cx clock frequency
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE
  * @retval I2C clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI or MSIK) is not ready
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

      case LL_RCC_I2C1_CLKSOURCE_MSIK:    /* I2C1 Clock is MSIK Osc.*/
        i2c_frequency = __LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                 LL_RCC_MSIK_GetRange() :
                                                 LL_RCC_MSIK_GetRangeAfterStandby()));
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

      case LL_RCC_I2C2_CLKSOURCE_MSIK:    /* I2C2 Clock is MSIK Osc.*/
        i2c_frequency = __LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                 LL_RCC_MSIK_GetRange() :
                                                 LL_RCC_MSIK_GetRangeAfterStandby()));
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

      case LL_RCC_I2C3_CLKSOURCE_MSIK:   /* I2C3 Clock is MSIK Osc.*/
        i2c_frequency = __LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                 LL_RCC_MSIK_GetRange() :
                                                 LL_RCC_MSIK_GetRangeAfterStandby()));
        break;
      case LL_RCC_I2C3_CLKSOURCE_PCLK3:  /* I2C3 Clock is PCLK3 */
        i2c_frequency = RCC_GetPCLK3ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
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

      case LL_RCC_I2C4_CLKSOURCE_MSIK:   /* I2C4 Clock is MSIK Osc.*/
        i2c_frequency = __LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                 LL_RCC_MSIK_GetRange() :
                                                 LL_RCC_MSIK_GetRangeAfterStandby()));
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

    case LL_RCC_LPUART1_CLKSOURCE_PCLK3:  /* LPUART1 Clock is PCLK3 */
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
  *         @arg @ref LL_RCC_LPTIM34_CLKSOURCE
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

      case LL_RCC_LPTIM1_CLKSOURCE_MSIK:   /* LPTIM1 Clock is MSIK Osc.*/
        lptim_frequency = __LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                  ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                   LL_RCC_MSIK_GetRange() :
                                                   LL_RCC_MSIK_GetRangeAfterStandby()));
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
  else if (LPTIMxSource == LL_RCC_LPTIM34_CLKSOURCE)
  {
    /* LPTIM34CLK clock frequency */
    switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
    {
      case LL_RCC_LPTIM34_CLKSOURCE_LSI:    /* LPTIM34 Clock is LSI Osc. */
        if (LL_RCC_LSI_IsReady() == 1U)
        {
          lptim_frequency = LSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM34_CLKSOURCE_HSI:    /* LPTIM34 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          lptim_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM34_CLKSOURCE_LSE:    /* LPTIM34 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          lptim_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPTIM34_CLKSOURCE_MSIK:   /* LPTIM34 Clock is MSIK */
        lptim_frequency = __LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                  ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                   LL_RCC_MSIK_GetRange() :
                                                   LL_RCC_MSIK_GetRangeAfterStandby()));
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
      case LL_RCC_SAI1_CLKSOURCE_PLL2:        /* PLL2 clock used as SAI1 clock source */
        if (LL_RCC_PLL2_IsReady() == 1U)
        {
          sai_frequency = RCC_PLL2_GetFreqDomain_SAI();
        }
        break;

      case LL_RCC_SAI1_CLKSOURCE_PLL3:        /* PLL3 clock used as SAI1 clock source */
        if (LL_RCC_PLL3_IsReady() == 1U)
        {
          sai_frequency = RCC_PLL3_GetFreqDomain_SAI();
        }
        break;

      case LL_RCC_SAI1_CLKSOURCE_PLL1:        /* PLL1 clock used as SAI1 clock source */
        if (LL_RCC_PLL1_IsReady() == 1U)
        {
          sai_frequency = RCC_PLL1_GetFreqDomain_SAI();
        }
        break;

      case LL_RCC_SAI1_CLKSOURCE_PIN:         /* External input clock used as SAI1 clock source */
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
      case LL_RCC_SAI2_CLKSOURCE_PLL2:       /* PLL2 clock used as SAI2 clock source */
        if (LL_RCC_PLL2_IsReady() == 1U)
        {
          sai_frequency = RCC_PLL2_GetFreqDomain_SAI();
        }
        break;

      case LL_RCC_SAI2_CLKSOURCE_PLL3:       /* PLL3 clock used as SAI2 clock source */
        if (LL_RCC_PLL3_IsReady() == 1U)
        {
          sai_frequency = RCC_PLL3_GetFreqDomain_SAI();
        }
        break;

      case LL_RCC_SAI2_CLKSOURCE_PLL1:       /* PLL1 clock used as SAI2 clock source */
        if (LL_RCC_PLL1_IsReady() == 1U)
        {
          sai_frequency = RCC_PLL1_GetFreqDomain_SAI();
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
  *         @arg @ref LL_RCC_SDMMC_KERNELCLKSOURCE
  * @retval SDMMC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready
  */
uint32_t LL_RCC_GetSDMMCKernelClockFreq(uint32_t SDMMCxSource)
{
  uint32_t sdmmc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_SDMMC_KERNELCLKSOURCE(SDMMCxSource));

  /* SDMMC12CLK kernel clock frequency */
  switch (LL_RCC_GetSDMMCKernelClockSource(SDMMCxSource))
  {
    case LL_RCC_SDMMC12_KERNELCLKSOURCE_48CLK: /* 48MHz clock from internal multiplexor used as SDMMC1/2 clock source */
      sdmmc_frequency = LL_RCC_GetSDMMCClockFreq(LL_RCC_SDMMC_CLKSOURCE);
      break;

    case LL_RCC_SDMMC12_KERNELCLKSOURCE_PLL1:   /* PLL1 "P" output (PLL1CLK) clock used as SDMMC1/2 clock source */
      if (LL_RCC_PLL1_IsReady() == 1U)
      {
        sdmmc_frequency = RCC_PLL1_GetFreqDomain_SAI();
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
  *         @arg @ref LL_RCC_SDMMC_CLKSOURCE
  * @retval SDMMC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSI /MSIK /HSI) or PLL is not ready
  */
uint32_t LL_RCC_GetSDMMCClockFreq(uint32_t SDMMCxSource)
{
  uint32_t sdmmc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_SDMMC_CLKSOURCE(SDMMCxSource));

  /* SDMMC1CLK clock frequency */
  switch (LL_RCC_GetSDMMCClockSource(SDMMCxSource))
  {
    case LL_RCC_SDMMC12_CLKSOURCE_PLL2:       /* PLL2 clock used as SDMMC12 clock source */
      if (LL_RCC_PLL2_IsReady() == 1U)
      {
        sdmmc_frequency = RCC_PLL2_GetFreqDomain_48M();
      }
      break;

    case LL_RCC_SDMMC12_CLKSOURCE_PLL1:        /* PLL1 clock used as SDMMC12 clock source */
      if (LL_RCC_PLL1_IsReady() == 1U)
      {
        sdmmc_frequency = RCC_PLL1_GetFreqDomain_48M();
      }
      break;

    case LL_RCC_SDMMC12_CLKSOURCE_MSIK:        /* MSIK clock used as SDMMC12 clock source */
      if (LL_RCC_MSIS_IsReady() == 1U)
      {
        sdmmc_frequency = __LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                  ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                   LL_RCC_MSIK_GetRange() :
                                                   LL_RCC_MSIK_GetRangeAfterStandby()));
      }
      break;

    case LL_RCC_SDMMC12_CLKSOURCE_HSI48:      /* HSI48 used as SDMMC1 clock source */
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
    case LL_RCC_RNG_CLKSOURCE_HSI:            /* HSI clock used as RNG clock source */
      if (LL_RCC_HSI_IsReady() == 1U)
      {
        rng_frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_RNG_CLKSOURCE_HSI48:         /* HSI48 clock used as RNG clock source */
      if (LL_RCC_HSI48_IsReady() == 1U)
      {
        rng_frequency = HSI48_VALUE;
      }
      break;

    case LL_RCC_RNG_CLKSOURCE_HSI48_DIV2:     /* HSI48DIV2 clock used as RNG clock source */
      if (LL_RCC_HSI48_IsReady() == 1U)
      {
        rng_frequency = (HSI48_VALUE / 2U);
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
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSI /HSI48) or PLL is not ready
  */
uint32_t LL_RCC_GetUSBClockFreq(uint32_t USBxSource)
{
  uint32_t usb_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_USB_CLKSOURCE(USBxSource));

  /* USBCLK clock frequency */
  switch (LL_RCC_GetUSBClockSource(USBxSource))
  {
    case LL_RCC_USB_CLKSOURCE_PLL2:          /* PLL2 clock used as USB clock source */
      if (LL_RCC_PLL2_IsReady() == 1U)
      {
        usb_frequency = RCC_PLL2_GetFreqDomain_48M();
      }
      break;

    case LL_RCC_USB_CLKSOURCE_PLL1:          /* PLL1 clock used as USB clock source */
      if (LL_RCC_PLL1_IsReady() == 1U)
      {
        usb_frequency = RCC_PLL1_GetFreqDomain_48M();
      }
      break;

    case LL_RCC_USB_CLKSOURCE_MSIK:           /* MSIK clock used as USB clock source */
      if (LL_RCC_MSIK_IsReady() == 1U)
      {
        usb_frequency = __LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                 LL_RCC_MSIK_GetRange() :
                                                 LL_RCC_MSIK_GetRangeAfterStandby()));
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
  * @brief  Return ADCxDAC clock frequency
  * @param  ADCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE
  * @retval ADC/DAC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSI /HSI /MSIK) or PLL is not ready
  */
uint32_t LL_RCC_GetADCDACClockFreq(uint32_t ADCxSource)
{
  uint32_t adcdac_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_ADCDAC_CLKSOURCE(ADCxSource));

  /* ADCCLK clock frequency */
  switch (LL_RCC_GetADCDACClockSource(ADCxSource))
  {
    case LL_RCC_ADCDAC_CLKSOURCE_HCLK:         /* ADCDAC Clock is SYSCLK */
      adcdac_frequency = RCC_GetSystemClockFreq();
      break;

    case LL_RCC_ADCDAC_CLKSOURCE_SYSCLK:       /* SYSCLK clock used as ADCDAC clock source */
      adcdac_frequency = RCC_GetSystemClockFreq();
      break;

    case LL_RCC_ADCDAC_CLKSOURCE_PLL2:         /* PLL2 clock used as ADCDAC clock source */
      if (LL_RCC_PLL2_IsReady() == 1U)
      {
        adcdac_frequency = RCC_PLL2_GetFreqDomain_ADC();
      }
      break;

    case LL_RCC_ADCDAC_CLKSOURCE_HSI:          /*HSI clock used as ADCDAC clock source */
      if (LL_RCC_HSI_IsReady() == 1U)
      {
        adcdac_frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_ADCDAC_CLKSOURCE_HSE:           /*HSE clock used as ADCDAC clock source */
      if (LL_RCC_HSE_IsReady() == 1U)
      {
        adcdac_frequency = HSE_VALUE;
      }
      break;

    case LL_RCC_ADCDAC_CLKSOURCE_MSIK:          /* MSIK clock used as ADCDAC clock source */
      if (LL_RCC_MSIK_IsReady() == 1U)
      {
        adcdac_frequency = __LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                   ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                    LL_RCC_MSIK_GetRange() :
                                                    LL_RCC_MSIK_GetRangeAfterStandby()));
      }
      break;

    default:
      /* unreachable code */
      break;
  }

  return adcdac_frequency;
}

/**
  * @brief  Return ADF1 clock frequency
  * @param  ADF1Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE
  * @retval ADF1 clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSIK) or PLL is not ready
  */
uint32_t LL_RCC_GetADF1ClockFreq(uint32_t ADF1Source)
{
  uint32_t ADF1_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_ADF1_CLKSOURCE(ADF1Source));

  /* ADF11CLK clock frequency */
  switch (LL_RCC_GetADF1ClockSource(ADF1Source))
  {
    case LL_RCC_ADF1_CLKSOURCE_HCLK:        /* ADF1 Clock is SYSCLK */
      ADF1_frequency = RCC_GetSystemClockFreq();
      break;

    case LL_RCC_ADF1_CLKSOURCE_PLL1:       /* ADF1 Clock is PLL1 */
      ADF1_frequency = RCC_PLL1_GetFreqDomain_SAI();
      break;

    case LL_RCC_ADF1_CLKSOURCE_PLL3:       /* ADF1 Clock is PLL3 */
      ADF1_frequency = RCC_PLL3_GetFreqDomain_48M();
      break;

    case LL_RCC_ADF1_CLKSOURCE_PIN:        /* External input clock used as ADF1 clock source */
      ADF1_frequency = EXTERNAL_SAI1_CLOCK_VALUE;
      break;

    case LL_RCC_ADF1_CLKSOURCE_MSIK:        /* ADF1 Clock is MSIK */
      ADF1_frequency = __LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                               ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                LL_RCC_MSIK_GetRange() :
                                                LL_RCC_MSIK_GetRangeAfterStandby()));
      break;

    default:
      /* unreachable code */
      break;
  }

  return ADF1_frequency;
}

/**
  * @brief  Return MDF1 clock frequency
  * @param  MDF1Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_MDF1_CLKSOURCE
  * @retval MDF1 clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (MSIK) or PLL is not ready
  */
uint32_t LL_RCC_GetMDF1ClockFreq(uint32_t MDF1Source)
{
  uint32_t MDF1_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_MDF1_CLKSOURCE(MDF1Source));

  /* MDF11CLK clock frequency */
  switch (LL_RCC_GetMDF1ClockSource(MDF1Source))
  {
    case LL_RCC_MDF1_CLKSOURCE_HCLK:        /* MDF1 Clock is SYSCLK */
      MDF1_frequency = RCC_GetSystemClockFreq();
      break;

    case LL_RCC_MDF1_CLKSOURCE_PLL1:        /* MDF1 Clock is PLL1 */
      MDF1_frequency = RCC_PLL1_GetFreqDomain_SAI();
      break;

    case LL_RCC_MDF1_CLKSOURCE_PLL3:        /* MDF1 Clock is PLL3 */
      MDF1_frequency = RCC_PLL3_GetFreqDomain_48M();
      break;

    case LL_RCC_MDF1_CLKSOURCE_PIN:         /* External input clock used as MDF1 clock source */
      MDF1_frequency = EXTERNAL_SAI1_CLOCK_VALUE;
      break;

    case LL_RCC_MDF1_CLKSOURCE_MSIK:        /* MDF1 Clock is MSIK */
      MDF1_frequency = __LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                               ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                LL_RCC_MSIK_GetRange() :
                                                LL_RCC_MSIK_GetRangeAfterStandby()));
      break;

    default:
      /* unreachable code */
      break;
  }

  return MDF1_frequency;
}

/**
  * @brief  Return DAC1 clock frequency
  * @param  DAC1Source This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC1_CLKSOURCE
  * @retval DAC1 clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that LSI or LSE oscillator is not ready
  */
uint32_t LL_RCC_GetDAC1ClockFreq(uint32_t DAC1Source)
{
  uint32_t DAC1_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_DAC1_CLKSOURCE(DAC1Source));

  /* DAC1CLK clock frequency */
  switch (LL_RCC_GetDAC1ClockSource(DAC1Source))
  {
    case LL_RCC_DAC1_CLKSOURCE_LSI:         /* DAC1 Clock is LSI  */
      DAC1_frequency = LSI_VALUE;
      break;

    case LL_RCC_DAC1_CLKSOURCE_LSE:         /* DAC1 Clock is LSE  */
      DAC1_frequency = LSE_VALUE;
      break;

    default:
      /* unreachable code */
      break;
  }

  return DAC1_frequency;
}

/**
  * @brief  Return OCTOSPI clock frequency
  * @param  OCTOSPIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE
  * @retval OCTOSPI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator MSIK or PLL is not ready
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

    case LL_RCC_OCTOSPI_CLKSOURCE_MSIK:     /* MSIk clock used as OCTOSPI clock */
      if (LL_RCC_MSIK_IsReady() == 1U)
      {
        octospi_frequency = __LL_RCC_CALC_MSIK_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                                    ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                                     LL_RCC_MSIK_GetRange() :
                                                     LL_RCC_MSIK_GetRangeAfterStandby()));
      }
      break;

    case LL_RCC_OCTOSPI_CLKSOURCE_PLL1:      /* PLL1 clock used as OCTOSPI source */
      if (LL_RCC_PLL1_IsReady() == 1U)
      {
        octospi_frequency = RCC_PLL1_GetFreqDomain_48M();
      }
      break;
    case LL_RCC_OCTOSPI_CLKSOURCE_PLL2:      /* PLL2 clock used as OCTOSPI source */
      if (LL_RCC_PLL2_IsReady() == 1U)
      {
        octospi_frequency = RCC_PLL2_GetFreqDomain_48M();
      }
      break;

    default:
      /* unreachable code */
      break;
  }

  return octospi_frequency;
}

/**
  * @brief  Return  SAESx clock frequency
  * @param  SAESxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAES_CLKSOURCE
  * @retval SAEx clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator SHSI is not ready
  */
uint32_t LL_RCC_GetSAESClockFreq(uint32_t SAESxSource)
{
  uint32_t rng_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_SAES_CLKSOURCE(SAESxSource));

  /* SAESCLK clock frequency */
  switch (LL_RCC_GetSAESClockSource(SAESxSource))
  {

    case LL_RCC_SAES_CLKSOURCE_SHSI:             /* SHSI clock used as SAES clock source */
      if (LL_RCC_SHSI_IsReady() == 1U)
      {
        rng_frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_SAES_CLKSOURCE_SHSI_DIV2:         /* SHSIDIV2 clock used as SAES clock source */
      if (LL_RCC_SHSI_IsReady() == 1U)
      {
        rng_frequency = (HSI_VALUE / 2U);
      }
      break;

    default:
      /* unreachable code */
      break;
  }

  return rng_frequency;
}

/**
  * @brief  Return FDCAN kernel clock frequency
  * @param  FDCANxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE
  * @retval FDCAN kernel clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator HSE or PLL is not ready
  */
uint32_t LL_RCC_GetFDCANClockFreq(uint32_t FDCANxSource)
{
  uint32_t fdcan_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_FDCAN_CLKSOURCE(FDCANxSource));

  /* FDCAN kernel clock frequency */
  switch (LL_RCC_GetFDCANClockSource(FDCANxSource))
  {
    case LL_RCC_FDCAN_CLKSOURCE_HSE:       /* HSE clock used as FDCAN kernel clock */
      if (LL_RCC_HSE_IsReady() == 1U)
      {
        fdcan_frequency = HSE_VALUE;
      }
      break;

    case LL_RCC_FDCAN_CLKSOURCE_PLL1:      /* PLL2 clock used as FDCAN kernel clock */
      if (LL_RCC_PLL1_IsReady() == 1U)
      {
        fdcan_frequency = RCC_PLL1_GetFreqDomain_48M();
      }
      break;

    case LL_RCC_FDCAN_CLKSOURCE_PLL2:     /* PLL2 clock used as FDCAN kernel clock */
      if (LL_RCC_PLL2_IsReady() == 1U)
      {
        fdcan_frequency = RCC_PLL2_GetFreqDomain_SAI();
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
    case LL_RCC_SYS_CLKSOURCE_STATUS_MSIS:   /* MSIS used as system clock source */
      frequency = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                          ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                           LL_RCC_MSIS_GetRange() :
                                           LL_RCC_MSIS_GetRangeAfterStandby()));
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_HSI:   /* HSI used as system clock  source */
      frequency = HSI_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_HSE:   /* HSE used as system clock  source */
      frequency = HSE_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_PLL1:  /* PLL1 used as system clock  source */
      frequency = RCC_PLL1_GetFreqDomain_SYS();
      break;

    default:
      frequency = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                          ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                           LL_RCC_MSIS_GetRange() :
                                           LL_RCC_MSIS_GetRangeAfterStandby()));
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
  * @brief  Return PCLK3 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK3 clock frequency (in Hz)
  */
static uint32_t RCC_GetPCLK3ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK2 clock frequency */
  return __LL_RCC_CALC_PCLK3_FREQ(HCLK_Frequency, LL_RCC_GetAPB3Prescaler());
}

/**
  * @brief  Return PLL1 clock frequency used for system domain
  * @retval PLL1 clock frequency (in Hz)
  */
static uint32_t RCC_PLL1_GetFreqDomain_SYS(void)
{
  uint32_t pllinputfreq;
  uint32_t pllsource;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLLM) * PLLN
     SYSCLK = PLL_VCO / PLLR
  */
  pllsource = LL_RCC_PLL1_GetMainSource();

  switch (pllsource)
  {
    case LL_RCC_PLL1SOURCE_MSIS:  /* MSIS used as PLL1 clock source */
      pllinputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                             ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                              LL_RCC_MSIS_GetRange() :
                                              LL_RCC_MSIS_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLL1SOURCE_HSI:  /* HSI used as PLL1 clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL1SOURCE_HSE:  /* HSE used as PLL1 clock source */
      pllinputfreq = HSE_VALUE;
      break;

    default:
      pllinputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                             ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                              LL_RCC_MSIS_GetRange() :
                                              LL_RCC_MSIS_GetRangeAfterStandby()));
      break;
  }
  return __LL_RCC_CALC_PLL1CLK_FREQ(pllinputfreq, LL_RCC_PLL1_GetDivider(),
                                    LL_RCC_PLL1_GetN(), LL_RCC_PLL1_GetR());
}
/**
  * @brief  Return PLL1 clock frequency used for SAI domain
  * @retval PLL1 clock frequency (in Hz)
  */
static uint32_t RCC_PLL1_GetFreqDomain_SAI(void)
{
  uint32_t pll1inputfreq;
  uint32_t pll1outputfreq;
  uint32_t pll1source;
  uint32_t pll1n;
  uint32_t pll1pdiv;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE / PLLM) * PLLN
     SAI Domain clock = PLL_VCO / PLL1P
  */
  pll1source = LL_RCC_PLL1_GetMainSource();

  switch (pll1source)
  {
    case LL_RCC_PLL1SOURCE_MSIS:  /* MSI used as PLL1 clock source */
      pll1inputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                              ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                               LL_RCC_MSIS_GetRange() :
                                               LL_RCC_MSIS_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLL1SOURCE_HSI:  /* HSI used as PLL1 clock source */
      pll1inputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL1SOURCE_HSE:  /* HSE used as PLL1 clock source */
      pll1inputfreq = HSE_VALUE;
      break;

    default:
      pll1inputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                              ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                               LL_RCC_MSIS_GetRange() :
                                               LL_RCC_MSIS_GetRangeAfterStandby()));
      break;
  }

  pll1n = LL_RCC_PLL1_GetN();
  pll1pdiv = LL_RCC_PLL1_GetP();
  if ((pll1n >= 8U) && (pll1pdiv >= 2U))
  {
    pll1outputfreq = __LL_RCC_CALC_PLL1CLK_SAI_FREQ(pll1inputfreq, LL_RCC_PLL1_GetDivider(),
                                                    pll1n, pll1pdiv);
  }
  else
  {
    pll1outputfreq = 0;  /* Invalid PLL1N or PLL1PDIV value */
  }
  return pll1outputfreq;
}

/**
  * @brief  Return PLL clock frequency used for 48 MHz domain
  * @retval PLL clock frequency (in Hz)
  */
static uint32_t RCC_PLL1_GetFreqDomain_48M(void)
{
  uint32_t pll1inputfreq;
  uint32_t pll1source;

  /* PLL1_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLL1M) * PLL1N
     48M Domain clock = PLL1_VCO / PLL1Q
  */
  pll1source = LL_RCC_PLL1_GetMainSource();

  switch (pll1source)
  {
    case LL_RCC_PLL1SOURCE_MSIS:  /* MSI used as PLL1 clock source */
      pll1inputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                              ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                               LL_RCC_MSIS_GetRange() :
                                               LL_RCC_MSIS_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLL1SOURCE_HSI:  /* HSI used as PLL1 clock source */
      pll1inputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL1SOURCE_HSE:  /* HSE used as PLL1 clock source */
      pll1inputfreq = HSE_VALUE;
      break;

    default:
      pll1inputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                              ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                               LL_RCC_MSIS_GetRange() :
                                               LL_RCC_MSIS_GetRangeAfterStandby()));
      break;
  }
  return __LL_RCC_CALC_PLL1CLK_48M_FREQ(pll1inputfreq, LL_RCC_PLL1_GetDivider(),
                                        LL_RCC_PLL1_GetN(), LL_RCC_PLL1_GetQ());
}

/**
  * @brief  Return PLL2 clock frequency used for SAI domain
  * @retval PLL2 clock frequency (in Hz)
  */
static uint32_t RCC_PLL2_GetFreqDomain_SAI(void)
{
  uint32_t pll2inputfreq;
  uint32_t pll2outputfreq;
  uint32_t pll2source;
  uint32_t pll2n;
  uint32_t pll2pdiv;

  /* PLL2_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLL2M) * PLL2N */
  /* SAI Domain clock  = PLL2_VCO / PLL2P */
  pll2source = LL_RCC_PLL2_GetSource();

  switch (pll2source)
  {
    case LL_RCC_PLL2SOURCE_MSIS:  /* MSI used as PLLSAI1 clock source */
      pll2inputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                              ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                               LL_RCC_MSIS_GetRange() :
                                               LL_RCC_MSIS_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLL2SOURCE_HSI:  /* HSI used as PLL2 clock source */
      pll2inputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL2SOURCE_HSE:  /* HSE used as PLL2 clock source */
      pll2inputfreq = HSE_VALUE;
      break;

    default:
      pll2inputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                              ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                               LL_RCC_MSIS_GetRange() :
                                               LL_RCC_MSIS_GetRangeAfterStandby()));
      break;
  }

  pll2n = LL_RCC_PLL2_GetN();
  pll2pdiv = LL_RCC_PLL2_GetP();
  if ((pll2n >= 8U) && (pll2pdiv >= 2U))
  {
    pll2outputfreq = __LL_RCC_CALC_PLL2CLK_SAI_FREQ(pll2inputfreq, LL_RCC_PLL2_GetDivider(),
                                                    pll2n, pll2pdiv);
  }
  else
  {
    pll2outputfreq = 0;  /* Invalid PLL2N or PLL2PDIV value */
  }
  return pll2outputfreq;
}

/**
  * @brief  Return PLL2 clock frequency used for 48Mhz domain
  * @retval PLL2 clock frequency (in Hz)
  */
static uint32_t RCC_PLL2_GetFreqDomain_48M(void)
{
  uint32_t pll2inputfreq;
  uint32_t pll2source;

  /* PLLSAI1_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLL2M) * PLL2N */
  /* 48M Domain clock  = PLL2_VCO / PLL2Q */
  pll2source = LL_RCC_PLL2_GetSource();

  switch (pll2source)
  {
    case LL_RCC_PLL2SOURCE_MSIS:  /* MSI used as PLL2 clock source */
      pll2inputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                              ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                               LL_RCC_MSIS_GetRange() :
                                               LL_RCC_MSIS_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLL2SOURCE_HSI:  /* HSI used as PLL2 clock source */
      pll2inputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL2SOURCE_HSE:  /* HSE used as PLL2 clock source */
      pll2inputfreq = HSE_VALUE;
      break;

    default:
      pll2inputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                              ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                               LL_RCC_MSIS_GetRange() :
                                               LL_RCC_MSIS_GetRangeAfterStandby()));
      break;
  }
  return __LL_RCC_CALC_PLL2CLK_48M_FREQ(pll2inputfreq, LL_RCC_PLL2_GetDivider(),
                                        LL_RCC_PLL2_GetN(), LL_RCC_PLL2_GetQ());
}

/**
  * @brief  Return PLL2 clock frequency used for ADC domain
  * @retval PLL2 clock frequency (in Hz)
  */
static uint32_t RCC_PLL2_GetFreqDomain_ADC(void)
{
  uint32_t pll2inputfreq;
  uint32_t pll2source;

  /* PLL2_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLL2M) * PLL2N */
  /* 48M Domain clock  = PLL2_VCO / PLL2R */
  pll2source = LL_RCC_PLL2_GetSource();

  switch (pll2source)
  {
    case LL_RCC_PLL2SOURCE_MSIS:  /* MSI used as PLL2 clock source */
      pll2inputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                              ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                               LL_RCC_MSIS_GetRange() :
                                               LL_RCC_MSIS_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLL2SOURCE_HSI:  /* HSI used as PLL2 clock source */
      pll2inputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL2SOURCE_HSE:  /* HSE used as PLL2 clock source */
      pll2inputfreq = HSE_VALUE;
      break;

    default:
      pll2inputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                              ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                               LL_RCC_MSIS_GetRange() :
                                               LL_RCC_MSIS_GetRangeAfterStandby()));
      break;
  }
  return __LL_RCC_CALC_PLL2CLK_ADC_FREQ(pll2inputfreq, LL_RCC_PLL2_GetDivider(),
                                        LL_RCC_PLL2_GetN(), LL_RCC_PLL2_GetR());
}

/**
  * @brief  Return PLL3 clock frequency used for SAI domain
  * @retval PLL3 clock frequency (in Hz)
  */
static uint32_t RCC_PLL3_GetFreqDomain_SAI(void)
{
  uint32_t pll3inputfreq;
  uint32_t pll3outputfreq;
  uint32_t pll3source;
  uint32_t pll3n;
  uint32_t pll3pdiv;

  /* PLL3_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLL3M) * PLL3N */
  /* SAI Domain clock  = PLL3_VCO / PLL3P */
  pll3source = LL_RCC_PLL3_GetSource();

  switch (pll3source)
  {
    case LL_RCC_PLL3SOURCE_MSIS:  /* MSI used as PLL3 clock source */
      pll3inputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                              ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                               LL_RCC_MSIS_GetRange() :
                                               LL_RCC_MSIS_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLL3SOURCE_HSI:  /* HSI used as PLL3 clock source */
      pll3inputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL3SOURCE_HSE:  /* HSE used as PLL3 clock source */
      pll3inputfreq = HSE_VALUE;
      break;

    default:
      pll3inputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                              ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                               LL_RCC_MSIS_GetRange() :
                                               LL_RCC_MSIS_GetRangeAfterStandby()));
      break;
  }

  pll3n = LL_RCC_PLL3_GetN();
  pll3pdiv = LL_RCC_PLL3_GetP();
  if ((pll3n >= 8U) && (pll3pdiv >= 2U))
  {
    pll3outputfreq = __LL_RCC_CALC_PLL3CLK_SAI_FREQ(pll3inputfreq, LL_RCC_PLL3_GetDivider(),
                                                    pll3n, pll3pdiv);
  }
  else
  {
    pll3outputfreq = 0;  /* Invalid PLL3N or PLL3PDIV value */
  }
  return pll3outputfreq;
}

/**
  * @}
  */

/**
  * @brief  Return PLL3clock frequency used for 48Mhz domain
  * @retval PLL3 clock frequency (in Hz)
  */
static uint32_t RCC_PLL3_GetFreqDomain_48M(void)
{
  uint32_t PLL3inputfreq;
  uint32_t PLL3source;

  /* PLLSAI1_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLL3M) * PLL3N */
  /* 48M Domain clock  = PLL3_VCO / PLL3Q */
  PLL3source = LL_RCC_PLL3_GetSource();

  switch (PLL3source)
  {
    case LL_RCC_PLL3SOURCE_MSIS:  /* MSI used as PLL3 clock source */
      PLL3inputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                              ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                               LL_RCC_MSIS_GetRange() :
                                               LL_RCC_MSIS_GetRangeAfterStandby()));
      break;

    case LL_RCC_PLL3SOURCE_HSI:  /* HSI used as PLL3 clock source */
      PLL3inputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL3SOURCE_HSE:  /* HSE used as PLL3 clock source */
      PLL3inputfreq = HSE_VALUE;
      break;

    default:
      PLL3inputfreq = __LL_RCC_CALC_MSIS_FREQ(LL_RCC_MSI_IsEnabledRangeSelect(),
                                              ((LL_RCC_MSI_IsEnabledRangeSelect() == 1U) ?
                                               LL_RCC_MSIS_GetRange() :
                                               LL_RCC_MSIS_GetRangeAfterStandby()));
      break;
  }
  return __LL_RCC_CALC_PLL3CLK_48M_FREQ(PLL3inputfreq, LL_RCC_PLL3_GetDivider(),
                                        LL_RCC_PLL3_GetN(), LL_RCC_PLL3_GetQ());
}

/**
  * @}
  */

#endif /* defined(RCC) */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */
