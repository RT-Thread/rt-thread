/**
  ******************************************************************************
  * @file    tae_dbg_conf_template.h
  * @author  MCD Application Team
  * @brief   Template of the configuration for dbg
  *          You should copy this file to your own directory and rename it to
  *          "tae_dbg_conf.h". Then you should change the config with your favourites
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
#ifndef _TAE_DBG_CONF_TEMPLATE_H_
#define _TAE_DBG_CONF_TEMPLATE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>


/** @addtogroup TAE_Utilities
  * @{
  */

/** @defgroup TAE_Debug_Template TAE Debug Template
  * @brief    TAE Debug Template
  * @{
  */


/* Exported Types ------------------------------------------------------------*/
/* Exported Constants --------------------------------------------------------*/
/** @defgroup TAE_Debug_Template_Exported_Constants TAE Debug Template Exported Constants
  * @brief    TAE Debug Template Exported Constants
  * @{
  */

/**
  * @brief Define TAE_USING_DBG to enable dbg
  */
#define TAE_USING_DBG

/**
  * @brief Define TAE_USING_DBG_COLOR to enable dbg color mode
  */
#define TAE_USING_DBG_COLOR

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup TAE_Debug_Template_Exported_Macros TAE Debug Template Exported Macros
  * @brief    TAE Debug Template Exported Macros
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


#endif /* _TAE_DBG_CONF_TEMPLATE_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

