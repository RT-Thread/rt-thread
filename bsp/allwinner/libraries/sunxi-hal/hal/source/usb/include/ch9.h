/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.

 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 * the the People's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.

 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PART'S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
 * IN ALLWINNER'SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
 * ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
 * ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PART'S TECHNOLOGY.


 * THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
 * PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
 * THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
 * OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __USB_CH9_H__
#define __USB_CH9_H__

#include <stdint.h>

/* CONTROL REQUEST SUPPORT */

/*
 * USB directions
 *
 * This bit flag is used in endpoint descriptors' bEndpointAddress field.
 * It's also one of three fields in control requests bRequestType.
 */
#define USB_DIR_OUT         0       /* to device */
#define USB_DIR_IN          0x80        /* to host */

/*
 * USB types, the second of three bRequestType fields
 */
#define USB_TYPE_MASK           (0x03 << 5)
#define USB_TYPE_STANDARD       (0x00 << 5)
#define USB_TYPE_CLASS          (0x01 << 5)
#define USB_TYPE_VENDOR         (0x02 << 5)
#define USB_TYPE_RESERVED       (0x03 << 5)

/*
 * USB recipients, the third of three bRequestType fields
 */
#define USB_RECIP_MASK          0x1f
#define USB_RECIP_DEVICE        0x00
#define USB_RECIP_INTERFACE     0x01
#define USB_RECIP_ENDPOINT      0x02
#define USB_RECIP_OTHER         0x03
/* From Wireless USB 1.0 */
#define USB_RECIP_PORT          0x04
#define USB_RECIP_RPIPE     0x05

/*
 * Standard requests, for the bRequest field of a SETUP packet.
 *
 * These are qualified by the bRequestType field, so that for example
 * TYPE_CLASS or TYPE_VENDOR specific feature flags could be retrieved
 * by a GET_STATUS request.
 */
#define USB_REQ_GET_STATUS      0x00
#define USB_REQ_CLEAR_FEATURE       0x01
#define USB_REQ_SET_FEATURE     0x03
#define USB_REQ_SET_ADDRESS     0x05
#define USB_REQ_GET_DESCRIPTOR      0x06
#define USB_REQ_SET_DESCRIPTOR      0x07
#define USB_REQ_GET_CONFIGURATION   0x08
#define USB_REQ_SET_CONFIGURATION   0x09
#define USB_REQ_GET_INTERFACE       0x0A
#define USB_REQ_SET_INTERFACE       0x0B
#define USB_REQ_SYNCH_FRAME     0x0C
#define USB_REQ_SET_SEL         0x30
#define USB_REQ_SET_ISOCH_DELAY     0x31

#define USB_REQ_SET_ENCRYPTION      0x0D    /* Wireless USB */
#define USB_REQ_GET_ENCRYPTION      0x0E
#define USB_REQ_RPIPE_ABORT     0x0E
#define USB_REQ_SET_HANDSHAKE       0x0F
#define USB_REQ_RPIPE_RESET     0x0F
#define USB_REQ_GET_HANDSHAKE       0x10
#define USB_REQ_SET_CONNECTION      0x11
#define USB_REQ_SET_SECURITY_DATA   0x12
#define USB_REQ_GET_SECURITY_DATA   0x13
#define USB_REQ_SET_WUSB_DATA       0x14
#define USB_REQ_LOOPBACK_DATA_WRITE 0x15
#define USB_REQ_LOOPBACK_DATA_READ  0x16
#define USB_REQ_SET_INTERFACE_DS    0x17

/* specific requests for USB Power Delivery */
#define USB_REQ_GET_PARTNER_PDO     20
#define USB_REQ_GET_BATTERY_STATUS  21
#define USB_REQ_SET_PDO         22
#define USB_REQ_GET_VDM         23
#define USB_REQ_SEND_VDM        24

/* The Link Power Management (LPM) ECN defines USB_REQ_TEST_AND_SET command,
 * used by hubs to put ports into a new L1 suspend state, except that it
 * forgot to define its number ...
 */

/*
 * USB feature flags are written using USB_REQ_{CLEAR,SET}_FEATURE, and
 * are read as a bit array returned by USB_REQ_GET_STATUS.  (So there
 * are at most sixteen features of each type.)  Hubs may also support a
 * new USB_REQ_TEST_AND_SET_FEATURE to put ports into L1 suspend.
 */
