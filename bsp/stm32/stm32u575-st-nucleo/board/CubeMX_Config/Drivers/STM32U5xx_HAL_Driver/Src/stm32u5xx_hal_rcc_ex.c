/**
  ******************************************************************************
  * @file    stm32u5xx_hal_rcc_ex.c
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
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
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
#define PLL1_TIMEOUT_VALUE     2UL    /* 2 ms (minimum Tick + 1) */
#define PLL2_TIMEOUT_VALUE     2UL    /* 2 ms (minimum Tick + 1) */
#define PLL3_TIMEOUT_VALUE     2UL    /* 2 ms (minimum Tick + 1) */

#define LSCO_CLK_ENABLE()    __HAL_RCC_GPIOA_CLK_ENABLE()

#define LSCO_GPIO_PORT         GPIOA

#define LSCO_PIN               GPIO_PIN_2

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup RCCEx_Private_Macros
  * @{
  */

#define IS_RCC_PLL2CLOCKOUT_VALUE(VALUE) ((0x00010000U <= (VALUE)) && ((VALUE) <= 0x00070000U))

#define IS_RCC_PLL3CLOCKOUT_VALUE(VALUE) ((0x00010000U <= (VALUE)) && ((VALUE) <= 0x00070000U))

#define IS_RCC_LSCOSOURCE(__SOURCE__) (((__SOURCE__) == RCC_LSCOSOURCE_LSI) || \
                                       ((__SOURCE__) == RCC_LSCOSOURCE_LSE))

#define IS_RCC_MSIPLLMODE_SELECT(__SOURCE__) (((__SOURCE__) == RCC_MSISPLL_MODE_SEL) || \
                                              ((__SOURCE__) == RCC_MSIKPLL_MODE_SEL))

#define IS_RCC_PERIPHCLOCK(__SELECTION__)   ((((__SELECTION__) & RCC_PERIPHCLOCK_ALL) != 0x00u) && \
                                             (((__SELECTION__) & ~RCC_PERIPHCLOCK_ALL) == 0x00u))

#define IS_RCC_USART1CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_USART1CLKSOURCE_PCLK2) || \
   ((__SOURCE__) == RCC_USART1CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_USART1CLKSOURCE_HSI) || \
   ((__SOURCE__) == RCC_USART1CLKSOURCE_LSE))

#define IS_RCC_USART2CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_USART2CLKSOURCE_PCLK1) || \
   ((__SOURCE__) == RCC_USART2CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_USART2CLKSOURCE_HSI) || \
   ((__SOURCE__) == RCC_USART2CLKSOURCE_LSE))

#define IS_RCC_USART3CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_USART3CLKSOURCE_PCLK1) || \
   ((__SOURCE__) == RCC_USART3CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_USART3CLKSOURCE_HSI) || \
   ((__SOURCE__) == RCC_USART3CLKSOURCE_LSE))

#define IS_RCC_UART4CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_UART4CLKSOURCE_PCLK1) || \
   ((__SOURCE__) == RCC_UART4CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_UART4CLKSOURCE_HSI) || \
   ((__SOURCE__) == RCC_UART4CLKSOURCE_LSE))

#define IS_RCC_UART5CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_UART5CLKSOURCE_PCLK1) || \
   ((__SOURCE__) == RCC_UART5CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_UART5CLKSOURCE_HSI) || \
   ((__SOURCE__) == RCC_UART5CLKSOURCE_LSE))

#define IS_RCC_LPUART1CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_LPUART1CLKSOURCE_PCLK3) || \
   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_HSI) || \
   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_LSE) || \
   ((__SOURCE__) == RCC_LPUART1CLKSOURCE_MSIK))

#define IS_RCC_I2C1CLKSOURCE(__SOURCE__)   \
  (((__SOURCE__) == RCC_I2C1CLKSOURCE_PCLK1) || \
   ((__SOURCE__) == RCC_I2C1CLKSOURCE_SYSCLK)|| \
   ((__SOURCE__) == RCC_I2C1CLKSOURCE_HSI)|| \
   ((__SOURCE__) == RCC_I2C1CLKSOURCE_MSIK))

#define IS_RCC_I2C2CLKSOURCE(__SOURCE__)   \
  (((__SOURCE__) == RCC_I2C2CLKSOURCE_PCLK1) || \
   ((__SOURCE__) == RCC_I2C2CLKSOURCE_SYSCLK)|| \
   ((__SOURCE__) == RCC_I2C2CLKSOURCE_HSI)|| \
   ((__SOURCE__) == RCC_I2C2CLKSOURCE_MSIK))

#define IS_RCC_I2C3CLKSOURCE(__SOURCE__)   \
  (((__SOURCE__) == RCC_I2C3CLKSOURCE_PCLK3) || \
   ((__SOURCE__) == RCC_I2C3CLKSOURCE_SYSCLK ) || \
   ((__SOURCE__) == RCC_I2C3CLKSOURCE_HSI    ) || \
   ((__SOURCE__) == RCC_I2C3CLKSOURCE_MSIK))

#define IS_RCC_I2C4CLKSOURCE(__SOURCE__)   \
  (((__SOURCE__) == RCC_I2C4CLKSOURCE_PCLK1) || \
   ((__SOURCE__) == RCC_I2C4CLKSOURCE_SYSCLK)|| \
   ((__SOURCE__) == RCC_I2C4CLKSOURCE_HSI)|| \
   ((__SOURCE__) == RCC_I2C4CLKSOURCE_MSIK))

#define IS_RCC_SAI1CLK(__SOURCE__)   \
  (((__SOURCE__) == RCC_SAI1CLKSOURCE_PLL2) || \
   ((__SOURCE__) == RCC_SAI1CLKSOURCE_PLL3) || \
   ((__SOURCE__) == RCC_SAI1CLKSOURCE_PLL1) || \
   ((__SOURCE__) == RCC_SAI1CLKSOURCE_PIN)  || \
   ((__SOURCE__) == RCC_SAI1CLKSOURCE_HSI))

#define IS_RCC_SAI2CLK(__SOURCE__)   \
  (((__SOURCE__) == RCC_SAI2CLKSOURCE_PLL2) || \
   ((__SOURCE__) == RCC_SAI2CLKSOURCE_PLL3) || \
   ((__SOURCE__) == RCC_SAI2CLKSOURCE_PLL1) || \
   ((__SOURCE__) == RCC_SAI2CLKSOURCE_PIN) || \
   ((__SOURCE__) == RCC_SAI2CLKSOURCE_HSI))

#define IS_RCC_LPTIM1CLK(__SOURCE__)  \
  (((__SOURCE__) == RCC_LPTIM1CLKSOURCE_MSIK) || \
   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSI) || \
   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_HSI) || \
   ((__SOURCE__) == RCC_LPTIM1CLKSOURCE_LSE))

#define IS_RCC_LPTIM2CLK(__SOURCE__)  \
  (((__SOURCE__) == RCC_LPTIM2CLKSOURCE_PCLK1) || \
   ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_LSI) || \
   ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_HSI) || \
   ((__SOURCE__) == RCC_LPTIM2CLKSOURCE_LSE))

#define IS_RCC_LPTIM34CLK(__SOURCE__)  \
  (((__SOURCE__) == RCC_LPTIM34CLKSOURCE_MSIK) || \
   ((__SOURCE__) == RCC_LPTIM34CLKSOURCE_LSI) || \
   ((__SOURCE__) == RCC_LPTIM34CLKSOURCE_HSI) || \
   ((__SOURCE__) == RCC_LPTIM34CLKSOURCE_LSE))

#define IS_RCC_FDCAN1CLK(__SOURCE__)  \
  (((__SOURCE__) == RCC_FDCAN1CLKSOURCE_HSE) || \
   ((__SOURCE__) == RCC_FDCAN1CLKSOURCE_PLL1) || \
   ((__SOURCE__) == RCC_FDCAN1CLKSOURCE_PLL2))

#define IS_RCC_SDMMCCLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_SDMMCCLKSOURCE_CLK48) || \
   ((__SOURCE__) == RCC_SDMMCCLKSOURCE_PLL1))

#define IS_RCC_RNGCLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_RNGCLKSOURCE_HSI48)   || \
   ((__SOURCE__) == RCC_RNGCLKSOURCE_HSI48_DIV2)  || \
   ((__SOURCE__) == RCC_RNGCLKSOURCE_HSI))

#define IS_RCC_SAESCLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_SAESCLKSOURCE_SHSI)   || \
   ((__SOURCE__) == RCC_SAESCLKSOURCE_SHSI_DIV2))

#define IS_RCC_ADCDACCLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_ADCDACCLKSOURCE_HCLK)   || \
   ((__SOURCE__) == RCC_ADCDACCLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_ADCDACCLKSOURCE_PLL2)   || \
   ((__SOURCE__) == RCC_ADCDACCLKSOURCE_HSE)     || \
   ((__SOURCE__) == RCC_ADCDACCLKSOURCE_HSI)     || \
   ((__SOURCE__) == RCC_ADCDACCLKSOURCE_MSIK))

#define IS_RCC_MDF1CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_MDF1CLKSOURCE_HCLK) || \
   ((__SOURCE__) == RCC_MDF1CLKSOURCE_PLL1) || \
   ((__SOURCE__) == RCC_MDF1CLKSOURCE_PLL3) || \
   ((__SOURCE__) == RCC_MDF1CLKSOURCE_PIN) || \
   ((__SOURCE__) == RCC_MDF1CLKSOURCE_MSIK))

#define IS_RCC_ADF1CLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_ADF1CLKSOURCE_HCLK) || \
   ((__SOURCE__) == RCC_ADF1CLKSOURCE_PLL1) || \
   ((__SOURCE__) == RCC_ADF1CLKSOURCE_PLL3) || \
   ((__SOURCE__) == RCC_ADF1CLKSOURCE_PIN) || \
   ((__SOURCE__) == RCC_ADF1CLKSOURCE_MSIK))

#define IS_RCC_OSPICLKSOURCE(__SOURCE__)  \
  (((__SOURCE__) == RCC_OSPICLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_OSPICLKSOURCE_MSIK) || \
   ((__SOURCE__) == RCC_OSPICLKSOURCE_PLL1) ||\
   ((__SOURCE__) == RCC_OSPICLKSOURCE_PLL2))

#define IS_RCC_CLK48CLKSOURCE(__SOURCE__)\
  (((__SOURCE__) == RCC_CLK48CLKSOURCE_HSI48)|| \
   ((__SOURCE__) == RCC_CLK48CLKSOURCE_PLL2) || \
   ((__SOURCE__) == RCC_CLK48CLKSOURCE_PLL1) || \
   ((__SOURCE__) == RCC_CLK48CLKSOURCE_MSIK))

#define IS_RCC_SPI1CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SPI1CLKSOURCE_PCLK2) || \
   ((__SOURCE__) == RCC_SPI1CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_SPI1CLKSOURCE_HSI)|| \
   ((__SOURCE__) == RCC_SPI1CLKSOURCE_MSIK))

#define IS_RCC_SPI2CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SPI2CLKSOURCE_PCLK1) || \
   ((__SOURCE__) == RCC_SPI2CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_SPI2CLKSOURCE_HSI)|| \
   ((__SOURCE__) == RCC_SPI2CLKSOURCE_MSIK))

#define IS_RCC_SPI3CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_SPI3CLKSOURCE_PCLK3) || \
   ((__SOURCE__) == RCC_SPI3CLKSOURCE_SYSCLK) || \
   ((__SOURCE__) == RCC_SPI3CLKSOURCE_HSI)|| \
   ((__SOURCE__) == RCC_SPI3CLKSOURCE_MSIK))

#define IS_RCC_DAC1CLKSOURCE(__SOURCE__) \
  (((__SOURCE__) == RCC_DAC1CLKSOURCE_LSE) || \
   ((__SOURCE__) == RCC_DAC1CLKSOURCE_LSI))

#define IS_RCC_RTCCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_RTCCLKSOURCE_NO_CLK) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_LSE)    || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_LSI)    || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV32))
#if defined(CRS)

#define IS_RCC_CRS_SYNC_SOURCE(__SOURCE__) (((__SOURCE__) == RCC_CRS_SYNC_SOURCE_GPIO) || \
                                            ((__SOURCE__) == RCC_CRS_SYNC_SOURCE_LSE) || \
                                            ((__SOURCE__) == RCC_CRS_SYNC_SOURCE_USB))

#define IS_RCC_CRS_SYNC_DIV(__DIV__)       (((__DIV__) == RCC_CRS_SYNC_DIV1) || ((__DIV__) == RCC_CRS_SYNC_DIV2) || \
                                            ((__DIV__) == RCC_CRS_SYNC_DIV4) || ((__DIV__) == RCC_CRS_SYNC_DIV8) || \
                                            ((__DIV__) == RCC_CRS_SYNC_DIV16) || ((__DIV__) == RCC_CRS_SYNC_DIV32) || \
                                            ((__DIV__) == RCC_CRS_SYNC_DIV64) || ((__DIV__) == RCC_CRS_SYNC_DIV128))

#define IS_RCC_CRS_SYNC_POLARITY(__POLARITY__) (((__POLARITY__) == RCC_CRS_SYNC_POLARITY_RISING) || \
                                                ((__POLARITY__) == RCC_CRS_SYNC_POLARITY_FALLING))

#define IS_RCC_CRS_RELOADVALUE(__VALUE__)  (((__VALUE__) <= 0xFFFFU))

#define IS_RCC_CRS_ERRORLIMIT(__VALUE__)   (((__VALUE__) <= 0xFFU))

#define IS_RCC_CRS_HSI48CALIBRATION(__VALUE__) (((__VALUE__) <= 0x3FU))

#define IS_RCC_CRS_FREQERRORDIR(__DIR__)   (((__DIR__) == RCC_CRS_FREQERRORDIR_UP) || \
                                            ((__DIR__) == RCC_CRS_FREQERRORDIR_DOWN))

#endif /* CRS */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCCEx_Private_Functions RCCEx Private Functions
  * @{
  */
static HAL_StatusTypeDef RCCEx_PLLSource_Enable(uint32_t PllSource);
static HAL_StatusTypeDef RCCEx_PLL2_Config(RCC_PLL2InitTypeDef *Pll2);
static HAL_StatusTypeDef RCCEx_PLL3_Config(RCC_PLL3InitTypeDef *Pll3);
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
        the backup registers) are set to their reset values.

