/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_DEF_H
#define USB_DEF_H

/* Useful define */
#define USB_1_1 0x0110
#define USB_2_0 0x0200
/* Set USB version to 2.1 so that the host will request the BOS descriptor */
#define USB_2_1 0x0210
#define USB_3_0 0x0300
#define USB_3_1 0x0310
#define USB_3_2 0x0320

/* Device speeds */
#define USB_SPEED_UNKNOWN    0 /* Transfer rate not yet set */
#define USB_SPEED_LOW        1 /* USB 1.1 */
#define USB_SPEED_FULL       2 /* USB 1.1 */
#define USB_SPEED_HIGH       3 /* USB 2.0 */
#define USB_SPEED_WIRELESS   4 /* Wireless USB 2.5 */
#define USB_SPEED_SUPER      5 /* USB 3.0 */
#define USB_SPEED_SUPER_PLUS 6 /* USB 3.1 */

/* Maximum number of devices per controller */
#define USB_MAX_DEVICES (127)

/* Default USB control EP, always 0 and 0x80 */
#define USB_CONTROL_OUT_EP0 0
#define USB_CONTROL_IN_EP0  0x80

/**< maximum packet size (MPS) for EP 0 */
#define USB_CTRL_EP_MPS 64

/**< maximum packet size (MPS) for bulk EP */
#define USB_BULK_EP_MPS_HS 512
#define USB_BULK_EP_MPS_FS 64

/* USB PID Types */
#define USB_PID_OUT   (0x01) /* Tokens */
#define USB_PID_IN    (0x09)
#define USB_PID_SOF   (0x05)
#define USB_PID_SETUP (0x0d)

#define USB_PID_DATA0 (0x03) /* Data */
#define USB_PID_DATA1 (0x0b)
#define USB_PID_DATA2 (0x07)
#define USB_PID_MDATA (0x0f)

#define USB_PID_ACK   (0x02) /* Handshake */
#define USB_PID_NAK   (0x0a)
#define USB_PID_STALL (0x0e)
#define USB_PID_NYET  (0x06)

#define USB_PID_PRE      (0x0c) /* Special */
#define USB_PID_ERR      (0x0c)
#define USB_PID_SPLIT    (0x08)
#define USB_PID_PING     (0x04)
#define USB_PID_RESERVED (0x00)

#define USB_REQUEST_DIR_SHIFT 7U                            /* Bits 7: Request dir */
#define USB_REQUEST_DIR_OUT   (0U << USB_REQUEST_DIR_SHIFT) /* Bit 7=0: Host-to-device */
#define USB_REQUEST_DIR_IN    (1U << USB_REQUEST_DIR_SHIFT) /* Bit 7=1: Device-to-host */
#define USB_REQUEST_DIR_MASK  (1U << USB_REQUEST_DIR_SHIFT) /* Bit 7=1: Direction bit */

#define USB_REQUEST_TYPE_SHIFT 5U /* Bits 5:6: Request type */
#define USB_REQUEST_STANDARD   (0U << USB_REQUEST_TYPE_SHIFT)
#define USB_REQUEST_CLASS      (1U << USB_REQUEST_TYPE_SHIFT)
#define USB_REQUEST_VENDOR     (2U << USB_REQUEST_TYPE_SHIFT)
#define USB_REQUEST_RESERVED   (3U << USB_REQUEST_TYPE_SHIFT)
#define USB_REQUEST_TYPE_MASK  (3U << USB_REQUEST_TYPE_SHIFT)

#define USB_REQUEST_RECIPIENT_SHIFT     0U /* Bits 0:4: Recipient */
#define USB_REQUEST_RECIPIENT_DEVICE    (0U << USB_REQUEST_RECIPIENT_SHIFT)
#define USB_REQUEST_RECIPIENT_INTERFACE (1U << USB_REQUEST_RECIPIENT_SHIFT)
#define USB_REQUEST_RECIPIENT_ENDPOINT  (2U << USB_REQUEST_RECIPIENT_SHIFT)
#define USB_REQUEST_RECIPIENT_OTHER     (3U << USB_REQUEST_RECIPIENT_SHIFT)
#define USB_REQUEST_RECIPIENT_MASK      (3U << USB_REQUEST_RECIPIENT_SHIFT)

