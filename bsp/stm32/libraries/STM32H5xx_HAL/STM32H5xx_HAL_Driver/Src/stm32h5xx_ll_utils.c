/**
  ******************************************************************************
  * @file    stm32h5xx_ll_utils.c
  * @author  MCD Application Team
  * @brief   UTILS LL module driver.
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
/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_ll_utils.h"
#include "stm32h5xx_ll_rcc.h"
#include "stm32h5xx_ll_system.h"
#include "stm32h5xx_ll_pwr.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32H5xx_LL_Driver
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
#define UTILS_MAX_FREQUENCY_SCALE0  250000000U         /*!< Maximum frequency for system clock at power scale0, in Hz */
#define UTILS_MAX_FREQUENCY_SCALE1  180000000U         /*!< Maximum frequency for system clock at power scale1, in Hz */
#define UTILS_MAX_FREQUENCY_SCALE2  130000000U         /*!< Maximum frequency for system clock at power scale2, in Hz */
#define UTILS_MAX_FREQUENCY_SCALE3   80000000U         /*!< Maximum frequency for system clock at power scale3, in Hz */

/* Defines used for PLL range */
#define UTILS_PLLVCO_INPUT_MIN1       1000000U      /*!< Frequency min for the low range PLLVCO input, in Hz    */
#define UTILS_PLLVCO_INPUT_MAX1       2000000U      /*!< Frequency max for the wide range PLLVCO input, in Hz   */
#define UTILS_PLLVCO_INPUT_MIN2       2000000U      /*!< Frequency min for the low range PLLVCO input, in Hz    */
#define UTILS_PLLVCO_INPUT_MAX2       4000000U      /*!< Frequency max for the wide range PLLVCO input, in Hz   */
#define UTILS_PLLVCO_INPUT_MIN3       4000000U      /*!< Frequency min for the low range PLLVCO input, in Hz    */
#define UTILS_PLLVCO_INPUT_MAX3       8000000U      /*!< Frequency max for the wide range PLLVCO input, in Hz   */
#define UTILS_PLLVCO_INPUT_MIN4       8000000U      /*!< Frequency min for the low range PLLVCO input, in Hz    */
#define UTILS_PLLVCO_INPUT_MAX4      16000000U      /*!< Frequency max for the wide range PLLVCO input, in Hz   */

#define UTILS_PLLVCO_MEDIUM_OUTPUT_MIN    150000000U    /*!< Frequency min for the medium range PLLVCO output, in Hz  */
#define UTILS_PLLVCO_WIDE_OUTPUT_MIN      192000000U    /*!< Frequency min for the wide range PLLVCO output, in Hz    */
#define UTILS_PLLVCO_MEDIUM_OUTPUT_MAX    420000000U    /*!< Frequency max for the medium range PLLVCO output, in Hz  */
#define UTILS_PLLVCO_WIDE_OUTPUT_MAX      836000000U    /*!< Frequency max for the wide range PLLVCO output, in Hz    */
/* Defines used for HSE range */
#define UTILS_HSE_FREQUENCY_MIN             4000000U      /*!< Frequency min for HSE frequency, in Hz   */
#define UTILS_HSE_FREQUENCY_MAX            50000000U      /*!< Frequency max for HSE frequency, in Hz   */

/* Defines used for FLASH latency according to HCLK Frequency */
#define UTILS_SCALE0_LATENCY0_FREQ     38000000U       /*!< HCLK frequency to set FLASH latency 0 in power scale 0 */
#define UTILS_SCALE0_LATENCY1_FREQ     76000000U       /*!< HCLK frequency to set FLASH latency 1 in power scale 0 */
#define UTILS_SCALE0_LATENCY2_FREQ    114000000U       /*!< HCLK frequency to set FLASH latency 2 in power scale 0 */
#define UTILS_SCALE0_LATENCY3_FREQ    152000000U       /*!< HCLK frequency to set FLASH latency 3 in power scale 0 */
#define UTILS_SCALE0_LATENCY4_FREQ    190000000U       /*!< HCLK frequency to set FLASH latency 4 in power scale 0 */
#define UTILS_SCALE0_LATENCY5_FREQ    250000000U       /*!< HCLK frequency to set FLASH latency 5 in power scale 0 */

