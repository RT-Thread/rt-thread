/**
  **************************************************************************
  * @file     usb_core.h
  * @brief    usb core header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CORE_H
#define __USB_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usb_std.h"

#ifdef USE_OTG_DEVICE_MODE
#include "usbd_core.h"
#endif
#ifdef USE_OTG_HOST_MODE
#include "usbh_core.h"
#endif

/** @addtogroup USB_drivers_core
  * @{
  */

/** @defgroup USB_core_exported_types
  * @{
  */

/**
  * @brief usb core speed select
  */
typedef enum
{
  USB_LOW_SPEED_CORE_ID,          /*!< usb low speed core id */
  USB_FULL_SPEED_CORE_ID,         /*!< usb full speed core id */
  USB_HIGH_SPEED_CORE_ID,         /*!< usb high speed core id */
} usb_speed_type;

/**
  * @brief usb core cofig struct
  */
typedef struct
{
  uint8_t                                speed;                     /*!< otg speed */
  uint8_t                                dma_en;                    /*!< dma enable state, not use*/
  uint8_t                                hc_num;                    /*!< the otg host support number of channel */
  uint8_t                                ept_num;                   /*!< the otg device support number of endpoint */

  uint16_t                               max_size;                  /*!< support max packet size */
  uint16_t                               fifo_size;                 /*!< the usb otg total file size */
  uint8_t                                phy_itface;                /*!< usb phy select */
  uint8_t                                core_id;                   /*!< the usb otg core id */
  uint8_t                                low_power;                 /*!< the usb otg low power option */
  uint8_t                                sof_out;                   /*!< the sof signal output */
  uint8_t                                usb_id;                    /*!< select otgfs1 or otgfs2 */
  uint8_t                                vbusig;                    /*!< vbus ignore */
} usb_core_cfg;

/**
  * @brief usb otg core struct type
  */
typedef struct
{
  usb_reg_type                           *usb_reg;                  /*!< the usb otg register type */
#ifdef USE_OTG_DEVICE_MODE
  usbd_core_type                         dev;                       /*!< the usb device core type */
#endif

#ifdef USE_OTG_HOST_MODE
  usbh_core_type                         host;                      /*!< the usb host core type */
#endif

  usb_core_cfg                           cfg;                       /*!< the usb otg core config type */

} otg_core_type;

usb_sts_type usb_core_config(otg_core_type *otgdev, uint8_t core_id);
#ifdef USE_OTG_DEVICE_MODE
usb_sts_type usbd_init(otg_core_type *udev,
                  uint8_t core_id, uint8_t usb_id);
#endif

#ifdef USE_OTG_HOST_MODE
usb_sts_type usbh_init(otg_core_type *hdev,
                  uint8_t core_id, uint8_t usb_id);
#endif

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif

