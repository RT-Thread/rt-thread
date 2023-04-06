/**
  ******************************************************************************
  * @file    stm32u5xx_hal_spi_ex.h
  * @author  MCD Application Team
  * @brief   Header file of SPI HAL Extended module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_HAL_SPI_EX_H
#define STM32U5xx_HAL_SPI_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup SPIEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup SPIEx_Exported_Types SPIEx Exported Types
  * @{
  */

/**
  * @brief  SPI Autonomous Mode Configuration structure definition
  */
typedef struct
{
  uint32_t TriggerState;        /*!< Specifies the trigger state. This parameter can be a value
                                     of @ref FunctionalState */

  uint32_t TriggerSelection;    /*!< Specifies the autonomous mode trigger signal selection. This parameter
                                     can be a value of @ref SPI_AutonomousMode_TriggerSelection */

  uint32_t TriggerPolarity;     /*!< Specifies the autonomous mode trigger signal polarity sensitivity. This parameter
                                     can be a value of @ref SPI_AutonomousMode_TriggerPolarity */

} SPI_AutonomousModeConfTypeDef;


/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup SPIEx_Exported_Constants SPIEx Exported Constants
  * @{
  */

/** @defgroup FunctionalState SPI Autonomous Mode State
  * @{
  */
#define SPI_AUTO_MODE_DISABLE           (0x00000000UL)
#define SPI_AUTO_MODE_ENABLE            SPI_AUTOCR_TRIGEN
/**
  * @}
  */

/** @defgroup SPI_AutonomousMode_TriggerSelection Autonomous Mode Trigger Selection
  * @{
  */
#define SPI_TRIG_GRP1                   (0x10000000U)      /* Trigger Group for SPI1 and SPI2 */
#define SPI_TRIG_GRP2                   (0x20000000U)      /* Trigger Group for SPI3 */

/* HW Trigger signal is GPDMA_CH0_TRG   */
#define SPI_GRP1_GPDMA_CH0_TCF_TRG      (uint32_t)(SPI_TRIG_GRP1 | (0x00000000U))
/* HW Trigger signal is GPDMA_CH1_TRG   */
#define SPI_GRP1_GPDMA_CH1_TCF_TRG      (uint32_t)(SPI_TRIG_GRP1 | (0x1U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is GPDMA_CH2_TRG   */
#define SPI_GRP1_GPDMA_CH2_TCF_TRG      (uint32_t)(SPI_TRIG_GRP1 | (0x2U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is GPDMA_CH3_TRG   */
#define SPI_GRP1_GPDMA_CH3_TCF_TRG      (uint32_t)(SPI_TRIG_GRP1 | (0x3U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is EXTI4_TRG       */
#define SPI_GRP1_EXTI4_TRG              (uint32_t)(SPI_TRIG_GRP1 | (0x4U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is EXTI9_TRG       */
#define SPI_GRP1_EXTI9_TRG              (uint32_t)(SPI_TRIG_GRP1 | (0x5U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM1_CH1_TRG  */
#define SPI_GRP1_LPTIM1_CH1_TRG         (uint32_t)(SPI_TRIG_GRP1 | (0x6U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM2_CH1_TRG  */
#define SPI_GRP1_LPTIM2_CH1_TRG         (uint32_t)(SPI_TRIG_GRP1 | (0x7U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is COMP1_TRG       */
#define SPI_GRP1_COMP1_TRG              (uint32_t)(SPI_TRIG_GRP1 | (0x8U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is COMP2_TRG       */
#define SPI_GRP1_COMP2_TRG              (uint32_t)(SPI_TRIG_GRP1 | (0x9U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is RTC_ALRA_TRG    */
#define SPI_GRP1_RTC_ALRA_TRG           (uint32_t)(SPI_TRIG_GRP1 | (0xAU << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is RTC_WUT_TRG     */
#define SPI_GRP1_RTC_WUT_TRG            (uint32_t)(SPI_TRIG_GRP1 | (0xBU << SPI_AUTOCR_TRIGSEL_Pos))

/* HW Trigger signal is LPDMA_CH0_TRG   */
#define SPI_GRP2_LPDMA_CH0_TCF_TRG      (uint32_t)(SPI_TRIG_GRP2 | (0x00000000U))
/* HW Trigger signal is LPDMA_CH1_TRG   */
#define SPI_GRP2_LPDMA_CH1_TCF_TRG      (uint32_t)(SPI_TRIG_GRP2 | (0x1U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPDMA_CH2_TRG   */
#define SPI_GRP2_LPDMA_CH2_TCF_TRG      (uint32_t)(SPI_TRIG_GRP2 | (0x2U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPDMA_CH3_TRG   */
#define SPI_GRP2_LPDMA_CH3_TCF_TRG      (uint32_t)(SPI_TRIG_GRP2 | (0x3U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is EXTI4_TRG       */
#define SPI_GRP2_EXTI4_TRG              (uint32_t)(SPI_TRIG_GRP2 | (0x4U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is EXTI8_TRG       */
#define SPI_GRP2_EXTI8_TRG              (uint32_t)(SPI_TRIG_GRP2 | (0x5U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM1_CH1_TRG  */
#define SPI_GRP2_LPTIM1_CH1_TRG         (uint32_t)(SPI_TRIG_GRP2 | (0x6U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM3_CH1_TRG  */
#define SPI_GRP2_LPTIM3_CH1_TRG         (uint32_t)(SPI_TRIG_GRP2 | (0x7U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is COMP1_TRG       */
#define SPI_GRP2_COMP1_TRG              (uint32_t)(SPI_TRIG_GRP2 | (0x8U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is COMP2_TRG       */
#define SPI_GRP2_COMP2_TRG              (uint32_t)(SPI_TRIG_GRP2 | (0x9U << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is RTC_ALRA_TRG    */
#define SPI_GRP2_RTC_ALRA_TRG           (uint32_t)(SPI_TRIG_GRP2 | (0xAU << SPI_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is RTC_WUT_TRG     */
#define SPI_GRP2_RTC_WUT_TRG            (uint32_t)(SPI_TRIG_GRP2 | (0xBU << SPI_AUTOCR_TRIGSEL_Pos))
/**
  * @}
  */

/** @defgroup SPI_AutonomousMode_TriggerPolarity Autonomous Mode Trigger Polarity
  * @{
  */
#define SPI_TRIG_POLARITY_RISING        (0x00000000UL)       /* SPI HW Trigger signal on rising edge  */
#define SPI_TRIG_POLARITY_FALLING       SPI_AUTOCR_TRIGPOL   /* SPI HW Trigger signal on falling edge */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup SPIEx_Exported_Macros SPIEx Extended Exported Macros
  * @{
  */

#define IS_SPI_AUTO_MODE(__MODE__)                  (((__MODE__) == SPI_AUTO_MODE_DISABLE) || \
                                                     ((__MODE__) == SPI_AUTO_MODE_ENABLE))

#define IS_SPI_TRIG_SOURCE(__INSTANCE__, __SOURCE__)  (((__INSTANCE__) == SPI3) ? \
                                                       IS_SPI_GRP2_TRIG_SOURCE(__SOURCE__) : \
                                                       IS_SPI_GRP1_TRIG_SOURCE(__SOURCE__))