@endverbatim
  * @{
  */
/**
  * @brief  Initialize the RCC extended peripherals clocks according to the specified
  *         parameters in the RCC_PeriphCLKInitTypeDef.
  * @param  pPeriphClkInit  pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         contains a field PeriphClockSelection which can be a combination of the following values:
  *            @arg @ref RCC_PERIPHCLK_USART1 USART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART2 USART2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART3 USART3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_UART4 UART4 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_UART5 UART5 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPUART1 LPUART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C1 I2C1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C2 I2C2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C3 I2C3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C4 I2C4 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM34 LPTIM34 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM2 LPTIM2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SAES SAES peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SAI1 SAI1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SAI2 SAI2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADCDAC ADC1,ADC4,DAC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_MDF1 MDF1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADF1 ADF1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_RTC RTC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_RNG RNG peripheral clock
  *            @arg @ref RCC_PERIPHCLK_CLK48 CLK48 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SDMMC SDMMC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI1 SPI1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI2 SPI2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI3 SPI3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_OSPI OSPI peripheral clock
  *            @arg @ref RCC_PERIPHCLK_FDCAN1 FDCAN1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_DAC1 DAC1 peripheral clock
  *
  * @note   Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select
  *         the RTC clock source: in this case the access to Backup domain is enabled.
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *pPeriphClkInit)
{
  uint32_t tmpregister;
  uint32_t tickstart;
  HAL_StatusTypeDef ret = HAL_OK;      /* Intermediate status */
  HAL_StatusTypeDef status = HAL_OK;   /* Final status */

  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(pPeriphClkInit->PeriphClockSelection));

  /*-------------------------- USART1 clock source configuration -------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART1) == RCC_PERIPHCLK_USART1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART1CLKSOURCE(pPeriphClkInit->Usart1ClockSelection));

    /* Configure the USART1 clock source */
    __HAL_RCC_USART1_CONFIG(pPeriphClkInit->Usart1ClockSelection);
  }

  /*-------------------------- USART2 clock source configuration -------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART2) == RCC_PERIPHCLK_USART2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART2CLKSOURCE(pPeriphClkInit->Usart2ClockSelection));

    /* Configure the USART2 clock source */
    __HAL_RCC_USART2_CONFIG(pPeriphClkInit->Usart2ClockSelection);
  }

  /*-------------------------- USART3 clock source configuration -------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART3) == RCC_PERIPHCLK_USART3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART3CLKSOURCE(pPeriphClkInit->Usart3ClockSelection));

    /* Configure the USART3 clock source */
    __HAL_RCC_USART3_CONFIG(pPeriphClkInit->Usart3ClockSelection);
  }

  /*-------------------------- UART4 clock source configuration --------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_UART4) == RCC_PERIPHCLK_UART4)
  {
    /* Check the parameters */
    assert_param(IS_RCC_UART4CLKSOURCE(pPeriphClkInit->Uart4ClockSelection));

    /* Configure the UART4 clock source */
    __HAL_RCC_UART4_CONFIG(pPeriphClkInit->Uart4ClockSelection);
  }

  /*-------------------------- UART5 clock source configuration --------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_UART5) == RCC_PERIPHCLK_UART5)
  {
    /* Check the parameters */
    assert_param(IS_RCC_UART5CLKSOURCE(pPeriphClkInit->Uart5ClockSelection));

    /* Configure the UART5 clock source */
    __HAL_RCC_UART5_CONFIG(pPeriphClkInit->Uart5ClockSelection);
  }

  /*-------------------------- LPUART1 clock source configuration ------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPUART1CLKSOURCE(pPeriphClkInit->Lpuart1ClockSelection));

    /* Configure the LPUART1 clock source */
    __HAL_RCC_LPUART1_CONFIG(pPeriphClkInit->Lpuart1ClockSelection);
  }

  /*-------------------------- I2C1 clock source configuration ---------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C1) == RCC_PERIPHCLK_I2C1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C1CLKSOURCE(pPeriphClkInit->I2c1ClockSelection));

    /* Configure the I2C1 clock source */
    __HAL_RCC_I2C1_CONFIG(pPeriphClkInit->I2c1ClockSelection);
  }

  /*-------------------------- I2C2 clock source configuration ---------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C2) == RCC_PERIPHCLK_I2C2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C2CLKSOURCE(pPeriphClkInit->I2c2ClockSelection));

    /* Configure the I2C2 clock source */
    __HAL_RCC_I2C2_CONFIG(pPeriphClkInit->I2c2ClockSelection);
  }

  /*-------------------------- I2C3 clock source configuration ---------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C3) == RCC_PERIPHCLK_I2C3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C3CLKSOURCE(pPeriphClkInit->I2c3ClockSelection));

    /* Configure the I2C3 clock source */
    __HAL_RCC_I2C3_CONFIG(pPeriphClkInit->I2c3ClockSelection);
  }

  /*-------------------------- I2C4 clock source configuration ---------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C4) == RCC_PERIPHCLK_I2C4)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C4CLKSOURCE(pPeriphClkInit->I2c4ClockSelection));

    /* Configure the I2C4 clock source */
    __HAL_RCC_I2C4_CONFIG(pPeriphClkInit->I2c4ClockSelection);
  }

  /*-------------------------- LPTIM1 clock source configuration -------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM1) == (RCC_PERIPHCLK_LPTIM1))
  {
    assert_param(IS_RCC_LPTIM1CLK(pPeriphClkInit->Lptim1ClockSelection));
    __HAL_RCC_LPTIM1_CONFIG(pPeriphClkInit->Lptim1ClockSelection);
  }

  /*-------------------------- LPTIM2 clock source configuration -------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM2) == (RCC_PERIPHCLK_LPTIM2))
  {
    assert_param(IS_RCC_LPTIM2CLK(pPeriphClkInit->Lptim2ClockSelection));
    __HAL_RCC_LPTIM2_CONFIG(pPeriphClkInit->Lptim2ClockSelection);
  }

  /*-------------------------- LPTIM34 clock source configuration -------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM34) == (RCC_PERIPHCLK_LPTIM34))
  {
    assert_param(IS_RCC_LPTIM34CLK(pPeriphClkInit->Lptim34ClockSelection));
    __HAL_RCC_LPTIM34_CONFIG(pPeriphClkInit->Lptim34ClockSelection);
  }

  /*-------------------------- SAI1 clock source configuration ---------------------*/
  if ((((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI1) == RCC_PERIPHCLK_SAI1))
  {
    /* Check the parameters */
    assert_param(IS_RCC_SAI1CLK(pPeriphClkInit->Sai1ClockSelection));

    switch (pPeriphClkInit->Sai1ClockSelection)
    {
      case RCC_SAI1CLKSOURCE_PLL1:      /* PLL is used as clock source for SAI1*/
        /* Enable SAI Clock output generated from System PLL  */
        __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL1_DIVP);
        /* SAI1 clock source config set later after clock selection check */
        break;

      case RCC_SAI1CLKSOURCE_PLL2:  /* PLL2 is used as clock source for SAI1*/
        /* PLL2 P input clock, parameters M, N & P configuration and clock output (PLL2ClockOut) */
        ret = RCCEx_PLL2_Config(&(pPeriphClkInit->PLL2));
        /* SAI1 clock source config set later after clock selection check */
        break;

      case RCC_SAI1CLKSOURCE_PLL3:  /* PLL3 is used as clock source for SAI1*/
        /* PLL3 P input clock, parameters M, N & P configuration clock output (PLL3ClockOut) */
        ret = RCCEx_PLL3_Config(&(pPeriphClkInit->PLL3));
        /* SAI1 clock source config set later after clock selection check */
        break;

      case RCC_SAI1CLKSOURCE_PIN:      /* External clock is used as source of SAI1 clock*/
        /* SAI1 clock source configuration done later after clock selection check */
        break;

      case RCC_SAI1CLKSOURCE_HSI:      /* HSI is used as source of SAI1 clock*/
        /* SAI1 clock source config set later after clock selection check */
        break;

      default:
        ret = HAL_ERROR;
        break;
    }

    if (ret == HAL_OK)
    {
      /* Set the source of SAI1 clock*/
      __HAL_RCC_SAI1_CONFIG(pPeriphClkInit->Sai1ClockSelection);
    }
    else
    {
      /* set overall return value */
      status = ret;
    }
  }

  /*-------------------------- SAI2 clock source configuration ---------------------*/
  if ((((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI2) == RCC_PERIPHCLK_SAI2))
  {
    /* Check the parameters */
    assert_param(IS_RCC_SAI2CLK(pPeriphClkInit->Sai2ClockSelection));

    switch (pPeriphClkInit->Sai2ClockSelection)
    {
      case RCC_SAI2CLKSOURCE_PLL1:      /* PLL is used as clock source for SAI2*/
        /* Enable SAI Clock output generated from System PLL  */
        __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL1_DIVP);
        /* SAI2 clock source config set later after clock selection check */
        break;

      case RCC_SAI2CLKSOURCE_PLL2: /* PLL2 is used as clock source for SAI2*/
        /* PLL2 P input clock, parameters M, N & P configuration and clock output (PLL2ClockOut) */
        ret = RCCEx_PLL2_Config(&(pPeriphClkInit->PLL2));
        /* SAI2 clock source config set later after clock selection check */
        break;

      case RCC_SAI2CLKSOURCE_PLL3:  /* PLL3 is used as clock source for SAI2*/
        /* PLL3 P input clock, parameters M, N & P configuration and clock output (PLL3ClockOut) */
        ret = RCCEx_PLL3_Config(&(pPeriphClkInit->PLL3));
        /* SAI2 clock source config set later after clock selection check */
        break;

      case RCC_SAI2CLKSOURCE_PIN:      /* External clock is used as source of SAI2 clock*/
        /* SAI2 clock source configuration done later after clock selection check */
        break;
      case RCC_SAI2CLKSOURCE_HSI:      /* HSI is used as source of SAI2 clock*/
        /* SAI2 clock source config set later after clock selection check */
        break;

      default:
        ret = HAL_ERROR;
        break;
    }

    if (ret == HAL_OK)
    {
      /* Set the source of SAI2 clock*/
      __HAL_RCC_SAI2_CONFIG(pPeriphClkInit->Sai2ClockSelection);
    }
    else
    {
      /* set overall return value */
      status = ret;
    }
  }

  /*-------------------------- ADCDAC clock source configuration ----------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADCDAC) == RCC_PERIPHCLK_ADCDAC)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADCDACCLKSOURCE(pPeriphClkInit->AdcDacClockSelection));

    switch (pPeriphClkInit->AdcDacClockSelection)
    {
      case RCC_ADCDACCLKSOURCE_PLL2:
        /* PLL2 input clock, parameters M, N,P, & R configuration and clock output (PLL2ClockOut) */
        ret = RCCEx_PLL2_Config(&(pPeriphClkInit->PLL2));
        break;

      case RCC_ADCDACCLKSOURCE_SYSCLK:
      case RCC_ADCDACCLKSOURCE_HCLK:
      case RCC_ADCDACCLKSOURCE_HSE:
      case RCC_ADCDACCLKSOURCE_HSI:
      case RCC_ADCDACCLKSOURCE_MSIK:
        break;
      default:
        ret = HAL_ERROR;
        break;
    }

    if (ret == HAL_OK)
    {
      /* Configure the ADC1 interface clock source */
      __HAL_RCC_ADCDAC_CONFIG(pPeriphClkInit->AdcDacClockSelection);
    }
    else
    {
      /* set overall return value */
      status = ret;
    }
  }

  /*-------------------------- MDF1 clock source configuration -------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_MDF1) == RCC_PERIPHCLK_MDF1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_MDF1CLKSOURCE(pPeriphClkInit->Mdf1ClockSelection));

    switch (pPeriphClkInit->Mdf1ClockSelection)
    {
      case RCC_MDF1CLKSOURCE_PLL1:
        /* Enable PLL1 Clock output generated from System PLL  */
        __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL1_DIVP);
        break;
      case RCC_MDF1CLKSOURCE_PLL3:
        /* PLL3 Q input clock, parameters M, N & Q configuration and clock output (PLL3ClockOut) */
        ret = RCCEx_PLL3_Config(&(pPeriphClkInit->PLL3));
        break;
      case RCC_MDF1CLKSOURCE_HCLK:
        break;
      case RCC_MDF1CLKSOURCE_PIN:
        break;
      case RCC_MDF1CLKSOURCE_MSIK:
        break;
      default:
        ret = HAL_ERROR;
        break;
    }

    if (ret == HAL_OK)
    {
      /* Configure the MDF1 interface clock source */
      __HAL_RCC_MDF1_CONFIG(pPeriphClkInit->Mdf1ClockSelection);
    }
    else
    {
      /* set overall return value */
      status = ret;
    }
  }

  /*-------------------------- ADF1 clock source configuration -------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADF1) == RCC_PERIPHCLK_ADF1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADF1CLKSOURCE(pPeriphClkInit->Adf1ClockSelection));

    switch (pPeriphClkInit->Adf1ClockSelection)
    {
      case RCC_ADF1CLKSOURCE_PLL1:
        /* Enable PLL1 Clock output generated from System PLL  */
        __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL1_DIVP);
        break;
      case RCC_ADF1CLKSOURCE_PLL3:
        /* PLL3 Q input clock, parameters M, N & Q configuration and clock output (PLL3ClockOut) */
        ret = RCCEx_PLL3_Config(&(pPeriphClkInit->PLL3));
        break;
      case RCC_ADF1CLKSOURCE_HCLK:
        break;
      case RCC_ADF1CLKSOURCE_PIN:
        break;
      case RCC_ADF1CLKSOURCE_MSIK:
        break;
      default:
        ret = HAL_ERROR;
        break;
    }

    if (ret == HAL_OK)
    {
      /* Configure the ADF1 interface clock source */
      __HAL_RCC_ADF1_CONFIG(pPeriphClkInit->Adf1ClockSelection);
    }
    else
    {
      /* set overall return value */
      status = ret;
    }
  }

  /*-------------------------- RTC clock source configuration ----------------------*/
  if ((pPeriphClkInit->PeriphClockSelection & RCC_PERIPHCLK_RTC) == RCC_PERIPHCLK_RTC)
  {
    FlagStatus       pwrclkchanged = RESET;
    /* Check for RTC Parameters used to output RTCCLK */
    assert_param(IS_RCC_RTCCLKSOURCE(pPeriphClkInit->RTCClockSelection));

    /* Enable Power Clock */
    if (__HAL_RCC_PWR_IS_CLK_DISABLED())
    {
      __HAL_RCC_PWR_CLK_ENABLE();
      pwrclkchanged = SET;
    }
    /* Enable write access to Backup domain */
    SET_BIT(PWR->DBPR, PWR_DBPR_DBP);

    /* Wait for Backup domain Write protection disable */
    tickstart = HAL_GetTick();

    while (HAL_IS_BIT_CLR(PWR->DBPR, PWR_DBPR_DBP))
    {
      if ((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
      {
        ret = HAL_TIMEOUT;
        break;
      }
    }

    if (ret == HAL_OK)
    {
      /* Reset the Backup domain only if the RTC Clock source selection is modified from default */
      tmpregister = READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL);

      if ((tmpregister != RCC_RTCCLKSOURCE_NO_CLK) && (tmpregister != pPeriphClkInit->RTCClockSelection))
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
      if (HAL_IS_BIT_SET(tmpregister, RCC_BDCR_LSEON))
      {
        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till LSE is ready */
        while (READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == 0U)
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
        __HAL_RCC_RTC_CONFIG(pPeriphClkInit->RTCClockSelection);
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

    /* Restore clock configuration if changed */
    if (pwrclkchanged == SET)
    {
      __HAL_RCC_PWR_CLK_DISABLE();
    }
  }

  /*-------------------------------------- CK48 Configuration -----------------------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_CLK48) == RCC_PERIPHCLK_CLK48)
  {
    /* Check the parameters */
    assert_param(IS_RCC_CLK48CLKSOURCE(pPeriphClkInit->Clk48ClockSelection));

    switch (pPeriphClkInit->Clk48ClockSelection)
    {
      case RCC_CLK48CLKSOURCE_PLL2:
        /* PLL2 input clock, parameters M, N,P,Q & R configuration and clock output (PLL2ClockOut) */
        ret = RCCEx_PLL2_Config(&(pPeriphClkInit->PLL2));
        break;
      case RCC_CLK48CLKSOURCE_PLL1:
        /* Enable CLK48 Clock output generated from System PLL  */
        __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL1_DIVQ);
        break;
      case RCC_CLK48CLKSOURCE_HSI48:
        break;
      case RCC_CLK48CLKSOURCE_MSIK:
        break;
      default:
        ret = HAL_ERROR;
        break;
    }
    if (ret == HAL_OK)
    {
      /* Configure the CLK48 source */
      __HAL_RCC_CLK48_CONFIG(pPeriphClkInit->Clk48ClockSelection);
    }
    else
    {
      /* set overall return value */
      status = ret;
    }
  }

  /*------------------------------ RNG Configuration -------------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RNG) == RCC_PERIPHCLK_RNG)
  {

    /* Check the parameters */
    assert_param(IS_RCC_RNGCLKSOURCE(pPeriphClkInit->RngClockSelection));

    switch (pPeriphClkInit->RngClockSelection)
    {
      case RCC_RNGCLKSOURCE_HSI48_DIV2: /* HSI48/2 is used as clock source for RNG*/
        /* RNG clock source configuration done later after clock selection check */
        break;
      case RCC_RNGCLKSOURCE_HSI: /* HSI is used as clock source for RNG*/
        /* RNG clock source configuration done later after clock selection check */
        break;
      case RCC_RNGCLKSOURCE_HSI48:
        /* HSI48 oscillator is used as source of RNG clock */
        /* RNG clock source configuration done later after clock selection check */
        break;
      default:
        ret = HAL_ERROR;
        break;
    }

    if (ret == HAL_OK)
    {
      /* Set the source of RNG clock*/
      __HAL_RCC_RNG_CONFIG(pPeriphClkInit->RngClockSelection);
    }
    else
    {
      /* set overall return value */
      status = ret;
    }
  }

  /*-------------------------- SAES clock source configuration ----------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAES) == RCC_PERIPHCLK_SAES)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SAESCLKSOURCE(pPeriphClkInit->SaesClockSelection));

    /* Configure the SAES clock source */
    __HAL_RCC_SAES_CONFIG(pPeriphClkInit->SaesClockSelection);
  }

  /*-------------------------- SDMMC1/2 clock source configuration -------------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SDMMC) == (RCC_PERIPHCLK_SDMMC))
  {
    /* Check the parameters */
    assert_param(IS_RCC_SDMMCCLKSOURCE(pPeriphClkInit->SdmmcClockSelection));

    if (pPeriphClkInit->SdmmcClockSelection == RCC_SDMMCCLKSOURCE_PLL1)
    {
      /* Enable PLL1 P CLK output */
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL1_DIVP);
    }

    /* Configure the SDMMC1/2 clock source */
    __HAL_RCC_SDMMC_CONFIG(pPeriphClkInit->SdmmcClockSelection);
  }

  /*-------------------------- SPI1 clock source configuration ----------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SPI1) == RCC_PERIPHCLK_SPI1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SPI1CLKSOURCE(pPeriphClkInit->Spi1ClockSelection));

    /* Configure the SPI1 clock source */
    __HAL_RCC_SPI1_CONFIG(pPeriphClkInit->Spi1ClockSelection);
  }

  /*-------------------------- SPI2 clock source configuration ----------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SPI2) == RCC_PERIPHCLK_SPI2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SPI2CLKSOURCE(pPeriphClkInit->Spi2ClockSelection));

    /* Configure the SPI2 clock source */
    __HAL_RCC_SPI2_CONFIG(pPeriphClkInit->Spi2ClockSelection);
  }

  /*-------------------------- SPI3 clock source configuration ----------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SPI3) == RCC_PERIPHCLK_SPI3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SPI3CLKSOURCE(pPeriphClkInit->Spi3ClockSelection));

    /* Configure the SPI3 clock source */
    __HAL_RCC_SPI3_CONFIG(pPeriphClkInit->Spi3ClockSelection);
  }

  /*-------------------------- OctoSPIx clock source configuration ----------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_OSPI) == RCC_PERIPHCLK_OSPI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_OSPICLKSOURCE(pPeriphClkInit->OspiClockSelection));

    if (pPeriphClkInit->OspiClockSelection == RCC_OSPICLKSOURCE_PLL1)
    {
      /* Enable PLL1 Q CLK output */
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL1_DIVQ);
    }
    if (pPeriphClkInit->OspiClockSelection == RCC_OSPICLKSOURCE_PLL2)
    {
      /* Enable PLL2 Q CLK output */
      __HAL_RCC_PLL2CLKOUT_ENABLE(RCC_PLL2_DIVQ);
    }
    /* Configure the OctoSPI clock source */
    __HAL_RCC_OSPI_CONFIG(pPeriphClkInit->OspiClockSelection);
  }

  /*-------------------------- FDCAN1 kernel clock source configuration -------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_FDCAN1) == (RCC_PERIPHCLK_FDCAN1))
  {
    assert_param(IS_RCC_FDCAN1CLK(pPeriphClkInit->Fdcan1ClockSelection));

    switch (pPeriphClkInit->Fdcan1ClockSelection)
    {
      case RCC_FDCAN1CLKSOURCE_HSE:      /* HSE is used as source of FDCAN1 kernel clock*/
        /* FDCAN1 kernel clock source config set later after clock selection check */
        break;
      case RCC_FDCAN1CLKSOURCE_PLL1:      /* PLL1 is used as clock source for FDCAN1 kernel clock*/
        /* Enable 48M2 Clock output generated from System PLL  */
        __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL1_DIVQ);
        /* FDCAN1 kernel clock source config set later after clock selection check */
        break;
      case RCC_FDCAN1CLKSOURCE_PLL2:  /* PLL2 is used as clock source for FDCAN1 kernel clock*/
        /* PLL2 input clock, parameters M, N & P configuration and clock output (PLL2ClockOut) */
        ret = RCCEx_PLL2_Config(&(pPeriphClkInit->PLL2));
        /* FDCAN1 kernel clock source config set later after clock selection check */
        break;
      default:
        ret = HAL_ERROR;
        break;
    }
    if (ret == HAL_OK)
    {
      /* Set the source of FDCAN1 kernel clock*/
      __HAL_RCC_FDCAN1_CONFIG(pPeriphClkInit->Fdcan1ClockSelection);
    }
    else
    {
      /* set overall return value */
      status = ret;
    }
  }

  /*-------------------------- DAC1 clock source configuration ----------------*/
  if (((pPeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_DAC1) == RCC_PERIPHCLK_DAC1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_DAC1CLKSOURCE(pPeriphClkInit->Dac1ClockSelection));

    /* Configure the DAC1 clock source */
    __HAL_RCC_DAC1_CONFIG(pPeriphClkInit->Dac1ClockSelection);
  }

  return status;
}

