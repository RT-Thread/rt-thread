/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_HUB_H
#define USB_HUB_H

/* HUB Class Descriptor Types */
#define HUB_DESCRIPTOR_TYPE_HUB  0x29
#define HUB_DESCRIPTOR_TYPE_HUB3 0x2A

#define HUB_MAX_DEPTH 5

#define HUB_SUBCLASS     0x00
#define HUB_PROTOCOL_STT 0x01
#define HUB_PROTOCOL_MTT 0x02

/* Hub class requests */
#define HUB_REQUEST_GET_STATUS      USB_REQUEST_GET_STATUS
#define HUB_REQUEST_CLEAR_FEATURE   USB_REQUEST_CLEAR_FEATURE
#define HUB_REQUEST_SET_FEATURE     USB_REQUEST_SET_FEATURE
#define HUB_REQUEST_GET_DESCRIPTOR  USB_REQUEST_GET_DESCRIPTOR
#define HUB_REQUEST_SET_DESCRIPTOR  USB_REQUEST_SET_DESCRIPTOR
#define HUB_REQUEST_CLEAR_TT_BUFFER (0x08)
#define HUB_REQUEST_RESET_TT        (0x09)
#define HUB_REQUEST_GET_TT_STATE    (0x0a)
#define HUB_REQUEST_STOP_TT         (0x0b)
#define HUB_REQUEST_SET_HUB_DEPTH   (0x0C)

/* Hub class features */
#define HUB_FEATURE_HUB_C_LOCALPOWER  (0x0)
#define HUB_FEATURE_HUB_C_OVERCURRENT (0x1)

/* Port features */
#define HUB_PORT_FEATURE_CONNECTION  (0x00)
#define HUB_PORT_FEATURE_ENABLE      (0x01)
#define HUB_PORT_FEATURE_SUSPEND     (0x02)
#define HUB_PORT_FEATURE_OVERCURRENT (0x03)
#define HUB_PORT_FEATURE_RESET       (0x04)
#define HUB_PORT_FEATURE_L1          (0x05) /* USB 2.0 only */

#define HUB_PORT_FEATURE_POWER    (0x08) /* USB 2.0 only */
#define HUB_PORT_FEATURE_POWER_SS (0x09) /* USB 3.0 only */
/* This is a bit tricky because HUB_PORT_FEATURE_POWER_SS and
   HUB_PORT_FEATURE_LOWSPEED share the same bit. */
#define HUB_PORT_FEATURE_LOWSPEED  (0x09) /* USB 2.0 only */
#define HUB_PORT_FEATURE_HIGHSPEED (0x0a) /* USB 2.0 only */
#define HUB_PORT_FEATURE_TEST      (0x0b) /* USB 2.0 only */
#define HUB_PORT_FEATURE_INDICATOR (0x0c) /* USB 2.0 only */

/* Port status change (wPortChange) */
#define HUB_PORT_FEATURE_C_CONNECTION  (0x10)
#define HUB_PORT_FEATURE_C_ENABLE      (0x11) /* USB 2.0 only */
#define HUB_PORT_FEATURE_C_SUSPEND     (0x12) /* USB 2.0 only */
#define HUB_PORT_FEATURE_C_OVER_CURREN (0x13)
#define HUB_PORT_FEATURE_C_RESET       (0x14)
#define HUB_PORT_FEATURE_C_BH_RESET    (0x15) /* USB 3.0 only */
#define HUB_PORT_FEATURE_C_LINK_STATE  (0x16) /* USB 3.0 only */
#define HUB_PORT_FEATURE_C_CONFIG_ERR  (0x17) /* USB 3.0 only */

/* Hub status */
#define HUB_STATUS_LOCALPOWER  (1 << 0)
#define HUB_STATUS_OVERCURRENT (1 << 1)

/* Hub status change */
#define HUB_STATUS_C_LOCALPOWER  (1 << 0)
#define HUB_STATUS_C_OVERCURRENT (1 << 1)

/* Hub port status */
#define HUB_PORT_STATUS_CONNECTION  (1 << 0)
#define HUB_PORT_STATUS_ENABLE      (1 << 1)
#define HUB_PORT_STATUS_SUSPEND     (1 << 2) /* USB 2.0 only */
#define HUB_PORT_STATUS_OVERCURRENT (1 << 3)
#define HUB_PORT_STATUS_RESET       (1 << 4)
#define HUB_PORT_STATUS_L1          (1 << 5) /* USB 2.0 only */