/* USB Standard Request Codes */
#define USB_REQUEST_GET_STATUS          0x00
#define USB_REQUEST_CLEAR_FEATURE       0x01
#define USB_REQUEST_SET_FEATURE         0x03
#define USB_REQUEST_SET_ADDRESS         0x05
#define USB_REQUEST_GET_DESCRIPTOR      0x06
#define USB_REQUEST_SET_DESCRIPTOR      0x07
#define USB_REQUEST_GET_CONFIGURATION   0x08
#define USB_REQUEST_SET_CONFIGURATION   0x09
#define USB_REQUEST_GET_INTERFACE       0x0A
#define USB_REQUEST_SET_INTERFACE       0x0B
#define USB_REQUEST_SYNCH_FRAME         0x0C
#define USB_REQUEST_SET_ENCRYPTION      0x0D
#define USB_REQUEST_GET_ENCRYPTION      0x0E
#define USB_REQUEST_RPIPE_ABORT         0x0E
#define USB_REQUEST_SET_HANDSHAKE       0x0F
#define USB_REQUEST_RPIPE_RESET         0x0F
#define USB_REQUEST_GET_HANDSHAKE       0x10
#define USB_REQUEST_SET_CONNECTION      0x11
#define USB_REQUEST_SET_SECURITY_DATA   0x12
#define USB_REQUEST_GET_SECURITY_DATA   0x13
#define USB_REQUEST_SET_WUSB_DATA       0x14
#define USB_REQUEST_LOOPBACK_DATA_WRITE 0x15
#define USB_REQUEST_LOOPBACK_DATA_READ  0x16
#define USB_REQUEST_SET_INTERFACE_DS    0x17

/* USB Standard Feature selectors */
#define USB_FEATURE_ENDPOINT_HALT  0
#define USB_FEATURE_SELF_POWERED   0
#define USB_FEATURE_REMOTE_WAKEUP  1
#define USB_FEATURE_TEST_MODE      2
#define USB_FEATURE_BATTERY        2
#define USB_FEATURE_BHNPENABLE     3
#define USB_FEATURE_WUSBDEVICE     3
#define USB_FEATURE_AHNPSUPPORT    4
#define USB_FEATURE_AALTHNPSUPPORT 5
#define USB_FEATURE_DEBUGMODE      6

/* USB GET_STATUS Bit Values */
#define USB_GETSTATUS_ENDPOINT_HALT 0x01
#define USB_GETSTATUS_SELF_POWERED  0x01
#define USB_GETSTATUS_REMOTE_WAKEUP 0x02

/* USB Descriptor Types */
#define USB_DESCRIPTOR_TYPE_DEVICE                0x01U
#define USB_DESCRIPTOR_TYPE_CONFIGURATION         0x02U
#define USB_DESCRIPTOR_TYPE_STRING                0x03U
#define USB_DESCRIPTOR_TYPE_INTERFACE             0x04U
#define USB_DESCRIPTOR_TYPE_ENDPOINT              0x05U
#define USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER      0x06U
#define USB_DESCRIPTOR_TYPE_OTHER_SPEED           0x07U
#define USB_DESCRIPTOR_TYPE_INTERFACE_POWER       0x08U
#define USB_DESCRIPTOR_TYPE_OTG                   0x09U
#define USB_DESCRIPTOR_TYPE_DEBUG                 0x0AU
#define USB_DESCRIPTOR_TYPE_INTERFACE_ASSOCIATION 0x0BU
#define USB_DESCRIPTOR_TYPE_BINARY_OBJECT_STORE   0x0FU
#define USB_DESCRIPTOR_TYPE_DEVICE_CAPABILITY     0x10U
#define USB_DESCRIPTOR_TYPE_WIRELESS_ENDPOINTCOMP 0x11U

/* Class Specific Descriptor */
#define USB_CS_DESCRIPTOR_TYPE_DEVICE        0x21U
#define USB_CS_DESCRIPTOR_TYPE_CONFIGURATION 0x22U
#define USB_CS_DESCRIPTOR_TYPE_STRING        0x23U
#define USB_CS_DESCRIPTOR_TYPE_INTERFACE     0x24U
#define USB_CS_DESCRIPTOR_TYPE_ENDPOINT      0x25U

#define USB_DESCRIPTOR_TYPE_SUPERSPEED_ENDPOINT_COMPANION     0x30U
#define USB_DESCRIPTOR_TYPE_SUPERSPEED_ISO_ENDPOINT_COMPANION 0x31U

