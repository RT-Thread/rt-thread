/**
  ******************************************************************************
  * @file    stm32g4xx_hal_rcc_ex.c
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
#include "stm32g4xx_hal.h"

/** @addtogroup STM32G4xx_HAL_Driver
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
#define PLL_TIMEOUT_VALUE        2U                /* 2 ms (minimum Tick + 1) */

#define DIVIDER_P_UPDATE          0U
#define DIVIDER_Q_UPDATE          1U
#define DIVIDER_R_UPDATE          2U

#define __LSCO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define LSCO_GPIO_PORT            GPIOA
#define LSCO_PIN                  GPIO_PIN_2
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCCEx_Private_Functions RCCEx Private Functions
 * @{
 */

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
  * @param  PeriphClkInit  pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         contains a field PeriphClockSelection which can be a combination of the following values:
  *            @arg @ref RCC_PERIPHCLK_RTC  RTC peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART1  USART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART2  USART2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART3  USART3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_UART4  UART4 peripheral clock (only for devices with UART4)
  *            @arg @ref RCC_PERIPHCLK_UART5  UART5 peripheral clock (only for devices with UART5)
  *            @arg @ref RCC_PERIPHCLK_LPUART1  LPUART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C1  I2C1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C2  I2C2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C3  I2C3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C4  I2C4 peripheral clock (only for devices with I2C4)
  *            @arg @ref RCC_PERIPHCLK_LPTIM1  LPTIM1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SAI1  SAI1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2S  I2S peripheral clock
  *            @arg @ref RCC_PERIPHCLK_FDCAN  FDCAN peripheral clock (only for devices with FDCAN)
  *            @arg @ref RCC_PERIPHCLK_RNG  RNG peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USB  USB peripheral clock (only for devices with USB)
  *            @arg @ref RCC_PERIPHCLK_ADC12  ADC1 and ADC2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADC345  ADC3, ADC4 and ADC5 peripheral clock (only for devices with ADC3, ADC4, ADC5)
  *            @arg @ref RCC_PERIPHCLK_QSPI  QuadSPI peripheral clock (only for devices with QuadSPI)
  *
  * @note   Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select
  *         the RTC clock source: in this case the access to Backup domain is enabled.
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tmpregister;
  uint32_t tickstart;
  HAL_StatusTypeDef ret = HAL_OK;      /* Intermediate status */
  HAL_StatusTypeDef status = HAL_OK;   /* Final status */

  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClkInit->PeriphClockSelection));

  /*-------------------------- RTC clock source configuration ----------------------*/
  if((PeriphClkInit->PeriphClockSelection & RCC_PERIPHCLK_RTC) == RCC_PERIPHCLK_RTC)
  {
    FlagStatus       pwrclkchanged = RESET;
    
    /* Check for RTC Parameters used to output RTCCLK */
    assert_param(IS_RCC_RTCCLKSOURCE(PeriphClkInit->RTCClockSelection));

    /* Enable Power Clock */
    if(__HAL_RCC_PWR_IS_CLK_DISABLED())
    {
      __HAL_RCC_PWR_CLK_ENABLE();
      pwrclkchanged = SET;
    }
      
    /* Enable write access to Backup domain */
    SET_BIT(PWR->CR1, PWR_CR1_DBP);

    /* Wait for Backup domain Write protection disable */
    tickstart = HAL_GetTick();

    while((PWR->CR1 & PWR_CR1_DBP) == 0U)
    {
      if((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
      {
        ret = HAL_TIMEOUT;
        break;
      }
    }

    if(ret == HAL_OK)
    { 
      /* Reset the Backup domain only if the RTC Clock source selection is modified from default */
      tmpregister = READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL);
      
      if((tmpregister != RCC_RTCCLKSOURCE_NONE) && (tmpregister != PeriphClkInit->RTCClockSelection))
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
        while(READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == 0U)
        {
          if((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            ret = HAL_TIMEOUT;
            break;
          }
        }
      }
      
      if(ret == HAL_OK)
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

    /* Restore clock configuration if changed */
    if(pwrclkchanged == SET)
    {
      __HAL_RCC_PWR_CLK_DISABLE();
    }
  }

  /*-------------------------- USART1 clock source configuration -------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART1) == RCC_PERIPHCLK_USART1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART1CLKSOURCE(PeriphClkInit->Usart1ClockSelection));

    /* Configure the USART1 clock source */
    __HAL_RCC_USART1_CONFIG(PeriphClkInit->Usart1ClockSelection);
  }

  /*-------------------------- USART2 clock source configuration -------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART2) == RCC_PERIPHCLK_USART2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART2CLKSOURCE(PeriphClkInit->Usart2ClockSelection));

    /* Configure the USART2 clock source */
    __HAL_RCC_USART2_CONFIG(PeriphClkInit->Usart2ClockSelection);
  }

  /*-------------------------- USART3 clock source configuration -------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USART3) == RCC_PERIPHCLK_USART3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_USART3CLKSOURCE(PeriphClkInit->Usart3ClockSelection));

    /* Configure the USART3 clock source */
    __HAL_RCC_USART3_CONFIG(PeriphClkInit->Usart3ClockSelection);
  }

#if defined(UART4)
  /*-------------------------- UART4 clock source configuration --------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_UART4) == RCC_PERIPHCLK_UART4)
  {
    /* Check the parameters */
    assert_param(IS_RCC_UART4CLKSOURCE(PeriphClkInit->Uart4ClockSelection));

    /* Configure the UART4 clock source */
    __HAL_RCC_UART4_CONFIG(PeriphClkInit->Uart4ClockSelection);
  }
#endif /* UART4 */

#if defined(UART5)

  /*-------------------------- UART5 clock source configuration --------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_UART5) == RCC_PERIPHCLK_UART5)
  {
    /* Check the parameters */
    assert_param(IS_RCC_UART5CLKSOURCE(PeriphClkInit->Uart5ClockSelection));

    /* Configure the UART5 clock source */
    __HAL_RCC_UART5_CONFIG(PeriphClkInit->Uart5ClockSelection);
  }

#endif /* UART5 */

  /*-------------------------- LPUART1 clock source configuration ------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPUART1) == RCC_PERIPHCLK_LPUART1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPUART1CLKSOURCE(PeriphClkInit->Lpuart1ClockSelection));

    /* Configure the LPUAR1 clock source */
    __HAL_RCC_LPUART1_CONFIG(PeriphClkInit->Lpuart1ClockSelection);
  }

  /*-------------------------- I2C1 clock source configuration ---------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C1) == RCC_PERIPHCLK_I2C1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C1CLKSOURCE(PeriphClkInit->I2c1ClockSelection));

    /* Configure the I2C1 clock source */
    __HAL_RCC_I2C1_CONFIG(PeriphClkInit->I2c1ClockSelection);
  }

  /*-------------------------- I2C2 clock source configuration ---------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C2) == RCC_PERIPHCLK_I2C2)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C2CLKSOURCE(PeriphClkInit->I2c2ClockSelection));

    /* Configure the I2C2 clock source */
    __HAL_RCC_I2C2_CONFIG(PeriphClkInit->I2c2ClockSelection);
  }

  /*-------------------------- I2C3 clock source configuration ---------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C3) == RCC_PERIPHCLK_I2C3)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C3CLKSOURCE(PeriphClkInit->I2c3ClockSelection));

    /* Configure the I2C3 clock source */
    __HAL_RCC_I2C3_CONFIG(PeriphClkInit->I2c3ClockSelection);
  }

#if defined(I2C4)  

  /*-------------------------- I2C4 clock source configuration ---------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2C4) == RCC_PERIPHCLK_I2C4)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2C4CLKSOURCE(PeriphClkInit->I2c4ClockSelection));

    /* Configure the I2C4 clock source */
    __HAL_RCC_I2C4_CONFIG(PeriphClkInit->I2c4ClockSelection);
  }

#endif /* I2C4 */

  /*-------------------------- LPTIM1 clock source configuration ---------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM1) == RCC_PERIPHCLK_LPTIM1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_LPTIM1CLKSOURCE(PeriphClkInit->Lptim1ClockSelection));

    /* Configure the LPTIM1 clock source */
    __HAL_RCC_LPTIM1_CONFIG(PeriphClkInit->Lptim1ClockSelection);
  }

  /*-------------------------- SAI1 clock source configuration ---------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI1) == RCC_PERIPHCLK_SAI1)
  {
    /* Check the parameters */
    assert_param(IS_RCC_SAI1CLKSOURCE(PeriphClkInit->Sai1ClockSelection));

    /* Configure the SAI1 interface clock source */
    __HAL_RCC_SAI1_CONFIG(PeriphClkInit->Sai1ClockSelection);
    
    if(PeriphClkInit->Sai1ClockSelection == RCC_SAI1CLKSOURCE_PLL)
    {
      /* Enable PLL48M1CLK output */
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_48M1CLK);
    }
  }

  /*-------------------------- I2S clock source configuration ---------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S) == RCC_PERIPHCLK_I2S)
  {
    /* Check the parameters */
    assert_param(IS_RCC_I2SCLKSOURCE(PeriphClkInit->I2sClockSelection));

    /* Configure the I2S interface clock source */
    __HAL_RCC_I2S_CONFIG(PeriphClkInit->I2sClockSelection);
    
    if(PeriphClkInit->I2sClockSelection == RCC_I2SCLKSOURCE_PLL)
    {
      /* Enable PLL48M1CLK output */
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_48M1CLK);
    }
  }

#if defined(FDCAN1)
  /*-------------------------- FDCAN clock source configuration ---------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_FDCAN) == RCC_PERIPHCLK_FDCAN)
  {
    /* Check the parameters */
    assert_param(IS_RCC_FDCANCLKSOURCE(PeriphClkInit->FdcanClockSelection));

    /* Configure the FDCAN interface clock source */
    __HAL_RCC_FDCAN_CONFIG(PeriphClkInit->FdcanClockSelection);
    
    if(PeriphClkInit->FdcanClockSelection == RCC_FDCANCLKSOURCE_PLL)
    {
      /* Enable PLL48M1CLK output */
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_48M1CLK);
    }
  }
#endif /* FDCAN1 */

#if defined(USB)

  /*-------------------------- USB clock source configuration ----------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_USB) == (RCC_PERIPHCLK_USB))
  {
    assert_param(IS_RCC_USBCLKSOURCE(PeriphClkInit->UsbClockSelection));
    __HAL_RCC_USB_CONFIG(PeriphClkInit->UsbClockSelection);

    if(PeriphClkInit->UsbClockSelection == RCC_USBCLKSOURCE_PLL)
    {
      /* Enable PLL48M1CLK output */
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_48M1CLK);
    }
  }

#endif /* USB */

  /*-------------------------- RNG clock source configuration ----------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RNG) == (RCC_PERIPHCLK_RNG))
  {
    assert_param(IS_RCC_RNGCLKSOURCE(PeriphClkInit->RngClockSelection));
    __HAL_RCC_RNG_CONFIG(PeriphClkInit->RngClockSelection);

    if(PeriphClkInit->RngClockSelection == RCC_RNGCLKSOURCE_PLL)
    {
      /* Enable PLL48M1CLK output */
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_48M1CLK);
    }
  }

  /*-------------------------- ADC12 clock source configuration ----------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADC12) == RCC_PERIPHCLK_ADC12)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADC12CLKSOURCE(PeriphClkInit->Adc12ClockSelection));

    /* Configure the ADC12 interface clock source */
    __HAL_RCC_ADC12_CONFIG(PeriphClkInit->Adc12ClockSelection);
    
    if(PeriphClkInit->Adc12ClockSelection == RCC_ADC12CLKSOURCE_PLL)
    {
      /* Enable PLLADCCLK output */
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_ADCCLK);
    }
  }
  
