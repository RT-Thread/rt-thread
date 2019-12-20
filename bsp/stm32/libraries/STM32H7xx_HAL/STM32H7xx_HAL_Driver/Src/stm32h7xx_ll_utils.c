/**
  ******************************************************************************
  * @file    stm32h7xx_ll_utils.c
  * @author  MCD Application Team
  * @brief   UTILS LL module driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
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
#include "stm32h7xx_ll_utils.h"
#include "stm32h7xx_ll_rcc.h"
#include "stm32h7xx_ll_pwr.h"

#ifdef  USE_FULL_ASSERT
  #include "stm32_assert.h"
#else
  #define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32H7xx_LL_Driver
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
#define UTILS_MAX_FREQUENCY_SCALE1  400000000U      /*!< Maximum frequency for system clock at power scale1, in Hz */
#define UTILS_MAX_FREQUENCY_SCALE2  300000000U      /*!< Maximum frequency for system clock at power scale2, in Hz */
#define UTILS_MAX_FREQUENCY_SCALE3  200000000U      /*!< Maximum frequency for system clock at power scale3, in Hz */

/* Defines used for PLL range */
#define UTILS_PLLVCO_INPUT_MIN1       1000000U      /*!< Frequency min for the low range PLLVCO input, in Hz    */
#define UTILS_PLLVCO_INPUT_MAX1       2000000U      /*!< Frequency max for the wide range PLLVCO input, in Hz   */
#define UTILS_PLLVCO_INPUT_MIN2       2000000U      /*!< Frequency min for the low range PLLVCO input, in Hz    */
#define UTILS_PLLVCO_INPUT_MAX2       4000000U      /*!< Frequency max for the wide range PLLVCO input, in Hz   */
#define UTILS_PLLVCO_INPUT_MIN3       4000000U      /*!< Frequency min for the low range PLLVCO input, in Hz    */
#define UTILS_PLLVCO_INPUT_MAX3       8000000U      /*!< Frequency max for the wide range PLLVCO input, in Hz   */
#define UTILS_PLLVCO_INPUT_MIN4       8000000U      /*!< Frequency min for the low range PLLVCO input, in Hz    */
#define UTILS_PLLVCO_INPUT_MAX4      16000000U      /*!< Frequency max for the wide range PLLVCO input, in Hz   */

#define UTILS_PLLVCO_MEDIUM_OUTPUT_MIN    150000000U      /*!< Frequency min for the medium range PLLVCO output, in Hz   */
#define UTILS_PLLVCO_WIDE_OUTPUT_MIN      192000000U      /*!< Frequency min for the wide range PLLVCO output, in Hz   */
#define UTILS_PLLVCO_MEDIUM_OUTPUT_MAX    420000000U      /*!< Frequency max for the wide range PLLVCO output, in Hz  */
#define UTILS_PLLVCO_WIDE_OUTPUT_MAX      836000000U      /*!< Frequency max for the wide range PLLVCO output, in Hz  */

/* Defines used for HSE range */
#define UTILS_HSE_FREQUENCY_MIN      4000000U        /*!< Frequency min for HSE frequency, in Hz   */
#define UTILS_HSE_FREQUENCY_MAX     48000000U        /*!< Frequency max for HSE frequency, in Hz   */

/* Defines used for FLASH latency according to HCLK Frequency */
#define UTILS_SCALE1_LATENCY0_FREQ   70000000U      /*!< HCLK frequency to set FLASH latency 0 in power scale 1  */
#define UTILS_SCALE1_LATENCY1_FREQ  140000000U      /*!< HCLK frequency to set FLASH latency 1 in power scale 1  */
#define UTILS_SCALE1_LATENCY2_FREQ  210000000U      /*!< HCLK frequency to set FLASH latency 2 in power scale 1  */