#define UTILS_SCALE1_LATENCY0_FREQ     32000000U       /*!< HCLK frequency to set FLASH latency 0 in power scale 1 */
#define UTILS_SCALE1_LATENCY1_FREQ     64000000U       /*!< HCLK frequency to set FLASH latency 1 in power scale 1 */
#define UTILS_SCALE1_LATENCY2_FREQ     96000000U       /*!< HCLK frequency to set FLASH latency 2 in power scale 1 */
#define UTILS_SCALE1_LATENCY3_FREQ    128000000U       /*!< HCLK frequency to set FLASH latency 3 in power scale 1 */
#define UTILS_SCALE1_LATENCY4_FREQ    160000000U       /*!< HCLK frequency to set FLASH latency 4 in power scale 1 */
#define UTILS_SCALE1_LATENCY5_FREQ    180000000U       /*!< HCLK frequency to set FLASH latency 5 in power scale 1 */

#define UTILS_SCALE2_LATENCY0_FREQ     26000000U       /*!< HCLK frequency to set FLASH latency 0 in power scale 2 */
#define UTILS_SCALE2_LATENCY1_FREQ     50000000U       /*!< HCLK frequency to set FLASH latency 1 in power scale 2 */
#define UTILS_SCALE2_LATENCY2_FREQ     80000000U       /*!< HCLK frequency to set FLASH latency 2 in power scale 2 */
#define UTILS_SCALE2_LATENCY3_FREQ    106000000U       /*!< HCLK frequency to set FLASH latency 3 in power scale 2 */
#define UTILS_SCALE2_LATENCY4_FREQ    130000000U       /*!< HCLK frequency to set FLASH latency 4 in power scale 2 */

#define UTILS_SCALE3_LATENCY0_FREQ     16000000U       /*!< HCLK frequency to set FLASH latency 0 in power scale 3 */
#define UTILS_SCALE3_LATENCY1_FREQ     32000000U       /*!< HCLK frequency to set FLASH latency 1 in power scale 3 */
#define UTILS_SCALE3_LATENCY2_FREQ     50000000U       /*!< HCLK frequency to set FLASH latency 2 in power scale 3 */
#define UTILS_SCALE3_LATENCY3_FREQ     65000000U       /*!< HCLK frequency to set FLASH latency 3 in power scale 3 */
#define UTILS_SCALE3_LATENCY4_FREQ     80000000U       /*!< HCLK frequency to set FLASH latency 4 in power scale 3 */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup UTILS_LL_Private_Macros
  * @{
  */
#define IS_LL_UTILS_SYSCLK_DIV(__VALUE__) (((__VALUE__) == LL_RCC_SYSCLK_DIV_1)      \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_2)   \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_4)   \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_8)   \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_16)  \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_64)  \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_128) \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_256) \
                                           || ((__VALUE__) == LL_RCC_SYSCLK_DIV_512))

#define IS_LL_UTILS_APB1_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB1_DIV_1)    \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_2) \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_4) \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_8) \
                                         || ((__VALUE__) == LL_RCC_APB1_DIV_16))

#define IS_LL_UTILS_APB2_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB2_DIV_1)    \
                                         || ((__VALUE__) == LL_RCC_APB2_DIV_2) \
                                         || ((__VALUE__) == LL_RCC_APB2_DIV_4) \
                                         || ((__VALUE__) == LL_RCC_APB2_DIV_8) \
                                         || ((__VALUE__) == LL_RCC_APB2_DIV_16))

#define IS_LL_UTILS_APB3_DIV(__VALUE__) (((__VALUE__) == LL_RCC_APB3_DIV_1)    \
                                         || ((__VALUE__) == LL_RCC_APB3_DIV_2) \
                                         || ((__VALUE__) == LL_RCC_APB3_DIV_4) \
                                         || ((__VALUE__) == LL_RCC_APB3_DIV_8) \
                                         || ((__VALUE__) == LL_RCC_APB3_DIV_16))

#define IS_LL_UTILS_PLLM_VALUE(__VALUE__) ((1U <= (__VALUE__)) && ((__VALUE__) <= 63U))

#define IS_LL_UTILS_PLLN_VALUE(__VALUE__) ((4U <= (__VALUE__)) && ((__VALUE__) <= 512U))

#define IS_LL_UTILS_PLLP_VALUE(__VALUE__) ((2U <= (__VALUE__)) && ((__VALUE__) <= 128U))

#define IS_LL_UTILS_FRACN_VALUE(__VALUE__) ((__VALUE__) <= 0x1FFFU)

