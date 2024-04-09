/**
  ******************************************************************************
  * @file    stm32h7rsxx_ll_utils.c
  * @author  MCD Application Team
  * @brief   UTILS LL module driver.
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
/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_ll_utils.h"
#include "stm32h7rsxx_ll_rcc.h"
#include "stm32h7rsxx_ll_pwr.h"

#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32H7RSxx_LL_Driver
  * @{
  */

/** @addtogroup UTILS_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup UTILS_LL_Private_Constants
  * @{
  */
#define UTILS_MAX_FREQUENCY_SCALE0  467000000U      /*!< Maximum frequency for system clock at power scale 0, in Hz */
#define UTILS_MAX_FREQUENCY_SCALE1  365000000U      /*!< Maximum frequency for system clock at power scale 1, in Hz */

/* Defines used for PLL range */
#define UTILS_PLLVCO_INPUT_MIN1          1000000U   /*!< Frequency min for the medium range PLLVCO input, in Hz   */
#define UTILS_PLLVCO_INPUT_MAX1          2000000U   /*!< Frequency max for the medium range PLLVCO input, in Hz   */
#define UTILS_PLLVCO_INPUT_MIN2          2000000U   /*!< Frequency min for the wide range PLLVCO input, in Hz  */
#define UTILS_PLLVCO_INPUT_MAX2          4000000U   /*!< Frequency max for the wide range PLLVCO input, in Hz  */
#define UTILS_PLLVCO_INPUT_MIN3          4000000U   /*!< Frequency min for the wide range PLLVCO input, in Hz  */
#define UTILS_PLLVCO_INPUT_MAX3          8000000U   /*!< Frequency max for the wide range PLLVCO input, in Hz  */
#define UTILS_PLLVCO_INPUT_MIN4          8000000U   /*!< Frequency min for the wide range PLLVCO input, in Hz  */
#define UTILS_PLLVCO_INPUT_MAX4         16000000U   /*!< Frequency max for the wide range PLLVCO input, in Hz  */

#define UTILS_PLLVCO_MEDIUM_OUTPUT_MIN 150000000U   /*!< Frequency min for the medium range PLLVCO output, in Hz  */
#define UTILS_PLLVCO_WIDE_OUTPUT_MIN   400000000U   /*!< Frequency min for the wide range PLLVCO output, in Hz */
#define UTILS_PLLVCO_MEDIUM_OUTPUT_MAX 420000000U   /*!< Frequency max for the medium range PLLVCO output, in Hz  */
#define UTILS_PLLVCO_WIDE_OUTPUT_MAX  1600000000U   /*!< Frequency max for the wide range PLLVCO output, in Hz */

/* Defines used for HSE range */
#define UTILS_HSE_FREQUENCY_MIN          4000000U   /*!< Frequency min for HSE frequency, in Hz   */
#define UTILS_HSE_FREQUENCY_MAX         50000000U   /*!< Frequency max for HSE frequency, in Hz   */

/* Defines used for FLASH latency according to HCLK Frequency at   */
/* VOS0 (highest power/frequency) or VOS1 (lowest power/frequency) */
#define UTILS_SCALE0_LATENCY0_FREQ      40000000U   /*!< HCLK frequency to set FLASH latency 0 in power scale 0  */
#define UTILS_SCALE0_LATENCY1_FREQ      80000000U   /*!< HCLK frequency to set FLASH latency 1 in power scale 0  */
#define UTILS_SCALE0_LATENCY2_FREQ     120000000U   /*!< HCLK frequency to set FLASH latency 2 in power scale 0  */
#define UTILS_SCALE0_LATENCY3_FREQ     160000000U   /*!< HCLK frequency to set FLASH latency 3 in power scale 0  */
#define UTILS_SCALE0_LATENCY4_FREQ     200000000U   /*!< HCLK frequency to set FLASH latency 4 in power scale 0  */
#define UTILS_SCALE0_LATENCY5_FREQ     234000000U   /*!< HCLK frequency to set FLASH latency 5 in power scale 0  */

#define UTILS_SCALE1_LATENCY0_FREQ      36000000U   /*!< HCLK frequency to set FLASH latency 0 in power scale 1  */
#define UTILS_SCALE1_LATENCY1_FREQ      72000000U   /*!< HCLK frequency to set FLASH latency 1 in power scale 1  */
#define UTILS_SCALE1_LATENCY2_FREQ     108000000U   /*!< HCLK frequency to set FLASH latency 2 in power scale 1  */
#define UTILS_SCALE1_LATENCY3_FREQ     144000000U   /*!< HCLK frequency to set FLASH latency 3 in power scale 1  */
#define UTILS_SCALE1_LATENCY4_FREQ     180000000U   /*!< HCLK frequency to set FLASH latency 4 in power scale 1  */
#define UTILS_SCALE1_LATENCY5_FREQ     183000000U   /*!< HCLK frequency to set FLASH latency 5 in power scale 1  */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup UTILS_LL_Private_Macros
  * @{
  */
#define IS_LL_UTILS_SYSCLK_DIV(__VALUE__) (((__VALUE__) == LL_RCC_SYSCLK_DIV_1)   \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_2)   \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_4)   \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_8)   \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_16)  \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_64)  \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_128) \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_256) \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_512))

#define IS_LL_UTILS_AHB_DIV(__VALUE__)    (((__VALUE__) == LL_RCC_AHB_DIV_1)   \
                                           || ((__VALUE__) == LL_RCC_AHB_DIV_2)   \
                                           || ((__VALUE__) == LL_RCC_AHB_DIV_4)   \
                                           || ((__VALUE__) == LL_RCC_AHB_DIV_8)   \
                                           || ((__VALUE__) == LL_RCC_AHB_DIV_16)  \
                                           || ((__VALUE__) == LL_RCC_AHB_DIV_64)  \
                                           || ((__VALUE__) == LL_RCC_AHB_DIV_128) \
                                           || ((__VALUE__) == LL_RCC_AHB_DIV_256) \
                                           || ((__VALUE__) == LL_RCC_AHB_DIV_512))

