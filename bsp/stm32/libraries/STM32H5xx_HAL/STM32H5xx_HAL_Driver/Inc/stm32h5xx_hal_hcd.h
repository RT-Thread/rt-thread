/**
  ******************************************************************************
  * @file    stm32h5xx_hal_hcd.h
  * @author  MCD Application Team
  * @brief   Header file of HCD HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H5xx_HAL_HCD_H
#define STM32H5xx_HAL_HCD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_ll_usb.h"

#if defined (USB_DRD_FS)
/** @addtogroup STM32H5xx_HAL_Driver
  * @{
  */

/** @addtogroup HCD HCD
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup HCD_Exported_Types HCD Exported Types
  * @{
  */

/** @defgroup HCD_Exported_Types_Group1 HCD State Structure definition
  * @{
  */
typedef enum
{
  HAL_HCD_STATE_RESET    = 0x00,
  HAL_HCD_STATE_READY    = 0x01,
  HAL_HCD_STATE_ERROR    = 0x02,
  HAL_HCD_STATE_BUSY     = 0x03,
  HAL_HCD_STATE_TIMEOUT  = 0x04
} HCD_StateTypeDef;

typedef USB_DRD_TypeDef         HCD_TypeDef;
typedef USB_DRD_CfgTypeDef      HCD_InitTypeDef;
typedef USB_DRD_HCTypeDef       HCD_HCTypeDef;
typedef USB_DRD_URBStateTypeDef HCD_URBStateTypeDef;
typedef USB_DRD_HCStateTypeDef  HCD_HCStateTypeDef;

typedef enum
{
  HCD_HCD_STATE_DISCONNECTED = 0x00U,
  HCD_HCD_STATE_CONNECTED    = 0x01U,
  HCD_HCD_STATE_RESETED      = 0x02U,
  HCD_HCD_STATE_RUN          = 0x03U,
  HCD_HCD_STATE_SUSPEND      = 0x04U,
  HCD_HCD_STATE_RESUME       = 0x05U,
} HCD_HostStateTypeDef;

/* PMA lookup Table size depending on PMA Size
 * 8Bytes each Block 32Bit in each word
 */
#define PMA_BLOCKS        ((USB_DRD_PMA_SIZE) / (8U * 32U))

/**
  * @}
  */

/** @defgroup HCD_Exported_Types_Group2 HCD Handle Structure definition
  * @{
  */
#if (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
typedef struct __HCD_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
{
  HCD_TypeDef               *Instance;  /*!< Register base address    */
  HCD_InitTypeDef           Init;       /*!< HCD required parameters  */
  HCD_HCTypeDef             hc[16];     /*!< Host channels parameters */

  uint32_t                  ep0_PmaAllocState;  /*!< EP0 PMA allocation State (allocated, virtual Ch, EP0 direction) */
  uint16_t                  phy_chin_state[8];  /*!< Physical Channel in State (Used/Free) */
  uint16_t                  phy_chout_state[8]; /*!< Physical Channel out State (Used/Free)*/
  uint32_t                  PMALookupTable[PMA_BLOCKS]; /*PMA LookUp Table */
  HCD_HostStateTypeDef      HostState; /*!< USB current state DICONNECT/CONNECT/RUN/SUSPEND/RESUME */

  HAL_LockTypeDef           Lock;       /*!< HCD peripheral status    */
  __IO HCD_StateTypeDef     State;      /*!< HCD communication state  */
  __IO  uint32_t            ErrorCode;  /*!< HCD Error code           */
  void                      *pData;     /*!< Pointer Stack Handler    */
#if (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
  void (* SOFCallback)(struct __HCD_HandleTypeDef *hhcd);                               /*!< USB OTG HCD SOF callback                */
  void (* ConnectCallback)(struct __HCD_HandleTypeDef *hhcd);                           /*!< USB OTG HCD Connect callback            */
  void (* DisconnectCallback)(struct __HCD_HandleTypeDef *hhcd);                        /*!< USB OTG HCD Disconnect callback         */
  void (* PortEnabledCallback)(struct __HCD_HandleTypeDef *hhcd);                       /*!< USB OTG HCD Port Enable callback        */
  void (* PortDisabledCallback)(struct __HCD_HandleTypeDef *hhcd);                      /*!< USB OTG HCD Port Disable callback       */
  void (* HC_NotifyURBChangeCallback)(struct __HCD_HandleTypeDef *hhcd, uint8_t chnum,
                                      HCD_URBStateTypeDef urb_state);                   /*!< USB OTG HCD Host Channel Notify URB Change callback  */

  void (* MspInitCallback)(struct __HCD_HandleTypeDef *hhcd);                           /*!< USB OTG HCD Msp Init callback           */
  void (* MspDeInitCallback)(struct __HCD_HandleTypeDef *hhcd);                         /*!< USB OTG HCD Msp DeInit callback         */
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
} HCD_HandleTypeDef;
/**
  * @}
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup HCD_Exported_Constants HCD Exported Constants
  * @{
  */

