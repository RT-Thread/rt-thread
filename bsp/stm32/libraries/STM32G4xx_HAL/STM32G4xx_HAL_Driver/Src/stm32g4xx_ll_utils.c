/**
  ******************************************************************************
  * @file    stm32g4xx_ll_utils.c
  * @author  MCD Application Team
  * @brief   UTILS LL module driver.
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
#include "stm32g4xx_ll_utils.h"
#include "stm32g4xx_ll_rcc.h"
#include "stm32g4xx_ll_system.h"
#include "stm32g4xx_ll_pwr.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32G4xx_LL_Driver
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
#define UTILS_MAX_FREQUENCY_SCALE1  170000000U       /*!< Maximum frequency for system clock at power scale1, in Hz */
#define UTILS_MAX_FREQUENCY_SCALE2   26000000U       /*!< Maximum frequency for system clock at power scale2, in Hz */

/* Defines used for PLL range */
#define UTILS_PLLVCO_INPUT_MIN        2660000U       /*!< Frequency min for PLLVCO input, in Hz   */
#define UTILS_PLLVCO_INPUT_MAX        8000000U       /*!< Frequency max for PLLVCO input, in Hz   */
#define UTILS_PLLVCO_OUTPUT_MIN      64000000U       /*!< Frequency min for PLLVCO output, in Hz  */
#define UTILS_PLLVCO_OUTPUT_MAX     344000000U       /*!< Frequency max for PLLVCO output, in Hz  */

/* Defines used for HSE range */
#define UTILS_HSE_FREQUENCY_MIN      4000000U        /*!< Frequency min for HSE frequency, in Hz   */
#define UTILS_HSE_FREQUENCY_MAX     48000000U        /*!< Frequency max for HSE frequency, in Hz   */

/* Defines used for FLASH latency according to HCLK Frequency */
#define UTILS_SCALE1_LATENCY1_FREQ   20000000U       /*!< HCLK frequency to set FLASH latency 1 in power scale 1 */
#define UTILS_SCALE1_LATENCY2_FREQ   40000000U       /*!< HCLK frequency to set FLASH latency 2 in power scale 1 */
#define UTILS_SCALE1_LATENCY3_FREQ   60000000U       /*!< HCLK frequency to set FLASH latency 3 in power scale 1 */
#define UTILS_SCALE1_LATENCY4_FREQ   80000000U       /*!< HCLK frequency to set FLASH latency 4 in power scale 1 */
#define UTILS_SCALE1_LATENCY5_FREQ  100000000U       /*!< HCLK frequency to set FLASH latency 5 in power scale 1 */
#define UTILS_SCALE1_LATENCY6_FREQ  120000000U       /*!< HCLK frequency to set FLASH latency 6 in power scale 1 */
#define UTILS_SCALE1_LATENCY7_FREQ  140000000U       /*!< HCLK frequency to set FLASH latency 7 in power scale 1 */
#define UTILS_SCALE1_LATENCY8_FREQ  160000000U       /*!< HCLK frequency to set FLASH latency 8 in power scale 1 */
#define UTILS_SCALE1_LATENCY9_FREQ  170000000U       /*!< HCLK frequency to set FLASH latency 9 in power scale 1 */
#define UTILS_SCALE2_LATENCY1_FREQ    8000000U       /*!< HCLK frequency to set FLASH latency 1 in power scale 2 */
#define UTILS_SCALE2_LATENCY2_FREQ   16000000U       /*!< HCLK frequency to set FLASH latency 2 in power scale 2 */
#define UTILS_SCALE2_LATENCY3_FREQ   26000000U       /*!< HCLK frequency to set FLASH latency 2 in power scale 2 */
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

#define IS_LL_UTILS_PLLM_VALUE(__VALUE__) (((__VALUE__) == LL_RCC_PLLM_DIV_1) \
                                        || ((__VALUE__) == LL_RCC_PLLM_DIV_2) \
                                        || ((__VALUE__) == LL_RCC_PLLM_DIV_3) \
                                        || ((__VALUE__) == LL_RCC_PLLM_DIV_4) \
                                        || ((__VALUE__) == LL_RCC_PLLM_DIV_5) \
                                        || ((__VALUE__) == LL_RCC_PLLM_DIV_6) \
                                        || ((__VALUE__) == LL_RCC_PLLM_DIV_7) \
                                        || ((__VALUE__) == LL_RCC_PLLM_DIV_8) \
                                        || ((__VALUE__) == LL_RCC_PLLM_DIV_9) \
                                        || ((__VALUE__) == LL_RCC_PLLM_DIV_10) \
                                        || ((__VALUE__) == LL_RCC_PLLM_DIV_11) \
                                        || ((__VALUE__) == LL_RCC_PLLM_DIV_12) \
                                        || ((__VALUE__) == LL_RCC_PLLM_DIV_13) \
                                        || ((__VALUE__) == LL_RCC_PLLM_DIV_14) \
                                        || ((__VALUE__) == LL_RCC_PLLM_DIV_15) \
                                        || ((__VALUE__) == LL_RCC_PLLM_DIV_16))

#define IS_LL_UTILS_PLLN_VALUE(__VALUE__) ((8U <= (__VALUE__)) && ((__VALUE__) <= 127U))

#define IS_LL_UTILS_PLLR_VALUE(__VALUE__) (((__VALUE__) == LL_RCC_PLLR_DIV_2) \
                                        || ((__VALUE__) == LL_RCC_PLLR_DIV_4) \
                                        || ((__VALUE__) == LL_RCC_PLLR_DIV_6) \
                                        || ((__VALUE__) == LL_RCC_PLLR_DIV_8))

#define IS_LL_UTILS_PLLVCO_INPUT(__VALUE__)  ((UTILS_PLLVCO_INPUT_MIN <= (__VALUE__)) && ((__VALUE__) <= UTILS_PLLVCO_INPUT_MAX))

#define IS_LL_UTILS_PLLVCO_OUTPUT(__VALUE__) ((UTILS_PLLVCO_OUTPUT_MIN <= (__VALUE__)) && ((__VALUE__) <= UTILS_PLLVCO_OUTPUT_MAX))

#define IS_LL_UTILS_PLL_FREQUENCY(__VALUE__) ((LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE1) ? ((__VALUE__) <= UTILS_MAX_FREQUENCY_SCALE1) : \
                                             ((__VALUE__) <= UTILS_MAX_FREQUENCY_SCALE2))

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
static uint32_t    UTILS_GetPLLOutputFrequency(uint32_t PLL_InputFrequency,
                                               LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct);
