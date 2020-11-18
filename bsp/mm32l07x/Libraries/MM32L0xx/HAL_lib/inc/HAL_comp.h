/**
******************************************************************************
* @file    HAL_comp.h
* @author  AE Team
* @version  V2.0.0
* @date  22/08/2017
* @brief   This file contains all the functions prototypes for the COMP firmware 
*          library.
******************************************************************************
* @attention
*
* <h2><center>&copy; 2017 MindMotion</center></h2>
******************************************************************************
*/ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_COMP_H
#define __HAL_COMP_H

#ifdef __cplusplus
extern "C" {
#endif
  
  /* Includes ------------------------------------------------------------------*/
#include "HAL_device.h"
  
  /** @addtogroup 
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
    
    uint32_t COMP_InvertingInput;     /*!< Selects the inverting input of the comparator.
    This parameter can be a value of @ref COMP_InvertingInput */
    
    uint32_t COMP_NonInvertingInput;  /*!< Selects the non inverting input of the comparator.
    This parameter can be a value of @ref COMP_NonInvertingInput */
    
    uint32_t COMP_Output;             /*!< Selects the output redirection of the comparator.
    This parameter can be a value of @ref COMP_Output */
    
    uint32_t COMP_BlankingSrce;      /*!< Selects the output blanking source of the comparator.
    This parameter can be a value of @ref COMP_BlankingSrce */
    
    uint32_t COMP_OutputPol;           /*!< Selects the output polarity of the comparator.
    This parameter can be a value of @ref COMP_OutputPoloarity */
    
    uint32_t COMP_Hysteresis;         /*!< Selects the hysteresis voltage of the comparator.
    This parameter can be a value of @ref COMP_Hysteresis */
    
    uint32_t COMP_Mode;               /*!< Selects the operating mode of the comparator
    and allows to adjust the speed/consumption.
    This parameter can be a value of @ref COMP_Mode */
    
  }COMP_InitTypeDef;
  
  /* Exported constants --------------------------------------------------------*/
  
  /** @defgroup COMP_Exported_Constants
  * @{
  */ 
  
  /** @defgroup COMP_Selection
  * @{
  */
  
#define COMP_Selection_COMP1                    ((uint32_t)0x00000000) /*!< COMP1 Selection */
#define COMP_Selection_COMP2                    ((uint32_t)0x00000004) /*!< COMP2 Selection */
  
  
#define IS_COMP_ALL_PERIPH(PERIPH) (((PERIPH) == COMP_Selection_COMP1) || \
  ((PERIPH) == COMP_Selection_COMP2))

/**
* @}
*/ 

/** @defgroup COMP_InvertingInput
* @{
*/

#define COMP_InvertingInput_1_4VREFINT          ((uint32_t)0x00000000) /*!< 1/4 VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_1_2VREFINT          ((uint32_t)0x00000010) /*!< 1/2 VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_3_4VREFINT          ((uint32_t)0x00000020) /*!< 3/4 VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_VREFINT             ((uint32_t)0x00000030) /*!< VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_DAC1                ((uint32_t)0x00000040) /*!< DAC1_OUT (PA4) connected to comparator inverting input */
#define COMP_InvertingInput_DAC2                ((uint32_t)0x00000050) /*!< DAC2_OUT (PA5) connected to comparator inverting input */
#define COMP_InvertingInput_IO1                 ((uint32_t)0x00000060) /*!< I/O1 (PA0 for COMP1, PA2 for COMP2) connected to comparator inverting input */
#define COMP_InvertingInput_IO2                 ((uint32_t)0x00000070) /*!< I/O2 (PA6 for COMP1, PA6 for COMP2) connected to comparator inverting input */


#define IS_COMP_INVERTING_INPUT(INPUT) (((INPUT) == COMP_InvertingInput_1_4VREFINT) || \
((INPUT) == COMP_InvertingInput_1_2VREFINT) || \
  ((INPUT) == COMP_InvertingInput_3_4VREFINT) || \
    ((INPUT) == COMP_InvertingInput_VREFINT)    || \
      ((INPUT) == COMP_InvertingInput_DAC1)       || \
        ((INPUT) == COMP_InvertingInput_DAC2)       || \
          ((INPUT) == COMP_InvertingInput_IO1)        || \
            ((INPUT) == COMP_InvertingInput_IO2))