/* USB Device Classes */
#define USB_DEVICE_CLASS_RESERVED      0x00
#define USB_DEVICE_CLASS_AUDIO         0x01
#define USB_DEVICE_CLASS_CDC           0x02
#define USB_DEVICE_CLASS_HID           0x03
#define USB_DEVICE_CLASS_MONITOR       0x04
#define USB_DEVICE_CLASS_PHYSICAL      0x05
#define USB_DEVICE_CLASS_IMAGE         0x06
#define USB_DEVICE_CLASS_PRINTER       0x07
#define USB_DEVICE_CLASS_MASS_STORAGE  0x08
#define USB_DEVICE_CLASS_HUB           0x09
#define USB_DEVICE_CLASS_CDC_DATA      0x0a
#define USB_DEVICE_CLASS_SMART_CARD    0x0b
#define USB_DEVICE_CLASS_SECURITY      0x0d
#define USB_DEVICE_CLASS_VIDEO         0x0e
#define USB_DEVICE_CLASS_HEALTHCARE    0x0f
#define USB_DEVICE_CLASS_DIAG_DEVICE   0xdc
#define USB_DEVICE_CLASS_WIRELESS      0xe0
#define USB_DEVICE_CLASS_MISC          0xef
#define USB_DEVICE_CLASS_APP_SPECIFIC  0xfe
#define USB_DEVICE_CLASS_VEND_SPECIFIC 0xff

/* usb string index define */
#define USB_STRING_LANGID_INDEX    0x00
#define USB_STRING_MFC_INDEX       0x01
#define USB_STRING_PRODUCT_INDEX   0x02
#define USB_STRING_SERIAL_INDEX    0x03
#define USB_STRING_CONFIG_INDEX    0x04
#define USB_STRING_INTERFACE_INDEX 0x05
#define USB_STRING_OS_INDEX        0x06
#define USB_STRING_MAX             USB_STRING_OS_INDEX
/*
 * Devices supporting Microsoft OS Descriptors store special string
 * descriptor at fixed index (0xEE). It is read when a new device is
 * attached to a computer for the first time.
 */
#define USB_OSDESC_STRING_DESC_INDEX 0xEE

/* bmAttributes in Configuration Descriptor */
#define USB_CONFIG_REMOTE_WAKEUP 0x20
#define USB_CONFIG_POWERED_MASK  0x40
#define USB_CONFIG_BUS_POWERED   0x80
#define USB_CONFIG_SELF_POWERED  0xC0

/* bMaxPower in Configuration Descriptor */
#define USB_CONFIG_POWER_MA(mA) ((mA) / 2)

/* bEndpointAddress in Endpoint Descriptor */
#define USB_ENDPOINT_DIRECTION_MASK 0x80
#define USB_ENDPOINT_OUT(addr)      ((addr) | 0x00)
#define USB_ENDPOINT_IN(addr)       ((addr) | 0x80)

/**
 * USB endpoint direction and number.
 */
#define USB_EP_DIR_MASK 0x80U
#define USB_EP_DIR_IN   0x80U
#define USB_EP_DIR_OUT  0x00U

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

/* bmAttributes in Endpoint Descriptor */
#define USB_ENDPOINT_TYPE_SHIFT       0
#define USB_ENDPOINT_TYPE_CONTROL     (0 << USB_ENDPOINT_TYPE_SHIFT)
#define USB_ENDPOINT_TYPE_ISOCHRONOUS (1 << USB_ENDPOINT_TYPE_SHIFT)
#define USB_ENDPOINT_TYPE_BULK        (2 << USB_ENDPOINT_TYPE_SHIFT)
#define USB_ENDPOINT_TYPE_INTERRUPT   (3 << USB_ENDPOINT_TYPE_SHIFT)
#define USB_ENDPOINT_TYPE_MASK        (3 << USB_ENDPOINT_TYPE_SHIFT)
#define USB_GET_ENDPOINT_TYPE(x)      ((x & USB_ENDPOINT_TYPE_MASK) >> USB_ENDPOINT_TYPE_SHIFT)

#define USB_ENDPOINT_SYNC_SHIFT              2
#define USB_ENDPOINT_SYNC_NO_SYNCHRONIZATION (0 << USB_ENDPOINT_SYNC_SHIFT)
#define USB_ENDPOINT_SYNC_ASYNCHRONOUS       (1 << USB_ENDPOINT_SYNC_SHIFT)
#define USB_ENDPOINT_SYNC_ADAPTIVE           (2 << USB_ENDPOINT_SYNC_SHIFT)
#define USB_ENDPOINT_SYNC_SYNCHRONOUS        (3 << USB_ENDPOINT_SYNC_SHIFT)
#define USB_ENDPOINT_SYNC_MASK               (3 << USB_ENDPOINT_SYNC_SHIFT)

#define USB_ENDPOINT_USAGE_SHIFT             4
#define USB_ENDPOINT_USAGE_DATA              (0 << USB_ENDPOINT_USAGE_SHIFT)
#define USB_ENDPOINT_USAGE_FEEDBACK          (1 << USB_ENDPOINT_USAGE_SHIFT)
#define USB_ENDPOINT_USAGE_IMPLICIT_FEEDBACK (2 << USB_ENDPOINT_USAGE_SHIFT)
#define USB_ENDPOINT_USAGE_MASK              (3 << USB_ENDPOINT_USAGE_SHIFT)

