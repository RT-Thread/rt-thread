/**
  ******************************************************************************
  * @file    system_tae32f53xx.h
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Header File.
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
#ifndef _SYSTEM_TAE32F53XX_H_
#define _SYSTEM_TAE32F53XX_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/


/** @addtogroup TAE_CMSIS
  * @{
  */

/** @addtogroup TAE32F53xx_System
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/** @addtogroup TAE32F53xx_System_Exported_Variables
  * @{
  */

/**
  * @brief System Clock Frequency (Core Clock)
  */
extern uint32_t SystemCoreClock;

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup TAE32F53xx_System_Exported_Functions
  * @{
  */
extern void SystemInit(void);
extern void SystemCoreClockUpdate(uint32_t sysclk);
/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SYSTEM_TAE32F53XX_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