/** @defgroup HCD_Speed HCD Speed
  * @{
  */
#define HCD_SPEED_FULL               USBH_FSLS_SPEED
#define HCD_SPEED_LOW                USBH_FSLS_SPEED
/**
  * @}
  */

/** @defgroup HCD_Device_Speed HCD Device Speed
  * @{
  */
#define HCD_DEVICE_SPEED_HIGH               0U
#define HCD_DEVICE_SPEED_FULL               1U
#define HCD_DEVICE_SPEED_LOW                2U
/**
  * @}
  */

/** @defgroup HCD_PHY_Module HCD PHY Module
  * @{
  */
#define HCD_PHY_ULPI                 1U
#define HCD_PHY_EMBEDDED             2U
/**
  * @}
  */

/** @defgroup HCD_Error_Code_definition HCD Error Code definition
  * @brief  HCD Error Code definition
  * @{
  */
#if (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
#define  HAL_HCD_ERROR_INVALID_CALLBACK                        (0x00000010U)    /*!< Invalid Callback error  */
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup HCD_Exported_Macros HCD Exported Macros
  *  @brief macros to handle interrupts and specific clock configurations
  * @{
  */
#define __HAL_HCD_ENABLE(__HANDLE__)                   (void)USB_EnableGlobalInt ((__HANDLE__)->Instance)
#define __HAL_HCD_DISABLE(__HANDLE__)                  (void)USB_DisableGlobalInt ((__HANDLE__)->Instance)

#define __HAL_HCD_GET_FLAG(__HANDLE__, __INTERRUPT__)      ((USB_ReadInterrupts((__HANDLE__)->Instance)\
                                                             & (__INTERRUPT__)) == (__INTERRUPT__))
#define __HAL_HCD_CLEAR_FLAG(__HANDLE__, __INTERRUPT__)    (((__HANDLE__)->Instance->ISTR) &= ~(__INTERRUPT__))
#define __HAL_HCD_IS_INVALID_INTERRUPT(__HANDLE__)         (USB_ReadInterrupts((__HANDLE__)->Instance) == 0U)