#define UTILS_SCALE2_LATENCY0_FREQ   55000000U      /*!< HCLK frequency to set FLASH latency 0 in power scale 2  */
#define UTILS_SCALE2_LATENCY1_FREQ  110000000U      /*!< HCLK frequency to set FLASH latency 1 in power scale 2  */
#define UTILS_SCALE2_LATENCY2_FREQ  165000000U      /*!< HCLK frequency to set FLASH latency 2 in power scale 2  */
#define UTILS_SCALE2_LATENCY3_FREQ  220000000U      /*!< HCLK frequency to set FLASH latency 3 in power scale 2  */

#define UTILS_SCALE3_LATENCY0_FREQ   45000000U      /*!< HCLK frequency to set FLASH latency 0 in power scale 3  */
#define UTILS_SCALE3_LATENCY1_FREQ   90000000U      /*!< HCLK frequency to set FLASH latency 1 in power scale 3  */
#define UTILS_SCALE3_LATENCY2_FREQ  135000000U      /*!< HCLK frequency to set FLASH latency 2 in power scale 3  */
#define UTILS_SCALE3_LATENCY3_FREQ  180000000U      /*!< HCLK frequency to set FLASH latency 3 in power scale 3  */
#define UTILS_SCALE3_LATENCY4_FREQ  225000000U      /*!< HCLK frequency to set FLASH latency 4 in power scale 3  */
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

#define IS_LL_UTILS_APB3_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB3_DIV_1) \
                                      || ((__VALUE__) == LL_RCC_APB3_DIV_2) \
                                      || ((__VALUE__) == LL_RCC_APB3_DIV_4) \
                                      || ((__VALUE__) == LL_RCC_APB3_DIV_8) \
                                      || ((__VALUE__) == LL_RCC_APB3_DIV_16))

#define IS_LL_UTILS_APB4_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB4_DIV_1) \
                                      || ((__VALUE__) == LL_RCC_APB4_DIV_2) \
                                      || ((__VALUE__) == LL_RCC_APB4_DIV_4) \
                                      || ((__VALUE__) == LL_RCC_APB4_DIV_8) \
                                      || ((__VALUE__) == LL_RCC_APB4_DIV_16))

#define IS_LL_UTILS_PLLM_VALUE(__VALUE__) ((1U <= (__VALUE__)) && ((__VALUE__) <= 63U))

#define IS_LL_UTILS_PLLN_VALUE(__VALUE__) ((4U <= (__VALUE__)) && ((__VALUE__) <= 512U))

#define IS_LL_UTILS_PLLP_VALUE(__VALUE__) ((1U <= (__VALUE__)) && ((__VALUE__) <= 128U))

#define IS_LL_UTILS_FRACN_VALUE(__VALUE__) ((__VALUE__) <= 0x1FFFU)

#define IS_LL_UTILS_PLLVCO_INPUT(__VALUE__, __RANGE__)  ( \
(((__RANGE__) == LL_RCC_PLLINPUTRANGE_1_2) && (UTILS_PLLVCO_INPUT_MIN1 <= (__VALUE__)) && ((__VALUE__) <= UTILS_PLLVCO_INPUT_MAX1)) || \
(((__RANGE__) == LL_RCC_PLLINPUTRANGE_2_4) && (UTILS_PLLVCO_INPUT_MIN2 <= (__VALUE__)) && ((__VALUE__) <= UTILS_PLLVCO_INPUT_MAX2)) || \
(((__RANGE__) == LL_RCC_PLLINPUTRANGE_4_8) && (UTILS_PLLVCO_INPUT_MIN3 <= (__VALUE__)) && ((__VALUE__) <= UTILS_PLLVCO_INPUT_MAX3)) || \
(((__RANGE__) == LL_RCC_PLLINPUTRANGE_8_16) && (UTILS_PLLVCO_INPUT_MIN4 <= (__VALUE__)) && ((__VALUE__) <= UTILS_PLLVCO_INPUT_MAX4)))

#define IS_LL_UTILS_PLLVCO_OUTPUT(__VALUE__, __RANGE__) ( \
(((__RANGE__) == LL_RCC_PLLVCORANGE_MEDIUM) && (UTILS_PLLVCO_MEDIUM_OUTPUT_MIN <= (__VALUE__)) && ((__VALUE__) <= UTILS_PLLVCO_MEDIUM_OUTPUT_MAX)) || \
(((__RANGE__) == LL_RCC_PLLVCORANGE_WIDE) && (UTILS_PLLVCO_WIDE_OUTPUT_MIN <= (__VALUE__)) && ((__VALUE__) <= UTILS_PLLVCO_WIDE_OUTPUT_MAX)))

