/**
  ******************************************************************************
  * @file    stm32h7xx_ll_utils.h
  * @author  MCD Application Team
  * @brief   Header file of UTILS LL module.
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The LL UTILS driver contains a set of generic APIs that can be
    used by user:
      (+) Device electronic signature
      (+) Timing functions
      (+) PLL configuration functions

  @endverbatim
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7xx_LL_UTILS_H
#define STM32H7xx_LL_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx.h"
#include "stm32h7xx_ll_system.h"
#include "stm32h7xx_ll_bus.h"

/** @addtogroup STM32H7xx_LL_Driver
  * @{
  */

/** @defgroup UTILS_LL UTILS
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup UTILS_LL_Private_Constants UTILS Private Constants
  * @{
  */

/* Max delay can be used in LL_mDelay */
#define LL_MAX_DELAY                  0xFFFFFFFFU

/**
 * @brief Unique device ID register base address
 */
#define UID_BASE_ADDRESS              UID_BASE

/**
 * @brief Flash size data register base address
 */
#define FLASHSIZE_BASE_ADDRESS        FLASHSIZE_BASE

/**
 * @brief Package data register base address
 */
#define PACKAGE_BASE_ADDRESS          PACKAGE_BASE

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup UTILS_LL_Private_Macros UTILS Private Macros
  * @{
  */
/**
  * @}
  */
/* Exported types ------------------------------------------------------------*/
/** @defgroup UTILS_LL_ES_INIT UTILS Exported structures
  * @{
  */
/**
  * @brief  UTILS PLL structure definition
  */
typedef struct
{
  uint32_t PLLM;   /*!< Division factor for PLL VCO input clock.
                        This parameter must be a number between Min_Data = 0 and Max_Data = 63

                        This feature can be modified afterwards using unitary function
                        @ref LL_RCC_PLL1_SetM(). */

  uint32_t PLLN;   /*!< Multiplication factor for PLL VCO output clock.
                        This parameter must be a number between Min_Data = 4 and Max_Data = 512

                        This feature can be modified afterwards using unitary function
                        @ref LL_RCC_PLL1_SetN(). */

  uint32_t PLLP;   /*!< Division for the main system clock.
                        This parameter must be a number between Min_Data = 2 and Max_Data = 128
                          odd division factors are not allowed

                        This feature can be modified afterwards using unitary function
                        @ref LL_RCC_PLL1_SetP(). */

  uint32_t FRACN;  /*!< Fractional part of the multiplication factor for PLL VCO.
                        This parameter can be a value between 0 and 8191

                        This feature can be modified afterwards using unitary function
                        @ref LL_RCC_PLL1_SetFRACN(). */

  uint32_t VCO_Input;  /*!< Fractional part of the multiplication factor for PLL VCO.
                        This parameter can be a value of @ref RCC_LL_EC_PLLINPUTRANGE

                        This feature can be modified afterwards using unitary function
                        @ref LL_RCC_PLL1_SetVCOInputRange(). */

  uint32_t VCO_Output;  /*!< Fractional part of the multiplication factor for PLL VCO.
                        This parameter can be a value of @ref RCC_LL_EC_PLLVCORANGE

                      This feature can be modified afterwards using unitary function
                      @ref LL_RCC_PLL1_SetVCOOutputRange(). */

} LL_UTILS_PLLInitTypeDef;

/**
  * @brief  UTILS System, AHB and APB buses clock configuration structure definition
  */
typedef struct
{
  uint32_t SYSCLKDivider;         /*!< The System clock (SYSCLK) divider. This clock is derived from the PLL output.
                                     This parameter can be a value of @ref RCC_LL_EC_SYSCLK_DIV

                                     This feature can be modified afterwards using unitary function
                                     @ref LL_RCC_SetSysPrescaler(). */

  uint32_t AHBCLKDivider;         /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_LL_EC_AHB_DIV

                                       This feature can be modified afterwards using unitary function
                                       @ref LL_RCC_SetAHBPrescaler(). */

  uint32_t APB1CLKDivider;        /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_LL_EC_APB1_DIV

                                       This feature can be modified afterwards using unitary function
                                       @ref LL_RCC_SetAPB1Prescaler(). */

  uint32_t APB2CLKDivider;        /*!< The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_LL_EC_APB2_DIV

                                       This feature can be modified afterwards using unitary function
                                       @ref LL_RCC_SetAPB2Prescaler(). */

  uint32_t APB3CLKDivider;        /*!< The APB2 clock (PCLK3) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_LL_EC_APB3_DIV

                                       This feature can be modified afterwards using unitary function
                                       @ref LL_RCC_SetAPB3Prescaler(). */

  uint32_t APB4CLKDivider;        /*!< The APB4 clock (PCLK4) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_LL_EC_APB4_DIV

                                       This feature can be modified afterwards using unitary function
                                       @ref LL_RCC_SetAPB4Prescaler(). */

} LL_UTILS_ClkInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup UTILS_LL_Exported_Constants UTILS Exported Constants
  * @{
  */

/** @defgroup UTILS_EC_HSE_BYPASS HSE Bypass activation
  * @{
  */
#define LL_UTILS_HSEBYPASS_OFF        0x00000000U       /*!< HSE Bypass is not enabled                */
#define LL_UTILS_HSEBYPASS_ON         0x00000001U       /*!< HSE Bypass is enabled                    */
/**
  * @}
  */

/** @defgroup UTILS_EC_PACKAGETYPE PACKAGE TYPE
  * @{
  */
#define LL_UTILS_PACKAGETYPE_LQFP100            LL_SYSCFG_LQFP100_PACKAGE          /*!< LQFP100 package type             */
#define LL_UTILS_PACKAGETYPE_TQFP144            LL_SYSCFG_TQFP144_PACKAGE          /*!< TQFP144 package type             */
#define LL_UTILS_PACKAGETYPE_TQFP176_UFBGA176   LL_SYSCFG_TQFP176_UFBGA176_PACKAGE /*!< TQFP176 or UFBGA176 package type */
#define LL_UTILS_PACKAGETYPE_LQFP208_TFBGA240   LL_SYSCFG_LQFP208_TFBGA240_PACKAGE /*!< LQFP208 or TFBGA240 package type */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup UTILS_LL_Exported_Functions UTILS Exported Functions
  * @{
  */

/** @defgroup UTILS_EF_DEVICE_ELECTRONIC_SIGNATURE DEVICE ELECTRONIC SIGNATURE
  * @{
  */

/**
  * @brief  Get Word0 of the unique device identifier (UID based on 96 bits)
  * @retval UID[31:0]
  */
__STATIC_INLINE uint32_t LL_GetUID_Word0(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)UID_BASE_ADDRESS)));
}

