/**
  ******************************************************************************
  * @file    stm32l1xx_hal_opamp_ex.h
  * @author  MCD Application Team
  * @brief   Header file of OPAMP HAL Extension module.
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
#ifndef STM32L1xx_HAL_OPAMP_EX_H
#define STM32L1xx_HAL_OPAMP_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L151xDX) || defined (STM32L152xE) || defined (STM32L152xDX) || defined (STM32L162xE) || defined (STM32L162xDX) || defined (STM32L162xC) || defined (STM32L152xC) || defined (STM32L151xC)
   
/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup OPAMPEx
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/* Exported constants ---------------------------------------------------------*/
/** @defgroup OPAMPEx_Exported_Constants OPAMPEx Exported Constants
  * @{
  */
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)
#define OPAMP_CSR_OPAXPD_ALL                                                   \
  (OPAMP_CSR_OPA1PD | OPAMP_CSR_OPA2PD | OPAMP_CSR_OPA3PD)
    
#define OPAMP_CSR_OPAXCAL_L_ALL                                                \
  (OPAMP_CSR_OPA1CAL_L | OPAMP_CSR_OPA2CAL_L | OPAMP_CSR_OPA3CAL_L)

#define OPAMP_CSR_OPAXCAL_H_ALL                                                \
  (OPAMP_CSR_OPA1CAL_H | OPAMP_CSR_OPA2CAL_H | OPAMP_CSR_OPA3CAL_H)
    
#define OPAMP_CSR_ALL_SWITCHES_ALL_OPAMPS                                      \
  (OPAMP_CSR_S3SEL1 | OPAMP_CSR_S4SEL1 | OPAMP_CSR_S5SEL1 | OPAMP_CSR_S6SEL1 | \
   OPAMP_CSR_ANAWSEL1                                                        | \
   OPAMP_CSR_S3SEL2 | OPAMP_CSR_S4SEL2 | OPAMP_CSR_S5SEL2 | OPAMP_CSR_S6SEL2 | \
   OPAMP_CSR_ANAWSEL2 | OPAMP_CSR_S7SEL2                                     | \
   OPAMP_CSR_S3SEL3 | OPAMP_CSR_S4SEL3 | OPAMP_CSR_S5SEL3 | OPAMP_CSR_S6SEL3 | \
   OPAMP_CSR_ANAWSEL3                                                         )
#else
#define OPAMP_CSR_OPAXPD_ALL                                                   \
  (OPAMP_CSR_OPA1PD | OPAMP_CSR_OPA2PD)
    
#define OPAMP_CSR_OPAXCAL_L_ALL                                                \
  (OPAMP_CSR_OPA1CAL_L | OPAMP_CSR_OPA2CAL_L)

#define OPAMP_CSR_OPAXCAL_H_ALL                                                \
  (OPAMP_CSR_OPA1CAL_H | OPAMP_CSR_OPA2CAL_H)
    
#define OPAMP_CSR_ALL_SWITCHES_ALL_OPAMPS                                      \
  (OPAMP_CSR_S3SEL1 | OPAMP_CSR_S4SEL1 | OPAMP_CSR_S5SEL1 | OPAMP_CSR_S6SEL1 | \
   OPAMP_CSR_ANAWSEL1                                                        | \
   OPAMP_CSR_S3SEL2 | OPAMP_CSR_S4SEL2 | OPAMP_CSR_S5SEL2 | OPAMP_CSR_S6SEL2 | \
   OPAMP_CSR_ANAWSEL2 | OPAMP_CSR_S7SEL2                                      )
#endif /* STM32L151xD || STM32L152xD || STM32L162xD */

/**
  * @}
  */
  
/* Exported macro ------------------------------------------------------------*/
    
/** @defgroup OPAMPEx_Exported_Macro OPAMPEx Exported Macro
  * @{
  */
    
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)
/**
  * @brief Enable internal analog switch SW1 to connect OPAMP3 ouput to ADC
  * switch matrix (ADC channel VCOMP, channel 26) and COMP1 non-inverting input
  * (OPAMP3 available on STM32L1 devices Cat.4 only).
  * @retval None
  */
#define __HAL_OPAMP_OPAMP3OUT_CONNECT_ADC_COMP1()    __HAL_RI_SWITCH_COMP1_SW1_CLOSE()

/**
  * @brief Disable internal analog switch SW1 to disconnect OPAMP3 ouput from 
  * ADC switch matrix (ADC channel VCOMP, channel 26) and COMP1 non-inverting
  * input.
  * @retval None
  */
#define __HAL_OPAMP_OPAMP3OUT_DISCONNECT_ADC_COMP1() __HAL_RI_SWITCH_COMP1_SW1_OPEN()
#endif /* STM32L151xD || STM32L152xD || STM32L162xD */
    
/**
  * @}
  */
      
/* Private macro -------------------------------------------------------------*/

/** @defgroup OPAMPEx_Private_Macro OPAMPEx Private Macro
  * @{
  */
   
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)
/**
  * @brief Get the OPAMP instance in decimal number for further
  * processing needs by HAL OPAMP driver functions.
  * @param __HANDLE__: OPAMP handle
  * @retval "0" for OPAMP1, "1" for OPAMP2, "2" for OPAMP3
  */