#if defined(ADC345_COMMON)
  /*-------------------------- ADC345 clock source configuration ----------------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_ADC345) == RCC_PERIPHCLK_ADC345)
  {
    /* Check the parameters */
    assert_param(IS_RCC_ADC345CLKSOURCE(PeriphClkInit->Adc345ClockSelection));

    /* Configure the ADC345 interface clock source */
    __HAL_RCC_ADC345_CONFIG(PeriphClkInit->Adc345ClockSelection);
    
    if(PeriphClkInit->Adc345ClockSelection == RCC_ADC345CLKSOURCE_PLL)
    {
      /* Enable PLLADCCLK output */
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_ADCCLK);
    }
  }
#endif /* ADC345_COMMON */

#if defined(QUADSPI)

  /*-------------------------- QuadSPIx clock source configuration ----------------*/
  if(((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_QSPI) == RCC_PERIPHCLK_QSPI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_QSPICLKSOURCE(PeriphClkInit->QspiClockSelection));

    /* Configure the QuadSPI clock source */
    __HAL_RCC_QSPI_CONFIG(PeriphClkInit->QspiClockSelection);

    if(PeriphClkInit->QspiClockSelection == RCC_QSPICLKSOURCE_PLL)
    {
      /* Enable PLL48M1CLK output */
      __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL_48M1CLK);
    }
  }

#endif /* QUADSPI */

  return status;
}

/**
  * @brief  Get the RCC_ClkInitStruct according to the internal RCC configuration registers.
  * @param  PeriphClkInit  pointer to an RCC_PeriphCLKInitTypeDef structure that
  *         returns the configuration information for the Extended Peripherals
  *         clocks(USART1, USART2, USART3, UART4, UART5, LPUART1, I2C1, I2C2, I2C3, I2C4,
  *         LPTIM1, SAI1, I2Sx, FDCANx, USB, RNG, ADCx, RTC, QSPI).
  * @retval None
  */
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  /* Set all possible values for the extended clock type parameter------------*/

#if defined(STM32G474xx) || defined(STM32G484xx)

  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART1  | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | RCC_PERIPHCLK_UART4  | \
                                        RCC_PERIPHCLK_UART5   | \
                                        RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | RCC_PERIPHCLK_I2C3   | \
                                        RCC_PERIPHCLK_I2C4    | \
                                        RCC_PERIPHCLK_LPTIM1  | RCC_PERIPHCLK_SAI1   | RCC_PERIPHCLK_I2S    | RCC_PERIPHCLK_FDCAN  | \
                                        RCC_PERIPHCLK_RNG     | RCC_PERIPHCLK_USB    | RCC_PERIPHCLK_ADC12  | RCC_PERIPHCLK_ADC345 | \
                                        RCC_PERIPHCLK_QSPI    | \
                                        RCC_PERIPHCLK_RTC;

#elif defined(STM32G473xx) || defined(STM32G483xx)

  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART1  | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | RCC_PERIPHCLK_UART4  | \
                                        RCC_PERIPHCLK_UART5   | \
                                        RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | RCC_PERIPHCLK_I2C3   | \
                                        RCC_PERIPHCLK_I2C4    | \
                                        RCC_PERIPHCLK_LPTIM1  | RCC_PERIPHCLK_SAI1   | RCC_PERIPHCLK_I2S    | \
                                        RCC_PERIPHCLK_RNG     | RCC_PERIPHCLK_USB    | RCC_PERIPHCLK_ADC12  | RCC_PERIPHCLK_ADC345 | \
                                        RCC_PERIPHCLK_QSPI    | \
                                        RCC_PERIPHCLK_RTC;

#elif defined(STM32G471xx)

  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART1  | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | RCC_PERIPHCLK_UART4  | \
                                        RCC_PERIPHCLK_UART5   | \
                                        RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | RCC_PERIPHCLK_I2C3   | \
                                        RCC_PERIPHCLK_I2C4    | \
                                        RCC_PERIPHCLK_LPTIM1  | RCC_PERIPHCLK_SAI1   | RCC_PERIPHCLK_I2S    | \
                                        RCC_PERIPHCLK_RNG     | RCC_PERIPHCLK_USB    | RCC_PERIPHCLK_ADC12  | \
                                        RCC_PERIPHCLK_RTC;
#elif defined(STM32G431xx) || defined(STM32G441xx)

  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART1  | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | RCC_PERIPHCLK_UART4  | \
                                        RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | RCC_PERIPHCLK_I2C3   | \
                                        RCC_PERIPHCLK_LPTIM1  | RCC_PERIPHCLK_SAI1   | RCC_PERIPHCLK_I2S    | RCC_PERIPHCLK_FDCAN    | \
                                        RCC_PERIPHCLK_RNG     | RCC_PERIPHCLK_USB    | RCC_PERIPHCLK_ADC12  | \
                                        RCC_PERIPHCLK_RTC;
#elif defined(STM32GBK1CB)

  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_USART1  | RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | \
                                        RCC_PERIPHCLK_LPUART1 | RCC_PERIPHCLK_I2C1   | RCC_PERIPHCLK_I2C2   | RCC_PERIPHCLK_I2C3   | \
                                        RCC_PERIPHCLK_LPTIM1  | RCC_PERIPHCLK_SAI1   | RCC_PERIPHCLK_I2S    | RCC_PERIPHCLK_FDCAN    | \
                                        RCC_PERIPHCLK_RNG     | RCC_PERIPHCLK_USB    | RCC_PERIPHCLK_ADC12  | \
                                        RCC_PERIPHCLK_RTC;

#endif /* STM32G431xx */


  /* Get the USART1 clock source ---------------------------------------------*/
  PeriphClkInit->Usart1ClockSelection  = __HAL_RCC_GET_USART1_SOURCE();
  /* Get the USART2 clock source ---------------------------------------------*/
  PeriphClkInit->Usart2ClockSelection  = __HAL_RCC_GET_USART2_SOURCE();
  /* Get the USART3 clock source ---------------------------------------------*/
  PeriphClkInit->Usart3ClockSelection  = __HAL_RCC_GET_USART3_SOURCE();

