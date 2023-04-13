/**
  **************************************************************************
  * @file     usbh_int.h
  * @brief    usb header file
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
#ifndef __USBH_INT_H
#define __USBH_INT_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "usbh_core.h"
#include "usb_core.h"

/** @addtogroup USBH_drivers_int
  * @{
  */

/** @defgroup USBH_interrupt_exported_types
  * @{
  */

#ifdef USE_OTG_HOST_MODE

void usbh_irq_handler(otg_core_type *hdev);
void usbh_hch_handler(usbh_core_type *uhost);
void usbh_port_handler(usbh_core_type *uhost);
void usbh_disconnect_handler(usbh_core_type *uhost);
void usbh_hch_in_handler(usbh_core_type *uhost, uint8_t chn);
void usbh_hch_out_handler(usbh_core_type *uhost, uint8_t chn);
void usbh_rx_qlvl_handler(usbh_core_type *uhost);
void usbh_wakeup_handler(usbh_core_type *uhost);
void usbh_sof_handler(usbh_core_type *uhost);
void usbh_connect_callback(usbh_core_type *uhost);
void usbh_disconnect_callback(usbh_core_type *uhost);
void usbd_notify_urbchange_callback(usbh_core_type *uhost, uint8_t chnum, urb_sts_type sts);

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