#define USB_DEVICE_SELF_POWERED     0   /* (read only) */
#define USB_DEVICE_REMOTE_WAKEUP    1   /* dev may initiate wakeup */
#define USB_DEVICE_TEST_MODE        2   /* (wired high speed only) */
#define USB_DEVICE_BATTERY      2   /* (wireless) */
#define USB_DEVICE_B_HNP_ENABLE     3   /* (otg) dev may initiate HNP */
#define USB_DEVICE_WUSB_DEVICE      3   /* (wireless)*/
#define USB_DEVICE_A_HNP_SUPPORT    4   /* (otg) RH port supports HNP */
#define USB_DEVICE_A_ALT_HNP_SUPPORT    5   /* (otg) other RH port does */
#define USB_DEVICE_DEBUG_MODE       6   /* (special devices only) */

/*
 * Test Mode Selectors
 * See USB 2.0 spec Table 9-7
 */
#define TEST_J      1
#define TEST_K      2
#define TEST_SE0_NAK    3
#define TEST_PACKET 4
#define TEST_FORCE_EN   5

/*
 * New Feature Selectors as added by USB 3.0
 * See USB 3.0 spec Table 9-7
 */
#define USB_DEVICE_U1_ENABLE    48  /* dev may initiate U1 transition */
#define USB_DEVICE_U2_ENABLE    49  /* dev may initiate U2 transition */
#define USB_DEVICE_LTM_ENABLE   50  /* dev may send LTM */
#define USB_INTRF_FUNC_SUSPEND  0   /* function suspend */

#define USB_INTR_FUNC_SUSPEND_OPT_MASK  0xFF00
/*
 * Suspend Options, Table 9-8 USB 3.0 spec
 */
#define USB_INTRF_FUNC_SUSPEND_LP   (1 << (8 + 0))
#define USB_INTRF_FUNC_SUSPEND_RW   (1 << (8 + 1))

/*
 * Interface status, Figure 9-5 USB 3.0 spec
 */
#define USB_INTRF_STAT_FUNC_RW_CAP     1
#define USB_INTRF_STAT_FUNC_RW         2

#define USB_ENDPOINT_HALT       0   /* IN/OUT will STALL */

/* Bit array elements as returned by the USB_REQ_GET_STATUS request. */
#define USB_DEV_STAT_U1_ENABLED     2   /* transition into U1 state */
#define USB_DEV_STAT_U2_ENABLED     3   /* transition into U2 state */
#define USB_DEV_STAT_LTM_ENABLED    4   /* Latency tolerance messages */

/*
 * Feature selectors from Table 9-8 USB Power Delivery spec
 */
#define USB_DEVICE_BATTERY_WAKE_MASK    40
#define USB_DEVICE_OS_IS_PD_AWARE   41
#define USB_DEVICE_POLICY_MODE      42
#define USB_PORT_PR_SWAP        43
#define USB_PORT_GOTO_MIN       44
#define USB_PORT_RETURN_POWER       45
#define USB_PORT_ACCEPT_PD_REQUEST  46
#define USB_PORT_REJECT_PD_REQUEST  47
#define USB_PORT_PORT_PD_RESET      48
#define USB_PORT_C_PORT_PD_CHANGE   49
#define USB_PORT_CABLE_PD_RESET     50
#define USB_DEVICE_CHARGING_POLICY  54

/**
 * struct usb_ctrlrequest - SETUP data for a USB device control request
 * @bRequestType: matches the USB bmRequestType field
 * @bRequest: matches the USB bRequest field
 * @wValue: matches the USB wValue field (le16 byte order)
 * @wIndex: matches the USB wIndex field (le16 byte order)
 * @wLength: matches the USB wLength field (le16 byte order)
 *
 * This structure is used to send control requests to a USB device.  It matches
 * the different fields of the USB 2.0 Spec section 9.3, table 9-2.  See the
 * USB spec for a fuller description of the different fields, and what they are
 * used for.
 *
 * Note that the driver for any interface can issue control requests.
 * For most devices, interfaces don't coordinate with each other, so
 * such requests may be made at any time.
 */
struct usb_ctrlrequest {
    uint8_t bRequestType;
    uint8_t bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
};

/*-------------------------------------------------------------------------*/

/*
 * STANDARD DESCRIPTORS ... as returned by GET_DESCRIPTOR, or
 * (rarely) accepted by SET_DESCRIPTOR.
 *
 * Note that all multi-byte values here are encoded in little endian
 * byte order "on the wire".  Within the kernel and when exposed
 * through the Linux-USB APIs, they are not converted to cpu byte
 * order; it is the responsibility of the client code to do this.
 * The single exception is when device and configuration descriptors (but
 * not other descriptors) are read from usbfs (i.e. /proc/bus/usb/BBB/DDD);
 * in this case the fields are converted to host endianness by the kernel.
 */

