/**
  ******************************************************************************
  * @file    stm32h7rsxx_ll_rcc.c
  * @author  MCD Application Team
  * @brief   RCC LL module driver.
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
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_ll_rcc.h"
#include "stm32h7rsxx_ll_bus.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_LL_DRIVER */

/** @addtogroup STM32H7RSxx_LL_Driver
  * @{
  */

#if defined(RCC)

/** @addtogroup RCC_LL
  * @{
  */

/* Private variables ---------------------------------------------------------*/
/** @addtogroup RCC_LL_Exported_Variables
  * @{
  */
const uint8_t LL_RCC_PrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCC_LL_Private_Macros
  * @{
  */
#define IS_LL_RCC_ADC_CLKSOURCE(__VALUE__)      ((__VALUE__) == LL_RCC_ADC_CLKSOURCE)

#define IS_LL_RCC_ADF1_CLKSOURCE(__VALUE__)     (((__VALUE__) == LL_RCC_ADF1_CLKSOURCE))

#define IS_LL_RCC_CEC_CLKSOURCE(__VALUE__)     (((__VALUE__) == LL_RCC_CEC_CLKSOURCE))

#define IS_LL_RCC_CLKP_CLKSOURCE(__VALUE__)     (((__VALUE__) == LL_RCC_CLKP_CLKSOURCE))

#define IS_LL_RCC_ETH1PHY_CLKSOURCE(__VALUE__)     (((__VALUE__) == LL_RCC_ETH1PHY_CLKSOURCE))

#define IS_LL_RCC_ETHREF_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_ETHREF_CLKSOURCE))

#define IS_LL_RCC_FDCAN_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_FDCAN_CLKSOURCE))

#define IS_LL_RCC_FMC_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_FMC_CLKSOURCE))

#define IS_LL_RCC_I2C_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_I2C1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_I2C23_CLKSOURCE))

#define IS_LL_RCC_I3C_CLKSOURCE(__VALUE__)    ((__VALUE__) == LL_RCC_I3C1_CLKSOURCE)

#define IS_LL_RCC_LPTIM_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_LPTIM1_CLKSOURCE)  \
                                               || ((__VALUE__) == LL_RCC_LPTIM23_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_LPTIM45_CLKSOURCE))

#define IS_LL_RCC_LPUART_CLKSOURCE(__VALUE__)  ((__VALUE__) == LL_RCC_LPUART1_CLKSOURCE)

#define IS_LL_RCC_PSSI_CLKSOURCE(__VALUE__)    ((__VALUE__) == LL_RCC_PSSI_CLKSOURCE)

#define IS_LL_RCC_RTC_CLKSOURCE(__VALUE__)    ((__VALUE__) == LL_RCC_RTC_CLKSOURCE)

#define IS_LL_RCC_SAI_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_SAI1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_SAI2_CLKSOURCE))

#define IS_LL_RCC_SDMMC_CLKSOURCE(__VALUE__)  ((__VALUE__) == LL_RCC_SDMMC_CLKSOURCE)

#define IS_LL_RCC_SPI_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_SPI1_CLKSOURCE)  \
                                               || ((__VALUE__) == LL_RCC_SPI23_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_SPI45_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_SPI6_CLKSOURCE))

#define IS_LL_RCC_SPDIFRX_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_SPDIFRX_CLKSOURCE))

#define IS_LL_RCC_USART_CLKSOURCE(__VALUE__)  (((__VALUE__) == LL_RCC_USART1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_USART234578_CLKSOURCE))

#define IS_LL_RCC_XSPI_CLKSOURCE(__VALUE__)   (((__VALUE__) == LL_RCC_XSPI1_CLKSOURCE) \
                                               || ((__VALUE__) == LL_RCC_XSPI2_CLKSOURCE))

#define IS_LL_RCC_USBPHYC_CLKSOURCE(__VALUE__)    (((__VALUE__) == LL_RCC_USBPHYC_CLKSOURCE))

#define IS_LL_RCC_OTGFS_CLKSOURCE(__VALUE__)      (((__VALUE__) == LL_RCC_OTGFS_CLKSOURCE))

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
static uint32_t RCC_GetPCLK4ClockFreq(uint32_t HCLK_Frequency);
static uint32_t RCC_GetPCLK5ClockFreq(uint32_t HCLK_Frequency);

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
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *            - HSI ON and used as system clock source
  *            - HSE, PLL1, PLL2 and PLL3 OFF
  *            - AHB, APB Bus pre-scaler set to 1.
  *            - CSS, MCO1 and MCO2 OFF
  *            - All interrupts disabled
  * @note   This function doesn't modify the configuration of the
  *            - Peripheral clocks
  *            - LSI, LSE and RTC clocks
  * @note   In case the FMC or XSPI clock protection have been set, it must be disabled
  *         prior to calling this API.
  * @warning FLASH latency must be adjusted according to the targeted system clock
  *          frequency and voltage scaling.
  * @retval None
  */
void LL_RCC_DeInit(void)
{
  /* Increasing the CPU frequency */
  if (FLASH_LATENCY_DEFAULT  > (READ_BIT((FLASH->ACR), FLASH_ACR_LATENCY)))
  {
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (uint32_t)(FLASH_LATENCY_DEFAULT));
  }

  /* Set HSION bit */
  SET_BIT(RCC->CR, RCC_CR_HSION);

  /* Wait for HSI READY bit */
  while (LL_RCC_HSI_IsReady() == 0U)
  {}

  /* Reset CFGR register to select HSI as system clock */
  CLEAR_REG(RCC->CFGR);

  /* Reset CSION, CSIKERON, HSEON, HSEEXT, HSI48ON, HSIDIV, PLL1ON, PLL2ON, PLL3ON bits */
  CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_HSEEXT | RCC_CR_HSIKERON | RCC_CR_HSIDIV | RCC_CR_CSION | RCC_CR_CSIKERON | \
            RCC_CR_HSI48ON | RCC_CR_PLL1ON | RCC_CR_PLL2ON | RCC_CR_PLL3ON);

  /* Wait for PLL1 READY bit to be reset */
  while (LL_RCC_PLL1_IsReady() != 0U)
  {}

  /* Wait for PLL2 READY bit to be reset */
  while (LL_RCC_PLL2_IsReady() != 0U)
  {}

  /* Wait for PLL3 READY bit to be reset */
  while (LL_RCC_PLL3_IsReady() != 0U)
  {}

  /* Reset CDCFGR register */
  CLEAR_REG(RCC->CDCFGR);

  /* Reset BMCFGR register */
  CLEAR_REG(RCC->BMCFGR);

  /* Reset APBCFGR register */
  CLEAR_REG(RCC->APBCFGR);

  /* Reset PLLCKSELR register to default value */
  LL_RCC_WriteReg(PLLCKSELR, \
                  (32U << RCC_PLLCKSELR_DIVM1_Pos) | (32U << RCC_PLLCKSELR_DIVM2_Pos) | (32U << RCC_PLLCKSELR_DIVM3_Pos));

  /* Reset PLLCFGR register to default value */
  LL_RCC_WriteReg(PLLCFGR, 0U);

  /* Reset PLL1DIVR1/PLL1DIVR2 registers to default value */
  LL_RCC_WriteReg(PLL1DIVR1, 0x01010280U);
  LL_RCC_WriteReg(PLL1DIVR2, 0x00000101U);

  /* Reset PLL1FRACR register */
  CLEAR_REG(RCC->PLL1FRACR);

  /* Reset PLL2DIVR1/PLL2DIVR2 registers to default value */
  LL_RCC_WriteReg(PLL2DIVR1, 0x01010280U);
  LL_RCC_WriteReg(PLL2DIVR2, 0x00000101U);

  /* Reset PLL2FRACR register */
  CLEAR_REG(RCC->PLL2FRACR);

  /* Reset PLL2DIVR1/PLL2DIVR2 registers to default value */
  LL_RCC_WriteReg(PLL2DIVR1, 0x01010280U);
  LL_RCC_WriteReg(PLL2DIVR2, 0x00000101U);

  /* Reset PLL3FRACR register */
  CLEAR_REG(RCC->PLL3FRACR);

  /* Reset HSEBYP bit */
  CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);

  /* Disable all interrupts */
  CLEAR_REG(RCC->CIER);

  /* Clear all interrupts */
  SET_BIT(RCC->CICR, RCC_CICR_LSIRDYC | RCC_CICR_LSERDYC | RCC_CICR_HSIRDYC | RCC_CICR_HSERDYC | \
          RCC_CICR_CSIRDYC | RCC_CICR_HSI48RDYC | RCC_CICR_PLL1RDYC | RCC_CICR_PLL2RDYC | \
          RCC_CICR_PLL3RDYC | RCC_CICR_LSECSSC | RCC_CICR_HSECSSC);

  /* Clear reset source flags */
  SET_BIT(RCC->RSR, RCC_RSR_RMVF);

  /* Decreasing the number of wait states because of lower CPU frequency */
  if (FLASH_LATENCY_DEFAULT  < (READ_BIT((FLASH->ACR), FLASH_ACR_LATENCY)))
  {
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (uint32_t)(FLASH_LATENCY_DEFAULT));
  }
}

