/**
  ******************************************************************************
  * @file    stm32h5xx_ll_rcc.c
  * @author  MCD Application Team
  * @brief   RCC LL module driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32h5xx_ll_rcc.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */
/** @addtogroup STM32H5xx_LL_Driver
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
#if defined(USART6)
#define IS_LL_RCC_USART_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_USART1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_USART2_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_USART3_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_USART6_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_USART10_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_USART11_CLKSOURCE))
#else
#define IS_LL_RCC_USART_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_USART1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_USART2_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_USART3_CLKSOURCE))
#endif /* USART6 */

#if defined(UART4)
#define IS_LL_RCC_UART_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_UART4_CLKSOURCE) \
                                                || ((__VALUE__) == LL_RCC_UART5_CLKSOURCE) \
                                                || ((__VALUE__) == LL_RCC_UART7_CLKSOURCE) \
                                                || ((__VALUE__) == LL_RCC_UART8_CLKSOURCE) \
                                                || ((__VALUE__) == LL_RCC_UART9_CLKSOURCE) \
                                                || ((__VALUE__) == LL_RCC_UART12_CLKSOURCE))
#endif /* UART4 */

#define IS_LL_RCC_LPUART_CLKSOURCE(__VALUE__) (((__VALUE__) == LL_RCC_LPUART1_CLKSOURCE))

#if defined(I2C3)
#define IS_LL_RCC_I2C_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_I2C1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_I2C2_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_I2C3_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_I2C4_CLKSOURCE))
#else
#define IS_LL_RCC_I2C_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_I2C1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_I2C2_CLKSOURCE))
#endif /* I2C3*/

#if defined(I3C2)
#define IS_LL_RCC_I3C_CLKSOURCE(__VALUE__) (((__VALUE__) == LL_RCC_I3C1_CLKSOURCE) \
                                            || ((__VALUE__) == LL_RCC_I3C2_CLKSOURCE))
#else
#define IS_LL_RCC_I3C_CLKSOURCE(__VALUE__) (((__VALUE__) == LL_RCC_I3C1_CLKSOURCE))
#endif /* I3C2 */

#if defined(SPI4)
#define IS_LL_RCC_SPI_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_SPI1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_SPI2_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_SPI3_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_SPI4_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_SPI5_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_SPI6_CLKSOURCE))
#else
#define IS_LL_RCC_SPI_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_SPI1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_SPI2_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_SPI3_CLKSOURCE))
#endif /* SPI4 */

#if defined(LPTIM3)
#define IS_LL_RCC_LPTIM_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_LPTIM1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPTIM2_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPTIM3_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPTIM4_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPTIM5_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPTIM6_CLKSOURCE))
#else
#define IS_LL_RCC_LPTIM_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_LPTIM1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPTIM2_CLKSOURCE))
#endif /* LPTIM3 */

#if defined(SAI1)
#define IS_LL_RCC_SAI_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_SAI1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_SAI2_CLKSOURCE))
#endif /* SAI1 */

#if defined (SDMMC2)
#define IS_LL_RCC_SDMMC_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_SDMMC1_CLKSOURCE) \
                                                 || ((__VALUE__) == LL_RCC_SDMMC2_CLKSOURCE))
#elif defined (SDMMC1)
#define IS_LL_RCC_SDMMC_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_SDMMC1_CLKSOURCE))
#endif /* SDMMC2*/

#define IS_LL_RCC_RNG_CLKSOURCE(__VALUE__)      (((__VALUE__) == LL_RCC_RNG_CLKSOURCE))

#define IS_LL_RCC_USB_CLKSOURCE(__VALUE__)      (((__VALUE__) == LL_RCC_USB_CLKSOURCE))

#define IS_LL_RCC_ADCDAC_CLKSOURCE(__VALUE__)   (((__VALUE__) == LL_RCC_ADCDAC_CLKSOURCE))

#define IS_LL_RCC_DAC_LP_CLKSOURCE(__VALUE__)   (((__VALUE__) == LL_RCC_DAC_LP_CLKSOURCE))

#define IS_LL_RCC_OCTOSPI_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_OCTOSPI_CLKSOURCE))

#define IS_LL_RCC_FDCAN_CLKSOURCE(__VALUE__)    ((__VALUE__) == LL_RCC_FDCAN_CLKSOURCE)

#if defined(CEC)
#define IS_LL_RCC_CEC_CLKSOURCE(__VALUE__)      (((__VALUE__) == LL_RCC_CEC_CLKSOURCE))
#endif /* CEC */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_LL_Private_Functions RCC Private functions
  * @{
  */
uint32_t RCC_GetSystemClockFreq(void);
uint32_t RCC_GetHCLKClockFreq(uint32_t SYSCLK_Frequency);
uint32_t RCC_GetPCLK1ClockFreq(uint32_t HCLK_Frequency);
uint32_t RCC_GetPCLK2ClockFreq(uint32_t HCLK_Frequency);
uint32_t RCC_GetPCLK3ClockFreq(uint32_t HCLK_Frequency);
uint32_t RCC_PLL1_GetFreqSystem(void);
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
  *         - HSI ON and used as system clock source
  *         - HSE, CSI, PLL1, PLL2 and PLL3 OFF
  *         - AHB, APB1, APB2 and APB3 prescaler set to 1.
  *         - CSS OFF
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

  /* Set HSION bit */
  LL_RCC_HSI_Enable();

  /* Wait for HSI READY bit */
  while (LL_RCC_HSI_IsReady() == 0U)
  {
  }

  /* Set HSIDIV Default value */
  CLEAR_BIT(RCC->CR, RCC_CR_HSIDIV);

  /* Set HSITRIM bits to the reset value*/
  LL_RCC_HSI_SetCalibTrimming(0x40U);

  /* Reset CFGR register */
  LL_RCC_WriteReg(CFGR1, 0x00000000U);
  LL_RCC_WriteReg(CFGR2, 0x00000000U);

  /* Wait till clock switch is ready */
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  }

#if defined(RCC_CR_PLL3ON)
  /* Reset HSECSSON, HSEON, HSIKERON, CSION, CSIKERON, HSI48ON, PLL1ON, PLL2ON and  PLL3ON bits */
  CLEAR_BIT(RCC->CR, RCC_CR_CSION | RCC_CR_CSIKERON | RCC_CR_HSECSSON | RCC_CR_HSIKERON | RCC_CR_HSI48ON |
            RCC_CR_HSEON | RCC_CR_PLL1ON | RCC_CR_PLL2ON | RCC_CR_PLL3ON);
#else
  /* Reset HSECSSON, HSEON, HSIKERON, CSION, CSIKERON, HSI48ON, PLL1ON, PLL2ON and  PLL3ON bits */
  CLEAR_BIT(RCC->CR, RCC_CR_CSION | RCC_CR_CSIKERON | RCC_CR_HSECSSON | RCC_CR_HSIKERON | RCC_CR_HSI48ON |
            RCC_CR_HSEON | RCC_CR_PLL1ON | RCC_CR_PLL2ON);
#endif /* PLL3 */

  /* Wait for PLL1 READY bit to be reset */
  while (LL_RCC_PLL1_IsReady() != 0U)
  {}

  /* Wait for PLL2 READY bit to be reset */
  while (LL_RCC_PLL2_IsReady() != 0U)
  {}

#if defined(RCC_CR_PLL3ON)
  /* Wait for PLL3 READY bit to be reset */
  while (LL_RCC_PLL3_IsReady() != 0U)
  {}
#endif /* PLL3 */

  /* Reset PLL1CFGR register */
  CLEAR_REG(RCC->PLL1CFGR);

  /* Reset PLL1DIVR register */
  LL_RCC_WriteReg(PLL1DIVR, 0x01010280U);

  /* Reset PLL1FRACR register */
  CLEAR_REG(RCC->PLL1FRACR);

  /* Reset PLL2CFGR register */
  CLEAR_REG(RCC->PLL2CFGR);

  /* Reset PLL2DIVR register */
  LL_RCC_WriteReg(PLL2DIVR, 0x01010280U);

  /* Reset PLL2FRACR register */
  CLEAR_REG(RCC->PLL2FRACR);

#if defined(RCC_CR_PLL3ON)
  /* Reset PLL3CFGR register */
  CLEAR_REG(RCC->PLL3CFGR);

  /* Reset PLL3DIVR register */
  LL_RCC_WriteReg(PLL3DIVR, 0x01010280U);

  /* Reset PLL3FRACR register */
  CLEAR_REG(RCC->PLL3FRACR);
#endif /* PLL3 */

  /* Reset HSEBYP bit */
  CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);

  /* Reset HSEEXT bit */
  CLEAR_BIT(RCC->CR, RCC_CR_HSEEXT);

#if defined(RCC_CR_PLL3ON)
  /* Disable all interrupts */
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSIRDYIE | RCC_CIER_LSERDYIE | RCC_CIER_HSIRDYIE | RCC_CIER_HSERDYIE
            | RCC_CIER_CSIRDYIE | RCC_CIER_HSI48RDYIE | RCC_CIER_PLL1RDYIE | RCC_CIER_PLL2RDYIE
            | RCC_CIER_PLL3RDYIE);

  /* Clear all interrupt flags */
  SET_BIT(RCC->CICR, RCC_CICR_LSIRDYC | RCC_CICR_LSERDYC | RCC_CICR_HSIRDYC | RCC_CICR_HSERDYC
          | RCC_CICR_CSIRDYC | RCC_CICR_HSI48RDYC | RCC_CICR_PLL1RDYC | RCC_CICR_PLL2RDYC
          | RCC_CICR_PLL3RDYC | RCC_CICR_HSECSSC);