static ErrorStatus UTILS_EnablePLLAndSwitchSystem(uint32_t SYSCLK_Frequency, LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct);
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
  uint32_t tmpDelay; /* MISRAC2012-Rule-17.8 */
  /* Add this code to indicate that local variable is not used */
  ((void)tmp);
  tmpDelay = Delay;
  /* Add a period to guaranty minimum wait */
  if(tmpDelay < LL_MAX_DELAY)
  {
    tmpDelay++;
  }

  while (tmpDelay != 0U)
  {
    if((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0U)
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

         (+) The maximum frequency of the SYSCLK, HCLK, PCLK1 and PCLK2 is 
             170000000 Hz for STM32G4xx.
  @endverbatim
  @internal
             Depending on the device voltage range, the maximum frequency should be
             adapted accordingly:

             (++) Table 1. HCLK clock frequency for STM32G4xx devices
             (++) +--------------------------------------------------------+
             (++) | Latency         |     HCLK clock frequency (MHz)       |
             (++) |                 |--------------------------------------|
             (++) |                 |  voltage range 1  | voltage range 2  |
             (++) |                 |       1.2 V       |     1.0 V        |
             (++) |-----------------|-------------------|------------------|
             (++) |0WS(1 CPU cycles)|   0 < HCLK <= 20  |  0 < HCLK <= 8   |
             (++) |-----------------|-------------------|------------------|
             (++) |1WS(2 CPU cycles)|  20 < HCLK <= 40  |  8 < HCLK <= 16  |
             (++) |-----------------|-------------------|------------------|
             (++) |2WS(3 CPU cycles)|  40 < HCLK <= 60  | 16 < HCLK <= 26  |
             (++) |-----------------|-------------------|------------------|
             (++) |3WS(4 CPU cycles)|  60 < HCLK <= 80  | 16 < HCLK <= 26  |
             (++) |-----------------|-------------------|------------------|
             (++) |4WS(5 CPU cycles)|  80 < HCLK <= 100 | 16 < HCLK <= 26  |
             (++) |-----------------|-------------------|------------------|
             (++) |5WS(6 CPU cycles)| 100 < HCLK <= 120 | 16 < HCLK <= 26  |
             (++) |-----------------|-------------------|------------------|
             (++) |6WS(7 CPU cycles)| 120 < HCLK <= 140 | 16 < HCLK <= 26  |
             (++) |-----------------|-------------------|------------------|
             (++) |7WS(8 CPU cycles)| 140 < HCLK <= 160 | 16 < HCLK <= 26  |
             (++) |-----------------|-------------------|------------------|
             (++) |8WS(9 CPU cycles)| 160 < HCLK <= 170 | 16 < HCLK <= 26  |
             (++) +--------------------------------------------------------+


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
  * @brief  Update number of Flash wait states in line with new frequency and current
            voltage range.
  * @param  HCLKFrequency  HCLK frequency
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Latency has been modified
  *          - ERROR: Latency cannot be modified
  */
ErrorStatus LL_SetFlashLatency(uint32_t HCLKFrequency)
{
  uint32_t timeout;
  uint32_t getlatency;
  ErrorStatus status = SUCCESS;

  uint32_t latency = LL_FLASH_LATENCY_0;  /* default value 0WS */

  /* Frequency cannot be equal to 0 or greater than max clock */
  if((HCLKFrequency == 0U) || (HCLKFrequency > UTILS_SCALE1_LATENCY9_FREQ))
  {
    status = ERROR;
  }
  else
  {
    if(LL_PWR_GetRegulVoltageScaling() == LL_PWR_REGU_VOLTAGE_SCALE1)
    {
      if(HCLKFrequency > UTILS_SCALE1_LATENCY8_FREQ)
      {
        /* 160 < HCLK <= 170 => 8WS (9 CPU cycles) */
        latency = LL_FLASH_LATENCY_8;
      }
      else if(HCLKFrequency > UTILS_SCALE1_LATENCY7_FREQ)
      {
        /* 140 < HCLK <= 160 => 7WS (8 CPU cycles) */
        latency = LL_FLASH_LATENCY_7;
      }
      else if(HCLKFrequency > UTILS_SCALE1_LATENCY6_FREQ)
      {
        /* 120 < HCLK <= 140 => 6WS (7 CPU cycles) */
        latency = LL_FLASH_LATENCY_6;
      }
      else if(HCLKFrequency > UTILS_SCALE1_LATENCY5_FREQ)
      {
        /* 100 < HCLK <= 120 => 5WS (6 CPU cycles) */
        latency = LL_FLASH_LATENCY_5;
      }
      else if(HCLKFrequency > UTILS_SCALE1_LATENCY4_FREQ)
      {
        /* 80 < HCLK <= 100 => 4WS (5 CPU cycles) */
        latency = LL_FLASH_LATENCY_4;
      }
      else if(HCLKFrequency > UTILS_SCALE1_LATENCY3_FREQ)
      {
        /* 60 < HCLK <= 80 => 3WS (4 CPU cycles) */
        latency = LL_FLASH_LATENCY_3;
      }
      else if(HCLKFrequency > UTILS_SCALE1_LATENCY2_FREQ)
      {
        /* 40 < HCLK <= 60 => 2WS (3 CPU cycles) */
        latency = LL_FLASH_LATENCY_2;
      }
      else
      {
        if(HCLKFrequency > UTILS_SCALE1_LATENCY1_FREQ)
        {
          /* 20 < HCLK <= 40 => 1WS (2 CPU cycles) */
          latency = LL_FLASH_LATENCY_1;
        }
        /* else HCLKFrequency <= 10MHz default LL_FLASH_LATENCY_0 0WS */
      }
    }
    else /* SCALE2 */
    {
      if(HCLKFrequency > UTILS_SCALE2_LATENCY2_FREQ)
      {
        /* 16 < HCLK <= 26 => 2WS (3 CPU cycles) */
        latency = LL_FLASH_LATENCY_2;
      }
      else
      {
        if(HCLKFrequency > UTILS_SCALE2_LATENCY1_FREQ)
        {
          /* 8 < HCLK <= 16 => 1WS (2 CPU cycles) */
          latency = LL_FLASH_LATENCY_1;
        }
        /* else HCLKFrequency <= 8MHz default LL_FLASH_LATENCY_0 0WS */
      }
    }

    if (status != ERROR)
    {
      LL_FLASH_SetLatency(latency);

      /* Check that the new number of wait states is taken into account to access the Flash
         memory by reading the FLASH_ACR register */
      timeout = 2U;
      do
      {
        /* Wait for Flash latency to be updated */
        getlatency = LL_FLASH_GetLatency();
        timeout--;
      } while ((getlatency != latency) && (timeout > 0U));

      if(getlatency != latency)
      {
        status = ERROR;
      }
    }
  }

  return status;
}

/**
  * @brief  This function configures system clock at maximum frequency with HSI as clock source of the PLL
  * @note   The application need to ensure that PLL is disabled.
  * @note   Function is based on the following formula:
  *         - PLL output frequency = (((HSI frequency / PLLM) * PLLN) / PLLR)
  *         - PLLM: ensure that the VCO input frequency ranges from 2.66 to 8 MHz (PLLVCO_input = HSI frequency / PLLM)
  *         - PLLN: ensure that the VCO output frequency is between 64 and 344 MHz (PLLVCO_output = PLLVCO_input * PLLN)
  *         - PLLR: ensure that max frequency at 170000000 Hz is reach (PLLVCO_output / PLLR)
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
  uint32_t pllfreq;
  uint32_t hpre = LL_RCC_SYSCLK_DIV_1;

  /* Check if one of the PLL is enabled */
  if(UTILS_PLL_IsBusy() == SUCCESS)
  {
    /* Calculate the new PLL output frequency */
    pllfreq = UTILS_GetPLLOutputFrequency(HSI_VALUE, UTILS_PLLInitStruct);

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
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN,
                                UTILS_PLLInitStruct->PLLR);

    /* Prevent undershoot at highest frequency by applying intermediate AHB prescaler 2 */
    if(pllfreq > 80000000U)
    {
      if (UTILS_ClkInitStruct->AHBCLKDivider == LL_RCC_SYSCLK_DIV_1)
      {
        UTILS_ClkInitStruct->AHBCLKDivider = LL_RCC_SYSCLK_DIV_2;
        hpre = LL_RCC_SYSCLK_DIV_2;
      }
    }

    /* Enable PLL and switch system clock to PLL */
    status = UTILS_EnablePLLAndSwitchSystem(pllfreq, UTILS_ClkInitStruct);

    /* Apply definitive AHB prescaler value if necessary */
    if ((status == SUCCESS) && (hpre != LL_RCC_SYSCLK_DIV_1))
    {
      /* Set FLASH latency to highest latency */
      status = LL_SetFlashLatency(pllfreq);
      if (status == SUCCESS)
      {
        UTILS_ClkInitStruct->AHBCLKDivider = LL_RCC_SYSCLK_DIV_1;
        LL_RCC_SetAHBPrescaler(UTILS_ClkInitStruct->AHBCLKDivider);
        LL_SetSystemCoreClock(pllfreq);
      }
    }
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
  *         - PLL output frequency = (((HSE frequency / PLLM) * PLLN) / PLLR)
  *         - PLLM: ensure that the VCO input frequency ranges from 2.66 to 8 MHz (PLLVCO_input = HSE frequency / PLLM)
  *         - PLLN: ensure that the VCO output frequency is between 64 and 344 MHz (PLLVCO_output = PLLVCO_input * PLLN)
  *         - PLLR: ensure that max frequency at 170000000 Hz is reached (PLLVCO_output / PLLR)
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
  uint32_t pllfreq;
  uint32_t hpre = LL_RCC_SYSCLK_DIV_1;

  /* Check the parameters */
  assert_param(IS_LL_UTILS_HSE_FREQUENCY(HSEFrequency));
  assert_param(IS_LL_UTILS_HSE_BYPASS(HSEBypass));

  /* Check if one of the PLL is enabled */
  if(UTILS_PLL_IsBusy() == SUCCESS)
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
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, UTILS_PLLInitStruct->PLLM, UTILS_PLLInitStruct->PLLN,
                                UTILS_PLLInitStruct->PLLR);

    /* Prevent undershoot at highest frequency by applying intermediate AHB prescaler 2 */
    if(pllfreq > 80000000U)
    {
      if (UTILS_ClkInitStruct->AHBCLKDivider == LL_RCC_SYSCLK_DIV_1)
      {
        UTILS_ClkInitStruct->AHBCLKDivider = LL_RCC_SYSCLK_DIV_2;
        hpre = LL_RCC_SYSCLK_DIV_2;
      }
    }

    /* Enable PLL and switch system clock to PLL */
    status = UTILS_EnablePLLAndSwitchSystem(pllfreq, UTILS_ClkInitStruct);

    /* Apply definitive AHB prescaler value if necessary */
    if ((status == SUCCESS) && (hpre != LL_RCC_SYSCLK_DIV_1))
    {
      /* Set FLASH latency to highest latency */
      status = LL_SetFlashLatency(pllfreq);
      if (status == SUCCESS)
      {
        UTILS_ClkInitStruct->AHBCLKDivider = LL_RCC_SYSCLK_DIV_1;
        LL_RCC_SetAHBPrescaler(UTILS_ClkInitStruct->AHBCLKDivider);
        LL_SetSystemCoreClock(pllfreq);
      }
    }
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
  assert_param(IS_LL_UTILS_PLLR_VALUE(UTILS_PLLInitStruct->PLLR));

  /* Check different PLL parameters according to RM                          */
  /*  - PLLM: ensure that the VCO input frequency ranges from 2.66 to 8 MHz.   */
  pllfreq = PLL_InputFrequency / (((UTILS_PLLInitStruct->PLLM >> RCC_PLLCFGR_PLLM_Pos) + 1U));
  assert_param(IS_LL_UTILS_PLLVCO_INPUT(pllfreq));

  /*  - PLLN: ensure that the VCO output frequency is between 64 and 344 MHz.*/
  pllfreq = pllfreq * (UTILS_PLLInitStruct->PLLN & (RCC_PLLCFGR_PLLN >> RCC_PLLCFGR_PLLN_Pos));
  assert_param(IS_LL_UTILS_PLLVCO_OUTPUT(pllfreq));

  /*  - PLLR: ensure that max frequency at 170000000 Hz is reached                   */
  pllfreq = pllfreq / (((UTILS_PLLInitStruct->PLLR >> RCC_PLLCFGR_PLLR_Pos) + 1U) * 2U);
  assert_param(IS_LL_UTILS_PLL_FREQUENCY(pllfreq));

  return pllfreq;
}

