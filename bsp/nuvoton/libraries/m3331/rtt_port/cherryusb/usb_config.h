/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
#ifndef __USB_CONFIG_H__
#define __USB_CONFIG_H__

#include "rtthread.h"
#include "NuMicro.h"



#define CONFIG_USB_PRINTF     rt_kprintf

#define usb_malloc(size)      rt_malloc(size)
#define usb_free(ptr)         rt_free(ptr)


//#define CONFIG_USB_DBG_LEVEL  USB_DBG_LOG
#if !defined(CONFIG_USB_DBG_LEVEL)
#define CONFIG_USB_DBG_LEVEL USB_DBG_INFO
#endif

/* Enable print with color */
#define CONFIG_USB_PRINTF_COLOR_ENABLE

/* data align size when use dma */
#if !defined(CONFIG_USB_ALIGN_SIZE)
    #define CONFIG_USB_ALIGN_SIZE 4
#endif

/* attribute data into no cache ram */
#define USB_NOCACHE_RAM_SECTION __attribute__((section(".noncacheable")))



#define CONFIG_USBDEV_MAX_BUS 1    // for now, bus num must be 1 except hpm ip

/* Ep0 max transfer buffer, specially for receiving data from ep0 out */
#define CONFIG_USBDEV_REQUEST_BUFFER_LEN   256

/* Setup packet log for debug */
// #define CONFIG_USBDEV_SETUP_LOG_PRINT

/* Check if the input descriptor is correct */
// #define CONFIG_USBDEV_DESC_CHECK

/* Enable test mode */
// #define CONFIG_USBDEV_TEST_MODE

#if !defined(CONFIG_USBDEV_MSC_MAX_LUN)
    #define CONFIG_USBDEV_MSC_MAX_LUN 1
#endif

#define CONFIG_USBDEV_TX_THREAD
#define CONFIG_USBDEV_RX_THREAD

#if defined(CONFIG_USBDEV_TX_THREAD)
    #if !defined(CONFIG_USBDEV_TX_PRIO)
        #define CONFIG_USBDEV_TX_PRIO 4
    #endif
    #if !defined(CONFIG_USBDEV_TX_STACKSIZE)
        #define CONFIG_USBDEV_TX_STACKSIZE 2048
    #endif
#endif

#if defined(CONFIG_USBDEV_RX_THREAD)
    #if !defined(CONFIG_USBDEV_RX_PRIO)
        #define CONFIG_USBDEV_RX_PRIO 4
    #endif
    #if !defined(CONFIG_USBDEV_RX_STACKSIZE)
        #define CONFIG_USBDEV_RX_STACKSIZE 2048
    #endif
#endif

#if !defined(CONFIG_USBDEV_MSC_MAX_LUN)
#define CONFIG_USBDEV_MSC_MAX_LUN 1
#if !defined(CONFIG_USBDEV_MSC_MAX_BUFSIZE)
#define CONFIG_USBDEV_MSC_MAX_BUFSIZE 512
#endif

#if !defined(CONFIG_USBDEV_MSC_MANUFACTURER_STRING)
#define CONFIG_USBDEV_MSC_MANUFACTURER_STRING ""
#endif
#if !defined(CONFIG_USBDEV_MSC_PRODUCT_STRING)
#define CONFIG_USBDEV_MSC_PRODUCT_STRING ""
#endif
#if !defined(CONFIG_USBDEV_MSC_VERSION_STRING)
#define CONFIG_USBDEV_MSC_VERSION_STRING "0.01"
#endif

/* move msc read & write from isr to while(1), you should call usbd_msc_polling in while(1) */
// #define CONFIG_USBDEV_MSC_POLLING

/* move msc read & write from isr to thread */
#define CONFIG_USBDEV_MSC_THREAD

#if !defined(CONFIG_USBDEV_MSC_PRIO)
#define CONFIG_USBDEV_MSC_PRIO 4
#endif
#if !defined(CONFIG_USBDEV_MSC_STACKSIZE)
#define CONFIG_USBDEV_MSC_STACKSIZE 2048
#endif

