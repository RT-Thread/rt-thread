/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     zyh          the first version
 */

#ifndef __UAPI_USB_CH11_H__
#define __UAPI_USB_CH11_H__

#include <rtdef.h>

/* This is arbitrary.
 * From USB 2.0 spec Table 11-13, offset 7, a hub can
 * have up to 255 ports. The most yet reported is 10.
 *
 * Current Wireless USB host hardware (Intel i1480 for example) allows
 * up to 22 devices to connect. Upcoming hardware might raise that
 * limit. Because the arrays need to add a bit for hub status data, we
 * use 31, so plus one evens out to four bytes.
 */
#define USB_MAXCHILDREN        (31U)

/* See USB 3.1 spec Table 10-5 */
#define USB_SS_MAXPORTS        (15U)

/*
 * Hub request types
 */

#define USB_RT_HUB             (USB_TYPE_CLASS | USB_RECIP_DEVICE)
#define USB_RT_PORT            (USB_TYPE_CLASS | USB_RECIP_OTHER)

/*
 * Port status type for GetPortStatus requests added in USB 3.1
 * See USB 3.1 spec Table 10-12
 */
#define HUB_PORT_STATUS         (0x00U)
#define HUB_PORT_PD_STATUS      (0x01U)
#define HUB_EXT_PORT_STATUS     (0x02U)

/*
 * Hub class requests
 * See USB 2.0 spec Table 11-16
 */
#define HUB_CLEAR_TT_BUFFER     (8U)
#define HUB_RESET_TT            (9U)
#define HUB_GET_TT_STATE        (10U)
#define HUB_STOP_TT             (11U)

/*
 * Hub class additional requests defined by USB 3.0 spec
 * See USB 3.0 spec Table 10-6
 */
#define HUB_SET_DEPTH           (12U)
#define HUB_GET_PORT_ERR_COUNT  (13U)

/*
 * Hub Class feature numbers
 * See USB 2.0 spec Table 11-17
 */
#define C_HUB_LOCAL_POWER        (0x00U)
#define C_HUB_OVER_CURRENT       (0x01U)

/*
 * Port feature numbers
 * See USB 2.0 spec Table 11-17
 */
#define USB_PORT_FEAT_CONNECTION        (0U)
#define USB_PORT_FEAT_ENABLE            (1U)
#define USB_PORT_FEAT_SUSPEND           (2U)    /* L2 suspend */
#define USB_PORT_FEAT_OVER_CURRENT      (3U)
#define USB_PORT_FEAT_RESET             (4U)
#define USB_PORT_FEAT_L1                (5U)    /* L1 suspend */
#define USB_PORT_FEAT_POWER             (8U)
#define USB_PORT_FEAT_LOWSPEED          (9U)    /* Should never be used */
#define USB_PORT_FEAT_C_CONNECTION      (16U)
#define USB_PORT_FEAT_C_ENABLE          (17U)
#define USB_PORT_FEAT_C_SUSPEND         (18U)
#define USB_PORT_FEAT_C_OVER_CURRENT    (19U)
#define USB_PORT_FEAT_C_RESET           (20U)
#define USB_PORT_FEAT_TEST              (21U)
#define USB_PORT_FEAT_INDICATOR         (22U)
#define USB_PORT_FEAT_C_PORT_L1         (23U)

/*
 * Port feature selectors added by USB 3.0 spec.
 * See USB 3.0 spec Table 10-7
 */
#define USB_PORT_FEAT_LINK_STATE            (5U)
#define USB_PORT_FEAT_U1_TIMEOUT            (23U)
#define USB_PORT_FEAT_U2_TIMEOUT            (24U)
#define USB_PORT_FEAT_C_PORT_LINK_STATE     (25U)
#define USB_PORT_FEAT_C_PORT_CONFIG_ERROR   (26U)
#define USB_PORT_FEAT_REMOTE_WAKE_MASK      (27U)
#define USB_PORT_FEAT_BH_PORT_RESET         (28U)
#define USB_PORT_FEAT_C_BH_PORT_RESET       (29U)
#define USB_PORT_FEAT_FORCE_LINKPM_ACCEPT   (30U)

#define USB_PORT_LPM_TIMEOUT(p)             (((p) & 0xff) << 8)

/* USB 3.0 hub remote wake mask bits, see table 10-14 */
#define USB_PORT_FEAT_REMOTE_WAKE_CONNECT           (0x01U << 8)
#define USB_PORT_FEAT_REMOTE_WAKE_DISCONNECT        (0x01U << 9)
#define USB_PORT_FEAT_REMOTE_WAKE_OVER_CURRENT      (0x01U << 10)

/*
 * Hub Status and Hub Change results
 * See USB 2.0 spec Table 11-19 and Table 11-20
 * USB 3.1 extends the port status request and may return 4 additional bytes.
 * See USB 3.1 spec section 10.16.2.6 Table 10-12 and 10-15
 */