#if defined(UART4)
  /* Get the UART4 clock source ----------------------------------------------*/
  PeriphClkInit->Uart4ClockSelection   = __HAL_RCC_GET_UART4_SOURCE();
#endif /* UART4 */

#if defined(UART5)
  /* Get the UART5 clock source ----------------------------------------------*/
  PeriphClkInit->Uart5ClockSelection   = __HAL_RCC_GET_UART5_SOURCE();
#endif /* UART5 */
  
  /* Get the LPUART1 clock source --------------------------------------------*/
  PeriphClkInit->Lpuart1ClockSelection = __HAL_RCC_GET_LPUART1_SOURCE();

  /* Get the I2C1 clock source -----------------------------------------------*/
  PeriphClkInit->I2c1ClockSelection    = __HAL_RCC_GET_I2C1_SOURCE();

  /* Get the I2C2 clock source ----------------------------------------------*/
  PeriphClkInit->I2c2ClockSelection    = __HAL_RCC_GET_I2C2_SOURCE();

  /* Get the I2C3 clock source -----------------------------------------------*/
  PeriphClkInit->I2c3ClockSelection    = __HAL_RCC_GET_I2C3_SOURCE();

#if defined(I2C4)
  /* Get the I2C4 clock source -----------------------------------------------*/
  PeriphClkInit->I2c4ClockSelection    = __HAL_RCC_GET_I2C4_SOURCE();
#endif /* I2C4 */

  /* Get the LPTIM1 clock source ---------------------------------------------*/
  PeriphClkInit->Lptim1ClockSelection  = __HAL_RCC_GET_LPTIM1_SOURCE();

  /* Get the SAI1 clock source -----------------------------------------------*/
  PeriphClkInit->Sai1ClockSelection    = __HAL_RCC_GET_SAI1_SOURCE();

  /* Get the I2S clock source -----------------------------------------------*/
  PeriphClkInit->I2sClockSelection    = __HAL_RCC_GET_I2S_SOURCE();

#if defined(FDCAN1)
  /* Get the FDCAN clock source -----------------------------------------------*/
  PeriphClkInit->FdcanClockSelection    = __HAL_RCC_GET_FDCAN_SOURCE();
#endif /* FDCAN1 */

#if defined(USB)
  /* Get the USB clock source ------------------------------------------------*/
  PeriphClkInit->UsbClockSelection   = __HAL_RCC_GET_USB_SOURCE();
#endif /* USB */

  /* Get the RNG clock source ------------------------------------------------*/
  PeriphClkInit->RngClockSelection   = __HAL_RCC_GET_RNG_SOURCE();

  /* Get the ADC12 clock source -----------------------------------------------*/
  PeriphClkInit->Adc12ClockSelection     = __HAL_RCC_GET_ADC12_SOURCE();

#if defined(ADC345_COMMON)
  /* Get the ADC345 clock source ----------------------------------------------*/
  PeriphClkInit->Adc345ClockSelection     = __HAL_RCC_GET_ADC345_SOURCE();
#endif /* ADC345_COMMON */

#if defined(QUADSPI)
  /* Get the QuadSPIclock source --------------------------------------------*/
  PeriphClkInit->QspiClockSelection = __HAL_RCC_GET_QSPI_SOURCE();
#endif /* QUADSPI */

  /* Get the RTC clock source ------------------------------------------------*/
  PeriphClkInit->RTCClockSelection     = __HAL_RCC_GET_RTC_SOURCE();

}

/**
  * @brief  Return the peripheral clock frequency for peripherals with clock source from PLL
  * @note   Return 0 if peripheral clock identifier not managed by this API
  * @param  PeriphClk  Peripheral clock identifier
  *         This parameter can be one of the following values:
  *            @arg @ref RCC_PERIPHCLK_USART1  USART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART2  USART2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USART3  USART3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_UART4  UART4 peripheral clock (only for devices with UART4)
  *            @arg @ref RCC_PERIPHCLK_UART5  UART5 peripheral clock (only for devices with UART5)
  *            @arg @ref RCC_PERIPHCLK_LPUART1  LPUART1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C1  I2C1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C2  I2C2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C3  I2C3 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2C4  I2C4 peripheral clock (only for devices with I2C4)
  *            @arg @ref RCC_PERIPHCLK_LPTIM1  LPTIM1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_SAI1  SAI1 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_I2S  SPI peripheral clock
  *            @arg @ref RCC_PERIPHCLK_FDCAN  FDCAN peripheral clock (only for devices with FDCAN)
  *            @arg @ref RCC_PERIPHCLK_RNG  RNG peripheral clock
  *            @arg @ref RCC_PERIPHCLK_USB  USB peripheral clock (only for devices with USB)
  *            @arg @ref RCC_PERIPHCLK_ADC12  ADC1 and ADC2 peripheral clock
  *            @arg @ref RCC_PERIPHCLK_ADC345  ADC3, ADC4 and ADC5 peripheral clock (only for devices with ADC3, ADC4, ADC5)
  *            @arg @ref RCC_PERIPHCLK_QSPI  QSPI peripheral clock (only for devices with QSPI)
  *            @arg @ref RCC_PERIPHCLK_RTC  RTC peripheral clock
  * @retval Frequency in Hz
  */
uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  uint32_t pllvco, plln, pllp;

  /* Check the parameters */
  assert_param(IS_RCC_PERIPHCLOCK(PeriphClk));

  if(PeriphClk == RCC_PERIPHCLK_RTC)
  {
    /* Get the current RTC source */
    srcclk = __HAL_RCC_GET_RTC_SOURCE();

    /* Check if LSE is ready and if RTC clock selection is LSE */
    if ((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_RTCCLKSOURCE_LSE))
    {
      frequency = LSE_VALUE;
    }
    /* Check if LSI is ready and if RTC clock selection is LSI */
    else if ((HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY)) && (srcclk == RCC_RTCCLKSOURCE_LSI))
    {
      frequency = LSI_VALUE;
    }
    /* Check if HSE is ready  and if RTC clock selection is HSI_DIV32*/
    else if ((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY)) && (srcclk == RCC_RTCCLKSOURCE_HSE_DIV32))
    {
      frequency = HSE_VALUE / 32U;
    }
    /* Clock not enabled for RTC*/
    else
    {
      /* nothing to do: frequency already initialized to 0 */
    }
  }
  else
  {
    /* Other external peripheral clock source than RTC */

    /* Compute PLL clock input */
    if(__HAL_RCC_GET_PLL_OSCSOURCE() == RCC_PLLSOURCE_HSI)   /* HSI ? */
    {
      if(HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY))
      {
        pllvco = HSI_VALUE;
      }
      else
      {
        pllvco = 0U;
      }
    }
    else if(__HAL_RCC_GET_PLL_OSCSOURCE() == RCC_PLLSOURCE_HSE)   /* HSE ? */
    {
      if(HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSERDY))
      {
        pllvco = HSE_VALUE;
      }
      else
      {
        pllvco = 0U;
      }
    }
    else /* No source */
    {
      pllvco = 0U;
    }

    /* f(PLL Source) / PLLM */
    pllvco = (pllvco / ((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLM) >> RCC_PLLCFGR_PLLM_Pos) + 1U));

    switch(PeriphClk)
    {

    case RCC_PERIPHCLK_USART1:
      /* Get the current USART1 source */
      srcclk = __HAL_RCC_GET_USART1_SOURCE();

      if(srcclk == RCC_USART1CLKSOURCE_PCLK2)
      {
        frequency = HAL_RCC_GetPCLK2Freq();
      }
      else if(srcclk == RCC_USART1CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_USART1CLKSOURCE_HSI) )
      {
        frequency = HSI_VALUE;
      }
      else if((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_USART1CLKSOURCE_LSE))
      {
        frequency = LSE_VALUE;
      }
      /* Clock not enabled for USART1 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;

    case RCC_PERIPHCLK_USART2:
      /* Get the current USART2 source */
      srcclk = __HAL_RCC_GET_USART2_SOURCE();

      if(srcclk == RCC_USART2CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else if(srcclk == RCC_USART2CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_USART2CLKSOURCE_HSI))
      {
        frequency = HSI_VALUE;
      }
      else if((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY))  && (srcclk == RCC_USART2CLKSOURCE_LSE))
      {
        frequency = LSE_VALUE;
      }
      /* Clock not enabled for USART2 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;

    case RCC_PERIPHCLK_USART3:
      /* Get the current USART3 source */
      srcclk = __HAL_RCC_GET_USART3_SOURCE();

      if(srcclk == RCC_USART3CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else if(srcclk == RCC_USART3CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_USART3CLKSOURCE_HSI))
      {
        frequency = HSI_VALUE;
      }
      else if((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_USART3CLKSOURCE_LSE))
      {
        frequency = LSE_VALUE;
      }
      /* Clock not enabled for USART3 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;

#if defined(UART4)
    case RCC_PERIPHCLK_UART4:
      /* Get the current UART4 source */
      srcclk = __HAL_RCC_GET_UART4_SOURCE();

      if(srcclk == RCC_UART4CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else if(srcclk == RCC_UART4CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_UART4CLKSOURCE_HSI))
      {
        frequency = HSI_VALUE;
      }
      else if((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_UART4CLKSOURCE_LSE))
      {
        frequency = LSE_VALUE;
      }
      /* Clock not enabled for UART4 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;
#endif /* UART4 */