/**
  * @brief  Get the RCC_ClkInitStruct according to the internal RCC configuration registers.
  * @param  pPeriphClkInit  pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         returns the configuration information for the Extended Peripherals
  *         clocks(USART1, USART2, USART3, UART4, UART5, LPUART, I2C1, I2C2, I2C3, LPTIM1, LPTIM2, SAI1, SAI2,
  *         SAES, ADC1, ADC4, MDF1, MDF2, RTC, CLK48, SDMMC1, I2C4, SPI12, SPI3, OSPI, FDCAN1, DAC1).
  * @retval None
  */
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *pPeriphClkInit)
{
  /* Set all possible values for the extended clock type parameter------------*/
  pPeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                         RCC_PERIPHCLK_UART4 | RCC_PERIPHCLK_UART5 | RCC_PERIPHCLK_LPUART1 | \
                                         RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_I2C2 | RCC_PERIPHCLK_I2C3 | \
                                         RCC_PERIPHCLK_LPTIM1 | RCC_PERIPHCLK_LPTIM34 | RCC_PERIPHCLK_LPTIM2 | \
                                         RCC_PERIPHCLK_SAES | RCC_PERIPHCLK_SAI1 | RCC_PERIPHCLK_SAI2 | \
                                         RCC_PERIPHCLK_ADCDAC | RCC_PERIPHCLK_MDF1 | RCC_PERIPHCLK_ADF1 | \
                                         RCC_PERIPHCLK_RTC | RCC_PERIPHCLK_CLK48 | RCC_PERIPHCLK_SDMMC | \
                                         RCC_PERIPHCLK_RNG | RCC_PERIPHCLK_I2C4 | RCC_PERIPHCLK_SPI1 | \
                                         RCC_PERIPHCLK_SPI2 | RCC_PERIPHCLK_SPI3 | RCC_PERIPHCLK_OSPI | \
                                         RCC_PERIPHCLK_FDCAN1 | RCC_PERIPHCLK_DAC1;

  /* Get the PLL2 Clock configuration -----------------------------------------------*/
  pPeriphClkInit->PLL2.PLL2Source = (uint32_t)((RCC->PLL2CFGR & RCC_PLL2CFGR_PLL2SRC) >> RCC_PLL2CFGR_PLL2SRC_Pos);
  pPeriphClkInit->PLL2.PLL2M = (uint32_t)((RCC->PLL2CFGR & RCC_PLL2CFGR_PLL2M) >> RCC_PLL2CFGR_PLL2M_Pos) + 1U;
  pPeriphClkInit->PLL2.PLL2N = (uint32_t)((RCC->PLL2DIVR & RCC_PLL2DIVR_PLL2N) >> RCC_PLL2DIVR_PLL2N_Pos) + 1U;
  pPeriphClkInit->PLL2.PLL2P = (uint32_t)((RCC->PLL2DIVR & RCC_PLL2DIVR_PLL2P) >> RCC_PLL2DIVR_PLL2P_Pos) + 1U;
  pPeriphClkInit->PLL2.PLL2Q = (uint32_t)((RCC->PLL2DIVR & RCC_PLL2DIVR_PLL2Q) >> RCC_PLL2DIVR_PLL2Q_Pos) + 1U;
  pPeriphClkInit->PLL2.PLL2R = (uint32_t)((RCC->PLL2DIVR & RCC_PLL2DIVR_PLL2R) >> RCC_PLL2DIVR_PLL2R_Pos) + 1U;
  pPeriphClkInit->PLL2.PLL2RGE = (uint32_t)((RCC->PLL2CFGR & RCC_PLL2CFGR_PLL2RGE) >> RCC_PLL2CFGR_PLL2RGE_Pos);
  pPeriphClkInit->PLL2.PLL2FRACN = (uint32_t)((RCC->PLL2FRACR & RCC_PLL2FRACR_PLL2FRACN) >> \
                                              RCC_PLL2FRACR_PLL2FRACN_Pos);

  /* Get the PLL3 Clock configuration -----------------------------------------------*/
  pPeriphClkInit->PLL3.PLL3Source = (uint32_t)((RCC->PLL3CFGR & RCC_PLL3CFGR_PLL3SRC) >> RCC_PLL3CFGR_PLL3SRC_Pos);
  pPeriphClkInit->PLL3.PLL3M = (uint32_t)((RCC->PLL3CFGR & RCC_PLL3CFGR_PLL3M) >> RCC_PLL3CFGR_PLL3M_Pos) + 1U;
  pPeriphClkInit->PLL3.PLL3N = (uint32_t)((RCC->PLL3DIVR & RCC_PLL3DIVR_PLL3N) >> RCC_PLL3DIVR_PLL3N_Pos) + 1U;
  pPeriphClkInit->PLL3.PLL3P = (uint32_t)((RCC->PLL3DIVR & RCC_PLL3DIVR_PLL3P) >> RCC_PLL3DIVR_PLL3P_Pos) + 1U;
  pPeriphClkInit->PLL3.PLL3Q = (uint32_t)((RCC->PLL3DIVR & RCC_PLL3DIVR_PLL3Q) >> RCC_PLL3DIVR_PLL3Q_Pos) + 1U;
  pPeriphClkInit->PLL3.PLL3R = (uint32_t)((RCC->PLL3DIVR & RCC_PLL3DIVR_PLL3R) >> RCC_PLL3DIVR_PLL3R_Pos) + 1U;
  pPeriphClkInit->PLL3.PLL3RGE = (uint32_t)((RCC->PLL3CFGR & RCC_PLL3CFGR_PLL3RGE) >> RCC_PLL3CFGR_PLL3RGE_Pos);
  pPeriphClkInit->PLL3.PLL3FRACN = (uint32_t)((RCC->PLL3FRACR & RCC_PLL3FRACR_PLL3FRACN) >> \
                                              RCC_PLL3FRACR_PLL3FRACN_Pos);

  /* Get the USART1 clock source ---------------------------------------------*/
  pPeriphClkInit->Usart1ClockSelection = __HAL_RCC_GET_USART1_SOURCE();

  /* Get the USART2 clock source ---------------------------------------------*/
  pPeriphClkInit->Usart2ClockSelection = __HAL_RCC_GET_USART2_SOURCE();

  /* Get the USART3 clock source ---------------------------------------------*/
  pPeriphClkInit->Usart3ClockSelection = __HAL_RCC_GET_USART3_SOURCE();

  /* Get the UART4 clock source ----------------------------------------------*/
  pPeriphClkInit->Uart4ClockSelection = __HAL_RCC_GET_UART4_SOURCE();

  /* Get the UART5 clock source ----------------------------------------------*/
  pPeriphClkInit->Uart5ClockSelection = __HAL_RCC_GET_UART5_SOURCE();

  /* Get the LPUART1 clock source --------------------------------------------*/
  pPeriphClkInit->Lpuart1ClockSelection = __HAL_RCC_GET_LPUART1_SOURCE();

  /* Get the I2C1 clock source -----------------------------------------------*/
  pPeriphClkInit->I2c1ClockSelection = __HAL_RCC_GET_I2C1_SOURCE();

  /* Get the I2C2 clock source -----------------------------------------------*/
  pPeriphClkInit->I2c2ClockSelection = __HAL_RCC_GET_I2C2_SOURCE();

  /* Get the I2C3 clock source -----------------------------------------------*/
  pPeriphClkInit->I2c3ClockSelection = __HAL_RCC_GET_I2C3_SOURCE();

  /* Get the I2C4 clock source -----------------------------------------------*/
  pPeriphClkInit->I2c4ClockSelection = __HAL_RCC_GET_I2C4_SOURCE();

  /* Get the LPTIM1 clock source ---------------------------------------------*/
  pPeriphClkInit->Lptim1ClockSelection = __HAL_RCC_GET_LPTIM1_SOURCE();

  /* Get the LPTIM2 clock source ---------------------------------------------*/
  pPeriphClkInit->Lptim2ClockSelection = __HAL_RCC_GET_LPTIM2_SOURCE();

  /* Get the LPTIM34 clock source --------------------------------------------*/
  pPeriphClkInit->Lptim34ClockSelection = __HAL_RCC_GET_LPTIM34_SOURCE();

  /* Get the FDCAN1 clock source ---------------------------------------------*/
  pPeriphClkInit->Fdcan1ClockSelection = __HAL_RCC_GET_FDCAN1_SOURCE();

  /* Get the MDF1 clock source -----------------------------------------------*/
  pPeriphClkInit->Mdf1ClockSelection = __HAL_RCC_GET_MDF1_SOURCE();

  /* Get the ADF1 clock source -----------------------------------------------*/
  pPeriphClkInit->Adf1ClockSelection = __HAL_RCC_GET_ADF1_SOURCE();

  /* Get the SAES clock source -----------------------------------------------*/
  pPeriphClkInit->SaesClockSelection = __HAL_RCC_GET_SAES_SOURCE();

  /* Get the SAI1 clock source -----------------------------------------------*/
  pPeriphClkInit->Sai1ClockSelection = __HAL_RCC_GET_SAI1_SOURCE();

  /* Get the SAI2 clock source -----------------------------------------------*/
  pPeriphClkInit->Sai2ClockSelection = __HAL_RCC_GET_SAI2_SOURCE();

  /* Get the CLK48 clock source ----------------------------------------------*/
  pPeriphClkInit->Clk48ClockSelection = __HAL_RCC_GET_CLK48_SOURCE();

  /* Get the SDMMC clock source ----------------------------------------------*/
  pPeriphClkInit->SdmmcClockSelection = __HAL_RCC_GET_SDMMC_SOURCE();

  /* Get the ADCDAC clock source ---------------------------------------------*/
  pPeriphClkInit->AdcDacClockSelection = __HAL_RCC_GET_ADCDAC_SOURCE();

  /* Get the DAC1 clock source -----------------------------------------------*/
  pPeriphClkInit->Dac1ClockSelection = __HAL_RCC_GET_DAC1_SOURCE();

  /* Get the OSPI clock source -----------------------------------------------*/
  pPeriphClkInit->OspiClockSelection = __HAL_RCC_GET_OSPI_SOURCE();

  /* Get the SPI1 clock source -----------------------------------------------*/
  pPeriphClkInit->Spi1ClockSelection = __HAL_RCC_GET_SPI1_SOURCE();

  /* Get the SPI2 clock source -----------------------------------------------*/
  pPeriphClkInit->Spi2ClockSelection = __HAL_RCC_GET_SPI2_SOURCE();

  /* Get the SPI3 clock source -----------------------------------------------*/
  pPeriphClkInit->Spi3ClockSelection = __HAL_RCC_GET_SPI3_SOURCE();

  /* Get the RTC clock source ------------------------------------------------*/
  pPeriphClkInit->RTCClockSelection = __HAL_RCC_GET_RTC_SOURCE();

  /* Get the RNG clock source ------------------------------------------------*/
  pPeriphClkInit->RngClockSelection = __HAL_RCC_GET_RNG_SOURCE();
}

