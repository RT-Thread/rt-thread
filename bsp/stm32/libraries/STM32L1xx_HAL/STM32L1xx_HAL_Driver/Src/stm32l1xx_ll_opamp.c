/**
  ******************************************************************************
  * @file    stm32l1xx_ll_opamp.c
  * @author  MCD Application Team
  * @brief   OPAMP LL module driver
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
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_ll_opamp.h"

#ifdef  USE_FULL_ASSERT
  #include "stm32_assert.h"
#else
  #define assert_param(expr) ((void)0U)
#endif

/** @addtogroup STM32L1xx_LL_Driver
  * @{
  */

#if defined (OPAMP1) || defined (OPAMP2) || defined (OPAMP3) 

/** @addtogroup OPAMP_LL OPAMP
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup OPAMP_LL_Private_Macros
  * @{
  */

/* Check of parameters for configuration of OPAMP hierarchical scope:         */
/* OPAMP instance.                                                            */

#define IS_LL_OPAMP_POWER_MODE(__POWER_MODE__)                                 \
  (   ((__POWER_MODE__) == LL_OPAMP_POWERMODE_NORMAL)                          \
   || ((__POWER_MODE__) == LL_OPAMP_POWERMODE_LOWPOWER))

#define IS_LL_OPAMP_FUNCTIONAL_MODE(__FUNCTIONAL_MODE__)                       \
  (   ((__FUNCTIONAL_MODE__) == LL_OPAMP_MODE_STANDALONE)                      \
   || ((__FUNCTIONAL_MODE__) == LL_OPAMP_MODE_FOLLOWER)                        \
  )

/* Note: Comparator non-inverting inputs parameters are different             */
/*       depending on OPAMP instance.                                         */
#if defined(OPAMP3)
#define IS_LL_OPAMP_INPUT_NONINVERTING(__OPAMPX__, __INPUT_NONINVERTING__)        \
  (((__OPAMPX__) == OPAMP1)                                                       \
    ? (                                                                           \
          ((__INPUT_NONINVERTING__) == LL_OPAMP_INPUT_NONINVERT_IO0)              \
       || ((__INPUT_NONINVERTING__) == LL_OPAMP_INPUT_NONINV_DAC1_CH1)            \
      )                                                                           \
      :                                                                           \
      (((__OPAMPX__) == OPAMP2)                                                   \
        ? (                                                                       \
              ((__INPUT_NONINVERTING__) == LL_OPAMP_INPUT_NONINVERT_IO0)          \
           || ((__INPUT_NONINVERTING__) == LL_OPAMP_INPUT_NONINV_DAC1_CH1)        \
           || ((__INPUT_NONINVERTING__) == LL_OPAMP_INPUT_NONINV_DAC1_CH2)        \
          )                                                                       \
          :                                                                       \
          (                                                                       \
              ((__INPUT_NONINVERTING__) == LL_OPAMP_INPUT_NONINVERT_IO0)          \
           || ((__INPUT_NONINVERTING__) == LL_OPAMP_INPUT_NONINV_DAC1_CH2_OPAMP3) \
          )                                                                       \
      )                                                                           \
  )
#else
#define IS_LL_OPAMP_INPUT_NONINVERTING(__OPAMPX__, __INPUT_NONINVERTING__)     \
  (((__OPAMPX__) == OPAMP1)                                                    \
    ? (                                                                        \
          ((__INPUT_NONINVERTING__) == LL_OPAMP_INPUT_NONINVERT_IO0)           \
       || ((__INPUT_NONINVERTING__) == LL_OPAMP_INPUT_NONINV_DAC1_CH1)         \
      )                                                                        \
      :                                                                        \
      (                                                                        \
          ((__INPUT_NONINVERTING__) == LL_OPAMP_INPUT_NONINVERT_IO0)           \
       || ((__INPUT_NONINVERTING__) == LL_OPAMP_INPUT_NONINV_DAC1_CH1)         \
       || ((__INPUT_NONINVERTING__) == LL_OPAMP_INPUT_NONINV_DAC1_CH2)         \
      )                                                                        \
  )
#endif

/* Note: Comparator non-inverting inputs parameters are the same on all       */
/*       OPAMP instances.                                                     */
/*       However, comparator instance kept as macro parameter for             */
/*       compatibility with other STM32 families.                             */
#define IS_LL_OPAMP_INPUT_INVERTING(__OPAMPX__, __INPUT_INVERTING__)           \
  (   ((__INPUT_INVERTING__) == LL_OPAMP_INPUT_INVERT_IO0)                     \
   || ((__INPUT_INVERTING__) == LL_OPAMP_INPUT_INVERT_IO1)                     \
   || ((__INPUT_INVERTING__) == LL_OPAMP_INPUT_INVERT_CONNECT_NO)              \
  )

/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup OPAMP_LL_Exported_Functions
  * @{
  */

/** @addtogroup OPAMP_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize registers of the selected OPAMP instance
  *         to their default reset values.
  * @param  OPAMPx OPAMP instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: OPAMP registers are de-initialized
  *          - ERROR: OPAMP registers are not de-initialized
  */
ErrorStatus LL_OPAMP_DeInit(OPAMP_TypeDef* OPAMPx)
{
  ErrorStatus status = SUCCESS;
  
  /* Check the parameters */
  assert_param(IS_OPAMP_ALL_INSTANCE(OPAMPx));
  
  MODIFY_REG(OPAMP->CSR,
               (OPAMP_CSR_S3SEL1 | OPAMP_CSR_S4SEL1 | OPAMP_CSR_S5SEL1 | OPAMP_CSR_S6SEL1 | OPAMP_CSR_OPA1CAL_L | OPAMP_CSR_OPA1CAL_H | OPAMP_CSR_OPA1LPM) << __OPAMP_INSTANCE_BITOFFSET(OPAMPx)
             | (OPAMP_CSR_ANAWSEL1) << __OPAMP_INSTANCE_DECIMAL(OPAMPx)
             | (OPAMP_CSR_S7SEL2 * __OPAMP_IS_INSTANCE_OPAMP2(OPAMPx)) ,
             (OPAMP_CSR_OPA1PD) << __OPAMP_INSTANCE_BITOFFSET(OPAMPx)
            );
  return status;
}

/**
  * @brief  Initialize some features of OPAMP instance.
  * @note   This function reset bit of calibration mode to ensure
  *         to be in functional mode, in order to have OPAMP parameters
  *         (inputs selection, ...) set with the corresponding OPAMP mode
  *         to be effective.
  * @note   This function configures features of the selected OPAMP instance.
  *         Some features are also available at scope OPAMP common instance
  *         (common to several OPAMP instances).
  *         Refer to functions having argument "OPAMPxy_COMMON" as parameter.
  * @param  OPAMPx OPAMP instance
  * @param  OPAMP_InitStruct Pointer to a @ref LL_OPAMP_InitTypeDef structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: OPAMP registers are initialized
  *          - ERROR: OPAMP registers are not initialized
  */
ErrorStatus LL_OPAMP_Init(OPAMP_TypeDef *OPAMPx, LL_OPAMP_InitTypeDef *OPAMP_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_OPAMP_ALL_INSTANCE(OPAMPx));
  assert_param(IS_LL_OPAMP_POWER_MODE(OPAMP_InitStruct->PowerMode));
  assert_param(IS_LL_OPAMP_FUNCTIONAL_MODE(OPAMP_InitStruct->FunctionalMode));
  assert_param(IS_LL_OPAMP_INPUT_NONINVERTING(OPAMPx, OPAMP_InitStruct->InputNonInverting));
  
  /* Note: OPAMP inverting input can be used with OPAMP in mode standalone.   */
  /*       Otherwise (OPAMP in mode follower), OPAMP inverting input is       */
  /*       not used (not connected to GPIO pin).                              */
  if(OPAMP_InitStruct->FunctionalMode != LL_OPAMP_MODE_FOLLOWER)
  {
    assert_param(IS_LL_OPAMP_INPUT_INVERTING(OPAMPx, OPAMP_InitStruct->InputInverting));
  }
  
  /* Configuration of OPAMP instance :                                        */
  /*  - PowerMode                                                             */
  /*  - Functional mode                                                       */
  /*  - Input non-inverting                                                   */
  /*  - Input inverting                                                       */
  /* Note: Bits OPAMP_CSR_OPAxCAL_y reset to ensure to be in functional mode  */
  if(OPAMP_InitStruct->FunctionalMode != LL_OPAMP_MODE_FOLLOWER)
  {
    MODIFY_REG(OPAMP->CSR,
               ((
                   OPAMP_CSR_OPA1LPM
                 | OPAMP_CSR_S3SEL1
                 | OPAMP_CSR_OPA1CAL_H
                 | OPAMP_CSR_OPA1CAL_L
                 | OPAMP_CSR_S5SEL1
                 | OPAMP_CSR_S6SEL1
                 | OPAMP_CSR_S4SEL1
                ) << __OPAMP_INSTANCE_BITOFFSET(OPAMPx)
               )
               | ((OPAMP_CSR_ANAWSEL1) << __OPAMP_INSTANCE_DECIMAL(OPAMPx))
               | (OPAMP_CSR_S7SEL2 * __OPAMP_IS_INSTANCE_OPAMP2(OPAMPx))
              ,
               ((
                   (OPAMP_InitStruct->PowerMode & OPAMP_POWERMODE_CSR_BIT_MASK)
                 | OPAMP_InitStruct->FunctionalMode
                 | OPAMP_InitStruct->InputNonInverting
                 | (OPAMP_InitStruct->InputInverting & OPAMP_CSR_S4SEL1)
                ) << __OPAMP_INSTANCE_BITOFFSET(OPAMPx)
               )
               | ((OPAMP_InitStruct->InputInverting & OPAMP_CSR_ANAWSEL1) << __OPAMP_INSTANCE_DECIMAL(OPAMPx))
               | ((OPAMP_InitStruct->InputNonInverting & OPAMP_CSR_S7SEL2) * __OPAMP_IS_INSTANCE_OPAMP2(OPAMPx))
              );
  }
  else
  {
    MODIFY_REG(OPAMP->CSR,
               ((
                   OPAMP_CSR_OPA1LPM
                 | OPAMP_CSR_OPA1CAL_H
                 | OPAMP_CSR_OPA1CAL_L
                 | OPAMP_CSR_S5SEL1
                 | OPAMP_CSR_S6SEL1
                 | OPAMP_CSR_S4SEL1
                ) << __OPAMP_INSTANCE_BITOFFSET(OPAMPx)
               )
               | ((OPAMP_CSR_ANAWSEL1) << __OPAMP_INSTANCE_DECIMAL(OPAMPx))
               | (OPAMP_CSR_S7SEL2 * __OPAMP_IS_INSTANCE_OPAMP2(OPAMPx))
              ,
               ((
                   (OPAMP_InitStruct->PowerMode & OPAMP_POWERMODE_CSR_BIT_MASK)
                 | OPAMP_InitStruct->FunctionalMode
                 | OPAMP_InitStruct->InputNonInverting
                 | OPAMP_CSR_S3SEL1
                ) << __OPAMP_INSTANCE_BITOFFSET(OPAMPx)
               )
               | ((OPAMP_InitStruct->InputNonInverting & OPAMP_CSR_S7SEL2) * __OPAMP_IS_INSTANCE_OPAMP2(OPAMPx))
              );
  }
  return SUCCESS;
}

/**
  * @brief Set each @ref LL_OPAMP_InitTypeDef field to default value.
  * @param OPAMP_InitStruct pointer to a @ref LL_OPAMP_InitTypeDef structure
  *                         whose fields will be set to default values.
  * @retval None
  */
void LL_OPAMP_StructInit(LL_OPAMP_InitTypeDef *OPAMP_InitStruct)
{
  /* Set OPAMP_InitStruct fields to default values */
  OPAMP_InitStruct->PowerMode         = LL_OPAMP_POWERMODE_NORMAL;
  OPAMP_InitStruct->FunctionalMode    = LL_OPAMP_MODE_FOLLOWER;
  OPAMP_InitStruct->InputNonInverting = LL_OPAMP_INPUT_NONINVERT_IO0;
  /* Note: Parameter discarded if OPAMP in functional mode follower,          */
  /*       set anyway to its default value.                                   */
  OPAMP_InitStruct->InputInverting    = LL_OPAMP_INPUT_INVERT_CONNECT_NO;
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

#endif /* OPAMP1 || OPAMP2 || OPAMP3 */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