struct usb_port_status {
    rt_le16_t wPortStatus;
    rt_le16_t wPortChange;
    rt_le32_t dwExtPortStatus;
} __attribute__ ((packed));

/*
 * wPortStatus bit field
 * See USB 2.0 spec Table 11-21
 */
#define USB_PORT_STAT_CONNECTION        (0x0001U)
#define USB_PORT_STAT_ENABLE            (0x0002U)
#define USB_PORT_STAT_SUSPEND           (0x0004U)
#define USB_PORT_STAT_OVERCURRENT       (0x0008U)
#define USB_PORT_STAT_RESET             (0x0010U)
#define USB_PORT_STAT_L1                (0x0020U)
/* bits 6 to 7 are reserved */
#define USB_PORT_STAT_POWER             (0x0100U)
#define USB_PORT_STAT_LOW_SPEED         (0x0200U)
#define USB_PORT_STAT_HIGH_SPEED        (0x0400U)
#define USB_PORT_STAT_TEST              (0x0800U)
#define USB_PORT_STAT_INDICATOR         (0x1000U)
/* bits 13 to 15 are reserved */

/*
 * Additions to wPortStatus bit field from USB 3.0
 * See USB 3.0 spec Table 10-10
 */
#define USB_PORT_STAT_LINK_STATE        (0x01e0U)
#define USB_SS_PORT_STAT_POWER          (0x0200U)
#define USB_SS_PORT_STAT_SPEED          (0x1c00U)
#define USB_PORT_STAT_SPEED_5GBPS       (0x0000U)
/* Valid only if port is enabled */
/* Bits that are the same from USB 2.0 */
#define USB_SS_PORT_STAT_MASK (USB_PORT_STAT_CONNECTION |        \
                USB_PORT_STAT_ENABLE |        \
                USB_PORT_STAT_OVERCURRENT | \
                USB_PORT_STAT_RESET)

/*
 * Definitions for PORT_LINK_STATE values
 * (bits 5-8) in wPortStatus
 */
#define USB_SS_PORT_LS_U0               (0x0000U)
#define USB_SS_PORT_LS_U1               (0x0020U)
#define USB_SS_PORT_LS_U2               (0x0040U)
#define USB_SS_PORT_LS_U3               (0x0060U)
#define USB_SS_PORT_LS_SS_DISABLED      (0x0080U)
#define USB_SS_PORT_LS_RX_DETECT        (0x00a0U)
#define USB_SS_PORT_LS_SS_INACTIVE      (0x00c0U)
#define USB_SS_PORT_LS_POLLING          (0x00e0U)
#define USB_SS_PORT_LS_RECOVERY         (0x0100U)
#define USB_SS_PORT_LS_HOT_RESET        (0x0120U)
#define USB_SS_PORT_LS_COMP_MOD         (0x0140U)
#define USB_SS_PORT_LS_LOOPBACK         (0x0160U)

/*
 * wPortChange bit field
 * See USB 2.0 spec Table 11-22 and USB 2.0 LPM ECN Table-4.10
 * Bits 0 to 5 shown, bits 6 to 15 are reserved
 */
#define USB_PORT_STAT_C_CONNECTION       (0x0001U)
#define USB_PORT_STAT_C_ENABLE           (0x0002U)
#define USB_PORT_STAT_C_SUSPEND          (0x0004U)
#define USB_PORT_STAT_C_OVERCURRENT      (0x0008U)
#define USB_PORT_STAT_C_RESET            (0x0010U)
#define USB_PORT_STAT_C_L1               (0x0020U)
/*
 * USB 3.0 wPortChange bit fields
 * See USB 3.0 spec Table 10-11
 */
#define USB_PORT_STAT_C_BH_RESET        (0x0020U)
#define USB_PORT_STAT_C_LINK_STATE      (0x0040U)
#define USB_PORT_STAT_C_CONFIG_ERROR    (0x0080U)

/*
 * USB 3.1 dwExtPortStatus field masks
 * See USB 3.1 spec 10.16.2.6.3 Table 10-15
 */

#define USB_EXT_PORT_STAT_RX_SPEED_ID   (0x0000000fU)
#define USB_EXT_PORT_STAT_TX_SPEED_ID   (0x000000f0U)
#define USB_EXT_PORT_STAT_RX_LANES      (0x00000f00U)
#define USB_EXT_PORT_STAT_TX_LANES      (0x0000f000U)

#define USB_EXT_PORT_RX_LANES(p) \
            (((p) & USB_EXT_PORT_STAT_RX_LANES) >> 8)
#define USB_EXT_PORT_TX_LANES(p) \
            (((p) & USB_EXT_PORT_STAT_TX_LANES) >> 12)

/*
 * wHubCharacteristics (masks)
 * See USB 2.0 spec Table 11-13, offset 3
 */