/**
  * @brief  Returns the PLL1 clock frequencies :PLL1_P_Frequency,PLL1_R_Frequency and PLL1_Q_Frequency
  * @note   The PLL1 clock frequencies computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source:
  * @note   The function returns values based on HSE_VALUE, HSI_VALUE or MSI Value multiplied/divided by the PLL
  *         factors.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  *
  * @note   Each time PLL1CLK changes, this function must be called to update the
  *         right PLL1CLK value. Otherwise, any configuration based on this function will be incorrect.
  * @param  PLL1_Clocks structure.
  * @retval None
  */
void HAL_RCCEx_GetPLL1ClockFreq(PLL1_ClocksTypeDef *PLL1_Clocks)
{
  uint32_t pll1source;
  uint32_t  pll1m;
  uint32_t pll1n;
  uint32_t pll1fracen;
  float_t fracn1;
  float_t pll1vco;

  pll1n = (RCC->PLL1DIVR & RCC_PLL1DIVR_PLL1N);
  pll1source = (RCC->PLL1CFGR & RCC_PLL1CFGR_PLL1SRC);
  pll1m = ((RCC->PLL1CFGR & RCC_PLL1CFGR_PLL1M) >> RCC_PLL1CFGR_PLL1M_Pos) + 1U;
  pll1fracen = RCC->PLL1CFGR & RCC_PLL1CFGR_PLL1FRACEN;
  fracn1 = (float_t)(uint32_t)(pll1fracen * ((RCC->PLL1FRACR & RCC_PLL1FRACR_PLL1FRACN) >> \
                                             RCC_PLL1FRACR_PLL1FRACN_Pos));

  if (pll1m != 0U)
  {
    switch (pll1source)
    {

      case RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
        pll1vco = ((float_t)HSI_VALUE / (float_t)pll1m) * ((float_t)(uint32_t)(RCC->PLL1DIVR & RCC_PLL1DIVR_PLL1N) + \
                                                           (fracn1 / (float_t)0x2000) + (float_t)1);
        break;
      case RCC_PLLSOURCE_MSI:  /* MSI used as PLL clock source */
        pll1vco = ((float_t)MSIRangeTable[(__HAL_RCC_GET_MSI_RANGE() >> RCC_ICSCR1_MSISRANGE_Pos)] / (float_t)pll1m) * \
                  ((float_t)pll1n + (fracn1 / (float_t)0x2000) + (float_t)1);
        break;
      case RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
        pll1vco = ((float_t)HSE_VALUE / (float_t)pll1m) * ((float_t)(uint32_t)(RCC->PLL1DIVR & RCC_PLL1DIVR_PLL1N) + \
                                                           (fracn1 / (float_t)0x2000) + (float_t)1);
        break;
      default:
        pll1vco = ((float_t)MSIRangeTable[(__HAL_RCC_GET_MSI_RANGE() >> RCC_ICSCR1_MSISRANGE_Pos)] / (float_t)pll1m) * \
                  ((float_t)pll1n + (fracn1 / (float_t)0x2000) + (float_t)1);
        break;
    }

    if (__HAL_RCC_GET_PLLCLKOUT_CONFIG(RCC_PLL1_DIVP) != 0U)
    {
      PLL1_Clocks->PLL1_P_Frequency = (uint32_t)(float_t)(pll1vco / ((float_t)(uint32_t)((RCC->PLL1DIVR & \
                                                                     RCC_PLL1DIVR_PLL1P) >> RCC_PLL1DIVR_PLL1P_Pos) + \
                                                                     (float_t)1));
    }
    else
    {
      PLL1_Clocks->PLL1_P_Frequency = 0U;
    }

    if (__HAL_RCC_GET_PLLCLKOUT_CONFIG(RCC_PLL1_DIVQ) != 0U)
    {
      PLL1_Clocks->PLL1_Q_Frequency = (uint32_t)(float_t)(pll1vco / ((float_t)(uint32_t)((RCC->PLL1DIVR & \
                                                                     RCC_PLL1DIVR_PLL1Q) >> RCC_PLL1DIVR_PLL1Q_Pos) + \
                                                                     (float_t)1));
    }
    else
    {
      PLL1_Clocks->PLL1_Q_Frequency = 0U;
    }

    if (__HAL_RCC_GET_PLLCLKOUT_CONFIG(RCC_PLL1_DIVR) != 0U)
    {
      PLL1_Clocks->PLL1_R_Frequency = (uint32_t)(float_t)(pll1vco / ((float_t)(uint32_t)((RCC->PLL1DIVR & \
                                                                     RCC_PLL1DIVR_PLL1R) >> RCC_PLL1DIVR_PLL1R_Pos) + \
                                                                     (float_t)1));
    }
    else
    {
      PLL1_Clocks->PLL1_R_Frequency = 0U;
    }

  }
  else
  {
    PLL1_Clocks->PLL1_P_Frequency = 0U;
    PLL1_Clocks->PLL1_Q_Frequency = 0U;
    PLL1_Clocks->PLL1_R_Frequency = 0U;
  }
}

/**
  * @brief  Returns the PLL2 clock frequencies :PLL2_P_Frequency,PLL2_R_Frequency and PLL2_Q_Frequency
  * @note   The PLL2 clock frequencies computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source:
  * @note   The function returns values based on HSE_VALUE, HSI_VALUE or CSI Value multiplied/divided by the PLL
  *        factors.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  *
  * @note   Each time PLL2CLK changes, this function must be called to update the
  *         right PLL2CLK value. Otherwise, any configuration based on this function will be incorrect.
  * @param  PLL2_Clocks structure.
  * @retval None
  */
void HAL_RCCEx_GetPLL2ClockFreq(PLL2_ClocksTypeDef *PLL2_Clocks)
{
  uint32_t  pll2source;
  uint32_t pll2m;
  uint32_t pll2n;
  uint32_t pll2fracen;
  float_t fracn2;
  float_t pll2vco;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE or CSI_VALUE/ PLL2M) * PLL2N
     PLL2xCLK = PLL2_VCO / PLL2x */
  pll2n = (RCC->PLL2DIVR & RCC_PLL2DIVR_PLL2N);
  pll2source = (RCC->PLL2CFGR & RCC_PLL2CFGR_PLL2SRC);
  pll2m = ((RCC->PLL2CFGR & RCC_PLL2CFGR_PLL2M) >> RCC_PLL2CFGR_PLL2M_Pos) + 1U;
  pll2fracen = RCC->PLL2CFGR & RCC_PLL2CFGR_PLL2FRACEN;
  fracn2 = (float_t)(uint32_t)(pll2fracen * ((RCC->PLL2FRACR & RCC_PLL2FRACR_PLL2FRACN) >> \
                                             RCC_PLL2FRACR_PLL2FRACN_Pos));

  if (pll2m != 0U)
  {
    switch (pll2source)
    {
      case RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
        pll2vco = ((float_t)HSI_VALUE / (float_t)pll2m) * ((float_t)(uint32_t)(RCC->PLL2DIVR & RCC_PLL2DIVR_PLL2N) + \
                                                           (fracn2 / (float_t)0x2000) + (float_t)1);
        break;

      case RCC_PLLSOURCE_MSI:  /* MSI used as PLL clock source */
        pll2vco = ((float_t)MSIRangeTable[(__HAL_RCC_GET_MSI_RANGE() >> RCC_ICSCR1_MSISRANGE_Pos)] / (float_t)pll2m) * \
                  ((float_t)pll2n + (fracn2 / (float_t)0x2000) + (float_t)1);
        break;

      case RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
        pll2vco = ((float_t)HSE_VALUE / (float_t)pll2m) * ((float_t)(uint32_t)(RCC->PLL2DIVR & RCC_PLL2DIVR_PLL2N) + \
                                                           (fracn2 / (float_t)0x2000) + (float_t)1);
        break;

      default:
        pll2vco = ((float_t)MSIRangeTable[(__HAL_RCC_GET_MSI_RANGE() >> RCC_ICSCR1_MSISRANGE_Pos)] / (float_t) pll2m) \
                  * ((float_t)pll2n + (fracn2 / (float_t)0x2000) + (float_t)1);
        break;
    }
    if (__HAL_RCC_GET_PLL2CLKOUT_CONFIG(RCC_PLL2_DIVP) != 0U)
    {
      PLL2_Clocks->PLL2_P_Frequency = (uint32_t)(float_t)(pll2vco / ((float_t)(uint32_t)((RCC->PLL2DIVR & \
                                                                     RCC_PLL2DIVR_PLL2P) >> RCC_PLL2DIVR_PLL2P_Pos) + \
                                                                     (float_t)1));
    }
    else
    {
      PLL2_Clocks->PLL2_P_Frequency = 0U;
    }
    if (__HAL_RCC_GET_PLL2CLKOUT_CONFIG(RCC_PLL2_DIVQ) != 0U)
    {
      PLL2_Clocks->PLL2_Q_Frequency = (uint32_t)(float_t)(pll2vco / ((float_t)(uint32_t)((RCC->PLL2DIVR & \
                                                                     RCC_PLL2DIVR_PLL2Q) >> RCC_PLL2DIVR_PLL2Q_Pos) + \
                                                                     (float_t)1));
    }
    else
    {
      PLL2_Clocks->PLL2_Q_Frequency = 0U;
    }
    if (__HAL_RCC_GET_PLL2CLKOUT_CONFIG(RCC_PLL2_DIVR) != 0U)
    {
      PLL2_Clocks->PLL2_R_Frequency = (uint32_t)(float_t)(pll2vco / ((float_t)(uint32_t)((RCC->PLL2DIVR & \
                                                                     RCC_PLL2DIVR_PLL2R) >> RCC_PLL2DIVR_PLL2R_Pos) + \
                                                                     (float_t)1));
    }
    else
    {
      PLL2_Clocks->PLL2_R_Frequency = 0U;
    }
  }
  else
  {
    PLL2_Clocks->PLL2_P_Frequency = 0U;
    PLL2_Clocks->PLL2_Q_Frequency = 0U;
    PLL2_Clocks->PLL2_R_Frequency = 0U;
  }
}

/**
  * @brief  Returns the PLL3 clock frequencies :PLL3_P_Frequency,PLL3_R_Frequency and PLL3_Q_Frequency
  * @note   The PLL3 clock frequencies computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source:
  * @note   The function returns values based on HSE_VALUE, HSI_VALUE or CSI Value multiplied/divided by the PLL
  *         factors.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  *
  * @note   Each time PLL3CLK changes, this function must be called to update the
  *         right PLL3CLK value. Otherwise, any configuration based on this function will be incorrect.
  * @param  PLL3_Clocks structure.
  * @retval None
  */
void HAL_RCCEx_GetPLL3ClockFreq(PLL3_ClocksTypeDef *PLL3_Clocks)
{
  uint32_t pll3source;
  uint32_t pll3m;
  uint32_t pll3n;
  uint32_t pll3fracen;
  float_t fracn3;
  float_t pll3vco;

  /* PLL3_VCO = (HSE_VALUE or HSI_VALUE or CSI_VALUE/ PLL3M) * PLL3N
  PLL3xCLK = PLL3_VCO / PLLxR
  */

  pll3n = (RCC->PLL3DIVR & RCC_PLL3DIVR_PLL3N);
  pll3source = (RCC->PLL3CFGR & RCC_PLL3CFGR_PLL3SRC);
  pll3m = ((RCC->PLL3CFGR & RCC_PLL3CFGR_PLL3M) >> RCC_PLL3CFGR_PLL3M_Pos) + 1U;
  pll3fracen = RCC->PLL3CFGR & RCC_PLL3CFGR_PLL3FRACEN;
  fracn3 = (float_t)(uint32_t)(pll3fracen * ((RCC->PLL3FRACR & RCC_PLL3FRACR_PLL3FRACN) >> \
                                             RCC_PLL3FRACR_PLL3FRACN_Pos));

  if (pll3m != 0U)
  {
    switch (pll3source)
    {
      case RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */
        pll3vco = ((float_t)HSI_VALUE / (float_t)pll3m) * ((float_t)(uint32_t)(RCC->PLL3DIVR & RCC_PLL3DIVR_PLL3N) + \
                                                           (fracn3 / (float_t)0x2000) + (float_t)1);

        break;
      case RCC_PLLSOURCE_MSI:  /* MSI used as PLL clock source */
        pll3vco = ((float_t)MSIRangeTable[(__HAL_RCC_GET_MSI_RANGE() >> RCC_ICSCR1_MSISRANGE_Pos)] / (float_t)pll3m) * \
                  ((float_t)pll3n + (fracn3 / (float_t)0x2000) + (float_t)1);
        break;

      case RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
        pll3vco = ((float_t)HSE_VALUE / (float_t)pll3m) * ((float_t)(uint32_t)(RCC->PLL3DIVR & RCC_PLL3DIVR_PLL3N) + \
                                                           (fracn3 / (float_t)0x2000) + (float_t)1);
        break;

      default:
        pll3vco = ((float_t)MSIRangeTable[(__HAL_RCC_GET_MSI_RANGE() >> RCC_ICSCR1_MSISRANGE_Pos)] / (float_t)pll3m) * \
                  ((float_t)pll3n + (fracn3 / (float_t)0x2000) + (float_t)1);
        break;
    }

    if (__HAL_RCC_GET_PLL3CLKOUT_CONFIG(RCC_PLL3_DIVP) != 0U)
    {
      PLL3_Clocks->PLL3_P_Frequency = (uint32_t)(float_t)(pll3vco / ((float_t)(uint32_t)((RCC->PLL3DIVR & \
                                                                     RCC_PLL3DIVR_PLL3P) >> RCC_PLL3DIVR_PLL3P_Pos) + \
                                                                     (float_t)1));
    }
    else
    {
      PLL3_Clocks->PLL3_P_Frequency = 0U;
    }

    if (__HAL_RCC_GET_PLL3CLKOUT_CONFIG(RCC_PLL3_DIVQ) != 0U)
    {
      PLL3_Clocks->PLL3_Q_Frequency = (uint32_t)(float_t)(pll3vco / ((float_t)(uint32_t)((RCC->PLL3DIVR & \
                                                                     RCC_PLL3DIVR_PLL3Q) >> RCC_PLL3DIVR_PLL3Q_Pos) + \
                                                                     (float_t)1));
    }
    else
    {
      PLL3_Clocks->PLL3_Q_Frequency = 0U;
    }

    if (__HAL_RCC_GET_PLL3CLKOUT_CONFIG(RCC_PLL3_DIVR) != 0U)
    {
      PLL3_Clocks->PLL3_R_Frequency = (uint32_t)(float_t)(pll3vco / ((float_t)(uint32_t)((RCC->PLL3DIVR & \
                                                                     RCC_PLL3DIVR_PLL3R) >> RCC_PLL3DIVR_PLL3R_Pos) + \
                                                                     (float_t)1));
    }
    else
    {
      PLL3_Clocks->PLL3_R_Frequency = 0U;
    }

  }
  else
  {
    PLL3_Clocks->PLL3_P_Frequency = 0U;
    PLL3_Clocks->PLL3_Q_Frequency = 0U;
    PLL3_Clocks->PLL3_R_Frequency = 0U;
  }
}