#if defined(UART5)
    case RCC_PERIPHCLK_UART5:
      /* Get the current UART5 source */
      srcclk = __HAL_RCC_GET_UART5_SOURCE();

      if(srcclk == RCC_UART5CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else if(srcclk == RCC_UART5CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_UART5CLKSOURCE_HSI))
      {
        frequency = HSI_VALUE;
      }
      else if((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_UART5CLKSOURCE_LSE))
      {
        frequency = LSE_VALUE;
      }
      /* Clock not enabled for UART5 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;
#endif /* UART5 */

    case RCC_PERIPHCLK_LPUART1:
      /* Get the current LPUART1 source */
      srcclk = __HAL_RCC_GET_LPUART1_SOURCE();

      if(srcclk == RCC_LPUART1CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else if(srcclk == RCC_LPUART1CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_LPUART1CLKSOURCE_HSI))
      {
        frequency = HSI_VALUE;
      }
      else if((HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSERDY)) && (srcclk == RCC_LPUART1CLKSOURCE_LSE))
      {
        frequency = LSE_VALUE;
      }
      /* Clock not enabled for LPUART1 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;

    case RCC_PERIPHCLK_I2C1:
      /* Get the current I2C1 source */
      srcclk = __HAL_RCC_GET_I2C1_SOURCE();

      if(srcclk == RCC_I2C1CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else if(srcclk == RCC_I2C1CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_I2C1CLKSOURCE_HSI))
      {
        frequency = HSI_VALUE;
      }
      /* Clock not enabled for I2C1 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;

    case RCC_PERIPHCLK_I2C2:
      /* Get the current I2C2 source */
      srcclk = __HAL_RCC_GET_I2C2_SOURCE();

      if(srcclk == RCC_I2C2CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else if(srcclk == RCC_I2C2CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_I2C2CLKSOURCE_HSI))
      {
        frequency = HSI_VALUE;
      }
      /* Clock not enabled for I2C2 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;

    case RCC_PERIPHCLK_I2C3:
      /* Get the current I2C3 source */
      srcclk = __HAL_RCC_GET_I2C3_SOURCE();

      if(srcclk == RCC_I2C3CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else if(srcclk == RCC_I2C3CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_I2C3CLKSOURCE_HSI))
      {
        frequency = HSI_VALUE;
      }
      /* Clock not enabled for I2C3 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;

#if defined(I2C4)

    case RCC_PERIPHCLK_I2C4:
      /* Get the current I2C4 source */
      srcclk = __HAL_RCC_GET_I2C4_SOURCE();

      if(srcclk == RCC_I2C4CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else if(srcclk == RCC_I2C4CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_I2C4CLKSOURCE_HSI))
      {
        frequency = HSI_VALUE;
      }
      /* Clock not enabled for I2C4 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;

#endif /* I2C4 */

    case RCC_PERIPHCLK_LPTIM1:
      /* Get the current LPTIM1 source */
      srcclk = __HAL_RCC_GET_LPTIM1_SOURCE();

      if(srcclk == RCC_LPTIM1CLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else if((HAL_IS_BIT_SET(RCC->CSR, RCC_CSR_LSIRDY)) && (srcclk == RCC_LPTIM1CLKSOURCE_LSI))
      {
        frequency = LSI_VALUE;
      }
      else if((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_LPTIM1CLKSOURCE_HSI))
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
        /* nothing to do: frequency already initialized to 0 */
      }
      break;

    case RCC_PERIPHCLK_SAI1:
      /* Get the current SAI1 source */
      srcclk = __HAL_RCC_GET_SAI1_SOURCE();

      if(srcclk == RCC_SAI1CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if(srcclk == RCC_SAI1CLKSOURCE_PLL)
      {
        if(__HAL_RCC_GET_PLLCLKOUT_CONFIG(RCC_PLL_48M1CLK) != 0U)
        {
          /* f(PLLQ) = f(VCO input) * PLLN / PLLQ */
          plln = READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
          frequency = (pllvco * plln) / (((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ) >> RCC_PLLCFGR_PLLQ_Pos) + 1U) << 1U);
        }
      }
      else if(srcclk == RCC_SAI1CLKSOURCE_EXT)
      {
        /* External clock used.*/
        frequency = EXTERNAL_CLOCK_VALUE;
      }
      else if((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_SAI1CLKSOURCE_HSI))
      {
        frequency = HSI_VALUE;
      }
      /* Clock not enabled for SAI1 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;

    case RCC_PERIPHCLK_I2S:
      /* Get the current I2Sx source */
      srcclk = __HAL_RCC_GET_I2S_SOURCE();

      if(srcclk == RCC_I2SCLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else if(srcclk == RCC_I2SCLKSOURCE_PLL)
      {
        if(__HAL_RCC_GET_PLLCLKOUT_CONFIG(RCC_PLL_48M1CLK) != 0U)
        {
          /* f(PLLQ) = f(VCO input) * PLLN / PLLQ */
          plln = READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
          frequency = (pllvco * plln) / (((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ) >> RCC_PLLCFGR_PLLQ_Pos) + 1U) << 1U);
        }
      }
      else if(srcclk == RCC_I2SCLKSOURCE_EXT)
      {
        /* External clock used.*/
        frequency = EXTERNAL_CLOCK_VALUE;
      }      
      else if((HAL_IS_BIT_SET(RCC->CR, RCC_CR_HSIRDY)) && (srcclk == RCC_I2SCLKSOURCE_HSI))
      {
        frequency = HSI_VALUE;
      }
      /* Clock not enabled for I2S */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;

#if defined(FDCAN1)
    case RCC_PERIPHCLK_FDCAN:
      /* Get the current FDCANx source */
      srcclk = __HAL_RCC_GET_FDCAN_SOURCE();

      if(srcclk == RCC_FDCANCLKSOURCE_PCLK1)
      {
        frequency = HAL_RCC_GetPCLK1Freq();
      }
      else if(srcclk == RCC_FDCANCLKSOURCE_HSE)
      {
        frequency = HSE_VALUE;
      }
      else if(srcclk == RCC_FDCANCLKSOURCE_PLL)
      {
        if(__HAL_RCC_GET_PLLCLKOUT_CONFIG(RCC_PLL_48M1CLK) != 0U)
        {
          /* f(PLLQ) = f(VCO input) * PLLN / PLLQ */
          plln = READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
          frequency = (pllvco * plln) / (((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ) >> RCC_PLLCFGR_PLLQ_Pos) + 1U) << 1U);
        }
      }
      /* Clock not enabled for FDCAN */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;
#endif /* FDCAN1 */
    
#if defined(USB)
    
    case RCC_PERIPHCLK_USB:
      /* Get the current USB source */
      srcclk = __HAL_RCC_GET_USB_SOURCE();
      
      if(srcclk == RCC_USBCLKSOURCE_PLL)  /* PLL ? */
      {
        /* f(PLLQ) = f(VCO input) * PLLN / PLLQ */
        plln = READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
        frequency = (pllvco * plln) / (((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ) >> RCC_PLLCFGR_PLLQ_Pos) + 1U) << 1U);
      }
      else if((HAL_IS_BIT_SET(RCC->CRRCR, RCC_CRRCR_HSI48RDY)) && (srcclk == RCC_USBCLKSOURCE_HSI48)) /* HSI48 ? */
      {
        frequency = HSI48_VALUE;
      }
      else /* No clock source */
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;
      
