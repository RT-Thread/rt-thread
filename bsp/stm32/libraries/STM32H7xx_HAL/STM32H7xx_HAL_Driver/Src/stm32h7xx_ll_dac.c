/**
  ******************************************************************************
  * @file    stm32h7xx_ll_dac.c
  * @author  MCD Application Team
  * @brief   DAC LL module driver
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_ll_dac.h"
#include "stm32h7xx_ll_bus.h"

#ifdef USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32H7xx_LL_Driver
  * @{
  */

#if defined(DAC1) || defined(DAC2)

/** @addtogroup DAC_LL DAC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup DAC_LL_Private_Macros
  * @{
  */
#define IS_LL_DAC_CHANNEL(__DAC_CHANNEL__)        \
  (((__DAC_CHANNEL__) == LL_DAC_CHANNEL_1)      \
   || ((__DAC_CHANNEL__) == LL_DAC_CHANNEL_2)   \
  )

#if defined (HRTIM1)
#define IS_LL_DAC_TRIGGER_SOURCE(__TRIGGER_SOURCE__)                           \
  (((__TRIGGER_SOURCE__) == LL_DAC_TRIG_SOFTWARE)                              \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM1_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM2_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM4_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM5_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM6_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM7_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM8_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM15_TRGO)                     \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_HRTIM_TRGO1)                    \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_HRTIM_TRGO2)                    \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_LPTIM1_OUT)                     \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_LPTIM2_OUT)                     \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_EXTI_LINE9)                     \
  )
#elif defined (DAC2)
#define IS_LL_DAC_TRIGGER_SOURCE(__TRIGGER_SOURCE__)                           \
  (((__TRIGGER_SOURCE__) == LL_DAC_TRIG_SOFTWARE)                              \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM1_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM2_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM4_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM5_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM6_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM7_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM8_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM15_TRGO)                     \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_LPTIM1_OUT)                     \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_LPTIM2_OUT)                     \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_EXTI_LINE9)                     \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_LPTIM3_OUT)                     \
  )
#else
#define IS_LL_DAC_TRIGGER_SOURCE(__TRIGGER_SOURCE__)                           \
  (((__TRIGGER_SOURCE__) == LL_DAC_TRIG_SOFTWARE)                              \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM1_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM2_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM4_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM5_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM6_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM7_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM8_TRGO)                      \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM15_TRGO)                     \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_LPTIM1_OUT)                     \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_LPTIM2_OUT)                     \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_EXTI_LINE9)                     \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM23_TRGO)                     \
   || ((__TRIGGER_SOURCE__) == LL_DAC_TRIG_EXT_TIM24_TRGO)                     \
  )
#endif /* HRTIM1 */

#define IS_LL_DAC_WAVE_AUTO_GENER_MODE(__WAVE_AUTO_GENERATION_MODE__)              \
  (((__WAVE_AUTO_GENERATION_MODE__) == LL_DAC_WAVE_AUTO_GENERATION_NONE)           \
   || ((__WAVE_AUTO_GENERATION_MODE__) == LL_DAC_WAVE_AUTO_GENERATION_NOISE)       \
   || ((__WAVE_AUTO_GENERATION_MODE__) == LL_DAC_WAVE_AUTO_GENERATION_TRIANGLE)    \
  )

