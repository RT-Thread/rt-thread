/**
  ******************************************************************************
  * @file    at32f4xx_comp.h
  * @author  Artery
  * @version V1.0.1
  * @date    20-April-2012
  * @brief   This file contains all the functions prototypes for the COMP firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 Artery</center></h2>
  *
  * Licensed under Artery Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4XX_COMP_H
#define __AT32F4XX_COMP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup AT32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup COMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  COMP Init structure definition  
  */
  
typedef struct
{

  uint32_t COMP_INMInput;     /*!< Selects the inverting input of the comparator.
                                          This parameter can be a value of @ref COMP_INMInput */

  uint32_t COMP_Output;             /*!< Selects the output redirection of the comparator.
                                          This parameter can be a value of @ref COMP_Output */

  uint32_t COMP_OutPolarity;           /*!< Selects the output polarity of the comparator.
                                          This parameter can be a value of @ref COMP_OutputPolarity */

  uint32_t COMP_Hysteresis;         /*!< Selects the hysteresis voltage of the comparator.
                                          This parameter can be a value of @ref COMP_Hysteresis */

  uint32_t COMP_Mode;               /*!< Selects the operating mode of the comparator
                                         and allows to adjust the speed/consumption.
                                          This parameter can be a value of @ref COMP_Mode */

}COMP_InitType;

/* Exported constants --------------------------------------------------------*/
   
/** @defgroup COMP_Exported_Constants
  * @{
  */ 

/** @defgroup COMP_Selection
  * @{
  */

#define COMP1_Selection                    ((uint32_t)0x00000000) /*!< COMP1 Selection */
#define COMP2_Selection                    ((uint32_t)0x00000010) /*!< COMP2 Selection */

#define IS_COMP_ALL_PERIPH(PERIPH) (((PERIPH) == COMP1_Selection) || \
                                    ((PERIPH) == COMP2_Selection))
 
/**
  * @}
  */ 

/** @defgroup COMP_NonInvertingInput
  * @{
  */

#define COMP_INPInput_00               ((uint32_t)0x00000000) /*!< PA5/PA7 connected to comparator1/2 non-inverting input */
#define COMP_INPInput_01               ((uint32_t)0x00000001) /*!< PA1/PA3 connected to comparator1/2 non-inverting input */
#define COMP_INPInput_10               ((uint32_t)0x00000002) /*!< PA0/PA2 connected to comparator1/2 non-inverting input */

#define IS_COMP_NONINVERTING_INPUT(INPUT) (((INPUT) == COMP_INPInput_00) || \
                                          ((INPUT) == COMP_INPInput_01) || \
                                          ((INPUT) == COMP_INPInput_10))

/** @defgroup COMP_InvertingInput
  * @{
  */

#define COMP_INMInput_1_4VREFINT          ((uint32_t)0x00000000) /*!< 1/4 VREFINT connected to comparator inverting input */
#define COMP_INMInput_1_2VREFINT          ((uint32_t)0x00000010) /*!< 1/2 VREFINT connected to comparator inverting input */
#define COMP_INMInput_3_4VREFINT          ((uint32_t)0x00000020) /*!< 3/4 VREFINT connected to comparator inverting input */
#define COMP_INMInput_VREFINT             ((uint32_t)0x00000030) /*!< VREFINT connected to comparator inverting input */
#define COMP_INMInput_IN1                 ((uint32_t)0x00000040) /*!< I/O (PA4 for COMP1 and PA3 for COMP2) connected to comparator inverting input */
#define COMP_INMInput_IN2                 ((uint32_t)0x00000050) /*!< I/O (PA5 for COMP1 and PA7 for COMP2) connected to comparator inverting input */
#define COMP_INMInput_IN3                 ((uint32_t)0x00000060) /*!< I/O (PA0 for COMP1 and PA2 for COMP2) connected to comparator inverting input */

#define IS_COMP_INVERTING_INPUT(INPUT) (((INPUT) == COMP_INMInput_1_4VREFINT) || \
                                        ((INPUT) == COMP_INMInput_1_2VREFINT) || \
                                        ((INPUT) == COMP_INMInput_3_4VREFINT) || \
                                        ((INPUT) == COMP_INMInput_VREFINT)    || \
                                        ((INPUT) == COMP_INMInput_IN1)       || \
                                        ((INPUT) == COMP_INMInput_1_4VREFINT) || \
                                        ((INPUT) == COMP_INMInput_IN3))
/**
  * @}
  */ 
  
/** @defgroup COMP_Output
  * @{
  */

#define COMP_Output_None                  ((uint32_t)0x00000000)   /*!< COMP output isn't connected to other peripherals */
#define COMP_Output_TMR1BKIN              ((uint32_t)0x00000100)   /*!< COMP output connected to TIM1 Break Input (BKIN) */
#define COMP_Output_TMR1IC1               ((uint32_t)0x00000200)   /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_Output_TMR1OCREFCLR          ((uint32_t)0x00000300)   /*!< COMP output connected to TIM1 OCREF Clear */
#define COMP_Output_TMR2IC4               ((uint32_t)0x00000400)   /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_Output_TMR2OCREFCLR          ((uint32_t)0x00000500)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_Output_TMR3IC1               ((uint32_t)0x00000600)   /*!< COMP output connected to TIM3 Input Capture 1 */
#define COMP_Output_TMR3OCREFCLR          ((uint32_t)0x00000700)   /*!< COMP output connected to TIM3 OCREF Clear */