#else
  /* Disable all interrupts */
  CLEAR_BIT(RCC->CIER, RCC_CIER_LSIRDYIE | RCC_CIER_LSERDYIE | RCC_CIER_HSIRDYIE | RCC_CIER_HSERDYIE
            | RCC_CIER_CSIRDYIE | RCC_CIER_HSI48RDYIE | RCC_CIER_PLL1RDYIE | RCC_CIER_PLL2RDYIE);

  /* Clear all interrupt flags */
  SET_BIT(RCC->CICR, RCC_CICR_LSIRDYC | RCC_CICR_LSERDYC | RCC_CICR_HSIRDYC | RCC_CICR_HSERDYC
          | RCC_CICR_CSIRDYC | RCC_CICR_HSI48RDYC | RCC_CICR_PLL1RDYC | RCC_CICR_PLL2RDYC
          | RCC_CICR_HSECSSC);
#endif /* PLL3 */


  /* Clear all reset flags */
  LL_RCC_ClearResetFlags();

  /* Update the SystemCoreClock global variable */
  SystemCoreClock = HSI_VALUE;

  return SUCCESS;
}

/**
  * @}
  */

/** @addtogroup RCC_LL_EF_Get_Freq
  * @brief  Return the frequencies of different on chip clocks;  System, AHB, APB1 and APB2 buses clocks
  *         and different peripheral clocks available on the device.
  * @note   If SYSCLK source is HSI, function returns values based on HSI_VALUE(*)
  * @note   If SYSCLK source is CSI, function returns values based on CSI_VALUE(**)
  * @note   If SYSCLK source is HSE, function returns values based on HSE_VALUE(***)
  * @note   If SYSCLK source is PLL1, function returns values based on HSE_VALUE(***)
  *         or HSI_VALUE(**) or CSI_VALUE(*) multiplied/divided by the main PLL factors.
  * @note   (*) HSI_VALUE is a constant defined in this file (default value
  *             64 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.
  * @note   (**) CSI_VALUE is a constant defined in this file (default value
  *              4 MHz) but the real value may vary depending on the variations
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
  * @brief  Return the frequencies of different on chip clocks;  System, AHB, APB1, APB2 and APB3 buses clocks
  * @note   Each time SYSCLK, HCLK, PCLK1, PCLK2 and PCLK3 clock changes, this function
  *         must be called to update structure fields. Otherwise, any
  *         configuration based on this function will be incorrect.
  * @param  pRCC_Clocks pointer to a @ref LL_RCC_ClocksTypeDef structure which will hold the clocks frequencies
  * @retval None
  */
void LL_RCC_GetSystemClocksFreq(LL_RCC_ClocksTypeDef *pRCC_Clocks)
{
  /* Get SYSCLK frequency */
  pRCC_Clocks->SYSCLK_Frequency = RCC_GetSystemClockFreq();

  /* HCLK clock frequency */
  pRCC_Clocks->HCLK_Frequency   = RCC_GetHCLKClockFreq(pRCC_Clocks->SYSCLK_Frequency);

  /* PCLK1 clock frequency */
  pRCC_Clocks->PCLK1_Frequency  = RCC_GetPCLK1ClockFreq(pRCC_Clocks->HCLK_Frequency);

  /* PCLK2 clock frequency */
  pRCC_Clocks->PCLK2_Frequency  = RCC_GetPCLK2ClockFreq(pRCC_Clocks->HCLK_Frequency);

  /* PCLK3 clock frequency */
  pRCC_Clocks->PCLK3_Frequency  = RCC_GetPCLK3ClockFreq(pRCC_Clocks->HCLK_Frequency);
}

/**
  * @brief  Return PLL1 clocks frequencies
  * @note   LL_RCC_PERIPH_FREQUENCY_NO returned for non activated output or oscillator not ready
  * @retval None
  */
void LL_RCC_GetPLL1ClockFreq(LL_PLL_ClocksTypeDef *pPLL_Clocks)
{
  uint32_t pllinputfreq = LL_RCC_PERIPH_FREQUENCY_NO;
  uint32_t pllsource;
  uint32_t pllm;
  uint32_t plln;
  uint32_t fracn = 0U;

  /* PLL_VCO = (HSE_VALUE, CSI_VALUE or HSI_VALUE/HSIDIV) / PLLM * (PLLN + FRACN)
     SYSCLK = PLL_VCO / PLLP
  */
  pllsource = LL_RCC_PLL1_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLL1SOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        pllinputfreq = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
      }
      break;

    case LL_RCC_PLL1SOURCE_CSI:
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        pllinputfreq = CSI_VALUE;
      }
      break;

    case LL_RCC_PLL1SOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        pllinputfreq = HSE_VALUE;
      }
      break;

    case LL_RCC_PLL1SOURCE_NONE:
    default:
      /* PLL clock disabled */
      break;
  }

  pPLL_Clocks->PLL_P_Frequency = 0U;
  pPLL_Clocks->PLL_Q_Frequency = 0U;
  pPLL_Clocks->PLL_R_Frequency = 0U;

  pllm = LL_RCC_PLL1_GetM();
  plln = LL_RCC_PLL1_GetN();
  if (LL_RCC_PLL1FRACN_IsEnabled() != 0U)
  {
    fracn = LL_RCC_PLL1_GetFRACN();
  }

  if (pllm != 0U)
  {
    if (LL_RCC_PLL1P_IsEnabled() != 0U)
    {
      pPLL_Clocks->PLL_P_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, pllm, plln, fracn, LL_RCC_PLL1_GetP());
    }

    if (LL_RCC_PLL1Q_IsEnabled() != 0U)
    {
      pPLL_Clocks->PLL_Q_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, pllm, plln, fracn, LL_RCC_PLL1_GetQ());
    }

    if (LL_RCC_PLL1R_IsEnabled() != 0U)
    {
      pPLL_Clocks->PLL_R_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, pllm, plln, fracn, LL_RCC_PLL1_GetR());
    }
  }
}

/**
  * @brief  Return PLL2 clocks frequencies
  * @note   LL_RCC_PERIPH_FREQUENCY_NO returned for non activated output or oscillator not ready
  * @retval None
  */
void LL_RCC_GetPLL2ClockFreq(LL_PLL_ClocksTypeDef *pPLL_Clocks)
{
  uint32_t pllinputfreq = LL_RCC_PERIPH_FREQUENCY_NO;
  uint32_t pllsource;
  uint32_t pllm;
  uint32_t plln;
  uint32_t fracn = 0U;

  /* PLL_VCO = (HSE_VALUE, CSI_VALUE or HSI_VALUE/HSIDIV) / PLLM * (PLLN + FRACN)
     SYSCLK = PLL_VCO / PLLP
  */
  pllsource = LL_RCC_PLL2_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLL2SOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        pllinputfreq = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
      }
      break;

    case LL_RCC_PLL2SOURCE_CSI:
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        pllinputfreq = CSI_VALUE;
      }
      break;

    case LL_RCC_PLL2SOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        pllinputfreq = HSE_VALUE;
      }
      break;

    case LL_RCC_PLL2SOURCE_NONE:
    default:
      /* PLL clock disabled */
      break;
  }

  pPLL_Clocks->PLL_P_Frequency = 0U;
  pPLL_Clocks->PLL_Q_Frequency = 0U;
  pPLL_Clocks->PLL_R_Frequency = 0U;

  pllm = LL_RCC_PLL2_GetM();
  plln = LL_RCC_PLL2_GetN();
  if (LL_RCC_PLL2FRACN_IsEnabled() != 0U)
  {
    fracn = LL_RCC_PLL2_GetFRACN();
  }

  if (pllm != 0U)
  {
    if (LL_RCC_PLL2P_IsEnabled() != 0U)
    {
      pPLL_Clocks->PLL_P_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, pllm, plln, fracn, LL_RCC_PLL2_GetP());
    }

    if (LL_RCC_PLL2Q_IsEnabled() != 0U)
    {
      pPLL_Clocks->PLL_Q_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, pllm, plln, fracn, LL_RCC_PLL2_GetQ());
    }

    if (LL_RCC_PLL2R_IsEnabled() != 0U)
    {
      pPLL_Clocks->PLL_R_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, pllm, plln, fracn, LL_RCC_PLL2_GetR());
    }
  }
}

#if defined(RCC_CR_PLL3ON)
/**
  * @brief  Return PLL3 clocks frequencies
  * @note   LL_RCC_PERIPH_FREQUENCY_NO returned for non activated output or oscillator not ready
  * @retval None
  */
void LL_RCC_GetPLL3ClockFreq(LL_PLL_ClocksTypeDef *pPLL_Clocks)
{
  uint32_t pllinputfreq = LL_RCC_PERIPH_FREQUENCY_NO;
  uint32_t pllsource;
  uint32_t pllm;
  uint32_t plln;
  uint32_t fracn = 0U;

  /* PLL_VCO = (HSE_VALUE, CSI_VALUE or HSI_VALUE/HSIDIV) / PLLM * (PLLN + FRACN)
     SYSCLK = PLL_VCO / PLLP
  */
  pllsource = LL_RCC_PLL3_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLL3SOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        pllinputfreq = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
      }
      break;

    case LL_RCC_PLL3SOURCE_CSI:
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        pllinputfreq = CSI_VALUE;
      }
      break;

    case LL_RCC_PLL3SOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        pllinputfreq = HSE_VALUE;
      }
      break;

    case LL_RCC_PLL3SOURCE_NONE:
    default:
      /* PLL clock disabled */
      break;
  }

  pPLL_Clocks->PLL_P_Frequency = 0U;
  pPLL_Clocks->PLL_Q_Frequency = 0U;
  pPLL_Clocks->PLL_R_Frequency = 0U;

  pllm = LL_RCC_PLL3_GetM();
  plln = LL_RCC_PLL3_GetN();
  if (LL_RCC_PLL3FRACN_IsEnabled() != 0U)
  {
    fracn = LL_RCC_PLL3_GetFRACN();
  }

  if ((pllm != 0U) && (pllinputfreq != 0U))
  {
    if (LL_RCC_PLL3P_IsEnabled() != 0U)
    {
      pPLL_Clocks->PLL_P_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, pllm, plln, fracn, LL_RCC_PLL3_GetP());
    }

    if (LL_RCC_PLL3Q_IsEnabled() != 0U)
    {
      pPLL_Clocks->PLL_Q_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, pllm, plln, fracn, LL_RCC_PLL3_GetQ());
    }

    if (LL_RCC_PLL3R_IsEnabled() != 0U)
    {
      pPLL_Clocks->PLL_R_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, pllm, plln, fracn, LL_RCC_PLL3_GetR());
    }
  }
}
#endif /* PLL3 */