#define IS_LL_UTILS_PLLVCO_INPUT(__VALUE__, __RANGE__)  ( \
                                                          (((__RANGE__) == LL_RCC_PLLINPUTRANGE_1_2)  && \
                                                           (UTILS_PLLVCO_INPUT_MIN1 <= (__VALUE__))   && \
                                                           ((__VALUE__) <= UTILS_PLLVCO_INPUT_MAX1))  || \
                                                          (((__RANGE__) == LL_RCC_PLLINPUTRANGE_2_4)  && \
                                                           (UTILS_PLLVCO_INPUT_MIN2 <= (__VALUE__))   && \
                                                           ((__VALUE__) <= UTILS_PLLVCO_INPUT_MAX2))  || \
                                                          (((__RANGE__) == LL_RCC_PLLINPUTRANGE_4_8)  && \
                                                           (UTILS_PLLVCO_INPUT_MIN3 <= (__VALUE__))   && \
                                                           ((__VALUE__) <= UTILS_PLLVCO_INPUT_MAX3))  || \
                                                          (((__RANGE__) == LL_RCC_PLLINPUTRANGE_8_16) && \
                                                           (UTILS_PLLVCO_INPUT_MIN4 <= (__VALUE__))   && \
                                                           ((__VALUE__) <= UTILS_PLLVCO_INPUT_MAX4)))

#define IS_LL_UTILS_PLLVCO_OUTPUT(__VALUE__, __RANGE__) ( \
                                                          (((__RANGE__) == LL_RCC_PLLVCORANGE_MEDIUM)       && \
                                                           (UTILS_PLLVCO_MEDIUM_OUTPUT_MIN <= (__VALUE__))  && \
                                                           ((__VALUE__) <= UTILS_PLLVCO_MEDIUM_OUTPUT_MAX)) || \
                                                          (((__RANGE__) == LL_RCC_PLLVCORANGE_WIDE)         && \
                                                           (UTILS_PLLVCO_WIDE_OUTPUT_MIN <= (__VALUE__))    && \
                                                           ((__VALUE__) <= UTILS_PLLVCO_WIDE_OUTPUT_MAX)))

#define IS_LL_UTILS_CHECK_VCO_RANGES(__RANGEIN__, __RANGEOUT__) ( \
                                                                  (((__RANGEIN__) == LL_RCC_PLLINPUTRANGE_1_2)   && \
                                                                   ((__RANGEOUT__) == LL_RCC_PLLVCORANGE_MEDIUM)) || \
                                                                  (((__RANGEIN__) != LL_RCC_PLLINPUTRANGE_1_2)   && \
                                                                   ((__RANGEOUT__) == LL_RCC_PLLVCORANGE_WIDE)))

#define IS_LL_UTILS_PLL_FREQUENCY(__VALUE__) ((LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE0) ? \
                                              ((__VALUE__) <= UTILS_MAX_FREQUENCY_SCALE0) : \
                                              (LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE1) ? \
                                              ((__VALUE__) <= UTILS_MAX_FREQUENCY_SCALE1) : \
                                              (LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE2) ? \
                                              ((__VALUE__) <= UTILS_MAX_FREQUENCY_SCALE2) : \
                                              ((__VALUE__) <= UTILS_MAX_FREQUENCY_SCALE3))

#define IS_LL_UTILS_HSE_BYPASS(__STATE__) (((__STATE__) == LL_UTILS_HSEBYPASS_ON)         \
                                           || ((__STATE__) == LL_UTILS_HSEBYPASS_DIGITAL_ON) \
                                           || ((__STATE__) == LL_UTILS_HSEBYPASS_OFF))

#define IS_LL_UTILS_HSE_FREQUENCY(__FREQUENCY__) (((__FREQUENCY__) >= UTILS_HSE_FREQUENCY_MIN) &&\
                                                  ((__FREQUENCY__) <= UTILS_HSE_FREQUENCY_MAX))
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
static ErrorStatus UTILS_PLL_IsBusy(void);
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
  * @param  HCLKFrequency HCLK frequency in Hz
  * @note   HCLK frequency can be calculated thanks to RCC helper macro or function @ref LL_RCC_GetSystemClocksFreq
  * @retval None
  */
