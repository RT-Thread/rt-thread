/**
  ******************************************************************************
  * @file    			ft32f4xx_hcd_hs.h
  * @author  			FMD XA
  * @brief   			This file contains all the functions prototypes for the
  *          >>->-USB_OTG_HS firmware library.
  * @version 			V1.0.0           
  * @data		 			2025-03-26
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_HCD_HS_H
#define __FT32F4XX_HCD_HS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_usb_hs.h"

#if defined (USB_OTG_HS)
/** @addtogroup ft32f4xx  Drive
  * @
  */

/** @addtogroup HCD_HS
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup HCD_HS_Exported_Types HCD Exported Types
  * @{
  */

/** @defgroup HCD_HS_Exported_Types_Group1 HCD State Structure definition
  * @{
  */
typedef enum
{
  HCD_HS_STATE_RESET    = 0x00,
  HCD_HS_STATE_READY    = 0x01,
  HCD_HS_STATE_ERROR    = 0x02,
  HCD_HS_STATE_BUSY     = 0x03,
  HCD_HS_STATE_TIMEOUT  = 0x04
} HCD_HS_StateTypeDef;

typedef USB_OTG_HS_GlobalTypeDef   HCD_HS_TypeDef;
typedef USB_OTG_HS_CfgTypeDef      HCD_HS_InitTypeDef;
typedef USB_OTG_HS_HCTypeDef       HCD_HS_HCTypeDef;
typedef USB_OTG_HS_URBStateTypeDef HCD_HS_URBStateTypeDef;
typedef USB_OTG_HS_HCStateTypeDef  HCD_HS_HCStateTypeDef;
typedef USB_HS_LockTypeDef         HCD_HS_LockTypeDef;
/**
  * @}
  */

/** @defgroup HCD_HS_Exported_Types_Group2 HCD Handle Structure definition
  * @{
  */
typedef struct
{
  HCD_HS_InitTypeDef           Init;       /*!< HCD required parameters  */
  HCD_HS_HCTypeDef             hc[16];     /*!< Host channels parameters */
  HCD_HS_LockTypeDef           Lock;       /*!< HCD peripheral status    */
  __IO HCD_HS_StateTypeDef     State;      /*!< HCD communication state  */
  __IO  uint32_t               ErrorCode;  /*!< HCD Error code           */
  void                         *pData;     /*!< Pointer Stack Handler    */
} HCD_HS_HandleTypeDef;
/**
  * @}
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup HCD_HS_Exported_Constants HCD Exported Constants
  * @{
  */

/** @defgroup HCD_Speed HCD Speed
  * @{
  */
#define HCD_SPEED_HIGH               USBH_HS_SPEED
#define HCD_SPEED_FULL               USBH_FSLS_SPEED
#define HCD_SPEED_LOW                USBH_FSLS_SPEED
/**
  * @}
  */

/** @defgroup HCD_Device_Speed HCD Device Speed
  * @{
  */
#define HCD_DEVICE_SPEED_HIGH         0U
#define HCD_DEVICE_SPEED_FULL         1U
#define HCD_DEVICE_SPEED_LOW          2U
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup HCD_HS_Exported_Macros HCD Exported Macros
  *  @brief macros to handle interrupts and specific clock configurations
  * @{
  */
#define __HCD_HS_ENABLE()                   (void)USB_HS_EnableGlobalInt ()
#define __HCD_HS_DISABLE()                  (void)USB_HS_DisableGlobalInt ()

#define __HCD_HS_GET_FLAG(__INTERRUPT__)      ((USB_HS_ReadInterrupts()\
                                                          & (__INTERRUPT__)) == (__INTERRUPT__))
#define __HCD_HS_GET_CH_FLAG(__chnum__, __INTERRUPT__)   \
                                                        ((USB_HS_ReadChInterrupts(__chnum__)\
                                                        & (__INTERRUPT__)) == (__INTERRUPT__))
#define __HCD_HS_CLEAR_FLAG(__INTERRUPT__)      ((USB_HS->GINTSTS) = (__INTERRUPT__))
#define __HCD_HS_IS_INVALID_INTERRUPT()         (USB_HS_ReadInterrupts() == 0U)

