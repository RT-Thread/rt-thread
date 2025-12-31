/**
  ******************************************************************************
  * @file    			ft32f4xx_pcd_hs.h
  * @author  			FMD XA
  * @brief   			This file contains all the functions prototypes for the 
  *          >>->-USB_OTG_HS firmware library.
  * @version 			V1.0.0           
  * @data		 			2025-03-31
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_PCD_HS_H
#define __FT32F4XX_PCD_HS_H

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

/**
 * @brief PCD state structure definition
 */

typedef enum
{
  PCD_HS_STATE_RESET    = 0x00,
  PCD_HS_STATE_READY    = 0x01,
  PCD_HS_STATE_ERROR    = 0x02,
  PCD_HS_STATE_BUSY     = 0x03,
  PCD_HS_STATE_TIMEOUT  = 0x04
} PCD_HS_StateTypeDef;



#if defined (USB_OTG_HS)
typedef USB_OTG_HS_GlobalTypeDef  PCD_HS_TypeDef;
typedef USB_OTG_HS_CfgTypeDef     PCD_HS_InitTypeDef;
typedef USB_OTG_HS_EPTypeDef      PCD_HS_EPTypeDef;
typedef USB_HS_LockTypeDef        PCD_HS_LockTypeDef;
#endif /* defined (USB_OTG_HS) */

/**
  * @}
  */

/** @brief PCD Handle Structure definition
  * @{
  */
typedef struct
{
  PCD_HS_InitTypeDef           Init;       /*!< PCD required parameters   */
  __IO uint8_t                 USB_Address;/*!< USB Address               */
  PCD_HS_EPTypeDef             IN_ep[16];  /*!< IN endpoint parameters    */
  PCD_HS_EPTypeDef             OUT_ep[16]; /*!< OUT endpoint parameters   */
  PCD_HS_LockTypeDef           Lock;       /*!< PCD peripheral status     */
  __IO PCD_HS_StateTypeDef     State;      /*!< PCD communication state   */
  __IO  uint32_t               ErrorCode;  /*!< PCD Error code            */
  uint32_t                     Setup[2];   /*!< Setup packet buffer       */
  uint32_t                     FrameNumber;/*!< Store Current Frame number*/
  void                         *pData;     /*!< Pointer Stack Handler     */
} PCD_HS_HandleTypeDef;
/**
  * @}
  */

/* Include PCD Extended module */
#include "ft32f4xx_pcd_ex_hs.h"



/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup PCD_HS_Exported_Constants PCD Exported Constants
  * @{
  */

/** @defgroup PCD_Speed PCD Speed
  * @{
  */
#define PCD_SPEED_HIGH               USBD_HS_SPEED
#define PCD_SPEED_HIGH_IN_FULL       USBD_HSINFS_SPEED
#define PCD_SPEED_FULL               USBD_FS_SPEED
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PCD_HS_Exported_Macros PCD Exported Macros
  *  @brief macros to handle interrupts and specific clock configurations
  * @{
  */
#define __PCD_HS_ENABLE()                   (void)USB_HS_EnableGlobalInt ()
#define __PCD_HS_DISABLE()                  (void)USB_HS_DisableGlobalInt ()

#define __PCD_HS_GET_FLAG(__INTERRUPT__)      ((USB_HS_ReadInterrupts()\
                                                          & (__INTERRUPT__)) == (__INTERRUPT__))
#define __PCD_HS_GET_CH_FLAG(__chnum__, __INTERRUPT__)   \
                                                        ((USB_HS_ReadChInterrupts((__chnum__))\
                                                        & (__INTERRUPT__)) == (__INTERRUPT__))
#define __PCD_HS_CLEAR_FLAG(__INTERRUPT__)    ((USB_HS->GINTSTS) = (__INTERRUPT__))
#define __PCD_HS_IS_INVALID_INTERRUPT()         (USB_HS_ReadInterrupts() == 0U)

#define __PCD_HS_UNGATE_PHYCLOCK() \
  *(__IO uint32_t *)((uint32_t)OTG_HS_BASE + USB_OTG_HS_PCGCCTL_BASE) &= ~(OTG_HS_PCGCCTL_STOPCLK)