#define __HAL_HCD_GET_CHNUM(__HANDLE__)                    (((__HANDLE__)->Instance->ISTR) & USB_ISTR_IDN)
#define __HAL_HCD_GET_CHDIR(__HANDLE__)                    (((__HANDLE__)->Instance->ISTR) & USB_ISTR_DIR)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HCD_Exported_Functions HCD Exported Functions
  * @{
  */

/** @defgroup HCD_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
HAL_StatusTypeDef HAL_HCD_Init(HCD_HandleTypeDef *hhcd);
HAL_StatusTypeDef HAL_HCD_DeInit(HCD_HandleTypeDef *hhcd);
HAL_StatusTypeDef HAL_HCD_HC_Init(HCD_HandleTypeDef *hhcd, uint8_t ch_num,
                                  uint8_t epnum, uint8_t dev_address,
                                  uint8_t speed, uint8_t ep_type, uint16_t mps);

HAL_StatusTypeDef HAL_HCD_HC_Halt(HCD_HandleTypeDef *hhcd, uint8_t ch_num);

HAL_StatusTypeDef HAL_HCD_HC_Close(HCD_HandleTypeDef *hhcd, uint8_t ch_num);

void              HAL_HCD_MspInit(HCD_HandleTypeDef *hhcd);
void              HAL_HCD_MspDeInit(HCD_HandleTypeDef *hhcd);

#if (USE_HAL_HCD_REGISTER_CALLBACKS == 1U)
/** @defgroup HAL_HCD_Callback_ID_enumeration_definition HAL USB OTG HCD Callback ID enumeration definition
  * @brief  HAL USB OTG HCD Callback ID enumeration definition
  * @{
  */
typedef enum
{
  HAL_HCD_SOF_CB_ID            = 0x01,       /*!< USB HCD SOF callback ID           */
  HAL_HCD_CONNECT_CB_ID        = 0x02,       /*!< USB HCD Connect callback ID       */
  HAL_HCD_DISCONNECT_CB_ID     = 0x03,       /*!< USB HCD Disconnect callback ID    */
  HAL_HCD_PORT_ENABLED_CB_ID   = 0x04,       /*!< USB HCD Port Enable callback ID   */
  HAL_HCD_PORT_DISABLED_CB_ID  = 0x05,       /*!< USB HCD Port Disable callback ID  */

  HAL_HCD_MSPINIT_CB_ID        = 0x06,       /*!< USB HCD MspInit callback ID       */
  HAL_HCD_MSPDEINIT_CB_ID      = 0x07        /*!< USB HCD MspDeInit callback ID     */

} HAL_HCD_CallbackIDTypeDef;
/**
  * @}
  */

/** @defgroup HAL_HCD_Callback_pointer_definition HAL USB OTG HCD Callback pointer definition
  * @brief  HAL USB OTG HCD Callback pointer definition
  * @{
  */

typedef void (*pHCD_CallbackTypeDef)(HCD_HandleTypeDef *hhcd);                   /*!< pointer to a common USB OTG HCD callback function  */
typedef void (*pHCD_HC_NotifyURBChangeCallbackTypeDef)(HCD_HandleTypeDef *hhcd,
                                                       uint8_t epnum,
                                                       HCD_URBStateTypeDef urb_state);   /*!< pointer to USB OTG HCD host channel  callback */
/**
  * @}
  */

HAL_StatusTypeDef HAL_HCD_RegisterCallback(HCD_HandleTypeDef *hhcd,
                                           HAL_HCD_CallbackIDTypeDef CallbackID,
                                           pHCD_CallbackTypeDef pCallback);

HAL_StatusTypeDef HAL_HCD_UnRegisterCallback(HCD_HandleTypeDef *hhcd,
                                             HAL_HCD_CallbackIDTypeDef CallbackID);

HAL_StatusTypeDef HAL_HCD_RegisterHC_NotifyURBChangeCallback(HCD_HandleTypeDef *hhcd,
                                                             pHCD_HC_NotifyURBChangeCallbackTypeDef pCallback);

HAL_StatusTypeDef HAL_HCD_UnRegisterHC_NotifyURBChangeCallback(HCD_HandleTypeDef *hhcd);
#endif /* USE_HAL_HCD_REGISTER_CALLBACKS */
/**
  * @}
  */

/* I/O operation functions  ***************************************************/
/** @addtogroup HCD_Exported_Functions_Group2 Input and Output operation functions
  * @{
  */
HAL_StatusTypeDef HAL_HCD_HC_SubmitRequest(HCD_HandleTypeDef *hhcd, uint8_t ch_num,
                                           uint8_t direction, uint8_t ep_type,
                                           uint8_t token, uint8_t *pbuff,
                                           uint16_t length, uint8_t do_ping);

HAL_StatusTypeDef HAL_HCD_HC_SetHubInfo(HCD_HandleTypeDef *hhcd, uint8_t ch_num,
                                        uint8_t addr, uint8_t PortNbr);

HAL_StatusTypeDef HAL_HCD_HC_ClearHubInfo(HCD_HandleTypeDef *hhcd, uint8_t ch_num);

/* Non-Blocking mode: Interrupt */
void HAL_HCD_IRQHandler(HCD_HandleTypeDef *hhcd);
void HAL_HCD_SOF_Callback(HCD_HandleTypeDef *hhcd);
void HAL_HCD_Connect_Callback(HCD_HandleTypeDef *hhcd);
void HAL_HCD_Disconnect_Callback(HCD_HandleTypeDef *hhcd);
void HAL_HCD_PortEnabled_Callback(HCD_HandleTypeDef *hhcd);
void HAL_HCD_PortDisabled_Callback(HCD_HandleTypeDef *hhcd);

void HAL_HCD_SuspendCallback(HCD_HandleTypeDef *hhcd);
void HAL_HCD_ResumeCallback(HCD_HandleTypeDef *hhcd);

void HAL_HCD_HC_NotifyURBChange_Callback(HCD_HandleTypeDef *hhcd, uint8_t chnum,
                                         HCD_URBStateTypeDef urb_state);
/**
  * @}
  */

/* Peripheral Control functions  **********************************************/
/** @addtogroup HCD_Exported_Functions_Group3 Peripheral Control functions
  * @{
  */
HAL_StatusTypeDef HAL_HCD_ResetPort(HCD_HandleTypeDef *hhcd);
HAL_StatusTypeDef HAL_HCD_Start(HCD_HandleTypeDef *hhcd);
HAL_StatusTypeDef HAL_HCD_Stop(HCD_HandleTypeDef *hhcd);

HAL_StatusTypeDef HAL_HCD_Suspend(HCD_HandleTypeDef *hhcd);
HAL_StatusTypeDef HAL_HCD_Resume(HCD_HandleTypeDef *hhcd);
HAL_StatusTypeDef HAL_HCD_ResumePort(HCD_HandleTypeDef *hhcd);

/**
  * @}
  */

/* Peripheral State functions  ************************************************/
/** @addtogroup HCD_Exported_Functions_Group4 Peripheral State functions
  * @{
  */
HCD_StateTypeDef        HAL_HCD_GetState(HCD_HandleTypeDef const *hhcd);
HCD_URBStateTypeDef     HAL_HCD_HC_GetURBState(HCD_HandleTypeDef const *hhcd, uint8_t chnum);
HCD_HCStateTypeDef      HAL_HCD_HC_GetState(HCD_HandleTypeDef const *hhcd, uint8_t chnum);
uint32_t                HAL_HCD_HC_GetXferCount(HCD_HandleTypeDef const *hhcd, uint8_t chnum);
uint32_t                HAL_HCD_GetCurrentFrame(HCD_HandleTypeDef *hhcd);
uint32_t                HAL_HCD_GetCurrentSpeed(HCD_HandleTypeDef *hhcd);


/* PMA Allocation functions  **********************************************/
/** @addtogroup PMA Allocation
  * @{
  */
HAL_StatusTypeDef  HAL_HCD_PMAlloc(HCD_HandleTypeDef *hhcd, uint8_t ch_num,
                                   uint16_t ch_kind, uint16_t mps);

HAL_StatusTypeDef  HAL_HCD_PMADeAlloc(HCD_HandleTypeDef *hhcd, uint8_t ch_num);
HAL_StatusTypeDef  HAL_HCD_PMAReset(HCD_HandleTypeDef *hhcd);

/**
  * @}
  */


/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup HCD_Private_Macros HCD Private Macros
  * @{
  */

#define HCD_MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define HCD_MAX(a, b)  (((a) > (b)) ? (a) : (b))

/** @defgroup HCD_LOGICAL_CHANNEL HCD Logical Channel
  * @{
  */
#define HCD_LOGICAL_CH_NOT_OPENED             0xFFU
#define HCD_FREE_CH_NOT_FOUND                 0xFFU
/**
  * @}
  */

/** @defgroup HCD_ENDP_Kind HCD Endpoint Kind
  * @{
  */
#define HCD_SNG_BUF                            0U
#define HCD_DBL_BUF                            1U
/**
  * @}
  */

/* Set Channel */
#define HCD_SET_CHANNEL                        USB_DRD_SET_CHEP

/* Get Channel Register */
#define HCD_GET_CHANNEL                        USB_DRD_GET_CHEP


/**
  * @brief free buffer used from the application realizing it to the line
  *         toggles bit SW_BUF in the double buffered endpoint register
  * @param USBx USB device.
  * @param   bChNum, bDir
  * @retval None
  */
#define HCD_FREE_USER_BUFFER                   USB_DRD_FREE_USER_BUFFER

/**
  * @brief Set the Setup bit in the corresponding channel, when a Setup
     transaction is needed.
  * @param USBx USB device.
  * @param   bChNum
  * @retval None
  */
#define HAC_SET_CH_TX_SETUP                    USB_DRD_CHEP_TX_SETUP

/**
  * @brief  sets the status for tx transfer (bits STAT_TX[1:0]).
  * @param  USBx USB peripheral instance register address.
  * @param  bChNum Endpoint Number.
  * @param  wState new state
  * @retval None
  */
#define HCD_SET_CH_TX_STATUS                   USB_DRD_SET_CHEP_TX_STATUS

/**
  * @brief  sets the status for rx transfer (bits STAT_TX[1:0])
  * @param  USBx USB peripheral instance register address.
  * @param  bChNum Endpoint Number.
  * @param  wState new state
  * @retval None
  */
#define HCD_SET_CH_RX_STATUS                   USB_DRD_SET_CHEP_RX_STATUS
/**
  * @brief  gets the status for tx/rx transfer (bits STAT_TX[1:0]
  *         /STAT_RX[1:0])
  * @param  USBx USB peripheral instance register address.
  * @param  bChNum Endpoint Number.
  * @retval status
  */
#define HCD_GET_CH_TX_STATUS                   USB_DRD_GET_CHEP_TX_STATUS
#define HCD_GET_CH_RX_STATUS                   USB_DRD_GET_CHEP_RX_STATUS
/**
  * @brief  Sets/clears CH_KIND bit in the Channel register.
  * @param  USBx USB peripheral instance register address.
  * @param  bChNum Endpoint Number.
  * @retval None
  */
#define HCD_SET_CH_KIND                        USB_DRD_SET_CH_KIND
#define HCD_CLEAR_CH_KIND                      USB_DRD_CLEAR_CH_KIND
#define HCD_SET_BULK_CH_DBUF                   HCD_SET_CH_KIND
#define HCD_CLEAR_BULK_CH_DBUF                 HCD_CLEAR_CH_KIND

/**
  * @brief  Clears bit ERR_RX in the Channel register
  * @param  USBx USB peripheral instance register address.
  * @param  bChNum Endpoint Number.
  * @retval None
  */
#define HCD_CLEAR_RX_CH_ERR                    USB_DRD_CLEAR_CHEP_RX_ERR

/**
  * @brief  Clears bit ERR_TX in the Channel register
  * @param  USBx USB peripheral instance register address.
  * @param  bChNum Endpoint Number.
  * @retval None
  */
#define HCD_CLEAR_TX_CH_ERR                    USB_DRD_CLEAR_CHEP_TX_ERR
/**
  * @brief  Clears bit CTR_RX / CTR_TX in the endpoint register.
  * @param  USBx USB peripheral instance register address.
  * @param  bChNum Endpoint Number.
  * @retval None
  */
#define HCD_CLEAR_RX_CH_CTR                    USB_DRD_CLEAR_RX_CHEP_CTR
#define HCD_CLEAR_TX_CH_CTR                    USB_DRD_CLEAR_TX_CHEP_CTR

/**
  * @brief  Toggles DTOG_RX / DTOG_TX bit in the endpoint register.
  * @param  USBx USB peripheral instance register address.
  * @param  bChNum Endpoint Number.
  * @retval None
  */
#define HCD_RX_DTOG                            USB_DRD_RX_DTOG
#define HCD_TX_DTOG                            USB_DRD_TX_DTOG
/**
  * @brief  Clears DTOG_RX / DTOG_TX bit in the endpoint register.
  * @param  USBx USB peripheral instance register address.
  * @param  bChNum Endpoint Number.
  * @retval None
  */
#define HCD_CLEAR_RX_DTOG                      USB_DRD_CLEAR_RX_DTOG
#define HCD_CLEAR_TX_DTOG                      USB_DRD_CLEAR_TX_DTOG

/**
  * @brief  sets counter for the tx/rx buffer.
  * @param  USBx USB peripheral instance register address.
  * @param  bChNum Endpoint Number.
  * @param  wCount Counter value.
  * @retval None
  */
#define HCD_SET_CH_TX_CNT                      USB_DRD_SET_CHEP_TX_CNT
#define HCD_SET_CH_RX_CNT                      USB_DRD_SET_CHEP_RX_CNT

/**
  * @brief  gets counter of the tx buffer.
  * @param  USBx USB peripheral instance register address.
  * @param  bChNum channel Number.
  * @retval Counter value
  */
#define HCD_GET_CH_TX_CNT                      USB_DRD_GET_CHEP_TX_CNT

/**
  * @brief  gets counter of the rx buffer.
  * @param  Instance USB peripheral instance register address.
  * @param  bChNum channel Number.
  * @retval Counter value
  */
__STATIC_INLINE uint16_t HCD_GET_CH_RX_CNT(HCD_TypeDef *Instance, uint16_t bChNum)
{
  uint32_t HostCoreSpeed;
  __IO uint32_t count = 10U;

  /* Get Host core Speed */
  HostCoreSpeed = USB_GetHostSpeed(Instance);

  /* Count depends on device LS */
  if (HostCoreSpeed == USB_DRD_SPEED_LS)
  {
    count = (63U * (HAL_RCC_GetHCLKFreq() / 1000000U)) / 100U;
  }

  if (count > 15U)
  {
    count = HCD_MAX(10U, (count - 15U));
  }

  /* WA: few cycles for RX PMA descriptor to update */
  while (count > 0U)
  {
    count--;
  }

  return (uint16_t)USB_DRD_GET_CHEP_RX_CNT((Instance), (bChNum));
}

/**
  * @brief  Gets buffer 0/1 address of a double buffer endpoint.
  * @param  USBx USB peripheral instance register address.
  * @param  bChNum Endpoint Number.
  * @param  bDir endpoint dir  EP_DBUF_OUT = OUT
  *         EP_DBUF_IN  = IN
  * @param  wCount: Counter value
  * @retval None
  */
#define HCD_SET_CH_DBUF0_CNT                   USB_DRD_SET_CHEP_DBUF0_CNT
#define HCD_SET_CH_DBUF1_CNT                   USB_DRD_SET_CHEP_DBUF1_CNT
#define HCD_SET_CH_DBUF_CNT                    USB_DRD_SET_CHEP_DBUF_CNT


/**
  * @brief  gets counter of the rx buffer0.
  * @param  Instance USB peripheral instance register address.
  * @param  bChNum channel Number.
  * @retval Counter value
  */
__STATIC_INLINE uint16_t HCD_GET_CH_DBUF0_CNT(const HCD_TypeDef *Instance, uint16_t bChNum)
{
  UNUSED(Instance);
  __IO uint32_t count = 10U;

  /* WA: few cycles for RX PMA descriptor to update */
  while (count > 0U)
  {
    count--;
  }

  return (uint16_t)USB_DRD_GET_CHEP_DBUF0_CNT((Instance), (bChNum));
}

/**
  * @brief  gets counter of the rx buffer1.
  * @param  Instance USB peripheral instance register address.
  * @param  bChNum channel Number.
  * @retval Counter value
  */
__STATIC_INLINE uint16_t HCD_GET_CH_DBUF1_CNT(const HCD_TypeDef *Instance, uint16_t bChNum)
{
  UNUSED(Instance);
  __IO uint32_t count = 10U;

  /* WA: few cycles for RX PMA descriptor to update */
  while (count > 0U)
  {
    count--;
  }

  return (uint16_t)USB_DRD_GET_CHEP_DBUF1_CNT((Instance), (bChNum));
}


/**
  * @}
  */
/* Private functions prototypes ----------------------------------------------*/

/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
#endif /* defined (USB_DRD_FS) */

#ifdef __cplusplus
}
#endif

#endif /* STM32H5xx_HAL_HCD_H */