/**
  * @}
  */

/** @addtogroup RCC_LL_EF_Get_Freq
  * @brief  Return the frequencies of different on chip clocks;  System, AHB, APB1, APB2, APB3 and APB4 buses clocks.
  *         and different peripheral clocks available on the device.
  * @note   If SYSCLK source is HSI, function returns values based on HSI_VALUE(*)
  * @note   If SYSCLK source is HSE, function returns values based on HSE_VALUE(**)
  * @note   If SYSCLK source is CSI, function returns values based on CSI_VALUE(***)
  * @note   If SYSCLK source is PLL, function returns values based on HSE_VALUE(**)
  *         or HSI_VALUE(*) multiplied/divided by the PLL factors.
  * @note   (*) HSI_VALUE is a constant defined in header file (default value
  *             64 MHz) divider by HSIDIV, but the real value may vary depending on
  *             on the variations in voltage and temperature.
  * @note   (**) HSE_VALUE is a constant defined in header file (default value
  *              24 MHz), user has to ensure that HSE_VALUE is same as the real
  *              frequency of the crystal used. Otherwise, this function may
  *              have wrong result.
  * @note   (***) CSI_VALUE is a constant defined in header file (default value
  *               4 MHz) but the real value may vary depending on the variations
  *               in voltage and temperature.
  * @note   The result of this function could be incorrect when using fractional
  *         value for HSE crystal.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @{
  */

/**
  * @brief  Return the frequencies of different on chip clocks;  System, AHB, APB1, APB2, APB4 and APB5 buses clocks.
  * @note   Each time SYSCLK, HCLK, PCLK1, PCLK2, PCLK4 and/or PCLK5 clock changes, this function
  *         must be called to update structure fields. Otherwise, any
  *         configuration based on this function will be incorrect.
  * @param  RCC_Clocks pointer to a @ref LL_RCC_ClocksTypeDef structure which will hold the clocks frequencies
  * @retval None
  */
void LL_RCC_GetSystemClocksFreq(LL_RCC_ClocksTypeDef *RCC_Clocks)
{
  /* Get SYSCLK frequency */
  RCC_Clocks->SYSCLK_Frequency = LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler());

  /* HCLK clock frequency */
  RCC_Clocks->HCLK_Frequency   = RCC_GetHCLKClockFreq(RCC_Clocks->SYSCLK_Frequency);

  /* PCLK1 clock frequency */
  RCC_Clocks->PCLK1_Frequency  = RCC_GetPCLK1ClockFreq(RCC_Clocks->HCLK_Frequency);

  /* PCLK2 clock frequency */
  RCC_Clocks->PCLK2_Frequency  = RCC_GetPCLK2ClockFreq(RCC_Clocks->HCLK_Frequency);

  /* PCLK4 clock frequency */
  RCC_Clocks->PCLK4_Frequency  = RCC_GetPCLK4ClockFreq(RCC_Clocks->HCLK_Frequency);

  /* PCLK5 clock frequency */
  RCC_Clocks->PCLK5_Frequency  = RCC_GetPCLK5ClockFreq(RCC_Clocks->HCLK_Frequency);
}

/**
  * @brief  Return PLL1 clocks frequencies
  * @note   LL_RCC_PERIPH_FREQUENCY_NO returned for non activated output or oscillator not ready
  * @retval None
  */
void LL_RCC_GetPLL1ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks)
{
  uint32_t pllinputfreq = LL_RCC_PERIPH_FREQUENCY_NO;
  uint32_t pllsource;
  uint32_t m;
  uint32_t n;
  uint32_t fracn = 0U;

  /* PLL_VCO = (HSE_VALUE, CSI_VALUE or HSI_VALUE/HSIDIV) / PLLM * (PLLN + FRACN)
     SYSCLK = PLL_VCO / PLLP
  */
  pllsource = LL_RCC_PLL_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        if (LL_RCC_HSI_IsDividerReady() != 0U)
        {
          pllinputfreq = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
        }
      }
      break;

    case LL_RCC_PLLSOURCE_CSI:
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        pllinputfreq = CSI_VALUE;
      }
      break;

    case LL_RCC_PLLSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        pllinputfreq = HSE_VALUE;
      }
      break;

    case LL_RCC_PLLSOURCE_NONE:
    default:
      /* PLL clock disabled */
      break;
  }

  PLL_Clocks->PLL_P_Frequency = 0U;
  PLL_Clocks->PLL_Q_Frequency = 0U;
  PLL_Clocks->PLL_R_Frequency = 0U;
  PLL_Clocks->PLL_S_Frequency = 0U;
  PLL_Clocks->PLL_T_Frequency = 0U;

  m = LL_RCC_PLL1_GetM();
  n = LL_RCC_PLL1_GetN();
  if (LL_RCC_PLL1FRACN_IsEnabled() != 0U)
  {
    fracn = LL_RCC_PLL1_GetFRACN();
  }

  if (m != 0U)
  {
    if (LL_RCC_PLL1P_IsEnabled() != 0U)
    {
      PLL_Clocks->PLL_P_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, m, n, fracn, LL_RCC_PLL1_GetP());
    }

    if (LL_RCC_PLL1Q_IsEnabled() != 0U)
    {
      PLL_Clocks->PLL_Q_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, m, n, fracn, LL_RCC_PLL1_GetQ());
    }

    if (LL_RCC_PLL1R_IsEnabled() != 0U)
    {
      PLL_Clocks->PLL_R_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, m, n, fracn, LL_RCC_PLL1_GetR());
    }

    if (LL_RCC_PLL1S_IsEnabled() != 0U)
    {
      PLL_Clocks->PLL_S_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, m, n, fracn, LL_RCC_PLL1_GetS());
    }
  }
}