#define IS_LL_UTILS_APB1_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB1_DIV_1) \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_2) \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_4) \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_8) \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_16))

#define IS_LL_UTILS_APB2_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB2_DIV_1) \
                                         || ((__VALUE__) == LL_RCC_APB2_DIV_2) \
                                         || ((__VALUE__) == LL_RCC_APB2_DIV_4) \
                                         || ((__VALUE__) == LL_RCC_APB2_DIV_8) \
                                         || ((__VALUE__) == LL_RCC_APB2_DIV_16))

#define IS_LL_UTILS_APB4_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB4_DIV_1) \
                                         || ((__VALUE__) == LL_RCC_APB4_DIV_2) \
                                         || ((__VALUE__) == LL_RCC_APB4_DIV_4) \
                                         || ((__VALUE__) == LL_RCC_APB4_DIV_8) \
                                         || ((__VALUE__) == LL_RCC_APB4_DIV_16))

#define IS_LL_UTILS_APB5_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB5_DIV_1) \
                                         || ((__VALUE__) == LL_RCC_APB5_DIV_2) \
                                         || ((__VALUE__) == LL_RCC_APB5_DIV_4) \
                                         || ((__VALUE__) == LL_RCC_APB5_DIV_8) \
                                         || ((__VALUE__) == LL_RCC_APB5_DIV_16))

#define IS_LL_UTILS_PLLM_VALUE(__VALUE__) ((1U <= (__VALUE__)) && ((__VALUE__) <= 63U))

#define IS_LL_UTILS_PLLN_VALUE(__VALUE__) ((8U <= (__VALUE__)) && ((__VALUE__) <= 420U))

#define IS_LL_UTILS_PLLP_VALUE(__VALUE__) ((1U <= (__VALUE__)) && ((__VALUE__) <= 128U))

#define IS_LL_UTILS_FRACN_VALUE(__VALUE__) ((__VALUE__) <= 0x1FFFU)

#define IS_LL_UTILS_PLLVCO_INPUT(__VALUE__, __RANGE__) \
  ((((__RANGE__) == LL_RCC_PLLINPUTRANGE_1_2) && \
    (UTILS_PLLVCO_INPUT_MIN1 <= (__VALUE__)) && ((__VALUE__) <= UTILS_PLLVCO_INPUT_MAX1)) || \
   (((__RANGE__) == LL_RCC_PLLINPUTRANGE_2_4) && \
    (UTILS_PLLVCO_INPUT_MIN2 <= (__VALUE__)) && ((__VALUE__) <= UTILS_PLLVCO_INPUT_MAX2)) || \
   (((__RANGE__) == LL_RCC_PLLINPUTRANGE_4_8) && \
    (UTILS_PLLVCO_INPUT_MIN3 <= (__VALUE__)) && ((__VALUE__) <= UTILS_PLLVCO_INPUT_MAX3)) || \
   (((__RANGE__) == LL_RCC_PLLINPUTRANGE_8_16) && \
    (UTILS_PLLVCO_INPUT_MIN4 <= (__VALUE__)) && ((__VALUE__) <= UTILS_PLLVCO_INPUT_MAX4)))

#define IS_LL_UTILS_PLLVCO_OUTPUT(__VALUE__, __RANGE__) \
  ((((__RANGE__) == LL_RCC_PLLVCORANGE_MEDIUM) && \
    (UTILS_PLLVCO_MEDIUM_OUTPUT_MIN <= (__VALUE__)) && ((__VALUE__) <= UTILS_PLLVCO_MEDIUM_OUTPUT_MAX)) || \
   (((__RANGE__) == LL_RCC_PLLVCORANGE_WIDE) && \
    (UTILS_PLLVCO_WIDE_OUTPUT_MIN <= (__VALUE__)) && ((__VALUE__) <= UTILS_PLLVCO_WIDE_OUTPUT_MAX)))

#define IS_LL_UTILS_CHECK_VCO_RANGES(__RANGEIN__, __RANGEOUT__) \
  ((((__RANGEIN__) == LL_RCC_PLLINPUTRANGE_1_2) && \
    ((__RANGEOUT__) == LL_RCC_PLLVCORANGE_MEDIUM)) || \
   (((__RANGEIN__) != LL_RCC_PLLINPUTRANGE_1_2) && \
    ((__RANGEOUT__) == LL_RCC_PLLVCORANGE_WIDE)))