/**
  * @brief  Get Word1 of the unique device identifier (UID based on 96 bits)
  * @retval UID[63:32]
  */
__STATIC_INLINE uint32_t LL_GetUID_Word1(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)(UID_BASE_ADDRESS + 4U))));
}

/**
  * @brief  Get Word2 of the unique device identifier (UID based on 96 bits)
  * @retval UID[95:64]
  */
__STATIC_INLINE uint32_t LL_GetUID_Word2(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)(UID_BASE_ADDRESS + 8U))));
}

/**
  * @brief  Get Flash memory size
  * @note   This bitfield indicates the size of the device Flash memory expressed in
  *         Kbytes. As an example, 0x040 corresponds to 64 Kbytes.
  * @retval FLASH_SIZE[15:0]: Flash memory size
  */
__STATIC_INLINE uint32_t LL_GetFlashSize(void)
{
  return (uint16_t)(READ_REG(*((uint32_t *)FLASHSIZE_BASE_ADDRESS)));
}

/**
  * @brief  Get Package type
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_UTILS_PACKAGETYPE_LQFP100
  *         @arg @ref LL_UTILS_PACKAGETYPE_TQFP144
  *         @arg @ref LL_UTILS_PACKAGETYPE_TQFP176_UFBGA176
  *         @arg @ref LL_UTILS_PACKAGETYPE_LQFP208_TFBGA240
  */
__STATIC_INLINE uint32_t LL_GetPackageType(void)
{

  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_SYSCFG);

  return LL_SYSCFG_GetPackage();
}

/**
  * @}
  */

/** @defgroup UTILS_LL_EF_DELAY DELAY
  * @{
  */

/**
  * @brief  This function configures the Cortex-M SysTick source of the time base.
  * @param  HCLKFrequency HCLK frequency in Hz (can be calculated thanks to RCC helper macro)
  * @note   When a RTOS is used, it is recommended to avoid changing the SysTick
  *         configuration by calling this function, for a delay use rather osDelay RTOS service.
  * @param  Ticks Number of ticks
  * @retval None
  */
__STATIC_INLINE void LL_InitTick(uint32_t HCLKFrequency, uint32_t Ticks)
{
  /* Configure the SysTick to have interrupt in 1ms time base */
  SysTick->LOAD  = (uint32_t)((HCLKFrequency / Ticks) - 1UL);  /* set reload register */
  SysTick->VAL   = 0UL;                                       /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_ENABLE_Msk;                   /* Enable the Systick Timer */
}

void        LL_Init1msTick(uint32_t CPU_Frequency);
void        LL_mDelay(uint32_t Delay);

/**
  * @}
  */

/** @defgroup UTILS_EF_SYSTEM SYSTEM
  * @{
  */

void        LL_SetSystemCoreClock(uint32_t CPU_Frequency);
ErrorStatus LL_PLL_ConfigSystemClock_HSI(LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct,
                                         LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct);
ErrorStatus LL_PLL_ConfigSystemClock_HSE(uint32_t HSEFrequency,
                                         uint32_t HSEBypass,
                                         LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct,
                                         LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7xx_LL_UTILS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
