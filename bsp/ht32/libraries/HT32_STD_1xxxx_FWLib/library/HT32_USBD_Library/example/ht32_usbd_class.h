/*********************************************************************************************************//**
 * @file    example/ht32_usbd_class.h
 * @version $Rev:: 5            $
 * @date    $Date:: 2017-05-11 #$
 * @brief   The header file of USB Device Class.
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
#ifndef __HT32_USBD_CLASS_H
#define __HT32_USBD_CLASS_H

/* Includes ------------------------------------------------------------------------------------------------*/

/** @addtogroup HT32_USBD_Library HT32 USB Device Library
  * @{
  */

/** @defgroup USBDClass USB Device Class
  * @brief USB Device Class
  * @{
  */


/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup USBDClass_Private_Define USB Device Class private definitions
  * @{
  */
/* For ht32_usbd_descriptor.c                                                                               */
#define CLASS_INF_CLASS                   (DESC_CLASS_03_XXX)
#define CLASS_INF_SUBCLASS                (HID_SUBCLASS_00_NONE)
#define CLASS_INF_PTCO                    (HID_PROTOCOL_00_NONE)

/* HID related definition                                                                                   */
#define DESC_LEN_XXX                      ((u32)(9))
#define DESC_LEN_XXX                      ((u16)(47))

#define DESC_TYPE_01_XXX                  (0x01)
#define DESC_TYPE_02_XXX                  (0x02)

#define HID_SUBCLASS_00_NONE              (0x00)
#define HID_SUBCLASS_01_BOOT              (0x01)

#define HID_PROTOCOL_00_NONE              (0x00)
/**
  * @}
  */


/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup USBDClass_Exported_Functions USB Device Class exported functions
  * @{
  */
void USBDClass_Init(USBDCore_Class_TypeDef *pClass);
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#endif /* __HT32_USBD_CLASS_H ------------------------------------------------------------------------------*/
