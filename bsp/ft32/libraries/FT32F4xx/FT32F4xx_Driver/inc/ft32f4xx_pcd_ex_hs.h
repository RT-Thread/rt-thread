/**
  ******************************************************************************
  * @file    			ft32f4xx_pcd_ex_hs.h
  * @author  			FMD XA
  * @brief   			This file contains all the functions prototypes for the 
  *          >>->-USB_OTG_HS firmware library.
  * @version 			V1.0.0           
  * @data		 			2025-03-31
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_PCD_EX_HS_H
#define __FT32F4XX_PCD_EX_HS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_usb_hs.h"

#if defined (USB_OTG_HS)
/** @addtogroup ft32f4xx  Drive
  * @
  */

/** @addtogroup PCD_HS
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup PCD_HS_Exported_Types PCD Exported Types
  * @{
  */

/** @defgroup PCD_HS_Exported_Types_Group1 PCD State Structure definition
  * @{
  */
/** @addtogroup PCDEx_Exported_Functions PCDEx Exported Functions
  * @{
  */
/** @addtogroup PCDEx_Exported_Functions_Group1 Peripheral Control functions
  * @{
  */

#if defined (USB_OTG_HS)
void PCDEx_HS_SetTxFiFo(uint8_t fifo, uint16_t size);
void PCDEx_HS_SetRxFiFo(uint16_t size);
#endif /* defined (USB_OTG_HS) */



/**
  * @}
  */
#endif /* defined (USB_OTG_HS) */

#ifdef __cplusplus
}
#endif


#endif /* FT32F4XX_PCD_HS_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