/**
* @}
*/ 

/** @defgroup COMP_NonInvertingInput
* @{
*/

#define COMP_NonInvertingInput_IO1                 ((uint32_t)0x00000000) /*!< I/O1 (PA0 for COMP1, PA0 for COMP2) connected to comparator non inverting input */

#define COMP_NonInvertingInput_IO2                 ((uint32_t)0x00000080) /*!< I/O2 (PA1 for COMP1, PA1 for COMP2) connected to comparator non inverting input */

#define COMP_NonInvertingInput_IO3                 ((uint32_t)0x00000100) /*!< I/O2 (PA2 for COMP1, PA2 for COMP2) connected to comparator non inverting input */

#define COMP_NonInvertingInput_IO4                 ((uint32_t)0x00000180) /*!< I/O2 (PA3 for COMP1, PA3 for COMP2) connected to comparator non inverting input */

#define COMP_NonInvertingInput_IO5                 ((uint32_t)0x00000200) /*!< I/O2 (PA4 for COMP1, PA4 for COMP2) connected to comparator non inverting input */

#define COMP_NonInvertingInput_IO6                 ((uint32_t)0x00000280) /*!< I/O2 (PA5 for COMP1, PA5 for COMP2) connected to comparator non inverting input */

#define COMP_NonInvertingInput_IO7                 ((uint32_t)0x00000300) /*!< I/O2 (PA6 for COMP1, PA6 for COMP2) connected to comparator non inverting input */

#define COMP_NonInvertingInput_IO8                 ((uint32_t)0x00000380) /*!< I/O2 (PA7 for COMP1, PA7 for COMP2) connected to comparator non inverting input */

#define IS_COMP_NONINVERTING_INPUT(INPUT)     (((INPUT) == COMP_NonInvertingInput_IO1)  || \
((INPUT) == COMP_NonInvertingInput_IO1)  || \
  ((INPUT) == COMP_NonInvertingInput_IO2)  || \
    ((INPUT) == COMP_NonInvertingInput_IO3)  || \
      ((INPUT) == COMP_NonInvertingInput_IO4)  || \
        ((INPUT) == COMP_NonInvertingInput_IO5)  || \
          ((INPUT) == COMP_NonInvertingInput_IO6)  || \
            ((INPUT) == COMP_NonInvertingInput_IO7)  || \
              ((INPUT) == COMP_NonInvertingInput_IO8))

/**
* @}
*/ 

/** @defgroup COMP_Output
* @{
*/

#define COMP_Output_None                  ((uint32_t)0x00000000)   /*!< COMP output isn't connected to other peripherals */

/* Output Redirection common for all comparators COMP1...COMP2 */
#define COMP_Output_TIM1BKIN              ((uint32_t)0x00000800) /*!< COMP output connected to TIM1 Break Input (BKIN) */

/* Output Redirection common for COMP1 and COMP2 */
#define COMP_Output_TIM1OCREFCLR          ((uint32_t)0x00001800)   /*!< COMP output connected to TIM1 OCREF Clear */
#define COMP_Output_TIM1IC1               ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_Output_TIM2IC4               ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_Output_TIM2OCREFCLR          ((uint32_t)0x00002400)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_Output_TIM3IC1               ((uint32_t)0x00002800)   /*!< COMP output connected to TIM3 Input Capture 1 */
#define COMP_Output_TIM3OCREFCLR          ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM3 OCREF Clear */


#define IS_COMP_OUTPUT(OUTPUT) 		(((OUTPUT) == COMP_Output_None)  || \
((OUTPUT) == COMP_Output_TIM1BKIN)  || \
  ((OUTPUT) == COMP_Output_TIM1IC1)  || \
    ((OUTPUT) == COMP_Output_TIM1OCREFCLR)  || \
      ((OUTPUT) == COMP_Output_TIM2IC4)  || \
        ((OUTPUT) == COMP_Output_TIM2OCREFCLR)  || \
          ((OUTPUT) == COMP_Output_TIM3IC1)  || \
            ((OUTPUT) == COMP_Output_TIM3OCREFCLR))

