/**
  **************************************************************************
  * @file     usbh_ctrl.h
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
#ifndef __USBH_CTRL_H
#define __USBH_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "usbh_core.h"

/** @addtogroup USBH_drivers_control
  * @{
  */

/** @defgroup USBH_ctrl_exported_types
  * @{
  */

#ifdef USE_OTG_HOST_MODE

usb_sts_type usbh_ctrl_send_setup(usbh_core_type *uhost, uint8_t *buffer, uint8_t hc_num);
usb_sts_type usbh_ctrl_recv_data(usbh_core_type *uhost, uint8_t *buffer,
                            uint16_t length, uint16_t hc_num);
usb_sts_type usbh_ctrl_send_data(usbh_core_type *uhost, uint8_t *buffer,
                            uint16_t length, uint16_t hc_num);
usb_sts_type usbh_ctrl_setup_handler(usbh_core_type *uhost);
usb_sts_type usbh_ctrl_setup_wait_handler(usbh_core_type *uhost, uint32_t *timeout);
usb_sts_type usbh_ctrl_data_in_handler(usbh_core_type *uhost);
usb_sts_type usbh_ctrl_data_in_wait_handler(usbh_core_type *uhost, uint32_t timeout);
usb_sts_type usbh_ctrl_data_out_handler(usbh_core_type *uhost);
usb_sts_type usbh_ctrl_data_out_wait_handler(usbh_core_type *uhost, uint32_t timeout);
usb_sts_type usbh_ctrl_status_in_handler(usbh_core_type *uhost);
usb_sts_type usbh_ctrl_status_in_wait_handler(usbh_core_type *uhost, uint32_t timeout);
usb_sts_type usbh_ctrl_status_out_handler(usbh_core_type *uhost);
usb_sts_type usbh_ctrl_status_out_wait_handler(usbh_core_type *uhost, uint32_t timeout);
usb_sts_type usbh_ctrl_error_handler(usbh_core_type *uhost);
usb_sts_type usbh_ctrl_stall_handler(usbh_core_type *uhost);
usb_sts_type usbh_ctrl_complete_handler(usbh_core_type *uhost);
usb_sts_type usbh_ctrl_transfer_loop(usbh_core_type *uhost);
usb_sts_type usbh_ctrl_request(usbh_core_type *uhost, uint8_t *buffer, uint16_t length);
usb_sts_type usbh_get_descriptor(usbh_core_type *uhost, uint16_t length,
                            uint8_t req_type, uint16_t wvalue,
                            uint8_t *buffer);
void usbh_parse_dev_desc(usbh_core_type *uhost, uint8_t *buffer, uint16_t length);
usb_header_desc_type *usbh_get_next_header(uint8_t *buf, uint16_t *index_len);
void usbh_parse_interface_desc(usb_interface_desc_type *intf, uint8_t *buf);
void usbh_parse_endpoint_desc(usb_endpoint_desc_type *ept_desc, uint8_t *buf);
usb_sts_type usbh_parse_configure_desc(usbh_core_type *uhost,
                                  uint8_t *buffer, uint16_t length);
uint8_t usbh_find_interface(usbh_core_type *uhost, uint8_t class_code, uint8_t sub_class, uint8_t protocol);
void usbh_parse_string_desc(uint8_t *src, uint8_t *dest, uint16_t length);
usb_sts_type usbh_get_device_descriptor(usbh_core_type *uhost, uint16_t length);
usb_sts_type usbh_get_configure_descriptor(usbh_core_type *uhost, uint16_t length);
usb_sts_type usbh_get_sting_descriptor(usbh_core_type *uhost, uint8_t string_id,
                                  uint8_t *buffer, uint16_t length);
usb_sts_type usbh_set_configuration(usbh_core_type *uhost, uint16_t config);
usb_sts_type usbh_set_address(usbh_core_type *uhost, uint8_t address);
usb_sts_type usbh_set_interface(usbh_core_type *uhost, uint8_t ept_num, uint8_t altsetting);
usb_sts_type usbh_set_feature(usbh_core_type *uhost, uint8_t feature, uint16_t index);
usb_sts_type usbh_clear_dev_feature(usbh_core_type *uhost, uint8_t feature, uint16_t index);
usb_sts_type usbh_clear_ept_feature(usbh_core_type *uhost, uint8_t ept_num, uint8_t hc_num);

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
