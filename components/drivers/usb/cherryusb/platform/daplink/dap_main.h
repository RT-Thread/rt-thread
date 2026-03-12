/*
 * Copyright (c) 2023 ~ 2025, sakumisu
 * Copyright (c) 2023 ~ 2025, HalfSweet
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef DAP_MAIN_H
#define DAP_MAIN_H

#include "usbd_core.h"
#include "usbd_cdc.h"
#include "usbd_msc.h"
#include "usbd_hid.h"
#include "chry_ringbuffer.h"
#include "DAP_config.h"
#include "DAP.h"

#define DAP_IN_EP  0x81
#define DAP_OUT_EP 0x02

#define CDC_IN_EP  0x83
#define CDC_OUT_EP 0x04
#define CDC_INT_EP 0x85

#define MSC_IN_EP  0x86
#define MSC_OUT_EP 0x07

#define HID_IN_EP  0x88
#define HID_OUT_EP 0x09

#define USBD_VID           0x0D28
#define USBD_PID           0x0204
#define USBD_MAX_POWER     500
#define USBD_LANGID_STRING 1033

#ifdef CONFIG_USB_HS
#if DAP_PACKET_SIZE != 512
#error "DAP_PACKET_SIZE must be 512 in hs"
#endif
#else
#if DAP_PACKET_SIZE != 64
#error "DAP_PACKET_SIZE must be 64 in fs"
#endif
#endif

#ifdef CONFIG_USB_HS
#define HID_PACKET_SIZE 1024
#else
#define HID_PACKET_SIZE 64
#endif

#define CONFIG_UARTRX_RINGBUF_SIZE (8 * 1024)
#define CONFIG_USBRX_RINGBUF_SIZE  (8 * 1024)

#ifndef CONFIG_CHERRYDAP_USE_MSC
#define CONFIG_CHERRYDAP_USE_MSC 0
#endif

#ifndef CONFIG_CHERRYDAP_USE_CUSTOM_HID
#define CONFIG_CHERRYDAP_USE_CUSTOM_HID 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern char serial_number_dynamic[36];

extern struct usbd_interface hid_intf;

extern chry_ringbuffer_t g_uartrx;
extern chry_ringbuffer_t g_usbrx;

void chry_dap_init(uint8_t busid, uint32_t reg_base);

void chry_dap_handle(void);

void chry_dap_usb2uart_handle(void);

/* implment by user */
extern void chry_dap_usb2uart_uart_config_callback(struct cdc_line_coding *line_coding);

/* implment by user */
extern void chry_dap_usb2uart_uart_send_bydma(uint8_t *data, uint16_t len);

void chry_dap_usb2uart_uart_send_complete(uint32_t size);

/* implment by user */
extern void hid_custom_notify_handler(uint8_t busid, uint8_t event, void *arg);

/* implment by user */
extern void usbd_hid_custom_in_callback(uint8_t busid, uint8_t ep, uint32_t nbytes);

/* implment by user */
extern void usbd_hid_custom_out_callback(uint8_t busid, uint8_t ep, uint32_t nbytes);

#ifdef __cplusplus
}
#endif

#endif