#define IS_SPI_GRP1_INSTANCE(__INSTANCE__)   (((__INSTANCE__) == SPI1) ||\
                                              ((__INSTANCE__) == SPI2))

#define IS_SPI_GRP2_INSTANCE(__INSTANCE__)    ((__INSTANCE__) == SPI3)

#define IS_SPI_GRP1_TRIG_SOURCE(__SOURCE__)  (((__SOURCE__) == SPI_GRP1_GPDMA_CH0_TCF_TRG  ) || \
                                              ((__SOURCE__) == SPI_GRP1_GPDMA_CH1_TCF_TRG  ) || \
                                              ((__SOURCE__) == SPI_GRP1_GPDMA_CH2_TCF_TRG  ) || \
                                              ((__SOURCE__) == SPI_GRP1_GPDMA_CH3_TCF_TRG  ) || \
                                              ((__SOURCE__) == SPI_GRP1_EXTI4_TRG          ) || \
                                              ((__SOURCE__) == SPI_GRP1_EXTI9_TRG          ) || \
                                              ((__SOURCE__) == SPI_GRP1_LPTIM1_CH1_TRG     ) || \
                                              ((__SOURCE__) == SPI_GRP1_LPTIM2_CH1_TRG     ) || \
                                              ((__SOURCE__) == SPI_GRP1_COMP1_TRG          ) || \
                                              ((__SOURCE__) == SPI_GRP1_COMP2_TRG          ) || \
                                              ((__SOURCE__) == SPI_GRP1_RTC_ALRA_TRG       ) || \
                                              ((__SOURCE__) == SPI_GRP1_RTC_WUT_TRG        ))