/**
  * @brief  Return the peripheral clock frequency for peripherals
  * @note   Return 0 if peripheral clock identifier not managed by this API
  * @param  PeriphClk  Peripheral clock identifier
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PERIPHCLK_USART1 USART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART2 USART2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART3 USART3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_UART4 UART4 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_UART5 UART5 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPUART1 LPUART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C1 I2C1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C2 I2C2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C3 I2C3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C4 I2C4 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM34 LPTIM34 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_LPTIM2 LPTIM2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SAES SAES peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SAI1 SAI1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SAI2 SAI2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADCDAC ADC1,ADC4, DAC1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_MDF1 MDF1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_MDF1 MDF1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_RTC RTC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_CLK48 CLK48 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SDMMC SDMMC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI1 SPI1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI2 SPI2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SPI3 SPI3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_OSPI OSPI peripheral clock
  *            @arg @ref RCC_PERIPHCLK_FDCAN1 FDCAN1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_DAC1 DAC1 peripheral clock
  * @retval Frequency in Hz
  */
uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{
  PLL1_ClocksTypeDef pll1_clocks;
  PLL2_ClocksTypeDef pll2_clocks;
  PLL3_ClocksTypeDef pll3_clocks;

  uint32_t frequency;
  uint32_t srcclk;

  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClk));

  if (PeriphClk == RCC_PERIPHCLK_RTC)
  {
    /* Get the current RTC source */
    srcclk = __HAL_RCC_GET_RTC_SOURCE();

    /* Check if LSE is ready and if RTC clock selection is LSE */
    if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_RTCCLKSOURCE_LSE))
    {
      frequency = LSE_VALUE;
    }
    /* Check if LSI is ready and if RTC clock selection is LSI */
    else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSIRDY)) && (srcclk == RCC_RTCCLKSOURCE_LSI))
    {
      if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSIPREDIV))
      {
        frequency = LSI_VALUE / 128U;
      }
      else
      {
        frequency = LSI_VALUE;
      }
    }
    /* Check if HSE is ready  and if RTC clock selection is HSI_DIV32*/
    else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY)) && (srcclk == RCC_RTCCLKSOURCE_HSE_DIV32))
    {
      frequency = HSE_VALUE / 32U;
    }
    /* Clock not enabled for RTC*/
    else
    {
      frequency = 0U;
    }
  }
  else
  {
    /* Other external peripheral clock source than RTC */
    switch (PeriphClk)
    {
      case RCC_PERIPHCLK_SAI1:

        srcclk = __HAL_RCC_GET_SAI1_SOURCE();

        switch (srcclk)
        {
          case RCC_SAI1CLKSOURCE_PLL1: /* PLL1P is the clock source for SAI1 */

            HAL_RCCEx_GetPLL1ClockFreq(&pll1_clocks);
            frequency = pll1_clocks.PLL1_P_Frequency;
            break;

          case RCC_SAI1CLKSOURCE_PLL2: /* PLL2P is the clock source for SAI1 */

            HAL_RCCEx_GetPLL2ClockFreq(&pll2_clocks);
            frequency = pll2_clocks.PLL2_P_Frequency;
            break;

          case RCC_SAI1CLKSOURCE_PLL3: /* PLLI3P is the clock source for SAI1 */

            HAL_RCCEx_GetPLL3ClockFreq(&pll3_clocks);
            frequency = pll3_clocks.PLL3_P_Frequency;
            break;

          case RCC_SAI1CLKSOURCE_PIN:

            frequency = EXTERNAL_SAI1_CLOCK_VALUE;
            break;

          case RCC_SAI1CLKSOURCE_HSI: /* HSI is the clock source for SAI1 */

            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            else
            {
              frequency = 0U;
            }
            break;

          default :
          {
            frequency = 0U;
            break;
          }
        }
        break;

      case RCC_PERIPHCLK_SAI2:

        srcclk = __HAL_RCC_GET_SAI2_SOURCE();

        switch (srcclk)
        {
          case RCC_SAI2CLKSOURCE_PLL1: /* PLL1P is the clock source for SAI1 */

            HAL_RCCEx_GetPLL1ClockFreq(&pll1_clocks);
            frequency = pll1_clocks.PLL1_P_Frequency;
            break;

          case RCC_SAI2CLKSOURCE_PLL2: /* PLL2P is the clock source for SAI1 */

            HAL_RCCEx_GetPLL2ClockFreq(&pll2_clocks);
            frequency = pll2_clocks.PLL2_P_Frequency;
            break;

          case RCC_SAI2CLKSOURCE_PLL3: /* PLLI3P is the clock source for SAI1 */

            HAL_RCCEx_GetPLL3ClockFreq(&pll3_clocks);
            frequency = pll3_clocks.PLL3_P_Frequency;
            break;

          case RCC_SAI2CLKSOURCE_PIN:

            frequency = EXTERNAL_SAI1_CLOCK_VALUE;
            break;

          case RCC_SAI2CLKSOURCE_HSI: /* HSI is the clock source for SAI1 */

            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            else
            {
              frequency = 0U;
            }
            break;

          default :

            frequency = 0U;
            break;

        }
        break;
      case RCC_PERIPHCLK_SAES:
        /* Get the current SAES source */
        srcclk = __HAL_RCC_GET_SAES_SOURCE();

        if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY) && (srcclk == RCC_SAESCLKSOURCE_SHSI))
        {
          frequency = HSI_VALUE;
        }
        else if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY) && (srcclk == RCC_SAESCLKSOURCE_SHSI_DIV2))
        {
          frequency = HSI_VALUE >> 1U;
        }
        /* Clock not enabled for SAES */
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_CLK48:

        srcclk = __HAL_RCC_GET_CLK48_SOURCE();

        switch (srcclk)
        {
          case RCC_CLK48CLKSOURCE_PLL1: /* PLL1Q  */

            HAL_RCCEx_GetPLL1ClockFreq(&pll1_clocks);
            frequency = pll1_clocks.PLL1_Q_Frequency;
            break;

          case RCC_CLK48CLKSOURCE_PLL2: /* PLL2Q */

            HAL_RCCEx_GetPLL2ClockFreq(&pll2_clocks);
            frequency = pll2_clocks.PLL2_Q_Frequency;
            break;

          case RCC_CLK48CLKSOURCE_HSI48: /* HSI48 */

            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSI48RDY))
            {
              frequency = HSI48_VALUE;
            }
            else
            {
              frequency = 0U;
            }
            break;

          case RCC_CLK48CLKSOURCE_MSIK: /* MSIK frequency range in HZ */

            frequency = MSIRangeTable[(__HAL_RCC_GET_MSIK_RANGE() >> RCC_ICSCR1_MSIKRANGE_Pos)];
            break;

          default :

            frequency = 0U;
            break;

        }
        break;

      case RCC_PERIPHCLK_SDMMC:
        srcclk = __HAL_RCC_GET_SDMMC_SOURCE();
        if (srcclk == RCC_SDMMCCLKSOURCE_CLK48)
        {
          srcclk = __HAL_RCC_GET_CLK48_SOURCE();

          switch (srcclk)
          {
            case RCC_CLK48CLKSOURCE_PLL1: /* PLL1Q  */
            {
              HAL_RCCEx_GetPLL1ClockFreq(&pll1_clocks);
              frequency = pll1_clocks.PLL1_Q_Frequency;
              break;
            }
            case RCC_CLK48CLKSOURCE_PLL2: /* PLL2Q */
            {
              HAL_RCCEx_GetPLL2ClockFreq(&pll2_clocks);
              frequency = pll2_clocks.PLL2_Q_Frequency;
              break;
            }
            case RCC_CLK48CLKSOURCE_HSI48: /* HSI48 */
            {
              if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSI48RDY))
              {
                frequency = HSI48_VALUE;
              }
              else
              {
                frequency = 0U;
              }
              break;
            }
            case RCC_CLK48CLKSOURCE_MSIK: /* MSIK frequency range in HZ */
            {
              frequency = MSIRangeTable[(__HAL_RCC_GET_MSIK_RANGE() >> RCC_ICSCR1_MSIKRANGE_Pos)];
              break;
            }
            default :
            {
              frequency = 0U;
              break;
            }
          }
          break;
        }
        else if (srcclk == RCC_SDMMCCLKSOURCE_PLL1)
        {
          HAL_RCCEx_GetPLL1ClockFreq(&pll1_clocks);
          frequency = pll1_clocks.PLL1_P_Frequency;
        }
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_USART1:
        /* Get the current USART1 source */
        srcclk = __HAL_RCC_GET_USART1_SOURCE();

        if (srcclk == RCC_USART1CLKSOURCE_PCLK2)
        {
          frequency = HAL_RCC_GetPCLK2Freq();
        }
        else if (srcclk == RCC_USART1CLKSOURCE_SYSCLK)
        {
          frequency = HAL_RCC_GetSysClockFreq();
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_USART1CLKSOURCE_HSI))
        {
          frequency = HSI_VALUE;
        }
        else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_USART1CLKSOURCE_LSE))
        {
          frequency = LSE_VALUE;
        }
        /* Clock not enabled for USART1 */
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_USART2:
        /* Get the current USART2 source */
        srcclk = __HAL_RCC_GET_USART2_SOURCE();

        if (srcclk == RCC_USART2CLKSOURCE_PCLK1)
        {
          frequency = HAL_RCC_GetPCLK1Freq();
        }
        else if (srcclk == RCC_USART2CLKSOURCE_SYSCLK)
        {
          frequency = HAL_RCC_GetSysClockFreq();
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_USART2CLKSOURCE_HSI))
        {
          frequency = HSI_VALUE;
        }
        else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_USART2CLKSOURCE_LSE))
        {
          frequency = LSE_VALUE;
        }
        /* Clock not enabled for USART2 */
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_USART3:
        /* Get the current USART3 source */
        srcclk = __HAL_RCC_GET_USART3_SOURCE();

        if (srcclk == RCC_USART3CLKSOURCE_PCLK1)
        {
          frequency = HAL_RCC_GetPCLK1Freq();
        }
        else if (srcclk == RCC_USART3CLKSOURCE_SYSCLK)
        {
          frequency = HAL_RCC_GetSysClockFreq();
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_USART3CLKSOURCE_HSI))
        {
          frequency = HSI_VALUE;
        }
        else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_USART3CLKSOURCE_LSE))
        {
          frequency = LSE_VALUE;
        }
        /* Clock not enabled for USART3 */
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_UART4:
        /* Get the current UART4 source */
        srcclk = __HAL_RCC_GET_UART4_SOURCE();

        if (srcclk == RCC_UART4CLKSOURCE_PCLK1)
        {
          frequency = HAL_RCC_GetPCLK1Freq();
        }
        else if (srcclk == RCC_UART4CLKSOURCE_SYSCLK)
        {
          frequency = HAL_RCC_GetSysClockFreq();
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_UART4CLKSOURCE_HSI))
        {
          frequency = HSI_VALUE;
        }
        else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_UART4CLKSOURCE_LSE))
        {
          frequency = LSE_VALUE;
        }
        /* Clock not enabled for UART4 */
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_UART5:
        /* Get the current UART5 source */
        srcclk = __HAL_RCC_GET_UART5_SOURCE();

        if (srcclk == RCC_UART5CLKSOURCE_PCLK1)
        {
          frequency = HAL_RCC_GetPCLK1Freq();
        }
        else if (srcclk == RCC_UART5CLKSOURCE_SYSCLK)
        {
          frequency = HAL_RCC_GetSysClockFreq();
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_UART5CLKSOURCE_HSI))
        {
          frequency = HSI_VALUE;
        }
        else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_UART5CLKSOURCE_LSE))
        {
          frequency = LSE_VALUE;
        }
        /* Clock not enabled for UART5 */
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_LPUART1:
        /* Get the current LPUART1 source */
        srcclk = __HAL_RCC_GET_LPUART1_SOURCE();

        if (srcclk == RCC_LPUART1CLKSOURCE_PCLK3)
        {
          frequency = HAL_RCC_GetPCLK3Freq();
        }
        else if (srcclk == RCC_LPUART1CLKSOURCE_SYSCLK)
        {
          frequency = HAL_RCC_GetSysClockFreq();
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_LPUART1CLKSOURCE_HSI))
        {
          frequency = HSI_VALUE;
        }
        else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_LPUART1CLKSOURCE_LSE))
        {
          frequency = LSE_VALUE;
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_MSIKRDY)) && (srcclk == RCC_LPUART1CLKSOURCE_MSIK))
        {
          frequency = MSIRangeTable[(__HAL_RCC_GET_MSIK_RANGE() >> RCC_ICSCR1_MSIKRANGE_Pos)];
        }
        /* Clock not enabled for LPUART1 */
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_ADCDAC:

        srcclk = __HAL_RCC_GET_ADCDAC_SOURCE();

        if (srcclk == RCC_ADCDACCLKSOURCE_SYSCLK)
        {
          frequency = HAL_RCC_GetSysClockFreq();
        }
        else if (srcclk == RCC_ADCDACCLKSOURCE_PLL2)
        {
          HAL_RCCEx_GetPLL2ClockFreq(&pll2_clocks);
          frequency = pll2_clocks.PLL2_R_Frequency;
        }
        else if (srcclk == RCC_ADCDACCLKSOURCE_HCLK)
        {
          frequency = HAL_RCC_GetHCLKFreq();
          break;
        }
        else if (srcclk == RCC_ADCDACCLKSOURCE_MSIK)
        {
          frequency = MSIRangeTable[(__HAL_RCC_GET_MSI_RANGE() >> RCC_ICSCR1_MSISRANGE_Pos)];
          break;
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY)) && (srcclk == RCC_ADCDACCLKSOURCE_HSE))
        {
          frequency = HSE_VALUE;
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_ADCDACCLKSOURCE_HSI))
        {
          frequency = HSI_VALUE;
        }
        /* Clock not enabled for ADC */
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_MDF1:
        /* Get the current MDF1 source */
        srcclk = __HAL_RCC_GET_MDF1_SOURCE();

        switch (srcclk)
        {
          case RCC_MDF1CLKSOURCE_PLL1:

            HAL_RCCEx_GetPLL1ClockFreq(&pll1_clocks);
            frequency = pll1_clocks.PLL1_P_Frequency;
            break;

          case RCC_MDF1CLKSOURCE_PLL3:

            HAL_RCCEx_GetPLL3ClockFreq(&pll3_clocks);
            frequency = pll3_clocks.PLL3_Q_Frequency;
            break;

          case RCC_MDF1CLKSOURCE_HCLK:

            frequency = HAL_RCC_GetHCLKFreq();
            break;

          case RCC_MDF1CLKSOURCE_PIN:

            frequency = EXTERNAL_SAI1_CLOCK_VALUE;
            break;

          case RCC_MDF1CLKSOURCE_MSIK:

            frequency = MSIRangeTable[(__HAL_RCC_GET_MSIK_RANGE() >> RCC_ICSCR1_MSIKRANGE_Pos)];
            break;

          default:

            frequency = 0U;
            break;

        }
        break;

      case RCC_PERIPHCLK_ADF1:
        /* Get the current ADF1 source */
        srcclk = __HAL_RCC_GET_ADF1_SOURCE();

        switch (srcclk)
        {
          case RCC_ADF1CLKSOURCE_PLL1:

            HAL_RCCEx_GetPLL1ClockFreq(&pll1_clocks);
            frequency = pll1_clocks.PLL1_P_Frequency;
            break;

          case RCC_ADF1CLKSOURCE_PLL3:

            HAL_RCCEx_GetPLL3ClockFreq(&pll3_clocks);
            frequency = pll3_clocks.PLL3_Q_Frequency;
            break;

          case RCC_ADF1CLKSOURCE_HCLK:

            frequency = HAL_RCC_GetHCLKFreq();
            break;

          case RCC_ADF1CLKSOURCE_PIN:

            frequency = EXTERNAL_SAI1_CLOCK_VALUE;
            break;

          case RCC_ADF1CLKSOURCE_MSIK:

            frequency = MSIRangeTable[(__HAL_RCC_GET_MSIK_RANGE() >> RCC_ICSCR1_MSIKRANGE_Pos)];
            break;

          default:

            frequency = 0U;
            break;
        }
        break;

      case RCC_PERIPHCLK_I2C1:
        /* Get the current I2C1 source */
        srcclk = __HAL_RCC_GET_I2C1_SOURCE();

        if (srcclk == RCC_I2C1CLKSOURCE_PCLK1)
        {
          frequency = HAL_RCC_GetPCLK1Freq();
        }
        else if (srcclk == RCC_I2C1CLKSOURCE_SYSCLK)
        {
          frequency = HAL_RCC_GetSysClockFreq();
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_I2C1CLKSOURCE_HSI))
        {
          frequency = HSI_VALUE;
        }
        /* Clock not enabled for I2C1 */
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_I2C2:
        /* Get the current I2C2 source */
        srcclk = __HAL_RCC_GET_I2C2_SOURCE();

        if (srcclk == RCC_I2C2CLKSOURCE_PCLK1)
        {
          frequency = HAL_RCC_GetPCLK1Freq();
        }
        else if (srcclk == RCC_I2C2CLKSOURCE_SYSCLK)
        {
          frequency = HAL_RCC_GetSysClockFreq();
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_I2C2CLKSOURCE_HSI))
        {
          frequency = HSI_VALUE;
        }
        /* Clock not enabled for I2C2 */
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_I2C3:
        /* Get the current I2C3 source */
        srcclk = __HAL_RCC_GET_I2C3_SOURCE();

        switch (srcclk)
        {
          case RCC_I2C3CLKSOURCE_PCLK3:
          {
            frequency = HAL_RCC_GetPCLK3Freq();
            break;
          }
          case RCC_I2C3CLKSOURCE_HSI:
          {
            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            else
            {
              frequency = 0U;
            }
            break;
          }
          case RCC_I2C3CLKSOURCE_SYSCLK:
          {
            frequency = HAL_RCC_GetSysClockFreq();
            break;
          }
          case RCC_I2C3CLKSOURCE_MSIK:
          {
            frequency = MSIRangeTable[(__HAL_RCC_GET_MSI_RANGE() >> RCC_ICSCR1_MSISRANGE_Pos)];
            break;
          }
          default:
          {
            frequency = 0U;
            break;
          }
        }
        break;

      case RCC_PERIPHCLK_I2C4:
        /* Get the current I2C4 source */
        srcclk = __HAL_RCC_GET_I2C4_SOURCE();

        if (srcclk == RCC_I2C4CLKSOURCE_PCLK1)
        {
          frequency = HAL_RCC_GetPCLK1Freq();
        }
        else if (srcclk == RCC_I2C4CLKSOURCE_SYSCLK)
        {
          frequency = HAL_RCC_GetSysClockFreq();
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_I2C4CLKSOURCE_HSI))
        {
          frequency = HSI_VALUE;
        }
        /* Clock not enabled for I2C4 */
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_LPTIM34:
        /* Get the current LPTIM34 source */
        srcclk = __HAL_RCC_GET_LPTIM34_SOURCE();

        if (srcclk == RCC_LPTIM34CLKSOURCE_MSIK)
        {
          frequency = MSIRangeTable[(__HAL_RCC_GET_MSIK_RANGE() >> RCC_ICSCR1_MSIKRANGE_Pos)];
        }
        else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSIRDY)) && (srcclk == RCC_LPTIM34CLKSOURCE_LSI))
        {
          frequency = LSI_VALUE;
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_LPTIM34CLKSOURCE_HSI))
        {
          frequency = HSI_VALUE;
        }
        else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_LPTIM34CLKSOURCE_LSE))
        {
          frequency = LSE_VALUE;
        }
        /* Clock not enabled for LPTIM34 */
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_LPTIM1:
        /* Get the current LPTIM1 source */
        srcclk = __HAL_RCC_GET_LPTIM1_SOURCE();

        if (srcclk == RCC_LPTIM1CLKSOURCE_MSIK)
        {
          frequency = MSIRangeTable[(__HAL_RCC_GET_MSIK_RANGE() >> RCC_ICSCR1_MSIKRANGE_Pos)];
        }
        else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSIRDY)) && (srcclk == RCC_LPTIM1CLKSOURCE_LSI))
        {
          frequency = LSI_VALUE;
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_LPTIM1CLKSOURCE_HSI))
        {
          frequency = HSI_VALUE;
        }
        else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_LPTIM1CLKSOURCE_LSE))
        {
          frequency = LSE_VALUE;
        }
        /* Clock not enabled for LPTIM1 */
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_LPTIM2:
        /* Get the current LPTIM2 source */
        srcclk = __HAL_RCC_GET_LPTIM2_SOURCE();

        if (srcclk == RCC_LPTIM2CLKSOURCE_PCLK1)
        {
          frequency = HAL_RCC_GetPCLK1Freq();
        }
        else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSIRDY)) && (srcclk == RCC_LPTIM2CLKSOURCE_LSI))
        {
          frequency = LSI_VALUE;
        }
        else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_LPTIM2CLKSOURCE_HSI))
        {
          frequency = HSI_VALUE;
        }
        else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_LPTIM2CLKSOURCE_LSE))
        {
          frequency = LSE_VALUE;
        }
        /* Clock not enabled for LPTIM2 */
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_FDCAN1:
        /* Get the current FDCAN1 kernel source */
        srcclk = __HAL_RCC_GET_FDCAN1_SOURCE();

        if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY)) && (srcclk == RCC_FDCAN1CLKSOURCE_HSE))
        {
          frequency = HSE_VALUE;
        }
        else if (srcclk == RCC_FDCAN1CLKSOURCE_PLL1) /* PLL1 ? */
        {
          HAL_RCCEx_GetPLL1ClockFreq(&pll1_clocks);
          frequency = pll1_clocks.PLL1_Q_Frequency;
        }
        else if (srcclk == RCC_FDCAN1CLKSOURCE_PLL2) /* PLL2 ? */
        {
          HAL_RCCEx_GetPLL2ClockFreq(&pll2_clocks);
          frequency = pll2_clocks.PLL2_P_Frequency;
        }
        /* Clock not enabled for FDCAN1 */
        else
        {
          frequency = 0U;
        }
        break;

      case RCC_PERIPHCLK_SPI1:
        /* Get the current SPI1 kernel source */
        srcclk = __HAL_RCC_GET_SPI1_SOURCE();
        switch (srcclk)
        {
          case RCC_SPI1CLKSOURCE_PCLK2:

            frequency = HAL_RCC_GetPCLK2Freq();
            break;

          case RCC_SPI1CLKSOURCE_SYSCLK:

            frequency = HAL_RCC_GetSysClockFreq();
            break;

          case RCC_SPI1CLKSOURCE_HSI:

            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            else
            {
              frequency = 0U;
            }
            break;

          case RCC_SPI1CLKSOURCE_MSIK:

            frequency = MSIRangeTable[(__HAL_RCC_GET_MSIK_RANGE() >> RCC_ICSCR1_MSIKRANGE_Pos)];
            break;

          default:

            frequency = 0U;
            break;

        }
        break;

      case RCC_PERIPHCLK_SPI2:
        /* Get the current SPI2 kernel source */
        srcclk = __HAL_RCC_GET_SPI2_SOURCE();
        switch (srcclk)
        {
          case RCC_SPI2CLKSOURCE_PCLK1:

            frequency = HAL_RCC_GetPCLK1Freq();
            break;

          case RCC_SPI2CLKSOURCE_SYSCLK:

            frequency = HAL_RCC_GetSysClockFreq();
            break;

          case RCC_SPI2CLKSOURCE_HSI:

            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            else
            {
              frequency = 0U;
            }
            break;

          case RCC_SPI2CLKSOURCE_MSIK:

            frequency = MSIRangeTable[(__HAL_RCC_GET_MSIK_RANGE() >> RCC_ICSCR1_MSIKRANGE_Pos)];
            break;

          default:

            frequency = 0U;
            break;

        }
        break;

      case RCC_PERIPHCLK_SPI3:
        /* Get the current SPI3 kernel source */
        srcclk = __HAL_RCC_GET_SPI3_SOURCE();
        switch (srcclk)
        {
          case RCC_SPI3CLKSOURCE_PCLK3:

            frequency = HAL_RCC_GetPCLK3Freq();
            break;

          case RCC_SPI3CLKSOURCE_SYSCLK:

            frequency = HAL_RCC_GetSysClockFreq();
            break;

          case RCC_SPI3CLKSOURCE_HSI:

            if (HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
            {
              frequency = HSI_VALUE;
            }
            else
            {
              frequency = 0U;
            }
            break;

          case RCC_SPI3CLKSOURCE_MSIK:

            frequency = MSIRangeTable[(__HAL_RCC_GET_MSIK_RANGE() >> RCC_ICSCR1_MSIKRANGE_Pos)];
            break;

          default:

            frequency = 0U;
            break;
        }
        break;

      case RCC_PERIPHCLK_OSPI:
        /* Get the current OSPI kernel source */
        srcclk = __HAL_RCC_GET_OSPI_SOURCE();

        switch (srcclk)
        {
          case RCC_OSPICLKSOURCE_PLL2:

            HAL_RCCEx_GetPLL2ClockFreq(&pll2_clocks);
            frequency = pll2_clocks.PLL2_Q_Frequency;
            break;

          case RCC_OSPICLKSOURCE_PLL1:

            HAL_RCCEx_GetPLL1ClockFreq(&pll1_clocks);
            frequency = pll1_clocks.PLL1_Q_Frequency;
            break;

          case RCC_OSPICLKSOURCE_SYSCLK:

            frequency = HAL_RCC_GetSysClockFreq();
            break;

          case RCC_OSPICLKSOURCE_MSIK:

            frequency = MSIRangeTable[(__HAL_RCC_GET_MSIK_RANGE() >> RCC_ICSCR1_MSIKRANGE_Pos)];
            break;

          default:

            frequency = 0U;
            break;
        }
        break;

      case RCC_PERIPHCLK_DAC1:
        /* Get the current DAC1 kernel source */
        srcclk = __HAL_RCC_GET_DAC1_SOURCE();
        /* Check if LSE is ready and if DAC1 clock selection is LSE */
        if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_DAC1CLKSOURCE_LSE))
        {
          frequency = LSE_VALUE;
        }
        /* Check if LSI is ready and if DAC1 clock selection is LSI */
        else if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSIRDY)) && (srcclk == RCC_DAC1CLKSOURCE_LSI))
        {
          frequency = LSI_VALUE;
        }
        /* Clock not enabled for DAC1*/
        else
        {
          frequency = 0U;
        }
        break;

      default:
         frequency = 0U;
        break;
    }
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
    activation or deactivation of MSI PLL-mode, PLL2, PLL3, LSE CSS,
    Low speed clock output and clock after wake-up from STOP mode.
