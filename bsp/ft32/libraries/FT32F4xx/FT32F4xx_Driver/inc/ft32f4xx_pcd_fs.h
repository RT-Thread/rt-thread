/**
  ******************************************************************************
  * @file    			ft32f4xx_pcd_fs.h
  * @author  			FMD XA
  * @brief   			This file contains all the functions prototypes for the 
  *          >>->-USB_OTG_FS firmware library.
  * @version 			V1.0.0           
  * @data		 			2025-06-04
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_PCD_FS_H
#define __FT32F4XX_PCD_FS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_usb_fs.h"

#if defined (USB_OTG_FS)


/* Exported types ------------------------------------------------------------*/

#if defined (USB_OTG_FS)
void PCD_FS_SetTxFiFo(uint8_t fifo, uint16_t size, uint8_t dpb);
void PCD_FS_SetRxFiFo(uint8_t fifo, uint16_t size, uint8_t dpb);
#endif /* defined (USB_OTG_FS) */


/**
 * @brief PCD state structure definition
 */

typedef enum
{
  PCD_FS_STATE_RESET    = 0x00,
  PCD_FS_STATE_READY    = 0x01,
  PCD_FS_STATE_ERROR    = 0x02,
  PCD_FS_STATE_BUSY     = 0x03,
  PCD_FS_STATE_TIMEOUT  = 0x04
} PCD_FS_StateTypeDef;



#if defined (USB_OTG_FS)
typedef USB_OTG_FS_CfgTypeDef       PCD_FS_InitTypeDef;
typedef USB_OTG_FS_DEPTypeDef       PCD_FS_EPTypeDef;
typedef USB_FS_LockTypeDef          PCD_FS_LockTypeDef;
typedef USB_OTG_FS_CtlStateTypeDef  PCD_FS_CtlStateTypeDef;
#endif /* defined (USB_OTG_FS) */

/**
  * @}
  */

/** @brief PCD Handle Structure definition
  * @{
  */
typedef struct
{
  PCD_FS_InitTypeDef           Init;       /*!< PCD required parameters   */
  __IO uint8_t                 USB_Address;/*!< USB Address               */
  PCD_FS_EPTypeDef             IN_ep[16];  /*!< IN endpoint parameters    */
  PCD_FS_EPTypeDef             OUT_ep[16]; /*!< OUT endpoint parameters   */
  PCD_FS_CtlStateTypeDef       ctrl_state;
  PCD_FS_LockTypeDef           Lock;       /*!< PCD peripheral status     */
  __IO PCD_FS_StateTypeDef     State;      /*!< PCD communication state   */
  __IO  uint32_t               ErrorCode;  /*!< PCD Error code            */
  uint32_t                     Setup[2];   /*!< Setup packet buffer       */
  uint32_t                     FrameNumber;/*!< Store Current Frame number*/
  void                         *pData;     /*!< Pointer Stack Handler     */
} PCD_FS_HandleTypeDef;
/**
  * @}
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

#define PCD_SPEED_FULL               USB_FS_SPEED

/* Exported macro ------------------------------------------------------------*/

#define __USB_OTG_FS_WAKEUP_EXTI_ENABLE_IT()    EXTI->IMR |= USB_OTG_FS_WAKEUP_EXTI_LINE
#define __USB_OTG_FS_WAKEUP_EXTI_DISABLE_IT()   EXTI->IMR &= ~(USB_OTG_FS_WAKEUP_EXTI_LINE)
#define __USB_OTG_FS_WAKEUP_EXTI_GET_FLAG()     EXTI->PR & (USB_OTG_FS_WAKEUP_EXTI_LINE)
#define __USB_OTG_FS_WAKEUP_EXTI_CLEAR_FLAG()   EXTI->PR = USB_OTG_FS_WAKEUP_EXTI_LINE

#define __USB_OTG_FS_WAKEUP_EXTI_ENABLE_RISING_EDGE() \
  do { \
    EXTI->FTSR &= ~(USB_OTG_FS_WAKEUP_EXTI_LINE); \
    EXTI->RTSR |= USB_OTG_FS_WAKEUP_EXTI_LINE; \
  } while(0U)


/* Exported functions --------------------------------------------------------*/

USB_FS_StatusTypeDef PCD_FS_Init(PCD_FS_HandleTypeDef *hpcd);
USB_FS_StatusTypeDef PCD_FS_DeInit(PCD_FS_HandleTypeDef *hpcd);
void PCD_FS_SetISO(uint8_t ep_num, uint8_t state);
void PCD_FS_SetMaxPkt(uint8_t ep_num, uint16_t size);

void              PCD_FS_MspInit(PCD_FS_HandleTypeDef *hpcd);
void              PCD_FS_MspDeInit(PCD_FS_HandleTypeDef *hpcd);


/* I/O operation functions  ***************************************************/

USB_FS_StatusTypeDef PCD_FS_Start(PCD_FS_HandleTypeDef *hpcd);
USB_FS_StatusTypeDef PCD_FS_Stop(PCD_FS_HandleTypeDef *hpcd);

/* Non-Blocking mode: Interrupt */
void PCD_FS_IRQHandler(PCD_FS_HandleTypeDef *hpcd);
void PCD_FS_EP0_IRQHandler(PCD_FS_HandleTypeDef *hpcd);
void PCD_FS_TXEP_IRQHandler(PCD_FS_HandleTypeDef *hpcd, uint32_t epnum);
void PCD_FS_RXEP_IRQHandler(PCD_FS_HandleTypeDef *hpcd, uint32_t epnum);
void PCD_FS_WKUP_IRQHandler(void);

void PCD_FS_SOFCallback(PCD_FS_HandleTypeDef *hpcd);
void PCD_FS_SetupStageCallback(PCD_FS_HandleTypeDef *hpcd);
void PCD_FS_ResetCallback(PCD_FS_HandleTypeDef *hpcd);
void PCD_FS_SuspendCallback(PCD_FS_HandleTypeDef *hpcd);
void PCD_FS_ResumeCallback(PCD_FS_HandleTypeDef *hpcd);
void PCD_FS_ConnectCallback(PCD_FS_HandleTypeDef *hpcd);
void PCD_FS_DisconnectCallback(PCD_FS_HandleTypeDef *hpcd);
void PCD_FS_SessionCallback(PCD_FS_HandleTypeDef *hpcd);
void PCD_FS_VBusErrCallback(PCD_FS_HandleTypeDef *hpcd);
void PCD_FS_OVERRUNCallback(PCD_FS_HandleTypeDef *hpcd);
void PCD_FS_UNDERRUNCallback(PCD_FS_HandleTypeDef *hpcd);
void PCD_FS_DERRCallback(PCD_FS_HandleTypeDef *hpcd);

void PCD_FS_DataOutStageCallback(PCD_FS_HandleTypeDef *hpcd, uint8_t epnum);
void PCD_FS_DataInStageCallback(PCD_FS_HandleTypeDef *hpcd, uint8_t epnum);

/* Peripheral Control functions  **********************************************/

USB_FS_StatusTypeDef PCD_FS_DevDisconnect(PCD_FS_HandleTypeDef *hpcd);
USB_FS_StatusTypeDef PCD_FS_SetAddress(PCD_FS_HandleTypeDef *hpcd, uint8_t address);
USB_FS_StatusTypeDef PCD_FS_EP_Open(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type);
USB_FS_StatusTypeDef PCD_FS_Ep_Close(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr);
void                 PCD_FS_Ep_Receive(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len);
void                 PCD_FS_Ep_Transmit(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len);
USB_FS_StatusTypeDef PCD_FS_EP_SetStall(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr);
USB_FS_StatusTypeDef PCD_FS_EP_ClrStall(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr);
USB_FS_StatusTypeDef PCD_FS_EP_Flush(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr);
USB_FS_StatusTypeDef PCD_FS_EP_Abort(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr);
void                 PCD_FS_ActivateRemoteWakeup(void);
void                 PCD_FS_DeActivateRemoteWakeup(void);

uint32_t             PCD_FS_EP_GetRxCount(const PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr);
USB_FS_StatusTypeDef PCD_FS_EP_Close(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr);
void PCD_FS_EP_Receive(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len);
void PCD_FS_EP_Transmit(PCD_FS_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len);
/* Peripheral State functions  ************************************************/

PCD_FS_StateTypeDef PCD_FS_GetState(PCD_FS_HandleTypeDef const *hpcd);


/* Private constants ---------------------------------------------------------*/


#if defined (USB_OTG_FS)
#define USB_OTG_FS_WAKEUP_EXTI_LINE                                   (0x1U << 18)  /*!< USB FS EXTI Line WakeUp Interrupt */
#endif /* defined (USB_OTG_FS) */



/* Private constants ---------------------------------------------------------*/


#endif /* defined (USB_OTG_FS) */

#ifdef __cplusplus
}
#endif

#endif /* FT32F4XX_PCD_FS_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