/**
* @}
*/ 

/** @defgroup COMP_BlankingSrce
* @{
*/

/* No blanking source can be selected for all comparators */
#define COMP_BlankingSrce_None                   ((uint32_t)0x00000000)    /*!< No blanking source */


#define IS_COMP_BLANKING_SOURCE(SOURCE) (((SOURCE) == COMP_BlankingSrce_None))   

/**
* @}
*/ 

/** @defgroup COMP_OutputPoloarity
* @{
*/
#define COMP_OutputPol_NonInverted          ((uint32_t)0x00000000)  /*!< COMP output on GPIO isn't inverted */
#define COMP_OutputPol_Inverted             ((uint32_t)0x00008000)  /*!< COMP output on GPIO is inverted */

#define IS_COMP_OUTPUT_POL(POL) (((POL) == COMP_OutputPol_NonInverted)  || \
((POL) == COMP_OutputPol_Inverted))

/**
* @}
*/ 

/** @defgroup COMP_Hysteresis
* @{
*/
/* Please refer to the electrical characteristics in the device datasheet for
the hysteresis level */
#define COMP_Hysteresis_No                         0x00000000           /*!< No hysteresis */
#define COMP_Hysteresis_Low                        ((uint32_t)0x00010000) /*!< Hysteresis level low */
#define COMP_Hysteresis_Medium                     ((uint32_t)0x00020000) /*!< Hysteresis level medium */
#define COMP_Hysteresis_High                       ((uint32_t)0x00030000)   /*!< Hysteresis level high */

#define IS_COMP_HYSTERESIS(HYSTERESIS)    (((HYSTERESIS) == COMP_Hysteresis_No)     || \
((HYSTERESIS) == COMP_Hysteresis_Low)    || \
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
#define COMP_Mode_HighSpeed                     ((uint32_t)0x0000000C)  /*!< High Speed */
#define COMP_Mode_MediumSpeed                   ((uint32_t)0x00000008)  /*!< Medium Speed */
#define COMP_Mode_LowPower                      ((uint32_t)0x00000004)  /*!< Low power mode */
#define COMP_Mode_UltraLowPower                 0x00000000            /*!< Ultra-low power mode */

#define IS_COMP_MODE(MODE)    (((MODE) == COMP_Mode_UltraLowPower) || \
((MODE) == COMP_Mode_LowPower)      || \
  ((MODE) == COMP_Mode_MediumSpeed)   || \
    ((MODE) == COMP_Mode_HighSpeed))
/**
* @}
*/

/** @defgroup COMP_OutputLevel
* @{
*/ 
/* When output polarity is not inverted, comparator output is high when
the non-inverting input is at a higher voltage than the inverting input */
#define COMP_OutputLevel_High                   ((uint32_t)0x40000000)
/* When output polarity is not inverted, comparator output is low when
the non-inverting input is at a lower voltage than the inverting input*/
#define COMP_OutputLevel_Low                    ((uint32_t)0x00000000)

/**
* @}
*/ 

/** @defgroup COMP_WindowMode
* @{
*/
#define IS_COMP_WINDOW(WINDOW)  (((WINDOW) == COMP_Selection_COMP2) || \
((WINDOW) == COMP_Selection_COMP4) || \
  ((WINDOW) == COMP_Selection_COMP6))
/**
* @}
*/

/**
* @}
*/ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the COMP configuration to the default reset state ****/
void COMP_DeInit(uint32_t COMP_Selection);

/* Initialization and Configuration functions *********************************/
void COMP_Init(uint32_t COMP_Selection, COMP_InitTypeDef* COMP_InitStruct);
void COMP_StructInit(COMP_InitTypeDef* COMP_InitStruct);
void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState);
void COMP_SwitchCmd(uint32_t COMP_Selection, FunctionalState NewState);
uint32_t COMP_GetOutputLevel(uint32_t COMP_Selection);

/* COMP configuration locking function ****************************************/
void COMP_LockConfig(uint32_t COMP_Selection);

#ifdef __cplusplus
}
#endif

#endif /*__HAL_COMP_H */

/**
* @}
*/ 

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2017 MindMotion ----------------------*/