#define IS_LL_UTILS_PLL_FREQUENCY(__VALUE__) \
  ((LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE0) ? \
   ((__VALUE__) <= UTILS_MAX_FREQUENCY_SCALE0) : ((__VALUE__) <= UTILS_MAX_FREQUENCY_SCALE1))

#define IS_LL_UTILS_HSE_BYPASS(__STATE__) \
  (((__STATE__) == LL_UTILS_HSEBYPASS_ON) || ((__STATE__) == LL_UTILS_HSEBYPASS_OFF))

#define IS_LL_UTILS_HSE_FREQUENCY(__FREQUENCY__) \
  (((__FREQUENCY__) >= UTILS_HSE_FREQUENCY_MIN) && ((__FREQUENCY__) <= UTILS_HSE_FREQUENCY_MAX))
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup UTILS_LL_Private_Functions UTILS Private functions
  * @{
  */
static uint32_t    UTILS_GetPLLOutputFrequency(uint32_t PLL_InputFrequency,
                                               const LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct);
static ErrorStatus UTILS_EnablePLLAndSwitchSystem(uint32_t SYSCLK_Frequency,
                                                  LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct);
static ErrorStatus UTILS_IsPLLsNotBusy(void);
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup UTILS_LL_Exported_Functions
  * @{
  */

/** @addtogroup UTILS_LL_EF_DELAY
  * @{
  */
/**
  * @brief  This function configures the Cortex-M SysTick source to have 1ms time base.
  * @note   When a RTOS is used, it is recommended to avoid changing the Systick
  *         configuration by calling this function, for a delay use rather osDelay RTOS service.
  * @param  CPU_Frequency Core frequency in Hz
  * @note   CPU_Frequency can be calculated thanks to RCC helper macro or function
  *         @ref LL_RCC_GetSystemClocksFreq
  * @retval None
  */
void LL_Init1msTick(uint32_t CPU_Frequency)
{
  /* Use frequency provided in argument */
  LL_InitTick(CPU_Frequency, 1000U);
}


/**
  * @brief  This function provides accurate delay (in milliseconds) based
  *         on SysTick counter flag
  * @note   When a RTOS is used, it is recommended to avoid using blocking delay
  *         and use rather osDelay service.
  * @note   To respect 1ms timebase, user should call @ref LL_Init1msTick function which
  *         will configure Systick to 1ms
  * @param  Delay specifies the delay time length, in milliseconds.
  * @retval None
  */
void LL_mDelay(uint32_t Delay)
{
  uint32_t count = Delay;
  __IO uint32_t  tmp = SysTick->CTRL;  /* Clear the COUNTFLAG first */
  /* Add this code to indicate that local variable is not used */
  ((void)tmp);

  /* Add a period to ensure minimum wait */
  if (count < LL_MAX_DELAY)
  {
    count++;
  }

  while (count != 0U)
  {
    if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0U)
    {
      count--;
    }
  }
}

/**
  * @}
  */

/** @addtogroup UTILS_EF_SYSTEM
  *  @brief    System Configuration functions
  *
  @verbatim
 ===============================================================================
           ##### System Configuration functions #####
 ===============================================================================
    [..]
         System, AXI, AHB and APB buses clocks configuration

         (+) The maximum frequency of the SYSCLK is 464 MHz and HCLK is 232 MHz.
         (+) The maximum frequency of the PCLK1, PCLK2, PCLK4 and PCLK5 is 116 MHz.
  @endverbatim
  @internal
             Depending on the device voltage range, the maximum frequency should be
             adapted accordingly:
             (++) +---------------------------------------------------------------------------+
             (++) |  Wait states        |  AXI interface clock frequency (MHz) vs Vcore range |
             (++) |                     |-----------------------------------------------------|
             (++) |  (Latency)          |      voltage scale 1     |      voltage scale 0     |
             (++) |                     |       1.15V - 1.26V      |       1.26V - 1.40V      |
             (++) |---------------------|--------------------------|--------------------------|
             (++) | 0WS (1 CPU cycle)   |     0 < HCLK <= 36       |     0 < HCLK <= 40       |
             (++) |---------------------|--------------------------|--------------------------|
             (++) | 1WS (2 CPU cycles)  |    36 < HCLK <= 72       |    40 < HCLK <= 80       |
             (++) |---------------------|--------------------------|--------------------------|
             (++) | 2WS (3 CPU cycles)  |    72 < HCLK <= 108      |    80 < HCLK <= 120      |
             (++) |---------------------|--------------------------|--------------------------|
             (++) | 3WS (4 CPU cycles)  |   108 < HCLK <= 144      |   120 < HCLK <= 160      |
             (++) |---------------------|--------------------------|--------------------------|
             (++) | 4WS (5 CPU cycles)  |   144 < HCLK <= 180      |   160 < HCLK <= 200      |
             (++) |---------------------|--------------------------|--------------------------|
             (++) | 5WS (6 CPU cycles)  |   180 < HCLK <= 216      |   200 < HCLK <= 240      |
             (++) |---------------------|--------------------------|--------------------------|
             (++) | 6WS (7 CPU cycles)  |   216 < HCLK <= 252      |                          |
             (++) |---------------------|--------------------------|--------------------------|

  @endinternal
  * @{
  */

/**
  * @brief  This function sets directly SystemCoreClock CMSIS variable.
  * @note   Variable can be calculated also through SystemCoreClockUpdate function.
  * @param  CPU_Frequency Core frequency in Hz
  * @note   CPU_Frequency can be calculated thanks to RCC helper macro or function
  *         @ref LL_RCC_GetSystemClocksFreq
  * @retval None
  */
void LL_SetSystemCoreClock(uint32_t CPU_Frequency)
{
  /* SYSCLK clock frequency */
  SystemCoreClock = CPU_Frequency;
}

/**
  * @brief  This function configures system clock at maximum frequency with HSI as clock source of the PLL
  * @note   The application need to ensure that PLL is disabled.
  * @note   Function is based on the following formula:
  *         - PLL output frequency = (((HSI frequency / PLLM) * PLLN) / PLLP)
  *         - PLLM: ensure that the VCO input frequency ranges from 1 to 16 MHz (PLLVCO_input = HSI frequency / PLLM)
  *         - PLLN: ensure that the VCO output frequency is
  *                   between 150 and 420 MHz (Medium) or
  *                   between 400 to 1600 MHz (Wide) (PLLVCO_output = PLLVCO_input * PLLN)
  *         - PLLP: ensure that max frequency at 464 MHz is reached (PLLVCO_output / PLLP)
  * @param  UTILS_PLLInitStruct pointer to a @ref LL_UTILS_PLLInitTypeDef structure that contains
  *                             the configuration information for the PLL.
  * @param  UTILS_ClkInitStruct pointer to a @ref LL_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Max frequency configuration done
  *          - ERROR: Max frequency configuration not done
  *
  */
ErrorStatus LL_PLL_ConfigSystemClock_HSI(LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct,
                                         LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct)
{
  ErrorStatus status;
#ifdef  USE_FULL_ASSERT
  uint32_t vcoinput_freq;
  uint32_t vcooutput_freq;
#endif /* USE_FULL_ASSERT */
  uint32_t pllfreq;
  uint32_t hsi_clk;

  /* Check the parameters */
  assert_param(IS_LL_UTILS_PLLM_VALUE(UTILS_PLLInitStruct->PLLM));
  assert_param(IS_LL_UTILS_PLLN_VALUE(UTILS_PLLInitStruct->PLLN));
  assert_param(IS_LL_UTILS_PLLP_VALUE(UTILS_PLLInitStruct->PLLP));
  assert_param(IS_LL_UTILS_FRACN_VALUE(UTILS_PLLInitStruct->FRACN));

  hsi_clk = (HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos));

  /* Check VCO Input frequency */
#ifdef  USE_FULL_ASSERT
  vcoinput_freq = hsi_clk / UTILS_PLLInitStruct->PLLM;
  assert_param(IS_LL_UTILS_PLLVCO_INPUT(vcoinput_freq, UTILS_PLLInitStruct->VCO_Input));
#endif /* USE_FULL_ASSERT */

  /* Check VCO Output frequency */
#ifdef  USE_FULL_ASSERT
  vcooutput_freq = LL_RCC_CalcPLLClockFreq(hsi_clk, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN,
                                           UTILS_PLLInitStruct->FRACN, 1UL);
  assert_param(IS_LL_UTILS_PLLVCO_OUTPUT(vcooutput_freq, UTILS_PLLInitStruct->VCO_Output));
#endif /* USE_FULL_ASSERT */

  /* Check VCO Input ranges */
  assert_param(IS_LL_UTILS_CHECK_VCO_RANGES(UTILS_PLLInitStruct->VCO_Input, UTILS_PLLInitStruct->VCO_Output));

  /* Check that no PLL is enabled and thus ready for configuration */
  if (UTILS_IsPLLsNotBusy() == SUCCESS)
  {
    /* Calculate the new PLL output frequency */
    pllfreq = UTILS_GetPLLOutputFrequency(hsi_clk, UTILS_PLLInitStruct);

    /* Enable HSI if not enabled */
    if (LL_RCC_HSI_IsReady() != 1U)
    {
      LL_RCC_HSI_Enable();
      while (LL_RCC_HSI_IsReady() != 1U)
      {
        /* Wait for HSI ready */
      }
    }

    /* Configure PLL */
    LL_RCC_PLL1FRACN_Disable();
    LL_RCC_PLL_SetSource(LL_RCC_PLLSOURCE_HSI);
    LL_RCC_PLL1_SetVCOInputRange(UTILS_PLLInitStruct->VCO_Input);
    LL_RCC_PLL1_SetVCOOutputRange(UTILS_PLLInitStruct->VCO_Output);
    LL_RCC_PLL1_SetM(UTILS_PLLInitStruct->PLLM);
    LL_RCC_PLL1_SetN(UTILS_PLLInitStruct->PLLN);
    LL_RCC_PLL1_SetP(UTILS_PLLInitStruct->PLLP);
    LL_RCC_PLL1_SetFRACN(UTILS_PLLInitStruct->FRACN);
    LL_RCC_PLL1FRACN_Enable();
    LL_RCC_PLL1_SetFRACN(UTILS_PLLInitStruct->FRACN);

    /* Enable PLL and switch system clock to PLL */
    status = UTILS_EnablePLLAndSwitchSystem(pllfreq, UTILS_ClkInitStruct);
  }
  else
  {
    /* Current PLL configuration cannot be modified */
    status = ERROR;
  }

  return status;
}