#define USB_ENDPOINT_MAX_ADJUSTABLE (1 << 7)

/* wMaxPacketSize in Endpoint Descriptor */
#define USB_MAXPACKETSIZE_SHIFT                        0
#define USB_MAXPACKETSIZE_MASK                         (0x7ff << USB_MAXPACKETSIZE_SHIFT)
#define USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT 11
#define USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_NONE  (0 << USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT)
#define USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_ONE   (1 << USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT)
#define USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_TWO   (2 << USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT)
#define USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_MASK  (3 << USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT)
#define USB_GET_MAXPACKETSIZE(x)                       ((x & USB_MAXPACKETSIZE_MASK) >> USB_MAXPACKETSIZE_SHIFT)
#define USB_GET_MULT(x)                                ((x & USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_MASK) >> USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT)

/* bDevCapabilityType in Device Capability Descriptor */
#define USB_DEVICE_CAPABILITY_WIRELESS_USB                1
#define USB_DEVICE_CAPABILITY_USB_2_0_EXTENSION           2
#define USB_DEVICE_CAPABILITY_SUPERSPEED_USB              3
#define USB_DEVICE_CAPABILITY_CONTAINER_ID                4
#define USB_DEVICE_CAPABILITY_PLATFORM                    5
#define USB_DEVICE_CAPABILITY_POWER_DELIVERY_CAPABILITY   6
#define USB_DEVICE_CAPABILITY_BATTERY_INFO_CAPABILITY     7
#define USB_DEVICE_CAPABILITY_PD_CONSUMER_PORT_CAPABILITY 8
#define USB_DEVICE_CAPABILITY_PD_PROVIDER_PORT_CAPABILITY 9
#define USB_DEVICE_CAPABILITY_SUPERSPEED_PLUS             10
#define USB_DEVICE_CAPABILITY_PRECISION_TIME_MEASUREMENT  11
#define USB_DEVICE_CAPABILITY_WIRELESS_USB_EXT            12

#define USB_BOS_CAPABILITY_EXTENSION 0x02
#define USB_BOS_CAPABILITY_PLATFORM  0x05

/* OTG SET FEATURE Constants */
#define USB_OTG_FEATURE_B_HNP_ENABLE      3 /* Enable B device to perform HNP */
#define USB_OTG_FEATURE_A_HNP_SUPPORT     4 /* A device supports HNP */
#define USB_OTG_FEATURE_A_ALT_HNP_SUPPORT 5 /* Another port on the A device supports HNP */

/* WinUSB Microsoft OS 2.0 descriptor request codes */
#define WINUSB_REQUEST_GET_DESCRIPTOR_SET 0x07
#define WINUSB_REQUEST_SET_ALT_ENUM       0x08

/* WinUSB Microsoft OS 2.0 descriptor sizes */
#define WINUSB_DESCRIPTOR_SET_HEADER_SIZE  10
#define WINUSB_FUNCTION_SUBSET_HEADER_SIZE 8
#define WINUSB_FEATURE_COMPATIBLE_ID_SIZE  20

/* WinUSB Microsoft OS 2.0 Descriptor Types */
#define WINUSB_SET_HEADER_DESCRIPTOR_TYPE       0x00
#define WINUSB_SUBSET_HEADER_CONFIGURATION_TYPE 0x01
#define WINUSB_SUBSET_HEADER_FUNCTION_TYPE      0x02
#define WINUSB_FEATURE_COMPATIBLE_ID_TYPE       0x03
#define WINUSB_FEATURE_REG_PROPERTY_TYPE        0x04
#define WINUSB_FEATURE_MIN_RESUME_TIME_TYPE     0x05
#define WINUSB_FEATURE_MODEL_ID_TYPE            0x06
#define WINUSB_FEATURE_CCGP_DEVICE_TYPE         0x07

#define WINUSB_PROP_DATA_TYPE_REG_SZ       0x01
#define WINUSB_PROP_DATA_TYPE_REG_MULTI_SZ 0x07

/* WebUSB Descriptor Types */
#define WEBUSB_DESCRIPTOR_SET_HEADER_TYPE       0x00
#define WEBUSB_CONFIGURATION_SUBSET_HEADER_TYPE 0x01
#define WEBUSB_FUNCTION_SUBSET_HEADER_TYPE      0x02
#define WEBUSB_URL_TYPE                         0x03

/* WebUSB Request Codes */
#define WEBUSB_REQUEST_GET_URL 0x02

/* bScheme in URL descriptor */
#define WEBUSB_URL_SCHEME_HTTP  0x00
#define WEBUSB_URL_SCHEME_HTTPS 0x01

/* WebUSB Descriptor sizes */
#define WEBUSB_DESCRIPTOR_SET_HEADER_SIZE       5
#define WEBUSB_CONFIGURATION_SUBSET_HEADER_SIZE 4
#define WEBUSB_FUNCTION_SUBSET_HEADER_SIZE      3

/* Setup packet definition used to read raw data from USB line */
struct usb_setup_packet {
    /** Request type. Bits 0:4 determine recipient, see
	 * \ref usb_request_recipient. Bits 5:6 determine type, see
	 * \ref usb_request_type. Bit 7 determines data transfer direction, see
	 * \ref usb_endpoint_direction.
	 */
    uint8_t bmRequestType;

    /** Request. If the type bits of bmRequestType are equal to
	 * \ref usb_request_type::LIBUSB_REQUEST_TYPE_STANDARD
	 * "USB_REQUEST_TYPE_STANDARD" then this field refers to
	 * \ref usb_standard_request. For other cases, use of this field is
	 * application-specific. */
    uint8_t bRequest;

    /** Value. Varies according to request */
    uint16_t wValue;

    /** Index. Varies according to request, typically used to pass an index
	 * or offset */
    uint16_t wIndex;

    /** Number of bytes to transfer */
    uint16_t wLength;
} __PACKED;

#define USB_SIZEOF_SETUP_PACKET 8

/** Standard Device Descriptor */
struct usb_device_descriptor {
    uint8_t bLength;            /* Descriptor size in bytes = 18 */
    uint8_t bDescriptorType;    /* DEVICE descriptor type = 1 */
    uint16_t bcdUSB;            /* USB spec in BCD, e.g. 0x0200 */
    uint8_t bDeviceClass;       /* Class code, if 0 see interface */
    uint8_t bDeviceSubClass;    /* Sub-Class code, 0 if class = 0 */
    uint8_t bDeviceProtocol;    /* Protocol, if 0 see interface */
    uint8_t bMaxPacketSize0;    /* Endpoint 0 max. size */
    uint16_t idVendor;          /* Vendor ID per USB-IF */
    uint16_t idProduct;         /* Product ID per manufacturer */
    uint16_t bcdDevice;         /* Device release # in BCD */
    uint8_t iManufacturer;      /* Index to manufacturer string */
    uint8_t iProduct;           /* Index to product string */
    uint8_t iSerialNumber;      /* Index to serial number string */
    uint8_t bNumConfigurations; /* Number of possible configurations */
} __PACKED;

#define USB_SIZEOF_DEVICE_DESC 18

/** Standard Configuration Descriptor */
struct usb_configuration_descriptor {
    uint8_t bLength;             /* Descriptor size in bytes = 9 */
    uint8_t bDescriptorType;     /* CONFIGURATION type = 2 or 7 */
    uint16_t wTotalLength;       /* Length of concatenated descriptors */
    uint8_t bNumInterfaces;      /* Number of interfaces, this config. */
    uint8_t bConfigurationValue; /* Value to set this config. */
    uint8_t iConfiguration;      /* Index to configuration string */
    uint8_t bmAttributes;        /* Config. characteristics */
    uint8_t bMaxPower;           /* Max.power from bus, 2mA units */
} __PACKED;

#define USB_SIZEOF_CONFIG_DESC 9

/** Standard Interface Descriptor */
struct usb_interface_descriptor {
    uint8_t bLength;            /* Descriptor size in bytes = 9 */
    uint8_t bDescriptorType;    /* INTERFACE descriptor type = 4 */
    uint8_t bInterfaceNumber;   /* Interface no.*/
    uint8_t bAlternateSetting;  /* Value to select this IF */
    uint8_t bNumEndpoints;      /* Number of endpoints excluding 0 */
    uint8_t bInterfaceClass;    /* Class code, 0xFF = vendor */
    uint8_t bInterfaceSubClass; /* Sub-Class code, 0 if class = 0 */
    uint8_t bInterfaceProtocol; /* Protocol, 0xFF = vendor */
    uint8_t iInterface;         /* Index to interface string */
} __PACKED;

#define USB_SIZEOF_INTERFACE_DESC 9

