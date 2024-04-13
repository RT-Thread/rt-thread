/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_rcc.c
  * @author  MCD Application Team
  * @brief   RCC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Reset and Clock Control (RCC) peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
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
  @verbatim
  ==============================================================================
                      ##### RCC specific features #####
  ==============================================================================
    [..]
      After reset the device is running from Internal High Speed oscillator
      (HSI 64MHz) with Flash 0 wait state,and all peripherals are off except
      internal SRAM, Flash, JTAG and PWR
      (+) There is no pre-scaler on High speed (AHB) and Low speed (APB) buses;
          all peripherals mapped on these buses are running at HSI speed.
      (+) The clock for all peripherals is switched off, except the SRAM and FLASH.
      (+) All GPIOs are in analogue mode , except the JTAG pins which
          are assigned to be used for debug purpose.

    [..]
      Once the device started from reset, the user application has to:
      (+) Configure the clock source to be used to drive the System clock
          (if the application needs higher frequency/performance)
      (+) Configure the System clock frequency and Flash settings
      (+) Configure the AHB and APB buses pre-scalers
      (+) Enable the clock for the peripheral(s) to be used
      (+) Configure the clock kernel source(s) for peripherals which clocks are not
          derived from the System clock.

                      ##### RCC Limitations #####
  ==============================================================================
    [..]
      A delay between an RCC peripheral clock enable and the effective peripheral
      enabling should be taken into account in order to manage the peripheral read/write
      from/to registers.
      (+) This delay depends on the peripheral mapping.
      (+) If peripheral is mapped on AHB: the delay is 2 AHB clock cycle
          after the clock enable bit is set on the hardware register
      (+) If peripheral is mapped on APB: the delay is 2 APB clock cycle
          after the clock enable bit is set on the hardware register

    [..]
      Implemented Workaround:
      (+) For AHB & APB peripherals, a dummy read to the peripheral register has been
          inserted in each __HAL_RCC_PPP_CLK_ENABLE() macro.

  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
  * @{
  */

/** @defgroup RCC  RCC
  * @brief RCC HAL module driver
  * @{
  */

#ifdef HAL_RCC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/** @defgroup RCC_Private_Constants RCC Private Constants
  * @{
  */
#define RCC_CSI_TIMEOUT_VALUE         1U        /* 1 ms */
#define RCC_HSI_TIMEOUT_VALUE         1U        /* 1 ms */
#define RCC_HSI48_TIMEOUT_VALUE       1U        /* 1 ms */
#define RCC_HSE_TIMEOUT_VALUE         HSE_STARTUP_TIMEOUT
#define RCC_LSI_TIMEOUT_VALUE         1U        /* 1 ms */
#define RCC_CLOCKSWITCH_TIMEOUT_VALUE 5000U     /* 5 s  */
#define RCC_PLL_FRAC_WAIT_VALUE       1U        /* PLL Fractional part waiting time before new latch enable : 1 ms */
#define RCC_PLL_INPUTRANGE0_FREQMAX   2000000U  /* 2 MHz is maximum frequency for VCO input range 0 */
#define RCC_PLL_INPUTRANGE1_FREQMAX   4000000U  /* 4 MHz is maximum frequency for VCO input range 1 */
#define RCC_PLL_INPUTRANGE2_FREQMAX   8000000U  /* 8 MHz is maximum frequency for VCO input range 2 */

#define RCC_PLL1_CONFIG               0U
#define RCC_PLL2_CONFIG               1U
#define RCC_PLL3_CONFIG               2U
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup RCC_Private_Macros RCC Private Macros
  * @{
  */
#define RCC_GET_MCO_GPIO_PIN(__RCC_MCOx__)   ((__RCC_MCOx__) & GPIO_PIN_MASK)

#define RCC_GET_MCO_GPIO_AF(__RCC_MCOx__)    (((__RCC_MCOx__) & RCC_MCO_GPIOAF_MASK) >> RCC_MCO_GPIOAF_POS)

#define RCC_GET_MCO_GPIO_INDEX(__RCC_MCOx__) (((__RCC_MCOx__) & RCC_MCO_GPIOPORT_MASK) >> RCC_MCO_GPIOPORT_POS)

#define RCC_GET_MCO_GPIO_PORT(__RCC_MCOx__)  (GPIOA_BASE + ((0x00000400UL) * RCC_GET_MCO_GPIO_INDEX((__RCC_MCOx__))))

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup RCC_Private_Variables Private Variables
  * @{
  */
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_Private_Functions RCC Private Functions
  * @{
  */
static uint32_t RCC_PLL1_GetVCOOutputFreq(void);
static uint32_t RCC_PLL2_GetVCOOutputFreq(void);
static uint32_t RCC_PLL3_GetVCOOutputFreq(void);
static HAL_StatusTypeDef RCC_PLL_Config(uint32_t PLLnumber, const RCC_PLLInitTypeDef *pPLLInit);
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
      This section provides functions allowing to configure the internal/external oscillators
      (HSE, HSI, LSE,CSI, LSI,HSI48, PLL, CSS and MCO) and the System buses clocks (SYSCLK, AHB3, AHB1
       AHB2,AHB4,APB3, APB1L, APB1H, APB2, and APB4).

    [..] Internal/external clock and PLL configuration
         (#) HSI (high-speed internal), 64 MHz factory-trimmed RC used directly or through
             the PLL as System clock source.
         (#) CSI is a low-power RC oscillator which can be used directly as system clock, peripheral
             clock, or PLL input.But even with frequency calibration, is less accurate than an
             external crystal oscillator or ceramic resonator.
         (#) LSI (low-speed internal), 32 KHz low consumption RC used as IWDG and/or RTC
             clock source.

         (#) HSE (high-speed external), 4 to 48 MHz crystal oscillator used directly or
             through the PLL as System clock source. Can be used also as RTC clock source.

         (#) LSE (low-speed external), 32 KHz oscillator used as RTC clock source.

         (#) PLL , The RCC features three independent PLLs (clocked by HSI , HSE or CSI),
             featuring three different output clocks and able  to work either in integer or Fractional mode.
           (++) A main PLL, PLL1, which is generally used to provide clocks to the CPU
                and to some peripherals.
           (++) Two dedicated PLLs, PLL2 and PLL3, which are used to generate the kernel clock for peripherals.


         (#) CSS (Clock security system), once enabled and if a HSE clock failure occurs
            (HSE used directly or through PLL as System clock source), the System clock
             is automatically switched to HSI and an interrupt is generated if enabled.
             The interrupt is linked to the Cortex-M NMI (Non-Mask-able Interrupt)
             exception vector.

         (#) MCO1 (micro controller clock output), used to output HSI, LSE, HSE, PLL1(PLL1_Q)
             or HSI48 clock (through a configurable pre-scaler) on PA8 pin.

         (#) MCO2 (micro controller clock output), used to output HSE, PLL2(PLL2_P), SYSCLK,
             LSI, CSI, or PLL1(PLL1_P) clock (through a configurable pre-scaler) on PC9 pin.

    [..] System, AHB and APB buses clocks configuration
         (#) Several clock sources can be used to drive the System clock (SYSCLK): CSI,HSI,
             HSE and PLL.
             The AHB clock (HCLK) is derived from System core clock through configurable
             pre-scaler and used to clock the CPU, memory and peripherals mapped
             on AHB and APB bus through configurable pre-scalers
             and used to clock the peripherals mapped on these buses. You can use
             "HAL_RCC_GetSysClockFreq()" function to retrieve system clock frequency.

@endverbatim
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
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCC_DeInit(void)
{
  uint32_t tickstart;

  /* Get Start Tick */
  tickstart = HAL_GetTick();

  /* Set HSION bit */
  SET_BIT(RCC->CR, RCC_CR_HSION);

  /* Wait till HSI is ready */
  while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == 0U)
  {
    if ((HAL_GetTick() - tickstart) > RCC_HSI_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Set HSITRIM[6:0] bits to the reset value */
  SET_BIT(RCC->HSICFGR, RCC_HSICFGR_HSITRIM_6);

  if (HAL_RCC_GetHCLKFreq() > HSI_VALUE)
  {
    /* Reset CFGR register (HSI is selected as system clock source) */
    CLEAR_REG(RCC->CFGR);

    /* Update the SystemCoreClock global variables */
    SystemCoreClock = HSI_VALUE;

    /* Adapt Systick interrupt period */
    if (HAL_InitTick(uwTickPrio) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Get Start Tick */
    tickstart = HAL_GetTick();

    /* Wait till clock switch is ready */
    while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != 0U)
    {
      if ((HAL_GetTick() - tickstart) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }

    /* Reduce flash latency */
    __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_1);
  }
  else
  {
    /* Increase flash latency */
    __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_1);

    /* Reset CFGR register (HSI is selected as system clock source) */
    CLEAR_REG(RCC->CFGR);

    /* Adapt Systick interrupt period */
    if (HAL_InitTick(uwTickPrio) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Get Start Tick */
    tickstart = HAL_GetTick();

    /* Wait till clock switch is ready */
    while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != 0U)
    {
      if ((HAL_GetTick() - tickstart) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }


  /* Get Start Tick */
  tickstart = HAL_GetTick();

  /* Reset CSION, CSIKERON, HSEON, HSI48ON, HSECSSON, HSIDIV bits */
  CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_HSIKERON | RCC_CR_HSIDIV |  RCC_CR_CSION | RCC_CR_CSIKERON  \
            | RCC_CR_HSI48ON | RCC_CR_HSECSSON);

  /* Wait till HSE is disabled */
  while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > RCC_HSE_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Get Start Tick */
  tickstart = HAL_GetTick();

  /* Clear PLLON bit */
  CLEAR_BIT(RCC->CR, RCC_CR_PLL1ON);

  /* Wait till PLL is disabled */
  while (READ_BIT(RCC->CR, RCC_CR_PLL1RDY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > RCC_PLL_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Get Start Tick */
  tickstart = HAL_GetTick();

  /* Reset PLL2ON bit */
  CLEAR_BIT(RCC->CR, RCC_CR_PLL2ON);

  /* Wait till PLL2 is disabled */
  while (READ_BIT(RCC->CR, RCC_CR_PLL2RDY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > RCC_PLL_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Get Start Tick */
  tickstart = HAL_GetTick();

  /* Reset PLL3 bit */
  CLEAR_BIT(RCC->CR, RCC_CR_PLL3ON);

  /* Wait till PLL3 is disabled */
  while (READ_BIT(RCC->CR, RCC_CR_PLL3RDY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > RCC_PLL_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Reset CDCFGR register */
  CLEAR_REG(RCC->CDCFGR);

  /* Reset BMCFGR register */
  CLEAR_REG(RCC->BMCFGR);

  /* Reset APBCFGR register */
  CLEAR_REG(RCC->APBCFGR);

  /* Reset PLLCKSELR register to default value */
  WRITE_REG(RCC->PLLCKSELR, 0x02020200U);

  /* Reset PLLCFGR register */
  CLEAR_REG(RCC->PLLCFGR);

  /* Reset PLL1DIVR1 register to default value */
  WRITE_REG(RCC->PLL1DIVR1, 0x01010280U);

  /* Reset PLL1DIVR2 register to default value */
  WRITE_REG(RCC->PLL1DIVR2, 0x00000101U);

  /* Reset PLL1FRACR register */
  CLEAR_REG(RCC->PLL1FRACR);

  /* Reset PLL2DIVR1 register to default value */
  WRITE_REG(RCC->PLL2DIVR1, 0x01010280U);

  /* Reset PLL2DIVR2 register to default value */
  WRITE_REG(RCC->PLL2DIVR2, 0x00000101U);

  /* Reset PLL2FRACR register */
  CLEAR_REG(RCC->PLL2FRACR);

  /* Reset PLL3DIVR1 register to default value */
  WRITE_REG(RCC->PLL3DIVR1, 0x01010280U);

  /* Reset PLL3DIVR2 register to default value */
  WRITE_REG(RCC->PLL3DIVR2, 0x00000101U);

  /* Reset PLL3FRACR register */
  CLEAR_REG(RCC->PLL3FRACR);

  /* Reset HSEBYP bit */
  CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);

  /* Disable all interrupts */
  CLEAR_REG(RCC->CIER);

  /* Clear all interrupts flags */
  WRITE_REG(RCC->CICR, 0xFFFFFFFFU);

  /* Reset all RSR flags */
  SET_BIT(RCC->RSR, RCC_RSR_RMVF);

  return HAL_OK;
}

/**
  * @brief  Initializes the RCC Oscillators according to the specified parameters in the
  *         RCC_OscInitTypeDef.
  * @param  RCC_OscInitStruct: pointer to an RCC_OscInitTypeDef structure that
  *         contains the configuration information for the RCC Oscillators.
  * @note   The PLL is not disabled when used as system clock.
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  *         supported by this function. User should request a transition to LSE Off
  *         first and then LSE On or LSE Bypass.
  * @note   Transition HSE Bypass to HSE On and HSE On to HSE Bypass are not
  *         supported by this function. User should request a transition to HSE Off
  *         first and then HSE On or HSE Bypass.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct)
{
  uint32_t tickstart;
  uint32_t sysclksrc;
  uint32_t pllsrc;
  uint32_t pllrdy;
  uint32_t tmpreg1;

  /* Check Null pointer */
  if (RCC_OscInitStruct == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_RCC_OSCILLATORTYPE(RCC_OscInitStruct->OscillatorType));

  sysclksrc = __HAL_RCC_GET_SYSCLK_SOURCE();
  pllsrc = __HAL_RCC_GET_PLL_OSCSOURCE();
  pllrdy = RCC->CR & (RCC_CR_PLL1RDY | RCC_CR_PLL2RDY | RCC_CR_PLL3RDY);

  /*------------------------------- HSE Configuration ------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSE(RCC_OscInitStruct->HSEState));

    /* When the HSE is used as system clock or clock source for PLL in these cases HSE will not disabled */
    if ((sysclksrc == RCC_SYSCLKSOURCE_STATUS_HSE) ||
        ((pllrdy != 0U) && (pllsrc == RCC_PLLSOURCE_HSE)))
    {
      if (RCC_OscInitStruct->HSEState == RCC_HSE_OFF)
      {
        return HAL_ERROR;
      }
    }
    else
    {
      /* Set the new HSE configuration ---------------------------------------*/
      __HAL_RCC_HSE_CONFIG(RCC_OscInitStruct->HSEState);

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Check the HSE State */
      if (RCC_OscInitStruct->HSEState != RCC_HSE_OFF)
      {
        /* Wait till HSE is ready */
        while (READ_BIT(RCC->CR, RCC_CR_HSERDY) == 0U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_HSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        /* Wait till HSE is disabled */
        while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != 0U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_HSE_TIMEOUT_VALUE)
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
    assert_param(IS_RCC_HSICALIBRATION_VALUE(RCC_OscInitStruct->HSICalibrationValue));

    /* Check if HSI is used as system clock or as PLL1 source when PLL1 is selected as system clock */
    if ((sysclksrc == RCC_SYSCLKSOURCE_STATUS_HSI) ||
        ((pllrdy != 0U) && (pllsrc == RCC_PLLSOURCE_HSI)))
    {
      /* When HSI is used as system clock it will not be disabled */
      if (RCC_OscInitStruct->HSIState == RCC_HSI_OFF)
      {
        return HAL_ERROR;
      }
      /* Otherwise, calibration is allowed, divider update also unless used for any enabled PLL */
      else
      {
        /* HSI must not be used as reference clock for any enabled PLL clock source */
        tmpreg1 = (RCC->CR & RCC_CR_HSIDIV);
        if ((pllsrc == RCC_PLLSOURCE_HSI) && (pllrdy != 0U) && \
            (tmpreg1 != RCC_OscInitStruct->HSIDiv))
        {
          return HAL_ERROR;
        }

        assert_param(IS_RCC_HSIDIV(RCC_OscInitStruct->HSIDiv));

        /* Set the Internal High Speed oscillator new divider */
        __HAL_RCC_HSI_CONFIG(RCC_HSI_ON | RCC_OscInitStruct->HSIDiv);

        if (sysclksrc == RCC_SYSCLKSOURCE_STATUS_HSI)
        {
          SystemCoreClock = (HSI_VALUE / (1UL << ((READ_BIT(RCC->CR, RCC_CR_HSIDIV)) >> RCC_CR_HSIDIV_Pos)));
        }
        /* Adapt Systick interrupt period */
        if (HAL_InitTick(uwTickPrio) != HAL_OK)
        {
          return HAL_ERROR;
        }
      }
      /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
      __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HSICalibrationValue);
    }
    else
    {
      /* Check the HSI State */
      if (RCC_OscInitStruct->HSIState != RCC_HSI_OFF)
      {
        /* Enable the Internal High Speed oscillator */
        __HAL_RCC_HSI_CONFIG(RCC_OscInitStruct->HSIState | RCC_OscInitStruct->HSIDiv);

        /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
        __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HSICalibrationValue);

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSI is ready */
        while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == 0U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_HSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        /* Disable the Internal High Speed oscillator (HSI). */
        __HAL_RCC_HSI_DISABLE();

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till HSI is disabled */
        while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) != 0U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_HSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
  }
  /*----------------------------- CSI Configuration --------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_CSI) == RCC_OSCILLATORTYPE_CSI)
  {
    /* Check the parameters */
    assert_param(IS_RCC_CSI(RCC_OscInitStruct->CSIState));

    /* When the CSI is used as system clock it will not disabled */
    if ((sysclksrc == RCC_SYSCLKSOURCE_STATUS_CSI) ||
        ((pllrdy != 0U) && (pllsrc == RCC_PLLSOURCE_CSI)))
    {
      /* When CSI is used as system clock it will not disabled */
      if (RCC_OscInitStruct->CSIState == RCC_CSI_OFF)
      {
        return HAL_ERROR;
      }
    }
    else
    {
      /* Check the CSI State */
      if ((RCC_OscInitStruct->CSIState) != RCC_CSI_OFF)
      {
        /* Enable the Internal High Speed oscillator (CSI). */
        __HAL_RCC_CSI_ENABLE();

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till CSI is ready */
        while (READ_BIT(RCC->CR, RCC_CR_CSIRDY) == 0U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_CSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {
        /* Disable the Internal High Speed oscillator (CSI). */
        __HAL_RCC_CSI_DISABLE();

        /* Get Start Tick*/
        tickstart = HAL_GetTick();

        /* Wait till CSI is disabled */
        while (READ_BIT(RCC->CR, RCC_CR_CSIRDY) != 0U)
        {
          if ((HAL_GetTick() - tickstart) > RCC_CSI_TIMEOUT_VALUE)
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
    if ((RCC_OscInitStruct->LSIState) != RCC_LSI_OFF)
    {
      /* Enable the Internal Low Speed oscillator (LSI). */
      __HAL_RCC_LSI_ENABLE();

      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSI is ready */
      while (READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) == 0U)
      {
        if ((HAL_GetTick() - tickstart) > RCC_LSI_TIMEOUT_VALUE)
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

      /* Wait till LSI is ready */
      while (READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) != 0U)
      {
        if ((HAL_GetTick() - tickstart) > RCC_LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  /*------------------------------ HSI48 Configuration -------------------------*/
  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSI48) == RCC_OSCILLATORTYPE_HSI48)
  {
    /* Check the parameters */
    assert_param(IS_RCC_HSI48(RCC_OscInitStruct->HSI48State));

    /* Check the HSI48 State */
    if ((RCC_OscInitStruct->HSI48State) != RCC_HSI48_OFF)
    {
      /* Enable the Internal Low Speed oscillator (HSI48). */
      __HAL_RCC_HSI48_ENABLE();

      /* Get time-out */
      tickstart = HAL_GetTick();

      /* Wait till HSI48 is ready */
      while (READ_BIT(RCC->CR, RCC_CR_HSI48RDY) == 0U)
      {
        if ((HAL_GetTick() - tickstart) > RCC_HSI48_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      /* Disable the Internal Low Speed oscillator (HSI48). */
      __HAL_RCC_HSI48_DISABLE();

      /* Get time-out */
      tickstart = HAL_GetTick();

      /* Wait till HSI48 is ready */
      while (READ_BIT(RCC->CR, RCC_CR_HSI48RDY) != 0U)
      {
        if ((HAL_GetTick() - tickstart) > RCC_HSI48_TIMEOUT_VALUE)
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

    /* Enable write access to Backup domain */
    PWR->CR1 |= PWR_CR1_DBP;

    /* Set the new LSE configuration -----------------------------------------*/
    __HAL_RCC_LSE_CONFIG(RCC_OscInitStruct->LSEState);
    /* Check the LSE State */
    if ((RCC_OscInitStruct->LSEState) != RCC_LSE_OFF)
    {
      /* Get Start Tick*/
      tickstart = HAL_GetTick();

      /* Wait till LSE is ready */
      while (READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == 0U)
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

      /* Wait till LSE is disabled */
      while (READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) != 0U)
      {
        if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  /*-------------------------------- PLL1 Configuration ----------------------*/
  /* Check the parameters */
  assert_param(IS_RCC_PLL(RCC_OscInitStruct->PLL1.PLLState));

  if (RCC_OscInitStruct->PLL1.PLLState != RCC_PLL_NONE)
  {
    /* Check if the PLL is used as system clock or not */
    if (sysclksrc == RCC_SYSCLKSOURCE_STATUS_PLLCLK)
    {
      /* No PLL off possible */
      if (RCC_OscInitStruct->PLL1.PLLState == RCC_PLL_OFF)
      {
        return HAL_ERROR;
      }
      else
      {
        /* Check if only fractional part needs to be updated  */
        tmpreg1 = ((RCC->PLL1FRACR & RCC_PLL1FRACR_FRACN) >> RCC_PLL1FRACR_FRACN_Pos);

        if (RCC_OscInitStruct->PLL1.PLLFractional != tmpreg1)
        {
          assert_param(IS_RCC_PLLFRACN_VALUE(RCC_OscInitStruct->PLL1.PLLFractional));

          /* Disable PLL1FRACLE */
          __HAL_RCC_PLL1_FRACN_DISABLE();

          /* Get Start Tick*/
          tickstart = HAL_GetTick();

          /* Wait at least 2 CK_REF (PLL input source divided by M) period to make sure next latched value will be taken into account. */
          while ((HAL_GetTick() - tickstart) < RCC_PLL_FRAC_WAIT_VALUE)
          {
            /* Do nothing */
          }

          /* Configure PLL1FRACN */
          __HAL_RCC_PLL1_FRACN_CONFIG(RCC_OscInitStruct->PLL1.PLLFractional);

          /* Enable PLL1FRACLE to latch new value . */
          __HAL_RCC_PLL1_FRACN_ENABLE();
        }
      }
    }
    else
    {
      /* Initialize PLL1T to 1 to use common PLL initialization function */
      RCC_OscInitStruct->PLL1.PLLT = 1U;
      if (RCC_PLL_Config(RCC_PLL1_CONFIG, &(RCC_OscInitStruct->PLL1)) != HAL_OK)
      {
        return HAL_ERROR;
      }
    }
  }

  /*-------------------------------- PLL2 Configuration ----------------------*/
  /* Check the parameters */
  assert_param(IS_RCC_PLL(RCC_OscInitStruct->PLL2.PLLState));

  if (RCC_OscInitStruct->PLL2.PLLState != RCC_PLL_NONE)
  {
    if (RCC_PLL_Config(RCC_PLL2_CONFIG, &(RCC_OscInitStruct->PLL2)) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  /*-------------------------------- PLL3 Configuration ----------------------*/
  /* Check the parameters */
  assert_param(IS_RCC_PLL(RCC_OscInitStruct->PLL3.PLLState));

  if (RCC_OscInitStruct->PLL3.PLLState != RCC_PLL_NONE)
  {
    /* Initialize PLL3T to 1 to use common PLL initialization function */
    RCC_OscInitStruct->PLL3.PLLT = 1U;
    if (RCC_PLL_Config(RCC_PLL3_CONFIG, &(RCC_OscInitStruct->PLL3)) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Initializes the CPU, AHB and APB buses clocks according to the specified
  *         parameters in the RCC_ClkInitStruct.
  * @param  RCC_ClkInitStruct: pointer to an RCC_OscInitTypeDef structure that
  *         contains the configuration information for the RCC peripheral.
  * @param  FLatency: FLASH Latency, this parameter depend on device selected
  *
  * @note   The SystemCoreClock CMSIS variable is used to store System Core Clock Frequency
  *         and updated by HAL_InitTick() function called within this function
  *
  * @note   The HSI is used (enabled by hardware) as system clock source after
  *         start-up from Reset, wake-up from STOP and STANDBY mode, or in case
  *         of failure of the HSE used directly or indirectly as system clock
  *         (if the Clock Security System CSS is enabled).
  *
  * @note   A switch from one clock source to another occurs only if the target
  *         clock source is ready (clock stable after start-up delay or PLL locked).
  *         If a clock source which is not yet ready is selected, the switch will
  *         occur when the clock source will be ready.
  *         You can use HAL_RCC_GetClockConfig() function to know which clock is
  *         currently used as system clock source.
  *         (for more details refer to section above "Initialization/de-initialization functions")
  * @retval None
  */
HAL_StatusTypeDef HAL_RCC_ClockConfig(const RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t FLatency)
{
  HAL_StatusTypeDef halstatus;
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
    must be correctly programmed according to the frequency of the CPU clock
    (HCLK) and the supply voltage of the device. */

  /* Increasing the CPU frequency */
  if (FLatency > __HAL_FLASH_GET_LATENCY())
  {
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    __HAL_FLASH_SET_LATENCY(FLatency);

    /* Check that the new number of wait states is taken into account to access the Flash
    memory by reading the FLASH_ACR register */
    if (__HAL_FLASH_GET_LATENCY() != FLatency)
    {
      return HAL_ERROR;
    }

  }

  /* Increasing the BUS frequency divider ? */

  /*-------------------------- PCLK1 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK1) == RCC_CLOCKTYPE_PCLK1)
  {
    assert_param(IS_RCC_PCLK1(RCC_ClkInitStruct->APB1CLKDivider));
    if ((RCC_ClkInitStruct->APB1CLKDivider) > (RCC->APBCFGR & RCC_APBCFGR_PPRE1))
    {
      MODIFY_REG(RCC->APBCFGR, RCC_APBCFGR_PPRE1, (RCC_ClkInitStruct->APB1CLKDivider));
    }
  }

  /*-------------------------- PCLK2 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK2) == RCC_CLOCKTYPE_PCLK2)
  {
    assert_param(IS_RCC_PCLK2(RCC_ClkInitStruct->APB2CLKDivider));
    if ((RCC_ClkInitStruct->APB2CLKDivider) > (RCC->APBCFGR & RCC_APBCFGR_PPRE2))
    {
      MODIFY_REG(RCC->APBCFGR, RCC_APBCFGR_PPRE2, (RCC_ClkInitStruct->APB2CLKDivider));
    }
  }

  /*-------------------------- PCLK4 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK4) == RCC_CLOCKTYPE_PCLK4)
  {
    assert_param(IS_RCC_PCLK4(RCC_ClkInitStruct->APB4CLKDivider));
    if ((RCC_ClkInitStruct->APB4CLKDivider) > (RCC->APBCFGR & RCC_APBCFGR_PPRE4))
    {
      MODIFY_REG(RCC->APBCFGR, RCC_APBCFGR_PPRE4, (RCC_ClkInitStruct->APB4CLKDivider));
    }
  }

  /*-------------------------- PCLK5 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK5) == RCC_CLOCKTYPE_PCLK5)
  {
    assert_param(IS_RCC_PCLK5(RCC_ClkInitStruct->APB5CLKDivider));
    if ((RCC_ClkInitStruct->APB5CLKDivider) > (RCC->APBCFGR & RCC_APBCFGR_PPRE5))
    {
      MODIFY_REG(RCC->APBCFGR, RCC_APBCFGR_PPRE5, (RCC_ClkInitStruct->APB5CLKDivider));
    }
  }

  /*-------------------------- HCLK Configuration --------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_HCLK) == RCC_CLOCKTYPE_HCLK)
  {
    assert_param(IS_RCC_HCLK(RCC_ClkInitStruct->AHBCLKDivider));
    if ((RCC_ClkInitStruct->AHBCLKDivider) > (RCC->BMCFGR & RCC_BMCFGR_BMPRE))
    {
      /* Set the new HCLK clock divider */
      MODIFY_REG(RCC->BMCFGR, RCC_BMCFGR_BMPRE, RCC_ClkInitStruct->AHBCLKDivider);
    }
  }

  /*------------------------- SYSCLK Configuration -------------------------*/
  if ((RCC_ClkInitStruct->ClockType & RCC_CLOCKTYPE_SYSCLK) == RCC_CLOCKTYPE_SYSCLK)
  {
    assert_param(IS_RCC_SYSCLKSOURCE(RCC_ClkInitStruct->SYSCLKSource));
    assert_param(IS_RCC_SYSCLK(RCC_ClkInitStruct->SYSCLKDivider));
    MODIFY_REG(RCC->CDCFGR, RCC_CDCFGR_CPRE, RCC_ClkInitStruct->SYSCLKDivider);

    /* HSE is selected as System Clock Source */
    if (RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_HSE)
    {
      /* Check the HSE ready flag */
      if (READ_BIT(RCC->CR, RCC_CR_HSERDY) == 0U)
      {
        return HAL_ERROR;
      }
    }
    /* PLL is selected as System Clock Source */
    else if (RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_PLLCLK)
    {
      /* Check the PLL ready flag */
      if (READ_BIT(RCC->CR, RCC_CR_PLL1RDY) == 0U)
      {
        return HAL_ERROR;
      }
    }
    /* CSI is selected as System Clock Source */
    else if (RCC_ClkInitStruct->SYSCLKSource == RCC_SYSCLKSOURCE_CSI)
    {
      /* Check the PLL ready flag */
      if (READ_BIT(RCC->CR, RCC_CR_CSIRDY) == 0U)
      {
        return HAL_ERROR;
      }
    }
    /* HSI is selected as System Clock Source */
    else
    {
      /* Check the HSI ready flag */
      if (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == 0U)
      {
        return HAL_ERROR;
      }
    }
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_ClkInitStruct->SYSCLKSource);

    /* Get Start Tick*/
    tickstart = HAL_GetTick();

    while (__HAL_RCC_GET_SYSCLK_SOURCE() != (RCC_ClkInitStruct->SYSCLKSource << RCC_CFGR_SWS_Pos))
    {
      if ((HAL_GetTick() - tickstart) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* Decreasing the BUS frequency divider ? */

  /*-------------------------- HCLK Configuration --------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_HCLK) == RCC_CLOCKTYPE_HCLK)
  {
    assert_param(IS_RCC_HCLK(RCC_ClkInitStruct->AHBCLKDivider));
    if ((RCC_ClkInitStruct->AHBCLKDivider) < (RCC->BMCFGR & RCC_BMCFGR_BMPRE))
    {
      /* Set the new HCLK clock divider */
      MODIFY_REG(RCC->BMCFGR, RCC_BMCFGR_BMPRE, RCC_ClkInitStruct->AHBCLKDivider);
    }
  }

  /* Decreasing the number of wait states because of lower CPU frequency */
  if (FLatency < __HAL_FLASH_GET_LATENCY())
  {
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    __HAL_FLASH_SET_LATENCY(FLatency);

    /* Check that the new number of wait states is taken into account to access the Flash
    memory by reading the FLASH_ACR register */
    if (__HAL_FLASH_GET_LATENCY() != FLatency)
    {
      return HAL_ERROR;
    }
  }

  /*-------------------------- PCLK1 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK1) == RCC_CLOCKTYPE_PCLK1)
  {
    assert_param(IS_RCC_PCLK1(RCC_ClkInitStruct->APB1CLKDivider));
    if ((RCC_ClkInitStruct->APB1CLKDivider) < (RCC->APBCFGR & RCC_APBCFGR_PPRE1))
    {
      MODIFY_REG(RCC->APBCFGR, RCC_APBCFGR_PPRE1, (RCC_ClkInitStruct->APB1CLKDivider));
    }
  }

  /*-------------------------- PCLK2 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK2) == RCC_CLOCKTYPE_PCLK2)
  {
    assert_param(IS_RCC_PCLK2(RCC_ClkInitStruct->APB2CLKDivider));
    if ((RCC_ClkInitStruct->APB2CLKDivider) < (RCC->APBCFGR & RCC_APBCFGR_PPRE2))
    {
      MODIFY_REG(RCC->APBCFGR, RCC_APBCFGR_PPRE2, (RCC_ClkInitStruct->APB2CLKDivider));
    }
  }

  /*-------------------------- PCLK4 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK4) == RCC_CLOCKTYPE_PCLK4)
  {
    assert_param(IS_RCC_PCLK4(RCC_ClkInitStruct->APB4CLKDivider));
    if ((RCC_ClkInitStruct->APB4CLKDivider) < (RCC->APBCFGR & RCC_APBCFGR_PPRE4))
    {
      MODIFY_REG(RCC->APBCFGR, RCC_APBCFGR_PPRE4, (RCC_ClkInitStruct->APB4CLKDivider));
    }
  }

  /*-------------------------- PCLK5 Configuration ---------------------------*/
  if (((RCC_ClkInitStruct->ClockType) & RCC_CLOCKTYPE_PCLK5) == RCC_CLOCKTYPE_PCLK5)
  {
    assert_param(IS_RCC_PCLK5(RCC_ClkInitStruct->APB5CLKDivider));
    if ((RCC_ClkInitStruct->APB5CLKDivider) < (RCC->APBCFGR & RCC_APBCFGR_PPRE5))
    {
      MODIFY_REG(RCC->APBCFGR, RCC_APBCFGR_PPRE5, (RCC_ClkInitStruct->APB5CLKDivider));
    }
  }

  /* Update the SystemCoreClock global variable with the System CPU clock */
  SystemCoreClock = HAL_RCC_GetSysClockFreq();

  /* Configure the source of time base considering new system clocks settings*/
  halstatus = HAL_InitTick(uwTickPrio);

  return halstatus;
}

/**
  * @}
  */

/** @defgroup RCC_Group2 Peripheral Control functions
  *  @brief   RCC clocks control functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the RCC Clocks
    frequencies.

@endverbatim
  * @{
  */

/**
  * @brief  Selects the clock source to output on MCO1 pin(PA8) or on MCO2 pin(PC9).
  * @note   PA8/PC9 should be configured in alternate function mode.
  * @param  RCC_MCOx specifies the output direction for the clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCO1_PA8 Clock source to output on MCO1 pin(PA8).
  *            @arg RCC_MCO2_PC9 Clock source to output on MCO2 pin(PC9).
  * @param  RCC_MCOSource specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCO1SOURCE_HSI HSI clock selected as MCO1 source
  *            @arg RCC_MCO1SOURCE_LSE LSE clock selected as MCO1 source
  *            @arg RCC_MCO1SOURCE_HSE HSE clock selected as MCO1 source
  *            @arg RCC_MCO1SOURCE_PLL1Q:  PLL1Q clock selected as MCO1 source
  *            @arg RCC_MCO1SOURCE_HSI48 HSI48 (48MHZ) selected as MCO1 source
  *            @arg RCC_MCO2SOURCE_SYSCLK System clock (SYSCLK) selected as MCO2 source
  *            @arg RCC_MCO2SOURCE_PLL2PCLK PLL2P clock selected as MCO2 source
  *            @arg RCC_MCO2SOURCE_HSE HSE clock selected as MCO2 source
  *            @arg RCC_MCO2SOURCE_PLL1P  PLL1P clock selected as MCO2 source
  *            @arg RCC_MCO2SOURCE_CSI  CSI clock selected as MCO2 source
  *            @arg RCC_MCO2SOURCE_LSI  LSI clock selected as MCO2 source
  * @param  RCC_MCODiv: specifies the MCOx pre-scaler.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCODIV_1 up to RCC_MCODIV_15  : divider applied to MCOx clock
  * @retval None
  */
void HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv)
{
#if defined(HAL_GPIO_MODULE_ENABLED)
  GPIO_InitTypeDef GPIO_InitStruct;
  uint32_t mcoindex;
  uint32_t mco_gpio_index;
  GPIO_TypeDef *mco_gpio_port;

  /* Check the parameters */
  assert_param(IS_RCC_MCO(RCC_MCOx));

  /* Common GPIO init parameters */
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;

  /* Get MCOx selection */
  mcoindex = RCC_MCOx & RCC_MCO_INDEX_MASK;

  /* Get MCOx GPIO Port */
  mco_gpio_port = (GPIO_TypeDef *) RCC_GET_MCO_GPIO_PORT(RCC_MCOx);

  /* MCOx Clock Enable */
  mco_gpio_index = RCC_GET_MCO_GPIO_INDEX(RCC_MCOx);
  SET_BIT(RCC->AHB4ENR, (1UL << mco_gpio_index));

  /* Configure the MCOx pin in alternate function mode */
  GPIO_InitStruct.Pin = RCC_GET_MCO_GPIO_PIN(RCC_MCOx);
  GPIO_InitStruct.Alternate = RCC_GET_MCO_GPIO_AF(RCC_MCOx);
  HAL_GPIO_Init(mco_gpio_port, &GPIO_InitStruct);

  if (mcoindex == RCC_MCO1_INDEX)
  {
    assert_param(IS_RCC_MCODIV(RCC_MCODiv));
    assert_param(IS_RCC_MCO1SOURCE(RCC_MCOSource));
    /* Mask MCOSEL[] and MCOPRE[] bits then set MCO clock source and prescaler */
    MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCO1SEL | RCC_CFGR_MCO1PRE), (RCC_MCOSource | RCC_MCODiv));
  }
  else if (mcoindex == RCC_MCO2_INDEX)
  {
    assert_param(IS_RCC_MCODIV(RCC_MCODiv));
    assert_param(IS_RCC_MCO2SOURCE(RCC_MCOSource));
    /* Mask MCOSEL[] and MCOPRE[] bits then set MCO clock source and prescaler */
    MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCO2SEL | RCC_CFGR_MCO2PRE), (RCC_MCOSource | (RCC_MCODiv << 7)));
  }
  else
  {
    /* Do nothing */
  }

#endif /* HAL_GPIO_MODULE_ENABLED */
}

/**
  * @brief  Enables the Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure (Clock Security System Interrupt, CSSI),
  *         allowing the MCU to perform rescue operations. The CSSI is linked to
  *         the Cortex-M NMI (Non-Mask-able Interrupt) exception vector.
  * @retval None
  */
void HAL_RCC_EnableCSS(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSECSSON);
}

/**
  * @brief  Disables the Clock Security System.
  * @retval None
  */
void HAL_RCC_DisableCSS(void)
{
  CLEAR_BIT(RCC->CR, RCC_CR_HSECSSON);
}

/**
  * @brief  Returns the SYSCLK frequency
  *
  * @note   The system frequency computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source:
  * @note     If SYSCLK source is CSI, function returns values based on CSI_VALUE(*)
  * @note     If SYSCLK source is HSI, function returns values based on HSI_VALUE(**)
  * @note     If SYSCLK source is HSE, function returns values based on HSE_VALUE(***)
  * @note     If SYSCLK source is PLL, function returns values based on CSI_VALUE(*),
  *           HSI_VALUE(**) or HSE_VALUE(***) multiplied/divided by the PLL factors.
  * @note     (*) CSI_VALUE is a constant defined in stm32h7rsxx_hal_conf.h file (default value
  *               4 MHz) but the real value may vary depending on the variations
  *               in voltage and temperature.
  * @note     (**) HSI_VALUE is a constant defined in stm32h7rsxx_hal_conf.h file (default value
  *               64 MHz) but the real value may vary depending on the variations
  *               in voltage and temperature.
  * @note     (***) HSE_VALUE is a constant defined in stm32h7rsxx_hal_conf.h file (default value
  *                24 MHz), user has to ensure that HSE_VALUE is same as the real
  *                frequency of the crystal used. Otherwise, this function may
  *                have wrong result.
  *
  * @note   The result of this function could be not correct when using fractional
  *         value for HSE crystal.
  *
  * @note   This function can be used by the user application to compute the
  *         baud rate for the communication peripherals or configure other parameters.
  *
  * @note   Each time SYSCLK changes, this function must be called to update the
  *         right SYSCLK value. Otherwise, any configuration based on this function will be incorrect.
  *
  *
  * @retval SYSCLK frequency
  */
uint32_t HAL_RCC_GetSysClockFreq(void)
{
  uint32_t pllp;
  uint32_t pllsource;
  uint32_t pllm;
  uint32_t pllfracen;
  uint32_t hsivalue;
  float_t fracn1;
  float_t pllvco;
  uint32_t sysclockfreq;
  uint32_t prescaler;

  /* Get SYSCLK source -------------------------------------------------------*/

  switch (RCC->CFGR & RCC_CFGR_SWS)
  {
    case RCC_SYSCLKSOURCE_STATUS_HSI:  /* HSI used as system clock source */

      if (READ_BIT(RCC->CR, RCC_CR_HSIDIVF) != 0U)
      {
        sysclockfreq = (uint32_t)(HSI_VALUE >> (__HAL_RCC_GET_HSI_DIVIDER() >> RCC_CR_HSIDIV_Pos));
      }
      else
      {
        /* Can't retrieve HSIDIV value */
        sysclockfreq = 0U;
      }

      break;

    case RCC_SYSCLKSOURCE_STATUS_CSI:  /* CSI used as system clock  source */
      sysclockfreq = CSI_VALUE;
      break;

    case RCC_SYSCLKSOURCE_STATUS_HSE:  /* HSE used as system clock  source */
      sysclockfreq = HSE_VALUE;
      break;

    case RCC_SYSCLKSOURCE_STATUS_PLLCLK:  /* PLL1 used as system clock  source */

      /* PLL_VCO = (HSE_VALUE or HSI_VALUE or CSI_VALUE/ PLLM) * PLLN
      SYSCLK = PLL_VCO / PLLR
      */
      pllsource = (RCC->PLLCKSELR & RCC_PLLCKSELR_PLLSRC);
      pllm = ((RCC->PLLCKSELR & RCC_PLLCKSELR_DIVM1) >> RCC_PLLCKSELR_DIVM1_Pos)  ;
      pllfracen = ((RCC-> PLLCFGR & RCC_PLLCFGR_PLL1FRACEN) >> RCC_PLLCFGR_PLL1FRACEN_Pos);
      fracn1 = (float_t)(uint32_t)(pllfracen * ((RCC->PLL1FRACR & RCC_PLL1FRACR_FRACN) >> 3));

      if (pllm != 0U)
      {
        switch (pllsource)
        {
          case RCC_PLLSOURCE_HSI:  /* HSI used as PLL clock source */

            if (READ_BIT(RCC->CR, RCC_CR_HSIDIVF) != 0U)
            {
              hsivalue = (HSI_VALUE >> (__HAL_RCC_GET_HSI_DIVIDER() >> RCC_CR_HSIDIV_Pos));
              pllvco = ((float_t)hsivalue / (float_t)pllm) * ((float_t)(uint32_t)(RCC->PLL1DIVR1 & RCC_PLL1DIVR1_DIVN) + (fracn1 / (float_t)0x2000) + (float_t)1);
            }
            else
            {
              /* Can't retrieve HSIDIV value */
              pllvco = (float_t)0;
            }
            break;

          case RCC_PLLSOURCE_CSI:  /* CSI used as PLL clock source */
            pllvco = ((float_t)CSI_VALUE / (float_t)pllm) * ((float_t)(uint32_t)(RCC->PLL1DIVR1 & RCC_PLL1DIVR1_DIVN) + (fracn1 / (float_t)0x2000) + (float_t)1);
            break;

          case RCC_PLLSOURCE_HSE:  /* HSE used as PLL clock source */
            pllvco = ((float_t)HSE_VALUE / (float_t)pllm) * ((float_t)(uint32_t)(RCC->PLL1DIVR1 & RCC_PLL1DIVR1_DIVN) + (fracn1 / (float_t)0x2000) + (float_t)1);
            break;

          default:
            pllvco = ((float_t)CSI_VALUE / (float_t)pllm) * ((float_t)(uint32_t)(RCC->PLL1DIVR1 & RCC_PLL1DIVR1_DIVN) + (fracn1 / (float_t)0x2000) + (float_t)1);
            break;
        }
        pllp = (((RCC->PLL1DIVR1 & RCC_PLL1DIVR1_DIVP) >> RCC_PLL1DIVR1_DIVP_Pos) + 1U) ;
        sysclockfreq = (uint32_t)(float_t)(pllvco / (float_t)pllp);
      }
      else
      {
        sysclockfreq = 0U;
      }
      break;

    default:
      sysclockfreq = CSI_VALUE;
      break;
  }

  prescaler = RCC->CDCFGR & RCC_CDCFGR_CPRE;
  if (prescaler >= 8U)
  {
    sysclockfreq = sysclockfreq >> (prescaler - RCC_CDCFGR_CPRE_3 + 1U);
  }

  return sysclockfreq;
}


/**
  * @brief  Return the HCLK frequency.
  * @retval HCLK frequency in Hz
  */
uint32_t HAL_RCC_GetHCLKFreq(void)
{
  uint32_t clock;
  uint32_t prescaler;
  const uint8_t AHBPrescTable[8] = {1U, 2U, 3U, 4U, 6U, 7U, 8U, 9U};

  /* SysClk */
  clock = HAL_RCC_GetSysClockFreq();
  /* Bus matrix divider */
  prescaler = (RCC->BMCFGR & RCC_BMCFGR_BMPRE) >> RCC_BMCFGR_BMPRE_Pos;
  if (prescaler >= 8U)
  {
    clock = clock >> AHBPrescTable[prescaler - 8U];
  }
  return (clock);
}

/**
  * @brief  Return the PCLK1 frequency.
  * @note   Each time PCLK1 changes, this function must be called to update the
  *         right PCLK1 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval PCLK1 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK1Freq(void)
{
  uint32_t clock;
  uint32_t prescaler;
  /* Get HCLK source and compute PCLK1 frequency ---------------------------*/
  clock = HAL_RCC_GetHCLKFreq();
  /* APB1 prescaler */
  prescaler = (RCC->APBCFGR & RCC_APBCFGR_PPRE1) >> RCC_APBCFGR_PPRE1_Pos;
  if (prescaler >= 4U)
  {
    clock = clock >> (prescaler - 3U);
  }
  return (clock);
}

/**
  * @brief  Return the PCLK2 frequency.
  * @note   Each time PCLK2 changes, this function must be called to update the
  *         right PCLK2 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval PCLK2 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK2Freq(void)
{
  uint32_t clock;
  uint32_t prescaler;
  /* Get HCLK source and compute PCLK2 frequency ---------------------------*/
  clock = HAL_RCC_GetHCLKFreq();
  /* APB2 prescaler */
  prescaler = (RCC->APBCFGR & RCC_APBCFGR_PPRE2) >> RCC_APBCFGR_PPRE2_Pos;
  if (prescaler >= 4U)
  {
    clock = clock >> (prescaler - 3U);
  }
  return (clock);
}

/**
  * @brief  Return the PCLK4 frequency.
  * @note   Each time PCLK4 changes, this function must be called to update the
  *         right PCLK4 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval PCLK4 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK4Freq(void)
{
  uint32_t clock;
  uint32_t prescaler;
  /* Get HCLK source and compute PCLK4 frequency ---------------------------*/
  clock = HAL_RCC_GetHCLKFreq();
  /* APB4 prescaler */
  prescaler = (RCC->APBCFGR & RCC_APBCFGR_PPRE4) >> RCC_APBCFGR_PPRE4_Pos;
  if (prescaler >= 4U)
  {
    clock = clock >> (prescaler - 3U);
  }
  return (clock);
}

/**
  * @brief  Return the PCLK5 frequency.
  * @note   Each time PCLK5 changes, this function must be called to update the
  *         right PCLK5 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval PCLK5 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK5Freq(void)
{
  uint32_t clock;
  uint32_t prescaler;
  /* Get HCLK source and compute PCLK5 frequency ---------------------------*/
  clock = HAL_RCC_GetHCLKFreq();
  /* APB5 prescaler */
  prescaler = (RCC->APBCFGR & RCC_APBCFGR_PPRE5) >> RCC_APBCFGR_PPRE5_Pos;
  if (prescaler >= 4U)
  {
    clock = clock >> (prescaler - 3U);
  }
  return (clock);
}

/**
  * @brief  Return the PLL1P frequency.
  * @retval PLL1P frequency in Hz
  */
uint32_t HAL_RCC_GetPLL1PFreq(void)
{
  uint32_t pllp;

  /* PLL1P divider */
  pllp = ((RCC->PLL1DIVR1 & RCC_PLL1DIVR1_DIVP) >> RCC_PLL1DIVR1_DIVP_Pos) + 1U;

  /* Compute VCO output frequency and return PLL1P one */
  return ((uint32_t)RCC_PLL1_GetVCOOutputFreq() / pllp);
}

/**
  * @brief  Return the PLL1Q frequency.
  * @retval PLL1Q frequency in Hz
  */
uint32_t HAL_RCC_GetPLL1QFreq(void)
{
  uint32_t pllq;

  /* PLL1Q divider */
  pllq = ((RCC->PLL1DIVR1 & RCC_PLL1DIVR1_DIVQ) >> RCC_PLL1DIVR1_DIVQ_Pos) + 1U;

  /* Compute VCO output frequency and return PLL1Q one */
  return ((uint32_t)RCC_PLL1_GetVCOOutputFreq() / pllq);
}

/**
  * @brief  Return the PLL1R frequency.
  * @retval PLL1R frequency in Hz
  */
uint32_t HAL_RCC_GetPLL1RFreq(void)
{
  uint32_t pllr;

  /* PLL1R divider */
  pllr = ((RCC->PLL1DIVR1 & RCC_PLL1DIVR1_DIVR) >> RCC_PLL1DIVR1_DIVR_Pos) + 1U;

  /* Compute VCO output frequency and return PLL1R one */
  return ((uint32_t)RCC_PLL1_GetVCOOutputFreq() / pllr);
}

/**
  * @brief  Return the PLL1S frequency.
  * @retval PLL1S frequency in Hz
  */
uint32_t HAL_RCC_GetPLL1SFreq(void)
{
  uint32_t plls;

  /* PLL1S divider */
  plls = ((RCC->PLL1DIVR2 & RCC_PLL1DIVR2_DIVS) >> RCC_PLL1DIVR2_DIVS_Pos) + 1U;

  /* Compute VCO output frequency and return PLL1S one */
  return ((uint32_t)RCC_PLL1_GetVCOOutputFreq() / plls);
}

/**
  * @brief  Return the PLL2P frequency.
  * @retval PLL2P frequency in Hz
  */
uint32_t HAL_RCC_GetPLL2PFreq(void)
{
  uint32_t pllp;

  /* PLL2P divider */
  pllp = ((RCC->PLL2DIVR1 & RCC_PLL2DIVR1_DIVP) >> RCC_PLL2DIVR1_DIVP_Pos) + 1U;

  /* Compute VCO output frequency and return PLL2P one */
  return ((uint32_t)RCC_PLL2_GetVCOOutputFreq() / pllp);
}

/**
  * @brief  Return the PLL2Q frequency.
  * @retval PLL2Q frequency in Hz
  */
uint32_t HAL_RCC_GetPLL2QFreq(void)
{
  uint32_t pllq;

  /* PLL2Q divider */
  pllq = ((RCC->PLL2DIVR1 & RCC_PLL2DIVR1_DIVQ) >> RCC_PLL2DIVR1_DIVQ_Pos) + 1U;

  /* Compute VCO output frequency and return PLL2Q one */
  return ((uint32_t)RCC_PLL2_GetVCOOutputFreq() / pllq);
}

/**
  * @brief  Return the PLL2R frequency.
  * @retval PLL2R frequency in Hz
  */
uint32_t HAL_RCC_GetPLL2RFreq(void)
{
  uint32_t pllr;

  /* PLL2R divider */
  pllr = ((RCC->PLL2DIVR1 & RCC_PLL2DIVR1_DIVR) >> RCC_PLL2DIVR1_DIVR_Pos) + 1U;

  /* Compute VCO output frequency and return PLL2R one */
  return ((uint32_t)RCC_PLL2_GetVCOOutputFreq() / pllr);
}

/**
  * @brief  Return the PLL2S frequency.
  * @retval PLL2S frequency in Hz
  */
uint32_t HAL_RCC_GetPLL2SFreq(void)
{
  uint32_t plls;

  /* PLL2S divider */
  plls = ((RCC->PLL2DIVR2 & RCC_PLL2DIVR2_DIVS) >> RCC_PLL2DIVR2_DIVS_Pos) + 1U;

  /* Compute VCO output frequency and return PLL2R one */
  return ((uint32_t)RCC_PLL2_GetVCOOutputFreq() / plls);
}

/**
  * @brief  Return the PLL2T frequency.
  * @retval PLL2T frequency in Hz
  */
uint32_t HAL_RCC_GetPLL2TFreq(void)
{
  uint32_t pllt;

  /* PLL2T divider */
  pllt = ((RCC->PLL2DIVR2 & RCC_PLL2DIVR2_DIVT) >> RCC_PLL2DIVR2_DIVT_Pos) + 1U;

  /* Compute VCO output frequency and return PLL2T one */
  return ((uint32_t)RCC_PLL2_GetVCOOutputFreq() / pllt);
}

/**
  * @brief  Return the PLL3P frequency.
  * @retval PLL3P frequency in Hz
  */
uint32_t HAL_RCC_GetPLL3PFreq(void)
{
  uint32_t pllp;

  /* PLL3P divider */
  pllp = ((RCC->PLL3DIVR1 & RCC_PLL3DIVR1_DIVP) >> RCC_PLL3DIVR1_DIVP_Pos) + 1U;

  /* Compute VCO output frequency and return PLL3P one */
  return ((uint32_t)RCC_PLL3_GetVCOOutputFreq() / pllp);
}

/**
  * @brief  Return the PLL3Q frequency.
  * @retval PLL3Q frequency in Hz
  */
uint32_t HAL_RCC_GetPLL3QFreq(void)
{
  uint32_t pllq;

  /* PLL3Q divider */
  pllq = ((RCC->PLL3DIVR1 & RCC_PLL3DIVR1_DIVQ) >> RCC_PLL3DIVR1_DIVQ_Pos) + 1U;

  /* Compute VCO output frequency and return PLL3Q one */
  return ((uint32_t)RCC_PLL3_GetVCOOutputFreq() / pllq);
}

/**
  * @brief  Return the PLL3R frequency.
  * @retval PLL3R frequency in Hz
  */
uint32_t HAL_RCC_GetPLL3RFreq(void)
{
  uint32_t pllr;

  /* PLL3R divider */
  pllr = ((RCC->PLL3DIVR1 & RCC_PLL3DIVR1_DIVR) >> RCC_PLL3DIVR1_DIVR_Pos) + 1U;

  /* Compute VCO output frequency and return PLL3R one */
  return ((uint32_t)RCC_PLL3_GetVCOOutputFreq() / pllr);
}

/**
  * @brief  Return the PLL3S frequency.
  * @retval PLL3S frequency in Hz
  */
uint32_t HAL_RCC_GetPLL3SFreq(void)
{
  uint32_t plls;

  /* PLL3S divider */
  plls = ((RCC->PLL3DIVR2 & RCC_PLL3DIVR2_DIVS) >> RCC_PLL3DIVR2_DIVS_Pos) + 1U;

  /* Compute VCO output frequency and return PLL3S one */
  return ((uint32_t)RCC_PLL3_GetVCOOutputFreq() / plls);
}

/**
  * @brief  Configures the RCC_OscInitStruct according to the internal
  * RCC configuration registers.
  * @param  RCC_OscInitStruct: pointer to an RCC_OscInitTypeDef structure that
  * will be configured.
  * @retval None
  */
void HAL_RCC_GetOscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct)
{

  uint32_t regvalue;
  uint32_t mask;

  /* Check the parameters */
  assert_param(RCC_OscInitStruct != (void *)NULL);

  /* Set all possible values for the Oscillator type parameter ---------------*/
  RCC_OscInitStruct->OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_CSI | \
                                      RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSI48;

  /* Get Backup Domain register  */
  regvalue = RCC->BDCR;

  /* Get the LSE configuration -----------------------------------------------*/
  mask = (RCC_BDCR_LSEBYP | RCC_BDCR_LSEEXT | RCC_BDCR_LSEON);
  RCC_OscInitStruct->LSEState = (regvalue & mask);

  /* Get RCC clock control and status register */
  regvalue = RCC->CSR;

  /* Get the LSI configuration -----------------------------------------------*/
  mask = RCC_CSR_LSION;
  RCC_OscInitStruct->LSIState = (regvalue & mask);

  /* Get Control register */
  regvalue = RCC->CR;

  /* Get the HSE configuration -----------------------------------------------*/
  mask = (RCC_CR_HSEBYP | RCC_CR_HSEEXT | RCC_CR_HSEON);
  RCC_OscInitStruct->HSEState = (regvalue & mask);

  /* Get the HSI configuration -----------------------------------------------*/
  mask = RCC_CR_HSION;
  RCC_OscInitStruct->HSIState = (regvalue & mask);
  RCC_OscInitStruct->HSIDiv = (regvalue & RCC_CR_HSIDIV);
  RCC_OscInitStruct->HSICalibrationValue = ((RCC->HSICFGR & RCC_HSICFGR_HSITRIM) >> RCC_HSICFGR_HSITRIM_Pos);

  /* Get the HSI48 configuration ---------------------------------------------*/
  mask = RCC_CR_HSI48ON;
  RCC_OscInitStruct->HSI48State = (regvalue & mask);

  /* Get the CSI configuration -----------------------------------------------*/
  mask = RCC_CR_CSION;
  RCC_OscInitStruct->CSIState = (regvalue & mask);

  /* Get the PLL1 configuration -----------------------------------------------*/
  if ((regvalue & RCC_CR_PLL1ON) == RCC_CR_PLL1ON)
  {
    RCC_OscInitStruct->PLL1.PLLState = RCC_PLL_ON;
  }
  else
  {
    RCC_OscInitStruct->PLL1.PLLState = RCC_PLL_OFF;
  }

  /* Get PLL1 configuration register */
  regvalue = RCC->PLLCKSELR;
  RCC_OscInitStruct->PLL1.PLLSource = (regvalue & RCC_PLLCKSELR_PLLSRC);
  RCC_OscInitStruct->PLL1.PLLM = ((regvalue & RCC_PLLCKSELR_DIVM1) >> RCC_PLLCKSELR_DIVM1_Pos);

  /* Check if fractional part is enable */
  regvalue = RCC->PLLCFGR;
  if ((regvalue & RCC_PLLCFGR_PLL1FRACEN) != 0x00u)
  {
    regvalue = (((RCC->PLL1FRACR & RCC_PLL1FRACR_FRACN) >> RCC_PLL1FRACR_FRACN_Pos));
  }
  else
  {
    regvalue = 0;
  }
  RCC_OscInitStruct->PLL1.PLLFractional = regvalue;

  /* Get PLL1 dividers register */
  regvalue = RCC->PLL1DIVR1;
  RCC_OscInitStruct->PLL1.PLLN = ((regvalue & RCC_PLL1DIVR1_DIVN) + 1U);
  RCC_OscInitStruct->PLL1.PLLR = (((regvalue & RCC_PLL1DIVR1_DIVR) >> RCC_PLL1DIVR1_DIVR_Pos) + 1U);
  RCC_OscInitStruct->PLL1.PLLP = (((regvalue & RCC_PLL1DIVR1_DIVP) >> RCC_PLL1DIVR1_DIVP_Pos) + 1U);
  RCC_OscInitStruct->PLL1.PLLQ = (((regvalue & RCC_PLL1DIVR1_DIVQ) >> RCC_PLL1DIVR1_DIVQ_Pos) + 1U);
  regvalue = RCC->PLL1DIVR2;
  RCC_OscInitStruct->PLL1.PLLS = (((regvalue & RCC_PLL1DIVR2_DIVS) >> RCC_PLL1DIVR2_DIVS_Pos) + 1U);
  RCC_OscInitStruct->PLL1.PLLT = 0;

  /* Get the PLL2 configuration -----------------------------------------------*/
  /* Get Control register */
  regvalue = RCC->CR;
  if ((regvalue & RCC_CR_PLL2ON) == RCC_CR_PLL2ON)
  {
    RCC_OscInitStruct->PLL2.PLLState = RCC_PLL_ON;
  }
  else
  {
    RCC_OscInitStruct->PLL2.PLLState = RCC_PLL_OFF;
  }

  /* Get PLL2 configuration register */
  regvalue = RCC->PLLCKSELR;
  RCC_OscInitStruct->PLL2.PLLSource = (regvalue & RCC_PLLCKSELR_PLLSRC);
  RCC_OscInitStruct->PLL2.PLLM = ((regvalue & RCC_PLLCKSELR_DIVM2) >> RCC_PLLCKSELR_DIVM2_Pos);

  /* Check if fractional part is enable */
  regvalue = RCC->PLLCFGR;
  if ((regvalue & RCC_PLLCFGR_PLL2FRACEN) != 0x00u)
  {
    regvalue = (((RCC->PLL2FRACR & RCC_PLL2FRACR_FRACN) >> RCC_PLL2FRACR_FRACN_Pos));
  }
  else
  {
    regvalue = 0;
  }
  RCC_OscInitStruct->PLL2.PLLFractional = regvalue;

  /* Get PLL2 dividers register */
  regvalue = RCC->PLL2DIVR1;
  RCC_OscInitStruct->PLL2.PLLN = ((regvalue & RCC_PLL2DIVR1_DIVN) + 1U);
  RCC_OscInitStruct->PLL2.PLLR = (((regvalue & RCC_PLL2DIVR1_DIVR) >> RCC_PLL2DIVR1_DIVR_Pos) + 1U);
  RCC_OscInitStruct->PLL2.PLLP = (((regvalue & RCC_PLL2DIVR1_DIVP) >> RCC_PLL2DIVR1_DIVP_Pos) + 1U);
  RCC_OscInitStruct->PLL2.PLLQ = (((regvalue & RCC_PLL2DIVR1_DIVQ) >> RCC_PLL2DIVR1_DIVQ_Pos) + 1U);
  regvalue = RCC->PLL2DIVR2;
  RCC_OscInitStruct->PLL2.PLLS = (((regvalue & RCC_PLL2DIVR2_DIVS) >> RCC_PLL2DIVR2_DIVS_Pos) + 1U);
  RCC_OscInitStruct->PLL2.PLLT = (((regvalue & RCC_PLL2DIVR2_DIVT) >> RCC_PLL2DIVR2_DIVT_Pos) + 1U);

  /* Get the PLL3 configuration -----------------------------------------------*/
  /* Get Control register */
  regvalue = RCC->CR;
  if ((regvalue & RCC_CR_PLL3ON) == RCC_CR_PLL3ON)
  {
    RCC_OscInitStruct->PLL3.PLLState = RCC_PLL_ON;
  }
  else
  {
    RCC_OscInitStruct->PLL3.PLLState = RCC_PLL_OFF;
  }

  /* Get PLL3 configuration register */
  regvalue = RCC->PLLCKSELR;
  RCC_OscInitStruct->PLL3.PLLSource = (regvalue & RCC_PLLCKSELR_PLLSRC);
  RCC_OscInitStruct->PLL3.PLLM = ((regvalue & RCC_PLLCKSELR_DIVM3) >> RCC_PLLCKSELR_DIVM3_Pos);


  /* Check if fractional part is enable */
  regvalue = RCC->PLLCFGR;
  if ((regvalue & RCC_PLLCFGR_PLL3FRACEN) != 0x00u)
  {
    regvalue = (((RCC->PLL3FRACR & RCC_PLL3FRACR_FRACN) >> RCC_PLL3FRACR_FRACN_Pos));
  }
  else
  {
    regvalue = 0;
  }
  RCC_OscInitStruct->PLL3.PLLFractional = regvalue;

  /* Get PLL3 dividers register */
  regvalue = RCC->PLL3DIVR1;
  RCC_OscInitStruct->PLL3.PLLN = ((regvalue & RCC_PLL3DIVR1_DIVN) + 1U);
  RCC_OscInitStruct->PLL3.PLLR = (((regvalue & RCC_PLL3DIVR1_DIVR) >> RCC_PLL3DIVR1_DIVR_Pos) + 1U);
  RCC_OscInitStruct->PLL3.PLLP = (((regvalue & RCC_PLL3DIVR1_DIVP) >> RCC_PLL3DIVR1_DIVP_Pos) + 1U);
  RCC_OscInitStruct->PLL3.PLLQ = (((regvalue & RCC_PLL3DIVR1_DIVQ) >> RCC_PLL3DIVR1_DIVQ_Pos) + 1U);
  regvalue = RCC->PLL3DIVR2;
  RCC_OscInitStruct->PLL3.PLLS = (((regvalue & RCC_PLL3DIVR2_DIVS) >> RCC_PLL3DIVR2_DIVS_Pos) + 1U);
  RCC_OscInitStruct->PLL3.PLLT = 0;

}

/**
  * @brief  Configures the RCC_ClkInitStruct according to the internal
  * RCC configuration registers.
  * @param  RCC_ClkInitStruct: pointer to an RCC_ClkInitTypeDef structure that
  * will be configured.
  * @param  pFLatency: Pointer on the Flash Latency.
  * @retval None
  */
void HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct, uint32_t *pFLatency)
{
  /* Set all possible values for the Clock type parameter --------------------*/
  RCC_ClkInitStruct->ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK  | \
                                 RCC_CLOCKTYPE_PCLK1  | RCC_CLOCKTYPE_PCLK2 | \
                                 RCC_CLOCKTYPE_PCLK4  | RCC_CLOCKTYPE_PCLK5;

  /* Get the SYSCLK source ---------------------------------------------------*/
  RCC_ClkInitStruct->SYSCLKSource = READ_BIT(RCC->CFGR, RCC_CFGR_SW);

  /* Get the SYSCLK configuration---------------------------------------------*/
  RCC_ClkInitStruct->SYSCLKDivider = READ_BIT(RCC->CDCFGR, RCC_CDCFGR_CPRE);

  /* Get the HCLK configuration ----------------------------------------------*/
  RCC_ClkInitStruct->AHBCLKDivider = READ_BIT(RCC->BMCFGR, RCC_BMCFGR_BMPRE);

  /* Get the APB1 configuration ----------------------------------------------*/
  RCC_ClkInitStruct->APB1CLKDivider = READ_BIT(RCC->APBCFGR, RCC_APBCFGR_PPRE1);

  /* Get the APB2 configuration ----------------------------------------------*/
  RCC_ClkInitStruct->APB2CLKDivider = READ_BIT(RCC->APBCFGR, RCC_APBCFGR_PPRE2);

  /* Get the APB4 configuration ----------------------------------------------*/
  RCC_ClkInitStruct->APB4CLKDivider = READ_BIT(RCC->APBCFGR, RCC_APBCFGR_PPRE4);

  /* Get the APB5 configuration ----------------------------------------------*/
  RCC_ClkInitStruct->APB5CLKDivider = READ_BIT(RCC->APBCFGR, RCC_APBCFGR_PPRE5);

  /* Get the Flash Wait State (Latency) configuration ------------------------*/
  *pFLatency = __HAL_FLASH_GET_LATENCY();
}

/**
  * @brief This function handles the RCC HSE CSS interrupt request.
  * @note This API should be called under the NMI_Handler().
  * @retval None
  */
void HAL_RCC_NMI_IRQHandler(void)
{
  /* Check RCC HSECSSF interrupt flag  */
  if (__HAL_RCC_GET_IT(RCC_IT_HSECSS))
  {
    /* Clear RCC HSE CSS pending bit */
    __HAL_RCC_CLEAR_IT(RCC_IT_HSECSS);

    /* RCC HSE Clock Security System interrupt user callback */
    HAL_RCC_HSECSSCallback();
  }
}

/**
  * @brief  RCC HSE Clock Security System interrupt callback
  * @retval none
  */
__weak void HAL_RCC_HSECSSCallback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RCC_HSECSSCallback could be implemented in the user file
   */
}

/**
  * @brief  RCC LSE Clock Security System interrupt callback
  * @retval none
  */
__weak void HAL_RCC_LSECSSCallback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_RCC_LSECSSCallback could be implemented in the user file
   */
}

/**
  * @brief  Get and clear reset flags
  * @note   Once reset flags are retrieved, this API is clearing them in order
  *         to isolate next reset reason.
  * @retval can be a combination of @ref RCC_Reset_Flag
  */
uint32_t HAL_RCC_GetResetSource(void)
{
  uint32_t reset;

  /* Get all reset flags */
  reset = RCC->RSR & RCC_RESET_FLAG_ALL;

  /* Clear Reset flags */
  RCC->RSR |= RCC_RSR_RMVF;

  return reset;
}

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup RCC_Private_Functions
  * @{
  */

/**
  * @brief  Configure the requested PLL
  * @param  PLLnumber PLL number to configure
  * @param  pPLLInit Pointer to an RCC_PLLInitTypeDef structure that
  *                  contains the configuration parameters.
  * @note   PLL is temporary disabled to apply new parameters
  *
  * @retval HAL status
  */
static HAL_StatusTypeDef RCC_PLL_Config(uint32_t PLLnumber, const RCC_PLLInitTypeDef *pPLLInit)
{
  __IO uint32_t *p_rcc_pll_divr1_reg;
  __IO uint32_t *p_rcc_pll_divr2_reg;
  __IO uint32_t *p_rcc_pll_fracr_reg;
  HAL_StatusTypeDef ret = HAL_OK;
  uint32_t tickstart;
  uint32_t pllsrc;
  uint32_t pllvco;

  p_rcc_pll_divr1_reg = &(RCC->PLL1DIVR1) + (((uint32_t)0x02) * PLLnumber);
  p_rcc_pll_divr2_reg = &(RCC->PLL1DIVR2) + (((uint32_t)0x01) * PLLnumber);

  /* Disable the post-dividers */
  CLEAR_BIT(RCC->PLLCFGR, (RCC_PLLCFGR_PLL1PEN | RCC_PLLCFGR_PLL1QEN | RCC_PLLCFGR_PLL1REN | RCC_PLLCFGR_PLL1SEN |
                           0x00000200U) /* Hardcoded because no definition in CMSIS */
            << ((RCC_PLLCFGR_PLL2PEN_Pos - RCC_PLLCFGR_PLL1PEN_Pos)*PLLnumber));

  /* Ensure PLLx is disabled */
  CLEAR_BIT(RCC->CR, RCC_CR_PLL1ON << ((RCC_CR_PLL2ON_Pos - RCC_CR_PLL1ON_Pos)*PLLnumber));

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait till PLLx is disabled */
  while (READ_BIT(RCC->CR, (RCC_CR_PLL1RDY << ((RCC_CR_PLL2RDY_Pos - RCC_CR_PLL1RDY_Pos)*PLLnumber))) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > RCC_PLL_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  if (pPLLInit->PLLState == RCC_PLL_ON)
  {
    /* Check the parameters */
    assert_param(IS_RCC_PLLSOURCE(pPLLInit->PLLSource));
    assert_param(IS_RCC_PLLM_VALUE(pPLLInit->PLLM));
    assert_param(IS_RCC_PLLN_VALUE(pPLLInit->PLLN));
    assert_param(IS_RCC_PLLP_VALUE(pPLLInit->PLLP));
    assert_param(IS_RCC_PLLQ_VALUE(pPLLInit->PLLQ));
    assert_param(IS_RCC_PLLR_VALUE(pPLLInit->PLLR));
    assert_param(IS_RCC_PLLS_VALUE(pPLLInit->PLLS));
    assert_param(IS_RCC_PLLT_VALUE(pPLLInit->PLLT));

    pllsrc = pPLLInit->PLLSource;

    /* Compute VCO input frequency and define range accordingly. First check clock source frequency */
    if (pllsrc == RCC_PLLSOURCE_HSI)
    {
      /* Clock source is HSI or HSI/HSIDIV */
      pllvco = HSI_VALUE >> ((RCC->CR & RCC_CR_HSIDIV) >> RCC_CR_HSIDIV_Pos);
    }
    else if (pllsrc == RCC_PLLSOURCE_HSE)
    {
      /* Clock source is HSE */
      pllvco = HSE_VALUE;
    }
    else
    {
      /* Clock source is CSI */
      pllvco = CSI_VALUE;
    }

    /* Compute VCO input frequency depending on M divider */
    pllvco = (pllvco / pPLLInit->PLLM);
    assert_param(IS_RCC_PLL_VCOINPUTFREQ(pllvco));

    if (pllvco >= RCC_PLL_INPUTRANGE2_FREQMAX)
    {
      pllvco = RCC_PLL_VCOINPUT_RANGE3 | RCC_PLL_VCO_HIGH;
    }
    else if (pllvco >= RCC_PLL_INPUTRANGE1_FREQMAX)
    {
      pllvco = RCC_PLL_VCOINPUT_RANGE2 | RCC_PLL_VCO_HIGH;
    }
    else if (pllvco >= RCC_PLL_INPUTRANGE0_FREQMAX)
    {
      pllvco = RCC_PLL_VCOINPUT_RANGE1 | RCC_PLL_VCO_HIGH;
    }
    else
    {
      pllvco = RCC_PLL_VCOINPUT_RANGE0 | RCC_PLL_VCO_LOW;
    }

    pllvco = (pllvco << ((RCC_PLLCFGR_PLL2RGE_Pos - RCC_PLLCFGR_PLL1RGE_Pos) * PLLnumber));

    /* Configure PLL source and PLLM divider */
    MODIFY_REG(RCC->PLLCKSELR, (RCC_PLLCKSELR_PLLSRC | (RCC_PLLCKSELR_DIVM1 << ((RCC_PLLCKSELR_DIVM2_Pos - RCC_PLLCKSELR_DIVM1_Pos)*PLLnumber))), \
               pllsrc | (pPLLInit->PLLM << (RCC_PLLCKSELR_DIVM1_Pos + ((RCC_PLLCKSELR_DIVM2_Pos - RCC_PLLCKSELR_DIVM1_Pos)*PLLnumber))));

    if ((RCC->PLLCKSELR & RCC_PLLCKSELR_PLLSRC) != pllsrc)
    {
      /* There is another PLL activated with another source */
      return HAL_ERROR;
    }

    /* Configure VCO input range, VCO selection and clear FRACEN */
    MODIFY_REG(RCC->PLLCFGR, (RCC_PLLCFGR_PLL1RGE | RCC_PLLCFGR_PLL1VCOSEL | RCC_PLLCFGR_PLL1FRACEN) << (((RCC_PLLCFGR_PLL2RGE_Pos - RCC_PLLCFGR_PLL1RGE_Pos)*PLLnumber)), \
               pllvco);

    /* Configure PLLN, PLLP, PLLQ, PLLR, PLLS and PLLT dividers */
    WRITE_REG(*p_rcc_pll_divr1_reg, ((pPLLInit->PLLN - 1U) |
                                     ((pPLLInit->PLLP - 1U) << RCC_PLL1DIVR1_DIVP_Pos) |
                                     ((pPLLInit->PLLQ - 1U) << RCC_PLL1DIVR1_DIVQ_Pos) |
                                     ((pPLLInit->PLLR - 1U) << RCC_PLL1DIVR1_DIVR_Pos)));
    WRITE_REG(*p_rcc_pll_divr2_reg, ((pPLLInit->PLLS - 1U) |
                                     ((pPLLInit->PLLT - 1U) << RCC_PLL2DIVR2_DIVT_Pos)));

    if (PLLnumber == RCC_PLL1_CONFIG)
    {
      SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1PEN);
    }

    if (pPLLInit->PLLFractional != 0U)
    {
      assert_param(IS_RCC_PLLFRACN_VALUE(pPLLInit->PLLFractional));

      p_rcc_pll_fracr_reg = &(RCC->PLL1FRACR) + (((uint32_t)0x02) * PLLnumber);

      /* Configure PLLFRACN */
      MODIFY_REG(*p_rcc_pll_fracr_reg, RCC_PLL1FRACR_FRACN, pPLLInit->PLLFractional << RCC_PLL1FRACR_FRACN_Pos);

      /* Enable PLLFRACLE */
      SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1FRACEN << ((RCC_PLLCFGR_PLL2FRACEN_Pos - RCC_PLLCFGR_PLL1FRACEN_Pos)*PLLnumber));
    }

    /* Enable the PLLx */
    SET_BIT(RCC->CR, RCC_CR_PLL1ON << ((RCC_CR_PLL2ON_Pos - RCC_CR_PLL1ON_Pos)*PLLnumber));

    /* Get Start Tick*/
    tickstart = HAL_GetTick();

    /* Wait till PLLx is ready */
    while (READ_BIT(RCC->CR, RCC_CR_PLL1RDY << ((RCC_CR_PLL2RDY_Pos - RCC_CR_PLL1RDY_Pos)*PLLnumber)) == 0U)
    {
      if ((HAL_GetTick() - tickstart) > RCC_PLL_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }
  }
  else
  {
    /* Disable outputs to save power when PLLx is off */
    MODIFY_REG(RCC->PLLCKSELR, ((RCC_PLLCKSELR_DIVM1 << (RCC_PLLCKSELR_DIVM1_Pos + ((RCC_PLLCKSELR_DIVM2_Pos - RCC_PLLCKSELR_DIVM1_Pos)*PLLnumber)))
                                | RCC_PLLCKSELR_PLLSRC), RCC_PLLSOURCE_NONE);
  }

  return ret;
}

/**
  * @brief  Compute PLL1 VCO output frequency
  * @retval Value of PLL1 VCO output frequency
  */
static uint32_t RCC_PLL1_GetVCOOutputFreq(void)
{
  uint32_t tmpreg1;
  uint32_t tmpreg2;
  uint32_t pllsrc;
  uint32_t pllm;
  uint32_t plln;
  uint32_t pllfracn;
  float_t frequency;

  /* Get PLL1 CKSELR and DIVR register values */
  tmpreg1 = RCC->PLLCKSELR;
  tmpreg2 = RCC->PLL1DIVR1;

  /* Retrieve PLL1 multiplication factor and divider */
  pllm = (tmpreg1 & RCC_PLLCKSELR_DIVM1) >> RCC_PLLCKSELR_DIVM1_Pos;
  plln = (tmpreg2 & RCC_PLL1DIVR1_DIVN) + 1U;

  if (pllm == 0U)
  {
    /* Prescaler disabled */
    return 0U;
  }

  /* Check if fractional part is enable */
  if ((RCC->PLLCFGR & RCC_PLLCFGR_PLL1FRACEN) != 0U)
  {
    pllfracn = (RCC->PLL1FRACR & RCC_PLL1FRACR_FRACN) >> RCC_PLL1FRACR_FRACN_Pos;
  }
  else
  {
    pllfracn = 0U;
  }

  /* determine PLL source */
  switch (tmpreg1 & RCC_PLLCKSELR_PLLSRC)
  {
    /* HSI used as PLL1 clock source */
    case RCC_PLLSOURCE_HSI:
      if (READ_BIT(RCC->CR, RCC_CR_HSIDIVF) != 0U)
      {
        pllsrc = HSI_VALUE >> ((RCC->CR & RCC_CR_HSIDIV) >> RCC_CR_HSIDIV_Pos);
      }
      else
      {
        /* Can't retrieve HSIDIV value */
        pllsrc = 0U;
      }
      break;

    /* HSE used as PLL1 clock source */
    case RCC_PLLSOURCE_HSE:
      pllsrc = HSE_VALUE;
      break;

    /* CSI used as PLL1 clock source */
    case RCC_PLLSOURCE_CSI:
      pllsrc = CSI_VALUE;
      break;

    default:
      pllsrc = 0U;
      break;
  }
  
  /* Compute VCO output frequency */
  frequency = ((float_t)pllsrc / (float_t)pllm) * ((float_t)plln + ((float_t)pllfracn / (float_t)0x2000U));
  
  return (uint32_t)frequency;
}

/**
  * @brief  Compute PLL2 VCO output frequency
  * @retval Value of PLL2 VCO output frequency
  */
static uint32_t RCC_PLL2_GetVCOOutputFreq(void)
{
  uint32_t tmpreg1;
  uint32_t tmpreg2;
  uint32_t pllsrc;
  uint32_t pllm;
  uint32_t plln;
  uint32_t pllfracn;
  float_t frequency;

  /* Get PLL2 CKSELR and DIVR register values */
  tmpreg1 = RCC->PLLCKSELR;
  tmpreg2 = RCC->PLL2DIVR1;

  /* Retrieve PLL2 multiplication factor and divider */
  pllm = (tmpreg1 & RCC_PLLCKSELR_DIVM2) >> RCC_PLLCKSELR_DIVM2_Pos;
  plln = (tmpreg2 & RCC_PLL2DIVR1_DIVN) + 1U;

  if (pllm == 0U)
  {
    /* Prescaler disabled */
    return 0U;
  }

  /* Check if fractional part is enable */
  if ((RCC->PLLCFGR & RCC_PLLCFGR_PLL2FRACEN) != 0U)
  {
    pllfracn = (RCC->PLL2FRACR & RCC_PLL2FRACR_FRACN) >> RCC_PLL2FRACR_FRACN_Pos;
  }
  else
  {
    pllfracn = 0U;
  }

  /* determine PLL source */
  switch (tmpreg1 & RCC_PLLCKSELR_PLLSRC)
  {
    /* HSI used as PLL2 clock source */
    case RCC_PLLSOURCE_HSI:
      if (READ_BIT(RCC->CR, RCC_CR_HSIDIVF) != 0U)
      {
        pllsrc = HSI_VALUE >> ((RCC->CR & RCC_CR_HSIDIV) >> RCC_CR_HSIDIV_Pos);
      }
      else
      {
        /* Can't retrieve HSIDIV value */
        pllsrc = 0U;
      }
      break;

    /* HSE used as PLL2 clock source */
    case RCC_PLLSOURCE_HSE:
      pllsrc = HSE_VALUE;
      break;

    /* CSI used as PLL2 clock source */
    case RCC_PLLSOURCE_CSI:
      pllsrc = CSI_VALUE;
      break;

    default:
      pllsrc = 0U;
      break;
  }

  /* Compute VCO output frequency */
  frequency = ((float_t)pllsrc / (float_t)pllm) * ((float_t)plln + ((float_t)pllfracn / (float_t)0x2000U));
  
  return (uint32_t)frequency;
}

/**
  * @brief  Compute PLL3 VCO output frequency
  * @retval Value of PLL3 VCO output frequency
  */
static uint32_t RCC_PLL3_GetVCOOutputFreq(void)
{
  uint32_t tmpreg1;
  uint32_t tmpreg2;
  uint32_t pllsrc;
  uint32_t pllm;
  uint32_t plln;
  uint32_t pllfracn;
  float_t frequency;

  /* Get PLL3 CKSELR and DIVR register values */
  tmpreg1 = RCC->PLLCKSELR;
  tmpreg2 = RCC->PLL3DIVR1;

  /* Retrieve PLL3 multiplication factor and divider */
  pllm = (tmpreg1 & RCC_PLLCKSELR_DIVM3) >> RCC_PLLCKSELR_DIVM3_Pos;
  plln = (tmpreg2 & RCC_PLL3DIVR1_DIVN) + 1U;

  if (pllm == 0U)
  {
    /* Prescaler disabled */
    return 0U;
  }

  /* Check if fractional part is enable */
  if ((RCC->PLLCFGR & RCC_PLLCFGR_PLL3FRACEN) != 0U)
  {
    pllfracn = (RCC->PLL3FRACR & RCC_PLL3FRACR_FRACN) >> RCC_PLL3FRACR_FRACN_Pos;
  }
  else
  {
    pllfracn = 0U;
  }

  /* determine PLL source */
  switch (tmpreg1 & RCC_PLLCKSELR_PLLSRC)
  {
    /* HSI used as PLL3 clock source */
    case RCC_PLLSOURCE_HSI:
      if (READ_BIT(RCC->CR, RCC_CR_HSIDIVF) != 0U)
      {
        pllsrc = HSI_VALUE >> ((RCC->CR & RCC_CR_HSIDIV) >> RCC_CR_HSIDIV_Pos);
      }
      else
      {
        /* Can't retrieve HSIDIV value */
        pllsrc = 0U;
      }
      break;

    /* HSE used as PLL3 clock source */
    case RCC_PLLSOURCE_HSE:
      pllsrc = HSE_VALUE;
      break;

    /* CSI used as PLL3 clock source */
    case RCC_PLLSOURCE_CSI:
      pllsrc = CSI_VALUE;
      break;

    default:
      pllsrc = 0U;
      break;
  }

  /* Compute VCO output frequency */
  frequency = ((float_t)pllsrc / (float_t)pllm) * ((float_t)plln + ((float_t)pllfracn / (float_t)0x2000U));
  
  return (uint32_t)frequency;
}

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