/**
  * @brief  This function configures system clock at maximum frequency with CSI as clock source of the PLL
  * @note   The application need to ensure that PLL is disabled.
  * @note   Function is based on the following formula:
  *         - PLL output frequency = (((CSI frequency / PLLM) * PLLN) / PLLP)
  *         - PLLM: ensure that the VCO input frequency ranges from 1 to 4 MHz (PLLVCO_input = CSI frequency / PLLM)
  *         - PLLN: ensure that the VCO output frequency is
  *                   between 150 and 420 MHz (Medium) or
  *                   between 400 to 1600 MHz (Wide) (PLLVCO_output = PLLVCO_input * PLLN)
  *         - PLLP: ensure that max frequency at 464 MHz is reached (PLLVCO_output / PLLP)
  * @param  UTILS_PLLInitStruct pointer to a @ref LL_UTILS_PLLInitTypeDef structure that contains
  *                             the configuration information for the PLL.
  * @param  UTILS_ClkInitStruct pointer to a @ref LL_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Max frequency configuration done
  *          - ERROR: Max frequency configuration not done
  *
  */
ErrorStatus LL_PLL_ConfigSystemClock_CSI(LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct,
                                         LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct)
{
  ErrorStatus status;
#ifdef  USE_FULL_ASSERT
  uint32_t vcoinput_freq;
  uint32_t vcooutput_freq;
#endif /* USE_FULL_ASSERT */
  uint32_t pllfreq;

  /* Check the parameters */
  assert_param(IS_LL_UTILS_PLLM_VALUE(UTILS_PLLInitStruct->PLLM));
  assert_param(IS_LL_UTILS_PLLN_VALUE(UTILS_PLLInitStruct->PLLN));
  assert_param(IS_LL_UTILS_PLLP_VALUE(UTILS_PLLInitStruct->PLLP));
  assert_param(IS_LL_UTILS_FRACN_VALUE(UTILS_PLLInitStruct->FRACN));

  /* Check VCO Input frequency */
#ifdef  USE_FULL_ASSERT
  vcoinput_freq = CSI_VALUE / UTILS_PLLInitStruct->PLLM;
  assert_param(IS_LL_UTILS_PLLVCO_INPUT(vcoinput_freq, UTILS_PLLInitStruct->VCO_Input));
#endif /* USE_FULL_ASSERT */

  /* Check VCO Output frequency */
#ifdef  USE_FULL_ASSERT
  vcooutput_freq = LL_RCC_CalcPLLClockFreq(CSI_VALUE, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN,
                                           UTILS_PLLInitStruct->FRACN, 1UL);
  assert_param(IS_LL_UTILS_PLLVCO_OUTPUT(vcooutput_freq, UTILS_PLLInitStruct->VCO_Output));
#endif /* USE_FULL_ASSERT */

  /* Check VCO Input ranges */
  assert_param(IS_LL_UTILS_CHECK_VCO_RANGES(UTILS_PLLInitStruct->VCO_Input, UTILS_PLLInitStruct->VCO_Output));

  /* Check that no PLL is enabled and thus ready for configuration */
  if (UTILS_IsPLLsNotBusy() == SUCCESS)
  {
    /* Calculate the new PLL output frequency */
    pllfreq = UTILS_GetPLLOutputFrequency(CSI_VALUE, UTILS_PLLInitStruct);

    /* Enable CSI if not enabled */
    if (LL_RCC_CSI_IsReady() != 1U)
    {
      LL_RCC_CSI_Enable();
      while (LL_RCC_CSI_IsReady() != 1U)
      {
        /* Wait for CSI ready */
      }
    }

    /* Configure PLL */
    LL_RCC_PLL1FRACN_Disable();
    LL_RCC_PLL_SetSource(LL_RCC_PLLSOURCE_CSI);
    LL_RCC_PLL1_SetVCOInputRange(UTILS_PLLInitStruct->VCO_Input);
    LL_RCC_PLL1_SetVCOOutputRange(UTILS_PLLInitStruct->VCO_Output);
    LL_RCC_PLL1_SetM(UTILS_PLLInitStruct->PLLM);
    LL_RCC_PLL1_SetN(UTILS_PLLInitStruct->PLLN);
    LL_RCC_PLL1_SetP(UTILS_PLLInitStruct->PLLP);
    LL_RCC_PLL1_SetFRACN(UTILS_PLLInitStruct->FRACN);
    LL_RCC_PLL1FRACN_Enable();
    LL_RCC_PLL1_SetFRACN(UTILS_PLLInitStruct->FRACN);

    /* Enable PLL and switch system clock to PLL */
    status = UTILS_EnablePLLAndSwitchSystem(pllfreq, UTILS_ClkInitStruct);
  }
  else
  {
    /* Current PLL configuration cannot be modified */
    status = ERROR;
  }

  return status;
}