#if !defined(CONFIG_USBDEV_RNDIS_RESP_BUFFER_SIZE)
#define CONFIG_USBDEV_RNDIS_RESP_BUFFER_SIZE 156
#endif

/* rndis transfer buffer size, must be a multiple of (1536 + 44)*/
#if !defined(CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE)
#define CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE 1580
#endif

#if !defined(CONFIG_USBDEV_RNDIS_VENDOR_ID)
#define CONFIG_USBDEV_RNDIS_VENDOR_ID 0x0000ffff
#endif

#if !defined(CONFIG_USBDEV_RNDIS_VENDOR_DESC)
#define CONFIG_USBDEV_RNDIS_VENDOR_DESC "CherryUSB"
#endif

#define CONFIG_USBDEV_RNDIS_USING_LWIP



#define CONFIG_USBHOST_MAX_RHPORTS          1
#define CONFIG_USBHOST_MAX_EXTHUBS          4
#define CONFIG_USBHOST_MAX_EHPORTS          8
#define CONFIG_USBHOST_MAX_INTERFACES       8
#define CONFIG_USBHOST_MAX_INTF_ALTSETTINGS 8
#define CONFIG_USBHOST_MAX_ENDPOINTS        8

#define CONFIG_USBHOST_MAX_CDC_ACM_CLASS 4
#define CONFIG_USBHOST_MAX_HID_CLASS     4
#define CONFIG_USBHOST_MAX_MSC_CLASS     2
#define CONFIG_USBHOST_MAX_AUDIO_CLASS   1
#define CONFIG_USBHOST_MAX_VIDEO_CLASS   1
#define CONFIG_USBHOST_MAX_RNDIS_CLASS   1

#define CONFIG_USBHOST_DEV_NAMELEN 16

#if !defined(CONFIG_USBHOST_PSC_PRIO)
#define CONFIG_USBHOST_PSC_PRIO 0
#endif
#if !defined(CONFIG_USBHOST_PSC_STACKSIZE)
#define CONFIG_USBHOST_PSC_STACKSIZE 2048
#endif

//#define CONFIG_USBHOST_GET_STRING_DESC

// #define CONFIG_USBHOST_MSOS_ENABLE
#if !defined(CONFIG_USBHOST_MSOS_VENDOR_CODE)
#define CONFIG_USBHOST_MSOS_VENDOR_CODE 0x00
#endif

/* Ep0 max transfer buffer */
#if !defined(CONFIG_USBHOST_REQUEST_BUFFER_LEN)
#define CONFIG_USBHOST_REQUEST_BUFFER_LEN 512
#endif

#if !defined(CONFIG_USBHOST_CONTROL_TRANSFER_TIMEOUT)
#define CONFIG_USBHOST_CONTROL_TRANSFER_TIMEOUT 500
#endif

#if !defined(CONFIG_USBHOST_MSC_TIMEOUT)
#define CONFIG_USBHOST_MSC_TIMEOUT 5000
#endif

/* This parameter affects usb performance, and depends on (TCP_WND)tcp eceive windows size,
 * you can change to 2K ~ 16K and must be larger than TCP RX windows size in order to avoid being overflow.
 */
#if !defined(CONFIG_USBHOST_RNDIS_ETH_MAX_RX_SIZE)
#define CONFIG_USBHOST_RNDIS_ETH_MAX_RX_SIZE (2048)
#endif

/* Because lwip do not support multi pbuf at a time, so increasing this variable has no performance improvement */
#if !defined(CONFIG_USBHOST_RNDIS_ETH_MAX_TX_SIZE)
#define CONFIG_USBHOST_RNDIS_ETH_MAX_TX_SIZE (2048)
#endif

/* This parameter affects usb performance, and depends on (TCP_WND)tcp eceive windows size,
 * you can change to 2K ~ 16K and must be larger than TCP RX windows size in order to avoid being overflow.
 */
