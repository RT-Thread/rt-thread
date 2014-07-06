/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : usb_istr.h
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : This file includes the peripherals header files in the
*                      user application.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_ISTR_H
#define __USB_ISTR_H

/* Includes ------------------------------------------------------------------*/
#include "usb_conf.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifndef STM32F10X_CL
 void USB_Istr(void);
#else /* STM32F10X_CL */
 u32 STM32_PCD_OTG_ISR_Handler(void);
#endif /* STM32F10X_CL */

/* function prototypes Automatically built defining related macros */

void EP1_IN_Callback(void);
void EP2_IN_Callback(void);
void EP3_IN_Callback(void);
void EP4_IN_Callback(void);
void EP5_IN_Callback(void);
void EP6_IN_Callback(void);
void EP7_IN_Callback(void);

void EP1_OUT_Callback(void);
void EP2_OUT_Callback(void);
void EP3_OUT_Callback(void);
void EP4_OUT_Callback(void);
void EP5_OUT_Callback(void);
void EP6_OUT_Callback(void);
void EP7_OUT_Callback(void);

#ifndef STM32F10X_CL

#ifdef CTR_CALLBACK
void CTR_Callback(void);
#endif

#ifdef DOVR_CALLBACK
void DOVR_Callback(void);
#endif

#ifdef ERR_CALLBACK
void ERR_Callback(void);
#endif

#ifdef WKUP_CALLBACK
void WKUP_Callback(void);
#endif

#ifdef SUSP_CALLBACK
void SUSP_Callback(void);
#endif

#ifdef RESET_CALLBACK
void RESET_Callback(void);
#endif

#ifdef SOF_CALLBACK
void SOF_Callback(void);
#endif

#ifdef ESOF_CALLBACK
void ESOF_Callback(void);
#endif

#else /* STM32F10X_CL */

/* Interrupt subroutines user callbacks prototypes.
   These callbacks are called into the respective interrupt sunroutine functinos
   and can be tailored for various user application purposes.
     Note: Make sure that the correspondant interrupt is enabled through the 
     definition in usb_conf.h file */ 
void INTR_MODEMISMATCH_Callback(void);
void INTR_SOFINTR_Callback(void);
void INTR_RXSTSQLVL_Callback(void);
void INTR_NPTXFEMPTY_Callback(void);
void INTR_GINNAKEFF_Callback(void);
void INTR_GOUTNAKEFF_Callback(void);
void INTR_ERLYSUSPEND_Callback(void);
void INTR_USBSUSPEND_Callback(void);
void INTR_USBRESET_Callback(void);
void INTR_ENUMDONE_Callback(void);
void INTR_ISOOUTDROP_Callback(void);
void INTR_EOPFRAME_Callback(void);
void INTR_EPMISMATCH_Callback(void);
void INTR_INEPINTR_Callback(void);
void INTR_OUTEPINTR_Callback(void);
void INTR_INCOMPLISOIN_Callback(void);
void INTR_INCOMPLISOOUT_Callback(void);
void INTR_WKUPINTR_Callback(void);

/* Isochronous data update */
void INTR_RXSTSQLVL_ISODU_Callback(void); 

#endif /* STM32F10X_CL */


#endif /*__USB_ISTR_H*/

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