/**
  * @brief  This function configures system clock with HSE as clock source of the PLL
  * @note   The application need to ensure that PLL is disabled.
  * @note   Function is based on the following formula:
  *         - PLL output frequency = (((HSE frequency / PLLM) * PLLN) / PLLP)
  *         - PLLM: ensure that the VCO input frequency ranges from 1 to 4 MHz (PLLVCO_input = CSI frequency / PLLM)
  *         - PLLN: ensure that the VCO output frequency is
  *                   between 150 and 420 MHz (Medium) or
  *                   between 400 to 1600 MHz (Wide) (PLLVCO_output = PLLVCO_input * PLLN)
  *         - PLLP: ensure that max frequency at 464 MHz is reached (PLLVCO_output / PLLP)
  * @param  HSEFrequency Value between Min_Data = 4000000 and Max_Data = 50000000
  * @param  HSEBypass This parameter can be one of the following values:
  *         @arg @ref LL_UTILS_HSEBYPASS_ON
  *         @arg @ref LL_UTILS_HSEBYPASS_OFF
  * @param  UTILS_PLLInitStruct pointer to a @ref LL_UTILS_PLLInitTypeDef structure that contains
  *                             the configuration information for the PLL.
  * @param  UTILS_ClkInitStruct pointer to a @ref LL_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Max frequency configuration done
  *          - ERROR: Max frequency configuration not done
  *
  */