@endverbatim
  * @{
  */

/**
  * @brief  Enable PLL2.
  * @param  PLL2Init  pointer to an RCC_PLL2InitTypeDef structure that
  *         contains the configuration information for the PLL2
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_EnablePLL2(RCC_PLL2InitTypeDef  *PLL2Init)
{
  uint32_t tickstart;
  HAL_StatusTypeDef status = HAL_OK;

  /* check for PLL2 Parameters used to output PLL2CLK */
  assert_param(IS_RCC_PLLSOURCE(PLL2Init->PLL2Source));
  assert_param(IS_RCC_PLLM_VALUE(PLL2Init->PLL2M));
  assert_param(IS_RCC_PLLN_VALUE(PLL2Init->PLL2N));
  assert_param(IS_RCC_PLLP_VALUE(PLL2Init->PLL2P));
  assert_param(IS_RCC_PLLQ_VALUE(PLL2Init->PLL2Q));
  assert_param(IS_RCC_PLLR_VALUE(PLL2Init->PLL2R));
  assert_param(IS_RCC_PLL2CLOCKOUT_VALUE(PLL2Init->PLL2ClockOut));

  /* Disable the PLL2 */
  __HAL_RCC_PLL2_DISABLE();

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till PLL2 is ready to be updated */
  while (READ_BIT(RCC->CR, RCC_CR_PLL2RDY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > PLL2_TIMEOUT_VALUE)
    {
      status = HAL_TIMEOUT;
      break;
    }
  }

  if (status == HAL_OK)
  {
    /* Make sure PLL2Source is ready */
    status = RCCEx_PLLSource_Enable(PLL2Init->PLL2Source);

    if (status == HAL_OK)
    {
      /* Configure the PLL2 clock source, multiplication factor N, */
      /* and division factors M, P, Q and R */
      __HAL_RCC_PLL2_CONFIG(PLL2Init->PLL2Source, PLL2Init->PLL2M, PLL2Init->PLL2N,
                            PLL2Init->PLL2P, PLL2Init->PLL2Q, PLL2Init->PLL2R);

      /* Disable PLL2FRACN  */
      __HAL_RCC_PLL2FRACN_DISABLE();

      /* Configure PLL  PLL2FRACN */
      __HAL_RCC_PLL2FRACN_CONFIG(PLL2Init->PLL2FRACN);

      /* Enable PLL2FRACN  */
      __HAL_RCC_PLL2FRACN_ENABLE();

      /* Select PLL2 input reference frequency range: VCI */
      __HAL_RCC_PLL2_VCIRANGE(PLL2Init->PLL2RGE);

      /* Configure the PLL2 Clock output(s) */
      __HAL_RCC_PLL2CLKOUT_ENABLE(PLL2Init->PLL2ClockOut);

      /* Enable the PLL2 again by setting PLL2ON to 1*/
      __HAL_RCC_PLL2_ENABLE();

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till PLL2 is ready */
      while (READ_BIT(RCC->CR, RCC_CR_PLL2RDY) == 0U)
      {
        if ((HAL_GetTick() - tickstart) > PLL2_TIMEOUT_VALUE)
        {
          status = HAL_TIMEOUT;
          break;
        }
      }
    }
  }
  return status;
}

/**
  * @brief  Disable PLL2.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_DisablePLL2(void)
{
  uint32_t tickstart;
  HAL_StatusTypeDef status = HAL_OK;

  /* Disable the PLL2 */
  __HAL_RCC_PLL2_DISABLE();

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till PLL2 is ready */
  while (READ_BIT(RCC->CR, RCC_CR_PLL2RDY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > PLL2_TIMEOUT_VALUE)
    {
      status = HAL_TIMEOUT;
      break;
    }
  }

  /* To save power disable the PLL2 Source, FRACN and Clock outputs */
  CLEAR_BIT(RCC->PLL2CFGR, RCC_PLL2CFGR_PLL2PEN | RCC_PLL2CFGR_PLL2QEN | RCC_PLL2CFGR_PLL2REN | RCC_PLL2CFGR_PLL2SRC | \
            RCC_PLL2CFGR_PLL2FRACEN);

  return status;
}