/** Standard Endpoint Descriptor */
struct usb_endpoint_descriptor {
    uint8_t bLength;          /* Descriptor size in bytes = 7 */
    uint8_t bDescriptorType;  /* ENDPOINT descriptor type = 5 */
    uint8_t bEndpointAddress; /* Endpoint # 0 - 15 | IN/OUT */
    uint8_t bmAttributes;     /* Transfer type */
    uint16_t wMaxPacketSize;  /* Bits 10:0 = max. packet size */
    uint8_t bInterval;        /* Polling interval in (micro) frames */
} __PACKED;

#define USB_SIZEOF_ENDPOINT_DESC 7

/** Unicode (UTF16LE) String Descriptor */
struct usb_string_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t bString;
} __PACKED;

#define USB_SIZEOF_STRING_LANGID_DESC 4

/* USB Interface Association Descriptor */
struct usb_interface_association_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bFirstInterface;
    uint8_t bInterfaceCount;
    uint8_t bFunctionClass;
    uint8_t bFunctionSubClass;
    uint8_t bFunctionProtocol;
    uint8_t iFunction;
} __PACKED;

#define USB_SIZEOF_IAD_DESC 8

/** USB device_qualifier descriptor */
struct usb_device_qualifier_descriptor {
    uint8_t bLength;            /* Descriptor size in bytes = 10 */
    uint8_t bDescriptorType;    /* DEVICE QUALIFIER type = 6 */
    uint16_t bcdUSB;            /* USB spec in BCD, e.g. 0x0200 */
    uint8_t bDeviceClass;       /* Class code, if 0 see interface */
    uint8_t bDeviceSubClass;    /* Sub-Class code, 0 if class = 0 */
    uint8_t bDeviceProtocol;    /* Protocol, if 0 see interface */
    uint8_t bMaxPacketSize;     /* Endpoint 0 max. size */
    uint8_t bNumConfigurations; /* Number of possible configurations */
    uint8_t bReserved;          /* Reserved = 0 */
} __PACKED;

#define USB_SIZEOF_DEVICE_QUALIFIER_DESC 10

/* Microsoft OS function descriptor.
 * This can be used to request a specific driver (such as WINUSB) to be
 * loaded on Windows. Unlike other descriptors, it is requested by a special
 * request USB_REQ_GETMSFTOSDESCRIPTOR.
 * More details:
 *       https://msdn.microsoft.com/en-us/windows/hardware/gg463179
 * And excellent explanation:
 *       https://github.com/pbatard/libwdi/wiki/WCID-Devices
 *
 * The device will have exactly one "Extended Compat ID Feature Descriptor",
 * which may contain multiple "Function Descriptors" associated with
 * different interfaces.
 */

/* MS OS 1.0 string descriptor */
struct usb_msosv1_string_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bString[14];
    uint8_t bMS_VendorCode; /* Vendor Code, used for a control request */
    uint8_t bPad;           /* Padding byte for VendorCode look as UTF16 */
} __PACKED;

/* MS OS 1.0 Header descriptor */
struct usb_msosv1_compat_id_header_descriptor {
    uint32_t dwLength;
    uint16_t bcdVersion;
    uint16_t wIndex;
    uint8_t bCount;
    uint8_t reserved[7];
} __PACKED;

/* MS OS 1.0 Function descriptor */
struct usb_msosv1_comp_id_function_descriptor {
    uint8_t bFirstInterfaceNumber;
    uint8_t reserved1;
    uint8_t compatibleID[8];
    uint8_t subCompatibleID[8];
    uint8_t reserved2[6];
} __PACKED;

#define usb_msosv1_comp_id_create(x)                                         \
    struct usb_msosv1_comp_id {                                              \
        struct usb_msosv1_compat_id_header_descriptor compat_id_header;      \
        struct usb_msosv1_comp_id_function_descriptor compat_id_function[x]; \
    };

struct usb_msosv1_descriptor {
    const uint8_t *string;
    uint8_t vendor_code;
    const uint8_t *compat_id;
    const uint8_t **comp_id_property;
};

/* MS OS 2.0 Header descriptor */
struct usb_msosv2_header_descriptor {
    uint32_t dwLength;
    uint16_t bcdVersion;
    uint16_t wIndex;
    uint8_t bCount;
} __PACKED;

/*Microsoft OS 2.0 set header descriptor*/
struct usb_msosv2_set_header_descriptor {
    uint16_t wLength;
    uint16_t wDescriptorType;
    uint32_t dwWindowsVersion;
    uint16_t wDescriptorSetTotalLength;
} __PACKED;

/* Microsoft OS 2.0 compatibleID descriptor*/
struct usb_msosv2_comp_id_descriptor {
    uint16_t wLength;
    uint16_t wDescriptorType;
    uint8_t compatibleID[8];
    uint8_t subCompatibleID[8];
} __PACKED;