ErrorStatus LL_PLL_ConfigSystemClock_HSE(uint32_t HSEFrequency, uint32_t HSEBypass,
                                         LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct,
                                         LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct)
{
  ErrorStatus status;
#ifdef  USE_FULL_ASSERT
  uint32_t vcoinput_freq;
  uint32_t vcooutput_freq;
#endif /* USE_FULL_ASSERT */
  uint32_t pllfreq;

  /* Check the parameters */
  assert_param(IS_LL_UTILS_PLLM_VALUE(UTILS_PLLInitStruct->PLLM));
  assert_param(IS_LL_UTILS_PLLN_VALUE(UTILS_PLLInitStruct->PLLN));
  assert_param(IS_LL_UTILS_PLLP_VALUE(UTILS_PLLInitStruct->PLLP));
  assert_param(IS_LL_UTILS_FRACN_VALUE(UTILS_PLLInitStruct->FRACN));
  assert_param(IS_LL_UTILS_HSE_FREQUENCY(HSEFrequency));
  assert_param(IS_LL_UTILS_HSE_BYPASS(HSEBypass));

  /* Check VCO Input frequency */
#ifdef  USE_FULL_ASSERT
  vcoinput_freq = HSEFrequency / UTILS_PLLInitStruct->PLLM;
  assert_param(IS_LL_UTILS_PLLVCO_INPUT(vcoinput_freq, UTILS_PLLInitStruct->VCO_Input));
#endif /* USE_FULL_ASSERT */

  /* Check VCO output frequency */
#ifdef  USE_FULL_ASSERT
  vcooutput_freq = LL_RCC_CalcPLLClockFreq(HSEFrequency, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN,
                                           UTILS_PLLInitStruct->FRACN, 1U);
  assert_param(IS_LL_UTILS_PLLVCO_OUTPUT(vcooutput_freq, UTILS_PLLInitStruct->VCO_Output));
#endif /* USE_FULL_ASSERT */

  /* Check VCO Input/output ranges compatibility */
  assert_param(IS_LL_UTILS_CHECK_VCO_RANGES(UTILS_PLLInitStruct->VCO_Input, UTILS_PLLInitStruct->VCO_Output));

  /* Check that no PLL is enabled and thus ready for configuration */
  if (UTILS_IsPLLsNotBusy() == SUCCESS)
  {
    /* Calculate the new PLL output frequency */
    pllfreq = UTILS_GetPLLOutputFrequency(HSEFrequency, UTILS_PLLInitStruct);

    /* Enable HSE if not enabled */
    if (LL_RCC_HSE_IsReady() != 1U)
    {
      /* Check if need to enable HSE bypass feature or not */
      if (HSEBypass == LL_UTILS_HSEBYPASS_ON)
      {
        LL_RCC_HSE_EnableBypass();
      }
      else
      {
        LL_RCC_HSE_DisableBypass();
      }

      /* Enable HSE */
      LL_RCC_HSE_Enable();
      while (LL_RCC_HSE_IsReady() != 1U)
      {
        /* Wait for HSE ready */
      }
    }

    /* Configure PLL */
    LL_RCC_PLL1FRACN_Disable();
    LL_RCC_PLL_SetSource(LL_RCC_PLLSOURCE_HSE);
    LL_RCC_PLL1_SetVCOInputRange(UTILS_PLLInitStruct->VCO_Input);
    LL_RCC_PLL1_SetVCOOutputRange(UTILS_PLLInitStruct->VCO_Output);
    LL_RCC_PLL1_SetM(UTILS_PLLInitStruct->PLLM);
    LL_RCC_PLL1_SetN(UTILS_PLLInitStruct->PLLN);
    LL_RCC_PLL1_SetP(UTILS_PLLInitStruct->PLLP);
    LL_RCC_PLL1_SetFRACN(UTILS_PLLInitStruct->FRACN);
    LL_RCC_PLL1FRACN_Enable();
    LL_RCC_PLL1_SetFRACN(UTILS_PLLInitStruct->FRACN);
    LL_RCC_PLL1FRACN_Enable();

    /* Enable PLL and switch system clock to PLL */
    status = UTILS_EnablePLLAndSwitchSystem(pllfreq, UTILS_ClkInitStruct);
  }
  else
  {
    /* Current PLL configuration cannot be modified */
    status = ERROR;
  }

  return status;
}

/**
  * @}
  */