#define __PCD_HS_GATE_PHYCLOCK() \
  *(__IO uint32_t *)((uint32_t)OTG_HS_BASE + USB_OTG_HS_PCGCCTL_BASE) |= OTG_HS_PCGCCTL_STOPCLK

#define __PCD_HS_IS_PHY_SUSPENDED() \
  ((*(__IO uint32_t *)((uint32_t)OTG_HS_BASE + USB_OTG_HS_PCGCCTL_BASE)) & 0x10U)

#define __USB_OTG_HS_WAKEUP_EXTI_ENABLE_IT()    EXTI->IMR |= USB_OTG_HS_WAKEUP_EXTI_LINE
#define __USB_OTG_HS_WAKEUP_EXTI_DISABLE_IT()   EXTI->IMR &= ~(USB_OTG_HS_WAKEUP_EXTI_LINE)
#define __USB_OTG_HS_WAKEUP_EXTI_GET_FLAG()     EXTI->PR & (USB_OTG_HS_WAKEUP_EXTI_LINE)
#define __USB_OTG_HS_WAKEUP_EXTI_CLEAR_FLAG()   EXTI->PR = USB_OTG_HS_WAKEUP_EXTI_LINE

#define __USB_OTG_HS_WAKEUP_EXTI_ENABLE_RISING_EDGE() \
  do { \
    EXTI->FTSR &= ~(USB_OTG_HS_WAKEUP_EXTI_LINE); \
    EXTI->RTSR |= USB_OTG_HS_WAKEUP_EXTI_LINE; \
  } while(0U)


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup PCD_HS_Exported_Functions PCD Exported Functions
  * @{
  */

/** @defgroup PCD_HS_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
USB_HS_StatusTypeDef PCD_HS_Init(PCD_HS_HandleTypeDef *hpcd);
USB_HS_StatusTypeDef PCD_HS_DeInit(PCD_HS_HandleTypeDef *hpcd);

void              PCD_HS_MspInit(PCD_HS_HandleTypeDef *hpcd);
void              PCD_HS_MspDeInit(PCD_HS_HandleTypeDef *hpcd);

/**
  * @}
  */

/* I/O operation functions  ***************************************************/
/** @addtogroup PCD_Exported_Functions_Group2 Input and Output operation functions
  * @{
  */
USB_HS_StatusTypeDef PCD_HS_Start(PCD_HS_HandleTypeDef *hpcd);
USB_HS_StatusTypeDef PCD_HS_Stop(PCD_HS_HandleTypeDef *hpcd);

/* Non-Blocking mode: Interrupt */
void PCD_HS_IRQHandler(PCD_HS_HandleTypeDef *hpcd);
void PCD_HS_WKUP_IRQHandler(void);

void PCD_HS_SOFCallback(PCD_HS_HandleTypeDef *hpcd);
void PCD_HS_SetupStageCallback(PCD_HS_HandleTypeDef *hpcd);
void PCD_HS_ResetCallback(PCD_HS_HandleTypeDef *hpcd);
void PCD_HS_SuspendCallback(PCD_HS_HandleTypeDef *hpcd);
void PCD_HS_ResumeCallback(PCD_HS_HandleTypeDef *hpcd);
void PCD_HS_ConnectCallback(PCD_HS_HandleTypeDef *hpcd);
void PCD_HS_DisconnectCallback(PCD_HS_HandleTypeDef *hpcd);

void PCD_HS_DataOutStageCallback(PCD_HS_HandleTypeDef *hpcd, uint8_t epnum);
void PCD_HS_DataInStageCallback(PCD_HS_HandleTypeDef *hpcd, uint8_t epnum);
void PCD_HS_ISOOUTIncompleteCallback(PCD_HS_HandleTypeDef *hpcd, uint8_t epnum);
void PCD_HS_ISOINIncompleteCallback(PCD_HS_HandleTypeDef *hpcd, uint8_t epnum);
void USBD_SET_ADDR_Callback(PCD_HS_HandleTypeDef *hpcd);

/**
  * @}
  */

/* Peripheral Control functions  **********************************************/
/** @addtogroup PCD_HS_Exported_Functions_Group3 Peripheral Control functions
  * @{
  */
USB_HS_StatusTypeDef PCD_HS_DevConnect(PCD_HS_HandleTypeDef *hpcd);
USB_HS_StatusTypeDef PCD_HS_DevDisconnect(PCD_HS_HandleTypeDef *hpcd);
USB_HS_StatusTypeDef PCD_HS_SetAddress(PCD_HS_HandleTypeDef *hpcd, uint8_t address);
USB_HS_StatusTypeDef PCD_HS_EP_Open(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type);
USB_HS_StatusTypeDef PCD_HS_Ep_Close(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr);
void                 PCD_HS_Ep_Receive(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len);
void                 PCD_HS_Ep_Transmit(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len);
USB_HS_StatusTypeDef PCD_HS_EP_SetStall(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr);
USB_HS_StatusTypeDef PCD_HS_EP_ClrStall(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr);
USB_HS_StatusTypeDef PCD_HS_EP_Flush(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr);
USB_HS_StatusTypeDef PCD_HS_EP_Abort(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr);
void                 PCD_HS_ActivateRemoteWakeup(void);
void                 PCD_HS_DeActivateRemoteWakeup(void);

void                 PCD_HS_SetTestMode(uint8_t testmode);

uint32_t             PCD_HS_EP_GetRxCount(PCD_HS_HandleTypeDef const *hpcd, uint8_t ep_addr);
USB_HS_StatusTypeDef PCD_HS_EP_Close(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr);
void PCD_HS_EP_Transmit(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len);
void PCD_HS_EP_Receive(PCD_HS_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len);
/**
  * @}
  */

/* Peripheral State functions  ************************************************/
/** @addtogroup PCD_Exported_Functions_Group4 Peripheral State functions
  * @{
  */
PCD_HS_StateTypeDef PCD_HS_GetState(PCD_HS_HandleTypeDef const *hpcd);

/**
  * @}
  */
/* Private constants ---------------------------------------------------------*/
/** @defgroup PCD_Private_Constants PCD Private Constants
  * @{
  */
/** @defgroup USB_EXTI_Line_Interrupt USB EXTI line interrupt
  * @{
  */
#if defined (USB_OTG_HS)
#define USB_OTG_HS_WAKEUP_EXTI_LINE                                   (0x1U << 20)  /*!< USB HS EXTI Line WakeUp Interrupt */
#endif /* defined (USB_OTG_HS) */


/**
  * @}
  */


#if defined (USB_OTG_HS)
#ifndef USB_OTG_DOEPINT_OTEPSPR
#define USB_OTG_DOEPINT_OTEPSPR                (0x1UL << 5)      /*!< Status Phase Received interrupt */
#endif /* defined USB_OTG_DOEPINT_OTEPSPR */

#ifndef USB_OTG_DOEPMSK_OTEPSPRM
#define USB_OTG_DOEPMSK_OTEPSPRM               (0x1UL << 5)      /*!< Setup Packet Received interrupt mask */
#endif /* defined USB_OTG_DOEPMSK_OTEPSPRM */

#ifndef USB_OTG_DOEPINT_NAK
#define USB_OTG_DOEPINT_NAK                    (0x1UL << 13)      /*!< NAK interrupt */
#endif /* defined USB_OTG_DOEPINT_NAK */

#ifndef USB_OTG_DOEPMSK_NAKM
#define USB_OTG_DOEPMSK_NAKM                   (0x1UL << 13)      /*!< OUT Packet NAK interrupt mask */
#endif /* defined USB_OTG_DOEPMSK_NAKM */

#ifndef USB_OTG_DOEPINT_STPKTRX
#define USB_OTG_DOEPINT_STPKTRX                (0x1UL << 15)      /*!< Setup Packet Received interrupt */
#endif /* defined USB_OTG_DOEPINT_STPKTRX */

#ifndef USB_OTG_DOEPMSK_NYETM
#define USB_OTG_DOEPMSK_NYETM                  (0x1UL << 14)      /*!< Setup Packet Received interrupt mask */
#endif /* defined USB_OTG_DOEPMSK_NYETM */
#endif /* defined (USB_OTG_HS) */


/* Private constants ---------------------------------------------------------*/
/** @defgroup PCD_Private_Macros PCD Private Constants
  * @{
  */
/**
  * @}
  */

/**
  * @}
  */
#endif /* defined (USB_OTG_HS) */

#ifdef __cplusplus
}
#endif


#endif /* FT32F4XX_PCD_HS_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