#define HUB_CHAR_LPSM                   (0x0003U) /* Logical Power Switching Mode mask */
#define HUB_CHAR_COMMON_LPSM            (0x0000U) /* All ports power control at once */
#define HUB_CHAR_INDV_PORT_LPSM         (0x0001U) /* per-port power control */
#define HUB_CHAR_NO_LPSM                (0x0002U) /* no power switching */

#define HUB_CHAR_COMPOUND               (0x0004U) /* hub is part of a compound device */

#define HUB_CHAR_OCPM                   (0x0018U) /* Over-Current Protection Mode mask */
#define HUB_CHAR_COMMON_OCPM            (0x0000U) /* All ports Over-Current reporting */
#define HUB_CHAR_INDV_PORT_OCPM         (0x0008U) /* per-port Over-current reporting */
#define HUB_CHAR_NO_OCPM                (0x0010U) /* No Over-current Protection support */

#define HUB_CHAR_TTTT                   (0x0060U) /* TT Think Time mask */
#define HUB_CHAR_PORTIND                (0x0080U) /* per-port indicators (LEDs) */

struct usb_hub_status {
    rt_le16_t wHubStatus;
    rt_le16_t wHubChange;
} __attribute__ ((packed));

/*
 * Hub Status & Hub Change bit masks
 * See USB 2.0 spec Table 11-19 and Table 11-20
 * Bits 0 and 1 for wHubStatus and wHubChange
 * Bits 2 to 15 are reserved for both
 */
#define HUB_STATUS_LOCAL_POWER          (0x0001U)
#define HUB_STATUS_OVERCURRENT          (0x0002U)
#define HUB_CHANGE_LOCAL_POWER          (0x0001U)
#define HUB_CHANGE_OVERCURRENT          (0x0002U)


/*
 * Hub descriptor
 * See USB 2.0 spec Table 11-13
 */

#define USB_DT_HUB                      (USB_TYPE_CLASS | 0x09U)
#define USB_DT_SS_HUB                   (USB_TYPE_CLASS | 0x0aU)
#define USB_DT_HUB_NONVAR_SIZE          (7U)
#define USB_DT_SS_HUB_SIZE              (12U)

/*
 * Hub Device descriptor
 * USB Hub class device protocols
 */

#define USB_HUB_PR_FS                   (0x00U) /* Full speed hub */
#define USB_HUB_PR_HS_NO_TT             (0x00U) /* Hi-speed hub without TT */
#define USB_HUB_PR_HS_SINGLE_TT         (0x01U) /* Hi-speed hub with single TT */
#define USB_HUB_PR_HS_MULTI_TT          (0x02U) /* Hi-speed hub with multiple TT */
#define USB_HUB_PR_SS                   (0x03U) /* Super speed hub */

struct usb_hub_descriptor {
    rt_uint8_t  bDescLength;
    rt_uint8_t  bDescriptorType;

    rt_uint8_t  bNbrPorts;
    rt_le16_t   wHubCharacteristics;
    rt_uint8_t  bPwrOn2PwrGood;
    rt_uint8_t  bHubContrCurrent;

    /* 2.0 and 3.0 hubs differ here */
    union {
        struct {
            /* add 1 bit for hub status change; round to bytes */
            rt_uint8_t  DeviceRemovable[(USB_MAXCHILDREN + 1 + 7) / 8];
            rt_uint8_t  PortPwrCtrlMask[(USB_MAXCHILDREN + 1 + 7) / 8];
        }  __attribute__ ((packed)) hs;

        struct {
            rt_uint8_t  bHubHdrDecLat;
            rt_le16_t   wHubDelay;
            rt_le16_t   DeviceRemovable;
        }  __attribute__ ((packed)) ss;
    } u;
} __attribute__ ((packed));

/* port indicator status selectors, tables 11-7 and 11-25 */
#define HUB_LED_AUTO                    (0x00U)
#define HUB_LED_AMBER                   (0x01U)
#define HUB_LED_GREEN                   (0x02U)
#define HUB_LED_OFF                     (0x03U)

enum hub_led_mode {
    INDICATOR_AUTO = 0,
    INDICATOR_CYCLE,
    /* software blinks for attention:  software, hardware, reserved */
    INDICATOR_GREEN_BLINK, INDICATOR_GREEN_BLINK_OFF,
    INDICATOR_AMBER_BLINK, INDICATOR_AMBER_BLINK_OFF,
    INDICATOR_ALT_BLINK, INDICATOR_ALT_BLINK_OFF
} __attribute__ ((packed));

/* Transaction Translator Think Times, in bits */
#define HUB_TTTT_8_BITS                 (0x00U)
#define HUB_TTTT_16_BITS                (0x20U)
#define HUB_TTTT_24_BITS                (0x40U)
#define HUB_TTTT_32_BITS                (0x60U)

#endif /* __UAPI_USB_CH11_H__ */
