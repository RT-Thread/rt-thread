/**
 **************************************************************************
 * File Name    : at32f4xx_acc.h
 * Description  : at32f4xx ACC header file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */

 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32f4xx_ACC_H
#define __AT32f4xx_ACC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"


/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup ACC
  * @{
  */

  /** @defgroup ACC_Exported_Constants
  * @{
  */
#define ACC_CAL_Enable                        ((uint16_t)0x0001)

#define ACC_CAL_ON                            ((uint16_t)0x0001)
#define ACC_TRIM_ON                           ((uint16_t)0x0003)

#define ACC_CAL_HSICAL                        ((uint16_t)0x0000)
#define ACC_CAL_HSITRIM                       ((uint16_t)0x0002)
  
#define ACC_FLAG_RSLOST                       ((uint16_t)0x0002)
#define ACC_FLAG_CALRDY                       ((uint16_t)0x0001)

#define ACC_IT_CALRDYIEN                      ((uint16_t)0x0020)
#define ACC_IT_EIEN                           ((uint16_t)0x0010)
/**
  * @}
  */
  
/** @defgroup ACC_Exported_Functions
  * @{
  */  

void ACC_EnterCALMode(uint16_t ACC_ON, FunctionalState NewState);
void ACC_ExitCALMode(void);
void ACC_SetStep(uint8_t StepValue);
void ACC_CAL_Choose(uint16_t ACC_Calibration_Choose);
void ACC_ITConfig(uint16_t ACC_IT, FunctionalState NewState);

uint8_t ACC_GetHSITRIM(void);
uint8_t ACC_GetHSICAL(void);

void ACC_WriteC1(uint16_t ACC_C1_Value);
void ACC_WriteC2(uint16_t ACC_C2_Value);
void ACC_WriteC3(uint16_t ACC_C3_Value);

uint16_t ACC_ReadC1(void);
uint16_t ACC_ReadC2(void);
uint16_t ACC_ReadC3(void);

FlagStatus ACC_GetFlagStatus(uint16_t ACC_FLAG);
void ACC_ClearFlag(uint16_t ACC_FLAG);


#ifdef __cplusplus
}
#endif

#endif /* __AT32F4xx_ACC_H */

/**
  * @}
  */
  
/**
  * @}
  */  
/**
  * @}
  */    





