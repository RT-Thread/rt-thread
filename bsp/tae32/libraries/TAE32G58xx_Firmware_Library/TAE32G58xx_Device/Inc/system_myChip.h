/**
  ******************************************************************************
  * @file    system_myChip.h
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-M4 Device Peripheral Access Layer System Header File.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SYSTEM_MYCHIP_H_
#define _SYSTEM_MYCHIP_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/


/** @addtogroup TAE_CMSIS
  * @{
  */

/** @addtogroup TAE32G58xx_System
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Types ------------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/** @addtogroup TAE32G58xx_System_Exported_Variables
  * @{
  */

/**
  * @brief System Clock Frequency (Core Clock)
  */
extern uint32_t SystemCoreClock;

/**
  * @}
  */


/* Exported Functions --------------------------------------------------------*/
/** @addtogroup TAE32G58xx_System_Exported_Functions
  * @{
  */
extern void SystemInit(void);
extern void SystemCoreClockUpdate(uint32_t sysclk);
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
#endif /* __cplusplus */

#endif /* _SYSTEM_MYCHIP_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