/* MS OS 2.0 property descriptor */
struct usb_msosv2_property_descriptor {
    uint16_t wLength;
    uint16_t wDescriptorType;
    uint32_t dwPropertyDataType;
    uint16_t wPropertyNameLength;
    const char *bPropertyName;
    uint32_t dwPropertyDataLength;
    const char *bPropertyData;
};

/* Microsoft OS 2.0 subset function descriptor  */
struct usb_msosv2_subset_function_descriptor {
    uint16_t wLength;
    uint16_t wDescriptorType;
    uint8_t bFirstInterface;
    uint8_t bReserved;
    uint16_t wSubsetLength;
} __PACKED;

struct usb_msosv2_descriptor {
    const uint8_t *compat_id;
    uint16_t compat_id_len;
    uint8_t vendor_code;
};

/* BOS header Descriptor */
struct usb_bos_header_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t wTotalLength;
    uint8_t bNumDeviceCaps;
} __PACKED;

/* BOS Capability platform Descriptor */
struct usb_bos_capability_platform_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDevCapabilityType;
    uint8_t bReserved;
    uint8_t PlatformCapabilityUUID[16];
} __PACKED;

/* BOS Capability MS OS Descriptors version 2 */
struct usb_bos_capability_msosv2_descriptor {
    uint32_t dwWindowsVersion;
    uint16_t wMSOSDescriptorSetTotalLength;
    uint8_t bVendorCode;
    uint8_t bAltEnumCode;
} __PACKED;

/* BOS Capability webusb */
struct usb_bos_capability_webusb_descriptor {
    uint16_t bcdVersion;
    uint8_t bVendorCode;
    uint8_t iLandingPage;
} __PACKED;

/* BOS Capability extension Descriptor*/
struct usb_bos_capability_extension_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDevCapabilityType;
    uint32_t bmAttributes;
} __PACKED;

/* Microsoft OS 2.0 Platform Capability Descriptor
* See https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/
* microsoft-defined-usb-descriptors
* Adapted from the source:
* https://github.com/sowbug/weblight/blob/master/firmware/webusb.c
* (BSD-2) Thanks http://janaxelson.com/files/ms_os_20_descriptors.c
*/
struct usb_bos_capability_platform_msosv2_descriptor {
    struct usb_bos_capability_platform_descriptor platform_msos;
    struct usb_bos_capability_msosv2_descriptor data_msosv2;
} __PACKED;

/* WebUSB Platform Capability Descriptor:
* https://wicg.github.io/webusb/#webusb-platform-capability-descriptor
*/
struct usb_bos_capability_platform_webusb_descriptor {
    struct usb_bos_capability_platform_descriptor platform_webusb;
    struct usb_bos_capability_webusb_descriptor data_webusb;
} __PACKED;

struct usb_webusb_url_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bScheme;
    char URL[];
} __PACKED;

struct usb_webusb_descriptor {
    uint8_t vendor_code;
    const uint8_t *string;
    uint32_t string_len;
} __PACKED;

struct usb_bos_descriptor {
    const uint8_t *string;
    uint32_t string_len;
};

/* USB Device Capability Descriptor */
struct usb_device_capability_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDevCapabilityType;
} __PACKED;

/** USB descriptor header */
struct usb_desc_header {
    uint8_t bLength;         /**< descriptor length */
    uint8_t bDescriptorType; /**< descriptor type */
};
// clang-format off
#define USB_DEVICE_DESCRIPTOR_INIT(bcdUSB, bDeviceClass, bDeviceSubClass, bDeviceProtocol, idVendor, idProduct, bcdDevice, bNumConfigurations) \
    0x12,                       /* bLength */                                                                                              \
    USB_DESCRIPTOR_TYPE_DEVICE, /* bDescriptorType */                                                                                      \
    WBVAL(bcdUSB),              /* bcdUSB */                                                                                               \
    bDeviceClass,               /* bDeviceClass */                                                                                         \
    bDeviceSubClass,            /* bDeviceSubClass */                                                                                      \
    bDeviceProtocol,            /* bDeviceProtocol */                                                                                      \
    0x40,                       /* bMaxPacketSize */                                                                                       \
    WBVAL(idVendor),            /* idVendor */                                                                                             \
    WBVAL(idProduct),           /* idProduct */                                                                                            \
    WBVAL(bcdDevice),           /* bcdDevice */                                                                                            \
    USB_STRING_MFC_INDEX,       /* iManufacturer */                                                                                        \
    USB_STRING_PRODUCT_INDEX,   /* iProduct */                                                                                             \
    USB_STRING_SERIAL_INDEX,    /* iSerial */                                                                                              \
    bNumConfigurations          /* bNumConfigurations */