#endif /* USB */

    case RCC_PERIPHCLK_RNG:
      /* Get the current RNG source */
      srcclk = __HAL_RCC_GET_RNG_SOURCE();

      if(srcclk == RCC_RNGCLKSOURCE_PLL)  /* PLL ? */
      {
        /* f(PLLQ) = f(VCO input) * PLLN / PLLQ */
        plln = READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
        frequency = (pllvco * plln) / (((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ) >> RCC_PLLCFGR_PLLQ_Pos) + 1U) << 1U);
      }
      else if( (HAL_IS_BIT_SET(RCC->CRRCR, RCC_CRRCR_HSI48RDY)) && (srcclk == RCC_RNGCLKSOURCE_HSI48)) /* HSI48 ? */
      {
        frequency = HSI48_VALUE;
      }
      else /* No clock source */
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;

    case RCC_PERIPHCLK_ADC12:
      /* Get the current ADC12 source */
      srcclk = __HAL_RCC_GET_ADC12_SOURCE();
      
      if(srcclk == RCC_ADC12CLKSOURCE_PLL)
      {
        if(__HAL_RCC_GET_PLLCLKOUT_CONFIG(RCC_PLL_ADCCLK) != 0U)
        {
          /* f(PLLP) = f(VCO input) * PLLN / PLLP */
          plln = READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
          pllp = READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLPDIV) >> RCC_PLLCFGR_PLLPDIV_Pos;
          if(pllp == 0U)
          {
            if(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP) != 0U)
            {
              pllp = 17U;
            }
            else
            {
              pllp = 7U;
            }
          }
          frequency = (pllvco * plln) / pllp;
        }
      }
      else if(srcclk == RCC_ADC12CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      /* Clock not enabled for ADC12 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;

#if defined(ADC345_COMMON)
    case RCC_PERIPHCLK_ADC345:
      /* Get the current ADC345 source */
      srcclk = __HAL_RCC_GET_ADC345_SOURCE();
      
      if(srcclk == RCC_ADC345CLKSOURCE_PLL)
      {
        if(__HAL_RCC_GET_PLLCLKOUT_CONFIG(RCC_PLL_ADCCLK) != 0U)
        {
          /* f(PLLP) = f(VCO input) * PLLN / PLLP */
          plln = READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
          pllp = READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLPDIV) >> RCC_PLLCFGR_PLLPDIV_Pos;
          if(pllp == 0U)
          {
            if(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP) != 0U)
            {
              pllp = 17U;
            }
            else
            {
              pllp = 7U;
            }
          }
          frequency = (pllvco * plln) / pllp;
        }
      }
      else if(srcclk == RCC_ADC345CLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      /* Clock not enabled for ADC345 */
      else
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;
#endif /* ADC345_COMMON */

#if defined(QUADSPI)

    case RCC_PERIPHCLK_QSPI:
      /* Get the current QSPI source */
      srcclk = __HAL_RCC_GET_QSPI_SOURCE();
      
      if(srcclk == RCC_QSPICLKSOURCE_PLL)  /* PLL ? */
      {
        /* f(PLLQ) = f(VCO input) * PLLN / PLLQ */
        plln = READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
        frequency = (pllvco * plln) / (((READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ) >> RCC_PLLCFGR_PLLQ_Pos) + 1U) << 1U);
      }
      else if(srcclk == RCC_QSPICLKSOURCE_HSI)
      {
        frequency = HSI_VALUE;
      }      
      else if(srcclk == RCC_QSPICLKSOURCE_SYSCLK)
      {
        frequency = HAL_RCC_GetSysClockFreq();
      }
      else /* No clock source */
      {
        /* nothing to do: frequency already initialized to 0 */
      }
      break;

#endif /* QUADSPI */

    default:
      break;
    }
  }

  return(frequency);
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
    activation or deactivation of LSE CSS,
    Low speed clock output and clock after wake-up from STOP mode.
@endverbatim
  * @{
  */

/**
  * @brief  Enable the LSE Clock Security System.
  * @note   Prior to enable the LSE Clock Security System, LSE oscillator is to be enabled
  *         with HAL_RCC_OscConfig() and the LSE oscillator clock is to be selected as RTC
  *         clock with HAL_RCCEx_PeriphCLKConfig().
  * @retval None
  */
void HAL_RCCEx_EnableLSECSS(void)
{
  SET_BIT(RCC->BDCR, RCC_BDCR_LSECSSON) ;
}

/**
  * @brief  Disable the LSE Clock Security System.
  * @note   LSE Clock Security System can only be disabled after a LSE failure detection.
  * @retval None
  */
void HAL_RCCEx_DisableLSECSS(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSECSSON) ;

  /* Disable LSE CSS IT if any */
  __HAL_RCC_DISABLE_IT(RCC_IT_LSECSS);
}

/**
  * @brief  Enable the LSE Clock Security System Interrupt & corresponding EXTI line.
  * @note   LSE Clock Security System Interrupt is mapped on RTC EXTI line 19
  * @retval None
  */
void HAL_RCCEx_EnableLSECSS_IT(void)
{
  /* Enable LSE CSS */
  SET_BIT(RCC->BDCR, RCC_BDCR_LSECSSON) ;

  /* Enable LSE CSS IT */
  __HAL_RCC_ENABLE_IT(RCC_IT_LSECSS);

  /* Enable IT on EXTI Line 19 */
  __HAL_RCC_LSECSS_EXTI_ENABLE_IT();
  __HAL_RCC_LSECSS_EXTI_ENABLE_RISING_EDGE();
}

/**
  * @brief Handle the RCC LSE Clock Security System interrupt request.
  * @retval None
  */
void HAL_RCCEx_LSECSS_IRQHandler(void)
{
  /* Check RCC LSE CSSF flag  */
  if(__HAL_RCC_GET_IT(RCC_IT_LSECSS))
  {
    /* RCC LSE Clock Security System interrupt user callback */
    HAL_RCCEx_LSECSS_Callback();

    /* Clear RCC LSE CSS pending bit */
    __HAL_RCC_CLEAR_IT(RCC_IT_LSECSS);
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
  FlagStatus       pwrclkchanged = RESET;
  FlagStatus       backupchanged = RESET;

  /* Check the parameters */
  assert_param(IS_RCC_LSCOSOURCE(LSCOSource));

  /* LSCO Pin Clock Enable */
  __LSCO_CLK_ENABLE();

  /* Configue the LSCO pin in analog mode */
  GPIO_InitStruct.Pin = LSCO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LSCO_GPIO_PORT, &GPIO_InitStruct);

  /* Update LSCOSEL clock source in Backup Domain control register */
  if(__HAL_RCC_PWR_IS_CLK_DISABLED())
  {
    __HAL_RCC_PWR_CLK_ENABLE();
    pwrclkchanged = SET;
  }
  if(HAL_IS_BIT_CLR(PWR->CR1, PWR_CR1_DBP))
  {
    HAL_PWR_EnableBkUpAccess();
    backupchanged = SET;
  }

  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSCOSEL | RCC_BDCR_LSCOEN, LSCOSource | RCC_BDCR_LSCOEN);

  if(backupchanged == SET)
  {
    HAL_PWR_DisableBkUpAccess();
  }
  if(pwrclkchanged == SET)
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
  if(__HAL_RCC_PWR_IS_CLK_DISABLED())
  {
    __HAL_RCC_PWR_CLK_ENABLE();
    pwrclkchanged = SET;
  }
  if(HAL_IS_BIT_CLR(PWR->CR1, PWR_CR1_DBP))
  {
    /* Enable access to the backup domain */
    HAL_PWR_EnableBkUpAccess();
    backupchanged = SET;
  }

  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSCOEN);

  /* Restore previous configuration */
  if(backupchanged == SET)
  {
    /* Disable access to the backup domain */
    HAL_PWR_DisableBkUpAccess();
  }
  if(pwrclkchanged == SET)
  {
    __HAL_RCC_PWR_CLK_DISABLE();
  }
}


