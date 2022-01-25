/**
  ******************************************************************************
  * @file    stm32l5xx_ll_icache.c
  * @author  MCD Application Team
  * @brief   ICACHE LL module driver.
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
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_ll_icache.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32L5xx_LL_Driver
  * @{
  */

#if defined(ICACHE)

/** @defgroup ICACHE_LL ICACHE
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup ICACHE_LL_Private_Macros ICACHE Private Macros
  * @{
  */

#define IS_LL_ICACHE_REGION(__VALUE__)    (((__VALUE__) == LL_ICACHE_REGION_0) || \
                                           ((__VALUE__) == LL_ICACHE_REGION_1) || \
                                           ((__VALUE__) == LL_ICACHE_REGION_2) || \
                                           ((__VALUE__) == LL_ICACHE_REGION_3))

#define IS_LL_ICACHE_REGION_SIZE(__VALUE__) (((__VALUE__) == LL_ICACHE_REGIONSIZE_2MB)  || \
                                             ((__VALUE__) == LL_ICACHE_REGIONSIZE_4MB)  || \
                                             ((__VALUE__) == LL_ICACHE_REGIONSIZE_8MB)  || \
                                             ((__VALUE__) == LL_ICACHE_REGIONSIZE_16MB) || \
                                             ((__VALUE__) == LL_ICACHE_REGIONSIZE_32MB) || \
                                             ((__VALUE__) == LL_ICACHE_REGIONSIZE_64MB) || \
                                             ((__VALUE__) == LL_ICACHE_REGIONSIZE_128MB))

#define IS_LL_ICACHE_MASTER_PORT(__VALUE__) (((__VALUE__) == LL_ICACHE_MASTER1_PORT) || \
                                             ((__VALUE__) == LL_ICACHE_MASTER2_PORT))

#define IS_LL_ICACHE_OUTPUT_BURST(__VALUE__) (((__VALUE__) == LL_ICACHE_OUTPUT_BURST_WRAP) || \
                                              ((__VALUE__) == LL_ICACHE_OUTPUT_BURST_INCR))

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ICACHE_LL_Exported_Functions
  * @{
  */

/** @addtogroup ICACHE_LL_EF_REGION_Init
  * @{
  */

/**
  * @brief  Configure and enable the memory remapped region.
  * @note   The Instruction Cache and corresponding region must be disabled.
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_ICACHE_REGION_0
  *         @arg @ref LL_ICACHE_REGION_1
  *         @arg @ref LL_ICACHE_REGION_2
  *         @arg @ref LL_ICACHE_REGION_3
  * @param  ICACHE_RegionStruct pointer to a @ref LL_ICACHE_RegionTypeDef structure.
  * @retval None
  */
void LL_ICACHE_ConfigRegion(uint32_t Region, LL_ICACHE_RegionTypeDef *ICACHE_RegionStruct)
{
  __IO uint32_t *reg;
  uint32_t value;

  /* Check the parameters */
  assert_param(IS_LL_ICACHE_REGION(Region));
  assert_param(IS_LL_ICACHE_REGION_SIZE(ICACHE_RegionStruct->Size));
  assert_param(IS_LL_ICACHE_MASTER_PORT(ICACHE_RegionStruct->TrafficRoute));
  assert_param(IS_LL_ICACHE_OUTPUT_BURST(ICACHE_RegionStruct->OutputBurstType));

  /* Get region control register address */
  reg = &(ICACHE->CRR0) + (1U * Region);

  /* Region 2MB:   BaseAddress size 8 bits, RemapAddress size 11 bits */
  /* Region 4MB:   BaseAddress size 7 bits, RemapAddress size 10 bits */
  /* Region 8MB:   BaseAddress size 6 bits, RemapAddress size 9 bits  */
  /* Region 16MB:  BaseAddress size 5 bits, RemapAddress size 8 bits  */
  /* Region 32MB:  BaseAddress size 4 bits, RemapAddress size 7 bits  */
  /* Region 64MB:  BaseAddress size 3 bits, RemapAddress size 6 bits  */
  /* Region 128MB: BaseAddress size 2 bits, RemapAddress size 5 bits  */
  value  = ((ICACHE_RegionStruct->BaseAddress & 0x1FFFFFFFU) >> 21U) & (0xFFU & ~(ICACHE_RegionStruct->Size - 1U));
  value |= ((ICACHE_RegionStruct->RemapAddress >> 5U) & ((uint32_t)(0x7FFU & ~(ICACHE_RegionStruct->Size - 1U)) << ICACHE_CRRx_REMAPADDR_Pos));
  value |= (ICACHE_RegionStruct->Size << ICACHE_CRRx_RSIZE_Pos) | ICACHE_RegionStruct->TrafficRoute | ICACHE_RegionStruct->OutputBurstType;
  *reg = (value | ICACHE_CRRx_REN);  /* Configure and enable region */
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

#endif /* ICACHE */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