#define USB_CONFIG_DESCRIPTOR_INIT(wTotalLength, bNumInterfaces, bConfigurationValue, bmAttributes, bMaxPower) \
    0x09,                              /* bLength */                                                       \
    USB_DESCRIPTOR_TYPE_CONFIGURATION, /* bDescriptorType */                                               \
    WBVAL(wTotalLength),               /* wTotalLength */                                                  \
    bNumInterfaces,                    /* bNumInterfaces */                                                \
    bConfigurationValue,               /* bConfigurationValue */                                           \
    0x00,                              /* iConfiguration */                                                \
    bmAttributes,                      /* bmAttributes */                                                  \
    USB_CONFIG_POWER_MA(bMaxPower)     /* bMaxPower */

#define USB_DEVICE_QUALIFIER_DESCRIPTOR_INIT(bcdUSB, bDeviceClass, bDeviceSubClass, bDeviceProtocol, bNumConfigurations) \
    0x0A,                                 /* bLength */                                                    \
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER, /* bDescriptorType */                                            \
    WBVAL(bcdUSB),              /* bcdUSB */                                                               \
    bDeviceClass,               /* bDeviceClass */                                                         \
    bDeviceSubClass,            /* bDeviceSubClass */                                                      \
    bDeviceProtocol,            /* bDeviceProtocol */                                                      \
    0x40,                       /* bMaxPacketSize */                                                       \
    bNumConfigurations,         /* bNumConfigurations */                                                   \
    0x00                        /* bReserved */

#define USB_OTHER_SPEED_CONFIG_DESCRIPTOR_INIT(wTotalLength, bNumInterfaces, bConfigurationValue, bmAttributes, bMaxPower) \
    0x09,                              /* bLength */                                                       \
    USB_DESCRIPTOR_TYPE_OTHER_SPEED,   /* bDescriptorType */                                               \
    WBVAL(wTotalLength),               /* wTotalLength */                                                  \
    bNumInterfaces,                    /* bNumInterfaces */                                                \
    bConfigurationValue,               /* bConfigurationValue */                                           \
    0x00,                              /* iConfiguration */                                                \
    bmAttributes,                      /* bmAttributes */                                                  \
    USB_CONFIG_POWER_MA(bMaxPower)     /* bMaxPower */

#define USB_INTERFACE_DESCRIPTOR_INIT(bInterfaceNumber, bAlternateSetting, bNumEndpoints,                  \
                                      bInterfaceClass, bInterfaceSubClass, bInterfaceProtocol, iInterface) \
    0x09,                          /* bLength */                                                       \
    USB_DESCRIPTOR_TYPE_INTERFACE, /* bDescriptorType */                                               \
    bInterfaceNumber,              /* bInterfaceNumber */                                              \
    bAlternateSetting,             /* bAlternateSetting */                                             \
    bNumEndpoints,                 /* bNumEndpoints */                                                 \
    bInterfaceClass,               /* bInterfaceClass */                                               \
    bInterfaceSubClass,            /* bInterfaceSubClass */                                            \
    bInterfaceProtocol,            /* bInterfaceProtocol */                                            \
    iInterface                     /* iInterface */

#define USB_ENDPOINT_DESCRIPTOR_INIT(bEndpointAddress, bmAttributes, wMaxPacketSize, bInterval) \
    0x07,                         /* bLength */                                             \
    USB_DESCRIPTOR_TYPE_ENDPOINT, /* bDescriptorType */                                     \
    bEndpointAddress,             /* bEndpointAddress */                                    \
    bmAttributes,                 /* bmAttributes */                                        \
    WBVAL(wMaxPacketSize),        /* wMaxPacketSize */                                      \
    bInterval                     /* bInterval */

#define USB_IAD_INIT(bFirstInterface, bInterfaceCount, bFunctionClass, bFunctionSubClass, bFunctionProtocol) \
    0x08,                                      /* bLength */                                             \
    USB_DESCRIPTOR_TYPE_INTERFACE_ASSOCIATION, /* bDescriptorType */                                     \
    bFirstInterface,                           /* bFirstInterface */                                     \
    bInterfaceCount,                           /* bInterfaceCount */                                     \
    bFunctionClass,                            /* bFunctionClass */                                      \
    bFunctionSubClass,                         /* bFunctionSubClass */                                   \
    bFunctionProtocol,                         /* bFunctionProtocol */                                   \
    0x00                                       /* iFunction */

#define USB_LANGID_INIT(id)                           \
    0x04,                           /* bLength */     \
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */ \
    WBVAL(id)                   /* wLangID0 */
// clang-format on

#endif /* USB_DEF_H */