/* Port Link State (PORT_LINK_STATE), USB 3.0 only */
#define HUB_PORT_STATUS_LS_U0          (0x00 << 5)
#define HUB_PORT_STATUS_LS_U1          (0x01 << 5)
#define HUB_PORT_STATUS_LS_U2          (0x02 << 5)
#define HUB_PORT_STATUS_LS_U3          (0x03 << 5)
#define HUB_PORT_STATUS_LS_SS_DISABLED (0x04 << 5)
#define HUB_PORT_STATUS_LS_RX_DETECT   (0x05 << 5)
#define HUB_PORT_STATUS_LS_SS_INACTIVE (0x06 << 5)
#define HUB_PORT_STATUS_LS_POLLING     (0x07 << 5)
#define HUB_PORT_STATUS_LS_RECOVERY    (0x08 << 5)
#define HUB_PORT_STATUS_LS_HOT_RESET   (0x09 << 5)
#define HUB_PORT_STATUS_LS_COMP_MOD    (0x0a << 5)
#define HUB_PORT_STATUS_LS_LOOPBACK    (0x0b << 5)

#define HUB_PORT_STATUS_POWER      (1 << 8)
#define HUB_PORT_STATUS_POWER_SS   (1 << 9)  /* USB 3.0 only */
#define HUB_PORT_STATUS_LOW_SPEED  (1 << 9)  /* USB 2.0 only */
#define HUB_PORT_STATUS_HIGH_SPEED (1 << 10) /* USB 2.0 only */
#define HUB_PORT_STATUS_TEST       (1 << 11) /* USB 2.0 only */
#define HUB_PORT_STATUS_INDICATOR  (1 << 12) /* USB 2.0 only */

/* Hub port status change */
#define HUB_PORT_STATUS_C_CONNECTION  (1 << 0)
#define HUB_PORT_STATUS_C_ENABLE      (1 << 1) /* USB 2.0 only */
#define HUB_PORT_STATUS_C_SUSPEND     (1 << 2) /* USB 2.0 only */
#define HUB_PORT_STATUS_C_OVERCURRENT (1 << 3)
#define HUB_PORT_STATUS_C_RESET       (1 << 4)
#define HUB_PORT_STATUS_C_L1          (1 << 5) /* USB 2.0 only */
#define HUB_PORT_STATUS_C_BH_RESET    (1 << 5) /* USB 3.0 only */
#define HUB_PORT_STATUS_C_PORTLINK    (1 << 6) /* USB 3.0 only */
#define HUB_PORT_STATUS_C_CONFIGERR   (1 << 7) /* USB 3.0 only */

/* Hub characteristics */
#define HUB_CHAR_LPSM_SHIFT      (0) /* Bits 0-1: Logical Power Switching Mode */
#define HUB_CHAR_LPSM_MASK       (3 << HUB_CHAR_LPSM_SHIFT)
#define HUB_CHAR_LPSM_GANGED     (0 << HUB_CHAR_LPSM_SHIFT)
#define HUB_CHAR_LPSM_INDIVIDUAL (1 << HUB_CHAR_LPSM_SHIFT)
#define HUB_CHAR_COMPOUND        (1 << 2) /* Bit 2: Compound device */
#define HUB_CHAR_OCPM_SHIFT      (3)      /* Bits 3-4: Over-current Protection Mode */
#define HUB_CHAR_OCPM_MASK       (3 << HUB_CHAR_OCPM_SHIFT)
#define HUB_CHAR_OCPM_GLOBAL     (0 << HUB_CHAR_OCPM_SHIFT)
#define HUB_CHAR_OCPM_INDIVIDUAL (1 << HUB_CHAR_OCPM_SHIFT)
#define HUB_CHAR_TTTT_SHIFT      (5) /* Bits 5-6: TT Think Time */
#define HUB_CHAR_TTTT_MASK       (3 << HUB_CHAR_TTTT_SHIFT)
#define HUB_CHAR_TTTT_8_BITS     (0 << HUB_CHAR_TTTT_SHIFT)
#define HUB_CHAR_TTTT_16_BITS    (1 << HUB_CHAR_TTTT_SHIFT)
#define HUB_CHAR_TTTT_24_BITS    (2 << HUB_CHAR_TTTT_SHIFT)
#define HUB_CHAR_TTTT_32_BITS    (3 << HUB_CHAR_TTTT_SHIFT)
#define HUB_CHAR_PORTIND         (1 << 7) /* Bit 7: Port Indicators Supported */

/* Hub descriptor */
struct usb_hub_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bNbrPorts;
    uint16_t wHubCharacteristics;
    uint8_t bPwrOn2PwrGood;
    uint8_t bHubContrCurrent;
    uint8_t DeviceRemovable;
    uint8_t PortPwrCtrlMask;
} __PACKED;

#define USB_SIZEOF_HUB_DESC 9

/* Super speed Hub descriptor */
struct usb_hub_ss_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bNbrPorts;
    uint16_t wHubCharacteristics;
    uint8_t bPwrOn2PwrGood;
    uint8_t bHubContrCurrent;
    uint8_t bHubHdrDecLat;
    uint16_t wHubDelay;
    uint8_t DeviceRemovable;
} __PACKED;

#define USB_SIZEOF_HUB_SS_DESC 11

/* Hub status */
struct hub_status {
    uint16_t wPortStatus;
    uint16_t wPortChange;
};

/* Hub port status */
struct hub_port_status {
    uint16_t wPortStatus;
    uint16_t wPortChange;
};

#endif /* USB_HUB_H */