/**
  * @brief  Return PLL2 clocks frequencies
  * @note   LL_RCC_PERIPH_FREQUENCY_NO returned for non activated output or oscillator not ready
  * @retval None
  */
void LL_RCC_GetPLL2ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks)
{
  uint32_t pllinputfreq = LL_RCC_PERIPH_FREQUENCY_NO;
  uint32_t pllsource;
  uint32_t m;
  uint32_t n;
  uint32_t fracn = 0U;

  /* PLL_VCO = (HSE_VALUE, CSI_VALUE or HSI_VALUE/HSIDIV) / PLLM * (PLLN + FRACN)
     SYSCLK = PLL_VCO / PLLP
  */
  pllsource = LL_RCC_PLL_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        if (LL_RCC_HSI_IsDividerReady() != 0U)
        {
          pllinputfreq = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
        }
      }
      break;

    case LL_RCC_PLLSOURCE_CSI:
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        pllinputfreq = CSI_VALUE;
      }
      break;

    case LL_RCC_PLLSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        pllinputfreq = HSE_VALUE;
      }
      break;

    case LL_RCC_PLLSOURCE_NONE:
    default:
      /* PLL clock disabled */
      break;
  }

  PLL_Clocks->PLL_P_Frequency = 0U;
  PLL_Clocks->PLL_Q_Frequency = 0U;
  PLL_Clocks->PLL_R_Frequency = 0U;
  PLL_Clocks->PLL_S_Frequency = 0U;
  PLL_Clocks->PLL_T_Frequency = 0U;

  m = LL_RCC_PLL2_GetM();
  n = LL_RCC_PLL2_GetN();
  if (LL_RCC_PLL2FRACN_IsEnabled() != 0U)
  {
    fracn = LL_RCC_PLL2_GetFRACN();
  }

  if (m != 0U)
  {
    if (LL_RCC_PLL2P_IsEnabled() != 0U)
    {
      PLL_Clocks->PLL_P_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, m, n, fracn, LL_RCC_PLL2_GetP());
    }

    if (LL_RCC_PLL2Q_IsEnabled() != 0U)
    {
      PLL_Clocks->PLL_Q_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, m, n, fracn, LL_RCC_PLL2_GetQ());
    }

    if (LL_RCC_PLL2R_IsEnabled() != 0U)
    {
      PLL_Clocks->PLL_R_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, m, n, fracn, LL_RCC_PLL2_GetR());
    }

    if (LL_RCC_PLL2S_IsEnabled() != 0U)
    {
      PLL_Clocks->PLL_S_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, m, n, fracn, LL_RCC_PLL2_GetS());
    }

    if (LL_RCC_PLL2T_IsEnabled() != 0U)
    {
      PLL_Clocks->PLL_T_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, m, n, fracn, LL_RCC_PLL2_GetT());
    }
  }
}

/**
  * @brief  Return PLL3 clocks frequencies
  * @note   LL_RCC_PERIPH_FREQUENCY_NO returned for non activated output or oscillator not ready
  * @retval None
  */
void LL_RCC_GetPLL3ClockFreq(LL_PLL_ClocksTypeDef *PLL_Clocks)
{
  uint32_t pllinputfreq = LL_RCC_PERIPH_FREQUENCY_NO;
  uint32_t pllsource;
  uint32_t m;
  uint32_t n;
  uint32_t fracn = 0U;

  /* PLL_VCO = (HSE_VALUE, CSI_VALUE or HSI_VALUE/HSIDIV) / PLLM * (PLLN + FRACN)
     SYSCLK = PLL_VCO / PLLP
  */
  pllsource = LL_RCC_PLL_GetSource();

  switch (pllsource)
  {
    case LL_RCC_PLLSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        if (LL_RCC_HSI_IsDividerReady() != 0U)
        {
          pllinputfreq = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
        }
      }
      break;

    case LL_RCC_PLLSOURCE_CSI:
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        pllinputfreq = CSI_VALUE;
      }
      break;

    case LL_RCC_PLLSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        pllinputfreq = HSE_VALUE;
      }
      break;

    case LL_RCC_PLLSOURCE_NONE:
    default:
      /* PLL clock disabled */
      break;
  }

  PLL_Clocks->PLL_P_Frequency = 0U;
  PLL_Clocks->PLL_Q_Frequency = 0U;
  PLL_Clocks->PLL_R_Frequency = 0U;
  PLL_Clocks->PLL_S_Frequency = 0U;
  PLL_Clocks->PLL_T_Frequency = 0U;

  m = LL_RCC_PLL3_GetM();
  n = LL_RCC_PLL3_GetN();
  if (LL_RCC_PLL3FRACN_IsEnabled() != 0U)
  {
    fracn = LL_RCC_PLL3_GetFRACN();
  }

  if ((m != 0U) && (pllinputfreq != 0U))
  {
    if (LL_RCC_PLL3P_IsEnabled() != 0U)
    {
      PLL_Clocks->PLL_P_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, m, n, fracn, LL_RCC_PLL3_GetP());
    }

    if (LL_RCC_PLL3Q_IsEnabled() != 0U)
    {
      PLL_Clocks->PLL_Q_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, m, n, fracn, LL_RCC_PLL3_GetQ());
    }

    if (LL_RCC_PLL3R_IsEnabled() != 0U)
    {
      PLL_Clocks->PLL_R_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, m, n, fracn, LL_RCC_PLL3_GetR());
    }

    if (LL_RCC_PLL3S_IsEnabled() != 0U)
    {
      PLL_Clocks->PLL_S_Frequency = LL_RCC_CalcPLLClockFreq(pllinputfreq, m, n, fracn, LL_RCC_PLL3_GetS());
    }
  }
}

/**
  * @brief  Configure Spread Spectrum used for PLL1
  * @note These bits must be written before enabling PLL1
  * @note MODPER x INCSTEP shall not exceed 2^15-1
  * @rmtoll PLL1SSCGR    MODPER        LL_RCC_PLL1_ConfigSpreadSpectrum\n
  *         PLL1SSCGR    INCSTEP       LL_RCC_PLL1_ConfigSpreadSpectrum\n
  *         PLL1SSCGR    SPREADSEL     LL_RCC_PLL1_ConfigSpreadSpectrum\n
  *         PLL1SSCGR    TPDFNDIS      LL_RCC_PLL1_ConfigSpreadSpectrum\n
  *         PLL1SSCGR    RPDFNDIS      LL_RCC_PLL1_ConfigSpreadSpectrum
  * @param  pConfig Pointer to LL_PLL_SpreadSpectrumTypeDef structure
  * @retval None
  */