#define __HCD_HS_CLEAR_HC_INT(chnum, __INTERRUPT__)  (USB_HS_HC(chnum)->HCINT = (__INTERRUPT__))
#define __HCD_HS_MASK_HALT_HC_INT(chnum)             (USB_HS_HC(chnum)->HCINTMSK &= ~OTG_HS_HCINTMSK_CHHM)
#define __HCD_HS_UNMASK_HALT_HC_INT(chnum)           (USB_HS_HC(chnum)->HCINTMSK |= OTG_HS_HCINTMSK_CHHM)
#define __HCD_HS_MASK_ACK_HC_INT(chnum)              (USB_HS_HC(chnum)->HCINTMSK &= ~OTG_HS_HCINTMSK_ACKM)
#define __HCD_HS_UNMASK_ACK_HC_INT(chnum)            (USB_HS_HC(chnum)->HCINTMSK |= OTG_HS_HCINTMSK_ACKM)
#define __HCD_HS_SET_HC_CSPLT(chnum)                 (USB_HS_HC(chnum)->HCSPLT   |= OTG_HS_HCSPLT_COMPLSPLT)
#define __HCD_HS_CLEAR_HC_CSPLT(chnum)               (USB_HS_HC(chnum)->HCSPLT   &= ~OTG_HS_HCSPLT_COMPLSPLT)
#define __HCD_HS_CLEAR_HC_SSPLT(chnum)               (USB_HS_HC(chnum)->HCSPLT   &= ~OTG_HS_HCSPLT_SPLITEN)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HCD_HS_Exported_Functions HCD Exported Functions
  * @{
  */

/** @defgroup HCD_HS_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
USB_HS_StatusTypeDef HCD_HS_Init(HCD_HS_HandleTypeDef *hhcd);
USB_HS_StatusTypeDef HCD_HS_DeInit(HCD_HS_HandleTypeDef *hhcd);
USB_HS_StatusTypeDef HCD_HS_HC_Init(HCD_HS_HandleTypeDef *hhcd, uint8_t ch_num,
                                  uint8_t epnum, uint8_t dev_address,
                                  uint8_t speed, uint8_t ep_type, uint16_t mps);

USB_HS_StatusTypeDef HCD_HS_HC_Halt(HCD_HS_HandleTypeDef *hhcd, uint8_t ch_num);
void                 HCD_HS_MspInit(HCD_HS_HandleTypeDef *hhcd);
void                 HCD_HS_MspDeInit(HCD_HS_HandleTypeDef *hhcd);

/**
  * @}
  */

/* I/O operation functions  ***************************************************/
/** @addtogroup HCD_Exported_Functions_Group2 Input and Output operation functions
  * @{
  */
void HCD_HS_HC_SubmitRequest(HCD_HS_HandleTypeDef *hhcd, uint8_t ch_num,
                                           uint8_t direction, uint8_t ep_type,
                                           uint8_t token, uint8_t *pbuff,
                                           uint16_t length, uint8_t do_ping);

void HCD_HS_HC_SetHubInfo(HCD_HS_HandleTypeDef *hhcd, uint8_t ch_num,
                                           uint8_t addr, uint8_t PortNbr);


void HCD_HS_HC_ClearHubInfo(HCD_HS_HandleTypeDef *hhcd, uint8_t ch_num);

/* Non-Blocking mode: Interrupt */
void HCD_HS_IRQHandler(HCD_HS_HandleTypeDef *hhcd);
void HCD_HS_WKUP_IRQHandler(HCD_HS_HandleTypeDef *hhcd);
void HCD_HS_SOF_Callback(HCD_HS_HandleTypeDef *hhcd);
void HCD_HS_Connect_Callback(HCD_HS_HandleTypeDef *hhcd);
void HCD_HS_Disconnect_Callback(HCD_HS_HandleTypeDef *hhcd);
void HCD_HS_PortEnabled_Callback(HCD_HS_HandleTypeDef *hhcd);
void HCD_HS_PortDisabled_Callback(HCD_HS_HandleTypeDef *hhcd);
void HCD_HS_HC_NotifyURBChange_Callback(HCD_HS_HandleTypeDef *hhcd, uint8_t chnum,
                                         HCD_HS_URBStateTypeDef urb_state);
/**
  * @}
  */

/* Peripheral Control functions  **********************************************/
/** @addtogroup HCD_HS_Exported_Functions_Group3 Peripheral Control functions
  * @{
  */
void                 HCD_HS_ResetPort(void);
USB_HS_StatusTypeDef HCD_HS_Start(HCD_HS_HandleTypeDef *hhcd);
USB_HS_StatusTypeDef HCD_HS_Stop(HCD_HS_HandleTypeDef *hhcd);
/**
  * @}
  */

/* Peripheral State functions  ************************************************/
/** @addtogroup HCD_Exported_Functions_Group4 Peripheral State functions
  * @{
  */
HCD_HS_StateTypeDef     HCD_HS_GetState(HCD_HS_HandleTypeDef *hhcd);
HCD_HS_URBStateTypeDef  HCD_HS_HC_GetURBState(HCD_HS_HandleTypeDef *hhcd, uint8_t chnum);
HCD_HS_HCStateTypeDef   HCD_HS_HC_GetState(HCD_HS_HandleTypeDef *hhcd, uint8_t chnum);
uint32_t                HCD_HS_HC_GetXferCount(HCD_HS_HandleTypeDef *hhcd, uint8_t chnum);
uint32_t                HCD_HS_GetCurrentFrame(void);
uint32_t                HCD_HS_GetCurrentSpeed(void);

/**
  * @}
  */

/**
  * @}
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


#endif /* FT32F4XX_HCD_HS_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
