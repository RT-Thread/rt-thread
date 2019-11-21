/**
  **************************************************************************************
  * @file    system_es32f027x.c
  * @brief   System File.
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

/* Incudes--------------------------------------------------------*/
#include "system_es32f027x.h"

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup System_ES32F027X
  * @{
  */

/* Public Functions -----------------------------------------------------------*/
/* Public Init Structure ------------------------------------------------------*/
/* Public Macros --------------------------------------------------------------*/
/* Public Constants -----------------------------------------------------------*/
/* Private Macros -------------------------------------------------------------*/
/* Private Constants-----------------------------------------------------------*/

/* Private Variables ----------------------------------------------------------*/
/** @addtogroup Private_Variables
  * @{
  */

/**
  * @brief update the value of SystemCoreClock after changing the system clock.
  */
unsigned int SystemCoreClock = 4000000;
unsigned int SystemFrequency_SysClk = 4000000;
unsigned int SystemFrequency_AHBClk = 4000000;
unsigned int SystemFrequency_APBClk = 4000000;
unsigned int PLL1Frequency = 48000000;
unsigned int PLL0Frequency = 4000000;

/**
  * @} Private_Variables
  */

/* Private Functions ----------------------------------------------------------*/
/** @addtogroup Private_Functions
  * @{
  */

/**
  * @brief:SystemInit. 
  * @param:none
  * @retval:none
  */
void SystemInit (void)
{
}

/**
  * @} Private_Functions
  */

/**
  * @} System_ES32F072X
  */

/**
  * @} CMSIS
  */
/********** (C) COPYRIGHT Eastsoft Microelectronics END OF FILE SYSTEM_ES32F027X.H **********/

