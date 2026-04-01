/**
  ******************************************************************************
  * @file    user_debug.h
  * @author  MCD Application Team
  * @brief   Header file for user debug.
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
#ifndef _USER_DEBUG_H_
#define _USER_DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll.h"


/** @addtogroup TAE_Utilities
  * @{
  */

/** @addtogroup User_Debug
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Types ------------------------------------------------------------*/
/** @defgroup User_Debug_Exported_Types User Debug Exported Types
  * @brief    User Debug Exported Types
  * @{
  */

/**
  * @brief User Debug Interface type definition
  */
typedef enum {
    USER_DBG_IFC_NO = 0,    /*!< User Debug interface NO    */
    USER_DBG_IFC_ITM,       /*!< User Debug interface ITM   */
    USER_DBG_IFC_UART0,     /*!< User Debug interface UART0 */
    USER_DBG_IFC_UART1,     /*!< User Debug interface UART1 */
    USER_DBG_IFC_UART2,     /*!< User Debug interface UART2 */
    USER_DBG_IFC_UART3,     /*!< User Debug interface UART3 */
    USER_DBG_IFC_UART4,     /*!< User Debug interface UART4 */
} USER_DBG_IfcETypeDef;

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup User_Debug_Exported_Functions
  * @{
  */
LL_StatusETypeDef User_Debug_Init(USER_DBG_IfcETypeDef ifc);
LL_StatusETypeDef User_Debug_DeInit(void);

int User_Debug_GetChar(void);
void User_Debug_PutChar(uint16_t Data);
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


#endif /* _USER_DEBUG_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