/**
  * @}
  */

#if defined(CRS)

/** @defgroup RCCEx_Exported_Functions_Group3 Extended Clock Recovery System Control functions
 *  @brief  Extended Clock Recovery System Control functions
 *
@verbatim
 ===============================================================================
                ##### Extended Clock Recovery System Control functions  #####
 ===============================================================================
    [..]
      For devices with Clock Recovery System feature (CRS), RCC Extention HAL driver can be used as follows:

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
void HAL_RCCEx_CRSConfig(RCC_CRSInitTypeDef *pInit)
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
  /* Set the TRIM[6:0] bits according to RCC_CRS_HSI48CalibrationValue value */
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
  assert_param(pSynchroInfo != (void *)NULL);

  /* Get the reload value */
  pSynchroInfo->ReloadValue = (READ_BIT(CRS->CFGR, CRS_CFGR_RELOAD));

  /* Get HSI48 oscillator smooth trimming */
  pSynchroInfo->HSI48CalibrationValue = (READ_BIT(CRS->CR, CRS_CR_TRIM) >> CRS_CR_TRIM_Pos);

  /* Get Frequency error capture */
  pSynchroInfo->FreqErrorCapture = (READ_BIT(CRS->ISR, CRS_ISR_FECAP) >> CRS_ISR_FECAP_Pos);

  /* Get Frequency error direction */
  pSynchroInfo->FreqErrorDirection = (READ_BIT(CRS->ISR, CRS_ISR_FEDIR));
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
    if(Timeout != HAL_MAX_DELAY)
    {
      if(((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
      {
        crsstatus = RCC_CRS_TIMEOUT;
      }
    }
    /* Check CRS SYNCOK flag  */
    if(__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCOK))
    {
      /* CRS SYNC event OK */
      crsstatus |= RCC_CRS_SYNCOK;

      /* Clear CRS SYNC event OK bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCOK);
    }

    /* Check CRS SYNCWARN flag  */
    if(__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCWARN))
    {
      /* CRS SYNC warning */
      crsstatus |= RCC_CRS_SYNCWARN;

      /* Clear CRS SYNCWARN bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCWARN);
    }

    /* Check CRS TRIM overflow flag  */
    if(__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_TRIMOVF))
    {
      /* CRS SYNC Error */
      crsstatus |= RCC_CRS_TRIMOVF;

      /* Clear CRS Error bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_TRIMOVF);
    }

    /* Check CRS Error flag  */
    if(__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCERR))
    {
      /* CRS SYNC Error */
      crsstatus |= RCC_CRS_SYNCERR;

      /* Clear CRS Error bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCERR);
    }

    /* Check CRS SYNC Missed flag  */
    if(__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_SYNCMISS))
    {
      /* CRS SYNC Missed */
      crsstatus |= RCC_CRS_SYNCMISS;

      /* Clear CRS SYNC Missed bit */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_SYNCMISS);
    }

    /* Check CRS Expected SYNC flag  */
    if(__HAL_RCC_CRS_GET_FLAG(RCC_CRS_FLAG_ESYNC))
    {
      /* frequency error counter reached a zero value */
      __HAL_RCC_CRS_CLEAR_FLAG(RCC_CRS_FLAG_ESYNC);
    }
  } while(RCC_CRS_NONE == crsstatus);

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
  if(((itflags & RCC_CRS_FLAG_SYNCOK) != 0U) && ((itsources & RCC_CRS_IT_SYNCOK) != 0U))
  {
    /* Clear CRS SYNC event OK flag */
    WRITE_REG(CRS->ICR, CRS_ICR_SYNCOKC);

    /* user callback */
    HAL_RCCEx_CRS_SyncOkCallback();
  }
  /* Check CRS SYNCWARN flag  */
  else if(((itflags & RCC_CRS_FLAG_SYNCWARN) != 0U) && ((itsources & RCC_CRS_IT_SYNCWARN) != 0U))
  {
    /* Clear CRS SYNCWARN flag */
    WRITE_REG(CRS->ICR, CRS_ICR_SYNCWARNC);

    /* user callback */
    HAL_RCCEx_CRS_SyncWarnCallback();
  }
  /* Check CRS Expected SYNC flag  */
  else if(((itflags & RCC_CRS_FLAG_ESYNC) != 0U) && ((itsources & RCC_CRS_IT_ESYNC) != 0U))
  {
    /* frequency error counter reached a zero value */
    WRITE_REG(CRS->ICR, CRS_ICR_ESYNCC);

    /* user callback */
    HAL_RCCEx_CRS_ExpectedSyncCallback();
  }
  /* Check CRS Error flags  */
  else
  {
    if(((itflags & RCC_CRS_FLAG_ERR) != 0U) && ((itsources & RCC_CRS_IT_ERR) != 0U))
    {
      if((itflags & RCC_CRS_FLAG_SYNCERR) != 0U)
      {
        crserror |= RCC_CRS_SYNCERR;
      }
      if((itflags & RCC_CRS_FLAG_SYNCMISS) != 0U)
      {
        crserror |= RCC_CRS_SYNCMISS;
      }
      if((itflags & RCC_CRS_FLAG_TRIMOVF) != 0U)
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
  * @}
  */

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

