/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : usb_lib.h
* Author             : MCD Application Team
* Version            : V3.1.0
* Date               : 10/30/2009
* Description        : USB library include files
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_LIB_H
#define __USB_LIB_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "usb_type.h"
#include "usb_regs.h"
#include "usb_def.h"
#include "usb_core.h"
#include "usb_init.h"
#ifndef STM32F10X_CL
 #include "usb_mem.h"
 #include "usb_int.h"
#endif /* STM32F10X_CL */

#include "usb_sil.h"

#ifdef STM32F10X_CL
 #include "otgd_fs_cal.h"
 #include "otgd_fs_pcd.h"
 #include "otgd_fs_dev.h"
 #include "otgd_fs_int.h"
#endif /* STM32F10X_CL */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* External variables --------------------------------------------------------*/

#endif /* __USB_LIB_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