/**
  * @brief  Update number of Flash wait states in line with new frequency and current
            voltage range.
  * @param  HCLK_Frequency  HCLK frequency
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Latency has been modified
  *          - ERROR: Latency cannot be modified
  */
ErrorStatus LL_SetFlashLatency(uint32_t HCLK_Frequency)
{
  ErrorStatus status = SUCCESS;
  uint32_t timeout;
  uint32_t getlatency;
  uint32_t latency;

  /* Frequency cannot be equal to 0 */
  if (HCLK_Frequency == 0U)
  {
    status = ERROR;
  }
  else
  {
    if (LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE0) /* Scale 0 */
    {
      if ((HCLK_Frequency > UTILS_SCALE0_LATENCY4_FREQ) && (HCLK_Frequency <= UTILS_SCALE0_LATENCY5_FREQ))
      {
        latency = LL_FLASH_LATENCY_5; /* 5WS (6 CPU cycles) */
      }
      else if ((HCLK_Frequency > UTILS_SCALE0_LATENCY3_FREQ) && (HCLK_Frequency <= UTILS_SCALE0_LATENCY4_FREQ))
      {
        latency = LL_FLASH_LATENCY_4; /* 4WS (5 CPU cycles) */
      }
      else if ((HCLK_Frequency > UTILS_SCALE0_LATENCY2_FREQ) && (HCLK_Frequency <= UTILS_SCALE0_LATENCY3_FREQ))
      {
        latency = LL_FLASH_LATENCY_3; /* 3WS (4 CPU cycles) */
      }
      else if ((HCLK_Frequency > UTILS_SCALE0_LATENCY1_FREQ) && (HCLK_Frequency <= UTILS_SCALE0_LATENCY2_FREQ))
      {
        latency = LL_FLASH_LATENCY_2; /* 2WS (3 CPU cycles) */
      }
      else if ((HCLK_Frequency > UTILS_SCALE0_LATENCY0_FREQ) && (HCLK_Frequency <= UTILS_SCALE0_LATENCY1_FREQ))
      {
        latency = LL_FLASH_LATENCY_1; /* 1WS (2 CPU cycles) */
      }
      else
      {
        latency = LL_FLASH_LATENCY_0; /* 0WS (1 CPU cycles) */
      }
    }
    else /* Scale 1 */
    {
      if ((HCLK_Frequency > UTILS_SCALE1_LATENCY4_FREQ) && (HCLK_Frequency <= UTILS_SCALE1_LATENCY5_FREQ))
      {
        latency = LL_FLASH_LATENCY_5; /* 5WS (6 CPU cycles) */
      }
      else if ((HCLK_Frequency > UTILS_SCALE1_LATENCY3_FREQ) && (HCLK_Frequency <= UTILS_SCALE1_LATENCY4_FREQ))
      {
        latency = LL_FLASH_LATENCY_4; /* 4WS (5 CPU cycles) */
      }
      else if ((HCLK_Frequency > UTILS_SCALE1_LATENCY2_FREQ) && (HCLK_Frequency <= UTILS_SCALE1_LATENCY3_FREQ))
      {
        latency = LL_FLASH_LATENCY_3; /* 3WS (4 CPU cycles) */
      }
      else if ((HCLK_Frequency > UTILS_SCALE1_LATENCY1_FREQ) && (HCLK_Frequency <= UTILS_SCALE1_LATENCY2_FREQ))
      {
        latency = LL_FLASH_LATENCY_2; /* 2WS (3 CPU cycles) */
      }
      else if ((HCLK_Frequency > UTILS_SCALE1_LATENCY0_FREQ) && (HCLK_Frequency <= UTILS_SCALE1_LATENCY1_FREQ))
      {
        latency = LL_FLASH_LATENCY_1; /* 1WS (2 CPU cycles) */
      }
      else
      {
        latency = LL_FLASH_LATENCY_0; /* 0WS (1 CPU cycles) */
      }
    }

    LL_FLASH_SetLatency(latency);

    /* Check that the new number of wait states is taken into account to access the Flash
    memory by reading the FLASH_ACR register */
    timeout = 2;
    do
    {
      /* Wait for Flash latency to be updated */
      getlatency = LL_FLASH_GetLatency();
      timeout--;
    } while ((getlatency != latency) && (timeout > 0U));

    if (getlatency != latency)
    {
      status = ERROR;
    }
  }

  return status;
}


/**
  * @}
  */

/** @addtogroup UTILS_LL_Private_Functions
  * @{
  */


/**
  * @brief  Function to Get PLL Output frequency
  * @param  PLL_InputFrequency  PLL input frequency (in Hz)
  * @param  UTILS_PLLInitStruct pointer to a @ref LL_UTILS_PLLInitTypeDef structure that contains
  *                             the configuration information for the PLL.
  * @retval PLL output frequency (in Hz)
  */
static uint32_t UTILS_GetPLLOutputFrequency(uint32_t PLL_InputFrequency,
                                            const LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct)
{
  uint32_t pllfreq;

  /* Check the parameters */
  assert_param(IS_LL_UTILS_PLLM_VALUE(UTILS_PLLInitStruct->PLLM));
  assert_param(IS_LL_UTILS_PLLN_VALUE(UTILS_PLLInitStruct->PLLN));
  assert_param(IS_LL_UTILS_PLLP_VALUE(UTILS_PLLInitStruct->PLLP));
  assert_param(IS_LL_UTILS_FRACN_VALUE(UTILS_PLLInitStruct->FRACN));

  pllfreq = LL_RCC_CalcPLLClockFreq(PLL_InputFrequency, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN,
                                    UTILS_PLLInitStruct->FRACN, UTILS_PLLInitStruct->PLLP);

  return pllfreq;
}

/**
  * @brief  Check that all PLLs are not busy therefore configuration can be done
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: All PLLs are ready so configuration can be done
  *          - ERROR: One PLL at least is busy
  */
static ErrorStatus UTILS_IsPLLsNotBusy(void)
{
  ErrorStatus status = SUCCESS;

  /* Check if one of the PLL1 is busy */
  if (LL_RCC_PLL1_IsReady() != 0U)
  {
    /* PLL1 configuration cannot be done */
    status = ERROR;
  }

  /* Check if one of the PLL2 is busy */
  if (LL_RCC_PLL2_IsReady() != 0U)
  {
    /* PLL2 configuration cannot be done */
    status = ERROR;
  }

  /* Check if one of the PLL3 is busy */
  if (LL_RCC_PLL3_IsReady() != 0U)
  {
    /* PLL3 configuration cannot be done */
    status = ERROR;
  }

  return status;
}

/**
  * @brief  Function to enable PLL and switch system clock to PLL
  * @param  SYSCLK_Frequency SYSCLK frequency
  * @param  UTILS_ClkInitStruct pointer to a @ref LL_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: No problem to switch system to PLL
  *          - ERROR: Problem to switch system to PLL
  */
static ErrorStatus UTILS_EnablePLLAndSwitchSystem(uint32_t SYSCLK_Frequency,
                                                  LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct)
{
  ErrorStatus status = SUCCESS;
  uint32_t new_sysclk_frequency;
  uint32_t new_hclk_frequency;

  assert_param(IS_LL_UTILS_SYSCLK_DIV(UTILS_ClkInitStruct->SYSCLKDivider));
  assert_param(IS_LL_UTILS_AHB_DIV(UTILS_ClkInitStruct->AHBCLKDivider));
  assert_param(IS_LL_UTILS_APB1_DIV(UTILS_ClkInitStruct->APB1CLKDivider));
  assert_param(IS_LL_UTILS_APB2_DIV(UTILS_ClkInitStruct->APB2CLKDivider));
  assert_param(IS_LL_UTILS_APB4_DIV(UTILS_ClkInitStruct->APB4CLKDivider));
  assert_param(IS_LL_UTILS_APB5_DIV(UTILS_ClkInitStruct->APB5CLKDivider));

  /* Calculate the new HCLK frequency */
  new_sysclk_frequency = LL_RCC_CALC_SYSCLK_FREQ(SYSCLK_Frequency, UTILS_ClkInitStruct->SYSCLKDivider);
  new_hclk_frequency = LL_RCC_CALC_HCLK_FREQ(new_sysclk_frequency, UTILS_ClkInitStruct->AHBCLKDivider);

  /* Increasing the number of wait states because of higher CPU frequency */
  if (SystemCoreClock < new_sysclk_frequency)
  {
    /* Set FLASH latency to highest latency */
    status = LL_SetFlashLatency(new_hclk_frequency);
  }

  /* Update system clock configuration */
  if (status == SUCCESS)
  {
    /* Enable PLL */
    LL_RCC_PLL1_Enable();
    while (LL_RCC_PLL1_IsReady() != 1U)
    {
      /* Wait for PLL ready */
    }

    LL_RCC_PLL1P_Enable();

    /* Set All APBxPrescaler to the Highest Divider */
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_16);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_16);
    LL_RCC_SetAPB4Prescaler(LL_RCC_APB4_DIV_16);
    LL_RCC_SetAPB5Prescaler(LL_RCC_APB5_DIV_16);

    /* Set SYS prescaler*/
    LL_RCC_SetSysPrescaler(UTILS_ClkInitStruct->SYSCLKDivider);

    /* Set AHB prescaler*/
    LL_RCC_SetAHBPrescaler(UTILS_ClkInitStruct->AHBCLKDivider);

    /* Sysclk activation on the main PLL */
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL1);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL1)
    {
      /* Wait for system clock switch to PLL */
    }

    /* Set APBn prescaler*/
    LL_RCC_SetAPB1Prescaler(UTILS_ClkInitStruct->APB1CLKDivider);
    LL_RCC_SetAPB2Prescaler(UTILS_ClkInitStruct->APB2CLKDivider);
    LL_RCC_SetAPB4Prescaler(UTILS_ClkInitStruct->APB4CLKDivider);
    LL_RCC_SetAPB5Prescaler(UTILS_ClkInitStruct->APB5CLKDivider);

    /* Decreasing the number of wait states because of lower CPU frequency */
    if (SystemCoreClock > new_sysclk_frequency)
    {
      /* Set FLASH latency to lowest latency */
      status = LL_SetFlashLatency(new_hclk_frequency);
    }

    /* Update SystemCoreClock variable */
    if (status == SUCCESS)
    {
      LL_SetSystemCoreClock(new_sysclk_frequency);
    }
  }

  return status;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