#define IS_LL_DAC_WAVE_AUTO_GENER_CONFIG(__WAVE_AUTO_GENERATION_MODE__, __WAVE_AUTO_GENERATION_CONFIG__)  \
  ( (((__WAVE_AUTO_GENERATION_MODE__) == LL_DAC_WAVE_AUTO_GENERATION_NOISE)                               \
     && (((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_NOISE_LFSR_UNMASK_BIT0)                             \
         || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_NOISE_LFSR_UNMASK_BITS1_0)                       \
         || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_NOISE_LFSR_UNMASK_BITS2_0)                       \
         || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_NOISE_LFSR_UNMASK_BITS3_0)                       \
         || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_NOISE_LFSR_UNMASK_BITS4_0)                       \
         || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_NOISE_LFSR_UNMASK_BITS5_0)                       \
         || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_NOISE_LFSR_UNMASK_BITS6_0)                       \
         || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_NOISE_LFSR_UNMASK_BITS7_0)                       \
         || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_NOISE_LFSR_UNMASK_BITS8_0)                       \
         || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_NOISE_LFSR_UNMASK_BITS9_0)                       \
         || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_NOISE_LFSR_UNMASK_BITS10_0)                      \
         || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_NOISE_LFSR_UNMASK_BITS11_0))                     \
    )                                                                                                     \
    ||(((__WAVE_AUTO_GENERATION_MODE__) == LL_DAC_WAVE_AUTO_GENERATION_TRIANGLE)                          \
       && (((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_TRIANGLE_AMPLITUDE_1)                             \
           || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_TRIANGLE_AMPLITUDE_3)                          \
           || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_TRIANGLE_AMPLITUDE_7)                          \
           || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_TRIANGLE_AMPLITUDE_15)                         \
           || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_TRIANGLE_AMPLITUDE_31)                         \
           || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_TRIANGLE_AMPLITUDE_63)                         \
           || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_TRIANGLE_AMPLITUDE_127)                        \
           || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_TRIANGLE_AMPLITUDE_255)                        \
           || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_TRIANGLE_AMPLITUDE_511)                        \
           || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_TRIANGLE_AMPLITUDE_1023)                       \
           || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_TRIANGLE_AMPLITUDE_2047)                       \
           || ((__WAVE_AUTO_GENERATION_CONFIG__) == LL_DAC_TRIANGLE_AMPLITUDE_4095))                      \
      )                                                                                                   \
  )

#define IS_LL_DAC_OUTPUT_BUFFER(__OUTPUT_BUFFER__)                             \
  (((__OUTPUT_BUFFER__) == LL_DAC_OUTPUT_BUFFER_ENABLE)                        \
   || ((__OUTPUT_BUFFER__) == LL_DAC_OUTPUT_BUFFER_DISABLE)                    \
  )

#define IS_LL_DAC_OUTPUT_CONNECTION(__OUTPUT_CONNECTION__)                     \
  (((__OUTPUT_CONNECTION__) == LL_DAC_OUTPUT_CONNECT_GPIO)                     \
   || ((__OUTPUT_CONNECTION__) == LL_DAC_OUTPUT_CONNECT_INTERNAL)              \
  )

#define IS_LL_DAC_OUTPUT_MODE(__OUTPUT_MODE__)                                 \
  (((__OUTPUT_MODE__) == LL_DAC_OUTPUT_MODE_NORMAL)                            \
   || ((__OUTPUT_MODE__) == LL_DAC_OUTPUT_MODE_SAMPLE_AND_HOLD)                \
  )

/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup DAC_LL_Exported_Functions
  * @{
  */

/** @addtogroup DAC_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize registers of the selected DAC instance
  *         to their default reset values.
  * @param  DACx DAC instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: DAC registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_DAC_DeInit(const DAC_TypeDef *DACx)
{
  /* Check the parameters */
  assert_param(IS_DAC_ALL_INSTANCE(DACx));

  if (DACx == DAC1)
  {
    /* Force reset of DAC clock */
    LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_DAC12);

    /* Release reset of DAC clock */
    LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_DAC12);
  }
#if defined (DAC2)
  else
  {
    /* Force reset of DAC clock */
    LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_DAC2);

    /* Release reset of DAC clock */
    LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_DAC2);
  }
#endif /* DAC2 */

  return SUCCESS;
}

/**
  * @brief  Initialize some features of DAC channel.
  * @note   @ref LL_DAC_Init() aims to ease basic configuration of a DAC channel.
  *         Leaving it ready to be enabled and output:
  *         a level by calling one of
  *           @ref LL_DAC_ConvertData12RightAligned
  *           @ref LL_DAC_ConvertData12LeftAligned
  *           @ref LL_DAC_ConvertData8RightAligned
  *         or one of the supported autogenerated wave.
  * @note   This function allows configuration of:
  *          - Output mode
  *          - Trigger
  *          - Wave generation
  * @note   The setting of these parameters by function @ref LL_DAC_Init()
  *         is conditioned to DAC state:
  *         DAC channel must be disabled.
  * @param  DACx DAC instance
  * @param  DAC_Channel This parameter can be one of the following values:
  *         @arg @ref LL_DAC_CHANNEL_1
  *         @arg @ref LL_DAC_CHANNEL_2
  * @param  DAC_InitStruct Pointer to a @ref LL_DAC_InitTypeDef structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: DAC registers are initialized
  *          - ERROR: DAC registers are not initialized
  */