#define IS_SPI_GRP2_TRIG_SOURCE(__SOURCE__)  (((__SOURCE__) == SPI_GRP2_LPDMA_CH0_TCF_TRG  ) || \
                                              ((__SOURCE__) == SPI_GRP2_LPDMA_CH1_TCF_TRG  ) || \
                                              ((__SOURCE__) == SPI_GRP2_LPDMA_CH2_TCF_TRG  ) || \
                                              ((__SOURCE__) == SPI_GRP2_LPDMA_CH3_TCF_TRG  ) || \
                                              ((__SOURCE__) == SPI_GRP2_EXTI4_TRG          ) || \
                                              ((__SOURCE__) == SPI_GRP2_EXTI8_TRG          ) || \
                                              ((__SOURCE__) == SPI_GRP2_LPTIM1_CH1_TRG     ) || \
                                              ((__SOURCE__) == SPI_GRP2_LPTIM3_CH1_TRG     ) || \
                                              ((__SOURCE__) == SPI_GRP2_COMP1_TRG          ) || \
                                              ((__SOURCE__) == SPI_GRP2_COMP2_TRG          ) || \
                                              ((__SOURCE__) == SPI_GRP2_RTC_ALRA_TRG       ) || \
                                              ((__SOURCE__) == SPI_GRP2_RTC_WUT_TRG        ))

#define IS_SPI_AUTO_MODE_TRG_POL(__POLARITY__)      (((__POLARITY__) == SPI_TRIG_POLARITY_RISING) || \
                                                     ((__POLARITY__) == SPI_TRIG_POLARITY_FALLING))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup SPIEx_Exported_Functions
  * @{
  */

/* Initialization and de-initialization functions  ****************************/
/* IO operation functions *****************************************************/
/** @addtogroup SPIEx_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_SPIEx_FlushRxFifo(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPIEx_EnableLockConfiguration(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPIEx_ConfigureUnderrun(SPI_HandleTypeDef *hspi, uint32_t UnderrunDetection,
                                              uint32_t UnderrunBehaviour);
/**
  * @}
  */

/** @addtogroup SPI_Autonomous_Mode_Functions Autonomous Mode Functions
  * @{
  */
HAL_StatusTypeDef HAL_SPIEx_SetConfigAutonomousMode(SPI_HandleTypeDef *hspi, SPI_AutonomousModeConfTypeDef *sConfig);
HAL_StatusTypeDef HAL_SPIEx_GetConfigAutonomousMode(SPI_HandleTypeDef *hspi, SPI_AutonomousModeConfTypeDef *sConfig);
HAL_StatusTypeDef HAL_SPIEx_ClearConfigAutonomousMode(SPI_HandleTypeDef *hspi);
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

#endif /* STM32U5xx_HAL_SPI_EX_H */