/**
  * @brief  Function to check that PLL can be modified
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: PLL modification can be done
  *          - ERROR: PLL is busy
  */
static ErrorStatus UTILS_PLL_IsBusy(void)
{
  ErrorStatus status = SUCCESS;

  /* Check if PLL is busy*/
  if(LL_RCC_PLL_IsReady() != 0U)
  {
    /* PLL configuration cannot be modified */
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
  ErrorStatus status = SUCCESS;
  uint32_t hclk_frequency;

  assert_param(IS_LL_UTILS_SYSCLK_DIV(UTILS_ClkInitStruct->AHBCLKDivider));
  assert_param(IS_LL_UTILS_APB1_DIV(UTILS_ClkInitStruct->APB1CLKDivider));
  assert_param(IS_LL_UTILS_APB2_DIV(UTILS_ClkInitStruct->APB2CLKDivider));

  /* Calculate HCLK frequency */
  hclk_frequency = __LL_RCC_CALC_HCLK_FREQ(SYSCLK_Frequency, UTILS_ClkInitStruct->AHBCLKDivider);

  /* Increasing the number of wait states because of higher CPU frequency */
  if(SystemCoreClock < hclk_frequency)
  {
    /* Set FLASH latency to highest latency */
    status = LL_SetFlashLatency(hclk_frequency);
  }

  /* Update system clock configuration */
  if(status == SUCCESS)
  {
    /* Enable PLL */
    LL_RCC_PLL_Enable();
    LL_RCC_PLL_EnableDomain_SYS();
    while (LL_RCC_PLL_IsReady() != 1U)
    {
      /* Wait for PLL ready */
    }

    /* Sysclk activation on the main PLL */
    LL_RCC_SetAHBPrescaler(UTILS_ClkInitStruct->AHBCLKDivider);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
    {
      /* Wait for system clock switch to PLL */
    }

    /* Set APB1 & APB2 prescaler*/
    LL_RCC_SetAPB1Prescaler(UTILS_ClkInitStruct->APB1CLKDivider);
    LL_RCC_SetAPB2Prescaler(UTILS_ClkInitStruct->APB2CLKDivider);
  }
    
  /* Decreasing the number of wait states because of lower CPU frequency */
  if(SystemCoreClock > hclk_frequency)
  {
    /* Set FLASH latency to lowest latency */
    status = LL_SetFlashLatency(hclk_frequency);
  }

  /* Update SystemCoreClock variable */
  if(status == SUCCESS)
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