/*
 * Descriptor types ... USB 2.0 spec table 9.5
 */
#define USB_DT_DEVICE           0x01
#define USB_DT_CONFIG           0x02
#define USB_DT_STRING           0x03
#define USB_DT_INTERFACE        0x04
#define USB_DT_ENDPOINT         0x05
#define USB_DT_DEVICE_QUALIFIER     0x06
#define USB_DT_OTHER_SPEED_CONFIG   0x07
#define USB_DT_INTERFACE_POWER      0x08
/* these are from a minor usb 2.0 revision (ECN) */
#define USB_DT_OTG          0x09
#define USB_DT_DEBUG            0x0a
#define USB_DT_INTERFACE_ASSOCIATION    0x0b
/* these are from the Wireless USB spec */
#define USB_DT_SECURITY         0x0c
#define USB_DT_KEY          0x0d
#define USB_DT_ENCRYPTION_TYPE      0x0e
#define USB_DT_BOS          0x0f
#define USB_DT_DEVICE_CAPABILITY    0x10
#define USB_DT_WIRELESS_ENDPOINT_COMP   0x11
#define USB_DT_WIRE_ADAPTER     0x21
#define USB_DT_RPIPE            0x22
#define USB_DT_CS_RADIO_CONTROL     0x23
/* From the T10 UAS specification */
#define USB_DT_PIPE_USAGE       0x24
/* From the USB 3.0 spec */
#define USB_DT_SS_ENDPOINT_COMP     0x30
/* From the USB 3.1 spec */
#define USB_DT_SSP_ISOC_ENDPOINT_COMP   0x31

/* Conventional codes for class-specific descriptors.  The convention is
 * defined in the USB "Common Class" Spec (3.11).  Individual class specs
 * are authoritative for their usage, not the "common class" writeup.
 */
#define USB_DT_CS_DEVICE        (USB_TYPE_CLASS | USB_DT_DEVICE)
#define USB_DT_CS_CONFIG        (USB_TYPE_CLASS | USB_DT_CONFIG)
#define USB_DT_CS_STRING        (USB_TYPE_CLASS | USB_DT_STRING)
#define USB_DT_CS_INTERFACE     (USB_TYPE_CLASS | USB_DT_INTERFACE)
#define USB_DT_CS_ENDPOINT      (USB_TYPE_CLASS | USB_DT_ENDPOINT)

/* All standard descriptors have these 2 fields at the beginning */
struct usb_descriptor_header {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
};


/*-------------------------------------------------------------------------*/

/* USB_DT_DEVICE: Device descriptor */
struct usb_device_descriptor {
    uint8_t  bLength;
    uint8_t  bDescriptorType;

    uint16_t bcdUSB;
    uint8_t  bDeviceClass;
    uint8_t  bDeviceSubClass;
    uint8_t  bDeviceProtocol;
    uint8_t  bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t  iManufacturer;
    uint8_t  iProduct;
    uint8_t  iSerialNumber;
    uint8_t  bNumConfigurations;
};

#define USB_DT_DEVICE_SIZE      18


/*
 * Device and/or Interface Class codes
 * as found in bDeviceClass or bInterfaceClass
 * and defined by www.usb.org documents
 */
#define USB_CLASS_PER_INTERFACE     0   /* for DeviceClass */
#define USB_CLASS_AUDIO         1
#define USB_CLASS_COMM          2
#define USB_CLASS_HID           3
#define USB_CLASS_PHYSICAL      5
#define USB_CLASS_STILL_IMAGE       6
#define USB_CLASS_PRINTER       7
#define USB_CLASS_MASS_STORAGE      8
#define USB_CLASS_HUB           9
#define USB_CLASS_CDC_DATA      0x0a
#define USB_CLASS_CSCID         0x0b    /* chip+ smart card */
#define USB_CLASS_CONTENT_SEC       0x0d    /* content security */
#define USB_CLASS_VIDEO         0x0e
#define USB_CLASS_WIRELESS_CONTROLLER   0xe0
#define USB_CLASS_MISC          0xef
#define USB_CLASS_APP_SPEC      0xfe
#define USB_CLASS_VENDOR_SPEC       0xff

#define USB_SUBCLASS_VENDOR_SPEC    0xff

/*-------------------------------------------------------------------------*/