/**
  * @brief  Enable PLL3.
  * @param  PLL3Init  pointer to an RCC_PLL3InitTypeDef structure that
  *         contains the configuration information for the PLL3
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_EnablePLL3(RCC_PLL3InitTypeDef  *PLL3Init)
{
  uint32_t tickstart;
  HAL_StatusTypeDef status = HAL_OK;

  /* check for PLL3 Parameters used to output PLL3CLK */
  assert_param(IS_RCC_PLLSOURCE(PLL3Init->PLL3Source));
  assert_param(IS_RCC_PLLM_VALUE(PLL3Init->PLL3M));
  assert_param(IS_RCC_PLLN_VALUE(PLL3Init->PLL3N));
  assert_param(IS_RCC_PLLP_VALUE(PLL3Init->PLL3P));
  assert_param(IS_RCC_PLL3CLOCKOUT_VALUE(PLL3Init->PLL3ClockOut));

  /* Disable the PLL3 */
  __HAL_RCC_PLL3_DISABLE();

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till PLL3 is ready to be updated */
  while (READ_BIT(RCC->CR, RCC_CR_PLL3RDY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > PLL3_TIMEOUT_VALUE)
    {
      status = HAL_TIMEOUT;
      break;
    }
  }

  if (status == HAL_OK)
  {
    /* Make sure PLL3Source is ready */
    status = RCCEx_PLLSource_Enable(PLL3Init->PLL3Source);

    if (status == HAL_OK)
    {
      /* Configure the PLL3 clock source, multiplication factor N, */
      /* and division factors M and P */
      __HAL_RCC_PLL3_CONFIG(PLL3Init->PLL3Source, PLL3Init->PLL3M, PLL3Init->PLL3N, PLL3Init->PLL3P, PLL3Init->PLL3Q, \
                            PLL3Init->PLL3R);

      /* Disable PLL3FRACN . */
      __HAL_RCC_PLL3FRACN_DISABLE();

      /* Configure PLL  PLL3FRACN */
      __HAL_RCC_PLL3FRACN_CONFIG(PLL3Init->PLL3FRACN);

      /* Enable PLL3FRACN . */
      __HAL_RCC_PLL3FRACN_ENABLE();

      /* Select PLL3 input reference frequency range: VCI */
      __HAL_RCC_PLL3_VCIRANGE(PLL3Init->PLL3RGE);

      /* Configure the PLL3 Clock output(s) */
      __HAL_RCC_PLL3CLKOUT_ENABLE(PLL3Init->PLL3ClockOut);

      /* Enable the PLL3 again by setting PLL3ON to 1*/
      __HAL_RCC_PLL3_ENABLE();

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till PLL3 is ready */
      while (READ_BIT(RCC->CR, RCC_CR_PLL3RDY) == 0U)
      {
        if ((HAL_GetTick() - tickstart) > PLL3_TIMEOUT_VALUE)
        {
          status = HAL_TIMEOUT;
          break;
        }
      }
    }
  }
  return status;
}

/**
  * @brief  Disable PLL3.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_DisablePLL3(void)
{
  uint32_t tickstart;
  HAL_StatusTypeDef status = HAL_OK;

  /* Disable the PLL3 */
  __HAL_RCC_PLL3_DISABLE();

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till PLL3 is ready */
  while (READ_BIT(RCC->CR, RCC_CR_PLL3RDY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > PLL3_TIMEOUT_VALUE)
    {
      status = HAL_TIMEOUT;
      break;
    }
  }

  /* To save power disable the PLL3 Source and Clock outputs */
  CLEAR_BIT(RCC->PLL3CFGR, RCC_PLL3CFGR_PLL3PEN | RCC_PLL3CFGR_PLL3QEN | RCC_PLL3CFGR_PLL3REN | RCC_PLL3CFGR_PLL3SRC | \
            RCC_PLL3CFGR_PLL3FRACEN);

  return status;
}

/**
  * @brief Select which MSI output clock uses the PLL mode.
  * @note  Prior to disable PLL-mode (MSIPLLEN = 0) before call HAL_RCCEx_EnableMSIPLLModeSelection.
  * @note  The MSI kernel clock output uses the same oscillator source than the MSI system
  *        clock output, then the PLL mode is applied to the both clocks outputs.
  * @param MSIPLLModeSelection specifies which MSI output clock uses the PLL mode.
  *          This parameter can be one of the following values:
  *            @arg @ref RCC_MSISPLL_MODE_SEL  PLL mode applied to MSIS (MSI system) clock output
  *            @arg @ref RCC_MSIKPLL_MODE_SEL  PLL mode applied to MSIK (MSI kernel) clock output
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_EnableMSIPLLModeSelection(uint32_t MSIPLLModeSelection)
{
  HAL_StatusTypeDef status = HAL_ERROR;

  assert_param(IS_RCC_MSIPLLMODE_SELECT(MSIPLLModeSelection));
  if (READ_BIT(RCC->CR, RCC_CR_MSIPLLEN) == 0U)
  {
    /* This bit is used only if PLL mode is disabled (MSIPLLEN = 0) */
    if (MSIPLLModeSelection == RCC_MSISPLL_MODE_SEL)
    {
      SET_BIT(RCC->CR, RCC_CR_MSIPLLSEL);
    }
    else
    {
      CLEAR_BIT(RCC->CR, RCC_CR_MSIPLLSEL);
    }
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief Enable the fast PLL mode start-up of the MSI clock
  * @note  Prior to enable PLL-mode (MSIPLLEN = 1) before call HAL_RCCEx_EnableMSIPLLFastStartup.
  * @note  The fast start-up feature is not active the first time the PLL mode is selected. The
  *        fast start-up is active when the MSI in PLL mode returns from switch off.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_EnableMSIPLLFastStartup(void)
{
  HAL_StatusTypeDef status = HAL_ERROR;

  if (READ_BIT(RCC->CR, RCC_CR_MSIPLLEN) == RCC_CR_MSIPLLEN)
  {
    /* This bit is used only if PLL mode is selected (MSIPLLEN = 1) */
    SET_BIT(RCC->CR, RCC_CR_MSIPLLFAST);
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief Disable the fast PLL mode start-up of the MSI clock
  * @note  the MSI fast startup mode disabled only when PLL-mode is enabled
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_DisableMSIPLLFastStartup(void)
{
  HAL_StatusTypeDef status = HAL_ERROR;

  if (READ_BIT(RCC->CR, RCC_CR_MSIPLLEN) == RCC_CR_MSIPLLEN)
  {
    /* This bit is used only if PLL mode is selected (MSIPLLEN = 1) */
    CLEAR_BIT(RCC->CR, RCC_CR_MSIPLLFAST);
    status = HAL_OK;
  }
  return status;
}

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
  * @brief  Configure the oscillator Kernel clock source for wakeup from Stop
  * @param  WakeUpClk: Kernel Wakeup clock
  *         This parameter can be one of the following values:
  *            @arg RCC_STOP_KERWAKEUPCLOCK_MSI: MSI oscillator selection
  *            @arg RCC_STOP_KERWAKEUPCLOCK_HSI: HSI oscillator selection
  * @retval None
  */
void HAL_RCCEx_KerWakeUpStopCLKConfig(uint32_t WakeUpClk)
{
  assert_param(IS_RCC_STOP_KERWAKEUPCLOCK(WakeUpClk));

  __HAL_RCC_KERWAKEUPSTOP_CLK_CONFIG(WakeUpClk);
}

/**
  * @brief  Configure the MSI range after standby mode.
  * @note   After Standby its frequency can be selected between 3 possible values (1, 3.072 or 4 MHz).
  * @param  MSIRange  MSI range
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_MSIRANGE_4  Range 4 around 4 MHz (reset value)
  *            @arg @ref RCC_MSIRANGE_5  Range 5 around 2 MHz
  *            @arg @ref RCC_MSIRANGE_6  Range 6 around 1.5 MHz
  *            @arg @ref RCC_MSIRANGE_7  Range 7 around 1 MHz
  *            @arg @ref RCC_MSIRANGE_8  Range 8 around 3.072 MHz
  * @retval None
  */
void HAL_RCCEx_StandbyMSIRangeConfig(uint32_t MSIRange)
{
  assert_param(IS_RCC_MSI_STANDBY_CLOCK_RANGE(MSIRange));

  __HAL_RCC_MSI_STANDBY_RANGE_CONFIG(MSIRange);
}

/**
  * @brief  Enable the LSE Clock Security System.
  * @note   Prior to enable the LSE Clock Security System, LSE oscillator is to be enabled
  *         with HAL_RCC_OscConfig() and the LSE oscillator clock is to be selected as RTC
  *         clock with HAL_RCCEx_PeriphCLKConfig().
  * @retval None
  */
void HAL_RCCEx_EnableLSECSS(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief  Disable the LSE Clock Security System.
  * @note   LSE Clock Security System can only be disabled after a LSE failure detection.
  * @retval None
  */
void HAL_RCCEx_DisableLSECSS(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSECSSON);
}

/**
  * @brief Handle the RCC LSE Clock Security System interrupt request.
  * @retval None
  */
void HAL_RCCEx_LSECSS_IRQHandler(void)
{
  if (READ_BIT(RCC->BDCR, RCC_BDCR_LSECSSD) != 0U)
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
  GPIO_InitTypeDef gpio_initstruct;
  FlagStatus       pwrclkchanged = RESET;
  FlagStatus       backupchanged = RESET;

  /* Check the parameters */
  assert_param(IS_RCC_LSCOSOURCE(LSCOSource));

  /* LSCO Pin Clock Enable */
  LSCO_CLK_ENABLE();

  /* Configure the LSCO pin in analog mode */
  gpio_initstruct.Pin = LSCO_PIN;
  gpio_initstruct.Mode = GPIO_MODE_ANALOG;
  gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
  gpio_initstruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LSCO_GPIO_PORT, &gpio_initstruct);

  /* Update LSCOSEL clock source in Backup Domain control register */
  if (__HAL_RCC_PWR_IS_CLK_DISABLED())
  {
    __HAL_RCC_PWR_CLK_ENABLE();
    pwrclkchanged = SET;
  }
  if (HAL_IS_BIT_CLR(PWR->DBPR, PWR_DBPR_DBP))
  {
    HAL_PWR_EnableBkUpAccess();
    backupchanged = SET;
  }

  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSCOSEL | RCC_BDCR_LSCOEN, LSCOSource | RCC_BDCR_LSCOEN);

  if (backupchanged == SET)
  {
    HAL_PWR_DisableBkUpAccess();
  }
  if (pwrclkchanged == SET)
  {
    __HAL_RCC_PWR_CLK_DISABLE();
  }
}

/**
  * @brief  Disable the Low Speed clock output.
  * @retval None
  */
void HAL_RCCEx_DisableLSCO(void)
{
  FlagStatus       pwrclkchanged = RESET;
  FlagStatus       backupchanged = RESET;

  /* Update LSCOEN bit in Backup Domain control register */
  if (__HAL_RCC_PWR_IS_CLK_DISABLED())
  {
    __HAL_RCC_PWR_CLK_ENABLE();
    pwrclkchanged = SET;
  }
  if (HAL_IS_BIT_CLR(PWR->DBPR, PWR_DBPR_DBP))
  {
    /* Enable access to the backup domain */
    HAL_PWR_EnableBkUpAccess();
    backupchanged = SET;
  }

  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSCOEN);

  /* Restore previous configuration */
  if (backupchanged == SET)
  {
    /* Disable access to the backup domain */
    HAL_PWR_DisableBkUpAccess();
  }
  if (pwrclkchanged == SET)
  {
    __HAL_RCC_PWR_CLK_DISABLE();
  }
}

/**
  * @brief  Enable the PLL-mode of the MSI.
  * @note   Prior to enable the PLL-mode of the MSI for automatic hardware
  *         calibration LSE oscillator is to be enabled with HAL_RCC_OscConfig().
  * @retval None
  */
void HAL_RCCEx_EnableMSIPLLMode(void)
{
  SET_BIT(RCC->CR, RCC_CR_MSIPLLEN);
}

/**
  * @brief  Disable the PLL-mode of the MSI.
  * @note   PLL-mode of the MSI is automatically reset when LSE oscillator is disabled.
  * @retval None
  */
void HAL_RCCEx_DisableMSIPLLMode(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_MSIPLLEN);
}

/**
  * @}
  */

#if defined(CRS)

/** @defgroup RCCEx_Exported_Functions_Group3 Extended Clock Recovery System Control functions
  * @brief  Extended Clock Recovery System Control functions
  *
@verbatim
 ===============================================================================
                ##### Extended Clock Recovery System Control functions  #####
 ===============================================================================
    [..]
      For devices with Clock Recovery System feature (CRS), RCC Extension HAL driver can be used as follows:

      (#) In System clock config, HSI48 needs to be enabled

      (#) Enable CRS clock in IP MSP init which will use CRS functions

      (#) Call CRS functions as follows:
          (##) Prepare synchronization configuration necessary for HSI48 calibration
              (+++) Default values can be set for frequency Error Measurement (reload and error limit)
                        and also HSI48 oscillator smooth trimming.
              (+++) Macro __HAL_RCC_CRS_RELOADVALUE_CALCULATE can be also used to calculate
                        directly reload value with target and sychronization frequencies values
          (##) Call function HAL_RCCEx_CRSConfig which
              (+++) Resets CRS registers to their default values.
              (+++) Configures CRS registers with synchronization configuration
              (+++) Enables automatic calibration and frequency error counter feature
           Note: When using USB LPM (Link Power Management) and the device is in Sleep mode, the
           periodic USB SOF will not be generated by the host. No SYNC signal will therefore be
           provided to the CRS to calibrate the HSI48 on the run. To guarantee the required clock
           precision after waking up from Sleep mode, the LSE or reference clock on the GPIOs
           should be used as SYNC signal.

          (##) A polling function is provided to wait for complete synchronization
              (+++) Call function HAL_RCCEx_CRSWaitSynchronization()
              (+++) According to CRS status, user can decide to adjust again the calibration or continue
                        application if synchronization is OK

      (#) User can retrieve information related to synchronization in calling function
            HAL_RCCEx_CRSGetSynchronizationInfo()

      (#) Regarding synchronization status and synchronization information, user can try a new calibration
           in changing synchronization configuration and call again HAL_RCCEx_CRSConfig.
           Note: When the SYNC event is detected during the downcounting phase (before reaching the zero value),
           it means that the actual frequency is lower than the target (and so, that the TRIM value should be
           incremented), while when it is detected during the upcounting phase it means that the actual frequency
           is higher (and that the TRIM value should be decremented).

      (#) In interrupt mode, user can resort to the available macros (__HAL_RCC_CRS_XXX_IT). Interrupts will go
          through CRS Handler (CRS_IRQn/CRS_IRQHandler)
              (++) Call function HAL_RCCEx_CRSConfig()
              (++) Enable CRS_IRQn (thanks to NVIC functions)
              (++) Enable CRS interrupt (__HAL_RCC_CRS_ENABLE_IT)
              (++) Implement CRS status management in the following user callbacks called from
                   HAL_RCCEx_CRS_IRQHandler():
                   (+++) HAL_RCCEx_CRS_SyncOkCallback()
                   (+++) HAL_RCCEx_CRS_SyncWarnCallback()
                   (+++) HAL_RCCEx_CRS_ExpectedSyncCallback()
                   (+++) HAL_RCCEx_CRS_ErrorCallback()

      (#) To force a SYNC EVENT, user can use the function HAL_RCCEx_CRSSoftwareSynchronizationGenerate().
          This function can be called before calling HAL_RCCEx_CRSConfig (for instance in Systick handler)

@endverbatim
  * @{
  */

/**
  * @brief  Start automatic synchronization for polling mode
  * @param  pInit Pointer on RCC_CRSInitTypeDef structure
  * @retval None
  */
void HAL_RCCEx_CRSConfig(const RCC_CRSInitTypeDef *const pInit)
{
  uint32_t value;

  /* Check the parameters */
  assert_param(IS_RCC_CRS_SYNC_DIV(pInit->Prescaler));
  assert_param(IS_RCC_CRS_SYNC_SOURCE(pInit->Source));
  assert_param(IS_RCC_CRS_SYNC_POLARITY(pInit->Polarity));
  assert_param(IS_RCC_CRS_RELOADVALUE(pInit->ReloadValue));
  assert_param(IS_RCC_CRS_ERRORLIMIT(pInit->ErrorLimitValue));
  assert_param(IS_RCC_CRS_HSI48CALIBRATION(pInit->HSI48CalibrationValue));

  /* CONFIGURATION */

  /* Before configuration, reset CRS registers to their default values*/
  __HAL_RCC_CRS_FORCE_RESET();
  __HAL_RCC_CRS_RELEASE_RESET();

  /* Set the SYNCDIV[2:0] bits according to Prescaler value */
  /* Set the SYNCSRC[1:0] bits according to Source value */
  /* Set the SYNCSPOL bit according to Polarity value */
  value = (pInit->Prescaler | pInit->Source | pInit->Polarity);
  /* Set the RELOAD[15:0] bits according to ReloadValue value */
  value |= pInit->ReloadValue;
  /* Set the FELIM[7:0] bits according to ErrorLimitValue value */
  value |= (pInit->ErrorLimitValue << CRS_CFGR_FELIM_Pos);
  WRITE_REG(CRS->CFGR, value);

  /* Adjust HSI48 oscillator smooth trimming */
  /* Set the TRIM[5:0] bits according to RCC_CRS_HSI48CalibrationValue value */
  MODIFY_REG(CRS->CR, CRS_CR_TRIM, (pInit->HSI48CalibrationValue << CRS_CR_TRIM_Pos));

  /* START AUTOMATIC SYNCHRONIZATION*/

  /* Enable Automatic trimming & Frequency error counter */
  SET_BIT(CRS->CR, CRS_CR_AUTOTRIMEN | CRS_CR_CEN);
}