ErrorStatus LL_DAC_Init(DAC_TypeDef *DACx, uint32_t DAC_Channel, const LL_DAC_InitTypeDef *DAC_InitStruct)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_DAC_ALL_INSTANCE(DACx));
  assert_param(IS_LL_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_LL_DAC_TRIGGER_SOURCE(DAC_InitStruct->TriggerSource));
  assert_param(IS_LL_DAC_OUTPUT_BUFFER(DAC_InitStruct->OutputBuffer));
  assert_param(IS_LL_DAC_OUTPUT_CONNECTION(DAC_InitStruct->OutputConnection));
  assert_param(IS_LL_DAC_OUTPUT_MODE(DAC_InitStruct->OutputMode));
  assert_param(IS_LL_DAC_WAVE_AUTO_GENER_MODE(DAC_InitStruct->WaveAutoGeneration));
  if (DAC_InitStruct->WaveAutoGeneration != LL_DAC_WAVE_AUTO_GENERATION_NONE)
  {
    assert_param(IS_LL_DAC_WAVE_AUTO_GENER_CONFIG(DAC_InitStruct->WaveAutoGeneration,
                                                  DAC_InitStruct->WaveAutoGenerationConfig));
  }

  /* Note: Hardware constraint (refer to description of this function)        */
  /*       DAC instance must be disabled.                                     */
  if (LL_DAC_IsEnabled(DACx, DAC_Channel) == 0UL)
  {
    /* Configuration of DAC channel:                                          */
    /*  - TriggerSource                                                       */
    /*  - WaveAutoGeneration                                                  */
    /*  - OutputBuffer                                                        */
    /*  - OutputConnection                                                    */
    /*  - OutputMode                                                          */
    if (DAC_InitStruct->WaveAutoGeneration != LL_DAC_WAVE_AUTO_GENERATION_NONE)
    {
      MODIFY_REG(DACx->CR,
                 (DAC_CR_TSEL1
                  | DAC_CR_WAVE1
                  | DAC_CR_MAMP1
                 ) << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK)
                 ,
                 (DAC_InitStruct->TriggerSource
                  | DAC_InitStruct->WaveAutoGeneration
                  | DAC_InitStruct->WaveAutoGenerationConfig
                 ) << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK)
                );
    }
    else
    {
      MODIFY_REG(DACx->CR,
                 (DAC_CR_TSEL1
                  | DAC_CR_WAVE1
                 ) << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK)
                 ,
                 (DAC_InitStruct->TriggerSource
                  | LL_DAC_WAVE_AUTO_GENERATION_NONE
                 ) << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK)
                );
    }
    MODIFY_REG(DACx->MCR,
               (DAC_MCR_MODE1_1
                | DAC_MCR_MODE1_0
                | DAC_MCR_MODE1_2
               ) << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK)
               ,
               (DAC_InitStruct->OutputBuffer
                | DAC_InitStruct->OutputConnection
                | DAC_InitStruct->OutputMode
               ) << (DAC_Channel & DAC_CR_CHX_BITOFFSET_MASK)
              );
  }
  else
  {
    /* Initialization error: DAC instance is not disabled.                    */
    status = ERROR;
  }
  return status;
}

/**
  * @brief Set each @ref LL_DAC_InitTypeDef field to default value.
  * @param DAC_InitStruct pointer to a @ref LL_DAC_InitTypeDef structure
  *                       whose fields will be set to default values.
  * @retval None
  */
void LL_DAC_StructInit(LL_DAC_InitTypeDef *DAC_InitStruct)
{
  /* Set DAC_InitStruct fields to default values */
  DAC_InitStruct->TriggerSource            = LL_DAC_TRIG_SOFTWARE;
  DAC_InitStruct->WaveAutoGeneration       = LL_DAC_WAVE_AUTO_GENERATION_NONE;
  /* Note: Parameter discarded if wave auto generation is disabled,           */
  /*       set anyway to its default value.                                   */
  DAC_InitStruct->WaveAutoGenerationConfig = LL_DAC_NOISE_LFSR_UNMASK_BIT0;
  DAC_InitStruct->OutputBuffer             = LL_DAC_OUTPUT_BUFFER_ENABLE;
  DAC_InitStruct->OutputConnection         = LL_DAC_OUTPUT_CONNECT_GPIO;
  DAC_InitStruct->OutputMode               = LL_DAC_OUTPUT_MODE_NORMAL;
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

#endif /* DAC1 || DAC2 */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */
