/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-08     CDT          first version
 */

#ifndef CHERRYUSB_CONFIG_H
#define CHERRYUSB_CONFIG_H

/* ================ USB common Configuration ================ */

#ifdef __RTTHREAD__
    #include <rtthread.h>

    #define CONFIG_USB_PRINTF(...) rt_kprintf(__VA_ARGS__)
#else
    #define CONFIG_USB_PRINTF(...) printf(__VA_ARGS__)
#endif

#ifndef CONFIG_USB_DBG_LEVEL
    #define CONFIG_USB_DBG_LEVEL USB_DBG_INFO
#endif

/* Enable print with color */
#define CONFIG_USB_PRINTF_COLOR_ENABLE

// #define CONFIG_USB_DCACHE_ENABLE

/* data align size when use dma or use dcache */
#ifdef CONFIG_USB_DCACHE_ENABLE
    #define CONFIG_USB_ALIGN_SIZE 32 // 32 or 64
#else
    #define CONFIG_USB_ALIGN_SIZE 4
#endif

/* attribute data into no cache ram */
#define USB_NOCACHE_RAM_SECTION __attribute__((section(".noncacheable")))

/* use usb_memcpy default for high performance but cost more flash memory.
 * And, arm libc has a bug that memcpy() may cause data misalignment when the size is not a multiple of 4.
*/
// #define CONFIG_USB_MEMCPY_DISABLE

/* ================= USB Device Stack Configuration ================ */

/* Ep0 in and out transfer buffer */
#ifndef CONFIG_USBDEV_REQUEST_BUFFER_LEN
    #define CONFIG_USBDEV_REQUEST_BUFFER_LEN 512
#endif

/* Send ep0 in data from user buffer instead of copying into ep0 reqdata
 * Please note that user buffer must be aligned with CONFIG_USB_ALIGN_SIZE
*/
// #define CONFIG_USBDEV_EP0_INDATA_NO_COPY

/* Check if the input descriptor is correct */
// #define CONFIG_USBDEV_DESC_CHECK

/* Enable test mode */
// #define CONFIG_USBDEV_TEST_MODE

/* enable advance desc register api */
#define CONFIG_USBDEV_ADVANCE_DESC

/* move ep0 setup handler from isr to thread */
// #define CONFIG_USBDEV_EP0_THREAD

#ifndef CONFIG_USBDEV_EP0_PRIO
    #define CONFIG_USBDEV_EP0_PRIO 4
#endif

#ifndef CONFIG_USBDEV_EP0_STACKSIZE
    #define CONFIG_USBDEV_EP0_STACKSIZE 2048
#endif

#ifndef CONFIG_USBDEV_MSC_MAX_LUN
    #define CONFIG_USBDEV_MSC_MAX_LUN 1
#endif

#ifndef CONFIG_USBDEV_MSC_MAX_BUFSIZE
    #define CONFIG_USBDEV_MSC_MAX_BUFSIZE 512
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

/* move msc read & write from isr to while(1), you should call usbd_msc_polling in while(1) */
// #define CONFIG_USBDEV_MSC_POLLING

/* move msc read & write from isr to thread */
// #define CONFIG_USBDEV_MSC_THREAD

#ifndef CONFIG_USBDEV_MSC_PRIO
    #define CONFIG_USBDEV_MSC_PRIO 4
#endif

#ifndef CONFIG_USBDEV_MSC_STACKSIZE
    #define CONFIG_USBDEV_MSC_STACKSIZE 2048
#endif

#ifndef CONFIG_USBDEV_MTP_MAX_BUFSIZE
    #define CONFIG_USBDEV_MTP_MAX_BUFSIZE 2048
#endif

#ifndef CONFIG_USBDEV_MTP_MAX_OBJECTS
    #define CONFIG_USBDEV_MTP_MAX_OBJECTS 256
#endif

#ifndef CONFIG_USBDEV_MTP_MAX_PATHNAME
    #define CONFIG_USBDEV_MTP_MAX_PATHNAME 256
#endif

#define CONFIG_USBDEV_MTP_THREAD

#ifndef CONFIG_USBDEV_MTP_PRIO
    #define CONFIG_USBDEV_MTP_PRIO 4
#endif

#ifndef CONFIG_USBDEV_MTP_STACKSIZE
    #define CONFIG_USBDEV_MTP_STACKSIZE 4096
#endif

#ifndef CONFIG_USBDEV_RNDIS_RESP_BUFFER_SIZE
    #define CONFIG_USBDEV_RNDIS_RESP_BUFFER_SIZE 156
#endif

/* rndis transfer buffer size, must be a multiple of (1536 + 44)*/
#ifndef CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE
    #define CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE 1580
#endif

#ifndef CONFIG_USBDEV_RNDIS_VENDOR_ID
    #define CONFIG_USBDEV_RNDIS_VENDOR_ID 0x0000ffff
#endif

#ifndef CONFIG_USBDEV_RNDIS_VENDOR_DESC
    #define CONFIG_USBDEV_RNDIS_VENDOR_DESC "CherryUSB"
#endif

#define CONFIG_USBDEV_RNDIS_USING_LWIP
#define CONFIG_USBDEV_CDC_ECM_USING_LWIP

/* ================ USB HOST Stack Configuration ================== */

#define CONFIG_USBHOST_MAX_RHPORTS          1
#define CONFIG_USBHOST_MAX_EXTHUBS          1
#define CONFIG_USBHOST_MAX_EHPORTS          4
#define CONFIG_USBHOST_MAX_INTERFACES       8
#define CONFIG_USBHOST_MAX_INTF_ALTSETTINGS 8
#define CONFIG_USBHOST_MAX_ENDPOINTS        4

#define CONFIG_USBHOST_MAX_CDC_ACM_CLASS 4
#define CONFIG_USBHOST_MAX_HID_CLASS     4
#define CONFIG_USBHOST_MAX_MSC_CLASS     2
#define CONFIG_USBHOST_MAX_AUDIO_CLASS   1
#define CONFIG_USBHOST_MAX_VIDEO_CLASS   1

#define CONFIG_USBHOST_DEV_NAMELEN 16

#ifndef CONFIG_USBHOST_PSC_PRIO
    #define CONFIG_USBHOST_PSC_PRIO 0
#endif
#ifndef CONFIG_USBHOST_PSC_STACKSIZE
    #define CONFIG_USBHOST_PSC_STACKSIZE 2048
#endif

//#define CONFIG_USBHOST_GET_STRING_DESC

// #define CONFIG_USBHOST_MSOS_ENABLE
#ifndef CONFIG_USBHOST_MSOS_VENDOR_CODE
    #define CONFIG_USBHOST_MSOS_VENDOR_CODE 0x00
#endif

/* Ep0 max transfer buffer */
#ifndef CONFIG_USBHOST_REQUEST_BUFFER_LEN
    #define CONFIG_USBHOST_REQUEST_BUFFER_LEN 512
#endif

#ifndef CONFIG_USBHOST_CONTROL_TRANSFER_TIMEOUT
    #define CONFIG_USBHOST_CONTROL_TRANSFER_TIMEOUT 500
#endif

#ifndef CONFIG_USBHOST_MSC_TIMEOUT
    #define CONFIG_USBHOST_MSC_TIMEOUT 5000
#endif

/* This parameter affects usb performance, and depends on (TCP_WND)tcp eceive windows size,
 * you can change to 2K ~ 16K and must be larger than TCP RX windows size in order to avoid being overflow.
 */
#ifndef CONFIG_USBHOST_RNDIS_ETH_MAX_RX_SIZE
    #define CONFIG_USBHOST_RNDIS_ETH_MAX_RX_SIZE (2048)
#endif

/* Because lwip do not support multi pbuf at a time, so increasing this variable has no performance improvement */
#ifndef CONFIG_USBHOST_RNDIS_ETH_MAX_TX_SIZE
    #define CONFIG_USBHOST_RNDIS_ETH_MAX_TX_SIZE (2048)
#endif

/* This parameter affects usb performance, and depends on (TCP_WND)tcp eceive windows size,
 * you can change to 2K ~ 16K and must be larger than TCP RX windows size in order to avoid being overflow.
 */
#ifndef CONFIG_USBHOST_CDC_NCM_ETH_MAX_RX_SIZE
    #define CONFIG_USBHOST_CDC_NCM_ETH_MAX_RX_SIZE (2048)
#endif
/* Because lwip do not support multi pbuf at a time, so increasing this variable has no performance improvement */
#ifndef CONFIG_USBHOST_CDC_NCM_ETH_MAX_TX_SIZE
    #define CONFIG_USBHOST_CDC_NCM_ETH_MAX_TX_SIZE (2048)
#endif

/* This parameter affects usb performance, and depends on (TCP_WND)tcp eceive windows size,
 * you can change to 2K ~ 16K and must be larger than TCP RX windows size in order to avoid being overflow.
 */
#ifndef CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE
    #define CONFIG_USBHOST_ASIX_ETH_MAX_RX_SIZE (2048)
#endif
/* Because lwip do not support multi pbuf at a time, so increasing this variable has no performance improvement */
#ifndef CONFIG_USBHOST_ASIX_ETH_MAX_TX_SIZE
    #define CONFIG_USBHOST_ASIX_ETH_MAX_TX_SIZE (2048)
#endif

/* This parameter affects usb performance, and depends on (TCP_WND)tcp eceive windows size,
 * you can change to 2K ~ 16K and must be larger than TCP RX windows size in order to avoid being overflow.
 */
#ifndef CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE
    #define CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE (2048)
#endif
/* Because lwip do not support multi pbuf at a time, so increasing this variable has no performance improvement */
#ifndef CONFIG_USBHOST_RTL8152_ETH_MAX_TX_SIZE
    #define CONFIG_USBHOST_RTL8152_ETH_MAX_TX_SIZE (2048)
#endif

#define CONFIG_USBHOST_BLUETOOTH_HCI_H4
// #define CONFIG_USBHOST_BLUETOOTH_HCI_LOG

#ifndef CONFIG_USBHOST_BLUETOOTH_TX_SIZE
    #define CONFIG_USBHOST_BLUETOOTH_TX_SIZE 2048
#endif
#ifndef CONFIG_USBHOST_BLUETOOTH_RX_SIZE
    #define CONFIG_USBHOST_BLUETOOTH_RX_SIZE 2048
#endif

/* ================ USB Device Port Configuration ================*/

#ifndef CONFIG_USBDEV_MAX_BUS
    #define CONFIG_USBDEV_MAX_BUS 1 // for now, bus num must be 1 except hpm ip
#endif

#ifndef CONFIG_USBDEV_EP_NUM
    #define CONFIG_USBDEV_EP_NUM 8
#endif

// #define CONFIG_USBDEV_SOF_ENABLE

/* When your chip hardware supports high-speed and wants to initialize it in high-speed mode,
 * the relevant IP will configure the internal or external high-speed PHY according to CONFIG_USB_HS.
 *
*/
//#define CONFIG_USB_HS

/* ---------------- DWC2 Configuration ---------------- */
/* enable dwc2 buffer dma mode for device
*/
// #define CONFIG_USB_DWC2_DMA_ENABLE

/* Defined FS Core device FIFO Size in words 32-bits */
#define CONFIG_USB_FS_CORE_DEVICE_RX_FIFO_SIZE      (128)
#define CONFIG_USB_FS_CORE_DEVICE_TX0_FIFO_SIZE     (32)
#define CONFIG_USB_FS_CORE_DEVICE_TX1_FIFO_SIZE     (32)
#define CONFIG_USB_FS_CORE_DEVICE_TX2_FIFO_SIZE     (32)
#define CONFIG_USB_FS_CORE_DEVICE_TX3_FIFO_SIZE     (32)
#define CONFIG_USB_FS_CORE_DEVICE_TX4_FIFO_SIZE     (32)
#define CONFIG_USB_FS_CORE_DEVICE_TX5_FIFO_SIZE     (32)
#define CONFIG_USB_FS_CORE_DEVICE_TX6_FIFO_SIZE     (32)
#define CONFIG_USB_FS_CORE_DEVICE_TX7_FIFO_SIZE     (32)
#define CONFIG_USB_FS_CORE_DEVICE_TX8_FIFO_SIZE     (32)
#define CONFIG_USB_FS_CORE_DEVICE_TX9_FIFO_SIZE     (32)
#define CONFIG_USB_FS_CORE_DEVICE_TX10_FIFO_SIZE    (32)
#define CONFIG_USB_FS_CORE_DEVICE_TX11_FIFO_SIZE    (32)
#define CONFIG_USB_FS_CORE_DEVICE_TX12_FIFO_SIZE    (32)
#define CONFIG_USB_FS_CORE_DEVICE_TX13_FIFO_SIZE    (32)
#define CONFIG_USB_FS_CORE_DEVICE_TX14_FIFO_SIZE    (32)
#define CONFIG_USB_FS_CORE_DEVICE_TX15_FIFO_SIZE    (32)

/* Defined FS Core host FIFO Size in words 32-bits */
#define CONFIG_USB_FS_CORE_HOST_RX_FIFO_SIZE        (128)
#define CONFIG_USB_FS_CORE_HOST_NP_FIFO_SIZE        (32)
#define CONFIG_USB_FS_CORE_HOST_PE_FIFO_SIZE        (64)

/* Defined FS Core total FIFO Size in words 32-bits */
#define CONFIG_USB_FS_CORE_TOTAL_FIFO_SIZE          (640)

/* Defined HS Core Device FIFO Size in words 32-bits */
#define CONFIG_USB_HS_CORE_DEVICE_RX_FIFO_SIZE      (1024)
#define CONFIG_USB_HS_CORE_DEVICE_TX0_FIFO_SIZE     (128)
#define CONFIG_USB_HS_CORE_DEVICE_TX1_FIFO_SIZE     (128)
#define CONFIG_USB_HS_CORE_DEVICE_TX2_FIFO_SIZE     (128)
#define CONFIG_USB_HS_CORE_DEVICE_TX3_FIFO_SIZE     (128)
#define CONFIG_USB_HS_CORE_DEVICE_TX4_FIFO_SIZE     (128)
#define CONFIG_USB_HS_CORE_DEVICE_TX5_FIFO_SIZE     (128)
#define CONFIG_USB_HS_CORE_DEVICE_TX6_FIFO_SIZE     (128)
#define CONFIG_USB_HS_CORE_DEVICE_TX7_FIFO_SIZE     (128)
#define CONFIG_USB_HS_CORE_DEVICE_TX8_FIFO_SIZE     (0)
#define CONFIG_USB_HS_CORE_DEVICE_TX9_FIFO_SIZE     (0)
#define CONFIG_USB_HS_CORE_DEVICE_TX10_FIFO_SIZE    (0)
#define CONFIG_USB_HS_CORE_DEVICE_TX11_FIFO_SIZE    (0)
#define CONFIG_USB_HS_CORE_DEVICE_TX12_FIFO_SIZE    (0)
#define CONFIG_USB_HS_CORE_DEVICE_TX13_FIFO_SIZE    (0)
#define CONFIG_USB_HS_CORE_DEVICE_TX14_FIFO_SIZE    (0)
#define CONFIG_USB_HS_CORE_DEVICE_TX15_FIFO_SIZE    (0)

/* Defined HS Core host FIFO Size in words 32-bits */
#define CONFIG_USB_HS_CORE_HOST_RX_FIFO_SIZE        (512)
#define CONFIG_USB_HS_CORE_HOST_NP_FIFO_SIZE        (128)
#define CONFIG_USB_HS_CORE_HOST_PE_FIFO_SIZE        (256)

/* Defined HS Core total FIFO Size in words 32-bits */
#define CONFIG_USB_HS_CORE_TOTAL_FIFO_SIZE          (2048)


/* ================ USB Host Port Configuration ==================*/
#ifndef CONFIG_USBHOST_MAX_BUS
    #define CONFIG_USBHOST_MAX_BUS 1
#endif

#ifndef CONFIG_USBHOST_PIPE_NUM
    #define CONFIG_USBHOST_PIPE_NUM 10
#endif


#ifndef usb_phyaddr2ramaddr
    #define usb_phyaddr2ramaddr(addr) (addr)
#endif

#ifndef usb_ramaddr2phyaddr
    #define usb_ramaddr2phyaddr(addr) (addr)
#endif

#endif