void LL_RCC_PLL1_ConfigSpreadSpectrum(const LL_PLL_SpreadSpectrumTypeDef *pConfig)
{
  MODIFY_REG(RCC->PLL1SSCGR, \
             (RCC_PLL1SSCGR_MODPER | RCC_PLL1SSCGR_INCSTEP | RCC_PLL1SSCGR_SPREADSEL | \
              RCC_PLL1SSCGR_TPDFNDIS | RCC_PLL1SSCGR_RPDFNDIS), \
             (pConfig->ModulationPeriod | ((uint32_t)pConfig->IncrementStep << RCC_PLL1SSCGR_INCSTEP_Pos) | \
              pConfig->SpreadMode | pConfig->DitheringTPDFN | pConfig->DitheringRPDFN));
}

/**
  * @brief  Configure Spread Spectrum used for PLL2
  * @note These bits must be written before enabling PLL2
  * @rmtoll PLL2SSCGR    MODPER        LL_RCC_PLL2_ConfigSpreadSpectrum\n
  *         PLL2SSCGR    INCSTEP       LL_RCC_PLL2_ConfigSpreadSpectrum\n
  *         PLL2SSCGR    SPREADSEL     LL_RCC_PLL2_ConfigSpreadSpectrum\n
  *         PLL2SSCGR    TPDFNDIS      LL_RCC_PLL2_ConfigSpreadSpectrum\n
  *         PLL2SSCGR    RPDFNDIS      LL_RCC_PLL2_ConfigSpreadSpectrum
  * @param  pConfig Pointer to LL_PLL_SpreadSpectrumTypeDef structure
  * @retval None
  */
void LL_RCC_PLL2_ConfigSpreadSpectrum(const LL_PLL_SpreadSpectrumTypeDef *pConfig)
{
  MODIFY_REG(RCC->PLL2SSCGR, \
             (RCC_PLL2SSCGR_MODPER | RCC_PLL2SSCGR_INCSTEP | RCC_PLL2SSCGR_SPREADSEL | \
              RCC_PLL2SSCGR_TPDFNDIS | RCC_PLL2SSCGR_RPDFNDIS), \
             (pConfig->ModulationPeriod | ((uint32_t)pConfig->IncrementStep << RCC_PLL2SSCGR_INCSTEP_Pos) | \
              pConfig->SpreadMode | pConfig->DitheringTPDFN | pConfig->DitheringRPDFN));
}

/**
  * @brief  Configure Spread Spectrum used for PLL3
  * @note These bits must be written before enabling PLL3
  * @rmtoll PLL3SSCGR    MODPER        LL_RCC_PLL3_ConfigSpreadSpectrum\n
  *         PLL3SSCGR    INCSTEP       LL_RCC_PLL3_ConfigSpreadSpectrum\n
  *         PLL3SSCGR    SPREADSEL     LL_RCC_PLL3_ConfigSpreadSpectrum\n
  *         PLL3SSCGR    TPDFNDIS      LL_RCC_PLL3_ConfigSpreadSpectrum\n
  *         PLL3SSCGR    RPDFNDIS      LL_RCC_PLL3_ConfigSpreadSpectrum
  * @param  pConfig Pointer to LL_PLL_SpreadSpectrumTypeDef structure
  * @retval None
  */
void LL_RCC_PLL3_ConfigSpreadSpectrum(const LL_PLL_SpreadSpectrumTypeDef *pConfig)
{
  MODIFY_REG(RCC->PLL3SSCGR, \
             (RCC_PLL3SSCGR_MODPER | RCC_PLL3SSCGR_INCSTEP | RCC_PLL3SSCGR_SPREADSEL | \
              RCC_PLL3SSCGR_TPDFNDIS | RCC_PLL3SSCGR_RPDFNDIS), \
             (pConfig->ModulationPeriod | ((uint32_t)pConfig->IncrementStep << RCC_PLL3SSCGR_INCSTEP_Pos) | \
              pConfig->SpreadMode | pConfig->DitheringTPDFN | pConfig->DitheringRPDFN));
}


/**
  * @brief  Return USARTx clock frequency
  * @param  USARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART1_CLKSOURCE
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE
  * @retval USART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetUSARTClockFreq(uint32_t USARTxSource)
{
  uint32_t usart_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_USART_CLKSOURCE(USARTxSource));

  switch (LL_RCC_GetUSARTClockSource(USARTxSource))
  {
    case LL_RCC_USART1_CLKSOURCE_PCLK2:
      usart_frequency = RCC_GetPCLK2ClockFreq(RCC_GetHCLKClockFreq(LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler())));
      break;

    case LL_RCC_USART234578_CLKSOURCE_PCLK1:
      usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler())));
      break;

    case LL_RCC_USART1_CLKSOURCE_PLL2Q:
    case LL_RCC_USART234578_CLKSOURCE_PLL2Q:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        usart_frequency = PLL_Clocks.PLL_Q_Frequency;
      }
      break;

    case LL_RCC_USART1_CLKSOURCE_PLL3Q:
    case LL_RCC_USART234578_CLKSOURCE_PLL3Q:
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
        usart_frequency = PLL_Clocks.PLL_Q_Frequency;
      }
      break;

    case LL_RCC_USART1_CLKSOURCE_HSI:
    case LL_RCC_USART234578_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        if (LL_RCC_HSI_IsDividerReady() != 0U)
        {
          usart_frequency = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
        }
      }
      break;

    case LL_RCC_USART1_CLKSOURCE_CSI:
    case LL_RCC_USART234578_CLKSOURCE_CSI:
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        usart_frequency = CSI_VALUE;
      }
      break;

    case LL_RCC_USART1_CLKSOURCE_LSE:
    case LL_RCC_USART234578_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        usart_frequency = LSE_VALUE;
      }
      break;

    default:
      /* Kernel clock disabled */
      break;
  }

  return usart_frequency;
}

/**
  * @brief  Return UARTx clock frequency
  * @param  UARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USART234578_CLKSOURCE
  * @retval USART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetUARTClockFreq(uint32_t UARTxSource)
{
  uint32_t uart_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_USART_CLKSOURCE(UARTxSource));

  switch (LL_RCC_GetUSARTClockSource(UARTxSource))
  {
    case LL_RCC_USART234578_CLKSOURCE_PCLK1:
      uart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler())));
      break;

    case LL_RCC_USART234578_CLKSOURCE_PLL2Q:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        uart_frequency = PLL_Clocks.PLL_Q_Frequency;
      }
      break;

    case LL_RCC_USART234578_CLKSOURCE_PLL3Q:
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
        uart_frequency = PLL_Clocks.PLL_Q_Frequency;
      }
      break;

    case LL_RCC_USART234578_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        if (LL_RCC_HSI_IsDividerReady() != 0U)
        {
          uart_frequency = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
        }
      }
      break;

    case LL_RCC_USART234578_CLKSOURCE_CSI:
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        uart_frequency = CSI_VALUE;
      }
      break;

    case LL_RCC_USART234578_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        uart_frequency = LSE_VALUE;
      }
      break;

    default:
      /* Kernel clock disabled */
      break;
  }

  return uart_frequency;
}