/**
  * @brief  Helper function to calculate the PLL1 frequency output
  * @note ex: @ref LL_RCC_CalcPLLClockFreq (HSE_VALUE, @ref LL_RCC_PLL1_GetM (),
  *           @ref LL_RCC_PLL1_GetN (), @ref LL_RCC_PLL1_GetFRACN (), @ref LL_RCC_PLL1_GetP ());
  * @param  PLLInputFreq PLL Input frequency (based on HSE/(HSI/HSIDIV)/CSI)
  * @param  M      Between 1 and 63
  * @param  N      Between 4 and 512
  * @param  FRACN  Between 0 and 0x1FFF
  * @param  PQR    VCO output divider (P, Q or R)
  *                Between 1 and 128, except for PLL1P Odd value not allowed
  * @retval PLL1 output clock frequency (in Hz)
  */
uint32_t LL_RCC_CalcPLLClockFreq(uint32_t PLLInputFreq, uint32_t M, uint32_t N, uint32_t FRACN, uint32_t PQR)
{
  float_t freq;

  freq = ((float_t)PLLInputFreq / (float_t)M) * ((float_t)N + ((float_t)FRACN / (float_t)0x2000));

  freq = freq / (float_t)PQR;

  return (uint32_t)freq;
}


/**
  * @brief  Return USARTx clock frequency
  * @param  USARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART2_CLKSOURCE
  *         @arg @ref LL_RCC_USART3_CLKSOURCE
  *         @arg @ref LL_RCC_USART6_CLKSOURCE (*)
  *         @arg @ref LL_RCC_USART10_CLKSOURCE (*)
  *         @arg @ref LL_RCC_USART11_CLKSOURCE (*)
  *
  *  (*)  : For stm32h56xxx and stm32h57xxx family lines only.
  * @retval USART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready
  */
