/*********************************************************************************************************//**
 * @file    ht32f5xxxx_div.h
 * @version $Rev:: 4617         $
 * @date    $Date:: 2020-02-26 #$
 * @brief   The header file of the DIV library.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F5XXXX_DIV_H
#define __HT32F5XXXX_DIV_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup DIV
  * @{
  */

/* Settings ------------------------------------------------------------------------------------------------*/
/** @defgroup DIV_Settings DIV settings
  * @{
  */
#define DIV_ENABLE_DIVIDE_BY_ZERO_CHECK      (0)
/**
  * @}
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup DIV_Exported_Types DIV exported types
  * @{
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup DIV_Exported_Constants DIV exported constants
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup DIV_Exported_Functions DIV exported functions
  * @{
  */
void DIV_DeInit(void);
s32 DIV_Div32(s32 dividend, s32 divisor);
s32 DIV_Mod(s32 dividend, s32 divisor);
bool DIV_IsDivByZero(void);

u32 DIV_uDiv32(u32 dividend, u32 divisor);
u32 DIV_uGetLastRemainder(void);

/*********************************************************************************************************//**
 * @brief Retuen the remainder of last dividend/divisor calculatation.
 * @retval The remainder of dividend/divisor
 ************************************************************************************************************/
__STATIC_INLINE s32 DIV_GetLastRemainder(void)
{
  return (HT_DIV->RMR);
}

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
#endif

#endif