#define IS_LL_UTILS_CHECK_VCO_RANGES(__RANGEIN__, __RANGEOUT__) ( \
(((__RANGEIN__) == LL_RCC_PLLINPUTRANGE_1_2) && ((__RANGEOUT__) == LL_RCC_PLLVCORANGE_MEDIUM)) || \
(((__RANGEIN__) != LL_RCC_PLLINPUTRANGE_1_2) && ((__RANGEOUT__) == LL_RCC_PLLVCORANGE_WIDE)))

#define IS_LL_UTILS_PLL_FREQUENCY(__VALUE__) ((LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE1) ? ((__VALUE__) <= UTILS_MAX_FREQUENCY_SCALE1) : \
                                              (LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE2) ? ((__VALUE__) <= UTILS_MAX_FREQUENCY_SCALE2) : \
                                              ((__VALUE__) <= UTILS_MAX_FREQUENCY_SCALE3))

#define IS_LL_UTILS_HSE_BYPASS(__STATE__) (((__STATE__) == LL_UTILS_HSEBYPASS_ON) \
                                        || ((__STATE__) == LL_UTILS_HSEBYPASS_OFF))

#define IS_LL_UTILS_HSE_FREQUENCY(__FREQUENCY__) (((__FREQUENCY__) >= UTILS_HSE_FREQUENCY_MIN) && ((__FREQUENCY__) <= UTILS_HSE_FREQUENCY_MAX))
/**
  * @}
  */
/* Private function prototypes -----------------------------------------------*/
/** @defgroup UTILS_LL_Private_Functions UTILS Private functions
  * @{
  */
static uint32_t    UTILS_GetPLLOutputFrequency(uint32_t PLL_InputFrequency, LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct);
static ErrorStatus UTILS_CalculateFlashLatency(uint32_t HCLK_Frequency, uint32_t *latency);
static ErrorStatus UTILS_SetFlashLatency(uint32_t latency);
static ErrorStatus UTILS_EnablePLLAndSwitchSystem(uint32_t SYSCLK_Frequency, LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct);
static ErrorStatus UTILS_IsPLLsReady(void);
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
#if defined (DUAL_CORE)
/**
  * @brief  This function configures the Cortex-M SysTick source to have 1ms time base.
  * @note   When a RTOS is used, it is recommended to avoid changing the Systick
  *         configuration by calling this function, for a delay use rather osDelay RTOS service.
  * @param  CPU_Frequency Core frequency in Hz
  * @note   CPU_Frequency can be calculated thanks to RCC helper macro or function
  *         @ref LL_RCC_GetSystemClocksFreq
  *         LL_RCC_GetSystemClocksFreq() is used to calculate the CM7 clock frequency
  *         and __LL_RCC_CALC_HCLK_FREQ is used to caluclate the CM4 clock frequency.
  * @retval None
  */
#else
/**
  * @brief  This function configures the Cortex-M SysTick source to have 1ms time base.
  * @note   When a RTOS is used, it is recommended to avoid changing the Systick
  *         configuration by calling this function, for a delay use rather osDelay RTOS service.
  * @param  CPU_Frequency Core frequency in Hz
  * @note   CPU_Frequency can be calculated thanks to RCC helper macro or function
  *         @ref LL_RCC_GetSystemClocksFreq
  * @retval None
  */
