/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_DFU_H
#define USB_DFU_H

/**\addtogroup USB_MODULE_DFU USB DFU class
 * \brief This module contains USB Device Firmware Upgrade class definitions.
 * \details This module based on
 * + [USB Device Firmware Upgrade Specification, Revision 1.1]
 * (https://www.usb.org/sites/default/files/DFU_1.1.pdf)
 * @{ */

/** DFU Specification release */
#define DFU_VERSION 0x0110

/** DFU Class Subclass */
#define DFU_SUBCLASS_DFU 0x01

/** DFU Class runtime Protocol */
#define DFU_PROTOCOL_RUNTIME 0x01

/** DFU Class DFU mode Protocol */
#define DFU_PROTOCOL_MODE 0x02

/**
 * @brief DFU Class Specific Requests
 */
#define DFU_REQUEST_DETACH    0x00
#define DFU_REQUEST_DNLOAD    0x01
#define DFU_REQUEST_UPLOAD    0x02
#define DFU_REQUEST_GETSTATUS 0x03
#define DFU_REQUEST_CLRSTATUS 0x04
#define DFU_REQUEST_GETSTATE  0x05
#define DFU_REQUEST_ABORT     0x06

/** DFU FUNCTIONAL descriptor type */
#define DFU_FUNC_DESC 0x21

/** DFU attributes DFU Functional Descriptor */
#define DFU_ATTR_WILL_DETACH            0x08
#define DFU_ATTR_MANIFESTATION_TOLERANT 0x04
#define DFU_ATTR_CAN_UPLOAD             0x02
#define DFU_ATTR_CAN_DNLOAD             0x01

/** bStatus values for the DFU_GETSTATUS response */
#define DFU_STATUS_OK               0x00U
#define DFU_STATUS_ERR_TARGET       0x01U
#define DFU_STATUS_ERR_FILE         0x02U
#define DFU_STATUS_ERR_WRITE        0x03U
#define DFU_STATUS_ERR_ERASE        0x04U
#define DFU_STATUS_ERR_CHECK_ERASED 0x05U
#define DFU_STATUS_ERR_PROG         0x06U
#define DFU_STATUS_ERR_VERIFY       0x07U
#define DFU_STATUS_ERR_ADDRESS      0x08U
#define DFU_STATUS_ERR_NOTDONE      0x09U
#define DFU_STATUS_ERR_FIRMWARE     0x0AU
#define DFU_STATUS_ERR_VENDOR       0x0BU
#define DFU_STATUS_ERR_USB          0x0CU
#define DFU_STATUS_ERR_POR          0x0DU
#define DFU_STATUS_ERR_UNKNOWN      0x0EU
#define DFU_STATUS_ERR_STALLEDPKT   0x0FU

/** bState values for the DFU_GETSTATUS response */
#define DFU_STATE_APP_IDLE                0U
#define DFU_STATE_APP_DETACH              1U
#define DFU_STATE_DFU_IDLE                2U
#define DFU_STATE_DFU_DNLOAD_SYNC         3U
#define DFU_STATE_DFU_DNLOAD_BUSY         4U
#define DFU_STATE_DFU_DNLOAD_IDLE         5U
#define DFU_STATE_DFU_MANIFEST_SYNC       6U
#define DFU_STATE_DFU_MANIFEST            7U
#define DFU_STATE_DFU_MANIFEST_WAIT_RESET 8U
#define DFU_STATE_DFU_UPLOAD_IDLE         9U
#define DFU_STATE_DFU_ERROR               10U

/** DFU Manifestation State  */
#define DFU_MANIFEST_COMPLETE    0U
#define DFU_MANIFEST_IN_PROGRESS 1U

/** Special Commands  with Download Request  */
#define DFU_CMD_GETCOMMANDS       0U
#define DFU_CMD_SETADDRESSPOINTER 0x21U
#define DFU_CMD_ERASE             0x41U
#define DFU_MEDIA_ERASE           0x00U
#define DFU_MEDIA_PROGRAM         0x01U

/** Other defines  */
/* Bit Detach capable = bit 3 in bmAttributes field */
#define DFU_DETACH_MASK   (1U << 3)
#define DFU_MANIFEST_MASK (1U << 2)

/** Run-Time Functional Descriptor */
struct dfu_runtime_descriptor {
    uint8_t bLength;         /**<\brief Descriptor length in bytes.*/
    uint8_t bDescriptorType; /**<\brief DFU functional descriptor type.*/
    uint8_t bmAttributes;    /**<\brief USB DFU capabilities \ref USB_DFU_CAPAB*/
    uint16_t wDetachTimeout; /**<\brief USB DFU detach timeout in ms.*/
    uint16_t wTransferSize;  /**<\brief USB DFU maximum transfer block size in bytes.*/
    uint16_t bcdDFUVersion;  /**<\brief USB DFU version \ref VERSION_BCD utility macro.*/
} __PACKED;

/**\brief Payload packet to response in DFU_GETSTATUS request */
struct dfu_info {
    uint8_t bStatus;       /**<\brief An indication of the status resulting from the
                                     * execution of the most recent request.*/
    uint8_t bPollTimeout;  /**<\brief Minimum time (LSB) in ms, that the host should wait
                                     * before sending a subsequent DFU_GETSTATUS request.*/
    uint16_t wPollTimeout; /**<\brief Minimum time (MSB) in ms, that the host should wait
                                     * before sending a subsequent DFU_GETSTATUS request.*/
    uint8_t bState;        /**<\brief An indication of the state that the device is going
                                     * to enter immediately following transmission of this response.*/
    uint8_t iString;       /**<\brief Index of the status string descriptor.*/
};

// clang-format off
#define DFU_DESCRIPTOR_INIT()                                                            \
    0x09,                          /* bLength */                                         \
    USB_DESCRIPTOR_TYPE_INTERFACE, /* bDescriptorType */                                 \
    0x00,                          /* bInterfaceNumber */                                \
    0x00,                          /* bAlternateSetting */                               \
    0x00,                          /* bNumEndpoints Default Control Pipe only */         \
    USB_DEVICE_CLASS_APP_SPECIFIC, /* bInterfaceClass */                                 \
    0x01,                          /* bInterfaceSubClass Device Firmware Upgrade */      \
    0x02,                          /* bInterfaceProtocol DFU mode */                     \
    0x04, /* iInterface */         /*!< Device Firmware Update Functional Descriptor  */ \
    0x09,                          /* bLength */                                         \
    0x21,                          /* DFU Functional Descriptor */                       \
    0x0B,                          /* bmAttributes */                                    \
    WBVAL(0x00ff),                 /* wDetachTimeOut */                                  \
    WBVAL(USBD_DFU_XFER_SIZE),     /* wTransferSize */                                   \
    WBVAL(0x011a)                  /* bcdDFUVersion */
// clang-format on

#endif /* USB_DFU_H */
