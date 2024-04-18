/*********************************************************************************************************//**
 * @file    ht32_serial.h
 * @version $Rev:: 2765         $
 * @date    $Date:: 2022-11-11 #$
 * @brief   The header file of the Serial library.
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
#ifndef __HT32_SERIAL_H
#define __HT32_SERIAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#ifdef RETARGET_IS_USB
#include "ht32_usbd_core.h"
#endif

/** @addtogroup HT32_Peripheral_Driver HT32 Peripheral Driver
  * @{
  */

/** @addtogroup SERIAL
  * @brief Serial related functions
  * @{
  */


/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup SERIAL_Exported_Functions Serial exported functions
  * @{
  */
void RETARGET_UART_IRQHandler(void);
u32 SERIAL_GetChar(void);
u32 SERIAL_PutChar(u32 ch);
#ifdef RETARGET_IS_USB
void SERIAL_USBDClass_Request(USBDCore_Device_TypeDef *pDev);
void SERIAL_USBDClass_RXHandler(USBD_EPTn_Enum EPTn);
void SERIAL_USBDClass_TXHandler(USBD_EPTn_Enum EPTn);
void SERIAL_USBDInit(void);
void SERIAL_Flush(void);
#else
#define SERIAL_Flush(...)
#endif
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