#define OPAMP_INSTANCE_DECIMAL(__HANDLE__)                                     \
  ( ( ((__HANDLE__)->Instance == OPAMP1)                                       \
    )?                                                                         \
     ((uint32_t)0UL)                                                             \
     :                                                                         \
     ( ( ((__HANDLE__)->Instance == OPAMP2)                                    \
       )?                                                                      \
        ((uint32_t)1UL)                                                          \
        :                                                                      \
        ((uint32_t)2UL)                                                          \
     )                                                                         \
  )
#else
/**
  * @brief Get the OPAMP instance in decimal number for further
  * processing needs by HAL OPAMP driver functions.
  * @param __HANDLE__: OPAMP handle
  * @retval "0" for OPAMP1, "1" for OPAMP2
  */
#define OPAMP_INSTANCE_DECIMAL(__HANDLE__)                                     \
  ( ( ((__HANDLE__)->Instance == OPAMP1)                                       \
    )?                                                                         \
     ((uint32_t)0UL)                                                             \
     :                                                                         \
     ((uint32_t)1UL)                                                             \
  )
#endif /* STM32L151xD || STM32L152xD || STM32L162xD */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)

/**
  * @brief Check OPAMP non-inverting input in function of OPAMPx instance
  * @param __HANDLE__: OPAMP handle
  * @param INPUT: OPAMP non-inverting input                                        
  * @retval None
  */
#define IS_OPAMP_NONINVERTING_INPUT_CHECK_INSTANCE(__HANDLE__, INPUT)          \
  ( ( ((__HANDLE__)->Instance == OPAMP1)                                       \
    )?                                                                         \
     (                                                                         \
      ((INPUT) == OPAMP_NONINVERTINGINPUT_IO0)     ||                          \
      ((INPUT) == OPAMP_NONINVERTINGINPUT_DAC_CH1)                             \
     )                                                                         \
     :                                                                         \
     ( ( ((__HANDLE__)->Instance == OPAMP2)                                    \
       )?                                                                      \
        (                                                                      \
         ((INPUT) == OPAMP_NONINVERTINGINPUT_IO0)     ||                       \
         ((INPUT) == OPAMP_NONINVERTINGINPUT_DAC_CH1) ||                       \
         ((INPUT) == OPAMP_NONINVERTINGINPUT_DAC_CH2)                          \
        )                                                                      \
        :                                                                      \
        (                                                                      \
         ((INPUT) == OPAMP_NONINVERTINGINPUT_IO0)     ||                       \
         ((INPUT) == OPAMP_NONINVERTINGINPUT_DAC_CH2)                          \
        )                                                                      \
     )                                                                         \
  )
#else
/**
  * @brief Check OPAMP non-inverting input in function of OPAMPx instance
  * @param __HANDLE__: OPAMP handle
  * @param INPUT: OPAMP non-inverting input                                        
  * @retval None
  */
#define IS_OPAMP_NONINVERTING_INPUT_CHECK_INSTANCE(__HANDLE__, INPUT)          \
  ( ( ((__HANDLE__)->Instance == OPAMP1)                                       \
    )?                                                                         \
     (                                                                         \
      ((INPUT) == OPAMP_NONINVERTINGINPUT_IO0)     ||                          \
      ((INPUT) == OPAMP_NONINVERTINGINPUT_DAC_CH1)                             \
     )                                                                         \
     :                                                                         \
     (                                                                         \
      ((INPUT) == OPAMP_NONINVERTINGINPUT_IO0)     ||                          \
      ((INPUT) == OPAMP_NONINVERTINGINPUT_DAC_CH1) ||                          \
      ((INPUT) == OPAMP_NONINVERTINGINPUT_DAC_CH2)                             \
     )                                                                         \
  )
#endif /* STM32L151xD || STM32L152xD || STM32L162xD */

/**
  * @}
  */
    
/* Exported functions --------------------------------------------------------*/
/** @addtogroup OPAMPEx_Exported_Functions
  * @{
  */

/* I/O operation functions  *****************************************************/
/** @defgroup OPAMPEx_Exported_Functions_Group1 Extended Input and Output operation functions
  * @{
  */
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)
HAL_StatusTypeDef HAL_OPAMPEx_SelfCalibrateAll(OPAMP_HandleTypeDef *hopamp1, OPAMP_HandleTypeDef *hopamp2, OPAMP_HandleTypeDef *hopamp3);
#else
HAL_StatusTypeDef HAL_OPAMPEx_SelfCalibrateAll(OPAMP_HandleTypeDef *hopamp1, OPAMP_HandleTypeDef *hopamp2);
#endif /* STM32L151xD || STM32L152xD || STM32L162xD */
/**
  * @}
  */
/* Peripheral Control functions  ************************************************/
/** @addtogroup OPAMPEx_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef HAL_OPAMPEx_Unlock(OPAMP_HandleTypeDef *hopamp); 
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

#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L151xDX || STM32L152xE || STM32L152xDX || STM32L162xE || STM32L162xDX || STM32L162xC || STM32L152xC || STM32L151xC */

#ifdef __cplusplus
}
#endif


#endif /* STM32L1xx_HAL_OPAMP_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