/**
  * @brief  Return LPUART clock frequency
  * @param  LPUARTxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPUART1_CLKSOURCE
  * @retval LPUART clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetLPUARTClockFreq(uint32_t LPUARTxSource)
{
  uint32_t lpuart_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_LPUART_CLKSOURCE(LPUARTxSource));

  switch (LL_RCC_GetLPUARTClockSource(LPUARTxSource))
  {
    case LL_RCC_LPUART1_CLKSOURCE_PCLK4:
      lpuart_frequency = RCC_GetPCLK4ClockFreq(RCC_GetHCLKClockFreq(LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler())));
      break;

    case LL_RCC_LPUART1_CLKSOURCE_PLL2Q:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        lpuart_frequency = PLL_Clocks.PLL_Q_Frequency;
      }
      break;

    case LL_RCC_LPUART1_CLKSOURCE_PLL3Q:
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
        lpuart_frequency = PLL_Clocks.PLL_Q_Frequency;
      }
      break;

    case LL_RCC_LPUART1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        if (LL_RCC_HSI_IsDividerReady() != 0U)
        {
          lpuart_frequency = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
        }
      }
      break;

    case LL_RCC_LPUART1_CLKSOURCE_CSI:
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        lpuart_frequency = CSI_VALUE;
      }
      break;

    case LL_RCC_LPUART1_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        lpuart_frequency = LSE_VALUE;
      }
      break;

    default:
      /* Kernel clock disabled */
      break;
  }

  return lpuart_frequency;
}

/**
  * @brief  Return I2Cx clock frequency
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I2C1_CLKSOURCE
  *         @arg @ref LL_RCC_I2C23_CLKSOURCE
  * @retval I2C clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetI2CClockFreq(uint32_t I2CxSource)
{
  uint32_t i2c_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_I2C_CLKSOURCE(I2CxSource));

  switch (LL_RCC_GetI2CClockSource(I2CxSource))
  {
    case LL_RCC_I2C1_CLKSOURCE_PCLK1:
    case LL_RCC_I2C23_CLKSOURCE_PCLK1:
      i2c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler())));
      break;

    case LL_RCC_I2C1_CLKSOURCE_PLL3R:
    case LL_RCC_I2C23_CLKSOURCE_PLL3R:
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
        i2c_frequency = PLL_Clocks.PLL_R_Frequency;
      }
      break;

    case LL_RCC_I2C1_CLKSOURCE_HSI:
    case LL_RCC_I2C23_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        if (LL_RCC_HSI_IsDividerReady() != 0U)
        {
          i2c_frequency = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
        }
      }
      break;

    case LL_RCC_I2C1_CLKSOURCE_CSI:
    case LL_RCC_I2C23_CLKSOURCE_CSI:
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        i2c_frequency = CSI_VALUE;
      }
      break;

    default:
      /* Nothing to do */
      break;
  }

  return i2c_frequency;
}

/**
  * @brief  Return I3Cx clock frequency
  * @param  I3CxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_I3C1_CLKSOURCE
  * @retval I3C clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetI3CClockFreq(uint32_t I3CxSource)
{
  uint32_t i3c_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_I3C_CLKSOURCE(I3CxSource));

  switch (LL_RCC_GetI3CClockSource(I3CxSource))
  {
    case LL_RCC_I3C1_CLKSOURCE_PCLK1:
      i3c_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler())));
      break;

    case LL_RCC_I3C1_CLKSOURCE_PLL3R:
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
        i3c_frequency = PLL_Clocks.PLL_R_Frequency;
      }
      break;

    case LL_RCC_I3C1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        if (LL_RCC_HSI_IsDividerReady() != 0U)
        {
          i3c_frequency = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
        }
      }
      break;

    case LL_RCC_I3C1_CLKSOURCE_CSI:
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        i3c_frequency = CSI_VALUE;
      }
      break;

    default:
      /* Nothing to do */
      break;
  }

  return i3c_frequency;
}

/**
  * @brief  Return LPTIMx clock frequency
  * @param  LPTIMxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_LPTIM1_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM23_CLKSOURCE
  *         @arg @ref LL_RCC_LPTIM45_CLKSOURCE
  * @retval LPTIM clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetLPTIMClockFreq(uint32_t LPTIMxSource)
{
  uint32_t lptim_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_LPTIM_CLKSOURCE(LPTIMxSource));

  switch (LL_RCC_GetLPTIMClockSource(LPTIMxSource))
  {
    case LL_RCC_LPTIM1_CLKSOURCE_PCLK1:
      lptim_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler())));
      break;

    case LL_RCC_LPTIM23_CLKSOURCE_PCLK4:
    case LL_RCC_LPTIM45_CLKSOURCE_PCLK4:
      lptim_frequency = RCC_GetPCLK4ClockFreq(RCC_GetHCLKClockFreq(LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler())));
      break;

    case LL_RCC_LPTIM1_CLKSOURCE_PLL2P:
    case LL_RCC_LPTIM23_CLKSOURCE_PLL2P:
    case LL_RCC_LPTIM45_CLKSOURCE_PLL2P:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        lptim_frequency = PLL_Clocks.PLL_P_Frequency;
      }
      break;

    case LL_RCC_LPTIM1_CLKSOURCE_PLL3R:
    case LL_RCC_LPTIM23_CLKSOURCE_PLL3R:
    case LL_RCC_LPTIM45_CLKSOURCE_PLL3R:
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
        lptim_frequency = PLL_Clocks.PLL_R_Frequency;
      }
      break;

    case LL_RCC_LPTIM1_CLKSOURCE_LSE:
    case LL_RCC_LPTIM23_CLKSOURCE_LSE:
    case LL_RCC_LPTIM45_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        lptim_frequency = LSE_VALUE;
      }
      break;

    case LL_RCC_LPTIM1_CLKSOURCE_LSI:
    case LL_RCC_LPTIM23_CLKSOURCE_LSI:
    case LL_RCC_LPTIM45_CLKSOURCE_LSI:
      if (LL_RCC_LSI_IsReady() != 0U)
      {
        lptim_frequency = LSI_VALUE;
      }
      break;

    case LL_RCC_LPTIM1_CLKSOURCE_CLKP:
    case LL_RCC_LPTIM23_CLKSOURCE_CLKP:
    case LL_RCC_LPTIM45_CLKSOURCE_CLKP:
      lptim_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_CLKP_CLKSOURCE);
      break;

    default:
      /* Kernel clock disabled */
      break;
  }

  return lptim_frequency;
}

/**
  * @brief  Return SAIx clock frequency
  * @param  SAIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SAI1_CLKSOURCE
  *         @arg @ref LL_RCC_SAI2_CLKSOURCE
  * @retval SAI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetSAIClockFreq(uint32_t SAIxSource)
{
  uint32_t sai_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_SAI_CLKSOURCE(SAIxSource));

  switch (LL_RCC_GetSAIClockSource(SAIxSource))
  {
    case LL_RCC_SAI1_CLKSOURCE_PLL1Q:
    case LL_RCC_SAI2_CLKSOURCE_PLL1Q:
      if (LL_RCC_PLL1_IsReady() != 0U)
      {
        LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
        sai_frequency = PLL_Clocks.PLL_Q_Frequency;
      }
      break;

    case LL_RCC_SAI1_CLKSOURCE_PLL2P:
    case LL_RCC_SAI2_CLKSOURCE_PLL2P:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        sai_frequency = PLL_Clocks.PLL_P_Frequency;
      }
      break;

    case LL_RCC_SAI1_CLKSOURCE_PLL3P:
    case LL_RCC_SAI2_CLKSOURCE_PLL3P:
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
        sai_frequency = PLL_Clocks.PLL_P_Frequency;
      }
      break;

    case LL_RCC_SAI1_CLKSOURCE_I2S_CKIN:
    case LL_RCC_SAI2_CLKSOURCE_I2S_CKIN:
      sai_frequency = EXTERNAL_CLOCK_VALUE;
      break;

    case LL_RCC_SAI1_CLKSOURCE_CLKP:
    case LL_RCC_SAI2_CLKSOURCE_CLKP:
      sai_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_CLKP_CLKSOURCE);
      break;

    default:
      /* Kernel clock disabled */
      break;
  }

  return sai_frequency;
}

