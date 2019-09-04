/**
  ******************************************************************************
  * @file    stm32l1xx_hal_tim_ex.h
  * @author  MCD Application Team
  * @brief   Header file of TIM HAL Extended module.
  ******************************************************************************
    * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
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
#ifndef STM32L1xx_HAL_TIM_EX_H
#define STM32L1xx_HAL_TIM_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup TIMEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup TIMEx_Exported_Types TIM Extended Exported Types
  * @{
  */

/**
  * @}
  */
/* End of exported types -----------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup TIMEx_Exported_Constants TIM Extended Exported Constants
  * @{
  */

/** @defgroup TIMEx_Remap TIM Extended Remapping
  * @{
  */
/* @note STM32L1XX devices are organized in 6 categories: Cat.1, Cat.2, Cat.3, Cat.4, Cat.5, Cat.6.
         Remap capabilities depend on the device category. As the DMA2 controller is available only in
         Cat.3, Cat.4,Cat.5 and Cat.6 devices it is used to discriminate Cat.1 and Cat.2 devices v.s.
         Cat.3, Cat.4, Cat.5 and Cat.6 devices. */
#if defined(DMA2)
#define TIM_TIM2_ITR1_TIM10_OC        (0x00000000)       /*!< TIM2 ITR1 input is connected to TIM10 OC */
#define TIM_TIM2_ITR1_TIM5_TGO        TIM2_OR_ITR1_RMP   /*!< TIM2 ITR1 input is connected to TIM5 TGO */
#endif /* DMA2 */

#if defined(DMA2)
#define TIM_TIM3_ITR2_TIM11_OC        (0x00000000)       /*!< TIM3 ITR2 input is connected to TIM11 OC */
#define TIM_TIM3_ITR2_TIM5_TGO        TIM2_OR_ITR1_RMP   /*!< TIM3 ITR2 input is connected to TIM5 TGO */
#endif /* DMA2 */

#if defined(DMA2)
#define TIM_TIM9_ITR1_TIM3_TGO        (0x00000000)       /*!< TIM9 ITR1 input is connected to TIM3 TGO */
#define TIM_TIM9_ITR1_TS              TIM9_OR_ITR1_RMP   /*!< TIM9 ITR1 input is connected to touch sensing I/O */
#endif /* DMA2 */
#define TIM_TIM9_GPIO                 (0x00000000)       /*!< TIM9 Channel1 is connected to GPIO */
#define TIM_TIM9_LSE                  TIM_OR_TI1RMP_0    /*!< TIM9 Channel1 is connected to LSE internal clock */
#define TIM_TIM9_GPIO1                TIM_OR_TI1RMP_1    /*!< TIM9 Channel1 is connected to GPIO */
#define TIM_TIM9_GPIO2                TIM_OR_TI1RMP      /*!< TIM9 Channel1 is connected to GPIO */

#if defined(DMA2)
#define TIM_TIM10_TI1RMP              (0x00000000)       /*!< TIM10 Channel 1 depends on TI1_RMP */
#define TIM_TIM10_RI                  TIM_OR_TI1_RMP_RI  /*!< TIM10 Channel 1 is connected to RI */
#define TIM_TIM10_ETR_LSE             (0x00000000)       /*!< TIM10 ETR input is connected to LSE clock */
#define TIM_TIM10_ETR_TIM9_TGO        TIM_OR_ETR_RMP     /*!< TIM10 ETR input is connected to TIM9 TGO */
#endif /* DMA2 */
#define TIM_TIM10_GPIO                (0x00000000)       /*!< TIM10 Channel1 is connected to GPIO */
#define TIM_TIM10_LSI                 TIM_OR_TI1RMP_0    /*!< TIM10 Channel1 is connected to LSI internal clock */
#define TIM_TIM10_LSE                 TIM_OR_TI1RMP_1    /*!< TIM10 Channel1 is connected to LSE internal clock */
#define TIM_TIM10_RTC                 TIM_OR_TI1RMP      /*!< TIM10 Channel1 is connected to RTC wakeup interrupt */