uint32_t LL_RCC_GetUSARTClockFreq(uint32_t USARTxSource)
{
  uint32_t usart_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_USART_CLKSOURCE(USARTxSource));

  if (USARTxSource == LL_RCC_USART1_CLKSOURCE)
  {
    /* USART1CLK clock frequency */
    switch (LL_RCC_GetUSARTClockSource(USARTxSource))
    {
      case LL_RCC_USART1_CLKSOURCE_PCLK2:  /* USART1 Clock is PCLK2 */
        usart_frequency = RCC_GetPCLK2ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_USART1_CLKSOURCE_PLL2Q: /* USART1 Clock is PLL2 Q */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            usart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

#if defined(LL_RCC_USART1_CLKSOURCE_PLL3Q)
      case LL_RCC_USART1_CLKSOURCE_PLL3Q: /* USART1 Clock is PLL3 Q */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            usart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;
#endif /* LL_RCC_USART1_CLKSOURCE_PLL3 */

      case LL_RCC_USART1_CLKSOURCE_HSI:    /* USART1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          usart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_USART1_CLKSOURCE_CSI:    /* USART1 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          usart_frequency = CSI_VALUE;
        }
        break;

      case LL_RCC_USART1_CLKSOURCE_LSE:    /* USART1 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          usart_frequency = LSE_VALUE;
        }
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
      case LL_RCC_USART2_CLKSOURCE_PCLK1:  /* USART2 Clock is PCLK1 */
        usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_USART2_CLKSOURCE_PLL2Q: /* USART2 Clock is PLL2 Q */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            usart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

#if defined(LL_RCC_USART2_CLKSOURCE_PLL3Q)
      case LL_RCC_USART2_CLKSOURCE_PLL3Q: /* USART2 Clock is PLL3 Q */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            usart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;
#endif /* LL_RCC_USART2_CLKSOURCE_PLL3 */

      case LL_RCC_USART2_CLKSOURCE_HSI:    /* USART2 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          usart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_USART2_CLKSOURCE_CSI:    /* USART2 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          usart_frequency = CSI_VALUE;
        }
        break;

      case LL_RCC_USART2_CLKSOURCE_LSE:    /* USART2 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          usart_frequency = LSE_VALUE;
        }
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
      case LL_RCC_USART3_CLKSOURCE_PCLK1:  /* USART3 Clock is PCLK1 */
        usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_USART3_CLKSOURCE_PLL2Q: /* USART3 Clock is PLL2 Q */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            usart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

#if defined(LL_RCC_USART3_CLKSOURCE_PLL3Q)
      case LL_RCC_USART3_CLKSOURCE_PLL3Q: /* USART3 Clock is PLL3 Q */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            usart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;
#endif /* LL_RCC_USART3_CLKSOURCE_PLL3 */

      case LL_RCC_USART3_CLKSOURCE_HSI:    /* USART3 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          usart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_USART3_CLKSOURCE_CSI:    /* USART3 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          usart_frequency = CSI_VALUE;
        }
        break;

      case LL_RCC_USART3_CLKSOURCE_LSE:    /* USART3 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          usart_frequency = LSE_VALUE;
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }

#if defined(USART6)
  else if (USARTxSource == LL_RCC_USART6_CLKSOURCE)
  {
    /* USART6CLK clock frequency */
    switch (LL_RCC_GetUSARTClockSource(USARTxSource))
    {
      case LL_RCC_USART6_CLKSOURCE_PCLK1:  /* USART6 Clock is PCLK1 */
        usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_USART6_CLKSOURCE_PLL2Q: /* USART6 Clock is PLL2 Q */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            usart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_USART6_CLKSOURCE_PLL3Q: /* USART6 Clock is PLL3 Q */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            usart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_USART6_CLKSOURCE_HSI:    /* USART6 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          usart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_USART6_CLKSOURCE_CSI:    /* USART6 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          usart_frequency = CSI_VALUE;
        }
        break;

      case LL_RCC_USART6_CLKSOURCE_LSE:    /* USART6 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          usart_frequency = LSE_VALUE;
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* USART6 */

#if defined(USART10)
  else if (USARTxSource == LL_RCC_USART10_CLKSOURCE)
  {
    /* USART10CLK clock frequency */
    switch (LL_RCC_GetUSARTClockSource(USARTxSource))
    {
      case LL_RCC_USART10_CLKSOURCE_PCLK1:  /* USART10 Clock is PCLK1 */
        usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_USART10_CLKSOURCE_PLL2Q: /* USART10 Clock is PLL2 Q */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            usart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_USART10_CLKSOURCE_PLL3Q: /* USART10 Clock is PLL3 Q */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            usart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_USART10_CLKSOURCE_HSI:    /* USART10 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          usart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_USART10_CLKSOURCE_CSI:    /* USART10 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          usart_frequency = CSI_VALUE;
        }
        break;

      case LL_RCC_USART10_CLKSOURCE_LSE:    /* USART10 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          usart_frequency = LSE_VALUE;
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* USART10 */

#if defined(USART11)
  else if (USARTxSource == LL_RCC_USART11_CLKSOURCE)
  {
    /* USART11CLK clock frequency */
    switch (LL_RCC_GetUSARTClockSource(USARTxSource))
    {
      case LL_RCC_USART11_CLKSOURCE_PCLK1:  /* USART11 Clock is PCLK1 */
        usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_USART11_CLKSOURCE_PLL2Q: /* USART11 Clock is PLL2 Q */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            usart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_USART11_CLKSOURCE_PLL3Q: /* USART11 Clock is PLL3 Q */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            usart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_USART11_CLKSOURCE_HSI:    /* USART11 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          usart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_USART11_CLKSOURCE_CSI:    /* USART11 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          usart_frequency = CSI_VALUE;
        }
        break;

      case LL_RCC_USART11_CLKSOURCE_LSE:    /* USART11 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          usart_frequency = LSE_VALUE;
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* USART11 */
  else
  {
    /* nothing to do */
  }

  return usart_frequency;
}

#if defined(UART4)
/**
  * @brief  Return UARTx clock frequency
  * @param  UARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_UART4_CLKSOURCE
  *         @arg @ref LL_RCC_UART5_CLKSOURCE
  *         @arg @ref LL_RCC_UART7_CLKSOURCE
  *         @arg @ref LL_RCC_UART8_CLKSOURCE
  *         @arg @ref LL_RCC_UART9_CLKSOURCE
  *         @arg @ref LL_RCC_UART12_CLKSOURCE
  * @retval UART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready
  */
uint32_t LL_RCC_GetUARTClockFreq(uint32_t UARTxSource)
{
  uint32_t uart_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_UART_CLKSOURCE(UARTxSource));

  if (UARTxSource == LL_RCC_UART4_CLKSOURCE)
  {
    /* UART4CLK clock frequency */
    switch (LL_RCC_GetUARTClockSource(UARTxSource))
    {
      case LL_RCC_UART4_CLKSOURCE_PCLK1:  /* UART4 Clock is PCLK1 */
        uart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_UART4_CLKSOURCE_PLL2Q: /* UART4 Clock is PLL2 Q */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            uart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_UART4_CLKSOURCE_PLL3Q: /* UART4 Clock is PLL3 Q */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            uart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_UART4_CLKSOURCE_HSI:     /* UART4 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          uart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_UART4_CLKSOURCE_CSI:     /* UART4 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          uart_frequency = CSI_VALUE;
        }
        break;

      case LL_RCC_UART4_CLKSOURCE_LSE:     /* UART4 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          uart_frequency = LSE_VALUE;
        }
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
      case LL_RCC_UART5_CLKSOURCE_PCLK1:  /* UART5 Clock is PCLK1 */
        uart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_UART5_CLKSOURCE_PLL2Q: /* UART5 Clock is PLL2 Q */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            uart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_UART5_CLKSOURCE_PLL3Q: /* UART5 Clock is PLL3 Q */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            uart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_UART5_CLKSOURCE_HSI:     /* UART5 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          uart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_UART5_CLKSOURCE_CSI:     /* UART5 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          uart_frequency = CSI_VALUE;
        }
        break;

      case LL_RCC_UART5_CLKSOURCE_LSE:     /* UART5 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          uart_frequency = LSE_VALUE;
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else if (UARTxSource == LL_RCC_UART7_CLKSOURCE)
  {
    /* UART7CLK clock frequency */
    switch (LL_RCC_GetUARTClockSource(UARTxSource))
    {
      case LL_RCC_UART7_CLKSOURCE_PCLK1:  /* UART7 Clock is PCLK1 */
        uart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_UART7_CLKSOURCE_PLL2Q: /* UART7 Clock is PLL2 Q */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            uart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_UART7_CLKSOURCE_PLL3Q: /* UART7 Clock is PLL3 Q */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            uart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_UART7_CLKSOURCE_HSI:     /* UART7 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          uart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_UART7_CLKSOURCE_CSI:     /* UART7 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          uart_frequency = CSI_VALUE;
        }
        break;

      case LL_RCC_UART7_CLKSOURCE_LSE:     /* UART7 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          uart_frequency = LSE_VALUE;
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else if (UARTxSource == LL_RCC_UART8_CLKSOURCE)
  {
    /* UART8CLK clock frequency */
    switch (LL_RCC_GetUARTClockSource(UARTxSource))
    {
      case LL_RCC_UART8_CLKSOURCE_PCLK1:  /* UART8 Clock is PCLK1 */
        uart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_UART8_CLKSOURCE_PLL2Q: /* UART8 Clock is PLL2 Q */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            uart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_UART8_CLKSOURCE_PLL3Q: /* UART8 Clock is PLL3 Q */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            uart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_UART8_CLKSOURCE_HSI:     /* UART8 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          uart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_UART8_CLKSOURCE_CSI:     /* UART8 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          uart_frequency = CSI_VALUE;
        }
        break;

      case LL_RCC_UART8_CLKSOURCE_LSE:     /* UART8 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          uart_frequency = LSE_VALUE;
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else if (UARTxSource == LL_RCC_UART9_CLKSOURCE)
  {
    /* UART9CLK clock frequency */
    switch (LL_RCC_GetUARTClockSource(UARTxSource))
    {
      case LL_RCC_UART9_CLKSOURCE_PCLK1:  /* UART9 Clock is PCLK1 */
        uart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_UART9_CLKSOURCE_PLL2Q: /* UART9 Clock is PLL2 Q */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            uart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_UART9_CLKSOURCE_PLL3Q: /* UART9 Clock is PLL3 Q */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            uart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_UART9_CLKSOURCE_HSI:     /* UART9 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          uart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_UART9_CLKSOURCE_CSI:     /* UART9 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          uart_frequency = CSI_VALUE;
        }
        break;

      case LL_RCC_UART9_CLKSOURCE_LSE:     /* UART9 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          uart_frequency = LSE_VALUE;
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
  else if (UARTxSource == LL_RCC_UART12_CLKSOURCE)
  {
    /* UART12CLK clock frequency */
    switch (LL_RCC_GetUARTClockSource(UARTxSource))
    {
      case LL_RCC_UART12_CLKSOURCE_PCLK1:  /* UART12 Clock is PCLK1 */
        uart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_UART12_CLKSOURCE_PLL2Q: /* UART12 Clock is PLL2 Q */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            uart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_UART12_CLKSOURCE_PLL3Q: /* UART12 Clock is PLL3 Q */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            uart_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_UART12_CLKSOURCE_HSI:     /* UART12 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          uart_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_UART12_CLKSOURCE_CSI:     /* UART12 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          uart_frequency = CSI_VALUE;
        }
        break;

      case LL_RCC_UART12_CLKSOURCE_LSE:     /* UART12 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          uart_frequency = LSE_VALUE;
        }
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
#endif /* UART4 */

/**
  * @brief  Return SPIx clock frequency
  * @param  SPIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI2_CLKSOURCE
  *         @arg @ref LL_RCC_SPI3_CLKSOURCE
  *         @arg @ref LL_RCC_SPI4_CLKSOURCE (*)
  *         @arg @ref LL_RCC_SPI5_CLKSOURCE (*)
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE (*)
  *
  *  (*)  : For stm32h56xxx and stm32h57xxx family lines only.
  * @retval SPI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready
  */
uint32_t LL_RCC_GetSPIClockFreq(uint32_t SPIxSource)
{
  uint32_t spi_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_SPI_CLKSOURCE(SPIxSource));

  if (SPIxSource == LL_RCC_SPI1_CLKSOURCE)
  {
    /* SPI1 CLK clock frequency */
    switch (LL_RCC_GetSPIClockSource(SPIxSource))
    {
      case LL_RCC_SPI1_CLKSOURCE_PLL1Q: /* SPI1 Clock is PLL1 Q */
        if (LL_RCC_PLL1_IsReady() != 0U)
        {
          if (LL_RCC_PLL1Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
            spi_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_SPI1_CLKSOURCE_PLL2P: /* SPI1 Clock is PLL2 P */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            spi_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;

#if defined(LL_RCC_SPI1_CLKSOURCE_PLL3P)
      case LL_RCC_SPI1_CLKSOURCE_PLL3P: /* SPI1 Clock is PLL3 P */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            spi_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;
#endif /* PLL3 */

      case LL_RCC_SPI1_CLKSOURCE_PIN:  /* SPI1 Clock is External Clock */
        spi_frequency = EXTERNAL_CLOCK_VALUE;
        break;

      case LL_RCC_SPI1_CLKSOURCE_CLKP:  /* SPI1 Clock is CLKP */
        spi_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_GetCLKPClockSource(LL_RCC_CLKP_CLKSOURCE));
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
      case LL_RCC_SPI2_CLKSOURCE_PLL1Q: /* SPI2 Clock is PLL1 Q */
        if (LL_RCC_PLL1_IsReady() != 0U)
        {
          if (LL_RCC_PLL1Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
            spi_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_SPI2_CLKSOURCE_PLL2P: /* SPI2 Clock is PLL2 P */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            spi_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;

#if defined(LL_RCC_SPI2_CLKSOURCE_PLL3P)
      case LL_RCC_SPI2_CLKSOURCE_PLL3P: /* SPI2 Clock is PLL3 P */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            spi_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;
#endif /* PLL3 */

      case LL_RCC_SPI2_CLKSOURCE_PIN:  /* SPI2 Clock is External Clock */
        spi_frequency = EXTERNAL_CLOCK_VALUE;
        break;

      case LL_RCC_SPI2_CLKSOURCE_CLKP:  /* SPI2 Clock is CLKP */
        spi_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_GetCLKPClockSource(LL_RCC_CLKP_CLKSOURCE));
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
      case LL_RCC_SPI3_CLKSOURCE_PLL1Q: /* SPI3 Clock is PLL1 Q */
        if (LL_RCC_PLL1_IsReady() != 0U)
        {
          if (LL_RCC_PLL1Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
            spi_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_SPI3_CLKSOURCE_PLL2P: /* SPI3 Clock is PLL2 P*/
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            spi_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;

#if defined(LL_RCC_SPI3_CLKSOURCE_PLL3P)
      case LL_RCC_SPI3_CLKSOURCE_PLL3P: /* SPI3 Clock is PLL3 P*/
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            spi_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;
#endif /* PLL3 */
      case LL_RCC_SPI3_CLKSOURCE_PIN:  /* SPI3 Clock is External Clock */
        spi_frequency = EXTERNAL_CLOCK_VALUE;
        break;

      case LL_RCC_SPI3_CLKSOURCE_CLKP:  /* SPI3 Clock is CLKP */
        spi_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_GetCLKPClockSource(LL_RCC_CLKP_CLKSOURCE));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#if defined(SPI4)
  else if (SPIxSource == LL_RCC_SPI4_CLKSOURCE)
  {
    /* SPI4 CLK clock frequency */
    switch (LL_RCC_GetSPIClockSource(SPIxSource))
    {
      case LL_RCC_SPI4_CLKSOURCE_PCLK2: /* SPI4 Clock is PCLK2 */
        spi_frequency = RCC_GetPCLK2ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_SPI4_CLKSOURCE_PLL2Q: /* SPI4 Clock is PLL2 Q*/
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            spi_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_SPI4_CLKSOURCE_PLL3Q: /* SPI4 Clock is PLL3 Q*/
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            spi_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_SPI4_CLKSOURCE_HSI:    /* SPI4 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          spi_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_SPI4_CLKSOURCE_CSI:    /* SPI4 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          spi_frequency = CSI_VALUE;
        }
        break;

      case LL_RCC_SPI4_CLKSOURCE_HSE:    /* SPI4 Clock is HSE Osc. */
        if (LL_RCC_HSE_IsReady() == 1U)
        {
          spi_frequency = HSE_VALUE;
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* SPI4 */
#if defined(SPI5)
  else if (SPIxSource == LL_RCC_SPI5_CLKSOURCE)
  {
    /* SPI5 CLK clock frequency */
    switch (LL_RCC_GetSPIClockSource(SPIxSource))
    {
      case LL_RCC_SPI5_CLKSOURCE_PCLK3: /* SPI5 Clock is PCLK3 */
        spi_frequency = RCC_GetPCLK3ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_SPI5_CLKSOURCE_PLL2Q: /* SPI5 Clock is PLL2 Q*/
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            spi_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_SPI5_CLKSOURCE_PLL3Q: /* SPI5 Clock is PLL3 Q*/
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            spi_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_SPI5_CLKSOURCE_HSI:    /* SPI5 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          spi_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_SPI5_CLKSOURCE_CSI:    /* SPI5 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          spi_frequency = CSI_VALUE;
        }
        break;

      case LL_RCC_SPI5_CLKSOURCE_HSE:    /* SPI5 Clock is HSE Osc. */
        if (LL_RCC_HSE_IsReady() == 1U)
        {
          spi_frequency = HSE_VALUE;
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* SPI5 */
#if defined(SPI6)
  else if (SPIxSource == LL_RCC_SPI6_CLKSOURCE)
  {
    /* SPI6 CLK clock frequency */
    switch (LL_RCC_GetSPIClockSource(SPIxSource))
    {
      case LL_RCC_SPI6_CLKSOURCE_PCLK2: /* SPI6 Clock is PCLK2 */
        spi_frequency = RCC_GetPCLK2ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_SPI6_CLKSOURCE_PLL2Q: /* SPI6 Clock is PLL2 Q*/
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            spi_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_SPI6_CLKSOURCE_PLL3Q: /* SPI6 Clock is PLL3 Q*/
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            spi_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_SPI6_CLKSOURCE_HSI:    /* SPI6 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          spi_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_SPI6_CLKSOURCE_CSI:    /* SPI6 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          spi_frequency = CSI_VALUE;
        }
        break;

      case LL_RCC_SPI6_CLKSOURCE_HSE:    /* SPI6 Clock is HSE Osc. */
        if (LL_RCC_HSE_IsReady() == 1U)
        {
          spi_frequency = HSE_VALUE;
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* SPI6 */

  else
  {
    /* nothing to do */
  }

  return spi_frequency;
}

/**
  * @brief  Return I2Cx clock frequency
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C2_CLKSOURCE
  *         @arg @ref LL_RCC_I2C3_CLKSOURCE (*)
  *         @arg @ref LL_RCC_I2C4_CLKSOURCE (*)
  *
  *  (*)  : For stm32h56xxx and stm32h57xxx family lines only.
  * @retval I2C clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready
  */
uint32_t LL_RCC_GetI2CClockFreq(uint32_t I2CxSource)
{
  uint32_t i2c_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_I2C_CLKSOURCE(I2CxSource));

  if (I2CxSource == LL_RCC_I2C1_CLKSOURCE)
  {
    /* I2C1 CLK clock frequency */
    switch (LL_RCC_GetI2CClockSource(I2CxSource))
    {
      case LL_RCC_I2C1_CLKSOURCE_PCLK1:  /* I2C1 Clock is PCLK1 */
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

#if defined(LL_RCC_I2C1_CLKSOURCE_PLL3R)
      case LL_RCC_I2C1_CLKSOURCE_PLL3R:   /* I2C1 Clock is PLL3 R */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            i2c_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;
#else
      case LL_RCC_I2C1_CLKSOURCE_PLL2R:   /* I2C1 Clock is PLL2 R */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            i2c_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;
#endif /* PLL3 */

      case LL_RCC_I2C1_CLKSOURCE_HSI:    /* I2C1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          i2c_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_I2C1_CLKSOURCE_CSI:    /* I2C1 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          i2c_frequency = CSI_VALUE;
        }
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
      case LL_RCC_I2C2_CLKSOURCE_PCLK1:  /* I2C2 Clock is PCLK1 */
        i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

#if defined(LL_RCC_I2C2_CLKSOURCE_PLL3R)
      case LL_RCC_I2C2_CLKSOURCE_PLL3R:   /* I2C2 Clock is PLL3 R */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            i2c_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;
#else
      case LL_RCC_I2C2_CLKSOURCE_PLL2R:   /* I2C2 Clock is PLL2 R */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            i2c_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;
#endif /* PLL3 */

      case LL_RCC_I2C2_CLKSOURCE_HSI:    /* I2C2 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          i2c_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_I2C2_CLKSOURCE_CSI:    /* I2C2 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          i2c_frequency = CSI_VALUE;
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#if defined(I2C3)
  else if (I2CxSource == LL_RCC_I2C3_CLKSOURCE)
  {
    /* I2C3 CLK clock frequency */
    switch (LL_RCC_GetI2CClockSource(I2CxSource))

    {
      case LL_RCC_I2C3_CLKSOURCE_PCLK3:  /* I2C3 Clock is PCLK3 */
        i2c_frequency = RCC_GetPCLK3ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_I2C3_CLKSOURCE_PLL3R:   /* I2C3 Clock is PLL3 R */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            i2c_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;

      case LL_RCC_I2C3_CLKSOURCE_HSI:    /* I2C3 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          i2c_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_I2C3_CLKSOURCE_CSI:    /* I2C3 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          i2c_frequency = CSI_VALUE;
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* I2C3 */
#if defined(I2C4)
  else if (I2CxSource == LL_RCC_I2C4_CLKSOURCE)
  {
    /* I2C4 CLK clock frequency */
    switch (LL_RCC_GetI2CClockSource(I2CxSource))
    {
      case LL_RCC_I2C4_CLKSOURCE_PCLK3:  /* I2C4 Clock is PCLK3 */
        i2c_frequency = RCC_GetPCLK3ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_I2C4_CLKSOURCE_PLL3R:   /* I2C4 Clock is PLL3 R */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            i2c_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;

      case LL_RCC_I2C4_CLKSOURCE_HSI:    /* I2C4 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          i2c_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_I2C4_CLKSOURCE_CSI:    /* I2C4 Clock is CSI Osc. */
        if (LL_RCC_CSI_IsReady() == 1U)
        {
          i2c_frequency = CSI_VALUE;
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* I2C4 */
  else
  {
    /* nothing to do */
  }

  return i2c_frequency;
}

/**
  * @brief  Return I3Cx clock frequency
  * @param  I3CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE
  *         @arg @ref LL_RCC_I3C2_CLKSOURCE (*)
  *
  *  (*)  : For stm32h503xx family line only.
  * @retval I3C clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready or no clock is selected
  */
uint32_t LL_RCC_GetI3CClockFreq(uint32_t I3CxSource)
{
  uint32_t I3C_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_I3C_CLKSOURCE(I3CxSource));


  if (I3CxSource == LL_RCC_I3C1_CLKSOURCE)
  {
    /* I3C1 CLK clock frequency */
    switch (LL_RCC_GetI3CClockSource(I3CxSource))
    {
      case LL_RCC_I3C1_CLKSOURCE_PCLK1:  /* I3C1 Clock is PCLK1 */
        I3C_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

#if defined(LL_RCC_I3C1_CLKSOURCE_PLL3R)
      case LL_RCC_I3C1_CLKSOURCE_PLL3R:   /* I3C1 Clock is PLL3 R */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            I3C_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;
#else
      case LL_RCC_I3C1_CLKSOURCE_PLL2R:   /* I3C1 Clock is PLL2 R */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            I3C_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;
#endif /* LL_RCC_I3C1_CLKSOURCE_PLL3R */

      case LL_RCC_I3C1_CLKSOURCE_HSI:    /* I3C1 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          I3C_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_I3C1_CLKSOURCE_NONE:    /* No Clock used for I3C1 */
        break;

      default:
        /* unreachable code */
        break;
    }

  }

#if defined (I3C2)
  else if (I3CxSource == LL_RCC_I3C2_CLKSOURCE)
  {
    /* I3C2 CLK clock frequency */
    switch (LL_RCC_GetI3CClockSource(I3CxSource))
    {
      case LL_RCC_I3C2_CLKSOURCE_PCLK3:  /* I3C2 Clock is PCLK3 */
        I3C_frequency = RCC_GetPCLK3ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_I3C2_CLKSOURCE_PLL2R:   /* I3C2 Clock is PLL2 R */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            I3C_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;

      case LL_RCC_I3C2_CLKSOURCE_HSI:    /* I3C2 Clock is HSI Osc. */
        if (LL_RCC_HSI_IsReady() == 1U)
        {
          I3C_frequency = HSI_VALUE;
        }
        break;

      case LL_RCC_I3C2_CLKSOURCE_NONE:    /* No Clock used for I3C2 */
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* I3C2 */
  else
  {
    /* nothing to do */
  }

  return I3C_frequency;
}

/**
  * @brief  Return LPUARTx clock frequency
  * @param  LPUARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE
  * @retval LPUART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready
  */
uint32_t LL_RCC_GetLPUARTClockFreq(uint32_t LPUARTxSource)
{
  uint32_t lpuart_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_LPUART_CLKSOURCE(LPUARTxSource));

  /* LPUART1CLK clock frequency */
  switch (LL_RCC_GetLPUARTClockSource(LPUARTxSource))
  {
    case LL_RCC_LPUART1_CLKSOURCE_PCLK3: /* LPUART1 Clock is is PCLK3 */
      lpuart_frequency = RCC_GetPCLK3ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
      break;

    case LL_RCC_LPUART1_CLKSOURCE_PLL2Q:   /* LPUART1 Clock is PLL2 Q */
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        if (LL_RCC_PLL2Q_IsEnabled() != 0U)
        {
          LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
          lpuart_frequency = PLL_Clocks.PLL_Q_Frequency;
        }
      }
      break;

#if defined(LL_RCC_LPUART1_CLKSOURCE_PLL3Q)
    case LL_RCC_LPUART1_CLKSOURCE_PLL3Q:   /* LPUART1 Clock is PLL3 Q */
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        if (LL_RCC_PLL3Q_IsEnabled() != 0U)
        {
          LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
          lpuart_frequency = PLL_Clocks.PLL_Q_Frequency;
        }
      }
      break;
#endif /* PLL3 */

    case LL_RCC_LPUART1_CLKSOURCE_HSI:    /* LPUART1 Clock is HSI Osc. */
      if (LL_RCC_HSI_IsReady() == 1U)
      {
        lpuart_frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_LPUART1_CLKSOURCE_CSI:    /* LPUART1 Clock is CSI Osc. */
      if (LL_RCC_CSI_IsReady() == 1U)
      {
        lpuart_frequency = CSI_VALUE;
      }
      break;

    case LL_RCC_LPUART1_CLKSOURCE_LSE:    /* LPUART1 Clock is LSE Osc. */
      if (LL_RCC_LSE_IsReady() == 1U)
      {
        lpuart_frequency = LSE_VALUE;
      }
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
  *         @arg @ref LL_RCC_LPTIM3_CLKSOURCE (*)
  *         @arg @ref LL_RCC_LPTIM4_CLKSOURCE (*)
  *         @arg @ref LL_RCC_LPTIM5_CLKSOURCE (*)
  *         @arg @ref LL_RCC_LPTIM6_CLKSOURCE (*)
  *
  *  (*)  : For stm32h56xxx and stm32h57xxx family lines only.
  * @retval LPTIM clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready
  */
uint32_t LL_RCC_GetLPTIMClockFreq(uint32_t LPTIMxSource)
{
  uint32_t lptim_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_LPTIM_CLKSOURCE(LPTIMxSource));

  if (LPTIMxSource == LL_RCC_LPTIM1_CLKSOURCE)
  {
    /* LPTIM1CLK clock frequency */
    switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
    {
      case LL_RCC_LPTIM1_CLKSOURCE_PCLK3: /* LPTIM1 Clock is is PCLK3 */
        lptim_frequency = RCC_GetPCLK3ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_LPTIM1_CLKSOURCE_PLL2P:   /* LPTIM1 Clock is PLL2 P */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            lptim_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;

#if defined(LL_RCC_LPTIM1_CLKSOURCE_PLL3R)
      case LL_RCC_LPTIM1_CLKSOURCE_PLL3R:   /* LPTIM1 Clock is PLL3 R */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            lptim_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;
#endif /* PLL3 */

      case LL_RCC_LPTIM1_CLKSOURCE_LSE:    /* LPTIM1 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          lptim_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPTIM1_CLKSOURCE_LSI:    /* LPTIM1 Clock is LSI Osc. */
        if (LL_RCC_LSI_IsReady() == 1U)
        {
          lptim_frequency = LSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM1_CLKSOURCE_CLKP:  /* LPTIM1 Clock is CLKP */
        lptim_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_GetCLKPClockSource(LL_RCC_CLKP_CLKSOURCE));
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
      case LL_RCC_LPTIM2_CLKSOURCE_PCLK1: /* LPTIM2 Clock is is PCLK1 */
        lptim_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_LPTIM2_CLKSOURCE_PLL2P:   /* LPTIM2 Clock is PLL2 P */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            lptim_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;

#if defined(LL_RCC_LPTIM2_CLKSOURCE_PLL3R)
      case LL_RCC_LPTIM2_CLKSOURCE_PLL3R:   /* LPTIM2 Clock is PLL3 R */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            lptim_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;
#endif /* PLL3 */

      case LL_RCC_LPTIM2_CLKSOURCE_LSE:    /* LPTIM2 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          lptim_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPTIM2_CLKSOURCE_LSI:    /* LPTIM2 Clock is LSI Osc. */
        if (LL_RCC_LSI_IsReady() == 1U)
        {
          lptim_frequency = LSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM2_CLKSOURCE_CLKP:  /* LPTIM2 Clock is CLKP */
        lptim_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_GetCLKPClockSource(LL_RCC_CLKP_CLKSOURCE));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#if defined(LPTIM3)
  else if (LPTIMxSource == LL_RCC_LPTIM3_CLKSOURCE)
  {
    /* LPTIM3CLK clock frequency */
    switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
    {
      case LL_RCC_LPTIM3_CLKSOURCE_PCLK3: /* LPTIM3 Clock is is PCLK3 */
        lptim_frequency = RCC_GetPCLK3ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_LPTIM3_CLKSOURCE_PLL2P:   /* LPTIM3 Clock is PLL2 P */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            lptim_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;

      case LL_RCC_LPTIM3_CLKSOURCE_PLL3R:   /* LPTIM3 Clock is PLL3 R */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            lptim_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;

      case LL_RCC_LPTIM3_CLKSOURCE_LSE:    /* LPTIM3 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          lptim_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPTIM3_CLKSOURCE_LSI:    /* LPTIM3 Clock is LSI Osc. */
        if (LL_RCC_LSI_IsReady() == 1U)
        {
          lptim_frequency = LSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM3_CLKSOURCE_CLKP:  /* LPTIM3 Clock is CLKP */
        lptim_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_GetCLKPClockSource(LL_RCC_CLKP_CLKSOURCE));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* LPTIM3 */
#if defined(LPTIM4)
  else if (LPTIMxSource == LL_RCC_LPTIM4_CLKSOURCE)
  {
    /* LPTIM4CLK clock frequency */
    switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
    {
      case LL_RCC_LPTIM4_CLKSOURCE_PCLK3: /* LPTIM4 Clock is is PCLK3 */
        lptim_frequency = RCC_GetPCLK3ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_LPTIM4_CLKSOURCE_PLL2P:   /* LPTIM4 Clock is PLL2 P */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            lptim_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;

      case LL_RCC_LPTIM4_CLKSOURCE_PLL3R:   /* LPTIM4 Clock is PLL3 R */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            lptim_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;

      case LL_RCC_LPTIM4_CLKSOURCE_LSE:    /* LPTIM4 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          lptim_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPTIM4_CLKSOURCE_LSI:    /* LPTIM4 Clock is LSI Osc. */
        if (LL_RCC_LSI_IsReady() == 1U)
        {
          lptim_frequency = LSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM4_CLKSOURCE_CLKP:  /* LPTIM4 Clock is CLKP */
        lptim_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_GetCLKPClockSource(LL_RCC_CLKP_CLKSOURCE));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* LPTIM4 */
#if defined(LPTIM5)
  else if (LPTIMxSource == LL_RCC_LPTIM5_CLKSOURCE)
  {
    /* LPTIM5CLK clock frequency */
    switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
    {
      case LL_RCC_LPTIM5_CLKSOURCE_PCLK3: /* LPTIM5 Clock is is PCLK3 */
        lptim_frequency = RCC_GetPCLK3ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_LPTIM5_CLKSOURCE_PLL2P:   /* LPTIM5 Clock is PLL2 P */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            lptim_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;

      case LL_RCC_LPTIM5_CLKSOURCE_PLL3R:   /* LPTIM5 Clock is PLL3 R */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            lptim_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;

      case LL_RCC_LPTIM5_CLKSOURCE_LSE:    /* LPTIM5 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          lptim_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPTIM5_CLKSOURCE_LSI:    /* LPTIM5 Clock is LSI Osc. */
        if (LL_RCC_LSI_IsReady() == 1U)
        {
          lptim_frequency = LSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM5_CLKSOURCE_CLKP:  /* LPTIM5 Clock is CLKP */
        lptim_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_GetCLKPClockSource(LL_RCC_CLKP_CLKSOURCE));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* LPTIM5 */
#if defined(LPTIM6)
  else if (LPTIMxSource == LL_RCC_LPTIM6_CLKSOURCE)
  {
    /* LPTIM6CLK clock frequency */
    switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
    {
      case LL_RCC_LPTIM6_CLKSOURCE_PCLK3: /* LPTIM6 Clock is is PCLK3 */
        lptim_frequency = RCC_GetPCLK3ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq()));
        break;

      case LL_RCC_LPTIM6_CLKSOURCE_PLL2P:   /* LPTIM6 Clock is PLL2 P */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            lptim_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;

      case LL_RCC_LPTIM6_CLKSOURCE_PLL3R:   /* LPTIM6 Clock is PLL3 R */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            lptim_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;

      case LL_RCC_LPTIM6_CLKSOURCE_LSE:    /* LPTIM6 Clock is LSE Osc. */
        if (LL_RCC_LSE_IsReady() == 1U)
        {
          lptim_frequency = LSE_VALUE;
        }
        break;

      case LL_RCC_LPTIM6_CLKSOURCE_LSI:    /* LPTIM6 Clock is LSI Osc. */
        if (LL_RCC_LSI_IsReady() == 1U)
        {
          lptim_frequency = LSI_VALUE;
        }
        break;

      case LL_RCC_LPTIM6_CLKSOURCE_CLKP:  /* LPTIM6 Clock is CLKP */
        lptim_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_GetCLKPClockSource(LL_RCC_CLKP_CLKSOURCE));
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* LPTIM6 */
  else
  {
    /* nothing to do */
  }

  return lptim_frequency;
}

#if defined(SAI1)
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
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_SAI_CLKSOURCE(SAIxSource));

  if (SAIxSource == LL_RCC_SAI1_CLKSOURCE)
  {
    /* SAI1CLK clock frequency */
    switch (LL_RCC_GetSAIClockSource(SAIxSource))
    {
      case LL_RCC_SAI1_CLKSOURCE_PLL1Q:        /* PLL1 Q clock used as SAI1 clock source */
        if (LL_RCC_PLL1_IsReady() != 0U)
        {
          if (LL_RCC_PLL1Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
            sai_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_SAI1_CLKSOURCE_PLL2P:        /* PLL2 P clock used as SAI1 clock source */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            sai_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;

      case LL_RCC_SAI1_CLKSOURCE_PLL3P:        /* PLL3 P clock used as SAI1 clock source */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            sai_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;

      case LL_RCC_SAI1_CLKSOURCE_PIN:         /* External input clock used as SAI1 clock source */
        sai_frequency = EXTERNAL_CLOCK_VALUE;
        break;

      case LL_RCC_SAI1_CLKSOURCE_CLKP:       /* CLKP used as SAI1 clock source  */
        sai_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_GetCLKPClockSource(LL_RCC_CLKP_CLKSOURCE));
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
      case LL_RCC_SAI2_CLKSOURCE_PLL1Q:        /* PLL1 Q clock used as SAI2 clock source */
        if (LL_RCC_PLL1_IsReady() != 0U)
        {
          if (LL_RCC_PLL1Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
            sai_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_SAI2_CLKSOURCE_PLL2P:        /* PLL2 P clock used as SAI2 clock source */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            sai_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;

      case LL_RCC_SAI2_CLKSOURCE_PLL3P:        /* PLL3 P clock used as SAI2 clock source */
        if (LL_RCC_PLL3_IsReady() != 0U)
        {
          if (LL_RCC_PLL3P_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
            sai_frequency = PLL_Clocks.PLL_P_Frequency;
          }
        }
        break;

      case LL_RCC_SAI2_CLKSOURCE_PIN:         /* External input clock used as SAI2 clock source */
        sai_frequency = EXTERNAL_CLOCK_VALUE;
        break;

      case LL_RCC_SAI2_CLKSOURCE_CLKP:       /* SAI2 Clock is CLKP */
        sai_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_GetCLKPClockSource(LL_RCC_CLKP_CLKSOURCE));
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
#endif /* SAI1 */

#if defined(SDMMC1)
/**
  * @brief  Return SDMMCx clock frequency
  * @param  SDMMCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC1_CLKSOURCE
  *         @arg @ref LL_RCC_SDMMC2_CLKSOURCE (*)
  * @retval SDMMC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready
  *
  * (*) : Available on some STM32H5 lines only.
  */
uint32_t LL_RCC_GetSDMMCClockFreq(uint32_t SDMMCxSource)
{
  uint32_t sdmmc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_SDMMC_CLKSOURCE(SDMMCxSource));

  if (SDMMCxSource == LL_RCC_SDMMC1_CLKSOURCE)
  {
    /* SDMMC1CLK clock frequency */
    switch (LL_RCC_GetSDMMCClockSource(SDMMCxSource))
    {
      case LL_RCC_SDMMC1_CLKSOURCE_PLL1Q:        /* PLL1 Q clock used as SDMMC1 clock source */
        if (LL_RCC_PLL1_IsReady() != 0U)
        {
          if (LL_RCC_PLL1Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
            sdmmc_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_SDMMC1_CLKSOURCE_PLL2R:        /* PLL2 R clock used as SDMMC1 clock source */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            sdmmc_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }

#if defined(SDMMC2)
  else if (SDMMCxSource == LL_RCC_SDMMC2_CLKSOURCE)
  {
    /* SDMMC2CLK clock frequency */
    switch (LL_RCC_GetSDMMCClockSource(SDMMCxSource))
    {
      case LL_RCC_SDMMC2_CLKSOURCE_PLL1Q:        /* PLL1 Q clock used as SDMMC2 clock source */
        if (LL_RCC_PLL1_IsReady() != 0U)
        {
          if (LL_RCC_PLL1Q_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
            sdmmc_frequency = PLL_Clocks.PLL_Q_Frequency;
          }
        }
        break;

      case LL_RCC_SDMMC2_CLKSOURCE_PLL2R:        /* PLL2 R clock used as SDMMC2 clock source */
        if (LL_RCC_PLL2_IsReady() != 0U)
        {
          if (LL_RCC_PLL2R_IsEnabled() != 0U)
          {
            LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
            sdmmc_frequency = PLL_Clocks.PLL_R_Frequency;
          }
        }
        break;

      default:
        /* unreachable code */
        break;
    }
  }
#endif /* SDMMC2 */

  else
  {
    /* nothing to do */
  }

  return sdmmc_frequency;
}
#endif /* SDMMC1 */

/**
  * @brief  Return RNGx clock frequency
  * @param  RNGxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_RNG_CLKSOURCE
  * @retval RNG clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready
  */
uint32_t LL_RCC_GetRNGClockFreq(uint32_t RNGxSource)
{
  uint32_t rng_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_RNG_CLKSOURCE(RNGxSource));

  /* RNGCLK clock frequency */
  switch (LL_RCC_GetRNGClockSource(RNGxSource))
  {
    case LL_RCC_RNG_CLKSOURCE_HSI48:          /* HSI48 clock used as RNG clock source */
      if (LL_RCC_HSI48_IsReady() == 1U)
      {
        rng_frequency = HSI48_VALUE;
      }
      break;

    case LL_RCC_RNG_CLKSOURCE_PLL1Q:           /* PLL1 Q clock used as RNG clock source */
      if (LL_RCC_PLL1_IsReady() != 0U)
      {
        if (LL_RCC_PLL1Q_IsEnabled() != 0U)
        {
          LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
          rng_frequency = PLL_Clocks.PLL_Q_Frequency;
        }
      }
      break;

    case LL_RCC_RNG_CLKSOURCE_LSE:            /* LSE clock used as RNG clock source */
      if (LL_RCC_LSE_IsReady() == 1U)
      {
        rng_frequency = LSE_VALUE;
      }
      break;

    case LL_RCC_RNG_CLKSOURCE_LSI:            /* LSI clock used as RNG clock source */
      if (LL_RCC_LSI_IsReady() == 1U)
      {
        rng_frequency = LSI_VALUE;
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
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready or no clock is selected
  */
uint32_t LL_RCC_GetUSBClockFreq(uint32_t USBxSource)
{
  uint32_t usb_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_USB_CLKSOURCE(USBxSource));

  /* USBCLK clock frequency */
  switch (LL_RCC_GetUSBClockSource(USBxSource))
  {

    case LL_RCC_USB_CLKSOURCE_NONE:          /* NO clock used as USB clock source */
      break;

    case LL_RCC_USB_CLKSOURCE_PLL1Q:          /* PLL1 Q clock used as USB clock source */
      if (LL_RCC_PLL1_IsReady() != 0U)
      {
        if (LL_RCC_PLL1Q_IsEnabled() != 0U)
        {
          LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
          usb_frequency = PLL_Clocks.PLL_Q_Frequency;
        }
      }
      break;

#if defined(LL_RCC_USB_CLKSOURCE_PLL3Q)
    case LL_RCC_USB_CLKSOURCE_PLL3Q:          /* PLL3 Q clock used as USB clock source */
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        if (LL_RCC_PLL3Q_IsEnabled() != 0U)
        {
          LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
          usb_frequency = PLL_Clocks.PLL_Q_Frequency;
        }
      }
      break;
#endif /* LL_RCC_USB_CLKSOURCE_PLL3 */

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
  * @param  ADCDACxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADCDAC_CLKSOURCE
  * @retval ADCDAC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready
  */
uint32_t LL_RCC_GetADCDACClockFreq(uint32_t ADCDACxSource)
{
  uint32_t adcdac_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_ADCDAC_CLKSOURCE(ADCDACxSource));

  /* ADCCLK clock frequency */
  switch (LL_RCC_GetADCDACClockSource(ADCDACxSource))
  {
    case LL_RCC_ADCDAC_CLKSOURCE_HCLK:         /* ADCDAC Clock is AHB clock */
      adcdac_frequency = RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq());
      break;

    case LL_RCC_ADCDAC_CLKSOURCE_SYSCLK:       /* ADCDAC Clock is SYSCLK clock */
      adcdac_frequency = RCC_GetSystemClockFreq();
      break;

    case LL_RCC_ADCDAC_CLKSOURCE_PLL2R:         /* ADCDAC Clock is PLL2 R */
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        if (LL_RCC_PLL2R_IsEnabled() != 0U)
        {
          LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
          adcdac_frequency = PLL_Clocks.PLL_R_Frequency;
        }
      }
      break;

    case LL_RCC_ADCDAC_CLKSOURCE_HSE:          /* ADCDAC Clock is HSE Osc. */
      if (LL_RCC_HSE_IsReady() == 1U)
      {
        adcdac_frequency = HSE_VALUE;
      }
      break;

    case LL_RCC_ADCDAC_CLKSOURCE_HSI:          /* ADCDAC Clock is HSI Osc. */
      if (LL_RCC_HSI_IsReady() == 1U)
      {
        adcdac_frequency = HSI_VALUE;
      }
      break;

    case LL_RCC_ADCDAC_CLKSOURCE_CSI:          /* ADCDAC Clock is CSI Osc. */
      if (LL_RCC_CSI_IsReady() == 1U)
      {
        adcdac_frequency = CSI_VALUE;
      }
      break;

    default:
      /* unreachable code */
      break;
  }

  return adcdac_frequency;
}

/**
  * @brief  Return DAC low-power clock frequency
  * @param  DACLPxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_DAC_LP_CLKSOURCE
  * @retval DAC low-power clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that LSI or LSE oscillator is not ready
  */
uint32_t LL_RCC_GetDACLPClockFreq(uint32_t DACLPxSource)
{
  uint32_t daclp_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_DAC_LP_CLKSOURCE(DACLPxSource));

  /* DAC clock frequency */
  switch (LL_RCC_GetDACLPClockSource(DACLPxSource))
  {
    case LL_RCC_DAC_LP_CLKSOURCE_LSE:    /* DAC low-power Clock is LSE Osc. */
      if (LL_RCC_LSE_IsReady() == 1U)
      {
        daclp_frequency = LSE_VALUE;
      }
      break;

    case LL_RCC_DAC_LP_CLKSOURCE_LSI:    /* DAC low-power Clock is LSI Osc. */
      if (LL_RCC_LSI_IsReady() == 1U)
      {
        daclp_frequency = LSI_VALUE;
      }
      break;

    default:
      /* unreachable code */
      break;
  }

  return daclp_frequency;
}

#if defined( OCTOSPI1)
/**
  * @brief  Return OCTOSPI clock frequency
  * @param  OCTOSPIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_OCTOSPI_CLKSOURCE
  * @retval OCTOSPI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready
  */
uint32_t LL_RCC_GetOCTOSPIClockFreq(uint32_t OCTOSPIxSource)
{
  uint32_t octospi_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_OCTOSPI_CLKSOURCE(OCTOSPIxSource));

  /* OCTOSPI clock frequency */
  switch (LL_RCC_GetOCTOSPIClockSource(OCTOSPIxSource))
  {
    case LL_RCC_OSPI_CLKSOURCE_HCLK:   /* OCTOSPI clock is SYSCLK */
      octospi_frequency = RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq());
      break;

    case LL_RCC_OSPI_CLKSOURCE_PLL1Q:      /* OSPI Clock is PLL1 Q */
      if (LL_RCC_PLL1_IsReady() != 0U)
      {
        if (LL_RCC_PLL1Q_IsEnabled() != 0U)
        {
          LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
          octospi_frequency = PLL_Clocks.PLL_Q_Frequency;
        }
      }
      break;

    case LL_RCC_OSPI_CLKSOURCE_PLL2R:      /* OSPI Clock is PLL2 R */
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        if (LL_RCC_PLL2R_IsEnabled() != 0U)
        {
          LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
          octospi_frequency = PLL_Clocks.PLL_R_Frequency;
        }
      }
      break;

    case LL_RCC_OSPI_CLKSOURCE_CLKP:       /* OSPI Clock is CLKP */
      octospi_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_GetCLKPClockSource(LL_RCC_CLKP_CLKSOURCE));
      break;

    default:
      /* unreachable code */
      break;
  }

  return octospi_frequency;
}
#endif /* OCTOSPI1 */

/**
  * @brief  Return FDCAN kernel clock frequency
  * @param  FDCANxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE
  * @retval FDCAN kernel clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator or PLL is not ready or no clock is selected
  *
  */
uint32_t LL_RCC_GetFDCANClockFreq(uint32_t FDCANxSource)
{
  uint32_t fdcan_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_FDCAN_CLKSOURCE(FDCANxSource));

  /* FDCANCLK clock frequency */
  switch (LL_RCC_GetFDCANClockSource(FDCANxSource))
  {
    case LL_RCC_FDCAN_CLKSOURCE_HSE:        /* HSE clock used as FDCAN clock source */
      if (LL_RCC_HSE_IsReady() == 1U)
      {
        fdcan_frequency = HSE_VALUE;
      }
      break;

    case LL_RCC_FDCAN_CLKSOURCE_PLL1Q:      /* PLL1 Q clock used as FDCAN clock source */
      if (LL_RCC_PLL1_IsReady() != 0U)
      {
        if (LL_RCC_PLL1Q_IsEnabled() != 0U)
        {
          LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
          fdcan_frequency = PLL_Clocks.PLL_Q_Frequency;
        }
      }
      break;

    case LL_RCC_FDCAN_CLKSOURCE_PLL2Q:      /* PLL2 Q clock used as FDCAN clock source */
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        if (LL_RCC_PLL2Q_IsEnabled() != 0U)
        {
          LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
          fdcan_frequency = PLL_Clocks.PLL_Q_Frequency;
        }
      }
      break;

    case LL_RCC_FDCAN_CLKSOURCE_NONE:        /* No clock used as FDCAN clock source */
      break;

    default:
      /* unreachable code */
      break;
  }

  return fdcan_frequency;
}

#if defined(CEC)
/**
  * @brief  Return CEC clock frequency
  * @param  CECxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_CEC_CLKSOURCE
  * @retval CEC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready or no clock is selected
  */
uint32_t LL_RCC_GetCECClockFreq(uint32_t CECxSource)
{
  uint32_t cec_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  switch (LL_RCC_GetCECClockSource(CECxSource))
  {
    case LL_RCC_CEC_CLKSOURCE_LSE:         /* CEC Clock is LSE */
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        cec_frequency = LSE_VALUE;
      }
      break;

    case LL_RCC_CEC_CLKSOURCE_LSI:         /* CEC Clock is LSI */
      if (LL_RCC_LSI_IsReady() != 0U)
      {
        cec_frequency = LSI_VALUE;
      }
      break;

    case LL_RCC_CEC_CLKSOURCE_CSI_DIV122:  /* CEC Clock is CSI divided by 122 */
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        cec_frequency = CSI_VALUE / 122U;
      }
      break;

    case LL_RCC_CEC_CLKSOURCE_NONE:       /* No Clock selected for CEC */
      break;

    default:
      /* Kernel clock disabled */
      break;
  }

  return cec_frequency;
}
#endif /* CEC */

/**
  * @brief  Return CLKP clock frequency
  * @param  CLKPxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_CLKP_CLKSOURCE
  * @retval CLKP clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready or no clock is selected
  */
uint32_t LL_RCC_GetCLKPClockFreq(uint32_t CLKPxSource)
{
  uint32_t clkp_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  switch (LL_RCC_GetCLKPClockSource(CLKPxSource))
  {
    case LL_RCC_CLKP_CLKSOURCE_HSI:          /* HSI used as CLKP clock source */
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        clkp_frequency = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
      }
      break;

    case LL_RCC_CLKP_CLKSOURCE_CSI:          /* CSI used as CLKP clock source */
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        clkp_frequency = CSI_VALUE;
      }
      break;

    case LL_RCC_CLKP_CLKSOURCE_HSE:          /* HSE used as CLKP clock source */
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        clkp_frequency = HSE_VALUE;
      }
      break;

    case LL_RCC_CLKP_CLKSOURCE_NONE:          /* NO clock used as CLKP clock source */
      break;

    default:
      /* CLKP clock disabled */
      break;
  }

  return clkp_frequency;
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
uint32_t RCC_GetSystemClockFreq(void)
{
  uint32_t frequency;

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (LL_RCC_GetSysClkSource())
  {
    case LL_RCC_SYS_CLKSOURCE_STATUS_HSI:   /* HSI used as system clock  source */
      frequency = HSI_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_CSI:   /* CSI used as system clock  source */
      frequency = CSI_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_HSE:   /* HSE used as system clock  source */
      frequency = HSE_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_PLL1:  /* PLL1 used as system clock  source */
      frequency = RCC_PLL1_GetFreqSystem();
      break;

    default:
      frequency = HSI_VALUE;
      break;
  }

  return frequency;
}

/**
  * @brief  Return HCLK clock frequency
  * @param  SYSCLK_Frequency SYSCLK clock frequency
  * @retval HCLK clock frequency (in Hz)
  */
uint32_t RCC_GetHCLKClockFreq(uint32_t SYSCLK_Frequency)
{
  /* HCLK clock frequency */
  return __LL_RCC_CALC_HCLK_FREQ(SYSCLK_Frequency, LL_RCC_GetAHBPrescaler());
}

/**
  * @brief  Return PCLK1 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK1 clock frequency (in Hz)
  */
uint32_t RCC_GetPCLK1ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK1 clock frequency */
  return __LL_RCC_CALC_PCLK1_FREQ(HCLK_Frequency, LL_RCC_GetAPB1Prescaler());
}

/**
  * @brief  Return PCLK2 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK2 clock frequency (in Hz)
  */
uint32_t RCC_GetPCLK2ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK2 clock frequency */
  return __LL_RCC_CALC_PCLK2_FREQ(HCLK_Frequency, LL_RCC_GetAPB2Prescaler());
}


/**
  * @brief  Return PCLK3 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK3 clock frequency (in Hz)
  */
uint32_t RCC_GetPCLK3ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK3 clock frequency */
  return __LL_RCC_CALC_PCLK3_FREQ(HCLK_Frequency, LL_RCC_GetAPB3Prescaler());
}

/**
  * @brief  Return PLL1 clock frequency used for system clock
  * @retval PLL1 clock frequency (in Hz)
  */
uint32_t RCC_PLL1_GetFreqSystem(void)
{
  uint32_t pllinputfreq;
  uint32_t pllsource;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or CSI_VALUE/ PLLM) * PLLN
     SYSCLK = PLL_VCO / PLLP
  */
  pllsource = LL_RCC_PLL1_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLL1SOURCE_HSI:  /* HSI used as PLL1 clock source */
      pllinputfreq = HSI_VALUE;
      break;

    case LL_RCC_PLL1SOURCE_CSI:  /* CSI used as PLL1 clock source */
      pllinputfreq = CSI_VALUE;
      break;

    case LL_RCC_PLL1SOURCE_HSE:  /* HSE used as PLL1 clock source */
      pllinputfreq = HSE_VALUE;
      break;

    default:
      pllinputfreq = 0;
      break;
  }
  return __LL_RCC_CALC_PLL1CLK_P_FREQ(pllinputfreq, LL_RCC_PLL1_GetM(),
                                      LL_RCC_PLL1_GetN(), LL_RCC_PLL1_GetP());
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

