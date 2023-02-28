/**
 * @file hal_usb.h
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#ifndef __HAL_USB__H__
#define __HAL_USB__H__

#include "stdint.h"

/**
 * USB endpoint Transfer Type mask.
 */
#define USBD_EP_TYPE_CTRL 0
#define USBD_EP_TYPE_ISOC 1
#define USBD_EP_TYPE_BULK 2
#define USBD_EP_TYPE_INTR 3
#define USBD_EP_TYPE_MASK 3

/**
 * USB endpoint direction and number.
 */
#define USB_EP_DIR_MASK 0x80U
#define USB_EP_DIR_IN   0x80U
#define USB_EP_DIR_OUT  0x00U

#define USB_EP_OUT_MSK 0x7FU
#define USB_EP_IN_MSK  0x80U

/** Get endpoint index (number) from endpoint address */
#define USB_EP_GET_IDX(ep) ((ep) & ~USB_EP_DIR_MASK)
/** Get direction from endpoint address */
#define USB_EP_GET_DIR(ep) ((ep)&USB_EP_DIR_MASK)
/** Get endpoint address from endpoint index and direction */
#define USB_EP_GET_ADDR(idx, dir) ((idx) | ((dir)&USB_EP_DIR_MASK))
/** True if the endpoint is an IN endpoint */
#define USB_EP_DIR_IS_IN(ep) (USB_EP_GET_DIR(ep) == USB_EP_DIR_IN)
/** True if the endpoint is an OUT endpoint */
#define USB_EP_DIR_IS_OUT(ep) (USB_EP_GET_DIR(ep) == USB_EP_DIR_OUT)

#define USB_SET_EP_OUT(ep) (ep & USB_EP_OUT_MSK)
#define USB_SET_EP_IN(ep)  (ep | USB_EP_IN_MSK)

#define USB_OUT_EP_NUM 8
#define USB_IN_EP_NUM  8

enum usb_dc_event_type {
    /** USB error reported by the controller */
    USB_DC_EVENT_ERROR,
    /** USB reset */
    USB_DC_EVENT_RESET,
    /** Start of Frame received */
    USB_DC_EVENT_SOF,
    /** USB connection established, hardware enumeration is completed */
    USB_DC_EVENT_CONNECTED,
    /** USB configuration done */
    USB_DC_EVENT_CONFIGURED,
    /** USB connection suspended by the HOST */
    USB_DC_EVENT_SUSPEND,
    /** USB connection lost */
    USB_DC_EVENT_DISCONNECTED,
    /** USB connection resumed by the HOST */
    USB_DC_EVENT_RESUME,

    /** USB interface selected */
    USB_DC_EVENT_SET_INTERFACE,
    /** USB interface selected */
    USB_DC_EVENT_SET_REMOTE_WAKEUP,
    /** USB interface selected */
    USB_DC_EVENT_CLEAR_REMOTE_WAKEUP,
    /** Set Feature ENDPOINT_HALT received */
    USB_DC_EVENT_SET_HALT,
    /** Clear Feature ENDPOINT_HALT received */
    USB_DC_EVENT_CLEAR_HALT,
    /** setup packet received */
    USB_DC_EVENT_SETUP_NOTIFY,
    /** ep0 in packet received */
    USB_DC_EVENT_EP0_IN_NOTIFY,
    /** ep0 out packet received */
    USB_DC_EVENT_EP0_OUT_NOTIFY,
    /** ep in packet except ep0 received */
    USB_DC_EVENT_EP_IN_NOTIFY,
    /** ep out packet except ep0 received */
    USB_DC_EVENT_EP_OUT_NOTIFY,
    /** Initial USB connection status */
    USB_DC_EVENT_UNKNOWN
};

enum usb_error_type {
    USB_DC_OK = 0,
    USB_DC_EP_DIR_ERR = 1,
    USB_DC_EP_EN_ERR = 2,
    USB_DC_EP_TIMEOUT_ERR = 3,
    USB_DC_ADDR_ERR = 4,
    USB_DC_DMA_ERR = 5,
    USB_DC_VDMA_ERR = 6,
    USB_DC_DATA_NONE = 7,
};
/**
 * @brief USB Endpoint Configuration.
 *
 * Structure containing the USB endpoint configuration.
 */
struct usb_dc_ep_cfg {
    /** The number associated with the EP in the device
     *  configuration structure
     *       IN  EP = 0x80 | \<endpoint number\>
     *       OUT EP = 0x00 | \<endpoint number\>
     */
    uint8_t ep_addr;
    /** Endpoint Transfer Type.
     * May be Bulk, Interrupt, Control or Isochronous
     */
    uint8_t ep_type;
    /** Endpoint max packet size */
    uint16_t ep_mps;
};

/*
 * USB endpoint  structure.
 */
typedef struct
{
    uint8_t ep_ena;
    uint8_t is_stalled;
    struct usb_dc_ep_cfg ep_cfg;
} usb_dc_ep_state_t;

typedef struct usb_dc_device {
    usb_dc_ep_state_t in_ep[8];  /*!< IN endpoint parameters             */
    usb_dc_ep_state_t out_ep[8]; /*!< OUT endpoint parameters            */
} usb_dc_device_t;

#endif