/**
  * @brief  Return ADC clock frequency
  * @param  ADCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADC_CLKSOURCE
  * @retval ADC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetADCClockFreq(uint32_t ADCxSource)
{
  uint32_t adc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_ADC_CLKSOURCE(ADCxSource));

  switch (LL_RCC_GetADCClockSource(ADCxSource))
  {
    case LL_RCC_ADC_CLKSOURCE_PLL2P:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        adc_frequency = PLL_Clocks.PLL_P_Frequency;
      }
      break;

    case LL_RCC_ADC_CLKSOURCE_PLL3R:
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
        adc_frequency = PLL_Clocks.PLL_R_Frequency;
      }
      break;

    case LL_RCC_ADC_CLKSOURCE_CLKP:
      adc_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_CLKP_CLKSOURCE);
      break;

    default:
      /* Kernel clock disabled */
      break;
  }

  return adc_frequency;
}

/**
  * @brief  Return SDMMC clock frequency
  * @param  SDMMCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SDMMC_CLKSOURCE
  * @retval SDMMC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetSDMMCClockFreq(uint32_t SDMMCxSource)
{
  uint32_t sdmmc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_SDMMC_CLKSOURCE(SDMMCxSource));

  switch (LL_RCC_GetSDMMCClockSource(SDMMCxSource))
  {
    case LL_RCC_SDMMC_CLKSOURCE_PLL2S:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        sdmmc_frequency = PLL_Clocks.PLL_S_Frequency;
      }
      break;

    case LL_RCC_SDMMC_CLKSOURCE_PLL2T:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        sdmmc_frequency = PLL_Clocks.PLL_T_Frequency;
      }
      break;

    default:
      /* Nothing to do */
      break;
  }

  return sdmmc_frequency;
}

/**
  * @brief  Return CEC clock frequency
  * @param  CECxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_CEC_CLKSOURCE
  * @retval CEC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetCECClockFreq(uint32_t CECxSource)
{
  uint32_t cec_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_CEC_CLKSOURCE(CECxSource));

  switch (LL_RCC_GetCECClockSource(CECxSource))
  {
    case LL_RCC_CEC_CLKSOURCE_LSE:
      if (LL_RCC_LSE_IsReady() != 0U)
      {
        cec_frequency = LSE_VALUE;
      }
      break;

    case LL_RCC_CEC_CLKSOURCE_LSI:
      if (LL_RCC_LSI_IsReady() != 0U)
      {
        cec_frequency = LSI_VALUE;
      }
      break;

    case LL_RCC_CEC_CLKSOURCE_CSI_DIV_122:
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        cec_frequency = CSI_VALUE / 122U;
      }
      break;

    default:
      /* Kernel clock disabled */
      break;
  }

  return cec_frequency;
}

/**
  * @brief  Return PSSI clock frequency
  * @param  PSSIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_PSSI_CLKSOURCE
  * @retval PSSI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetPSSIClockFreq(uint32_t PSSIxSource)
{
  uint32_t pssi_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef pll_clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_PSSI_CLKSOURCE(PSSIxSource));

  switch (LL_RCC_GetPSSIClockSource(PSSIxSource))
  {
    case LL_RCC_PSSI_CLKSOURCE_PLL3R:
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        LL_RCC_GetPLL3ClockFreq(&pll_clocks);
        pssi_frequency = pll_clocks.PLL_R_Frequency;
      }
      break;

    case LL_RCC_PSSI_CLKSOURCE_CLKP:
      pssi_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_CLKP_CLKSOURCE);
      break;

    default:
      /* Nothing to do */
      break;
  }

  return pssi_frequency;
}


/**
  * @brief  Return USBPHYC clock frequency
  * @param  USBPHYCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_USBPHYC_CLKSOURCE
  * @retval USBPHYC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready or Disabled
  */
uint32_t LL_RCC_GetUSBPHYCClockFreq(uint32_t USBPHYCxSource)
{
  uint32_t usb_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_USBPHYC_CLKSOURCE(USBPHYCxSource));

  switch (LL_RCC_GetUSBPHYCClockSource(USBPHYCxSource))
  {
    case LL_RCC_USBPHYC_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        usb_frequency = HSE_VALUE;
      }
      break;

    case LL_RCC_USBPHYC_CLKSOURCE_HSE_DIV_2:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        usb_frequency = (HSE_VALUE / 2U);
      }
      break;

    case LL_RCC_USBPHYC_CLKSOURCE_PLL3Q:
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
        usb_frequency = PLL_Clocks.PLL_Q_Frequency;
      }
      break;

    case LL_RCC_USBPHYC_CLKSOURCE_DISABLE:
    default:
      /* Nothing to do */
      break;
  }

  return usb_frequency;
}

/**
  * @brief  Return ADF clock frequency
  * @param  ADFxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ADF1_CLKSOURCE
  * @retval ADF clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetADFClockFreq(uint32_t ADFxSource)
{
  uint32_t adf_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_ADF1_CLKSOURCE(ADFxSource));

  switch (LL_RCC_GetADFClockSource(ADFxSource))
  {
    case LL_RCC_ADF1_CLKSOURCE_HCLK:
      adf_frequency = RCC_GetHCLKClockFreq(LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler()));
      break;

    case LL_RCC_ADF1_CLKSOURCE_PLL2P:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        adf_frequency = PLL_Clocks.PLL_P_Frequency;
      }
      break;

    case LL_RCC_ADF1_CLKSOURCE_PLL3P:
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
        adf_frequency = PLL_Clocks.PLL_P_Frequency;
      }
      break;

    case LL_RCC_ADF1_CLKSOURCE_I2S_CKIN:
      adf_frequency = EXTERNAL_CLOCK_VALUE;
      break;

    case LL_RCC_ADF1_CLKSOURCE_CSI:
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        adf_frequency = CSI_VALUE;
      }
      break;

    case LL_RCC_ADF1_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        if (LL_RCC_HSI_IsDividerReady() != 0U)
        {
          adf_frequency = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
        }
      }
      break;

    default:
      /* Nothing to do */
      break;
  }

  return adf_frequency;
}