/* USB_DT_CONFIG: Configuration descriptor information.
 *
 * USB_DT_OTHER_SPEED_CONFIG is the same descriptor, except that the
 * descriptor type is different.  Highspeed-capable devices can look
 * different depending on what speed they're currently running.  Only
 * devices with a USB_DT_DEVICE_QUALIFIER have any OTHER_SPEED_CONFIG
 * descriptors.
 */
struct usb_config_descriptor {
    uint8_t  bLength;
    uint8_t  bDescriptorType;

    uint16_t wTotalLength;
    uint8_t  bNumInterfaces;
    uint8_t  bConfigurationValue;
    uint8_t  iConfiguration;
    uint8_t  bmAttributes;
    uint8_t  bMaxPower;
};

#define USB_DT_CONFIG_SIZE      9

/* from config descriptor bmAttributes */
#define USB_CONFIG_ATT_ONE      (1 << 7)    /* must be set */
#define USB_CONFIG_ATT_SELFPOWER    (1 << 6)    /* self powered */
#define USB_CONFIG_ATT_WAKEUP       (1 << 5)    /* can wakeup */
#define USB_CONFIG_ATT_BATTERY      (1 << 4)    /* battery powered */

/*-------------------------------------------------------------------------*/

/* USB_DT_STRING: String descriptor */
struct usb_string_descriptor {
    uint8_t  bLength;
    uint8_t  bDescriptorType;

    uint16_t wData[1];      /* UTF-16LE encoded */
};

/* note that "string" zero is special, it holds language codes that
 * the device supports, not Unicode characters.
 */

/*-------------------------------------------------------------------------*/

/* USB_DT_INTERFACE: Interface descriptor */
struct usb_interface_descriptor {
    uint8_t  bLength;
    uint8_t  bDescriptorType;

    uint8_t  bInterfaceNumber;
    uint8_t  bAlternateSetting;
    uint8_t  bNumEndpoints;
    uint8_t  bInterfaceClass;
    uint8_t  bInterfaceSubClass;
    uint8_t  bInterfaceProtocol;
    uint8_t  iInterface;
};

#define USB_DT_INTERFACE_SIZE       9

/*-------------------------------------------------------------------------*/

/* USB_DT_ENDPOINT: Endpoint descriptor */
struct usb_endpoint_descriptor {
    uint8_t  bLength;
    uint8_t  bDescriptorType;

    uint8_t  bEndpointAddress;
    uint8_t  bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t  bInterval;

    /* NOTE:  these two are _only_ in audio endpoints. */
    /* use USB_DT_ENDPOINT*_SIZE in bLength, not sizeof. */
    uint8_t  bRefresh;
    uint8_t  bSynchAddress;
};


/* USB_DT_DEVICE_QUALIFIER: Device Qualifier descriptor */
struct __attribute__((packed)) usb_qualifier_descriptor
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;

    uint16_t bcdUSB;
    uint8_t  bDeviceClass;
    uint8_t  bDeviceSubClass;
    uint8_t  bDeviceProtocol;
    uint8_t  bMaxPacketSize0;
    uint8_t  bNumConfigurations;
    uint8_t  bRESERVED;
};


#define USB_DT_ENDPOINT_SIZE        7
#define USB_DT_ENDPOINT_AUDIO_SIZE  9   /* Audio extension */


/*
 * Endpoints
 */
#define USB_ENDPOINT_NUMBER_MASK    0x0f    /* in bEndpointAddress */
#define USB_ENDPOINT_DIR_MASK       0x80

#define USB_ENDPOINT_XFERTYPE_MASK  0x03    /* in bmAttributes */
#define USB_ENDPOINT_XFER_CONTROL   0
#define USB_ENDPOINT_XFER_ISOC      1
#define USB_ENDPOINT_XFER_BULK      2
#define USB_ENDPOINT_XFER_INT       3
#define USB_ENDPOINT_MAX_ADJUSTABLE 0x80

#define USB_EP_MAXP_MULT_SHIFT  11
#define USB_EP_MAXP_MULT_MASK   (3 << USB_EP_MAXP_MULT_SHIFT)
#define USB_EP_MAXP_MULT(m) \
    (((m) & USB_EP_MAXP_MULT_MASK) >> USB_EP_MAXP_MULT_SHIFT)

/* The USB 3.0 spec redefines bits 5:4 of bmAttributes as interrupt ep type. */
#define USB_ENDPOINT_INTRTYPE       0x30
#define USB_ENDPOINT_INTR_PERIODIC  (0 << 4)
#define USB_ENDPOINT_INTR_NOTIFICATION  (1 << 4)

