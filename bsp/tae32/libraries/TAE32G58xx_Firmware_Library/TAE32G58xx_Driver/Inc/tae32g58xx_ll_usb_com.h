/**
  ******************************************************************************
  * @file    tae32g58xx_ll_usb_com.h
  * @author  MCD Application Team
  * @brief   Header file for USB LL and USB Core Common
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32G58XX_LL_USB_COM_H_
#define _TAE32G58XX_LL_USB_COM_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup USB_LL_COM USB LL Common
  * @brief    USB LL Common
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/* Exported Types ------------------------------------------------------------*/
/** @defgroup USB_LL_COM_Exported_Types USB LL COM Exported Types
  * @brief    USB LL COM Exported Types
  * @{
  */

/**
  * @brief USB LL Common IRQ callback function type definition
  */
typedef void (*USB_LL_IRQCallback)(USB_TypeDef *Instance);


/**
  * @brief USB LL Common Endpoint Number Definition
  */
typedef enum {
    EP_NUM_0 = 0,       /*!< Endpoint Number 0          */
    EP_NUM_1,           /*!< Endpoint Number 1          */
    EP_NUM_2,           /*!< Endpoint Number 2          */
    EP_NUMS,            /*!< Endpoint Numbers           */
} USB_EpNumETypeDef;

/**
  * @brief USB LL Common Endpoint Type Definition
  */
typedef enum {
    EP_TYPE_CTRL = 0,   /*!< Endpoint Type Control      */
    EP_TYPE_ISOC,       /*!< Endpoint Type ISO          */
    EP_TYPE_BULK,       /*!< Endpoint Type BULK         */
    EP_TYPE_INT,        /*!< Endpoint Type Interrupt    */
} USB_EpTypeETypeDef;

/**
  * @brief USB LL Common Endpoint Diretion Definition
  */
typedef enum {
    EP_DIR_IN = 0,      /*!< Endpoint Diretion IN       */
    EP_DIR_OUT,         /*!< Endpoint Diretion OUT      */
} USB_EpDirETypeDef;


/**
  * @brief USB LL Common Endpoint Config Struct Definition
  */
typedef struct __USB_EpCfgTypeDef {
    USB_EpNumETypeDef  ep_num;              /*!< Endpoint Number                        */
    USB_EpDirETypeDef  ep_dir;              /*!< Endpoint Direction                     */
    USB_EpTypeETypeDef ep_type;             /*!< Endpoint Type                          */
    uint32_t           ep_max_pl;           /*!< Endpoint Max Payload                   */
} USB_EpCfgTypeDef;

/**
  * @brief USB LL Common IRQ Callback Definition
  */
typedef struct __USB_LL_IRQCbTypeDef {
    //Power Interrupt Callback
    USB_LL_IRQCallback PowerSuspend;        /*!< Power Suspend Interrupt Callback       */
    USB_LL_IRQCallback PowerResume;         /*!< Power Resume Interrupt Callback        */
    USB_LL_IRQCallback PowerReset;          /*!< Power Reset Interrupt Callback         */
    USB_LL_IRQCallback PowerSOF;            /*!< Power SOF Interrupt Callback           */
    USB_LL_IRQCallback PowerDisconn;        /*!< Power Disconnect Interrupt Callback    */

    //Detect Interrupt Callback
    USB_LL_IRQCallback DetInsert;           /*!< Detect Insert Interrupt Callback       */
    USB_LL_IRQCallback DetUnplug;           /*!< Detect Unplug Interrupt Callback       */

    //Endpoint Interrupt Callback
    USB_LL_IRQCallback Ep0Setup;            /*!< Endpoint 0 Setup Interrupt Callback    */
    USB_LL_IRQCallback EpxIn[EP_NUMS];      /*!< Endpoint X In Interrupt Callback       */
    USB_LL_IRQCallback EpxOut[EP_NUMS];     /*!< Endpoint X Out Interrupt Callback      */
} USB_LL_IRQCbTypeDef;

/**
  * @brief USB LL Common Driver Interface Struct Definition
  */
typedef struct __USB_LL_DrvTypeDef {
    //Endpoint Operation Interface
    LL_StatusETypeDef(*EpCfg)(USB_TypeDef *Instance, USB_EpCfgTypeDef *ep_cfg, bool ep_en);                     /*!< Ep Config      */
    LL_StatusETypeDef(*EpFIFOFlush)(USB_TypeDef *Instance, USB_EpNumETypeDef ep_num, USB_EpDirETypeDef ep_dir); /*!< Ep FIFO Flush  */
    uint32_t (*EpFIFORead)(USB_TypeDef *Instance, USB_EpNumETypeDef ep_num, uint8_t *buf, uint32_t len);        /*!< Ep FIFO Read   */
    uint32_t (*EpFIFOWrite)(USB_TypeDef *Instance, USB_EpNumETypeDef ep_num, uint8_t *buf, uint32_t len);       /*!< Ep FIFO Write  */

    //Setup Operation Interface
    void (*SetupStallSet)(USB_TypeDef *Instance);               /*!< Setup Stall Set    */
    void (*SetupStallClr)(USB_TypeDef *Instance);               /*!< Setup Stall Clear  */
    void (*SetupDataEndSet)(USB_TypeDef *Instance);             /*!< Setup Data End Set */
    void (*SetupAddrSet)(USB_TypeDef *Instance, uint8_t addr);  /*!< Setup Address Set  */
} USB_LL_DrvTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_USB_COM_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

