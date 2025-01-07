/*********************************************************************************************************//**
 * @file    example/ht32_usbd_descriptor.h
 * @version $Rev:: 5            $
 * @date    $Date:: 2017-05-11 #$
 * @brief   The USB descriptor.
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
#ifndef __HT32_USBD_DESCRIPTOR_H
#define __HT32_USBD_DESCRIPTOR_H

/* Includes ------------------------------------------------------------------------------------------------*/

/** @addtogroup HT32_USBD_Library HT32 USB Device Library
  * @{
  */

/** @defgroup USBDDescriptor USB Descriptor
  * @brief USB descriptor
  * @{
  */


/* Exported constants --------------------------------------------------------------------------------------*/
#define DESC_LEN_CONFN_T          (u16)(DESC_LEN_CONFN + DESC_LEN_INF + DESC_LEN_XXX + DESC_LEN_EPT * 2)

/* Exported functions --------------------------------------------------------------------------------------*/
void USBDDesc_Init(USBDCore_Desc_TypeDef *pDesc);


/**
  * @}
  */

/**
  * @}
  */

#endif /* __HT32_USBD_DESCRIPTOR_H -------------------------------------------------------------------------*/