void LL_Init1msTick(uint32_t HCLKFrequency)
{
  /* Use frequency provided in argument */
  LL_InitTick(HCLKFrequency, 1000U);
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
  __IO uint32_t  tmp = SysTick->CTRL;  /* Clear the COUNTFLAG first */
  uint32_t tmpDelay = Delay;

  /* Add this code to indicate that local variable is not used */
  ((void)tmp);

  /* Add a period to guaranty minimum wait */
  if (tmpDelay < LL_MAX_DELAY)
  {
    tmpDelay++;
  }

  while (tmpDelay != 0U)
  {
    if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0U)
    {
      tmpDelay--;
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

         (+) The maximum frequency of the SYSCLK is 250 MHz and HCLK is 250 MHz.
         (+) The maximum frequency of the PCLK1, PCLK2 and PCLK3 is 250 MHz.
  @endverbatim
  @internal
             Depending on the device voltage range, the maximum frequency should be
             adapted accordingly:

             (++) Table 1. HCLK clock frequency for STM32H5 devices
             (++) +-----------------------------------------------------------------------------------------------+
             (++) | Latency         |                          HCLK clock frequency (MHz)                         |
             (++) |                 |-----------------------------------------------------------------------------|
             (++) |                 |  voltage range 0  |  voltage range 1 | voltage range 2  | voltage range 3   |
             (++) |                 |    1.26 - 1.35V   |   1.15 - 1.26V   |   1.05 - 1.15V   |   0,95 - 1,05V    |
             (++) |-----------------|-------------------|------------------|------------------|-------------------|
             (++) |0WS(1 CPU cycles)|   0 < HCLK <= 38  |  0 < HCLK <= 32  |  0 < HCLK <= 26  | 0 < HCLK <= 16    |
             (++) |-----------------|-------------------|------------------|------------------|-------------------|
             (++) |1WS(2 CPU cycles)|  38 < HCLK <= 76  | 32 < HCLK <= 64  | 26 < HCLK <= 50  | 16 < HCLK <= 32   |
             (++) |-----------------|-------------------|------------------|------------------|-------------------|
             (++) |2WS(3 CPU cycles)|  76 < HCLK <= 114 | 64 < HCLK <= 96  | 50 < HCLK <= 80  | 32 < HCLK <= 50   |
             (++) |-----------------|-------------------|------------------|------------------|-------------------|
             (++) |3WS(4 CPU cycles)| 114 < HCLK <= 152 | 96 < HCLK <= 128 | 80 < HCLK <= 106 | 50 < HCLK <= 65   |
             (++) |-----------------|-------------------|------------------|------------------|-------------------|
             (++) |4WS(5 CPU cycles)|  152 < HCLK <= 190| 128 < HCLK <= 160| 106 < HCLK <= 130| 65 < HCLK <= 80   |
             (++) |-----------------|-------------------|------------------|------------------|-------------------|
             (++) |5WS(6 CPU cycles)|  190 < HCLK <= 250| 160 < HCLK <= 180|        NA        |         NA        |
             (++) +-----------------+-------------------+------------------+------------------+-------------------+

  @endinternal
  * @{
  */

/**
  * @brief  This function sets directly SystemCoreClock CMSIS variable.
  * @note   Variable can be calculated also through SystemCoreClockUpdate function.
  * @param  HCLKFrequency HCLK frequency in Hz (can be calculated thanks to RCC helper macro)
  * @retval None
  */
void LL_SetSystemCoreClock(uint32_t HCLKFrequency)
{
  /* HCLK clock frequency */
  SystemCoreClock = HCLKFrequency;
}

/**
  * @brief  This function configures system clock at maximum frequency with CSI as clock source of the PLL1
  * @note   The application needs to ensure that all PLLs is disabled.
  * @note   Function is based on the following formula:
  *         - PLL1 output frequency = (((CSI frequency / PLL1M) * PLL1N) / PLL1P)
  *         - PLL1M: ensure that the VCO input frequency ranges from 1 to 16 MHz (PLL1VCO_input = CSI frequency / PLL1M)
  *         - PLL1N: ensure that the VCO output frequency is between 192 and 836 MHz
  *          (PLL1VCO_output = PLL1VCO_input * PLL1N)
  *         - PLL1P: ensure that max frequency at 250 MHz is reached (PLL1VCO_output / PLL1P)
  * @param  UTILS_PLLInitStruct pointer to a @ref LL_UTILS_PLLInitTypeDef structure that contains
  *                             the configuration information for the PLL.
  * @param  UTILS_ClkInitStruct pointer to a @ref LL_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Max frequency configuration done
  *          - ERROR: Max frequency configuration not done
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
#endif /* USE_FULL_ASSERT */
  assert_param(IS_LL_UTILS_PLLVCO_INPUT(vcoinput_freq, UTILS_PLLInitStruct->VCO_Input));

  /* Check VCO Input ranges */
  assert_param(IS_LL_UTILS_CHECK_VCO_RANGES(UTILS_PLLInitStruct->VCO_Input, UTILS_PLLInitStruct->VCO_Output));

  /* Check VCO Output frequency */
#ifdef  USE_FULL_ASSERT
  vcooutput_freq = LL_RCC_CalcPLLClockFreq(CSI_VALUE, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN,
                                           UTILS_PLLInitStruct->FRACN, 1U);
  /* PLL1P Set to 1 to check the assert param (VCO_output)*/
#endif /* USE_FULL_ASSERT */
  assert_param(IS_LL_UTILS_PLLVCO_OUTPUT(vcooutput_freq, UTILS_PLLInitStruct->VCO_Output));

  /* Check if the main PLL is enabled */
  if (UTILS_PLL_IsBusy() == SUCCESS)
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
    LL_RCC_PLL1_ConfigDomain_SYS(LL_RCC_PLL1SOURCE_CSI, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN,
                                 UTILS_PLLInitStruct->PLLP);
    LL_RCC_PLL1FRACN_Disable();
    LL_RCC_PLL1_SetFRACN(UTILS_PLLInitStruct->FRACN);
    LL_RCC_PLL1FRACN_Enable();
    LL_RCC_PLL1_SetVCOInputRange(UTILS_PLLInitStruct->VCO_Input);
    LL_RCC_PLL1_SetVCOOutputRange(UTILS_PLLInitStruct->VCO_Output);

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
  * @brief  This function configures system clock at maximum frequency with HSI as clock source of the PLL1
  * @note   The application need to ensure that all PLLs are disabled.
  * @note   Function is based on the following formula:
  *         - PLL1 output frequency = (((HSI frequency / PLL1M) * PLL1N) / PLL1P)
  *         - PLL1M: ensure that the VCO input frequency ranges from 1 to 16 MHz (PLL1VCO_input = HSI frequency / PLL1M)
  *         - PLL1N: ensure that the VCO output frequency is between 150 and 836 MHz
  *          (PLL1VCO_output = PLL1VCO_input * PLL1N)
  *         - PLL1P: ensure that max frequency at 250 MHz is reach (PLL1VCO_output / PLL1P)
  * @param  UTILS_PLLInitStruct pointer to a @ref LL_UTILS_PLLInitTypeDef structure that contains
  *                             the configuration information for the PLL1.
  * @param  UTILS_ClkInitStruct pointer to a @ref LL_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Max frequency configuration done
  *          - ERROR: Max frequency configuration not done
  *
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
#endif /* USE_FULL_ASSERT */
  assert_param(IS_LL_UTILS_PLLVCO_INPUT(vcoinput_freq, UTILS_PLLInitStruct->VCO_Input));

  /* Check VCO Input ranges */
  assert_param(IS_LL_UTILS_CHECK_VCO_RANGES(UTILS_PLLInitStruct->VCO_Input, UTILS_PLLInitStruct->VCO_Output));

  /* Check VCO Output frequency */
#ifdef  USE_FULL_ASSERT
  vcooutput_freq = LL_RCC_CalcPLLClockFreq(hsi_clk, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN,
                                           UTILS_PLLInitStruct->FRACN, 1UL);
  /* PLL1P Set to 1 to check the assert param (VCO_output)*/
#endif /* USE_FULL_ASSERT */
  assert_param(IS_LL_UTILS_PLLVCO_OUTPUT(vcooutput_freq, UTILS_PLLInitStruct->VCO_Output));

  /* Check if the main PLL is enabled */
  if (UTILS_PLL_IsBusy() == SUCCESS)
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
    LL_RCC_PLL1_ConfigDomain_SYS(LL_RCC_PLL1SOURCE_HSI, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN,
                                 UTILS_PLLInitStruct->PLLP);
    LL_RCC_PLL1FRACN_Disable();
    LL_RCC_PLL1_SetFRACN(UTILS_PLLInitStruct->FRACN);
    LL_RCC_PLL1FRACN_Enable();
    LL_RCC_PLL1_SetVCOInputRange(UTILS_PLLInitStruct->VCO_Input);
    LL_RCC_PLL1_SetVCOOutputRange(UTILS_PLLInitStruct->VCO_Output);

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
  * @brief  This function configures system clock with HSE as clock source of the PLL1
  * @note   The application needs to ensure that the PLL1 is disabled.
  * @note   Function is based on the following formula:
  *         - PLL1 output frequency = (((HSE frequency / PLL1M) * PLL1N) / PLL1P)
  *         - PLL1M: ensure that the VCO input frequency ranges from 1 to 16 MHz (PLL1VCO_input = HSE frequency / PLL1M)
  *         - PLL1N: ensure that the VCO output frequency is between 192 and 836 MHz
  *          (PLL1VCO_output = PLL1VCO_input * PLL1N)
  *         - PLL1P: ensure that max frequency at 250 MHz is reached (PLL1VCO_output / PLL1P)
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
#endif /* USE_FULL_ASSERT */
  assert_param(IS_LL_UTILS_PLLVCO_INPUT(vcoinput_freq, UTILS_PLLInitStruct->VCO_Input));

  /* Check VCO Input/output ranges compatibility */
  assert_param(IS_LL_UTILS_CHECK_VCO_RANGES(UTILS_PLLInitStruct->VCO_Input, UTILS_PLLInitStruct->VCO_Output));

  /* Check VCO output frequency */
#ifdef  USE_FULL_ASSERT
  vcooutput_freq = LL_RCC_CalcPLLClockFreq(HSEFrequency, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN,
                                           UTILS_PLLInitStruct->FRACN, 1U);
  /* PLL1P Set to 1 to check the assert param (VCO_output)*/
#endif /* USE_FULL_ASSERT */
  assert_param(IS_LL_UTILS_PLLVCO_OUTPUT(vcooutput_freq, UTILS_PLLInitStruct->VCO_Output));

  /* Check if the main PLL is enabled */
  if (UTILS_PLL_IsBusy() == SUCCESS)
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
        LL_RCC_HSE_SetExternalClockType(LL_RCC_HSE_ANALOG_TYPE);
      }
      else if (HSEBypass == LL_UTILS_HSEBYPASS_DIGITAL_ON)
      {
        LL_RCC_HSE_EnableBypass();
        LL_RCC_HSE_SetExternalClockType(LL_RCC_HSE_DIGITAL_TYPE);
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
    LL_RCC_PLL1_ConfigDomain_SYS(LL_RCC_PLL1SOURCE_HSE, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN,
                                 UTILS_PLLInitStruct->PLLP);
    LL_RCC_PLL1FRACN_Disable();
    LL_RCC_PLL1_SetFRACN(UTILS_PLLInitStruct->FRACN);
    LL_RCC_PLL1FRACN_Enable();
    LL_RCC_PLL1_SetVCOInputRange(UTILS_PLLInitStruct->VCO_Input);
    LL_RCC_PLL1_SetVCOOutputRange(UTILS_PLLInitStruct->VCO_Output);

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
  uint32_t latency = LL_FLASH_LATENCY_0;  /* default value 0WS */

  /* Frequency cannot be equal to 0 */
  if (HCLK_Frequency == 0U)
  {
    status = ERROR;
  }
  else
  {
    if (LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE0)
    {
      if (HCLK_Frequency <= UTILS_SCALE0_LATENCY0_FREQ)
      {
        /* 0 < HCLK <= 38 => 0WS (1 CPU cycles) : Do nothing, keep latency to default  LL_FLASH_LATENCY_0 */
      }
      else if ((HCLK_Frequency <= UTILS_SCALE0_LATENCY1_FREQ))
      {
        /* 38 < HCLK <=76  => 1WS (2 CPU cycles) */
        latency = LL_FLASH_LATENCY_1;
      }
      else if (HCLK_Frequency <= UTILS_SCALE0_LATENCY2_FREQ)
      {
        /* 76 < HCLK <= 114 => 2WS (3 CPU cycles) */
        latency = LL_FLASH_LATENCY_2;
      }
      else if (HCLK_Frequency <= UTILS_SCALE0_LATENCY3_FREQ)
      {
        /* 114 < HCLK <= 152 => 3WS (4 CPU cycles) */
        latency = LL_FLASH_LATENCY_3;
      }
      else if (HCLK_Frequency <= UTILS_SCALE0_LATENCY4_FREQ)
      {
        /* 152 < HCLK <= 190 => 4WS (5 CPU cycles) */
        latency = LL_FLASH_LATENCY_4;
      }
      else if (HCLK_Frequency <= UTILS_SCALE0_LATENCY5_FREQ)
      {
        /* 190 < HCLK <= 250 => 5WS (6 CPU cycles) */
        latency = LL_FLASH_LATENCY_5;
      }
      else
      {
        status = ERROR;
      }
    }
    else if (LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE1)
    {
      if (HCLK_Frequency <= UTILS_SCALE1_LATENCY0_FREQ)
      {
        /* 0 < HCLK <= 32 => 0WS (1 CPU cycles) : Do nothing, keep latency to default  LL_FLASH_LATENCY_0 */
      }
      else if (HCLK_Frequency <= UTILS_SCALE1_LATENCY1_FREQ)
      {
        /* 32 < HCLK <=64  => 1WS (2 CPU cycles) */
        latency = LL_FLASH_LATENCY_1;
      }
      else if (HCLK_Frequency <= UTILS_SCALE1_LATENCY2_FREQ)
      {
        /* 64 < HCLK <= 96 => 2WS (3 CPU cycles) */
        latency = LL_FLASH_LATENCY_2;
      }
      else if (HCLK_Frequency <= UTILS_SCALE1_LATENCY3_FREQ)
      {
        /* 96 < HCLK <= 128 => 3WS (4 CPU cycles) */
        latency = LL_FLASH_LATENCY_3;
      }
      else if (HCLK_Frequency <= UTILS_SCALE1_LATENCY4_FREQ)
      {
        /* 128 < HCLK <= 160 => 4WS (5 CPU cycles) */
        latency = LL_FLASH_LATENCY_4;
      }
      else if (HCLK_Frequency <= UTILS_SCALE1_LATENCY5_FREQ)
      {
        /* 160 < HCLK <= 150 => 5WS (6 CPU cycles) */
        latency = LL_FLASH_LATENCY_5;
      }
      else
      {
        status = ERROR;
      }
    }
    else if (LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE2)
    {
      if (HCLK_Frequency <= UTILS_SCALE2_LATENCY0_FREQ)
      {
        /* 0 < HCLK <= 26 => 0WS (1 CPU cycles) : Do nothing, keep latency to default  LL_FLASH_LATENCY_0 */
      }
      else if (HCLK_Frequency <= UTILS_SCALE2_LATENCY1_FREQ)
      {
        /* 26 < HCLK <= 50 => 1WS (2 CPU cycles) */
        latency = LL_FLASH_LATENCY_1;
      }
      else if (HCLK_Frequency <= UTILS_SCALE2_LATENCY2_FREQ)
      {
        /* 50 < HCLK <= 80 => 2WS (3 CPU cycles) */
        latency = LL_FLASH_LATENCY_2;
      }
      else if (HCLK_Frequency <= UTILS_SCALE2_LATENCY3_FREQ)
      {
        /* 80 < HCLK <= 106 => 3WS (4 CPU cycles) */
        latency = LL_FLASH_LATENCY_3;
      }
      else if (HCLK_Frequency <= UTILS_SCALE2_LATENCY4_FREQ)
      {
        /* 106 < HCLK <= 130 => 4WS (5 CPU cycles) */
        latency = LL_FLASH_LATENCY_4;
      }
      else
      {
        status = ERROR;
      }
    }
    else /* Voltage Scale 3 */
    {
      if (HCLK_Frequency  <= UTILS_SCALE3_LATENCY0_FREQ)
      {
        /* 0 < HCLK <= 16 => 0WS (1 CPU cycles) : Do nothing, keep latency to default  LL_FLASH_LATENCY_0 */
      }
      else if (HCLK_Frequency <= UTILS_SCALE3_LATENCY1_FREQ)
      {
        /* 16 < HCLK <= 32 => 1WS (2 CPU cycles) */
        latency = LL_FLASH_LATENCY_1;
      }
      else if (HCLK_Frequency <= UTILS_SCALE3_LATENCY2_FREQ)
      {
        /* 32 < HCLK <= 50 => 2WS (3 CPU cycles) */
        latency = LL_FLASH_LATENCY_2;
      }
      else if (HCLK_Frequency <= UTILS_SCALE3_LATENCY3_FREQ)
      {
        /* 50 < HCLK <= 65 => 3WS (4 CPU cycles) */
        latency = LL_FLASH_LATENCY_3;
      }
      else if (HCLK_Frequency <= UTILS_SCALE3_LATENCY4_FREQ)
      {
        /* 65 < HCLK <= 80 => 4WS (5 CPU cycles) */
        latency = LL_FLASH_LATENCY_4;
      }
      else
      {
        status = ERROR;
      }
    }
  }

  if (status == SUCCESS)
  {
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

/** @addtogroup UTILS_LL_Private_Functions
  * @{
  */
/**
  * @brief  Function to Get PLL1 Output frequency
  * @param  PLL_InputFrequency  PLL1 input frequency (in Hz)
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

  /* Check different PLL parameters according to RM                          */
  /*  - PLLM: ensure that the VCO input frequency is in the correct range.   */
  pllfreq = PLL_InputFrequency / (UTILS_PLLInitStruct->PLLM);
  assert_param(IS_LL_UTILS_PLLVCO_INPUT(pllfreq,  UTILS_PLLInitStruct->VCO_Input));

  /*  - PLLN: ensure that the VCO output frequency is in the correct range.  */
  pllfreq = pllfreq * (UTILS_PLLInitStruct->PLLN);
  assert_param(IS_LL_UTILS_PLLVCO_OUTPUT(pllfreq,  UTILS_PLLInitStruct->VCO_Output));

  /*  - PLLP: ensure that PLL1P output frequency does not exceed the corresponding maximum voltage scale frequency.  */
  pllfreq = pllfreq / (UTILS_PLLInitStruct->PLLP);
  assert_param(IS_LL_UTILS_PLL_FREQUENCY(pllfreq));

  return pllfreq;
}

/**
  * @brief  Function to check that main PLL can be modified
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Main PLL modification can be done
  *          - ERROR: Main PLL is busy
  */
static ErrorStatus UTILS_PLL_IsBusy(void)
{
  ErrorStatus status = SUCCESS;

  /* Check if PLL1 is busy*/
  if (LL_RCC_PLL1_IsReady() != 0U)
  {
    /* PLL configuration cannot be modified */
    status = ERROR;
  }

  return status;
}

/**
  * @brief  Function to enable PLL1 and switch system clock to PLL1
  * @param  SYSCLK_Frequency SYSCLK frequency
  * @param  UTILS_ClkInitStruct pointer to a @ref LL_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: No problem to switch system to PLL1
  *          - ERROR: Problem to switch system to PLL1
  */
static ErrorStatus UTILS_EnablePLLAndSwitchSystem(uint32_t SYSCLK_Frequency,
                                                  LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct)
{
  ErrorStatus status = SUCCESS;
  uint32_t hclk_frequency;

  assert_param(IS_LL_UTILS_SYSCLK_DIV(UTILS_ClkInitStruct->SYSCLKDivider));
  assert_param(IS_LL_UTILS_APB1_DIV(UTILS_ClkInitStruct->APB1CLKDivider));
  assert_param(IS_LL_UTILS_APB2_DIV(UTILS_ClkInitStruct->APB2CLKDivider));
  assert_param(IS_LL_UTILS_APB3_DIV(UTILS_ClkInitStruct->APB3CLKDivider));

  /* Calculate HCLK frequency */
  hclk_frequency = __LL_RCC_CALC_HCLK_FREQ(SYSCLK_Frequency, UTILS_ClkInitStruct->SYSCLKDivider);

  /* Increasing the number of wait states because of higher CPU frequency */
  if (SystemCoreClock < hclk_frequency)
  {
    /* Set FLASH latency to highest latency */
    status = LL_SetFlashLatency(hclk_frequency);
  }

  /* Update system clock configuration */
  if (status == SUCCESS)
  {
    /* Enable PLL1 */
    LL_RCC_PLL1_Enable();
    LL_RCC_PLL1P_Enable();
    while (LL_RCC_PLL1_IsReady() != 1U)
    {
      /* Wait for PLL ready */
    }

    /* Set All APBxPrescaler to the Highest Divider */
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_16);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_16);
    LL_RCC_SetAPB3Prescaler(LL_RCC_APB3_DIV_16);

    /* Set AHB prescaler*/
    LL_RCC_SetAHBPrescaler(UTILS_ClkInitStruct->SYSCLKDivider);

    /* Sysclk activation on the main PLL */
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL1);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL1)
    {
      /* Wait for system clock switch to PLL */
    }

    /* Set APB1, APB2 & APB3 prescaler*/
    LL_RCC_SetAPB1Prescaler(UTILS_ClkInitStruct->APB1CLKDivider);
    LL_RCC_SetAPB2Prescaler(UTILS_ClkInitStruct->APB2CLKDivider);
    LL_RCC_SetAPB3Prescaler(UTILS_ClkInitStruct->APB3CLKDivider);
  }

  /* Decreasing the number of wait states because of lower CPU frequency */
  if (SystemCoreClock > hclk_frequency)
  {
    /* Set FLASH latency to lowest latency */
    status = LL_SetFlashLatency(hclk_frequency);
  }

  /* Update SystemCoreClock variable */
  if (status == SUCCESS)
  {
    LL_SetSystemCoreClock(hclk_frequency);
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