#if defined(DMA2)
#define TIM_TIM11_TI1RMP              (0x00000000)       /*!< TIM11 Channel 1 depends on TI1_RMP */
#define TIM_TIM11_RI                  TIM_OR_TI1_RMP_RI  /*!< TIM11 Channel 1 is connected to RI */
#define TIM_TIM11_ETR_LSE             (0x00000000)       /*!< TIM11 ETR input is connected to LSE clock */
#define TIM_TIM11_ETR_TIM9_TGO        TIM_OR_ETR_RMP     /*!< TIM11 ETR input is connected to TIM9 TGO */
#endif /* DMA2 */
#define TIM_TIM11_GPIO                (0x00000000)       /*!< TIM11 Channel1 is connected to GPIO */
#define TIM_TIM11_MSI                 TIM_OR_TI1RMP_0    /*!< TIM11 Channel1 is connected to MSI internal clock */
#define TIM_TIM11_HSE_RTC             TIM_OR_TI1RMP_1    /*!< TIM11 Channel1 is connected to HSE_RTC clock */
#define TIM_TIM11_GPIO1               TIM_OR_TI1RMP      /*!< TIM11 Channel1 is connected to GPIO */
/**
  * @}
  */

/**
  * @}
  */
/* End of exported constants -------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/** @defgroup TIMEx_Exported_Macros TIM Extended Exported Macros
  * @{
  */

/**
  * @}
  */
/* End of exported macro -----------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/** @defgroup TIMEx_Private_Macros TIM Extended Private Macros
  * @{
  */
#if defined(DMA2)
#define IS_TIM_REMAP(INSTANCE, TIM_REMAP)               \
        ( (((INSTANCE) == TIM2)  && (((TIM_REMAP) == TIM_TIM2_ITR1_TIM10_OC) || ((TIM_REMAP) == TIM_TIM2_ITR1_TIM5_TGO)))  || \
          (((INSTANCE) == TIM3)  && (((TIM_REMAP) == TIM_TIM3_ITR2_TIM11_OC) || ((TIM_REMAP) == TIM_TIM3_ITR2_TIM5_TGO)))  || \
          (((INSTANCE) == TIM9)  && ((TIM_REMAP) <= (TIM_TIM9_ITR1_TS | TIM_TIM9_GPIO2)))                                  || \
          (((INSTANCE) == TIM10) && ((TIM_REMAP) <= (TIM_TIM10_RI | TIM_TIM10_ETR_TIM9_TGO | TIM_TIM10_RTC)))              || \
          (((INSTANCE) == TIM11) && ((TIM_REMAP) <= (TIM_TIM11_RI | TIM_TIM11_ETR_TIM9_TGO | TIM_TIM11_GPIO1)))               \
        )
#else
#define IS_TIM_REMAP(INSTANCE, TIM_REMAP)               \
        ( (((INSTANCE) == TIM9)  && (((TIM_REMAP) == TIM_TIM9_GPIO) || ((TIM_REMAP) == TIM_TIM9_LSE) || ((TIM_REMAP) == TIM_TIM9_GPIO1) || ((TIM_REMAP) == TIM_TIM9_GPIO2)))       || \
          (((INSTANCE) == TIM10) && (((TIM_REMAP) == TIM_TIM10_GPIO) || ((TIM_REMAP) == TIM_TIM10_LSI) || ((TIM_REMAP) == TIM_TIM10_LSE) || ((TIM_REMAP) == TIM_TIM10_RTC)))       || \
          (((INSTANCE) == TIM11) && (((TIM_REMAP) == TIM_TIM11_GPIO) || ((TIM_REMAP) == TIM_TIM11_MSI) || ((TIM_REMAP) == TIM_TIM11_HSE_RTC) || ((TIM_REMAP) == TIM_TIM11_GPIO1)))    \
        )
#endif /* DMA2 */

/**
  * @}
  */
/* End of private macro ------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup TIMEx_Exported_Functions TIM Extended Exported Functions
  * @{
  */

/** @addtogroup TIMEx_Exported_Functions_Group5 Extended Peripheral Control functions
 *  @brief    Peripheral Control functions
 * @{
 */
/* Extended Control functions  ************************************************/
HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim, TIM_MasterConfigTypeDef *sMasterConfig);
HAL_StatusTypeDef HAL_TIMEx_RemapConfig(TIM_HandleTypeDef *htim, uint32_t Remap);
/**
  * @}
  */

/**
  * @}
  */
/* End of exported functions -------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


#endif /* STM32L1xx_HAL_TIM_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
