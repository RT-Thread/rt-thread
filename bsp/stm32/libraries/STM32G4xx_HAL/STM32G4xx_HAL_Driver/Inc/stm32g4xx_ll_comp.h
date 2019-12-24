/**
  ******************************************************************************
  * @file    stm32g4xx_ll_comp.h
  * @author  MCD Application Team
  * @brief   Header file of COMP LL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G4xx_LL_COMP_H
#define STM32G4xx_LL_COMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx.h"

/** @addtogroup STM32G4xx_LL_Driver
  * @{
  */



/** @defgroup COMP_LL COMP
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup COMP_LL_ES_INIT COMP Exported Init structure
  * @{
  */

/**
  * @brief  Structure definition of some features of COMP instance.
  */
typedef struct
{
  uint32_t InputPlus;                   /*!< Set comparator input plus (non-inverting input).
                                             This parameter can be a value of @ref COMP_LL_EC_INPUT_PLUS

                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetInputPlus(). */

  uint32_t InputMinus;                  /*!< Set comparator input minus (inverting input).
                                             This parameter can be a value of @ref COMP_LL_EC_INPUT_MINUS

                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetInputMinus(). */

  uint32_t InputHysteresis;             /*!< Set comparator hysteresis mode of the input minus.
                                             This parameter can be a value of @ref COMP_LL_EC_INPUT_HYSTERESIS

                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetInputHysteresis(). */

  uint32_t OutputPolarity;              /*!< Set comparator output polarity.
                                             This parameter can be a value of @ref COMP_LL_EC_OUTPUT_POLARITY

                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetOutputPolarity(). */

  uint32_t OutputBlankingSource;        /*!< Set comparator blanking source.
                                             This parameter can be a value of @ref COMP_LL_EC_OUTPUT_BLANKING_SOURCE

                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetOutputBlankingSource(). */

} LL_COMP_InitTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Constants COMP Exported Constants
  * @{
  */

/** @defgroup COMP_LL_EC_INPUT_PLUS Comparator inputs - Input plus (input non-inverting) selection
  * @{
  */
#define LL_COMP_INPUT_PLUS_IO1          (0x00000000UL)                          /*!< Comparator input plus connected to IO1 (pin PA1 for COMP1, pin PA7 for COMP2, pin PA0 for COMP3, pin PB0 for COMP4, pin PB13 for COMP5, pin PB11 for COMP6, pin PB14 for COMP7). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_INPUT_PLUS_IO2          (COMP_CSR_INPSEL)                       /*!< Comparator input plus connected to IO2 (pin PB1 for COMP1, pin PA3 for COMP2, pin PC1 for COMP3, pin PE7 for COMP4, pin PD12 for COMP5, pin PD11 for COMP6, pin PD14 for COMP7). Note: For COMPx instance availability, please refer to datasheet */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_MINUS Comparator inputs - Input minus (input inverting) selection
  * @{
  */
#define LL_COMP_INPUT_MINUS_1_4VREFINT  (                                                            COMP_CSR_SCALEN | COMP_CSR_BRGEN)        /*!< Comparator input minus connected to 1/4 VrefInt  */
#define LL_COMP_INPUT_MINUS_1_2VREFINT  (                                        COMP_CSR_INMSEL_0 | COMP_CSR_SCALEN | COMP_CSR_BRGEN)        /*!< Comparator input minus connected to 1/2 VrefInt  */
#define LL_COMP_INPUT_MINUS_3_4VREFINT  (                    COMP_CSR_INMSEL_1                     | COMP_CSR_SCALEN | COMP_CSR_BRGEN)        /*!< Comparator input minus connected to 3/4 VrefInt  */
#define LL_COMP_INPUT_MINUS_VREFINT     (                    COMP_CSR_INMSEL_1 | COMP_CSR_INMSEL_0 | COMP_CSR_SCALEN                 )        /*!< Comparator input minus connected to VrefInt */
#define LL_COMP_INPUT_MINUS_DAC1_CH1    (COMP_CSR_INMSEL_2                     | COMP_CSR_INMSEL_0)                                           /*!< Comparator input minus connected to DAC1 Channel 1 for COMP1/3/4. Note: For COMPx & DACx instances availability, please refer to datasheet */
#define LL_COMP_INPUT_MINUS_DAC1_CH2    (COMP_CSR_INMSEL_2                     | COMP_CSR_INMSEL_0)                                           /*!< Comparator input minus connected to DAC1 Channel 2 for COMP2/5. Note: For COMPx & DACx instances availability, please refer to datasheet */
#define LL_COMP_INPUT_MINUS_DAC2_CH1    (COMP_CSR_INMSEL_2                     | COMP_CSR_INMSEL_0)                                           /*!< Comparator input minus connected to DAC2 Channel 1 for COMP6/7. Note: For COMPx & DACx instances availability, please refer to datasheet */
#define LL_COMP_INPUT_MINUS_DAC3_CH1    (COMP_CSR_INMSEL_2                                        )                                           /*!< Comparator input minus connected to DAC3 Channel 1 for COMP1/3. Note: For COMPx & DACx instances availability, please refer to datasheet */
#define LL_COMP_INPUT_MINUS_DAC3_CH2    (COMP_CSR_INMSEL_2                                        )                                           /*!< Comparator input minus connected to DAC3 Channel 2 for COMP2/4. Note: For COMPx & DACx instances availability, please refer to datasheet */
#define LL_COMP_INPUT_MINUS_DAC4_CH1    (COMP_CSR_INMSEL_2                                        )                                           /*!< Comparator input minus connected to DAC4 Channel 1 for COMP5/7. Note: For COMPx & DACx instances availability, please refer to datasheet */
#define LL_COMP_INPUT_MINUS_DAC4_CH2    (COMP_CSR_INMSEL_2                                        )                                           /*!< Comparator input minus connected to DAC4 Channel 2 for COMP6. Note: For COMPx & DACx instances availability, please refer to datasheet */
#define LL_COMP_INPUT_MINUS_IO1         (COMP_CSR_INMSEL_2 | COMP_CSR_INMSEL_1                    )                                           /*!< Comparator input minus connected to IO1 (pin PA4 for COMP1, pin PA5 for COMP2, pin PF1 for COMP3, pin PE8 for COMP4, pin PB10 for COMP5, pin PD10 for COMP6, pin PD15 for COMP7). Note: For COMPx instance availability, please refer to datasheet */ 
#define LL_COMP_INPUT_MINUS_IO2         (COMP_CSR_INMSEL_2 | COMP_CSR_INMSEL_1 | COMP_CSR_INMSEL_0)                                           /*!< Comparator input minus connected to IO2 (pin PA0 for COMP1, pin PA2 for COMP2, pin PC0 for COMP3, pin PB2 for COMP4, pin PD13 for COMP5, pin PB15 for COMP6, pin PB12 for COMP7). Note: For COMPx instance availability, please refer to datasheet */

/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_HYSTERESIS Comparator input - Hysteresis
  * @{
  */
#define LL_COMP_HYSTERESIS_NONE         (0x00000000UL)                                       /*!< No hysteresis */
#define LL_COMP_HYSTERESIS_10MV         (                                    COMP_CSR_HYST_0) /*!< Hysteresis level 10mV */
#define LL_COMP_HYSTERESIS_20MV         (                  COMP_CSR_HYST_1                  ) /*!< Hysteresis level 20mV */
#define LL_COMP_HYSTERESIS_30MV         (                  COMP_CSR_HYST_1 | COMP_CSR_HYST_0) /*!< Hysteresis level 30mV */
#define LL_COMP_HYSTERESIS_40MV         (COMP_CSR_HYST_2                                    ) /*!< Hysteresis level 40mV */
#define LL_COMP_HYSTERESIS_50MV         (COMP_CSR_HYST_2                   | COMP_CSR_HYST_0) /*!< Hysteresis level 50mV */
#define LL_COMP_HYSTERESIS_60MV         (COMP_CSR_HYST_2 | COMP_CSR_HYST_1                  ) /*!< Hysteresis level 60mV */
#define LL_COMP_HYSTERESIS_70MV         (COMP_CSR_HYST_2 | COMP_CSR_HYST_1 | COMP_CSR_HYST_0) /*!< Hysteresis level 70mV */
#define LL_COMP_HYSTERESIS_LOW          LL_COMP_HYSTERESIS_10MV /*!< Hysteresis level low */
#define LL_COMP_HYSTERESIS_MEDIUM       LL_COMP_HYSTERESIS_40MV /*!< Hysteresis level medium */
#define LL_COMP_HYSTERESIS_HIGH         LL_COMP_HYSTERESIS_70MV /*!< Hysteresis level high */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_POLARITY Comparator output - Output polarity
  * @{
  */
#define LL_COMP_OUTPUTPOL_NONINVERTED   (0x00000000UL)          /*!< COMP output polarity is not inverted: comparator output is high when the plus (non-inverting) input is at a higher voltage than the minus (inverting) input */
#define LL_COMP_OUTPUTPOL_INVERTED      (COMP_CSR_POLARITY)     /*!< COMP output polarity is inverted: comparator output is low when the plus (non-inverting) input is at a lower voltage than the minus (inverting) input */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_BLANKING_SOURCE Comparator output - Blanking source
  * @{
  */
#define LL_COMP_BLANKINGSRC_NONE            (0x00000000UL)          /*!<Comparator output without blanking */
#define LL_COMP_BLANKINGSRC_TIM1_OC5_COMP1  (                                            COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM1 OC5 (specific to COMP instance: COMP1). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM1_OC5_COMP2  (                                            COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM1 OC5 (specific to COMP instance: COMP2). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM1_OC5_COMP3  (                                            COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM1 OC5 (specific to COMP instance: COMP3). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM1_OC5_COMP4  (COMP_CSR_BLANKING_2                                            )   /*!< Comparator output blanking source TIM1 OC5 (specific to COMP instance: COMP4). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM1_OC5_COMP5  (COMP_CSR_BLANKING_2                                            )   /*!< Comparator output blanking source TIM1 OC5 (specific to COMP instance: COMP5). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM1_OC5_COMP6  (COMP_CSR_BLANKING_2                                            )   /*!< Comparator output blanking source TIM1 OC5 (specific to COMP instance: COMP6). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM1_OC5_COMP7  (                                            COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM1 OC5 (specific to COMP instance: COMP7). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM2_OC3_COMP1  (                      COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM2 OC3 (specific to COMP instance: COMP1). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM2_OC3_COMP2  (                      COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM2 OC3 (specific to COMP instance: COMP2). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM2_OC3_COMP5  (                                            COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM2 OC3 (specific to COMP instance: COMP5). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM2_OC4_COMP3  (                      COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM2 OC4 (specific to COMP instance: COMP3). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM2_OC4_COMP6  (                      COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM2 OC4 (specific to COMP instance: COMP6). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM3_OC3_COMP1  (                      COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM3 OC3 (specific to COMP instance: COMP1). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM3_OC3_COMP2  (                      COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM3 OC3 (specific to COMP instance: COMP2). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM3_OC3_COMP3  (                      COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM3 OC3 (specific to COMP instance: COMP3). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM3_OC3_COMP5  (                      COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM3 OC3 (specific to COMP instance: COMP5). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM3_OC3_COMP7  (                      COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM3 OC3 (specific to COMP instance: COMP7). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM3_OC4_COMP4  (                                            COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM3 OC4 (specific to COMP instance: COMP4). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM8_OC5_COMP1  (COMP_CSR_BLANKING_2                                            )   /*!< Comparator output blanking source TIM8 OC5 (specific to COMP instance: COMP1). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM8_OC5_COMP2  (COMP_CSR_BLANKING_2                                            )   /*!< Comparator output blanking source TIM8 OC5 (specific to COMP instance: COMP2). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM8_OC5_COMP3  (COMP_CSR_BLANKING_2                                            )   /*!< Comparator output blanking source TIM8 OC5 (specific to COMP instance: COMP3). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM8_OC5_COMP4  (                      COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM8 OC5 (specific to COMP instance: COMP4). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM8_OC5_COMP5  (                      COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM8 OC5 (specific to COMP instance: COMP5). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM8_OC5_COMP6  (                                            COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM8 OC5 (specific to COMP instance: COMP6). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM8_OC5_COMP7  (                      COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM8 OC5 (specific to COMP instance: COMP7). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM15_OC1_COMP4 (                      COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM15 OC1 (specific to COMP instance: COMP4). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM15_OC2_COMP6 (                      COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM15 OC2 (specific to COMP instance: COMP6). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM15_OC2_COMP7 (COMP_CSR_BLANKING_2                                            )   /*!< Comparator output blanking source TIM15 OC3 (specific to COMP instance: COMP7). Note: For COMPx instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM20_OC5       (COMP_CSR_BLANKING_2 |                       COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM20 OC5 (Common to all COMP instances). Note: For TIM20 instance availability, please refer to datasheet */
#define LL_COMP_BLANKINGSRC_TIM15_OC1       (COMP_CSR_BLANKING_2 | COMP_CSR_BLANKING_1                      )   /*!< Comparator output blanking source TIM15 OC1 (Common to all COMP instances). */
#define LL_COMP_BLANKINGSRC_TIM4_OC3        (COMP_CSR_BLANKING_2 | COMP_CSR_BLANKING_1 | COMP_CSR_BLANKING_0)   /*!< Comparator output blanking source TIM4 OC3 (Common to all COMP instances). */

/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_LEVEL Comparator output - Output level
  * @{
  */
#define LL_COMP_OUTPUT_LEVEL_LOW        (0x00000000UL)          /*!< Comparator output level low (if the polarity is not inverted, otherwise to be complemented) */
#define LL_COMP_OUTPUT_LEVEL_HIGH       (0x00000001UL)          /*!< Comparator output level high (if the polarity is not inverted, otherwise to be complemented) */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_HW_DELAYS  Definitions of COMP hardware constraints delays
  * @note   Only COMP peripheral HW delays are defined in COMP LL driver driver,
  *         not timeout values.
  *         For details on delays values, refer to descriptions in source code
  *         above each literal definition.
  * @{
  */

/* Delay for comparator startup time.                                         */
/* Note: Delay required to reach propagation delay specification.             */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART").                                                       */
/* Unit: us                                                                   */
#define LL_COMP_DELAY_STARTUP_US          (  5UL) /*!< Delay for COMP startup time */

/* Delay for comparator voltage scaler stabilization time.                    */
/* Note: Voltage scaler is used when selecting comparator input               */
/*       based on VrefInt: VrefInt or subdivision of VrefInt.                 */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART_SCALER").                                                */
/* Unit: us                                                                   */
#define LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US ( 200UL) /*!< Delay for COMP voltage scaler stabilization time */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Macros COMP Exported Macros
  * @{
  */
/** @defgroup COMP_LL_EM_WRITE_READ Common write and read registers macro
  * @{
  */

/**
  * @brief  Write a value in COMP register
  * @param  __INSTANCE__ comparator instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_COMP_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG((__INSTANCE__)->__REG__, (__VALUE__))

/**
  * @brief  Read a value in COMP register
  * @param  __INSTANCE__ comparator instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_COMP_ReadReg(__INSTANCE__, __REG__) READ_REG((__INSTANCE__)->__REG__)
/**
  * @}
  */

/** @defgroup COMP_LL_EM_HELPER_MACRO COMP helper macro
  * @{
  */

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Functions COMP Exported Functions
  * @{
  */

/** @defgroup COMP_LL_EF_Configuration_comparator_inputs Configuration of comparator inputs
  * @{
  */

/**
  * @brief  Set comparator inputs minus (inverting) and plus (non-inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @note   On this STM32 serie, scaler bridge is configurable:
  *         to optimize power consumption, this function enables the
  *         voltage scaler bridge only when required
  *         (when selecting comparator input based on VrefInt: VrefInt or
  *         subdivision of VrefInt).
  *         - For scaler bridge power consumption values,
  *           refer to device datasheet, parameter "IDDA(SCALER)".
  *         - Voltage scaler requires a delay for voltage stabilization.
  *           Refer to device datasheet, parameter "tSTART_SCALER".
  *         - Scaler bridge is common for all comparator instances,
  *           therefore if at least one of the comparator instance
  *           is requiring the scaler bridge, it remains enabled.
  * @rmtoll CSR      INMSEL         LL_COMP_ConfigInputs\n
  *         CSR      INPSEL         LL_COMP_ConfigInputs\n
  *         CSR      BRGEN          LL_COMP_ConfigInputs\n
  *         CSR      SCALEN         LL_COMP_ConfigInputs
  * @param  COMPx Comparator instance
  * @param  InputMinus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_1_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_2VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_3_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH1   (1,3,4)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH2   (2,5)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC2_CH1   (6,7)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC3_CH1   (1,3)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC3_CH2   (2,4)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC4_CH1   (5,7)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC4_CH2   (6)
  *         (a,b...) Only available for COMPa, COMPb...
  *                  For COMPx & DACx instances availability, please refer to datasheet
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  * @param  InputPlus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  * @retval None
  */
__STATIC_INLINE void LL_COMP_ConfigInputs(COMP_TypeDef *COMPx, uint32_t InputMinus, uint32_t InputPlus)
{
  MODIFY_REG(COMPx->CSR,
             COMP_CSR_INMSEL | COMP_CSR_INPSEL | COMP_CSR_SCALEN | COMP_CSR_BRGEN,
             InputMinus | InputPlus);
}

/**
  * @brief  Set comparator input plus (non-inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll CSR      INPSEL         LL_COMP_SetInputPlus
  * @param  COMPx Comparator instance
  * @param  InputPlus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetInputPlus(COMP_TypeDef *COMPx, uint32_t InputPlus)
{
  MODIFY_REG(COMPx->CSR, COMP_CSR_INPSEL, InputPlus);
}

/**
  * @brief  Get comparator input plus (non-inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll CSR      INPSEL         LL_COMP_GetInputPlus
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputPlus(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CSR, COMP_CSR_INPSEL));
}

/**
  * @brief  Set comparator input minus (inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @note   On this STM32 serie, scaler bridge is configurable:
  *         to optimize power consumption, this function enables the
  *         voltage scaler bridge only when required
  *         (when selecting comparator input based on VrefInt: VrefInt or
  *         subdivision of VrefInt).
  *         - For scaler bridge power consumption values,
  *           refer to device datasheet, parameter "IDDA(SCALER)".
  *         - Voltage scaler requires a delay for voltage stabilization.
  *           Refer to device datasheet, parameter "tSTART_SCALER".
  *         - Scaler bridge is common for all comparator instances,
  *           therefore if at least one of the comparator instance
  *           is requiring the scaler bridge, it remains enabled.
  * @rmtoll CSR      INMSEL         LL_COMP_SetInputMinus\n
  *         CSR      BRGEN          LL_COMP_SetInputMinus\n
  *         CSR      SCALEN         LL_COMP_SetInputMinus
  * @param  COMPx Comparator instance
  * @param  InputMinus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_1_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_2VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_3_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH1   (1,3,4)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH2   (2,5)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC2_CH1   (6,7)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC3_CH1   (1,3)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC3_CH2   (2,4)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC4_CH1   (5,7)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC4_CH2   (6)
  *         (a,b...) Only available for COMPa, COMPb...
  *                  For COMPx & DACx instances availability, please refer to datasheet
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetInputMinus(COMP_TypeDef *COMPx, uint32_t InputMinus)
{
  MODIFY_REG(COMPx->CSR, COMP_CSR_INMSEL | COMP_CSR_SCALEN | COMP_CSR_BRGEN, InputMinus);
}

/**
  * @brief  Get comparator input minus (inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll CSR      INMSEL         LL_COMP_GetInputMinus\n
  *         CSR      BRGEN          LL_COMP_GetInputMinus\n
  *         CSR      SCALEN         LL_COMP_GetInputMinus
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_1_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_2VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_3_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH1   (1,3,4)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH2   (2,5)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC2_CH1   (6,7)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC3_CH1   (1,3)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC3_CH2   (2,4)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC4_CH1   (5,7)
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC4_CH2   (6)
  *         (a,b...) Only available for COMPa, COMPb...
  *                  For COMPx & DACx instances availability, please refer to datasheet
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputMinus(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CSR, COMP_CSR_INMSEL | COMP_CSR_SCALEN | COMP_CSR_BRGEN));
}

/**
  * @brief  Set comparator instance hysteresis mode of the input minus (inverting input).
  * @rmtoll CSR      HYST           LL_COMP_SetInputHysteresis
  * @param  COMPx Comparator instance
  * @param  InputHysteresis This parameter can be one of the following values:
  *         @arg @ref LL_COMP_HYSTERESIS_NONE
  *         @arg @ref LL_COMP_HYSTERESIS_10MV
  *         @arg @ref LL_COMP_HYSTERESIS_20MV
  *         @arg @ref LL_COMP_HYSTERESIS_30MV
  *         @arg @ref LL_COMP_HYSTERESIS_40MV
  *         @arg @ref LL_COMP_HYSTERESIS_50MV
  *         @arg @ref LL_COMP_HYSTERESIS_60MV
  *         @arg @ref LL_COMP_HYSTERESIS_70MV
  *         @arg @ref LL_COMP_HYSTERESIS_LOW
  *         @arg @ref LL_COMP_HYSTERESIS_MEDIUM
  *         @arg @ref LL_COMP_HYSTERESIS_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetInputHysteresis(COMP_TypeDef *COMPx, uint32_t InputHysteresis)
{
  MODIFY_REG(COMPx->CSR, COMP_CSR_HYST, InputHysteresis);
}

/**
  * @brief  Get comparator instance hysteresis mode of the minus (inverting) input.
  * @rmtoll CSR      HYST           LL_COMP_GetInputHysteresis
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_HYSTERESIS_NONE
  *         @arg @ref LL_COMP_HYSTERESIS_10MV
  *         @arg @ref LL_COMP_HYSTERESIS_20MV
  *         @arg @ref LL_COMP_HYSTERESIS_30MV
  *         @arg @ref LL_COMP_HYSTERESIS_40MV
  *         @arg @ref LL_COMP_HYSTERESIS_50MV
  *         @arg @ref LL_COMP_HYSTERESIS_60MV
  *         @arg @ref LL_COMP_HYSTERESIS_70MV
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputHysteresis(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CSR, COMP_CSR_HYST));
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_Configuration_comparator_output Configuration of comparator output
  * @{
  */

/**
  * @brief  Set comparator instance output polarity.
  * @rmtoll CSR      POLARITY       LL_COMP_SetOutputPolarity
  * @param  COMPx Comparator instance
  * @param  OutputPolarity This parameter can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUTPOL_NONINVERTED
  *         @arg @ref LL_COMP_OUTPUTPOL_INVERTED
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetOutputPolarity(COMP_TypeDef *COMPx, uint32_t OutputPolarity)
{
  MODIFY_REG(COMPx->CSR, COMP_CSR_POLARITY, OutputPolarity);
}

/**
  * @brief  Get comparator instance output polarity.
  * @rmtoll CSR      POLARITY       LL_COMP_GetOutputPolarity
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUTPOL_NONINVERTED
  *         @arg @ref LL_COMP_OUTPUTPOL_INVERTED
  */
__STATIC_INLINE uint32_t LL_COMP_GetOutputPolarity(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CSR, COMP_CSR_POLARITY));
}

/**
  * @brief  Set comparator instance blanking source.
  * @note   Blanking source may be specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @note   Availability of parameters of blanking source from timer
  *         depends on timers availability on the selected device.
  * @rmtoll CSR      BLANKING       LL_COMP_SetOutputBlankingSource
  * @param  COMPx Comparator instance
  * @param  BlankingSource This parameter can be one of the following values:
  *         @arg @ref LL_COMP_BLANKINGSRC_NONE
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5_COMP1
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5_COMP2
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5_COMP3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5_COMP4
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5_COMP5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5_COMP6
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5_COMP7
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC3_COMP1
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC3_COMP2
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC3_COMP5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC4_COMP3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC4_COMP6
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC3_COMP1
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC3_COMP2
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC3_COMP3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC3_COMP5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC3_COMP7
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC4_COMP4
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5_COMP1
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5_COMP2
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5_COMP3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5_COMP4
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5_COMP5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5_COMP6
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5_COMP7
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM15_OC1_COMP4
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM15_OC2_COMP6
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM15_OC2_COMP7
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM20_OC5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM15_OC1
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM4_OC3
  *
  *         On STM32G4 series, blanking sources are linked to COMP instance (except
  *         those without COMPx suffix that are common to all instances)
  *         Note: For COMPx & TIMx instances availability, please refer to datasheet
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetOutputBlankingSource(COMP_TypeDef *COMPx, uint32_t BlankingSource)
{
  MODIFY_REG(COMPx->CSR, COMP_CSR_BLANKING, BlankingSource);
}

/**
  * @brief  Get comparator instance blanking source.
  * @note   Availability of parameters of blanking source from timer
  *         depends on timers availability on the selected device.
  * @note   Blanking source may be specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll CSR      BLANKING       LL_COMP_GetOutputBlankingSource
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_BLANKINGSRC_NONE
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5_COMP1
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5_COMP2
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5_COMP3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5_COMP4
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5_COMP5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5_COMP6
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5_COMP7
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC3_COMP1
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC3_COMP2
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC3_COMP5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC4_COMP3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC4_COMP6
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC3_COMP1
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC3_COMP2
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC3_COMP3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC3_COMP5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC3_COMP7
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC4_COMP4
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5_COMP1
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5_COMP2
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5_COMP3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5_COMP4
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5_COMP5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5_COMP6
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5_COMP7
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM15_OC1_COMP4
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM15_OC2_COMP6
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM15_OC2_COMP7
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM20_OC5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM15_OC1
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM4_OC3
  *
  *         On STM32G4 series, blanking sources are linked to COMP instance (except
  *         those without COMPx suffix that are common to all instances)
  *         Note: For COMPx & TIMx instances availability, please refer to datasheet
  */
__STATIC_INLINE uint32_t LL_COMP_GetOutputBlankingSource(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CSR, COMP_CSR_BLANKING));
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_Operation Operation on comparator instance
  * @{
  */

/**
  * @brief  Enable comparator instance.
  * @note   After enable from off state, comparator requires a delay
  *         to reach reach propagation delay specification.
  *         Refer to device datasheet, parameter "tSTART".
  * @rmtoll CSR      EN             LL_COMP_Enable
  * @param  COMPx Comparator instance
  * @retval None
  */
__STATIC_INLINE void LL_COMP_Enable(COMP_TypeDef *COMPx)
{
  SET_BIT(COMPx->CSR, COMP_CSR_EN);
}

/**
  * @brief  Disable comparator instance.
  * @rmtoll CSR      EN             LL_COMP_Disable
  * @param  COMPx Comparator instance
  * @retval None
  */
__STATIC_INLINE void LL_COMP_Disable(COMP_TypeDef *COMPx)
{
  CLEAR_BIT(COMPx->CSR, COMP_CSR_EN);
}

/**
  * @brief  Get comparator enable state
  *         (0: COMP is disabled, 1: COMP is enabled)
  * @rmtoll CSR      EN             LL_COMP_IsEnabled
  * @param  COMPx Comparator instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_COMP_IsEnabled(COMP_TypeDef *COMPx)
{
  return ((READ_BIT(COMPx->CSR, COMP_CSR_EN) == (COMP_CSR_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Lock comparator instance.
  * @note   Once locked, comparator configuration can be accessed in read-only.
  * @note   The only way to unlock the comparator is a device hardware reset.
  * @rmtoll CSR      LOCK           LL_COMP_Lock
  * @param  COMPx Comparator instance
  * @retval None
  */
__STATIC_INLINE void LL_COMP_Lock(COMP_TypeDef *COMPx)
{
  SET_BIT(COMPx->CSR, COMP_CSR_LOCK);
}

/**
  * @brief  Get comparator lock state
  *         (0: COMP is unlocked, 1: COMP is locked).
  * @note   Once locked, comparator configuration can be accessed in read-only.
  * @note   The only way to unlock the comparator is a device hardware reset.
  * @rmtoll CSR      LOCK           LL_COMP_IsLocked
  * @param  COMPx Comparator instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_COMP_IsLocked(COMP_TypeDef *COMPx)
{
  return ((READ_BIT(COMPx->CSR, COMP_CSR_LOCK) == (COMP_CSR_LOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Read comparator instance output level.
  * @note   On this STM32 serie, comparator 'value' is taken before
  *         polarity and blanking are applied, thus:
  *          - Comparator output is low when the input plus
  *            is at a lower voltage than the input minus
  *          - Comparator output is high when the input plus
  *            is at a higher voltage than the input minus
  * @rmtoll CSR      VALUE          LL_COMP_ReadOutputLevel
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUT_LEVEL_LOW
  *         @arg @ref LL_COMP_OUTPUT_LEVEL_HIGH
  */
__STATIC_INLINE uint32_t LL_COMP_ReadOutputLevel(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CSR, COMP_CSR_VALUE)
                    >> COMP_CSR_VALUE_Pos);
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup COMP_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus LL_COMP_DeInit(COMP_TypeDef *COMPx);
ErrorStatus LL_COMP_Init(COMP_TypeDef *COMPx, LL_COMP_InitTypeDef *COMP_InitStruct);
void        LL_COMP_StructInit(LL_COMP_InitTypeDef *COMP_InitStruct);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

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

#endif /* STM32G4xx_LL_COMP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