#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_Output_None)         || \
                                ((OUTPUT) == COMP_Output_TMR1BKIN)     || \
                                ((OUTPUT) == COMP_Output_TMR1IC1)      || \
                                ((OUTPUT) == COMP_Output_TMR1OCREFCLR) || \
                                ((OUTPUT) == COMP_Output_TMR2IC4)      || \
                                ((OUTPUT) == COMP_Output_TMR2OCREFCLR) || \
                                ((OUTPUT) == COMP_Output_TMR3IC1)      || \
                                ((OUTPUT) == COMP_Output_TMR3OCREFCLR))
/**
  * @}
  */ 

/** @defgroup COMP_OutputPolarity
  * @{
  */
#define COMP_OutPolarity_NonInverted          ((uint32_t)0x00000000)  /*!< COMP output on GPIO isn't inverted */
#define COMP_OutPolarity_Inverted             COMP_CTRLSTS_COMP1POL       /*!< COMP output on GPIO is inverted */

#define IS_COMP_OUTPUT_POL(POL) (((POL) == COMP_OutPolarity_NonInverted)  || \
                                 ((POL) == COMP_OutPolarity_Inverted))

/**
  * @}
  */ 

/** @defgroup COMP_Hysteresis
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the hysteresis level */
#define COMP_Hysteresis_No                         ((uint32_t)0x00000000)   /*!< No hysteresis */
#define COMP_Hysteresis_Low                        COMP_CTRLSTS_COMP1HYST_0 /*!< Hysteresis level low */
#define COMP_Hysteresis_Medium                     COMP_CTRLSTS_COMP1HYST_1 /*!< Hysteresis level medium */
#define COMP_Hysteresis_High                       COMP_CTRLSTS_COMP1HYST   /*!< Hysteresis level high */

#define IS_COMP_HYSTERESIS(HYSTERESIS)    (((HYSTERESIS) == COMP_Hysteresis_No) || \
                                           ((HYSTERESIS) == COMP_Hysteresis_Low) || \
                                           ((HYSTERESIS) == COMP_Hysteresis_Medium) || \
                                           ((HYSTERESIS) == COMP_Hysteresis_High))
/**
  * @}
  */

/** @defgroup COMP_Mode
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the power consumption values */
#define COMP_Mode_Fast                     ((uint32_t)0x00000000)  /*!< High Speed */
#define COMP_Mode_Slow                     COMP_CTRLSTS_COMP1MDE_0 /*!< Low power mode */

#define IS_COMP_MODE(MODE)    (((MODE) == COMP_Mode_Slow)      || \
                               ((MODE) == COMP_Mode_Fast))
/**
  * @}
  */

/** @defgroup COMP_OutputLevel
  * @{
  */ 
/* When output polarity is not inverted, comparator output is high when
   the non-inverting input is at a higher voltage than the inverting input */
#define COMP_OutputState_High                   COMP_CTRLSTS_COMP1OUT
/* When output polarity is not inverted, comparator output is low when
   the non-inverting input is at a lower voltage than the inverting input*/
#define COMP_OutputState_Low                    ((uint32_t)0x00000000)

/**
  * @}
  */ 

/** @defgroup COMP_High_Pulse_Filter
  * @{
  */        
  
#define IS_COMP_HighPulseCnt(HighPulse)          ((HighPulse) <= 0x3F)
/**
  * @}
  */
  
/** @defgroup COMP_Low_Pulse_Filter
  * @{
  */        
  
#define IS_COMP_LowPulseCnt(LowPulse)            ((LowPulse) <= 0x3F)
/**
  * @}
  */
  
/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the COMP configuration to the default reset state ****/
void COMP_Reset(void);

/* Initialization and Configuration functions *********************************/
void COMP_Init(uint32_t COMP_Selection, COMP_InitType* COMP_InitStruct);
void COMP_SelectINPInput(uint32_t COMP_Selection, uint32_t COMP_INPInput);
void COMP_StructInit(COMP_InitType* COMP_InitStruct);
void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState);
void COMP_SwitchCmd(FunctionalState NewState);
uint32_t COMP_GetOutputState(uint32_t COMP_Selection);

/* Window mode control function ***********************************************/
void COMP_WindowCmd(FunctionalState NewState);

/* COMP configuration locking function ****************************************/
void COMP_LockConfig(uint32_t COMP_Selection);

/* COMP configuration glitch filter ****************************************/
void COMP_FilterConfig(uint16_t COMP_HighPulseCnt, uint16_t COMP_LowPulseCnt, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /*__AT32F4xx_COMP_H */

/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT Artery *****END OF FILE****/
