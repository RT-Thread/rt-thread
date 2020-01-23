/**
  **************************************************************************************
  * @file    SYSTEM_ES32F027x.H
  * @brief   es32f0271 system head file.
  *
  * @version V0.01
  * @data    5/17/2018
  * @author  Eastsoft AE Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/ 

#ifndef __SYSTEM_ES32F027x_H__
#define __SYSTEM_ES32F027x_H__

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes -------------------------------------------------------*/
#include <stdint.h>
 
/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup System_ES32F027x
  * @{
  */
   
/* Public Functions -----------------------------------------------------------*/
/* Public Init Structure ------------------------------------------------------*/
/* Public Macros --------------------------------------------------------------*/
/* Public Constants -----------------------------------------------------------*/
/* Private Variables ----------------------------------------------------------*/
/* Private Macros -------------------------------------------------------------*/
/* Private Constants-----------------------------------------------------------*/

/* Public Types ---------------------------------------------------------------*/
/** @addtogroup Public_Types 
  * @{
  */
extern unsigned int SystemCoreClock;
extern unsigned int SystemFrequency_SysClk;
extern unsigned int SystemFrequency_AHBClk;
extern unsigned int SystemFrequency_APBClk;
extern unsigned int PLL1Frequency;
extern unsigned int PLL0Frequency;

/* Exported function -------------------------------------------------*/
/** @addtogroup Public_Functions
  * @{
  */

extern void SystemInit (void);

#ifdef __cplusplus
}
#endif

#endif 

/**
  * @} Public_Functions 
  */

/**
  * @} Public_Types
  */
  
/**
  * @} System_ES32F027x
  */
  
/**
  * @} CMSIS
  */ 
/********** (C) COPYRIGHT Eastsoft Microelectronics END OF FILE SYSTEM_ES32F027x.H **********/