#endif /* DUAL_CORE */
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

  /* Add a period to guaranty minimum wait */
  if(count < LL_MAX_DELAY)
  {
    count++;
  }

  while (count != 0U)
  {
    if((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0U)
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
         System, AHB and APB buses clocks configuration

         (+) The maximum frequency of the SYSCLK is 400 MHz and HCLK is 200 MHz.
         (+) The maximum frequency of the PCLK1, PCLK2, PCLK3 and PCLK4 is 100 MHz.
  @endverbatim
  @internal
             Depending on the device voltage range, the maximum frequency should be
             adapted accordingly:
             (++) +----------------------------------------------------------------------------+
             (++) |  Wait states   |                           HCLK clock frequency (MHz)      |
             (++) |                |-----------------------------------------------------------|
             (++) |  (Latency)     |   voltage range 1 |   voltage range 2 |   voltage range 3 |
             (++) |                |    1.15V - 1.26V  |    1.05V - 1.15V  |    0.95V - 1.05V  |
             (++) |----------------|-------------------|-------------------|-------------------|
             (++) |0WS(1CPU cycle) |   0 < HCLK <= 70  |   0 < HCLK <= 55  |   0 < HCLK <= 45  |
             (++) |----------------|-------------------|-------------------|-------------------|
             (++) |1WS(2CPU cycle) |  70 < HCLK <= 140 |  55 < HCLK <= 110 |  45 < HCLK <= 90  |
             (++) |----------------|-------------------|-------------------|-------------------|
             (++) |2WS(3CPU cycle) | 140 < HCLK <= 210 | 110 < HCLK <= 165 |  90 < HCLK <= 135 |
             (++) |----------------|-------------------|-------------------|-------------------|
             (++) |3WS(4CPU cycle) |        --         | 165 < HCLK <= 220 | 135 < HCLK <= 180 |
             (++) |----------------|-------------------|-------------------|-------------------|
             (++) |4WS(5CPU cycle) |        --         |        --         | 180 < HCLK <= 225 |
             (++) +----------------------------------------------------------------------------+

  @endinternal
  * @{
  */
#if defined (DUAL_CORE)
/**
  * @brief  This function sets directly SystemCoreClock CMSIS variable.
  * @note   Variable can be calculated also through SystemCoreClockUpdate function.
  * @param  CPU_Frequency Core frequency in Hz
  * @note   CPU_Frequency can be calculated thanks to RCC helper macro or function
  *         @ref LL_RCC_GetSystemClocksFreq
  *         LL_RCC_GetSystemClocksFreq() is used to calculate the CM7 clock frequency
  *         and __LL_RCC_CALC_HCLK_FREQ is used to caluclate the CM4 clock frequency.
  * @retval None
  */
#else
/**
  * @brief  This function sets directly SystemCoreClock CMSIS variable.
  * @note   Variable can be calculated also through SystemCoreClockUpdate function.
  * @param  CPU_Frequency Core frequency in Hz
  * @note   CPU_Frequency can be calculated thanks to RCC helper macro or function
  *         @ref LL_RCC_GetSystemClocksFreq
  * @retval None
  */
#endif /* DUAL_CORE */
void LL_SetSystemCoreClock(uint32_t CPU_Frequency)
{
  /* HCLK clock frequency */
  SystemCoreClock = CPU_Frequency;
}

/**
  * @brief  This function configures system clock at maximum frequency with HSI as clock source of the PLL
  * @note   The application need to ensure that PLL is disabled.
  * @note   Function is based on the following formula:
  *         - PLL output frequency = (((HSI frequency / PLLM) * PLLN) / PLLP)
  *         - PLLM: ensure that the VCO input frequency ranges from 1 to 16 MHz (PLLVCO_input = HSI frequency / PLLM)
  *         - PLLN: ensure that the VCO output frequency is between 150 and 836 MHz (PLLVCO_output = PLLVCO_input * PLLN)
  *         - PLLP: ensure that max frequency at 400000000 Hz is reach (PLLVCO_output / PLLP)
  * @param  UTILS_PLLInitStruct pointer to a @ref LL_UTILS_PLLInitTypeDef structure that contains
  *                             the configuration information for the PLL.
  * @param  UTILS_ClkInitStruct pointer to a @ref LL_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Max frequency configuration done
  *          - ERROR: Max frequency configuration not done
  */
ErrorStatus LL_PLL_ConfigSystemClock_HSI(LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct,
                                         LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct)
{
  ErrorStatus status;
#ifdef  USE_FULL_ASSERT
  uint32_t vcoinput_freq, vcooutput_freq;
#endif
  uint32_t pllfreq, hsi_clk;

  /* Check the parameters */
  assert_param(IS_LL_UTILS_PLLM_VALUE(UTILS_PLLInitStruct->PLLM));
  assert_param(IS_LL_UTILS_PLLN_VALUE(UTILS_PLLInitStruct->PLLN));
  assert_param(IS_LL_UTILS_PLLP_VALUE(UTILS_PLLInitStruct->PLLP));
  assert_param(IS_LL_UTILS_FRACN_VALUE(UTILS_PLLInitStruct->FRACN));

  hsi_clk = (HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos));

  /* Check VCO Input frequency */
#ifdef  USE_FULL_ASSERT
  vcoinput_freq = hsi_clk / UTILS_PLLInitStruct->PLLM;
#endif
  assert_param(IS_LL_UTILS_PLLVCO_INPUT(vcoinput_freq, UTILS_PLLInitStruct->VCO_Input));

  /* Check VCO Output frequency */
#ifdef  USE_FULL_ASSERT
  vcooutput_freq = LL_RCC_CalcPLLClockFreq(hsi_clk, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN, UTILS_PLLInitStruct->FRACN, 1UL);
#endif
  assert_param(IS_LL_UTILS_PLLVCO_OUTPUT(vcooutput_freq, UTILS_PLLInitStruct->VCO_Output));

  /* Check VCO Input ranges */
  assert_param(IS_LL_UTILS_CHECK_VCO_RANGES(UTILS_PLLInitStruct->VCO_Input, UTILS_PLLInitStruct->VCO_Output));

  /* Check if one of the PLL is enabled */
  if(UTILS_IsPLLsReady() == SUCCESS)
  {
    /* Calculate the new PLL output frequency */
    pllfreq = UTILS_GetPLLOutputFrequency(hsi_clk, UTILS_PLLInitStruct);

    /* Enable HSI if not enabled */
    if(LL_RCC_HSI_IsReady() != 1U)
    {
      LL_RCC_HSI_Enable();
      while (LL_RCC_HSI_IsReady() != 1U)
      {
        /* Wait for HSI ready */
      }
    }

    /* Configure PLL */
    LL_RCC_PLL1P_Enable();
    LL_RCC_PLL1FRACN_Enable();
    LL_RCC_PLL_SetSource(LL_RCC_PLLSOURCE_HSI);
    LL_RCC_PLL1_SetVCOInputRange(UTILS_PLLInitStruct->VCO_Input);
    LL_RCC_PLL1_SetVCOOutputRange(UTILS_PLLInitStruct->VCO_Output);
    LL_RCC_PLL1_SetM(UTILS_PLLInitStruct->PLLM);
    LL_RCC_PLL1_SetN(UTILS_PLLInitStruct->PLLN);
    LL_RCC_PLL1_SetP(UTILS_PLLInitStruct->PLLP);
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
  *         - PLLM: ensure that the VCO input frequency ranges from 0.95 to 2.10 MHz (PLLVCO_input = HSE frequency / PLLM)
  *         - PLLN: ensure that the VCO output frequency is between 150 and 836 MHz (PLLVCO_output = PLLVCO_input * PLLN)
  *         - PLLP: ensure that max frequency at 400000000 Hz is reached (PLLVCO_output / PLLP)
  * @param  HSEFrequency Value between Min_Data = 4000000 and Max_Data = 48000000
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
  */
ErrorStatus LL_PLL_ConfigSystemClock_HSE(uint32_t HSEFrequency, uint32_t HSEBypass,
                                         LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct, LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct)
{
  ErrorStatus status;
#ifdef  USE_FULL_ASSERT
  uint32_t vcoinput_freq, vcooutput_freq;
#endif
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
#endif
  assert_param(IS_LL_UTILS_PLLVCO_INPUT(vcoinput_freq, UTILS_PLLInitStruct->VCO_Input));

  /* Check VCO output frequency */
#ifdef  USE_FULL_ASSERT
  vcooutput_freq = LL_RCC_CalcPLLClockFreq(HSEFrequency, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN, UTILS_PLLInitStruct->FRACN, 1U);
#endif
  assert_param(IS_LL_UTILS_PLLVCO_OUTPUT(vcooutput_freq, UTILS_PLLInitStruct->VCO_Output));

  /* Check VCO Input/output ranges compatibility */
  assert_param(IS_LL_UTILS_CHECK_VCO_RANGES(UTILS_PLLInitStruct->VCO_Input, UTILS_PLLInitStruct->VCO_Output));

  /* Check if one of the PLL is enabled */
  if(UTILS_IsPLLsReady() == SUCCESS)
  {
    /* Calculate the new PLL output frequency */
    pllfreq = UTILS_GetPLLOutputFrequency(HSEFrequency, UTILS_PLLInitStruct);

    /* Enable HSE if not enabled */
    if(LL_RCC_HSE_IsReady() != 1U)
    {
      /* Check if need to enable HSE bypass feature or not */
      if(HSEBypass == LL_UTILS_HSEBYPASS_ON)
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
    LL_RCC_PLL1P_Enable();
    LL_RCC_PLL1FRACN_Enable();
    LL_RCC_PLL_SetSource(LL_RCC_PLLSOURCE_HSE);
    LL_RCC_PLL1_SetVCOInputRange(UTILS_PLLInitStruct->VCO_Input);
    LL_RCC_PLL1_SetVCOOutputRange(UTILS_PLLInitStruct->VCO_Output);
    LL_RCC_PLL1_SetM(UTILS_PLLInitStruct->PLLM);
    LL_RCC_PLL1_SetN(UTILS_PLLInitStruct->PLLN);
    LL_RCC_PLL1_SetP(UTILS_PLLInitStruct->PLLP);
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
  * @}
  */

/**
  * @}
  */

/** @addtogroup UTILS_LL_Private_Functions
  * @{
  */

/**
  * @brief  Calculate and check the Flash wait states number according to the
            new HCLK frequency and current voltage range.
  * @param  HCLK_Frequency  HCLK frequency
  * @param  latency This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  *         @arg @ref LL_FLASH_LATENCY_2
  *         @arg @ref LL_FLASH_LATENCY_3
  *         @arg @ref LL_FLASH_LATENCY_4
  *         @arg @ref LL_FLASH_LATENCY_5
  *         @arg @ref LL_FLASH_LATENCY_6
  *         @arg @ref LL_FLASH_LATENCY_7
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Latency has been modified
  *          - ERROR: Latency cannot be modified
  */
static ErrorStatus UTILS_CalculateFlashLatency(uint32_t HCLK_Frequency, uint32_t *latency)
{
  ErrorStatus status = SUCCESS;

  /* Frequency cannot be equal to 0 */
  if(HCLK_Frequency == 0U)
  {
    status = ERROR;
  }
  else
  {
    if(LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE1)
    {
      if((HCLK_Frequency > UTILS_SCALE1_LATENCY1_FREQ) && (HCLK_Frequency <= UTILS_SCALE1_LATENCY2_FREQ))
      {
        /* 140 < HCLK <= 210 => 2WS (3 CPU cycles) */
        *latency = LL_FLASH_LATENCY_2;
      }
      else if((HCLK_Frequency > UTILS_SCALE1_LATENCY0_FREQ) && (HCLK_Frequency <= UTILS_SCALE1_LATENCY1_FREQ))
      {
        /* 70 < HCLK <= 140 => 1WS (2 CPU cycles) */
        *latency = LL_FLASH_LATENCY_1;
      }
      else if(HCLK_Frequency <= UTILS_SCALE1_LATENCY0_FREQ)
      {
        /* HCLK <= 70 => 0WS (1 CPU cycles) */
        *latency = LL_FLASH_LATENCY_0;
      }
      else
      {
        status = ERROR;
      }
    }
    else if(LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE2)
    {
      if((HCLK_Frequency > UTILS_SCALE2_LATENCY2_FREQ) && (HCLK_Frequency <= UTILS_SCALE2_LATENCY3_FREQ))
      {
        /* 165 < HCLK <= 220 => 3WS (4 CPU cycles) */
        *latency = LL_FLASH_LATENCY_3;
      }
      else if((HCLK_Frequency > UTILS_SCALE2_LATENCY1_FREQ) && (HCLK_Frequency <= UTILS_SCALE2_LATENCY2_FREQ))
      {
        /* 110 < HCLK <= 165 => 2WS (3 CPU cycles) */
        *latency = LL_FLASH_LATENCY_2;
      }
      else if((HCLK_Frequency > UTILS_SCALE2_LATENCY0_FREQ) && (HCLK_Frequency <= UTILS_SCALE2_LATENCY1_FREQ))
      {
        /* 55 < HCLK <= 110 => 1WS (2 CPU cycles) */
        *latency = LL_FLASH_LATENCY_1;
      }
      else if(HCLK_Frequency <= UTILS_SCALE2_LATENCY0_FREQ)
      {
        /* HCLK <= 55 => 0WS (1 CPU cycles) */
        *latency = LL_FLASH_LATENCY_0;
      }
      else
      {
        status = ERROR;
      }
    }
    else /* Scale 3 */
    {
      if((HCLK_Frequency > UTILS_SCALE3_LATENCY3_FREQ) && (HCLK_Frequency <= UTILS_SCALE3_LATENCY4_FREQ))
      {
        /* 180 < HCLK <= 225 => 4WS (5 CPU cycles) */
        *latency = LL_FLASH_LATENCY_4;
      }
      else if((HCLK_Frequency > UTILS_SCALE3_LATENCY2_FREQ) && (HCLK_Frequency <= UTILS_SCALE3_LATENCY3_FREQ))
      {
        /* 135 < HCLK <= 180 => 3WS (4 CPU cycles) */
        *latency = LL_FLASH_LATENCY_3;
      }
      else if((HCLK_Frequency > UTILS_SCALE3_LATENCY1_FREQ) && (HCLK_Frequency <= UTILS_SCALE3_LATENCY2_FREQ))
      {
        /* 90 < HCLK <= 135 => 2WS (3 CPU cycles) */
        *latency = LL_FLASH_LATENCY_2;
      }
      else if((HCLK_Frequency > UTILS_SCALE3_LATENCY0_FREQ) && (HCLK_Frequency <= UTILS_SCALE3_LATENCY1_FREQ))
      {
        /* 45 < HCLK <= 90 => 1WS (2 CPU cycles) */
        *latency = LL_FLASH_LATENCY_1;
      }
      else if(HCLK_Frequency <= UTILS_SCALE3_LATENCY0_FREQ)
      {
        /* HCLK <= 45 => 0WS (1 CPU cycles) */
        *latency = LL_FLASH_LATENCY_0;
      }
      else
      {
        status = ERROR;
      }
    }
  }

  return status;
}

/**
  * @brief  Update number of Flash wait states
  * @param  latency  Flash Latency
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Latency has been modified
  *          - ERROR: Latency cannot be modified
  */
static ErrorStatus UTILS_SetFlashLatency(uint32_t latency)
{
  ErrorStatus status = SUCCESS;

  LL_FLASH_SetLatency(latency);

  /* Check that the new number of wait states is taken into account to access the Flash
     memory by reading the FLASH_ACR register */
  if(LL_FLASH_GetLatency() != latency)
  {
    status = ERROR;
  }

  return status;
}

/**
  * @brief  Function to check that PLL can be modified
  * @param  PLL_InputFrequency  PLL input frequency (in Hz)
  * @param  UTILS_PLLInitStruct pointer to a @ref LL_UTILS_PLLInitTypeDef structure that contains
  *                             the configuration information for the PLL.
  * @retval PLL output frequency (in Hz)
  */
static uint32_t UTILS_GetPLLOutputFrequency(uint32_t PLL_InputFrequency, LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct)
{
  uint32_t pllfreq;

  /* Check the parameters */
  assert_param(IS_LL_UTILS_PLLM_VALUE(UTILS_PLLInitStruct->PLLM));
  assert_param(IS_LL_UTILS_PLLN_VALUE(UTILS_PLLInitStruct->PLLN));
  assert_param(IS_LL_UTILS_PLLP_VALUE(UTILS_PLLInitStruct->PLLP));
  assert_param(IS_LL_UTILS_FRACN_VALUE(UTILS_PLLInitStruct->FRACN));

  pllfreq = LL_RCC_CalcPLLClockFreq(PLL_InputFrequency, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN, UTILS_PLLInitStruct->FRACN, UTILS_PLLInitStruct->PLLP);

  return pllfreq;
}

/**
  * @brief  Check that all PLLs are ready therefore configuration can be done
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: All PLLs are ready so configuration can be done
  *          - ERROR: One PLL at least is busy
  */
static ErrorStatus UTILS_IsPLLsReady(void)
{
  ErrorStatus status = SUCCESS;

  /* Check if one of the PLL1 is busy */
  if(LL_RCC_PLL1_IsReady() != 0U)
  {
    /* PLL1 configuration cannot be done */
    status = ERROR;
  }

  /* Check if one of the PLL2 is busy */
  if(LL_RCC_PLL2_IsReady() != 0U)
  {
    /* PLL2 configuration cannot be done */
    status = ERROR;
  }

  /* Check if one of the PLL3 is busy */
  if(LL_RCC_PLL3_IsReady() != 0U)
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
static ErrorStatus UTILS_EnablePLLAndSwitchSystem(uint32_t SYSCLK_Frequency, LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct)
{
  ErrorStatus status;
  uint32_t new_hclk_frequency, new_latency;

  assert_param(IS_LL_UTILS_SYSCLK_DIV(UTILS_ClkInitStruct->SYSCLKDivider));
  assert_param(IS_LL_UTILS_AHB_DIV(UTILS_ClkInitStruct->AHBCLKDivider));
  assert_param(IS_LL_UTILS_APB1_DIV(UTILS_ClkInitStruct->APB1CLKDivider));
  assert_param(IS_LL_UTILS_APB2_DIV(UTILS_ClkInitStruct->APB2CLKDivider));
  assert_param(IS_LL_UTILS_APB3_DIV(UTILS_ClkInitStruct->APB3CLKDivider));
  assert_param(IS_LL_UTILS_APB4_DIV(UTILS_ClkInitStruct->APB4CLKDivider));

  /* Calculate the new HCLK frequency */
  new_hclk_frequency = LL_RCC_CALC_HCLK_FREQ(SYSCLK_Frequency, UTILS_ClkInitStruct->AHBCLKDivider);

  /* Calculate the new FLASH latency according to the new HCLK frequency */
  status = UTILS_CalculateFlashLatency(new_hclk_frequency, &new_latency);

  if(status == SUCCESS)
  {
    /* Increasing the number of wait states because of higher CPU frequency */
    if(LL_FLASH_GetLatency() < new_latency)
    {
      status = UTILS_SetFlashLatency(new_latency);
    }

    /* Update system clock configuration */
    if(status == SUCCESS)
    {
      /* Enable PLL */
      LL_RCC_PLL1_Enable();
      while (LL_RCC_PLL1_IsReady() != 1U)
      {
        /* Wait for PLL ready */
      }

      /* Set All APBxPrescaler to the Highest Divider */
      LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_16);
      LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_16);
      LL_RCC_SetAPB3Prescaler(LL_RCC_APB3_DIV_16);
      LL_RCC_SetAPB4Prescaler(LL_RCC_APB4_DIV_16);

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
      LL_RCC_SetAPB3Prescaler(UTILS_ClkInitStruct->APB3CLKDivider);
      LL_RCC_SetAPB4Prescaler(UTILS_ClkInitStruct->APB4CLKDivider);

      /* Update SystemCoreClock variable */
      LL_SetSystemCoreClock(SYSCLK_Frequency);
    }

    /* Decreasing the number of wait states because of lower CPU frequency */
    if(LL_FLASH_GetLatency() > new_latency)
    {
      status = UTILS_SetFlashLatency(new_latency);
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