#if !defined(CONFIG_USBHOST_CDC_NCM_ETH_MAX_RX_SIZE)
#define CONFIG_USBHOST_CDC_NCM_ETH_MAX_RX_SIZE (2048)
#endif
/* Because lwip do not support multi pbuf at a time, so increasing this variable has no performance improvement */
#if !defined(CONFIG_USBHOST_CDC_NCM_ETH_MAX_TX_SIZE)
#define CONFIG_USBHOST_CDC_NCM_ETH_MAX_TX_SIZE (2048)
#endif

/* This parameter affects usb performance, and depends on (TCP_WND)tcp eceive windows size,
 * you can change to 2K ~ 16K and must be larger than TCP RX windows size in order to avoid being overflow.
 */
#if !defined(CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE)
#define CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE (2048)
#endif
/* Because lwip do not support multi pbuf at a time, so increasing this variable has no performance improvement */
#if !defined(CONFIG_USBHOST_ASIX_ETH_MAX_TX_SIZE)
#define CONFIG_USBHOST_ASIX_ETH_MAX_TX_SIZE (2048)
#endif

/* This parameter affects usb performance, and depends on (TCP_WND)tcp eceive windows size,
 * you can change to 2K ~ 16K and must be larger than TCP RX windows size in order to avoid being overflow.
 */
#if !defined(CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE)
#define CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE (2048)
#endif
/* Because lwip do not support multi pbuf at a time, so increasing this variable has no performance improvement */
#if !defined(CONFIG_USBHOST_RTL8152_ETH_MAX_TX_SIZE)
#define CONFIG_USBHOST_RTL8152_ETH_MAX_TX_SIZE (2048)
#endif

#define CONFIG_USBHOST_BLUETOOTH_HCI_H4
// #define CONFIG_USBHOST_BLUETOOTH_HCI_LOG

#if !defined(CONFIG_USBHOST_BLUETOOTH_TX_SIZE)
#define CONFIG_USBHOST_BLUETOOTH_TX_SIZE 2048
#endif
#if !defined(CONFIG_USBHOST_BLUETOOTH_RX_SIZE)
#define CONFIG_USBHOST_BLUETOOTH_RX_SIZE 2048
#endif


#if !defined(CONFIG_USB_HS)
#define CONFIG_USB_HS
#endif

#if !defined(CONFIG_USBDEV_EP_NUM)
    #define CONFIG_USBDEV_EP_NUM    8
#endif
#if !defined(CONFIG_USBHOST_MAX_BUS)
#define CONFIG_USBHOST_MAX_BUS 1
#endif

#if !defined(CONFIG_USBHOST_PIPE_NUM)
#define CONFIG_USBHOST_PIPE_NUM 10
#endif

/* ---------------- EHCI Configuration ---------------- */
#define CONFIG_USB_EHCI_HCCR_OFFSET     (0)
#define CONFIG_USB_EHCI_FRAME_LIST_SIZE 1024
#define CONFIG_USB_EHCI_QH_NUM          CONFIG_USBHOST_PIPE_NUM
#define CONFIG_USB_EHCI_QTD_NUM         3
#define CONFIG_USB_EHCI_ITD_NUM         20
// #define CONFIG_USB_EHCI_HCOR_RESERVED_DISABLE
#define CONFIG_USB_EHCI_CONFIGFLAG
// #define CONFIG_USB_EHCI_ISO
//#define CONFIG_USB_EHCI_WITH_OHCI

/* ---------------- OHCI Configuration ---------------- */
#define CONFIG_USB_OHCI_HCOR_OFFSET (0x0)

#if !defined(usb_phyaddr2ramaddr)
#define usb_phyaddr2ramaddr(addr) (addr)
#endif

#if !defined(usb_ramaddr2phyaddr)
#define usb_ramaddr2phyaddr(addr) (addr)
#endif

#endif
