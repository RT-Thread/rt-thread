/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : otgd_fs_int.h
* Author             : MCD Application Team
* Version            : V3.1.0
* Date               : 10/30/2009
* Description        : Endpoint interrupt's service routines prototypes.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_INT_H
#define __USB_INT_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef STM32F10X_CL

/* Interrupt Handlers functions */
uint32_t OTGD_FS_Handle_ModeMismatch_ISR(void);
uint32_t OTGD_FS_Handle_Sof_ISR(void);
uint32_t OTGD_FS_Handle_RxStatusQueueLevel_ISR(void);
uint32_t OTGD_FS_Handle_NPTxFE_ISR(void);
uint32_t OTGD_FS_Handle_GInNakEff_ISR(void);
uint32_t OTGD_FS_Handle_GOutNakEff_ISR(void);
uint32_t OTGD_FS_Handle_EarlySuspend_ISR(void);
uint32_t OTGD_FS_Handle_USBSuspend_ISR(void);
uint32_t OTGD_FS_Handle_UsbReset_ISR(void);
uint32_t OTGD_FS_Handle_EnumDone_ISR(void);
uint32_t OTGD_FS_Handle_IsoOutDrop_ISR(void);
uint32_t OTGD_FS_Handle_EOPF_ISR(void);
uint32_t OTGD_FS_Handle_EPMismatch_ISR(void);
uint32_t OTGD_FS_Handle_InEP_ISR(void);
uint32_t OTGD_FS_Handle_OutEP_ISR(void);
uint32_t OTGD_FS_Handle_IncomplIsoIn_ISR(void);
uint32_t OTGD_FS_Handle_IncomplIsoOut_ISR(void);
uint32_t OTGD_FS_Handle_Wakeup_ISR(void);

#endif /* STM32F10X_CL */

/* External variables --------------------------------------------------------*/

#endif /* __USB_INT_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