/**
  * @brief  Generate the software synchronization event
  * @retval None
  */
void HAL_RCCEx_CRSSoftwareSynchronizationGenerate(void)
{
  SET_BIT(CRS->CR, CRS_CR_SWSYNC);
}

/**
  * @brief  Return synchronization info
  * @param  pSynchroInfo Pointer on RCC_CRSSynchroInfoTypeDef structure
  * @retval None
  */
void HAL_RCCEx_CRSGetSynchronizationInfo(RCC_CRSSynchroInfoTypeDef *pSynchroInfo)
{
  /* Check the parameter */
  assert_param(pSynchroInfo != (void *) NULL);

  /* Get the reload value */
  pSynchroInfo->ReloadValue = (uint32_t)(READ_BIT(CRS->CFGR, CRS_CFGR_RELOAD));

  /* Get HSI48 oscillator smooth trimming */
  pSynchroInfo->HSI48CalibrationValue = (uint32_t)(READ_BIT(CRS->CR, CRS_CR_TRIM) >> CRS_CR_TRIM_Pos);

  /* Get Frequency error capture */
  pSynchroInfo->FreqErrorCapture = (uint32_t)(READ_BIT(CRS->ISR, CRS_ISR_FECAP) >> CRS_ISR_FECAP_Pos);

  /* Get Frequency error direction */
  pSynchroInfo->FreqErrorDirection = (uint32_t)(READ_BIT(CRS->ISR, CRS_ISR_FEDIR));
}

/**
  * @brief Wait for CRS Synchronization status.
  * @param Timeout  Duration of the timeout
  * @note  Timeout is based on the maximum time to receive a SYNC event based on synchronization
  *        frequency.
  * @note    If Timeout set to HAL_MAX_DELAY, HAL_TIMEOUT will be never returned.
  * @retval Combination of Synchronization status
  *          This parameter can be a combination of the following values:
  *            @arg @ref RCC_CRS_TIMEOUT
  *            @arg @ref RCC_CRS_SYNCOK
  *            @arg @ref RCC_CRS_SYNCWARN
  *            @arg @ref RCC_CRS_SYNCERR
  *            @arg @ref RCC_CRS_SYNCMISS
  *            @arg @ref RCC_CRS_TRIMOVF
  */
uint32_t HAL_RCCEx_CRSWaitSynchronization(uint32_t Timeout)
{
  uint32_t crsstatus = RCC_CRS_NONE;
  uint32_t tickstart;

  /* Get timeout */
  tickstart = HAL_GetTick();

  /* Wait for CRS flag or timeout detection */
  do
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
      {
        crsstatus = RCC_CRS_TIMEOUT;
      }
    }
    /* Check CRS SYNCOK flag  */
    if (__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCOK))
    {
      /* CRS SYNC event OK */
      crsstatus |= RCC_CRS_SYNCOK;

      /* Clear CRS SYNC event OK bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCOK);
    }

    /* Check CRS SYNCWARN flag  */
    if (__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCWARN))
    {
      /* CRS SYNC warning */
      crsstatus |= RCC_CRS_SYNCWARN;

      /* Clear CRS SYNCWARN bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCWARN);
    }

    /* Check CRS TRIM overflow flag  */
    if (__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_TRIMOVF))
    {
      /* CRS SYNC Error */
      crsstatus |= RCC_CRS_TRIMOVF;

      /* Clear CRS Error bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_TRIMOVF);
    }

    /* Check CRS Error flag  */
    if (__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCERR))
    {
      /* CRS SYNC Error */
      crsstatus |= RCC_CRS_SYNCERR;

      /* Clear CRS Error bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCERR);
    }

    /* Check CRS SYNC Missed flag  */
    if (__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCMISS))
    {
      /* CRS SYNC Missed */
      crsstatus |= RCC_CRS_SYNCMISS;

      /* Clear CRS SYNC Missed bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCMISS);
    }

    /* Check CRS Expected SYNC flag  */
    if (__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_ESYNC))
    {
      /* frequency error counter reached a zero value */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_ESYNC);
    }
  } while (RCC_CRS_NONE == crsstatus);

  return crsstatus;
}

/**
  * @brief Handle the Clock Recovery System interrupt request.
  * @retval None
  */
void HAL_RCCEx_CRS_IRQHandler(void)
{
  uint32_t crserror = RCC_CRS_NONE;
  /* Get current IT flags and IT sources values */
  uint32_t itflags = READ_REG(CRS->ISR);
  uint32_t itsources = READ_REG(CRS->CR);

  /* Check CRS SYNCOK flag  */
  if (((itflags & RCC_CRS_FLAG_SYNCOK) != 0U) && ((itsources & RCC_CRS_IT_SYNCOK) != 0U))
  {
    /* Clear CRS SYNC event OK flag */
    WRITE_REG(CRS->ICR, CRS_ICR_SYNCOKC);

    /* user callback */
    HAL_RCCEx_CRS_SyncOkCallback();
  }
  /* Check CRS SYNCWARN flag  */
  else if (((itflags & RCC_CRS_FLAG_SYNCWARN) != 0U) && ((itsources & RCC_CRS_IT_SYNCWARN) != 0U))
  {
    /* Clear CRS SYNCWARN flag */
    WRITE_REG(CRS->ICR, CRS_ICR_SYNCWARNC);

    /* user callback */
    HAL_RCCEx_CRS_SyncWarnCallback();
  }
  /* Check CRS Expected SYNC flag  */
  else if (((itflags & RCC_CRS_FLAG_ESYNC) != 0U) && ((itsources & RCC_CRS_IT_ESYNC) != 0U))
  {
    /* frequency error counter reached a zero value */
    WRITE_REG(CRS->ICR, CRS_ICR_ESYNCC);

    /* user callback */
    HAL_RCCEx_CRS_ExpectedSyncCallback();
  }
  /* Check CRS Error flags  */
  else
  {
    if (((itflags & RCC_CRS_FLAG_ERR) != 0U) && ((itsources & RCC_CRS_IT_ERR) != 0U))
    {
      if ((itflags & RCC_CRS_FLAG_SYNCERR) != 0U)
      {
        crserror |= RCC_CRS_SYNCERR;
      }
      if ((itflags & RCC_CRS_FLAG_SYNCMISS) != 0U)
      {
        crserror |= RCC_CRS_SYNCMISS;
      }
      if ((itflags & RCC_CRS_FLAG_TRIMOVF) != 0U)
      {
        crserror |= RCC_CRS_TRIMOVF;
      }

      /* Clear CRS Error flags */
      WRITE_REG(CRS->ICR, CRS_ICR_ERRC);

      /* user error callback */
      HAL_RCCEx_CRS_ErrorCallback(crserror);
    }
  }
}

/**
  * @brief  RCCEx Clock Recovery System SYNCOK interrupt callback.
  * @retval none
  */
__weak void HAL_RCCEx_CRS_SyncOkCallback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the @ref HAL_RCCEx_CRS_SyncOkCallback should be implemented in the user file
   */
}

/**
  * @brief  RCCEx Clock Recovery System SYNCWARN interrupt callback.
  * @retval none
  */
__weak void HAL_RCCEx_CRS_SyncWarnCallback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the @ref HAL_RCCEx_CRS_SyncWarnCallback should be implemented in the user file
   */
}

/**
  * @brief  RCCEx Clock Recovery System Expected SYNC interrupt callback.
  * @retval none
  */
__weak void HAL_RCCEx_CRS_ExpectedSyncCallback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the @ref HAL_RCCEx_CRS_ExpectedSyncCallback should be implemented in the user file
   */
}

/**
  * @brief  RCCEx Clock Recovery System Error interrupt callback.
  * @param  Error Combination of Error status.
  *         This parameter can be a combination of the following values:
  *           @arg @ref RCC_CRS_SYNCERR
  *           @arg @ref RCC_CRS_SYNCMISS
  *           @arg @ref RCC_CRS_TRIMOVF
  * @retval none
  */
__weak void HAL_RCCEx_CRS_ErrorCallback(uint32_t Error)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Error);

  /* NOTE : This function should not be modified, when the callback is needed,
            the @ref HAL_RCCEx_CRS_ErrorCallback should be implemented in the user file
   */
}

/**
  * @}
  */

#endif /* CRS */

/**
  * @}
  */

/** @addtogroup RCCEx_Private_Functions
  * @{
  */
/**
  * @brief  Configure the PLL 1 source clock.
  * @param  PllSource  PLL1 source clock it can be :
  *                             RCC_PLLSOURCE_NONE
  *                             RCC_PLLSOURCE_MSI
  *                             RCC_PLLSOURCE_HSI
  *                             RCC_PLLSOURCE_HSE
  *
  * @retval HAL status
  */
static HAL_StatusTypeDef RCCEx_PLLSource_Enable(uint32_t PllSource)
{
  uint32_t tickstart;
  HAL_StatusTypeDef status = HAL_OK;

  switch (PllSource)
  {
    case RCC_PLLSOURCE_MSI:
      /* Check whether MSI in not ready and enable it */
      if (READ_BIT(RCC->CR, RCC_CR_MSISRDY) == 0U)
      {
        /* Enable the Internal Multi Speed oscillator (MSI). */
        __HAL_RCC_MSI_ENABLE();

        /* Get timeout */
        tickstart = HAL_GetTick();

        /* Wait till MSI is ready */
        while (READ_BIT(RCC->CR, RCC_CR_MSISRDY) == 0U)
        {
          if ((HAL_GetTick() - tickstart) > MSI_TIMEOUT_VALUE)
          {
            status = HAL_TIMEOUT;
            break;
          }
        }
      }
      break;

    case RCC_PLLSOURCE_HSI:
      /* Check whether HSI in not ready and enable it */
      if (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == 0U)
      {
        /* Enable the Internal High Speed oscillator (HSI) */
        __HAL_RCC_HSI_ENABLE();

        /* Get timeout */
        tickstart = HAL_GetTick();

        /* Wait till MSI is ready */
        while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == 0U)
        {
          if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
          {
            status = HAL_TIMEOUT;
            break;
          }
        }
      }
      break;

    case RCC_PLLSOURCE_HSE:
      /* Check whether HSE in not ready and enable it */
      if (READ_BIT(RCC->CR, RCC_CR_HSERDY) == 0U)
      {
        /* Enable the External High Speed oscillator (HSE) */
        SET_BIT(RCC->CR, RCC_CR_HSEON);

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSE is ready */
        while (READ_BIT(RCC->CR, RCC_CR_HSERDY) == 0U)
        {
          if ((HAL_GetTick() - tickstart) > HSE_TIMEOUT_VALUE)
          {
            status = HAL_TIMEOUT;
            break;
          }
        }
      }
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

/**
  * @brief  Configure the PLL2 VCI ranges, multiplication and division factors and enable it
  * @param  pll2: Pointer to an RCC_PLL2InitTypeDef structure that
  *         contains the configuration parameters as well as VCI clock ranges.
  * @note   PLL2 is temporary disable to apply new parameters
  *
  * @retval HAL status
  */
static HAL_StatusTypeDef RCCEx_PLL2_Config(RCC_PLL2InitTypeDef *pll2)
{

  uint32_t tickstart;
  assert_param(IS_RCC_PLLSOURCE(pll2->PLL2Source));
  assert_param(IS_RCC_PLLM_VALUE(pll2->PLL2M));
  assert_param(IS_RCC_PLLN_VALUE(pll2->PLL2N));
  assert_param(IS_RCC_PLLP_VALUE(pll2->PLL2P));
  assert_param(IS_RCC_PLLQ_VALUE(pll2->PLL2Q));
  assert_param(IS_RCC_PLLR_VALUE(pll2->PLL2R));

  /* Disable  PLL2 */
  __HAL_RCC_PLL2_DISABLE();

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till PLL is ready */
  while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLL2RDY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > PLL2_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Configure PLL2 multiplication and division factors */
  __HAL_RCC_PLL2_CONFIG(pll2->PLL2Source,
                        pll2->PLL2M,
                        pll2->PLL2N,
                        pll2->PLL2P,
                        pll2->PLL2Q,
                        pll2->PLL2R);

  /* Select PLL2 input reference frequency range: VCI */
  __HAL_RCC_PLL2_VCIRANGE(pll2->PLL2RGE);

  /* Configure the PLL2 Clock output(s) */
  __HAL_RCC_PLL2CLKOUT_ENABLE(pll2->PLL2ClockOut);

  /* Disable PLL2FRACN  */
  __HAL_RCC_PLL2FRACN_DISABLE();

  /* Configures PLL2 clock Fractional Part Of The Multiplication Factor */
  __HAL_RCC_PLL2FRACN_CONFIG(pll2->PLL2FRACN);

  /* Enable PLL2FRACN  */
  __HAL_RCC_PLL2FRACN_ENABLE();

  /* Enable  PLL2 */
  __HAL_RCC_PLL2_ENABLE();

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till PLL2 is ready */
  while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLL2RDY) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > PLL2_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }
  return HAL_OK;

}

/**
  * @brief  Configure the parameters N & P & optionally M of PLL3 and enable PLL3 output clock(s).
  * @param  pll3  pointer to an RCC_PLL3InitTypeDef structure that
  *         contains the configuration parameters N & P & optionally M as well as PLL3 output clock(s)
  * @note   PLL3 is temporary disable to apply new parameters
  * @retval HAL status
  */
static HAL_StatusTypeDef RCCEx_PLL3_Config(RCC_PLL3InitTypeDef *pll3)
{
  uint32_t tickstart;
  assert_param(IS_RCC_PLLSOURCE(pll3->PLL3Source));
  assert_param(IS_RCC_PLLM_VALUE(pll3->PLL3M));
  assert_param(IS_RCC_PLLN_VALUE(pll3->PLL3N));
  assert_param(IS_RCC_PLLP_VALUE(pll3->PLL3P));
  assert_param(IS_RCC_PLLQ_VALUE(pll3->PLL3Q));
  assert_param(IS_RCC_PLLR_VALUE(pll3->PLL3R));

  /* Disable  PLL3 */
  __HAL_RCC_PLL3_DISABLE();

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till PLL is ready */
  while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLL3RDY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > PLL3_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Configure PLL3 multiplication and division factors */
  __HAL_RCC_PLL3_CONFIG(pll3->PLL3Source,
                        pll3->PLL3M,
                        pll3->PLL3N,
                        pll3->PLL3P,
                        pll3->PLL3Q,
                        pll3->PLL3R);

  /* Select PLL3 input reference frequency range: VCI */
  __HAL_RCC_PLL3_VCIRANGE(pll3->PLL3RGE);

  /* Configure the PLL3 Clock output(s) */
  __HAL_RCC_PLL3CLKOUT_ENABLE(pll3->PLL3ClockOut);

  /* Disable PLL3FRACN  */
  __HAL_RCC_PLL3FRACN_DISABLE();

  /* Configures PLL3 clock Fractional Part Of The Multiplication Factor */
  __HAL_RCC_PLL3FRACN_CONFIG(pll3->PLL3FRACN);

  /* Enable PLL3FRACN  */
  __HAL_RCC_PLL3FRACN_ENABLE();

  /* Enable  PLL3 */
  __HAL_RCC_PLL3_ENABLE();

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till PLL3 is ready */
  while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLL3RDY) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > PLL3_TIMEOUT_VALUE)
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

/**
  * @}
  */

