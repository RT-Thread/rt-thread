/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef CHERRYUSB_CONFIG_H
#define CHERRYUSB_CONFIG_H

#include <rtthread.h>

#define CHERRYUSB_VERSION 0x001002

/* ================ USB common Configuration ================ */

#define CONFIG_USB_PRINTF(...)              rt_kprintf(__VA_ARGS__)

#define usb_malloc(size)                    rt_malloc(size)
#define usb_free(ptr)                       rt_free(ptr)
#define usb_align(align, size)              rt_malloc_align(size, align)  

#ifndef CONFIG_USB_DBG_LEVEL
#define CONFIG_USB_DBG_LEVEL USB_DBG_ERROR
#endif

/* Enable print with color */
#define CONFIG_USB_PRINTF_COLOR_ENABLE

/* data align size when use dma */
#ifndef CONFIG_USB_ALIGN_SIZE
#define CONFIG_USB_ALIGN_SIZE 4
#endif

/* attribute data into no cache ram */
#define USB_NOCACHE_RAM_SECTION __attribute__((section(".noncacheable")))

/* ================= USB Device Stack Configuration ================ */

/* Ep0 max transfer buffer, specially for receiving data from ep0 out */
#define CONFIG_USBDEV_REQUEST_BUFFER_LEN 512

/* Setup packet log for debug */
#define CONFIG_USBDEV_SETUP_LOG_PRINT

/* Check if the input descriptor is correct */
#define CONFIG_USBDEV_DESC_CHECK

#ifndef CONFIG_USB_ERROR_USE_SYSTEM
#define CONFIG_USB_ERROR_USE_SYSTEM
#endif

/* Enable test mode */
// #define CONFIG_USBDEV_TEST_MODE

#ifndef CONFIG_USBDEV_MSC_BLOCK_SIZE
#define CONFIG_USBDEV_MSC_BLOCK_SIZE 512
#endif

#ifndef CONFIG_USBDEV_MSC_MANUFACTURER_STRING
#define CONFIG_USBDEV_MSC_MANUFACTURER_STRING ""
#endif

#ifndef CONFIG_USBDEV_MSC_PRODUCT_STRING
#define CONFIG_USBDEV_MSC_PRODUCT_STRING ""
#endif

#ifndef CONFIG_USBDEV_MSC_VERSION_STRING
#define CONFIG_USBDEV_MSC_VERSION_STRING "0.01"
#endif

#define CONFIG_USBDEV_MSC_THREAD

#ifndef CONFIG_USBDEV_MSC_PRIO
#define CONFIG_USBDEV_MSC_PRIO 4
#endif

#ifndef CONFIG_USBDEV_MSC_STACKSIZE
#define CONFIG_USBDEV_MSC_STACKSIZE 8192
#endif

#ifndef CONFIG_USBDEV_RNDIS_RESP_BUFFER_SIZE
#define CONFIG_USBDEV_RNDIS_RESP_BUFFER_SIZE 156
#endif

#ifndef CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE
#define CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE 1536
#endif

#ifndef CONFIG_USBDEV_RNDIS_VENDOR_ID
#define CONFIG_USBDEV_RNDIS_VENDOR_ID 0x0000ffff
#endif

#ifndef CONFIG_USBDEV_RNDIS_VENDOR_DESC
#define CONFIG_USBDEV_RNDIS_VENDOR_DESC "CherryUSB"
#endif

#define CONFIG_USBDEV_RNDIS_USING_LWIP

/* ================ USB HOST Stack Configuration ================== */

#define CONFIG_USBHOST_MAX_RHPORTS          1
#define CONFIG_USBHOST_MAX_EXTHUBS          1
#define CONFIG_USBHOST_MAX_EHPORTS          4
#define CONFIG_USBHOST_MAX_INTERFACES       6
#define CONFIG_USBHOST_MAX_INTF_ALTSETTINGS 1
#define CONFIG_USBHOST_MAX_ENDPOINTS        4

#define CONFIG_USBHOST_MAX_CDC_ACM_CLASS 4
#define CONFIG_USBHOST_MAX_HID_CLASS     4
#define CONFIG_USBHOST_MAX_MSC_CLASS     2
#define CONFIG_USBHOST_MAX_AUDIO_CLASS   1
#define CONFIG_USBHOST_MAX_VIDEO_CLASS   1

#define CONFIG_USBHOST_DEV_NAMELEN 16

#ifndef CONFIG_USBHOST_PSC_PRIO
#define CONFIG_USBHOST_PSC_PRIO 4
#endif
#ifndef CONFIG_USBHOST_PSC_STACKSIZE
#define CONFIG_USBHOST_PSC_STACKSIZE 81920
#endif

// #define CONFIG_USBHOST_GET_STRING_DESC

// #define CONFIG_USBHOST_MSOS_ENABLE
#define CONFIG_USBHOST_MSOS_VENDOR_CODE 0x00

/* Ep0 max transfer buffer */
#define CONFIG_USBHOST_REQUEST_BUFFER_LEN 512

#ifndef CONFIG_USBHOST_CONTROL_TRANSFER_TIMEOUT
#define CONFIG_USBHOST_CONTROL_TRANSFER_TIMEOUT 500
#endif

#ifndef CONFIG_USBHOST_MSC_TIMEOUT
#define CONFIG_USBHOST_MSC_TIMEOUT 5000
#endif

/* ================ USB Device Port Configuration ================*/

/* ================ USB Host Port Configuration ==================*/

#define CONFIG_USBHOST_PIPE_NUM 10

/* ================ XHCI Configuration ================ */
#if defined(PKG_CHERRYUSB_HOST_XHCI)
#define CONFIG_USBHOST_XHCI
#define CONFIG_USBHOST_XHCI_ID  0U
#endif

/* ================ PUSB2 Configuration ================ */
#if defined(PKG_CHERRYUSB_HOST_PUSB2) || defined(PKG_CHERRYUSB_DEVICE_PUSB2)
#define CONFIG_USBDEV_PUSB2_CTRL_ID    0U
#define CONFIG_USBDEV_PUSB2_CTRL_NUM   1U
#endif

#endif