/**
  * @brief  Return SPDIFRX clock frequency
  * @param  SPDIFRXxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPDIFRX_CLKSOURCE
  * @retval SPDIF clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetSPDIFRXClockFreq(uint32_t SPDIFRXxSource)
{
  uint32_t spdif_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_SPDIFRX_CLKSOURCE(SPDIFRXxSource));

  switch (LL_RCC_GetSPDIFRXClockSource(SPDIFRXxSource))
  {
    case LL_RCC_SPDIFRX_CLKSOURCE_PLL1Q:
      if (LL_RCC_PLL1_IsReady() != 0U)
      {
        LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
        spdif_frequency = PLL_Clocks.PLL_Q_Frequency;
      }
      break;

    case LL_RCC_SPDIFRX_CLKSOURCE_PLL2R:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        spdif_frequency = PLL_Clocks.PLL_R_Frequency;
      }
      break;

    case LL_RCC_SPDIFRX_CLKSOURCE_PLL3R:
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
        spdif_frequency = PLL_Clocks.PLL_R_Frequency;
      }
      break;

    case LL_RCC_SPDIFRX_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        if (LL_RCC_HSI_IsDividerReady() != 0U)
        {
          spdif_frequency = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
        }
      }
      break;

    default:
      /* Nothing to do */
      break;
  }

  return spdif_frequency;
}

/**
  * @brief  Return SPIx clock frequency
  * @param  SPIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_SPI1_CLKSOURCE
  *         @arg @ref LL_RCC_SPI23_CLKSOURCE
  *         @arg @ref LL_RCC_SPI45_CLKSOURCE
  *         @arg @ref LL_RCC_SPI6_CLKSOURCE
  * @retval SPI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetSPIClockFreq(uint32_t SPIxSource)
{
  uint32_t spi_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_SPI_CLKSOURCE(SPIxSource));

  switch (LL_RCC_GetSPIClockSource(SPIxSource))
  {
    case LL_RCC_SPI1_CLKSOURCE_PLL1Q:
    case LL_RCC_SPI23_CLKSOURCE_PLL1Q:
      if (LL_RCC_PLL1_IsReady() != 0U)
      {
        LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
        spi_frequency = PLL_Clocks.PLL_Q_Frequency;
      }
      break;

    case LL_RCC_SPI1_CLKSOURCE_PLL2P:
    case LL_RCC_SPI23_CLKSOURCE_PLL2P:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        spi_frequency = PLL_Clocks.PLL_P_Frequency;
      }
      break;

    case LL_RCC_SPI1_CLKSOURCE_PLL3P:
    case LL_RCC_SPI23_CLKSOURCE_PLL3P:
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
        spi_frequency = PLL_Clocks.PLL_P_Frequency;
      }
      break;

    case LL_RCC_SPI1_CLKSOURCE_I2S_CKIN:
    case LL_RCC_SPI23_CLKSOURCE_I2S_CKIN:
      spi_frequency = EXTERNAL_CLOCK_VALUE;
      break;

    case LL_RCC_SPI1_CLKSOURCE_CLKP:
    case LL_RCC_SPI23_CLKSOURCE_CLKP:
      spi_frequency = LL_RCC_GetCLKPClockFreq(LL_RCC_CLKP_CLKSOURCE);
      break;

    case LL_RCC_SPI45_CLKSOURCE_PCLK2:
      spi_frequency = RCC_GetPCLK2ClockFreq(RCC_GetHCLKClockFreq(LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler())));
      break;

    case LL_RCC_SPI6_CLKSOURCE_PCLK4:
      spi_frequency = RCC_GetPCLK4ClockFreq(RCC_GetHCLKClockFreq(LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler())));
      break;

    case LL_RCC_SPI45_CLKSOURCE_PLL2Q:
    case LL_RCC_SPI6_CLKSOURCE_PLL2Q:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        spi_frequency = PLL_Clocks.PLL_Q_Frequency;
      }
      break;

    case LL_RCC_SPI45_CLKSOURCE_PLL3Q:
    case LL_RCC_SPI6_CLKSOURCE_PLL3Q:
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
        spi_frequency = PLL_Clocks.PLL_Q_Frequency;
      }
      break;

    case LL_RCC_SPI45_CLKSOURCE_HSI:
    case LL_RCC_SPI6_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        if (LL_RCC_HSI_IsDividerReady() != 0U)
        {
          spi_frequency = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
        }
      }
      break;

    case LL_RCC_SPI45_CLKSOURCE_CSI:
    case LL_RCC_SPI6_CLKSOURCE_CSI:
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        spi_frequency = CSI_VALUE;
      }
      break;

    case LL_RCC_SPI45_CLKSOURCE_HSE:
    case LL_RCC_SPI6_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        spi_frequency = HSE_VALUE;
      }
      break;

    default:
      /* Kernel clock disabled */
      break;
  }

  return spi_frequency;
}

/**
  * @brief  Return ETH clock frequency
  * @param  ETHxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_ETH1PHY_CLKSOURCE
  * @retval ETH clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready or Disabled
  */
uint32_t LL_RCC_GetETHPHYClockFreq(uint32_t ETHxSource)
{
  uint32_t eth_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_ETH1PHY_CLKSOURCE(ETHxSource));

  switch (LL_RCC_GetETHPHYClockSource(ETHxSource))
  {
    case LL_RCC_ETH1PHY_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        eth_frequency = HSE_VALUE;
      }
      break;

    case LL_RCC_ETH1PHY_CLKSOURCE_PLL3S:
      if (LL_RCC_PLL3_IsReady() != 0U)
      {
        LL_RCC_GetPLL3ClockFreq(&PLL_Clocks);
        eth_frequency = PLL_Clocks.PLL_S_Frequency;
      }
      break;

    default:
      /* Nothing to do */
      break;
  }

  return eth_frequency;
}


/**
  * @brief  Return FDCAN clock frequency
  * @param  FDCANxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FDCAN_CLKSOURCE
  * @retval FDCAN clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetFDCANClockFreq(uint32_t FDCANxSource)
{
  uint32_t fdcan_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_FDCAN_CLKSOURCE(FDCANxSource));

  switch (LL_RCC_GetFDCANClockSource(FDCANxSource))
  {
    case LL_RCC_FDCAN_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        fdcan_frequency = HSE_VALUE;
      }
      break;

    case LL_RCC_FDCAN_CLKSOURCE_PLL1Q:
      if (LL_RCC_PLL1_IsReady() != 0U)
      {
        LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
        fdcan_frequency = PLL_Clocks.PLL_Q_Frequency;
      }
      break;

    case LL_RCC_FDCAN_CLKSOURCE_PLL2Q:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        fdcan_frequency = PLL_Clocks.PLL_Q_Frequency;
      }
      break;

    default:
      /* Kernel clock disabled */
      break;
  }

  return fdcan_frequency;
}

/**
  * @brief  Return FMC clock frequency
  * @param  FMCxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_FMC_CLKSOURCE
  * @retval FMC clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetFMCClockFreq(uint32_t FMCxSource)
{
  uint32_t fmc_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  uint32_t clksource;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_FMC_CLKSOURCE(FMCxSource));

  if (LL_RCC_GetFMCSwitchPosition() == LL_RCC_SWP_FMC_HCLK_DIV4)
  {
    clksource = LL_RCC_FMC_CLKSOURCE_HCLK_DIV4;
  }
  else
  {
    clksource = LL_RCC_GetFMCClockSource(FMCxSource);
  }

  switch (clksource)
  {
    case LL_RCC_FMC_CLKSOURCE_HCLK:
      fmc_frequency = RCC_GetHCLKClockFreq(LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler()));
      break;

    case LL_RCC_FMC_CLKSOURCE_PLL1Q:
      if (LL_RCC_PLL1_IsReady() != 0U)
      {
        LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
        fmc_frequency = PLL_Clocks.PLL_Q_Frequency;
      }
      break;

    case LL_RCC_FMC_CLKSOURCE_PLL2R:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        fmc_frequency = PLL_Clocks.PLL_R_Frequency;
      }
      break;

    case LL_RCC_FMC_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        if (LL_RCC_HSI_IsDividerReady() != 0U)
        {
          fmc_frequency = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
        }
      }
      break;

    case LL_RCC_FMC_CLKSOURCE_HCLK_DIV4:
      fmc_frequency = (RCC_GetHCLKClockFreq(LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler())) / 4U);
      break;

    default:
      /* Nothing to do */
      break;
  }

  return fmc_frequency;
}

/**
  * @brief  Return XSPI clock frequency
  * @param  XSPIxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_XSPI1_CLKSOURCE
  *         @arg @ref LL_RCC_XSPI2_CLKSOURCE
  * @retval XSPI clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */

uint32_t LL_RCC_GetXSPIClockFreq(uint32_t XSPIxSource)
{
  uint32_t xspi_frequency = LL_RCC_PERIPH_FREQUENCY_NO;
  uint32_t clksource;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Check parameter */
  assert_param(IS_LL_RCC_XSPI_CLKSOURCE(XSPIxSource));

  clksource = LL_RCC_GetXSPIClockSource(XSPIxSource);

  /* Update clock source depending on the XSPI clock switch position */
  switch (XSPIxSource)
  {
    case LL_RCC_XSPI1_CLKSOURCE:
      if (LL_RCC_GetXSPI1SwitchPosition() == LL_RCC_SWP_XSPI1_HCLK_DIV4)
      {
        clksource = LL_RCC_XSPI1_CLKSOURCE_HCLK_DIV4;
      }
      break;
    case LL_RCC_XSPI2_CLKSOURCE:
      if (LL_RCC_GetXSPI2SwitchPosition() == LL_RCC_SWP_XSPI2_HCLK_DIV4)
      {
        clksource = LL_RCC_XSPI2_CLKSOURCE_HCLK_DIV4;
      }
      break;
    default:
      /* Do nothing */
      break;
  }

  switch (clksource)
  {
    case LL_RCC_XSPI1_CLKSOURCE_HCLK:
    case LL_RCC_XSPI2_CLKSOURCE_HCLK:
      xspi_frequency = RCC_GetHCLKClockFreq(LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler()));
      break;

    case LL_RCC_XSPI1_CLKSOURCE_PLL2S:
    case LL_RCC_XSPI2_CLKSOURCE_PLL2S:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        xspi_frequency = PLL_Clocks.PLL_S_Frequency;
      }
      break;

    case LL_RCC_XSPI1_CLKSOURCE_PLL2T:
    case LL_RCC_XSPI2_CLKSOURCE_PLL2T:
      if (LL_RCC_PLL2_IsReady() != 0U)
      {
        LL_RCC_GetPLL2ClockFreq(&PLL_Clocks);
        xspi_frequency = PLL_Clocks.PLL_T_Frequency;
      }
      break;

    case LL_RCC_XSPI1_CLKSOURCE_HCLK_DIV4:
    case LL_RCC_XSPI2_CLKSOURCE_HCLK_DIV4:
      xspi_frequency = (RCC_GetHCLKClockFreq(LL_RCC_CALC_SYSCLK_FREQ(RCC_GetSystemClockFreq(), LL_RCC_GetSysPrescaler())) / 4U);
      break;

    default:
      /* Nothing to do */
      break;
  }

  return xspi_frequency;
}

/**
  * @brief  Return CLKP clock frequency
  * @param  CLKPxSource This parameter can be one of the following values:
  *         @arg @ref LL_RCC_CLKP_CLKSOURCE
  * @retval CLKP clock frequency (in Hz)
  *         - @ref  LL_RCC_PERIPH_FREQUENCY_NO indicates that oscillator is not ready
  */
uint32_t LL_RCC_GetCLKPClockFreq(uint32_t CLKPxSource)
{
  uint32_t clkp_frequency = LL_RCC_PERIPH_FREQUENCY_NO;

  /* Check parameter */
  assert_param(IS_LL_RCC_CLKP_CLKSOURCE(CLKPxSource));

  switch (LL_RCC_GetCLKPClockSource(CLKPxSource))
  {
    case LL_RCC_CLKP_CLKSOURCE_HSI:
      if (LL_RCC_HSI_IsReady() != 0U)
      {
        if (LL_RCC_HSI_IsDividerReady() != 0U)
        {
          clkp_frequency = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
        }
      }
      break;

    case LL_RCC_CLKP_CLKSOURCE_CSI:
      if (LL_RCC_CSI_IsReady() != 0U)
      {
        clkp_frequency = CSI_VALUE;
      }
      break;

    case LL_RCC_CLKP_CLKSOURCE_HSE:
      if (LL_RCC_HSE_IsReady() != 0U)
      {
        clkp_frequency = HSE_VALUE;
      }
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
static uint32_t RCC_GetSystemClockFreq(void)
{
  uint32_t frequency = 0U;
  LL_PLL_ClocksTypeDef PLL_Clocks;

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (LL_RCC_GetSysClkSource())
  {
    /* No check on Ready: Won't be selected by hardware if not */
    case LL_RCC_SYS_CLKSOURCE_STATUS_HSI:
      frequency = HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos);
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_CSI:
      frequency = CSI_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_HSE:
      frequency = HSE_VALUE;
      break;

    case LL_RCC_SYS_CLKSOURCE_STATUS_PLL1:
      LL_RCC_GetPLL1ClockFreq(&PLL_Clocks);
      frequency = PLL_Clocks.PLL_P_Frequency;
      break;

    default:
      /* Nothing to do */
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
  return LL_RCC_CALC_HCLK_FREQ(SYSCLK_Frequency, LL_RCC_GetAHBPrescaler());
}

/**
  * @brief  Return PCLK1 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK1 clock frequency (in Hz)
  */
static uint32_t RCC_GetPCLK1ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK1 clock frequency */
  return LL_RCC_CALC_PCLK1_FREQ(HCLK_Frequency, LL_RCC_GetAPB1Prescaler());
}

/**
  * @brief  Return PCLK2 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK2 clock frequency (in Hz)
  */
static uint32_t RCC_GetPCLK2ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK2 clock frequency */
  return LL_RCC_CALC_PCLK2_FREQ(HCLK_Frequency, LL_RCC_GetAPB2Prescaler());
}

/**
  * @brief  Return PCLK4 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK4 clock frequency (in Hz)
  */
static uint32_t RCC_GetPCLK4ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK4 clock frequency */
  return LL_RCC_CALC_PCLK4_FREQ(HCLK_Frequency, LL_RCC_GetAPB4Prescaler());
}

/**
  * @brief  Return PCLK5 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK5 clock frequency (in Hz)
  */
static uint32_t RCC_GetPCLK5ClockFreq(uint32_t HCLK_Frequency)
{
  /* PCLK5 clock frequency */
  return LL_RCC_CALC_PCLK5_FREQ(HCLK_Frequency, LL_RCC_GetAPB5Prescaler());
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
