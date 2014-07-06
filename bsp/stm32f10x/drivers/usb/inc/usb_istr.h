/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : usb_istr.h
* Author             : MCD Application Team
* Version            : V2.2.1
* Date               : 09/22/2008
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
#include "tocom\usb_tocom_conf.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
//void USB_Istr(void);
/* function prototypes Automatically built defining related macros */
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

#endif /*__USB_ISTR_H*/

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
