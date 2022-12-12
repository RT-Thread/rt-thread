/**
  ******************************************************************************
  * @file    tae32f53xx_dbg_conf.h
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
#ifndef _TAE32F53XX_DBG_CONF_H_
#define _TAE32F53XX_DBG_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>


/** @addtogroup TAE32F53xx_Examples
  * @{
  */

/** @addtogroup TAE32F53xx_Template
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup TAE32F53xx_Debug_Conf_Exported_Constants TAE32F53xx Debug Conf Exported Constants
  * @brief    TAE32F53xx Debug Conf Exported Constants
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


/* Exported macro ------------------------------------------------------------*/
/** @defgroup TAE32F53xx_Debug_Conf_Exported_Macros TAE32F53xx Debug Conf Exported Macros
  * @brief    TAE32F53xx Debug Conf Exported Macros
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


/* Exported functions --------------------------------------------------------*/
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


#endif /* _TAE32F53XX_DBG_CONF_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

