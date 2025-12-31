/**
  ******************************************************************************
  * @file    			ft32f4xx_hcd_fs.h
  * @author  			FMD XA
  * @brief   			This file contains all the functions prototypes for the
  *          >>->-USB_OTG_FS firmware library.
  * @version 			V1.0.0           
  * @data		 			2025-05-28
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_HCD_FS_H
#define __FT32F4XX_HCD_FS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_usb_fs.h"

#if defined (USB_OTG_FS)

/* Exported types ------------------------------------------------------------*/

typedef enum
{
  HCD_FS_STATE_RESET    = 0x00,
  HCD_FS_STATE_READY    = 0x01,
  HCD_FS_STATE_ERROR    = 0x02,
  HCD_FS_STATE_BUSY     = 0x03,
  HCD_FS_STATE_TIMEOUT  = 0x04,
} HCD_FS_StateTypeDef;


typedef USB_OTG_FS_CfgTypeDef      HCD_FS_InitTypeDef;
typedef USB_OTG_FS_HEPTypeDef      HCD_FS_EPTypeDef;
typedef USB_OTG_FS_URBStateTypeDef HCD_FS_URBStateTypeDef;
typedef USB_OTG_FS_HEPStateTypeDef HCD_FS_EPStateTypeDef;
typedef USB_FS_LockTypeDef         HCD_FS_LockTypeDef;

/**
  * @}
  */

typedef struct
{
  HCD_FS_InitTypeDef           Init;       /*!< HCD required parameters  */
  HCD_FS_EPTypeDef             ep[16];     /*!< Host endpoint parameters */
  HCD_FS_LockTypeDef           Lock;       /*!< HCD peripheral status    */
  __IO HCD_FS_StateTypeDef     State;      /*!< HCD communication state  */
  __IO  uint32_t               ErrorCode;  /*!< HCD Error code           */
  __IO  uint32_t               cur_ep;     /*!< host current used ep pipe*/
  void                         *pData;     /*!< Pointer Stack Handler    */
} HCD_FS_HandleTypeDef;
/**
  * @}
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup HCD_Speed HCD Speed
  * @{
  */
#define HCD_SPEED_FULL               USB_FS_SPEED
#define HCD_SPEED_LOW                USB_LS_SPEED
/**
  * @}
  */

/** @defgroup HCD_Device_Speed HCD Device Speed
  * @{
  */
#define HCD_DEVICE_SPEED_FULL         0U
#define HCD_DEVICE_SPEED_LOW          1U
/**
  * @}
  */


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

USB_FS_StatusTypeDef HCD_FS_Init(HCD_FS_HandleTypeDef *hhcd);
USB_FS_StatusTypeDef HCD_FS_DeInit(HCD_FS_HandleTypeDef *hhcd);
USB_FS_StatusTypeDef HCD_FS_EP_Init(HCD_FS_HandleTypeDef *hhcd, uint8_t pipe,
                                    uint8_t epnum, uint8_t dev_address,
                                    uint8_t speed, uint8_t ep_type,
                                    uint16_t mps);

void                 HCD_FS_MspInit(HCD_FS_HandleTypeDef *hhcd);
void                 HCD_FS_MspDeInit(HCD_FS_HandleTypeDef *hhcd);

/**
  * @}
  */

/* I/O operation functions  ***************************************************/
void HCD_FS_EP_SubmitRequest(HCD_FS_HandleTypeDef *hhcd, uint8_t ep_num,
                             uint8_t direction, uint8_t ep_type,
                             uint8_t token, uint8_t *pbuff,
                             uint16_t length, uint8_t ctl_state);

/* Non-Blocking mode: Interrupt */
void HCD_FS_IRQHandler(HCD_FS_HandleTypeDef *hhcd);
void HCD_FS_WKUP_IRQHandler(HCD_FS_HandleTypeDef *hhcd);
void HCD_FS_SOF_Callback(HCD_FS_HandleTypeDef *hhcd);
void HCD_FS_VBusErr_Callback(HCD_FS_HandleTypeDef *hhcd);
void HCD_FS_Session_Callback(HCD_FS_HandleTypeDef *hhcd);
void HCD_FS_Babble_Callback(HCD_FS_HandleTypeDef *hhcd);
void HCD_FS_Resume_Callback(HCD_FS_HandleTypeDef *hhcd);
void HCD_FS_Connect_Callback(HCD_FS_HandleTypeDef *hhcd);
void HCD_FS_Disconnect_Callback(HCD_FS_HandleTypeDef *hhcd);
void HCD_FS_EP_NotifyURBChange_Callback(HCD_FS_HandleTypeDef *hhcd, uint8_t epnum,
                                        HCD_FS_URBStateTypeDef urb_state);



/* Peripheral Control functions  **********************************************/
void                 HCD_FS_ResetPort(void);
USB_FS_StatusTypeDef HCD_FS_Start(HCD_FS_HandleTypeDef *hhcd);
USB_FS_StatusTypeDef HCD_FS_Stop(HCD_FS_HandleTypeDef *hhcd);


/* Peripheral State functions  ************************************************/
HCD_FS_StateTypeDef     HCD_FS_GetState(HCD_FS_HandleTypeDef *hhcd);
HCD_FS_URBStateTypeDef  HCD_FS_EP_GetURBState(HCD_FS_HandleTypeDef *hhcd, uint8_t ep_num);
HCD_FS_EPStateTypeDef   HCD_FS_EP_GetState(HCD_FS_HandleTypeDef *hhcd, uint8_t ep_num);
uint32_t                HCD_FS_EP_GetXferCount(HCD_FS_HandleTypeDef *hhcd, uint8_t ep_num);
uint32_t                HCD_FS_GetCurrEp(HCD_FS_HandleTypeDef *hhcd);
uint32_t                HCD_FS_GetCurrentFrame(void);
uint32_t                HCD_FS_GetCurrentSpeed(void);


#endif /* defined (USB_OTG_FS) */

#ifdef __cplusplus
}
#endif


#endif /* FT32F4XX_HCD_FS_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
