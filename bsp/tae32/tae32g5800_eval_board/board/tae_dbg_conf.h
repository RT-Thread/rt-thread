/**
  ******************************************************************************
  * @file    tae_dbg_conf.h
  * @author  MCD Application Team
  * @brief   Configuration for dbg
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
#ifndef _TAE_DBG_CONF_H_
#define _TAE_DBG_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <inttypes.h>


/** @addtogroup TAE32G58xx_Examples
  * @{
  */

/** @addtogroup TAE32G58xx_GPIO_Flow_LED_Example
  * @{
  */


/* Exported Types ------------------------------------------------------------*/
/* Exported Constants --------------------------------------------------------*/
/** @defgroup GPIO_Flow_LED_Debug_Conf_Exported_Constants GPIO_Flow_LED Debug Conf Exported Constants
  * @brief    GPIO_Flow_LED Debug Conf Exported Constants
  * @{
  */

/**
  * @brief Define TAE_USING_DBG to enable dbg
  */
#define TAE_USING_DBG

/**
  * @brief Define TAE_USING_DBG_COLOR to enable dbg color mode
  */
//#define TAE_USING_DBG_COLOR

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup GPIO_Flow_LED_Debug_Conf_Exported_Macros GPIO_Flow_LED Debug Conf Exported Macros
  * @brief    GPIO_Flow_LED Debug Conf Exported Macros
  * @{
  */

/**
  * @brief Define your own print interface here
  */
#ifdef TAE_USING_DBG
#define TAE_DBG_PRINT(fmt, ...)             printf(fmt, ##__VA_ARGS__)
#else
#define TAE_DBG_PRINT(fmt, ...)
#endif

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE_DBG_CONF_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