#define USB_ENDPOINT_SYNCTYPE       0x0c
#define USB_ENDPOINT_SYNC_NONE      (0 << 2)
#define USB_ENDPOINT_SYNC_ASYNC     (1 << 2)
#define USB_ENDPOINT_SYNC_ADAPTIVE  (2 << 2)
#define USB_ENDPOINT_SYNC_SYNC      (3 << 2)

#define USB_ENDPOINT_USAGE_MASK     0x30
#define USB_ENDPOINT_USAGE_DATA     0x00
#define USB_ENDPOINT_USAGE_FEEDBACK 0x10
#define USB_ENDPOINT_USAGE_IMPLICIT_FB  0x20    /* Implicit feedback Data endpoint */

static inline int usb_endpoint_num(const struct usb_endpoint_descriptor *epd)
{
    return epd->bEndpointAddress & USB_ENDPOINT_NUMBER_MASK;
}
static inline int usb_endpoint_type(const struct usb_endpoint_descriptor *epd)
{
    return epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK;
}

static inline int usb_endpoint_dir_in(const struct usb_endpoint_descriptor *epd)
{
    return ((epd->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN);
}

static inline int usb_endpoint_dir_out(
                const struct usb_endpoint_descriptor *epd)
{
    return ((epd->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_OUT);
}

static inline int usb_endpoint_xfer_bulk(
                const struct usb_endpoint_descriptor *epd)
{
    return ((epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
        USB_ENDPOINT_XFER_BULK);
}
static inline int usb_endpoint_xfer_control(
                const struct usb_endpoint_descriptor *epd)
{
    return ((epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
        USB_ENDPOINT_XFER_CONTROL);
}
static inline int usb_endpoint_xfer_int(
                const struct usb_endpoint_descriptor *epd)
{
    return ((epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
        USB_ENDPOINT_XFER_INT);
}
static inline int usb_endpoint_xfer_isoc(
                const struct usb_endpoint_descriptor *epd)
{
    return ((epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
        USB_ENDPOINT_XFER_ISOC);
}
static inline int usb_endpoint_is_bulk_in(
                const struct usb_endpoint_descriptor *epd)
{
    return usb_endpoint_xfer_bulk(epd) && usb_endpoint_dir_in(epd);
}
static inline int usb_endpoint_is_bulk_out(
                const struct usb_endpoint_descriptor *epd)
{
    return usb_endpoint_xfer_bulk(epd) && usb_endpoint_dir_out(epd);
}
static inline int usb_endpoint_is_int_in(
                const struct usb_endpoint_descriptor *epd)
{
    return usb_endpoint_xfer_int(epd) && usb_endpoint_dir_in(epd);
}
static inline int usb_endpoint_is_int_out(
                const struct usb_endpoint_descriptor *epd)
{
    return usb_endpoint_xfer_int(epd) && usb_endpoint_dir_out(epd);
}
static inline int usb_endpoint_is_isoc_in(
                const struct usb_endpoint_descriptor *epd)
{
    return usb_endpoint_xfer_isoc(epd) && usb_endpoint_dir_in(epd);
}
static inline int usb_endpoint_is_isoc_out(
                const struct usb_endpoint_descriptor *epd)
{
    return usb_endpoint_xfer_isoc(epd) && usb_endpoint_dir_out(epd);
}
static inline int usb_endpoint_maxp(const struct usb_endpoint_descriptor *epd)
{
    return le16_to_cpu(epd->wMaxPacketSize);
}

enum usb_device_speed {
    USB_SPEED_UNKNOWN = 0,          /* enumerating */
    USB_SPEED_LOW, USB_SPEED_FULL,      /* usb 1.1 */
    USB_SPEED_HIGH,             /* usb 2.0 */
    USB_SPEED_WIRELESS,         /* wireless (usb 2.5) */
    USB_SPEED_SUPER,            /* usb 3.0 */
    USB_SPEED_SUPER_PLUS,           /* usb 3.1 */
};
enum usb_device_state {
    USB_STATE_NOTATTACHED = 0,
    USB_STATE_ATTACHED,
    USB_STATE_POWERED,          /* wired */
    USB_STATE_RECONNECTING,         /* auth */
    USB_STATE_UNAUTHENTICATED,      /* auth */
    USB_STATE_DEFAULT,          /* limited function */
    USB_STATE_ADDRESS,
    USB_STATE_CONFIGURED,           /* most functions */
    USB_STATE_SUSPENDED
};
#endif /*__USB_CH9_H__*/
